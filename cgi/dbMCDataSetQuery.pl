#!/usr/local/bin/perl -w
#
# dbMCDatSetQuery.pl
#
################################################################

use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $debugOn = 0;

my @collision = ( "all","auau100", "auau200", "auau130", "auau128", "augas100", "pau200", "pp200","dAu200");
my @evtGen  = ("all","hijing", "hijet", "mevsim", "venus", "nexus", "vni", "two_photon", "hbt", "rqmd", "single", "starlight", "strongcp", "pythia", "hemicosm");

my @geoYear = ("all","year_1b", "year_1h", "year_1e", "year_1s", "complete", "year_1a", "year1a", "year2001", "year2003", "year_2a", "year2a");

my @ftype = ("fzd","root");

$query = new CGI;

print $query->header;
print $query->start_html('dbMCDataSetQuery');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"dbMCList.pl");  

print "<body bgcolor=\"#ffdc9f\">\n";
print "<h1 align=center>Query for MC Datasets</h1>\n";

print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h3 align=center>Select Collision:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'setC',
			     -values=>\@collision,
			     -size=>8);
print "</td><td>";
print "<h3 align=center> Select Event Generator:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'evGen',
			     -values=>\@evtGen,
			     -size =>8); 
print "</td><td>";
print "<h3 align=center> Select Geometry:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'gYear',
			     -values=>\@geoYear,
			     -size =>8); 

print "</td><td>";
print "<h3 align=center> Select format:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'fform',
			     -values=>\@ftype,
			     -size =>8); 

print "</td> </tr> </table><hr><center>";

print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

#print $query->delete_all;
print $query->end_html;
