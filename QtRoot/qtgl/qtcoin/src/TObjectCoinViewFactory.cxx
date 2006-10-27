// @(#)root/gtgl:$Name:  $:$Id: TObjectCoinViewFactory.cxx,v 1.4 2006/10/27 00:26:47 fine Exp $
// Author: Valery Fine      24/09/06

/****************************************************************************
**
** TObjectCoinViewFactory
** An unterface of the class visitor to convert the ROOT 3D objets into 
** the concrete "viewer" representation like OpenGL, OpenInventor, x3d etc
**
** Copyright (C) 2006 by Valeri Fine.  Brookhaven National Laboratory All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#include "TObjectCoinViewFactory.h"
#include "TCoinShapeBuilder.h"
#include "TShape3DPolygonView.h"
#include "TObject3DView.h"
#include "TDataSetIter.h"
#include "TStopwatch.h"
#include "TGeometry.h"
#include <stack>

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>

#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTransformSeparator.h> 
#include <Inventor/nodes/SoTranslation.h>

#include "assert.h"
// #define OWNNORMALS 1

//______________________________________________________________________________
static inline void SetView(TObject3DView *view, const SoGroup *node)
{
     node->ref(); // this node to be release by Release method
     view->SetViewID(ULong_t ( node ) );
}

//____________________________________________________________________________________________________________________
static inline TObject3DView *OpenView(TObject3DViewFactoryABC  *aFactory) 
{  
   // Instantiate the OpenGL list and TObjectView
   // If one can not create OpenGL list the object is to dle
   TObject3DView *view = new TObject3DView(aFactory); 
   SetView(view , new SoGroup() );
   return view;
}

//____________________________________________________________________________________________________________________
TObjectCoinViewFactory::TObjectCoinViewFactory() : TObject3DViewFactory()
{ }
//____________________________________________________________________________________________________________________
TObjectCoinViewFactory::~TObjectCoinViewFactory()
{ }

//____________________________________________________________________________________________________________________
void TObjectCoinViewFactory::AddChild(TObject3DView * parent, TObject3DView *child)
{
   // Connect Coin3D node in the parent-child tree
   if (parent && child) {
      if (parent->GetViewId() == 0) {
         SoGroup * p = new SoGroup();
         p->setName(parent->GetTitle());
         p->setUserData((void*)parent);
         SetView(parent , p );
      }
      if (child->GetViewId()  == 0) {
         // FIX ME:  This is a dummy node. It must be deleted in fact
         // fprintf(stderr,"\tnew child %s \n", child->GetTitle());
         // assert(0);
         SoGroup * c = new SoGroup();
         c->setName(child->GetTitle());
         c->setUserData((void*)child);
         SetView(child , c );
      }
      SoGroup *p = (SoGroup*)(parent->GetViewId());
      p->setUserData((void*)parent); // FIXME: one has to check this first
      
      SoGroup *c = (SoGroup*)(child->GetViewId() );
      c->setUserData((void*)child);  // FIXME: one has to check this first// FIXME: one ha to checl this first
      p->addChild(c);
   } else {
      assert(0);
   }
}

//____________________________________________________________________________________________________________________
void TObjectCoinViewFactory::AddNormal(TObject3DView *, const Double_t * )
{ }

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::BeginModel(TObject3DView *rootView)
{
   if (rootView) {}
   TObject3DView *view = new TObject3DView(this);
   SoSeparator *separator = new SoSeparator();
   separator->setName(rootView->GetObject()->GetTitle());
//   separator->renderCaching = SoSeparator::ON;
//   separator->boundingBoxCaching = SoSeparator::ON;
   SetView(view , separator );
   return view;
}
//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::EndModel()
{   return 0;                                     }

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::CreateNormal(double const*)
{ return 0; }

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::CreateMatrix( const Double_t *translation
                                                      ,const Double_t *rotation
                                                      ,Bool_t isReflection )
{
   SoTranslation     *trans = 0;
   SoMatrixTransform *rot   = 0;
   TObject3DView     *view  = 0;
   Double_t  bombTranslation[3] = {1.0,1.0,1.0};
   const Double_t *thisTranslation = translation;
   {
      Float_t bombFactor[3] =  { 1.0, 1.0, 1.0 };
      if (gGeometry) {
         bombFactor[0] = bombFactor[1] = bombFactor[2] = gGeometry->GetBomb();
      }
      //SoShapeHints *hints   = new SoShapeHints;
      //hints->shapeType      = SoShapeHints::SOLID;
      //hints->vertexOrdering = isReflection  ?
      //                          SoShapeHints::CLOCKWISE :
      //                          SoShapeHints::COUNTERCLOCKWISE;
      // shapeGroup->addChild(hints);
      // TVirtualGeoPainter* TVirtualGeoPainter::GeoPainter()
      if (TMath::Abs( bombFactor[0] - 1.0) > 0.01) {
         thisTranslation = bombTranslation;
         for (int i=0;i<3;i++) bombTranslation[i] = bombFactor[i]*translation[i];
      }
      if (thisTranslation) {
          if ( (   TMath::Abs(thisTranslation[0])
                 + TMath::Abs(thisTranslation[1])
                 + TMath::Abs(thisTranslation[2])
                ) > 1.0E-7) {
            trans = new  SoTranslation();
            trans->translation.setValue( thisTranslation[0]
                                        ,thisTranslation[1]
                                        ,thisTranslation[2] );
      }  }
      if (rotation) {
         // Check whether this is the unity:
         Double_t diagonal = rotation[0] + rotation[ 4] + rotation[8];
         Bool_t doRotation = true;
         if ( TMath::Abs(diagonal - 3) < 0.00001 ) {
            Double_t members = TMath::Abs(rotation[1]) + TMath::Abs(rotation[2])
                             + TMath::Abs(rotation[3]) + TMath::Abs(rotation[5])
                             + TMath::Abs(rotation[6]) + TMath::Abs(rotation[7]);
            // Second check 
            doRotation = ( members > 1.0E-7);
         }
         if (doRotation) {
            rot = new SoMatrixTransform();
            rot->matrix.setValue(    rotation[0] , rotation[ 1] , rotation[ 2] , 0.
                                   , rotation[3] , rotation[ 4] , rotation[ 5] , 0.
                                   , rotation[6] , rotation[ 7] , rotation[ 8] , 0.
                                   ,     0.      ,     0.       ,     0.       , 1.
                                );
            if (isReflection)
               rot->setName("reflection");
            else
               rot->setName("straight");
         }
      }
      if ( trans || rot ) {
         view =  OpenView(this);
         SoGroup *shapeGroup = (SoGroup *) view->GetViewId();
         shapeGroup->setName("VolumeTransformation");
         if (trans) shapeGroup->addChild(trans);
         if (rot)   shapeGroup->addChild(rot);
      }
   }
   return view;
}

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::CreatePosition(UInt_t Id)
{
    // Create the new position node with Id
   if (Id) {}
   TObject3DView *view = new TObject3DView(this);
   // SoTransformSeparator *separator =  new SoTransformSeparator();
   SoSeparator *separator =  new SoSeparator();
   separator->setName("Position");
//   SoSeparator *separator =  new SoSeparator();
//   separator->renderCaching      = SoSeparator::ON;
//   separator->boundingBoxCaching = SoSeparator::ON;
   SetView(view , separator);
   return view;
}

//____________________________________________________________________________________________________________________
TObject3DView *CreateNormal(const Double_t * /*normal*/)
{  return 0;  }

