/***************************************************************************
 *
 * $Id: StEbye2ptMaker.cxx,v 1.1 2000/02/05 03:15:21 jgreid Exp $
 *
 * StEbye2ptMaker.cxx
 *
 * Author: Jeff Reid, UW
 *         with design advice from Thomas Ullrich, Yale
 *
 ***************************************************************************
 *
 * Description:  This is a maker to generate 2-point correlation
 *                spaces (App) from p_t spectra
 *
 ***************************************************************************
 *
 * $Log: StEbye2ptMaker.cxx,v $
 * Revision 1.1  2000/02/05 03:15:21  jgreid
 * Initial revision
 *
 *
 **************************************************************************/
#include "StEbye2ptMaker.h"
#include "StChain.h"
#include "StEventTypes.h"
#include "StMessMgr.h"
#include "StParticleTypes.hh"

#include "SystemOfUnits.h"
#ifndef ST_NO_NAMESPACES
using namespace units;
#endif

static const char rcsid[] = "$Id: StEbye2ptMaker.cxx,v 1.1 2000/02/05 03:15:21 jgreid Exp $";

ClassImp(StEbye2ptMaker)

StEbye2ptMaker::StEbye2ptMaker(const Char_t *name) : StMaker(name) { /* noop*/ }

StEbye2ptMaker::~StEbye2ptMaker() { /* noop */ }

Int_t
StEbye2ptMaker::Init()
{
  Int_t aMax = 5000;
  Int_t BinNumber = 25;

  // allocate the nexessary histograms
  mSibPP = new TH2F("SPP","Sibling : +.+",BinNumber,0,1,BinNumber,0,1);
  mSibPM = new TH2F("SPM","Sibling : +.-",BinNumber,0,1,BinNumber,0,1);
  mSibMP = new TH2F("SMP","Sibling : -.+",BinNumber,0,1,BinNumber,0,1);
  mSibMM = new TH2F("SMM","Sibling : -.-",BinNumber,0,1,BinNumber,0,1);

  mMixPP = new TH2F("MPP","Mixed : +.+",BinNumber,0,1,BinNumber,0,1);
  mMixPM = new TH2F("MPM","Mixed : +.-",BinNumber,0,1,BinNumber,0,1);
  mMixMP = new TH2F("MMP","Mixed : -.+",BinNumber,0,1,BinNumber,0,1);
  mMixMM = new TH2F("MMM","Mixed : -.-",BinNumber,0,1,BinNumber,0,1);

  // allocate the particle arrays for mixing
  mPreviousEventPlus = new Double_t[aMax];
  assert (mPreviousEventPlus != 0);
  mPreviousEventMinus = new Double_t[aMax]; 
  assert (mPreviousEventMinus != 0);
  
  mThisEventPlus = new Double_t[aMax];
  assert (mThisEventPlus != 0);
  mThisEventMinus = new Double_t[aMax];
  assert (mThisEventMinus != 0);

  // set the first element of the event arrays to zero
  //  (we use Event[0] to keep track of the number of valid 
  //   elements in the array, and they start out empty)
  mPreviousEventPlus[0] = 0;
  mPreviousEventMinus[0] = 0;
  mThisEventPlus[0] = 0;
  mThisEventMinus[0] = 0;
    
  return StMaker::Init();
}

void
StEbye2ptMaker::Clear(Option_t *opt)
{
  StMaker::Clear();
}

Int_t
StEbye2ptMaker::Finish()
{
  // create the histogram output file
  //  (file name is currently hardwired, fix this)
  TFile histogramFile("ebye2pt.root","recreate");

  // write out histograms to file

  mSibPP->Write();
  mSibPM->Write();
  mSibMP->Write();
  mSibMM->Write();

  mMixPP->Write();
  mMixPM->Write();
  mMixMP->Write();
  mMixMM->Write();

  histogramFile.Close();

  // give back the allocated memory for the histograms
  //   and particle arrays
  delete mSibPP;
  delete mSibPM;
  delete mSibMP;
  delete mSibMM;

  delete mMixPP;
  delete mMixPM;
  delete mMixMP;
  delete mMixMM;

  delete [] mPreviousEventPlus;
  delete [] mPreviousEventMinus;
  delete [] mThisEventPlus;
  delete [] mThisEventMinus;

  return kStOK;
}

