#! /opt/star/bin/perl -w
#  
#  $Id:
#
#  $Log:
# cvsErrQuery.pl - script for query of CVS revision of files in DEV 
#
###############################################################################

use CGI;

my @setCvs_err = ();;
my @setCvsErr = ();

my $Wdir = "/afs/rhic/star/doc/www/comp/prod/";

opendir DIR, $Wdir or die "Cannot open directory $Wdir <br> \n";
while( defined ( $file = readdir(DIR) ) ){
  $file =~ /error\.html/ and push @setCvs_err, $file;
}

# sort chronologically
@setCvsErr = sort {-M "$Wdir/$a" <=> -M "$Wdir/$b"} @setCvs_err;

# truncate list to 24 files
$#setCvsErr > 24 and $#setCvsErr = 24; 

$query = new CGI;

print $query->header;
print $query->start_html('cvsErrQuery');
print $query->startform(-action=>"ShowPage.pl");  

  print "<html>\n";
  print " <head>\n";
  print " <title>Status of Source Files </title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>CVS Conflicts for Source Files </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<p>
<br>
END




print "<h2 align=center>CVS map for conflicts between working and repository revisions:</h2>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'set1',
                   -values=>\@setCvsErr,
                   -size=>12
                        );
print "</h4>";
 
 print "<p>";
 print "<p><br>";
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
