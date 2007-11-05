#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbTodayMCQuery.pl  script to get browser of MC files updated today. 
#  L. Didneko
#
###############################################################################

use CGI;
use Mysql;
use Class::Struct;


require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my @prodPer = ("MDC4", "P01hd");
my $debugOn = 0;
my $thisDay = "000000";
my $thisday = 0;
my @dbFiles;
my $ndbFiles = 0;


struct FileAttr => {
        flname  => '$', 
         dtSet  => '$',
         fpath  => '$',
         timeS  => '$',
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

$thisDay = '01'.$thisday;

# print "Today Date :", $thisDay, "\n";

&StDbProdConnect();

&beginHtml();


$sql="SELECT dataset, path, fName, createTime FROM $FileCatalogT where insertTime like '$thisDay%' AND fName like '%dst.root' AND type = 'MC_reco' ";
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
 }
       $dbFiles[$ndbFiles] = $fObjAdr;
       $ndbFiles++; 
      
  }

my $myFile;
my $myDSet;
my $myCtime;
my $myPath;

 foreach $eachFile (@dbFiles) {

       $myFile  = ($$eachFile)->flname;
       $myDSet  = ($$eachFile)->dtSet;
       $myPath  = ($$eachFile)->fpath;
       $myCtime = ($$eachFile)->timeS;  

  &printRow();

     }
&endHtml();

&StDbProdDisconnect();

#################
sub beginHtml {

print <<END;
  <html>
   <head>
          <title>List of MC DST Files Inserted Today into FileCatalog</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>List of DST Files Inserted Today into FileCatalog</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=50><B>Dataset</B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=50><B>Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=50><B>Name of File</B></TD>
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
<td>$myDSet</td>
<td>$myFile</td>
<td>$myPath</td>
<td>$myCtime</td>
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
