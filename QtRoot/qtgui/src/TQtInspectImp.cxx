// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtInspectImp.cxx,v 1.4 2007/06/02 04:45:51 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#include "TQtInspectImp.h"
#include "TGQt.h"
#include "Buttons.h"
#include "TClass.h"
#include "TRealData.h"
#include "TDataType.h"
#include "TDataMember.h"
#include "TIterator.h"
#include "TList.h"
#include "TLink.h"
#include "TDatime.h"

#include "qclipboard.h"
#include "qapplication.h"

#if QT_VERSION >= 0x40000
#  include <QTableWidgetItem>
#  include <QHeaderView>
#  include <QtDebug>
#  include <QTableWidget>
#endif /* QT_VERSION */

class TQtInspectorItem : public
#if QT_VERSION < 0x40000
                         QListViewItem 
#else /* QT_VERSION */
                         QTableWidgetItem 
#endif /* QT_VERSION */
                            {
private:
  TLink *fLink;
public:
#if QT_VERSION < 0x40000
  TQtInspectorItem(QListView * parent, QString label, QString label2,QString label3, TLink *link)
    :  QListViewItem(parent,label,label2,label3),fLink(link) {}
#else /* QT_VERSION */
  TQtInspectorItem(QTableWidget*parent, QString label, QString label2,QString label3, TLink *link)
    :  QTableWidgetItem(label),fLink(link) 
  {
      Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
      int rows = parent->rowCount();
      parent->setRowCount (rows+1);      
      parent->setItem(rows,0,this); 
      setText(label);
      setFlags(flags);
       
      QTableWidgetItem *item= new QTableWidgetItem();       
      item->setText(label2);
      item->setFlags(flags);
      parent->setItem(rows,1,item);
      
      item= new QTableWidgetItem();
      item->setText(label3);
      item->setFlags(flags);
      parent->setItem(rows,2,item);
//       qDebug() << "Row" << rows+1<<":"<< label << label2 << label3;

  }
#endif /* QT_VERSION */
   TLink *Link(){ return fLink;} 
  ~TQtInspectorItem(){delete Link(); }
};

// ClassImp(TQtInspectWidget)

///////////////////////////////////////////////////////////////
//                                                           //
//   TQtInspectWidget is a special Qt object to implement    //
//   TObject::Inspect  member funection                      //
//                                                           //
///////////////////////////////////////////////////////////////

//______________________________________________________________________________
TQtInspectWidget::TQtInspectWidget(QWidget *parent,const TObject *obj) :
#if QT_VERSION < 0x40000
                                   QListView(parent,0,Qt::WDestructiveClose)
#else /* QT_VERSION */
                                  QTableWidget(parent)
#endif /* QT_VERSION */
, fInspector(0)
 {
   CreateInspector(obj);
#if QT_VERSION < 0x40000
   connect(this,SIGNAL(clicked(QListViewItem *)),SLOT(Selected(QListViewItem *)));
#else /* QT_VERSION */
   connect(this,SIGNAL(itemClicked(QTableWidgetItem *)),SLOT(Selected(QTableWidgetItem *)));
   setAttribute(Qt::WA_DeleteOnClose);
#endif /* QT_VERSION */
}

//______________________________________________________________________________
TQtInspectWidget::TQtInspectWidget(TQtInspectImp  *parent,const TObject *obj) :
#if QT_VERSION < 0x40000
                                   QListView(0,0,Qt::WDestructiveClose)
#else /* QT_VERSION */
                                  QTableWidget()
#endif /* QT_VERSION */
, fInspector(parent)
 {
   CreateInspector(obj);
#if QT_VERSION < 0x40000
   connect(this,SIGNAL(clicked(QListViewItem *)),SLOT(Selected(QListViewItem *)));
#else /* QT_VERSION */
   connect(this,SIGNAL(itemClicked(QTableWidgetItem *)),SLOT(Selected(QTableWidgetItem *)));
   setAttribute(Qt::WA_DeleteOnClose);
#endif /* QT_VERSION */
}

