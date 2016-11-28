#!/usr/bin/env perl
#
#  $Id:
#
#  $Log:
# dbfillSplitJobs.pl - script to update splitJobs20XX table with splitted jobs status
# Requires 4 arguments: production series, trigset, year of data taken
# usage:  dbfillSplitJobs.pl P16ie AuAu_200_production_2016 2016 
#
# Author: L.Didenko
############################################################################

use Class::Struct;
use File::Basename;
use Compress::Zlib;
use Time::Local;
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

$JobStatusT = "splitJobs2016";

my $debugOn=0;

my $DISK1 = "/star/rcf/prodlog";
my $prodSr = $ARGV[0]; 
my $trig = $ARGV[1];
my $dyear = $ARGV[2];

my $datpath = "/star/data17/reco/".$trig."/ReversedFullField/".$prodSr."/".$dyear."/*/*/seq/";

print  $datpath, "\n";

my @prtk = ();
my @wrd = ();
my @prt = ();
 

my $jobFDir = "/star/u/starreco/" . $prodSr ."/requests/daq";

my $Startfile = "/star/u/starreco/cronj/" .$trig ."_split.log";

# if( -f $Startfile) {
#     `/bin/rm  $Startfile`;
  

struct JFileAttr => {
          prSer  => '$',
          lgFile => '$',
          lgDir  => '$',
          jbFile => '$',
          NoEvt  => '$',
          sbtime => '$',
          jobSt  => '$',  
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

my @jobSum_set;
my $jobSum_no = 0;


#####  connect to the DB

   &StDbProdConnect();

#####  select from JobStatus table files which should be updated

 $sql="SELECT logfileName, logfileDir, jobfileName, jobStatus, NoEvents, submitTime FROM $JobStatusT WHERE prodTag = '$prodSr' AND trigsetName = '$trig' AND jobStatus <> 'Done' " ;


    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
      while(@fields = $cursor->fetchrow) {
       my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(JFileAttr->new());
 
     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
         my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;


          ($$fObjAdr)->lgFile($fvalue)   if( $fname eq 'logfileName'); 
          ($$fObjAdr)->lgDir($fvalue)    if( $fname eq 'logfileDir'); 
          ($$fObjAdr)->jbFile($fvalue)   if( $fname eq 'jobfileName');
          ($$fObjAdr)->jobSt($fvalue)    if( $fname eq 'jobStatus');
          ($$fObjAdr)->NoEvt($fvalue)    if( $fname eq 'NoEvents');
          ($$fObjAdr)->sbtime($fvalue)   if( $fname eq 'submitTime');
     }

         $jobSum_set[$jobSum_no] = $fObjAdr;
         $jobSum_no++; 
 }


#########  declare variables needed to fill the JobStatus table

 my $mjobSt = "n/a";
 my $mNev  = 0;
 my $mCPU = 0;
 my $mRealT = 0;
 my $mmemSz = 0;
 my $mNoTrk = 0;
 my $mNoPrTrk = 0;
 my $mnodeId = "n/a";
 my $jb_logFile;
 my $jb_errFile;
 my $logFile;
 my $logDir;
 my $jobFname;
 my $jfile;
 my $mfile;
 my $lgsize;
 my $outSt = "n/a";
 my $nevt = 0;
 my $avr_prtracks = 0;
 my $no_prvertx = 0;
 my $nevent_vtx = 0;
 my $mudstfile;
 my $fullpath;
 my $fullname = "none";

########  declare variables needed to fill in FileCatalog table

 my $mrunId = 0;
 my $mcTime = "0000-00-00";
 my $mNevts = 0;
 my $jLog_err;
 my $lgfile;
 my $dbStat = "n/a";
 my $dbNev = 0;
 my $exterr = ".err.gz";
 my $subtime;
 my $epsubtime;
 my $epcrtime;
 my $epstrtime;
 my $difmin;
 my $difhour;
 my $rnhours;
 my $exhours; 
 my $sec1;
 my $min1;
 my $hr1;
 my $dy1;
 my $mn1;
 my $yr1;

