// $Id: StHistUtil.cxx,v 1.28 2000/08/18 20:30:13 lansdell Exp $
// $Log: StHistUtil.cxx,v $
// Revision 1.28  2000/08/18 20:30:13  lansdell
// added global track probability of fit histogram; extra, empty page is currently printed for some reason, still checking
//
// Revision 1.27  2000/08/17 21:13:53  lansdell
// loop over all TPC hits for the z-hit distribution histogram
//
// Revision 1.26  2000/08/17 18:52:27  lansdell
// added z distribution of hits histogram to StEventQA set
//
// Revision 1.25  2000/07/31 19:29:47  lansdell
// primary vertex check histogram now contains entries for events with or without a primary vertex (with = 1, without = -1)
//
// Revision 1.24  2000/07/28 19:25:19  lansdell
// added histogram of number of events without a primary vertex
//
// Revision 1.23  2000/07/26 19:57:48  lansdell
// new histograms and functionality added (e.g., overlay several histograms, new printlist option qa_shift)
//
// Revision 1.22  2000/07/07 23:22:22  lansdell
// added year1 PrintList option for QA and EventQA histograms
//
// Revision 1.21  2000/07/07 03:52:32  genevb
// AddHist improvements
//
// Revision 1.20  2000/06/23 18:05:36  kathy
// add new method PrintInfoHists which prints info about hist to screen & file -- name,entries,mean,rms
//
// Revision 1.19  2000/06/23 15:26:22  kathy
// added method to return the copied array & it's size
//
// Revision 1.18  2000/06/23 14:36:08  kathy
// comment out print statements and add some documentation
//
// Revision 1.17  2000/06/23 14:31:52  kathy
// put 2 new methods in: CopyHists (must be used first), AddHists
//
// Revision 1.16  2000/05/25 03:47:09  lansdell
// changed default logy list to reflect new QA histograms
//
// Revision 1.15  2000/02/29 18:19:47  kathy
// fix code so it will handle without crashing when there is no histogram branch of the one requested
//
// Revision 1.14  2000/02/28 19:03:01  kathy
// print list for FlowTag Maker histograms
//
// Revision 1.13  2000/02/15 22:11:18  lansdell
// simplified default logy hist code
//
// Revision 1.12  2000/02/11 15:54:06  kathy
// set point id histogram to logY scale
//
// Revision 1.11  2000/02/10 22:21:57  kathy
// turned the new impact param hist to logY scale
//
// Revision 1.10  2000/02/08 19:45:31  kathy
// added a few more hist to print list for cosmics
//
// Revision 1.9  2000/02/02 16:35:48  kathy
// fixing hist names in default lists
//
// Revision 1.8  2000/02/01 00:10:00  lansdell
// added check on max value of bins to Overlay methods; set 2D overlay to box plot
//
// Revision 1.7  2000/01/31 17:22:31  kathy
// put chisq hist for globtrk,primtrk tpc+svt in logY scale
//
// Revision 1.6  2000/01/31 14:59:13  kathy
// add default print list for ftpc
//
// Revision 1.5  2000/01/28 17:53:41  lansdell
// split overlay method into Overlay1D and Overlay2D
//
// Revision 1.4  2000/01/27 18:30:12  kathy
// add Curtis' new method which reads in 2 histograms and overlays them - Overlay2Hists
//
// Revision 1.3  2000/01/27 16:18:50  kathy
// adding more hist names in setdefaultlogx list to make tom trainor happier
//
// Revision 1.2  2000/01/26 19:29:26  kathy
// add methods SetDefaultLogXList,AddToLogXList,ExamineLogXList,RemoveFromLogXList - requested by T.Trainor - impact param hists are now draw with LogX scale
//
// Revision 1.1  2000/01/18 16:42:40  kathy
// move StHistUtil class from St_QA_Maker directory and put into StAnalysisUtilities
//
// Revision 1.27  2000/01/13 16:22:32  kathy
// changed DrawHist method so that it now correctly prints from a list (if printlist is available)
//
// Revision 1.26  2000/01/12 23:17:49  kathy
// changes so it can print from a list
//
// Revision 1.24  2000/01/12 16:49:04  kathy
// add new methods so that one can set a list which will be used to print,draw a subset of the histograms corresponding to a given maker; new methods are SetDefaultPrintList,AddToPrintList,RemoveFromPrintList,ExaminePrintList; can't test it yet because seems can't find directory of histograms in DEV anymore and there are conflicts in NEW; updates to DrawHist method to use this new list are not done yet
//
// Revision 1.23  1999/12/29 17:52:30  kathy
// changes to hist limits and list of logY scales
//
// Revision 1.22  1999/12/22 17:16:43  kathy
// fix so that it doesn't try to print/draw in logY scale if the max entries in any bins is 0
//
// Revision 1.21  1999/12/22 16:32:28  kathy
// check if histogram has entries before setting logY scale
//
// Revision 1.20  1999/12/21 15:50:32  kathy
// got page numbers to print out properlycvs -n update - thanks Jeff & Valery!
//
// Revision 1.19  1999/12/20 17:31:25  kathy
// updates to write page numbers on output histogram ps file
//
// Revision 1.18  1999/12/17 22:11:32  kathy
// add psi vs phi hist, change limits
//
// Revision 1.17  1999/12/16 23:12:03  kathy
// fixed list of default histograms, had wrong title and added a few for tables and stevent; rescaled some histograms and fixed titles in booking
//
// Revision 1.16  1999/12/16 03:56:20  lansdell
// mirrored Kathy's changes in St_QA_Maker.cxx: separated tpc and tpc+svt histograms for global tracks using StEvent; added r0,phi0,z0,curvature histograms for global tracks in the tpc
//
// Revision 1.15  1999/12/15 20:32:17  kathy
// separated the tpc and tpc+svt histograms for globtrk table; had to book and fill new histograms, add histograms to default logy list AND had to change what values of iflag I cut on for filling each different type of track in makehistglob method
//
// Revision 1.14  1999/12/15 18:31:05  kathy
// added 4 new histogram to globtrk for tpc - r0,phi0,z0,curvature; also put 3 of these in default logY list; also changed scale on iflag hist. for globtrk & primtrk
//
// Revision 1.13  1999/12/13 20:08:37  lansdell
// added pt vs eta in ftpc histogram to match table QA changes; updated logy scale histograms
//
// Revision 1.12  1999/12/10 17:38:24  kathy
// now reprint canvas on each page of postscript output file; also changed some histogram limits
//
// Revision 1.11  1999/12/08 22:58:16  kathy
// changed histogram limits and made names smaller
//
// Revision 1.10  1999/12/07 23:14:18  kathy
// fix primary vtx histograms for dst tables; split apart the ftpc and tpc in the dedx histograms
//
// Revision 1.9  1999/12/07 21:54:15  kathy
// added date and time to DrawHist method in StHistUtil class so that this is printed at bottom right of histogram output
//
// Revision 1.7  1999/12/06 22:25:05  kathy
// split apart the tpc and ftpc (east & west) histograms for the globtrk table; had to add characters to end of each histogram pointer to differentiate the different ones; updated the default list of hist to be plotted with logy scale
//
// Revision 1.6  1999/11/24 14:55:32  lansdell
// log scale fixed for QA histograms (gene)
//
// Revision 1.5  1999/11/22 22:46:41  lansdell
// update to identify histogram method used (StEvent or DST tables) by Gene; StEventQAMaker code partially completed (run bfcread_dst_EventQAhist.C)
//
// Revision 1.4  1999/11/18 18:18:17  kathy
// adding default logY hist list for EventQA histogram set
//
// Revision 1.3  1999/11/05 22:26:01  kathy
// now allow setting of global title from a method
//
// Revision 1.2  1999/11/05 21:51:58  kathy
// write title at top of each page of histograms in DrawHists method
//
// Revision 1.1  1999/09/20 20:12:15  kathy
// moved the histogram utility methods out of St_QA_Maker and into StHistUtil because they can really be used by any Maker and associated histograms
//

///////////////////////////////////////////////////////////////////////////////
// Histogram Utility methods for use with star makers and bfc output
///////////////////////////////////////////////////////////////////////////////
                                                                          

#include <iostream.h>
#include <fstream.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <strstream.h>

#include "PhysicalConstants.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TObjString.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TString.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TDatime.h"

#include "StChain.h"
#include "St_DataSetIter.h"
#include "StMaker.h"

#include "StHistUtil.h"

ClassImp(StHistUtil)
  
//_____________________________________________________________________________

// Constructor

StHistUtil::StHistUtil(){

  m_ListOfLogY = 0;
  m_ListOfLogX = 0;
  m_ListOfPrint = 0;
  m_HistCanvas = 0;


}
//_____________________________________________________________________________

// Destructor

StHistUtil::~StHistUtil(){
  SafeDelete(m_HistCanvas);
  if (m_ListOfLogY) {
    m_ListOfLogY->Delete();
    SafeDelete(m_ListOfLogY);
  }
  if (m_ListOfLogX) {
    m_ListOfLogX->Delete();
    SafeDelete(m_ListOfLogX);
  }
  if (m_ListOfPrint) {
    m_ListOfPrint->Delete();
    SafeDelete(m_ListOfPrint);
  }
  if (newHist){
    delete [] newHist;
  }
}
//_____________________________________________________________________________

