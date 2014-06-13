#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# NewLibPlots.pl cgi to make plots for NEW library tests on sites
#
################################################################

use CGI;

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
#use Mysql;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";

# Tables

$JobStatusT = "siteJobStatus";

my $debugOn = 0;
my @data = ();
my @legend = ();

my @prod_set = (
                "daq_ittf/year_2014/AuAu200_production_mid_2014",
                "daq_ittf/year_2014/AuAu200_production_2014",
                "daq_ittf/year_2014/production_15GeV_2014",
                "daq_ittf/year_2013/pp500_production_2013",   
                "daq_ittf/year_2012/UU_production_2012", 
                "daq_ittf/year_2012/cuAu_production_2012",   
                "daq_ittf/year_2012/pp500_production_2012",     
                "daq_ittf/year_2012/pp200_production_2012",
                "daq_ittf/year_2012/pp200_embed",
                "daq_ittf/year_2012/UU193_embed",                
                "daq_ittf/year_2011/AuAu200_production",
                "daq_ittf/year_2011/AuAu27_production",
                "daq_ittf/year_2011/AuAu19_production", 
                "daq_ittf/year_2011/pp500_production_2011",
                "daq_ittf/year_2011/pp500_embed",
                "daq_ittf/year_2011/AuAu200_embed",
                "daq_ittf/year_2010/auau200_production",
                "daq_ittf/year_2010/auau62_production",
                "daq_ittf/year_2010/auau39_production",
                "daq_ittf/year_2010/auau11_production",
                "daq_ittf/year_2010/auau7_production",
                "daq_ittf/year_2010/auau200_embed",
                "daq_ittf/year_2010/auau39_embed",
                "daq_ittf/year_2010/auau11_embed",
                "daq_ittf/year_2010/auau7_embed",
                "daq_ittf/year_2009/production2009_500GeV",
                "daq_ittf/year_2009/production2009_200Gev_Hi",
                "daq_ittf/year_2009/pp200_embed",
                "daq_ittf/year_2008/production_dAu2008",
                "daq_ittf/year_2008/ppProduction2008",
                "daq_ittf/year_2007/2007ProductionMinBias",
                "daq_ittf/year_2007/2007Production",
                "daq_ittf/year_2007/auau200_embedTpcSvtSsd",
                "daq_ittf/year_2006/ppProdLong",
                "daq_ittf/year_2006/ppProdTrans",
                "daq_ittf/year_2005/CuCu200_MinBias",
                "daq_ittf/year_2005/CuCu62_MinBias",
                "daq_ittf/year_2005/CuCu22_MinBias",
                "daq_ittf/year_2005/CuCu200_embedTpc",
                "daq_ittf/year_2005/CuCu200_embedTpcSvtSsd",
                "daq_ittf/year_2005/ppProduction",
                "daq_ittf/year_2004/AuAuMinBias",
                "daq_ittf/year_2004/AuAu_prodHigh",
                "daq_ittf/year_2004/AuAu_prodLow",
                "daq_ittf/year_2004/prodPP",
                "daq_ittf/year_2003/ppMinBias",
                "daq_ittf/year_2003/dAuMinBias",
                "daq_ittf/year_2001/minbias",
                "daq_ittf/year_2001/central",
                "daq_ittf/year_2001/ppMinBias",
                "daq_ittf/year_2000/minbias",
                "daq_ittf/year_2000/central",
                "trs_ittf/year_2012/pp500_minbias",
                "trs_ittf/year_2012/pp200_minbias",
                "trs_ittf/year_2012/CuAu200_minbias",
                "trs_ittf/year_2012/UU200_minbias",
                "trs_ittf/year_2011/auau200_central",
                "trs_ittf/year_2011/pp500_minbias",
                "trs_ittf/year_2011/pp500_pileup",
                "trs_ittf/year_2010/auau200_minbias",
                "trs_ittf/year_2010/auau62_minbias",
                "trs_ittf/year_2010/auau39_minbias",
                "trs_ittf/year_2010/auau11_minbias",
                "trs_ittf/year_2010/auau7_minbias",
                "trs_ittf/year_2009/pp200_minbias",
                "trs_ittf/year_2009/pp500_minbias",
                "trs_ittf/year_2008/dau200_minbias",
                "trs_ittf/year_2008/pp200_minbias",
                "trs_ittf/year_2007/auau200_central",
                "trs_ittf/year_2006/pp200_minbias",
                "trs_ittf/year_2005/cucu200_minbias",
                "trs_ittf/year_2005/cucu62_minbias",
                "trs_ittf/year_2004/auau_minbias",
                "trs_ittf/year_2004/auau_central",
                "trs_ittf/year_2003/dau_minbias",
                "trs_ittf/year_2001/hc_standard",
                "trs_ittf/year_2001/pp_minbias",
                "trs_ittf/year_2000/hc_standard"
		);