//____________________________________________________________________________________________________________________
void TObjectCoinViewFactory::CompileViewLevel(TObject3DView *,ERenderType )
{
   // No compile view level is needed for Coin Factory
}

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::MakeShape(TShape3DPolygonView &shapeView, const Float_t *rgba)
{
    TObject3DView *view = new TObject3DView(this);

    TCoinShapeBuilder coinShape(shapeView, rgba);
    SetView(view, coinShape());

    return view;
} 
//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::CompileSelection(TObject3DView *view)
{
   // No compile selection is needed for Coin Factory
   return view;
}
 
//____________________________________________________________________________________________________________________
void  TObjectCoinViewFactory::GetBoundBox(Double_t *min, Double_t *max) const
{
   const Coord3D &maxBox = fBoundBox.GetMaxBounds();
   const Coord3D &minBox = fBoundBox.GetMinBounds();
   for (int i=0; i < 3; i++ ){
      min[i] =  minBox[i];
      max[i] =  maxBox[i];
   }
}

//____________________________________________________________________________________________________________________
ULong_t TObjectCoinViewFactory::GetViewerId(TObject3DView *view) const
{       assert(0);   return view ? view->GetViewId():0;                      }
//____________________________________________________________________________________________________________________
Bool_t TObjectCoinViewFactory::NeedCompilation() const
{   
   // Coin view needs no compilation step to be performed
   return kFALSE; 
}
//____________________________________________________________________________________________________________________
void   TObjectCoinViewFactory::Release(TObject3DView *view)
{ 
   if (view) {
      SoGroup *id = 0;
      if ( (id = (SoGroup *)view->GetViewId()) )  
         id->unref();
      if ( (id = (SoGroup *)view->GetViewId(TObject3DViewFactoryABC::kSelectable)) ) 
         id->unref();
      if ( (id = (SoGroup *)view->GetViewId(TObject3DViewFactoryABC::kSelected))  ) 
         id->unref();
   }
}

