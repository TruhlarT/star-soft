// @(#)root/base:$Name:  $:$Id: TQtRootViewer3D.cxx
// Author: Valeri Fine 05/05/2005

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtRootViewer3D                                                      //
//                                                                      //
// Generic 3D shapes viewer.                                            //
//                                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <cassert>
//#include "TQtRootViewer3D.h"
#include "TQtRootCoinViewer3D.h"
#include "TQtCoinViewerImp.h"
#include "TObjectCoinViewFactory.h"

#include "TDataSetIter.h"

#include "TGQt.h"
#include "TEnv.h"
#include <qstringlist.h>
#include <Inventor/SoDB.h> 
#include <Inventor/SoInput.h> 

/*
#include "TObject3DView.h"

#include "TQtGLViewerImp.h"

#include "TList.h"
#include "TError.h"

#ifndef __APPLE__
#  include "TRootGLU.h"
#else
#  include <glu.h>
#endif

#include "TObjectOpenGLViewFactory.h"
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#include <QPixmap>
#endif 
*/
/* QT_VERSION */

#include "TVirtualPad.h"

ClassImp(TQtRootCoinViewer3D)
//______________________________________________________________________________
TQtRootCoinViewer3D::TQtRootCoinViewer3D(TVirtualPad * pad)
	: TQtRootViewer3D(pad)
{ }

//______________________________________________________________________________
void   TQtRootCoinViewer3D::Viewer()
{
   if (!fViewer && fPad) {
   fView3DFactory = TObject3DViewFactoryABC::View3DFactory("oiv");
   if (!fView3DFactory) {
      SoDB::init();
      TObject3DViewFactoryABC::Registr(new TObjectCoinViewFactory(), "oiv");
      fView3DFactory = TObject3DViewFactoryABC::View3DFactory("oiv");
      // prepare the list of the search directories for "iv" files
      // that matches the list of the ROOO macros directories
      const char *macroPath = gEnv->GetValue("Root.MacroPath","");
      if (macroPath && macroPath[0]) {
          SoInput::removeDirectory(".");
#ifdef R__WIN32
         const char sep = ';';
#else
         const char sep = ':';
#endif
         TString path(macroPath); path.ReplaceAll("\\","/");
         QStringList macroPathList =  QStringList::split(QChar(sep),QString((const char*)path));
         for ( QStringList::Iterator it = macroPathList.begin(); it != macroPathList.end(); ++it ) 
         {
             SoInput::addDirectoryLast((const char*)(*it));
         }
      }
   }
   assert(fView3DFactory);
   fListOfPrimitives.SetViewFactory(fView3DFactory);
      fViewer = new TQtCoinViewerImp(fPad,fPad->GetName(),fPad->UtoPixel(1.),fPad->VtoPixel(0.) );
      fDisconnectSlot = new SlotDisconnect(this);
      QObject::connect(&(fViewer->Signals()),SIGNAL(destroyed()), fDisconnectSlot, SLOT(DestroyMaster()));
      fPad->Connect("Closed()","TQtRootCoinViewer3D", this, "DisconnectPad()");
      QObject::connect(gQt->Emitter(),SIGNAL(padPainted(QPixmap*)),fDisconnectSlot, SLOT(UpdateView(QPixmap*)));
   }
   // printf("TQtRootCoinViewer3D::Viewer end\n");
}
//______________________________________________________________________________
TQtRootCoinViewer3D::~TQtRootCoinViewer3D()
{  }


