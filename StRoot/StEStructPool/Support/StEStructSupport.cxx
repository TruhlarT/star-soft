/**********************************************************************
 *
 * $Id: StEStructSupport.cxx,v 1.18 2008/03/19 22:08:38 prindle Exp $
 *
 * Author: Jeff Porter 
 *
 **********************************************************************
 *
 * Description: Simple helper class for calculating
 *              delta-rho, delta-rho/rho, and delta-rho/sqrt(rho)
 *              plus some other goodies
 *
 ***********************************************************************/
#include "StEStructSupport.h"
#include "StEStructPool/Correlations/StEStructMaxB.h"
#include "Stiostream.h"
#include <sstream>
#include "Stsstream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"


const char* _pair_typename[] = {"Sib","Mix"};
const char* _pair_chargename[]   = {"pp","pm","mp","mm"};
const char* _pair_ptweight[]   = {"Pr","Su"};
int _pair_typemax=2;
int _pair_chargemax=4;
int _pair_totalmax=_pair_typemax*_pair_chargemax;

ClassImp(StEStructSupport)

//---------------------------------------------------------
bool StEStructSupport::goodName(const char* name){

  TString testName(_pair_typename[0]);
  testName+=_pair_chargename[0];
  testName+=name;
  TObject* obj = NULL;
  mtf->GetObject(testName.Data(),obj);
  if(!obj) return false;

  return true;
}
//---------------------------------------------------------
bool StEStructSupport::goodName_zBuf(const char* name, int zBin){

  TString testName(_pair_typename[0]);
  testName+=_pair_chargename[0];
  testName+=name;
  testName+="_zBuf_"; testName += zBin;
  TObject* obj=NULL;
  mtf->GetObject(testName.Data(),obj);
  if(!obj) return false;

  return true;
}

//---------------------------------------------------------
char* StEStructSupport::getFrontName(int itype){

  /* for itype=0-7, returns Sibpp, Sibpm, Sibmp, Sibmm, Mixpp, Mixpm, Mixmp, Mixmm   */

  if(mtmpString) delete [] mtmpString;
  mtmpString=new char[256];
  ostringstream ts;
  int j,k;
  if(itype<_pair_chargemax){
    j=0; k=itype;
  } else {
    j=1; k=itype-_pair_chargemax;
  }

  ts<<_pair_typename[j]<<_pair_chargename[k];
  strcpy(mtmpString,(ts.str()).c_str());
  return mtmpString;
}

//---------------------------------------------------------
const char* StEStructSupport::getTypeName(int itype){ 
  return _pair_typename[itype]; 
}

//---------------------------------------------------------
const char* StEStructSupport::getChargeSignName(int ics){ 
  return _pair_chargename[ics]; 
}

//---------------------------------------------------------
//
//  Now the real class work 
//
//---------------------------------------------------------

StEStructSupport::StEStructSupport(TFile* tf, int bgmode, float* npairs) : mtf(tf), mbgMode(bgmode), mtmpString(NULL){

  //
  // npairs is a normalization for when one cuts on say two (many) different 
  // ytyt slices and wants to compare the amplitudes, the generic normalization
  // of sum of rho = 1. isn't sufficient
  //

  msilent=false;
  mapplyDEtaFix=false; // must set explicitly now
  mDoSymmetrize = false;
  mPairNormalization = false;
  mIdenticalPair = true;

  // Scan file for number of z-buffer bins
  getNZBins();
  
  if(npairs){
    mnpairs = new float[8];
    for(int i=0;i<8;i++)mnpairs[i]=npairs[i];
  } else {
    mnpairs = 0;
  }

}

StEStructSupport::~StEStructSupport(){ 
  if(mtmpString) delete [] mtmpString; 
  if(mnpairs) delete [] mnpairs; 
};

//---------------------------------------------------------
int StEStructSupport::getNZBins(){
    TString hname("NEventsSib_zBuf_");
    int iZBin;
    for (iZBin=1;iZBin<99;iZBin++) {
        TString zBinName(hname.Data());
        zBinName += iZBin-1;
        TH1* tmp = NULL;
        mtf->GetObject(zBinName.Data(),tmp);
        if (!tmp) {
            break;
        }
    }
    mNumZBins = iZBin-1;
    return mNumZBins;
};
//---------------------------------------------------------
// We have been calculating \Delta\rho/rhoin different multiplicity/z bins
// then averaging using the number of pairs as a weight.
// This heavily favors slightly larger multiplicities..
// These get*Number routines are so I can try multiplicity weighting.
//
// Note: We allocate space for four floats, fill in the numbers, then return a pointer to them.
//       Valgrind claims they are being used un-initialized. I think that is an issue
//       with Valgrind. Might be nice to change how we return the numbers to get
//       rid of those warnings.
float *StEStructSupport::getCommonNumber(int zBin) {
    float *number = new float[4];
    TString hname("");
    TH1 *hpt[4];

    hname = "meanPtPA_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[0]);
    hname = "meanPtMA_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[1]);
    hname = "meanPtPB_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[2]);
    hname = "meanPtMB_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[3]);

    // Want pp, pm, mp, mm
    number[0] = hpt[0]->Integral() + hpt[2]->Integral();
    number[1] = hpt[0]->Integral() + hpt[3]->Integral();
    number[2] = hpt[1]->Integral() + hpt[2]->Integral();
    number[3] = hpt[1]->Integral() + hpt[3]->Integral();
    return number;
};
//---------------------------------------------------------
float *StEStructSupport::getCommonPairs(int zBin) {
    float *pairs = new float[4];
    for (int i=0;i<4;i++) {
        pairs[i] = 0;
        TString hname("");
        hname += "Sib";
        hname += _pair_chargename[i];
        hname += "NDEtaDPhi_zBuf_";
        hname += zBin;
        TH1 *tmp = NULL;
        mtf->GetObject(hname.Data(),tmp);
        if (tmp) {
            pairs[i] = tmp->Integral();
        } else {
            pairs[i] = 0;
        }
    }
    return pairs;
};
//---------------------------------------------------------
float *StEStructSupport::getChargeNumber(int zBin) {
    float *number = new float[4];
    TString hname("");
    TH1 *hpt[4];

    hname = "meanPtPA_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[0]);
    hname = "meanPtMA_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[1]);
    hname = "meanPtPB_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[2]);
    hname = "meanPtMB_zBuf_"; hname += zBin;   mtf->GetObject(hname.Data(),hpt[3]);

    // Want LS, US, CI, CD. Turns out to just be grand sum.
    number[0] = hpt[0]->Integral() + hpt[2]->Integral();
    number[0]+= hpt[0]->Integral() + hpt[3]->Integral();
    number[0]+= hpt[1]->Integral() + hpt[2]->Integral();
    number[0]+= hpt[1]->Integral() + hpt[3]->Integral();
    number[1] = number[0];
    number[2]+= number[0];
    number[3] = number[0];
    return number;
};
//---------------------------------------------------------
float *StEStructSupport::getChargePairs(int zBin) {
    float *pairs = new float[4];
    for (int i=0;i<4;i++) {
        pairs[i] = 0;
        TString hname("");
        hname += "Sib";
        hname += _pair_chargename[i];
        hname += "NDEtaDPhi_zBuf_";
        hname += zBin;
        TH1 *tmp = NULL;
        mtf->GetObject(hname.Data(),tmp);
        if (tmp) {
            pairs[i] = tmp->Integral();
        } else {
            pairs[i] = 0;
        }
    }
    pairs[0] += pairs[3];
    pairs[1] += pairs[2];
    pairs[2] = pairs[0] + pairs[1];
    pairs[3] = pairs[0] + pairs[1];
    return pairs;
};

