#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# gridEffiPlots.pl to make grid production efficicency plots
#
##########################################################


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

 $JobStatusT = "JobStatus2009";

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

my $nowdate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my @prodyear = ("2009","2010");

my @arperiod = ( );
my $mstr;

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

my %rte = {};
my %nstr = {};
my @arupsilon = ();
my @armtd = ();
my @arphysics = ();
my @argamma = ();
my @arhlt = ();
my @ndate = ();
my $ndt = 0;

$JobStatusT = "JobStatus2009";
 
my @arperiod = ("week","1_month","2_months","3_months","6_months","12_months");

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


&StDbProdDisconnect();

my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

my $qprod  = $query->param('prod');
my $qperiod = $query->param('period');


if( $qperiod eq "" and $pryear eq "" ) {
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
    print "<h3 align=center> Select year</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'ryear',
	                          -values=>\@arrprod,
	                          -default=>P10ic,
      			          -size =>1);

    print "<p>";
    print "</td><td>";  
    print "<h3 align=center> Period of monitoring</h3>";
    print "<h4 align=center>";
    print  $query->scrolling_list(-name=>'period',
                                  -values=>\@arperiod,
                                  -default=>week,
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

 } else {
    
     my $qqr = new CGI;

    my $qprod = $qqr->param('prod');
    my $qperiod = $qqr->param('period');
 
    
 # Tables

 #   $JobStatusT = "JobStatus".$pryear;

  my $day_diff = 0;
  my $nmonth = 0;
  my @prt = ();
  my $myday;
  my $nday = 0;
  my @ardays = ();
  my $tdate;
  my @jbstat = ();  
  my $nstat = 0;


     @arstream = ();


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


    $sql="SELECT DISTINCT date_format(createTime, '%Y-%m-%d') AS PDATE  FROM $JobStatusT WHERE prodSeries = ? AND (TO_DAYS(\"$nowdate\") - TO_DAYS(createTime)) < ?  order by PDATE";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute($qprod,$day_diff);

    while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
    }


 $ndt = 0;
 my $jset;

    #####################


 %rte = {};
 %nstr = {};
 @arupsilon = ();
 @armtd = ();
 @arphysics = ();
 @argamma = ();
 @arhlt = ();
 @ndate = ();
 

    foreach  $tdate (@ardays) {
	@jbstat = ();  
	$nstat = 0;

   $sql="SELECT date_format(createTime, '%Y-%m-%d') AS PDATE, CPU_per_evt_sec, RealTime_per_evt, streamName FROM $JobStatusT WHERE  createTime like '$tdate%' AND prodSeries = ? AND CPU_per_evt_sec > 0.01 AND RealTime_per_evt > 0.01 "; 

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

    if( $pcpu >= 0.01) {             

        $rte{$pstream,$ndt} = $rte{$pstream,$ndt} + $prtime/$pcpu;
        $nstr{$pstream,$ndt}++;
         
            $ndate[$ndt] = $pday;    

	    }
	  }
####################        

          foreach my $mfile (@arstream) {      
              if ($nstr{$mfile,$ndt} >= 0.01) {
                  $rte{$mfile,$ndt} = $rte{$mfile,$ndt}/$nstr{$mfile,$ndt};
		  if ( $mfile eq "physics" ) {
	       $arphysics[$ndt] =  $rte{$mfile,$ndt};
	      }elsif( $mfile eq "mtd" ) {
               $armtd[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "upsilon" ) {
               $arupsilon[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "gamma" ) {
               $argamma[$ndt] =  $rte{$mfile,$ndt};
              }elsif( $mfile eq "hlt" ) {
               $arhlt[$ndt] =  $rte{$mfile,$ndt};
	       }
              }
          }
print STDOUT "Check data   ",$ndt,"   ", $ndate[$ndt],"   ",$arphysics[$ndt],"   ", $argamma[$ndt], "\n";

        $ndt++;

    } # foreach tdate



    &StDbProdDisconnect();

    my @data = ();

    my $graph = new GD::Graph::linespoints(750,650);

    if ( ! $graph){
	print STDOUT $query->header(-type => 'text/plain');
	print STDOUT "Failed\n";

    } else {
	# 
	my $format = $graph->export_format();


	$legend[0] = "st_physics   ";
	$legend[1] = "st_mtd       ";
	$legend[2] = "st_upsilon   ";
	$legend[3] = "st_hlt       ";
	$legend[4] = "st_gamma     ";
	
#	@data = (\@ndate, \@arphysics, \@armtd, \@arupsilon, \@arhlt, \@argamma ) ;

        	@data = (\@ndate, \@arphysics );   
  
	my $ylabel;
	my $gtitle; 
	my $xLabelsVertical = 1;
	my $xLabelPosition = 0;
	my $xLabelSkip = 1;
	my $skipnum = 1;
 

	$min_y = 0;
#	$max_y = 140 ; 

	if (scalar(@ndate) >= 20 ) {
	    $skipnum = int(scalar(@ndate)/20);
	}

	$xLabelSkip = $skipnum;

	$ylabel = "Average ratio RealTime/CPU per day";
	$gtitle = "Average ratio RealTime/CPU per day for different stream data";
	
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
                    dclrs => [ qw(lblue lgreen lgray lpurple lorange lred lblack) ],
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
	    print $query->header(-type => 'text/html')."\n";
	    &beginHtml();
	} else {
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
     <h1 align=center>No Data for that Period</h1>
     

    </body>
   </html>
END
}
