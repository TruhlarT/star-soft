#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveGridJobs.pl
#
# Retrive failed GRID production jobs
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
#use Mysql;
use Class::Struct;


($sec,$min,$hour,$mday,$mon,$year) = localtime();

 $mon++;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

my $query = new CGI;

    if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };


my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');
my $qflag = $query->param('jflag');

my @jbfName = ();
my @jbEvent = ();
my @jbStatus  = ();
my @jbftime = ();
my @jbsubdate = ();
my @jbstate = ();
my @jbmudst = ();

my $nn = 0;
my $ii = 0;


  &StDbProdConnect();

   if( $qflag eq "jstat") {
 
  &beginJbHtml(); 

 $nn = 0; 

 $sql="SELECT inputFileName, recoStatus, nEvents, submissionTime, jobFinishTime from $JobStatusT where recoStatus <> 'completed' and recoStatus <> 'unknown' and prodTag = '$qprod' and datasetName = '$qtrg' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $jbfName [$nn]  = $fields[0];
          $jbStatus[$nn]  = $fields[1];
          $jbEvent[$nn]   = $fields[2];
          $jbsubdate[$nn] = $fields[3];
          $jbftime[$nn]   = $fields[4];
	  $nn++;

         }

   $cursor->finish();

   
 }elsif($qflag eq "unknown") {

   &beginUnHtml();

  $nn = 0; 

 $sql="SELECT inputFileName, jobState, submissionTime from $JobStatusT where recoStatus = 'unknown' and prodTag = '$qprod' and datasetName = '$qtrg' ";

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $jbfName [$nn]  = $fields[0];
          $jbStatus[$nn]  = $fields[1];
          $jbsubdate[$nn] = $fields[2];
	  $nn++;

         }

   $cursor->finish();

 
 }elsif($qflag eq "mudst") {

   &beginMuHtml();

  $nn = 0; 

  $sql="SELECT inputFileName, recoStatus, nEvents, submissionTime, jobFinishTime from $JobStatusT where prodTag = '$qprod' and datasetName = '$qtrg' and recoStatus <> 'unknown' and ( muDstStatus = 'missing' or  muDstStatus = 'corrupted')" ;

          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $jbfName [$nn]  = $fields[0];
          $jbStatus[$nn]  = $fields[1];
          $jbEvent[$nn]   = $fields[2];
          $jbsubdate[$nn] = $fields[3];
          $jbftime[$nn]   = $fields[4];
	  $nn++;

         }

   $cursor->finish();


 }elsif($qflag eq "mlog") {

   &beginLogHtml();

  $nn = 0; 

 $sql="SELECT inputFileName, jobProgress, submissionTime, muDstStatus  from $JobStatusT where  prodTag = '$qprod' and datasetName = '$qtrg' and  jobState = 'done' and (logFileState = 'missing' or logFileState = 'truncated' )  ";


          $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
          $cursor->execute();

        while(@fields = $cursor->fetchrow) {

          $jbfName [$nn]  = $fields[0];
          $jbStatus[$nn]  = $fields[1];
          $jbsubdate[$nn] = $fields[2];
          $jbmudst[$nn]   = $fields[3];

	  $nn++;
         }

   $cursor->finish();


  }else{

   &beginHtml();
 }

&StDbProdDisconnect(); 


    if( $qflag eq "jstat" ) {

   for ( $ii=0; $ii<$nn; $ii++ ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$ii]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$ii]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$ii]</h3></td>
<td HEIGHT=10><h3>$jbsubdate[$ii]</h3></td>
<td HEIGHT=10><h3>$jbftime[$ii]</h3></td>
</TR>
END
   }

 }elsif($qflag eq "mudst") {

 for ( $ii=0; $ii<$nn; $ii++ ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$ii]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$ii]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$ii]</h3></td>
<td HEIGHT=10><h3>$jbsubdate[$ii]</h3></td>
<td HEIGHT=10><h3>$jbftime[$ii]</h3></td>
</TR>
END
 }


 }elsif($qflag eq "unknown") {

 for ( $ii=0; $ii<$nn; $ii++ ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$ii]</h3></td>
<td HEIGHT=10><h3>$jbstate[$ii]</h3></td>
<td HEIGHT=10><h3>$jbsubdate[$ii]</h3></td>
</TR>
END
 }

 }elsif($qflag eq "mlog") {

for ($ii=0; $ii<$nn; $ii++ ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$ii]</h3></td>
<td HEIGHT=10><h3>$jbstate[$ii]</h3></td>
<td HEIGHT=10><h3>$jbsubdate[$ii]</h3></td>
<td HEIGHT=10><h3>$jbmudst[$ii]</h3></td>
</TR>
END
   }
 }


 &endHtml();

######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B>List of jobs failed for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>No failed jobs</h3></B></TD>
   </TR>
    </body>
END
}

#####################################

sub beginJbHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs crashed in<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Input filename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Reco status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Date of submission</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
</TR>
    </body>
END
}

#####################################

sub beginUnHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs wth reco status 'unknown' in<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Input filename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Last job state</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Date of submission</h3></B></TD>
</TR>
    </body>
END
}


#####################################

sub beginMuHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to deliver MuDst files for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Input filename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Reco status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Date of submission</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
</TR>
    </body>
END
}

#####################################

sub beginLogHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to deliver log files for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Input filename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Last job state</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Date of submission</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>MuDst status</h3></B></TD>

</TR>
    </body>
END
}

#####################################

sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created:  June 10 2014 -->
<!-- hhmts start -->
Last modified: 2014-06-10
<!-- hhmts end -->
  </body>
</html>
END

}



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

sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}












