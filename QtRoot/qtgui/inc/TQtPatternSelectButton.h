// @(#)root/gui:$Name:  $:$Id: TQtPatternSelectButton.h,v 1.2 2006/09/22 17:27:10 fine Exp $
// Author: Bertrand Bellenot + Fons Rademakers   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TQtPatternSelectButton
#define ROOT_TQtPatternSelectButton

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtPatternFrame, TQt16BrushSelector, TQtPatternPopup and TQtPatternSelect.     //
//                                                                      //
// The TQtPatternFrame is a small framw with border showing a specific  //
// color.                                                               //
//                                                                      //
// The TQt16BrushSelector is a composite frame with 16 TQtPatternFrames.//
//                                                                      //
// The TQtPatternPopup is a popup containing a TQt16BrushSelector and a //
// "More..." button which popups up a QBrushDialog allowing custom      //
// color selection.                                                     //
//                                                                      //
// The TQtPatternSelect widget is like a checkbutton but instead of the //
// check mark there is color area with a little down arrow. When        //
// clicked on the arrow the TQtPatternPopup pops up.                    //
//                                                                      //
// Selecting a color in this widget will generate the event:            //
// kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      //
// and the signal:                                                      //
// BrushSelected(Pixel_t pixel)                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "GuiTypes.h"
#include "Riostream.h"
#include "TQtBrush.h"
#include "Gtypes.h"

#include <qtoolbutton.h> 
#if QT_VERSION < 0x40000
#  include <qbuttongroup.h> 
#  include <qvbox.h> 
#  include <qframe.h>
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
#  include <q3buttongroup.h> 
#  include <q3vbox.h> 
#  include <q3frame.h>
//MOC_SKIP_END
#endif /* QT_VERSION */
#include <qdialog.h> 

#include <qcolor.h>
#include <qbrush.h>
#include <qpushbutton.h> 




class TEmitRootSignal;
//----------------------------------------------------------------------
//                TQtPatternFrame
//----------------------------------------------------------------------

class TQtPatternFrame : public QToolButton {
Q_OBJECT

protected:
   QColor          fPixel;
   Bool_t          fActive;
   TQtBrush        fBrush;
   QString         fBrushTipLabel;
   
protected:
   virtual void drawButtonLabel(QPainter *);

public:
   TQtPatternFrame(QWidget *p, TQtBrush &c, Int_t n=-1);
   TQtPatternFrame(QWidget *p, Style_t pattern, Int_t n);
   virtual ~TQtPatternFrame() { }
   QSize   sizeHint () const ;
   void    SetActive(Bool_t in)         { fActive = in;       }
   void    SetBrush(TQtBrush &newBrush) { fBrush = newBrush ; }
   const TQtBrush &GetBrush() const { return fBrush; }

protected slots:
   virtual void languageChange();

   // ClassDef(TQtPatternFrame,0)  // Frame for color cell
};

//----------------------------------------------------------------------
//                 TQt16BrushSelector
//----------------------------------------------------------------------

#if QT_VERSION < 0x40000
class TQt16BrushSelector : public  QFrame {
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  class TQt16BrushSelector : public  Q3Frame {
//MOC_SKIP_END
#endif /* QT_VERSION */
Q_OBJECT
protected:
   Int_t            fActive;
   TQtPatternFrame    *fCe[28];

public:
   TQt16BrushSelector(QWidget *p, const char *name=0);
   virtual ~TQt16BrushSelector();

   void    SetActive(Int_t newat);
   Int_t   GetActive() const { return fActive; }
   const TQtBrush  &GetActiveBrush() const;

public slots:
   void SetActiveSlot(int id);
   void SetActiveSlot();

protected slots:
   virtual void languageChange();

signals:
   void BrushChanged(const TQtBrush &pattern);
   // ClassDef(TQt16BrushSelector,0)  // 16 color cells
};

//----------------------------------------------------------------------
//                 TQtPatternPopup
//----------------------------------------------------------------------
class TQtPatternPopup : public QDialog  {
Q_OBJECT
protected:
   Int_t            fActive;
   Int_t            fLaunchDialog;
   TQtBrush           fCurrentBrush;
   static TQtPatternPopup *fgBrushPopup;//  Pointer to the singletons

protected:
#if QT_VERSION < 0x40000
   TQtPatternPopup( QWidget *p, TQtBrush &color,const char *name=0, bool modal=FALSE, WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
   TQtPatternPopup( QWidget *p, TQtBrush &color,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);
//MOC_SKIP_END
#endif /* QT_VERSION */

public:
#if QT_VERSION < 0x40000
   static TQtPatternPopup *Create(QWidget *p, TQtBrush &pattern,const char *name=0, bool modal=FALSE, WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);            
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
   static TQtPatternPopup *Create(QWidget *p, TQtBrush &pattern,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);            
//MOC_SKIP_END
#endif /* QT_VERSION */
   virtual ~TQtPatternPopup();

   const TQtBrush &Brush() const { return fCurrentBrush;}
   
public slots:
      virtual void BrushSelected(const TQtBrush &pattern);
      
protected slots:
   virtual void languageChange();
  //  ClassDef(TQtPatternPopup,0)  // Brush selector popup
};

//----------------------------------------------------------------------
//                 TQtPatternSelectButton
//----------------------------------------------------------------------


#if QT_VERSION < 0x40000
  class TQtPatternSelectButton : public QFrame {
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  class TQtPatternSelectButton : public Q3Frame {
//MOC_SKIP_END
#endif /* QT_VERSION */
Q_OBJECT
protected:
   TQtBrush         fBrush;
   TQtPatternPopup *fBrushPopup;
   TEmitRootSignal *fBrushEmitter;
   TQtPatternFrame *fPushButton;
   QToolButton     *fArrowButton;
 
   void CreateWidget();
public:
   TQtPatternSelectButton(QWidget *p, UInt_t style, Int_t id=-1,TEmitRootSignal *emitter=0);
   TQtPatternSelectButton(QWidget *p, TQtBrush &pattern, Int_t id=-1,TEmitRootSignal *emitter=0);
   TQtPatternSelectButton(QWidget *p, const char *name, Qt::WFlags f = Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);
         
   virtual ~TQtPatternSelectButton();

   const   TQtBrush &GetBrush() const { return fBrush; }
   Style_t GetStyle() const { return fBrush.GetStyle(); }
   void    Enable();
   void    Disable();

public slots:
   virtual void PopupDialog();
   virtual void SetBrush(UInt_t style);
   virtual void SetBrush(const TQtBrush &pattern);
   void    SetStyle(Style_t pattern){SetBrush(UInt_t(pattern ));}
protected slots:
   virtual void languageChange();
signals:
   void brushSelected(const TQtBrush&);
   // ClassDef(TQtPatternSelect,0)  // Brush selection checkbutton
};

#endif
