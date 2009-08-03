// @(#)root/ged:$Name:  $:$Id: TQtLineEditor.cxx,v 1.2 2009/08/03 18:02:59 fine Exp $
// Author: Valeri Fine 13/06/06

/*************************************************************************
 * This source is based on TLineEditor, a ROOT GUI toolkit.              *
 * Author: Ilka  Antcheva 24/04/06
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  TQtLineEditor                                                       //
//                                                                      //
//  Implements GUI for editing line attributes: shape, size, angle.     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
//Begin_Html
/*
<img src="gif/TQtLineEditor.gif">
*/
//End_Html


#include "TQtLineEditor.h"
#include "TQtFloatSpinBox.h"

#include <qtooltip.h>
#include <qlabel.h>
#include <qcheckbox.h> 

#if QT_VERSION < 0x40000
#  include <qvbox.h> 
#  include <qvgroupbox.h> 
#  include <qhbuttongroup.h> 
#  include <qvbuttongroup.h>
#else /* QT_VERSION */
#  include <QGroupBox>
#  include <QButtonGroup>
#  include <QVBoxLayout>
#  include <QHBoxLayout>
#endif /* QT_VERSION */

ClassImp(TQtLineEditor)

//______________________________________________________________________________
TQtLineEditor::TQtLineEditor(QMainWindow *p, TCanvas *canvas,  Int_t id, Int_t width,
                           Int_t height, UInt_t options, Pixel_t back)
   : TQtGedAttFrame<TLine>(p, "Line", canvas, id, width, height, options, back)
{
   
}

//______________________________________________________________________________
TQtLineEditor::TQtLineEditor( TCanvas *canvas,QWidget  *p, Int_t id, Int_t width,
                         Int_t height, UInt_t options, Pixel_t back)
   : TQtGedAttFrame<TLine>("Line", p, canvas, id, width, height, options, back)
{
   
}
//______________________________________________________________________________
void TQtLineEditor::BuildView(QWidget  *editorPanel)
{
  // Constructor of line GUI.
  const int space =  3; //  the space between the label and spinbox
  fStartPointX=0; fEndPointX=0; fStartPointY=0;  fEndPointY  =0;
  
#if QT_VERSION < 0x40000  
  QVBox  *vframe  = new QVBox(editorPanel);
  QHBox *hbox = new QHBox(vframe);
  QLabel *label = new QLabel("Points:",hbox); 
#else /* QT_VERSION */
  delete editorPanel->layout();
  QVBoxLayout *vframeLayout  = new QVBoxLayout(editorPanel);
  QHBoxLayout *hbox    = new QHBoxLayout();
  vframeLayout->addLayout(hbox);
  QLabel *label = new QLabel("Points:",editorPanel);
  hbox->addWidget(label);
#endif /* QT_VERSION */
  label->setAlignment(Qt::AlignHCenter);
  
  
#if QT_VERSION < 0x40000
  hbox = new QHBox(vframe); hbox->setSpacing(space);
  label = new QLabel("Start X:",hbox); label->setAlignment(Qt::AlignRight); 
  fStartPointX = new TQtFloatSpinBox(0.0, -1000000.0, 1000000.0, 2, hbox);
  QToolTip::add(fStartPointX,"Set start point X coordinate of Line.");
#else /* QT_VERSION */
  hbox = new  QHBoxLayout; hbox->setSpacing(space);
  vframeLayout->addLayout(hbox);
  label = new QLabel("Start X:",editorPanel); label->setAlignment(Qt::AlignRight); 
  hbox->addWidget(label);  
  fStartPointX = new TQtFloatSpinBox(0.0, -1000000.0, 1000000.0, 2,editorPanel);
  hbox->addWidget(fStartPointX); 
  fStartPointX->setToolTip( tr("Set start point X coordinate of Line."));
#endif /* QT_VERSION */
  
#if QT_VERSION < 0x40000
  hbox = new QHBox(vframe); hbox->setSpacing(space);
  label = new QLabel("Y:",hbox); label->setAlignment(Qt::AlignRight);
  fStartPointY = new TQtFloatSpinBox(0.0, -1000000.0, 1000000.0, 2, hbox);
  QToolTip::add(fStartPointY,"Set start point Y coordinate of Line.");
#else /* QT_VERSION */
  hbox = new QHBoxLayout; hbox->setSpacing(space);
  vframeLayout->addLayout(hbox);
  label = new QLabel("Y:",editorPanel); label->setAlignment(Qt::AlignRight);
  hbox->addWidget(label);  
  fStartPointY = new TQtFloatSpinBox(0.0, -1000000.0, 1000000.0, 2,editorPanel);
  hbox->addWidget(fStartPointY); 
  fStartPointY->setToolTip(tr("Set start point Y coordinate of Line."));
#endif /* QT_VERSION */
  
#if QT_VERSION < 0x40000
  hbox = new QHBox(vframe); hbox->setSpacing(space);
  label = new QLabel("End X:",hbox);label->setAlignment(Qt::AlignRight);
  fEndPointX = new TQtFloatSpinBox(0.25, -1000000.0, 1000000.0, 2, hbox);
  QToolTip::add(fEndPointX,"Set end point X coordinate of Line.");
#else /* QT_VERSION */
  hbox = new QHBoxLayout; hbox->setSpacing(space);
  vframeLayout->addLayout(hbox);
  label = new QLabel("End X:",editorPanel);label->setAlignment(Qt::AlignRight);
  hbox->addWidget(label);  
  fEndPointX = new TQtFloatSpinBox(0.25, -1000000.0, 1000000.0, 2,editorPanel);
  fEndPointX->setToolTip(tr("Set end point X coordinate of Line."));
#endif /* QT_VERSION */
  
#if QT_VERSION < 0x40000
  hbox = new QHBox(vframe); hbox->setSpacing(space);
  label = new QLabel("Y:",hbox);label->setAlignment(Qt::AlignRight);
  fEndPointY = new TQtFloatSpinBox(0.25, -1000000.0, 1000000.0, 2, hbox);
  QToolTip::add(fEndPointY,"Set end point Y coordinate of Line.");
#else /* QT_VERSION */
  hbox = new QHBoxLayout; hbox->setSpacing(space);
  vframeLayout->addLayout(hbox);
  label = new QLabel("Y:",editorPanel);label->setAlignment(Qt::AlignRight);
  hbox->addWidget(label);  
  fEndPointY = new TQtFloatSpinBox(0.25, -1000000.0, 1000000.0, 2,editorPanel);
  fEndPointY->setToolTip(tr("Set end point Y coordinate of Line."));
#endif /* QT_VERSION */
  
#if ROOT_VERSION_CODE > ROOT_VERSION(5,11,3) 
#if QT_VERSION < 0x40000
  fOrientation  = new QVButtonGroup(vframe); fOrientation->setExclusive(TRUE);
  fVertical = new QCheckBox("Vertical",fOrientation);
  QToolTip::add(fVertical,   "Set vertical");
  fVertical->setTristate();
  
  fHorizontal = new QCheckBox("Horizontal",fOrientation);
  QToolTip::add(fHorizontal,"Set horizontal");
  fHorizontal->setTristate();
#else /* QT_VERSION */
  QGroupBox   *group  = new QGroupBox(editorPanel);
  QVBoxLayout *layout = new QVBoxLayout(group);
  fOrientation        = new QButtonGroup(editorPanel); fOrientation->setExclusive(TRUE);
  vframeLayout->addWidget(group);
  
  fVertical = new QCheckBox(tr("Vertical"),group);
  fVertical->setToolTip(tr("Set vertical"));
  fVertical->setTristate();
  layout->addWidget(fVertical);
  fOrientation->addButton(fVertical);
  
  fHorizontal = new QCheckBox(tr("Horizontal"),group);
  fHorizontal->setToolTip(tr("Set horizontal"));
  fHorizontal->setTristate();
  layout->addWidget(fHorizontal);
  fOrientation->addButton(fHorizontal);
#endif /* QT_VERSION */
#else
   fOrientation  = 0; fHorizontal = 0;
#endif   
}

