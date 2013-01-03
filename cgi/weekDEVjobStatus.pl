#! /usr/local/bin/perl -w
#
#  $Id:
#
#  weekDEVjobStatus.pl  script to get browser of nightly test job status in DEV for a week. 
#  L. Didneko
#
###############################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use Mysql;
use Class::Struct;
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";


# Tables
$FilesCatalogT = "FilesCatalog";
$JobStatusT = "JobStatus";

my $TOP_DIRD = "/star/rcf/test/dev/";

my @OUT_DIR;
my @OUTD_DIR;
my @Nday = ("Mon","Tue","Wed","Thu","Fri", "Sat","Sun");


my %dayHash = (
                 "Mon" => 1,
                 "Tue" => 2, 
                 "Wed" => 3, 
                 "Thu" => 4, 
                 "Fri" => 5,
                 "Sat" => 6,
                 "Sun" => 7 
                 );

my %wkHash = (
                 "Mon" => "Monday",
                 "Tue" => "Tuesday", 
                 "Wed" => "Wednesday", 
                 "Thu" => "Thursday", 
                 "Fri" => "Friday",
                 "Sat" => "Saturday",
                 "Sun" => "Sunday" 
                 );

my %dmonth = (
               "01" => 76,
               "02" => 78,
               "03" => 76,
               "04" => 77,
               "05" => 76,
               "06" => 77,
               "07" => 76,
               "08" => 76,
               "09" => 77,
               "10" => 76,
               "11" => 77,
               "12" => 76
	      );

my $min;
my $hour;
my $mday;
my $mon;
my $year;
my $wday;
my $yday;
my $isdst;
my $thisday;
my $thistime;


 my $myFile;
 my $myPath;
 my $myEvtD;
 my $myJobS;
 my $myMemF;
 my $myMemL;
 my $myCPU;
 my $myCtime;
 my $mychain;
 my $cdate;
 my $bdate;
 my $dftime;
 my $dtyear;
 my $evtype;


struct FileAttr => {
        flname  => '$', 
         fpath  => '$',
         pyear  => '$',
         jobSt  => '$',
         timeS  => '$',
        noEvtD  => '$',
          memF  => '$',
          memL  => '$',
          mCPU  => '$', 
         chOpt  => '$',
		  };




($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;
    $thisday = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

 my $ii = 0;
 my $yr;
 my $mdate;
  $yr = 1900 + $year;
  $mon++;
  if( $mon < 10) { $mon = '0'.$mon };
  if( $mday < 10) { $mday = '0'.$mday };
  $mdate = $yr."-".$mon."-".$mday;
 my $iday;
 my $testDay;
 my $beforeDay;
 my $lstmon = 0;
 my $dfmon = 0;

  $iday = $dayHash{$thisday}; 
 $testDay = $Nday[$iday - 1];

my $ddate = $yr.$mon.$mday;
my $daydif = 77;
my $ttime = 0; 

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);


my $wkday =  $query->param('wday');

  if( $wkday eq "") {


print $query->header;
print $query->start_html('DEV jobs status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>DEV nightly test status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END


print "<p>";
print "</td><td>";
print "<h3 align=center> Day of test</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'wday',
                             -values=>\@Nday,
                             -default=>$testDay,
                             -size =>1);


print "<p>";
print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

  }else{

my $qqr = new CGI;

my $wkday    =  $qqr->param('wday');

my @dbFiles = ();
my $ndbFiles = 0; 
my $qpath; 


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";


# Tables
$FilesCatalogT = "FilesCatalog";
$JobStatusT = "JobStatus";

 print $qqr->header;
 print $qqr->start_html('Nightly test status for DEV library');
 print "<body bgcolor=\"cornsilk\">\n";

 $qpath = "/star/rcf/test/dev/%ittf%$wkday%"; 

&StDbTJobsConnect();

$sql="SELECT path, prodyear, logFile, jobStatus, NoEventDone, chainOpt, memUsageF, memUsageL, CPU_per_evt_sec, createTime FROM $JobStatusT where path LIKE ? AND avail = 'Y' order by prodyear ";

 $cursor =$dbh->prepare($sql)
   || die "Cannot prepare statement: $DBI::errstr\n";
 $cursor->execute($qpath);

 my $counter = 0;
 while(@fields = $cursor->fetchrow) {
   my $cols=$cursor->{NUM_OF_FIELDS};
   $fObjAdr = \(FileAttr->new()); 

  for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
     my $fname=$cursor->{NAME}->[$i];
#     print "$fname = $fvalue\n" ;

     ($$fObjAdr)->fpath($fvalue)   if($fname eq 'path'); 
     ($$fObjAdr)->pyear($fvalue)   if($fname eq 'prodyear'); 
     ($$fObjAdr)->flname($fvalue)  if($fname eq 'logFile');
     ($$fObjAdr)->noEvtD($fvalue)  if($fname eq 'NoEventDone');
     ($$fObjAdr)->jobSt($fvalue)   if($fname eq 'jobStatus');
     ($$fObjAdr)->memF($fvalue)    if($fname eq 'memUsageF');
     ($$fObjAdr)->memL($fvalue)    if($fname eq 'memUsageL');
     ($$fObjAdr)->mCPU($fvalue)    if($fname eq 'CPU_per_evt_sec');
     ($$fObjAdr)->timeS($fvalue)   if($fname eq 'createTime');
     ($$fObjAdr)->chOpt($fvalue)   if($fname eq 'chainOpt');

 }
        $dbFiles[$ndbFiles] = $fObjAdr;
        $ndbFiles++; 
      
  }
 
