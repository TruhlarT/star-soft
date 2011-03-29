#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# streamCpuRate.pl to make plots for average RealTime/CPU job's usage and stream rate 
#
#######################################################################################


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
      jbtot     => '$', 
      strv      => '$'
};


($sec,$min,$hour,$mday,$mon,$year) = localtime();


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".($mon+1)."-".$mday;

my $nowdate = $todate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my @prodyear = ("2010");


my @arperiod = ( );
my @arval = ("cpu","rtime/cpu","jobtottime");
my @arrcas = ();
my @arrcrs = ();

my @arrprod = ();
my @arstream = ();
my @ardays = ();
my $nday = ();
my $nst = 0;
my $str;
my $npr = 0;
my $mpr;
my $pday;
my $pcpu;
my $prtime;
my $pstream;
my $jbTottime;
my $pryear = "2010";

my %rte = {};
my %nstr = {};
my %arcpu = {};
my %arjbtime = {};

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
my @ndate = ();
my $ndt = 0;
my $nn = 0;
my $ni = 0;

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


#my @arhr = ();
#my $mhr = 0;
#my $nhr = 0;

my @arnode = ();
my @arperiod = ("week","1_month","2_months","3_months","4_months","5_months","6_months");

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

    $sql="SELECT DISTINCT nodeID  FROM $JobStatusT where nodeID like ' rcas6%' order by nodeID" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $arrcas[$nn] = $dy;
          $nn++;
       }
    $cursor->finish();


    $sql="SELECT DISTINCT nodeID  FROM $JobStatusT where nodeID like ' rcrs6%' order by nodeID" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $arrcrs[$ni] = $dy;
          $ni++;
       }
    $cursor->finish();

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qprod   = $query->param('prod');
my $qperiod = $query->param('period');
my $qvalue  = $query->param('pvalue');
my $qnode   = $query->param('pnode');


if( $qvalue eq "" and $qprod eq "" and $qnode eq "" and $qperiod eq "" ) {

    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production CPU&RealTime usage by node</u></h1>\n";
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
	                          -default=>P10ik,
      			          -size =>1);
 
    
    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Node name <br> </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pnode',
                                  -values=>\@arrcrs,
                                  -size =>1);


    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Period of monitoring <br> </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'period',
                                  -values=>\@arperiod,
                                  -default=>day,
                                  -size =>1);

    
    print "<p>";
    print "</td><td>";
    print "</td> </tr> </table><hr><center>";
    print "</h4>";    
    print "<br>";
    print "<br>"; 
    print "<hr> <table align=center>";
    print "<tr ALIGN=center>";
    print "<td>";  
    print "<h3 align=center> Stream values: <br> CPU, rtime/CPU,<br>jobs total time on the farm<br></h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pvalue',
	                          -values=>\@arval,
	                          -default=>cpu,
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
 
my $qprod   = $qqr->param('prod');
my $qperiod = $qqr->param('period');
my $qvalue  = $qqr->param('pvalue');
my $qnode   = $qqr->param('pnode');
my $dnode   = "".$qnode; 
#my $dnode;

my @arnode = ( "rcrs6114.rcf.bnl.gov",
               "rcrs6115.rcf.bnl.gov",
               "rcrs6116.rcf.bnl.gov",
               "rcrs6117.rcf.bnl.gov",
               "rcrs6118.rcf.bnl.gov",
               "rcrs6119.rcf.bnl.gov",
               "rcrs6120.rcf.bnl.gov",
               "rcrs6121.rcf.bnl.gov",
               "rcrs6122.rcf.bnl.gov",
               "rcrs6123.rcf.bnl.gov",
               "rcrs6124.rcf.bnl.gov",
               "rcrs6125.rcf.bnl.gov",
               "rcrs6126.rcf.bnl.gov",
               "rcrs6127.rcf.bnl.gov",
               "rcrs6128.rcf.bnl.gov", 
               "rcrs6129.rcf.bnl.gov",
               "rcrs6130.rcf.bnl.gov",
               "rcrs6131.rcf.bnl.gov",
               "rcrs6132.rcf.bnl.gov",
               "rcrs6133.rcf.bnl.gov",
               "rcrs6134.rcf.bnl.gov",
               "rcrs6135.rcf.bnl.gov",
               "rcrs6136.rcf.bnl.gov",
               "rcrs6137.rcf.bnl.gov",
               "rcrs6138.rcf.bnl.gov",
               "rcrs6139.rcf.bnl.gov",
               "rcrs6140.rcf.bnl.gov",
               "rcrs6141.rcf.bnl.gov",
               "rcrs6142.rcf.bnl.gov",
               "rcrs6143.rcf.bnl.gov",
               "rcrs6144.rcf.bnl.gov",
               "rcrs6145.rcf.bnl.gov"
	       );
    
    $JobStatusT = "JobStatus".$pryear;

  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $myday;
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


 #####################

    if( $qperiod eq "day") {  
     $day_diff = 1;

    }elsif( $qperiod eq "week") {
        $day_diff = 8;

    } elsif ( $qperiod =~ /month/) {
        @prt = split("_", $qperiod);
        $nmonth = $prt[0];
        $day_diff = 30*$nmonth + 1;
    }

    $day_diff = int($day_diff);

     if( $qperiod eq "day" or $qperiod eq "week") {

    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT WHERE prodSeries = ?  AND jobStatus = 'Done' AND runDay <> '0000-00-00' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) <= ?  order by PDATE ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }

