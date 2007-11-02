# $Id: Module.mk,v 1.4 2007/11/02 17:48:07 fine Exp $
# Module.mk for qtgui module
# Copyright (c) 2001 Valeri Fine
#
# Author: Valeri Fine, 21/10/2001

MODDIR           := qtgui
MODDIRS          := $(MODDIR)/src
MODDIRI          := $(MODDIR)/inc

ROOTQTGUIDIR     := $(MODDIR)
ROOTQTGUIDIRS    := $(ROOTQTGUIDIR)/src
ROOTQTGUIDIRI    := $(ROOTQTGUIDIR)/inc

QT4           :=  $(findstring QtCore, $(QTINCDIR))

##### libQtGui #####
QTGUIL          := $(MODDIRI)/LinkDef.h
QTGUIDS         := $(MODDIRS)/G__QtGUI.cxx
QTGUIDO         := $(QTGUIDS:.cxx=.o)
QTGUIDH         := $(QTGUIDS:.cxx=.h)

# QTH1         := $(MODDIRI)/TGWin32.h $(MODDIRI)/TQtGuiFactory.h
QTGUIH1        := $(MODDIRI)/TQtGuiFactory.h        $(MODDIRI)/TBrowserCustom.h   \
                  $(MODDIRI)/TQtPatternSelect.h     $(MODDIRI)/TQtTabValidator.h  \
                  $(MODDIRI)/TEmbeddedPad.h         $(MODDIRI)/TQtColorSelect.h   \
                  $(MODDIRI)/TQtZoomPadWidget.h     $(MODDIRI)/TQGsiRootCanvas.h  \
				  $(MODDIRI)/TQtPad2Html.h          $(MODDIRI)/TQtCanvas2Html.h   \
                  $(MODDIRI)/TQtMarkerSelect.h      $(MODDIRI)/TQtPixmapBox.h   
               
