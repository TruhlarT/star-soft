#include "TVirtualPad.h"
#include "TContextMenu.h"

#include "TQVirtualGL.h"
#include "TQPadOpenGLView.h"

#define QGLVIEWER

#include "TQtGLViewerImp.h"
#include "TQtGLViewerWidget.h"
#include "TObject3DView.h"

#include "TSystem.h"
#include "TROOT.h"
#include "TEnv.h"
#include "TColor.h"

#include <qprinter.h>
#include <qpixmap.h>
#include <qapplication.h>
#include <qclipboard.h>
#include <qimage.h>

#if QT_VERSION < 0x40000
#  include <qfiledialog.h>
#  include <qpopupmenu.h>
#  include <qwhatsthis.h> 
#  include <qaction.h>
#else /* QT_VERSION */
#  include <QFileDialog>
#  include <QMenu>
#  include <QWhatsThis> 
//Added by qt3to4:
#  include <QLabel>
#  include <QAction>
#endif /* QT_VERSION */

#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qmenubar.h>

#include <qpainter.h>
#include <qtextstream.h>
#include <qstatusbar.h>
#include <qsplitter.h>

#include <qevent.h>

#ifdef WIN32
#  ifdef CopyFile
#     undef CopyFile
#  endif
#endif

// ClassImp(TQtGLViewerImp)
Int_t TQtGLViewerImp::gfDefaultMaxSnapFileCounter = 2;
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp():QMainWindow(){}
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TPadOpenGLView *pad, const char *title,
                       UInt_t width, UInt_t height)
 : QMainWindow(
#if QT_VERSION < 0x40000
     0,"glviewer", Qt::WDestructiveClose
#endif /* QT_VERSION */
      )
   , TGLViewerImp(pad,title,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(0),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
 {
#if QT_VERSION > 0x40000
   setAttribute(Qt::WA_DeleteOnClose);
#endif   
   QString saveFile = TGLViewerImp::GetSnapShotFileName();
   if (!saveFile.isEmpty()) fSaveFile = (const char*)saveFile;
   if (pad) {
      TVirtualPad *thisPad = pad->GetPad();
      if (thisPad) {
         // Create the default SnapShot file name and type if any
         if (saveFile.isEmpty() || saveFile.endsWith("/") ) {
            fSaveFile += thisPad->GetName();
            fSaveFile += ".";
            fSaveFile += "jpg";
         }
         QString caption = thisPad->GetTitle();
         caption += ": OpenGL viewer";
         setCaption(caption);
         resize(width, height);
         fGLView = pad;
         CreateViewer(title);
         MakeMenu();
         int parts[] = {43,7,10,39};
         CreateStatusBar(parts,4);
         SetDrawList(0);
         ShowStatusBar();
         show();
      }
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TPadOpenGLView *pad, const char *title,
                       Int_t x, Int_t y, UInt_t width, UInt_t height)
   : QMainWindow(
#if QT_VERSION < 0x40000
       0,"glviewer", Qt::WDestructiveClose | Qt::WRepaintNoErase | Qt:: WResizeNoErase 
#endif /* QT_VERSION */
      )      
   , TGLViewerImp(pad,title,x,y,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(0),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
{
#if QT_VERSION > 0x40000
   setAttribute(Qt::WA_DeleteOnClose);
#endif   
   QString saveFile = TGLViewerImp::GetSnapShotFileName();
   if (!saveFile.isEmpty()) fSaveFile = (const char*)saveFile;
   if (pad) {
      TVirtualPad *thisPad = pad->GetPad();
      if (thisPad) {
         if (saveFile.isEmpty() || saveFile.endsWith("/") ) {
            fSaveFile += thisPad->GetName();
            fSaveFile += ".";
            fSaveFile += "jpg";
         }
         QString caption = thisPad->GetTitle();
         caption += ": OpenGL viewer";
         setCaption(caption);

         setGeometry(x, y, width, height);
         fGLView = pad;
         CreateViewer(title);
         MakeMenu();
         int parts[] = {43,7,10,39};
         CreateStatusBar(parts,4);
         SetDrawList(0);
         show();
      }
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TVirtualPad *pad, const char *title,
                       UInt_t width, UInt_t height)
   : QMainWindow(
#if QT_VERSION < 0x40000
      0,"glviewer", Qt::WDestructiveClose
#endif /* QT_VERSION */
     )
   , TGLViewerImp(0,title,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(pad),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
 {
#if QT_VERSION > 0x40000
   setAttribute(Qt::WA_DeleteOnClose);
#endif   
   // Create the default SnapShot file name and type if any
   QString saveFile = TGLViewerImp::GetSnapShotFileName();
   if (!saveFile.isEmpty()) fSaveFile = (const char*)saveFile;
   if (fPad) {
      if (saveFile.isEmpty() || saveFile.endsWith("/") ) {
         fSaveFile += fPad->GetName();
         fSaveFile += ".";
         fSaveFile += "jpg";
      }
       
      QString caption = fPad->GetTitle();
      caption += ": OpenGL viewer";
      setCaption(caption);
      resize(width, height);
      fGLView = 0;
      CreateViewer(title);
      int parts[] = {43,7,10,39};
      CreateStatusBar(parts,4);
      MakeMenu();
      SetDrawList(0);
      show();
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TVirtualPad *pad, const char *title,
                       Int_t x, Int_t y, UInt_t width, UInt_t height)
   : QMainWindow(
#if QT_VERSION < 0x40000
       0,"glviewer", Qt::WDestructiveClose | Qt::WRepaintNoErase | Qt:: WResizeNoErase 
#endif /* QT_VERSION */
      )      
   , TGLViewerImp(0,title,x,y,width,height)
   , fSaveType("JPEG"),fMaxSnapFileCounter(2),fGLWidget(0),fPad(pad),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   ,fSelectionViewer(kFALSE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
{
#if QT_VERSION > 0x40000
   setAttribute(Qt::WA_DeleteOnClose);
#endif   
   QString saveFile = TGLViewerImp::GetSnapShotFileName();
   if (!saveFile.isEmpty()) fSaveFile = (const char*)saveFile;
   if (fPad) {
      if (saveFile.isEmpty() || saveFile.endsWith("/") ) {
         fSaveFile += fPad->GetName();
         fSaveFile += ".";
         fSaveFile += "jpg";
      }
      QString caption = fPad->GetTitle();
      caption += ": OpenGL viewer";
      setCaption(caption);

      setGeometry(x, y, width, height);
      fGLView = 0;
      CreateViewer(title);
      MakeMenu();
      int parts[] = {43,7,10,39};
      CreateStatusBar(parts,4);
      SetDrawList(0);
      show();
   }
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
//______________________________________________________________________________
TQtGLViewerImp::TQtGLViewerImp(TQtGLViewerImp &parent) :
      QMainWindow(
#if QT_VERSION < 0x40000
     &parent,"glviewerutil", Qt::WDestructiveClose | Qt::WType_TopLevel
#endif /* QT_VERSION */
      )
   , TGLViewerImp(0,"selection",parent.width(),parent.height())
   , fSaveType(parent.fSaveType),fMaxSnapFileCounter(2),fGLWidget(0),fPad(parent.fPad),fContextMenu(0),fSelectedView(0),fSelectedViewActive(kFALSE)
   , fSelectionViewer(kTRUE),fSelectionHighlight(kFALSE),fShowSelectionGlobal(kFALSE),fWantRootContextMenu(kFALSE)
   , fSnapShotAction(0)
{
#if QT_VERSION > 0x40000
   setAttribute(Qt::WA_DeleteOnClose);
#endif   
   // create a satelite widget
   connect(this,SIGNAL(destroyed() ),&parent, SLOT(DisconnectSelectorWidgetCB()));
   QString caption;
   QString saveFile = TGLViewerImp::GetSnapShotFileName();
   if (!saveFile.isEmpty()) fSaveFile = (const char*)saveFile;
   if (fPad) {
      if (saveFile.isEmpty() || saveFile.endsWith("/") ) {
         fSaveFile += fPad->GetName();
         fSaveFile += ".";
         fSaveFile += "jpg";
      }
      caption = fPad->GetTitle();
   }
   fGLView = 0;
   caption += ": selection viewer";
   setCaption(caption);
   resize(2*parent.width()/3,2*parent.height()/3);
   CreateViewer(parent.GLWidget(),"selection");
   MakeMenu();
   int parts[] = {43,7,10,39};
   CreateStatusBar(parts,4);
   SetDrawList(0);
   show();
   fMaxSnapFileCounter = CreateSnapShotCounter();
}
//______________________________________________________________________________
TQtGLViewerImp::~TQtGLViewerImp()
{  }
//______________________________________________________________________________
void TQtGLViewerImp::Clear(const char *)
{
     // Clear (remove) all objects from the view
   QWidget *c = centralWidget();
   if (!c) return;
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   glView->clearGLList();
   Update();
}
//______________________________________________________________________________
void TQtGLViewerImp::CreateStatusBar(Int_t nparts)
{
 //  Create the status bar with "nparts" separate portions
  QStatusBar *thisStatusBar = statusBar();
  Int_t i=0;
  fStatusBar.resize(nparts);
  for (i=0;i<nparts;i++) {
    QLabel *l = new QLabel(thisStatusBar);
    thisStatusBar->addWidget(l,1,TRUE);
    // remember to delete later
    fStatusBar.insert(i,l);  
  }
}
//______________________________________________________________________________
void TQtGLViewerImp::CreateStatusBar(Int_t *parts, Int_t nparts)
{
  //  Create the status bar with "nparts" separate portions
  // The initial relative size of each part is defined by "parts" array

  QStatusBar *thisStatusBar = statusBar();
#ifdef WIN32
  thisStatusBar->setSizeGripEnabled(FALSE);
#endif
  // Any number of widgets may be controlled by just
  // one splitter
  QSplitter *split = new QSplitter(thisStatusBar);
  thisStatusBar->addWidget(split,1,FALSE);

  fStatusBar.resize(nparts);
  Int_t iField=0;
  for (iField=0; iField<nparts; iField++) {
    QLabel *infoBox = new QLabel(split);
    infoBox->setIndent(3);
    QSize s = infoBox->size();
    s.setWidth(parts[iField]);
    infoBox->resize(s);

    // remember to delete later
    fStatusBar.insert(iField,infoBox);
  }
}
//______________________________________________________________________________
int TQtGLViewerImp::CreateSnapShotCounter()
{
   // Define the number of the snapshot frames based on either
   // "SnapShotFileCounter" environment variable
   //    use: 
   //          setenv SnapShotFileCounter 100
   // to produce 100  different frames in raw
   // or the ROOT parameters (via ".rootrc" file) 
   //
   //   Gui.SnapShotFileCounter 100
   //
   const char *dcounter = gSystem->Getenv("SnapShotFileCounter");
   if (!(dcounter && dcounter[0]) && ( gEnv ) ) {
        dcounter  = gEnv->GetValue("Gui.SnapShotFileCounter","2");
   }
   if (dcounter && dcounter[0]) {
      int count = QString(dcounter).toInt();
      if (count > 2 )  gfDefaultMaxSnapFileCounter = count;
   }
   return gfDefaultMaxSnapFileCounter;
}
//______________________________________________________________________________
void TQtGLViewerImp::DisconnectSelectorWidgetCB()
{
   // [slot] to disconnect the destroyed  "selection" widget
  fSelectedView = 0; 
}

//______________________________________________________________________________
void TQtGLViewerImp::SetStatusText(const char *text, Int_t partidx, Int_t stype)
{  
  // Set Text into the 'npart'-th part of the status bar
  if (Int_t(fStatusBar.size()) > partidx) {
    if (stype >=  0) {
       TColor *rootColor = gROOT->GetColor(stype);
       float rgb[3];
       rootColor->GetRGB(rgb[0],rgb[1],rgb[2]);
       fStatusBar[partidx]->setPaletteForegroundColor(QColor(int(255*rgb[0]),int(255*rgb[1]),int(255*rgb[2])));
    }
    fStatusBar[partidx]->setText(text);
  }
}
//______________________________________________________________________________
void TQtGLViewerImp::SetUpdatesEnabled( bool enable)
{  
   setUpdatesEnabled(enable); 
   if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setUpdatesEnabled(enable);
}
//______________________________________________________________________________
bool  TQtGLViewerImp::GetUpdatesEnabled() const
{ 
   return fGLWidget? fGLWidget->isUpdatesEnabled() : isUpdatesEnabled(); 
}

//______________________________________________________________________________
void TQtGLViewerImp::ShowStatusBar(Bool_t show)
{
   // Show / Hide the status bar
   
  if (show) statusBar()->show();
  else      statusBar()->hide();
}
//______________________________________________________________________________
 void  TQtGLViewerImp::DisconnectPad()
 {
    fPad = 0;
 }
//______________________________________________________________________________
TVirtualPad *TQtGLViewerImp::GetPad() 
{
   if (GetGLView()) return GetGLView()->GetPad();
   return fPad;
}
//______________________________________________________________________________
//
// Slots
//______________________________________________________________________________
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectorWidgetCB(bool on)
{
     // Active the separate window to show the selected objects
    fSelectedViewActive =  on;
    CreateSelectionViewer();
}
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectionHighlighCB(bool on)
{
     // Active the separate window to show the selected objects
    fSelectionHighlight  =  on;
}
//______________________________________________________________________________
void TQtGLViewerImp::ActivateSelectionGlobalCB(bool on)
{
     // Show the selected object on the global coordinate system
    fShowSelectionGlobal =  on;
}

//______________________________________________________________________________
void TQtGLViewerImp::AddGLList(unsigned int list, EObject3DType type)
{
	// printf("TQtGLViewerImp::AddGLList");
   QWidget *c = centralWidget();
   if (!c) return;   
#ifdef QGLVIEWER
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     switch (type) {
     case TGLViewerImp::kWired:
        glView->addGLList(list, TQtGLViewerWidget::kWired);
        break;
     case TGLViewerImp::kSolid: default:
        glView->addGLList(list, TQtGLViewerWidget::kSolid);
        break;
     case TGLViewerImp::kSelecting:
        glView->addGLList(list, TQtGLViewerWidget::kSelecting);
        break;
     };
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::RemoveGLList(unsigned int list)
{
   QWidget *c = centralWidget();
   if (!c) return;   
#ifdef QGLVIEWER
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     glView->removeGLList(list);
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::NewViewer(){
  new TQtGLViewerImp(GetGLView());
}
//______________________________________________________________________________
void TQtGLViewerImp::PrintCB(){
   QPrinter p;
   QWidget *c = centralWidget();
   if (c && p.setup()) {
      QPainter pnt(&p);
        QGLWidget *glView = (QGLWidget *)c;
        if (glView) pnt.drawImage(0,0,glView-> grabFrameBuffer());
      pnt.end();
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::CopyCB()
{
 //  Copy the current x3d view to the system clipboard 
   QWidget *c = centralWidget();
   if (c) { 
      QClipboard *cb = QApplication::clipboard();
      cb->setPixmap(QPixmap::grabWindow(c->winId () )) ;
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::CopyFrameCB()
{
   // Copy the entire window including the menu and the status bar
   QClipboard *cb = QApplication::clipboard();
   cb->setPixmap(QPixmap::grabWidget(topLevelWidget()));
}
//______________________________________________________________________________
void TQtGLViewerImp::ReadInputFile(const char * /*fileName*/ )
{
   // Read the extrernal OpenInventor file
   //This implementation can not do this
   QMessageBox::critical(0, "OpenGL Viewer","Can not render the Open Inventor scene"
         , QMessageBox::Ok, QMessageBox::NoButton);
   
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveCB()
{ 
   QWidget *c = centralWidget();
   if (!c) return;
   if (fSaveFile.IsNull()) 
      SaveAsCB();
   else {
#ifndef QGLVIEWER
     QGLWidget *glView = (QGLWidget *)c;
     glView-> grabFrameBuffer().save(fSaveFile.Data(),fSaveType.Data());
#else
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     glView->setSnapshotFileName  (fSaveFile.Data());
     glView->saveSnapshot(true);
     fSaveFile = (const char*) glView->snapshotFileName();
#endif
  }
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveAsCB()
{ 
   QWidget *c = centralWidget();
   if (!c) return;
#ifndef QGLVIEWER
   QString filter = 
     "Image (";

   QString defExtension[] = {"bmp","C"};

   UInt_t i;
   for (i = 0; i < QImageIO::outputFormats().count(); i++ ) 
   {
      if (i) filter +=',';
      filter += "*.";
      QString str = QString( QImageIO::outputFormats().at( i ) );
      filter += str.lower();
   }
   filter +=");;";

   QString selectedFilter;

   QString thatFile = QFileDialog::getSaveFileName(
#if QT_VERSION < 0x40000
          gSystem->WorkingDirectory()
        , filter, centralWidget(), "SaveAs"
        , tr("Save the current 3D view as")
        , &selectedFilter
        );
#else /* QT_VERSION */
         centralWidget(),
       , tr("Save the current 3D view as")
       , gSystem->WorkingDirectory()
       , filter
       , &selectedFilter
       );
#endif /* QT_VERSION */

   if (thatFile.isEmpty()) return;
 
   UInt_t nExt = sizeof(defExtension)/sizeof(const char *);
   QString e;
   for (i = 0; i < nExt-1; i++) {
     e = '.'; e += defExtension[i];
     if (selectedFilter.contains(e)) break;
   }

   if (! thatFile.contains('.'))  thatFile += '.';
   if (thatFile.at(thatFile.length()-1) == '.')  thatFile += defExtension[i];

   fSaveFile = (const char *)thatFile;
   QGLWidget *glView = (QGLWidget *)c;
   glView-> grabFrameBuffer().save(fSaveFile.Data(),fSaveType.Data());
#else
     TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
     glView->saveSnapshot(false);
     fSaveFile = (const char *)glView->snapshotFileName( );
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveSnapShot(bool)
{
#ifdef QGLVIEWER
//  QString filename(fSaveFile.Data());
//  glView->saveSnapshot("STAR",true);
    if (fSaveFile.IsNull()) {
       SaveAsCB();
    } else {
       // raise the widget
       QWidget *c = centralWidget();
       TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
       TVirtualPad *thisPad= GetPad();
       QString footer(thisPad->GetTitle());
       glView->setFooter(footer);
       
       // raise();
       
       glView->saveSnapshot(true,true);
       if (fMaxSnapFileCounter <= 2) {
          SaveHtml(glView->snapshotCounter()-1);
          float x,y,z;
          if (glView->RotationAxisAngle(x,y,z)< 0.02) {
             CopyFile(QString(fSaveFile.Data()),glView->snapshotCounter()-1);
          }
       }
       if (glView->snapshotCounter() ==  fMaxSnapFileCounter) glView->setSnapshotCounter(0);
   }
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::CopyFile(const QString &fileName2Copy,Int_t counter)
{
  QFileInfo infoOldFile(fileName2Copy);
  QString newName = infoOldFile.dirPath() + "/" + infoOldFile.baseName(TRUE) +
  "_S."+infoOldFile.extension(FALSE); 
  QFileInfo infoNewFile(newName);

QString shellCommand;
#ifndef WIN32  
   shellCommand = "cd " + infoOldFile.dirPath(true)  + " && " +
                  "cp " + infoOldFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoOldFile.extension(FALSE)
                       + "   " + infoNewFile.baseName(TRUE) + "-000" + QString::number(counter) + "."
                         + infoNewFile.extension(FALSE);
#else
   shellCommand = 
                 "copy " + infoOldFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoOldFile.extension(FALSE)
                         + "   " + infoNewFile.baseName(TRUE) + "-000" + QString::number(counter) + "." + infoNewFile.extension(FALSE);
#endif
   gSystem->Exec((const char*) shellCommand);
//   fprintf(stderr," ==Copy==  %s \n", (const char*) shellCommand);

   SaveHtml(newName,counter);
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveHtml(Int_t counter)
{
   if (fSaveFile.IsNull())  SaveAsCB();
   if (!fSaveFile.IsNull()) {
     QString f(fSaveFile.Data());
     SaveHtml(f,counter);
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::SaveHtml(QString &saveFile, Int_t counter)
{
#if 0
   if (fSaveFile.IsNull()) {
       SaveAsCB();
   }
   if (fSaveFile.IsNull()) return;
   
   QFileInfo info(fSaveFile.Data());
#else
   if (saveFile.isEmpty()) return;
   
   QFileInfo info(saveFile);
#endif   
   QString htmlFile(  info.dirPath(true) + "/" + info.baseName(TRUE) + "-000" +
                      QString::number(counter) +".html");
#ifdef GENERATE_HTML
   TVirtualPad *thisPad= GetPad();
   QString caption = thisPad->GetTitle();
   FILE *f = fopen((const char*)htmlFile, "w+");
   if (f) {
   QTextOStream(f) << "<html>"   << endl; 
   QTextOStream(f) << "<title>"  << endl;
   QTextOStream(f) <<  caption << endl;
//   QTextOStream(f) <<  caption() << endl;
   QTextOStream(f) << "</title>" << endl;
   QTextOStream(f) << "<head>"   << endl;
   QTextOStream(f) << "<meta http-equiv=\"REFRESH\" content=\"15\">" << endl;
   QTextOStream(f) << "</head>"  << endl;
   QTextOStream(f) << "<body>"   << endl;
   QTextOStream(f) << "<center>" << endl;
   QTextOStream(f) << "<H2> <a href=\"http://www.star.bnl.gov\">STAR@rhic</a></H2><br>" << endl;
//   QTextOStream(f) << "<H3>" << caption() << "</H3><br><hr><br>"   << endl;
   QTextOStream(f) << "<H3>" << caption << "</H3><br><hr><br>"   << endl;
   QTextOStream(f) << "<img src=\"" << info.baseName(TRUE) << "-000" + 
     QString::number(counter) + "." <<info.extension(FALSE)  << "\">" << endl;
//     QString::number(counter) + "." <<info.extension(FALSE)  << "\" width=100%>" << endl;
   QTextOStream(f) << "</center>"<< endl;
   QTextOStream(f) << "</body>"  << endl;
   QTextOStream(f) << "</html>"  << endl;
   fflush(f);
   fclose(f);
#ifndef WIN32  
   QString shellCommand =  "cd " + info.dirPath(true)  + " && " 
                         + "mv   " + info.baseName(TRUE) + "-000" + QString::number(counter) +".html "
                         + info.baseName(TRUE) + ".html";
#else
   QString shellCommand =  "cd  " + info.dirPath(true)  + " && " 
                         + "ren " + info.baseName(TRUE) + "-000" + QString::number(counter) +".html "
                                  + info.baseName(TRUE) + ".html";
#endif                         
#else
   QString shellCommand;
   QFileInfo html(htmlFile);
   if (html.exists() && html.isReadable() ) {
#ifndef WIN32
           shellCommand =  "cd " + info.dirPath(true)  + " && " 
                         + "cp " + htmlFile   + " "
                                 + "." + info.baseName(TRUE) + ".html && "
                         + "mv " + "." + info.baseName(TRUE) + ".html " + info.baseName(TRUE) + ".html";
#else
          shellCommand =   "cd  " + info.dirPath(true)  + " && "
                         + "copy "+ htmlFile            + "   "
                                  + "." + info.baseName(TRUE) + ".html && "
                         + "ren  "+ "." + info.baseName(TRUE) + ".html " + info.baseName(TRUE) + ".html";
#endif
   }
#endif
    if (!shellCommand.isEmpty())  gSystem->Exec((const char*) shellCommand);
    // fprintf(stderr," ***  %s \n", (const char*) shellCommand);
#ifdef GENERATE_HTML
   } else {
      char buffer[100];
      sprintf(buffer,"TQtGLViewerImp::SaveHtml file %s", (const char*)htmlFile);
      perror(buffer);
      assert(0);
   }
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SelectEventCB(bool on)
{
    // Toggle the widget the "wried object selecction mode
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (glView) glView->SetWiredSelectable(on);
}
//______________________________________________________________________________
void TQtGLViewerImp::SelectDetectorCB(bool on)
{
   // Toggle the widget the "wried object selecction mode
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (glView) glView->SetSolidSelectable(on);
}

//______________________________________________________________________________
void TQtGLViewerImp::SnapShotSaveCB(bool on)
{  
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   // Adjust the menu indicator if any
   if (fSnapShotAction) {
      bool snapStatus = fSnapShotAction->isOn();
      if (snapStatus != on ) {
         blockSignals (true);
         fSnapShotAction->setOn(on);
         blockSignals (false);
      }
   }
   if (on) {
         // fGLWidget->resize(720, 576); // PAL DV format (use 720x480 for NTSC DV)
       raise();
       connect(glView, SIGNAL(drawFinished(bool)), this, SLOT(SaveSnapShot(bool)));
    } else {
       disconnect(glView, SIGNAL(drawFinished(bool)), this, SLOT(SaveSnapShot(bool)));
    }
}

//______________________________________________________________________________
void TQtGLViewerImp::SynchTPadCB(bool on)
{  
    SetPadSynchronize(on);
}

//______________________________________________________________________________
void TQtGLViewerImp::ShowFrameAxisCB(bool on)
{  
#ifdef QGLVIEWER
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   if (on) 
      glView->SetFrameAxisFactor(5.0);
   else 
      glView->SetFrameAxisFactor(-1);
   glView->update();
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::ShowLightsCB(bool on)
{  
#ifdef QGLVIEWER
   QWidget *c = centralWidget();
   TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;
   glView->setDrawLight(on);glView->update();
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::ViewAll()
{
   // view the entire scene
   if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->ViewAll();
}

//______________________________________________________________________________
void TQtGLViewerImp::WantRootContextMenuCB(bool on)
{
  // Create "ROOT Context menu" otherwise use the QGLViewer "right mouse click"
  fWantRootContextMenu = on; 
}
//______________________________________________________________________________
void TQtGLViewerImp::AboutCB()
{ 
   QMessageBox::aboutQt(0);
   QString rootVersion = "ROOT ";
   rootVersion += gROOT->GetVersion();
   rootVersion += "with Qt interface";
   QMessageBox::about(0,rootVersion
     ,"ROOT Qt interface Copyright (C) 2001-2005, Valeri Fine. Brookhaven National Laboratory. All right reserved.");
}
//______________________________________________________________________________
void TQtGLViewerImp::HelpCB()
{
   // Show TGLWidget command key values
#ifndef QGLVIEWER
   TQtGLWidget *c = dynamic_cast<TQtGLWidget *>(centralWidget());
   if (c) c->ShowHelp();
#else
   TQtGLViewerWidget *c = dynamic_cast<TQtGLViewerWidget *>(centralWidget());
   if (c) c->help();
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::CreateViewer(const char *name)
{
   if (!fGLWidget) {
      if (fPad) {
      fGLWidget = 
#ifndef QGLVIEWER
                 new TQtGLWidget      ( fPad,name,this);
#else
                 new TQtGLViewerWidget( fPad, name, this );
#endif
      } else {
      fGLWidget = 
#ifndef QGLVIEWER
                 new TQtGLWidget      (GetGLView(),name,this);
#else
                 new TQtGLViewerWidget( GetGLView(), name, this );
#endif
      }
      setCentralWidget (fGLWidget);
#ifdef QGLVIEWER
      ((TQtGLViewerWidget *)fGLWidget)->setSnapshotFileName  (fSaveFile.Data());
      connect(fGLWidget,SIGNAL(objectSelected(TObject*,const QPoint &)),this,SLOT( ShowObjectInfo(TObject *, const QPoint&)));
      connect(fGLWidget,SIGNAL(objectSelected(TObject*,const QPoint &)),&this->Signals(),SIGNAL( ObjectSelected(TObject *, const QPoint&)));
#endif
   };
}
//______________________________________________________________________________
void TQtGLViewerImp::CreateViewer(QGLWidget *share, const char *name)
{
   // Create satellite viewe to share the same GL lists
   if (!fGLWidget) {
      fGLWidget = new TQtGLViewerWidget( this,name,share );
      TQtGLViewerWidget *glw = (TQtGLViewerWidget *)fGLWidget;
#if 0      
      glw->setSceneCenter(((TQtGLViewerWidget *)share)->sceneCenter());
      glw->setSceneRadius(((TQtGLViewerWidget *)share)->sceneRadius());
      glw->setBackgroundColor(((TQtGLViewerWidget *)share)->backgroundColor());
#endif      
      glw->makeCurrent();
      glw->setSceneCenter(((TQtGLViewerWidget *)share)->sceneCenter());
      glw->setSceneRadius(((TQtGLViewerWidget *)share)->sceneRadius());
      glw->setBackgroundColor(((TQtGLViewerWidget *)share)->backgroundColor());

      setCentralWidget (fGLWidget);
      glw->setSnapshotFileName  (fSaveFile.Data());
      connect(fGLWidget,SIGNAL(objectSelected(TObject*,const QPoint &)),this,SLOT( ShowObjectInfo(TObject *, const QPoint&)));
   }
}
//______________________________________________________________________________
void TQtGLViewerImp::MakeCurrent() 
{
#ifdef QGLVIEWER
   fGLWidget->makeCurrent();
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::MakeMenu()
{
   // Create a "save" action
   QAction *saveAction = 
#if QT_VERSION < 0x40000
    new QAction("Save", "&Save", CTRL+Key_S, this, "save" );
   connect ( saveAction, SIGNAL( activated() ) , this, SLOT( SaveCB() ) );
#else /* QT_VERSION */
    new QAction("&Save", this);
   connect ( saveAction, SIGNAL( triggered() ) , this, SLOT( SaveCB() ) );
#endif /* QT_VERSION */

   const char * saveText = "<p><img source=\"save\"> "
                "Click this button to save a <em>3D image</em>to the current image file. <br>"
                "You can also select the <b>Save</b> command "
                "from the <b>File</b> menu.</p>";
   saveAction->setWhatsThis( tr(saveText) );

   // Create a "save as" action
#if QT_VERSION < 0x40000
   QAction *saveAsAction =  new QAction("SaveAs", "Save As", CTRL+Key_A, this, "saveas" );
   connect ( saveAsAction, SIGNAL( activated() ) , this, SLOT( SaveAsCB() ) );
#else /* QT_VERSION */
   QAction *saveAsAction =  new QAction("Save &As", this);
   connect ( saveAsAction, SIGNAL(triggered() ) , this, SLOT( SaveAsCB() ) );
#endif /* QT_VERSION */

   const char * saveAsText = "<p><img source=\"save\"> "
                "Click this button to select file and save a <em>3D image</em>there. <br>"
                "You can also select the <b>Save As</b> command "
                "from the <b>File</b> menu.</p>";
   saveAsAction->setWhatsThis( tr(saveAsText) );
 
   // Create a "save as" action
#if QT_VERSION < 0x40000
   fSnapShotAction  =  new QAction("snapShot", "SnapShotSave", CTRL+Key_O, this, "snapshot" );
   fSnapShotAction->setToggleAction(true);
#else /* QT_VERSION */
   fSnapShotAction  =  new QAction("SnapSh&otSave", this);
   fSnapShotAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( fSnapShotAction, SIGNAL( toggled(bool) ) , this, SLOT( SnapShotSaveCB(bool) ) );

   const char * snapShotText = "<p><img source=\"snapshot\"> "
                "Click this button to save the image each time the frame is updated";
   fSnapShotAction->setWhatsThis( tr(snapShotText) );

   // Create a "print" action
#if QT_VERSION < 0x40000
   QAction *printAction =  new QAction("Print", "&Print", CTRL+Key_P, this, "print" );
   connect ( printAction, SIGNAL( activated() ) , this, SLOT( PrintCB() ) );
#else /* QT_VERSION */
   QAction *printAction =  new QAction("&Print", this);
   connect ( printAction, SIGNAL( triggered () ) , this, SLOT( PrintCB() ) );
#endif /* QT_VERSION */

   const char * printText = "<p><img source=\"print\"> "
                "Click this button to print a <em>3D image</em>. <br>"
                "You can also select the <b>Print</b> command "
                "from the <b>File</b> menu.</p>";
   printAction->setWhatsThis( printText );

   // Create a "copy" action
#if QT_VERSION < 0x40000
   QAction *copyAction =  new QAction("Copy", "&Copy", CTRL+Key_C, this, "copy" );
   connect ( copyAction, SIGNAL( activated() ) , this, SLOT( CopyCB() ) );
#else /* QT_VERSION */
   QAction *copyAction =  new QAction("&Copy", this );
   connect ( copyAction, SIGNAL( triggered() ) , this, SLOT( CopyCB() ) );
#endif /* QT_VERSION */

   const char * copyText = "<p><img source=\"copy\"> "
                "Click this button to copy a <em>3D image</em>to the system clipborad. <br>"
                "You can also select the <b>Copy</b> command "
                "from the <b>Edit</b> menu.</p>";
   copyAction->setWhatsThis( tr(copyText) );
 
    // Create a "copy frame" action
#if QT_VERSION < 0x40000
   QAction *copyFrameAction =  new QAction("Frame", "Copy &Frame", CTRL+Key_F, this, "frame" );
   connect ( copyFrameAction, SIGNAL( activated() ) , this, SLOT( CopyFrameCB() ) );
#else /* QT_VERSION */
   QAction *copyFrameAction =  new QAction("Copy &Frame", this);
   connect ( copyFrameAction, SIGNAL( triggered() ) , this, SLOT( CopyFrameCB() ) );
#endif /* QT_VERSION */
   const char * copyFrameText = "<p><img source=\"frame\"> "
                "Click this button to copy a <em>tge frame of the 3D image</em>to the system clipborad. <br>"
                "You can also select the <b>Copy Frame</b> command "
                "from the <b>Edit</b> menu.</p>";
   copyFrameAction->setWhatsThis( tr(copyFrameText) );

   // Create "close" action
#if QT_VERSION < 0x40000
   QAction *fileCloseAction = new QAction( "Close", "&Close", Qt::ALT+Qt::Key_F4, this,
      "close" );
   connect ( fileCloseAction, SIGNAL( activated() ) , this,  SLOT( close() ) );
#else
   QAction *fileCloseAction = new QAction("&Close", this);
   fileCloseAction->setShortcut(Qt::ALT+Qt::Key_F4);   
   connect ( fileCloseAction, SIGNAL( triggered() ) , this,  SLOT( close() ) );
#endif

   // Synchronize TPad rotation 
   
#if QT_VERSION < 0x40000
   QAction *synchAction =  new QAction("TPadSynch", "Synchromize with TPad", CTRL+Key_I, this, "synch" );
   synchAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *synchAction =  new QAction("Synchrom&ize with TPad", this);
   synchAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( synchAction, SIGNAL( toggled(bool) ) , this, SLOT( SynchTPadCB(bool)  ) );
   const char * synchText = "<p><img source=\"frame\"> "
                "Select this option if your want the OpenGL view follows the <b>TPad</B> rotation";
   synchAction->setWhatsThis( tr(synchText) );

   // Synchronize TPad rotation 
   
#ifdef QGLVIEWER
#if QT_VERSION < 0x40000
   QAction *showFrameAxisAction =  new QAction("Frame3DAxis", "Show Frame axis", CTRL+Key_1, this, "frameaxis" );
   showFrameAxisAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *showFrameAxisAction =  new QAction("Show Frame axis", this);
   showFrameAxisAction->setShortcut(Qt::ALT+Qt::Key_1);
   showFrameAxisAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( showFrameAxisAction, SIGNAL( toggled(bool) ) , this, SLOT( ShowFrameAxisCB(bool)  ) );
   const char *showFrameAxisText = "Show the ROOT 3D object axis";
   showFrameAxisAction->setWhatsThis( tr(showFrameAxisText));

#if QT_VERSION < 0x40000
   QAction *showLightsAction =  new QAction("GLLights", "Show &light", CTRL+Key_L, this, "gllight" );
   showLightsAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *showLightsAction =  new QAction("Show &light", this);
   showLightsAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( showLightsAction, SIGNAL( toggled(bool) ) , this, SLOT( ShowLightsCB(bool)  ) );
   const char * showLightsText = "<p><img source=\"frame\"> "
                "Show the light source to debug the code";
   showLightsAction->setWhatsThis( showLightsText );
   
   // Create a "Event selectable" action
#if QT_VERSION < 0x40000
   QAction *selectEventAction =  new QAction("Event", "Select Event", CTRL+Key_E, this, "event" );
   selectEventAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *selectEventAction =  new QAction("Select &Event", this);
   selectEventAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( selectEventAction, SIGNAL( toggled(bool) ) , this, SLOT( SelectEventCB(bool) ) );
   const char * selectEventText = "Turn this option on to be able to select the <b>event</b> (tracks and hits)  and similar \"wired\" object";
   selectEventAction->setWhatsThis( tr(selectEventText));
   
   // Create a "Detector selectable" action
#if QT_VERSION < 0x40000
   QAction *selectDetectorAction =  new QAction("Detector", "Select Detector", CTRL+Key_D, this, "detector" );
   selectDetectorAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *selectDetectorAction =  new QAction("Select &Detector", this);
   selectDetectorAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( selectDetectorAction, SIGNAL( toggled(bool)  ) , this, SLOT( SelectDetectorCB(bool) ) );
   const char * selectDetectorText = "Turn this option on to be able to select the <b>detector</b> (solid) objects";
   selectDetectorAction->setWhatsThis(  selectDetectorText);

   // Create a "Detector selectable" action
#if QT_VERSION < 0x40000
   QAction *viewSelectionAction =  new QAction("Selection", "Show the selected object", CTRL+Key_T, this, "selection" );
   viewSelectionAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *viewSelectionAction =  new QAction("Show the selec&ted object",this);
   viewSelectionAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( viewSelectionAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectorWidgetCB(bool) ) );
   const char * viewSelectionActionText = "Turn this option on to see the selected object with the dedicted view";
   viewSelectionAction->setWhatsThis( viewSelectionActionText );

   // Show  the "selected object" with the separate widget using the global coordinate
#if QT_VERSION < 0x40000
   QAction *viewSelectionGlobalAction =  new QAction("SelectionGlobal", "Show the selected object in global system", CTRL+Key_I, this, "selectionglobal" );
   viewSelectionGlobalAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *viewSelectionGlobalAction =  new QAction("Show the selected object &in global system",  this);
   viewSelectionGlobalAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( viewSelectionGlobalAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectionGlobalCB(bool) ) );
   connect ( viewSelectionAction, SIGNAL( toggled(bool)  ), viewSelectionGlobalAction, SLOT( setEnabled(bool) ) );
   const char * viewSelectionGlobalActionText = "Turn this option on to show the selected object in the global coordinate system";
   viewSelectionGlobalAction->setWhatsThis( viewSelectionGlobalActionText );

   // Create a "Highlight the selected object" action
#if QT_VERSION < 0x40000
   QAction *viewSelectionHighlightAction =  new QAction("SelectionHighLight", "Highlight the selected object", CTRL+Key_I, this, "selectionhighlight" );
   viewSelectionHighlightAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *viewSelectionHighlightAction =  new QAction("Highl&ight the selected object", this);
   viewSelectionHighlightAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( viewSelectionHighlightAction, SIGNAL( toggled(bool)  ) , this, SLOT( ActivateSelectionHighlighCB(bool) ) );
   const char * viewSelectionHighlightActionText = "Turn this option on to highlight the selected object";
   viewSelectionHighlightAction->setWhatsThis( viewSelectionHighlightActionText );
 
   // Create a "Context Menu for  the selected object" action
#if QT_VERSION < 0x40000
   QAction *viewContextMenuAction =  new QAction("ContexteMenu", "Context menu", CTRL+Key_I, this, "contextmenu" );
   viewContextMenuAction->setToggleAction(true);
#else /* QT_VERSION */
   QAction *viewContextMenuAction =  new QAction("Context menu", this);
   viewContextMenuAction->setCheckable(true);
#endif /* QT_VERSION */
   connect ( viewContextMenuAction, SIGNAL( toggled(bool)  ) , this, SLOT( WantRootContextMenuCB(bool) ) );
   const char * viewContextMenuActionText  = "Show the ROOT context menu for the selected ROOT object";
   viewContextMenuAction->setWhatsThis( viewContextMenuActionText );
#endif
  
   QMenuBar   *mainMenu = menuBar();

   // -- populate the menu bar
#if QT_VERSION < 0x40000
      QPopupMenu *fileMenu      = new QPopupMenu();
      mainMenu->insertItem("&File",fileMenu);
 
      QPopupMenu *editMenu      = new QPopupMenu();
      mainMenu->insertItem("&Edit",editMenu);

      QPopupMenu *optionMenu    = new QPopupMenu();
      mainMenu->insertItem("&Options",optionMenu);

      QPopupMenu *helpMenu   = new QPopupMenu();
      mainMenu->insertItem("&Help",helpMenu);      
  // -- The menu bar has been completed

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  fileMenu
   
   saveAction     ->addTo(fileMenu);
   saveAsAction   ->addTo(fileMenu);
   fSnapShotAction->addTo(fileMenu);
                    fileMenu->insertSeparator();
   printAction    ->addTo(fileMenu);
                    fileMenu->insertSeparator();
   fileCloseAction->addTo(fileMenu);


 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  editMenu
    copyAction     ->addTo(editMenu);
    copyFrameAction->addTo(editMenu);
   
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  optionMenu
    synchAction->addTo(optionMenu);
    synchAction->setOn(true);
    synchAction->setEnabled (true);
#ifdef QGLVIEWER
    QWidget *c = centralWidget();
    TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;

    showFrameAxisAction->addTo(optionMenu);
    showFrameAxisAction->setOn(glView? glView->FrameAxisScale()> 0 : false);
    showFrameAxisAction->setEnabled(true);

    showLightsAction->addTo(optionMenu);
    showLightsAction->setOn(false);
    showLightsAction->setEnabled (true);

    
    optionMenu->insertSeparator();

    selectEventAction->addTo(optionMenu);
    selectEventAction->setOn(glView ? glView->IsWiredSelectable() : false );
    selectEventAction->setEnabled (true);

    selectDetectorAction->addTo(optionMenu);
    selectDetectorAction->setOn( glView ? glView->IsSolidSelectable() : false );
    selectDetectorAction->setEnabled (true);
    
    optionMenu->insertSeparator();
    
    viewSelectionAction->addTo(optionMenu);
    viewSelectionAction->setOn( false );
    viewSelectionAction->setEnabled (true);
    
    viewSelectionGlobalAction->addTo(optionMenu);
    viewSelectionGlobalAction->setOn( false );
    viewSelectionGlobalAction->setEnabled (false);

    viewSelectionHighlightAction->addTo(optionMenu);
    viewSelectionHighlightAction->setOn( false );
    viewSelectionHighlightAction->setEnabled (true);
    
    viewContextMenuAction->addTo(optionMenu);
    viewContextMenuAction->setOn( false );
    viewContextMenuAction->setEnabled (true);

#endif
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  helpMenu
    helpMenu->insertItem("&Help",this,SLOT(HelpCB()));
    helpMenu->insertSeparator();
    helpMenu->insertItem("&About",this,SLOT(AboutCB()));
#else
    QMenu *fileMenu      = mainMenu->addMenu("&File");
    QMenu *editMenu      = mainMenu->addMenu("&Edit");
    QMenu *optionMenu    = mainMenu->addMenu("&Options");
    QMenu *helpMenu      = mainMenu->addMenu("&Help");      
  // -- The menu bar has been completed

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  fileMenu
   
   fileMenu->clear();
   fileMenu->addAction(saveAction);
   fileMenu->addAction(saveAsAction);
   fileMenu->addAction(fSnapShotAction);
                    fileMenu->addSeparator();
   fileMenu->addAction(printAction);
                    fileMenu->addSeparator();
   fileMenu->addAction(fileCloseAction);


 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  editMenu
    editMenu->clear();
    editMenu->addAction(copyAction);
    editMenu->addAction(copyFrameAction);
   
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  optionMenu
    optionMenu->clear();
    optionMenu->addAction(synchAction);
    synchAction->setChecked(true);
    synchAction->setEnabled (true);
#ifdef QGLVIEWER
    QWidget *c = centralWidget();
    TQtGLViewerWidget *glView = (TQtGLViewerWidget *)c;

    optionMenu->addAction(showFrameAxisAction);
    showFrameAxisAction->setChecked(glView? glView->FrameAxisScale()> 0 : false);
    showFrameAxisAction->setEnabled(true);

    optionMenu->addAction(showLightsAction);
    showLightsAction->setChecked(false);
    showLightsAction->setEnabled (true);

    
                  optionMenu->addSeparator();

    optionMenu->addAction(selectEventAction);
    selectEventAction->setChecked(glView ? glView->IsWiredSelectable() : false );
    selectEventAction->setEnabled (true);

    optionMenu->addAction(selectDetectorAction);
    selectDetectorAction->setChecked( glView ? glView->IsSolidSelectable() : false );
    selectDetectorAction->setEnabled (true);
    
    optionMenu->addSeparator();
    
    optionMenu->addAction(viewSelectionAction);
    viewSelectionAction->setChecked( false );
    viewSelectionAction->setEnabled (true);
    
    optionMenu->addAction(viewSelectionGlobalAction);
    viewSelectionGlobalAction->setChecked( false );
    viewSelectionGlobalAction->setEnabled (false);

    optionMenu->addAction(viewSelectionHighlightAction);
    viewSelectionHighlightAction->setChecked( false );
    viewSelectionHighlightAction->setEnabled (true);
    
    optionMenu->addAction(viewContextMenuAction);
    viewContextMenuAction->setChecked( false );
    viewContextMenuAction->setEnabled (true);

#endif
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 //  helpMenu
    helpMenu->clear();
    helpMenu->addAction("&Help",this,SLOT(HelpCB()));
    helpMenu->addSeparator();
    (helpMenu->addAction("&About",this,SLOT(AboutCB())))->setMenuRole(QAction::AboutRole);
#endif /* QT_VERSION */    
}
//______________________________________________________________________________
void TQtGLViewerImp::Paint(Option_t *opt)
{
   CreateViewer();
#ifndef QGLVIEWER
   TGLViewerImp::Paint(opt);
#else
   if (opt){;}
   Update();
#endif

  //// Paint G3D objects  
  // Int_t myGLIst = GetGLView()->GetGLList()-1;
  // assert(myGLIst );
  // if (myGLIst) {

  //   // Pick the current TPad rotation
  //   gVirtualGL->RunGLList(myGLIst + TPadOpenGLView::kView);

  //   // Draw G3D objects
  //   gVirtualGL->RunGLList(myGLIst + TPadOpenGLView::kModel);
  // }
}

//______________________________________________________________________________
void TQtGLViewerImp::Update()
{  
   CreateViewer();
#ifdef QGLVIEWER
   if (fGLWidget && !fSelectionViewer) 
      ((TQtGLViewerWidget*)fGLWidget)->SetSceneLayout();
#endif
   TGLViewerImp::Update();
   centralWidget()->update();
}
//______________________________________________________________________________
void TQtGLViewerImp::SetFooter(QString &text)
{
   // Set the footer text
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setFooter(text);
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SetPadSynchronize(Bool_t on)
{
  // Define whether the GL Widget view should follow TPad rotation
#ifndef QGLVIEWER
   if(on) {} // QtGLWidget provide no synch means
#else
   if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setPadSynchronize(on);
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::EnableObjectPick(bool enable)
{
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->EnableObjectPick(enable);
#endif
}
//______________________________________________________________________________
bool TQtGLViewerImp::ObjectPickEnabled() const
{
   return fGLWidget ? ((TQtGLViewerWidget*)fGLWidget)->ObjectPickEnabled():false;
}
//______________________________________________________________________________
void TQtGLViewerImp::SetFullScreenView(bool on)
{
   // set the full screen view mode if available
   // Shows the widget in full-screen mode.
   if (on) showFullScreen();
   else    showNormal();
   // if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->SetFullScreenView();
}
//______________________________________________________________________________
void TQtGLViewerImp::SetFooter(const char *text)
{
   // Assign the text for the footer
  QString f(text);
  SetFooter(f);
}
//______________________________________________________________________________
bool TQtGLViewerImp::IsFullScreen()  const  
{
   // Returns TRUE if the widget is full screen 
   return isFullScreen();
  
}
//______________________________________________________________________________
void TQtGLViewerImp::SetRotationAxisAngle(const float x, const float y, const float z, const float a)
{
   // Set the current rotation of the frame. 
   // Parameters are the rotation axis vector and its angle (in radians). 
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->setRotationAxisAngle(x,y,z,a);
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SetBackgroundColor(Color_t color)
{
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->SetBackgroundColor(color);
#endif
}
//______________________________________________________________________________
void TQtGLViewerImp::SetBackgroundColor(const TColor *color)
{
#ifdef QGLVIEWER
  if (fGLWidget) ((TQtGLViewerWidget*)fGLWidget)->SetBackgroundColor(color);
#endif
} 
//______________________________________________________________________________
void TQtGLViewerImp::ShowObjectInfo(TObject *obj, const QPoint &cursorPosition)
{
   //  Qt Slot to accept the signal emiited by the GL Widget selecting the ROOT object
   static QRect previousTipArea;
   QString tipText = obj->GetObjectInfo(cursorPosition.x(),cursorPosition.y());
   
   SetStatusText(obj->GetName(), 0);
   Color_t objectColor = -1;
   if (obj->InheritsFrom("TAttLine")) {
      TAttLine *lAttr = dynamic_cast<TAttLine *>(obj);
      if (lAttr)  objectColor =  lAttr->GetLineColor();
   }
   SetStatusText(QString("%1,%2").arg(cursorPosition.x()).arg(cursorPosition.y()), 1,objectColor);
   SetStatusText(obj->ClassName(), 2);
   SetStatusText(tipText, 3);
   // Create a tooltip

   TQtGLViewerWidget *tipped = (TQtGLViewerWidget *)sender();
   QPoint globalPosition = tipped->mapToGlobal(cursorPosition);
#if QT_VERSION < 0x40000
   QWhatsThis::display(tipText, globalPosition,tipped);
#else /* QT_VERSION */
   QWhatsThis::showText(globalPosition,tipText,tipped);
#endif /* QT_VERSION */

   TObject3DView *view = (TObject3DView *)tipped->selectedName();

   // open a separate window to show the selection   
   if (fSelectedViewActive) {      
      if (!fSelectedView) 
         CreateSelectionViewer();
      else 
         fSelectedView->Clear();
      fSelectedView->setCaption(tipText);
      ULong_t id = 0;
      if (fShowSelectionGlobal) {
          if (!view->GetViewId(TObject3DViewFactoryABC::kSelected)) view->CompileSelection();
          id = view->GetViewId(TObject3DViewFactoryABC::kSelected);
      } else { 
          id = view->GetViewId();
      }
      fSelectedView->AddGLList(id, view->IsSolid() ? kSolid : kWired  );
//      fSelectedView->Update();
      fSelectedView->update();
   }
   if (fSelectionHighlight) {
      // remove the previouse selection
      tipped->clearGLList(TQtGLViewerWidget::kSelected);
      // Hightlight the new one
      if (!view->GetViewId(TObject3DViewFactoryABC::kSelected)) view->CompileSelection();
      tipped->addGLList(view->GetViewId(TObject3DViewFactoryABC::kSelected), TQtGLViewerWidget::kSelected);
   }
   // Display the context menu if any
   if (fWantRootContextMenu) {
      if (!fContextMenu) fContextMenu = new TContextMenu("3DViewContextMenu");
      TObject *obj = view->GetObject();
      if (obj) {
         QPoint pos = tipped->mapToGlobal(cursorPosition);
         fContextMenu->Popup(pos.x(),pos.y(), obj,(TBrowser *)0);
      }
   }
}

//______________________________________________________________________________
void TQtGLViewerImp::CreateSelectionViewer( ) 
{
   // Create another OpenGL viewer to show the selection 
   if (fSelectedViewActive && !fSelectedView)  {
      fSelectedView  = new TQtGLViewerImp(*this);
      fSelectedView->SelectEventCB(false);
      fSelectedView->SelectDetectorCB(false);
   }
}

//______________________________________________________________________________
ULong_t TQtGLViewerImp::GetViewerID() const
{
   return ULong_t((QMainWindow *) this);
}
//______________________________________________________________________________
void TQtGLViewerImp::SetSnapFileCounter(int counter)
{  fMaxSnapFileCounter = counter;                                              }
