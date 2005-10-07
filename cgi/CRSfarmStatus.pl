#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: CRSfarmStatus.pl,v 1.1 2005/10/07 16:07:50 didenko Exp $
#
# $Log: CRSfarmStatus.pl,v $
# Revision 1.1  2005/10/07 16:07:50  didenko
# farm status
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

my $query = new CGI;

my $day_diff = 8;
my $max_y = 500000, $min_y = 0;
my @data;
my @legend;

 my $fperiod   =  $query->param('period');


if ( ($fperiod eq "") ) {
    print $query->header;
    print $query->start_html('Farm Status for $fperiod');
    print "<body bgcolor=\"cornsilk\"><center><pre>";
    print "<h1>Youre query failed, try again!!</h1>";
    print $query->end_html;
    exit(0);
}

my @numjobs1 = ();
my @numjobs2 = ();
my @numjobs3 = ();
my @numjobs4 = ();
my @numjobs5 = ();
my @Npoint = ();


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

	   my $ii = 0;

 @numjobs1 = ();
 @numjobs2 = ();
 @numjobs3 = ();
 @numjobs4 = ();
 @numjobs5 = ();
 @Npoint = ();


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

    @data = (\@Npoint, \@numjobs1, \@numjobs2, \@numjobs3, \@numjobs4 );

    $legend[0] = "Jobs in status 'executing'";
    $legend[1] = "Jobs waiting transferring from HPSS";
    $legend[2] = "Jobs waiting transferring to HPSS";
    $legend[3] = "Jobs failed";


  $graph = new GIFgraph::linespoints(750,650);

if ( ! $graph){
    print STDOUT $query->header(-type => 'text/plain');
    print STDOUT "Failed\n";
} else {
    print STDOUT $query->header(-type => 'image/gif');
    binmode STDOUT;


    my $min_y = 0;
    my $max_y = 600;  

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2  if( $fperiod eq "day" );
$xLabelSkip = 12  if( $fperiod eq "week" );
$xLabelSkip = 24 if( $fperiod eq "1_month" );
$xLabelSkip = 48 if( $fperiod eq "2_month" );
$xLabelSkip = 72 if( $fperiod eq "3_month" );
$xLabelSkip = 96 if( $fperiod eq "4_month" );
$xLabelSkip = 120 if( $fperiod eq "5_month" );
$xLabelSkip = 144 if( $fperiod eq "6_month" );
 
    $graph->set(x_label => "  ",
		y_label => "Number of jobs",
		title   => "Number of jobs on the farm for the period of $fperiod ",
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


sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}

