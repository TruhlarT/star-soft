#!/usr/bin/env perl 
#
# This is the command line utility, which allows access to the data in the
# FileCatalog database.
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# Written J.Lauret 2002, 2003
#
# Uncodumented paramaters
#
# -debug      : maintainance option
#

use lib "/afs/rhic/star/packages/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;

# The state variables
my ($all, $unique, $field_list, $cond_list, $start, $limit, $delim, $onefile, $outfilename);

# Load the modules to store the data into a new database
my $fileC = FileCatalog->new;
$fileC->connect_as("User");

# Set the defaults for he state values
$all         = 0;
$unique      = 0;
$field_list  = "";
$cond_list   = "";
$fileC->debug_off();
$debug       = 0;
$onefile     = 0;
$outfilename = "";

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
    elsif ($ARGV[$count] eq "-onefile")
      { $onefile = 1; }
    elsif ($ARGV[$count] eq "-distinct")
      { $unique = 1; }
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
	open (STDOUT, ">$outfilename") || die "Cannot redirect output to file $outfilename";
    }

    # Setting the context based on the switches
    foreach (split(/,/,$cond_list)){
	$fileC->set_context($_);
    }
    if ($all==1){          $fileC->set_context("all=1");   }
    if (defined $limit){   $fileC->set_context("limit=$limit"); }
    if (defined $start){   $fileC->set_context("startrecord=$start"); }
    if (defined $delim){   $fileC->set_delimeter($delim); }
    if ($unique==0){       $fileC->set_context("nounique=1");}


    if ($onefile > 0){
        # ,orda(persistent)"; <-- great idea but returns persistent
	$field_list .= ",grp(filename),orda(persistent)";
    }

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
    print qq~
Command usage:
 % get_file_list.pl [qualifiers] -keys field{,field} [-cond field=value{,field=value}]

 where the qualifiers may be
 -all                               use all entries regardless of availability flag
 -onefile                           returns only one location (not the default)
 -distinct                          get only one value for a key-set (not the default
                                    which is faster).
 -delim <string>                    sets the default delimeter in between keys
 -limit <number of output records>  limits the number of returned values (0 for all)
 -start <start record number>       start at the n-th record of the sample
 -o <output filename>               redirects results to an ouput file (use STDOUT)

 Fields appearing in -keys and/or -cond may be amongst the following
     ~;

 print join(" ",$fileC->get_keyword_list())."\n\n";

}

