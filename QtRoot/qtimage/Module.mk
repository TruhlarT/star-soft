# Module.mk for qtimage module
# Copyright (c) 2004 Valeri Fine Brookhaven National Laboratory
#
# Author: Valeri Fine, 7/02/2004

MODDIR       := qtimage
MODDIRS      := $(MODDIR)/src
MODDIRI      := $(MODDIR)/inc

QTIMAGEDIR   := $(MODDIR)
QTIMAGEDIRS  := $(QTIMAGEDIR)/src
QTIMAGEDIRI  := $(QTIMAGEDIR)/inc

##### libqtimage #####


QTIMAGEH     := $(filter-out $(MODDIRI)/LinkDef%,$(wildcard $(MODDIRI)/*.h))
QTIMAGES     := $(filter-out $(MODDIRS)/moc_%,$(filter-out $(MODDIRS)/G__%,$(wildcard $(MODDIRS)/*.cxx)))
QTIMAGEO     := $(QTIMAGES:.cxx=.o)

# --  Qt signals/slots
QTIMAGEMOCS  := $(subst $(QTIMAGEDIRI)/,$(QTIMAGEDIRS)/moc_,\
		   $(patsubst %.h,%.cxx,$(QTIMAGEH)))

QTIMAGEMOCO  := $(QTIMAGEMOCS:.cxx=.o)

# -- ROOT dictionary  
QTIMAGEL     := $(MODDIRI)/LinkDef.h
QTIMAGEDS    := $(MODDIRS)/G__QtImage.cxx
QTIMAGEDO    := $(QTIMAGEDS:.cxx=.o)
QTIMAGEDH    := $(QTIMAGEDS:.cxx=.h)

QTIMAGEDEP   := $(QTIMAGEO:.o=.d) 
# -- $(QTIMAGEDO:.o=.d)

QTIMAGELIB   := $(LPATH)/libQtImage.$(SOEXT)

QTIMAGECXXFLAGS := -DQT_DLL -DQT_THREAD_SUPPORT -I. -I$(QTDIR)/mkspecs/default $(QTINCDIR:%=-I%)

# used in the main Makefile
ALLHDRS     += $(patsubst $(MODDIRI)/%.h,include/%.h,$(QTIMAGEH))
ALLLIBS     += $(QTIMAGELIB)

# include all dependency files
INCLUDEFILES += $(QTIMAGEDEP)

##### local rules #####
include/%.h:    $(QTIMAGEDIRI)/%.h
		cp $< $@

$(QTIMAGELIB):  $(QTIMAGEO) $(QTIMAGEDO) $(QTIMAGEMOCO) $(MAINLIBS) \
                $(QTIMAGELIBDEP)
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)" \
		   "$(SOFLAGS)" libQtImage.$(SOEXT) $@ \
		   "$(QTIMAGEO) $(QTIMAGEMOCO) $(QTIMAGEDO)" \
		   "$(QTIMAGELIBEXTRA) "

$(QTIMAGEDS):   $(QTIMAGEH) $(QTIMAGEL) $(ROOTCINTTMPEXE)
		@echo "Generating dictionary $@..."
		$(ROOTCINTTMP) -f $@ -c $(QTIMAGEH) $(QTIMAGEL)

$(QTIMAGEDO):   $(QTIMAGEDS)
		$(CXX) $(NOOPT) $(CXXFLAGS) $(QTIMAGECXXFLAGS)  $(CXXOUT)$@ -c $<

all-qtimage:    $(QTIMAGELIB)

clean-qtimage:
		@rm -f $(QTIMAGEO) $(QTIMAGEDO) $(QTIMAGEMOCO) $(QTIMAGEMOC)

clean::         clean-qtimage

distclean-qtimage: clean-qtimage
		@rm -f $(QTIMAGEDEP) $(QTIMAGEDS) $(QTIMAGEDH) $(QTIMAGELIB)

distclean::     distclean-qtimage

show-qtimage:
	@echo QTIMAGES:    $(QTIMAGES)
	@echo QTIMAGEMOCS: $(QTIMAGEMOCS)
	@echo QTIMAGEO:    $(QTIMAGEO)
	@echo QTIMAGEMOCO: $(QTIMAGEMOCO)

##### extra rules ######
$(QTIMAGEO): CXXFLAGS +=  $(QTIMAGECXXFLAGS)

$(QTIMAGEMOCO): %.o: %.cxx
	$(CXX) $(OPT) $(CXXFLAGS) $(QTIMAGECXXFLAGS) $(CXXOUT)$@ -c $<

#moc_%.cpp: %.h
#            $(QTMOCEXE) $< -o $@

$(sort $(QTIMAGEMOCS)) : $(QTIMAGEDIRS)/moc_%.cxx: $(QTIMAGEDIRI)/%.h 
	$(QTMOCEXE) $< -o $@
