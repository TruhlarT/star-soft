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

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn=0;

my @prodPer;
my $nprodPer;
my %prodFlag = ();

$query = new CGI;

 my $mSet   =  $query->param('SetMC');

 my @spl = ();

 @spl = split(" ",$mSet);
$mcSet = $spl[0];

my @Nchain = ("tfs","trs");
my $prodCh; 
my @prChain;
my $kk = 0;
my $myprod;

&StDbProdConnect();

my $jobFile = $mcSet;
   $jobFile =~ s/\//_/g;

my $jobs = "$jobFile%";

$sql="SELECT DISTINCT prodSeries FROM $JobStatusT where jobfileName like ? ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($jobs);

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $myprod = $fvalue  if($fname eq 'prodSeries'); 
       }
        $prodPer[$nprodPer] = $myprod;
         $nprodPer++;
      }
# $prodPer[0] = "P001hi";

for( $ll = 0; $ll<scalar( @prodPer); $ll++) {
  for( $ii = 0; $ii<scalar(@Nchain); $ii++) {
    $prodCh = $prodPer[$ll] . "_" . $Nchain[$ii];
    $prodFlag{$prodCh} = 0;
    $prChain[$kk] = $prodCh;
   $kk++;
  }
}
    $prodCh = "MDC4" . "_" . "test" . "_" ."trs2y";
    $prodFlag{$prodCh} = 0;
    $prChain[$kk] = $prodCh;
   
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


my %mchain = ();
my %mLib = ();
my $mprodS;
my $prodChain;
my $chainN;


  foreach my $dsfile (@hpssDstFiles) {

      $dhjbID  = ($$dsfile)->jbID;
      $dhdtSet = ($$dsfile)->dtSet;
      $dhfile  = ($$dsfile)->flName; 
      $dhpath  = ($$dsfile)->fpath;
      $dhprSer = ($$dsfile)->prSer;
      $dchName = ($$dsfile)->chName;

	if ($dchName =~ /tfs/) {
         $chainN = "tfs";
       }elsif($dchName =~ /trs/) {
         $chainN = "trs";
       }

       if ($dchName eq "trs2y") {
      $prodChain = $dhprSer . "_" . "test" . "_" . "trs2y"; 
    }else {
      $prodChain = $dhprSer . "_" . $chainN;
    }

 $sql="SELECT chainOpt, libVersion, prodSeries FROM $ProdOptionsT WHERE chainName = '$dchName'  AND prodSeries = '$dhprSer' ";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

   while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
         my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

       $mprodS        = $fvalue if( $fname eq 'prodSeries');
       $mchain{$prodChain} = $fvalue if( $fname eq 'chainOpt');
       $mLib{$prodChain}   = $fvalue if( $fname eq 'libVersion'); 

      }
    }

      $prodFlag{$prodChain} = 1;  
     if ($dhfile =~ /dst.root/) {
        $dstHpSize{$prodChain} += ($$dsfile)->hpsize;
   }elsif($dhfile =~ /event.root/) {
        $evtHpSize{$prodChain} += ($$dsfile)->hpsize; 
        $dstHpEvts{$prodChain} += ($$dsfile)->Nevts;   
   }elsif($dhfile =~ /geant.root/) {
        $gntHpSize{$prodChain} += ($$dsfile)->hpsize;
  }else{
   next;
 }
}

#####  select MC files from FileCatalog
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

for ($ii = 0; $ii<scalar(@prChain); $ii++) {
   $mprSer = $prChain[$ii];
  if($prodFlag{$mprSer} == 1) {  

    $MgeantHpSize = $geantHpSize/1024/1024/1024;
    $MevtHpSize{$mprSer} = $evtHpSize{$mprSer}/1024/1024/1024;
    $MdstHpSize{$mprSer} = $dstHpSize{$mprSer}/1024/1024/1024;        
    $MgntHpSize{$mprSer} = $gntHpSize{$mprSer}/1024/1024/1024; 
    $MxdfHpSize{$mprSer} = $xdfHpSize{$mprSer}/1024/1024/1024;
     
    $TgeantHpSize = sprintf( "%8.3f", $MgeantHpSize);
    $TevtHpSize{$mprSer} = sprintf( "%8.3f",$MevtHpSize{$mprSer});
    $TdstHpSize{$mprSer} = sprintf( "%8.3f",$MdstHpSize{$mprSer});
    $TgntHpSize{$mprSer} = sprintf( "%8.3f",$MgntHpSize{$mprSer});
    $TxdfHpSize{$mprSer} = sprintf( "%8.3f",$MxdfHpSize{$mprSer});
 
    if ($dstHpEvts{$mprSer} == 0) {
      $dstHpEvts{$mprSer} = $xdfHpEvts{$mprSer}
    }
 
    if ($mprSer =~ /MDC4_test/){
    $prodSer = "MDC4_test";
  }else {
    @prt = split("_",$mprSer);
    $prodSer = $prt[0];  
  }
 &printTotal(); 

   }else{
    next;
  }
 }
#####  finished with database
 &StDbProdDisconnect();

  &endHtml();

exit 0;
#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TgeantHpSize</h3></td>
<td HEIGHT=80><h3>$geantHpEvts</h3></td>
<td HEIGHT=80><h3>$prodSer</h3></td>
<td HEIGHT=80><h3>$mLib{$mprSer}</h3></td>
<td HEIGHT=80><h3>$mchain{$mprSer}</h3></td>
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
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Production Chain</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in event.root</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of dst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of geant.root files</B></TD>
</TR> 
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












