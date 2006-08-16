// @(#)root/base:$Name:  $:$Id: TQVirtualGL.cxx,v 1.1 2006/08/16 19:38:50 fine Exp $
// Author: Valery Fine(fine@vxcern.cern.ch)   05/03/97

//______________________________________________________________________________
//*-*-*-*-*-*-*-*-*-*-*-* TQVirtualGL class *-*-*-*-*-*-*-*-*-*-*-*-*
//*-*                     ================
//*-*
//*-*   TGLKernel class defines the interface for OpenGL commands and utilities
//*-*   Those are defined with GL/gl and GL/glu include directories
//*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "RVersion.h"
#if ROOT_VERSION_CODE >= ROOT_VERSION(4,01,00)
//  This class was relocated from ROOT 4.00.08 g3g package

#include "TQVirtualGL.h"

TQVirtualGL *gQVirtualGL=0;

//____________________________________________________________________________
TQVirtualGL::TQVirtualGL()
{
   fColorIndx     = 0;
   fRootLight     = kFALSE;
   fTrueColorMode = kFALSE;
   fFaceFlag      = kCCW;
}
#endif
