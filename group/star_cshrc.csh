#
# What is here is equivalent to what should be excuted in a cshrc
# i.e. aliases, terminal settings and key bindings.
#
# Note that this file is executed at EACH processes so DO NOT add
# unecessary instructions here.
#
# J.Lauret May 2001
#
setenv star_cshrc_csh 1
if ( ! $?star_login_csh ) then
    # OK. Missing environment variables ... 
    if( -r /afs/rhic/star/group/star_login.csh ) then
	source /afs/rhic/star/group/star_login.csh
    endif
endif


# --------------------------------------------------------------------------------
# Aliases. Backward compatibility only.
# Somehow, I am sure that most of it is unused ...
# I have eliminated the following non-portable commands
#
# alias pp        '/bin/ps auxww | /bin/egrep '\''PID|\!*'\'' | /bin/grep -v grep'
# alias rs        'set noglob;eval `/usr/bin/X11/resize`;unset noglob'
# --------------------------------------------------------------------------------
alias nman       '/usr/bin/nroff -man \!* | $PAGER'
alias ll         '/bin/ls -lA'
alias pwd        'echo $cwd'
alias h          'history'
alias l          'ls -lt'
alias lf         'ls -CF'
alias terminal   'setenv TERM `/usr/bin/tset - \!*`'

# YP fix
if ( -x "/bin/domainname" ) then
    if( ! $?DOMAINNAME) then
	setenv DOMAINNAME `/bin/domainname`
    endif
    if ($DOMAINNAME != "") then
	alias passwd /usr/bin/yppasswd
    endif
endif


# This group file might be merged later on.
if( -r $GROUP_DIR/group_aliases.csh ) then
    source $GROUP_DIR/group_aliases.csh
endif



# -------------------------------------------------
# Now, this is the time to set the tty
# There will be last ultimate call to a group_login
# script which is a file containing commands NOT
# requird in batch mode.
# -------------------------------------------------
/usr/bin/tty -s
if ( $status == 0 ) then
    if ( ! $?ENVIRONMENT ) then
	setenv ENVIRONMENT INTERACTIVE
    else
        if ( $ENVIRONMENT != "DMLOGIN" ) then
	    setenv ENVIRONMENT INTERACTIVE
        endif
    endif


    # Terminal setting. Can be defined in both mode.
    # ls /afs/rhic/star/users/*/.Delete
    # ls /afs/rhic/star/users/*/.BackSpace
    # and same with /star/u did not find anything. I removed
    # support for this (noboddy was apparently aware of it).
    if( ! $?TERM) then
	setenv TERM vt100
        set term=$TERM
    endif
    # Delete mode was /bin/stty erase '^?' intr '^c' kill '^u'
    # BackSpace mode is ...
    stty erase '^h' intr '^c' kill '^u'
    stty echoe -inlcr -istrip -parity
    stty -tostop susp '^z'
    # BTW, the STAR group login does it all again ...


    # support for several su mode
    if ( -o /bin/su ) then
	if($USER == "root") then
	    # root prompt
	    alias setprompt 'set prompt="%m@%.04/# "'
	else
	    # to another user ...
	    alias setprompt 'set prompt="%m@%.04/| "'
	endif
    else
	# user
	alias setprompt 'set prompt="%m@%.04/> "'
    endif


    # support csh/tcsh
    set filec
    set fignore = ( .o .dvi .aux .toc .lot .lof .log .blg .bbl .bak .BAK .sav .old .trace )
    set noclobber               
    set ignoreeof
    set notify
    set savehist=50
    set history=100

    switch ($SHELL)
	case "/usr/local/bin/tcsh":
	case "/bin/tcsh":
	    set correct = cmd
	    set autolist=on
	    set listjobs=long
	    set showdots=on
	    set ellispis=1
	    set histfile=~/.history.$HOST
	    breaksw
	default:
	    breaksw
    endsw

    # key bindings. Not sure I have done this correctly.
    if ($?tcsh) then
	bindkey '^[[1~'  exchange-point-and-mark
	bindkey '^[[2~'  overwrite-mode
	bindkey '^[[3~'  delete-char-or-list
	bindkey '^[[4~'  set-mark-command
	bindkey '^[[5~'  history-search-backward
	bindkey '^[[6~'  history-search-forward
	bindkey '^[Ol'   kill-line
	bindkey '^[Om'   yank
	bindkey '^[On'   set-mark-command
	bindkey '^[Op'   exchange-point-and-mark
	bindkey '^[Oq'   forward-word
	bindkey '^[Or'   spell-line
	bindkey '^[Os'   copy-prev-word
	bindkey '^[Ot'   beginning-of-line
	bindkey '^[Ou'   which-command
	bindkey '^[Ov'   end-of-line
	bindkey '^[Ow'   backward-word
	bindkey '^[Ox'   yank
	bindkey '^[Oy'   kill-region
    endif
 
    # This was taken from HEPIX 100 % as-is
    # Make sure csh.login will be sourced on IRIX
    if ( ! $?SHLVL ) then
       setenv SHLVL 1
    endif   

    setprompt
    alias cd 'chdir \!* && setprompt'

else
    if ( ! $?ENVIRONMENT ) then
	setenv ENVIRONMENT BATCH
    endif
endif 


# One file is not called at all that is
# the group_cshrc . I think it is obsolete
# because what is done there is done in other
# files anyways.

# So, we should be done and OK