//---------------------------------------------------------
double *StEStructSupport::getd2NdEtadPhi(int zBin) {
    double* retVal = new double[5];
    // (nA+)*(nB+), (nA+)*(nB-), (nA-)*(nB+), (nA-)*(nB-), (nA+)+(nA-)+(nB+)+(nB-)
    // where the () means {d^2() \over d\eta d\phi}
    // Note that in cases where we don't distinguish a and b
    // (nA+)*(nB-) and (nA-)*(nB+) are the same and retVal[2] is not necessary.

    TString hSibName("NEventsSib_zBuf_"); hSibName += zBin;  TH1* hNSum;  mtf->GetObject(hSibName.Data(),hNSum);
    double nEvents = hNSum->Integral();

    double nTracksAP, nTracksAM, nTracksBP, nTracksBM;
    double dNdEtaAP, dNdEtaAM, dNdEtaBP, dNdEtaBM;
    TH1 *hEta;
    TString hname;

    hname = "etaPA_zBuf_";  hname += zBin;  mtf->GetObject(hname.Data(),hEta);  nTracksAP = hEta->Integral();
    hname = "etaMA_zBuf_";  hname += zBin;  mtf->GetObject(hname.Data(),hEta);  nTracksAM = hEta->Integral();
    hname = "etaPB_zBuf_";  hname += zBin;  mtf->GetObject(hname.Data(),hEta);  nTracksBP = hEta->Integral();
    hname = "etaMB_zBuf_";  hname += zBin;  mtf->GetObject(hname.Data(),hEta);  nTracksBM = hEta->Integral();

    // The 0.5 is because we integrate tracks over two units of rapidity.
    dNdEtaAP = 0.5 * nTracksAP / nEvents;
    dNdEtaAM = 0.5 * nTracksAM / nEvents;
    dNdEtaBP = 0.5 * nTracksBP / nEvents;
    dNdEtaBM = 0.5 * nTracksBM / nEvents;
    retVal[0] = dNdEtaAP*dNdEtaBP / pow(2*3.1415926,2);
    retVal[1] = dNdEtaAP*dNdEtaBM / pow(2*3.1415926,2);
    retVal[2] = dNdEtaAM*dNdEtaBP / pow(2*3.1415926,2);
    retVal[3] = dNdEtaAM*dNdEtaBM / pow(2*3.1415926,2);

    // There are factors of 2 when expanding the full correlation term that
    // could be included in loops over pairs, but appear not to have been.
    // Fix that up here.
    if (mIdenticalPair) {
        retVal[1] *= 2;
        retVal[4] = (dNdEtaAP + dNdEtaAM) / (2*3.1415926);
    } else {
        retVal[0] *= 2;
        retVal[2] *= 2;
        retVal[3] *= 2;
        retVal[4] = (dNdEtaAP + dNdEtaAM + dNdEtaBP + dNdEtaBM) / (2*3.1415926);
    }
    return retVal;
}
//---------------------------------------------------------
double *StEStructSupport::getptHat(int zBin) {
    double* retVal = new double[4];
    TH1 *hpt;
    TString hname;

    hname = "meanPtPA_zBuf_"; hname += zBin;  mtf->GetObject(hname.Data(),hpt);  retVal[0] = hpt->GetMean();
    hname = "meanPtMA_zBuf_"; hname += zBin;  mtf->GetObject(hname.Data(),hpt);  retVal[1] = hpt->GetMean();
    hname = "meanPtPB_zBuf_"; hname += zBin;  mtf->GetObject(hname.Data(),hpt);  retVal[2] = hpt->GetMean();
    hname = "meanPtMB_zBuf_"; hname += zBin;  mtf->GetObject(hname.Data(),hpt);  retVal[3] = hpt->GetMean();

    return retVal;
}
//---------------------------------------------------------
TH1** StEStructSupport::getHists(const char* name, int zBin){
  TH1** retVal=NULL;
  // If zBin = 0 check for name without with zBuf first.
  if((0 == zBin) && !goodName(name)) {
      if (!goodName_zBuf(name,zBin)) {
          return retVal;
      }
  }

  retVal=new TH1*[8];
  TH1* tmpF;
  for(int i=0;i<_pair_totalmax;i++){
    TString hname(getFrontName(i));  hname+=name;  mtf->GetObject(hname.Data(),tmpF);
    if (!tmpF) {
        TString hname(getFrontName(i));  hname += name;  hname+= "_zBuf_";  hname+= zBin;
        mtf->GetObject(hname.Data(),tmpF);
    }
    // I think I only need the next line. Why do I need the tedious bin-by-bin copy?
    //   retVal[i] = tmpF;

    TAxis * xa=tmpF->GetXaxis();
    TAxis * ya=tmpF->GetYaxis();

    TH1::AddDirectory(kFALSE);
    if(ya->GetNbins()==1){
      retVal[i]=(TH1*)new TH1D(tmpF->GetName(),tmpF->GetTitle(),
                   xa->GetNbins(),xa->GetXmin(),xa->GetXmax());
    } else {
      retVal[i]=(TH1*)new TH2D(tmpF->GetName(),tmpF->GetTitle(),
                   xa->GetNbins(),xa->GetXmin(),xa->GetXmax(),
                   ya->GetNbins(),ya->GetXmin(),ya->GetXmax());
    }

    for(int ix=1;ix<=xa->GetNbins();ix++){
      for(int iy=1;iy<=ya->GetNbins();iy++){
        retVal[i]->SetBinContent(ix,iy,tmpF->GetBinContent(ix,iy));
        retVal[i]->SetBinError(ix,iy,tmpF->GetBinError(ix,iy));
      }
    }
  }


  return retVal;
}
//---------------------------------------------------------
TH1** StEStructSupport::getLocalClones(const char* name, int zBin){

  TH1** hset=getHists(name,zBin);
  if(!hset) return (TH1**)NULL;

  // make local clones
  TH1** hlocal=new TH1*[_pair_totalmax];
  for(int i=0;i<_pair_totalmax;i++) {
    hlocal[i]=(TH1*)hset[i]->Clone();
    delete hset[i];
//    hlocal[i]->Sumw2();  // trigger error propogation
  }
  delete [] hset;

  return hlocal;
}
//-----------------------------------------------------
void StEStructSupport::rescale(TH1** hists, int zBin) {
    // Divide hists by bin widths, divide by Nevents.

    if(!mtf) return;

    //>>>>>Need to rethink how to handle old cases where _zBuf_n is not in histogram name!!!!!
    TH1 *hNum;
    TString hSibName("NEventsSib_zBuf_");  hSibName += zBin;  mtf->GetObject(hSibName.Data(),hNum);
    double nSib = hNum->Integral();
    TString hMixName("NEventsMix_zBuf_");  hMixName += zBin;  mtf->GetObject(hMixName.Data(),hNum);
    double nMix = hNum->Integral();

    for(int i=0;i<4;i++){
        if(hists[i]->Integral() > 0) {
            double dx = (hists[i]->GetXaxis())->GetBinWidth(1);
            double dy = (hists[i]->GetYaxis())->GetBinWidth(1);
            double binFactor = dx*dy; 
            // dividing by ex*ey converts all input hists from counts to densities, so all operations and final result should also be density.
            if (i==0 && !msilent) {
                cout << "Scaling with Nevents " << nSib << " and binFactor " << binFactor << endl;
            }
            hists[i]->Scale(1.0/(nSib*binFactor));

            if (mPairNormalization) {
                double nSibPairs = hists[i]->Integral();
                double nMixPairs = hists[i+4]->Integral();
                if (nMixPairs > 0) {
                    hists[i+4]->Scale(nSibPairs/nMixPairs);
                } else {
                    hists[i+4]->Scale(0);
                }
            } else {
                if (nMix > 0) {
                    hists[i+4]->Scale(0.5/(nMix*binFactor));
                } else {
                    hists[i+4]->Scale(0);
                }
            }
        }
    }
};

