#!/usr/local/bin/perl

#
# Script written by J.Lauret, May 2004.
# It relies on an intermediate disk space $OUTD
# and just displays them ... See also showquotas script.
#
#
# Magic Letters
#   AS   Created by this script to indicate to Auto-Spider to start
#   SD   Created by Auto-Spider script via DBUpdateProd.pl -O (starreco)
#   FC   Created by nova daemon, simple indexer
#
# (c) J. Lauret   
#

use CGI qw(:standard);;
use CGI::Carp qw(fatalsToBrowser carpout);

my $query      = new CGI;
my $disk       = param("disk");  
my $file       = param("file");
my $action     = param("action"); 
my $kind       = param("kind");

my $this_script= $query->url(-relative=>1);
my $full_script= $query->url();


$OUTD     = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub/Spider";


$title    = "Spider Control Center";
$BGCOLOR  = ""; # Body color fields
$TEXTCOL  = "black";
$LINKCOL  = "navy";
$author   = "J&eacute;r&ocirc;me LAURET";
$email    = "jlauret [at] bnl.gov";

# Some table color
$TD  = "<TD BGCOLOR=\"black\" align=\"center\"><FONT FACE=\"Arial, Helvetica\"><FONT COLOR=\"white\"><B>";
$ETD = "</FONT></B></FONT></TD>\n\t";

# List of reference one can return to
%REFS = ("Disk Space Overview","/webdata/pub/overall.html#FCREF");

# List of spider scripts to stop via a .quit file
@SPIDERS=("DBUpdateProd","DBUpdate");


# Resource monitoring
$SERVERI = "/cgi-bin/protected/nova/showMachine.pl?machine=";
$DISKI   = "/webdata/pub/overall.html#";


# Some path to web URI and image
$WWWD  = "/webdata/pub/Spider";                                # Web equivalent
$ICON0 = "/icons/text.gif";                                    # Icon to display for OK disks
$ICON1 = "/icons/transfer.gif";                                # Icon to display for indexer result
$ICON2 = "/STARpublic/images/Spider1.jpg";                     # Icon to display for spider result
$ALERT = "/icons/alert.red.gif";                               # Problem alert icon
$IKILL = "/icons/skull-small.gif";                             # Dead thingy alert
$KK = "/home/users/starweb/bin/bla.csh";

print
    $query->header,
    $query->start_html(-title=>$title,
                       -AUTHOR=>$author,
                       -BGCOLOR=>$BGCOLOR,
                       -TEXT=>$TEXTCOL,
                       -LINK=>$LINKCOL),"\n",
    $query->h1($title)."\n";



if ( ! -d $OUTD ){
    if ( mkdir($OUTD,0700) ){
	print "<B>Info</B> Directory created<BR>\n";
    }
}


# Default values and script variables