Int_t StHistUtil::DrawHists(Char_t *dirName) 
{
// Method DrawHists -->
// Plot the selected  histograms and generate the postscript file as well 
  
  cout << " **** Now in StHistUtil::DrawHists  **** " << endl;


// set output ps file name
  TPostScript *psf = 0;
  const Char_t *psfileName = m_PsFileName.Data();
  if (!m_PsFileName.IsNull()) psf = new TPostScript((char *)psfileName);  
  
// set global title which goes at top of each page of histograms
  const Char_t *gtitle = m_GlobalTitle.Data();

//set Style of Plots
  const Int_t numPads = m_PadColumns*m_PadRows;  
// SetPaperSize wants width & height in cm: A4 is 20,26 & US is 20,24
  gStyle->SetPaperSize(m_PaperWidth,m_PaperHeight); 

  gStyle->SetOptStat(111111);
  gStyle->SetStatStyle(0);

//

//setup canvas
  SafeDelete(m_HistCanvas);

// TCanvas wants width & height in pixels (712 x 950 corresponds to A4 paper)
//                                        (600 x 780                US      )
  //  TCanvas *HistCanvas = new TCanvas("CanvasName","Canvas Title",30*m_PaperWidth,30*m_PaperHeight);
    TCanvas *HistCanvas = new TCanvas("CanvasName"," STAR Maker Histogram Canvas",600,780);

  //  HistCanvas->SetFillColor(19);
  // but now we have paper size in cm
  //  HistCanvas->Range(0,0,20,24);
  //  Can set range to something which makes it equivalent to canvas but is 0,1 by default
  //HistCanvas->SetBorderSize(2);  

// Range for all float numbers used by ROOT methods is now 0,1 by default!

// order of PaveLabel is x1,y1,x2,y2 - fraction of pad (which is the canvas now)
// option = br means the shadow of box starts at bottom right
//    myself, I'd like to get rid of the stupid shadow that somebody decided I need!

// write title at top of canvas - first page
   TPaveLabel *Ltitle = new TPaveLabel(0.1,0.96,0.9,1.0,(char *)gtitle,"br");
   Ltitle->SetFillColor(18);
   Ltitle->SetTextFont(32);
   Ltitle->SetTextSize(0.5);
   // Ltitle->SetTextColor(49);
   Ltitle->Draw();

// now put in date & time at bottom right of canvas - first page
  TDatime HistTime;
  const Char_t *myTime = HistTime.AsString();
  TPaveLabel *Ldatetime = new TPaveLabel(0.7,0.01,0.95,0.03,myTime,"br");
  Ldatetime->SetTextSize(0.6);
  Ldatetime->Draw();


// now put in page # at bottom left of canvas - first page
    Int_t Ipagenum=1;
  //convert to character
    Char_t Ctmp[10];
    ostrstream Cpagenum(Ctmp,10);
    Cpagenum << Ipagenum << ends;
//    cout << " Ipage " << Ipagenum << " Cpage " << Ctmp << endl;
  TPaveLabel *Lpage = new TPaveLabel(0.1,0.01,0.2,0.03,Ctmp,"br");
  Lpage->SetTextSize(0.6);
  Lpage->Draw();

// Make 1 big pad on the canvas - make it a little bit inside the  canvas 
//    - must cd to get to this pad! 
// order is x1 y1 x2 y2 
  TPad *graphPad = new TPad("PadName","Pad Title",0.0,0.05,1.00,0.95);
  graphPad->Draw();
  graphPad->cd();

// Now divide the canvas (should work on the last pad created) 
  graphPad->Divide(m_PadColumns,m_PadRows);

  if (psf) psf->NewPage();
  const Char_t *firstHistName = m_FirstHistName.Data();
  const Char_t *lastHistName  = m_LastHistName.Data();

  //  cout << " **** Now finding hist **** " << endl;

// Now find the histograms
// get the TList pointer to the histograms:
  TList  *dirList = 0;
  dirList = FindHists(dirName);
 
  if (!dirList) cout << " DrawHists - histograms not available! " << endl;

  Int_t padCount = 0;
  
// Create an iterator called nextHist - use TIter constructor
  TIter nextHist(dirList);
  Int_t histCounter = 0;
  Int_t histReadCounter = 0;
  Bool_t started = kFALSE;

//NOTE!! the () used by nextHist below is an overloaded operator 
//     in TIter that returns a TObject* 

  TObject *obj = 0;
  Int_t chkdim=0;
  while ((obj = nextHist())) {
//   cout << " **** Now in StHistUtil::DrawHists - in loop: " << endl;
//   cout << "               name = " << obj->GetName() << endl;


    if (obj->InheritsFrom("TH1")) { 
//    cout << " **** Now in StHistUtil::DrawHists - obj->InheritsFrom(TH1)  **** " << endl;
      histReadCounter++;
      printf(" %d. Reading ... %s::%s; Title=\"%s\"\n",histReadCounter,obj->ClassName(),obj->GetName(), obj->GetTitle());
      if (! started && (strcmp("*",firstHistName)==0 || strcmp(obj->GetName(),firstHistName)==0 ))  started = kTRUE;

// Here is the actual loop over histograms !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if (started) {
	if (strcmp(obj->GetName(),lastHistName)==0) started = kFALSE;
	histCounter++;

// Switch to a new page.....................................................
	if (padCount == numPads) {
	  if (psf) psf->NewPage();

// update the page number
          Ipagenum++;
          ostrstream Cpagenumt(Ctmp,10);
          Cpagenumt << Ipagenum << ends;
//          cout << " Ipage " << Ipagenum << " Cpage " << Ctmp << endl;
          Lpage->SetLabel(Ctmp);

// must redraw the histcanvas for each new page of postscript file!
	  //    HistCanvas->cd();
        HistCanvas->Modified();
        HistCanvas->Update();
	  padCount=0;
	}
//...........................................................................


// If there's no print list, then print all histograms in directory
// If there is a print list, then only print if hist name is on list
	//cout << " print list pointer = " << m_ListOfPrint << endl;
        //cout << "     size of list   = " << m_ListOfPrint->GetSize() << endl;
 
	if (!m_ListOfPrint || (m_ListOfPrint && m_ListOfPrint->FindObject(obj->GetName()) )){

// this histogram will actually be printed/drawn!!
        printf("  -   %d. Drawing ... %s::%s; Title=\"%s\"\n",
	  histCounter,obj->ClassName(),obj->GetName(), obj->GetTitle());

// go to next pad 
        graphPad->cd(++padCount);
//NOTE! (13jan00,kt) -->  this cd is really acting on gPad!!!
//   --> gPad is a global variable & one uses it to set attributes of current pad
//  --> you can see the full list of global variables by starting ROOT and entering .g
//  --> to find the full list of commands, type ? in ROOT 

// set logY & logX scale off
	 gPad->SetLogy(0);
	 gPad->SetLogx(0);	  

// Set logY scale on if: there is a loglist, if the hist name is on the list, if it has entries
//    and if the max entries in all bins is > 0
	if (m_ListOfLogY && m_ListOfLogY->FindObject(obj->GetName()) && ((TH1 *)obj)->GetEntries()
            && ((TH1 *)obj)->GetMaximum() ){
	  gPad->SetLogy(1);
          cout << "             -- Will draw in logY scale: " << obj->GetName() <<endl;
	 }


// Set logX scale on if: there is a loglist, if the hist name is on the list, if it has entries
//    and if the max entries in all bins is > 0
	if (m_ListOfLogX && m_ListOfLogX->FindObject(obj->GetName()) && ((TH1 *)obj)->GetEntries()
            && ((TH1 *)obj)->GetMaximum() ){
	  gPad->SetLogx(1);
          cout << "             -- Will draw in logX scale: " << obj->GetName() <<endl;
	 }


// check dimension of histogram
          chkdim = ((TH1 *)obj)->GetDimension();
	  //	  cout << " name " << obj->GetName() << " dimension " << chkdim << endl;

// actually draw,print
          if (chkdim == 2) obj->Draw("box");
          else {
	    TH1F *tempHist = (TH1F*)obj;
	    tempHist->SetLineWidth(5);
	    tempHist->Draw();
	  }
	  if (gPad) gPad->Update();
        }
      }

//NOTE! (13jan00,kt) 
//--> obj->Draw just appends the histogram to the list
//    --> you must update the current pad (gPad) or the whole big pad (graphPad)
//        to actually see the stupid thing

// just ended  actual loop over histograms !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    }
  }

  if (psf) {
    psf->Close();
    delete psf;
  }
  return histCounter;
}
 
//_____________________________________________________________________________


TList* StHistUtil::FindHists(Char_t *dirName) 
{  

// NOTE - must have already used method SetPntrToMaker to get the
//       pointer m_PntrToMaker  to an StMaker class!
//

//  Method 1 ------------------------------------------------
// Method FindHists -->
// Find pointer to histograms under a Maker

  TList *dList=0;

  cout << " Beg: FindHists, dList pointer = " << dList << endl;

//---- First look under Maker for histograms ==>
//They  should show up in your Maker's directory, so search for them there,
//     i.e. MakerName/.hist is where they'd be
// Note: Histograms is a method of StMaker
//---- If you have a chain, you'll always have the .hist directory, so
//     have to check if there's really anything there (so use First method)

//
  StMaker *temp = m_PntrToMaker->GetMaker(dirName);
    if (temp) {
      cout << "FindHists - found pointer to maker" << endl;
      dList = temp->Histograms();
    }

// Now check to see if any histograms exist here (look for something in
//  the list (test)
  TObject *test=0;
  if (dList) test = dList->First();
  if (test){ 
      cout << " FindHists - found hist. in Maker-Branch " << endl;
     }

    cout << " Mid: FindHists, dList pointer = " << dList << endl;
    cout << " Mid: FindHists, test pointer =  " << test << endl;

// If you have the pointer but the hist. really aren't here, set
//  the pointer back to zero
  if (!test) dList = 0;

  cout << " Mid2: FindHists, dList pointer = " << dList << endl;
  cout << " Mid2: FindHists, test pointer =  " << test << endl;


  if (!dList) {

// Method 2 -----------------------------------------------------

//-------------- Now try and see if they're in histBranch from output of bfc


  St_DataSet *hist=0;
  hist = m_PntrToMaker->GetDataSet("hist");
  if (hist) {
//    hist->ls(9);

// must look in dirNameHist 
// use TString to append "Hist" to the dirName
// += is overloaded operator of TString

    TString hBN(dirName);
    hBN += "Hist";
    
//find particular branch
    St_DataSet *QAH = 0;
    QAH = hist->Find(hBN.Data());
// or can create iterator and look over all branches

//now get the list of histograms
    if (QAH)  {
      dList = (TList *)QAH->GetObject();
    }

  }

// now have we found them?
  if (dList){ 
      cout << " FindHists - found hist. in histBranch, with name:  " 
	   << dirName <<  endl;
     }
  else { 
         cout << " FindHists - histogram branch has not been found for branch --> "
	   << dirName <<  endl;
     }

  }

  cout << " FindHists, dList pointer = " << dList << endl;
  
 
 return dList;
}
//_____________________________________________________________________________


