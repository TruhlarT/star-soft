////////////////////////////////////////////////////////////////////////////
//
// $Id: StFlowScalarProdMaker.cxx,v 1.2 2001/12/21 17:01:59 aihong Exp $
//
// Authors: Method proposed by Art and Sergei, code written by Aihong
//          Frame adopted from Art and Raimond's StFlowAnalysisMaker.
////////////////////////////////////////////////////////////////////////////
//
// Description:  Maker to analyze Flow using the scalar product method
//
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include "StMaker.h"
#include "StFlowScalarProdMaker.h"
#include "StFlowMaker/StFlowMaker.h"
#include "StFlowMaker/StFlowEvent.h"
#include "StFlowMaker/StFlowConstants.h"
#include "StFlowMaker/StFlowSelection.h"
#include "StFlowMaker/StFlowCutTrack.h"
#include "StEnumerations.h"
#include "PhysicalConstants.h"
#include "SystemOfUnits.h"
#include "TVector2.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TF1.h"
#include "TOrdCollection.h"
#include "StMessMgr.h"
#include "TMath.h"
#define PR(x) cout << "##### FlowScalarProdAnalysis: " << (#x) << " = " << (x) << endl;

ClassImp(StFlowScalarProdMaker)

//-----------------------------------------------------------------------

StFlowScalarProdMaker::StFlowScalarProdMaker(const Char_t* name): StMaker(name),
  MakerName(name) {
  pFlowSelect = new StFlowSelection();
}

StFlowScalarProdMaker::StFlowScalarProdMaker(const Char_t* name,
					 const StFlowSelection& flowSelect) :
  StMaker(name), MakerName(name) {
  pFlowSelect = new StFlowSelection(flowSelect); //copy constructor
}

//-----------------------------------------------------------------------

StFlowScalarProdMaker::~StFlowScalarProdMaker() {
}

//-----------------------------------------------------------------------

Int_t StFlowScalarProdMaker::Make() {
  // Fill histograms

  // Get a pointer to StFlowEvent
  StFlowMaker* pFlowMaker = NULL;
  pFlowMaker = (StFlowMaker*)GetMaker("Flow");
  if (pFlowMaker) pFlowEvent = pFlowMaker->FlowEventPointer();
  if (pFlowEvent) {
    if (pFlowSelect->Select(pFlowEvent)) {      // event selected
      FillFromFlowEvent();                      // get event quantities
      FillEventHistograms();                    // fill from FlowEvent
      if (pFlowEvent) FillParticleHistograms(); // fill particle histograms
    }
    if (Debug()) StMaker::PrintInfo();
  } else {
    gMessMgr->Info("##### FlowScalarProdMaker: FlowEvent pointer null");
  }
  
  return kStOK;
}

//-----------------------------------------------------------------------

