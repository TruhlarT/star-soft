// @(#)root/gui:$Name:  $:$Id: TQtPatternSelectButton.cxx,v 1.3 2007/07/04 20:45:43 fine Exp $
// Author: Bertrand Bellenot + Fons Rademakers   22/08/02

/*************************************************************************
 * Copyright (C) 1995-2002, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
/**************************************************************************

    This file is part of xclass.
    Copyright (C) 2000, 2001, Hector Peraza.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

**************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtPatternFrame, TQt16ColorSelector, TQtPatternPopup and TQtPatternSelectButton.     //
//                                                                      //
// The TQtPatternFrame is a small frame with border showing a specific  //
// color.                                                               //
//                                                                      //
// The TQt16BrushSelector is a composite frame with 16 TQtPatternFrames.//
//                                                                      //
// The TQtPatternPopup is a popup containing a TQt16BrushSelector and a //
// "More..." button which popups up a TQtBrushDialog allowing custom    //
// color selection.                                                     //
//                                                                      //
// The TQtPatternSelectButton widget is like a checkbutton but instead of the //
// check mark there is color area with a little down arrow. When        //
// clicked on the arrow the TQtPatternPopup pops up.                    //
//                                                                      //
// Selecting a color in this widget will generate the event:            //
// kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      //
// and the signal:                                                      //
// BrushSelected(ULong_t pixel)                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// #include "TGClient.h"
#include "TGQt.h"
#include "TQtPatternSelectButton.h"
#include "TQtPatternSelect.h"
#include "TEmbeddedPad.h"
#include "TColor.h"

#include <qcolordialog.h> 
#include <qtooltip.h> 
#include <qcolor.h> 
#if QT_VERSION < 0x40000
#  include <qhgroupbox.h> 
#  include <qwhatsthis.h>
#  include <qtoolbutton.h> 
#  include <qevent.h>
#else
#  include <QStyleOptionButton>
#  include <QPixmap>
#  include <QBitmap>
#  include <QHBoxLayout>
#  include <QToolButton>
#  include <QDebug>
#  include <QMouseEvent>
#endif /* QT_VERSION */
#include <qapplication.h> 

#include <qstyle.h>
#include <qvariant.h>
#include <qlayout.h>

//ClassImp(TQtPatternFrame)
//ClassImp(TQt16ColorSelector)
//ClassImp(TQtPatternPopup)
//ClassImp(TQtPatternSelectButton)

static int boxSize = 8;
static int wSize = 3*boxSize ;
static int hSize = 2*boxSize ;

TQtPatternPopup *TQtPatternPopup::fgBrushPopup = 0;

class MyPanel : public QWidget {
      TQtBrush *fBrush;
      public:
            MyPanel(QWidget *parent, TQtBrush &brush): QWidget(parent), fBrush(&brush){}
   public:
      void SetBrush(TQtBrush *brush) { fBrush = brush; update(); };
      protected:
         void paintEvent(QPaintEvent *) {
            QPainter p(this);
#ifdef R__WIN32
            if ( 3000 <= fBrush->GetStyle() && fBrush->GetStyle() < 4000) {
               QPixmap &px = *fBrush->pixmap();
               px.fill(fBrush->GetColor());
               p.drawTiledPixmap(rect(), px);
            } else 
#endif
               p.fillRect(rect(), *fBrush);
         }
   };
//________________________________________________________________________________
//TQtPatternFrame::TQtPatternFrame( QWidget *p, ULong_t color, Int_t /*n*/) 
//: QToolButton(p)
//{
//   setPaletteBackgroundColor (gQt->QtColor(color));
//   setPaletteForegroundColor (gQt->QtColor(color));
//   fColor = color;
//}

 //________________________________________________________________________________
TQtPatternFrame::TQtPatternFrame(QWidget *p, Style_t pattern, Int_t n):QFrame(p)
,fActive(n), fPanel(0)
{
   fBrush.SetStyle(pattern);

   languageChange();
#if QT_VERSION < 0x40000
   QToolTip::add(this,fBrushTipLabel + QString::number(fBrush.GetStyle()) );
#else
   setToolTip(tr(fBrushTipLabel + QString::number(fBrush.GetStyle())));
#endif      
   setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
   SetIcon();
   resize(wSize, hSize);   
}
 //________________________________________________________________________________
TQtPatternFrame::TQtPatternFrame(QWidget *p, TQtBrush &pattern, Int_t n): QFrame(p)
,fActive(n),fBrush(pattern),fPanel(0)
{ 
   if (boxSize == 0 ) {
#if QT_VERSION < 0x40000
      boxSize = 
            QApplication::style().subRect(QStyle::SR_PushButtonContents,this).height();
#else
      QStyleOptionButton button;
      boxSize = 
            QApplication::style()->subElementRect(QStyle::QStyle::SE_PushButtonContents,&button).height();
#endif
    }

   languageChange();
#if QT_VERSION < 0x40000
   QToolTip::add(this,fBrushTipLabel + QString::number(fBrush.GetStyle()) );
#else   
   setToolTip(fBrushTipLabel + QString::number(fBrush.GetStyle()) );
#endif   
   setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
   SetIcon();
   resize(wSize, hSize);
}
//________________________________________________________________________________
void TQtPatternFrame::SetBrush(TQtBrush &newBrush)
{ 
   fBrush = newBrush;
   if (fPanel) ((MyPanel *)fPanel)->SetBrush(&fBrush);
}

