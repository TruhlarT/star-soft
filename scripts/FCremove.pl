#!/usr/bin/env perl

#
# Get a file list and mark all the files as un-available in DDB.
# Note that the format as been made flexible to accept a file
# list formatted by an HPSS index dump (i.e. one every 2 lines
# having some numbers and path starting with ".")
#
# Syntax is
#
# % FCremove.pl [{-s|-k}] FileList.lis  [StorageType] [Site] [Node]
#
# Use -s to mark the file as sanity=0 instead of available=0 .
#
# The last 3 arguments are non-mandatory and may revert
# to default.
#

use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;

if ($ARGV[0] eq "-s"){
    $sanity = 1;
    shift @ARGV;
}

$STORE = "";
$SITE  = "";
$FILIN = shift(@ARGV) if (@ARGV);
$STORE = shift(@ARGV) if (@ARGV);
$SITE  = shift(@ARGV) if (@ARGV);
$NODE  = shift(@ARGV) if (@ARGV);


open(FI,$FILIN) || die "Give a file name as input\n";

# Instantiate
$fileC = FileCatalog->new;

print "Password : ";
chomp($passwd = <STDIN>);
$fileC->connect("FC_admin",$passwd);


# Turn off module debugging and script debugging
$fileC->debug_off();

while ( defined($file = <FI>)){
    chomp($file);
    if ( substr($file,0,1) eq "."){
	$file = substr($file,1,length($file)-1);
    }
    if ($file =~ m/(.*\/)(.*)/){
	($path,$file) = ($1,$2);
	if ( $file =~ /::/){
	    # Catalog format
	    ($tmp,$file) = split("::",$file);
	    $path .= $tmp;
	} else {
	    chop($path);
	}
	#print "$path $file\n";
	$fileC->set_context("path=$path",
			    "filename=$file");
	$fileC->set_context("storage=$STORE") if ($STORE ne "");
	$fileC->set_context("site=$SITE")     if ($SITE  ne "");
	$fileC->set_context("node=$NODE")     if ($NODE  ne "");


	if ($sanity){
	    $fileC->set_context("sanity=1");
	} else {
	    $fileC->set_context("available=1");
	}
	@all = $fileC->run_query("path","filename");
	if( $#all != -1 ){
	    # There is no need for a foreach loop here because
	    # path/filename can only be a unique result
	    #foreach (@all){
	    #($path,$file) = split("::",$_);
	    if ( $sanity ){
		print "Marking $path $file insane\n";
		$fileC->update_location("sanity",0);
	    } else {
		print "Disabling $path $file\n";
		$fileC->update_location("available",0);
	    }
	    #}
	} else {
	    print "Did not find $path/$file (already marked ?)\n";
	}
    }
}

$fileC->destroy();
