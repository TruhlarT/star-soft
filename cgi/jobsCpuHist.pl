#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# jobsCpuHist.pl to get distribution of CPU, realtime/cpu, total stream jobs execution time
#
#########################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
use Class::Struct;


$dbhost="duvall.star.bnl.gov";

#$dbhost="fc2.star.bnl.gov:3386";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      cpuv      => '$',
      rtmv      => '$',
      jbtot     => '$',
      nevt      => '$',
      strv      => '$'
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

my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my $lastdate;

my @prodyear = ("2013","2014","2015");


my @arperiod = ( );
my $mstr;
my @arrate = ("cpu","rtime/cpu","exectime","events","njobs");

my @arrprod = ();
my @arstream = ();
my $nst = 0;
my $str;
my $npr = 0;
my $mpr;
my $phr;
my $pcpu;
my $prtime;
my $pstream;
my $exctime;
my @nevents = ();
my @numjobs = ();
my $maxcpu = 0;
my $maxexectm = 0 ;
my $maxcpuval = 0;
my $maxvalue = 0;

my $pryear = "2014";

my $rte = 0;

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
my @arhltgood = ();
my @arcentralpro = ();
my @arwb = ();

my @ndate = ();
my $ndt = 0;
my @ardays = ();
my $ndy = 0;

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
my @cphltgood = ();
my @cpcentralpro  = (); 
my @cpwb  = (); 

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
my @jbhltgood = ();
my @jbcentralpro  = ();
my @jbwb = ();

  &StDbProdConnect();


 $JobStatusT = "JobStatus2013";


    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT  where runDay >= '2014-02-20' order by runDay ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();


 $JobStatusT = "JobStatus2014";


    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT where runDay >= '2015-01-02' order by runDay ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();


$arrprod[$npr] = "all2014";

my @arperiod = ("1_month","2_months","3_months","4_months","5_months","6_months","7_months","8_months","9_months","10_months","11_months","12_months");


&StDbProdDisconnect();


my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

#my $pryear = $query->param('pyear');

my $qperiod = $query->param('period');
my $qprod   = $query->param('prod');
my $srate   = $query->param('prate');


if( $qprod eq "" and $qperiod eq ""  and $srate eq "" ) {

    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Distributions of CPU/evt, RealTime/CPU, total time of jobs execution, number of events and jobs processed per day </u></h1>\n";
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
    print "<h3 align=center> Production series</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prod',
	                          -values=>\@arrprod,
	                          -default=>all2014,
      			          -size =>1);

  
   print "<p>";
    print "</td><td>";
    print "<h3 align=center> CPU/evt, Realtime/CPU, <br> total time of job's execution, <br> number of events and <br>jobs processed per day</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
                                  -values=>\@arrate,
                                  -default=>cpu,
                                  -size =>1);


    print "<p>";
    print "</td><td>";  
    print "<h3 align=center>Period of monitoring</h3>";
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

    my $qprod   = $qqr->param('prod');
    my $qperiod = $qqr->param('period');    
    my $srate   = $qqr->param('prate');
    
 # Tables

  if( $qprod =~ /P10/ ) {$pryear = "2010"};
  if( $qprod =~ /P11/ ) {$pryear = "2011"};
  if( $qprod =~ /P12/ ) {$pryear = "2012"};
  if( $qprod =~ /P13ib/ ) {$pryear = "2012"};
  if( $qprod =~ /P14ia/ ) {$pryear = "2013"};
  if( $qprod =~ /P14ig/ ) {$pryear = "2013"};
  if( $qprod =~ /P14ii/ ) {$pryear = "2014"};
  if( $qprod =~ /P15ib/ or $qprod =~ /P15ic/ or $qprod =~ /P15ie/) {$pryear = "2014"};

    $JobStatusT = "JobStatus".$pryear;


  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $mhr;
  my $nhr = 0;
  my @arhr = ();
  my $tdate;
  my @jbstat = ();  
  my $nstat = 0;
  my $jset;
  my $cpubin = 0;
  my $rcpubin = 0;
  my $jobtotbin = 0;

 
  if ( $qperiod =~ /month/) {
        @prt = split("_", $qperiod);
        $nmonth = $prt[0];
        $day_diff = 30*$nmonth + 1;
    }

    $day_diff = int($day_diff);


    @arstream = ();


 &StDbProdConnect();

  if($qprod eq "all2014" ) {

    $sql="SELECT DISTINCT streamName  FROM $JobStatusT where (prodSeries = 'P15ic' or prodSeries = 'P15ie') ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $str = $cursor->fetchrow() ) {
          $arstream[$nst] = $str;
          $nst++;
       }
    $cursor->finish();


