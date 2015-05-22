#!/usr/local/bin/perl
#!/usr/bin/env perl
#
# $Id:
#
# $Log:  prodEffcPlot.cgi
#
# L. Didenko
# Production efficiency plot  
# 
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
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

my $nowdate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my $pryear = "2014";


my @arrprod = ();
my @trigs = ();
my @ndate = ();
my $ndt = 0;
my $npr = 0;
my $ntr = 0;

my @prt = ();
my @ardays = ();
my @data = ();


my @jbsubmit = ();
my @jbdone  = ();
my @jbinfail = ();
my @jboutfail = ();
my @jbcrsfail = ();
my @jbheld = ();
my @jbcrash = ();


my $JobStatusT = "JobStatus2014";

 &StDbProdConnect();


   $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT where runDay >= '2015-03-15' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( my $mpr = $cursor->fetchrow() ) {
	   print "Production tag  ",$mpr, "\n";

          $arrprod[$npr] = $mpr;
          $npr++;
        }
    $cursor->finish();

   $arrprod[$npr] = "all2014";

   $sql="SELECT DISTINCT trigsetName  FROM $JobStatusT where runDay >= '2015-03-15'";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( my $mpr = $cursor->fetchrow() ) {

	   print "Dataset name  ",$mpr, "\n";

          $trigs[$ntr] = $mpr;
          $ntr++;
       }
    $cursor->finish();

   $trigs[$ntr] = "all";


my @arperiod = ("1_month","2_months","3_months","4_months","5_months","6_months","12_months");

my @arrate = ("cpu","rtime/cpu","exectime","events","njobs")

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

#my $pryear = $query->param('pyear');

my $qperiod = $query->param('period');
my $qprod   = $query->param('prod');
my $srate   = $query->param('prate');


if( $qprod eq "" and $qperiod eq ""  and $srate eq "" ) {

    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Distributions of CPU/evt, RealTime/CPU, total time of jobs execution, number of events and jobs processed per day </u></h1>\n";
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
    print "<h3 align=center> CPU/evt, Realtime/CPU, <br> total time of job's execution, <br> number of events and <br>jobs processed per day</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
                                  -values=>\@arrate,
                                  -default=>cpu,
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
    my $srate   = $qqr->param('prate');
    

}







############################

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
          <title>Production size distrubution</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production </h1>


    </body>
   </html>
END
}

