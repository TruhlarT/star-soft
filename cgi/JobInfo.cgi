#!/opt/star/bin/perl -w 
#JobInfo.pl

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
 use CGI::Carp qw(fatalsToBrowser carpout); 
}

use CGI qw(:standard);
use DBI;
use strict;

my $ProdTag = param("PT");
my $Trigger = param("Trigger");
my $Status = param("Status");
my $Method = param("button_name");
my $Method1 = param("button_name1");

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

my $move_list;
my $job_dir = "/star/u/starreco/$ProdTag/requests/daq/jobfiles/";
my $arch_dir = "/star/u/starreco/$ProdTag/requests/daq/archive/";
my $list_dir = "/afs/rhic/star/doc/www/html/comp-nfs/csh/";

my $datasourse = "DBI:mysql:operation:duvall.star.bnl.gov";
my $username = "starreco";
my $scriptname = "http://www.star.bnl.gov/devcgi/JobInfo.cgi";

my @querystr; 

print header,
      "<HTML>\n","<HEAD>\n","<TITLE>JobInfo</TITLE>\n","</HEAD>\n",
      "<BODY BGCOLOR=beige LINK=blue, ALINK=red, VLINK=navy>\n";           

print "<!-- $Method $ProdTag $Trigger -->\n";

if (($ProdTag) || ($Trigger)) {    
    if ($Method eq "Generate") {
        print "<!-- We are in Method=Generate -->\n";	       
	my $dbh1 = DBI->connect($datasourse,$username) 
	    or die "Can't connect to $datasourse";
	my $sth1 = $dbh1->prepare("SELECT ProdTag, Trigger, LFName ".
				  "FROM RJobInfo ".
				  "WHERE id = ?"
				  );

        @querystr = split(/&/,$ENV{'QUERY_STRING'}); 
        if ($#querystr>3) {  
	    foreach $chek (@querystr) {
		if ($chek=~/(cb)(\d+)/) {
		    $id=$2;          
		    push (@checked,"cb$id");                              
		    $sth1->execute($id);                   
		    while (($prodtag, $trigger, $LFname)= $sth1->fetchrow_array()){ 
			print "mv $arch_dir$prodtag\_$trigger*$LFname $job_dir\n", br;
		    }
		}
	    }               	   
            print 
                "<FORM action=$scriptname>\n",
                "<INPUT type=hidden name=PT value=$ProdTag>\n",
	        "<INPUT type=hidden name=Trigger value=$Trigger>\n",  
                "<INPUT type=hidden name=Status value=$Status>\n",  
                "<INPUT type=hidden name=button_name1 value=Update>\n";
  	        foreach $chek (@checked) {
                   print "<INPUT type=hidden name=$chek value=on>\n";
	        }
            print
#                "<INPUT type=submit name=button_name value=Status>\n",
                submit('button_name','Create List'),
                "</FORM>\n";    

        } else {
            print "<H1>No jobs selected</H1>";
	}
	print "<P align=left>
           <A HREF=$scriptname?PT=$ProdTag&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";      
    } 

    # Method Status
    if (($Method eq "MarkMoved") or ($Method eq "Create List")) {
        print "<!-- We are in Method=MarkMoved -->\n";
	my $dbh1 = DBI->connect($datasourse,$username) 
	    or die "Can't connect to $datasourse";
	my $sth3 = $dbh1->prepare("UPDATE RJobInfo SET Status=1 WHERE id =?");        
	@querystr = split(/&/,$ENV{'QUERY_STRING'}); 
        if ($Method eq "Create List") {
            $move_list = $list_dir.time().".ml"; 
            open(MOVELIST,">>$move_list") || die "can't create $move_list\n";   
        }
        if ($#querystr>3) {                 
	    foreach $chek (@querystr) {
		if ($chek=~/(cb)(\d+)/) { 
		    $id=$2;     
		    $sth3->execute($id);
		    if ($Method eq "Create List") {
			my $dbh1 = DBI->connect($datasourse,$username) 
			    or die "Can't connect to $datasourse";
			my $sth1 = $dbh1->prepare("SELECT ProdTag, Trigger, LFName ". 
                                                  "FROM RJobInfo ".
                                                  "WHERE id = ? "
						  );
			$sth1->execute($id);
			while (($prodtag, $trigger, $LFname)= $sth1->fetchrow_array()){ 
			    print MOVELIST "$arch_dir$prodtag\_$trigger*$LFname    $job_dir\n";
			}
		    }
		}        
	    }
	    if (!$Method1) {
                print 
                    "<H1>db RJobInfo was updated</H1>\n",
                    "<P align=left>",
		    "<A HREF=$scriptname?PT=$ProdTag&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
	    }        	
        } else {
            print 
                "<H1>No jobs selected</H1>\n",
                "<P align=left>",
                "<A HREF=$scriptname?PT=$ProdTag&Trigger=$Trigger&Status=$Status&button_name=Submit+Query&>Back</A></P>\n";
	}             
    }

    #Method Update
    if (($Method eq "Update") or ($Method eq "Submit Query") or ($Method1 eq "Update")){       
        print "<!-- We are in the update method -->\n";
	my $dbh1 = DBI->connect($datasourse,$username) 
	    or die "Can't connect to $datasourse";        
        if ($Status==1) {
            $query = "Where ProdTag = \"$ProdTag\" AND Status=1 AND Trigger = \"$Trigger\" " ;
        } elsif ($Status==0){
            $query = "Where ProdTag = \"$ProdTag\" AND Status=0 AND Trigger = \"$Trigger\" ";
	} elsif ($Status==-1){
            $query = "Where ProdTag = \"$ProdTag\" AND Trigger = \"$Trigger\" ";
        }
	my $sth2 = $dbh1->prepare("SELECT id, ProdTag, Trigger, LFName, mtime, ErrorStr, Status ".
				  "FROM RJobInfo $query"
				  );
        $sth2->execute();         
	print
	    "<H1>Query results</H1>\n", 
	    "<P align=center><A HREF=\"#TableEnd\">End of table</A></P>\n",         
	    "<A NAME=TableBegin><A>\n", 
	    "<FORM action=$scriptname>\n",
            "<INPUT type=hidden name=PT value=$ProdTag\n>",
	    "<INPUT type=hidden name=Trigger value=$Trigger>\n",  
            "<INPUT type=hidden name=Status value=$Status>\n",  	                  
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

        while (($id, $prodtag, $trigger, $LFname, $mtime, $errstr, $status)= $sth2->fetchrow_array) {                
	    $mTime = modtime($mtime);
	    print           
		"<TR align=center bgcolor=khaki><TD>$prodtag</TD>",
		"<TD>$trigger</TD>",
		"<TD>$LFname</TD>",
		"<TD>$mTime</TD>",
		"<TD align=left>$errstr</TD>\n";

	    if ($status==1) {                        
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
	}#while 
                   
	print 
	    "</Table>\n", 
	    "<A NAME=TableEnd><A>\n", 
	    "<P align=center><A HREF=\"#TableBegin\">Begin of table</A></P>\n",   
	    "<center><p align=center>",
            "<INPUT type=submit name=button_name value=Generate>",
            "<INPUT type=submit name=button_name value=MarkMoved>",
            "<INPUT type=submit name=button_name value=Update>",
	    "</p></center>\n",
            "<P align=center><A HREF=\"$scriptname\">Back</A></P>\n",
	    "</FORM>\n";                          
 	$dbh1->disconnect;          
    } 

} else { 
    #Default Method
    print "<!-- We are in the default block -->\n";              	 
    my $dbh1 = DBI->connect($datasourse,$username) 
	or die "Can't connect to $datasourse";      

    #create temp tables for ProdTag and Trigger     
    my $sth1 = $dbh1->prepare("CREATE TABLE ValidTrigger (Trigger CHAR(20) NOT NULL, PRIMARY KEY(Trigger))");
    my $sth4 = $dbh1->prepare("CREATE TABLE ValidProdTag (ProdTag CHAR(8) NOT NULL, PRIMARY KEY(ProdTag))");
    $sth1->execute() or die "Cannnot create table: $DBI::errstr\n";
    $sth4->execute() or die "Cannnot create table: $DBI::errstr\n";

    # fill tables from db RJobInfo
    my $sth2 = $dbh1->prepare("INSERT INTO ValidTrigger SELECT RJobInfo.Trigger FROM RJobInfo");
    $sth2->execute() or die "Cannnot prepare query: $DBI::errstr\n";
    my $sth5 = $dbh1->prepare("INSERT INTO ValidProdTag SELECT RJobInfo.ProdTag FROM RJobInfo");
    $sth5->execute() or die "Cannnot prepare query: $DBI::errstr\n";

    #select Trigger and ProdTag from temp tables
    my $sth3 = $dbh1->prepare("SELECT Trigger FROM ValidTrigger");
    $sth3->execute() or die "Cannnot execute query: $DBI::errstr\n";
    my $sth6 = $dbh1->prepare("SELECT ProdTag FROM ValidProdTag");
    $sth6->execute() or die "Cannnot execute query: $DBI::errstr\n";

    print     
	"<H1 align=\"center\">Job Info</H1>\n",
        "<H3 align=\"center\">Crashed Jobs Information</H3>\n",
	"<FORM action=$scriptname>\n", hr ,br,
	"\n<table align=center border=0>\n",
	"<tr bgcolor=khaki><td>ProdTag:<td bgcolor=beige><SELECT name=PT>\n"; 

    while (($pt) = $sth6->fetchrow_array) {
	print "\t<OPTION value=$pt>$pt\n";
    }                                   
    print 
	"\t</SELECT></td></tr>\n";
    print 
	"<tr bgcolor=khaki><td>Trigger:</td><td bgcolor=beige><SELECT name=Trigger>\n";
    while (($tr) = $sth3->fetchrow_array) {
	print 
	    "\t<OPTION value=$tr>$tr\n";
    }      
    print 
	"\t</SELECT></td></tr>\n";
    print 
      "<tr bgcolor=khaki><td>Status:</td><td bgcolor=beige>",
      "<SELECT name=Status>\n",
      "\t<OPTION value=0>0\n",
      "\t<OPTION value=1>1\n",
      "\t<OPTION value=-1>-1\n",
      "\t</SELECT></td></tr></table>\n",
      "<BR>\n<center><p align=center>",
      submit('button_name','Submit Query'),
      "\n</P></center>\n",
      br, hr,
      "</FORM>\n";
    my $sth = $dbh1->prepare("DROP TABLE if exists ValidTrigger");
    $sth->execute() || die "Cannnot drop table: $DBI::errstr\n";   
    my $sth7 = $dbh1->prepare("DROP TABLE if exists ValidProdTag");
    $sth7->execute() || die "Cannnot drop table: $DBI::errstr\n";   
}
print 
    "<font size=-1><b><i>Written by <A HREF=\"mailto:nikita\@rcf.rhic.bnl.gov\">Nikita Soldatov</A> </i></b></font>\n",
    end_html;

#subs
#===================

sub modtime {

    my ($mtime) = @_;
    my ($sec,$min,$hr,$dy,$mo,$yr,$fullyear);
    
    ($sec,$min,$hr,$dy,$mo,$yr) = (localtime($mtime))[0,1,2,3,4,5];
     $mo = sprintf("%2.2d", $mo+1);
     $dy = sprintf("%2.2d", $dy);  
     if($yr > 97) {
        $fullyear = 1900 + $yr;
     } else {
        $fullyear = 2000 + $yr;
     }
     $mtime = sprintf("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:00",
                       $fullyear,$mo,$dy,$hr,$min);     
  }
#ffdc9f 
