#include "TQtRootAction.h"
#include "TQtGui.h"
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#  include <QPixmap>
#endif /* QT_VERSION */
//_________________________________________________________________________________________________________
TQtRootAction::TQtRootAction(QObject * parent, const TQtBrowserMenuItem_t  &data)
      : QAction (parent), fId(data.fId)
{
#if QT_VERSION < 0x40000
   setMenuText(data.fMenuText);
   if (data.fToolTip && data.fToolTip[0]) 
            setToolTip(data.fToolTip);   
   if (data.fAccelerator) setAccel(data.fAccelerator);
   if (data.iconName && data.iconName[0] /*&& gClient*/ ) {
         const QPixmap &pixmap = TQtGui::GetPicture(data.iconName);
         setIconSet(pixmap);
   }
#else
   setText(data.fMenuText);
   if (data.fToolTip && data.fToolTip[0]) 
            setToolTip(data.fToolTip);   
   if (data.fAccelerator) setShortcut (data.fAccelerator);
   if (data.iconName && data.iconName[0] /*&& gClient*/ ) {
      if (data.iconName[0] == ':') {
          // Use the Qt4 resource 
          setIcon(QIcon(data.iconName));
      } else {
          const QPixmap &pixmap = TQtGui::GetPicture(data.iconName);
          setIcon(pixmap);
      }
   }
#endif 
}
