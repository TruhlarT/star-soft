#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# jobsCpuPlots_bydate.pl to make plots for CPU, realtime/cpu, total time of jobs usage by production date
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


#  $dbhost="duvall.star.bnl.gov";

$dbhost="fc2.star.bnl.gov:3386";
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

my @prodyear = ("2009","2010","2011","2012");


my @arperiod = ( );
my $mstr;
my @arrate = ("rtime/cpu","cpu","jobtottime");

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
my $jbTottime;
my $pryear = "2010";

my %rte = {};
my %nstr = {};

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
my @arcentralpro  = ();
my @arwb = ();

my @ndate = ();
my $ndt = 0;
my @rdays = ();
my $ndy = 0;
my @rvdays = ();

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
my @cpwb = ();

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
my @jbwb = (); 

 my $maxval = 1;
 my $maxcpu = 0;
 my $maxjbtime = 0.1;


#my @arperiod = ("day","week");

 $JobStatusT = "JobStatus2010";  


  &StDbProdConnect();

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


    $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2012-05-10' order by runDay" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

       while( $dy = $cursor->fetchrow() ) {
          $rdays[$ndy] = $dy;
          $ndy++;
       }
    $cursor->finish();


@rvdays = reverse @rdays ;

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);


my $qprod = $query->param('prod');
my $srate = $query->param('prate');
my $qday = $query->param('pday');

