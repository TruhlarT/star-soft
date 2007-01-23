// @(#)root/qt:$Name:  $:$Id: TQtTimer.h,v 1.3 2007/01/23 17:53:37 fine Exp $
// Author: Valeri Fine   09/08/2004
/****************************************************************************
**
** Copyright (C) 2004 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtTimer
#define ROOT_TQtTimer

#include "Rtypes.h"

#ifndef __CINT__
#  include <qtimer.h>
#else
  class QTimer;
#endif

//
// TQtTimer is a singelton QTimer to awake the ROOT event loop from Qt event loop
//

//___________________________________________________________________
class  TQtTimer : public QTimer  {
#ifndef __CINT__    
     Q_OBJECT
#endif
private:
	 void operator=(const TQtTimer &);
    TQtTimer(const TQtTimer &);
protected:
  static TQtTimer *fgQTimer;
  int fCounter;     
  TQtTimer (QObject *parent=0, const char *name=0): QTimer(parent,name),fCounter(0){}
  
protected slots:
  virtual void AwakeRootEvent();
 
public:
  virtual ~TQtTimer(){}
  static TQtTimer *Create(QObject *parent=0, const char *name=0);
  static TQtTimer *QtTimer();
  ClassDef(TQtTimer,0) // QTimer to awake the ROOT event loop from Qt event loop
};
inline TQtTimer *TQtTimer::QtTimer(){ return fgQTimer; }


#endif
