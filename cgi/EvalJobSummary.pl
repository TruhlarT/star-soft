#!/usr/bin/env perl
#
# $Id:
#
# L.Didenko
# EvalJobSummary.pl - summary of production jobs status for new tracking evaluation
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Class::Struct;

&cgiSetup();

#$dbhost="fc2.star.bnl.gov:3386";


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      trgset    => '$',
      prdtag    => '$',
      evltg     => '$',
      strtm     => '$',
      fintm     => '$',
      prst      => '$',   
      nevt      => '$'
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

 $JobStatusT = "EvalJobStatus";

my @jbstat = ();
my $nst = 0;
my @prodtag = ();
my @artrg = ();
my @strtime = ();
my @fntime = ();
my @sumevt = ();
my @jbdone = ();
my @jbcreat = ();
my @jbcrsh = ();
my @jbhung = ();
my @jbhpss = ();
my @jbresub  = ();
my @szmudst = ();
my @mismudst = ();
my @trcktag = ();
my @prstat = ();
my @avgcpu = ();
my @avgtrk = ();

my $daydif = 0;
my $mxtime = 0;
my $mondif = 0;

my $nprod = 0;

  &StDbProdConnect();

  $sql="SELECT distinct trigsetName, prodSeries, evaltag, status, date_format(min(createTime), '%Y-%m-%d') as mintm, date_format(max(createTime), '%Y-%m-%d') as maxtm from $JobStatusT where createTime <> '0000-00-00 00:00:00' group by trigsetName, prodSeries, evaltag order by max(createTime) ";


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

                ($$fObjAdr)->trgset($fvalue)   if( $fname eq 'trigsetName');
                ($$fObjAdr)->prdtag($fvalue)   if( $fname eq 'prodSeries');
                ($$fObjAdr)->evltg($fvalue)    if( $fname eq 'evaltag');
                ($$fObjAdr)->prst($fvalue)     if( $fname eq 'status');
                ($$fObjAdr)->strtm($fvalue)    if( $fname eq 'mintm');
                ($$fObjAdr)->fintm($fvalue)    if( $fname eq 'maxtm');

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }


  &beginHtml();

 my @prt = ();

       foreach  $pjob (@jbstat) {

    $prodtag[$nprod]  = ($$pjob)->prdtag;
    $artrg[$nprod]   = ($$pjob)->trgset;
    $trcktag[$nprod] = ($$pjob)->evltg;    
    $prstat[$nprod]  = ($$pjob)->prst;
    $strtime[$nprod] =  ($$pjob)->strtm;
    $fntime[$nprod]  =  ($$pjob)->fintm;
    @prt = ();
    $mxtime = $fntime[$nprod];
    @prt = split("-",$mxtime);
    $mxtime =~ s/-//g;
    $daydif = $nowdate - $mxtime;
    $mondif = $mon - $prt[1];

   if($mondif == 1  and ($daydiff == 70 or $daydiff == 71 ) ) {
    $daydif = $nowdate - $mxtime - $daydiff;
    };

    $jbcreat[$nprod] = 0;
    $jbdone[$nprod] = 0;
    $jbcrsh[$nprod] = 0;
    $jbhung[$nprod] = 0;
    $jbhpss[$nprod] = 0;
    $jbresub[$nprod] = 0;
    $szmudst[$nprod] = 0;
    $mismudst[$nprod] = 0;    
    $sumevt[$nprod] = 0;
    $avgcpu[$nprod] = 0;
    $avgtrk[$nprod] = 0;   


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcreat[$nprod] = $mpr;
       }
    $cursor->finish();
    
  
############

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus = 'Done' and evaltag = '$trcktag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbdone[$nprod] = $mpr;
       }
    $cursor->finish();


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus <> 'Done' and jobStatus <> 'n/a' and jobStatus <> 'hung' and evaltag = '$trcktag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcrsh[$nprod] = $mpr;
       }
    $cursor->finish();


##########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus = 'hung' and  evaltag = '$trcktag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhung[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]'  and prodSeries = '$prodtag[$nprod]' and inputHpssStatus like 'hpss_error%'  and  evaltag = '$trcktag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhpss[$nprod] = $mpr;
       }
    $cursor->finish();


########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]'  and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' and submitAttempt >=2  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbresub[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

  $sql="SELECT sum(mudstsize)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' and outputStatus = 'yes'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $szmudst[$nprod] = $mpr;
       }
    $cursor->finish();

    $szmudst[$nprod] = int($szmudst[$nprod]/1000000000 + 0.5); 

########## 


  $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName = '$artrg[$nprod]'  and prodSeries = '$prodtag[$nprod]' and  evaltag = '$trcktag[$nprod]' and jobStatus <> 'n/a' and jobStatus <> 'hung' and inputHpssStatus = 'OK' and outputStatus = 'n/a' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $mismudst[$nprod] = $mpr;
       }
    $cursor->finish();

