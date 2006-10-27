// @(#)root/g3d:$Name:  $:$Id: TQtCoinViewerImp.h,v 1.3 2006/10/27 00:26:47 fine Exp $
// Author: Valery Fine      23/05/97

/****************************************************************************
** $Id: TQtCoinViewerImp.h,v 1.3 2006/10/27 00:26:47 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#ifndef ROOT_TQtCoinViewerImp
#define ROOT_TQtCoinViewerImp

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtCoinViewerImp                                                       //
//                                                                      //
// Second ABC TQtCoinViewerImp specifies Window system independent openGL //
// interface. This class uses the GL includes and isn't passed to CINT  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "RVersion.h"
#if ROOT_VERSION_CODE >= 262400
// ROOT_VERSION(4,01,00)
#  include "TQGLViewerImp.h"
#else
#  include "TGLViewerImp.h"
#endif

#include "TString.h"

#ifndef __CINT__
#  include <qglobal.h>
#  if QT_VERSION < 0x40000
#    include <qmainwindow.h>
#    include <qptrvector.h>
#  else /* QT_VERSION */
#    include <q3mainwindow.h>
#    include <q3ptrvector.h>
#  endif /* QT_VERSION */
#  include <qlabel.h>
#else
#  if QT_VERSION < 0x40000
     class QMainWindow;
#  else /* QT_VERSION */
     class Q3MainWindow;
#  endif /* QT_VERSION */
   class QString;
#endif

//====================
class SoSeparator;
class SoNode;
class SoMaterial;
class SoCallback;
class SoQtViewer;
class SoPerspectiveCamera;
class SoCamera;
class SoSelection;
class SmAxisDisplayKit;

//#include <qintdict.h>
//class TQtRootAction;
//====================   
   
#include <vector>

class QAction;
class TVirtualPad;
class SoQtExaminerViewer;
class TObject3DView;
class TContextMenu;

