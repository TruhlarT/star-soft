#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbDataSetQuery.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################

require "/afs/rhic/star/packages/scripts/dbCpProdSetup.pl";

use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

#&cgiSetup();

my $debugOn = 0;

my @prodPer;
my $myprod;
my $nprodPer = 0;
my @colSet = ("AuAu130", "AuAu200","laser");
my @detSet = ("all","tpc","svt","rich","tof","ftpc","emc","fpd","pmd");
my @trigSet  = ("all","central","minbias","medium","peripheral","mixed","physics","n/a");
my @mfield = ("all","HalfField","ReversedFullField","ReversedHalfField","FieldOff");
my @format = ("daq","dst.root","event.root","hist.root","tags.root");
my @locSet = ("hpss","disk");

&StDbProdConnect();

$sql="SELECT DISTINCT prodSeries FROM JobStatus where prodSeries like 'P0%'";

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

$query = new CGI;

print $query->header;
print $query->start_html('dbDataSetQuery');
print $query->startform(-action=>"dbRunQuery.pl");  

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
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod\"><h5>Production </h5></a>\n";
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
print "<h3 align=center>Collision:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetCl',  
                   -values=>\@colSet,
                   -default=>'AuAu200',                  
                   -size=>4                              
                   );
print "</h3>"; 
print "</td><td>";
print "<h3 align=center>Detector:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetDet',
                    -values=>\@detSet,
                    -default=>'all',
                    -size=>4
                    ); 
print "</h3>";
print "</td><td>";
print "<h3 align=center>Trigger:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetTrg',
                    -values=>\@trigSet,
                    -default=>'all',
                    -size=>4
                    ); 

print "</h3>";
print "</td> </table><center>";


print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "</td><td>";
print "<h3 align=center>Magnetic Field:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetField',
                    -values=>\@mfield,
                    -default=>'all', 
                    -size=>4
                    ); 
print "</h3>";
print "</td><td>";
print "<h3 align=center>Format:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetForm',
                    -values=>\@format,
                    -default=>'daq',
                    -size=>4
                    ); 
print "</h3>";
print "</td><td>";
print "<h3 align=center>Production series:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetPrd',  
                   -values=>\@prodPer,
                   -default=>'P01hf',                   
                   -size=>4                              
                   );  
print "</h3>";
print "</td> </tr> </table><hr><center>";


print "<h3 align=center>Location:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetLc',
                    -values=>\@locSet,
                    -default=>hpss,
                    -size=>2
                    ); 
print "</h3>";

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
  dbRunQuery($query);
}
#print $query->delete_all;
print $query->end_html; 







