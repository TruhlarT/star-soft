#!/usr/bin/env perl
#
# $Log: RetriveCRSjobs.pl
#
# L.Didenko
#
# RetriveCRSjobs.pl
#
# Retrive filenames and streams for jobs with selected runnumber processing on the CRS farm.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
use Class::Struct;


($sec,$min,$hour,$mday,$mon,$year) = localtime();

my $mon++;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday;

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

 $JobsInfoT = "CRSJobsInfo"; 

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $jbrun = $query->param('qrun');
my $jbprod = $query->param('qprod');
my $jbname = $query->param('qname');
my $scdate = $query->param('qdate');

my $rdate = $scdate."%";

my @jbId = ();
my @jbfiles = ();
my @jbstreams = ();
my $nn = 0;
my $nm = 0;

  &StDbConnect();

  if($jbname eq "fname" ){ 

  $nn = 0;

    $sql="SELECT jobId, filename  FROM $JobsInfoT where runnumber = ? and prodtag = ? and runDate like ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jbrun,$jbprod,$rdate);

       while( @fields = $cursor->fetchrow() ) {

	   $jbId[$nn]    = $fields[0];
           $jbfiles[$nn] = $fields[1];
           $nn++;
       }
    $cursor->finish();

  &beginHtmlF();

  for ( my $ii = 0; $ii < $nn; $ii++ ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10>$jbId[$ii]</td>
<td HEIGHT=10>$jbfiles[$ii]</td>
</TR>
END
  }

  }elsif($jbname eq "fstream" ){


  $nm = 0;
 
    $sql="SELECT distinct stream  FROM $JobsInfoT where runnumber = ? and prodtag = ? and runDate like ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jbrun,$jbprod,$rdate);

       while( my $strm = $cursor->fetchrow() ) {

	   $jbstreams[$nm]   = $strm;
           $nm++;
       }
    $cursor->finish();  

  &beginHtmlS();

  for ( my $ii = 0; $ii < $nm; $ii++ ) {

print <<END;
<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=20><B>$jbstreams[$ii]</B></td>
</TR>
END
    }
 }

  &StDbDisconnect(); 

  &endHtml();

######################

sub beginHtmlF {

print <<END;

  <html>

   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B> Files for runnumber <font color="blue">$jbrun </font> in <font color="blue">$jbprod </font> production scanned at <font color="blue">$scdate </font></B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>JobID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Filename</h3></B></TD>
</TR>
    </body>
END
}

######################

sub beginHtmlS {

print <<END;

  <html>

   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B>Streams for runnumber <font color="blue">$jbrun </font> in <font color="blue">$jbprod </font> production scanned at  <font color="blue">$scdate </font></B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=4 CELLSPACING=1 CELLPADDING=1 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Stream Name</h3></B></TD>
</TR>
    </body>
END
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

#####################

sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: April 25 2014 -->
<!-- hhmts start -->
Last modified: 2014-04-25
<!-- hhmts end -->
  </body>
</html>
END

}

##############