my @prt;

 &beginHtml();
  

  foreach $eachFile (@dbFiles) {

        $myFile  = ($$eachFile)->flname;
        $myPath  = ($$eachFile)->fpath;
        $dtyear  = ($$eachFile)->pyear;
        $myEvtD  = ($$eachFile)->noEvtD;
        $myJobS  = ($$eachFile)->jobSt; 
        $myMemF  = ($$eachFile)->memF; 
        $myMemL  = ($$eachFile)->memL; 
        $myCPU   = ($$eachFile)->mCPU;          
        $myCtime = ($$eachFile)->timeS;  
        $mychain = ($$eachFile)->chOpt;

    if($myPath =~ /embed/)  {
       $evtype = "embedding";
    }elsif($myPath =~ /daq/)  {
      $evtype = "realData";
    }elsif($myPath =~ /trs/ ) {
        $evtype = "MC";
    }

       @prt = split (" ", $myCtime);
    $cdate = $prt[0];
    $bdate = $cdate;
    $bdate =~ s/-//g;  

   $dftime = $ddate - $bdate ;
   $ttime = $dftime;
    @prt = ();
    @prt = split ("-", $cdate); 
    $lstmon = $prt[1];

    $daydif = $dmonth{$lstmon};

      $dfmon = $mon - $lstmon;
      if($dfmon == 1 ) {       

      $bdate = $prt[0].$mon."00";
      $dftime = $ddate - $bdate ;
    } 


     if( $dfmon == 1 and $ttime >= $daydif ) {
  
      $myJobS = "n/a";
      $myMemF = 0;
      $myMemL = 0;
      $myCPU = 0;
      $myEvtD = 0;

      &printRowNA(); 
 
     }elsif(  $dftime <= 6 and $myJobS eq "Done") {

      &printRow();

#       }elsif( $dftime <= 6  and $myJobS eq "Run not completed") {
      
     }elsif( $dftime <= 6  and $myJobS ne "Done") {

      &printRowFd(); 


     }elsif( $dfmon == 0 and  $dftime > 6.1 ) {     

      $myJobS = "n/a";
      $myMemF = 0;
      $myMemL = 0;
      $myCPU = 0;
      $myEvtD = 0;

      &printRowNA(); 

     }elsif( $dfmon < 0 ) {

      $myJobS = "n/a";
      $myMemF = 0;
      $myMemL = 0;
      $myCPU = 0;
      $myEvtD = 0;

      &printRowNA();

       }else{
     &printRow(); 
       } 

      }


 &StDbTJobsDisconnect();

 print $qqr->end_html;

 &endHtml();

 }


#################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Status of Nightly Test Jobs Produced on $wkday </title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>Status of Nightly Test Jobs Produced Last $wkHash{$wkday} </h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Year of production</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Event type</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log file name</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Chain options</B></TD>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=50><B>Job status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Number of events<br>Done</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Memory usage<br>for first event</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Memory usage<br>for last event </B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>CPU per event</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Last create date</B></TD>
</TR> 
   </head>
    <body>
END
}

############### 
sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$myPath</td>
<td><b>$dtyear</b></td> 
<td><b>$evtype</b></td> 
<td>$myFile</td>
<td><a href="http://www.star.bnl.gov/devcgi/jobChainRetrv.pl?set= $mychain">chain</td>
<td><b>$myJobS</b></td>
<td>$myEvtD</td>
<td>$myMemF</td>
<td>$myMemL</td>
<td>$myCPU</td>
<td>$cdate</td>
</TR>
END

}

############### 
sub printRowNA {

print <<END;
<TR BGCOLOR=\"#ffdc9f\" ALIGN=CENTER>
<td>$myPath</td>
<td><b>$dtyear</b></td>
<td><b>$evtype</b></td>  
<td>$myFile</td>
<td><a href="http://www.star.bnl.gov/devcgi/jobChainRetrv.pl?set= $mychain">chain</td>
<td><b>$myJobS</b></td>
<td>$myEvtD</td>
<td>$myMemF</td>
<td>$myMemL</td>
<td>$myCPU</td>
<td>$cdate</td>
</TR>
END

}

############### 
sub printRowFd {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER>
<td>$myPath</td>
<td><b>$dtyear</b></td>
<td><b>$evtype</b></td>  
<td>$myFile</td>
<td><a href="http://www.star.bnl.gov/devcgi/jobChainRetrv.pl?set= $mychain">chain</td>
<td><b>$myJobS</b></td>
<td>$myEvtD</td>
<td>$myMemF</td>
<td>$myMemL</td>
<td>$myCPU</td>
<td>$cdate</td>
</TR>
END

}

###############
sub endHtml {
my $Date = `/bin/date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Wed May 41  05:29:25 MET 2000 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}


######################
sub StDbTJobsConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbTJobsDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}



