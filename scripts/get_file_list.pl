#!/usr/bin/perl -w
#
# This is the command line utility, which allows access to the data in the
# FileCatalog database.
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# for the STAR Experiment.

# The command line parameters are: 
# -all        : get all the records from the database, even duplicates (default - faster)
# -distinct   : get only one location (the persistent one) for each file (opposite to -all)
# -keys       : the comma delimited list of keys to get from the database
# -cond       : comma delimited list of conditions limiting the dataset
# -onefile    : get only one location for each filename
# -delim      : change the characters separating data from different columns (defaut "::")
# -limit      : limit the number of returne records
# -start      : start with the n-th record of the sample
# -debug      : maintainance option

use lib "/afs/rhic/star/packages/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;

# The state variables
my ($all, $field_list, $cond_list, $start, $limit, $delim, $onefile, $outfilename, $OUTHANDLE);

# Load the modules to store the data into a new database
my $fileC = FileCatalog->new;
$fileC->connect;

# Set the defaults for he state values
$all = 1;
$field_list = "";
$cond_list = "";
$fileC->debug_off();
$debug = 0;
$onefile = 0;
$outfilename = "";
$OUTHANDLE = 200;

# Parse the cvommand line arguments.
$count = 0;
#foreach (@ARGV)
#  {
#    print "Argument $count: $_\n";
#    $count++;
#    
#  }
while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-all")
      {	$all = 1; }
    elsif ($ARGV[$count] eq "-distinct")
      { $all = 0; }
    elsif ($ARGV[$count] eq "-onefile")
      { $onefile = 1; }
    elsif ($ARGV[$count] eq "-debug"){
	$fileC->debug_on();
    }
    elsif ($ARGV[$count] eq "-start")
      { $start = $ARGV[++$count]; }
    elsif ($ARGV[$count] eq "-limit")
      { $limit = $ARGV[++$count]; }
    elsif ($ARGV[$count] eq "-delim")
      {	$delim = $ARGV[++$count]; }
    elsif ($ARGV[$count] eq "-keys")
      {
	$field_list = $ARGV[++$count];
	if ($debug > 0) { print "The field list is $field_list\n"; }
      }
    elsif ($ARGV[$count] eq "-cond")
      {
	$cond_list = $ARGV[++$count];
	if ($debug > 0) { print "The conditions list is $cond_list\n"; }
      }
    elsif ($ARGV[$count] eq "-o")
    {
	$outfilename = $ARGV[++$count];
    }
    else
    {

	print "Unknown switch used: ".$ARGV[$count]."\n";
	&Usage();
	exit;
    }
    $count++;
}

if ($count == 0){
    &Usage();
} else {
    if ($outfilename ne ""){
	open (STDOUT, '>', $outfilename) || die "Cannot redirect output to file $outfilename";
    }

    # Setting the context based on the swiches
    foreach (split(/,/,$cond_list)){
	$fileC->set_context($_);
    }
    if ($all==1)
      { $fileC->set_context("nounique=1"); }
    if (defined $limit)
      { $fileC->set_context("limit=$limit"); }
    if (defined $start)
      { $fileC->set_context("start=$start"); }
    if (defined $delim)
      {	$fileC->set_delimeter($delim); }
    if ($onefile > 0)
      {	$field_list .= ",grp(filename),orda(persistent)"; }

    # Getting the data
    @output = $fileC->run_query(split(/,/,$field_list));

    # Printing the output
    if ($onefile != 1)
      {
	foreach (@output)
	  { print "$_\n"; }
    }
    else
    {	
	my $lastfname = "";
	my $delimeter;

	if (defined $delim)
	  { $delimeter = $delim; }
	else
	  { $delimeter = "::"; }
	foreach (@output)
	  { 
	    my @fields;
	    (@fields) = split($delimeter,$_);
	    $fields[$#fields] = "";
	    if (join($delimeter,(@fields)) ne $lastfname)
	      { print "$_\n"; }
	    $lastfname = join($delimeter,(@fields));
	  }

    }
}


sub Usage
{
    print "Command usage:\n";
    print "% get_file_list.pl [-all] [-distinct] -keys field{,field} [-cond field=value{,field=value}] [-start <start record number>] [-limit <number of output records>] [-delim <string>] [-onefile] [-o <output filename>]\n";
    print "The valid keywords are: ".join(" ",$fileC->get_keyword_list())."\n";
}

