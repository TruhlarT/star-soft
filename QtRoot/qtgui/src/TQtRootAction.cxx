#include "TQtRootAction.h"
#include "TQtGuiFactory.h"
#include "TGClient.h"
#include "TGPicture.h"
#include "TSystem.h"
#include <qpixmapcache.h> 
#include <qfileinfo.h> 
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#include <QPixmap>
#endif /* QT_VERSION */
static QPixmap *dummyIcon = 0; 
//________________________________________________________________________
static const QPixmap &GetPicture(const char *pictureName) {
   // A'la const TGPicture *TGPicturePool::GetPicture(const char *name)
   QPixmap* pp;
   QPixmap p;
   if ( !(pp=QPixmapCache::find(pictureName)) ) {

      QString pname = QString(pictureName).stripWhiteSpace();
      QString ext   = QFileInfo(pname).extension(FALSE).lower();

      if (!ext.isEmpty()) { // ".xpm", ".gif" etc
         char *pxname = gSystem->ExpandPathName(gSystem->UnixPathName((const char*)pname));
         pname = pxname;
         delete [] pxname;
      }

      // Get ROOT Icon path:
      const char *iconPath = ".";
      if (gClient) {
         // see: TGResourcePool::TGResourcePool
         TGPicturePool *pool  = gClient->GetPicturePool();
         iconPath = pool->GetPath();
         if (!iconPath && !iconPath[0]) iconPath = ".";
      } 
      char *picnam = 0;
      picnam = gSystem->Which(iconPath, (const char *)pname, kReadPermission);
      if (picnam) {
         p.load(picnam);
         pp = new QPixmap(p);        
         QPixmapCache::insert(pname, *pp);
      }
   }
   if (!dummyIcon && !pp) dummyIcon = new QPixmap;
   return pp ? *pp : *dummyIcon;
}
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
         const QPixmap &pixmap = GetPicture(data.iconName);
         setIconSet(pixmap);
   }
}