###########   max createTime

      $sql="SELECT max(date_format(createTime, '%Y-%m-%d' ))  FROM $JobStatusT where (prodSeries = 'P15ic' or prodSeries = 'P15ie') ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

    my $mxtime = $cursor->fetchrow ;

       $cursor->finish();

       $lastdate = $mxtime;
       $nowdate = $lastdate;

#######    max CPU

     $sql="SELECT max(CPU_per_evt_sec)  FROM $JobStatusT where ( prodSeries = 'P15ic' or prodSeries = 'P15ie') ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

        $maxcpu = $cursor->fetchrow ;

       $cursor->finish();

        
###########   max exectime

      $sql="SELECT max(exectime)  FROM $JobStatusT where ( prodSeries = 'P15ic' or prodSeries = 'P15ie') ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

        $maxexectm = $cursor->fetchrow ;

       $cursor->finish();


    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d' ) as PDATE  FROM $JobStatusT WHERE (prodSeries = 'P15ic' or prodSeries = 'P15ie') AND  runDay <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) < ?  order by createTime";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$ndy] = $myday;
        $ndy++;
    }

         $cursor->finish();

  }else{

      $sql="SELECT DISTINCT streamName  FROM $JobStatusT where prodSeries = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod);

       while( $str = $cursor->fetchrow() ) {
          $arstream[$nst] = $str;
          $nst++;
       }
    $cursor->finish();

  }

###########   max createTime


      $sql="SELECT max(date_format(createTime, '%Y-%m-%d' ))  FROM $JobStatusT where prodSeries = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod);

    my $mxtime = $cursor->fetchrow ;

       $cursor->finish();

       $lastdate = $mxtime;


    if($pryear eq "2013" or $pryear eq "2014") {
        $nowdate = $lastdate;
    } else {
        $nowdate = $todate;
    }
      

###########   max CPU

      $sql="SELECT max(CPU_per_evt_sec)  FROM $JobStatusT where prodSeries = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod);

        $maxcpu = $cursor->fetchrow ;

       $cursor->finish();

        
###########   max exectime

      $sql="SELECT max(exectime)  FROM $JobStatusT where prodSeries = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod);

        $maxexectm = $cursor->fetchrow ;

       $cursor->finish();


    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d' ) as PDATE  FROM $JobStatusT WHERE prodSeries = ?  AND  runDay <> '0000-00-00'  AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) < ?  order by createTime";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$ndy] = $myday;
        $ndy++;
    }

         $cursor->finish();

  }


  #####################

 $rte = 1;
 
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
 @arhltgood = ();
 @arcentralpro = ();
 @arwb = ();

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
 @cphltgood = (); 
 @cpcentralpro  = ();
 @cpwb = (); 

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
 @jbhltgood = ();
 @jbcentralpro  = ();
 @jbwb = ();

 @nevents = ();
 @numjobs = ();


   if( $srate eq "exectime" ) {

 $ndt = 0;
 @ndate = ();
 @jbstat = ();
 $nstat = 0;

    foreach  $tdate (@ardays) {
 
	if($qprod eq "all2014") {

 
 $sql="SELECT exectime, streamName FROM $JobStatusT WHERE (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59' )  AND (prodSeries = 'P15ic' or prodSeries = 'P15ie') AND exectime > 0.1  AND jobStatus = 'Done' AND NoEvents >= 10  "; 

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

                ($$fObjAdr)->jbtot($fvalue)   if( $fname eq 'exectime');
		($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

	    }
	    $jbstat[$nstat] = $fObjAdr;
	    $nstat++;
         }

    }else{

  $sql="SELECT exectime, streamName FROM $JobStatusT WHERE (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59' )  AND prodSeries = ? AND exectime > 0.1  AND jobStatus = 'Done' AND NoEvents >= 10  "; 

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

                ($$fObjAdr)->jbtot($fvalue)   if( $fname eq 'exectime');
		($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

	    }
	    $jbstat[$nstat] = $fObjAdr;
	    $nstat++;
         }
      }
    }

