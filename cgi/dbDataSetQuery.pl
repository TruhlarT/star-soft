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
use File::Find;

#&cgiSetup();

my $debugOn = 0;


my @prodSet = (
                "P00hd",
                "P00hd_1",
                "P00he",
                "P00hg",
                "P00hi",
                "P00hm",
); 

my @datSet = ("all","tpc","tpc.rich","tpc.svt.rich");
my @trigSet  = ("central","minbias","medium","peripheral","mixed");


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
</SELECT><br>
<br>
END

print "<p>";
print "<h3 align=center>Select production series:</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetP',  
                   -values=>\@prodSet,                   
                   -size=>4                              
                   );                                  
 
print <<END;
</SELECT><br>
<br>
END

 print "<p>";
 print "<h3 align=center>Select detector set:</h3>";
 print "<h4 align=center>";
 print $query->popup_menu(-name=>'SetD',
                    -values=>\@datSet,
                    -size=>3
                    ); 
print <<END;
</SELECT><br>
<br>
END

 print "<p>";
 print "<h3 align=center>Select Dataset:</h3>";
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
  dbRunQuery($query);
}
#print $query->delete_all;
print $query->end_html; 







