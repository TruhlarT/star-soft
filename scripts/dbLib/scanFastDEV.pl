#!/usr/local/bin/perl -w
#
# $Id: scanFastDEV.pl
#
# $Log: L.Didenko
#
# scanFastDEV.pl - script to scan error messages in log files for Fast DEV release test. 
#
##########################################################################################################

use DBI;
use Time::Local;

my $TOPDIR = "/star/rcf/test/devfast/";
my @OUTDIR = ();
my $devflag = "complete";
my @files = ();
my $fullname;
my $output = ();
my $errMessage = "none";
my $logcount = 0;
my $email = "didenko\@bnl.gov,jeromel\@bnl.gov";
my $message = "DEV test failed";
my $subject = "DEV fast test";

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";

$JobStatusT = "fastJobsStatus";

($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday ;


my $dirtree =  $TOPDIR."*/*" ;

 @OUTDIR = `ls -d $dirtree` ;

 for ($i = 0; $i < scalar(@OUTDIR); $i++) {
 print $OUTDIR[$i], "\n"; 
 }

 foreach my $eachdir (@OUTDIR) {

  chop $eachdir;

  opendir(DIR, $eachdir) or die "can't open $eachdir\n";

     @files = readdir(DIR);

     foreach my $fname ( @files) {
      next if !$fname;
      next if $fname =~ /^\.\.?$/;
      next if $fname =~ /.root/;  
   
       if ($fname =~ /.log/)  {

      $logcount++;

#    print "File Name:",$fname, "\n";

     $fullname = $eachdir."/".$fname;

     @output = ();
     @output = `tail -1200 $fullname`;

     foreach my $line (@output) {

    if ($line =~ /Abort/)  {  
         $devflag = "failed";
         $errMessage = "Abort";
    }elsif ($line =~ /segmentation violation/) {
         $devflag = "failed"; 
         $errMessage = "Segmentation violation";  
    } elsif ($line =~ /segmentation fault/) {
         $devflag = "failed"; 
         $errMessage = "Segmentation fault";  
    } elsif ($line =~ /undefined symbol/) {
         $devflag = "failed";  
         $errMessage = "undefined symbol";
    }elsif ($line =~ /Assertion/ & $line =~ /failed/)  {
         $devflag = "failed";  
         $errMessage = "Assertion failed";
    }elsif ($line =~ /FATAL/ and $line =~ /floating point exception/) {
         $devflag = "failed"; 
         $errMessage = "FATAL, floating point exception", 
    }elsif ($line =~ /glibc detected/)  {
         $devflag = "failed"; 
         $errMessage = "glibc detected";

    }
         }
       }
     }

 }

  &StDbConnect(); 

   if($devflag eq "failed") {

   system("echo \"$message\" | mail -s \"$subject\" $email");

     $sql="update $JobStatusT set testStatus = 'failed', errorCode = '$errMessage' where date = '$todate' and testStatus = 'submitted' ";

    $rv = $dbh->do($sql) || die $dbh->errstr;
   

   }elsif($devflag eq "complete" and $logcount == 3 ) {

    $sql="update $JobStatusT set testStatus = 'OK', errorCode = 'none' where date = '$todate' and testStatus = 'submitted' ";

    $rv = $dbh->do($sql) || die $dbh->errstr;


  }

 &StDbDisconnect();

exit;

################################################################################

sub StDbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}
