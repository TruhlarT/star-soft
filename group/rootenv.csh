   if ( -x /afs/rhic/star/group/dropit) then
     setenv LD_LIBRARY_PATH `/afs/rhic/star/group/dropit -p "$LD_LIBRARY_PATH" ROOT`
     setenv PATH            `/afs/rhic/star/group/dropit ROOT`
   endif
   setenv ROOTSYS /afs/rhic/opt/rhic/ROOT2
   if ( -x $STAR_PATH/ROOT2.08/root/bin/root ) setenv ROOTSYS $STAR_PATH/ROOT2.08/root
#   if ( ! -e $ROOTSYS) setenv ROOTSYS /afs/rhic/opt/rhic/root
#   if ( ! -e $ROOTSYS) setenv ROOTSYS /afs/rhic/sunx86_55/opt/rhic/ROOT2

   set path = ($ROOTSYS/bin $path)
# On Solaris, Linux, SGI, Alpha/OSF do:
  set MACHINE = `uname -s`
  
  switch ($MACHINE)
    case Linux:
    case SunOS:
    case IRIX:
    case OSF1:
    if (! ${?LD_LIBRARY_PATH}) setenv LD_LIBRARY_PATH 

#       for those who uses non standard pthread library
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/pthread/lib
#       ROOT libs
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/lib
#       System libs
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/lib:/usr/local/lib
#               for Sun
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/dt/lib:/usr/openwin/lib:/usr/ccs/lib
#               PrintIt
    echo LD_LIBRARY_PATH = $LD_LIBRARY_PATH
    breaksw

    case IRIX64:
    if (! ${?LD_LIBRARYN32_PATH}) setenv LD_LIBRARYN32_PATH 
#       ROOT libs
    setenv LD_LIBRARYN32_PATH ${LD_LIBRARYN32_PATH}:${ROOTSYS}/lib
#       System libs
    setenv LD_LIBRARYN32_PATH ${LD_LIBRARYN32_PATH}:/usr/lib32:/usr/local/lib
#               PrintIt
    echo LD_LIBRARYN32_PATH = $LD_LIBRARYN32_PATH
    breaksw

    case AIX:
    if (! ${?LIBPATH}) setenv LIBPATH 
    setenv  LIBPATH /lib:/usr/lib:${LIBPATH}:$ROOTSYS/lib    
    breaksw


    default:
    echo " Unimplemented platform $MACHINE"
    exit   
  endsw

#
# OpenGL
if (-e $ROOTSYS/../Mesa) setenv OPENGL $ROOTSYS/../Mesa  
