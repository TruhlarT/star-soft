#!/usr/bin/env perl 
#
# $Id: TrigProdStatus.cgi
#
# L. Didenko 
#
# TrigProdStatus.cgi - script to browse trigger/subsystem test production status
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
$dbname="operation";


my ($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday;

my $nowdate = ($year+1900)."-".$mon."-".$mday ." ".$hour.":".$min.":".$sec ;

my $TrigRequestT = "TrigProdRequest";  

my @runs = ();
my @streams = ();
my @datast = ();
my @prodtg = ();
my @nfl_subm = ();
my @nfl_proc = ();
my @submstat = ();
my @runstat = ();
my @reqtime = ();
my @fintime = ();
my $nl = 0;


 my $query = new CGI;

if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };



 &StDbConnect();

  $sql="SELECT DISTINCT runnumber, stream, dataset, prodtag, Nfiles_subm, Nfiles_proc, submit, done, requestTime, finishTime from $TrigRequestT ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $runs[$nl]     = $fields[0];
         $streams[$nl]  = $fields[1];
         $datast[$nl]   = $fields[2];
         $prodtg[$nl]   = $fields[3];
         $nfl_subm[$nl] = $fields[4];
         $nfl_proc[$nl] = $fields[5];
         $submstat[$nl] = $fields[6];
         $runstat[$nl]  = $fields[7];
         $reqtime[$nl]  = $fields[8];
         $fintime[$nl]  = $fields[9];

         $nl++; 

   }

  $cursor->finish();


##############

  &beginHtml();

 for (my $ii = 0; $ii < $nl; $ii++) {

     if ($submstat[$ii] eq "no" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"pink\">
<td HEIGHT=10>$runs[$ii]</td>
<td HEIGHT=10>$datast[$ii]</td>
<td HEIGHT=10>$streams[$ii]</td>
<td HEIGHT=10>$prodtg[$ii]</td>
<td HEIGHT=10>$nfl_subm[$ii]</td>
<td HEIGHT=10>$nfl_proc[$ii]</td>
<td HEIGHT=10>$submstat[$ii]</td>
<td HEIGHT=10>$runstat[$ii]</td>
<td HEIGHT=10>$reqtime[$ii]</td>
<td HEIGHT=10>$fintimeime[$ii]</td>
</TR>
END

     }elsif($submstat[$ii] eq "yes" and $runstat[$ii] eq "no" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"blue\">
<td HEIGHT=10>$runs[$ii]</td>
<td HEIGHT=10>$datast[$ii]</td>
<td HEIGHT=10>$streams[$ii]</td>
<td HEIGHT=10>$prodtg[$ii]</td>
<td HEIGHT=10>$nfl_subm[$ii]</td>
<td HEIGHT=10>$nfl_proc[$ii]</td>
<td HEIGHT=10>$submstat[$ii]</td>
<td HEIGHT=10>$runstat[$ii]</td>
<td HEIGHT=10>$reqtime[$ii]</td>
<td HEIGHT=10>$fintimeime[$ii]</td>
</TR>
END


 }elsif($submstat[$ii] eq "yes" and $runstat[$ii] eq "yes" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10>$runs[$ii]</td>
<td HEIGHT=10>$datast[$ii]</td>
<td HEIGHT=10>$streams[$ii]</td>
<td HEIGHT=10>$prodtg[$ii]</td>
<td HEIGHT=10>$nfl_subm[$ii]</td>
<td HEIGHT=10>$nfl_proc[$ii]</td>
<td HEIGHT=10>$submstat[$ii]</td>
<td HEIGHT=10>$runstat[$ii]</td>
<td HEIGHT=10>$reqtime[$ii]</td>
<td HEIGHT=10>$fintimeime[$ii]</td>
</TR>
END

  }

 }


 &StDbDisconnect();


 &endHtml();

 

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
          <title>Status of fast trigger test production</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER>Status of fast production for trigger/subsystem evaluation</h2>
 <h3 ALIGN=CENTER> Status on $nowdate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Runnumber</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"25%\" HEIGHT=60><B><h3>Trigger setup</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Stream</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.files submitted</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.files processed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Submit status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Complete status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=60><B><h3>Submit time</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
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
<!-- Created: November 12 2014 -->
<!-- hhmts start -->
Last modified: 2014-11-14
<!-- hhmts end -->
  </body>
</html>
END

}

