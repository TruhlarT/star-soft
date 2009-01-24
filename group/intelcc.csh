#!/bin/csh -f

#
# Setup for Intel compiler 
# (c) J. Lauret 2003
#

set self="intelcc"

# get version as first argument
set vers=0
if ( $?1 ) then
    set vers=$1
    if ( $vers == "") set vers=0
endif


set pathtointel = `/bin/ls -1d /usr/intel* | /usr/bin/tail -1`
if ( $?DECHO ) then
   echo "$self :: Path found is [$pathtointel]"
endif




if ( "$pathtointel" != "") then
    # search for setup files and source later 
    if ( $vers == 0 ) then
       if ( $?DECHO ) then
          echo "$self :: No version specified, using the 'latest'"
       endif
       set seticc=`  /usr/bin/find $pathtointel -type f -name iccvars.csh   | /usr/bin/tail -1`
       set setifc=`  /usr/bin/find $pathtointel -type f -name ifcvars.csh   | /usr/bin/tail -1`
       set setifort=`/usr/bin/find $pathtointel -type f -name ifortvars.csh | /usr/bin/tail -1`
       set setidb=`  /usr/bin/find $pathtointel -type f -name idbvars.csh   | /usr/bin/tail -1`
    else
       if ( $?DECHO ) then
          echo "$self :: Version [$vers] specified, searching"
       endif
       set seticc=`  /usr/bin/find $pathtointel -type f -name iccvars.csh   | /bin/grep $vers`
       set setifc=`  /usr/bin/find $pathtointel -type f -name ifcvars.csh   | /bin/grep $1`
       set setifort=`/usr/bin/find $pathtointel -type f -name ifortvars.csh | /bin/grep $1`
       set setidb=`  /usr/bin/find $pathtointel -type f -name idbvars.csh   | /bin/grep $1`
    endif 
    if ( -x $GROUP_DIR/dropit ) then
	setenv PATH            `$GROUP_DIR/dropit intel`
	setenv LD_LIBRARY_PATH `$GROUP_DIR/dropit -p $LD_LIBRARY_PATH intel`
	setenv MANPATH         `$GROUP_DIR/dropit -p $MANPATH intel`
    endif
    if ( "$seticc"   != "") source $seticc
    if ( "$setifc"   != "") source $setifc
    if ( "$setifort" != "") source $setifort
    if ( "$setidb"   != "") source $setidb
endif
