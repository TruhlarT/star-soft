#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveTrigID.pl
#
# Retrive offline trigger ID for certain trigger set name from FileCatalog.
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

my @trglable = ();
my @trgid = ();
my $tline = 0;
my $nlist = 0;

my @artrig = ();
my @prt = ();

my $query = new CGI;

my $qtrg = $query->param('trigs');

$artrig[0] = 0;

&beginHtml();

 $fileC->set_context("trgsetupname=$qtrg","filetype=online_daq","sanity=1","storage=hpss","limit=0");

 @artrig = $fileC->run_query("trgname","orda(trgword)");

 $fileC->clear_context( );

     foreach $tline (@artrig){

     @prt = ();
     @prt = split("::",$tline);
     $trglable[$nlist] = @prt[0];
     $trgid[$nlist] = @prt[1];

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$trglable[$nlist]</h3></td>
<td HEIGHT=10><h3>$trgid[$nlist]</h3></td>
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
 <h2 ALIGN=CENTER> <B>Offline trigger ID list for <font color="blue">$qtrg </font> dataset </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Trigger lable</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Offline trigger ID</h3></B></TD>

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
<!-- Created: Fri January 4 15:15:00 MET 2013 -->
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












