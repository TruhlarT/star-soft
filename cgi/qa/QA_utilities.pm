#! /usr/bin/perl

# general utilities used by main routines

# pmj 31/8/99
#=========================================================
package QA_utilities;
#=========================================================

#use CGI qw/:standard :html3 -no_debug/;
use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);
use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Storable;
use Data::Dumper;

use Time::Local;

use QA_globals;
#=========================================================
1.;
#===========================================================
sub cleanup_topdir{

  # some cleanup(pmj 23/6/99): File::Find doesn't seem to like soft links, so
  # run through list of dirs and replace with hard links
  
  $now = cwd();
  
  foreach $dir (@topdir_data){
    chdir $dir;
    push @temp, cwd();
  }
  
  @topdir_data = @temp;
  
  chdir $now;
}
#=================================================================
sub get_QA_objects{

  @_ and my $arg = shift;

  #--------------------------------------------------------
  # retrieve hash

  if ($query){

    #-----------------------------------------------------------
    # do a general cleanup of object scratch file directory -
    # delete everything older than 12 hours

    opendir (SCRATCH, $scratch) or print "Cannot open scratch directory $scratch \n";
    
    while ( defined( $file = readdir(SCRATCH) ) ){
#      $file =~ /\.qa_hash$/ or next;
      my $full_file = "$scratch/$file";
      -M $full_file > 0.5 and do{
	unlink($full_file);
      };
    }
    close (SCRATCH);

    #---------------------------------------------------------

    my $temp = $query->param('save_object_hash_scratch_file');

    if (-e $temp) {

      $Save_object_hash_scratch_file = $temp;
      my $ref = retrieve($Save_object_hash_scratch_file);
      %Save_object_hash = %$ref;

      %QA_object_hash = %{$Save_object_hash{QA_object_hash}};
      %Button_object_hash = %{$Save_object_hash{Button_object_hash}};
      %QA_message_hash = %{$Save_object_hash{QA_message_hash}};

    }
    else {

      %QA_object_hash = ();
      %Button_object_hash = ();
      %QA_message_hash = ();

      #---- 

      # generate unique file ID
      srand;
      my $id_string = int(rand(1000000)); 
      $Save_object_hash_scratch_file ="$scratch/temp_$id_string.persistent_hash";
      $query->param('save_object_hash_scratch_file', $Save_object_hash_scratch_file);
#      &hidden_field_string;
      
    }

  }
  else {
    %QA_object_hash = ();
    %Button_object_hash = ();
  }
  #-----------------------------------------------------------
  # get report catalogue

  # half of startup time is in this section - can it be reduced?  pmj 3/12/99

  opendir(REPORTDIR, $topdir_report) or die "Couldn't open report directory $topdir_report \n";

  while ( defined ($report_key = readdir(REPORTDIR))){

    # key must end in six digits
    $report_key =~ /\d{6}$/ or next;

    defined $QA_object_hash{$report_key} or do{

      $QA_object_hash{$report_key} = QA_object->new($report_key);

    };
  }
  
  closedir(REPORTDIR);

  #---------------------------------------------------------------
  # if update, get additional directories on disk

  $arg eq 'update' and do{

    @logfile_list = ();
    
    # bum, toggle -  we only want the logfiles which corresponds
    # to the current directory.  if debug, look in dev.

    switch:{
      $dir = $topdir_data[0] and last if $topdir eq $topdir_dev;
      $dir = $topdir_data[1] and last if $topdir eq $topdir_new;
      $dir = $topdir_data[2] and last if $topdir eq $topdir_cosmics;
      $dir = $topdir_data[0] and last if $topdir eq $topdir_debug;
      print "<h3>Can't find $topdir in updating </h3>\n";
    }
   
    find( \&get_logfiles, $dir );

    #------------------------------------------------
    $dir_list_update_ref = get_update_dirs(@logfile_list);
    @dir_list_update = @$dir_list_update_ref;

    foreach $dir_string ( @dir_list_update ){
      
      $new_qa = QA_object->new($dir_string, $arg);
      $report_key = $new_qa->ReportKey();
      $QA_object_hash{$report_key} = $new_qa;

      print "In QA_main: new directory $dir_string, report key $report_key <br> \n";
      
    }

    # make file giving time of last update
    my $update_filename = "$update_dir/last_update";
    open UPDATE, ">$update_filename" or print "Cannot open update file $update_filename \n";
    print UPDATE scalar localtime, "\n";
    close UPDATE;
    chmod 0664, $update_filename;

  };

  #-----------------------------------------------------------
  # sort directories in time

  @key_list_sorted = ( sort { sort_time($b) <=> sort_time($a) } keys %QA_object_hash );

  #-----------------------------------------------------------
  return @key_list_sorted

}
#=================================================================
sub sort_time{

  my $report_key = shift;

  $report_key or return -99999;

  return $QA_object_hash{$report_key}->CreationEpochSec;

}
#=================================================================
sub submit_batchjob {

  $action = shift;
  @_ and @key_list = @_;

  #bum. toggle - $topdir is passed into QA_main_batch to set directories 
  my $topdir = $query->param('topdir') || $topdir_default;

  #-----------------------------------------------------------------------
  # set random seed for unique file ID
  srand;

  my $id_string = int(rand(1000000));

  my $file_string = "$batch_dir/temp\_$id_string";

  $job_output = "$file_string\.batchjob";

  $report_filename = "$file_string\.$action";
  $batchscript_filename = "$file_string\.csh";
  $output_filename = "$file_string\.html";

  $job_filename = "$file_string\.batch";

  $done_dir = "$batch_dir/done";

  #-----------------------------------------------------------------------
  # file containing report keys to operate on

  @key_list and do {

    open REPORTFILE, ">$report_filename" or die "Cannot open report file $report_filename \n";

    foreach $report_key (@key_list){
      print REPORTFILE $report_key,"\n";

      # make file in report_key directory to flag that batch job is in progress
      my $status_filename = "$topdir_report/$report_key/batch_$id_string\.$action";
      open STATUS, ">$status_filename" or print "Cannot open status file $status_filename \n";
      print STATUS scalar localtime, "\n";
      close STATUS;
      chmod 0664, $status_filename;
    }
    
    close REPORTFILE;
  };

  #-----------------------------------------------------------------------
  # now compose batch  script

  $now = cwd();
  $program = "$now/QA_main_batch.pm";

  open BATCHSCRIPT, ">$batchscript_filename" or die "Cannot open batchfile $batchscript_filename \n";

  print BATCHSCRIPT "#! /usr/local/bin/tcsh \n",
  "setenv GROUP_DIR /afs/rhic/rhstar/group \n",
  "setenv CERN_ROOT /cern/pro \n",
  "setenv HOME /star/u2e/starqa \n",
  "setenv SILENT 1 \n",
  "source /afs/rhic/rhstar/group/.stardev \n";

  print BATCHSCRIPT 
    "echo \"Starting perl script...<br>\" >& $output_filename \n",
    # bum, toggle - main_batch needs $topdir 
    "/opt/star/bin/perl -I$now $program $report_filename $topdir >>& $output_filename \n",
    "echo \"Moving files...\" >>& $output_filename \n",
    "\\mv $batchscript_filename $done_dir \n",
    "\\mv $report_filename $done_dir \n",
    "\\mv $output_filename $done_dir \n",
    "\\rm -f $job_filename \n";

  close BATCHSCRIPT;

  #-----------------------------------------------------------------------
  open JOB, ">$job_filename" or die "Cannot open job file $job_filename \n";

  print JOB "#! /usr/local/bin/ksh \n",
  "$batchscript_filename \n";

  close JOB;

  #-----------------------------------------------------------------------
  chmod 0775, $report_filename;
  chmod 0775, $batchscript_filename;
  chmod 0775, $job_filename;
  #-----------------------------------------------------------------------
  # submit batch job
  
  $status = system("at -f $job_filename now");
#  $status = system("$batchscript_filename");

  #----------------------------------------------------------------------
  # if this is an update job, copy csh file to update directory for reporting 
  # updates-in-progress

  $action =~ /update/ and do{
    system("cp $batchscript_filename $update_dir");
  };
  
  #----------------------------------------------------------------------
  # show queue status

  print "<h4> Job submitted, status  = $status <br> Here is atq: </h4> \n";

  $queue_file = "$batch_dir/at_queue";
  system("atq > $queue_file");

  open ATQ, $queue_file;

  print "<pre>\n";
  while (defined($line = <ATQ>)){print "$line \n";}
  print "</pre>\n";

  close ATQ;

}
#==========================================================
sub get_logfiles{

# look for directories containing log file

  $filename = $File::Find::name;

  $filename =~ /\.log$/ and do {
    push @logfile_list, $filename;
  };
  return;
}
#==========================================================
sub get_update_dirs{

  @logfile_list = @_;

  @dir_list_update = ();

  # bum, toggle
  my $count=1;

  foreach $logfile (@logfile_list){

    # already catalogued?
    $dir_string = dirname($logfile);
    $report_key = QA_make_reports::get_report_key($dir_string); 

    defined $QA_object_hash{$report_key} and next;

    # too large? log files as large as 200 MB have been seen

    $size = -s $logfile;
    $size > 50000000 and do {
      print "Logfile $logfile size=$size; Too large, skipping this run <br> \n";
      next;
    };
    
    # check that run is complete
    
    open LOGFILE, $logfile or die "Cannot open logfile $logfile: $! \n";
    my @lines = <LOGFILE>;
    
    my $job_done = 1;
    
  ENDOFJOB:{
      while (my $line = pop @lines){
	$line =~ /This is the end of ROOT -- Goodbye/ and last ENDOFJOB;
	$line =~ /segmentation violation/ and last ENDOFJOB; 
	$line =~ /QAInfo:Run completed/ and last ENDOFJOB; 
	$line =~ /Broken Pipe/ and last ENDOFJOB; 
	$line =~ /bus error/ and last ENDOFJOB; 
      }
      $job_done = 0;
    }

    if($job_done){
      push @dir_list_update, dirname($logfile)."/"; $count++;
      # bum, toggle
      last if ($topdir eq $topdir_debug and $count>1);     
    }
    else{
      print "<font color = red> New logfile found: $logfile; ",
      "not catalogued because run apparently not finished </font> <br>\n";
    }

  }

  return \@dir_list_update;

}
#==========================================================
sub get_update_dirs_save{

  @logfile_list = @_;

  @dir_list_update = ();

  foreach $logfile (@logfile_list){
    
    # already catalogued?
    $dir_string = dirname($logfile);
    $report_key = QA_make_reports::get_report_key($dir_string); 

    defined $QA_object_hash{$report_key} and next;
    
    # check that run is complete
    
    open LOGFILE, $logfile or die "Cannot open logfile $logfile: $! \n";
    my @lines = <LOGFILE>;
    
    my $job_done = 1;
    
  ENDOFJOB:{
      while (my $line = pop @lines){
	$line =~ /This is the end of ROOT -- Goodbye/ and last ENDOFJOB;
	$line =~ /segmentation violation/ and last ENDOFJOB; 
	$line =~ /QAInfo:Run completed/ and last ENDOFJOB; 
	$line =~ /Broken Pipe/ and last ENDOFJOB; 
	$line =~ /bus error/ and last ENDOFJOB; 
      }
      $job_done = 0;
    }

    if($job_done){
      push @dir_list_update, dirname($logfile)."/";
    }
    else{
      print "<font color = red> New logfile found: $logfile; ",
      "not catalogued because run apparently not finished </font> <br>\n";
    }

  }

  return \@dir_list_update;

}
#===================================================================
sub hidden_field_string{
  
  @_ and my $arg = shift;
  
  #-----------------------------------------------------------------
  # bum, toggle -- added 'topdir', 
  $string = $query->hidden('selected_key_string').
    $query->hidden('dataset_array_previous').
      $query->hidden('selected_key_list').
	$query->hidden('expert_pw').
	  $query->hidden('display_env_var').
	    $query->hidden('enable_add_edit_comments').
	      $query->hidden('save_object_hash_scratch_file').
		$query->hidden('topdir');
  #------------------------------------------------------------  
  # store persistent hashes if this hasn't been done since script was
  # invoked or a new object has been created
  
  $save_filename = $Save_object_hash_scratch_file;
  
#  &print_traceback_hidden($save_filename);
  
 SAVEOBJECTS: {
    
    $arg eq 'DontWriteFile' and last SAVEOBJECTS;
    
    ( (-s $save_filename) and ($new_QA_object == 0) and 
      ($new_Button_object == 0) and ($new_Message == 0) ) and last SAVEOBJECTS;
    
#    print "Printing temp file $save_filename <br> \n";
    
    $Save_object_hash{QA_object_hash} = \%QA_object_hash;
    $Save_object_hash{Button_object_hash} = \%Button_object_hash;
    $Save_object_hash{QA_message_hash} = \%QA_message_hash;
    
    store(\%Save_object_hash, $save_filename ) or print "<h4> Cannot write $save_filename: $! </h4> \n";
  };

  #----------------------------------------------------------------
  return $string;
}
#===========================================================
sub print_refresh{
  print "<h3> <font color = blue> To refresh upper panel when done, reselect dataset </font> </h3> \n";
  return;
}
#===========================================================
sub print_button_object_hash{

  ($package, $filename, $line) = caller;

  print "-" x 80, "\n<br> print_button_object_hash called from $package::$filename, line $line <br> \n";

  foreach $key ( keys %Button_object_hash ){

    $object_ref = $Button_object_hash{$key};
    $object = $$object_ref;

    my $name = $object->ButtonName;
    my $method = $object->MethodName;
    my $value = $object->ButtonValue;
    my $report_key = $object->ReportKey;

    print "ref = $object_ref, name = $name, method = $method, value = $value, report_key = $report_key <br> \n";

  }

}
#===========================================================
sub print_timing{

  @_ and do{
    $time_start = shift;
    @_ and $time_last_call = shift;
    $sys_time_start = 0;
    $sys_time_last_call = 0;
    $wall_clock_start = time;
    $wall_clock_last_call = time;
    $count_print_timing = 0;
    return;
  };

  $count_print_timing++;

  ($package, $filename, $line) = caller;

  print "-" x 80, "\n<br> $count_print_timing: print_timing called from $package::$filename, line $line <br> \n";

  # get elapsed time
  $wall_clock = time;

  # get cpu time
  $now = (times)[0];
  $sys_now = (times)[1];

  printf "<font color=red>user cpu time since start = %.3f sec; user cpu time since last call= %.3f sec </font><br>\n",
  $now-$time_start,$now-$time_last_call;

  printf "<font color=blue>system cpu time since start = %.3f sec; system cpu time since last call= %.3f sec </font><br>\n",
  $sys_now-$sys_time_start,$sys_now-$sys_time_last_call;

  printf "<font color=green>elapsed time since start = %d sec; elapsed time since last call= %d sec </font><br>\n",
  $wall_clock-$wall_clock_start,$wall_clock-$wall_clock_last_call;

  $time_last_call = $now;
  $sys_time_last_call = $sys_now;
  $wall_clock_last_call = $wall_clock;
}
#=======================================================================
sub print_traceback{

  print "=" x 80, "\n<br> print_traceback called <br> \n";

  $i = 0;
  while ( ($package, $filename, $line, $sub, $hasargs, $wantarray) = caller($i++) ){
    print "from $package::$filename, line $line, subroutine $sub <br> \n";
  }

  print "=" x 80, "<br> \n";

}
#=======================================================================
sub print_traceback_hidden{

  my $save_filename = shift;

  print "=" x 80, "\n<br> print_traceback_hidden called <br> \n";

  $i = 0;
  while ( ($package, $filename, $line, $sub, $hasargs, $wantarray) = caller($i++) ){
    print "from $package::$filename, line $line, subroutine $sub <br> \n";
  }

  if ( -s $save_filename ){
    print "$save_filename exists <br> \n";
  }
  else{
    print "$save_filename doesnt exist <br> \n";
  }
  
  print "new QAobj: $new_QA_object; new ButtonObj:$new_Button_object; new Msg:$new_Message <br> \n";

  print "=" x 80, "<br> \n";

}
#===========================================================
sub move_old_reports{
  
  local $oldtime = 30*24*3600; # 30 days in seconds
  local $now     = timelocal( 0,0,0, (localtime)[3,4,5]); # epoch sec

  opendir REPORTDIR, $topdir_report or die "Cannot open report_dir $topdir_report \n";
  
  while ( defined ( $report = readdir REPORTDIR ) ){
    
    # move if older than 30 days
    
    next if $report =~ /^\./;
    next unless is_old_report($report); # bum - 10/03/00 

    $name = "$topdir_report/$report";
    
    # $next unless -M $name; 
    
    $name_move = "$topdir_report_old/$report";
    
    print "cp -rp $name $name_move <br> \n";
    system ("cp -rp $name $name_move");

    print "\\rm -rf $name <br> \n";
    system ("\\rm -rf $name");
    
  }
}
#============================================================
# bum 10/3/00 - called in move_old_reports above

