#!/usr/bin/env perl 
#
# $Id: fastDEVtestStatus.pl
#
# L. Didenko 
#
# fastDEVtestStatus.pl - script to browse results of fast nightly test status for DEV release
# 
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Time::Local;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="LibraryJobs";


my ($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday;

my $nowdate = ($year+1900)."-".$mon."-".$mday ." ".$hour.":".$min.":".$sec ;

my @arperiod = ("week","1_month","2_months","6_months");


my $JobStatusT = "fastJobsStatus";  


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qperiod = $query->param('period');

if( $qperiod eq "" ) {
    print $query->header();
    print $query->start_html('Fast DEV test status');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Fast DEV nightly test status </u></h1>\n";
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
    print "<h3 align=center> Period to query test results <br> </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'period',
                                  -values=>\@arperiod,
                                  -default=>week,
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
 
  my $qperiod = $qqr->param('period');
 
    
 # Tables
      
 $JobStatusT = "fastJobsStatus";


  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $nday = 0;
  my @ardays = ();
  my $tdate;
  my $nstat = 0;

  my @autStatus = ();
  my @autInfo = ();
  my @jbstatus = ();
  my @submTime = ();
  my @complTime = ();
  my @testErr = ();
  my @testday = ();
  my $autostat = 0;
  my $teststat = 0;  


 print $qqr->header;
 print $qqr->start_html('Fast DEV test status');
 print "<body bgcolor=\"cornsilk\">\n";


 &StDbConnect();

     if( $qperiod eq "week") {
	$day_diff = 8;
  
    } elsif ( $qperiod =~ /month/) {
	@prt = split("_", $qperiod);
	$nmonth = $prt[0];
	$day_diff = 30*$nmonth + 1; 
    }

    $sql="SELECT DISTINCT date_format(entryDate, '%Y-%m-%d') as PDATE, autoBuildStatus, autoBuildInfo, testStatus, testInfo, testSubmitTime, testCompleteTime  FROM $JobStatusT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(entryDate)) <= $day_diff  order by PDATE ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

     while(@fields = $cursor->fetchrow) {

     $testday[$nday]   = $fields[0];
     $autStatus[$nday] = $fields[1];
     $autInfo[$nday]   = $fields[2];
     $jbstatus[$nday]  = $fields[3];
     $testErr[$nday]   = $fields[4];
     $submTime[$nday]  = $fields[5];
     $complTime[$nday] = $fields[6];
     $nday++;

    }

   $cursor->finish();


   &beginHtml();

##############################

   for (my $ii=0; $ii<$nday; $ii++ ) {

       if ( $autStatus[$ii]== 0 ) {
	   $autostat = "failed";
       }elsif($autStatus[$ii] == 1 ) {
           $autostat = "success";
       }
       if ($jbstatus[$ii] == 0 ) {
         $teststat = "not submitted";
      }elsif($jbstatus[$ii] == 1) {
         $teststat = "submitted";      
      }elsif($jbstatus[$ii] == 2) {
         $teststat = "success";
      }elsif($jbstatus[$ii] == 3) {
         $teststat = "failed"; 
      }

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$testday[$ii]</h3></td>
<td HEIGHT=10><h3>$autostat</h3></td>
<td HEIGHT=10><h3>$autInfo[$ii]</h3></td>
<td HEIGHT=10><h3>$teststat</h3></td>
<td HEIGHT=10><h3>$testErr[$ii]</h3></td>
<td HEIGHT=10><h3>$submTime[$ii]</h3></td>
<td HEIGHT=10><h3>$complTime[$ii]</h3></td>
</TR>
END

   }


    &StDbDisconnect();

 print $qqr->end_html;

 &endHtml();
}

######################
sub StDbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub beginHtml {

print <<END;

  <html>

    <head>
          <title>Fast DEV test status</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Fast DEV nightly test status for the period of $qperiod</h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Date</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>AutoBuild status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>AutoBuild info</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Test status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Error message</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Test submit time</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Test complete time</h3></B></TD>
</TR>
    </body>
END
}


#####################

sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: January 10 2014 -->
<!-- hhmts start -->
Last modified: 2014-01-14
<!-- hhmts end -->
  </body>
</html>
END

}

}
