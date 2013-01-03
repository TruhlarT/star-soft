#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# streamCpuPlots.pl to make plots of average CPU, RealTime/CPU, total time job's usage for extended periods of production time 
#
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Mysql;
use Class::Struct;


$dbhost="fc2.star.bnl.gov:3386";
#$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      vday      => '$',
      cpuv      => '$',
      rtmv      => '$', 
      strk      => '$',
      strv      => '$',
      jbtot     => '$'
};


($sec,$min,$hour,$mday,$mon,$year) = localtime();

$mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday;

my $nowdate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my @prodyear = ("2010","2011","2012","2013");


my @arperiod = ( );
my $mstr;
my @arrate = ("cpu","rtime/cpu","jobtottime","ntracks","stream_rate","njobs" );

my @arrprod = ();
my @arstream = ();
my $nst = 0;
my $str;
my $npr = 0;
my $mpr;
my $pday;
my $pcpu;
my $prtime;
my $pstream;
my $jbTottime;

my $pryear = "2012";

my %rte = {};
my %nstr = {};
my %arcpu = {};
my %artrk = {};
my %arjbtime = {};

my $ptrack;
my @arupsilon = ();
my @armtd = ();
my @arphysics = ();
my @argamma = ();
my @arhlt = ();
my @arfmsfast = ();
my @arht = ();
my @aratomcules = ();
my @arupc = ();
my @armonitor = ();
my @arpmdftp = ();
my @arcentralpro = ();

my @ndate = ();
my $ndt = 0;

my @nstphysics = ();
my @nstgamma = ();
my @nstmtd = ();
my @nsthlt = ();
my @nstfmsfast = ();
my @nstht = ();
my @nstatomcules = ();
my @nstupc = ();
my @nstmonitor = ();
my @nstpmdftp = ();
my @nstupsilon = ();
my @numstream  = ();
my @nstcentralpro  = ();

my @rtgamma = ();
my @rtmtd = ();
my @rthlt = ();
my @rtfmsfast = ();
my @rtht = ();
my @rtatomcules = ();
my @rtupc = ();
my @rtmonitor = ();
my @rtpmdftp = ();
my @rtupsilon = ();
my @rtphysics = ();
my @rtcentralpro  = ();

my @cpupsilon = ();
my @cpmtd = ();
my @cpphysics = ();
my @cpgamma = ();
my @cphlt = ();
my @cpfmsfast = ();
my @cpht = ();
my @cpatomcules = ();
my @cpupc = ();
my @cpmonitor = ();
my @cppmdftp = ();
my @cpcentralpro  = ();

my @trupsilon = ();
my @trmtd = ();
my @trphysics = ();
my @trgamma = ();
my @trhlt = ();
my @trfmsfast = ();
my @trht = ();
my @tratomcules = ();
my @trupc = ();
my @trmonitor = ();
my @trpmdftp = ();
my @trcentralpro  = ();

my @jbupsilon = ();
my @jbmtd = ();
my @jbphysics = ();
my @jbgamma = ();
my @jbhlt = ();
my @jbfmsfast = ();
my @jbht = ();
my @jbatomcules = ();
my @jbupc = ();
my @jbmonitor = ();
my @jbpmdftp = ();
my @jbcentralpro  = ();
 
 my @arperiod = ("week","1_month","2_months","3_months","4_months","5_months","6_months");

#my @arperiod = ("1_month","2_months","3_months","4_months","5_months","6_months");

  &StDbProdConnect();


 $JobStatusT = "JobStatus2010";  

    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();

$JobStatusT = "JobStatus2011";  

    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();
  
$JobStatusT = "JobStatus2012";  

    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

#my $pryear = $query->param('pyear');
my $qprod = $query->param('prod');
my $qperiod = $query->param('period');
my $srate = $query->param('prate');

