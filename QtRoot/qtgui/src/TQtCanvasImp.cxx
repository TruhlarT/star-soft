// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtCanvasImp.cxx,v 1.3 2006/09/28 00:41:14 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtCanvasImp                                                         //
//                                                                      //
// This class creates a main window with menubar, scrollbars and a      //
// drawing area.                                                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
# include "Windows4Root.h"
#endif

#include "TROOT.h"
#include "TBrowser.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TMarker.h"
#include "TStyle.h"
#include "HelpText.h"
#include "TInterpreter.h"
#include "TVirtualPadEditor.h"
#include "TQtCanvas2Html.h"
#include "TEnv.h"

#if  ROOT_VERSION_CODE >= ROOT_VERSION(4,03,3)   
#include "TVirtualViewer3D.h"
#endif

#include "TQtCanvasImp.h"
#include "TGQt.h"
#include "TQtWidget.h"
#include "TQtCanvasWidget.h"
#include "TQtRootAction.h"
#include "TQtZoomPadWidget.h"

#include <qapplication.h>
#include <qmenubar.h>

#if QT_VERSION < 0x40000
#  include <qpopupmenu.h>
#  include <qtoolbar.h>
#  include <qvaluelist.h>
#  include <qfiledialog.h>
#  include <qscrollview.h>
#  include <qwhatsthis.h> 
#else /* QT_VERSION */
#  include <q3popupmenu.h>
#  include <QImageWriter>
#  include <QFileDialog>
#  include <q3scrollview.h>
#  include <q3whatsthis.h> 
#  include <q3valuelist.h>
#  include <q3filedialog.h>
#  include <q3toolbar.h>
//Added by qt3to4:
#  include <QPixmap>
#endif /* QT_VERSION */

#include <qmessagebox.h>
#include <qstatusbar.h>

#include <qlabel.h>
#include <qsplitter.h>

#include <qimage.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qprinter.h>

#include "TQtToolBar.h"

// Canvas menu command ids
enum ERootCanvasCommands {
   kFileNewCanvas,
   kFileOpen,
   kFileSave,
   kFileSaveAs,
   kFileSaveAsRoot,
   kFileSaveAsC,
   kFileSaveAsPS,
   kFileSaveAsEPS,
   kFileSaveAsPDF,
   kFileSaveAsSVG,
   kFileSaveAsGIF,
   kFileSaveAsWeb,
   kFilePrint,
   kFileCloseCanvas,
   kFileQuit,
   kFileExit,

   kEditCut,
   kEditCopy,
   kEditCopyFrame,
   kEditPaste,
   kEditClearPad,
   kEditClearCanvas,
   kEditUndo,
   kEditRedo,

   kViewEditor,
   kViewToolbar,
   kViewEventStatus,
   kViewColors,
   kViewFonts,
   kViewMarkers,
   kViewIconify,
   kViewX3D,
   kViewOpenGL,
   kViewInventorGL,
   kViewZoomer,
   
   kOptionAutoResize,
   kOptionResizeCanvas,
   kOptionMoveOpaque,
   kOptionResizeOpaque,
   kOptionInterrupt,
   kOptionRefresh,
   kOptionAutoExec,
   kOptionStatistics,
   kOptionHistTitle,
   kOptionFitParams,
   kOptionCanEdit,

   kInspectRoot,
   kInspectBrowser,

   kClassesTree,

   kHelpHelp,
   kHelpAbout,
   kHelpOnCanvas,
   kHelpOnMenus,
   kHelpOnGraphicsEd,
   kHelpOnBrowser,
   kHelpOnObjects,
   kHelpOnPS,
};

//static const char *gOpenTypes[] = { "ROOT files",   "*.root",
//                                    "All files",    "*",
//                                    0,              0 };


static TQtBrowserMenuItem_t gMenu_Data[] = {
  // { filename,      tooltip,            staydown,  id,              button}
/* File Menu */
  { "&New",       kFileNewCanvas,  Qt::CTRL+Qt::Key_N, "Open the new ROOT TCanvas widget",     "newcanvas.xpm"           },
  { "&Open",      kFileOpen,       Qt::CTRL+Qt::Key_O, "Open a new ROOT TFile",               "open.xpm"                },
  { "&Close",     kFileCloseCanvas,Qt::ALT +Qt::Key_F4,"Close the TCanvas widget and delete the TCanvas object",  "" },
  { "&Save",      kFileSave,       Qt::CTRL+Qt::Key_S, "Save the current canvas image as ... ","save.xpm"            },
  { "Save &As",   kFileSaveAs,         0,              "Save the current canvas image as ... ","hdisk_t.xpm"         },
  { "Save as Web page", kFileSaveAsWeb,   0,           "Save the current canvas as Web site"  ,"hdisk_t.xpm"         },
  { "&Print",     kFilePrint,      Qt::CTRL+Qt::Key_P, "Print the TCanvas image ",             "printer_s.xpm"       },
  { "&Quit",      kFileQuit,       Qt::CTRL+Qt::Key_Q, "Terminate the ROOT application",       ""                    },
  { "E&xit",      kFileExit,       Qt::CTRL+Qt::Key_X, "Exit the ROOT application",            ""                    },
/* Edit Menu */
  { "&Copy",      kEditCopy,       Qt::CTRL+Qt::Key_C, "Copy the image of the TCanvas client area to the system clipboard","" },
  { "Copy &Frame",kEditCopyFrame,  Qt::CTRL+Qt::Key_F, "Copy the image of the TCanvasframe border to the system clipboard","" },
  { "Clear &Pad", kEditClearPad,       0, "", ""},
  { "Clear &Window", kEditClearCanvas, 0, "", ""},

 /* View Menu */
  { "&Pad Editor", kViewEditor,      Qt::CTRL+Qt::Key_E, "", ""},
  { "&Tool bar",   kViewToolbar,     0, "", ""},
  { "&Status Bar", kViewEventStatus, 0, "", ""},
  { "&Explore",    kInspectBrowser, Qt::CTRL+Qt::Key_B, "Start ROOT Browser",               "browser.xpm"                 },
  { "&Zoomer",     kViewZoomer,     Qt::CTRL+Qt::Key_Z, "Attach the zoomer",                ""                            },

  { "&Color Box", kViewColors,       0, "", ""},
  { "&Font Box",  kViewFonts,        0, "", ""},
  { "&Markers",   kViewMarkers,      0, "", ""},
  { "&Iconify",   kViewIconify,      0, "", ""},

  { "OpenGL &3D View", kViewOpenGL,    0, "", ""},
  { "X&3D View",       kViewX3D,       0, "", ""},
  { "Coin3D View",     kViewInventorGL,0, "", ""},

  { "Interrupt", kOptionInterrupt,Qt::ALT+Qt::Key_C , "Send the interruption signal to the application", "interrupt.xpm"},
  { "Re&Fresh",   kOptionRefresh,  Qt::Key_F5,         "Refresh the TCanvas widget",       "refresh2.xpm"                },
  { "&Pad Auto Exec", kOptionAutoExec,         0, "", ""},
  { "&Resize Canvas", kOptionResizeCanvas,     0, "", ""},
  { "&Auto Resize Canvas", kOptionAutoResize,  0, "", ""},
  { "&Statistics", kOptionStatistics,          0, "", ""},
  { "&Histogram title", kOptionHistTitle,      0, "", ""},
  { "Fit &Params", kOptionFitParams,           0, "", ""},
  { "&Can Edit Histograms", kOptionCanEdit,    0, "", ""},

  { "Inspect",   kInspectRoot,    Qt::Key_F3,         "Inspect the ROOT objectwith the ROOT object inspector", "inspect.xpm" },
  { "Browser",   kInspectBrowser, Qt::CTRL+Qt::Key_B, "Start ROOT Browser",               "browser.xpm"                 },
  { "&Class Tree",kClassesTree,      0, "", ""},

  { "About",                 kHelpAbout,        0, "", ""},
  { "Help On Canvas...",     kHelpOnCanvas,     0, "", ""},
  { "Help On Menus...",      kHelpOnMenus,      0, "", ""},
  { "Help On Graphics Editor...",  kHelpOnGraphicsEd, 0, "", ""},
  { "Help On Browser...",    kHelpOnBrowser,    0, "", ""},
  { "Help On Objects...",    kHelpOnObjects,    0, "", ""},
  { "Help On PostScript...", kHelpOnPS,         0, "", ""},
  {0,0,0,"",""}
};

