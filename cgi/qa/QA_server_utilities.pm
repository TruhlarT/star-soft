#! /usr/bin/perl

# general utilities used by various scripts

# pmj 1/7/99
#=========================================================
package QA_server_utilities;
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
use QA_cgi_utilities;
#=========================================================
1.;
#===================================================================
sub display_server_batch_queue{

  print "<H2> Server batch (\"at\") queue </H2>\n";

  #-----------------------------------------------------------------------------
  
  $queue_file = "$batch_dir/at_queue";
  system("atq > $queue_file");
  
  open ATQ, $queue_file;
  
  print "<pre>\n";
  while (defined($line = <ATQ>)){print "$line \n";}
  print "</pre>\n";
  
  close ATQ;
  
}
#========================================================
sub display_server_log{

  $server_log = "/usr/local/apache/var/log/error_log";
  
  $max_lines = 200;

  #--------------------------------------------------------
  
  print "<H2> Tail End of Apache Server Log </H2>\n";
  
  print "<h4> file is $server_log</h4>\n";
  
  #-----------------------------------------------------------------------------
  
  open (LOGFILE, $server_log) or die "cannot open $server_log: $!<BR>";
  
  # dump contents of log file to array for parsing
  @logfile = <LOGFILE>;
  
  #---------------------------------------------------------
  
  # display logfile backwards
  
  $icount = 0;
  
  while ( $line  = pop @logfile ){
    print $line,"<br>\n";
    last if $icount++ > $max_lines; 
  }
}
#========================================================
sub display_batch_logfiles{

  print "<h3> Batch jobs in progress: </h3> \n";
  $dir = "$batch_dir";
  $dir_WWW = "$batch_dir_WWW";
  batch_logfile_anchors($dir, $dir_WWW);

  print "<hr><h3> Completed batch jobs: </h3> \n";
  $dir = "$batch_dir/done";
  $dir_WWW = "$batch_dir_WWW/done";
  batch_logfile_anchors($dir, $dir_WWW);

}
#========================================================
sub batch_logfile_anchors{

  my $dir = shift;
  my $dir_WWW = shift;

  #-----------------------------------------------------------

  opendir (DIR, $dir) or print "Cannot open directory $dir:$! \n";

  my %batch_log = ();

  # get filename and creation time
  while ( defined($file = readdir(DIR))){
    $file =~ /\.html/ and $batch_log{$file} = stat("$dir/$file")->mtime; 
  }

  closedir(DIR);

  # sort in time
  @keys = sort { $batch_log{$b} <=> $batch_log{$a} } keys %batch_log;
  
  #--------------------------------------------------------------

  if (@keys){

    # display
    foreach $file (@keys){
      
      $full_file = "$dir/$file";
      $full_file_WWW = "$dir_WWW/$file";
      $time_string = "Created ".localtime($batch_log{$file}).":";
      QA_cgi_utilities::make_anchor($time_string, $full_file, $full_file_WWW);
      
    }
  }

  else{
    print "None <br> \n";
  }
}
