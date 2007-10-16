#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbMCList2005.pl  script to get browser of MC dataset and create WEB page 
#  L. Didneko
#
###############################################################################

use CGI;

require "/afs/rhic/star/users/didenko/cgi/dbProdSetup.2005.pl";

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

my $mCol = $query->param('setC');
my $mEvt = $query->param('evGen');
my $mGeo = $query->param('gYear');

my @spl = ();

  @spl = split(" ",$mCol );
  $myCol = $spl[0];
  @spl = ();
  @spl = split(" ",$mEvt);
  $myEvt = $spl[0];
  @spl = ();
  @spl = split(" ",$mGeo);
  $myGeo = $spl[0];  

my $Geo = "%$myGeo%";
my $Evt = "%$myEvt%";
my $Col = "$myCol%"; 

&StDbProdConnect();


 if ($myCol eq "all" and $myEvt eq "all" and $myGeo eq "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset <> 'n/a' AND type = 'MC_reco' ";

        $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

 }elsif($myCol eq "all" and $myEvt eq "all" and $myGeo ne "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND type = 'MC_reco' ";

     $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Geo);

 }elsif($myCol eq "all" and $myEvt ne "all" and $myGeo ne "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND dataset like ? AND type = 'MC_reco' ";

       $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Evt,$Geo);

 }elsif($myCol eq "all" and $myEvt ne "all" and $myGeo eq "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND type = 'MC_reco' ";

         $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Evt);

 }elsif($myCol ne "all" and $myEvt eq "all" and $myGeo eq "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND type = 'MC_reco' ";

         $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Col);  

 }elsif($myCol ne "all" and $myEvt ne "all" and $myGeo eq "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND dataset like ? AND type = 'MC_reco' ";

         $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Col,$Evt);    

 }elsif($myCol ne "all" and $myEvt eq "all" and $myGeo ne "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND dataset like ? AND type = 'MC_reco' ";

        $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($Col,$Geo); 

 }elsif($myCol ne "all" and $myEvt ne "all" and $myGeo ne "all" ) {

 $sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND dataset like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' ";

      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($Col,$Evt,$Geo);
}

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

$query = new CGI;

print $query->header;
print $query->start_html('List of MC Datasets');

 print $query->startform(-action=>"dbMCProdSum2005.pl");

  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod/index.html\"><h4>Production </h4></a>\n";
  print "  <h1 align=center>List of MC Datasets</h1>\n";

print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<h3 align=center>Select MC Dataset</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetMC',  
                   -values=>\@SetD,                   
                   -size=>10                             
                   );                                  

print "</td><td> </table><hr><center>";
 
 print "<p>";
 print "<p><br>"; 
 print "<br>"; 
 print "<br>"; 
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
