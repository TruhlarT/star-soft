#!/usr/bin/perl -w
#
# This is a command line utility to do a maintenance and cleanup
# of te FileCatalog database
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# for the STAR Experiment.

# The command line parameters are: 
#   The modes of operation:
#   -status  : check the availability status of each file
#   -check   : check the availability status of each file
#              and then compare it to reality
#   -delete  : if the file is marked unavailable, recheck it
#              and if still not there - delete from database
#              WARNING!!! The delete operation is irreversible!
#   -mark    : mark given files as unavailable - no checking
#   -recheck : 
# other options
# -cond

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

# Load the modules
my $fileC = FileCatalog->new;
$fileC->connect;

# Turn off module debugging and script debugging
$fileC->debug_off();
$debug=0;

# Parse the cvommand line arguments.
$count = 0;
while (defined $ARGV[$count])
  {
    if ($ARGV[$count] eq "-status")
      {	$mode = 0; }
    elsif ($ARGV[$count] eq "-check")
      { $mode = 1; }
    elsif ($ARGV[$count] eq "-delete")
      { $mode = 2; }
    elsif ($ARGV[$count] eq "-mark")
      { $mode = 3; }
    elsif ($ARGV[$count] eq "-recheck")
      { $mode = 4; }
    elsif ($ARGV[$count] eq "-cond")
      {
	$cond_list = $ARGV[++$count];
	if ($debug > 0) { print "The conditions list is $cond_list\n"; }
      }
    else
      {
	print "Wrong keyword used: ".$ARGV[$count]."\n";
	print "Usage: fC_cleanup [-status|-check|-delete|-mark|-recheck] [-cond field=value{,filed=value}]\n";
	exit;
      }
    $count++;
  }

if ($count == 0)
  {
    print "Usage: fC_cleanup [-status|-check|-delete|-mark|-recheck] [-cond field=value{,filed=value}]\n";
    exit;
  }

# First mode of operation - just get the file list and their availability
if ($mode == 0)
  {
    # Setting the context based on the swiches
    if (defined $cond_list)
      {
	foreach (split(/,/,$cond_list))
	  {
	    $fileC->set_context($_);
	  }
      }
    $fileC->set_context("limit=$batchsize");
    $fileC->set_context("start=0");
    $fileC->set_delimeter("::");

    # Getting the data
    @output = $fileC->run_query("path","filename","available");

    # Printing the output
    foreach (@output)
      { 
	my ($path, $fname, $av) = split ("::");
	print join("/",($path, $fname))." $av\n"; 
      }
  }
