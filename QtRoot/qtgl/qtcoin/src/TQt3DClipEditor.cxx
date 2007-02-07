#include "TQt3DClipEditor.h"
#include <qlayout.h> 
#include <qvbuttongroup.h> 
#include <qradiobutton.h> 

#include <Inventor/manips/SoClipPlaneManip.h>
#include <Inventor/nodes/SoCamera.h>


//_______________________________________________________________________________
TQt3DClipEditor::TQt3DClipEditor ( Place p, QWidget *parent, const char *name, WFlags f)
: QDockWindow(p,parent,name,f), fPlaneEditor(0),fCamera(0)
{  BuildWidget(); }

//_______________________________________________________________________________
TQt3DClipEditor::TQt3DClipEditor(QWidget *parent, const char *name, WFlags f)
: QDockWindow(parent, name, f), fPlaneEditor(0),fCamera(0)
{  BuildWidget();  } 

//_______________________________________________________________________________
void TQt3DClipEditor::BuildWidget()
{
  setCloseMode(QDockWindow::Always);
  QBoxLayout *layout   = boxLayout();
  QVButtonGroup *gr = new QVButtonGroup("Cliping", this);
  layout->addWidget(gr);
  QRadioButton *button = new QRadioButton("X",gr);
                button = new QRadioButton("Y",gr);
                button = new QRadioButton("Z",gr);
  connect(gr,SIGNAL(clicked(int)),this,SLOT(PlaneSelected(int)));
}

//_______________________________________________________________________________
TQt3DClipEditor::~TQt3DClipEditor()
{
   if (fPlaneEditor) fPlaneEditor->unref();
   fPlaneEditor = 0;
   if (fCamera) fCamera->unref();
   fCamera = 0;
}

//_______________________________________________________________________________
void TQt3DClipEditor::SetClipMan(SoClipPlaneManip *man)
{
   if (fPlaneEditor != man) {
      if (fPlaneEditor) fPlaneEditor->unref();
      fPlaneEditor = man;
      if (fPlaneEditor) fPlaneEditor->ref();
   }
}

//_______________________________________________________________________________
void TQt3DClipEditor::SetCamera(SoCamera *cam)
{
   if (fCamera != cam) {
      if (fCamera) fCamera->unref();
      fCamera = cam;
      if (fCamera) fCamera->ref();
   }
}

//_______________________________________________________________________________
SoClipPlaneManip *TQt3DClipEditor::ClipMan() const
{ return fPlaneEditor; }

//_______________________________________________________________________________
SoCamera *TQt3DClipEditor::Camera() const
{ return fCamera; }
//_______________________________________________________________________________
void TQt3DClipEditor::PlaneSelected(int plane)
{
   if (fCamera) {
      switch (plane) {
         case 0:
           fCamera->orientation.setValue(SbRotation(SbVec3f(0, 1, 0), M_PI / 2.0f));
           break;
         case 1:
           fCamera->orientation.setValue(SbRotation(SbVec3f(1, 0, 0), M_PI / 2.0f));
           break;
         case 2:
           fCamera->orientation.setValue(SbRotation(SbVec3f(0, 0, 1), 0.0f));
           break;
      }
      emit Orientation();
   }
}

