# Create the Qt4 aware version of qtRoot package
# $Id: QtRootQt3to4.csh,v 1.2 2006/09/22 17:27:10 fine Exp $
qt3to4 -rulesFile $QTDIR/q3porting.xml  qtgui.pro
rm -rf qt4
mkdir -p qt4/src
mkdir -p qt4/inc
foreach f ( src/*.cxx   inc/*.h )
echo qt4/$f

# Check against of CVS after conversion
cvs diff --ifdef=QT_VERSION $f | sed -e  "1,5d" | sed -e "s/ndef QT_VERSION/ QT_VERSION < 0x40000/g" |  sed -e "s/ifdef QT_VERSION/if QT_VERSION >= 0x40000/g"  >qt4/$f 

# Copy the files with no corrections
if (!( -s qt4/$f))  then
echo "        File $f was not changed."
   cp $f qt4/$f
endif
end
cp qtgui.pro qt4
cd qt4
qmake CONFIG+=debug
make
