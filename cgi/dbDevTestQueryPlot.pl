#!/opt/star/bin/perl 
#-w
#
# $Id: dbDevTestQueryPlot.pl,v 1.1 2001/02/14 16:59:37 liuzx Exp $
#
# $Log: dbDevTestQueryPlot.pl,v $
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
#use CGI::Carp qw(fatalsToBrowser);
#use Class::Struct;
#use File::Basename;


my $query = new CGI;

my @Nday;
my $day_diff = 8;
my $max_y = 0;
my @point0 = (0,0,0,0,0);
my @point1 = (0,0,0,0,0);
my @point2 = (0,0,0,0,0);
my @point3 = (0,0,0,0,0);
my @data;
my @legend;

print <<END;
<META HTTP-equiv="Refresh" content="0; URL-HTTP://duvall.star.bnl.gov/cgi-bin/liuzx/star/dbDevQueryPlot.pl">
END

my $mplotVal;
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

$set1   =  $query->param('set1');
#$datProd = $query->param('datProd');
$plotVal = $query->param('plotVal');

#if(! defined $datProd) { $datProd = 0};

$mplotVal = $plotHash{$plotVal};

($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
$today = (Sun,Mon,Tue,Wed,Thu,Fri,Sat)[(localtime)[6]];
my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

if ( $today eq Sun ) {
    @Nday = ("Mon","Tue","Wed","Thu","Fri");
} elsif ( $today eq Mon ) {
    @Nday = ("Mon","Tue","Wed","Thu","Fri");
} elsif ( $today eq Tue ) {
    @Nday = ("Tue","Wed","Thu","Fri","Mon");
} elsif ( $today eq Wed ) {
    @Nday = ("Wed","Thu","Fri","Mon","Tue");
} elsif ( $today eq Thu ) {
    @Nday = ("Thu","Fri","Mon","Tue","Wed");
} elsif ( $today eq Fri ) {
    @Nday = ("Fri","Mon","Tue","Wed","Thu");
} elsif ( $today eq Sat ) {
    @Nday = ("Mon","Tue","Wed","Thu","Fri");
}

&StDbTJobsConnect();

#print $query->header;
#print $query->start_html('Select Query for Production Plots');

#print "<pre>";

#print $datProd, "\n";
#print $mplotVal, "\n";
#print $set1, "\n";

for ($d_week = 0; $d_week <=4; $d_week++) {
    if ($today eq Fri) {
	if($d_week eq 0) {
	    $day_diff = 8;
	} else {
	    $day_diff = 6-$d_week;
	}
    } elsif ($today eq Sat) {
	$day_diff = 6-$d_week;
    } elsif ($today eq Sun) {
	$day_diff = 7-$d_week;
    } else {
	$day_diff = 8-$d_week;
    }

    my $sql;
    
    my $path = $set1;
    $path =~ s(year)($Nday[$d_week]/year);
    #print $path, "\n";
    $path =~ s(/)(%)g;

    #$path = $dbh->quote($path);

    $sql="SELECT path, $mplotVal FROM JobStatus WHERE path LIKE \"%$path%\" AND avail='Y' AND jobStatus=\"Done\" AND errMessage=\"none\" AND (TO_DAYS(\"$nowdate\") -TO_DAYS(createTime)) < $day_diff ORDER by createTime DESC LIMIT 2";

    #print $sql,"\n";
    $cursor = $dbh->prepare($sql);
# || die "Cannot prepare statement: $DBI::errstr\n";

    $cursor->execute;
    my $blank = 0;
    while(@fields = $cursor->fetchrow_array) {
	if ($fields[0] =~ /opt/) {
	    $blank ++;
	    $point2[$d_week] = $fields[1];
	    if ($plotVal eq "MemUsage") {
		$point3[$d_week] = $fields[2];
	    }
	    #print "opt ",$point2[$d_week],"\t",$point3[$d_week],"\n";
	} else {
	    $blank ++;
	    $point0[$d_week] = $fields[1];
	    if ($point0[$d_week] > $max_y) {
		$max_y = $point0[$d_week];
	    }
	    if ($plotVal eq "MemUsage") {
		$point1[$d_week] = $fields[2];
		if ($point1[$d_week] > $max_y) {
		    $max_y = $point1[$d_week];
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

    if ($blank eq 0) {
	$Nday[$d_week] = $Nday[$d_week]." (NULL)";
    }
}

&StDbTJobsDisconnect();

if ($plotVal eq "MemUsage") {
    @data = (\@Nday, \@point0, \@point1, \@point2, \@point3);
    $legend[0] = "MemUsageF";
    $legend[1] = "MemUsgaeL";
    $legend[2] = "MemUsgaeF(opt)";
    $legend[3] = "MemUsageL(opt)";
} else {
    @data = (\@Nday, \@point0, \@point2);
    $legend[0] = "$plotVal";
    $legend[1] = "$plotVal"."(opt)";
}

binmode STDOUT;
print STDOUT $query->header(-type => 'image/gif');

$graph = new GIFgraph::linespoints(600,500);

$graph->set(x_label => "",
            y_label => "$mplotVal",
            title   => "$set1"." ($mplotVal)",
	    y_tick_number => 10,
            y_min_value => 0,
            y_max_value => $max_y + 10,
	    );

$graph->set_legend(@legend);
$graph->set_legend_font(gdMediumBoldFont);
$graph->set_title_font(gdMediumBoldFont);
$graph->set_x_label_font(gdMediumBoldFont);
$graph->set_y_label_font(gdMediumBoldFont);
$graph->set_x_axis_font(gdMediumBoldFont);
$graph->set_y_axis_font(gdMediumBoldFont);
print STDOUT $graph->plot(\@data);
#print "</pre>";
#print $query->end_html;
