#! /usr/local/bin/perl -w
#
# $Id:
# 
# $Log: submitTrigProd.pl
# 
# 
# L.Didenko
# script to create production jobfiles for requested trigger/test production
# and submit them to the farm
# 
# 
##################################################################################################

use File::Basename;
use DBI;
use Time::Local;

my $CRSDIR  = "/home/starreco/newcrs/bin";

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $TrigRequestT = "TrigProdRequest";
my $DaqInfoT   = "DAQInfo";
my $FTrgSetT = "FOTriggerSetup";


my $prodPeriod = "DEV";
my $LibTag = "DEV";
my $datadisk = "/star/data+09-12";

###Set directories to be created for jobfiles

my $DISK1        = "/gpfs01/star/rcf/prodlog/";
my $TOPHPSS_SINK = "/home/starsink/raw/daq";
my $TOPHPSS_RECO = "/home/starreco/reco";
my $JOB_LOG =  $DISK1 . $prodPeriod . "/log/daq"; 
my $jobdir = "/star/u/starreco/" . $prodPeriod ."/requests/daq/jobfiles";
my $archdir = "/star/u/starreco/" . $prodPeriod ."/requests/daq/archive";

my $ryear = "2014";
my @runnum = ();
my @strname = ();
my @nevents = ();
my $chain = "P2014a,mtd,btof,BEmcChkStat,Corr4,OSpaceZ2,OGridLeak3D,-hitfilt";


my @trgsetup = ();
my @mField = ();
my @rscale  = ();
my @trgid = ();

my @filename = ();
my $daqname;
my $nj = 0;
my $njob = 0;
my $jobFname;
my $rday = 0;
my $rdtemp = 0;
my @runday = ();
my @jbset = ();
my @jbid = ();
my @nfiles = ();

&StDbConnect();


    $sql="SELECT runnumber, stream, Nevents  FROM $TrigRequestT where submit = 'no' and runnumber <> 0 order by runnumber ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

    while( @fields = $cursor->fetchrow() ) {

    $runnum[$nj]  = $fields[0];
    $strname[$nj] = $fields[1];
    $nevents[$nj] = $fields[2]; 
    $nj++;
       }
    $cursor->finish();


  for ( my $ik = 0; $ik < $nj; $ik++ ) {

     $sql="SELECT distinct scaleFactor, TrgSetup, id, Label  FROM  $DaqInfoT, $FTrgSetT where runNumber = '$runnum[$ik]' and $FTrgSetT.id = $DaqInfoT.TrgSetup ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

    while( @fields = $cursor->fetchrow() ) {

    $rscale[$ik] = $fields[0];
    $trgid[$ik] = $fields[1];
    $trgsetup[$ik] = $fields[3];

   if( $rscale[$ik] > 0.98) {
     $mField[$ik] = "FullField";
   }elsif ( $rscale[$ik] > 0.44 && $rscale[$ik] < 0.53 ) {
     $mField[$ik] = "HalfField";
   }elsif (abs($rscale[$ik]) < 0.1) {
     $mField[$ik] = "FieldOff";
   }elsif ( $rscale[$ik] < -0.44 && $rscale[$ik] > -0.53 ) {
     $mField[$ik] = "ReversedHalfField";
   }elsif( $rscale[$ik] < -0.98) {
     $mField[$ik] = "ReversedFullField";
   }else {
     $mField[$ik] = "Unknown";
   }
       }

    $cursor->finish(); 

 print "Check magnetic field, trigger setup name ", $runnum[$ik], "   ",$mField[$ik],"   ", $trgsetup[$ik],"   ", $trgid[$ik], "\n"; 

 }

  chdir($jobdir) || die "Could not chdir to $jobdir\n";

  for ( my $ik = 0; $ik < $nj; $ik++ ) {

    $njob = 0;

    $rday = $runnum[$ik];
    $rdtemp = substr($rday,2) + 0;
    $runday[$ik] = substr($rdtemp,0,-3) + 0;

    print "Check runnumber, day   ", $runnum[$ik],"   ",  $runday[$ik], "\n";

    $jbset[$ik] = $trgsetup[$ik]."_".$mField[$ik]."_".$prodPeriod;

    $sql="SELECT distinct file  FROM  $DaqInfoT where runNumber = '$runnum[$ik]' and file like '%$strname[$ik]%' ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

    while( @fields = $cursor->fetchrow() ) {

    $daqname = $fields[0];
    $filename[$njob] = $daqname; 
    $filename[$njob] =~ s/.daq//g;
    $jbid[$njob] = $ik;

   &create_jobs($trgsetup[$ik],$mField[$ik],$filename[$njob],$runday[$ik],$runnum[$ik],$nevents[$ik]);

#   `$CRSDIR/crs_job -insert $jobFname` ; 

    `/bin/mv $jobFname $archdir`;

    print "Check jobfileNAme  ",$jobFname, "\n";      

    $njob++;
    }
    $cursor->finish(); 

    $nfiles[$ik] = $njob;
   }

  for ( my $jk = 0; $jk < $nj; $jk++ ) {

  $sql="update $TrigRequestT  set submit = 'yes', Nfiles = '$nfiles[$jk]' where runnumber = '$runnum[$jk]' and submit = 'no' ";

  $rv = $dbh->do($sql) || die $dbh->errstr;

 }

    &StDbDisconnect();

   exit;

