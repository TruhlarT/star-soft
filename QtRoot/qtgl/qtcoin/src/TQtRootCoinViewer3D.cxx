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

//#include "TQtRootViewer3D.h"
#include "TQtRootCoinViewer3D.h"
#include "TQtCoinViewerImp.h"
#include "TObjectCoinViewFactory.h"

#include "TDataSetIter.h"

#include "TGQt.h"

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
{
	printf("TQtRootCoinViewer3D::TQtRootCoinViewer3D %p\n",this);
}

//______________________________________________________________________________
void   TQtRootCoinViewer3D::Viewer()
{
	printf("TQtRootCoinViewer3D::Viewer begin\n");
   if (!fCoinViewer && fPad) {
	TObject3DViewFactoryABC::Registr(new TObjectCoinViewFactory(), "oiv");
	fView3DFactory = TObject3DViewFactoryABC::View3DFactory("oiv");
	fListOfPrimitives.SetViewFactory(fView3DFactory);
      fCoinViewer = new TQtCoinViewerImp(fPad,fPad->GetName(),fPad->UtoPixel(1.),fPad->VtoPixel(0.) );
      printf("TQtRootCoinViewer3D::Viewer this=%p, fPad=%p, fView3DFactory=%p, fCoinViewer=%p\n",this,fPad,fView3DFactory,fCoinViewer);
	//*
      fDisconnectSlot = new SlotDisconnect(this);
     //  QObject::connect(fViewer,SIGNAL(destroyed()), fDisconnectSlot, SLOT(Disconnect()));
      QObject::connect(fCoinViewer,SIGNAL(destroyed()), fDisconnectSlot, SLOT(DestroyMaster()));
 //     QObject::connect(fViewer->GLWidget(),SIGNAL(viewerAbout2Close())
 //                     , fDisconnectSlot, SLOT(CleanPrimitives()));
      // fPad->Connect("Modified()","TQtRootViewer3D", this, "UpdateView()");
      fPad->Connect("Closed()","TQtRootViewer3D", this, "DisconnectPad()");
      QObject::connect(gQt->Emitter(),SIGNAL(padPainted(QPixmap*)),fDisconnectSlot, SLOT(UpdateView(QPixmap*)));
	 //  */
   }
   printf("TQtRootCoinViewer3D::Viewer end\n");
}
//______________________________________________________________________________
TQtRootCoinViewer3D::~TQtRootCoinViewer3D()
{
    TQtCoinViewerImp *sav = fCoinViewer;
    if (sav && fDisconnectSlot) {
       QObject::disconnect(sav,SIGNAL(destroyed()), fDisconnectSlot, SLOT(DestroyMaster()));
//       QObject::disconnect(sav,SIGNAL(viewerAbout2Close()), fDisconnectSlot, SLOT(CleanPrimitives()));
       ClearPrimitives();
    }
    if (fDisconnectSlot) {  delete fDisconnectSlot; fDisconnectSlot = 0; }
    Disconnect();
    if (sav) delete sav;
}


//______________________________________________________________________________
void TQtRootCoinViewer3D::ClearPrimitives()
{
   if (fCoinViewer)  {
      //fViewer->MakeCurrent();
      fCoinViewer->setUpdatesEnabled(FALSE);
      fCoinViewer->Clear();
   }
   fListOfPrimitives.Delete();
   fListOfPrimitives.Clear();
}
//______________________________________________________________________________
void  TQtRootCoinViewer3D::EndScene(){
	printf("TQtRootCoinViewer3D::EndScene\n");
  
	fCoinViewer->Clear();
     TDataSetIter nextList(&fListOfPrimitives);
     TObject3DView *glo = 0;
     while( (glo = (TObject3DView *)nextList()  )) {
	//glo->ls(0);
	printf("TQtRootCoinViewer3D::EndScene_in loop\n");
		fCoinViewer->AddRootChild(glo->GetViewId());
     }
	// old internal format GLFactory
	/*
   // called by TPad::Paint | PaintModified
   // This is a signal the scene has been closed and we should refresh the display
   if (fCoinViewer) {
     //fCoinViewer->MakeCurrent();
#if 1
      fCoinViewer->setUpdatesEnabled(FALSE);
      fCoinViewer->Clear();
#endif
    fCoinViewer->SetBackgroundColor(gPad->GetFillColor());
#if 0     
     fListOfPrimitives.CompileViewLevel();
#endif     
     TDataSetIter nextList(&fListOfPrimitives);
     TObject3DView *glo = 0;
     while( (glo = (TObject3DView *)nextList()  )) {
        fCoinViewer->AddGLList(glo->GetViewId(), glo->IsSolid() );
#ifdef EXTRASELECTION
        if ( glo->GetViewId(TObject3DViewFactoryABC::kSelectable) ) 
           fCoinViewer->AddGLList(glo->GetViewId(TObject3DViewFactoryABC::kSelectable), 2 );
#endif
     }
     fCoinViewer->setUpdatesEnabled(TRUE);
     fCoinViewer->Update();
   }
   fBuildingScena = kFALSE;
   */
   
}
//______________________________________________________________________________
void   TQtRootCoinViewer3D::DisconnectPad()
{
   if (fPad) {
      // fprintf(stderr," TQtRootViewer3D::DisconnectPad() fPad= %p %s\n", fPad, fPad->GetName());
      QObject::disconnect(gQt->Emitter(),SIGNAL(padPainted(QPixmap*)),fDisconnectSlot, SLOT(UpdateView(QPixmap*)));
      if (fCoinViewer) {
          fCoinViewer->DisconnectPad();
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
      if (fCoinViewer) {
         QObject::disconnect(fCoinViewer,SIGNAL(destroyed()),        fDisconnectSlot, SLOT(DestroyMaster()));
          //QObject::disconnect(fViewer,SIGNAL(viewerAbout2Close()),fDisconnectSlot, SLOT(CleanPrimitives()));
         fCoinViewer->DisconnectPad();
      }
      fPad->TQObject::Disconnect("Closed()",this, 0);
      fPad->TQObject::Disconnect("Modified()",this, 0);
#if ROOT_VERSION_CODE < ROOT_VERSION(5,07,00)
      TVirtualViewer3D *currentPadViewer = fPad->GetViewer3D(0);
#else
      TVirtualViewer3D *currentPadViewer = fPad->GetViewer3D("");
#endif
      if (currentPadViewer == (TVirtualViewer3D *)this ) 
         fPad->ReleaseViewer3D();
   }
   fCoinViewer = 0;
}


//______________________________________________________________________________
void  TQtRootCoinViewer3D::MakeViewerNil()
{
   fCoinViewer = 0;
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
