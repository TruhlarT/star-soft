#include "TQtMarkerSelect.h"
#include "TQtMarkerSelectButton.h"

#include "TQtRootAction.h"
#include <qstring.h>


#if QT_VERSION < 0x40000
#define  QBUTTONGROUP QButtonGroup
#include <qbuttongroup.h>

#else /* QT_VERSION */
#define  QBUTTONGROUP Q3ButtonGroup
#include <q3buttongroup.h>
#endif /* QT_VERSION */

#include <qhbox.h>

ClassImp( TQtMarkerSelect )

/////////////////////////////////////////////////////////////////////////////////////////////////
// TQtMarkerSelect                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////
TQtMarkerSelect::TQtMarkerSelect ( QWidget * p, const char * name, Style_t style )
   : fSelected(0),
     fPopup   (0)
{
   //QBUTTONGROUP *group =  new  QBUTTONGROUP (2, Qt::Horizontal , p, "markerGroup");
   //group->setSizePolicy(QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed ));

   QHBox * hbox = new QHBox(p);
   hbox->setMargin (0);
   hbox->setSpacing(0);
   hbox->setSizePolicy(QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Minimum ));

                 fSelected = new TQtMarkerFrame (hbox,"selectedMarker",style);
   QToolButton * arrow     = new QToolButton( Qt::DownArrow,hbox,"arrowDownToolButton" );

   connect ( arrow     , SIGNAL ( clicked ( ))                  , this , SLOT ( showPopup()    )) ;
   connect ( fSelected , SIGNAL ( clicked ( ))                  , this , SLOT ( showPopup()    )) ;

   fPopup    = new TQt18MarkerSelector(hbox,"18markerSelector");

   connect ( fPopup    , SIGNAL ( selected ( TQtMarkerFrame * )), this , SLOT ( selectedSlot(TQtMarkerFrame * ) )) ;

   //group->setInsideMargin  ( 1 );
   //group->setInsideSpacing ( 1 );

   arrow->setFixedWidth(arrow->sizeHint().width()+4);
   arrow->setSizePolicy(QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Minimum ));

   fSelected->setSizePolicy(QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Minimum ));

   //group->adjustSize();
   fSelected->show();
   arrow->show();

   hbox->show();
   //group->show();
}

void TQtMarkerSelect::selectedSlot( TQtMarkerFrame * selectedMarkerFrame )
{
   Style_t style = selectedMarkerFrame->GetStyle();
   if ( style != fSelected->GetStyle() ) {
      fSelected->SetStyle ( style );
      MarkerStyleEmit (style );
   }
}

Style_t TQtMarkerSelect::GetStyle()
{
   return fSelected ? fSelected->GetStyle() : 1 ;
}

void TQtMarkerSelect::SetStyle(Style_t style)
{
   if ( fSelected ) {
      fSelected->SetStyle(style);
   }
}

void TQtMarkerSelect::showPopup()
{
   fPopup->showSelector( fSelected->mapToGlobal(fSelected->pos()+QPoint(fSelected->width(),fSelected->height())) ); // QWidget::mapToGlobal().
}

void TQtMarkerSelect::MarkerStyleEmit(Style_t style)
{
  emit StyleSelected (style);
  Emit("StyleSelected(style);", style);
}

#undef QBUTTONGROUP
