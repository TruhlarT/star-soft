#! /opt/star/bin/perl -w
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

use CGI;

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

use File::Find;
use Class::Struct;

my $debugOn=0;

#&cgiSetup();
my ($query) = @_;
$query = new CGI;

$prodSer =  $query->param('SetP');
$trigD   =  $query->param('SetT');

my @SetD = (
             $prodSer . "/2000/06",
             $prodSer . "/2000/07",
             $prodSer . "/2000/08", 
             $prodSer . "/2000/09" 
);

struct FilAttr => {
       flName   => '$',
       hpsize   => '$', 
       fpath    => '$',
       Nevts    => '$',
}; 
 

#####  Find sets in DataSet table

 my $dstHpEvts = 0;
 my $daqHpEvts = 0;
 my $daqHpSize = 0;
 my $dstHpSize = 0;
 my $evtHpSize = 0;
 my $TdaqHpSize = 0;
 my $TdstHpSize = 0;
 my $TevtHpSize = 0;

 my $topHpss = "/home/starreco/reco";

#####  connect to RunLog DB

&StDbProdConnect();

##### select Geant files from FileCatalog

my $nmfile;
my @hpssInFiles;


#####  select DST files on HPSS from FileCatalog
my $dhfile;
my $dhpath;
my @OnlFiles;
my $nOnlFile = 0;
my @hpssDstFiles;

 $nhpssDstFiles = 0;


 $sql="SELECT fName, size, path, Nevents  FROM $FileCatalogT WHERE fName LIKE '%.root' AND jobID LIKE '%$prodSer%' AND trigger = '$trigD' AND hpss ='Y'";
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

       ($$fObjAdr)->flName($fvalue)   if( $fname eq 'fName');
       ($$fObjAdr)->fpath($fvalue)    if( $fname eq 'path');
       ($$fObjAdr)->hpsize($fvalue)   if( $fname eq 'size');
       ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
     }
  
     $hpssDstFiles[$nhpssDstFiles] = $fObjAdr;  
     $nhpssDstFiles++;
   
    }

  foreach my $dsfile (@hpssDstFiles) {

      $dhfile = ($$dsfile)->flName; 
      $dhpath = ($$dsfile)->fpath;
     if ($dhfile =~ /dst.root/) {
        $dstHpEvts  += ($$dsfile)->Nevts; 
        $dstHpSize  += ($$dsfile)->hpsize;
   }elsif($dhfile =~ /event.root/) {
        $evtHpSize  += ($$dsfile)->hpsize;    
  }else{
   next;
 }
}
#####  select daq files from FileCatalog
 my $dqfile;
 my $dqpath;

 $sql="SELECT fName, path, size, Nevents  FROM $FileCatalogT WHERE trigger = '$trigD' AND fName LIKE '%daq' AND hpss ='Y' ";
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
# print "$fname = $fvalue\n";
       ($$fObjAdr)->flName($fvalue)   if( $fname eq 'fName');
       ($$fObjAdr)->fpath($fvalue)    if( $fname eq 'path');
       ($$fObjAdr)->hpsize($fvalue)   if( $fname eq 'size'); 
       ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
     }
  
     $OnlFiles[$nOnlFile] = $fObjAdr;  
     $nOnlFile++;
   
   }


  foreach my $onfile (@OnlFiles) {

     $dqfile = ($$onfile)->flName;
     $dqpath = ($$onfile)->fpath;
     $dqEvts = ($$onfile)->Nevts;
     $dqEvts -= 1;

    $daqHpEvts  += $dqEvts;
    $daqHpSize  += ($$onfile)->hpsize; 

 }

    $TdaqHpSize = int($daqHpSize/1024/1024/1024);
    $TevtHpSize = int($evtHpSize/1024/1024/1024);
    $TdstHpSize = int($dstHpSize/1024/1024/1024);        

&cgiSetup();
&beginHtml();

 &printTotal(); 

#####  finished with database
 &StDbProdDisconnect();
  
  &endHtml();

#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>$TdaqHpSize</h3></td>
<td HEIGHT=80><h3>$daqHpEvts</h3></td>
<td HEIGHT=80><h3>$TdstHpSize</h3></td>
<td HEIGHT=80><h3>$TevtHpSize</h3></td>
<td HEIGHT=80><h3>$dstHpEvts</h3></td>
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
     <h2 align=center>Summary for $trigD events production<br> $prodSer series </h2>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events<br>in DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of dst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events<br>in DST</B></TD>
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












