#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# $Log: DEVPlots.pl
#
# L.Didenko
# Plots to check on daily bases changes in tracking and CPU for DEV library test samples
#
#############################################################################

use CGI;

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";

# Tables

my $JobStatusT = "JobStatus";

my @data = ();
my @legend = ();
my @Ndate = ();
my $ndt = 0;

my @prod_set = (
                "daq_ittf/year_2014/AuAu200_production_mid_2014",
                "daq_ittf/year_2014/AuAu200_production_low_2014",
                "daq_ittf/year_2014/AuHe3_production_2014",
                "daq_ittf/year_2014/AuAu200_production_2014",
                "daq_ittf/year_2014/production_15GeV_2014",
                "daq_ittf/year_2013/pp500_production_2013",
                "daq_ittf/year_2012/cuAu_production_2012",
                "daq_ittf/year_2012/UU_production_2012",
                "daq_ittf/year_2012/pp500_production_2012",
                "daq_ittf/year_2012/pp200_production_2012",
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
                "daq_ittf/year_2007/auau200_embedTpcSvtSsd",
                "daq_ittf/year_2006/ppProdLong",
                "daq_ittf/year_2006/ppProdTrans",
                "daq_ittf/year_2005/CuCu200_MinBias",
                "daq_ittf/year_2005/CuCu62_MinBias",
                "daq_ittf/year_2005/CuCu22_MinBias",
                "daq_ittf/year_2005/ppProduction",
                "daq_ittf/year_2005/CuCu200_embedTpc",
                "daq_ittf/year_2005/CuCu200_embedTpcSvtSsd",
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
                "Average_NoTracks",
                "Average_NoPrimaryT",
                "Average_NoTracksNfit15",
                "Average_NoPrimaryTNfit15",
                "Average_NoPrimVertex",
                "NoEvent_vertex",
                "Percent_of_usableEvents",
                "Average_NoTracks_per_usableEvent",
                "Average_NoTracksNfit15_per_usableEvent",
                "MemUsage",
                "CPU_per_Event",
                "RealTime_per_Event",
                "RealTime_per_CPU",
                  );   


my %plotHash = (
                Average_NoTracks => 'avg_no_tracks',
                Average_NoPrimaryT => 'avg_no_primaryT',
                Average_NoTracksNfit15 => 'avg_no_tracksnfit15',
                Average_NoPrimaryTNfit15  => 'avg_no_primaryTnfit15',
                Average_NoPrimVertex => 'avgNoVtx_evt',
                NoEvent_vertex => 'NoEventVtx',
                Percent_of_usableEvents => 'percent_of_usable_evt',
                Average_NoTracks_per_usableEvent => 'avgNoTrack_usbevt',
                Average_NoTracksNfit15_per_usableEvent => 'avgNoTrackNfit15_usbevt',
                MemUsage => 'memUsageF, memUsageL',
                CPU_per_Event => 'CPU_per_evt_sec',
                RealTime_per_evt  => 'RealTime_per_evt',         
                RealTime_per_CPU => 'RealTime_per_evt, CPU_per_evt_sec',
    );

my $min_y = 0;
my $max_y = 2000;

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $tset    = $query->param('sets');
my $plotVal = $query->param('plotVal');
my $qweek = $query->param('nweek');

  if( $tset eq "" and $plotVal eq "" and $qweek eq "") {

print $query->header();
print $query->start_html('Plots for DEV library test');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Plots for DEV library test </u></h1>\n";

print "<br>";
print "<br>";
print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h3 align=center>Select test sample</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'sets',
			     -values=>\@prod_set,
			     -size=>6);
print "</td><td>";
print "<h3 align=center> Select plot:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'plotVal',
			     -values=>\@myplot,
			     -size =>6); 

print "</td> </tr> </table><hr><center>";
print "<br>";
print "<h3 align=center> How many weeks do you want to show: ";
print $query->popup_menu(-name=>'nweek',
                         -values=>['1','2','3','4','5','6','7','8','9','10','12','13','14','15','16'],
                         -defaults=>1);
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
my $qweek   =  $qqr->param('nweek');

 $JobStatusT = "JobStatus";

