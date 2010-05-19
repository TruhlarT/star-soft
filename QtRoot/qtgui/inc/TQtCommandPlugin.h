// @(#)root/gui:$Id: TQtCommandPlugin.h,v 1.1 2010/05/19 22:36:37 fine Exp $
// Author: Valeri Fine 15/05/2010 (derived from TGCommandPlugin by Bertrand Bellenot   26/09/2007)

#ifndef ROOT_TQtCommandPlugin
#define ROOT_TQtCommandPlugin

#include <QtGui/QFrame>
#include <QtCore/QFile>
#include <QtCore/QTimer>
// Command (I/O redirection) plugin for the new ROOT Browser
class Ui_TQtRootCommand;

class TQtCommandPlugin : public QFrame {
   Q_OBJECT
private:
   Ui_TQtRootCommand   *fUi; 
   QFile               fTempFile;
   QTimer              fTimer;
protected:
   qint64  fPid;               // current process id

public:
   TQtCommandPlugin(QWidget * parent=0, Qt::WindowFlags f=0);
   virtual ~TQtCommandPlugin();

   void     InsertFromHistory(int index=0);

public slots:
   void     HandleCommand();
   void     CheckRemote();
};

#endif
