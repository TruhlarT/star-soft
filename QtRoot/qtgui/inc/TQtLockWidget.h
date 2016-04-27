// @(#)root/gui:$Name:  $:$Id: TQtLockWidget.h,v 1.3.2.1 2016/04/27 16:45:49 jeromel Exp $
// Author: Valeri Fine 07/07/2006

#ifndef ROOT_TQtLockWidget
#define ROOT_TQtLockWidget

#include <QObject>

#include <QPointer>
#include <QWidget>


// Class to block the widget signal and update
class TQtLockWidget {
  private:
     QPointer<QWidget>    fWidget; //  Widget to lock
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