Int_t
StEbye2ptMaker::Make()
{
    Double_t *tempEventPlus,*tempEventMinus;

    StEvent* mEvent;
    mEvent = (StEvent *) GetInputDS("StEvent");
    if (! mEvent) return kStOK; // If no event, we're done
    StEvent& ev = *mEvent;
    
    // processEvent() applies the event and track cuts to the current event
    //  and fills thisEvent with the p_t values which pass these cuts.
    if((processEvent(ev)) == kStOk) {

      // if there is a non-empty event previous to this one then mix them
      if (mPreviousEventPlus[0] != 0) mixEvents();

      // set the previous event to be the current event (and the current to be
      //  the pervious so we don't have to reallocate memory)
      tempEventPlus = mPreviousEventPlus;
      tempEventMinus = mPreviousEventMinus;

      mPreviousEventPlus = mThisEventPlus;
      mPreviousEventMinus = mThisEventMinus;

      mThisEventPlus = tempEventPlus;
      mThisEventMinus = tempEventMinus;

      mThisEventPlus[0] = 0;
      mThisEventMinus[0] = 0;

      gMessMgr->Info() << " StEbye2ptMaker::Make() completed OK " << endl;
      return kStOK;

    } else {
       
      gMessMgr->Info() << " StEbye2ptMaker::Make() FAILED" << endl;
      return kStErr;

    } 
}

Int_t
StEbye2ptMaker::processEvent(StEvent& event) 
{

  // hardwire cut values temproarily
  float pt_min = 0;
  float pt_max = 20;
   
  // define variables
  float pt, mtOnly;
  float charge;

  float dip;
  float theta, eta;

  float nFound, nMax;

  float trackCount = 0.0;
  float meanPt = 0.0;
  float meanPtSquared = 0.0;
  float meanEta = 0.0;
  float meanEtaSquared = 0.0;

  double s;
  StThreeVectorD dca, p;

  double dcaX, dcaY, dcaZ, dcaM;

  int minusCount = 0;
  int plusCount = 0;
  
  float minusPt = 0;
  float minusPt2 = 0;
  float PlusPt = 0;
  float PlusPt2 = 0;
	    
  double PionMass = StPionPlus::instance()->mass();
  float Temperature = 0.16;

  float Minimum = (1+(PionMass/Temperature))*exp(-PionMass/Temperature);

  StVertex *primeVertex;

  StThreeVectorD origin(0,0,0);
  StThreeVectorD primaryVertexPosition;

  // Number of primary vertices
  Int_t npvtx = event.numberOfPrimaryVertices();
  if (npvtx == 0) return kStErr;
  
  // loop over these and choose the one with the most daughters,
  //  or default to primaryVertex(0) if there is only one
  primeVertex = event.primaryVertex(0);
  for (Int_t i = 1 ; i < npvtx ; i++) {
    if (event.primaryVertex(i)->numberOfDaughters() > primeVertex->numberOfDaughters())
      primeVertex = event.primaryVertex(i);
  } 

  // ** track loop **
  if (primeVertex) {
    primaryVertexPosition = primeVertex->position();
    const StSPtrVecTrackNode& theNodes = event.trackNodes();
    for (unsigned int k=0; k<theNodes.size(); k++) {

      // get the momentum of the current track
      pt = theNodes[k]->track(global)->geometry()->momentum().perp();

      // get the charge of the current track
      charge = theNodes[k]->track(global)->geometry()->charge();

      // get Nfound & Nmax
      nFound = theNodes[k]->track(global)->fitTraits().numberOfFitPoints();
      nMax = theNodes[k]->track(global)->numberOfPossiblePoints();

      // calculate distance of closest approach to the primary vertex position
      s = theNodes[k]->track(global)->geometry()->helix().pathLength(primaryVertexPosition);
      p = theNodes[k]->track(global)->geometry()->helix().at(s);
      dca = p-primaryVertexPosition;
      dcaX = dca.x()/centimeter;
      dcaY = dca.y()/centimeter;
      dcaZ = dca.z()/centimeter;
      dcaM = (abs(dca))/centimeter;

      // calculate mt (needed for temperature calculation)
      mtOnly = sqrt(pt*pt + PionMass*PionMass);

      // calculate eta
      dip = theNodes[k]->track(global)->geometry()->dipAngle();
      theta = (M_PI/2.0)-dip;
      eta = -log(tan(theta/2.0));

      // ** cut out extreme pt values [cut #1]
      if ((pt > pt_min) && (pt < pt_max)) {

        if (charge < 0) {
          // precrement so that the 0th element of the pt arrays can be used
          //  for the number of quality tracks in the event
          minusCount++;
          mThisEventMinus[minusCount]=1-(1+(mtOnly/Temperature))*exp(-mtOnly/Temperature)/Minimum;
          minusPt += pt;
          minusPt2 += pt*pt;
	}
        else if (charge > 0) {
          plusCount++;
          mThisEventPlus[plusCount]=1-(1+(mtOnly/Temperature))*exp(-mtOnly/Temperature)/Minimum;
          PlusPt += pt;
          PlusPt2 += pt*pt;
        }

        // calculate number of particles that make the cuts, and the first two pt moments
        trackCount++;
        meanPtSquared += pt*pt;
        meanPt += pt;

  	meanEtaSquared += eta*eta;
	meanEta += eta;

      } // [cut #1]

    } // ** end of track loop **
  }
  mThisEventMinus[0] = minusCount;
  mThisEventPlus[0] = plusCount;

  minusPt2 /= minusCount;
  minusPt /= minusCount;
  PlusPt2 /= plusCount;
  PlusPt /= plusCount;

  return kStOK;
}

