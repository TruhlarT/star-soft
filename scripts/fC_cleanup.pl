#!/opt/star/bin/perl -w
#
# This is a command line utility to do a maintenance and cleanup
# of te FileCatalog database
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# Modified by J.Lauret, BNL
#
# The command line parameters are: 
#   General modes of operation (status check)
#   -----------------------------------------
#   -status  : show the availability status of each file
#
#   -check   : check the availability status of each file
#              and then compare it to reality, set availability
#              to 0 if not present. 
#
#   -recheck : get the file list, and check if they really exist - 
#              if not, mark them as unavailable if yes - remark them 
#              as available
#
#   -mark    : mark given files as (un)available - no checking
#              keywords {on|off}
#
#   -debug   : turn database module debugging information ON
#   -nodebug : turn THIS SCRIPT debugging information OFF
# 
#   Potentially dammaging mode of operation
#   ---------------------------------------
#   -modif keyword=value
#              alter value of the location table.
#   -alter keyword=value    
#              alter keyword value for entry ** DANGEROUS **
#
#   All delete operations are made on availability=0 files
#
#   -delete/-cdelete/-ddelete
#              -cdelete (check deletion) only displays what it will 
#                       delete based on context.
#              -ddelete (delayed) See documentation.
#
#              WARNING!!! The delete operation is irreversible!
#
#   Integrety check operations
#   ---------------------------
#   -clean   : delete records failing the bootstrap (pertinent to above params)
#   -fdata   : check the FileData for orphan records
#   -floc    : check the FileLocations for orphan records
#   -trgc    : check the TriggerCompositions table
#   -boots X : bootstrap keyword X
#
# other options
#   -cond    : conditions to limit the records processed 
#              You REALLY shouldn't use this script on the 
#              whole database at once!
#   -u user  : use current user ddb access privs
#   -p passwd: use this password for ddb access
#

use lib "/afs/rhic/star/packages/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;
my $doit;
my $delay;

# Control variables
# The size of a batch to process at once.
my $batchsize = 1000;
my $mode;
my $cond_list;
my $state="";
my $passwd="";
my $dodel;
my $kwrd="";
my $newval=undef;
my $user="";
my $keyw;

# Load the modules
my $fileC = FileCatalog->new;


# Turn off module debugging and script debugging
$fileC->debug_off();
$debug = 1;
$dodel = 0;
$delay = 0;
$mode  = 1;  # check is the default

