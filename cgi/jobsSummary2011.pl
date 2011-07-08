#!/usr/local/bin/perl
#!/usr/bin/env perl
#
# $Id:
#
# L.Didenko
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use Mysql;
use Class::Struct;

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
      nevt      => '$'
};


($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday;

my $nowdate = $todate;

 $JobStatusT = "JobStatus2011";

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

my $nprod = 0;

  &StDbProdConnect();

  $sql="SELECT distinct trigsetName, prodSeries, date_format(min(createTime), '%Y-%m-%d') as mintm, date_format(max(createTime), '%Y-%m-%d') as maxtm, sum(NoEvents) from $JobStatusT where createTime <> '0000-00-00 00:00:00' and prodSeries not like '%test%' group by trigsetName, prodSeries order by max(createTime) ";


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
                ($$fObjAdr)->strtm($fvalue)    if( $fname eq 'mintm');
                ($$fObjAdr)->fintm($fvalue)    if( $fname eq 'maxtm');

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }


  &beginHtml();

       foreach  $pjob (@jbstat) {

    $prodtag[$nprod]  = ($$pjob)->prdtag;
    $artrg[$nprod]   = ($$pjob)->trgset;
    $sumevt[$nprod]  = ($$pjob)->nevt;
    $strtime[$nprod] =  ($$pjob)->strtm;
    $fntime[$nprod]  =  ($$pjob)->fintm;
    
    $jbcreat[$nprod] = 0;
    $jbdone[$nprod] = 0;
    $jbcrsh[$nprod] = 0;
    $jbhung[$nprod] = 0;
    $jbhpss[$nprod] = 0;
    $jbresub[$nprod] = 0;


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and prodSeries = '$prodtag[$nprod]' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcreat[$nprod] = $mpr;
       }
    $cursor->finish();
    
  
############

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%'  and prodSeries = '$prodtag[$nprod]' and jobStatus = 'Done' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbdone[$nprod] = $mpr;
       }
    $cursor->finish();


###########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and prodSeries = '$prodtag[$nprod]' and jobStatus <> 'Done' and jobStatus <> 'n/a' and jobStatus <> 'hung'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbcrsh[$nprod] = $mpr;
       }
    $cursor->finish();


##########

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and prodSeries = '$prodtag[$nprod]' and jobStatus = 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhung[$nprod] = $mpr;
       }
    $cursor->finish();

########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and prodSeries = '$prodtag[$nprod]' and inputHpssStatus like 'hpss_error%'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbhpss[$nprod] = $mpr;
       }
    $cursor->finish();


########## 

   $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$artrg[$nprod]%$prodtag[$nprod]%' and prodSeries = '$prodtag[$nprod]' and submitAttempt >=2  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $jbresub[$nprod] = $mpr;
       }
    $cursor->finish();

########## 


 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$artrg[$nprod]</h3></td>
<td HEIGHT=10><h3>$prodtag[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbcreat[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbdone[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2011;pflag=jstat">$jbcrsh[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2011;pflag=hung">$jbhung[$nprod]</h3></td>
<td HEIGHT=10><h3><a href="http://www.star.bnl.gov/devcgi/RetriveJobStat.pl?trigs=$artrg[$nprod];prod=$prodtag[$nprod];pyear=2011;pflag=hpss">$jbhpss[$nprod]</h3></td>
<td HEIGHT=10><h3>$jbresub[$nprod]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nprod]</h3></td>
<td HEIGHT=10><h3>$strtime[$nprod]</h3></td>
<td HEIGHT=10><h3>$fntime[$nprod]</h3></td>
</TR>
END

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
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Summary of production jobs status for<font color="blue"> run 2011 </font>data  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<h4 ALIGN=LEFT><font color="#ff0000">Ongoing production is in red color</font></h4>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=60><B><h3>Trigger set</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Production tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.jobs created</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.jobs done</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs crashed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs 'hung'</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs failed due to HPSS error</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.jobs resubmit</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>No.events produced<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=60><B><h3>Start time <h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"15%\" HEIGHT=60><B><h3>End time <h3></B></TD>
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
