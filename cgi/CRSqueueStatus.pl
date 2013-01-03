#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: CRSqueueStatus.pl,v 1.22 2013/01/03 19:14:39 didenko Exp $
#
# $Log: CRSqueueStatus.pl,v $
# Revision 1.22  2013/01/03 19:14:39  didenko
# minor modifications
#
# Revision 1.21  2013/01/03 19:05:42  didenko
# added year 2013
#
# Revision 1.20  2012/01/09 16:00:39  didenko
# changed default year to 2012
#
# Revision 1.18  2011/01/04 19:26:25  didenko
# more fixes
#
# Revision 1.17  2010/10/20 15:50:08  didenko
# updated title
#
# Revision 1.15  2010/10/20 15:36:25  didenko
# minor changes
#
# Revision 1.14  2010/10/20 15:27:16  didenko
# updated queues
#
# Revision 1.13  2010/01/06 19:03:22  didenko
# fixed scale
#
# Revision 1.12  2010/01/06 18:52:36  didenko
# updates for year 2010
#
# Revision 1.11  2009/01/05 18:06:06  didenko
# change default to 2009
#
# Revision 1.10  2008/12/31 17:08:37  didenko
# updated for year 2009
#
# Revision 1.9  2008/01/07 16:10:24  didenko
# updated for year 2008
#
# Revision 1.8  2007/11/07 19:13:42  didenko
# replace GIFGraph with GC::Graph
#
# Revision 1.7  2007/01/09 17:40:34  didenko
# change default year
#
# Revision 1.6  2007/01/09 17:33:51  didenko
# updates for year 2007
#
# Revision 1.5  2006/07/21 17:45:32  didenko
# more fixes for injection protection
#
# Revision 1.4  2006/07/06 16:02:46  didenko
# extend period for monitoring
#
# Revision 1.3  2006/01/12 22:11:34  didenko
# updated to use year's table
#
# Revision 1.2  2005/10/28 20:32:15  didenko
# get rid of onr more script
#
# Revision 1.2  2005/10/07 16:54:39  didenko
# updated limit
#
# Revision 1.2  2005/10/06 15:41:10  didenko
# updated
#
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use GD;
use CGI qw(:standard);
use GD::Graph::linespoints;
use Mysql;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months","7_months","8_months","9_months","10_months","11_months","12_months");
my @plotview = ("numbers","percentage");
my @prodyear = ("2009","2010","2011","2012","2013");

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $pryear =  $query->param('ryear');
 my $fperiod  =  $query->param('period');
 my $plview   =  $query->param('plotvw');


 if( $fperiod eq "" and $plview eq "" and $pryear eq "") {


print $query->header;
print $query->start_html('CRS queue status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS queue status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";  
print "<h3 align=center> Select year of production</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'ryear',
                             -values=>\@prodyear,
                             -default=>2013,
                             -size =>1); 

print "<p>";
print "</td><td>";
print "<h3 align=center> Select period of monitoring</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'period',
                             -values=>\@reqperiod,
                             -default=>day,
                             -size =>1); 

print "<p>";
print "</td><td>";
print "<h3 align=center> How do you want to view plots:</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'plotvw',
                             -values=>\@plotview,
                             -default=>numbers,
                             -size =>1); 


