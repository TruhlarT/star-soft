#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log: 
# 
# L.Didenko and Wensheng Deng  10/15/1999
# 
# GifPlots.pl
# Script to create plots for production operation
# 
#################################################################### 

require "dbOperaSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;
use CGI::Carp qw(fatalsToBrowser);
use Class::Struct;
use File::Basename;

 my ($query) = @_;

 
 $query = new CGI;
  
 $set1 =  $query->param('set1');
 $mchain = $query->param('mchain');
 $libTag1 = $query->param('libTag1');
 $datProd = $query->param('datProd');
 $plotVal = $query->param('plotVal');
 

struct Products => {
    geantFName => '$',
    dbId      => '$', 
    memSize   => '$',
    cpuEvt    => '$', 
    aveTrks   => '$',
    aveVtxs   => '$',
};

my @prodInfo;
my $nProdInfo = 0;


&StDbOperaConnect();

my $sql;
if ($datProd) {
$sql="SELECT GeantFile, id, Sum_File, Mem_size_MB, CPU_per_evt_sec, Ave_No_Tracks, Ave_No_Vtx FROM $OperationT WHERE SetName = '$set1' AND Chain = '$mchain' AND Lib_tag = '$libTag1' AND HPSS_dst_date = '$datProd' "; 
}
else {
 $sql="SELECT GeantFile, id, Sum_File, Mem_size_MB, CPU_per_evt_sec, Ave_No_Tracks, Ave_No_Vtx FROM $OperationT WHERE SetName = '$set1' AND Chain = '$mchain'  AND Lib_tag = '$libTag1'" ; 
}
 
  $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute;
    while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS}; 

        $prodAddr = \(Products->new());
         my $sumFile = "no";
    for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];
        ($$prodAddr)->geantFName($fvalue) if( $fname eq 'GeantFile');
        ($$prodAddr)->dbId($fvalue) if( $fname eq 'id');
        ($$prodAddr)->memSize($fvalue) if( $fname eq 'Mem_size_MB');
        ($$prodAddr)->cpuEvt($fvalue) if( $fname eq 'CPU_per_evt_sec');
        ($$prodAddr)->aveTrks($fvalue) if( $fname eq 'Ave_No_Tracks');
        ($$prodAddr)->aveVtxs($fvalue) if( $fname eq 'Ave_No_Vtx');
        $sumFile = $fvalue if ( $fname eq 'Sum_File');      
    }       
        next if ( $sumFile eq "no" );
      $prodInfo[$nProdInfo] = $prodAddr;      
      $nProdInfo++;
}

&StDbOperaDisconnect();
#===================================================================================================
# can loop over set here. for the moment, just deal with one set.

my ($second, $minute, $hour, $day, $month ,$year) = (localtime())[0,1,2,3,4,5];
$month +=1;
my $timeS = sprintf ("%2.2d%2.2d%2.2d%2.2d%2.2d%2.2d", 
                       $year,$month,$day,$hour,$minute,$second);

my $mSetName = "\/";
my $mGeantFName = "n\/a";
my $mDbId = "n\/a";
my $mMemSize = 0;
my $mCPUEvt = 0;
my $mAveTrks = 0;
my $mAveVtxs = 0;

my @aGeantFName;
my @aDbId;
my @aMemSize;
my @aCPUEvt;
my @aAveTrks;
my @aAveVtxs;

my $ii = 0;
foreach $prodAddr (@prodInfo) {
    $mGeantFName = ($$prodAddr)->geantFName; 
    $mDbId = ($$prodAddr)->dbId;
    $mMemSize = ($$prodAddr)->memSize;
    $mCPUEvt  = ($$prodAddr)->cpuEvt;
    $mAveTrks = ($$prodAddr)->aveTrks;
    $mAveVtxs = ($$prodAddr)->aveVtxs;

   $mGeantFName = basename("$mGeantFName", ".fzd");
 
      $aGeantFName[$ii] = $mGeantFName;
      $aDbId[$ii] = $mDbId;
      $aMemSize[$ii] = $mMemSize;
      $aCPUEvt[$ii] = $mCPUEvt;
      $aAveTrks[$ii] = $mAveTrks;
      $aAveVtxs[$ii] = $mAveVtxs;      
    $ii++;
}

#========================================================================================
my @markerList = (3,4,1,2,5,6,7,8);
my $marketSize = 4;
my $xLabelSkip = 4;
my $lineWidth = 5;
my $xLabelsVertical = 1;
my $xLabelPosition = 0;

my $xLabelSkip = 1;
$xLabelSkip = 2 if( scalar(@aDbId) > 20 );
$xLabelSkip = 4 if( scalar(@aDbId) > 40 );
$xLabelSkip = 8 if( scalar(@aDbId) > 80 );
$xLabelSkip = 10 if( scalar(@aDbId) > 100 );

my $qr = new CGI;

my $graph = new GIFgraph::linespoints(650,500);

if($plotVal eq "Memory_Size")   {
my @data = (\@aGeantFName, \@aMemSize);

print $qr->header(-type => "image/gif");


$graph->set(x_label => " ",
            y_label => "Average memory size (MB)", 
            title   => "$set1",
            y_max_value => 800,
            y_min_value => 0,
            dclrs => ['red','green','blue'],
            markers => \@markerList,
           line_width => $lineWidth,
           x_label_skip => $xLabelSkip, 
           x_labels_vertical =>$xLabelsVertical 

);

$graph->set_title_font(gdLargeFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);

print $graph->plot(\@data);
}

####### CPU per Event

elsif($plotVal eq "CPU_Event") {

 my @data = (\@aGeantFName, \@aCPUEvt);

$xLabelsVertical = 1;

print $qr->header(-type => "image/gif");

$graph = new GIFgraph::linespoints(650,560);

$graph->set(x_label => "",
            y_label => "CPU per event(seconds)", 
            title   => "$set1",
            markers => \@markerList,
            line_width => $lineWidth,
            x_label_skip => $xLabelSkip,
            y_min_value => 0,
            y_max_value => 800,
 x_labels_vertical =>$xLabelsVertical
);

$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
print $graph->plot(\@data);

}

##### Average number of tracks

elsif ( $plotVal eq "Avg_No_Tracks") {
 
 my @data = (\@aGeantFName, \@aAveTrks);

$xLabelsVertical = 1;

print $qr->header(-type => "image/gif");

$graph = new GIFgraph::linespoints(650,560);

$graph->set(x_label => "",
            y_label => "Average number of tracks", 
            title   => "$set1",
            markers => \@markerList,
            line_width => $lineWidth,
            x_label_skip => $xLabelSkip,
            y_min_value => 0,
            y_max_value => 10000,
 x_labels_vertical =>$xLabelsVertical
);

$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
print $graph->plot(\@data);
}

##### Average number of vertexes

elsif ( $plotVal eq "Avg_No_Vertexes") {
 
 my @data = (\@aGeantFName, \@$aAveVtxs);

$xLabelsVertical = 1;

print $qr->header(-type => "image/gif");

$graph->set(x_label => "",
            y_label => "Average number of vertexes", 
            title   => "$set1",
            markers => \@markerList,
            line_width => $lineWidth,
            x_label_skip => $xLabelSkip,
            y_min_value => 0,
            y_max_value => 4000,
 x_labels_vertical =>$xLabelsVertical
);

$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
print $graph->plot(\@data);
}







