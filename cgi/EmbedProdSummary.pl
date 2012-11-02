#!/usr/bin/env perl
#
# $Id:
#
# L.Didenko
# EmbedProdSummary.pl - summary of embedding production from FileCatalog
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Mysql;
use Class::Struct;
use Time::Local;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

my $EmbedSumT = "EmbedSummary";

&cgiSetup();


struct JobAttr => {
      trgset    => '$',
      coll      => '$',
      yrdat     => '$',
      prdtag    => '$',
      lbtag     => '$', 
      partc     => '$',
      reqID     => '$',
      sumev     => '$',
      mdsfl     => '$',
      outsz     => '$',
      mnfset    => '$',
      mxfset    => '$',       
      prsite    => '$' 
};


($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $nowdate = ($year+1900).$mon.$mday;


my @jbstat = ();
my $nst = 0;
my @prodtag  = ();
my @trgname  = ();
my @colls    = ();
my @yrdata    = ();
my @librv    = ();
my @sumevt   = ();
my @reqsid   = ();
my @partcl   = ();
my @outsize  = ();
my @totmudst  = ();
my @prdsite  = ();
my @fsetmin  = ();
my @fsetmax  = ();


my $nprod = 0;

  &StDbEmbConnect();

  $sql="SELECT distinct trigName, collision, yearData, requestID, particleID, prodTag, libTag, min(fSet), max(fSet), sum(Nevents), sum(Nmufiles), sum(totsize), site  from $EmbedSumT  group by trigName, prodTag, requestID, particleID order by yearData DESC, trigName ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n"; 
            $cursor->execute();

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->trgset($fvalue)   if( $fname eq 'trigName');
                ($$fObjAdr)->coll($fvalue)     if( $fname eq 'collision');
                ($$fObjAdr)->yrdat($fvalue)    if( $fname eq 'yearData');
                ($$fObjAdr)->prdtag($fvalue)   if( $fname eq 'prodTag');
                ($$fObjAdr)->lbtag($fvalue)    if( $fname eq 'libTag');
                ($$fObjAdr)->reqID($fvalue)    if( $fname eq 'requestID');
                ($$fObjAdr)->partc($fvalue)    if( $fname eq 'particleID');
                ($$fObjAdr)->sumev($fvalue)    if( $fname eq 'sum(Nevents)');
                ($$fObjAdr)->mdsfl($fvalue)    if( $fname eq 'sum(Nmufiles)');
                ($$fObjAdr)->outsz($fvalue)    if( $fname eq 'sum(totsize)');
                ($$fObjAdr)->mnfset($fvalue)   if( $fname eq 'min(fSet)');
                ($$fObjAdr)->mxfset($fvalue)   if( $fname eq 'max(fSet)');
                ($$fObjAdr)->prsite($fvalue)   if( $fname eq 'site');

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }


  &beginHtml();

       foreach  $pjob (@jbstat) {

    $trgname[$nprod]   = ($$pjob)->trgset;
    $colls[$nprod]    = ($$pjob)->coll;
    $yrdata[$nprod]    = ($$pjob)->yrdat;
    $prodtag[$nprod]   = ($$pjob)->prdtag;
    $librv[$nprod]     = ($$pjob)->lbtag;
    $reqsid[$nprod]    = ($$pjob)->reqID;
    $partcl[$nprod]    = ($$pjob)->partc;
    $sumevt[$nprod]    = ($$pjob)->sumev;
    $totmudst[$nprod]  = ($$pjob)->mdsfl;
    $outsize[$nprod]   = ($$pjob)->outsz;
    $fsetmin[$nprod]   = ($$pjob)->mnfset;
    $fsetmax[$nprod]   = ($$pjob)->mxfset;
    $prdsite[$nprod]   = ($$pjob)->prsite;

  $outsize[$nprod] = int($outsize[$nprod]/1000000000 + 0.5); 


###########

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$trgname[$nprod]</h3></td>
<td HEIGHT=10><h3>$colls[$nprod]</h3></td>
<td HEIGHT=10><h3>$yrdata[$nprod]</h3></td>
<td HEIGHT=10><h3>$reqsid[$nprod]</h3></td>
<td HEIGHT=10><h3>$partcl[$nprod]</h3></td>
<td HEIGHT=10><h3>$prodtag[$nprod]</h3></td>
<td HEIGHT=10><h3>$librv[$nprod]</h3></td>
<td HEIGHT=10><h3>$fsetmin[$nprod]</h3></td>
<td HEIGHT=10><h3>$fsetmax[$nprod]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nprod]</h3></td>
<td HEIGHT=10><h3>$totmudst[$nprod]</h3></td>
<td HEIGHT=10><h3>$outsize[$nprod]</h3></td>
<td HEIGHT=10><h3>$prdsite[$nprod]</h3></td>
</TR>
END

    $nprod++;
 }

 &StDbEmbDisconnect();

 &endHtml();


#==============================================================================

######################
sub StDbEmbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbEmbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub beginHtml {

print <<END;

  <html>

    <head>
          <title>Summary of embedding productions jobs status</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of embedding  production</h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger set<br>name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Collision</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Year of <br>data taken</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>RequestID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Embedded Particle</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>ProdTag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Library<br>revision</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>fSet min</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>fSet max</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.events processed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.of MuDst files </h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Size of output files in GB</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Site<h3></B></TD>
</TR>
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
<!-- Created: Fri November 2 2012 -->
<!-- hhmts start -->
Last modified: 2012-11-02
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
