#!/bin/echo You must source

if ( -d /afs/rhic/oodb/solaris4/bin ) then
  switch ($STAR_SYS)
    case "i386_*":
      setenv OBJY_HOME /afs/rhic/oodb/v_5.1
    breaksw
    case "sun4*":
      setenv OBJY_HOME /afs/rhic/oodb/v_5.1
    breaksw
    default:
    breaksw
  endsw
endif

if ( $?OBJY_HOME ) then

if ( ! $?OO_FD_BOOT ) setenv OO_FD_BOOT $STAR_DB/stardb/STAR
if ( ! $?BFWORK ) setenv BFWORK $STAR_DB/StObjy
if ( ! $?BFSTAR ) setenv BFSTAR $STAR_DB/StafObjy

if ( $?SILENT == 0 ) echo Objectivity location OBJY_HOME set to $OBJY_HOME
setenv PATH $PATH\:$BFWORK/bin/$BFARCH\:$OBJY_HOME/$OBJY_ARCH/bin

if ( $?BFARCH ) then

  # Variables needed by BaBar software
  setenv BFROOT /star/sol/packages/BaBar
  setenv BFSITE starbnl
  setenv OBJYBASE $OBJY_HOME

  if ( -d $STAR_DB/bin/$BFARCH ) then
    setenv PATH $PATH\:$STAR_DB/bin/$BFARCH\:$STAR_DB/bin/share
  endif

endif

if (${?LD_LIBRARY_PATH} == 1) then
	setenv LD_LIBRARY_PATH   $LD_LIBRARY_PATH\:$OBJY_HOME/$OBJY_ARCH/lib
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
  setenv XUSERFILESEARCHPATH "${XUSERFILESEARCHPATH}:${OBJY_HOME}/${OBJY_ARCH}/etc/app-defaults/%N"
endif

if ( "$?XBMLANGPATH" == 0 ) then
  setenv XBMLANGPATH "${OBJY_HOME}/${OBJY_ARCH}/etc/bitmaps/%N/%B"
else
  setenv XBMLANGPATH "${XBMLANGPATH}:${OBJY_HOME}/${OBJY_ARCH}/etc/bitmaps/%N/%B"
endif

else

if ( $?SILENT == 0 ) echo "Objectivity not configured, and be thankful for it!"

endif

#end file
