#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id: dbDevTestQueryPlot.pl,v 1.48 2008/01/09 20:40:49 didenko Exp $
#
# $Log: dbDevTestQueryPlot.pl,v $
# Revision 1.48  2008/01/09 20:40:49  didenko
# updated due to moved directory
#
# Revision 1.47  2007/11/07 16:43:02  didenko
# last cleanup for working version
#
# Revision 1.39  2006/07/25 19:36:15  didenko
# more updates
#
# Revision 1.38  2006/07/21 19:22:02  didenko
# come back to previous version
#
# Revision 1.34  2006/07/21 18:55:44  didenko
# more fixes
#
# Revision 1.30  2006/04/14 16:20:23  didenko
# updated for tracks with nfit point > 15
#
# Revision 1.29  2005/01/10 18:02:43  didenko
# remove icc path
#
# Revision 1.23  2005/01/10 15:28:47  didenko
# updated for ITTF test
#
# Revision 1.22  2004/12/20 22:28:58  didenko
# more directories to query
#
# Revision 1.21  2004/12/20 21:35:55  didenko
# comment print
#
# Revision 1.20  2004/12/20 21:32:02  didenko
# updated for new datasets and SL3 platform
#
# Revision 1.19  2004/02/16 04:13:49  jeromel
# Small modifs (modules would need to be also installed in OPTSTAR)
#
# Revision 1.18  2002/10/11 15:13:42  didenko
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

require "/afs/rhic.bnl.gov/star/packages/scripts/dbLib/dbTJobsSetup.pl";

use CGI qw(:standard);
use GD;
use GD::Graph::linespoints;

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
                Average_NoTracksNfit15 => 'avg_no_tracksnfit15',
		Average_NoPrimaryTNfit15  => 'avg_no_primaryTnfit15',     
                Average_NoV0Vrt => 'avg_no_V0Vrt',
		Average_NoXiVrt => 'avg_no_XiVrt',
		Average_NoKinKVrt => 'avg_no_KinKVrt'
                );

my $set1    =  $query->param('set1');
my $plotVal = $query->param('plotVal');
my $weeks   = $query->param('weeks');

if ( ($set1 eq "") || ($plotVal eq "") ) {
    print $query->header;
    print $query->start_html('Plot for Nightly Test in DEV Library');
    print "<body bgcolor=\"cornsilk\"><center><pre>";
    print "<h1>You must select both the type of test and plot!!</h1>";
    print $query->end_html;
    exit(0);
}

my @point0 = ();
my @point1 = ();
my @point2 = ();
my @point3 = ();
my @point4 = ();
my @point5 = ();
my @point6 = ();
my @point7 = ();
my @point8 = ();