Int_t StHistUtil::ListHists(Char_t *dirName) 
{  
// Method ListHists -->
// List of all histograms

  cout << " **** Now in StHistUtil::ListHists **** " << endl;

// get the TList pointer to the histograms:
  TList  *dirList = 0;
  dirList = FindHists(dirName);

  if (!dirList) cout << " ListHists - histograms not available! " << endl;

//Now want to loop over all histograms
// Create an iterator
  TIter nextObj(dirList);
  Int_t histReadCount = 0;
  TObject *obj = 0;

// use = here instead of ==, because we are setting obj equal to nextObj and then seeing if it's T or F
  while ((obj = nextObj())) {

// now check if obj is a histogram
    if (obj->InheritsFrom("TH1")) {
 
      histReadCount++;
//  \n means newline, \" means print a quote
//      printf(" %d. Have histogram Type %s, Name %s with Title=\"%s\"\n",histReadCount,obj->ClassName(),obj->GetName(),obj->GetTitle());
            cout << " ListHists: Hist No. " << histReadCount << ", Type: " << obj->ClassName() 
           << ", Name: " << obj->GetName() << ", Title \"" << obj->GetTitle() << "\"  "<< endl; 
    }
  }

  cout << " ListHists: Total No. Histograms Booked  = " << histReadCount <<endl;
  return histReadCount;
}


//_____________________________________________________________________________

Int_t StHistUtil::PrintInfoHists(TList *dirList,  const Char_t *fname )
{  

  cout << " **** Now in StHistUtil::PrintInfoHists **** " << endl;
  cout << " output file = " << fname << endl;

  ofstream fout(fname);

  if (!dirList) cout << " PrintInfoHists - histograms not available! " << endl;

  Int_t histInfoCount = 0;

  if (dirList){

//Now want to loop over all histograms
// Create an iterator
    TIter nextObj(dirList);
    TObject *obj = 0;

    cout << " Hist #, Name, #Entries, Mean, RMS " << endl;
    fout << " Hist #, Name, #Entries, Mean, RMS " << endl;

// use = instead of ==, because we are setting obj equal to nextObj and then seeing if it's T or F

    while ((obj = nextObj())) {

// now check if obj is a histogram
      if (obj->InheritsFrom("TH1")) {
 
        histInfoCount++;

        cout << 
              histInfoCount << " " <<
              obj->GetName() << " " <<
              ((TH1 *)obj)->GetEntries() << " " <<
              ((TH1 *)obj)->GetMean() << " " <<
              ((TH1 *)obj)->GetRMS() << " " <<
              endl;

        fout << 
              histInfoCount << " " <<
              obj->GetName() << " " <<
              ((TH1 *)obj)->GetEntries() << " " <<
              ((TH1 *)obj)->GetMean() << " " <<
              ((TH1 *)obj)->GetRMS() << " " <<
              endl;

      }
    }
  } // if dirList

  cout << " PrintInfoHists: # hist read  = " << histInfoCount <<endl;

  return histInfoCount;
}


//_____________________________________________________________________________


Int_t StHistUtil::CopyHists(TList *dirList)
{  
  cout << " **** Now in StHistUtil::CopyHists **** " << endl;

  if (!dirList) cout << " StHistUtil::CopyHists - histogram Pointer not set! " << endl;

// create array of pointers to the new histograms I will create
 Int_t ilg = 0;
 cout << " StHistUtil::CopyHists - max # hist to copy (hardwired) = " << 
   maxHistCopy << endl;
 for (ilg=0;ilg<maxHistCopy;ilg++) {
      newHist[ilg]=0;
 }

  Int_t ijk=0;
  Int_t histCopyCount = 0;

  if (dirList){
   TIter nextObj(dirList);
   TObject *obj = 0;
    while ((obj = nextObj())) {    
     if (obj->InheritsFrom("TH1")) {
       histCopyCount++;         
       if (ijk<maxHistCopy){
         newHist[ijk] = ((TH1 *)obj->Clone());
       } // if ijk
       ijk++;
     }   // if obj
    }    // while obj
  }      // if dirList

  cout << " ListHists: Total No. Histograms Copied  = " << 
        histCopyCount <<endl;

// Now see if we can find these copies:
 // Int_t imk = 0;
 //for (imk=0;imk<histCopyCount;imk++) {
 //  if (newHist[imk]->InheritsFrom("TH1")) {       
 //        cout << " !!! NEW Type: " << newHist[imk]->ClassName() << 
 //             ", Name: "    << newHist[imk]->GetName() << 
 //             ", Title: "   << newHist[imk]->GetTitle() << 
 //	    ", Max: " << ((TH1 *)newHist[imk])->GetMaximum() << endl; 
 //  }
 //} 

  return histCopyCount;
}

//_____________________________________________________________________________

// **** IMPORTANT! ***** 
//  THIS METHOD ASSUMES YOU HAVE ALREADY USED CopyHists TO PUT
//  HISTOGRAMS FROM 1 FILE INTO newHist array
//   -- this method is used in subsequent files!

Int_t StHistUtil::AddHists(TList *dirList,Int_t numHistCopy)
{  
  cout << " **** Now in StHistUtil::AddHists **** " << endl;
  //  cout << " num hists to copy = " << numHistCopy << endl;

  if (!dirList) cout << 
        " StHistUtil::AddHists - histogram Pointer not set! " << endl;

  Int_t histAddCount = 0;

  if (dirList){
    if (numHistCopy < 0) numHistCopy = dirList->GetSize();
    TIter nextObj(dirList);
    TObject *obj = 0;

    while ((obj = nextObj())) {
      if (obj->InheritsFrom("TH1")) {
// now want to add these histograms to the copied ones:
	Int_t imk = 0;
	for (imk=0;imk<numHistCopy;imk++) {
	  if (strcmp( (newHist[imk]->GetName()), (obj->GetName()) )==0) {
	    //cout << "  ---- hist num to add --- " << imk << endl;
	    newHist[imk]->Add((TH1 *)obj);
	    histAddCount++;
	    //cout << " !!! Added histograms with Name: " << newHist[imk]->GetName() <<  endl;

	  } // strcmp
	}  // loop over imk
      }   // if obj inherits from th1
    }    //while
  } //dirlist

  cout << " StHistUtil::AddHists: Total No. Histograms Added  = " << 
        histAddCount <<endl;


  return histAddCount;
}

//_____________________________________________________________________________


Int_t StHistUtil::ExamineLogYList() 
{  
// Method ExamineLogYList
// List of all histograms that will be drawn with logy scale

  cout << " **** Now in StHistUtil::ExamineLogYList **** " << endl;

// m_ListOfLogY -  is a list of log plots
// construct a TObject
  TObject *obj = 0;
// construct a TIter ==>  () is an overloaded operator in TIter
  TIter nextObj(m_ListOfLogY);
  Int_t LogYCount = 0;

// use = here instead of ==, because we are setting obj equal to nextObj and then seeing if it's T or F
  while ((obj = nextObj())) {

    cout << " StHistUtil::ExamineLogYList has hist " <<  obj->GetName() << endl;
    LogYCount++;

  }

  cout << " Now in StHistUtil::ExamineLogYList, No. Hist. in LogY scale = " << LogYCount <<endl;
  return LogYCount;
}

//_____________________________________________________________________________


Int_t StHistUtil::ExamineLogXList() 
{  
// Method ExamineLogXList
// List of all histograms that will be drawn with logX scale

  cout << " **** Now in StHistUtil::ExamineLogXList **** " << endl;

// m_ListOfLogX -  is a list of log plots
// construct a TObject
  TObject *obj = 0;
// construct a TIter ==>  () is an overloaded operator in TIter
  TIter nextObj(m_ListOfLogX);
  Int_t LogXCount = 0;

// use = here instead of ==, because we are setting obj equal to nextObj and then seeing if it's T or F
  while ((obj = nextObj())) {

    cout << " StHistUtil::ExamineLogXList has hist " <<  obj->GetName() << endl;
    LogXCount++;

  }

  cout << " Now in StHistUtil::ExamineLogXList, No. Hist. in LogX scale = " << LogXCount <<endl;
  return LogXCount;
}

//_____________________________________________________________________________


Int_t StHistUtil::ExaminePrintList() 
{  
// Method ExaminePrintList
// List of all histograms that will be drawn,printed

  cout << " **** Now in StHistUtil::ExaminePrintList **** " << endl;

// m_ListOfPrint -  is a list of hist to print,draw

// check if there is a list
  if (!m_ListOfPrint){
    cout << "      no subset print list was setup - all hist in directory will be printed " << endl;
    //    return PrintCount;
    return 0;
  }

// construct a TObject
  TObject *obj = 0;

// construct a TIter ==>  () is an overloaded operator in TIter
  TIter nextObj(m_ListOfPrint);
  Int_t PrintCount = 0;

// use = here instead of ==, because we are setting obj equal to nextObj and then seeing if it's T or F
  while ((obj = nextObj())) {

    cout << " StHistUtil::ExaminePrintList has hist " <<  obj->GetName() << endl;
    PrintCount++;

  }

  cout << " Now in StHistUtil::ExaminePrintList, No. Hist. to Print,Draw = " << PrintCount <<endl;
  return m_ListOfPrint->GetSize();
}

//_____________________________________________________________________________


Int_t StHistUtil::AddToLogYList(const Char_t *HistName){  
// Method AddToLogYList
//   making list of all histograms that we want drawn with LogY scale

//  cout << " **** Now in StHistUtil::AddToLogYList  **** " << endl;

// Since I'm creating a new list, must delete it in the destructor!!
//make a new TList on heap(persistant); have already defined m_ListOfLogY in header file
   if (!m_ListOfLogY) m_ListOfLogY = new TList;

// the add method for TList requires a TObject input  (also can use TObjString)
// create TObjString on heap
   TObjString *HistNameObj = new TObjString(HistName);

// - check if it's already on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfLogY->FindObject(HistName);
// now can use Add method of TList
    if (!lobj) {
       m_ListOfLogY->Add(HistNameObj);
//       cout << " StHistUtil::AddToLogYList: " << HistName  <<endl;
    }
    else  cout << " StHistUtil::AddToLogYList: " << HistName << " already in list - not added" <<endl;
 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfLogY->GetSize();
}


