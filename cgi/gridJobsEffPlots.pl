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
use Mysql;
use Class::Struct;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="GridJobs";



 struct JobAttr => {
    subday      => '$',
    tsite       => '$',
    glstat      => '$',
    glerr       => '$', 
    lgstat      => '$',
    exstat      => '$',
    intrs       => '$',
    outtrs      => '$',
    rftime      => '$',
    crtime      => '$',
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
my $glStatus = 0;
my $glError = 0;
my $lgStatus = 0;
my $intrans = 0;
my $outtrans = 0;
my $recoSt = "not complete";
my $sdate = "0000-00-00 00:00:00:";
my $cretime = "0000-00-00 00:00:00:";
my $sbday;
my $gsite;
my @njobs = ();
my %siteH = { };
my @globeff = ();
my @logeff = ();
my @inputef = ();
my @outputeff = ();
my @recoComeff = ();
my @overeff = ();
my @ndate = ();
my @effpdsf = ();
my @effspu = ();
my @effwsu = ();
my @effbnl = ();
my %globEfH = { };
my %logEfH = { };
my %inEfH  = { };
my %outEfH  = { };
my %recoEfH = { };
my %overEfH = { };
my %siteEff = { };
my %datetest = { };
my $nreco = 0;
my @sites = ();
my $msite;


my $globSt;
my $logSt;
my $inSt;
my $outSt;

 
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
print $query->start_html('Grid Jobs efficiency');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Grid Test Efficiency</u></h1>\n";
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
my $myday;
my $nday = 0;
my @ardays = ();
my $tdate;


    if( $qperiod eq "week") {
           $day_diff = 7;
  
   }elsif ( $qperiod =~ /month/) {
       @prt = split("_", $qperiod);
       $nmonth = $prt[0];
       $day_diff = 30*$nmonth + 1; 
    }

   &GRdbConnect();

   $sql="SELECT DISTINCT testday FROM $JobStatusT WHERE status = 'complete' AND (TO_DAYS(\"$nowdate\") - TO_DAYS(testday)) <= $day_diff ORDER by testday";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

      while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
      }

