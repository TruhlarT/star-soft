// @(#)root/qt:$Id: TQtMarker.cxx,v 1.4 2008/04/16 00:59:20 fine Exp $
// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtMarker.cxx,v 1.4 2008/04/16 00:59:20 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#include "TQtRConfig.h"
#include "TQtMarker.h"
#if QT_VERSION >= 0x40000
#  include <QPolygon>
#endif /* QT_VERSION */

ClassImp(TQtMarker)

////////////////////////////////////////////////////////////////////////
//
// TQtMarker - class-utility to convert the ROOT TMarker object shape 
//             in to the Qt QPointArray.
//
////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
TQtMarker::TQtMarker(int n, TPoint *xy, int type) : fNumNode(n),
               fChain(0), fCindex(0), fMarkerType(type)
{
  if (type >= 2) {
#if defined(R__QTWIN32) && (QT_VERSION < 0x40000)
     fChain.setPoints(n,(QCOORD *)xy);
#else
     fChain.resize(n);
     TPoint *rootPoint = xy;
     for (int i=0;i<n;i++,rootPoint++)
        fChain.setPoint(i,rootPoint->fX,rootPoint->fY);
#endif
  }
}
//______________________________________________________________________________
TQtMarker::~TQtMarker(){}
//______________________________________________________________________________
int    TQtMarker::GetNumber() const {return fNumNode;}
//______________________________________________________________________________
#if QT_VERSION < 0x40000
QPointArray &TQtMarker::GetNodes() {return fChain;}
#else /* QT_VERSION */
QPolygon &TQtMarker::GetNodes() {return fChain;}
#endif /* QT_VERSION */
//______________________________________________________________________________
int  TQtMarker::GetType() const {return fMarkerType;}

//______________________________________________________________________________
void TQtMarker::SetMarker(int n, TPoint *xy, int type)
{
//*-* Did we have a chain ?
  fNumNode = n;
  fMarkerType = type;
  if (fMarkerType >= 2) {
#if defined(R__QTWIN32) && (QT_VERSION < 0x40000)
    fChain.setPoints(n,(QCOORD *)xy);
#else
    fChain.resize(n);
    TPoint *rootPoint = xy;
    for (int i=0;i<n;i++,rootPoint++)
       fChain.setPoint(i,rootPoint->fX,rootPoint->fY);
#endif

  }
}
