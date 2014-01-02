#!/usr/bin/env perl
#
# $Id: CRSsummary.pl
#
# L.Didenko
#
# CRSsummary.pl - current summary of jobs states on CRS farm
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Time::Local;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $crsJobStatusT = "newcrsJobState";

my $query = new CGI;

($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $nowdate = ($year+1900).$mon.$mday;

my $thisdate = ($year+1900)."-".$mon."-".$mday." ".$hour."%";

my $ncreate  = 0;
my $nsubmit  = 0;
my $nqueued  = 0;
my $nstaging = 0;
my $nimport  = 0;
my $nrunning = 0;
my $nexport  = 0;
my $ndone    = 0;
my $nerror   = 0;
my $nkilled  = 0;
my $nheld    = 0;


   &StcrsdbConnect();

  $sql="SELECT created, submitted, queued, staging, importing, running, exporting, done, error, killed, held  from $crsJobStatusT where sdate like '$thisdate' ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $ncreate  = $fields[0];
          $nsubmit  = $fields[1];
          $nqueued  = $fields[2];
          $nstaging = $fields[3];
          $nimport  = $fields[4];
          $nrunning = $fields[5];
          $nexport  = $fields[6];
          $ndone    = $fields[7];
          $nerror   = $fields[8];
          $nkilled  = $fields[9];
          $nheld    = $fields[10];
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

 &endHtml();


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
 <h2 ALIGN=CENTER> <B>CRS jobs states summary</h2>
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

