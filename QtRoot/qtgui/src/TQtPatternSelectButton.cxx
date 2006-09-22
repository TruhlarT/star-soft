// @(#)root/gui:$Name:  $:$Id: TQtPatternSelectButton.cxx,v 1.2 2006/09/22 17:27:11 fine Exp $
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
#include "TColor.h"

#include <qcolordialog.h> 
#include <qtooltip.h> 
#include <qcolor.h> 
#if QT_VERSION < 0x40000
#  include <qhgroupbox.h> 
#endif /* QT_VERSION */
#include <qapplication.h> 

#include <qstyle.h>
#include <qvariant.h>
#include <qlayout.h>
#if QT_VERSION < 0x40000
#  include <qwhatsthis.h>
#else /* QT_VERSION */
#  include <q3whatsthis.h>
#  include <QStyleOptionButton>
//Added by qt3to4:
#  include <QPixmap>
#  include <Q3Frame>
#  include <Q3HBoxLayout>
#endif /* QT_VERSION */

//ClassImp(TQtPatternFrame)
//ClassImp(TQt16ColorSelector)
//ClassImp(TQtPatternPopup)
//ClassImp(TQtPatternSelectButton)

static int boxSize = 8;
static int wSize = 4*boxSize ;
static int hSize = 3*boxSize ;

TQtPatternPopup *TQtPatternPopup::fgBrushPopup = 0;

//________________________________________________________________________________
//TQtPatternFrame::TQtPatternFrame( QWidget *p, ULong_t color, Int_t /*n*/) 
//: QToolButton(p)
//{
//   setPaletteBackgroundColor (gQt->QtColor(color));
//   setPaletteForegroundColor (gQt->QtColor(color));
//   fColor = color;
//}

 //________________________________________________________________________________
TQtPatternFrame::TQtPatternFrame(QWidget *p, Style_t pattern, Int_t n):QToolButton(p),fActive(n)
{
   fBrush.SetStyle(pattern);
   // setMinimumSize( QSize( wSize, hSize ) );
   // setMaximumSize( QSize( wSize, hSize ) );
   // setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

   languageChange();
   QToolTip::add(this,fBrushTipLabel + QString::number(fBrush.GetStyle()) );
   
}
 //________________________________________________________________________________
TQtPatternFrame::TQtPatternFrame(QWidget *p, TQtBrush &pattern, Int_t n): QToolButton(p),fActive(n),fBrush(pattern)
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

   // setMinimumSize( QSize( wSize, hSize ) );
   // setMaximumSize( QSize( wSize, hSize ) );
   // setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

   languageChange();
   QToolTip::add(this,fBrushTipLabel + QString::number(fBrush.GetStyle()) );
  //  resize(10,10);
}
//________________________________________________________________________________
QSize TQtPatternFrame::sizeHint () const 
{
   return QSize(wSize, hSize);
}
//________________________________________________________________________________
void TQtPatternFrame::drawButtonLabel(QPainter *paint)
{
#if QT_VERSION >= 0x40000
   QStyleOptionButton button;
   QRect buttonDraw = 
         QApplication::style()->subElementRect(QStyle::QStyle::SE_PushButtonContents,&button);
#else
   QRect buttonDraw =  
         QApplication::style().subRect(QStyle::SR_PushButtonContents,this);
#endif
   buttonDraw.addCoords(1,1,-1,-2);
#ifdef R__WIN32
   if ( 3000 <= fBrush.GetStyle() && fBrush.GetStyle() < 4000) {
      QPixmap &px = *fBrush.pixmap();
      px.fill(fBrush.GetColor());
      paint->drawTiledPixmap(buttonDraw, px);
   } else 
#endif
      paint->fillRect (buttonDraw, fBrush);
}
//______________________________________________________________________________
void TQtPatternFrame::languageChange()
{
   fBrushTipLabel = tr("Fill Style:  ");
}

//________________________________________________________________________________
TQt16BrushSelector::TQt16BrushSelector( QWidget *p,const char *name) :
#if QT_VERSION < 0x40000
   QFrame (p, name),fActive(-1)
#else /* QT_VERSION */
   Q3Frame (p, name),fActive(-1)
