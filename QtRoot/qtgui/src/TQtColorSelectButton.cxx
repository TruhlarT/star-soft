// @(#)root/gui:$Name:  $:$Id: TQtColorSelectButton.cxx,v 1.3 2007/06/19 23:31:27 fine Exp $
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
// TQtColorFrame, TQt16ColorSelector, TQtColorPopup and TQtColorSelectButton.     //
//                                                                      //
// The TQtColorFrame is a small frame with border showing a specific     //
// color.                                                               //
//                                                                      //
// The TQt16ColorSelector is a composite frame with 16 TQtColorFrames.  //
//                                                                      //
// The TQtColorPopup is a popup containing a TQt16ColorSelector and a   //
// "More..." button which popups up a QColorDialog allowing custom      //
// color selection.                                                     //
//                                                                      //
// The TQtColorSelectButton widget is like a checkbutton but instead of the //
// check mark there is color area with a little down arrow. When        //
// clicked on the arrow the TQtColorPopup pops up.                       //
//                                                                      //
// Selecting a color in this widget will generate the event:            //
// kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      //
// and the signal:                                                      //
// ColorSelected(ULong_t pixel)                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// #include "TGClient.h"
#include "TGQt.h"
#include "TQtColorSelectButton.h"
#include "TQtColorSelect.h"
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
#include <qwhatsthis.h>
#else /* QT_VERSION */
#include <q3whatsthis.h>
#include <q3button.h>
//Added by qt3to4:
#include <Q3Frame>
#include <Q3HBoxLayout>
#include <QStyleOptionButton>
#endif /* QT_VERSION */

//ClassImp(TQtColorFrame)
//ClassImp(TQt16ColorSelector)
//ClassImp(TQtColorPopup)
//ClassImp(TQtColorSelectButton)

static int boxSize = 22;

TQtColorPopup *TQtColorPopup::fgColorPopup = 0;

//________________________________________________________________________________
//TQtColorFrame::TQtColorFrame( QWidget *p, ULong_t color, Int_t /*n*/) 
//: QToolButton(p)
//{
//   setPaletteBackgroundColor (gQt->QtColor(color));
//   setPaletteForegroundColor (gQt->QtColor(color));
//   fColor = color;
//}

//________________________________________________________________________________
TQtColorFrame::TQtColorFrame(QWidget *p, const QColor &color, Int_t n): QToolButton(p),fActive(n),fColor(color)
{
   setPaletteBackgroundColor (fColor);
   setPaletteForegroundColor (fColor);
   if (boxSize == 0 ) {
#if QT_VERSION < 0x40000
     boxSize =   QApplication::style().subRect(QStyle::SR_PushButtonContents,this).height();
#else
     QStyleOptionButton button;
     QApplication::style()->subElementRect(QStyle::QStyle::SE_PushButtonContents,&button).height();
#endif
    }

   setMinimumSize( QSize( boxSize, boxSize ) );
   setMaximumSize( QSize( boxSize, boxSize ) );
   setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

   languageChange();
   QToolTip::add(this,fColorTipLabel + fColor.name());
  //  resize(10,10);
}
//________________________________________________________________________________
QSize TQtColorFrame::sizeHint () const 
{
   return QSize(boxSize,boxSize);
}
//________________________________________________________________________________
void TQtColorFrame::drawButtonLabel(QPainter *paint)
{
#if QT_VERSION < 0x40000
     QRect buttonDraw =  QApplication::style().subRect(QStyle::SR_PushButtonContents,this);
#else
     QStyleOptionButton button;
     QRect buttonDraw = QApplication::style()->subElementRect(QStyle::QStyle::SE_PushButtonContents,&button);
#endif

   buttonDraw.addCoords(1,1,-1,-2);
   paint->fillRect (buttonDraw, fColor);
}
//______________________________________________________________________________
void TQtColorFrame::languageChange()
{
   fColorTipLabel = tr("Color ");
}

//________________________________________________________________________________
TQt16ColorSelector::TQt16ColorSelector( QWidget *p,const char *name) :
#if QT_VERSION < 0x40000
   QFrame (p, name),fActive(-1)
#else /* QT_VERSION */
   Q3Frame (p, name),fActive(-1)
#endif /* QT_VERSION */
{
   if (!name)
      setName("ColorSelect16");
   // setGeometry(QRect(0,0,200,200));
   
#if QT_VERSION < 0x40000
   QButtonGroup *group=  new  QButtonGroup (4, Qt::Horizontal , this, "colorGroup");
#else /* QT_VERSION */
   Q3ButtonGroup *group=  new  Q3ButtonGroup (4, Qt::Horizontal , this, "colorGroup");
#endif /* QT_VERSION */
   group->setGeometry(QRect(0,0,2 + 4*(boxSize+1) +1, 2 + 4*(boxSize+1) +1));

   group->setExclusive(true);
   languageChange();
   group->setInsideMargin(2);  
   group->setInsideSpacing(1); 
   Color_t  defColors[] = {  0, 1 , 2 , 3 
                           , 4, 5 , 6 , 7
                           , 8, 9 ,30 ,38
                           , 41,42,50 ,51 
   };
   int i =0;
   int nDefColors = sizeof(defColors)/sizeof(Color_t);
   for (i=0;i < nDefColors;i++) {
     fCe[i] = new TQtColorFrame(group,gQt->ColorIndex(defColors[i]), i);
     connect(fCe[i],SIGNAL(clicked()),this,SLOT(SetActiveSlot()));
  }
  connect(group,SIGNAL(clicked(int)),this,SLOT(SetActiveSlot(int)));
 }
