#!/bin/echo You must source

if ( -d /opt/objy/objy500 ) then
  # sol location
    #  setenv OBJY_HOME /opt/objy/objy500
  # use same location as elsewhere
    setenv OBJY_HOME /afs/rhic/oodb
else
  if ( -d /afs/rhic/oodb ) then
    # other machines
    setenv OBJY_HOME /afs/rhic/oodb
  endif
endif

if ( $?OBJY_HOME ) then

echo Objectivity location OBJY_HOME set to $OBJY_HOME
setenv PATH $PATH\:$OBJY_HOME/$OBJY_ARCH/bin

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

endif

#end file
