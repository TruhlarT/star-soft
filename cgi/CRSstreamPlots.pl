#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# CRSstreamPlots.pl - script to make a plots of number of different stream's jobs running on the farm
#
####################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Mysql;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


my @reqperiod = ("day","week","1_month","2_months","3_months","6_month");
my @plotview = ("numbers","ratios");
my @prodyear = ("2010","2011","2012");

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $day_diff = 1;
my @data = ();
my @legend;
my $Nmaxjob = 1000;
my @maxvalue = ();

my @njb = ();
my @nphysics = ();
my @nht = ();
my @nhlt = ();
my @ngamma = ();
my @nminbias = ();
my @nmtd = ();
my @nmonitor = ();
my @natomcules = ();
my @nfmsfast = ();
my @npmdftp = ();
my @nupsilon = ();
my @nupc = ();
my @nWbs = ();
my @nzerobs = ();
my @ncentral = ();

my @rphysics = ();
my @rht = ();
my @rhlt = ();
my @rgamma = ();
my @rminbias = ();
my @rmtd = ();
my @rmonitor = ();
my @ratomcules = ();
my @rfmsfast = ();
my @rpmdftp = ();
my @rupsilon = ();
my @rupc = ();
my @rWbs = ();
my @rzerobs = ();
my @rcentral = ();

my @Npoint = ();


 my $pryear =  $query->param('ryear');
 my $fperiod  =  $query->param('period');
 my $plview   =  $query->param('plotvw');


  if( $fperiod eq "" and $plview eq "" and $pryear eq "") {


print $query->header;
print $query->start_html('Ratio of stream jobs');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Ratio of stream's jobs running on the CRS farm</u></h1>\n";
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
                             -default=>2012,
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
print "<h3 align=center> How do you want to view plots:<br> numbers or ratios </h3>";
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

# Tables
 $crsJobStreamsT = "crsJobStreamsY".$dyear;

#$crsJobStreamsT = "crsJobStreamsY11";

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

 @njob = ();
 @nphysics = ();
 @nht = ();
 @nhlt = ();
 @ngamma = ();
 @nminbias = ();
 @nmtd = ();
 @nmonitor = ();
 @nfmsfast = ();
 @npmdftp = ();
 @nupsilon = ();
 @nupc = ();
 @nWbs = ();
 @nzerobs = ();
 @ncentral = ();

 @rphysics = ();
 @rht = ();
 @rhlt = ();
 @rgamma = ();
 @rminbias = ();
 @rmtd = ();
 @rmonitor = ();
 @rfmsfast = ();
 @rpmdftp = ();
 @rupsilon = ();
 @rupc = ();
 @rWbs = ();
 @rzerobs = ();
 @rcentral = ();

 @Npoint = ();
 @maxvalue = ();

 $Nmaxjob = 1;

 my $ii = 0;
 
   $sql="SELECT max(physics), max(ht),max(hlt), max(gamma), max(fmsfast), max(minbias), max(mtd), max(monitor), max(pmdftp), max(upsilon), max(upc), max(zerobias), max(centralpro), max(Wbs) FROM  $crsJobStreamsT  WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? ";
 
	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);

        while(@fields = $cursor->fetchrow_array) {

         for( my $k = 0; $k < 14; $k++) {

         $maxvalue[$k] = $fields[$k];
        }
      }

#           $cursor->finish();

   $sql="SELECT physics, ht, hlt, gamma, fmsfast, minbias, mtd, monitor, pmdftp, upsilon, upc, zerobias, centralpro, Wbs, Njobs,sdate FROM  $crsJobStreamsT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(sdate)) <= ? and sdate <= '$nowdatetime' ORDER by sdate ";

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($day_diff);

        while(@fields = $cursor->fetchrow_array) {

                $nphysics[$ii] = $fields[0];
                $nht[$ii]      = $fields[1];
                $nhlt[$ii]     = $fields[2];
                $ngamma[$ii]   = $fields[3];
                $nfmsfast[$ii] = $fields[4];
                $nminbias[$ii] = $fields[5];
                $nmtd[$ii]     = $fields[6];
                $nmonitor[$ii] = $fields[7];
                $npmdftp[$ii]  = $fields[8];
                $nupsilon[$ii] = $fields[9];
                $nupc[$ii]     = $fields[10];
                $nzerobs[$ii]  = $fields[11];
                $ncentral[$ii] = $fields[12];
                $nWbs[$ii]     = $fields[13];
                $njb[$ii]      = $fields[14];

                $Npoint[$ii] =  $fields[15];
               	$ii++;
  }
 
    &StcrsdbDisconnect();
 
