#!/usr/bin/csh -f
   if ( -x /afs/rhic/star/group/dropit) then
     switch ($STAR_SYS)
     case "hp_ux102":
#  ====================
       setenv SHLIB_PATH `/afs/rhic/star/group/dropit -p "$SHLIB_PATH" ROOT`
     breaksw
     default:
#  ====================
       setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH" ROOT`
       breaksw
     endsw
     setenv PATH            `/afs/rhic/star/group/dropit -p "$PATH" ROOT`
   endif
  setenv ROOTSYS /afs/rhic/star/ROOT/${ROOT_LEVEL}/.${STAR_HOST_SYS}/root
  setenv PATH "${ROOTSYS}/bin:${PATH}"
  setenv MANPATH "/afs/rhic/star/ROOT/${ROOT_LEVEL}/man:${MANPATH}"
# On Solaris, Linux, SGI, Alpha/OSF do:
  set MACHINE = `uname -s`
  set VERSION = `uname -r`  

  switch ($MACHINE)
    case Linux:
#    setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}"
    case SunOS:
    case IRIX:
    case OSF1:
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 

#       for those who uses non standard pthread library
#       ROOT libs
    setenv LD_LIBRARY_PATH "${ROOTSYS}/lib:${LD_LIBRARY_PATH}"
#       System libs
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/lib:/usr/local/lib
#               for Sun
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/dt/lib:/usr/openwin/lib:/usr/ccs/lib
#               PrintIt
    breaksw

    case IRIX64:
    switch ($VERSION)
      case 6.2
#       ROOT libs
      setenv LD_LIBRARY_PATH "${ROOTSYS}/lib:${LD_LIBRARY_PATH}"
#       System libs
      setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/lib:/usr/local/lib
#               for Sun
      setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/dt/lib:/usr/openwin/lib:/usr/ccs/lib
#               PrintIt
      if ($?SILENT == 0) echo LD_LIBRARY_PATH = $LD_LIBRARY_PATH
      breaksw
    case 6.4   
      if (! ${?LD_LIBRARYN32_PATH}) setenv LD_LIBRARYN32_PATH 
#       ROOT libs
      setenv LD_LIBRARYN32_PATH "${ROOTSYS}/lib:${LD_LIBRARYN32_PATH}"
#       System libs
      setenv LD_LIBRARYN32_PATH ${LD_LIBRARYN32_PATH}:/usr/lib32:/usr/local/lib
#               PrintIt
      if ($?SILENT == 0) echo LD_LIBRARYN32_PATH = $LD_LIBRARYN32_PATH
      breaksw
    endsw
    
    case AIX:
    if (! ${?LIBPATH}) setenv LIBPATH 
    setenv  LIBPATH $ROOTSYS/lib:${LIBPATH}:/lib:/usr/lib
    breaksw
    case HP-UX:
    if (! ${?SHLIB_PATH}) setenv SHLIB_PATH 
    setenv  SHLIB_PATH  $ROOTSYS/lib:${SHLIB_PATH}
    if ($?SILENT == 0) echo SHLIB_PATH = $SHLIB_PATH
    breaksw
    

    default:
    if ($?SILENT == 0) echo " Unimplemented platform $MACHINE"
    exit   
  endsw

#
# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
