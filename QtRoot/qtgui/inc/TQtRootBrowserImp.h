// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtRootBrowserImp.h,v 1.1 2006/08/16 19:33:21 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtRootBrowserImp
#define ROOT_TQtRootBrowserImp

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtRootBrowserImp                                                        //
//                                                                      //
// ABC describing GUI independent browser implementation protocol.      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TBrowserImp.h"
#include "TQtGui.h"

#include <qglobal.h>
#if QT_VERSION < 0x40000
#include <qptrvector.h>
#else /* QT_VERSION */
#include <q3ptrvector.h>
#endif /* QT_VERSION */
#include <qstring.h>
#include <qobject.h>
#if QT_VERSION < 0x40000
#include <qintdict.h>
#else /* QT_VERSION */
#include <q3intdict.h>
//Added by qt3to4:
#include <Q3ActionGroup>
#endif /* QT_VERSION */

// class TQtBrowserWidget;
class TQtBrowserImp;
class TQtIconBrowserImp;
class TQtRootAction;

#if QT_VERSION < 0x40000
class QMainWindow;
#else /* QT_VERSION */
class Q3MainWindow;
#endif /* QT_VERSION */
class QMenuBar;
#if QT_VERSION < 0x40000
class QToolBar;
class QActionGroup;
#else /* QT_VERSION */
class Q3ToolBar;
class Q3ActionGroup;
#endif /* QT_VERSION */

class TQtRootBrowserImp :  public QObject, public TBrowserImp {
  Q_OBJECT
    friend class ev;
protected:

#if QT_VERSION < 0x40000
  QMainWindow       *fBrowserImpID;
#else /* QT_VERSION */
  Q3MainWindow       *fBrowserImpID;
#endif /* QT_VERSION */
  QMenuBar          *fMenuBar;
  TQtBrowserImp     *fTreeView;
  TQtIconBrowserImp *fIconView;

  Int_t   fX,fY;
  UInt_t  fWidth,fHeight;
  QString fTitle;  

#if QT_VERSION < 0x40000
  QIntDict<TQtRootAction> fActions;
  QActionGroup      *fViewActions;
  QToolBar          *fToolBar;
#else /* QT_VERSION */
  Q3IntDict<TQtRootAction> fActions;
  Q3ActionGroup      *fViewActions;
  Q3ToolBar          *fToolBar;
#endif /* QT_VERSION */
  QString           fSaveType;
  QString           fSaveFileName;

public:

   TQtRootBrowserImp(TBrowser *b=0,bool initFlag=true);
   TQtRootBrowserImp(TBrowser *b, const char *title, UInt_t width, UInt_t height,bool initFlag=true);
   TQtRootBrowserImp(TBrowser *b, const char *title, Int_t x, Int_t y, UInt_t width, UInt_t height,bool initFlag=true);
   virtual ~TQtRootBrowserImp();

  // The base class overloaded methods:

   virtual void  Add(TObject *, const char *caption, Int_t);
   virtual void  Add(TObject *, const char *caption);
   virtual void  AddCheckBox(TObject *, Bool_t = kFALSE);
   virtual void  CheckObjectItem(TObject *, Bool_t = kFALSE);
   virtual void  RemoveCheckBox(TObject *);
   virtual void  BrowseObj(TObject *);
   virtual void  ExecuteDefaultAction(TObject *);
   virtual void  Iconify();
   virtual void  RecursiveRemove(TObject *);
   virtual void  Refresh(Bool_t = kFALSE);
   virtual void  SetDrawOption(Option_t *option="");
   virtual Option_t *GetDrawOption() const;
   virtual void  Show();

   // TObject overloaded methods:
   const char* GetTitle() const;
   QWidget *GetBrowserID();
   // This class own data-members:
protected:
   // This class own methods:
   void Add(TObject *obj, const char *caption, Bool_t firstFlag);
   void MakeActions();
   void MakeMenu();
   void MakeToolBar() ;
   void MakeStatBar() ;
   void SetViewMode(int mode) ;

public:
   virtual Int_t InitWindow();
protected slots:
  virtual void Disconnect();
  virtual void DisplayTotal(Int_t total, Int_t selected);

  void ProcessMessage();
  void NewBrowserCB();
  void NewCanvasCB();
  void OpenCB();
  void SaveCB();
  void SaveAsCB();
  void CopyCB();
  void PrintCB();
  void CloseCB();
  void QuitCB();
 
//*-*   Items for the View

  void ToolbarCB(bool show);
  void StatusBarCB(bool show);
  void LargeCB()  {SetViewMode(TQtGui::kViewLargeIcons);}
  void SmallCB()  {SetViewMode(TQtGui::kViewSmallIcons);}
  void ListCB()   {SetViewMode(TQtGui::kViewList);}
  void DetailsCB(){SetViewMode(TQtGui::kViewDetails);}
  void ArrangeCB(){;}
  void LineupCB(){;}
  void RefreshCB();
  void HelpCB();
  void AboutCB();
  void ResetAction(int mode) ;

};
inline  const char* TQtRootBrowserImp::GetTitle() const {return fTitle;}

#endif
