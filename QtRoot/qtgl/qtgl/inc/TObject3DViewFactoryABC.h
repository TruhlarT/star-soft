// @(#)root/gtgl:$Name:  $:$Id: TObject3DViewFactoryABC.h,v 1.1 2006/08/16 19:38:48 fine Exp $
// Author: Valery Fine      24/04/05

#ifndef ROOT_TObject3DViewFactoryABC
#define ROOT_TObject3DViewFactoryABC

/****************************************************************************
**
** TObject3DViewFactoryABC
** An unterface of the class visitor to convert the ROOT 3D objets into 
** the concrete "viewer" representation like OpenGL, OpenInventor, x3d etc
**
** Copyright (C) 2005 by Valeri Fine.  Brookhaven National Laboratory All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#include "TObject.h"
#include "TString.h"
#include <map>

class TObject3DView;

class TObject3DViewFactoryABC : public TObject {
private:
   static  std::map<TString, TObject3DViewFactoryABC *> gfMap;

public:
   enum ERenderType { kNormal, kSelectable, kSelected } ;
   TObject3DViewFactoryABC() :TObject(){};
   virtual ~TObject3DViewFactoryABC(){}
   virtual void AddNormal(TObject3DView *, const Double_t *normal) = 0;
   virtual TObject3DView *BeginModel(TObject3DView *)              = 0;
   virtual TObject3DView *EndModel()                               = 0;
   virtual void           PushMatrix()                             = 0;
   virtual void           PopMatrix()                              = 0;
   virtual TObject3DView *CreateMatrix(const Double_t *traslation, const Double_t *rotation, Bool_t isReflection) = 0;
   virtual TObject3DView *CreateNormal(const Double_t *normal)     = 0;
   virtual TObject3DView *CreateShape (const TObject *shape,const Float_t *rgba)     = 0;
   virtual void           GetBoundBox(Double_t *min, Double_t *max) const            = 0;
   virtual TObject3DView *CompileSelection(TObject3DView *view)                      = 0;
   virtual void           CompileViewLevel(TObject3DView *,ERenderType type=kNormal) = 0;
   virtual ULong_t        GetViewerId(TObject3DView *) const       = 0;
   virtual Bool_t NeedCompilation()                    const       = 0;
   virtual void   Release(TObject3DView *)                         = 0;
   static TObject3DViewFactoryABC *View3DFactory(Option_t *type="OGL");
   static void DestroyCurrentView3DFactory(Option_t *type="OGL");
   ClassDef(TObject3DViewFactoryABC,0) // Abstract interface to 3D factory
};


#endif
