# $Id: Module.mk,v 1.5 2009/08/03 18:03:08 fine Exp $
# Module.mk for qtgui module
# Copyright (c) 2001 Valeri Fine
#
# Author: Valeri Fine, 21/10/2001

MODNAME          := qtgui

MODDIR           := $(MODNAME)
MODDIRS          := $(MODDIR)/src
MODDIRI          := $(MODDIR)/inc

ROOTQTGUIDIR     := $(MODDIR)
ROOTQTGUIDIRS    := $(ROOTQTGUIDIR)/src
ROOTQTGUIDIRI    := $(ROOTQTGUIDIR)/inc

QT4              :=  $(findstring QtCore, $(QTINCDIR))

##### libQtGui #####
QTGUIL          := $(MODDIRI)/LinkDef.h
QTGUIDS         := $(MODDIRS)/G__QtGUI.cxx
QTGUIDO         := $(QTGUIDS:.cxx=.o)
QTGUIDH         := $(QTGUIDS:.cxx=.h)

# QTH1         := $(MODDIRI)/TGWin32.h $(MODDIRI)/TQtGuiFactory.h
QTGUIH1        := TQtGuiFactory.h        TBrowserCustom.h   \
                  TQtPatternSelect.h     TQtTabValidator.h  \
                  TEmbeddedPad.h         TQtColorSelect.h   \
                  TQtZoomPadWidget.h     TQGsiRootCanvas.h  \
			      TQtPad2Html.h          TQtCanvas2Html.h   \
                  TQtMarkerSelect.h      TQtPixmapBox.h   
						
