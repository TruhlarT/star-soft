#! /usr/local/bin/perl -w
#
# $Id:
# 
# $Log: 
# 
# createJobsbyRunList_split.pl - scripts to create CRS jobs spliting daq files by number of events.
# Use 4 arguments: production tag, chainName from ProdOptions table, filename with list of run numbers
# and stream name (use "all" if all stream data should be processed)   
# For example:
# createJobsbyRunList_split.pl P16ie aauau200.run2016.prod auau19_goodruns.list st_physics
# 
#
# Author:  L.Didenko
#
##################################################################################################

use File::Basename;
use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;

use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

$JobStatusT = "splitJobs2016";
$DAQInfoT = "splitDaqInfo2016";

$ProdOptionsT = "ProdOptions";



my $prodPeriod = $ARGV[0]; 
my $chName = $ARGV[1];
my $fileName = $ARGV[2]; 
my $ftype = $ARGV[3];

my $datDisk = "/star/data17";             
my $trig;

my $listName = "/star/u/starreco/".$fileName;

my @runList = ();

 open (RUNLIST, $listName ) or die "cannot open $listName: $!\n";

 @runList = <RUNLIST>;

###Set directories to be created for jobfiles

my $DISK1        = "/star/rcf/prodlog/";
my $TOPHPSS_SINK = "/home/starsink/raw/daq";
my $TOPNFS_RECO = "/star/data17/reco";
my $JOB_LOG =  $DISK1 . $prodPeriod . "/log/daq" ;
my $JOB_DIR =  "/star/u/starreco/" . $prodPeriod ."/requests/daq"; 

my @jobs_set = ();

 my $jb_news;
 my $jb_archive;
 my $jb_jobfile;
 my $jb_fstat;
 my $jb_joblost;
 my $jb_jobrerun;

########  declare variables needed to fill the JobStatus table

 my $prodSr = "n/a";
 my $jobFname = "n/a";
 my $jobFdir = "n/a";
 my $logFile = "n/a";
 my $logDir = "n/a";
 my $jobSt = "n/a";
 my $outnfs = "n/a";
 my $inhpss = "n/a";
 my $mchain; 
 my $mlibVer; 
 my $strName;


 &StDbProdConnect();

############################################################################


 $sql="SELECT libVersion, chainOpt FROM $ProdOptionsT where prodSeries = '$prodPeriod' AND chainName = '$chName'";

     $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];

      print "$fname = $fvalue\n" if $debugOn;

#      print "$fname = $fvalue\n";

         $mchain   = $fvalue    if( $fname eq 'chainOpt');          
         $mlibVer  = $fvalue    if( $fname eq 'libVersion');   
       }
   }

     &StDbProdDisconnect();


my $SITE = "BNL";

my $fileC = new FileCatalog();

$fileC->connect_as($SITE."::User","FC_user") || die "Connection failed for FC_user\n";

my $jbset;
my @prt = ();
my @prts = ();
my $flname;
my $jpath;
my $jfile;
my $nfiles = 0;
my $field;
my $mrunId;
my @flsplit = ();
my $kjob = 0;
my $Nevents = 0;
my $num = 400;
my $nstr = 0;
my $nfin = 0;
my $njobSt = "n/a";
my $mgSt = "n/a";


 &StDbProdConnect();

  $prodSr = $prodPeriod;
  $logDir = $JOB_LOG;


 for ($ii=0; $ii< scalar(@runList); $ii++)  {

 chop $runList[$ii];
 @jobs_set = ();
 $nfiles = 0; 
 $mrunId = $runList[$ii];

  print "Run number to be processed:  ",$runList[$ii], "\n";
 
  if( $ftype eq "all") {

  $fileC->set_context("runnumber=$runList[$ii]","filetype=online_daq","filename~st_physics_17124030_raw_150004","sanity=1","storage=HPSS","limit=0");

   }else{
  
  $fileC->set_context("runnumber=$runList[$ii]","filetype=online_daq","filename~$ftype","sanity=1","storage=HPSS","limit=0");
  }

  @jobs_set = $fileC->run_query("trgsetupname","path","filename","magscale","events");

    $fileC->clear_context();

  foreach my $jobline (@jobs_set){

#      print $jobline, "\n";
 
    @flsplit = ();
    @prt = ();
    @prts = ();
    @prt = split("::",$jobline);

    $trig = $prt[0];
    $jpath  = $prt[1];
    $flname = $prt[2];
    $field = $prt[3];
    $Nevents = $prt[4]; 
    $jfile = $flname;
    $jfile =~ s/.daq//g;
    @flsplit = split ("_",$jfile);   
    $strName = $flsplit[1];

    next if ($field =~ /FieldOff/);

    @prts =  split ("/", $jpath);

     $jbset = $field."_".$prodPeriod."_".$prts[5]."_".$prts[6]."_".$prts[7];
     $kjob = int($Nevents/$num) + 1;

    if($flname =~ /_adc_/ ) {
       $mrunId =  $flsplit[3];
    }else{
       $mrunId =  $flsplit[2];
    }

#    print $trig,"   ",$jpath,"   ",$field,"   ",$flname,"   ", $Nevent, "\n";

      &fillDITable();


     for ($k=1; $k <= $kjob ; $k++)  {

      $logName = $jfile."_".$k.".log";

#       print $k," %  ",$logName,"\n";

      $nstr = $num*($k -1) +1 ;
      $nfin = $num*$k;

      $jobSt = "n/a";
      $inhpss = "n/a";
      $outnfs = "n/a";

    $jobFname = $trig . "_" .$field . "_" .$prodPeriod ."_". $jfile."_".$k;

   $jb_fstat = 1;
    $jb_news = $JOB_DIR . "/new_jobs/" . $jobFname;
    $jb_archive = $JOB_DIR . "/archive/" . $jobFname;
    $jb_jobfile = $JOB_DIR . "/jobfiles/" . $jobFname;
    $jb_joblost = $JOB_DIR . "/jobs_lostfiles/" . $jobFname;
    $jb_jobrerun = $JOB_DIR . "/jobs_rerun/" . $jobFname;

     if (-f $jb_news)     {$jb_fstat = 0};
     if (-f $jb_archive)  {$jb_fstat = 0};
     if (-f $jb_jobfile)  {$jb_fstat = 0};
     if (-f $jb_joblost)  {$jb_fstat = 0};
     if (-f $jb_jobrerun) {$jb_fstat = 0};  

      if($jb_fstat == 1)  {
      
      &create_jobs($jfile, $jbset, $mchain, $mlibVer, $JOB_DIR, $k); 

      print  $jobFname,"  ", $nfiles, "\n";
      $nfiles++;
 

    &fillJSTable();   

      }
     }
  }
}

