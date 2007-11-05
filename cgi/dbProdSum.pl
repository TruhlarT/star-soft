#!/usr/bin/env perl
#
# $Id:
#
# $Log:
#
# L.Didenko
#
# dbProdSum.pl
#
# Scanning FilesCatalog table to get production summary and put it to Web page
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

use File::Find;
use Class::Struct;

my $debugOn=0;

#&cgiSetup();
my ($query) = @_;
$query = new CGI;

my $prodS  =  $query->param('SetP');
my $trig   =  $query->param('SetT');
my $field  =  $query->param('SetF');
my $detect =  $query->param('SetD');
my $coll   =  $query->param('SetC');
my $Loct   =  $query->param('SetLc');

my @spl = ();

 @spl = split(" ", $prodS);
 my $prodSer = $spl[0];
 @spl = ();
 @spl = split(" ", $trig);
 my $trigD =  $spl[0]; 
 @spl = ();
 @spl = split(" ", $field);
 my $fieldM =  $spl[0];
 @spl = ();
 @spl = split(" ", $detect);
 my $detSet =  $spl[0];
 @spl = ();
 @spl = split(" ", $coll);
 my $colSet =  $spl[0];
 @spl = ();
 @spl = split(" ", $Loct);
 my $Loc =  $spl[0];

 $Loc = $Loc."_rcf";

my $dtset = $colSet."_".$fieldM;
my @SetD = (
             $prodSer . "/2000/06",
             $prodSer . "/2000/07",
             $prodSer . "/2000/08", 
             $prodSer . "/2000/09" 
);

struct FilAttr => {
       flName   => '$',
       hpsize   => '$', 
       dset     => '$',
       Nevts    => '$',
}; 
 
my $colls;
my $dPath;
if ($prodSer =~ /^P01/) {
  $dPath = "/2001/";
}
if ($prodSer eq "P01he" or $prodSer eq "P01hi" ) {
  $dPath = "/2000/";
}
if($colSet eq "AuAu130") {
  $colls = "AuAu1";
  $dPath = "/2000/";
}else{
  $colls = $colSet;
  $dPath = "/daq/";
}

#####  Find sets in DataSet table

 my $rootSize = 0;
 my $daqHpEvts = 0;
 my $daqHpSize = 0;
 my $evtHpSize = 0;
 my $evtHpEvts = 0;
 my $TdaqHpSize = 0;
 my $TroHpSize = 0;
 my $TevtHpSize = 0;
 my $TNevPrimVtx = 0;
 my $TNevHadrMinb = 0;
 my $TNevHadrCent = 0;
 my $TNevHiMult = 0;
 my $TNevHiMultZDC = 0;
 my $TNevUPCMinb = 0;
 my $TNevTOPO = 0;
 my $TNevTOPOeff = 0;
 my $TNevTOPOZDC = 0;
 my $TNevLaser = 0;
 my $TNevppMinBias = 0;
 my $TNevppCTB = 0;
 my $TNevppEMChi = 0;
 my $TNevppFPD = 0;
 my $TNevppFPD2 = 0;
 my $TNevppFPDTB = 0;
 my $TNevppMBNoVtx = 0;


 my $topHpss = "/home/starreco/reco";

my $prod = "%$prodSer%";
my $coldata = "$colls%";
my $datasmp = "$dtset%";
my $detconf = "%$detSet%";

&StDbProdConnect();

##### select event.root files from FileCatalog

my @prt;
my $mfield;

if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a' AND site = ?";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$Loc);
 
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND trigger = ? AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$trigD, $Loc);


}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$Loc);

 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND trigger = ?  AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$trigD,$Loc);


}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$Loc);

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ?  AND site = ? ";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$trigD,$Loc);


}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$detconf,$Loc);

}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.event.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ?  AND site = ? ";


     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$detconf,$trigD,$Loc);

}

   while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};
       $fObjAdr = \(FilAttr->new());

      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
         my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

        $evtHpSize = $fvalue   if( $fname eq 'sum(size)');
        $evtHpEvts = $fvalue   if( $fname eq 'sum(Nevents)');
       }
     }


##### find sum(size) and sum(Nevents) for daq files from FileCatalog

