#!/usr/bin/csh -f
set level = `echo $ROOT_LEVEL | awk -F. '{print $2}'`
if ($level  >= 24)  then
    setenv ROOTSYS /afs/rhic/star/ROOT/${ROOT_LEVEL}
    set root = "/.${STAR_HOST_SYS}/root"
else
    setenv ROOTSYS /afs/rhic/star/ROOT/${ROOT_LEVEL}/.${STAR_HOST_SYS}/root
    set root   = ""
endif
switch ($STAR_SYS)
    case "hp_ux102":
#  ====================
    if (! ${?SHLIB_PATH}) setenv SHLIB_PATH 
    if ( -x /afs/rhic/star/group/dropit) setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p "$SHLIB_PATH" ROOT`
    setenv  SHLIB_PATH  ${ROOTSYS}${root}/lib:${SHLIB_PATH}
	breaksw
	default:
#  ====================
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
    if ( -x /afs/rhic/star/group/dropit) setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH" ROOT`
    setenv LD_LIBRARY_PATH "${ROOTSYS}${root}/lib:${LD_LIBRARY_PATH}"
endsw
if ( -x /afs/rhic/star/group/dropit) setenv PATH  `/afs/rhic/star/group/dropit -p "$PATH" ROOT`
setenv PATH "${ROOTSYS}/${root}/bin:${PATH}"
setenv MANPATH "/afs/rhic/star/ROOT/${ROOT_LEVEL}/man:${MANPATH}"
# On Solaris, Linux, SGI, Alpha/OSF do:
set MACHINE = `uname -s`

switch ($MACHINE)
#    setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}"
    case SunOS:
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/dt/lib:/usr/openwin/lib:/usr/ccs/lib:/usr/ucblib
    breaksw
    case Linux:
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/lib:/usr/local/lib
    breaksw
    case HP-UX:
    breaksw
    default:
    if ($?SILENT == 0) echo " Unimplemented platform $MACHINE"
    exit   
  endsw
#
# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