if( $qprod eq "" and $qday eq ""  and $srate eq "" ) {

    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production CPU&RealTime usage by individual jobs </u></h1>\n";
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
	                          -default=>P13ib,
      			          -size =>1);

  
   print "<p>";
    print "</td><td>";
    print "<h3 align=center> Stream values: CPU, ratio rtime/CPU <br> or total jobs time on the farm </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
                                  -values=>\@arrate,
                                  -default=>cpu,
                                  -size =>1);


    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Date of production</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pday',
                                  -values=>\@rvdays,
                                  -default=>$nowdate,
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
    
 # Tables

   if( $qprod =~ /P10/ ) {$pryear = "2010"};
   if( $qprod =~ /P11/ ) {$pryear = "2011"};
   if( $qprod =~ /P12/ ) {$pryear = "2012"};
   if( $qprod =~ /P13ib/ ) {$pryear = "2012"};
  
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


    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT WHERE prodSeries = ?  AND runDay = ? order by createTime ";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$qday);

    while($mhr = $cursor->fetchrow() ) {
        $arhr[$nhr] = $mhr;
        $nhr++;
    }

     $cursor->finish();

  #####################

 %rte = {};
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
 @arcentralpro  = ();
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
 @cppmdftp = (); 
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
 @jbpmdftp = ();
 @jbcentralpro  = ();
 @jbwb = ();

   if( $srate eq "jobtottime" ) {

 $ndt = 0;
 @ndate = ();
 @jbstat = ();
 $nstat = 0;

    foreach  $tdate (@arhr) {
 
  $sql="SELECT date_format(createTime, '%Y-%m-%d %H') as PDATE, jobtotalTime, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND jobtotalTime > 0.1  AND submitAttempt = 1 AND jobStatus = 'Done' AND NoEvents >= 10 order by  createTime "; 

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

###########

     foreach $jset (@jbstat) {
	    $phr       = ($$jset)->vday;
            $jbTottime = ($$jset)->jbtot;
	    $pstream   = ($$jset)->strv;

           $ndate[$ndt] = $phr;  

           if ( $jbTottime > $maxjbtime ) {
            $maxjbtime = $jbTottime ;
           }

	   if ( $pstream eq "physics" ) {
	       $jbphysics[$ndt] = $jbTottime;
           }elsif( $pstream eq "centralpro" ) {
               $jbcentralpro[$ndt] = $jbTottime; 
	   }elsif( $pstream eq "mtd" ) {
               $jbmtd[$ndt] = $jbTottime;
           }elsif( $pstream eq "upsilon" ) {
               $jbupsilon[$ndt] = $jbTottime; 
           }elsif( $pstream eq "gamma" ) {
               $jbgamma[$ndt] = $jbTottime; 
           }elsif( $pstream eq "hlt" ) {
               $jbhlt[$ndt] = $jbTottime;  
           }elsif( $pstream eq "fmsfast" ) {
               $jbfmsfast[$ndt] =  $jbTottime; 
           }elsif( $pstream eq "ht" ) {
               $jbht[$ndt] = $jbTottime;  
           }elsif( $pstream eq "atomcules" ) {
               $jbatomcules[$ndt] = $jbTottime; 
           }elsif( $pstream eq "monitor" ) {
               $jbmonitor[$ndt] = $jbTottime;  
#           }elsif( $pstream eq "pmdftp" ) {
#               $jbpmdftp[$ndt] = $jbTottime;   
           }elsif( $pstream eq "upc" ) {
               $jbupc[$ndt] =  $jbTottime;
          }elsif( $pstream eq "W" ) {
               $jbwb[$ndt] =  $jbTottime;
	       }
	    $ndt++;
	    }

###################

   }else{

 $ndt = 0;
 @ndate = ();

 @jbstat = ();
 $nstat = 0;

    foreach  $tdate (@arhr) {

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
  
  }

###########

 $ndt = 0;
 @ndate = ();

     foreach $jset (@jbstat) {
	    $phr     = ($$jset)->vday;
	    $pcpu     = ($$jset)->cpuv;
	    $prtime   = ($$jset)->rtmv;
	    $pstream  = ($$jset)->strv;

        if( $pcpu >= 0.01) {             

           $rte{$pstream,$ndt} = $prtime/$pcpu;
           $ndate[$ndt] = $phr; 
#
           if ( $pcpu > $maxcpu ) {
           $maxcpu = $pcpu; 
	   }
           if ( $rte{$pstream,$ndt} > $maxval ) {
	       $maxval =  $rte{$pstream,$ndt};
	   }

	       if ( $pstream eq "physics" ) {
	       $arphysics[$ndt] =  $rte{$pstream,$ndt};
	       $cpphysics[$ndt] = $pcpu;
              }elsif( $pstream eq "centralpro" ) {
               $arcentralpro[$ndt] =  $rte{$pstream,$ndt};
               $cpcentralpro[$ndt] = $pcpu; 
	      }elsif( $pstream eq "mtd" ) {
               $armtd[$ndt] =  $rte{$pstream,$ndt};
               $cpmtd[$ndt] = $pcpu;
              }elsif( $pstream eq "upsilon" ) {
               $arupsilon[$ndt] =  $rte{$pstream,$ndt};
               $cpupsilon[$ndt] = $pcpu; 
              }elsif( $pstream eq "gamma" ) {
               $argamma[$ndt] =  $rte{$pstream,$ndt};
               $cpgamma[$ndt] = $pcpu; 
              }elsif( $pstream eq "hlt" ) {
               $arhlt[$ndt] =  $rte{$pstream,$ndt};
               $cphlt[$ndt] = $pcpu;  
              }elsif( $pstream eq "fmsfast" ) {
               $arfmsfast[$ndt] =  $rte{$pstream,$ndt};
               $cpfmsfast[$ndt] =  $pcpu; 
              }elsif( $pstream eq "ht" ) {
               $arht[$ndt] =  $rte{$pstream,$ndt};
               $cpht[$ndt] = $pcpu;  
              }elsif( $pstream eq "atomcules" ) {
               $aratomcules[$ndt] =  $rte{$pstream,$ndt};
               $cpatomcules[$ndt] = $pcpu; 
              }elsif( $pstream eq "monitor" ) {
               $armonitor[$ndt] =  $rte{$pstream,$ndt};
               $cpmonitor[$ndt] = $pcpu;  
#              }elsif( $pstream eq "pmdftp" ) {
#               $arpmdftp[$ndt] =  $rte{$pstream,$ndt};
#               $cppmdftp[$ndt] = $pcpu;   
              }elsif( $pstream eq "upc" ) {
               $arupc[$ndt] =  $rte{$pstream,$ndt};
               $cpupc[$ndt] =  $pcpu;
              }elsif( $pstream eq "W" ) {
               $arwb[$ndt] =  $rte{$pstream,$ndt};
               $cpwb[$ndt] =  $pcpu;
	       }
	    $ndt++;
	    }
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
       $legend[1] = "st_gamma    ";
       $legend[2] = "st_hlt      ";
       $legend[3] = "st_ht       ";
       $legend[4] = "st_monitor  ";
       $legend[5] = "st_pmdftp   ";
       $legend[6] = "st_upc      ";
       $legend[7] = "st_W        ";
       $legend[8] = "st_mtd      ";
       $legend[9] = "st_centralpro ";
       $legend[10] = "st_atomcules ";


#       $legend[3] = "st_upsilon   ";
    
       if( $srate eq "cpu" )  {

 @data = ();

	$ylabel = "CPU in sec/evt";
	$gtitle = "CPU in sec/evt for different stream jobs for $qday day";

      $max_y = $maxcpu + 0.2*$maxcpu; 
      $max_y = int($max_y);

    @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpmonitor, \@cppmdftp, \@cpupc, \@cpwb, \@cpmtd, \@cpcentralpro, \@cpatomcules ) ; 

      }elsif( $srate eq "rtime/cpu"){

 @data = ();

        $ylabel = "Ratio RealTime/CPU";
	$gtitle = "Ratios RealTime/CPU for different stream jobs for $qday day";

       $max_y = $maxval + 0.2*$maxval; 
#      $max_y = int($max_y);
  
    @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@armonitor, \@arpmdftp, \@arupc, \@arwb, \@armtd, \@arcentralpro, \@aratomcules ) ;

     }elsif( $srate eq "jobtottime"){

 @data = ();

        $ylabel = "Total jobs time on the farm in hours";
	$gtitle = "Total jobs time on the farm for different stream jobs for $qday day";

       $max_y = $maxjbtime + 0.2*$maxjbtime; 
      $max_y = int($max_y);
  
    @data = (\@ndate, \@jbphysics, \@jbgamma, \@jbhlt, \@jbht, \@jbmonitor, \@jbpmdftp, \@jbupc, \@jbwb, \@jbmtd, \@jbcentralpro, \@jbatomcules ) ;


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

	$graph->set(x_label => "Datetime of job's compeletion",
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange lred lblack marine lbrown lyellow lgray) ],
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
     <h1 align=center>No Data for $qprod production and $qday day </h1>
     

    </body>
   </html>
END
}
