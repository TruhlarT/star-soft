#! /opt/star/bin/perl -w
#
#  $Id:
#
#  dbQueryDS.pl  script to get browser of MC dataset and create WEB page 
#  L. Didneko
#
###############################################################################

use CGI;

require "/afs/rhic/star/packages/DEV00/mgr/dbCpProdSetup.pl";

my @prodPer = ("mdc1", "mdc2", "postmdc2", "prod4", "prod5", "mdc3");
my $debugOn = 0;
my %pair;
my @Sets;
my $nSets = 0;
my $prod;
my $dtSet;
my $mySet;
my $prodSeq = " ";
my $prodNext;

&cgiSetup();

&StDbProdConnect();

&beginHtml();


$sql="SELECT DISTINCT dataset FROM $cpFileCatalogT where jobID <> 'n/a' ";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

my $counter = 0;
while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;
    next if ($fvalue =~ /daq/);
    next if ($fvalue =~ /dst/);

     $mySet = $fvalue  if($fname eq 'dataset'); 
 }
      $Sets[$nSets] = $mySet;
      $nSets++;

     $pair{$mySet} = " ";    

  }


for ($ll=0;$ll<scalar(@prodPer);$ll++) {

 $prod = "_" . $prodPer[$ll] . "_";
 $prodSeq = " ";
$sql="SELECT DISTINCT dataset FROM $cpFileCatalogT where jobID like '%$prod%' ";
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
$cursor->execute;

my $counter = 0;
while(@fields = $cursor->fetchrow) {
  my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;

     $mySet = $fvalue  if($fname eq 'dataset'); 
  }
    next if ($fvalue =~ /daq/);
    next if ($fvalue =~ /dst/);

     $prodNext = $prodPer[$ll];
     $pair{$mySet} =  $pair{$mySet} . " : " . $prodNext ;

  } 

 }

for ($ll=0;$ll<scalar(@Sets);$ll++) { 

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
<td>$mySet</td>
<td>$pair{$mySet}</td>
</tr>
END

}

###############
sub endHtml {
my $Date = `date`;

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
