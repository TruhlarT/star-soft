// $Id: bfc.C,v 1.7 1998/08/10 02:35:13 fisyak Exp $
// $Log: bfc.C,v $
// Revision 1.7  1998/08/10 02:35:13  fisyak
// add laser
//
// Revision 1.6  1998/07/23 11:32:42  fisyak
// Small fixes
//
// Revision 1.5  1998/07/21 13:35:14  fine
// The new version of the macros: MakeHtmlTables and makedoc have been introduced
//
// Revision 1.4  1998/07/21 01:04:41  fisyak
// Clean up
//
// Revision 1.3  1998/07/21 00:36:49  fisyak
// tcl and tpt
//
// Revision 1.2  1998/07/20 15:08:19  fisyak
// Add tcl and tpt
//
{
   gSystem->Load("libasu.so");
   gSystem->Load("libdsl.so");
   gSystem->Load("St_base.so");
   gSystem->Load("St_Tables.so");
   gSystem->Load("libmsg.so");
   gSystem->Load("libtls.so");
   gSystem->Load("tpc.sl");
   gSystem->Load("St_tpc.so");
   gSystem->Load("svt.sl");
   gSystem->Load("St_svt.so");
   gSystem->Load("StChain.so");

#ifndef __CINT__
#include "Rtypes.h"
#include "St_XDFFile.h"
#include "St_DataSet.h"
#include "St_Module.h"
#include "St_Table.h"
#endif
//gSystem.Exec("rm *.log");
//  Char_t *filename = "/star/mds/data/SD98/auau200/bfc/central/hijing/set0001/regular/tss/auau_ce_b0-2_0001_0020.xdf";
//  Char_t *filename = "/afs/rhic/star/data/samples/event_0000050.xdf";
//  Char_t *filename = "/afs/rhic/star/data/samples/muons_100_ctb.dsl";
  Char_t *filename = "/afs/rhic/star/data/samples/muons_100_ctb.dsl";
  St_XDFFile xdffile_in(filename,"r");
// Create the main chain object
  StChain chain("StChain");
//  Create the makers to be called by the current chain
  St_xdfin_Maker xdfin("xdfin_Maker","event/geant");
  chain.SetInputXDFile(&xdffile_in);
  St_run_Maker run_Maker("run_Maker","run/params");
//  St_evg_Maker evg_Maker("evg_Maker","event");
  St_tss_Maker tss_Maker("tss_Maker","event/raw_data/tpc");
  St_srs_Maker srs_Maker("srs_Maker","event/data/svt");
  St_tcl_Maker tcl_Maker("tcl_Maker","event/data/tpc/hits");
  St_tpt_Maker tpt_Maker("tpt_Maker","event/data/tpc/tracks");
// Set parameters
  tss_Maker.adcxyzon();
  chain.PrintInfo();
// Init the mai chain and all its makers
  chain.Init();
// Prepare TCanvas to show some histograms created by makers
  gBenchmark->Start("bfc");
for (Int_t i=0;i<1;i++){
  chain.Make(i);
  //  histCanvas->Modified();
  //  histCanvas->Update();
  //  chain.Clear();
}
  gBenchmark->Stop("bfc");
  gBenchmark->Print("bfc");
  TBrowser b;
}
