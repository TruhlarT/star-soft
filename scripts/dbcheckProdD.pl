#! /opt/star/bin/perl -w
#
#  $Id:
#
# dbcheckProdD.pl - check missing in operation reco files located on disk 
# Requires two arguments: production series, trigger name, disk location
# usage dbcheckProdD.pl P01gk MinBiasVertex /star/data18/reco 
# L.Didenko
############################################################################

use Mysql;
use Class::Struct;
use File::Basename;
use Net::FTP;

require "/afs/rhic/star/packages/scripts/dbCpProdSetup.pl";

my $debugOn=0;


my $DISK1 = "/star/rcf/prodlog";
my $prodSr = $ARGV[0]; 
my $trig = $ARGV[1];
my $DISK = $ARGV[2];
my $jobFDir = "/star/u/starreco/" . $prodSr ."/requests/";

my @dbSet;
my $ndbSet = 0;
my @SetS = ();
my $nSetS = 0;
my $mySet;
my @prtk;

 struct RunAttr => {
        drun   => '$',
        dtSet  => '$',
        dtTrg  => '$',
        dpath  => '$',
                  };
 struct DBrunAttr => {            
            dbfl  => '$',
           dbpth  => '$',
           dbsize => '$',
           dbrun  => '$',
             };  

  &StDbProdConnect();

  $sql="SELECT DISTINCT path FROM $FileCatalogT WHERE trigger = '$trig' AND path like '$DISK%' AND jobID like '%$prodSr%' ";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#         print "$fname = $fvalue\n" ;
         
         $mySet = $fvalue  if ( $fname eq 'path'); 
         }
        $SetS[$nSetS] = $mySet;
        $nSetS++; 
     }

my $i = 0;

my @diskRecoFiles;
my $nDiskFiles = 0;
my @diskRecoDirs;
my %flagHash = ();

# @SetS = ( 
#           "/star/data19/reco/dAuCombined/ReversedFullField/P03ia/2003/047",
#           "/star/data19/reco/dAuCombined/ReversedFullField/P03ia/2003/045",
#           "/star/data19/reco/dAuCombined/ReversedFullField/P03ia/2003/043",
#            "/star/data23/reco/dAuMinBias/FullField/P03ia/2003/035",
#            "/star/data23/reco/dAuMinBias/FullField/P03ia/2003/037",
#           "/star/data23/reco/dAuMinBias/FullField/P03ia/2003/038",
#            "/star/data23/reco/dAuMinBias/FullField/P03ia/2003/039",
#            "/star/data23/reco/dAuMinBias/FullField/P03ia/2003/040", 
#             "/star/data23/reco/dAuMinBias/ReversedFullField/P03ia/2003/019",
#             "/star/data23/reco/dAuMinBias/ReversedFullField/P03ia/2003/020",
#             "/star/data23/reco/dAuMinBias/ReversedFullField/P03ia/2003/041", 
# );


 &StDbProdDisconnect();

my $recoDir = ("daq");

struct JFileAttr => {
          prSer  => '$',
          job_id => '$', 
          smFile => '$',
          smDir  => '$',
          jbFile => '$',
          NoEvt  => '$',
          NoEvSk => '$',
          jobSt  => '$',  
		    };
 
 struct FileAttr => {
    filename  => '$',
    fpath     => '$', 
    dsize     => '$',
    timeS     => '$',
    faccess   => '$',
    fowner    => '$',
    iflag     => '$',
                  };

 my %monthHash = (
                  "Jan" => 1,
                  "Feb" => 2, 
                  "Mar" => 3, 
                  "Apr" => 4, 
                  "May" => 5, 
                  "Jun" => 6, 
                  "Jul" => 7, 
                  "Aug" => 8, 
                  "Sep" => 9, 
                  "Oct" => 10, 
                  "Nov" => 11, 
                  "Dec" => 12
                  );

my $jbSt = "n/a";
my @runDescr;
my $nrunDescr = 0;

