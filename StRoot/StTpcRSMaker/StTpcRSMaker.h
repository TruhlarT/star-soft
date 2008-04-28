#ifndef STAR_ST_TRS_MAKER_HH
#define STAR_ST_TRS_MAKER_HH

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StTpcRSMaker virtual base class for Maker                          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#ifndef StMaker_H
#include "StMaker.h"
#endif
#ifndef HEP_SYSTEM_OF_UNITS_H
#include "SystemOfUnits.h"
#endif
#ifndef ST_NO_NAMESPACES
using namespace units;
#endif
#include "TF1F.h"
#include "TH1.h"
#include "TTree.h"
#include "PAI.h"
#include "TGiant3.h"
// g2t tables
#include "tables/St_g2t_tpc_hit_Table.h"
#include "tables/St_g2t_track_Table.h"
#include "tables/St_g2t_vertex_Table.h" 
#include "tables/St_raw_sec_m_Table.h"
#include "tables/St_raw_row_Table.h"
#include "tables/St_raw_pad_Table.h"
#include "tables/St_raw_seq_Table.h"
#include "tables/St_type_shortdata_Table.h"
#include "tables/St_asic_thresholds_Table.h"
#include "tables/St_tss_tsspar_Table.h"
#include "StTpcDb/StTpcDb.h"
#include "StTpcDb/StTpcdEdxCorrection.h" 
#include "StMagF.h"
struct SignalSum_t {
  Float_t      Sum;
  Short_t      Adc;
  Short_t  TrackId;
};
class StTpcRSMaker : public StMaker {
 public:
  enum EMode {kPAI         = 0,// switch to PAI from GEANT
	      kBICHSEL     = 1,// switch to Bichsel from GEANT 
	      kGAIN        = 2,// use GAIN correction (in/out)
	      kGAINO       = 3,// use GAIN correction (in) output is uncorrected data
	      kGAINOAtALL  = 4,// do not use GAIN at all
	      kPedestal    = 5,// do use Pedestal and noise
	      kAVERAGEPEDESTAL = 6, // use Pedestal in average i.e. Gaus(mAveragePedestal,mAveragePedestalRMS) for pedestal itself 
 	      //              and Gaus(0,mPedestalRMS) for noise
	      kNONOISE     = 7,// No pedestal noise
	      kdEdxCorr    = 8,// do use TpcdEdxCorrection
	      kPseudoPadRow= 9,// include pseudo padrows in simulation
	      kNoToflight  =10,// don't account for particle time of flight
	      kTree        =11// make Tree
  };
  StTpcRSMaker(const char *name="TrsMini");
  virtual              ~StTpcRSMaker();
  virtual Int_t         InitRun(int runnumber);
  virtual Int_t         Make();
#if 0
  virtual void   	Clear(Option_t *option="");
#endif
  virtual Int_t  	Finish();
  virtual void          AlignHits(Bool_t flag=kFALSE){mAlignSector=flag;}
  TF1 *GetShaperResponse(Int_t io = 0, Int_t sector = 1) {return (TF1 *) mShaperResponses[io][sector-1];}          
  TF1 *GetChargeFractionInner()     {return (TF1 *) mChargeFractionInner;}     
  TF1 *GetPadResponseFunctionInner(){return (TF1 *) mPadResponseFunctionInner;}
  TF1 *GetChargeFractionOuter()     {return (TF1 *) mChargeFractionOuter;}     
  TF1 *GetPadResponseFunctionOuter(){return (TF1 *) mPadResponseFunctionOuter;}
  TF1 *GetPolya()                   {return (TF1 *) mPolya;}
  Double_t GetNoPrimaryClusters(Double_t betaGamma);
  virtual void Print(Option_t *option="") const;
  void DigiSector(Int_t sector);
  void SetLaserScale(Double_t m=1) {mLaserScale = m;}
  void SetClusterLength(Double_t m=0) {mClusterLength = m;}
  static Int_t    SearchT(const void *elem1, const void **elem2);
  static Int_t    CompareT(const void **elem1, const void **elem2);
  static Double_t shapeEI(Double_t *x, Double_t *par=0);
  static Double_t shapeEI_I(Double_t *x, Double_t *par=0);
  static Double_t expint(Int_t n, Double_t x); // Exponential Integrals En
  static Double_t ei(Double_t x); // Exponential Integral Ei
  SignalSum_t  *GetSignalSum();
  SignalSum_t  *ResetSignalSum();
 private:
  TTree   *fTree;                     //!
  TGiant3 *mGeant;                    //!
  SignalSum_t     *m_SignalSum;       //!
  TH1D*    mdNdx;                     //!
  TH1D*    mdNdE;                     //!
  static Double_t ShaperFunc(Double_t *x, Double_t *p);
  static Double_t PadResponseFunc(Double_t *x, Double_t *p);
  static Double_t Gatti(Double_t *x, Double_t *p);
  static Double_t InducedCharge(Double_t s, Double_t h, Double_t ra, Double_t Va, Double_t &t0);
  static TF1     *fgTimeShape;        //!
  TF1F  *mShaperResponses[2][24];     //!
  TF1F  *mChargeFractionInner;        //!
  TF1F  *mPadResponseFunctionInner;   //!
  TF1F  *mChargeFractionOuter;        //!
  TF1F  *mPadResponseFunctionOuter;   //!
  TF1F  *mPolya;                      //!
  St_tss_tsspar *mtsspar;             //!
  Bool_t mAlignSector;                //! 
  Int_t  mMagUtilitiesMask;           //!
  StTpcdEdxCorrection *m_TpcdEdxCorrection; // !
  PAI  *mPAI;                        //!
  Double_t             mLaserScale;  //!
  Double_t             mClusterLength;//!
  Double_t             mTau;         //!
  Double_t             mTimeBinWidth;//!
  // local variables
  Int_t NumberOfInnerRows;//!
  Int_t numberOfSectors; //!
  Int_t NumberOfRows; //!
  Int_t NoPads; //!
  Int_t numberOfTimeBins; //!
  Double_t W; //!// = 26.2;// *eV
  Double_t I0; //! = 15.7 eV for Ar (and  13.1 eV for CH4)
  const Double_t mCluster; //!
  //  Double_t firstOuterSectorAnodeWire ; //!
  Double_t innerSectorzOffSet; //!
  Double_t outerSectorzOffSet; //!
  //  Double_t offset; //!
  Double_t samplingFrequency; //!
  Double_t tauGlobalOffSet; //!
  Int_t    numberOfInnerSectorAnodeWires; //! 
  Double_t firstInnerSectorAnodeWire; //!
  Double_t lastInnerSectorAnodeWire; //!
  Int_t    numberOfOuterSectorAnodeWires; //!
  Double_t firstOuterSectorAnodeWire; //!
  Double_t lastOuterSectorAnodeWire; //!
  Double_t anodeWirePitch; //!
  Double_t OmegaTauC; //!
  Double_t transverseDiffusionConstant; //!
  Double_t longitudinalDiffusionConstant; //!
  Double_t OmegaTau; //! 
  Double_t InnerSectorGasGain; //!
  Double_t OuterSectorGasGain; //!
  Double_t Inner_wire_to_plane_coupling; //!
  Double_t Outer_wire_to_plane_coupling; //!
  const  Double_t  Inner_wire_to_plane_couplingScale; //!
  const  Double_t  Outer_wire_to_plane_couplingScale; //!
  Double_t numberOfElectronsPerADCcount; //!
  Double_t anodeWireRadius; //!
  const Double_t FanoFactor; //! // average Fano factor  
  Int_t mThreshLo; //!
  Int_t mThreshHi; //!
  Int_t mNseqLo; //!
  Int_t mNseqHi; //!
  const Double_t K3IP; //!
  const Double_t K3IR; //!
  const Double_t K3OP; //!
  const Double_t K3OR; //!
  const Double_t mAveragePedestal;    //!
  const Double_t mAveragePedestalRMS; //!
  const Double_t mPedestalRMS; //!
  const Double_t minSignal;    //!
  const Double_t LorenzAngle;  //!
  Double_t TanLorenzAngle; //!
  Double_t InnerAlphaVariation; //!
  Double_t OuterAlphaVariation; //!
  Double_t innerSectorAnodeVoltage; //!
  Double_t outerSectorAnodeVoltage; //!
  const Double_t ElectronRange; //!
  const Double_t ElectronRangeEnergy; //!
  const Double_t ElectronRangePower; //!
  const Double_t CrossTalkInner; //!
  const Double_t CrossTalkOuter; //!
 public:    
  virtual const char *GetCVS() const {
    static const char cvs[]= 
      "Tag $Name:  $ $Id: StTpcRSMaker.h,v 1.1 2008/04/28 14:39:47 fisyak Exp $ built __DATE__ __TIME__"; 
      return cvs;
  }
  ClassDef(StTpcRSMaker,0)   //StAF chain virtual base class for Makers
};
#endif
// $Id: StTpcRSMaker.h,v 1.1 2008/04/28 14:39:47 fisyak Exp $
// $Log: StTpcRSMaker.h,v $
// Revision 1.1  2008/04/28 14:39:47  fisyak
// Initial revision
//
// Revision 1.14  2008/04/24 10:42:04  fisyak
// Fix binning issues
//
// Revision 1.13  2008/04/04 15:00:11  fisyak
// Freeze before shaper modifications
//
// Revision 1.12  2005/02/07 21:40:31  fisyak
// rename antique TGeant3 to TGiant3
//
// Revision 1.11  2005/01/26 21:45:31  fisyak
// Freeze correction made in June
//
// Revision 1.9  2004/05/29 21:16:27  fisyak
// Fix pad direction, add sorting for ADC/cluster nonlinearity, replace product by sum of logs
//
// Revision 1.8  2004/05/04 13:39:06  fisyak
// Add TF1F
//
// Revision 1.7  2004/04/22 01:05:03  fisyak
// Freeze the version before modification parametrization for K3
//
// Revision 1.6  2004/04/06 01:50:13  fisyak
// Switch from Double_t to Float_t for sum
//
// Revision 1.5  2004/03/30 19:30:04  fisyak
// Add Laser
//
// Revision 1.4  2004/03/21 19:00:43  fisyak
// switch to GEANT step length
//
// Revision 1.3  2004/03/20 17:57:15  fisyak
// Freeze the version of PAI model
//
// Revision 1.2  2004/03/17 20:47:43  fisyak
// Add version with TrsCluster TTree
//
// Revision 1.1.1.1  2004/03/05 20:51:25  fisyak
// replacement for Trs
//
