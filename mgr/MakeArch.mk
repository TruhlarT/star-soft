#  $Log: MakeArch.mk,v $
#  Revision 1.11  1998/07/10 12:23:15  nevski
#  Add backup for PAMs shared libraries
#
#  Revision 1.10  1998/05/19 16:36:38  perev
#  Makefiles
#
#  Revision 1.4  1998/02/13 14:18:20  fisyak
#  Simplify Makefile, reduce SLibrary
#
#  Revision 1.3  1998/02/12 13:35:09  fisyak
#  Add versioning, new Makefile with domain/package libraries
#
#  Revision 1.2  1998/02/10 00:06:10  fisyak
#  SL98a second version
#
#  Revision 1.1  1998/01/31 23:32:52  fisyak
#  New Environment variables
#
#  Revision 1.2  1998/01/30 12:42:16  fisyak
#  Save changes before moving to SL97b
#
#  Revision 1.1.1.1  1997/12/31 14:35:23  fisyak
#  Revision ?.?.?.?  1998/02/07           perev
#
#             Last modification $Date: 1998/07/10 12:23:15 $ 
#. default setings

RM := rm -f
MV := mv -f
RMDIR := rm -rf
CP := cp
LN := ln -s
SLASH :=/
MKDIR := mkdir -p

COUT := -o 
LOUT := -o 

  O     :=o
  A     :=a
  Cxx   :=cxx
  So    :=so

CERN_LEVEL :=pro
MOTIF :=YES
GCC      :=  gcc
CC       :=  $(GCC)
CFLAGS   := $(DEBUG) -fpic -w
CXX      :=  g++
CXXFLAGS := $(DEBUG) -fpic -w
FC 	 := f77
AR       := ar
ARFLAGS  := rvu
LD 	 := $(CXX)
SO	 := $(CC)
SOFLAGS	 := 
LDFLAGS	 := 
EXEFLAGS := NONE
So       :=so
O        :=o
A        :=a
Cxx   :=cc
CLIBS    :=
FLIBS    :=

CPPFLAGS := $(UNAMES) $(STAF_ARCH) $(TULL_ARCH)
OSFID    :=
STRID    :=
YACC     := yacc
YACCLIB  := -ly
LEX      := lex
LEXLIB   := -ll

DEBUG := -g
ifdef NODEBUG
  DEBUG := -O
endif
ifdef nodebug
  DEBUG := -O
endif

ifneq (,$(findstring $(STAF_ARCH),intel_wnt))
#  case WIN32
#  ====================


  COUT := -Fo 
  LOUT := -out: 

  O     :=obj
  A     :=lib
  Cxx   :=cxx
  So    :=dll
  
  RM := del /Q
  CP := copy
  LN := xcopy
  SLASH := \\
  MKDIR :=mkdir
  OSFID   := VISUAL_CPLUSPLUS CERNLIB_WINNT CERNLIB_MSSTDCALL
  STRID   := wnt
  CXX     := cl
  CC      := cl
  LD      := $(CXX)
  SO      := link
  SOFLAGS := /DEBUG /NODEFAULTLIB /INCREMENTAL:NO /NOLOGO /DLL /PDB:$(PDB)_all
  CXXFLAGS:= $(cvarsdll) /MD /G5 /Zi /Fd$(PDB) /O2
  CFLAGS  := $(CXXFLAGS)
  LDFLAGS := $(conlflags)
  CLIBS   := $(guilibsdll)

  FC         = fl32
  FLIBS   := dfordll.lib
  FFLAGS  := /MD /G5 /Zi /Fd$(PDB) /fpp /Oxp
  FEXTEND := /extend_source
endif 

ifneq (,$(findstring $(STAF_ARCH),rs_aix31 rs_aix32 rs_aix41))
#  case IBMRT
#  ====================

  OSFID :=aix AIX CERNLIB_IBMRT CERNLIB_UNIX CERNLIB_QMIBM
  STRID :=aix
  ifdef GCC.
    CXXFLAGS := $(DEBUG)  -fsigned-char -w  
    CFLAGS  := $(DEBUG)  -fsigned-char -w 
    LDFLAGS  := 
    SOFLAGS  :=  -shared 
    CLIBS  :=  -lXm -lXt -lX11 -lg++ -lm -lld
  else
    CXX    := xlC
    CC     := xlC
    LD     := $(CXX)
    SO     := ???
    SOFLAGS := ???
    CXXFLAGS := $(DEBUG) -w -qchars=signed -qnoro -qnoroconst 
    CFLAGS  := $(DEBUG) -w -qchars=signed -qnoro -qnoroconst 
    LDFLAGS  := 
    CLIBS  :=  -lXm -lXt -lX11  -lld  -lm -lc -lcurses
  endif

  FC         = xlf
  FLIBS   := -lxlf90 -lxlf
  FFLAGS  := $(DEBUG) -qextname  -qrndsngl -qcharlen=6000 
  FEXTEND := -e
endif 