//---------------------------------------------------------
TH1** StEStructSupport::getPtHists(const char* name, int zBin){

  TH1** retVal=NULL;
  // If zBin = 0 check for name without with zBuf first.
  if((0 == zBin) && !goodName(name)) {
      if (!goodName_zBuf(name,zBin)) {
          return retVal;
      }
  }
  
  retVal=new TH1*[32];

  for(int i=0;i<_pair_totalmax;i++){
    TString hname(getFrontName(i)),hprname(getFrontName(i)),hpaname(getFrontName(i)),hpbname(getFrontName(i));
                   hname+=name;   hname+="_zBuf_";   hname+=zBin;
    hprname+="Pr"; hprname+=name; hprname+="_zBuf_"; hprname+=zBin;
    hpaname+="Pa"; hpaname+=name; hpaname+="_zBuf_"; hpaname+=zBin;
    hpbname+="Pb"; hpbname+=name; hpbname+="_zBuf_"; hpbname+=zBin;
    mtf->GetObject(hname.Data(),retVal[i]);
    mtf->GetObject(hprname.Data(),retVal[i+8]);
    mtf->GetObject(hpaname.Data(),retVal[i+16]);
    mtf->GetObject(hpbname.Data(),retVal[i+24]);
  }

  return retVal;
}
//---------------------------------------------------------------
TH1** StEStructSupport::getPtClones(const char* name, int zBin){

  // hset contains pointers to in-memory histograms, _not_ copies.
  TH1** hset=getPtHists(name,zBin);
  if(!hset) return (TH1**)NULL;

  // make local clones
  TH1** hlocal=new TH1*[_pair_totalmax*4];
  for(int i=0;i<_pair_totalmax*4;i++) {
    hlocal[i]=(TH1*)hset[i]->Clone();
//    hlocal[i]->Sumw2();  // trigger error propogation
  }
  // Delete array containing pointers, but not objects being pointed to.
  delete [] hset;

  return hlocal;
}
//-----------------------------------------------------
void StEStructSupport::rescalePt(TH1** hists, int zBin) {
    // Divide hists by bin widths, divide by Nevents.

    if(!mtf) return;

    TH1 *hNum;
    TString hSibName("NEventsSib_zBuf_");  hSibName += zBin;  mtf->GetObject(hSibName.Data(),hNum);
    double nSib = hNum->GetEntries();
    TString hMixName("NEventsMix_zBuf_");  hMixName += zBin;  mtf->GetObject(hMixName.Data(),hNum);
    double nMix = hNum->GetEntries();

    for(int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            if (hists[i+4*j]->Integral() > 0) {
                double binFactor = 1.0;
                double dx = (hists[i+8*j]->GetXaxis())->GetBinWidth(1);
                double dy = (hists[i+8*j]->GetYaxis())->GetBinWidth(1);
                binFactor = dx*dy;
                // divinding by ex*ey converts all input hists from counts to densities, so all operations and final result should also be density.
                if(i==0 && !msilent) cout << "Scaling with Nevents " << nSib << " and binFactor " << binFactor << endl;
                hists[i+8*j]->Scale(1.0/(nSib*binFactor));

                double nSibPairs = hists[i+8*j]->Integral();
                double nMixPairs = hists[i+4+8*j]->Integral();
                if (mPairNormalization) {
                    if (nMixPairs > 0) {
                        hists[i+4+8*j]->Scale(nSibPairs/nMixPairs);
                    } else {
                        hists[i+4+8*j]->Scale(0);
                    }
                } else {
                    if (nMix > 0) {
                        hists[i+4+8*j]->Scale(0.5/(nMix*binFactor));
                    } else {
                        hists[i+4+8*j]->Scale(0);
                    }
                }
            }
        }
    }
};

//-----------------------------------------------------
void StEStructSupport::setSymmetrizeUS(bool symm) {
    mDoSymmetrize = symm;
}
//-----------------------------------------------------
void StEStructSupport::symmetrizeUS(const char *name, TH1** histos) {
  // For pid mode the US X vs X and LS but different species histograms are not symmetrized.
  // To form CD and CI combos we need the US to be symmetrized in the cases the LS are.

  // Histograms to be symmetrized are:
  char *symHistos[] = {"YtYt",   "NYtYt",   "PtPt",
                       "PhiPhi", "NPhiPhi", "PrPhiPhi", "PaPhiPhi", "PbPhiPhi",
                       "EtaEta",            "PrEtaEta", "PaEtaEta", "PbEtaEta"};
  // eight input histograms ++,+-,-+,-- for Sib and Mix
  int symInt[] = {1,2, 5, 6};
  for (int xy=0;xy<12;xy++) {
      if (!strcmp(name,symHistos[xy])) {
          for (int ih=0;ih<4;ih++) {
              for (int ix=1;ix<=histos[symInt[ih]]->GetNbinsX();ix++) {
                  for (int iy=ix;iy<=histos[symInt[ih]]->GetNbinsY();iy++) {
                      double sum = histos[symInt[ih]]->GetBinContent(ix,iy) + histos[symInt[ih]]->GetBinContent(iy,ix);
                      histos[symInt[ih]]->SetBinContent(ix,iy,sum);
                      histos[symInt[ih]]->SetBinContent(iy,ix,sum);
                  }
              }
          }
      }
  }
};
//-----------------------------------------------------
void StEStructSupport::symmetrizePtUS(const char *name, TH1** histos) {
  // For pid mode the US X vs X and LS but different species histograms are not symmetrized.
  // To form CD and CI combos we need the US to be symmetrized in the cases the LS are.

  // Histograms to be symmetrized are:
  char *symHistos[] = {"YtYt",   "NYtYt",   "PtPt",
                       "PhiPhi", "NPhiPhi", "PrPhiPhi", "PaPhiPhi", "PbPhiPhi",
                       "EtaEta",            "PrEtaEta", "PaEtaEta", "PbEtaEta"};
  int symInt[] = {1,2, 5, 6};
  //    4 groups of 8 (Sibpp,Sibpm,Sibmp,Sibmm,Mixpp,Mixpm,Mixmp,Mixmm) 
  //    1st 8 are number, 2nd 8 are pt1*pt2, 3rd 8 are pt1 and 4th 8 are pt2
  for (int xy=0;xy<12;xy++) {
      if (!strcmp(name,symHistos[xy])) {
          for (int ig=0;ig<32;ig+=8) {
              for (int ih=0;ih<4;ih++) {
                  int histNum = ig + symInt[ih];
                  for (int ix=1;ix<=histos[histNum]->GetNbinsX();ix++) {
                      for (int iy=ix;iy<=histos[histNum]->GetNbinsY();iy++) {
                          double sum = histos[histNum]->GetBinContent(ix,iy) + histos[histNum]->GetBinContent(iy,ix);
                          histos[histNum]->SetBinContent(ix,iy,sum);
                          histos[histNum]->SetBinContent(iy,ix,sum);
                      }
                  }
              }
          }
      }
  }
};

//-----------------------------------------------------
float* StEStructSupport::getNorms(TH1** histArray){

  /* not really used any more but keep */

  float* retVal=NULL;
  if(!histArray) return retVal;

  retVal=new float[8];
  for(int i=0;i<_pair_totalmax; i++) retVal[i]=histArray[i]->Integral();

  return retVal;
}

