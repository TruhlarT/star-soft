#! /usr/bin/perl

# general utilities used by main routines

# pmj 31/8/99
#=========================================================
package QA_utilities;
#=========================================================

use CGI qw/:standard :html3 -no_debug/;
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
      $file =~ /\.qa_hash$/ or next;
      my $full_file = "$scratch/$file";
      -M $full_file > 0.5 and do{
	unlink($full_file);
      };
    }
    close (SCRATCH);

    #-----------------------------------------------------------

    my $temp = $query->param('qa_object_hash_scratch_file');

    if (-e $temp) {
      $QA_object_hash_scratch_file = $temp;
      my $ref = retrieve($QA_object_hash_scratch_file);
      %QA_object_hash = %$ref;
    }
    else {
      %QA_object_hash = ();

      # quick upload for testing
#      print "Using quick-upload test.qa_hash <br> \n";
#      $QA_object_hash_scratch_file = "$scratch/test.qa_hash";    
#      my $ref = retrieve($QA_object_hash_scratch_file);
#      %QA_object_hash = %$ref;
      #---- 

      # generate unique file ID
      srand;
      my $id_string = int(rand(1000000)); 
      $QA_object_hash_scratch_file ="$scratch/temp_$id_string.qa_hash";
      $query->param('qa_object_hash_scratch_file', $QA_object_hash_scratch_file);
      &hidden_field_string;
      
    }
  }
  else {
    %QA_object_hash = ();
  }
  #-----------------------------------------------------------
  # get report catalogue

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
    
    foreach $dir ( @topdir_data){
      find( \&get_logfiles, $dir );
    }
    
    $dir_list_update_ref = get_update_dirs(@logfile_list);
    @dir_list_update = @$dir_list_update_ref;

    foreach $dir_string ( @dir_list_update ){
      
      print "In QA_main: new directory $dir_string, report key $report_key <br> \n";

      $new_qa = QA_object->new($dir_string, $arg);
      $report_key = $new_qa->ReportKey();
      $QA_object_hash{$report_key} = $new_qa;
      
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

return @key_list_sorted

}
#=================================================================
sub sort_time{

  my $report_key = shift;

  return $QA_object_hash{$report_key}->CreationEpochSec;

}
#=================================================================
sub submit_batchjob {

  $action = shift;
  @_ and @key_list = @_;

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
  "setenv HOME /star/u2/jacobs \n",
  "setenv SILENT 1 \n",
  "source /afs/rhic/rhstar/group/.stardev \n";

  print BATCHSCRIPT 
    "echo \"Starting perl script...<br>\" >& $output_filename \n",
    "/opt/star/bin/perl -I$now $program $report_filename >>& $output_filename \n",
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

  $filename =~ /\.log/ and do {
    push @logfile_list, $filename;
  };
  return;
}
#==========================================================
sub get_update_dirs{

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

  $string = $query->hidden('select_dataset').
    $query->hidden('report_key_selected').
      $query->hidden('button_action').
	$query->hidden('dataset_array_previous').
	  $query->hidden('selected_key_list').
	    $query->hidden('expert_pw').
	      $query->hidden('qa_object_hash_scratch_file');

  #------------------------------------------------------------  
  # store hash
  %QA_object_hash and do{
    $filename = $QA_object_hash_scratch_file;
    store(\%QA_object_hash, $filename ) or print "<h4> Cannot write $filename: $! </h4> \n";
  };
  #----------------------------------------------------------------
  return $string;
}