Int_t
StEbye2ptMaker::mixEvents()
{
    // fill the manyHistos that we need

    int l, j;
    //float k, qp, qm;

    for (j = 1 ; j <= mThisEventMinus[0] ; j++) {
      for (l = 1 ; l <= mPreviousEventPlus[0] ; l++) {
        //k = (mPreviousEventPlus[l]+mThisEventMinus[j])/2;
        //qp = (mPreviousEventPlus[l]-mThisEventMinus[j])/2;
        //qm = -qp;
        mMixPM->Fill(mPreviousEventPlus[l],mThisEventMinus[j],1);
        mMixMP->Fill(mThisEventMinus[j],mPreviousEventPlus[l],1);
        //MixedHkq0->Fill(k,qp,1);
        //MixedHkq0->Fill(k,qm,1);
      }
      for (l = 1 ; l <= mPreviousEventMinus[0] ; l++) {
        //k = (mPreviousEventMinus[l]+mThisEventMinus[j])/2;
        //qp = (mPreviousEventMinus[l]-mThisEventMinus[j])/2;
        //qm = -qp;
        mMixMM->Fill(mPreviousEventMinus[l],mThisEventMinus[j],1);
        mMixMM->Fill(mThisEventMinus[j],mPreviousEventMinus[l],1);
        //MixedHkqM->Fill(k,qp,1);
        //MixedHkqM->Fill(k,qm,1);
      }
      for (l = j+1 ; l <= mThisEventMinus[0] ; l++) {
        //k = (mThisEventMinus[l]+mThisEventMinus[j])/2;
        //qp = (mThisEventMinus[l]-mThisEventMinus[j])/2;
        //qm = -qp;
        mSibMM->Fill(mThisEventMinus[l],mThisEventMinus[j],1);
        mSibMM->Fill(mThisEventMinus[j],mThisEventMinus[l],1);
        //SiblingHkqM->Fill(k,qp,1);
        //SiblingHkqM->Fill(k,qm,1);
      }
      //cout << "filled m hists" << endl;
      //histograms->negatv->Fill(mThisEventMinus[j]);
      //cout << "filled negatv" << mThisEventMinus[0] << j << endl;
    }
    for (j = 1 ; j <= mThisEventPlus[0] ; j++) {
      for (l = 1 ; l <= mThisEventMinus[0] ; l++) {
        //k = (mThisEventMinus[l]+mThisEventPlus[j])/2;
        //qp = (mThisEventMinus[l]-mThisEventPlus[j])/2;
        //qm = -qp;
        mSibMP->Fill(mThisEventMinus[l],mThisEventPlus[j],1);
        mSibPM->Fill(mThisEventPlus[j],mThisEventMinus[l],1);
        //SiblingHkq0->Fill(k,qp,1);
        //SiblingHkq0->Fill(k,qm,1);
      }
      for (l = 1 ; l <= mPreviousEventPlus[0] ; l++) {
        //k = (mPreviousEventPlus[l]+mThisEventPlus[j])/2;
        //qp = (mPreviousEventPlus[l]-mThisEventPlus[j])/2;
        //qm = -qp;
        mMixPP->Fill(mPreviousEventPlus[l],mThisEventPlus[j],1);
        mMixPP->Fill(mThisEventPlus[j],mPreviousEventPlus[l],1);
        //MixedHkqP->Fill(k,qp,1);
        //MixedHkqP->Fill(k,qm,1);
      }
      for (l = j+1 ; l <= mThisEventPlus[0] ; l++) {
        //k = (mThisEventPlus[l]+mThisEventPlus[j])/2;
        //qp = (mThisEventPlus[l]-mThisEventPlus[j])/2;
        //qm = -qp;
        mSibPP->Fill(mThisEventPlus[l],mThisEventPlus[j],1);
        mSibPP->Fill(mThisEventPlus[j],mThisEventPlus[l],1);
        //SiblingHkqP->Fill(k,qp,1);
        //SiblingHkqP->Fill(k,qm,1);
      }
      for (l = 1 ; l <= mPreviousEventMinus[0] ; l++) {
        mMixMP->Fill(mPreviousEventMinus[l],mThisEventPlus[j],1);
        mMixPM->Fill(mThisEventPlus[j],mPreviousEventMinus[l],1);
      }
      //cout << "filled p hists" << endl;
      //histograms->positv->Fill(mThisEventPlus[j]);
      //cout << "filled positv" << endl;
    }

    return kStOK;
}