sub is_old_report{
  my $report  = shift;
  my ($day, $month, $year, $report_age);

  # extract date from report_dir.  e.g. blah.250300 (day,month,year)
  ($day, $month, $year) = ($report =~ /(\d{2})(\d{2})(\d{2})$/);
  
  # error check
  if (not defined ($day, $month, $year)) {
    print "$report has a faulty date\n"; return;
  }

  # convert it to epoch seconds - note that this doesnt work after 2038...
  $year = 100 + $year if $year < 38; # timelocal conversion
  $month--; # ditto
  $report_age =  timelocal(0,0,0, $day, $month, $year);

  # return true if older than 30 days ($oldtime)  
  # see move_old_reports above for $now and $oldtime
  return 1 ? ($now - $report_age > $oldtime) : 0;
}
#=======================================================================
sub run_DSV{

  $report_key = shift;

  $report_key or do{
    print "Error in QA_utilities::run_DSV: valid report key not supplied <br> \n";
    return;
  };
  #-----------------------------------------------------------------------------

  $global_input_data_type = ".dst.xdf";
  $production_dir = $QA_object_hash{$report_key}->LogReport->OutputDirectory; 
  find( \&QA_cgi_utilities::get_file, $production_dir );

  if ( ! -e $global_filename ){
    print "Error in QA_utilities::run_DSV: file with type .dst.xdf not found in $production_dir <br> \n";
    return;
  };

  $xdf_file = $global_filename;

  #-----------------------------------------------------------------------------
  $DISPLAY = $query->param('display_env_var');

  if ($DISPLAY){
    print "Current DISPLAY environment variable is $DISPLAY <br> \n";
  }
  else{
    print "DISPLAY environment variable not set. Set it and try again. <br> \n";
    return;
  }

  #-----------------------------------------------------------------------------
  print "Starting dsv on file $xdf_file... <br> \n";
  #-----------------------------------------------------------------------------
  # create temporary csh script, use process pid ($$) to make unique name
  $script = $scratch."/"."run_dsv".$$."\.csh";
  
  # make sure it disappears at the end...
#  END { unlink($script) };
  
  open (SCRIPT, "> $script") or die "Cannot open $script: $!\n";

  # write to script
  print SCRIPT "#! /usr/local/bin/tcsh\n",
  "setenv GROUP_DIR /afs/rhic/rhstar/group\n",
  "setenv CERN /cern\n",
  "setenv CERN_ROOT /cern/pro\n",
  "setenv HOME /star/u2e/starqa\n",
  "setenv DISPLAY $DISPLAY\n",
  "source /afs/rhic/rhstar/group/.stardev\n",
  "setenv DSV_DIR /afs/rhic/star/tpc/dsv\n",
  "echo Doing: source /afs/rhic/star/tpc/dsv/set_path\n",
  "source /afs/rhic/star/tpc/dsv/set_path\n",
  "echo Doing: rpoints -xdfFile $xdf_file -event dst_0\n",
  "rpoints -xdfFile $xdf_file -event dst_0 &\n";

  close SCRIPT;
  
  chmod 0775, $script;
  #-----------------------------------------------------------------------------
  # 2nd layer - needed to get clean return of control to web page, not sure why this 
  # happens pmj 12/1/99
  $submit_script = $scratch."/"."submit_run_dsv".$$."\.csh";
  
  # make sure it disappears at the end...
#  END { unlink($submit_script) };
  
  open (SUBMIT, "> $submit_script") or die "Cannot open $submit_script: $!\n";

  # write to script
  print SUBMIT "#! /usr/local/bin/tcsh\n",
  "$script\n";

  close SUBMIT;
  
  chmod 0775, $submit_script;
  
  #-----------------------------------------------------------------------------
  
  # for debugging - doesn't properly create background process
  # pipe both STDOUT and STDERR (see PERL Cookbook 16.7)
  #open SCRIPTLOG, "$script 2>&1 |"  or die "can't fork: $!";
  #print "<pre> \n";
  #while ($line = <SCRIPTLOG>){
  #  print $line;
  #}
  #print "</pre> \n";
  #close SCRIPTLOG;

  #-----------------------------------------------------------------------------

  print "Running DVS on display $DISPLAY, input file $xdf_file... <br> \n";
  system("$submit_script &");
  print "DSV is running independently, control has returned to web page<br> \n";

}
#=======================================================================
sub comment_form{

  $arg = shift;
  #-----------------------------------------------------------------------------
  # pmj 23/12/99 form for creating new comment

  $author = $query->param('enable_add_edit_comments');

  #-----------------------------------------------------------------------------

  print $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 

  print "<h4> Author: </h4>",$query->textfield('comment_author', $author, 50, 80),"<br>\n";

  #---

  if ($arg eq 'global' ){
    $etime = time;
  }
  else{
    $etime = $QA_object_hash{$arg}->CreationEpochSec + 1;
  }
  $date = epochsec_to_message_time($etime);
  #---

  print "<h4> Date and Time: </h4>",
  "(Must be in format hh:mm dd/mm/yy to be parsed properly,",
  "otherwise message will not be in correct chronological order)<br>",
  $query->textfield('comment_date', $date, 50, 80),"<br>\n";


  print "<h4> Comment text: </h4>",$query->textarea(-name=>'comment_text', 
						     -value=>'', 
						     -rows=>10, 
						     -cols=>60,
						     -wrap=>virtual)
    ,"<br>\n";


  #---
  # is this global comment or comment specific to a run?

  if ( $arg eq 'global'){
    $button_ref = Button_object->new('NewComment', 'Submit');
  }
  else{
    $button_ref = Button_object->new('NewComment', 'Submit', $arg);
  }

  #---

  $hidden_string = &QA_utilities::hidden_field_string;

  print "<br>",$button_ref->SubmitString.$hidden_string;

  print $query->endform;

}
#=====================================================================
sub create_comment_object{

  $arg = shift;

  #----------------------------------------------------------------

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

  $author = $query->param('comment_author');

  if ($arg eq 'global' ){
    $date = $query->param('comment_date');
    $etime = message_time_to_epochsec($date);
  }
  else{
    $etime = $QA_object_hash{$arg}->CreationEpochSec + 1;
  }

  $text = $query->param('comment_text');

  #----------------------------------------------------------------

  $message_ref = QA_message->new($message_key,$author,$etime,$text);
  $QA_message_hash{$message_key} = $message_ref;

  #----------------------------------------------------------------

  $message_file = "$message_dir/$message_key";
  
  store($message_ref, $message_file ) or 
    print "<h4> Cannot write $filename: $! </h4> \n";
}
#=====================================================================
sub edit_comment{

  $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::edit_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  $author = $QA_message_hash{$message_key}->Author;

  $temp = $QA_message_hash{$message_key}->CreationEpochSec;
  $date = epochsec_to_message_time($temp);

  $text = $QA_message_hash{$message_key}->MessageString;

  #-----------------------------------------------------------------------------

  print "<h3> Modify comment fields and press Submit. Reselect dataset to display modifications. </h3>";

  print $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 

  print "<h4> Author: </h4>",$query->textfield('comment_author', $author, 50, 80),"<br>\n";


  print "<h4> Date and Time: </h4>",
  "(Must be in format hh:mm dd/mm/yy to be parsed properly,",
  "otherwise message will not be in correct chronological order)<br>",
  $query->textfield('comment_date', $date, 50, 80),"<br>\n";

  print "<h4> Comment text: </h4>",$query->textarea(-name=>'comment_text', 
						     -value=>$text, 
						     -rows=>10, 
						     -cols=>60,
						     -wrap=>virtual)
    ,"<br>\n";

  $button_ref = Button_object->new('ModifyComment', 'Submit', $message_key);
  $hidden_string = &QA_utilities::hidden_field_string;

  print "<br>",$button_ref->SubmitString.$hidden_string;

  print $query->endform;

}
#=====================================================================
sub modify_comment{

  $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::modify_global_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  $author = $query->param('comment_author');
  $date = $query->param('comment_date');
  $text = $query->param('comment_text');

  #----------------------------------------------------------------
  $QA_message_hash{$message_key}->Author($author);

  $etime = message_time_to_epochsec($date);
  $QA_message_hash{$message_key}->CreationEpochSec($etime);

  $QA_message_hash{$message_key}->MessageString($text);

  #----------------------------------------------------------------
  # save modification on disk also

  $message_ref = $QA_message_hash{$message_key};
  $message_file = "$message_dir/$message_key";
  
  store($message_ref, $message_file ) or 
    print "<h4> Cannot write $filename: $! </h4> \n";
}
#=====================================================================
sub delete_comment{

  $message_key = shift;

  exists $QA_message_hash{$message_key} or do{
    print "QA_utilities::modify_global_comment: QA_message_hash not defined for key $message_key <br> \n";
    return;
  };

  #-----------------------------------------------------------------------------

  print "Delete comment for message key $message_key...<br> \n";

  $old_file = "$message_dir/$message_key";
  $new_file = "$deleted_message_dir/$message_key";

  system("mv $old_file $new_file");

  delete( $QA_message_hash{$message_key} );

  print "...done. Reselect dataset to remove comment from current listing.<br>\n";

}
#==========================================================================
sub epochsec_to_message_time{

  $temp = shift;

  ($sec,$min,$hour,$mday,$mon,$year,$junk) = localtime($temp);

  $sec < 10 and $sec = "0".$sec;
  $min < 10 and $min = "0".$min;
  $hour < 10 and $hour = "0".$hour;
  $mday < 10 and $mday = "0".$mday;

  $mon += 1;
  $mon < 10 and $mon = "0".$mon;

  $year > 99 and $year -= 100;
  $year < 10 and $year = "0".$year;

  $string = "$hour:$min $mday/$mon/$year";

  return $string;
}
#==========================================================================
sub message_time_to_epochsec{

  $string = shift;

  $etime = -9999;

  $string =~ /(\d+):(\d+) (\d+)\/(\d+)\/(\d+)/ and do{

    $hour = $1;
    $min = $2;
    $sec = 0;

    $mday = $3;
    $mon = $4 - 1;
    $year = $5;

    $etime = timelocal($sec, $min, $hour, $mday, $mon, $year);

  };
  
  return $etime;
}
#===========================================================================
#   bum, toggle - set global directories - called in QA_main, QA_main_batch
#===========================================================================
# dont forget to modify the popup menu in QA_main if adding more dirs