#endif /* QT_VERSION */
{
   if (!name)
      setName("BrushSelect16");
   // setGeometry(QRect(0,0,200,200));
   
//   QButtonGroup *group=  new  QButtonGroup (4, Qt::Horizontal , this, "colorGroup");
#if QT_VERSION < 0x40000
   QButtonGroup *group=  new  QButtonGroup (3, Qt::Horizontal , this, "colorGroup");
#else /* QT_VERSION */
   Q3ButtonGroup *group=  new  Q3ButtonGroup (3, Qt::Horizontal , this, "colorGroup");
#endif /* QT_VERSION */
   group->setGeometry(QRect(0,0,2 + 3*(wSize+1) +1, 2 + 10*(hSize+1) +1));

   group->setExclusive(true);
   languageChange();
   group->setInsideMargin(2);
   group->setInsideSpacing(1);
   
   int i =0;
   fCe[0] = new TQtPatternFrame(group,ULong_t(0), 0); 
   QToolTip::add(fCe[0]," Style: 0 - transparent" );
   fCe[1] = new TQtPatternFrame(group,ULong_t(1000), 1); 
   QToolTip::add(fCe[1]," Style: 1000 - solid" );
   for (i=0;i < 26;i++) {
     fCe[i+2] = new TQtPatternFrame(group,ULong_t(3000+i), i+2); 
     connect(fCe[i],SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
  }
}
//________________________________________________________________________________
TQt16BrushSelector::~TQt16BrushSelector()
{ }
//________________________________________________________________________________
void TQt16BrushSelector::SetActiveSlot()
{
   TQtPatternFrame *patternFrame = (TQtPatternFrame*)sender();
   // colorFrame->GetBrush();
   emit BrushChanged(patternFrame->GetBrush());
}
//________________________________________________________________________________
void TQt16BrushSelector::SetActiveSlot(Int_t newat)
{ 
   if (fActive != newat ) {
      fActive = newat;
      emit BrushChanged(GetActiveBrush());
   }
}
//________________________________________________________________________________
void TQt16BrushSelector::SetActive(Int_t newat)
{
   if ( fActive != newat)  {
      SetActiveSlot(newat);
      // setButton(newat);
   }
}
//________________________________________________________________________________
const TQtBrush  &TQt16BrushSelector::GetActiveBrush() const
{
   const TQtPatternFrame &activeButton = *fCe[GetActive()];
   return activeButton.GetBrush();
}
//______________________________________________________________________________
void TQt16BrushSelector::languageChange()
{
    //setCaption( tr( "Select Brush" ) );
    //fPushButton->setText( tr( "pushButton39" ) );
    //QToolTip::add( fPushButton, tr( "Current Brush" ) );
    //QWhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
}
//________________________________________________________________________________
#if QT_VERSION < 0x40000
TQtPatternPopup::TQtPatternPopup(QWidget *p, TQtBrush &color,const char *name, bool modal, WFlags f) :
#else /* QT_VERSION */
TQtPatternPopup::TQtPatternPopup(QWidget *p, TQtBrush &color,const char *name, bool modal, Qt::WFlags f) :
#endif /* QT_VERSION */
   QDialog(p,name,modal,f),fCurrentBrush(color)
{ 
#if QT_VERSION < 0x40000
   QVBox *inter =  new QVBox(this);
#else /* QT_VERSION */
   Q3VBox *inter =  new Q3VBox(this);
#endif /* QT_VERSION */
 
   inter->setGeometry( QRect( 2, 2, 2  + 3*(wSize+1) +1, 2 + 10*(hSize+1) + 2 ) );
   TQt16BrushSelector *cs = new TQt16BrushSelector(inter);
 
   connect(cs,SIGNAL(BrushChanged(const TQtBrush &)), this, SLOT(BrushSelected(const TQtBrush &)));
   adjustSize();
}
//________________________________________________________________________________
#if QT_VERSION < 0x40000
TQtPatternPopup *TQtPatternPopup::Create(QWidget *p, TQtBrush &color,const char *name, bool modal, WFlags f) 
#else /* QT_VERSION */
TQtPatternPopup *TQtPatternPopup::Create(QWidget *p, TQtBrush &color,const char *name, bool modal, Qt::WFlags f) 
#endif /* QT_VERSION */
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
TQtPatternSelectButton::TQtPatternSelectButton( QWidget *p, const char *name, Qt::WFlags f) 
#if QT_VERSION < 0x40000
    : QFrame(p,name,f),fBrushEmitter(0)
#else /* QT_VERSION */
    : Q3Frame(p,name,f),fBrushEmitter(0)
#endif /* QT_VERSION */
{
   fBrush.SetStyle();
   CreateWidget();
}

//________________________________________________________________________________
TQtPatternSelectButton::TQtPatternSelectButton( QWidget *p, UInt_t pattern, Int_t /*id*/,TEmitRootSignal *emitter) 
#if QT_VERSION < 0x40000
    : QFrame(p,"BrushSelectButton",Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop),fBrushEmitter(emitter)
#else /* QT_VERSION */
    : Q3Frame(p,"BrushSelectButton",Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop),fBrushEmitter(emitter)
#endif /* QT_VERSION */
{
   fBrush.SetStyle(pattern);
   CreateWidget();
}
//________________________________________________________________________________
TQtPatternSelectButton::TQtPatternSelectButton( QWidget *p, TQtBrush &pattern, Int_t /*id*/,TEmitRootSignal *emitter) 
#if QT_VERSION < 0x40000
    : QFrame(p,"BrushSelectButton"),fBrush(pattern),fBrushEmitter(emitter)
#else /* QT_VERSION */
    : Q3Frame(p,"BrushSelectButton"),fBrush(pattern),fBrushEmitter(emitter)
#endif /* QT_VERSION */
{
   CreateWidget();
}
//________________________________________________________________________________
void TQtPatternSelectButton::CreateWidget() 
{

      setGeometry( QRect( 80, 30, 80, 27 ) );
    setLineWidth(1);
    //setFrameShape( QFrame::StyledPanel );
    //setFrameShadow( QFrame::Raised );
#if QT_VERSION < 0x40000
    setFrameShadow(QFrame::Plain);
#else /* QT_VERSION */
    setFrameShadow(Q3Frame::Plain);
#endif /* QT_VERSION */
    
  
#if QT_VERSION < 0x40000
    QHBoxLayout *layout = new QHBoxLayout(this, 0, 0, "layoutPatternSelect"); 
#else /* QT_VERSION */
    Q3HBoxLayout *layout = new Q3HBoxLayout(this, 0, 0, "layoutPatternSelect"); 
#endif /* QT_VERSION */

    //  Brush Button TQtPatternFrame
    fPushButton = new TQtPatternFrame( this, fBrush );
      layout->setStretchFactor(fPushButton,3); 
      layout->addWidget(fPushButton);
      connect(fPushButton,SIGNAL(clicked()),this, SLOT(PopupDialog()));

    // The vertical divider 
#if QT_VERSION < 0x40000
    QFrame *line1 = new QFrame( this, "line1" );
      line1->setFrameShape ( QFrame::VLine  );
      line1->setFrameShadow( QFrame::Sunken );
#else /* QT_VERSION */
    Q3Frame *line1 = new Q3Frame( this, "line1" );
      line1->setFrameShape ( Q3Frame::VLine  );
      line1->setFrameShadow( Q3Frame::Sunken );
#endif /* QT_VERSION */
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
      fPushButton->repaint();
      update();
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
      fPushButton->repaint();
            //fPushButton->setEraseColor(color);
      //fPushButton->setPaletteBackgroundColor (color);
      //fPushButton->setPaletteForegroundColor (color); 
      update();
   }
}

//______________________________________________________________________________
void TQtPatternSelectButton::languageChange()
{
    setCaption( tr( "Select Pattern" ) );
    if (fPushButton) {
       fPushButton->setText( tr( "pushButton39" ) );
       QToolTip::add( fPushButton, tr( "Current Pattern" ) );
#if QT_VERSION < 0x40000
       QWhatsThis::add( fPushButton, tr( "Your current attribute fill pattern" ) );
#else /* QT_VERSION */
       Q3WhatsThis::add( fPushButton, tr( "Your current attribute fill pattern" ) );
#endif /* QT_VERSION */
    }
}
