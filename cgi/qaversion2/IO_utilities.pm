#! /usr/bin/perl -w

# contains miscellaneous utilities that do I/O but not supported by
# IO_object .

# intention is to concentrate all routines with specific reference to
# file names here in IO_object if poccible, otherwise here

# pmj 24/5/00

#=========================================================
package IO_utilities;
#=========================================================

use CGI qw(:standard escapeHTML);
use CGI::Carp qw(fatalsToBrowser);

use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Time::Local;
use Storable;

#use KeyList_object;

use QA_globals;

use strict 'vars';

#=========================================================
1.;
#===================================================================
sub CheckBatchStatus{

  my $print_string = "";

  my $io_BatchDir = new IO_object("BatchDir");
  my $batch_dir_local =  $io_BatchDir->Name();
  undef $io_BatchDir;

  my $io_UpdateDir = new IO_object("UpdateDir");
  my $dh = $io_UpdateDir->Open();
  my $update_dir_local =  $io_UpdateDir->Name();

  my $file;

  while ( defined( $file = readdir($dh) ) ){

    $file !~ /(\d+)\.csh/ and next;

    my $batch_job_file = "$batch_dir_local/$file";

    my $start_time = stat("$update_dir_local/$file")->mtime; 
    my $time_string = " (started ".localtime($start_time).")";
    
    if ( -e $batch_job_file ){
      $print_string = "<font color=blue>Update and QA batch job in progress $time_string</font><br>";
    }
    else{
      my $full_file = "$update_dir_local/$file";
      unlink($full_file);
    }
  }

  undef $io_UpdateDir;

  return $print_string;

}
#===================================================================
# currently i dont use this

sub GetGlobalMessages{

  my $io_dir = new IO_object("MessageDir");
  my $dh = $io_dir->Open();

  my $message_key;
  while ( defined ($message_key = readdir($dh))){

    $message_key =~ /global/ or next;

    my $io_file = new IO_object("MessageFile", $message_key);
    my $message_file = $io_file->Name();
    undef $io_file;

    if ( -e $message_file ){
      $QA_message_hash{$message_key} = retrieve($message_file)
	or print "Cannot retrieve file $message_file:$! <br>\n";
    }
    else {
      print "IO_utilities::GetGlobalMessages: file $message_file not found <br> \n";
    }

  }
  
  undef $io_dir;

}
#==============================================================
sub CleanUpScratch{

  #-----------------------------------------------------------
  # do a general cleanup of object scratch file directory -
  # delete everything older than 12 hours

  my $io_dir = new IO_object("ScratchDir");
  my $dh = $io_dir->Open();

  my $dir_name = $io_dir->Name();

  my $file;

#  unlink { -M $_ > 0.5 } map {"$dir_name/$_"} readdir $dh;

  while ( defined( $file = readdir($dh) ) ){

    my $full_file = "$dir_name/$file";

    -M $full_file > 0.5 and do{
      unlink($full_file);
    };

  }

  undef $io_dir;
}
#==============================================================
# BEN(4jun2000):
#
# ComposeBatchScript($action, $data_class, $batchscript_filename, 
#                    $job_filename, 
#                    $batch_log_html, $done_dir [, $report_key])
# 
# all arguments are required except $report_key, which may specify one
# particular job to do qa on.
#
# $action is as described in QA_main::DoBatch
# $data_class is a valid type from DataClass_object
sub ComposeBatchScript{

    my $action = shift;
    my $data_class = shift;
  my $batchscript_filename = shift;
  my $job_filename = shift;
  my $batch_log_html = shift;
  my $done_dir = shift;
  my $report_key = shift;
  
  #----------------------------------------------------------------
  my $now = getcwd();
  my $program = "$now/QA_main.pm"; #BEN(3jun00): no more QA_main_batch
    
    # BEN(4jun2000): took out TopDir stuff....we have data_class

  my $string = "#! /usr/local/bin/tcsh \n".
    "setenv GROUP_DIR /afs/rhic/rhstar/group \n".
      "setenv CERN_ROOT /cern/pro \n".
	"setenv HOME /star/u2e/starqa \n".
	  "setenv SILENT 1 \n".
	      "source /afs/rhic/rhstar/group/.stardev \n";

  $string .= "echo \"Starting perl script...<br>\" >& $batch_log_html \n".
    "/opt/star/bin/perl -I$now $program batch_job $data_class $action ".
	($report_key ? "$report_key " : "") . 
	    ">>& $batch_log_html \n".
      "echo \"Moving files...\" >>& $batch_log_html \n".
	"\\mv $batchscript_filename $done_dir \n".
	    "\\mv $batch_log_html $done_dir \n".
	      "\\rm -f $job_filename \n";
  
  return $string;
}
#==============================================================
sub ComposeBatchJob{

  my $batchscript_filename = shift;

  #----------------------------------------------------------------

  #BEN(5jun2000):  had wrong path to ksh, try just /bin/sh
  my $string = "#! /bin/sh \n".
    "$batchscript_filename \n";
 
  return $string;
}
#============================================================
sub PrintLastUpdate{
  my $io = new IO_object("UpdateFile");
  my $fh = $io->Open(">","0664");

  print $fh scalar localtime,"\n";
}
#===========================================================
sub move_old_reports{

  my $io_dir = new IO_object("TopdirReport");
  my $dh = $io_dir->Open();
  my $dir_name = $io_dir->Name();

  my $io_dir_old = new IO_object("TopdirReportOld");
  my $dir_name_old = $io_dir->Name();
  undef $io_dir_old;

  my $report;
  while ( defined ( $report = readdir $dh ) ){
    
    # move if older than 30 days
    
    next if $report =~ /^\./;
    next unless is_old_report($report); # bum - 10/03/00 

    my $name = "$dir_name/$report";
    
    # $next unless -M $name; 
    
    my $name_move = "$dir_name_old/$report";
    
    print "cp -rp $name $name_move <br> \n";
#    system ("cp -rp $name $name_move");

    print "\\rm -rf $name <br> \n";
#    system ("\\rm -rf $name");
    
  }
}

#============================================================
# bum 10/3/00 - called in move_old_reports above

sub is_old_report{
  my $report  = shift;
  my ($day, $month, $year, $report_age);

# pmj 3/6/00
  my $oldtime = 30*24*3600;
  my $now     = timelocal( 0,0,0, (localtime)[3,4,5]);
#---

  # extract date from report_dir.  e.g. blah.250300 (day,month,year)
  ($day, $month, $year) = ($report =~ /(\d{2})(\d{2})(\d{2})$/);
  
  # error check
  if (not defined $day ) {
    print "$report has a faulty date\n"; return;
  }

  # convert it to epoch seconds - note that this doesnt work after 2038...
  $year = 100 + $year if $year < 38; # timelocal conversion
  $month--; # ditto
  $report_age =  timelocal(0,0,0, $day, $month, $year);

  # return true if older than 30 days ($oldtime)  
  # see move_old_reports above for $now and $oldtime
  return ($now - $report_age > $oldtime) ? 1 : 0;
}
