#! /usr/local/bin/tcsh -f
switch ($STAR_SYS)
    case "i386_redhat61":
	setenv PARASOFT /usr/local/app/parasoft
##VP 	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.linux2
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p {$PARASOFT}/lib.linux2`
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.linux2)
##VP 	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p {$PARASOFT}/man`
	breaksw
    case "i386_*":
	setenv PARASOFT /afs/rhic/i386_linux22/app/parasoft
##VP 	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.linux
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p {$PARASOFT}/lib.linux`
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.linux)
##VP 	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p {$PARASOFT}/man`
	breaksw
    case "sun4*":
	setenv PARASOFT /afs/rhic/sun4x_56/app/parasoft
##VP 	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:{$PARASOFT}/lib.solaris
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p {$PARASOFT}/lib.solaris`
	if ( -x /afs/rhic/star/group/dropit) setenv PATH `dropit parasoft`
	set path = ($path $PARASOFT/bin.solaris)
##VP 	setenv MANPATH ${MANPATH}:{$PARASOFT}/man
	setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p {$PARASOFT}/man`
	breaksw 
    default:
	    echo "No parasoft setup  defined for platform $STAR_SYS"
    breaksw
endsw
#___________
