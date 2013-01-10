#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveTrigID.pl
#
# Retrive offline trigger ID for certain trigger set name from FileCatalog.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use CGI qw(:standard);
use DBI;
use Mysql;
use Class::Struct;
use Time::Local;

use CGI;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $TrigDataT = "ProdTriggerSet";


($sec,$min,$hour,$mday,$mon,$year) = localtime();

my $mon =  $mon + 1;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;


my @trglable = ();
my @trgid = ();
my @nevents = ();
my $tline = 0;
my $nlist = 0;

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };


my $qtrg = $query->param('rtrig');
my $qprod = $query->param('rprod');

$artrig[0] = 0;

&beginHtml();

   &StDbProdConnect();

   $sql="SELECT distinct trigLabel, offlineTrgId, sum(Nevents) from ProdTriggerSet where trigSetName = '$qtrg' and prodTag = '$qprod' group by offlineTrgId ";

           $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};

            for($i=0;$i<$cols;$i++) {

            $trglable[$nlist] = $fields[0];
            $trgid[$nlist] = $fields[1];
            $nevents[$nlist] = $fields[2];

	}

print <<END;

<TR ALIGN=CENTER HEIGHT=5 bgcolor=\"#ffdc9f\">
<td HEIGHT=5><h3>$trglable[$nlist]</h3></td>
<td HEIGHT=5><h3>$trgid[$nlist]</h3></td>
<td HEIGHT=5><h3>$nevents[$nlist]</h3></td>
</TR>
END

	    $nlist++;
	}
 
   &StDbProdDisconnect();

 &endHtml();

######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B>Offline trigger ID list for <font color="blue">$qtrg </font> dataset <br>and  <font color="blue">$qprod </font>production</B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=0.5 CELLPADDING=1 >
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Trigger lable</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Offline trigger ID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Number of Events</h3></B></TD>

</TR> 
   </head>
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
 Created: Fri January 11 15:15:00 MET 2013
<!-- hhmts start -->
<!--Last modified: $Date -->
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


##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}












