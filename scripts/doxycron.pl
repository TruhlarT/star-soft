#!/usr/bin/env perl

#
# This script will serve as a wrapper to doxygen
# and is suitable for a crontab. Written
# J.Lauret Dec 18th 2001. So far, 'dev' only.
#
# In the directory $TARGETD/dox, a configuration
# file $PROJECT.cfg is supposed to exists. 
#
# This file is assumed to be a template to which,
# the output_dir and input directory will be added
# depending on the value of $INDEXD and $SUBDIR.
#
# OUTPUT_DIRECTORY will default to $TARGETD/dox$SUBDIR
# and the DOC_ABSPATH will take the form 
# $TARGETD/dox$SUBDIR/html. However, for the processing, 
# everything will be done in a temporary sub-directory 
# and moved only after everything is done. This was 
# chosen to avoid interference with already existing 
# documents and so we maintain a clean tree.
#
# Currently supported : html, latex, man directories
# will be moved to their final destination by this
# script. See code for relatively easy extension
# to other formats.
#
# The INPUT directory is defaulted to $INDEXD.
#
# $URLPATH will be used to generate a DOC_URL of the
# form $HTTPD/$URLPATH/dox$SUBDIR/html so it needs
# only to appear as a relative path to the root
# URL. Note that we require that you setup HTTPD as
# being the server name running the WebServer. Finally,
# the CGI_URL will map the defined path convention i.e.
# will be initialized as $HTPPD/cgi-bin/dox$SUBDIR .
# Better to setup that script (usually a copy from what
# doxygen generates) ...
#
# The implementation of the search from tamplate is
# incomplete and may be fixed later.
#  
#
# The doxygen project name is assumed to match
# the $PROJECT variable. Currently, this should
# be a single name only (no space) since there
# is an assumption project-name/Config file.
#
# Note also that this script accepts arguments
# superseding the default values that is :
#  $TARGETD
#  $INDEXD
#  $URLPATH
#  $PROJECT
#  $SUBDIR
#
# In principle, anyboddy can then run this script
# and generate their own doc. This will be helpful
# for testing new configuration files. It initially
# sounds complicated but really follows a standardized
# path naming-convention alllowing for looping over
# directories and or re-use for several projects while
# ensuring output safety.
#
#

$TARGETD = "/afs/rhic/star/doc/www/html/tmp";        # Working directory
$INDEXD  = "/afs/rhic/star/packages/dev/StRoot";     # Dir to scan
$PROJECT = "StRoot";                                 # Project name
$SUBDIR  = "";                                       # Sub-dir for output


# Eventually replace by @ARGV
$DOTAG = 1;
do {
    $tmp = shift(@ARGV) if ( @ARGV );
    if( substr($tmp,0,1) eq "-"){
	# Treat it as option
	if($tmp eq "-i"){ $DOTAG = 0;}
    } else {
	$TARGETD = $tmp if ($tmp);
	$tmp     = "";
    }
} while ($tmp ne "");

$INDEXD  = shift(@ARGV) if ( @ARGV );
$PROJECT = shift(@ARGV) if ( @ARGV );
$SUBDIR  = shift(@ARGV) if ( @ARGV );


# -------------------------------------------------------------------------
$TMPDIR  = "/tmp";                                   # temp dir on cron node

$BINPATH = "/usr/bin/";                              # path to bin for doxy-progs 
                                                     # for Web server (indexer)

$BINCRON = "/opt/star/bin";                          # path where doxycron will
                                                     # find the excutables (not
                                                     # the same than BINPATH if 
                                                     # doxycron runs on a
                                                     # different node than httpd

$DOXYGEN = "doxygen";                                # exe names on local node
$DOXYTAG = "doxytag";                                # can be full path or not.
$HTTPD   = "http://www.star.bnl.gov";                # HTTP Server
$URLPATH = "webdatanfs";                             # Base URL path





# -------------------------------------------------------------------
# Sanity checks
# -------------------------------------------------------------------
if ( ! -e "$BINCRON/$DOXYGEN"){    chomp($DOXYGEN=`which $DOXYGEN`);
} else {                                 $DOXYGEN= "$BINCRON/$DOXYGEN";}
if ( ! -e "$BINCRON/$DOXYTAG"){    chomp($DOXYTAG=`which $DOXYTAG`);
} else {                                 $DOXYTAG= "$BINCRON/$DOXYTAG";}


# RE-check now
if( ! -e $DOXYGEN){
    print "Boomer ! Required $DOXYGEN is missing. Please, install.\n";
    exit;
} 
if( ! -d "$TARGETD/dox"){
    if( ! mkdir("$TARGETD/dox",0777) ){
	print "Dooo  !! Directory $TARGETD/dox cannot be created.\n";
	exit;
    } else {
	print "Created $TARGETD/dox\n";
    }
}
if( ! -e "$TARGETD/dox/$PROJECT.cfg"){
    if( ! &CfgCreate("$TARGETD/dox/$PROJECT.cfg") ){
	print "Huuuu !! Missing config file $TARGETD/dox/$PROJECT.cfg ".
	    "and cannot create it ..\n";
	exit;
    } else {
	print "Created $TARGETD/dox/$PROJECT.cfg\n";
    }
}


# -------------------------------------------------------------------
# Generate alternate config file i.e. a copy of the template
# from which several keywords will be auto-replaced by values
# based on passed parameters.
# -------------------------------------------------------------------
$tmpf = $TMPDIR."/doxygen$>-$$";
open(FI,"$TARGETD/dox/$PROJECT.cfg");
open(FO,">$tmpf.cfg");

$GENERATE_HTML = 0;
$GENERATE_LATX = 0;
$GENERATE_MAN  = 0;