//______________________________________________________________________________
void TQtInspectWidget::CreateInspector(const TObject *obj)
{
  fObject = obj;
#if QT_VERSION >= 0x40000   
 setSortingEnabled(false);
 setColumnCount(3);
#endif      
  MakeTitle();
  MakeHeaders();
  AddValues();
  
  
  // Enable the sorting
#if QT_VERSION < 0x40000
  setShowSortIndicator(TRUE); 
#else  
  verticalHeader()->hide();
  setSortingEnabled(TRUE);
#endif      
  
}

//______________________________________________________________________________
void TQtInspectWidget::MakeHeaders()
{

  const char *headers[3];
  headers[0] = "Member Name";
  headers[1] = "Value";
  headers[2] = "Title";

#if QT_VERSION < 0x40000
  Int_t widths[]  = {96,120,-320};
#else  
  Int_t widths[]  = {96,120, 320};
#endif  
  int i;
  int lHeader = sizeof(headers)/sizeof(const char *);
  for (i=0;i<lHeader;i++){
#if QT_VERSION < 0x40000
    addColumn(headers[i],widths[i]);
#else    
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(tr(headers[i]));
    setHorizontalHeaderItem(i, item);
    setColumnWidth(i, widths[i]);
#endif           
  }  
}
//______________________________________________________________________________
void TQtInspectWidget::MakeTitle()
{
    TClass *cl = fObject->IsA();
    if (cl == 0) return;

    char buffer[1024];
    sprintf(buffer, "%s   :   %s:%d   -   \"%s\"  -> 0x%p", cl->GetName(),
                                           fObject->GetName(),
                                           fObject->GetUniqueID(),
                                           fObject->GetTitle(),fObject);
    setCaption(buffer);
}
//______________________________________________________________________________
void TQtInspectWidget::AddValues()
{
    Int_t cdate = 0;
    Int_t ctime = 0;
    UInt_t *cdatime = 0;
    Bool_t isdate = kFALSE;
    enum {kname, kvalue, ktitle};

    char *line[ktitle+1];

    line[kname] = " ";
    line[kvalue] = new char[2048];
    line[ktitle] = " ";

    TClass *cl = fObject->IsA();
    if (cl == 0) return;
    if (!cl->GetListOfRealData()) cl->BuildRealData();

//*-*- count number of data members in order to resize the canvas
    TRealData *rd;
    TIter      next(cl->GetListOfRealData());
    Int_t nreal = cl->GetListOfRealData()->GetSize();
    if (nreal == 0)  return;

//*-*  Prepare a list view control for adding a large number of items
//*-*
    while ( ( rd = (TRealData*) next() ) ) {
       TDataMember *member = rd->GetDataMember();
       TDataType *membertype = member->GetDataType();
       isdate = kFALSE;
       if (strcmp(member->GetName(),"fDatime") == 0 && strcmp(member->GetTypeName(),"UInt_t") == 0)
       {
          isdate = kTRUE;
       }
//*-*- Encode data member name
       line[kname] = (char *)(rd->GetName());

//*-*- Encode data value or pointer value
       Int_t offset = rd->GetThisOffset();
       char *pointer = (char*)fObject + offset;
       char **ppointer = (char**)(pointer);
       TLink *tlink = 0;

       if (member->IsaPointer()) {
          char **p3pointer = (char**)(*ppointer);
          if (!p3pointer) {
             sprintf(line[kvalue],"->0");
          } else if (!member->IsBasic()) {
             sprintf(line[kvalue],"->%x ",  (unsigned int)p3pointer );
             tlink = new TLink(0, 0, p3pointer);
          } else if (membertype){
               if (!strcmp(membertype->GetTypeName(), "char"))
                  sprintf(line[kvalue], "%s", *ppointer);
               else
                  strcpy(line[kvalue], membertype->AsString(p3pointer));
          }
          else if (!strcmp(member->GetFullTypeName(), "char*") ||
                   !strcmp(member->GetFullTypeName(), "const char*")) {
             sprintf(line[kvalue], "%s", *ppointer);
          } else {
             sprintf(line[kvalue],"->%x ", (unsigned int)p3pointer);
             tlink = new TLink(0, 0, p3pointer);
          }
       } else if (membertype)
            if (isdate) {
               cdatime = (UInt_t*)pointer;
               TDatime::GetDateTime(cdatime[0],cdate,ctime);
               sprintf(line[kvalue],"%d/%d",cdate,ctime);
            } else {
               strcpy(line[kvalue], membertype->AsString(pointer));
            }
       else
           sprintf(line[kvalue],"->%x ", (unsigned int)pointer);

    //*-*- Encode data member title

       if (strcmp(member->GetFullTypeName(), "char*") &&
           strcmp(member->GetFullTypeName(), "const char*")) {
          line[ktitle] = (char *)member->GetTitle();
       }
       if (tlink) {
         tlink->SetName((char *)member->GetTypeName());
         tlink->SetBit(kCanDelete);
       }
       
       new TQtInspectorItem(this,line[kname],line[kvalue],line[ktitle],tlink);
//       if (tlink) { Add(tlink); ctrl->Add(tlink); } 
    }
}
//______________________________________________________________________________
TQtInspectWidget::~TQtInspectWidget()
{ 
   hide(); 
   delete Disconnect();
}
//______________________________________________________________________________
void TQtInspectWidget::Hide(){ hide(); }
//______________________________________________________________________________
void TQtInspectWidget::Show(){ 
#if QT_VERSION >= 0x40000
   resizeColumnToContents(2); 
 //  show();
#endif   
   raise();
   showNormal();
//   gVirtualX->RaiseWindow(TGQt::iwid(this)); 
}

