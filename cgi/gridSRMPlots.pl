#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI;
use GIFgraph::linespoints;
use GD;
use Class::Struct;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="GridJobs";



 struct JobAttr => {
      subday    => '$',
       tsite    => '$',
        wans    => '$',
        srms    => '$', 
        drmt    => '$',
		    };


($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;


# Tables
#$JobStatusT = "JobStatus"."_".$dyear;

$JobStatusT = "JobStatus_06";

my @arsites = ( );
my $mydate;
my $nd = 0;
my $nsite = 0;

my @jbstat = ();
my $nstat = 0;
my $sbday;
my $gsite;
my @njobs = ();
my %siteH = { };
my $wansp = 0;
my $srmsp = 0;
my $drmtime = 0;
my @ndate = ();
my @wanpdsf = ();
my @wanspu = ();
my @wanwsu = ();
my @wanbnl = ();
my %datetest = { };
my @sites = ();
my $msite;
my @wansite = ();
my @srmsite = ();

 
  &GRdbConnect();

 
 my @arperiod = ("week","1_month","2_months","3_months","4_months","5_months","6_months","7_months","8_months","9_months","10_months","11_months","12_months");


  $sql="SELECT DISTINCT site   FROM $JobStatusT ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while($mysite = $cursor->fetchrow) {
        $arsites[$nsite] = $mysite;
        $nsite++;
      }

   $cursor->finish; 

  push @sites, @arsites;
  push @arsites, "ALL";
   
    &GRdbDisconnect();

 my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $qperiod  =  $query->param('period');
 my $qsite  =  $query->param('testsite');

 if( $qperiod eq "" and $qsite eq "" ) {


print $query->header;
print $query->start_html('SRM Transferring Speed');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>SRM Transferring Speed</u></h1>\n";
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
print "<h3 align=center> Period of monitoring</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'period',
                             -values=>\@arperiod,
                             -default=>week,
                             -size =>1); 


print "<p>";
print "</td><td>"; 
print "<h3 align=left> Test Site</h3>";
print "<h4 align=left>";
print  $query->scrolling_list(-name=>'testsite',
                             -values=>\@arsites,
                             -default=>ALL,
                             -size =>1); 


print "<p>";
print "</td><td>";
print "</td> </tr> </table><hr><center>";

