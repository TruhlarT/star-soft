#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# $Log: GifMdc3Plots.pl
# 
# L.Didenko
# Script to create plots for production operation
#================================================================== 

require "/afs/rhic/star/packages/scripts/dbCpProdSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;
use Class::Struct;
use File::Basename;

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


 my ($query) = @_;
 
$query = new CGI;

print <<END;
<META HTTP-equiv="Refresh" content="1; URL-HTTP://www.star.bnl.gov/cgi-bin/didenko/mdc3PlotReq.pl">
END


my $mplotVal;
my %plotHash = (
             Memory_size => 'mem_size_MB', 
             CPU_per_Event => 'CPU_per_evt_sec',
             Average_NoTracks => 'avg_no_tracks',
             Average_NoVertices => 'avg_no_vertex',   
             RealTime_per_Event => 'RealTime_per_evt'
);
  
 $set1   =  $query->param('set1');
 $datProd = $query->param('datProd');
 $plotVal = $query->param('plotVal');

if(! defined $datProd) { $datProd = 0};
 
 $datProd = 0; 
 $mplotVal = $plotHash{$plotVal};

my $jobset = $set1;
   $jobset =~ s/\//_/g;   
  
#open (STDOUT,">Error_check");

#print $set1, "\n";
#print $plotVal, "\n";
#print $datProd, "\n";
#print $mplotVal, "\n";
#print $jobset, "\n"; 

#close (STDOUT);

struct Products => {
   flName    => '$',
    dset     => '$',
    memSize   => '$',
    cpuEvt    => '$', 
    rtEvt     => '$',
    aveTrks   => '$',
    aveVtxs   => '$',
};


my @prodInfo;
my $nProdInfo = 0;
my $mjobSt;

my @dstFile;
my $ndstFile = 0;
my $mcpuEvt = 0;

&StDbProdConnect();

my $sql;

  if( $datProd eq 0) { 

 if( $set1 ne "all" ) {
$sql="SELECT sumFileName,jobfileName, jobStatus, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex, RealTime_per_evt FROM $JobStatusT WHERE jobfileName LIKE '$jobset%' AND JobID LIKE '%mdc3%' AND jobStatus <>'n/a'"; 
}
elsif ( $set1 eq "all") {
$sql="SELECT sumFileName,jobfileName, jobStatus, mem_size_MB, CPU_per_evt_sec, avg_no_tracks, avg_no_vertex, RealTime_per_evt FROM $JobStatusT WHERE JobID LIKE '%mdc3%' AND jobStatus <> 'n/a'";
}

  $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute;
    while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS}; 

        $prodAddr = \(Products->new());
      my  $mjobSt = "n/a";
    for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];
#     print "$fname = $fvalue\n";
        ($$prodAddr)->flName($fvalue) if( $fname eq 'sumFileName');
        ($$prodAddr)->dset($fvalue)   if($fname eq 'jobfileName'); 
        ($$prodAddr)->memSize($fvalue) if( $fname eq 'mem_size_MB');
        ($$prodAddr)->cpuEvt($fvalue) if( $fname eq 'CPU_per_evt_sec');
        ($$prodAddr)->rtEvt($fvalue) if( $fname eq 'RealTime_per_evt');
        ($$prodAddr)->aveTrks($fvalue) if( $fname eq 'avg_no_tracks'); 
        ($$prodAddr)->aveVtxs($fvalue) if( $fname eq 'avg_no_vertex');   
        $mjobSt = $fvalue if ( $fname eq 'jobStatus');       
        $mcpuEvt =  $fvalue if ( $fname eq 'CPU_per_evt_sec');
    }       
        next if ( $mcpuEvt = 0 );
      $prodInfo[$nProdInfo] = $prodAddr;      
      $nProdInfo++;
}
}
  elsif ($datProd ne 0) {
  if ($set1 ne "all") {
$sql="SELECT fName, dataset FROM $FileCatalogT WHERE dataset = '$set1' AND fName LIKE '%dst.root' AND jobID LIKE '%mdc3%' AND createTime LIKE '$datProd%'";
}
  elsif($set1 eq "all") {
$sql="SELECT fName, dataset FROM $FileCatalogT WHERE fName LIKE '%dst.root' AND jobID LIKE '%mdc3%' AND createTime LIKE '$datProd%'";
}

  $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute;
    while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};

        $prodAddr = \(Products->new());
      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];
