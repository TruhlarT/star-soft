#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: CRSstatusPlots.pl,v 1.29 2013/01/03 19:18:03 didenko Exp $
#
# $Log: CRSstatusPlots.pl,v $
# Revision 1.29  2013/01/03 19:18:03  didenko
# added year 2013
#
# Revision 1.28  2012/01/09 16:24:55  didenko
# added note if no data
#
# Revision 1.27  2012/01/03 20:01:07  didenko
# change skip label
#
# Revision 1.24  2011/01/04 19:33:39  didenko
# updated for 2011 year
#
# Revision 1.22  2010/10/06 17:39:10  didenko
# changed scale
#
# Revision 1.21  2010/01/06 19:03:21  didenko
# fixed scale
#
# Revision 1.20  2010/01/06 18:57:26  didenko
# fixed syntax
#
# Revision 1.19  2010/01/06 18:52:36  didenko
# updates for year 2010
#
# Revision 1.18  2009/01/05 18:06:06  didenko
# change default to 2009
#
# Revision 1.17  2008/12/31 17:08:47  didenko
# updated for year 2009
#
# Revision 1.16  2008/01/09 20:09:24  didenko
# updated due to changed location
#
# Revision 1.15  2008/01/07 16:10:33  didenko
# updated for year 2008
#
# Revision 1.14  2007/11/07 19:19:07  didenko
# replace GIFGraph with GC::Graph
#
# Revision 1.13  2007/01/09 17:40:34  didenko
# change default year
#
# Revision 1.12  2007/01/09 17:34:00  didenko
# updates for year 2007
#
# Revision 1.11  2006/07/21 18:15:30  didenko
# more fixes for injection protection
#
# Revision 1.10  2006/07/06 16:16:23  didenko
# fixed syntax
#
# Revision 1.8  2006/01/13 22:29:48  didenko
# updated for year tables
#
# Revision 1.7  2005/10/28 16:35:25  didenko
# fixed name
#
# Revision 1.5  2005/10/19 21:08:31  didenko
# fixed bug
#
# Revision 1.4  2005/10/07 21:00:54  didenko
# more improvements
#
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

require "/afs/rhic.bnl.gov/star/packages/scripts/CRSUtils/dbCRSSetup.pl";

use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Mysql;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my @farmstat = ("executing","submitted","submitFailed","started","importWaiting","importHPSS","sleep","exportWaiting","exportHPSS","exportUNIX","done","error","fatal");

my @reqperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months","7_month","8_months","9_months","10_months","11_months","12_months");

$query = new CGI;


 my $fstatus   =  $query->param('statusfield');
 my $fperiod   =  $query->param('period');
 my @prodyear = ("2005","2006","2007","2008","2009","2010","2011","2012","2013");

  if( $fperiod eq "" and $fstatus eq "" and $pryear eq "" ) {

print $query->header;
print $query->start_html('CRS jobs status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>CRS jobs status </u></h1>\n";

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
print "<h3 align=center>Select jobs status</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'statusfield',
                             -values=>\@farmstat,
                             -default=>executing,
                             -size=>1);
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
 my $qstatus   =  $qqr->param('statusfield');
 my $fperiod   =  $qqr->param('period'); 

 my $dyear = $pryear - 2000 ;

 $dyear = 12;

# Tables
$crsJobStatusT = "crsJobStatusY".$dyear;
$crsQueueT = "crsQueueY".$dyear;


my $day_diff = 0;
my $max_y = 10000;
my $min_y = 0;
my @data;
my @legend;
my $maxvalue = 10000;

my @numjobs = ();
my @Npoint = ();

my $fstatus;

  $fstatus = (split(" ",$qstatus))[0];

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

 @numjobs = ();
 @Npoint = ();


        $sql="SELECT max($fstatus) FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff) ;
	while(@fields = $cursor->fetchrow_array) {

             $maxvalue =  $fields[0];
	 }


            $sql="SELECT $fstatus, sdate FROM  $crsJobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ?  and sdate <= '$nowdatetime' ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);
	while(@fields = $cursor->fetchrow_array) {

		$numjobs[$ii] = $fields[0];
                $Npoint[$ii] =  $fields[1]; 
               	$ii++;
 
 }


    &StcrsdbDisconnect();

    @data = (\@Npoint, \@numjobs );

my  $graph = new GD::Graph::linespoints(750,650);

if ( ! $graph){
    print STDOUT $query->header(-type => 'text/plain');
    print STDOUT "Failed\n";
} else {
 
  my $format = $graph->export_format;
  print header("image/$format");
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
$xLabelSkip = 8 if( $fperiod eq "week" );
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


           if ( scalar(@Npoint) <= 1 ) {
            print $qqr->header(-type => 'text/html')."\n";
            &beginHtml();

        } else {

     print STDOUT $graph->plot(\@data)->$format();

   }
  }
}

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
          <title>CRS farm status</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No data for the period of $fperiod </h1>


    </body>
   </html>
END
}

