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
# OUTPUT_DIRECTORY will default to $TARGETD/dox/$SUBDIR
# However, for the processing, everything will be done
# in a temporary sub-directory and moved only after
# everything is done. This was chosen to avoid 
# interference with already existing documents and
# so we maintain a clean tree.
# Currently supported : html and latex directories
# will be moved to their final destination by this
# script.
#
# The INPUT directory is defaulted to $INDEXD.
#
# The doxygen project name is assumed to match
# the $PROJECT variable. Currently, this should
# be a single name only (no space) since there
# is an assumption project-name/Config file.
#
# Note also that this script accepts arguments
# superseding teh default values that is :
#  $TARGETD
#  $INDEXD
#  $PROJECT
#  $SUBDIR
#
# In principle, anyboddy can then run this script
# and generate their own doc. This will be helpful
# for testing new configuration files.
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
$TMPDIR  = "/tmp";
$DOXYGEN = "/usr/bin/doxygen";
$DOXYSRCH= "/usr/bin/doxysearch";


# Sanity checks
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


$tmp = $TMPDIR."/doxygen$>-$$";

# Generate alternate config file
open(FI,"$TARGETD/dox/$PROJECT.cfg");
open(FO,">$tmp.cfg");
while ( defined($line = <FI>) ){
    chomp($line);
    if($line =~ m/(OUTPUT_DIRECTORY.*=\s+)(.*)/){
	# We add an extra level so we can do some cleanup
	# in between.
	$line = "OUTPUT_DIRECTORY       = $TARGETD/dox/$SUBDIR/tmp$$";
    } elsif ($line =~ m/(PROJECT_NAME.*=\s+\")(.*)(\")/){
	if($2 ne $PROJECT){
	    $line = "PROJECT_NAME           = \"$PROJECT\"";
	}
    } elsif ($line =~ m/(INPUT.*=\s+)(.*)/){
	if($2 ne $INDEXD){
	    $line = "INPUT                  = $INDEXD";
	}
	
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
    }
    print FO "$line\n";
}
close(FI);
close(FO);
chmod(0600,"$tmp.cfg");




# Create temporary sub-directories if necassary
if( ! -d "$TARGETD/dox/$SUBDIR"){
    print "Creating to structure  $TARGETD/dox/$SUBDIR\n";
    mkdir("$TARGETD/dox/$SUBDIR",0777);
}
if( ! -d "$TARGETD/dox/$SUBDIR/tmp$$"){
    print "Creating temporary dir $TARGETD/dox/$SUBDIR/tmp$$\n";
    mkdir("$TARGETD/dox/$SUBDIR/tmp$$",0777);
}




# Now, start using this file but also redirect all
# resulting output of doxygen to a temp file
if( -e "$tmp.cfg"){
    print "Running $DOXYGEN now ".localtime()."\n";
    system("cd $TMPDIR ; $DOXYGEN $tmp.cfg >&$tmp.log");
    unlink("$tmp.cfg");
} else {
    print "Action did not create a temporary configuration file\n";
}




# Check if the expected sub-directories were created
foreach $dir (@DIRS){
    if( -d "$TARGETD/dox/$SUBDIR/tmp$$/$dir"){
	# Rename the tmp-directories to target-directories
	# Take care of the old one first
	if( -d "$TARGETD/dox/$SUBDIR/$dir"){
	    if( -d "$TARGETD/dox/$SUBDIR/$dir.old"){
		#print "Removing old $TARGETD/dox/$SUBDIR/$dir.old\n";
		system("rm -fr $TARGETD/dox/$SUBDIR/$dir.old");
	    }
	    #print "Renaming current $TARGETD/dox/$SUBDIR/$dir\n";
	    rename("$TARGETD/dox/$SUBDIR/$dir",
		   "$TARGETD/dox/$SUBDIR/$dir.old");
	}
	# Rename tmp -> final destination
	print "Installing created $TARGETD/dox/$SUBDIR/$dir\n";
	rename("$TARGETD/dox/$SUBDIR/tmp$$/$dir",
	       "$TARGETD/dox/$SUBDIR/$dir");
    } else {
	print "Warning :: $dir not found\n";
    }
}
if( -d "$TARGETD/dox/$SUBDIR/tmp$$"){
    rmdir("$TARGETD/dox/$SUBDIR/tmp$$");
}



# Guess what ? We have a few interresting comments/warning
# generated from that pass. Parse it now ... NOT currently
# enabled.
if( 1==0){
    open(FI,"$tmp.log");
    while ( defined($line=<FI>) ){
	if($line =~ m/(.*)(:\d+\s+)(Warning:)(.*)/){
	    # I separated it because it may become a '|' list
	    # in the pattern. So far, only saw 'Warning'.
	    if( defined($ERRORS{$1}) ){
		$ERRORS{$1} .= "|$2$3$4";
	    } else {
		$ERRORS{$1}  = "$2$3$4";
	    }
	}
    }
}


# delete the log now
unlink("$tmp.log");