#####=======================================================
#####  hpss reco daq file check

 my @flsplit = ();
 my $ltime;
 my $mfilegz;
 my $flag1 = 0;
 my $flag2 = 0;
 my $bfcflag = 0;
 my $logDir2;
 my $fullyear;
 my $cretime;
 my $strtime = "0000-00-00 00:00:00";
 my $mfTime;
 my $rday = "0000-00-00";
 my @sprt = ();


   foreach my $jobnm (@jobSum_set){
        $logFile = ($$jobnm)->lgFile;
        $logDir  = ($$jobnm)->lgDir;
        $jobFname = ($$jobnm)->jbFile;
        $dbStat    = ($$jobnm)->jobSt;
        $dbNev     = ($$jobnm)->NoEvt;
        $subtime   = ($$jobnm)->sbtime;

    
        $jfile = $logFile;
        $jfile =~ s/.log//g;

        $mudstfile = $jfile.".MuDst.root";

###########

      $mfilegz = $logDir ."/". $logFile .".gz";  

#  print $mfilegz, "\n";

      $mfile = $logDir ."/". $logFile;  
      $flag1 = 0;
      $flag2 = 0;  
      $ltime = 10; 
        if (-f $mfilegz)  {
#   print "Found log file  ", $mfilegz, "\n"; 

      $ltime = `mod_time $mfilegz`;

     ($mfTime) = (stat($mfilegz))[9];
     ($sec,$min,$hr,$dy,$mo,$yr) = (localtime($mfTime))[0,1,2,3,4,5];

     if( $yr > 97 ) {
        $fullyear = 1900 + $yr;
      } else {
        $fullyear = 2000 + $yr;
      };

      $mo = sprintf("%2.2d", $mo+1);
      $dy = sprintf("%2.2d", $dy);

     $cretime = sprintf ("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:00",
                       $fullyear,$mo,$dy,$hr,$min );
     $rday = sprintf ("%4.4d-%2.2d-%2.2d", $fullyear,$mo,$dy); 

  $epcrtime = timelocal($sec, $min, $hr, $dy, $mo-1, $fullyear );  

      $jb_logFile = $mfilegz;
      $jb_errFile = $jb_logFile;
      $jb_errFile =~ s/log.gz/err.gz/g; 
      $flag1 = 1;

   }      

        $exterr = ".err.gz"; 
        if( $flag1 == 1 ) {
          $lgsize = (stat($jb_logFile))[7];          
          if($lgsize > 2000) {

  if($subtime ne "0000-00-00 00:00:00") {

#  print $jb_logFile, "\n";

  @prt = ();
  @sprt = ();
  @prt = split (" ",$subtime);
  @sprt = split ("-",$prt[0]);
  $yr1 = $sprt[0];
  $mn1 = $sprt[1];
  $dy1 = $sprt[2];
  @sprt = ();
  @sprt = split (":",$prt[1]);
  $hr1 = $sprt[0];
  $min1 = $sprt[1];
  $sec1 = $sprt[2];

  $epsubtime = timelocal($sec1, $min1, $hr1, $dy1, $mn1-1, $yr1);

  $difmin = ($epcrtime - $epsubtime)/60.;
  $difhour = $difmin/60.;

  $rnhours = sprintf("%.2f", $difhour);

# print "Jobs total time:  ", $cretime,"   ",$subtime,"   ",$epcrtime,"   ",$epsubtime,"   ",$difmin,"   ",$rnhours, "\n";

  }else{

  $rnhours = 0;
  
  }

        $mjobSt = "n/a";
        $mNev  = 0;
        $mCPU = 0;
        $mRealT = 0; 
        $mmemSz = 0;
        $mNoTrk = 0;
        $mNoPrTrk = 0;
        $mnodeId = "n/a";

       parse_log($jb_logFile,$jb_errFile);

#     print "JobFile=", $mjobFname," % ",$jb_logFile,"  %  ","Job Status: ", $mjobSt," %  ", $mNev, "\n";

        $fullpath = $datpath.$mudstfile;
        $fullname = `ls $fullpath` ;

      print "#################" , "\n";
      print "Check file  ",$fullname,"\n";

      if($fullname =~ /$mudstfile/ ) {
	   $outSt = "yes" ;
	   print $outSt, "  ", $fullname, "\n";
      }


 if($strtime ne "0000-00-00 00:00:00") {

  @prt = ();
  @sprt = ();
  @prt = split (" ",$strtime);
  @sprt = split ("-",$prt[0]);
  $yr1 = $sprt[0];
  $mn1 = $sprt[1];
  $dy1 = $sprt[2];
  @sprt = ();
  @sprt = split (":",$prt[1]);
  $hr1 = $sprt[0];
  $min1 = $sprt[1];
  $sec1 = $sprt[2];

  $epstrtime = timelocal($sec1, $min1, $hr1, $dy1, $mn1-1, $yr1);

  $difmin = ($epcrtime - $epstrtime)/60.;
  $difhour = $difmin/60.;

  $exhours = sprintf("%.2f", $difhour);

# print "Jobs execution time:  ", $cretime,"   ",$strtime,"   ",$epcrtime,"   ",$epstrtime,"   ",$difmin,"   ",$exhours, "\n";

  }else{

  $exhours = 0;
  
  }

  if (($mjobSt ne  $dbStat) or ( $mNev != $dbNev ) )  {
        print "Updating  jobFile=", $jobFname," % ", "Job Status: ", $mjobSt," % "," MuDst Status:  ", $outSt, "\n";
#      print "Event,CPU,Trk,Vrtx:", $mNev," % ", $mCPU, " % ", $mNoTrk, " % ",$mNoPrTrk, "\n";

#####  update JobStatus table with info for jobs completed
#   print "updating JobStatus table\n";
 
     &updateJSTable(); 

      } else {
       next;
     }
     }else {
       next;
     }
     }else {
       next;
     }  
   }



