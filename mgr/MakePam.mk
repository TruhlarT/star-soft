#  $Log: MakePam.mk,v $
#  Revision 1.19  1998/06/05 11:45:53  fisyak
#  clean up
#
#  Revision 1.18  1998/05/06 17:27:39  didenko
#  makefile updated by Yuri
#
#  Revision 1.17  1998/05/03 18:27:41  fisyak
#  Set fixed path to geant3
#
#  Revision 1.16  1998/04/28 16:36:48  fisyak
#  remove or merger from stic -M
#
#  Revision 1.15  1998/04/26 02:49:35  fisyak
#  Fix fortran dependencies
#
#  Revision 1.14  1998/04/20 23:41:09  fisyak
#  Remove -traditional from gcc
#
#  Revision 1.13  1998/04/20 22:39:10  fisyak
#  Correct dependencies
#
#  Revision 1.12  1998/04/20 15:06:47  fisyak
#  user CERNLIN include
#
#  Revision 1.11  1998/04/13 16:03:48  fisyak
#  Correct HPUX flags
#
#  Revision 1.10  1998/04/10 14:03:14  fisyak
#  Add supermodule in shared libraries
#
#  Revision 1.9  1998/04/07 22:02:49  fisyak
#  fogotten bracket
#
#  Revision 1.7  1998/04/07 20:57:14  fisyak
#  Add standard library to path
#
#  Revision 1.6  1998/04/04 14:45:50  fisyak
#  Fix bug with geant3.def
#
#  Revision 1.5  1998/03/27 14:32:54  fisyak
#  Simplify MakePam
#
#  Revision 1.3  1998/03/23 02:31:42  fisyak
#  move staff in group_dir
#
#  Revision 1.2  1998/03/09 14:36:30  fisyak
#  Switch varibales
#
#  Revision 1.1  1998/03/09 13:31:50  fisyak
#  Remove environment Variables
#
#  Revision 1.13  1998/02/22 02:08:25  fisyak
#  CPPFLAGS for HPX
#
#  Revision 1.12  1998/02/21 18:33:54  fisyak
#  Add util domain
#
#  Revision 1.11  1998/02/21 00:58:31  fisyak
#  Add tls library
#
#  Revision 1.10  1998/02/18 22:58:03  fisyak
#  Move staf
#
#  Revision 1.9  1998/02/17 18:06:46  fisyak
#  Add dropit for PATH
#
#  Revision 1.8  1998/02/14 02:08:20  fisyak
#  Add silent mode for make
#
#  Revision 1.7  1998/02/13 14:18:19  fisyak
#  Simplify Makefile, reduce SLibrary
#
#  Revision 1.5  1998/02/10 00:06:07  fisyak
#  SL98a second version
#
#  Revision 1.4  1998/01/31 23:32:51  fisyak
#  New Environment variables
#
#  Revision 1.3  1998/01/30 12:42:14  fisyak
#  Save changes before moving to SL97b
#
#  Revision 1.2  1998/01/01 03:28:11  fisyak
#  New make.kumac
#
#  Revision 1.1.1.1  1997/12/31 14:35:23  fisyak
#
#           Last modification $Date: 1998/06/05 11:45:53 $ 
#  #. default setings
include $(STAR)/mgr/MakeSYS.mk
ifdef SILENT
.SILENT:
endif       
ifndef MAKEFILE
MAKEFILE = $(STAR)/mgr/MakePam.mk
endif          
ifndef INP_DIR 
INP_DIR := $(CWD)
endif           
NAME    := $(notdir $(INP_DIR))
# define level pams -> domain -> package from *.idl and *.g files
#======================= level ===========================
PAMS    :=pams
pams    :=$(findstring $(PAMS),$(INP_DIR))
LEVEL   := $(words  $(subst /, ,$(subst $(word 1, $(subst /pams, ,$(INP_DIR))),, $(INP_DIR))))
ifeq ($(LEVEL),$(ZERO))
	ROOT    :=$(INP_DIR)
	SUBDIRS :=$(shell test -d pams && echo pams)
