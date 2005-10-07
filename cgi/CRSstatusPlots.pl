#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: CRSstatusPlots.pl,v 1.4 2005/10/07 21:00:54 didenko Exp $
#
# $Log: CRSstatusPlots.pl,v $
# Revision 1.4  2005/10/07 21:00:54  didenko
# more improvements
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
my $max_y = 10000;
my $min_y = 0;
my @data;
my @legend;
my $maxvalue = 10000;

 my $fstatus   =  $query->param('statusfield');
 my $fperiod   =  $query->param('period');


if ( ($fstatus eq "") || ($fperiod eq "") ) {
    print $query->header;
    print $query->start_html('Number of jobs in $fstatus for $fperiod');
    print "<body bgcolor=\"cornsilk\"><center><pre>";
    print "<h1>You must select both the type of plot and period!!</h1>";
    print $query->end_html;
    exit(0);
}

my @numjobs = ();
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

 @numjobs = ();
 @Npoint = ();


        $sql="SELECT max($fstatus) FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) < $day_diff ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute;
	while(@fields = $cursor->fetchrow_array) {

             $maxvalue =  $fields[0];
	 }


	if ($fperiod eq "day") {
	    $sql="SELECT $fstatus, sdate FROM  $crsJobStatusT WHERE sdate LIKE \"$nowdate%\"  ORDER by sdate ";
        }else {
            $sql="SELECT $fstatus, sdate FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) < $day_diff ORDER by sdate ";
      }

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute;
	while(@fields = $cursor->fetchrow_array) {

		$numjobs[$ii] = $fields[0];
                $Npoint[$ii] =  $fields[1]; 
               	$ii++;
 
 }


    &StcrsdbDisconnect();

    @data = (\@Npoint, \@numjobs );

  $graph = new GIFgraph::linespoints(700,600);

if ( ! $graph){
    print STDOUT $query->header(-type => 'text/plain');
    print STDOUT "Failed\n";
} else {
    print STDOUT $query->header(-type => 'image/gif');
    binmode STDOUT;

   if($maxvalue <= 20) {
    $max_y = $maxvalue + 10;
  }elsif($maxvalue <= 50) {
    $max_y = $maxvalue + 20;
  }elsif( $maxvalue <= 100) {
    $max_y = $maxvalue + 50;
  }elsif( $maxvalue <= 200) {
    $max_y = $maxvalue + 100;
  }elsif( $maxvalue <= 1000) {
    $max_y = $maxvalue + 200;
   }else{
   $max_y = $maxvalue + 400;  
  }

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2  if( $fperiod eq "day" );
$xLabelSkip = 12 if( $fperiod eq "week" );
$xLabelSkip = 24 if( $fperiod eq "1_month" );
$xLabelSkip = 48 if( $fperiod eq "2_month" );
$xLabelSkip = 72 if( $fperiod eq "3_month" );
$xLabelSkip = 96 if( $fperiod eq "4_month" );
$xLabelSkip = 120 if( $fperiod eq "5_month" );
$xLabelSkip = 144 if( $fperiod eq "6_month" );
 
    $graph->set(x_label => "  ",
		y_label => "Number of jobs",
		title   => "Number of jobs in status '$fstatus' for the period of $fperiod ",
		y_tick_number => 10,
		y_min_value => $min_y,
		y_max_value => $max_y,
		y_number_format => \&y_format,
		dclrs => [ qw(lblack lblue lred lgreen lpink lpurple lorange lyellow ) ],
		line_width => 2,
		markers => [ 2,3,4,5,6,7,8,9],
		marker_size => 1,
                x_label_skip => $xLabelSkip, 
                x_labels_vertical =>$xLabelsVertical, 		
		);

#    $graph->set_legend(@legend);
#    $graph->set_legend_font(gdMediumBoldFont);
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

