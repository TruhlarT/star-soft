#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveStreamDd.pl
#
# Retrive stream data productions on distributed disks from FileCatalog.
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

my @sumevt = ();
my @sumevents = ();
my @sumsize = ();
my @datasize = ();
my @filelst = (); 
my @strname = ();
my $nlist = 0;
my $ssize = 0;
my $dsize = 0;
my @numfiles = ();
my @prt = ();
my @arstream = ();

my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');

&beginHtml();

 $fileC->set_context("trgsetupname=$qtrg","production=$qprod","filetype=daq_reco_MuDst","storage=local","limit=0");

 @arstream = $fileC->run_query("grp(sname2)","sum(size)","sum(events)");

 $fileC->clear_context( );

     foreach my $strline (@arstream){

     @prt = ();
     @prt = split("::",$strline);
     $strname[$nlist] = $prt[0];
     $datasize[$nlist] = $prt[1];
     $dsize = $datasize[$nlist]/1000000000. ;
     $sumsize[$nlist] = sprintf("%.2f", $dsize);
     $sumevents[$nlist] = $prt[2];

     @filelst = ();  

 $fileC->set_context("trgsetupname=$qtrg","production=$qprod","sname2=$strname[$nlist]","filetype=daq_reco_MuDst","storage=local","limit=0");

   @filelst = $fileC->run_query(filename);

   $fileC->clear_context( );

   $numfiles[$nlist] = scalar(@filelst);

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$strname[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumevents[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumsize[$nlist]</h3></td>
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
 <h2 ALIGN=CENTER> <B> <font color="blue">$qprod </font>production summary for <font color="blue">$qtrg </font> <br>stream data on distributed disk</B></h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Stream name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Number of Events</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Size of MuDst (GB) </h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Number of MuDst files </h3></B></TD>
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
<!-- Created: Wed July 10  05:29:25 MET 2013 -->
<!-- hhmts start -->
Last modified: July 26 2013
<!-- hhmts end -->
  </body>
</html>
END

}














