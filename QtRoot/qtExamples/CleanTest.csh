#!/bin/tcsh
@echo Cleaning the Qt/Root examples: 
@echo ------------------------
@echo.

alias del rm 
alias nmake make 

nmake distclean

cd CustomCanvasMenu
nmake distclean
del Makefile
cd ..

cd CustomWidgets
nmake distclean
del Makefile
cd ..

cd ex1
nmake distclean
del Makefile
cd ..

cd HelloCanvas 
nmake distclean
del Makefile
cd ..

cd HelloCint
nmake distclean
del Makefile
cd ..

cd HelloWord
nmake distclean
del Makefile
cd ..

cd HelloLife
nmake distclean
del Makefile
cd ..

cd QtGBrowser
nmake distclean
del Makefile
cd ..

del Makefile

@echo ---------  Cleaning  has been finished ------------------

@echo -- Recreate the examples:

qmake
nmake

@echo Execute the examples:
@echo -----------------

cd CustomCanvasMenu
echo ----------- CustomCanvasMenu  -------------
CustomCanvasMenu
cd ..

cd CustomWidgets
echo -----------   CustomWidgets   -------------
CustomWidgets
cd ..

cd ex1
echo -----------        ex1        -------------
tqrootexample
cd ..

cd HelloCanvas 
echo -----------   HelloCanvas     -------------
HelloCanvas
cd ..

cd HelloCint
echo -----------     HelloCint     -------------
root.exe HelloCint.C
cd ..

cd HelloWord
echo -----------     HelloWord     -------------
HelloWord
cd ..

cd HelloLife
echo -----------     HelloLife     -------------
HelloLife
cd ..

cd HelloPixmap
echo -----------     HelloPixmap     -------------
HelloPixmap
cd ..

cd QtGBrowser
echo -----------  Geometry Browser -------------
GeomBrowser starcomplete.root
cd ..

cd HelloZoomPad
echo -----------  HelloZoomPad -------------
root.exe -q -l %ROOTSYS%\tutorials\hsimple.C
root.exe h1draw_zoom.C
cd ..

echo All example has been performed !!!


