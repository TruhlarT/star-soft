#!/usr/local/bin/perl -w

#
# Written J.Lauret sometime in January 2002
# Reads BFChain.cxx and spit out an HTML formatted
# table of related-options (clickable).
#
# Planned : Add an option 'expand' (i.e. detail
#           what an option really means as per basic
#           maker, order they run etc ...). Will need
#           and extra threading.
#

$IN = shift(@ARGV) if (@ARGV);
$OUT= shift(@ARGV) if (@ARGV);

if( ! defined($IN) ){  $IN  = "StRoot/StBFChain/StBFChain.cxx";}
if( ! defined($OUT)){  $OUT = "StRoot/StBFChain/doc/index.html";}

if ( ! open(FI,"$IN") ){ die "Could not open $IN for reading\n";}

if ($0 !~ m/^\//){
    chomp($SELF = `pwd`);
    $SELF = "$SELF/$0";
} else {
    $SELF = $0;
}

$parse = 0;
while ( defined($line = <FI>) ){
    if($line =~ /Bfc_st BFC/){
	$parse = 1;
    } elsif ($line =~ /\};/){
	last;
    } elsif ($parse){
	$line =~ s/\/\/.*//;
	$line =~ s/^\s*(.*?)\s*$/$1/;
	push(@lines,$line) ;#if ($line ne "");
    }
}
close(FI);

for ($i=0 ; $i <= $#lines ; $i++){
    chomp($line  = $lines[$i]);
    while ($line !~ /\}/){
	$i++;
	$line .= $lines[$i];
    }
    push(@items,split(/\"\s*,/,$line));

    $flag = 1;
    for($j=0 ; $j <= $#items ; $j++){
	$items[$j] =~ s/[\{\"\}]//g;
	$items[$j] =~ s/,/ /g;
	if( index($items[$j],"---") != -1){
	    $items[$j] =~ s/-/ /g;
	}
	$items[$j] =~ s/^\s*(.*?)\s*$/$1/;

	if( $j != 0 && $j != $#items){
	    #print STDERR "$flag [$items[$j]] ";
	    $flag = $flag & ($items[$j] eq "");
	    if($items[$j] eq ""){ $items[$j] = "&nbsp;"}
	}
    }
    
    # Now we are ready
    $key = uc($items[0]);

    if( $i == 0){
	$COLOR{$key} = "orange";
    } elsif( $flag ){
	$COLOR{$key} = "cornsilk";
    } else {
	$COLOR{$key} = "";
    }


    push(@KEYS,$key);
    $OKEY{$key}   = $items[0];
    $KNAME{$key}  = $items[1];
    $KCHAIN{$key} = $items[2];
    $KOPT{$key}   = $items[3];
    $KMAKE{$key}  = $items[4];
    $KLIBS{$key}  = $items[5];
    $KCMT{$key}   = $items[6];

    undef(@items);
}
undef(@lines);


if ( ! open(FO,">$OUT") ){ die "Could not open $OUT for writing\n";}
print FO
    "<head><title>BFChain Options</title></head>\n",
    "<html>\n",
    "<body bgcolor=white>\n",
    "<!-- Generated by $SELF @ARGV -->\n",
    "<H1 ALIGN=\"center\">BFChain Options</H1>\n",
    "<table border=\"1\">\n";

foreach $key (@KEYS){
    if( $key eq ""){ next;}
    if( ! defined($COLOR{$key}) ){  
	$COLOR{$key} = "";
	print STDERR "Missing color for key=$key\n";
    }
    if( $COLOR{$key} ne "" ){
	$col = " BGCOLOR=\"$COLOR{$key}\"";
    } else {
	$col = "";
    }
    print FO "<tr$col><td><A NAME=\"$key\">$OKEY{$key}</A></td><td>$KNAME{$key}</td><td>$KCHAIN{$key}</td>";

    print FO "<td>";	
    @items = split(" ",$KOPT{$key});
    foreach $el (@items){
	$tmp = uc($el);
	if( defined($KNAME{$tmp}) ){
	    print FO "<A HREF=\"\#$tmp\">$el</A> ";
	} else {
	    print FO "$el ";
	}
    }
    print FO "</td><td>$KMAKE{$key}</td><td>$KLIBS{$key}</td><td>$KCMT{$key}</td></tr>\n";
	
}
print FO
    "</table>\n",
    "</body>\n",
    "</html>\n";
close(FO);