//________________________________________________________________________________
void TQtPatternFrame::SetIcon()
{   
   if (!fPanel) {
#if QT_VERSION < 0x40000
      setMargin(2);
#else
      setContentsMargins(2,2,2,2);
#endif
      QGridLayout *l = new QGridLayout(this);
      l->setMargin(1);
      l->setSpacing(0);
      fPanel = new MyPanel(this,fBrush);
      l->addWidget(fPanel,0,0);
   }
}
//________________________________________________________________________________
QSize TQtPatternFrame::sizeHint () const 
{
   return QSize(wSize, hSize);
}

//______________________________________________________________________________
void TQtPatternFrame::languageChange()
{
   fBrushTipLabel = tr("Fill Style:  ");
}

//________________________________________________________________________________
void TQtPatternFrame::mouseReleaseEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)  emit clicked();      
   return QFrame::mouseReleaseEvent(event);
}

//________________________________________________________________________________
TQtPatternPopup::TQtPatternPopup(QWidget *p, TQtBrush &color,const char *name, bool modal, Qt::WFlags f) :
#if QT_VERSION < 0x40000
   QDialog(p,name,modal,f)
#else
   QDialog(p,f)
#endif            
 ,fCurrentBrush(color)
{ 
   QGridLayout *gridLayout = new QGridLayout(this);
   gridLayout->setMargin(0);
   QFrame *group = new QFrame(this);
   gridLayout->addWidget(group,0,0);
   group->setFrameShape(QFrame::Panel);
   setName(name);
   setModal(modal);
   
   gridLayout = new QGridLayout(group);
   gridLayout->setMargin(2);  
   gridLayout->setSpacing(1); 
   
   int i = 0;
   TQtPatternFrame *fr = new TQtPatternFrame(group,ULong_t(0), i++); 
   gridLayout->addWidget(fr,0,0);
   connect(fr,SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
   fr->resize(wSize, hSize);
#if QT_VERSION < 0x40000
   QToolTip::add(fr," Style: 0 - transparent" );
#else   
   fr->setToolTip(tr(" Style: 0 - transparent" ));
#endif 
   
   fr = new TQtPatternFrame(group,ULong_t(1000), i++); 
   gridLayout->addWidget(fr,0,1);
   connect(fr,SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
   fr->resize(wSize, hSize);
#if QT_VERSION < 0x40000
   QToolTip::add(fr," Style: 1000 - solid" );
#else   
   fr->setToolTip(tr(" Style: 1000 - solid"    ));
#endif 
   
   fr = new TQtPatternFrame(group,ULong_t(2000), i++); 
   gridLayout->addWidget(fr,0,2);
   fr->resize(wSize, hSize);
   connect(fr,SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
#if QT_VERSION < 0x40000
   QToolTip::add(fr," Style: 2000 - pattern" );
#else   
   fr->setToolTip(tr(" Style: 2000 - pattern"  ));
#endif 
   for (int k=1;k < 10;k++) {
      for (int j=0;j <= 2;j++) {    
        fr = new TQtPatternFrame(group,ULong_t(3000+i-3), i++); 
        gridLayout->addWidget(fr,k,j);
        fr->resize(wSize, hSize);
        connect(fr,SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
      }
   }
   resize(2  + 3*(wSize+1) +1, 2 + 10*(hSize+1) + 2 );
}
//________________________________________________________________________________
TQtPatternPopup *TQtPatternPopup::Create(QWidget *p, TQtBrush &color,const char *name, bool modal, Qt::WFlags f) 
{ 
  // Create the singletone object
  if (!fgBrushPopup) 
     fgBrushPopup =  new TQtPatternPopup(p, color,name, modal, f);
  return fgBrushPopup;
}
      
//________________________________________________________________________________
TQtPatternPopup::~TQtPatternPopup()
{ }

//________________________________________________________________________________
void TQtPatternPopup::SetActiveSlot()
{
   TQtPatternFrame *patternFrame = (TQtPatternFrame*)sender();
   BrushSelected(patternFrame->GetBrush());
}

//________________________________________________________________________________
void TQtPatternPopup::BrushSelected(const TQtBrush &pattern )
{   
   fCurrentBrush = pattern;
   accept();
}
//______________________________________________________________________________
void TQtPatternPopup::languageChange()
{
    //setCaption( tr( "Select Brush" ) );
    //fPushButton->setText( tr( "pushButton39" ) );
    //QToolTip::add( fPushButton, tr( "Current Brush" ) );
    //QWhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
}
//________________________________________________________________________________
TQtPatternSelectButton::TQtPatternSelectButton(QWidget *p, const char *name, Qt::WFlags f)
#if QT_VERSION < 0x40000
    : QFrame(p,name,f)
#else /* QT_VERSION */
    : QFrame(p,f)
#endif /* QT_VERSION */
    , fBrushEmitter(0)
{
   if (name && name[0]) setName(name);
   fBrush.SetStyle();
   CreateWidget();
}

//________________________________________________________________________________
TQtPatternSelectButton::TQtPatternSelectButton( QWidget *p, UInt_t pattern, Int_t /*id*/,TEmitRootSignal *emitter) 
#if QT_VERSION < 0x40000
    : QFrame(p,"BrushSelectButton",Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop)
#else /* QT_VERSION */
    : QFrame(p)
#endif /* QT_VERSION */
   , fBrushEmitter(emitter)
{
#if QT_VERSION >= 0x40000
   setName("BrushSelectButton");
   setWindowFlags (Qt::WindowStaysOnTopHint);
#endif   
   fBrush.SetStyle(pattern);
   CreateWidget();
}

//________________________________________________________________________________
TQtPatternSelectButton::TQtPatternSelectButton( QWidget *p, TQtBrush &pattern, Int_t /*id*/,TEmitRootSignal *emitter) 
    : QFrame(p)
    , fBrush(pattern),fBrushEmitter(emitter)
{
   setName("BrushSelectButton");
   CreateWidget();
}
//________________________________________________________________________________
void TQtPatternSelectButton::CreateWidget() 
{

    // setGeometry( QRect( 80, 30, 80, 27 ) );
    setLineWidth(1);
    //setFrameShape( QFrame::StyledPanel );
    //setFrameShadow( QFrame::Raised );
    
  
    QHBoxLayout *layout = new QHBoxLayout(this, 0, 0, "layoutPatternSelect"); 
    layout->setSpacing(0);
    layout->setMargin(0);
    

    //  Brush Button TQtPatternFrame
    fPushButton = new TQtPatternFrame( this, fBrush );
      layout->setStretchFactor(fPushButton,3); 
      layout->addWidget(fPushButton);
      connect(fPushButton,SIGNAL(clicked()),this, SLOT(PopupDialog()));

    // The vertical divider 
    QFrame *line1 = new QFrame( this, "line1" );
      line1->setFrameShape ( QFrame::VLine  );
      line1->setFrameShadow( QFrame::Sunken );
      
      layout->setStretchFactor(line1,1); 
      layout->addWidget( line1 );

    // The arrow button
    fArrowButton = new QToolButton( Qt::DownArrow,this,"arrowDownToolButton" );
      fArrowButton->setFixedWidth(fArrowButton->sizeHint().width()+4);
      layout->setStretchFactor(fArrowButton,1); 
      layout->addWidget( fArrowButton );
      connect(fArrowButton,SIGNAL(clicked()),this, SLOT(PopupDialog()));

    languageChange();
#if QT_VERSION < 0x40000
     clearWState( WState_Polished );
#endif /* QT_VERSION */
}
//________________________________________________________________________________
TQtPatternSelectButton::~TQtPatternSelectButton()
{ }

//________________________________________________________________________________
void TQtPatternSelectButton::PopupDialog()
{
   TQtPatternPopup *popup = TQtPatternPopup::Create(0,fBrush);
   QPoint global = fArrowButton->mapToGlobal(QPoint(0,0));
   popup->move(global.x()
              ,global.y()+fArrowButton->frameSize().height());
   if ( popup->exec() == QDialog::Accepted ){
      // to emit the ROOT signal
      SetBrush(popup->Brush());
      if (fBrushEmitter) fBrushEmitter->EmitRootSignal(fBrush.GetStyle());
      emit brushSelected(fBrush);
   }
}
//________________________________________________________________________________
void TQtPatternSelectButton::SetBrush(UInt_t style) {
   if (UInt_t(fBrush.GetStyle()) != style) {
      fBrush.SetStyle(style);
      fPushButton->SetBrush(fBrush);
   }
}

//________________________________________________________________________________
void TQtPatternSelectButton::SetBrush(const TQtBrush &pattern)
{
   // Set color.
//   if (fBrush != pattern) 
      {
      fBrush = pattern;
      fPushButton->SetBrush(fBrush);
   }
}

//______________________________________________________________________________
void TQtPatternSelectButton::languageChange()
{
    setCaption( tr( "Select Pattern" ) );
    if (fPushButton) {
       QToolTip::add( fPushButton, tr( "Current Pattern" ) );
#if QT_VERSION < 0x40000
       QWhatsThis::add( fPushButton, tr( "Your current attribute fill pattern" ) );
#else /* QT_VERSION */
       fPushButton->setWhatsThis(tr( "Your current attribute fill pattern" ) );
#endif /* QT_VERSION */
    }
}