if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";

      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata);
 
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger = ?  AND dataStatus = 'OK' ";
 
      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata,$trigD);

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";

       $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp);
 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger = ? AND dataStatus = 'OK' " ;
  
      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp,$trigD);

}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata,$detconf);

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND dataset like ? AND trigger = ? AND dataStatus = 'OK' ";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($coldata,$detconf,$trigD);


}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND  dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";

       $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($datasmp,$detconf);

}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND dataset like ? AND trigger = ?  AND dataStatus = 'OK' ";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($datasmp,$detconf,$trigD);

}

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
     $fObjAdr = \(FilAttr->new());

     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $daqHpSize = $fvalue    if( $fname eq 'sum(size)');
       $daqHpEvts = $fvalue    if( $fname eq 'sum(Nevents)');
     }
   }


if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a' AND site = ? ";

      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$coldata,$Loc);
 
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger = ? AND site = ? ";

       $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$coldata,$trigD,$Loc);


}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

       $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$datasmp,$Loc);
 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE '%$prodSer%' AND dataset like '$dtset%' AND trigger = ?  AND site = ? ";

      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$datasmp,$trigD,$Loc);

}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

       $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$coldata,$detconf,$Loc);

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ? AND site = ? ";

      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$coldata,$detconf,$trigD,$Loc);

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

        $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$datasmp,$detconf,$Loc); 

}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ?  AND site = ? ";

  
      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($prod,$datasmp,$detconf,$trigD,$Loc);

}

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
     $fObjAdr = \(FilAttr->new());

     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $rootSize = $fvalue    if( $fname eq 'sum(size)');
     }
   }


    $TdaqHpSize = int($daqHpSize/1024/1024/1024);
    $TevtHpSize = int($evtHpSize/1024/1024/1024);
    $TroHpSize = int($rootSize/1024/1024/1024);

    if($colSet eq "AuAu200" )   {
     if($fieldM eq "all" ) {

   $sql="SELECT sum(NevPrimVtx), sum(NevHadrMinb), sum(NevHadrCent), sum(NevHiMult), sum(NevHiMultZDC), sum(NevUPCMinb), sum(NevTOPO), sum(NevTOPOZDC), sum(NevTOPOeff) from TriggerEvents where triggerSetup = ? and prodSeries = ? and collision = ? ";

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($trigD,$prodSer,$colSet);

  } else{
 
  $sql="SELECT sum(NevPrimVtx), sum(NevHadrMinb), sum(NevHadrCent), sum(NevHiMult), sum(NevHiMultZDC), sum(NevUPCMinb), sum(NevTOPO), sum(NevTOPOZDC), sum(NevTOPOeff) from TriggerEvents where triggerSetup = ? and prodSeries = ? and magField = ? and collision = ? ";

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($trigD,$prodSer,$fieldM,$colSet);

 }

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS}; 
     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $TNevPrimVtx  = $fvalue    if( $fname eq 'sum(NevPrimVtx)');
       $TNevHadrMinb = $fvalue    if( $fname eq 'sum(NevHadrMinb)');
       $TNevHadrCent = $fvalue    if( $fname eq 'sum(NevHadrCent)');
       $TNevHiMult   = $fvalue    if( $fname eq 'sum(NevHiMult)');
       $TNevHiMultZDC = $fvalue   if( $fname eq 'sum(NevHiMultZDC)');
       $TNevUPCMinb   = $fvalue   if( $fname eq 'sum(NevUPCMinb)');
       $TNevTOPO      = $fvalue   if( $fname eq 'sum(NevTOPO)' );
       $TNevTOPOZDC   = $fvalue   if( $fname eq 'sum(NevTOPOZDC)');
       $TNevTOPOeff   = $fvalue   if( $fname eq 'sum(NevTOPOeff)'); 

  }
 }
}

 
    if($colSet eq "ProtonProton200") {
         if($fieldM eq "all" ) {

   $sql="SELECT sum(NevPrimVtx), sum(NevppMinBias), sum(NevppCTB), sum(NevppEMChi), sum(NevppFPD), sum(NevppFPD2), sum(NevppFPDTB), sum(NevppMBNoVtx) from TriggerEvents where triggerSetup = ? and prodSeries = ? and collision = ? ";

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($trigD,$prodSer,$colSet);

 }else{

   $sql="SELECT sum(NevPrimVtx), sum(NevppMinBias), sum(NevppCTB), sum(NevppEMChi), sum(NevppFPD), sum(NevppFPD2), sum(NevppFPDTB), sum(NevppMBNoVtx) from TriggerEvents where triggerSetup = ? and prodSeries = ? and collision = ? and magField = ? ";

      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($trigD,$prodSer,$colSet,$fieldM);
}

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS}; 
     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;


        $TNevPrimVtx   = $fvalue    if( $fname eq 'sum(NevPrimVtx)');
        $TNevppMinBias = $fvalue    if( $fname eq 'sum(NevppMinBias)');
        $TNevppCTB     = $fvalue    if( $fname eq 'sum(NevppCTB)');
        $TNevppEMChi   = $fvalue    if( $fname eq 'sum(NevppEMChi)');
        $TNevppFPD     = $fvalue    if( $fname eq 'sum(NevppFPD)');
        $TNevppFPD2    = $fvalue    if( $fname eq 'sum(NevppFPD2)');
        $TNevppFPDTB   = $fvalue    if( $fname eq 'sum(NevppFPDTB)');
        $TNevppMBNoVtx = $fvalue    if( $fname eq 'sum(NevppMBNoVtx)');

         }
      }
   }


 &StDbProdDisconnect();

