// $Id: QAhlist_EventQA_qa_shift.h,v 2.25 2004/10/04 16:40:42 genevb Exp $
// $Log: QAhlist_EventQA_qa_shift.h,v $
// Revision 2.25  2004/10/04 16:40:42  genevb
// FTPC radial histos
//
// Revision 2.24  2004/04/23 23:15:29  genevb
// Added signedDCA (Impact) plots for globals
//
// Revision 2.23  2004/03/17 00:35:14  genevb
// Left Mult off hist names in previous commit
//
// Revision 2.22  2004/03/15 23:32:14  genevb
// Add primary vertex check for event classes to QA Shift set
//
// Revision 2.21  2004/02/12 17:39:15  genevb
// Separate MinBias histos
//
// Revision 2.20  2004/02/12 05:03:03  genevb
// Year 4 AuAu changes. New SVT histos.
//
// Revision 2.19  2003/04/19 00:17:49  genevb
// Updated for dAu/pp running
//
// Revision 2.18  2003/01/02 19:39:47  genevb
// Comment out BBC/FPD histos; See diffs to previous version to restore
//
// Revision 2.17  2002/05/29 13:54:30  genevb
// Some changes to FTPC chisq histos
//
// Revision 2.16  2002/04/23 01:59:55  genevb
// Addition of BBC/FPD histos
//
// Revision 2.15  2002/02/12 18:41:59  genevb
// Additional FTPC histograms
//
// Revision 2.14  2002/01/26 03:04:07  genevb
// Fixed some problems with fcl histos
//
// Revision 2.13  2002/01/21 22:09:24  genevb
// Include some ftpc histograms from StFtpcClusterMaker
//
// Revision 2.12  2001/11/20 21:53:45  lansdell
// added x-y dist of hits, tpc east&west histos
//
// Revision 2.11  2001/08/29 20:45:15  genevb
// Trigger word histos
//
// Revision 2.10  2001/08/27 21:15:15  genevb
// fixed a typo
//
// Revision 2.9  2001/07/31 23:21:42  lansdell
// added last point, hit-helix histos
//
// Revision 2.8  2001/06/27 23:57:50  lansdell
// added geant-reco primvtx position histos to qa_shift list
//
// Revision 2.7  2001/05/29 23:23:05  lansdell
// removed impact param plots for FTPC from qa_shift list
//
// Revision 2.6  2001/05/25 16:31:20  lansdell
// more updates to qa shift histograms
//
// Revision 2.5  2001/05/24 01:48:13  lansdell
// qa_shift histograms updated
//
// Revision 2.4  2001/05/23 00:14:52  lansdell
// more changes for qa_shift histograms
//
// Revision 2.3  2001/05/16 20:57:02  lansdell
// new histograms added for qa_shift printlist; some histogram ranges changed; StMcEvent now used in StEventQA
//
// Revision 2.2  2001/04/24 22:53:50  lansdell
// Removed redundant radial position of first hit histograms
//
// Revision 2.1  2000/08/25 16:04:09  genevb
// Introduction of files
//
//
///////////////////////////////////////////////////////////////////////
// Names of histograms to be plotted for dir=EventQA, analType=qa_shift
///////////////////////////////////////////////////////////////////////
// Note: Editing this file means that StAnalysisUtilities/StHistUtil
// must be recompiled

  "StEQaMultClass",
  "StEQaTrigWord",
  "StEQaTrigBits",
  "fcl_chargestepW",
  "fcl_chargestepE",
  "fcl_radialW",
  "fcl_radialE",

  "StEQaPointTpc",
  "StEQaPointSvt",
  "StEQaPointSvtLaser",
  "StEQaPointFtpc",
  "StEQaPointXYTpcE",
  "StEQaPointXYTpcW",
  "StEQaPointXYFtpcE",
  "StEQaPointXYFtpcW",
  "StEQaPointPadTimeFtpcE",
  "StEQaPointPadTimeFtpcW",
  "StEQaPointZhits",
  "StEQaPointPhiT",
  "StEQaPointZhitsS",
  "StEQaPointPhiS",
  "StEQaPointPadrowT",
  "StEQaPointBarrelS",
  "StEQaPointPlaneF",
  "StEQaRichTot",
  "StEQaGtrkZfTS",
  "StEQaGtrkPhifTS",
  "StEQaGtrkZfT",
  "StEQaGtrkPhifT",
  "StEQaGtrkXfYfFE",
  "StEQaGtrkXfYfFW",
  "StEQaGtrkPadTimeFtpcE",
  "StEQaGtrkPadTimeFtpcW",
  "StEQaGtrkPadfTEW",
  "StEQaGtrkRTS",
  "StEQaGtrkPlanefF",
  "StEQaGtrkRnfTTS",
  "StEQaGtrkRnmfTTS",
  "StEQaGtrkRnmF",
  "StEQaGtrkPsiTTS",
  "StEQaGtrkPtTTS",
  "StEQaGtrkEtaTTS",
  "StEQaGtrkPsiF",
  "StEQaGtrkPtF",
  "StEQaGtrkEtaF",
  "StEQaGtrkPF",
  "StEQaGtrkChisq0TTS",
  "StEQaGtrkChisq1TTS",
  "StEQaGtrkChisq0F",
  "StEQaGtrkChisq1F",
  "StEQaGtrkFlag",
  "StEQaGtrkGoodTot",
  "StEQaGtrkNPntFitTTS",
  "StEQaGtrkNPntF",
  "StEQaGtrkGoodTTS",
  "StEQaGtrkGoodF",
  "StEQaGtrkFitPntLTTS",
  "StEQaGtrkSImpactT",
  "StEQaGtrkImpactTTS",
  "StEQaGtrkImpactrTTS",
  "StEQaGtrkImpactrF",
  "StEQaGtrkDetId",
  "StEQaGtrkTanlzf",
  "StEQaGtrkTanlzfTS",
  "StEQaPtrkPsiTTS",
  "StEQaPtrkPtTTS",
  "StEQaPtrkEtaTTS",
  "StEQaPtrkPsiF",
  "StEQaPtrkPtF",
  "StEQaPtrkEtaF",
  "StEQaPtrkMeanPtTTS",
  "StEQaPtrkMeanEtaTTS",
  "StEQaPtrkMeanPtF",
  "StEQaPtrkMeanEtaF",
  "StEQaPtrkGoodTTS",
  "StEQaPtrkGoodF",
  "StEQaPtrkChisq0TTS",
  "StEQaPtrkChisq1TTS",
  "StEQaPtrkChisq0F",
  "StEQaPtrkChisq1F",
  "StEQaPtrkFlag",
  "StEQaPtrkImpactTTS",
  "StEQaPtrkImpactrTTS",
  "StEQaPtrkGlob",
  "StEQaPtrkFitPntLTTS",
  "StEQaNullPrimVtx",
  "StEQaVtxPrXY",
  "StEQaVtxPrZ",
  "StEQaVtxSvtvsTpc",
  "StEQaGtrkDcaBeamZ1",
  "StEQaGtrkDcaBeamZ2",
  "StEQaGtrkZdcaZf",
  "StEQaGtrkZdcaPsi",
  "StEQaGtrkZdcaTanl",
  "QaDedxAllSectors",
  "StEQaPidGlobtrkDstdedxPVsDedx",
  "StEQaDedxBBTTS",
  "StEQaDedxDedx0F",
  "StEQaEvsumTotChg",
  "StEQaEvsumTotChgF",
  "StEQaV0Vtx",
  "StEQaV0VtxRDist",
  "StEQaV0VtxZDist",
  "StEQaV0VtxPhiDist",
  "StEQaV0LambdaMass",
  "StEQaV0K0Mass",
  "StEQaXiVtxTot",
  "StEQaKinkTot",
  "StEQaGtrkRZf0",
  "StEQaGtrkRZl0",
  "StEQaGtrkRZf0TS",
  "StEQaGtrkRZl0TS",
  "StEQaPtrkRZf0",
  "StEQaPtrkRZl0",
  "StEQaPtrkRZf0TS",
  "StEQaPtrkRZl0TS",
  "StEbemcClNum",
  "StEbemcClEnergy",
  "StEbemcEta",
  "StEbemcPhi",
  "StEbsmdeClNum",
  "StEbsmdeEta",
  "StEbsmdpClNum",
  "StEbsmdpPhi",
  "StEEmcCat4_Point_Energy",
  "StEEmcCat4_Point_Eta",
  "StEEmcCat4_Point_Phi",
  "StEEmcCat4_Sigma_Eta",
  "StEEmcCat4_Sigma_Phi",
  "StEEmcCat4_Delta_Eta",
  "StEEmcCat4_Delta_Phi",
  "StEEmcCat4_Points_Multiplicity",
  "StEEmcCat4_Track_Momenta",
  "StE Point Flag",
  "StEQaGRpvtxDx",
  "StEQaGRpvtxDy",
  "StEQaGRpvtxDz",
  "StEQaBbcAdcES",
  "StEQaBbcAdcEL",
  "StEQaBbcAdcWS",
  "StEQaBbcAdcWL",
  "StEQaBbcTdcES",
  "StEQaBbcTdcEL",
  "StEQaBbcTdcWS",
  "StEQaBbcTdcWL",
  "StEQaFpdTop0",
  "StEQaFpdTop1",
  "StEQaFpdBottom0",
  "StEQaFpdBottom1",
  "StEQaFpdSouth0",
  "StEQaFpdSouth1",
  "StEQaFpdNorth0",
  "StEQaFpdNorth1",
  "StEQaFpdSums0",
  "StEQaFpdSums1",
  "StEQaFpdSums2",
  "StEQaFpdSums3",
  "StEQaFpdSums4",
  "StEQaFpdSums5",
  "StEQaFpdSums6",
  "StEQaFpdSums7",

  "StELMQaPointTpc",
  "StELMQaPointSvt",
  "StELMQaPointSvtLaser",
  "StELMQaPointFtpc",
  "StELMQaPointXYTpcE",
  "StELMQaPointXYTpcW",
  "StELMQaPointXYFtpcE",
  "StELMQaPointXYFtpcW",
  "StELMQaPointPadTimeFtpcE",
  "StELMQaPointPadTimeFtpcW",
  "StELMQaPointZhits",
  "StELMQaPointPhiT",
  "StELMQaPointZhitsS",
  "StELMQaPointPhiS",
  "StELMQaPointPadrowT",
  "StELMQaPointBarrelS",
  "StELMQaPointPlaneF",
  "StELMQaRichTot",
  "StELMQaGtrkZfTS",
  "StELMQaGtrkPhifTS",
  "StELMQaGtrkZfT",
  "StELMQaGtrkPhifT",
  "StELMQaGtrkXfYfFE",
  "StELMQaGtrkXfYfFW",
  "StELMQaGtrkPadTimeFtpcE",
  "StELMQaGtrkPadTimeFtpcW",
  "StELMQaGtrkPadfTEW",
  "StELMQaGtrkRTS",
  "StELMQaGtrkPlanefF",
  "StELMQaGtrkRnfTTS",
  "StELMQaGtrkRnmfTTS",
  "StELMQaGtrkRnmF",
  "StELMQaGtrkPsiTTS",
  "StELMQaGtrkPtTTS",
  "StELMQaGtrkEtaTTS",
  "StELMQaGtrkPsiF",
  "StELMQaGtrkPtF",
  "StELMQaGtrkEtaF",
  "StELMQaGtrkPF",
  "StELMQaGtrkChisq0T",
  "StELMQaGtrkChisq1T",
  "StELMQaGtrkChisq0F",
  "StELMQaGtrkChisq1F",
  "StELMQaGtrkFlag",
  "StELMQaGtrkGoodTot",
  "StELMQaGtrkNPntFitTTS",
  "StELMQaGtrkNPntF",
  "StELMQaGtrkGoodTTS",
  "StELMQaGtrkGoodF",
  "StELMQaGtrkFitPntLTTS",
  "StELMQaGtrkSImpactT",
  "StELMQaGtrkImpactTTS",
  "StELMQaGtrkImpactrTTS",
  "StELMQaGtrkImpactrF",
  "StELMQaGtrkDetId",
  "StELMQaGtrkTanlzf",
  "StELMQaGtrkTanlzfTS",
  "StELMQaPtrkPsiTTS",
  "StELMQaPtrkPtTTS",
  "StELMQaPtrkEtaTTS",
  "StELMQaPtrkPsiF",
  "StELMQaPtrkPtF",
  "StELMQaPtrkEtaF",
  "StELMQaPtrkMeanPtTTS",
  "StELMQaPtrkMeanEtaTTS",
  "StELMQaPtrkMeanPtF",
  "StELMQaPtrkMeanEtaF",
  "StELMQaPtrkGoodTTS",
  "StELMQaPtrkGoodF",
  "StELMQaPtrkChisq0TTS",
  "StELMQaPtrkChisq1TTS",
  "StELMQaPtrkChisq0F",
  "StELMQaPtrkChisq1F",
  "StELMQaPtrkFlag",
  "StELMQaPtrkImpactTTS",
  "StELMQaPtrkImpactrTTS",
  "StELMQaPtrkGlob",
  "StELMQaPtrkFitPntLTTS",
  "StELMQaNullPrimVtxMult",
  "StELMQaVtxPrXY",
  "StELMQaVtxPrZ",
  "StELMQaVtxSvtvsTpc",
  "StELMQaGtrkDcaBeamZ1",
  "StELMQaGtrkDcaBeamZ2",
  "StELMQaGtrkZdcaZf",
  "StELMQaGtrkZdcaPsi",
  "StELMQaGtrkZdcaTanl",
  "StELMQaPidGlobtrkDstdedxPVsDedx",
  "StELMQaDedxBBTTS",
  "StELMQaDedxDedx0F",
  "StELMQaEvsumTotChg",
  "StELMQaEvsumTotChgF",
  "StELMQaV0Vtx",
  "StELMQaV0VtxRDist",
  "StELMQaV0VtxZDist",
  "StELMQaV0VtxPhiDist",
  "StELMQaV0LambdaMass",
  "StELMQaV0K0Mass",
  "StELMQaXiVtxTot",
  "StELMQaKinkTot",
  "StELMQaGtrkRZf0",
  "StELMQaGtrkRZf0TS",
  "StELMQaPtrkRZf0",
  "StELMQaPtrkRZf0TS",
  "StELMbemcClNum",
  "StELMbemcClEnergy",
  "StELMbemcEta",
  "StELMbemcPhi",
  "StELMbsmdeClNum",
  "StELMbsmdeEta",
  "StELMbsmdpClNum",
  "StELMbsmdpPhi",
  "StELMEmcCat4_Point_Energy",
  "StELMEmcCat4_Point_Eta",
  "StELMEmcCat4_Point_Phi",
  "StELMEmcCat4_Sigma_Eta",
  "StELMEmcCat4_Sigma_Phi",
  "StELMEmcCat4_Delta_Eta",
  "StELMEmcCat4_Delta_Phi",
  "StELMEmc_Cat4_Points_Multiplicity",
  "StELMEmcCat4_Track_Momenta",
  "StELM Point Flag",
  "StELMQaGRpvtxDx",
  "StELMQaGRpvtxDy",
  "StELMQaGRpvtxDz",
  "StELMQaBbcAdcES",
  "StELMQaBbcAdcEL",
  "StELMQaBbcAdcWS",
  "StELMQaBbcAdcWL",
  "StELMQaBbcTdcES",
  "StELMQaBbcTdcEL",
  "StELMQaBbcTdcWS",
  "StELMQaBbcTdcWL",
  "StELMQaFpdTop0",
  "StELMQaFpdTop1",
  "StELMQaFpdBottom0",
  "StELMQaFpdBottom1",
  "StELMQaFpdSouth0",
  "StELMQaFpdSouth1",
  "StELMQaFpdNorth0",
  "StELMQaFpdNorth1",
  "StELMQaFpdSums0",
  "StELMQaFpdSums1",
  "StELMQaFpdSums2",
  "StELMQaFpdSums3",
  "StELMQaFpdSums4",
  "StELMQaFpdSums5",
  "StELMQaFpdSums6",
  "StELMQaFpdSums7",

  "StEMMQaPointTpc",
  "StEMMQaPointSvt",
  "StEMMQaPointSvtLaser",
  "StEMMQaPointFtpc",
  "StEMMQaPointXYTpcE",
  "StEMMQaPointXYTpcW",
  "StEMMQaPointXYFtpcE",
  "StEMMQaPointXYFtpcW",
  "StEMMQaPointPadTimeFtpcE",
  "StEMMQaPointPadTimeFtpcW",
  "StEMMQaPointZhits",
  "StEMMQaPointPhiT",
  "StEMMQaPointZhitsS",
  "StEMMQaPointPhiS",
  "StEMMQaPointPadrowT",
  "StEMMQaPointBarrelS",
  "StEMMQaPointPlaneF",
  "StEMMQaRichTot",
  "StEMMQaGtrkZfTS",
  "StEMMQaGtrkPhifTS",
  "StEMMQaGtrkZfT",
  "StEMMQaGtrkPhifT",
  "StEMMQaGtrkXfYfFE",
  "StEMMQaGtrkXfYfFW",
  "StEMMQaGtrkPadTimeFtpcE",
  "StEMMQaGtrkPadTimeFtpcW",
  "StEMMQaGtrkPadfTEW",
  "StEMMQaGtrkRTS",
  "StEMMQaGtrkPlanefF",
  "StEMMQaGtrkRnfTTS",
  "StEMMQaGtrkRnmfTTS",
  "StEMMQaGtrkRnmF",
  "StEMMQaGtrkPsiTTS",
  "StEMMQaGtrkPtTTS",
  "StEMMQaGtrkEtaTTS",
  "StEMMQaGtrkPsiF",
  "StEMMQaGtrkPtF",
  "StEMMQaGtrkEtaF",
  "StEMMQaGtrkPF",
  "StEMMQaGtrkChisq0T",
  "StEMMQaGtrkChisq1T",
  "StEMMQaGtrkChisq0F",
  "StEMMQaGtrkChisq1F",
  "StEMMQaGtrkFlag",
  "StEMMQaGtrkGoodTot",
  "StEMMQaGtrkNPntFitTTS",
  "StEMMQaGtrkNPntF",
  "StEMMQaGtrkGoodTTS",
  "StEMMQaGtrkGoodF",
  "StEMMQaGtrkFitPntLTTS",
  "StEMMQaGtrkSImpactT",
  "StEMMQaGtrkImpactTTS",
  "StEMMQaGtrkImpactrTTS",
  "StEMMQaGtrkImpactrF",
  "StEMMQaGtrkDetId",
  "StEMMQaGtrkTanlzf",
  "StEMMQaGtrkTanlzfTS",
  "StEMMQaPtrkPsiTTS",
  "StEMMQaPtrkPtTTS",
  "StEMMQaPtrkEtaTTS",
  "StEMMQaPtrkPsiF",
  "StEMMQaPtrkPtF",
  "StEMMQaPtrkEtaF",
  "StEMMQaPtrkMeanPtTTS",
  "StEMMQaPtrkMeanEtaTTS",
  "StEMMQaPtrkMeanPtF",
  "StEMMQaPtrkMeanEtaF",
  "StEMMQaPtrkGoodTTS",
  "StEMMQaPtrkGoodF",
  "StEMMQaPtrkChisq0TTS",
  "StEMMQaPtrkChisq1TTS",
  "StEMMQaPtrkChisq0F",
  "StEMMQaPtrkChisq1F",
  "StEMMQaPtrkFlag",
  "StEMMQaPtrkImpactTTS",
  "StEMMQaPtrkImpactrTTS",
  "StEMMQaPtrkGlob",
  "StEMMQaPtrkFitPntLTTS",
  "StEMMQaNullPrimVtxMult",
  "StEMMQaVtxPrXY",
  "StEMMQaVtxPrZ",
  "StEMMQaVtxSvtvsTpc",
  "StEMMQaGtrkDcaBeamZ1",
  "StEMMQaGtrkDcaBeamZ2",
  "StEMMQaGtrkZdcaZf",
  "StEMMQaGtrkZdcaPsi",
  "StEMMQaGtrkZdcaTanl",
  "StEMMQaPidGlobtrkDstdedxPVsDedx",
  "StEMMQaDedxBBTTS",
  "StEMMQaDedxDedx0F",
  "StEMMQaEvsumTotChg",
  "StEMMQaEvsumTotChgF",
  "StEMMQaV0Vtx",
  "StEMMQaV0VtxRDist",
  "StEMMQaV0VtxZDist",
  "StEMMQaV0VtxPhiDist",
  "StEMMQaV0LambdaMass",
  "StEMMQaV0K0Mass",
  "StEMMQaXiVtxTot",
  "StEMMQaKinkTot",
  "StEMMQaGtrkRZf0",
  "StEMMQaGtrkRZf0TS",
  "StEMMQaPtrkRZf0",
  "StEMMQaPtrkRZf0TS",
  "StEMMbemcClNum",
  "StEMMbemcClEnergy",
  "StEMMbemcEta",
  "StEMMbemcPhi",
  "StEMMbsmdeClNum",
  "StEMMbsmdeEta",
  "StEMMbsmdpClNum",
  "StEMMbsmdpPhi",
  "StEMMEmcCat4_Point_Energy",
  "StEMMEmcCat4_Point_Eta",
  "StEMMEmcCat4_Point_Phi",
  "StEMMEmcCat4_Sigma_Eta",
  "StEMMEmcCat4_Sigma_Phi",
  "StEMMEmcCat4_Delta_Eta",
  "StEMMEmcCat4_Delta_Phi",
  "StEMMEmc_Cat4_Points_Multiplicity",
  "StEMMEmcCat4_Track_Momenta",
  "StEMM Point Flag",
  "StEMMQaGRpvtxDx",
  "StEMMQaGRpvtxDy",
  "StEMMQaGRpvtxDz",
  "StEMMQaBbcAdcES",
  "StEMMQaBbcAdcEL",
  "StEMMQaBbcAdcWS",
  "StEMMQaBbcAdcWL",
  "StEMMQaBbcTdcES",
  "StEMMQaBbcTdcEL",
  "StEMMQaBbcTdcWS",
  "StEMMQaBbcTdcWL",
  "StEMMQaFpdTop0",
  "StEMMQaFpdTop1",
  "StEMMQaFpdBottom0",
  "StEMMQaFpdBottom1",
  "StEMMQaFpdSouth0",
  "StEMMQaFpdSouth1",
  "StEMMQaFpdNorth0",
  "StEMMQaFpdNorth1",
  "StEMMQaFpdSums0",
  "StEMMQaFpdSums1",
  "StEMMQaFpdSums2",
  "StEMMQaFpdSums3",
  "StEMMQaFpdSums4",
  "StEMMQaFpdSums5",
  "StEMMQaFpdSums6",
  "StEMMQaFpdSums7",

  "StEHMQaPointTpc",
  "StEHMQaPointSvt",
  "StEHMQaPointSvtLaser",
  "StEHMQaPointFtpc",
  "StEHMQaPointXYTpcE",
  "StEHMQaPointXYTpcW",
  "StEHMQaPointXYFtpcE",
  "StEHMQaPointXYFtpcW",
  "StEHMQaPointPadTimeFtpcE",
  "StEHMQaPointPadTimeFtpcW",
  "StEHMQaPointZhits",
  "StEHMQaPointPhiT",
  "StEHMQaPointZhitsS",
  "StEHMQaPointPhiS",
  "StEHMQaPointPadrowT",
  "StEHMQaPointBarrelS",
  "StEHMQaPointPlaneF",
  "StEHMQaRichTot",
  "StEHMQaGtrkZfTS",
  "StEHMQaGtrkPhifTS",
  "StEHMQaGtrkZfT",
  "StEHMQaGtrkPhifT",
  "StEHMQaGtrkXfYfFE",
  "StEHMQaGtrkXfYfFW",
  "StEHMQaGtrkPadTimeFtpcE",
  "StEHMQaGtrkPadTimeFtpcW",
  "StEHMQaGtrkPadfTEW",
  "StEHMQaGtrkRTS",
  "StEHMQaGtrkPlanefF",
  "StEHMQaGtrkRnfTTS",
  "StEHMQaGtrkRnmfTTS",
  "StEHMQaGtrkRnmF",
  "StEHMQaGtrkPsiTTS",
  "StEHMQaGtrkPtTTS",
  "StEHMQaGtrkEtaTTS",
  "StEHMQaGtrkPsiF",
  "StEHMQaGtrkPtF",
  "StEHMQaGtrkEtaF",
  "StEHMQaGtrkPF",
  "StEHMQaGtrkChisq0T",
  "StEHMQaGtrkChisq1T",
  "StEHMQaGtrkChisq0F",
  "StEHMQaGtrkChisq1F",
  "StEHMQaGtrkFlag",
  "StEHMQaGtrkGoodTot",
  "StEHMQaGtrkNPntFitTTS",
  "StEHMQaGtrkNPntF",
  "StEHMQaGtrkGoodTTS",
  "StEHMQaGtrkGoodF",
  "StEHMQaGtrkFitPntLTTS",
  "StEHMQaGtrkSImpactT",
  "StEHMQaGtrkImpactTTS",
  "StEHMQaGtrkImpactrTTS",
  "StEHMQaGtrkImpactrF",
  "StEHMQaGtrkDetId",
  "StEHMQaGtrkTanlzf",
  "StEHMQaGtrkTanlzfTS",
  "StEHMQaPtrkPsiTTS",
  "StEHMQaPtrkPtTTS",
  "StEHMQaPtrkEtaTTS",
  "StEHMQaPtrkPsiF",
  "StEHMQaPtrkPtF",
  "StEHMQaPtrkEtaF",
  "StEHMQaPtrkMeanPtTTS",
  "StEHMQaPtrkMeanEtaTTS",
  "StEHMQaPtrkMeanPtF",
  "StEHMQaPtrkMeanEtaF",
  "StEHMQaPtrkGoodTTS",
  "StEHMQaPtrkGoodF",
  "StEHMQaPtrkChisq0TTS",
  "StEHMQaPtrkChisq1TTS",
  "StEHMQaPtrkChisq0F",
  "StEHMQaPtrkChisq1F",
  "StEHMQaPtrkFlag",
  "StEHMQaPtrkImpactTTS",
  "StEHMQaPtrkImpactrTTS",
  "StEHMQaPtrkGlob",
  "StEHMQaPtrkFitPntLTTS",
  "StEHMQaNullPrimVtxMult",
  "StEHMQaVtxPrXY",
  "StEHMQaVtxPrZ",
  "StEHMQaVtxSvtvsTpc",
  "StEHMQaGtrkDcaBeamZ1",
  "StEHMQaGtrkDcaBeamZ2",
  "StEHMQaGtrkZdcaZf",
  "StEHMQaGtrkZdcaPsi",
  "StEHMQaGtrkZdcaTanl",
  "StEHMQaPidGlobtrkDstdedxPVsDedx",
  "StEHMQaDedxBBTTS",
  "StEHMQaDedxDedx0F",
  "StEHMQaEvsumTotChg",
  "StEHMQaEvsumTotChgF",
  "StEHMQaV0Vtx",
  "StEHMQaV0VtxRDist",
  "StEHMQaV0VtxZDist",
  "StEHMQaV0VtxPhiDist",
  "StEHMQaV0LambdaMass",
  "StEHMQaV0K0Mass",
  "StEHMQaXiVtxTot",
  "StEHMQaKinkTot",
  "StEHMQaGtrkRZf0",
  "StEHMQaGtrkRZf0TS",
  "StEHMQaPtrkRZf0",
  "StEHMQaPtrkRZf0TS",
  "StEHMbemcClNum",
  "StEHMbemcClEnergy",
  "StEHMbemcEta",
  "StEHMbemcPhi",
  "StEHMbsmdeClNum",
  "StEHMbsmdeEta",
  "StEHMbsmdpClNum",
  "StEHMbsmdpPhi",
  "StEHMEmcCat4_Point_Energy",
  "StEHMEmcCat4_Point_Eta",
  "StEHMEmcCat4_Point_Phi",
  "StEHMEmcCat4_Sigma_Eta",
  "StEHMEmcCat4_Sigma_Phi",
  "StEHMEmcCat4_Delta_Eta",
  "StEHMEmcCat4_Delta_Phi",
  "StEHMEmc_Cat4_Points_Multiplicity",
  "StEHMEmcCat4_Track_Momenta",
  "StEHM Point Flag",
  "StEHMQaGRpvtxDx",
  "StEHMQaGRpvtxDy",
  "StEHMQaGRpvtxDz",
  "StEHMQaBbcAdcES",
  "StEHMQaBbcAdcEL",
  "StEHMQaBbcAdcWS",
  "StEHMQaBbcAdcWL",
  "StEHMQaBbcTdcES",
  "StEHMQaBbcTdcEL",
  "StEHMQaBbcTdcWS",
  "StEHMQaBbcTdcWL",
  "StEHMQaFpdTop0",
  "StEHMQaFpdTop1",
  "StEHMQaFpdBottom0",
  "StEHMQaFpdBottom1",
  "StEHMQaFpdSouth0",
  "StEHMQaFpdSouth1",
  "StEHMQaFpdNorth0",
  "StEHMQaFpdNorth1",
  "StEHMQaFpdSums0",
  "StEHMQaFpdSums1",
  "StEHMQaFpdSums2",
  "StEHMQaFpdSums3",
  "StEHMQaFpdSums4",
  "StEHMQaFpdSums5",
  "StEHMQaFpdSums6",
  "StEHMQaFpdSums7",

  "StECLQaPointTpc",
  "StECLQaPointSvt",
  "StECLQaPointSvtLaser",
  "StECLQaPointFtpc",
  "StECLQaPointXYTpcE",
  "StECLQaPointXYTpcW",
  "StECLQaPointXYFtpcE",
  "StECLQaPointXYFtpcW",
  "StECLQaPointPadTimeFtpcE",
  "StECLQaPointPadTimeFtpcW",
  "StECLQaPointZhits",
  "StECLQaPointPhiT",
  "StECLQaPointZhitsS",
  "StECLQaPointPhiS",
  "StECLQaPointPadrowT",
  "StECLQaPointBarrelS",
  "StECLQaPointPlaneF",
  "StECLQaRichTot",
  "StECLQaGtrkZfTS",
  "StECLQaGtrkPhifTS",
  "StECLQaGtrkZfT",
  "StECLQaGtrkPhifT",
  "StECLQaGtrkXfYfFE",
  "StECLQaGtrkXfYfFW",
  "StECLQaGtrkPadTimeFtpcE",
  "StECLQaGtrkPadTimeFtpcW",
  "StECLQaGtrkPadfTEW",
  "StECLQaGtrkRTS",
  "StECLQaGtrkPlanefF",
  "StECLQaGtrkRnfTTS",
  "StECLQaGtrkRnmfTTS",
  "StECLQaGtrkRnmF",
  "StECLQaGtrkPsiTTS",
  "StECLQaGtrkPtTTS",
  "StECLQaGtrkEtaTTS",
  "StECLQaGtrkPsiF",
  "StECLQaGtrkPtF",
  "StECLQaGtrkEtaF",
  "StECLQaGtrkPF",
  "StECLQaGtrkChisq0T",
  "StECLQaGtrkChisq1T",
  "StECLQaGtrkChisq0F",
  "StECLQaGtrkChisq1F",
  "StECLQaGtrkFlag",
  "StECLQaGtrkGoodTot",
  "StECLQaGtrkNPntFitTTS",
  "StECLQaGtrkNPntF",
  "StECLQaGtrkGoodTTS",
  "StECLQaGtrkGoodF",
  "StECLQaGtrkFitPntLTTS",
  "StECLQaGtrkSImpactT",
  "StECLQaGtrkImpactTTS",
  "StECLQaGtrkImpactrTTS",
  "StECLQaGtrkImpactrF",
  "StECLQaGtrkDetId",
  "StECLQaGtrkTanlzf",
  "StECLQaGtrkTanlzfTS",
  "StECLQaPtrkPsiTTS",
  "StECLQaPtrkPtTTS",
  "StECLQaPtrkEtaTTS",
  "StECLQaPtrkPsiF",
  "StECLQaPtrkPtF",
  "StECLQaPtrkEtaF",
  "StECLQaPtrkMeanPtTTS",
  "StECLQaPtrkMeanEtaTTS",
  "StECLQaPtrkMeanPtF",
  "StECLQaPtrkMeanEtaF",
  "StECLQaPtrkGoodTTS",
  "StECLQaPtrkGoodF",
  "StECLQaPtrkChisq0TTS",
  "StECLQaPtrkChisq1TTS",
  "StECLQaPtrkChisq0F",
  "StECLQaPtrkChisq1F",
  "StECLQaPtrkFlag",
  "StECLQaPtrkImpactTTS",
  "StECLQaPtrkImpactrTTS",
  "StECLQaPtrkGlob",
  "StECLQaPtrkFitPntLTTS",
  "StECLQaNullPrimVtxMult",
  "StECLQaVtxPrXY",
  "StECLQaVtxPrZ",
  "StECLQaVtxSvtvsTpc",
  "StECLQaGtrkDcaBeamZ1",
  "StECLQaGtrkDcaBeamZ2",
  "StECLQaGtrkZdcaZf",
  "StECLQaGtrkZdcaPsi",
  "StECLQaGtrkZdcaTanl",
  "StECLQaPidGlobtrkDstdedxPVsDedx",
  "StECLQaDedxBBTTS",
  "StECLQaDedxDedx0F",
  "StECLQaEvsumTotChg",
  "StECLQaEvsumTotChgF",
  "StECLQaV0Vtx",
  "StECLQaV0VtxRDist",
  "StECLQaV0VtxZDist",
  "StECLQaV0VtxPhiDist",
  "StECLQaV0LambdaMass",
  "StECLQaV0K0Mass",
  "StECLQaXiVtxTot",
  "StECLQaKinkTot",
  "StECLQaGtrkRZf0",
  "StECLQaGtrkRZf0TS",
  "StECLQaPtrkRZf0",
  "StECLQaPtrkRZf0TS",
  "StECLbemcClNum",
  "StECLbemcClEnergy",
  "StECLbemcEta",
  "StECLbemcPhi",
  "StECLbsmdeClNum",
  "StECLbsmdeEta",
  "StECLbsmdpClNum",
  "StECLbsmdpPhi",
  "StECLEmcCat4_Point_Energy",
  "StECLEmcCat4_Point_Eta",
  "StECLEmcCat4_Point_Phi",
  "StECLEmcCat4_Sigma_Eta",
  "StECLEmcCat4_Sigma_Phi",
  "StECLEmcCat4_Delta_Eta",
  "StECLEmcCat4_Delta_Phi",
  "StECLEmc_Cat4_Points_Multiplicity",
  "StECLEmcCat4_Track_Momenta",
  "StECL Point Flag",
  "StECLQaGRpvtxDx",
  "StECLQaGRpvtxDy",
  "StECLQaGRpvtxDz",
  "StECLQaBbcAdcES",
  "StECLQaBbcAdcEL",
  "StECLQaBbcAdcWS",
  "StECLQaBbcAdcWL",
  "StECLQaBbcTdcES",
  "StECLQaBbcTdcEL",
  "StECLQaBbcTdcWS",
  "StECLQaBbcTdcWL",
  "StECLQaFpdTop0",
  "StECLQaFpdTop1",
  "StECLQaFpdBottom0",
  "StECLQaFpdBottom1",
  "StECLQaFpdSouth0",
  "StECLQaFpdSouth1",
  "StECLQaFpdNorth0",
  "StECLQaFpdNorth1",
  "StECLQaFpdSums0",
  "StECLQaFpdSums1",
  "StECLQaFpdSums2",
  "StECLQaFpdSums3",
  "StECLQaFpdSums4",
  "StECLQaFpdSums5",
  "StECLQaFpdSums6",
  "StECLQaFpdSums7",

  "StEHTQaPointTpc",
  "StEHTQaPointSvt",
  "StEHTQaPointSvtLaser",
  "StEHTQaPointFtpc",
  "StEHTQaPointXYTpcE",
  "StEHTQaPointXYTpcW",
  "StEHTQaPointXYFtpcE",
  "StEHTQaPointXYFtpcW",
  "StEHTQaPointPadTimeFtpcE",
  "StEHTQaPointPadTimeFtpcW",
  "StEHTQaPointZhits",
  "StEHTQaPointPhiT",
  "StEHTQaPointZhitsS",
  "StEHTQaPointPhiS",
  "StEHTQaPointPadrowT",
  "StEHTQaPointBarrelS",
  "StEHTQaPointPlaneF",
  "StEHTQaRichTot",
  "StEHTQaGtrkZfTS",
  "StEHTQaGtrkPhifTS",
  "StEHTQaGtrkZfT",
  "StEHTQaGtrkPhifT",
  "StEHTQaGtrkXfYfFE",
  "StEHTQaGtrkXfYfFW",
  "StEHTQaGtrkPadTimeFtpcE",
  "StEHTQaGtrkPadTimeFtpcW",
  "StEHTQaGtrkPadfTEW",
  "StEHTQaGtrkRTS",
  "StEHTQaGtrkPlanefF",
  "StEHTQaGtrkRnfTTS",
  "StEHTQaGtrkRnmfTTS",
  "StEHTQaGtrkRnmF",
  "StEHTQaGtrkPsiTTS",
  "StEHTQaGtrkPtTTS",
  "StEHTQaGtrkEtaTTS",
  "StEHTQaGtrkPsiF",
  "StEHTQaGtrkPtF",
  "StEHTQaGtrkEtaF",
  "StEHTQaGtrkPF",
  "StEHTQaGtrkChisq0T",
  "StEHTQaGtrkChisq1T",
  "StEHTQaGtrkChisq0F",
  "StEHTQaGtrkChisq1F",
  "StEHTQaGtrkFlag",
  "StEHTQaGtrkGoodTot",
  "StEHTQaGtrkNPntFitTTS",
  "StEHTQaGtrkNPntF",
  "StEHTQaGtrkGoodTTS",
  "StEHTQaGtrkGoodF",
  "StEHTQaGtrkFitPntLTTS",
  "StEHTQaGtrkSImpactT",
  "StEHTQaGtrkImpactTTS",
  "StEHTQaGtrkImpactrTTS",
  "StEHTQaGtrkImpactrF",
  "StEHTQaGtrkDetId",
  "StEHTQaGtrkTanlzf",
  "StEHTQaGtrkTanlzfTS",
  "StEHTQaPtrkPsiTTS",
  "StEHTQaPtrkPtTTS",
  "StEHTQaPtrkEtaTTS",
  "StEHTQaPtrkPsiF",
  "StEHTQaPtrkPtF",
  "StEHTQaPtrkEtaF",
  "StEHTQaPtrkMeanPtTTS",
  "StEHTQaPtrkMeanEtaTTS",
  "StEHTQaPtrkMeanPtF",
  "StEHTQaPtrkMeanEtaF",
  "StEHTQaPtrkGoodTTS",
  "StEHTQaPtrkGoodF",
  "StEHTQaPtrkChisq0TTS",
  "StEHTQaPtrkChisq1TTS",
  "StEHTQaPtrkChisq0F",
  "StEHTQaPtrkChisq1F",
  "StEHTQaPtrkFlag",
  "StEHTQaPtrkImpactTTS",
  "StEHTQaPtrkImpactrTTS",
  "StEHTQaPtrkGlob",
  "StEHTQaPtrkFitPntLTTS",
  "StEHTQaNullPrimVtxMult",
  "StEHTQaVtxPrXY",
  "StEHTQaVtxPrZ",
  "StEHTQaVtxSvtvsTpc",
  "StEHTQaGtrkDcaBeamZ1",
  "StEHTQaGtrkDcaBeamZ2",
  "StEHTQaGtrkZdcaZf",
  "StEHTQaGtrkZdcaPsi",
  "StEHTQaGtrkZdcaTanl",
  "StEHTQaPidGlobtrkDstdedxPVsDedx",
  "StEHTQaDedxBBTTS",
  "StEHTQaDedxDedx0F",
  "StEHTQaEvsumTotChg",
  "StEHTQaEvsumTotChgF",
  "StEHTQaV0Vtx",
  "StEHTQaV0VtxRDist",
  "StEHTQaV0VtxZDist",
  "StEHTQaV0VtxPhiDist",
  "StEHTQaV0LambdaMass",
  "StEHTQaV0K0Mass",
  "StEHTQaXiVtxTot",
  "StEHTQaKinkTot",
  "StEHTQaGtrkRZf0",
  "StEHTQaGtrkRZf0TS",
  "StEHTQaPtrkRZf0",
  "StEHTQaPtrkRZf0TS",
  "StEHTbemcClNum",
  "StEHTbemcClEnergy",
  "StEHTbemcEta",
  "StEHTbemcPhi",
  "StEHTbsmdeClNum",
  "StEHTbsmdeEta",
  "StEHTbsmdpClNum",
  "StEHTbsmdpPhi",
  "StEHTEmcCat4_Point_Energy",
  "StEHTEmcCat4_Point_Eta",
  "StEHTEmcCat4_Point_Phi",
  "StEHTEmcCat4_Sigma_Eta",
  "StEHTEmcCat4_Sigma_Phi",
  "StEHTEmcCat4_Delta_Eta",
  "StEHTEmcCat4_Delta_Phi",
  "StEHTEmc_Cat4_Points_Multiplicity",
  "StEHTEmcCat4_Track_Momenta",
  "StEHT Point Flag",
  "StEHTQaGRpvtxDx",
  "StEHTQaGRpvtxDy",
  "StEHTQaGRpvtxDz",
  "StEHTQaBbcAdcES",
  "StEHTQaBbcAdcEL",
  "StEHTQaBbcAdcWS",
  "StEHTQaBbcAdcWL",
  "StEHTQaBbcTdcES",
  "StEHTQaBbcTdcEL",
  "StEHTQaBbcTdcWS",
  "StEHTQaBbcTdcWL",
  "StEHTQaFpdTop0",
  "StEHTQaFpdTop1",
  "StEHTQaFpdBottom0",
  "StEHTQaFpdBottom1",
  "StEHTQaFpdSouth0",
  "StEHTQaFpdSouth1",
  "StEHTQaFpdNorth0",
  "StEHTQaFpdNorth1",
  "StEHTQaFpdSums0",
  "StEHTQaFpdSums1",
  "StEHTQaFpdSums2",
  "StEHTQaFpdSums3",
  "StEHTQaFpdSums4",
  "StEHTQaFpdSums5",
  "StEHTQaFpdSums6",
  "StEHTQaFpdSums7",

  "StEMBQaPointTpc",
  "StEMBQaPointSvt",
  "StEMBQaPointSvtLaser",
  "StEMBQaPointFtpc",
  "StEMBQaPointXYTpcE",
  "StEMBQaPointXYTpcW",
  "StEMBQaPointXYFtpcE",
  "StEMBQaPointXYFtpcW",
  "StEMBQaPointPadTimeFtpcE",
  "StEMBQaPointPadTimeFtpcW",
  "StEMBQaPointZhits",
  "StEMBQaPointPhiT",
  "StEMBQaPointZhitsS",
  "StEMBQaPointPhiS",
  "StEMBQaPointPadrowT",
  "StEMBQaPointBarrelS",
  "StEMBQaPointPlaneF",
  "StEMBQaRichTot",
  "StEMBQaGtrkZfTS",
  "StEMBQaGtrkPhifTS",
  "StEMBQaGtrkZfT",
  "StEMBQaGtrkPhifT",
  "StEMBQaGtrkXfYfFE",
  "StEMBQaGtrkXfYfFW",
  "StEMBQaGtrkPadTimeFtpcE",
  "StEMBQaGtrkPadTimeFtpcW",
  "StEMBQaGtrkPadfTEW",
  "StEMBQaGtrkRTS",
  "StEMBQaGtrkPlanefF",
  "StEMBQaGtrkRnfTTS",
  "StEMBQaGtrkRnmfTTS",
  "StEMBQaGtrkRnmF",
  "StEMBQaGtrkPsiTTS",
  "StEMBQaGtrkPtTTS",
  "StEMBQaGtrkEtaTTS",
  "StEMBQaGtrkPsiF",
  "StEMBQaGtrkPtF",
  "StEMBQaGtrkEtaF",
  "StEMBQaGtrkPF",
  "StEMBQaGtrkChisq0T",
  "StEMBQaGtrkChisq1T",
  "StEMBQaGtrkChisq0F",
  "StEMBQaGtrkChisq1F",
  "StEMBQaGtrkFlag",
  "StEMBQaGtrkGoodTot",
  "StEMBQaGtrkNPntFitTTS",
  "StEMBQaGtrkNPntF",
  "StEMBQaGtrkGoodTTS",
  "StEMBQaGtrkGoodF",
  "StEMBQaGtrkFitPntLTTS",
  "StEMBQaGtrkSImpactT",
  "StEMBQaGtrkImpactTTS",
  "StEMBQaGtrkImpactrTTS",
  "StEMBQaGtrkImpactrF",
  "StEMBQaGtrkDetId",
  "StEMBQaGtrkTanlzf",
  "StEMBQaGtrkTanlzfTS",
  "StEMBQaPtrkPsiTTS",
  "StEMBQaPtrkPtTTS",
  "StEMBQaPtrkEtaTTS",
  "StEMBQaPtrkPsiF",
  "StEMBQaPtrkPtF",
  "StEMBQaPtrkEtaF",
  "StEMBQaPtrkMeanPtTTS",
  "StEMBQaPtrkMeanEtaTTS",
  "StEMBQaPtrkMeanPtF",
  "StEMBQaPtrkMeanEtaF",
  "StEMBQaPtrkGoodTTS",
  "StEMBQaPtrkGoodF",
  "StEMBQaPtrkChisq0TTS",
  "StEMBQaPtrkChisq1TTS",
  "StEMBQaPtrkChisq0F",
  "StEMBQaPtrkChisq1F",
  "StEMBQaPtrkFlag",
  "StEMBQaPtrkImpactTTS",
  "StEMBQaPtrkImpactrTTS",
  "StEMBQaPtrkGlob",
  "StEMBQaPtrkFitPntLTTS",
  "StEMBQaNullPrimVtxMult",
  "StEMBQaVtxPrXY",
  "StEMBQaVtxPrZ",
  "StEMBQaVtxSvtvsTpc",
  "StEMBQaGtrkDcaBeamZ1",
  "StEMBQaGtrkDcaBeamZ2",
  "StEMBQaGtrkZdcaZf",
  "StEMBQaGtrkZdcaPsi",
  "StEMBQaGtrkZdcaTanl",
  "StEMBQaPidGlobtrkDstdedxPVsDedx",
  "StEMBQaDedxBBTTS",
  "StEMBQaDedxDedx0F",
  "StEMBQaEvsumTotChg",
  "StEMBQaEvsumTotChgF",
  "StEMBQaV0Vtx",
  "StEMBQaV0VtxRDist",
  "StEMBQaV0VtxZDist",
  "StEMBQaV0VtxPhiDist",
  "StEMBQaV0LambdaMass",
  "StEMBQaV0K0Mass",
  "StEMBQaXiVtxTot",
  "StEMBQaKinkTot",
  "StEMBQaGtrkRZf0",
  "StEMBQaGtrkRZf0TS",
  "StEMBQaPtrkRZf0",
  "StEMBQaPtrkRZf0TS",
  "StEMBbemcClNum",
  "StEMBbemcClEnergy",
  "StEMBbemcEta",
  "StEMBbemcPhi",
  "StEMBbsmdeClNum",
  "StEMBbsmdeEta",
  "StEMBbsmdpClNum",
  "StEMBbsmdpPhi",
  "StEMBEmcCat4_Point_Energy",
  "StEMBEmcCat4_Point_Eta",
  "StEMBEmcCat4_Point_Phi",
  "StEMBEmcCat4_Sigma_Eta",
  "StEMBEmcCat4_Sigma_Phi",
  "StEMBEmcCat4_Delta_Eta",
  "StEMBEmcCat4_Delta_Phi",
  "StEMBEmc_Cat4_Points_Multiplicity",
  "StEMBEmcCat4_Track_Momenta",
  "StEMB Point Flag",
  "StEMBQaGRpvtxDx",
  "StEMBQaGRpvtxDy",
  "StEMBQaGRpvtxDz",
  "StEMBQaBbcAdcES",
  "StEMBQaBbcAdcEL",
  "StEMBQaBbcAdcWS",
  "StEMBQaBbcAdcWL",
  "StEMBQaBbcTdcES",
  "StEMBQaBbcTdcEL",
  "StEMBQaBbcTdcWS",
  "StEMBQaBbcTdcWL",
  "StEMBQaFpdTop0",
  "StEMBQaFpdTop1",
  "StEMBQaFpdBottom0",
  "StEMBQaFpdBottom1",
  "StEMBQaFpdSouth0",
  "StEMBQaFpdSouth1",
  "StEMBQaFpdNorth0",
  "StEMBQaFpdNorth1",
  "StEMBQaFpdSums0",
  "StEMBQaFpdSums1",
  "StEMBQaFpdSums2",
  "StEMBQaFpdSums3",
  "StEMBQaFpdSums4",
  "StEMBQaFpdSums5",
  "StEMBQaFpdSums6",
  "StEMBQaFpdSums7"
