#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# prodEffcPlot.cgi - script for production efficiency
#
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Class::Struct;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday;

my $nowdate = $todate;

my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my $lastdate;


my @arperiod = ( );

my @arrprod = ();
my $npr = 0;
my $mpr;

my $pryear = "2014";

my @ndate = ();
my $ndt = 0;
my @ardays = ();
my $ndy = 0;


my @jbsubmit = ();
my @jbdone  = ();
my @jbinfail = ();
my @jboutfail = ();
my @jbcrsfail = ();
my @jbheld = ();
my @jbcrash = ();


my @rtdone = ();
my @rtinfail = ();
my @rtoutfail = ();
my @rtcrsfail = ();
my @rtheld = ();
my @rtcrash = ();


  &StDbProdConnect();


 $JobStatusT = "JobStatus2014";


    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT where runDay >= '2015-03-12' order by runDay ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();


$arrprod[$npr] = "all2014";

my @arperiod = ("1_month","2_months","3_months","4_months","5_months","6_months","12_months");


&StDbProdDisconnect();


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);


my $qperiod = $query->param('period');
my $qprod   = $query->param('prod');


if( $qprod eq "" and $qperiod eq ""  ) {

    print $query->header();
    print $query->start_html('Production efficiency');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Efficiency of jobs processing </u></h1>\n";
    print "<br>";
    print "<br>";
    print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Production series</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prod',
	                          -values=>\@arrprod,
	                          -default=>all2014,
      			          -size =>1);


    print "<p>";
    print "</td><td>";  
    print "<h3 align=center>Period of monitoring</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'period',
                                  -values=>\@arperiod,
                                  -size =>1); 

    
    print "<p>";
    print "</td><td>";
    print "</td> </tr> </table><hr><center>";

    print "</h4>";
    print "<br>";
    print "<br>";
    print "<br>";
    print $query->submit(),"<p>";
    print $query->reset();
    print $query->endform();
    print "<br>";
    print "<br>";
    print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

    print $query->end_html();

} else{
    
  my $qqr = new CGI;

    my $qprod   = $qqr->param('prod');
    my $qperiod = $qqr->param('period');    
    
 # Tables
 $JobStatusT = "JobStatus2014";


my @ardays = ();
my @prt = ();
my $day_diff = 0;
my $nmonth = 0;

if ( $qperiod =~ /month/) {
     @prt = split("_", $qperiod);
     $nmonth = $prt[0];
     $day_diff = 30*$nmonth + 1;
  }

  $day_diff = int($day_diff);


 &StDbProdConnect();


 if($qprod eq "all2014"){

   $sql="SELECT DISTINCT date_format(submitTime, '%Y-%m-%d') as SDATE FROM $JobStatusT WHERE ( prodSeries = 'P15ic' or prodSeries = 'P15ie')  and date_format(submitTime, '%Y-%m-%d') <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(submitTime)) < ?  order by SDATE";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

         $cursor->finish();

  }else{


   $sql="SELECT DISTINCT date_format(submitTime, '%Y-%m-%d') as SDATE FROM $JobStatusT WHERE prodSeries = ?  and date_format(submitTime, '%Y-%m-%d') <> '0000-00-00' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(submitTime)) < ? order by SDATE";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

         $cursor->finish();
  }

################


@ndate = ();
$ndt = 0;

@jbsubmit = ();
@jbdone  = ();
@jbinfail = ();
@jboutfail = ();
@jbcrsfail = ();
@jbheld = ();
@jbcrash = ();

@rtdone = ();
@rtinfail = ();
@rtoutfail = ();
@rtcrsfail = ();
@rtheld = ();
@rtcrash = ();


  if($qprod eq "all2014"){

  foreach my $tdate (@ardays) {

     $ndate[$ndt] = $tdate;

  $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and (prodSeries = 'P15ic' or prodSeries = 'P15ie') ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

   my $njobs = $cursor->fetchrow ;

     $cursor->finish();

     $jbsubmit[$ndt] = $njobs;

#########

   $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND jobStatus = 'Done' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {
     $jbdone[$ndt] = $njobs;
    }else{
     $jbdone[$ndt] = 0;
    }
#########


    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND inputHpssStatus like 'error%' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbinfail[$ndt] = $njobs;
    }else{
     $jbinfail[$ndt] = 0;
    }


##########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND crsError = 'error_60' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jboutfail[$ndt] = $njobs;
    }else{
     $jboutfail[$ndt] = 0;
    }

##########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and (prodSeries = 'P15ic' or prodSeries = 'P15ie') AND (crsError = 'error_10' or crsError = 'error_50') ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbcrsfail[$ndt] = $njobs;
    }else{
     $jbcrsfail[$ndt] = 0;
    }

#########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and (prodSeries = 'P15ic' or prodSeries = 'P15ie') AND crsError = 'error_held'  ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbheld[$ndt] = $njobs;
    }else{
     $jbheld[$ndt] = 0;
    }

#########


    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND jobStatus <> 'Done' and jobStatus <> 'n/a' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute();

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbcrash[$ndt] = $njobs;
    }else{
     $jbcrash[$ndt] = 0;
    }