//____________________________________________________
static inline QString QtFileFormat(const char *selector)
{ return QtFileFormat(QString(selector)); }

//____________________________________________________
static inline  QString QtFileFormat(const QString &selector)
{
   // returns Qt file format
   return TGQt::QtFileFormat(selector);
}

//____________________________________________________
static inline QString RootFileFormat(const char *selector)
{  return RootFileFormat(QString(selector)); }
//____________________________________________________
static inline QString RootFileFormat(const QString &selector)
{   
   return TGQt::RootFileFormat(selector);
}
#if  ROOT_VERSION_CODE < ROOT_VERSION(4,03,03)   
static Bool_t glViewerLoadFlag = kFALSE;
#endif

TQtZoomPadWidget  *TQtCanvasImp::fgZoomingWidget = 0;

//______________________________________________________________________________
TQtCanvasImp::TQtCanvasImp()
: QObject(), TCanvasImp()
, fCanvasImpID(0),fCoinMenu(-1), fViewMenu(0),fEditor(0)
, fMenuBar(0),fOptionMenu(0),fDoubleBuffer(kTRUE) {;}
//______________________________________________________________________________
TQtCanvasImp::TQtCanvasImp(TCanvas *c, const char *name, UInt_t width, UInt_t height,bool initFlag)
:   QObject(), TCanvasImp(c, name, width, height)
 , fCanvasImpID(0),fX(0),fY(0),fWidth(width),fHeight(height), fCoinMenu(-1), fViewMenu(0) 
 , fFileToolBar(0),fToolBar(0),fEditToolBar(0),fEditor(0)
 , fMenuBar(0),fOptionMenu(0), fDoubleBuffer(kTRUE)  
{ 
   if (initFlag) InitWindow();
}
//______________________________________________________________________________
TQtCanvasImp::TQtCanvasImp(TCanvas *c, const char *name, Int_t x, Int_t y, UInt_t width, UInt_t height,bool initFlag)
:  QObject(), TCanvasImp(c, name,x,y,width, height)
 , fCanvasImpID(0),fX(x),fY(y),fWidth(width),fHeight(height), fCoinMenu(-1), fViewMenu(0)
 , fFileToolBar(0),fToolBar(0),fEditToolBar(0),fEditor(0)
 , fMenuBar(0),fOptionMenu(0), fDoubleBuffer(kTRUE)  
{
   if (initFlag) InitWindow();
}
//______________________________________________________________________________
TQtCanvasImp::~TQtCanvasImp()
{ 
#ifndef WIN32
  qApp->lock();
  Delete();
  qApp->unlock();
#endif
}
//______________________________________________________________________________
void TQtCanvasImp::Delete() 
{
   // Delete widget from the proper thread
   if (fCanvasImpID) {
      TCanvas *c =  Canvas();
      if (c) c->DisconnectWidget();
      fCanvasImpID->hide();
      if (c && c->GetCanvasID() != TGQt::iwid(((TGQt *)gVirtualX)->GetSelectedWindow()) ) 
         gVirtualX->SelectWindow ( TGQt::iwid(fCanvasID));
      fCanvasID = 0;
#if ROOT_VERSION_CODE < ROOT_VERSION(5,13,3) 
      // Stolen from the TRootCanvas::Close()
      if (fEditor) fEditor->DeleteEditors();
#endif      
#if 0      
      if (TVirtualPadEditor::GetPadEditor(kFALSE) != 0)
         TVirtualPadEditor::Terminate();
#else
      delete fEditor; fEditor = 0;
#endif      
      gVirtualX->CloseWindow();
      TQtCanvasWidget *wid = fCanvasImpID;
      fCanvasImpID = 0;
      disconnect(wid,SIGNAL(destroyed()),this,SLOT(Disconnect()));
      delete wid;
   }
}
//______________________________________________________________________________
void TQtCanvasImp::DrawEventStatus(const char *text, Int_t partidx)
{ 
  // Set text for 'partidx field
  SetStatusText(text,partidx);
} 
//______________________________________________________________________________
void TQtCanvasImp::MakeActions() {
   int i=0;
   while (gMenu_Data[i].fMenuText!=NULL) {
      // skip the separators 
      TQtRootAction *action = new TQtRootAction(fCanvasImpID,gMenu_Data[i]);
      fActions.insert(action->Id(),action);
      connect( action, SIGNAL( activated() ) , this, SLOT(ProcessMessage()) );
      i++;
   }
   MakeToolBarActions(i);
}
//______________________________________________________________________________
void TQtCanvasImp::MakeToolBarActions(Int_t /* firstId */)
{
   fEditToolBar = new TQtToolBar(fCanvasImpID);
}
//______________________________________________________________________________
void TQtCanvasImp::MakeMenu()
{
   if (!fCanvasImpID) return;
   if (fMenuBar) { delete fMenuBar; fMenuBar = 0; }
   QMenuBar   *mainMenu = fCanvasImpID->menuBar();
   fMenuBar = mainMenu;

    //---- toolbar. Add the action with the icon to the toolbar
#if QT_VERSION < 0x40000
   fFileToolBar = new QToolBar(fCanvasImpID);
#else /* QT_VERSION */
   fFileToolBar = new Q3ToolBar(fCanvasImpID);
#endif /* QT_VERSION */
   fCanvasImpID->addDockWindow(fFileToolBar);

#if QT_VERSION < 0x40000
   fToolBar = new QToolBar(fCanvasImpID);
#else /* QT_VERSION */
   fToolBar = new Q3ToolBar(fCanvasImpID);
#endif /* QT_VERSION */
   fCanvasImpID->addDockWindow(fToolBar);
   
   // fEditToolBar has been created at TQtCanvasImp::MakeToolBarAction()
   fCanvasImpID->addDockWindow(fEditToolBar);

   //    QPopupMenu *fileMenu = new QPopupMenu;
   //    fileMenu->insertItem( "New",  myView, SLOT(newFile()), CTRL+Key_N );
   //    fileMenu->insertItem( "Open", myView, SLOT(open()),    CTRL+Key_O );
   //    mainMenu->insertItem( "File", fileMenu );

   //*-*  Main Canvas menu items

   // Int_t iMainMenuStart = i;
#if QT_VERSION < 0x40000
   QPopupMenu *fileMenu      = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *fileMenu      = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&File",fileMenu);
#if QT_VERSION < 0x40000
   QPopupMenu *editMenu      = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *editMenu      = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&Edit",editMenu);

#if QT_VERSION < 0x40000
   QPopupMenu *viewMenu      = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *viewMenu      = new Q3PopupMenu();
#endif /* QT_VERSION */
   fViewMenu = viewMenu;
   mainMenu->insertItem("&View",viewMenu);


#if QT_VERSION < 0x40000
   QPopupMenu *optionsMenu   = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *optionsMenu   = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&Options",optionsMenu);
   fOptionMenu = optionsMenu;

#if QT_VERSION < 0x40000
   QPopupMenu *inspectorMenu = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *inspectorMenu = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&Inspector",inspectorMenu);

#if QT_VERSION < 0x40000
   QPopupMenu *classesMenu   = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *classesMenu   = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&Classes",classesMenu);

   mainMenu->insertSeparator();
#if QT_VERSION < 0x40000
   QPopupMenu *helpMenu   = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *helpMenu   = new Q3PopupMenu();
#endif /* QT_VERSION */
   mainMenu->insertItem("&Help",helpMenu);

   //*-*   Items for the File Menu

   fActions[kFileNewCanvas]->addTo(fileMenu);                    fActions[kFileNewCanvas]->addTo(fFileToolBar);
   fActions[kFileOpen]     ->addTo(fileMenu);                    fActions[kFileOpen]     ->addTo(fFileToolBar);
   fileMenu->                                 insertSeparator();
   fActions[kFileCloseCanvas]->addTo(fileMenu);
   fileMenu->                                 insertSeparator();
   fActions[kFileSave]     ->addTo(fileMenu);                    fActions[kFileSave]     ->addTo(fFileToolBar);
   fActions[kFileSaveAs]   ->addTo(fileMenu);                    fActions[kFileSaveAs]   ->addTo(fFileToolBar);
   fActions[kFileSaveAsWeb]->addTo(fileMenu);                    fActions[kFileSaveAsWeb]->addTo(fFileToolBar);
   fileMenu->                                 insertSeparator();
   fActions[kFilePrint]    ->addTo(fileMenu);                    fActions[kFilePrint]    ->addTo(fFileToolBar);
   fileMenu->                                 insertSeparator();
   fActions[kFileQuit]     ->addTo(fileMenu);
   fActions[kFileExit]     ->addTo(fileMenu);


   //*-*   Items for the Edit Menu

   //  editMenu->insertItem("Undo","&Undo",SLOT(UnDoCB));
   fActions[kEditCopy]       ->addTo(editMenu);
   fActions[kEditCopyFrame]  ->addTo(editMenu);
   editMenu->                                  insertSeparator();
   fActions[kViewEditor]     ->addTo(editMenu);
      fActions[kViewEditor]->setToggleAction(true);
      fActions[kViewEditor]->setOn(gStyle->GetShowEditor());
   editMenu->                                  insertSeparator();
#if QT_VERSION < 0x40000
   QPopupMenu *clearMenu = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *clearMenu = new Q3PopupMenu();
#endif /* QT_VERSION */
   editMenu->insertItem("C&lear",clearMenu);

   fActions[kEditClearPad]   ->addTo(clearMenu);
   fActions[kEditClearCanvas]->addTo(clearMenu);

   //*-*   Items for the View

   fActions[kViewEditor] ->addTo(viewMenu);
   fActions[kViewToolbar]->addTo(viewMenu);   
      fActions[kViewToolbar]->setToggleAction(true);
      if (gStyle->GetShowToolBar()) {
         fActions[kViewEventStatus]->setOn(true);
      } else {
         fActions[kViewEventStatus]->setOn(false);
         fFileToolBar->hide();
         fToolBar->hide();
         fEditToolBar->hide();
      }
   fActions[kViewEventStatus]->addTo(viewMenu);
      fActions[kViewEventStatus]->setToggleAction(true);
      fActions[kViewEventStatus]->setOn(gStyle->GetShowEventStatus());
   fActions[kInspectBrowser] ->addTo(viewMenu);
   fActions[kViewZoomer] ->addTo(viewMenu);
      fActions[kViewZoomer]->setToggleAction(true);
      fActions[kViewZoomer]->setOn(false);
   
   viewMenu->                                  insertSeparator();
   fActions[kViewColors] ->addTo(viewMenu);
   fActions[kViewFonts]  ->addTo(viewMenu);
   fActions[kViewMarkers]->addTo(viewMenu);
   fActions[kViewIconify]->addTo(viewMenu);
   viewMenu->                                  insertSeparator();
#if QT_VERSION < 0x40000
   QPopupMenu *viewWithMenu = new QPopupMenu();
#else /* QT_VERSION */
   Q3PopupMenu *viewWithMenu = new Q3PopupMenu();
#endif /* QT_VERSION */
   viewMenu->insertItem("View &3D With",viewWithMenu);

#ifdef WIN32
   fActions[kViewOpenGL ]->addTo(viewWithMenu);
#else
   fActions[kViewX3D]    ->addTo(viewWithMenu);
   
#  if ROOT_VERSION_CODE >= ROOT_VERSION(4,01,00)
      fActions[kViewX3D]    ->setEnabled(FALSE);
#  endif
   
   fActions[kViewOpenGL] ->addTo(viewWithMenu);
#endif
   // Check whether we haved OpenGL plugin
   char *libRQTGL = gSystem->DynamicPathName("libRQTGL",kTRUE);
   fActions[kViewOpenGL]->setEnabled(libRQTGL);
   delete [] libRQTGL;
   {
      fActions[kViewInventorGL]->addTo(viewWithMenu); 
      // Check whether we haved OpenInventor plugin
      libRQTGL = gSystem->DynamicPathName("libRQIVTGL",kTRUE);
      fActions[kViewInventorGL]->setEnabled(libRQTGL);
      delete [] libRQTGL;
   }

   //*-*   Items for the Options Menu
 
   fActions[kViewEventStatus]   ->addTo(optionsMenu);
   fActions[kOptionAutoExec]    ->addTo(optionsMenu);
   optionsMenu->                                  insertSeparator();
   fActions[kOptionAutoResize]  ->addTo(optionsMenu);
   fActions[kOptionResizeCanvas]->addTo(optionsMenu);
   optionsMenu->                                  insertSeparator();
   fActions[kOptionInterrupt]   ->addTo(optionsMenu);             fActions[kOptionInterrupt]  ->addTo(fToolBar); 
   fActions[kOptionRefresh]     ->addTo(optionsMenu);             fActions[kOptionRefresh]    ->addTo(fToolBar); 
   optionsMenu->                                  insertSeparator();

   fActions[kOptionStatistics]  ->addTo(optionsMenu);
   fActions[kOptionStatistics]->setToggleAction(true);
   fActions[kOptionStatistics]->setOn(gStyle->GetOptStat());

   fActions[kOptionHistTitle]   ->addTo(optionsMenu);
   fActions[kOptionHistTitle]->setToggleAction(true);
   fActions[kOptionHistTitle]->setOn(gStyle->GetOptTitle());

   fActions[kOptionFitParams]   ->addTo(optionsMenu);
   fActions[kOptionFitParams]->setToggleAction(true);
   fActions[kOptionFitParams]->setOn(gStyle->GetOptFit());

   fActions[kOptionCanEdit]     ->addTo(optionsMenu);
   fActions[kOptionCanEdit]->setToggleAction(true);
   fActions[kOptionCanEdit]->setOn(gROOT->GetEditHistograms());

   //*-*   Items for the Inspect Menu

   fActions[kInspectRoot]->addTo(inspectorMenu);                   fActions[kInspectRoot]    ->addTo(fToolBar); 
   fActions[kInspectBrowser]->addTo(inspectorMenu);                fActions[kInspectBrowser]    ->addTo(fToolBar); 

   //*-*   Items for the Class Menu

   fActions[kClassesTree]->addTo(classesMenu);


//   fActions[kHelpHelp]        ->addTo(helpMenu);
   fActions[kHelpOnCanvas]    ->addTo(helpMenu);
   fActions[kHelpOnMenus]     ->addTo(helpMenu);
   fActions[kHelpOnGraphicsEd]->addTo(helpMenu);
   fActions[kHelpOnBrowser]   ->addTo(helpMenu);
   fActions[kHelpOnObjects]   ->addTo(helpMenu);
   fActions[kHelpOnPS]        ->addTo(helpMenu);
   helpMenu->                                   insertSeparator();
   fActions[kHelpAbout]       ->addTo(helpMenu);

}

