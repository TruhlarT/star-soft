#!/opt/star/bin/perl -w
#
#  $Id:
#
#  $Log:   readStatusFile.pl - script to read status files on NFS and update production job status database
#          
#  L.Didenko
#
############################################################################################################

use DBI;
use Time::Local;
use Mysql;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

my $statusPath = $ARGV[0];
#my $jobStatPath = "/star/data08/users/didenko/gridwork/prodtest/job_status";
my $outfile;
my @statusfile = ();
my @statfile = ();
my @wrd = ();
my @prt = ();
my $JbID;
my $jobId = 0;
my $prcId = 0;
my $jbstat;
my $dqsize = 0;

# print "Job status path name  ", $jobStatPath, "\n";

 chdir $jobStatPath;

 @statusfile = `ls *`;

 &StDbConnect();

 foreach my $sline (@statusfile) {
     chop $sline ;
  print $sline, "\n" ;
     $outfile = $jobStatPath."/".$sline ;
     @wrd = ();
     @wrd = split ("-", $sline);
     $JbID = $wrd[0];
     $jbstat = $wrd[1];
     @wrd = ();
     @wrd = split ("_", $JbID);
     $jobId = $wrd[0];
     $prcId = $wrd[1];

#  print "From the status file name  ", $JbID,"  %  ",$jbstat,"  %  ",$jobId,"  %  ",$prcId, "\n"; 

  if ($jbstat eq "daq_transferred" ) {

 open (STATFILE, $outfile ) or die "cannot open $outfile: $!\n";

 @statfile = <STATFILE>;

 close (STATFILE);

 foreach my $line (@statfile) {
    chop $line;
    @prt = ();
    @prt = split ("%", $line);
    $dqsize = $prt[3];     
#  print "Input for  ", $sline," % ",$line," % ",$dqsize, "\n" ;
 }

  $sql= "update $JobStatusT set jobState = '$jbstat', daqSizeOnSite = '$dqsize' where sumsRequestID = '$jobId' and sumsJobIndex = '$prcId' ";

 $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

}else{

 $sql= "update $JobStatusT set jobState = '$jbstat' where sumsRequestID = '$jobId' and sumsJobIndex = '$prcId' ";

 $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

 }

 `rm $outfile`;

 }


 &StDbDisconnect();


exit;

######################
sub StDbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}


######################
sub StDbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}
