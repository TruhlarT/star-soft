#!/usr/bin/env csh 
#if ($#argv > 0) setenv ROOT_LEVEL $1
if ($?STAR_HOST_SYS == 0) setenv STAR_HOST_SYS `sys`
set level = `echo $ROOT_LEVEL | awk -F. '{print $2}'`
if ($?ROOT == 0) setenv ROOT ${STAR_ROOT}/ROOT
if ($level  >= 24)  then
    setenv ROOTSYS ${ROOT}/${ROOT_LEVEL}
    set root = "/.${STAR_HOST_SYS}/root"
else
    setenv ROOTSYS ${ROOT}/${ROOT_LEVEL}/.${STAR_HOST_SYS}/root
    set root   = ""
endif
switch ($STAR_HOST_SYS)
    case "hp_ux102":
#  ====================
    if (! ${?SHLIB_PATH}) setenv SHLIB_PATH 
    if ( -x ${GROUP_DIR}/dropit) setenv SHLIB_PATH `${GROUP_DIR}/dropit -p "$SHLIB_PATH" ROOT`
    setenv  SHLIB_PATH  ${ROOTSYS}${root}/lib:${SHLIB_PATH}
    if ($?NODEBUG) then
      setenv  SHLIB_PATH  ${ROOTSYS}${root}/LIB:${SHLIB_PATH}
    endif
	breaksw
	default:
#  ====================
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
    if ( -x ${GROUP_DIR}/dropit) setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "$LD_LIBRARY_PATH" ROOT`
    setenv LD_LIBRARY_PATH "${ROOTSYS}${root}/lib:${LD_LIBRARY_PATH}"
    if ($?NODEBUG) then
      setenv LD_LIBRARY_PATH "${ROOTSYS}${root}/LIB:${LD_LIBRARY_PATH}"
    endif
endsw
if ( -x ${GROUP_DIR}/dropit) setenv PATH  `${GROUP_DIR}/dropit -p "$PATH" ROOT`
setenv PATH "${ROOTSYS}/${root}/bin:${PATH}"
if ($?NODEBUG) then
  setenv PATH "${ROOTSYS}/${root}/BIN:${PATH}"
endif
setenv MANPATH "/afs/rhic/star/ROOT/${ROOT_LEVEL}/man:${MANPATH}"
#
# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
setenv CINTSYSDIR ${ROOTSYS}/cint
#setenv PATH "${PATH}:${CINTSYSDIR}"
setenv MANPATH "${MANPATH}:${CINTSYSDIR}/doc"
