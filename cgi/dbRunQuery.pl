#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbRunQuery.pl
#
# L.Didenko
#
# Interactive box for run numbers query
# 
#############################################################################

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

use Mysql;
use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);
use File::Find;

#&cgiSetup();

my $debugOn = 0;

my ($query) = @_;

$query = new CGI;

my $prodSr  =  $query->param('SetP');
my $detrSet =  $query->param('SetD');
my $datSet  =  $query->param('SetT');

my @joinSet = ( $prodSr . "%" .$datSet ."%" . $detrSet);

#####  connect to operation DB

 &StDbProdConnect();

my $mmRun;
my @runSet;
my $nrunSet = 0;

if($detrSet eq "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND path like '%/200%' ";

}else{

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND dataset like '%$detrSet' AND path like '%/200%' ";
}
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


if($nrunSet == 0) {
  $runSet[0] = "no data";
}

 &StDbProdDisconnect();      

  
      
#$qq = new CGI;

print $query->header;
print $query->start_html('dbRunQuery');
print $query->startform(-action=>"dbRunBrows.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Query for Run Number" CONTENT="Interactive Box for Run Number Query">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

  print " <title>Query for Run Number</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h2 align=center>Run Numbers in Production $prodSr for $datSet Events </h2>\n";
  print " </head>\n";
  print " <body>";

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
 print "<h4 align=center>";
 print $query->hidden(-name=>'prodSet',
                    -values=>\@joinSet,
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

#if($query->param) {
#  dbRunBrows($query);
#}
#print $query->delete_all;
print $query->end_html; 







