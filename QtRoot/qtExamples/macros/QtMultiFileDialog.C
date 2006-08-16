// @(#)root/qt:$Name:  $:$Id: QtMultiFileDialog.C,v 1.1 2006/08/16 19:41:06 fine Exp $
// Author: Valeri Fine   23/03/2006
#ifndef __CINT__
#  include <qapplication.h> 
#  include <qstyle.h> 
#  include <qfiledialog.h> 
#  include <qstringlist.h> 
#  include <qstring.h> 
#  include "TObjString.h"
#  include "TList.h"
#endif
TList *QtMultiFileDialog(const char *style="") {
  // This is a small ROOT macro to use Qt 3.3 class :begin_html <a href="http://doc.trolltech.com/3.3/qfiledialog.html">QFileDialog</a> end_html
  // See: begin_html <a href="http://doc.trolltech.com/3.3/qfiledialog.html#getOpenFileNames">http://doc.trolltech.com/3.3/qfiledialog.html#getOpenFileNames</a> end_html
  //
  // To use, invoke ACLiC from the ROOT prompt:
  // root [] .x QtMultiFileDialog.C++
  //
  // To use it with no ACLiC, omit the trailing "++"
  // root [] .x QtMultiFileDialog.C
  //
  // The QtMultiFileDialog creates TList of TObjString objects and 
  // returns its pointer. 
  //
  // The "QtFileDialog.C" macro provides the simplified version of the "QtMultiFileDialog.C"
  //
  // Option: you can change the look and feel of the Qt file dialog
  // ======= by providing the optional parameter "style":
  //         The number of the available styles is defined by your local
  //         Qt installation. 
  //         Try: "windows", "motif", "kde", "platinum" etc
  //
  // The full list of the Qt classes available from Cint is defined by
  // begin_html <a href="http://root.bnl.gov/QtRoot/htmldoc/src/qtclasses.h.html">by $ROOTSYS/cint/lib/qtclasses.h</a> end_html
  //
  // All Qt classes can be used from ACLiC though.

#ifdef __CINT__
  // Load the qt cint dictionary.
  // One is recommended to do that at once somewhere.
  // For example  from his/her custom rootlogon.C script
  gSystem->Load("$ROOTSYS/cint/include/qtcint");
#endif   
  QStyle *saveStyle =  0;
  if (!QString(style).isEmpty()) { 
     saveStyle = &QApplication::style();
     QApplication::setStyle(style);
  }
  TList *listOfNames = new TList();
  QStringList files = QFileDialog::getOpenFileNames ();
  QStringList::Iterator it = files.begin();
  while ( it != files.end() ) {
      printf ("Next file selected: %s\n", (const char *)(*it));
      // Convert QString to TObjString and add it to the output
      listOfNames->Add(new TObjString((const char *)(*it)));
      ++it;
  }
  // Restore the style
  if (saveStyle) QApplication::setStyle(saveStyle);
  printf ("\nThe TList of the file names contains:");
  printf ("\n-------------------------------------\n");
  listOfNames->ls();
  return listOfNames;
}
