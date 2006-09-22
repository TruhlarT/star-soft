// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtCanvasWidget.h,v 1.2 2006/09/22 17:27:10 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_QtCanvasWidget
#define ROOT_QtCanvasWidget

#include <qglobal.h> 
#if (QT_VERSION < 0x40000)
#  include <qmainwindow.h> 
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
#  include <q3mainwindow.h> 
//MOC_SKIP_END
#endif /* QT_VERSION */

#if (QT_VERSION < 0x40000)
class  TQtCanvasWidget : public QMainWindow {
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
class  TQtCanvasWidget : public Q3MainWindow {
//MOC_SKIP_END
#endif /* QT_VERSION */
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
