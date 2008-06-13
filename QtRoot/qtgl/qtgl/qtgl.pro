######################################################################
# Automatically generated by qmake (1.07a) Thu Jun 16 17:45:08 2005
######################################################################

TEMPLATE = lib
QGLVIEWERDIR = ../qglviewer/QGLViewer
CONFIG *= thread dll opengl
CONFIG *= create_prl

TARGET = RQTGL

isEmpty(DESTDIR) {
  DESTDIR=..
}
isEmpty(QTROOTSYSPATHINSTALL) {
  QTROOTSYSPATHINSTALL = $$DESTDIR
}

QTGLDIRS  = src
QTGLDIRI  = inc

DEPENDPATH  += $$QTGLDIRI $$QTGLDIRS $$QGLVIEWERDIR
INCLUDEPATH += $$QTGLDIRI $$QGLVIEWERDIR  

GQTDIRI   = ../../qt/inc

QTGLH1    = $$QTGLDIRI/TObject3DViewFactoryABC.h    $$QTGLDIRI/TQGLViewerImp.h      $$QTGLDIRI/TQtRootViewer3D.h  \
            $$QTGLDIRI/TQtGLViewerWidget.h          $$QTGLDIRI/TObject3DView.h      $$QTGLDIRI/TQtGLViewerImp.h

CREATE_ROOT_DICT_FOR_CLASSES  = $$QTGLH1 $$QTGLDIRI/LinkDef.h

unix {
  LIBS += -L../..
}

!exists ($(ROOTSYS)/include/TObjectSet.h){
     message("qtgl" package requeries the ROOT libTable shared library to be built first)
     message(Your current ROOT configuration is:)
unix:     system(more $ROOTSYS/config.status)
win32:    system(type %ROOTSYS%/config.status)
   message(Either re-install ROOT to add the "--enable-table" flag to the ROOT configure - RECOMMENDED)
     error(       or remove the qtgl package from the list of the Qt/Root packages  - NOT RECOMMENDED)
}

QTROOTSYSPATHINSTALL = $(QTROOTSYSDIR)
QT_VERSION=$$[QT_VERSION]
contains( QT_VERSION, "^4.*" ) {
    QTROOTSYSPATHINSTALL = $$(QTROOTSYSDIR)
}

ROOTCINTFOUND =
    exists ($$GQTDIRI/rootcintrule.pri){
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
   LIBS += -L../../qt  -lGeom
}
mac {
   LIBS *=  -L../../qt -lGeom
}

#  LIBS += -L$$QGLVIEWERDIR  -lQGLViewer
# LIB_NAME
LIB_NAME = libQGLViewer.so
macx|darwin-g++ {
   LIB_NAME = libQGLViewer.$${QMAKE_EXTENSION_SHLIB}
  }
hpux {
  LIB_NAME = libQGLViewer.sl
}

LIBS +=  $$QGLVIEWERDIR/$$LIB_NAME
    
headerfiles.path  = $$QTROOTSYSPATHINSTALL/include
headerfiles.files = $$QTGLDIRI/*.*

plugins.path   = $$QTROOTSYSPATHINSTALL/etc/plugins/TVirtualViewer3D/
plugins.files  = plugins/TVirtualViewer3D/*.C

target.path    = $$QTROOTSYSPATHINSTALL/lib

INSTALLS += headerfiles target plugins

# Input
HEADERS += inc/TBoundBoxEstimator.h       \
           inc/TObject3DView.h            \
           inc/TObject3DViewFactory.h     \
           inc/TObject3DViewFactoryABC.h  \
           inc/TObjectOpenGLViewFactory.h \
           inc/TQGLViewerImp.h            \
           inc/TQtGLViewerImp.h           \
           inc/TQtGLViewerWidget.h        \
           inc/TQtRootViewer3D.h          \
           inc/TQVirtualGL.h              \
           inc/TShape3DPolygonView.h
#           inc/TQGLKernel.h              \
           
SOURCES += src/TObject3DView.cxx             \
           src/TObject3DViewFactory.cxx      \
           src/TObject3DViewFactoryABC.cxx   \
           src/TObjectOpenGLViewFactory.cxx  \
           src/TQtGLViewerImp.cxx            \
           src/TQtGLViewerWidget.cxx         \
           src/TQtRootViewer3D.cxx           \
           src/TQVirtualGL.cxx               \
           src/TPadOpenGLView.cxx            \
           src/TGLViewerImp.cxx             
#           src/TGLKernel.cxx                 \

           
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
