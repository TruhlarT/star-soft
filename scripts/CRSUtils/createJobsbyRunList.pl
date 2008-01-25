#! /usr/local/bin/perl -w
#
# $Id:
# 
# $Log: 
# 
# createJobsbyRunList.pl - scripts to create CRS jobs. Use 3 (4) arguments: production serie,
# filename with list of run numbers, chainName from ProdOptions table and name of daq file
# if requested.   
# For example:
#  createJobsbyRunList.pl P07ie runlist2007.list auau200.2007.prod2 st_btag
# Run on rcrsuser3
#
# Author:  L.Didenko
#
##################################################################################################

use Mysql;
use Class::Struct;
use File::Basename;
use Net::FTP;
use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;

use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

$JobStatusT = "JobStatus2007";
$ProdOptionsT = "ProdOptions";


my $debugOn=0;

my $prodPeriod = $ARGV[0];
my $fileName = $ARGV[1]; 
my $trig;
my $chName = $ARGV[2];
my $datDisk = "/star/data+12-55";             
my $ftype = "";
my $coll;
my $chainDir = "daq";

   if ( !defined $ARGV[3]) {
   $ftype = "";
   }else{
    $ftype = $ARGV[3]; 
   }


my $listName = "/star/u/starreco/".$fileName;

my @runList = ();

 open (RUNLIST, $listName ) or die "cannot open $listName: $!\n";

 @runList = <RUNLIST>;



###Set directories to be created for jobfiles

my $DISK1        = "/star/rcf/prodlog/";
my $TOPHPSS_SINK = "/home/starsink/raw/daq";
my $TOPHPSS_RECO = "/home/starreco/reco";
my $JOB_LOG =  $DISK1 . $prodPeriod . "/log/" . $chainDir ;
my $JOB_DIR;

my @jobs_set = ();

#####  connect to production DB

 &StDbProdConnect();

 my $jb_news;
 my $jb_archive;
 my $jb_jobfile;
 my $jb_hold;
 my $jb_fstat;

########  declare variables needed to fill the JobStatus table

 my $mchainOp;

 my $mflName = "n/a";
 my $mjobID = "n/a";
 my $mprodSr = "n/a";
 my $mjobFname = "n/a";
 my $mjobFdir = "n/a";
 my $msumFile = "n/a";
 my $msumDir = "n/a";
 my $mjobSt = "n/a";
 my $startId = "Job_P00h";
 my $startSer = "P00h";
 my $new_id = 0;
 my $mchain; 
 my $mlibVer; 

 $JOB_DIR =  "/home/starreco/newcrs/" . $prodPeriod ."/requests/". $chainDir; 

 &StDbProdConnect();

##### insert first line to JobStatusT table get last ID 

    $sql="insert into $JobStatusT set ";    
    $sql.="jobID='$startId',"; 
    $sql.="prodSeries='$startSer'";
     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;
    $new_id = $dbh->{'mysql_insertid'};

#############################################################################


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
my $flname;
my $jpath;
my $jfile;
my $chain;
my $num = 0;
my $nfiles = 0;
my $fileSeq;
my $field;
my $myID;


 for ($ii=0; $ii< scalar(@runList); $ii++)  {

 $nfiles = 0;
 
 chop $runList[$ii];

#  print "Run number to be processed:  ",$runList[$ii], "\n";
 
  if( $ftype eq "") {

  $fileC->set_context("runnumber=$runList[$ii]","tpc=1","filetype=online_daq","sanity=1","storage=HPSS");
   }else{
  
  $fileC->set_context("runnumber=$runList[$ii]","tpc=1","filetype=online_daq","filename~$ftype","sanity=1","storage=HPSS");
  }
  @jobs_set = $fileC->run_query("trgsetupname","path","filename","fileseq","magscale");

    $fileC->clear_context();

  
 &StDbProdConnect();

  foreach my $jobline (@jobs_set){
 
    @prt = ();
    @prt = split("::",$jobline);

    $trig = $prt[0];
    $jpath  = $prt[1];
    $flname = $prt[2];
    $fileSeq = $prt[3];
    $field = $prt[4]; 
    $jfile = $flname;
    $jfile =~ s/.daq//g;

#    print $trig,"   ",$jpath,"   ",$field,"   ",$flname,"\n";

       next if ($field eq "FieldOff");

    $num = $fileSeq/10 - int($fileSeq/10);
           $mprodSr = $prodPeriod; 
           $myID = 100000000 + $new_id;
           $mjobID = "Job". $myID . "/" . $prodPeriod ."/". $mlibVer;
           $mflName = $flname;       
           $msumFile = $jfile . ".log";
           $msumDir = $JOB_LOG;
           $mjobFdir = "new_jobs";
           $mjobSt = "n/a";
           $mchName = $chName;
           $chain = $mchain;
          @parts =  split ("/", $jpath);
    $jbset = $trig . "_" .$field . "_" .$prodPeriod . "_" . $parts[5] . "_" . $parts[6]. "_" . $parts[7];
   
          $mjobFname = $trig . "_" .$field . "_" .$prodPeriod ."_". $jfile;

    $jb_fstat = 1;
    $jb_news = $JOB_DIR . "/new_jobs/" . $mjobFname;
    $jb_archive = $JOB_DIR . "/archive/" . $mjobFname;
    $jb_jobfile = $JOB_DIR . "/jobfiles/" . $mjobFname;
    $jb_hold = $JOB_DIR . "/jobs_hold/" . $mjobFname;
     if (-f $jb_news)     {$jb_fstat = 0};
     if (-f $jb_archive)  {$jb_fstat = 0};
     if (-f $jb_jobfile)  {$jb_fstat = 0};
     if (-f $jb_hold)     {$jb_fstat = 0};

      if($jb_fstat == 1)  {
      
      if($num == 0 ) {
      $chain = $mchain .",-hitfilt";
    }
#     if($nfiles < 11 ) {
          &create_jobs($jfile, $jbset, $chain, $mlibVer, $JOB_DIR, $num, $datDisk); 

      print "JOB ID = " ,$mjobID, " % " . $mjobFname,  "\n";
      $nfiles++;
#####  fill  JobStatus table
      print "filling JobStatus table\n";
 
     &fillJSTable();   

#      } 
     }
 }
}
##### delete from $JobStatusT inserted JobID

     $sql="delete from $JobStatusT WHERE ";    
     $sql.="jobID='$startId' AND "; 
     $sql.="prodSeries='$startSer'";
      print "$sql\n" if $debugOn;
     $rv = $dbh->do($sql) || die $dbh->errstr;

