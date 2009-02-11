#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L. Didenko 
# gridtransPlots.pl to make plots of output files trasnferring to RCF
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
$dbname="Scheduler_bnl";



 struct JobAttr => {
    tsdate      => '$',
    tsite       => '$',
    tsize       => '$',
		    };


($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".($mon+1)."-".$mday;

my $nowdate;
my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

my @prodyear = ("2008","2009");

# Tables

$JobEfficiencyT = "MasterJobEfficiency";

my @arsites = ( );
my @sites = ( );
my $mydate;
my $nd = 0;
my $nsite = 0;

my @trstat = ();
my $nstat = 0;
my %siteH = { };

 
  &GRdbConnect();

 
 my @arperiod = ("day","week","1_month","2_months","3_months","4_months","5_months","6_months");


  $sql="SELECT DISTINCT site FROM $JobEfficiencyT where site is not NULL ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while($mysite = $cursor->fetchrow) {
        $arsites[$nsite] = $mysite;
        $nsite++;
      }

   $cursor->finish; 

  push @sites, @arsites;
#  push @arsites, "ALL";
   
  
    &GRdbDisconnect();

 my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $pryear  = $query->param('ryear');
 my $qperiod = $query->param('period');
 my $qsite   = $query->param('prodsite');

 if( $qperiod eq "" and $qsite eq "" and $pryear eq "" ) {


print $query->header;
print $query->start_html('Transferring output files');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Transferring output files from the remote sites</u></h1>\n";
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
                             -values=>\@prodyear,
                             -default=>2009,
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
print "<h3 align=center>Production Site</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'prodsite',
                             -values=>\@arsites,
                             -default=>pdsf,
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

 my $pryear  = $qqr->param('ryear');
 my $qperiod = $qqr->param('period');
 my $qsite   = $qqr->param('prodsite');
 
my $dyear = $pryear - 2000;
if($dyear < 10) { $dyear = "0".$dyear };

# Tables

$MasterIOT = "MasterIO";

my $day_diff = 0;
my $nmonth = 0;
my @prt = ();
my $myday;
my $nday = 0;
my @ardays = ();
my $tdate;

   if($pryear eq "2008") {
    $nowdate = "2007-12-31";
  }else{
    $nowdate = $todate;
  }

    if( $qperiod eq "week") {
           $day_diff = 8;
  
   }elsif ( $qperiod =~ /month/) {
       @prt = split("_", $qperiod);
       $nmonth = $prt[0];
       $day_diff = 30*$nmonth + 1; 
    }

$day_diff = int($day_diff);

   &GRdbConnect();

   $sql="SELECT DISTINCT date_format(date_requester, '%Y-%m-%d %H') AS PDATE  FROM $MasterIOT WHERE (TO_DAYS(\"$nowdate\") - TO_DAYS(date_requester)) < ? order by PDATE";

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($day_diff);

      while($myday = $cursor->fetchrow) {
        $ardays[$nday] = $myday;
        $nday++;
      }

my $ndt1 = 0;
my $ndt2 = 0;

 @trstat = ();  
 $nstat = 0;


   foreach  $tdate (@ardays) {

  if( $qsite eq "ALL" ) {

     $sql="SELECT  date_format(date_requester, '%Y-%m-%d %H') as PDATE, size_requester, $MasterIOT.jobID_MD5 as jobMID, $MasterIOT.processID as prMID, $JobEfficiencyT.jobID_MD5 as jobEfID, $JobEfficiencyT.processID as prJID, site FROM $MasterIOT, $JobEfficiencyT WHERE $MasterIOT.jobID_MD5 = $JobEfficiencyT.jobID_MD5 AND $MasterIOT.processID = $JobEfficiencyT.processID AND isInputFile = 0 AND date_requester like '$tdate%' order by PDATE";

    $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute;

  }else{

     $sql="SELECT  date_format(date_requester, '%Y-%m-%d %H') as PDATE, size_requester, $MasterIOT.jobID_MD5 as jobMID, $MasterIOT.processID as prMID, $JobEfficiencyT.jobID_MD5 as jobEfID, $JobEfficiencyT.processID as prJID, site FROM $MasterIOT, $JobEfficiencyT WHERE $MasterIOT.jobID_MD5 = $JobEfficiencyT.jobID_MD5 AND $MasterIOT.processID = $JobEfficiencyT.processID AND site = ? AND date_requester like '$tdate%' order by PDATE";


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

      ($$fObjAdr)->tsdate($fvalue)    if( $fname eq 'PDATE');
      ($$fObjAdr)->tsite($fvalue)     if( $fname eq 'site');
      ($$fObjAdr)->tsize($fvalue)     if( $fname eq 'size_requester');

        }
       $trstat[$nstat] = $fObjAdr;
        $nstat++;
      }
  }

 %siteH = { };

