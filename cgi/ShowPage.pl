#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log: 
# 
# L.Didenko
# 
# ShowPage.pl
# 
# 
#################################################################### 


use CGI;
use GD;
use CGI::Carp qw(fatalsToBrowser);
use Class::Struct;
use File::Basename;


 my ($query) = @_;

 
 $query = new CGI;

my $setName;
  
 $setName =  $query->param('set1');

print $query->header;
print $query->start_html('ShowPage');

 my $setf;
 my $ii;


 $setf = "http://www.star.bnl.gov/STARAFS/comp/prod/" . $setName ;

print $query->redirect($setf);

print <<END;
 <TITLE>Message</TITLE>
 <META HTTP-EQUIV="STATUS"       CONTENT="302 Redirected">
 <META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html">
END
print  "<META HTTP-EQUIV=\"LOCATION\" CONTENT=\"", $setf,"\">";
print  "<META HTTP-EQUIV=\"REFRESH\"      CONTENT=\"0;URL=", $setf, "\">";


print $query->end_html;
 

 




