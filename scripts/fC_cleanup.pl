#!/usr/bin/env perl 
#
# This is a command line utility to do a maintenance and cleanup
# of te FileCatalog database
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# Modified by J.Lauret, BNL
#

use lib "/afs/rhic/star/packages/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;
my $delay;

# Control variables
# The size of a batch to process at once.
my $batchsize = 1000;
my $mode;
my $cond_list;
my $state="";
my $passwd=undef;
my $kwrd="";
my $newval=undef;
my $user="";
my $keyw;
my $n;
my $confirm;

# Load the modules
my $fileC = FileCatalog->new;


# Turn off module debugging and script debugging
$fileC->debug_off();
$debug = 1;
$delay = 0;
$mode  = 1;  # check is the default
$confirm = 0;

# Parse the cvommand line arguments.
$count = 0;
while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-status"){
	$mode = 0;

    } elsif ($ARGV[$count] eq "-debug"){
	$fileC->debug_on();

    } elsif ($ARGV[$count] eq "-ucheck"){
	$mode = -1;
    } elsif ($ARGV[$count] eq "-check"){
	$mode = 1;

    } elsif ($ARGV[$count] eq "-nodebug"){
	$debug = 0;


    } elsif ($ARGV[$count] eq "-u"){
	$user      = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-p"){
	$passwd    = $ARGV[++$count];


    } elsif ($ARGV[$count] eq "-delete"){
	$mode      = 2;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-cdelete"){
	$mode      = 2;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-ddelete"){
	$mode      = 2;
	$delay     = 1;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-alla"){
	if ($mode != 2){
	    print "-alla works only with deletion keywords\n";
	} else {
	    $mode = -$mode;
	}

    } elsif ($ARGV[$count] eq "-doit"){
	$confirm = 1;

    } elsif ($ARGV[$count] eq "-mark"){
	$mode  = 3;
	$state = $ARGV[++$count];


    } elsif ($ARGV[$count] eq "-alter" || $ARGV[$count] eq "-modif"){
	$mode = ($ARGV[$count] eq "-alter")?4:-4;
	($kwrd,$newval) = split("=",$ARGV[++$count]);

    } elsif ($ARGV[$count] eq "-recheck"){
	$mode = 5;
    } elsif ($ARGV[$count] eq "-fdata"){
	$mode = 6;
    } elsif ($ARGV[$count] eq "-floc"){
	$mode = 7;
    } elsif ($ARGV[$count] eq "-trgc"){
	$mode = 8;
    } elsif ($ARGV[$count] eq "-boots"){
	$mode = 9;
	$keyw = $ARGV[++$count];


    } elsif ($ARGV[$count] eq "-cond"){
	$cond_list = $ARGV[++$count];
	if ($debug > 0) { print "The conditions list is $cond_list\n"; }


    } else {
	print "Wrong keyword used: ".$ARGV[$count]."\n";
	&Usage();
	exit;
    }
    $count++;
  }

if ($count == 0){
    &Usage();
    exit;
}

if ( $user eq ""){
    print "Password : ";
    chomp($passwd = <STDIN>);
    $fileC->connect_as("Admin","FC_admin",$passwd);
} else {
    $fileC->connect_as("Admin",$user,$passwd);
}