if ( ! defined($kind) ){  $kind = "FC";}
else {                    $kind =~ s/[\.\s\|%].*//;}

$EXTRA   = "";           # may be used to allow extraneous menu display
$REFRESH = "REFRESH";    # may change the display




if( $full_script =~ /protected/){
    print "All operations permitted.<br>\n";
} else {
    print "Restricted control permitted.<br>\n";
}

#
# An action has been requested
#
if ( defined($disk) || defined($file) ){
    # first things first
    $disk =~ s/[\.\s\|%].*//;
    $file =~ s/[\.\s\|%].*//;

    # Will accept both "/" path and already substituted
    if ( defined($disk) ){
	$rdisk = $disk;
	$rdisk =~ s/\//_/g;

	print "You requested for $disk to be $action<br>\n";
    } else {
	print "You requested to $action $file<br>\n";
    }


    $error = 0; 
    if ($action eq "view"){
	my($flnm);
	if ( defined($disk) ){  $flnm = "$OUTD/$kind$disk.txt";}
	else                 {  $flnm = "$OUTD/$file";}

	print "Click on menu items to see reports or control the Auto-Spider\n";
	if ( -f $flnm){
	    open(FI,"<$flnm");
	    print "<PRE>\n";
	    while ( defined($line=<FI>) ){
		print $line;
	    }
	    close(FI);
	    print "<PRE>\n";
	}
	$REFRESH = "BACK";
	goto ENDCGI;


    } elsif ( $action eq "enable" ){
	print "action enable\n";
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    foreach $file (@SPIDERS){
		push(@clean,"$OUTD/$file.quit") if ( -e "$OUTD/$file.quit");
	    }
	    if ($#clean == -1){
		print "<I>None of the spiders were blocked</I>\n";	    
	    } else {
		print "<UL>\n";
		foreach $file (@clean){
		    print "<LI>Lock existed as <TT>$file</TT> ";
		    system("$KK && /bin/rm -f $file");
		    if ( ! -e $file ){
			print " <I>Deleted</I>\n";
		    } else {
			print " <B>Cannot be deleted</B>\n";
			$error = 1;
		    }
		}
		print "</UL>\n";
	    }
	}
    } elsif ( $action eq "disable" ){
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    print "<UL>\n";
	    foreach $file (@SPIDERS){
	    system("$KK && /bin/date >$OUTD/$file.quit");
		if ( -e "$OUTD/$file.quit" ){
		    print " <LI><I>Lock created for $file</I><BR>\n";
		} else {
		    print " <LI><B>Lock creating failed for $file</B><BR>\n";
		}
	    }
	    print "</UL>\n";
	}



    } elsif ( $action eq "logclean" ){
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    @clean = glob("$OUTD/*.log*");	
	    if ($#clean == -1){
		print "<I>There are no server logs left</I>\n";
	    } else {	    
		print "<UL>\n";
		foreach $file (@clean){
		    print "<LI>Found <TT>$file</TT> ";
		    system("$KK && /bin/rm -f $file");
		    if ( ! -e $file ){
			print " <I>Deleted</I>\n";
		    } else {
			print " <B>Cannot be deleted</B>\n";
			$error = 1;
		    }
		}
		print "</UL>\n";	    
	    }
	}

    } elsif ( $action eq "clean" || ($dcln = ($action eq "deepclean")) ){
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    @clean = glob("$OUTD/*$rdisk.*");
	    if ($#clean == -1){
		print "<I>The disk is clean</I>\n";
	    } else {
		print "<UL>\n";
		print 
		    "<LI>Note that if files are on disk and not in the Catalog,\n".
		    "    the Auto-Indexer will soon or later add a reference back.<BR>\n",
		    "    You MUST adress the Auto-Indexer issues to complete the cleanup.\n";
		foreach $file (@clean){
		    #next  if ($file =~ m/\.tmp$/);
		    #next  if ($file =~ m/\.lock$/);
		    if ( $file =~ m/.on/ && ! $dcln){ next;}   # do not delete ON files
		    print "<LI>Found <TT>$file</TT> ";
		    system("$KK && /bin/rm -f $file");
		    if ( ! -e $file ){
			print " <I>Deleted</I>\n";
		    } else {
			print " <B>Cannot be deleted</B>\n";
			$error = 1;
		    }
		}
		print "</UL>\n";
	    }
	}

    } elsif ($action eq "ON"){
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    if ( -e "$OUTD/AS$rdisk.on"){
		print "<I>$disk already as Auto-Spidering activated</I>\n";
	    } else {
		system("$KK && echo \"Spidering requested on ".localtime()."\" >$OUTD/AS$rdisk.on");
		if ( -e "$OUTD/AS$rdisk.on" ){
		    print "<I>Auto-Spidering marker created</I>\n";
		    $error = 0;
		} else {
		    print "<B>Cannot create $OUTD/AS$rdisk.on</B>\n";
		    $error = 1;
		}
	    }
	}
    } elsif ($action eq "OFF" ){
	if( $full_script !~ /protected/){
	    &Bomb();
	} else {
	    if ( -e "$OUTD/AS$rdisk.on" ){
		system("$KK && /bin/rm -f $OUTD/AS$rdisk.on");
		if ( ! -e "$OUTD/AS$rdisk.on" ){
		    print "<I>Auto-Spidering marker deleted</I>\n";
		} else {
		    print "<B>Cannot delete $OUTD/AS$rdisk.on</B>\n";
		    $error = 1;
		}
	    } else {
		print "<I>$disk is OFF Auto-Spidering</I>\n";
	    }
	} 
    }

    # All actions will display a status
    print 
	"<BR>\n".
	"<B>Status</B> ".
	($error ? "<FONT COLOR=\"#FF0000\"><B>ERROR</B></FONT>":"<FONT COLOR=\"#0000FF\"><B>Success</B></FONT>").
	"\n";
} 


