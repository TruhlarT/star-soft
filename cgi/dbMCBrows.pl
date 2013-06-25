#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbMCBrowes.pl  script to get browser of MC datasets
#  L. Didenko
#
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

use Class::Struct;
use CGI::Carp qw(fatalsToBrowser);
#use Mysql;

my $debugOn = 0;
my @SetD;
my $nSetD = 0;
my $mySet;
my $myCol;
my $myEvt;
my $myGeo;
my $myForm;
my $prod;
my $loct;

#&cgiSetup();

my ($query) = @_;

$query = new CGI;

my $mCol = $query->param('setC');
my $mEvt = $query->param('evGen');
my $mGeo = $query->param('gYear');
my $mform = $query->param('SetForm');
my $mprod = $query->param('SetPrd');
my $mloct = $query->param('SetLc');

my @spl = ();
 @spl = split(" ", $mCol);
  $myCol = $spl[0];
 @spl = ();
 @spl = split(" ", $mEvt);
  $myEvt = $spl[0];
 @spl = ();
 @spl = split(" ", $mGeo);
  $myGeo = $spl[0];
 @spl = ();
 @spl = split(" ", $mform);
  $myForm = $spl[0];
 @spl = ();
 @spl = split(" ", $mprod);
  $prod = $spl[0];
  @spl = ();
 @spl = split(" ", $mloct);
  $loct = $spl[0];


my @joinSet = ($prod . "%" .$myForm . "%" .$loct);

my $Prod = "%$prod%";
my $exts = "%$myForm";
my $Col = "$myCol%";
my $Evt = "%$myEvt%";
my $Geo = "%$myGeo%";
my $Loc = "$loct%";


&StDbProdConnect();

if ($myForm =~ /root/) {

if ($myCol eq "all" and $myEvt eq "all" and $myGeo eq "all" and $prod ne "all" ) {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset <> 'n/a' AND type = 'MC_reco' AND fName like ? and site like ? ";

$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$exts,$Loc);

}elsif($myCol eq "all" and $myEvt eq "all" and $myGeo ne "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

  $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Geo,$exts,$Loc);

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo ne "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ?";

 $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Evt,$Geo,$exts,$Loc);

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo eq "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

 $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Evt,$exts,$Loc);

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo eq "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

 $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Col,$exts,$Loc);

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo eq "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

  $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Col,$Evt,$exts,$Loc);

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo ne "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

   $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Col,$Geo,$exts,$Loc); 

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo ne "all" and $prod ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like ? AND dataset like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

   $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Prod,$Col,$Evt,$Geo,$exts,$Loc);  

}elsif ($myCol eq "all" and $myEvt eq "all" and $myGeo eq "all" and $prod eq "all" ) {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset <> 'n/a' AND type = 'MC_reco' AND fName like ? and site like ? ";

    $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($exts,$Loc); 

}elsif($myCol eq "all" and $myEvt eq "all" and $myGeo ne "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

    $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Geo,$exts,$Loc); 

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo ne "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Evt,$Geo,$exts,$Loc); 

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo eq "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? '";

    $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Evt,$exts,$Loc);  

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo eq "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$exts,$Loc); 

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo eq "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where  dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Evt,$exts,$Loc); 

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo ne "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Geo,$exts,$Loc); 

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo ne "all" and $prod eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND dataset like ? AND type = 'MC_reco' AND fName like ? and site like ? ";
  
     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Evt,$Geo,$exts,$Loc); 

}

}else{

if ($myCol eq "all" and $myEvt eq "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset <> 'n/a' AND type = 'MC' AND fName like ? ";
 
    $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($exts);  

}elsif($myCol eq "all" and $myEvt eq "all" and $myGeo ne "all" ) {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Geo,$exts); 

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Evt,$Geo,$exts); 

}elsif($myCol eq "all" and $myEvt ne "all" and $myGeo eq "all" ) {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Evt,$exts); 

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$exts); 

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo eq "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Evt,$exts); 

}elsif($myCol ne "all" and $myEvt eq "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND type = 'MC' AND fName like ? ";

     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Geo,$exts); 

}elsif($myCol ne "all" and $myEvt ne "all" and $myGeo ne "all") {

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where dataset like ? AND dataset like ? AND dataset like ? AND type = 'MC' AND fName like ? ";
     $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute($Col,$Evt,$Geo,$exts); 

 }
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

 print $query->startform(-action=>"dbMCProdRetrv.pl");

  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "<a href=\"http://www.star.bnl.gov/STARAFS/comp/prod/index.html\"><h4>Production </h4></a>\n";
  print "  <h1 align=center>List of MC Datasets</h1>\n";

print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<h3 align=center>MC Datasets</h3>";
print "<h4 align=center>";
print $query->scrolling_list(-name=>'SetMC',  
                   -values=>\@SetD,                   
                   -size=>8                              
                   );                                  

print "</td><td> </table><hr><center>";

 print "<p>";
 print "<h4 align=center>";
 print $query->hidden(-name=>'prodSet',
                    -values=>\@joinSet,
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
