#! /opt/star/bin/perl -w
#
#  $Id:
#
#  dbTodayNFCQuery.pl  script to get browser of nightly test files updated today. 
#  L. Didneko
#
###############################################################################

use CGI;
use Mysql;
use Class::Struct;


require "/afs/rhic/star/packages/DEV00/mgr/dbTJobsSetup.pl";

my $TOP_DIRD = "/star/rcf/test/dev/";
my @dir_year = ("year_1h", "year_2b");
my @node_dir = ("trs_redhat61","trs_redhat61_opt","daq_redhat61", "daq_redhat61_opt" ); 
my @hc_dir = ("hc_lowdensity", "hc_standard", "hc_highdensity", "peripheral", "minbias","central");

my @OUT_DIR;
my @OUTD_DIR;
my @Nday = ("Mon","Tue","Wed","Thu","Fri");


my %dayHash = (
                 "Mon" => 1,
                 "Tue" => 2, 
                 "Wed" => 3, 
                 "Thu" => 4, 
                 "Fri" => 5, 
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
         fpath  => '$',
         timeS  => '$',
         noEvtD => '$',
         noEvtS => '$', 
		  };

&cgiSetup();


($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    $thisday = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

  my $ii = 0;
 
  my $iday;
  my $testDay;
  my $beforeDay;
  $iday = $dayHash{$thisday}; 
  if($thisday eq "Mon") {
  $testDay = "Fri";
 }else{
 $testDay = $Nday[$iday - 2];
 } 
 if($thisday eq "Sat" or $thisday eq "Sun" ){
 $testDay = "Fri";
 } 

# print "Today Date :", $thisDay, "\n";

&StDbTJobsConnect();

 &beginHtml();


$sql="SELECT path, fName, NoEventDone, NoEventSkip, createTime FROM $FilesCatalogT where path LIKE '%$testDay%' AND path like '%redhat61%' AND avail = 'Y'";
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
     ($$fObjAdr)->flname($fvalue)  if($fname eq 'fName');
     ($$fObjAdr)->noEvtD($fvalue)  if($fname eq 'NoEventDone');
     ($$fObjAdr)->noEvtS($fvalue)  if($fname eq 'NoEventSkip'); 
     ($$fObjAdr)->timeS($fvalue)   if($fname eq 'createTime');
  }
        $dbFiles[$ndbFiles] = $fObjAdr;
        $ndbFiles++; 
      
   }

 my $myFile;
 my $myPath;
 my $myEvtD;
 my $myEvtS;
 my $myCtime;

  foreach $eachFile (@dbFiles) {

        $myFile  = ($$eachFile)->flname;
        $myPath  = ($$eachFile)->fpath;
        $myEvtD  = ($$eachFile)->noEvtD;
        $myEvtS  = ($$eachFile)->noEvtS; 
        $myCtime = ($$eachFile)->timeS;  
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
          <title>List of Files Inserted into FileCatalog Today</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>List of Nightly Test Reco Files Produced Last Night</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Name of File</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Number of Events<br>Done</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Number of Events<br>Skiped</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Create Date</B></TD>
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
<td>$myEvtD</td>
<td>$myEvtS</td>
<td>$myCtime</td>
</TR>
END

}

###############
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

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