ifneq (,$(findstring $(STAF_ARCH),i386_linux2 i386_redhat50))
#    case linux
#  ====================
  MOTIF :=
  CERN_LEVEL :=pgf98
  OSFID    := lnx Linux linux LINUX CERNLIB_LINUX CERNLIB_UNIX CERNLIB_LNX CERNLIB_QMLNX
  STRID    := lnx
  FC       := pgf77
  LD       := $(CXX)
  SO	   := $(CXX)
  CXXFLAGS := $(DEBUG) -fPIC
  CFLAGS   := $(DEBUG) -fPIC
  CPPFLAGS += f2cFortran
  LDFLAGS  := -Wl,-Bstatic
  EXEFLAGS := -Wl,-Bdynamic  
  SOFLAGS  := -shared  
##CLIBS    := -L/usr/X11R6/lib -Wl,-Bdynamic -lXpm -lXt -lXext -lX11 -lg++ -lpgc -lm -ldl -rdynamic
  CLIBS    := -L/usr/pgi/linux86/lib -L/usr/X11R6/lib -L/usr/lib -lXt -lXpm -lX11 -lcrypt -lg++ -lpgc -lm -ldl  -rdynamic
  FLIBS    := -L/usr/pgi/linux86/lib -lpgftnrtl 
  FFLAGS   := -DPGI  $(DEBUG)
  FEXTEND  := -Mextend
  YACC     := bison -y
  YACCLIB  := 
  LEX      := flex
  LEXLIB   := -lfl
endif

ifneq (,$(findstring $(STAF_ARCH),alpha_osf1 alpha_osf32c alpha_dux40))
#    case "alpha":
#  ====================
  OSFID := osf ALPHA alpha CERNLIB_QMVAOS CERNLIB_DECS CERNLIB_UNIX
  STRID := osf
  ifdef GCC.
    CXXFLAGS := -w  -D__osf__ -D__alpha 
    CFLAGS  := -w  -D__osf__ -D__alpha 
    LDFLAGS  :=
    SOFLAGS  := -shared 
    CLIBS  := -lXm -lXt -lX11 -lg++ -lm -lPW -lm -lm_4sqrt -lots -lc
 
 else
    CXX    :=cxx
    CC     :=cc
    LD     :=$(CXX)
    SO     :=$(CXX)
    CXXFLAGS := -w -D__osf__ -D__alpha -Dcxxbug -DALPHACXX 
    CFLAGS  := $(DEBUG) -w  
    LDFLAGS  := 
    SOFLAGS  :=  -call_shared -expect_unresolved '*'
    CLIBS  :=  -lXm -lXt -lX11 -lm -lPW -lm -lm_4sqrt -lots -lc
 
  endif

  FLIBS    :=  -lUfor -lfor -lFutil 
  FFLAGS   :=  -pic  -static -fpe2 
  FEXTEND  :=  -extend_source 
endif

ifneq (,$(findstring $(STAF_ARCH),hp_ux102 hp700_ux90))

#    case "hp":
#  ====================
  HPUX := Yess
  OSFID := HPUX CERNLIB_HPUX CERNLIB_UNIX
  STRID := hpu
  ifdef GCC
    CXXFLAGS  := $(DEBUG) -fPIC  -I/usr/include/X11R5 -Dextname -D_HPUX_SOURCE 
    CFLAGS    := $(DEBUG) -fPIC  -I/usr/include/X11R5 -Dextname -D_HPUX_SOURCE
    LDFLAGS   := -b $(DEBUG) 
    SOFLAGS   := -shared $(DEBUG) 
    CLIBS   := -L/usr/lib/Motif1.2 -L/usr/lib/X11R5 -L/usr/lib -lXm -lXt -lX11 -lg++ -lm -lPW -ldld -L/opt/CC/lib -lC.ansi -lcxx -lcl -lc
    FLIBS   :=  /opt/fortran/lib/libU77.a 

  endif

  ifndef noACC.
    CXX     := aCC
    CC      := cc
    LD      := $(CXX)
    SO      := $(CXX)
    CXXFLAGS  := $(DEBUG) -z +Z  -Dextname  
    CFLAGS   := $(DEBUG) -Ae -z +Z -Dextname  
    LDFLAGS   := $(DEBUG)  -z -Wl,+s -Wl,-E 
    SOFLAGS   := $(DEBUG)  -b -z  
    CLIBS   :=   -lXm -lXt -lX11 -lm -lPW -ldld

  else
    CXX     :=  CC
    CC      := cc
    LD      := $(CXX)
    SO      := $(CXX)
    CXXFLAGS  := $(DEBUG) +a1 -z +Z -w -Dextname  -D_HPUX_SOURCE
    CFLAGS   :=  $(DEBUG) -Ae -z +Z -Dextname   -D_HPUX_SOURCE
    LDFLAGS   := $(DEBUG) +a1 -z -Wl,+s -Wl,-E 
    SOFLAGS   := $(DEBUG) -b +a1 -z 
    CLIBS   :=   -L/usr/lib/X11R5 -lXm -lXt -lX11 -lm -lPW -ldld
  endif
  So := sl
  FC        :=fort77
