#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveCalChain.pl
#
# Retrieve calibration production chain.
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

my $mon =  $mon + 1;

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

 $chainOptionT = "ProdOptions"; 

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qchain = $query->param('rchain');
my $qcaltg = $query->param('rcaltag');

my $chainopt;

  &StDbProdConnect();

    $sql="SELECT chainOpt  FROM $chainOptionT  where chainName = ?";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qchain);

      $chainopt = $cursor->fetchrow();

      $cursor->finish();
  

&StDbProdDisconnect(); 

&beginHtml();



######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
 <TD ALIGN=CENTER> <B><h3> Chain options used for <font color="blue">$qcaltg </font>calibration production</B></h3></TD>
</TR><TR>
<TD  ALIGN=CENTER WIDTH=\"100%\" HEIGHT=50><h3>$chainopt</h3></TD>
</TR>

</TABLE>
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












