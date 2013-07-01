#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveNodes.pl
#
# Retrive list of nodes and size of  data productions stored on these nodes from FileCatalog.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;


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

my @sumsize = ();
my @datasize = ();
my @nodelst = (); 
my @arnodes = ();
my $strline = 'none';

my $nlist = 0;
my $ssize = 0;
my $dsize = 0;

my @prt = ();


my $query = new CGI;

my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');

$arnodes[0] = 0;

&beginHtml();

 $fileC->set_context("trgsetupname=$qtrg","production=$qprod","filetype=daq_reco_MuDst","storage=local");

 @arnodes = $fileC->run_query('grp(node)','sum(size)');

 $fileC->clear_context( );

     foreach $strline (@arnodes){

     @prt = ();
     @prt = split("::",$strline);
     $nodelst[$nlist] = $prt[0]; 
     $datasize[$nlist] = $prt[1]; 
    
    $sumsize[$nlist] = int($datasize[$nlist]/1000000000);

   if($sumsize[$nlist] < 1 ) {
   $ssize = int($datasize[$nlist]/1000000);
   $sumsize[$nlist] = "0.".$ssize;
  }elsif($sumsize[$nlist] < 10 ) {
   $ssize = int($datasize[$nlist]/1000000) - $dsize*1000;
   $sumsize[$nlist] = $dsize.".".$ssize;

    }else{
   $sumsize[$nlist] = int($datasize[$nlist]/1000000000 + 0.5);
    }


 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$nodelst[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumsize[$nlist]</h3></td>
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
 <h2 ALIGN=CENTER> <B> <font color="blue">$qprod </font>production summary on local disks for <font color="blue">$qtrg </font> data </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Node name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Size (GB) of MuDst </h3></B></TD>
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












