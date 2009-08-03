// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtUtil.h,v 1.2 2009/08/03 18:02:57 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtUTIL
#define ROOT_TQtUTIL

#include "TGQt.h"
#include "TCanvas.h"
#include "TCanvasImp.h"

#include <QtGui/QPixmap>
#include <QtGui/QWidget>

//----------------------------------------
//      Q: How to get Qt pointer:
//----------------------------------------
namespace  TQtUtil {
//_______________________________________
inline QPixmap *padPixmap(TPad *pad)
{     return (QPixmap *)TGQt::iwid(pad->GetPixmapID());   }
//_______________________________________
inline QWidget *canvasWidget(TCanvas *c)
{  return (QWidget *)TGQt::iwid(c->GetCanvasID()) ; }
#if 0
//_______________________________________
inline QWidget *canvasWidget(TCanvasImp *c)
{ return (QWidget *) TGQt::iwid(((TQtCanvasImp *)c)->GetCanvasImpID()); }
//_______________________________________
inline QWidget *mainWidget(TCanvas *c)
{  return canvasWidget(c->GetCanvasImp());}
#endif

//----------------------------------------
// Q: Get WIN32/X11 handles:
//    (see function above and Qt manual also)
//----------------------------------------
//_______________________________________
inline unsigned long  wigdetHdc(TPad *pad)
{  return padPixmap(pad)->handle(); }

//_______________________________________
inline unsigned long  hwndWin32(TCanvas *c)
{  return canvasWidget(c)->winId(); }
};
#endif

