#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbProdDAQQuery.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";
require "/afs/rhic/star/packages/DEV00/mgr/dbDescriptorSetup.pl";



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
); 

#####  connect to RunLog DB


$query = new CGI;

print $query->header;
print $query->start_html('dbProdQuery');
print $query->startform(-action=>"dbRunNumQuery.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Production plotes" CONTENT="This site demonstrates plots for production operation">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

  print " <title>Production Summary</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>Production Series Query </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<p>
<br>
END

print "<p>";
print "<h2 align=center>Select production series:</h2>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'set1',
                   -values=>\@prodSet,
                   -size=>4
                   ); 


print <<END;
</SELECT><br>
<p>
<br>
END


 print "<p>";
 print "<p><br>"; 
 print $query->submit;
 print "<P><br>", $query->reset;
 print $query->endform;
 print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod/ProdSummary.html\"><h3>Back </h3></a>\n";
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
  

#=======================================================================

if($query->param) {
  dbRunNumQuery($query);
}
print $query->delete_all;
print $query->end_html; 