//______________________________________________________________________________
TQtLineEditor::~TQtLineEditor()
{
   // Destructor of line editor.
}

//______________________________________________________________________________
void TQtLineEditor::ConnectSignals2Slots()
{
   // Connect signals to slots.

   ConnectView(fStartPointX,SIGNAL(ValueChanged(double)),this, SLOT(DoStartPointX(double))     );
   ConnectView(fStartPointY,SIGNAL(ValueChanged(double)),this, SLOT(DoStartPointY(double))     );
   ConnectView(fEndPointX,  SIGNAL(ValueChanged(double)),this, SLOT(DoEndPointX(double))       );
   ConnectView(fEndPointY,  SIGNAL(ValueChanged(double)),this, SLOT(DoEndPointY(double))       );
#if ROOT_VERSION_CODE > ROOT_VERSION(5,11,3) 
#if QT_VERSION < 0x40000
   ConnectView(fOrientation,SIGNAL(clicked(int))     ,this, SLOT(DoLineOrientation(int)));
#else
   ConnectView(fOrientation,SIGNAL(buttonClicked(int))     ,this, SLOT(DoLineOrientation(int)));
#endif
#endif   
}

//______________________________________________________________________________
void TQtLineEditor::ChangeView()
{
   // Pick up the used line attributes.
   //  View                    Model

   fStartPointX->SetValue  (fModel->GetX1() );
   fEndPointX  ->SetValue  (fModel->GetX2() );
   fStartPointY->SetValue  (fModel->GetY1() );
   fEndPointY  ->SetValue  (fModel->GetY2() );
#if ROOT_VERSION_CODE > ROOT_VERSION(5,11,3) 
   fHorizontal ->setChecked(fModel->IsHorizontal());
#endif   
}

//______________________________________________________________________________
void TQtLineEditor::DoStartPointX(double value)
{
   // Slot connected to the line start point.

   fModel->SetX1(value);
   // fModel->Paint(fModel->GetDrawOption());
}
//______________________________________________________________________________
void TQtLineEditor::DoStartPointY(double value)
{
   // Slot connected to the line start point.
   fModel->SetY1(value);
}

//______________________________________________________________________________
void TQtLineEditor::DoEndPointX(double value)
{
   // Slot connected to the line EndPoint X.

   fModel->SetX2(value);
}

//______________________________________________________________________________
void TQtLineEditor::DoEndPointY(double value)
{
   // Slot connected to the line EndPoint Y.
   fModel->SetY2(value);
}

//______________________________________________________________________________                                                                                
void TQtLineEditor::DoLineOrientation(int)
{
   // Slot so set the line orientation

#if ROOT_VERSION_CODE > ROOT_VERSION(5,11,3) 
#if QT_VERSION < 0x40000
   fModel->SetVertical  (fVertical  ->state() == QButton::On);
   fModel->SetHorizontal(fHorizontal->state() == QButton::On);
#else /* QT_VERSION */
   fModel->SetVertical  (fVertical  ->state() == QCheckBox::On);
   fModel->SetHorizontal(fHorizontal->state() == QCheckBox::On);
#endif /* QT_VERSION */
#endif   
}


//______________________________________________________________________________                                                                                
//
// Register the GED factory interfaces:
//______________________________________________________________________________                                                                                
static TQtGedFactory<TQtLineEditor>   gQtLineEditor;