Int_t StFlowScalarProdMaker::Init() {
  // Book histograms

  float ptMaxPart = Flow::ptMaxPart;
  if (pFlowSelect->PtMaxPart()) {
    ptMaxPart = pFlowSelect->PtMaxPart();
  }
  xLabel = "Pseudorapidity";
  if (strlen(pFlowSelect->PidPart()) != 0) { xLabel = "Rapidity"; }

  

  
  TString* histTitle;


  for (int k = 0; k < Flow::nSels; k++) {
    char countSels[2];
    sprintf(countSels,"%d",k+1);

    // for each selection


    // resolution
    histTitle = new TString("Flow_Res_Sel");
    histTitle->Append(*countSels);
    histFull[k].mHistRes = new TProfile(histTitle->Data(), histTitle->Data(),
      Flow::nHars, 0.5, (float)(Flow::nHars) + 0.5, -1.*FLT_MAX, FLT_MAX, "");
    histFull[k].mHistRes->SetXTitle("Harmonic");
    histFull[k].mHistRes->SetYTitle("Resolution");
    delete histTitle;

    // vObs
    histTitle = new TString("Flow_vObs_Sel");
    histTitle->Append(*countSels);
    histFull[k].mHist_vObs = new TProfile(histTitle->Data(), histTitle->Data(),
      Flow::nHars, 0.5, (float)(Flow::nHars) + 0.5, -100., 100., "");
    histFull[k].mHist_vObs->SetXTitle("Harmonic");
    histFull[k].mHist_vObs->SetYTitle("vObs (%)");
    delete histTitle;
    
    // for each harmonic
    for (int j = 0; j < Flow::nHars; j++) {
      char countHars[2];
      sprintf(countHars,"%d",j+1);

      // Flow observed
      histTitle = new TString("Flow_vObs2D_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_vObs2D =	new TProfile2D(histTitle->Data(),
        histTitle->Data(), Flow::nEtaBins, Flow::etaMin, Flow::etaMax, Flow::nPtBins, 
		 Flow::ptMin, ptMaxPart, -100., 100., "");
      histFull[k].histFullHar[j].mHist_vObs2D->SetXTitle((char*)xLabel.Data());
      histFull[k].histFullHar[j].mHist_vObs2D->SetYTitle("Pt (GeV)");
      delete histTitle;

      // Flow observed profiles
      histTitle = new TString("Flow_vObsEta_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_vObsEta = new TProfile(histTitle->Data(),
        histTitle->Data(), Flow::nEtaBins, Flow::etaMin, Flow::etaMax, 
							      -100., 100., "");
      histFull[k].histFullHar[j].mHist_vObsEta->SetXTitle((char*)xLabel.Data());
      histFull[k].histFullHar[j].mHist_vObsEta->SetYTitle("v (%)");
      delete histTitle;

      histTitle = new TString("Flow_vObsPt_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_vObsPt = new TProfile(histTitle->Data(),
        histTitle->Data(), Flow::nPtBins, Flow::ptMin, ptMaxPart, -100., 100., "");
      histFull[k].histFullHar[j].mHist_vObsPt->SetXTitle("Pt (GeV)");
      histFull[k].histFullHar[j].mHist_vObsPt->SetYTitle("v (%)");
      delete histTitle;

    }
  }

  gMessMgr->SetLimit("##### FlowAnalysis", 2);
  gMessMgr->Info("##### FlowAnalysis: $Id: StFlowScalarProdMaker.cxx,v 1.2 2001/12/21 17:01:59 aihong Exp $");

  return StMaker::Init();
}



//-----------------------------------------------------------------------

void StFlowScalarProdMaker::FillFromFlowEvent() {
  // Get event quantities from StFlowEvent
  for (int k = 0; k < Flow::nSels; k++) {
    pFlowSelect->SetSelection(k);
    for (int j = 0; j < Flow::nHars; j++) {
      pFlowSelect->SetHarmonic(j);
      for (int n = 0; n < Flow::nSubs; n++) {
	pFlowSelect->SetSubevent(n);
	int i = Flow::nSels*k + n;
	// sub-event quantities
        mQSub[i][j]=pFlowEvent->Q(pFlowSelect);
     }

      pFlowSelect->SetSubevent(-1);
      // full event quantities
      mQ[k][j]    = pFlowEvent->Q(pFlowSelect);
    }
  }

}

//-----------------------------------------------------------------------

void StFlowScalarProdMaker::FillEventHistograms() {

  for (int k = 0; k < Flow::nSels; k++) {
    for (int j = 0; j < Flow::nHars; j++) {
      float order  = (float)(j+1);


      histFull[k].mHistRes->Fill(order, (mQSub[Flow::nSels*k + 0][j].X()) * (mQSub[Flow::nSels*k + 1][j].X()) + (mQSub[Flow::nSels*k + 0][j].Y()) * (mQSub[Flow::nSels*k + 1][j].Y()) ); 

    }
  }

}

//-----------------------------------------------------------------------

