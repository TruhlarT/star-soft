#!/usr/bin/env perl
#
# $Id:
#
# L.Didenko
# jobSummary2010.pl - summary of production jobs status for year 2010
#
########################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
#use Mysql;
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
      strtm     => '$',
      fintm     => '$',
      evtcpu    => '$',
      avtrk     => '$',
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

 $JobStatusT = "JobStatus2010";

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
my @jbmudst = ();
my @mismudst = ();
my @avcpu  = ();
my @avgtrk  = ();

my $daydif = 0;
my $mxtime = 0;
my $mondif = 0;

my $nprod = 0;

  &StDbProdConnect();

  $sql="SELECT distinct trigsetName, prodSeries, date_format(min(createTime), '%Y-%m-%d') as mintm, date_format(max(createTime), '%Y-%m-%d') as maxtm, sum(NoEvents), avg(CPU_per_evt_sec), avg(avg_no_tracks) from $JobStatusT where createTime <> '0000-00-00 00:00:00' and prodSeries not like '%test%' and CPU_per_evt_sec > 0.0001  group by trigsetName, prodSeries order by max(createTime) ";


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
                ($$fObjAdr)->nevt($fvalue)     if( $fname eq 'sum(NoEvents)');
                ($$fObjAdr)->evtcpu($fvalue)   if( $fname eq 'avg(CPU_per_evt_sec)');
                ($$fObjAdr)->avtrk($fvalue)    if( $fname eq 'avg(avg_no_tracks)');
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
    $artrg[$nprod]    = ($$pjob)->trgset;
    $sumevt[$nprod]   = ($$pjob)->nevt;
    $avcpu[$nprod]    = ($$pjob)->evtcpu;
    $avgtrk[$nprod]   = ($$pjob)->avtrk;
    $strtime[$nprod]  = ($$pjob)->strtm;
    $fntime[$nprod]   = ($$pjob)->fintm;
    $avcpu[$nprod]    = sprintf("%.2f",$avcpu[$nprod]);
    if($avgtrk[$nprod] <= 1.0 ) {
    $avgtrk[$nprod] = sprintf("%.2f",$avgtrk[$nprod]);
    }elsif($avgtrk[$nprod] <= 10.0 ) {
    $avgtrk[$nprod] = sprintf("%.1f",$avgtrk[$nprod]);
    }else{
    $avgtrk[$nprod] = int($avgtrk[$nprod] + 0.5);
    }
    @prt = ();
    $mxtime = $fntime[$nprod];
    @prt = split("-",$mxtime);
    $mxtime =~ s/-//g;
    $daydif = $nowdate - $mxtime;
    $mondif = $mon - $prt[1];
    
    if($mondif == 1 and ($daydiff == 70 or $daydiff == 71 )) {
    $daydif = $nowdate - $mxtime - $daydiff;
    };
    
    $jbcreat[$nprod] = 0;
    $jbdone[$nprod] = 0;
    $jbcrsh[$nprod] = 0;
    $jbhung[$nprod] = 0;
    $jbhpss[$nprod] = 0;
    $jbresub[$nprod] = 0;
    $jbmudst[$nprod] = 0;
    $mismudst[$nprod] = 0;    


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcreat[$nprod] = $mpr;
       }
    $cursor->finish();
    
  
############

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and prodSeries = '$prodtag[$nprod]' and trigsetName  = '$artrg[$nprod]' and jobStatus = 'Done' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbdone[$nprod] = $mpr;
       }
    $cursor->finish();


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName  = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus <> 'Done' and jobStatus <> 'n/a' and jobStatus <> 'hung'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcrsh[$nprod] = $mpr;
       }
    $cursor->finish();


##########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName  = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus = 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhung[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName  = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and inputHpssStatus like 'hpss_error%'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhpss[$nprod] = $mpr;
       }
    $cursor->finish();


########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName  = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and submitAttempt >=2  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbresub[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

  $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and trigsetName   = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and outputHpssStatus = 'yes'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbmudst[$nprod] = $mpr;
       }
    $cursor->finish();

########## 


  $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and trigsetName  = '$artrg[$nprod]' and prodSeries = '$prodtag[$nprod]' and jobStatus <> 'n/a' and jobStatus <> 'hung' and inputHpssStatus = 'OK' and outputHpssStatus = 'n/a' ";

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
<td HEIGHT=10><h3><font color="red">$artrg[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$prodtag[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbcreat[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbdone[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=jstat">$jbcrsh[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=hung">$jbhung[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=hpss">$jbhpss[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbresub[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=mudst">$mismudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$jbmudst[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$sumevt[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=strcpu">$avcpu[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red"><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=sttrack">$avgtrk[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$strtime[$nprod]</font></h3></td>
<td HEIGHT=10><h3><font color="red">$fntime[$nprod]</font></h3></td>
</TR>
END

   }else{

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$artrg[$nprod]</h3></td>
<td HEIGHT=10><h3>$prodtag[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbcreat[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbdone[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=jstat">$jbcrsh[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=hung">$jbhung[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=hpss">$jbhpss[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbresub[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=mudst">$mismudst[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbmudst[$nprod]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=strcpu">$avcpu[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2010;pflag=sttrack">$avgtrk[$nprod]</h3></td>
<td HEIGHT=10><h3>$strtime[$nprod]</h3></td>
<td HEIGHT=10><h3>$fntime[$nprod]</h3></td>
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
          <title>Summary of production jobs for run 2010</title> 
    </head>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of production jobs status for<font color="blue"> run 2010 </font>data  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<h4 ALIGN=LEFT><font color="#ff0000">Ongoing production is in red color</font></h4>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<br>
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Trigger set</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Prod.<br>tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs created</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs done</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs crashed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs 'hung'</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs failed due to HPSS error</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs resubmit</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.<br>MuDst files missing on HPSS</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.<br>MuDst files on HPSS</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.events produced<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Avg.<br>CPU/evt<br> in sec<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Avg.No.<br>tracks<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Start time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>End time <h3></B></TD>
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
