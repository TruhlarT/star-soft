#!/usr/bin/csh -f
#       $Id: group_env.csh,v 1.100 2000/05/26 19:01:06 fisyak Exp $
#	Purpose:	STAR group csh setup 
#
#	Author:		Y.Fisyak     BNL
#	Date:		27 Feb. 1998
#	Modified:
#     3 Mar 98  T. Wenaus  HP Jetprint added (for sol)
# 
#	STAR software group	1998
#
set ECHO = 1; if ($?STAR == 1) set ECHO = 0
if ($?SILENT == 1) set ECHO = 0;
if ($ECHO) then
  cat /afs/rhic/star/group/small-logo 
endif
setenv WWW_HOME http://www.star.bnl.gov/
                                             if ($ECHO) echo   "Setting up WWW_HOME  = $WWW_HOME"
setenv AFS       /usr/afsws
setenv AFS_RHIC  /afs/rhic
setenv STAR_ROOT ${AFS_RHIC}/star;           if ($ECHO) echo   "Setting up STAR_ROOT = ${STAR_ROOT}"         
# Defined by HEPiX
if ( ! $?GROUP_DIR )  setenv GROUP_DIR ${STAR_ROOT}/group
# Defined in CORE
if ( ! $?GROUP_PATH ) setenv GROUP_PATH ${STAR_ROOT}/group
setenv GROUPPATH  $GROUP_PATH
if ($?STAR_PATH == 0) setenv STAR_PATH ${STAR_ROOT}/packages;      if ($ECHO) echo   "Setting up STAR_PATH = ${STAR_PATH}"
if ($?STAR_LEVEL == 0) setenv STAR_LEVEL pro
if ($STAR_LEVEL  == "old" || $STAR_LEVEL  == "pro" || $STAR_LEVEL  == "new" || $STAR_LEVEL  == "dev" || $STAR_LEVEL  == ".dev") then
  setenv STAR_VERSION `/bin/ls -ld $STAR_PATH/${STAR_LEVEL} |cut -f2 -d">"`  
else
  setenv STAR_VERSION ${STAR_LEVEL}
endif
if ($?STAF_LEVEL == 0) setenv STAF_LEVEL pro
if ($STAF_LEVEL  == "old" || $STAF_LEVEL  == "pro" || $STAF_LEVEL  == "new" || $STAF_LEVEL  == "dev" || $STAF_LEVEL  == ".dev") then
  setenv STAF_VERSION `/bin/ls -ld $STAR_PATH/StAF/${STAF_LEVEL} |cut -f2 -d">"`  
else
  setenv STAF_VERSION ${STAF_LEVEL}
endif
source ${GROUP_DIR}/STAR_SYS; 
setenv STAR $STAR_PATH/${STAR_VERSION};         if ($ECHO) echo   "Setting up STAR      = ${STAR}"
setenv STAF $STAR_PATH/StAF/${STAF_VERSION};    if ($ECHO) echo   "Setting up STAF      = ${STAF}"
setenv STAF_LIB  $STAF/.${STAR_HOST_SYS}/lib;   if ($ECHO) echo   "Setting up STAF_LIB  = ${STAF_LIB}"
setenv STAF_BIN  $STAF/.${STAR_HOST_SYS}/bin;   if ($ECHO) echo   "Setting up STAF_BIN  = ${STAF_BIN}"
setenv STAR_LIB  $STAR/.${STAR_HOST_SYS}/lib;   if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv MINE_LIB        .${STAR_HOST_SYS}/lib;
if ($?NODEBUG) then
  setenv STAR_lib  $STAR/.${STAR_HOST_SYS}/LIB; if ($ECHO) echo   "Setting up STAR_lib  = ${STAR_lib}"
  setenv MINE_lib        .${STAR_HOST_SYS}/LIB;
else 
  if ($?STAR_lib) unsetenv STAR_lib
  if ($?MINE_lib) unsetenv MINE_lib
endif
setenv STAR_BIN  $STAR/.${STAR_HOST_SYS}/bin  ; if ($ECHO) echo   "Setting up STAR_BIN  = ${STAR_BIN}"
setenv MY_BIN          .${STAR_HOST_SYS}/bin 
setenv STAR_MGR $STAR/mgr
setenv STAR_SCRIPTS $STAR/scripts
setenv STAR_CGI $STAR/cgi
setenv STAR_PAMS $STAR/pams;                 if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"
setenv STAR_DATA ${STAR_ROOT}/data;          if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
if ( $?STAR_DB == 0) setenv STAR_DB /star/sol/db;                 if ($ECHO) echo   "Setting up STAR_DB   = ${STAR_DB}"
setenv STAR_PARAMS ${STAR}/params;      if ($ECHO) echo   "Setting up STAR_PARAMS= ${STAR_PARAMS}"
setenv STAR_CALIB ${STAR_ROOT}/calib;   if ($ECHO) echo   "Setting up STAR_CALIB= ${STAR_CALIB}"
setenv STAR_PROD   $STAR/prod;          if ($ECHO) echo   "Setting up STAR_PROD = ${STAR_PROD}"
setenv CVSROOT   $STAR_PATH/repository; if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"

