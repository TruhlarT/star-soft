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
# Currently supported : html and latex directories
# will be moved to their final destination by this
# script.
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

$TARGETD = "/afs/rhic/star/doc/www/html/comp-nfs";   # Working directory
$INDEXD  = "/afs/rhic/star/packages/dev/StRoot";     # Dir to scan
$PROJECT = "StRoot";                                 # Project name
$SUBDIR  = "";                                       # Sub-dir for output


# Eventually replace by @ARGV
$TARGETD = shift(@ARGV) if ( @ARGV );
$INDEXD  = shift(@ARGV) if ( @ARGV );
$PROJECT = shift(@ARGV) if ( @ARGV );
$SUBDIR  = shift(@ARGV) if ( @ARGV );


# -------------------------------------------------------------------------
$TMPDIR  = "/tmp";                                   # temp dir on cron node
$BINPATH = "/usr/bin/";                              # path to bin for 
                                                     # doxy-progs on Web server
$DOXYGEN = "/usr/bin/doxygen";                       # Redundant with this
$DOXYTAG = "/usr/bin/doxytag";                       # shows exe names 
$HTTPD   = "http://www.star.bnl.gov";                # HTTP Server
$URLPATH = "webdatanfs";                             # Base URL path





# -------------------------------------------------------------------
# Sanity checks
# -------------------------------------------------------------------
if( ! -e $DOXYGEN){
    print "Boomer ! Required $DOXYGEN is missing. Please, install\n";
    exit;
} 
if( ! -d "$TARGETD/dox"){
    print "Dooo  !! Directory $TARGETD/dox does not exists\n";
}
if( ! -e "$TARGETD/dox/$PROJECT.cfg"){
    print "Huuuu !! Missing config file $TARGETD/dox/$PROJECT.cfg . ".
	"Please create.\n";
    exit;
}


# -------------------------------------------------------------------
# Generate alternate config file i.e. a copy of the template
# from which several keywords will be auto-replaced by values
# based on passed parameters.
# -------------------------------------------------------------------
$tmpf = $TMPDIR."/doxygen$>-$$";
open(FI,"$TARGETD/dox/$PROJECT.cfg");
open(FO,">$tmpf.cfg");

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
	

    } elsif ($line =~ m/(HTML_OUTPUT.*=\s+)(.*)/){
	if( $2 eq ""){
	    push(@DIRS,"html");
	} else {
	    push(@DIRS,$2);
	}
    } elsif ($line =~ m/(LATEX_OUTPUT.*=\s+)(.*)/){
	if( $2 eq ""){
	    push(@DIRS,"latex");
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
    if( -d "$TARGETD/dox$SUBDIR/tmp$$/html"){
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
		$ERRORS{$el} .= ";$2";
	    } else {
		$ERRORS{$el}  = "$2";
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
	    "<a href=\"doxycron-errors.html\">Runtime warnings</a>\n";

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