sub set_directories{  
  my $topdir = shift;
  
  my %switch = ($topdir_dev      => \&dev,
		$topdir_new      => \&new,
		$topdir_cosmics  => \&cosmics,
                $topdir_debug    => \&debug);
  $switch{$topdir}->();
}
#===================================================================
# bum, toggle -called in set_directories above.  
# these actually do the resetting
sub dev{
  $topdir            = $topdir_dev;
  $topdir_report     = $topdir_report_dev;
  $topdir_report_WWW = $topdir_report_WWW_dev;
  $batch_dir         = $batch_dir_dev;
  $batch_dir_WWW     = $batch_dir_WWW_dev;
  $control_dir       = $control_dir_dev;
  $control_dir_WWW   = $control_dir_WWW_dev;
  $update_dir        = $update_dir_dev;
  $scratch           = $scratch_dev;
  $cron_dir          = $cron_dir_dev;
  $backup_dir        = $backup_dir_dev;
  $compare_dir       = $compare_dir_dev;
}
#-------------------------------------------------------------------
sub new{
  $topdir            = $topdir_new;
  $topdir_report     = $topdir_report_new;
  $topdir_report_WWW = $topdir_report_WWW_new;
  $batch_dir         = $batch_dir_new;
  $batch_dir_WWW     = $batch_dir_WWW_new;
  $control_dir       = $control_dir_new;
  $control_dir_WWW   = $control_dir_WWW_new;
  $update_dir        = $update_dir_new;
  $scratch           = $scratch_new;
  $cron_dir          = $cron_dir_new;
  $backup_dir        = $backup_dir_new;
  $compare_dir       = $compare_dir_new;
}
#-------------------------------------------------------------------
sub cosmics{
  $topdir            = $topdir_cosmics;
  $topdir_report     = $topdir_report_cosmics;
  $topdir_report_WWW = $topdir_report_WWW_cosmics;
  $batch_dir         = $batch_dir_cosmics;
  $batch_dir_WWW     = $batch_dir_WWW_cosmics;
  $control_dir       = $control_dir_cosmics;
  $control_dir_WWW   = $control_dir_WWW_cosmics;
  $update_dir        = $update_dir_cosmics;
  $scratch           = $scratch_cosmics;
  $cron_dir          = $cron_dir_cosmics;
  $backup_dir        = $backup_dir_cosmics;
  $compare_dir       = $compare_dir_cosmics;
}
#--------------------------------------------------------------------
sub test{
  $topdir            = $topdir_test;
  $topdir_report     = $topdir_report_test;
  $topdir_report_WWW = $topdir_report_WWW_test;
  $batch_dir         = $batch_dir_test;
  $batch_dir_WWW     = $batch_dir_WWW_test;
  $control_dir       = $control_dir_test;
  $control_dir_WWW   = $control_dir_WWW_test;
  $update_dir        = $update_dir_test;
  $scratch           = $scratch_test;
  $cron_dir          = $cron_dir_test;
  $backup_dir        = $backup_dir_test;
  $compare_dir       = $compare_dir_test;
}
#-------------------------------------------------------------------
sub debug{
  $topdir            = $topdir_debug;
  $topdir_report     = $topdir_report_debug;
  $topdir_report_WWW = $topdir_report_WWW_debug;
  $batch_dir         = $batch_dir_debug;
  $batch_dir_WWW     = $batch_dir_WWW_debug;
  $control_dir       = $control_dir_debug;
  $control_dir_WWW   = $control_dir_WWW_debug;
  $update_dir        = $update_dir_debug;
  $scratch           = $scratch_debug;
  $cron_dir          = $cron_dir_debug;
  $backup_dir        = $backup_dir_debug;
  $compare_dir       = $compare_dir_debug;
}


  
