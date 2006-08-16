ifeq ($(PLATFORM),win32) 
# move libThread  from PROOFLIBS to libCore   $(LPATH)/libThread.lib
  PROOFLIBS    := $(LPATH)/libProof.lib $(LPATH)/libTreePlayer.lib 
  COREL  +=  $(THREADL)
  COREO  +=  $(THREADO)
  COREDO +=  $(THREADDO)
endif