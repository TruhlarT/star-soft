#!/usr/bin/env perl
#
#  $Id:
#
#  $Log:   CRSjobsStatus.pl - monitoring of CRS jobs
#           
#  L.Didenko
###############################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}
use CGI;
use Mysql;
use Class::Struct;

 require "/afs/rhic.bnl.gov/star/packages/scripts/dbProdSetup.pl";

my ($query) = @_;

$query = new CGI;

my $ldate =  $query->param('dateFst');
my $hdate =  $query->param('dateLst');


my $mynode; 
my @nodeCount;

my @jobsCount = ();
my $njobsCount = 0;

 struct NodeAttr => {
         node    => '$',
         crash   => '$',
         abort   => '$',
         staging => '$',
         donejob => '$',
         nofile  => '$',
         qufail  => '$',
         trfail  => '$',
         msfail  => '$',
         dbfail  => '$',
};

my $TotAbCount = 0;
my $TotDnCount = 0;
my $TotCrCount = 0;
my $TotStCount = 0;
my $TotFNFCount = 0;
my $TotQuFaCount = 0;
my $TotTrFaCount = 0;
my $TotMsFaCount = 0;
my $TotDbFaCount = 0;

my $thisday;
my $year;

my %NodeSum = ();

 ($sec,$min,$hour,$mday,$mon,$yr) = localtime;
   $mon++;
 if( $mon < 10) { $mon = '0'.$mon };
 if( $mday < 10) { $mday = '0'.$mday };
 $year = 1900 + $yr;

 $thisday = $year."-".$mon."-".$mday; 

my @nodes;
my $nnode = 0;

    &StDbProdConnect();

 $sql="SELECT DISTINCT nodeName FROM $crsStatusT ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];

     $mynode = $fvalue  if($fname eq 'nodeName'); 
      }
        $nodes[$nnode] = $mynode;
        $nnode++;
      }

 
 if( $ldate eq $hdate) {
   $thisday =  $hdate ;

 $sql="SELECT  nodeName, crashedJobs, abortedJobs, stagingFailed, doneJobs, fileNotFound, queuingFailed, transferFailed, msgFailed, dbFailed from $crsStatusT where mdate = ?" ;

     $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
      $cursor->execute($thisday);

 }else{
 
 $sql="SELECT  nodeName, crashedJobs, abortedJobs, stagingFailed, doneJobs, fileNotFound, queuingFailed, transferFailed, msgFailed, dbFailed from $crsStatusT where mdate >= ? and mdate <= ? " ;


      $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
      $cursor->execute($ldate,$hdate) ;
} 
       while(@fields = $cursor->fetchrow) {
       my $cols=$cursor->{NUM_OF_FIELDS};
           $fObjAdr = \(NodeAttr->new());
 
      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

        ($$fObjAdr)->node($fvalue)     if( $fname eq 'nodeName');
        ($$fObjAdr)->crash($fvalue)    if( $fname eq 'crashedJobs');
        ($$fObjAdr)->abort($fvalue)    if( $fname eq 'abortedJobs');
        ($$fObjAdr)->staging($fvalue)  if( $fname eq 'stagingFailed');
        ($$fObjAdr)->donejob($fvalue)  if( $fname eq 'doneJobs'); 
        ($$fObjAdr)->nofile($fvalue)   if( $fname eq 'fileNotFound');
        ($$fObjAdr)->qufail($fvalue)   if( $fname eq 'queuingFailed');
        ($$fObjAdr)->trfail($fvalue)   if( $fname eq 'transferFailed');
        ($$fObjAdr)->msfail($fvalue)   if( $fname eq 'msgFailed');
        ($$fObjAdr)->dbfail($fvalue)   if( $fname eq 'dbFailed');       
      }
        
        $jobsCount[$njobsCount] = $fObjAdr;
        $njobsCount++;
}

my @nodeCount = ();
my %NodeSumCr = ();
my %NodeSumAb = ();
my %NodeSumSt = ();
my %NodeSumDn = ();
my %NodeSumFNF = ();
my %NodeSumQuFa = ();
my %NodeSumTrFa = ();
my %NodeSumMsFa = ();
my %NodeSumDbFa = ();

&cgiSetup();

