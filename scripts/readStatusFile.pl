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
my $prodtg;
my $dqfile = 0;
my $jbstat;
my $dqsize = 0;
my $nfspath = "/star/data10/daq/2012/";
my $daqname;
my $fulldname;
my $inpsize = 0;


# print "Job status path name  ", $jobStatPath, "\n";

 chdir $statusPath;

 @statusfile = `ls *`;

 &StDbConnect();

 foreach my $sline (@statusfile) {
     chop $sline ;
  print $sline, "\n" ;
     $outfile = $jobStatPath."/".$sline ;
     @wrd = ();
     @wrd = split ("-", $sline);
     $prodtg = $wrd[0];
     $dqfile = $wrd[1].".daq";
     $jbstat = $wrd[2];

  print "From the status file name  ",$prodtg ,"  %  ",$dqfile ,"  %  ", $jbstat, "\n"; 

  if ($jbstat eq "daq_transferred" ) {

 open (STATFILE, $outfile ) or die "cannot open $outfile: $!\n";

 @statfile = <STATFILE>;

 close (STATFILE);

 foreach my $line (@statfile) {
    chop $line;
    @prt = ();
    @prt = split ("%", $line);
    $dqsize = $prt[3];     
  print "Input for  ", $sline," % ",$line," % ",$dqsize, "\n" ;
 }

  $sql= "update $JobStatusT set jobProgress = '$jbstat', daqSizeOnSite = '$dqsize' where prodTag = '$prodtg' and inputfileName = '$dqfile' and jobProgress = 'none' ";

 $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

##########

 $sql="SELECT inputFileName, inputFileSize  FROM $JobStatusT where prodTag = '$prodtg' and inputfileName = '$dqfile' and jobProgress = 'daq_transferred' ";

    $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];

      print "$fname = $fvalue\n" if $debugOn;

      $daqname = $fvalue    if( $fname eq 'inputFileName');
      $inpsize = $fvalue    if( $fname eq 'inputFileSize');

         }
     }

     $fulldname = $nfspath.$daqname;
     if($inpsize == $dqsize) {

     `rm $fulldname`;

     }else {
 
  $sql= "update $JobStatusT set jobProgress = 'none', jobState = 'none', daqSizeOnSite = 0  where prodTag = '$prodtg' and inputfileName = '$dqfile' ";

  $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;
   }

############


  }elsif($jbstat eq "reco_finish") {

 $sql= "update $JobStatusT set jobProgress = '$jbstat' where prodTag = '$prodtg' and inputfileName = '$dqfile' and jobProgress = 'daq_transferred' ";

 $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

############

 }elsif($jbstat eq "mudst_transferred") {

 $sql= "update $JobStatusT set jobProgress = '$jbstat' where prodTag = '$prodtg' and inputfileName = '$dqfile' and jobProgress = 'reco_finish' ";

 }else{
     next;
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
