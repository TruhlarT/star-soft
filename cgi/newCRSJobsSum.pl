#!/usr/bin/env perl 
#
# $Id: newCRSJobSum.pl
#
# L. Didenko 
#
# newCRSJobSum.pl - script to get summary for CRS jobs id, trigset, production tag, runnumbers,
# input file names and streams
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


my $date_hour = ($year+1900)."-".$mon."-".$mday ." ".$hour;

my $nowdate = ($year+1900)."-".$mon."-".$mday ." ".$hour.":".$min.":".$sec ;

my $JobStatusT = "CRSJobsInfo";  

 my @jbstate  = ();
 my @prodtags = ();
 my @jbtrigs = ();
 my @runId = ();
 my $nj = 0;
 my @njbfile = ();
 my @nstream = ();
 my @rundate = ();
 my $ni = 0;

 my $query = new CGI;

if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };


 &StDbConnect();

    $sql="SELECT DISTINCT runDate FROM $JobStatusT where flag = 'Done'  ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

    while( $mpr = $cursor->fetchrow() ) {
          $rundate[$ni] = $mpr;
          $ni++;
       }
    $cursor->finish();

  for ( my $kk = 0; $kk < $ni; $kk++ ) {  

    $sql="SELECT DISTINCT status, prodtag, trigset, runnumber  FROM $JobStatusT where runDate = '$rundate[$kk]' and runnumber <> 0 order by status, runnumber ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute();

    while( @fields = $cursor->fetchrow() ) {


       $jbstate[$nj]  =  $fields[0];
       $prodtags[$nj] =  $fields[1];
       $jbtrigs[$nj]  =  $fields[2];
       $runId[$nj]    =  $fields[3];
       $nj++;

       }
    $cursor->finish();

  }

my $maxdate = $rundate[0];

  &beginHtml();

  for ( my $ik = 0; $ik < $nj; $ik++ ) {  

##############   find N files


   $sql="SELECT count(filename)  FROM $JobStatusT where runnumber = '$runId[$ik]' and prodtag = '$prodtags[$ik]' and status = '$jbstate[$ik]' and runDate = '$maxdate' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( my $mpr = $cursor->fetchrow() ) {
          $njbfile[$ik] = $mpr;
       }
    $cursor->finish();

###############   find N streams

 
  $sql="SELECT count(distinct stream)  FROM $JobStatusT where runnumber = '$runId[$ik]' and prodtag = '$prodtags[$ik]' and status = '$jbstate[$ik]' and runDate = '$maxdate' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( my $mpr = $cursor->fetchrow() ) {
          $nstream[$ik] = $mpr;
       }
    $cursor->finish();

 }


  for ( my $ii = 0; $ii < $nj; $ii++ ) {  

 if($jbstate[$ii] eq "RUNNING" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

 }elsif($jbstate[$ii] eq "QUEUED" )  {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"lightblue\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

      }elsif($jbstate[$ii] eq "CREATED" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"lightblue\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

      }elsif($jbstate[$ii] eq "STAGING" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"lightgreen\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

      }elsif($jbstate[$ii] eq "SUBMITTED" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"yellow\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

      }elsif($jbstate[$ii] eq "IMPORTING" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"pink\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END


 }elsif($jbstate[$ii] eq "EXPORTING" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"pink\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

  }elsif($jbstate[$ii] eq "ERROR" or $jbstate[$ii] eq "HELD" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"#D8BFD8\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

  }else{

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"#D8BFD8\">
<td HEIGHT=10>$jbstate[$ii]</td>
<td HEIGHT=10>$jbtrigs[$ii]</td>
<td HEIGHT=10>$prodtags[$ii]</td>
<td HEIGHT=10>$runId[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fname;qstate=$jbstate[$ii];qdate=$maxdate">$njbfile[$ii]</td>
<td HEIGHT=10><a href="http://www.star.bnl.gov/devcgi/RetriveCRSjobs.pl?qrun=$runId[$ii];qprod=$prodtags[$ii];qname=fstream;qstate=$jbstate[$ii];qdate=$maxdate">$nstream[$ii]</td>
<td HEIGHT=10>$rundate[0]</td>
</TR>
END

  }
 }

 &StDbDisconnect();

 &summaryHtml();

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
          <title>CRS Jobs </title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Jobs currently processing on the CRS farm</B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Trigger set name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Prod Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Runnumber</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Number of files</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Number of streams</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Date-time of scan</h3></B></TD>
</TR>
    </body>
END
}

################################################################################

sub summaryHtml {

print <<END;

  <html>

    <head>
          <title>CRS Jobs Summary </title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of jobs currently processing on the CRS farm</B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Trigger set name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Prod Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of jobs</h3></B></TD>

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
<!-- Created: April 24 2014 -->
<!-- hhmts start -->
Last modified: 2014-10-06
<!-- hhmts end -->
  </body>
</html>
END

}

##############


