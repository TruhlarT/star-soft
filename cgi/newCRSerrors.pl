#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: newCRSerrors.pl - script to display jobs failure due to different errors 
#
#####################################################################################


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
$dbname="operation";


my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months","7_months","8_months","9_months","10_months","11_months","12_months");
my @prodyear = ("2013","2014");
my @plotview = ("numbers","percentage");

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);


my $day_diff = 1;
my $max_y = 10000;
my $min_y = 0;
my @data;
my @legend;
#my $Nmaxjobs = 700;

 my $pryear =  $query->param('ryear');
 my $fperiod  =  $query->param('period');
 my $plview   =  $query->param('plotvw');


  if( $fperiod eq "" and $plview eq "" and $pryear eq "") {


print $query->header;
print $query->start_html('CRS jobs failure status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS jobs failure plots </u></h1>\n";
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

 $dyear = 13;

# Tables
#$crsJobStatusT = "crsJobStatusY".$dyear;

$crsJobStatusT = "newcrsJobState";

my @numjobs1 = ();
my @numjobs2 = ();
my @numjobs3 = ();
my @numjobs4 = ();
my @numjobs5 = ();
my @numjobs6 = ();
my @numjobs7 = ();
my @jobsdone = ();
my @jobrate1 = ();
my @jobrate2 = ();
my @jobrate3 = ();
my @jobrate4 = ();
my @jobrate5 = ();
my @jobrate6 = ();
my @jobrate7 = ();
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
 @numjobs7 = ();
 @jobsdone = ();
 @jobrate1 = ();
 @jobrate2 = ();
 @jobrate3 = ();
 @jobrate4 = ();
 @jobrate5 = ();
 @jobrate6 = ();
 @jobrate7 = ();
  @Npoint = ();
 @maxvalue = ();

 
             $sql="SELECT max(condor_failed), max(prestaging_failed), max(hpss_import_failed), max(hpss_export_failed), max(hpss_retry_failed), max(job_exec_failed), max(io_error) FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? ";
 
	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);
	while(@fields = $cursor->fetchrow_array) {  

 		$maxvalue[0] = $fields[0];
		$maxvalue[1] = $fields[1];
		$maxvalue[2] = $fields[2];
		$maxvalue[3] = $fields[3];
 		$maxvalue[4] = $fields[4];
		$maxvalue[5] = $fields[5];
		$maxvalue[6] = $fields[6];  
	    }

 my $ii = 0;

            $sql="SELECT condor_failed, prestaging_failed, hpss_import_failed, hpss_export_failed, hpss_retry_failed, job_exec_failed, io_error, done, sdate FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? and sdate <= '$nowdatetime' ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);
	while(@fields = $cursor->fetchrow_array) {

		$numjobs1[$ii] = $fields[0];
		$numjobs2[$ii] = $fields[1];
		$numjobs3[$ii] = $fields[2];
		$numjobs4[$ii] = $fields[3];
                $numjobs5[$ii] = $fields[4];
		$numjobs6[$ii] = $fields[5];
                $numjobs7[$ii] = $fields[6];
                $jobsdone[$ii] = $fields[7];
                $Npoint[$ii] =  $fields[8]; 
               	$ii++;
 
 }

my $hmax = 0;
my $ymax = 1;
my $rtmax = 1;

    &StcrsdbDisconnect();

   $graph = new GD::Graph::linespoints(750,650);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

 } else {


    $legend[0] = "Jobs failed due to 'condor_failed'";
    $legend[1] = "Jobs failed due to 'prestaging_failed'";
    $legend[2] = "Jobs failed due to 'hpss_import_failed'";
    $legend[3] = "Jobs failed due to 'hpss_export_failed'";
    $legend[4] = "Jobs failed due to 'hpss_retry_failed'";
    $legend[5] = "Jobs failed due to 'job_exec_failed'";
    $legend[6] = "Jobs failed due to 'io_error'";

 my $ylabel;
 my $gtitle; 
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


$ymax = 1;
  $hmax = 0;
  $rtmax = 1;

    for ($k = 0; $k < scalar(@maxvalue); $k++) {
	if( $ymax <= $maxvalue[$k]) {
     $ymax = $maxvalue[$k];        
       }
    }

  if( $plview eq "numbers") {
 
    @data = (\@Npoint, \@numjobs1, \@numjobs2, \@numjobs3, \@numjobs4, \@numjobs5, \@numjobs6, \@numjobs7 );

  $min_y = 0;
  $max_y = $ymax + 50 ;  
  $ylabel = "Number of failed jobs per hour";
  $gtitle = "Number of jobs failed per hour for the period of $fperiod ";

    } else{

 for ($i = 0; $i<scalar(@Npoint); $i++) {
     if($jobsdone[$i] < 0.1 ) {
     $jobsdone[$i] = 1 ;
   }

  $jobrate1[$i] = $numjobs1[$i]*100/($numjobs1[$i] + $jobsdone[$i]);
  $jobrate2[$i] = $numjobs2[$i]*100/($numjobs2[$i] + $jobsdone[$i]);
  $jobrate3[$i] = $numjobs3[$i]*100/($numjobs3[$i] + $jobsdone[$i]);
  $jobrate4[$i] = $numjobs4[$i]*100/($numjobs4[$i] + $jobsdone[$i]);
  $jobrate5[$i] = $numjobs5[$i]*100/($numjobs5[$i] + $jobsdone[$i]);
  $jobrate6[$i] = $numjobs6[$i]*100/($numjobs6[$i] + $jobsdone[$i]);
  $jobrate7[$i] = $numjobs7[$i]*100/($numjobs7[$i] + $jobsdone[$i]);

	if( $hmax <= $jobrate1[$i]) {
     $hmax = $jobrate1[$i];        
       }  
	if( $hmax <= $jobrate2[$i]) {
     $hmax = $jobrate2[$i];        
       }
	if( $hmax <= $jobrate3[$i]) {
     $hmax = $jobrate3[$i];        
       }
 	if( $hmax <= $jobrate4[$i]) {
     $hmax = $jobrate4[$i];        
       }      
	if( $hmax <= $jobrate5[$i]) {
     $hmax = $jobrate5[$i];        
       }
	if( $hmax <= $jobrate6[$i]) {
     $hmax = $jobrate6[$i];        
       }
	if( $hmax <= $jobrate7[$i]) {
     $hmax = $jobrate7[$i];        
       }
    $rtmax =  $hmax;

 }

    @data = (\@Npoint, \@jobrate1, \@jobrate2, \@jobrate3, \@jobrate4, \@jobrate5, \@jobrate6, \@jobrate7 );

  $min_y = 0;  
  $max_y = int($rtmax) + 20 ;
# $max_y = 140;


  $ylabel = "Number of failed jobs in % to number of jobs finished per hour ";
  $gtitle = "Number of failed jobs in % to number of jobs finished per hour for period of $fperiod ";

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
		dclrs => [ qw(lblue lred lgreen lpurple lblack lyellow lpink lgrey ) ],
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

    my $format = $graph->export_format;
    print header("image/$format");
    binmode STDOUT;

    print STDOUT $graph->plot(\@data)->$format();      

   }
 }
}

######################
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
          <title>CRS jobs status (failure) </title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No data for the period of $fperiod </h1>


    </body>
   </html>
END
}
