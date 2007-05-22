#include "TQtMarkerSelectButton.h"

#include "TQtGui.h"
#include <qstring.h>


#if QT_VERSION < 0x40000
#  define  QBUTTONGROUP QButtonGroup
#  include <qbuttongroup.h>

#else /* QT_VERSION */
#  define  QBUTTONGROUP Q3ButtonGroup
#  include  <q3buttongroup.h>
#endif /* QT_VERSION */

/////////////////////////////////////////////////////////////////////////////////////////////////
// TQtMarkerFrame                                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////
TQtMarkerFrame::TQtMarkerFrame ( QWidget *p, const char * name, Style_t style )
   : QToolButton (p, name),
     fStyle (-1),
     fPixmap()
{
//   std::cout << "TQtMarkerFrame constructor "<< (QString("marker")  + QString::number(shape) + ".xpm" )).ascii() << std::endl ;
   SetStyle(style);
   connect (this , SIGNAL(clicked()), this, SLOT(clickedSlot()));
   adjustSize();
   show();
}

void TQtMarkerFrame::SetStyle ( const Style_t & style )
{
   if ( fStyle != style ) {
      fStyle  = style;
      fPixmap = TQtGui::GetPicture( QString("marker")  + QString::number(fStyle) + ".xpm" ) ;
      setPixmap ( fPixmap );
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// TQt18MarkerSelector                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////
TQt18MarkerSelector::TQt18MarkerSelector( QWidget * p,Qt::WFlags f) :
#if QT_VERSION < 0x40000
   QDialog (p,0,0,f)
#else
   QDialog (p,f)
#endif
{
   setModal(true);
   QBUTTONGROUP *group =  new  QBUTTONGROUP (3, Qt::Horizontal , this, "markerGroup");

   TQtMarkerFrame * frame;
   frame = new TQtMarkerFrame ( group, "",  1 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  6 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  7 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  2 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  3 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  4 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "",  5 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 20 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 21 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 22 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 23 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 24 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 25 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 26 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 27 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 28 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 29 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );
   frame = new TQtMarkerFrame ( group, "", 30 ); connect ( frame, SIGNAL (selected( TQtMarkerFrame * )), this, SLOT( selectedSlot ( TQtMarkerFrame * )) );

   group->setInsideMargin  ( 0 );
   group->setInsideSpacing ( 0 );

   group -> adjustSize();

   adjustSize();
}

void TQt18MarkerSelector::selectedSlot ( TQtMarkerFrame * selectedMarkerFrame )
{
   // close();
   accept();
   emit selected(selectedMarkerFrame);
}

void TQt18MarkerSelector::showSelector( const QPoint & position)
{
   // popup(position);
   move(position);
   exec();
}

#undef QBUTTONGROUP
