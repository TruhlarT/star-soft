#! /usr/local/bin/perl -w
#
# $Id:
#
# $Log:
#
# L.Didenko
#
# dbSumDAQMonth.pl
#
# Scanning FilesCatalog table to get production summary and put it to Web page
# 
################################################################################################

use CGI;

require "/afs/rhic/star/packages/cgi/dbCpProdSetup.pl";
require "/afs/rhic/star/packages/dev/mgr/dbDescriptorSetup.pl";

use File::Find;
use Class::Struct;

my $debugOn=0;

&cgiSetup();

my @SetD = (
             "P00hm/2000/06",
             "P00hm/2000/07",
             "P00hm/2000/08", 
             "P00hm/2000/09" 
);

struct FilAttr => {
       flName   => '$',
       hpsize   => '$', 
       fpath    => '$',
       Nevts    => '$',
       numRun   => '$',
}; 
 
my $prodSer = "P00hm" ;

&beginHtml();


#####  Find sets in DataSet table

 my %dstDEvts = ();
 my %dstHpEvts = ();
 my %daqHpEvts = ();
 my %daqHpSize = ();
 my %dstDSize = ();
 my %dstHpSize = ();
 my $periodRun;
 my @DRun;
 my $nRun = 0;
 my $myRun;
 my @jobSum_set;
 my $jobSum_no = 0;
 my @dirP;
 my $dirR;
 my $topHpss = "/home/starreco/reco";
 my @topDisk = (
                "/star/data14/reco",
                "/star/rcf/disk00001/star/reco", 
);

 my @prodRun = ("JUNE-2000","JULY-2000","AUGUST-2000","SEPTEMBER-2000"); 

 my %RunHash = (
                  "2000/06" => "JUNE-2000",
                  "2000/07" => "JULY-2000",
                  "2000/08" => "AUGUST-2000",
                  "2000/09" => "SEPTEMBER-2000"                    
 ); 


#####  connect to RunLog DB

 &StDbDescriptorConnect();

my $mmRun;
my @runSet;
my $nrunSet = 0;

 $sql="SELECT runNumber FROM $runDescriptorT WHERE category = 'physics'";

   $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;
 
    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

        for($i=0;$i<$cols;$i++) {
           my $fvalue=$fields[$i];
           my $fname=$cursor->{NAME}->[$i];
#        print "$fname = $fvalue\n" ;
       
         $mmRun = $fvalue     if( $fname eq 'runNumber'); 
         }
        $runSet[$nrunSet] = $mmRun;
        $nrunSet++;
 }

 &StDbDescriptorDisconnect();      

&StDbProdConnect();

##### select Geant files from FileCatalog

my $nmfile;
my @hpssInFiles;


$sql="SELECT DISTINCT runID FROM $FileCatalogT WHERE jobID like '%$prodSer%' AND fName LIKE '%dst.root' AND hpss = 'Y'";
  $cursor =$dbh->prepare($sql)
    || die "Cannot prepare statement: $DBI::errstr\n";
  $cursor->execute;

  while(@fields = $cursor->fetchrow) {
    my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
      my $fvalue=$fields[$i];
      my $fname=$cursor->{NAME}->[$i];
      print "$fname = $fvalue\n" if $debugOn;
  
       $myRun = $fvalue  if($fname eq 'runID');
    }
  
    $DRun[$nRun] = $myRun;
    $nRun++;
    }

#####  select DST files on HPSS from FileCatalog
my $dhfile;
my $dhpath;
my $hpSz;
my @OnlFiles;
my $nOnlFile = 0;
my @hpssDstFiles;

 $nhpssDstFiles = 0;

 $sql="SELECT runID, size, fName, path, Nevents  FROM $FileCatalogT WHERE fName LIKE '%dst.root' AND JobID LIKE '%$prodSer%' AND hpss ='Y'";
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
       ($$fObjAdr)->numRun($fvalue)   if( $fname eq 'runID');
     }
  
     $hpssDstFiles[$nhpssDstFiles] = $fObjAdr;  
     $nhpssDstFiles++;
   
    }

  foreach my $dsfile (@hpssDstFiles) {

     $dhfile = ($$dsfile)->flName; 
     $dhpath = ($$dsfile)->fpath;
     @dirP = split ("/", $dhpath);
     $dirR = $dirP[5] . "/" . $dirP[6];
   $periodRun = $RunHash{$dirR};
   $dstHpEvts{$periodRun}  += ($$dsfile)->Nevts; 
   $dstHpSize{$periodRun}  += ($$dsfile)->hpsize;
   }

#####  select daq files from FileCatalog
 my $dqfile;
 my $dqpath;

   for ($ll=0; $ll<scalar(@runSet); $ll++) {
  
 $sql="SELECT runID, size, fName,path, Nevents  FROM $FileCatalogT WHERE runID = '$runSet[$ll]' AND fName LIKE '%daq' AND hpss ='Y' ";
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
       ($$fObjAdr)->numRun($fvalue)   if( $fname eq 'runID');
     }
  
     $OnlFiles[$nOnlFile] = $fObjAdr;  
     $nOnlFile++;
   
   }

}

  foreach my $onfile (@OnlFiles) {

     $dqfile = ($$onfile)->flName;
     $dqpath = ($$onfile)->fpath;
     $dqEvts = ($$onfile)->Nevts;
     $dqEvts -= 1;
     @dirP = split ("/", $dqpath);
     $dirR = $dirP[5] . "/" . $dirP[6];
    $periodRun = $RunHash{$dirR}; 
    $daqHpEvts{$periodRun}  += $dqEvts;
    $daqHpSize{$periodRun}  += ($$onfile)->hpsize; 

#   print "Period of run :", $dirR," % ", $periodRun{$dqRun}, "\n";

 }

