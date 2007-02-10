######################################################################
# Automatically generated by qmake (1.07a) Thu Jun 16 17:45:08 2005
######################################################################

TEMPLATE = lib
QGLVIEWERDIR = ../qcoinviewer/QCoinViewer
CONFIG *= thread dll opengl
CONFIG *= create_prl
COIN3DDIR= $(IVROOT)

TARGET = RQIVTGL

!exists ($(ROOTSYS)/include/TObjectSet.h){
     message("qtgl" package requeries the ROOT libTable shared library to be built first)
     message(Your current ROOT configuration is:)
unix:     system(more $ROOTSYS/config.status)
win32:    system(type %ROOTSYS%/config.status)
   message(Either re-install ROOT to add the "--enable-table" flag to the ROOT configure - RECOMMENDED)
     error(       or remove the qtgl package from the list of the Qt/Root packages  - NOT RECOMMENDED)
}
QTROOTSYSPATHINSTALL = $(QTROOTSYSDIR)

isEmpty(DESTDIR) {
  DESTDIR=..
}
isEmpty(QTROOTSYSPATHINSTALL) {
  QTROOTSYSPATHINSTALL = $$DESTDIR
}

QTCOINDIRS  = src
QTCOINDIRI  = inc

QTGLGLDIRI = ../qtgl/inc
COININCDIRI = $$COIN3DDIR/include

DEPENDPATH  += $$QTCOINDIRI $$QTGLGLDIRI
INCLUDEPATH += $$QTCOINDIRI $$QTGLGLDIRI $$COININCDIRI $$SOQTINCDIRI

GQTDIRI   = ../../qt/inc

QTCOINH1    = $$QTCOINDIRI/TQtCoinViewerImp.h      $$QTCOINDIRI/TQtCoinWidget.h   $$QTCOINDIRI/TQtRootCoinViewer3D.h  \
              $$QTCOINDIRI/TQtCoin3DDefInterface.h $$QTCOINDIRI/TGeoTranslationC.h
#$$QTCOINDIRI/TQtGLViewerWidget.h          $$QTCOINDIRI/TObject3DView.h      $$QTCOINDIRI/TQtGLViewerImp.h


CREATE_ROOT_DICT_FOR_CLASSES  = $$QTCOINH1 $$QTCOINDIRI/LinkDef.h

unix {
  LIBS += -L../.. -L$$COIN3DDIR/lib -lSoQt -lCoin -lSmallChange
}

ROOTCINTFOUND =
    exists ($$GQTDIRI/rootcintrule.pri){
#message(first)
         ROOTCINTFOUND =$$GQTDIRI/rootcintrule.pri
         INCLUDEPATH  *= $$GQTDIRI
         DEPENDPATH   *= $$GQTDIRI
    }
    isEmpty(ROOTCINTFOUND) {
       exists ($(ROOTSYS)/include/rootcintrule.pri){
           ROOTCINTFOUND ="$(ROOTSYS)/include/rootcintrule.pri"
       }
    }

    isEmpty(ROOTCINTFOUND) {
        message ("$$TARGET: The rootcintrule.pri was not found")
    }

include (../../qt/inc/rootcintrule.pri)

ROOTCINTFOUND =

    exists ($$GQTDIRI/rootlibs.pri){
         ROOTCINTFOUND =$$GQTDIRI/rootlibs.pri
    }
    isEmpty(ROOTCINTFOUND) {
       exists ($(ROOTSYS)/include/rootlibs.pri){
           ROOTCINTFOUND =$(ROOTSYS)/include/rootlibs.pri
       }
    }

    isEmpty(ROOTCINTFOUND) {
        message ("$$TARGET: The rootlibs.pri was not found")
    }

include (../../qt/inc/rootlibs.pri)

#win32 {
#   LIBS += "$(ROOTSYS)/lib/libGQt.lib"   "$(ROOTSYS)/lib/libGraf3d.lib"
#}
unix {
   LIBS += -L../../qt  -L.. -lGeom -lRQTGL 
}
mac {
   LIBS *=  -L../../qt -lGeom
}

#  LIBS += -L$$QGLVIEWERDIR  -lQGLViewer

# LIB_NAME
LIB_NAME = libRQIVTGL.so
macx|darwin-g++ {
   LIB_NAME = libQCoinViewer.$${QMAKE_EXTENSION_SHLIB}
  }
hpux {
  LIB_NAME = libQCoinViewer.sl
}

#LIBS +=  $$QGLVIEWERDIR/$$LIB_NAME
#LIBS +=  $$LIB_NAME

headerfiles.path  = $$QTROOTSYSPATHINSTALL/include
headerfiles.files = $$QTCOINDIRI/*.*

target.path = $$QTROOTSYSPATHINSTALL/lib

INSTALLS += headerfiles target

# Input
HEADERS += inc/TQtCoinViewerImp.h            \
           inc/TQtCoinWidget.h               \
           inc/TQtRootCoinViewer3D.h         \
           inc/TObjectCoinViewFactory.h      \
           inc/TCoinShapeBuilder.h           \
           inc/TSimageMovie.h                \
           inc/TQt3DClipEditor.h             \
           inc/x.xpm.h                       \
           inc/y.xpm.h                       \
           inc/z.xpm.h                       \
           inc/TQtCoin3DDefInterface.h
           
SOURCES += src/TQtCoinWidget.cxx             \
           src/TQtCoinViewerImp.cxx          \
           src/TQtRootCoinViewer3D.cxx       \
           src/TObjectCoinViewFactory.cxx    \
           src/TCoinShapeBuilder.cxx         \
           src/TSimageMovie.cxx              \
           src/TQt3DClipEditor.cxx           \
           src/TQtCoin3DDefInterface.cxx

DISTFILES += LICENSE.QPL

unix {
#  -- working directory

  QMAKE_CLEAN  += ${DESTDIR}lib${QMAKE_TARGET}.prl

  ROOTCINT_DIR = .rootcint
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj

}
#The following line was inserted by qt3to4
QT +=  qt3support 
#The following line was inserted by qt3to4
QT += xml  opengl 
