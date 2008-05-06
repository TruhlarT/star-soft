// $Id: StJetEtCell.cxx,v 1.11 2008/05/06 02:13:16 tai Exp $
#include "StJetEtCell.h"

StJetEtCell::StJetEtCell(double etaMin, double etaMax, double phiMin, double phiMax)
  : StEtaPhiCell(etaMin, etaMax, phiMin, phiMax)
{

}

StJetEtCell::StJetEtCell(const StJetEtCell& c)
  : StEtaPhiCell(c)
{

}

StJetEtCell::StJetEtCell()
{

}

StJetEtCell::~StJetEtCell()
{

}

StEtaPhiCell* StJetEtCell::clone() const
{
  return new StJetEtCell(*this);
}

void StJetEtCell::add(const StProtoJet& pj)
{
  mEt += pj.eT();
  mProtoJet.add(pj);
  mUpToDate = false;
}

void StJetEtCell::clear()
{
  mEt = 0;
  mNtimesUsed = 0;
  mCells.clear();
  mProtoJet.clear();
  mUpToDate = false;
}

void StJetEtCell::add(StEtaPhiCell* cell)
{
  mEt += cell->eT();
  mCells.push_back(cell);
  cell->setNtimesUsed( cell->nTimesUsed() + 1 );
  mUpToDate=false;
}

