#!/usr/bin/env perl

#
# This is a command line utility to do a maintenance and cleanup
# of te FileCatalog database
#
# Written by Adam Kisiel, Warsaw University of Technology (2002)
#
# Modified by J.Lauret, BNL 2002-2009
#

use Env qw(STAR_SCRIPTS);
use lib "$STAR_SCRIPTS";
# use lib "/star/u/jeromel/work/ddb";
use strict;
use FileCatalog;

my @output;
my $i;
my $count;
my $debug;
my $delay;

# Control variables
# The size of a batch to process at once.
my $batchsize =  1000;
my $MARKSIZE  =  5000;
my $mode;
my $cond_list;
my $state="";
my $kwrd="";
my $newval=undef;
my $keyw;
my $n;
my $confirm;
my $allst;
my $class;
my $instance="";
my $limit;

# Connection parameters
my $user=undef;
my $passwd=undef;
my $host=undef;
my $port=undef;
my $db=undef;

# global array
my @MARK;
my $ligne;

# Load the modules
my $fileC = FileCatalog->new();


# Turn off module debugging and script debugging
$fileC->debug_off();
$debug    = 1;
$delay    = 0;
$mode     = 1;  # check is the default
$confirm  = 0;
$allst    = 0;
$limit    = 1;

# Parse the command line arguments.
$count = 0;
while (defined $ARGV[$count]){
    if ($ARGV[$count] eq "-status"){
	$mode = 0;

    } elsif ($ARGV[$count] eq "-debug"){
	$fileC->debug_on();
    } elsif ($ARGV[$count] eq "-class"){
	# class of debugging
	$fileC->message_class($ARGV[++$count]);

    } elsif ($ARGV[$count] eq "-ucheck"){
	$mode = -1;
    } elsif ($ARGV[$count] eq "-check"){
	$mode = 1;

    } elsif ($ARGV[$count] eq "-nodebug"){
	$debug = 0;

    } elsif ($ARGV[$count] eq "-nl"){
	$limit = 0;

    } elsif ($ARGV[$count] eq "-i"){
	$instance  = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-u"){
	$user      = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-p"){
	$passwd    = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-h"){
	$host      = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-P"){
	$port      = $ARGV[++$count];
    } elsif ($ARGV[$count] eq "-db"){
	$port      = $ARGV[++$count];

    } elsif ($ARGV[$count] eq "-delete"){
	$mode      = 2;
	$batchsize = 250;
    } elsif ($ARGV[$count] eq "-cdelete"){
	print "-cdelete currently has the same meaning than -delete\n";
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

    } elsif ($ARGV[$count] eq "-allst"){
	$allst = 1;

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
	if ($debug > 0) { &Print("The conditions list is $cond_list"); }


    } else {
	print "Wrong keyword used: ".$ARGV[$count]."\n";
	&Usage(1);
    }
    $count++;
}

if ($count == 0){  &Usage(1);}


#
# Handle instance for multi-process cohesion
#
if ( $instance ne ""){
    $instance = "/tmp/.fC_cleanup_$instance";
    if ( -e $instance ){
	my(@items)=stat($instance);
	if ( (time() - $items[9]) > 3600 ){
	    # No activity on lock file for an hour?
	    &Print("No activity detected on $instance, deleting");
	    unlink($instance);
	} else {
	    &Print("$instance exists, $$ exiting");
	    exit;
	}
    } 
}




