#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# streamCpuRate.pl to make plots of average CPU, RealTime/CPU, total time of job's usage and stream rate by production date 
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

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      vday      => '$',
      cpuv      => '$',
      rtmv      => '$', 
      strk      => '$',
      jbtot     => '$', 
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

my @prodyear = ("2010","2011","2012","2013","2014","2015");


my @arperiod = ( );
my $mstr;
#my @arrate = ("cpu","rtime/cpu","jobtotalTime","ntracks","stream_rate","njobs");

my @arrate = ("cpu","rtime/cpu","ntracks","stream_rate","njobs");

my @arrprod = ();
my @arstream = ();
my @ardays = ();
my $ndy = 0;
my $nst = 0;
my $str;
my $npr = 0;
my $mpr;
my $pday;
my $pcpu;
my $prtime;
my $pstream;
my $ptrack;
my $jbTottime;
my $pryear = "2014";

my %rte = {};
my %nstr = {};
my %arcpu = {};
my %artrk = {};
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
my @arhltgood = ();
my @arcentralpro = ();
my @arwb = ();

my @ndate = ();
my $ndt = 0;
my @rdays = ();
my $ndy = 0;
my @rvdays = ();

my @nstphysics = ();
my @nstgamma = ();
my @nstmtd = ();
my @nsthlt = ();
my @nstfmsfast = ();
my @nstht = ();
my @nstatomcules = ();
my @nstupc = ();
my @nstmonitor = ();
my @nsthltgood = ();
my @nstupsilon = ();
my @nstcentralpro  = ();
my @numstream  = ();
my @nstwb = ();

my @rtgamma = ();
my @rtmtd = ();
my @rthlt = ();
my @rtfmsfast = ();
my @rtht = ();
my @rtatomcules = ();
my @rtupc = ();
my @rtmonitor = ();
my @rthltgood = ();
my @rtupsilon = ();
my @rtphysics = ();
my @rtcentralpro  = ();
my @rtwb = ();

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
my @cpwb = ();

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
my @trhltgood = ();
my @trcentralpro  = ();
my @trwb  = ();

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

my @arhr = ();
my $mhr = 0;
my $nhr = 0;

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

  $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2010-07-20' order by runDay" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
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
 
   $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2011-06-01' order by runDay" ;


      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
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

    $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2012-05-20' order by runDay" ;


      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
       }
    $cursor->finish();


$JobStatusT = "JobStatus2013";


    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();


    $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2014-02-20' order by runDay" ;


      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
       }
    $cursor->finish();


$JobStatusT = "JobStatus2014";


    $sql="SELECT DISTINCT prodSeries  FROM $JobStatusT ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

      while( $mpr = $cursor->fetchrow() ) {
          $arrprod[$npr] = $mpr;
          $npr++;
       }
    $cursor->finish();


    $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2015-01-09' order by runDay" ;


      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
       }
#    $cursor->finish();



@rvdays = reverse @rdays ;

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qprod = $query->param('prod');
my $qday = $query->param('pday');
my $srate = $query->param('prate');


