#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# jobCpuAllNodes.pl to make plots for average RealTime/CPU job's usage for stream data for all nodes 
#
#####################################################################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;
#use Mysql;
use Class::Struct;

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      cpuv      => '$',
      rtmv      => '$', 
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

my @prodyear = ("2010","2011","2012","2013");
my @arval = ("rtime/cpu","cpu");
my @arnode = ("rcrs","rcas");
my @arcrs = ();
my @arcas = ();


my @arrprod = ();
my @arstream = ();
my @ardays = ();
my @rvdays = ();
my $ndy = 0;
my $nday = ();
my $nst = 0;
my $str;
my $pday;
my $npr = 0;
my $pcpu;
my $prtime;
my $pstream;
my $pryear = "2013";
my $dy;
my $mpr;

my %rte = {};
my %nstr = {};
my %arcpu = {};

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
my @arwb  = ();

my @ndate = ();
my $ndt = 0;
my $nn = 0;
my $ni = 0;
my $dnode;
my $mnode;

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
my @nstcentralpro = ();
my @nstwb = (); 

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
my @rtcentralpro = ();
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
my @cppmdftp = ();
my @cpcentralpro = ();
my @cpwb = ();

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
          $ardays[$ndy] = $dy;
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
          $ardays[$ndy] = $dy;
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
          $ardays[$ndy] = $dy;
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
          $ardays[$ndy] = $dy;
          $ndy++;
       }
    $cursor->finish();


  @rvdays = reverse @ardays ;

&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qprod   = $query->param('prod');
my $qday    = $query->param('pday');
my $qvalue  = $query->param('pvalue');
my $qnode   = $query->param('pnode');


if( $qvalue eq "" and $qprod eq "" and $qnode  eq "" and $qday eq "" ) {

    print $query->header();
    print $query->start_html('Production CPU usage');
    print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
    print $query->startform(-action=>"$scriptname");

    print "<body bgcolor=\"cornsilk\">\n";
    print "<h1 align=center><u>Production CPU&RealTime usage on every node</u></h1>\n";
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
	                          -default=>P14ia,
      			          -size =>1);
 
    
    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Node type <br> </h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pnode',
                                  -values=>\@arnode,
                                  -size =>1);


    print "<p>";
    print "</td><td>";
    print "<h3 align=center> Production date <br> </h3>";
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
    print "<table align=center>";
    print "<tr ALIGN=center>";
    print "<td>";  
    print "<h3 align=center> Stream values: <br> CPU & rtime/CPU</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'pvalue',
	                          -values=>\@arval,
      			          -size =>1);

    print "<p>";
    print "</td><td>";
    print "</td> </tr> </table><center>";

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
my $qday    = $qqr->param('pday');
my $qvalue  = $qqr->param('pvalue');
my $qnode   = $qqr->param('pnode');

 if( $qprod =~ /P10/ ) {$pryear = "2010"};
 if( $qprod =~ /P11/ ) {$pryear = "2011"};
 if( $qprod =~ /P12/ ) {$pryear = "2012"};
 if( $qprod =~ /P13ib/ ) {$pryear = "2012"};
 if( $qprod =~ /P14ia/ ) {$pryear = "2013"};

  $JobStatusT = "JobStatus".$pryear;

  my @jbstat = ();  
  my $nstat = 0;
  my $jset;

 &StDbProdConnect();

 %rte = {};
 %nstr = {};
 %arcpu = {};

  my $maxval = 1.0;
  my $maxcpu = 0;
 
##################################### cpu, rtime/cpu

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
 @rtpmdftp = ();
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
 @cppmdftp = ();
 @cpcentralpro = ();
 @cpwb = ();

############################# 

 $ndt = 0;
 @ndate = ();

     if($qnode eq "rcrs" ) {

   $sql="SELECT DISTINCT nodeID  FROM $JobStatusT where nodeID like ' rcrs6%' and runDay = ? order by nodeID" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qday);

       while( $dy = $cursor->fetchrow() ) {
          $arcrs[$ni] = $dy;
          $ni++;
       }
 
   $cursor->finish();