if (-f $STAR/mgr/ROOT_LEVEL && -f $STAR/mgr/CERN_LEVEL) then
  setenv ROOT_LEVEL `cat $STAR/mgr/ROOT_LEVEL`
  setenv CERN_LEVEL `cat $STAR/mgr/CERN_LEVEL`
else
switch ( $STAR_VERSION )

  case SL98l: setenv ROOT_LEVEL 2.20
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

  default: setenv ROOT_LEVEL 2.13
endsw
endif
setenv CERN_ROOT  $CERN/$CERN_LEVEL
if ($ECHO) echo   "Setting up ROOT_LEVEL= ${ROOT_LEVEL}"
setenv GROUPPATH "${GROUP_DIR}:${STAR_MGR}:${STAR_SCRIPTS}:${STAR_CGI}:${MY_BIN}:${STAR_BIN}:${STAF}/mgr:${STAF_BIN}"
setenv PATH "/opt/star/bin:$PATH"
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} GROUPPATH`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} $STAR_PATH`
  if ($?LD_LIBRARY_PATH == 1) setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p ${LD_LIBRARY_PATH} $STAR_PATH`
  if ($?SHLIB_PATH == 1)      setenv SHLIB_PATH      `/afs/rhic/star/group/dropit -p ${SHLIB_PATH} $STAR_PATH`
endif
setenv PATH "${GROUPPATH}:/usr/afsws/bin:/usr/afsws/etc:/opt/star/bin:/usr/sue/bin:/usr/local/bin:${PATH}"
## Put mysql on path if available
if ( -d /usr/local/mysql/bin) then
  setenv PATH "${PATH}:/usr/local/mysql/bin"
endif
if ($?MANPATH == 1) then
  setenv MANPATH ${MANPATH}:${STAR_PATH}/man
else
  setenv MANPATH ${STAR_PATH}/man
endif
     setenv OBJY_ARCH  ""
switch ($STAR_SYS)
    case "rs_aix*":
#  ====================
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
      if ($?SHLIB_PATH == 0) setenv SHLIB_PATH
      if ( -x /afs/rhic/star/group/dropit) setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p ${SHLIB_PATH} $STAR_PATH`
      if ($?MINE_lib == 1 && $?STAR_lib == 1) then
        setenv SHLIB_PATH ${MINE_lib}:${STAR_lib}:${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${SHLIB_PATH}
      else
	if ( -x /afs/rhic/star/group/dropit) setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p ${SHLIB_PATH} .${STAR_HOST_SYS}/LIB`
        setenv SHLIB_PATH ${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${SHLIB_PATH}
      endif
      setenv LD_LIBRARY_PATH ${SHLIB_PATH}
      setenv BFARCH hp_ux102
      limit coredumpsize 0
    breaksw
    case "i386_*":
#  ====================
# make sure that afws in the path
     if (! -d /usr/afsws/bin) set path = ($path /afs/rhic/i386_redhat50/usr/afsws/bin)
     if ( -d /usr/pgi ) then
       setenv PGI /usr/pgi
       set path = ( $PGI/linux86/bin $path)
       setenv MANPATH "$MANPATH":$PGI/man
       setenv LM_LICENSE_FILE $PGI/license.dat
       alias pgman 'man -M $PGI/man'
     endif
     if (-d /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE) then
       setenv KAI /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE
       set path = ($KAI/bin $path)
       
     endif
     set path = ($path  /usr/local/bin/ddd)
     if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH 
     if ($?MINE_lib == 1 && $?STAR_lib == 1) then
       setenv LD_LIBRARY_PATH "${MINE_lib}:${STAR_lib}:${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${LD_LIBRARY_PATH}"
     else
       if ( -x /afs/rhic/star/group/dropit) setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p ${LD_LIBRARY_PATH} .${STAR_HOST_SYS}/LIB`
       setenv LD_LIBRARY_PATH "${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${LD_LIBRARY_PATH}"
     endif
     limit coredump 0
     setenv BFARCH Linux2

     setenv OBJY_ARCH linux86
    breaksw
    case "sun4*":
#  ====================
      if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH
      setenv LD_LIBRARY_PATH "/usr/openwin/lib:/usr/dt/lib:/usr/local/lib:/afs/rhic/star/packages/ObjectSpace/2.0m/lib:${LD_LIBRARY_PATH}"
      if ("${STAR_HOST_SYS}" == "sun4x_56_CC5") then
        setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:/opt/WS5.0/lib:/opt/WS5.0/SC5.0/lib"
        setenv PATH "/opt/WS5.0/bin:${PATH}"
	setenv MANPATH "/opt/WS5.0/man:${MANPATH}"
        if ( -x /afs/rhic/star/group/dropit) then
          setenv PATH `/afs/rhic/star/group/dropit SUNWspro`
          setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p $LD_LIBRARY_PATH SUNWspro`
        endif
      else
        if ( -x /afs/rhic/star/group/dropit) then
          setenv PATH `/afs/rhic/star/group/dropit WS5.0`
          setenv PATH `/afs/rhic/star/group/dropit CC5`
          setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p $LD_LIBRARY_PATH 5.0`
          setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p $LD_LIBRARY_PATH CC5`
        endif
        setenv LD_LIBRARY_PATH "/opt/SUNWspro/lib:${LD_LIBRARY_PATH}"
        setenv PATH "/opt/SUNWspro/bin:$PATH"
        setenv MANPATH "/opt/SUNWspro/man:$MANPATH"
      endif

     if ($?MINE_lib == 1 && $?STAR_lib == 1) then
       setenv LD_LIBRARY_PATH "${MINE_lib}:${STAR_lib}:${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${LD_LIBRARY_PATH}"
     else
       setenv LD_LIBRARY_PATH "${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${LD_LIBRARY_PATH}"
     endif
     setenv BFARCH SunOS5
     if ("${STAR_HOST_SYS}" == "sun4x_56_CC5") setenv BFARCH SunOS5_CC5
     setenv OBJY_ARCH solaris4
     limit coredump 0
     unlimit descriptors
    breaksw 
    default:
#  ====================
    breaksw
endsw
if ( -e /usr/ccs/bin/ld ) set path = ( $path /usr/ccs/bin /usr/ccs/lib )
if ( -d /usr/local/lsf/bin ) then
  if ( -x /afs/rhic/star/group/dropit) setenv PATH `/afs/rhic/star/group/dropit lsf`
  setenv LSF_ENVDIR /usr/local/lsf/mnt/conf
  set path=(/usr/local/lsf/bin $path)
  setenv MANPATH {$MANPATH}:/usr/local/lsf/mnt/man
endif
# We need this aliases even during BATCH
if (-r $GROUP_DIR/group_aliases.csh) source $GROUP_DIR/group_aliases.csh
#
if ($?SCRATCH == 0) then
if ( -w /home/scratch ) then
        setenv SCRATCH /home/scratch/$LOGNAME
else if ( -w /scr20 ) then
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


# HP Jetprint
if ( -d /opt/hpnp ) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH "$MANPATH":/opt/hpnp/man
# set PATH = ( $PATH':'/opt/hpnp/bin':'/opt/hpnp/admin )
  set path = ( $path /opt/hpnp/bin /opt/hpnp/admin )
endif
set path = ($HOME/bin $HOME/bin/.$STAR_SYS $path $CERN_ROOT/bin $CERN_ROOT/mgr .)
if ( -x /afs/rhic/star/group/dropit) then
# clean-up PATH
if ("$CERN_LEVEL" != "pro") then
  setenv PATH  `/afs/rhic/star/group/dropit cern`
  setenv PATH  "${PATH}:${CERN_ROOT}/bin"
endif 
setenv PATH "/opt/star/bin:${PATH}"
switch ($STAR_SYS)
    case "hp_ux102":
#  ====================
  setenv SHLIB_PATH "${SHLIB_PATH}:/opt/star/lib"
  if ( -d /opt/star/lib/mysql ) then
    setenv SHLIB_PATH "${SHLIB_PATH}:/opt/star/lib/mysql"
  endif
  setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p "$SHLIB_PATH"`
    breaksw
    default:
#  ====================
  setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:/opt/star/lib"
  if ( -d /opt/star/lib/mysql ) then
    setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:/opt/star/lib/mysql"
  endif
  setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH"`
    breaksw
endsw
  setenv MANPATH `/afs/rhic/star/group/dropit -p ${MANPATH}`
  setenv PATH `/afs/rhic/star/group/dropit -p ${PATH} GROUPPATH`
endif
if ($ECHO) then
echo "STAR setup on" `hostname` "by" `date` " has been completed"
if ($ECHO) echo   "LD_LIBRARY_PATH = $LD_LIBRARY_PATH"
unset ECHO
endif
set date="`date`"
cat >> $GROUP_DIR/statistics/star${STAR_VERSION} << EOD
$USER from $HOST asked for STAR_LEVEL=$STAR_LEVEL / STAR_VERSION=$STAR_VERSION  $date
EOD
#END



