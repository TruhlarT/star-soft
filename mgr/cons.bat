@rem = '--*-PERL-*--';
@rem = '
@echo off
rem setlocal
set ARGS=
:loop
if .%1==. goto endloop
set ARGS=%ARGS% %1
shift
goto loop
:endloop
rem ***** This assumes PERL is in the PATH *****
rem $Id: cons.bat,v 1.2 2000/03/14 01:46:57 fisyak Exp $
perl.exe -S cons.bat %ARGS%
goto endofperl
@rem ';

#!/usr/bin/env perl

# Cons: A Software Construction Tool.
# Bob Sidebotham (rns@fore.com), FORE Systems, 1996.
# $Id: cons.bat,v 1.2 2000/03/14 01:46:57 fisyak Exp $

$ver_num = 1.8;
$ver_rev = "-dev";
$version = "This is Cons $ver_num$ver_rev " .
	    '($Id: cons.bat,v 1.2 2000/03/14 01:46:57 fisyak Exp $)'. "\n";

# Copyright (c) 1996-1999 FORE Systems, Inc.	 All rights reserved.

# Permission to use, copy, modify and distribute this software and
# its documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies and
# that both that copyright notice and this permission notice appear
# in supporting documentation, and that the name of FORE Systems, Inc.
# ("FORE Systems") not be used in advertising or publicity pertaining to
# distribution of the software without specific, written prior permission.

# FORE SYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
# INCLUDING ANY WARRANTIES REGARDING INTELLECTUAL PROPERTY RIGHTS AND
# ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.  IN NO EVENT SHALL FORE SYSTEMS BE LIABLE FOR ANY SPECIAL,
# INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

require 5.002;
use integer;
use Cwd;
use File::Copy;
use File::Spec;

#------------------------------------------------------------------
# Determine if running on win32 platform - either Windows NT or 95
#------------------------------------------------------------------

BEGIN {
    $PATH_SEPARATOR = ':';
    $FLAG_CHARACTER = '-';
    $LIB_FLAG_PREFIX = '-L';
    # if the version is 5.003, we can check $^O
    if ($] <  5.003) {
	eval("require Win32");
	$iswin32 = (!$@);
    } else {
	$iswin32 = ($^O eq "MSWin32") ? 1 : 0;
    }
    if ($iswin32) {
	$_WIN32 = 1;
	$PATH_SEPARATOR = ';';
	$FLAG_CHARACTER = '/';
	$LIB_FLAG_PREFIX = '/LIBPATH:';
    }
}

# Flush stdout each time.
$| = 1;

# Seed random number generator.
srand(time . $$); # this works better than time ^ $$ in perlfunc manpage.

$usage = q(
Usage: cons <arguments>

Arguments can be any of the following, in any order:

  <targets>	Build the specified targets. If <target> is a directory
		recursively build everything within that directory.

  +<pattern>	Limit the cons scripts considered to just those that
		match <pattern>. Multiple + arguments are accepted.

  <name>=<val>	Sets <name> to value <val> in the ARG hash passed to the
		top-level Construct file.

  -cc           Show command that would have been executed, when
		retrieving from cache. No indication that the file
		has been retrieved is given; this is useful for
		generating build logs that can be compared with
		real build logs.

  -cd           Disable all caching. Do not retrieve from cache nor
		flush to cache.

  -cr           Build dependencies in random order. This is useful when
		building multiple similar trees with caching enabled.

  -cs           Synchronize existing build targets that are found to be
		up-to-date with cache. This is useful if caching has
		been disabled with -cc or just recently enabled with
		UseCache.

  -d            Enable dependency debugging.

  -f <file>	Use the specified file instead of "Construct" (but first
		change to containing directory of <file>).

  -h            Show a help message local to the current build if
		one such is defined,  and exit.

  -o <file>	Read override file <file>.

  -k		Keep going as far as possible after errors.

  -m            Show cons modification history and exit.

  -p		Show construction products in specified trees.
  -pa		Show construction products and associated actions.
  -pw		Show products and where they are defined.

  -q		Don't be verbose about Installing and Removing targets.

  -wf <file>    Write all filenames considered into <file>.

  -r		Remove construction products associated with <targets>

  -R <repos>	Search for files in <repos>.  Multiple -R <repos>
		directories are searched in the order specified.

  -t            Traverse up the directory hierarchy looking for a
		Construct file, if none exists in the current directory.
		(Targets will be modified to be relative to the
		Construct file.)

  -v		Show cons version and continue processing.
  -V            Show cons version and exit.
  -x		Show this message and exit.

   Please report any bugs/fixes/suggestions through the
   cons-discuss@eng.fore.com mailing list. To subscribe, send mail to
   cons-discuss-request@eng.fore.com with body 'subscribe'.

   User documentation of cons is contained in cons and can be obtained
   by doing 'perldoc /path/to/cons'.

   The Official cons site is: http://www.dsmit.com/cons
);

# Simplify program name, if it is a path.
($vol, $dir, $file) = File::Spec->splitpath($0);
$0 = $file;

# Default parameters.
$param::topfile = 'Construct';	# Top-level construction file.
$param::install = 1;		# Show installations
$param::build = 1;		# Build targets
$param::show = 1;		# Show building of targets.
$param::sigpro = 'md5';		# Signature protocol.
$param::depfile = '';		# Write all deps out to this file
$param::salt = undef;		# Salt derived file signatures with this.
$param::rep_sig_times_ok = 1;	# Repository .consign times are in sync w/files.
$param::quiet = 0;		# should we show the command being executed.

# Display a command while executing or otherwise. This
# should be called by command builder action methods.
sub showcom {
    print($indent . $_[0] . "\n");
}

# Default environment.
@param::defaults = (
     'CC'	    => 'cc',
     'CFLAGS'	    => '',
     'CCCOM'	    => '%CC %CFLAGS %_IFLAGS -c %< -o %>',
     'CXX'          => '%CC',
     'CXXFLAGS'     => '%CFLAGS',
     'CXXCOM'       => '%CXX %CXXFLAGS %_IFLAGS -c %< -o %>',
     'LINK'	    => '%CXX',
     'LINKCOM'	    => '%LINK %LDFLAGS -o %> %< %_LDIRS %LIBS',
     'LINKMODULECOM'=> '%LD -r -o %> %<',
     'AR'	    => 'ar',
     'ARFLAGS'	    => 'r', # rs?
     'ARCOM'	    => "%AR %ARFLAGS %> %<\n%RANLIB %>",
     'RANLIB'	    => 'ranlib',
     'AS'	    => 'as',
     'ASFLAGS'	    => '',
     'ASCOM'	    => '%AS %ASFLAGS %< -o %>',
     'LD'	    => 'ld',
     'LDFLAGS'	    => '',
     'PREFLIB'      => 'lib',
     'SUFLIB'	    => '.a',
     'SUFLIBS'      => '.so:.a',
     'SUFMAP'       => {
	 '.c'  => 'build::command::cc',
	 '.C'  => 'build::command::cc',
	 '.s'  => 'build::command::cc',
	 '.S'  => 'build::command::cc',
	 '.cc' => 'build::command::cc',
	 '.cxx'=> 'build::command::cc',
	 '.cpp'=> 'build::command::cc',
     },
     'SUFOBJ'	    => '.o',
     'ENV'	    => { 'PATH' => '/bin:/usr/bin' },
);

# overrides for Win32
if ($main::_WIN32) {
    # Defined for VC++ 6.0 by Greg Spencer <greg_spencer@acm.org>.
    # Your mileage may vary.
    my @win = (
	'CC'             => 'cl',
	'CFLAGS'         => '/nologo',
	'CCCOM'          => '%CC %CFLAGS %_IFLAGS /c %< /Fo%>',
	'LINK'           => 'link',
	'LINKCOM'        => '%LINK %LDFLAGS /out:%> %< %_LDIRS %LIBS',
	'LINKMODULECOM'  => '%LD /r /o %> %<',
	'AR'             => 'lib',
	'ARFLAGS'        => '/nologo ',
	'ARCOM'          => "%AR %ARFLAGS /out:%> %<",
	'RANLIB'         => '',
	'LD'             => 'link',
	'LDFLAGS'        => '/nologo ',
	'PREFLIB'        => '',
	'SUFEXE'         => '.exe',
	'SUFLIB'         => '.lib',
	'SUFLIBS'        => '.dll:.lib',
	'SUFOBJ'         => '.obj',
    );
    push(@param::defaults, @win);
}

# Handle command line arguments.
while (@ARGV) {
    $_ = shift(@ARGV);
    &option, next			if s/^-//;
    push (@param::include, $_), next	if s/^\+//;
    &equate, next			if /=/;
    push (@targets, $_), next;
}

sub option {
    my %opt = (
		    'cc' =>   sub { $param::cachecom = 1; },
		    'cd' =>   sub { $param::cachedisable = 1; },
		    'cr' =>   sub { $param::random = 1; },
		    'cs' =>   sub { $param::cachesync = 1; },
		    'd' =>    sub { $param::depends = 1; },
		    'h' =>    sub { $param::localhelp = 1; },
		    'k' =>    sub { $param::kflag = 1; },
		    'p' =>    sub { $param::pflag = 1;
				    $param::build = 0; },
		    'pa' =>   sub { $param::pflag = 1;
				    $param::aflag = 1;
				    $indent = "... ";
				    $param::build = 0; },
		    'pw' =>   sub { $param::pflag = 1;
				    $param::wflag = 1;
				    $param::build = 0; },
		    'q' =>    sub { $param::quiet = 1; },
		    'r' =>    sub { $param::rflag = 1;
				    $param::build = 0; },
		    't' =>    sub { $param::traverse = 1; },
		    'v' =>    sub { print($version); },
		    'V' =>    sub { print($version), exit(0); },
		    'x' =>    sub { print($usage), exit 0; },
		);

    my %opt_arg = (
		    'f' =>    sub { $param::topfile = $_[0]; },
		    'o' =>    sub { $param::overfile = $_[0]; },
		    'R' =>    sub { script::Repository($_[0]); },
		    'wf' =>   sub { $param::depfile = $_[0]; },
		);

    if (defined $opt{$_}) {
	$opt{$_}->();
	return;
    }
    $_  =~ m/(.)(.*)/;
    if (defined $opt_arg{$1}) {
	if (! $2) {
	    $_ = shift @ARGV;
	    die("$0: -$1 option requires an argument.\n") if ! $_;
	}
	$opt_arg{$1}->($2 || $_);
	return;
    }
    $_  =~ m/(..)(.*)/;
    if (defined $opt_arg{$1}) {
	if (! $2) {
	    $_ = shift @ARGV;
	    die("$0: -$1 option requires an argument.\n") if ! $_;
	}
	$opt_arg{$1}->($2 || $_);
	return;
    }
    if ($_) {
	die qq($0: unrecognized option "-$_".  Use -x for a usage message.\n);
    }
}

# Process an equate argument (var=val).
sub equate {
    my($var, $val) = /([^=]*)=(.*)/;
    $script::ARG{$var} = $val;
}

# Define file signature protocol.
sig->select($param::sigpro);

# Cleanup after an interrupt.
$SIG{HUP} = $SIG{INT} = $SIG{QUIT} = $SIG{TERM} = sub {
    $SIG{PIPE} = $SIG{HUP} = $SIG{INT} = $SIG{QUIT} = $SIG{TERM} = 'IGNORE';
    warn("\n$0: killed\n");
    # Call this first, to make sure that this processing
    # occurs even if a child process does not die (and we
    # hang on the wait).
    sig::hash::END();
    wait();
    exit(1);
};

# Cleanup after a broken pipe (someone piped our stdout?)
$SIG{PIPE} = sub {
    $SIG{PIPE} = $SIG{HUP} = $SIG{INT} = $SIG{QUIT} = $SIG{TERM} = 'IGNORE';
    warn("\n$0: broken pipe\n");
    sig::hash::END();
    wait();
    exit(1);
};

if ($param::depfile) {
  open (main::DEPFILE, ">".$param::depfile) ||
    die ("$0: couldn't open $param::depfile ($!)\n");
}

# If the supplied top-level Conscript file is not in the
# current directory, then change to that directory.
($vol, $dir, $file) = File::Spec->splitpath($param::topfile);
if ($vol || $dir) {
    my($cd) = File::Spec->catpath($vol, $dir, undef);
    chdir($cd) || die("$0: couldn't change to directory $cd ($!)\n");
    $param::topfile = $file;
}

# Walk up the directory hierarchy looking for a Conscript file (if -t set).
my $target_top;
if ($param::traverse) {
    my $cwd = cwd();
    $target_top = dir::lookupdir(undef, $cwd);
    my $dir = $target_top;
    while (! -f $dir->prefix . $param::topfile) {
	$dir = $dir->up;
	die("$0: unable to find $param::topfile.\n") if ! $dir;
    }
    chdir($dir->path);
    @targets = map(dir::lookup($target_top, $_)->path, @targets);
}

# Set up $dir::top and $dir::cwd, now that we are in the right directory.
dir::init();