QTGUIH1        := $(patsubst %,$(MODDIRI)/%,$(QTGUIH1))
QTGUIH         := $(filter-out $(MODDIRI)/LinkDef%,$(wildcard $(MODDIRI)/*.h))

QTGUIMOCH     := TQtBrowserImp.h          TQtCanvasImp.h         \
                 TQtCanvasWidget.h        TQtColorSelect.h       \
                 TQtColorSelectButton.h   TQtContextMenuImp.h    \
                 TQtControlBarImp.h       TQtIconBrowserImp.h    \
                 TQtCustomizeCanvasMenu.h TQtFloatSpinBox.h      \
                 TQtInspectImp.h          TQtRootBrowserImp.h    \
                 TQtObjectDialog.h        TQtPatternSelect.h     \
                 TQtPatternSelectButton.h TQtRootBrowserAction.h \
                 TQtZoomPadWidget.h       TQtToolBar.h           \
                 TQtMarkerSelect.h        TQtPixmapBox.h         \
                 TQtMarkerSelectButton.h  TQtStyleComboBox.h     \
                 TQtFloatSlider.h         TQtRootCommandCombo.h  \
                 qtcolorpicker.h          TQtColorPickerHelper.h \
                 qtmmlwidget.h   
                 
QTGUIMOCH        := $(patsubst %,$(MODDIRI)/%,$(QTGUIMOCH))
                 
#                 $(ROOTQTGUIDIRI)/TQGsiRootCanvas.h   

QTGUISOLUTIONH  := $(ROOTQTGUIDIRI)/QtMmlWidget $(ROOTQTGUIDIRI)/QtColorPicker  $(ROOTQTGUIDIRI)/QtMmlDocument
QTGUIMOC        := $(subst $(MODDIRI)/,$(MODDIRS)/moc_,$(patsubst %.h,%.cxx,$(QTGUIMOCH)))
QTGUIMOCO       := $(QTGUIMOC:.cxx=.o)

QTGUIS          := $(filter-out $(MODDIRS)/moc_%,$(filter-out $(MODDIRS)/G__%,$(wildcard $(MODDIRS)/*.cxx)))
QTGUIO          := $(QTGUIS:.cxx=.o)

QTGUIDEP        := $(QTGUIO:.o=.d) $(QTGUIDO:.o=.d)

QTGUICXXFLAGS   := -DQT3_SUPPORT -DQT_DLL -DQT_THREAD_SUPPORT -I. 
ifeq ($(ARCH),win32)
QTGUICXXFLAGS   += -I$(QTDIR)/mkspecs/win32-msvc2005
else
QTGUICXXFLAGS   += -I$(QTDIR)/mkspecs/default 
endif

QTGUICXXFLAGS   += $(QTINCDIR:%=-I%)
QTGUILIB        := $(LPATH)/libQtRootGui.$(SOEXT)
QTGUIMAP        := $(QTGUILIB:.$(SOEXT)=.rootmap)

# used in the main Makefile
ALLHDRS     += $(patsubst $(MODDIRI)/%.h,include/%.h,$(QTGUIH))
# ALLHDRS     += $(patsubst $(ROOTQTGUIDIRI)/Qt%, include/%, $(QTGUISOLUTIONH))
ALLMAPS     += $(QTGUIMAP)
ALLLIBS     += $(QTGUILIB)

# include all dependency files
INCLUDEFILES += $(QTGUIDEP)

##### local rules #####
include/%.h:    $(ROOTQTGUIDIRI)/%.h
		cp $< $@
		      
#include/Qt%.:    $(ROOTQTGUIDIRI)/Qt%.
#		cp $< $@
      
$(QTGUILIB):    $(QTGUIO) $(QTGUIDO) $(QTGUIMOCO)  $(ORDER_) $(MAINLIBS) $(QTGUILIBDEP)  $(QTGUISOLUTIONH)
		@$(MAKELIB) $(PLATFORM) $(LD) "$(LDFLAGS)" \
		   "$(SOFLAGS)" libQtRootGui.$(SOEXT) $@       \
		   "$(QTGUIO) $(QTGUIMOCO) $(QTGUIDO)"     \
		   "$(QTGUILIBEXTRA)" 

$(QTGUIDS):     $(QTGUIH1) $(QTGUIL) $(ROOTCINTTMPDEP)
		@echo "Generating dictionary $@..."
		$(ROOTCINTTMP) -f $@ -c $(QTGUIH1) $(QTGUIL)

$(QTGUIMAP):     $(RLIBMAP) $(MAKEFILEDEP) $(QTGUIL)
		$(RLIBMAP) -o $(QTGUIMAP) -l $(QTGUILIB) \
		   -d $(QTGUILIBDEPM) -c $(QTGUIL)

all-$(MODNAME):      $(QTGUILIB) $(QTGUIMAP)

clean-$(MODNAME):
		rm -f $(QTGUIO) $(QTGUIDO) $(QTGUIMOC) $(QTGUIMOCO)

clean::         clean-$(MODNAME)

show-$(MODNAME):
		@echo "QTGUIS     $(QTGUIS)"
		@echo "QTGUIO     $(QTGUIO)"
		@echo "QTGUIDO    $(QTGUIDO)" 
		@echo "QTGUIMOC   $(QTGUIMOC)" 
		@echo "QTGUIMOCO  $(QTGUIMOCO)"
		@echo .
		@echo "ROOTCINTTMPDEP  $(ROOTCINTTMPDEP)"
		@echo "ROOTCINTTMP  $(ROOTCINTTMP)"
		

distclean-$(MODNAME): clean-$(MODNAME) 
		@rm -f $(QTGUIDEP) $(QTGUIDS) $(QTGUIDH) $(QTGUILIB)

distclean::     distclean-$(MODNAME)

##### extra rules ######
$(sort $(QTGUIMOCO) $(QTGUIO)):  CXXFLAGS += $(GQTCXXFLAGS)
$(QTGUIDO):	 CXXFLAGS += $(GQTCXXFLAGS)

$(QTGUIMOC) : $(ROOTQTGUIDIRS)/moc_%.cxx: $(ROOTQTGUIDIRI)/%.h
ifeq (,$(QT4))
	$(QTMOCEXE)  $< -o $@
else
	$(QTMOCEXE)  $(QTGUICXXFLAGS) $< -o $@
endif
