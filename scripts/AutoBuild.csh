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

	# The extra sed is because Solaris does not like the brakets
	# in the string, although we doubel quote it.
	set TEST=`tokens | grep afs@rhic | sed "s/\[.*//"`
	if( "$TEST" == "") then
	    if ( ! -e /tmp/AutoBuild.info) then
		date >/tmp/AutoBuild.info
	    endif
	    echo "There is no token on `hostname` for `whoami`" >>/tmp/AutoBuild.info
	    tokens >>/tmp/AutoBuild.info
	    cat /tmp/AutoBuild.info | mail jeromel@bnl.gov
	else
	    # Check presence of a log directory
	    if( ! -d $HOME/log) then
		mkdir $HOME/log
	    endif

	    # Small global usage variable
	    set DAY=`date | sed "s/ .*//"`

	    setenv SILENT 1
	    staradev
	    unset noclobber

	    switch ("$1")
	    case "Clean":
		cd $STAR
		mgr/CleanLibs | grep Delete  >$HOME/log/CleanLibs.log
		breaksw

	    case "Insure":
		cd $STAR
		$SCRIPTD/insbld.pl -c -s >$HOME/log/IN-$DAY.log
		mgr/CleanLibs IOBJ 1
		breaksw


	    # ***** THOSE BLOCKS ARE TEMPORARY *****
	    # Commands uses whatever is found in 'adev' and compiles
	    case "Solaris":
		set LPATH=/afs/rhic/star/packages/adev
		set SPATH=/afs/rhic/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -k -i -1 -t -p $LPATH
		if( -e $HOME/AutoBuild-solaris.html) then
		    mv -f $HOME/AutoBuild-solaris.html $SPATH/AutoBuild-solaris.html
		endif
		cd $LPATH
		# Clean this garbage
		echo "Cleaning up C++ demangling cache"
		/usr/bin/find . -type d -name SunWS_cache -exec rm -fr {} \;
		echo "Cleaning older libraries"
		mgr/CleanLibs
		breaksw

	    case "Linux72":
		set LPATH=/afs/rhic/star/packages/adev
		set SPATH=/afs/rhic/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -k -i -1 -t -p $LPATH
		if( -e $HOME/AutoBuild-linux.html) then
		    mv -f $HOME/AutoBuild-linux.html $SPATH/AutoBuild-linux72.html
		endif
		cd $LPATH
		echo "Cleaning older libraries"
		mgr/CleanLibs obj 1
		breaksw



		# ****** This is the default action *****
	    default
		# Is update mode, not checkout
		$SCRIPTD/AutoBuild.pl -u >$HOME/log/AB-$DAY.log
	    endsw
	endif
endif
