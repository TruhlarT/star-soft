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
setenv GROUP rhstar
if (! $?GROUP_DIR ) then
    # allow users to have a private copy for testing by
    # redefining GROUP_DIR
    setenv GROUP_DIR   "/afs/rhic/$GROUP/group"
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
    set ROOTPATH="$SYSPATH"
    # Here is a bunch of paths to check for (in reverse order)
    set DIRS="/usr/dt/bin /usr/ucb /usr/local/bin"
    foreach tdir ($DIRS)
	if ( -d "$tdir" ) then
	    set ROOTPATH="$tdir $ROOTPATH"
	endif
    end
    set USERPATH="$HOME/bin $HOME/scripts $ROOTPATH /cern/pro/bin ."

    if ( $USER == "root" ) then
	set path=( $ROOTPATH )
    else 
	set path=( $USERPATH )
    endif
    unset USERPATH
    unset ROOTPATH
endif


# Default manpath
if ( -r "/etc/man.config" ) then
   setenv SYSMAN `/bin/awk 'BEGIN{fi=1}/^MANPATH[\t ]/{if(fi==1){printf("%s",$2);fi=0}else{printf(":%s",$2)}}END{printf"\n"}' /etc/man.config`
else
   setenv SYSMAN "/usr/man"
endif
setenv MANPATH "${HOME}/man:${SYSMAN}:/usr/local/man:/cern/man"
setenv XFILESEARCHPATH "/usr/lib/X11/app-defaults/%N:/usr/local/lib/X11/app-defaults/%N"
setenv EDITOR      "pico -w"
setenv VISUAL      "pico -w"
setenv LESSCHARSET latin1
setenv WWW_HOME    "http://www.rhic.bnl.gov"
setenv NNTPSERVER  "news.rhic.bnl.gov"
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
setenv CERN "/cern"
if ($?CERN_LEVEL == 0) setenv CERN_LEVEL pro
setenv CERN_ROOT "$CERN/$CERN_LEVEL"



# Is this used ??
setenv INITIALE  `echo $USER | /usr/bin/cut -c1`
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
if( -r $GROUP_DIR/group_login.csh && $?term ) then
    source $GROUP_DIR/group_login.csh
endif


# The last part is executed in case
# a user forgets to do it from within is cshrc
if ( ! $?star_cshrc_csh) then
    if ( -e $GROUP_DIR/star_cshrc.csh ) then
	source $GROUP_DIR/star_cshrc.csh
    endif
endif




