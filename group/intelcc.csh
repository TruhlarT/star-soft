#!/usr/bin/csh -f

if ( -d /usr/intel ) then
    set seticc=`find /usr/intel -type f -name iccvars.csh | tail -1`
    set setifc=`find /usr/intel -type f -name ifcvars.csh | tail -1`
    if ( "$seticc" != "") source $seticc
    if ( "$setifc" != "") source $setifc
endif    
