#include "TQtGui.h"
#include "TGClient.h"
#include "TGPicture.h"
#include "TSystem.h"
#include <qpixmapcache.h> 
#include <qfileinfo.h> 
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#  include <QPixmap>
#  include <QString>
#endif /* QT_VERSION */
static QPixmap *gDummyIcon = 0;
//________________________________________________________________________
bool TQtGui::AddPicture(const QPixmap &pic, const char *pictureName, bool checkCache)
{
   // Add the picture to the picture cache
   // Ignore the unamed and empty pictures
   // Return: true  - the picture was sussefully added
   //         false - wrong input parameters or the picture 
   //                 name has been taken
   bool  res = false;
   if (pictureName && pictureName[0] && !pic.isNull()) 
   {
     QString pname = QString(pictureName).stripWhiteSpace();
     bool found = false;
     if (!checkCache || ( checkCache && !(found = QPixmapCache::find(pname))))
     {
#if QT_VERSION >= 0x40000
        QPixmap p(pic);
        QPixmapCache::insert(pictureName, p);
#else
        QPixmapCache::insert(pictureName, new QPixmap(pic));
#endif
        res = true;
     }
   }
   return res;
}
//________________________________________________________________________
const QPixmap &TQtGui::GetPicture(QString &pictureName) 
{
#if QT_VERSION >= 0x40000
   std::string pName = pictureName.toStdString();
#else
   std::string pName = (const char *)pictureName;
#endif
   return GetPicture(pName.c_str());
}

//________________________________________________________________________
const QPixmap &TQtGui::GetPicture(const char *pictureName) 
{
   //
   // A'la const TGPicture *TGPicturePool::GetPicture(const char *name)
   // Warning: If valid, you should copy the pixmap immediately (this is fast). 
   // Subsequent insertions into the cache could cause the pointer 
   // to become invalid.
   //
   QPixmap* pp=0;
   QPixmap p;
   QString pname = QString(pictureName).stripWhiteSpace();
   if ( !(pp=QPixmapCache::find(pname)) ) {

      QString ext   = QFileInfo(pname).extension(FALSE).lower();

      if (!ext.isEmpty()) { // ".xpm", ".gif" etc
#if QT_VERSION >= 0x40000
         std::string mstrname = pname.toStdString();
#else
         std::string mstrname = (const char *)pname;
#endif
         char *pxname = gSystem->ExpandPathName(gSystem->UnixPathName(mstrname.c_str()));
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
         AddPicture(p,pname,kFALSE);
         pp = QPixmapCache::find(pname);
      }
   }
   if (!gDummyIcon && !pp) gDummyIcon = new QPixmap();
   return pp ? *pp : *gDummyIcon;
}
