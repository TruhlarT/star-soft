#!/bin/csh -f

set pathtointel = `ls -1d /usr/intel* | /usr/bin/tail -1`
if ( "$pathtointel" != "") then
    set seticc=`/usr/bin/find $pathtointel -type f   -name iccvars.csh | /usr/bin/tail -1`
    set setifc=`/usr/bin/find $pathtointel -type f -name ifcvars.csh | /usr/bin/tail -1`
    set setifort=`/usr/bin/find $pathtointel -type f -name ifortvars.csh | /usr/bin/tail -1`
    set setidb=`/usr/bin/find $pathtointel -type f -name idbvars.csh | /usr/bin/tail -1`
    if ( -x $GROUP_DIR/dropit ) then
	setenv PATH            `$GROUP_DIR/dropit intel`
	setenv LD_LIBRARY_PATH `$GROUP_DIR/dropit -p $LD_LIBRARY_PATH intel`
	setenv MANPATH         `$GROUP_DIR/dropit -p $MANPATH intel`
    endif
    if ( "$seticc" != "") source $seticc
    if ( "$setifc" != "") source $setifc
    if ( "$setifort" != "") source $setifort
    if ( "$setidb" != "") source $setidb
endif
