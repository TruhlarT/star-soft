#       $Id: group_env.csh,v 1.17 1998/06/24 18:01:23 wenaus Exp $
#	Purpose:	STAR group csh setup 
#       $Log: group_env.csh,v $
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
setenv STAR_VERSION `ls -l $STAR_PATH | grep "${STAR_LEVEL} ->" |cut -f2 -d">"`  
setenv STAR $STAR_PATH/${STAR_LEVEL} ;       if ($ECHO) echo   "Setting up STAR      = ${STAR}"
setenv STAR_MGR $STAR/mgr
source ${GROUP_DIR}/STAR_SYS; 
setenv STAF_LIB  $STAR/asps/../.${STAR_HOST_SYS}/lib  ; if ($ECHO) echo   "Setting up STAF_LIB  = ${STAF_LIB}"
if ($STAR_LEVEL == "dev") then
setenv STAR_LIB  $STAR/.${STAR_HOST_SYS}/lib; if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv STAR_BIN  $STAR/asps/../.${STAR_HOST_SYS}/bin  ; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
else   
setenv STAR_LIB  $STAR/lib/${STAR_HOST_SYS}; if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv STAR_BIN  $STAR/asps/../.${STAR_HOST_SYS}/bin  ; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
endif
setenv STAR_PAMS $STAR/pams;                 if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"
setenv STAR_DATA ${STAR_ROOT}/data;          if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
if ( ! $?STAR_DB ) setenv STAR_DB /star/sol/db;                 if ($ECHO) echo   "Setting up STAR_DB = ${STAR_DB}"
setenv STAR_CALIB ${STAR_ROOT}/calib;        if ($ECHO) echo   "Setting up STAR_CALIB= ${STAR_CALIB}"
setenv CVSROOT   $STAR_PATH/repository;      if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"
setenv TEXINPUTS :${GROUP_DIR}/latex/styles
setenv GROUPPATH "${GROUP_DIR}:${STAR_MGR}:${STAR_BIN}"
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit GROUPPATH`
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
      if ($?CERN == 0 || $CERN == "/cern") then
	setenv CERN ${AFS_RHIC}/asis/hp_ux102/cern
	setenv CERN_LEVEL new
	setenv CERN_ROOT $CERN/$CERN_LEVEL
        set path = ( $CERN_ROOT/bin $path )
        echo hp_ux102 PATH = $PATH
      endif
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
        if (! ${?LD_LIBRARY_PATHN32}) setenv LD_LIBRARY_PATHN32 
	setenv LD_LIBRARY_PATHN32 "${STAF_LIB}:${LD_LIBRARY_PATHN32}"
        
        limit coredumpsize 0
    breaksw
    case "i386_linux2":
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
     set path = (/usr/bin $path  /usr/local/bin/ddd /usr/local/DQS318/bin )
#    set path = ($path  /usr/local/bin/ddd /usr/local/DQS318/bin )
     set path = ($path $PARASOFT/bin.linux)
     if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
     setenv LD_LIBRARY_PATH "/usr/lib:${PARASOFT}/lib.linux:/usr/local/lib:${STAF_LIB}:${LD_LIBRARY_PATH}"
        limit coredump 0
    breaksw
    case "sun4*":
#  ====================
      if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH
      setenv LD_LIBRARY_PATH "/opt/SUNWspro/lib:/usr/openwin/lib:/usr/dt/lib:/usr/local/lib:${PARASOFT}/lib.solaris:${STAF_LIB}:{LD_LIBRARY_PATH}"
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
# Objy 5.00
if (-f /opt/objy/objy500/setup.csh) then
if ( ! $?OBJY_HOME) source  /opt/objy/objy500/setup.csh
endif
# BaBar
setenv BFROOT /star/sol/packages/BaBar
setenv BFSITE starbnl
setenv OBJYBASE $OBJY_HOME
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
set path = (. $HOME/bin $HOME/bin/$STAR_SYS $path $CERN_ROOT/mgr)
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
  setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH"`
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit GROUPPATH`
endif
unset ECHO
set date="`date`"
cat >> $GROUP_DIR/statistics/star${STAR_LEVEL} << EOD
$USER from $HOST asked for $STAR_VERSION $date
EOD
#END



