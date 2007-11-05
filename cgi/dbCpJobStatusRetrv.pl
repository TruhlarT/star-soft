#! /usr/local/bin/perl -w
#
#  $Id:
#
#  $Log: Wensheng Deng 
#  dbCpJobStatusRetrv.pl - script to retrive JobStatus table
#
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;

&cgiSetup();

&StDbProdConnect();

&beginHtml();

$sql="SELECT * FROM $JobStatusT";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;


while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;
    $pair{$fname} = $fvalue;
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
          <title>Jobs Status</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"20%\" HEIGHT=50><B>JobID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>prodSeries</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>jobfileName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>jobfileDir</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>sumFileName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>sumFileDir</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>jobStatus</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>NoEvents</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>mem_size_MB</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>CPU_per_evt_sec</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>avg_no_tracks</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>avg_no_vertex</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>chainName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>nodeID</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'JobID'}</td>
<td>$pair{'prodSeries'}</td>
<td>$pair{'jobfileName'}</td>
<td>$pair{'jobfileDir'}</td>
<td>$pair{'sumFileName'}</td>
<td>$pair{'sumFileDir'}</td>
<td>$pair{'jobStatus'}</td>
<td>$pair{'NoEvents'}</td>
<td>$pair{'mem_size_MB'}</td>
<td>$pair{'CPU_per_evt_sec'}</td>
<td>$pair{'avg_no_tracks'}</td>
<td>$pair{'avg_no_vertex'}</td>
<td>$pair{'chainName'}</td>
<td>$pair{'nodeID'}</td>
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