#####################################################

   }elsif($qnode eq "rcas" ) {

   $sql="SELECT DISTINCT nodeID  FROM $JobStatusT where nodeID like ' rcas6%' and runDay = ? order by nodeID" ;

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qday);

       while( $dy = $cursor->fetchrow() ) {
          $arcrs[$ni] = $dy;
          $ni++;
       }
 
   $cursor->finish();

   }

    foreach $mnode (@arcrs) {

 @arstream = ();
 $nst = 0;

 @jbstat = ();
 $nstat = 0;

  $sql="SELECT  CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE  runDay = ? AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 and nodeID = '$mnode' and jobStatus = 'Done' AND NoEvents >= 10 ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute($qday,$qprod);

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

     foreach $jset (@jbstat) {
            $pcpu    = ($$jset)->cpuv;
            $prtime  = ($$jset)->rtmv;
            $pstream = ($$jset)->strv;

    if( $pcpu >= 0.001) {

        $rte{$pstream,$ndt} += $prtime/$pcpu;
        $arcpu{$pstream,$ndt} += $pcpu;
        $nstr{$pstream,$ndt}++;

            }
          }

        $dnode = $mnode;
        $dnode = substr($dnode,0,-13);

        $ndate[$ndt] = $dnode;  
       
####################


      $sql="SELECT DISTINCT streamName  FROM $JobStatusT where prodSeries = ? and runDay = ? and nodeID = '$mnode'";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qday);

       while( $str = $cursor->fetchrow() ) {
          $arstream[$nst] = $str;
          $nst++;
       }
    $cursor->finish();

###################

          foreach my $mfile (@arstream) {
              if ($nstr{$mfile,$ndt} >= 2 ) {
                  $arcpu{$mfile,$ndt} = $arcpu{$mfile,$ndt}/$nstr{$mfile,$ndt};
                  $rte{$mfile,$ndt} = $rte{$mfile,$ndt}/$nstr{$mfile,$ndt};
                  if ( $rte{$mfile,$ndt} > $maxval ) {
		      $maxval =  $rte{$mfile,$ndt};
                 }
                  if ( $arcpu{$mfile,$ndt} > $maxcpu ) {
                      $maxcpu = $arcpu{$mfile,$ndt} ;
                  }
                  if ( $mfile eq "physics" ) {
               $arphysics[$ndt] = $rte{$mfile,$ndt};
               $cpphysics[$ndt] = $arcpu{$mfile,$ndt};
              }elsif( $mfile eq "centralpro" ) {
               $arcentralpro[$ndt] = $rte{$mfile,$ndt};
               $cpcentralpro[$ndt] = $arcpu{$mfile,$ndt};
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
#              }elsif( $mfile eq "pmdftp" ) {
#               $arpmdftp[$ndt] = $rte{$mfile,$ndt};
#               $cppmdftp[$ndt] = $arcpu{$mfile,$ndt};
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

    } # foreach $mnode

#  }

############################################################################

    &StDbProdDisconnect();

 my $ylabel;
 my $gtitle; 
 my @data = ();
 my $max_y;
 my $min_y;

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
       $legend[7] = "st_W         ";
       $legend[8] = "st_mtd       ";
       $legend[9] = "st_centralpro ";
       $legend[10] = "st_atomcules ";
       $legend[11] = "st_fms ";


       if ( $qvalue eq "rtime/cpu" ) {

       $ylabel = "Average ratio RealTime/CPU per day";
       $gtitle = "Ratio RealTime/CPU for different streams on $qnode nodes for day $qday";

    @data = ();

  @data = (\@ndate, \@arphysics, \@argamma, \@arhlt, \@arht, \@armonitor, \@arpmdftp, \@arupc, \@arwb, \@armtd, \@arcentralpro, \@aratomcules, \@arfmsfast ) ;

  	$max_y = 1.2*$maxval; 

  }elsif(  $qvalue eq "cpu" ) {

       $ylabel = "Average CPU in sec/evt per day";
       $gtitle = "CPU in sec/evt for different streams on $qnode nodes for day $qday ";

    @data = ();

  @data = (\@ndate, \@cpphysics, \@cpgamma, \@cphlt, \@cpht, \@cpmonitor, \@cppmdftp, \@cpupc, \@cpwb, \@cpmtd, \@cpcentralpro, \@cpatomcules, \@cpfmsfast ) ;

    	$max_y = 1.2*$maxcpu; 
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

	$graph->set(x_label => "Node's name",
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange lred marine lblack lbrown lyellow lgray lred) ],
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
     <h1 align=center>No Data for $qprod production on $qnode nodes for $qday </h1>
     

    </body>
   </html>
END
}