//---------------------------------------------------------
TH1** StEStructSupport::buildCommonRatios(const char* name){
  return buildCommon(name,0);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildCommonCFunctions(const char* name){
  return buildCommon(name,1);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildCommonRFunctions(const char* name){
  return buildCommon(name,2);
}

//---------------------------------------------------------
TH1** StEStructSupport::buildCommonRatios(const char* name, int zBin){
  return buildCommon(name,0,zBin);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildCommonCFunctions(const char* name, int zBin){
  return buildCommon(name,1,zBin);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildCommonRFunctions(const char* name, int zBin){
  return buildCommon(name,2,zBin);
}
//---------------------------------------------------------
// Note for all buildXXX functions:
//  We have three basic quantities, \rho_{sib}, \rho_{ref} and {d^2N \over d\eta d\phi}
//  We use {d^2N \over d\eta d\phi}^2 as a proxy for \rho_{ref} in cases where we want
//  an acceptance/efficiency independent number. (Ok, there is still an average
//  efficiency that we have to divide by.)
//  When combining z-bins and/or centralities we want to add \Delta\rho, but
//  each bin has a different efficiency correction. To account for this we define
//   \hat\Delta\rho = {d^2N \over d\eta d\phi}^2 * \Delta\rho / \rho_{ref}.
//   This takes role of \Delta\rho when we combine multiple bins.
//  Option 0) \Delta\rho/\rho_{ref}       -> \Sum_1^n{\hat\Delta\rho} / {(1/n) \Sum_1^n{dN/d\eta}}^2
//         1) \Delta\rho                  -> \hat\Delta\rho
//         2) \Delta\rho/sqrt(\rho_{ref}) -> \Sum_1^n{\hat\Delta\rho} / {(1/n) \Sum_1^n{dN/d\eta}}

// Common ->  {"PP","PM","MP","MM"};
TH1** StEStructSupport::buildCommon(const char* name, int opt) {
    double *d2NdEtadPhi = getd2NdEtadPhi(0);
    double dNdEtadPhi = d2NdEtadPhi[4];
    TH1** retVal= buildCommon(name, opt, 0);
    for (int iType=0;iType<4;iType++) {
        retVal[iType]->Scale(d2NdEtadPhi[iType]);
    }
    delete [] d2NdEtadPhi;

    for (int iz=1;iz<mNumZBins;iz++) {
        d2NdEtadPhi = getd2NdEtadPhi(iz);
        dNdEtadPhi += d2NdEtadPhi[4];
        TH1** tmpVal= buildCommon(name, opt, iz);
        for (int iType=0;iType<4;iType++) {
            retVal[iType]->Add(tmpVal[iType],d2NdEtadPhi[iType]);
            delete tmpVal[iType];
        }
        delete [] tmpVal;
        delete [] d2NdEtadPhi;
    }
    double sqrtRho = dNdEtadPhi / mNumZBins;
    for (int iType=0;iType<4;iType++) {
        if (0 < sqrtRho) {
            // Note: I can imagine cases where a bin is empty (or nearly so) so it should
            //       not count. Currently rely on some other QA to catch.
            retVal[iType]->Scale(1.0/mNumZBins);
            if (0 == opt) {
                retVal[iType]->Scale(1.0/pow(sqrtRho,2));
            } else if (2 == opt) {
                retVal[iType]->Scale(1.0/sqrtRho);
            }
        } else {
            retVal[iType]->Scale(0.0);
        }
    }
    return retVal;
}

//---------------------------------------------------------
// Note that I (djp) modified the analysis code so that we only fill the -+
// histograms for identified, different particles. So we get -+ filled for
// pi-K+ as an example but not for unidentified particles (as in mode 1
// and mode 3) where we don't know what the particle types are.

// Ignore opt here, only use it for over-loading distinction.
// Always return \Delta\rho/rho_{ref}
TH1** StEStructSupport::buildCommon(const char* name, int opt, int zBin) {

    /* builds hist types = ++,+-,-+,-- */


    // eight input histograms ++,+-,-+,-- for Sib and Mix 
    TH1** hlocal = getLocalClones(name, zBin);
    if (!hlocal) {
        return hlocal;
    }

    rescale(hlocal, zBin);  // Divide out bin size, number of events to approximate density.
                            // Optionally scale number of mix pairs to be same as sibling.
    if (strstr(name,"DEta") || strstr(name,"SEta")) {
        fixDEta((TH2**)hlocal,8); // does nothing unless mapplyDEtaFix is set
    }

    // four returned hists. Make them the right size with reasonable titles.
    TH1** retVal= new TH1*[4]; // 0=++ 1=+- 2=-+ 3=--
    const char* nm[4]  = {"PP","PM","MP","MM"};
    const char* tit[4] = {"PP : ++","PM : +-","MP: -+","MM : --"};
    for(int i=0;i<4;i++) {
        retVal[i]=(TH1*)hlocal[0]->Clone();// just get correct dimensions & names
        retVal[i]->SetName(swapIn(hlocal[0]->GetName(),"Sibpp",nm[i]));
        retVal[i]->SetTitle(swapIn(hlocal[0]->GetTitle(),"Sibling : +.+",tit[i]));
        retVal[i]->Scale(0.); // zero the hists
    }

    // \Delta\rho/\rho_{ref}
    for (int i=0;i<4;i++) {
        retVal[i]->Add(hlocal[i],hlocal[i+4],1.0,-1.0); // delta rho
        retVal[i]->Divide(hlocal[i+4]);                 // delta-rho/rho_{ref}
    }

    // Free memory of hlocal.
    for (int i=0;i<_pair_totalmax;i++) {
        delete hlocal[i];
    }
    delete [] hlocal;

    return retVal;
}
//---------------------------------------------------------
// When we have imposed some type of pt cuts we may have introduced
// a covariance which will show up here. Subtract mixed pairs
// to reduce this contribution.

// opt: 0 = delta-rho/rho_mix;  1 = delta-rho;  2 = delta-rho/sqrt(rho_mix);
TH1** StEStructSupport::buildPtCommon(const char* name, int opt, int subtract) {
    double *d2NdEtadPhi = getd2NdEtadPhi(0);
    double dNdEtadPhi = d2NdEtadPhi[4];
    TH1** retVal= buildPtCommon(name, opt, subtract, 0);
    for (int iType=0;iType<4;iType++) {
        retVal[iType]->Scale(d2NdEtadPhi[iType]);
    }
    delete [] d2NdEtadPhi;

    for (int iz=1;iz<mNumZBins;iz++) {
        d2NdEtadPhi = getd2NdEtadPhi(iz);
        dNdEtadPhi += d2NdEtadPhi[4];
        TH1** tmpVal= buildPtCommon(name, opt, subtract, iz);
        for (int iType=0;iType<4;iType++) {
            retVal[iType]->Add(tmpVal[iType],d2NdEtadPhi[iType]);
            delete tmpVal[iType];
        }
        delete [] tmpVal;
        delete [] d2NdEtadPhi;
    }

    double sqrtRho = dNdEtadPhi/mNumZBins;
    for (int iType=0;iType<4;iType++) {
        if (0 < sqrtRho) {
            retVal[iType]->Scale(1.0/mNumZBins);
            if (0 == opt) {
                retVal[iType]->Scale(1.0/pow(sqrtRho,2));
            } else if (2 == opt) {
                retVal[iType]->Scale(1.0/sqrtRho);
            }
        } else {
            retVal[iType]->Scale(0.0);
        }
    }
    return retVal;
}
//---------------------------------------------------------
TH1** StEStructSupport::buildPtCommon(const char* name, int opt, int subtract, int zBin) {

  /* builds hist types = ++,+-,-+,-- */

    if(!mtf) return (TH1**)NULL;

    // -- here we get 32 hists: 
    //    4 groups of 8 (Sibpp,Sibpm,Sibmp,Sibmm,Mixpp,Mixpm,Mixmp,Mixmm)
    //    1st 8 are number, 2nd 8 are pt1*pt2, 3rd are pt1 and 4th are pt2

    TH1** hlocal=getPtClones(name,zBin);
    rescalePt(hlocal, zBin);  // Divide out bin size, number of events to approximate density.
                              // Optionally scale number of mix pairs to be same as sibling.

    // four returned hists
    TH1** retVal= new TH1*[4]; // 0=++ 1=+- 2=-+ 3=--
    TH1** mixVal= new TH1*[4]; // 0=++ 1=+- 2=-+ 3=--
    const char* nm[4]={"PP","PM","MP","MM"};
    const char* tit[4]={"PP : ++","PM : +-","MP: -+","MM : --"};
    for (int i=0;i<4;i++) {
        retVal[i]=(TH1*)hlocal[0]->Clone();// just get correct dimensions & names
        retVal[i]->SetName(swapIn(hlocal[0]->GetName(),"Sibpp",nm[i]));
        retVal[i]->SetTitle(swapIn(hlocal[0]->GetTitle(),"Sibling : +.+",tit[i]));
        retVal[i]->Scale(0.); // zero the hists

        mixVal[i]=(TH1*)hlocal[0]->Clone();
        mixVal[i]->Scale(0.); // zero the hists 
    }

    if(strstr(name,"DEta") || strstr(name,"SEta")) {
        fixDEta((TH2**)hlocal,32);
    }
    double *ptHat = getptHat(zBin);
    double ptHatA[4], ptHatB[4];
    ptHatA[0] = ptHat[0];
    ptHatA[1] = ptHat[0];
    ptHatA[2] = ptHat[1];
    ptHatA[3] = ptHat[1];
    ptHatB[0] = ptHat[2];
    ptHatB[1] = ptHat[2];
    ptHatB[2] = ptHat[3];
    ptHatB[3] = ptHat[3];
    delete [] ptHat;
    for (int i=0;i<4;i++) {  // Note that i=0->3 is ++, +-, -+, --
        retVal[i]->Add(hlocal[i+ 8]);
        retVal[i]->Add(hlocal[i+16],-ptHatB[i]);
        retVal[i]->Add(hlocal[i+24],-ptHatA[i]);
        retVal[i]->Add(hlocal[i   ],ptHatA[i]*ptHatB[i]);

        mixVal[i]->Add(hlocal[i+12]);
        mixVal[i]->Add(hlocal[i+20],-ptHatB[i]);
        mixVal[i]->Add(hlocal[i+28],-ptHatA[i]);
        mixVal[i]->Add(hlocal[i+ 4],ptHatA[i]*ptHatB[i]);
    }

    for (int i=0;i<4;i++) {
        retVal[i]->Divide(hlocal[i]);
        mixVal[i]->Divide(hlocal[i+4]);
        if (subtract) {
            retVal[i]->Add(mixVal[i],-1);  // Subtract mixed event artifacts
        }
    }



    // Free local histograms.
    for (int i=1;i<4;i++) {
        delete mixVal[i];
    }
    for(int i=0;i<_pair_totalmax*4;i++) {
        delete hlocal[i];
    }
    delete [] mixVal;
    delete [] hlocal;

    return retVal;
}

//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeRatios(const char* name){
  return buildChargeTypes(name,0);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeCFunctions(const char* name){
  return buildChargeTypes(name,1);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeRFunctions(const char* name){
  return buildChargeTypes(name,2);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeRatios(const char* name, int zBin){
  return buildChargeTypes(name,0);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeCFunctions(const char* name, int zBin){
  return buildChargeTypes(name,1);
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypeRFunctions(const char* name, int zBin){
  return buildChargeTypes(name,2);
}
//---------------------------------------------------------
// See comments before buildCommon about d2NdEtadPhi being turned into proxy for \rho_{ref}
// ChargeTypes ->  {"LS","US","CD","CI"}
// For opt=0 calculate \Delta\rho / rho_ref
//         1           \Delta\rho
//         2           \Delta\rh0 / sqrt(rho_ref)
TH1** StEStructSupport::buildChargeTypes(const char* name, int opt, float *sf){
    // Scale ++, +-, -+ and -- by their respective {d^2N \over d\eta d\phi}^2 to create
    // \Delta\rho. Scale by appropriate amount of {d^2N \over d\eta d\phi} for opt.
    // Finally add together to form LS, US, CD and CI.
    double *d2NdEtadPhi = getd2NdEtadPhi(0);
    double dNdEtadPhi = d2NdEtadPhi[4];
    TH1** retVal= buildChargeTypes(name, opt, sf, 0);
    for (int iType=0;iType<4;iType++) {
        retVal[iType]->Scale(d2NdEtadPhi[iType]);
    }
    delete [] d2NdEtadPhi;

    for (int iz=1;iz<mNumZBins;iz++) {
        d2NdEtadPhi = getd2NdEtadPhi(iz);
        dNdEtadPhi += d2NdEtadPhi[4];
        TH1** tmpVal= buildChargeTypes(name, opt, sf, iz);
        for (int iType=0;iType<4;iType++) {
            retVal[iType]->Add(tmpVal[iType],d2NdEtadPhi[iType]);
            delete tmpVal[iType];
        }
        delete [] tmpVal;
        delete [] d2NdEtadPhi;
    }
    // Scale according to opt.
    double sqrtRho = dNdEtadPhi/mNumZBins;
    for (int iType=0;iType<4;iType++) {
        if (0 < sqrtRho) {
            retVal[iType]->Scale(1.0/mNumZBins);
            if (0 == opt) {
                retVal[iType]->Scale(1.0/pow(sqrtRho,2));
            } else if (2 == opt) {
                retVal[iType]->Scale(1.0/sqrtRho);
            }
        } else {
            retVal[iType]->Scale(0.0);
        }
    }

    // Now form LS, US, CD and CI
    retVal[0]->Add(retVal[3]);
    retVal[1]->Add(retVal[2]);
    retVal[2]->Add(retVal[0],retVal[1],1,-1);
    retVal[3]->Add(retVal[0],retVal[1]);

    return retVal;
}

//---------------------------------------------------------
// This routine always returns \Delta\rho/\rho_{ref}
TH1** StEStructSupport::buildChargeTypes(const char* name, int opt, float* sf, int zBin){

    // build hist types = LS, US, CD, CI

    TH1** retVal = getLocalClones(name, zBin);
    if(!retVal) {
        return retVal;
    }
    if (mDoSymmetrize) {
        symmetrizeUS(name,retVal);
    }

    if (mnpairs) {  // manual scaling
        for(int i=0;i<8;i++) {
            retVal[i]->Scale(1.0/mnpairs[i]);
        }
    } else {
        rescale(retVal, zBin);  // Divide out bin size, number of events to approximate density.
                                // Optionally scale number of mix pairs to be same as sibling.
    }
    if (strstr(name,"DEta") || strstr(name,"SEta")) {
        fixDEta((TH2**)retVal,8); // does nothing unless mapplyDEtaFix is set
    }

    // four returned hists
    const char* nm[4]={"LS","US","CD","CI"};
    const char* tit[4]={"LS : ++ + --","US : +- + -+","CD: ++ + -- - +- - -+","CI : ++ + -- + +- + -+"};
    for(int i=0;i<4;i++) {
        retVal[i]->SetName(swapIn(retVal[0]->GetName(),"Sibpp",nm[i]));
        retVal[i]->SetTitle(swapIn(retVal[0]->GetTitle(),"Sibling : +.+",tit[i]));
    }

    float scf1=0.;
    float scf2=0.;
    if (sf) {
        scf1=sf[0];
        scf2=sf[1];
    }
    // if requested, scale bg to require correlations>=0 where statistics are large
    // This is important for Yt-Yt correlations. When we return to study those we
    // better double check this stuff is reasonable.
    if (1==mbgMode) {
        scaleBackGround(retVal[0],retVal[4],scf1);
        scaleBackGround(retVal[1],retVal[5],scf2);
        scaleBackGround(retVal[2],retVal[6],scf2);
        scaleBackGround(retVal[3],retVal[7],scf1);
//        if (opt==3) {
//            scaleBackGround(retVal[2],retVal[6]);
//        }
    }

    for(int i=0;i<4;i++){
        retVal[i]->Add(retVal[i+4],-1);
        retVal[i]->Divide(retVal[i+4]);
    }
    return retVal;
}

//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypesSumOfRatios(const char* name, int opt, float *sf){
    TH1** retVal= buildChargeTypesSumOfRatios(name, opt, sf, 0);
    float *nPairs = getChargeNumber(0);
    for (int iType=0;iType<4;iType++) {
        retVal[iType]->Scale(nPairs[iType]);

    }
    for (int iz=1;iz<mNumZBins;iz++) {
        TH1** tmpVal= buildChargeTypesSumOfRatios(name, opt, sf, iz);
        float *tempPairs = getChargeNumber(iz);
        for (int iType=0;iType<4;iType++) {
            retVal[iType]->Add(tmpVal[iType],tempPairs[iType]);
            nPairs[iType]+=tempPairs[iType];
            delete tmpVal[iType];
        }
        delete [] tmpVal;
        delete [] tempPairs;
    }
    for (int iType=0;iType<4;iType++) {
        if (nPairs[iType]) {
            retVal[iType]->Scale(1.0/nPairs[iType]);
        } else {
            retVal[iType]->Scale(0.0);
        }
    }
    delete [] nPairs;
    return retVal;
}
//---------------------------------------------------------
TH1** StEStructSupport::buildChargeTypesSumOfRatios(const char* name, int opt, float* sf, int zBin){
  // finds LS and US same as buildChargeTypes, but here CI and CD are sums of ratios

  // build hist types = LS, US, CD, CI
  // eight input histograms ++,+-,-+,-- for Sib and Mix
  TH1** hlocal=getLocalClones(name,zBin);
  if(!hlocal) return hlocal;

  if(mnpairs){  // manual scaling
    for(int i=0;i<8;i++) hlocal[i]->Scale(1.0/mnpairs[i]);
  } else rescale(hlocal,zBin);  // automatic scaling, norm sib to pairs per event, norm mix to sib

  if(strstr(name,"DEta") || strstr(name,"SEta"))fixDEta((TH2**)hlocal,8); // does nothing unless mapplyDEtaFix is set

  // four returned hists
  TH1** retVal= new TH1*[4]; // 0=LS 1=US 2=CD=LS-US 3=CI=LS+US
  const char* nm[4]={"LS","US","CD","CI"};
  const char* tit[4]={"LS : ++ + --","US : +- + -+","CD: ++ + -- - +- - -+","CI : ++ + -- + +- + -+"};
  for(int i=0;i<4;i++){
    retVal[i]=(TH1*)hlocal[0]->Clone();
    retVal[i]->SetName(swapIn(hlocal[0]->GetName(),"Sibpp",nm[i]));
    retVal[i]->SetTitle(swapIn(hlocal[0]->GetTitle(),"Sibling : +.+",tit[i]));
    retVal[i]->Scale(0.); // zero the hists
  }

  hlocal[0]->Add(hlocal[3]);                // ++ + -- Sib
  if(hlocal[2]) hlocal[1]->Add(hlocal[2]);  // +- + -+ Sib, backward compatible
  hlocal[4]->Add(hlocal[7]);                // ++ + -- Mix
  if(hlocal[6]) hlocal[5]->Add(hlocal[6]);  // +- + -+ Mix

  float scf1=0.;
  float scf2=0.;
  if(sf){
    scf1=sf[0];
    scf2=sf[1];
  }
  // if requested, scale bg to require correlations>=0 where statistics are large
  if(1==mbgMode){
    scaleBackGround(hlocal[0],hlocal[4],scf1);
    scaleBackGround(hlocal[1],hlocal[5],scf2);
    if(opt==3)scaleBackGround(hlocal[3],hlocal[7]);
  }

  retVal[0]->Add(hlocal[0]);  // LS sib
  retVal[1]->Add(hlocal[1]);  // US sib

  // opt: 0 = delta-rho/rho_mix;  1 = delta-rho;  2 = delta-rho/sqrt(rho_mix)

  for(int i=0;i<2;i++){  // loop over LS and US
    retVal[i]->Add(hlocal[i+4],-1.0);  // delta-rho
  }
  retVal[2]->Add(retVal[0],retVal[1],1.,-1.);  // CD sib
  retVal[3]->Add(retVal[0],retVal[1],1.,1.);   // CI sib

  if(opt!=1) {  // retVal has LS, US, CD, CI sib; use hlocal to take ratios
    hlocal[6]->Add(hlocal[4], hlocal[5]);
    hlocal[7]->Add(hlocal[4], hlocal[5]);  // hlocal[4] starts mix for denominators

    for(int i=0;i<4;i++) {  //2
      retVal[i]->Divide(hlocal[i+4]);  // delta-rho/rho_mix
      // NOTE: now CI = (LS_sib + US_sib) / (LS_mix + US_mix), not sum of ratios

      if(opt>=2){    // dN/d\eta * (delta-rho/rho_mix)
        TString hSibName("NEventsSib_zBuf_"); hSibName += zBin;
        TH1 *hNum;  mtf->GetObject(hSibName.Data(),hNum);
        double dNdeta = hNum->GetMean()/2;
        retVal[i]->Scale(dNdeta/(2*3.1415926));
      }
    }
  }

  // Free local histograms.
  for(int i=0;i<_pair_totalmax;i++) {
    delete hlocal[i];
  }
  delete hlocal;

  return retVal;
}
//---------------------------------------------------------
// When we have imposed some type of pt cuts we may have introduced
// a covariance which will show up here. Subtract mixed pairs
// to reduce this contribution.
TH1** StEStructSupport::buildPtChargeTypes(const char* name, int opt, int subtract){
    // See comments in buildChargeTypes.
    double *d2NdEtadPhi = getd2NdEtadPhi(0);
    double dNdEtadPhi = d2NdEtadPhi[4];
    TH1** retVal= buildPtChargeTypes(name, opt, subtract, 0);
    for (int iType=0;iType<4;iType++) {
        retVal[iType]->Scale(d2NdEtadPhi[iType]);
    }
    delete [] d2NdEtadPhi;

    for (int iz=1;iz<mNumZBins;iz++) {
        d2NdEtadPhi = getd2NdEtadPhi(iz);
        dNdEtadPhi += d2NdEtadPhi[4];
        TH1** tmpVal= buildPtChargeTypes(name, opt, subtract, iz);
        for (int iType=0;iType<4;iType++) {
            retVal[iType]->Add(tmpVal[iType],d2NdEtadPhi[iType]);
            delete tmpVal[iType];
        }
        delete [] tmpVal;
        delete [] d2NdEtadPhi;
    }

    double sqrtRho = dNdEtadPhi/mNumZBins;
    for (int iType=0;iType<4;iType++) {
        if (0 < sqrtRho) {
            retVal[iType]->Scale(1.0/mNumZBins);
            if (0 == opt) {
                retVal[iType]->Scale(1.0/pow(sqrtRho,2));
            } else if (2 == opt) {
                retVal[iType]->Scale(1.0/sqrtRho);
            }
        } else {
            retVal[iType]->Scale(0.0);
        }
    }

    retVal[0]->Add(retVal[3]);
    retVal[1]->Add(retVal[2]);
    retVal[2]->Add(retVal[0],retVal[1],1,-1);
    retVal[3]->Add(retVal[0],retVal[1]);
    return retVal;
}
//---------------------------------------------------------
// This routine always returns \Delta\rho/\rho_{ref}
TH1** StEStructSupport::buildPtChargeTypes(const char* name, int opt, int subtract, int zBin) {

    if(!mtf) return (TH1**)NULL;

    // -- here we get 32 hists: 
    //    4 groups of 8 (Sibpp,Sibpm,Sibmp,Sibmm,Mixpp,Mixpm,Mixmp,Mixmm) 
    //    1st 8 are number, 2nd 8 are pt1*pt2, 3rd 8 are pt1 and 4th 8 are pt2

    TH1** hlocal = getPtClones(name,zBin);
    if(!hlocal) return hlocal;
    if (mDoSymmetrize) {
        symmetrizePtUS(name,hlocal);
    }
    rescalePt(hlocal,zBin);  // Divide out bin size, number of events to approximate density.
                             // Optionally scale number of mix pairs to be same as sibling.

    // four returned hists
    TH1** retVal= new TH1*[4]; // 0=LS 1=US 2=CD=LS-US 3=CI=LS+US
    const char* nm[4]={"LS","US","CD","CI"};
    const char* tit[4]={"LS : ++ + --","US : +- + -+","CD: ++ + -- - +- - -+","CI : ++ + -- + +- + -+"};
    TH1* mixVal[4]; // ++,+-,-+,--
    for(int i=0;i<4;i++){
        retVal[i] = (TH1*) hlocal[0]->Clone();
        retVal[i]->SetName(swapIn(hlocal[0]->GetName(),"Sibpp",nm[i]));
        retVal[i]->SetTitle(swapIn(hlocal[0]->GetTitle(),"Sibling : +.+",tit[i]));
        retVal[i]->Scale(0.); // zero the hists
        mixVal[i] = (TH1*) hlocal[0]->Clone();
        mixVal[i]->Scale(0.); // zero the hists 
    }

//>>>> Want to form \Delta\rho/\rho^2 for ++, +-, -+ and --.
//     Subtract mixed from sibling for these.
//     Then form LS and US.
//     Finally, form CI and CD.

    if(strstr(name,"DEta") || strstr(name,"SEta")) {
        fixDEta((TH2**)hlocal,32);
    }
    double *ptHat = getptHat(zBin);
    double ptHatA[4], ptHatB[4];
    ptHatA[0] = ptHat[0];
    ptHatA[1] = ptHat[0];
    ptHatA[2] = ptHat[1];
    ptHatA[3] = ptHat[1];
    ptHatB[0] = ptHat[2];
    ptHatB[1] = ptHat[2];
    ptHatB[2] = ptHat[3];
    ptHatB[3] = ptHat[3];
    delete [] ptHat;
    for(int i=0;i<4;i++){
        retVal[i]->Add(hlocal[i+ 8]);
        mixVal[i]->Add(hlocal[i+12]);
        retVal[i]->Add(hlocal[i+16],-ptHatB[i]);
        mixVal[i]->Add(hlocal[i+20],-ptHatB[i]);
        retVal[i]->Add(hlocal[i+24],-ptHatA[i]);
        mixVal[i]->Add(hlocal[i+28],-ptHatA[i]);
        retVal[i]->Add(hlocal[i   ],ptHatA[i]*ptHatB[i]);
        mixVal[i]->Add(hlocal[i+ 4],ptHatA[i]*ptHatB[i]);
    }

    for (int i=0;i<4;i++) {
        retVal[i]->Divide(hlocal[i]);
        mixVal[i]->Divide(hlocal[i+4]);
        if (subtract) {
            retVal[i]->Add(mixVal[i],-1);  // Subtract mixed event artifacts
        }
    }

    // Free local histograms.
    for (int i=1;i<4;i++) {
        delete mixVal[i];
    }
    for(int i=0;i<_pair_totalmax*4;i++) {
        delete hlocal[i];
    }
    delete [] hlocal;

    return retVal;

}

//---------------------------------------------------------
void StEStructSupport::scaleBackGround(TH1* sib, TH1* mix, float sf) {
    float alpha=1.0;
    if (sf!=0.) {
        alpha=sf;
    } else {
        float hmax = mix->GetMaximum();
        for (int ix=1;ix<=mix->GetNbinsX();ix++) {
            for(int iy=1;iy<=mix->GetNbinsY();iy++) {
                float mval = mix->GetBinContent(ix,iy);
                if (mval>0.) {
                    float sval = sib->GetBinContent(ix,iy);
                    if (sval==0.) {
                        continue;
                    }
                    float eval = sib->GetBinError(ix,iy)/sval;
                    float dval = fabs(sval-mval)/sval;
                    if (sval<mval && dval>3.0*eval && mval/hmax>0.45) {
//                        if (sval/hmax>0.5) {
                        float rval = sval/mval;
                        if (rval<alpha) {
                            alpha = rval;
                        }
                    }
                }
            }
        }
    }
    mix->Scale(alpha);
    if (!msilent) {
        cout<<"Scaling "<<mix->GetName()<<" by "<<alpha<<endl;
    }
}

//---------------------------------------------------------
 TH1* StEStructSupport::getSqrt(TH1* h){

   TH1* retVal=(TH1*)h->Clone();
   for(int ix=1;ix<=retVal->GetNbinsX();ix++){
     for(int iy=1;iy<=retVal->GetNbinsY();iy++){
       float nv=h->GetBinContent(ix,iy);
       float env=h->GetBinError(ix,iy);
       if(nv>0.){
         nv=sqrt(nv);
         env=env/(2.0*nv);
       };
       retVal->SetBinContent(ix,iy,nv);
       retVal->SetBinError(ix,iy,nv);
     }
   }

   return retVal;
 }


//----------------------------------------------------------------
void StEStructSupport::fixDEta(TH2** h, int numHists) {

  // Expect histograms in groups of eight. The first eight are number,
  // with the first four being sibling and the second four being
  // mixed. If there are more than eight they will be pt weighted.
  // I find acceptance in the pair hole region is different for ++ and
  // +-, so we create two acceptance histograms, ++ + -- and +- + -+
  // using the mixed number. Not sure how to normalize the acceptance
  // histograms. For now try setting acceptance for \eta_\Delta = 0
  // to 1, excluding the pair cut hole.

    if(!mapplyDEtaFix) return;

    TH2D *acc[2];
    acc[0] = (TH2D *) h[4]->Clone();
    acc[0]->Add(h[7]);
    acc[1] = (TH2D *) h[5]->Clone();
    acc[1]->Add(h[6]);
    int n = acc[0]->GetNbinsX();
    double scale[] = {0, 0};
    if (n%2) {
        int mid = 1 + n/2;
        for (int iy=12;iy<=25;iy++) {
            scale[0] += acc[0]->GetBinContent(mid,iy);
            scale[1] += acc[1]->GetBinContent(mid,iy);
        }
        scale[0] /= 14;
        scale[1] /= 14;
    } else {
        int mid = n/2;
        for (int iy=12;iy<=25;iy++) {
            scale[0] += acc[0]->GetBinContent(mid,iy);
            scale[0] += acc[0]->GetBinContent(mid+1,iy);
            scale[1] += acc[1]->GetBinContent(mid,iy);
            scale[1] += acc[1]->GetBinContent(mid+1,iy);
        }
        scale[0] /= 28;
        scale[1] /= 28;
    }
    if (scale[0] > 0) {
        acc[0]->Scale(1.0/scale[0]);
    }
    if (scale[1] > 0) {
        acc[1]->Scale(1.0/scale[1]);
    }

    for (int ig=0;ig<numHists;ig+=8) {
        if (acc[0]->Integral() > 0) {
            h[ig+0]->Divide(acc[0]);
            h[ig+1]->Divide(acc[1]);
            h[ig+2]->Divide(acc[1]);
            h[ig+3]->Divide(acc[0]);
            h[ig+4]->Divide(acc[0]);
            h[ig+5]->Divide(acc[1]);
            h[ig+6]->Divide(acc[1]);
            h[ig+7]->Divide(acc[0]);
        }
    }
  delete acc[0];
  delete acc[1];
}

//---------------------------------------------------------
void StEStructSupport::writeAscii(TH1** h, int iHist, const char* fname, int optErrors){

  ofstream of(fname);
   int xbins=h[iHist]->GetNbinsX();
   TAxis * xa= h[iHist]->GetXaxis();
   of<<"# Histogram Name = "<<h[iHist]->GetName()<<endl;
   of<<"# X-axis: min="<<xa->GetBinLowEdge(1)<<" max="<<xa->GetBinUpEdge(xbins)<<" nbins="<<xbins<<endl;
 
   int ybins=h[iHist]->GetNbinsY();
   TAxis * ya= h[iHist]->GetYaxis();
   if(ybins>1){
     of<<"# Y-axis: min="<<ya->GetBinLowEdge(1)<<" max="<<ya->GetBinUpEdge(ybins)<<" nbins="<<ybins<<endl;
     of<<"# ix  iy  Value "<<endl; 
     for(int i=1;i<=xbins;i++){
       for(int j=1;j<=ybins;j++){
         of<<i<<"   "<<j<<"   "<<h[iHist]->GetBinContent(i,j);
         if(optErrors>0)of<<"  "<<h[iHist]->GetBinError(i,j);
         of<<endl;
       }
     }
     of<<endl;
   } else {
     of<<"# ix Value "<<endl;
     for(int i=1;i<=xbins;i++){
         of<<i<<"   "<<h[iHist]->GetBinContent(i);
         if(optErrors>0)of<<"  "<<h[iHist]->GetBinError(i);
         of<<endl;
     }
     of<<endl;
   }

  of.close();
}

//---------------------------------------------------------
char* StEStructSupport::swapIn(const char* name, const char* s1, const char* s2){

  // looks for s1 in name and replaces with s2
  //
  //  in perl    $name=~s/$s1/$s2/;

  if(mtmpString) delete [] mtmpString;
  mtmpString=NULL;

  if(!name) return mtmpString;

  int len=strlen(name);
  char* tmp=new char[len+1];
  strcpy(tmp,name);

  char* ptr1;
  if(!(ptr1=strstr(tmp,s1))) {
    delete [] tmp;
    return mtmpString;
  }

  int len1=strlen(s1);
  mtmpString=new char[256];

  ostringstream ts;
  char* ptr2=ptr1;
  *ptr1='\0';
  ts<<tmp; 
  if(s2)ts<<s2;
  ptr1+=len1;
  ts<<ptr1;
  *ptr2=' ';

  delete [] tmp;
  strcpy(mtmpString,(ts.str()).c_str());
  return mtmpString;
}


/***********************************************************************
 *
 * $Log: StEStructSupport.cxx,v $
 * Revision 1.18  2008/03/19 22:08:38  prindle
 * Use GetObject instead of Get for type safety. Stop deleting objects we didn't create.
 * Treat \Delta\rho = d^2n/dEtadphi (rho - rho_ref)/rho_ref as basic unit when combining
 * centralities and z bins.
 *
 * This code should be check in more detail before being completely relied upon.
 *
 * Revision 1.17  2007/11/26 20:07:19  prindle
 * Modified to average \Delta\rho/sqrt(\rho) over z-bins (if more than one z-bin
 * present for given centrality. Note: I weight by number of tracks, not number of
 * pairs. This is important when we are also combining different centralities (which
 * I do by combining centrality tag with z-bin tag in macro/addCentralities.)
 *
 * Scale mixed histograms by number of events. Integral of \Delta\rho need not be 0.
 *
 * delete items that are created and valgrind complained were lost. (Not a big deal
 * since macro is run once)
 *
 * [Still need to commit StEStructHAdd.cxx which cvs complained that check-update failed.]
 *
 * Revision 1.16  2007/05/27 22:46:01  msd
 * Added buildChargeTypes mode 3 which takes rho_ref from track counts.
 * Added buildChargeTypeSumOfRatios.
 *
 * Revision 1.15  2007/01/26 17:20:58  msd
 * Updated HAdd for new binning scheme.
 * Improved Support::buildChargeTypes.
 *
 * Revision 1.14  2006/12/14 20:07:11  prindle
 *   I was calculating \Delta\rho/sqrt(rho) for ++, +-, -+ and --
 * and then combining those into LS, US, CD and CI. The was wrong
 * and now I am doing it correctly. For CI this makes only a slight
 * change, it seems the amplitude is decreased a little. For CD
 * this is a bigger change. I left the old versions (with _Old appended)
 * for now.
 *
<<<<<<< StEStructSupport.cxx
=======
 * Revision 1.13  2006/10/27 00:05:32  prindle
 *   Modified buildChargeTypes to handle case where the -+ histogram is
 * empty. Also tried making buildCommonTypes work, but there one of the
 * output histograms was intended to be -+ and most of the time that
 * will be empty.
 *
>>>>>>> 1.13
 * Revision 1.11  2006/04/26 18:52:12  dkettler
 *
 * Added reaction plane determination for the analysis
 *
 * Added reaction plane angle calculation
 *
 * Case 3 in buildPtChargeTypes needs to be corrected
 *
 * Revision 1.10  2006/04/25 21:04:39  msd
 * Added Jeff's patch for getHists to create doubles instead of floats
 *
 * Revision 1.9  2006/04/06 01:09:49  prindle
 *   Calculating pt for each cut bin caused changes in HAdd.
 * The splitting of +- into +- and -+ caused changes in Support.
 *
 * Revision 1.8  2006/04/04 22:14:10  porter
 * fixdeta is now NOT default but included in StEStruct2ptCorrelations
 *
 * Revision 1.7  2005/09/14 17:25:37  msd
 * minor tweak
 *
 * Revision 1.6  2005/09/07 20:26:16  prindle
 *
 *
 *     Support: Fixed some meory leaks.
 *
 * Revision 1.4  2005/03/08 21:56:42  porter
 * fixed bug in StEStructHAdd.cxx and added diagnostic option in ptcorrelations to
 * view individual terms separately
 *
 * Revision 1.3  2005/03/08 20:16:34  msd
 * included <sstream> library
 *
 * Revision 1.2  2005/03/03 01:33:05  porter
 * Added pt-correlations method to support and included
 * these histograms to the HAdd routine
 *
 * Revision 1.1  2004/07/01 00:37:17  porter
 * new code previously my StEStructHelper. Takes hists from correltation
 * pass and builds final ressults.  Also the StEStructHAdd.h is a simple
 * replacemnt for my sumyt.C macro which could be expanded later as needed.
 *
 *
 *
 *********************************************************************/