my @myplot =   (
		"MemUsage",
                "CPU_per_Event",
		"RealTime_per_Event",
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
		"Average_NoPrimTrack_per_usableEvent",
                "Average_NoTracksNfit15_per_usableEvent",
		"Average_NoPrimTrackNfit15_per_usableEvent",                 
                "Average_NoV0_per_usableEvent",
		"Average_NoXi_uper_sableEvent",
                  );   


my %plotHash = (
                MemUsage => 'memUsageF, memUsageL',
                CPU_per_Event => 'CPU_per_evt_sec',
                RealTime_per_Event => 'RealTime_per_evt',
                Average_NoTracks => 'avg_no_tracks',
                Average_NoPrimaryT => 'avg_no_primaryT',
                Average_NoTracksNfit15 => 'avg_no_tracksnfit15',
                Average_NoPrimaryTNfit15  => 'avg_no_primaryTnfit15',
                Average_NoPrimVertex => 'avgNoVtx_evt',
                NoEvent_vertex => 'NoEventVtx',
                Average_NoV0Vrt => 'avg_no_V0Vrt',
                Average_NoXiVrt => 'avg_no_XiVrt',
                Percent_of_usableEvents => 'percent_of_usable_evt',
                Average_NoTracks_per_usableEvent => 'avgNoTrack_usbevt',
#                Average_NoPrimTrack_per_usableEvent => 'avgNoPrTrack_1vtx_usbevt',
                Average_NoTracksNfit15_per_usableEvent => 'avgNoTrackNfit15_usbevt',
#                Average_NoPrimTrackNfit15_per_usableEvent => 'avgNoPrTrackNfit15_1vtx_usbevt',
#                Average_NoV0_per_usableEvent => 'avgNoV0_usbevt',
#                Average_NoXi_per_sableEvent => 'avgNoXi_usbevt',
               );


my @libtag = ();

my @plotvaldg = ();
my @plotvalop = ();
my @plotvalvmcdg = ();
my @plotvalvmcop = ();

my @plotvalpdsf = ();
my $npt = 0;
my $nl = 0;

my @plotmemfstpdsf = ();
my @plotmemlstpdsf = ();
my @plotmemfsto = ();
my @plotmemlsto = ();
my @plotmemfstd = ();
my @plotmemlstd = ();

my @plotmemvmcfsto = ();
my @plotmemvmclsto = ();
my @plotmemvmcfstd = ();
my @plotmemvmclstd = ();

my $min_y = 0;
my $max_y = 5000;
my $maxval = 0;
my $minVal = 0;
my @arsite = ("rcf","pdsf","kisti");

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $tset    = $query->param('sets');
my $plotVal = $query->param('plotVal');

  if( $tset eq "" and $plotVal eq "" ) {

print $query->header();
print $query->start_html('Plots for Nightly Test in NEW Library');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Plots for NEW libraries validation tests</u></h1>\n";

print "<br>";
print "<br>";
print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h3 align=center>Select Test</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'sets',
			     -values=>\@prod_set,
			     -size=>10);
print "</td><td>";
print "<h3 align=center> Select plot:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'plotVal',
			     -values=>\@myplot,
			     -size =>10); 

