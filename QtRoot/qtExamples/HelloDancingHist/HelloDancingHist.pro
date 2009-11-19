TEMPLATE = app
TARGET   = HelloDancingHist
QT += qt3support

QMAKE_RPATH=


HelloDancingHistIncludeFile = $$(QTROOTSYSDIR)/include
exists($$HelloDancingHistIncludeFile) {
  include ($$HelloDancingHistIncludeFile/rootcint.pri)
  embeddedPadFile = $$HelloDancingHistIncludeFile/TEmbeddedPad.h

  exists ($$embeddedPadFile) {
     DEFINES += EMBEDDEDTPAD
  }
}

!exists ($$HelloDancingHistIncludeFile) {
  HelloDancingHistIncludeFile = $$(ROOTSYS)/include/rootcint.pri
  exists ($$HelloDancingHistIncludeFile) {
    include ($$HelloDancingHistIncludeFile)
    embeddedPadFile = $(ROOTSYS)/include/TEmbeddedPad.h
    exists ($$embeddedPadFile) {
      DEFINES += EMBEDDEDTPAD
    }
  }
}

HEADERS		= HelloDancingHist.h \
		 
SOURCES		= HelloDancingHist.cxx \
		  main.cxx
