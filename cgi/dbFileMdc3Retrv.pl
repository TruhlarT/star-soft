#! /usr/local/bin/perl -w
#
#  $Id:
#
#  L. Didneko
#
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;

&cgiSetup();

my $set = $q->param("set");

my @spl = ();

@spl = split(" ",$set);

my $dtset = $spl[0];

&StDbProdConnect();

&beginHtml();

$sql="SELECT * FROM $FileCatalogT WHERE dataset = ? AND JobID LIKE '%mdc3%'";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($dtset);

my $counter = 0;
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
          <title>Production File Catalog</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
     <h3>set = $set </h3>
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"20%\" HEIGHT=50><B>jobID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>runID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>fileSeq</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>eventType</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>fName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>path</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>dataset</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>createTime</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>insertTime</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Nevents</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>NevLo</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>NevHi</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>owner</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>protection</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>type</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>component</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>format</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>site</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>hpss</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>status</B></TD>
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
<td>$pair{'eventType'}</td>
<td>$pair{'fName'}</td>
<td>$pair{'path'}</td>
<td>$pair{'dataset'}</td>
<td>$pair{'size'}</td>
<td>$pair{'createTime'}</td>
<td>$pair{'insertTime'}</td>
<td>$pair{'Nevents'}</td>
<td>$pair{'NevLo'}</td>
<td>$pair{'NevHi'}</td>
<td>$pair{'owner'}</td>
<td>$pair{'protection'}</td>
<td>$pair{'type'}</td>
<td>$pair{'component'}</td>
<td>$pair{'format'}</td>
<td>$pair{'site'}</td>
<td>$pair{'hpss'}</td>
<td>$pair{'status'}</td>
<td>$pair{'comment'}</td>
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
