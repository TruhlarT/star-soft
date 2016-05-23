// @(#)root/thread:$Name:  $:$Id: TQtCondition.h,v 1.3.4.1 2016/05/23 18:33:09 jeromel Exp $
// $Id: TQtCondition.h,v 1.3.4.1 2016/05/23 18:33:09 jeromel Exp $
// Author: Valery Fine  08/25/2005
/****************************************************************************
** Copyright (C) 2005 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#ifndef ROOT_TQtCondition
#define ROOT_TQtCondition


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtCondition                                                      //
//                                                                      //
// This class provides an interface to the win32 condition variable     //
// routines.                                                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TConditionImp
#include "TConditionImp.h"
#endif

class TMutexImp;
class QMutex;
class QWaitCondition;


class TQtCondition : public TConditionImp {

private:
   QWaitCondition  *fCond;
   QMutex         &fMutex;    // mutex used around Wait() and TimedWait()

public:
   TQtCondition(TMutexImp *m);
   virtual ~TQtCondition();

   Int_t  Wait();
   Int_t  TimedWait(ULong_t secs, ULong_t nanoSecs = 0);
   Int_t  Signal();
   Int_t  Broadcast();

   ClassDef(TQtCondition,0)   // Posix condition variable
};

#endif
