#!/usr/local/bin/perl
#!/usr/bin/env perl
###################################################
#                                                 #
# !/opt/star/bin/perl -w                          #
# FileCatalogQuery.pl                             #
#                                                 #
# Written by Adam Kisiel, Dec 2001                #
#                                                 #
# This page allows you to build the query to get  #
# the relevant data from the FileCatalog database #
#                                                 #
###################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser);
}

use CGI qw(:standard);
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;
require "cgi-lib.pl";

my $fields = param("fields");

my $fC = new FileCatalog();
$fC->connect_as("User");

my $boxfields = "filetype,extension,storage,site,production,library,trgword,trgsetupname,runtype,configuration,geometry,collision,magscale,fileseq,owner,node,generator,genversion,genparams";

my $binval="persistent,available";

my $queryfields = "filetype,extension,storage,site,production,library,triggername,triggerword,triggersetup,runtype,configuration,geometry,runnumber,runcomments,collision,datetaken,magscale,magvalue,filename,size,fileseq,filecomment,owner,protection,node,available,persistent,createtime,inserttime,path,simcomment,generator,genversion,gencomment,genparams,tpc,svt,tof,emc,fpd,ftpc,pmd,rich,ssd";
my $operfields = "datetaken,magvalue,runnumber,filename,size,createtime,inserttime,path";


my (@dets) =  $fC->get_detectors();
$binval   .= join(",",@dets);
$boxfields.= ",$binval";

print
    header,
    "<html>\n",
    "<head>\n",
    "<title>FileCatalog Query Builder</title>\n",
    "<LINK rel=\"stylesheet\" type=\"text/css\" href=\"/STAR/comp/cgi_def.css\">",
    "</head>\n",
    "<body bgcolor=#E0E0E0 link=blue, alink=#5599CC, vlink=navy>\n",
    "<FORM name=selectvalues method=get action=\"FileCatalogBrowse.pl\">\n";


my $count = 0;
my $by1   = 6;
my $left1 = $by1 - 2;

print
    "<TABLE cellpading=1 cellspacing=1 border=0>\n",
    "<TR><TD colspan=$by1 class=first>",
    "Select the constraining values for fields:",
    "</TD></TR>\n";


foreach (split(",",$boxfields)){
    if ($count % $by1 == 0){ print "<TR>"; }
    print "<TD class=head>$_</TD><TD class=second> <SELECT name=".$_."val>\n";
    print get_options_for_field($_)."\n";

    print "</SELECT></TD>\n";
    $count++;
    if ($count % ($by1/2) == 0){ print "</TR>\n"; }
}
print
    "<TR><TD class=head>simulation</TD>",
    "<TD class=second><SELECT name=\"simulationval\">\n",
    "<OPTION>ALL</OPTION><OPTION>0</OPTION><OPTION>1</OPTION></SELECT>",
    "</TD></TR>\n";
print
    "<TR><TD colspan=$by1 class=first>",
    "Select the glob match for the following fields:",
    "</TD></TR>\n";

$count = 0;
foreach (split(",",$operfields)){
    print
	"<TR><TD class=head colspan=2>$_</TD>\n",
	"<TD class=second colspan=$left1>",
	"<SELECT name=".$_."oper>",
	"<OPTION>greater than</OPTION>",
	"<OPTION>less than</OPTION>",
	"<OPTION>no greater than</OPTION>",
	"<OPTION>no less then</OPTION>",
	"<OPTION>not equal</OPTION>",
	"<OPTION>equal</OPTION>",
	"<OPTION>not like</OPTION>",
	"<OPTION>like</OPTION>",
	"</SELECT>",
	"<INPUT name='".$_."glob' TYPE=text width=50 value=''>",
	"</TD></TR>\n";
    $count++;
}
print "</TABLE>\n";



my $by2=9;
print
    "<TABLE cellpading=1 cellspacing=1 border=0>\n",
    "<TR><TD colspan=$by2 class=first>",
    "Select which fields to return in the query:</TD></TR>\n";

$count = 0;
foreach (split(",",$queryfields)){
    if ($count % $by2 == 0){ print "<TR>"; }
    print "<TD class=second><INPUT name=".$_." TYPE='checkbox'> $_ </TD>\n";
    $count++;
    if ($count % $by2 == 0){ print "</TR>\n"; }

}
print
    "<TR><TD colspan=$by2 class=first>",
    "<INPUT name=go type=submit value='Get the records'></TD></TR>\n",
    "</TABLE>\n";



print "<br>\n<H5><b><i>Written by ".
    "<A HREF=\"mailto:kisiel\@if.pw.edu.pl\">Adam Kisiel</A> </i></b></H5>".
    "</FORM>\n",
    end_html;

$fC->destroy();




sub get_options_for_field 
{
    ($parkey) = @_;
    my($retstring,$last,@entries);

    $last = 0;

    if ( index($binval,$_) == -1){
	if ( -e "/tmp/$parkey.val"){ $last = (stat("/tmp/$parkey.val"))[10];}

	if ( (time() - $last) > 300 ){
	    @entries = $fC->run_query($parkey);
	    if ( open(FO,">/tmp/$parkey.val") ){
		foreach (@entries){ print FO "$_\n";}
	    }
	    close(FO);
	} else {
	    open(FI,"/tmp/$parkey.val");
	    @entries = <FI>;
	    close(FI);
	}
    } else {
	@entries = (0,1);
    }


    $retstring .= "<OPTION>ALL</OPTION>";
    foreach (@entries){
	$retstring .= "<OPTION>$_</OPTION>";
    }
    return $retstring;
}
