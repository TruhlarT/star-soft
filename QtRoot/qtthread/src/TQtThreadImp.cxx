// @(#)root/thread:$Name:  $:$Id: TQtThreadImp.cxx,v 1.3 2009/08/03 18:03:11 fine Exp $
// $Id: TQtThreadImp.cxx,v 1.3 2009/08/03 18:03:11 fine Exp $
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
// TQtThreadImp                                                         //
//                                                                      //
// This class provides an interface to the Qt QThread class             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// ------------------------------
//
//  The workaroung to provide the Qt thread fro the previous version of ROOT
// unless the class will be introduced as a legal friend officially by Fons :)
//
#define TWin32Thread TWin32Thread; friend class TQtThreadImp; friend class TRootThread;
#include "TQtThreadImp.h"
#undef TWin32Thread
// ------------------------------
#include <qthread.h>

class TRootThread : public QThread {
  private:
    TThread *fROOTTHread;
  public:
     TRootThread(TThread *thread) : fROOTTHread(thread) {}
     virtual ~TRootThread() {
        fROOTTHread->fHandle = 0L;
     }
     virtual void run() { 
           fROOTTHread->fId = (Long_t)QThread::currentThread();
           TThread::Function(fROOTTHread); 
     }
};
class TCancelThread : public QThread {
   private:
     TCancelThread() {};
   public:
     ~TCancelThread() {};
   void SetCancel(Bool_t on=kTRUE) {
#if (QT_VERSION >= 0x040000)
      setTerminationEnabled(on);
#endif      
   }               
};

ClassImp(TQtThreadImp)

//______________________________________________________________________________
Int_t TQtThreadImp::Run(TThread *th)
{
   // Qt threads -- spawn new thread (like pthread_create).
   // Qt has a thread QThread pointer in addition to the thread ID.

   QThread *thread = new  TRootThread(th);
   th->fHandle = (Long_t)thread;
   const QThread::Priority Root2QtMap[] = {QThread::LowPriority,QThread::InheritPriority,QThread::HighPriority};
   thread->start(Root2QtMap[th->fPriority]);
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::Join(TThread *th, void ** /*ret*/)
{
   // Wait for specified thread execution (if any) to complete
   // (like pthread_join).
   QThread *qt = ((QThread*)th->fHandle);
   if (qt) qt->wait();
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::Exit(void * /*ret*/)
{
   // Exit the thread.

#if (QT_VERSION < 0x040000)
   QThread::exit();
#else   
   QThread *qt = QThread::currentThread();
   if (qt) qt->quit();
#endif   
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::Kill(TThread *th)
{
   // This is a somewhat dangerous function; it's not
   // suggested to Stop() threads a lot.
      
   QThread *qt = ((QThread*)th->fHandle);
   if (qt) { qt->terminate();  qt->wait(); delete qt; }
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::CleanUpPush(void **main, void *free,void *arg)
{
   if (!free) fprintf(stderr, "CleanUpPush ***ERROR*** Routine=0\n");
   new TQtThreadImpCleanUp(main,free,arg);
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::CleanUpPop(void **main,Int_t exe)
{
   if (!*main) return 1;
   TQtThreadImpCleanUp *l = (TQtThreadImpCleanUp*)(*main);
   if (!l->fRoutine) fprintf(stderr,"CleanUpPop ***ERROR*** Routine=0\n");
   if (exe && l->fRoutine) ((void (*)(void*))(l->fRoutine))(l->fArgument);
   *main = l->fNext;  delete l;
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::CleanUp(void **main)
{
   fprintf(stderr," CleanUp %lx\n",(ULong_t)*main);
   while(!CleanUpPop(main,1)) { }
   return 0;
}

//______________________________________________________________________________
Long_t TQtThreadImp::SelfId()
{
   // Return the current thread's ID.

   return (Long_t)QThread::currentThread();
}

//______________________________________________________________________________
Int_t TQtThreadImp::SetCancelOff()
{
#if (QT_VERSION < 0x040000)
   if (gDebug)
      Warning("SetCancelOff", "Not implemented on Qt");
#else
   QThread *qt = QThread::currentThread();
   if (qt) ((TCancelThread *)qt)->SetCancel(kFALSE);
#endif      
   
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::SetCancelOn()
{
#if (QT_VERSION < 0x040000)
   if (gDebug)
      Warning("SetCancelOn", "Not implemented on Qt ");
#else
   QThread *qt = QThread::currentThread();
   if (qt) ((TCancelThread *)qt)->SetCancel();
#endif      
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::SetCancelAsynchronous()
{
   if (gDebug)
      Warning("SetCancelAsynchronous", "Not implemented on Qt");
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::SetCancelDeferred()
{
   if (gDebug)
      Warning("SetCancelDeferred", "Not implemented on Qt");
   return 0;
}

//______________________________________________________________________________
Int_t TQtThreadImp::CancelPoint()
{
   if (gDebug)
      Warning("CancelPoint", "Not implemented on Qt");
   return 0;
}

//   Clean Up section. PTHREAD implementations of cleanup after cancel are
//   too different and often too bad. Temporary I invent my own bicycle.
//                                                              V.Perev.

//______________________________________________________________________________
TQtThreadImpCleanUp::TQtThreadImpCleanUp(void **main, void *routine, void *arg)
{
   fNext = (TQtThreadImpCleanUp*)*main;
   fRoutine = routine; fArgument = arg;
   *main  = this;
}
