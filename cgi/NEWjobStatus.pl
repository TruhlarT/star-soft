#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbNewJobStatus.pl  script to get browser of nightly test files updated today. 
#  L. Didneko
#
###############################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use CGI;
use Class::Struct;
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";


# Tables
$FilesCatalogT = "FilesCatalog";
$JobStatusT = "JobStatus";

my $TOP_DIRD = "/star/rcf/test/new/";

my @OUT_DIR;
my @OUTD_DIR;


my $sec;
my $min;
my $hour;
my $mday;
my $mon;
my $year;
my $wday;
my $yday;
my $isdst;
my $thisday;



struct FileAttr => {
        flname  => '$', 
         lbtag  => '$',
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


($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    $thisday = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

  my $ii = 0;
  my $yr;
  my $mdate;
  $yr = 1900 + $year;
  $mon++;
  if( $mon < 10) { $mon = '0'.$mon };
  if( $mday < 10) { $mday = '0'.$mday };

my $ddate = $yr.$mon.$mday;
my $newlib;
my @arlib = ();
my $nd = 0;

  my $q=new CGI;

    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };

&StDbTJobsConnect();


 $sql="SELECT distinct LibTag FROM $JobStatusT where path LIKE '%test/new/%' order by createTime ";

  $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

     while($newlib = $cursor->fetchrow) {

        $arlib[$nd] = $newlib;
        $nd++;
    }
      $cursor->finish;

my $lastlib = $arlib[$nd-1];


 &beginHtml();


$sql="SELECT path, prodyear, logFile, LibTag, jobStatus, NoEventDone, chainOpt, memUsageF, memUsageL, CPU_per_evt_sec, createTime FROM $JobStatusT where path LIKE '%test/new/%'  AND avail = 'Y' order by prodyear ";


    $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

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
     ($$fObjAdr)->lbtag($fvalue)   if($fname eq 'LibTag');
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
 
 my $myFile;
 my $myPath;
 my $myEvtD;
 my $myJobS;
 my $myMemF;
 my $myMemL;
 my $myCPU;
 my $myCtime;
 my $mylib;
 my $mychain;
 my $cdate;
 my @prt;
 my $dtyear;
 my $evtype;


  foreach $eachFile (@dbFiles) {

        $myFile  = ($$eachFile)->flname;
        $myPath  = ($$eachFile)->fpath;
        $dtyear  = ($$eachFile)->pyear;
        $mylib   = ($$eachFile)->lbtag;
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
    }elsif($myPath =~ /trs/ or $myPath =~ /simu/ ) {
        $evtype = "MC";
    }

        @prt = split (" ", $myCtime);
    $cdate = $prt[0];  

        if($mylib eq $lastlib and $myJobS eq "Done") {

      &printRow();

#       }elsif( $mylib eq $lastlib  and $myJobS eq "Run not completed") {

       }elsif( $mylib eq $lastlib  and $myJobS ne "Done") {

      &printRowFd();

      }elsif(  $mylib ne $lastlib ) {

      $myJobS = "n/a";
      $myMemF = 0;
      $myMemL = 0;
      $myCPU = 0;
      $myEvtD = 0;

      &printRowNA();

        }
     }

 &StDbTJobsDisconnect();

 &endHtml();

#################
sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Status of nightly test for the new library</title>
   </head>
   <body BGCOLOR=\"cornsilk\"> 
     <h1 align=center>Status of nightly test for $lastlib library</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Year of production</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Event type</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log file name</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Library version</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Chain options</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Job status</B></TD>
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
<td>$mylib</td>
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
<td>$mylib</td>
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
<td>$mylib</td>
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


#####################
sub endHtml {
my $Date = `date`;

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
