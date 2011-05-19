#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# ProdTrgList.pl
#
# List of trigset set productions from FileCatalog.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;

use DBI;
use Mysql;

my $SITE         = "BNL";
my $status       = (0==1);


my $fileC = new FileCatalog();

    $fileC->connect_as($SITE."::User","FC_user") || die "Connection failed for FC_user\n";

my @coll = ();
my @trig = ();
my @prod = ();
my @sumevt = ();
my @prodset = ();
my @runevents = ();
my @sumsize = ();
my @datasize = ();
my @prt = ();
my $nline = 0;
my $nlist = 0;

my $trg0 = "n/a";

 $fileC->set_context("filetype=daq_reco_MuDst","storage=hpss","limit=0");

 my @prodset = $fileC->run_query("trgsetupname","ordd(production)");

 $fileC->clear_context( );

&beginHtml();

    foreach my $line (@prodset){

	next if($line =~ /$trg0/);
        next if($line =~ /DEV/);

    @prt = (); 
    @prt = split("::",$line); 

    $trig[$nlist] = $prt[0];
    $prod[$nlist] = $prt[1];  


     @runevents = ();
     $runevents[0] = 0;  
     @datasize = ();
     $datasize[0] = 0; 

    $fileC->set_context("trgsetupname=$trig[$nlist]","production=$prod[$nlist]","filetype=daq_reco_MuDst","storage=hpss");
 
   @runevents = $fileC->run_query("sum(events)");
   @datasize = $fileC->run_query("sum(size)");

   $fileC->clear_context( );

   $sumevt[$nlist] = $runevents[0];
   $sumsize[$nlist] = int($datasize[0]/1000000000);

 print <<END;
<TR ALIGN=CENTER HEIGHT=60 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$trig[$nlist]</h3></td>
<td HEIGHT=10><h3>$prod[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nlist]</h3></td>
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
 <h2 ALIGN=CENTER><B>Real Data Production Summary </B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Trigger sets</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Production Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Number of Events<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Size (GB) of MuDst <h3></B></TD>
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