else
	DIRS    := $(strip $(wildcard *))
	SUBDIRS := $(foreach dir, $(DIRS), $(shell test -d $(dir) && echo $(dir))) 
	SUBDIRS := $(filter-out inc, $(SUBDIRS))
	SUBDIRS := $(filter-out idl, $(SUBDIRS))
	SUBDIRS := $(filter-out doc, $(SUBDIRS))
	SUBDIRS := $(filter-out CVS, $(SUBDIRS))
	SUBDIRS := $(filter-out wrk, $(SUBDIRS))
	SUBDIRS := $(filter-out src, $(SUBDIRS))
	SUBDIRS := $(filter-out exa, $(SUBDIRS))
	SUBDIRS := $(strip    $(sort $(SUBDIRS)))
#       SUBDIRS := $(filter util, $(SUBDIRS)) $(filter-out util, $(SUBDIRS))
        SUBDIRS := $(filter-out util, $(SUBDIRS))
endif
ifeq ($(LEVEL), $(ONE))  #pams level
	ROOT    := $(shell cd $(INP_DIR)/../; $(PWD))
endif
ifeq ($(LEVEL), $(TWO))  #default is domain
	ROOT    := $(shell cd $(INP_DIR)/../../; $(PWD))
	DOM_DIR := $(CWD)
	PKG     := $(notdir $(DOM_DIR))
ifeq (gen,$(PKG))              
	PKG     :=
endif                          
#ifeq (sim,$(PKG))              
#	PKG     :=
#endif                          
endif
ifeq ($(LEVEL), $(THREE)) #package level
	ROOT    := $(shell cd $(INP_DIR)/../../../; $(PWD))
	DOM_DIR := $(shell cd $(INP_DIR)/../; $(PWD))
	PKG     := $(NAME)
	SUBDIRS:=
endif                       
ifeq ($(LEVEL),$(FOUR)) #subpackage level
	ROOT    := $(shell cd $(INP_DIR)/../../../../; $(PWD))
	DOM_DIR := $(shell cd $(INP_DIR)/../../; $(PWD))
	PKG     := $(NAME)
#	PKG     := $(notdir $(shell cd $(INP_DIR)/../; $(PWD)))
endif                          
ifndef OUT_DIR                 
	override OUT_DIR := $(shell cd $(ROOT); $(PWD))
endif                          
ifeq ($(NAME),$(PKG))          
	SUBDIRS :=
endif                          
ifneq ($(LEVEL)$(SUBDIRS),$(ZERO)) 
ifneq ($(EMPTY),$(SUBDIRS))     
#          I have subdrs
.PHONY               : all test clean clean_lib clean_share clean_obj
#      I_have_subdirs
all:  $(addsuffix _all, $(SUBDIRS))
%_all:
	$(MAKE) -f $(MAKEFILE) -C $(STEM) all 
test: $(addsuffix _test, $(SUBDIRS))
%_test: 
	$(MAKE) -f $(MAKEFILE) -C $(STEM) test 
clean: $(addsuffix _clean, $(SUBDIRS))
%_clean: 
	$(MAKE) -f $(MAKEFILE) -C $(STEM) clean 
clean_lib: $(addsuffix _clean_lib, $(SUBDIRS))
%_clean_lib: 
	$(MAKE) -f $(MAKEFILE) -C $(STEM) clean_lib 
clean_share: $(addsuffix _clean_share, $(SUBDIRS))
%_clean_share: 
	$(MAKE) -f $(MAKEFILE) -C $(STEM) clean_share 
clean_obj: $(addsuffix _clean_obj, $(SUBDIRS))
%_clean_obj: 
	$(MAKE) -f $(MAKEFILE) -C $(STEM) clean 
else # I have no subdirs
SRC_DIR := $(INP_DIR)
IDLS    := $(wildcard $(SRC_DIR)/*.idl $(SRC_DIR)/*/*.idl $(SRC_DIR)/*/*/*.idl)
ifneq ($(EMPTY),$(IDLS))       
FILES_IDM := $(shell egrep -l 'interface.*:.*amiModule' $(IDLS))
endif                          
FILES_G  := $(wildcard $(SRC_DIR)/*.g $(SRC_DIR)/*/*.g $(SRC_DIR)/*/*/*.g)
#=========================================================
ifeq ($(LEVEL),$(FIVE))        
.PHONY               : default
all:
	@echo "Please run make in parent directory"