print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit(),"<p>";
print $query->reset();
print $query->endform();
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html();

  }else{

my $qqr = new CGI;

my $tset    =  $qqr->param('sets');
my $plotVal =  $qqr->param('plotVal');
my $tyear;


$JobStatusT = "siteJobStatus";

($sec,$min,$hour,$mday,$mon,$year) = localtime();


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".($mon+1)."-".$mday." ".$hour.":".$min.":".$sec ;

#my $day_diff = 366;

my $day_diff = 456;

my $tyear = $year+1900;

my $dyear = $tyear - 2000 ;

if( $dyear < 10 ) {$dyear = '0'.$dyear};

my $ylib = "SL"."$dyear%";
my @spl = ();
@spl = split(" ",$plotVal);
my $plotVl = $spl[0];

my $mplotVal = $plotHash{$plotVl};

  &StDbTJobsConnect();

my $path;
my $pth;
my $dpth;
my $tpath;
my $agmlpath;
my $agml;

 @spl = ();
 @spl = split(" ", $tset);
 $pth = $spl[0];
 @spl = ();
 @spl = split("/", $pth);
 $path = $spl[1]."/". $spl[2];
 $agml = $spl[1].".AgML"."/". $spl[2] ;
 $tpath = $spl[0]; 
 @spl = ();
 @spl = split("_", $tpath);
 $dpth = $spl[0];
 


 my $qupath = "%new/".$dpth."%/".$path;
 $agmlpath = "%new/".$dpth."%/".$agml;

@plotvaldg = ();
@plotvalop = ();
@plotvalpdsf = ();
@plotvalvmcdg = ();
@plotvalvmcop = ();
@plotvalkisti = ();

@libtag = ();

$npt = 0;
$nl = 0;

@plotmemfsto = ();
@plotmemlsto = ();
@plotmemfstd = ();
@plotmemlstd = ();
@plotmemvmcfsto = ();
@plotmemvmclsto = ();
@plotmemvmcfstd = ();
@plotmemvmclstd = ();
@plotmemfstpdsf = ();
@plotmemlstpdsf = ();
@plotmemfstkisti = ();
@plotmemlstkisti = ();


$min_y = 1;
$max_y = 1000;
$maxval = 0;
$minval = 100000;

    $sql="SELECT distinct LibTag  FROM $JobStatusT WHERE site = 'rcf' AND path LIKE ? AND  (TO_DAYS(\"$todate\") - TO_DAYS(createTime)) <= $day_diff ORDER by createTime ";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($qupath);

       while( $mlib = $cursor->fetchrow() ) {
          $libtag[$nl] = $mlib;
          $nl++;
       }
    $cursor->finish();

for ($npt = 0; $npt<scalar(@libtag); $npt++)  {
  

    $sql="SELECT path, $mplotVal, site, createTime  FROM $JobStatusT WHERE path LIKE ?  AND LibTag = '$libtag[$npt]' AND jobStatus= 'Done' AND  (TO_DAYS(\"$todate\") - TO_DAYS(createTime)) <= $day_diff ORDER by createTime";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($qupath);

        while(@fields = $cursor->fetchrow_array) {

            if ($fields[2] eq "pdsf" or $fields[3] eq "pdsf") {
          
             if ($plotVal eq "MemUsage") {
                $plotmemfstpdsf[$npt] = $fields[1];
                $plotmemlstpdsf[$npt] = $fields[2];
                if( $plotmemlstpdsf[$npt] >= $maxval) {
		    $maxval =  $plotmemlstpdsf[$npt];
                  }
	        if( $plotmemfstpdsf[$npt] >= 0 and $plotmemfstpdsf[$npt] <= $minval ) {
		  $minval =  $plotmemfstpdsf[$npt];
	          }
	   }else{
		$plotvalpdsf[$npt] = $fields[1];
		if( $plotvalpdsf[$npt] >= $maxval) {
		    $maxval =  $plotvalpdsf[$npt];
                  }
	        if( $plotvalpdsf[$npt] >=0 and $plotvalpdsf[$npt] <= $minval ) {
		  $minval =  $plotvalpdsf[$npt];
	          }
	       }
           }elsif ($fields[2] eq "kisti" or $fields[3] eq "kisti") {
          
             if ($plotVal eq "MemUsage") {
                $plotmemfstkisti[$npt] = $fields[1];
                $plotmemlstkisti[$npt] = $fields[2];
                if( $plotmemlstkisti[$npt] >= $maxval) {
		    $maxval =  $plotmemlstkisti[$npt];
                  }
	        if( $plotmemfstkisti[$npt] >= 0 and $plotmemfstkisti[$npt] <= $minval ) {
		  $minval =  $plotmemfstkisti[$npt];
	          }
	   }else{
		$plotvalkisti[$npt] = $fields[1];
		if( $plotvalkisti[$npt] >= $maxval) {
		    $maxval =  $plotvalkisti[$npt];
                  }
	        if( $plotvalkisti[$npt] >=0 and $plotvalkisti[$npt] <= $minval ) {
		  $minval =  $plotvalkisti[$npt];
	          }
	       }

	   }elsif($fields[2] eq "rcf" or $fields[3] eq "rcf") {

            if ($fields[0] =~ /sl302.ittf_opt/) {
              if ($plotVal eq "MemUsage") {
                $plotmemfsto[$npt] = $fields[1];
                $plotmemlsto[$npt] = $fields[2];
                if( $plotmemlsto[$npt] >= $maxval) {
		    $maxval =  $plotmemlsto[$npt];
                  }
	        if( $plotmemfsto[$npt] >= 0 and $plotmemfsto[$npt] <= $minval ) {
		  $minval =  $plotmemfsto[$npt];
	          }
	   }else{
		$plotvalop[$npt] = $fields[1];
		if( $plotvalop[$npt] >= $maxval) {
		    $maxval =  $plotvalop[$npt];
                  }
	        if( $plotvalop[$npt] >=0 and $plotvalop[$npt] <= $minval ) {
		  $minval =  $plotvalop[$npt];
	          }
	       }
	    }else{                
              if ($plotVal eq "MemUsage") {
                $plotmemfstd[$npt] = $fields[1];
                $plotmemlstd[$npt] = $fields[2];
		if( $plotmemlstd[$npt] >= $maxval) {
		    $maxval =  $plotmemlstd[$npt];
                  }
	        if( $plotmemfstd[$npt] >= 0 and $plotmemfstd[$npt]  <= $minval ) {
		  $minval =  $plotmemfstd[$npt];
	          }
	   }else{
 		$plotvaldg[$npt] = $fields[1];
                if( $plotvaldg[$npt] >= $maxval) {
		    $maxval =  $plotvaldg[$npt];
                  }
	        if( $plotvaldg[$npt] >= 0 and $plotvaldg[$npt] <= $minval ) {
		  $minval =  $plotvaldg[$npt];
	          }
            }
	  }
     	 }
	}
############

    $sql="SELECT path, $mplotVal, site, createTime  FROM $JobStatusT WHERE path LIKE ?  AND LibTag = '$libtag[$npt]' AND jobStatus= 'Done' AND  (TO_DAYS(\"$todate\") - TO_DAYS(createTime)) <= $day_diff ORDER by createTime";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($agmlpath);

        while(@fields = $cursor->fetchrow_array) {

	    if($fields[2] eq "rcf" or $fields[3] eq "rcf") {

            if ($fields[0] =~ /sl302.ittf_opt/) {
              if ($plotVal eq "MemUsage") {
                $plotmemvmcfsto[$npt] = $fields[1];
                $plotmemvmclsto[$npt] = $fields[2];
                if( $plotmemvmclsto[$npt] >= $maxval) {
		    $maxval =  $plotmemvmclsto[$npt];
                  }
	        if( $plotmemvmcfsto[$npt] >= 0 and $plotmemvmcfsto[$npt] <= $minval ) {
		  $minval =  $plotmemvmcfsto[$npt];
	          }
	   }else{
		$plotvalvmcop[$npt] = $fields[1];
		if( $plotvalvmcop[$npt] >= $maxval) {
		    $maxval =  $plotvalvmcop[$npt];
                  }
	        if( $plotvalvmcop[$npt] >=0 and $plotvalvmcop[$npt] <= $minval ) {
		  $minval =  $plotvalvmcop[$npt];
	          }
	       }
	    }else{                
              if ($plotVal eq "MemUsage") {
                $plotmemvmcfstd[$npt] = $fields[1];
                $plotmemvmclstd[$npt] = $fields[2];
		if( $plotmemvmclstd[$npt] >= $maxval) {
		    $maxval =  $plotmemvmclstd[$npt];
                  }
	        if( $plotmemvmcfstd[$npt] >= 0 and $plotmemvmcfstd[$npt]  <= $minval ) {
		  $minval =  $plotmemvmcfstd[$npt];
	          }
	   }else{
 		$plotvaldg[$npt] = $fields[1];
                if( $plotvalvmcdg[$npt] >= $maxval) {
		    $maxval =  $plotvalvmcdg[$npt];
                  }
	        if( $plotvalvmcdg[$npt] >= 0 and $plotvalvmcdg[$npt] <= $minval ) {
		  $minval =  $plotvalvmcdg[$npt];
	          }
              }
	    }
	  }
	}

#########
}

&StDbTJobsDisconnect();

 $min_y = 0.8*$minval;
 $max_y = $maxval;

 my $ylabel;
 my $gtitle;

@data = ();


my $graph = new GD::Graph::linespoints(650,500);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

 } else {


if ($plotVal eq "MemUsage") {
    @data = (\@libtag, \@plotmemfsto, \@plotmemlsto, \@plotmemfstd, \@plotmemlstd, \@plotmemfstpdsf, \@plotmemlstpdsf,\@plotmemvmcfsto, \@plotmemvmclsto, \@plotmemvmcfstd, \@plotmemvmclstd, \@plotmemfstkisti, \@plotmemlstkisti,);

    $legend[0] = "MemUsageFirst(optimized,rcf)";
    $legend[1] = "MemUsageLast(optimized,rcf)";
    $legend[2] = "MemUsageFirst(nonoptimized,rcf)";
    $legend[3] = "MemUsageLast(nonoptimized,rcf)";
    $legend[4] = "MemUsageFirst(pdsf)";
    $legend[5] = "MemUsageLast(pdsf)";
    $legend[6] = "MemUsageFirst(optimized.AgML,rcf)";
    $legend[7] = "MemUsageLast(optimized.AgML,rcf)";
    $legend[8] = "MemUsageFirst(nonoptimized.AgML,rcf)";
    $legend[9] = "MemUsageLast(nonoptimized.AgML,rcf)";
    $legend[10] = "MemUsageFirst(kisti)";
    $legend[11] = "MemUsageLast(kisti)";

    $mplotVal="MemUsageFirstEvent,MemUsageLastEvent";

  } else {

    @data = (\@libtag, \@plotvalop, \@plotvaldg, \@plotvalpdsf, \@plotvalvmcop, \@plotvalvmcdg, \@plotvalkisti, );

    $legend[0] = "$plotVal"."(optimized,rcf)";
    $legend[1] = "$plotVal"."(nonoptimized,rcf)";
    $legend[2] = "$plotVal"."(pdsf)";
    $legend[3] = "$plotVal"."(optimized.AgML,rcf)";
    $legend[4] = "$plotVal"."(nonoptimized.AgML,rcf)";
    $legend[5] = "$plotVal"."(kisti)";

}

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0.5;
 my $xLabelSkip = 1;


    if( $min_y == 0) {
        $graph->set(x_label => "(0 value means job failed or data not available)");
    } else {
#        $min_y = $min_y*0.8;
  
    }

   $max_y = 1.2*$max_y;

    if($min_y < 0) {
        $min_y = 0;
    }

    $graph->set(#x_label => "$xlabel",
                #y_label => "$mplotVal",
                x_label_position => 0.5,
                title   => "$tset"." ($mplotVal)",
                y_tick_number => 10,
                y_min_value => $min_y,
                y_max_value => $max_y,
                y_number_format => \&y_format,
                labelclr => "lblack",
                dclrs => [ qw(lblack lred lgreen lpurple lgray lblue lorange lyellow lpink dbrown) ],
                line_width => 2,
                markers => [ 2,3,4,5,6,7,8,9],
                marker_size => 2,
                x_label_skip => $xLabelSkip,
                x_labels_vertical =>$xLabelsVertical,
                #long_ticks => 1
                );

   $graph->set_legend(@legend);
    $graph->set_legend_font(gdMediumBoldFont);
    $graph->set_title_font(gdMediumBoldFont);
    $graph->set_x_label_font(gdMediumBoldFont);
    $graph->set_y_label_font(gdMediumBoldFont);
    $graph->set_x_axis_font(gdMediumBoldFont);
    $graph->set_y_axis_font(gdMediumBoldFont);

         if ( scalar(@libtag) < 1 ) {
#        if ( scalar(@libtagop) < 1 or scalar(@plotvalop) < 1  ) {           
            print $qqr->header(-type => 'text/html')."\n";
            &beginHtml();
        } else {
            my $format = $graph->export_format;
            print header("image/$format");
            binmode STDOUT;
    
    print STDOUT $graph->plot(\@data)->$format();

       }
    }
  }

exit 0;

######################
sub StDbTJobsConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbTJobsDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}


##########################################################

sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}

#####################################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Plots for Nightly Test in NEW Library</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No $plotVal data for $tset and one year period </h1>


    </body>
   </html>
END
}
