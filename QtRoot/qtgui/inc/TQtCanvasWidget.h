// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtCanvasWidget.h,v 1.3 2007/05/22 01:05:23 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_QtCanvasWidget
#define ROOT_QtCanvasWidget

#include <qmainwindow.h> 

class  TQtCanvasWidget : public QMainWindow {
 Q_OBJECT
public:
  TQtCanvasWidget( QWidget* parent=0, const char* name=0, Qt::WFlags f=Qt::WDestructiveClose|Qt::WType_TopLevel);
  virtual ~TQtCanvasWidget(){;}
 
protected slots:
  virtual bool ExitSizeEvent(int updt);
  void   ChangeDocking(bool);

#ifdef WIN32
protected:
  //  Some WIN32 optimization. It will work with out these methods too.
  virtual bool winEvent(MSG *msg);
#endif

};

#endif
