#ifndef ROOT_TQtMarkerSelectButton
#define ROOT_TQtMarkerSelectButton

#include "Gtypes.h"
#include <TObject.h>
#include <TQObject.h>

#include <qpoint.h>
#include <qtoolbutton.h>
#include <qobject.h>
#include <qpopupmenu.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
// TQtMarkerFrame                                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////
class TQtMarkerFrame : public QToolButton {
Q_OBJECT

private :

   Style_t   fStyle;  // each pixmap is associated to a Style_t value
   QPixmap   fPixmap;

public :
   TQtMarkerFrame ( QWidget *p, const char * name, Style_t style );
   virtual ~TQtMarkerFrame(){}

   void SetStyle ( const Style_t & style );
   const Style_t & GetStyle ( ) const { return fStyle ; }

protected slots :
   void clickedSlot () { emit selected(this); }

signals :
   void selected ( TQtMarkerFrame * selectedMarkerFrame );
}; // class TQtMarkerFrame


/////////////////////////////////////////////////////////////////////////////////////////////////
// TQt18MarkerSelector                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////
class TQt18MarkerSelector : public QPopupMenu {
Q_OBJECT

public :
   TQt18MarkerSelector( QWidget *p, const char * name );
   virtual ~TQt18MarkerSelector(){}
   void showSelector ( const QPoint & position );

protected slots :
   void selectedSlot ( TQtMarkerFrame * selectedMarkerFrame );

signals :
   void selected ( TQtMarkerFrame * selectedMarkerFrame );

}; // class TQt18MarkerSelector

#endif // #ifndef ROOT_TQtMarkerSelectButton
