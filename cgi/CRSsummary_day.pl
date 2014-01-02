#!/usr/bin/env perl
#
# $Id: CRSsummary_day.pl
#
# L.Didenko
#
# CRSsummary_day.pl - summary of jobs states on CRS farm on daily bases
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Class::Struct;
use Time::Local;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $crsJobStatusT = "newcrsJobState";

#&cgiSetup();

my $query = new CGI;

($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $nowdate = ($year+1900)."-".$mon."-".$mday ;

my $ncreate = 0;
my $nsubmit = 0;
my $nqueued = 0;
my $nstaging = 0;
my $nimport = 0;
my $nrunning = 0;
my $nexport = 0;
my $ndone = 0;
my $nerror = 0;
my $nkilled = 0;
my $nheld = 0;
my @ardays = ();
my $nd = 0;
my @rvdays = ()


   &StcrsdbConnect();


   $sql="SELECT DISTINCT  date_format(sdate, '%Y-%m-%d') as PDATE  FROM $crsJobStatusT order by sdate ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mhr = $cursor->fetchrow() ) {

          $ardays[$nd] = $mhr;
          $nd++;
       }
    $cursor->finish();

    @rvdays = reverse @ardays ;

  &StcrsdbDisconnect();


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qday = $query->param('pday');

if( $qday eq "" ) {
    print $query->header();
    print $query->start_html('CRS jobs status');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>CRS jobs states summary on daily bases</u></h1>\n";
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
    print "<h3 align=center> Date of production<br></h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pday',
                                  -values=>\@rvdays,
                                  -default=>\$nowdate,
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

  my $qday = $qqr->param('pday');
  chop $qday;
  my $qdate = $qday."%";

 print $qqr->header;
 print $qqr->start_html('CRS jobs state summary');
 print "<body bgcolor=\"cornsilk\">\n";



   &StcrsdbConnect();


  $sql="SELECT sum(created), sum(submitted), sum(queued), sum(staging), sum(importing), sum(running), sum(exporting), sum(done), sum(error), sum(killed), sum(held)  from $crsJobStatusT where sdate like $qdate ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $ncreate = $fields[0];
          $nsubmit = $fields[1];
          $nqueued = $fields[2];
          $nstaging = $fields[3];
          $nimport = $fields[4];
          $nrunning = $fields[5];
          $nexport = $fields[6];
          $ndone = $fields[7];
          $nerror = $fields[8];
          $nkilled = $fields[9];
          $nheld = $fields[10];
         }


  &beginHtml();

###########

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$ncreate</h3></td>
<td HEIGHT=10><h3>$nsubmit</h3></td>
<td HEIGHT=10><h3>$nqueued</h3></td>
<td HEIGHT=10><h3>$nstaging</h3></td>
<td HEIGHT=10><h3>$nimport</h3></td>
<td HEIGHT=10><h3>$nrunning</h3></td>
<td HEIGHT=10><h3>$nexport</h3></td>
<td HEIGHT=10><h3>$ndone</h3></td>
<td HEIGHT=10><h3>$nerror</h3></td>
<td HEIGHT=10><h3>$nkilled</h3></td>
<td HEIGHT=10><h3>$nheld</h3></td>
</TR>
END

 &StcrsdbDisconnect();

 print $qqr->end_html;

 &endHtml();

}

#==============================================================================

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
          <title>CRS jobs states summary</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>CRS jobs states summary for $qday </h2>
 <h3 ALIGN=CENTER> Status on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>CREATED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>SUBMITTED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>QUEUED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>STAGING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>IMPORTING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>RUNNING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>EXPORTING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>DONE</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>ERROR</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>KILLED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>HELD</h3></B></TD>
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
<!-- Created: January 8 2014 -->
<!-- hhmts start -->
Last modified: 2014-01-08
<!-- hhmts end -->
  </body>
</html>
END

}

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
