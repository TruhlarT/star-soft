#!/usr/bin/env perl

#
# This is the command line utility, which allows access to the data in the
# FileCatalog database.
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
# Written by J.Lauret 2002-2004
#
# Uncodumented paramaters
#
# -debug      : maintainance option
#
#use Env (OPTSTAR);
#use lib "$OPTSTAR/lib";
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
#use lib "/star/u/jeromel/work/STAR/scripts";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my ($debug,$caching);

# The state variables
my ($all, $alls, $unique, $field_list, $class);
my ($cond_list, $start, $limit, $delim, $onefile, $outfilename);
my ($intent)="User";

# Load the modules to store the data into a new database
# Simple way to connect (possibly using XML or default values)
my $fileC = FileCatalog->new();


# Set the defaults for he state values
$all         = 0;
$alls        = 0;
$unique      = 0;
$field_list  = "";
$cond_list   = "";
$fileC->debug_off();
$debug       = 0;
$onefile     = 0;
$outfilename = "";
$class       = "";
$caching     = 0;

# Parse the cvommand line arguments.
$count = 0;

while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-all"){
	$all = 1; 
    } elsif ($ARGV[$count] eq "-alls") {
	$alls = 1;
    } elsif ($ARGV[$count] eq "-onefile"){
	$onefile = 1; 
    } elsif ($ARGV[$count] eq "-distinct"){
	$unique = 1; 
    } elsif ($ARGV[$count] eq "-cache"){
	$caching= 1;

    } elsif ($ARGV[$count] eq "-V"){
	print "This is Version ".$fileC->Version()."\n"; 
	exit;
    } elsif ($ARGV[$count] eq "-debug" ||
	     $ARGV[$count] eq "-coffee"){
	$fileC->debug_on();
    } elsif ($ARGV[$count] eq "-class"){
	# class of debugging
	$fileC->message_class($ARGV[++$count]);

    }elsif ($ARGV[$count] eq "-as")
      { $intent = $ARGV[++$count]; }


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
    # connect_as() in this case mandate that the rest of the
    # the information is defined via connection schema.
    $fileC->connect_as($intent);

    if ($outfilename ne ""){
	open (STDOUT, ">$outfilename") || die "Cannot redirect output to file $outfilename";
    }

    # Setting the context based on the switches
    foreach (split(/,/,$cond_list)){
	$fileC->set_context($_);
    }
    if ($all ==1){         $fileC->set_context("all=1");   }
    if ($alls==1){         
        # do nothing
    } else {
	# do something only if sanity was not used
	# in the condition
	if ( ! defined($fileC->get_context("sanity")) ){
	    $fileC->set_optional_context("sanity=1");
	}
    }
    if (defined $limit){   $fileC->set_context("limit=$limit"); }
    if (defined $start){   $fileC->set_context("startrecord=$start"); }
    if (defined $delim){   $fileC->set_delimeter($delim); }
    if ($unique==0){       $fileC->set_context("nounique=1");}


    if ($onefile > 0){
        # ,orda(persistent)"; <-- great idea but returns persistent
	$field_list .= ",grp(filename),orda(persistent)";
    }

    # Getting the data - DO NOT use query_cache() for all querries
    if ($caching){
	@output = $fileC->run_query_cache(split(/,/,$field_list));
    } else {
	@output = $fileC->run_query(split(/,/,$field_list));
    }

    # Printing the output
    if ($onefile == 0) {
	foreach (@output){ print "$_\n"; }

    } else {
	my (@fields);
	my ($delimeter,$line,$cline);
	my ($lastfname) = "";

	if (defined $delim){
	    $delimeter = $delim; 
	} else {
	    $delimeter = "::"; 
	}
	# not secure to do this with split() as delim can be
	# changed.
	foreach $line (@output){
	    for ( $i= length($line) ; $i > 0 ; $i--){
		if ( substr($line,$i,length($delimeter)) eq $delimeter){ last;}
	    }
	    $cline = substr($line,0,$i);

	    if ($cline ne $lastfname){     print "$cline\n"; }
	    $lastfname = $cline;
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
                                    default is available=1
 -alls                              use all entries regardless of sanity flag 
                                    default is sanity=1 unless the sanity key
                                    was used as condition
 -onefile                           returns only one location (not the default)
 -distinct                          get only one value for a key-set (not the default
                                    which is faster).
 -delim <string>                    sets the default delimeter in between keys
 -limit <number of output records>  limits the number of returned values (0 for all)
 -start <start record number>       start at the n-th record of the sample
 -o <output filename>               redirects results to an ouput file (use STDOUT)

 -V                                 print version and exits
 -as <scope>                        connects as specified, scopes={Admin|User}
 -as <site>::<scope>                connects to site as specified

 Fields appearing in -keys and/or -cond may be amongst the following
     ~;

 print join(" ",$fileC->get_keyword_list())."\n\n";

}

