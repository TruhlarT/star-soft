// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtCanvasWidget.cxx,v 1.7 2008/04/21 16:12:50 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

// Definition of TQtWinget class
// "double-buffere widget

#include "TQtCanvasWidget.h"
#include "TQtWidget.h"
#include "TROOT.h"
#include "TCanvasImp.h"
#include "TCanvas.h"
#include "Buttons.h"
#include "qevent.h"
#include "qpainter.h"
#include "qapplication.h"

#ifdef WIN32
#include "Windows4Root.h"
#endif

//_____________________________________________________________________________
TQtCanvasWidget::TQtCanvasWidget(QWidget* parent, const char* name, Qt::WFlags f)
          :QMainWindow(parent,name,f)
{ 
#if QT_VERSION < 0x40000
   setWFlags(getWFlags () | Qt::WDestructiveClose);
#else
//   setAttribute(Qt::WA_DeleteOnClose);
#endif
}
//_____________________________________________________________________________
void TQtCanvasWidget::ChangeDocking(bool)
{ 
   // The change of the docking may have lead to the TCanvas size change also
   // We should attempt to resize the TCanvas
   // adjustSize();
   ExitSizeEvent(TQtWidget::kFORCESIZE);
   update();
}
//_____________________________________________________________________________
bool TQtCanvasWidget::ExitSizeEvent (int update)
{
  // Disable update during resizing (for the sake of the optimization) 
  QWidget *w = centralWidget();
  if (!w) return FALSE;

  QApplication::sendEvent(w,new QCustomEvent(int(QEvent::User+update)) );
  
  return TRUE;
}

#ifdef R__WIN32
//_____________________________________________________________________________
bool TQtCanvasWidget::winEvent ( MSG *msg )
{
   // QT 3.x compliand version of the method
   long result;
   return winEvent ( msg , &result);
}
//_____________________________________________________________________________
bool    TQtCanvasWidget::winEvent ( MSG *msg , long * result )
{
   // In your reimplementation of this function, if you want to stop the event 
   // being handled by Qt, return TRUE. If you return FALSE, this native event
   // is passed back to Qt, which translates the event into a Qt event and sends
   // it to the widget. 
  bool res = FALSE;
  switch ( msg->message ) {

  case WM_ENTERSIZEMOVE: { res = ExitSizeEvent(TQtWidget::kENTERSIZEMOVE); break;}
  case WM_EXITSIZEMOVE:  { res = ExitSizeEvent(TQtWidget::kEXITSIZEMOVE);  break;}

  default: break;
  };
  *result = 0;
  return res;
}
#endif
