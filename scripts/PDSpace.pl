#!/usr/local/bin/perl

#
# Get a detail of the space on each disks
# Look 2 directory deep for what is there assuming
#
# $0 > /afs/rhic/star/doc/www/html/tmp/pub/overall.html
#

#
# List of disks will be by numbers
#
$MIN   =  5;
$MAX   =  6;  # for testing
$MAX   = 27;
$MAIN  = "/star/data";

@COLORS = ("#cceecc","#ddffdd","#ccccee","#ddbbbb");


for ( $i = $MIN ; $i <= $MAX ; $i++){
    push(@DISKS,sprintf("$MAIN%2.2d",$i));
}

foreach $disk (@DISKS){
    chomp($res = `df -k $disk | grep % | grep '/'`);
    $res =~ s/^\s*(.*?)\s*$/$1/;
    $res =~ s/\s+/ /g;
    @items = split(" ",$res);

    #print STDERR "$disk $res\n";

    if ($#items < 5){
	$tota = $items[0];
	$used = $items[1];
	$avai = $items[2];
	$prct = $items[3];
    } else {
	$tota = $items[1];
	$used = $items[2];
	$avai = $items[3];
	$prct = $items[4];
    }
    # Now scan the disk for a reco directory
    undef(@TRGS);
    undef(%LIBS);

    if( -d "$disk/reco"){
	@TMP = glob("$disk/reco*/*");
	foreach $trg (@TMP){
	    #print "Found $trg\n";
	    if ($trg =~ /StarDb/){ next;}
	    $tmp = $trg;
	    $tmp =~ s/.*\///;
	    push (@TRGS,$tmp);
	    @vers = glob("$trg/*/*");
	    foreach $ver (@vers){
		#print "\tFound $ver\n";
		$ver =~ s/.*\///;
		$LIBS{$ver} = 1;
	    }
	}

    }
    

    $DINFO{$disk} = "$tota;$used;$avai;$prct;";
    $trg = " ";
    foreach $tmp (@TRGS){
	$trg .= "$tmp ";
    }
    if ( -e "$disk/AAAREADME"){
	@all = `cat $disk/AAAREADME`;
	$DINFO{$disk} .= "<B><PRE>".join("",@all)."</PRE></B>";
    }
    $DINFO{$disk} .= "$trg;";

    $ver = " ";
    foreach $tmp (keys %LIBS){
	$ver .= "$tmp ";
    }
    $DINFO{$disk} .= "$ver;";
}

if ( defined($ARGV[0]) ){
    open(FO,">$ARGV[0]-tmp") || die "Could not open $ARGV[0]-tmp\n";
    $FO = FO;
} else {
    $FO = STDOUT;
}

print $FO 
    "<HTML>\n",
    "<HEAD><TITLE>Disk space overview</TITLE></HEAD>\n",
    "<BODY>\n",
    "<H1 ALIGN=\"center\">Disk space overview</H1>\n",
    "<h5 align=\"center\">Generated on ".localtime()."</h5>\n",
    "<h2>Disk space overview</h2>\n",
    "Note that each disk may contain other directories than reco*/. Those ",
    "are the only ones scanned ...\n",
    "The reported structure reflects a tree assumed to be of the form ",
    " Trigger/Field/Production.\n",
    "<P>\n";


print $FO "<table border=\"1\" cellspacing=\"0\" width=\"1000\">\n";
printf $FO
    "<TR bgcolor=\"orange\"><TD align=\"center\">%10s</TD><TD align=\"center\">%10s</TD><TD align=\"center\">%10s</TD><TD align=\"center\">%10s</TD><TD align=\"center\">%3s</TD><TD align=\"center\">%s</TD><TD align=\"center\">%s</TD></TR>\n",
    "Disk","Total","Used","Avail","Used %","Triggers","Libs";

$col = 0;
foreach $disk (sort keys %DINFO){
    @items = split(";",$DINFO{$disk});
    $items[4] =~ s/\s/&nbsp; /;
    $items[5] =~ s/\s/&nbsp; /;

    $col =  $items[3];
    $col =~ s/%//;
    $col =  int( ($#COLORS+1) * ( $col /100.0));
    if( $col >= $#COLORS){ $col = $#COLORS;}

    printf $FO 
	"<TR height=\"10\" bgcolor=\"$COLORS[$col]\"><TD align=\"right\">%10s</TD><TD align=\"right\">%10d</TD><TD align=\"right\">%10d</TD><TD align=\"right\">%10d</TD><TD align=\"right\">%3s</TD><TD>%s</TD><TD align=\"right\">%s</TD></TR>\n",
	"<i><b>$disk</b></i>",$items[0],$items[1],$items[2],$items[3],
	$items[4],$items[5];

    #$col++;
    #if($col > $#COLORS){ $col = 0;}
}


print $FO
    "</TABLE>\n",
    "</BODY>\n",
    "</HTML>\n";

if ( defined($ARGV[0]) ){
    rename("$ARGV[0]-tmp","$ARGV[0]");
}

