######################################################################
# Automatically generated by qmake (2.01a) Mon Jul 27 19:23:43 2009
######################################################################

TEMPLATE = app
TARGET = GeomBrowser
QMAKE_RPATH=

DEPENDPATH += .
INCLUDEPATH += .

FORMS = StGeomDepthControl.ui
RESOURCES = GeomBrowser.qrc

# Input
HEADERS += GeomBrowser.h         \
           QExGeoDrawHelper.h    \
           StarGeomTreeWidget.h  \
           TQtRangeControl.h     
           

SOURCES += GeomBrowser.cxx        \
           QExGeoDrawHelper.cxx   \
           StarGeomTreeWidget.cxx \
           TQtRangeControl.cxx    \
           main.cpp

unix:LIBS      += -lGeom

mac:LIBS	+= $$system(root-config --glibs) -lGeom -lTable -lGQt -lQtRootGui

DEFINES	+= NO_GEANT_MAKER
unix:DEFINES	+= QT_EXTENSION 


#IMAGES	= arrow_right.xpm \
#	      arrow_left.xpm  \
#	      wirebox.xpm

# mac:


# release
unix {
  ROOT_SHAREDLIB_EXT=so
  ROOT_SHAREDLIB_DIR=lib
  QMAKE_EXTENSION_SHLIB = so
}

mac {
  ROOT_SHAREDLIB_EXT=so
  ROOT_SHAREDLIB_DIR=lib
  QMAKE_EXTENSION_SHLIB = dylib
}

win32 {
  ROOT_SHAREDLIB_EXT=dll
  ROOT_SHAREDLIB_DIR=bin
  QMAKE_EXTENSION_SHLIB = dll
}
message("ATTENTION !!!!  QtGBrowser example needs Qt ROOT extension to be installed from http://root.bnl.gov ")

includeFile = $(QTROOTSYSDIR)/include
exists( $$includeFile ) {
   INCLUDEPATH *= "$$includeFile"
   include ($$includeFile/rootcint.pri)
    message(" ---  ATTENTION !!!!  QtGBrowser example needs Qt ROOT extension to be installed from http://root.bnl.gov ")
}
libFile = $(ROOTSYS)/$${ROOT_SHAREDLIB_DIR}/libQtRootGui.$$QMAKE_EXTENSION_SHLIB
exists($$libFile)
{
   message (Found: $$libFile )
  !exists( $$includeFile/rootcint.pri ) {
     include ($(ROOTSYS)/include/rootcint.pri)
  }
}   

UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

unix {

#
#  generate the link to the proper version of the ROOT resource file
#
  rootrc.target   = .rootrc
  rootrc.commands = @rm -rf .rootrc; ln -s rootrcqtgui $$rootrc.target

  QMAKE_EXTRA_UNIX_TARGETS += rootrc
  PRE_TARGETDEPS  += $$rootrc.target
  QMAKE_CLEAN     += $$rootrc.target
}

:QT += qt3support