#!/usr/bin/env perl
# JobInfo2.cgi

# Version 2
#
# This cgi script read the information from the RJobInfo
# table from the operation database. It displays it
# in a comprehensive way and allows manipulation of
# the results (such as marking entries as 'old',
# generate scripts to move job-files around etc ...).
#
# This script is 'fed' by the ScanLog.pl script.
#
# Both were written by Nikita Soldatov, July 2001.
#
#


BEGIN {
 use CGI::Carp qw(fatalsToBrowser); # carpout);
}

use CGI qw(:standard);
use DBI;

my $updatetime = 90;

my $ProdTag = param("PT");
my $Trigger = param("Trigger");
my $Status  = param("Status");
my $Method  = param("button_name");
my $Method1 = param("button_name1");
my $Kind    = param("Kind");
if(! $Kind){ $Kind = "daq";}

my $id;
my $prodtag;
my $trigger;
my $errstr;
my $LFname;
my $mtime;
my $mTime;
my $status;
my $query;
my ($pt,$tr);

my @checked;
my $chek;

my %formdata;
my @name;
my $count;
my $name;

my $move_list;

my $job_dir  = "/star/u/starreco/$ProdTag/requests/$kind/jobfiles/";
my $arch_dir = "/star/u/starreco/$ProdTag/requests/$Kind/archive/";
my $list_dir = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/csh/";

my $dbdriver   = "mysql";
my $dbname     = "operation";
my $hostname   = "duvall.star.bnl.gov";
my $username   = "starreco";

# my $datasourse = "DBI:mysql:operation:duvall.star.bnl.gov";
	
my $scriptname = "/devcgi/JobInfo.cgi";
my @KINDS      = ("daq","event");         # Ugly hardwiring

my @querystr;

# Build url reference for REFRESH rule
 my $urlref=$scriptname;
 my $qstr = $ENV{'QUERY_STRING'};
 if( $qstr ne ""){
     $qstr =~ s/button.*/button_name=Submit+Query/;
     $urlref .= "?$qstr";
 }

my ($dbh1, $sth, $sth1, $sth2, $sth3, $sth4, $sth5, $sth6, $sth7);

$dbh1 = DBI->connect("DBI:$dbdriver:$dbname:$hostname","$username")
    or die "Can't connect to db $dbname at $hostname";


print
    header,
    "<HTML>\n",
    "<HEAD>\n",
    "<TITLE>Crashed Jobs Information</TITLE>\n",
    "<META HTTP-EQUIV=Refresh CONTENT=\"$updatetime;URL=$urlref\">\n",
    "</HEAD>\n",
    "<BODY BGCOLOR=beige LINK=blue, ALINK=red, VLINK=navy>\n";

