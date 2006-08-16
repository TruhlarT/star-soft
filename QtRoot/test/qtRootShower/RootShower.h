// Author: Bertrand Bellenot   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Bertrand Bellenot.                           *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see the LICENSE file.                         *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// This File contains the declaration of the RootShower-class           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOTSHOWER_H
#define ROOTSHOWER_H

#include <qobject.h>
#include <qaction.h>
#include <qlabel.h>
#include <qmainwindow.h> 
#include <qintdict.h>
#include <qptrvector.h>
#include <qstring.h>

#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TDatime
#include "TDatime.h"
#endif

class QMenuBar;
class QPopupMenu;
class GTitleFrame;
class GButtonFrame;
class QButton;
class QListTree;
class QListViewItem;
class TRootEmbeddedCanvas;
class TGCanvas;
class QStatusBar;
class QTextEdit;
class QTabWidget;
class TCanvas;
class TPad;
class MyEvent;
class TEnv;
class QTimer;
class TGeometry;
class TBRIK;
class TNode;
class TH1F;
class QToolBar;
class TGButton;
class QVBox;
class QListView;
class QTabWidget;

class TQtWidget;

extern QListViewItem   *gEventListTree; // event selection QListTree
extern QListViewItem   *gBaseLTI;
extern QListViewItem   *gTmpLTI;
extern QListViewItem   *gLTI[];

extern Int_t            gColIndex;

struct ToolBarData_t {
   const char *fPixmap;
   const char *fTipText;
   Bool_t      fStayDown;
   Int_t       fId;
   TGButton   *fButton;
};

//___________________________________________________________
class ShowerAction : public QAction {
public:
   ShowerAction(QObject * parent, ToolBarData_t &data, const char * name = 0, bool toggle = FALSE)
      : QAction(parent,name,toggle),fBarData(data) 
   {
       setMenuText(fBarData.fPixmap);
       setToolTip(fBarData.fTipText);       
   }
   int Id(){ return fBarData.fId; }
private:
   ToolBarData_t fBarData;
};

//___________________________________________________________
class RootShower: public QMainWindow {
Q_OBJECT
    friend class SettingsDialog;

private:

    // Statics
    static Int_t        fgDefaultXPosition; // default X position of top left corner
    static Int_t        fgDefaultYPosition; // default Y position of top left corner

    Bool_t              fOk;
    Bool_t              fModified;
    Bool_t              fSettingsModified;
    Bool_t              fIsRunning;
    Bool_t              fInterrupted;

    ULong_t             fEventNr;   // Event number
    UInt_t              fNRun;      // Run number
    TDatime             fEventTime; // Event generation date

    Int_t               fPicIndex;
    Int_t               fPicNumber;
    Int_t               fPicDelay;
    Int_t               fPicReset;

    TEnv               *fRootShowerEnv;
    // MenuBar Frame
    QMenuBar          *fMenuBar;
    QPopupMenu        *fMenuFile;
    QPopupMenu        *fMenuTest;
    QPopupMenu        *fMenuInspect;
    QPopupMenu        *fMenuView;
    QPopupMenu        *fMenuHelp;
    void                MakeMenuBarFrame();

    // ToolBar Frame
    QToolBar           *fToolBar;

    // Title Frame
    GTitleFrame        *fTitleFrame;

    // Selection frame
    QVBox             *fSelectionFrame;
    GButtonFrame      *fButtonFrame; // button frame
    QListView         *fEventListTree; // event selection QListTree

    // Display frame
    QTabWidget        *fDisplayFrame;    // QTab for graphical and text display
    TQtWidget         *fEmbeddedCanvas3; // the actual frame which displays histo
    QTextEdit         *fTextView;

    QTimer             *fTimer;
    TCanvas            *cA;
    TCanvas            *cB;
    TCanvas            *cC;
    TGeometry          *fSelection;
    TBRIK              *sel_detect;
    TNode              *sel_node;
    MyEvent            *fEvent;
    TPad               *padA,*padB,*padC;
    
    TH1F               *fHisto_dEdX;       // histogram of particle's energy loss
    QIntDict<ShowerAction> fActions;
     // Statusbar
    QPtrVector<QLabel>  fStatusBar;
    QPixmap            *fLeafPic;
    QPixmap            *fBranchPic;
    QString             fSaveFileName;


protected:

    Int_t               fMaterial;
    Int_t               fFirstParticle;
    Double_t            fDimX,fDimY,fDimZ;
    Double_t            fE0;
    Double_t            fB;

public:
    // statics
    static void        setDefaultPosition(Int_t x, Int_t y);

    // Constructors & destructor
    RootShower(QWidget *p, UInt_t w, UInt_t h);
    virtual ~RootShower();

    void               SetOk(Bool_t ok=true) { fOk = ok; }
    void               Modified(Bool_t modified=true) { fModified = modified; }
    void               SettingsModified(Bool_t modified=true) { fSettingsModified = modified; }
    Bool_t             IsInterrupted() { return fInterrupted; }
    virtual void       Initialize(Int_t first);
    virtual void       OnOpenFile(const Char_t *filename);
    virtual void       OnSaveFile(const Char_t *filename);
    virtual void       OnShowerProduce();
    virtual void       produce();
    virtual void       ShowInfos();
    virtual void       HighLight(QListViewItem *item);
    virtual void       CloseWindow();
    virtual Int_t      DistancetoPrimitive(Int_t px, Int_t py);
    void               SetStatusText(const char *text, Int_t partidx);
    void               CreateStatusBar(Int_t *parts, Int_t nparts);

public slots:
    virtual void       ProcessMessage();
    virtual void       ShowToolBar(bool);
    virtual void       OnShowSelected(QListViewItem *item);
    virtual void       NextEvent();
    virtual void       SelectEvent();
            void       Interrupt(Bool_t inter=true) { fInterrupted = inter; }
            void       HandleTimer();
    
};

extern RootShower   *gRootShower;

#endif // EMSHOWER_H
