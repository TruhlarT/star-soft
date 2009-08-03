// @(#)root/thread:$Name:  $:$Id: TQtMutex.h,v 1.2 2009/08/03 18:03:11 fine Exp $
// $Id: TQtMutex.h,v 1.2 2009/08/03 18:03:11 fine Exp $
// Author: Valery Fine  08/25/2005
/****************************************************************************
** Copyright (C) 2005 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#ifndef ROOT_TQtMutex
#define ROOT_TQtMutex


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtMutex                                                          //
//                                                                      //
// This class provides an interface to the Win32 mutex routines.        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TMutexImp
#include "TMutexImp.h"
#endif

class QMutex;

class TQtMutex : public TMutexImp {

friend class TQtCondition;

private:
   QMutex *fMutex;

public:
   TQtMutex();
   virtual ~TQtMutex();

   Int_t  Lock();
   Int_t  UnLock();
   Int_t  TryLock();
// 
   const QMutex *Mutex() const;
   QMutex *Mutex();
   ClassDef(TQtMutex,0)  // Qt mutex lock
};

inline  const QMutex *TQtMutex::Mutex() const { return fMutex; }
inline        QMutex *TQtMutex::Mutex()       { return fMutex; }

#endif
