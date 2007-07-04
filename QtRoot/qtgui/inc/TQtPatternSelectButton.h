// @(#)root/gui:$Name:  $:$Id: TQtPatternSelectButton.h,v 1.3 2007/07/04 20:45:43 fine Exp $
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
// #include <qpushbutton.h> 
#if QT_VERSION < 0x40000
#  include <qbuttongroup.h> 
#  include <qvbox.h> 
#  include <qframe.h>
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
#  include <QFrame>
//MOC_SKIP_END
#endif /* QT_VERSION */
#include <qdialog.h> 

#include <qcolor.h>
#include <qbrush.h>


class QToolButton;
class QMouseEvent;

class TEmitRootSignal;
//----------------------------------------------------------------------
//                TQtPatternFrame
//----------------------------------------------------------------------

//class TQtPatternFrame : public QPushButton {
//class TQtPatternFrame : public QToolButton {
class TQtPatternFrame : public QFrame {
Q_OBJECT

protected:
   QColor          fPixel;
   Bool_t          fActive;
   TQtBrush        fBrush;
   QString         fBrushTipLabel;
   QWidget        *fPanel;
   
protected:
   virtual void SetIcon();
   virtual void mouseReleaseEvent(QMouseEvent *event);

public:
   TQtPatternFrame(QWidget *p, TQtBrush &c, Int_t n=-1);
   TQtPatternFrame(QWidget *p, Style_t pattern, Int_t n);
   virtual ~TQtPatternFrame() { }
   QSize   sizeHint () const ;
   void    SetActive(Bool_t in)         { fActive = in;       }
   const TQtBrush &GetBrush() const { return fBrush; }

public slots:
   void    SetBrush(TQtBrush &newBrush);
protected slots:
   virtual void languageChange();
signals:
   void clicked();

   // ClassDef(TQtPatternFrame,0)  // Frame for color cell
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
   TQtPatternPopup( QWidget *p, TQtBrush &color,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);

public:
   static TQtPatternPopup *Create(QWidget *p, TQtBrush &pattern,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);            
   virtual ~TQtPatternPopup();

   const TQtBrush &Brush() const { return fCurrentBrush;}
   
protected slots:
    void SetActiveSlot();

public slots:
      virtual void BrushSelected(const TQtBrush &pattern);
      
protected slots:
   virtual void languageChange();
  //  ClassDef(TQtPatternPopup,0)  // Brush selector popup
};

//----------------------------------------------------------------------
//                 TQtPatternSelectButton
//----------------------------------------------------------------------


  class TQtPatternSelectButton : public QFrame {
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