//______________________________________________________________________________
void TQtCanvasImp::FitCanvas(){}
//______________________________________________________________________________
void TQtCanvasImp::Lock()
{
   // Lock updating canvas.
  if (!fCanvasImpID) fCanvasImpID->setUpdatesEnabled(FALSE);
}

//______________________________________________________________________________
void TQtCanvasImp::Unlock()
{
   //  Unlock updating canvas.

  if (!fCanvasImpID) fCanvasImpID->setUpdatesEnabled(TRUE);
}
//______________________________________________________________________________
Bool_t TQtCanvasImp::IsLocked() 
{  
   if (fCanvasImpID) return !fCanvasImpID->isUpdatesEnabled();
   return kFALSE; 
}
//______________________________________________________________________________
void TQtCanvasImp::Close() 
{ 
  // if (fCanvasImpID) fCanvasImpID->topLevelWidget()->close();
  Delete();
}
//______________________________________________________________________________
void TQtCanvasImp::ReallyDelete()
{
   // Really delete the canvas and this GUI.
   if (fCanvasImpID) fCanvasImpID->hide();
   TVirtualPad *savepad = gPad;
   gPad = 0;        // hide gPad from CINT
   gInterpreter->DeleteGlobal(fCanvas);
   gPad = savepad;  // restore gPad for ROOT
//   Delete();
   TCanvas *c = fCanvas; fCanvas = 0;
   delete c;  // will in turn delete this object

}
//______________________________________________________________________________
void TQtCanvasImp::ForceUpdate()
{
   fprintf(stderr," TQtCanvasImp::ForceUpdate();\n");

}
//______________________________________________________________________________
#if ROOT_VERSION_CODE > ROOT_VERSION(4,00,4) 
UInt_t TQtCanvasImp::GetWindowGeometry(Int_t &x, Int_t &y, UInt_t &w, UInt_t &h)
#else
void   TQtCanvasImp::GetWindowGeometry(Int_t &x, Int_t &y, UInt_t &w, UInt_t &h);
#endif   
{
  // Get effective window parameters (with borders and menubar)
   QRect rect = fCanvasImpID->topLevelWidget()->frameGeometry();
   x = rect.x();
   y = rect.y();
   w = rect.width();
   h = rect.height();
//   if (!fCanvas->GetShowEditor()) return 0;
//   return fEditorFrame->GetWidth();
#if ROOT_VERSION_CODE > ROOT_VERSION(4,00,4) 
   return 0;
#endif   
}
//______________________________________________________________________________
void TQtCanvasImp::Iconify()
{
  if (fCanvasImpID) fCanvasImpID->topLevelWidget()->showMinimized();
}
//______________________________________________________________________________
Int_t TQtCanvasImp::InitWindow()
{
  if (!fCanvasImpID) 
  {
     // fprintf(stderr,"TQtCanvasImp::InitWindow: ");
    fCanvasImpID = new TQtCanvasWidget (0,gVirtualX->GetName(),Qt::WDestructiveClose|Qt::WType_TopLevel);
    connect(fCanvasImpID,SIGNAL(destroyed()),this,SLOT(Disconnect()));
//    fCanvasID = (TQtWidget *)TGQt::iwid(gVirtualX->InitWindow(TGQt::iwid(fCanvasImpID)));
    fCanvasID = (TQtWidget *)TGQt::iwid(gVirtualX->InitWindow(0));
    fCanvasID->reparent(fCanvasImpID,QPoint(0,0));
    // printf(" %d \n",  fCanvasID->isTopLevel());
    fCanvasID->SetCanvas(Canvas());
//    fCanvasID->resize(fWidth,fHeight);

#if 0 
#if QT_VERSION < 0x40000
    QScrollView *view = new QScrollView (0,"canvasscroll");
#else /* QT_VERSION */
    Q3ScrollView *view = new Q3ScrollView (0,"canvasscroll");
#endif /* QT_VERSION */
    view->addChild(fCanvasID);
    fCanvasImpID->setCentralWidget (view);
#else
    fCanvasImpID->setCentralWidget (fCanvasID);
#endif
 
    int parts[] = {43,7,10,39};
    CreateStatusBar(parts,4);
    fCanvasImpID->statusBar()->hide();
    MakeActions();
    MakeMenu();

    fCanvasImpID->move(fX,fY);
#ifndef WIN32
    // Now try to figure out the full size of the main window.
    // = (Canvas size) + (frame size) + (menu bar size)
    QSize fullSize =   QSize(fWidth,fHeight) 
                     + (fCanvasImpID->frameSize() - fCanvasImpID->size())  + QSize(0,3)
                     + QSize(0,fCanvasImpID->menuBar()->frameSize().height());
    fCanvasImpID->resize(fullSize);
#else
    fCanvasImpID->resize(fWidth,fHeight);
#endif

    fCanvasID->resize(fWidth,fHeight);
  }
  assert(Canvas()->GetCanvasID() == -1 ||  Canvas()->GetCanvasID() != TGQt::iwid(fCanvasID));
  // fprintf(stderr," TQtCanvasImp::InitWindow() %d \n",TGQt::iwid(fCanvasID));
  return TGQt::iwid(fCanvasID);
}
//______________________________________________________________________________
void TQtCanvasImp::Disconnect()
{
  qApp->lock();
  if (fCanvasImpID) {
     fCanvasImpID = 0;
     TCanvas *c = Canvas();
     if (c && c->IsOnHeap() ) {
       c->DisconnectWidget();
       if (c->GetCanvasID() == TGQt::iwid(((TGQt *)gVirtualX)->GetSelectedWindow()) ) 
       {
          // To close QPainter properly
         gVirtualX->SelectWindow(-1);
       }
       ReallyDelete();
       // delete c;
     }
  }
  qApp->unlock();
}
//______________________________________________________________________________
void TQtCanvasImp::NewCanvas()
{
  gROOT->GetMakeDefCanvas()();
}
//______________________________________________________________________________
void TQtCanvasImp::CreateStatusBar(Int_t nparts)
{
  QStatusBar *statusBar = fCanvasImpID->statusBar();
  Int_t i=0;
  fStatusBar.resize(nparts);
  for (i=0;i<nparts;i++) {
    QLabel *l = new QLabel(statusBar);
    statusBar->addWidget(l,1,TRUE);

    // remember to delete later
    fStatusBar.insert(i,l);  
  }
}
//______________________________________________________________________________
void TQtCanvasImp::CreateStatusBar(Int_t *parts, Int_t nparts)
{
  QStatusBar *statusBar = fCanvasImpID->statusBar();
#ifdef WIN32
  statusBar->setSizeGripEnabled(FALSE);
#endif
  // Any number of widgets may be controlled by just
  // one splitter
  QSplitter *split = new QSplitter(statusBar);
  statusBar->addWidget(split,1,FALSE);

  fStatusBar.resize(nparts);
  Int_t iField=0;
  for (iField=0; iField<nparts; iField++) {
    QLabel *infoBox = new QLabel(split);
    infoBox->setIndent(3);
    QSize s = infoBox->size();
    s.setWidth(parts[iField]);
    infoBox->resize(s);

    // remember to delete later
    fStatusBar.insert(iField,infoBox);
  }
}
//______________________________________________________________________________
void  TQtCanvasImp::ProcessMessage()
{
   TQtRootAction *actionSender =  (TQtRootAction *)sender ();
   switch (actionSender->Id()) {

   case kFileNewCanvas:    NewCB();    break;
   case kFileOpen:         OpenCB();   break;
   case kFileSave:         SaveCB();   break;
   case kFileSaveAs:       SaveAsCB(); break;
   case kFileSaveAsWeb:    SaveAsWebCB();break;
   case kFilePrint:        PrintCB();  break;
   case kFileCloseCanvas:  CloseCB();  break;
   case kFileQuit:         QuitCB();   break;
   case kFileExit:         QuitCB();   break;
 
   case kEditCut:          CB();            break;
   case kEditCopy:         CopyCB();        break;
   case kEditPaste:        CB();            break;
   case kEditClearPad:     ClearPadCB();    break;
   case kEditClearCanvas:  ClearCanvasCB(); break;
   case kEditUndo:         CB();            break;
   case kEditRedo:         CB();            break;

   case kViewEditor:       EditorCB();      break;
   case kViewToolbar:      ToolBarCB();     break;
   case kViewEventStatus:  EventStatusCB(); break;
   case kViewColors:       ColorsCB();      break;
   case kViewFonts:        FontsCB();       break;
   case kViewMarkers:      MarkersCB();     break;
   case kViewIconify:      IconifyCB();     break;
   case kViewX3D:          X3DViewCB();     break;
   case kViewOpenGL:       GLViewCB();      break;
   case kViewInventorGL:   GLIVViewCB();    break;
   case kViewZoomer:       ZoomCB();        break;

   case kOptionAutoResize:    CB();         break;
   case kOptionResizeCanvas:  CB();         break;
   case kOptionMoveOpaque:    CB();         break;
   case kOptionResizeOpaque:  CB();         break;
   case kOptionInterrupt:  InterruptCB();   break;
   case kOptionRefresh:    RefreshCB();     break;
   case kOptionAutoExec:   PadAutoExecCB(); break;
   case kOptionStatistics: OptStatCB();     break;
   case kOptionHistTitle:  OptTitleCB();    break;
   case kOptionFitParams:  OptFitCB();      break;
   case kOptionCanEdit:    CanEditHistogramsCB(); break;

   case kInspectRoot:      ROOTInspectCB(); break;
   case kInspectBrowser:   BrowserCB();     break;

   case kClassesTree:      FullTreeCB();    break;

   case kHelpAbout:        AboutCB();            break;
   case kHelpOnCanvas:     HelpOnCanvasCB();     break;
   case kHelpOnMenus:      HelpOnMenusCB();      break;
   case kHelpOnGraphicsEd: HelpOnGraphicsEdCB(); break;
   case kHelpOnBrowser:    HelpOnBrowserCB();    break;
   case kHelpOnObjects:    HelpOnObjectsCB();    break;
   case kHelpOnPS:         HelpOnPSCB();         break;

   default:
      break;

   };

}

