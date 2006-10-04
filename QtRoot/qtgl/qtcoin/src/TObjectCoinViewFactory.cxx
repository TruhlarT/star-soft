// @(#)root/gtgl:$Name:  $:$Id: TObjectCoinViewFactory.cxx,v 1.1 2006/10/04 20:38:10 fine Exp $
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
#include "TShape3DPolygonView.h"
#include "TObject3DView.h"
#include "TDataSetIter.h"
#include "TStopwatch.h"
#include "TGeometry.h"
#include <stack>

#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/fields/SoMFVec3f.h> 
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoMarkerSet.h> 
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShapeHints.h>

#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTransformSeparator.h> 
#include <Inventor/nodes/SoTranslation.h>

#include "assert.h"
// #define OWNNORMALS 1

//______________________________________________________________________________
static inline void SetView(TObject3DView *view, const SoGroup *node)
{
     view->SetViewID(ULong_t ( node ) );
}
//______________________________________________________________________________
static inline SoNode *SetCurrentColor(const Float_t *rgba,bool material=false)
{
   SoNode *node = 0;
   if ( material ) {
      SoMaterial * m = new SoMaterial;
      m->diffuseColor.setValue(rgba[0], rgba[1], rgba[2]);
      m->transparency = rgba[3]; // fFactor;
      m->shininess = .4;
      node = m;
   } else {
      SoBaseColor * colorNode = new SoBaseColor;
      colorNode->rgb = SbColor(rgba[0], rgba[1], rgba[2]);
      node = colorNode;
   }
   return node;
}

//____________________________________________________________________________________________________________________
static inline void SetIndex(int index, int value, SoMFInt32  &coordIndex)
{
   coordIndex.set1Value(index, value);
}

//____________________________________________________________________________________________________________________
static inline void MakeShapeQuadeStrip(const std::vector<Int_t>  &rootIndices, SoMFInt32  &coinIndex )
{
   // Create the QuadeStrip indexed set

   Int_t vSize = rootIndices.size();
   Int_t jOff = coinIndex.getNum();  if (jOff == 1)  jOff = 0;
   coinIndex.setNum(jOff+vSize+vSize/4);
   Int_t i =0;
   Int_t j = jOff;
   if (vSize ==  1) {
         SetIndex(j++, rootIndices[i], coinIndex);
         SetIndex(j++, SO_END_FACE_INDEX,coinIndex);
   } else {
      for (;i < vSize-2; i += 2) {
         SetIndex(j++, rootIndices[i+0], coinIndex);
         SetIndex(j++, rootIndices[i+1], coinIndex);
         SetIndex(j++, rootIndices[i+3], coinIndex);
         SetIndex(j++, rootIndices[i+2], coinIndex);
         SetIndex(j++, SO_END_FACE_INDEX,coinIndex);
      }
   }
}

//____________________________________________________________________________________________________________________
static inline void MakeShapeQuads(const std::vector<Int_t>  &rootIndices, SoMFInt32  &coinIndex )
{
   // Create the Quads indexed set
   Int_t vSize = rootIndices.size();
   Int_t jOff = coinIndex.getNum(); if (jOff == 1)  jOff = 0;
   coinIndex.setNum(jOff+vSize+vSize/4);
   Int_t i = 0;
   Int_t j = jOff;
   // fprintf(stderr, " MakeShapeQuads  size = %d offset = %d\n", vSize, jOff );
   if (vSize ==  1) {
         SetIndex(j++, rootIndices[i], coinIndex);
         SetIndex(j++, SO_END_FACE_INDEX,coinIndex);
   } else {
      for (;i < vSize; i += 4 ) {
         SetIndex(j++, rootIndices[i+0], coinIndex); // fprintf(stderr,"%d %d : ",j-1, rootIndices[i]);
         SetIndex(j++, rootIndices[i+1], coinIndex); // fprintf(stderr,"%d %d : ",j-1, rootIndices[i+1]);
         SetIndex(j++, rootIndices[i+2], coinIndex); // fprintf(stderr,"%d %d : ",j-1, rootIndices[i+2]);
         SetIndex(j++, rootIndices[i+3], coinIndex); // fprintf(stderr,"%d %d : ",j-1, rootIndices[i+3]);
         SetIndex(j++, SO_END_FACE_INDEX,coinIndex); // fprintf(stderr,"%d \n", jOff+vSize);
   }  }
}
 