#if QT_VERSION < 0x40000
  class TQtCoinViewerImp :public QMainWindow, public TGLViewerImp {
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  class TQtCoinViewerImp :public Q3MainWindow, public TGLViewerImp {
//MOC_SKIP_END
#endif /* QT_VERSION */
Q_OBJECT	  
private:
	
   SoQtViewer             *fInventorViewer;
   SoQtExaminerViewer     *qt_viewer;
   SoSeparator            *fRootNode;
   SoSeparator            *fShapeNode;
   SoSelection            *fSelNode;
   SoPerspectiveCamera    *myCamera;
   SoCamera               *fCamera;
   SmAxisDisplayKit       *fAxis;
   std::vector<int>        flist[3];

   TQtCoinViewerImp(const TQtCoinViewerImp&);
   void operator=(const TQtCoinViewerImp&)  {}
protected:

   TString         fSaveFile;           // the file name to save the pixmap to
   TString         fSaveType;           // the image format type name
   Int_t           fMaxSnapFileCounter; // The max number of the difffrent "snapshot files" (The length of the cyclic buffer)
   //static Int_t    gfDefaultMaxSnapFileCounter; // the default max number of the different "snapshot files" (The length of the cyclic bugger)
   //QGLWidget      *fGLWidget;           // QT GL widget to render the view
   TVirtualPad    *fPad;                // For forward compatibility with the new viewer
   TContextMenu   *fContextMenu;        // ROOT Context menu for the 3D widget
   static Bool_t   fgCoinInitialized;
   TObject        *fSelectedObject;     // The last selected TObject


#ifndef __CINT__
#if QT_VERSION < 0x40000
   QPtrVector<QLabel> fStatusBar;
#else
//MOC_SKIP_BEGIN
   Q3PtrVector<QLabel> fStatusBar;
//MOC_SKIP_END
#endif
#endif

   //TQtCoinViewerImp *fSelectedView;        // extra viewer to show the selected object only
   //Bool_t          fSelectedViewActive;  // the flag to activate the "Selected view"
   //Bool_t          fSelectionViewer;     // Flag to create the slave viewer with no own layout
   //Bool_t          fSelectionHighlight;  // Flag to highlight the selection object in place
   //Bool_t          fShowSelectionGlobal; // Show the selected object in the global coordinate
   Bool_t          fWantRootContextMenu; // Create "ROOT Context menu" for the seelcted ROOT objects
   QAction        *fSnapShotAction;      // QAction to toglle the snap shot file saving
   
   
   
   
protected:
   void CopyFile(const QString &fileName2Copy,Int_t counter);
   void CreateViewer(const char *name="qcoinviewer");
   //void CreateViewer(QGLWidget *share, const char *name="qglviewershared");
   void MakeMenu();
   //void SaveHtml(Int_t counter);
   //void SaveHtml(QString &fileName, Int_t counter);
   //void CreateSelectionViewer();
   //static int CreateSnapShotCounter();

   //TQtCoinViewerImp(TQtCoinViewerImp &);

public:
   enum {kStatusPopIn, kStatusNoBorders, kStatusOwn, kStatusPopOut};
   //TQtCoinViewerImp();
   //TQtCoinViewerImp(TPadOpenGLView *padview, const char *title="OpenGL Viewer", UInt_t width=400, UInt_t height=300);

   //TQtCoinViewerImp(TPadOpenGLView *padview, const char *title, Int_t x, Int_t y,UInt_t width, UInt_t height);
   TQtCoinViewerImp(TVirtualPad *pad, const char *title="Coin Viewer", UInt_t width=400, UInt_t height=300);
   //TQtCoinViewerImp(TVirtualPad *pad, const char *title, Int_t x, Int_t y,UInt_t width, UInt_t height);

   virtual ~TQtCoinViewerImp();
   void AddRootChild(ULong_t id);
   virtual void   Clear();
   //virtual void   CreateStatusBar(Int_t nparts=1);
   virtual void   CreateStatusBar(Int_t *parts, Int_t nparts=1);
   virtual TContextMenu &ContextMenu(); 
   //virtual void   DeleteContext() { }
   //virtual void   MakeCurrent();
   //virtual void   Paint(Option_t *opt="");

   //virtual void   SetStatusText(const char *text, Int_t partidx=0,Int_t stype=-1);
   //virtual void   ShowStatusBar(Bool_t show = kTRUE);

   //virtual void   SwapBuffers() { };
   SoCamera *GetCamera() const { return fCamera;} 
   SmAxisDisplayKit *GetAxis() const { return fAxis;}
   std::vector<int> GetMyGLList1() { return flist[0]; }
   std::vector<int> GetMyGLList2() { return flist[1]; }
   std::vector<int> GetMyGLList3() { return flist[2]; }
   //virtual void   SetDrawList(UInt_t list) { fDrawList = list; }

   //virtual void   Iconify() { hide(); };
   //virtual void   Show() { show(); };
   virtual void   Update();
   
   virtual ULong_t GetViewerID() const;   
   //virtual void    SetPadSynchronize(Bool_t on=kTRUE);
   // static void     SetDefaultFileCounter(int counter);
   virtual void SetUpdatesEnabled(const bool&);
   virtual void    DisconnectPad();
   //QGLWidget *GLWidget() const { return fGLWidget;}
   virtual TVirtualPad *GetPad();
   void CreateViewer(const int id);
   void EmitSelectSignal(TObject3DView * view);
   void SetBoxSelection();
   void SetLineSelection();
   TObject     *GetSelected()         const { return fSelectedObject;     }
   SoQtViewer  *GetCoinViewer()       const { return fInventorViewer;     }
   Bool_t       WantRootContextMenu() const { return fWantRootContextMenu;}

#ifndef __CINT__
  public slots:
     //virtual void ActivateSelectorWidgetCB(bool);
     //virtual void ActivateSelectionHighlighCB(bool);
     //virtual void ActivateSelectionGlobalCB(bool);
     //virtual void DisconnectSelectorWidgetCB();
     virtual void AddGLList(unsigned int list, int type=1);
     virtual void RemoveGLList(unsigned int list);
     //virtual void NewViewer();
     virtual void PrintCB();
     virtual void CopyCB();
     virtual void CopyFrameCB();
     virtual void SaveCB();
     virtual void OpenCB();
     virtual void ClearCB();
     virtual void SaveAsCB();
     //virtual void SelectEventCB(bool on);
     //virtual void SelectDetectorCB(bool on);
     virtual void SetBackgroundColor(Color_t color);
     //virtual void SetBackgroundColor(const TColor *color);
     virtual void ShowObjectInfo(TObject *, const QPoint&);
     virtual void SnapShotSaveCB(bool);
     virtual void SaveSnapShot(bool);
     virtual void ShowFrameAxisCB(bool);
     virtual void ShowLightsCB(bool);
     virtual void SynchTPadCB(bool);
     virtual void SetRotationAxisAngle(const float  x, const float  y, const float  z, const float a);
     virtual void SetSnapFileCounter(int counter);
     //virtual void SetFooter(QString &text);
     virtual void WantRootContextMenuCB(bool on);
     virtual void AboutCB();
     virtual void HelpCB();
  signals:
       void ObjectSelected(TObject *, const QPoint&);
#endif

//   ClassDef(TQtCoinViewerImp,0)  //ROOT OpenGL viewer implementation
};

// $log$
#endif
