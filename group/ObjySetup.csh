#!/bin/echo You must source

if ( -d $AFS_RHIC/oodb/solaris4/bin ) then
  switch ($STAR_SYS)
    case "i386_*":
      setenv OBJY_HOME $AFS_RHIC/oodb/v_5.1
    breaksw
    case "sun4*":
      setenv OBJY_HOME $AFS_RHIC/oodb/v_5.1
    breaksw
    default:
    breaksw
  endsw
endif

if ( $?OBJY_HOME ) then

if ( ! $?OO_FD_BOOT ) setenv OO_FD_BOOT $STAR_DB/stardb/STAR
if ( ! $?BFWORK ) setenv BFWORK /star/sol/db/StObjy
#if ( $?SILENT == 0 ) echo Objectivity location OBJY_HOME set to $OBJY_HOME
##VP setenv PATH $PATH\:$BFWORK/bin/$BFARCH\:$OBJY_HOME/$OBJY_ARCH/bin
setenv PATH `${GROUP_DIR}/dropit -p $PATH -p $BFWORK/bin/$BFARCH -p $OBJY_HOME/$OBJY_ARCH/bin`

if ( $?BFARCH ) then

  # Variables needed by BaBar software
  setenv BFROOT $AFS_RHIC/star/packages/BaBar
  setenv BFSITE starbnl
  setenv OBJYBASE $OBJY_HOME

  if ( -d $AFS_RHIC/star/packages/stardb/bin/$BFARCH ) then
##VP     setenv PATH $PATH\:$AFS_RHIC/star/packages/stardb/bin/$BFARCH\:$AFS_RHIC/star/packages/stardb/bin/share
    setenv PATH `${GROUP_DIR}/dropit -p $PATH -p $AFS_RHIC/star/packages/stardb/bin/$BFARCH -p $AFS_RHIC/star/packages/stardb/bin/share`
  endif

endif

if (${?LD_LIBRARY_PATH} == 1) then
##VP 	setenv LD_LIBRARY_PATH   $LD_LIBRARY_PATH\:$OBJY_HOME/$OBJY_ARCH/lib
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p $LD_LIBRARY_PATH -p $OBJY_HOME/$OBJY_ARCH/lib`
else
	setenv LD_LIBRARY_PATH   $OBJY_HOME/$OBJY_ARCH/lib
endif

if (${?XAPPLRESDIR} == 1) then
	setenv XAPPLRESDIR	$XAPPLRESDIR\:$OBJY_HOME/$OBJY_ARCH/etc/app-defaults
else
	setenv XAPPLRESDIR	$OBJY_HOME/$OBJY_ARCH/etc/app-defaults
endif

if ( "$?XUSERFILESEARCHPATH" == 0 ) then
  setenv XUSERFILESEARCHPATH "${OBJY_HOME}/${OBJY_ARCH}/etc/app-defaults/%N"
else
##VP   setenv XUSERFILESEARCHPATH "${XUSERFILESEARCHPATH}:${OBJY_HOME}/${OBJY_ARCH}/etc/app-defaults/%N"
  setenv XUSERFILESEARCHPATH `${GROUP_DIR}/dropit -p ${XUSERFILESEARCHPATH} -p ${OBJY_HOME}/${OBJY_ARCH}/etc/app-defaults/%N`
endif

if ( "$?XBMLANGPATH" == 0 ) then
  setenv XBMLANGPATH "${OBJY_HOME}/${OBJY_ARCH}/etc/bitmaps/%N/%B"
else
##VP   setenv XBMLANGPATH "${XBMLANGPATH}:${OBJY_HOME}/${OBJY_ARCH}/etc/bitmaps/%N/%B"
  setenv XBMLANGPATH `${GROUP_DIR}/dropit -p ${XBMLANGPATH} -p ${OBJY_HOME}/${OBJY_ARCH}/etc/bitmaps/%N/%B`
endif

else

#if ( $?SILENT == 0 ) echo "Objectivity not configured, and be thankful for it!"

endif

#end file
