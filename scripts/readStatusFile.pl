#!/usr/bin/env perl
#
#  $Id: readStatusFile.pl
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

my $outfile;
my @statusfile = ();
my @statfile = ();
my @wrd = ();
my @prt = ();
my $prodtg;
my $daqfile;
my $jbstat;
my $dqsize = 0;
my $nfspath = "/star/data16/GRID/daq/2012/";
my @daqname = ();
my $fulldname;
my @inpsize = ();
my @sitedsize = ();
my $nn = 0;

 chdir $statusPath;

 @statusfile = `ls *daq_transferred`;

 &StDbConnect();

 foreach my $sline (@statusfile) {
     chop $sline ;
     print $sline, "\n" ;
     $outfile = $statusPath."/".$sline ;
     @wrd = ();
     @wrd = split ("-", $sline);
     $prodtg = $wrd[0];
     $daqfile = $wrd[1].".daq";
     $jbstat = $wrd[2];

     @statfile = ();

 open (STATFILE, $outfile ) or die "cannot open $outfile: $!\n";

 @statfile = <STATFILE>;

 close (STATFILE);

 foreach my $line (@statfile) {
    chop $line;
    @prt = ();
    @prt = split ("% ", $line);
    $dqsize = $prt[3];  
    chop $dqsize;

 }

   $sql= "update $JobStatusT set jobProgress = '$jbstat', daqSizeOnSite = '$dqsize' where prodTag = '$prodtg' and inputFileName = '$daqfile' and jobProgress = 'none' ";

#  print "$sql\n";
 
   $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

  `rm -f $outfile`;

   }   #  $sline

##########

 $sql="SELECT inputFileName, inputFileSize, daqSizeOnSite  FROM $JobStatusT where prodTag = '$prodtg' and jobProgress = 'daq_transferred' ";

    $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

   while(@fields = $cursor->fetchrow) {

      $daqname[$nn] = $fields[0];
      $inpsize[$nn] = $fields[1];
      $sitedsize[$nn] = $fields[2];

     $nn++;
    }

  $cursor->finish();

for ( my $ii=0; $ii< $nn; $ii++) {

     $fulldname = $nfspath.$daqname[$ii];
     if($inpsize[$ii] == $sitedsize[$ii]) {

#     `rm -f $fulldname`;

     }else {
 
	 print "Check files with different sizes ",$daqname[$ii]," % ",$inpsize[$ii]," % ",$sitedsize[$ii],"\n";

     $sql= "update $JobStatusT set jobProgress = 'none', jobState = 'none'  where prodTag = '$prodtg' and inputFileName = '$daqname[$ii]' ";

     $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

   print "$sql\n";

     }
  }
 
#######################################################################################

   @statusfile = ();

   @statusfile = `ls *reco_finish`;


   foreach my $sline (@statusfile) {
     chop $sline ;
     print $sline, "\n" ;
     $outfile = $statusPath."/".$sline ;
     @wrd = ();
     @wrd = split ("-", $sline);
     $prodtg = $wrd[0];
     $daqfile = $wrd[1].".daq";
     $jbstat = $wrd[2];

   $sql= "update $JobStatusT set jobProgress = '$jbstat' where prodTag = '$prodtg' and inputFileName = '$daqfile' and jobProgress = 'daq_transferred' ";

   $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

  `rm -f $outfile`;

  }

##########################################################################################


   @statusfile = ();

   @statusfile = `ls *mudst_transferred`;


   foreach my $sline (@statusfile) {
     chop $sline ;
     print $sline, "\n" ;
     $outfile = $statusPath."/".$sline ;
     @wrd = ();
     @wrd = split ("-", $sline);
     $prodtg = $wrd[0];
     $daqfile = $wrd[1].".daq";
     $jbstat = $wrd[2];

   $sql= "update $JobStatusT set jobProgress = '$jbstat' where prodTag = '$prodtg' and inputFileName = '$daqfile' and (jobProgress = 'reco_finish' or jobProgress = 'daq_transferred') ";

   $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;


     `rm -f $outfile`;

   }
  
##########################################################################

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