void StFlowScalarProdMaker::FillParticleHistograms() {
  // Fill histograms from the particles


  // Initialize Iterator
  StFlowTrackCollection* pFlowTracks = pFlowEvent->TrackCollection();
  StFlowTrackIterator itr;
  
  for (itr = pFlowTracks->begin(); itr != pFlowTracks->end(); itr++) {
    StFlowTrack* pFlowTrack = *itr;

    float phi       = pFlowTrack->Phi();
    if (phi < 0.) phi += twopi;
    float eta       = pFlowTrack->Eta();
    float pt        = pFlowTrack->Pt();

    for (int k = 0; k < Flow::nSels; k++) {
      pFlowSelect->SetSelection(k);
      for (int j = 0; j < Flow::nHars; j++) {
	bool oddHar = (j+1) % 2;
	pFlowSelect->SetHarmonic(j);
	double order  = (double)(j+1);

	  // Get phiWgt
	  double phiWgt = pFlowEvent->PhiWeight(k, j, pFlowTrack);

	  double phiWgtRaw = phiWgt;
	  if (pFlowEvent->PtWgt()) { // remove pt weighting
	    phiWgtRaw /= (pt < 2.) ? pt : 2.;
	  }
	  if (oddHar && eta < 0.) phiWgtRaw /= -1.;


	  TVector2 q_i;
	  TVector2 mQ_i=mQ[k][j];
          TVector2 q_i_unit;

          q_i.Set(phiWgt * cos(phi * order), phiWgt * sin(phi * order));



	  // Remove autocorrelations
          if ( (pFlowSelect->SelectPart(pFlowTrack)) && 
               (pFlowSelect->Select(pFlowTrack)) ) 
	     mQ_i = mQ_i - q_i;


          q_i_unit.Set(cos(phi*order),sin(phi*order));

       	// Caculate v for all particles selected for correlation analysis
	if (pFlowSelect->SelectPart(pFlowTrack)) {

	  float v = (mQ_i.X()*q_i_unit.X()+mQ_i.Y()*q_i_unit.Y());
	  float vFlip = v;
	  if (eta < 0 && oddHar) vFlip *= -1;
	  if (strlen(pFlowSelect->PidPart()) != 0) { 
	    float rapidity = pFlowTrack->Y();
	    histFull[k].histFullHar[j].mHist_vObs2D-> Fill(rapidity, pt, v);
	    histFull[k].histFullHar[j].mHist_vObsEta->Fill(rapidity, v);
	  } else {
	    histFull[k].histFullHar[j].mHist_vObs2D-> Fill(eta, pt, v);
	    histFull[k].histFullHar[j].mHist_vObsEta->Fill(eta, v);
	  }
	  histFull[k].histFullHar[j].mHist_vObsPt-> Fill(pt, vFlip);
	  histFull[k].mHist_vObs->Fill(order, vFlip);
	  

	}
      }
    }  
  }

}


//-----------------------------------------------------------------------