foreach $file (@SPIDERS){
    print "<UL>\n";
    if ( -e "$OUTD/$file.quit"){
	print 
	    "<LI><B>Note</B> Spider <I>$file</I> is currentely disabled ".
	    "    <A HREF=\"$this_script?disk=all&action=enable\">[enable]</A>\n";
    }
    print "</UL>\n";
}

print 
    "<BR>".
    "<HR>".
    "<A name=\"TOP\"></a> ".
    "<P ALIGN=\"center\">\n".
    " [<a href=\"$this_script\"><B>$REFRESH</B></a>] &nbsp;\n".
    " [<a href=\"#MID\">Middle</a>] &nbsp;\n".
    " [<a href=\"#BOT\">Bottom</a>] &nbsp;\n".
    "</P>\n".
    "<BR>\n";


@needed = glob("$OUTD/FC*.txt");
if ($#needed != -1){
    $count = 0;
    foreach $d (@needed){
	$disk = $d;	    
	$disk =~ s/$OUTD//;
	$disk =~ s/\/FC//;
	$disk =~ s/\..*//;
	$rdisk= $disk;
	$disk =~ s/_/\//g;


	
	$ind   = &GetFCRef("FC",$ICON1,$disk);
	#if ( $ind eq ""){
	#    push(@OKDISKS,$disk);
	#    next;
	#}
	if ( $ind eq ""){
	    #print "$d ind is null";
	    $ind = &GetFCRef("FC",$ICON0,$disk,1);
	    if ( $ind =~ m/alert/){
		$ind = "<FONT COLOR=\"#FF0000\">Problem occured</FONT> $ind";
	    } else {
		$ind = "$ind No spidering required";
	    }
	}


	$count++;
	if ( $count == 1){
	    print 
		"<TABLE ALIGN=\"center\" CELLSPACING=\"0\"  BORDER=\"1\">\n",
		"  <TR>$TD Disk    $ETD\n".
		"      $TD Indexer $ETD\n".
		"      $TD Spider  $ETD\n".
		"      $TD Info    $ETD\n".
		"</TR>\n";
	}

	$FCRef = &GetFCRef("SD",$ICON2,$disk);

	$Info  = &Activity("SD",$disk);
	if ( $Info ne ""){
	    #print "<!-- DEBUGX $Info -->\n";
	    $Info  =~ s/\n/<BR>/gs;
	    $Info  =~ s/in \/.*reco\///;
	    if ( $Info =~ /last/i){
		$Info  = 
		    "<A HREF=\"$this_script?disk=$rdisk&action=clean\">Clean</A><br>".
		    "<i>Not recommended unless day missmatch</i><br>".
		    "$Info<br>".
		    "Now ".localtime()."<br>";
	    } else {
		$Info  = "<A HREF=\"$this_script?disk=$rdisk&action=clean\">Turn Spider OFF</A><br>$Info";
	    }
	} else {
	    $Info  = "<A HREF=\"$this_script?disk=$rdisk&action=ON\">Turn Spider ON</A>";
	}
	print 
	    "<TR><TD BGCOLOR=\"#DDDDDD\"><A HREF=\"$DISKI$rdisk\">$disk</A></TD>\n".
	    "    <TD BGCOLOR=\"#EFEFEF\" ALIGN=\"center\">$ind</TD>\n".
	    "    <TD BGCOLOR=\"#EFEFEF\" ALIGN=\"center\">".($FCRef ne "" ? $FCRef : "<i>off</i>")."</TD>\n".
	    "    <TD BGCOLOR=\"#EFEFEF\" ALIGN=\"center\">".($Info  ne "" ? $Info  : "&nbsp;")."</TD>\n".
	    "</TR>\n";
    }
    print "</TABLE>\n" if ($count != 0);

    if ($#OKDISKS != -1){
	print 
	    "The following did not require a spider (no unknown detected) : <BR>\n",
	    "<BLOCKQUOTE>\n";
	foreach $d (@OKDISKS){
	    print "\t$d&nbsp;\n";
	}
	print "</BLOCKQUOTE>\n";
    }

} else {
    print 
	"<I>Indexer and Spider daemons may be down (please start them) ".
	"or a cleanup was recentely requested</I>\n";
}

