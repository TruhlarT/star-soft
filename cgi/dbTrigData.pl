#!/usr/bin/env perl
#
# $Id:
#
# $Log:  
#
# dbTrigData.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

use Class::Struct;
use CGI;
use Mysql;

#&cgiSetup();

my $debugOn = 0;

my @prodPer;
my $nprodPer = 0;
my $myprod;

my @detSet = ("all","tpc","svt","rich","tof","ftpc","emc","fpd","pmd");
my @trigSet;
my @mfield = ("all","HalfField","FullField","ReversedFullField","ReversedHalfField","FieldOff");
my @collis = ("AuAu200", "AuAu130", "AuAu19","ProtonProton200","ProtonProton48","DeuteronAu200","DeuteronAu42","DeuteronAu21" );
my @trigSet;
my $ntrigSet = 0;
my $mytrig;
my @locSet = ("hpss","disk");
$trigSet[0] = "all";
$ntrigSet = 1;

&StDbProdConnect();

$sql="SELECT DISTINCT prodSeries FROM $JobStatusT WHERE prodSeries like 'P0%'";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

     $myprod = $fvalue  if($fname eq 'prodSeries'); 
      }
        $prodPer[$nprodPer] = $myprod;
        $nprodPer++;
      }


$sql="SELECT DISTINCT trigset FROM $FileCatalogT where fName like '%daq' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;
   
       $mytrig = $fvalue  if($fname eq 'trigset'); 
    }
       $trigSet[$ntrigSet] = $mytrig;
       $ntrigSet++;
    }


&StDbProdDisconnect();

$query = new CGI;

print $query->header;
print $query->start_html('dbTirgData');
print $query->startform(-action=>"dbProdSum.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Production plotes" CONTENT="This site demonstrates plots for production operation">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
 
  
  print " <title>Production Query</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ccffff\"> \n";
  print "<a href=\"http://www.star.bnl.gov/STAR/comp/prod\"><h5>Production </h5></a>\n";
  print "  <h1 align=center>Production Query </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "</td><td>";
print "<h3 align=center>Collisions:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetC',  
                   -values=>\@collis,
                   -default=>'DeuteronAu200',                   
                   -size=>6                              
                   );  

 print "</h3>";
print "</td><td>";
print "<h3 align=center>Production series:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetP',  
                   -values=>\@prodPer,
                   -default=>'P03ia',                   
                   -size=>6                              
                   );                                  
 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Trigger:</h3>";
 print "<h3 align=center>";
 print $query->popup_menu(-name=>'SetT',
                    -values=>\@trigSet,
                    -default=>'all', 
                    -size=>6
                    ); 

 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Magnetic Field:</h3>";
 print "<h3 align=center>";
 print $query->popup_menu(-name=>'SetF',
                    -values=>\@mfield,
                    -default=>'all', 
                    -size=>6
                    ); 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Detectors:</h3>";
 print "<h3 align=center>";
 print $query->popup_menu(-name=>'SetD',
                    -values=>\@detSet,
                    -default=>'all', 
                    -size=>6
                    ); 

print "</h3>";
print "</td> </table><hr><center>";

print "<h3 align=center>Location:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetLc',
                    -values=>\@locSet,
                    -default=>hpss,
                    -size=>2
                    ); 


 print "<p>";
 print "<p><br><br>"; 
 print $query->submit;
 print "<P><br>", $query->reset;
 print $query->endform;
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
  

#=======================================================================

if($query->param) {
  dbProdSum($query);
}
print $query->end_html; 







