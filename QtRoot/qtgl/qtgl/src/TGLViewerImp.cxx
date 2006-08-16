// @(#)root/g3d:$Name:  $:$Id: TGLViewerImp.cxx,v 1.1 2006/08/16 19:38:49 fine Exp $
// Author: Valery Fine      23/05/97

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGLViewerImp                                                         //
//                                                                      //
// TGLViewerImp is abstract OpenGL viewer. Actual implementations are   //
// TRootGLViewer and TWin32GLViewerImp. The TGLViewer is used by the    //
// TPadOpenGLView.                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#include "RVersion.h"
#if ROOT_VERSION_CODE >= ROOT_VERSION(4,01,00)

//  This class was relocated from ROOT 4.00.08 g3g package

#include "TQGLViewerImp.h"
#include "TGuiFactory.h"
#include "TROOT.h"
#include "TQPadOpenGLView.h"
#include "TQVirtualGL.h"


ClassImp(TGLViewerImp)

//______________________________________________________________________________
TGLViewerImp::TGLViewerImp()
{
    fDrawList = 0;
    fGLView   = 0;
    fPaint    = kFALSE;
}

//______________________________________________________________________________
TGLViewerImp::TGLViewerImp(TPadOpenGLView *, const char *, UInt_t, UInt_t)
{
    fDrawList = 0;
    fGLView   = 0;
    fPaint    = kFALSE;
}

//______________________________________________________________________________
TGLViewerImp::TGLViewerImp(TPadOpenGLView *, const char *, Int_t, Int_t, UInt_t, UInt_t)
{
    fDrawList = 0;
    fGLView   = 0;
    fPaint    = kFALSE;
}

//______________________________________________________________________________
TGLViewerImp::~TGLViewerImp()
{
   // break view / viewer relationship
   if (fGLView) {
      TPadOpenGLView *view = fGLView;
      fGLView = 0;
      view->Disconnect();
      delete view;
   }
   fPaint    = kFALSE;
   // Delete the browser.

//   gROOT->GetListOfGLViewers()->Remove(this);
}

//______________________________________________________________________________
void TGLViewerImp::DeleteView()
{ 
   if(fGLView) { 
      // some protection  to avoid a cross deleting 
      // of the  "view" and "viewer"
      TPadOpenGLView *view = fGLView;
      fGLView = 0;
      delete view; 
   } 
}

//______________________________________________________________________________
void TGLViewerImp::HandleInput(EEventType button, Int_t x, Int_t y)
{
    if (!fGLView) return;

    switch (button) {
    case kButton1Down:
    case kButton1Up:
    case kButton1Motion:
    case kKeyPress :
        fGLView->ExecuteEvent(button,x,y);
        break;
    default:
        break;
    }
}

//______________________________________________________________________________
void TGLViewerImp::Paint(Option_t *)
{
 //   if (fPaint)
    {
        MakeCurrent();
        if (fGLView) fGLView->Paint();
        //*-* Run extra GL list if any
        UInt_t list = 0;
        if ((list=GetDrawList()))
            gQVirtualGL->RunGLList(list);
        gQVirtualGL->FlushGL();
        SwapBuffers();
//        SetStatusText("Done",1);
 //       fPaint = kFALSE;
    }
}
#endif
