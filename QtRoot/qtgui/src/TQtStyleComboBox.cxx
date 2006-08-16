// @(#)root/gui:$Name:  $:$Id: TQtStyleComboBox.cxx,v 1.1 2006/08/16 19:27:08 fine Exp $
// Author: Valeri Fine 07/07/2006
/****************************************************************************
**
** Copyright (C) 2006 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/
#include "TQtStyleComboBox.h"

#include "TEmbeddedPad.h"
#include "TQtLockWidget.h"
#include "TLine.h"
#include "TText.h"

#include <qpixmap.h>
#include <qsize.h>

//______________________________________________________________________________
TQtStyleComboBox::TQtStyleComboBox( int listSize, QWidget *parent,QString name)
: QComboBox(parent), fPad(0), fItemListSize (listSize)
{
    // The base class for all "style" selectors
   // Add the the prepared Qt item to the QComboBox
#if QT_VERSION < 0x40000
   setName(name);
#else
   setObjectName(name);
#endif
}
//______________________________________________________________________________
TQtStyleComboBox::~TQtStyleComboBox () 
{
   delete fPad; fPad = 0;
}
//______________________________________________________________________________
void TQtStyleComboBox::AddItem(QPixmap &pixmap, QString &seq)
{
   // Add the the prepared Qt item to the QComboBox
#if QT_VERSION < 0x40000
   insertItem(pixmap,seq);
#else
   addItem(pixmap,seq);
#endif
}
//______________________________________________________________________________
void TQtStyleComboBox::Build()
{
   TQtLockWidget(this);

   clear();
   TVirtualPad *padsav = gPad;
   for (Int_t i = 1; i <= fItemListSize; i++) AddItem(i,FALSE);
   if (padsav) padsav->cd();

   SetCurrentItem (1);  // to have first entry selected
   // SetWindowName();
}

//______________________________________________________________________________
void TQtStyleComboBox::SetCurrentItem(int style)
{
   // Select the item using ROOT style type
  setCurrentItem (style-1);
}

//______________________________________________________________________________
TEmbeddedPad  &TQtStyleComboBox::Pad() {
   if (!fPad) {
      fPad = new  TEmbeddedPad("","",width()-40,height()-4,kWhite);
      fPad->SetBorderSize(0);
   }
   return *fPad;
}
 //______________________________________________________________________________
void  TQtStyleComboBox::resizeEvent(QResizeEvent *e)
{
   QComboBox::resizeEvent(e);
   if (abs(e->oldSize().width() -  e->size().width()) > 1 ) {
     TVirtualPad *padsav = fPad;
     fPad = 0;
     Build();
     if (padsav) delete padsav;
   }
}

//______________________________________________________________________________
//
//   TQtLineStyleComboBox
//______________________________________________________________________________
TQtLineStyleComboBox::TQtLineStyleComboBox(QWidget *parent,QString name)
#if QT_VERSION < 0x40000
     : TQtStyleComboBox(5,parent,name)
#else
     : TQtStyleComboBox(10,parent,name)
#endif      
{
   // Create the image of the line using the given styles and the offscreen TPad
}
//______________________________________________________________________________
void TQtLineStyleComboBox::AddItem(int lstyle, bool savepadflag)
{
   // Create the image of the line using the given styles and the offscreen TPad
   TVirtualPad *padsav = savepadflag ? gPad : 0;
   Pad().cd();
   TLine line(0.0,0.5,1.0,0.5);
   QString seq;
   line.SetLineStyle(lstyle);line.SetLineWidth(2);
   line.Draw();
   Pad().Update();
   QPixmap &pixmap = *(QPixmap *)Pad().GetHandle();
   TQtStyleComboBox::AddItem(pixmap,seq.setNum(lstyle));
   if (padsav) padsav->cd();
}
//______________________________________________________________________________
//
//   TQtLineWidthComboBox
//______________________________________________________________________________
//______________________________________________________________________________
TQtLineWidthComboBox::TQtLineWidthComboBox(QWidget *parent,QString name)
      : TQtStyleComboBox(16,parent,name)
{
   // Create the image of the line using the given styles and the offscreen TPad
}
//______________________________________________________________________________
void TQtLineWidthComboBox::AddItem(int lwidth, bool savepadflag)
{
   // Create the image of the line using the given styles and the offscreen TPad
   TVirtualPad *padsav = savepadflag ? gPad : 0;
   Pad().cd();
   TLine line(0.0,0.5,1.0,0.5);
   QString seq;
   line.SetLineWidth(lwidth);
   line.Draw();   Pad().Update();
   QPixmap &pixmap = *(QPixmap*)Pad().GetHandle();
   TQtStyleComboBox::AddItem(pixmap,seq.setNum(lwidth));
   if (padsav) padsav->cd();
}
//_____________________________________________________________________________
//
//  TQtFontTypeComboBox
//______________________________________________________________________________
 TQtFontComboBox::TQtFontComboBox(QWidget *parent,QString name)
      : TQtStyleComboBox(13,parent,name) 
{
   // Create the image of the fonts using the given font number and the offscreen TPad
}
static const char *gFonts[] = {
      "times italic"
    , "times bold"
    , "times bold italic"
    , "helvetica"
    , "helvetica italic"
    , "helvetica bold"
    , "helvetica bold italic"
    , "courier"
    , "courier italic"
    , "courier bold"
    , "courier bold italic"
    , "symbol"
    , "times"

};
//______________________________________________________________________________
void TQtFontComboBox::AddItem(int lfont, bool savepadflag)
{
   // Create the image of the fonts using the given font number and the offscreen TPad
   TVirtualPad *padsav = savepadflag ? gPad : 0;
   Pad().cd();
   TText text(0.0,0.5,gFonts[lfont-1]);
   QString seq;
   text.SetTextFont(lfont*10); text.SetTextSize(0.9);text.SetTextAlign(12);
   text.Draw();    Pad().Update();
   QPixmap &pixmap = *(QPixmap*)Pad().GetHandle();
   TQtStyleComboBox::AddItem(pixmap,seq.setNum(lfont));
   if (padsav) padsav->cd();
}
