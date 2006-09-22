// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtRootAction.h,v 1.2 2006/09/22 17:27:10 fine Exp $
**
** Copyright (C) 2003 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtRootAction
#define ROOT_TQtRootAction

#include <qglobal.h>
#if QT_VERSION < 0x40000
#  include <qaction.h>
#  define ROOT_QT_ACTION QAction
#else
#  include <Q3Action>
#  define ROOT_QT_ACTION Q3Action
#endif
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtRootAction                                                        //
//                                                                      //
// QAction Qt class to build ROOT-related menu and tool bars     .      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// Structure to initialize the QAction class
struct TQtBrowserMenuItem_t  {
   const char *fMenuText;
   int         fId;
   int         fAccelerator;
   const char *fToolTip;
   const char *iconName;
};  

class TQtRootAction : public ROOT_QT_ACTION {
  public:
    TQtRootAction(QObject * parent, const TQtBrowserMenuItem_t  &data, const char * name = 0);
    int Id() const { return fId; }
  private:
     int  fId;
};
#undef ROOT_QT_ACTION
#endif
