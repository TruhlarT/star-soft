#!/usr/bin/env perl
#
# $Id: GRIDsummary.2017.cgi
#
# L.Didenko
#
# GRIDsummary.2017.pl - current summary of jobs states on GRID production farm
#
########################################################################################

use DBI;
use Time::Local;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2018";

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


my $jobs_html = "/star/u/starlib/gridsum/GRIDsummary.2017.html";

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
my @nevents = ();
my @nmislog = ();
my @nodaq   = ();
my @globuserr = ();
my @avgcpu = ();

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


  $sql="SELECT count(inputFileName) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and  jobProgress = 'mudst_sunk'  ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $hpssset[$ii]  = $fields[0];

         }
   $cursor->finish();


  $sql="SELECT count(inputFileName) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and overallJobStates =  'done' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $overstat[$ii]  = $fields[0];

         }
   $cursor->finish();

  $sql="SELECT avg(cpuPerEvent) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and recoStatus = 'completed' and cpuPerEvent > 0 ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $avgcpu[$ii]  = sprintf("%.2f\n\n",$fields[0]);

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and inputFileExists = 'yes' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $ndaq[$ii]  = $fields[0];

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and inputFileExists = 'no' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $nodaq[$ii]  = $fields[0];

         }
   $cursor->finish();




 $sql="SELECT count(inputFileName) from $JobStatusT where  prodTag = '$prtag' and datasetName = '$dtset' and  jobState = 'done'  and ( muDstStatus = 'missing' or  muDstStatus = 'corrupted')  ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $nmisdst[$ii]  = $fields[0];

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where  prodTag = '$prtag' and datasetName = '$dtset' and  jobState = 'done' and (logFileState = 'missing' or logFileState = 'truncated' )  ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $nmislog[$ii]  = $fields[0];

         }
   $cursor->finish();


 $sql="SELECT count(inputFileName) from $JobStatusT where  prodTag = '$prtag' and datasetName = '$dtset' and  globusError <> ' ' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $globuserr[$ii]  = $fields[0];

         }
   $cursor->finish();



 $sql="SELECT sum(Nevents) from $JobStatusT where prodTag = '$prtag' and datasetName = '$dtset' and jobState = 'done' and  muDstStatus = 'present' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $nevents[$ii]  = $fields[0];

         }
   $cursor->finish();


  }



  &beginHtml();

###########

   for ($ik = 0; $ik <$nset; $ik++) {


print HTML "<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">\n";
print HTML "<td HEIGHT=10><h3>$trigset[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$prodtag[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$ndaq[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=mdaq\">$nodaq[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nsubmit[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nrunning[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$ndone[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nidle[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nheld[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nnotInQ[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nnone[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$recosucces[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$avgcpu[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=jstat\">$recofailed[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=unknown\">$recounknown[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=mglob\">$globuserr[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$hpssset[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$nevents[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=mudst\">$nmisdst[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3><a href=\"http://www.star.bnl.gov/devcgi/RetriveGridJobs.pl?trigs=$trigset[$ik];prod=$prodtag[$ik];jflag=mlog\">$nmislog[$ik]</h3></td>\n";
print HTML "<td HEIGHT=10><h3>$overstat[$ik]</h3></td>\n";
print HTML "</TR>\n";

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

open (HTML,">$jobs_html") or die "can't write to $jobs_html ";
print HTML "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n";

print HTML "<html>\n";
print HTML "    <head>\n";
print HTML "    <title>GRID jobs states summary for run 2017-2018</title>\n";
print HTML "    </head>>\n";

print HTML "    <body BGCOLOR=\"cornsilk\">\n";
print HTML "  <h2 ALIGN=CENTER> <B>GRID production jobs states summary for year 2017 - 2018 productions </h2>\n";
print HTML "  <h3 ALIGN=CENTER> Status on $todate</h3>\n";
print HTML " <br>\n";
print HTML " <TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">\n";
print HTML " <TR>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger Set</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod Tag</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Input files on disk </h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Missing input files </h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Jobs SUBMITTED</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Jobs RUNNING</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Jobs FINISH</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Jobs IDLE</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Jobs HELD</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Jobs notInQ</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Jobs NOT SUBMITTED</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Reco success</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Average CPU/evt sec</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Reco failed</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Reco unknown</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Globus error</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>MuDst/picoDst<br> sunk to HPSS</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>N events produced</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Missing <br>MuDst,<br>picoDst</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Missing log file</h3></B></TD>\n";
print HTML "<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Jobs all done</h3></B></TD>\n";
print HTML "</TR>\n";
print HTML "</body>\n";

}

#####################

sub endHtml {
my $Date = `date`;

print HTML "</TABLE>\n";
print HTML "      <h5>\n";
print HTML "      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";
print HTML "<!-- Created: December 28 2017 -->\n";
print HTML "<!-- hhmts start -->\n";
print HTML "Last modified: 2018-03-12\n";
print HTML "<!-- hhmts end -->\n";
print HTML "  </body>\n";
print HTML "</html>\n";
 close (HTML);

}

##############

