#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:
# cvsShSolaris.pl - script for query of CVS revision for shared Libraries
# on Solaris in DEV
###############################################################################

use CGI;

my @setShr_Sol = ();
my @setShrSol = ();

# get all files in directory
my $Wdir = "/afs/rhic/star/doc/www/comp/prod/";

opendir DIR, $Wdir or die "Cannot open directory $Wdir <br> \n";
while( defined ( $file = readdir(DIR) ) ){
  $file =~ /dev.sun4x_56/ and push @setShr_Sol, $file;
}

# sort chronologically
@setShrSol = sort {-M "$Wdir/$a" <=> -M "$Wdir/$b"} @setShr_Sol;

# truncate list to 24 files
$#setShrSol > 24 and $#setShrSol = 24; 

                      
$query = new CGI;

print $query->header;
print $query->start_html('cvsShSolaris');
print $query->startform(-action=>"ShowPage.pl");  

  print "<html>\n";
  print " <head>\n";
  print " <title>CVS Status of Shared Libraries on Solaris</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>CVS Status of Shared Libraries on Solaris</h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<p>
<br>
END



print "<h2 align=center>Complete CVS map of Shared Libraries:</h2>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'set1',
                   -values=>\@setShrSol,
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