#### finished with data base
    &StDbProdDisconnect();

 $fileC->destroy();

   exit;

################################################################################
  sub fillJSTable {

    $sql="insert into $JobStatusT set ";
    $sql.="jobID='$mjobID',";
    $sql.="prodSeries='$mprodSr',";
    $sql.="jobfileName='$mjobFname',";
    $sql.="jobfileDir='$mjobFdir',";
    $sql.="sumFileName='$msumFile',";
    $sql.="sumFileDir='$msumDir',";
    $sql.="jobStatus='$mjobSt',"; 
    $sql.="chainName='$chName'";

     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;
    $new_id = $dbh->{'mysql_insertid'};     
  
    }

#############################################################################
##### create jobfiles to get default set of output files

 sub create_jobs {

  my ($gfile, $Jset, $fchain, $jlibVer, $JobDir, $nseq, $dataDisk ) = @_ ;

 my $Jsetd;
 my $Jsetr;
 my $inFile;
 my $logDir;
 my @pts = ();

    @pts = split ("_",$Jset);
    $Jsetr = $pts[3] . "/" .$pts[4]. "/" .$pts[5];
    $Jsetd = $pts[0] . "/" .$pts[1] . "/" . $pts[2] . "/" .$Jsetr;     
    $inFile =  $gfile . ".daq";
    $logDir = $JOB_LOG;   

   my $exArg = "29,".$jlibVer ."," .$dataDisk . ",-1," . $fchain;
  
    my $jb_new = $JobDir . "/new_jobs/" . $pts[0] . "_" .$pts[1] . "_" . $pts[2]  . "_" . $gfile;
  
      my $hpss_raw_dir  = $TOPHPSS_SINK . "/" . $Jsetr;
      my $hpss_raw_file = $inFile;
      my $hpss_dst_dir  = $TOPHPSS_RECO . "/" . $Jsetd;
      my $hpss_dst_file0 = $gfile . ".event.root";
      my $hpss_dst_file1 = $gfile . ".hist.root";
      my $hpss_dst_file2 = $gfile . ".tags.root";
      my $hpss_dst_file3 = $gfile . ".MuDst.root";
#      my $hpss_dst_file4 = $gfile . ".runco.root";    
      my $executable     = "/afs/rhic/star/packages/scripts/bfccb";
      my $executableargs = $exArg; 
      my $log_dir       = $logDir;
      my $log_name      = $gfile . ".log";
      my $err_log       = $gfile . ".err";
      if (!open (JOB_FILE,">$jb_new")) {printf ("Unable to create job submission script %s\n",$jb_new);}
        print JOB_FILE "mergefactor=1\n";


       print JOB_FILE "#input\n";
       print JOB_FILE "      inputnumstreams=2\n";
       print JOB_FILE "      inputstreamtype[0]=HPSS\n";
       print JOB_FILE "      inputdir[0]=$hpss_raw_dir\n";
       print JOB_FILE "      inputfile[0]=$hpss_raw_file\n";
       print JOB_FILE "      inputstreamtype[1]=UNIX\n";
       print JOB_FILE "      inputdir[1]=/star/data13/reco/StarDb\n";
       print JOB_FILE "      inputfile[1]=OneSpaceCharge\n";
       print JOB_FILE "#output\n";
       print JOB_FILE "      outputnumstreams=4\n";
       print JOB_FILE "#output stream \n";
       print JOB_FILE "      outputstreamtype[0]=HPSS\n";
       print JOB_FILE "      outputdir[0]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[0]=$hpss_dst_file0\n";
       print JOB_FILE "      outputstreamtype[1]= HPSS\n";
       print JOB_FILE "      outputdir[1]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[1]=$hpss_dst_file1\n";
       print JOB_FILE "      outputstreamtype[2]=HPSS\n";
       print JOB_FILE "      outputdir[2]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[2]=$hpss_dst_file2\n";
       print JOB_FILE "      outputstreamtype[3]=HPSS\n";
       print JOB_FILE "      outputdir[3]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[3]=$hpss_dst_file3\n";
#       print JOB_FILE "      outputstreamtype[4]=HPSS\n";
#       print JOB_FILE "      outputdir[4]=$hpss_dst_dir\n";
#       print JOB_FILE "      outputfile[4]=$hpss_dst_file4\n";
       print JOB_FILE "#standard out -- Should be five outputs\n";
       print JOB_FILE "      stdoutdir=$log_dir\n";
       print JOB_FILE "      stdout=$log_name\n";
       print JOB_FILE "#standard error -- Should be four\n";
       print JOB_FILE "      stderrdir=$log_dir\n";
       print JOB_FILE "      stderr=$err_log\n";
       print JOB_FILE "      notify=starreco\@rcrsuser3.rcf.bnl.gov\n";
       print JOB_FILE "#program to run\n";
       print JOB_FILE "      executable=$executable\n";
       print JOB_FILE "      executableargs=$executableargs\n";
 
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

