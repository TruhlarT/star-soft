#!/bin/csh
#
# Wrapper to autobuild
# J.Lauret 2001.
#
# Current target for this script
#
#  Linux61
#  Linux72    build a Linux61 AutoBuild report (one version)
#  Linux9     
#
#  Solaris    ditto for Solaris (does cache cleaning)
#  du         Digital Unix using hack space in 'cal' (dev only)
#
#  Clean      Runs CleanLibs
#  Insure     Builds Insure++ compilation
#  
#
#
#

# Grab it from env
if ( ! $?AFS_RHIC ) setenv AFS_RHIC /afs/rhic

# In case of token failure, send an Email to
set EMAIL="jeromel@bnl.gov,didenko@bnl.gov"

# Path where to find the damned scripts.
set SCRIPTD=$AFS_RHIC/star/packages/scripts

# Loading of the star environment etc ...
setenv GROUP_DIR $AFS_RHIC/rhstar/group
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
	    cat /tmp/AutoBuild.info | mail -s "Token on `hostname`" $EMAIL
	else
	    # Check presence of a log directory
	    if( ! -d $HOME/log) then
		mkdir $HOME/log
	    endif

	    # Small global usage variable
	    set DAY=`date | sed "s/ .*//"`

	    setenv SILENT 1
	    if ($?INSURE) unsetenv INSURE
	    staradev
	    unset noclobber

	    switch ("$1")
	    case "Clean":
		cd $STAR
		mgr/CleanLibs obj 2 | grep Delete  >$HOME/log/CleanLibs.log
		mgr/CleanLibs OBJ 2 | grep Delete  >$HOME/log/CleanLibs.log
		breaksw

	    case "Insure":
		cd $STAR
		$SCRIPTD/insbld.pl -c -s >$HOME/log/IN-$DAY.log
		mgr/CleanLibs IOBJ 1
		breaksw


	    # ***** THOSE BLOCKS ARE TEMPORARY *****
	    # Commands uses whatever is found in 'adev' and compiles
	    case "du":
		set LPATH=$AFS_RHIC/star/packages/cal
		set SPATH=$AFS_RHIC/star/doc/www/comp/prod/Sanity
		perl $SCRIPTD/AutoBuild.pl -k -i -1 -t -p $LPATH	    
		if( -e $HOME/AutoBuild-dec_osf.html) then
		    mv -f $HOME/AutoBuild-dec_osf.html $SPATH/AutoBuild-dec_osf.html
		endif
		cd $LPATH
		echo "Cleaning older libraries"
		mgr/CleanLibs obj 1
		breaksw

	    case "Solaris":
		set LPATH=$AFS_RHIC/star/packages/adev
		set SPATH=$AFS_RHIC/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -k -i -1 -t -p $LPATH
		if( -e $HOME/AutoBuild-solaris.html) then
		    mv -f $HOME/AutoBuild-solaris.html $SPATH/AutoBuild-solaris.html
		endif
		cd $LPATH
		# Clean this garbage
		echo "Cleaning up C++ demangling cache"
		/usr/bin/find . -type d -name SunWS_cache -exec rm -fr {} \;
		echo "Cleaning older libraries"
		mgr/CleanLibs obj 1
		breaksw

	    case "Linux61":
	    case "Linux72":
	    case "Linux9":
		set LPATH=$AFS_RHIC/star/packages/adev
		set SPATH=$AFS_RHIC/star/doc/www/comp/prod/Sanity
		$SCRIPTD/AutoBuild.pl -k -i -1 -t -p $LPATH
		if( -e $HOME/AutoBuild-linux.html) then
		    mv -f $HOME/AutoBuild-linux.html $SPATH/AutoBuild-$1.html
		endif
		cd $LPATH
		echo "Cleaning older libraries"
		mgr/CleanLibs obj 1
		echo "Cleaning emacs flc files"
		/usr/bin/find StRoot/ -name '*.flc' -exec rm -f {} \;
		breaksw



		# ****** This is the default action *****
	    default
		# Is update mode, not checkout
		$SCRIPTD/AutoBuild.pl -u >$HOME/log/AB-$DAY.log
	    endsw
	endif
endif
