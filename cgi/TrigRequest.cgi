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

my $TrigRequestT = "TrigProdRequest";

my $DaqInfoT   = "DAQInfo";
my $FlStreamT = "FOFileType";

my @arevents = ("1000","2000","5000","10000");
my @arstreams = ();
my @arruns = ();
my @prodlibs = ("dev","SL14h","SL14g");
my @prodfiles = ("all","10","20","50","100");


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

# &StdbDisconnect();


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $trgrun      =  $query->param('qrun');
 my $trgstream   =  $query->param('qstream');
 my $fevents     =  $query->param('qevent');
 my $plib        =  $query->param('qlib');
 my $pfile       =  $query->param('qfile');


  if( $trgrun eq "" and $trgstream eq "" and  $fevents eq "" and $plib eq "" and $pfile eq "" ) {

print $query->header();
print $query->start_html('Test production request form');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");  

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Trigger/subsystem test production requests form </u></h1>\n";

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
print "<h3 align=center> Select number of files</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'qfile',
                             -values=>\@prodfiles,
                             -default=>all,
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
print "<h3 align=center>Select library</h3>"; 
print $query->scrolling_list(-name=>'qlib',
                             -values=>\@prodlibs,
                             -default=>dev,
                             -size =>1); 

print "<br>";
print "<br>";
print "<br>";
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


$TrigRequestT = "TrigProdRequest";

my $qqr = new CGI;

 my $trgrun      =  $qqr->param('qrun');
 my $trgstream   =  $qqr->param('qstream');
 my $fevents     =  $qqr->param('qevent');
 my $plib        =  $qqr->param('qlib');
 my $pfile       =  $qqr->param('qfile');


($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowtime = ($year+1900)."-".($mon+1)."-".$mday." ".$hour.":".$min.":".$sec;


if( $pfile eq "all" ) {

  $sql= "insert into $TrigRequestT set runnumber = '$trgrun', stream = '$trgstream', dataset = 'n/a', prodtag = 'n/a', Nevents = '$fevents', libtag = '$plib', requestTime = '$nowtime' ";

  $dbh->do($sql) || die $dbh->errstr;

    }else{

  $sql= "insert into $TrigRequestT set runnumber = '$trgrun', stream = '$trgstream', dataset = 'n/a', prodtag = 'n/a', Nevents = '$fevents', libtag = '$plib', Nfiles = '$pfile', requestTime = '$nowtime' ";

  $dbh->do($sql) || die $dbh->errstr;

}

 print $qqr->header;
 print $qqr->start_html('Requested runnumber');
 print "<body bgcolor=\"cornsilk\">\n"; 
 print "<h2 align=center>Runnumber <font color=\"red\"> $trgrun</font> and stream <font color=\"red\">$trgstream </font> have been requested  <br> for test production</h2>";

 print "<br>";
 print "<br>";
 print "<br>";
 print "<h3 align=center><a href=\"$scriptname\">Next Selection</a></h3>";
 print "<p>";
 print $qqr->end_html;


&StdbDisconnect();

}

 

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
  <head>
          <title>Requested runnumber </title>
   </head>
     <h2 align=center>Next runnumber and stream have been requested for <br>test production: $trgrun,"   ", $trgstream </h2>
     <br>
     <br>
     <br> 
     <h3 align=center>New Selection</h3>
     <br> 
    </body>
  </html>
END
}

