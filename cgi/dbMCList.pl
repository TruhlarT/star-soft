#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbMCDataSet.pl  script to get browser of MC dataset and create WEB page 
#  L. Didneko
#
###############################################################################

use CGI;

require "/afs/rhic/star/packages/cgi/dbCpProdSetup.pl";

use Class::Struct;
use CGI::Carp qw(fatalsToBrowser);

my $debugOn = 0;
my @SetD;
my $nSetD = 0;
my $mySet;
my $myCol;
my $myEvt;
my $myGeo;

#&cgiSetup();

my ($query) = @_;

$query = new CGI;

$myCol = $query->param('setC');
$myEvt = $query->param('evGen');
$myGeo = $query->param('gYear');

&StDbProdConnect();

if ($myCol eq "all" and $myEvt eq "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset <> 'n/a' AND type = 'MC_reco' ";

}elsif($myCol eq "all" and $myEvt eq "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '%$myGeo%' AND type = 'MC_reco' ";

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '%$myEvt%' AND dataset like '%$myGeo%' AND type = 'MC_reco' ";

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '%$myEvt%' AND type = 'MC_reco' ";

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '$myCol%' AND type = 'MC_reco' ";

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '$myCol%' AND dataset like '%$myEvt%' AND type = 'MC_reco' ";

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '$myCol%' AND dataset like '%$myGeo%' AND type = 'MC_reco' ";

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like '$myCol%' AND dataset like '%$myEvt%' AND dataset like '%$myGeo%' AND type = 'MC_reco' ";
}


$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

my $counter = 0;
while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;

     $mySet = $fvalue  if($fname eq 'dataset'); 
 }
    next if ($mySet =~ /daq/);
    next if ($mySet =~ /dst/);
    next if ($mySet eq 'n/a');

      $SetD[$nSetD] = $mySet;
      $nSetD++;

  }

&StDbProdDisconnect();

if (!$nSetD) {$SetD[0] = "No dataset found for your query"};

my $rand = rand(100);


$query = new CGI;

print $query->header;
print $query->start_html('List of MC Datasets');

print $query->startform(-action=>"dbMCProdSum.pl?rand=$rand");   

  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "<a href=\"http://www.star.bnl.gov/STAR/comp/prod/index.html\"><h4>Production </h4></a>\n";
  print "  <h1 align=center>List of MC Datasets</h1>\n";

print "<p>";
print "<p><br>"; 
print "<h3 align=center>Select MC Dataset for Production Summary</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetMC',  
                   -values=>\@SetD,                   
                   -size=>15                              
                   );                                  
 print "<p>";
 print "<p><br>"; 
 print $query->submit;
 print "<P><br>", $query->reset;
 print $query->endform;
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
 exit 0;


###############

print $query->end_html; 

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