##FLIBS     := /opt/fortran/lib/libU77.a /opt/langtools/lib/end.o
  FLIBS     := /opt/fortran/lib/libU77.a 
  FFLAGS    := $(DEBUG) +DA1.0 +ppu +Z  +U77
  FEXTEND   := +es
endif



ifneq (,$(findstring $(STAF_ARCH),sgi_52 sgi_53))
#  ====================
  OSF SGI irix IRIX CERNLIB_SGI CERNLIB_UNIX
  STRID := sgi
  FFLAGS    :=  -Nn20000 -static -trapuv  
  FEXTEND   :=  -extend_source
  CC        :=    cc
  CFLAGS    :=   -signed -fullwarn
  CXX       :=   CC
  CXXFLAGS  :=   -signed  -fullwarn
  ARFLAGS   :=   slrvu
  LD        :=   $(CXX)
  LDFLAGS   :=
  SO        :=   $(CXX)
  SOFLAGS   :=  -shared
  CLIBS     := -lsun -lmalloc  -lm -lc -lPW -lXext
  FLIBS     :=   -lftn 

endif

ifneq (,$(findstring $(STAF_ARCH),sgi_64 ))

  OSFID :=  irix64 sgi64 SGI64 IRIX64 CERNLIB_QMIRIX64 CERNLIB_SGI CERNLIB_UNIX
  STRID := sgi
  FFLAGS    :=  -n32  -static -trapuv 
  FEXTEND   :=  -extend_source
  CC        :=    cc
  CFLAGS    :=  -n32  -fullwarn	
  CXX       :=    CC
  CXXFLAGS  :=  -n32 -fullwarn
  LD        :=   $(CXX)
  LDFLAGS   :=  -n32 -multigot
  SO        :=   $(CXX)
  SOFLAGS   :=  -n32 -shared -multigot
  CLIBS     :=  -lsun  -lm -lc -lPW -lXext -lmalloc
  FLIBS     :=  -lftn 

endif


ifneq (,$(findstring $(STAF_ARCH),sun4x_55 sun4x_56))

  CPPFLAGS := $(filter-out SunOS,$(CPPFLAGS))
  OSFID :=  sun SUN SOLARIS Solaris CERNLIB_UNIX CERNLIB_SUN
  STRID :=  sun
  CC :=  /opt/SUNWspro/bin/cc
  CXX := /opt/SUNWspro/bin/CC
  LD  := $(CXX)
  SO  := $(CXX)
  FC  := /opt/SUNWspro/bin/f77

  FFLAGS   :=  $(DEBUG)  -KPIC -w 
  FEXTEND  :=  -e
  CFLAGS   :=  $(DEBUG)  -KPIC 
  CXXFLAGS :=  $(DEBUG)  -KPIC 
  LDFLAGS  :=  $(DEBUG)  -Bstatic
  EXEFLAGS :=  $(DEBUG)  -Bdynamic -t
  SOFLAGS  :=  $(DEBUG) -G
  CLIBS    := -L/opt/SUNWspro/lib -L/opt/SUNWspro/SC4.2/lib  -lm -lc -L/usr/ucblib -R/usr/ucblib -lucb -lmapmalloc
  FLIBS    := -lM77 -lF77 -lsunmath
endif


ifneq (,$(findstring $(STAF_ARCH),sunx86_55))
  CPPFLAGS := $(filter-out SunOS,$(CPPFLAGS))
  OSFID :=  sun SUN SOLARIS SOLARISPC CERNLIB_UNIX CERNLIB_SUN CERNLIB_FQNEEDCV 
  STRID :=  sun
  CC       :=  /opt/SUNWspro/bin/cc
  CXX      := /opt/SUNWspro/bin/CC
  SO       := $(CXX)
  FC       := /opt/SUNWspro/bin/f77
  LD       := $(CXX)
  FFLAGS   :=  $(DEBUG) -KPIC  
  FEXTEND  := -e
  CFLAGS   :=  $(DEBUG) -KPIC +w2 -I/usr/dt/share/include -I/usr/openwin/share/include
  CXXFLAGS :=  $(CFLAGS)
  LDFLAGS  :=  $(DEBUG)  -z muldefs -Bstatic
  EXEFLAGS :=  $(DEBUG)  -z muldefs -Bdynamic -t
  SOFLAGS  :=  $(DEBUG)  -G
  CLIBS    := -L/opt/SUNWspro/lib -L/opt/SUNWspro/SC4.2/lib  -lm -lc -L/usr/ucblib -R/usr/ucblib -lucb -lmapmalloc
  FLIBS    := -lM77 -lF77 -lsunmath

endif

CPPFLAGS := $(filter-out HP-UX,$(CPPFLAGS) $(OSFID))
CPPFLAGS := $(sort $(addprefix -D,$(CPPFLAGS)))

FOR72 := $(FC)
FC  := $(FC) $(FEXTEND)

ifeq ($(EXEFLAGS),NONE)
  EXEFLAGS := $(LDFLAGS)
endif

