#!/usr/bin/env perl 
#
# $Id: CRSstatusQuery.pl,v  2005/10/04 14:42:20 didenko 
#
# $Log: CRSstatusQuery.pl,v 
#
#
################################################################

use CGI;
 
BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCRSSetup.pl";

my $debugOn = 0;

my $rand = rand(100);

my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months");

$query = new CGI;

print $query->header;
print $query->start_html('CRS farm status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"CRSfarmStatus.pl?rand=$rand");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS farm status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";
print "<h3 align=center> Select period of monitoring</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'period',
			     -values=>\@reqperiod,
                             -default=>day,
			     -size =>1); 

print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

#print $query->delete_all;
print $query->end_html;
exit 0;
