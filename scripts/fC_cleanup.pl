#!/usr/bin/perl -w
#
# This is a command line utility to do a maintenance and cleanup
# of te FileCatalog database
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# for the STAR Experiment.

# The command line parameters are: 
#   The modes of operation:
#
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
#   -delete  : if the file is marked unavailable, recheck it
#              and if still not there - delete from database
#              WARNING!!! The delete operation is irreversible!
#
#   -mark    : mark given files as (un)available - no checking
#              keywords {on|off}
#
#   -fdata   : check the FileData for orphan records
#   -floc    : check the FileLocations for orphan records
#
# other options
#   -cond    : conditions to limit the records processed 
#              You REALLY shouldn't use this script on the 
#              whole database at once!

use lib "/afs/rhic/star/packages/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;

# Control variables
# The size of a batch to process at once.
my $batchsize = 1000;
my $mode;
my $cond_list;
my $state="";
my $passwd;
my $dodel;
my $kwrd="";
my $newval=undef;

# Load the modules
my $fileC = FileCatalog->new;

print "Password : ";
chomp($passwd = <STDIN>);
$fileC->connect("FC_admin",$passwd);


# Turn off module debugging and script debugging
$fileC->debug_off();
$debug=1;

$dodel = 0;

# Parse the cvommand line arguments.
$count = 0;
while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-status"){
	$mode = 0; 

    } elsif ($ARGV[$count] eq "-debug"){
	$fileC->debug_on(); 

    } elsif ($ARGV[$count] eq "-check"){
	$mode = 1; 

    } elsif ($ARGV[$count] eq "-delete"){
	$mode = 2; 
    } elsif ($ARGV[$count] eq "-clean"){
	$dodel = 1; 
    } elsif ($ARGV[$count] eq "-mark"){
	$mode = 3; 
	$state = $ARGV[++$count];

    } elsif ($ARGV[$count] eq "-alter"){
	$mode = 4;
	($kwrd,$newval) = split("=",$ARGV[++$count]);

    } elsif ($ARGV[$count] eq "-recheck"){
	$mode = 5; 
    } elsif ($ARGV[$count] eq "-fdata"){
	$mode = 6;
    } elsif ($ARGV[$count] eq "-floc"){
	$mode = 7;
    } elsif ($ARGV[$count] eq "-cond"){
	$cond_list = $ARGV[++$count];
	if ($debug > 0) { print "The conditions list is $cond_list\n"; }

    } else {
	print "Wrong keyword used: ".$ARGV[$count]."\n";
	print "Usage: fC_cleanup [-status|-check|-delete|-mark [on|off]|-alter keyword=value|-recheck] [-cond field=value{,filed=value}]\n";
	exit;
    }
    $count++;
  }

if ($count == 0)
  {
    print "Usage: fC_cleanup [-status|-check|-delete|-mark|-recheck] [-cond field=value{,filed=value}]\n";
    exit;
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
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_context("available>0");
	$fileC->set_delimeter("::");
	
	# Getting the data
	@output = $fileC->run_query("path","filename");
	
	# Check if there are any records left
	print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	foreach (@output)
	  { 
	    my ($path, $fname) = split ("::");
	    if (-e $path."/".$fname)
	      {
		if ($debug > 0)
		  { print "File $_ exists\n"; }
	      }
	    else
	      {		
		if ($debug>0)
		  { print "!!! File $_ DOES NOT exist or is unavailable!!!\n"; }
		# Marking the file as unavailable
		$fileC->clear_context();
		$fileC->set_context("filename=$fname");
		$fileC->set_context("path=$path");
		$fileC->set_context("available=1");
		$fileC->update_location("available",0);
	      }
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
	    print "You specified an incorrect state: $state\n";
	    print "Please use a correct state: 'on' or 'off'\n"; 
	}


    } elsif ($mode == 4){
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
	$fileC->set_context("limit=0");
	my (@output) = $fileC->run_query("path","filename","$kwrd");
	my (@items);

	$fileC->set_delayed();
	foreach (@output){
	    @items = split("::");
	    #print "---> ".join(" ",@items)."\n";
	    $fileC->set_context("path=$items[0]","filename=$items[1]");
	    $fileC->set_context("$kwrd=$items[2]");
	    $fileC->update_location($kwrd,$newval,1);
	    #print "<-- \n";
	}
	$fileC->print_delayed();


    } elsif ($mode == 5)
	# Fifth mode of operation - get the file list, 
	# and check if they really exist - if not, mark them as unavailable
	# if yes - remark them as available
    {
	$fileC->set_context("limit=$batchsize");
	$fileC->set_context("startrecord=$start");
	$fileC->set_context("all=1");
	$fileC->set_delimeter("::");
	
	# Getting the data
	@output = $fileC->run_query("path","filename","available");
	
	# Check if there are any records left
	print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	foreach (@output)
	  { 
	    my ($path, $fname, $av) = split ("::");
	    if (-e $path."/".$fname)
	      {
		if ($av == 0)
		  {
		    if ($debug > 0)
		      { print "File $_ exists\n"; }
		    # Marking the file as unavailable
		    $fileC->clear_context();
		    $fileC->set_context("filename=$fname");
		    $fileC->set_context("path=$path");
		    $fileC->set_context("available=0");
		    $fileC->update_location("available",1);
		  }
	      }
	    else
	      {		
		if ($av == 1)
		  {
		    if ($debug>0)
		      { print "!!! File $_ DOES NOT exist or is unavailable!!!\n"; }
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
	@rows = $fileC->bootstrap_data("filename",$dodel);
	print "Returned IDs: @rows\n";
      }    
    elsif ($mode == 7)
      # Fourth mode of operation - mark selected files as available/unavailable
      # without checking if they exist or not.
      {
	# Marking the file as unavailable
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap_data("path",$dodel);
	print "Returned IDs: @rows\n";
      }    
    $start += $batchsize;

  }
