#!/bin/csh -f
#       $Id: group_env.csh,v 1.155 2003/09/22 00:45:25 jeromel Exp $
#	Purpose:	STAR group csh setup
#
#	Author:		Y.Fisyak     BNL
#	Date:		27 Feb. 1998
#	Modified:
#     3 Mar 98  T. Wenaus  HP Jetprint added (for sol)
#     2 Apr 01  J. Lauret  Insure path added
#    24 Apr 01  J. Lauret  Disabled echoing in ! prompt.
#                          DO NOT MODIFY THIS !!!
#
#	STAR software group	1998
#
set ECHO = 1; 
if ($?STAR == 1)   set ECHO = 0
if ( ! $?prompt)   set ECHO = 0
if ($?SILENT == 1) set ECHO = 0


# This variable was added for the ECHOD debug mode
#set ECHO = 1
#set Self=`echo $0 | sed "s/.*\///g"`
#echo "$Self :: Receiving STAR_LEVEL $STAR_LEVEL"


setenv WWW_HOME http://www.star.bnl.gov/
if ($ECHO) echo   "Setting up WWW_HOME  = $WWW_HOME"

setenv AFS       /usr/afsws

if (! $?STAR_ROOT) then
    setenv STAR_ROOT ${AFS_RHIC}/star;
endif
if ($ECHO) then
  echo ""
  echo "         ----- STAR Group Login from $GROUP_DIR/ -----"
  echo ""
endif
if ($ECHO) echo   "Setting up STAR_ROOT = ${STAR_ROOT}"


# Define /opt/star
if ( ! $?OPTSTAR ) then
    if ( -e /opt/star ) then
	setenv OPTSTAR /opt/star
    else
	if ( -e ${AFS_RHIC}/opt/star ) then
	    setenv OPTSTAR ${AFS_RHIC}/opt/star
	endif
    endif
endif


    

# Defined by Group Dir
if ( ! $?GROUP_DIR )  setenv GROUP_DIR ${STAR_ROOT}/group
# Defined in CORE. GROUP_PATH/GROUPPATH are global
# while GROUP_DIR may be local
if ( ! $?GROUP_PATH ) setenv GROUP_PATH ${STAR_ROOT}/group
setenv GROUPPATH  $GROUP_PATH
if ($?STAR_PATH == 0) setenv STAR_PATH ${STAR_ROOT}/packages;
if ($ECHO) echo   "Setting up STAR_PATH = ${STAR_PATH}"


# Default value (some if not already defined)
if ($?STAR_LEVEL == 0) setenv STAR_LEVEL pro

setenv STAR_VERSION ${STAR_LEVEL}
if ($STAR_LEVEL  == "old" || $STAR_LEVEL  == "pro" || $STAR_LEVEL  == "new" || $STAR_LEVEL  == "dev" || $STAR_LEVEL  == ".dev") then
  # i.e. replace with link value instead
  if( -e $STAR_PATH/${STAR_LEVEL}) then
    # be carefull, it may not be "seen" as a soft link
    # at all ... Some AFS client do not show the link.
    # No even speaking of absolute path ...
    set a = `/bin/ls -ld $STAR_PATH/${STAR_LEVEL}`
    set b = `/bin/ls -ld $STAR_PATH/${STAR_LEVEL} |cut -f2 -d">"`
    if ( "$a" != "$b") then
	setenv STAR_VERSION $b
    else
	setenv STAR_VERSION $STAR_LEVEL
    endif
  endif
endif

if ($?STAF_LEVEL == 0) then
 if ( -e $STAR_PATH/StAF/${STAR_LEVEL}) then
    setenv STAF_LEVEL $STAR_LEVEL
 else
    setenv STAF_LEVEL pro
 endif
endif

setenv STAF_VERSION ${STAF_LEVEL}
if ($STAF_LEVEL  == "old" || $STAF_LEVEL  == "pro" || $STAF_LEVEL  == "new" || $STAF_LEVEL  == "dev" || $STAF_LEVEL  == ".dev") then
  if( -e $STAR_PATH/StAF/${STAF_LEVEL}) then
    set a = `/bin/ls -ld $STAR_PATH/StAF/${STAF_LEVEL}`
    set b = `/bin/ls -ld $STAR_PATH/StAF/${STAF_LEVEL} |cut -f2 -d">"`
    if ( "$a" != "$b") then
	setenv STAF_VERSION $b
    else
	setenv STAF_VERSION ${STAF_LEVEL}
    endif
  endif
endif




# Clear this out. First block STAF, second STAR
source ${GROUP_DIR}/STAR_SYS;

