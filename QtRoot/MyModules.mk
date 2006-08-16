# User level Makefile for ROOT System
#
# Author: Valeri Fine 22/8/2003

##### Allow local dependency #####
 
-include MyMakefile.depend


ifeq ($(TABLE),)
# turn on the table package if needed
# this is a workaround to be removed later (V.Fine 30.10.2003)
# TABLE          := 1
# MODULES      += table
endif

ifneq ($(QTINCDIR),)
# Core of the Qt ROOT layer
#MODULES      += qt qtroot 
EXTRA_CXXFLAGS  += -DR__QT
EXTRA_CFLAGS    += -DR__QT
# Extensions of the Qt ROOT layer
MODULES         += qtgui qtimage qtged
ifneq ($(ARCH),win32old) 
ifneq ($(ARCH),win32gdk)
# MODULES        += qtx3d
endif
endif
ifneq ($(BUILDGL),)
MODULES      += qtgl
else
ifeq ($(ARCH),win32old)
MODULES      += qtgl
else
ifneq ($(OPENGLINCDIR),)
ifneq ($(OPENGLLIB),)
MODULES      += qtgl
endif
endif
endif
endif
endif