########## Find reco for daq files on HPSS

  my $maccess; 
  my $mdowner; 
  my $flname;

my $fullpath;
my $fulldbpath;


 my $mFile;
 my @parts;
 my $mjobDg = "none";

#########  declare variables needed to fill the JobStatus table

 my $mjobSt = "n/a";
 my $mNev  = 0;
 my $mlogFile;
 my $mproSr;
 my $jfile;
 my $mfile;
 my $fullname;

########  declare variables needed to fill the database table

 my $mJobId = "n/a";
 my $mrunId = 0;
 my $mfileSeq = 0;
 my $mevtType = 0;
 my $mfName = "n/a";
 my $mpath  = "n/a";
 my $mdataSet = "n/a";
 my $msize = 0;
 my $mcTime = 00-00-00;
 my $mNevts = 0;
 my $mNevtLo = 0;
 my $mNevtHi = 0;
 my $mowner = "n/a";
 my $mprotc = "-rw-r-----";
 my $mtype = "n/a";
 my $mcomp = "n/a";
 my $mformat = "n/a";
 my $msite = "n/a";
 my $mhpss = "Y";
 my $mstatus = 0;
 my $mdtStat = "OK";
 my $mcomnt = " ";
 my $mcalib = "n/a";
 my $mtrigger = "n/a";
 my $mstream = 0;
 my $mSeq = 0;
 my $Seq = 0;
 my $compont;
 my $lgfile;
 my $dbfile ;
 my $dbpath ;
 my $dbStat = "n/a";
 my $mdone = 0;
 my $mName;
  my $dbsz = 0;

#####=======================================================
#####  hpss reco daq file check

 my @flsplit;
 my $mfileS;
 my $extn;
 my $mrun;
 my $Numrun;
 my $mdtSet;
 my $mTrg;
 my $diskDir;


  &StDbProdConnect();

  foreach my $diskDir (@SetS) {

  @diskRecoFiles = ();
  $nDiskFiles = 0;
 
    print $diskDir, "\n";
   if (-d $diskDir) {
    opendir(DIR, $diskDir) or die "can't open $diskDir\n";
    while( defined($flname = readdir(DIR)) ) {
       next if $flname =~ /^\.\.?$/;
       next if $flname =~ /hold/;
  
          $maccess = "-rw-r--r--"; 
          $mdowner = "starreco";

       $fullname = $diskDir."/".$flname;
       my @dirF = split(/\//, $diskDir); 

      ($size, $mTime) = (stat($fullname))[7, 9];
      ($sec,$min,$hr,$dy,$mo,$yr) = (localtime($mTime))[0,1,2,3,4,5];

      if( $yr > 92 ) {
        $fullyear = 1900 + $yr;
      } else {
        $fullyear = 2000 + $yr;
      }
      $mo = sprintf("%2.2d", $mo+1);      
      $dy = sprintf("%2.2d", $dy);
      $timeS = sprintf ("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:00",
                         $fullyear,$mo,$dy,$hr,$min);

 my $fflag = 1;

     $fObjAdr = \(FileAttr->new());
      ($$fObjAdr)->filename($flname);
      ($$fObjAdr)->fpath($diskDir);
      ($$fObjAdr)->dsize($size);
      ($$fObjAdr)->timeS($timeS);
      ($$fObjAdr)->faccess($maccess);
      ($$fObjAdr)->fowner($mdowner);
      ($$fObjAdr)->iflag($fflag);
      $diskRecoFiles[$nDiskFiles] = $fObjAdr;
      $nDiskFiles++;
#     }
  }
  closedir DIR;
}

  print "Total reco files: $nDiskFiles\n";

 @dbSet = ();
 $ndbSet = 0; 
 $msize = 0;
 $dbsz = 0;
    
 $sql="SELECT fName, path, size  FROM $FileCatalogT  WHERE path = '$diskDir' and fName like '%.root' ";

    $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
           $cursor->execute;
 
   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(DBrunAttr->new());
  
   for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       ($$fObjAdr)->dbfl($fvalue)      if( $fname eq 'fName');
       ($$fObjAdr)->dbpth($fvalue)     if( $fname eq 'path');
       ($$fObjAdr)->dbsize($fvalue)     if( $fname eq 'size');
         }
       $dbSet[$ndbSet] = $fObjAdr;
       $ndbSet++;
      }
