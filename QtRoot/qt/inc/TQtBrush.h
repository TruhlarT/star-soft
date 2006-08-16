// @(#)root/qt:$Name:  $:$Id: TQtBrush.h,v 1.1 2006/08/16 19:29:07 fine Exp $
// Author: Valeri Fine   21/01/2002
/****************************************************************************
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtBrush
#define ROOT_TQtBrush

#ifndef __CINT__
#  include <qbrush.h>
#  include <qcolor.h>
#  include <qpixmap.h>
#else
   class  QColor;
   class  QBrush;
   class  QPixmap;
#endif

#include "Rtypes.h"
   //
   // TQtBrush creates the QBrush Qt object based on the ROOT "fill" attributes 
   //
class TQtBrush : public QBrush
{
protected:
  QColor fBackground;
  int fStyle;
  int fFasi;
#ifdef R__WIN32
  QPixmap fCustomPixmap; // shadow transparent pixmap fro WIN32
#endif
public:
   TQtBrush();
   TQtBrush(const TQtBrush &src):QBrush(src)
   {
      fBackground=src.fBackground;
      fStyle=src.fStyle;
      fFasi=src.fFasi;
   }
   virtual ~TQtBrush(){;}
   void SetStyle(int style=1000){  SetStyle(style/1000,style%1000); };
   void SetStyle(int style, int fasi);
   void SetColor(const QColor &color);
   const QColor &GetColor() const { return fBackground;}
   int   GetStyle()         const { return 1000*fStyle + fFasi; }
   ClassDef(TQtBrush,0); // create QBrush object based on the ROOT "fill" attributes 
};

#endif