###########

 if($qprod eq "P14ia" or $qprod eq "P14ig" or $qprod eq "P14ii") {
     $maxvalue = 120;
 }else{
     $maxvalue = 240;
 }

 $jobtotbin = int($maxvalue/120. + 0.01);

 $ndate[0] = 0;

 for ($i = 0; $i < 120; $i++) {
   $ndate[$i] = $jobtotbin*$i; 
 }

     foreach $jset (@jbstat) {
            $exctime = ($$jset)->jbtot;
	    $pstream   = ($$jset)->strv;

	    if($exctime <=  $maxvalue )  {
	   $ndt = int($exctime/$jobtotbin);
           $ndate[$ndt] = $jobtotbin*$ndt;  

	   if ( $pstream eq "physics" ) {
	       $jbphysics[$ndt]++;
#           }elsif( $pstream eq "centralpro" ) {
#               $jbcentral[$ndt]++; 
	   }elsif( $pstream eq "mtd" ) {
               $jbmtd[$ndt]++;
#           }elsif( $pstream eq "upsilon" ) {
#               $jbupsilon[$ndt]++; 
#           }elsif( $pstream eq "gamma" ) {
#               $jbgamma[$ndt]++; 
           }elsif( $pstream eq "hlt" ) {
               $jbhlt[$ndt]++;  
           }elsif( $pstream eq "fms" ) {
               $jbfmsfast[$ndt]++; 
#           }elsif( $pstream eq "ht" ) {
#               $jbht[$ndt]++;  
#           }elsif( $pstream eq "atomcules" ) {
#               $jbatomcules[$ndt]++; 
#           }elsif( $pstream eq "monitor" ) {
#               $jbmonitor[$ndt]++;  
           }elsif( $pstream eq "hltgood" ) {
               $jbhltgood[$ndt]++;   
           }elsif( $pstream eq "upc" ) {
               $jbupc[$ndt]++;
           }elsif( $pstream eq "W" or $pstream eq "WE" or $pstream eq "WB" ) {
               $jbwb[$ndt]++;
	       }
 	    }
        }



 }elsif( $srate eq "events" ) {

 $ndt = 0;
 @ndate = ();

    foreach  $tdate (@ardays) {
 
	$ndate[$ndt] = $tdate;

	if($qprod eq "all2014") {

 $sql="SELECT  sum(NoEvents) FROM $JobStatusT WHERE  (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') AND ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND jobStatus = 'Done'  "; 

	    $cursor =$dbh->prepare($sql)
	      || die "Cannot prepare statement: $DBI::errstr\n";
	    $cursor->execute();
 
       while( my $sumev = $cursor->fetchrow() ) {

          $nevents[$ndt] = int($sumev + 0.01);
          }

         $ndt++;
         $cursor->finish();

  }else{

  $sql="SELECT  sum(NoEvents) FROM $JobStatusT WHERE  (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59') AND prodSeries = ? AND jobStatus = 'Done'  "; 

	    $cursor =$dbh->prepare($sql)
	      || die "Cannot prepare statement: $DBI::errstr\n";
	    $cursor->execute($qprod);
 
       while( my $sumev = $cursor->fetchrow() ) {

          $nevents[$ndt] = int($sumev + 0.01);
          }

         $ndt++;
         $cursor->finish();
     
    }
 }
###########

 }elsif( $srate eq "njobs" ) {

 $ndt = 0;
 @ndate = ();

    foreach  $tdate (@ardays) {
 
	$ndate[$ndt] = $tdate;

      if($qprod eq "all2014") { 

 $sql="SELECT  count(jobfileName) FROM $JobStatusT WHERE  (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59')  AND ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND jobStatus = 'Done'  "; 

	    $cursor =$dbh->prepare($sql)
	      || die "Cannot prepare statement: $DBI::errstr\n";
	    $cursor->execute();
 
       while( my $njb = $cursor->fetchrow() ) {

          $numjobs[$ndt] = int($njb + 0.01);
          }

         $ndt++;
         $cursor->finish();

   }else{

  $sql="SELECT  count(jobfileName) FROM $JobStatusT WHERE  (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59')  AND prodSeries = ? AND jobStatus = 'Done'  "; 

	    $cursor =$dbh->prepare($sql)
	      || die "Cannot prepare statement: $DBI::errstr\n";
	    $cursor->execute($qprod);
 
       while( my $njb = $cursor->fetchrow() ) {

          $numjobs[$ndt] = int($njb + 0.01);
          }

         $ndt++;
         $cursor->finish();
      
    }
   }
###################

   }else{

 $ndt = 0;
 @ndate = ();

 @jbstat = ();
 $nstat = 0;

    foreach  $tdate (@ardays) {

    if($qprod eq "all2014") {

  $sql="SELECT CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59')  AND ( prodSeries = 'P15ic' or prodSeries = 'P15ie') AND CPU_per_evt_sec > 0.01 and jobStatus = 'Done' AND NoEvents >= 10  "; 

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

		($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
		($$fObjAdr)->rtmv($fvalue)    if( $fname eq 'RealTime_per_evt');
		($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

	     }
	    $jbstat[$nstat] = $fObjAdr;
	    $nstat++;
      }

    }else{

  $sql="SELECT CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE (createTime BETWEEN '$tdate 00:00:00' AND '$tdate 23:59:59')  AND prodSeries = ? AND CPU_per_evt_sec > 0.01 and jobStatus = 'Done' AND NoEvents >= 10  "; 

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

		($$fObjAdr)->cpuv($fvalue)    if( $fname eq 'CPU_per_evt_sec');
		($$fObjAdr)->rtmv($fvalue)    if( $fname eq 'RealTime_per_evt');
		($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

	    }
	    $jbstat[$nstat] = $fObjAdr;
	    $nstat++;
         }
      }
    }

