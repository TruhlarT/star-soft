// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtInspectImp.cxx,v 1.1 2006/08/16 19:27:07 fine Exp $
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
#include "TLink.h"
#include "TDatime.h"

#include "qclipboard.h"
#include "qapplication.h"

#if QT_VERSION < 0x40000
class TQtInspectorItem : public QListViewItem {
#else /* QT_VERSION */
class TQtInspectorItem : public Q3ListViewItem {
#endif /* QT_VERSION */
private:
  TLink *fLink;
public:
#if QT_VERSION < 0x40000
  TQtInspectorItem(QListView * parent, QString label, QString label2,QString label3, TLink *link)
    :  QListViewItem(parent,label,label2,label3),fLink(link) {}
#else /* QT_VERSION */
  TQtInspectorItem(Q3ListView * parent, QString label, QString label2,QString label3, TLink *link)
    :  Q3ListViewItem(parent,label,label2,label3),fLink(link) {}
#endif /* QT_VERSION */
  ~TQtInspectorItem(){delete fLink; }
  TLink *Link(){ return fLink;} 
};

// ClassImp(TQtInspectImp)

///////////////////////////////////////////////////////////////
//                                                           //
//   TQtInspectImp is a special Qt object to implement       //
//   TObject::Inspect  member funection                      //
//                                                           //
///////////////////////////////////////////////////////////////

//______________________________________________________________________________
TQtInspectImp::TQtInspectImp(const TObject *obj,UInt_t width, UInt_t height) :
#if QT_VERSION < 0x40000
                                   QListView(0,0,Qt::WDestructiveClose)
#else /* QT_VERSION */
                                   Q3ListView(0,0,Qt::WDestructiveClose)
#endif /* QT_VERSION */
{
   CreateInspector(obj);
#if QT_VERSION < 0x40000
   connect(this,SIGNAL(clicked(QListViewItem *)),SLOT(Selected(QListViewItem *)));
#else /* QT_VERSION */
   connect(this,SIGNAL(clicked(Q3ListViewItem *)),SLOT(Selected(Q3ListViewItem *)));
#endif /* QT_VERSION */
   resize(width,height);
   Show();
}
//______________________________________________________________________________
void TQtInspectImp::CreateInspector(const TObject *obj)
{
  fObject = obj;

  MakeTitle();
  MakeHeaders();
  AddValues();
}

//______________________________________________________________________________
void TQtInspectImp::MakeHeaders()
{

  const char *headers[3];
  headers[0] = "Member Name";
  headers[1] = "Value";
  headers[2] = "Title";

  Int_t widths[]  = {96,120,-320};
  int i;
  int lHeader = sizeof(headers)/sizeof(const char *);
  for (i=0;i<lHeader;i++){
    addColumn(headers[i],widths[i]);
  }
  setShowSortIndicator(TRUE); 
}
//______________________________________________________________________________
void TQtInspectImp::MakeTitle()
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
void TQtInspectImp::AddValues()
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
TQtInspectImp::~TQtInspectImp()
{  hide(); }
//______________________________________________________________________________
void TQtInspectImp::Hide(){ hide(); }
//______________________________________________________________________________
void TQtInspectImp::Show(){ 
   raise();
   showNormal();
//   gVirtualX->RaiseWindow(TGQt::iwid(this)); 
}

//______________________________________________________________________________
#if QT_VERSION < 0x40000
void TQtInspectImp::Selected(QListViewItem * item)
#else /* QT_VERSION */
void TQtInspectImp::Selected(Q3ListViewItem * item)
#endif /* QT_VERSION */
{
  // - Expand the selected item (if possible)
  // - Copy the selcted item to the system clipboad

  if (item) {
    QString clipboardText = item->text(0);
    clipboardText += item->text(1);
    clipboardText += item->text(2);
    if ( ! clipboardText.isEmpty() ){
      // Copy it to the system clipboad
      QClipboard *cb = QApplication::clipboard();
      cb->setText(clipboardText);
    }
    // Execute ROOT action
    TQtInspectorItem *it = (TQtInspectorItem *)item;
    TLink *tlink = it->Link();
    if (tlink) tlink->ExecuteEvent(kButton1Up,0,0);
  }
}