//_____________________________________________________________________________


Int_t StHistUtil::AddToLogXList(const Char_t *HistName){  
// Method AddToLogXList
//   making list of all histograms that we want drawn with LogX scale

//  cout << " **** Now in StHistUtil::AddToLogXList  **** " << endl;

// Since I'm creating a new list, must delete it in the destructor!!
//make a new TList on heap(persistant); have already defined m_ListOfLogX in header file
   if (!m_ListOfLogX) m_ListOfLogX = new TList;

// the add method for TList requires a TObject input  (also can use TObjString)
// create TObjString on heap
   TObjString *HistNameObj = new TObjString(HistName);

// - check if it's already on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfLogX->FindObject(HistName);
// now can use Add method of TList
    if (!lobj) {
       m_ListOfLogX->Add(HistNameObj);
//       cout << " StHistUtil::AddToLogXList: " << HistName  <<endl;
    }
    else  cout << " StHistUtil::AddToLogXList: " << HistName << " already in list - not added" <<endl;
 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfLogX->GetSize();
}


//_____________________________________________________________________________


Int_t StHistUtil::AddToPrintList(const Char_t *HistName){  

// Method AddToPrintList
//   making list of all histograms that we want drawn,printed

//  cout << " **** Now in StHistUtil::AddToPrintList  **** " << endl;

// Since I'm creating a new list, must delete it in the destructor!!
//make a new TList on heap(persistant); have already defined m_ListOfPrint in header file
   if (!m_ListOfPrint) m_ListOfPrint = new TList;

// the add method for TList requires a TObject input  (also can use TObjString)
// create TObjString on heap
   TObjString *HistNameObj = new TObjString(HistName);

// - check if it's already on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfPrint->FindObject(HistName);

// now can use Add method of TList
    if (!lobj) {
       m_ListOfPrint->Add(HistNameObj);
//       cout << " StHistUtil::AddToPrintList: " << HistName  <<endl;
    }
    else  cout << " StHistUtil::AddToPrintList: " << HistName << " already in list - not added" <<endl;
 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfPrint->GetSize();

}

//_____________________________________________________________________________

Int_t StHistUtil::RemoveFromLogYList(const Char_t *HistName){  
// Method RemoveFromLogYList
//   remove hist from  list  that we want drawn with LogY scale

//  cout << " **** Now in StHistUtil::RemoveFromLogYList  **** " << endl;

// check if list exists:
  if (m_ListOfLogY) {
    
// the remove method for TList requires a TObject input  
// - check if it's  on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfLogY->FindObject(HistName);
// now can use Remove method of TList
    if (lobj) {
      m_ListOfLogY->Remove(lobj);
      cout << " RemoveLogYList: " << HistName << " has been removed from list" <<endl;
    }
    else  cout << " RemoveLogYList: " << HistName << " not on list - not removing" <<endl;

  } 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfLogY->GetSize();
}


//_____________________________________________________________________________

Int_t StHistUtil::RemoveFromLogXList(const Char_t *HistName){  
// Method RemoveFromLogXList
//   remove hist from  list  that we want drawn with LogX scale

//  cout << " **** Now in StHistUtil::RemoveFromLogXList  **** " << endl;

// check if list exists:
  if (m_ListOfLogX) {
    
// the remove method for TList requires a TObject input  
// - check if it's  on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfLogX->FindObject(HistName);
// now can use Remove method of TList
    if (lobj) {
      m_ListOfLogX->Remove(lobj);
      cout << " RemoveLogXList: " << HistName << " has been removed from list" <<endl;
    }
    else  cout << " RemoveLogXList: " << HistName << " not on list - not removing" <<endl;

  } 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfLogX->GetSize();
}


//_____________________________________________________________________________

Int_t StHistUtil::RemoveFromPrintList(const Char_t *HistName){  
// Method RemoveFromPrintList
//   remove hist from  list  that we want drawn,printed

//  cout << " **** Now in StHistUtil::RemoveFromPrintList  **** " << endl;

// check if list exists:
  if (m_ListOfPrint) {
    
// the remove method for TList requires a TObject input  
// - check if it's  on the list - use FindObject method of TList
    TObject *lobj = 0;
    lobj = m_ListOfPrint->FindObject(HistName);
// now can use Remove method of TList
    if (lobj) {
      m_ListOfPrint->Remove(lobj);
      cout << " RemovePrintList: " << HistName << " has been removed from list" <<endl;
    }
    else  cout << " RemovePrintList: " << HistName << " not on list - not removing" <<endl;

  } 
// return using a method of TList (inherits GetSize from TCollection)
 return m_ListOfPrint->GetSize();
}


//_____________________________________________________________________________
// Method SetDefaultLogYList
//    - create default list of histograms we want plotted in LogY scale

void StHistUtil::SetDefaultLogYList(Char_t *dirName)
{  
// Method SetDefaultLogYList
//    - create default list of histograms we want plotted in LogY scale

  cout << " **** Now in StHistUtil::SetDefaultLogYList  **** " << endl;


  Int_t lengofList = 0;
  TString type;

  if (strcmp(dirName,"QA") == 0)
    type = "Tab";
  if (strcmp(dirName,"EventQA") == 0)
    type = "StE";

   TString sdefList[] = {
 "QaInnerSectorDeDx",
 "QaOuterSectorDeDx",
 "QaDedxAllSectors",
 "QaGtrkFitProb",
 "QaGtrkDetId",
 "QaGtrkFlag",
 "QaGtrkf0",
 "QaGtrkf0TS",
 "QaGtrkXf0",
 "QaGtrkXf0TS",
 "QaGtrkYf0",
 "QaGtrkYf0TS",
 "QaGtrkZf0",
 "QaGtrkZf0TS",
 "QaGtrkImpactT",
 "QaGtrkImpactTS",
 "QaGtrkNPntT",
 "QaGtrkNPntTS",
 "QaGtrkNPntFE",
 "QaGtrkNPntFW",
 "QaGtrkNPntMaxT",
 "QaGtrkNPntMaxTS",
 "QaGtrkNPntMaxFE",
 "QaGtrkNPntMaxFW",
 "QaGtrkNPntFitT",
 "QaGtrkNPntFitTS",
 "QaGtrkNPntFitFE",
 "QaGtrkNPntFitFW",
 "QaGtrkPtT",
 "QaGtrkPtTS",
 "QaGtrkPtFE",
 "QaGtrkPtFW",
 "QaGtrkPT",
 "QaGtrkPTS",
 "QaGtrkPFE",
 "QaGtrkPFW",
 "QaGtrkR0T",
 "QaGtrkR0TS",
 "QaGtrkZ0T",
 "QaGtrkZ0TS",
 "QaGtrkCurvT",
 "QaGtrkCurvTS",
 "QaGtrkRfT",
 "QaGtrkRfTS",
 "QaGtrkPadfT",
 "QaGtrkXfT",
 "QaGtrkXfTS",
 "QaGtrkXfFE",
 "QaGtrkXfFW",
 "QaGtrkYfT",
 "QaGtrkYfTS",
 "QaGtrkYfFE",
 "QaGtrkYfFW",
 "QaGtrkZfT",
 "QaGtrkZfTS",
 "QaGtrkZfFE",
 "QaGtrkRT",
 "QaGtrkRTS",
 "QaGtrkRFE",
 "QaGtrkRFW",
 "QaGtrkRnfT",
 "QaGtrkRnfTS",
 "QaGtrkRnfFE",
 "QaGtrkRnfFW",
 "QaGtrkRnmT",
 "QaGtrkRnmTS",
 "QaGtrkRnmFE",
 "QaGtrkRnmFW",
 "QaGtrkTanlT",
 "QaGtrkTanlTS",
 "QaGtrkTanlFE",
 "QaGtrkTanlFW",
 "QaGtrkThetaT",
 "QaGtrkThetaTS",
 "QaGtrkThetaFE",
 "QaGtrkThetaFW",
 "QaGtrkEtaT",
 "QaGtrkEtaTS",
 "QaGtrkEtaFE",
 "QaGtrkEtaFW",
 "QaGtrkLengthT",
 "QaGtrkLengthTS",
 "QaGtrkLengthFE",
 "QaGtrkLengthFW",
 "QaGtrkChisq0T",
 "QaGtrkChisq0TS",
 "QaGtrkChisq1T",
 "QaGtrkChisq1TS",
 "QaGtrkImpactrT",
 "QaGtrkImpactrTS",

 "QaPtrkDetId",
 "QaPtrkFlag",
 "QaPtrkf0",
 "QaPtrkf0TS",
 "QaPtrkXf0",
 "QaPtrkXf0TS",
 "QaPtrkYf0",
 "QaPtrkYf0TS",
 "QaPtrkZf0",
 "QaPtrkZf0TS",
 "QaPtrkImpactT",
 "QaPtrkImpactTS",
 "QaPtrkNPntT",
 "QaPtrkNPntTS",
 "QaPtrkNPntMaxT",
 "QaPtrkNPntMaxTS",
 "QaPtrkNPntFitT",
 "QaPtrkNPntFitTS",
 "QaPtrkPtT",
 "QaPtrkPtTS",
 "QaPtrkPT",
 "QaPtrkPTS",
 "QaPtrkR0T",
 "QaPtrkR0TS",
 "QaPtrkZ0T",
 "QaPtrkZ0TS",
 "QaPtrkCurvT",
 "QaPtrkCurvTS",
 "QaPtrkXfT",
 "QaPtrkXfTS",
 "QaPtrkYfT",
 "QaPtrkYfTS",
 "QaPtrkZfT",
 "QaPtrkZfTS",
 "QaPtrkRT",
 "QaPtrkRTS",
 "QaPtrkRnfT",
 "QaPtrkRnfTS",
 "QaPtrkRnmT",
 "QaPtrkRnmTS",
 "QaPtrkTanlT",
 "QaPtrkTanlTS",
 "QaPtrkThetaT",
 "QaPtrkThetaTS",
 "QaPtrkEtaT",
 "QaPtrkEtaTS",
 "QaPtrkLengthT",
 "QaPtrkLengthTS",
 "QaPtrkChisq0T",
 "QaPtrkChisq0TS",
 "QaPtrkChisq1T",
 "QaPtrkChisq1TS",
 "QaPtrkImpactrT",
 "QaPtrkImpactrTS",

/* These are FTPC histograms. Currently, the FTPC doesn't do primary tracking...
 "QaPtrkNPntFE",
 "QaPtrkNPntFW",
 "QaPtrkNPntMaxFE",
 "QaPtrkNPntMaxFW",
 "QaPtrkNPntFitFE",
 "QaPtrkNPntFitFW",
 "QaPtrkPtFE",
 "QaPtrkPtFW",
 "QaPtrkPFE",
 "QaPtrkPFW",
 "QaPtrkXfFE",
 "QaPtrkXfFW",
 "QaPtrkYfFE",
 "QaPtrkYfFW",
 "QaPtrkZfFE",
 "QaPtrkZfFW",
 "QaPtrkRFE",
 "QaPtrkRFW",
 "QaPtrkRnfFE",
 "QaPtrkRnfFW",
 "QaPtrkRnmFE",
 "QaPtrkRnmFW",
 "QaPtrkTanlFE",
 "QaPtrkTanlFW",
 "QaPtrkThetaFE",
 "QaPtrkThetaFW",
 "QaPtrkEtaFE",
 "QaPtrkEtaFW",
 "QaPtrkLengthFE",
 "QaPtrkLengthFW",
*/
 "QaDedxNum",
 "QaDedxDedx0T", 
 "QaDedxDedx1T",
 "QaDedxDedx0FE", 
 "QaDedxDedx1FE",
 "QaDedxDedx0FW", 
 "QaDedxDedx1FW",
 "QaPointId",
 "QaEvgenPt",
 "QaEvgenVtxX",
 "QaEvgenVtxY",
 "QaEvgenVtxZ",
 "QaVtxX",
 "QaVtxY",
 "QaVtxZ",
 "QaVtxChisq"
  };

  lengofList = sizeof(sdefList)/8;

  //  else 
  //  { cout << " StHistUtil::SetDefaultLogYList - no hist set in def logy list " << endl; } 

  Int_t numLog = 0;

  if (lengofList) {
    Int_t ilg = 0;
    for (ilg=0;ilg<lengofList;ilg++) {
      TString listString;
      if ((sdefList[ilg] != "QaInnerSectorDeDx") &&
	  (sdefList[ilg] != "QaOuterSectorDeDx") &&
	  (sdefList[ilg] != "QaDedxAllSectors"))
	listString = type+sdefList[ilg];
      else
	listString = sdefList[ilg];
     numLog = AddToLogYList((const Char_t *)listString);
     cout <<  " !!! adding histogram " << listString << " to LogY list "  << endl ;
    }
  }

  cout <<  " !!!  StHistUtil::SetDefaultLogYList, # histogram put in list " << numLog << endl;

}

