#! /usr/local/bin/perl -w
#
# L. Didenko
###############################################################################

my $prodSer = $ARGV[0];  
my $CRSDIR  = "/home/starreco/newcrs/bin";
my $jobdir  = "/home/starreco/newcrs/" . $prodSer ."/requests/daq/jobfiles";
my $archdir = "/home/starreco/newcrs/" . $prodSer ."/requests/daq/archive";

my @statlist = ();
my @jobslist = ();
my $timestamp ;

@statlist = `$CRSDIR/farmstat`;

my $Ncreate = 0;

my $n1 = 0;
my $nlast = 0;
my $jbfile;
my @prt = ();
my $year;

($sec,$min,$hour,$mday,$mon,$yr) = localtime();

    $mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $min = '0'.$sec };

$year = $yr + 1900;

$timestamp = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

print $timestamp, "\n";

foreach $line (@statlist) {
    chop $line ;
#   print  $line, "\n";
    @prt = ();
    @prt = split (" ", $line);
    if ($prt[0] eq "CREATED") {
	$Ncreate =  $prt[1];
    }
}


if($Ncreate <= 1000) {

#    chdir $jobdir;
  chdir($jobdir) || die "Could not chdir to $jobdir\n";

    @jobslist = `/bin/ls`;

    $nlast = scalar(@jobslist);

    if ($nlast <= 1) {
	print "No more jobs in the directory", "\n";
    }

    if($nlast >= 1001) { 
	$n1 = scalar(@jobslist) - 1000;     
	if ($n1 < 0){ $n1 = 0;}
    } else {
	$n1 = 0;
    }

    for ( $kk = $n1; $kk<$nlast; $kk++) {
	$jbfile = $jobslist[$kk];
	chop $jbfile ;
        if ( -f $jbfile) {
	print  $jbfile, "\n";
	`$CRSDIR/crs_job -create $jbfile -q4 -p20 -drop`;
	`/bin/mv $jbfile $archdir`;
       } else {
                print "[?] $jbfile is not a file\n";
        }
	
    }
} else {
    print "No new jobs submitted", "\n";
}

exit;

