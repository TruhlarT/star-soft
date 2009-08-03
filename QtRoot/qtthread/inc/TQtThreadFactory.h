// @(#)root/thread:$Name:  $:$Id: TQtThreadFactory.h,v 1.2 2009/08/03 18:03:11 fine Exp $
// $Id: TQtThreadFactory.h,v 1.2 2009/08/03 18:03:11 fine Exp $
// Author: Valery Fine  08/25/2005
/****************************************************************************
** Copyright (C) 2005 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/
 
#ifndef ROOT_TQtThreadFactory
#define ROOT_TQtThreadFactory

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TQtThreadFactory                                                     //
//                                                                      //
// This is a factory for Qt thread components.                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TThreadFactory
#include "TThreadFactory.h"
#endif

class TMutexImp;
class TConditionImp;
class TThreadImp;


class TQtThreadFactory : public TThreadFactory {

public:
   TQtThreadFactory(const char *name = "Qt", const char *title = "Qt Thread Factory");
   virtual ~TQtThreadFactory() { }

   virtual TMutexImp      *CreateMutexImp();
   virtual TConditionImp  *CreateConditionImp(TMutexImp *m);
   virtual TThreadImp     *CreateThreadImp();

   ClassDef(TQtThreadFactory,0)  // Qt thread factory
};

#endif