//____________________________________________________________________________________________________________________
static inline void MakeShape(const std::vector<Int_t>  &rootIndices, SoMFInt32  &coinIndex )
{
   // Create the Line or Polygon indexed set
   Int_t vSize = rootIndices.size();
   Int_t jOff  = coinIndex.getNum(); if (jOff == 1)  jOff = 0;
   coinIndex.setNum(jOff+vSize+1);
   Int_t i =0;
   // fprintf(stderr,"MakeShape size=%d\n", vSize);
   for (;i < vSize; i++) {
       SetIndex(jOff+i, rootIndices[i],coinIndex);
       // fprintf(stderr,"::  %d. %d  ::  \n", jOff+i, rootIndices[i] );
   }
   SetIndex(jOff+vSize, SO_END_FACE_INDEX,coinIndex);
   // fprintf(stderr,"\n");
}
//____________________________________________________________________________________________________________________
static inline void MakeShapeQuadeStrip(SoIndexedFaceSet *face, const TPolygone3DView &shape, const std::vector<Int_t> &normIndex)
{
   // Create the QuadeStrip set for that
   if (face) {
      MakeShapeQuadeStrip(shape.fVertexIndices,face->coordIndex);
#ifdef OWNNORMALS
      MakeShapeQuadeStrip(normIndex,face->normalIndex);
#endif
   }
}

//____________________________________________________________________________________________________________________
static inline void MakeShapeQuads(SoIndexedFaceSet *face, const TPolygone3DView &shape
                                                        , const std::vector<Int_t> &normIndex)
{
   // Create the Quade indexed set
   if (face) {
      MakeShapeQuads(shape.fVertexIndices,face->coordIndex);
#ifdef OWNNORMALS
      MakeShapeQuads(normIndex,face->normalIndex);
#endif
   }
}


//____________________________________________________________________________________________________________________
static inline void MakeShape(SoIndexedShape *face, const TPolygone3DView &shape
                                                 , const std::vector<Int_t> &normIndex)
{
   if (face) {
      MakeShape(shape.fVertexIndices,face->coordIndex);
#ifdef OWNNORMALS
      if (normIndex[0] >= 0 ) {
        MakeShape(normIndex,face->normalIndex);
      }
#endif
  }
}
//____________________________________________________________________________________________________________________
static inline void MakeShapePolygon(SoIndexedFaceSet *face,const TPolygone3DView &shape
                                                          ,const std::vector<Int_t> &normIndex)
{
    // Create the Polygon set for that
   MakeShape(face, shape, normIndex);
}

//____________________________________________________________________________________________________________________
static inline void MakeShapeLines(SoIndexedLineSet *face,const TPolygone3DView &shape
                                                        , const std::vector<Int_t> &normIndex)
{
   MakeShape(face, shape, normIndex);
}

//____________________________________________________________________________________________________________________
static inline void AddCoordinates(SoCoordinate3 &currentCoordinate,const std::vector<Coord3D> &vertices)
{
   // Fill the coordinate
   SoMFVec3f &point = currentCoordinate.point;
   int startIndex = point.getNum(); if(startIndex==1) startIndex =0;
   int size       = vertices.size();
   // fprintf(stderr,"AddCoordinates %d\n", size);
   point.setNum(startIndex+size);
   std::vector <Coord3D>::const_iterator vertex = vertices.begin();
   for (;vertex != vertices.end(); ++vertex ) {
       point.set1Value(startIndex++,(*vertex).fX,(*vertex).fY,(*vertex).fZ);
       // fprintf(stderr,"AddCoordinates %f %f %f\n", (*vertex).fX,(*vertex).fY,(*vertex).fZ );
   }
}

