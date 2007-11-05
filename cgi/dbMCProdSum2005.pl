#!/usr/bin/env perl
#
# $Id:
#
# $Log:
#
# L.Didenko
#
# dbMCProdSum.pl
#
# Scanning FilesCatalog table to get MC production summary
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use Class::Struct;

require "/afs/rhic.bnl.gov/star/users/didenko/cgi/dbProdSetup.2005.pl";

my $debugOn=0;

my @prodPer;
my $nprodPer = 0;
my %prodFlag = ();
my $mOpt;

 $query = new CGI;

my  $mSet   =  $query->param('SetMC');

 my @spl = ();

 @spl = split(" ",$mSet);
 my $mcSet = $spl[0];

my @prChain = ();
my $myprod;
my $mychname;
my $mchain;
my $mLib;
my %prodChain = ();
my %prodLib = ();
my @prodLb = ();
my @prodCh = ();
my $prodAttr;


&StDbProdConnect();

 my $jobFile = $mcSet;
   $jobFile =~ s/\//_/g;

  my $jobs = "$jobFile%";

$sql="SELECT DISTINCT prodSeries, chainName FROM $JobStatusT where jobfileName like ? ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($jobs);

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $myprod = $fvalue    if($fname eq 'prodSeries'); 
       $mychname = $fvalue  if($fname eq 'chainName');
       }
        $prChain[$nprodPer] = $myprod . "_" .$mychname ;
        $nprodPer++;

      }

 
my $DtSet = $mcSet; 

struct FilAttr => {
       jbID     => '$', 
       dtSet    => '$',
       flName   => '$',
       hpsize   => '$', 
       fpath    => '$',
       Nevts    => '$',
       prSer    => '$',
       chName   => '$',
}; 

struct ChainAttr => { 
       chOpt     => '$',
       libVr     => '$',
		    };
   

#####  Find sets in DataSet table

 my %dstHpEvts = ();
 my $geantHpEvts = 0;
 my $geantHpSize = 0;
 my %dstHpSize = ();
 my %evtHpSize = ();
 my %gntHpSize = ();
 my %xdfHpSize = ();
 my %xdfHpEvts = ();
 my %TgeantHpSize = ();
 my %TdstHpSize = ();
 my %TevtHpSize = ();
 my %TgntHpSize = ();
 my %TxdfHpSize = (); 
 my %prodlib = ();

 my $topHpss = "/home/starreco/reco";

#####  connect to RunLog DB

my $nmfile;

#####  select DST files from FileCatalog
my $dhfile;
my $dhpath;
my $dhjbID;
my $dhdtSet;

my @geantFiles;
my $ngeantFile = 0;
my @hpssDstFiles;
my $nhpssDstFiles = 0;


 $sql="SELECT $FileCatalogT.jobID as fjobID, dataset, fName, size, path, Nevents, $JobStatusT.JobID as jjobID, prodSeries,chainName FROM $FileCatalogT, $JobStatusT WHERE dataset = ? AND type = 'MC_reco' AND hpss ='Y' AND $FileCatalogT.jobID = $JobStatusT.JobID ";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($mcSet);

   while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};
       $fObjAdr = \(FilAttr->new());

      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
         my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       ($$fObjAdr)->jbID($fvalue)     if( $fname eq 'fjobID');        
       ($$fObjAdr)->dtSet($fvalue)    if( $fname eq 'dataset');        
       ($$fObjAdr)->flName($fvalue)   if( $fname eq 'fName');
       ($$fObjAdr)->fpath($fvalue)    if( $fname eq 'path');
       ($$fObjAdr)->hpsize($fvalue)   if( $fname eq 'size');
       ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
       ($$fObjAdr)->prSer($fvalue)    if( $fname eq 'prodSeries');      
       ($$fObjAdr)->chName($fvalue)   if( $fname eq 'chainName');        
     }
  
     $hpssDstFiles[$nhpssDstFiles] = $fObjAdr;  
     $nhpssDstFiles++;
   
    }


  foreach my $dsfile (@hpssDstFiles) {

      $dhjbID  = ($$dsfile)->jbID;
      $dhdtSet = ($$dsfile)->dtSet;
      $dhfile  = ($$dsfile)->flName; 
      $dhpath  = ($$dsfile)->fpath;
      $dhprSer = ($$dsfile)->prSer;
      $dchName = ($$dsfile)->chName;

     $prodAttr = $dhprSer."_".$dchName;

  $sql="SELECT chainOpt, libVersion FROM $ProdOptionsT WHERE chainName = '$dchName'  AND prodSeries = '$dhprSer' ";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
 
  $cursor->execute;

   while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
         my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;
       $prodLib{$prodAttr}   = $fvalue if( $fname eq 'libVersion');
       $prodChain{$prodAttr}   = $fvalue if( $fname eq 'chainOpt');

      }
    }


     if ($dhfile =~ /MuDst.root/) {
        $dstHpSize{$prodAttr} += ($$dsfile)->hpsize;
        $dstHpEvts{$prodAttr} += ($$dsfile)->Nevts; 
   }elsif($dhfile =~ /event.root/) {
        $evtHpSize{$prodAttr} += ($$dsfile)->hpsize;   
   }elsif($dhfile =~ /geant.root/) {
        $gntHpSize{$prodAttr} += ($$dsfile)->hpsize;
  }else{
   next;
 }
}

