#!/bin/csh -f

set pathtointel = `ls -1d /usr/intel* | tail -1`
if ( "$pathtointel" != "") then
    set seticc=`find $pathtointel -type f -name iccvars.csh | tail -1`
    set setifc=`find $pathtointel -type f -name ifcvars.csh | tail -1`
    set setifort=`find $pathtointel -type f -name ifortvars.csh | tail -1`
    if ( -x $GROUP_DIR/dropit ) then
	setenv PATH            `$GROUP_DIR/dropit intel`
	setenv LD_LIBRARY_PATH `$GROUP_DIR/dropit -p $LD_LIBRARY_PATH intel`
	setenv MANPATH         `$GROUP_DIR/dropit -p $MANPATH intel`
    endif
    if ( "$seticc" != "") source $seticc
    if ( "$setifc" != "") source $setifc
    if ( "$setifort" != "") source $setifort
endif

