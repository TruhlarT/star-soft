#
# This login has been added for the STAR collaboration.
# it prupose is to replace the multiple layer of HEPIX
# software and avoid loading, sourcing so many level
# of files that mother-duck herself would lose her
# children on the way ....
#
# Written J.Lauret in May 2001.
# Based on some Hepix script content written by A. Taddei
#
# do not do it again, do not even continue
if( $?star_login_csh ) exit
setenv star_login_csh 1


# ------------------------------
# Variables subject to changes
# ------------------------------
# this is kept for compatibility purposes (until I can cleared
# out if it is really necessary or not) but is actually a 
# soft-link to .../star/
setenv GROUP rhstar           
if (! $?GROUP_DIR ) then
    # by testing this, it allows users to have a private copy 
    # for testing purposes by redefining GROUP_DIR
    setenv GROUP_DIR   "/afs/rhic/star/group"
endif


# -------------------------------------
# Intial checks and definitions
# -------------------------------------
# Username defined ? Define it then ... 
if ( ! $?USER ) then
    if ( $?LOGNAME ) then
	setenv USER $LOGNAME
    else
	setenv USER `/usr/bin/whoami`
    endif
endif
if ( ! $?LOGNAME ) then
   setenv LOGNAME $USER
endif


# CHECK FOR LOGIN PERMISSION                          
if ( -f /etc/nologin &&  $USER != root  ) then  
   echo "Sorry but this system is under maintenance. No logins ..."
   /bin/cat /etc/nologin
   /bin/sleep 5
   exec "echo"
   exit
endif


# Set the umask so that newly created files and directories will be 
# readable by others, but writable only by the user.

# Set a minimal path. With this, we will be able to use several
# commands without assuming a path. Temporary setup only ...
if (! $?PATH ) then
    set path=(/usr/bin /bin)
endif
umask 0022
set user=$USER



# May be more. To be extended if needed or
# actually supressed if unused.
setenv OSTYPE `/bin/uname -s`
switch ($OSTYPE)
    case "SunOS":
	set OS="Solaris"
	breaksw
    default:
	set OS=$OSTYPE
	breaksw
endsw
setenv BINTYPE $OS
setenv SYSTYPE sysV




# -------------------------------------
# path path and more paths ...
# -------------------------------------
# This is done stupidly in HEpix. I prefer
if( ! $?X11BIN || ! $?PATH) then
    if( -d /usr/openwin/bin ) then
	# Damned open window systems
	setenv X11BIN  "/usr/openwin/bin"
    endif
    if( -d /usr/bin/X11 ) then
	setenv X11BIN "/usr/bin/X11"
    endif
    if ( -d /usr/X11R6/bin ) then
	setenv X11BIN "/usr/X11R6/bin"
    endif

    set SYSPATH="/usr/bin /bin $X11BIN"
    set ROOTPATH="$X11BIN"
    # Here is a bunch of paths to check for (in reverse order)
    set DIRS="/usr/dt/bin /usr/ccs/bin /usr/ucb /usr/sbin /bin /usr/bin /usr/local/bin/X11 /usr/local/bin"
    foreach tdir ($DIRS)
	if ( -d "$tdir" ) then
	    set ROOTPATH="$tdir $ROOTPATH"
	endif
    end
    set USERPATH="$HOME/bin $HOME/scripts $ROOTPATH /cern/pro/bin ."


    # Support for Globus toolkit
    if ( $?GLOBUS_PATH ) then
	if ( -d /opt/globus/bin ) then 
	    set UGLOBUS="$GLOBUS_PATH /opt/globus/bin"
	else
	    set UGLOBUS=$GLOBUS_PATH
	endif
    else
	set UGLOBUS=""
    endif


    if ( $USER == "root" ) then
	set path=( $ROOTPATH $UGLOBUS)
    else 
	set path=( $USERPATH $UGLOBUS)
    endif
    unset USERPATH
    unset ROOTPATH
    unset UGLOBUS
endif



# Default manpath
if ( -r "/etc/man.config" ) then
   setenv SYSMAN `/bin/awk 'BEGIN{fi=1}/^MANPATH[\t ]/{if(fi==1){printf("%s",$2);fi=0}else{printf(":%s",$2)}}END{printf"\n"}' /etc/man.config`
