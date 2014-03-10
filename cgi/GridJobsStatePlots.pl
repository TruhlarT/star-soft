#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: GridJobsStatePlots.pl
#
# $Log: GridJobsStatePlots.pl
#
# L.Didenko
#
# script to monitor GRID production jobs states
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
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my @reqperiod = ("week","1_month","2_months","3_months","4_months","5_months","6_months");


my $day_diff = 0;
my $max_y = 10000;
my $min_y = 0;
my @data = ();
my @legend = ();
my $maxvalue = 10000;

my @Npoint = ();
my @sdays = ();
my $ndy = 0;
my @strun = ();
my @stdone = ();
my @stidle = ();
my @stheld = ();
my $nd = 0;


 my $fperiod   =  $query->param('period');


  if( $fperiod eq "" ) {

print $query->header();
print $query->start_html('GRID jobs states');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>GRID jobs states </u></h1>\n";

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

my $fperiod   =  $qqr->param('period'); 

# Tables

$JobStatusT = "jobs_prod_2013";

 $day_diff = 0;
 $max_y = 10000;
 $min_y = 0;
 @data = ();
 @legend = ();
 $maxvalue = 10000;

 @numjobs = ();
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

#if( $thisyear eq $pryear) {

 $nowdate = $thisyear."-".($mon+1)."-".$mday;
 $nowdatetime = $thisyear."-".($mon+1)."-".$mday." ".$hour.":".$min.":59" ;

# }else{

# $nowdate = $pryear."-12-31 23:59:59";
# $nowdatetime = $nowdate;
#}

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


   &StdbConnect();

 @sdays = ();
 $ndy = 0;
 @strun = ();
 @stdone = ();
 @stidle = ();
 @stheld = ();
 $nd = 0;


   $sql="SELECT DISTINCT date_format(submissionTime, '%Y-%m-%d') as SDATE  FROM $JobStatusT where (TO_DAYS(\"$nowdate\") - TO_DAYS(submissionTime)) <= ? order by SDATE" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($day_diff);

       while( my $dy = $cursor->fetchrow() ) {
          $sdays[$ndy] = $dy;
          $ndy++;
       }
    $cursor->finish();

@sdays = ();
@sdays = ("2014-03-03","2014-03-04","2014-03-05","2014-03-06","2014-03-07","2014-03-08","2014-03-09","2014-03-10");



   foreach my $tdate (@sdays) {


        $sql="SELECT count(jobState) FROM  $JobStatusT WHERE submissionTime like '$tdate%' where jobState = 'running' ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute( ) ;
	while( my $srun = $cursor->fetchrow) {

             $strun[$nd] =  $srun;
	 }

    $cursor->finish();

       $sql="SELECT count(jobState) FROM  $JobStatusT WHERE submissionTime like '$tdate%' where jobState = 'done' ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute( ) ;
	while( my $sdn = $cursor->fetchrow) {

             $stdone[$nd] =  $sdn;
	 }

    $cursor->finish();
 

      $sql="SELECT count(jobState) FROM  $JobStatusT WHERE submissionTime like '$tdate%' where jobState = 'idle' ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute( ) ;
	while( my $sdle = $cursor->fetchrow) {

             $stidle[$nd] =  $sdle;
	 }

    $cursor->finish();

      $sql="SELECT count(jobState) FROM  $JobStatusT WHERE submissionTime like '$tdate%' where jobState = 'held' ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute( ) ;
	while( my $sdhd = $cursor->fetchrow) {

             $stheld[$nd] =  $sdhd;
	 }

    $cursor->finish();
 
	$Npoint[$nd] = $tdate;
	$nd++;

 }

   &StdbDisconnect();

   @data = (\@Npoint, \@strun, \@stdone, \@stidle, \@stheld );



my  $graph = new GD::Graph::linespoints(750,650);

if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

} else {
 

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2 if( $fperiod eq "1_month" );
$xLabelSkip = 4 if( $fperiod eq "2_months" );
$xLabelSkip = 6 if( $fperiod eq "3_months" );
$xLabelSkip = 12 if( $fperiod eq "4_months" );
$xLabelSkip = 14 if( $fperiod eq "5_months" );
$xLabelSkip = 16 if( $fperiod eq "6_months" );
 
    $graph->set(x_label => "  ",
		y_label => "Number of jobs",
		title   => "Number of jobs in different states for the period of $fperiod ",
		y_tick_number => 10,
#		y_min_value => $min_y,
#		y_max_value => $max_y,
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
sub StdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

##############################################
sub StdbDisconnect {
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

