TEMPLATE = app
TARGET   = HelloLife
QT += qt3support

CONFIG   += qt warn_on release thread


helloLifeIncludeFile = $(QTROOTSYSDIR)/include
exists($$helloLifeIncludeFile) {
  include ($$helloLifeIncludeFile/rootcint.pri)
  embeddedPadFile = $$helloLifeIncludeFile/TEmbeddedPad.h

  exists ($$embeddedPadFile) {
  message (from QTroot $$embeddedPadFile )
     DEFINES += EMBEDDEDTPAD
  }
}

!exists ($$helloLifeIncludeFile) {
  helloLifeIncludeFile = $(ROOTSYS)/include/rootcint.pri
  exists ($$helloLifeIncludeFile) {
    include ($$helloLifeIncludeFile)
    embeddedPadFile = $(ROOTSYS)/include/TEmbeddedPad.h
    exists ($$embeddedPadFile) {
      DEFINES += EMBEDDEDTPAD
    }
  }
}

HEADERS		= HelloLife.h \
		  HelloLifeDlg.h
SOURCES		= HelloLife.cxx \
		  HelloLifeDlg.cxx \
		  main.cxx
