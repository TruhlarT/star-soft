#       $Id: group_env.csh,v 1.4 1998/03/24 00:04:09 fisyak Exp $
#	Purpose:	STAR group csh setup 
#       $Log: group_env.csh,v $
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
#setenv GROUPPATH  "__NONE__"
setenv GROUPPATH  $GROUP_PATH
#if ($ECHO && -r ${GROUP_DIR}/logo )                      cat  ${GROUP_DIR}/logo  
setenv STAR_PATH ${STAR_ROOT}/packages;      if ($ECHO) echo   "Setting up STAR_PATH = ${STAR_PATH}"       
if ($?STAR_LEVEL == 0) setenv STAR_LEVEL pro
setenv LEVEL_STAR $STAR_LEVEL
setenv STAR_VERSION `ls -l $STAR_PATH | grep "${STAR_LEVEL} ->" |cut -f2 -d">"`  
setenv VERSION_STAR $STAR_VERSION
setenv STAR $STAR_PATH/${STAR_LEVEL} ;       if ($ECHO) echo   "Setting up STAR      = ${STAR}"
setenv STAR_MGR $STAR/mgr
source ${GROUP_DIR}/STAR_SYS;    
setenv STAR_LIB  $STAR/lib/${STAR_HOST_SYS}; if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv LIB_STAR  ${STAR_LIB}
#setenv STAR_BIN  $STAR/bin/${STAR_HOST_SYS}; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
setenv STAR_BIN  $STAR/asps/../.${STAR_HOST_SYS}/bin  ; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
setenv BIN_STAR  ${STAR_BIN}
setenv STAR_PAMS $STAR/pams;                 if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"
setenv PAMS_STAR ${STAR_PAMS}
setenv STAR_DATA ${STAR_ROOT}/data;          if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
setenv STAR_CALIB ${STAR_ROOT}/calib;        if ($ECHO) echo   "Setting up STAR_CALIB= ${STAR_CALIB}"
setenv CVSROOT   $STAR_PATH/repository;      if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"
setenv TEXINPUTS :${GROUP_DIR}/latex/styles
setenv GROUPPATH "${GROUP_DIR}:${STAR_MGR}:${STAR_BIN}"
setenv PATH /usr/afsws/bin:/usr/afsws/etc:/opt/rhic/bin:/usr/local/bin:${GROUP_DIR}:${STAR_MGR}:${STAR_BIN}:${PATH}
setenv MANPATH ${MANPATH}:${STAR_PATH}/man
setenv STAR_LD_LIBRARY_PATH ""
switch ($STAR_SYS)
    case "rs_aix*":
#  ====================
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
        setenv PATH `/afs/rhic/star/group/dropit cern`:$CERN_ROOT/bin
      endif
    breaksw
    case "sgi_5*":
#  ====================
      if ($?CERN == 0 || $CERN == "/cern") then
	setenv CERN ${AFS_RHIC}/asis/sgi_52/cern
	setenv CERN_LEVEL pro
	setenv CERN_ROOT $CERN/$CERN_LEVEL
        setenv PATH `/afs/rhic/star/group/dropit cern`:$CERN_ROOT/bin
      endif
    breaksw
    case "sgi_6*":
#  ====================
    breaksw
    case "i386_linux2":
#  ====================
     if ( -d /usr/pgi ) then
       setenv PGI /usr/pgi
       set path = ( $PGI/linux86/bin $path)
       setenv MANPATH "$MANPATH":$PGI/man
       setenv LM_LICENSE_FILE $PGI/license.dat
       alias pgman 'man -M $PGI/man'
     endif
    breaksw
    case "sun4*":
#  ====================
      setenv STAR_LD_LIBRARY_PATH "/opt/SUNWspro/lib:/usr/openwin/lib:/usr/dt/lib:/usr/local/lib"
    breaksw 
    case "sunx86_55":
#  ====================
    breaksw
    default:
#  ====================
    breaksw
endsw
if ($?LD_LIBRARY_PATH == 0) then
setenv LD_LIBRARY_PATH "$STAR_LD_LIBRARY_PATH"
else
setenv LD_LIBRARY_PATH "$STAR_LD_LIBRARY_PATH":"$LD_LIBRARY_PATH"
endif
setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p ${LD_LIBRARY_PATH}`
if ( -e /usr/ccs/bin/ld ) set PATH = ( $PATH':'/usr/ccs/bin':'/usr/ccs/lib )
  setenv PATH `/afs/rhic/star/group/dropit`
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
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
#if ( -e $STAR/mgr/init_star.csh) source $STAR/mgr/init_star.csh
if ($ECHO) echo   "STAR library version "$STAR_VERSION" has been initiated with `which staf`"
#
# HP Jetprint
if ( -d /opt/hpnp ) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH "$MANPATH":/opt/hpnp/man
  set PATH = ( $PATH':'/opt/hpnp/bin':'/opt/hpnp/admin )
endif
# clean-up PATH
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit GROUPPATH`
#
unset ECHO
#END
