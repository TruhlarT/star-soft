#!/usr/bin/env perl

# This cgi will generate a list of files and destination
# suitable for the the DataCarousel to digest.
# Small help interface added for STAR.
#

use lib "/afs/rhic.bnl.gov/star/packages/scripts/";
use RunDAQ;
use CGI qw(:standard);


$BGCOLOR  = "cornsilk"; # Body color fields
$TEXTCOL  = "black";
$LINKCOL  = "navy";

$query = new CGI;
$this_script= $query->url();

$dctref = "/STAR/comp/sofi/tutorials/carousel";
$title  = "List generator for the STAR DataCarousel ...";
$namlen = 35;


#
# Star the form 
#
print $query->header;
print $query->start_html(-title=>$title,
			 -AUTHOR=>$author,
			 -BGCOLOR=>$BGCOLOR,
			 -TEXT=>$TEXTCOL,
			 -LINK=>$LINKCOL),"\n";


print $query->h1($title),"\n"; 

$dest = param("Dest");

if( defined($dest) ){
    print "Destination is $dest\n";

    # in case of additional garbage
    $dest = (split(" ",$dest))[0];

    # 2 modes
    if( substr($dest,length($dest)-1,1) eq "/"){
	# trailing space means exact path 
	# restoration
	$base= "";
    } else {
	# Open trail means tree/structure 
	# restoration
	@elm = split("/",$dest);
	$base= "/$elm[1]/$elm[2]";
	splice(@elm,0,3);
	#print "[@elm]\n";
    }

    $list = param("Flist");
    if( defined($list) ){
	print "$list\n";
	$list =~ s/\n/ /g;
	$list =~ s/\s+/ /g;
	@all  = split(" ",$list);

	$strip= param("Strip");
	$strip= (split(" ",$strip))[0];

	$obj = rdaq_open_odatabase();
	foreach $file (@all){
	    # the comparison 'eq' is safe but \d+ a bit smarter.
	    if( $file =~ m/^\d+$/ ){
		# this is a run number. We need an extra query
		if ( $obj){
		    print "<!-- Expanding run $file -->\n";
		    $SEL{"runNumber"} = $file;
		    @files = rdaq_get_orecords($obj,\%SEL,-1,0);
		    push(@FILES,@files);
		}
	    } elsif ( $file =~ m/(^\d+).(\d+)/ ){
		$SEL{"runNumber"} = $1;
		$fseq = $2;                
		# no selection on fileseq yet via module
		# use native perl grep (?? failed)
		print "<!-- Expanding run $file ($fseq) -->\n";
		if ( $obj){
		    $tmp = "_raw_";
		    @files = grep(/($tmp)(0*)($fseq)/,
				  rdaq_get_orecords($obj,\%SEL,-1,0));
		    push(@FILES,@files);
		}
	    } else {
		push(@FILES,$file);
	    }
	}
	rdaq_close_odatabase($obj);

	print "<pre>\n";
	print "# Cut from here ---&gt;\n";


	# Now the real list
	foreach $file (@FILES){
	    # print "<!-- Parsing rdaq_file2hpss($file) -->\n";
	    # if $file do not have any extension, assume ".daq"
	    if ($file !~ m/\./){  $file .= ".daq";}

	    $hpssfile = rdaq_file2hpss($file);
	    if( $base eq ""){
		print "$hpssfile $dest$file\n";
	    } else {
		$dfile =  $hpssfile;
		$dfile =~ s/\/home\/starsink//;
		$dfile =~ s/$strip//;
		@fel   = split("/",$dfile);
		shift(@fel);
		for($i=0 ; $i <= $#elm ; $i++){
		    #print "[shifting ".shift(@fel)."]\n";
		    shift(@fel);
		}
		unshift(@fel,@elm);
		$dfile = "$base/". join("/",@fel);
		print "$hpssfile $dfile\n";
	    }
	}
	print "# &lt;--- to here\n";
	print "</pre>";
    } else {
	print "<b>You need to specify a list of files<b>\n";
    }

} else {
    print 
	"This script is ONLY meant to help you generate a list of file \n",
	"to recover from HPSS. This is NOT a submission script. This cgi \n",
	"will function only based on files the FastOffline system knows about\n",
	"(this is a limitation).<br>\n",
	"The produced output of this cgi MUST serve as input of the \n",
	"<a href=\"$dctref\">DataCarousel</a> tool for the files to ",
	"appear ...<p>\n",
	"Path with trailing slash indicates the exact absolute path\n",
	"you wan to use. Path without trailing slash indicates you\n",
	"want to preserve the directory structure.<br>\n",
	"This script supports Year1 or Year &gt; 2 files BUT the syntax \n",
	"using <tt>RunNumber</tt> or <tt>Runnumber.filesequence</tt>\n",
	"works in Year &gt 2 mode only ...\n";

    # default form
    print 
	"<HR>\n",
	"<FORM ACTION=\"$this_script\">\n",
	"<TABLE BORDER=\"0\">\n";


    print 
	"<TR><TD>",
	"<FONT SIZE=\"+1\">Restore Base PATH</FONT>",
	"</TD>\n\t<TD>",
	$query->textfield(-size=>($namlen+1),-name=>"Dest",
			  -default=>"/star/data03"),
	"</TD></TR>\n";

    print 
	"<TR><TD>",
	"<FONT SIZE=\"+1\">Ignored HPSS path</FONT>",
	"</TD>\n\t<TD>",
	$query->textfield(-size=>($namlen+1),-name=>"Strip",
			  -default=>"raw/"),
	"</TD></TR>\n";

    print
	"<TR><TD>",
	"<FONT SIZE=\"+1\">Space separated list<br>of DAQ file name(s)<br>",
	"and/or Year &gt; 2 run<br>number and/or<br>RunNumber.fileSeq</FONT>",
	"</TD>\n\t<TD>",
	$query->textarea(-name=>"Flist",
			 -default=>"",
			 -rows=>10,
			 -columns=>($namlen+1)),
	"</TD></TR>\n";


    print 
	"</TABLE>\n",
	$query->submit,"\n",
	$query->endform,"\n<HR>\n";
}

print
    "<p>\n",
    "<a href=\"$dctref\">DataCarousel Tutorial</a><p>\n",
    "<font size=-1><b><i>Written by ",
    "<A HREF=\"mailto:jlauret\@bnl.gov\">J&eacute;r&ocirc;me LAURET</A> ",
    "</i></b></font>\n";
print $query->end_html,"\n";

