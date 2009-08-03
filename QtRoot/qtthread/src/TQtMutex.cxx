// @(#)root/thread:$Name:  $:$Id: TQtMutex.cxx,v 1.2 2009/08/03 18:03:11 fine Exp $
// $Id: TQtMutex.cxx,v 1.2 2009/08/03 18:03:11 fine Exp $
// Author: Valery Fine  08/25/2005
/****************************************************************************
** Copyright (C) 2005 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtMutex                                                             //
//                                                                      //
// This class provides an interface to the Win32 mutex routines.        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TThread.h"
#include "TQtMutex.h"
#include <qmutex.h>

ClassImp(TQtMutex)

//______________________________________________________________________________
TQtMutex::TQtMutex()
{
   // Create a Qt mutex lock.

   fMutex = new QMutex();
}

//______________________________________________________________________________
TQtMutex::~TQtMutex()
{
   // TMutex dtor.

  QMutex *m = fMutex; fMutex=0; delete m;
}

//______________________________________________________________________________
Int_t TQtMutex::Lock()
{
   // Lock the mutex.
   if (fMutex) fMutex->lock();
   return 0;
}

//______________________________________________________________________________
Int_t TQtMutex::TryLock()
{
   // Try locking the mutex. Returns 0 if mutex can be locked.

   Int_t locked = 1;
   if (fMutex && fMutex->tryLock()) locked = 0;
   return locked;
}

//______________________________________________________________________________
Int_t TQtMutex::UnLock(void)
{
   // Unlock the mutex.

   if (fMutex) fMutex->unlock();
   return 0;
}