print "<p>";
print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

  }else{

my $qqr = new CGI;

my $pryear    =  $qqr->param('ryear');
my $fperiod   =  $qqr->param('period');
my $plview    =  $qqr->param('plotvw');

my $dyear = $pryear - 2000 ;

$dyear = 12;

# Tables
$crsJobStatusT = "crsJobStatusY".$dyear;
$crsQueueT = "crsQueueY".$dyear;


my $day_diff = 1;
my $max_y = 10000;
my $min_y = 0;
my @data;
my @legend;
my $ymax = 1;

my @numjobs1 = ();
my @numjobs2 = ();
my @numjobs3 = ();
my @numjobs4 = ();
my @numjobs5 = ();
my @numjobs6 = ();
my @Npoint = ();
my @maxvalue = ();

($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;
my $thisyear = $year+1900;
my $nowdatetime ;

 if( $thisyear eq $pryear) {

 $nowdate = $thisyear."-".($mon+1)."-".$mday;
 $nowdatetime = $thisyear."-".($mon+1)."-".$mday." ".$hour.":".$min.":59" ;

 }else{

 $nowdate = $pryear."-12-31 23:59:59";
 $nowdatetime = $nowdate;
}

my $day_diff = 0;
my $nmonth = 0;
my @prt = ();

    if( $fperiod eq "day") {
           $day_diff = 1;
    
    }elsif( $fperiod eq "week") {
           $day_diff = 7;
    }elsif ( $fperiod =~ /month/) {
       @prt = split("_", $fperiod);
       $nmonth = $prt[0];
       $day_diff = 30*$nmonth + 1; 
    }

  $day_diff = int($day_diff);


   &StcrsdbConnect();

 @numjobs1 = ();
 @numjobs2 = ();
 @numjobs3 = ();
 @numjobs4 = ();
 @numjobs5 = ();
 @numjobs6 = ();
 @Npoint = ();
 @maxvalue = ();

    if($plview eq "numbers") {

             $sql="SELECT max(queue0), max(queue3), max(queue4), max(queue5) FROM  $crsQueueT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff) ;
	while(@fields = $cursor->fetchrow_array) {  

 		$maxvalue[0] = $fields[0];
		$maxvalue[3] = $fields[1]; 
                $maxvalue[4] = $fields[2];
                $maxvalue[5] = $fields[3];   
	    }

 my $ii = 0;

            $sql="SELECT queue0, queue3, queue4, queue5, sdate FROM  $crsQueueT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? and sdate <= '$nowdatetime' ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff) ;
	while(@fields = $cursor->fetchrow_array) {

		$numjobs1[$ii] = $fields[0];
		$numjobs4[$ii] = $fields[1];
		$numjobs5[$ii] = $fields[2];
		$numjobs6[$ii] = $fields[3];
                $Npoint[$ii] =  $fields[4]; 
               	$ii++;
 
      }
    for ($k = 0; $k < scalar(@maxvalue); $k++) {
        if( $ymax <= $maxvalue[$k]) {
     $ymax = $maxvalue[$k];    
       }
    }
  $min_y = 0;
  $max_y = $ymax + 200 ;  
  $ylabel = "Number of jobs in the queues";
  $gtitle = "Number of jobs in the queues for the period of $fperiod ";

##

    }else{

            $sql="SELECT Rqueue0, Rqueue3, Rqueue4, Rqueue5 sdate FROM  $crsQueueT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) < ? ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff) ;
	while(@fields = $cursor->fetchrow_array) {

		$numjobs1[$ii] = $fields[0];
		$numjobs4[$ii] = $fields[1];
		$numjobs5[$ii] = $fields[2];
		$numjobs6[$ii] = $fields[3];
                $Npoint[$ii] =  $fields[4]; 
               	$ii++;
 
      }
   $min_y = 0;
  $max_y = 140;       
  $ylabel = "Number of jobs in the queue in % to max number of slots";
  $gtitle = "Number of jobs in the queues in % to max slots in the queue for period of $fperiod ";

    }

    &StcrsdbDisconnect();

#    @data = (\@Npoint, \@numjobs1, \@numjobs2, \@numjobs3, \@numjobs4, \@numjobs5, \@numjobs6 );
  @data = (\@Npoint, \@numjobs1, \@numjobs4, \@numjobs5, \@numjobs6 );

    $legend[0] = "Jobs in queue 0'";
#    $legend[1] = "Jobs in queue 1";
#    $legend[2] = "Jobs in queue 2";
    $legend[1] = "Jobs in queue 3";
    $legend[2] = "Jobs in queue 4"; 
    $legend[3] = "Jobs in queue 5";

 my  $graph = new GD::Graph::linespoints(750,650);


if ( ! $graph){
    print STDOUT $query->header(-type => 'text/plain');
    print STDOUT "Failed\n";
} else {

  my $format = $graph->export_format;
  print header("image/$format");
  binmode STDOUT;


 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2  if( $fperiod eq "day" );
$xLabelSkip = 12  if( $fperiod eq "week" );
$xLabelSkip = 24 if( $fperiod eq "1_month" );
$xLabelSkip = 48 if( $fperiod eq "2_months" );
$xLabelSkip = 72 if( $fperiod eq "3_months" );
$xLabelSkip = 96 if( $fperiod eq "4_months" );
$xLabelSkip = 120 if( $fperiod eq "5_months" );
$xLabelSkip = 144 if( $fperiod eq "6_months" );
$xLabelSkip = 168 if( $fperiod eq "7_months" );
$xLabelSkip = 192 if( $fperiod eq "8_months" );
$xLabelSkip = 216 if( $fperiod eq "9_months" );
$xLabelSkip = 240 if( $fperiod eq "10_months" );
$xLabelSkip = 264 if( $fperiod eq "11_months" );
$xLabelSkip = 288 if( $fperiod eq "12_months" );
 
    $graph->set(x_label => "  ",
		y_label => $ylabel,
		title   => $gtitle,
		y_tick_number => 10,
                x_label_position => 0.5,
		y_min_value => $min_y,
		y_max_value => $max_y,
		y_number_format => \&y_format,
		#labelclr => "lblack",
                titleclr => "lblack",
		dclrs => [ qw(lblack lblue lred lgreen lpink lpurple lorange lyellow ) ],
		line_width => 2,
		markers => [ 2,3,4,5,6,7,8,9],
		marker_size => 1,
                x_label_skip => $xLabelSkip, 
                x_labels_vertical =>$xLabelsVertical, 		
		);

    $graph->set_legend(@legend);
    $graph->set_legend_font(gdMediumBoldFont);
    $graph->set_title_font(gdLargeFont);
    $graph->set_x_label_font(gdMediumBoldFont);
    $graph->set_y_label_font(gdMediumBoldFont);
    $graph->set_x_axis_font(gdMediumBoldFont);
    $graph->set_y_axis_font(gdMediumBoldFont);
 

           if ( scalar(@Npoint) <= 1 ) {
            print $qqr->header(-type => 'text/html')."\n";
            &beginHtml();

        } else {

    print STDOUT $graph->plot(\@data)->$format();

   }
 }
}

####################
sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}
######################
sub StcrsdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StcrsdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}


#########################
sub beginHtml {

print <<END;
  <html>
   <head>
          <title>CRS queue status</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No data for the period of $fperiod </h1>


    </body>
   </html>
END
}
