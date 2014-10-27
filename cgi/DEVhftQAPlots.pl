#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: DEVhftQAPlots.pl
#
# L.Didenko
# Plots to check on dayly bases average numbet of hits for new detectors and 
# ratio of number of tracks reconstructed with /without HFT
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

$JobQAT = "newJobsQA";

my $debugOn = 0;
my @data = ();
my @legend = ();
my @Ndate = ();
my $ndt = 0;

my @prod_set = (
                "year_2014/AuAu200_production_low_2014",
                "year_2014/AuAu200_production_mid_2014",
		);


my @myplot =   (
		"PxlHits",
                "IstHits",
		"SsdHits", 
                "MtdHits",
		"MtdMatchHits",
                "avg_ratio_tracks",
		"avg_ratio_tracksnfit15",
                "avg_ratio_primaryT",
                "avg_ratio_primaryTnfit15",                 
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
print $query->start_html('Plots for new detectors software validation');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Plots for new detectors codes validation</u></h1>\n";

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
			     -size=>8);
print "</td><td>";
print "<h3 align=center> Select plot:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'plotVal',
			     -values=>\@myplot,
			     -size =>8); 

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

my $JobQAT = "newJobsQA";

my @point1 = ();
my @point2 = ();

$ndt = 0;
@Ndate = ();

for($i=0;$i<7*$qweek;$i++) {

    $point1[$i]=undef;
    $point2[$i]=undef;
}


($sec,$min,$hour,$mday,$mon,$year) = localtime();


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


#my $todate = ($year+1900)."-".($mon+1)."-".$mday." ".$hour.":".$min.":".$sec ;

my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

my $path;
my $path_opt;
my $qupath;
my $day_diff = 0;
my $maxvalue = 0;


 @Ndate = ();

 $day_diff = int(7*$qweek);
 $path_opt = "sl302.ittf_opt/%/".$tset;
 $path = "sl302.ittf/%/".$tset;

 &StDbTJobsConnect();

 if( $qweek >= 1 ) {

  $qupath = "%$path%";

            $sql="SELECT path, $plotVal, date_format(createTime, '%Y-%m-%d') as CDATE FROM $JobQAT WHERE path LIKE ? AND jobStatus=\"Done\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < ? ORDER by createTime  ";

        $cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
        $cursor->execute($qupath,$day_diff);


       while(@fields = $cursor->fetchrow_array) {
                $point1[$ndt] = $fields[1];
                $Ndate[$ndt] = $fields[2]; 
	        $ndt++;
          }


 $qupath = "%$path_opt%";

      for (my $ik = 0; $ik < $ndt; $ik++) {  

            $sql="SELECT path, $plotVal FROM $JobQAT WHERE path LIKE ? AND jobStatus=\"Done\" AND createTime like '$Ndate[$ik]%'  ";

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

    $legend[0] = "nonoptimized";
    $legend[1] = "optimized";


     if( $plotVal eq "avg_ratio_tracks" ) {
	 $ylabel = "Ratio of global tracks with/without HFT";
     }elsif( $plotVal eq "avg_ratio_tracksnfit15") {
	 $ylabel = "Ratio of global tracks nfits >= 15 for reco with/without HFT";
     }elsif( $plotVal eq "avg_ratio_primaryT" ) {
          $ylabel = "Ratio of primary tracks with/without HFT";
     }elsif( $plotVal eq "avg_ratio_primaryTnfit15" ) {
          $ylabel = "Ratio of primary tracks nfits >= 15 for reco with/without HFT" ;
     }else{
          $ylabel = "Number of hits";
     }
 
 
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
          <title>Plots for new detecrors QA </title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No $plotVal data for $tset and $qweek week period </h1>


    </body>
   </html>
END
}