my $nnk = $ii;
      
    for( my $jj = 0; $jj < $nnk; $jj++) {
	if( $njb[$jj] >= 1) {
    
         $rphysics[$jj] = $nphysics[$jj]/$njb[$jj];
         $rht[$jj]      = $nht[$jj]/$njb[$jj];
         $rhlt[$jj]     = $nhlt[$jj]/$njb[$jj];
         $rgamma[$jj]   = $ngamma[$jj]/$njb[$jj];
         $rminbias[$jj] = $nminbias[$jj]/$njb[$jj];
         $rmtd[$jj]     = $nmtd[$jj]/$njb[$jj] ;
         $rmonitor[$jj] = $nmonitor[$jj]/$njb[$jj];
         $ratomcules[$jj] = $natomcules[$jj]/$njb[$jj];
         $rfmsfast[$jj] = $nfmsfast[$jj]/$njb[$jj];
         $rpmdftp[$jj]  = $npmdftp[$jj]/$njb[$jj];
         $rupsilon[$jj] = $nupsilon[$jj]/$njb[$jj];
         $rcentral[$jj] = $ncentral[$jj]/$njb[$jj];
         $rupc[$jj]     = $nupc[$jj]/$njb[$jj];
         $rWbs[$jj]     = $nWbs[$jj]/$njb[$jj];
     }else{
         $rphysics[$jj] = 0;
         $rht[$jj]      = 0;
         $rhlt[$jj]     = 0;
         $rgamma[$jj]   = 0;
         $rminbias[$jj] = 0;
         $rmtd[$jj]     = 0;
         $rmonitor[$jj] = 0;
         $ratomcules[$jj] = 0;
         $rfmsfast[$jj] = 0;
         $rpmdftp[$jj]  = 0;
         $rupsilon[$jj] = 0;
         $rcentral[$jj] = 0;
         $rupc[$jj]     = 0;
         $rWbs[$jj]     = 0;
        }
     }

     for( my $k = 0; $k < 14; $k++) {

     if ($maxvalue[$k] > $Nmaxjob ) {
        $Nmaxjob = $maxvalue[$k];

    }
 }

 @data = ();

   $graph = new GD::Graph::linespoints(750,650);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";
 } else {

#  my $format = $graph->export_format;
#  print header("image/$format");
#  binmode STDOUT;

       $legend[0] = "st_physics   ";
       $legend[1] = "st_gamma     ";
       $legend[2] = "st_hlt       ";
       $legend[3] = "st_ht        ";
       $legend[4] = "st_monitor   ";
       $legend[5] = "st_pmdftp    ";
       $legend[6] = "st_upc       ";
       $legend[7] = "st_atomcules ";
       $legend[8] = "st_mtd       ";
       $legend[9] = "st_central   ";

 my $ylabel;
 my $gtitle; 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;
 my $min_y = 0;
 my $max_y = 1;
 my $skipnum = 1;

       if (scalar(@Npoint) >= 40 ) {
            $skipnum = int(scalar(@Npoint)/20);
        }

        $xLabelSkip = $skipnum;

    if( $plview eq "numbers") {

#    @data = (\@Npoint, \@nphysics, \@ngamma, \@nhlt, \@nht, \@nmonitor, \@npmdftp, \@nupc, \@nmtd, \@nWbs );

    @data = (\@Npoint, \@nphysics, \@ngamma, \@nhlt, \@nht, \@nmonitor, \@npmdftp, \@nupc, \@natomcules, \@nmtd, \@ncentral );

  $min_y = 0;
  $max_y = $Nmaxjob + 200 ;
  
  $ylabel = "Number of different stream jobs ";
  $gtitle = "Number of different stream jobs on the farm for the period of $fperiod ";

    } else{
 
#    @data = (\@Npoint, \@rphysics, \@rgamma, \@rhlt, \@rht, \@rmonitor, \@rpmdftp, \@rupc, \@rmtd, \@rWbs );
    
	@data = (\@Npoint, \@rphysics, \@rgamma, \@rhlt, \@rht, \@rmonitor, \@rpmdftp, \@rupc, \@ratomcules, \@rmtd, \@rcentral );

  $min_y = 0;
  $max_y = 1.2 ;  

  $ylabel = "Ratio of different stream jobs"; 
  $gtitle = "Ratio of different stream jobs on the farm for the period of $fperiod ";

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
		dclrs => [ qw(lblue lgreen lpurple lorange lred marine lblack lyellow lbrown lgray) ],
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

#####################################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>CPU versus RealTime usage</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No stream jobs for the period of $fperiod </h1>


    </body>
   </html>
END
}