if( $qperiod eq "" and $qprod eq "" and $srate eq "" ) {
    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production CPU&RealTime usage </u></h1>\n";
    print "<br>";
    print "<br>";
    print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Production series <br></h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prod',
	                          -values=>\@arrprod,
	                          -default=>P12id,
      			          -size =>1);


   print "<p>";
    print "</td><td>";
    print "<h3 align=center> Stream jobs  values: <br> CPU, rtime/CPU, <br>jobs total time on the farm,<br> avg number of tracks in jobs,<br> stream jobs ratios by finish time,<br>number of stream jobs</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
                                  -values=>\@arrate,
                                  -default=>cpu,
                                  -size =>1);


    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Period of monitoring <br> </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'period',
                                  -values=>\@arperiod,
                                  -size =>1); 

    
    print "<p>";
    print "</td><td>";
    print "</td> </tr> </table><hr><center>";

    print "</h4>";
    print "<br>";
    print "<br>";
    print "<br>";
    print $query->submit(),"<p>";
    print $query->reset();
    print $query->endform();
    print "<br>";
    print "<br>";
    print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

    print $query->end_html();

} else{
    
  my $qqr = new CGI;
 
    my $qprod = $qqr->param('prod');
    my $qperiod = $qqr->param('period');
    my $srate = $qqr->param('prate');
 
    
 # Tables


 if( $qprod =~ /P10/ ) {$pryear = "2010"};
 if( $qprod =~ /P11/ ) {$pryear = "2011"};
 if( $qprod =~ /P12/ ) {$pryear = "2012"};
 if( $qprod =~ /P13/ ) {$pryear = "2013"};
      
    $JobStatusT = "JobStatus".$pryear;


  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $myday;
  my $nday = 0;
  my @ardays = ();
  my $tdate;
  my @jbstat = ();  
  my $nstat = 0;
  my $jset;

     @arstream = ();


 &StDbProdConnect();

      $sql="SELECT DISTINCT streamName  FROM $JobStatusT where prodSeries = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod);

       while( $str = $cursor->fetchrow() ) {
          $arstream[$nst] = $str;
          $nst++;
       }
    $cursor->finish();


#    if($pryear eq "2009") {
#	$nowdate = "2009-12-31";
#    } else {
	$nowdate = $todate;
#    }

     if( $qperiod eq "week") {
	$day_diff = 8;
  
    } elsif ( $qperiod =~ /month/) {
	@prt = split("_", $qperiod);
	$nmonth = $prt[0];
	$day_diff = 30*$nmonth + 1; 
    }

    $day_diff = int($day_diff);


     if( $qperiod eq "week") {

    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT WHERE prodSeries = ?  AND runDay <> '0000-00-00' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) <= $day_diff  order by PDATE ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

##############################

   }else{ 
 
    $sql="SELECT DISTINCT runDay  FROM $JobStatusT WHERE prodSeries = ?  AND  runDay <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(runDay)) < ?  order by runDay";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

   }

 %nstr = {};
 @numstream = ();

  my $maxcpu = 1.0;
  my $maxval = 1.0;
  my $maxjbtime = 0.1;
  my $maxtrk = 1.0;

##################################### average CPU

        if( $srate eq "cpu" ) {

 %arcpu = {};
 %nstr = {};

 @cpupsilon = ();
 @cpmtd = ();
 @cpphysics = ();
 @cpgamma = ();
 @cphlt = ();
 @cpfmsfast = ();
 @cpht = ();
 @cpatomcules = ();
 @cpupc = ();
 @cpmonitor = ();
 @cppmdftp = (); 
 @cpcentralpro = ();

 @ndate = ();
 $ndt = 0;
 $maxcpu = 1.0;

   foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, CPU_per_evt_sec, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 and jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'PDATE');
                ($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');
            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }

     }else{

  $sql="SELECT runDay, CPU_per_evt_sec, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'runDay');
                ($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }
      }


     foreach $jset (@jbstat) {
            $pday     = ($$jset)->vday;
            $pcpu     = ($$jset)->cpuv;
            $pstream  = ($$jset)->strv;

    if( $pcpu >= 0.01) {

        $arcpu{$pstream,$ndt} = $arcpu{$pstream,$ndt} + $pcpu;
        $nstr{$pstream,$ndt}++;

            $ndate[$ndt] = $pday;

            }
          }