#####  select daq files from FileCatalog
 my $dqfile;
 my $dqpath;

 $sql="SELECT dataset, fName, path, size, Nevents  FROM $FileCatalogT WHERE dataset = ? AND type = 'MC' AND fName LIKE '%fz%' AND hpss ='Y' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($mcSet);

   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
     $fObjAdr = \(FilAttr->new());

     for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       ($$fObjAdr)->dtSet($fvalue)    if( $fname eq 'dataset');
       ($$fObjAdr)->flName($fvalue)   if( $fname eq 'fName');
       ($$fObjAdr)->fpath($fvalue)    if( $fname eq 'path');
       ($$fObjAdr)->hpsize($fvalue)   if( $fname eq 'size'); 
       ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
     }
  
     $geantFiles[$ngeantFile] = $fObjAdr;  
     $ngeantFile++;
   
   }


  foreach my $onfile (@geantFiles) {

     $dqfile = ($$onfile)->flName;
     $dqpath = ($$onfile)->fpath;

    $geantHpEvts  += ($$onfile)->Nevts;
    $geantHpSize  += ($$onfile)->hpsize; 

 }

&cgiSetup();

print $query->start_html('Production Summmary');

print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

&beginHtml();

my $mprSer;
my $prodSer;
my @prt;
my $MgeantHpSize;
my %MevtHpSize = ();
my %MdstHpSize = ();
my %MgntHpSize = ();
my %MxdfHpSize = ();
my $XgeantHpSize;
my $XevtHpSize;
my $XdstHpSize;
my $XgntHpSize;
my $XxdfHpSize;
my $Lib; 
my $chain;

 &StDbProdDisconnect();



for ($ii = 0; $ii<scalar(@prChain); $ii++) {
 
   $mprSer = $prChain[$ii];

    $MgeantHpSize = $geantHpSize/1024/1024/1024;
    $MevtHpSize{$mprSer} = $evtHpSize{$mprSer}/1024/1024/1024;
    $MdstHpSize{$mprSer} = $dstHpSize{$mprSer}/1024/1024/1024;        
    $MgntHpSize{$mprSer} = $gntHpSize{$mprSer}/1024/1024/1024; 
    $MxdfHpSize{$mprSer} = $xdfHpSize{$mprSer}/1024/1024/1024;
     
    $TgeantHpSize = sprintf( "%8.3f", $MgeantHpSize);
    $TevtHpSize{$mprSer} = sprintf( "%8.3f",$MevtHpSize{$mprSer});
    $TdstHpSize{$mprSer} = sprintf( "%8.3f",$MdstHpSize{$mprSer});
    $TgntHpSize{$mprSer} = sprintf( "%8.3f",$MgntHpSize{$mprSer});
 
    $Lib = $prodLib{$mprSer};
    $chain = $prodChain{$mprSer};
    @prt = split("_",$mprSer);
    $prodSer = $prt[0];  

 &printTotal(); 
 

 }

&beginHtml2();


  for ($ii = 0; $ii<scalar(@prChain); $ii++) {
 
   $mprSer = $prChain[$ii];

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$prodChain{$mprSer}</h3></td>
</TR>
END
 } 

  &endHtml();

exit 0;
#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TgeantHpSize</h3></td>
<td HEIGHT=80><h3>$geantHpEvts</h3></td>
<td HEIGHT=80><h3>$prodSer</h3></td>
<td HEIGHT=80><h3>$prodLib{$mprSer}</h3></td>
<td HEIGHT=80><h3>$dstHpEvts{$mprSer}</h3></td>
<td HEIGHT=80><h3>$TdstHpSize{$mprSer}</h3></td>
<td HEIGHT=80><h3>$TevtHpSize{$mprSer}</h3></td>
<td HEIGHT=80><h3>$TgntHpSize{$mprSer}</h3></td>
</TR>
END

}

######################
sub beginHtml {

print <<END;

   <body BGCOLOR=\"#ccffff\"> 
     <h2 align=center>Production Summary for Dataset: <br> $DtSet</h2>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of GEANT files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in GEANT files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Production Series</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Library Version</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in MuDst.root</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of MuDst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of geant.root files</B></TD>
</TR>
END
}

#####################

#####################
sub beginHtml2 {

print <<END;

<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B><h2> Production Chain</h2></B></TD>
</TR>
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












