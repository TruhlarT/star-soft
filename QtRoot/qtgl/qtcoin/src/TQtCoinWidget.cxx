#include "TVirtualPad.h"
#include "TContextMenu.h"

#include "TQVirtualGL.h"
#include "TQPadOpenGLView.h"

#define QGLVIEWER

#include "TQtCoinWidget.h"
//#include "TQtGLViewerWidget.h"
#include "TObject3DView.h"

#include "TSystem.h"
#include "TROOT.h"
#include "TEnv.h"
#include "TColor.h"

#include <qprinter.h>
#include <qpixmap.h>
#include <qapplication.h>
#include <qclipboard.h>
#include <qregexp.h> 
#include <qimage.h>

#if QT_VERSION < 0x40000
#  include <qfiledialog.h>
#  include <qpopupmenu.h>
#  include <qwhatsthis.h> 
#  include <qaction.h>
#else 
#  include <q3filedialog.h>
#  include <q3popupmenu.h>
#  include <q3whatsthis.h> 
//Added by qt3to4:
#  include <QLabel>
#  include <Q3Action>
#endif 

#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qimage.h>
#include <qgl.h> 
#include <qpngio.h> 

#include <qpainter.h>
#include <qtextstream.h>
#include <qstatusbar.h>
#include <qsplitter.h>

#include <qevent.h>

#ifdef WIN32
#  ifdef CopyFile
#     undef CopyFile
#  endif
#endif


#include "TObject3DView.h"

//=============

//#include "TQtCoinWidget.h"
//#include "TVirtualPad.h"
#include "TView.h"
//#include <qglobal.h>
//#include <qmainwindow.h>

#include <qlayout.h> 
#include <qframe.h> 

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

#include <Inventor/SoPickedPoint.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoBaseColor.h> 
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
//#include <Inventor/VRMLnodes/SoVRMLIndexedLineSet.h>
//#include <Inventor/VRMLnodes/SoVRMLCoordinate.h>
#include <Inventor/VRMLnodes/SoVRMLShape.h>

#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/manips/SoClipPlaneManip.h>

#include <Inventor/SoOffscreenRenderer.h>

#include <Inventor/actions/SoSearchAction.h> 
#include <Inventor/actions/SoToVRML2Action.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoLineHighlightRenderAction.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/nodes/SoDirectionalLight.h>

#include <Inventor/VRMLnodes/SoVRMLGroup.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/manips/SoTabBoxManip.h>
#include <Inventor/annex/HardCopy/SoHardCopy.h>
#include <Inventor/nodes/SoTransparencyType.h> 

#include <Inventor/annex/HardCopy/SoVectorizePSAction.h>
#include <Inventor/annex/HardCopy/SoVectorOutput.h>

#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoToVRML2Action.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>

#include <Inventor/manips/SoTransformerManip.h>

#include <Inventor/SoPath.h>

#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoShape.h>
#include <SmallChange/nodekits/SmAxisDisplayKit.h>
#include <SmallChange/nodekits/SmAxisKit.h>
#include <SmallChange/misc/Init.h>
#include <Inventor/sensors/SoFieldSensor.h> 

#include <vector>
#include "TRootGLU.h"

//#include "OverlayHighlightRenderAction.h"
Bool_t TQtCoinWidget::fgCoinInitialized = kFALSE;

//______________________________________________________________________________
SoGLRenderAction &TQtCoinWidget::BoxHighlightAction()
{
   if (!fBoxHighlightAction) 
      fBoxHighlightAction = new SoBoxHighlightRenderAction;
   return *fBoxHighlightAction;
}
//______________________________________________________________________________
SoGLRenderAction &TQtCoinWidget::LineHighlightAction()
{
   if (!fLineHighlightAction) 
      fLineHighlightAction = new SoLineHighlightRenderAction;
   return *fLineHighlightAction;
}

//______________________________________________________________________________
 static void testCube() {
   // - > 0-th face binded polygon
 glBegin(GL_QUADS);
    float a= 20.0, b = 15.0;
   glNormal3f( -1.000000, 0.000000, 0.000000);
     glVertex3f(-a, -b , -b);
     glVertex3f(-a,  b , -b);
     glVertex3f(-a,  b ,  b);
     glVertex3f(-a, -b ,  b);

 //-- > 1-th face binded polygon
     glNormal3f(0.000000, 1.000000, 0.0000000);
      glVertex3f(-a, b, -b);
      glVertex3f( a, b, -b);
      glVertex3f( a, b,  b);
      glVertex3f(-a, b,  b);
 // -- > 2-th face binded polygon
   glNormal3f( -1.000000, 0.000000, 0.000000);
      glVertex3f(a,  b, -b);
      glVertex3f(a, -b, -b);
      glVertex3f(a, -b,  b);
      glVertex3f(a,  b,  b);
// -- > 3-th face binded polygon
   glNormal3f(0.000000, -1.000000, 0.000000);
      glVertex3f(-a, -b, -b);
      glVertex3f(-a, -b,  b);
      glVertex3f( a, -b,  b);
      glVertex3f( a, -b, -b);
// -- > 4-th face binded polygon
   glNormal3f(0.000000, 0.000000, +1.000000);
       glVertex3f(-a, -b, b);
       glVertex3f(-a,  b, b);
       glVertex3f( a,  b, b);
       glVertex3f( a, -b, b);
 //-- > 5-th face binded polygon
    glNormal3f(0.000000, 0.000000, -1.000000);
       glVertex3f( a, -b, -b);
       glVertex3f( a,  b, -b);
       glVertex3f(-a,  b, -b);
       glVertex3f(-a, -b, -b);
  glEnd();
 }
//______________________________________________________________________________
// Inventor call back function
static void InventorCallback1(void *d, SoAction *action)
{
   printf("static void InventorCallback1\n");
   if (!d) return;
   TQtCoinWidget *currentViewer = (TQtCoinWidget *)d;
   if ( currentViewer ) {
      if (action->isOfType(SoGLRenderAction::getClassTypeId()) )
      {
        // glEnable(GL_LIGHTING);
        SoCacheElement::invalidate(action->getState());
	int max = currentViewer->GetMyGLList1().size();
	printf("static void InventorCallback1 lists count=%i\n", max);
        // testCube();
	for (int i = 0; i < max; i++) glCallList(currentViewer->GetMyGLList1()[i]);
	//gVirtualGL->RunGLList(myGLIst + TPadOpenGLView::kModel);
      }
      //*
      else if (action->isOfType(SoGetBoundingBoxAction::getClassTypeId()) )
      {

         Float_t minBound[3]={-1500,-1500,-1500};
         Float_t maxBound[3]={ 1500, 1500, 1500};

         //currentViewer->GetGLView()->GetPad()->GetView()->GetRange(minBound,maxBound);		// old
	 currentViewer->GetPad()->GetView()->GetRange(minBound,maxBound);				// new
	
	  //printf(" %f %f %f :  %f %f %f \n", minBound[0],minBound[1],minBound[2]
	//		  , maxBound[0],maxBound[1],maxBound[2]);
	  
         if (minBound[0] == maxBound[0]) {
            SoCacheElement::invalidate(action->getState());
         }
         SoGetBoundingBoxAction *boundAction =  (SoGetBoundingBoxAction *)action;
         Float_t min = TMath::Min(TMath::Min(minBound[0],minBound[1]),minBound[2]);
         Float_t max = TMath::Max(TMath::Max(maxBound[0],maxBound[1]),maxBound[2]);
         boundAction->
            extendBy(SbBox3f(min,min,min,max,max,max));

         //boundAction->
         //   extendBy(SbBox3f(minBound[0],minBound[1],minBound[2]
         //   ,maxBound[0],maxBound[1],maxBound[2])
         //      );
             // I had to add the line below into 
             //  SoNode::GLRenderS:780 to supress the annoying warning
             // This is very dirty but I have to do that (Valeri Fine 24.05.2003 fine@bnl.gov)
             //    err =  GL_NO_ERROR;

         const SbVec3f &centerPoint =  boundAction->getBoundingBox().getCenter();
         boundAction->setCenter(centerPoint, false);
         float x,y,z;
         centerPoint.getValue(x,y,z);
         // printf(" new center = %f %f %f \n", x,y,z);
	 
      }
      //*/
   }
}

//______________________________________________________________________________
// Inventor call back function
static void InventorCallback2(void *d, SoAction *action)
{
   if (!d) return;
   TQtCoinWidget *currentViewer = (TQtCoinWidget *)d;
   if ( currentViewer ) {
      if (action->isOfType(SoGLRenderAction::getClassTypeId()) )
      {
        SoCacheElement::invalidate(action->getState());
        //glEnable(GL_LIGHT0); 
        glEnable(GL_LIGHTING);
        //glEnable(GL_COLOR_MATERIAL);

	int max = currentViewer->GetMyGLList2().size();
	printf("static void InventorCallback2 lists count=%i\n", max);
	for (int i = 0; i < max; i++) glCallList(currentViewer->GetMyGLList2()[i]);
      }
   }
}

//______________________________________________________________________________
// Inventor call back function
static void InventorCallback3(void *d, SoAction *action)
{
   printf("static void InventorCallback2\n");
   if (!d) return;
   TQtCoinWidget *currentViewer = (TQtCoinWidget *)d;
   if ( currentViewer ) {
      if (action->isOfType(SoGLRenderAction::getClassTypeId()) )
      {
        SoCacheElement::invalidate(action->getState());
	int max = currentViewer->GetMyGLList3().size();
	for (int i = 0; i < max; i++) glCallList(currentViewer->GetMyGLList3()[i]);
      }
   }
}
static int iframe = 0;
static int ifile = 0;
static QPNGImagePacker *fAnimator = 0;
static QIODevice *fAnimDevice;
//______________________________________________________________________________
// Inventor call back function
static void MovieCallback(void *d, SoAction *action)
{
   if (!d) return;
   TQtCoinWidget *currentViewer = (TQtCoinWidget *)d;
   if ( currentViewer ) {
      if (action->isOfType(SoGLRenderAction::getClassTypeId()) )
      {
        SoCacheElement::invalidate(action->getState());
        QGLWidget *w = (QGLWidget *)currentViewer->GetCoinViewer()->getGLWidget();
        fprintf(stderr,"MovieCallback %s \n",(const char*)QString("file%1.png").arg(iframe+1));
        QImage im =  w->grabFrameBuffer(TRUE); 
//        if (!fAnimator) {
//           fAnimDevice = new  QFile(QString("file%1.png").arg(ifile++));
//           fAnimDevice->open( IO_WriteOnly );           
//           fAnimator = new QPNGImagePacker(fAnimDevice,32,Qt::AutoColor);
//        }
//        fAnimator->packImage(im);iframe++; 
//        if (iframe > 20) { fAnimDevice->flush(); fAnimDevice->close(); delete fAnimator;  fAnimator = 0; delete fAnimDevice;  fAnimDevice = 0;}
        im.save(QString("file%1.png").arg(iframe++),"PNG");
//              QPixmap::grabWidget(w).save(QString("file%1.png").arg(iframe++),"PNG");
      }
   }
}

