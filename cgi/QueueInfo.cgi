#!/usr/bin/env perl

# Will use nova monistoring information to display queue information. 
# This cgi may be moved to the local server as it will also have
# administrative tasks
#
# J. Lauret 2013
#

use CGI qw(:standard);
use DBI;

my $query = new CGI;
my $this_script= $query->url();


$PATH     = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub";
$title    = "Batch queue information at BNL";
$TEXTCOL  = "black";
$LINKCOL  = "navy";
$BGCOLOR  = "cornsilk"; 


print
    $query->header,
    $query->start_html(-title=>$title,
                       -AUTHOR=>$author,
                       -BGCOLOR=>$BGCOLOR,
                       -TEXT=>$TEXTCOL,
                       -LINK=>$LINKCOL),"\n",
    $query->h1($title)."\n";

#
# Begin --> 
#
# Since we want to preserve separatyon of privileges i.e.
# hide a bit the "nova" specific (protected) info, let's
# make this is as simple as showing an already formatted
# file in HTML.
#
# But we could use marker files for actions
#  
#
#
if ( -e "$PATH/QueueInfo.html"){
    if ( open(FI,"$PATH/QueueInfo.html") ){
	while (defined($line = <FI>) ){
	    print $line;
	}
	close(FI);
    } else {
	print "&MsgHdr().Problem opening result - please try again\n";
    }
} else {
    print &MsgHdr()."Sorry, no information so far, try again later";
}


#
# <-- Ends here 
#
print $query->end_html;



sub MsgHdr
{
    return localtime()." - ";
}
