#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log: 
# 
# L.Didenko
# 
# GifDstPlots.pl
# Script to create plots for production operation
# 
#################################################################### 

require "/afs/rhic/star/packages/DEV/mgr/dbDstProdSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;
use CGI::Carp qw(fatalsToBrowser);
use Class::Struct;
use File::Basename;


 my ($query) = @_;

 
$query = new CGI;


print <<END;
END


  
 $set1   =  $query->param('set1');
 $evType =  $query->param('EvType');
 $numRun =  $query->param('numRun');
 $datProd = $query->param('datProd');
 $plotVal = $query->param('plotVal');



struct Products => {
    flName  => '$',
    dbId      => '$', 
    memSize   => '$',
    cpuEvt    => '$', 
    aveTrks   => '$',
    aveVtxs   => '$',
};


my @prodInfo;
my $nProdInfo = 0;


&StDbDstProdConnect();

my $sql;

if ($datProd) {
 if( $numRun ne "all" and $evType ne "all") {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND nrun = '$numRun' AND eventType = '$evType' AND HPSS_date = '$datProd' "; 
}
elsif ( $numRun ne "all" and $evType eq "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND nrun = '$numRun' AND HPSS_date = '$datProd' "; 
}
elsif ( $numRun eq "all" and $evType ne "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1'  AND eventType = '$evType' AND HPSS_date = '$datProd' "; 
}
elsif ( $numRun eq "all" and $evType eq "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND HPSS_date = '$datProd' "; 
}
}
###
else {
 if( $numRun ne "all" and $evType ne "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND nrun = '$numRun' AND eventType = '$evType' "; 
}
elsif ( $numRun ne "all" and $evType eq "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND nrun = '$numRun' "; 
}
elsif ( $numRun eq "all" and $evType ne "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' AND eventType = '$evType' "; 
}
elsif ( $numRun eq "all" and $evType eq "all" ) {
$sql="SELECT fileName, id, summaryFile, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex FROM $DstProductionT WHERE prodSeries = '$set1' "; 
 }
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

        ($$prodAddr)->flName($fvalue) if( $fname eq 'fileName');
        ($$prodAddr)->dbId($fvalue) if( $fname eq 'id');
        ($$prodAddr)->memSize($fvalue) if( $fname eq 'mem_size_MB');
        ($$prodAddr)->cpuEvt($fvalue) if( $fname eq 'CPU_per_evt_sec');
        ($$prodAddr)->aveTrks($fvalue) if( $fname eq 'avg_no_tracks');
        ($$prodAddr)->aveVtxs($fvalue) if( $fname eq 'avg_no_vertex');
        $sumFile = $fvalue if ( $fname eq 'summaryFile');      
    }       
        next if ( $sumFile eq "no" );
      $prodInfo[$nProdInfo] = $prodAddr;      
      $nProdInfo++;
}

&StDbDstProdDisconnect();
#===================================================================================================
# can loop over set here. for the moment, just deal with one set.

my ($second, $minute, $hour, $day, $month ,$year) = (localtime())[0,1,2,3,4,5];
$month +=1;
my $timeS = sprintf ("%2.2d%2.2d%2.2d%2.2d%2.2d%2.2d", 
                       $year,$month,$day,$hour,$minute,$second);

my $mprodSer = "\/";
my $mflName = "n\/a";
my $mDbId = "n\/a";
my $mMemSize = 0;
my $mCPUEvt = 0;
my $mAveTrks = 0;
my $mAveVtxs = 0;

my @aflName;
my @aDbId;
my @aMemSize;
my @aCPUEvt;
my @aAveTrks;
my @aAveVtxs;

my $ii = 0;
foreach $prodAddr (@prodInfo) {
    $mflName = ($$prodAddr)->flName; 
    $mDbId = ($$prodAddr)->dbId;
    $mMemSize = ($$prodAddr)->memSize;
    $mCPUEvt  = ($$prodAddr)->cpuEvt;
    $mAveTrks = ($$prodAddr)->aveTrks;
    $mAveVtxs = ($$prodAddr)->aveVtxs;

   $mflName = basename("$mflName", ".daq");
 
      $aflName[$ii] = $mflName;
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

 $xLabelSkip = 1;
$xLabelSkip = 2 if( scalar(@aDbId) > 20 );
$xLabelSkip = 4 if( scalar(@aDbId) > 40 );
$xLabelSkip = 8 if( scalar(@aDbId) > 80 );
$xLabelSkip = 10 if( scalar(@aDbId) > 100 );

my $qr = new CGI;

my $graph = new GIFgraph::linespoints(650,500);

if($plotVal eq "Memory_Size")   {
my @data = (\@aflName, \@aMemSize);

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

 my @data = (\@aflName, \@aCPUEvt);

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
 
 my @data = (\@aflName, \@aAveTrks);

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
 
 my @data = (\@aflName, \@aAveVtxs);

$xLabelsVertical = 1;

print $qr->header(-type => "image/gif");

$graph->set(x_label => "",
            y_label => "Average number of verteces", 
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







