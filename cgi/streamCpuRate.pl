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


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

struct JobAttr => {
      vday      => '$',
      cpuv      => '$',
      rtmv      => '$', 
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
my $mstr;
my @arrate = ("cpu","rate");

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
my @nstpmdftp = ();
my @nstupsilon = ();
my @numstream  = ()

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

    $sql="SELECT DISTINCT runDay  FROM $JobStatusT where runDay >= '2010-08-10' order by runDay" ;

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
    print "<h3 align=center> Select production series</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prod',
	                          -values=>\@arrprod,
	                          -default=>P10ih,
      			          -size =>1);
 
   print "<p>";
    print "</td><td>";
    print "<h3 align=center> Select stream values: <br> CPU or stream rate</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'prate',
	                          -values=>\@arrate,
	                          -default=>cpu,
      			          -size =>1);

    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Select Day of production</h3>";
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


   $sql="SELECT DISTINCT  date_format(createTime, '%Y-%m-%d %H') as PDATE  FROM $JobStatusT  where prodSeries = ? and runDay = ? order by PDATE ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qday);

       while( $mhr = $cursor->fetchrow() ) {

          $arhr[$nhr] = $mhr;
          $nhr++;
       }
    $cursor->finish();


 $ndt = 0;

 #####################

 %rte = {};
 %nstr = {};
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
 @rtpmdftp = ();
 @rtupsilon = ();


  my $maxvalue = 1;

    foreach my $tdate (@arhr) {
	@jbstat = ();  
	$nstat = 0;

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
 

     foreach $jset (@jbstat) {
	    $pday     = ($$jset)->vday;
	    $pcpu     = ($$jset)->cpuv;
	    $prtime   = ($$jset)->rtmv;
	    $pstream  = ($$jset)->strv;

    if( $pcpu >= 0.001) {             

        $rte{$pstream,$ndt} = $rte{$pstream,$ndt} + $prtime/$pcpu;
        $nstr{$pstream,$ndt}++;
         
            $ndate[$ndt] = $pday;    

	    }
	  }
####################        

          foreach my $mfile (@arstream) {      
              if ($nstr{$mfile,$ndt} >= 0.1) {
                  $rte{$mfile,$ndt} = $rte{$mfile,$ndt}/$nstr{$mfile,$ndt};
                  if ( $rte{$mfile,$ndt} > $maxval ) {
                $maxval =  $rte{$mfile,$ndt}
	        }
		  if ( $mfile eq "physics" ) {
	       $arphysics[$ndt] =  $rte{$mfile,$ndt};
 	       $nstphysics[$ndt] =  $nstr{$mfile,$ndt};              
	      }elsif( $mfile eq "mtd" ) {
               $armtd[$ndt] =  $rte{$mfile,$ndt};
               $nstmtd[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $arupsilon[$ndt] =  $rte{$mfile,$ndt};
               $nstupsilon[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $argamma[$ndt] =  $rte{$mfile,$ndt};
               $nstgamma[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $arhlt[$ndt] =  $rte{$mfile,$ndt};
               $nsthlt[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "fmsfast" ) {
               $arfmsfast[$ndt] =  $rte{$mfile,$ndt};
               $nstfmsfast[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "ht" ) {
               $arht[$ndt] =  $rte{$mfile,$ndt};
               $nstht[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "atomcules" ) {
               $aratomcules[$ndt] =  $rte{$mfile,$ndt};
               $nstatomcules[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "monitor" ) {
               $armonitor[$ndt] =  $rte{$mfile,$ndt};
               $nstmonitor[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "pmdftp" ) {
               $arpmdftp[$ndt] =  $rte{$mfile,$ndt};
               $nstpmdftp[$ndt] =  $nstr{$mfile,$ndt};
              }elsif( $mfile eq "upc" ) {
               $arupc[$ndt] =  $rte{$mfile,$ndt};
               $nstupc[$ndt] =  $nstr{$mfile,$ndt};
	       }
              }
          }

        $ndt++;

    } # foreach tdate

      for($ii = 0; $ii < $ndt; $ii++) {
	  $numstream[$ii] = $nstphysics[$ii]+$nstmtd[$ii]+$nsthlt[$ii]+$nstht[$ii]+$nstmonitor[$ii]+$nstpmdftp[$ii]+ $nstupc[$ii];

     if ($numstream[$ii] >= 1) { 
      $rtphysics[$ii] = $nstphysics[$ii]/$numstream[$ii];
      $rtmtd[$ii] = $nstmtd[$ii]/$numstream[$ii];
      $rthlt[$ii] = $nsthlt[$ii]/$numstream[$ii];
      $rtht[$ii] = $nstht[$ii]/$numstream[$ii];
      $rtmonitor[$ii] = $nstmonitor[$ii]/$numstream[$ii];
      $rtpmdftp[$ii] = $nstpmdftp[$ii]/$numstream[$ii];
      $rtupc[$ii] = $nstupc[$ii]/$numstream[$ii];

  }
#      if ($nstphysics[$ii] >= 1) {
      
#      $rtmtd[$ii] = $nstmtd[$ii]/$nstphysics[$ii];
#      $rthlt[$ii] = $nsthlt[$ii]/$nstphysics[$ii];
#      $rtht[$ii] = $nstht[$ii]/$nstphysics[$ii];
#      $rtmonitor[$ii] = $nstmonitor[$ii]/$nstphysics[$ii];
#      $rtpmdftp[$ii] = $nstpmdftp[$ii]/$nstphysics[$ii];
#      $rtupc[$ii] = $nstupc[$ii]/$nstphysics[$ii];
#      $rtfmsfast[$ii] = $nstfmsfast[$ii]/$nstphysics[$ii];
#      $rtatomcules[$ii] = $nstatomcules[$ii]/$nstphysics[$ii];
#     }

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
       $legend[1] = "st_mtd       ";
       $legend[2] = "st_hlt       ";
       $legend[3] = "st_ht        ";
       $legend[4] = "st_monitor   ";
       $legend[5] = "st_pmdftp    ";

       if ( $srate eq "cpu" ) {

       $ylabel = "Average ratio RealTime/CPU per hour";
       $gtitle = "Average ratio RealTime/CPU per hour for different stream data";

  @data = (\@ndate, \@arphysics, \@armtd, \@arhlt, \@arht, \@armonitor, \@arpmdftp ) ;

  	$max_y = $maxval + 0.2*$maxval; 
 
  }elsif(  $srate eq "rate" ) {

	$ylabel = "Ratio of different stream data to st_physics per hour ";
	$gtitle = "Ratio of different stream data to st_physics per hour for day $qday ";

 @data = (\@ndate, \@rtmtd, \@rthlt, \@rtht, \@rtmonitor, \@rtpmdftp ) ;

       	$max_y = 2.0;
     
    }

	my $xLabelsVertical = 1;
	my $xLabelPosition = 0;
	my $xLabelSkip = 1;
	my $skipnum = 1;
 

	$min_y = 0;
#	$max_y = $maxval + 0.2*$maxval; 

	if (scalar(@ndate) >= 40 ) {
	    $skipnum = int(scalar(@ndate)/20);
	}

	$xLabelSkip = $skipnum;

	$graph->set(x_label => "Date of Production",
	            y_label => $ylabel,
                    title   => $gtitle,
                    y_tick_number => 14,
                    x_label_position => 0.5,
                    y_min_value => $min_y,
                    y_max_value => $max_y,
                    y_number_format => \&y_format,
	            #labelclr => "lblack",
                    titleclr => "lblack",
                    dclrs => [ qw(lblue lgreen lpurple lorange lred lblack) ],
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
     <h1 align=center>No Data for $qprod and $qday </h1>
     

    </body>
   </html>
END
}
