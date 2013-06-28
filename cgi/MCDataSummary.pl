#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# MCDataSummary.pl
#
# List of MC datasets and production summary from FileCatalog.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;

use DBI;

&cgiSetup();

($sec,$min,$hour,$mday,$mon,$year) = localtime();

my $mon =  $mon + 1;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $SITE         = "BNL";
my $status       = (0==1);


my $fileC = new FileCatalog();

    $fileC->connect_as($SITE."::User","FC_user") || die "Connection failed for FC_user\n";

my @coll = ();
my @mcset = ();
my @recopath = ();
my @prod = ();
my @runs = ();
my @sumevt = ();
my @prodset = ();
my @runevents = ();
my @sumsize = ();
my @datasize = ();
my @filelst = ();
my @yrgeom = ();
my @mcsize = ();
my @totsize = ();
my @prt = ();
my $nline = 0;
my $nlist = 0;
my $ssize = 0;
my $dsize  = 0;
my @numfiles = ();

my $prodname = "n/a";

 $fileC->set_context("filetype=MC_reco_MuDst","storage=hpss","limit=0");

 @prodset = $fileC->run_query("path","collision","ordd(geometry)","runnumber","production");

 $fileC->clear_context( );

&beginHtml();

    foreach my $line (@prodset){

    @prt = (); 
    @prt = split("::",$line); 

    $recopath[$nlist] = $prt[0];
    $coll[$nlist]   = $prt[1];
    $yrgeom[$nlist] = $prt[2];
    $runs[$nlist]   = $prt[3]; 
    $prod[$nlist]   = $prt[4]; 

    if ($coll[$nlist] eq "auau19.564" ) {
	$coll[$nlist] = "auau19.6";
    }


    @prt = (); 
    @prt = split("/",$recopath[$nlist]);
    $mcset[$nlist] = $prt[4]."/".$prt[5]."/". $prt[6]."/". $prt[7]."/".$prt[8]."/". $prt[9]; 

     @runevents = ();
     $runevents[0] = 0;  
     @datasize = ();
     $datasize[0] = 0; 
     @filelst = ();


    $fileC->set_context("path=$recopath[$nlist]","production=$prod[$nlist]","filetype=MC_reco_MuDst","storage=hpss","sanity=1","limit=0");
 
   @runevents = $fileC->run_query("sum(events)");
   @datasize = $fileC->run_query("sum(size)");
   @filelst = $fileC->run_query(filename);

   $fileC->clear_context( );

   $sumevt[$nlist] = $runevents[0];
   $sumsize[$nlist] = int($datasize[0]/1000000000);
   $dsize = $sumsize[$nlist];

   if($sumsize[$nlist] < 1 ) {
   $ssize = int($datasize[0]/1000000);
   $sumsize[$nlist] = "0.".$ssize;
   }elsif($sumsize[$nlist] < 10 ) {
   $ssize = int($datasize[0]/10000000) - $dsize*100;
   $sumsize[$nlist] = $dsize.".".$ssize; 

    }else{
   $sumsize[$nlist] = int($datasize[0]/1000000000 + 0.5);
    } 

   $numfiles[$nlist] = scalar(@filelst);

 $prodname = $mcset[$nlist].".".$prod[$nlist].".html";

    @mcsize = (); 
    $mcsize = 0;

    $fileC->set_context("path=$recopath[$nlist]","production=$prod[$nlist]","storage=hpss","sanity=1","limit=0");

    @mcsize = $fileC->run_query("sum(size)");

   $fileC->clear_context( );

   $totsize[$nlist] = int($mcsize[0]/1000000000);
   $dsize = $totsize[$nlist];

   if($totsize[$nlist] < 1 ) {
   $ssize = int($mcsize[0]/1000000);
   $totsize[$nlist] = "0.".$ssize;
   }elsif($totsize[$nlist] < 10 ) {
   $ssize = int($mcsize[0]/10000000) - $dsize*100;
   $totsize[$nlist] = $dsize.".".$ssize; 

    }else{
   $totsize[$nlist] = int($mcsize[0]/1000000000 + 0.5);
    } 
   
     if($prod[$nlist] eq "eval" ) {
       $prod[$nlist] = $prt[10];
    }

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$mcset[$nlist]</h3></td>
<td HEIGHT=10><h3>$coll[$nlist]</h3></td>
<td HEIGHT=10><h3>$yrgeom[$nlist]</h3></td>
<td HEIGHT=10><h3>$runs[$nlist]</h3></td>
<td HEIGHT=10><h3>$prod[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumsize[$nlist]</h3></td>
<td HEIGHT=10><h3>$totsize[$nlist]</h3></td>
<td HEIGHT=10><h3>$numfiles[$nlist]</h3></td>
</TR>
END
      $nlist++;

    }
 
   $fileC->destroy();

 &endHtml();


######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B> MC Data Production Summary  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<h4 ALIGN=LEFT><font color="blue">Production descriptions can be found on  <a href="http://www.star.bnl.gov/public/comp/prod/MCProdList.html"> the page</a></font></h4>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Dataset name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Collision</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Geometry</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Run number</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Production Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number<br> of Events<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Size of <br> MuDst <br>(GB) <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Total<br> Size <br>(GB) <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number<br> of MuDst<br> files <h3></B></TD>
</TR> 
   </head>
    </body>
END
}

#####################
sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: 23 February 12  17:00:00 MET 2012 -->
<!-- hhmts start -->
Last update: 2012-11-05
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












