#!/usr/bin/csh -f
#       $Id: group_env.csh,v 1.38 1998/07/24 15:17:36 fisyak Exp $
#	Purpose:	STAR group csh setup 
#       $Log: group_env.csh,v $
#       Revision 1.38  1998/07/24 15:17:36  fisyak
#       Add redhat50
#
#       Revision 1.37  1998/07/23 14:28:48  wenaus
#       re-insert new Objy setup
#
#       Revision 1.36  1998/07/22 21:41:31  fisyak
#       Move STAR_SYS  up
#
#       Revision 1.35  1998/07/22 21:29:20  fisyak
#       Add SL98f
#
#       Revision 1.32  1998/07/19 01:30:40  fisyak
#       /usr/bin/ls -> /bin/ls
#
#       Revision 1.31  1998/07/19 01:26:15  fisyak
#       replace ls -> /usr/bin/ls to protect from user aliases
#
#       Revision 1.30  1998/07/12 23:14:03  fisyak
#       fix bug in LD_LIBRARY_PATH
#
#       Revision 1.29  1998/07/11 00:59:14  fisyak
#       add cern/LEVEL/bin to path
#
#       Revision 1.28  1998/07/10 21:18:40  fisyak
#       Fix NODEBUG flug for SL98c and SL98e
#
#       Revision 1.27  1998/07/10 14:06:42  fisyak
#       Keep for SL98a and SL98b the old version convention
#
#       Revision 1.26  1998/07/10 13:49:28  fisyak
#       Add cleaning of STAR_PATH
#
#       Revision 1.25  1998/07/10 12:53:32  fisyak
#       Use STAR_VERSION instead STAR_LEVEL for STAR top directory, to be in sunc. with starver script
#
#       Revision 1.24  1998/07/07 18:25:49  fisyak
#       Add STAR_PARAMS to STAR environment variables
#
#       Revision 1.23  1998/07/04 18:49:35  fisyak
#       Add STAF_LIB to LD_LIBRARYN32_PATH for sgi_64
#
#       Revision 1.22  1998/07/03 20:04:04  fisyak
#       Add MANPATH to DQS386
#
#       Revision 1.21  1998/07/01 23:28:08  fisyak
#       Add non debug version
#
#       Revision 1.20  1998/06/30 14:37:22  didenko
#       Add hp
#
#       Revision 1.19  1998/06/24 20:18:38  wenaus
#       BaBar setup only in conjunction with Objy setup
#
#       Revision 1.18  1998/06/24 18:35:52  wenaus
#       Objy setup must always be run
#
#       Revision 1.17  1998/06/24 18:01:23  wenaus
#       Add env variables for BaBar and G4 software
#
#       Revision 1.16  1998/06/20 01:05:23  fisyak
#       Add STAF_LIB in LD_LIBRARY_PATH
#
#       Revision 1.15  1998/06/14 19:48:00  fisyak
#       Add crean up of ROOT path
#
#       Revision 1.14  1998/06/12 15:45:32  fisyak
#       Resotore dev environment
#
#       Revision 1.13  1998/06/12 13:11:57  fisyak
#       Add version statistics
#
#       Revision 1.12  1998/06/11 20:29:49  wenaus
#       Set STAR_DB only if not yet set to allow offsite overrides
#
#       Revision 1.11  1998/06/11 20:23:13  wenaus
#       Add STAR_DB env variable
#
#       Revision 1.10  1998/05/14 19:04:25  fisyak
#       clean LD_LIBRARY_PATH
#
#       Revision 1.9  1998/05/12 12:14:20  fisyak
#       Clean up
#
#       Revision 1.8  1998/05/01 22:55:43  fisyak
#       add dropit for PATH
#
#       Revision 1.7  1998/04/24 17:08:52  fisyak
#       Set coredupsize=0
#
#       Revision 1.6  1998/04/04 14:47:22  fisyak
#       Add clean PATH
#
#       Revision 1.5  1998/03/26 16:41:34  fisyak
#       Add STAR_LEVELS
#
#       Revision 1.4  1998/03/24 00:04:09  fisyak
#       fix PATH
#
#       Revision 1.3  1998/03/23 02:29:15  fisyak
#       Fix group start-up
#
#	Author:		Y.Fisyak     BNL
#	Date:		27 Feb. 1998
#	Modified:
#     3 Mar 98  T. Wenaus  HP Jetprint added (for sol)
# 
#	STAR software group	1998
#
set ECHO = 1; if ($?STAR == 1) set ECHO = 0
if ($ECHO) then
  cat /afs/rhic/star/group/small-logo 
endif
setenv WWW_HOME http://www.rhic.bnl.gov/STAR/star.html; 
                                             if ($ECHO) echo   "Setting up WWW_HOME  = $WWW_HOME"
