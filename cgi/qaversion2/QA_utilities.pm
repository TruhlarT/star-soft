#! /usr/bin/perl

# general utilities used by main routines

# pmj 31/8/99
#=========================================================
package QA_utilities;
#=========================================================

use strict;

#use CGI qw/:standard :html3 -no_debug/;
#use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);
use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Storable;
use Data::Dumper;

use Time::Local;
use QA_message;
use QA_globals;

use HiddenObject_object;
use Server_object;

use Batch_utilities;

use QA_object_nightly;
use QA_object_offline;

use DataClass_object;
use Db_update_utilities;
#=========================================================
1.;
#=================================================================
sub sort_time{

  my $key = shift;

  $key or return -99999;

  my $time;

  if ( exists $QA_message_hash{$key} ){
    $time = $QA_message_hash{$key}->CreationEpochSec;
  }
  elsif ( exists $QA_object_hash{$key} ){
    $time = $QA_object_hash{$key}->CreationEpochSec;
  }
  else{
    $time = -99999;
  }

  return $time;

}
#=================================================================
# BEN(4jun2000)
# 
# submit_batchjob($action [, $report_key])
#
# $report_key is optional and allows the user to specify a particular
# job to do qa on.
sub submit_batchjob {

  my $action = shift;
  my $report_key = shift;

  # BEN(4jun2000): find what data class we're dealing with
  my $data_class = $gDataClass_object->DataClass();

  #-----------------------------------------------------------------------
  # special check for update_and_qa: prevent multiple jobs of this type
  # pmj 10/5/00

  $action eq 'update_and_qa' and do{

    my $string = &IO_utilities::CheckBatchStatus;

    $string and do{
      print "<font color=red>Update and QA batch job found, new one not submitted.</font><br>\n";
      return;
    };
  };
  #-----------------------------------------------------------------------
  # set random seed for unique file ID

  srand;
  my $id_string = int(rand(1000000));

  my $io = new IO_object("BatchLogHTML", $id_string);
  my $batch_log_html = $io->Name();
  undef $io;

  $io = new IO_object("BatchDirDone");
  my $done_dir = $io->Name();
  undef $io;

  # BEN(4jun2000):  Took out report_key_file (max of 1 report key now)

  # make file in report_key directory to flag that batch job is in progress
  if ($report_key){
      
      my $io_status = new IO_object("BatchStatusReport", $id_string, $action, $report_key);
      my $STATUS = $io_status->Open(">");
      print $STATUS scalar localtime, "\n";
      undef $io_status;
  }

  #-----------------------------------------------------------------------
  # open job here because we need its name in batch script...

  my $io_job = new IO_object("BatchJob", $id_string);
  my $job_filename = $io_job->Name();
  undef $io_job;
  
  #-----------------------------------------------------------------------
  # now compose batch script, write to file

  my $io_batch = new IO_object("BatchScript", $id_string);
  my $BATCH = $io_batch->Open(">", "0755");
  my $batchscript_filename = $io_batch->Name();

  my $string = IO_utilities::ComposeBatchScript($action, $data_class, 
						$batchscript_filename, 
						$job_filename, $batch_log_html,
						$done_dir, $report_key);

  print "<h3>My batch script is:</h3>\n<pre>\n$string\n</pre>\n";
  print $BATCH $string;

  undef $io_batch;

  #-----------------------------------------------------------------------

  $io_job = new IO_object("BatchJob", $id_string);
  my $JOB = $io_job->Open(">", "0755");

  $string = IO_utilities::ComposeBatchJob( $batchscript_filename );
  print $JOB $string;

  undef $io_job;
  #-----------------------------------------------------------------------
  # submit batch job
 
  #BEN (2jun2000): use Batch_utilities
  my $status = Batch_utilities::SubmitJob($job_filename);

  #----------------------------------------------------------------------
  # if this is an update job, copy csh file to update directory for reporting 
  # updates-in-progress

  $action =~ /update/ and do{
    my $update_dir_local = $gDataClass_object->UpdateDir();
    system("cp $batchscript_filename $update_dir_local");
  };
  
  #----------------------------------------------------------------------
  # show queue status

  print "<h4> Job submitted, status  = $status <br> </h4> \n";

  &Server_utilities::display_server_batch_queue;

}
#===========================================================
sub print_refresh{
  print "<h3> <font color = blue> To refresh upper panel when done, reselect dataset </font> </h3> \n";
  return;
}
#===========================================================
sub print_button_object_hash{

  my ($package, $filename, $line) = caller;

  print "-" x 80, "\n<br> print_button_object_hash called from $package::$filename, line $line <br> \n";

  my $key;
  foreach $key ( keys %Button_object_hash ){

    my $object_ref = $Button_object_hash{$key};
    my $object = $$object_ref;

    my $name = $object->ButtonName;
    my $method = $object->MethodName;
    my $value = $object->ButtonValue;
    my $report_key = $object->ReportKey;

    print "ref = $object_ref, name = $name, method = $method, value = $value, report_key = $report_key <br> \n";

  }

}
#=======================================================================
sub print_traceback{

  print "=" x 80, "\n<br> print_traceback called <br> \n";

  my $i = 0;
  while ( my ($package, $filename, $line, $sub, $hasargs, $wantarray) = caller($i++) ){
    print "from $package::$filename, line $line, subroutine $sub <br> \n";
  }

  print "=" x 80, "<br> \n";

}
#=======================================================================
sub run_DSV{

#  my $report_key = shift;
#
#  $report_key or do{
#    print "Error in QA_utilities::run_DSV: valid report key not supplied <br> \n";
#    return;
#  };
#  #-----------------------------------------------------------------------------
#
#  my $global_input_data_type = ".dst.xdf";
#  my $production_dir = $QA_object_hash{$report_key}->LogReport->OutputDirectory; 
#  find( \&QA_cgi_utilities::get_file, $production_dir );
#
#  if ( ! -e $global_filename ){
#    print "Error in QA_utilities::run_DSV: file with type .dst.xdf not found in $production_dir <br> \n";
#    return;
#  };
#
#  $xdf_file = $global_filename;
#
# #-----------------------------------------------------------------------------
#  $DISPLAY = $gCGIquery->param('display_env_var');
#
#  if ($DISPLAY){
#    print "Current DISPLAY environment variable is $DISPLAY <br> \n";
#  }
#  else{
#    print "DISPLAY environment variable not set. Set it and try again. <br> \n";
#    return;
#  }
#
#  #-----------------------------------------------------------------------------
#  print "Starting dsv on file $xdf_file... <br> \n";
#  #-----------------------------------------------------------------------------
#  # create temporary csh script, use process pid ($$) to make unique name
#
#  $proc_id = $$;
#
#  my $io = new IO_object("DSVRunScript", $proc_id);
#  my $fh = $io->Open(">", "0755");
#  my $script_name = $io->Name();
#
#  # make sure it disappears at the end...
#  END { unlink($script_name) };
#
#  # write to script
#  print $fh "#! /usr/local/bin/tcsh\n",
#  "setenv GROUP_DIR /afs/rhic/rhstar/group\n",
#  "setenv CERN /cern\n",
#  "setenv CERN_ROOT /cern/pro\n",
#  "setenv HOME /star/u2e/starqa\n",
#  "setenv DISPLAY $DISPLAY\n",
#  "source /afs/rhic/rhstar/group/.stardev\n",
#  "setenv DSV_DIR /afs/rhic/star/tpc/dsv\n",
#  "echo Doing: source /afs/rhic/star/tpc/dsv/set_path\n",
#  "source /afs/rhic/star/tpc/dsv/set_path\n",
#  "echo Doing: rpoints -xdfFile $xdf_file -event dst_0\n",
#  "rpoints -xdfFile $xdf_file -event dst_0 &\n";
#
#  undef $io;

  #-----------------------------------------------------------------------------
  # 2nd layer - needed to get clean return of control to web page, not sure why this 
  # happens pmj 12/1/99

#  my $io_submit = new IO_object("DSVSubmitScript", $proc_id);
#  my $fh_submit = $io_submit->Open(">", "0755");
#  my $submit_script_name = $io_submit->Name();
  
  # make sure it disappears at the end...
#  END { unlink($submit_script_name) };

  # write to script
#  print $fh_submit "#! /usr/local/bin/tcsh\n",
#  "$script_name\n";

# undef $io_submit;

  #-----------------------------------------------------------------------------

#  print "Running DVS on display $DISPLAY, input file $xdf_file... <br> \n";
#  system("$submit_script_name &");
#  print "DSV is running independently, control has returned to web page<br> \n";

}
#=======================================================================
sub comment_form{

  my $arg = shift;
  #-----------------------------------------------------------------------------
  # pmj 23/12/99 form for creating new comment

  my $author = $gCGIquery->param('enable_add_edit_comments');

  #-----------------------------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  print $gCGIquery->startform(-action=>"$script_name/lower_display", 
			  -TARGET=>"display"); 

  print "<h4> Author: </h4>",
        $gCGIquery->textfield('comment_author', $author, 50, 80),"<br>\n";

  my $etime;
  if ($arg eq 'global' ){
    $etime = time;
  }
  else{
    $etime = $QA_object_hash{$arg}->CreationEpochSec + 1;
  }
  my $date = epochsec_to_message_time($etime);
  #---

  print "<h4> Date and Time: </h4>",
  "(Must be in format hh:mm dd/mm/yy to be parsed properly,",
  "otherwise message will not be in correct chronological order)<br>",
  $gCGIquery->textfield('comment_date', $date, 50, 80),"<br>\n";


  print "<h4> Comment text: </h4>",$gCGIquery->textarea(-name=>'comment_text', 
						     -value=>'', 
						     -rows=>10, 
						     -cols=>60,
						     -wrap=>'virtual')
    ,"<br>\n";


  #---
  # is this global comment or comment specific to a run?

  my $button_ref;
  if ( $arg eq 'global'){
    $button_ref = Button_object->new('NewComment', 'Submit');
  }
  else{
    $button_ref = Button_object->new('NewComment', 'Submit', $arg);
  }

  #---

  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<br>",$button_ref->SubmitString.$hidden_string;

  print $gCGIquery->endform;

}
#=====================================================================
sub create_comment_object{

  my $arg = shift;

  #----------------------------------------------------------------
  my $message_key;

  if ( $arg eq 'global' ){
    # this is a global comment, not tied to a specific run 
    #get a string of current date and time
    my $string = &QA_cgi_utilities::yymmddhhmmss;
    $message_key = "global.$string.msg";
  }
  else{
    $message_key = "$arg.msg";
  }

  #----------------------------------------------------------------

  my $author = $gCGIquery->param('comment_author');

  my $date;
  my $etime;

  if ($arg eq 'global' ){
    $date = $gCGIquery->param('comment_date');
    $etime = message_time_to_epochsec($date);
  }
  else{
    $etime = $QA_object_hash{$arg}->CreationEpochSec + 1;
  }

  my $text = $gCGIquery->param('comment_text');

  #----------------------------------------------------------------

  my $message_ref = QA_message->new($message_key,$author,$etime,$text);
  $QA_message_hash{$message_key} = $message_ref;

  #----------------------------------------------------------------

  my $io = new IO_object("MessageFile", $message_key);
  my $message_file = $io->Name();
  undef $io;
  
  store($message_ref, $message_file ) or 
    print "<h4> Cannot write $message_file: $! </h4> \n";
}
#=====================================================================
sub edit_comment{

  my $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::edit_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  my $author = $QA_message_hash{$message_key}->Author;

  my $temp = $QA_message_hash{$message_key}->CreationEpochSec;
  my $date = epochsec_to_message_time($temp);

  my $text = $QA_message_hash{$message_key}->MessageString;

  #-----------------------------------------------------------------------------

  print "<h3> Modify comment fields and press Submit. Reselect dataset to display modifications. </h3>";

  my $script_name = $gCGIquery->script_name;
  print $gCGIquery->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 

  print "<h4> Author: </h4>",$gCGIquery->textfield('comment_author', $author, 50, 80),"<br>\n";


  print "<h4> Date and Time: </h4>",
  "(Must be in format hh:mm dd/mm/yy to be parsed properly,",
  "otherwise message will not be in correct chronological order)<br>",
  $gCGIquery->textfield('comment_date', $date, 50, 80),"<br>\n";

  print "<h4> Comment text: </h4>",$gCGIquery->textarea(-name=>'comment_text', 
						     -value=>$text, 
						     -rows=>10, 
						     -cols=>60,
						     -wrap=>'virtual')
    ,"<br>\n";

  my $button_ref = Button_object->new('ModifyComment', 'Submit', $message_key);
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<br>",$button_ref->SubmitString.$hidden_string;

  print $gCGIquery->endform;

}
#=====================================================================
sub modify_comment{

  my $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::modify_global_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  my $author = $gCGIquery->param('comment_author');
  my $date = $gCGIquery->param('comment_date');
  my $text = $gCGIquery->param('comment_text');

  #----------------------------------------------------------------
  $QA_message_hash{$message_key}->Author($author);

  my $etime = message_time_to_epochsec($date);
  $QA_message_hash{$message_key}->CreationEpochSec($etime);

  $QA_message_hash{$message_key}->MessageString($text);

  #----------------------------------------------------------------
  # save modification on disk also

  my $message_ref = $QA_message_hash{$message_key};

  my $io = new IO_object("MessageFile", $message_key);
  my $message_file = $io->Name();
  undef $io;
  
  store($message_ref, $message_file ) or 
    print "<h4> Cannot write $message_file: $! </h4> \n";
}
#=====================================================================
sub delete_comment{

  my $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::modify_global_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  print "Delete comment for message key $message_key...<br> \n";

  my $io = new IO_object("MessageFile", $message_key);
  my $old_file = $io->Name();
  undef $io;

  $io = new IO_object("DeletedMessageFile", $message_key);
  my $new_file = $io->Name();
  undef $io;

  system("mv $old_file $new_file");

  delete( $QA_message_hash{$message_key} );

  print "...done. Reselect dataset to remove comment from current listing.<br>\n";

}
#==========================================================================
sub epochsec_to_message_time{

  my $temp = shift;

  my ($sec,$min,$hour,$mday,$mon,$year,$junk) = localtime($temp);

  $sec < 10 and $sec = "0".$sec;
  $min < 10 and $min = "0".$min;
  $hour < 10 and $hour = "0".$hour;
  $mday < 10 and $mday = "0".$mday;

  $mon += 1;
  $mon < 10 and $mon = "0".$mon;

  $year > 99 and $year -= 100;
  $year < 10 and $year = "0".$year;

  my $string = "$hour:$min $mday/$mon/$year";

  return $string;
}
#==========================================================================
sub message_time_to_epochsec{

  my $string = shift;

  my $etime = -9999;

  $string =~ /(\d+):(\d+) (\d+)\/(\d+)\/(\d+)/ and do{

    my $hour = $1;
    my $min = $2;
    my $sec = 0;

    my $mday = $3;
    my $mon = $4 - 1;
    my $year = $5;

    $etime = timelocal($sec, $min, $hour, $mday, $mon, $year);

  };
  
  return $etime;
}
#========================================================================
# bum db - called in QA_main::display_datasets, QA_main_batch

