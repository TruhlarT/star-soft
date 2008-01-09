#!/usr/bin/env perl
#
# $Id:
#
# $Log:  
#
# jobsData.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

 require "/afs/rhic.bnl.gov/star/packages/cgi/dbProdSetup.pl";
 
use Class::Struct;
use CGI;

my $debugOn = 0;

my @jbDate;
my @jobDates;
my $njob = 0;
my $today;

 ($sec,$min,$hour,$mday,$mon,$yr) = localtime;
   $mon++;
 if( $mon < 10) { $mon = '0'.$mon };
 if( $mday < 10) { $mday = '0'.$mday };
 my $year = 1900 + $yr;

 $today = $year."-".$mon."-".$mday;  

&StDbProdConnect();

$sql="SELECT DISTINCT mdate FROM $crsStatusT order by mdate ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

    for($i=0;$i<$cols;$i++) {
       my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
       print "$fname = $fvalue\n" if $debugOn;

     $mydate = $fvalue  if($fname eq 'mdate'); 
      }
        $jbDate[$njob] = $mydate;
        $njob++;
      }

    $jobsDate[0] = $today;
  for ($ll = 0; $ll < $njob; $ll++)  {
    $jobsDate[$ll+1]= $jbDate[$njob - $ll -1]
  }
  
  
&StDbProdDisconnect();

$query = new CGI;

print $query->header;
print $query->start_html('jobsDate');
print $query->startform(-action=>"CRSjobsStatus.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Production Dates" CONTENT="Production Dates">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
 
  
  print " <title>Production Dates</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ccffff\"> \n";
  print "  <h1 align=left>Dates of Production </h1>\n";
  print " </head>\n";
  print " <body>";


print "<br>";
print "<p>";
print "<B><font size=4> First </font></B> ";
print $query->popup_menu(-name=>'dateFst',  
                   -values=>\@jobsDate,
                   -default=>$today,                                                
                   -size=>1
);  

print "<p>";
print "<B><font size=4> Last </font></B> ";
print $query->popup_menu(-name=>'dateLst',  
                   -values=>\@jobsDate,
                   -default=>$today,                                                
                   -size=>1
);  
 
 print "<p><br><br>"; 
 print $query->submit;
 print "<P><br>", $query->reset;
 print $query->endform;
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
  

#=======================================================================

if($query->param) {
  CRSjobsStatus($query);
}
print $query->end_html; 







