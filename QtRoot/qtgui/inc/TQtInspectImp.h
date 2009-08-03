// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtInspectImp.h,v 1.5 2009/08/03 18:03:08 fine Exp $
**
** Copyright (C) 2002 by Valeri Fine.  All rights reserved.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
*****************************************************************************/

#ifndef ROOT_TQtInspectImp
#define ROOT_TQtInspectImp

///////////////////////////////////////////////////////////////
//                                                           //
//   TQtInspectImp is a special Qt type of browser           //
//   to back TObject::Inspect  member function               //
//                                                           //
///////////////////////////////////////////////////////////////

#include "TInspectorImp.h"
#include <qglobal.h>

#if QT_VERSION < 0x40000
#ifndef Q_MOC_RUN
#  include "qlistview.h"
#endif
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
#   include <QTableWidget>
class QTableWidget;
class QTableWidgetItem;
//MOC_SKIP_END
#endif /* QT_VERSION */

class TQtInspectImp;

#if QT_VERSION < 0x40000
#ifndef Q_MOC_RUN
  class TQtInspectWidget : public QListView    {
#endif
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  class TQtInspectWidget : public QTableWidget {
//MOC_SKIP_END
#endif /* QT_VERSION */

Q_OBJECT

private:
  const TObject *fObject;             // Pointer to displayed object
  TQtInspectImp *fInspector;
   
protected:
  friend class TQtInspectImp;
  virtual void AddValues();
  virtual void CreateInspector(const TObject *obj);
  virtual void MakeHeaders();
  virtual void MakeTitle();
  TQtInspectImp *Disconnect();

public:
  TQtInspectWidget(QWidget *parent=0,const TObject *obj=0);
  TQtInspectWidget(TQtInspectImp *parent,const TObject *obj=0);
  virtual ~TQtInspectWidget();
  virtual void Hide();
  virtual void Show();

public slots:
#if QT_VERSION < 0x40000
#ifndef Q_MOC_RUN
  virtual void Selected(QListViewItem * item);
#endif
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  virtual void Selected(QTableWidgetItem *item );
//MOC_SKIP_END
#endif /* QT_VERSION */
};
  

class TQtInspectImp : public TInspectorImp {
   private:         
     TQtInspectWidget *fWidget;
   protected:
     friend class TQtInspectWidget;
     TQtInspectWidget *Disconnect();
   
   public:
     TQtInspectImp(const TObject *obj=0, UInt_t width=400, UInt_t height=300);
     virtual ~TQtInspectImp();
     virtual void Hide();
     virtual void Show();
};

#endif
