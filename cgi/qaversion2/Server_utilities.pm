#! /usr/bin/perl

# general utilities used by various scripts

# pmj 1/7/99
#=========================================================
package Server_utilities;
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

use IO_object;

use Batch_utilities; #BEN
#=========================================================
1.;
#===================================================================
sub display_server_batch_queue{

  print "<H4> Server batch queue </H4>\n";

  #-----------------------------------------------------------------------------
# BEN (2jun00):  Eliminated temporary queue file and incorporated 
#                queue retrieval into Batch_utilities     

  print "<pre>\n";
  print Batch_utilities::Queue();
  print "</pre>\n";
  
}
#========================================================
sub display_server_log{

  $io = new IO_object("ServerLogFile");
  $server_log = $io->Name();

  # dump contents of log file to array for parsing
  $fh = $io->Open();
  @logfile = <$fh>;
  undef $io;

  #--------------------------------------------------------
  # display logfile backwards
  
  print "<H2> Tail End of Apache Server Log </H2>\n";
  
  print "<h4> file is $server_log</h4>\n";

  $max_lines = 200;
  $icount = 0;
  
  while ( $line  = pop @logfile ){
    print $line,"<br>\n";
    last if $icount++ > $max_lines; 
  }
}
#========================================================
sub display_batch_logfiles{

  print "<h3> Batch jobs in progress: </h3> \n";

  #------------------------------------------------

  $io_dir = new IO_object("BatchDir");
  $dir = $io_dir->Name();
  undef $io_dir;

  $io_dir_WWW = new IO_object("BatchDirWWW");
  $dir_WWW = $io_dir_WWW->Name();
  undef $io_dir_WWW;

  batch_logfile_anchors($dir, $dir_WWW);

  #------------------------------------------------

  print "<hr><h3> Completed batch jobs: </h3> \n";

  $io_dir = new IO_object("BatchDirDone");
  $dir = $io_dir->Name();
  undef $io_dir;

  $io_dir_WWW = new IO_object("BatchDirDoneWWW");
  $dir_WWW = $io_dir_WWW->Name();
  undef $io_dir_WWW;

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
