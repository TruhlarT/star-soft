#!/bin/sh
echo "Prepare Coin3D directory tree:"

mkdir Coin2
cd Coin2
mkdir srcDir
mkdir buildDir
cd srcDir

echo "Check Out Coin3D components from the CVS repository:"
echo "See: http://www.coin3d.org/doc/cvs_access"

export COINCVSROOT=:pserver:cvs@cvs.coin3d.org:/export/cvsroot
cvs login
# "Coin" - Latest development version
# cvs -z3 -d $COINCVSROOT checkout Coin

# "Coin-2" - Last stable production release
cvs -z3 -d $COINCVSROOT checkout Coin-2

cvs -z3 -d $COINCVSROOT checkout SmallChange
cvs -z3 -d $COINCVSROOT checkout simage
cvs -z3 -d $COINCVSROOT checkout simacros
cvs -z3 -d $COINCVSROOT checkout SoQt
testPlatform=`uname | grep -c CYGWIN`
if test "x$testPlatform" = "x0" ; then
  cvs -z3 $COINCVSROOT checkout SoXt
fi

cvs -z3 -d $COINCVSROOT checkout SoGuiExamples
