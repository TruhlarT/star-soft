#!/bin/sh

# CoinInstallDir 
srcdir=`pwd`
platform=$STAR_HOST_SYS

if test "x$platform" = "x" ; then
   platform=`uname`
fi 

packageName=$platform/coin3d

cd ..
builddirbase=`pwd`/buildDir
installDir=$1
if test ! $installDir;  then
  echo "** Error ** missing installDir. Please specify!"
  echo ""
  echo "cd to the directory where \"cvs co\" has been performed"
  echo ""
  echo "Usage: install installDir"
  echo "-----"
  exit 1
fi

if !(test -d "$installDir"); then
  echo "** Warning ** \"$installDir\" does not exist. Create it!"
  if !(mkdir -p $installDir); then
     exit 1
  fi
fi

if !(test -d "$builddirbase"); then
  echo "** Warning ** \"$builddirbase\" does not exist. Create it!"
  if !(mkdir -p $builddirbase); then
     exit 1
  fi
fi

installDir=`pwd`/$installDir/$packageName
echo "Coin package will be installed in to the \"$installDir\" directory from $srcdir"
builddir=$builddirbase/${packageName}

cd $srcdir
if test -d Coin-2; then 
 
 # define Windows option if any
 testPlatform=`uname | grep -c CYGWIN`
 if test "x$testPlatform" = "x1" ; then
 msvcrt=--with-msvcrt=multithread-dynamic 
 fi
 

 cd $builddirbase
 mkdir -p ${packageName}
 cd ${packageName}
  mkdir simage-1
  mkdir Coin-2
  mkdir SmallChange
  mkdir SoQt
  mkdir SoGuiExamples-SoQt
 cd ../..
 pwd
 echo " Configure simage $builddir/simage-1"
 cd $builddir/simage-1
  $srcdir/simage/configure  --prefix=$installDir  ${msvcrt}  --enable-qimage  --enable-optimization=yes  --enable-debug  --with-qt=true --with-mpeg2enc --with-avienc --enable-threadsafe
  make install
 
 cd $builddir/Coin-2
 echo " Configure Coin3d  at `pwd`"
 pwd

  $srcdir/Coin-2/configure  --prefix=$installDir  ${msvcrt}  --enable-optimization=yes  --enable-debug --enable-threadsafe
  make install

 cd $builddir/SmallChange
 echo " Configure Coin3d  at `pwd`"
 pwd

  $srcdir/SmallChange/configure  --prefix=$installDir  ${msvcrt}  --enable-optimization=yes  --enable-debug --enable-threadsafe
  make install
  
 echo " Configure SoQt"
 cd $builddir/SoQt
   $srcdir/SoQt/configure  --prefix=$installDir  ${msvcrt}  --with-coin   --with-qt=true  --enable-debug --enable-threadsafe
    make install
  
  if test "x$testPlatform" = "x0" ; then
    # non Windows 
   echo " Configure SoXt"
   echo " Do NOT build SoXt!!!  It may confuse the ROOT configure utility!!!"

  # cd $builddir/SoXt
  #   $srcdir/SoXt/configure  --prefix=$installDir --with-coin --enable-debug --enable-threadsafe
  #    make install
  fi

  export PATH=$installDir/bin:$PATH
  cd $builddir/SoGuiExamples-SoQt
  $srcdir/SoGuiExamples/configure --with-soqt ${msvcrt} --enable-threadsafe
  make
  echo "---- Installation of Coin3D package has been completed"
  echo " Do not forget to set the env variable "
  echo "export IVROOT=$installDir"
else
  echo "** Error **  There is no Coin-2 src directory yet. Check Coin2 package out from \":pserver:cvs@cvs.coin3d.org:/export/cvsroot\" "
fi
  