# Now handle override file.
package override;
if ($param::overfile) {
    my($ov) = $param::overfile;
    die qq($0: can't read override file "$ov" ($!)\n) if ! -f $ov; #'
    do $ov;
    if ($@) {
	chop($@);
	die qq($0: errors in override file "$ov" ($@)\n);
    }
}

# Provide this to user to setup override patterns.
sub Override {
    my($re, @env) = @_;
    return if $overrides{$re}; # if identical, first will win.
    $param::overrides = 1;
    $param::overrides{$re} = \@env;
    push(@param::overrides, $re);
}

package main;
# Check script inclusion regexps
for $re (@param::include) {
    if (! defined eval {"" =~ /$re/}) {
	my($err) = $@;
	$err =~ s/in regexp at .*$//;
	die("$0: error in regexp $err");
    }
}

# Read the top-level construct file and its included scripts.
doscripts($param::topfile);

# Status priorities. This lets us aggregate status for directories
# and print an appropriate message (at the top-level).
%priority =
    ('none' => 1, 'handled' => 2, 'built' => 3, 'unknown' => 4, 'errors' => 5);

# If no targets were specified, supply default targets (if any).
@targets = @param::default_targets if ! @targets;

# Build the supplied target patterns.
for $tgt (map($dir::top->lookup($_), @targets)) {
    if ($target_top && ! $tgt->is_under($target_top)) {
	# A -t option was used, and this target is not underneath
	# the directory where we were invoked via -t.
	# If the target is a directory and the -t directory
	# is underneath it, then build the -t directory.
	if (ref $tgt ne "dir" || ! $target_top->is_under($tgt)) {
	    next;
	}
	$tgt = $target_top;
    }
    my($status) = buildtarget($tgt);
    if ($status ne 'built') {
	my($path) = $tgt->path;
	if ($status eq "errors") {
	    print qq($0: "$path" not remade because of errors.\n);
	    $errors++;
	} elsif ($status eq "handled") {
	    print qq($0: "$path" is up-to-date.\n);
	} elsif ($status eq "unknown") {
	    # cons error already reported.
	    $errors++;
	} elsif ($status eq "none") {
	    #???
	} else {
	    print qq($0: don't know how to construct "$path".\n"); #'
	    $errors++;
	}
    }
}

exit 0 + ($errors != 0);

# Build the supplied target directory or files. Return aggregated status.
sub buildtarget {
    my($tgt) = @_;
    if (ref($tgt) eq "dir") {
	my($result) = "none";
	my($priority) = $priority{$result};
	if (exists $tgt->{member}) {
	    my($members) = $tgt->{member};
	    for $entry (sort keys %$members) {
		# XXX
		# This manipulation is still operating-system specific,
		# but there's no File::Spec method for hidden files,
		# so leave it alone until we know what cross-OS
		# conventions make sense.
		next if $entry =~ /^\./; # ignore hidden files
		my($tgt) = $members->{$entry};
		next if ref($tgt) eq "file" && !exists($tgt->{builder});
		my($stat) = buildtarget($members->{$entry});
		my($pri) = $priority{$stat};
		if ($pri > $priority) {
		    $priority = $pri;
		    $result = $stat;
		}
	    }
	}
	return $result;
    }
    if ($param::build) {
	return build $tgt;
    } elsif ($param::depends) {
	my($path) = $tgt->path;
	if ($tgt->{builder}) {
	    my(@dep) = (@{$tgt->{dep}}, @{$tgt->{sources}});
	    my($dep) = join(' ',map($_->path, @dep));
	    print("$path: $dep\n");
	} else {
	    print("$path: not a derived file\n");
	}
    } elsif ($param::pflag || $param::wflag || $param::aflag) {
	if ($tgt->{builder}) {
	    if ($param::wflag) {
		print qq(${\$tgt->path}: $tgt->{script}\n);
	    } elsif ($param::pflag) {
		print qq(${\$tgt->path}:\n) if $param::aflag;
		print qq(${\$tgt->path}\n) if !$param::aflag;
	    }
	    if ($param::aflag) {
		$tgt->{builder}->action($tgt);
	    }
	}
    } elsif ($param::rflag && $tgt->{builder}) {
	my($path) = $tgt->path;
	if (-f $path) {
	    if (unlink($path)) {
		print("Removed $path\n") unless ($param::quiet);
	    } else {
		warn("$0: couldn't remove $path\n");
	    }
	}
    }

    return "none";
}

# Support for "building" scripts, importing and exporting variables.
# With the expection of the top-level routine here (invoked from the
# main package by cons), these are all invoked by user scripts.
package script;

# This is called from main to interpret/run the top-level Construct
# file, passed in as the single argument.
sub main::doscripts {
    my($script) = @_;
    Build($script);
    # Now set up the includes/excludes (after the Construct file is read).
    $param::include = join('|', @param::include);

    my(@scripts) = pop(@priv::scripts);
    while ($priv::self = shift(@scripts)) {
	my($path) = $priv::self->{script}->rsrcpath;
	$dir::cwd = $priv::self->{script}->{dir};
	if (-f $path) {
	    do $path;
	    if ($@) {
		chop($@);
		print qq($0: error in file "$path" ($@)\n);
		$run::errors++;
	    } else {
		# Only process subsidiary scripts if no errors in parent.
		unshift(@scripts, @priv::scripts);
	    }
	    undef @priv::scripts;
	} else {
	    warn qq(Ignoring missing script "$path".\n);
	}

# reset "a-zA-Z";# Reset here, to give Construct chance at globals (i.e. %ARG).
# RESET causes a memory corruption problem, with all sorts of bad side effects
# so we've replaced it with the following code.
	my($key,$val);
	while (($key,$val) = each %script::) {
	    local(*priv::script) = $val;
	    undef $priv::script;
	    undef @priv::script;
	    undef %priv::script;
	}
    }
    die("$0: script errors encountered: construction aborted\n") if $run::errors;
}

# Link a directory to another. This simply means set up the *source*
# for the directory to be the other directory.
sub Link {
    my(@paths) = @_;
    my($srcdir) = $dir::cwd->lookupdir(pop @paths)->srcdir;
    map($dir::cwd->lookupdir($_)->{srcdir} = $srcdir, @paths);
}

# Add directories to the repository search path for files.
# We're careful about stripping our current directory from
# the list, which we do by comparing the `pwd` results from
# the current directory and the specified directory.  This
# is cumbersome, but assures that the paths will be reported
# the same regardless of symbolic links.
sub Repository {
    my($my_dir) = Cwd::cwd();
    foreach $dir (@_) {
	my($d) = `$^X -e "use Cwd; chdir('$dir') && print cwd"`;
	next if ! $d || ! -d $d || $d eq $my_dir;
	# We know we can get away with passing undef to lookupdir
	# as the directory because $dir is an absolute path.
	push(@param::rpath, dir::lookupdir(undef, $dir));
	push @INC, $d;
    }
}

# Return the list of Repository directories specified.
sub Repository_List {
    map($_->path, @param::rpath);
}

# Specify whether the .consign signature times in repository files are,
# in fact, consistent with the times on the files themselves.
sub Repository_Sig_Times_OK {
    $param::rep_sig_times_ok = shift;
}

# Specify files/targets that must be present and built locally,
# even if they exist already-built in a Repository.
sub Local {
    my(@files) = map($dir::cwd->lookup($_), @_);
    map($_->local(1), @files);
}

# Export variables to any scripts invoked from this one.
sub Export {
    @{$priv::self->{exports}} = @_;
}

# Import variables from the export list of the caller
# of the current script.
sub Import {
    my($parent) = $priv::self->{parent};
    my($imports) = $priv::self->{imports};
    @{$priv::self->{exports}} = keys %$imports;
    my($var);
    while ($var = shift) {
	if (!exists $imports->{$var}) {
	    my($path) = $parent->{script}->path;
	    die qq($0: variable "$var" not exported by file "$path"\n);
	}
	if (!defined $imports->{$var}) {
	    my($path) = $parent->{script}->path;
	    die qq($0: variable "$var" exported but not defined by file "$path"\n);
	}
	${"script::$var"} = $imports->{$var};
    }
}

# Build an inferior script. That is, arrange to read and execute
# the specified script, passing to it any exported variables from
# the current script.
sub Build {
    my(@files) = map($dir::cwd->lookup($_), @_);
    my(%imports);
    map($imports{$_} = ${"script::$_"}, @{$priv::self->{exports}});
    for $file (@files) {
	next if $param::include && $file->path !~ /$param::include/o;
	my($self) = {'script' => $file,
		     'parent' => $priv::self,
		     'imports' => \%imports};
	bless $self;  # may want to bless into class of parent in future
	push(@priv::scripts, $self);
    }
}

# Set up regexps dependencies to ignore. Should only be called once.
sub Ignore {
    die("Ignore called more than once\n") if $param::ignore;
    $param::ignore = join("|", map("($_)", @_)) if @_;
}

# Specification of default targets.
sub Default {
    push(@param::default_targets, map($dir::cwd->lookup($_)->path, @_));
}

# Local Help.  Should only be called once.
sub Help {
    if ($param::localhelp) {
	print "@_\n";
	exit 2;
    }
}

# Return the build name(s) of a file or file list.
sub FilePath {
    wantarray
	? map($dir::cwd->lookup($_)->path, @_)
	: $dir::cwd->lookup($_[0])->path;
}

# Return the build name(s) of a directory or directory list.
sub DirPath {
    wantarray
	? map($dir::cwd->lookupdir($_)->path, @_)
	: $dir::cwd->lookupdir($_[0])->path;
}

# Split the search path provided into components. Look each up
# relative to the current directory.
# The usual path separator problems abound; for now we'll use :
sub SplitPath {
    my($dirs) = @_;
    if (ref($dirs) ne ARRAY) {
	$dirs = [ split(/$main::PATH_SEPARATOR/o, $dirs) ];
    }
    map { DirPath(@_) } @$dirs;
}

# Return true if the supplied path is available as a source file
# or is buildable (by rules seen to-date in the build).
sub ConsPath {
    my($path) = @_;
    my($file) = $dir::cwd->lookup($path);
    return $file->accessible;
}

# Return the source path of the supplied path.
sub SourcePath {
    my($path) = @_;
    my($file) = $dir::cwd->lookup($path);
    return $file->rsrcpath;
}

# Search up the tree for the specified cache directory, starting with
# the current directory. Returns undef if not found, 1 otherwise.
# If the directory is found, then caching is enabled. The directory
# must be readable and writable. If the argument "mixtargets" is provided,
# then targets may be mixed in the cache (two targets may share the same
# cache file--not recommended).
sub UseCache($@) {
    my($dir, @args) = @_;
    # NOTE: it's important to process arguments here regardless of whether
    # the cache is disabled temporarily, since the mixtargets option affects
    # the salt for derived signatures.
    for (@args) {
	if ($_ eq "mixtargets") {
	    # When mixtargets is enabled, we salt the target signatures.
	    # This is done purely to avoid a scenario whereby if
	    # mixtargets is turned on or off after doing builds, and
	    # if cache synchronization with -cs is used, then
	    # cache files may be shared in the cache itself (linked
	    # under more than one name in the cache). This is not bad,
	    # per se, but simply would mean that a cache cleaning algorithm
	    # that looked for a link count of 1 would never find those
	    # particular files; they would always appear to be in use.
	    $param::salt = 'M' . $param::salt;
	    $param::mixtargets = 1;
	} else {
	    die qq($0: UseCache unrecognized option "$_"\n");
	}
    }
    if ($param::cachedisable) {
	warn("Note: caching disabled by -cd flag\n");
	return 1;
    }
    my($depth) = 15;
    while ($depth-- && ! -d $dir) {
	$dir = File::Spec->catdir(File::Spec->updir, $dir);
    }
    if (-d $dir) {
	$param::cache = $dir;
	return 1;
    }
    return undef;
}

# Salt the signature generator. The salt (a number of string) is added
# into the signature of each derived file. Changing the salt will
# force recompilation of all derived files.
sub Salt($) {
    # We append the value, so that UseCache and Salt may be used
    # in either order without changing the signature calculation.
    $param::salt .= $_[0];
}


# These methods are callable from Conscript files, via a cons
# object. Procs beginning with _ are intended for internal use.
package cons;

# This is passed the name of the base environment to instantiate.
# Overrides to the base environment may also be passed in
# as key/value pairs.
sub new {
    my($package) = shift;
    my ($env) = {@param::defaults, @_};
    @{$env->{_envcopy}} = %$env; # Note: we never change PATH
    $env->{_cwd} = $dir::cwd; # Save directory of environment for
    bless $env, $package;	# any deferred name interpretation.
}

# Clone an environment.
# Note that the working directory will be the initial directory
# of the original environment.
sub clone {
    my($env) = shift;
    my $clone = {@{$env->{_envcopy}}, @_};
    @{$clone->{_envcopy}} = %$clone; # Note: we never change PATH
    $clone->{_cwd} = $env->{_cwd};
    bless $clone, ref $env;
}

# Create a flattened hash representing the environment.
# It also contains a copy of the PATH, so that the path
# may be modified if it is converted back to a hash.
sub copy {
    my($env) = shift;
    (@{$env->{_envcopy}}, 'ENV' => {%{$env->{ENV}}}, @_)
}

# Resolve which environment to actually use for a given
# target. This is just used for simple overrides.
sub _resolve {
    return $_[0] if !$param::overrides;
    my($env, $tgt) = @_;
    my($path) = $tgt->path;
    for $re (@param::overrides) {
	next if $path !~ /$re/;
	# Found one. Return a combination of the original environment
	# and the override.
	my($ovr) = $param::overrides{$re};
	return $envcache{$env,$re} if $envcache{$env,$re};
	my($newenv) = {@{$env->{_envcopy}}, @$ovr};
	@{$newenv->{_envcopy}} = %$env;
	$newenv->{_cwd} = $env->{_cwd};
	return $envcache{$env,$re} = bless $newenv, ref $env;
    }
    return $env;
}

# Substitute construction environment variables into a string.
# Internal function/method.
sub _subst {
    my($env, $str) = @_;
    while ($str =~ s/\%([_a-zA-Z]\w*)/$env->{$1}/ge) {}
    $str;
}

sub Precious {
    my($env) = shift;
    for $file (map($dir::cwd->lookup($_), @_)) {
	$file->{precious} = 1;
    }
}

sub Install {
    my($env) = shift;
    my($tgtdir) = $dir::cwd->lookupdir(shift);
    for $file (map($dir::cwd->lookup($_), @_)) {
	my($tgt) = $tgtdir->lookup($file->{entry});
	$tgt->bind(find build::install, $file);
    }
}

sub InstallAs {
    my $env = shift;
    my $tgt = shift;
    my $src = shift;
    my @sources = ();
    my @targets = ();

    if (ref $tgt) {
	die "InstallAs: Source is a file and target is a list!\n"
	    if (!ref($src));
	@sources = @$src;
	@targets = @$tgt;
    } elsif (ref $src) {
	die "InstallAs: Target is a file and source is a list!\n";
    } else {
	push @sources, $src;
	push @targets, $tgt;
    }

    if ($#sources != $#targets) {
	my $tn = $#targets+1;
	my $sn = $#sources+1;
	die "InstallAs: Source file list ($sn) and target file list ($tn) " .
	    "are inconsistent in length!\n";
    } else {
	foreach (0..$#sources) {
	    my $tfile = $dir::cwd->lookup($targets[$_]);
	    my $sfile = $dir::cwd->lookup($sources[$_]);
	    $tfile->bind(find build::install, $sfile);
	}
    }
}

# Installation in a local build directory,
# copying from the repository if it's already built there.
# Functionally equivalent to:
#	Install $env $dir, $file;
#	Local "$dir/$file";
sub Install_Local {
    my($env) = shift;
    my($tgtdir) = $dir::cwd->lookupdir(shift);
    for $file (map($dir::cwd->lookup($_), @_)) {
	my($tgt) = $tgtdir->lookup($file->{entry});
	$tgt->bind(find build::install, $file);
	$tgt->local(1);
    }
}

sub Objects {
    my($env) = shift;
    map($_->relpath($dir::cwd), _Objects($env, map($dir::cwd->lookup($_), @_)))
}

# Called with multiple source file references (or object files).
# Returns corresponding object files references.
sub _Objects {
    my($env) = shift;
    my($suffix) = $env->{SUFOBJ};
    map(_Object($env, $_, $_->{dir}->lookup($_->base . $suffix)), @_);
}

# Called with an object and source reference.  If no object reference
# is supplied, then the object file is determined implicitly from the
# source file's extension. Sets up the appropriate rules for creating
# the object from the source.  Returns the object reference.
sub _Object {
    my($env, $src, $obj) = @_;
    return $obj if $src eq $obj; # don't need to build self from self.
    my($objenv) = $env->_resolve($obj);
    my($suffix) = $src->suffix;

    my($builder) = $env->{SUFMAP}{$suffix};

    if ($builder) {
	$obj->bind((find $builder($objenv)), $src);
    } else {
	die("don't know how to construct ${\$obj->path} from ${\$src->path}.\n");
    }
    $obj
}

sub Program {
    my($env) = shift;
    my($tgt) = $dir::cwd->lookup(shift);
    my($progenv) = $env->_resolve($tgt);
    $tgt->bind(find build::command::link($progenv, $progenv->{LINKCOM}),
	       $env->_Objects(map($dir::cwd->lookup($_), @_)));
}

sub Module {
    my($env) = shift;
    my($tgt) = $dir::cwd->lookup(shift);
    my($modenv) = $env->_resolve($tgt);
    my($com) = pop(@_);
    $tgt->bind(find build::command::link($modenv, $com),
	       $env->_Objects(map($dir::cwd->lookup($_), @_)));
}

sub LinkedModule {
    my($env) = shift;
    my($tgt) = $dir::cwd->lookup(shift);
    my($progenv) = $env->_resolve($tgt);
    $tgt->bind(find build::command::linkedmodule
	       ($progenv, $progenv->{LINKMODULECOM}),
	       $env->_Objects(map($dir::cwd->lookup($_), @_)));
}

sub Library {
    my($env) = shift;
    my($lib) = $dir::cwd->lookup(file::addsuffix(shift, $env->{SUFLIB}));
    my($libenv) = $env->_resolve($lib);
    $lib->bind(find build::command::library($libenv),
	       $env->_Objects(map($dir::cwd->lookup($_), @_)));
}

# Simple derivation: you provide target, source(s), command.
# Special variables substitute into the rule.
# Target may be a reference, in which case it is taken
# to be a multiple target (all targets built at once).
sub Command {
    my($env) = shift;
    my($tgt) = shift;
    my($com) = pop(@_);
    my(@sources) = map($dir::cwd->lookup($_), @_);
    if (ref($tgt)) {
	# A multi-target command.
	my(@tgts) = map($dir::cwd->lookup($_), @$tgt);
	die("empty target list in multi-target command\n") if !@tgts;
	$env = $env->_resolve($tgts[0]);
	my($builder) = find build::command::user($env, $com);
	my($multi) = build::multiple->new($builder, \@tgts);
	for $tgt (@tgts) {
	    $tgt->bind($multi, @sources);
	}
    } else {
	$tgt = $dir::cwd->lookup($tgt);
	$env = $env->_resolve($tgt);
	my($builder) = find build::command::user($env, $com);
	$tgt->bind($builder, @sources);
    }
}

sub Depends {
    my($env) = shift;
    my($tgt) = $dir::cwd->lookup(shift);
    push(@{$tgt->{dep}}, map($dir::cwd->lookup($_), @_));
}

# Setup a quick scanner for the specified input file, for the
# associated environment. Any use of the input file will cause the
# scanner to be invoked, once only. The scanner sees just one line at
# a time of the file, and is expected to return a list of
# dependencies.
sub QuickScan {
    my($env, $code, $file, $path) = @_;
    $dir::cwd->lookup($file)->{srcscan,$env} =
	find scan::quickscan($code, $env, $path);
}

# Generic builder module. Just a few default methods.  Every derivable
# file must have a builder object of some sort attached.  Usually
# builder objects are shared.
package build;

# Null signature for dynamic includes.
sub includes { () }

# Null signature for build script.
sub script { () }

# Not compatible with any other builder, by default.
sub compatible { 0 }


# Builder module for the Install command.
package build::install;
BEGIN {
    @ISA = qw(build);
    bless $installer = {}    # handle for this class.
}

sub find {
    $installer
}

# Caching not supported for Install: generally install is trivial anyway,
# and we don't want to clutter the cache.
sub cachin { undef }
sub cachout { }

# Do the installation.
sub action {
    my($self, $tgt) = @_;
    my($src) = $tgt->{sources}[0];
    main::showcom("Install ${\$src->rpath} as ${\$tgt->path}")
	if ($param::install && !$param::quiet);
    return unless $param::build;
    futil::install($src->rpath, $tgt);
    return 1;
}


# Builder module for generic UNIX commands.
package build::command;
BEGIN { @ISA = qw(build) }

sub find {
    my($class, $env, $com, $includes) = @_;
    $com = $env->_subst($com);
    $com{$env,$com,$includes} || do {
	# Remove unwanted bits from signature -- those bracketed by %( ... %)
	my($comsig) = $com;
	$comsig =~ s/^\@\s*//mg;
	while ($comsig =~ s/%\(([^%]|%[^\(])*?%\)//g) { }
	my($self) = { env => $env, com => $com, includes => $includes,
		     comsig => $comsig };
	$com{$env,$com,$includes} = bless $self, $class;
    }
}

# Default cache in function.
sub cachin {
    my($self, $tgt, $sig) = @_;
    if (cache::in($tgt, $sig)) {
	if ($param::cachecom) {
	    map { if (! s/^\@\s*//) { main::showcom($_) } } $self->getcoms($tgt);
	} else {
	    printf("Retrieved %s from cache\n", $tgt->path) unless ($param::quiet);
	}
	return 1;
    }
    return undef;
}

# Default cache out function.
sub cachout {
    my($self, $tgt, $sig) = @_;
    cache::out($tgt, $sig);
}

# internal routine to process variable options.
# f: return file part
# F: return file part, but strip any suffix
# d: return directory part
# b: return full path, but strip any suffix (a.k.a. return basename)
# s: return only the suffix (or an empty string, if no suffix is there)
# no option: return full path to file
sub _variant {
    my($opt, $file) = @_;
    if ($opt eq 'f') { return $file->{entry}; }
    elsif ($opt eq 'd') { return $file->{dir}->path; }
    elsif ($opt eq 'F') {
	my $subst = $file->{entry};
	$subst =~ s/\.[^\.]+$//;
	return $subst;
    }
    elsif ($opt eq 'b') {
	my $subst = $file->path;
	$subst =~ s/\.[^\.]+$//;
	return $subst;
    }
    elsif ($opt eq 's') {
	my $subst = $file->{entry};
	$subst =~ m/(\.[^\.]+)$/;
	return $1;
    }
    else { return $file->path; }
}

# For the signature of a basic command, we don't bother
# including the command itself. This is not strictly correct,
# and if we wanted to be rigorous, we might want to insist
# that the command was checked for all the basic commands
# like gcc, etc. For this reason we don't have an includes
# method.

# Call this to get the command line script: an array of
# fully substituted commands.
sub getcoms {
    my($self, $tgt) = @_;
    my(@coms);
    for $com (split(/\n/, $self->{com})) {
	my(@src) = (undef, @{$tgt->{sources}});
	my(@src1) = @src;

	next if $com =~ /^\s*$/;

	# NOTE: we used to have a more elegant s//.../e solution
	# for the items below, but this caused a bus error...

	# Remove %( and %) -- those are only used to bracket parts
	# of the command that we don't depend on.
	$com =~ s/%[()]//g;

	# Deal with %n, n=1,9 and variants.
	while ($com =~ /%([1-9])(:([fdbsF]?))?/) {
	    my($match) = $&;
	    my($src) = $src1[$1];
	    my($subst) = _variant($3, $src1[$1]->rfile);
	    undef $src[$1];
	    $com =~ s/$match/$subst/;
	}

	# Deal with %0 aka %> and variants.
	while ($com =~ /%[0>](:([fdbsF]?))?/) {
	    my($match) = $&;
	    my($subst) = _variant($2, $tgt);
	    $com =~ s/$match/$subst/;
	}

	# Deal with %< (all sources except %n's already used)
	while ($com =~ /%<(:([fdbsF]?))?/) {
	    my($match) = $&;
	    my @list = ();
	    foreach (@src) {
		push(@list, _variant($2, $_->rfile)) if $_;
	    }
	    my($subst) = join(' ', @list);
	    $com =~ s/$match/$subst/;
	}

	# Deal with %[ %].
	$com =~ s{%\[(.*?)%\]}{
	    my($func, @args) = split(/\s/, $1);
	    die("$0: \"$func\" is not defined.\n")
		unless ($self->{env}->{$func});
	    $self->{env}->{$func}->(@args);
	}gex;

	# White space cleanup. XXX NO WAY FOR USER TO HAVE QUOTED SPACES
	$com = join(' ', split(' ', $com));
	next if $com =~ /^:/ && $com !~ /^:\S/;
	push(@coms, $com);
    }
    @coms
}

# Build the target using the previously specified commands.
sub action {
    my($self, $tgt) = @_;
    my($env) = $self->{env};

    if ($param::build) {
	futil::mkdir($tgt->{dir});
	unlink($tgt->path) if ! $tgt->precious;
    }

    # Set environment.
    map(delete $ENV{$_}, keys %ENV);
    %ENV = %{$env->{ENV}};

    # Handle multi-line commands.
    for $com ($self->getcoms($tgt)) {
	if ($com !~ s/^\@\s*//) {
	    main::showcom($com);
	}
	if ($param::build) {

	  #---------------------
	  # Can't fork on Win32
	  #---------------------

	  if ($main::_WIN32) {
	    system($com);
	  } else {
	    my($pid) = fork();
	    die("$0: unable to fork child process ($!)\n") if !defined $pid;
	    if (!$pid) {
	      # This is the child.
	      exec($com);
	      $com =~ s/\s.*//;
	      die qq($0: failed to execute "$com" ($!). )
		. qq(Is this an executable on path "$ENV{PATH}"?\n);
	    }
	    for (;;) {
	      do {} until wait() == $pid;
	      my($b0, $b1 ) = ($? & 0xFF, $? >> 8);
	      # Don't actually see 0177 on stopped process; is this necessary?
	      next if $b0 == 0177; # process stopped; we can wait.
	      if ($b0) {
		my($core, $sig) = ($b0 & 0200, $b0 & 0177);
		my($coremsg) = $core ? "; core dumped" : "";
		$com =~ s/\s.*//;
		my($path) = $tgt->path;
		warn qq($0: *** [$path] $com terminated by signal $sig$coremsg\n);
		return undef;
	      }
	      if ($b1) {
		my($path) = $tgt->path;
		warn qq($0: *** [$path] Error $b1\n); # trying to be like make.
		return undef;
	      }
	      last;
	    }
	  }
	}

	if ($main::_WIN32) {
	  my($err) = $?;
	  if ($err) {
	    my($path) = $tgt->path;
	    warn qq($0: *** [$path] Error $err\n); # trying to be like make.
	    return undef;
	  }
	}
    }

    # success.
    return 1;
}

# Return script signature.
sub script {
    $_[0]->{comsig}
}


# Create a linked module.
package build::command::link;
BEGIN { @ISA = qw(build::command) }

# Find an appropriate linker.
sub find {
    my($class, $env, $command) = @_;
    if (!exists $env->{_LDIRS}) {
	my($ldirs);
	my($wd) = $env->{_cwd};
	my($pdirs) = $env->{LIBPATH};
	if (ref($pdirs) ne 'ARRAY') {
	    $pdirs = [ split(/$main::PATH_SEPARATOR/o, $pdirs) ];
	}
	# On Win32, build library search path as /LIBPATH:A
	# <schwarze@isa.de> 1998-05-13
	# Move its invariant calculation outside the loop
	# <knight@baldmt.com> 1998-09-22
	my($flagprefix) = " ${main::LIB_FLAG_PREFIX}";
	for $dir (map($wd->lookupdir($_), @$pdirs)) {
	    my($dpath) = $dir->path;
	    $ldirs .= $flagprefix . $dpath;
	    next if File::Spec->file_name_is_absolute($dpath);
	    if (@param::rpath) {
		if ($dpath eq File::Spec->curdir) {
		    foreach my $d (map($_->path, @param::rpath)) {
			$ldirs .= $flagprefix . $d;
		    }
		} else {
		    foreach my $d (map($_->path, @param::rpath)) {
			$ldirs .= $flagprefix . File::Spec->catfile($d, $dpath);
		    }
		}
	    }
	}
	$env->{_LDIRS} = "%($ldirs%)";
    }

    # Introduce a new magic _LIBS symbol which allows to use the
    # Unix-style -lNAME syntax for Win32 only. -lNAME will be replaced
    # with %{PREFLIB}NAME%{UFLIB}. <schwarze@isa.de> 1998-06-18

    if ($main::_WIN32 && !exists $env->{_LIBS}) {
	my($libs);
	for $name (split(' ', $env->_subst($env->{LIBS}))) {
	    if ($name =~ /^-l(.*)/) {
		$name = "$env->{PREFLIB}$1$env->{SUFLIB}";
	    }
	    $libs .= ' ' . $name;
	}
	$env->{_LIBS} = "%($libs%)";
    }
    bless find build::command($env, $command);
}

# Called from file::build. Make sure any libraries needed by the
# environment are built, and return the collected signatures
# of the libraries in the path.
sub includes {
    return $_[0]->{sig} if exists $_[0]->{sig};
    my($self, $tgt) = @_;
    my($env) = $self->{env};
    my($ewd) = $env->{_cwd};
    my($ldirs) = $env->{LIBPATH};
    if (ref($ldirs) ne 'ARRAY') {
	$ldirs = [ split(/$main::PATH_SEPARATOR/o, $ldirs) ];
    }
    my(@lpath) = map($ewd->lookupdir($_), @$ldirs);
    my(@sigs);
    my(@names);

    if ($main::_WIN32) {
	# Pass %LIBS symbol through %-substituition
	# <schwarze@isa.de> 1998-06-18
	@names = split(' ', $env->_subst($env->{LIBS}));
    } else {
	@names = split(' ', $env->{LIBS});
    }
    for $name (@names) {
	my($lpath,@allnames);
	if ($name =~ /^-l(.*)/) {
	    # -l style names are looked up on LIBPATH, using all
	    # possible lib suffixes in the same search order the
	    # linker uses (according to SUFLIBS).
	    # Recognize new PREFLIB symbol, which should be 'lib' on
	    # Unix, and empty on Win32. TODO: What about shared
	    # library suffixes?  <schwarze@isa.de> 1998-05-13
	   @allnames = map("$env->{PREFLIB}$1$_",
			   split(/:/, $env->{SUFLIBS}));
	    $lpath = \@lpath;
	} else {
	    @allnames = ($name);
	    # On Win32, all library names are looked up in LIBPATH
	    # <schwarze@isa.de> 1998-05-13
	    if ($main::_WIN32) {
		$lpath = [$dir::top, @lpath];
	    }
	    else {
		$lpath = [$dir::top];
	    }
	}
	DIR: for $dir (@$lpath) {
	    for $n (@allnames) {
		my($lib) = $dir->lookup($n);
		if ($lib->accessible) {
		    last DIR if $lib->ignore;
		    if ((build $lib) eq 'errors') {
			$tgt->{status} = 'errors';
			return undef;
		    }
		    push(@sigs, sig->signature($lib));
		    last DIR;
		}
	    }
	}
    }
    $self->{sig} = sig->collect(@sigs);
}

# Always compatible with other such builders, so the user
# can define a single program or module from multiple places.
sub compatible {
    my($self, $other) = @_;
    ref($other) eq "build::command::link";
}

# Link a program.
package build::command::linkedmodule;

BEGIN { @ISA = qw(build::command) }

# Always compatible with other such builders, so the user
# can define a single linked module from multiple places.
sub compatible {
    my($self, $other) = @_;
    ref($other) eq "build::command::linkedmodule";
}

# Builder for a C module
package build::command::cc;

BEGIN { @ISA = qw(build::command) }

sub find {
    $_[1]->{_cc} || do {
	my($class, $env) = @_;
	my($cscanner) = find scan::cpp($env->{_cwd}, $env->{CPPPATH});
	$env->{_IFLAGS} = "%(" . $cscanner->iflags . "%)";
	my($self) = find build::command($env, $env->{CCCOM});
	$self->{scanner} = $cscanner;
	bless $env->{_cc} = $self;
    }
}

# Invoke the associated	 C scanner to get signature of included files.
sub includes {
    my($self, $tgt) = @_;
    $self->{scanner}->includes($tgt, $tgt->{sources}[0]);
}

# Builder for a user command (cons::Command).  We assume that a user
# command might be built and implement the appropriate dependencies on
# the command itself (actually, just on the first word of the command
# line).
package build::command::user;

BEGIN { @ISA = qw(build::command) }

# XXX Optimize this to not use ignored paths.
sub comsig {
    return $_[0]->{_comsig} if exists $_[0]->{_comsig};
    my($self, $tgt) = @_;
    my($env) = $self->{env};
  com:
    for $com (split(/[\n;]/, $self->script)) {
	# Isolate command word.
	$com =~ s/^\s*//;
	$com =~ s/\s.*//;
	next if !$com; # blank line
	my($pdirs) = $env->{ENV}->{PATH};
	if (ref($pdirs) ne 'ARRAY') {
	    $pdirs = [ split(/$main::PATH_SEPARATOR/o, $pdirs) ];
	}
	for $dir (map($dir::top->lookupdir($_), @$pdirs)) {
	    my($prog) = $dir->lookup($com);
	    if ($prog->accessible) { # XXX Not checking execute permission.
		if ((build $prog) eq 'errors') {
		    $tgt->{status} = 'errors';
		    return undef;
		}
		next com if $prog->ignore;
		$self->{_comsig} .= sig->signature($prog);
		next com;
	    }
	}
	# Not found: let shell give an error.
    }
    $self->{_comsig}
}

sub includes {
    my($self, $tgt) = @_;
    my($sig);

    # Check for any quick scanners attached to source files.
    for $dep (@{$tgt->{dep}}, @{$tgt->{sources}}) {
	my($scanner) = $dep->{srcscan,$self->{env}};
	if ($scanner) {
	    $sig .= $scanner->includes($tgt, $dep);
	}
    }

    # Add the command signature.
    return &comsig . $sig;
}


# Builder for a library module (archive).
# We assume that a user command might be built and implement the
# appropriate dependencies on the command itself.
package build::command::library;

BEGIN { @ISA = qw(build::command) }

sub find {
    my($class, $env) = @_;
    bless find build::command($env, $env->{ARCOM})
}

# Always compatible with other library builders, so the user
# can define a single library from multiple places.
sub compatible {
    my($self, $other) = @_;
    ref($other) eq "build::command::library";
}

# A multi-target builder.
# This allows multiple targets to be associated with a single build
# script, without forcing all the code to be aware of multiple targets.
package build::multiple;

sub new {
    my($class, $builder, $tgts) = @_;
    bless { 'builder' => $builder, 'tgts' => $tgts };
}

sub script {
    my($self, $tgt) = @_;
    $self->{builder}->script($tgt);
}

sub includes {
    my($self, $tgt) = @_;
    $self->{builder}->includes($tgt);
}

sub compatible {
    my($self, $tgt) = @_;
    $self->{builder}->compatible($tgt);
}

sub cachin {
    my($self, $tgt, $sig) = @_;
    $self->{builder}->cachin($tgt, $sig);
}

sub cachout {
    my($self, $tgt, $sig) = @_;
    $self->{builder}->cachout($tgt, $sig);
}

sub action {
    my($self, $invoked_tgt) = @_;
    return $self->{built} if exists $self->{built};

    # Make sure all targets in the group are unlinked before building any.
    my($tgts) = $self->{tgts};
    for $tgt (@$tgts) {
	futil::mkdir($tgt->{dir});
	unlink($tgt->path) if ! $tgt->precious;
    }

    # Now do the action to build all the targets. For consistency
    # we always call the action on the first target, just so that
    # $> is deterministic.
    $self->{built} = $self->{builder}->action($tgts->[0]);

    # Now "build" all the other targets (except for the one
    # we were called with). This guarantees that the signature
    # of each target is updated appropriately. We force the
    # targets to be built even if they have been previously
    # considered and found to be OK; the only effect this
    # has is to make sure that signature files are updated
    # correctly.
    for $tgt (@$tgts) {
	if ($tgt ne $invoked_tgt) {
	    delete $tgt->{status};
	    sig->invalidate($tgt);
	    build $tgt;
	}
    }

    # Status of action.
    $self->{built};
}


# Generic scanning module.
package scan;

# Returns the signature of files included by the specified files on
# behalf of the associated target. Any errors in handling the included
# files are propagated to the target on whose behalf this processing
# is being done. Signatures are cached for each unique file/scanner
# pair.
sub includes {
    my($self, $tgt, @files) = @_;
    my(%files, $file);
    my($inc) = $self->{includes} || ($self->{includes} = {});
    while ($file = pop @files) {
	next if exists $files{$file};
	if ($inc->{$file}) {
	    push(@files, @{$inc->{$file}});
	    $files{$file} = sig->signature($file->rfile);
	} else {
	    if ((build $file) eq 'errors') {
		$tgt->{status} = 'errors'; # tgt inherits build status
		return ();
	    }
	    $files{$file} = sig->signature($file->rfile);
	    my(@includes) = $self->scan($file);
	    $inc->{$file} = \@includes;
	    push(@files, @includes);
	}
    }
    sig->collect(sort values %files)
}


# A simple scanner. This is used by the QuickScanfunction, to setup
# one-time target and environment-independent scanning for a source
# file. Only used for commands run by the Command method.
package scan::quickscan;

BEGIN { @ISA = qw(scan) }

sub find {
    my($class, $code, $env, $path) = @_;
    $scanner{$code,$env,$path} || do {
	my(@path) = map { $dir::cwd->lookupdir($_) } split(/:/, $path);
	my($self) = { code => $code, env => $env, path => \@path };
	$scanner{$code,$env,$path} = bless $self;
    }
}

# Scan the specified file for included file names.
sub scan {
    my($self, $file) = @_;
    my($code) = $self->{code};
    my(@includes);
    # File should have been built by now. If not, we'll ignore it.
    return () unless open(SCAN, $file->rpath);
    local($script::env) = $self->{env};
    while(<SCAN>) {
	push(@includes, &$code);
    }
    close(SCAN);
    my($wd) = $file->{dir};
    my(@files);
    for $name (@includes) {
	for $dir ($file->{dir}, @{$self->{path}}) {
	    my($include) = $dir->lookup($name);
	    if ($include->accessible) {
		push(@files, $include) unless $include->ignore;
		last;
	    }
	}
    }
    @files
}


# CPP (C preprocessor) scanning module
package scan::cpp;

BEGIN { @ISA = qw(scan) }

# For this constructor, provide the include path argument (colon
# separated). Each path is taken relative to the provided directory.

# Note: a particular scanning object is assumed to always return the
# same result for the same input. This is why the search path is a
# parameter to the constructor for a CPP scanning object. We go to
# some pains to make sure that we return the same scanner object
# for the same path: otherwise we will unecessarily scan files.
sub find {
    my($class, $dir, $pdirs) = @_;
    if (ref($pdirs) ne 'ARRAY') {
	$pdirs = [ split(/$main::PATH_SEPARATOR/o, $pdirs) ];
    }
    my(@path) = map($dir->lookupdir($_), @$pdirs);
    my($spath) = "@path";
    $scanner{$spath} || do {
	my($self) = {'path' => \@path};
	$scanner{$spath} = bless $self;
    }
}

# Scan the specified file for include lines.
sub scan {
    my($self, $file) = @_;
    my($angles, $quotes);

    if (exists $file->{angles}) {
	$angles = $file->{angles};
	$quotes = $file->{quotes};
    } else {
	my(@anglenames, @quotenames);
	return () unless open(SCAN, $file->rpath);
	while (<SCAN>) {
	    next unless /^\s*#/;
	    if (/^\s*#\s*include\s*([<"])(.*?)[>"]/) {
		if ($1 eq "<") {
		    push(@anglenames, $2);
		} else {
		    push(@quotenames, $2);
		}
	    }
	}
	close(SCAN);
	$angles = $file->{angles} = \@anglenames;
	$quotes = $file->{quotes} = \@quotenames;
    }


    my(@shortpath) = @{$self->{path}};	  # path for <> style includes
    my(@longpath) = ($file->{dir}, @shortpath); # path for "" style includes

    my(@includes);

    for $name (@$angles) {
	for $dir (@shortpath) {
	    my($include) = $dir->lookup($name);
	    if ($include->accessible) {
		push(@includes, $include) unless $include->ignore;
		last;
	    }
	}
    }

    for $name (@$quotes) {
	for $dir(@longpath) {
	    my($include) = $dir->lookup($name);
	    if ($include->accessible) {
		push(@includes, $include) unless $include->ignore;
		last;
	    }
	}
    }

    return @includes
}

# Return the include flags that would be used for a C Compile.
sub iflags {
    my($self) = @_;
    my($iflags);
    my($dpath);
    # Recognize /I style include directive on Win32
    # <schwarze@isa.de> 1998-05-13
    # Move its invariant calculation outside the loop
    # <knight@baldmt.com> 1998-09-22
    my($flagprefix) = " ${main::FLAG_CHARACTER}I";
    for $dpath (map($_->path, @{$self->{path}})) {
	$iflags .= $flagprefix . $dpath;
	next if File::Spec->file_name_is_absolute($dpath);
	if (@param::rpath) {
	    if ($dpath eq File::Spec->curdir) {
		foreach my $d (map($_->path, @param::rpath)) {
		    $iflags .= $flagprefix . $d;
		}
	    } else {
		foreach my $d (map($_->path, @param::rpath)) {
		    $iflags.= $flagprefix . File::Spec->catfile($d, $dpath);
		}
	    }
	}
    }
    $iflags
}

package File::Spec;

# Some of the File::Spec methods we use are recent additions.
# Provide some rudimentary fall-back methods (probably with some
# hidden UNIX assumptions in them) for people with older modules
# installed.

# We should NOT put a lot of effort into supporting these methods,
# making them portable, etc.  Encourage people to upgrade their
# File::Spec module or their version of Perl instead.

sub _splitpath {
    $_[1] =~ s#^([A-Za-z]:)/#/#;
    my $vol = $1;
    my(@path) = split(/$dir::MATCH_SEPARATOR/, $_[1], -1);
    $file = pop @path;
    push @path, $file if ! $file;
    $dirs = join($dir::SEPARATOR, @path);
    return ($vol, $dirs, $file);
}

sub _splitdir {
    my @dirs = split(/$dir::MATCH_SEPARATOR/, $_[1], -1);
    push(@dirs, '') if $dirs[$#dirs];
    @dirs;
}

sub _catpath {
    $_[0]->catfile(@_[2..$#_]);
}

# Catch these undefined File::Spec methods with AUTOLOAD
# and redirect them to our fall-back methods.

sub AUTOLOAD {
    my %map = (
	splitpath => \&_splitpath,
	splitdir => \&_splitdir,
	catpath => \&_catpath,
    );
    my($func) =$AUTOLOAD;
    $func =~ s/File::Spec:://;
    *$func = $map{$func};	# Arrange for a direct call next time.
    $map{$func}->(@_);
}

# Directory and file handling. Files/dirs are represented by objects.
# Other packages are welcome to add component-specific attributes.
package dir;

BEGIN {
    # A portable way of determing our directory separator.
    $SEPARATOR = File::Spec->catdir('', '');
    $MATCH_SEPARATOR = "\Q$SEPARATOR\E";
}

# Look up a file (but not a directory) in a directory.
# The file may be specified as relative, absolute (starts
# with /), or top-relative (starts with #).
sub lookup {
    my($dir, $entry) = @_;

    # Convert all slashes to the native directory separator.
    # This allows Construct files to always be written with good
    # ol' POSIX path names, regardless of what we're running on.
    $entry =~ s#/#$SEPARATOR#g;

    if ($entry !~ m#$MATCH_SEPARATOR#o) {
	# Fast path: simple entry name in a known directory.
	if ($entry =~ s/^#//) {
	    # Top-relative names begin with #.
	    $dir = $dir::top;
	}
    } else {
	# Portable file name manipulation with File::Spec;
	# lots of comments to explain what's happening and why.
	#
	# File::Spec doesn't understand the Cons convention of
	# an initial '#' for top-relative files.  Strip it.
	my($toprel) = $entry =~ s/^#//;
	my($vol, $directories);
	($vol, $directories, $entry) = File::Spec->splitpath($entry);
	if ($vol || $directories) {
	    # There was at least one separator somewhere in the path.
	    my @dirs = File::Spec->splitdir($directories);

	    # If there was a file entry on the end of the path, then
	    # the last @dirs elemnt is '' and we don't need it.  If
	    # there wasn't a file entry on the end (File::Spec knew
	    # the last component was a directory), then the last @dirs
	    # element becomes the entry we want to look up.
	    my($e) = pop @dirs;
	    $entry ||= $e;

	    # splitdir returns '' as the first array element if it
	    # finds a separator first in the path, so we can test
	    # that to determine if the path name was absolute.
	    # The less-efficient alternative is to pass the original
	    # value of $entry to File::Spec->file_name_is_absolute.
	    if (! $dirs[0]) {
		# The path was absolute.  If no volume was supplied,
		# use the volume of our current directory.
		$vol ||= $cwd_vol;
		if (! $root{$vol}) {
		    # This is our first time looking up a path name
		    # on this volume, so create a root node for it.
		    # (On UNIX systems, $vol is always '', so '/'
		    # always maps to the $root{''} node.)
		    $root{$vol} = {path => $vol.$SEPARATOR,
				prefix => $vol.$SEPARATOR,
				srcpath => $vol.$SEPARATOR,
				'exists' => 1 };
		    $root{$vol}->{srcdir} = $root{$vol};
		    bless $root{$vol};
		}
		if (@dirs <= 1) {
		    # We're in the root directory.  If we're not
		    # looking up a $entry within the root, then they
		    # asked for '/' and we return the node.
		    return $root{$vol} if ! $entry;
		    $dir = $root{$vol};
		} else {
		    # We're looking up something below the root directory.
		    # Strip the initial '/' from the path (the array
		    # slice below) and look it up relative to this
		    # volume's root.
		    $dir = $root{$vol}->lookupdir(File::Spec->catdir(@dirs[1 .. $#dirs]));
		}
	    } else {
		# The path was relative, not absolute.  But there
		# was at least one directory separator there, so
		# we have a directory to look up, either relative
		# to the top (if there was an initial '#') or the
		# current directory (if not).
		if ($toprel) {
		    $dir = $dir::top->lookupdir(File::Spec->catdir(@dirs));
		} else {
		    $dir = $dir->lookupdir(File::Spec->catdir(@dirs));
		}
	    }
	}
    }

    $dir->{member}->{$entry} ||
	bless $dir->{member}->{$entry} =
	    {'entry' => $entry, 'dir' => $dir}, file
}

sub lookupdir {
    $dir::cache{$_[0],$_[1]} || do {
	my($dir) = $dir::cache{$_[0],$_[1]} = &dir::lookup;
	$dir->{member}->{'..'} = $dir->{dir};
	$dir->{member}->{'.'} = $dir;
	bless $dir;
    }
}

# Return the parent directory without doing a lookupdir,
# which would create a parent if it doesn't already exist.
# A return value of undef (! $dir->up) indicates a root directory.
sub up {
    $_[0]->{member}->{'..'};
}

# Return whether this is an entry somewhere underneath the
# specified directory.
sub is_under {
    my $dir = $_[0];
    while ($dir) {
	return 1 if $_[1] == $dir;
	$dir = $dir->up;
    }
    return undef;
}

# Return the relative path from the specified directory ($_[1])
# to the object.  Return undef if this isn't underneath the
# specified directory.
sub relpath {
    my $dir = $_[0];
    my @dirs;
    while ($dir) {
	if ($_[1] == $dir) {
	    if (@dirs < 2) {
		return @dirs[0] || '';
	    } else {
		return File::Spec->catdir(@dirs);
	    }
	}
	unshift(@dirs, $dir->{entry});
	$dir = $dir->up;
    }
    return undef;
}

# Return the path of the directory (file paths implemented
# separately, below).
sub path {
    $_[0]->{path} ||
	($_[0]->{path} = $_[0]->{dir}->prefix . $_[0]->{entry});
}

# Return the pathname as a prefix to be concatenated with an entry.
sub prefix {
    return $_[0]->{prefix} if exists $_[0]->{prefix};
    $_[0]->{prefix} = $_[0]->path . $SEPARATOR;
}

# Return the related source path prefix.
sub srcprefix {
    return $_[0]->{srcprefix} if exists $_[0]->{srcprefix};
    my($srcdir) = $_[0]->srcdir;
    $srcdir->{srcprefix} = $srcdir eq $_[0] ? $srcdir->prefix : $srcdir->srcprefix;
}

# Return the related source directory.
sub srcdir {
    $_[0]->{srcdir} ||
	($_[0]->{srcdir} = $_[0]->{dir}->srcdir->lookupdir($_[0]->{entry}))
}

# Return if the directory is linked to a separate source directory.
sub is_linked {
    $_[0]->{is_linked} ||
	($_[0]->{is_linked} = $_[0]->path ne $_[0]->srcdir->path)
}

sub accessible {
    my $path = $_[0]->path;
    my $err = "$0: you have attempted to use path \"$path\" both as a file " .
	      "and as a directory!\n";
    die $err;
}

sub init {
    my $path = Cwd::cwd();

    # We know we can get away with passing undef to lookupdir
    # as the directory because $dir is an absolute path.
    $top = lookupdir(undef, $path);
    $top->{path} = $top->{srcpath} = File::Spec->curdir;
    $top->{prefix} = '';
    $top->{srcdir} = $top;

    $cwd = $top;

    ($cwd_vol, undef, undef) = File::Spec->splitpath($path);
}


package file;

BEGIN { @ISA = qw(dir) }

# Return the pathname of the file.
# Define this separately from dir::path because we don't want to
# cache all file pathnames (just directory pathnames).
sub path {
    $_[0]->{dir}->prefix . $_[0]->{entry}
}

# Return the related source file path.
sub srcpath {
    $_[0]->{dir}->srcprefix . $_[0]->{entry}
}

# Return if the file is (should be) linked to a separate source file.
sub is_linked {
    $_[0]->{dir}->is_linked
}

# Repository file search.  If the local file exists, that wins.
# Otherwise, return the first existing same-named file under a
# Repository directory.  If there isn't anything with the same name
# under a Repository directory, return the local file name anyway
# so that some higher layer can try to construct it.
sub rfile {
    return $_[0]->{rfile} if exists $_[0]->{rfile};
    my($self) = @_;
    my($rfile) = $self;
    if (@param::rpath) {
	my($path) = $self->path;
	if (! File::Spec->file_name_is_absolute($path) && ! -f $path) {
	    my($dir);
	    foreach $dir (@param::rpath) {
		my($t) = $dir->prefix . $path;
		if (-f $t) {
		    $rfile = $_[0]->lookup($t);
		    $rfile->{is_on_rpath} = 1;
		    last;
		}
	    }
	}
    }
    $self->{rfile} = $rfile;
}

# returns the "precious" status of this file.
sub precious {
    return $_[0]->{precious};
}

# "Erase" reference to a Repository file,
# making this a completely local file object
# by pointing it back to itself.
sub no_rfile {
    $_[0]->{rfile} = $_[0];
}

# Return a path to the first existing file under a Repository directory,
# implicitly returning the current file's path if there isn't a
# same-named file under a Repository directory.
sub rpath {
    $_[0]->{rpath} ||
	($_[0]->{rpath} = $_[0]->rfile->path)
}

# Return a path to the first linked srcpath file under a Repositoy
# directory, implicitly returning the current file's srcpath if there
# isn't a same-named file under a Repository directory.
sub rsrcpath {
    return $_[0]->{rsrcpath} if exists $_[0]->{rsrcpath};
    my($self) = @_;
    my($path) = $self->{rsrcpath} = $self->srcpath;
    if (@param::rpath && ! File::Spec->file_name_is_absolute($path) && ! -f $path) {
	my($dir);
	foreach $dir (@param::rpath) {
	    my($t) = $dir->prefix . $path;
	    if (-f $t) {
		$self->{rsrcpath} = $t;
		last;
	    }
	}
    }
    $self->{rsrcpath};
}

# Return if a same-named file source file exists.
# This handles the interaction of Link and Repository logic.
# As a side effect, it will link a source file from its Linked
# directory (preferably local, but maybe in a repository)
# into a build directory from its proper Linked directory.
sub source_exists {
    return $_[0]->{source_exists} if defined $_[0]->{source_exists};
    my($self) = @_;
    my($path) = $self->path;
    my($time) = (stat($path))[9];
    if ($self->is_linked) {
	# Linked directory, local logic.
	my($srcpath) = $self->srcpath;
	my($srctime) = (stat($srcpath))[9];
	if ($srctime) {
	    if (! $time || $srctime != $time) {
		futil::install($srcpath, $self);
	    }
	    return $self->{source_exists} = 1;
	}
	# Linked directory, repository logic.
	if (@param::rpath) {
	    if ($self != $self->rfile) {
		return $self->{source_exists} = 1;
	    }
	    my($rsrcpath) = $self->rsrcpath;
	    if ($path ne $rsrcpath) {
		my($rsrctime) = (stat($rsrcpath))[9];
		if ($rsrctime) {
		    if (! $time || $rsrctime != $time) {
			futil::install($rsrcpath, $self);
		    }
		    return $self->{source_exists} = 1;
		}
	    }
	}
	# There was no source file in any Linked directory
	# under any Repository.  If there's one in the local
	# build directory, it no longer belongs there.
	if ($time) {
	    unlink($path) || die("$0: couldn't unlink $path ($!)\n");
	}
	return $self->{source_exists} = '';
    } else {
	if ($time) {
	    return $self->{source_exists} = 1;
	}
	if (@param::rpath && $self != $self->rfile) {
	    return $self->{source_exists} = 1;
	}
	return $self->{source_exists} = '';
    }
}

# Return if a same-named derived file exists under a Repository directory.
sub derived_exists {
    $_[0]->{derived_exists} ||
	($_[0]->{derived_exists} = ($_[0] != $_[0]->rfile));
}

# Return if this file is somewhere under a Repository directory.
sub is_on_rpath {
    $_[0]->{is_on_rpath};
}

sub local {
    my($self, $arg) = @_;
    if (defined $arg) {
	$self->{local} = $arg;
    }
    $self->{local};
}

# Return the entry name of the specified file
# without the suffix
sub base {
    my($entry) = $_[0]->{entry};
    $entry =~ s/\.[^\.]*$//;
    $entry;
}

# Return the suffix of the file, for up to a 3 character
# suffix. Anything less returns nothing.
sub suffix {
  if (! $main::_WIN32) {
    $_[0]->{entry} =~ /\.[^\.\/]{0,3}$/;
    $&
  } else {
    @pieces = split(/\./, $_[0]->{entry});
    $suffix = pop(pieces);
    return ".$suffix";
  }
}

# Called as a simple function file::addsuffix(name, suffix)
sub addsuffix {
    my($name, $suffix) = @_;

    if ($suffix && substr($name, -length($suffix)) ne $suffix) {
	return $name .= $suffix;
    }
    $name;
}

# Return true if the file is (or will be) accessible.
# That is, if we can build it, or if it is already present.
sub accessible {
    (exists $_[0]->{builder}) || ($_[0]->source_exists);
}

# Return true if the file should be ignored for the purpose
# of computing dependency information (should not be considered
# as a dependency and, further, should not be scanned for
# dependencies).
sub ignore {
    return 0 if !$param::ignore;
    return $_[0]->{ignore} if exists $_[0]->{ignore};
    $_[0]->{ignore} = $_[0]->path =~ /$param::ignore/o;
}

# Build the file, if necessary.
sub build {
    $_[0]->{status} || &file::_build;
}

sub _build {
    my($self) = @_;
    print main::DEPFILE $self->path, "\n" if param::depfile;
    print((' ' x $level), $self->path, "\n") if $param::depends;
    if (!exists $self->{builder}) {
	# We don't know how to build the file. This is OK, if
	# the file is present as a source file, under either the
	# local tree or a Repository.
	if ($self->source_exists) {
	    return $self->{status} = 'handled';
	} else {
	    my($name) = $self->path;
	    print("$0: don't know how to construct \"$name\"\n");
	    exit(1) unless $param::kflag;
	    return $self->{status} = 'errors'; # xxx used to be 'unknown'
	}
    }

    # An associated build object exists, so we know how to build
    # the file. We first compute the signature of the file, based
    # on its dependendencies, then only rebuild the file if the
    # signature has changed.
    my($builder) = $self->{builder};
    $level += 2;

    my(@deps) = (@{$self->{dep}}, @{$self->{sources}});
    my($rdeps) = \@deps;

    if ($param::random) {
	# If requested, build in a random order, instead of the
	# order that the dependencies were listed.
	my(%rdeps);
	map { $rdeps{$_,'*' x int(rand 10)} = $_ } @deps;
	$rdeps = [values(%rdeps)];
    }

    for $dep (@$rdeps) {
	if ((build $dep) eq 'errors') {
	    # Propagate dependent errors to target.
	    # but try to build all dependents regardless of errors.
	    $self->{status} = 'errors';
	}
    }

    # If any dependents had errors, then we abort.
    if ($self->{status} eq 'errors') {
	$level -= 2;
	return 'errors';
    }

    # Compute the final signature of the file, based on
    # the static dependencies (in order), dynamic dependencies,
    # output path name, and (non-substituted) build script.
    my($sig) = sig->collect(map(sig->signature($_->rfile), @deps),
			    $builder->includes($self),
			    $builder->script);

    # May have gotten errors during computation of dynamic
    # dependency signature, above.
    $level -= 2;
    return 'errors' if $self->{status} eq 'errors';

    if (@param::rpath && $self->derived_exists) {
	# There is no local file of this name, but there is one
	# under a Repository directory.

	if (sig->current($self->rfile, $sig)) {
	    # The Repository copy is current (its signature matches
	    # our calculated signature).
	    if ($self->local) {
		# ...but they want a local copy, so provide it.
		main::showcom("Local copy of ${\$self->path} from ${\$self->rpath}");
		futil::install($self->rpath, $self);
		sig->set($self, $sig);
	    }
	    return $self->{status} = 'handled';
	}

	# The signatures don't match, implicitly because something
	# on which we depend exists locally.  Get rid of the reference
	# to the Repository file; we'll build this (and anything that
	# depends on it) locally.
	$self->no_rfile;
    }

    # Then check for currency.
    if (! sig->current($self, $sig)) {
	# We have to build/derive the file.
	# First check to see if the built file is cached.
	if ($builder->cachin($self, $sig)) {
	    sig->set($self, $sig);
	    return $self->{status} = 'built';
	} elsif ($builder->action($self)) {
	    $builder->cachout($self, $sig);
	    sig->set($self, $sig);
	    return $self->{status} = 'built';
	} else {
	    die("$0: errors constructing ${\$self->path}\n") unless $param::kflag;
	    return $self->{status} = 'errors';
	}
    } else {
	# Push this out to the cache if we've been asked to (-C option).
	# Don't normally do this because it slows us down.
	# In a fully built system, no accesses to the cache directory
	# are required to check any files. This is a win if cache is
	# heavily shared. Enabling this option puts the directory in the
	# loop. Useful only when you wish to recreate a cache from a build.
	if ($param::cachesync) {
	    $builder->cachout($self, $sig);
	    sig->set($self, $sig);
	}
	return $self->{status} = 'handled';
    }
}

# Bind an action to a file, with the specified sources. No return value.
sub bind {
    my($self, $builder, @sources) = @_;
    if ($self->{builder} && !$self->{builder}->compatible($builder)) {
	# Even if not "compatible", we can still check to see if the
	# derivation is identical. It should be identical if the builder is
	# the same and the sources are the same.
	if ("$self->{builder} @{$self->{sources}}" ne "$builder @sources") {
	    $main::errors++;
	    my($path) = $self->path;
	    die("$0: attempt to build ${\$self->path} twice, in different ways!\n");
	}
	return;
    }
    if ($param::wflag) {
	my($lev) = 1;
	my(@frame);
	do {@frame = caller ++$lev} while $frame[3] ne '(eval)';
	@frame = caller --$lev;
	$self->{script} .= "; " if $self->{script};
	$self->{script} .= qq($frame[3] in "$frame[1]", line $frame[2]);
    }
    $self->{builder} = $builder;
    push(@{$self->{sources}}, @sources);
}

sub is_under {
    $_[0]->{dir}->is_under($_[1]);
}

sub relpath {
    my $dirpath = $_[0]->{dir}->relpath($_[1]);
    if (! defined $dirpath) {
	return undef;
    } elsif (! $dirpath) {
	return $_[0]->{entry};
    } else {
	File::Spec->catfile($dirpath, $_[0]->{entry});
    }
}

# File utilities
package futil;

# Install one file as another.
# Links them if possible (hard link), otherwise copies.
# Don't ask why, but the source is a path, the tgt is a file obj.
sub install {
    my($sp, $tgt) = @_;
    my($tp) = $tgt->path;
    return 1 if $tp eq $sp;
    return 1 if eval { link($sp, $tp) };
    unlink($tp);
    if (! futil::mkdir($tgt->{dir})) {
	return undef;
    }
    return 1 if eval { link($sp, $tp) };
    futil::copy($sp, $tp);
}

# Copy one file to another. Arguments are actual file names.
# Returns undef on failure. Preserves mtime and mode.
sub copy {
    my ($sp, $tp) = @_;
    my($mode, $length, $atime, $mtime) = (stat($sp))[2,7,8,9];

# ****XXX Remember to remove before going FCS, if fix is ok ****

#     if (!open(SRC, $sp)) {
#	die("$0: unable to read file $sp ($!)\n");
#	return undef;
#     }
#     if (!open(TGT, ">$tp")) {
#	die("$0: unable to write file $tp ($!)\n");
#	close(SRC);
#	return undef;
#     }

    # Use Perl standard library module for file copying, which handles
    # binary copies. <schwarze@isa.de> 1998-06-18
    if (! File::Copy::copy($sp, $tp)) {
	warn qq($0: can\'t install "$sp" to "$tp" ($!)\n); #'
	return undef;
    }
    if (! utime $atime, $mtime, $tp) {
	warn qq($0: can\'t set modification time for file "$tp" ($!)\n); #'
	return undef;
    }
    if (! chmod $mode, $tp) {
	warn qq($0: can\'t set mode $mode on file "$tp" ($!)\n); #'
	return undef;
    }
    return 1;
}

# Ensure that the specified directory exists.
# Aborts on failure.
sub mkdir {
    return 1 if $_[0]->{exists};
    if (! futil::mkdir($_[0]->{dir})) { # Recursively make parent.
	return undef;
    }
    my($path) = $_[0]->path;
    if (!-d $path && !mkdir($path, 0777)) {
	warn qq($0: can't create directory $path ($!).\n); #'
	return undef;
    }
    $dir->{exists} = 1;
}


# Signature package.
package sig::hash;

sub init {
    my($dir) = @_;
    my($consign) = $dir->prefix . ".consign";
    my($dhash) = $dir->{consign} = {};
    if (-f $consign) {
	open(CONSIGN, $consign) || die("$0: can't open $consign ($!)\n");
	while(<CONSIGN>) {
	    chop;
	    ($file,$sig) = split(/:/,$_);
	    $dhash->{$file} = $sig;
	}
	close(HASH);
    }
    $dhash
}

# Read the hash entry for a particular file.
sub in {
    my($dir) = $_[0]->{dir};
    ($dir->{consign} || init($dir))->{$_[0]->{entry}}
}

# Write the hash entry for a particular file.
sub out {
    my($file, $sig) = @_;
    my($dir) = $file->{dir};
    ($dir->{consign} || init($dir))->{$file->{entry}} = $sig;
    $sig::hash::dirty{$dir} = $dir;
}

# Flush hash entries. Called at end or via ^C interrupt.
sub END {
    return if $called++; # May be called twice.
    close(CONSIGN); # in case this came in via ^C.
    for $dir (values %sig::hash::dirty) {
	my($consign) = $dir->prefix . ".consign";
	my($constemp) = $consign . ".$$";
	if (! open(CONSIGN, ">$constemp")) {
	    die("$0: can't create $constemp ($!)\n");
	}
	my($entry, $sig);
	while (($entry, $sig) = each %{$dir->{consign}}) {
	    if (! print CONSIGN "$entry:$sig\n") {
		die("$0: error writing to $constemp ($!)\n");
	    }
	}
	close(CONSIGN);
	if (! rename($constemp, $consign)) {
	    if (futil::copy($constemp, $consign)) {
		unlink($constemp);
	    } else {
		die("$0: could not rename or copy $constemp to $consign ($!)\n");
	    }
	}
    }
}


# Derived file caching.
package cache;

# Find a file in the cache. Return non-null if the file is in the cache.
sub in {
    return undef unless $param::cache;
    my($file, $sig) = @_;
    # Add the path to the signature, to make it unique.
    $sig = sig->collect($sig, $file->path) unless $param::mixtargets;
    my($dir) = substr($sig, 0, 1);
    my($cp) = File::Spec->catfile($param::cache, $dir, $sig);
    return -f $cp && futil::install($cp, $file);
}

# Try to flush a file to the cache, if not already there.
# If it doesn't make it out, due to an error, then that doesn't
# really matter.
sub out {
    return unless $param::cache;
    my($file, $sig) = @_;
    # Add the path to the signature, to make it unique.
    $sig = sig->collect($sig, $file->path) unless $param::mixtargets;
    my($dir) = substr($sig, 0, 1);
    my($sp) = $file->path;
    my($cp) = File::Spec->catfile($param::cache, $dir, $sig);
    my($cdir) = File::Spec->catfile($param::cache, $dir);
    if (! -d $cdir) {
	mkdir($cdir, 0777) ||
	    die("$0: can't create cache directory $cdir ($!).\n");
    } elsif (-f $cp) {
	# Already cached: try to use that instead, to save space.
	# This can happen if the -cs option is used on a previously
	# uncached build, or if two builds occur simultaneously.
	my($lp) = ".$sig";
	unlink($lp);
	return if ! eval { link($cp, $lp) };
	rename($lp, $sp);
	return;
    }

    return if eval { link($sp, $cp) };
    return if ! -f $sp; # if nothing to cache.
    if (futil::copy($sp, "$cp.new")) {
	rename("$cp.new", $cp);
    }
}


# Generic signature handling
package sig;

sub select {
    my($package, $subclass) = @_;
    @ISA = ("sig::$subclass");
};


# MD5-based signature package.
package sig::md5;

use MD5 1.6;

BEGIN {
    $md5 = new MD5;
}

# Invalidate a cache entry.
sub invalidate {
    delete $_[1]->{sig}
}

# Determine the current signature of an already-existing or
# non-existant file.
sub signature {
    if (defined $_[1]->{sig}) {
	return $_[1]->{sig};
    }
    my ($self, $file) = @_;
    my($path) = $file->path;
    my($time) = (stat($path))[9];
    if ($time) {
	my($sigtime) = sig::hash::in($file);
	if ($file->is_on_rpath) {
	    if ($sigtime) {
		my($htime, $hsig) = split(' ',$sigtime);
		if (! $hsig) {
		    # There was no separate $htime recorded in
		    # the .consign file, which implies that this
		    # is a source file in the repository.
		    # (Source file .consign entries don't record
		    # $htime.)  Just return the signature that
		    # someone else conveniently calculated for us.
		    return $htime;	# actually the signature
		} else {
		    if (! $param::rep_sig_times_ok || $htime == $time) {
			return $file->{sig} = $hsig;
		    }
		}
	    }
	    return $file->{sig} = $file->path . $time;
	}
	if ($sigtime) {
	    my($htime, $hsig) = split(' ',$sigtime);
	    if ($htime == $time) {
		return $file->{sig} = $hsig;
	    }
	}
	if (! File::Spec->file_name_is_absolute($path)) {
	    # A file in the local build directory. Assume we can write
	    # a signature file for it, and compute the actual source
	    # signature. We compute the file based on the build path,
	    # not source path, only because there might be parallel
	    # builds going on... In principle, we could use the source
	    # path and only compute this once.
	    my($sig) = srcsig($path);
	    sig::hash::out($file, $sig);
	    return $file->{sig} = $sig;
	} else {
	    return $file->{sig} = $file->{entry} . $time;
	}
    }
    $file->{sig} = '';
}

# Is the provided signature equal to the signature of the current
# instantiation of the target (and does the target exist)?
sub current {
    my($self, $file, $sig) = @_;
    # Uncomment this to debug checks for signature currency.
    # <knight@baldmt.com> 1998-10-29
#   my $fsig = $self->signature($file); print STDOUT "\$self->signature(${\$file->path}) '$fsig' eq \$sig '$sig'\n"; return $fsig eq $sig;
    $self->signature($file) eq $sig
}

# Store the signature for a file.
sub set {
    my($self, $file, $sig) = @_;
    my($time) = (stat($file->path))[9];
    sig::hash::out($file, "$time $sig");
    $file->{sig} = $sig
}

# Return an aggregate signature
sub collect {
    my($self, @sigs) = @_;
    # The following sequence is faster than calling the hex interface.
    $md5->reset();
    $md5->add(join('', $param::salt, @sigs));

    # Uncomment this to debug dependency signatures.
    # <schwarze@isa.de> 1998-05-08
#   my $buf = join(', ', $param::salt, @sigs); print STDOUT "sigbuf=|$buf|\n";
    # Uncomment this to print the result of dependency signature calculation.
    # <knight@baldmt.com> 1998-10-13
#   $buf = unpack("H*", $md5->digest()); print STDOUT "\t=>|$buf|\n"; return $buf;

    unpack("H*", $md5->digest());
}

# Directly compute a file signature as the MD5 checksum of the
# bytes in the file.
sub srcsig {
    my($path) = @_;
    $md5->reset();
    open(FILE, $path) || die("$0: couldn't read $path ($!)\n");
    $md5->addfile(FILE);
    close(FILE);
    # Uncomment this to print the result of file signature calculation.
    # <knight@baldmt.com> 1998-10-13
#   my $buf = unpack("H*", $md5->digest()); print STDOUT "$path=|$buf|\n"; return $buf;
    unpack("H*", $md5->digest());
}

__END__;

=head1 NAME

Cons - Cons: A Software Construction System

=head1 DESCRIPTION

The original document was automatically derived from the F<cons/cons.html>
by B<html2pod>, thanks to Ulrich Pfiefer. Later revisions were created from
the original.

=head1 B<Cons: A Software Construction System>

by Bob Sidebotham F<rns@fore.com>

A guide and reference for version 1.8-dev

Copyright (c) 1996-1999 FORE Systems, Inc. All rights reserved.

Permission to use, copy, modify and distribute this software and its
documentation for any purpose and without fee is hereby granted, provided
that the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of FORE Systems, Inc. (``FORE Systems'')
not be used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

FORE SYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ANY WARRANTIES REGARDING INTELLECTUAL PROPERTY RIGHTS AND ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. IN NO EVENT SHALL FORE SYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.


=head1 B<Introduction>

B<Cons> is a system for constructing, primarily, software, but is quite
different from previous software construction systems. Cons was designed
from the ground up to deal easily with the construction of software spread
over multiple source directories. Cons makes it easy to create build scripts
that are simple, understandable and maintainable. Cons ensures that complex
software is easily and accurately reproducible.

Cons uses a number of techniques to accomplish all of this. Construction
scripts are just Perl scripts, making them both easy to comprehend and very
flexible. Global scoping of variables is replaced with an import/export
mechanism for sharing information between scripts, significantly improving
the readability and maintainability of each script. B<Construction
environments> are introduced: these are Perl objects that capture the
information required for controlling the build process. Multiple
environments are used when different semantics are required for generating
products in the build tree. Cons implements automatic dependency analysis
and uses this to globally sequence the entire build. Variant builds are
easily produced from a single source tree. Intelligent build subsetting is
possible, when working on localized changes. Overrides can be setup to
easily override build instructions without modifying any scripts. MD5
cryptographic B<signatures> are associated with derived files, and are used
to accurately determine whether a given file needs to be rebuilt.

While offering all of the above, and more, Cons remains simple and easy to
use. This will, hopefully, become clear as you read the remainder of this
document.


=head1 B<Why Cons? Why not Make?>

Cons is a B<make> replacement. In the following paragraphs, we look at a few
of the undesirable characteristics of make--and typical build environments
based on make--that motivated the development of Cons.


=item B<Build complexity>

Traditional make-based systems of any size tend to become quite complex. The
original make utility and its derivatives have contributed to this tendency
in a number of ways. Make is not good at dealing with systems that are
spread over multiple directories. Various work-arounds are used to overcome
this difficulty; the usual choice is for make to invoke itself recursively
for each sub-directory of a build. This leads to complicated code, in which
it is often unclear how a variable is set, or what effect the setting of a
variable will have on the build as a whole. The make scripting language has
gradually been extended to provide more possibilities, but these have
largely served to clutter an already over extended language. Often, builds
are done in multiple passes in order to provide appropriate products from
one directory to another directory. This represents a further increase in
build complexity.


=item B<Build reproducibility >

The bane of all makes has always been the correct handling of
dependencies. Most often, an attempt is made to do a reasonable job of
dependencies within a single directory, but no serious attempt is made to do
the job between directories. Even when dependencies are working correctly,
make's reliance on a simple time stamp comparison to determine whether a
file is out of date with respect to its dependents is not, in general,
adequate for determining when a file should be rederived. If an external
library, for example, is rebuilt and then ``snapped'' into place, the
timestamps on its newly created files may well be earlier than the last
local build, since it was built before it became visible.


=item B<Variant builds>

Make provides only limited facilities for handling variant builds. With the
proliferation of hardware platforms and the need for debuggable
vs. optimized code, the ability to easily create these variants is
essential. More importantly, if variants are created, it is important to
either be able to separate the variants or to be able to reproduce the
original or variant at will. With make it is very difficult to separate the
builds into multiple build directories, separate from the source. And if
this technique isn't used, it's also virtually impossible to guarantee at
any given time which variant is present in the tree, without resorting to a
complete rebuild.


=item B<Repositories>

Make provides only limited support for building software from code that
exists in a central repository directory structure.  The VPATH feature of
GNU make (and some other make implementations) is intended to provide this,
but doesn't work as expected: it changes the path of target file to the
VPATH name too early in its analysis, and therefore searches for all
dependencies in the VPATH directory.  To ensure correct development builds,
it is important to be able to create a file in a local build directory and
have any files in a code repository (a VPATH directory, in make terms) that
depend on the local file get rebuilt properly.  This isn't possible with
VPATH, without coding a lot of complex repository knowledge directly into
the makefiles.


=head1 B<Keeping it simple>

A few of the difficulties with make have been cited above. In this and
subsequent sections, we shall introduce Cons and show how these issues are
addressed.


=item B<Perl scripts>

Cons is Perl-based. That is, Cons scripts--C<Conscript> and C<Construct>
files, the equivalent to C<makefiles>--are all written in Perl. This
provides an immediate benefit: the language for writing scripts is a
familiar one. Even if you don't happen to be a Perl programmer, it helps to
know that Perl is basically just a simple declarative language, with a
well-defined flow of control, and familiar semantics. It has variables that
behave basically the way you would expect them to, subroutines,
flow-of-control, and so on. There is no special syntax introduced for
Cons. The use of Perl as a scripting language simplifies the task of
expressing the appropriate solution to the often complex requirements of a
build.


=item B<Hello, World!>

To ground the following discussion, here's how you could build the B<Hello,
World!> C application with Cons:



  $env = new cons();
  Program $env 'hello', 'hello.c';

If you install this script in a directory, naming the script C<Construct,>
and create the C<hello.c> source file in the same directory, then you can
type C<cons hello> to build the application:



  % cons hello
  cc -c hello.c -o hello.o
  cc -o hello hello.o


=item B<Construction environments>

A key simplification of Cons is the idea of a B<construction environment>. A
construction environment is an B<object> characterized by a set of key/value
pairs and a set of B<methods. >In order to tell Cons how to build something,
you invoke the appropriate method via an appropriate construction
environment. Consider the following example:



  $env = new cons(
	CC	=>	'gcc',
	LIBS	=>	'libworld.a'
  );

  Program $env 'hello', 'hello.c';

In this case, rather than using the default construction environment, as is,
we have overridden the value of C<CC> so that the GNU C Compiler equivalent
is used, instead. Since this version of B<Hello, World!> requires a library,
C<libworld.a>, we have specified that any program linked in this environment
should be linked with that library. If the library exists already, well and
good, but if not, then we'll also have to include the statement:



  Library $env 'libworld', 'world.c';

Now if you type C<cons hello>, the library will be built before the program
is linked, and, of course, C<gcc> will be used to compile both modules:



  % cons hello
  gcc -c hello.c -o hello.o
  gcc -c world.c -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a


=item B<Automatic and complete dependency analysis>

With Cons, dependencies are handled automatically. Continuing the previous
example, note that when we modify C<world.c>, C<world.o> is recompiled,
C<libworld.a> recreated, and C<hello> relinked:



  % touch world.c
  % cons hello
  gcc -c world.c -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a

This is a relatively simple example: Cons ``knows'' world.o depends upon
C<world.c>, because the dependency is explicitly set up by the C<Library>
method. It also knows that C<libworld.a> depends upon C<world.o> and that
C<hello> depends upon C<libworld.a>, all for similar reasons.

Now it turns out that C<hello.c> also includes the interface definition
file, C<world.h>:



  % touch world.h
  % cons hello
  gcc -c hello.c -o hello.o
  gcc -o hello hello.o libworld.a

How does Cons know that C<hello.c> includes C<world.h>, and that C<hello.o>
must therefore be recompiled? For now, suffice it to say that when
considering whether or not C<hello.o> is up-to-date, Cons invokes a scanner
for its dependency, C<hello.c>. This scanner enumerates the files included
by C<hello.c> to come up with a list of further dependencies, beyond those
made explicit by the Cons script. This process is recursive: any files
included by included files will also be scanned.

Isn't this expensive? The answer is--it depends. If you do a full build of a
large system, the scanning time is insignificant. If you do a rebuild of a
large system, then Cons will spend a fair amount of time thinking about it
before it decides that nothing has to be done (although not necessarily more
time than make!). The good news is that Cons makes it very easy to
intelligently subset your build, when you are working on localized changes.


=item B<Automatic global build sequencing>

Because Cons does full and accurate dependency analysis, and does this
globally, for the entire build, Cons is able to use this information to take
full control of the B<sequencing> of the build. This sequencing is evident
in the above examples, and is equivalent to what you would expect for make,
given a full set of dependencies. With Cons, this extends trivially to
larger, multi-directory builds. As a result, all of the complexity involved
in making sure that a build is organized correctly--including multi-pass
hierarchical builds--is eliminated. We'll discuss this further in the next
sections.


=head1 B<Building large trees--still just as simple>


=item B<A hierarchy of build scripts>

A larger build, in Cons, is organized by creating a hierarchy of B<build
scripts>. At the top of the tree is a script called C<Construct>. The rest
of the scripts, by convention, are each called C<Conscript>. These scripts
are connected together, very simply, by the C<Build>, C<Export>, and
C<Import> commands.


=item B<The >B<Build>B< command>

The C<Build> command takes a list of C<Conscript> file names, and arranges
for them to be included in the build. For example:



  Build qw(
	drivers/display/Conscript
	drivers/mouse/Conscript
	parser/Conscript
	utilities/Conscript
  );

This is a simple two-level hierarchy of build scripts: all the subsidiary
C<Conscript> files are mentioned in the top-level C<Construct> file. Notice
that not all directories in the tree necessarily have build scripts
associated with them.

This could also be written as a multi-level script. For example, the
C<Construct> file might contain this command:



  Build qw(
	parser/Conscript
	drivers/Conscript
	utilities/Conscript
  );

and the C<Conscript> file in the C<drivers> directory might contain this:




  Build qw(
	display/Conscript
	mouse/Conscript
  );

Experience has shown that the former model is a little easier to understand,
since the whole construction tree is laid out in front of you, at the
top-level. Hybrid schemes are also possible. A separately maintained
component that needs to be incorporated into a build tree, for example,
might hook into the build tree in one place, but define its own construction
hierarchy.


=item B<Relative, top-relative, and absolute file names>

You may have noticed that the file names specified to the Build command are
relative to the location of the script it is invoked from. This is generally
true for other filename arguments to other commands, too, although we might
as well mention here that if you begin a file name with a hash mark, ``#'',
then that file is interpreted relative to the top-level directory (where the
Construct file resides). And, not surprisingly, if you begin it with ``/'',
then it is considered to be an absolute pathname. This is true even on
systems which use a back slash rather than a forward slash to name absolute
paths.


=item B<Scope of variables>

Each C<Conscript> file, and also the top-level C<Construct> file, begins
life in a separate Perl package. Except for the C<Construct> file, which
gets some of the command line arguments, the symbol table for each script is
empty. All of the variables that are set, therefore, are set by the script
itself--not by some external script. Variables can be explicitly B<imported>
by a script from its parent script. To import a variable, it must have been
B<exported> by the parent and initialized (otherwise an error will
occur). It is therefore possible to determine, from looking at a single
script, exactly where each variable in that script is set.


=item B<The >B<Export>B< command>

The C<Export> command is used as in the following example:



  $ENV = new cons();
  $INCLUDE = "#export/include";
  $LIB = "#export/lib";
  Export qw( ENV INCLUDE LIB );
  Build qw( util/Conscript );

The values of the simple variables mentioned in the C<Export> list will be
squirreled away by any subsequent C<Build> commands. The C<Export> command
will only export PerlB< scalar> variables, that is, variables whose name
begins with C<$>. Other variables, objects, etc. can be exported by
reference--but all scripts will refer to the same object, and this object
should be considered to be read-only by the subsidiary scripts and by the
original exporting script. It's acceptable, however, to assign a new value
to the exported scalar variable--that won't change the underlying variable
referenced. This sequence, for example, is OK:



  $ENV = new cons();
  Export qw( ENV INCLUDE LIB );
  Build qw( util/Conscript );
  $ENV = new cons(CFLAGS => '-O');
  Build qw( other/Conscript );

It doesn't matter whether the variable is set before or after the C<Export>
command. The important thing is the value of the variable at the time the
C<Build> command is executed. This is what gets squirreled away. Any
subsequent C<Export> commands, by the way, invalidate the first: you must
mention all the variables you wish to export on each C<Export> command.


=item B<The >B<Import>B< command>

Variables exported by the C<Export> command can be imported into subsidiary
scripts by the C<Import> command. The subsidiary script always imports
variables directly from the superior script. Consider this example:


  Import qw( ENV INCLUDE );

This is only legal if the parent script exported both C<$ENV> and
C<$INCLUDE>. It also must have given each of these variables values. It is
OK for the subsidiary script to only import a subset of the exported
variables (in this example, C<$LIB>, which was exported by the previous
example, is not imported).

All the imported variables are automatically re-exported, so the sequence:



  Import qw ( ENV INCLUDE );
  Build qw ( beneath-me/Conscript );

will supply both C<$ENV> and C<$INCLUDE> to the subsidiary file. If only
C<$ENV> is to be exported, then the following will suffice:



  Import qw ( ENV INCLUDE );
  Export qw ( ENV );
  Build qw ( beneath-me/Conscript );

Needless to say, the variables may be modified locally before invoking
C<Build> on the subsidiary script.


=item B<Build script evaluation order>

The only constraint on the ordering of build scripts is that superior
scripts are evaluated before their inferior scripts. The top-level
C<Construct> file, for instance, is evaluated first, followed by any
inferior scripts. This is all you really need to know about the evaluation
order, since order is generally irrelevant. Consider the following C<Build>
command:



  Build qw(
	drivers/display/Conscript
	drivers/mouse/Conscript
	parser/Conscript
	utilities/Conscript
  );

We've chosen to put the script names in alphabetical order, simply because
that's the most convenient for maintenance purposes. Changing the order will
make no difference to the build.


=head1 B<A Model for sharing files>


=item B<Some simple conventions>

In any complex software system, a method for sharing build products needs to
be established. We propose a simple set of conventions which are trivial to
implement with Cons, but very effective.

The basic rule is to require that all build products which need to be shared
between directories are shared via an intermediate directory. We have
typically called this C<export>, and, in a C environment, provided
conventional sub-directories of this directory, such as C<include>, C<lib>,
C<bin>, etc.

These directories are defined by the top-level C<Construct> file. A simple
C<Construct> file for a B<Hello, World!> application, organized using
multiple directories, might look like this:



  # Construct file for Hello, World!

  # Where to put all our shared products.
  $EXPORT = '#export';

  Export qw( CONS INCLUDE LIB BIN );



  # Standard directories for sharing products.
  $INCLUDE = "$EXPORT/include";
  $LIB = "$EXPORT/lib";
  $BIN = "$EXPORT/bin";

  # A standard construction environment.
  $CONS = new cons (
	CPPPATH => $INCLUDE,	# Include path for C Compilations
	LIBPATH => $LIB,	# Library path for linking programs
	LIBS => '-lworld',	# List of standard libraries
  );



  Build qw(
	hello/Conscript
	world/Conscript
  );

The C<world> directory's C<Conscript> file looks like this:



  # Conscript file for directory world
  Import qw( CONS INCLUDE LIB );



  # Install the products of this directory
  Install $CONS $LIB, 'libworld.a';
  Install $CONS $INCLUDE, 'world.h';



  # Internal products
  Library $CONS 'libworld.a', 'world.c';

and the C<hello> directory's C<Conscript> file looks like this:



  # Conscript file for directory hello
  Import qw( CONS BIN );

  # Exported products
  Install $CONS $BIN, 'hello';

  # Internal products
  Program $CONS 'hello', 'hello.c';

To construct a B<Hello, World!> program with this directory structure, go to
the top-level directory, and invoke C<cons> with the appropriate
arguments. In the following example, we tell Cons to build the directory
C<export>. To build a directory, Cons recursively builds all known products
within that directory (only if they need rebuilding, of course). If any of
those products depend upon other products in other directories, then those
will be built, too.



  % cons export
  Install world/world.h as export/include/world.h
  cc -Iexport/include -c hello/hello.c -o hello/hello.o
  cc -Iexport/include -c world/world.c -o world/world.o
  ar r world/libworld.a world/world.o
  ar: creating world/libworld.a
  ranlib world/libworld.a
  Install world/libworld.a as export/lib/libworld.a
  cc -o hello/hello hello/hello.o -Lexport/lib -lworld
  Install hello/hello as export/bin/hello


=item B<Clean, understandable, location-independent scripts>

You'll note that the two C<Conscript> files are very clean and
to-the-point. They simply specify products of the directory and how to build
those products. The build instructions are minimal: they specify which
construction environment to use, the name of the product, and the name of
the inputs. Note also that the scripts are location-independent: if you wish
to reorganize your source tree, you are free to do so: you only have to
change the C<Construct> file (in this example), to specify the new locations
of the C<Conscript> files. The use of an export tree makes this goal easy.

Note, too, how Cons takes care of little details for you. All the C<export>
directories, for example, were made automatically. And the installed files
were really hard-linked into the respective export directories, to save
space and time. This attention to detail saves considerable work, and makes
it even easier to produce simple, maintainable scripts.


=head1 B<Separating source and build trees>

It's often desirable to keep any derived files from the build completely
separate from the source files. This makes it much easier to keep track of
just what is a source file, and also makes it simpler to handle B<variant>
builds, especially if you want the variant builds to co-exist.


=item B<Separating build and source directories using the >B<Link>B< command>

Cons provides a simple mechanism that handles all of these requirements. The
C<Link> command is invoked as in this example:



  Link 'build' => 'src';

The specified directories are ``linked'' to the specified source
directory. Let's suppose that you setup a source directory, C<src>, with the
sub-directories C<world> and C<hello> below it, as in the previous
example. You could then substitute for the original build lines the
following:



  Build qw(
	build/world/Conscript
	build/hello/Conscript
  );

Notice that you treat the C<Conscript> file as if it existed in the build
directory. Now if you type the same command as before, you will get the
following results:



  % cons export
  Install build/world/world.h as export/include/world.h
  cc -Iexport/include -c build/hello/hello.c -o build/hello/hello.o
  cc -Iexport/include -c build/world/world.c -o build/world/world.o
  ar r build/world/libworld.a build/world/world.o
  ar: creating build/world/libworld.a
  ranlib build/world/libworld.a
  Install build/world/libworld.a as export/lib/libworld.a
  cc -o build/hello/hello build/hello/hello.o -Lexport/lib -lworld
  Install build/hello/hello as export/bin/hello

Again, Cons has taken care of the details for you. In particular, you will
notice that all the builds are done using source files and object files from
the build directory. For example, C<build/world/world.o> is compiled from
C<build/world/world.c>, and C<export/include/world.h> is installed from
C<build/world/world.h>. This is accomplished on most systems by the simple
expedient of ``hard'' linking the required files from each source directory
into the appropriate build directory.

The links are maintained correctly by Cons, no matter what you do to the
source directory. If you modify a source file, your editor may do this ``in
place'' or it may rename it first and create a new file. In the latter case,
any hard link will be lost. Cons will detect this condition the next time
the source file is needed, and will relink it appropriately.

You'll also notice, by the way, that B<no> changes were required to the
underlying C<Conscript> files. And we can go further, as we shall see in the
next section.


=head1 B<Variant builds>


=item B<Hello, World!>B< for baNaNa and peAcH OS's>

Variant builds require just another simple extension. Let's take as an
example a requirement to allow builds for both the baNaNa and peAcH
operating systems. In this case, we are using a distributed file system,
such as NFS to access the particular system, and only one or the other of
the systems has to be compiled for any given invocation of C<cons>. Here's
one way we could set up the C<Construct> file for our B<Hello, World!>
application:



  # Construct file for Hello, World!

  die qq(OS must be specified) unless $OS = $ARG{OS};
  die qq(OS must be "peach" or "banana")
	if $OS ne "peach" && $OS ne "banana";



  # Where to put all our shared products.
  $EXPORT = "#export/$OS";

  Export qw( CONS INCLUDE LIB BIN );

  # Standard directories for sharing products.
  $INCLUDE = "$EXPORT/include";
  $LIB = "$EXPORT/lib";
  $BIN = "$EXPORT/bin";

  # A standard construction environment.
  $CONS = new cons (
	CPPPATH => $INCLUDE,	# Include path for C Compilations
	LIBPATH => $LIB,	# Library path for linking programs
	LIBS => '-lworld',	# List of standard libraries
  );



  # $BUILD is where we will derive everything.
  $BUILD = "#build/$OS";



  # Tell cons where the source files for $BUILD are.
  Link $BUILD => 'src';

  Build (
	"$BUILD/hello/Conscript",
	"$BUILD/world/Conscript",
  );

Now if we login to a peAcH system, we can build our B<Hello, World!>
application for that platform:



  % cons export OS=peach
  Install build/peach/world/world.h as export/peach/include/world.h
  cc -Iexport/peach/include -c build/peach/hello/hello.c -o build/peach/hello/hello.o
  cc -Iexport/peach/include -c build/peach/world/world.c -o build/peach/world/world.o
  ar r build/peach/world/libworld.a build/peach/world/world.o
  ar: creating build/peach/world/libworld.a
  ranlib build/peach/world/libworld.a
  Install build/peach/world/libworld.a as export/peach/lib/libworld.a
  cc -o build/peach/hello/hello build/peach/hello/hello.o -Lexport/peach/lib -lworld
  Install build/peach/hello/hello as export/peach/bin/hello


=item B<Variations on a theme>

Other variations of this model are possible. For example, you might decide
that you want to separate out your include files into platform dependent and
platform independent files. In this case, you'd have to define an
alternative to C<$INCLUDE> for platform-dependent files. Most C<Conscript>
files, generating purely platform-independent include files, would not have
to change.

You might also want to be able to compile your whole system with debugging
or profiling, for example, enabled. You could do this with appropriate
command line options, such as C<DEBUG=on>. This would then be translated
into the appropriate platform-specific requirements to enable debugging
(this might include turning off optimization, for example). You could
optionally vary the name space for these different types of systems, but, as
we'll see in the next section, it's not B<essential> to do this, since Cons
is pretty smart about rebuilding things when you change options.


=head1 B<Signatures>


=item B<MD5 cryptographic signatures>

Whenever Cons creates a derived file, it stores a B<signature> for that
file. The signature is stored in a separate file, one per directory. After
the previous example was compiled, the C<.consign> file in the
C<build/peach/world> directory looked like this:



  world.o:834179303 23844c0b102ecdc0b4548d1cd1cbd8c6
  libworld.a:834179304 9bf6587fa06ec49d864811a105222c00

The first number is a timestamp--for a UNIX systems, this is typically the
number of seconds since January 1st, 1970. The second value is an MD5
checksum. The B<Message Digest Algorithm> is an algorithm that, given an
input string, computes a strong cryptographic signature for that string. The
MD5 checksum stored in the C<.consign> file is, in effect, a digest of all
the dependency information for the specified file. So, for example, for the
file C<world.o>, this includes at least the file C<world.c>, and also any
header files that Cons knows about that are included, directly or indirectly
by C<world.c>. Not only that, but the actual command line that was used to
generate C<world.o> is also fed into the computation of the
signature. Similarly, C<libworld.a> gets a signature which ``includes'' all
the signatures of its constituents (and hence, transitively, the signatures
of B<their> constituents), as well as the command line that created the
file.

The signature of a non-derived file is computed, by default, by taking the
current modification time of the file and the file's entry name (unless
there happens to be a current C<.consign> entry for that file, in which case
that signature is used).

Notice that there is no need for a derived file to depend upon any
particular C<Construct> or C<Conscript> file--if changes to these files
affect the file in question, then this will be automatically reflected in
its signature, since relevant parts of the command line are included in the
signature. Unrelated changes will have no effect.

When Cons considers whether to derive a particular file, then, it first
computes the expected signature of the file. It then compares the file's
last modification time with the time recorded in the C<.consign> entry, if
one exists. If these times match, then the signature stored in the
C<.consign> file is considered to be accurate. If the file's previous
signature does not match the new, expected signature, then the file must be
rederived.

Notice that a file will be rederived whenever anything about a dependent
file changes. In particular, notice that B<any> change to the modification
time of a dependent (forward or backwards in time) will force recompilation
of the derived file.

The use of these signatures is an extremely simple, efficient, and effective
method of improving--dramatically--the reproducibility of a system.

We'll demonstrate this with a simple example:



  # Simple "Hello, World!" Construct file
  $CFLAGS = '-g' if $ARG{DEBUG} eq 'on';
  $CONS = new cons(CFLAGS => $CFLAGS);
  Program $CONS 'hello', 'hello.c';

Notice how Cons recompiles at the appropriate times:



  % cons hello
  cc -c hello.c -o hello.o
  cc -o hello hello.o
  % cons hello
  cons: "hello" is up-to-date.
  % cons DEBUG=on hello
  cc -g -c hello.c -o hello.o
  cc -o hello hello.o
  % cons DEBUG=on hello
  cons: "hello" is up-to-date.
  % cons hello
  cc -c hello.c -o hello.o
  cc -o hello hello.o


=head1 B<Code Repositories>

Many software development organizations will have one or more central
repository directory trees containing the current source code for one or
more projects, as well as the derived object files, libraries, and
executables.  In order to reduce unnecessary recompilation, it is useful to
use files from the repository to build development software--assuming, of
course, that no newer dependency file exists in the local build tree.


=item B<Repository>

Cons provides a mechanism to specify a list of code repositories that will
be searched, in-order, for source files and derived files not found in the
local build directory tree.

The following lines in a C<Construct> file will instruct Cons to look first
under the C</usr/experiment/repository> directory and then under the
C</usr/product/repository> directory:

  Repository qw (
	/usr/experiment/repository
	/usr/product/repository
  );

The repository directories specified may contain source files, derived files
(objects, libraries and executables), or both.  If there is no local file
(source or derived) under the directory in which Cons is executed, then the
first copy of a same-named file found under a repository directory will be
used to build any local derived files.

Cons maintains one global list of repositories directories.  Cons will
eliminate the current directory, and any non-existent directories, from the
list.


=item B<Finding the Construct file in a Repository>

Cons will also search for C<Construct> and C<Conscript> files in the
repository tree or trees.  This leads to a chicken-and-egg situation,
though: how do you look in a repository tree for a C<Construct> file if the
C<Construct> file tells you where the repository is?  To get around this,
repositories may be specified via C<-R> options on the command line:

  % cons -R /usr/experiment/repository -R /usr/product/repository .

Any repository directories specified in the C<Construct> or C<Conscript>
files will be appended to the repository directories specified by
command-line C<-R> options.

=item B<Repository source files>

If the source code (include the C<Conscript> file) for the library version
of the I<Hello, World!> C application is in a repository (with no derived
files), Cons will use the repository source files to create the local object
files and executable file:

  % cons -R /usr/src_only/repository hello
  gcc -c /usr/src_only/repository/hello.c -o hello.o
  gcc -c /usr/src_only/repository/world.c -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a

Creating a local source file will cause Cons to rebuild the appropriate
derived file or files:

  % touch world.c
  % cons -R /usr/src_only/repository hello
  gcc -c world.c -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a

And removing the local source file will cause Cons to revert back to
building the derived files from the repository source:

  % touch -R /usr/src_only/repository hello world.c
  % cons hello
  gcc -c /usr/src_only/world.c/repository -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a


=item B<Repository derived files>

If a repository tree contains derived files (usually object files,
libraries, or executables), Cons will perform its normal signature
calculation to decide whether the repository file is up-to-date or a derived
file must be built locally.  This means that, in order to ensure correct
signature calculation, a repository tree must also contain the C<.consign>
files that were created by Cons when generating the derived files.

This would usually be accomplished by building the software in the
repository (or, alternatively, in a build directory, and then copying the
result to the repository):

  % cd /usr/all/repository
  % cons hello
  gcc -c hello.c -o hello.o
  gcc -c world.c -o world.o
  ar r libworld.a world.o
  ar: creating libworld.a
  ranlib libworld.a
  gcc -o hello hello.o libworld.a

(This is safe even if the C<Construct> file lists the C</usr/all/repository>
directory in a C<Repository> command because Cons will remove the current
directory from the repository list.)

Now if we want to build a copy of the application with our own C<hello.c>
file, we only need to create the one necessary source file, and use the
C<-R> option to have Cons use other files from the repository:

  % mkdir $HOME/build1
  % cd $HOME/build1
  % touch hello.c
  % cons -R /usr/all/repository hello
  gcc -c hello.c -o hello.o
  gcc -o hello hello.o /usr/all/repository/libworld.a

Notice that Cons has not bothered to recreate a local C<libworld.a> library
(or recompile the C<world.o> module), but instead uses the already-compiled
version from the repository.

Because the MD5 signatures that Cons puts in the C<.consign> file contain
timestamps for the derived files, the signature timestamps must match the
file timestamps for a signature to be considered valid.

Some software systems may alter the timestamps on repository files (by
copying them, e.g.), in which case Cons will, by default, assume the
repository signatures are invalid and rebuild files unnecessarily.  This
behavior may be altered by specifying:

  Repository_Sig_Times_OK 0;

This tells Cons to ignore timestamps when deciding whether a signature is
valid.  (Note that avoiding this sanity check means there must be proper
control over the repository tree to ensure that the derived files cannot be
modified without updating the C<.consign> signature.)


=item B<Local copies of files>

If the repository tree contains the complete results of a build, and we try
to build from the repository without any files in our local tree, something
moderately surprising happens:

  % mkdir $HOME/build2
  % cd $HOME/build2
  % cons -R /usr/all/repository hello
  cons: "hello" is up-to-date.

Why does Cons say that the C<hello> program is up-to-date when there is no
C<hello> program in the local build directory?  Because the repository (not
the local directory) contains the up-to-date C<hello> program, and Cons
correctly determines that nothing needs to be done to rebuild this
up-to-date copy of the file.

There are, however, many times in which it is appropriate to ensure that a
local copy of a file always exists.  A packaging or testing script, for
example, may assume that certain generated files exist locally Instead of
making these subsidiary scripts aware of the repository directory, the
C<Local> command may be added to a C<Construct> or C<Conscript> file to
specify that a certain file or files must appear in the local build
directory:

  Local qw(
	hello
  );

Then, if we re-run the same command, Cons will make a local copy of the
program from the repository copy (telling you that it is doing so):

  % cons -R /usr/all/repository hello
  Local copy of hello from /usr/all/repository/hello
  cons: "hello" is up-to-date.

Notice that, because the act of making the local copy is not considered a
"build" of the C<hello> file, Cons still reports that it is up-to-date.

Creating local copies is most useful for files that are being installed into
an intermediate directory (for sharing with other directories) via the
C<Install> command.  Accompanying the C<Install> command for a file with a
companion C<Local> command is so common that Cons provides a
C<Install_Local> command as a convenient way to do both:

  Install_Local $env, '#export', 'hello';

is exactly equivalent to:

  Install $env '#export', 'hello';
  Local '#export/hello';

Both the C<Local> and C<Install_Local> commands update the local C<.consign>
file with the appropriate file signatures, so that future builds are
performed correctly.


=item B<Repository dependency analysis>

Due to its built-in scanning, Cons will search the specified repository
trees for included C<.h> files.  Unless the compiler also knows about the
repository trees, though, it will be unable to find C<.h> files that only
exist in a repository.  If, for example, the C<hello.c> file includes the
C<hello.h> file in its current directory:

  % cons -R /usr/all/repository hello
  gcc -c /usr/all/repository/hello.c -o hello.o
  /usr/all/repository/hello.c:1: hello.h: No such file or directory

Solving this problem forces some requirements onto the way construction
environments are defined and onto the way the C C<#include> preprocessor
directive is used to include files.

In order to inform the compiler about the repository trees, Cons will add
appropriate C<-I> flags to the compilation commands.  This means that the
C<CPPPATH> variable in the construct environment must explicitly specify all
subdirectories which are to be searched for included files, including the
current directory.  Consequently, we can fix the above example by changing
the environment creation in the C<Construct> file as follows:

  $env = new cons(
	CC	=> 'gcc',
	CPPPATH	=> '.',
	LIBS	=> 'libworld.a',
  );

Due to the definition of the C<CPPPATH> variable, this yields, when we
re-execute the command:

  % cons -R /usr/all/repository hello
  gcc -c -I. -I/usr/all/repository /usr/all/repository/hello.c -o hello.o
  gcc -o hello hello.o /usr/all/repository/libworld.a

The order of the C<-I> flags replicates, for the C preprocessor, the same
repository-directory search path that Cons uses for its own dependency
analysis.  If there are multiple repositories and multiple C<CPPPATH>
directories, Cons will append the repository directories to the beginning of
each C<CPPPATH> directory, rapidly multiplying the number of C<-I> flags.
As an extreme example, a C<Construct> file containing:

  Repository qw(
	/u1
	/u2
  );

  $env = new cons(
	CPPPATH	=> 'a:b:c',
  );

Would yield a compilation command of:

	cc -Ia -I/u1/a -I/u2/a -Ib -I/u1/b -I/u2/b -Ic -I/u1/c -I/u2/c -c hello.c -o hello.o

Because Cons relies on the compiler's C<-I> flags to communicate the order
in which repository directories must be searched, Cons' handling of
repository directories is fundamentally incompatible with using
double-quotes on the C<#include> directives in your C source code:

  #include "file.h"	/* DON'T USE DOUBLE-QUOTES LIKE THIS */

This is because most C preprocessors, when faced with such a directive, will
always first search the directory containing the source file.  This
undermines the elaborate C<-I> options that Cons constructs to make the
preprocessor conform to its preferred search path.

Consequently, when using repository trees in Cons,
B<always> use angle-brackets for included files:

  #include <file.h>	/* USE ANGLE-BRACKETS INSTEAD */


=item B<Repository_List>

Cons provides a C<Repository_List> command to return a list of all
repository directories in their current search order.  This can be used for
debugging, or to do more complex Perl stuff:

  @list = Repository_List;
  print join(' ', @list), "\n";


=item B<Repository interaction with other Cons features>

Cons' handling of repository trees interacts correctly with other Cons
features--which is to say, it generally does what you would expect.

Most notably, repository trees interact correctly, and rather powerfully,
with the 'Link' command.  A repository tree may contain one or more
subdirectories for version builds established via C<Link> to a source
subdirectory.  Cons will search for derived files in the appropriate build
subdirectories under the repository tree.


=head1 B<Default targets>

Until now, we've demonstrated invoking Cons with an explicit target
to build:

  % cons hello

Normally, Cons does not build anything unless a target is specified,
but specifying '.' (the current directory) will build everything:

  % cons		# does not build anything

  % cons .		# builds everything under the top-level directory

Adding the C<Default> method to any Construct or Conscript file will add
the specified targets to a list of default targets.  Cons will build
these defaults if there are no targets specified on the command line.
So adding the following line to the top-level Construct file will mimic
Make's typical behavior of building everything by default:

  Default '.';

The following would add the C<hello> and C<goodbye> commands (in the
same directory as the Construct or Conscript file) to the default list:

  Default qw(
	hello
	goodbye
  );

The C<default> method may be used more than once to add targets to the
default list.

=head1 B<Selective builds>

Cons provides two methods for reducing the size of given build. The first is
by specifying targets on the command line, and the second is a method for
pruning the build tree. We'll consider target specification first.


=item B<Selective targeting>

Like make, Cons allows the specification of ``targets'' on the command
line. Cons targets may be either files or directories. When a directory is
specified, this is simply a short-hand notation for every derivable
product--that Cons knows about--in the specified directory and below. For
example:



  cons build/hello/hello.o

means buildC<hello.o> and everything that C<hello.o> might need. This is
from a previous version of the B<Hello, World!> program in which C<hello.o>
depended upon C<export/include/world.h>. If that file is not up-to-date
(because someone modified C<src/world/world.h)>, then it will be rebuilt,
even though it is in a directory remote from C<build/hello>.

In this example:



  cons build

Everything in the C<build> directory is built, if necessary. Again, this may
cause more files to be built. In particular, both C<export/include/world.h>
and C<export/lib/libworld.a> are required by the C<build/hello> directory,
and so they will be built if they are out-of-date.

If we do, instead:



  cons export

then only the files that should be installed in the export directory will be
rebuilt, if necessary, and then installed there. Note that C<cons build>
might build files that C<cons export> doesn't build, and B<vice-versa>.


=item B<No ``special'' targets>

With Cons, make-style ``special'' targets are not required. The simplest
analog with Cons is to use special C<export> directories, instead. Let's
suppose, for example, that you have a whole series of unit tests that are
associated with your code. The tests live in the source directory near the
code. Normally, however, you don't want to build these tests. One solution
is to provide all the build instructions for creating the tests, and then to
install the tests into a separate part of the tree. If we install the tests
in a top-level directory called C<tests>, then:



  cons tests

will build all the tests.



  cons export

will build the production version of the system (but not the tests), and:



  cons build

should probably be avoided (since it will compile tests unecessarily).

If you want to build just a single test, then you could explicitly name the
test (in either the C<tests> directory or the C<build> directory). You could
also aggregate the tests into a convenient hierarchy within the tests
directory. This hierarchy need not necessarily match the source hierarchy,
in much the same manner that the include hierarchy probably doesn't match
the source hierarchy (the include hierarchy is unlikely to be more than two
levels deep, for C programs).

If you want to build absolutely everything in the tree (subject to whatever
options you select), you can use:



  cons .

This is not particularly efficient, since it will redundantly walk all the
trees, including the source tree. The source tree, of course, may have
buildable objects in it--nothing stops you from doing this, even if you
normally build in a separate build tree.


=head1 B<Build Pruning>

In conjunction with target selection, B<build pruning> can be used to reduce
the scope of the build. In the previous peAcH and baNaNa example, we have
already seen how script-driven build pruning can be used to make only half
of the potential build available for any given invocation of C<cons>. Cons
also provides, as a convenience, a command line convention that allows you
to specify which C<Conscript> files actually get ``built''--that is,
incorporated into the build tree. For example:



  cons build +world

The C<+> argument introduces a Perl regular expression. This must, of
course, be quoted at the shell level if there are any shell meta-characters
within the expression. The expression is matched against each C<Conscript>
file which has been mentioned in a C<Build> statement, and only those
scripts with matching names are actually incorporated into the build
tree. Multiple such arguments are allowed, in which case a match against any
of them is sufficient to cause a script to be included.

In the example, above, the C<hello> program will not be built, since Cons
will have no knowledge of the script C<hello/Conscript>. The C<libworld.a>
archive will be built, however, if need be.

There are a couple of uses for build pruning via the command line. Perhaps
the most useful is the ability to make local changes, and then, with
sufficient knowledge of the consequences of those changes, restrict the size
of the build tree in order to speed up the rebuild time. A second use for
build pruning is to actively prevent the recompilation of certain files that
you know will recompile due to, for example, a modified header file. You may
know that either the changes to the header file are immaterial, or that the
changes may be safely ignored for most of the tree, for testing
purposes.With Cons, the view is that it is pragmatic to admit this type of
behavior, with the understanding that on the next full build everything that
needs to be rebuilt will be. There is no equivalent to a ``make touch''
command, to mark files as permanently up-to-date. So any risk that is
incurred by build pruning is mitigated. For release quality work, obviously,
we recommend that you do not use build pruning (it's perfectly OK to use
during integration, however, for checking compilation, etc. Just be sure to
do an unconstrained build before committing the integration).


=head1 B<Backing builds>

T.B.S.


=head1 B<Temporary overrides>

Cons provides a very simple mechanism for overriding aspects of a build. The
essence is that you write an override file containing one or more
C<Override> commands, and you specify this on the command line, when you run
C<cons>:



  cons -o over export

will build the C<export> directory, with all derived files subject to the
overrides present in the file C<over>. If you leave out the C<-o> option,
then everything necessary to remove all overrides will be rebuilt.


=item B<Overriding environment variables>

The override file can contain two types of overrides. The first is incoming
environment variables. These are normally accessible by the C<Construct>
file from the C<%ENV> hash variable. These can trivially be overridden in
the override file by setting the appropriate elements of C<%ENV> (these
could also be overridden in the user's environment, of course).


=item B<The>B< Override>B< command>

The second type of override is accomplished with the C<Override> command,
which looks like this:



  Override <regexp>, <var1> => <value1>, <var2> => <value2>, ...;

The regular expression I<regexp> is matched against every derived file that
is a candidate for the build. If the derived file matches, then the
variable/value pairs are used to override the values in the construction
environment associated with the derived file.

Let's suppose that we have a construction environment like this:



  $CONS = new cons(
	COPT => '',
	CDBG => '-g',
	CFLAGS => '%COPT %CDBG',
  );

Then if we have an override file C<over> containing this command:



  Override '\.o$', COPT => '-O', CDBG => '';

then any C<cons> invocation with C<-o over> that creates C<.o> files via
this environment will cause them to be compiled with C<-O >and no C<-g>. The
override could, of course, be restricted to a single directory by the
appropriate selection of a regular expression.

Here's the original version of the Hello, World! program, built with this
environment. Note that Cons rebuilds the appropriate pieces when the
override is applied or removed:



  % cons hello
  cc -g -c hello.c -o hello.o
  cc -o hello hello.o
  % cons -o over hello
  cc -O -c hello.c -o hello.o
  cc -o hello hello.o
  % cons -o over hello
  cons: "hello" is up-to-date.
  % cons hello
  cc -g -c hello.c -o hello.o
  cc -o hello hello.o

It's important that the C<Override> command only be used for temporary,
on-the-fly overrides necessary for development because the overrides are not
platform independent and because they rely too much on intimate knowledge of
the workings of the scripts. For temporary use, however, they are exactly
what you want.

Note that it is still useful to provide, say, the ability to create a fully
optimized version of a system for production use--from the C<Construct> and
C<Conscript> files. This way you can tailor the optimized system to the
platform. Where optimizer trade-offs need to be made (particular files may
not be compiled with full optimization, for example), then these can be
recorded for posterity (and reproducibility) directly in the scripts.


=head1 B<More on construction environments:Default construction variables>

We have mentioned, and used, the concept of a B<construction environment>,
many times in the preceding pages. Now it's time to make this a little more
concrete. With the following statement:



  $env = new cons();


=item B<Default construction variables>

a reference to a new, default construction environment is created. This
contains a number of construction variables and some methods. At the present
writing, the default list of construction variables is defined as follows:


  CC		=> 'cc',
  CFLAGS	=> '',
  CCCOM		=> '%CC %CFLAGS %_IFLAGS -c %< -o %>',
  CXX		=> '%CC',
  CXXFLAGS	=> '%CFLAGS',
  CXXCOM	=> '%CXX %CXXFLAGS %_IFLAGS -c %< -o %>',
  LINK		=> '%CXX',
  LINKCOM	=> '%LINK %LDFLAGS -o %> %< %_LDIRS %LIBS',
  LINKMODULECOM	=> '%LD -r -o %> %<',
  AR		=> 'ar',
  ARFLAGS	=> 'r',
  ARCOM		=> "%AR %ARFLAGS %> %<\n%RANLIB %>",
  RANLIB	=> 'ranlib',
  AS		=> 'as',
  ASFLAGS	=> '',
  ASCOM		=> '%AS %ASFLAGS %< -o %>',
  LD		=> 'ld',
  LDFLAGS	=> '',
  PREFLIB	=> 'lib',
  SUFLIB	=> '.a',
  SUFLIBS	=> '.so:.a',
  SUFOBJ	=> '.o',
  ENV		=> { 'PATH' => '/bin:/usr/bin' },


On Win32 systems (Windows NT), the following construction variables
are overridden in the default:

  CC		=> 'cl',
  CFLAGS	=> '/nologo',
  CCCOM		=> '%CC %CFLAGS %_IFLAGS /c %< /Fo%>',
  LINK		=> 'link',
  LINKCOM	=> '%LINK %LDFLAGS /out:%> %< %_LDIRS %LIBS',
  LINKMODULECOM	=> '%LD /r /o %> %<',
  AR		=> 'lib',
  ARFLAGS	=> '/nologo ',
  ARCOM		=> "%AR %ARFLAGS /out:%> %<",
  RANLIB	=> '',
  LD		=> 'link',
  LDFLAGS	=> '/nologo ',
  PREFLIB	=> '',
  SUFEXE	=> '.exe',
  SUFLIB	=> '.lib',
  SUFLIBS	=> '.dll:.lib',
  SUFOBJ	=> '.obj',

These variables are used by the various methods associated with the
environment, in particular any method that ultimately invokes an external
command will substitute these variables into the final command, as
appropriate. For example, the C<Objects> method takes a number of source
files and arranges to derive, if necessary, the corresponding object
files. For example:



  Objects $env 'foo.c', 'bar.c';

This will arrange to produce, if necessary, C<foo.o> and C<bar.o>. The
command invoked is simply C<%CCOM>, which expands through substitution, to
the appropriate external command required to build each object. We will
explore the substitution rules further under the C<Command> method, below.

The construction variables are also used for other purposes. For example,
C<CPPPATH> is used to specify a colon-separated path of include
directories. These are intended to be passed to the C preprocessor and are
also used by the C-file scanning machinery to determine the dependencies
involved in a C Compilation. Variables beginning with underscore, are
created by various methods, and should normally be considered ``internal''
variables. For example, when a method is called which calls for the creation
of an object from a C source, the variable C<_IFLAGS> is created: this
corresponds to the C<-I> switches required by the C compiler to represent
the directories specified by C<CPPPATH>.

Note that, for any particular environment, the value of a variable is set
once, and then never reset (to change a variable, you must create a new
environment. Methods are provided for copying existing environments for this
purpose). Some internal variables, such as C<_IFLAGS> are created on demand,
but once set, they remain fixed for the life of the environment.

Another variable, C<ENV>, is used to determine the system environment during
the execution of an external command. By default, the only environment
variable that is set is C<PATH>, which is the execution path for a UNIX
command. For the utmost reproducibility, you should really arrange to set
your own execution path, in your top-level C<Construct> file (or perhaps by
importing an appropriate construction package with the Perl C<use>
command). The default variables are intended to get you off the ground.


=head1 B<Default construction methods>

The list of default construction methods includes the following:


=item B<The >B<new>B< constructor>

The C<new> method is a Perl object constructor. That is, it is not invoked
via a reference to an existing construction environment B<reference>, but,
rather statically, using the name of the Perl B<package> where the
constructor is defined. The method is invoked like this:



  $env = new cons(<overrides>);

The environment you get back is blessed into the package C<cons>, which
means that it will have associated with it the default methods described
below. Individual construction variables can be overridden by providing
name/value pairs in an override list. Note that to override any command
environment variable (i.e. anything under C<ENV>), you will have to override
all of them. You can get around this difficulty by using the C<copy> method
on an existing construction environment.


=item B<The >B<clone>B< method>

The C<clone> method creates a clone of an existing construction environment,
and can be called as in the following example:



  $env2 = $env1->clone(<overrides>);

You can provide overrides in the usual manner to create a different
environment from the original. If you just want a new name for the same
environment (which may be helpful when exporting environments to existing
components), you can just use simple assignment.


=item B<The >B<copy>B< method>

The C<copy> method extracts the externally defined construction variables
from an environment and returns them as a list of name/value
pairs. Overrides can also be provided, in which case, the overridden values
will be returned, as appropriate. The returned list can be assigned to a
hash, as shown in the prototype, below, but it can also be manipulated in
other ways:



  %env = $env1->copy(<overrides>);

The value of C<ENV>, which is itself a hash, is also copied to a new hash,
so this may be changed without fear of affecting the original
environment. So, for example, if you really want to override just the
C<PATH> variable in the default environment, you could do the following:



  %cons = new cons()->copy();
  $cons{ENV}{PATH} = "<your path here>";
  $cons = new cons(%cons);

This will leave anything else that might be in the default execution
environment undisturbed.


=item B<The >B<Install>B< method>

The C<Install> method arranges for the specified files to be installed in
the specified directory. The installation is optimized: the file is not
copied if it can be linked. If this is not the desired behavior, you will
need to use a different method to install the file. It is called as follows:



  Install $env <directory>, <names>;

Note that, while the files to be installed may be arbitrarily named, only
the last component of each name is used for the installed target name. So,
for example, if you arrange to install C<foo/bar> in C<baz>, this will
create a file C<bar> in directory C<baz> (not C<foo/bar>).


=item B<The >B<InstallAs>B< method>

The C<InstallAs> method arranges for the specified source file(s) to be
installed as the specified target file(s). Multiple files should be
specified as a file list. The installation is optimized: the file is not
copied if it can be linked. If this is not the desired behavior, you will
need to use a different method to install the file. It is called as follows:

C<InstallAs> works in two ways:

Single File Install:

  InstallAs $env TgtFile, SrcFile;

Multiple File Install:

  InstallAs $env ['tgt1', 'tgt2'], ['src1', 'src2'];

  Or, even as:

  @srcs = qw(src1 src2 src3);
  @tgts = qw(tgt1 tgt2 tgt3);
  InstallAs $env [@tgts], [@srcs];

Both the target and the sources lists should be of the same length.

=item B<The >B<Precious>B< method>

The C<Precious> method asks cons not to delete the given file or list
of files before building them again.  This is especially useful for
allowing incremental updates to libraries or debug information files
which are updated rather than rebuilt anew each time.  Cons will still
delete the files when the C<-r> flag is specified.

=item B<The >B<Command>B< method>

The C<Command> method is a catchall method which can be used to arrange for
any external command to be called to update the target. For this command, a
target file and list of inputs is provided. In addition a construction
command line, or lines, is provided as a string (this string may have
multiple commands embedded within it, separated by new lines). C<Command> is
called as follows:



  Command $env <target>, <inputs>, <construction command>;

The target is made dependent upon the list of input files specified, and the
inputs must be built successfully or Cons will not attempt to build the
target.

Within the construction command, any variable from the construction
environment may be introduced by prefixing the name of the construction
variable with C<%>. This is recursive: the command is expanded until no more
substitutions can be made. If a construction variable is not defined in the
environment, then the null string will be substituted.

There are several pseudo variables which will also be expanded:


=over 10


=item C<%>>

The target file name (in a multi-target command, this is always the first
target mentioned).

=item C<%0>

Same as C<%>>.

=item C<%1,>

%2, ..., %9 These refer to the first through ninth input file, respectively.

=item C<%<>

The full set of inputs. If any of these have been used anywhere else in the
current command line (via C<%1>, C<%2>, etc.), then those will be deleted
from the list provided by C<%<>. Consider the following command found in a
C<Conscript> file in the directory C<test>:

  Command $env 'tgt', qw(foo bar baz), qq(
	echo %< -i %1 > %>
	echo %< -i %2 >> %>
	echo %< -i %3 >> %>
  );



=item

If C<tgt> needed to be updated, then this would result in the execution of
the following commands, assuming that no remapping has been established for
directory C<test>:

  echo test/bar test/baz -i test/foo > test/tgt
  echo test/foo test/baz -i test/bar >> test/tgt
  echo test/foo test/bar -i test/baz >> test/tgt



=back

Any of the above pseudo variables may be followed immediately by one of
the following suffixes to select a portion of the expanded path name:

  C<:b>    the directory plus the file name stripped of any suffix
  C<:d>    the directory
  C<:f>    the file name
  C<:s>    the file name suffix
  C<:F>    the file name stripped of any suffix

Continuing with the above example, C<%<:f> would expand to C<foo bar baz>,
and C<%>:d> would expand to C<test>.

It is possible to programmatically rewrite part of the command by
enclosing part of it between C<%[> and C<%]>.  This will call the
construction variable named as the first word enclosed in the brackets
as a Perl code reference; the results of this call will be used to
replace the contents of the brackets in the command line.  For example:

  $env = new cons(X_COMMA => sub { join(",", @_) });
  Command $env 'tgt', qw(foo bar baz), "echo %[X_COMMA %<%] > %>"

This will execute:

  echo foo,bar,baz > tgt

After substitution occurs, strings of white space are converted into single
blanks, and leading and trailing white space is eliminated. It is therefore
not possible to introduce variable length white space in strings passed into
a command, without resorting to some sort of shell quoting.

If a multi-line command string is provided, the commands are executed
sequentially. If any of the commands fails, then none of the rest are
executed, and the target is not marked as updated, i.e. a new signature is
not stored for the target.

Normally, if all the commands succeed, and return a zero status (or whatever
platform-specific indication of success is required), then a new signature
is stored for the target. If a command erroneously reports success even
after a failure, then Cons will assume that the target file created by that
command is accurate and up-to-date.

The first word of each command string, after expansion, is assumed to be an
executable command looked up on the C<PATH> environment variable (which is,
in turn, specified by the C<ENV> construction variable). If this command is
found on the path, then the target will depend upon it: the command will
therefore be automatically built, as necessary. It's possible to write
multi-part commands to some shells, separated by semi-colons. Only the first
command word will be depended upon, however, so if you write your command
strings this way, you must either explicitly set up a dependency (with the
C<Depends> method), or be sure that the command you are using is a system
command which is expected to be available. If it isn't available, you will,
of course, get an error.

Cons normally prints a command before executing it.  This behavior is
suppressed if the first character of the command is C<@>.  Note that
you may need to separate the C<@> from the command name or escape it to
prevent C<@cmd> from looking like an array to Perl quote operators that
perform interpolation:

  # The first command line is incorrect,
  # because "@cp" looks like an array
  # to the Perl qq// function.
  # Use the second form instead.
  Command $env 'foo', 'foo.in', qq(
	@cp %< tempfile
	@ cp tempfile %>
  );

If there are shell meta characters anywhere in the expanded command line,
such as C<<>, C<>>, quotes, or semi-colon, then the command will actually be
executed by invoking a shell. This means that a command such as:



  cd foo

alone will typically fail, since there is no command C<cd> on the path. But
the command string:



  cd $<:d; tar cf $>:f $<:f

when expanded will still contain the shell meta character semi-colon, and a
shell will be invoked to interpret the command. Since C<cd> is interpreted
by this sub-shell, the command will execute as expected.

To specify a command with multiple targets, you can specify a reference to a
list of targets. In Perl, a list reference can be created by enclosing a
list in square brackets. Hence the following command:



  Command $env ['foo.h', 'foo.c'], 'foo.template', q(
	gen %1
  );

could be used in a case where the command C<gen> creates two files, both
C<foo.h> and C<foo.c>.


=item B<The >B<Objects>B< method>

The C<Objects> method arranges to create the object files that correspond to
the specified source files. It is invoked as shown below:



  @files = Objects $env <source or object files>;

Under Unix, source files ending in C<.s> and C<.c> are currently supported,
and will be compiled into a name of the same file ending in C<.o>. By
default, all files are created by invoking the external command which
results from expanding the C<CCOM> construction variable, with C<%<> and
C<%>> set to the source and object files, respectively (see the C<Command>
method for expansion details) . The variable C<CPPPATH> is also used when
scanning source files for dependencies. This is a colon separated list of
pathnames, and is also used to create the construction variable C<_IFLAGS,>
which will contain the appropriate list of -C<I> options for the
compilation. Any relative pathnames in C<CPPPATH> is interpreted relative to
the directory in which the associated construction environment was created
(absolute and top-relative names may also be used). This variable is used by
C<CCOM>. The behavior of this command can be modified by changing any of the
variables which are interpolated into C<CCOM>, such as C<CC>, C<CFLAGS>,
and, indirectly, C<CPPPATH>. It's also possible to replace the value of
C<CCOM>, itself. As a convenience, this file returns the list of object
filenames.


=item B<The >B<Program>B< method>

The C<Program> method arranges to link the specified program with the
specified object files. It is invoked in the following manner:



  Program $env <program name>, <source or object files>;

Source files may be specified in place of objects files--the C<Objects>
method will be invoked to arrange the conversion of all the files into
object files, and hence all the observations about the C<Objects> method,
above, apply to this method also. The actual linking of the program will be
handled by an external command which results from expanding the C<LINKCOM>
construction variable, with C<%<> set to the object files to be linked (in
the order presented), and C<%>> set to the target (see the C<Command> method
for expansion details). The user may set additional variables in the
construction environment, including C<LINK>, to define which program to use
for linking, C<LIBPATH>, a colon-separated list of library search paths, for
use with library specifications of the form I<-llib>, and C<LIBS>,
specifying the list of libraries to link against (in either I<-llib> form or
just as pathnames. Relative pathnames in both C<LIBPATH> and C<LIBS> are
interpreted relative to the directory in which the associated construction
environment created (absolute and top-relative names may also be used). Cons
automatically sets up dependencies on any libraries mentioned in C<LIBS>:
those libraries will be built before the command is linked.


=item B<The >B<Library>B< method>

The C<Library> method arranges to create the specified library from the
specified object files. It is invoked as follows:



  Library $env <library name>, <source or object files>;

Source files may be specified in place of objects files--the C<Objects>
method will be invoked to arrange the conversion of all the files into
object files, and hence all the observations about the C<Objects> method,
above, apply to this method also. The actual creation of the library will be
handled by an external command which results from expanding the C<ARCOM>
construction variable, with C<%<> set to the library members (in the order
presented), and C<%>> to the library to be created (see the C<Command>
method for expansion details). The user may set variables in the
construction environment which will affect the operation of the
command. These include C<AR>, the archive program to use, C<ARFLAGS>, which
can be used to modify the flags given to the program specified by C<AR>, and
C<RANLIB>, the name of a archive index generation program, if needed (if the
particular need does not require the latter functionality, then C<ARCOM>
must be redefined to not reference C<RANLIB>).

The C<Library> method allows the same library to be specified in multiple
method invocations. All of the contributing objects from all the invocations
(which may be from different directories) are combined and generated by a
single archive command. Note, however, that if you prune a build so that
only part of a library is specified, then only that part of the library will
be generated (the rest will disappear!).


=item B<The >B<Module>B< method>

The C<Module> method is a combination of the C<Program> and C<Command>
methods. Rather than generating an executable program directly, this command
allows you to specify your own command to actually generate a module. The
method is invoked as follows:



  Module $env <module name>, <source or object files>, <construction command>;

This command is useful in instances where you wish to create, for example,
dynamically loaded modules, or statically linked code libraries.


=item B<The >B<Depends>B< method>

The C<Depends> method allows you to specify additional dependencies for a
target. It is invoked as follows:



  Depends $env <target>, <dependencies>;

This may be occasionally useful, especially in cases where no scanner exists
(or is writable) for particular types of files. Normally, dependencies are
calculated automatically from a combination of the explicit dependencies set
up by the method invocation or by scanning source files.


=head1 B<Extending Cons>


=item B<Overriding construction variables>

There are several ways of extending Cons, which vary in degree of
difficulty. The simplest method is to define your own construction
environment, based on the default environment, but modified to reflect your
particular needs. This will often suffice for C-based applications. You can
use the C<new> constructor, and the C<clone> and C<copy> methods to create
hybrid environments. These changes can be entirely transparent to the
underlying C<Conscript> files.


=item B<Adding new methods>

For slightly more demanding changes, you may wish to add new methods to the
C<cons> package. Here's an example of a very simple extension,
C<InstallScript>, which installs a tcl script in a requested location, but
edits the script first to reflect a platform-dependent path that needs to be
installed in the script:



  # cons::InstallScript - Create a platform dependent version of a shell
  # script by replacing string ``#!your-path-here'' with platform specific
  # path $BIN_DIR.

  sub cons::InstallScript {
	my($env, $dst, $src) = shift;
	Command $env $dst, $src, qq(
		sed s+your-path-here+$BIN_DIR+ %< > %>
		chmod oug+x %>
	);
  }

Notice that this method is defined directly in the C<cons> package (by
prefixing the name with C<cons::>). A change made in this manner will be
globally visible to all environments, and could be called as in the
following example:



  InstallScript $env "$BIN/foo", "foo.tcl";

For a small improvement in generality, the C<BINDIR> variable could be
passed in as an argument or taken from the construction environment--as
C<%BINDIR>.


=item B<Overriding methods>

Instead of adding the method to the C<cons> name space, you could define a
new package which inherits existing methods from the C<cons> package and
overrides or adds others. This can be done using Perl's inheritance
mechanisms.

The following example defines a new package cons::switch which overrides the
standard C<Library> method. The overridden method builds linked library
modules, rather than library archives. A new constructor is
provided. Environments created with this Constructor will have the new
library method; others won't.







  package cons::switch;
  BEGIN {@ISA = `cons'}



  sub new {
	shift;
	bless new cons(@_);
  }



  sub Library {
	my($env) = shift;
	my($lib) = shift;
	my(@objs) = Objects $env @_;
	Command $env $lib, @objs, q(
		%LD -r %LDFLAGS %< -o %>
	);
  }

This functionality could be invoked as in the following example:



  $env = new cons::switch(@overrides);
  ...
  Library $env 'lib.o', 'foo.c', 'bar.c';


=head1 B<Invoking Cons>

The C<cons> command is usually invoked from the root of the build tree. A
C<Construct> file must exist in that directory. If the C<-f> argument is
used, then an alternate C<Construct> file may be used (and, possibly, an
alternate root, since C<cons> will cd to C<Construct> file's containing
directory).

If C<cons> is invoked from a child of the root of the build tree with
the C<-t> argument, it will walk up the directory hierarchy looking for a
C<Construct> file.  (An alternate name may still be specified with C<-f>.)
The targets supplied on the command line will be modified to be relative
to the discovered C<Construct> file.  For example, invoking C<cons> in
"root/libfoo/sub" with C<cons -t target> is identical to invoking it in
"root" with C<cons libfoo/sub/target>.  (Assuming there is a C<Construct>
file in "root".  If there are any C<Default> targets specified in
the directory hierarchy's C<Construct> or C<Conscript> files, only
the default targets at or below the directory from which C<cons -t>
was invoked will be built.

The command is invoked as follows:

  cons <arguments>

where I<arguments> can be any of the following, in any order:


=over 10


=item I<target>

Build the specified target. If I<target> is a directory, then recursively
build everything within that directory.

=item I<+pattern>

Limit the C<Conscript> files considered to just those that match I<pattern>,
which is a Perl regular expression. Multiple C<+> arguments are accepted.

=item I<name>=<val>

Sets I<name> to value I<val> in the C<ARG> hash passed to the top-level
C<Construct> file.

=item C<-cc>

Show command that would have been executed, when retrieving from cache. No
indication that the file has been retrieved is given; this is useful for
generating build logs that can be compared with real build logs.

=item C<-cd>

Disable all caching. Do not retrieve from cache nor flush to cache.

=item C<-cr>

Build dependencies in random order. This is useful when building multiple
similar trees with caching enabled.

=item C<-cs>

Synchronize existing build targets that are found to be up-to-date with
cache. This is useful if caching has been disabled with -cc or just recently
enabled with UseCache.

=item C<-d>

Enable dependency debugging.

=item C<-f> <file>

Use the specified file instead of C<Construct> (but first change to
containing directory of I<file>).

=item C<-h>

Show a help message local to the current build if one such is defined, and
exit.

=item C<-o> <file>

Read override file I<file>.

=item C<-k>

Keep going as far as possible after errors.

=item C<-m>

Show cons modification history and exit.

=item C<-p>

Show construction products in specified trees. No build is attempted.

=item C<-pa>

Show construction products and associated actions. No build is attempted.

=item C<-pw>

Show products and where they are defined. No build is attempted.

=item C<-q>

Don't be verbose about Installing and Removing targets.

=item C<-wf> <file>

Write all filenames considered into I<file>.

=item C<-r>

Remove construction products associated with <targets>. No build is
attempted.

=item C<-R> <repos>

Search for files in I<repos>.  Multiple B<-R> I<repos> directories are
searched in the order specified.

=item C<-t>

Traverse up the directory hierarchy looking for a Construct file, if
none exists in the current directory.  Targets will be modified to be
relative to the Construct file.

=item C<-v>

Show C<cons> version and continue processing.

=item C<-V>

Show C<cons> version and exit.

=item C<-x>

Show a help message similar to this one, and exit.

=back

Note that C<cons -r .> is equivalent to a full recursive C<make clean>, but
requires no support in the C<Construct> file or any C<Conscript> files. This
is most useful if you are compiling files into source directories (if you
separate the C<build>/C<export> directories, then you can just remove the
directories).

The options C<-p>, C<-pa>, and C<-pw> are extremely useful for use as an aid
in reading scripts or debugging them. If you want to know what script
installs C<export/include/foo.h>, for example, just type:



  cons -pw export/include/foo.h


=head1 B<Using and writing dependency scanners>

T.B.S.


=head1 B<Support and Suggestions>

Cons is maintained by the user community.  To subscribe, send mail to
B<cons-discuss-request@eng.fore.com> with body B<subscribe>.

Please report any bugs/fixes/suggestions through the
cons-discuss@eng.fore.com mailing list.

The Official cons site is: http://www.dsmit.com/cons


#:endofperl
