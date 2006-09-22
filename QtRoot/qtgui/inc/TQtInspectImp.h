// Author: Valeri Fine   21/01/2002
/****************************************************************************
** $Id: TQtInspectImp.h,v 1.2 2006/09/22 17:27:10 fine Exp $
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
#  include "qlistview.h"
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
   #include "q3listview.h"
//MOC_SKIP_END
#endif /* QT_VERSION */

#if QT_VERSION < 0x40000
  class TQtInspectImp : public QListView, public TInspectorImp {
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  class TQtInspectImp : public Q3ListView, public TInspectorImp {
//MOC_SKIP_END
#endif /* QT_VERSION */

Q_OBJECT

private:
  const TObject  *fObject;             // Pointer to displayed object

protected:

  virtual void AddValues();
  virtual void CreateInspector(const TObject *obj);
  virtual void MakeHeaders();
  virtual void MakeTitle();

public:
  TQtInspectImp(const TObject *obj=0, UInt_t width=400, UInt_t height=300);
  virtual ~TQtInspectImp();
  virtual void Hide();
  virtual void Show();

public slots:
#if QT_VERSION < 0x40000
  virtual void Selected(QListViewItem * item);
#else /* QT_VERSION */
//MOC_SKIP_BEGIN
  virtual void Selected(Q3ListViewItem * item);
//MOC_SKIP_END
#endif /* QT_VERSION */

};

#endif
