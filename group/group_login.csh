#
#	File:		group_login
#	Purpose:	STAR group initialization 
#			during login.
#	Author:		Y. Fisyak 		BNL
#	Date:		02 Mar 98
#	Modified:
#	STAR software group	1998
#
#
# Set the umask so that newly created files and directories will be readable
# by others, but writable only by the user.
#
umask 022
#
# Following put in to handle NQS
#
if ( $?ENVIRONMENT ) then
	if ( $ENVIRONMENT == "BATCH" ) exit
endif
#
# Determine terminal type
#
set ttype=`echo $term |cut -c1`
switch (x$term)
case x:
case xunknown:
case xarpanet:
case xnetwork:
case xnet:
case xdialup:
case xdumb:
	set term=vt100
	stty erase '^?'
breaksw
default
	if ( -r /usr/lib/terminfo/$ttype/$term || -r /usr/share/lib/terminfo/$ttype/$term ) then
		switch ($term)
		case iris-ansi:	
		case iris-ansi-net:	
		case hp:
			stty erase '^h'
		breaksw
		default
			stty erase '^?'
 		breaksw
		endsw
	else
		set bterm=`echo $term | cut -c1-3`
		if ( -r /usr/lib/terminfo/$ttype/$bterm || -r /usr/share/lib/terminfo/$ttype/$bterm ) then
			set term=$bterm
			stty erase '^?'
		else
			switch ($MACH_OS)
			case IRIX:
			case SunOS:
			case AIX:
				switch ($bterm)
				case vt2:
				case vt3:
					set term=vt220
					stty erase '^?'
				breaksw
				default
					set term=vt100
		 			stty erase '^?'
				breaksw
				endsw
			breaksw
			case ULTRIX:
				switch ($bterm)
				case vt3:
					set term=vt300
					stty erase '^?'
				breaksw
				case vt2:
					set term=vt200
					stty erase '^?'
				breaksw
				default
					set term=vt100
		 			stty erase '^?'
				breaksw
				endsw
			breaksw
			case OSF1:
				switch ($bterm)
				case vt2:
				case vt3:
					stty erase '^?'
				breaksw
				default
					set term=vt100
		 			stty erase '^?'
				breaksw
				endsw
			breaksw
			default
				set term=vt100
		 		stty erase '^?'
			breaksw
			endsw
		endif
	endif
breaksw
endsw
#
# Set DISPLAY
#
if ( ! $?DISPLAY ) then
	set TTYPORT=`tty`
	if ( $TTYPORT == /dev/console ) then
		setenv DISPLAY "localhost:0"
	else if ( $?REMOTEHOST ) then
		setenv DISPLAY "${REMOTEHOST}:0"
	else
		set TTYNAME=`echo $TTYPORT |cut -c6-`
		set REMOTEHOST=`who|grep "$TTYNAME"|awk '{print $6}'|sed 's/(//'|sed 's/)//'`
		if ( x"$REMOTEHOST" != x ) then
			setenv DISPLAY "${REMOTEHOST}:0"
		endif
	endif
endif
#
# Establish PAGER
#
if ( -r /usr/local/bin/less ) then
	setenv PAGER /usr/local/bin/less
else
	setenv PAGER more
endif
#
# Common terminal characteristics
#
stty intr '^c'	# set interrupt key to <ctrl-c>
stty kill '^x'	# set kill key to <ctrl-x>
stty echoe			# erase ERASEd characters
echo "Terminal Type is $TERM"
#
# Some systems the user doesn't own his tty device ( Sun OpenWindows) so
# redirect stderr
#
/bin/chmod 622 `tty` >& /dev/null

if ($?SCRATCH == 0) then
if ( -w /scr20 ) then
        setenv SCRATCH /scr20/$LOGNAME
else if ( -w /scr21 ) then
        setenv SCRATCH /scr21/$LOGNAME
else if ( -w /scr22 ) then
        setenv SCRATCH /scr22/$LOGNAME
else if ( -w /scratch ) then
        setenv SCRATCH /scratch/$LOGNAME
else 
#	echo No scratch directory available. Using /tmp/$USER ...
        setenv SCRATCH /tmp/$LOGNAME
endif
 
if ( ! -d $SCRATCH ) then
        mkdir $SCRATCH
        chmod 755 $SCRATCH
endif
if ($ECHO) echo   "Setting up SCRATCH   = $SCRATCH"
endif
#
# Hot news....
if ( -f $STAR_PATH/news/motd.$SYS_STAR ) cat $STAR_PATH/news/motd.$SYS_STAR
#
#END
