#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: CRSfarmStatus.pl,v 1.6 2005/10/24 18:33:39 didenko Exp $
#
# $Log: CRSfarmStatus.pl,v $
# Revision 1.6  2005/10/24 18:33:39  didenko
# fixed typo
#
# Revision 1.5  2005/10/24 18:28:33  didenko
# modified
#
# Revision 1.4  2005/10/19 21:04:44  didenko
# adjusted number of x marks
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

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCRSSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;
use Mysql;

my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months");
my @plotview = ("numbers","percentage");

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);


my $day_diff = 1;
my $max_y = 10000;
my $min_y = 0;
my @data;
my @legend;
my $Nmaxjobs = 422;

 my $fperiod  =  $query->param('period');
 my $plview   =  $query->param('plotvw');


  if( $fperiod eq "" and $plview eq "") {


print $query->header;
print $query->start_html('CRS farm status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS farm status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

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

my $fperiod   =  $qqr->param('period');
my $plview    =  $qqr->param('plotvw');

my @numjobs1 = ();
my @numjobs2 = ();
my @numjobs3 = ();
my @numjobs4 = ();
my @numjobs5 = ();
my @Npoint = ();
my @maxvalue = ();

($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

my $day_diff = 0;
my $nmonth = 0;
my @prt = ();

    if( $fperiod eq "day") {
           $day_diff = 1;
    
    }elsif( $fperiod eq "week") {
           $day_diff = 8;
    }elsif ( $fperiod =~ /month/) {
       @prt = split("_", $fperiod);
       $nmonth = $prt[0];
       $day_diff = 30*$nmonth + 1; 
    }

   &StcrsdbConnect();

 @numjobs1 = ();
 @numjobs2 = ();
 @numjobs3 = ();
 @numjobs4 = ();
 @jobrate1 = ();
 @jobrate2 = ();
 @jobrate3 = ();
 @jobrate4 = ();
 @Npoint = ();
 @maxvalue = ();


 
 	if ($fperiod eq "day") {
	    $sql="SELECT max(executing), max(importWaiting), max(exportWaiting), max(error) FROM  $crsJobStatusT WHERE sdate LIKE \"$nowdate%\" ";
        }else {
            $sql="SELECT max(executing), max(importWaiting), max(exportWaiting), max(error) FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) < $day_diff ";
      }

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute;
	while(@fields = $cursor->fetchrow_array) {  

 		$maxvalue[0] = $fields[0];
		$maxvalue[1] = $fields[1];
		$maxvalue[2] = $fields[2];
		$maxvalue[3] = $fields[3];   
	    }

 my $ii = 0;

	if ($fperiod eq "day") {
	    $sql="SELECT executing, importWaiting, exportWaiting, error, sdate FROM  $crsJobStatusT WHERE sdate LIKE \"$nowdate%\"  ORDER by sdate ";
        }else {
            $sql="SELECT executing, importWaiting, exportWaiting, error, sdate FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) < $day_diff ORDER by sdate ";
      }

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute;
	while(@fields = $cursor->fetchrow_array) {

		$numjobs1[$ii] = $fields[0];
		$numjobs2[$ii] = $fields[1];
		$numjobs3[$ii] = $fields[2];
		$numjobs4[$ii] = $fields[3];
                $Npoint[$ii] =  $fields[4]; 
               	$ii++;
 
 }


    &StcrsdbDisconnect();

   $graph = new GIFgraph::linespoints(750,650);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";
 } else {
    print STDOUT $qqr->header(-type => 'image/gif');
    binmode STDOUT;

    $legend[0] = "Jobs in status 'executing'";
    $legend[1] = "Jobs waiting transferring from HPSS";
    $legend[2] = "Jobs waiting transferring to HPSS";
    $legend[3] = "Jobs failed";


 my $ylabel;
 my $gtitle; 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2  if( $fperiod eq "day" );
$xLabelSkip = 12  if( $fperiod eq "week" );
$xLabelSkip = 24 if( $fperiod eq "1_month" );
$xLabelSkip = 44 if( $fperiod eq "2_months" );
$xLabelSkip = 60 if( $fperiod eq "3_months" );
$xLabelSkip = 80 if( $fperiod eq "4_months" );
$xLabelSkip = 120 if( $fperiod eq "5_months" );
$xLabelSkip = 144 if( $fperiod eq "6_months" );

    my  $ymax = 1;

    for ($k = 0; $k < scalar(@maxvalue); $k++) {
	if( $ymax <= $maxvalue[$k]) {
     $ymax = $maxvalue[$k];    
       }
    }

    if( $plview eq "numbers") {

    @data = (\@Npoint, \@numjobs1, \@numjobs2, \@numjobs3, \@numjobs4 );

  $min_y = 0;
  $max_y = $ymax + 200 ;  
  $ylabel = "Number of jobs";
  $gtitle = "Number of jobs on the farm for the period of $fperiod ";

    } else{

  for ($i = 0; $i<scalar(@numjobs1); $i++) {
  $jobrate1[$i] = $numjobs1[$i]*100/$Nmaxjobs; 
  $jobrate2[$i] = $numjobs2[$i]*100/$Nmaxjobs;
  $jobrate3[$i] = $numjobs3[$i]*100/$Nmaxjobs;
  $jobrate4[$i] = $numjobs4[$i]*100/$Nmaxjobs;    
 }
 
    @data = (\@Npoint, \@jobrate1, \@jobrate2, \@jobrate3, \@jobrate4 );

  $min_y = 0;
  $max_y = $ymax*100/$Nmaxjobs + 40 ;  

  $ylabel = "Number of jobs in % "; 
  $gtitle = "Number of jobs on the farm in % to available slots for the period of $fperiod ";

}

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
    print STDOUT $graph->plot(\@data);
}
}

sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}

