#!/bin/csh 

#if ($#argv > 0) setenv ROOT_LEVEL $1
if ($?STAR_HOST_SYS == 0) setenv STAR_HOST_SYS `sys`
set level = `echo $ROOT_LEVEL | awk -F. '{print $1$2}'`

if (! $?ROOT) setenv ROOT ${STAR_ROOT}/ROOT

if ($level  >= 224)  then
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
    ##VP     setenv  SHLIB_PATH  ${ROOTSYS}${root}/lib:${SHLIB_PATH}
    setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/lib -p ${SHLIB_PATH}`
    if ($?NODEBUG) then
    ##VP       setenv  SHLIB_PATH  ${ROOTSYS}${root}/LIB:${SHLIB_PATH}
	setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/LIB -p ${SHLIB_PATH}`
    endif
    breaksw
        
    default:
    #  ====================
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 
    if ( -x ${GROUP_DIR}/dropit) setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "$LD_LIBRARY_PATH" ROOT`
    ##VP     setenv LD_LIBRARY_PATH "${ROOTSYS}${root}/lib:${LD_LIBRARY_PATH}"
    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/lib -p ${LD_LIBRARY_PATH}`
    if ($?NODEBUG) then
	##VP       setenv LD_LIBRARY_PATH "${ROOTSYS}/LIB:${LD_LIBRARY_PATH}"
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/LIB -p ${LD_LIBRARY_PATH}`
    endif
    if ($?INSURE) then
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/ILIB -p ${LD_LIBRARY_PATH}`
    endif
endsw


if ( -x ${GROUP_DIR}/dropit) setenv PATH  `${GROUP_DIR}/dropit -p "$PATH" ROOT`

##VP setenv PATH "${ROOTSYS}/${root}/bin:${PATH}"
setenv PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/bin -p ${PATH}`

if ($?NODEBUG) then
  ##VP   setenv PATH "${ROOTSYS}/${root}/BIN:${PATH}"
  setenv PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/BIN -p ${PATH}`
endif
if ($?INSURE) then
  setenv PATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/IBIN -p ${PATH}`
endif


if ($?MANPATH == 0) setenv MANPATH
##VP setenv MANPATH "${ROOTSYS}/man:${MANPATH}"
setenv MANPATH `${GROUP_DIR}/dropit -p ${ROOTSYS}/man -p ${MANPATH}`

# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
setenv CINTSYSDIR ${ROOTSYS}/cint
##VP #setenv PATH "${PATH}:${CINTSYSDIR}"
#setenv PATH `${GROUP_DIR}/dropit -p ${PATH} -p ${CINTSYSDIR}`
##VP setenv MANPATH "${MANPATH}:${CINTSYSDIR}/doc"
setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p ${CINTSYSDIR}/doc`