setenv AFS       /afs
setenv AFS_RHIC  ${AFS}/rhic
setenv STAR_ROOT ${AFS_RHIC}/star;           if ($ECHO) echo   "Setting up STAR_ROOT = ${STAR_ROOT}"         
# Defined by HEPiX
if ( ! $?GROUP_DIR )  setenv GROUP_DIR ${STAR_ROOT}/group
# Defined in CORE
if ( ! $?GROUP_PATH ) setenv GROUP_PATH ${STAR_ROOT}/group
setenv GROUPPATH  $GROUP_PATH
setenv STAR_PATH ${STAR_ROOT}/packages;      if ($ECHO) echo   "Setting up STAR_PATH = ${STAR_PATH}"
if ($?STAR_LEVEL == 0) setenv STAR_LEVEL pro
setenv STAR_VERSION `/bin/ls -l $STAR_PATH | grep "${STAR_LEVEL} ->" |cut -f2 -d">"`  
source ${GROUP_DIR}/STAR_SYS; 
if (${STAR_VERSION} == "") setenv STAR_VERSION ${STAR_LEVEL}
if ($STAR_VERSION  == "SL98a" || $STAR_VERSION  == "SL98b") then
  setenv STAR $STAR_PATH/${STAR_LEVEL} ;         if ($ECHO) echo   "Setting up STAR      = ${STAR}"
  setenv STAR_LIB  $STAR/lib/${STAR_HOST_SYS};   if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
  setenv STAF_LIB 
else  
  setenv STAR $STAR_PATH/${STAR_VERSION} ;       if ($ECHO) echo   "Setting up STAR      = ${STAR}"
  setenv STAF_LIB  $STAR/asps/../.${STAR_HOST_SYS}/lib  ; if ($ECHO) echo   "Setting up STAF_LIB  = ${STAF_LIB}"
  if ($?NODEBUG == 0) then
    setenv STAR_LIB  $STAR/.${STAR_HOST_SYS}/lib; if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
  else
    setenv STAR_LIB  $STAR/.${STAR_HOST_SYS}/nodeb; if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
  endif
endif
setenv STAR_BIN  $STAR/asps/../.${STAR_HOST_SYS}/bin  ; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
setenv STAR_MGR $STAR/mgr
setenv STAR_PAMS $STAR/pams;                 if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"
setenv STAR_DATA ${STAR_ROOT}/data;          if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
if ( ! $?STAR_DB ) setenv STAR_DB /star/sol/db;                 if ($ECHO) echo   "Setting up STAR_DB   = ${STAR_DB}"
setenv STAR_PARAMS ${STAR}/params;      if ($ECHO) echo   "Setting up STAR_PARAMS= ${STAR_PARAMS}"
setenv STAR_CALIB ${STAR_ROOT}/calib;        if ($ECHO) echo   "Setting up STAR_CALIB= ${STAR_CALIB}"
setenv CVSROOT   $STAR_PATH/repository;      if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"
setenv TEXINPUTS :${GROUP_DIR}/latex/styles
setenv GROUPPATH "${GROUP_DIR}:${STAR_MGR}:${STAR_BIN}"
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} GROUPPATH`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} $STAR_PATH`
endif
setenv PATH "/usr/afsws/bin:/usr/afsws/etc:/opt/star/bin:/opt/rhic/bin:/usr/sue/bin:/usr/local/bin:${GROUP_DIR}:${STAR_MGR}:${STAR_BIN}:${PATH}"
#set path=( /usr/afsws/bin /usr/afsws/etc /opt/rhic/bin /usr/local/bin $GROUP_DIR $STAR_MGR $STAR_BIN $path )
if ($?MANPATH == 1) then
  setenv MANPATH ${MANPATH}:${STAR_PATH}/man
else
  setenv MANPATH ${STAR_PATH}/man
endif
setenv PARASOFT /afs/rhic/star/packages/parasoft
switch ($STAR_SYS)
    case "rs_aix*":
#  ====================
	set path = ($path $PARASOFT/bin.aix4) 
        setenv MANPATH {$MANPATH}:/usr/share/man
    breaksw
    case "alpha_osf32c":
#  ====================
    breaksw
    case "hp700_ux90":
#  ====================
    breaksw
    case "hp_ux102":
#  ====================
      if ($?CERN == 0 || $CERN == "/cern" ) then
#	setenv CERN ${AFS_RHIC}/asis/hp_ux102/cern
#	setenv CERN_LEVEL new
#	setenv CERN_ROOT $CERN/$CERN_LEVEL
#	set path = ( $CERN_ROOT/bin $path )
      endif
      if (! ${?SHLIB_PATH}) setenv SHLIB_PATH
      setenv SHLIB_PATH ${SHLIB_PATH}:${STAF_LIB}
    breaksw
    case "sgi_5*":
#  ====================
	set path = ($path $PARASOFT/bin.sgi5)
        if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
	setenv LD_LIBRARY_PATH "${PARASOFT}/lib.sgi5:${STAF_LIB}:${LD_LIBRARY_PATH}"
        limit coredumpsize 0
    breaksw
    case "sgi_6*":
