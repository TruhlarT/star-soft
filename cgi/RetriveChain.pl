#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveChain.pl
#
# Retrive production chain.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
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

 $chainOptionT = "ProductionChains"; 

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');

my @archain = ();

$archain[0] = 0;
my $np = 0;
my $chpt;
my $chset;

  &StDbProdConnect();

    $sql="SELECT chainOpt  FROM $chainOptionT  where trgsetName = ? and prodTag = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qtrg,$qprod);

       while( $chpt = $cursor->fetchrow() ) {
          $archain[$np] = $chpt;
          $np++;
       }
    $cursor->finish();
  
$chset = $archain[0];

&StDbProdDisconnect(); 

&beginHtml();



######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
 <TD ALIGN=CENTER> <B><h3> Chain options for <font color="blue">$qprod </font>production and <font color="blue"> $qtrg </font>dataset </B></h3></TD>
</TR><TR>
<TD  ALIGN=CENTER WIDTH=\"100%\" HEIGHT=50><h3>$chset</h3></TD>
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












