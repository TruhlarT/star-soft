#!/usr/bin/env perl
#
#  $Id:
#
#  dbProdOptionRetrv.pl - script to retrive Production Option table
#
###############################################################################

use CGI;

require "/afs/rhic/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;

my $chain;

&cgiSetup();

&StDbProdConnect();

&beginHtml();

$sql="SELECT * FROM $ProdOptionsT ORDER BY id DESC ";
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
    $chain = $fvalue  if( $fname eq 'chainOpt');
  }
    if($chain =~ /ITTF/) {
   
 &printRow();

}else{
  &printRoww();
  }
 }

&endHtml();

&StDbProdDisconnect();

#################
sub beginHtml {

print <<END;
<html>
  <head>
          <title>Production Options</title>
  </head>
  <body BGCOLOR=\"cornsilk\"> 
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"5%\" HEIGHT=50><B>Production Series</B></TD>
<TD WIDTH=\"5%\" HEIGHT=50><B>Event Type</B></TD>
<TD WIDTH=\"5%\" HEIGHT=50><B>Library Version</B></TD>
<TD WIDTH=\"5%\" HEIGHT=50><B>Geometry</B></TD>
<TD WIDTH=\"40%\" HEIGHT=50><B>Chain Option</B></TD>
<TD WIDTH=\"40%\" HEIGHT=50><B>Production</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'prodSeries'}</td>
<td>$pair{'eventType'}</td>
<td>$pair{'libVersion'}</td>
<td>$pair{'geometry'}</td>
<td>$pair{'chainOpt'}</td>
<td>$pair{'comment'}</td>
</tr>
END

}

###############
sub printRoww {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'prodSeries'}</td>
<td>$pair{'eventType'}</td>
<td>$pair{'libVersion'}</td>
<td>$pair{'geometry'}</td>
<td>$pair{'chainOpt'}</td>
<td>$pair{'comment'}</td>
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