my $morerecords = 1;
my $start = 0;
while ($morerecords)
{
    #
    # Allow for one shot disable
    #
    my($test) = $ENV{HOME}."/fC_cleanup.quit";
    if ( -e $test ){
	# &Print("Found $test - quitting");
	&Die("Found $test - quitting");
    }
    
    &Print("--- ($$)") if ($start == 0 && abs($mode) < 5);
    $morerecords = 0;

    if ($mode == 0){
	# First mode of operation - just get the file list and their availability
	&MyConnect($fileC,"User")  if ($start == 0);
	&ResetContext($fileC);
	
	&Print("Checking mode=0 so-far=$start (getting +$batchsize records) ".localtime());
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
	    &Print(join("/",($path, $fname))." $av");
	}
	$start += $batchsize;



    } elsif ($mode*$mode == 1){
	# Second mode of operation - get the file list,
	# select the available ones and check if they
	# really exist - if not, mark them as unavailable later
	$n = 0;
	if ($start == 0){
	    &MyConnect($fileC,"User");
	} else {
	    if ($#MARK > $MARKSIZE ){
		$n += &DoMark($fileC,"User");
	    }
	}
	&ResetContext($fileC);
	
	&Print("Checking mode=$mode so-far=$start (+getting $batchsize records) ".localtime());
	
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
	    $fileC->set_context("storage=$store");
	} else {
	    if( $store eq "HPSS"){
		&Die("HPSS checking not immplemented yet");
	    }
	}

	# Getting the data
	@output = $fileC->run_query("path","filename","available","node","site");
	# @output = "/star/data34/reco/cuProductionMinBias/ReversedFullField/P07ib/2005/030::st_physics_adc_6030096_raw_2080008.tags.root::1::localhost::BNL";

	# Check if there are any records left
	# print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	# $n = 0;
	foreach (@output){
	    my ($path, $fname,$available,$node,$site) = split ("::");

	    # $fileC->clear_context();
	    # $fileC->set_context("filename=$fname");
	    # $fileC->set_context("path=$path");
	    # $fileC->set_context("storage=$store");
	    # $fileC->set_context("node=$node") if ($node ne "");
	    # $fileC->set_context("site=$site") if ($site ne "");

	    if ( ($mode == 1  && $available <= 0) ||
		 ($mode == -1 && $available != 0)){
		print "BOGUS logic or corrupt records !!\n";
		next;
	    }

	    # print "$path/$fname\n";
	    if ( &Exist("$path/$fname") ){
		if ($mode == -1){
		    # remark available
		    &Print("File  $site.$store://$node$path/$fname exists $available");
		    # $fileC->update_location("available",1,$confirm);
		    push(@MARK,"1:$confirm:$fname:$path:$available:$store:$node:$site");
		    # $n++;
		} elsif ($debug > 1){
		    &Print("Found  $site.$store://$node$path/$fname and avail=$available");
		}
	    } else {
		if ($mode == 1){
		    # and ! Exist($path/$file) that is ...
		    &Print("File  $site.$store://$node$path/$fname DOES NOT exist and available=$available");
                    # mark it un-available
		    # $fileC->update_location("available",0,$confirm);
		    push(@MARK,"0:$confirm:$fname:$path:$available:$store:$node:$site");
		    # print "Pushing 0:$confirm:$fname:$path:".":$store:$node:$site $#MARK\n";
		    # print $MARK[0]."\n";
		    # $n++;
		}
	    }

	}
	# &DoMark($fileC,"User");	
	
	# We have modified records so the next ROW number
	# need to be offset by how many we just changed
	$start += ($batchsize - $n) if ($n <= $batchsize);

    } elsif ($mode == 2 || $mode*$mode == 4){
	# Delete records. Note that this function is EXTREMELY
	# dangerous now since any record can be deleted based
	# on context.
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);
	
	my($rec,@items);
	&Print("Checking mode=$mode so-far=$start (getting +$batchsize records) ".localtime());
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
	if( ! defined($store) && ! $allst){
	    # Impose NFS to minimize errors
	    $store = "NFS";
	    $fileC->set_context("storage=NFS");
	    print "NOTE :: storage=NFS is set by default. Use storage keyword to over-write\n";
	}


	if( $confirm ){
	    @items = $fileC->delete_records($confirm);
	    if( $debug ){
		foreach (@items){
		    &Print("Deleted $_");
		}
	    }

	    if ( $delay){
		# $fileC->print_delayed();
		$fileC->flush_delayed();
	    }
	} else {
	    @items = $fileC->run_query("site","node","storage","path","filename","available");
	    foreach (@items){
		&Print("$_");
	    }
	}

	if (($#items +1) == $batchsize){
	    $morerecords = 1;
	} else {
	    print "Running post-deletion bootstrap\n";
	    &FullBootstrap($confirm);
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
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);

	if ($debug>0){
	    if ($state eq "on"){
		&Print("Marking files as available");
	    } elsif ($state eq "off") {
		&Print("Marking files as unavailable");
	    } elsif ($state eq "delf") {
		&Print("Marking files as deletable (any dameon may pic those and delete)");
	    } else {
		&Print("Marking files with available = $state");
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
	} elsif ( $state eq "delf") {
	    $fileC->set_context("available=1");
	    $fileC->update_location("available",-1,$confirm);
	} else {
	    $fileC->set_context("available=1");
	    $fileC->update_location("available",$state,$confirm);
	}


    } elsif ( $mode*$mode == 16){
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);
	
	$fileC->set_context("limit=$batchsize");
	if ($kwrd ne ""){
	    if( ! defined($newval) ){
		&Die("  You must specify a new value");
	    } else {
		print "Resetting keyword [$kwrd] to new value $newval $start ".
		    localtime()."\n";
	    }
	} else {
	    &Die("Keyword is empty ");
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
	# print "$morerecords\n";

    } elsif ($mode == 5){
	# Fifth mode of operation - get the file list,
	# and check if they really exist - if not, mark them as unavailable
	# if yes - remark them as available
	$n = 0;
	if ($start == 0){	
	    &MyConnect($fileC,"User");
	} else {
	    if ($#MARK > $MARKSIZE ){
		 $n += &DoMark($fileC,"User");
	    }
	}
	&ResetContext($fileC);

	&Print("Checking mode=$mode so-far=$start (getting +$batchsize records) ".localtime());
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
		&Die("HPSS checking not implemented yet");
	    }
	}

	# Getting the data
	@output = $fileC->run_query("path","filename","available","node","site");

	# Check if there are any records left
	# print "OUTPUT: $#output batchsize $batchsize\n";
	if (($#output +1) == $batchsize)
	  { $morerecords = 1; }

	# checking the availability
	# $n = 0;
	foreach (@output){
	    my ($path, $fname, $av,$node, $site) = split ("::");
	    if ( &Exist("$path/$fname") ){
		if ($av == 0){
		    # if ($debug > 0)
		    # {
		    &Print("File $site.$store://$node$path/$fname exists");
		    # }
		    # Marking the file as available
		    # $fileC->clear_context();
		    # $fileC->set_context("filename=$fname");
		    # $fileC->set_context("path=$path");
		    # $fileC->set_context("available=0");
		    # $fileC->set_context("storage=$store");
		    # $fileC->set_context("node=$node") if ($node ne "");
		    # $fileC->set_context("site=$site") if ($site ne "");
		    # $n += $fileC->update_location("available",1);
		    push(@MARK,"1:".":$fname:$path:0:$store:$node:$site")		    
		}
	    } else {
		if ($av == 1){
		    # if ($debug>0)
		    # {
		    &Print("File $site.$store://$node$path/$fname DOES NOT exist and available=1");
		    # }
		    # Marking the file as unavailable
		    # $fileC->clear_context();
		    # $fileC->set_context("filename=$fname");
		    # $fileC->set_context("path=$path");
		    # $fileC->set_context("available=1");
		    # $n += $fileC->update_location("available",0);
		    # NOTE: No store before (???)
		    push(@MARK,"0:".":$fname:$path:1:$store:$node:$site")		    		    
		}
	    }
	}
	$start += ($batchsize - $n) if ($n <= $batchsize);


    } elsif ($mode == 6) {
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	# Marking the file as unavailable
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);

	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("filename",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 7){
	# Fourth mode of operation - mark selected files as available/unavailable
	# without checking if they exist or not.
	# Marking the file as unavailable
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);
	
	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("owner",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 8){
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);

	my @rows;
	$fileC->set_context("limit=100000000");
	@rows = $fileC->bootstrap("tctwid",$confirm);
	print "Returned IDs $#rows: @rows\n";
	print "Use -doit to do a real cleaning\n" if (! $confirm);

    } elsif ($mode == 9){
	&MyConnect($fileC,"Admin")  if ($start == 0);
	&ResetContext($fileC);

	if ( $keyw eq "all"){
	    &FullBootstrap($confirm);
	} else {
	    my @rows;
	    $fileC->set_context("limit=100000000");
	    @rows = $fileC->bootstrap($keyw,$confirm);
	    print "Returned IDs $#rows: @rows\n";
	}
	print "Use -doit to do a real cleaning\n" if (! $confirm);
    }
}