if ( ! $?optstar && $?OPTSTAR ) then
    setenv optstar ${OPTSTAR}
    if ( -e ${OPTSTAR}/${STAR_HOST_SYS} ) then
	# Redhat > 7.3  transition ; adding one level
	setenv OPTSTAR  ${optstar}/${STAR_HOST_SYS}
    endif
endif


# Display the messages here now
if (  $?OPTSTAR ) then
    if ($ECHO) echo   "Setting up OPTSTAR   = ${OPTSTAR}"
else
    if ($ECHO) echo   "WARNING : OPTSTAR undefined"
endif






# STAF
setenv STAF ${STAR_PATH}/StAF/${STAF_VERSION} ;   if ($ECHO) echo   "Setting up STAF      = ${STAF}"
setenv STAF_LIB  $STAF/.${STAR_HOST_SYS}/lib  ;   if ($ECHO) echo   "Setting up STAF_LIB  = ${STAF_LIB}"
setenv STAF_BIN  $STAF/.${STAR_HOST_SYS}/bin  ;   if ($ECHO) echo   "Setting up STAF_BIN  = ${STAF_BIN}"
# STAR
setenv STAR      $STAR_PATH/${STAR_VERSION}   ;   if ($ECHO) echo   "Setting up STAR      = ${STAR}"
setenv STAR_LIB  $STAR/.${STAR_HOST_SYS}/lib  ;   if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv MINE_LIB        .${STAR_HOST_SYS}/lib
setenv STAR_BIN  $STAR/.${STAR_HOST_SYS}/bin
setenv MY_BIN          .${STAR_HOST_SYS}/bin


# Options my alter *_BIN and/or add *_lib. All options should
# be treated here. Defaults hould be preserved above.
if ($?NODEBUG) then
  setenv STAR_lib  $STAR/.${STAR_HOST_SYS}/LIB ;  if ($ECHO) echo   "Setting up STAR_lib  = ${STAR_lib}"
  setenv MINE_lib        .${STAR_HOST_SYS}/LIB
  setenv STAR_BIN  $STAR/.${STAR_HOST_SYS}/BIN
  setenv MY_BIN          .${STAR_HOST_SYS}/BIN
else if ($?INSURE) then
  # Do it conditional because this is a late addition.
  # The directory structure may not exist for all library version.
  if( -e $STAR/.${STAR_HOST_SYS}/ILIB) then
   if (-f $GROUP_DIR/parasoftenv.csh) then
     source $GROUP_DIR/parasoftenv.csh
     setenv STAR_lib  $STAR/.${STAR_HOST_SYS}/ILIB ;  if ($ECHO) echo   "Setting up STAR_lib  = ${STAR_lib}"
     setenv MINE_lib        .${STAR_HOST_SYS}/ILIB
     setenv STAR_BIN  $STAR/.${STAR_HOST_SYS}/IBIN
     setenv MY_BIN          .${STAR_HOST_SYS}/IBIN
   else
     if ($ECHO) echo "Setting up STAR_lib  = Insure not found (not set)"
   endif
  else
   if ($ECHO) echo  "Setting up STAR_lib  = Cannot Set (missing tree)"
  endif
else
  if ($?STAR_lib) unsetenv STAR_lib
  if ($?MINE_lib) unsetenv MINE_lib
endif

if ($ECHO)    echo   "Setting up STAR_BIN  = ${STAR_BIN}"

# Common stuff
setenv STAR_SCRIPTS $STAR_PATH/scripts
setenv STAR_CGI  $STAR_PATH/cgi
setenv STAR_MGR  $STAR/mgr
setenv STAR_PAMS $STAR/pams;            if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"
setenv STAR_DATA ${STAR_ROOT}/data;     if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
setenv CVSROOT   $STAR_PATH/repository; if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"


if (-f $STAR/mgr/ROOT_LEVEL && -f $STAR/mgr/CERN_LEVEL) then
  setenv ROOT_LEVEL `cat $STAR/mgr/ROOT_LEVEL`
  setenv CERN_LEVEL `cat $STAR/mgr/CERN_LEVEL`
  if ( -f $STAR/mgr/CERN_LEVEL.${STAR_HOST_SYS} ) then
    # Overwrite
    setenv CERN_LEVEL `cat $STAR/mgr/CERN_LEVEL.${STAR_HOST_SYS}`
  endif
