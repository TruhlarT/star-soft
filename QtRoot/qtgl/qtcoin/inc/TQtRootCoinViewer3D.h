// @(#)root/base:$Name:  $:$Id: TQtRootViewer3D.h
// Author: Valeri Fine 05/10/2004

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TQtRootCoinViewer3D
#define ROOT_TQtRootCoinViewer3D

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtRootCoinViewer3D                                                  //
//                                                                      //
// Abstract 3D shapes viewer. The concrete implementations are:         //
//                                                                      //
// TViewerX3D   : X3d viewer                                            //
// TViewerOpenGL: OpenGL viewer                                         //
// TViewerPad3D : visualise the 3D scene in the current Pad             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TQtRootViewer3D.h"

class TQtCoinViewerImp;
class TVirtualPad;

class TQtRootCoinViewer3D : public TQtRootViewer3D
{
   friend class     SlotDisconnect;
public:
   TQtRootCoinViewer3D(TVirtualPad * pad = 0);	
   virtual void   EndScene();            // called by TPad::Paint | PaintModified
   virtual void   DisconnectPad();
   //virtual Int_t  AddObject(TObject *, Option_t* drawOption = 0, Bool_t * addChildren = 0);
   //virtual Int_t  AddObjectFirst(TObject *, Option_t* drawOption = 0, Bool_t * addChildren = 0);
protected:
   // TQtCoinViewerImp   *fCoinViewer;
   virtual void        Viewer();
   virtual ~TQtRootCoinViewer3D();

   virtual void     MakeViewerNil();	
   void             Disconnect();
   void             ClearPrimitives();

   ClassDef(TQtRootCoinViewer3D,0)  // Abstract interface to 3D viewers
};

#endif
