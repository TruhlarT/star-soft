#! /usr/bin/perl

# general utilities used by various scripts

# pmj 1/7/99
#=========================================================
package QA_cgi_utilities;
#=========================================================

use CGI qw(:standard escapeHTML);
use CGI::Carp qw(fatalsToBrowser);

use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Time::Local;

use QA_globals;
#=========================================================
1.;
#===================================================================

sub make_anchor{

  my $message = shift (@_);
  my $filename = shift (@_);
  my $link = shift (@_);

  print "$message: <a href=$link>$filename</a> <br> \n";

}
#==========================================================
sub get_file{
  
  $filename = $File::Find::name;

  my @string = split  /\./, $filename;
  my $filetype = ".".$string[-2].".".$string[-1];

  $global_input_data_type eq $filetype and $global_filename = $filename;

}
#==========================================================
sub get_logfile{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.log$/ ) {
    $global_logfile = $filename;
  }
}
#==========================================================
sub get_root_dst_file{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.dst\.root/ ) {
    $global_root_dst_file = $filename;
  }
}
#==========================================================
sub get_root_hist_file{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.hist\.root/ ) {
    $global_root_hist_file = $filename;
  }
  
}
#==========================================================
sub get_root_event_file{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.event\.root/ ) {
    $global_root_event_file = $filename;
  }
  
}
#==========================================================
sub get_xdf_file{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.dst\.xdf/ ) {
    $global_dst_xdf_file = $filename;
  }
  
}
#==========================================================
sub convert_logtime_to_epoch_sec{
  
  # converts time string from format in log file to one usable by localtime

  $in_string = shift;

  # make sure there is something in the string;
  $in_string or return 0;

  # time given in log file as YYYYMMDD/(H)HMMSS, where H can be one or two digits (!!??)
  
  $year = substr($in_string, 0, 4) - 1900;
  $month = substr($in_string, 4, 2) - 1;
  $mday = substr($in_string, 6, 2);
  $hour = substr($in_string, -6, 2);
  $min = substr($in_string, -4, 2);
  $sec = substr($in_string, -2, 2);
  
  $hour =~ s/\///;
  
  return timelocal($sec, $min, $hour, $mday, $month, $year);
  
}
#==========================================================
sub yymmddhhmmss{
  
  ($sec, $min, $hour, $mday, $mon, $year) = localtime;

  $sec < 10 and $sec = "0".$sec;

  $min < 10 and $min = "0".$min;

  $hour < 10 and $hour = "0".$hour;

  $mday < 10 and $mday = "0".$mday;

  $mon += 1;
  $mon < 10 and $mon = "0".$mon;

  $year > 99 and $year -= 100;
  $year < 10 and $year = "0".$year;

  return $year.$mon.$mday.$hour.$min.$sec;
}
#=================================================================================
sub print_page_header{

  my $header_string = shift;

  print "<table border=0 width=100% cellpadding=0>",
    "<tr bgcolor=red>",
    "<td align=left valign=top>",	  
    "<ul>",
    "<h4><br></h4>",  
    "<h1><font color=darkblue>$header_string</font></h1>",
    "</ul>",
    "</td>",
    "</table>",
    "\n";
  

  # ad hoc determination of where to find documentation...if checked out into jacobs area,
  # this is development version, otherwise, this is in library
  $now = cwd();
  if ($now =~ /jacobs/){
    $doc_link ="http://www.star.bnl.gov/STARAFS/comp/qa/pmj/index.html";
  }
  else{
#    $star_level = $ENV{STAR_LEVEL};
    $doc_link = "http://duvall.star.bnl.gov/STARAFS/comp/pkg/dev/cgi/qa/doc/index.html";
  }

#  print "<hr noshade=noshade>",
#  "<address><a href=mailto:pmjacobs\@lbl.gov>webmaster</a></address>";
#  print "<p align=left><a href=$doc_link target='display'>Documentation </a> </p>\n";

  print "<hr noshade=noshade>";

  $webmaster_string = "<address><a href=mailto:pmjacobs\@lbl.gov>webmaster</a></address>";
    
  $doc_string = "<a href=$doc_link target='display'>Documentation </a>";

  my $name = basename($topdir);
  my $current = "<font size=+1><b>You are in $name</b><font>" ;

  @table_rows = (); 
  push( @table_rows, td( [$doc_string, $webmaster_string, $current ]) );
#  print table( {-width=>'20%', -valign=>'top', -align=>'left'}, Tr(\@table_rows));
  print table( {-width=>'50%'}, Tr(\@table_rows));

#  print "<br><hr noshade=noshade> \n";
#  print "<p> \n";

  #---------------------------------------------------------------------------------

  return;
}