##########

  $sql="SELECT sum(NoEvents)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' and jobStatus <> 'n/a' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $sumevt[$nprod] = $mpr;
       }
    $cursor->finish();


########## 

  $sql="SELECT avg(CPU_per_evt_sec) FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' and jobStatus <> 'n/a' and  CPU_per_evt_sec > 0.0001 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $avgcpu[$nprod] = $mpr;
          $avgcpu[$nprod] = sprintf("%.2f",$avgcpu[$nprod]);
       }
    $cursor->finish();


########## 

  $sql="SELECT avg(avg_no_tracks) FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and evaltag = '$trcktag[$nprod]' and jobStatus <> 'n/a' and avg_no_tracks >= 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $avgtrk[$nprod] = $mpr;
         if($avgtrk[$nprod] <= 1.0 ) {
         $avgtrk[$nprod] = sprintf("%.2f",$avgtrk[$nprod]);
        }elsif($avgtrk[$nprod] <= 10.0 ) {
          $avgtrk[$nprod] = sprintf("%.1f",$avgtrk[$nprod]);
        }else{
          $avgtrk[$nprod] = int($avgtrk[$nprod] + 0.5);
        }
       }
    $cursor->finish();


########## 


if($prstat[$nprod] eq "removed" ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3><font color="green">$artrg[$nprod]<br><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=ndisk">location</font></h3></td>
<td HEIGHT=10><h3><font color="green">$prodtag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$trcktag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=qchain">chain</font></h3></td>
<td HEIGHT=10><h3><font color="green">$jbcreat[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$jbdone[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=jstat">$jbcrsh[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hung">$jbhung[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hpss">$jbhpss[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$jbresub[$nprod]</h3></td>
<td HEIGHT=10><h3><font color="green"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=mudst">$mismudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$szmudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$sumevt[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$avgcpu[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$avgtrk[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$strtime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$fntime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="green">$prstat[$nprod]</font></h3></td>
</TR>
END

 }elsif($prstat[$nprod] ne "removed" and $daydif < 2){

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3><font color="red">$artrg[$nprod]<br><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=ndisk">location</font></h3></td>
<td HEIGHT=10><h3><font color="red">$prodtag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$trcktag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=qchain">chain</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbcreat[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbdone[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=jstat">$jbcrsh[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hung">$jbhung[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hpss">$jbhpss[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbresub[$nprod]</h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=mudst">$mismudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$szmudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$sumevt[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$avgcpu[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$avgtrk[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$strtime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$fntime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$prstat[$nprod]</font></h3></td>
</TR>
END

  }else{

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$artrg[$nprod]<br><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=ndisk">location</font></h3></td>
<td HEIGHT=10><h3>$prodtag[$nprod]</h3></td>
<td HEIGHT=10><h3>$trcktag[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=qchain">chain</h3></td>
<td HEIGHT=10><h3>$jbcreat[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbdone[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=jstat">$jbcrsh[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hung">$jbhung[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=hpss">$jbhpss[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbresub[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveEvalJob.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];caltag=$trcktag[$nprod];pflag=mudst">$mismudst[$nprod]</h3></td>
<td HEIGHT=10><h3>$szmudst[$nprod]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nprod]</h3></td>
<td HEIGHT=10><h3>$avgcpu[$nprod]</h3></td>
<td HEIGHT=10><h3>$avgtrk[$nprod]</h3></td>
<td HEIGHT=10><h3>$strtime[$nprod]</h3></td>
<td HEIGHT=10><h3>$fntime[$nprod]</h3></td>
<td HEIGHT=10><h3>$prstat[$nprod]</h3></td>
</TR>
END

 }
      $nprod++;

}

    &StDbProdDisconnect();

 &endHtml();


#==============================================================================

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub beginHtml {

print <<END;

  <html>

    <head>
          <title>Summary of production jobs status for new tracking</title>
    </head>

   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of production jobs status for new tracking evaluation</h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<h4 ALIGN=LEFT><font color="#ff0000">Ongoing production is in red color</font><br>
<ALIGN=LEFT><font color="green">Removed production is in green color</font><br>
<ALIGN=LEFT>Link under trigger set name has list of disk names for production location</h4>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger set</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod.<br>tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Tracker code name<br></h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Chain options</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs created</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs done</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs crashed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs 'hung'</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs failed due to HPSS error</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs resubmit</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.<br>missing MuDst files</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Size of output files in GB</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.<br>events<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Avg<br>CPU/evt<br>in sec<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Avg No.<br>tracks<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Start time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>End time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Status<h3></B></TD>
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
<!-- Created: Thu June 30 2011 -->
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
