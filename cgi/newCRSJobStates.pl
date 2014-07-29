#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: newCRSJobStates.pl
#
# $Log: newCRSJobStates.pl
#
# L.Didenko
#
# script to make summary plot for CRS jobs states with new software
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $crsJobStatusT = "newcrsJobState";

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months","7_month","8_months","9_months","10_months","11_months","12_months");


my $day_diff = 0;
my $max_y = 10000;
my $min_y = 0;
my @data = ();
my @legend = ();
my $maxvalue = 10000;

my @numjobs = ();
my @Npoint = ();

my @numrun = ();
my @numstage = ();
my @numimport = ();
my @numexport = ();
my @numqueued = ();
my @numsubmit = ();
my @numerror = ();
my @numdone = ();
my @numheld = ();


 my $pryear    =  $query->param('ryear');
 my $fperiod   =  $query->param('period');
 
 my $fstatus ;
 my @prodyear = ("2013","2014");

  if( $fperiod eq "" and $pryear eq "" ) {

print $query->header();
print $query->start_html('CRS jobs state');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS jobs states </u></h1>\n";

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
                             -default=>2014,
                             -size =>1); 

print "</td><td>";
print "<h3 align=center> Select period of monitoring</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'period',
                             -values=>\@reqperiod,
                             -default=>day,
                             -size =>1); 

print "</td> </tr> </table><hr><center>";

print "</h4>";
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

# my $dyear = $pryear - 2000 ;

my $dyear = $pryear;

# Tables
#$crsJobStatusT = "newcrsJobState".$dyear;

$crsJobStatusT = "newcrsJobState";

 $day_diff = 0;
 $max_y = 10000;
 $min_y = 0;
 @data = ();
 @legend = ();
 @maxvalue = ();
 $maxval = 0;

 @numrun = ();
 @numstage = ();
 @numimport = ();
 @numexport = ();
 @numqueued = ();
 @numsubmit = ();
 @numerror = ();
 @numdone = ();
 @numheld = ();
 @Npoint = ();


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

my $ii = 0;


        $sql="SELECT max(running), max(staging), max(done), max(queued), max(error) FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff) ;
	while(@fields = $cursor->fetchrow_array) {

            $maxvalue[0] =  $fields[0];
            $maxvalue[1] =  $fields[1];
            $maxvalue[2] =  $fields[2];
            $maxvalue[3] =  $fields[3];
            $maxvalue[4] =  $fields[4];
	 }


        $sql="SELECT running, staging, importing, exporting, queued, done, error, held, submitted, sdate FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ?  and sdate <= '$nowdatetime' ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);
	while(@fields = $cursor->fetchrow_array) {

	     $numrun[$ii]    = $fields[0];
	     $numstage[$ii]  = $fields[1];
	     $numimport[$ii] = $fields[2];
	     $numexport[$ii] = $fields[3];
	     $numqueued[$ii] = $fields[4];
	     $numdone[$ii]   = $fields[5];
	     $numerror[$ii]  = $fields[6];
             $numheld[$ii]   = $fields[7];
             $numsubmit[$ii] = $fields[8];             
             $Npoint[$ii]    = $fields[9]; 
             $ii++;
 
 }

   &StcrsdbDisconnect();

    for( $kk =0; $kk < 5; $kk++)  {
	if( $maxvalue[$kk] >= $maxval ) {
         $maxval = $maxvalue[$kk];
      }
    } 


   @data = (\@Npoint, \@numrun, \@numstage, \@numsubmit, \@numimport, \@numexport, \@numqueued, \@numdone, \@numerror, \@numheld );

my  $graph = new GD::Graph::linespoints(750,650);

if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

} else {
 
   $max_y = int($maxval + 0.2* $maxval);

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;


   $legend[0] = "jobs running";
   $legend[1] = "jobs staging";
   $legend[2] = "jobs submitted";
   $legend[3] = "jobs importing";
   $legend[4] = "jobs exporting";
   $legend[5] = "jobs queued";
   $legend[6] = "jobs done";
   $legend[7] = "jobs error";
   $legend[8] = "jobs held";


$xLabelSkip = 2  if( $fperiod eq "day" );
$xLabelSkip = 12 if( $fperiod eq "week" );
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
		y_label => "Number of jobs",
		title   => "Number of jobs in different states for the period of $fperiod ",
		y_tick_number => 10,
		y_min_value => $min_y,
		y_max_value => $max_y,
		y_number_format => \&y_format,
		dclrs => [ qw(lblack lgreen gold brown purple red blue orange pink) ],
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
	       print  $qqr->header(-type => 'text/html');
            &beginHtml();

        } else {
           my $format = $graph->export_format;
           print header("image/$format");
           binmode STDOUT;

     print STDOUT $graph->plot(\@data)->$format();

   }
  }
 }

#############################################

sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}


#############################################
sub StcrsdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

##############################################
sub StcrsdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

##############################################
sub beginHtml {

print <<END;
  <html>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No data for the period of $fperiod </h1>

    </body>
  </html>
END
}

