// @(#)root/base:$Name:  $:$Id: TVirtualViewer3D.cxx
// Author: Olivier Couet 05/10/2004

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TObject3DViewFactoryABC                                              //
//                                                                      //
// Abstract 3D shapes viewer. The concrete implementations are:         //
//                                                                      //
// TViewerX3D   : X3d viewer                                            //
// TViewerOpenGL: OpenGL viewer                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#if 0
#  include "TObject3DViewFactoryABC.h"
#else
#  include "TObjectOpenGLViewFactory.h"
#endif

#include <assert.h>

#include "TROOT.h"
#include "TPluginManager.h"
#include "TError.h"

std::map<TString, TObject3DViewFactoryABC *> TObject3DViewFactoryABC::gfMap;
TObject3DViewFactoryABC *g3DFactory=0;
ClassImp(TObject3DViewFactoryABC)
//______________________________________________________________________________
void TObject3DViewFactoryABC::DestroyCurrentView3DFactory(Option_t * /* type */ ) 
{
   assert(0);
}
//______________________________________________________________________________
TObject3DViewFactoryABC* TObject3DViewFactoryABC::View3DFactory(Option_t *type)
{
 //  Create a Viewer 3D of specified type
//   TObject3DViewFactoryABC *factory = gfMap.find(TString(type)); 
//   if (!factory) {
   if (!g3DFactory) {
#if 0
      TPluginHandler *h;
      if ((h = gROOT->GetPluginManager()->FindHandler("TObject3DViewFactoryABC", type))) {
         if (h->LoadPlugin() == -1) return 0;    
         factory  = (TObject3DViewFactoryABC *) h->ExecPlugin(0); 
         typedef std::pair <TString, TObject3DViewFactoryABC *> FACTORY_PAIR;
         TString factoryName(type); 
         gfMap.insert(FACTORY_PAIR(factoryName,factory));
      }
#else
         g3DFactory  = new TObjectOpenGLViewFactory();
//         typedef std::pair <TString, TObject3DViewFactoryABC *> FACTORY_PAIR;
//         TString factoryName(type); 
//         gfMap.insert(FACTORY_PAIR(factoryName,factory));
#endif
   }
   return g3DFactory;
}