//static bool g_isManip = false;

//______________________________________________________________________________
static void DeselectCB(void * viewer, SoPath *p) 
{
   // printf("DeselectCB %p %d\n",p,p->getRefCount() );	
	/*
   SoPath * path = new SoPath(*p);
   path->ref();
   path->truncate(path->getLength()-3);
   if (path->getLength() == 0) {
	//printf("!!!Er:path.len = 0\n");
	return;
   }
   SoSeparator * group = (SoSeparator *) path->getTail();
   if (g_isManip) {
	   SoTransformerManip * manip = (SoTransformerManip *) group->getChild(0);
	   if ( manip->isOfType(SoTransformerManip::getClassTypeId()) ) {
	      path->append(manip);
	      manip->replaceManip(path, new SoTransform);
	   }
   }
   path->unref();
	*/
  ((TQtCoinWidget*)(viewer))->Update();
}

//______________________________________________________________________________
static SoPath * PickFilterCB(void * viewer, const SoPickedPoint * pick)
{
   SoPath *selPath = 0;
   SoPath *p = pick->getPath();
	/*
   if (p->getTail()->getTypeId() == SoLineSet::getClassTypeId()          ||
       p->getTail()->getTypeId() == SoIndexedLineSet::getClassTypeId()) {
	// for lines
	((TQtCoinWidget*)(viewer))->SetLineSelection();
   } else {
	// for figures
	((TQtCoinWidget*)(viewer))->SetBoxSelection();
   }
	*/
   int i=0;
   int l = p->getLength();
   if (l > 1) {
      for (i = l - 1; i > 0; i--) {
         SoNode *n = p->getNode(i);
         if (n->getName() == "CoinShapeNode")
            break;
     }
  }
//  SoGroup *thisGroup = (SoGroup *)p->getNode(i);
  TObject3DView *v = (TObject3DView*)p->getNode(i)->getUserData();
 // printf("static SoPath *PickFilterCB l=%d, i=%d %s : root name = %s \n",p->getLength(),i
 //        ,(const char *)p->getNode(i)->getName(),(const char *)v->GetName());
  if (v) {
     TQtCoinWidget *thisViewer = (TQtCoinWidget*)viewer;
     if (v->IsSolid()) thisViewer->SetLineSelection();
      else              thisViewer->SetBoxSelection();
     // Emit signal at once
     if (!thisViewer->WasPicked(v) ) thisViewer->EmitSelectSignal(v);
     selPath = p->copy(0, i);
  }
  // fprintf(stderr,"static SoPath *PickFilterCB path %p\n", selPath);
  return selPath;
}

//______________________________________________________________________________
static void SelectCB(void * viewer, SoPath *p)
{
   // fprintf(stderr, "SelectCB %p %d\n",p,p->getRefCount() );	
	/*
   SoPath * path = new SoPath(*p);
   path->ref();
   path->truncate(path->getLength()-3);
   //printf("SelectCB; %S\n", p->getTail()->getTypeId().getName().getString());
   if (path->getLength() != 0) {
	   TObject3DView * v = (TObject3DView*)(path->getTail()->getUserData());
	   //printf("\tnode->userdata=%p\n", v);
	   ((TQtCoinWidget*)(viewer))->EmitSelectSignal(v);
	   if (g_isManip) {
		   SoSeparator * group = (SoSeparator *) path->getTail();
		   if ( !group->getChild(0)->isOfType(SoTransform::getClassTypeId())) {
		      group->insertChild(new SoTransform, 0);
		   }	
		   SoTransform * transform = (SoTransform *) group->getChild(0);
		   path->append(transform);
		   static SoTransformerManip * manip = 0;
		   // if (!manip) {
		      manip = new SoTransformerManip;
		      manip->ref();
		   // }
		   manip->replaceNode(path);
	   }
   } else {
	//printf("!!!Er:path.len = 0\n");
   }
   path->unref();
   */
   TQtCoinWidget *thisViewer = (TQtCoinWidget*)viewer;
   thisViewer->Update();

    // Popup the object tip

   TObject *selectedObject = thisViewer->GetSelected();
   if ((!thisViewer->WantRootContextMenu()) && selectedObject ) {
      QPoint globalPosition = QCursor::pos();
      QWidget *viewerWidget = thisViewer->GetCoinViewer()->getWidget();
      QPoint cursorPosition = viewerWidget->mapFromGlobal(globalPosition);
      QString tipText =  selectedObject->GetObjectInfo(cursorPosition.x(),cursorPosition.y());
#if QT_VERSION < 0x40000
      QWhatsThis::display(tipText, globalPosition,viewerWidget);
#else
      Q3WhatsThis::display(tipText,globalPosition,viewerWidget);
#endif
   }
}

/*
//______________________________________________________________________________
TQtCoinWidget::TQtCoinWidget(TPadOpenGLView *pad, const char *title,
                       UInt_t width, UInt_t height)
	: TGLViewerImp(pad,title,width,height)
{	
if QT_VERSION < 0x40000
   : QMainWindow(0,"glviewer", Qt::WDestructiveClose)
#else 
   : Q3MainWindow(0,"glviewer", Qt::WDestructiveClose)
#endif 
   , TGLViewerImp(pad,title,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(0),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
 {
   if (pad) {
      TVirtualPad *thisPad = pad->GetPad();
      if (thisPad) {

         // Create the default SnapShot file name and type if any
         const char *fileDir = gSystem->Getenv("SnapShotDirectory");
         if (!(fileDir  && fileDir[0]) && ( gEnv ) ) {
             fileDir  = gEnv->GetValue("Gui.SnapShotDirectory",(const char *)0);
         }
         if (fileDir  && fileDir[0]) {  fSaveFile = fileDir; fSaveFile += "/"; }

         fSaveFile += thisPad->GetName();
         fSaveFile += ".";
         fSaveFile += "jpg";
         QString caption = thisPad->GetTitle();
         caption += ": OpenGL viewer";
         setCaption(caption);
         resize(width, height);
         fGLView = pad;
         CreateViewer(title);
         MakeMenu();
         int parts[] = {43,7,10,39};
         CreateStatusBar(parts,4);
         SetDrawList(0);
         ShowStatusBar();
         show();
      }
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();

}
*/
/*
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TPadOpenGLView *pad, const char *title,
                       Int_t x, Int_t y, UInt_t width, UInt_t height)

}
*/
//______________________________________________________________________________
TQtCoinWidget::TQtCoinWidget(TVirtualPad *pad, const char *title,
                       UInt_t width, UInt_t height)
#if QT_VERSION < 0x40000
   : QMainWindow(0,"coinviewer", Qt::WDestructiveClose)
#else 
   : Q3MainWindow(0,"coinviewer", Qt::WDestructiveClose)
#endif 
   , TGLViewerImp(0,title,width,height)
   , fInventorViewer(0),qt_viewer(0), fRootNode(0)
   , fShapeNode(0),fSelNode(0),myCamera(0),fCamera(0),fAxes(0)
   , fXAxis(0), fYAxis(0), fZAxis(0),fCameraSensor(0),fPickedObject(0)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fPad(pad),fContextMenu(0),fSelectedObject(0)
   , fWantRootContextMenu(kFALSE)
   //,fGLWidget(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   //, fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE)
   , fSnapShotAction(0),fBoxHighlightAction(0),fLineHighlightAction(0)
   , fWantClipPlane(kFALSE), fClipPlaneMan(0), fClipPlane(0)
{
   if ( fPad ) {
	   printf("TQtCoinWidget::TQtCoinWidget begin Pad=%p\n", pad);
       //Create the default SnapShot file name and type if any
      const char *fileDir = gSystem->Getenv("SnapShotDirectory");
      if (!(fileDir  && fileDir[0]) && ( gEnv ) ) {
           fileDir  = gEnv->GetValue("Gui.SnapShotDirectory",(const char *)0);
      }
      if (fileDir  && fileDir[0]) {  fSaveFile = fileDir; fSaveFile += "/"; }
      fSaveFile += fPad->GetName();
      fSaveFile += ".";
      fSaveFile += "jpg";
      
      QString caption = fPad->GetTitle();
      caption += ": Coin viewer";
      setCaption(caption);
      resize(width, height);
      fGLView = 0;
      CreateViewer(title);
      int parts[] = {43,7,10,39};
      CreateStatusBar(parts,4);
      MakeMenu();
      SetDrawList(0);
      show();
   }
   fMaxSnapFileCounter = 2;//CreateSnapShotCounter();
   printf("TQtCoinWidget::TQtCoinWidget end\n");
}
/*
//______________________________________________________________________________
TQtCoinWidget::TQtCoinWidget(TVirtualPad *pad, const char *title,
                       Int_t x, Int_t y, UInt_t width, UInt_t height)
	:TGLViewerImp(0,title,x,y,width,height)
	{
*/
/*
#if QT_VERSION < 0x40000
   : QMainWindow(0,"glviewer",Qt::WDestructiveClose | Qt::WRepaintNoErase | Qt:: WResizeNoErase )
#else 
   : Q3MainWindow(0,"glviewer",Qt::WDestructiveClose | Qt::WNoAutoErase | Qt:: WResizeNoErase )
#endif 
   , TGLViewerImp(0,title,x,y,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(pad),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   ,fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
{
   if (fPad) {
      // Create the default SnapShot file name and type if any
      const char *fileDir = gSystem->Getenv("SnapShotDirectory");
      if (!(fileDir  && fileDir[0]) && ( gEnv ) ) {
         fileDir  = gEnv->GetValue("Gui.SnapShotDirectory",(const char *)0);
      }
      if (fileDir  && fileDir[0]) {  fSaveFile = fileDir; fSaveFile += "/"; }
      fSaveFile += fPad->GetName();
      fSaveFile += ".";
      fSaveFile += "jpg";
      QString caption = fPad->GetTitle();
      caption += ": OpenGL viewer";
      setCaption(caption);

      setGeometry(x, y, width, height);
      fGLView = 0;
      CreateViewer(title);
      MakeMenu();
      int parts[] = {43,7,10,39};
      CreateStatusBar(parts,4);
      SetDrawList(0);
      show();
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();
   
}  

//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TQtGLViewerImp &parent) :
#if QT_VERSION < 0x40000
     QMainWindow(&parent,"glviewerutil", Qt::WDestructiveClose | Qt::WType_TopLevel)
#else 
     Q3MainWindow(&parent,"glviewerutil",Qt::WDestructiveClose | Qt::WType_TopLevel)
#endif 
   , TGLViewerImp(0,"selection",parent.width(),parent.height())
   , fSaveType(parent.fSaveType),fMaxSnapFileCounter(2),fGLWidget(0),fPad(parent.fPad),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kTRUE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
{
   // create a satelite widget
   connect(this,SIGNAL(destroyed() ),&parent, SLOT(DisconnectSelectorWidgetCB()));
   QString caption;
   if (fPad) {
      // Create the default SnapShot file name and type if any
      const char *fileDir = gSystem->Getenv("SnapShotDirectory");
      if (!(fileDir  && fileDir[0]) && ( gEnv ) ) {
         fileDir  = gEnv->GetValue("Gui.SnapShotDirectory",(const char *)0);
      }
      if (fileDir  && fileDir[0]) {  fSaveFile = fileDir; fSaveFile += "/"; }
      fSaveFile += fPad->GetName();
      fSaveFile += ".";
      fSaveFile += "jpg";
      caption = fPad->GetTitle();
   }
   fGLView = 0;
   caption += ": selection viewer";
   setCaption(caption);
   resize(2*parent.width()/3,2*parent.height()/3);
   CreateViewer(parent.GLWidget(),"selection");
   MakeMenu();
   int parts[] = {43,7,10,39};
   CreateStatusBar(parts,4);
   SetDrawList(0);
   show();
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
*/
//______________________________________________________________________________
TQtCoinWidget::~TQtCoinWidget()
{ 
   if (fClipPlaneMan) { fClipPlaneMan->unref(); fClipPlaneMan = 0;}
   if (fAxes)         { fAxes        ->unref(); fAxes         = 0;}
   if (fXAxis)        { fXAxis       ->unref(); fXAxis        = 0;}
   if (fYAxis)        { fYAxis       ->unref(); fYAxis        = 0;}
   if (fZAxis)        { fZAxis       ->unref(); fZAxis        = 0;}
   delete fBoxHighlightAction; fBoxHighlightAction  = 0;
   delete fLineHighlightAction;fLineHighlightAction = 0;
   delete fCameraSensor;       fCameraSensor        = 0;
   if (fRootNode)     { fRootNode    ->unref(); fRootNode     = 0;}
}