Int_t StFlowScalarProdMaker::Finish() {
  // Calculates resolution and mean flow values
  TString* histTitle;

  double content;
  double error;
  double totalError;
  for (int k = 0; k < Flow::nSels; k++) {
    char countSels[2];
    sprintf(countSels,"%d",k+1);
    // Creat the 1D v histogram
    histTitle = new TString("Flow_v_ScalarProd_Sel");
    histTitle->Append(*countSels);
    histFull[k].mHist_v = 
      histFull[k].mHist_vObs->ProjectionX(histTitle->Data());
    histFull[k].mHist_v->SetTitle(histTitle->Data());
    histFull[k].mHist_v->SetXTitle("Harmonic");
    histFull[k].mHist_v->SetYTitle("v (%)");
    delete histTitle;
    AddHist(histFull[k].mHist_v);

    for (int j = 0; j < Flow::nHars; j++) {
      char countHars[2];
      sprintf(countHars,"%d",j+1);

      mRes[k][j] = sqrt(histFull[k].mHistRes->GetBinContent(j+1))*2.*perCent;

      mResErr[k][j] = sqrt(histFull[k].mHistRes->GetBinError(j+1))*2.*perCent; 

	// Creat the v 2D histogram
      histTitle = new TString("Flow_v2D_ScalarProd_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_v2D = 
	histFull[k].histFullHar[j].mHist_vObs2D->ProjectionXY(histTitle->Data());
      histFull[k].histFullHar[j].mHist_v2D->SetTitle(histTitle->Data());
      histFull[k].histFullHar[j].mHist_v2D->SetXTitle((char*)xLabel.Data());
      histFull[k].histFullHar[j].mHist_v2D->SetYTitle("Pt (GeV)");
      histFull[k].histFullHar[j].mHist_v2D->SetZTitle("v (%)");
      delete histTitle;
      AddHist(histFull[k].histFullHar[j].mHist_v2D);

      // Creat the 1D v histograms
      histTitle = new TString("Flow_vEta_ScalarProd_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_vEta = 
	histFull[k].histFullHar[j].mHist_vObsEta->ProjectionX(histTitle->Data());
      histFull[k].histFullHar[j].mHist_vEta->SetTitle(histTitle->Data());
      histFull[k].histFullHar[j].mHist_vEta->SetXTitle((char*)xLabel.Data());
      histFull[k].histFullHar[j].mHist_vEta->SetYTitle("v (%)");
      delete histTitle;
      AddHist(histFull[k].histFullHar[j].mHist_vEta);

      TString* histTitle = new TString("Flow_vPt_ScalarProd_Sel");
      histTitle->Append(*countSels);
      histTitle->Append("_Har");
      histTitle->Append(*countHars);
      histFull[k].histFullHar[j].mHist_vPt = 
	histFull[k].histFullHar[j].mHist_vObsPt->ProjectionX(histTitle->Data());
      histFull[k].histFullHar[j].mHist_vPt->SetTitle(histTitle->Data());
      histFull[k].histFullHar[j].mHist_vPt->SetXTitle("Pt (GeV)");
      histFull[k].histFullHar[j].mHist_vPt->SetYTitle("v (%)");
      delete histTitle;
      AddHist(histFull[k].histFullHar[j].mHist_vPt);

      // Calulate v = vObs / Resolution
      if (mRes[k][j]) {
	cout << "##### Resolution of the " << j+1 << "th harmonic = " << 
	  mRes[k][j] << " +/- " << mResErr[k][j] 
	     << endl;
	// The systematic error of the resolution is not folded in.
	histFull[k].histFullHar[j].mHist_v2D-> Scale(1. / mRes[k][j]);
	histFull[k].histFullHar[j].mHist_vEta->Scale(1. / mRes[k][j]);
	histFull[k].histFullHar[j].mHist_vPt ->Scale(1. / mRes[k][j]);
	content = histFull[k].mHist_v->GetBinContent(j+1);
	content /=  mRes[k][j];
	histFull[k].mHist_v->SetBinContent(j+1, content);
	// The systematic error of the resolution is folded in.
	error = histFull[k].mHist_v->GetBinError(j+1);
	error /= mRes[k][j];
	totalError = fabs(content) * sqrt((error/content)*(error/content) +
	       (mResErr[k][j]/mRes[k][j])*(mResErr[k][j]/mRes[k][j]));
	histFull[k].mHist_v->SetBinError(j+1, totalError);
	cout << "##### v" << j+1 << "= (" << content << " +/- " << error << 
	  " +/- " << totalError << "(with syst.)) %" << endl;
      } else {
	cout << "##### Resolution of the " << j+1 << "th harmonic was zero."
	     << endl;
	histFull[k].histFullHar[j].mHist_v2D-> Reset();
	histFull[k].histFullHar[j].mHist_vEta->Reset();
	histFull[k].histFullHar[j].mHist_vPt ->Reset();
	histFull[k].mHist_v->SetBinContent(j+1, 0.);
	histFull[k].mHist_v->SetBinError(j+1, 0.);
      }
    }
  }
  //GetHistList()->ls();

  // Write all histograms
  TFile histFile("flow.scalar.root", "RECREATE");
  GetHistList()->Write();
  histFile.Close();
  

  // Print the selection object details
  pFlowSelect->PrintList();

  delete pFlowSelect;

  cout << endl;
  gMessMgr->Summary(3);
  cout << endl;

  return StMaker::Finish();
}

////////////////////////////////////////////////////////////////////////////
//
// $Log: StFlowScalarProdMaker.cxx,v $
// Revision 1.2  2001/12/21 17:01:59  aihong
// minor changes
//
// Revision 1.1  2001/12/18 23:46:47  aihong
// install scalar product method
//
//  
////////////////////////////////////////////////////////////////////////////
