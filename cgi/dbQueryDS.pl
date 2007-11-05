#! /usr/local/bin/perl -w
#
#  $Id:
#
#  dbQueryDS.pl  script to get browser of MC dataset and create WEB page 
#  L. Didneko
#
###############################################################################

use CGI;

require "/afs/rhic.bnl.gov/star/packages/scripts/dbCpProdSetup.pl";

my @prodPer = ();
my $debugOn = 0;
my %pair;
my @Sets = ();
my $nSets = 0;
my $dtSet;
my $mySet;
my $prodSeq = " ";
my $prodNext;
my $nprodPer = 0;
my $myprod;
my $mSet;

&cgiSetup();

&StDbProdConnect();

&beginHtml();

$sql="SELECT DISTINCT prodSeries FROM $JobStatusT ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

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
        $prodPer[$nprodPer] = "prod4";

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID <> 'n/a' AND type = 'MC_reco' ";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;

     $mySet = $fvalue  if($fname eq 'dataset'); 
 }
    next if ($mySet eq 'n/a');

      $Sets[$nSets] = $mySet;
      $nSets++;

     $pair{$mySet} = " ";    

  }


for ($ll=0; $ll < scalar(@prodPer); $ll++) {

my $prod = $prodPer[$ll];

$sql="SELECT DISTINCT dataset FROM $FileCatalogT where jobID like '%$prod%' AND dataset <> 'n/a' AND type = 'MC_reco' ";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;

     $mSet = $fvalue  if($fname eq 'dataset'); 
  }
     $prodNext = $prodPer[$ll];
     $pair{$mSet} =  $pair{$mSet} . " : " . $prodNext ;
#     $pair{$mSet} = $prodPer[$ll]; 
  } 

 }

for ($ll=0; $ll<scalar(@Sets); $ll++) { 

     $mySet = $Sets[$ll];
     if ($mySet =~ /Bjet/) {
     $pair{$mySet} = ": prod5" ;
   }
     &printRow();    
  } 

 &endHtml();

&StDbProdDisconnect();

#################
sub beginHtml {

print <<END;
 <html>
  <head>
          <title>List of Datasets available in FileCatalog</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
     <h1 align=center>List of Monte Carlo Datasets Available in FileCatalog </h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"60%\" HEIGHT=50><B>Dataset</B></TD>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=50><B>Production Series</B></TD>
</TR> 
   </head>
    <body>
END
}

###############
sub printRow {

print <<END;
<TR ALIGN=LEFT VALIGN=CENTER>
<td><a href=\"http://www.star.bnl.gov/devcgi/dbMCProdSum.pl?SetMC=$mySet\">$mySet</td>
<td>$pair{$mySet}</td>
</TR>
END

}

###############
sub endHtml {
my $Date = '/bin/date';

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Wed May 41  05:29:25 MET 2000 -->
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