# Parse the cvommand line arguments.
$count = 0;
while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-status"){
	$mode = 0; 

    } elsif ($ARGV[$count] eq "-debug"){
	$fileC->debug_on(); 

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
	$doit      = 1;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-cdelete"){
	$mode      = 2; 
	$doit      = 0;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-ddelete"){
	$mode      = 2; 
	$doit      = 1;
	$delay     = 1;
	$batchsize = 250;

    } elsif ($ARGV[$count] eq "-clean"){
	$dodel = 1; 
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
    $fileC->connect("FC_admin",$passwd);
} else {
    $fileC->connect($user,$passwd);
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

    if ($mode == 0)
      # First mode of operation - just get the file list and their availability
      {
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
      }
    elsif ($mode == 1)
      # Second mode of operation - get the file list, select the available ones
      # and check if they really exist - if not, mark them as unavailable
      {
	print "Checking $start (+$batchsize) ".localtime()."\n"; 
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_context("available>0");
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
	foreach (@output)
	  { 
	    my ($path, $fname,$available,$node,$site) = split ("::");
	    if (-e $path."/".$fname)
	      {
		 if ($debug > 0)
		  { print "File  $site.$store://$node$path/$fname exists\n"; }
	      }
	    else
	    {		
		#if ($debug>0)
		#{
		print "!!! File  $site.$store://$node$path/$fname DOES NOT exist or is unavailable !\n"; 
		#}
		# Marking/re-marking the file as unavailable
		$fileC->clear_context();
		$fileC->set_context("filename=$fname");
		$fileC->set_context("path=$path");
		$fileC->set_context("available=$available");
		$fileC->set_context("storage=$store");
		$fileC->set_context("node=$node") if ($node ne "");
		$fileC->set_context("site=$site") if ($site ne "");
		$fileC->update_location("available",0);
	      }
	  }    

    } elsif ($mode == 2){
	# Delete records. Note that this function is EXTREMELY
	# dangerous now since any record can be deleted based
	# on context.
	my($rec,@items);
	print "Checking $start (+$batchsize) ".localtime()."\n"; 
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_context("available=0");
	$fileC->set_delimeter("::");
	$fileC->set_delayed() if ($delay);

	# 
	if( $doit ){
	    @items = $fileC->delete_records($doit);
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


    } elsif ( $mode == 3 ){
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	if ($debug>0){
	    if ($state eq "on"){
		print "Marking files as available\n"; 
	    } elsif ($state eq "off") {
		print "Marking files as unavailable\n"; 
	    }
	}


	# Marking the file as unavailable
	$fileC->set_context("limit=0");

	if ($state eq "on"){
	    $fileC->set_context("available=0");
	    $fileC->update_location("available",1);
	} elsif ( $state eq "off") {
	    $fileC->set_context("available=1");
	    $fileC->update_location("available",0);
	} else {
	    $fileC->set_context("available=1");	    
	    $fileC->update_location("available",$state);
	    #print "You specified an incorrect state: $state\n";
	    #print "Please use a correct state: 'on' or 'off'\n"; 
	}


    } elsif ( $mode*$mode == 16){
	if ($kwrd ne ""){
	    if( ! defined($newval) ){
		die "  You must specify a new value\n";
	    } else {
		print "Resetting keyword [$kwrd] to new value $newval\n";
	    }
	} else {
	    die "Keyword is empty \n";
	}


	# In this mode, we change the record content
	#$fileC->set_context("limit=0");
	#my (@output) = $fileC->run_query("path","filename","$kwrd");
	#my (@items);

	#foreach (@output){
	#    @items = split("::");
	#    #print "---> ".join(" ",@items)."\n";
	#    $fileC->set_context("path=$items[0]","filename=$items[1]");
	#    $fileC->set_context("$kwrd=$items[2]");
	#    $fileC->update_location($kwrd,$newval,1);
	#    #print "<-- \n";
	#}

	$fileC->set_delayed();
	if ($mode == 4){
	    $fileC->update_record($kwrd,"$newval",1);
	} else {
	    $fileC->update_location($kwrd,$newval,1);
	}
	$fileC->print_delayed();

	


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
		    $fileC->update_location("available",1);
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
		    $fileC->update_location("available",0);
		}
	    }
	}    


    }
    elsif ($mode == 6)
      # Fourth mode of operation - mark selected files as available/unavailable
      # without checking if they exist or not.
      {
	# Marking the file as unavailable
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("filename",$dodel);
	print "Returned IDs $#rows: @rows\n";
      }    
    elsif ($mode == 7)
      # Fourth mode of operation - mark selected files as available/unavailable
      # without checking if they exist or not.
      {
	# Marking the file as unavailable
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("path",$dodel);
	print "Returned IDs $#rows: @rows\n";
      }    
    elsif ($mode == 8)
    {
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("tctwid",$dodel);
	print "Returned IDs $#rows: @rows\n";
    }
    elsif ($mode == 9)
    {
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap($keyw,$dodel);
	print "Returned IDs $#rows: @rows\n";
    }
    $start += $batchsize;

}




sub Usage
{
    print qq~
 Usage: fC_cleanup [option]  [-cond field=value{,filed=value}]

 where option is one of
 -status                 show availability
 -check                  check availability/set to 0 if not found
 -recheck                check unavailable files and adjust if necessary
 -mark {on|off}          mark selected files availability

 -delete/-{c|d}delete    delete records with availability=0 (current context applies)
                         cdelete only checks it but don't do anything
                         ddelete uses the delayed mechanism of the module
 -alter keyword=value    alter keyword value for entry ** DANGEROUS **


 -clean                  delete records in found 'verify' operations
 -floc                   verify the location table sanity
 -fdata                  verify the data information
 -trgc                   verify the trigger information

 -debug                  turn ddb module debugging information ON (default=OFF)
 -nodebug                turn this script debugging information OFF (default=ON)

~;

}