my $ndt = 0;

   foreach  $tdate (@ardays) {

 @jbstat = ();  
 $nstat = 0;

  if( $qsite eq "ALL" ) {

      $sql="SELECT testday, site, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, recoFinishTime, createTime FROM $JobStatusT WHERE  testday = '$tdate' AND (status = 'complete' OR status = 'failed') "; 

  }else{

     $sql="SELECT testday, site, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, recoFinishTime, createTime FROM $JobStatusT WHERE site = '$qsite' AND  testday = '$tdate' AND (status = 'complete' OR status = 'failed') ";

 }

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;
 
      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(JobAttr->new());

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

      ($$fObjAdr)->subday($fvalue)    if( $fname eq 'testday');
      ($$fObjAdr)->tsite($fvalue)     if( $fname eq 'site');
      ($$fObjAdr)->glstat($fvalue)    if( $fname eq 'globusStatus');
      ($$fObjAdr)->glerr($fvalue)     if( $fname eq 'globusError');
      ($$fObjAdr)->lgstat($fvalue)    if( $fname eq 'logStatus');
      ($$fObjAdr)->exstat($fvalue)    if( $fname eq 'execStatus');          
      ($$fObjAdr)->intrs($fvalue)     if( $fname eq 'transfer_in');  
      ($$fObjAdr)->outtrs($fvalue)    if( $fname eq 'transfer_out'); 
      ($$fObjAdr)->rftime($fvalue)    if( $fname eq 'recoFinishTime');
      ($$fObjAdr)->crtime($fvalue)    if( $fname eq 'createTime');

        }
       $jbstat[$nstat] = $fObjAdr;
        $nstat++;
      }


 %siteH = { };
 %globEfH = { };
 %logEfH = { };
 %inEfH  = { };
 %outEfH  = { };
 %recoEfH = { };
 %overEfH = { };
 %siteEff = { };
 %datetest = { };

   $nreco = 0;

      foreach $jstat (@jbstat) {

    $sbday     = ($$jstat)->subday;
    $gsite     = ($$jstat)->tsite; 
    $glStatus  = ($$jstat)->glstat; 
    $glError   = ($$jstat)->glerr;
    $lgStatus  = ($$jstat)->lgstat;
    $intrans   = ($$jstat)->intrs;
    $outtrans  = ($$jstat)->outtrs; 
    $recoSt    = ($$jstat)->exstat;
    $sdate     = ($$jstat)->rftime;
    $cretime    = ($$jstat)->crtime;

    if( $glError == 129 ) {
	$glStatus = 1;
   }

    $siteH{$gsite}++; 

    if( $recoSt eq "Done" ) { 
    $nreco = 1;
   } else{ 
    $nreco = 0;
  }

    $datetest{$gsite} = $sbday;
    $globEfH{$gsite} = $globEfH{$gsite} + $glStatus;
    $logEfH{$gsite} =  $logEfH{$gsite} +  $lgStatus;
    $inEfH{$gsite} = $inEfH{$gsite} + $intrans;   
    $outEfH{$gsite} = $outEfH{$gsite} + $outtrans;
    $recoEfH{$gsite} = $recoEfH{$gsite} + $nreco;

   if( $glStatus == 1 && $lgStatus >= 1 && $intrans == 1 && $outtrans == 5 && $nreco == 1 ) {

       $siteEff{$gsite}++;

  }

}
   for($ii = 0; $ii <scalar(@sites); $ii++) {

   $msite = $sites[$ii]; 
       if( $siteH{$msite} >= 1 ) {

   $ndate[$ndt] = $datetest{$msite};
   $njobs[$ndt] = $siteH{$msite};
   $globeff[$ndt] = $globEfH{$msite}*100/$njobs[$ndt];
   $logeff[$ndt] = $logEfH{$msite}*100/(2*$njobs[$ndt]);
   $inputef[$ndt] = $inEfH{$msite}*100/$njobs[$ndt];
   $outputeff[$ndt] = $outEfH{$msite}*100/(5*$njobs[$ndt]);
   $recoComeff[$ndt] = $recoEfH{$msite}*100/$njobs[$ndt]; 
   $overeff[$ndt] = $siteEff{$msite}*100/$njobs[$ndt];
   if ($msite eq "PDSF")  {
   $effpdsf[$ndt] = $siteEff{$msite}*100/$njobs[$ndt];
   }elsif($msite eq "SPU")  {
   $effspu[$ndt] = $siteEff{$msite}*100/$njobs[$ndt];
   }elsif($msite eq "WSU")  {
   $effwsu[$ndt] = $siteEff{$msite}*100/$njobs[$ndt];
   }elsif($msite eq "BNL")  {
   $effbnl[$ndt] = $siteEff{$msite}*100/$njobs[$ndt];
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

    $legend[0] = "Efficiency for PDSF";
    $legend[1] = "Efficiency for SPU"; 
    $legend[2] = "Efficiency for WSU"; 
    $legend[3] = "Efficiency for BNL";

    @data = (\@ndate, \@effpdsf, \@effspu, \@effwsu, \@effbnl );

      }else{

    $legend[0] = "Globus efficiency";
    $legend[1] = "Log files delivery";
    $legend[2] = "Input transferring";
    $legend[3] = "Output transferring";
    $legend[4] = "Reco completion";
    $legend[5] = "Overall efficiency";

      @data = (\@ndate, \@globeff, \@logeff, \@inputef, \@outputeff, \@recoComeff, \@overeff) ;

  }

 my $ylabel;
 my $gtitle; 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 3 if( $qperiod eq "1_months" );
$xLabelSkip = 6 if( $qperiod eq "2_months" );
$xLabelSkip = 9 if( $qperiod eq "3_months" );
$xLabelSkip = 12 if( $qperiod eq "4_months" );
$xLabelSkip = 15 if( $qperiod eq "5_months" );
$xLabelSkip = 18 if( $qperiod eq "6_months" );
$xLabelSkip = 21 if( $qperiod eq "7_months" );
$xLabelSkip = 24 if( $qperiod eq "8_months" );
$xLabelSkip = 27 if( $qperiod eq "9_months" );
$xLabelSkip = 30 if( $qperiod eq "10_months" );
$xLabelSkip = 33 if( $qperiod eq "11_months" );
$xLabelSkip = 36 if( $qperiod eq "12_months" );


  $min_y = 0;
  $max_y = 120 ;  
  $ylabel = "Efficiency in %";
  $gtitle = "Efficiency of jobs execution for the period of $qperiod on  $qsite site";

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