//______________________________________________________________________________
void TQtRootCoinViewer3D::ClearPrimitives()
{
   if (fViewer)  {
      //fViewer->MakeCurrent();
      fViewer->SetUpdatesEnabled(FALSE);
      fViewer->Clear();
   }
   fListOfPrimitives.Delete();
   fListOfPrimitives.Clear();
}
//______________________________________________________________________________
void  TQtRootCoinViewer3D::EndScene()
{
   printf("TQtRootCoinViewer3D::EndScene\n");

   fViewer->SetUpdatesEnabled(FALSE);
   fViewer->Clear();
   TDataSetIter nextList(&fListOfPrimitives);
   TObject3DView *glo = 0;
   while( (glo = (TObject3DView *)nextList()  )) {
   //glo->ls(0);
      fViewer->AddRootChild(glo->GetViewId()
                          , glo->IsSolid() ? TGLViewerImp::kSolid : TGLViewerImp::kWired);
   }
   fViewer->SetUpdatesEnabled(TRUE);
   fViewer->ViewAll();
   fViewer->Update();

   // old internal format GLFactory
	/*
   // called by TPad::Paint | PaintModified
   // This is a signal the scene has been closed and we should refresh the display
   if (fViewer) {
     //fViewer->MakeCurrent();
#if 1
      fViewer->setUpdatesEnabled(FALSE);
      fViewer->Clear();
#endif
    fViewer->SetBackgroundColor(gPad->GetFillColor());
#if 0     
     fListOfPrimitives.CompileViewLevel();
#endif     
     TDataSetIter nextList(&fListOfPrimitives);
     TObject3DView *glo = 0;
     while( (glo = (TObject3DView *)nextList()  )) {
        fViewer->AddGLList(glo->GetViewId(), glo->IsSolid() );
#ifdef EXTRASELECTION
        if ( glo->GetViewId(TObject3DViewFactoryABC::kSelectable) ) 
           fViewer->AddGLList(glo->GetViewId(TObject3DViewFactoryABC::kSelectable), 2 );
#endif
     }
     fViewer->setUpdatesEnabled(TRUE);
     fViewer->Update();
   }
   fBuildingScena = kFALSE;
   */
   
}
//______________________________________________________________________________
Int_t  TQtRootCoinViewer3D::AddRawObject(ULong_t placedID, UInt_t optMask)
{
   if (fViewer) {
      fViewer->AddRootChild(placedID,TGLViewerImp::EObject3DType(optMask));
   }
   return 0;
}

//______________________________________________________________________________
void   TQtRootCoinViewer3D::DisconnectPad()
{
   if (fPad) {
      // fprintf(stderr," TQtRootViewer3D::DisconnectPad() fPad= %p %s\n", fPad, fPad->GetName());
      QObject::disconnect(gQt->Emitter(),SIGNAL(padPainted(QPixmap*)),fDisconnectSlot, SLOT(UpdateView(QPixmap*)));
      if (fViewer) {
          fViewer->DisconnectPad();
      }
      fPad->TQObject::Disconnect("Closed()",this, 0);
      fPad->TQObject::Disconnect("Modified()",this, 0);
      fPad = 0;
   }
}
//______________________________________________________________________________
void   TQtRootCoinViewer3D::Disconnect() 
{
   if (fPad)  {
      // fprintf(stderr," TQtRootViewer3D::Disconnect() fViewer=%p\n", fViewer);
      if (fViewer) {
         QObject::disconnect(&(fViewer->Signals()),SIGNAL(destroyed()), fDisconnectSlot, SLOT(DestroyMaster()));
          //QObject::disconnect(fViewer,SIGNAL(viewerAbout2Close()),fDisconnectSlot, SLOT(CleanPrimitives()));
         fViewer->DisconnectPad();
      }
      fPad->TQObject::Disconnect("Closed()",this, 0);
      fPad->TQObject::Disconnect("Modified()",this, 0);
#if ROOT_VERSION_CODE < ROOT_VERSION(5,07,00)
      TVirtualViewer3D *currentPadViewer = fPad->GetViewer3D(0);
#else
      TVirtualViewer3D *currentPadViewer = fPad->GetViewer3D((const char*)0);
#endif
      if (currentPadViewer == (TVirtualViewer3D *)this ) 
         fPad->ReleaseViewer3D();
   }
   fViewer = 0;
}


//______________________________________________________________________________
void  TQtRootCoinViewer3D::MakeViewerNil()
{
   fViewer = 0;
}


/*
//______________________________________________________________________________
Int_t  TQtRootCoinViewer3D::AddObject(TObject *obj, Option_t* drawOption , Bool_t * addChildren )
{
    //return 0;
    return  TQtRootViewer3D::AddObject(obj,drawOption,addChildren );
}
//______________________________________________________________________________
 Int_t  TQtRootCoinViewer3D::AddObjectFirst(TObject *obj, Option_t* drawOption , Bool_t * addChildren )
{
    //return 0;
    return  TQtRootViewer3D::AddObjectFirst(obj,drawOption,addChildren );
}
*/
