#!/usr/bin/env perl
#
# $Id: GRIDsummary.pl
#
# L.Didenko
#
# GRIDsummary.pl - current summary of jobs states on GRID production farm
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
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

&cgiSetup();

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

my $nnone    = 0;
my $nsubmit  = ();
my $nrunning = ();
my $ndone    = ();
my $nidle    = ();
my $nnotInQ  = ();
my $nheld    = ();

   &StdbConnect();

   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'submitted' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nsubmit  = $fields[0];

         }
 
  $cursor->finish();


   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'running' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nrunning  = $fields[0];

         }
 
  $cursor->finish();


   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'done' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $ndone  = $fields[0];

         }
 
  $cursor->finish();

  $sql="SELECT count(jobState) from $JobStatusT where jobState = 'idle' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nidle  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'held' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nheld  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'notInQ' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nnotInQ  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'none' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nnone  = $fields[0];

         }
 
  $cursor->finish();


  &beginHtml();

###########

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$nsubmit</h3></td>
<td HEIGHT=10><h3>$nrunning</h3></td>
<td HEIGHT=10><h3>$ndone</h3></td>
<td HEIGHT=10><h3>$nidle</h3></td>
<td HEIGHT=10><h3>$nheld</h3></td>
<td HEIGHT=10><h3>$nnotInQ</h3></td>
<td HEIGHT=10><h3>$nnone</h3></td>

</TR>
END


  &StdbDisconnect();

 &endHtml();


#==============================================================================

######################
sub StdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StdbDisconnect {
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
 <h2 ALIGN=CENTER> <B>Current CRS jobs states summary</h2>
 <h3 ALIGN=CENTER> Status on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>SUBMITTED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>RUNNING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>DONE</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>IDLE</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>HELD</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>notInQ</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>NOT SUBMITTED</h3></B></TD>
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
