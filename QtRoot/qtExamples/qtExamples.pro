TEMPLATE = subdirs
QT += qt3support

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
                      HelloZoomer

!contains( QT_VERSION, "^4.*" ) {
    QTEXAMPLEPACKAGES += ex1/tqrootexample.pro \
                      HelloLife
}

QTEXTENSIONEXAMPLES = QtGBrowser            \
                      HelloPixmap           \
                      CustomWidgets         \
                      CustomCanvasMenu

unix {
  exists($${LOCALROOTSYS}/lib/libQtRootGui.so):       QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($${LOCALQTROOTSYSDIR}/lib/libQtRootGui.so):  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
}

win32 {
  exists($${LOCALROOTSYS}/bin/libQtRootGui.dll):          QTEXAMPLEPACKAGES += $$QTEXTENSIONEXAMPLES
  exists($${LOCALQTROOTSYSDIR}/bin) {
      exists($${LOCALQTROOTSYSDIR}/bin/libQtRootGui.dll)  QTEXAMPLEPACKAGES *= $$QTEXTENSIONEXAMPLES
  }
}

!contains( QT_VERSION, "^4.*" ) {
exists($${LOCALROOTSYS}/qtgsi) : QTEXAMPLEPACKAGES += qtgsi/example1
}

exists($${LOCALROOTSYS}/include/rootcint.pri):   QTEXAMPLEPACKAGES += HelloCint

message("This project us to build $$QTEXAMPLEPACKAGES Qt/Root examples")
SUBDIRS = $$QTEXAMPLEPACKAGES
