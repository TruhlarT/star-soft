#
#	File:		group_cshrc
#	Purpose:	STAR group csh setup 
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
setenv AFS       /afs/rhic
setenv STAR_ROOT ${AFS}/star;                if ($ECHO) echo   "Setting up STAR_ROOT = ${STAR_ROOT}"         
# Defined in CORE
if ( ! $?GROUP_PATH ) setenv GROUP_PATH ${STAR_ROOT}/group
# Defined by HEPiX
if ( ! $?GROUP_DIR ) then
	setenv GROUP_DIR ${STAR_ROOT}/group
        setenv PATH ${GROUPPATH}:$PATH
endif
#if ($ECHO && -r ${GROUP_DIR}/logo )                      cat  ${GROUP_DIR}/logo  
setenv STAR_PATH ${STAR_ROOT}/packages;      if ($ECHO) echo   "Setting up STAR_PATH = ${STAR_PATH}"       
if ($?LEVEL_STAR == 0) setenv LEVEL_STAR pro
setenv VERSION_STAR `ls -l $STAR_PATH | grep "${LEVEL_STAR} ->" |cut -f2 -d">"`  
setenv STAR $STAR_PATH/${LEVEL_STAR} ;       if ($ECHO) echo   "Setting up STAR      = ${STAR}"
setenv STAR_MGR $STAR/mgr
source ${GROUP_DIR}/SYS_STAR;    
setenv LIB_STAR  $STAR/lib/${SYS_HOST_STAR}; if ($ECHO) echo   "Setting up LIB_STAR  = ${LIB_STAR}"
setenv BIN_STAR  $STAR/bin/${SYS_HOST_STAR}; if ($ECHO) echo   "Setting up BIN_STAR  = ${BIN_STAR}"
setenv PAMS_STAR $STAR/pams;                 if ($ECHO) echo   "Setting up PAMS_STAR = ${PAMS_STAR}"
setenv STAR_DATA ${STAR_ROOT}/data;          if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
setenv STAR_CALB ${STAR_ROOT}/calb;          if ($ECHO) echo   "Setting up STAR_CALB = ${STAR_CALB}"
setenv CVSROOT   $STAR_PATH/repository;      if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"
setenv TEXINPUTS :${GROUP_DIR}/latex/styles
setenv PATH "/usr/afsws/bin:/usr/afsws/etc:/opt/rhic/bin:${STAR_MGR}:${BIN_STAR}:$PATH"
setenv MANPATH ${MANPATH}:${STAR_PATH}/man
setenv STAR_LD_LIBRARY_PATH ""
switch ($SYS_STAR)
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
    breaksw
    case "sgi_5*":
#  ====================
      if ($?CERN == 0 || $CERN == "/cern") then
	setenv CERN /afs/rhic/asis/sgi_52/cern
	setenv CERN_LEVEL pro
	setenv CERN_ROOT $CERN/$CERN_LEVEL
      endif
    breaksw
    case "sgi_6*":
#  ====================
    breaksw
    case "i386_linux2":
#  ====================
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
setenv LD_LIBRARY_PATH `dropit -p $LD_LIBRARY_PATH`
if ( -e /usr/ccs/bin/ld ) set PATH = ( $PATH':'/usr/ccs/bin':'/usr/ccs/lib )
  setenv PATH `dropit`
  setenv MANPATH `dropit -p $MANPATH`
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
if ($ECHO) echo   "STAR library version "$VERSION_STAR" has been initiated with `which staf++`"
#
# HP Jetprint
if ( -d /opt/hpnp ) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH "$MANPATH":/opt/hpnp/man
  set PATH = ( $PATH':'/opt/hpnp/bin':'/opt/hpnp/admin )
endif
# clean-up PATH
  setenv PATH `dropit GROUPPATH`
#
unset ECHO
#END