if( ($ProdTag) || ($Trigger) ){

    # Generate Block
    # =====================================================

    if( $Method eq "Generate" ){
	print "<!-- We are in Method=Generate -->\n";
	$sth1 = $dbh1->prepare("SELECT ProdTag, Trigger, LFName ".
			       "FROM RJobInfo ".
			       "WHERE id = ?"
			       );
	&parse_formdata();
	if( $count<=4 ){
	    print
		"<H1>No jobs selected</H1>\n",
		"<P align=left>".
		"<A HREF=$scriptname?PT=$ProdTag&Kind=$Kind&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
	} else {
	    print
		"<P align=left>".
		"<A HREF=$scriptname?PT=$ProdTag&Kind=$Kind&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n",
		"<A HREF=\"#ListEnd\">End of list</A>\n<BR>\n<BR>\n",
		"<A NAME=ListBegin><A>\n";
	
	    undef($name);
	    undef(@checked);
	    foreach $name (@names){
		    if( $name=~/(cb)(\d+)/ ){
		    	$id=$2;
		    	push (@checked, "cb$id");
		    	$sth1->execute($id);
		    	while( ($prodtag, $trigger, $LFname)= $sth1->fetchrow_array() ){
				print 
			    	    "mv /star/u/starreco/$prodtag/requests/$Kind/archive/*$LFname ",
			            "/star/u/starreco/$prodtag/requests/$Kind/jobfiles/\n", br;
		    	}
		    }
	    }
	    print
		"<FORM action=$scriptname method=POST>\n",
		"<INPUT type=hidden name=PT value=$ProdTag>\n",
		"<INPUT type=hidden name=Kind value=$Kind>\n",
		"<INPUT type=hidden name=Trigger value=$Trigger>\n",
		"<INPUT type=hidden name=Status value=$Status>\n",
		"<INPUT type=hidden name=button_name1 value=Update>\n";
	    undef($chek);
	    foreach $chek (@checked){
		print "<INPUT type=hidden name=$chek value=on>\n";
	    }
	    print
		"<A HREF=\"#ListBegin\">Begin of list</A>\n<BR>\n<BR>\n",
		"<A NAME=ListEnd><A>\n",
		submit('button_name','Create List'),
		"</FORM>\n";
	    print 
		"<P align=left>".
	    	"<A HREF=$scriptname?PT=$ProdTag&Kind=$Kind&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
        } # else
    } 
    # End Generate Block
    # =====================================================

    # MarkMoved Block
    # =====================================================

    if( ($Method eq "MarkMoved") or ($Method eq "Create List") ){
	print "<!-- We are in Method=MarkMoved -->\n";
	$sth3 = $dbh1->prepare("UPDATE RJobInfo SET Status=1 WHERE id =?");
	
	&parse_formdata();
	if( $count<=4 ){
	    print 
		"<H1>No jobs selected</H1>",
		"<P align=left>",
		"<A HREF=$scriptname?PT=$ProdTag&Kind=$Kind&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
	} else { 
	    if( $Method eq "Create List" ){
	    	undef($move_list);
	    	$move_list = $list_dir.time().".ml";
	    	open(MOVELIST,">$move_list") || warn "can't create $move_list\n";
	    	$sth1 = $dbh1->prepare("SELECT ProdTag, Trigger, LFName ".
						  "FROM RJobInfo ".
						  "WHERE id = ?"
						  )
			or die "can't prepare statement\n";
	    }
	    foreach $name (@names){
		if( $name=~/(cb)(\d+)/ ){
		    $id=$2;
		    $sth3->execute($id);
		    if( $Method eq "Create List" ){
			$sth1->execute($id);
			while( ($prodtag, $trigger, $LFname)= $sth1->fetchrow_array() ){
			    print MOVELIST
				"/star/u/starreco/$prodtag/requests/$Kind/archive/*$LFname ",
				"/star/u/starreco/$prodtag/requests/$Kind/jobfiles/\n";
			}
		    } #if Method=CreatList
		}
	    }
	    if( ! eof(MOVELIST) ){
		close(MOVELIST);
		chmod(0775,$move_list);
	    }
	    if( !$Method1 ){
		print
		    "<H1>db RJobInfo was updated</H1>\n",
		    "<P align=left>",
		    "<A HREF=$scriptname?PT=$ProdTag&Kind=$Kind&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
	    }
        }
    } 
    # End MarkMoved Block
    # =====================================================	

    # Update & SubmitQuery Block
    # =====================================================	

    if( ($Method eq "Update") or ($Method eq "Submit Query") or ($Method1 eq "Update") ){
	print "<!-- We are in the update method -->\n";
	if( $Status==1 ){
	    $query = "Where ProdTag = \"$ProdTag\" AND Trigger = \"$Trigger\" AND Status=1";
        }elsif( $Status==0 ){
	    $query = "Where ProdTag = \"$ProdTag\" AND Trigger = \"$Trigger\" AND Status=0";
	}elsif( $Status==-1 ){
	    $query = "Where ProdTag = \"$ProdTag\" AND Trigger = \"$Trigger\" AND  ";
	}
	if( ($ProdTag eq "All") && ($Trigger eq "All") ){
	    if( $Status==-1 ){
		$query=~s/Where//;
	    }
	    $query =~ s/ProdTag = \"$ProdTag\" AND Trigger = \"$Trigger\" AND//;
	} elsif( $Status==-1 ){
	    $query=~s/AND  //;
	}
	if( $ProdTag eq "All" ){
	    $query =~ s/ProdTag = \"$ProdTag\" AND//;
	}
	if( $Trigger eq "All" ){
	    if( $Status==-1 ){
		$query =~ s/AND Trigger = \"$Trigger\"//;
	    } else {
		$query =~ s/Trigger = \"$Trigger\" AND//;
	    }
	}
	$sth2 = $dbh1->prepare("SELECT id, ProdTag, Trigger, LFName, mtime, ErrorStr, Status ".
				  "FROM RJobInfo $query")
	    or die "cannot prepare query";
	$sth2->execute();
	print
	    "<H1 align=\"center\">Your query</H1>\n",
	    "<TABLE align=center>\n",
		"<TR bgcolor=#ffdc9f>",
			"<TH>ProdTag</TH>\n",
			"<TH>Kind</TH>\n",
	    		"<TH>Trigger</TH> \n",
	    		"<TH>Status</TH>\n",
		"</TR>\n",
		"<TR align=center bgcolor=khaki>\n",
			"<TD>$ProdTag</TD>",
			"<TD>$Kind</TD>",
			"<TD>$Trigger</TD>";
	    	if( $Status==1 ){
		    print
		        "<TD>Moved</TD>";
	        } elsif ( $Status==0 ){
		    print
		        "<TD>NotMoved</TD>";
                } else {
		    print
		        "<TD>All</TD>";
	        }
	print
	    "</TR>\n",				
	    "</TABLE>\n<BR>\n",
            "<P align=center><A HREF=\"$scriptname\">Back</A></P>\n",    
	    "<H1 align=\"center\">Query results</H1>\n",
	    "<FORM action=$scriptname method=POST>\n",
	    "<INPUT type=hidden name=PT value=$ProdTag\n>",
	    "<INPUT type=hidden name=Kind value=$Kind>\n",
	    "<INPUT type=hidden name=Trigger value=$Trigger>\n",
	    "<INPUT type=hidden name=Status value=$Status>\n",
            "<P align=center><A HREF=\"#TableEnd\">End of table</A></P>\n",
	    "<A NAME=TableBegin><A>\n",
	    "<TABLE align=center>\n",
	    	"<TR bgcolor=#ffdc9f>",
	    		"<TH>ProdTag</TH>\n",
	    		"<TH>Trigger</TH> \n",
	    		"<TH>LogFileName</TH>\n",
	    		"<TH>MTime</TH>\n",
	    		"<TH>ErrorString</TH>\n",
	    		"<TH>Status</TH>\n",
	    		"<TH>Select</TH>\n",
	    	"</TR>\n";
	while( ($id, $prodtag, $trigger, $LFname, $mtime, $errstr, $status)= $sth2->fetchrow_array ){
		
#	    	$mTime = modtime($mtime);
	    	$mTime = localtime($mtime);

	    	# Convert error string to HTML
	    	$errstr =~ s/\&/&amp;/g;
	    	$errstr =~ s/</&lt;/g;
	    	$errstr =~ s/>/&gt;/g;

	    	print
		    "<TR align=center bgcolor=khaki>\n",
			"<TD>$prodtag</TD>",
			"<TD>$trigger</TD>",
			"<TD>$LFname</TD>",
			"<TD>$mTime</TD>",
			"<TD align=left>$errstr</TD>\n";
	         if( $status==1 ){
		     print
		    	 "<TD bgcolor=red>Moved</TD>\n",
		  	 "<TD bgcolor=khaki>&nbsp</TD>\n";
	    	 } else {
		     print
		         "<TD bgcolor=lightgreen>NotMoved</TD>\n",
		         "<TD><INPUT type=checkbox name=cb$id value=on checked></TD>\n";
	         }
	         print 
	             "</TR>\n";
	} # while
	print
	    "</Table>\n",
	    "<A NAME=TableEnd><A>\n",
	    "<P align=center><A HREF=\"#TableBegin\">Begin of table</A></P>\n",
	    "<center>\n",
		"<INPUT type=submit name=button_name value=Generate>",
		"<INPUT type=submit name=button_name value=MarkMoved>",
		"<INPUT type=submit name=button_name value=Update>",
	    "</center>\n",
	    "<P align=center><A HREF=\"$scriptname\">Back</A></P>\n",
	    "</FORM>\n",
	    "<HR>\n",
	    "<H5>This page is automatically updated every $updatetime seconds</H5>\n";
    } 
    # End Update Block
    # =====================================================	

} else {
	
    # Default Block
    # =====================================================		

    print "<!-- We are in the default block -->\n";
    # drop temp tables for ProdTag and Trigger if exist and create them
    $sth7 = $dbh1->prepare("DROP TABLE if exists ValidProdTag");
    $sth4 = $dbh1->prepare("CREATE TABLE ValidProdTag (ProdTag CHAR(8) NOT NULL, PRIMARY KEY(ProdTag))");
    $sth7->execute() or die "Cannnot drop table: $DBI::errstr\n";
    $sth4->execute() or die "Cannnot create table: $DBI::errstr\n";

    $sth = $dbh1->prepare("DROP TABLE if exists ValidTrigger");
    $sth1 = $dbh1->prepare("CREATE TABLE ValidTrigger (Trigger CHAR(20) NOT NULL, PRIMARY KEY(Trigger))");
    $sth->execute() || die "Cannnot drop table: $DBI::errstr\n";
    $sth1->execute() or die "Cannnot create table: $DBI::errstr\n";

    # fill tables from db RJobInfo
    $sth2 = $dbh1->prepare("INSERT INTO ValidTrigger SELECT DISTINCT RJobInfo.Trigger FROM RJobInfo");
    $sth2->execute() or die "Cannnot prepare query: $DBI::errstr\n";
    $sth5 = $dbh1->prepare("INSERT INTO ValidProdTag SELECT DISTINCT RJobInfo.ProdTag FROM RJobInfo");
    $sth5->execute() or die "Cannnot prepare query: $DBI::errstr\n";
    # select Trigger and ProdTag from temp tables
    $sth3 = $dbh1->prepare("SELECT Trigger FROM ValidTrigger");
    $sth3->execute() or die "Cannnot execute query: $DBI::errstr\n";
    $sth6 = $dbh1->prepare("SELECT ProdTag FROM ValidProdTag");
    $sth6->execute() or die "Cannnot execute query: $DBI::errstr\n";
    print
	"<H1 align=\"center\">Job Info</H1>\n",
	"<H3 align=\"center\">Crashed Jobs Information</H3>\n",
	"<FORM action=$scriptname>\n", hr ,br,
	"\n<table align=center border=0>\n",
	"<tr bgcolor=khaki><td>ProdTag:<td bgcolor=beige><SELECT name=PT>\n",
	"\t<OPTION value=All>All\n";
    while( ($pt) = $sth6->fetchrow_array ){
	print "\t<OPTION value=$pt>$pt\n";
    }
    print "\t</SELECT></td></tr>\n";
    print 
	"<tr bgcolor=khaki><td>Trigger:</td><td bgcolor=beige><SELECT name=Trigger>\n",
	"<OPTION value=All>All\n";
    while( ($tr) = $sth3->fetchrow_array ){
	print "\t<OPTION value=$tr>$tr\n";
    }
    print "\t</SELECT></td></tr>\n";
    print
	"<tr bgcolor=khaki><td>Status:</td><td bgcolor=beige>",
	"<SELECT name=Status>\n",
	"\t<OPTION value=0>0\n",
	"\t<OPTION value=1>1\n",
	"\t<OPTION value=-1>-1\n",
	"\t</SELECT></td></tr>",
	"<tr bgcolor=khaki><td>Kind:</td><td bgcolor=beige>",
	"<SELECT name=Kind>\n";
    foreach my $value (@KINDS){
	print "\t<OPTION value=$value>$value\n";
    }
    print
	"\t</SELECT></td></tr>\n",
	"</table>\n",
	"<BR>\n<center><p align=center>",
	submit('button_name','Submit Query'),
	"\n</P></center>\n",
	br,
	"</FORM>\n",
	"<HR>\n",
	"<H5>This page is automatically updated every $updatetime seconds</H5>\n";
} #else Method=Default

# End Update Block
# =====================================================	

print
    "<font size=-1><b><i>Written by <A HREF=\"mailto:nikita\@rcf.rhic.bnl.gov\">Nikita Soldatov</A> </i></b></font>",
    end_html;

$dbh1->disconnect;


#subs
#==============================================================

sub modtime {
    my ($mtime) = @_;
    my ($sec,$min,$hr,$dy,$mo,$yr,$fullyear);

    ($sec,$min,$hr,$dy,$mo,$yr) = (localtime($mtime))[0,1,2,3,4,5];
    $mo = sprintf("%2.2d", $mo+1);
    $dy = sprintf("%2.2d", $dy);
    if ( $yr > 97 ){
	$fullyear = 1900 + $yr;
    } else {
	$fullyear = 2000 + $yr;
    }
    $mtime = sprintf("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:00",
		     $fullyear,$mo,$dy,$hr,$min);
}
#==============================================================

sub parse_formdata {
    
    undef(%formdata);
    undef(@names);
    undef($count);
    
    my $name;
    foreach $name ( param ){
	push(@names,$name);
	$formdata{$name}=param( $name );
	$count++;			   
    }
}
#==============================================================
#ffdc9f