print 
    "<A name=\"MID\"></a> ".
    "<P ALIGN=\"center\">\n".
    " [<a href=\"$this_script\"><B>$REFRESH</B></a>] &nbsp;\n".
    " [<a href=\"#TOP\">Top</a>] &nbsp;\n".
    " [<a href=\"#BOT\">Bottom</a>] &nbsp;\n".
    "</P>";



@needed = glob("$OUTD/*.log");
if ($#needed != -1 ){
    print 
	"<hr>\n",
	"<B>Server logs</b>:<br>\n",
	"<BLOCKQUOTE>\n";

    if ( -e "$OUTD/Auto-Spider.report"){
	open(FI,"<$OUTD/Auto-Spider.report");
	while ( defined($line = <FI>) ){
	    chomp($line);
	    # will format later - is $d;$TAG;$LCK;localtime();$status;$stsstr;$CMD;
	    print "<FONT SIZE=\"-1\">$line</FONT><BR>\n";
	}
	close(FI);
    }

    $ii = 0;
    foreach $file (@needed){
	$file =~ s/.*\///;
	$file =~ s/\..*//;
	$name = $file;

	if ( $name =~ /indexer/){
	    $name =~ s/indexer-//;
	    $name =~ s/-.*//;
	} else {
	    $name =~ s/_.*//;
	}
	print 
	    "<A HREF=\"$this_script?action=view&file=$file.log\">$file</A> <A HREF=\"$SERVERI$name.rcf.bnl.gov\">+</A> &nbsp; ";
	$ii++;
	if ($ii == 5){
	    print "<br>\n";
	    $ii = 0;
	}
    }
    print "</BLOCKQUOTE><HR>\n";

    $EXTRA .= "[<a href=\"$this_script\?disk=all&action=logclean\">Logs Cleanup</a>] &nbsp;<br>\n";
}


$EXTRA .= 
    " [<a href=\"$this_script\?disk=_star_data*&action=deepclean\"\">Spiders OFF</a>] ".
                      "(will need to turn them ON again)<br>\n".
    " [<a href=\"$this_script\?disk=_star_data*&action=clean\"\">Spiders Reset</a>] (last info deleted)<br>\n".
    " [&nbsp; <a href=\"$this_script?disk=all&action=enable\">Enable</a> &nbsp; / &nbsp;\n".
    "         <a href=\"$this_script?disk=all&action=disable\">Disable</a> spidering] &nbsp; \n";




ENDCGI:
 print  
    "<P ALIGN=\"center\">",
    "<A name=\"BOT\"></A>".
    "[<a href=\"$this_script\"><B>$REFRESH</B></a>] &nbsp; ".
    "[<a href=\"#TOP\">Top</a>] <br>\n".
    $EXTRA.
    "</P>".
    "<HR>";

foreach $page (keys %REFS){
    print "Back to <a href=\"$REFS{$page}\">$page</a><br>\n";
}

print 
    "<font size=-1><b><i>Written by <A HREF=\"mailto:$email\">$author</A> </i></b></font>",
    $query->end_html;



# -------------------------------------------------------------------------------------------


