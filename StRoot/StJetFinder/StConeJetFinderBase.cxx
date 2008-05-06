// $Id: StConeJetFinderBase.cxx,v 1.3 2008/05/06 22:43:48 tai Exp $
#include "StConeJetFinderBase.h"

#include "TObject.h"

//std
#include <iostream>
#include <algorithm>
#include <time.h>
#include <map>
using std::sort;

#include "StMessMgr.h"

//StJetFinder
#include "StJetEtCell.h"
#include "StJetSpliterMerger.h"
#include "StProtoJet.h"

using namespace StSpinJet;

StConeJetFinderBase::StConeJetFinderBase(const StConePars& pars)
  : mPars(pars)
  , mWorkCell(new StJetEtCell)
  , mSearchCounter(0)
  , _cellGrid(mPars)
{

}

StConeJetFinderBase::~StConeJetFinderBase()
{

}

void StConeJetFinderBase::Init()
{
  _cellGrid.buildGrid(makeCellFactory());
}

StJetEtCellFactory* StConeJetFinderBase::makeCellFactory()
{
  return new StJetEtCellFactory;
}

void StConeJetFinderBase::clearPreviousResult()
{
  for(CellList::iterator it = _preJets.begin(); it != _preJets.end(); ++it) {
    delete *it;
  }
  _preJets.clear();
  mSearchCounter = 0;
}

StEtaPhiCell::CellList StConeJetFinderBase::generateEtOrderedList(JetList& protoJetList)
{
  _cellGrid.fillGridWith(protoJetList);
  return _cellGrid.EtSortedCellList();
}

StEtaPhiCell::CellList StConeJetFinderBase::generateToSearchListFrom(CellList& orderedList)
{
  CellList toSearchList;
 
  for (CellList::iterator cell = orderedList.begin(); cell != orderedList.end(); ++cell) {
  
    if ((*cell)->eT() <= mPars.seedEtMin()) break;
  
    toSearchList.push_back(*cell);

  }
 
  return toSearchList;
}

void StConeJetFinderBase::findProtoJets(CellList& toSearchList)
{
    for (CellList::iterator cell = toSearchList.begin(); cell != toSearchList.end(); ++cell) {
  
      if (shouldNotSearchForJetAroundThis((*cell))) continue;

      findJetAroundThis(*cell);
    }
}

void StConeJetFinderBase::storeTheResultIn(JetList& protoJetList)
{
  protoJetList.clear();
  
  for (CellList::iterator jet = _preJets.begin(); jet != _preJets.end(); ++jet) {

    if ((*jet)->cellList().size() == 0) continue;

    protoJetList.push_back( collectCell(*jet) );
  }
}

bool StConeJetFinderBase::shouldNotSearchForJetAroundThis(const StEtaPhiCell* cell) const
{
  return false;
}

void StConeJetFinderBase::initializeWorkCell(const StEtaPhiCell* other)
{
    mWorkCell->clear();
    *mWorkCell = *other;
    mWorkCell->setEt(0.);
    if (mWorkCell->cellList().empty()==false) {
	cout <<"StConeJetFinderBase::initializeWorkCell(). ERROR:\t"
	     <<"workCell is not empty. abort()"<<endl;
	abort();
    }
}

StConeJetFinderBase::SearchResult StConeJetFinderBase::doSearch()
{
    
  ++mSearchCounter;

  if (mPars.performMinimization() && mSearchCounter > 100) {
    return kTooManyTries;
  }
    
  CellList cellList = _cellGrid.WithinTheConeRadiusCellList(*mWorkCell);

  for (CellList::iterator cell = cellList.begin(); cell != cellList.end(); ++cell) {
    if(shouldNotAddToTheCell(*mWorkCell, **cell)) continue;
    mWorkCell->addCell(*cell);
  }

  const StProtoJet& centroid = mWorkCell->centroid();

  if (!isInTheVolume(centroid.eta(), centroid.phi())) return kLeftVolume;

  if(areTheyInTheSameCell(mWorkCell->eta(), mWorkCell->phi(), centroid.eta(), centroid.phi())) return kConverged;

  return kContinueSearch;
}

bool StConeJetFinderBase::isInTheVolume(double eta, double phi)
{
    return (_cellGrid.Cell(eta, phi)) ? true : false;
}

bool StConeJetFinderBase::shouldNotAddToTheCell(const StEtaPhiCell& theCell, const StEtaPhiCell& otherCell) const
{
  if (otherCell.empty()) return true;
  if (otherCell.eT() <= mPars.assocEtMin()) return true; 
  return false;
}

bool StConeJetFinderBase::areTheyInTheSameCell(double eta1, double phi1, double eta2, double phi2)
{
  return(_cellGrid.Cell(eta1, phi1)->isSamePosition(*_cellGrid.Cell(eta2, phi2)));
}

void StConeJetFinderBase::addToPrejets(StEtaPhiCell& cell)
{
  StEtaPhiCell* realCell = _cellGrid.Cell(cell.eta(), cell.phi());
  if (!realCell) {
    cout << "PreJetInitializer(). ERROR:\t"
	 << "real Cell doesn't exist." << endl;
    abort();
  }
	
  cell.setEt(0);
  for(CellList::iterator etCell = cell.cellList().begin(); etCell != cell.cellList().end(); ++etCell) {
    (*etCell)->update();
    cell.setEt(cell.Et() + (*etCell)->eT());
  }

  //  _preJets.push_back(new StEtaPhiCell(cell));
  _preJets.push_back(cell.clone());

}

const StProtoJet& StConeJetFinderBase::collectCell(StEtaPhiCell* seed)
{

  if (seed->cellList().empty()) {
    StProtoJet& center = seed->protoJet();
    center.update();
    cout <<"\treturn w/o action.  empty cell"<<endl;
    return center;
  }
    
	
  //arbitrarily choose protojet from first cell in list
  CellList& cells = seed->cellList();
  StEtaPhiCell* centerCell = cells.front();
  StProtoJet& center = centerCell->protoJet();
	
		
  //now combine protojets from other cells
  for (CellList::iterator it = cells.begin(); it != cells.end(); ++it) {
    if (it != cells.begin()) { //don't double count first!
      StEtaPhiCell* cell = (*it);
      if (!cell) {
	cout <<"\tStConeJetFinderBase::collectCell(). ERROR:\t"
	     <<"null cell.  skip"<<endl;
      }
      if (centerCell==*it) {
	cout <<"\tStConeJetFinderBase::collectCell(). ERROR:\t"
	     <<"attempt to add self! skip"<<endl;
      }	else {
	//cout <<"\t\tadding cell:\t"<<icell++<<endl;
	if (cell->empty()==false) {
	  center.add( cell->protoJet() );
	}
      }
    }
  }
  center.update();
  return center;
}



//non members ---

void PreJetLazyUpdater ::operator()(StEtaPhiCell& cell)
{
    sumEt += cell.eT();
}

void PreJetLazyUpdater ::operator()(StEtaPhiCell* cell)
{
    (*this)(*cell);
}

void PostMergeUpdater::operator()(StEtaPhiCell& cell)
{
    //now update each cell:
    PreJetLazyUpdater updater;
    updater = for_each( cell.cellList().begin(), cell.cellList().end(), updater );
	
    //now update jet-eT
    cell.mEt = updater.sumEt;
}

