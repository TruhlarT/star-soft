#!/usr/local/bin/perl
#!/usr/bin/env perl
###################################################
#                                                 #
# !/opt/star/bin/perl -w                          #
# DataBrowser.pl                                  #
#                                                 #
# Written by Adam Kisiel, Dec 2001                #
#                                                 #
# This is production data browser that allows you #
# to make query from db FileCatalog.              #
# This script uses my perl module FileCat.pm      #
# to work with db FileCatalog.                    #
#                                                 #
###################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser);
}

use CGI qw(:standard);
use lib "/afs/rhic.bnl.gov/star/packages/scripts/";
use FileCatalog;
require "cgi-lib.pl";

my $fields = param("fields");

my $fC = new FileCatalog();
$fC->connect_as("User");


my $boxfields = "filetype,extension,storage,site,production,library,trgword,trgsetupname,runtype,configuration,geometry,collision,magscale,fileseq,owner,node,available,persistent,generator,genversion,genparams,tpc,svt,tof,emc,eemc,fpd,ftpc,pmd,rich,ssd,simulation";

my $queryfields = "filetype,extension,storage,site,production,library,triggername,triggerword,triggersetup,runtype,configuration,geometry,runnumber,runcomments,collision,datetaken,magscale,magvalue,filename,size,fileseq,filecomment,owner,protection,node,available,persistent,createtime,inserttime,path,simcomment,generator,genversion,gencomment,genparams,tpc,svt,tof,emc,fpd,ftpc,pmd,rich,ssd";

my $operfields = "datetaken,magvalue,runnumber,filename,size,createtime,inserttime,path";

print
    header,
    "<html>\n",
    "<head>\n",
    "<title>FileCatalog Data Browser</title>\n",
    "<LINK rel=\"stylesheet\" type=\"text/css\" href=\"/STAR/comp/cgi_def.css\">",
    "</head>\n",
    "<body bgcolor=#E0E0E0 link=blue, alink=#5599CC, vlink=navy>\n";

$fC->clear_context;
$fC->debug_on("cmth");

my (@pars);
foreach (split(",",$boxfields)){
    if ((param($_."val") ne "ALL") && (param($_."val") ne ""))
    { $fC->set_context("$_ = ".param($_."val")); }
}

foreach (split(",",$operfields))
  {
    if (param($_."glob") ne "")
      {
	my $oper;
	if (param($_."oper") eq "greater than")
	  { $oper = " > "; }
	elsif (param($_."oper") eq "equal")
	  { $oper = " = "; }
	elsif (param($_."oper") eq "less than")
	  { $oper = " < "; }
	elsif (param($_."oper") eq "like")
	  { $oper = " ~ "; }
	elsif (param($_."oper") eq "no greater than")
	  { $oper = " <= "; }
	elsif (param($_."oper") eq "no less than")
	  { $oper = " >= "; }
	elsif (param($_."oper") eq "not equal")
	  { $oper = " != "; }
	elsif (param($_."oper") eq "not like")
	  { $oper = " !~ "; }

	$fC->set_context("$_".$oper.param($_."glob"));
      }
  }
foreach (split(",",$queryfields))
  {
    if (param($_) eq "on")
      { push (@pars, $_); }
  }
my ($start, $limit);

if (param("start") ne "")
  { $start = param("start"); }
else
  { $start = 0; }
print "Param is ".param("start")." setting start to $start<BR>\n";
if (param("limit") ne "")
  { $limit = param("limit"); }
else
  { $limit = 100; }
print "Param is ".param("limit")." setting start to $limit<BR>\n";
$fC->set_context("startrecord = $start");
$fC->set_context("limit = $limit");

print "The fields $fields<br>\n";
my @road = $fC->run_query(@pars);
print "<br>Selected records: $#road<br>\n";
print "<table cellpadding=2 cellspacing=1>\n";
print "<tr><td class=head>Num</td>";
foreach (@pars)
  {
    print "<td class=head>$_</td>";
  }
print "</tr>\n";
print "<tr>";

my $class="first";
my $lp = 1;


foreach (@road)
  {
    my @fields;

    (@fields) = split("::");
    print "<tr>";
    print "<td class=lp>".($lp+$start)."</td>";
    foreach(@fields)
      {
	print "<td class=$class>$_</td>";
      }
    print "</tr>\n";
    $lp++;
    if ($class eq "first")
      { $class = "second"; }
    else
      { $class = "first"; }
  }
print "</table>\n";
print "Start: $start Limit: $limit; s+l".($start+$limit)." s-l: ".($start-$limit)."<BR>\n";
my $cururl = self_url();
my ($oldstart) = $cururl =~ m/start=([0-9]*)/;
my ($oldlimit) = $cururl =~ m/limit=([0-9]*)/;
my $newurl = $cururl;
my ($newstart) = $start - $limit;
if ($newstart < 0)
  { $newstart = 0; }
if ($oldstart)
  {
    $newurl =~ s/start=$oldstart/start=$newstart/;
  }
else
  {
    $newurl .= "&start=$newstart";
  }
if (not $oldlimit)
  {
    $newurl .= "&limit=$limit";
  }


print "<A href='$newurl'>PREVIOUS $limit RECORDS</A>&nbsp;&nbsp;\n";

my $newurl = $cururl;
my $newstart = $start + $limit;
if ($oldstart){
    $newurl =~ s/start=$oldstart/start=$newstart/;
} else {
    $newurl .= "&start=$newstart";
}
if (not $oldlimit){
    $newurl .= "&limit=$limit";
}
print "<A href='$newurl'>NEXT $limit RECORDS</A><BR>\n";


print
    "<br>\n<h5><b><i>Written by ",
    "<A HREF=\"mailto:kisiel\@if.pw.edu.pl\">Adam Kisiel</A> </i></b></h5>",
    end_html;
$fC->destroy();

