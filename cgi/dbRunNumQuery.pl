#! /usr/local/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbRunNumQuery.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);
use File::Find;

#&cgiSetup();

my $debugOn = 0;

my ($query) = @_;

$query = new CGI;

$prodSr =  $query->param('set1');

my @prod = (
            $prodSr,
  );

#####  connect to operation DB

 &StDbProdConnect();

my $mmRun;
my @runSet;
my $nrunSet = 0;

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' and path like '%/200%' ";

   $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;
 
    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

        for($i=0;$i<$cols;$i++) {
           my $fvalue=$fields[$i];
           my $fname=$cursor->{NAME}->[$i];
#        print "$fname = $fvalue\n" ;
       
         $mmRun = $fvalue     if( $fname eq 'runID'); 
         }
        $runSet[$nrunSet] = $mmRun;
        $nrunSet++;
 }

 &StDbProdDisconnect();      

      
print $query->header;
print $query->start_html('dbRunNumQuery');
print $query->startform(-action=>"dbSumRun.pl");  

  print " <title>Query for Run Number</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1 align=center>Run Numbers in Production $prodSr </h1>\n";
  print " </head>\n";
  print " <body>";

print <<END;
</SELECT><br>
<p>
<br>
END

print "<p>";
print "<h2 align=center>Production series you selected:</h2>";
print "<h4 align=center>";
print $query->popup_menu(-name=>'setP',
                   -values=>\@prod,
                   ); 

print <<END;
</SELECT><br>
<p>
<br>
END

 print "<p>";
 print "<h2 align=center>Select Run Number:</h2>";
 print "<h4 align=center>";
 print $query->popup_menu(-name=>'runN',
                    -values=>\@runSet,
                    -size=>10
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
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
  

#=======================================================================

print $query->delete_all;
print $query->end_html; 