########################
 
          foreach my $mfile (@arstream) {
            if ($nstr{$mfile,$ndt} >= 3 ) {
              $arcpu{$mfile,$ndt} = $arcpu{$mfile,$ndt}/$nstr{$mfile,$ndt};
                if ( $arcpu{$mfile,$ndt} > $maxcpu ) {
                    $maxcpu = $arcpu{$mfile,$ndt} ;
                }

              if ( $mfile eq "physics" ) {
               $cpphysics[$ndt] = $arcpu{$mfile,$ndt};
             }elsif( $mfile eq "centralpro" ) {
               $cpcentralpro[$ndt] = $arcpu{$mfile,$ndt};
             }elsif( $mfile eq "mtd" ) {
               $cpmtd[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $cpgamma[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $cpupsilon[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $cphlt[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $cpfmsfast[$ndt] =  $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $cpht[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $cpatomcules[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $cpmonitor[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $cppmdftp[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $cpupc[$ndt] =  $arcpu{$mfile,$ndt};
           }else{
             next;
           }
              }
          }

        $ndt++;

     }# foreach tdate


###################################### ratio realTime/CPU

             }elsif( $srate eq "rtime/cpu" ) { 

 %rte = {};
 %arcpu = {};
 %nstr = {};

 @arupsilon = ();
 @armtd = ();
 @arphysics = ();
 @argamma = ();
 @arhlt = ();
 @arfmsfast = ();
 @arht = ();
 @aratomcules = ();
 @arupc = ();
 @armonitor = ();
 @arpmdftp = ();
 @arcentralpro = ();

 @cpupsilon = ();
 @cpmtd = ();
 @cpphysics = ();
 @cpgamma = ();
 @cphlt = ();
 @cpfmsfast = ();
 @cpht = ();
 @cpatomcules = ();
 @cpupc = ();
 @cpmonitor = ();
 @cppmdftp = ();
 @cpcentralpro = ();

 @ndate = ();
 $ndt = 0;
 $maxval = 1.0;


   foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 and jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'PDATE');
                ($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
                ($$fObjAdr)->rtmv($fvalue)    if( $fname eq 'RealTime_per_evt');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }

     }else{

   $sql="SELECT runDay, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 and jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;


                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'runDay');
                ($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
                ($$fObjAdr)->rtmv($fvalue)    if( $fname eq 'RealTime_per_evt');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }
     }

     foreach $jset (@jbstat) {
            $pday     = ($$jset)->vday;
            $pcpu     = ($$jset)->cpuv;
            $prtime   = ($$jset)->rtmv;
            $pstream  = ($$jset)->strv;

    if( $pcpu >= 0.01) {

        $rte{$pstream,$ndt} = $rte{$pstream,$ndt} + $prtime/$pcpu;
        $nstr{$pstream,$ndt}++;

            $ndate[$ndt] = $pday;

            }
          }

          foreach my $mfile (@arstream) {
              if ($nstr{$mfile,$ndt} >= 3 ) {
                   $rte{$mfile,$ndt} = $rte{$mfile,$ndt}/$nstr{$mfile,$ndt};

                  if ( $rte{$mfile,$ndt} > $maxval ) {
                $maxval =  $rte{$mfile,$ndt}
                }
                  if ( $mfile eq "physics" ) {
               $arphysics[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $arcentralpro[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "mtd" ) {
               $armtd[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $arupsilon[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $argamma[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $arhlt[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $arfmsfast[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $arht[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $aratomcules[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $armonitor[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $arpmdftp[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $arupc[$ndt] =  $rte{$mfile,$ndt};

          }else{
             next;
           }
              }
          }

        $ndt++;

    } # foreach tdate


########################################## average number of tracks

        }elsif( $srate eq "ntracks" ) { 

 %artrk = {};
 %nstr = {};

 @trupsilon = ();
 @trmtd = ();
 @trphysics = ();
 @trgamma = ();
 @trhlt = ();
 @trfmsfast = ();
 @trht = ();
 @tratomcules = ();
 @trupc = ();
 @trmonitor = ();
 @trpmdftp = ();
 @trcentralpro = ();

 @ndate = ();
 $ndt = 0;
 $maxtrk = 1.0;

   foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, avg_no_tracks, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND  jobStatus = 'Done' AND avg_no_tracks >= 1 AND NoEvents >= 10 ";


            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'PDATE');
                ($$fObjAdr)->strk($fvalue)    if( $fname eq 'avg_no_tracks');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }

     }else{

   $sql="SELECT runDay, avg_no_tracks, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries= ? AND jobStatus = 'Done' AND avg_no_tracks >= 1 AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'runDay');
                ($$fObjAdr)->strk($fvalue)    if( $fname eq 'avg_no_tracks');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }
     }

    foreach $jset (@jbstat) {
            $pday     = ($$jset)->vday;
            $pstream  = ($$jset)->strv;
            $ptrack   = ($$jset)->strk;

        $artrk{$pstream,$ndt} = $artrk{$pstream,$ndt} + $ptrack;
        $nstr{$pstream,$ndt}++;

            $ndate[$ndt] = $pday;
         }


          foreach my $mfile (@arstream) {
              if ($nstr{$mfile,$ndt} >= 3 ) {
                  $artrk{$mfile,$ndt} = $artrk{$mfile,$ndt}/$nstr{$mfile,$ndt};

                 if ( $artrk{$mfile,$ndt} > $maxtrk ) {
                $maxtrk =  $artrk{$mfile,$ndt}
               }
                  if ( $mfile eq "physics" ) {
               $trphysics[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $trcentralpro[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "mtd" ) {
               $trmtd[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $trupsilon[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $trgamma[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $trhlt[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $trfmsfast[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $trht[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $tratomcules[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $trmonitor[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $trpmdftp[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $trupc[$ndt] =  $artrk{$mfile,$ndt};

           }else{
             next;
           }
              }
          }

        $ndt++;

    } # foreach tdate

#############################  stream ratios

          }elsif( $srate eq "stream_rate" or $srate eq "njobs" ) { 
 
 %nstr = {};
 @numstream = 0;

 @nstphysics = ();
 @nstgamma = ();
 @nstmtd = ();
 @nsthlt = ();
 @nstfmsfast = ();
 @nstht = ();
 @nstatomcules = ();
 @nstupc = ();
 @nstmonitor = ();
 @nstpmdftp = ();
 @nstupsilon = ();
 @nstcentralpro = ();

 @ndate = ();
 $ndt = 0;  

 @rtphysics = ();
 @rtgamma = ();
 @rtmtd = ();
 @rthlt = ();
 @rtfmsfast = ();
 @rtht = ();
 @rtatomcules = ();
 @rtupc = ();
 @rtmonitor = ();
 @rtpmdftp = ();
 @rtupsilon = ();
 @rtcentralpro = ();

    foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND  jobStatus = 'Done' AND NoEvents >= 10 order by createTime ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'PDATE');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }

     }else{

   $sql="SELECT runDay, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries = ? AND jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'runDay');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }
     }

    foreach $jset (@jbstat) {
            $pday     = ($$jset)->vday;
            $pstream  = ($$jset)->strv;

          $nstr{$pstream,$ndt}++;
          $ndate[$ndt] = $pday;
          }

         foreach my $mfile (@arstream) {
 
           if ( $mfile eq "physics" ) {
               $nstphysics[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $nstcentralpro[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "mtd" ) {
               $nstmtd[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $nstupsilon[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $nstgamma[$ndt] =  $nstr{$mfile,$ndt};
	      }elsif( $mfile eq "hlt" ) {
               $nsthlt[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $nstfmsfast[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $nstht[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $nstatomcules[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $nstmonitor[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $nstpmdftp[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $nstupc[$ndt] =  $nstr{$mfile,$ndt};
           }else{
             next;
           }
              }
#          }

        $ndt++;

    } # foreach tdate
 
      for($ii = 0; $ii < $ndt; $ii++) {
      $numstream[$ii] = $nstphysics[$ii]+$nstcentralpro[$ii]+$nstmtd[$ii]+$nsthlt[$ii]+$nstht[$ii]+$nstmonitor[$ii]+$nstpmdftp[$ii]+ $nstupc[$ii]+ $nstgamma[$ii]+  $nstatomcules[$ii]+ $nstupsilon[$ii];

     if ($numstream[$ii] >= 1) {
      $rtphysics[$ii] = $nstphysics[$ii]/$numstream[$ii];
      $rtcentralpro[$ii] = $nstcentralpro[$ii]/$numstream[$ii];
      $rtmtd[$ii] = $nstmtd[$ii]/$numstream[$ii];
      $rthlt[$ii] = $nsthlt[$ii]/$numstream[$ii];
      $rtht[$ii] = $nstht[$ii]/$numstream[$ii];
      $rtmonitor[$ii] = $nstmonitor[$ii]/$numstream[$ii];
      $rtpmdftp[$ii] = $nstpmdftp[$ii]/$numstream[$ii];
      $rtupc[$ii] = $nstupc[$ii]/$numstream[$ii];
      $rtupsilon[$ii] = $nstupsilon[$ii]/$numstream[$ii];
      $rtgamma[$ii] = $nstgamma[$ii]/$numstream[$ii];
#      $rtfmsfast[$ii] = $nstfmsfast[$ii]/$numstream[$ii];
      $rtatomcules[$ii] = $nstatomcules[$ii]/$numstream[$ii];

       }
  }

#########################################  jobs total time on the farm

   }elsif( $srate eq "jobtottime" ) { 

 %arjbtime = {};
 %nstr = {};

 @jbupsilon = ();
 @jbmtd = ();
 @jbphysics = ();
 @jbgamma = ();
 @jbhlt = ();
 @jbfmsfast = ();
 @jbht = ();
 @jbatomcules = ();
 @jbupc = ();
 @jbmonitor = ();
 @jbpmdftp = ();
 @jbcenralpro = ();

 @ndate = ();
 $ndt = 0;  
 $maxjbtime = 0.1;


   foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

     if( $qperiod eq "week") {

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, jobtotalTime, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND jobtotalTime > 0.1  AND submitAttempt = 1 AND jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'PDATE');
                ($$fObjAdr)->jbtot($fvalue)   if( $fname eq 'jobtotalTime');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }

     }else{

   $sql="SELECT runDay, jobtotalTime, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries = ? AND  jobtotalTime > 0.1 AND submitAttempt = 1 AND jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qprod);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->vday($fvalue)    if( $fname eq 'runDay');
                ($$fObjAdr)->jbtot($fvalue)   if( $fname eq 'jobtotalTime');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }
     }

    foreach $jset (@jbstat) {
            $pday      = ($$jset)->vday;
            $pstream   = ($$jset)->strv;
            $jbTottime = ($$jset)->jbtot; 

	    $arjbtime{$pstream,$ndt} = $arjbtime{$pstream,$ndt} + $jbTottime;
            $nstr{$pstream,$ndt}++;

            $ndate[$ndt] = $pday;

          }

      foreach my $mfile (@arstream) {
          if ($nstr{$mfile,$ndt} >= 3 ) {
           $arjbtime{$mfile,$ndt} = $arjbtime{$mfile,$ndt}/$nstr{$mfile,$ndt};

                if ( $arjbtime{$mfile,$ndt} > $maxjbtime ) {
                    $maxjbtime = $arjbtime{$mfile,$ndt} ;
                }

            if ( $mfile eq "physics" ) {
               $jbphysics[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "centralpro" ) {
               $jbcentralpro[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "mtd" ) {
               $jbmtd[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "upsilon" ) {
               $jbupsilon[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "gamma" ) {
               $jbgamma[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "hlt" ) {
               $jbhlt[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "fmsfast" ) {
               $jbfmsfast[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "ht" ) {
               $jbht[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "atomcules" ) {
               $jbatomcules[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "monitor" ) {
               $jbmonitor[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "pmdftp" ) {
               $jbpmdftp[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "upc" ) {
               $jbupc[$ndt] =  $arjbtime{$mfile,$ndt};

           }else{
             next;
           }
            }
          }

        $ndt++;

    } # foreach tdate

  }

#############################

    &StDbProdDisconnect();

 my @data = ();
 my $ylabel;
 my $gtitle; 

    my $graph = new GD::Graph::linespoints(750,650);

    if ( ! $graph){
	print STDOUT $qqr->header(-type => 'text/plain');
	print STDOUT "Failed\n";

    } else {
	 

       $legend[0] = "st_physics   ";
       $legend[1] = "st_gamma     ";
       $legend[2] = "st_hlt       ";
       $legend[3] = "st_ht        ";
       $legend[4] = "st_monitor   ";
       $legend[5] = "st_pmdftp    ";
       $legend[6] = "st_upc       ";       
       $legend[7] = "st_atomcules ";
       $legend[8] = "st_mtd       ";
       $legend[9] = "st_centralpro ";

       if ( $srate eq "rtime/cpu" ) {

    @data = ();

       if( $qperiod eq "week") {

       $ylabel = "Average ratio RealTime/CPU per hour";
       $gtitle = "Average ratio RealTime/CPU per hour for different streams for $qperiod period";

      }else{

       $ylabel = "Average ratio RealTime/CPU per day";
       $gtitle = "Average ratio RealTime/CPU per day for different streams for $qperiod period";
      }     

  @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@armonitor, \@arpmdftp, \@arupc, \@aratomcules, \@armtd, \@arcentralpro ) ;

      $max_y = $maxval + 0.2*$maxval;
#     $max_y = int($max_y);

     }elsif(  $srate eq "cpu" ) {

  @data = ();

       if( $qperiod eq "week") {

       $ylabel = "Average CPU in sec/evt per hour";
       $gtitle = "Average CPU in sec/evt per hour for different streams for $qperiod period";

         }else{

       $ylabel = "Average CPU in sec/evt per day";
       $gtitle = "Average CPU in sec/evt per day for different streams for $qperiod period";

         }   

  @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpmonitor, \@cppmdftp, \@cpupc, \@cpatomcules, \@cpmtd, \@cpcentralpro ) ;

       $max_y = $maxcpu + 0.2*$maxcpu;
       $max_y = int($max_y);

  }elsif(  $srate eq "stream_rate" ) {

  @data = ();

       if( $qperiod eq "week") {

        $ylabel = "Ratio of different stream jobs finishing per hour ";
        $gtitle = "Ratio of different stream jobs finishing per hour for $qperiod period";

      }else{

        $ylabel = "Ratio of different stream jobs finishing per day ";
        $gtitle = "Ratio of different stream jobs finishing per day for $qperiod period";
     }

 @data = (\@ndate, \@rtphysics, \@rtgamma, \@rthlt, \@rtht, \@rtmonitor, \@rtpmdftp, \@rtupc, \@rtatomcules, \@rtmtd, \@rtcentralpro ) ;

        $max_y = 1.2;

    }elsif(  $srate eq "jobtottime" ) {

    @data = ();

       if( $qperiod eq "week") {

	$ylabel = "Total time jobs stay on the farm in hours";
	$gtitle = "Total time jobs stay on the farm (finishing per hour) for $qperiod period ";

      }else{

	$ylabel = "Total time jobs stay on the farm in hours ";
	$gtitle = "Total time jobs stay on the farm (finishing per day) for $qperiod period ";
     }

 @data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbmonitor, \@jbpmdftp, \@jbupc, \@jbatomcules, \@jbmtd, \@jbcentralpro ) ;
    $max_y = $maxjbtime + 0.2*$maxjbtime;    
    $max_y = int($max_y);

    }elsif(  $srate eq "ntracks" ) {

    @data = ();

       if( $qperiod eq "week") {

	$ylabel = "Average number of tracks in different streams per hour";
	$gtitle = "Average number of tracks in different streams per hour for $qperiod period ";

      }else{

	$ylabel = "Average number of tracks in different streams per day";
	$gtitle = "Average number of tracks in different streams per day for $qperiod period ";
     }

 @data = (\@ndate, \@trphysics, \@trgamma, \@trhlt, \@trht, \@trmonitor, \@trpmdftp, \@trupc, \@tratomcules, \@trmtd, \@trcentralpro ) ;
    
      $max_y = $maxtrk + 0.2*$maxtrk;
      $max_y = int($max_y); 


 }elsif(  $srate eq "njobs" ) {

  @data = ();

       if( $qperiod eq "week") {

        $ylabel = "Number of stream jobs finishing per hour ";
        $gtitle = "Number of stream jobs finishing per hour for $qperiod period";

      }else{

        $ylabel = "Number of stream jobs finishing per day ";
        $gtitle = "Number of stream jobs finishing per day for $qperiod period";
     }

 @data = (\@ndate, \@nstphysics, \@nstgamma, \@nsthlt, \@nstht, \@nstmonitor, \@nstpmdftp, \@nstupc, \@nstatomcules, \@nstmtd, \@nstcentralpro ) ;


     }
  
	my $xLabelsVertical = 1;
	my $xLabelPosition = 0;
	my $xLabelSkip = 1;
	my $skipnum = 1;
 
	$min_y = 0;

	if (scalar(@ndate) >= 40 ) {
	    $skipnum = int(scalar(@ndate)/20);
	}

	$xLabelSkip = $skipnum;

	$graph->set(x_label => "Datetime of job's completion",
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange marine lred lblack lyellow lbrown lgray) ],
                    line_width => 4,
                    markers => [ 2,3,4,5,6,7,8,9],
                    marker_size => 3,
                    x_label_skip => $xLabelSkip, 
                    x_labels_vertical =>$xLabelsVertical, 
	            );

	$graph->set_legend(@legend);
	$graph->set_legend_font(gdMediumBoldFont);
	$graph->set_title_font(gdGiantFont);
	$graph->set_x_label_font(gdGiantFont);
	$graph->set_y_label_font(gdGiantFont);
	$graph->set_x_axis_font(gdMediumBoldFont);
	$graph->set_y_axis_font(gdMediumBoldFont);
	
	if ( scalar(@ndate) <= 1 ) {
	    print $qqr->header(-type => 'text/html')."\n";
	    &beginHtml();
	} else {
            my $format = $graph->export_format;
	    print header("image/$format");
	    binmode STDOUT;

	    print STDOUT $graph->plot(\@data)->$format();
	}
#
    }
 }
 



###############################
#  subs and helper routines
###############################
sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}

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
          <title>CPU versus RealTime usage</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production and $qperiod period </h1>
     

    </body>
   </html>
END
}
