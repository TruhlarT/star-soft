#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbTodayQuery.pl  script to get browser of files updated today. 
#  L. Didneko
#
###############################################################################

use CGI;
use Mysql;
use Class::Struct;


require "/afs/rhic.bnl.gov/star/packages/scripts/dbCpProdSetup.pl";

my $prodPer = "P01gl";
my $debugOn = 0;
my $thisDay = "000000";
my $thisday = 0;
my @dbFiles;
my $ndbFiles = 0;

struct FileAttr => {
        flname  => '$', 
         dtSet  => '$',
         timeS  => '$',
         Nevts  => '$',
         dataSt => '$',
          fpath => '$',
          trig  => '$',
          com   => '$'
		  };

&cgiSetup();

$now = localtime;
($sec,$min,$hour,$mday,$mon,$year) = localtime;

 $mon += 1;
  if ($mday < 10) {
  $mday = '0'.$mday;
 } 
  if ($mon < 10) {
  $mon = '0'.$mon;
 }   
  $thisday = $mon . $mday;

$thisDay = '02'.$thisday;

# print "Today Date :", $thisDay, "\n";

&StDbProdConnect();

&beginHtml();


$sql="SELECT dataset, path, fName, createTime, Nevents, trigger, dataStatus, comment FROM $FileCatalogT where insertTime like '$thisDay%' AND fName like '%.event.root' AND type = 'daq_reco' AND site = 'disk_rcf' ORDER BY runID, fileSeq ";
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
#    print "$fname = $fvalue\n" ;

    ($$fObjAdr)->dtSet($fvalue)   if($fname eq 'dataset'); 
    ($$fObjAdr)->flname($fvalue)  if($fname eq 'fName');
    ($$fObjAdr)->fpath($fvalue)   if($fname eq 'path');
    ($$fObjAdr)->timeS($fvalue)   if($fname eq 'createTime');
    ($$fObjAdr)->Nevts($fvalue)   if($fname eq 'Nevents');
    ($$fObjAdr)->dataSt($fvalue)  if($fname eq 'dataStatus'); 
    ($$fObjAdr)->trig($fvalue)    if($fname eq 'trigger');
    ($$fObjAdr)->com($fvalue)    if($fname eq 'comment');  
}
       $dbFiles[$ndbFiles] = $fObjAdr;
       $ndbFiles++; 
      
  }

my $myFile;
my $myDSet;
my $myCtime;
my $myPath;
my $myEvts;
my $myDataSt;
my $myTrig;
my $myCom;

 foreach $eachFile (@dbFiles) {

       $myFile  = ($$eachFile)->flname;
       $myDSet  = ($$eachFile)->dtSet;
       $myPath  = ($$eachFile)->fpath;
       $myCtime = ($$eachFile)->timeS;  
       $myEvts  = ($$eachFile)->Nevts;
       $myDataSt = ($$eachFile)->dataSt;
       $myTrig  = ($$eachFile)->trig;
       $myCom   = ($$eachFile)->com;
       if($myDataSt eq "notOK")  {
         $myDataSt = $myCom;
       }

  &printRow();

     }
&endHtml();

&StDbProdDisconnect();

#################
sub beginHtml {

print <<END;
  <html>
   <head>
          <title>List of DST Files Inserted Today into FileCatalog</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>List of DST Files Inserted Today into FileCatalog</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=30><B>Dataset</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=30><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=30><B>Trigger</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=20><B>Name of File</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=20><B>Create Date</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=20><B>Number of Events</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=20><B>Data Status</B></TD>
</TR> 
   </head>
    <body>
END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$myDSet</td>
<td>$myPath</td>
<td>$myTrig</td>
<td>$myFile</td>
<td>$myCtime</td>
<td>$myEvts</td>
<td>$myDataSt</td>
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
