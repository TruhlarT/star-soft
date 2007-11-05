#! /usr/local/bin/perl -w
#
# $Id:
#
# $Log:
#
# L.Didenko
#
# dbSumRun.pl
#
# Scanning FilesCatalog table to get production summary and put it to Web page
# 
################################################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

use File::Find;
use Class::Struct;

my $debugOn=0;

my ($query) = @_;
 
$query = new CGI;

$prodSr =  $query->param('setP');
$runNum = $query->param('runN');

my $prodDir = "/home/starreco/reco/". $prodSr; 

struct FilAttr => {
       flName   => '$',
       DtSt     => '$', 
       fpath    => '$',
       fsize    => '$',
       Nevts    => '$',
       numRun   => '$',
       trg      => '$',
}; 
 

##### Find sets in DataSet table

 my %dstHpEvts = ();
 my %daqHpEvts = ();
 my %daqHpSize = ();
 my %dstHpSize = ();
 my %prodRun = ();
 my %periodRun = ();
 my %dtSet = ();
 my %dtTrg = ();
 my %numFiles = ();
 my @DRun;
 my $nRun = 0;
 my $myRun;
 my @jobSum_set;
 my $jobSum_no = 0;
 my @dirP;
 my $dirR;
 my $topHpss = "/home/starreco/reco";

&StDbProdConnect();

my  $nmfile;
my  @hpssInFiles;


##### select DST files on HPSS from FileCatalog
 my $hdfile;
 my $dhRun;
 my $dqRun;
 my $dhSet;
 my $dhTrg;
 my @OnlFiles;
 my $nOnlFile = 0;
 my @hpssDstFiles;
  $nhpssDstFiles = 0;

  $sql="SELECT runID, dataset, fName, path, size, Nevents, trigger  FROM $FileCatalogT WHERE runID = '$runNum' AND fName LIKE '%.event.root' AND path like '%$prodSr%' AND hpss = 'Y'";
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
 
      ($$fObjAdr)->DtSt($fvalue)     if( $fname eq 'dataset'); 
      ($$fObjAdr)->flName($fvalue)   if( $fname eq 'fName');
      ($$fObjAdr)->fpath($fvalue)    if( $fname eq 'path'); 
      ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
      ($$fObjAdr)->fsize($fvalue)    if( $fname eq 'size');
      ($$fObjAdr)->numRun($fvalue)   if( $fname eq 'runID');
      ($$fObjAdr)->trg($fvalue)      if( $fname eq 'trigger');
    }
  
    $hpssDstFiles[$nhpssDstFiles] = $fObjAdr;  
    $nhpssDstFiles++;
   
    }

 foreach my $dsfile (@hpssDstFiles) {

    $dhfile = ($$dsfile)->flName;
    $dhpath = ($$dsfile)->fpath;
    $dhRun =  ($$dsfile)->numRun;
    $dhSet =  ($$dsfile)->DtSt;
    $dhTrg =  ($$dsfile)->trg; 
    @dirP = split ("/", $dhpath);
    $dirR = $dirP[5] . "/" . $dirP[6];

  $periodRun{$dhRun} = $RunHash{$dirR};
  $dstHpEvts{$dhRun}  += ($$dsfile)->Nevts; 
  $dstHpSize{$dhRun}  += ($$dsfile)->fsize;
  $dtSet{$dhRun} = $dhSet;
  $dtTrg{$dhRun} = $dhTrg;
  }

##### select daq files from FileCatalog
  my $dqfile;
  my $dqRun;

  $sql="SELECT runID, fName,path, size, Nevents  FROM $FileCatalogT WHERE runID = '$runNum' AND fName LIKE '%daq' AND hpss ='Y'";
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
      ($$fObjAdr)->fpath($fvalue)   if( $fname eq 'path');
      ($$fObjAdr)->fsize($fvalue)   if( $fname eq 'size'); 
      ($$fObjAdr)->Nevts($fvalue)    if( $fname eq 'Nevents');
      ($$fObjAdr)->numRun($fvalue)   if( $fname eq 'runID');
    }
    $OnlFiles[$nOnlFile] = $fObjAdr;  
    $nOnlFile++;
   
    }

 foreach my $onfile (@OnlFiles) {

    $dqfile = ($$onfile)->flName;
    $dqpath = ($$onfile)->fpath;
    $dqRun = ($$onfile)->numRun;
    @dirP = split ("/", $dqpath);
    $dirR = $dirP[5] . "/" . $dirP[6];
   $periodRun{$dqRun} = $RunHash{$dirR}; 
   $daqHpEvts{$dqRun}  += ($$onfile)->Nevts; 
   $daqHpSize{$dqRun}  += ($$onfile)->fsize;
#  print "Period of run :", $dirR," % ", $periodRun{$dqRun}, "\n";

 }

### pack Run number and Prod Series for query

my $runSet = $runNum . "%" . $prodSr;

#################################################################################################
&cgiSetup();

&beginHtml();

#initialize for total amount

        if (! defined $dstHpEvts{$runNum}) {$dstHpEvts{$runNum} = 0 };
        if (! defined $daqHpEvts{$runNum}) {$daqHpEvts{$runNum} = 0 };
        if (! defined $dstHpSize{$runNum}) {$dstHpSize{$runNum} = 0 };
        if (! defined $daqHpSize{$runNum}) {$daqHpSize{$runNum} = 0 };
         $dstHpSize{$runNum} = int($dstHpSize{$runNum}/1024/1024);
         $daqHpSize{$runNum} = int($daqHpSize{$runNum}/1024/1024);          
        if (! defined $dtSet{$runNum}) {$dtSet{$runNum} = 'n/a'};
         $numFiles{$runNum} = $nOnlFile;
print <<END;
<TR ALIGN=CENTER HEIGHT=60>
<td HEIGHT=60><a href=\"http://www.star.bnl.gov/devcgi/dbFileDAQRetrv.pl?runD=$runSet\"><h4>$runNum</h4></td>
<td HEIGHT=60><h4>$dtSet{$runNum}</h4></td>
<td HEIGHT=60><h4>$dtTrg{$runNum}</h4></td>
<td HEIGHT=60><h4>$numFiles{$runNum}</h4></td>
<td HEIGHT=60><h4>$daqHpSize{$runNum}</h4></td>
<td HEIGHT=60><h4>$daqHpEvts{$runNum}</h4></td>
<td HEIGHT=60><h4>$dstHpSize{$runNum}</h4></td>
<td HEIGHT=60><h4>$dstHpEvts{$runNum}</h4></td>
</TR>
END

##### finished with database
 &StDbProdDisconnect();

 &endHtml();


##################################
sub beginHtml {

print <<END;

  <html>
  <head>
          <title>Production Summary for Real Data</title>
   </head>
   <body BGCOLOR=\"#ccffff\"> 
<h5><a href=\"http://www.star.bnl.gov/STARAFS/comp/prod/ProdSummary.html\">Production</a><br>
<a href=\"http://www.star.bnl.gov/devcgi/dbProdDAQQuery.pl\">Production Series Query </a><br>
     <h2 align=center>Production Summary for $prodSr <br> and Run Number $runNum</h2>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Run Number </B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Dataset </B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Trigger </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of files </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(MB) of DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(MB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Number of Events<br>in event.root files</B></TD>
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
 