//_____________________________________________________________________________
// Method SetDefaultLogXList
//    - create default list of histograms we want plotted in LogX scale

void StHistUtil::SetDefaultLogXList(Char_t *dirName)
{  
// Method SetDefaultLogXList
//    - create default list of histograms we want plotted in LogX scale

  cout << " **** Now in StHistUtil::SetDefaultLogXList  **** " << endl;


  Char_t **sdefList=0;
  Int_t lengofList = 0;


  Int_t numLog = 0;

  if (lengofList) {
    Int_t ilg = 0;
    for (ilg=0;ilg<lengofList;ilg++) {
     numLog = AddToLogXList(sdefList[ilg]);
     //     cout <<  " !!! adding histogram " << sdefList[ilg] << " to LogX list "  << endl ;
    }
  }

  cout <<  " !!!  StHistUtil::SetDefaultLogXList, # histogram put in list " << numLog << endl;

}

//_____________________________________________________________________________
// Method SetDefaultPrintList
//    - create default list of histograms we want drawn,printed

void StHistUtil::SetDefaultPrintList(Char_t *dirName, Char_t *analType)
{  

  cout << " **** Now in StHistUtil::SetDefaultPrintList  **** " << endl;

  Char_t **sdefList=0;
  Int_t lengofList = 0;

// If not analysis Type is set, then don't setup a list
  if ( strcmp(analType,"")==0 || strcmp(analType,"All")==0 ) {
    cout << " All histograms in directory will be printed/drawn, no list set" << endl;
    return;
  }

// Cosmic Data Table QA list .............................................
  if (strcmp(dirName,"QA")==0 && strcmp(analType,"Cosmic")==0) {
   Char_t* sdefList1[] = {
 "TabQaNullPrimVtx",
 "TabQaEvsumTrkTot",
 "TabQaEvsumTrkTotsm",
 "TabQaEvsumPlusMinusTrk",
 "TabQaEvsumPlusMinusTrksm",
 "TabQaEvsumTotChg",
 "TabQaEvsumMeanPt",
 "TabQaEvsumMeanPtsm",
 "TabQaGtrkGood",
 "TabQaGtrkGoodsm",
 "TabQaGtrkNPntT",
 "TabQaGtrkNPntMaxT",
 "TabQaGtrkNPntFitT",
 "TabQaGtrkRnmT",
 "TabQaGtrkChrgT",
 "TabQaGtrkR0T",
 "TabQaGtrkPhi0T",
 "TabQaGtrkZ0T",
 "TabQaGtrkCurvT",
 "TabQaGtrkRfT",
 "TabQaGtrkPadfT",
 "TabQaGtrkXfT",
 "TabQaGtrkXf0",
 "TabQaGtrkYfT",
 "TabQaGtrkYf0",
 "TabQaGtrkZfT",
 "TabQaGtrkZf0",
 "TabQaGtrkRT",
 "TabQaGtrkf0",
 "TabQaGtrkLengthT",
 "TabQaGtrkPsiT",
 "TabQaGtrkTanlT",
 "TabQaGtrkThetaT",
 "TabQaGtrkPtT",
 "TabQaGtrkPT",
 "TabQaGtrkChisq0T",
 "TabQaGtrkChisq1T",
 "TabQaGtrkXfYfT",
 "TabQaGtrkTanlzf",
 "TabQaGtrkPVsTrkLength",
 "TabQaGtrkNPntLengthT",
 "TabQaGtrkChi0MomT",
 "TabQaGtrkChi1MomT",
 "TabQaGtrkChi0TanlT",
 "TabQaGtrkChi1TanlT",
 "TabQaGtrkChi0zfT",
 "TabQaGtrkChi1zfT",
 "TabQaGtrkPsiPhiT"
   };
  sdefList = sdefList1;
  lengofList = sizeof(sdefList1)/4;  
  }

// Test Table QA list.........................................................
  if (strcmp(dirName,"QA")==0 && strcmp(analType,"TestQATable")==0) {
   Char_t* sdefList2[] = {
     "TabQaVtxX",
     "TabQaVtxY"
   };
  sdefList = sdefList2;
  lengofList = sizeof(sdefList2)/4;  
  }

// FTPC Table QA list.........................................................
  if (strcmp(dirName,"QA")==0 && strcmp(analType,"Ftpc")==0) {
   Char_t* sdefList3[] = {
  "TabQaGtrkNPntFE",
  "TabQaGtrkNPntFW",
  "TabQaGtrkNPntMaxFE",
  "TabQaGtrkNPntMaxFW",
  "TabQaGtrkNPntFitFE",
  "TabQaGtrkNPntFitFW",
  "TabQaGtrkRnfFE",
  "TabQaGtrkRnfFW",
  "TabQaGtrkRnmFE",
  "TabQaGtrkRnmFW",
  "TabQaGtrkChrgFE",
  "TabQaGtrkChrgFW",
  "TabQaGtrkXfFE",
  "TabQaGtrkXfFW",
  "TabQaGtrkYfFE",
  "TabQaGtrkYfFW",
  "TabQaGtrkZfFE",
  "TabQaGtrkZfFW",
  "TabQaGtrkRFE",
  "TabQaGtrkRFW",
  "TabQaGtrkLengthFE",
  "TabQaGtrkLengthFW",
  "TabQaGtrkPsiFE",
  "TabQaGtrkPsiFW",
  "TabQaGtrkEtaFE",
  "TabQaGtrkEtaFW",
  "TabQaGtrkPtFE",
  "TabQaGtrkPtFW",
  "TabQaGtrkPFE",
  "TabQaGtrkPFW",
  "TabQaGtrkChisq0FE",
  "TabQaGtrkChisq0FW",
  "TabQaGtrkChisq1FE",
  "TabQaGtrkChisq1FW",
  "TabQaGtrkPtVsEtaFE",
  "TabQaGtrkPtVsEtaFW",
  "TabQaGtrkXfYfFE",
  "TabQaGtrkXfYfFW",
  "TabQaGtrkLengthVEtaFE",
  "TabQaGtrkLengthVEtaFW",
  "TabQaGtrkNPntLengthFE",
  "TabQaGtrkNPntLengthFW",
  "TabQaGtrkFitPntLengthFE",
  "TabQaGtrkFitPntLengthFW",
  "TabQaDedxNdedxFE",
  "TabQaDedxDedx0FE",
  "TabQaDedxDedx1FE",
  "TabQaDedxNdedxFW",
  "TabQaDedxDedx0FW",
  "TabQaDedxDedx1FW",  
  "TabQaPointFtpcE",
  "TabQaPointFtpcW"
   };
  sdefList = sdefList3;
  lengofList = sizeof(sdefList3)/4;  
  }

// FTPC Table QA list.........................................................
  if (strcmp(dirName,"FlowTag")==0 && strcmp(analType,"MDC3")==0) {
   Char_t* sdefList4[] = {
     "FlowPsi0Harmonic1",
     "FlowPsi0Harmonic2",
     "FlowMeanPt0Harmonic1",
     "FlowMeanPt0Harmonic2",
     "FlowMult0Harmonic1",
     "FlowMult0Harmonic2",
     "Flow_q0Harmonic1",
     "Flow_q0Harmonic2"
   };
  sdefList = sdefList4;
  lengofList = sizeof(sdefList4)/4;  
  }

// St_QA_Maker histograms without svt and ftpc histograms
  if (strcmp(dirName,"QA")==0 && strcmp(analType,"year1")==0) {
    Char_t* sdefList5[] = {
     "TabQaNullPrimVtx",
     "TabQaEvsumTrkGoodDTotal",
     "TabQaEvsumTrkTot",
     "TabQaEvsumTrkTotsm",
     "TabQaEvsumPlusMinusTrk",
     "TabQaEvsumPlusMinusTrksm",
     "TabQaEvsumTotChg",
     "TabQaEvsumTrkPrim",
     "TabQaEvsumTrkPrimsm",
     "TabQaEvsumVertTot",
     "TabQaEvsumVertTotsm",
     "TabQaEvsumMeanPt",
     "TabQaEvsumMeanPtsm",
     "TabQaEvsumMeanEta",
     "TabQaEvsumRmsEta",
     "TabQaEvsumPrimVertR",
     "TabQaEvsumPrimVertX",
     "TabQaEvsumPrimVertY",
     "TabQaEvsumPrimVertZ",
     "TabQaGtrkTot",
     "TabQaGtrkTotsm",
     "TabQaGtrkFlag",
     "TabQaGtrkGood",
     "TabQaGtrkGoodsm",
     "TabQaGtrkDetId",
     "TabQaGtrkNPntT",
     "TabQaGtrkNPntMaxT",
     "TabQaGtrkNPntFitT",
     "TabQaGtrkRnfT",
     "TabQaGtrkRnmT",
     "TabQaGtrkChrgT",
     "TabQaGtrkR0T",
     "TabQaGtrkPhi0T",
     "TabQaGtrkZ0T",
     "TabQaGtrkCurvT",
     "TabQaGtrkRfT",
     "TabQaGtrkPadfT",
     "TabQaGtrkf0",
     "TabQaGtrkXfT",
     "TabQaGtrkXf0",
     "TabQaGtrkYfT",
     "TabQaGtrkYf0",
     "TabQaGtrkZfT",
     "TabQaGtrkZf0",
     "TabQaGtrkRT",
     "TabQaGtrkLengthT",
     "TabQaGtrkPsiT",
     "TabQaGtrkTanlT",
     "TabQaGtrkThetaT",
     "TabQaGtrkEtaT",
     "TabQaGtrkPtT",
     "TabQaGtrkPT",
     "TabQaGtrkChisq0T",
     "TabQaGtrkChisq1T",
     "TabQaGtrkImpactT",
     "TabQaGtrkImpactrT",
     "TabQaGtrkPtVsEtaT",
     "TabQaGtrkXfYfT",
     "TabQaGtrkTanlzf",
     "TabQaGtrkPVsTrkLength",
     "TabQaGtrkLengthVEtaT",
     "TabQaGtrkNPntLengthT",
     "TabQaGtrkFitPntLengthT",
     "TabQaGtrkChi0MomT",
     "TabQaGtrkChi1MomT",
     "TabQaGtrkChi0EtaT",
     "TabQaGtrkChi1EtaT",
     "TabQaGtrkChi0TanlT",
     "TabQaGtrkChi1TanlT",
     "TabQaGtrkChi0zfT",
     "TabQaGtrkChi1zfT",
     "TabQaGtrkChi0PhiT",
     "TabQaGtrkRPntMomT",
     "TabQaGtrkRPntEtaT",
     "TabQaGtrkPsiPhiT",
     "TabQaPtrkTot",
     "TabQaPtrkTotsm",
     "TabQaPtrkFlag",
     "TabQaPtrkGood",
     "TabQaPtrkGoodsm",
     "TabQaPtrkDetId",
     "TabQaPtrkNPntT",
     "TabQaPtrkNPntMaxT",
     "TabQaPtrkNPntFitT",
     "TabQaPtrkRnfT",
     "TabQaPtrkRnmT",
     "TabQaPtrkChrgT",
     "TabQaPtrkR0T",
     "TabQaPtrkPhi0T",
     "TabQaPtrkZ0T",
     "TabQaPtrkCurvT",
     "TabQaPtrkXfT",
     "TabQaPtrkXf0",
     "TabQaPtrkYfT",
     "TabQaPtrkYf0",
     "TabQaPtrkZfT",
     "TabQaPtrkZf0",
     "TabQaPtrkf0",
     "TabQaPtrkRT",
     "TabQaPtrkLengthT",
     "TabQaPtrkPsiT",
     "TabQaPtrkTanlT",
     "TabQaPtrkThetaT",
     "TabQaPtrkEtaT",
     "TabQaPtrkPtT",
     "TabQaPtrkPT",
     "TabQaPtrkChisq0T",
     "TabQaPtrkChisq1T",
     "TabQaPtrkImpactT",
     "TabQaPtrkImpactrT",
     "TabQaPtrkPtVsEtaT",
     "TabQaPtrkXfYfT",
     "TabQaPtrkTanlzf",
     "TabQaPtrkPVsTrkLength",
     "TabQaPtrkLengthVEtaT",
     "TabQaPtrkNPntLengthT",
     "TabQaPtrkFitPntLengthT",
     "TabQaPtrkChi0MomT",
     "TabQaPtrkChi1MomT",
     "TabQaPtrkChi0EtaT",
     "TabQaPtrkChi1EtaT",
     "TabQaPtrkChi0TanlT",
     "TabQaPtrkChi1TanlT",
     "TabQaPtrkChi0zfT",
     "TabQaPtrkChi1zfT",
     "TabQaPtrkRPntMomT",
     "TabQaPtrkRPntEtaT",
     "TabQaPtrkPsiPhiT",
     "TabQaDedxNum",
     "TabQaDedxNdedxT",
     "TabQaDedxDedx0T",
     "TabQaDedxDedx1T",
     "TabQaEvgenNPart",
     "TabQaEvgenNPartsm",
     "TabQaEvgenNChgPart",
     "TabQaEvgenNChgPartsm",
     "TabQaEvgenPt",
     "TabQaEvgenPtT",
     "TabQaEvgenEta",
     "TabQaEvgenPtVsEta",
     "TabQaEvgenVtxX",
     "TabQaEvgenVtxY",
     "TabQaEvgenVtxZ",
     "TabQaPidGlobtrkDstdedxPVsDedx",
     "TabQaVtxNum",
     "TabQaVtxNumsm",
     "TabQaVtxVtxId",
     "TabQaVtxX",
     "TabQaVtxY",
     "TabQaVtxZ",
     "TabQaVtxChisq",
     "TabQaVtxR",
     "TabQaVtxPrVtxId",
     "TabQaVtxPrX",
     "TabQaVtxPrY",
     "TabQaVtxPrZ",
     "TabQaVtxPrChisq",
     "TabQaVtxPrR",
     "TabQaV0Vtx",
     "TabQaV0LambdaMass",
     "TabQaV0K0Mass",
     "TabQaXiVtxTot",
     "TabQaXiaMass",
     "TabQaKinkTot",
     "TabQaPointTot",
     "TabQaPointTotmed",
     "TabQaPointTotsm",
     "TabQaPointId",
     "TabQaPointTpc",
     "TabQaRichTot",
     "TabQaGRpvtxDx",
     "TabQaGRpvtxDy",
     "TabQaGRpvtxDz",
     "TabQaGRpvtxDzZ"
    };
   sdefList = sdefList5;
   lengofList = sizeof(sdefList5)/4;  
  }

// St_QA_Maker histograms without the svt and ftpc histograms
  if (strcmp(dirName,"EventQA")==0 && strcmp(analType,"year1")==0) {
    Char_t* sdefList6[] = {
     "StEQaNullPrimVtx",
     "QaInnerSectorDeDx",
     "QaOuterSectorDeDx",
     "QaDedxAllSectors",
     "StEQaEvsumTrkGoodDTotal",
     "StEQaEvsumTrkTot",
     "StEQaEvsumTrkTotsm",
     "StEQaEvsumPlusMinusTrk",
     "StEQaEvsumPlusMinusTrksm",
     "StEQaEvsumTotChg",
     "StEQaEvsumTrkPrim",
     "StEQaEvsumTrkPrimsm",
     "StEQaEvsumVertTot",
     "StEQaEvsumVertTotsm",
     "StEQaEvsumMeanPt",
     "StEQaEvsumMeanPtsm",
     "StEQaEvsumMeanEta",
     "StEQaEvsumRmsEta",
     "StEQaEvsumPrimVertR",
     "StEQaEvsumPrimVertX",
     "StEQaEvsumPrimVertY",
     "StEQaEvsumPrimVertZ",
     "StEQaGtrkTot",
     "StEQaGtrkTotsm",
     "StEQaGtrkFlag",
     "StEQaGtrkGood",
     "StEQaGtrkGoodsm",
     "StEQaGtrkFitProb",
     "StEQaGtrkDetId",
     "StEQaGtrkDcaBeamXY",
     "StEQaGtrkDcaBeamZ1",
     "StEQaGtrkDcaBeamZ2",
     "StEQaGtrkDcaBeamZ3",
     "StEQaGtrkZdcaTanl",
     "StEQaGtrkZdcaZf",
     "StEQaGtrkZdcaPsi",
     "StEQaGtrkZdcaPhi0",
     "StEQaGtrkNPntT",
     "StEQaGtrkNPntMaxT",
     "StEQaGtrkNPntFitT",
     "StEQaGtrkRnfT",
     "StEQaGtrkRnmT",
     "StEQaGtrkChrgT",
     "StEQaGtrkR0T",
     "StEQaGtrkPhi0T",
     "StEQaGtrkZ0T",
     "StEQaGtrkCurvT",
     "StEQaGtrkRfT",
     "StEQaGtrkPadfT",
     "StEQaGtrkf0",
     "StEQaGtrkXfT",
     "StEQaGtrkXf0",
     "StEQaGtrkYfT",
     "StEQaGtrkYf0",
     "StEQaGtrkZfT",
     "StEQaGtrkZf0",
     "StEQaGtrkRT",
     "StEQaGtrkLengthT",
     "StEQaGtrkPsiT",
     "StEQaGtrkTanlT",
     "StEQaGtrkThetaT",
     "StEQaGtrkEtaT",
     "StEQaGtrkPtT",
     "StEQaGtrkPT",
     "StEQaGtrkChisq0T",
     "StEQaGtrkChisq1T",
     "StEQaGtrkImpactT",
     "StEQaGtrkImpactrT",
     "StEQaGtrkPtVsEtaT",
     "StEQaGtrkXfYfT",
     "StEQaGtrkTanlzf",
     "StEQaGtrkPVsTrkLength",
     "StEQaGtrkLengthVEtaT",
     "StEQaGtrkNPntLengthT",
     "StEQaGtrkFitPntLengthT",
     "StEQaGtrkChi0MomT",
     "StEQaGtrkChi1MomT",
     "StEQaGtrkChi0EtaT",
     "StEQaGtrkChi1EtaT",
     "StEQaGtrkChi0TanlT",
     "StEQaGtrkChi1TanlT",
     "StEQaGtrkChi0zfT",
     "StEQaGtrkChi1zfT",
     "StEQaGtrkChi0PhiT",
     "StEQaGtrkRPntMomT",
     "StEQaGtrkRPntEtaT",
     "StEQaGtrkPsiPhiT",
     "StEQaPtrkTot",
     "StEQaPtrkTotsm",
     "StEQaPtrkFlag",
     "StEQaPtrkGood",
     "StEQaPtrkGoodsm",
     "StEQaPtrkDetId",
     "StEQaPtrkNPntT",
     "StEQaPtrkNPntMaxT",
     "StEQaPtrkNPntFitT",
     "StEQaPtrkRnfT",
     "StEQaPtrkRnmT",
     "StEQaPtrkChrgT",
     "StEQaPtrkR0T",
     "StEQaPtrkPhi0T",
     "StEQaPtrkZ0T",
     "StEQaPtrkCurvT",
     "StEQaPtrkXfT",
     "StEQaPtrkXf0",
     "StEQaPtrkYfT",
     "StEQaPtrkYf0",
     "StEQaPtrkZfT",
     "StEQaPtrkZf0",
     "StEQaPtrkf0",
     "StEQaPtrkRT",
     "StEQaPtrkLengthT",
     "StEQaPtrkPsiT",
     "StEQaPtrkTanlT",
     "StEQaPtrkThetaT",
     "StEQaPtrkEtaT",
     "StEQaPtrkPtT",
     "StEQaPtrkPT",
     "StEQaPtrkChisq0T",
     "StEQaPtrkChisq1T",
     "StEQaPtrkImpactT",
     "StEQaPtrkImpactrT",
     "StEQaPtrkPtVsEtaT",
     "StEQaPtrkXfYfT",
     "StEQaPtrkTanlzf",
     "StEQaPtrkPVsTrkLength",
     "StEQaPtrkLengthVEtaT",
     "StEQaPtrkNPntLengthT",
     "StEQaPtrkFitPntLengthT",
     "StEQaPtrkChi0MomT",
     "StEQaPtrkChi1MomT",
     "StEQaPtrkChi0EtaT",
     "StEQaPtrkChi1EtaT",
     "StEQaPtrkChi0TanlT",
     "StEQaPtrkChi1TanlT",
     "StEQaPtrkChi0zfT",
     "StEQaPtrkChi1zfT",
     "StEQaPtrkRPntMomT",
     "StEQaPtrkRPntEtaT",
     "StEQaPtrkPsiPhiT",
     "StEQaDedxNum",
     "StEQaDedxNdedxT",
     "StEQaDedxDedx0T",
     "StEQaDedxDedx1T",
     "StEQaPidGlobtrkDstdedxPVsDedx",
     "StEQaVtxNum",
     "StEQaVtxNumsm",
     "StEQaVtxVtxId",
     "StEQaVtxX",
     "StEQaVtxY",
     "StEQaVtxZ",
     "StEQaVtxChisq",
     "StEQaVtxR",
     "StEQaVtxPrVtxId",
     "StEQaVtxPrX",
     "StEQaVtxPrY",
     "StEQaVtxPrZ",
     "StEQaVtxPrChisq",
     "StEQaVtxPrR",
     "StEQaV0Vtx",
     "StEQaV0LambdaMass",
     "StEQaV0K0Mass",
     "StEQaXiVtxTot",
     "StEQaXiaMass",
     "StEQaKinkTot",
     "StEQaPointTot",
     "StEQaPointTotmed",
     "StEQaPointTotsm",
     "StEQaPointTpc",
     "StEQaRichTot",
     "StEQaPointZhits"
    };
   sdefList = sdefList6;
   lengofList = sizeof(sdefList6)/4;  
  }

// St_QA_Maker histograms for QA shift
  if (strcmp(dirName,"QA")==0 && strcmp(analType,"qa_shift")==0) {
    Char_t* sdefList7[] = {
     "TabQaNullPrimVtx",
     "TabQaEvsumTrkGoodDTotal",
     "TabQaEvsumTrkTot",
     "TabQaEvsumTotChg",
     "TabQaEvsumTrkPrim",
     "TabQaEvsumMeanPt",
     "TabQaEvsumPrimVertR",
     "TabQaEvsumPrimVertZ",
     "TabQaGtrkRnfT",
     "TabQaGtrkR0T",
     "TabQaGtrkPhi0T",
     "TabQaGtrkZ0T",
     "TabQaGtrkRfT",
     "TabQaGtrkf0",
     "TabQaGtrkLengthT",
     "TabQaGtrkPsiT",
     "TabQaGtrkTanlT",
     "TabQaGtrkEtaT",
     "TabQaGtrkPtT",
     "TabQaGtrkChisq0T",
     "TabQaGtrkImpactT",
     "TabQaGtrkImpactrT",
     "TabQaGtrkPtVsEtaT",
     "TabQaGtrkTanlzf",
     "TabQaGtrkLengthVEtaT",
     "TabQaGtrkNPntLengthT",
     "TabQaGtrkFitPntLengthT",
     "TabQaGtrkChi0EtaT",
     "TabQaGtrkChi0PhiT",
     "TabQaGtrkRPntMomT",
     "TabQaGtrkRPntEtaT",
     "TabQaPtrkTot",
     "TabQaPtrkGood",
     "TabQaPtrkNPntT",
     "TabQaPtrkNPntFitT",
     "TabQaPtrkRnfT",
     "TabQaPtrkPhi0T",
     "TabQaPtrkXfT",
     "TabQaPtrkYfT",
     "TabQaPtrkZfT",
     "TabQaPtrkf0",
     "TabQaPtrkRT",
     "TabQaPtrkPsiT",
     "TabQaPtrkTanlT",
     "TabQaPtrkPtT",
     "TabQaPtrkChisq0T",
     "TabQaPtrkChisq1T",
     "TabQaPtrkImpactT",
     "TabQaPtrkImpactrT",
     "TabQaPtrkPtVsEtaT",
     "TabQaPtrkTanlzf",
     "TabQaPtrkLengthVEtaT",
     "TabQaPtrkNPntLengthT",
     "TabQaPtrkChi0EtaT",
     "TabQaPtrkChi1EtaT",
     "TabQaPtrkRPntMomT",
     "TabQaPtrkRPntEtaT",
     "TabQaPtrkPsiPhiT",
     "TabQaPidGlobtrkDstdedxPVsDedx",
     "TabQaVtxNum",
     "TabQaV0Vtx",
     "TabQaV0LambdaMass",
     "TabQaV0K0Mass",
     "TabQaXiVtxTot",
     "TabQaXiaMass",
     "TabQaKinkTot"
    };
   sdefList = sdefList7;
   lengofList = sizeof(sdefList7)/4;  
  }

// St_QA_Maker histograms for QA shift
  if (strcmp(dirName,"EventQA")==0 && strcmp(analType,"qa_shift")==0) {
    Char_t* sdefList8[] = {
     "StEQaNullPrimVtx",
     "QaDedxAllSectors",
     "StEQaEvsumTrkGoodDTotal",
     "StEQaEvsumTrkTot",
     "StEQaEvsumTotChg",
     "StEQaEvsumTrkPrim",
     "StEQaEvsumMeanPt",
     "StEQaEvsumPrimVertR",
     "StEQaEvsumPrimVertZ",
     "StEQaGtrkFitProb",
     "StEQaGtrkDcaBeamXY",
     "StEQaGtrkDcaBeamZ1",
     "StEQaGtrkDcaBeamZ2",
     "StEQaGtrkDcaBeamZ3",
     "StEQaGtrkZdcaTanl",
     "StEQaGtrkZdcaZf",
     "StEQaGtrkZdcaPsi",
     "StEQaGtrkZdcaPhi0",
     "StEQaGtrkRnfT",
     "StEQaGtrkR0T",
     "StEQaGtrkPhi0T",
     "StEQaGtrkZ0T",
     "StEQaGtrkRfT",
     "StEQaGtrkPadfT",
     "StEQaGtrkf0",
     "StEQaGtrkLengthT",
     "StEQaGtrkPsiT",
     "StEQaGtrkTanlT",
     "StEQaGtrkEtaT",
     "StEQaGtrkPtT",
     "StEQaGtrkChisq0T",
     "StEQaGtrkImpactT",
     "StEQaGtrkImpactrT",
     "StEQaGtrkPtVsEtaT",
     "StEQaGtrkTanlzf",
     "StEQaGtrkLengthVEtaT",
     "StEQaGtrkNPntLengthT",
     "StEQaGtrkFitPntLengthT",
     "StEQaGtrkChi0EtaT",
     "StEQaGtrkChi0PhiT",
     "StEQaGtrkRPntMomT",
     "StEQaGtrkRPntEtaT",
     "StEQaPtrkTot",
     "StEQaPtrkGood",
     "StEQaPtrkNPntT",
     "StEQaPtrkNPntFitT",
     "StEQaPtrkRnfT",
     "StEQaPtrkPhi0T",
     "StEQaPtrkXfT",
     "StEQaPtrkYfT",
     "StEQaPtrkZfT",
     "StEQaPtrkf0",
     "StEQaPtrkRT",
     "StEQaPtrkPsiT",
     "StEQaPtrkTanlT",
     "StEQaPtrkPtT",
     "StEQaPtrkChisq0T",
     "StEQaPtrkChisq1T",
     "StEQaPtrkImpactT",
     "StEQaPtrkImpactrT",
     "StEQaPtrkPtVsEtaT",
     "StEQaPtrkTanlzf",
     "StEQaPtrkLengthVEtaT",
     "StEQaPtrkNPntLengthT",
     "StEQaPtrkChi0EtaT",
     "StEQaPtrkChi1EtaT",
     "StEQaPtrkRPntMomT",
     "StEQaPtrkRPntEtaT",
     "StEQaPtrkPsiPhiT",
     "StEQaPidGlobtrkDstdedxPVsDedx",
     "StEQaVtxNum",
     "StEQaV0Vtx",
     "StEQaV0LambdaMass",
     "StEQaV0K0Mass",
     "StEQaXiVtxTot",
     "StEQaXiaMass",
     "StEQaKinkTot",
     "StEQaPointZhits"
    };
   sdefList = sdefList8;
   lengofList = sizeof(sdefList8)/4;
  }

  Int_t numPrt = 0;
  if (lengofList) {
    Int_t ilg = 0;
    for (ilg=0;ilg<lengofList;ilg++) {
     numPrt = AddToPrintList(sdefList[ilg]);
     //     cout <<  " !!! adding histogram " << sdefList[ilg] << " to print list "  << endl ;
    }
  }
  
  cout <<  " !!!  StHistUtil::SetDefaultPrintList, # histogram put in list " << numPrt << endl;

}