else
 switch ( $STAR_VERSION )

  case SL98l: 
    setenv ROOT_LEVEL 2.20
    breaksw

  case SL99a:
  case SL99b:
  case SL99c:
    setenv ROOT_LEVEL 2.21
    setenv CERN_LEVEL 99
    breaksw

  case SL99d:
  case SL99e:
    setenv ROOT_LEVEL 2.21.08
    setenv CERN_LEVEL 99
    breaksw

  case SL99f:
  case SL99g:
    setenv ROOT_LEVEL 2.22
    setenv CERN_LEVEL 99
    breaksw

  default: 
    setenv ROOT_LEVEL 3.02.00

  endsw
endif

setenv CERN_ROOT  $CERN/$CERN_LEVEL
if ($ECHO) echo   "Setting up ROOT_LEVEL= ${ROOT_LEVEL}"

if ( -x ${GROUP_DIR}/dropit) then
    setenv GROUPPATH `${GROUP_DIR}/dropit -p ${GROUP_DIR} -p mgr -p ${STAR_MGR} -p ${STAR_SCRIPTS} -p ${STAR_CGI} -p ${MY_BIN} -p ${STAR_BIN} -p ${STAF}/mgr -p ${STAF_BIN}`
    setenv PATH `${GROUP_DIR}/dropit -p ${OPTSTAR}/bin -p $PATH`
else
    setenv GROUPPATH ${GROUP_DIR}:mgr:${STAR_MGR}:${STAR_SCRIPTS}:${STAR_CGI}:${MY_BIN}:${STAR_BIN}:${STAF}/mgr:${STAF_BIN}
    setenv PATH  ${OPTSTAR}/bin:$PATH
endif


# ROOT
if ( -f $GROUP_DIR/rootenv.csh) then
  source $GROUP_DIR/rootenv.csh
endif

if ( -x ${GROUP_DIR}/dropit) then
  # clean-up PATH
  setenv MANPATH `${GROUP_DIR}/dropit -p ${OPTSTAR}/man -p ${MANPATH}`
  setenv PATH    `${GROUP_DIR}/dropit -p ${PATH} GROUPPATH`
  setenv PATH    `${GROUP_DIR}/dropit -p ${PATH} $STAR_PATH`
  if ($?LD_LIBRARY_PATH == 1) setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} $STAR_PATH`
  if ($?SHLIB_PATH == 1)      setenv SHLIB_PATH      `${GROUP_DIR}/dropit -p ${SHLIB_PATH} $STAR_PATH`
  setenv PATH `${GROUP_DIR}/dropit -p ${GROUPPATH} -p /usr/afsws/bin -p /usr/afsws/etc -p ${OPTSTAR}/bin -p /usr/sue/bin -p /usr/local/bin -p ${PATH}`
endif


## Put mysql on path if available
if ( -d /usr/local/mysql/bin) then
  if ( -x ${GROUP_DIR}/dropit) setenv PATH `${GROUP_DIR}/dropit -p ${PATH} -p /usr/local/mysql/bin`
endif

if ($?MANPATH == 1) then
  ##VP   setenv MANPATH ${MANPATH}:${STAR_PATH}/man
  setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p ${STAR_PATH}/man`
else
  setenv MANPATH ${STAR_PATH}/man
endif
  
   
switch ($STAR_SYS)
    case "rs_aix*":
        if ( -x ${GROUP_DIR}/dropit) setenv MANPATH `${GROUP_DIR}/dropit -p {$MANPATH} -p /usr/share/man`
        breaksw
    case "alpha_osf32c":
	breaksw
    case "hp700_ux90":
	breaksw

    case "hp_ux102":
      if ($?SHLIB_PATH == 0) setenv SHLIB_PATH
      if ( -x ${GROUP_DIR}/dropit) setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} $STAR_PATH`
      if ($?MINE_lib == 1 && $?STAR_lib == 1) then
        setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${MINE_lib} -p ${MINE_LIB} -p ${STAR_lib} -p ${STAR_LIB} -p ${STAF_LIB} -p ${SHLIB_PATH}`
      else
	if ( -x ${GROUP_DIR}/dropit) setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} .${STAR_HOST_SYS}/LIB`
##VP         setenv SHLIB_PATH ${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${SHLIB_PATH}
        setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${STAF_LIB} -p ${SHLIB_PATH}`
      endif
      setenv LD_LIBRARY_PATH ${SHLIB_PATH}
      setenv BFARCH hp_ux102
      limit  coredumpsize 0
      breaksw

    case "i386_*":
      #  ====================
      # make sure that afws in the path
      if (! -d /usr/afsws/bin) setenv PATH `${GROUP_DIR}/dropit -p $PATH -p ${AFS_RHIC}/i386_redhat50/usr/afsws/bin`
      if ( -d /usr/pgi ) then
       setenv PGI /usr/pgi
       setenv PATH `${GROUP_DIR}/dropit -p $PGI/linux86/bin -p $PATH`
