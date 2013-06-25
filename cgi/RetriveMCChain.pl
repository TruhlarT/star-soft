#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveMCChain.pl
#
# Retrieve  chain for MC test production for new tracker evoluation.
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

 $chainOptionT = "EvalMCChains"; 

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qsimid = $query->param('simid');
my $qtrk = $query->param('trkname');
my $qprod = $query->param('prodsr');

my $chainopt;

  &StDbProdConnect();

    $sql="SELECT chainOpts  FROM $chainOptionT  where prodSeries = ? and simuID = ? and trackerName = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qsimid,$qtrk);

      $chainopt = $cursor->fetchrow();

      $cursor->finish();
  

&StDbProdDisconnect(); 

&beginHtml();

exit;

######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B><h2> Chain options used for <font color="blue">$qsimid </font>dataset and <font color="blue">$qprod </font> production with <font color="blue">$qtrk </font> tracker </font></B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
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












