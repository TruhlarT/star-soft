#!/bin/sh
#-------------------------------------------------------
# Author: Valeri Fine (fine@bnl.gov)       2007/05/16
# $Id: install.csh,v 1.2 2007/05/16 18:03:46 fine Exp $
#-------------------------------------------------------
QT_VERSION=4.3.0beta
QTSDK=qt-x11-opensource-src-${QT_VERSION}
# --
# -- download the Qt4 kit
# 
if ! test -s ${QTSDK} 
then
  if ! test -s ${QTSDK}.tar.gz
  then
    echo 1. -- downloading the distribution kit --- 
    wget ftp://ftp.trolltech.com/qt/source/${QTSDK}.tar.gz
  fi
# --
# -- upack the Qt4 kit
# 
  if  ! test -s ${QTSDK} 
  then
   echo 2. -- unzipping the distribution kit --- 
   tar -xzf ${QTSDK}.tar.gz
   rm ${QTSDK}.tar.gz
  fi
fi
# --
# -- configure the Qt4 to be installed under .$STAR_HOST_SYS/qt4
# 
if  test -s ${QTSDK} 
then
  cd ${QTSDK}
  echo 3. configure the Qt4 to be installed under .$STAR_HOST_SYS/qt4 from `pwd`
  ./configure -prefix .$STAR_HOST_SYS/${QT_VERSION}/debug -debug
# --
# -- build the Qt4 from `pwd`
#
make -j2 && make install 
else
  echo No Qt SDK ${QTSDK} has been found yet
  exit 1
fi


