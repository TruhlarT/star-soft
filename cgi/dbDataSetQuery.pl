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

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

#&cgiSetup();

my $debugOn = 0;

my @prodPer;
my $myprod;
my $nprodPer = 0;
my @colSet = ("AuAu130", "tpc_laser");
my @datSet = ("all","tpc","tpc.rich","tpc.svt.rich");
my @trigSet  = ("all","central","minbias","medium","peripheral","mixed");

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

&StDbProdDisconnect();

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
  print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod/ProdSummary.html\"><h5>Production </h5></a>\n";
  print "  <h1 align=center>Production Query </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "<h4 align=center>Select dataset:</h4>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetC',  
                   -values=>\@colSet,                   
                   -size=>4                              
                   );  

print "</td><td>";
print "<h4 align=center>Select production series:</h4>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetP',  
                   -values=>\@prodPer,                   
                   -size=>4                              
                   );                                  
 
print "</td><td>";
print "<h4 align=center>Select detector set:</h4>";
print "<h4 align=center>";
print $query->popup_menu(-name=>'SetD',
                    -values=>\@datSet,
                    -size=>4
                    ); 

print "</td><td>";
print "<h4 align=center>Select Trigger:</h4>";
print "<h4 align=center>";
print $query->popup_menu(-name=>'SetT',
                    -values=>\@trigSet,
                    -size=>4
                    ); 

print "</td> </tr> </table><hr><center>";

 print "<p>";
 print "<p><br>"; 
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