sub make_QA_objects{

  my @selected_keys = @_; # create these objects

  #retrieve_objects() if defined $gCGIquery; # if from browser
       
  # we got the selected keys from QA_main::get_selected_keys
  # create the objects
  # note $QA_obj is a global

  foreach my $report_key (@selected_keys){
    exists $QA_object_hash{$report_key} or
      $QA_object_hash{$report_key} = 
	$gDataClass_object->QA_obj->new($report_key);
  }
}
#================================================================
sub doUpdate{

  # pmj 3/6/00 This is the steering routine for doing udpates. gDataClass_object
  # must already exist to specify which data class to update. The update keys are gotten
  # from the DB, and then update_QA_objects is called to create the new objects (including
  # extracting logfile info

  no strict 'refs';

  my $update_routine = $gDataClass_object->UpdateRoutine();
  my @updated_keys = &$update_routine;
  #------------------------------------------------------------------------------------

  if (not defined @updated_keys) {
    print "<font color=red><h1>No jobs to update</h1></font>";
    return;
  } 
  #------------------------------------------------------------------------------------

  # make the report directories and parse log file

  QA_utilities::update_QA_objects(@updated_keys);
}
#================================================================
# bum db
# makes QA_objects that are not in the db and creates an logfile
# Note the switch statement for determining the class of data!

