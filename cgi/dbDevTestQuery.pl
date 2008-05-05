#!/usr/bin/env perl 
#
# $Id: dbDevTestQuery.pl,v 1.22 2008/05/05 17:07:33 didenko Exp $
#
# $Log: dbDevTestQuery.pl,v $
# Revision 1.22  2008/05/05 17:07:33  didenko
# updated datasets
#
# Revision 1.21  2008/03/31 18:46:49  didenko
# extended number of weeks one can query
#
# Revision 1.20  2008/03/31 18:36:09  didenko
# extended set of values to be queryed
#
# Revision 1.19  2008/01/09 21:07:42  didenko
# updated tests
#
# Revision 1.18  2006/04/14 16:20:12  didenko
# updated for tracks with nfit point > 15
#
# Revision 1.17  2005/10/04 14:42:20  didenko
# updated for cucu hijing and pp200 run 2005
#
# Revision 1.16  2005/05/05 21:21:31  didenko
# updated for CuCu data
#
# Revision 1.15  2004/12/20 20:56:35  didenko
# updated for SL3 platform
#
# Revision 1.14  2004/02/20 15:27:26  didenko
# updated for 2004 run test
#
# Revision 1.13  2004/02/16 04:13:49  jeromel
# Small modifs (modules would need to be also installed in OPTSTAR)
#
# Revision 1.12  2003/05/22 18:59:18  didenko
# updated test directories for year2003
#
# Revision 1.11  2002/04/12 19:32:39  didenko
# updated redhat72
#
# Revision 1.10  2002/01/30 15:08:54  didenko
# add new daq test
#
# Revision 1.8  2001/08/21 17:03:34  didenko
# update daq directory
#
# Revision 1.7  2001/07/10 20:14:36  didenko
# updated dataset
#
# Revision 1.6  2001/04/02 18:02:02  didenko
# update directories
#
# Revision 1.5  2001/02/23 00:37:48  liuzx
# .Add a random number as the action's parameter!
#
# Revision 1.4  2001/02/16 15:37:54  liuzx
# .Add select for weeks,(default 1, max 4)
#
# Revision 1.3  2001/02/15 18:13:15  liuzx
# Header Error modified!
#
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

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

my $debugOn = 0;

my $rand = rand(100);
my @prod_set = (
#		"trs_sl302/year_1h/hc_lowdensity",
		"trs_sl302/year_1h/hc_standard",
#		"trs_sl302/year_1h/hc_highdensity",
#		"trs_sl302/year_1h/peripheral", 
		"trs_sl302/year_2001/hc_lowdensity",
		"trs_sl302/year_2001/hc_standard",
		"trs_sl302/year_2001/hc_highdensity",
                "trs_sl302/year_2001/pp_minbias",
                "trs_sl302/year_2003/dau_minbias",
                "trs_sl302/year_2004/auau_minbias",
                "trs_sl302/year_2004/auau_central", 
                "trs_sl302/year_2005/cucu200_minbias",
                "trs_sl302/year_2005/cucu62_minbias",
                "trs_sl302/year_2007/auau200_central",
		"daq_sl302/year_2001/minbias",
                "daq_sl302/year_2001/central",
                "daq_sl302/year_2001/ppMinBias",
                "daq_sl302/year_2003/ppMinBias",
                "daq_sl302/year_2003/dAuMinBias",
                "daq_sl302/year_2004/AuAuMinBias",
                "daq_sl302/year_2004/AuAu_prodHigh",
                "daq_sl302/year_2004/AuAu_prodLow",
                "daq_sl302/year_2004/prodPP",
                "daq_sl302/year_2005/CuCu200_HighTower",
                "daq_sl302/year_2005/CuCu200_MinBias",
                "daq_sl302/year_2005/CuCu62_MinBias",
                "daq_sl302/year_2005/CuCu22_MinBias",
                "daq_sl302/year_2005/ppProduction",
                "daq_sl302/year_2006/ppProdLong",
                "daq_sl302/year_2006/ppProdTrans",
                "daq_sl302/year_2007/2007ProductionMinBias",
                "daq_sl302/year_2008/production_dAu2008",
                "daq_sl302/year_2008/ppProduction2008", 
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
                "Average_NoTracksNfit15",
		"Average_NoPrimaryTNfit15",                 
                "Average_NoV0Vrt",
		"Average_NoXiVrt",
		"Average_NoKinKVrt",
                "Percent_of_usableEvents",
                "Average_NoTracks_per_usableEvent",
		"Average_NoPrimTrack_per_usableEvent",
                "Average_NoTracksNfit15_per_usableEvent",
		"Average_NoPrimTrackNfit15_per_usableEvent",                 
                "Average_NoV0_per_usableEvent",
		"Average_NoXi_uper_sableEvent",
		"Average_NoKink_per_usableEvent",                 
                
                );   

$query = new CGI;

print $query->header;
print $query->start_html('Query for Nightly Test in DEV Library');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"dbDevTestQueryPlot.pl?rand=$rand");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Query for Nightly Test in DEV Library</u></h1>\n";

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
			     -size=>8);
print "</td><td>";
print "<h3 align=center> Select plot:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'plotVal',
			     -values=>\@myplot,
			     -size =>8); 
print "</td> </tr> </table><hr><center>";

print "<h4 align=center> How many weeks do you want to show: ";
print $query->popup_menu(-name=>'weeks',
			 -values=>['1','2','3','4','5','6','7','8'],
			 -defaults=>1);
print "</h4>";

print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

#print $query->delete_all;
print $query->end_html;
exit 0;