###########

       if( $srate eq "cpu" ) {

 @ndate = ();
 $ndate[0] = 0;
  $ndt = 0;


 if($qprod eq "P14ia" or $qprod eq "P14ig" or $qprod eq "P14ii" ) {
     $maxcpuval = 110;
 }else{
     $maxcpuval = 220;
 }

 $cpubin   = int($maxcpuval/110. + 0.01);

 for ($i = 0; $i < 110; $i++) {

   $ndate[$i] = $cpubin*$i; 
 }

     foreach $jset (@jbstat) {
	    $pcpu     = ($$jset)->cpuv;
	    $pstream  = ($$jset)->strv;

            if($pcpu < $maxcpuval )     {

	    $ndt = int($pcpu/$cpubin);
            $ndate[$ndt] = $cpubin*$ndt;  

	       if ( $pstream eq "physics" ) {
	       $cpphysics[$ndt]++;
#              }elsif( $pstream eq "centralpro" ) {
#               $cpcentralpro[$ndt]++; 
	      }elsif( $pstream eq "mtd" ) {
               $cpmtd[$ndt]++;
#              }elsif( $pstream eq "upsilon" ) {
#               $cpupsilon[$ndt]++; 
#              }elsif( $pstream eq "gamma" ) {
#               $cpgamma[$ndt]++; 
              }elsif( $pstream eq "hlt" ) {
               $cphlt[$ndt]++;  
              }elsif( $pstream eq "fms" ) {
               $cpfmsfast[$ndt]++; 
#              }elsif( $pstream eq "ht" ) {
#               $cpht[$ndt]++;  
#              }elsif( $pstream eq "atomcules" ) {
#               $cpatomcules[$ndt]++; 
#              }elsif( $pstream eq "monitor" ) {
#               $cpmonitor[$ndt]++;  
              }elsif( $pstream eq "hltgood" ) {
               $cphltgood[$ndt]++;   
              }elsif( $pstream eq "upc" ) {
               $cpupc[$ndt]++;
              }elsif( $pstream eq "W" or $pstream eq "WE" or $pstream eq "WB" ) {
               $cpwb[$ndt]++;
	       }
	    }
	}

##################################################

     }elsif( $srate eq "rtime/cpu" ) {

 $ndate[0] = 0;
 $rcpubin = 0.002; 
 $ndt = 0;

 for ($i = 0; $i < 120; $i++) {

 $ndate[$i] = 0.98 + $rcpubin*$i; 
 }

     foreach $jset (@jbstat) {
	    $pcpu     = ($$jset)->cpuv;
	    $prtime   = ($$jset)->rtmv;
	    $pstream  = ($$jset)->strv;

        if( $pcpu >= 0.001) {             

           $rte = $prtime/$pcpu; 

	   if($rte >= 0.98 and $rte <= 1.22 )     {
          $ndt = int(($rte - 0.98)/$rcpubin + 0.00001);
           $ndate[$ndt] = 0.98 + $rcpubin*$ndt;  

	       if ( $pstream eq "physics" ) {
	       $arphysics[$ndt]++ ;
#              }elsif( $pstream eq "centralpro" ) {
#               $arcentralpro[$ndt]++ ;
	      }elsif( $pstream eq "mtd" ) {
               $armtd[$ndt]++;
#              }elsif( $pstream eq "upsilon" ) {
#               $arupsilon[$ndt]++ ;
#              }elsif( $pstream eq "gamma" ) {
#               $argamma[$ndt]++ ;
              }elsif( $pstream eq "hlt" ) {
               $arhlt[$ndt]++;
              }elsif( $pstream eq "fms" ) {
               $arfmsfast[$ndt]++ ;
#              }elsif( $pstream eq "ht" ) {
#               $arht[$ndt]++ ;
#              }elsif( $pstream eq "atomcules" ) {
#               $aratomcules[$ndt]++ ;
#              }elsif( $pstream eq "monitor" ) {
#               $armonitor[$ndt]++ ;
              }elsif( $pstream eq "hltgood" ) {
               $arhltgood[$ndt]++ ;   
              }elsif( $pstream eq "upc" ) {
               $arupc[$ndt]++;
              }elsif( $pstream eq "W" or $pstream eq "WE" or $pstream eq "WB"  ) {
               $arwb[$ndt]++;
	       }
	    } 
	   }
	}
############
        }
 
   }

    &StDbProdDisconnect();