#####  finished with data base
     &StDbProdDisconnect();

my $nmin;
my $nhour;
my $nday;
my $nmon;
my $nyear;
my $wday;
my $yday;
my $isdst;
my $thistime;

   ($nsec,$nmin,$nhour,$nday,$nmon,$nyear,$wday,$yday,$isdst) = localtime(time);
   $nmon++;

  if( $nmon < 10) { $nmon = '0'.$nmon };
  if( $nday < 10) { $nday = '0'.$nday };
  if( $nsec < 10) { $nsec = '0'.$nsec };

my  $yr = 1900 + $nyear;

   $thistime =  $yr.".".$nmon .".".$nday ." ".$nhour.":".$nmin.":".$nsec;

#  open (STDOUT, ">$Startfile");
#    print "Update finished at $thistime", "\n";

# close (STDOUT); 


 
  `sleep 600`;
    exit;

##############################################################################
  sub updateJSTable {

   $sql="update $JobStatusT set ";
   $sql.="jobStatus='$mjobSt',";
   $sql.="inputStatus='OK',";
   $sql.="createTime='$cretime',";
   $sql.="runDay='$rday',";
   $sql.="startTime='$strtime',";
   $sql.="NoEvents='$mNev',";
   $sql.="memsize='$mmemSz',";
   $sql.="CPU_evt='$mCPU',";
   $sql.="WallTime_evt='$mRealT',";
   $sql.="jobtotalTime='$rnhours',";
   $sql.="exectime='$exhours',";
   $sql.="outputStatus='$outSt',";
   $sql.="avg_no_tracks='$mNoTrk',";
   $sql.="avg_no_prtracks= '$mNoPrTrk',";   
   $sql.="nodeID='$mnodeId'";
   $sql.=" WHERE jobfileName = '$jobFname' ";
   print "$sql\n" if $debugOn;
#   print "$sql\n";
   $rv = $dbh->do($sql) || die $dbh->errstr;
    }

#######################################################################################

 sub mod_time($) { 
my $atime;   # Last access time since the epoch
my $mtime;   # Last modify time since the epoch
my $ctime;   # Inode change time (NOT creation time!) since the epoch
my $now;     # current time 
my $dev;
my $ino;
my $mode;
my $nlink;
my $uid;
my $gid;
my $rdev;
my $blksize;
my $blocks;
my $dtime;
my $file_name =  $ARGV[0];

$now = time;
($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks ) = stat $file_name;
printf ($mtime);
$dtime = $now - $mtime;
printf  ($dtime) ;
}

############################################################################################

