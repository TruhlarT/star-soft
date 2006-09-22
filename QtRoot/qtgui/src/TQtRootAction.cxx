#include "TQtRootAction.h"
#include "TQtGui.h"
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#include <QPixmap>
#endif /* QT_VERSION */
//_________________________________________________________________________________________________________
TQtRootAction::TQtRootAction(QObject * parent, const TQtBrowserMenuItem_t  &data, const char * name)
#if QT_VERSION < 0x40000
      : QAction (parent,name)
#else
      : Q3Action(parent,name)
#endif
      , fId(data.fId)
{
   setMenuText(data.fMenuText);
   if (data.fToolTip && data.fToolTip[0]) 
            setToolTip(data.fToolTip);   
   if (data.fAccelerator) setAccel(data.fAccelerator);
   if (data.iconName && data.iconName[0] /*&& gClient*/ ) {
         const QPixmap &pixmap = TQtGui::GetPicture(data.iconName);
         setIconSet(pixmap);
   }
}
