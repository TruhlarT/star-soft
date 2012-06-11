// @(#)root/gui:$Name:  $:$Id: TQtColorSelectButton.h,v 1.8 2012/06/11 14:20:56 fisyak Exp $
// Author: Bertrand Bellenot + Fons Rademakers   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TQtColorSelectButton
#define ROOT_TQtColorSelectButton

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtColorFrame, TQt16ColorSelector, TQtColorPopup and TQtColorSelect. //
//                                                                      //
// The TQtColorFrame is a small framw with border showing a specific    //
// color.                                                               //
//                                                                      //
// The TQt16ColorSelector is a composite frame with 16 TQtColorFrames.  //
//                                                                      //
// The TQtColorPopup is a popup containing a TQt16ColorSelector and a   //
// "More..." button which popups up a QColorDialog allowing custom      //
// color selection.                                                     //
//                                                                      //
// The TQtColorSelect widget is like a checkbutton but instead of the   //
// check mark there is color area with a little down arrow. When        //
// clicked on the arrow the TQtColorPopup pops up.                      //
//                                                                      //
// Selecting a color in this widget will generate the event:            //
// kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      //
// and the signal:                                                      //
// ColorSelected(Pixel_t pixel)                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "GuiTypes.h"

#include <qtoolbutton.h> 
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
#include <qpushbutton.h> 



class QMenu;
class TColorEmit;
//----------------------------------------------------------------------
//                TQtColorFrame
//----------------------------------------------------------------------

class TQtColorFrame : public QToolButton {
Q_OBJECT

protected:
   QColor          fPixel;
   Int_t           fActive;
   QColor          fColor;
   QString         fColorTipLabel;
   
protected:
   virtual void drawButtonLabel(QPainter *);

public:
   TQtColorFrame(QWidget *p, const QColor &c, Int_t n=-1);
   virtual ~TQtColorFrame() { }
         QSize   sizeHint () const ;
         void    SetActive(Bool_t in) { fActive = in;  }
   const QColor &GetColor() const { return fColor; }
         void SetColor(const QColor &color);

protected slots:
   virtual void languageChange();

   // ClassDef(TQtColorFrame,0)  // Frame for color cell
};

//----------------------------------------------------------------------
//                 TQt16ColorSelector
//----------------------------------------------------------------------

class TQt16ColorSelector : public  QFrame {
Q_OBJECT
protected:
   Int_t            fActive;
   TQtColorFrame    *fCe[16];

public:
   TQt16ColorSelector(QWidget *p, const char *name=0);
   virtual ~TQt16ColorSelector();

   void    SetActive(Int_t newat);
   Int_t   GetActive() const { return fActive; }
   const QColor  &GetActiveColor() const;

public slots:
   void SetActiveSlot();
   void SetActiveSlot(int id);

protected slots:
   virtual void languageChange();

signals:
   void ColorChanged(const QColor &color);
   // ClassDef(TQt16ColorSelector,0)  // 16 color cells
};

//----------------------------------------------------------------------
//                 TQtColorPopup
//----------------------------------------------------------------------
class TQtColorPopup : public QDialog  {
Q_OBJECT
protected:
   Int_t            fActive;
   Int_t            fLaunchDialog;
   QColor           fCurrentColor;
   static TQtColorPopup *fgColorPopup;//  Pointer to the singletons

protected:
   TQtColorPopup( QWidget *p, QColor &color,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);

public:
   static TQtColorPopup *Create(QWidget *p, QColor &color,const char *name=0, bool modal=FALSE, Qt::WFlags f=Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);            
   virtual ~TQtColorPopup();

   const QColor &Color() const { return fCurrentColor;}
   
public slots:
      virtual void ColorSelectDialog();
      virtual void ColorSelected(const QColor &color);
      
protected slots:
   virtual void languageChange();
  //  ClassDef(TQtColorPopup,0)  // Color selector popup
};

//----------------------------------------------------------------------
//                 TQtColorSelectButton
//----------------------------------------------------------------------


class TQtColorSelectButton : public QFrame {
Q_OBJECT
Q_PROPERTY( QColor  fColor  READ GetColor  WRITE SetColor)
protected:
   QColor         fColor;
   TQtColorPopup *fColorPopup;
   TColorEmit    *fColorEmitter;
#if QT_VERSION < 0x40000
   QButton       *fPushButton;
   QToolButton   *fArrowButton;
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
   QAbstractButton       *fPushButton;
//MOC_SKIP_END
#endif /* QT_VERSION */
   QMenu         *fFakeMenu;
   //     QToolButton   *fPushButton;
//   QToolButtonQPushButton   *fPushButton;

   void CreateWidget();
public:
   TQtColorSelectButton(QWidget *p, UInt_t pixel, Int_t id=-1,TColorEmit *emitter=0);
   TQtColorSelectButton(QWidget *p, QColor &color, Int_t id=-1,TColorEmit *emitter=0);
   TQtColorSelectButton(QWidget *p, const char *name, Qt::WFlags f = Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop);
   TQtColorSelectButton(QWidget *p);
   virtual ~TQtColorSelectButton();


   const   QColor &GetColor() const { return fColor; }
   void    Enable();
   void    Disable();

   virtual void ColorSelected() { /* Emit("ColorSelected(Pixel_t)", GetColor());*/  }  //*SIGNAL*
public slots:
   virtual void PopupDialog();
   virtual void SetColor(const QColor &color);
protected slots:
   virtual void languageChange();
signals:
   void colorSelected(const QColor&);
   // ClassDef(TQtColorSelect,0)  // Color selection checkbutton
};

#endif
