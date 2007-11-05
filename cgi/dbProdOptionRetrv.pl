#!/usr/bin/env perl
#
#  $Id:
#
#  dbProdOptionRetrv.pl - script to retrive Production Option table
#
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;

my $chain;
my $chainline;

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
    $chainline =  $chain;
    $chainline =~ s/,/ /g; 

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
<TABLE WIDTH=100% BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TH WIDTH=\"5%\" HEIGHT=100><h3>Production Series</h3></TH>
<TH WIDTH=\"5%\" HEIGHT=100><h3>Event Type</h3></TH>
<TH WIDTH=\"5%\" HEIGHT=100><h3>Library Version</h3></TH>
<TH WIDTH=\"5%\" HEIGHT=100><h3>Geometry</h3></TH>
<TH WIDTH=\"50%\" HEIGHT=100><h3>Chain Options</h3></TH>
<TH WIDTH=\"30%\" HEIGHT=100><h3>Production <br> description</h3></TH>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER VALIGN=CENTER>
<th WIDTH=5%>$pair{'prodSeries'}</th>
<th WIDTH=5%>$pair{'eventType'}</th>
<th WIDTH=5%>$pair{'libVersion'}</th>
<th WIDTH=5%>$pair{'geometry'}</th>
<th WIDTH=50%> $chainline</th>
<th WIDTH=30%> $pair{'comment'}</th>
</tr>
END

}

###############
sub printRoww {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<th WIDTH=5%>$pair{'prodSeries'}</th>
<th WIDTH=5%>$pair{'eventType'}</th>
<th WIDTH=5%>$pair{'libVersion'}</th>
<th WIDTH=5%>$pair{'geometry'}</th>
<th WIDTH=50%>$chainline</th>
<th WIDTH=30%>$pair{'comment'}</th>
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