# need to work on the last batch of files not yet treated
if ($#MARK != -1){
    &DoMark($fileC,"User");
}
$fileC->destroy();

unlink($instance) if ( $instance ne "");


#
# This will destroy i.e. close the FileCatalog, re-open as admin
# and start a batch marking
#
sub DoMark
{
    my($fileC,$wasas)=@_;
    my($count)=0;
    my($ligne,$Tstart,$rate,$delta);
    
    if ($#MARK != -1){
	if ($wasas ne "Admin"){
	    # this means we need to close and re-open as admin
	    $fileC->destroy();
	    # $fileC->debug_on();
	    &MyConnect($fileC,"Admin");
	    &Die("NULL FC handler")      if (!$fileC);
	    &Print("Now marking a batch of ".($#MARK+1)." files (switching to Admin)");
	} else {
	    &Print("Now marking a batch of ".($#MARK+1)." files (was Admin, re-using db connection)");
	}
	# &ResetContext($fileC);
	
	$Tstart=time();
	# $fileC->set_delayed();
	$fileC->warn_if_duplicates(0); # wedisable because of delays between Userand Admin
	foreach $ligne (@MARK){
	    # print "Got [$ligne]\n";
	    my($avail,$confirm,$fname,$path,$av,$store,$node,$site) = split(":",$ligne);
	    # print "Retreiving $avail,$confirm,$fname,$path,$av,$store,$node,$site\n";
	    # die;
	    
	    # $fileC->debug_on();
	    $fileC->clear_context();
	    $fileC->set_context("filename=$fname");
	    $fileC->set_context("path=$path");
	    $fileC->set_context("available=$av")   if ($av   ne "");
	    $fileC->set_context("storage=$store");
	    $fileC->set_context("node=$node")      if ($node ne "");
	    $fileC->set_context("site=$site")      if ($site ne "");
	    if ($confirm eq ""){  $confirm = undef;}
	    if ( $fileC->update_location("available",$avail,$confirm) ){
		$count++;
		$delta= time()-$Tstart;
		if ($delta != 0){
		    $rate = sprintf("%.4f",60*$count/(time()-$Tstart));
		} else {
		    $rate = "unknown";
		}
		&Print("Marked $fname $path ($rate ops/mn)"); # $store $node $site
	    }
	}
	# &Print("Flushing $count delayed operations ".localtime());
	# $fileC->flush_delayed();
	# $fileC->unset_delayed();
	# $rate = sprintf("%.4f",60*$count/(time()-$Tstart));
	
	# now re-connect as a normal non-Admin
	if ($wasas ne "Admin"){
	    # re-connect as initial $wasas
	    $fileC->destroy();
	    &MyConnect($fileC,$wasas) 
	}
	$fileC->warn_if_duplicates(1);
	undef(@MARK);
    }
    return $count;
}


sub MyConnect
{
    my($fileC,$as)=@_;
    my($luser,$lpasswd,$lport,$lhost,$ldb);
    
    if ( ! defined($as) ){  $as = "User";}
    
    # Get connection fills the blanks while reading from XML
    # However, USER/PASSWORD presence are re-checked
    my ($USER,$PASSWD,$PORT,$HOST,$DB) = $fileC->get_connection($as);
    
    $luser   = defined($user)?$user:$USER;
    $lpasswd = defined($passwd)?$passwd:$PASSWD;
    $lport   = defined($port)?$port:$PORT;
    $lhost   = defined($host)?$host:$HOST;
    $ldb     = defined($db)?$db:$DB;

    if ( $luser eq "" ){
	# get it from command line
	print "Username for FileCatalog : ";
	chomp($luser = <STDIN>);
    }
    if ( $lpasswd eq "" ){
	# get it from command line
	print "Password for $user : ";
	chomp($lpasswd = <STDIN>);
    }

    # Load is managed globally - remove limit if -nl
    if ( !$limit && $as eq "Admin"){
	$fileC->set_thresholds(0,0,0);
    }
    

    #
    # Now connect
    #
    if ( ! $fileC->connect($luser,$lpasswd,$lport,$lhost,$ldb) ){
	&Print("Failed to connect to db");
	exit;
    }
}

sub ResetContext
{
    my($fileC)=@_;
    
    # Setting the context based on the swiches
    $fileC->clear_context();
    if (defined $cond_list){
	foreach (split(/,/,$cond_list)){
	    $fileC->set_context($_);
	}
    }
}


sub Die
{
    my($mess)=@_;
    unlink($instance) if ( $instance ne "");
    $fileC->destroy() if ( $fileC);
    die "$mess\n";
}
sub Exit
{
    my($val)=@_;
    unlink($instance) if ( $instance ne "");
    exit $val;
}


sub Print
{
    my(@msg)=@_;
    my($mess);
    foreach $mess (@msg){
	chomp($mess);
	print "$mess\n";
	if ( $instance ne ""){
	    open(OUT,">>$instance");
	    print OUT localtime()." $$ $mess\n";
	    close(OUT);
	}
    }
}



sub Exist
{
    my($file)=@_;
    my($realf);

    # DO support soft-links
    if ( -l $file ){
	# only files in a path containing starreco/reco will 
	# apply otherwise, we will ignore. 
	# Path like /home/starlib/home/starreco should be valid 
	# and /home/starlib/reco not ... This is a Xrootd 
	# transition hack.
	if ( $file =~ m/starlib\/reco/){ return 0;}

	# check if target exists
	$realf = readlink($file);
	if ( -e $realf ){
	    return 1;
	} else {
	    return 0;
	}
    } elsif ( -e $file ){
	return 1;
    } else {
        # and since I am paranoid
	if ( open(FT,$file) ){
	    close(FT);
	    return 1;
	} else {
	    return 0;
	}
    }
}


sub FullBootstrap
{
    my($confirm)=@_;
    my(@rows);

    $fileC->set_context("limit=100000000");
    @rows = $fileC->bootstrap("runnumber",$confirm);
    @rows = $fileC->bootstrap("collision",$confirm);
    @rows = $fileC->bootstrap("generator",$confirm);
    @rows = $fileC->bootstrap("configuration",$confirm);
    @rows = $fileC->bootstrap("path",$confirm);
    @rows = $fileC->bootstrap("node",$confirm);
}


sub Usage
{
    my($sts)=@_;

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

 -mark {on|off|delf|i}   mark selected files availability (1, 0 or the specified value i)

 Unless specified, the context storage is set to NFS by default for check operations.
 HPSS checks is NOT implemented.
 marking operations are not auto-restricted to a storage context and you may want to
 specify a condition.


 Potentially dammaging mode of operation
 ---------------------------------------
 -delete/-{c|d}delete    delete records with availability=0 (current context applies)
                         cdelete only checks it but do not do anything
                         ddelete uses the delayed mechanism of the module


 WARNING!!! The delete operation is irreversible ! Therefore, we made it perticularly
 combersome to delete records to prevent accidental delete. DO NOT use the above
 keywords unless you are sure of what will happen :

   + -doit  switch MUST now be specified for ALL delete operations.
   + -allst Unless specified, the context storage is set to NFS by default for
            delete operations. -allst is a switch you may want to use to take into
            account all storage type in one shot. The default storage=NFS is made
            to prevent accidental deletion of persistent stored files. This should
            be used with caution.

   + -alla  is a switch you may use to affect availability < 0
            The default is to only delete the 0 ones. Practically, -ucheck would
            check for files previously marked unavailable (on more check) and
            -delete -alla would delete all records marked with any availability <= 0.

 -alter keyword=value    alter keyword value for entry(ies) ** DANGEROUS **
                         This works on dictionaries or tables and may allows
                         for gobal updates. 
 -modif keyword=value    alter FileData/FileLocation association for entry(ies)
                         This switch also modify non-dictionary tables but within
                         carefull checks (one by one).

 Integrety check operations
 --------------------------
 The -doit switch MUST be specified for the above
 -floc                   check the FileLocations for orphan records (no associated Data)
 -fdata                  check the FileData for orphan records (no associated Locations)
 -trgc                   check the TriggerCompositions table
 -boots {X|all}          bootstrap keyword X, using "all" will do a
                         sequence of table cleaning (but not filename or flid)

 Authentication options
 ----------------------
 -u user                 use 'user' db access privs
 -p passwd               use 'password' for db access
 -h host                 use 'host' for db access
 -P port                 use 'port' for db accces
 -db db                  use dabatase 'db' for db access

 Other options
 -------------
 -debug                  turn database module debugging information ON (default=OFF)
 -nodebug                turn this script debugging information OFF (default=ON)
 -doit                   switch MUST be specified to really perform the operation.
                         Without it, the API will only display the operation it
                         intends to perform (i.e. debug mode). It is wise to start
                         in debug mode.
 -nl                     Bypass the load balancer - do not use this option in cron     
 -class XXX              Set debugging class
~;

    if( defined($sts) ){ exit;}

}