#}

      foreach my $eachFile (@diskRecoFiles) {

      $mfName = ($$eachFile)->filename;
      $mpath = ($$eachFile)->fpath; 
      $msize = ($$eachFile)->dsize;  
      $fullpath = $mpath . "/" . $mfName; 
      $flagHash{$fullpath} = ($$eachFile)->iflag;

       foreach my $eachdbFile (@dbSet)  {
          $dbfile = ($$eachdbFile)->dbfl;
          $dbpath = ($$eachdbFile)->dbpth; 
          $dbsz   =  ($$eachdbFile)->dbsize;   
           $fulldbpath = $dbpath . "/" . $dbfile;
         
          if(($fullpath eq $fulldbpath) and ($dbsz == $msize) ) {
             $flagHash{$fullpath} = 0;
           last;
        }
         elsif(($fullpath eq $fulldbpath) and ($dbsz < $msize) ) {
             $flagHash{$fullpath} = 2;
           last;
#        }         
	   }else{
           next;
	 }
	}
    }

         foreach my $eachDstFile (@diskRecoFiles) {

#####   reinitialize variables
 $mJobId = "n/a"; 
 $mrunId = 0;
 $mfileSeq = 0;
 $mevtType = 0;
 $mfName = "n/a";
 $mpath  = "n/a";
 $mdataSet = "n/a";
 $mNevts = 0;
 $mNevtLo = 0;
 $mNevtHi = 0;
 $msize = 0;
 $mcTime = 00-00-00;
 $mowner = "n/a";
 $mprotc = "-rw-r-----";
 $mtype = "n/a";
 $mcomp = "n/a";
 $mformat = "n/a";
 $msite = "n/a";
 $mhpss = "Y";
 $mstatus = 0;
 $mdtStat = "OK";
 $mcomnt = " ";   
 $mcalib = "n/a";
 $mtrigger = "n/a";
 $mjobSt = "n/a"; 
 $mlogFile = "none.log"; 

#####   end of reinitialization

  $mfName = ($$eachDstFile)->filename;
  $mpath  = ($$eachDstFile)->fpath;
  $mcTime  = ($$eachDstFile)->timeS;
  $mprotc = ($$eachDstFile)->faccess;
  $mowner = ($$eachDstFile)->fowner;
  $msize = ($$eachDstFile)->dsize;
  $fullName = $mpath . "/" . $mfName; 
 if( $flagHash{$fullName} >= 1) {

   if($mfName =~ /root/) {
      $mformat = "root";
      $basename = basename("$mfName",".root");   
      $compont = $basename;
      if ($compont =~ m/\.([A-Za-z0-9_]{3,})$/) {
      $mcomp = $1;
    }else{
     $mcomp = "unknown";
    } 
    @flsplit = split ("_",$basename);  
    $mrun =  $flsplit[2];
    $mrunId = $mrun;

    $mSeq = $flsplit[4];
    $mName = $flsplit[1];
    $extn = "." . $mcomp;
#    $mfileSeq = basename("$mSeq","$extn");
#      $mstream = 0;
    $Seq = basename("$mSeq","$extn");
    $mfileSeq = substr($Seq,3) + 0;
    $mstream = substr($Seq,0,-4) + 0;
 
    $jfile = basename("$compont", "$extn"); 
    $msite = "disk_rcf";
    $mhpss = "N";
    $mtype = "daq_reco";

    $mevtType = 3;

  $sql="SELECT JobID, prodSeries, jobfileName, sumFileName, jobStatus, NoEvents FROM $JobStatusT WHERE prodSeries= '$prodSr' AND sumFileName like '$jfile%' AND jobStatus <> 'n/a'";

   $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;
 
    while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
 
   for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
#        print "$fname = $fvalue\n" ;

        $mproSr   = $fvalue  if( $fname eq 'prodSeries');
        $mJobId   = $fvalue  if( $fname eq 'JobID');
        $mlogFile = $fvalue  if( $fname eq 'sumFileName');
        $mNevts   = $fvalue  if( $fname eq 'NoEvents');
        $mjobSt   = $fvalue  if( $fname eq 'jobStatus');

      }
   }
        $lgfile = $mlogFile;
        $lgfile =~ s/.log//g;
       if ( $mfName =~ /$lgfile/) {

        if ( $mjobSt eq "Done") {
         $mdtStat = "OK";
         $mcomnt = " ";
      } else{
        $mdtStat = "notOK";
        $mcomnt = $mjobSt;
      }

 $sql="SELECT DISTINCT runID, dataset,trigger FROM $FileCatalogT WHERE runID = '$mrunId' AND fName like '%daq' ";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;
   
       $mdataSet = $fvalue   if( $fname eq 'dataset');
       $mtrigger = $fvalue   if( $fname eq 'trigger');   
          
         }
      }

    if( $flagHash{$fullName} == 1) {
    print "File to be inserted :", $mpath, " % ",$mfName, " % ",$mdtStat ," % ",$mNevts, " % ",$mcTime, "\n"; 
 
   &fillDbTable();   

    }elsif( $flagHash{$fullName} == 2) {

   print "File to be updated :", $mpath, " % ",$mfName, " % ",$mdtStat ," % ",$mNevts, " % ",$mcTime, "\n"; 
  
    &updateDbTable();

  }
       } else {
         next;
       }
      }else{
       next;
    }
    }else{
    next;
   }
  }
}

