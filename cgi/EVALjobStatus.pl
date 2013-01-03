#! /usr/local/bin/perl -w
#
#  $Id:
#
#  NewJobStatusSite.pl  script to  browse  test results for NEW libraries created on site. 
#  L. Didneko
#
#######################################################################################################


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

$JobStatusT = "evalJobStatus";

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
 my $bdate;
 my @prt;
 my $dtyear;
 my $evtype;

 my $lstmon = 0;
 my $dfmon = 0;


($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    $thisday = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

  my $ii = 0;
  my $yr;
  my $mdate;
  $yr = 1900 + $year;
  $mon++;
  if( $mon < 10)  { $mon = '0'.$mon };
  if( $mday < 10) { $mday = '0'.$mday };

my $ddate = $yr.$mon.$mday;
my $mdate = $yr."-".$mon."-".$mday;

my $daydif = 76;
my $ttime = 0;
my $dftime = 0;

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

my $nd = 0;
my @arlib = ("Sti-CA","Sti","Stv","Stv-CA","Sti.AgML","Stv.AgML");


my $query=new CGI;

my $scriptname = $query->url(-relative=>1);

my $trlib = $query->param('rlib');

  if( $trlib eq "" ) {

print $query->header();
print $query->start_html('Status of EVAL library test jobs');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Status of EVAL library test jobs </u></h1>\n";


print "<br>";
print "<br>";
print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h3 align=center>Select tracker</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'rlib',
                             -values=>\@arlib,
                             -default=>Sti-CA,
                             -size=>1);

print "</td> </tr> </table><hr><center>";
print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit(),"<p>";
print $query->reset();
print $query->endform();
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html();

  }else{

my $qqr = new CGI;

my $trlib = $qqr->param('rlib');

my @prt = ();
# @prt = split("_",$trklib); 

$JobStatusT = "evalJobStatus";

 print $qqr->header;
 print $qqr->start_html('Status of EVAL library test jobs');
 print "<body bgcolor=\"cornsilk\">\n";

&StDbTJobsConnect();


$sql="SELECT path, prodyear, LibTracker, logFile, jobStatus, NoEventDone, chainOpt, memUsageF, memUsageL, CPU_per_evt_sec, createTime FROM $JobStatusT where LibTracker = ?  and avail = 'Y' order by prodyear ";


    $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($trlib);

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
     ($$fObjAdr)->lbtag($fvalue)   if($fname eq 'LibTracker');
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
 
  &beginHtml(); 

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
 
    if($myPath =~ /embed/ ) {
      $evtype = "embedding";
    }elsif($myPath =~ /daq/)  {
      $evtype = "realData";
    }elsif($myPath =~ /trs/ ) {
       $evtype = "MC";
    }

    @prt = ();
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

#     }elsif( $dftime <= 6  and $myJobS eq "Run not completed") {

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
          <title>Status of nightly test for the EVAL library</title>
   </head>
   <body BGCOLOR=\"cornsilk\"> 
     <h1 align=center>Status of nightly test jobs for <font color="#ff0000">$trlib</font> tracker </h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Year of production</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Event type</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log file name</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Tracker Lib</B></TD>
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