my $morerecords = 1;
my $start = 0;
while ($morerecords)
{
    $morerecords = 0;
    # Setting the context based on the swiches
    $fileC->clear_context();
    if (defined $cond_list){
	foreach (split(/,/,$cond_list)){
	    $fileC->set_context($_);
	}
    }

    if ($mode == 0){
	# First mode of operation - just get the file list and their availability
	print "Checking $start (+$batchsize) ".localtime()."\n";
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_delimeter("::");

	# Getting the data
	@output = $fileC->run_query("path","filename","available");

	# Check if there are any records left
	if (($#output + 1) == $batchsize)
	  { $morerecords = 1; }

	# Printing the output
	foreach (@output)
	  {
	    my ($path, $fname, $av) = split ("::");
	    print join("/",($path, $fname))." $av\n";
	}
	$start += $batchsize;



    } elsif ($mode*$mode == 1){
	# Second mode of operation - get the file list, select the available ones
	# and check if they really exist - if not, mark them as unavailable
	print "Checking mode=$mode $start (+$batchsize) ".localtime()."\n";
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	if ($mode == 1){
	    $fileC->set_context("available>0");
	} else {
	    # ONLY = 0
	    $fileC->set_context("available=0");
	}
	$fileC->set_delimeter("::");

	my $store=$fileC->get_context("storage");
	if( ! defined($store) ){
	    # Impose NFS to minimize errors
	    $store = "NFS";
	    $fileC->set_context("storage=NFS");
	} else {
	    if( $store eq "HPSS"){
		die "HPSS checking not immplemented yet\n";
	    }
	}

	# Getting the data
	@output = $fileC->run_query("path","filename","available","node","site");

	# Check if there are any records left
	#print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	$n = 0;
	foreach (@output){
	    my ($path, $fname,$available,$node,$site) = split ("::");

	    $fileC->clear_context();
	    $fileC->set_context("filename=$fname");
	    $fileC->set_context("path=$path");
	    $fileC->set_context("storage=$store");
	    $fileC->set_context("node=$node") if ($node ne "");
	    $fileC->set_context("site=$site") if ($site ne "");


	    if (-e $path."/".$fname){
		if ($mode == -1){
		    print "File  $site.$store://$node$path/$fname exists $available\n";
		    $n++;
		} elsif ($debug > 1){
		    print "Found  $site.$store://$node$path/$fname and avail=$available\n";
		}
	    } else {
		if ($mode == 1){
		    print "File  $site.$store://$node$path/$fname DOES NOT exist or is unavailable !\n";
		    $n++;
		}
	    }

	    if ($mode == 1){
		# mark it un-available
		$fileC->update_location("available",0,$confirm);
	    } else {
		# remark available
		$fileC->update_location("available",1,$confirm);
	    }

	}
	# We have modified records so the next ROW number
	# need to be offset by how many we just changed
	$start += ($batchsize - $n) if ($n <= $batchsize);

    } elsif ($mode == 2 || $mode*$mode == 4){
	# Delete records. Note that this function is EXTREMELY
	# dangerous now since any record can be deleted based
	# on context.
	my($rec,@items);
	print "Checking $start (+$batchsize) ".localtime()."\n";
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	if ($mode == -2){
	    $fileC->set_context("available<0");
	} else {
	    $fileC->set_context("available=0");
	}
	$fileC->set_delimeter("::");
	$fileC->set_delayed() if ($delay);

	my $store=$fileC->get_context("storage");
	if( ! defined($store) ){
	    # Impose NFS to minimize errors
	    $store = "NFS";
	    $fileC->set_context("storage=NFS");
	}


	if( $confirm ){
	    @items = $fileC->delete_records($confirm);
	    if( $debug ){
		foreach (@items){
		    print "Deleted $_\n";
		}
	    }

	    if ( $delay){
		#$fileC->print_delayed();
		$fileC->flush_delayed();
	    }
	} else {
	    @items = $fileC->run_query("site","node","storage","path","filename","available");
	    foreach (@items){
		print "$_\n";
	    }
	}

	if (($#items +1) == $batchsize){
	    $morerecords = 1;
	} else {
	    my(@rows);
	    print "Running post-deletion bootstrap\n";
	    $fileC->set_context("limit=100000000");
	    @rows = $fileC->bootstrap("runnumber",1);     print "Runnumber cleaned @rows\n" if (@rows);
	    @rows = $fileC->bootstrap("collision",1);     print "Collision cleaned @rows\n" if (@rows);
	    @rows = $fileC->bootstrap("configuration",1); print "Configuration cleaned @rows\n" if (@rows);
	}
	if ($confirm){
	    # we have shifted records
	    $start += ($batchsize - $#items -1) if ($#items < $batchsize);
	} else {
	    $start += $batchsize;
	    print "Use -doit to confirm deletion\n";
	}



    } elsif ( $mode == 3 ){
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	if ($debug>0){
	    if ($state eq "on"){
		print "Marking files as available\n";
	    } elsif ($state eq "off") {
		print "Marking files as unavailable\n";
	    } else {
		print "Marking files with available = $state\n";
	    }
	}

	# Marking the file as unavailable
	$fileC->set_context("limit=0");

	if ($state eq "on"){
	    $fileC->set_context("available=0");
	    $fileC->update_location("available",1,$confirm);
	} elsif ( $state eq "off") {
	    $fileC->set_context("available=1");
	    $fileC->update_location("available",0,$confirm);
	} else {
	    $fileC->set_context("available=1");
	    $fileC->update_location("available",$state,$confirm);
	}


    } elsif ( $mode*$mode == 16){
	$fileC->set_context("limit=$batchsize");
	if ($kwrd ne ""){
	    if( ! defined($newval) ){
		die "  You must specify a new value\n";
	    } else {
		print "Resetting keyword [$kwrd] to new value $newval $start ".localtime()."\n";
	    }
	} else {
	    die "Keyword is empty \n";
	}

	$fileC->set_delayed() if (! $confirm);
	if ($mode == 4){
	    $morerecords = $fileC->update_record($kwrd,"$newval",$confirm);
	} else {
	    my $delete=1;
	    $morerecords = $fileC->update_location($kwrd,$newval,$confirm,$delete);
	}
	if (! $confirm ){
	    $morerecords = 0;
	    print "Confirmed = $confirm . Use -doit for really updating\n";
	    $fileC->print_delayed();
	}
	# only for stat
	$start += $morerecords;


    } elsif ($mode == 5){
	# Fifth mode of operation - get the file list,
	# and check if they really exist - if not, mark them as unavailable
	# if yes - remark them as available
	print "Checking $start (+$batchsize) ".localtime()."\n";
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_context("all=1");
	$fileC->set_delimeter("::");


	my $store=$fileC->get_context("storage");
	if( ! defined($store) ){
	    # Impose NFS to minimize errors
	    $store = "NFS";
	    $fileC->set_context("storage=NFS");
	} else {
	    if( $store eq "HPSS"){
		die "HPSS checking not implemented yet\n";
	    }
	}

	# Getting the data
	@output = $fileC->run_query("path","filename","available","node","site");

	# Check if there are any records left
	#print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	$n = 0;
	foreach (@output){
	    my ($path, $fname, $av,$node, $site) = split ("::");
	    if (-e $path."/".$fname){
		if ($av == 0){
		    #if ($debug > 0)
		    #{
		    print "File $site.$store://$node$path/$fname exists\n";
		    #}
		    # Marking the file as available
		    $fileC->clear_context();
		    $fileC->set_context("filename=$fname");
		    $fileC->set_context("path=$path");
		    $fileC->set_context("available=0");
		    $fileC->set_context("storage=$store");
		    $fileC->set_context("node=$node") if ($node ne "");
		    $fileC->set_context("site=$site") if ($site ne "");
		    $n += $fileC->update_location("available",1);
		}
	    } else {
		if ($av == 1){
		    #if ($debug>0)
		    #{
		    print "File $site.$store://$node$path/$fname DOES NOT exist or is unavailable !\n";
		    #}
		    # Marking the file as unavailable
		    $fileC->clear_context();
		    $fileC->set_context("filename=$fname");
		    $fileC->set_context("path=$path");
		    $fileC->set_context("available=1");
		    $n += $fileC->update_location("available",0);
		}
	    }
	}
	$start += ($batchsize - $n) if ($n <= $batchsize);


    } elsif ($mode == 6) {
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	# Marking the file as unavailable
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("filename",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 7){
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	# Marking the file as unavailable
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("path",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 8){
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("tctwid",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 9){
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap($keyw,$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);
    }


}




sub Usage
{
    print qq~
 Usage: fC_cleanup [option]  [-cond field=value{,filed=value}]

 The condition list may be listed using the get_file_list.pl script.

 where option is one of

 General modes of operation (status check)
 ------------------------------------------
 -status                 show availability status for each file

 -check                  check files with availability > 0, set to 0 if not found
 -ucheck                 check files with availability =0, set to 1 if found
 -recheck                recheck all files (any availability) and adjust as necessary

 -mark {on|off|i}        mark selected files availability (1, 0 or the specified value i)

 Unless specified, the context storage is set to NFS by default for check operations.
 HPSS checks is NOT implemented.
 marking operations are not auto-restricted to a storage context and you may want to
 specify a condition.


 Potentially dammaging mode of operation
 ---------------------------------------
 -delete/-{c|d}delete    delete records with availability=0 (current context applies)
                         cdelete only checks it but do not do anything
                         ddelete uses the delayed mechanism of the module


                         WARNING!!! The delete operation is irreversible!
                         -alla is a switch you may use to delete availability < 0
                               The default is to only delete the 0 ones.

 Unless specified, the context storage is set to NFS by default for delete operations.
 The -doit switch MUST now be specified for ALL delete operations.
 For the 2 above switches, -doit switch MUST be specified (debug mode otherwise)

 -alter keyword=value    alter keyword value for entry(ies) ** DANGEROUS **
                         This works on dictionaries or tables
 -modif keyword=value    alter FileData/FileLocation association for entry(ies)


 Integrety check operations
 --------------------------
 The -doit switch MUST be specified for the above
 -floc                   check the FileLocations for orphan records
 -fdata                  check the FileData for orphan records
 -trgc                   check the TriggerCompositions table
 -boots X                bootstrap keyword X


 Other options
 -------------
 -debug                  turn ddb module debugging information ON (default=OFF)
 -nodebug                turn this script debugging information OFF (default=ON)
 -u user                 use 'user' ddb access privs
 -p passwd               use 'password' for ddb access

~;

}

