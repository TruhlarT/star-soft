#!/usr/local/bin/perl -w
#
#  $Id: 
#  dbMCData.pl
#  L.Didenko
#
################################################################

use CGI;
use CGI::Carp qw(fatalsToBrowser);
#use Mysql;
require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;

my @collision = ( "all","auau100", "auau200", "auau130", "auau128", "augas100", "pau200", "pp200", "dAu200");
my @evtGen  = ("all","hijing", "hijet", "mevsim", "venus", "nexus", "vni", "two_photon", "hbt", "rqmd", "single", "starlight", "strongcp", "pythia", "hemicosm");

my @geoYear = ("all","year_1b", "year_1h", "year_1e", "year_1s", "complete", "year_1a", "year1a", "year2001", "year2003", "y2003x", "year_2a", "year2a");

my @ftype = ("fzd","event.root","geant.root", "MuDst.root");
my @locSet = ("hpss","disk");
my @prodPer;
my $myprod;
my $nprodPer = 0;
my @prod = ();


&StDbProdConnect();

$sql="SELECT DISTINCT prodSeries FROM $JobStatusT where jobfileName like '%hadronic%' OR jobfileName like '%gheisha%'";

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

   push @prod, "all";
   push @prod, @prodPer;

 &StDbProdDisconnect();

$query = new CGI;

print $query->header;
print $query->start_html('dbMCData');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"dbMCBrows.pl");  

print "<body bgcolor=\"#ffdc9f\">\n";
print "<h1 align=center> Monte Carlo Datasets</h1>\n";

print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<td>";
print "<h3 align=center>Collision:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'setC',
			     -values=>\@collision,
                             -default=>'all',
			     -size=>6);

print "</td><td>";
print "<h3 align=center> Event Generator:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'evGen',
			     -values=>\@evtGen,
                             -default=>'all', 
			     -size =>6); 

print "</td><td>";
print "<h3 align=center> Geometry:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'gYear',
			     -values=>\@geoYear,
                             -default=>'all',
			     -size =>6); 

print "</td><td>";
print "<h3 align=center>Production series:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetPrd',  
                   -values=>\@prod,
                   -default=>'all',                   
                   -size=>6);                              

print "</td><td>";
print "<h3 align=center>Format:</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetForm',
                    -values=>\@ftype,
                    -default=>'event.root',
                    -size=>6);
                  

print "</td> </table><hr><center>";

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
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

#print $query->delete_all;
print $query->end_html;
