#!/usr/bin/env perl
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

my $outfile;
my @statusfile = ();
my @statfile = ();
my @wrd = ();
my @prt = ();
my $prodtg;
my $daqfile;
my $jbstat;
my $dqsize = 0;
my $nfspath = "/star/data10/daq/2012/";
my $daqname;
my $fulldname;
my $inpsize = 0;

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

 $sql="SELECT inputFileName, inputFileSize  FROM $JobStatusT where prodTag = '$prodtg' and inputFileName = '$daqfile' and jobProgress = 'daq_transferred' ";

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

     `rm -f $fulldname`;

     }else {
 
     $sql= "update $JobStatusT set jobProgress = 'none', jobState = 'none', daqSizeOnSite = 0  where prodTag = '$prodtg' and inputFileName = '$daqfile' ";

     $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;

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

 print "CHeck reco_finish  ",$prodtg,"  ",$daqfile,"  ",$jbstat, "\n"; 


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

 print "CHeck  mudst_transferred ",$prodtg,"  ",$daqfile,"  ",$jbstat, "\n"; 

   $sql= "update $JobStatusT set jobProgress = '$jbstat' where prodTag = '$prodtg' and inputFileName = '$daqfile' and jobProgress = 'reco_finish' ";

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
