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
		

		# ***** THIS BLOCK IS TEMPORARY *****
	    case "Solaris":
		# Solaris one pass only
		set LPATH=/afs/rhic/star/packages/adev
		set SPATH=/afs/rhic/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -f -k -i -1 -t -p $LPATH 
		if( -e $HOME/AutoBuild-solaris.html) then
		    mv -f $HOME/AutoBuild-solaris.html $SPATH/AutoBuild-solaris.html
		endif
		cd $LPATH
		# Clean this garbage
		/usr/bin/find . -type d -name SunWS_cache -exec rm -fr {} \;
		breaksw

	    case "Gcc":
		set LPATH=/star/u/jeromel/work/STAR/GCC
		set SPATH=/afs/rhic/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -f -k -p $LPATH -v dev -1 -c >$HOME/log/AB-$DAY.log
		if( -e $HOME/AutoBuild.html) then
		    mv -f $HOME/AutoBuild.html $SPATH/AutoBuild-gcc.html
		endif
		/usr/bin/find $LPATH -name '*.so*' -exec rm -f {} \; >&/dev/null
		breaksw



		# ****** This is the default action *****
	    default
		# Is update mode, not checkout
		if (-e $HOME/log/AB-$DAY.log) then
		    rm -f $HOME/log/AB-$DAY.log
		endif
		$SCRIPTD/AutoBuild.pl -u >$HOME/log/AB-$DAY.log
	    endsw
	endif
endif