#      print "$fname = $fvalue\n";
        ($$prodAddr)->flName($fvalue) if( $fname eq 'fName');
        ($$prodAddr)->dset($fvalue)   if($fname eq 'dataset');

} 
       $dstFile[$ndstFile] = $prodAddr;
       $ndstFile++;
}
}

#===================================================================================================
# can loop over set here. for the moment, just deal with one set.

my ($second, $minute, $hour, $day, $month ,$year) = (localtime())[0,1,2,3,4,5];
$month +=1;
my $timeS = sprintf ("%2.2d%2.2d%2.2d%2.2d%2.2d%2.2d", 
                       $year,$month,$day,$hour,$minute,$second);
my $msetnm = "n\/a";
my $mflName = "n\/a";
my $mDbId = "n\/a";
my $mMemSize = 0;
my $mCPUEvt = 0;
my $mRTEvt = 0;
my $mAveTrks = 0;
my $mAveVtxs = 0;

my @aflName;
my @aDbId;
my @aMemSize;
my @aCPUEvt;
my @aRTEvt;
my @aAveTrks;
my @aAveVtxs;
my $fileAddr;
my $dsflName;
my $dstset;

my $ii = 0;

foreach $prodAddr (@prodInfo) {
    $mflName = ($$prodAddr)->flName; 
    $msetnm  = ($$prodAddr)->dset; 
    $mMemSize = ($$prodAddr)->memSize;
    $mCPUEvt  = ($$prodAddr)->cpuEvt;
    $mRTEvt =  ($$prodAddr)->rtEvt;
    $mAveTrks = ($$prodAddr)->aveTrks;
    $mAveVtxs = ($$prodAddr)->aveVtxs;
     if ($mCPUEvt != 0)  { 
  $mflName = basename("$mflName", ".sum");

  if ($datProd ne 0) {
     foreach $fileAddr (@dstFile) {
      $dsflName = ($$fileAddr)->flName; 
      $dstset = ($$fileAddr)->dset;
       
      if ( $dsflName =~ /$mflName/) {

      $aflName[$ii] = $mflName;
      $aMemSize[$ii] = $mMemSize;
      $aCPUEvt[$ii] = $mCPUEvt;
      $aRTEvt[$ii] = $mRTEvt;
      $aAveTrks[$ii] = $mAveTrks;
      $aAveVtxs[$ii] = $mAveVtxs;      
      $ii++;      
} else {
  next;
}
    }
   }else{
      $aflName[$ii] = $mflName;
      $aMemSize[$ii] = $mMemSize;
      $aCPUEvt[$ii] = $mCPUEvt;
      $aRTEvt[$ii] = $mRTEvt;
      $aAveTrks[$ii] = $mAveTrks;
      $aAveVtxs[$ii] = $mAveVtxs;      
# print $aflName[$ii], $aMemSize[$ii], "\n";
    $ii++;
    }
  } 
 }
#close (STDOUT);
&StDbProdDisconnect();
#========================================================================================
my @markerList = (3,4,1,2,5,6,7,8);
my $marketSize = 4;
my $xLabelSkip = 4;
my $lineWidth = 5;
my $xLabelsVertical = 1;
my $xLabelPosition = 0;

$xLabelSkip = 1;
$xLabelSkip = 2 if( scalar(@aflName) > 20 );
$xLabelSkip = 4 if( scalar(@aflName) > 40 );
$xLabelSkip = 8 if( scalar(@aflName) > 80 );
$xLabelSkip = 10 if( scalar(@aflName) > 100);
$xLabelSkip = 20 if( scalar(@aflName) > 200);
$xLabelSkip = 30 if( scalar(@aflName) > 300);

my $qr = new CGI;

my $graph = new GIFgraph::linespoints(650,500);

if($plotVal eq "Memory_size")   {
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

elsif($plotVal eq "CPU_per_Event") {

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
##### Average Real Time per Event

elsif($plotVal eq "RealTime_per_Event") {

 my @data = (\@aflName, \@aRTEvt);

$xLabelsVertical = 1;

print $qr->header(-type => "image/gif");

$graph = new GIFgraph::linespoints(650,560);

$graph->set(x_label => "",
            y_label => "Real Time per event(seconds)", 
            title   => "$set1",
            markers => \@markerList,
            line_width => $lineWidth,
            x_label_skip => $xLabelSkip,
            y_min_value => 0,
            y_max_value => 1400,
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

elsif ( $plotVal eq "Average_NoTracks") {
 
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

##### Average number of vertices

elsif ( $plotVal eq "Average_NoVertices") {
 
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







