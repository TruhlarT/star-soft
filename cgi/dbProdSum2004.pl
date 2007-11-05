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

require "/afs/rhic.bnl.gov/star/packages/scripts/dbProdSetup.pl";

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

 @spl = ();

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

my $colls;
my $dPath;

 if($colSet eq "ProtonProton200") {
     $colls = "PPPP200";
   }elsif($colSet eq "ProtonProton48") {
     $colls = "PPPP48";
  }else{
      $colls = $colSet;
  };

my $dtset = $colls."_".$fieldM;

struct FilAttr => {
       flName   => '$',
       hpsize   => '$', 
       dset     => '$',
       Nevts    => '$',
}; 
 

  $dPath = "/daq/";

my $prod = "%$prodSer%";
my $coldata = "$colls%";
my $datasmp = "$dtset%";
my $detconf = "%$detSet%";

#####  Find sets in DataSet table

 my $rootSize = 0;
 my $daqHpEvts = 0;
 my $daqHpSize = 0;
 my $evtHpSize = 0;
 my $evtHpEvts = 0;
 my $TdaqHpSize = 0;
 my $TroHpSize = 0;
 my $TevtHpSize = 0;

 my $topHpss = "/home/starreco/reco";

#####  connect to RunLog DB

&StDbProdConnect();

##### select Geant files from FileCatalog

my @prt;
my $mfield;

if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a' AND site = ?";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$Loc);
 
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND trigger = ? AND site = ? ";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$trigD,$Loc); 

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$Loc); 

 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND trigger = ?  AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$trigD,$Loc); 

}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ?  AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$Loc);
  
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND  dataset like ? AND trigger = ?  AND site = ? ";
 
    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$trigD,$Loc); 

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? '";

     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$detconf,$Loc);  


}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.MuDst.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ?  AND site = ? ";

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

  if(!$evtHpSize)  {$evtHpSize = 0};
  if(!$evtHpEvts)  {$evtHpEvts = 0};


##### find sum(size) and sum(Nevents) for daq files from FileCatalog

if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";
 
     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata) ;

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size), sum(Nevents)  FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger = ? AND dataStatus = 'OK' ";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata,$trigD) ;

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger <> 'n/a'  AND dataStatus = 'OK' ";

      $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp) ;
 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND trigger = ? AND dataStatus = 'OK' " ;

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp,$trigD) ;

}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND dataset like ? AND trigger <> 'n/a' AND dataStatus = 'OK' ";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata,$detconf) ; 

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND  dataset like ? AND trigger = ? AND dataStatus = 'OK' ";

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($coldata,$detconf,$trigD) ; 

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like '$dtset%' AND  dataset like '%$detSet%' AND trigger <> 'n/a'  AND dataStatus = 'OK' ";

        $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp,$detconf) ;  


}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size), sum(Nevents) FROM $FileCatalogT WHERE fName LIKE '%.daq' AND dataset like ? AND  dataset like ? AND trigger = ? AND dataStatus = 'OK' ";

         $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($datasmp,$detconf,$trigD) ;  

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

  if(!$daqHpEvts) {$daqHpEvts = 0};
  if(!$daqHpSize) {$daqHpSize = 0};

if ($trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

 $sql="SELECT sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a' AND site = ? ";

        $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$Loc) ;  
 
}elsif($trigD ne "all" and $fieldM eq "all" and $detSet eq "all") {

 $sql="SELECT sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger = ? AND site = ? ";

         $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$trigD,$Loc) ;   

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet eq "all") {

 $sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

         $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$Loc) ;   
 
}elsif($trigD ne "all" and $fieldM ne "all" and $detSet eq "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND trigger = ?  AND site = ? ";

          $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$trigD,$Loc) ;  

}elsif ($trigD eq "all" and $fieldM eq "all"  and $detSet ne "all" ) {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

          $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$Loc) ;  

}elsif($trigD ne "all" and $fieldM eq "all" and $detSet ne "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND  dataset like ? AND trigger = ?  AND site = ? ";

            $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$coldata,$detconf,$trigD,$Loc) ;    

}elsif ($trigD eq "all" and $fieldM ne "all" and $detSet ne "all" ) {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger <> 'n/a'  AND site = ? ";

            $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$detconf,$Loc) ;  

}elsif($trigD ne "all" and $fieldM ne "all" and $detSet ne "all") {

$sql="SELECT  sum(size) FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE ? AND dataset like ? AND dataset like ? AND trigger = ? AND site = ? ";

             $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($prod,$datasmp,$detconf,$trigD,$Loc) ;   

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

if(!$rootSize) {$rootSize = 0};

    $TdaqHpSize = int($daqHpSize/1024/1024/1024);
    $TevtHpSize = int($evtHpSize/1024/1024/1024);
    $TroHpSize = int($rootSize/1024/1024/1024);
 

 &StDbProdDisconnect();

&cgiSetup();
&beginHtml();

 &printTotal(); 

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
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of MuDst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events <br>in MuDst.root files</B></TD>
</TR> 
   </head>
    <body>
END
}

#####################
sub endHtml {
my $Date = '/bin/date';

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












