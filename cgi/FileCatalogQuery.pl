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
use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;
require "cgi-lib.pl";

my $fields = param("fields");

my $fC = FileCatalog->new;
$fC->connect;

my $boxfields = "filetype,extension,storage,site,production,library,triggername,triggerword,triggersetup,runtype,configuration,geometry,collision,magscale,fileseq,owner,node,available,persistent,generator,genversion,genparams,tpc,svt,tof,emc,fpd,ftpc,pmd,rich,ssd";
my $queryfields = "filetype,extension,storage,site,production,library,triggername,triggerword,triggersetup,runtype,configuration,geometry,runnumber,runcomments,collision,datetaken,magscale,magvalue,filename,size,fileseq,filecomment,owner,protection,node,available,persistent,createtime,inserttime,path,simcomment,generator,genversion,gencomment,genparams,tpc,svt,tof,emc,fpd,ftpc,pmd,rich,ssd";
my $operfields = "datetaken,magvalue,runnumber,filename,size,createtime,inserttime,path";

print 
    header,    
    "<html>\n",
    "<head>\n",
    "<title>FileCatalog Query Builder</title>\n",
    #"<LINK rel=\"stylesheet\" href=\"def_style.css\" type=\"text/css\">",
    "</head>\n",
    "<body bgcolor=#E0E0E0 link=blue, alink=#5599CC, vlink=navy>\n";   
print "<TABLE cellpading=1 cellspacing=1 border=0>\n";
print "<FORM name=selectvalues method=get action=\"FileCatalogBrowse.pl\">\n";
print "<TR><TD colspan=8 class=first>Select the constraining values for fields:</TD></TR>\n"; 
my $count = 0;
foreach (split(",",$boxfields))
  { 
    if ($count % 4 == 0)
      { print "<TR>"; }
    print "<TD class=head>$_</TD><TD class=second> <SELECT name=".$_."val>\n";
    print get_options_for_field($_)."\n";
    print "</SELECT></TD>\n";
    $count++;
    if ($count % 4 == 0)
      { print "</TR>\n"; }
  }
print "<TR><TD class=head>simulation</TD><TD class=second><SELECT name=\"simulationval\">\n";
print "<OPTION>ALL</OPTION><OPTION>0</OPTION><OPTION>1</OPTION></SELECT></TD></TR>\n";
print "<TR><TD colspan=8 class=first>Select the glob match for the following fields:</TD></TR>\n"; 
$count = 0;
foreach (split(",",$operfields))
  { 
    print "<TR><TD class=head colspan=2>$_</TD>\n";
    print "<TD class=second colspan=6>";
    print "<SELECT name=".$_."oper>";
    print "<OPTION>greater than</OPTION>";
    print "<OPTION>less than</OPTION>";
    print "<OPTION>no greater than</OPTION>";
    print "<OPTION>no less then</OPTION>";
    print "<OPTION>not equal</OPTION>";
    print "<OPTION>equal</OPTION>";
    print "<OPTION>not like</OPTION>";
    print "<OPTION>like</OPTION>";
    print "</SELECT>";
    print "<INPUT name='".$_."glob' TYPE=text width=50 value=''>";
    print "</TD></TR>\n";
    $count++;
  }
print "<TR><TD colspan=8 class=first>Select which fields to return in the query:</TD></TR>\n"; 
$count = 0;
foreach (split(",",$queryfields))
  {
    if ($count % 8 == 0)
      { print "<TR>"; }
    print "<TD class=second><INPUT name=".$_." TYPE='checkbox'> $_ </TD>\n";
    $count++;
    if ($count % 8 == 0)
      { print "</TR>\n"; }
    
  }

print "<TR><TD colspan=8 class=first><INPUT name=go type=submit value='Get the records'></TD></TR>\n";
print "</FROM></TABLE>\n";
print
    "<br>\n<font size=-1><b><i>Written by <A HREF=\"mailto:kisiel\@if.pw.edu.pl\">Adam Kisiel</A> </i></b></font>",
    end_html;

$fC->destroy;

sub get_options_for_field {
  ($parkey) = @_;
  my $retstring;
  my @entries = $fC->run_query($parkey);
  
  $retstring .= "<OPTION>ALL</OPTION>";
  foreach (@entries)
    {
      $retstring .= "<OPTION>$_</OPTION>";
    }
  return $retstring;
}
