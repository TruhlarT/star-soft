#ifndef ROOT_TQUserEvent
#define ROOT_TQUserEvent

#include <qglobal.h>
#if QT_VERSION < 0x40000
  #include <event.h>
#endif /* QT_VERSION */
#include "GuiTypes.h"

class TQUserEvent : public 
#if QT_VERSION < 0x40000
   QCustomEvent 
#else
   QEvent 
#endif
{
#if QT_VERSION >= 0x40000
private:
   Event_t *fEvent;
#endif 
public:
#if QT_VERSION >= 0x40000
   Event_t *data() const { return fEvent;}
   void setData(Event_t *ev) { delete data(); fEvent=ev;}
   TQUserEvent(const Event_t &pData) : QEvent(Type(QEvent::User+Type(1)))
#else
   TQUserEvent(const Event_t &pData) : QCustomEvent(Id(),0)
#endif
   {   setData(new Event_t); *(Event_t *)data() = pData;  }
   ~TQUserEvent() { delete (Event_t *)data(); }
   void getData( Event_t &user) const { user = *(Event_t*)data(); }
   static Type Id() { return Type(QEvent::User + Type(1) /*kQTGClientEvent*/) ;}
};

#endif