//______________________________________________________________________________
void TQtCoinWidget::AddRootChild(ULong_t id)
{
   assert(id);
   printf("TQtCoinWidget::AddRootChild----------------------------------------------------------------  <===\n");
   //fRootNode->addChild(new SoCone);
   fShapeNode->addChild((SoNode*)id);
   
   // Make myCamera see everything.
   fCamera->viewAll(fRootNode, fInventorViewer->getViewportRegion());
}

//______________________________________________________________________________
void TQtCoinWidget::ClearCB()
{
	Clear();
}

//______________________________________________________________________________
void TQtCoinWidget::Clear()
{
	fShapeNode->removeAllChildren();
	/*
	fInventorViewer->setSceneGraph(NULL);
	fInventorViewer->setSceneGraph(NULL);
	fRootNode->unref();
	fRootNode = NULL;
	*/
	/*
     // Clear (remove) all objects from the view
   QWidget *c = centralWidget();
   if (!c) return;
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   glView->clearGLList();
   Update();
	*/
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::CreateStatusBar(Int_t nparts)
{
 //  Create the status bar with "nparts" separate portions
  QStatusBar *thisStatusBar = statusBar();
  Int_t i=0;
  fStatusBar.resize(nparts);
  for (i=0;i<nparts;i++) {
    QLabel *l = new QLabel(thisStatusBar);
    thisStatusBar->addWidget(l,1,TRUE);
    // remember to delete later
    fStatusBar.insert(i,l);  
  }
}
*/

//______________________________________________________________________________
void TQtCoinWidget::CreateStatusBar(Int_t *parts, Int_t nparts)
{
  //  Create the status bar with "nparts" separate portions
  // The initial relative size of each part is defined by "parts" array
/*
  QStatusBar *thisStatusBar = statusBar();
#ifdef WIN32
  thisStatusBar->setSizeGripEnabled(FALSE);
#endif
  // Any number of widgets may be controlled by just
  // one splitter
  QSplitter *split = new QSplitter(thisStatusBar);
  thisStatusBar->addWidget(split,1,FALSE);

  fStatusBar.resize(nparts);
  Int_t iField=0;
  for (iField=0; iField<nparts; iField++) {
    QLabel *infoBox = new QLabel(split);
    infoBox->setIndent(3);
    QSize s = infoBox->size();
    s.setWidth(parts[iField]);
    infoBox->resize(s);

    // remember to delete later
    fStatusBar.insert(iField,infoBox);
  }
  */
}
/*
//______________________________________________________________________________
int TQtCoinWidget::CreateSnapShotCounter()
{
   // Define the number of the snapshot frames based on either
   // "SnapShotFileCounter" environment variable
   //    use: 
   //          setenv SnapShotFileCounter 100
   // to produce 100  different frames in raw
   // or the ROOT parameters (via ".rootrc" file) 
   //
   //   Gui.SnapShotFileCounter 100
   //
   const char *dcounter = gSystem->Getenv("SnapShotFileCounter");
   if (!(dcounter && dcounter[0]) && ( gEnv ) ) {
        dcounter  = gEnv->GetValue("Gui.SnapShotFileCounter","2");
   }
   if (dcounter && dcounter[0]) {
      int count = QString(dcounter).toInt();
      if (count > 2 )  gfDefaultMaxSnapFileCounter = count;
   }
   return gfDefaultMaxSnapFileCounter;
}
*/
//______________________________________________________________________________
TContextMenu &TQtCoinWidget::ContextMenu() 
{
   // Create the TConextMEny if needed and return it
   if (!fContextMenu) 
        fContextMenu = new TContextMenu("3DViewContextMenu");
   return *fContextMenu;
}

/*
//______________________________________________________________________________
void TQtGLViewerImp::DisconnectSelectorWidgetCB()
{
   // [slot] to disconnect the destroyed  "selection" widget
  fSelectedView = 0; 
}

//______________________________________________________________________________
void TQtGLViewerImp::SetStatusText(const char *text, Int_t partidx, Int_t stype)
{  
  // Set Text into the 'npart'-th part of the status bar
  if (Int_t(fStatusBar.size()) > partidx) {
    if (stype >=  0) {
       TColor *rootColor = gROOT->GetColor(stype);
       float rgb[3];
       rootColor->GetRGB(rgb[0],rgb[1],rgb[2]);
       fStatusBar[partidx]->setPaletteForegroundColor(QColor(int(255*rgb[0]),int(255*rgb[1]),int(255*rgb[2])));
    }
    fStatusBar[partidx]->setText(text);
  }
}
//______________________________________________________________________________
void TQtGLViewerImp::ShowStatusBar(Bool_t show)
{
   // Show / Hide the status bar
   
  if (show) statusBar()->show();
  else      statusBar()->hide();
}
*/
//______________________________________________________________________________
 void  TQtCoinWidget::DisconnectPad()
 {
    fPad = 0;
 }
//______________________________________________________________________________
void TQtCoinWidget::SetUpdatesEnabled(const bool&enable)
{   setUpdatesEnabled(enable);                            }

//______________________________________________________________________________
TVirtualPad *TQtCoinWidget::GetPad() 
{
   if (GetGLView()) return GetGLView()->GetPad();
   return fPad;
}
/*
//______________________________________________________________________________
//
// Slots
//______________________________________________________________________________
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectorWidgetCB(bool on)
{
     // Active the separate window to show the selected objects
    fSelectedViewActive =  on;
    CreateSelectionViewer();
}
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectionHighlighCB(bool on)
{
     // Active the separate window to show the selected objects
    fSelectionHighlight  =  on;
}
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectionGlobalCB(bool on)
{
     // Show the selected object on the global coordinate system
    fShowSelectionGlobal =  on;
}
*/
//______________________________________________________________________________
void TQtCoinWidget::AddGLList(unsigned int list, int type)
{
   printf("TQtCoinWidget::AddGLList\n");
   
   flist[type].push_back(list);
	/*
   QWidget *c = centralWidget();
   if (!c) return;   
#ifdef QGLVIEWER
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     switch (type) {
     case 0:
        glView->addGLList(list, TQtGLViewerWidget::kWired);
        break;
     case 1: default:
        glView->addGLList(list, TQtGLViewerWidget::kSolid);
        break;
     case 2:
        glView->addGLList(list, TQtGLViewerWidget::kSelecting);
        break;
     };
#endif
	*/
}

//______________________________________________________________________________
void TQtCoinWidget::RemoveGLList(unsigned int list)
{
	printf("TQtCoinWidget::RemoveGLList\n");
	/*
   QWidget *c = centralWidget();
   if (!c) return;   
#ifdef QGLVIEWER
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     glView->removeGLList(list);
#endif
	*/
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::NewViewer(){
  new TQtGLViewerImp(GetGLView());

*/
//______________________________________________________________________________
void TQtCoinWidget::PrintCB(){
	/*
   QPrinter p;
   QWidget *c = centralWidget();
   if (c && p.setup()) {
      QPainter pnt(&p);
        QGLWidget *glView = (QGLWidget *)c;
        if (glView) pnt.drawImage(0,0,glView->grabFrameBuffer());
      pnt.end();
   }
	*/	
	SoWriteAction 	writeAction;
	writeAction.apply(fRootNode); //writes the entire scene graph to stdout
}

//______________________________________________________________________________
void TQtCoinWidget::CopyCB()
{
	/*
 //  Copy the current x3d view to the system clipboard 
   QWidget *c = centralWidget();
   if (c) { 
      QClipboard *cb = QApplication::clipboard();
      cb->setPixmap(QPixmap::grabWindow(c->winId () )) ;
   }
	*/
}
//______________________________________________________________________________
void TQtCoinWidget::CopyFrameCB()
{
	/*
   // Copy the entire window including the menu and the status bar
   QClipboard *cb = QApplication::clipboard();
   cb->setPixmap(QPixmap::grabWidget(topLevelWidget()));
	*/
}

//______________________________________________________________________________
void TQtCoinWidget::OpenCB()
{ 
   printf("TQtCoinWidget::OpenCB\n");

   QString filter = "WRL File (*.wrl);;IV files (*.iv)";
   QString selectedFilter;
#if QT_VERSION < 0x40000
   QString thatFile = QFileDialog::getOpenFileName(gSystem->WorkingDirectory()
#else 
   QString thatFile = Q3FileDialog::getOpenFileName(gSystem->WorkingDirectory()
#endif 
    , filter, centralWidget(), "Open"
    , "Add graph to coin scene");
	
   const char * fileDecor = thatFile;
     SoInput viewDecor;
     if (!gSystem->AccessPathName(fileDecor) && viewDecor.openFile(fileDecor)) {
        SoSeparator *extraObjects = SoDB::readAll(&viewDecor);
        if (extraObjects) {
	   printf("readings ...\n");
           fShapeNode->addChild(extraObjects);
        }
     }
}
//______________________________________________________________________________
static QString ListOfFilters() 
{
  QString a = "";
  SoOffscreenRenderer r(*(new SbViewportRegion));
  int num = r.getNumWriteFiletypes();

 if (num == 0) {
    (void)fprintf(stdout,
                   "No image formats supported by the "
                  "SoOffscreenRenderer except SGI RGB and Postscript.\n");
 } else {
    for (int i=0; i < num; i++) {
       SbPList extlist;
       SbString fullname, description;
       r.getWriteFiletypeInfo(i, extlist, fullname, description);
       if (i > 0) a+= ";";
       a += fullname.getString(); 
       (void)fprintf(stdout, "%s: %s (extension%s: ",
                      fullname.getString(), description.getString(),
                      extlist.getLength() > 1 ? "s" : "");
         a+= " ( " ;
         for (int j=0; j < extlist.getLength(); j++) {
            if (j>0) a+= ", "; a+= "*."; a+=(const char*) extlist[j];
            (void)fprintf(stdout, "%s%s", j>0 ? ", " : "", (const char*) extlist[j]);
         }
         a += " );";
         (void)fprintf(stdout, ")\n");
    }
  }
  return a;
}
//______________________________________________________________________________
static QStringList ExtensionList(const QString &filter)
{
   // Return the list of the extsntion from the file dialog filter
   QRegExp rx("(\\*\\.\\w+\\b)");
   QStringList extension;
   int pos = 0;
   while ( pos >= 0 ) {
      pos = rx.search(filter,pos);
      if ( pos > -1 ) {
         extension += rx.cap(1);
         pos  += rx.matchedLength();
      }
   }   
   return extension ;
}
//______________________________________________________________________________
void TQtCoinWidget::SaveCB()
{ 
   printf("TQtCoinWidget::SaveCB\n");
   //if (!c) return;
   QString filter = ListOfFilters();
   filter +=";Transparent Img File (*.rgbt);;WRL File (*.wrl);;IV files (*.iv);";

   QString selectedFilter;
#if QT_VERSION < 0x40000
   QString thatFile = QFileDialog::getSaveFileName(gSystem->WorkingDirectory()
#else 
   QString thatFile = Q3FileDialog::getSaveFileName(gSystem->WorkingDirectory()
#endif 
    , filter, centralWidget(), "SaveAs"
    , "Save the current view as"
    , &selectedFilter);
   
   QStringList selectedExtensions = ExtensionList(selectedFilter);
   
   if (thatFile.isEmpty()) return;
   
   QString e = selectedFilter.mid(selectedFilter.find('.') + 1);
   e.remove(')');
//   QFileInfo outFile( thatFile );
//   QString ext = outFile.extenstion(FALSE);
//   if (ext.isEmpty()) 
   if (! thatFile.contains('.')) thatFile += '.';
   if (thatFile.at(thatFile.length()-1) == '.')  thatFile += e;

   printf("selectedFilter = %s\n", selectedFilter.data());
   printf("thatFile = %s\n", thatFile.data());
   printf("e = %s\n", e.data());
   
   if (e == "rgb") {
      SoOffscreenRenderer osr(fInventorViewer->getViewportRegion());
      osr.setComponents(SoOffscreenRenderer::RGB);
      SbBool ok = osr.render(fShapeNode);
      if (!ok) { return; }
      ok = osr.writeToRGB(thatFile);
   } else if (e == "rgbt") {
      SoOffscreenRenderer osr(fInventorViewer->getViewportRegion());
      osr.setComponents(SoOffscreenRenderer::RGB_TRANSPARENCY);
      SbBool ok = osr.render(fShapeNode);
      if (!ok) { return; }
      ok = osr.writeToRGB(thatFile);
   } else if (e == "wrl") {
      printf("Converting...\n");
      SoToVRML2Action tovrml2;
      tovrml2.apply(fShapeNode);
      SoVRMLGroup *newroot = tovrml2.getVRML2SceneGraph();
      newroot->ref();
      printf("Writing...\n");
      SoOutput out;
      out.openFile(thatFile);
      out.setHeaderString("#VRML V2.0 utf8");
      SoWriteAction wra(&out);
      wra.apply(newroot);
      out.closeFile();	
      newroot->unref();
   } else if (e == "ps") {
         //*
#if 0      
      int printerDPI = 400;
      const SbViewportRegion &vp  = fInventorViewer->getViewportRegion();
      const SbVec2s &imagePixSize = vp.getViewportSizePixels();
      SbVec2f imageInches;
      float pixPerInch;

      pixPerInch = SoOffscreenRenderer::getScreenPixelsPerInch();
      imageInches.setValue((float)imagePixSize[0] / pixPerInch,
                           (float)imagePixSize[1] / pixPerInch);

      // The resolution to render the scene for the printer
      // is equal to the size of the image in inches times
      // the printer DPI;
      SbVec2s postScriptRes;
      postScriptRes.setValue((short)(imageInches[0])*printerDPI,
                             (short)(imageInches[1])*printerDPI);

            // Create a viewport to render the scene into.
      SbViewportRegion myViewport;
      myViewport.setWindowSize(postScriptRes);
      myViewport.setPixelsPerInch((float)printerDPI);

      // Render the scene
      SoOffscreenRenderer myRenderer(myViewport);
      if (myRenderer.render(fShapeNode)) 
          myRenderer.writeToPostScript(thatFile);
      //*/	
#else
     SoVectorizePSAction *va = new SoVectorizePSAction;
     if (true) {
        va->setGouraudThreshold(0.1f);
     } else {
        va->setGouraudThreshold(0.0f);
     }
     va->setBackgroundColor(TRUE, SbColor(1.0f, 1.0f, 1.0f));
     SoVectorOutput * out = va->getOutput();
     if (!out->openFile((const char*)thatFile)) {
       fprintf(stderr,"Unable to open %s for writing\n",
              (const char*)thatFile);
     }
     SbVec2s vpsize = fInventorViewer->getViewportRegion().getViewportSizePixels();
     float vpratio = ((float)vpsize[0]) / ((float)vpsize[1]);

     //
     if (vpratio > 1.0f) {
        va->setOrientation(SoVectorizeAction::LANDSCAPE);
        vpratio = 1.0f / vpratio;
     } else {
        va->setOrientation(SoVectorizeAction::PORTRAIT);
     }
     
     const float BORDER = 10.0f;
     
//     va->beginStandardPage(SoVectorizeAction::A4, BORDER);
     va->beginPage (SbVec2f(0,0), SbVec2f(8,10), SoVectorizeAction::INCH);
      
     // try to fill as much "paper" as possible

     // FIXME: consider making getPageSize() public
     //SbVec2f size = va->getPageSize();
     
//     SbVec2f size = SbVec2f(210.0f - BORDER*2.0f,
//                            297.0f - BORDER*2.0f);

     SbVec2f size = SbVec2f(203.0f - BORDER*2.0f,
                            279.0f - BORDER*2.0f);
     
     float pageratio = size[0] / size[1];
     float xsize, ysize;

     if (pageratio < vpratio) {
        xsize = size[0];
        ysize = xsize / vpratio;
     } else {
       ysize = size[1];
       xsize = ysize * vpratio;
     }

     float offx = BORDER + (size[0]-xsize) * 0.5f;
     float offy = BORDER + (size[1]-ysize) * 0.5f;

     va->beginViewport(SbVec2f(offx, offy), SbVec2f(xsize, ysize));
     va->calibrate(fInventorViewer->getViewportRegion() );

     fprintf(stdout,"Vectorizing...");
     fflush(stdout);

     va->apply(fInventorViewer->getSceneManager()->getSceneGraph());
     fprintf(stdout,"Creating postscript file (%s)...", (const char*)thatFile);
     fflush(stdout);
     va->endViewport();
     va->endPage();
     out->closeFile();

     fprintf(stdout,"done\n");
     fflush(stdout);
#endif      
   } else if (e == "iv") {
      printf("Saving in iv format ...\n");
      SoWriteAction myAction;
      myAction.getOutput()->openFile(thatFile);
      myAction.getOutput()->setBinary(FALSE);
      myAction.apply(fShapeNode);
      myAction.getOutput()->closeFile();
   } else {
      //assert(false);
   }
}
//______________________________________________________________________________
void TQtCoinWidget::SaveAsCB()
{ 
/*
   QWidget *c = centralWidget();
   if (!c) return;
#ifndef QGLVIEWER
   QString filter = 
     "Image (";

   QString defExtension[] = {"bmp","C"};

   UInt_t i;
   for (i = 0; i < QImageIO::outputFormats().count(); i++ ) 
   {
      if (i) filter +=',';
      filter += "*.";
      QString str = QString( QImageIO::outputFormats().at( i ) );
      filter += str.lower();
   }
   filter +=");;";

   QString selectedFilter;

#if QT_VERSION < 0x40000
   QString thatFile = QFileDialog::getSaveFileName(gSystem->WorkingDirectory()
#else 
   QString thatFile = Q3FileDialog::getSaveFileName(gSystem->WorkingDirectory()
#endif 
    , filter, centralWidget(), "SaveAs"
    , "Save the current x3d view as"
    , &selectedFilter);

   if (thatFile.isEmpty()) return;
 
   UInt_t nExt = sizeof(defExtension)/sizeof(const char *);
   QString e;
   for (i = 0; i < nExt-1; i++) {
     e = '.'; e += defExtension[i];
     if (selectedFilter.contains(e)) break;
   }

   if (! thatFile.contains('.'))  thatFile += '.';
   if (thatFile.at(thatFile.length()-1) == '.')  thatFile += defExtension[i];

   fSaveFile = (const char *)thatFile;
   QGLWidget *glView = (QGLWidget *)c;
   glView-> grabFrameBuffer().save(fSaveFile.Data(),fSaveType.Data());
#else
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     glView->saveSnapshot(false);
     fSaveFile = (const char *)glView->snapshotFileName( );
#endif
*/
}

//______________________________________________________________________________
void TQtCoinWidget::SaveSnapShot(bool)
{
	/*
#ifdef QGLVIEWER
//  QString filename(fSaveFile.Data());
//  glView->saveSnapshot("STAR",true);
    if (fSaveFile.IsNull()) {
       SaveAsCB();
    } else {
       // raise the widget
       QWidget *c = centralWidget();
       TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
       TVirtualPad *thisPad= GetPad();
       QString footer(thisPad->GetTitle());
       glView->setFooter(footer);
       
       // raise();
       
       glView->saveSnapshot(true,true);
       if (fMaxSnapFileCounter <= 2) {
          SaveHtml(glView->snapshotCounter()-1);
          float x,y,z;
          if (glView->RotationAxisAngle(x,y,z)< 0.02) {
             CopyFile(QString(fSaveFile.Data()),glView->snapshotCounter()-1);
          }
       }
       if (glView->snapshotCounter() ==  fMaxSnapFileCounter) glView->setSnapshotCounter(0);
   }
#endif
*/
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::CopyFile(const QString &fileName2Copy,Int_t counter)
{
  QFileInfo infoOldFile(fileName2Copy);
  QString newName = infoOldFile.dirPath() + "/" + infoOldFile.baseName(TRUE) +
  "_S."+infoOldFile.extension(FALSE); 
  QFileInfo infoNewFile(newName);

QString shellCommand;
#ifndef WIN32  
   shellCommand = "cd " + infoOldFile.dirPath(true)  + " && " +
                  "cp " + infoOldFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoOldFile.extension(FALSE)
                       + "   " + infoNewFile.baseName(TRUE) + "-000" + QString::number(counter) + "."
                         + infoNewFile.extension(FALSE);
#else
   shellCommand = 
                 "copy " + infoOldFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoOldFile.extension(FALSE)
                         + "   " + infoNewFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoNewFile.extension(FALSE);
#endif
   gSystem->Exec((const char*) shellCommand);
//   fprintf(stderr," ==Copy==  %s \n", (const char*) shellCommand);

   SaveHtml(newName,counter);
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveHtml(Int_t counter)
{
   if (fSaveFile.IsNull())  SaveAsCB();
   if (!fSaveFile.IsNull()) {
     QString f(fSaveFile.Data());
     SaveHtml(f,counter);
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveHtml(QString &saveFile, Int_t counter)
{
#if 0
   if (fSaveFile.IsNull()) {
       SaveAsCB();
   }
   if (fSaveFile.IsNull()) return;
   
   QFileInfo info(fSaveFile.Data());
#else
   if (saveFile.isEmpty()) return;
   
   QFileInfo info(saveFile);
#endif   
   QString htmlFile(  info.dirPath(true) + "/" + info.baseName(TRUE) + "-000" +
                      QString::number(counter) +".html");
#ifdef GENERATE_HTML
   TVirtualPad *thisPad= GetPad();
   QString caption = thisPad->GetTitle();
   FILE *f = fopen((const char*)htmlFile, "w+");
   if (f) {
   QTextOStream(f) << "<html>"   << endl; 
   QTextOStream(f) << "<title>"  << endl;
   QTextOStream(f) <<  caption << endl;
//   QTextOStream(f) <<  caption() << endl;
   QTextOStream(f) << "</title>" << endl;
   QTextOStream(f) << "<head>"   << endl;
   QTextOStream(f) << "<meta http-equiv=\"REFRESH\" content=\"15\">" << endl;
   QTextOStream(f) << "</head>"  << endl;
   QTextOStream(f) << "<body>"   << endl;
   QTextOStream(f) << "<center>" << endl;
   QTextOStream(f) << "<H2> <a href=\"http://www.star.bnl.gov\">STAR@rhic</a></H2><br>" << endl;
//   QTextOStream(f) << "<H3>" << caption() << "</H3><br><hr><br>"   << endl;
   QTextOStream(f) << "<H3>" << caption << "</H3><br><hr><br>"   << endl;
   QTextOStream(f) << "<img src=\"" << info.baseName(TRUE) << "-000" + 
     QString::number(counter) + "." <<info.extension(FALSE)  << "\">" << endl;
//     QString::number(counter) + "." <<info.extension(FALSE)  << "\" width=100%>" << endl;
   QTextOStream(f) << "</center>"<< endl;
   QTextOStream(f) << "</body>"  << endl;
   QTextOStream(f) << "</html>"  << endl;
   fflush(f);
   fclose(f);
#ifndef WIN32  
   QString shellCommand =  "cd " + info.dirPath(true)  + " && " 
                         + "mv   " + info.baseName(TRUE) + "-000" + QString::number(counter) +".html "
                         + info.baseName(TRUE) + ".html";
#else
   QString shellCommand =  "cd  " + info.dirPath(true)  + " && " 
                         + "ren " + info.baseName(TRUE) + "-000" + QString::number(counter) +".html "
                                  + info.baseName(TRUE) + ".html";
#endif                         
#else
   QString shellCommand;
   QFileInfo html(htmlFile);
   if (html.exists() && html.isReadable() ) {
#ifndef WIN32
           shellCommand =  "cd " + info.dirPath(true)  + " && " 
                         + "cp " + htmlFile   + " "
                                 + "." + info.baseName(TRUE) + ".html && "
                         + "mv " + "." + info.baseName(TRUE) + ".html " + info.baseName(TRUE) + ".html";
#else
          shellCommand =   "cd  " + info.dirPath(true)  + " && "
                         + "copy "+ htmlFile            + "   "
                                  + "." + info.baseName(TRUE) + ".html && "
                         + "ren  "+ "." + info.baseName(TRUE) + ".html " + info.baseName(TRUE) + ".html";
#endif
   }
#endif
    if (!shellCommand.isEmpty())  gSystem->Exec((const char*) shellCommand);
    // fprintf(stderr," ***  %s \n", (const char*) shellCommand);
#ifdef GENERATE_HTML
   } else {
      char buffer[100];
      sprintf(buffer,"TQtGLViewerImp::SaveHtml file %s", (const char*)htmlFile);
      perror(buffer);
      assert(0);
   }
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SelectEventCB(bool on)
{
    // Toggle the widget the "wried object selecction mode
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (glView) glView->SetWiredSelectable(on);
}
//______________________________________________________________________________
void TQtGLViewerImp::SelectDetectorCB(bool on)
{
   // Toggle the widget the "wried object selecction mode
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (glView) glView->SetSolidSelectable(on);
}
*/

//______________________________________________________________________________
void TQtCoinWidget::SnapShotSaveCB(bool on)
{  
	/*
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   // Adjust the menu indicator if any
   if (fSnapShotAction) {
      bool snapStatus = fSnapShotAction->isOn();
      if (snapStatus != on ) {
         blockSignals (true);
         fSnapShotAction->setOn(on);
         blockSignals (false);
      }
   }
   if (on) {
         // fGLWidget->resize(720, 576); // PAL DV format (use 720x480 for NTSC DV)
       raise();
       connect(glView, SIGNAL(drawFinished(bool)), this, SLOT(SaveSnapShot(bool)));
    } else {
       disconnect(glView, SIGNAL(drawFinished(bool)), this, SLOT(SaveSnapShot(bool)));
    }
	*/
}

//______________________________________________________________________________
void TQtCoinWidget::SynchTPadCB(bool on)
{  
    //SetPadSynchronize(on);
}

//______________________________________________________________________________
void TQtCoinWidget::ShowFrameAxisCB(bool on)
{  
   if (on) {
      if (!fXAxis) { fXAxis = new SmAxisKit; fXAxis->ref(); }
      
      SoGetBoundingBoxAction ba(fInventorViewer->getViewportRegion());
      ba.apply(fShapeNode);
   
      SbBox3f box = ba.getBoundingBox();
      fXAxis->axisRange.setValue(box.getMin()[0], box.getMax()[0]);
      fXAxis->axisName = "X";
      SoSeparator *as = new SoSeparator; as->setName("MainAxices");
       as->addChild(fXAxis);
      fShapeNode->insertChild(as, 0);
   }
/*
#ifdef QGLVIEWER
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (on) 
      glView->SetFrameAxisFactor(5.0);
   else 
      glView->SetFrameAxisFactor(-1);
   glView->update();
#endif
   */
}

//______________________________________________________________________________
void TQtCoinWidget::ShowLightsCB(bool on)
{  
	/*
#ifdef QGLVIEWER
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   glView->setDrawLight(on);glView->update();
#endif
	*/
}

//______________________________________________________________________________
void TQtCoinWidget::WantRootContextMenuCB(bool on)
{
  // Create "ROOT Context menu" otherwise use the QGLViewer "right mouse click"
  fWantRootContextMenu = on; 
}

//______________________________________________________________________________
void TQtCoinWidget::AboutCB()
{ 
   QMessageBox::aboutQt(0);
   QString rootVersion = "ROOT ";
   rootVersion += gROOT->GetVersion();
   rootVersion += "with Qt interface";
   QMessageBox::about(0,rootVersion,"ROOT Qt interface Coin Viewer 2006 Zubanov Alexei AZubanov@gmail.com");
}

//______________________________________________________________________________
void TQtCoinWidget::HelpCB()
{
	/*
   // Show TGLWidget command key values
#ifndef QGLVIEWER
   TQtGLWidget *c = dynamic_cast<TQtGLWidget *>(centralWidget());
   if (c) c->ShowHelp();
#else
   TQtGLViewerWidget *c = dynamic_cast<TQtGLViewerWidget *>(centralWidget());
   if (c) c->help();
#endif
   */
}
//______________________________________________________________________________
static void cameraChangeCB(void *data, SoSensor *)
{
   // Callback  that reports whenever the viewer's orientation change
  TQtCoinWidget *viewer = (TQtCoinWidget *) data;
  SoCamera *camera = viewer->GetCamera();
  if (camera) {
     SmAxisDisplayKit *axis = viewer->GetAxis();
     if (axis) {
        axis->orientation = camera->orientation;
     }
  }
}
//______________________________________________________________________________
void TQtCoinWidget::CreateViewer(const char *name)
{
   printf("TQtCoinWidget::CreateViewer\n");

   connect(this, SIGNAL(ObjectSelected(TObject*, const QPoint &)), &this->Signals(), SIGNAL(ObjectSelected(TObject *, const QPoint&)));
   if ( !fgCoinInitialized) { 
      SoQt::init(this); 
      SoHardCopy::init();
 #ifdef __SMALLCHANGE__ 
      smallchange_init(); 
#endif
     fgCoinInitialized = kTRUE;
   }
    // 
    // fInventorViewer
    //      | 
    //  fRootNode ---+
    //               | fSelNode
    //               |----------+
    //               |          |  fShapeNode
    //               |          |-------------+
    //               | SelectCB               | ShapeHints
    //               |---------               |------------
    //               |                        |
    //               |DeselectCB              |  fileNode
    //               |----------              |------------
    //               |
    //               |PickFilterCB    
    //               |---------- 
    //               |
    //               | MovieCB    
    //               |---------- 
    //               |
    //               | fAxes    
    //               |---------- 
    // 
   //OverlayHighlightRenderAction::initClass();	
	//*
   fRootNode = new SoSeparator;
   fRootNode->setName("RootNode");
   fRootNode->ref();	
	
   fSelNode = new SoSelection;
   fSelNode->setName("SelectionNode");
   fRootNode->addChild(fSelNode);

   fShapeNode = new SoSeparator;
   fShapeNode->setName("ShapesNode");
   fSelNode->addChild(fShapeNode);
 // ---------------------------------------------------------------------
 // void SoSeparator::setNumRenderCaches ( const int  howmany ) [static] 
 // ---------------------------------------------------------------------
 // Set the maximum number of caches that SoSeparator nodes may allocate
 // for render caching. This is a global value which will be used for all
 // SoSeparator nodes, but the value indicate the maximum number per
 // SoSeparator node. More caches might give better performance, but will
 //  use more memory. The built-in default value is 2.
 //
 // The value can also be changed globally by setting the host system's 
 // environment variable IV_SEPARATOR_MAX_CACHES to the wanted number.
 // This is primarily meant as an aid during debugging, to make it easy to 
 // turn off rendercaching completely (by setting "IV_SEPARATOR_MAX_CACHES=0")
 // without having to change any application code.
 //

	SoShapeHints * sh = new SoShapeHints;
	sh->vertexOrdering = SoShapeHints::CLOCKWISE;
	sh->shapeType      = SoShapeHints::SOLID;
	sh->faceType       = SoShapeHints::CONVEX;
   //sh->shapeType = SoShapeHints::UNKNOWN_SHAPE_TYPE;
	//sh->faceType = SoShapeHints::UNKNOWN_FACE_TYPE;
	fShapeNode->addChild(sh);	
    
	//*/
   //fRootNode = new SoSelection;

   //SoMaterial *myMaterial = new SoMaterial;
   //fRootNode->addChild(myCamera);
   //fRootNode->addChild(new SoDirectionalLight);
   //myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);   // Red
   //fRootNode->addChild(myMaterial);
   //fRootNode->addChild(new SoCone);
   //SoSeparator * fWNode = new SoSeparator;

	// old GLFactory
	/*
   SoCallback * cb1 = new SoCallback;
   SoCallback * cb2 = new SoCallback;
   SoCallback * cb3 = new SoCallback;
   cb1->setCallback(InventorCallback1, this);
   cb2->setCallback(InventorCallback2, this);
   cb3->setCallback(InventorCallback3, this);

   SoSeparator * s1 = new SoSeparator;
   SoSeparator * s2 = new SoSeparator;
   SoSeparator * s3 = new SoSeparator;
   s1->addChild(cb1);
   //s2->addChild(new SoShape);
   s2->addChild(cb2);
   s3->addChild(cb3);

   fRootNode->addChild(s1);		// wired
   fRootNode->addChild(s2);		// solid
   fRootNode->addChild(s3);		// selecting
   
   SoDrawStyle *wireStyle;
   wireStyle = new SoDrawStyle;
   wireStyle->style = SoDrawStyle::LINES;
   s1->insertChild(wireStyle, 0);
	*/
   /*
      QMainWindow       *fMainWidget;
      fMainWidget = new QMainWindow(0,"Coin3dViewer",Qt::WDestructiveClose|Qt::WType_TopLevel);
      //connect(fMainWidget,SIGNAL(destroyed()),this,SLOT(Disconnect()));
      QFrame *glFrame = new QFrame(fMainWidget);
      fMainWidget->setCentralWidget (glFrame);
      qt_viewer = new SoQtExaminerViewer((QWidget*)glFrame);   
      qt_viewer->setSceneGraph(fRootNode);
      setCentralWidget(fInventorViewer);
      */
   
   
   fSelNode->addSelectionCallback(SelectCB, this); 		//!
   fSelNode->addDeselectionCallback(DeselectCB, this); 		//!
   fSelNode->setPickFilterCallback(PickFilterCB, this); 		//!
   
   QFrame *glFrame = new QFrame(this);
   setCentralWidget (glFrame);
   QVBoxLayout *l  = new QVBoxLayout(glFrame);
   fInventorViewer = new SoQtExaminerViewer(glFrame);
   l->addWidget(fInventorViewer->getWidget());
   fInventorViewer->setSceneGraph(fRootNode);
   fInventorViewer->setTransparencyType(SoGLRenderAction::NONE);

   fCamera = fInventorViewer->getCamera(); 
#if 0   
   SoCallback * movie = new SoCallback;
//    SoSeparator *mv    = new SoSeparator;
   movie->setCallback(MovieCallback, this);
   fRootNode->addChild(movie);
#endif   
   
   //  Pick the background color from pad
   SetBackgroundColor(fPad->GetFillColor());

   connect(this,SIGNAL(ObjectSelected(TObject*,const QPoint &)),this,SLOT( ShowObjectInfo(TObject *, const QPoint&)));
}

//______________________________________________________________________________
void TQtCoinWidget::EmitSelectSignal(TObject3DView * view)
{
   static QPoint mousePosition;

   mousePosition = fInventorViewer->getWidget()->mapFromGlobal ( QCursor::pos());
   if (view) {
      TObject3DView  *parent = (TObject3DView  *)view->GetParent();
      TObject *obj = parent->GetObject();
      fSelectedObject = obj;
      if (obj) {
         //  printf("\tTQtCoinWidget::EmitSelectSignal view = %p, obj = %p; obj name %s \n", view, obj, (const char*)obj->GetName());
         emit ObjectSelected(obj,  mousePosition);
      }
   }
}

//______________________________________________________________________________
void TQtCoinWidget::SetBoxSelection()
{
 // BoxHighlightAction().setTransparencyType(fInventorViewer->getTransparencyType());
 // fInventorViewer->setGLRenderAction( &BoxHighlightAction());
}

//______________________________________________________________________________
void TQtCoinWidget::SetLineSelection()
{
   LineHighlightAction().setTransparencyType(fInventorViewer->getTransparencyType());
	fInventorViewer->setGLRenderAction( &LineHighlightAction());
}

/*
//______________________________________________________________________________
void TQtGLViewerImp::CreateViewer(QGLWidget *share, const char *name)
{
   // Create satellite viewe to share the same GL lists
   if (!fGLWidget) {
      fGLWidget = new TQtGLViewerWidget( this,name,share );
      TQtGLViewerWidget *glw = (TQtGLViewerWidget *)fGLWidget;
#if 0      
      glw->setSceneCenter(((TQtGLViewerWidget *)share)->sceneCenter());
      glw->setSceneRadius(((TQtGLViewerWidget *)share)->sceneRadius());
      glw->setBackgroundColor(((TQtGLViewerWidget *)share)->backgroundColor());
#endif      
      glw->makeCurrent();
      glw->setSceneCenter(((TQtGLViewerWidget *)share)->sceneCenter());
      glw->setSceneRadius(((TQtGLViewerWidget *)share)->sceneRadius());
      glw->setBackgroundColor(((TQtGLViewerWidget *)share)->backgroundColor());

      setCentralWidget (fGLWidget);
      glw->setSnapshotFileName  (fSaveFile.Data());
      connect(fGLWidget,SIGNAL(objectSelected(TObject*,const QPoint &)),this,SLOT( ShowObjectInfo(TObject *, const QPoint&)));
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::MakeCurrent() 
{
#ifdef QGLVIEWER
   fGLWidget->makeCurrent();
#endif
}
*/
//______________________________________________________________________________
void TQtCoinWidget::MakeMenu()
{
   // Create a "save" action
#if QT_VERSION < 0x40000
   QAction *saveAction =  new QAction("Save", "&Save", CTRL+Key_S, this, "save" );
#else 
   Q3Action *saveAction =  new Q3Action("Save", "&Save", Qt::CTRL+Qt::Key_S, this, "save" );
#endif 
   connect ( saveAction, SIGNAL( activated() ) , this, SLOT( SaveCB() ) );

   const char * saveText = "<p><img source=\"save\"> "
                "Click this button to save a <em>3D image</em>to the current image file. <br>"
                "You can also select the <b>Save</b> command "
                "from the <b>File</b> menu.</p>";
   saveAction->setWhatsThis( saveText );

   // Create a "save as" action
#if QT_VERSION < 0x40000
   QAction *saveAsAction =  new QAction("SaveAs", "Save As", CTRL+Key_A, this, "saveas" );
#else 
   Q3Action *saveAsAction =  new Q3Action("SaveAs", "Save As", Qt::CTRL+Qt::Key_A, this, "saveas" );
#endif 
   connect ( saveAsAction, SIGNAL( activated() ) , this, SLOT( SaveAsCB() ) );

   const char * saveAsText = "<p><img source=\"save\"> "
                "Click this button to select file and save a <em>3D image</em>there. <br>"
                "You can also select the <b>Save As</b> command "
                "from the <b>File</b> menu.</p>";
   saveAsAction->setWhatsThis( saveAsText );
 
    // Create a "open" action
#if QT_VERSION < 0x40000
   QAction *openAction =  new QAction("Open", "Open", CTRL+Key_O, this, "open" );
#else 
   Q3Action *saveAsAction =  new Q3Action("Open", "Open", Qt::CTRL+Qt::Key_O, this, "open" );
#endif 
   connect ( openAction, SIGNAL( activated() ) , this, SLOT( OpenCB() ) );

   const char * openText = "<p><img source=\"save\"> "
                "Click this button to select file and open a <em>3D image</em>there. <br>"
                "You can also select the <b>Open</b> command "
                "from the <b>File</b> menu.</p>";
   openAction->setWhatsThis( openText );
 
   // Create a "save as" action
#if QT_VERSION < 0x40000
   fSnapShotAction  =  new QAction("snapShot", "SnapShotSave", CTRL+Key_O, this, "snapshot" );
   connect ( fSnapShotAction, SIGNAL( toggled(bool) ) , this, SLOT( SnapShotSaveCB(bool) ) );
#else 
   fSnapShotAction  =  new Q3Action("snapShot", "SnapShotSave", Qt::CTRL+Qt::Key_O, this, "snapshot" );
#endif 
   connect ( fSnapShotAction, SIGNAL( toggled(bool) ) , this, SLOT( SnapShotSaveCB(bool) ) );

   const char * snapShotText = "<p><img source=\"snapshot\"> "
                "Click this button to save the image each time the frame is updated";
   fSnapShotAction->setWhatsThis( snapShotText );
   fSnapShotAction->setToggleAction(true);

   // Create a "print" action
#if QT_VERSION < 0x40000
   QAction *printAction =  new QAction("Print", "&Print graph in ctout", CTRL+Key_P, this, "print" );
#else 
   Q3Action *printAction =  new Q3Action("Print", "&Print", Qt::CTRL+Qt::Key_P, this, "print" );
#endif 
   connect ( printAction, SIGNAL( activated() ) , this, SLOT( PrintCB() ) );

   const char * printText = "<p><img source=\"print\"> "
                "Click this button to print a <em>3D image</em>. <br>"
                "You can also select the <b>Print</b> command "
                "from the <b>File</b> menu.</p>";
   printAction->setWhatsThis( printText );

   // Create a "clear scene" action
#if QT_VERSION < 0x40000
   QAction *clearAction =  new QAction("Print", "&Clear Scene", CTRL+Key_C, this, "clear" );
#else 
   Q3Action *clearAction =  new Q3Action("Print", "&Clear", Qt::CTRL+Qt::Key_C, this, "clear" );
#endif 
   connect ( clearAction, SIGNAL( activated() ) , this, SLOT( ClearCB() ) );

   const char * clearText = "<p><img source=\"print\"> "
                "Click this button to clear a <em>3D image</em>. <br>"
                "You can also select the <b>Clear</b> command "
                "from the <b>File</b> menu.</p>";
   clearAction->setWhatsThis( clearText );

   // Create a "copy" action
#if QT_VERSION < 0x40000
   QAction *copyAction =  new QAction("Copy", "&Copy", CTRL+Key_C, this, "copy" );
#else 
   Q3Action *copyAction =  new Q3Action("Copy", "&Copy", Qt::CTRL+Qt::Key_C, this, "copy" );
#endif 
   connect ( copyAction, SIGNAL( activated() ) , this, SLOT( CopyCB() ) );

   const char * copyText = "<p><img source=\"copy\"> "
                "Click this button to copy a <em>3D image</em>to the system clipborad. <br>"
                "You can also select the <b>Copy</b> command "
                "from the <b>Edit</b> menu.</p>";
   copyAction->setWhatsThis( copyText );
 
    // Create a "copy frame" action
#if QT_VERSION < 0x40000
   QAction *copyFrameAction =  new QAction("Frame", "Copy &Frame", CTRL+Key_F, this, "frame" );
#else 
   Q3Action *copyFrameAction =  new Q3Action("Frame", "Copy &Frame", Qt::CTRL+Qt::Key_F, this, "frame" );
#endif 
   connect ( copyFrameAction, SIGNAL( activated() ) , this, SLOT( CopyFrameCB() ) );
   const char * copyFrameText = "<p><img source=\"frame\"> "
                "Click this button to copy a <em>tge frame of the 3D image</em>to the system clipborad. <br>"
                "You can also select the <b>Copy Frame</b> command "
                "from the <b>Edit</b> menu.</p>";
   copyFrameAction->setWhatsThis( copyFrameText );

   // Create "close" action
#if QT_VERSION < 0x40000
   QAction *fileCloseAction = new QAction( "Close", "&Close", Qt::ALT+Qt::Key_F4, this,
      "close" );
#else
   Q3Action *fileCloseAction = new Q3Action( "Close", "&Close", Qt::ALT+Qt::Key_F4, this,
      "close" );
#endif
   connect ( fileCloseAction, SIGNAL( activated() ) , this,  SLOT( close() ) );

   // Synchronize TPad rotation 
   
#if QT_VERSION < 0x40000
   QAction *synchAction =  new QAction("TPadSynch", "Synchromize with TPad", CTRL+Key_I, this, "synch" );
#else 
   Q3Action *synchAction =  new Q3Action("TPadSynch", "Synchromize with TPad", Qt::CTRL+Qt::Key_I, this, "synch" );
#endif 
   connect ( synchAction, SIGNAL( toggled(bool) ) , this, SLOT( SynchTPadCB(bool)  ) );
   const char * synchText = "<p><img source=\"frame\"> "
                "Select this option if your want the OpenGL view follows the <b>TPad</B> rotation";
   synchAction->setToggleAction(true);
   synchAction->setWhatsThis( synchText );

   // Show frame axis
   
#if QT_VERSION < 0x40000
   QAction *showFrameAxisAction =  new QAction("Frame3DAxis", "Show Frame axis", CTRL+Key_1, this, "frameaxis" );
#else 
   Q3Action *showFrameAxisAction =  new Q3Action("Frame3DAxis", "Show Frame axis", Qt::CTRL+Qt::Key_1, this, "frameaxis" );
#endif 
   connect ( showFrameAxisAction, SIGNAL( toggled(bool) ) , this, SLOT( ShowFrameAxisCB(bool)  ) );
   const char *showFrameAxisText = "Show the ROOT 3D object axis";
   showFrameAxisAction->setToggleAction(true);
   showFrameAxisAction->setWhatsThis( showFrameAxisText);

   // Show frame axis
   
#if QT_VERSION < 0x40000
   QAction *showSmallAxesAction =  new QAction("Small3DAxes", "Show \"small\" axes", CTRL+Key_2, this, "smallaxes" );
#else 
   Q3Action *showSmallAxesAction =  new Q3Action("Small3DAxes", "Show \"small\" axes", Qt::CTRL+Qt::Key_2, this, "smallaxes" );
#endif 
   connect ( showSmallAxesAction, SIGNAL( toggled(bool) ) , this, SLOT( SmallAxesActionCB(bool)  ) );
   const char *showSmallAxesText = "Show the  small 3D axes at the bottom right corner of the screen. Can slow down the rendering !!!";
   showSmallAxesAction->setToggleAction(true);
   showSmallAxesAction->setWhatsThis( showSmallAxesText);

      // Edit ClipPlane 
   
#if QT_VERSION < 0x40000
   QAction *editClipPlaneAction  =  new QAction("clipPlane", "Edit the Clip Plane", CTRL+Key_9, this, "clipplane" );
#else 
   Q3Action *editClipPlaneAction =  new Q3Action("clipPlane", "Edit the Clip Plane", Qt::CTRL+Qt::Key_9, this, "clipplane " );
#endif 
   connect ( editClipPlaneAction, SIGNAL( toggled(bool) ) , this, SLOT( FrameAxisActionCB(bool)  ) );
   const char *editClipPlaneText = "Activate Clip Plane manipulator";
   editClipPlaneAction->setToggleAction(true);
   showFrameAxisAction->setWhatsThis( editClipPlaneText);

#if QT_VERSION < 0x40000
   QAction *showLightsAction =  new QAction("GLLights", "Show &light", CTRL+Key_L, this, "gllight" );
#else 
   Q3Action *showLightsAction =  new Q3Action("GLLights", "Show &light", Qt::CTRL+Qt::Key_L, this, "gllight" );
#endif 
   connect ( showLightsAction, SIGNAL( toggled(bool) ) , this, SLOT( ShowLightsCB(bool)  ) );
   const char * showLightsText = "<p><img source=\"frame\"> "
                "Show the light source to debug the code";
   showLightsAction->setToggleAction(true);
   showLightsAction->setWhatsThis( showLightsText );
   /*
   // Create a "Event selectable" action
#if QT_VERSION < 0x40000
   QAction *selectEventAction =  new QAction("Event", "Select Event", CTRL+Key_E, this, "event" );
#else 
   Q3Action *selectEventAction =  new Q3Action("Event", "Select Event", Qt::CTRL+Qt::Key_E, this, "event" );
#endif 
   connect ( selectEventAction, SIGNAL( toggled(bool) ) , this, SLOT( SelectEventCB(bool) ) );
   const char * selectEventText = "Turn this option on to be able to select the <b>event</b> (tracks and hits)  and similar \"wired\" object";
   selectEventAction->setToggleAction(true);
   selectEventAction->setWhatsThis( selectEventText);
   
   // Create a "Detector selectable" action
#if QT_VERSION < 0x40000
   QAction *selectDetectorAction =  new QAction("Detector", "Select Detector", CTRL+Key_D, this, "detector" );
#else 
   Q3Action *selectDetectorAction =  new Q3Action("Detector", "Select Detector", Qt::CTRL+Qt::Key_D, this, "detector" );
#endif 
   connect ( selectDetectorAction, SIGNAL( toggled(bool)  ) , this, SLOT( SelectDetectorCB(bool) ) );
   const char * selectDetectorText = "Turn this option on to be able to select the <b>detector</b> (solid) objects";
   selectDetectorAction->setWhatsThis(  selectDetectorText);
   selectDetectorAction->setToggleAction(true);

   // Create a "Detector selectable" action
#if QT_VERSION < 0x40000
   QAction *viewSelectionAction =  new QAction("Selection", "Show the selected object", CTRL+Key_T, this, "selection" );
#else 
   Q3Action *viewSelectionAction =  new Q3Action("Selection", "Show the selected object", Qt::CTRL+Qt::Key_T, this, "selection" );
#endif 
   connect ( viewSelectionAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectorWidgetCB(bool) ) );
   const char * viewSelectionActionText = "Turn this option on to see the selected object with the dedicted view";
   viewSelectionAction->setWhatsThis( viewSelectionActionText );
   viewSelectionAction->setToggleAction(true);

   // Show  the "selected object" with the separate widget using the global coordinate
#if QT_VERSION < 0x40000
   QAction *viewSelectionGlobalAction =  new QAction("SelectionGlobal", "Show the selected object in global system", CTRL+Key_I, this, "selectionglobal" );
#else 
   Q3Action *viewSelectionGlobalAction =  new Q3Action("SelectionGlobal", "Show the selected object in global system", Qt::CTRL+Qt::Key_I, this, "selectionglobal" );
#endif 
   connect ( viewSelectionGlobalAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectionGlobalCB(bool) ) );
   connect ( viewSelectionAction, SIGNAL( toggled(bool)  ), viewSelectionGlobalAction, SLOT( setEnabled(bool) ) );
   const char * viewSelectionGlobalActionText = "Turn this option on to show the selected object in the global coordinate system";
   viewSelectionGlobalAction->setWhatsThis( viewSelectionGlobalActionText );
   viewSelectionGlobalAction->setToggleAction(true);

   // Create a "Highlight the selected object" action
#if QT_VERSION < 0x40000
   QAction *viewSelectionHighlightAction =  new QAction("SelectionHighLight", "Highlight the selected object", CTRL+Key_I, this, "selectionhighlight" );
#else 
   Q3Action *viewSelectionHighlightAction =  new Q3Action("SelectionHighLight", "Highlight the selected object", Qt::CTRL+Qt::Key_I, this, "selectionhighlight" );
#endif 
   connect ( viewSelectionHighlightAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectionHighlighCB(bool) ) );
   const char * viewSelectionHighlightActionText = "Turn this option on to highlight the selected object";
   viewSelectionHighlightAction->setWhatsThis( viewSelectionHighlightActionText );
   viewSelectionHighlightAction->setToggleAction(true);
 */
   // Create a "Context Menu for  the selected object" action
#if QT_VERSION < 0x40000
   QAction *viewContextMenuAction =  new QAction("ContexteMenu", "Context menu", CTRL+Key_I, this, "contextmenu" );
#else 
   Q3Action *viewContextMenuAction =  new Q3Action("ContexteMenu", "Context menu", Qt::CTRL+Qt::Key_I, this, "contextmenu" );
#endif 
   connect ( viewContextMenuAction, SIGNAL( toggled(bool)  ) , this, SLOT( WantRootContextMenuCB(bool) ) );
   const char * viewContextMenuActionText  = "Show the ROOT context menu for the selected ROOT object";
   viewContextMenuAction->setWhatsThis( viewContextMenuActionText );
   viewContextMenuAction->setToggleAction(true);

   QMenuBar   *mainMenu = menuBar();

   // -- populate the menu bar
#if QT_VERSION < 0x40000
      QPopupMenu *fileMenu      = new QPopupMenu();
#else 
      Q3PopupMenu *fileMenu      = new Q3PopupMenu();
#endif 
      mainMenu->insertItem("&File",fileMenu);
 /*
#if QT_VERSION < 0x40000
      QPopupMenu *editMenu      = new QPopupMenu();
#else 
      Q3PopupMenu *editMenu      = new Q3PopupMenu();
#endif 
      mainMenu->insertItem("&Edit",editMenu);
*/

#if QT_VERSION < 0x40000
      QPopupMenu *optionMenu    = new QPopupMenu();
#else 
      Q3PopupMenu *optionMenu    = new Q3PopupMenu();
#endif 
      mainMenu->insertItem("&Options",optionMenu);

#if QT_VERSION < 0x40000
      QPopupMenu *helpMenu   = new QPopupMenu();
#else 
      Q3PopupMenu *helpMenu   = new Q3PopupMenu();
#endif 
      mainMenu->insertItem("&Help",helpMenu);
  // -- The menu bar has been completed

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  fileMenu
   
   saveAction     ->addTo(fileMenu);
   //saveAsAction   ->addTo(fileMenu);
   //fSnapShotAction->addTo(fileMenu);
   openAction     ->addTo(fileMenu);
   clearAction     ->addTo(fileMenu);
                    fileMenu->insertSeparator();
   printAction    ->addTo(fileMenu);
                    fileMenu->insertSeparator();
   fileCloseAction->addTo(fileMenu);


 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  editMenu
    //copyAction     ->addTo(editMenu);
    //copyFrameAction->addTo(editMenu);
   
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  optionMenu
    //synchAction->addTo(optionMenu);
    //synchAction->setOn(true);
    //synchAction->setEnabled (true);
#ifdef QGLVIEWER

    //QWidget *c = centralWidget();
    //TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;

    showFrameAxisAction->addTo(optionMenu);
    //showFrameAxisAction->setOn(glView? glView->FrameAxisScale()> 0 : false);
    showFrameAxisAction->setOn(false);
    showFrameAxisAction->setEnabled(true);
    
    showSmallAxesAction->addTo(optionMenu);
    showSmallAxesAction->setOn(false);
    showSmallAxesAction->setEnabled(true);
    
/*
    showLightsAction->addTo(optionMenu);
    showLightsAction->setOn(false);
    showLightsAction->setEnabled (true);

    
    optionMenu->insertSeparator();

    selectEventAction->addTo(optionMenu);
    selectEventAction->setOn(glView ? glView->IsWiredSelectable() : false );
    selectEventAction->setEnabled (true);

    selectDetectorAction->addTo(optionMenu);
    selectDetectorAction->setOn( glView ? glView->IsSolidSelectable() : false );
    selectDetectorAction->setEnabled (true);
    
    optionMenu->insertSeparator();
    
    viewSelectionAction->addTo(optionMenu);
    viewSelectionAction->setOn( false );
    viewSelectionAction->setEnabled (true);
    
    viewSelectionGlobalAction->addTo(optionMenu);
    viewSelectionGlobalAction->setOn( false );
    viewSelectionGlobalAction->setEnabled (false);

    viewSelectionHighlightAction->addTo(optionMenu);
    viewSelectionHighlightAction->setOn( false );
    viewSelectionHighlightAction->setEnabled (true);
*/
    viewContextMenuAction->addTo(optionMenu);
    viewContextMenuAction->setOn( false );
    viewContextMenuAction->setEnabled (true);
    
    editClipPlaneAction->addTo(optionMenu);
    editClipPlaneAction->setOn( false );
    editClipPlaneAction->setEnabled (true);

#endif
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  helpMenu
    //helpMenu->insertItem("&Help",this,SLOT(HelpCB()));
    //helpMenu->insertSeparator();
    helpMenu->insertItem("&About",this,SLOT(AboutCB()));
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::Paint(Option_t *opt)
{
   CreateViewer();
#ifndef QGLVIEWER
   TGLViewerImp::Paint(opt);
#else
   if (opt);
   Update();
#endif

  //// Paint G3D objects  
  // Int_t myGLIst = GetGLView()->GetGLList()-1;
  // assert(myGLIst );
  // if (myGLIst) {

  //   // Pick the current TPad rotation
  //   gVirtualGL->RunGLList(myGLIst + TPadOpenGLView::kView);

  //   // Draw G3D objects
  //   gVirtualGL->RunGLList(myGLIst + TPadOpenGLView::kModel);
  // }
}
*/
//______________________________________________________________________________
void TQtCoinWidget::Update()
{  
	fRootNode->touch();
	/*
   CreateViewer();
#ifdef QGLVIEWER
   if (fGLWidget && !fSelectionViewer) 
      ((TQtGLViewerWidget*)fGLWidget)->SetSceneLayout();
#endif
   TGLViewerImp::Update();
   centralWidget()->update();
   */
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::SetFooter(QString &text)
{
   // Set the footer text
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setFooter(text);
#endif
}
*/
/*
//______________________________________________________________________________
void TQtCoinWidget::SetPadSynchronize(Bool_t on)
{
  // Define whether the GL Widget view should follow TPad rotation
#ifndef QGLVIEWER
   if(on) {} // QtGLWidget provide no synch means
#else
   if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setPadSynchronize(on);
#endif
}
*/
//______________________________________________________________________________
void TQtCoinWidget::SetRotationAxisAngle(const float x, const float y, const float z, const float a)
{
	/*
   // Set the current rotation of the frame. 
   // Parameters are the rotation axis vector and its angle (in radians). 
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setRotationAxisAngle(x,y,z,a);
#endif
	*/
}

//______________________________________________________________________________
void TQtCoinWidget::SetBackgroundColor(Color_t color)
{
   TColor *background = gROOT->GetColor(color);
   if (background) {
     float rgb[3];
     background->GetRGB(rgb[0],rgb[1],rgb[2]);
     fInventorViewer->setBackgroundColor(SbColor(rgb));
   }  
}

//______________________________________________________________________________
void TQtCoinWidget::ShowObjectInfo(TObject *obj, const QPoint &cursorPosition)
{
  if (obj) {
	/*
   //  Qt Slot to accept the signal emiited by the GL Widget selecting the ROOT object
   static QRect previousTipArea;
   QString tipText = obj->GetObjectInfo(cursorPosition.x(),cursorPosition.y());
   
   SetStatusText(obj->GetName(), 0);
   Color_t objectColor = -1;
   if (obj->InheritsFrom("TAttLine")) {
      TAttLine *lAttr = dynamic_cast<TAttLine *>(obj);
      if (lAttr)  objectColor =  lAttr->GetLineColor();
   }
   SetStatusText(QString("%1,%2").arg(cursorPosition.x()).arg(cursorPosition.y()), 1,objectColor);
   SetStatusText(obj->ClassName(), 2);
   SetStatusText(tipText, 3);
   // Create a tooltip

   TQtGLViewerWidget *tipped = (TQtGLViewerWidget *)sender();
   QPoint globalPosition = tipped->mapToGlobal(cursorPosition);
#if QT_VERSION < 0x40000
   QWhatsThis::display(tipText, globalPosition,tipped);
#else 
   Q3WhatsThis::display(tipText, globalPosition,tipped);
#endif 

   TObject3DView *view = (TObject3DView *)tipped->selectedName();

   // open a separate window to show the selection   
   if (fSelectedViewActive) {      
      if (!fSelectedView) 
         CreateSelectionViewer();
      else 
         fSelectedView->Clear();
      fSelectedView->setCaption(tipText);
      ULong_t id = 0;
      if (fShowSelectionGlobal) {
          if (!view->GetViewId(TObject3DViewFactoryABC::kSelected)) view->CompileSelection();
          id = view->GetViewId(TObject3DViewFactoryABC::kSelected);
      } else { 
          id = view->GetViewId();
      }
      fSelectedView->AddGLList(id, view->IsSolid() );
//      fSelectedView->Update();
      fSelectedView->update();
   }
   if (fSelectionHighlight) {
      // remove the previouse selection
      tipped->clearGLList(TQtGLViewerWidget::kSelected);
      // Hightlight the new one
      if (!view->GetViewId(TObject3DViewFactoryABC::kSelected)) view->CompileSelection();
      tipped->addGLList(view->GetViewId(TObject3DViewFactoryABC::kSelected), TQtGLViewerWidget::kSelected);
   }
   */
   // Display the context menu if any
      if (fWantRootContextMenu) {
      // Popup the context menu
         QPoint pos = fInventorViewer->getWidget()->mapToGlobal(cursorPosition);
         ContextMenu().Popup(pos.x(),pos.y(), obj,(TBrowser *)0);
      }
   }
}
/*
//______________________________________________________________________________
void TQtGLViewerImp::CreateSelectionViewer( ) 
{
   // Create another OpenGL viewer to show the selection 
   if (fSelectedViewActive && !fSelectedView)  {
      fSelectedView  = new TQtGLViewerImp(*this);
      fSelectedView->SelectEventCB(false);
      fSelectedView->SelectDetectorCB(false);
   }
}
*/
//______________________________________________________________________________
ULong_t TQtCoinWidget::GetViewerID() const
{
   return ULong_t((QMainWindow *) this);
}

//______________________________________________________________________________
void TQtCoinWidget::SetSnapFileCounter(int counter)
{ 
	fMaxSnapFileCounter = counter;  
}
//______________________________________________________________________________
void TQtCoinWidget::SetCliPlaneMan(Bool_t on)
{
   if (on) {
     if (!fClipPlaneMan) {
        fClipPlaneMan = new SoClipPlaneManip();       
        fClipPlaneMan->ref();
        SoGetBoundingBoxAction ba(fInventorViewer->getViewportRegion());
        ba.apply(fShapeNode);
   
        SbBox3f box = ba.getBoundingBox();
        fClipPlaneMan->setValue(box, SbVec3f(1.0f, 0.0f, 0.0f), 0.5f);
        
        fClipPlane    = new SoClipPlane();
        fClipPlane->plane = fClipPlaneMan->plane;
        fShapeNode->insertChild(fClipPlane,0);
     }
     
     fClipPlane->on = FALSE;
     fClipPlaneMan->plane = fClipPlane->plane;    
          
     fShapeNode->insertChild(fClipPlaneMan, 0);
     
  } else if (fClipPlaneMan) {
     fShapeNode->removeChild(fClipPlaneMan);
     fClipPlane->plane = fClipPlaneMan->plane;
     fClipPlane->on=TRUE;
  }
}

//______________________________________________________________________________
void TQtCoinWidget::FrameAxisActionCB(bool on)
{
  SetCliPlaneMan(on); 
}
//______________________________________________________________________________
void TQtCoinWidget::SmallAxesActionCB(bool on)
{
    if (on) {
#ifdef __SMALLCHANGE__ 
       if (!fAxes) { 
          fAxes =  new SmAxisDisplayKit();
          fAxes->ref();
          
          SmAxisDisplayKit *ax = fAxes;
          // axis sizes
          ax->axes.set1Value(0, 20., 0., 0.);
          ax->axes.set1Value(1, 0., 20., 0.);
          ax->axes.set1Value(2, 1., 0., 20.);
   
          // axis colors
          ax->colors.set1Value( 0, 1., 0., 0.);
          ax->colors.set1Value( 1, 0., 1., 0.);
          ax->colors.set1Value( 2, 1., 0., 1.);
   
          // axis labels
          ax-> annotations.set1Value(0,"x");
          ax-> annotations.set1Value(1,"y");
          ax-> annotations.set1Value(2,"z");
   
          //  Adjust the initial orientation if any
          if (fCamera) 
             ax->orientation = fCamera->orientation;
          
          if (!fCameraSensor) 
             fCameraSensor = new SoFieldSensor(cameraChangeCB,this);
       }
       fCameraSensor->attach(&fCamera->orientation);
       fRootNode->addChild(fAxes);
   } else if (fAxes) {
      fRootNode->removeChild(fAxes);
      fCameraSensor->detach();
   }
#endif
}
