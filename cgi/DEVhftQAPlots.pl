#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: DEV hftQAPlits.pl
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

my @prod_set = (
                "/year_2014/AuAu200_production_low_2014",
                "/year_2014/AuAu200_production_mid_2014",
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
print "<h1 align=center><u>Plots for new detectors code validation</u></h1>\n";

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
			     -size=>1);
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

my @Nday = ();

my @point1 = ();
my @point2 = ();

my $ndt = 0;
my @Ndate = ();

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

my $today = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];

my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

if ( $today eq Tue ) {
    $Nday[0] = "Tue"; $Nday[1] = "Wed"; $Nday[2] = "Thu"; $Nday[3] = "Fri"; $Nday[4] = "Sat"; $Nday[5] = "Sun"; $Nday[6] = "Mon";
} elsif ( $today eq Wed ) {
    $Nday[6] = "Tue"; $Nday[0] = "Wed"; $Nday[1] = "Thu"; $Nday[2] = "Fri"; $Nday[3] = "Sat"; $Nday[4] = "Sun"; $Nday[5] = "Mon";
} elsif ( $today eq Thu ) {
    $Nday[5] = "Tue"; $Nday[6] = "Wed"; $Nday[0] = "Thu"; $Nday[1] = "Fri"; $Nday[2] = "Sat"; $Nday[3] = "Sun"; $Nday[4] = "Mon";
} elsif ( $today eq Fri ) {
    $Nday[4] = "Tue"; $Nday[5] = "Wed"; $Nday[6] = "Thu"; $Nday[0] = "Fri"; $Nday[1] = "Sat"; $Nday[2] = "Sun"; $Nday[3] = "Mon";
} elsif ( $today eq Sat ) {
    $Nday[3] = "Tue"; $Nday[4] = "Wed"; $Nday[5] = "Thu"; $Nday[6] = "Fri"; $Nday[0] = "Sat"; $Nday[1] = "Sun"; $Nday[2] = "Mon";
} elsif ( $today eq Sun ) {
    $Nday[2] = "Tue"; $Nday[3] = "Wed"; $Nday[4] = "Thu"; $Nday[5] = "Fri"; $Nday[6] = "Sat"; $Nday[0] = "Sun"; $Nday[1] = "Mon";
} else {
    $Nday[1] = "Tue"; $Nday[2] = "Wed"; $Nday[3] = "Thu"; $Nday[4] = "Fri"; $Nday[5] = "Sat"; $Nday[6] = "Sun"; $Nday[0] = "Mon";
}

my $weeks = int($qweek);

for($i=1;$i<$weeks;$i++) {
    for($j=0;$j<7;$j++) {
        $Nday[$j+7*$i] = $Nday[$j];
    }
}

my $path;
my $path_opt;
my $qupath;
my $day_diff = 0;

 @Ndate = ();

 $day_diff = int(7*$qweek);
 $path_opt = "sl302.ittf_opt/%".$tset;
 $path = "sl302.ittf/%".$tset;

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


     if( $plotVal =~ /avg_ratio_track/ ) {
	 $ylabel = "Ratio of global tracks";
     } elsif( $plotVal =~ /avg_ratio_primary/ ) {
          $ylabel = "Ratio of primary tracks";
     }else{
          $ylabel = "Number of hits";
     }
 
 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0.5;
 my $xLabelSkip = 1;

 $min_y = 0;

    $graph->set(#x_label => "$xlabel",
                #y_label => "$plotVal",
                x_label_position => 0.5,
                title   => "$tset"."   ($plotVal)",
                y_label => $ylabel,
                y_tick_number => 10,
                y_min_value => $min_y,
#                y_max_value => $max_y,
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
     <h1 align=center>No $plotVal data for $tset and $qweek period </h1>


    </body>
   </html>
END
}