my @data = ();
my $ylabel;
my $gtitle; 

    my $graph = new GD::Graph::linespoints(750,650);

    if ( ! $graph){
	print STDOUT $qqr->header(-type => 'text/plain');
	print STDOUT "Failed\n";

    } else {
	 
       $legend[0] = "st_physics  ";
       $legend[1] = "st_hlt      ";
#       $legend[3] = "st_ht      ";
#       $legend[4] = "st_monitor ";
       $legend[2] = "st_hltgood  ";
       $legend[3] = "st_mtd      ";
       $legend[4] = "st_upc      ";
       $legend[5] = "st_W        ";
#       $legend[1] = "st_gamma    ";
#       $legend[8] = "st_centralpro ";
#       $legend[9] = "st_atomcules ";
       $legend[6] = "st_fms";
    
       if( $srate eq "cpu" )  {

 @data = ();

 if($qprod eq "P14ia" or $qprod eq "P14ig") {
     $max_y = 14000 ;
 }elsif($qprod eq "P14ii" ) {
     $max_y = 7000 ;
 }elsif($qprod eq "P15ib" ){
     $max_y = 7000 ;
 }elsif($qprod eq "P15ic" or $qprod eq "P15ie" ){
     $max_y = 21000 ;
 }

	$xlabel = "CPU in sec/evt";
        $ylabel = "Number of jobs";
	$gtitle = "CPU in sec/evt for different stream jobs in $qprod production ";



#    @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cphltgood, \@cpupc, \@cpwb, \@cpmtd, \@cpcentralpro, \@cpatomcules, \@cpfmsfast ) ; 

   @data = (\@ndate, \@cpphysics, \@cphlt, \@cphltgood, \@cpmtd, \@cpupc, \@cpwb, \@cpfmsfast ) ; 


      }elsif( $srate eq "rtime/cpu"){

 @data = ();

if($qprod eq "P14ia" ) {
     $max_y = 42000 ;
 }elsif($qprod eq "P14ig" ) {
     $max_y = 42000 ;
 }elsif($qprod eq "P14ii" ) {
     $max_y = 5600 ;
 }elsif($qprod eq "P15ib" ){
     $max_y = 14000 ;
 }elsif($qprod eq "P15ic" or $qprod eq "P15ie" ){
     $max_y = 35000 ;
 }


        $xlabel = "Ratio RealTime/CPU";
        $ylabel = "Number of jobs";
	$gtitle = "Ratios RealTime/CPU for different stream jobs in $qprod production ";

  

#    @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@arhltgood, \@arupc, \@arwb, \@armtd, \@arcentralpro, \@aratomcules, \@arfmsfast ) ;


    @data = (\@ndate, \@arphysics, \@arhlt, \@arhltgood, \@armtd, \@arupc, \@arwb, \@arfmsfast ) ;


     }elsif( $srate eq "exectime"){

 @data = ();


 if($qprod eq "P14ia" ) {
     $max_y = 2800 ;
 }elsif($qprod eq "P14ig" ) {
     $max_y = 14000 ;
 }elsif($qprod eq "P14ii" ) {
     $max_y = 2800 ;
 }elsif($qprod eq "P15ib" ){
     $max_y = 7000 ;
 }elsif($qprod eq "P15ic" or $qprod eq "P15ie"){
     $max_y = 8400 ;
 }else{
     $max_y = 14000 ;
 }

        $xlabel = "Job's execution time on the farm in hours";
        $ylabel = "Number of jobs";         
	$gtitle = "Execution time for different stream jobs in $qprod production ";

  

#    @data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbhltgood, \@jbupc, \@jbwb, \@jbmtd, \@jbcentralpro, \@jbatomcules, \@jbfmsfast ) ;

    @data = (\@ndate, \@jbphysics, \@jbhlt, \@jbhltgood, \@jbmtd, \@jbupc, \@jbwb, \@jbfmsfast ) ;

     }elsif( $srate eq "events"){

 $legend[0] = "all stream data ";

 @data = ();

 if($qprod eq "P14ii" ) {
     $max_y = 84000000 ;
 }else{ 
     $max_y = 42000000 ;
 } 

        $xlabel = "Date of jobs completion";
        $ylabel = "Number of events";         
	$gtitle = "Number of events processed per day in $qprod production ";

# $max_y = int(42000000) ; 

    @data = (\@ndate, \@nevents ) ;


     }elsif( $srate eq "njobs"){

 $legend[0] = "all stream data ";

 @data = ();


 if($qprod eq "P14ia" ) {
     $max_y = 11200 ;
 }elsif($qprod eq "P14ig" ) {
     $max_y = 9800 ;
 }elsif($qprod eq "P14ii" ) {
     $max_y = 11200 ;
 }else{ 
     $max_y = 9800 ;
 } 

        $xlabel = "Date of jobs completion";
        $ylabel = "Number of jobs";         
	$gtitle = "Number of jobs processed per day in $qprod production ";


    @data = (\@ndate, \@numjobs ) ;


     }

 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;
 my $skipnum = 2;
 
 $min_y = 0;

  if (scalar(@ndate) > 60 ) {
     $skipnum = int(scalar(@ndate)/20);
 }

 $xLabelSkip = $skipnum;

	$graph->set(x_label => $xlabel,
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple orange lred lyellow lblack  brown lyellow lpink marine lgray lred) ],
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
          <title>CPU and RealTime production usage</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production  </h1>
     

    </body>
   </html>
END
}