#  ====================
        setenv CERN_LEVEL pro
        setenv CERN_ROOT  /cern/pro
        if (! ${?LD_LIBRARYN32_PATH}) setenv LD_LIBRARYN32_PATH 
	setenv LD_LIBRARYN32_PATH "${STAF_LIB}:${LD_LIBRARYN32_PATH}"
        limit coredumpsize 0
    breaksw
    case "i386_*":
#  ====================
     if ( -d /usr/pgi ) then
       setenv PGI /usr/pgi
       set path = ( $PGI/linux86/bin $path)
       setenv MANPATH "$MANPATH":$PGI/man
       setenv LM_LICENSE_FILE $PGI/license.dat
       alias pgman 'man -M $PGI/man'
       setenv CERN_LEVEL pgf98
       setenv CERN_ROOT  $CERN/$CERN_LEVEL
     endif
     set path = ($path  /usr/local/bin/ddd /usr/local/DQS318/bin )
     setenv  MANPATH "$MANPATH":/usr/local/DQS318/man
#    set path = ($path  /usr/local/bin/ddd /usr/local/DQS318/bin )
     set path = ($path $PARASOFT/bin.linux)
     if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
     setenv LD_LIBRARY_PATH "/usr/lib:${PARASOFT}/lib.linux:/usr/local/lib:${STAF_LIB}:${LD_LIBRARY_PATH}:/opt/star/lib"
        limit coredump 0
    breaksw
    case "sun4*":
#  ====================
      if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH
      setenv LD_LIBRARY_PATH "/opt/SUNWspro/lib:/usr/openwin/lib:/usr/dt/lib:/usr/local/lib:${PARASOFT}/lib.solaris:${STAF_LIB}:${LD_LIBRARY_PATH}"
	set path = ($path $PARASOFT/bin.solaris)
    breaksw 
    case "sunx86_55":
#  ====================
        if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH
        setenv LD_LIBRARY_PATH "${STAF_LIB}:${LD_LIBRARY_PATH}"
        limit coredump 0
    breaksw
    default:
#  ====================
    breaksw
endsw
if ( -e /usr/ccs/bin/ld ) set path = ( $path /usr/ccs/bin /usr/ccs/lib )
# We need this aliases even during BATCH
if (-r $GROUP_DIR/group_aliases.csh) source $GROUP_DIR/group_aliases.csh
#
if ($?SCRATCH == 0) then
if ( -w /scr20 ) then
        setenv SCRATCH /scr20/$LOGNAME
else if ( -w /scr21 ) then
        setenv SCRATCH /scr21/$LOGNAME
else if ( -w /scr22 ) then
        setenv SCRATCH /scr22/$LOGNAME
else if ( -w /scratch ) then
        setenv SCRATCH /scratch/$LOGNAME
else 
#	echo No scratch directory available. Using /tmp/$USER ...
        setenv SCRATCH /tmp/$LOGNAME
endif
 
if ( ! -d $SCRATCH ) then
        mkdir $SCRATCH
        chmod 755 $SCRATCH
endif
if ($ECHO) echo   "Setting up SCRATCH   = $SCRATCH"
endif
if ($ECHO) echo   "STAR library version "$STAR_VERSION" has been initiated with `which staf`"
if ($?CERN_ROOT == 1 ) then
if ($ECHO) echo   "CERNLIB version "$CERN_LEVEL" has been initiated with CERN_ROOT="${CERN_ROOT}
endif
# root
if ( -f $GROUP_DIR/rootenv.csh) then
  source $GROUP_DIR/rootenv.csh
endif

# Objectivity
source $GROUP_DIR/ObjySetup.csh

# Geant4
setenv G4PROTO /star/sol/packages/geant4/prototype
setenv RWBASE /star/sol/packages/rogue/workspaces/SOLARIS25/SUNPRO42/12s
setenv CLHEP_BASE_DIR /opt/rhic
# HP Jetprint
if ( -d /opt/hpnp ) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH "$MANPATH":/opt/hpnp/man
# set PATH = ( $PATH':'/opt/hpnp/bin':'/opt/hpnp/admin )
  set path = ( $path /opt/hpnp/bin /opt/hpnp/admin )
endif
set path = (. $HOME/bin $HOME/bin/.$STAR_SYS $path $CERN_ROOT/bin $CERN_ROOT/mgr)
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
switch ($STAR_SYS)
    case "hp_ux102":
#  ====================
  setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p "$SHLIB_PATH"`
    breaksw
    case "sgi_64":
#  ====================
  setenv LD_LIBRARYN32_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARYN32_PATH"`
    breaksw
    default:
#  ====================
  setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH"`
    breaksw
endsw
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} GROUPPATH`
endif
if ($ECHO) echo "STAR setup on" `hostname` "by" `date` " has been completed"
unset ECHO
set date="`date`"
cat >> $GROUP_DIR/statistics/star${STAR_VERSION} << EOD
$USER from $HOST asked for STAR_LEVEL=$STAR_LEVEL / STAR_VERSION=$STAR_VERSION  $date
EOD
#END



