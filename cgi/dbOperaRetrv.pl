#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
#
######################################################################
#
# dbOperaRetrv.pl
#
# Wensheng Deng 9/99
#
# Retrieve operation table in database by set name and present to the web
# 
# Usage: dbOperaRetrv.pl
#
use CGI;

require "dbOperaSetup.pl";

my $debugOn = 0;
my %pair;

&cgiSetup();

$set = $q->param("set");

&StDbOperaConnect();

&beginHtml();

$sql="SELECT * FROM $OperationT WHERE SetName = '$set'";
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

&StDbOperaDisconnect();

#################
sub beginHtml {

print <<END;
<html>
  <head>
          <title>set name query</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
      <h3>set = $set </h3>
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"20%\" HEIGHT=50><B>GeantFile</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Geant_size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Produced_date</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Chain</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>JobStatus</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>EventsDone</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Disk_dst_date</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Disk_dst_size<br>(MB)</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Disk_hist_date</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Disk_hist_size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>HPSS_dst_date</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>HPSS_dst_size<br>(MB)</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>HPSS_hist_date</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>HPSS_hist_size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Sum_File</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Jobfile</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Lib_tag</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Mem_size<br>(MB)</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>CPU_per_event<br>(secend)</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Ave_No_Tracks</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Ave_No_Vtx</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'GeantFile'}</td>
<td>$pair{'Geant_size'}</td>
<td>$pair{'Produced_date'}</td>
<td>$pair{'Chain'}</td>
<td>$pair{'JobStatus'}</td>
<td>$pair{'EventsDone'}</td>
<td>$pair{'Disk_dst_date'}</td>
<td>$pair{'Disk_dst_size'}</td>
<td>$pair{'Disk_hist_date'}</td>
<td>$pair{'Disk_hist_size'}</td>
<td>$pair{'HPSS_dst_date'}</td>
<td>$pair{'HPSS_dst_size'}</td>
<td>$pair{'HPSS_hist_date'}</td>
<td>$pair{'HPSS_hist_size'}</td>
<td>$pair{'Sum_File'}</td>
<td>$pair{'Jobfile'}</td>
<td>$pair{'Lib_tag'}</td>
<td>$pair{'Mem_size_MB'}</td>
<td>$pair{'CPU_per_evt_sec'}</td>
<td>$pair{'Ave_No_Tracks'}</td>
<td>$pair{'Ave_No_Vtx'}</td>
</tr>
END

}

###############
sub endHtml {
my $Date = `date`;

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