//____________________________________________________________________________________________________________________
static inline void AddNormals(SoNormal &currentNormal,const std::vector<Coord3D> &normals)
{
   // Fill normals
   SoMFVec3f &vector = currentNormal.vector;
   int startIndex = vector.getNum();  if(startIndex==1) startIndex =0;
   int size       = normals.size(); 
   // fprintf(stderr,"AddNormals %d\n", size);
   vector.setNum(startIndex+size);
   std::vector <Coord3D>::const_iterator normal = normals.begin();
   for (;normal != normals.end(); ++normal ) {
      vector.set1Value(startIndex++,(*normal).fX,(*normal).fY,(*normal).fZ);
      // fprintf(stderr,"AddNormals %f %f %f\n", (*normal).fX,(*normal).fY,(*normal).fZ);
   }
}
//____________________________________________________________________________________________________________________
static inline void MakeShape(SoIndexedFaceSet *face, const TPolygone3DView &shape
                                                   , const std::vector<Int_t> &normIndex)
{
   // see: http://www.rush3d.com/reference/opengl-redbook-1.1/figures/fig2-6.gif
   if (face) {
      switch (shape.fType) {
      case TPolygone3DView::kTriangle:
         assert(0); break;
      case TPolygone3DView::kQuadeStrip:
         MakeShapeQuadeStrip(face,shape,normIndex);
         break;
      case TPolygone3DView::kQuade:
         MakeShapeQuads(face,shape,normIndex);
         break;
      case TPolygone3DView::kPolygon:
         MakeShapePolygon(face,shape,normIndex);
         break;
      default: fprintf(stderr, "ERROR **  MakeShape  unknown shape type %x\n",shape.fType);
      }
   }
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
TObject3DView *TObjectCoinViewFactory::MakeShape(TShape3DPolygonView &shapeView, const Float_t *rgba)
{
    TObject3DView *view = OpenView(this);
    // shapeView.Print();
    SoGroup *shapeGroup = (SoGroup *) view->GetViewId();
    const std::vector<Coord3D> &vertices = shapeView.fVertex;

#ifdef OWNNORMALS
    // Create normals
    const std::vector<Coord3D> &normals  = shapeView.fNormals;
    SoNormal *shapeNormal      = new SoNormal();
//       shapeGroup->addChild(shapeNormal);
#endif

    SoCoordinate3 *shapeVertices = new SoCoordinate3();
//       shapeGroup->addChild(shapeVertices);

    SoIndexedFaceSet *shapeFaces       = 0;
    SoIndexedFaceSet *shapeVertexFaces = 0;
    SoLineSet        *shapeLine        = 0;
    SoPointSet       *shapePoint       = 0;

    if (shapeView.fPolygonsFaceBinding.size()) {
        std::vector <TPolygone3DFaceBindingView>::const_iterator face_binding_iter = shapeView.fPolygonsFaceBinding.begin();
        for (; face_binding_iter != shapeView.fPolygonsFaceBinding.end(); ++face_binding_iter) {
            //fprintf(stderr, " TPolygone3DFaceBindingView  %d\n",++testCounter);
            // SetCurrentSize(rgba);
            if ( ( (*face_binding_iter).fType ==  TPolygone3DView::kLines )  && !shapeLine ) { 
               shapeGroup->addChild(SetCurrentColor(rgba));
               shapeLine       = new SoLineSet();
               SoDrawStyle *ds = new SoDrawStyle();
               ds->lineWidth   = shapeView.GetLineWidth()+0.4;
               shapeGroup->addChild(ds);
            } else if ( ( (*face_binding_iter).fType ==  TPolygone3DView::kPoints) && !shapePoint) {
               shapeGroup->addChild(SetCurrentColor(rgba));
               Style_t style = (Style_t)shapeView.GetLineStyle();
              /*
               *-*  List of the currently supported markers (screen and PostScript)
               *-*  ===============================================================
               *-*      1 : dot                     kDot
               *-*      2 : +                       kPlus            PLUS_x_x
               *-*      3 : *                       kStar            STAR_x_x
               *-*      4 : o                       kCircle          CIRCLE_LINE_x_x
               *-*      5 : x                       kMultiply        CROSS_x_x
               *-*      6 : small scalable dot      kFullDotSmall
               *-*      7 : medium scalable dot     kFullDotMedium
               *-*      8 : large scalable dot      kFullDotLarge
               *-*      9 -->15 : dot
               *-*     16 : open triangle down      kOpenTriangleDown
               *-*     18 : full cross              kFullCross
               *-*     20 : full circle             kFullCircle       CIRCLE_FILLED_x_x
               *-*     21 : full square             kFullSquare       QUARE_FILLED_x_x
               *-*     22 : full triangle up        kFullTriangleUp   TRIANGLE_LINE_x_x
               *-*     23 : full triangle down      kFullTriangleDown RHOMBUS_LINE_x_x
               *-*     24 : open circle             kOpenCircle       CIRCLE_LINE_x_x
               *-*     25 : open square             kOpenSquare       SQUARE_LINE_x_x
               *-*     26 : open triangle up        kOpenTriangleUp
               *-*     27 : open diamond            kOpenDiamond      DIAMOND_LINE_x_x
               *-*     28 : open cross              kOpenCross
               *-*     29 : open star               kOpenStar
               *-*     30 : full star               kFullStar
               *-*/
               
               switch (style) {
                  case kDot: case kFullDotSmall : case kFullDotMedium : case kFullDotLarge : default:
                     shapePoint =  new SoPointSet();
                     break;
                  case kPlus:
                     shapePoint = new SoMarkerSet();
                    ((SoMarkerSet *)shapePoint)->markerIndex = SoMarkerSet::PLUS_5_5; // 5_5 - 7_7 - 9_9 
                     break;
                  case kStar:
                     shapePoint = new SoMarkerSet();
                    ((SoMarkerSet *)shapePoint)->markerIndex = SoMarkerSet::STAR_5_5;
                     break;
                  case kCircle:case  kOpenCircle:
                     shapePoint = new SoMarkerSet();
                    ((SoMarkerSet *)shapePoint)->markerIndex = SoMarkerSet::CIRCLE_LINE_5_5;
                     break;
                };
               SoDrawStyle *ds = new SoDrawStyle();
               ds->pointSize = 2.66*shapeView.GetLineWidth() + 0.5;
               shapeGroup->addChild(ds);
            } else if ( !(shapeLine || shapePoint || shapeFaces) ) {
               shapeGroup->addChild(SetCurrentColor(rgba,true));
               SoNormalBinding *binding = new SoNormalBinding();
               binding->value = SoNormalBindingElement::PER_FACE;
               shapeGroup->addChild(binding);
               SoShapeHints *hints   = new SoShapeHints;
               hints->shapeType      = SoShapeHints::SOLID;
               hints->vertexOrdering.setIgnored(TRUE);
               hints->creaseAngle    = 0.1;
               shapeGroup->addChild(hints);
               shapeFaces = new SoIndexedFaceSet();
            }
            std::vector<Int_t> normalIndex; 
            normalIndex.push_back((*face_binding_iter).fNormalIndex);
            ::MakeShape(shapeFaces, *face_binding_iter,normalIndex);
            // ::MakeShape(shapeLine,  *face_binding_iter,normalIndex);
        }
     }
#ifdef OWNNORMALS
      ::AddNormals(*shapeNormal,normals);
      shapeGroup->addChild(shapeNormal);
#endif
      ::AddCoordinates(*shapeVertices,vertices);
      shapeGroup->addChild(shapeVertices);
      
           if (shapeFaces) shapeGroup->addChild(shapeFaces);
      else if (shapeLine ) shapeGroup->addChild(shapeLine );
      else if (shapePoint) shapeGroup->addChild(shapePoint);
//--
//--   Vertex binding Face Sets
//
      if (shapeView.fPolygonsVertexBinding.size() ) {
         shapeGroup->addChild(SetCurrentColor(rgba,true));
         SoShapeHints *hints   = new SoShapeHints;
         hints->shapeType      = SoShapeHints::SOLID;
         hints->vertexOrdering.setIgnored(TRUE);
         hints->creaseAngle    = 3.1415926;
         shapeGroup->addChild(hints);
         SoNormalBinding *binding = new SoNormalBinding();
         binding->value = SoNormalBindingElement::PER_VERTEX;
         shapeGroup->addChild(binding);
         shapeVertexFaces = new SoIndexedFaceSet();
         // loop over to created the indexed set
         std::vector <TPolygone3DVertexBindingView>::const_iterator vertex_binding_iter = shapeView.fPolygonsVertexBinding.begin();;
         for (; vertex_binding_iter != shapeView.fPolygonsVertexBinding.end(); ++vertex_binding_iter) {
             // fprintf(stderr, " fPolygonsVertexBinding  %d\n",++testCounter);
            ::MakeShape(shapeVertexFaces, *vertex_binding_iter,(*vertex_binding_iter).fNormalIndices);
         }
         shapeGroup->addChild(shapeVertexFaces);
     }
     return view;
}
//____________________________________________________________________________________________________________________
void TObjectCoinViewFactory::AddNormal(TObject3DView *, const Double_t * /*normal*/ )
{ }

//____________________________________________________________________________________________________________________
TObject3DView *TObjectCoinViewFactory::BeginModel(TObject3DView *rootView)
{
   if (rootView) {}
   TObject3DView *view = new TObject3DView(this);
   SoSeparator *separator = new SoSeparator();
   separator->setName(rootView->GetTitle());
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
         rot = new SoMatrixTransform();
         rot->matrix.setValue(   rotation[0] , rotation[ 1] , rotation[ 2] , 0.
                               , rotation[3] , rotation[ 4] , rotation[ 5] , 0.
                               , rotation[6] , rotation[ 7] , rotation[ 8] , 0.
                               ,     0.      ,     0.       ,     0.       , 1.  );
         if (isReflection)
            rot->setName("reflection");
         else
            rot->setName("stright");
      }

      if ( trans || rot ) {
         view =  OpenView(this);  
         SoGroup *shapeGroup = (SoGroup *) view->GetViewId();
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
   SetView(view , new SoTransformSeparator() );
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
#if 0      
      SoGroup *id = 0;
      if ( (id = (SoGroup *)view->GetViewId()) )  
         id->unref();
      if ( (id = (SoGroup *)view->GetViewId(TObject3DViewFactoryABC::kSelectable)) ) 
         id->unref();
      if ( (id = (SoGroup *)view->GetViewId(TObject3DViewFactoryABC::kSelected))  ) 
         id->unref();
#endif
   }
}