#### finished with data base
    &StDbProdDisconnect();

 $fileC->destroy();

   exit;

################################################################################
  sub fillJSTable {

    $sql="insert into $JobStatusT set ";
    $sql.="prodTag='$prodSr',";
    $sql.="trigsetName='$trig',";
    $sql.="jobfileName='$jobFname',";
    $sql.="streamName='$strName',";
    $sql.="runID='$mrunId',";
    $sql.="logfileName='$logName',";
    $sql.="logfileDir='$logDir',";
    $sql.="inputStatus='$inhpss',";
    $sql.="outputStatus='$outnfs',";
    $sql.="evtstart='$nstr',";
    $sql.="evtend='$nfin',";    
    $sql.="jobStatus='$jobSt',";
    $sql.="chainName='$chName'";
#    print "$sql\n" ;
     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;    
  
    }


################################################################################
  sub fillDITable {

    $sql="insert into $DAQInfoT set ";
    $sql.="filename='$jfile',";
    $sql.="prodTag='$prodSr',";
    $sql.="nevents='$Nevents',";
    $sql.="njobcreate='$kjob',";
    $sql.="jobStatus='$njobSt',";
    $sql.="mergeStatus='$mgSt',";
    $sql.="runID='$mrunId'";
#    print "$sql\n" ;
     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;    
  
    }


#############################################################################
##### create jobfiles to get default set of output files

 sub create_jobs {

  my ($gfile, $Jset, $fchain, $jlibVer, $JobDir, $nm ) = @_ ;

 my $Jsetd;
 my $Jsetr;
 my $inFile;
 my @pts = ();
 my $outfile = $gfile ."_".$nm.".root";

 my $nmstr = $num*($nm -1) +1 ;
 my $nmfin = $num*$nm;

    @pts = split ("_",$Jset);
    $Jsetr = $pts[2]."/".$pts[3]."/".$pts[4];
    $Jsetd = $trig."/".$pts[0]."/".$pts[1]."/".$Jsetr;     

    $inFile = $gfile . ".daq";

    my $exArg = "4,".$jlibVer.",.,".$nmstr."-".$nmfin.",@,bfc.C,".$outfile.",".$fchain;
  
    my $jb_new = $JobDir . "/jobfiles/" . $trig."_".$pts[0]."_".$pts[1]."_".$gfile."_".$nm;

      my $hpss_raw_dir  = $TOPHPSS_SINK . "/" . $Jsetr;
      my $hpss_raw_file = $inFile;
      my $nfs_dst_dir   = $TOPNFS_RECO . "/" . $Jsetd."/seq";
      my $nfs_dst_file0 = $gfile."_".$nm.".MuDst.root";
      my $nfs_dst_file1 = $gfile."_".$nm.".hist.root";
      my $nfs_dst_file2 = $gfile."_".$nm.".tags.root";
      my $nfs_dst_file3 = $gfile."_".$nm.".event.root";  
      my $executable     = "/afs/rhic.bnl.gov/star/packages/scripts/bfcca";
      my $execargs = $exArg;
         $execargs =~ s/,/ /g;
      my $log_name      = $JOB_LOG."/".$gfile."_".$nm.".log";
      my $err_name      = $JOB_LOG."/".$gfile."_".$nm.".err";

      if (!open (JOB_FILE,">$jb_new")) {printf ("Unable to create job submission script %s\n",$jb_new);}


       print JOB_FILE "                \n";
       print JOB_FILE "[output-0]\n";
       print JOB_FILE "path = $nfs_dst_dir\n";
       print JOB_FILE "type = LOCAL\n";
       print JOB_FILE "file = $nfs_dst_file0\n";
       print JOB_FILE "                \n";
       print JOB_FILE "[output-1]\n";
       print JOB_FILE "path = $nfs_dst_dir\n";
       print JOB_FILE "type = LOCAL\n";
       print JOB_FILE "file = $nfs_dst_file1\n";
       print JOB_FILE "                \n";
       print JOB_FILE "[output-2]\n";
       print JOB_FILE "path = $nfs_dst_dir\n";
       print JOB_FILE "type = LOCAL\n";
       print JOB_FILE "file = $nfs_dst_file2\n";
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
#       print JOB_FILE "queue = default\n";
       print JOB_FILE "              \n"; 
       print JOB_FILE "[input-0]\n";
       print JOB_FILE "path = $hpss_raw_dir\n";
       print JOB_FILE "type = HPSS\n";
       print JOB_FILE "file = $hpss_raw_file\n";
       print JOB_FILE "              \n"; 
 
 
     close(JOB_FILE);

 }

#==============================================================================

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

###################################################################################