#####   finished with data base

 &StDbProdDisconnect();

    exit;

##############################################################################

  sub fillDbTable {

   $sql="insert into $FileCatalogT set ";
   $sql.="jobID='$mJobId',";
   $sql.="runID='$mrunId',";
   $sql.="fileSeq='$mfileSeq',";
   $sql.="eventType='$mevtType',";
   $sql.="fName='$mfName',";
   $sql.="path='$mpath',";
   $sql.="dataset='$mdataSet',";
   $sql.="size='$msize',";
   $sql.="createTime='$mcTime',";
   $sql.="Nevents='$mNevts',";
   $sql.="NevLo='$mNevtLo',";
   $sql.="NevHi='$mNevtHi',";
   $sql.="owner='$mowner',";
   $sql.="protection='$mprotc',";
   $sql.="type='$mtype',";
   $sql.="component='$mcomp',";
   $sql.="format='$mformat',";
   $sql.="site='$msite',"; 
   $sql.="hpss='$mhpss',";
   $sql.="status= 0,";
   $sql.="dataStatus='$mdtStat',";
   $sql.="calib='$mcalib',";
   $sql.="trigger='$mtrigger',";
   $sql.="stream='$mstream',";
   $sql.="comment='$mcomnt' ";
   print "$sql\n" if $debugOn;
   $rv = $dbh->do($sql) || die $dbh->errstr;
   }

##############################################################################

  sub updateDbTable {

    $sql="update $FileCatalogT set ";
    $sql.="size='$msize',";
    $sql.="createTime='$mcTime',";
    $sql.="Nevents='$mNevts',";
    $sql.="dataStatus='$mdtStat',";     
    $sql.="comment='$mcomnt' ";  
    $sql.=" WHERE fName = '$mfName' AND path='$mpath' ";
    print "$sql\n" if $debugOn;
    $rv = $dbh->do($sql) || die $dbh->errstr;

    }
      