else                           
ifndef RANLIB                  
override RANLIB := /bin/true
endif                          
ROOTD   := $(shell cd $(ROOT)/..; $(PWD) )
SYS_DIR := $(OUT_DIR)/.$(STAR_HOST_SYS)
LIB_DIR := $(SYS_DIR)/lib
DOMAIN  := $(notdir $(DOM_DIR))
OBJ_DIR := $(SYS_DIR)/obj/$(DOMAIN)
DEP_DIR := $(SYS_DIR)/dep/$(DOMAIN)
DIR_GEN := $(OUT_DIR)/.share
TAB_DIR := $(DIR_GEN)/tables
TMP_DIR := $(DIR_GEN)/tmp/$(DOMAIN)
GEN_DIR := $(DIR_GEN)/$(DOMAIN)
DOM_DIRS:= $(filter-out CVS, $(shell cd $(ROOT)/$(PAMS); ls))
#.
check_out   := $(shell test -d $(OUT_DIR) || mkdir -p $(OUT_DIR)) 
check_lib   := $(shell test -d $(LIB_DIR) || mkdir -p $(LIB_DIR))
check_lib   := $(shell test -h $(OUT_DIR)/lib || ln -s  .@sys/lib $(OUT_DIR)/lib)
#check_lib   := $(shell test -h $(OUT_DIR)/lib/$(STAR_HOST_SYS) || ln -s $(SYS_DIR) $(OUT_DIR)/lib/$(STAR_HOST_SYS))
check_obj   := $(shell test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR))
check_dep   := $(shell test -d $(DEP_DIR) || mkdir -p $(DEP_DIR))
check_gen   := $(shell test -d $(DIR_GEN) || mkdir -p $(DIR_GEN))
check_neg   := $(shell test -d $(GEN_DIR) || mkdir -p $(GEN_DIR))
check_tab   := $(shell test -d $(TAB_DIR) || mkdir -p $(TAB_DIR))
check_tmp   := $(shell test -d $(TMP_DIR) || mkdir -p $(TMP_DIR))
#.
sources := $(strip $(sort $(dir $(wildcard $(SRC_DIR)/*.* $(SRC_DIR)/*/*.* $(SRC_DIR)/*/*/*.*))))
SRC_DIRS:= $(subst /TAIL, ,$(addsuffix TAIL, $(sources)))
IDL_DIRS:= $(wildcard $(ROOT)/$(PAMS)/*/idl $(STAR)/$(PAMS)/*/idl)
INC_DIRG:= $(GEN_DIR) $(TAB_DIR) 
INC_DIRS:= $(wildcard $(ROOT)/$(PAMS)/*/inc $(STAR)/$(PAMS)/*/inc) $(STAR)/.share/$(DOMAIN) $(STAR)/.share/tables
VPATH   := $(wildcard $(SRC_DIRS)) $(GEN_DIR) $(OBJ_DIR)
VPATH   += $(IDL_DIRS)
#VPATH   := $(filter-out $(DOM_DIR)/idl, $(VPATH))
#                 I have idl- or g-files
FILES_CC := $(wildcard $(addsuffix /*.cc, $(SRC_DIRS)))
FILES_C  := $(wildcard $(addsuffix /*.c , $(SRC_DIRS)))
FILES_F  := $(wildcard $(addsuffix /*.F , $(SRC_DIRS)))
FILES_CDF:= $(wildcard $(addsuffix /*.cdf , $(SRC_DIRS)))

NAMES_IDM:= $(basename $(notdir $(FILES_IDM)))
NAMES_G  := $(basename $(notdir $(FILES_G)))
NAMES_CC := $(basename $(notdir $(FILES_CC)))
NAMES_C  := $(basename $(notdir $(FILES_C)))
NAMES_F  := $(basename $(notdir $(FILES_F)))
NAMES_CDF:= $(basename $(notdir $(FILES_CDF)))

FILES_I  := $(addprefix $(GEN_DIR)/, $(addsuffix .inc, $(NAMES_IDM)))
FILES_H  := $(addprefix $(GEN_DIR)/, $(addsuffix .h,   $(NAMES_IDM)))
FILES_CA := $(addprefix $(GEN_DIR)/, $(addsuffix _i.cc,$(NAMES_IDM)))
FILES_O  := $(strip \
            $(addprefix $(OBJ_DIR)/, $(addsuffix .o,   $(NAMES_F) \
                                                       $(NAMES_C) $(NAMES_CC))))
ifeq ($(DOMAIN),gen)           
ifneq ($(PKG),$(EMPTY))         
		PKG_LIB := lib$(PKG).a
endif                           
else                           
ifneq ($(DOMAIN),$(EMPTY))      
		PKG_LIB := lib$(DOMAIN).a
endif                           
endif                          
ifneq ($(FILES_O),$(EMPTY))    
LIB_PKG := $(LIB_DIR)/$(PKG_LIB) 
endif                          
ifneq ($(EMPTY),$(PKG))        
	PKG_SL  := $(PKG).sl
        PKG_ST  := St_$(PKG).so
        PKG_TAB := St_Tables.so
	PKG_BASE:= St_base.so
ifneq ($(EMPTY),$(strip $(FILES_IDM) $(FILES_G) $(FILES_CDF))) 
        SL_PKG  := $(LIB_DIR)/$(PKG_SL)
        ST_PKG  := $(LIB_DIR)/$(PKG_ST)
	ST_TAB  := $(LIB_DIR)/$(PKG_TAB)
	ST_BASE := $(LIB_DIR)/$(PKG_BASE)
endif                           
endif                          
MKDEPFLAGS:= -MG -MM -w
ifndef NODEPEND                
FILES_D  := $(addprefix $(DEP_DIR)/, $(addsuffix .d,   $(notdir $(basename $(FILES_O)))))
FILES_DM := $(addprefix $(GEN_DIR)/, $(addsuffix .didl, $(NAMES_IDM)))                         
endif                          
FILES_O  += $(addprefix $(OBJ_DIR)/, $(addsuffix .o,   $(notdir $(basename $(FILES_CA)))))
NAMES_O   = $(notdir $(FILES_O))
ifeq ($(LEVEL),$(TWO))          # domain level: add all domain IDM
ifneq ($(EMPTY),$(FILES_IDM))   
IDLSD    := $(wildcard $(STAR)/$(PAMS)/$(DOMAIN)/*/*.idl $(STAR)/$(PAMS)/$(DOMAIN)/*/*/*.idl $(STAR)/$(PAMS)/$(DOMAIN)/*/*/*/*.idl)
ifneq ($(EMPTY),$(IDLSD))      
FILES_DD := $(shell egrep -l 'interface.*:.*amiModule' $(IDLSD))
NAMES_IDM+= $(basename $(notdir $(FILES_DD)))
override  NAMES_IDM := $(sort $(NAMES_IDM))
endif                          
endif                           
endif                          
ifneq (,$(NAMES_IDM))          
FILES_SL  := $(addprefix $(OBJ_DIR)/, $(PKG)_init.o)
endif                          
ifneq (,$(NAMES_CDF))          
FILES_SL  += $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAMES_CDF)))
endif                          
ifneq (,$(NAMES_G))            
FILES_SL  += $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAMES_G)))
endif                          
ifneq (,$(NAMES_CC))            
FILES_SL  += $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAMES_CC)))
endif                          
#-------------------------------includes----------------------------
STICFLAGS =  $(addprefix -I,  $(STAR)/asps/staf/inc $(SRC_DIR) $(IDL_DIRS))
ifneq ($(STAR_SYS),hp_ux102)   
CPPFLAGS += -D$(STAR_SYS) $(strip -D$(shell uname)) 
endif                          
ifneq ($(ROOT),$(STAR))        
CPPFLAGG +=  $(addprefix -I, $(INC_DIRG))
endif                          
CPPFLAGS += -I. -I../ -I/usr/include -I$(STAR)/asps/staf/inc \
             $(addprefix -I, $(SRC_DIR) $(GEN_DIR) $(INC_DIRS)) -I$(CERN_ROOT)/include -I$(CERN_ROOT)/include/cfortran
FFLAGS   += -DCERNLIB_TYPE
#                                   -I$(CERN_ROOT)/src/geant321 
ifndef NODEBUG                 
FFLAGS   += -g
CFLAGS   += -g
CXXFLAGS += -g
CPPFLAGS += -DDEBUG
else
FFLAGS   += -O
CFLAGS   += -O
CXXFLAGS += -O
endif                          
ifeq ($(EMPTY),$(findstring $(STAR_HOST_SYS),hp_ux102 hp_ux102_aCC))
ifndef CERN_LIBS               
    CERN_LIBS := $(shell cernlib mathlib kernlib)
endif
else
    CERN_LIBS :=
endif                          
ifndef LIBRARIES
		LIBRARIES := $(LIB_PKG)	               
ifneq ($(STAR_PATH),$(ROOTD))   
ifneq ($(LIB_PKG),$(EMPTY))
LIBRARIES += $(shell test -f $(STAR_LIB)/$(PKG_LIB) && echo  $(STAR_LIB)/$(PKG_LIB))
endif                           
endif                           
LIBRARIES += -L$(STAR)/asps/../.$(STAR_HOST_SYS)/lib -ltls -lmsg
endif
define TAB_GEN
	cp  $(FIRST_DEP) $(TAB_DIR)/ ; cd $(TAB_DIR); $(STIC) -r -q $(STICFLAGS) $(FIRST_DEP); $(RM) $(STEM).idl
endef
define MOD_GEN
	cp  $(FIRST_DEP) $(TMP_DIR)/ ; cd $(TMP_DIR);\
        $(STIC) -r -q $(STICFLAGS) $(FIRST_DEP); \
        mv $(STEM)_i.cc $(STEM).h $(STEM).inc St_$(STEM)_Module.cxx  St_$(STEM)_Module.h $(GEN_DIR);\
        mv *.h *.inc *.cxx $(TAB_DIR)/; \
        gcc  $(MKDEPFLAGS)  -x c $(STICFLAGS) $(FIRST_DEP) | \
        sed -e 's/$(STEM)\.idl\.o/$(subst .,\., $(subst /,\/, $(GEN_DIR)))\/$(STEM)\.didl/g' \
        > $(GEN_DIR)/$(STEM).didl; \
        $(STIC) -q -M  $(STICFLAGS) $(FIRST_DEP) | grep ":" | sed -e 's/or merger//g'  \
        >> $(GEN_DIR)/$(STEM).didl; $(RM) $(STEM).idl
#       temporarly, until stic is fixed:
	@sed -e 's/broker->newInvoker(\(.*\),/broker->deleteInvoker(\1); broker->newInvoker(\1,/' \
                $(GEN_DIR)/$(STEM)_i.cc > temp
	@mv  -f temp $(GEN_DIR)/$(STEM)_i.cc
endef                          
#-------------------------------rules-------------------------------
NOROOT=yes
ifndef NOROOT
TARGETS := $(PKG) $(ST_PKG)  $(ST_BASE) $(ST_TAB)
else
TARGETS := $(PKG)
endif
# phony - not a file
.PHONY               : $(TARGETS) depend clean test
all                  : $(TARGETS)
$(ST_PKG) : $(wiildcard $(addprefix $(GEN_DIR), *.h *.cxx))
	gmake -f $(STAR)/mgr/MakeDll.mk -C $(GEN_DIR) SO_LIB=$(ALL_TAGS)
$(ST_TAB) : $(wiildcard $(addprefix $(TAB_DIR), *.h *.cxx))
	gmake -f $(STAR)/mgr/MakeDll.mk -C $(TAB_DIR) SO_LIB=$(ALL_TAGS)
$(ST_BASE) : $(wildcard $(addprefix $(STAR)/StRoot/base/, *.c *.cxx *.h)) 
	gmake -f $(STAR)/mgr/MakeDll.mk -C $(STAR)/StRoot/base SO_LIB=$(ALL_TAGS)
# all files:
ifneq ($(EMPTY),$(strip $(FILES_O) $(FILES_SL))) 
#                 I have NO idl- and NO g-files
$(PKG)               : $(SL_PKG) $(LIB_PKG)
ifneq ($(FILES_O),$(EMPTY))    
$(LIB_PKG): $(FILES_O)
	$(AR) $(ARFLAGS) $(LIB_PKG) $(FILES_O)
	@echo "          Library " $(LIB_PKG) " has been updated"
endif                          
ifneq ($(FILES_SL),$(EMPTY))   
$(SL_PKG): $(FILES_SL) $(LIB_PKG)
	$(LD) $(LDFLAGS) $(FILES_SL) -o $(SL_PKG) \
        $(LIBRARIES) $(CERN_LIBS) $(LD_LIBS) $(CC_LIBS) 
	@echo "          Shared library " $(SL_PKG) " has been created"
#--------- module ---------
ifneq ($(NAMES_IDM),)           
$(OBJ_DIR)/$(PKG)_init.o: $(FILES_IDM) 
	@if [ -f $(GEN_DIR)/$(PKG)_init.cc ]; then  rm $(GEN_DIR)/$(PKG)_init.cc ; fi
	@echo '/* '$(PKG)' package interface to STAF */' > $(GEN_DIR)/$(PKG)_init.cc
	@echo '/* automatically generated file */'      >> $(GEN_DIR)/$(PKG)_init.cc
	@for p in $(NAMES_IDM); do echo $p; echo '#include "'$$p'.h"'   \
                                                        >> $(GEN_DIR)/$(PKG)_init.cc ; done
	@echo 'extern "C" int  $(PKG)_init (void);'     >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'extern "C" int  $(PKG)_start(void);'     >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'extern "C" int  $(PKG)_stop (void);'     >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'extern "C" void $(PKG)_init_();  '       >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'void $(PKG)_init_() {$(PKG)_start();}'   >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'int  $(PKG)_init () { return 1; }'       >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'int  $(PKG)_start() {'                   >> $(GEN_DIR)/$(PKG)_init.cc
	@for p in $(NAMES_IDM); do echo "      $${p}_load_ami(ami);" \
                                                        >> $(GEN_DIR)/$(PKG)_init.cc ; done
	@echo '                       return 1; }'      >> $(GEN_DIR)/$(PKG)_init.cc
	@echo 'int  $(PKG)_stop () { return 1; }'       >> $(GEN_DIR)/$(PKG)_init.cc
	$(CXX) $(CPPFLAGS) $(CPPFLAGG) $(CXXFLAGS) -c $(GEN_DIR)/$(PKG)_init.cc -o $(ALL_TAGS)
endif                           
endif                           # NO idl- or g-files
#-----cleaning------------------------------
clean: clean_obj clean_lib clean_dep
clean_share:
	rm -rf $(GEN_DIR) 
clean_obj:
	rm -rf $(OBJ_DIR) 
clean_dep:
	rm -rf $(DEP_DIR) 
clean_lib:
	rm -rf $(SL_PKG) $(LIB_PKG)
#-----dependencies--------------------------
ifneq ($(EMPTY), $(strip $(FILES_D))) 
include $(FILES_D)
endif                               #
ifneq ($(EMPTY), $(strip $(FILES_DM)))
include $(FILES_DM)
endif                               # 
endif                            # end if of FILES_O FILES_SL
endif       # LEVEL 4
#--------  idm, idl --------
$(TAB_DIR)/%.h           : %.idl  
	$(TAB_GEN)
$(TAB_DIR)/%.inc         : %.idl
	 $(TAB_GEN)
$(TAB_DIR)/St_%_Table.cxx: %.idl
	 $(TAB_GEN)
$(TAB_DIR)/St_%_Table.h  : %.idl
	 $(TAB_GEN)
#--- compilation -
$(GEN_DIR)/geant3.def: $(STAR)/asps/agi/gst/geant3.def
	test -h $(GEN_DIR)/geant3.def || $(RM)  $(GEN_DIR)/geant3.def
	test -h $(GEN_DIR)/geant3.def || ln -s $(STAR)/asps/agi/gst/geant3.def  $(GEN_DIR)/geant3.def 
$(OBJ_DIR)/%.o:%.g $(GEN_DIR)/geant3.def
#	test -h $(GEN_DIR)/geant3.def || ln -s $(STAR)/asps/agi/gst/geant3.def  $(GEN_DIR)/geant3.def
	cp $(FIRST_DEP) $(GEN_DIR); cd $(GEN_DIR); $(GEANT3) $(FIRST_DEP) -o  $(GEN_DIR)/$(STEM).F
	$(FC)  $(CPPFLAGS) $(FFLAGS) -c $(GEN_DIR)/$(STEM).F  -o  $(ALL_TAGS)
$(OBJ_DIR)/%.o: %.F
	$(FC)  $(CPPFLAGS) $(FFLAGS) $(F_EXTENDED)   -c $(FIRST_DEP) -o $(OBJ_DIR)/$(STEM).o
$(OBJ_DIR)/%.o: %.c
	$(CC)  $(CPPFLAGS) $(CFLAGS)   -c $(FIRST_DEP) -o $(OBJ_DIR)/$(STEM).o
$(OBJ_DIR)/%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(FIRST_DEP) -o $(OBJ_DIR)/$(STEM).o
$(OBJ_DIR)/%.o: %.cdf
	$(KUIPC) $(KUIPC_FLAGS) $(FIRST_DEP) $(GEN_DIR)/$(STEM).c
	$(CC)  $(CPPFLAGS) $(CFLAGS)   -c $(GEN_DIR)/$(STEM).c -o $(OBJ_DIR)/$(STEM).o; \
        $(RM)  $(GEN_DIR)/$(STEM).c
#-----dependencies-------
$(GEN_DIR)/%.didl        : %.idl 
	$(MOD_GEN)
$(GEN_DIR)/%_i.cc        : %.idl
	$(MOD_GEN)
$(GEN_DIR)/%.h           : %.idl
	$(MOD_GEN)
$(GEN_DIR)/%.inc         : %.idl
	$(MOD_GEN)
$(GEN_DIR)/%.inc         : %.idl
	$(MOD_GEN)
$(GEN_DIR)/St_%_Module.h : %.idl
	$(MOD_GEN)
$(DEP_DIR)/%.d: %.cc 
	gcc $(MKDEPFLAGS) $(CPPFLAGS) $(FIRST_DEP) | sed -e \
's/$(notdir $(STEM))\.o/$(subst .,\.,$(subst /,\/,$(OBJ_DIR)))\/$(STEM)\.o $(subst .,\.,$(subst /,\/,$(ALL_TAGS)))/g'\
        > $(ALL_TAGS)
$(DEP_DIR)/%.d: %.c
	gcc $(MKDEPFLAGS) $(CPPFLAGS) $(FIRST_DEP) | sed -e \
's/$(notdir $(STEM))\.o/$(subst .,\.,$(subst /,\/,$(OBJ_DIR)))\/$(STEM)\.o $(subst .,\.,$(subst /,\/,$(ALL_TAGS)))/g'\
        > $(ALL_TAGS)
$(DEP_DIR)/%.d: %.F
	gcc -traditional -x c $(MKDEPFLAGS) $(CPPFLAGS) $(FIRST_DEP) | sed -e \
's/$(notdir $(STEM))\.F\.o/$(subst .,\.,$(subst /,\/,$(OBJ_DIR)))\/$(STEM)\.o $(subst .,\.,$(subst /,\/,$(ALL_TAGS)))/g'\
        > $(ALL_TAGS)
$(DEP_DIR)/%.d: %.cdf
	cd $(SRC_DIR); \
        echo "$(notdir $(STEM)).c $(ALL_TAGS): $(ALL_DEPS)" > $(ALL_TAGS) ;
        echo "$(STEM).o: $(STEM).c" >> $(ALL_TAGS)
endif                           # end if of SUBDIR loop
#-----test variables------------------------
test: test_dir test_files test_mk
test_files:
	@echo "FILES_IDM =" $(FILES_IDM)
	@echo "FILES_G   =" $(FILES_G)
	@echo "FILES_CC  =" $(FILES_CC)
	@echo "FILES_C   =" $(FILES_C)
	@echo "FILES_F   =" $(FILES_F)
	@echo "FILES_I   =" $(FILES_I)
	@echo "FILES_H   =" $(FILES_H)
	@echo "FILES_CA  =" $(FILES_CA)
	@echo "FILES_O   =" $(FILES_O)
	@echo "FILES_D   =" $(FILES_D)
	@echo "FILES_CDF =" $(FILES_CDF)
	@echo "FILES_SL  =" $(FILES_SL)
	@echo "NAMES_IDM =" $(NAMES_IDM)
	@echo "NAMES_G   =" $(NAMES_G)
	@echo "NAMES_CC  =" $(NAMES_CC)
	@echo "NAMES_C   =" $(NAMES_C)
	@echo "NAMES_F   =" $(NAMES_F)
	@echo "NAMES_CDF =" $(NAMES_CDF)
test_mk:
	@echo "STAR_HOST_SYS=" $(STAR_HOST_SYS) "; OPSYS =" $(OPSYS)
	@echo "HOST      =" $(HOST)  "; STAR_SYS =" $(STAR_SYS)
	@echo "MAKE      =" $(MAKE) 
	@echo "VPATH     =" $(VPATH)
	@echo "SHELL     =" $(SHELL)
	@echo "MAKE      =" $(MAKE)
	@echo "MAKELEVEL =" $(MAKELEVEL)
	@echo "MAKEFILE  =" $(MAKEFILE)
	@echo "MAKFLAGS  =" $(MAKEFLAGS)
	@echo "SUFFIXES  =" $(SUFFIXES)
	@echo "STIC      =" $(STIC)	"; STICFLAGS	="	$(STICFLAGS)
	@echo "AR        =" $(AR)	"; ARFLAGS 	="	$(ARFLAGS)
	@echo "RANLIB    =" $(RANLIB)
	@echo "AS        =" $(AS)	"; ASFLAGS 	="	$(ASFLAGS)
	@echo "CC        =" $(CC)	"; CFLAGS 	="	$(CFLAGS)
	@echo "CXX       =" $(CXX)	"; CXXFLAGS 	="	$(CXXFLAGS)
	@echo "CPP       =" $(CPP)	"; CPPFLAGS 	="	$(CPPFLAGS)
	@echo "FC        =" $(FC)	"; FFLAGS 	="	$(FFLAGS)
	@echo "F_EXTENDED=" $(F_EXTENDED)
	@echo "LD        =" $(LD)	"; LDFLAGS	="	$(LDFLAGS)
	@echo "LD_LIBS   =" $(LD_LIBS)  "; CC_LIBS	="	$(CC_LIBS)
	@echo "LDS       =" $(LDS)      "; LDS_FLAGS    ="      $(LDS_FLAGS)
	@echo "RM        =" $(RM)
	@echo "SUBDIRS   =" $(SUBDIRS)
	@echo "LIBRARIES =" $(LIBRARIES)
	@echo "CERN_LIBS =" $(CERN_LIBS)
	@echo "DIRS      =" $(DIRS)
	@echo "ALL_DEPS  =" $(ALL_DEPS)
	@echo "FIRST_DEP =" $(FIRST_DEP)
	@echo "FIRSTF    =" $(FIRSTF)
	@echo "ALL_TAGS  =" $(ALL_TAGS)
	@echo "STEM      =" $(STEM)
	@echo "STEMF     =" $(STEMF)
	@echo "STIC      =" $(STIC)
	@echo "KUIPC     =" $(KUIPC)
	@echo "KUIPC_FLAGS=" $(KUIPC_FLAGS)
	@echo "EMPTY     =" $(EMPTY)
	@echo "ZERO      =" $(ZERO)
	@echo "ONE       =" $(ONE)
	@echo "TWO       =" $(TWO)
	@echo "THREE     =" $(THREE)
	@echo "FOUR      =" $(FOUR)
test_dir:
	@echo "CWD       =" $(CWD)  
	@echo "ROOT      =" $(ROOT) "; ROOTD = " $(ROOTD)
	@echo "DOMAIN    =" $(DOMAIN)
	@echo "NAME      =" $(NAME) 
	@echo "PGK       =" $(PKG) 
	@echo "PKG_SL    =" $(PKG_SL)
	@echo "PKG_LIB   =" $(PKG_LIB)
	@echo "SL_PGK    =" $(SL_PKG)
	@echo "LIB_PKG   =" $(LIB_PKG)
	@echo "INP_DIR   =" $(INP_DIR)
	@echo "DOM_DIR   =" $(DOM_DIR)
	@echo "DOM_DIRS  =" $(DOM_DIRS)
	@echo "OUT_DIR   =" $(OUT_DIR)
	@echo "SRC_DIR   =" $(SRC_DIR)
	@echo "IDL_DIRS  =" $(IDL_DIRS)
	@echo "INC_DIRS  =" $(INC_DIRS)
	@echo "LIB_DIR   =" $(LIB_DIR)
	@echo "OBJ_DIR   =" $(OBJ_DIR)
	@echo "DEP_DIR   =" $(DEP_DIR)
	@echo "GEN_DIR   =" $(GEN_DIR)
	@echo "SRC_DIRS  =" $(SRC_DIRS)
	@echo "INP_DIR   =" $(INP_DIR)
	@echo "LEVEL     =" $(LEVEL)
	@echo "SUBDIRS   =" $(SUBDIRS)
	@echo "sources   =" $(sources)
	@echo "SRC_DIRS  =" $(SRC_DIRS)
	@echo "IDLS      =" $(IDLS)
	@echo "IDLSD     =" $(IDLSD)
	@echo "FILES_DD  =" $(FILES_DD)
	@echo "FILES_D   =" $(FILES_D)
	@echo "FILES_DM  =" $(FILES_DM)
else
.PHONY               : default
all:
	@echo "No PAMS. Take standard libraries"
endif                           # LEVEL=0 







