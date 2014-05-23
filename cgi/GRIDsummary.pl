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

my $query = new CGI;

    if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

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

my @nnone      = ();
my @nsubmit    = ();
my @nrunning   = ();
my @ndone      = ();
my @nidle      = ();
my @nnotInQ    = ();
my @nheld      = ();
my @prodtag    = ();
my @trigset    = ();
my @recosucces = ();
my @recofailed = ();
my @recounknown = ();
my $nset = 0;
my @hpssset     = ();
my @overstat = ();
my @ndaq = ();
my @nmisdst = ();

my $prtag;
my $dtset;

   &StdbConnect();

    $sql="SELECT distinct prodTag, datasetName from $JobStatusT ";

           $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $prodtag[$nset]  = $fields[0];
         $trigset[$nset]  = $fields[1];
         $nset++; 

         }
 
  $cursor->finish();


  for ($ii = 0; $ii <$nset; $ii++) {

  $prtag = $prodtag[$ii];
  $dtset = $trigset[$ii];

   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'submitted' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nsubmit[$ii]  = $fields[0];

         }
 
  $cursor->finish();


   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'running' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nrunning[$ii]  = $fields[0];

         }
 
  $cursor->finish();


   $sql="SELECT count(jobState) from $JobStatusT where jobState = 'done' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $ndone[$ii]  = $fields[0];

         }
 
  $cursor->finish();

  $sql="SELECT count(jobState) from $JobStatusT where jobState = 'idle' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nidle[$ii]  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'held' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nheld[$ii]  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'notInQ' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nnotInQ[$ii]  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(jobState) from $JobStatusT where jobState = 'none' and prodTag = '$prtag' and datasetName = '$dtset' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $nnone[$ii]  = $fields[0];

         }
 
  $cursor->finish();


 $sql="SELECT count(recoStatus) from $JobStatusT where recoStatus = 'completed' and prodTag = '$prtag' and datasetName = '$dtset' ";

         $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
         $cursor->execute();

        while(@fields = $cursor->fetchrow) {

         $recosucces[$ii]  = $fields[0];

         }
 
  $cursor->finish();

 $sql="SELECT count(recoStatus) from $JobStatusT where recoStatus <> 'completed' and recoStatus <> 'unknown' and prodTag = '$prtag' and datasetName = '$dtset' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $recofailed[$ii]  = $fields[0];

         }
   $cursor->finish();


  $sql="SELECT count(recoStatus) from $JobStatusT where recoStatus = 'unknown' and jobState = 'done' and prodTag = '$prtag' and datasetName = '$dtset' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $recounknown[$ii]  = $fields[0];

         }
   $cursor->finish();


  $sql="SELECT count(inputFileName) from $JobStatusT where jobProgress = 'mudst_sunk' and prodTag = '$prtag' and datasetName = '$dtset' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $hpssset[$ii]  = $fields[0];

         }
   $cursor->finish();


  $sql="SELECT count(inputFileName) from $JobStatusT where overallJobStates = 'done' and prodTag = '$prtag' and datasetName = '$dtset' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $overstat[$ii]  = $fields[0];

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where inputFileExists = 'yes' and prodTag = '$prtag' and datasetName = '$dtset' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $ndaq[$ii]  = $fields[0];

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where  jobState = 'done' and recoStatus <> 'unknown' and prodTag = '$prtag' and datasetName = '$dtset' and ( muDstStatus = 'missing' or  muDstStatus = 'corrupted')  ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $nmisdst[$ii]  = $fields[0];

         }
   $cursor->finish();



  }




  &beginHtml();

###########

   for ($ik = 0; $ik <$nset; $ik++) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$trigset[$ik]</h3></td>
<td HEIGHT=10><h3>$prodtag[$ik]</h3></td>
<td HEIGHT=10><h3>$ndaq[$ik]</h3></td>
<td HEIGHT=10><h3>$nsubmit[$ik]</h3></td>
<td HEIGHT=10><h3>$nrunning[$ik]</h3></td>
<td HEIGHT=10><h3>$ndone[$ik]</h3></td>
<td HEIGHT=10><h3>$nidle[$ik]</h3></td>
<td HEIGHT=10><h3>$nheld[$ik]</h3></td>
<td HEIGHT=10><h3>$nnotInQ[$ik]</h3></td>
<td HEIGHT=10><h3>$nnone[$ik]</h3></td>
<td HEIGHT=10><h3>$recosucces[$ik]</h3></td>
<td HEIGHT=10><h3>$recofailed[$ik]</h3></td>
<td HEIGHT=10><h3>$recounknown[$ik]</h3></td>
<td HEIGHT=10><h3>$hpssset[$ik]</h3></td>
<td HEIGHT=10><h3>$nmisdst[$ik]</h3></td>
<td HEIGHT=10><h3>$overstat[$ik]</h3></td>
</TR>
END
 }

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
          <title>GRID jobs states summary</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>GRID production jobs states summary</h2>
 <h3 ALIGN=CENTER> Status on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger Set</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>N daq files on disk</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>SUBMITTED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>RUNNING</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>FINISH</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>IDLE</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>HELD</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>notInQ</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>NOT SUBMITTED</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Reco success</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Reco failed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Reco unknown</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Sunk to HPSS</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Missing MuDst</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>All done</h3></B></TD>
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
<!-- Created: March 12 2014 -->
<!-- hhmts start -->
Last modified: 2014-04-28
<!-- hhmts end -->
  </body>
</html>
END

}

##############