##############################

   }else{

    $sql="SELECT DISTINCT runDay  FROM $JobStatusT WHERE prodSeries = ? AND jobStatus = 'Done'  AND  runDay <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(runDay)) < ?  order by runDay";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
      }
    }

 %rte = {};
 %nstr = {};
 %arcpu = {};

  my $maxval = 1;
  my $maxcpu = 0;
  my $maxjbtime = 0.1;
 
 @ndate = ();
 $ndt = 0;

 if( $qvalue eq "jobtottime" ) {

 %arjbtime = {};

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

 @ndate = ();
 $ndt = 0;

############################# 

   foreach my $tdate (@ardays) {
	@jbstat = ();  
	$nstat = 0;

    if( $qperiod eq "day" or $qperiod eq "week") {

      for ($k = 0; $k<scalar(@arnode); $k++) {
       $dnode   = " ".$arnode[$k]; 

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, jobtotalTime, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND nodeID = '$dnode' AND prodSeries = ? AND jobtotalTime > 0.1  AND submitAttempt = 1 AND jobStatus = 'Done' AND NoEvents >= 10  order by createTime";

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
  }

     }else{

    for ($k = 0; $k<scalar(@arnode); $k++) {
       $dnode   = " ".$arnode[$k]; 

  $sql="SELECT runDay, jobtotalTime, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND nodeID = '$dnode' AND prodSeries = ? AND jobtotalTime > 0.1  AND submitAttempt = 1  AND jobStatus = 'Done' AND NoEvents >= 10 order by runDay ";

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
     }


     foreach $jset (@jbstat) {
           $pday      = ($$jset)->vday;
           $jbTottime = ($$jset)->jbtot;
           $pstream   = ($$jset)->strv;

           $arjbtime{$pstream,$ndt} = $arjbtime{$pstream,$ndt} + $jbTottime;
           $nstr{$pstream,$ndt}++;

           $ndate[$ndt] = $pday;

          }

          foreach my $mfile (@arstream) {
             if ($nstr{$mfile,$ndt} >= 2 ) {
           $arjbtime{$mfile,$ndt} = $arjbtime{$mfile,$ndt}/$nstr{$mfile,$ndt};

                if ( $arjbtime{$mfile,$ndt} > $maxjbtime ) {
                    $maxjbtime = $arjbtime{$mfile,$ndt} ;
                }

            if ( $mfile eq "physics" ) {
               $jbphysics[$ndt] =  $arjbtime{$mfile,$ndt};
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

##################################### cpu, rtime/cpu

   }elsif( $qvalue eq "cpu" or $qvalue eq "rtime/cpu"  ) {

 @ndate = ();
 $ndt = 0;

 @arupsilon = ();
 @armtd = ();
 @arphysics = ();
 @argamma = ();
 @arhlt = ();
 @arfmsfast = ();
 @ndate = ();
 @arht = ();
 @aratomcules = ();
 @arupc = ();
 @armonitor = ();
 @arpmdftp = ();

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

############################# 

    foreach my $tdate (@ardays) {
        @jbstat = ();
        $nstat = 0;

    if( $qperiod eq "day" or $qperiod eq "week") {

       for ($k = 0; $k<scalar(@arnode); $k++) {
       $dnode   = " ".$arnode[$k]; 

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND nodeID = '$dnode' AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 and jobStatus = 'Done' AND NoEvents >= 10 order by createTime ";

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
       }

    }else{

     for ($k = 0; $k<scalar(@arnode); $k++) {
     $dnode   = " ".$arnode[$k]; 

  $sql="SELECT runDay, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE runDay = '$tdate' AND prodSeries = ?  AND nodeID = '$dnode' AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 AND jobStatus = 'Done' AND NoEvents >= 10 order by runDay ";

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
    }

     foreach $jset (@jbstat) {
            $pday     = ($$jset)->vday;
            $pcpu     = ($$jset)->cpuv;
            $prtime   = ($$jset)->rtmv;
            $pstream  = ($$jset)->strv;

    if( $pcpu >= 0.001) {

        $rte{$pstream,$ndt} = $rte{$pstream,$ndt} + $prtime/$pcpu;
        $arcpu{$pstream,$ndt} = $arcpu{$pstream,$ndt} + $pcpu;
        $nstr{$pstream,$ndt}++;

            $ndate[$ndt] = $pday;

            }
          }

####################

          foreach my $mfile (@arstream) {
              if ($nstr{$mfile,$ndt} >= 3 ) {
                  $arcpu{$mfile,$ndt} = $arcpu{$mfile,$ndt}/$nstr{$mfile,$ndt};
                  $rte{$mfile,$ndt} = $rte{$mfile,$ndt}/$nstr{$mfile,$ndt};
                  if ( $rte{$mfile,$ndt} > $maxval ) {
                $maxval =  $rte{$mfile,$ndt}
                 }
                  if ( $arcpu{$mfile,$ndt} > $maxcpu ) {
                      $maxcpu = $arcpu{$mfile,$ndt} ;
                  }
                  if ( $mfile eq "physics" ) {
               $arphysics[$ndt] = $rte{$mfile,$ndt};
               $cpphysics[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "mtd" ) {
               $armtd[$ndt] = $rte{$mfile,$ndt};
               $cpmtd[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $arupsilon[$ndt] = $rte{$mfile,$ndt};
               $cpupsilon[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $argamma[$ndt] = $rte{$mfile,$ndt};
               $cpgamma[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $arhlt[$ndt] = $rte{$mfile,$ndt};
               $cphlt[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $arfmsfast[$ndt] = $rte{$mfile,$ndt};
               $cpfmsfast[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $arht[$ndt] = $rte{$mfile,$ndt};
               $cpht[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $aratomcules[$ndt] = $rte{$mfile,$ndt};
               $cpatomcules[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $armonitor[$ndt] = $rte{$mfile,$ndt};
               $cpmonitor[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $arpmdftp[$ndt] = $rte{$mfile,$ndt};
               $cppmdftp[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $arupc[$ndt] =  $rte{$mfile,$ndt};
               $cpupc[$ndt] =  $arcpu{$mfile,$ndt};
               }
              }
          }

        $ndt++;

    } # foreach tdate

###########################################################

  }

    &StDbProdDisconnect();

 my $ylabel;
 my $gtitle; 
 my @data = ();

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


       if ( $qvalue eq "rtime/cpu" ) {

       $ylabel = "Average ratio RealTime/CPU per hour";
       $gtitle = "Average ratio RealTime/CPU per hour for different streams for $qperiod";

    @data = ();

  @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@armonitor, \@arpmdftp, \@arupc, \@aratomcules, \@armtd ) ;

  	$max_y = $maxval + 0.2*$maxval; 
#        $max_y = int($max_y);

  }elsif(  $qvalue eq "cpu" ) {

       $ylabel = "Average CPU in sec/evt per hour";
       $gtitle = "Average CPU in sec/evt per hour for different streams for $qperiod";

    @data = ();

  @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpmonitor, \@cppmdftp, \@cpupc, \@cpatomcules, \@cpmtd ) ;

    	$max_y = $maxcpu + 0.2*$maxcpu; 
        $max_y = int($max_y);

  }elsif(  $qvalue eq "jobtottime" ) {

    @data = ();

   $ylabel = "Total average time jobs stay on the farm in hours";
   $gtitle = "Total average time jobs stay on the farm (finished per hour) for $qperiod ";

@data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbmonitor, \@jbpmdftp, \@jbupc, \@jbatomcules, \@jbmtd ) ;

  $max_y = $maxjbtime + 0.2*$maxjbtime;
  $max_y = int($max_y);

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

	$graph->set(x_label => "Datetime of jobs completion",
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange lred lblack lgray lbrown lyellow) ],
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
          <title>CPU&RealTime usage at CRS nodes</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production on $qnode  for $qperiod period </h1>
     

    </body>
   </html>
END
}
