#!/usr/bin/env perl
#
# $Id:
#
# L.Didenko
# MCJobsSummary.pl - summary of MC  production jobs status
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Class::Struct;

&cgiSetup();

$dbhost="duvall.star.bnl.gov:3306";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

struct JobAttr => {
      trgset    => '$',
      reqID     => '$', 
      prdtag    => '$',
      lbtag     => '$',        
      strtm     => '$',
      fintm     => '$',
      outsz     => '$',
      evtcpu    => '$',   
      nevt      => '$',
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

my $JobStatusT = "jobs_embed_2013";
my $RequestSumT = "request_embed_2013";

my @jbstat = ();
my $nst = 0;
my @prodtag  = ();
my @trgname  = ();
my @librv    = ();
my @strtime  = ();
my @fntime   = ();
my @sumevt   = ();
my @reqsid   = ();
my @outsize  = ();
my @avcpu    = ();
my @prdsite  = ();

my @jbdone = ();
my @jbcreat = ();
my @jbcrsh = ();
my @mismudst = ();
my @chainm = ();

my $daydif = 0;
my $mxtime = 0;
my $mondif = 0;

my $nprod = 0;

  &StDbEmbConnect();


$sql="SELECT distinct triggerSetName, prodTag, libTag, requestID, date_format(min(startTime), '%Y-%m-%d') as mintm, date_format(max(endTime), '%Y-%m-%d') as maxtm, sum(totalEvents), avg(CPUperEvt), sum(outputSize), site from $JobStatusT where triggerSetName <> 'NULL' and particle is NULL and jobStatus = 'Done' and  status = 1 and startTime <> '0000-00-00 00:00:00' and CPUperEvt > 0.00001 group by triggerSetName, prodTag, requestID order by max(startTime) ";


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

                ($$fObjAdr)->trgset($fvalue)   if( $fname eq 'triggerSetName');
                ($$fObjAdr)->prdtag($fvalue)   if( $fname eq 'prodTag');
                ($$fObjAdr)->lbtag($fvalue)    if( $fname eq 'libTag');
                ($$fObjAdr)->reqID($fvalue)    if( $fname eq 'requestID');
                ($$fObjAdr)->strtm($fvalue)    if( $fname eq 'mintm');
                ($$fObjAdr)->fintm($fvalue)    if( $fname eq 'maxtm');
                ($$fObjAdr)->nevt($fvalue)     if( $fname eq 'sum(totalEvents)');
                ($$fObjAdr)->evtcpu($fvalue)   if( $fname eq 'avg(CPUperEvt)');
                ($$fObjAdr)->outsz($fvalue)    if( $fname eq 'sum(outputSize)');
                ($$fObjAdr)->prsite($fvalue)   if( $fname eq 'site');

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }


  &beginHtml();

 my @prt = ();

       foreach  $pjob (@jbstat) {

    $prodtag[$nprod]   = ($$pjob)->prdtag;
    $trgname[$nprod]   = ($$pjob)->trgset;
    $librv[$nprod]     = ($$pjob)->lbtag;
    $reqsid[$nprod]    = ($$pjob)->reqID;
    $sumevt[$nprod]    = ($$pjob)->nevt;
    $avcpu[$nprod]     = ($$pjob)->evtcpu;
    $outsize[$nprod]   = ($$pjob)->outsz;
    $strtime[$nprod]   = ($$pjob)->strtm;
    $fntime[$nprod]    = ($$pjob)->fintm;
    $prdsite[$nprod]   = ($$pjob)->prsite;

  $outsize[$nprod] = int($outsize[$nprod]/1000 + 0.5); 

    @prt = ();
    $mxtime = $fntime[$nprod];
    @prt = split("-",$mxtime);
    $mxtime =~ s/-//g;
    $daydif = $nowdate - $mxtime;
    $mondif = $mon - $prt[1];

   if($mondif == 1  and ($daydiff == 70 or $daydiff == 71 ) ) {
    $daydif = $nowdate - $mxtime - $daydiff;
    };

    $avcpu[$nprod]   = sprintf("%.2f",$avcpu[$nprod]);  
    $jbcreat[$nprod]  = 0;
    $jbdone[$nprod]   = 0;
    $jbcrsh[$nprod]   = 0;
    $jbremain[$nprod] = 0;
    $mismudst[$nprod] = 0;    

###########

   $sql="SELECT count(inputFile)  FROM $JobStatusT where triggerSetName = '$trgname[$nprod]' and  requestID = '$reqsid[$nprod]' and prodTag = '$prodtag[$nprod]' and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcreat[$nprod] = $mpr;
       }
    $cursor->finish();
    
  
