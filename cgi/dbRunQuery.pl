#! /usr/local/bin/perl -w
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

require "/afs/rhic/star/packages/scripts/dbCpProdSetup.pl";

use Mysql;
use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

#&cgiSetup();

my $debugOn = 0;

my ($query) = @_;

$query = new CGI;

my $collSet =  $query->param('SetCl');
my $prodSr  =  $query->param('SetPrd');
my $detrSet =  $query->param('SetDet');
my $datSet  =  $query->param('SetTrg');
my $fldSet  =  $query->param('SetField');
my $frSet   =  $query->param('SetForm');
my $lctSet  =  $query->param('SetLc');


my $colSet;
my $dPath;

if ($collSet eq "AuAu130") {
 $colSet = "AuAu1";
 $dPath = "/2000/";
}else {
$colSet = $collSet;
$dPath = "/daq/";
}

my @joinSet = ( $colSet. "%" .$datSet . "%" . $detrSet . "%" .$fldSet . "%" . $frSet . "%" . $lctSet. "%" .$prodSr. "%". $dPath );


#####  connect to operation DB

 &StDbProdConnect();

my $mmRun;
my @runSet;
my $nrunSet = 0;

if( $frSet =~ /root/) { 

if($detrSet eq "all" and $datSet ne "all" and $fldSet ne "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND dataset like '$colSet%' AND dataset like  '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet ne "all" and $datSet ne "all" and $fldSet ne "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND dataset like  '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet ne "all" and $datSet eq "all" and $fldSet ne "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND dataset like '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet eq "all" and $datSet eq "all" and $fldSet ne "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND dataset like '$colSet%' AND dataset like '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";
}

elsif($detrSet eq "all" and $datSet ne "all" and $fldSet eq "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet ne "all" and $datSet ne "all" and $fldSet eq "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND trigger = '$datSet' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet ne "all" and $datSet eq "all" and $fldSet eq "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";

}elsif($detrSet eq "all" and $datSet eq "all" and $fldSet eq "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSr%' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' order by runID ";
}
}elsif($frSet eq "daq")  { 

if($detrSet eq "all" and $datSet ne "all" and $fldSet ne "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE trigger = '$datSet' AND dataset like '$colSet%' AND dataset like  '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet ne "all" and $datSet ne "all" and $fldSet ne "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE trigger = '$datSet' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND dataset like  '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet ne "all" and $datSet eq "all" and $fldSet ne "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE dataset like '%$detrSet%' AND dataset like '$colSet%' AND dataset like '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet eq "all" and $datSet eq "all" and $fldSet ne "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE dataset like '$colSet%' AND dataset like '%$fldSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";
}

elsif($detrSet eq "all" and $datSet ne "all" and $fldSet eq "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE trigger = '$datSet' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet ne "all" and $datSet ne "all" and $fldSet eq "all") {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE trigger = '$datSet' AND dataset like '%$detrSet%' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet ne "all" and $datSet eq "all" and $fldSet eq "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE dataset like '%$detrSet%' AND dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";

}elsif($detrSet eq "all" and $datSet eq "all" and $fldSet eq "all" ) {

 $sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE dataset like '$colSet%' AND fName like '%$frSet' AND site like '$lctSet%' AND path like '%$dPath%' AND dataStatus = 'OK' order by runID ";
 }
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

if($nrunSet == 1) {
  $runSet[0] = "no data";
}

 &StDbProdDisconnect();      
  
      
#$qq = new CGI;

print $query->header;
print $query->start_html('dbRunQuery');
print $query->startform(-action=>"dbRunBrows.pl");  

  print " <title>Query for Run Number</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
if ($frSet eq "daq") {
  print "  <h2 align=center>Run Numbers for $collSet collisions </h2>\n";
}else{
  print "  <h2 align=center>Run Numbers for $collSet collisions in $prodSr production </h2>\n";
}
  print " </head>\n";
  print " <body>";

print <<END;
</SELECT><br>
<p>
<br>
END

 print "<p>";
 print "<h2 align=center>Run Numbers:</h2>";
 print "<h4 align=center>";
 print $query->popup_menu(-name=>'runN',
                    -values=>\@runSet,
                    -default=>'all',
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


#if($query->param) {
#  dbRunBrows($query);
#}
  
print $query->end_html; 