&beginHtml();

  foreach my $eachNode(@jobsCount) {
      $mynode = ($$eachNode)->node;
      $NodeSumCr{$mynode} += ($$eachNode)->crash;
      $NodeSumAb{$mynode} += ($$eachNode)->abort;
      $NodeSumSt{$mynode} += ($$eachNode)->staging; 
      $NodeSumDn{$mynode} += ($$eachNode)->donejob;       
      $NodeSumFNF{$mynode} += ($$eachNode)->nofile;
      $NodeSumQuFa{$mynode} += ($$eachNode)->qufail;
      $NodeSumTrFa{$mynode} += ($$eachNode)->trfail;
      $NodeSumMsFa{$mynode} += ($$eachNode)->msfail;
      $NodeSumDbFa{$mynode} += ($$eachNode)->dbfail;  

 }

  for ($ii = 0; $ii < 9; $ii++)  {
   $nodeCount[$ii] = 0;
 }


  foreach my $dnode (@nodes) {
   
    if( $njobsCount <= 1) {

  $mynode = $dnode;  
&printRow();

  }else{

      $nodeCount[0] = $NodeSumDn{$dnode};
      $nodeCount[1] = $NodeSumCr{$dnode};
      $nodeCount[2] = $NodeSumAb{$dnode};
      $nodeCount[3] = $NodeSumSt{$dnode};        
      $nodeCount[4] = $NodeSumFNF{$dnode};
      $nodeCount[5] = $NodeSumQuFa{$dnode};
      $nodeCount[6] = $NodeSumTrFa{$dnode};
      $nodeCount[7] = $NodeSumMsFa{$dnode};
      $nodeCount[8] = $NodeSumDbFa{$dnode};

     
      $TotDnCount += $nodeCount[0];
      $TotCrCount += $nodeCount[1];
      $TotAbCount += $nodeCount[2];
      $TotStCount += $nodeCount[3];
      $TotFNFCount += $nodeCount[4];
      $TotQuFaCount += $nodeCount[5];
      $TotTrFaCount += $nodeCount[6];
      $TotMsFaCount += $nodeCount[7];
      $TotDbFaCount += $nodeCount[8];

print <<END;
<TR ALIGN=CENTER>
<td>$dnode</td>
END
     for ($ii = 0; $ii < scalar(@nodeCount); $ii++)  {
     if($nodeCount[$ii] == 0) {
print <<END;
<td>$nodeCount[$ii]</td>
END
 }elsif($ii == 0 && $nodeCount[0] != 0 ) {
print <<END;
<td bgcolor=lightgreen>$nodeCount[$ii]</td>
END
 }else{
print <<END;
<td bgcolor=red>$nodeCount[$ii]</td>
END
   }
  }
print <<END;
</TR>
END
  }
  }
 &printTotal();

  &endHtml();

######################

sub beginHtml {

print <<END;
  <html>
   <head>
           <title>CRS Jobs Monitor  </title>
 </head>
    <body BGCOLOR=\"#ccffff\"> 
         <h1 align=center>CRS Jobs Monitor</h1>
 <TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
 <TR>
 <TD ALIGN=CENTER WIDTH= 220 HEIGHT=80><B>Node ID </B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>Done</B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs crashed</B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs aborted</B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs with staging failed</B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with file notfound</B></TD>
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with queuing failed</B></TD> 
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with transfer failed</B></TD> 
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with msg. failed</B></TD> 
 <TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with db failed</B></TD> 
 </TR> 
    </head>
      <body>
END
}

#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER bgcolor=lightblue>
<td>Total</td>
<td>$TotDnCount</td>
<td>$TotCrCount</td>
<td>$TotAbCount</td>
<td>$TotStCount</td>
<td>$TotFNFCount</td>
<td>$TotQuFaCount</td>
<td>$TotTrFaCount</td>
<td>$TotMsFaCount</td>
<td>$TotDbFaCount</td>
</TR>
END

}

###############################

 sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCount[0]</td>
<td>$nodeCount[1]</td>
<td>$nodeCount[2]</td>
<td>$nodeCount[3]</td>
<td>$nodeCount[4]</td>
<td>$nodeCount[5]</td>
<td>$nodeCount[6]</td>
<td>$nodeCount[7]</td>
<td>$nodeCount[8]</td>
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
<!-- Created: Fri Juny 7  05:29:25 MET 2000 -->
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


