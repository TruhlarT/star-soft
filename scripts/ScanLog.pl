#!/opt/star/bin/perl -w
#dbitest.pl

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
# productioTage -> default P01he
# Flag is specified empty the database first (maintainance
# only).
#
#

use strict;
use DBI;
use File::stat;

my $logname;
my $fullname;
my $fsize;
my $modtime;
my $mtime;
my $ctime;
my $job_name;
my $id;
my $ProdTag = $ARGV[0] || "P01he";
print "ProdTag : $ProdTag\n";
my $Trigger;
my $err_file;
my $Status;
my @log_errs1;
my @log_errs2;
my @job_errs;
my $logerr;
my $err;
my $min_size = 1200;
my $min_time = 3600;

my $i = 0;
my $m_time;
my $c_time;

#dirs
my $log_dir = "/star/rcf/prodlog/$ProdTag/log/daq/";
#my $log_dir = "/star/u/nikita/daq/"; #test dir
my $job_dir = "/star/u/starreco/$ProdTag/requests/daq/jobfiles/";
my $arch_dir = "/star/u/starreco/$ProdTag/requests/daq/archive/";

my $datasourse = "DBI:mysql:operation:duvall.star.bnl.gov";
my $username = "starreco";

my $dbh1 = DBI->connect($datasourse,$username) 
    or die "Can't connect to $datasourse: $DBI::errstr\n";

my $del;

if( defined($ARGV[2]) ){
  $dbh1->do("DELETE FROM RJobInfo");
}

my $sth1 = $dbh1->prepare("INSERT INTO RJobInfo ".
			  "(ProdTag, Trigger, LFName, ".
			  "ctime, mtime, ErrorStr) ". 
			  "VALUES (?, ?, ?, ?, ?, ?)");

my $sth3=$dbh1->prepare("SELECT id, mtime, Status FROM RJobInfo ". 
			"WHERE ProdTag = \"$ProdTag\" AND ". 
			"Trigger = ? AND ". 
			"LFName = ?");
if( ! $sth3 || ! $sth1){
  die "Problem !! Cannot prepare statement\n";
}

# suck it all in array
my(%JNAMES);
opendir(ARCH,"$arch_dir") || die "Could not open archive directory\n";
while( defined($job_name = readdir(ARCH)) ){
  if($job_name !~ /st_/){ next;}
  $job_name =~ m/(.*)(st_.*)/;
  $JNAMES{$2} = $job_name;
}
closedir(ARCH);


opendir(LOGDIR,$log_dir) || die "can't open $log_dir\n: $!";
while (defined($logname = readdir(LOGDIR))) {      
  if ($logname =~/\.log/) {
    $fullname = $log_dir . $logname; 
    $err_file = $fullname;
    $err_file =~ s/\.log/\.err/;                           
    &define_time($fullname);

    if ($modtime > $min_time) {
      if( -e "$log_dir/$logname.done"){
	next;
      } else {
	if( open(FO,">$log_dir/$logname.done") ){
	  print FO "$0 (Nikita Man) ".localtime()."\n";
	  close(FO);
	  chmod(0775,"$log_dir/$logname.done");
	}
      }
    
      $fsize = stat($fullname)->size;  
      $logname =~ s/\.log//;       

      # search for a file with similar name
      #$job_name = glob("$arch_dir*$logname");
      #if( ! defined($job_name) ){ next;}
      if( ! defined($job_name = $JNAMES{$logname}) ){ next;}

      # now, we have a job file
      $fullname = $log_dir . $logname.".log";   
      define_trigger_mtime($fullname, $job_name);


      if ($fsize <= $min_size) {   
	print 
	  "Found log type 1 : $logname\n",
	  "modtime : $modtime\n",
	  "size : $fsize\n",
	  #define ErrorStr           
	  "Error file : $err_file\n",
	  "Error string : ";

	$err="";
	@job_errs = `tail -4 $err_file`;
	for ($i=0;$i<=$#job_errs;$i++){                 	  
	  unless ($err=~/$job_errs[$i]/) {
	    $err .= "$job_errs[$i] | ";                      
	  }
	}       
	print "$err\n";

      } else {       
	print 
	  "Found log type 2 : $logname\n",
	  "modtime : $modtime\n",
	  "size : $fsize\n",
	  #define ErrorStr
	  #scan log_file for break errors    
	  "Errors in log file : \n";

	$err="";
	@log_errs2 = `tail -5000 $fullname | grep Break`;
	foreach $logerr (@log_errs2) {
	  print "$logerr\n";
	  if ($logerr=~/(\*+\s+Break\s+\*+)(.*)/) {
	    unless ($err=~/$2/) {                        
	      $err.=" $2 |"; 
	    }
	  }
	}
	undef(@log_errs2);

	#scan err_file for assertion and eof errors    
	print 
	  "Error file : $err_file\n",
	  "Error string : ";  

	@log_errs1 = `tail -5 $err_file`;
	foreach $logerr (@log_errs1) {                   
	  if ($logerr=~/Assertion.*\s+failed/) {
	    $err.= " $logerr |";
	    print "$logerr\n";     
	  }
	  if ($logerr=~/Unexpected EOF/) {  
	    $err.= "Unexpected EOF | ";
	    print " $logerr |";
	  }
	}  			   
	chop($err);


      }#else fsize/minsize compare


      if ($err) {
	$sth3->execute($Trigger, $logname);
	# or die "cannot execute sth3\n";                   
	if (($id, $mtime) = $sth3->fetchrow_array()) {
	  print "\nold mtime : $mtime\n";
	  print "\nnew mtime : $m_time\n";
	  if ($mtime != $m_time) {    
	    #update record
	    print "Updated $logname\n";                                  
	    my $sth4=$dbh1->prepare("UPDATE RJobInfo SET ".
				    "mtime = \"$m_time\", ".      
				    "ErrorStr = \"$err\", ".
				    "Status = 0 ".
				    "WHERE id = ?");
	    $sth4->execute($id);
	    $sth4->finish();
	  }
	} else {
	  #insert record
	  print "\n Inserted $logname\n";
	  $sth1->execute($ProdTag, $Trigger, $logname, $c_time, $m_time, $err);
	}
                            
      }#if $err

      print "\n==============================\n";                     

    } # modtime/min_time

  } # logname
  $sth1->finish();
} #while
closedir(LOGDIR);               


my $sth2 = $dbh1->prepare("SELECT id, ProdTag, Trigger, LFName, ctime, mtime, Status, ErrorStr FROM RJobInfo");
$sth2->execute();
while (($id, $ProdTag, $Trigger, $logname, $c_time, $m_time, $Status, $err) = $sth2->fetchrow_array()) {
    print "$id  $ProdTag  $Trigger  $logname  $Status  $m_time  $err\n";   
}
$sth2->finish();
$dbh1->disconnect();

#subs
#=======================================

sub define_time {
    my ($fname) = @_;
    my $now; 
    my $mod_time;
    $now = time;
    $mod_time = stat($fname)->mtime;
    $modtime = $now - $mod_time;
}

#=======================================

sub define_trigger_mtime {
    my ($lname,$jname) = @_;
    my $Trig;
    #define Trigger   
    $Trigger = (split(/_/, $jname))[1];   
    if ( substr($Trigger,0,1) eq "2" ){
      # Wrong field. Trigger is missing and we
      # grabbed the next item = date.
      $Trigger = "unknown";
    }     
    #define mtime,ctime
    $c_time = 1;#stat($lname)->ctime;               
    $m_time = stat($lname)->mtime;   
}
