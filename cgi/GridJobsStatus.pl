#!/usr/bin/env perl
#
# $Id: GridJobsStatus.pl
#
# L.Didenko
#
# GridJobsStatus.pl - browser for GRID production jobs status
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Class::Struct;

&cgiSetup();

#$dbhost="fc2.star.bnl.gov:3386";


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $nowdate = ($year+1900).$mon.$mday;


my $nst = 0;
my @prodtag = ();
my @trigset = ();
my @daqfile = ();
my @subdate= ();
my @subAtt = ();
my @daqsize = ();
my @jobprg = ();
my @globerr = ();
my @jobst = ();
my @recost = ();
my @mudstst  = ();
my @logst = ();
my @allst = ();


  &StDbProdConnect();

  $sql="SELECT distinct prodTag, datasetName, inputFileName, date_format(submissionTime, '%Y-%m-%d') as SDATE, submitAttempt, daqSizeOnSite, jobProgress, globusError, jobState, recoStatus, muDstStatus, logFileState, overallJobStates  from $JobStatusT where  overallJobStates <> 'done' order by SDATE ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute();

             while(@fields = $cursor->fetchrow) {

               $prodtag[$nst]   = $fields[0];
               $trigset[$nst]   = $fields[1];
               $daqfile[$nst]   = $fields[2];
               $subdate[$nst]   = $fields[3];
               $subAtt[$nst]    = $fields[4];
               $daqsize[$nst]   = $fields[5];
               $jobprg[$nst]    = $fields[6];
               $globerr[$nst]   = $fields[7];
               $jobst[$nst]     = $fields[8];
               $recost[$nst]    = $fields[9];
               $mudstst[$nst]   = $fields[10];
               $logst[$nst]     = $fields[11];
               $allst[$nst]   = $fields[12];

               $nst++;
    }

   $cursor->finish();

 
  &beginHtml();


########## 

    for (my $ii=0; $ii<$nst; $ii++ ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$trigset[$ii]</h3></td>
<td HEIGHT=10><h3>$prodtag[$ii]</h3></td>
<td HEIGHT=10><h3>$daqfile[$ii]</h3></td>
<td HEIGHT=10><h3>$subdate[$ii]</h3></td>
<td HEIGHT=10><h3>$subAtt[$ii]</h3></td>
<td HEIGHT=10><h3>$jobprg[$ii]</h3></td>
<td HEIGHT=10><h3>$daqsize[$ii]</h3></td>
<td HEIGHT=10><h3>$jobst[$ii]</h3></td>
<td HEIGHT=10><h3>$globerr[$ii]</h3></td>
<td HEIGHT=10><h3>$recost[$ii]</h3></td>
<td HEIGHT=10><h3>$mudstst[$ii]</h3></td>
<td HEIGHT=10><h3>$logst[$ii] </h3></td>
<td HEIGHT=10><h3>$allst[$ii]</h3></td>
</TR>
END

}


    &StDbProdDisconnect();

 &endHtml();


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
          <title>GRID production jobs status</title> 
    </head>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>GRID production jobs status </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<br>
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger set name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod <br>tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Input file name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Date of submission</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Submit attempt</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Job progress</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Input file size on site</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Job state</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Globus error</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Reco status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>MuDst status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Log file status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Overral job status</h3></B></TD>
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
<!-- Created: Thu December 26 2013 -->
<!-- hhmts start -->
Last modified: 2013-12-26
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