&cgiSetup();
&beginHtml();

 &printTotal(); 

 if($colSet eq "AuAu200") {

 &begin2Html();
 &printTrigSum();
 }elsif($colSet eq "ProtonProton200") {

  &begin3Html();
 &printTrigpp();
 }

#####  finished with database
  
  &endHtml();

#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TdaqHpSize</h3></td>
<td HEIGHT=80><h3>$daqHpEvts</h3></td>
<td HEIGHT=80><h3>$TroHpSize</h3></td>
<td HEIGHT=80><h3>$TevtHpSize</h3></td>
<td HEIGHT=80><h3>$evtHpEvts</h3></td>
</TR>
END

}

######################

 sub printTrigSum {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TNevPrimVtx</h3></td>
<td HEIGHT=80><h3>$TNevHadrMinb</h3></td>
<td HEIGHT=80><h3>$TNevHadrCent</h3></td>
<td HEIGHT=80><h3>$TNevHiMult</h3></td>
<td HEIGHT=80><h3>$TNevHiMultZDC</h3></td>
<td HEIGHT=80><h3>$TNevUPCMinb</h3></td>
<td HEIGHT=80><h3>$TNevTOPO</h3></td>
<td HEIGHT=80><h3>$TNevTOPOZDC</h3></td>
<td HEIGHT=80><h3>$TNevTOPOeff</h3></td>
</TR>
END

}

######################

 sub printTrigpp {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TNevPrimVtx</h3></td>
<td HEIGHT=80><h3>$TNevppMinBias</h3></td>
<td HEIGHT=80><h3>$TNevppCTB</h3></td>
<td HEIGHT=80><h3>$TNevppEMChi</h3></td>
<td HEIGHT=80><h3>$TNevppFPD</h3></td>
<td HEIGHT=80><h3>$TNevppFPD2</h3></td>
<td HEIGHT=80><h3>$TNevppFPDTB</h3></td>
<td HEIGHT=80><h3>$TNevppMBNoVtx</h3></td>
</TR>
END

}

######################

sub beginHtml {

print <<END;

  <html>
  <head>
          <title>Production Summary</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h2 align=center>Summary for $trigD  $colSet events in $prodSer production </h2>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events<br>in DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Total size(GB) of root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events <br>in event.root files</B></TD>
</TR> 
   </head>
    <body>
END
}

#######################################################################################################

sub begin2Html {

print <<END;

  <html>
  <head>
          <title>Production Summary by Trigger</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Events<br> with primary vertex</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hadronic MinBias</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hadronic Central</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hi-mult</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hi-mult & ZDC </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>UPC MinBias</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPO</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPO & ZDC</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPOeff</B></TD>
</TR> 

   </head>
    <body>
END
}

#######################################################################################################

sub begin3Html {

print <<END;

  <html>
  <head>
          <title>Production Summary by Trigger</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Events<br> with primary vertex</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppMinBias</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppCTB</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppEMChi</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppFPD</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppFPD2</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppFPD_TB</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>ppMBNoVtx</B></TD>
</TR> 

   </head>
    <body>
END
}

#####################
sub endHtml {
my $Date = `/bin/date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Wed July 26  05:29:25 MET 2000 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}












