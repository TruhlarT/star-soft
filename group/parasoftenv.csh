#! /usr/local/bin/tcsh -f
switch ($STAR_SYS)
    case "i386_redhat61":
	setenv PARASOFT /usr/local/app/parasoft
	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.linux2
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.linux2)
	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	breaksw
    case "i386_*":
	setenv PARASOFT /afs/rhic/i386_linux22/app/parasoft
	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.linux
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.linux)
	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	breaksw
    case "sun4*":
	setenv PARASOFT /afs/rhic/sun4x_56/app/parasoft
	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.solaris
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.solaris)
	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	breaksw 
    default:
	    echo "No parasoft setup  defined for platform $STAR_SYS"
    breaksw
endsw
#___________
