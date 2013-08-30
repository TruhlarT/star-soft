######################################################################
# Automatically generated by qmake (1.07a) Sun Jun 26 02:03:47 2005
# Adjusted by hand to include $ROOTSYS/include/rootcint.pri file
######################################################################

TEMPLATE = app thread
QMAKE_LFLAGS_RPATH=
CONFIG -= moc
#
# Include "by hand" the qmake include file "rootcint.pri"
# from the ROOT distribution to define:
#
#  1. include path to the ROOT system header files
#  2. the list of the ROTO shared libraries to link
#     Qt application against of
#  3. qmake rules to generate ROOT/Cint dictionaries

incFile = $$(QTROOTSYSDIR)/include
exists ($$incFile) {
  include ($$incFile/rootcint.pri)
}

!exists ($$incFile) {
  incFile = $$(ROOTSYS)/include/rootcint.pri
  exists ($$incFile) {
    include ($$incFile)
  }
}


# Input
SOURCES += RotatePad.cxx

#  -- Check for the obsolete ROOT version :(
!exists ($$incFile) {
    message (" ")
    message ("WARNING:  The $$inlcudeFile was not found !!!")
    message ("Please update your Qt layer version from http://root.bnl.gov ")
    message (" ")
    LIBS += $$system(root-config --glibs) -lGQt
    INCLUDEPATH += $(ROOTSYS)/include
}
#The following line was inserted by qt3to4
QT +=  qt3support 
