#include "TQtObjectViewFrame.h"
#include <QStandardItem>
#include <QString>
#include <QFileIconProvider>
#include "TList.h"
#include "TClass.h"
#include "TDataMember.h"
#include "TRealData.h"
#include "TKey.h"
#include "TH3.h"

//_________________________________________________________________
static QStandardItem *CreateItem(TDirectory  *parentDir) 
{
   // Create tree view of the ROOT TDirectory
   TDirectory *saveDir = (parentDir == gDirectory) ? 0 : gDirectory;
   QFileIconProvider::IconType it = QFileIconProvider::Trashcan;
   if (saveDir) parentDir->cd();

   QStandardItem *item = 0;
   item =  TQtObjectViewFrame::ClearEditFlag(new QStandardItem(parentDir->GetName()));
   item->setData(qVariantFromValue((void *)parentDir));

   TList *listOfKeys = parentDir->GetListOfKeys();
   TIter next(listOfKeys);
   TObject *key = 0;
   while ((key = next())) { 
     TObject *obj = ((TKey *)key)->ReadObj();
     if (TDirectory *nextDir = dynamic_cast<TDirectory*>(obj)) {
         item->appendRow(CreateItem(nextDir));
     } else {
       QStandardItem *itObj =  TQtObjectViewFrame::ClearEditFlag(new QStandardItem(obj->GetName()));
       itObj->setData(qVariantFromValue((void *)obj));
       QList<QStandardItem *>  columns;
       columns << itObj
            <<  TQtObjectViewFrame::ClearEditFlag(new QStandardItem(obj->ClassName()))
            <<  TQtObjectViewFrame::ClearEditFlag(new QStandardItem(obj->GetTitle()))
          ;
       item->appendRow(columns);
       if (obj->InheritsFrom(TH3::Class())) 
         itObj->setIcon(QIcon("h3_s.xpm"));
       else if (obj->InheritsFrom(TH2::Class()))
         itObj->setIcon(QIcon("h2_s.xpm"));
       else  if (obj->InheritsFrom(TH1::Class()))
          itObj->setIcon(QIcon("h1_s.xpm"));
       else  if (obj->InheritsFrom("TNtuple"))
          itObj->setIcon(QIcon("ntuple_s.xpm"));
       else  if (obj->InheritsFrom("TTree"))
          itObj->setIcon(QIcon("tree_s.xpm"));
       else
          itObj->setIcon(TQtObjectViewFrame::Icon(QFileIconProvider::File));
     }
   }
   if (item) {
       it = item->hasChildren () ? 
       QFileIconProvider::Folder 
        :
       QFileIconProvider::File;
       item->setIcon(TQtObjectViewFrame::Icon(it)); 
   }
   if (saveDir) saveDir->cd();
   return item;
}

//_________________________________________________________________
QStandardItem *TQtObjectViewFrame::CreateItem(TDirectory *dir, QStandardItem *parentItem)
{
   // Create the top view 
   if (dir) {
      QStandardItem *item = ::CreateItem(dir);
       QList<QStandardItem *>  columns;
       columns  << item
                << TQtObjectViewFrame::ClearEditFlag(new QStandardItem(dir->ClassName()))
                << TQtObjectViewFrame::ClearEditFlag(new QStandardItem(dir->GetTitle()))
           ;

      parentItem->appendRow(columns);
   }
   return parentItem;
}
