#!/bin/csh
#
# Wrapper to autobuild
# J.Lauret 2001.
#
# Current target for this script
#
# Linux based targets:
#   Linux61
#   Linux72    build a LinuxXX AutoBuild report (one version)
#   Linux9     
#
#   Insure     Builds Insure++ compilation
#   icc        Builds with icc
#   inter      Builds as per the default target but do not perform
#              post compilation tasks (and do not send Email if 
#              failure)
#
# Targets for Other platforms:
#   Solaris    Ditto for Solaris (does cache cleaning)
#   du         Digital Unix using hack space in 'cal' (dev only)
#
# Miscellaneous targets
#   Clean      Runs CleanLibs under the current OS and keeps 2
#              versions.
#  
#
# Default is to run on the current platform both optimized and
# non optimized. The
#
#

# Grab it from env
if ( ! $?AFS_RHIC ) setenv AFS_RHIC /afs/rhic.bnl.gov

# In case of token failure, send an Email to
set EMAIL="jeromel@bnl.gov,didenko@bnl.gov"

# Path where to find the damned scripts.
set SCRIPTD=$AFS_RHIC/star/packages/scripts

# Loading of the star environment etc ...
setenv GROUP_DIR $AFS_RHIC/star/group
if ( -r  $GROUP_DIR/star_login.csh ) then
	source $GROUP_DIR/star_login.csh

	# The extra sed is because Solaris does not like the brakets
	# in the string, although we doubel quote it.
	if ( -e $HOME/bin/token.csh) then
	    $HOME/bin/token.csh
	    set STATUS=$status
	else
	    set STATUS=1
	endif

	if ($STATUS != 0) then
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
	    if ($?INSURE)  unsetenv INSURE
	    if ($?NODEBUG) unsetenv NODEBUG
	    staradev
	    unset noclobber

	    switch ("$1")
	    case "Clean":
		cd $STAR
		mgr/CleanLibs obj 2 | grep Delete  >$HOME/log/CleanLibs.log
		mgr/CleanLibs OBJ 2 | grep Delete  >$HOME/log/CleanLibs.log
		breaksw

	    case "Insure":
		starver .IDEV
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


	    case "icc":
		set LPATH=$AFS_RHIC/star/packages/adev
		set SPATH=$AFS_RHIC/star/doc/www/comp/prod/Sanity

		# this is only for double checking. AutoBuild.pl is
		# impermeable to external env changes (start a new process)
		# so modifications has to be passed at command line level
		echo "Testing setup icc "
		setup icc
		set test=`which icc`
		set sts=$status
		if ( $sts == 0 ) then
		    echo "icc is $test ; starting AutoBuild"
		    $SCRIPTD/AutoBuild.pl -k -i -1 -t -T icc -p $LPATH -a 'setup icc' >$HOME/log/AB-icc-$DAY.log 
		    if( -e $HOME/AutoBuild-linux-icc.html) then
			mv -f $HOME/AutoBuild-linux-icc.html $SPATH/AutoBuild-$1.html
		    endif
		    cd $LPATH
		    echo "Cleaning older libraries"
		    mgr/CleanLibs obj 1
		else
		    echo "Test returned status $sts"
		endif
		echo "Reverting to gcc setup"
		setup gcc
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
	    case "inter":
		# Is update mode, not checkout
		$SCRIPTD/AutoBuild.pl -u -s >$HOME/log/AB-d-$DAY.log
		breaksw
	    default
		# Is update mode, not checkout
		$SCRIPTD/AutoBuild.pl -u >$HOME/log/AB-$DAY.log
	    endsw
	endif
endif
