#!/usr/bin/perl -w

# Updates special documentation files if necessary
# Jan  7, 2000 - Written by Gene Van Buren
# Feb  2, 2001 - GVB - changed /star/starlib/doc/www/html/comp-nfs/
#                     to      /u1/webdata
# Dec 18, 2001 - GVB - changed again to /afs/rhic/star/doc_public/www/webdata
# Aug 20, 2002 - GVB - changed again to /afs/rhic/star/doc_public/www/html/tmp
# Nov  4, 2002 - GVB - changed log file to doc_cgi-log, and gzip old logs
# May  5, 2003 - GVB - add StSecondaryVertexMaker
# Dec 20, 2003 - GVB -         afs/rhic -> afs/rhic.bnl.gov
#                      www.star.bnl.gov -> www.star.bnl.gov/STAR/

# needs three parameters supplied:
# base is one of:
#           "StEvent"
#           "StMcEvent"
#           "SCL"
#           "StAssociationMaker"
#           "TRS"
#           "StSecondaryVertexMaker"
# type is one of:
#           "ps"
#           "pdf"
# level is one of:
#           "CVS"
#           "dev"
#           "new"
#           "pro"
#
# also, write_area is the area in which the script is allowed to write
#
# If any new libraries are added, be sure to put additional entries in
# the names, sdirs, and makepdf tables below.

#use CGI qw(:standard);
use CGI qw(:all);
use File::Path;

#BEGIN {
#use CGI::Carp qw(carpout);
#open(LOG, ">>/afs/rhic.bnl.gov/star/doc_public/www/html/tmp/doc_cgi-log")
#  or die "Unable to append to doc_cgi-log: $!\n";
#carpout(*LOG);
#}

BEGIN {
    use CGI::Carp qw(fatalsToBrowser);
}


$docfile = "/afs/rhic.bnl.gov/star/doc_public/www/html/tmp/doc_cgi-log";
if (`/bin/grep Fail $docfile | /usr/bin/wc -l` > 0) {
#  `/bin/mail -s 'DOC_LOG_FAIL' gene\@bnl.gov < $docfile`;
}

# These are the file names used for the .tex and .ps/.pdf files.
%names = (
   "StEvent" => "StEvent",
   "StMcEvent" => "StMcEvent",
   "SCL" => "StarClassLibrary",
   "StAssociationMaker" => "StAssociationMaker",
   "TRS" => "trs",
   "StSecondaryVertexMaker" => "docXiFinder",
);

# These are the directories where the documentation is located.
%sdirs = (
   "StEvent" => "StRoot\/StEvent\/doc\/tex\/",
   "StMcEvent" => "StRoot\/StMcEvent\/doc\/tex\/",
   "SCL" => "StRoot\/StarClassLibrary\/doc\/tex\/",
   "StAssociationMaker" => "StRoot\/StAssociationMaker\/doc\/tex\/",
   "TRS" => "StRoot\/StTrsMaker\/doc\/",
   "StSecondaryVertexMaker" => "StRoot\/StSecondaryVertexMaker\/doc\/",
);

# If the Makefile for this library allows building pdf files, enter a 1 here.
%makepdf = (
   "StEvent"            => 0,
   "StMcEvent"          => 0,
   "SCL"                => 0,
   "StAssociationMaker" => 0,
   "TRS"                => 0,
   "StSecondaryVertexMaker" => 0,
);

#----------------

# if no base supplied, return
$base = param('base');
if ($base) {

    $level =  param('level');
    $level =~ s/[\s\|\>\<].*//;

    if (! $level) {
	warn "No level parameter supplied...using dev.\n";
	$level = "dev";
    }

    $packdir = "\/afs\/rhic.bnl.gov\/star\/packages\/";
    if ($level eq "CVS") {
	$CVS = 1;
	$SR2 = $packdir . "repository";
	$ENV{CVSROOT} = $SR2;
	$SR = $SR2 . "\/";
	$subdir = $sdirs{$base};
	$thesource2 = $SR . $subdir . $names{$base} . ".tex";
	$thesource = $thesource2 . ",v";
    } else {
	$CVS = 0;
	$SR = $packdir . $level . "\/";
	$subdir = $sdirs{$base};
	$thesource = $SR . $subdir . $names{$base} . ".tex";
    }

    # default type is ps:
    $type = param('type');
    $type or $type = "ps";

    $write_area = "/afs/rhic.bnl.gov/star/doc_public/www/html/tmp/";
    $thefile = $names{$base} . "." . $type;
    $psfile = $names{$base} . ".ps";
    $thefile2 = $level . "_" . $thefile;
    $psfile2 = $level . "_" . $psfile;
    $thefile3 = $write_area . $thefile2;
    $psfile3 = $write_area . $psfile2;
    $request = "----- " . $thefile2 . " -----\n" .
	"  Host   : " . remote_host() . "\n" .
	"  Browser: " . user_agent() . "\n";
    warn $request;

    $ENV{PATH} .= ":/usr/local/bin:/usr/ccs/bin";
    $ENV{LD_LIBRARY_PATH} .= ":/usr/local/lib";
    chdir($write_area);
    $createnew = 0;
    
    if (-e $thefile2) {
	if ((-M $thefile2) > (-M $thesource)) {
	    `/bin/rm $thefile2`;
	    $createnew = 1;
	}
    } else {
	if ((($type eq "pdf") && (! $makepdf{$base})) && (-e $psfile2)) {
	    `/usr/bin/ps2pdf $psfile2 $thefile2`;
	    (-e $thefile2) or die "Failed to convert $psfile2 to $thefile2.\n";
	} else {
	    $createnew = 1;
	}
    }

    if ($createnew) {
	warn "Creating new file.\n";
	if ($CVS) {
	    `/usr/bin/cvs co $subdir`;
	} else {
	    mkpath($subdir) || die "Could not make $subdir in $write_area\n";
	}
	(-e $subdir) or die "Failed to find/create subdirectory $subdir.\n";
	chdir($subdir);
	if (! $CVS) {
	    $olddir = $SR . $subdir . "\*";
	    `/bin/cp -R $olddir .`;
	}
	if ($type eq "pdf") {
	    if ($makepdf{$base}) {
		`/usr/bin/make -s pdf`;
	    } else {
		`/usr/bin/make -s`;
		`/usr/bin/ps2pdf $psfile $thefile`;
		`/bin/mv $psfile $psfile3`;
	    }
	} else {
	    `/usr/bin/make -s`;
	}
	(-e $thefile) or die "Failed to create file $thefile.\n";
	`/bin/mv $thefile $thefile3`;
	chdir($write_area);
        #  rmtree("StRoot");
    } else {
	warn "Retrieving existing file.\n";
    }
   
    $url = "/webdata/$thefile2";
} else {
    # no base name supplied
    $url = "/public/comp/root/special_docs.html";
}
print "Location: $url\n\n";

if (`/bin/cat $docfile | /usr/bin/wc -l` > 500) {
    `/bin/mail -s 'DOC_LOG' gene\@bnl.gov < $docfile`;
    $zipf = $docfile . ".gz.";
    $zipfany = $zipf . "*" ;
    $zipn = `/bin/ls -1 $zipfany | /usr/bin/wc -l`;
    chomp $zipn;
    $zipn =~ s/ //g;
    $zipfname = $zipf . $zipn;
    `/usr/bin/gzip $docfile -c > $zipfname; /bin/rm $docfile`;
}
exit;