##VP        setenv MANPATH "${MANPATH}:${PGI}/man"
       setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p ${PGI}/man`
       setenv LM_LICENSE_FILE $PGI/license.dat
       alias pgman 'man -M $PGI/man'
      endif
      if (-d /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE) then
       setenv KAI /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE
       setenv PATH `${GROUP_DIR}/dropit -p $KAI/bin -p $PATH`

      endif
      setenv PATH  `${GROUP_DIR}/dropit -p $PATH  -p /usr/local/bin/ddd`
      if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH
      if ($?MINE_lib == 1 && $?STAR_lib == 1) then
       setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_lib} -p ${MINE_LIB} -p ${STAR_lib} -p ${STAR_LIB} -p ${STAF_LIB} -p ${LD_LIBRARY_PATH}`
      else
       if ( -x ${GROUP_DIR}/dropit) setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} .${STAR_HOST_SYS}/LIB`
       setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${STAF_LIB} -p ${LD_LIBRARY_PATH}`
      endif

      #  cygwin tcsh has no 'limit' command embedded
      if ( `echo $STAR_SYS | grep _nt` == "") then
	limit  coredump 0
	setenv BFARCH Linux2
      endif
      breaksw

    case "sun4*":
      #  ====================
      # Sun/Solaris version 4
      #  ====================
      if ( ! $?SUNWS ) then
	if ( -r $STAR_MGR/sunWS ) then
	    setenv SUNWS `cat $STAR_MGR/sunWS`
	    if ( ! -d /opt/$SUNWS ) then
		if ($ECHO) echo "$SUNWS Workshop not found. Reverting to SUNWspro"
		setenv SUNWS "SUNWspro"
	    endif
        else
	    # default packages distribution directory
	    setenv SUNWS "SUNWspro"
	endif
      endif

      if (! $?SUNOPT) setenv SUNOPT /opt

      set WSVERS=`echo $SUNWS  | sed "s/WS//"`   # full version number
      set WSMVER=`echo $WSVERS | sed "s/\..*//"` # major version number

      if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH
      setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p /usr/openwin/lib -p /usr/dt/lib -p /usr/local/lib -p ${LD_LIBRARY_PATH}`


      # Rebuild path - Basic
      if ( -x ${GROUP_DIR}/dropit) then
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p $SUNOPT/$SUNWS/lib -p $SUNOPT/$SUNWS/SC$WSVERS/lib -p $SUNOPT/$SUNWS/WS$WSMVER/lib`
	setenv PATH `${GROUP_DIR}/dropit -p $SUNOPT/$SUNWS/bin -p ${PATH}`
	setenv MANPATH `${GROUP_DIR}/dropit -p $SUNOPT/$SUNWS/man -p ${MANPATH}`

	if ($?MINE_lib == 1 && $?STAR_lib == 1 ) then
	    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_lib} -p ${MINE_LIB} -p ${STAR_lib} -p ${STAR_LIB} -p ${STAF_LIB} -p ${LD_LIBRARY_PATH}`
        else
	    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${STAF_LIB} -p ${LD_LIBRARY_PATH}`
        endif
      endif

      setenv  BFARCH SunOS5
      if ("${STAR_HOST_SYS}" == "sun4x_56_CC5") setenv BFARCH SunOS5_CC5
      limit   coredump 0
      unlimit descriptors
      breaksw

    default:
	#  ====================
	breaksw
endsw


# ==================================================================
# Extra package support
# ==================================================================

# Support for LSF
if ( -d /usr/local/lsf/bin && ! $?LSF_ENVDIR ) then
    if ( -e /etc/profile.d/lsfsetup.csh ) then
	source /etc/profile.d/lsfsetup.csh
    else
	setenv LSF_DIR    /usr/local/lsf
	setenv LSF_ENVDIR $LSF_DIR/mnt/conf
	set path=($path $LSF_DIR/bin)
	setenv MANPATH ${MANPATH}:$LSF_DIR/mnt/man
    endif
endif


# Support for JAVA/JDK
if ( ! $?JAVA_ROOT ) then
    # Search for a default path
    if ( -d /usr/java ) then
	set a = `/bin/ls /usr/java | tail -1`
	if ( "$a" != "") then
	    setenv JAVA_ROOT /usr/java/$a
	endif
    endif
