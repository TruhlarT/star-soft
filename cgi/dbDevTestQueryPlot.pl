#!/opt/star/bin/perl -w
#
# $Id: dbDevTestQueryPlot.pl,v 1.10 2001/02/23 00:46:06 liuzx Exp $
#
# $Log: dbDevTestQueryPlot.pl,v $
# Revision 1.10  2001/02/23 00:46:06  liuzx
# Now output the GIF on the fly!
#
#
##########################################################

require "/afs/rhic/star/packages/DEV00/mgr/dbTJobsSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;


my $query = new CGI;

my $day_diff = 8;
my $max_y = 0, $min_y = 500000;
my @data;
my @legend;

my %plotHash = (
                MemUsage => 'memUsageF, memUsageL',
                CPU_per_Event => 'CPU_per_evt_sec',
		RealTime_per_Event => 'RealTime_per_evt',
                Average_NoTracks => 'avg_no_tracks',
		Average_NoPrimaryT => 'avg_no_primaryT',
                Average_NoV0Vrt => 'avg_no_V0Vrt',
		Average_NoXiVrt => 'avg_no_XiVrt',
		Average_NoKinKVrt => 'avg_no_KinKVrt'
                );

my $set1   =  $query->param('set1');
my $plotVal = $query->param('plotVal');
my $weeks = $query->param('weeks');

if ( ($set1 eq "") || ($plotVal eq "") ) {
    print $query->header;
    print $query->start_html('Plot for Nightly Test in DEV Library');
    print "<body bgcolor=\"#ffdc9f\"><center><pre>";
    print "<h1>You must select both the type of test and plot!!</h1>";
    print $query->end_html;
    exit(0);
}

my @Nday;
for($i=0;$i<5*$weeks;$i++) {
    $point0[$i]=undef;
    $point1[$i]=undef;
    $point2[$i]=undef;
    $point3[$i]=undef;
    $Nday[$i] = undef;
}

my $mplotVal = $plotHash{$plotVal};

($today,$today,$today,$mday,$mon,$year,$today,$today,$today) = localtime(time);
#$sec,$min,$hour                  $wday,$yday,$isdst
$today = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];
my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

if ( $today eq Tue ) {
    $Nday[0] = "Tue"; $Nday[1] = "Wed"; $Nday[2] = "Thu"; $Nday[3] = "Fri"; $Nday[4] = "Mon";
} elsif ( $today eq Wed ) {
    $Nday[4] = "Tue"; $Nday[0] = "Wed"; $Nday[1] = "Thu"; $Nday[2] = "Fri"; $Nday[3] = "Mon";
} elsif ( $today eq Thu ) {
    $Nday[3] = "Tue"; $Nday[4] = "Wed"; $Nday[0] = "Thu"; $Nday[1] = "Fri"; $Nday[2] = "Mon";
} elsif ( $today eq Fri ) {
    $Nday[2] = "Tue"; $Nday[3] = "Wed"; $Nday[4] = "Thu"; $Nday[0] = "Fri"; $Nday[1] = "Mon";
} else {
    $Nday[1] = "Tue"; $Nday[2] = "Wed"; $Nday[3] = "Thu"; $Nday[4] = "Fri"; $Nday[0] = "Mon";
}

for($i=1;$i<$weeks;$i++) {
    for($j=0;$j<5;$j++) {
	$Nday[$j+5*$i] = $Nday[$j];
    }
}

&StDbTJobsConnect();