//______________________________________________________________________________
void TQtCanvasImp::RootExec(const char* /*cmd*/){assert(0);}

//______________________________________________________________________________
void TQtCanvasImp::SetCanvasSize(UInt_t w, UInt_t h)
{ 
   printf("It is not clear what SetCanvasSize differs from SetWindowSize\n");
   fCanvasImpID->resize(w,h);
}

//______________________________________________________________________________
void TQtCanvasImp::SetWindowPosition(Int_t x, Int_t y)
{
   fCanvasImpID->move(x,y);
}
//______________________________________________________________________________
void TQtCanvasImp::SetWindowSize(UInt_t w, UInt_t h) 
{ 
   fCanvasImpID->resize(w,h);
}
//______________________________________________________________________________
void TQtCanvasImp::SetWindowTitle(const Text_t *newTitle) 
{ 
   fCanvasImpID->setCaption(newTitle);
}
//______________________________________________________________________________
void TQtCanvasImp::SetStatusText(const char *text, Int_t partidx)
{
  // Set Text into the 'npart'-th part of the status bar
  if (Int_t(fStatusBar.size()) > partidx) {
    fStatusBar[partidx]->setText(text);
  }
} 
//______________________________________________________________________________
void TQtCanvasImp::ShowEditor(Bool_t show)
{
   // fprintf(stderr,"QtCanvasImp::ShowEditor %d\n",show);

   // Canvas()->ToggleEditor();  / Toogle call ShowEditor !!!
   TVirtualPad *savedPad = 0;
   savedPad = (TVirtualPad *) gPad;
   gPad = Canvas();
   
   if (show) {
      if (!fActions[kViewEditor]->isOn()) 
         fActions[kViewEditor]->setOn(true);
      if (!fEditor) CreateEditor();
      if (fEditor) fEditor->Show();
   } else {
      if (fActions[kViewEditor]->isOn()) 
         fActions[kViewEditor]->setOn(false);
      if (fEditor) fEditor->Hide();
   }
   if (savedPad) gPad = savedPad;
}
//______________________________________________________________________________
void TQtCanvasImp::ShowMenuBar(Bool_t show)
{
  if (show) fMenuBar->show();
  else fMenuBar->hide();
}
//______________________________________________________________________________
void TQtCanvasImp::ShowStatusBar(Bool_t show)
{
  if (show) fCanvasImpID->statusBar()->show(); 
  else      fCanvasImpID->statusBar()->hide(); 
#if 0
  TCanvas *c = Canvas();
  if (c) {
    c->Modified();
    c->Update();
  }
#endif  
}
//______________________________________________________________________________
void TQtCanvasImp::ShowToolBar(Bool_t show)
{
   // Show or hide toolbar.
   if (show) {
       if (!fActions[kViewToolbar]->isOn()) 
          fActions[kViewToolbar]->setOn(true);
       fFileToolBar->show();
       fToolBar->show();
       fEditToolBar->show();
    } else {
       if (fActions[kViewToolbar]->isOn()) 
          fActions[kViewToolbar]->setOn(false);
       fFileToolBar->hide();
       fToolBar->hide();
       fEditToolBar->hide();
    }
}
//______________________________________________________________________________
void TQtCanvasImp::Show(){
  if (fCanvasImpID) {
     fCanvasImpID->show();
//    gVirtualX->MapRaised(TGQt::iwid(fCanvasImpID));
  }
}
//______________________________________________________________________________
void TQtCanvasImp::NewCB()
{ 
  NewCanvas();
}
//______________________________________________________________________________
void TQtCanvasImp::OpenCB()
{
   static QString thisCintCommand;
   static QString filetypes = "ROOT files (*.root);;";
   if( Canvas()) {
      QString selectedFilter;
      QString dir = fSaveFileName;
      if (dir.isEmpty()) dir = gSystem->WorkingDirectory(); 
      else               dir = QFileInfo(dir).dirPath();

#if QT_VERSION < 0x40000
      QString fOpenFileName = QFileDialog::getOpenFileName (dir
#else /* QT_VERSION */
      QString fOpenFileName = Q3FileDialog::getOpenFileName (dir
#endif /* QT_VERSION */
         , filetypes, fCanvasImpID, "Open"
         , "Open ROOT file "
         , &selectedFilter);      
      if (!fOpenFileName.isEmpty()){
         thisCintCommand = "{new TFile(\"";
         thisCintCommand += fOpenFileName;
         thisCintCommand +="\",\"update\");}";
         gROOT->ProcessLine((const char *)thisCintCommand);
      }
   }
}

//______________________________________________________________________________
void TQtCanvasImp::SaveCB()
{ 
   if (!(fSaveFileName.isEmpty() ||  fSaveType.isEmpty()) ) 
      SaveFile(fSaveFileName,fSaveType);
   else 
      SaveAsCB();
}

//______________________________________________________________________________
void TQtCanvasImp::SaveAsCB()
{ 
  QString filter = 
      "C++ macro (*.cpp,*.cxx,*.C);"
     ";Postscript (*.ps);"
     ";Encapsulated Postscript  (*.eps);"
     ";Portable Document Format (*.pdf);"
     ";Scalable Vector Graphics (*.svg);"
     ";Extensible Markup Language (*.xml);"
     ";Web page (*.html);"
     ";ROOT file (*.root);"
     ";Image (";

  UInt_t i=0;
#if QT_VERSION < 0x40000
  for (i = 0; i < QImageIO::outputFormats().count(); i++ ) 
#else
  QList<QByteArray> formats =  QImageWriter::supportedImageFormats();
  QList<QByteArray>::const_iterator j;
  for (j = formats.constBegin(); j != formats.constEnd(); ++j)
#endif
  {
    if (i) filter +=',';
    filter += "*.";
#if QT_VERSION < 0x40000
    QString str = QString( QImageIO::outputFormats().at( i ) );
#else
    QString str =  *j; i++;
#endif
    filter += str.lower();
  }
  filter +=");";
  filter +=";all files (*.*);;";

  QString selectedFilter;

#if QT_VERSION < 0x40000
  QString thatFile = QFileDialog::getSaveFileName(gSystem->WorkingDirectory()
#else /* QT_VERSION */
  QString thatFile = Q3FileDialog::getSaveFileName(gSystem->WorkingDirectory()
#endif /* QT_VERSION */
    , filter, fCanvasImpID, "SaveAs"
    , "Save the selected Canvas/Pad as"
    , &selectedFilter);

  if (thatFile.isEmpty()) return;
  SaveFile(thatFile,selectedFilter);
}


//______________________________________________________________________________
void TQtCanvasImp::SaveAsWebCB()
{ 
  QString filter = "Web page (*.html);";

#if QT_VERSION < 0x40000
  QString thatFolder = QFileDialog::getExistingDirectory(gSystem->WorkingDirectory()
    , fCanvasImpID, "SaveAsWeb"
    , "Select the folder to save the Canvas/Pad as Web site" );
#else /* QT_VERSION */
  QString thatFolder = QFileDialog::getExistingDirectory(
          fCanvasImpID
        , "Select the folder to save the Canvas/Pad as Web site"
        , gSystem->WorkingDirectory());
#endif /* QT_VERSION */

   if (thatFolder.isEmpty()) return;
   if (fActions[kViewZoomer]->isOn() ) {
       TQtCanvas2Html a(Canvas(),1,(const char *)thatFolder,fgZoomingWidget);
   } else {
       TQtCanvas2Html a(Canvas(),1.8,(const char *)thatFolder);
   }
}


//______________________________________________________________________________
void TQtCanvasImp::SaveFile(const QString &theFile, const QString &selectedFilter)
{
  //
  // selectedFilter contains "*.* - the output formnat is defined by the file extension
  //                        != *.* - outputformat is defined by the seleted filter
  QString thatFile = theFile;
  QString e;
  bool rootFormatFound = kTRUE;
  fprintf(stderr,"Selected filter %s \n", (const char *)selectedFilter);

  //  define the file extension
  QString fileNameExtension = QFileInfo(thatFile).extension(FALSE);
  QString  saveType = fileNameExtension.upper();

  if (selectedFilter.contains("*.*")) {
     if (!fileNameExtension.isEmpty() ) {
         saveType =  RootFileFormat(fileNameExtension);
         if (saveType.isEmpty() )  {
            rootFormatFound = kFALSE;
            saveType = QtFileFormat(fileNameExtension);
         }
     } 
  } else {
     saveType =  RootFileFormat(selectedFilter);
     if (saveType.isEmpty() && !selectedFilter.contains("html"))  {
        rootFormatFound = kFALSE;
        saveType = QtFileFormat(fileNameExtension);
     }
     if (saveType.isEmpty() && selectedFilter.contains("html"))  {
        rootFormatFound = kFALSE;
        saveType = "HTML";
     }
  }

  if (saveType.isEmpty() ) {
     TCanvas *c =  Canvas();
     if (c) c->Error("Save As", "no image format is defined");
     return;
  }
  fSaveType      = saveType;
  fSaveFileName  = theFile;

//   if (! thatFile.contains('.'))  thatFile += '.';
//   if (thatFile.at(thatFile.length()-1) == '.')  thatFile += defExtension[i];
  
  fprintf(stderr, "Save %d:<%s> file as \"%s\"\n",rootFormatFound,(const char *)fSaveFileName, (const char *)fSaveType);
  if (fSaveType == "HTML") {
     if (fActions[kViewZoomer]->isOn() ) {
        TQtCanvas2Html a(Canvas(),1,0,fgZoomingWidget);
     } else {
        TQtCanvas2Html a(Canvas());
     }
  } else {
       fCanvasID->Save(fSaveFileName,fSaveType);
  }
}
//____________________________________________________________________________
void TQtCanvasImp::PrintCB()
{ 
  QPrinter p;
  if (p.setup()) {     
    QPixmap *pix = &fCanvasID->GetBuffer(); //(QPixmap *)TGQt::iwid(c->GetCanvasID());
    QPainter pnt(&p);
    pnt.drawPixmap(0,0,*pix);
  }
}

//______________________________________________________________________________
void TQtCanvasImp::CloseCB()
{
  TCanvas *c = Canvas();
  if (c && c->IsOnHeap() )  delete c;
}

//______________________________________________________________________________
void TQtCanvasImp::QuitCB()
{
   if (gROOT->GetClass("TStyleManager"))
     gROOT->ProcessLine("TStyleManager::Terminate()");
   gApplication->Terminate(0);
}

// editor menu 
//______________________________________________________________________________
void TQtCanvasImp::CopyCB()
{
//  Copy the current gPad to the system clipboard 
  QPixmap *p = 0;
  if (gPad == gPad->GetCanvas() ) {
    // Copy the double buffer of the TCanvas
    p = &fCanvasID->GetBuffer();
  } else {
    // Get the selected TPad only
    p = (QPixmap *)TGQt::iwid(gPad->GetPixmapID());
  }
  if (p) {
     QClipboard *cb = QApplication::clipboard();
     cb->setPixmap(*p);
  }
}

//______________________________________________________________________________
void TQtCanvasImp::CopyFrameCB()
{
  // Copy the entire window including the menu and the status bar
  QClipboard *cb = QApplication::clipboard();
  cb->setPixmap(QPixmap::grabWidget(fCanvasImpID->topLevelWidget()));
}

//______________________________________________________________________________
void TQtCanvasImp::EditorCB()
{
  // Canvas()->EditorBar(); 
   TCanvas *c = Canvas();
   // This is XOR operation
   if (c && (c->GetShowEditor() && !fActions[kViewEditor]->isOn()  ||
            !c->GetShowEditor() &&  fActions[kViewEditor]->isOn()) )
            {
                 Canvas()->ToggleEditor();
            }
//     ShowEditor(fActions[kViewEditor]->isOn());
}

//______________________________________________________________________________
void TQtCanvasImp::CreateEditor()
{
   // Create editor.
#if 0
   if (TVirtualPadEditor::GetPadEditor(kFALSE) != 0) {
      TVirtualPadEditor::HideEditor();
   }
#endif   
  // fEditorFrame->SetEditable();
  // gPad = Canvas();
   TString show = gEnv->GetValue("Canvas.ShowEditor","false");
   gEnv->SetValue("Canvas.ShowEditor","true");
   gPad = Canvas();
   fEditor = TVirtualPadEditor::LoadEditor();
   fEditor->SetGlobal(kFALSE);

   // next line is related to the old editor
   if (show == "false") gEnv->SetValue("Canvas.ShowEditor","false");
}
//______________________________________________________________________________
void TQtCanvasImp::ClearPadCB()
{
   gPad->Clear();
   gPad->Modified();
   gPad->Update();
}
//______________________________________________________________________________
void TQtCanvasImp::ClearCanvasCB()
{
   TCanvas *c = Canvas();
   if (!c) return;
   c->Clear();
   c->Modified();
   c->Update();
}

//______________________________________________________________________________
void TQtCanvasImp::BrowserCB()
{ new TBrowser("browser"); }
//______________________________________________________________________________
void TQtCanvasImp::ZoomCB()
{
   // Activate the Qt Zoomer
   
   TQtRootAction *action = (TQtRootAction *)sender();
   if (!fgZoomingWidget && (action->isOn()))  {
       fgZoomingWidget = new TQtZoomPadWidget();
#if QT_VERSION < 0x40000
       QWhatsThis::display("<P>Click any <b>TPad</b> object with the <b>middle</b> mouse button to zoom it out");
#else /* QT_VERSION */
       Q3WhatsThis::display("<P>Click any <b>TPad</b> object with the <b>middle</b> mouse button to zoom it out");
#endif /* QT_VERSION */
   }
   if (action->isOn()) { 
       fgZoomingWidget->Connect(fCanvasID);
   } else {
       fgZoomingWidget->Disconnect(fCanvasID);
   }
}
//______________________________________________________________________________
void TQtCanvasImp::ColorsCB()
{
  TVirtualPad *padsav = gPad->GetCanvas();
  char defcanvas[32];
  strcpy(defcanvas,gROOT->GetDefCanvasName());
  gROOT->SetDefCanvasName("DisplayColors");
  (gROOT->GetMakeDefCanvas())();
  gROOT->SetDefCanvasName(defcanvas);
  TPad::DrawColorTable();
  gPad->Update();
  padsav->cd();
}
//______________________________________________________________________________
void TQtCanvasImp::FontsCB()
{ printf(" TQtCanvasImp::FontsCB() \n"); }
//______________________________________________________________________________
void TQtCanvasImp::MarkersCB()
{
  TVirtualPad *padsav = gPad->GetCanvas();
  TCanvas *m = new TCanvas("markers","MarkersTypes",600,200);
  TMarker::DisplayMarkerTypes();
  m->Update();
  padsav->cd();
}
//______________________________________________________________________________
void TQtCanvasImp::IconifyCB()
{ Iconify(); }
//______________________________________________________________________________
void TQtCanvasImp::X3DViewCB()
{  
  // Create X3d viewer
  // This entry for X11 only. It is never called under WIN32
#if  ROOT_VERSION_CODE >= ROOT_VERSION(4,03,3)   
      fprintf(stderr,"  There is no 3D viewer implementation with the Qt layer for ROOT 4.03 yet !!!\n");
#else   
  gPad->x3d();
#endif  
}
//______________________________________________________________________________
void TQtCanvasImp::GLViewCB()
{  
   // Load Qt-based GL viewer first
   // // static bool loadFlag = TRUE;
   // if (loadFlag) loadFlag = gQt->LoadQt("libRQTGL");
#if  ROOT_VERSION_CODE >= ROOT_VERSION(4,03,03)   
   TVirtualViewer3D *viewer = TVirtualViewer3D::Viewer3D(gPad,"ogl");
   if (viewer) {
      // Create Open GL viewer
      TGQt::SetCoinFlag(0);
      viewer->BeginScene();
      viewer->EndScene();
   }
#else   
   if (! glViewerLoadFlag) {
      glViewerLoadFlag = !gQt->LoadQt("libRQTGL");
   }
   if (glViewerLoadFlag) {
      // Create Open GL viewer
      TGQt::SetCoinFlag(0);
      gPad->x3d("OPENGL");
   }
#endif  
   else {
      fViewMenu->setItemEnabled(fCoinMenu, false);
   }
}
//______________________________________________________________________________
void TQtCanvasImp::GLIVViewCB()
{  
   // Create Open GL viewer
   // Load Qt-based GL viewer first
   // static bool loadFlag = TRUE;
   // if (loadFlag) loadFlag = gQt->LoadQt("libRQIVTGL");
#if  ROOT_VERSION_CODE >= ROOT_VERSION(4,03,3)
   TVirtualViewer3D *viewer = TVirtualViewer3D::Viewer3D(gPad,"oiv");
   if (viewer) {
      // Create Open GL viewer
      TGQt::SetCoinFlag(1);
      fprintf(stderr,"  There is no X3D viewer implementation with the Qt layer for ROOT 4.03 yet !!!\n");
      viewer->BeginScene();
      viewer->EndScene();
    }
#else
   if (! glViewerLoadFlag) {
      glViewerLoadFlag = !gQt->LoadQt("libRQTGL");
   }
   if (glViewerLoadFlag) {
      // Create Open GL viewer
      TGQt::SetCoinFlag(1);
      gPad->x3d("OPENGL");
   }
#endif
   else {
      fViewMenu->setItemEnabled(fCoinMenu, false);
   }
}

//______________________________________________________________________________
void TQtCanvasImp::InterruptCB()
{ gROOT->SetInterrupt(); }
//______________________________________________________________________________
void TQtCanvasImp::ModifiedUpdate()
{
   gPad->Modified();
   Canvas()->Modified();
   Canvas()->Update();
}
//______________________________________________________________________________
void TQtCanvasImp::AutoFitCanvasCB()
{}
//______________________________________________________________________________
void TQtCanvasImp::FitCanvasCB()
{}
//______________________________________________________________________________
void TQtCanvasImp::RefreshCB()
{  
   TCanvas *c = Canvas();
   if (!c) return;
   c->Paint();
   ModifiedUpdate();
}
//______________________________________________________________________________
void TQtCanvasImp::MenuBarCb()
{
  // ShowMenuBar(fActions[kViewMenuBar]->isOn());

}
//______________________________________________________________________________
void TQtCanvasImp::ToolBarCB()
{
   ShowToolBar(fActions[kViewToolbar]->isOn());
}
//______________________________________________________________________________
void TQtCanvasImp::EventStatusCB()
{  
   TCanvas *c = Canvas();
   if (!c) return;
   TQtRootAction *action = (TQtRootAction *)sender();
   c->ToggleEventStatus();
   if (c->GetShowEventStatus())
   {
      ShowStatusBar();
      if (!action->isOn()) action->setOn(true);
   }
   else {
      if (action->isOn()) action->setOn(false);
      ShowStatusBar(kFALSE);
   }
   ModifiedUpdate();
}
//______________________________________________________________________________
void TQtCanvasImp::PadAutoExecCB()
{
   TQtRootAction *action = (TQtRootAction *)sender();
   TCanvas *c = Canvas();
   if (c) {
      c->ToggleAutoExec();
      if (c->GetAutoExec() != action->isOn() ) 
         action->setOn(c->GetAutoExec());
      ModifiedUpdate();
   }
}

//______________________________________________________________________________
void TQtCanvasImp::OptStatCB()
{
   TQtRootAction *action = (TQtRootAction *)sender();
   if (gStyle->GetOptStat()) {
      gStyle->SetOptStat(0);
      delete gPad->FindObject("stats");
      if (action->isOn()) action->setOn(false);
   } else {
      gStyle->SetOptStat(1);
      if (!action->isOn()) action->setOn(true);
   }
   ModifiedUpdate();
}
//______________________________________________________________________________
void TQtCanvasImp::OptTitleCB()
{
   TQtRootAction *action = (TQtRootAction *)sender();
   if (gStyle->GetOptTitle()) {
      gStyle->SetOptTitle(0);
      delete gPad->FindObject("title");
      if (action->isOn()) action->setOn(false);
   } else {
      gStyle->SetOptTitle(1);
      if (!action->isOn()) action->setOn(true);
   }
   ModifiedUpdate();
}
//______________________________________________________________________________
void TQtCanvasImp::OptFitCB()
{
   TQtRootAction *action = (TQtRootAction *)sender();
   if (gStyle->GetOptFit()) {
      gStyle->SetOptFit(0);
      if (action->isOn()) action->setOn(false);
   } else {
      gStyle->SetOptFit(1);
      if (!action->isOn()) action->setOn(true);
   }
   ModifiedUpdate();
}
//______________________________________________________________________________
void TQtCanvasImp::CanEditHistogramsCB()
{
   TQtRootAction *action = (TQtRootAction *)sender();
   if (gROOT->GetEditHistograms()) {
      gROOT->SetEditHistograms(kFALSE);
      if (action->isOn()) action->setOn(false);
   } else {
      gROOT->SetEditHistograms(kTRUE);
      if (!action->isOn()) action->setOn(true);
   }
}
  //*-*   Items for the Inspect Menu
//______________________________________________________________________________
void TQtCanvasImp::ROOTInspectCB()
{
   Canvas()->cd();
   gROOT->Inspect();
}
   
   //*-*   Items for the Class Menu
//______________________________________________________________________________
void TQtCanvasImp::FullTreeCB()
{}

//______________________________________________________________________________
void TQtCanvasImp::AboutCB()
{ 
  QMessageBox::aboutQt(0);
  QMessageBox::about(0,"ROOT Canvas with Qt interface"
    ,"ROOT Qt interface Copyright (C) 2001-2002, Valeri Fine. Brookhaven National Laboratory. All right reserved.");
#ifdef R__UNIX
                        TString rootx;
# ifdef ROOTBINDIR
                        rootx = ROOTBINDIR;
# else
                        rootx = gSystem->Getenv("ROOTSYS");
                        if (!rootx.IsNull()) rootx += "/bin";
# endif
                        rootx += "/root -a &";
                        gSystem->Exec(rootx);
#else                        
                        QString str = QString("ROOT ") + QString(gROOT->GetVersion());
                        QString helpAbout = gHelpAbout;
                        helpAbout.replace("\n"," ");
                        HelpOn(str,helpAbout);
#endif
}
//______________________________________________________________________________
void TQtCanvasImp::HelpCB()
{
#ifdef R__WIN32
  gSystem->Exec("explorer http://root.cern.ch/root/html/ClassIndex.html");
#else
  gSystem->Exec("netscape http://root.cern.ch/root/html/ClassIndex.html");
#endif
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOn(const char *title, const char *text) {
    QString body = "<tt><center><b>";
    body += title; body += "</b></center><br>";
    body += text;
    body.replace("\n","<br>");
    QMessageBox::about(0,title,body);
 }
//______________________________________________________________________________
void TQtCanvasImp::HelpOnCanvasCB(){  
   HelpOn("Help On Canvas...",gHelpAbout ); 
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOnMenusCB() { 
   HelpOn("Help On Menus...", gHelpPullDownMenus);
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOnGraphicsEdCB() {
   HelpOn("Help On Graphics Editor...", gHelpGraphicsEditor); 
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOnBrowserCB() {
   HelpOn("Help On Browser...", gHelpBrowser ); 
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOnObjectsCB() { 
   HelpOn("Help On Objects...", gHelpObjects); 
}
//______________________________________________________________________________
void TQtCanvasImp::HelpOnPSCB()      { 
   HelpOn("Help On PostScript...",gHelpPostscript ); 
}
