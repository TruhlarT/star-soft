#! /opt/star/bin/perl -w
#
# $Id:
# 
# $Log: 
# 
# createRunJobs.pl  
# L.Didenko
# script to create jobfiles and JobID and fill in JobStatus and jobRelations tables 
# script requires 4  arguments: production Series, year of data taken, chain name from ProdOption table,
# run Number
#
# example of usage:  createJobs.pl P01hf 2001 p2001f 2229029
##################################################################################################

use Mysql;
use Class::Struct;
use File::Basename;

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCpProdSetup.pl";

my $debugOn=0;

my @SetD; 
my $nSetD = 0;
          
my $prodPeriod = $ARGV[0]; 
my $chName = $ARGV[2];
my $dyear = $ARGV[1];
my $dRun = $ARGV[3];
my $dPath = "/daq/" . $dyear ;             
my $chainDir = "daq";

###Set directories to be created for jobfiles

my $DISK1        = "/star/rcf/prodlog/";
my $TOPHPSS_SINK = "/home/starsink/raw/daq";
my $TOPHPSS_RECO = "/home/starreco/reco";
my $JOB_LOG =  $DISK1 . $prodPeriod . "/log/" . $chainDir; ;
my $JOB_DIR;

my @jobIn_set = ();
my $jobIn_no = 0;


struct JFileAttr => {
         pathN   => '$', 
         fileN   => '$',
        jobIdN   => '$',
         dtSet   => '$', 
		    };

  my $mySet;

#####  connect to production DB

 &StDbProdConnect();

my $myRun;
 
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
 my $mNev  = 0;
 my $mCPU = 0;
 my $mmemSz = 0;
 my $mNoTrk = 0;
 my $mNoVert = 0;
 my $mchName = "n/a";
 my $mnodeId = "n/a";
 my $startId = "Job_P00h";
 my $startSer = "P00h";
 my $new_id = 0;

 my $filename;


##### insert first line to JobStatusT table get last ID 

    $sql="insert into $JobStatusT set ";    
    $sql.="jobID='$startId',"; 
    $sql.="prodSeries='$startSer'";
     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;
    $new_id = $dbh->{'mysql_insertid'};

#############################################################################

 $JOB_LOG =  $DISK1 . $prodPeriod . "/log/" . $chainDir;
 $JOB_DIR =  "/star/u/starreco/" . $prodPeriod ."/requests/". $chainDir; 

 my $jobDIn_no = 0;
 my @jobDIn_set = (); 
 my $mchain; 
 my $mlibVer; 
 my $mNikName;

 $sql="SELECT prodSeries, libVersion, chainOpt, chainName  FROM $ProdOptionsT where prodSeries = '$prodPeriod' AND chainName = '$chName'";

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
         $mNikName = $fvalue    if( $fname eq 'chainName'); 
       }
   }

 $jobDIn_no = 0; 

  $sql="SELECT runID, path, fName, dataset FROM $FileCatalogT WHERE fName LIKE '%daq' AND runID = '$dRun' AND dataStatus = 'OK' AND hpss = 'Y' ";
    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
           $cursor->execute;
 
   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
        $fObjAdr = \(JFileAttr->new());
 

    for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
      print "$fname = $fvalue\n" if $debugOn;

         ($$fObjAdr)->pathN($fvalue)   if( $fname eq 'path');
         ($$fObjAdr)->fileN($fvalue)   if( $fname eq 'fName'); 
         ($$fObjAdr)->dtSet($fvalue)   if( $fname eq 'dataset'); 
      }

   $jobDIn_set[$jobDIn_no] = $fObjAdr;
   $jobDIn_no++;
    }

#####  start loop over input files
my $jbset;
my @flsplit;
my $mrunId;
my $nfiles = 0;

  foreach my $jobDnm (@jobDIn_set){
      my $jpath  = ($$jobDnm)->pathN;
      my $flname = ($$jobDnm)->fileN;
      my $dset   = ($$jobDnm)->dtSet;
      my $jfile = $flname;
       $jfile =~ s/.daq//g;
       @flsplit = split ("_",$jfile);  
       $mrunId =  $flsplit[2];

           $mprodSr = $prodPeriod; 
           $myID = 100000000 + $new_id;
           $mjobID = "Job". $myID . "/" . $prodPeriod ."/". $mlibVer;
           $mflName = $flname;
           $msumFile = $jfile . ".log";
           $msumDir = $JOB_LOG;
           $mjobFdir = "new_jobs";
           $mjobSt = "n/a";
           $mchName = $mNikName;
          @parts =  split ("/", $jpath);
    $jbset = $prodPeriod . "_" . $parts[5] . "_" . $parts[6];
          $mjobFname = $jbset ."_". $jfile;

    $jb_fstat = 1;
    $jb_news = $JOB_DIR . "/new_jobs/" . $mjobFname;
    $jb_archive = $JOB_DIR . "/archive/" . $mjobFname;
    $jb_jobfile = $JOB_DIR . "/jobfiles/" . $mjobFname;
    $jb_hold = $JOB_DIR . "/jobs_hold/" . $mjobFname;
     if (-f $jb_news)     {$jb_fstat = 0};
     if (-f $jb_archive)  {$jb_fstat = 0};
     if (-f $jb_jobfile)  {$jb_fstat = 0};
     if (-f $jb_hold)     {$jb_fstat = 0};  

      if($jb_fstat eq 1)  {
      if($dset =~ /FieldOff/) {
       $mchain = "ry2001,in,tpc_daq,tpc,rich,l3onl,Physics,FieldOff,Cdst,tags,Tree,evout,ExB";   
     }
          &create_jobs($jfile, $jbset, $mchain, $mlibVer, $JOB_DIR); 

         print "JOB ID = " ,$mjobID, " % " . $mjobFname,  "\n";

#####  fill  JobStatus table
      print "filling JobStatus table\n";
 
       &fillJSTable();   

#####  fill  jobRelations table
       print "filling jobRelations table\n";
       &fillJRelTable();

      }  
    }
   
