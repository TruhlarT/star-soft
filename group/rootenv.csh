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
#   if ( -x /afs/rhic/star/ROOT/${ROOT_LEVEL}/.${STAR_SYS}/root/bin/root ) 
   setenv ROOTSYS /afs/rhic/star/ROOT/${ROOT_LEVEL}/.${STAR_SYS}/root
#   if ( ! -e $ROOTSYS) setenv ROOTSYS /afs/rhic/opt/rhic/root
#   if ( ! -e $ROOTSYS) setenv ROOTSYS /afs/rhic/sunx86_55/opt/rhic/ROOT2

#   set path = ($ROOTSYS/bin $path)
  setenv PATH "${PATH}:${ROOTSYS}/bin"
  setenv MANPATH "${MANPATH}:/afs/rhic/star/ROOT/${ROOT_LEVEL}/man"
# On Solaris, Linux, SGI, Alpha/OSF do:
  set MACHINE = `uname -s`
  set VERSION = `uname -r`  

  switch ($MACHINE)
    case Linux:
    setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}"
    case SunOS:
    case IRIX:
    case OSF1:
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 

#       for those who uses non standard pthread library
#    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/pthread/lib
#       ROOT libs
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/lib
#       System libs
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/lib:/usr/local/lib
#               for Sun
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/dt/lib:/usr/openwin/lib:/usr/ccs/lib
#               PrintIt
    if ($?SILENT == 0) echo LD_LIBRARY_PATH = $LD_LIBRARY_PATH
    breaksw

    case IRIX64:
    switch ($VERSION)
      case 6.2
#       ROOT libs
      setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/lib
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
      setenv LD_LIBRARYN32_PATH ${LD_LIBRARYN32_PATH}:${ROOTSYS}/lib
#       System libs
      setenv LD_LIBRARYN32_PATH ${LD_LIBRARYN32_PATH}:/usr/lib32:/usr/local/lib
#               PrintIt
      if ($?SILENT == 0) echo LD_LIBRARYN32_PATH = $LD_LIBRARYN32_PATH
      breaksw
    endsw
    
    case AIX:
    if (! ${?LIBPATH}) setenv LIBPATH 
    setenv  LIBPATH /lib:/usr/lib:${LIBPATH}:$ROOTSYS/lib    
    breaksw
    case HP-UX:
    if (! ${?SHLIB_PATH}) setenv SHLIB_PATH 
    setenv  SHLIB_PATH  ${SHLIB_PATH}:$ROOTSYS/lib    
    if ($?SILENT == 0) echo SHLIB_PATH = $SHLIB_PATH
    breaksw
    

    default:
    if ($?SILENT == 0) echo " Unimplemented platform $MACHINE"
    exit   
  endsw

#
# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