my $gdate;
my $gsite;
my $gsize;

my $mdate; 
my %sumsz = {};
my %datetrans  = {};
my %sumpdsf = {};
my %sumvm = {};
my %datepdsf  = {};
my %datevm  = {};
my %nfpdsf   = {};
my %nfvm   = {};
my %sumunk = {};
my %dateunk  = {};
my %nfunk   = {};
my @ndatepdsf = ();
my @npdsf = ();
my @ndatevm = ();
my @nvm = ();
my @sizepdsf = ();
my @sizevm = ();


      foreach $jstat (@trstat) {

    $gdate    = ($$jstat)->tsdate;
    $gsite     = ($$jstat)->tsite; 
    $gsize     = ($$jstat)->tsize; 


 if(!defined($gsite)) {$gsite = "unknown"}

    if ($gsite eq "pdsf") {
    $sumpdsf{$gdate} = $sumpdsf{$gdate} + $gsize;
    $datepdsf{$gdate} = $gdate;
    $nfpdsf{$gdate}++;     
    }elsif ($gsite eq "amazon") {
    $sumvm{$gdate} = $sumvm{$gdate} + $gsize;
    $datevm{$gdate} = $gdate;
    $nfvm {$gdate}++;        
   }else{
    $sumunk{$gdate} = $sumunk{$gdate} + $gsize;
    $dateunk{$gdate} = $gdate;
    $nfunk{$gdate}++;        
    }
 }

 $ndt1 = 0;
 $ndt2 = 0;

   for($ii = 0; $ii <scalar(@ardays); $ii++) {

      $mdate = $ardays[$ii];

      if( $datepdsf{$mdate}) {

     $ndatepdsf[$ndt1] = $datepdsf{$mdate};     
     $npdsf[$ndt1] = $nfpdsf{$mdate}/10; 
     $sizepdsf[$ndt1] = $sumpdsf{$mdate}/1000000000. ;
      $ndt1++; 
      }
      if( $datevm{$mdate}) {

     $ndatevm[$ndt2] = $datevm{$mdate};     
     $nvm[$ndt2] = $nfvm{$mdate}/10; 
     $sizevm[$ndt2] = $sumvm{$mdate}/1000000000. ;
      $ndt2++; 
   }    

  }
 
   &GRdbDisconnect();

 my $graph = new GD::Graph::linespoints(750,650);

  if ( ! $graph){
    print STDOUT $qqr->header(-type => 'text/plain');
    print STDOUT "Failed\n";

 } else {

  my $format = $graph->export_format;
  print header("image/$format");
  binmode STDOUT;

    $ptag = $qsite; 

    $legend[0] = "Size of files in GB ";
    $legend[1] = "Number of files/10; "; 

  if($qsite eq "pdsf")  {

    @data = (\@ndatepdsf, \@sizepdsf, \@npdsf ) ;

    }elsif($qsite eq "amazon" ) {

     @data = (\@ndatevm, \@sizevm, \@nvm ) ; 

  }

#   print $qqr->start_html(-title=>"Files transferring"), "\n"; 

 my $ylabel;
 my $gtitle; 
 my $xLabelsVertical = 1;
 my $xLabelPosition = 0;
 my $xLabelSkip = 1;

$xLabelSkip = 2 if( $qperiod eq "week" );
$xLabelSkip = 4 if( $qperiod eq "1_months" );
$xLabelSkip = 6 if( $qperiod eq "2_months" );
$xLabelSkip = 8 if( $qperiod eq "3_months" );
$xLabelSkip = 10 if( $qperiod eq "4_months" );
$xLabelSkip = 14 if( $qperiod eq "5_months" );
$xLabelSkip = 20 if( $qperiod eq "6_months" );

  $min_y = 0;
#  $max_y = 100 ;  
  $ylabel = "Size in GB and number of transfered files per 1 hour";
  $gtitle = "Size of files transffered for the period $qperiod from  $qsite site";

     $graph->set(x_label => "Date of file transferring",
                y_label => $ylabel,
                title   => $gtitle,
                y_tick_number => 15,
                x_label_position => 0.5,
                y_min_value => $min_y,
                y_max_value => $max_y,
                y_number_format => \&y_format,
                #labelclr => "lblack",
                titleclr => "lblack",
                dclrs => [ qw(lblack lgreen lgray lpurple lorange lred lblue) ],
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

   print STDOUT $graph->plot(\@data)->$format();

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

