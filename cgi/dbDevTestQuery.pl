#!/usr/bin/env perl 
#
# $Id: dbDevTestQuery.pl,v 1.58 2014/07/21 16:19:52 didenko Exp $
#
# $Log: dbDevTestQuery.pl,v $
# Revision 1.58  2014/07/21 16:19:52  didenko
# add auau 200GeV run 2014 production_low dataset for year 2014 with pxl chain
#
# Revision 1.57  2014/07/03 19:35:36  didenko
# remove simu directories
#
# Revision 1.56  2014/06/30 14:47:54  didenko
# add more run 2014 datasets for test
#
# Revision 1.55  2014/04/04 18:34:58  didenko
# add run 2014 datasample
#
# Revision 1.54  2013/08/02 14:12:06  didenko
# add simulation test
#
# Revision 1.53  2013/05/10 17:34:32  didenko
# added more embedding tests
#
# Revision 1.52  2013/04/12 19:43:53  didenko
# add pp 500GeV run2013 sample
#
# Revision 1.51  2012/05/23 17:45:05  didenko
# add cuAu200
#
# Revision 1.50  2012/05/18 18:13:44  didenko
# removed plots for tpt tracking
#
# Revision 1.49  2012/05/14 16:17:19  didenko
# comment unusable fields
#
# Revision 1.48  2012/04/24 16:00:48  didenko
# add UU test plots
#
# Revision 1.47  2012/04/02 15:29:16  didenko
# add pp 500GeV test
#
# Revision 1.46  2012/03/14 14:50:45  didenko
# add auau 200GeV year2011
#
# Revision 1.45  2012/03/09 16:03:26  didenko
# extand number of weeks
#
# Revision 1.44  2012/03/01 20:07:47  didenko
# added year 2012  real data and MC tests
#
# Revision 1.43  2011/07/15 19:38:22  didenko
# updated auau 27GeV data
#
# Revision 1.42  2011/05/13 17:49:16  didenko
#  year 2011 pp 500GeV MC test
#
# Revision 1.39  2011/03/07 19:28:24  didenko
# add pp 500GeV run 2011
#
# Revision 1.38  2010/12/03 16:16:33  didenko
# add embedding tests to plots
#
# Revision 1.37  2010/11/05 15:33:59  didenko
# reorder tests samples
#
# Revision 1.36  2010/11/05 15:19:42  didenko
# reorder tests samples
#
# Revision 1.34  2010/11/05 15:07:47  didenko
# add new MC tests and remove cucu200 HT
#
# Revision 1.33  2010/07/02 17:11:29  didenko
# updated for number of vertices
#
# Revision 1.32  2010/06/15 14:40:42  didenko
# added auau 11.5 GeV
#
# Revision 1.31  2010/06/14 16:51:37  didenko
# add auau 62GeV
#
# Revision 1.30  2010/05/25 17:36:41  didenko
# add more data 2010
#
# Revision 1.29  2010/02/02 19:37:32  didenko
# update for run 2010
#
# Revision 1.28  2009/12/10 18:43:24  didenko
# extanded test samples for pp pythia
#
# Revision 1.27  2009/11/18 20:55:18  didenko
# uncomment right line
#
# Revision 1.26  2009/11/18 20:49:48  didenko
# updated for changed tests
#
# Revision 1.25  2009/05/21 19:08:15  didenko
# updated for pp 200GeV run 2009 test
#
# Revision 1.24  2009/05/01 15:42:27  didenko
# fixed year 2009
#
# Revision 1.23  2009/04/01 15:54:52  didenko
# add pp 500GeV test
#
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
                "daq_sl302/year_2014/AuAu200_production_mid_2014",
                "daq_sl302/year_2014/AuAu200_production_low_2014",
                "daq_sl302/year_2014/AuHe3_production_2014",
                "daq_sl302/year_2014/AuAu200_production_2014",
                "daq_sl302/year_2014/production_15GeV_2014",
                "daq_sl302/year_2013/pp500_production_2013",
                "daq_sl302/year_2012/cuAu_production_2012",
                "daq_sl302/year_2012/UU_production_2012",
                "daq_sl302/year_2012/pp500_production_2012",
                "daq_sl302/year_2012/pp200_production_2012",
                "daq_sl302/year_2011/AuAu200_production",
                "daq_sl302/year_2011/AuAu27_production",
                "daq_sl302/year_2011/AuAu19_production",
                "daq_sl302/year_2011/pp500_production_2011",
                "daq_sl302/year_2011/pp500_embed",
                "daq_sl302/year_2011/AuAu200_embed",
                "daq_sl302/year_2010/auau200_production",
                "daq_sl302/year_2010/auau62_production",
                "daq_sl302/year_2010/auau39_production",
                "daq_sl302/year_2010/auau11_production", 
                "daq_sl302/year_2010/auau7_production",
                "daq_sl302/year_2010/auau200_embed",
                "daq_sl302/year_2010/auau39_embed",
                "daq_sl302/year_2010/auau11_embed", 
                "daq_sl302/year_2010/auau7_embed",
                "daq_sl302/year_2009/production2009_500GeV", 
                "daq_sl302/year_2009/production2009_200Gev_Hi",
                "daq_sl302/year_2009/pp200_embed",
                "daq_sl302/year_2008/production_dAu2008",
                "daq_sl302/year_2008/ppProduction2008", 
                "daq_sl302/year_2007/2007ProductionMinBias",
                "daq_sl302/year_2007/auau200_embedTpcSvtSsd",
                "daq_sl302/year_2006/ppProdLong",
                "daq_sl302/year_2006/ppProdTrans",
                "daq_sl302/year_2005/CuCu200_MinBias",
                "daq_sl302/year_2005/CuCu62_MinBias",
                "daq_sl302/year_2005/CuCu22_MinBias",
                "daq_sl302/year_2005/ppProduction",
                "daq_sl302/year_2005/CuCu200_embedTpc",
                "daq_sl302/year_2005/CuCu200_embedTpcSvtSsd",
                "daq_sl302/year_2004/AuAuMinBias",
                "daq_sl302/year_2004/AuAu_prodHigh",
                "daq_sl302/year_2004/AuAu_prodLow",
                "daq_sl302/year_2004/prodPP",
                "daq_sl302/year_2003/ppMinBias",
                "daq_sl302/year_2003/dAuMinBias",
		"daq_sl302/year_2001/minbias",
                "daq_sl302/year_2001/central",
                "daq_sl302/year_2001/ppMinBias",
                "daq_sl302/year_2000/minbias",
                "daq_sl302/year_2000/central",
                "trs_sl302/year_2012/pp500_minbias",
                "trs_sl302/year_2012/pp200_minbias",
                "trs_sl302/year_2012/CuAu200_minbias",
                "trs_sl302/year_2012/UU200_minbias",
                "trs_sl302/year_2011/auau200_central",
                "trs_sl302/year_2011/pp500_minbias",
                "trs_sl302/year_2011/pp500_pileup",
                "trs_sl302/year_2010/auau200_minbias",
                "trs_sl302/year_2010/auau62_minbias",
                "trs_sl302/year_2010/auau39_minbias",
                "trs_sl302/year_2010/auau11_minbias",
                "trs_sl302/year_2010/auau7_minbias",
                "trs_sl302/year_2009/pp200_minbias",
                "trs_sl302/year_2009/pp500_minbias",
                "trs_sl302/year_2008/dau200_minbias",
                "trs_sl302/year_2008/pp200_minbias",
                "trs_sl302/year_2007/auau200_central",
                "trs_sl302/year_2006/pp200_minbias",
                "trs_sl302/year_2005/cucu200_minbias",
                "trs_sl302/year_2005/cucu62_minbias",
                "trs_sl302/year_2004/auau_minbias",
                "trs_sl302/year_2004/auau_central", 
                "trs_sl302/year_2003/dau_minbias",
		"trs_sl302/year_2001/hc_standard",
                "trs_sl302/year_2001/pp_minbias",
                "trs_sl302/year_2000/hc_standard"
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
                "RealTime_per_CPU", 
                "Average_NoTracks",
		"Average_NoPrimaryT",
                "Average_NoTracksNfit15",
		"Average_NoPrimaryTNfit15",
                "Average_NoPrimVertex",
                "NoEvent_vertex",                 
                "Average_NoV0Vrt",
		"Average_NoXiVrt",
                "Percent_of_usableEvents",
                "Average_NoTracks_per_usableEvent",
#		"Average_NoPrimTrack_per_usableEvent",
                "Average_NoTracksNfit15_per_usableEvent",
#		"Average_NoPrimTrackNfit15_per_usableEvent",                 
#                "Average_NoV0_per_usableEvent",
#		"Average_NoXi_uper_sableEvent"                 
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
			 -values=>['1','2','3','4','5','6','7','8','9','10','12','13','14','15','16'],
			 -defaults=>1);
print "</h4>";

print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

#print $query->delete_all;
print $query->end_html;
exit 0;
