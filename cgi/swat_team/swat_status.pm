#! /opt/star/bin/perl

# drive for SWAT team  status page
# pmj 31/7/00

#=========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Report_object;
use Report_collection;

use strict;
#=========================================================
print header;
print start_html('STAR Analysis Status'),
  h1('STAR Analysis: Status of Common Issues');
#---------------------------------------------------------------------------
my $report_dir = "/afs/rhic/star/users/jacobs/public/swat_team";
#---------------------------------------------------------------------------
my $collection = new Report_collection("Test Collection", $report_dir);
#---------------------------------------------------------------------------
$collection->Display();
#---------------------------------------------------------------------------
print end_html;