#####delete from $JobStatusT inserted JobID

     $sql="delete from $JobStatusT WHERE ";    
     $sql.="jobID='$startId' AND "; 
     $sql.="prodSeries='$startSer'";
      print "$sql\n" if $debugOn;
     $rv = $dbh->do($sql) || die $dbh->errstr;

#### finished with data base
    &StDbProdDisconnect();

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
    $sql.="chainName='$mchName'";

     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;
    $new_id = $dbh->{'mysql_insertid'};     
  
    }

###############################################################################
  sub fillJRelTable {

    $sql="insert into $jobRelationsT set ";
    $sql.="JobID='$mjobID',";
    $sql.="prodSeries='$mprodSr',";
    $sql.="inputFile='$mflName'"; 

     print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;

   }

#############################################################################
##### create jobfiles to get default set of output files

 sub create_jobs {

  my ($gfile, $Jset, $fchain, $jlibVer, $JobDir ) = @_ ;

 my $Jsetd;
 my $Jsetr;
 my $Jsetn;
 my $inFile;
 my $logDir;
 my @pts;

    @pts = split ("_",$Jset);
    $Jsetr = $pts[1] . "/" .$pts[2];
    $Jsetd = $prodPeriod . "/" . $Jsetr;     
    $inFile =  $gfile . ".daq";
    $logDir = $JOB_LOG;   

##### print $job_set, "\n";
 
   my $jb_new = $JobDir . "/new_jobs/" .  $Jset . "_" . $gfile;
#     print $jb_new, "\n";
  
      my $hpss_raw_dir  = $TOPHPSS_SINK . "/" . $Jsetr;
      my $hpss_raw_file = $inFile;
      my $hpss_dst_dir  = $TOPHPSS_RECO . "/" . $Jsetd;
      my $hpss_dst_file0 = $gfile . ".event.root";
      my $hpss_dst_file1 = $gfile . ".hist.root";
      my $hpss_dst_file2 = $gfile . ".tags.root";
      my $hpss_dst_file3 = $gfile . ".runco.root";
#  if ( $gfile =~ /raw_0001/) {
      my $hpss_dst_file4 = $gfile . ".dst.root";
#    }
      my $executable     = "/afs/rhic.bnl.gov/star/packages/" . $jlibVer . "/mgr/bfc.csh";
      my $executableargs = $fchain; 
      my $log_dir       = $logDir;
      my $log_name      = $gfile . ".log";
      my $err_log       = $gfile . ".err";
      if (!open (JOB_FILE,">$jb_new")) {printf ("Unable to create job submission script %s\n",$jb_new);}
        print JOB_FILE "mergefactor=1\n";


       print JOB_FILE "#input\n";
       print JOB_FILE "      inputnumstreams=1\n";
       print JOB_FILE "      inputstreamtype[0]=HPSS\n";
       print JOB_FILE "      inputdir[0]=$hpss_raw_dir\n";
       print JOB_FILE "      inputfile[0]=$hpss_raw_file\n";
       print JOB_FILE "#output\n";
#     if ( $gfile =~ /raw_0001/) {
       print JOB_FILE "      outputnumstreams=5\n";
#     }else{
#       print JOB_FILE "      outputnumstreams=4\n";
#     }     
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
#     if ( $gfile =~ /raw_0001/) {     
       print JOB_FILE "      outputstreamtype[4]=HPSS\n";
       print JOB_FILE "      outputdir[4]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[4]=$hpss_dst_file4\n";
#     }else{
#     } 
       print JOB_FILE "#standard out -- Should be five outputs\n";
       print JOB_FILE "      stdoutdir=$log_dir\n";
       print JOB_FILE "      stdout=$log_name\n";
       print JOB_FILE "#standard error -- Should be five\n";
       print JOB_FILE "      stderrdir=$log_dir\n";
       print JOB_FILE "      stderr=$err_log\n";
       print JOB_FILE "      notify=starreco\@rcrsuser1.rcf.bnl.gov\n";
       print JOB_FILE "#program to run\n";
       print JOB_FILE "      executable=$executable\n";
       print JOB_FILE "      executableargs=$executableargs\n";
 
     close(JOB_FILE);

 }


