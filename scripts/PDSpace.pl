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
$MIN   =  1;  # 4
$MAX   =  6;  # for testing
$MAX   = 50;
$MAIN  = "/star/data";

@COLORS = ("#FFFACD","#C1FFC1","#7FFFD4","#00DEFF","#87CEFA","#ccccee","#D8BFD8","#FF69B4");

# Insert an extra table break before those numbers
$BREAK{"01"} =  "User Space";  
$BREAK{"03"} =  "Reserved Usage Space Area";  
$BREAK{"06"} =  "Production Disks / Assigned TEMPORARY space for Projects";  
$BREAK{"08"} =  "Production Disks";  



for ( $i = $MIN ; $i <= $MAX ; $i++){
    push(@DISKS,sprintf("$MAIN%2.2d",$i));
}

foreach $disk (@DISKS){
    if ( ! -e "$disk" && ! -e "$disk/."){  next;}  # -l may be a unmounted disk
    if ( ! -d "$disk/." ){                         # this is definitly not mounted
	$DINFO{$disk} = "?;?;?;?;".
	    "<BLINK><B><FONT COLOR=#FF0000>Offline or bad mount point".
		"</FONT></B></BLINK>; ";
	next;
    }


    chomp($res = `df -k $disk | grep % | grep '/'`);
    $res   =~ s/^\s*(.*?)\s*$/$1/;
    $res   =~ s/\s+/ /g;
    @items =  split(" ",$res);

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
    #print STDERR "\t$tota $used $avai $prct\n";

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
		if (! -d $ver && ! -l $ver){ next;}
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
    #print STDERR "$disk --> $DINFO{$disk}\n";
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
    "<P>\n",
    "<table border=\"0\">\n<TR><td>Color Scale</TD>\n";

for ($i=0 ; $i <= $#COLORS ; $i++){
    $low  = int(100*$i/($#COLORS+1));
    $high = int(100*($i+1)/($#COLORS+1));
    print $FO "\t<TD BGCOLOR=\"$COLORS[$i]\">$low - $high</TD>\n";
}

print $FO 
    "</TR>\n</TABLE>\n",
    "<P>\n",
    "<table border=\"1\" cellspacing=\"0\" width=\"1000\">\n";

$TD  = "<TD BGCOLOR=\"black\" align=\"center\"><FONT FACE=\"Arial, Helvetica\"><FONT COLOR=\"white\"><B>";
$ETD = "</FONT></B></FONT></TD>";

printf $FO
    "<TR>$TD%10s$ETD $TD%11s$ETD $TD%11s$ETD $TD%11s$ETD $TD%3s$ETD $TD%s$ETD $TD%s$ETD</TR>\n",
    "Disk","Total","Used","Avail","Used %","Triggers","Libs";


$col     = 0;
@$totals = (0,0,0);
foreach $disk (sort keys %DINFO){
    $tdisk =  $disk;
    $tdisk =~ s/\//_/g;    # used for name reference

    #print STDERR "$DINFO{$disk}\n";
    @items = split(";",$DINFO{$disk});
    $items[4] =~ s/\s/&nbsp; /;
    $items[5] =~ s/\s/&nbsp; /;

    $icol =  $items[3];
    $icol =~ s/%//;
    #print "$icol ";
    $col =  int( ($#COLORS+1) * ( $icol /100.0));
    #print "$col ";
    if( $icol >= 99 ){
	$col = "red";
    } else {
	$col = $COLORS[$col];
    }

    #print "$col\n";
    $disk =~ m/(\d+)/;
    if ( defined($BREAK{$1}) ){
	printf $FO 
	    "<TR BGCOLOR=\"#333333\"><TD ALIGN=\"center\" COLSPAN=\"7\">".
	    "<FONT COLOR=\"white\"><B>$BREAK{$1}</B></FONT></TD></TR>\n";
    }
    printf $FO
	"<TR height=\"10\" bgcolor=\"$col\">\n".
	"  <TD align=\"right\"><A NAME=\"%s\">%10s</A></TD>\n".
	"  <TD align=\"right\">%11s</TD>\n".
	"  <TD align=\"right\">%11s</TD>\n".
	"  <TD align=\"right\">%11s</TD>\n".
	"  <TD align=\"right\">%3s</TD>\n".
	"  <TD>%s</TD>\n".
	"  <TD align=\"right\">%s</TD>\n".
	"</TR>\n",
	    $tdisk,"<i><b>$disk</b></i>",$items[0],$items[1],$items[2],
	    $items[3],$items[4],$items[5];

    $totals[0] += $items[0];
    $totals[1] += $items[1];
    $totals[2] += $items[2];

    #$col++;
    #if($col > $#COLORS){ $col = 0;}
}


print $FO
    "</TABLE>\n",
    "<B>Summary:</B><BR>\n",
    "<BLOCKQUOTE>\n",
    "Total Space = ".sprintf("%.2f",$totals[0]/1024/1024)." GB<br>\n",
    "Total Used =  ".sprintf("%.2f",$totals[1]/1024/1024)." GB<br>\n",
    "Available  =  ".sprintf("%.2f",$totals[2]/1024/1024)." GB<br>\n",
    "</BLOCKQUOTE>\n",
    "</BODY>\n",
    "</HTML>\n";

if ( defined($ARGV[0]) ){
    if ( -e $ARGV[0]){ 
	# delete if exits the preceedingly renamed file
	if ( -e "$ARGV[0]-old"){ unlink("$ARGV[0]-old");}
	# move the file to a new target name
	if ( ! rename("$ARGV[0]","$ARGV[0]-old") ){
	    # if we cannot rename() try to delete
	    unlink($ARGV[0]);
	}
    }
    # move new file to target
    rename("$ARGV[0]-tmp","$ARGV[0]");
}