sub parse_log($$) {

  my $logName = $_[0];
  my $errFile = $_[1];
  my $line; 
  $mjobSt = "Run not completed";
  my $Err_messg = "none";
  my $exmessg = "none";
  my $logFile;
  my $basefile;
  my $gz;
  my $status;
  my $comp; 

  my $no_event = 0;
  my $num_event = 0;
  my $num_line = 0;  
  my $maker_size = 0;
  my $mymaker; 
  my $no_tracks = 0; 
  my @no_prtracks = (); 
  my @no_prtrck_nfit15 = ();
  my $tot_tracks = 0;
  my $tot_prtracks = 0;
  my @word_tr = ();
  my @nparts;
  my @size_line;
  my @words;
  my @prt;
  my $cpuflag = 0;
  my $mRealTbfc = 0;
  my $mCPUbfc = 0;
  my $bfcflag = 0;
  my @vrank = ();
  my $npr = 0;
  my @nmb = ();
  my @nmbx = ();
  my $smon;
  $nevt = 0;
  $mEvtSk = 0;
  $mmemSz = 0; 
  $mnodeId = "n/a";
  $mRealT = 0;
  $mCPU = 0;
  $no_prvertx = 0;
  $nevent_vtx = 0;

 #---------------------------------------------------------
#  print "Log name   ", $logName, "\n";

 $nevent_vtx = 0;

#   $nevent_vtx = `zgrep 'primary vertex(0):' $logName | wc -l ` ;

    if($logName =~ /\.gz/){
        $gz     = gzopen($logName , "r");
        $status = defined($gz);
        $comp   = 1;
    } else {
        $comp   = 0;
        $status = open(FI,"logName");
    }

 $Anflag = 0;   

        if( $comp){
        $status = ($gz->gzreadline($line) > 0);
        } else {
        $status = defined($line = <FI>);
        }

        while ( $status ){
            chomp($line);

 @prt = ();

     if ( $line =~ /Start at Date / ) {
       @prt = split(" ",$line);
# print "Check start time  ", $prt[6]," % ", $prt[7]," % ",$prt[8]," % ", $prt[9], "\n";
       
       $smon = $monthHash{"$prt[6]"};
       if($smon < 10) {$smon = "0".$smon;}

       $strtime = $prt[9]."-".$smon."-".$prt[7]." ".$prt[8] ;  
#  print "Start time  = ", $smon,"   %  ", $strtime, "\n";
     }

 @prt = ();

     if ( $line =~ /You are using STAR_LEVEL/ ) {
       @word_tr = split(":",$line);
       $mnodeId = $word_tr[4];  
#  print $mnodeId, "\n";
     }

         if ($line =~ /Processing bfc.C/) {
         $bfcflag++;
       }
              if( $bfcflag == 1) { 

# get memory size at the outputStream
#     if ($num_line > 1000){
#     if( $line =~ /EndMaker/ and $line =~ /outputStream/){
#       @size_line = split(" ",$line); 
#       $size_line[6] =~ s/=//g;      
#        $maker_size += $size_line[6];
#         $mymaker = $size_line[3];
#     }
#   }
# get  number of events

   if ( $line =~ /QAInfo: Done with Event/ ) {
      $no_event++;
      } 


# get number of tracks, vertices and hits

  @nmb = ();
  @nmbx = ();
  @word_tr = ();

     if ($line =~ /track nodes:/ ) {
           my  $string = $line;
             @word_tr = split /:/,$string;            
              $no_tracks = $word_tr[2];
              $tot_tracks += $no_tracks; 
#              print $word_tr[2], $no_tracks, "\n";

               if($no_tracks >= 1) {
              $nevt++;
               }

          $npr = 0;
          @no_prtracks = ();
          @no_prtrck_nfit15 = ();

        }elsif(  $line =~ /QA :INFO/ and $line =~ /Rank/ and $line =~ /#V/ ) {
              @word_tr = ();
              @nmbx = ();
              @word_tr = split (":",$line);
              @nmbx = split (" ",$word_tr[4]);
#         print "Check splitting   ",$word_tr[3]," %  ", $word_tr[4]," %  ", $word_tr[5]," % ", $word_tr[6], "\n";
             $vrank[$npr] = $nmbx[0];
             @nmb = ();
             @nmb = split (",",$word_tr[5]);
             $no_prvertx++;
             $no_prtracks[$npr] = $nmb[1];             
             $no_prtrck_nfit15[$npr]  = $nmb[2];

             $tot_prtracks += $no_prtracks[$npr];
             
             $npr++;

           if ($npr == 1 ) {
              $nevent_vtx++;
           }

	  }
           
########## check
# check if job crashed 

      if($line =~ /Bus error/) {
         $Err_messg = "Bus error";
       }

    elsif ($line =~ /Segmentation violation/ or $line =~ /segmentation violation/) {
             $Err_messg = "segmentation violation";
    }
    elsif ($line =~ /Segmentation fault/ or $line =~ /segmentation fault/ ) {
	    $Err_messg = "segmentation fault";
     }

    elsif ($line =~ /eventIsCorrupted/)  {
            $Err_messg  = "Corrupted event";
    } 
    elsif ($line =~ /Interpreter error recovered/)  {
             $Err_messg = "Interpreter error recovered";
           }
    
   elsif ($line =~ /Killed/)  {
             $Err_messg = "Killed";
           }

   elsif ($line =~ /StMuDstMaker:ERROR - TFile::WriteBuffer/)  {
             $Err_messg = "Error WriteBuffer";
           }
   elsif ($line =~ /StMuDstMaker:FATAL - TFile::WriteBuffer/)  {
             $Err_messg = "Error WriteBuffer";
           }

   elsif ($line =~ /error writing all requested bytes to file/) {
             $Err_messg = "Error WriteBuffer";
       }
   elsif ($line =~ /Abort/ and $Err_messg eq "none" )  {
             $Err_messg = "Abort";
           }

   elsif ($line =~ /glibc detected/)  {
             $Err_messg = "glibc detected";
	 }

   elsif ($line =~ /Tried to find a host for 500 times, will abort now/)  {
             $Err_messg = "DB connection failed";
           }

  elsif ($line =~ /FATAL/ and $line =~ /floating point exception/ )  {
             $Err_messg = "FPE";
	 }

 elsif ($line =~ /TPC has tripped - declaring EOF/ )  {
             $Err_messg = "TPC tripped";
         }


# check how many events have been skiped
  
      if ( $line =~ /QAInfo:Run/ and $line =~ /Total events processed/) {
#  print $line, "\n";
        @word_tr = split /:/,$line;
        $mEvtSk =  $word_tr[4];
      }

 $mNev =  $no_event;

#check if job is completed
    if ( $line =~ /Run completed/) {          
          $mjobSt = "Done";      
        }

   if ($no_event != 0) {
   if ($line =~ /StBFChain::bfc/) {
      @words= split (" ", $line); 

     if($words[8] eq "=" ){

      $mCPUbfc = $words[9];
      }elsif($words[8] eq "Cpu" ){
       $mCPUbfc = $words[10];
      }else{
 
      $mCPUbfc = $words[8];
      $mCPUbfc = substr($mCPUbfc,1) + 0;
    }

      if($words[6] eq "=" ){
      $mRealTbfc = $words[7];
      }else{
      $mRealTbfc = $words[6];
      $mRealTbfc = substr($mRealTbfc,1) + 0;
    }
#      print "CHeck CPU, RealTime   : ",  $mCPUbfc,"    ", $mRealTbfc,"\n";

     $cpuflag = 1;
    }  
   }
  }

  $num_line++;

      if( $comp){
                $status = ($gz->gzreadline($line) > 0);
           } else {
                $status = defined($line = <FI>);
           }
     }

       if($comp){
        $gz->gzclose();
        } else {
        close(FI);
        }

# print "Number no_event, status ", $mNev,"  %  ", $mjobSt,"\n";

  $num_event = $mNev - $mEvtSk;
 
  if( $num_event > 0 )  {

    if($cpuflag == 1) {
    $mCPU = $mCPUbfc/$num_event;
    $mRealT = $mRealTbfc/$num_event;

#  print "CPU2 ", $mCPU,"   %   ", $mRealT, "\n";
   }
 } 
 
   if($nevt >=1 )  {
  $mNoTrk    = $tot_tracks/$nevt;
  $mNoPrTrk  = $tot_prtracks/$nevt;  
 }

##----------------------------------------------------------------------------
# parse error log file

   my @err_out;
   my $mline;

# print "Check err file name  ", $errFile,"\n"; 

 @err_out = `zcat $errFile | tail -200 `;

  foreach $mline (@err_out){
          chop $mline;
       if ( $mline =~ /No space left on device/)  {
        $Err_messg = "No space left on device";
     } 

     elsif ($mline =~ /glibc detected/)  {
             $Err_messg = "glibc detected";
      }
     elsif ($mline =~ /Error calling module/) {
       chop $mline;  
      $Err_messg = $mline;
      }
     elsif ($mline =~ /Stale NFS file handle/) {
  
      $Err_messg = "Stale NFS file handle";
     }       
     elsif ( $mline =~ /Assertion/ & $mline =~ /failed/)  {
        $Err_messg = "Assertion failed";
     } 
      elsif ($mline =~ /Fatal in <operator delete>/) {
  
       $Err_messg = "Fatal in <operator delete>";   
     }
       elsif ($mline =~ /Fatal in <operator new>/) {
  
       $Err_messg = "Fatal in <operator new>";   
     }
      elsif ($mline =~ /Error: Unexpected EOF/) {
      $Err_messg = "Unexpected EOF";
     } 
     elsif ($mline =~ /Error: Symbol G__exception is not defined/) {
      $Err_messg = "G_exception not defined";     
     } 
    }
      if ( $Err_messg ne "none") {
     $mjobSt = $Err_messg;
   } 

#  print "Check at the end ",$logName,"   ", $errFile,"   ",$mjobSt, "\n";

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
