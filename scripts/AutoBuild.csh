#!/bin/csh
#
# Wrapper to autobuild
# J.Lauret 2001.
#

# Path where to find the damned scripts.
set SCRIPTD=/afs/rhic/star/packages/scripts

# Loading of the star environment etc ...
setenv GROUP_DIR /afs/rhic/rhstar/group
if ( -r  $GROUP_DIR/star_login.csh ) then
	source $GROUP_DIR/star_login.csh 

	set TEST=`tokens | grep afs@rhic`
	if( "$TEST" == "") then
	    echo "There is no token on `hostname` for `whoami`"
	else
	    # Check presence of a log directory
	    if( ! -d $HOME/log) then
		mkdir $HOME/log
	    endif

	    # Small global usage variable
	    set DAY=`date | sed "s/ .*//"`

	    setenv SILENT 1
	    staradev

	    switch ("$1")
	    case "Clean":
		cd $STAR
		foreach file (tca.map .inslog2 .psrc .ix* $HOME/log/CleanLibs.log)
		    test -e $file && rm -f $file
		end
		mgr/CleanLibs | grep Delete  >$HOME/log/CleanLibs.log
		breaksw

	    case "Insure":
		cd $STAR
		if (-e $HOME/log/IN-$DAY.log) then
		    rm -f $HOME/log/IN-$DAY.log
		endif
		$SCRIPTD/insbld.pl -c -s >$HOME/log/IN-$DAY.log
		breaksw
		
	    default
		if (-e $HOME/log/AB-$DAY.log) then
		    rm -f $HOME/log/AB-$DAY.log
		endif
		$SCRIPTD/AutoBuild.pl -u >$HOME/log/AB-$DAY.log
	    endsw
	endif
endif
