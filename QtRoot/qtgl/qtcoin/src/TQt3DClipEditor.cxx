#include "TQt3DClipEditor.h"
#include <qlayout.h> 
#include <qvbuttongroup.h> 
#include <qradiobutton.h> 

#include <Inventor/manips/SoClipPlaneManip.h>
#include <Inventor/Qt/viewers/SoQtViewer.h> 
#include <Inventor/nodes/SoCamera.h>


//_______________________________________________________________________________
TQt3DClipEditor::TQt3DClipEditor ( Place p, QWidget *parent, const char *name, WFlags f)
: QDockWindow(p,parent,name,f),fInventorViewer(0),fCameraGroup(0), fPlaneEditor(0),fPlaneGroup(0)
{  BuildWidget(); }

//_______________________________________________________________________________
TQt3DClipEditor::TQt3DClipEditor(QWidget *parent, const char *name, WFlags f)
: QDockWindow(parent, name, f),fInventorViewer(0),fCameraGroup(0), fPlaneEditor(0),fPlaneGroup(0)
{  BuildWidget();  } 

//_______________________________________________________________________________
void TQt3DClipEditor::BuildWidget()
{
  setCloseMode(QDockWindow::Always);
  QBoxLayout *layout   = boxLayout();
  fCameraGroup = new QVButtonGroup("Camera", this);
  layout->addWidget(fCameraGroup ); 
  fCameraGroup->setEnabled(false);
  QRadioButton *button = new QRadioButton("X",fCameraGroup);
                button = new QRadioButton("Y",fCameraGroup);
                button = new QRadioButton("Z",fCameraGroup);
  connect(fCameraGroup,SIGNAL(clicked(int)),this,SLOT(CameraSelected(int)));
  fPlaneGroup = new QVButtonGroup("Cliping", this);
  fPlaneGroup->setEnabled(false);
  layout->addWidget(fPlaneGroup );
         button = new QRadioButton("X",fPlaneGroup);
         button = new QRadioButton("Y",fPlaneGroup);
         button = new QRadioButton("Z",fPlaneGroup);
  connect(fPlaneGroup,SIGNAL(clicked(int)),this,SLOT(PlaneSelected(int)));
}

//_______________________________________________________________________________
TQt3DClipEditor::~TQt3DClipEditor()
{
   if (fPlaneEditor) fPlaneEditor->unref();
   fPlaneEditor = 0;
   fInventorViewer = 0;
}

//_______________________________________________________________________________
void TQt3DClipEditor::SetClipMan(SoClipPlaneManip *man)
{
   if (fPlaneEditor != man) {
      if (fPlaneEditor) fPlaneEditor->unref();
      fPlaneEditor = man;
      if (fPlaneEditor)  fPlaneEditor->ref();
      fPlaneGroup->setEnabled(fPlaneEditor);
   }
}

//_______________________________________________________________________________
void TQt3DClipEditor::SetViewer(SoQtViewer *viewer)
{
   if (fInventorViewer != viewer) {
      fInventorViewer = viewer;
      fCameraGroup->setEnabled(fInventorViewer);
   }
}

//_______________________________________________________________________________
SoClipPlaneManip *TQt3DClipEditor::ClipMan() const
{ return fPlaneEditor; }

//_______________________________________________________________________________
SoQtViewer *TQt3DClipEditor::Viewer() const
{ return fInventorViewer; }
//_______________________________________________________________________________
void TQt3DClipEditor::CameraSelected(int cameraDirection)
{
   if (fInventorViewer) {
      SoCamera *camera = fInventorViewer->getCamera();
      if (camera) {
         switch (cameraDirection) {
         case 0:
            camera->orientation.setValue(SbRotation(SbVec3f(0, 1, 0), -M_PI / 2.0f));
            break;
         case 1:
            camera->orientation.setValue(SbRotation(SbVec3f(1, 0, 0), M_PI / 2.0f));
            break;
         case 2:
            camera->orientation.setValue(SbRotation(SbVec3f(0, 0, 1), 0.0f));
            break;
         }
         emit Orientation();
      }
   }
}

//_______________________________________________________________________________
void TQt3DClipEditor::PlaneSelected(int planeDirection)
{
   if (fPlaneEditor) {
      SbPlane currentClipPlane = fPlaneEditor->plane.getValue();      
      SbVec3d point  = currentClipPlane.getNormal();
              point *= currentClipPlane.getDistanceFromOrigin();

      SbVec3f normal;
      switch (planeDirection) {
         case 0: normal.setValue(1,0,0); break;
         case 1: normal.setValue(0,1,0); break;
         case 2: normal.setValue(0,0,1); break;
      };
      fPlaneEditor->plane.setValue(SbPlane(normal,point));
   }
}