while ( defined($line = <FI>) ){
    chomp($line);
    if($line =~ m/(OUTPUT_DIRECTORY.*=\s+)(.*)/){
	# We add an extra level so we can do some cleanup
	# in between.
	$line = "OUTPUT_DIRECTORY       = $TARGETD/dox$SUBDIR/tmp$$";

    } elsif ($line =~ m/(PROJECT_NAME.*=\s+\")(.*)(\")/){
	if($2 ne $PROJECT){
	    $line = "PROJECT_NAME           = \"$PROJECT\"";
	}

    } elsif ($line =~ m/(INPUT.*=\s+)(.*)/){
	if($2 ne $INDEXD){
	    $line = "INPUT                  = $INDEXD";
	}

    } elsif ($line =~ m/(EXAMPLE_PATH.*=\s+)(.*)/){
	# This is dynamic
	$expath = join(" ",glob("$INDEXD/*/examples/"));
	$line = "EXAMPLE_PATH           = $expath";

    } elsif ($line =~ m/(STRIP_FROM_PATH.*=\s+)(.*)/){
	$line = "STRIP_FROM_PATH        = $INDEXD/";
	


    } elsif ($line =~ m/(GENERATE_HTML.*=\s+)(YES)/){
	$GENERATE_HTML = 1;
    } elsif ($line =~ m/(GENERATE_LATEX.*=\s+)(YES)/){
	$GENERATE_LATX = 1;
    } elsif ($line =~ m/(GENERATE_MAN.*=\s+)(YES)/){
	$GENERATE_MAN  = 1;
    } elsif ($line =~ m/(HTML_OUTPUT.*=\s+)(.*)/ && $GENERATE_HTML){
	if( $2 eq ""){
	    push(@DIRS,"html");
	} else {
	    push(@DIRS,$2);
	}
    } elsif ($line =~ m/(LATEX_OUTPUT.*=\s+)(.*)/ && $GENERATE_LATX){
	if( $2 eq ""){
	    push(@DIRS,"latex");
	} else {
	    push(@DIRS,$2);
	}
    } elsif ($line =~ m/(MAN_OUTPUT.*=\s+)(.*)/ && $GENERATE_MAN){
	if( $2 eq ""){
	    push(@DIRS,"man");
	} else {
	    push(@DIRS,$2);
	}



	#### CGI setup
    } elsif ($line =~ m/(CGI_NAME.*=\s+)(.*)/){
	$line = "CGI_NAME               = search.cgi";

    } elsif ($line =~ m/(CGI_URL.*=\s+)(.*)/){
	$line = "CGI_URL                = $HTTPD/cgi-bin/dox$SUBDIR";



	#### URL setup for search
    } elsif ($line =~ m/(DOC_URL.*=\s+)(.*)/){
	$line = "DOC_URL                = $HTTPD/$URLPATH/dox$SUBDIR/html";

    } elsif ($line =~ m/(DOC_ABSPATH.*=\s+)(.*)/){
	$line = "DOC_ABSPATH            = $TARGETD/dox$SUBDIR/html";

    } elsif ($line =~ m/(BIN_ABSPATH.*=\s+)(.*)/){
	$line = "BIN_ABSPATH            = $BINPATH";

    }
    print FO "$line\n";
}
close(FI);
close(FO);
chmod(0600,"$tmpf.cfg");




# -------------------------------------------------------------------
# Create temporary sub-directories in target tree if necassary
# -------------------------------------------------------------------
if( ! -d "$TARGETD/dox$SUBDIR"){
    print "Creating to structure  $TARGETD/dox$SUBDIR\n";
    if( ! mkdir("$TARGETD/dox$SUBDIR",0777) ){
	print "Cannot create $TARGETD/dox$SUBDIR\n";
	exit;
    }
}
if( ! -d "$TARGETD/dox$SUBDIR/tmp$$"){
    print "Creating temporary dir $TARGETD/dox$SUBDIR/tmp$$\n";
    if (! mkdir("$TARGETD/dox$SUBDIR/tmp$$",0777) ){
	print "Cannot create $TARGETD/dox$SUBDIR/tmp$$\n";
	exit;
    }

}



# -------------------------------------------------------------------
# Now, start using this file but also redirect all
# resulting output of doxygen to a temp file
# -------------------------------------------------------------------
if( -e "$tmpf.cfg"){
    print "Running $DOXYGEN now ".localtime()."\n";
    system("cd $TMPDIR ; $DOXYGEN $tmpf.cfg >&$tmpf.log");
    if( -d "$TARGETD/dox$SUBDIR/tmp$$/html" && $DOTAG){
	print "Running $DOXYTAG now ".localtime()."\n";
	system("cd $TARGETD/dox$SUBDIR/tmp$$/html ; ".
	       "$DOXYTAG -s search.idx >&/dev/null");
    } else {
	print "Missing tmp$$/html directory\n";
    }
    #unlink("$tmpf.cfg");
} else {
    print "Action did not create a temporary configuration file\n";
    exit;
}



# -------------------------------------------------------------------
# Check if the expected sub-directories were created and
# move them to target destination.
# -------------------------------------------------------------------
foreach $dir (@DIRS){
    if( -d "$TARGETD/dox$SUBDIR/tmp$$/$dir"){
	# Rename the tmp-directories to target-directories
	# Take care of the old one first
	if( -d "$TARGETD/dox$SUBDIR/$dir"){
	    if( -d "$TARGETD/dox$SUBDIR/$dir.old"){
		#print "Removing old $TARGETD/dox/$SUBDIR/$dir.old\n";
		system("rm -fr $TARGETD/dox$SUBDIR/$dir.old");
	    }
	    #print "Renaming current $TARGETD/dox/$SUBDIR/$dir\n";
	    rename("$TARGETD/dox$SUBDIR/$dir",
		   "$TARGETD/dox$SUBDIR/$dir.old");
	}
	# Rename tmp -> final destination
	print "Installing created $TARGETD/dox$SUBDIR/$dir\n";
	rename("$TARGETD/dox$SUBDIR/tmp$$/$dir",
	       "$TARGETD/dox$SUBDIR/$dir");
    } else {
	print "Warning :: $dir not found\n";
    }
}
if( -d "$TARGETD/dox$SUBDIR/tmp$$"){
    rmdir("$TARGETD/dox$SUBDIR/tmp$$");
}


# -------------------------------------------------------------------
# Guess what ? We have a few interresting comments/warning
# generated from that pass. Parse it now ... and re-generate
# the index.html as we see fit. This is kinda' home-made but
# this entire block may be disabled.
# -------------------------------------------------------------------
if( 1==1 ){
    print "Scanning for errors/warnings\n";
    open(FI,"$tmpf.log");
    while ( defined($line=<FI>) ){
	if($line =~ m/(Error\:)(.*)/){
	    $el = "Errors";
	    if( defined($ERRORS{$el}) ){
		$ERRORS{$el} .= ";$line";
	    } else {
		$ERRORS{$el}  = "$line";
	    }
	} elsif($line =~ m/(.*)(:\d+\s+)(Warning:)(.*)/){
	    # I separated it because it may become a ';' list
	    # in the pattern. So far, only saw 'Warning'.
	    $el = $1; $val = "$2$3$4";
	    $el =~ s/$INDEXD\///g;
	    if( defined($ERRORS{$el}) ){
		$ERRORS{$el} .= ";$val";
	    } else {
		$ERRORS{$el}  = "$val";
	    }
	    if($line =~ /no matching file member found for/ ||
	       $line =~ /no matching class member found for/){
		chomp($ERRORS{$el} .= <FI>);
	    }
	}
	
    }
    close(FI);

    if( -d "$TARGETD/dox$SUBDIR/html"){
	print "Reading template file\n";
	open(FI,"$TARGETD/dox$SUBDIR/html/index.html");
	$tmp = 0;
	while ( defined($line = <FI>) ){
	    chomp($line);
	    if( $line =~ /<p>/){
		$tmp = 1;
	    } elsif ($line =~ /<hr><h1>.*/){
		# Ignore it
	    } else {
		if($tmp==1){
		    push(@TAIL,$line);
		} elsif ($tmp == 0) {
		    push(@HEAD,$line);
		}
	    }
	}
	close(FI);


	print "Now printing out the errors\n";
	open(FO,">$TARGETD/dox$SUBDIR/html/doxycron-errors.html");

	# start with a reference list
	foreach $line (@HEAD){ print FO "$line\n";}
	print FO
	    "<hr><h1>Runtime Warning/Errors</h1>\n",
	    "<tt>EXAMPLE_PATH</tt> was determined to be <tt>$expath</tt>\n",
	    "<p><table border=\"0\" cellspacing=\"1\">\n<tr>\n";
	$i = 0;
	foreach $line (sort keys %ERRORS){
	    $ref = &GetRef($line);
	    if($i % 4 == 0){ 
		print FO "</tr>\n<tr>\n";
		$i = 0;
	    }
	    print FO "<td><a href=\"#$ref\">$line</a></td>\n";
	    $i++;
	}
	while ($i < 4){ print FO "<td>&nbsp;</td>"; $i++;}
	if($i == 4){    print FO "</tr>\n";}
	print FO "</table>\n";

	# Now dislay the errors
	foreach $line (sort keys %ERRORS){
	    $ref = &GetRef($line);
	    print FO "<p><a name=\"$ref\"></a>$line\n<blockquote><pre>\n";
	    @items = split(/;/,$ERRORS{$line});
	    foreach $tmp (@items){
		print FO "$tmp\n";
	    }
	    print FO "</pre></blockquote>\n";
	}
	foreach $line (@TAIL){ print FO "$line\n";}
	close(FO);


	#
	# Re-write the index file
	#
	open(FO,">$TARGETD/dox$SUBDIR/html/index.html");
	foreach $line (@HEAD){ print FO "$line\n";}
	print FO 
	    "<hr><h1>$PROJECT Documentation</h1>\n",
	    "<p>\n",
	    "<ul>",
	    "<li><a href=\"doxycron-errors.html\">Runtime warnings</a>",
	    "<li><a href=\"/STAR/comp/sofi/doxygen/\">User documentation</a>",
	    "</ul>\n";

	foreach $line (@TAIL){ print FO "$line\n";}
	close(FO);
    }
}


# delete the log now
unlink("$tmpf.log");


# File to Ref
sub GetRef
{
    my($line)=@_;
    $line =~ s/[\.\[\]:\(\)]/_/g;
    $line =~ s/\s//g;
    $line;
}


#
# Todo:
#   - Now that it works well, clean it up for clarity ...
#
#


sub CfgCreate
{
    my($file)=@_;

    if( ! open(FO,">$file") ){ return 0;}
    print FO qq~

# Doxyfile 1.2.12-20011125

# This file describes the settings to be used by the documentation system
# doxygen (www.doxygen.org) for a project
#
# All text after a hash (#) is considered a comment and will be ignored
# The format is:
#       TAG = value [value, ...]
# For lists items can also be appended using:
#       TAG += value [value, ...]
# Values that contain spaces should be placed between quotes (" ")

#---------------------------------------------------------------------------
# General configuration options
#---------------------------------------------------------------------------

# The PROJECT_NAME tag is a single word (or a sequence of words surrounded 
# by quotes) that should identify the project.

PROJECT_NAME           = "StRoot"

# The PROJECT_NUMBER tag can be used to enter a project or revision number. 
# This could be handy for archiving the generated documentation or 
# if some version control system is used.

PROJECT_NUMBER         = 1

# The OUTPUT_DIRECTORY tag is used to specify the (relative or absolute) 
# base path where the generated documentation will be put. 
# If a relative path is entered, it will be relative to the location 
# where doxygen was started. If left blank the current directory will be used.

OUTPUT_DIRECTORY       = Auto->/afs/rhic/star/doc/www/html/tmp./dox

# The OUTPUT_LANGUAGE tag is used to specify the language in which all 
# documentation generated by doxygen is written. Doxygen will use this 
# information to generate all constant output in the proper language. 
# The default language is English, other supported languages are: 
# Brazilian, Chinese, Croatian, Czech, Danish, Dutch, Finnish, French, 
# German, Hungarian, Italian, Japanese, Korean, Norwegian, Polish, 
# Portuguese, Romanian, Russian, Slovak, Slovene, Spanish and Swedish.

OUTPUT_LANGUAGE        = English

# If the EXTRACT_ALL tag is set to YES doxygen will assume all entities in 
# documentation are documented, even if no documentation was available. 
# Private class members and static file members will be hidden unless 
# the EXTRACT_PRIVATE and EXTRACT_STATIC tags are set to YES

EXTRACT_ALL            = NO

# If the EXTRACT_PRIVATE tag is set to YES all private members of a class 
# will be included in the documentation.

EXTRACT_PRIVATE        = NO

# If the EXTRACT_STATIC tag is set to YES all static members of a file 
# will be included in the documentation.

EXTRACT_STATIC         = NO

# If the HIDE_UNDOC_MEMBERS tag is set to YES, Doxygen will hide all 
# undocumented members of documented classes, files or namespaces. 
# If set to NO (the default) these members will be included in the 
# various overviews, but no documentation section is generated. 
# This option has no effect if EXTRACT_ALL is enabled.

HIDE_UNDOC_MEMBERS     = NO

# If the HIDE_UNDOC_CLASSES tag is set to YES, Doxygen will hide all 
# undocumented classes that are normally visible in the class hierarchy. 
# If set to NO (the default) these class will be included in the various 
# overviews. This option has no effect if EXTRACT_ALL is enabled.

HIDE_UNDOC_CLASSES     = NO

# If the BRIEF_MEMBER_DESC tag is set to YES (the default) Doxygen will 
# include brief member descriptions after the members that are listed in 
# the file and class documentation (similar to JavaDoc). 
# Set to NO to disable this.

BRIEF_MEMBER_DESC      = YES

# If the REPEAT_BRIEF tag is set to YES (the default) Doxygen will prepend 
# the brief description of a member or function before the detailed description. 
# Note: if both HIDE_UNDOC_MEMBERS and BRIEF_MEMBER_DESC are set to NO, the 
# brief descriptions will be completely suppressed.

REPEAT_BRIEF           = YES

# If the ALWAYS_DETAILED_SEC and REPEAT_BRIEF tags are both set to YES then 
# Doxygen will generate a detailed section even if there is only a brief 
# description.

ALWAYS_DETAILED_SEC    = NO

# If the FULL_PATH_NAMES tag is set to YES then Doxygen will prepend the full 
# path before files name in the file list and in the header files. If set 
# to NO the shortest path that makes the file name unique will be used.

FULL_PATH_NAMES        = YES

# If the FULL_PATH_NAMES tag is set to YES then the STRIP_FROM_PATH tag 
# can be used to strip a user defined part of the path. Stripping is 
# only done if one of the specified strings matches the left-hand part of 
# the path. It is allowed to use relative paths in the argument list.

STRIP_FROM_PATH        = Auto->\$INPUT/

# The INTERNAL_DOCS tag determines if documentation 
# that is typed after a \internal command is included. If the tag is set 
# to NO (the default) then the documentation will be excluded. 
# Set it to YES to include the internal documentation.

INTERNAL_DOCS          = NO

# Setting the STRIP_CODE_COMMENTS tag to YES (the default) will instruct 
# doxygen to hide any special comment blocks from generated source code 
# fragments. Normal C and C++ comments will always remain visible.

STRIP_CODE_COMMENTS    = YES

# If the CASE_SENSE_NAMES tag is set to NO then Doxygen will only generate 
# file names in lower case letters. If set to YES upper case letters are also 
# allowed. This is useful if you have classes or files whose names only differ 
# in case and if your file system supports case sensitive file names. Windows 
# users are adviced to set this option to NO.

CASE_SENSE_NAMES       = YES

# If the SHORT_NAMES tag is set to YES, doxygen will generate much shorter 
# (but less readable) file names. This can be useful is your file systems 
# doesn't support long names like on DOS, Mac, or CD-ROM.

SHORT_NAMES            = NO

# If the HIDE_SCOPE_NAMES tag is set to NO (the default) then Doxygen 
# will show members with their full class and namespace scopes in the 
# documentation. If set to YES the scope will be hidden.

HIDE_SCOPE_NAMES       = NO

# If the VERBATIM_HEADERS tag is set to YES (the default) then Doxygen 
# will generate a verbatim copy of the header file for each class for 
# which an include is specified. Set to NO to disable this.

VERBATIM_HEADERS       = YES

# If the SHOW_INCLUDE_FILES tag is set to YES (the default) then Doxygen 
# will put list of the files that are included by a file in the documentation 
# of that file.

SHOW_INCLUDE_FILES     = YES

# If the JAVADOC_AUTOBRIEF tag is set to YES then Doxygen 
# will interpret the first line (until the first dot) of a JavaDoc-style 
# comment as the brief description. If set to NO, the JavaDoc 
# comments  will behave just like the Qt-style comments (thus requiring an 
# explict \@brief command for a brief description.

JAVADOC_AUTOBRIEF      = NO

# If the INHERIT_DOCS tag is set to YES (the default) then an undocumented 
# member inherits the documentation from any documented member that it 
# reimplements.

INHERIT_DOCS           = YES

# If the INLINE_INFO tag is set to YES (the default) then a tag [inline] 
# is inserted in the documentation for inline members.

INLINE_INFO            = YES

# If the SORT_MEMBER_DOCS tag is set to YES (the default) then doxygen 
# will sort the (detailed) documentation of file and class members 
# alphabetically by member name. If set to NO the members will appear in 
# declaration order.

SORT_MEMBER_DOCS       = YES

# If member grouping is used in the documentation and the DISTRIBUTE_GROUP_DOC 
# tag is set to YES, then doxygen will reuse the documentation of the first 
# member in the group (if any) for the other members of the group. By default 
# all members of a group must be documented explicitly.

DISTRIBUTE_GROUP_DOC   = NO

# The TAB_SIZE tag can be used to set the number of spaces in a tab. 
# Doxygen uses this value to replace tabs by spaces in code fragments.

TAB_SIZE               = 8

# The GENERATE_TODOLIST tag can be used to enable (YES) or 
# disable (NO) the todo list. This list is created by putting \todo 
# commands in the documentation.

GENERATE_TODOLIST      = YES

# The GENERATE_TESTLIST tag can be used to enable (YES) or 
# disable (NO) the test list. This list is created by putting \test 
# commands in the documentation.

GENERATE_TESTLIST      = YES

# The GENERATE_BUGLIST tag can be used to enable (YES) or 
# disable (NO) the bug list. This list is created by putting \bug 
# commands in the documentation.

GENERATE_BUGLIST       = YES

# This tag can be used to specify a number of aliases that acts 
# as commands in the documentation. An alias has the form "name=value". 
# For example adding "sideeffect=\par Side Effects:\n" will allow you to 
# put the command \sideeffect (or \@sideeffect) in the documentation, which 
# will result in a user defined paragraph with heading "Side Effects:". 
# You can put \n's in the value part of an alias to insert newlines.

ALIASES                = 

# The ENABLED_SECTIONS tag can be used to enable conditional 
# documentation sections, marked by \if sectionname ... \endif.

ENABLED_SECTIONS       = 

# The MAX_INITIALIZER_LINES tag determines the maximum number of lines 
# the initial value of a variable or define consist of for it to appear in 
# the documentation. If the initializer consists of more lines than specified 
# here it will be hidden. Use a value of 0 to hide initializers completely. 
# The appearance of the initializer of individual variables and defines in the 
# documentation can be controlled using \showinitializer or \hideinitializer 
# command in the documentation regardless of this setting.

MAX_INITIALIZER_LINES  = 30

# Set the OPTIMIZE_OUTPUT_FOR_C tag to YES if your project consists of C sources 
# only. Doxygen will then generate output that is more tailored for C. 
# For instance some of the names that are used will be different. The list 
# of all members will be omitted, etc.

OPTIMIZE_OUTPUT_FOR_C  = NO

# Set the SHOW_USED_FILES tag to NO to disable the list of files generated 
# at the bottom of the documentation of classes and structs. If set to YES the 
# list will mention the files that were used to generate the documentation.

SHOW_USED_FILES        = YES

#---------------------------------------------------------------------------
# configuration options related to warning and progress messages
#---------------------------------------------------------------------------

# The QUIET tag can be used to turn on/off the messages that are generated 
# by doxygen. Possible values are YES and NO. If left blank NO is used.

QUIET                  = NO

# The WARNINGS tag can be used to turn on/off the warning messages that are 
# generated by doxygen. Possible values are YES and NO. If left blank 
# NO is used.

WARNINGS               = YES

# If WARN_IF_UNDOCUMENTED is set to YES, then doxygen will generate warnings 
# for undocumented members. If EXTRACT_ALL is set to YES then this flag will 
# automatically be disabled.

WARN_IF_UNDOCUMENTED   = NO

# The WARN_FORMAT tag determines the format of the warning messages that 
# doxygen can produce. The string should contain the \$file, \$line, and \$text 
# tags, which will be replaced by the file and line number from which the 
# warning originated and the warning text.

WARN_FORMAT            = 

# The WARN_LOGFILE tag can be used to specify a file to which warning 
# and error messages should be written. If left blank the output is written 
# to stderr.

WARN_LOGFILE           = 

#---------------------------------------------------------------------------
# configuration options related to the input files
#---------------------------------------------------------------------------

# The INPUT tag can be used to specify the files and/or directories that contain 
# documented source files. You may enter file names like "myfile.cpp" or 
# directories like "/usr/src/myproject". Separate the files or directories 
# with spaces.

INPUT                  = Auto->/afs/rhic/star/packages/dev/StRoot

# If the value of the INPUT tag contains directories, you can use the 
# FILE_PATTERNS tag to specify one or more wildcard pattern (like *.cpp 
# and *.h) to filter out the source-files in the directories. If left 
# blank file matching one of the following patterns are included: 
# *.c *.cc *.cxx *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.h *.hh *.hxx *.hpp 
# *.h++ *.idl

FILE_PATTERNS          = 

# The RECURSIVE tag can be used to turn specify whether or not subdirectories 
# should be searched for input files as well. Possible values are YES and NO. 
# If left blank NO is used.

RECURSIVE              = YES

# The EXCLUDE tag can be used to specify files and/or directories that should 
# excluded from the INPUT source files. This way you can easily exclude a 
# subdirectory from a directory tree whose root is specified with the INPUT tag.

EXCLUDE                = /html /doc 

# If the value of the INPUT tag contains directories, you can use the 
# EXCLUDE_PATTERNS tag to specify one or more wildcard patterns to exclude 
# certain files from those directories.

EXCLUDE_PATTERNS       = 

# The EXAMPLE_PATH tag can be used to specify one or more files or 
# directories that contain example code fragments that are included (see 
# the \include command).

EXAMPLE_PATH           = Auto->\$INPUT/*/examples

# If the value of the EXAMPLE_PATH tag contains directories, you can use the 
# EXAMPLE_PATTERNS tag to specify one or more wildcard pattern (like *.cpp 
# and *.h) to filter out the source-files in the directories. If left 
# blank all files are included.

EXAMPLE_PATTERNS       = 

# If the EXAMPLE_RECURSIVE tag is set to YES then subdirectories will be 
# searched for input files to be used with the \include or \dontinclude 
# commands irrespective of the value of the RECURSIVE tag. 
# Possible values are YES and NO. If left blank NO is used.

EXAMPLE_RECURSIVE      = NO

# The IMAGE_PATH tag can be used to specify one or more files or 
# directories that contain image that are included in the documentation (see 
# the \image command).

IMAGE_PATH             = 

# The INPUT_FILTER tag can be used to specify a program that doxygen should 
# invoke to filter for each input file. Doxygen will invoke the filter program 
# by executing (via popen()) the command <filter> <input-file>, where <filter> 
# is the value of the INPUT_FILTER tag, and <input-file> is the name of an 
# input file. Doxygen will then use the output that the filter program writes 
# to standard output.

INPUT_FILTER           = 

# If the FILTER_SOURCE_FILES tag is set to YES, the input filter (if set using 
# INPUT_FILTER) will be used to filter the input files when producing source 
# files to browse.

FILTER_SOURCE_FILES    = NO

#---------------------------------------------------------------------------
# configuration options related to source browsing
#---------------------------------------------------------------------------

# If the SOURCE_BROWSER tag is set to YES then a list of source files will 
# be generated. Documented entities will be cross-referenced with these sources.

SOURCE_BROWSER         = YES

# Setting the INLINE_SOURCES tag to YES will include the body 
# of functions and classes directly in the documentation.

INLINE_SOURCES         = NO

# If the REFERENCED_BY_RELATION tag is set to YES (the default) 
# then for each documented function all documented 
# functions referencing it will be listed.

REFERENCED_BY_RELATION = YES

# If the REFERENCES_RELATION tag is set to YES (the default) 
# then for each documented function all documented entities 
# called/used by that function will be listed.

REFERENCES_RELATION    = YES

#---------------------------------------------------------------------------
# configuration options related to the alphabetical class index
#---------------------------------------------------------------------------

# If the ALPHABETICAL_INDEX tag is set to YES, an alphabetical index 
# of all compounds will be generated. Enable this if the project 
# contains a lot of classes, structs, unions or interfaces.

ALPHABETICAL_INDEX     = YES

# If the alphabetical index is enabled (see ALPHABETICAL_INDEX) then 
# the COLS_IN_ALPHA_INDEX tag can be used to specify the number of columns 
# in which this list will be split (can be a number in the range [1..20])

COLS_IN_ALPHA_INDEX    = 5

# In case all classes in a project start with a common prefix, all 
# classes will be put under the same header in the alphabetical index. 
# The IGNORE_PREFIX tag can be used to specify one or more prefixes that 
# should be ignored while generating the index headers.

IGNORE_PREFIX          = 

#---------------------------------------------------------------------------
# configuration options related to the HTML output
#---------------------------------------------------------------------------

# If the GENERATE_HTML tag is set to YES (the default) Doxygen will 
# generate HTML output.

GENERATE_HTML          = YES

# The HTML_OUTPUT tag is used to specify where the HTML docs will be put. 
# If a relative path is entered the value of OUTPUT_DIRECTORY will be 
# put in front of it. If left blank `html' will be used as the default path.

HTML_OUTPUT            = 

# The HTML_HEADER tag can be used to specify a personal HTML header for 
# each generated HTML page. If it is left blank doxygen will generate a 
# standard header.

HTML_HEADER            = 

# The HTML_FOOTER tag can be used to specify a personal HTML footer for 
# each generated HTML page. If it is left blank doxygen will generate a 
# standard footer.

HTML_FOOTER            = 

# The HTML_STYLESHEET tag can be used to specify a user defined cascading 
# style sheet that is used by each HTML page. It can be used to 
# fine-tune the look of the HTML output. If the tag is left blank doxygen 
# will generate a default style sheet

HTML_STYLESHEET        = 

# If the HTML_ALIGN_MEMBERS tag is set to YES, the members of classes, 
# files or namespaces will be aligned in HTML using tables. If set to 
# NO a bullet list will be used.

HTML_ALIGN_MEMBERS     = YES

# If the GENERATE_HTMLHELP tag is set to YES, additional index files 
# will be generated that can be used as input for tools like the 
# Microsoft HTML help workshop to generate a compressed HTML help file (.chm) 
# of the generated HTML documentation.

GENERATE_HTMLHELP      = NO

# If the GENERATE_HTMLHELP tag is set to YES, the GENERATE_CHI flag 
# controls if a separate .chi index file is generated (YES) or that 
# it should be included in the master .chm file (NO).

GENERATE_CHI           = NO

# If the GENERATE_HTMLHELP tag is set to YES, the BINARY_TOC flag 
# controls whether a binary table of contents is generated (YES) or a 
# normal table of contents (NO) in the .chm file.

BINARY_TOC             = NO

# The TOC_EXPAND flag can be set to YES to add extra items for group members 
# to the contents of the Html help documentation and to the tree view.

TOC_EXPAND             = NO

# The DISABLE_INDEX tag can be used to turn on/off the condensed index at 
# top of each HTML page. The value NO (the default) enables the index and 
# the value YES disables it.

DISABLE_INDEX          = NO

# This tag can be used to set the number of enum values (range [1..20]) 
# that doxygen will group on one line in the generated HTML documentation.

ENUM_VALUES_PER_LINE   = 4

# If the GENERATE_TREEVIEW tag is set to YES, a side panel will be
# generated containing a tree-like index structure (just like the one that 
# is generated for HTML Help). For this to work a browser that supports 
# JavaScript and frames is required (for instance Mozilla, Netscape 4.0+, 
# or Internet explorer 4.0+). Note that for large projects the tree generation 
# can take a very long time. In such cases it is better to disable this feature. 
# Windows users are probably better off using the HTML help feature.

GENERATE_TREEVIEW      = NO

# If the treeview is enabled (see GENERATE_TREEVIEW) then this tag can be 
# used to set the initial width (in pixels) of the frame in which the tree 
# is shown.

TREEVIEW_WIDTH         = 250

#---------------------------------------------------------------------------
# configuration options related to the LaTeX output
#---------------------------------------------------------------------------

# If the GENERATE_LATEX tag is set to YES (the default) Doxygen will 
# generate Latex output.

GENERATE_LATEX         = YES

# The LATEX_OUTPUT tag is used to specify where the LaTeX docs will be put. 
# If a relative path is entered the value of OUTPUT_DIRECTORY will be 
# put in front of it. If left blank `latex' will be used as the default path.

LATEX_OUTPUT           = 

# If the COMPACT_LATEX tag is set to YES Doxygen generates more compact 
# LaTeX documents. This may be useful for small projects and may help to 
# save some trees in general.

COMPACT_LATEX          = NO

# The PAPER_TYPE tag can be used to set the paper type that is used 
# by the printer. Possible values are: a4, a4wide, letter, legal and 
# executive. If left blank a4wide will be used.

PAPER_TYPE             = letter

# The EXTRA_PACKAGES tag can be to specify one or more names of LaTeX 
# packages that should be included in the LaTeX output.

EXTRA_PACKAGES         = 

# The LATEX_HEADER tag can be used to specify a personal LaTeX header for 
# the generated latex document. The header should contain everything until 
# the first chapter. If it is left blank doxygen will generate a 
# standard header. Notice: only use this tag if you know what you are doing!

LATEX_HEADER           = 

# If the PDF_HYPERLINKS tag is set to YES, the LaTeX that is generated 
# is prepared for conversion to pdf (using ps2pdf). The pdf file will 
# contain links (just like the HTML output) instead of page references 
# This makes the output suitable for online browsing using a pdf viewer.

PDF_HYPERLINKS         = NO

# If the USE_PDFLATEX tag is set to YES, pdflatex will be used instead of 
# plain latex in the generated Makefile. Set this option to YES to get a 
# higher quality PDF documentation.

USE_PDFLATEX           = NO

# If the LATEX_BATCHMODE tag is set to YES, doxygen will add the \\batchmode. 
# command to the generated LaTeX files. This will instruct LaTeX to keep 
# running if errors occur, instead of asking the user for help. 
# This option is also used when generating formulas in HTML.

LATEX_BATCHMODE        = NO

#---------------------------------------------------------------------------
# configuration options related to the RTF output
#---------------------------------------------------------------------------

# If the GENERATE_RTF tag is set to YES Doxygen will generate RTF output 
# The RTF output is optimised for Word 97 and may not look very pretty with 
# other RTF readers or editors.

GENERATE_RTF           = NO

# The RTF_OUTPUT tag is used to specify where the RTF docs will be put. 
# If a relative path is entered the value of OUTPUT_DIRECTORY will be 
# put in front of it. If left blank `rtf' will be used as the default path.

RTF_OUTPUT             = 

# If the COMPACT_RTF tag is set to YES Doxygen generates more compact 
# RTF documents. This may be useful for small projects and may help to 
# save some trees in general.

COMPACT_RTF            = NO

# If the RTF_HYPERLINKS tag is set to YES, the RTF that is generated 
# will contain hyperlink fields. The RTF file will 
# contain links (just like the HTML output) instead of page references. 
# This makes the output suitable for online browsing using WORD or other 
# programs which support those fields. 
# Note: wordpad (write) and others do not support links.

RTF_HYPERLINKS         = NO

# Load stylesheet definitions from file. Syntax is similar to doxygen's 
# config file, i.e. a series of assigments. You only have to provide 
# replacements, missing definitions are set to their default value.

RTF_STYLESHEET_FILE    = 

# Set optional variables used in the generation of an rtf document. 
# Syntax is similar to doxygen's config file.

RTF_EXTENSIONS_FILE    = 

#---------------------------------------------------------------------------
# configuration options related to the man page output
#---------------------------------------------------------------------------

# If the GENERATE_MAN tag is set to YES (the default) Doxygen will 
# generate man pages

GENERATE_MAN           = NO

# The MAN_OUTPUT tag is used to specify where the man pages will be put. 
# If a relative path is entered the value of OUTPUT_DIRECTORY will be 
# put in front of it. If left blank `man' will be used as the default path.

MAN_OUTPUT             = 

# The MAN_EXTENSION tag determines the extension that is added to 
# the generated man pages (default is the subroutine's section .3)

MAN_EXTENSION          = 

# If the MAN_LINKS tag is set to YES and Doxygen generates man output,
# then it will generate one additional man file for each entity
# documented in the real man page(s). These additional files
# only source the real man page, but without them the man command
# would be unable to find the correct page. The default is NO.

MAN_LINKS              = NO

#---------------------------------------------------------------------------
# configuration options related to the XML output
#---------------------------------------------------------------------------

# If the GENERATE_XML tag is set to YES Doxygen will 
# generate an XML file that captures the structure of 
# the code including all documentation. Note that this 
# feature is still experimental and incomplete at the 
# moment.

GENERATE_XML           = NO

#---------------------------------------------------------------------------
# Configuration options related to the preprocessor   
#---------------------------------------------------------------------------

# If the ENABLE_PREPROCESSING tag is set to YES (the default) Doxygen will 
# evaluate all C-preprocessor directives found in the sources and include 
# files.

ENABLE_PREPROCESSING   = YES

# If the MACRO_EXPANSION tag is set to YES Doxygen will expand all macro 
# names in the source code. If set to NO (the default) only conditional 
# compilation will be performed. Macro expansion can be done in a controlled 
# way by setting EXPAND_ONLY_PREDEF to YES.

MACRO_EXPANSION        = NO

# If the EXPAND_ONLY_PREDEF and MACRO_EXPANSION tags are both set to YES 
# then the macro expansion is limited to the macros specified with the 
# PREDEFINED and EXPAND_AS_PREDEFINED tags.

EXPAND_ONLY_PREDEF     = NO

# If the SEARCH_INCLUDES tag is set to YES (the default) the includes files 
# in the INCLUDE_PATH (see below) will be search if a #include is found.

SEARCH_INCLUDES        = YES

# The INCLUDE_PATH tag can be used to specify one or more directories that 
# contain include files that are not input files but should be processed by 
# the preprocessor.

INCLUDE_PATH           = 

# You can use the INCLUDE_FILE_PATTERNS tag to specify one or more wildcard 
# patterns (like *.h and *.hpp) to filter out the header-files in the 
# directories. If left blank, the patterns specified with FILE_PATTERNS will 
# be used.

INCLUDE_FILE_PATTERNS  = 

# The PREDEFINED tag can be used to specify one or more macro names that 
# are defined before the preprocessor is started (similar to the -D option of 
# gcc). The argument of the tag is a list of macros of the form: name 
# or name=definition (no spaces). If the definition and the = are 
# omitted =1 is assumed.

PREDEFINED             = 

# If the MACRO_EXPANSION and EXPAND_PREDEF_ONLY tags are set to YES then 
# this tag can be used to specify a list of macro names that should be expanded. 
# The macro definition that is found in the sources will be used. 
# Use the PREDEFINED tag if you want to use a different macro definition.

EXPAND_AS_DEFINED      = 

# If the SKIP_FUNCTION_MACROS tag is set to YES (the default) then 
# doxygen's preprocessor will remove all function-like macros that are alone 
# on a line and do not end with a semicolon. Such function macros are typically 
# used for boiler-plate code, and will confuse the parser if not removed.

SKIP_FUNCTION_MACROS   = YES

#---------------------------------------------------------------------------
# Configuration::addtions related to external references   
#---------------------------------------------------------------------------

# The TAGFILES tag can be used to specify one or more tagfiles.

TAGFILES               = 

# When a file name is specified after GENERATE_TAGFILE, doxygen will create 
# a tag file that is based on the input files it reads.

GENERATE_TAGFILE       = index.tag

# If the ALLEXTERNALS tag is set to YES all external classes will be listed 
# in the class index. If set to NO only the inherited external classes 
# will be listed.

ALLEXTERNALS           = NO

# The PERL_PATH should be the absolute path and name of the perl script 
# interpreter (i.e. the result of `which perl').

PERL_PATH              = 

#---------------------------------------------------------------------------
# Configuration options related to the dot tool   
#---------------------------------------------------------------------------

# If the CLASS_DIAGRAMS tag is set to YES (the default) Doxygen will 
# generate a inheritance diagram (in Html, RTF and LaTeX) for classes with base or 
# super classes. Setting the tag to NO turns the diagrams off. Note that this 
# option is superceded by the HAVE_DOT option below. This is only a fallback. It is 
# recommended to install and use dot, since it yield more powerful graphs.

CLASS_DIAGRAMS         = YES

# If you set the HAVE_DOT tag to YES then doxygen will assume the dot tool is 
# available from the path. This tool is part of Graphviz, a graph visualization 
# toolkit from AT&T and Lucent Bell Labs. The other options in this section 
# have no effect if this option is set to NO (the default)

HAVE_DOT               = NO

# If the CLASS_GRAPH and HAVE_DOT tags are set to YES then doxygen 
# will generate a graph for each documented class showing the direct and 
# indirect inheritance relations. Setting this tag to YES will force the 
# the CLASS_DIAGRAMS tag to NO.

CLASS_GRAPH            = YES

# If the COLLABORATION_GRAPH and HAVE_DOT tags are set to YES then doxygen 
# will generate a graph for each documented class showing the direct and 
# indirect implementation dependencies (inheritance, containment, and 
# class references variables) of the class with other documented classes.

COLLABORATION_GRAPH    = YES

# If set to YES, the inheritance and collaboration graphs will show the 
# relations between templates and their instances.

TEMPLATE_RELATIONS     = YES

# If set to YES, the inheritance and collaboration graphs will hide 
# inheritance and usage relations if the target is undocumented 
# or is not a class.

HIDE_UNDOC_RELATIONS   = YES

# If the ENABLE_PREPROCESSING, SEARCH_INCLUDES, INCLUDE_GRAPH, and HAVE_DOT 
# tags are set to YES then doxygen will generate a graph for each documented 
# file showing the direct and indirect include dependencies of the file with 
# other documented files.

INCLUDE_GRAPH          = YES

# If the ENABLE_PREPROCESSING, SEARCH_INCLUDES, INCLUDED_BY_GRAPH, and 
# HAVE_DOT tags are set to YES then doxygen will generate a graph for each 
# documented header file showing the documented files that directly or 
# indirectly include this file.

INCLUDED_BY_GRAPH      = YES

# If the GRAPHICAL_HIERARCHY and HAVE_DOT tags are set to YES then doxygen 
# will graphical hierarchy of all classes instead of a textual one.

GRAPHICAL_HIERARCHY    = YES

# The tag DOT_PATH can be used to specify the path where the dot tool can be 
# found. If left blank, it is assumed the dot tool can be found on the path.

DOT_PATH               = 

# The DOTFILE_DIRS tag can be used to specify one or more directories that 
# contain dot files that are included in the documentation (see the 
# \dotfile command).

DOTFILE_DIRS           = 

# The MAX_DOT_GRAPH_WIDTH tag can be used to set the maximum allowed width 
# (in pixels) of the graphs generated by dot. If a graph becomes larger than 
# this value, doxygen will try to truncate the graph, so that it fits within 
# the specified constraint. Beware that most browsers cannot cope with very 
# large images.

MAX_DOT_GRAPH_WIDTH    = 1024

# The MAX_DOT_GRAPH_HEIGHT tag can be used to set the maximum allows height 
# (in pixels) of the graphs generated by dot. If a graph becomes larger than 
# this value, doxygen will try to truncate the graph, so that it fits within 
# the specified constraint. Beware that most browsers cannot cope with very 
# large images.

MAX_DOT_GRAPH_HEIGHT   = 1024

# If the GENERATE_LEGEND tag is set to YES (the default) Doxygen will 
# generate a legend page explaining the meaning of the various boxes and 
# arrows in the dot generated graphs.

GENERATE_LEGEND        = YES

# If the DOT_CLEANUP tag is set to YES (the default) Doxygen will 
# remove the intermedate dot files that are used to generate 
# the various graphs.

DOT_CLEANUP            = YES

#---------------------------------------------------------------------------
# Configuration::addtions related to the search engine   
#---------------------------------------------------------------------------

# The SEARCHENGINE tag specifies whether or not a search engine should be 
# used. If set to NO the values of all tags below this one will be ignored.

SEARCHENGINE           = YES

# The CGI_NAME tag should be the name of the CGI script that 
# starts the search engine (doxysearch) with the correct parameters. 
# A script with this name will be generated by doxygen.

CGI_NAME               = Fixed->search.cgi

# The CGI_URL tag should be the absolute URL to the directory where the 
# cgi binaries are located. See the documentation of your http daemon for 
# details.

CGI_URL                = Auto->http://www.star.bnl.gov/cgi-bin/dox

# The DOC_URL tag should be the absolute URL to the directory where the 
# documentation is located. If left blank the absolute path to the 
# documentation, with file:// prepended to it, will be used.

DOC_URL                = Auto->http://www.star.bnl.gov/webdatanfs/dox/html

# The DOC_ABSPATH tag should be the absolute path to the directory where the 
# documentation is located. If left blank the directory on the local machine 
# will be used.

DOC_ABSPATH            = Auto->\$INPUT/dox/html

# The BIN_ABSPATH tag must point to the directory where the doxysearch binary 
# is installed.

BIN_ABSPATH            = Fixed->/usr/bin/

# The EXT_DOC_PATHS tag can be used to specify one or more paths to 
# documentation generated for other projects. This allows doxysearch to search 
# the documentation for these projects as well.

EXT_DOC_PATHS          = 

    ~;
    1;
}