//________________________________________________________________________________
TQt16ColorSelector::~TQt16ColorSelector()
{ }
//________________________________________________________________________________
void TQt16ColorSelector::SetActiveSlot()
{
   TQtColorFrame *colorFrame = (TQtColorFrame*)sender();
   colorFrame->GetColor();
   emit ColorChanged(colorFrame->GetColor());
}
//________________________________________________________________________________
void TQt16ColorSelector::SetActiveSlot(Int_t newat)
{ 
   if (fActive != newat ) {
      fActive = newat;
      emit ColorChanged(GetActiveColor());
   }
}
//________________________________________________________________________________
void TQt16ColorSelector::SetActive(Int_t newat)
{
   if ( fActive != newat)  {
      SetActiveSlot(newat);
      // setButton(newat);
   }
}
//________________________________________________________________________________
const QColor  &TQt16ColorSelector::GetActiveColor() const
{
   const TQtColorFrame &activeButton = *fCe[GetActive()];
   return activeButton.GetColor();
}
//______________________________________________________________________________
void TQt16ColorSelector::languageChange()
{
    //setCaption( tr( "Select Color" ) );
    //fPushButton->setText( tr( "pushButton39" ) );
    //QToolTip::add( fPushButton, tr( "Current Color" ) );
    //QWhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
}
//________________________________________________________________________________
#if QT_VERSION < 0x40000
TQtColorPopup::TQtColorPopup(QWidget *p, QColor &color,const char *name, bool modal, WFlags f) :
#else /* QT_VERSION */
TQtColorPopup::TQtColorPopup(QWidget *p, QColor &color,const char *name, bool modal, Qt::WFlags f) :
#endif /* QT_VERSION */
   QDialog(p,name,modal,f),fCurrentColor(color)
{ 
#if QT_VERSION < 0x40000
   QVBox *inter =  new QVBox(this);
#else /* QT_VERSION */
   Q3VBox *inter =  new Q3VBox(this);
#endif /* QT_VERSION */
   inter->setGeometry( QRect( 2, 2, 2 + 4*(boxSize+1) +1 ,2 + 5*(boxSize+1) + boxSize/2 + 4 ) );
   TQt16ColorSelector *cs = new TQt16ColorSelector(inter);
   
   // The horizontal divider 
#if QT_VERSION < 0x40000
   QFrame *line1 = new QFrame( inter, "lineH" );
   line1->setFrameShape ( QFrame::HLine  );
   line1->setFrameShadow( QFrame::Sunken );
#else /* QT_VERSION */
   Q3Frame *line1 = new Q3Frame( inter, "lineH" );
   line1->setFrameShape ( Q3Frame::HLine  );
   line1->setFrameShadow( Q3Frame::Sunken );
#endif /* QT_VERSION */

   QPushButton *other     = new QPushButton("Other...",inter);
   other->setAutoDefault(true); 
   QToolTip::add(other,"Popups up Color Selector");
   connect(cs,SIGNAL(ColorChanged(const QColor &)), this, SLOT(ColorSelected(const QColor &)));
   connect(other,SIGNAL(clicked()), this, SLOT(ColorSelectDialog()));
   adjustSize();
}
//________________________________________________________________________________
#if QT_VERSION < 0x40000
TQtColorPopup *TQtColorPopup::Create(QWidget *p, QColor &color,const char *name, bool modal, WFlags f) 
#else /* QT_VERSION */
TQtColorPopup *TQtColorPopup::Create(QWidget *p, QColor &color,const char *name, bool modal, Qt::WFlags f) 
#endif /* QT_VERSION */
{ 
  // Create the singletone object
  if (!fgColorPopup) 
     fgColorPopup =  new TQtColorPopup(p, color,name, modal, f);
  return fgColorPopup;
}
      
//________________________________________________________________________________
TQtColorPopup::~TQtColorPopup()
{ }

//________________________________________________________________________________
void TQtColorPopup::ColorSelectDialog()
{
   ColorSelected(QColorDialog::getColor(fCurrentColor, this));
}
//________________________________________________________________________________
void TQtColorPopup::ColorSelected(const QColor &color )
{   
   if (fCurrentColor != color) {
      fCurrentColor = color;
   }
   accept();
}
//______________________________________________________________________________
void TQtColorPopup::languageChange()
{
    //setCaption( tr( "Select Color" ) );
    //fPushButton->setText( tr( "pushButton39" ) );
    //QToolTip::add( fPushButton, tr( "Current Color" ) );
    //QWhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
}
//________________________________________________________________________________
TQtColorSelectButton::TQtColorSelectButton( QWidget *p,  const char *name,Qt::WFlags f)
#if QT_VERSION < 0x40000
    : QFrame(p,name,f),fColor("grey"),fColorEmitter(0)
