#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
# cvsShLinux.pl - script for query of CVS revision for shared Libraries
# on Linux in DEV
###############################################################################

use CGI;

my @setShr_Lin = ();
my $setShrLin = ();

# get all files in directory
my $Wdir = "/afs/rhic/star/doc/www/comp/prod/";
opendir DIR, $Wdir or die "Cannot open directory $Wdir <br> \n";
while( defined ( $file = readdir(DIR) ) ){
  $file =~ /dev.i386_redhat51/ and push @setShr_Lin, $file;
}

# sort chronologically
@setShrLin = sort {-M "$Wdir/$a" <=> -M "$Wdir/$b"} @setShr_Lin;

# truncate list to 24 files
$#setShrLin > 24 and $#setShrLin = 24; 

                      
$query = new CGI;

print $query->header;
print $query->start_html('cvsShLinux');
print $query->startform(-action=>"ShowPage.pl");  

  print "<html>\n";
  print " <head>\n";
  print " <title>CVS Status of Shared Libraries on Linux</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>CVS Status of Shared Libraries on Linux</h1>\n";
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
                   -values=>\@setShrLin,
                   -size=>12
                        );
print "</h4>";
 
 print "<p>";
 print "<p><br>"; 
 print $query->submit;
 print $query->reset;
 print $query->endform;

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