my @point1 = ();
my @point2 = ();

for($i=0;$i<7*$qweek;$i++) {

    $point1[$i]=undef;
    $point2[$i]=undef;
}

my @spl = ();
@spl = split(" ",$plotVal);
my $plotVl = $spl[0];

my $mplotVal = $plotHash{$plotVl};


($sec,$min,$hour,$mday,$mon,$year) = localtime();


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


#my $todate = ($year+1900)."-".($mon+1)."-".$mday." ".$hour.":".$min.":".$sec ;

my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

my $weeks = int($qweek);


my $path;
my $path_opt;
my $qupath;
my $day_diff = 0;
my $maxvalue = 0;

my @prt = ();

$path = "/star/rcf/test/dev/".$tset ;
$path =~ s/ittf/sl53.ittf\/%/g ;
$path_opt = "/star/rcf/test/dev/".$tset ;
$path_opt =~ s/ittf/sl53.ittf_opt\/%/g ;


 @Ndate = ();
 $ndt = 0;

 $day_diff = int(7*$qweek);

 &StDbTJobsConnect();

 if( $qweek >= 1 ) {

  $qupath = "$path%";


            $sql="SELECT path, $mplotVal, date_format(createTime, '%Y-%m-%d') as CDATE FROM $JobStatusT WHERE path LIKE ? AND jobStatus=\"Done\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < ? ORDER by createTime  ";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($qupath,$day_diff);


       while(@fields = $cursor->fetchrow_array) {
                $point1[$ndt] = $fields[1];
                $Ndate[$ndt] = $fields[2]; 
	        $ndt++;
          }


 $qupath = "$path_opt%";

      for (my $ik = 0; $ik < $ndt; $ik++) {  

            $sql="SELECT path, $mplotVal FROM $JobStatusT WHERE path LIKE ? AND jobStatus=\"Done\" AND createTime like '$Ndate[$ik]%'  ";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($qupath);


       while(@fields = $cursor->fetchrow_array) {
                $point2[$ik] = $fields[1];
          }

      }

########
  }

$maxvalue = 0;

      for (my $ik = 0; $ik < $ndt; $ik++) {  

	  if($point1[$ik] >= $maxvalue ) {
            $maxvalue = $point1[$ik];
          }else{
           next;
          }  
      }

     for (my $ik = 0; $ik < $ndt; $ik++) {  

	  if($point2[$ik] >= $maxvalue ) {
            $maxvalue = $point2[$ik];
          }else{
           next;
          }  
      }



&StDbTJobsDisconnect();

 my $ylabel;
 my $gtitle;

@data = ();


my $graph = new GD::Graph::linespoints(650,500);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

 } else {

    @data = (\@Ndate, \@point1, \@point2 );

#   @data = (\@Ndate, \@point1 );

    $legend[0] = "nonoptimized";
    $legend[1] = "optimized";


 $ylabel = $plotVal; 

 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0.5;
 my $xLabelSkip = 1;

 $min_y = 0;
 $max_y = 1.4*$maxvalue; 

$xLabelSkip = 2 if( $qweek eq "4" );
$xLabelSkip = 2 if( $qweek eq "5" );
$xLabelSkip = 2 if( $qweek eq "6" );
$xLabelSkip = 2 if( $qweek eq "7" );
$xLabelSkip = 2 if( $qweek eq "8" );
$xLabelSkip = 2 if( $qweek eq "9" );
$xLabelSkip = 2 if( $qweek eq "10" );
$xLabelSkip = 3 if( $qweek eq "12" );
$xLabelSkip = 3 if( $qweek eq "13" );
$xLabelSkip = 3 if( $qweek eq "14" );
$xLabelSkip = 4 if( $qweek eq "15" );
$xLabelSkip = 4 if( $qweek eq "16" );


    $graph->set(#x_label => "$xlabel",
                x_label_position => 0.5,
                title   => "$tset"." ($plotVal)",
                y_label => $ylabel,
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

         if ( scalar(@Ndate) < 1 ) {

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


#####################################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Plots for DEV library tests </title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No $plotVl data for $tset and $qweek week period </h1>


    </body>
   </html>
END
}





##########################################################

sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}