else
   setenv SYSMAN "/usr/man"
endif
setenv MANPATH "${HOME}/man:${SYSMAN}:/usr/local/man:/cern/man"
setenv XFILESEARCHPATH "/usr/openwin/lib/app-defaults/%N:/usr/lib/X11/app-defaults/%N:/usr/local/lib/X11/app-defaults/%N"
setenv EDITOR      "pico -w"
setenv VISUAL      "pico -w"
setenv LESSCHARSET latin1
setenv WWW_HOME    "http://www.rhic.bnl.gov"
setenv NNTPSERVER  "news.rhic.bnl.gov"
setenv http_proxy  "http://squid1.sec.bnl.local:3128/"
setenv ftp_proxy   "http://192.168.1.3:3128/"
setenv PRINT_CMD   "xprint"

# The folowing instruction also appears in the
# group_login.csh file. One of them will have 
# to go ...
if (-e /usr/local/bin/less ) then
    setenv PAGER       "less"
else
    setenv PAGER       "more"
endif



# CERN stuff
if ( -e /cern ) then
    setenv CERN "/cern"
else 
    # What to do now ...
    if( -e "/afs/rhic/asis/@sys/cern" ) then
	setenv CERN "/afs/rhic/asis/@sys/cern"
    else
	echo "WARNING /cern nor /afs/rhic/asis/@sys/cern exist ..."
    endif
endif
if ($?CERN == 0) setenv CERN "/cern"
if ($?CERN_LEVEL == 0) setenv CERN_LEVEL pro
setenv CERN_ROOT "$CERN/$CERN_LEVEL"



# Is this used ??
setenv INITIALE  `echo $USER | cut -c1`
setenv HPSS_HOME "/hpss/rhic.bnl.gov/user/$INITIALE/$USER"
setenv HSM_HOME  "/hpss/rhic.bnl.gov/user/$INITIALE/$USER"
unsetenv INITIALE


# Set hostname
setenv HOST `/bin/hostname | sed "s/\..*//"`


# In principle, the was a if (-r) on several files here
# only $GROUP_DIR/group_sys.conf.csh was releveant but
# empty. Also, several operation are redundtly done
# (done over and over and re-checked etc ...) so I
# re-grouped things out a bit in hopefully logically
# designed sections.

# Then, we came back one level down to ...
if ( ! -d "$HOME" && -d /homeless ) then
    setenv HOME /homeless
    set home="$HOME"
    cd $HOME
endif



# We partially start the STAR stuff which has always been there
# although we can do further merging and avoid further unecessary
# checks and actions.
if( -r $GROUP_DIR/group_env.csh ) then
    source $GROUP_DIR/group_env.csh
endif


# ** GROUP LOGIN ***> should be merged as well
#if( -r $GROUP_DIR/group_login.csh && $?term ) then
#    source $GROUP_DIR/group_login.csh
#endif
# MERGED now

# Set default mask
umask 022
# Some systems the user doesn't own his tty device 
set ttydev=`tty`
if ("$ttydev" != "") then
    /bin/chmod 622 $ttydev >& /dev/null
endif

# Prepare the scratch disk if not present
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
	# echo No scratch directory available. Using /tmp/$USER ...
	setenv SCRATCH /tmp/$LOGNAME
    endif
    if ( ! -d $SCRATCH ) then
	mkdir $SCRATCH
	chmod 755 $SCRATCH
    endif
    if ($?ECHO) echo   "Setting up SCRATCH   = $SCRATCH"
endif
# <** GROUP LOGIN ENDS. Some parts moved.


# The last part is executed in case
# a user forgets to do it from within is cshrc
if ( ! $?star_cshrc_csh) then
    if ( -e $GROUP_DIR/star_cshrc.csh ) then
	source $GROUP_DIR/star_cshrc.csh
    endif
endif

# Now, display the news if any 
if ($?SILENT == 0 && $?prompt) then
    if ( -f $STAR_PATH/news/motd ) cat $STAR_PATH/news/motd
    if ( -f $STAR_PATH/news/motd.$STAR_SYS ) cat $STAR_PATH/news/motd.$STAR_SYS
endif



