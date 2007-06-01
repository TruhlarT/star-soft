#!/bin/sh
#-------------------------------------------------------
# Author: Valeri Fine (fine@bnl.gov)       2007/05/16
# $Id: install.csh,v 1.7 2007/06/01 14:59:38 fine Exp $
#-------------------------------------------------------
QT_VERSION=4.3.0
QTSDK=qt-x11-opensource-src-${QT_VERSION}
# QTSDK=qt-x11-commercial-src-${QT_VERSION}
# --
# -- download the Qt4 kit
# 
if ! test -s ${QTSDK} 
then
  if ! test -s ${QTSDK}.tar.gz
  then
    echo 1. -- downloading the distribution kit --- 
    wget  --quiet ftp://ftp.trolltech.com/qt/source/${QTSDK}.tar.gz
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
  echo Attn. the Qt4 -debug option creates both the debug as well as non-debug versions of the Qt4 binaries
  ./configure -prefix-install -prefix .$STAR_HOST_SYS/${QT_VERSION}/debug -debug  -no-openssl <<YES
yes
YES
# --
# -- build the Qt4 from `pwd`
#
make && make install 
else
  echo No Qt SDK ${QTSDK} has been found yet
  exit 1
fi


