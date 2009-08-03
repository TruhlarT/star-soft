#ifndef ROOT_TQTUPDATEVIEWFLAG
#define ROOT_TQTUPDATEVIEWFLAG
// Author: Valeri Fine   30/04/2003
/****************************************************************************
** $Id: TQtUpdateViewFlag.h,v 1.3 2009/08/03 18:03:09 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/
#include <qglobal.h>
#if QT_VERSION < 0x40000
#include <qscrollview.h> 
#else /* QT_VERSION */
#include <q3scrollview.h> 
#endif /* QT_VERSION */

/////////////////////////////////////////////////////////////
//                                                         //
//  Small counter class to avoid redundant lock/ unlock    //
//  Scrollview to update                                   //
//                                                         //
/////////////////////////////////////////////////////////////
class TQtUpdateViewFlag {
private:
   unsigned int  fCounter;
   TQtUpdateViewFlag(const TQtUpdateViewFlag &){;}
public:
   TQtUpdateViewFlag(): fCounter (0){};
#if QT_VERSION < 0x40000
   void FreezeToUpdate(QScrollView *view){
#else /* QT_VERSION */
   void FreezeToUpdate(Q3ScrollView *view){
#endif /* QT_VERSION */
      if (!fCounter) {
         view->setUpdatesEnabled( FALSE );
         view->viewport()->setUpdatesEnabled( FALSE );
      }
      fCounter++;
   };

#if QT_VERSION < 0x40000
   void UnFreezeToUpdate(QScrollView *view){ 
#else /* QT_VERSION */
   void UnFreezeToUpdate(Q3ScrollView *view){ 
#endif /* QT_VERSION */
      if (fCounter) fCounter--; 
      if (!fCounter) {
         view->viewport()->setUpdatesEnabled( TRUE );
         view->setUpdatesEnabled( TRUE );
         view->repaintContents();
      }
   }
};

#endif


