// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtContextMenuImp.cxx,v 1.2 2006/09/22 17:27:11 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine. Brookhaven National Laboratory.
**                                    All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
*****************************************************************************/

#include <qapplication.h>
#if QT_VERSION >= 0x40000
//Added by qt3to4:
#include <Q3PopupMenu>
#endif /* QT_VERSION */
#include "TQtContextMenuImp.h"
#include "TGQt.h"
#include "TQtLock.h"

#include "TCanvas.h"
#include "TClass.h"

#include "TMethod.h"
#include "TBrowser.h"
#include "TMethodArg.h"
#include "TDataType.h"
#include "TMethodCall.h"
#include "TROOT.h"

#include "TContextMenuImp.h"
#include "TObjArray.h"
#include "TApplication.h"
#include "TQtApplication.h"
#include "TQtObjectDialog.h"
#include "TQtBrowserImp.h"
#include "TObjectExecute.h"

#include  <qlabel.h>
//______________________________________________________________________________
TQtContextMenuImp::TQtContextMenuImp(TContextMenu *c) :  TContextMenuImp(c), fPopupMenu(0)
                      
{
    fItems.setAutoDelete(TRUE);
    fExecute = new TObjectExecute();
}
//______________________________________________________________________________
TQtContextMenuImp::~TQtContextMenuImp()
{
  DeletePopup();
}
//______________________________________________________________________________
void TQtContextMenuImp::DeletePopup()
{
  if (fPopupMenu) {
    fPopupMenu->disconnect(this);
#if QT_VERSION < 0x40000
    QPopupMenu   *m = fPopupMenu; fPopupMenu = 0;
#else /* QT_VERSION */
    Q3PopupMenu   *m = fPopupMenu; fPopupMenu = 0;
#endif /* QT_VERSION */
    delete m; 
  }
  ClearProperties();
  if (fExecute) {
    TObjectExecute  *e=fExecute; fExecute = 0; 
    delete e;
  }
  // qApp->unlock();
}
//______________________________________________________________________________
void TQtContextMenuImp::CreatePopup ( TObject * /*object*/ ) 
{}
//______________________________________________________________________________
void TQtContextMenuImp::CreatePopup () {
  TContextMenu *c;

//*-*   Find the parent canvas window

  if ( (c=GetContextMenu()) ) {
    TCanvas *canvas = (TCanvas*)c->GetSelectedCanvas();
    QWidget *parent = 0;
    if (canvas) {
      parent = (QWidget *)TGQt::iwid(canvas->GetCanvasID());
    }
//*-*  Add a title. 
    if (fPopupMenu) delete fPopupMenu;
    fPopupMenu = 0;
#if QT_VERSION < 0x40000
    fPopupMenu = new QPopupMenu(parent,"ContextMenu");
#else /* QT_VERSION */
    fPopupMenu = new Q3PopupMenu(parent,"ContextMenu");
#endif /* QT_VERSION */
    connect(fPopupMenu,SIGNAL(destroyed()),this,SLOT(Disconnect()));
    connect(fPopupMenu,SIGNAL(aboutToShow () ),this,SLOT( AboutToShow() ));
    fPopupMenu->setCaption("Title");

//*-*  Include the menu title
    TObject *object = c? c->GetSelectedObject() : 0;
    QString titleBar = "<center><b><i>";
    titleBar += fContextMenu->CreatePopupTitle(object);
    titleBar += "</i></b></center>";
#if QT_VERSION < 0x40000
    fPopupMenu->insertItem(new QLabel(titleBar,fPopupMenu));
#else
    fPopupMenu->setTitle(titleBar);
    titleBar = fContextMenu->CreatePopupTitle(object);
    fPopupMenu->addAction(titleBar);
#endif

    fPopupMenu->insertSeparator();fPopupMenu->insertSeparator();

//*-*  Include the standard static item into the context menu
    fPopupMenu->insertItem("&Inspect",    this,SLOT(InspectCB()));
    fPopupMenu->insertItem("&Browse",     this,SLOT(BrowseCB()));
  }
}
//______________________________________________________________________________
void TQtContextMenuImp::AboutToShow()
{
   // Slot to propagate the QPopupMenu signal further to the TContextMenu "clients"
   if (fPopupMenu) {
        emit AboutToShow(fPopupMenu,GetContextMenu());
   }
}
//______________________________________________________________________________
void TQtContextMenuImp::ClearProperties()
{ }
//______________________________________________________________________________
void  TQtContextMenuImp::Dialog( TObject *object, TMethod *method )
{
  if ( !( object && method ) ) return;
  TQtObjectDialog *d = new TQtObjectDialog(object,method);
  if (d->exec() == QDialog::Accepted )  {
    TObjArray *parList = d->GetParamList();
    if (fExecute) fExecute->Execute(object,method,parList);
    // TContextMenu *c=GetContextMenu();
    //  c->Execute(object,method,parList); 
  }
  delete d;
}
//______________________________________________________________________________
void  TQtContextMenuImp::Dialog( TObject *object, TFunction *function )
{
  if ( !( object && function ) ) return;
  TQtObjectDialog *d = new TQtObjectDialog(object,(TMethod *)function);
  if (d->exec() == QDialog::Accepted )  {
    TObjArray *parList = d->GetParamList();
    if (fExecute) fExecute->Execute(function,parList);
    // TContextMenu *c=GetContextMenu();
    //  c->Execute(0,function,parList); 
  }
  delete d;
}