#############################################################################
##### create jobfiles

 sub create_jobs {

  my ($jbtrg, $jbmag, $jbfile, $rnday, $rnum, $jbevents ) = @_ ;

 my $Jsetd;
 my $Jsetr;
 my $inputfile;
 my $exArg;
 my $jobname;

 $jobFname = $jbtrg."_".$jbmag."_".$prodPeriod."_".$jbfile;
 $Jsetd = $jbtrg."/".$jbmag."/".$prodPeriod."/".$ryear."/".$rnday."/".$rnum ;  
 $Jsetr = $ryear."/".$rnday."/".$rnum ;
 $inputfile =  $jbfile . ".daq";

  if($jbevents >= 10000 ) {

  $exArg = "4,".$LibTag.",".$datadisk.",-1,".$chain;

  }else{

  $exArg = "4,".$LibTag .",".$datadisk.",".$jbevents.",".$chain;

  }

 my $jb_new = $jobdir ."/".$jobFname;

#  print $jb_new, "\n";

      my $hpss_raw_dir  = $TOPHPSS_SINK."/".$Jsetr;
      my $hpss_raw_file = $inputfile;
      my $hpss_reco_dir  = $TOPHPSS_RECO."/".$Jsetd;
      my $hpss_reco_file0 = $jbfile.".MuDst.root";
      my $hpss_reco_file1 = $jbfile.".hist.root";
      my $hpss_reco_file2 = $jbfile.".tags.root";
      my $hpss_reco_file3 = $jbfile.".event.root";
      my $executable     = "/afs/rhic.bnl.gov/star/packages/scripts/bfccb";
      my $execargs = $exArg;
         $execargs =~ s/\,/ /g;
      my $log_name      = $JOB_LOG."/".$jbfile .".log";
      my $err_name      = $JOB_LOG."/".$jbfile .".err";
      if (!open (JOB_FILE,">$jb_new")) {printf ("Unable to create job submission script %s\n",$jb_new);}


       print JOB_FILE "                \n";
       print JOB_FILE "[output-0]\n";
       print JOB_FILE "path = $hpss_reco_dir\n";
       print JOB_FILE "type = HPSS\n";
       print JOB_FILE "file = $hpss_reco_file0\n";
       print JOB_FILE "                \n";
       print JOB_FILE "[output-1]\n";
       print JOB_FILE "path = $hpss_reco_dir\n";
       print JOB_FILE "type = HPSS\n";
       print JOB_FILE "file = $hpss_reco_file1\n";
       print JOB_FILE "                \n";
       print JOB_FILE "[output-2]\n";
       print JOB_FILE "path = $hpss_reco_dir\n";
       print JOB_FILE "type = HPSS\n";
       print JOB_FILE "file = $hpss_reco_file2\n";
       print JOB_FILE "               \n";
       print JOB_FILE "[exec-0]\n";
       print JOB_FILE "args = $execargs\n";
       print JOB_FILE "gzip_output = True\n";
       print JOB_FILE "stdout = $log_name\n";
       print JOB_FILE "stderr = $err_name\n";
       print JOB_FILE "exec = $executable\n";
       print JOB_FILE "              \n";
       print JOB_FILE "[main]\n";
       print JOB_FILE "num_inputs = 1\n";
       print JOB_FILE "num_outputs = 3\n";
       print JOB_FILE "queue = high\n";
       print JOB_FILE "              \n";
       print JOB_FILE "[input-0]\n";
       print JOB_FILE "path = $hpss_raw_dir\n";
       print JOB_FILE "type = HPSS\n";
       print JOB_FILE "file = $hpss_raw_file\n";
       print JOB_FILE "              \n";

     close(JOB_FILE);

 }


######################
sub StDbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}


######################
sub StDbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}
