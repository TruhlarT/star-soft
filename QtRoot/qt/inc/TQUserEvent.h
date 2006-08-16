#ifndef ROOT_TQUserEvent
#define ROOT_TQUserEvent

#include <qevent.h>
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#include <QCustomEvent>
#endif /* QT_VERSION */
#include "GuiTypes.h"

class TQUserEvent : public QCustomEvent {
public:
   TQUserEvent(const Event_t &pData) : QCustomEvent(Id(),0)
   {   setData(new Event_t); *(Event_t *)data() = pData;  }
   ~TQUserEvent() {delete (Event_t *)data(); }
   void getData( Event_t &user) const { user = *(Event_t*)data(); }
   static Type Id() { return Type(QEvent::User + 1 /*kQTGClientEvent*/) ;}
};

#endif
