#!/opt/star/bin/perl -w
#
# $Id: dbDevTestQueryPlot.pl,v 1.17 2002/10/11 14:50:16 didenko Exp $
#
# $Log: dbDevTestQueryPlot.pl,v $
# Revision 1.17  2002/10/11 14:50:16  didenko
# *** empty log message ***
#
# Revision 1.14  2002/01/30 17:39:55  didenko
# extand week days for Sat, Sun
#
# Revision 1.12  2001/06/07 17:08:18  jeromel
# Change DEV00 -> dev
#
# Revision 1.11  2001/02/27 16:38:05  liuzx
# max_y and min_y changed! (9th and 6th ticks)
#
# Revision 1.10  2001/02/23 00:46:06  liuzx
# Now output the GIF on the fly!
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

require "/afs/rhic/star/packages/scripts/dbTJobsSetup.pl";

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
for($i=0;$i<7*$weeks;$i++) {
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
    $Nday[0] = "Tue"; $Nday[1] = "Wed"; $Nday[2] = "Thu"; $Nday[3] = "Fri"; $Nday[4] = "Sat"; $Nday[5] = "Sun"; $Nday[6] = "Mon";
} elsif ( $today eq Wed ) {
    $Nday[6] = "Tue"; $Nday[0] = "Wed"; $Nday[1] = "Thu"; $Nday[2] = "Fri"; $Nday[3] = "Sat"; $Nday[4] = "Sun"; $Nday[5] = "Mon";
} elsif ( $today eq Thu ) {
    $Nday[5] = "Tue"; $Nday[6] = "Wed"; $Nday[0] = "Thu"; $Nday[1] = "Fri"; $Nday[2] = "Sat"; $Nday[3] = "Sun"; $Nday[4] = "Mon";
} elsif ( $today eq Fri ) {
    $Nday[4] = "Tue"; $Nday[5] = "Wed"; $Nday[6] = "Thu"; $Nday[0] = "Fri"; $Nday[1] = "Sat"; $Nday[2] = "Sun"; $Nday[3] = "Mon";
} elsif ( $today eq Sat ) {
    $Nday[3] = "Tue"; $Nday[4] = "Wed"; $Nday[5] = "Thu"; $Nday[6] = "Fri"; $Nday[0] = "Sat"; $Nday[1] = "Sun"; $Nday[2] = "Mon";
} elsif ( $today eq Sun ) {
    $Nday[2] = "Tue"; $Nday[3] = "Wed"; $Nday[4] = "Thu"; $Nday[5] = "Fri"; $Nday[6] = "Sat"; $Nday[0] = "Sun"; $Nday[1] = "Mon";
} else {
    $Nday[1] = "Tue"; $Nday[2] = "Wed"; $Nday[3] = "Thu"; $Nday[4] = "Fri"; $Nday[5] = "Sat"; $Nday[6] = "Sun"; $Nday[0] = "Mon";
}
for($i=1;$i<$weeks;$i++) {
    for($j=0;$j<7;$j++) {
	$Nday[$j+7*$i] = $Nday[$j];
    }
}

&StDbTJobsConnect();

my $n_weeks = $weeks - 1;
while($n_weeks >= 0) {
    my $rn_weeks = $weeks-1-$n_weeks;
    for ($d_week = 0; $d_week <=6; $d_week++) {
	    if($d_week eq 0) {
		$day_diff = 8;
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
		$point2[$d_week+7*$rn_weeks] = $fields[1];
		if($point2[$d_week+7*$rn_weeks] > $max_y) {
		    $max_y = $point2[$d_week+7*$rn_weeks];
		}
		if($point2[$d_week+7*$rn_weeks] < $min_y) {
		    $min_y = $point2[$d_week+7*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point3[$d_week+7*$rn_weeks] = $fields[2];
		    if ($point3[$d_week+7*$rn_weeks] > $max_y) {
			$max_y = $point3[$d_week+7*$rn_weeks];
		    }
		    if ($point3[$d_week+7*$rn_weeks] < $min_y) {
			$min_y = $point3[$d_week+7*$rn_weeks];
		    }
		}
	    } else {
		$point0[$d_week+7*$rn_weeks] = $fields[1];
		if ($point0[$d_week+7*$rn_weeks] > $max_y) {
		    $max_y = $point0[$d_week+7*$rn_weeks];
		}
		if ($point0[$d_week+7*$rn_weeks] < $min_y) {
		    $min_y = $point0[$d_week+7*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point1[$d_week+7*$rn_weeks] = $fields[2];
		    if ($point1[$d_week+7*$rn_weeks] > $max_y) {
			$max_y = $point1[$d_week+7*$rn_weeks];
		    }
		    if ($point1[$d_week+7*$rn_weeks] < $min_y) {
			$min_y = $point1[$d_week+7*$rn_weeks];
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
    $graph->set(x_label => "(0 value means job failed)");
} else {
    # keep the min_y in the 6th ticks (6/3)
    $min_y = $min_y - ($max_y-$min_y)*2.0;
}

# keep the max_y in the 9th ticks
$max_y = $max_y + ($max_y - $min_y)/9.0;

if($max_y eq $min_y) {
    $max_y += 1;
    $min_y -= 1;
}

if($min_y < 0) {
    $min_y = 0;
}

$graph->set(#x_label => "$xlabel",
            #y_label => "$mplotVal",
	    x_label_position => 0.5,
            title   => "$set1"." ($mplotVal)",
	    y_tick_number => 10,
            y_min_value => $min_y,
            y_max_value => $max_y,
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