QTGUIH          := $(filter-out $(MODDIRI)/LinkDef%,$(wildcard $(MODDIRI)/*.h))

QTGUIMOCH     := $(ROOTQTGUIDIRI)/TQtBrowserImp.h          $(ROOTQTGUIDIRI)/TQtCanvasImp.h         \
                 $(ROOTQTGUIDIRI)/TQtCanvasWidget.h        $(ROOTQTGUIDIRI)/TQtColorSelect.h       \
                 $(ROOTQTGUIDIRI)/TQtColorSelectButton.h   $(ROOTQTGUIDIRI)/TQtContextMenuImp.h    \
                 $(ROOTQTGUIDIRI)/TQtControlBarImp.h       $(ROOTQTGUIDIRI)/TQtIconBrowserImp.h    \
                 $(ROOTQTGUIDIRI)/TQtCustomizeCanvasMenu.h $(ROOTQTGUIDIRI)/TQtFloatSpinBox.h      \
                 $(ROOTQTGUIDIRI)/TQtInspectImp.h          $(ROOTQTGUIDIRI)/TQtRootBrowserImp.h    \
                 $(ROOTQTGUIDIRI)/TQtObjectDialog.h        $(ROOTQTGUIDIRI)/TQtPatternSelect.h     \
                 $(ROOTQTGUIDIRI)/TQtPatternSelectButton.h $(ROOTQTGUIDIRI)/TQtRootBrowserAction.h \
                 $(ROOTQTGUIDIRI)/TQtZoomPadWidget.h       $(ROOTQTGUIDIRI)/TQtToolBar.h           \
                 $(ROOTQTGUIDIRI)/TQtMarkerSelect.h        $(ROOTQTGUIDIRI)/TQtPixmapBox.h         \
                 $(ROOTQTGUIDIRI)/TQtMarkerSelectButton.h\
                 $(ROOTQTGUIDIRI)/TQtFloatSlider.h   
                 
#                 $(ROOTQTGUIDIRI)/TQGsiRootCanvas.h   


QTGUIMOC        := $(subst $(MODDIRI)/,$(MODDIRS)/moc_,$(patsubst %.h,%.cxx,$(QTGUIMOCH)))
QTGUIMOCO       := $(QTGUIMOC:.cxx=.o)

QTGUIS          := $(filter-out $(MODDIRS)/moc_%,\
		    $(filter-out $(MODDIRS)/G__%,$(wildcard $(MODDIRS)/*.cxx)))
QTGUIO          := $(QTGUIS:.cxx=.o)

QTGUIDEP        := $(QTGUIO:.o=.d) $(QTGUIDO:.o=.d)

QTGUICXXFLAGS   := -DQT_DLL -DQT_THREAD_SUPPORT -I. 
ifeq ($(ARCH),win32)
QTGUICXXFLAGS   += -I$(QTDIR)/mkspecs/win32-msvc2005
else
QTGUICXXFLAGS   += -I$(QTDIR)/mkspecs/default 
endif

QTGUICXXFLAGS   += $(QTINCDIR:%=-I%)
QTGUILIB        := $(LPATH)/libQtRootGui.$(SOEXT)


QTGUIOBJEXTRA   := $(QTGUIMOCO)

QCUSTOMWIDGETS += $(ROOTQTGUIDIRI)/TQtColorSelectButton.cw  $(ROOTQTGUIDIRI)/TQtLineStyleComboBox.cw   \
                  $(ROOTQTGUIDIRI)/TQtFloatSlider.cw        $(ROOTQTGUIDIRI)/TQtLineWidthComboBox.cw   \
                  $(ROOTQTGUIDIRI)/TQtFloatSpinBox.cw       $(ROOTQTGUIDIRI)/TQtPatternSelectButton.cw \
                  $(ROOTQTGUIDIRI)/TQtFontComboBox.cw

# used in the main Makefile
ALLHDRS     += $(patsubst $(MODDIRI)/%.h,include/%.h,$(QTGUIH))
ALLHDRS     += $(patsubst $(ROOTQTGUIDIRI)/%.cw,include/%.cw,$(QCUSTOMWIDGETS))
ALLLIBS     += $(QTGUILIB)

# include all dependency files
INCLUDEFILES += $(QTGUIDEP)

##### local rules #####
include/%.h:    $(ROOTQTGUIDIRI)/%.h
		cp $< $@
		
include/%.cw:   $(ROOTQTGUIDIRI)/%.cw
		cp $< $@

$(QTGUILIB):    $(QTGUIO) $(QTGUIDO) $(QTGUIMOCO)  $(ORDER_) $(MAINLIBS) $(QTGUILIBDEP)
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)" \
		   "$(SOFLAGS)" libQtRootGui.$(SOEXT) $@       \
		   "$(QTGUIO) $(QTGUIMOCO) $(QTGUIDO)"     \
		   "$(QTGUILIBEXTRA)" 

$(QTGUIDS):     $(QTGUIH1) $(QTGUIL) $(ROOTCINTTMPEXE) include/rootcint.pri
		@echo "Generating dictionary $@..."
		$(ROOTCINTTMP) -f $@ -c $(QTGUIH1) $(QTGUIL)

$(QTGUIDO): $(QTGUIDS)
		$(CXX) $(NOOPT) $(CXXFLAGS) $(QTGUICXXFLAGS) $(CXXOUT)$@ -c $<

all-qtgui:      $(QTGUILIB)

map-qtgui:      $(RLIBMAP)
		$(RLIBMAP) -r $(ROOTMAP) -l $(QTGUILIB) \
                  -d $(QTGUILIBDEP) -c $(QTGUIL)

map::           map-qtgui

clean-qtgui:
		rm -f $(QTGUIO) $(QTGUIDO) $(QTGUIMOC) $(QTGUIMOCO)

clean::         clean-qtgui

show-qtgui:
		@echo "QTGUIO     $(QTGUIO)"
		@echo "QTGUIDO    $(QTGUIDO)" 
		@echo "QTGUIMOC   $(QTGUIMOC)" 
		@echo "QTGUIMOCO  $(QTGUIMOCO)"

distclean-qtgui: clean-qtgui 
		@rm -f $(QTGUIDEP) $(QTGUIDS) $(QTGUIDH) $(QTGUILIB)

distclean::     distclean-qtgui

##### extra rules ######
$(sort $(QTGUIMOCO) $(QTGUIO)):  CXXFLAGS += $(GQTCXXFLAGS)
#(GQTGUIDO): CXXFLAGS += kkk $(GQTCXXFLAGS)

$(QTGUIMOC) : $(ROOTQTGUIDIRS)/moc_%.cxx: $(ROOTQTGUIDIRI)/%.h
ifeq (,$(QT4))
	$(QTMOCEXE)  $< -o $@
else
	$(QTMOCEXE)  $(QTGUICXXFLAGS) $< -o $@
endif