//_____________________________________________________________________________

// Method Overlay1D
//    - takes two TH1F histograms and overlays them

Int_t StHistUtil::Overlay1D(Char_t *dirName,Char_t *inHist1,
			    Char_t *inHist2) {

  cout << " **** Now in StHistUtil::Overlay1D **** " << endl;

  Int_t n1dHists = 0;

// get the TList pointer to the histograms
  TList  *dirList = 0;
  dirList = FindHists(dirName);

// check that directory exists
  if (!dirList)
    return kStErr;

  cout << "Histogram directory exists -> Find and overlay histograms" << endl;
// Now want to loop over all histograms
// Create an iterator
  TIter nextObj(dirList);
  TObject *obj = 0;

// temporary holder histograms
  TH1F *hist1f1 = new TH1F;
  TH1F *hist1f2 = new TH1F;

// use = here instead of ==, because we are setting obj equal to nextObj
// and then seeing if it's T or F
  while ((obj = nextObj())) {

// now check if obj is a histogram and see if it matches input name
    if (obj->InheritsFrom("TH1")) {
      if (obj->GetName() == (TString)inHist1 ||
	  obj->GetName() == (TString)inHist2) {
	cout << " Found Histogram: Type '" << obj->ClassName() << "', Name '"
	     << obj->GetName() << "', Title '" << obj->GetTitle() << "'"
	     << endl;

// check on type of histogram and make copies
	if (obj->ClassName() == (TString)"TH1F") {
	  if (obj->GetName() == (TString)inHist1) {
	    *hist1f1 = *(TH1F *)obj;
	    n1dHists++;
	  }
	  if (obj->GetName() == (TString)inHist2) {
	    *hist1f2 = *(TH1F *)obj;
	    n1dHists++;
	  }
	}
	else
	  cout << " ERROR: histogram not of type TH1F !!!" << endl;
      }
    }
  }

// if the two histograms exist, overlay them
  if (n1dHists == 2) {
    hist1f1->SetLineColor(4);
    hist1f1->SetLineStyle(1);
    hist1f2->SetLineColor(2);
    hist1f2->SetLineStyle(2);

    hist1f1->SetStats(kFALSE);
    hist1f2->SetStats(kFALSE);

    hist1f1->SetTitle(hist1f1->GetTitle()+(TString)" and "+hist1f2->GetTitle());
    hist1f2->SetTitle(hist1f1->GetTitle());
// create a new canvas
    TCanvas *newCanvas = new TCanvas("c1d","Combined 1D Histogram",600,780);
    newCanvas->Draw();

// set global title which goes at top of each page of histograms
    const Char_t *gtitle = m_GlobalTitle.Data();

// write title at top of canvas
    TPaveLabel *Ltitle = new TPaveLabel(0.1,0.96,0.9,1.0,(char *)gtitle,"br");
    Ltitle->SetFillColor(18);
    Ltitle->SetTextFont(32);
    Ltitle->SetTextSize(0.5);
    Ltitle->Draw();

// now put in date & time at bottom right of canvas
    TDatime HistTime;
    const Char_t *myTime = HistTime.AsString();
    TPaveLabel *Ldatetime = new TPaveLabel(0.7,0.01,0.95,0.03,myTime,"br");
    Ldatetime->SetTextSize(0.6);
    Ldatetime->Draw();

// create a pad
    TPad *newPad = new TPad("p1d","Combined 1D Histogram",0.02,0.04,0.98,0.93);
    newPad->Draw();
    newPad->cd();

// draw the histograms
    if (hist1f1->GetMaximum() >= hist1f2->GetMaximum()) {
      hist1f1->Draw();
      hist1f2->Draw("Same");
    }
    else {
      hist1f2->Draw();
      hist1f1->Draw("Same");
    }

// make a legend
    TLegend *legend = new TLegend(0.75,0.85,0.98,0.95);
    legend->SetFillColor(0);
    legend->SetHeader("Legend");
    legend->SetMargin(0.25);
    legend->AddEntry(hist1f1,inHist1,"l");
    legend->AddEntry(hist1f2,inHist2,"l");
    legend->Draw();

    newCanvas->Update();

    return kStOk;
  }

  return kStErr;
}

