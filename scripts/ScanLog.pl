#!/opt/star/bin/perl -w
#ScanLog2.pl

#
# Version2
#
# This script was written by Nikita Soldatov, July 2001.
# Its purpose is to scan a log directory, scan for errors
# and fill a database (operation -> RJobInfo) with all the
# required information. This information is viewable via
# a cgi also developped by your kind servant, Nikita ... :)
#
# Unique argument is a production tage. This script is
# suitable for a crontab job.
#
# Usage :
#   % 'ThisScriptName' [productionTag] [Flag]
#
# ProductionTage -> default P01he
# Flag is specified empty the database first (maintainance
# only).
#
# Added zcat support. Need tuning (twice a zcat | tail is
# inefficient).
#
#

use strict;
use DBI;
#use File::stat;


my $ProdTag = $ARGV[0] || "P01he";

my $min_size = 1200;
my $min_time = 60;
my $max_time = 3600;

#dirs
my $log_dir = "/star/rcf/prodlog/$ProdTag/log/daq/";
#my $log_dir = "/star/u/nikita/daq/"; #test dir
my $job_dir = "/star/u/starreco/$ProdTag/requests/daq/jobfiles/";
my $arch_dir = "/star/u/starreco/$ProdTag/requests/daq/archive/";

my $datasourse = "DBI:mysql:operation:duvall.star.bnl.gov";
my $username = "starreco";



my $logname;
my $fullname;
my $fsize;
my $deltatime;
my $mtime;
my $ctime;
my $job_name;
my $id;
my $Trigger;
my $err_file;
my $Status;
my @log_errs1;
my @log_errs2;
my @job_errs;
my $logerr;
my $err;
my $cmprss;

my $i = 0;
my $m_time;
my $c_time=1;
my $pmtime;

my @fc;

my $dbh1 = DBI->connect($datasourse,$username)
    or die "Can't connect to $datasourse: $DBI::errstr\n";

my $del;

if( defined($ARGV[1]) ){
    # An option ?
    $dbh1->do("DELETE FROM RJobInfo") if ($ARGV[1] eq "delete");
}

my $sth1 = $dbh1->prepare("INSERT INTO RJobInfo ".
			  "(ProdTag, Trigger, LFName, ".
			  "ctime, mtime, ErrorStr) ".
			  "VALUES (?, ?, ?, ?, ?, ?)");

my $sth3=$dbh1->prepare("SELECT id, mtime FROM RJobInfo ".
			"WHERE ProdTag = \"$ProdTag\" AND ".
			"Trigger = ? AND ".
			"LFName = ?");

my $sth4 = $dbh1->prepare("UPDATE RJobInfo SET ".
			  "mtime=?, ".
			  "ErrorStr=?, ".
			  "Status = 0 ".
			  "WHERE id=?");

my $DEBUG=0;


if( ! $sth3 || ! $sth1){
   die "Problem !! Cannot prepare statement\n";
}

my(%JNAMES);
opendir(ARCH,"$arch_dir") || die "Could not open archive directory\n";
while ( defined($job_name = readdir(ARCH)) ){
  if($job_name !~ /st_/){ next;}
  $job_name =~ m/(.*)(st_.*)/;
  $JNAMES{$2} = $job_name;
}
closedir(ARCH);