if( $qday eq "" and $qprod eq "" and $srate eq "" ) {
    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production CPU&RealTime usage for stream data</u></h1>\n";
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
	                          -default=>P14ii,
      			          -size =>1);
 
   print "<p>";
    print "</td><td>";
    print "<h3 align=center> Stream values: <br> CPU, rtime/CPU,<br>avg number of tracks, <br>stream jobs ratios by finish time,<br>number of finished jobs</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
	                          -values=>\@arrate,
	                          -default=>cpu,
      			          -size =>1);

    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Date of production<br></h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pday',
                                  -values=>\@rvdays,
                                  -default=>\$nowdate,
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
    my $qday = $qqr->param('pday');
    my $srate = $qqr->param('prate');
 
  if( $qprod =~ /P10/ ) {$pryear = "2010"};
  if( $qprod =~ /P11/ ) {$pryear = "2011"};
  if( $qprod =~ /P12/ ) {$pryear = "2012"};
  if( $qprod =~ /P13ib/ ) {$pryear = "2012"};
  if( $qprod =~ /P14ia/ ) {$pryear = "2013"};
  if( $qprod =~ /P14ig/ ) {$pryear = "2013"};
  if( $qprod =~ /P14ii/ ) {$pryear = "2014"};

   
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


   $sql="SELECT DISTINCT  date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT  where prodSeries = ? and runDay = ? order by createTime ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qday);

       while( $mhr = $cursor->fetchrow() ) {

          $arhr[$nhr] = $mhr;
          $nhr++;
       }
    $cursor->finish();

 #####################

 %rte = {};
 %nstr = {};
 %arcpu = {};
 %artrk = {};

  my $maxval = 1;
  my $maxcpu = 0;
  my $maxjbtime = 0.1;
  my $maxtrk = 1.0;
 
 @ndate = ();
 $ndt = 0;

 if( $srate eq "jobtotalTime" ) {

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
 @jbhltgood = ();
 @jbcentralpro  = ();
 @jbwb = ();

 @ndate = ();
 $ndt = 0;

   foreach my $tdate (@arhr) {
	@jbstat = ();  
	$nstat = 0;

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, jobtotalTime, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND jobtotalTime > 0.1 AND jobStatus = 'Done' AND NoEvents >= 10  order by createTime";

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
           }elsif( $mfile eq "centralpro" ) {
               $jbcentralpro[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "mtd" ) {
               $jbmtd[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "upsilon" ) {
               $jbupsilon[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "gamma" ) {
               $jbgamma[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "hlt" ) {
               $jbhlt[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "fms" ) {
               $jbfmsfast[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "ht" ) {
               $jbht[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "atomcules" ) {
               $jbatomcules[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "monitor" ) {
               $jbmonitor[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "hltgood" ) {
               $jbhltgood[$ndt] = $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "upc" ) {
               $jbupc[$ndt] =  $arjbtime{$mfile,$ndt};
            }elsif( $mfile eq "W" or $mfile eq "WB" or $mfile eq "WE") {
               $jbwb[$ndt] =  $arjbtime{$mfile,$ndt};

           }else{
             next;
           }
            }
          }

        $ndt++;

   } # foreach tdate

##################################### cpu, rtime/cpu

   }elsif( $srate eq "cpu" or $srate eq "rtime/cpu"  ) {

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
 @arhltgood = ();
 @arcentralpro = ();
 @arwb = ();

 @rtphysics = ();
 @rtgamma = ();
 @rtmtd = ();
 @rthlt = ();
 @rtfmsfast = ();
 @rtht = ();
 @rtatomcules = ();
 @rtupc = ();
 @rtmonitor = ();
 @rthltgood = ();
 @rtupsilon = ();
 @rtcentralpro = ();
 @rtwb = ();

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
 @cpcentralpro = ();
 @cpwb = ();


    foreach my $tdate (@arhr) {
        @jbstat = ();
        $nstat = 0;

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 and jobStatus = 'Done' AND NoEvents >= 10 order by createTime ";

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
              }elsif( $mfile eq "centralpro" ) {
               $arcentralpro[$ndt] = $rte{$mfile,$ndt};
               $cpcentralpro[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $arupsilon[$ndt] = $rte{$mfile,$ndt};
               $cpupsilon[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $argamma[$ndt] = $rte{$mfile,$ndt};
               $cpgamma[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $arhlt[$ndt] = $rte{$mfile,$ndt};
               $cphlt[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "fms" ) {
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
              }elsif( $mfile eq "hltgood" ) {
               $arhltgood[$ndt] = $rte{$mfile,$ndt};
               $cphltgood[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $arupc[$ndt] =  $rte{$mfile,$ndt};
               $cpupc[$ndt] =  $arcpu{$mfile,$ndt};
             }elsif( $mfile eq "W" or $mfile eq "WB" or $mfile eq "WE" ) {
               $arwb[$ndt] =  $rte{$mfile,$ndt};
               $cpwb[$ndt] =  $arcpu{$mfile,$ndt};

               }
              }
          }

        $ndt++;

    } # foreach tdate

######################################  average number of tracks

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
 @trhltgood = ();
 @trcentralpro = ();
 @trwb = ();
 @ndate = ();
 $ndt = 0;
 $maxtrk = 1.0;

   foreach my $tdate (@arhr) {
	@jbstat = ();  
	$nstat = 0;

  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, avg_no_tracks, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? and avg_no_tracks >= 1 AND jobStatus = 'Done' AND NoEvents >= 10 order by createTime ";

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
                ($$fObjAdr)->strk($fvalue)   if( $fname eq 'avg_no_tracks');
                ($$fObjAdr)->strv($fvalue)    if( $fname eq 'streamName');

            }
            $jbstat[$nstat] = $fObjAdr;
            $nstat++;
        }


     foreach $jset (@jbstat) {
           $pday      = ($$jset)->vday;
           $ptrack   = ($$jset)->strk;
           $pstream   = ($$jset)->strv;

           $artrk{$pstream,$ndt} = $artrk{$pstream,$ndt} + $ptrack;
           $nstr{$pstream,$ndt}++;
           $ndate[$ndt] = $pday;
          }

          foreach my $mfile (@arstream) {
             if ($nstr{$mfile,$ndt} >= 2 ) {
             $artrk{$mfile,$ndt} = $artrk{$mfile,$ndt}/$nstr{$mfile,$ndt};

             if ( $artrk{$mfile,$ndt} > $maxtrk ) {
             $maxtrk =  $artrk{$mfile,$ndt}
               }

                  if ( $mfile eq "physics" ) {
               $trphysics[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "mtd" ) {
               $trmtd[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $trcentralpro[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $trupsilon[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $trgamma[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $trhlt[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "fms" ) {
               $trfmsfast[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $trht[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $tratomcules[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $trmonitor[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "hltgood" ) {
               $trhltgood[$ndt] = $artrk{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $trupc[$ndt] =  $artrk{$mfile,$ndt};
             }elsif( $mfile eq "W" or $mfile eq "WB" or $mfile eq "WE" ) {
               $trwb[$ndt] =  $artrk{$mfile,$ndt};

           }else{
             next;
           }
            }
          }

        $ndt++;

   } # foreach tdate


#######################################  number of finished stream jobs

 }elsif( $srate eq "njobs" or $srate eq "stream_rate"){

 @ndate = ();
 $ndt = 0;

 @nstphysics = ();
 @nstgamma = ();
 @nstmtd = ();
 @nsthlt = ();
 @nstfmsfast = ();
 @nstht = ();
 @nstatomcules = ();
 @nstupc = ();
 @nstmonitor = ();
 @nsthltgood = ();
 @nstupsilon = ();
 @nstcentralpro = ();
 @nstwb = ();

 @numstream = ();

 @rtphysics = ();
 @rtgamma = ();
 @rtmtd = ();
 @rthlt = ();
 @rtfmsfast = ();
 @rtht = ();
 @rtatomcules = ();
 @rtupc = ();
 @rtmonitor = ();
 @rthltgood = ();
 @rtupsilon = ();
 @rtcentralpro = ();
 @rtwb = ();

    foreach my $tdate (@arhr) {
	@jbstat = ();  
	$nstat = 0;

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
 

     foreach $jset (@jbstat) {
	    $pday     = ($$jset)->vday;
	    $pstream  = ($$jset)->strv;

           $nstr{$pstream,$ndt}++;
           $ndate[$ndt] = $pday;    

	  }
####################        

          foreach my $mfile (@arstream) {      

		  if ( $mfile eq "physics" ) {
               $nstphysics[$ndt] = $nstr{$mfile,$ndt};
	      }elsif( $mfile eq "mtd" ) {
               $nstmtd[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $nstcentralpro[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $nstupsilon[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $nstgamma[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $nsthlt[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "fms" ) {
               $nstfmsfast[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $nstht[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $nstatomcules[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $nstmonitor[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "hltgood" ) {
               $nsthltgood[$ndt] = $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $nstupc[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "W" or $mfile eq "WB" or $mfile eq "WE" ) {
               $nstwb[$ndt] =  $nstr{$mfile,$ndt};
	       }
             }

        $ndt++;

    } # foreach tdate

      for($ii = 0; $ii < $ndt; $ii++) {
      $numstream[$ii] = $nstphysics[$ii]+$nstcentralpro[$ii]+$nstmtd[$ii]+$nsthlt[$ii]+$nstht[$ii]+$nstmonitor[$ii]+$nstupc[$ii]+ $nstgamma[$ii]+  $nstatomcules[$ii]+ $nstupsilon[$ii] + $nstwb[$ii] + $nstfmsfast[$ii];

     if ($numstream[$ii] >= 1) {
      $rtphysics[$ii] = $nstphysics[$ii]/$numstream[$ii];
      $rtcentralpro[$ii] = $nstcentralpro[$ii]/$numstream[$ii];
      $rtmtd[$ii] = $nstmtd[$ii]/$numstream[$ii];
      $rthlt[$ii] = $nsthlt[$ii]/$numstream[$ii];
      $rtht[$ii] = $nstht[$ii]/$numstream[$ii];
      $rtmonitor[$ii] = $nstmonitor[$ii]/$numstream[$ii];
      $rthltgood[$ii] = $nsthltgood[$ii]/$numstream[$ii];
      $rtupc[$ii] = $nstupc[$ii]/$numstream[$ii];
      $rtupsilon[$ii] = $nstupsilon[$ii]/$numstream[$ii];
      $rtgamma[$ii] = $nstgamma[$ii]/$numstream[$ii];
      $rtfmsfast[$ii] = $nstfmsfast[$ii]/$numstream[$ii];
      $rtatomcules[$ii] = $nstatomcules[$ii]/$numstream[$ii];
      $rtwb[$ii] = $nstwb[$ii]/$numstream[$ii];

       }
  }
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
#       $legend[4] = "st_monitor   ";
       $legend[4] = "st_W    ";
       $legend[5] = "st_upc       ";
       $legend[6] = "st_atomcules ";
       $legend[7] = "st_mtd       ";
       $legend[8] = "st_centralpro";
       $legend[9] = "st_fms";
       $legend[10] = "st_hltgood";

       if ( $srate eq "rtime/cpu" ) {

       $ylabel = "Average ratio RealTime/CPU per hour";
       $gtitle = "Average ratio RealTime/CPU for different streams for day $qday";

    @data = ();

#  @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@armonitor, \@arwb, \@arupc, \@aratomcules, \@armtd, \@arcentralpro, \@arfmsfast ) ;


  @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@arwb, \@arupc, \@aratomcules, \@armtd, \@arcentralpro, \@arfmsfast, \@arhltgood ) ;

  	$max_y = $maxval + 0.2*$maxval; 
#        $max_y = int($max_y);

  }elsif(  $srate eq "cpu" ) {

       $ylabel = "Average CPU in sec/evt per hour";
       $gtitle = "Average CPU in sec/evt for different streams for day $qday";

    @data = ();

#  @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpmonitor, \@cpwb, \@cpupc, \@cpatomcules, \@cpmtd, \@cpcentralpro, \@cpfmsfast ) ;

 @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpwb, \@cpupc, \@cpatomcules, \@cpmtd, \@cpcentralpro, \@cpfmsfast, \@cphltgood ) ;

    	$max_y = $maxcpu + 0.2*$maxcpu; 
        $max_y = int($max_y);

  }elsif(  $srate eq "jobtotalTime" ) {

    @data = ();

   $ylabel = "Average total time jobs stay on the farm in hours";
   $gtitle = "Average total time jobs stay on the farm  for $qday ";

#@data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbmonitor, \@jbwb, \@jbupc, \@jbatomcules, \@jbmtd, \@jbcentralpro, \@jbfmsfast ) ;

@data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbwb, \@jbupc, \@jbatomcules, \@jbmtd, \@jbcentralpro, \@jbfmsfast, \@jbhltgood ) ;

  $max_y = $maxjbtime + 0.2*$maxjbtime;
  $max_y = int($max_y);

     
 }elsif(  $srate eq "ntracks" ) {

	$ylabel = "Average number of tracks in different streams";
	$gtitle = "Average number of tracks in different streams for day $qday ";

   @data = ();

# @data = (\@ndate, \@trphysics, \@trgamma, \@trhlt, \@trht, \@trmonitor, \@trwb, \@trupc, \@tratomcules, \@trmtd, \@trcentralpro, \@trfmsfast ) ;


 @data = (\@ndate, \@trphysics, \@trgamma, \@trhlt, \@trht, \@trwb, \@trupc, \@tratomcules, \@trmtd, \@trcentralpro, \@trfmsfast, \@trhltgood ) ;
  
      $max_y = $maxtrk + 0.2*$maxtrk;
      $max_y = int($max_y);
   
  }elsif(  $srate eq "njobs" ) {

        $ylabel = "Number of stream jobs finished per hour ";
        $gtitle = "Number of stream jobs finished per hour for day $qday ";

    @data = ();

# @data = (\@ndate, \@nstphysics, \@nstgamma, \@nsthlt, \@nstht, \@nstmonitor, \@nstwb, \@nstupc, \@nstatomcules, \@nstmtd, \@nstcentralpro, \@nstfmsfast ) ;

 @data = (\@ndate, \@nstphysics, \@nstgamma, \@nsthlt, \@nstht, \@nstwb, \@nstupc, \@nstatomcules, \@nstmtd, \@nstcentralpro, \@nstfmsfast, \@nsthltgood ) ;


  }elsif(  $srate eq "stream_rate" ) {

        $ylabel = "Ratio of different stream jobs finishing per hour ";
        $gtitle = "Ratio of different stream jobs finishing per hour for day $qday ";

 @data = ();

# @data = (\@ndate, \@rtphysics, \@rtgamma, \@rthlt, \@rtht, \@rtwb, \@rtupc, \@rtatomcules, \@rtmtd, \@rtcentralpro, \@rtfmsfast ) ;

 @data = (\@ndate, \@rtphysics, \@rtgamma, \@rthlt, \@rtht, \@rtmonitor, \@rtwb, \@rtupc, \@rtatomcules, \@rtmtd, \@rtcentralpro, \@rtfmsfast, \@rthltgood ) ;

        $max_y = 1.2;
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
                    dclrs => [ qw(lblue lgreen lpurple lorange lred lblack marine lyellow lbrown lgray lred) ],
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
          <title>Ratio of different stream  data</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center>No Data for $qprod production and $qday day </h1>
     

    </body>
   </html>
END
}
