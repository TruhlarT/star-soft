#!/opt/star/bin/perl -w
#
# $Id: dbDevTestQueryPlot.pl,v 1.6 2001/02/16 15:37:54 liuzx Exp $
#
# $Log: dbDevTestQueryPlot.pl,v $
# Revision 1.6  2001/02/16 15:37:54  liuzx
# .Add select for weeks,(default 1, max 4)
#
# Revision 1.5  2001/02/15 19:02:55  liuzx
# .Fixed the problem with Netscape's Cache!
#
# Revision 1.4  2001/02/14 23:16:39  liuzx
# .Update for description of MemUsage
# .Update for 0 value's meaning
#
# Revision 1.3  2001/02/14 19:58:19  liuzx
# Modify the min_y and skip no data now!
#
# Revision 1.2  2001/02/14 18:18:39  liuzx
# Missing max_y added!
#
# Revision 1.1  2001/02/14 16:59:37  liuzx
# Initial Version: query for nightly test in DEV library.
#                   (currently only last five days)
#
#
##########################################################

require "/afs/rhic/star/packages/DEV00/mgr/dbTJobsSetup.pl";

use CGI;
use GIFgraph::linespoints;
use GD;
#use strict;
#use CGI::Carp qw(fatalsToBrowser);
#use Class::Struct;
#use File::Basename;


my $query = new CGI;

print $query->header;
print $query->start_html('Plot for Nightly Test in DEV Library');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

print "<body bgcolor=\"#ffdc9f\"><center><pre>";

my $day_diff = 8;
my $max_y = 0, $min_y = 500000;
#my @point0, @point1, @point2, @point3;
#my @point0 = (undef,undef,undef,undef,undef);
#my @point1 = (undef,undef,undef,undef,undef);
#my @point2 = (undef,undef,undef,undef,undef);
#my @point3 = (undef,undef,undef,undef,undef);
my @data;
my @legend;

#print <<END;
#<META HTTP-equiv="Refresh" content="0; URL-HTTP://duvall.star.bnl.gov/cgi-bin/liuzx/star/dbDevTestQueryPlot.pl">
#END

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
#$datProd = $query->param('datProd');
my $plotVal = $query->param('plotVal');
my $weeks = $query->param('weeks');

if ( ($set1 eq "") || ($plotVal eq "") ) {
    print "<h1>You must select both the type of test and plot!!</h1>";
    print $query->end_html;
    exit(0);
}

my @Nday;
#if(! defined $datProd) { $datProd = 0};
for($i=0;$i<5*$weeks;$i++) {
    $point0[$i]=undef;
    $point1[$i]=undef;
    $point2[$i]=undef;
    $point3[$i]=undef;
    $Nday[$i] = undef;
}

my $mplotVal = $plotHash{$plotVal};

($sec,$min,$hour,$mday,$mon,$year,$today,$today,$today) = localtime(time);
#                                 $wday,$yday,$isdst
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

#print $query->header;
#print $query->start_html('Select Query for Production Plots');

#print "<pre>";

#print $datProd, "\n";
#print $mplotVal, "\n";
#print $set1, "\n";

my $n_weeks = $weeks - 1;
#for($n_weeks=$weeks-1; $n_week>=0;$n_week--) {
while($n_weeks >= 0) {
    my $rn_weeks = $weeks-1-$n_weeks;
    #my $nowdate = ($year+1900)."-".($mon+1)."-".($mday-7*$n_weeks);
    #print $n_weeks,"\t",$rn_weeks,"\n";
    for ($d_week = 0; $d_week <=4; $d_week++) {
	#print $d_week,"\n";
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

	#$path = $dbh->quote($path);
	if ($n_weeks == 0) {
	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE \"%$path%\" AND avail='Y' AND jobStatus=\"Done\" AND errMessage=\"none\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < $day_diff ORDER by createTime DESC LIMIT 2";
	} else {
	    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE \"%$path%\" AND jobStatus=\"Done\" AND errMessage=\"none\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < $day_diff AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) > $day_diff1 ORDER by createTime DESC LIMIT 2";
	}

	#print $sql,"\n";
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
		#print "opt ",$point2[$d_week],"\t",$point3[$d_week],"\n";
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
		#print $point0[$d_week],"\t",$point1[$d_week],"\n";
	    }
	    #print $point0[$d_week],"\t",$point1[$d_week],"\n";
	    #my $cols=$cursor->{NUM_OF_FIELDS};
	    #for($i=0;$i<$cols;$i++) {
	    #    print $fields[$i], "\t";
	    #}
	    #print "\n";
	}
    }
    $n_weeks--;
}

&StDbTJobsDisconnect();

my $xlable = "";

if( $min_y == 0) {
    $min_y = 10;
    $xlabel = "(0 value means job failed)";
} elsif (($min_y < 10)&& ($min_y != 0) ) {
    $min_y = 10;
}

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

#binmode STDOUT;
#print STDOUT $query->header(-type => 'image/gif');

$graph = new GIFgraph::linespoints(550+50*$weeks,500);

$graph->set(x_label => "$xlabel",
            #y_label => "$mplotVal",
	    x_label_position => 0.5,
            title   => "$set1"." ($mplotVal)",
	    y_tick_number => 10,
            y_min_value => $min_y-10,
            y_max_value => $max_y+1+($max_y-$min_y)/16.0,
	    labelclr => "lred",
	    dclrs => [ qw(lred lgreen lblue lpurple) ],
	    line_width => 2,
	    markers => [ 2,4,6,8],
	    marker_size => 6
	    );

$graph->set_legend(@legend);
$graph->set_legend_font(gdMediumBoldFont);
$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
#print STDOUT $graph->plot(\@data);

`rm -fr /star/starlib/doc/www/html/comp-nfs/plot*.gif`;
my $gif = "/star/starlib/doc/www/html/comp-nfs/plot".$sec.$min.$hour.".gif";
$graph->plot_to_gif("$gif",\@data);

#open (GRAPH,"$gif");
#while($line = <GRAPH>) {
#	print STDOUT $line;
#	}
print "</pre>";
print "<img src=\"http://www.star.bnl.gov/webdata/plot".$sec.$min.$hour.".gif\"></center>";
print $query->end_html;