my @Nday;
for($i=0;$i<7*$weeks;$i++) {
    $point0[$i]=undef;
    $point1[$i]=undef;
    $point2[$i]=undef;
    $point3[$i]=undef;
    $point4[$i]=undef;
    $point5[$i]=undef;
    $point6[$i]=undef;
    $point7[$i]=undef;
    $Nday[$i] = undef;
}

  my @spl = ();
 @spl = split(" ",$plotVal);
 my $plotVl = $spl[0];

 my $mplotVal = $plotHash{$plotVl};

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
 

 $weeks = int($weeks);

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

  $day_diff = int($day_diff);
  $day_diff1 = int($day_diff1);

  my $sql;
	
  my $path;

  @spl = ();
  
   @spl = split(" ", $set1);
   $path = $spl[0];  
	$path =~ s(year)($Nday[$d_week]/year);
	$path =~ s(/)(%)g;

	    my $qupath = "%$path%";

	if ($n_weeks == 0) {

	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE ? AND avail='Y' AND jobStatus=\"Done\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < ? ORDER by createTime DESC LIMIT 5";

 	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($qupath,$day_diff);

	} else {
	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE ? AND jobStatus=\"Done\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < ? AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) > ? ORDER by createTime DESC LIMIT 5";


	$cursor = $dbh->prepare($sql) || die "Cannot prepare statement: $dbh->errstr\n";
	$cursor->execute($qupath,$day_diff, $day_diff1);

 }
	while(@fields = $cursor->fetchrow_array) {
            next if ( $fields[0] =~ /daq_sl302.icc80/) ;
	    if ($fields[0] =~ /sl302.ittf_opt/) {
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
           }elsif($fields[0] =~ /sl302_opt/) {
		$point4[$d_week+7*$rn_weeks] = $fields[1];
		if($point4[$d_week+7*$rn_weeks] > $max_y) {
		    $max_y = $point4[$d_week+7*$rn_weeks];
		}
		if($point4[$d_week+7*$rn_weeks] < $min_y) {
		    $min_y = $point4[$d_week+7*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point5[$d_week+7*$rn_weeks] = $fields[2];
		    if ($point5[$d_week+7*$rn_weeks] > $max_y) {
			$max_y = $point5[$d_week+7*$rn_weeks];
		    }
		    if ($point5[$d_week+7*$rn_weeks] < $min_y) {
			$min_y = $point5[$d_week+7*$rn_weeks];
		    }
		}
          }elsif($fields[0] =~ /sl302.ittf/) {
		$point6[$d_week+7*$rn_weeks] = $fields[1];
		if($point6[$d_week+7*$rn_weeks] > $max_y) {
		    $max_y = $point6[$d_week+7*$rn_weeks];
		}
		if($point6[$d_week+7*$rn_weeks] < $min_y) {
		    $min_y = $point6[$d_week+7*$rn_weeks];
		}
		if ($plotVal eq "MemUsage") {
		    $point7[$d_week+7*$rn_weeks] = $fields[2];
		    if ($point7[$d_week+7*$rn_weeks] > $max_y) {
			$max_y = $point7[$d_week+7*$rn_weeks];
		    }
		    if ($point7[$d_week+7*$rn_weeks] < $min_y) {
			$min_y = $point7[$d_week+7*$rn_weeks];
		    }
		}

	    }elsif($fields[0] =~ /sl302/) {
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
    @data = (\@Nday, \@point0, \@point1, \@point2, \@point3, \@point4, \@point5, \@point6, \@point7 );
    $legend[0] = "MemUsageF(tpt)";
    $legend[1] = "MemUsgaeL(tpt)";
    $legend[2] = "MemUsgaeF(ittf.optimized)";
    $legend[3] = "MemUsageL(tpt.optimized)";
    $legend[4] = "MemUsageF(tpt.optimized)";
    $legend[5] = "MemUsgaeL(ittf.optimized)";
    $legend[6] = "MemUsgaeF(ittf)";
    $legend[7] = "MemUsageL(ittf)";
    $mplotVal="MemUsageFirstEvent,MemUsageLastEvent";
} else {
    @data = (\@Nday, \@point0, \@point2, \@point4, \@point6 );
    $legend[0] = "$plotVal"."(tpt)";
    $legend[1] = "$plotVal"."(ittf.optimized)";
    $legend[2] = "$plotVal"."(tpt.optimized)";
    $legend[3] = "$plotVal"."(ittf)";
}


$graph = new GD::Graph::linespoints(550+50*$weeks,500);

 if ( ! $graph){
    print STDOUT $query->header(-type => 'text/plain');
    print STDOUT "Failed\n";
} else {

  my $format = $graph->export_format;
  print header("image/$format");
  binmode STDOUT;


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
		dclrs => [ qw(lblack lblue lred lgreen lpink lpurple lorange lyellow ) ],
		line_width => 2,
		markers => [ 2,3,4,5,6,7,8,9],
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

    print STDOUT $graph->plot(\@data)->$format();     
}


sub y_format
{
    my $value = shift;
    my $ret;

    $ret = sprintf("%8.2f", $value);
}