##########
     if($jbsubmit[$ndt] >= 1 ) {

     $rtdone[$ndt]    = ($jbdone[$ndt]/$jbsubmit[$ndt])*100;
     $rtinfail[$ndt]  = ($jbinfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtoutfail[$ndt] = ($jboutfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtcrsfail[$ndt] = ($jbcrsfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtcrash[$ndt]   = ($jbcrash[$ndt]/$jbsubmit[$ndt])*100;

     }else{
     $rtdone[$ndt]    = 0;
     $rtinfail[$ndt]  = 0;
     $rtoutfail[$ndt] = 0;
     $rtcrsfail[$ndt] = 0;
     $rtcrash[$ndt]   = 0;
     }
     $ndt++;
   }

  }else{

  foreach my $tdate (@ardays) {

     $ndate[$ndt] = $tdate;

  $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

   my $njobs = $cursor->fetchrow ;

     $cursor->finish();

     $jbsubmit[$ndt] = $njobs;

#########

   $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? AND jobStatus = 'Done' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbdone[$ndt] = $njobs;
    }else{
     $jbdone[$ndt] = 0;
    }

##########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? AND inputHpssStatus like 'error%' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbinfail[$ndt] = $njobs;
    }else{
     $jbinfail[$ndt] = 0;
    }

##########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? AND crsError = 'error_60' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jboutfail[$ndt] = $njobs;
    }else{
     $jboutfail[$ndt] = 0;
    }

##########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? AND (crsError = 'error_10' or crsError = 'error_50') ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbcrsfail[$ndt] = $njobs;
    }else{
     $jbcrsfail[$ndt] = 0;
    }

#########


    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and prodSeries = ? AND crsError = 'error_held'  ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbheld[$ndt] = $njobs;
    }else{
     $jbheld[$ndt] = 0;
    }

#########

    $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE (submitTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') and  prodSeries = ? AND jobStatus <> 'Done' and jobStatus <> 'n/a' ";

     $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qprod);

    my $njobs = $cursor->fetchrow ;

     $cursor->finish();

    if( defined $njobs) {

     $jbcrash[$ndt] = $njobs;
    }else{
     $jbcrash[$ndt] = 0;
    }
############
      if($jbsubmit[$ndt] >= 1 ) {

     $rtdone[$ndt]    = ($jbdone[$ndt]/$jbsubmit[$ndt])*100;
     $rtinfail[$ndt]  = ($jbinfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtoutfail[$ndt] = ($jboutfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtcrsfail[$ndt] = ($jbcrsfail[$ndt]/$jbsubmit[$ndt])*100;
     $rtcrash[$ndt]   = ($jbcrash[$ndt]/$jbsubmit[$ndt])*100;

     }else{
     $rtdone[$ndt]    = 0;
     $rtinfail[$ndt]  = 0;
     $rtoutfail[$ndt] = 0;
     $rtcrsfail[$ndt] = 0;
     $rtcrash[$ndt]   = 0;
     }

##########
      $ndt++;

    }

######## $qprod all2014
  }

############


############################################################

    &StDbProdDisconnect();

 my $ylabel;
 my $gtitle;
 my $max_y;
 my $min_y = 0;

    my $graph = new GD::Graph::linespoints(750,650);

    if ( ! $graph){
        print STDOUT $qqr->header(-type => 'text/plain');
        print STDOUT "Failed\n";

    } else {

 $legend[0] = "jobs done         ";
 $legend[1] = "HPSS import failed";
 $legend[2] = "HPSS export failed";
 $legend[3] = "CRS errors        ";
 $legend[4] = "jobs held         ";
 $legend[5] = "jobs crashed      ";

 @data = ();

 $max_y = 120;

      $ylabel = "Percent of jobs";
      $gtitle = "Percentage of submitted, done and failed jobs ";


#  @data = (\@ndate, \@jbsubmit, \@jbdone, \@jbinfail, \@jboutfail, \@jbcrsfail, \@jbheld, \@jbcrash );

  @data = (\@ndate, \@rtdone, \@rtinfail, \@rtoutfail, \@rtcrsfail, \@rtheld, \@rtcrash );


  my $xLabelsVertical = 1;
  my $xLabelPosition = 0;
  my $xLabelSkip = 1;
  my $skipnum = 1;


  if (scalar(@ndate) >= 40 ) {
    $skipnum = int(scalar(@ndate)/20);
        }

  $xLabelSkip = $skipnum;

       $graph->set(x_label => "Date of jobs submission",
                    y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 12,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
                    #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblack lblue lgreen lred lpurple lgray lorange marine lbrown lyellow) ],
                    line_width => 4,
                    markers => [ 2,3,4,5,6,7,8,9],
                    marker_size => 3,
                    x_label_skip => $xLabelSkip,
                    x_labels_vertical =>$xLabelsVertical,
                    );

        $graph->set_legend(@legend);
        $graph->set_legend_font(gdMediumBoldFont);
        $graph->set_title_font(gdGiantFont);
        $graph->set_x_label_font(gdGiantFont);
        $graph->set_y_label_font(gdGiantFont);
        $graph->set_x_axis_font(gdMediumBoldFont);
        $graph->set_y_axis_font(gdMediumBoldFont);

        if ( scalar(@ndate) <= 1 ) {
            print $qqr->header(-type => 'text/html')."\n";
            &beginHtml();

        } else {
            my $format = $graph->export_format;
            print header("image/$format");
            binmode STDOUT;

            print STDOUT $graph->plot(\@data)->$format();
        }
#
     }

################   last
}


###############################
#  subs and helper routines
###############################
sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}

#==============================================================================

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Production Efficiency</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production  </h1>
     

    </body>
   </html>
END
}