//_____________________________________________________________________________

// Method Overlay2D
//    - takes two TH2F histograms and overlays them

Int_t StHistUtil::Overlay2D(Char_t *dirName,Char_t *inHist1,
			    Char_t *inHist2) {

  cout << " **** Now in StHistUtil::Overlay2D **** " << endl;

  Int_t n2dHists = 0;

// get the TList pointer to the histograms
  TList  *dirList = 0;
  dirList = FindHists(dirName);

// check that directory exists
  if (!dirList)
    return kStErr;

  cout << "Histogram directory exists -> Find and overlay histograms" << endl;
// Now want to loop over all histograms
// Create an iterator
  TIter nextObj(dirList);
  TObject *obj = 0;

// temporary holder histograms
  TH2F *hist2f1 = new TH2F;
  TH2F *hist2f2 = new TH2F;

// use = here instead of ==, because we are setting obj equal to nextObj
// and then seeing if it's T or F
  while ((obj = nextObj())) {

// now check if obj is a histogram and see if it matches input name
    if (obj->InheritsFrom("TH1")) {
      if (obj->GetName() == (TString)inHist1 ||
	  obj->GetName() == (TString)inHist2) {
	cout << " Found Histogram: Type '" << obj->ClassName() << "', Name '"
	     << obj->GetName() << "', Title '" << obj->GetTitle() << "'"
	     << endl;

// check on type of histogram and make copies
	if (obj->ClassName() == (TString)"TH2F") {
	  if (obj->GetName() == (TString)inHist1) {
	    *hist2f1 = *(TH2F *)obj;
	    n2dHists++;
	  }
	  if (obj->GetName() == (TString)inHist2) {
	    *hist2f2 = *(TH2F *)obj;
	    n2dHists++;
	  }
	}
	else
	  cout << " ERROR: histogram is not of type TH2F !!!" << endl;
      }
    }
  }

// if the two histograms exist, overlay them
  if (n2dHists == 2) {
    hist2f1->SetLineColor(4);
    hist2f2->SetLineColor(2);

    hist2f1->SetStats(kFALSE);
    hist2f2->SetStats(kFALSE);

    hist2f1->SetTitle(hist2f1->GetTitle()+(TString)" and "+hist2f2->GetTitle());
    hist2f2->SetTitle(hist2f1->GetTitle());

// set global title which goes at top of each page of histograms
    const Char_t *gtitle = m_GlobalTitle.Data();

// create a new canvas and pad to write to
    TCanvas *newCanvas = new TCanvas("c2d","Combined 2D Histogram",600,780);
    newCanvas->Draw();

// write title at top of canvas
    TPaveLabel *Ltitle = new TPaveLabel(0.1,0.96,0.9,1.0,(char *)gtitle,"br");
    Ltitle->SetFillColor(18);
    Ltitle->SetTextFont(32);
    Ltitle->SetTextSize(0.5);
    Ltitle->Draw();

// now put in date & time at bottom right of canvas
    TDatime HistTime;
    const Char_t *myTime = HistTime.AsString();
    TPaveLabel *Ldatetime = new TPaveLabel(0.7,0.01,0.95,0.03,myTime,"br");
    Ldatetime->SetTextSize(0.6);
    Ldatetime->Draw();

// create a pad
    TPad *newPad = new TPad("p2d","Combined 2D Histogram",0.02,0.04,0.98,0.93);
    newPad->Draw();
    newPad->cd();

// draw the histograms
    if (hist2f1->GetMaximum() >= hist2f2->GetMaximum()) {
      hist2f1->Draw("Box");
      hist2f2->Draw("BoxSame");
    }
    else {
      hist2f2->Draw("Box");
      hist2f1->Draw("BoxSame");
    }

// make a legend
    TLegend *legend = new TLegend(0.75,0.85,0.98,0.95);
    legend->SetFillColor(0);
    legend->SetHeader("Legend");
    legend->SetMargin(0.25);
    legend->AddEntry(hist2f1,inHist1,"f");
    legend->AddEntry(hist2f2,inHist2,"f");
    legend->Draw();

    newCanvas->Update();

    return kStOk;
  }

  return kStErr;
}

//_____________________________________________________________________________
