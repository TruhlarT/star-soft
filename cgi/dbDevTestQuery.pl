#!/opt/star/bin/perl -w
#
# $Id: dbDevTestQuery.pl,v 1.2 2001/02/14 17:02:58 liuzx Exp $
#
# $Log: dbDevTestQuery.pl,v $
# Revision 1.2  2001/02/14 17:02:58  liuzx
# Form->action error modified!
#
# Revision 1.1  2001/02/14 16:59:37  liuzx
# Initial Version: query for nightly test in DEV library.
#                   (currently only last five days)
#
#
################################################################

use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $debugOn = 0;

my @prod_set = (
		"trs_redhat61/year_1h/hc_lowdensity",
		"trs_redhat61/year_1h/hc_standard",
		"trs_redhat61/year_1h/hc_highdensity",
		"trs_redhat61/year_1h/peripheral", 
		"trs_redhat61/year_2b/hc_lowdensity",
		"trs_redhat61/year_2b/hc_standard",
		"trs_redhat61/year_2b/hc_highdensity",
		"daq_redhat61/year_1h/minbias",
		"daq_redhat61/year_1h/central",
		);

my @sets_name;

my $kk = 0;
$sets_name[0] = "all";
for( $ll=0; $ll<scalar(@prod_set); $ll++) {
    $sets_name[$kk] = $prod_set[$ll] ;
    $kk++;
}  

my @myplot =   (
		"MemUsage",
                "CPU_per_Event",
		"RealTime_per_Event",
                "Average_NoTracks",
		"Average_NoPrimaryT",
                "Average_NoV0Vrt",
		"Average_NoXiVrt",
		"Average_NoKinKVrt"
                );   

$query = new CGI;

print $query->header;
print $query->start_html('Select Query for Production Plots');
print $query->startform(-action=>"dbDevTestQueryPlot.pl");  

print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

print "<body bgcolor=\"#ffdc9f\">\n";
print "<h1 align=center>Query for Nightly Test in DEV Library</h1>\n";

print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h3 align=center>Select Test</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'set1',
			     -values=>\@sets_name,
			     -size=>9);
print "</td><td>";
print "<h3 align=center> Select plot:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'plotVal',
			     -values=>\@myplot,
			     -size =>8); 

print "</td> </tr> </table><hr><center>";

print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:liuzx\@bnl.gov\">Zhixu Liu</a></address>\n";

#print $query->delete_all;
print $query->end_html;
