#! /opt/star/bin/perl -w
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

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

#&cgiSetup();

my $debugOn = 0;

my @prodPer;
my $nprodPer = 0;
my $myprod;

#my @datSet = ("all","tpc","tpc.rich","tpc.svt.rich");
my @trigSet  = ("all","central","minbias","medium","peripheral","mixed");

&StDbProdConnect();

$sql="SELECT DISTINCT prodSeries FROM JobStatus WHERE prodSeries like 'P0%'";

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
  print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod\"><h5>Production </h5></a>\n";
  print "  <h1 align=center>Production Query </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<br>
END

print "<p>";
print "<h3 align=center>Production series:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetP',  
                   -values=>\@prodPer,                   
                   -size=>4                              
                   );                                  
 

 print "<p>";
 print "<h3 align=center>Datasets:</h3>";
 print "<h4 align=center>";
 print $query->popup_menu(-name=>'SetT',
                    -values=>\@trigSet,
                    -size=>4
                    ); 
print <<END;
</SELECT><br>
<br>
END

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
  dbProdSum($query);
}
#print $query->delete_all;
print $query->end_html; 