#####   select DST files on DISK from FileCatalog

my $ddfile;
my $ddSet;
my @diskDstFiles;

 $ndiskDstFiles = 0;

 $sql="SELECT runID, fName, size, path, Nevents FROM $FileCatalogT WHERE fName LIKE '%dst.root' AND jobID LIKE '%$prodSer%' AND site = 'disk_rcf'";
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

       ($$fObjAdr)->flName($fvalue)    if( $fname eq 'fName');
       ($$fObjAdr)->fpath($fvalue)     if( $fname eq 'path');
       ($$fObjAdr)->hpsize($fvalue)    if( $fname eq 'size');
       ($$fObjAdr)->Nevts($fvalue)     if( $fname eq 'Nevents');
       ($$fObjAdr)->numRun($fvalue)    if( $fname eq 'runID');
     }
  
     $diskDstFiles[$ndiskDstFiles] = $fObjAdr;  
     $ndiskDstFiles++;
    }
 
 foreach my $ddfile (@diskDstFiles) {

    $dhfile = ($$ddfile)->flName;
    $dhpath = ($$ddfile)->fpath;
    @dirP = split ("/", $dhpath);
 if( $dhpath =~ /data0/ ) {
    $dirR = $dirP[6] . "/" . $dirP[7];
 }
   elsif($dhpath =~ /disk00001/ ) {
    $dirR = $dirP[7] . "/" . $dirP[8];   
}
    $periodRun = $RunHash{$dirR};
    $dstDEvts{$periodRun}  += ($$ddfile)->Nevts;   
    $dstDSize{$periodRun}  += ($$ddfile)->hpsize;     
   }


###### initialize for total amount

 my $TdstDEvt   = 0; 
 my $TdstHEvt   = 0;
 my $TdaqHEvt   = 0;
 my $TdstDSize  = 0; 
 my $TdstHSize  = 0;
 my $TdaqHSize  = 0;
 my $RunMonth;
 my $runD;
     foreach $runD (@prodRun) {
      
         $RunMonth = $runD;   
         if (! defined $dstHpEvts{$runD}) {$dstHpEvts{$runD} = 0 };
         if (! defined $dstDEvts{$runD})  {$dstDEvts{$runD} = 0 };
         if (! defined $daqHpEvts{$runD}) {$daqHpEvts{$runD} = 0 };
         if (! defined $dstHpSize{$runD}) {$dstHpSize{$runD} = 0 };
         if (! defined $dstDSize{$runD})  {$dstDSize{$runD} = 0 };
         if (! defined $daqHpSize{$runD}) {$daqHpSize{$runD} = 0 };
         $dstHpSize{$runD} = int($dstHpSize{$runD}/1024/1024/1024);
         $dstDSize{$runD}  = int($dstDSize{$runD}/1024/1024/1024);
         $daqHpSize{$runD} = int($daqHpSize{$runD}/1024/1024/1024);  
         $TdstHEvt    +=  $dstHpEvts{$runD}; 
         $TdstDEvt    +=  $dstDEvts{$runD}; 
         $TdaqHEvt    +=  $daqHpEvts{$runD};
         $TdstDSize   +=  $dstDSize{$runD};
         $TdstHSize   +=  $dstHpSize{$runD}; 
         $TdaqHSize   +=  $daqHpSize{$runD};
  &printRow(); 
       }

  &printTotal(); 

#####  finished with database
  &StDbProdDisconnect();
  
 &endHtml();

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER HEIGHT=60>
<td HEIGHT=60><h3>$RunMonth</h3></td>
<td HEIGHT=60><h3>$daqHpSize{$RunMonth}</h3></td>
<td HEIGHT=60><h3>$daqHpEvts{$RunMonth}</h3></td>
<td HEIGHT=60><h3>$dstHpSize{$RunMonth}</h3></td>
<td HEIGHT=60><h3>$dstHpEvts{$RunMonth}</h3></td>
<td HEIGHT=60><h3>$dstDSize{$RunMonth}</h3></td>
<td HEIGHT=60><h3>$dstDEvts{$RunMonth}</h3></td>
</TR>
END

}

#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
<td HEIGHT=80><h3>TOTAL</h3></td>
<td HEIGHT=80><h3>$TdaqHSize</h3></td>
<td HEIGHT=80><h3>$TdaqHEvt</h3></td>
<td HEIGHT=80><h3>$TdstHSize</h3></td>
<td HEIGHT=80><h3>$TdstHEvt</h3></td>
<td HEIGHT=80><h3>$TdstDSize</h3></td>
<td HEIGHT=80><h3>$TdstDEvt</h3></td>
</TR>
END

}

######################
sub beginHtml {

print <<END;
  <html>

  <head>
          <title>Production Summary for Real Data</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>Production Summary for period P00hm</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=100><B>MONTH/YEAR</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of DST files<br> on HPSS</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in DST on HPSS</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of DST files<br> on Disk</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in DST on Disk</B></TD>
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












