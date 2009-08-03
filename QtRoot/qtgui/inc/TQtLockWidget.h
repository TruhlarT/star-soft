// @(#)root/gui:$Name:  $:$Id: TQtLockWidget.h,v 1.3 2009/08/03 18:03:08 fine Exp $
// Author: Valeri Fine 07/07/2006

#ifndef ROOT_TQtLockWidget
#define ROOT_TQtLockWidget

#include <qobject.h>

#if QT_VERSION < 0x40000
#  include <qguardedptr.h> 
#  include <qwidget.h>
#else
#  include <QPointer>
#  include <QWidget>
#endif 


// Class to block the widget signal and update
class TQtLockWidget {
  private:
#if QT_VERSION < 0x40000
     QGuardedPtr<QWidget> fWidget; //  Widget to lock
#else
     QPointer<QWidget>    fWidget; //  Widget to lock
#endif
     bool                 fWasEnabled;
     bool                 fWasBlocked;
  public:
     TQtLockWidget(QWidget *w) : fWidget(w)
        , fWasEnabled(FALSE), fWasBlocked(FALSE)
         {
            if (fWidget) {
               if (( fWasEnabled = w->isEnabled()) )
                  fWidget->setUpdatesEnabled(!fWasEnabled);
               if (!(fWasBlocked=w->signalsBlocked())) 
                  fWidget->blockSignals(!fWasBlocked);
            }
         }
     ~TQtLockWidget() {
        if (fWidget) {
           if (fWasEnabled)  fWidget->setUpdatesEnabled(fWasEnabled);
           if (!fWasBlocked) fWidget->blockSignals(fWasBlocked) ;
        }
     }
};

#endif
