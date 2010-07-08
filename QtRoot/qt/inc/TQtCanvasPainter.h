// $Id: TQtCanvasPainter.h,v 1.1 2010/07/08 04:19:45 fine Exp $
// Author: Valeri Fine   21/05/2010

#ifndef ROOT_TQTCANVASPAINTER
#define ROOT_TQTCANVASPAINTER

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// TQtCanvasPainter                                                        //
//                                                                         //
// TQtCanvasPainter is abstract visitor interface                          //
// to customize TQtWidget painting                                         //
// It allows the arbitrary low level Qt painting onto the TQtWidget face   //
// on the top of  TCanvas image                                            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <QtCore/QObject>

class TQtCanvasPainter : public QObject 
{
    protected:
       TQtCanvasPainter(){}
    public:
       TQtCanvasPainter(QObject *mother) : QObject(mother) {}
       virtual ~TQtCanvasPainter() {}
       virtual void paintEvent(QPainter &painter, QPaintEvent *e=0) = 0;
//     ClassDef(TQtCanvasPainter,0); // Interface to use the Qt graphics to custom paint over ROOT TCanvas 
};

#endif
