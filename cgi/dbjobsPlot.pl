#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# dbjobsPlot.pl to make plots of number of failed jobs due to DB connection problem and total execution time
# what job spent trying to connect to DB server.
#
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Mysql;


#$dbhost="fc2.star.bnl.gov:3386";
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

my $nowdate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my @prodyear = ("2012","2013");


my @arperiod = ( );
my @arrate = ("njobs", "jobstime");

my @arrprod = ();
my $npr = 0;
my @ardays = ();
my @jbcount = (); 
my @jbscount = (); 
my @avgtime = ();
my @jbstime = ();
my @jbtime = ();
my @numjobs = ();
my $mpr;
my $pryear = "2012";

my @ndate = ();
my $ndt = 0;

 
 my @arperiod = ("week","1_month","2_months","3_months","4_months","5_months","6_months");

  &StDbProdConnect();

  
$JobStatusT = "JobStatus2012";  

    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qprod = $query->param('prod');
my $qperiod = $query->param('period');
my $qjob = $query->param('pjob');

if( $qperiod eq "" and $qprod eq "" and $qjob eq "" ) {
    print $query->header();
    print $query->start_html('Production Jobs failure');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production jobs failed due to DB connection problem </u></h1>\n";
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
    print "<h3 align=center> Production series <br></h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prod',
	                          -values=>\@arrprod,
	                          -default=>P12id,
      			          -size =>1);


   print "<p>";
    print "</td><td>";
    print "<h3 align=center> Number of failed jobs</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pjob',
                                  -values=>\@arrate,
                                  -default=>njobs,
                                  -size =>1);


    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Period of monitoring <br> </h3>";
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

 }else{

  my $qqr = new CGI;

    my $qprod = $qqr->param('prod');
    my $qperiod = $qqr->param('period');
    my $qjob = $qqr->param('pjob');


 # Tables

 if( $qprod =~ /P12/ ) {$pryear = "2012"};
 if( $qprod =~ /P13/ ) {$pryear = "2013"};

#    $JobStatusT = "JobStatus".$pryear;

  $JobStatusT = "JobStatus2012";

  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $myday;
  my $nday = 0;
  my $nstat = 0;
  my $mycount;

 @ardays = ();

 &StDbProdConnect();


#    if($pryear eq "2009") {
#       $nowdate = "2009-12-31";
#    } else {
        $nowdate = $todate;
#    }

     if( $qperiod eq "week") {
        $day_diff = 7;

    } elsif ( $qperiod =~ /month/) {
        @prt = split("_", $qperiod);
        $nmonth = $prt[0];
        $day_diff = 30*$nmonth + 1;
    }

    $day_diff = int($day_diff);

     if( $qperiod eq "week") {

    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT WHERE prodSeries = ?  AND runDay <> '0000-00-00' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) <= $day_diff  order by PDATE ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;

        $nday++;
    }

##############################

   }else{

    $sql="SELECT DISTINCT runDay  FROM $JobStatusT WHERE prodSeries = ?  AND  runDay <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(runDay)) < ?  order by runDay";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

   }


##################################### jobs count with DB connection failure

 @ndate = ();
 $ndt = 0;
 @jbscount = ();
 @jbcount = ();
 @jbstime = ();
 @jbtime = ();
 @numjobs = ();
 $nstat = 0;
 @avgtime = ();

   if( $qjob eq "njobs" ) {

   foreach my $tdate (@ardays) {
        $jbscount[$ndt] = 0;
        $ndate[$ndt] = $tdate;

     $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE  prodSeries = ? and jobStatus = 'DB connection failed' and createTime like '$tdate%' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($mycount = $cursor->fetchrow) {
        $jbcount[$nstat] = $mycount;
        $nstat++;
    }

   }else{

  $sql="SELECT count(jobfileName) FROM $JobStatusT WHERE  prodSeries = ? and jobStatus = 'DB connection failed' and runDay = '$tdate
' ";


   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($mycount = $cursor->fetchrow) {
        $jbcount[$nstat] = $mycount;
        $nstat++;
    }
 }


   if($nstat >= 1) {
   $jbscount[$ndt] = $jbcount[$nstat-1];
      }
  $ndt++;

 }# foreach tdate


 }elsif( $qjob eq "jobstime" ) {

$nstat = 0;
$ndt = 0;
@ndate = ();


   foreach my $tdate (@ardays) {

        $ndate[$ndt] = $tdate;
        $jbstime[$ndt] = 0;
        $numjobs[$ndt] = 0;
        $avgtime[$ndt] = 0;
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT exectime FROM $JobStatusT WHERE  prodSeries = ? and jobStatus = 'DB connection failed' and createTime like '$tdate%' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($mycount = $cursor->fetchrow) {
        $jbstime[$ndt] = $jbstime[$ndt] + $mycount;
        $nstat++;
#   $numjobs[$ndt] = $nstat ;
    }
   $numjobs[$ndt] = $nstat ;

   }else{

  $sql="SELECT exectime FROM $JobStatusT WHERE  prodSeries = ? and jobStatus = 'DB connection failed' and runDay = '$tdate' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($mycount = $cursor->fetchrow) {
        $jbstime[$ndt] = $jbstime[$ndt] + $mycount;
        $nstat++;
#    $numjobs[$ndt] = $nstat ;
    }
    $numjobs[$ndt] = $nstat ;
 }

    if($numjobs[$ndt] >=1 ) {
    $avgtime[$ndt] = int($jbstime[$ndt]/$numjobs[$ndt] + 0.5 );
  }else{
    $avgtime[$ndt] = 0;
  }
    $ndt++;
  }# foreach tdate


  }

    &StDbProdDisconnect();

 my @data = ();
 my $ylabel;
 my $gtitle;

    my $graph = new GD::Graph::linespoints(750,650);

    if ( ! $graph){
        print STDOUT $qqr->header(-type => 'text/plain');
        print STDOUT "Failed\n";

    } else {

       if ( $qjob eq "njobs" ) {

    @data = ();

       if( $qperiod eq "week") {

       $ylabel = "Number of failed jobs per hour";
       $gtitle = "Number of jobs failed due to DB connections problem for $qperiod period";

      }else{

       $ylabel = "Number of failed jobs per day";
       $gtitle = "Number of jobs failed due to DB connections problem for $qperiod period";
      }

  @data = (\@ndate, \@jbscount ) ;

  }elsif(  $qjob eq "jobstime" ) {

  @data = ();

       if( $qperiod eq "week") {

       $ylabel = "Average time of jobs execution  per hour";
       $gtitle = "Average time of jobs execution  for $qperiod period";

         }else{

       $ylabel = "Average time of jobs execution jobs per day";
       $gtitle = "Average time of jobs execution for $qperiod period";

         }

  @data = (\@ndate, \@avgtime ) ;

  }

########

        my $xLabelsVertical = 1;
        my $xLabelPosition = 0;
        my $xLabelSkip = 1;
        my $skipnum = 1;

        $min_y = 0;

        if (scalar(@ndate) >= 60 ) {
            $skipnum = int(scalar(@ndate)/40);
        }

        $xLabelSkip = $skipnum;

        $graph->set(x_label => "Datetime of job's completion",
                    y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
                    #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange marine lred lblack lyellow lbrown lgray) ],
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


#####
  }
exit;
############


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
          <title>Production jobs failed due to DB connection problem</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No failed jobs for $qprod production and $qperiod period </h1>
     

    </body>
   </html>
END
}