my $n_weeks = $weeks - 1;
while($n_weeks >= 0) {
    my $rn_weeks = $weeks-1-$n_weeks;
    for ($d_week = 0; $d_week <=4; $d_week++) {
	if ($today eq "Fri") {
	    if($d_week eq 0) {
		$day_diff = 8;
	    } else {
		$day_diff = 6-$d_week;
	    }
	} elsif ($today eq "Sat") {
	    $day_diff = 6-$d_week;
	} elsif ($today eq "Sun") {
	    $day_diff = 7-$d_week;
	} else {
	    $day_diff = 8-$d_week;
	}
	$day_diff = $day_diff + 7*$n_weeks;
	$day_diff1 = 7*$n_weeks;
	my $sql;
	
	my $path = $set1;
	$path =~ s(year)($Nday[$d_week]/year);
	#print $path, "\n";
	$path =~ s(/)(%)g;

	if ($n_weeks == 0) {
	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE \"%$path%\" AND avail='Y' AND jobStatus=\"Done\" AND errMessage=\"none\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < $day_diff ORDER by createTime DESC LIMIT 2";
	} else {
	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE \"%$path%\" AND jobStatus=\"Done\" AND errMessage=\"none\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < $day_diff AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) > $day_diff1 ORDER by createTime DESC LIMIT 2";
	}

	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute;
	while(@fields = $cursor->fetchrow_array) {
	    if ($fields[0] =~ /opt/) {
		$point2[$d_week+5*$rn_weeks] = $fields[1];
		if($point2[$d_week+5*$rn_weeks] > $max_y) {
		    $max_y = $point2[$d_week+5*$rn_weeks];
		}
		if($point2[$d_week+5*$rn_weeks] < $min_y) {
		    $min_y = $point2[$d_week+5*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point3[$d_week+5*$rn_weeks] = $fields[2];
		    if ($point3[$d_week+5*$rn_weeks] > $max_y) {
			$max_y = $point3[$d_week+5*$rn_weeks];
		    }
		    if ($point3[$d_week+5*$rn_weeks] < $min_y) {
			$min_y = $point3[$d_week+5*$rn_weeks];
		    }
		}
	    } else {
		$point0[$d_week+5*$rn_weeks] = $fields[1];
		if ($point0[$d_week+5*$rn_weeks] > $max_y) {
		    $max_y = $point0[$d_week+5*$rn_weeks];
		}
		if ($point0[$d_week+5*$rn_weeks] < $min_y) {
		    $min_y = $point0[$d_week+5*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point1[$d_week+5*$rn_weeks] = $fields[2];
		    if ($point1[$d_week+5*$rn_weeks] > $max_y) {
			$max_y = $point1[$d_week+5*$rn_weeks];
		    }
		    if ($point1[$d_week+5*$rn_weeks] < $min_y) {
			$min_y = $point1[$d_week+5*$rn_weeks];
		    }
		}
	    }
	}
    }
    $n_weeks--;
}

&StDbTJobsDisconnect();

if ($plotVal eq "MemUsage") {
    @data = (\@Nday, \@point0, \@point1, \@point2, \@point3);
    $legend[0] = "MemUsageF";
    $legend[1] = "MemUsgaeL";
    $legend[2] = "MemUsgaeF(opt)";
    $legend[3] = "MemUsageL(opt)";
    $mplotVal="MemUsageFirstEvent,MemUsageLastEvent";
} else {
    @data = (\@Nday, \@point0, \@point2);
    $legend[0] = "$plotVal";
    $legend[1] = "$plotVal"."(opt)";
}

binmode STDOUT;

print STDOUT $query->header(-type => 'image/gif');

$graph = new GIFgraph::linespoints(550+50*$weeks,500);

if( $min_y == 0) {
    $min_y = 10;
    $graph->set(x_label => "(0 value means job failed)");
} elsif (($min_y < 10)&& ($min_y != 0) ) {
    $min_y = 10;
}

$graph->set(#x_label => "$xlabel",
            #y_label => "$mplotVal",
	    x_label_position => 0.5,
            title   => "$set1"." ($mplotVal)",
	    y_tick_number => 10,
            y_min_value => $min_y-10,
            y_max_value => $max_y+1+($max_y-$min_y)/16.0,
	    y_number_format => \&y_format,
	    labelclr => "lred",
	    dclrs => [ qw(lred lgreen lblue lpurple) ],
	    line_width => 2,
	    markers => [ 2,4,6,8],
	    marker_size => 6,
	    #long_ticks => 1
	    );

$graph->set_legend(@legend);
$graph->set_legend_font(gdMediumBoldFont);
$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
print STDOUT $graph->plot(\@data);

sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}