print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

  }else{

my $qqr = new CGI;

 my $qperiod  =  $qqr->param('period');
 my $qsite  =  $qqr->param('testsite');
 
my $day_diff = 0;
my $nmonth = 0;
my @prt = ();
my $myday = 0;
my $nday = 0;
my @ardays = ();
my $tdate;


    if( $qperiod eq "week") {
           $day_diff = 8;
  
   }elsif ( $qperiod =~ /month/) {
       @prt = split("_", $qperiod);
       $nmonth = $prt[0];
       $day_diff = 30*$nmonth + 1; 
    }

  $day_diff = int($day_diff);

   &GRdbConnect();

   $sql="SELECT DISTINCT testday FROM $JobStatusT WHERE status = 'complete' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(testday)) < ? ORDER by testday";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($day_diff);

      while($myday = $cursor->fetchrow) {
#      print $myday, "\n"; 

        $ardays[$nday] = $myday;
        $nday++;
      }

my $ndt = 0;

@ndate = { };

   foreach  $tdate (@ardays) {

 @srmspeed = ();  
 $nstat = 0;


  if( $qsite eq "ALL" ) {

      $sql="SELECT testday, site, wan_speed, srm_speed, drm_time FROM $JobStatusT WHERE  testday = '$tdate' AND transfer_out >= 2  AND (status = 'complete' OR status = 'failed') "; 

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

  }else{

     $sql="SELECT testday, site, wan_speed, srm_speed, drm_time FROM $JobStatusT WHERE site = ? AND  testday = '$tdate' AND transfer_out >= 2  AND (status = 'complete' OR status = 'failed') ";


     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qsite);

} 
      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(JobAttr->new());

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

      ($$fObjAdr)->subday($fvalue)   if( $fname eq 'testday');
      ($$fObjAdr)->tsite($fvalue)    if( $fname eq 'site');
      ($$fObjAdr)->wans($fvalue)     if( $fname eq 'wan_speed');
      ($$fObjAdr)->srms($fvalue)     if( $fname eq 'srm_speed');
      ($$fObjAdr)->drmt($fvalue)     if( $fname eq 'drm_time'); 


        }
       $srmspeed[$nstat] = $fObjAdr;
        $nstat++;
      }


 %siteH = { };
 %wan = { };
 %srm = { };
 %drm = { };
 %datetest = { };

      foreach $jobst (@srmspeed) {

    $sbday     = ($$jobst)->subday;
    $gsite     = ($$jobst)->tsite; 
    $wansp     = ($$jobst)->wans;
    $srmsp     = ($$jobst)->srms;
    $drmtime   = ($$jobst)->drmt;   

    $siteH{$gsite}++; 

    $datetest{$gsite} = $sbday;
    $wan{$gsite} = $wan{$gsite} + $wansp;
    $srm{$gsite} = $srm{$gsite} + $srmsp;
    $drm{$gsite} = $drm{$gsite} + $drmtime;   

}
   for($ii = 0; $ii <scalar(@sites); $ii++) {

   $msite = $sites[$ii]; 
       if( $siteH{$msite} >= 1 ) {

   $ndate[$ndt] = $datetest{$msite};
   $njobs[$ndt] = $siteH{$msite};

   if ($msite eq "PDSF")  {
   $wanpdsf[$ndt] = $wan{$msite}/$njobs[$ndt];
   $srmpdsf[$ndt] = $srm{$msite}/$njobs[$ndt];   
   }elsif($msite eq "SPU")  {
   $wanspu[$ndt] = $wan{$msite}/$njobs[$ndt];
   $srmspu[$ndt] = $srm{$msite}/$njobs[$ndt];
   }elsif($msite eq "WSU")  {
   $wanwsu[$ndt] = $wan{$msite}/$njobs[$ndt];
   $srmwsu[$ndt] = $srm{$msite}/$njobs[$ndt];
   }elsif($msite eq "BNL")  {
   $wanbnl[$ndt] = $wan{$msite}/$njobs[$ndt];
   $srmbnl[$ndt] = $srm{$msite}/$njobs[$ndt];

       }
     }
   }
   $ndt++;

 }
    &GRdbDisconnect();


   $graph = new GIFgraph::linespoints(750,650);

 if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";
 } else {
    print STDOUT $qqr->header(-type => 'image/gif');
    binmode STDOUT;

    if( $qsite eq "ALL" ) {

    $legend[0] = "WAN speed  for PDSF";
    $legend[1] = "SRM speed  for PDSF";
#    $legend[1] = "WAN speed  for SPU"; 
#    $legend[2] = "WAN speed  for WSU"; 
#    $legend[3] = "WAN speed  for BNL";

#    @data = (\@ndate, \@wanpdsf, \@wanspu, \@wanwsu, \@wanbnl );
     @data = (\@ndate, \@wanpdsf, \@srmpdsf ); 

      }else{

    $legend[0] = "WAN speed";
    $legend[1] = "SRM speed";

       if( $qsite eq "PDSF" ) {    
	   push @wansite, @wanpdsf;
           push @srmsite, @srmpdsf;
       }elsif( $qsite eq "WSU" ) {    
	   push @wansite, @wanwsu;
	   push @srmsite, @wanwsu;
       }elsif( $qsite eq "SPU" ) {    
	   push @wansite, @wanspu;
	   push @srmsite, @wanspu;
       }elsif( $qsite eq "BNL" ) {    
	   push @wansite, @wanbnl;
	   push @srmsite, @wanbnl;
       }
      @data = (\@ndate, \@wansite, \@srmsite ) ;

  }

 my $ylabel;
 my $gtitle; 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 1 if( $qperiod eq "1_months" );
$xLabelSkip = 2 if( $qperiod eq "2_months" );
$xLabelSkip = 3 if( $qperiod eq "3_months" );
$xLabelSkip = 4 if( $qperiod eq "4_months" );
$xLabelSkip = 5 if( $qperiod eq "5_months" );
$xLabelSkip = 6 if( $qperiod eq "6_months" );
$xLabelSkip = 7 if( $qperiod eq "7_months" );
$xLabelSkip = 8 if( $qperiod eq "8_months" );
$xLabelSkip = 9 if( $qperiod eq "9_months" );
$xLabelSkip = 10 if( $qperiod eq "10_months" );
$xLabelSkip = 11 if( $qperiod eq "11_months" );
$xLabelSkip = 12 if( $qperiod eq "12_months" );

  $min_y = 0;
  $max_y = 2000 ;  
  $ylabel = "Speed in KB/sec";
  $gtitle = "Average SRM Speed for the period of $qperiod on  $qsite site";

     $graph->set(x_label => "Date of Test",
                y_label => $ylabel,
                title   => $gtitle,
                y_tick_number => 10,
                x_label_position => 0.5,
                y_min_value => $min_y,
                y_max_value => $max_y,
                y_number_format => \&y_format,
                #labelclr => "lblack",
                titleclr => "lblack",
                dclrs => [ qw(lblack lblue lred lgreen lpurple lorange ) ],
                line_width => 2,
                markers => [ 2,3,4,5,6,7,8,9],
                marker_size => 1,
                x_label_skip => $xLabelSkip, 
                x_labels_vertical =>$xLabelsVertical, 
                );

    $graph->set_legend(@legend);
    $graph->set_legend_font(gdMediumBoldFont);
    $graph->set_title_font(gdLargeFont);
    $graph->set_x_label_font(gdMediumBoldFont);
    $graph->set_y_label_font(gdMediumBoldFont);
    $graph->set_x_axis_font(gdMediumBoldFont);
    $graph->set_y_axis_font(gdMediumBoldFont);
    print STDOUT $graph->plot(\@data);
    }

 }

######################
sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}


######################
sub GRdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub GRdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

