#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:
# cvsQuery.pl - script for query of CVS revision of files in DEV 
#
###############################################################################

use CGI;

#-------------------------------------------------------
# changed by pmj 27/1/00

my @setCvs_all = ();
my @setCvsAll = ();

# get all files in directory
$Wdir = "/afs/rhic/star/doc/www/comp/prod/";
opendir DIR, $Wdir or die "Cannot open directory $Wdir <br> \n";
while( defined ( $file = readdir(DIR) ) ){
  $file =~ /all\.html/ and push @setCvs_all, $file;
}

# sort chronologically
@setCvsAll = sort {-M "$Wdir/$a" <=> -M "$Wdir/$b"} @setCvs_all;

# truncate list to 24 files
$#setCvsAll > 24 and $#setCvsAll = 24; 

#--------------------------------------------------------
                      
$query = new CGI;

print $query->header;
print $query->start_html('cvsQuery');
print $query->startform(-action=>"ShowPage.pl target");  

  print "<html>\n";
  print " <head>\n";
  print " <title>Status of Source Files </title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>CVS Status of Source Files </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<p>
<br>
END



print "<h2 align=center>Complete CVS map of source files:</h2>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'set1',
                   -values=>\@setCvsAll,
                   -size=>12
                        );
print "</h4>";
 
 print "<p>";
 print "<p><br>"; 
 print $query->submit;
 print $query->reset;
 print $query->endform;
  print "<p><br>";
 print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/ofl/CvsRevision.html\"><h3>Back </h3></a>\n"; 
  print "<p><br>";
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";




#=======================================================================

if($query->param) {
  ShowPage($query);
}
print $query->delete_all;
print $query->end_html; 
