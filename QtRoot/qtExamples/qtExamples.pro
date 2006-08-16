TEMPLATE = subdirs

QTEXAMPLEPACKAGES   = ex1/tqrootexample.pro \
                      HelloCanvas           \
                      HelloWord             \
                      HelloLife             \
                      HelloZoomer

QTEXTENSIONEXAMPLES = QtGBrowser            \
                      CustomWidgets         \
                      CustomCanvasMenu
unix {
  exists($(ROOTSYS)/lib/libQtRootGui.so):       QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($(QTROOTSYSDIR)/lib/libQtRootGui.so):  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
}

win32 {
  exists($(ROOTSYS)/bin/libQtRootGui.dll):          QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($(QTROOTSYSDIR)/bin) {
      exists($(QTROOTSYSDIR)/bin/libQtRootGui.dll)  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
  }
}

exists($(ROOTSYS)/qtgsi) : QTEXAMPLEPACKAGES += qtgsi/example1

exists($(ROOTSYS)/include/rootcint.pri):   QTEXAMPLEPACKAGES += HelloCint

message("This project us to build $$QTEXAMPLEPACKAGES Qt/Root examples")
SUBDIRS = $$QTEXAMPLEPACKAGES
