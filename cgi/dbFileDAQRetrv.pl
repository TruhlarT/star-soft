#! /usr/local/bin/perl -w
#
#  $Id:
#  dbFileDAQRetrv.pl 
#  L. Didneko
#  
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;
my @pck;
my $mcomment;
my $mstat;

&cgiSetup();

$runPr = $q->param("runD");
#$setN = $q->param("setD")

@pck = split ("%",$runPr);
$runN = $pck[0];
$setN = $pck[1]; 

&StDbProdConnect();

&beginHtml();
my $dirRun = "/home/starreco/reco/" . $setN;

$sql="SELECT * FROM $FileCatalogT WHERE runID = '$runN' AND jobID like '%$setN%' AND path like '%$setN%' AND fName like '%root' order by fileSeq ";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

my $counter = 0;

while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;
    $pair{$fname} = $fvalue;

   $mstat = $fvalue if( $fname eq 'dataStatus');   
   $mcomment = $fvalue if( $fname eq 'comment');
  }
  if ($mstat eq "OK"){$mcomment = "no"};
&printRow();

}

&endHtml();

&StDbProdDisconnect();

#################
sub beginHtml {

print <<END;
<html>
  <head>
          <title>Production File Catalog</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
     <h3>run = $runN </h3>
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"10%\" HEIGHT=50><B>jobID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>runID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>fileSeq</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>fName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>path</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>dataset</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>trigger</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>createTime</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Nevents</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>NevLo</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>NevHi</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>type</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>site</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>hpss</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>calib</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>dataStatus</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>comment</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'jobID'}</td>
<td>$pair{'runID'}</td>
<td>$pair{'fileSeq'}</td>
<td>$pair{'fName'}</td>
<td>$pair{'path'}</td>
<td>$pair{'dataset'}</td>
<td>$pair{'trigger'}</td>
<td>$pair{'size'}</td>
<td>$pair{'createTime'}</td>
<td>$pair{'Nevents'}</td>
<td>$pair{'NevLo'}</td>
<td>$pair{'NevHi'}</td>
<td>$pair{'type'}</td>
<td>$pair{'site'}</td>
<td>$pair{'hpss'}</td>
<td>$pair{'calib'}</td>
<td>$pair{'dataStatus'}</td>
<td>$mcomment</td>
</tr>
END

}

###############
sub endHtml {
my $Date = '/bin/date';

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Tue Set 10  05:29:25 MET 1999 -->
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