#else /* QT_VERSION */
    : Q3Frame(p,name,f),fColor("grey"),fColorEmitter(0)
#endif /* QT_VERSION */
{
   CreateWidget();
}

//________________________________________________________________________________
TQtColorSelectButton::TQtColorSelectButton( QWidget *p, UInt_t pixel, Int_t /*id*/,TColorEmit *emitter) 
#if QT_VERSION < 0x40000
    : QFrame(p,"ColorSelectButton",Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop),fColor(gQt->QtColor(pixel)),fColorEmitter(emitter)
#else /* QT_VERSION */
    : Q3Frame(p,"ColorSelectButton",Qt::WStyle_Customize | Qt::WStyle_NoBorder|Qt::WStyle_StaysOnTop),fColor(gQt->QtColor(pixel)),fColorEmitter(emitter)
#endif /* QT_VERSION */
{
   CreateWidget();
}
//________________________________________________________________________________
TQtColorSelectButton::TQtColorSelectButton( QWidget *p, QColor &color, Int_t /*id*/,TColorEmit *emitter) 
#if QT_VERSION < 0x40000
    : QFrame(p,"ColorSelectButton"),fColor(color),fColorEmitter(emitter)
#else /* QT_VERSION */
    : Q3Frame(p,"ColorSelectButton"),fColor(color),fColorEmitter(emitter)
#endif /* QT_VERSION */
{
   CreateWidget();
}
//________________________________________________________________________________
void TQtColorSelectButton::CreateWidget() 
{
    setSizePolicy(QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed ));
    QRect r;
#if QT_VERSION < 0x40000
    r = QApplication::style().querySubControlMetrics(QStyle::CC_ComboBox, this, QStyle::SC_ComboBoxEditField);
          //QRect r = QStyle::visualRect( combo->style().querySubControlMetrics(QStyle::CC_ComboBox, combo,
	 //							        combo );
#else
      QStyleOptionComboBox editField;
      r = QApplication::style()->subControlRect(QStyle::CC_ComboBox, &editField, QStyle::SC_ComboBoxEditField);
#endif
    setMinimumSize( QSize( int(r.width()*0.75), r.height() ) );
    setLineWidth(1);
    //setFrameShape( QFrame::StyledPanel );
#if QT_VERSION < 0x40000
    setFrameShadow( QFrame::Raised );
#else /* QT_VERSION */
    setFrameShadow( Q3Frame::Raised );
#endif /* QT_VERSION */
    //setFrameShadow(QFrame::Plain);
    
#if QT_VERSION < 0x40000
    QHBoxLayout *layout = new QHBoxLayout( this, 0, 0, "layoutColorButton"); 
#else /* QT_VERSION */
    Q3HBoxLayout *layout = new Q3HBoxLayout( this, 0, 0, "layoutColorButton"); 
#endif /* QT_VERSION */
       
    //  Color Button
#if QT_VERSION < 0x40000
    fPushButton = new QButton( this, "currentColorButton" );        
#else /* QT_VERSION */
    fPushButton = new Q3Button( this, "currentColorButton" );        
#endif /* QT_VERSION */
      fPushButton->setPaletteBackgroundColor (fColor);
      fPushButton->setEraseColor(fColor);
      layout->setStretchFactor(fPushButton,4); 
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
#endif
}
//________________________________________________________________________________
TQtColorSelectButton::~TQtColorSelectButton()
{ }

//________________________________________________________________________________
void TQtColorSelectButton::PopupDialog()
{
   TQtColorPopup *popup = TQtColorPopup::Create(0,fColor);
   QPoint global = fArrowButton->mapToGlobal(QPoint(0,0));
   popup->move(global.x()
              ,global.y()+fArrowButton->frameSize().height());
   if ( popup->exec() == QDialog::Accepted ){
      // to emit the ROOT signal
      SetColor(popup->Color());
      ColorSelected();
      if (fColorEmitter) fColorEmitter->ColorEmit(fColor.pixel());
      emit colorSelected(fColor);
   }
}
//________________________________________________________________________________
void TQtColorSelectButton::SetColor(const QColor &color)
{
   // Set color.
   if (fColor != color) {
      fColor = color;
      fPushButton->setEraseColor(color);
      fPushButton->setPaletteBackgroundColor (color);
      fPushButton->setPaletteForegroundColor (color);
  
      update();
   }
}

//______________________________________________________________________________
void TQtColorSelectButton::languageChange()
{
    setCaption( tr( "Select Color" ) );
    if (fPushButton) {
       fPushButton->setText( tr( "pushButton39" ) );
       QToolTip::add( fPushButton, tr( "Current Color" ) );
#if QT_VERSION < 0x40000
       QWhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
#else /* QT_VERSION */
       Q3WhatsThis::add( fPushButton, tr( "Your current attribute fill color" ) );
#endif /* QT_VERSION */
    }
}