opendir(LOGDIR,$log_dir) || die "can't open $log_dir\n: $!";
while ( defined($logname = readdir(LOGDIR)) ){
    if ( $logname =~ /\.log$/ || $logname =~ /\.log\.gz$/) {
        $fullname = $log_dir . $logname;
	$err_file = $fullname;
	if ($err_file =~ /\.gz/){
	    $err_file =~ s/\.gz// ;
	    $cmprss = 1;
	} else {
	    $cmprss = 0;
	}
	$err_file =~ s/\.log/\.err/;
        @fc = stat($fullname);
        $deltatime = time() - $fc[9];

	# laps time has to be at minimum min_time
	if($deltatime > $min_time ){
	    if ( -e "$log_dir/$logname.parsed"){
		# if a .parsed file exists, then skip it UNLESS
		# the log file is more recent than the .parsed file.
		$pmtime = (stat("$log_dir/$logname.parsed"))[9];
		if ( $pmtime > $fc[9] ){
		    next;
		} else {
		    unlink("$log_dir/$logname.parsed");
		}
	     } elsif ( $deltatime > $max_time ){
		 # after max_time, and only after, we create a .parsed
		 # file has a mark that we do NOT want to go through
		 # this log file again. However, the logic is such that
		 # if a run is started again, the .parsed file would be 
		 # deleted and the related log file would be treated as
		 # a new one.
		 if ( open(FO,">$log_dir$logname.parsed") ){
		     print FO "$0 (Nikita Man) ".localtime()."\n";
		     close(FO);
		     chmod(0775,"$log_dir/$logname.parsed");
		 }
	     }

	    if($cmprss){
		$logname =~ s/\.log\.gz//;
	    } else {
		$logname =~ s/\.log//;
	    }

	    # search for a file with similar name
	    if( ! defined($job_name = $JNAMES{$logname}) ){ next;}

	    # now, we have a job file
	    $fullname = $log_dir . $logname.".log".($cmprss?".gz":"");
	    define_trigger($fullname, $job_name);

	    if ( $fc[7] <= $min_size ){
		if($DEBUG){
		    print
			"Found log type 1 : $logname\n",
			"deltatime : $deltatime\n",
			"size : $fsize\n",
			# define ErrorStr
			"Error file : $err_file\n",
			"Error string : ";
		}
		$err="";
		@job_errs = `tail -4 $err_file`;
		for ( $i=0;$i<=$#job_errs;$i++ ){
		    unless ( $err=~/$job_errs[$i]/ ){
			$err .= "$job_errs[$i] | ";
		    }
		}
		if($DEBUG){
		    print "$err\n";
		} else {
		    if($err ne ""){ print "error type 1 in $logname\n";}
		}
	    } else {
		if($DEBUG){
		    print
			"Found log type 2 : $logname\n",
			"deltatime : $deltatime\n",
			"size : $fc[7]\n",
			#define ErrorStr
			#scan log_file for break errors
			"Errors in log file : \n";
		    #scan err_file for assertion and eof errors
		    print
			"Error file : $err_file\n",
			"Error string : ";
		}
		$err="";
		if($cmprss){
		    @log_errs2 = 
			`zcat $fullname | tail -5000 | grep Break`;
		} else {
		    @log_errs2 = 
			`tail -5000 $fullname | grep Break`;
		}
		foreach $logerr (@log_errs2){
		    print "$logerr\n";
		    if ( $logerr=~/(\*+\s+Break\s+\*+)(.*)/ ){
			unless ( $err=~/$2/ ){
			    $err.=" $2 |";
			}
		    }
		}
		undef(@log_errs2);

		my $tmp = "";
		if($cmprss){
		    @log_errs2 = 
			`zcat $fullname | tail -5000 | grep 'Done with Event'`;
		} else {
		    @log_errs2 = 
			`tail -5000 $fullname | grep 'Done with Event'`;
		}
		foreach $logerr (@log_errs2){
		    if($logerr =~ m/(\d+)(\/run)/){
			$tmp = $1;
		    }
		}
		if($tmp ne "" && $err ne ""){  
		    $err = "After $tmp events $err\n";
		}
		undef(@log_errs2);
		
		@log_errs1 = `tail -5 $err_file`;
		foreach $logerr (@log_errs1){
		    &define_err("Assertion.*\s+failed",$logerr);
		    &define_err("Unexpected EOF",$logerr);
		    &define_err("Fatal in <operator delete>",$logerr);
		    &define_err("Fatal in <operator new>",$logerr);
		    &define_err("error in loading shared libraries",$logerr);
		}
		chop($err);

		if($DEBUG){
		    print "$err\n";
		} else {
		    if($err ne ""){ print "error type 2 [$err] in $logname\n";}
		}
	    } #else fsize/minsize compare

	    if ( $err ){
		$sth3->execute($Trigger, $logname)
		    or die "cannot execute sth3\n";
		#print $sth3->fetchrow_array()."\n";
		if ( ($id, $mtime) = $sth3->fetchrow_array() ){
		    print "\nold mtime : $mtime\n";
		    print "\nnew mtime : $fc[9]\n";
		    if ( $mtime != $fc[9] ){
			#update record
			print "Updated $logname\n";
			$sth4->execute($fc[9],$err,$id);
		    }
		} else {
		    #insert record
		    print "\n Inserted $logname\n";
		    $sth1->execute($ProdTag, $Trigger, $logname, $c_time, $fc[9], $err);
		}
	    } #if $err
	    if ($DEBUG){ print "\n==============================\n";}
	} #if modtime/min_time
    } #if logname
} #while
closedir(LOGDIR);

# terminate statements handler
$sth1->finish();
$sth3->finish();
$sth4->finish();


# This commented block alows you to see a content of the table RJobInfo.
# If you want to see a content of the table every time you run the script
# uncomment this block.

#my $sth2 = $dbh1->prepare("SELECT id, ProdTag, Trigger, LFName, ctime, mtime, Status, ErrorStr FROM RJobInfo");
#$sth2->execute();
#while (($id, $ProdTag, $Trigger, $logname, $c_time, $m_time, $Status, $err) = $sth2->fetchrow_array()) {
#    print "$id  $ProdTag  $Trigger  $logname  $Status  $m_time  $err\n";
#}
#$sth2->finish();


$dbh1->disconnect();

#subs
#=======================================

sub define_trigger {
    my ($lname,$jname) = @_;
    my @temp;
    my $i = 0;

    # define Trigger, use a default value
    $Trigger = "unknown";
    @temp = split(/_/, $jname);

    if($#temp == -1){ return;}
    print "Looking at $jname\n";

    # We assume that the trigger name will be after the Prodtag
    # appearance in the file name.
    while( $temp[$i++] ne $ProdTag ) {
	if($i == $#temp){ last;}
    }

    if ( substr($temp[$i],0,1) eq "2" || $i == ($#temp-1)){
	# Wrong field. Trigger is missing and we
	# grabbed the next item = date.
	return;
    } else {
	$Trigger = $temp[$i];
    }
}

#=======================================

sub define_err 
{
    my ($errname,$logerr) = @_;
    if( $logerr =~ m/$errname/ ){
	chomp($errname);
	$err .= " $errname |";
	print "$err";
    }
}