sub update_QA_objects{
  my @key_list = @_;
  
  # note $gDataClass_object->QA_obj is a global
  foreach my $report_key (@key_list){
      $QA_object_hash{$report_key} = 
	$gDataClass_object->QA_obj->new($report_key,'update');
  }
  IO_utilities::PrintLastUpdate();

}

#==========================================================================
# bum
# convert YYYY-MM-DD hh:mm:ss to epoch sec

sub datetime_to_epochsec{

  my $datetime = shift; # YYYY-MM-DD hh:mm:ss

  my ($date, $time)        = split /\s+/, $datetime;
  my ($year, $month, $day) = split /-/, $date;
  my ($hour, $min, $sec)   = split /:/, $time;

  # get out if there's an error
  unless (defined $date and defined $time){
    warn "Bad datetime"; return;
  }

  return timelocal($sec, $min, $hour, $day, $month-1, $year-1900);
}
#==========================================================================
# bum 
# convert the weird date time scheme in the log file
# to the conventional year-month-day hour:min:sec format

sub convert_logdatetime{
  my $logdatetime = shift; # e.g. 20000516/5839

  return if not defined $logdatetime; #error?

  my ($date, $time) = split /\//, $logdatetime;

  my $year  = substr($date, 0, 4);
  my $month = substr($date, 4, 2);
  my $day   = substr($date, 6, 2);
  my $hour  = substr($time, -6, 2);
  my $min   = substr($time, -4, 2);
  my $sec   = substr($time, -2, 2);

  my $count;

  $count = $hour =~ tr/0-9//;

  $hour = "0$hour" if $count == 1;
  $hour = "00"     if $count == 0;

  $count = $min =~ tr/0-9//;

  $min = "0$min" if $count == 1;
  $min = "00" if $count == 0;

  return "$year-$month-$day $hour:$min:$sec";
}
