#! /opt/star/bin/perl -w
#
# $Id:
# 
# $Log: 
# 
# createCalJob.pl        / L.Didenko 
# 
# script to create jobfiles to produce TPC driftvelocity calibrations
# script requires 3 arguments: production Series, year of data taken, library version
#
# example of usage:  createJobs.pl P01hg 2001 SL01g 
# 
##########################################################################################

use Mysql;
use Class::Struct;
use File::Basename;

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCpProdSetup.pl";

my $debugOn=0;

my @SetD;
my $nSetD = 0;
my $prodPeriod = $ARGV[0];
my $dyear = $ARGV[1];
my $mlibVer = $ARGV[2]; 
my $coll = "AuAu200";
my $dPath = "/daq/" . $dyear ;  
my $chainDir = "daq";

###Set directories to be created for jobfiles

my $DISK1        = "/star/rcf/prodlog/";
my $TOPHPSS_SINK = "/home/starsink/raw/daq";
my $TOPHPSS_RECO = "/home/starreco/reco";
my $JOB_LOG;
my $JOB_DIR;

my @runSet;
my $nrunSet = 0;

struct JFileAttr => {
         pathN   => '$', 
         fileN   => '$',
                    };

 ########  declare variables needed to fill the JobStatus table

 my $mchainOp;

 my $mflName = "n/a";
 my $mjobFname = "n/a";
 my $mjobFdir = "n/a";
 my $filename;


 $JOB_LOG =  $DISK1 . $prodPeriod . "/" ."calibration/log";
 $JOB_DIR =  "/star/u/starreco/" . $prodPeriod ."/requests/". $chainDir; 


 #####  start loop over input files
my $jbset;
my $jpath;  
my $jfile;
my $mchain;
my $mprodSr;
my @parts;
my $mySet;

 $mchain = "p00h";  
 $mprodSr = $prodPeriod; 

&StDbProdConnect();

  $sql="SELECT DISTINCT path FROM $FileCatalogT WHERE path like '%$dPath%' AND insertTime > 0107120000 ";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;
         
         $mySet = $fvalue  if ( $fname eq 'path'); 
         }
       next if ($mySet eq "/home/starsink/raw/daq/2001/04");
       next if ($mySet eq "/home/starsink/raw/daq/2001/192");
       next if ($mySet eq "/home/starsink/raw/daq/2001/193");
       next if ($mySet eq "/home/starsink/raw/daq/2001/198");
       next if ($mySet eq "/home/starsink/raw/daq/2001/199");     
        $SetD[$nSetD] = $mySet;
        $nSetD++; 
      }

 my $ii = 0;        
 my $istart = scalar(@SetD) - 2;

for ($ii=$istart; $ii< scalar(@SetD); $ii++)  { 
 
 $sql="SELECT path, fName FROM $FileCatalogT WHERE fName LIKE '%daq' AND path = '$SetD[$ii]' AND dataset like '$coll%' AND dataset like '%tpc%' AND dataStatus = 'OK' AND hpss = 'Y' ";

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

         ($$fObjAdr)->pathN($fvalue)    if( $fname eq 'path');
         ($$fObjAdr)->fileN($fvalue)   if( $fname eq 'fName'); 
  }

   $runSet[$nrunSet] = $fObjAdr;
   $nrunSet++;
  }
}

my $jb_fstat = 1;
my $jb_news;
my $jb_archive;
my $jb_jobfile;
my $jb_hold;

&StDbProdDisconnect();

  foreach my $jobDnm (@runSet){
      $jpath = ($$jobDnm)->pathN;
      $jfile = ($$jobDnm)->fileN;
       $jfile =~ s/.daq//g;
     @parts =  split ("/", $jpath);
     $jbset = $prodPeriod . "_" . $parts[5] . "_" .$parts[6];
          $mjobFname = "calibration" ."_" .$jbset ."_". $jfile;

     $jb_fstat = 1;
     $jb_news = $JOB_DIR . "/cal_jobs/" . $mjobFname;
     $jb_archive = $JOB_DIR . "/archive/" . $mjobFname;
     $jb_jobfile = $JOB_DIR . "/cjobfiles/" . $mjobFname;
     $jb_hold = $JOB_DIR . "/job_hold/" . $mjobFname;
     if (-f $jb_news)     {$jb_fstat = 0};
     if (-f $jb_archive)  {$jb_fstat = 0};
     if (-f $jb_jobfile)  {$jb_fstat = 0};
     if (-f $jb_hold)     {$jb_fstat = 0};
 
      if($jb_fstat == 1 )  { 
	if ( $jfile =~ /raw_000/ || $jfile =~ /raw_005/ || $jfile =~ /raw_010/ || $jfile =~ /raw_020/ || $jfile =~ /raw_030/ || $jfile =~ /raw_030/ ) {

          &create_jobs($jfile, $jbset, $mchain, $mlibVer, $JOB_DIR); 

         print "JOB Name: " , $mjobFname,  "\n";
	}
	}
   }

   exit;

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

    $fchain = "p00h";
    @pts = split ("_",$Jset);
   $Jsetr = $pts[1] . "/" .$pts[2];
    $Jsetd = $prodPeriod . "/" . $Jsetr;     
    $inFile =  $gfile . ".daq";  

##### print $job_set, "\n";
 
   my $jb_new = $JOB_DIR . "/cal_jobs/" . "calibration" ."_". $Jset . "_" . $gfile;
  
      my $hpss_raw_dir  = $TOPHPSS_SINK . "/" . $Jsetr;
      my $hpss_raw_file = $inFile;
      my $hpss_dst_dir  = $TOPHPSS_RECO . "/" . $Jsetd;
      my $hpss_dst_file0 = $gfile . ".dst.root";
      my $executable     = "/afs/rhic.bnl.gov/star/packages/" . $jlibVer . "/mgr/bfcT.csh";
      my $executableargs = $fchain; 
      my $log_dir       = $JOB_LOG;
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
       print JOB_FILE "      outputnumstreams=1\n";
       print JOB_FILE "#output stream \n";
       print JOB_FILE "      outputstreamtype[0]=HPSS\n";
       print JOB_FILE "      outputdir[0]=$hpss_dst_dir\n";
       print JOB_FILE "      outputfile[0]=$hpss_dst_file0\n";
       print JOB_FILE "#standard out -- Should be one output\n";
       print JOB_FILE "      stdoutdir=$log_dir\n";
       print JOB_FILE "      stdout=$log_name\n";
       print JOB_FILE "#standard error -- Should be one output\n";
       print JOB_FILE "      stderrdir=$log_dir\n";
       print JOB_FILE "      stderr=$err_log\n";
       print JOB_FILE "      notify=starreco\@rcrsuser1.rcf.bnl.gov\n";
       print JOB_FILE "#program to run\n";
       print JOB_FILE "      executable=$executable\n";
       print JOB_FILE "      executableargs=$executableargs\n";
 
     close(JOB_FILE);

 }






