sub GetFCRef
{
    my($What,$Icon,$el,$flag)=@_;
    my($x,$xx,$xtra);
    $el =~ s/[\/ ]/_/g;

    if ( ! -e "$OUTD/$What$el.txt" && -e "$OUTD/$What$el.txt.last" ){
	$xtra = ".last";
    } else {
	$xtra = "";
    }
    # later argument
    if ( ! defined($flag) ){  $flag = 0;}

    $XWhat = $What;
    $XWhat = "AS" if ($What eq "SD");

    if ( -e "$OUTD/$XWhat$el.kill"){
	my $res=`/bin/cat $OUTD/$XWhat$el.kill | /bin/grep -v Cmd`;
	$res =~ s/\n/<BR>/g;
	return 
	    "<IMG BORDER=\"0\" ALT=\"+\" SRC=\"$IKILL\" WIDTH=\"40\" HEIGHT=\"40\"><BR>".
	    "<FONT COLOR=\"#FF0000\">$res</FONT>";
    }

    #print "<!-- $XWhat $What $el -->\n";

    # while @STAT is global, the intent is to get the value of the previous
    # globally stat-ed file a result.  Do not undef() on an else statement.

    if ( -e "$OUTD/$What$el.txt$xtra"){
	@STAT = stat($OUTD."/$What$el.txt$xtra");
	if ( $STAT[7] != 0){
	    #return 
	    #"<A HREF=\"$WWWD/$What$el.txt\">".
	    #"<IMG BORDER=\"0\" ALT=\"+\" SRC=\"$Icon\" WIDTH=\"25\" HEIGHT=\"25\"></A>";
	    if ( $What eq "FC"){
		chomp($x = `/bin/grep Unknown $OUTD/$What$el.txt$xtra`);
		return "" if ($x eq "" && ! $flag);

		chomp($xx = `/bin/grep Error $OUTD/$What$el.txt$xtra`);
		if ( $xx ne ""){  
		    $x    = $xx;
		    $Icon = $ALERT;
		}

		$x =~ m/(.*)(\d+\.\d+)(.*)/;
		$x = "<BR><TT>$2$3</TT>";
	    }

	    return 
		"<A HREF=\"$this_script?disk=$el&action=view&kind=$What\">".
		"<IMG BORDER=\"0\" ALT=\"+\" SRC=\"$Icon\" WIDTH=\"25\" HEIGHT=\"25\"></A>$x";
	}
    } 
    return "";

}


sub Activity
{
    my($What,$el)=@_;
    $el =~ s/[\/ ]/_/g;
    if ( -e "$OUTD/$What$el.txt"){ 
	$res = `/usr/bin/tail -12 $OUTD/$What$el.txt | /bin/grep '=' |/bin/grep -v '= 0' `;


	print "<!-- DEBUG $res -->\n";

	if ( $res =~ m/(.*)(FC\s+add)(.*)/is){    
	    $res = "$1<b>FC add</b>$3";
	    #print "<!-- DEBUG2 $res -->\n";
	}
	if ( $res =~ m/(.*)(FC\s+Bogus)(.*)/is){  
	    $res = 
		"$1<IMG SRC=\"$ALERT\" WIDTH=15 HEIGHT=15>&nbsp;".
		"<blink><font color=\"#FF0000\">".
		"<B><A HREF=\"$this_script?disk=$el&action=view&kind=$What\">".
		"</A>FC Bogus </B></FONT></blink>$3";
	    #print "<!-- DEBUG3 $res -->\n";
	}
	if ( $res =~ m/(.*)(Unknown)(.*)/is){     
	    $res = "$1<font color=\"#0000FF\"><B>Unknown</B></FONT>$3";
	    #print "<!-- DEBUG4 $res -->\n";
	}
	if ( $res =~ m/(.*)(Old\s+=\s*\d+\n)(.*)/is){
	    $res = $1.$3;
	}

	if ($res ne ""){
	    print "<!-- DEBUG FINAL [$res] -->\n";
	    return 
		$res."\n<FONT SIZE=\"-2\">".
		localtime((stat("$OUTD/$What$el.txt"))[9]).
		"</FONT>";
	} else {
	    return 
		"Last ".
		localtime((stat("$OUTD/$What$el.txt"))[10]);
	}
    } elsif ( -e "$OUTD/AS$el.on"){
	return 
	    "<FONT COLOR=\"#5555EE\"><FONT SIZE=\"-2\">".
	    `/bin/cat $OUTD/AS$el.on`."</FONT></FONT>";

    } elsif ( -e "$OUTD/$What$el.txt.last"){
	return 
	    "<A HREF=\"$WWWD/$What$el.txt.last\">Old</A>".
	    localtime((stat("$OUTD/$What$el.txt.last"))[10]);
    }
    return "";
}



 
sub Bomb
{
    if ( $full_script =~ m/public/){
	$full_script =~ s/public/protected/;
    } else {
	$full_script =~ s/starreco/starreco\/protected/;
    }
    print 
	"<BLOCKQUOTE><FONT SIZE=\"+1\" COLOR=\"#0000FF\">\n",
	" <B>Access of protected operation [$action] via un-protected script not allowed.<BR>\n",
	" Try <A HREF=\"$full_script?$disk=$disk&action=$action\">this link</A> instead<BR>\n",
	"</FONT></BLOCKQUOTE>\n";
    $error = 1;
}