endif
if ( $?JAVA_ROOT ) then
    if ( -d $JAVA_ROOT/ ) then
	set path=($path $JAVA_ROOT/bin)
	setenv MANPATH ${MANPATH}:$JAVA_ROOT/man
	#CLASSPATH anyone ??
    endif
endif


# Support for Insure++
if ( ! $?INSV ) then
    setenv INSV insure-6.1-gcc-3.2
endif
if ( -d ${AFS_RHIC}/app/${INSV} ) then
    set VER=`/bin/ls -ld ${AFS_RHIC}/app/${INSV}/bin* | sed "s/.*\.//"`
    if ("$VER" != "") set VER=".$VER"
    set path=($path ${AFS_RHIC}/app/${INSV}/bin$VER)
    setenv LD_LIBRARY_PATH  ${LD_LIBRARY_PATH}:${AFS_RHIC}/app/${INSV}/lib$VER
    unset VER
endif


# Support for Qt
if ( -d $OPTSTAR/qt ) then
    setenv QTDIR $OPTSTAR/qt
    set path=($path $QTDIR/bin)
    setenv MANPATH ${MANPATH}:$QTDIR/man
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$QTDIR/lib
endif




# ==================================================================
# END 
# ==================================================================



# We need this aliases even during BATCH
if (-r $GROUP_DIR/group_aliases.csh) source $GROUP_DIR/group_aliases.csh
# Scratch space ...
if ($?SCRATCH == 0) then
    setenv SCRATCH /tmp/$LOGNAME
endif


# User Scratch directory
if ( ! -d $SCRATCH ) then
    mkdir $SCRATCH
    chmod 755 $SCRATCH
endif
if ($ECHO) echo   "Setting up SCRATCH   = $SCRATCH"


# Echo CERN level information
if ($?CERN_ROOT == 1 ) then
    if ($ECHO) echo   "CERNLIB version "$CERN_LEVEL" has been initiated with CERN_ROOT="${CERN_ROOT}
endif

# CLHEP library support
if (! $?CLHEP_BASE_DIR ) then
    setenv CLHEP_BASE_DIR ${OPTSTAR}
endif


# HP Jetprint
if ( -d /opt/hpnp ) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH `${GROUP_DIR}/dropit -p $MANPATH -p /opt/hpnp/man`
  setenv PATH    `${GROUP_DIR}/dropit -p $PATH  -p /opt/hpnp/bin -p /opt/hpnp/admin`
endif
setenv PATH `${GROUP_DIR}/dropit -p $HOME/bin -p $HOME/bin/.$STAR_HOST_SYS -p $PATH -p $CERN_ROOT/bin -p $CERN_ROOT/mgr .`


# clean-up PATH
if ( -x ${GROUP_DIR}/dropit) then
    if ("$CERN_LEVEL" != "pro") then
	setenv PATH  `${GROUP_DIR}/dropit cern`
	setenv PATH `${GROUP_DIR}/dropit -p ${PATH} -p ${CERN_ROOT}/bin`
    endif
    setenv PATH `${GROUP_DIR}/dropit -p ${OPTSTAR}/bin -p ${PATH}`
    switch ($STAR_SYS)
	case "hp_ux102":
	#  ====================
	setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} -p ${OPTSTAR}/lib`
	if ( -d ${OPTSTAR}/lib/mysql ) then
	    setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} -p ${OPTSTAR}/lib/mysql`
	endif
	setenv SHLIB_PATH `${GROUP_DIR}/dropit -p "$SHLIB_PATH"`
	breaksw

    default:
	#  ====================
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p ${OPTSTAR}/lib`
	if ( -d ${OPTSTAR}/lib/mysql ) then
	    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p ${OPTSTAR}/lib/mysql`
	endif
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "$LD_LIBRARY_PATH"`
	breaksw
    endsw
    setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH}`
    setenv PATH `${GROUP_DIR}/dropit -p ${PATH} GROUPPATH`
endif

if ($ECHO) then
    echo "STAR setup on" `hostname` "by" `date` " has been completed"
    echo   "LD_LIBRARY_PATH = $LD_LIBRARY_PATH"
    unset ECHO
endif

#
# Uncomment to get statistics on version used at
# login level. 
#
#set date="`date`"
#cat >> $GROUP_DIR/statistics/star${STAR_VERSION} << EOD
#$USER from $HOST asked for STAR_LEVEL=$STAR_LEVEL / STAR_VERSION=$STAR_VERSION  $date
#EOD
#END


#echo "$STAR"
#echo "$LD_LIBRARY_PATH"
