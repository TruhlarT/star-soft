// Author: Valeri Fine   16/06/2006
/****************************************************************************
** $Id: TQtToolBar.h,v 1.1 2006/08/16 19:33:21 fine Exp $
**
** Copyright (C) 2006 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtToolBar
#define ROOT_TQtToolBar

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtToolBar                                                           //
//                                                                      //
// This class creates a main window with menubar, scrollbars and a      //
// drawing area.                                                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#if QT_VERSION < 0x40000
#  include <qintdict.h>
#  include <qtoolbar.h>
#else /* QT_VERSION */
#  include <q3intdict.h>
#  include <q3toolbar.h>
#endif

#if QT_VERSION < 0x40000
#define TOOLBARCLASSNAME QToolBar
#else /* QT_VERSION */
#define TOOLBARCLASSNAME Q3ToolBar
#endif /* QT_VERSION */

class QMainWindow;
class TQtRootAction;
class TQtBrowserMenuItem_t;
class TQtRootAction;

class TQtToolBar : public TOOLBARCLASSNAME {

Q_OBJECT

private:
#if QT_VERSION < 0x40000
   QIntDict<TQtRootAction> fActions;
#else /* QT_VERSION */
   Q3IntDict<TQtRootAction> fActions;
#endif /* QT_VERSION */

public:

   TQtToolBar(const QString &label, QMainWindow *mainWindow, QWidget *parent, bool newLine=FALSE, const char *name=0,Qt::WFlags f=0);
   TQtToolBar(QMainWindow *parent, const char *name=0);
   virtual ~TQtToolBar();
   void AddAction(const TQtBrowserMenuItem_t &action);
   void AddAction(TQtRootAction *action);

protected:
   void  Build();

protected slots:
   void ProcessToolMessage();

   // ClassDef(TQtToolBar,0)  // Class to provide the ROOT tool bar
};

#endif
