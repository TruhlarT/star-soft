#! /opt/star/bin/perl -w
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

use CGI;

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

use File::Find;
use Class::Struct;

my $debugOn=0;

my @prodPer = ("mdc1", "mdc2", "postmdc2", "prod4", "prod5", "mdc3", "prod6", "P00hi");
my %prodFlag = ();

#my ($query) = @_;

$query = new CGI;

$mcSet   =  $query->param('SetMC');

my @Nchain = ("tfs","tss","trs");
my $prodCh; 
my @prChain;
my $kk = 0;

for( $ll = 0; $ll<scalar( @prodPer); $ll++) {
  for( $ii = 0; $ii<scalar(@Nchain); $ii++) {
    $prodCh = $prodPer[$ll] . "_" . $Nchain[$ii];
    $prodFlag{$prodCh} = 0;
    $prChain[$kk] = $prodCh;
   $kk++;
  }
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

&StDbProdConnect();

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



 $sql="SELECT $FileCatalogT.jobID as fjobID, dataset, fName, size, path, Nevents, $JobStatusT.JobID as jjobID, prodSeries,chainName FROM $FileCatalogT, $JobStatusT WHERE dataset = '$mcSet' AND type = 'MC_reco' AND hpss ='Y' AND $FileCatalogT.jobID = $JobStatusT.JobID ";

   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

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
      } elsif($dchName =~ /tss/) {
         $chainN = "tss";
       }elsif($dchName =~ /trs/) {
         $chainN = "trs";
       }

      $prodChain = $dhprSer . "_" . $chainN;

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
        $dstHpEvts{$prodChain} += ($$dsfile)->Nevts; 
        $dstHpSize{$prodChain} += ($$dsfile)->hpsize;
   }elsif($dhfile =~ /event.root/) {
        $evtHpSize{$prodChain} += ($$dsfile)->hpsize;    
   }elsif($dhfile =~ /geant.root/) {
        $gntHpSize{$prodChain} += ($$dsfile)->hpsize;
   }elsif($dhfile =~ /.xdf/) {
        $xdfHpEvts{$prodChain} += ($$dsfile)->Nevts;
        $xdfHpSize{$prodChain} += ($$dsfile)->hpsize;  
  }else{
   next;
 }
}

#####  select daq files from FileCatalog
 my $dqfile;
 my $dqpath;

 $sql="SELECT dataset, fName, path, size, Nevents  FROM $FileCatalogT WHERE dataset = '$mcSet' AND type = 'MC' AND fName LIKE '%fz%' AND hpss ='Y' ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

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

&beginHtml();

my $mprSer;
my $prodSer;
my @prt;

for ($ii = 0; $ii<scalar(@prChain); $ii++) {
   $mprSer = $prChain[$ii];
  if($prodFlag{$mprSer} == 1) {  

    $TgeantHpSize = int($geantHpSize/1024/1024/1024);
    $TevtHpSize{$mprSer} = int($evtHpSize{$mprSer}/1024/1024/1024);
    $TdstHpSize{$mprSer} = int($dstHpSize{$mprSer}/1024/1024/1024);        
    $TgntHpSize{$mprSer} = int($gntHpSize{$mprSer}/1024/1024/1024); 
    $TxdfHpSize{$mprSer} = int($xdfHpSize{$mprSer}/1024/1024/1024);  
   
    if ($dstHpEvts{$mprSer} == 0) {
      $dstHpEvts{$mprSer} = $xdfHpEvts{$mprSer}
    }
 
    @prt = split("_",$mprSer);
    $prodSer = $prt[0];  

 &printTotal(); 

   }else{
    next;
  }
 }

#####  finished with database
 &StDbProdDisconnect();
  
  &endHtml();

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
<td HEIGHT=80><h3>$TxdfHpSize{$mprSer}</h3></td>
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
     <h2 align=center>Production Summary for Dataset: <br> $DtSet</h2>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of GEANT files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in GEANT files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Production Series</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Library Version</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Production Chain</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in DST</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of dst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of geant.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of .xdf files</B></TD>
</TR> 
   </head>
    <body>
END
}


#####################
sub endHtml {
my $Date = `date`;

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












