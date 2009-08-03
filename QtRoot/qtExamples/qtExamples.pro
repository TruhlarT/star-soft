TEMPLATE = subdirs
QT += qt3support

QMAKE_RPATH=

QT_VERSION=$$[QT_VERSION]

contains( QT_VERSION, "^4.*" ) {
  LOCALROOTSYSDIR = $$(QTROOTSYSDIR)
  LOCALROOTSYS = $$(ROOTSYS)
}
!contains( QT_VERSION, "^4.*" ) {
  LOCALROOTSYSDIR = $$QTROOTSYSDIR
  LOCALROOTSYS    = $$ROOTSYS
}

QTEXAMPLEPACKAGES   = HelloCanvas           \
                      HelloWord             \
                      HelloClick            \
                      HelloZoomer

!contains( QT_VERSION, "^4.*" ) {
    QTEXAMPLEPACKAGES += ex1/tqrootexample.pro \
                      HelloLife
}

QTEXTENSIONEXAMPLES = HelloPixmap           \
                      HelloToolBar          \
                      HelloGLViewer         \
                      HelloOpenGL           \
                      DrawFunction          \
                      CustomCanvasMenu      \
                      HelloQtSolutions      \
                      QtGBrowser

#                      CustomWidgets        \

unix {
  exists($$LOCALROOTSYS/lib/libQtRootGui.so):       QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($${LOCALROOTSYSDIR}/lib/libQtRootGui.so):  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
}

win32 {
  exists($${LOCALROOTSYS}/bin/libQtRootGui.dll):      QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($${LOCALROOTSYSDIR}/bin) {
      exists($${LOCALROOTSYSDIR}/bin/libQtRootGui.dll)  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
  }
}

!contains( QT_VERSION, "^4.*" ) {
exists($${LOCALROOTSYS}/qtgsi) : QTEXAMPLEPACKAGES += qtgsi/example1
}

exists($${LOCALROOTSYS}/include/rootcint.pri):   QTEXAMPLEPACKAGES += HelloCint

QTEXAMPLEPACKAGES += Qt4/CustomWidgets  Qt4/HelloFileBrowser  Qt4/HelloSignal 

message("This project us to build $$QTEXAMPLEPACKAGES Qt/Root examples")
SUBDIRS = $$QTEXAMPLEPACKAGES
