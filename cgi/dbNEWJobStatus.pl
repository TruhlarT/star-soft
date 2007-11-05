#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbNewJobStatus.pl  script to get browser of nightly test files updated today. 
#  L. Didneko
#
###############################################################################

use CGI;
use Mysql;
use Class::Struct;


require "/afs/rhic.bnl.gov/star/packages/scripts/dbTJobsSetup.pl";

my $TOP_DIRD = "/star/rcf/test/new/";
my @dir_year = ("year_1h", "year_2001", "year_2003", "year_2004");
my @node_dir = ("trs_sl302","trs_sl302_opt", "trs_sl302.ittf", "trs_sl302.ittf_opt", "daq_sl302", "daq_sl302_opt","daq_sl302.ittf","daq_sl302.ittf_opt"); 
my @hc_dir = ("hc_lowdensity", "hc_standard", "hc_highdensity", "peripheral", "minbias", "central");

my @OUT_DIR;
my @OUTD_DIR;

my %dayHash = (
                 "Mon" => 1,
                 "Tue" => 2, 
                 "Wed" => 3, 
                 "Thu" => 4, 
                 "Fri" => 5,
                 "Sat" => 6,
                 "Sun" => 7 
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



struct FileAttr => {
        flname  => '$', 
         lbtag  => '$',
         fpath  => '$',
         jobSt  => '$',
         timeS  => '$',
        noEvtD  => '$',
          memF  => '$',
          memL  => '$',
          mCPU  => '$', 
         chOpt  => '$',
		  };

&cgiSetup();


($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    $thisday = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

&StDbTJobsConnect();

 &beginHtml();


$sql="SELECT path, logFile, LibTag, jobStatus, NoEventDone, chainOpt, memUsageF, memUsageL, CPU_per_evt_sec, createTime FROM $JobStatusT where path LIKE '%test/new%sl302%'  AND avail = 'Y'";
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

  foreach $eachFile (@dbFiles) {

        $myFile  = ($$eachFile)->flname;
        $myPath  = ($$eachFile)->fpath;
        $mylib   = ($$eachFile)->lbtag;
        $myEvtD  = ($$eachFile)->noEvtD;
        $myJobS  = ($$eachFile)->jobSt; 
        $myMemF  = ($$eachFile)->memF; 
        $myMemL  = ($$eachFile)->memL; 
        $myCPU   = ($$eachFile)->mCPU;          
        $myCtime = ($$eachFile)->timeS;
        $mychain = ($$eachFile)->chOpt;
        @prt = split (" ", $myCtime);
    $cdate = $prt[0];  
    next if $myPath =~ /tfs_/;
    next if $myPath =~ /year_2a/;

   &printRow();

      }
 &endHtml();

 &StDbTJobsDisconnect();

#################
sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Status of Nightly Test Jobs for NEW library</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>Status of Nightly Test Jobs for NEW library</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log File Name</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Library Version</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Chain Option</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Job Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Number of Events<br>Done</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Memory Usage<br>for First Event</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Memory Usage<br>for Last Event </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>CPU per Event</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Create Date</B></TD>
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
<td>$myFile</td>
<td>$mylib</td>
<td>$mychain</td>
<td>$myJobS</td>
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
my $Date = '/bin/date';

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

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
