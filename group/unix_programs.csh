#!/bin/csh
# Find and set a few unix program

if ( ! $?AWK ) then
    set AWK  = "echo"
    if (-x /bin/awk) then
	set AWK = "/bin/awk"
    else
	if (-x /usr/bin/awk) then
	    set AWK = "/usr/bin/awk"
	endif
    endif
endif