//______________________________________________________________________________
void TQtContextMenuImp::Disconnect()
{
  TQtLock lock;
   // Popup menu has been desstroyed from outside
  if (fPopupMenu) fPopupMenu = 0;
}
//______________________________________________________________________________
void  TQtContextMenuImp::DisplayPopup ( Int_t x, Int_t y)
{
  TContextMenu *m = GetContextMenu();
  if (!m) return;

  CreatePopup();

//*-*   Update a popup

  UpdateProperties();

//*-*   Display Popup
  QWidget *w = (QWidget *)fPopupMenu->parent();
  QPoint pop = QPoint(x,y);
  if (w) pop = w->mapToGlobal(QPoint(x,y));
  fPopupMenu->popup(pop);
}
//______________________________________________________________________________
void TQtContextMenuImp::UpdateProperties()
{
  TContextMenu *c = GetContextMenu();
  TObject *object = c? c->GetSelectedObject() : 0;
  if (object)
  {
    //*-*   Change title
    fPopupMenu->setCaption(fContextMenu->CreatePopupTitle(object));
    
    //*-*  Include the "Properties" item "by canvases"
#if QT_VERSION < 0x40000
    QPopupMenu *propertiesMenu = new QPopupMenu();
#else /* QT_VERSION */
    Q3PopupMenu *propertiesMenu = new Q3PopupMenu();
#endif /* QT_VERSION */
    fPopupMenu->insertSeparator();
    fPopupMenu->insertItem("&Properties",propertiesMenu);

    //*-*  Create Menu "Properties"

    TClass *classPtr = NULL;
    TMethod *method  = NULL;

    //*-*  Create a linked list
    TList *methodList = new TList();
    object->IsA()->GetMenuItems( methodList );
    TIter next( methodList );
    fItems.clear();

    while ( ( method = (TMethod *) next () ) ) {
      
      if ( classPtr != method->GetClass() ) {
        //*-*  Add a separator.
        if (classPtr) propertiesMenu->insertSeparator();
        classPtr = method->GetClass();
      }
      //*-*  Create a popup item.
      TQtMenutItem *menuItem = new TQtMenutItem(c,method,object);
      fItems.push(menuItem);
      propertiesMenu->insertItem(method->GetName(),menuItem,SLOT(Exec()));
    }
    // Delete linked list of methods.
    delete methodList;
  }
}
//______________________________________________________________________________
void TQtContextMenuImp::InspectCB()
{
  TContextMenu *c = GetContextMenu();
  TObject *object = c? c->GetSelectedObject() : 0;
  if (object) object->Inspect();
}
//______________________________________________________________________________
void TQtContextMenuImp::BrowseCB()
{ 
  TContextMenu *c = GetContextMenu();
  TObject *object = c? c->GetSelectedObject() : 0;
  if (object) new TBrowser(object->GetName(),object);
}
