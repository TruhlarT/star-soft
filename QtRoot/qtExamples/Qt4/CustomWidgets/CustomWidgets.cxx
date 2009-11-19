#include "CustomWidgets.h"
#include <QWhatsThis>
#include <QLineEdit>
#include <string>
#include "TROOT.h"
#include "TQtWidget.h"
#include "TApplication.h"


/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
//__________________________________________________________________
CustomWidgets::CustomWidgets(QWidget* parent)
: QFrame(parent)
{
   setupUi(this);
   init();
}
//__________________________________________________________________
CustomWidgets::~CustomWidgets(){;}
//__________________________________________________________________
void CustomWidgets::init()
{
//  tQtFloatSlider1->setOrientation(Qt::Horizontal);
//  tQtFloatSpinBox1->SetMinValue(-34.4);
//  tQtFloatSpinBox1->SetMinValue(+46.4);
  horizontalSlider->SetRange( doubleSpinBox->MinValue()
                            ,doubleSpinBox->MaxValue());
  horizontalSlider->SetPageStep(horizontalSlider->Range()/10);
  horizontalSlider->SetLineStep(horizontalSlider->Range()/100);
  connect(horizontalSlider,SIGNAL(ValueChanged(double)),this, SLOT(SliderValue(double)));
  // Connect "Select Color" with the "Select Slider" 
  connect(frame_4,SIGNAL(colorSelected(const QColor &)),frame_3,SLOT(SetBrush(const QColor &))); 
   // Attach the validator to facilitate the ROOT <tab> completion
   // fTabCompValidator = new TQtTabValidator(comboBox1);
   // comboBox1->setValidator(fTabCompValidator);

   // Predefine to ROOT command
   comboBox_4->addItem("gROOT->Macro(\"$ROOTSYS/tutorials/hsimple.C\");");
   comboBox_4->addItem("new TCanvas");
   comboBox_4->addItem("new TBrowser");
   comboBox_4->addItem(".q");
   // Connect the QLineEditor with the ROOT command interpreter  
   connect(comboBox_4->lineEdit(),SIGNAL(returnPressed ()),this, SLOT( execRoot()) );
}
//__________________________________________________________________
void CustomWidgets::destroy()
{}
//__________________________________________________________________
void CustomWidgets::execRoot()
{
   // Execute the ROOT command
   // TQtTabValidator::Clear(); 
   string ROOTCommand = comboBox_4->lineEdit()->text().toStdString();
   gROOT->ProcessLine(ROOTCommand.c_str());
   gROOT->ProcessLine("gPad->Update();");
}

//__________________________________________________________________
void CustomWidgets::SliderValue(double v)
{
   // QRect slRect = tQtFloatSlider1->sliderRect ();
   doubleSpinBox->SetValue(v);
   //QWhatsThis::display(QString::number(v)
   // ,tQtFloatSlider1->mapToGlobal(QPoint(slRect.x(),slRect.y()+slRect.height())));
}

//__________________________________________________________________
void CustomWidgets::widget_destroyed( QObject * )
{
}
//__________________________________________________________________
void CustomWidgets::languageChange(){}
