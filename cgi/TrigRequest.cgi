#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: TrigRequest.cgi
#
# $Log:  TrigRequest.cgi
#
# L.Didenko
#
# script for trig tunning production request
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use lib "/opt/star/lib";
use CGI qw(:standard);
use DBI;
use Time::Local;

require 'cgi-lib.pl';

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $TrigRequestT = "TrigJobRequest";

my $DaqInfoT   = "DAQInfo";
my $FlStreamT = "FOFileType";

my @arevents = ("20000","10000","5000","2000","1000");
my @arstreams = ();
my @arruns = ();
my $maxrun = 0;
my @runs = ();
my $nn = 0;
my $nk = 0;

 &StdbConnect();

    $sql="SELECT DISTINCT runNumber  FROM $DaqInfoT order by runNumber";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $runs[$nn] = $mpr;
          $nn++;
   }

   $cursor->finish();

@arruns = reverse @runs;

$maxrun = $arruns[0];

   $sql="SELECT DISTINCT Label  FROM $FlStreamT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arstreams[$nk] = $mpr;
          $nk++;
   }

   $cursor->finish();


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $trgrun      =  $query->param('qrun');
 my $trgstream   =  $query->param('qstream');
 my $fevents     =  $query->param('qevent');

  if( $trgrun eq "" and $trgstream eq "" and  $fevents eq "" ) {

print $query->header();
print $query->start_html('Trigger request form');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Trigger production requests form </u></h1>\n";

print "<br>";
print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END


print "<p>";
print "</td><td>";  
print "<h3 align=center> Select runnumber</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'qrun',
                             -values=>\@arruns,
                             -default=>$maxrun,
                             -size =>1); 


print "</td><td>";
print "<h3 align=center> Select stream</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'qstream',
                             -values=>\@arstreams,
                             -default=>physics,
                             -size =>1); 


print "</td><td>";
print "<h3 align=center> Select number of events<br>in one file</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'qevent',
                             -values=>\@arevents,
                             -default=>1000,
                             -size =>1); 


print "<p>";
print "</td><td>";
print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

   }else{


my $qqr = new CGI;

 my $trgrun      =  $qqr->param('qrun');
 my $trgstream   =  $qqr->param('qstream');
 my $fevents     =  $qqr->param('qevent');


($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowtime = ($year+1900)."-".($mon+1)."-".$mday." ".$hour.":".$min.":".$sec;

 $sql= "insert into $TrigRequestT set runnumber = '$trgrun', stream = '$trgstream', Nevents = '$fevents', requestTime = '$nowtime' ";

      $dbh->do($sql) || die $dbh->errstr;


 &beginHtml();


}

   &StdbDisconnect();

 

#############################################
sub StdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

##############################################
sub StdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

##############################################
sub beginHtml {

print <<END;
  <html>
   <body BGCOLOR=\"#ccffff\">
     <h2 align=center>Next runnumber and stream have been requested for <br>test production: $trgrun,"   ", $trgstream </h2>
     <br>
     <br>
     <br> 
     <h3 align=center><a href=\"$scriptname\">New Selection</a></h3>
     <br> 
    </body>
  </html>
END
}