//______________________________________________________________________________
#if QT_VERSION < 0x40000
void TQtInspectWidget::Selected(QListViewItem * item)
#else /* QT_VERSION */
void TQtInspectWidget::Selected(QTableWidgetItem *item)
#endif /* QT_VERSION */
{
  // - Expand the selected item (if possible)
  // - Copy the selected item to the system clipboard

  if (item) {
    QString clipboardText;
    
#if QT_VERSION < 0x40000
    clipboardText += item->text(0);
    clipboardText += item->text(1);
    clipboardText += item->text(2);
#else    
    int row = item->row();
    clipboardText += takeItem(row,0)->text();
    clipboardText += takeItem(row,1)->text();
    clipboardText += takeItem(row,2)->text();
#endif        
    if ( ! clipboardText.isEmpty() ){
      // Copy it to the system clipboard
      QClipboard *cb = QApplication::clipboard();
      cb->setText(clipboardText);
    }
    // Execute ROOT action
    TQtInspectorItem *it = 0;
#if QT_VERSION < 0x40000
    it = (TQtInspectorItem *)item;
#else    
    it = (TQtInspectorItem *)takeItem(row,0);
#endif    
    if (it) {
       TLink *tlink = it->Link();
       if (tlink) tlink->ExecuteEvent(kButton1Up,0,0);
    }
  }
}
//______________________________________________________________________________
TQtInspectImp *TQtInspectWidget::Disconnect()
{
   TQtInspectImp *save = fInspector;
   fInspector = 0;
   if (save) save->Disconnect();
   return save;
}

//______________________________________________________________________________
//
//              TQtInspectImp
//______________________________________________________________________________
TQtInspectImp::TQtInspectImp(const TObject *obj, UInt_t width, UInt_t height)
{
    fWidget = new  TQtInspectWidget(this, obj);  
    fWidget->resize(width,height);
    Show();
}
//______________________________________________________________________________
TQtInspectImp::~TQtInspectImp()
{
   // Destroy the widget
   Hide();
   delete Disconnect();
}
//______________________________________________________________________________
void  TQtInspectImp::Hide()
{
   // Hide the widget
   if (fWidget) fWidget->Hide();
}
//______________________________________________________________________________
void  TQtInspectImp::Show()
{
   // Show the widget
   if (fWidget) fWidget->Show();
}
//______________________________________________________________________________
TQtInspectWidget *TQtInspectImp::Disconnect()
{
   // To be called by TQtInspectWidget dtor
   TQtInspectWidget *save = fWidget;
   fWidget = 0;
   if (save) save->Disconnect();
   return save;
}
