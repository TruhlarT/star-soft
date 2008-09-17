#!/usr/bin/env perl

#
# Script written by J.Lauret, May 2002.
# It relies on already formatted pages located in $PATH
# and just displays them ... See also showquotas script.
#
#BEGIN {
# use CGI::Carp qw(fatalsToBrowser carpout);
#}

use CGI qw(:standard);;

my $query = new CGI;
my $disk  = param("disk");
my $this_script= $query->url();


$PATH = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub";
$title    = "Disk Space Information";
$BGCOLOR  = "cornsilk"; # Body color fields
$TEXTCOL  = "black";
$LINKCOL  = "navy";
$author   = "J&eacute;r&ocirc;me LAURET";
$email    = "jlauret\@bnl.gov";

print
    $query->header,
    $query->start_html(-title=>$title,
		       -AUTHOR=>$author,
		       -BGCOLOR=>$BGCOLOR,
		       -TEXT=>$TEXTCOL,
		       -LINK=>$LINKCOL),"\n",
    $query->h1($title)."\n";


if ($disk){
    # Display header, Open the file, check content
    print "\n<a href=\"$this_script\">Back</a><br>\n";
    if( -e "$PATH/$disk"){
	# Note that the little pipe here will prevent from
	# output-ing a binary file ... Small security we will
	# turn on later
	#if( open(FI,"|cat $PATH/$disk | groff -Tascii8") ){
	if( open(FI,"$PATH/$disk") ){
	    while( defined($line = <FI>) ){
		chomp($line);
		#$t = chop($line);
		#if( $t ne "-"){ $line .= $t;}
		print "$line\n";
	    }
	    close(FI);
	} else {
	    print
		"<B>Error reading information</B>\n",
		"If this problem persists, please, contact ",
		"<a mailto=\"$email\">$author</a>";
	}
    } else {
	print
	    "<B>There is no information available for $disk</B>";
    }
    print "\n<a href=\"$this_script\">Back</a><br>\n";

} else {
    @raw = glob("$PATH/SQ*.html");

    if($#raw != -1){
	foreach $val (@raw){
	    if ($val !~ m/SQ_/){    next;}
	    if ($val =~ /overall/){ next;}
	    $val =~ s/.*\///g;
	    $txt = $val;
	    $txt =~ s/\..*//; $txt =~ s/SQ_//;
	    $labels{$val} = $txt;
	    push(@values,$val);
	}

	print
	    "<FORM action=$this_script method=POST>\n",
	    $query->popup_menu(-name=>"disk",
			       -values=>\@values,
			       -labels=>\%labels,
			       ),
	    submit('button_name','Show'),
	    "</FORM>\n";
    } else {
	print
	    "<b>Not properly configured or no information available</b><br>\n",
	    "If this problem persists, please, contact ",
	    "<a mailto=\"$email\">$author</a>";
    }
}

print
    "<font size=-1><b><i>Written by <A HREF=\"mailto:$email\">$author</A> </i></b></font>",
    $query->end_html;