############

   $sql="SELECT count(inputFile)  FROM $JobStatusT where triggerSetName = '$trgname[$nprod]' and prodTag = '$prodtag[$nprod]' and requestID = '$reqsid[$nprod]' and jobStatus = 'Done' and recoStatus = 'Done'  and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbdone[$nprod] = $mpr;
       }
    $cursor->finish();


###########

   $sql="SELECT count(inputFile)  FROM $JobStatusT where triggerSetName = '$trgname[$nprod]' and prodTag = '$prodtag[$nprod]' and requestID = '$reqsid[$nprod]' and jobStatus = 'Done' and recoStatus <> 'Done'  and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcrsh[$nprod] = $mpr;
       }
    $cursor->finish();


##########

  $sql="SELECT count(inputFile)  FROM $JobStatusT where triggerSetName = '$trgname[$nprod]' and prodTag = '$prodtag[$nprod]' and requestID = '$reqsid[$nprod]' and jobStatus <> 'Done'  and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbremain[$nprod] = $mpr;
       }
    $cursor->finish();


########## 


  $sql="SELECT count(inputFile)  FROM $JobStatusT where  triggerSetName = '$trgname[$nprod]' and prodTag = '$prodtag[$nprod]'  and requestID = '$reqsid[$nprod]' and jobStatus = 'Done' and  outputNFS <> 'Done'  and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $mismudst[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

 if( $daydif <= 2){

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3><font color="red">$trgname[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$reqsid[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$prodtag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$librv[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];pflag=chnopt">chain</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbcreat[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbdone[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=jstat">$jbcrsh[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbremain[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=mudst">$mismudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=sdisk">location</font></h3></td>
<td HEIGHT=10><h3><font color="red">$outsize[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$sumevt[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$avcpu[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$strtime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$fntime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$prdsite[$nprod]</font></h3></td>
</TR>
END

  }else{

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$trgname[$nprod]</h3></td>
<td HEIGHT=10><h3>$reqsid[$nprod]</h3></td>
<td HEIGHT=10><h3>$prodtag[$nprod]</h3></td>
<td HEIGHT=10><h3>$librv[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];pflag=chnopt">chain</h3></td>
<td HEIGHT=10><h3>$jbcreat[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbdone[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=jstat">$jbcrsh[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbremain[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=mudst">$mismudst[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveMCJob.pl?rreq=$reqsid[$nprod];rtrig=$trgname[$nprod];rprod=$prodtag[$nprod];pflag=sdisk">location</h3></td>
<td HEIGHT=10><h3>$outsize[$nprod]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nprod]</h3></td>
<td HEIGHT=10><h3>$avcpu[$nprod]</h3></td>
<td HEIGHT=10><h3>$strtime[$nprod]</h3></td>
<td HEIGHT=10><h3>$fntime[$nprod]</h3></td>
<td HEIGHT=10><h3>$prdsite[$nprod]</h3></td>
</TR>
END

 }
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
          <title>Summary of MC production jobs status</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of MC  production jobs status</h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<h4 ALIGN=LEFT><font color="#ff0000">Ongoing production is in red color</font><br></h4>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3> MC dataset name </h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>RequestID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>ProdTag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Library<br>version</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>Chain <br> options</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Total <br>No.jobs</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>No.jobs<br> done</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>No.jobs<br> crashed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>No.jobs<br> remaining</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>No.mis. files on NFS</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>Location<br> on NFS</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>Total size of output files in GB</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.<br>events <br>processed<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>Avg.<br>CPU/evt<br> in sec<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Start time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>End time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"2%\" HEIGHT=60><B><h3>Site<h3></B></TD>
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
<!-- Created: Thu September 6 2012 -->
<!-- hhmts start -->
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
