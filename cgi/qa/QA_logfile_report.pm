#! /usr/bin/perl -w

# parse production log file

# pmj 23/8/99
#=========================================================
package QA_logfile_report;
#=========================================================
use Cwd;

use File::stat;

use File::Copy;
use File::Find;
use File::Basename;

use Data::Dumper;

use QA_cgi_utilities;
use QA_globals;

#=========================================================
1.;
#=====================================================================
sub make_logfile_report{
    
  $production_dir = shift;
  $logfile_report = shift;

  #------------------------------------------------------------------
  -s $logfile_report and return;
  #------------------------------------------------------------------

  $global_logfile = "";
  find( \&QA_cgi_utilities::get_logfile, $production_dir );
  
  if ( -e $global_logfile ){
    
    print "<h3> Making logfile report $logfile_report... </h3> \n";
    parse_logfile($global_logfile, $logfile_report);

  }
  else{
    print "<h4> Directory = $production_dir; Cannot find log file $global_logfile </h4> \n";
  }
}
#=========================================================

sub parse_logfile {

  $logfile_name = shift(@_);
  $logfile_report = shift(@_);

  #----------------------------------------------------------
  # dump contents of log file to array for parsing  

  open (LOGFILE, $logfile_name) or die "cannot open $logfile_name: $!";
  @logfile = <LOGFILE>;
  close LOGFILE;

  #---------------------------------------------------------
  # open report file

  open REPORT, ">$logfile_report" or die "Cannot open file $logfile_report: $!\n"; 

  #----------------------------------------------------------
  
  # parse beginning of file
  
  $record_run_options = 0;

  undef $star_level_log;
  undef $root_level_log;
  undef $starlib_version;
  undef $run_options;
  undef $requested_chain;
  undef $input_fn;
  undef $n_event;
  undef $first_event_requested;
  undef $last_event_requested;
  undef $output_fn;
  undef $run_start_time_and_date;
  undef $machine;
  undef $output_directory;
  undef $tags;
  undef $event_timing;
 
  foreach $line (@logfile) {
    
    next unless $line =~ /^QAInfo:/;
    
    # get STAR and ROOT levels
    $line =~ /STAR_LEVEL\W+(\w+) and ROOT_LEVEL\W+([0-9\.]+)/ and do{
      $star_level_log = $1;
      $root_level_log = $2;
      next;
    };
    
    # get STARLIB version
    $line =~ /You are in (\w+)/ and do{
      $starlib_version = $1;
      next;
    };
    
    # start recording of run options
    $line =~ /Requested chain is\W+([\w ]+)/ and do{
      $record_run_options = 1;
      $run_options = "\n";
      $requested_chain = $1;
      next;
    };
    
    # turn off recording of run options?
    $record_run_options and $line !~ /=======/ and $record_run_options = 0;
    
    $record_run_options and do {
      $line =~ s/QAInfo://;
      $run_options .= $line;
      next;
    };
    
    # get input file name
    $line =~ /Input file name = (\S+)/ and do {
      $input_fn = $1;
      next;
    };

    #valid from 99h on pmj 14/9/99
    $line =~ /QAInfo:Process\s+\[First=\s+(\d+)\/Last=\s+(\d+)\/Total=\s+(\d+)/ and do{
      $first_event_requested = $1;
      $last_event_requested = $2;
      $n_event = $3;
      next;
    };

    # valid up to 99g  pmj 14/9/99
    # get number of events to process
    $line =~ /Events to process = (\d+)/ and do {
      $n_event = $1;
      next;
    };

    # for old log files (keep this in for now pmj 17/8/99)
    
    # get input file name and number of events to process
    $line =~ /Input file name = (\S+).*Events to process = (\d+)/ and do {
      $input_fn = $1;
      $n_event = $2;
      next;
    };

    
    # get output root filename
    $line =~ /Output root file name (\S+)/ and do {
      $output_fn = $1;
      next;
    };
    
    # run start time
    $line =~ /Run is started at Date\/Time ([0-9\/]+)/ and do {
      $run_start_time_and_date = $1;
      next;
    };
    
    # machine and directory
    $line =~ /Run on ([\w\.]+) in (\S+)/ and do {
      $machine = $1;
      $output_directory = $2;
      next;
    };
    
    # CVS tags
    $line =~ /with Tag (.*)/ and do{
      $tags = "\n".$1;
      next;
    };
    $line =~ /built.*from Tag (.*)/ and do{
      $tags .= "\n".$1;
      next;
    };
    
    # event timing
    $line =~ /Done with (Event.*)/ and do{
      $event_timing .= "\n".$1;
      next;
    };
    
  }
    
  #--------------------------------------------------------------------------
  # get lines at end of file, starting with last occurence of "EndMakerShell"
  
  undef @end_lines;

  while ( $line  = pop @logfile ){

    push @end_lines, $line;
    $line =~ /Done with Event/  and last;
    
  };
  
  @end_lines = reverse @end_lines;
  
  #--------------------------------------------------------------------------
  # parse end of file
  
  undef $timing_string;
  undef $last_event;
  undef $return_code_last_event;
  undef $run_completion_time_and_date;

  $segmentation_violation = 0;
  $run_completed_ok = 0;
  $divider = "-" x 80;
  $divider .= "\n";
 
  foreach $line (@end_lines) {

    # look for segmentation violation
    $line =~ /segmentation violation/ and do {
      $segmentation_violation = 1;
      next ;
    };

    next unless $line =~ /^QAInfo:/;

    # this one valid from 99h pmj 14/9/99
    # get last event number
    $line =~ /QAInfo: Done with Event\s+\[no\.\s+(\d+)\/run\s+(\d+)\/evt\.\s+(\d+)\/sta\s+(\d+)/ and do{
      $last_event = $1;
      $return_code_last_event = $4;
      next;
    };

    # this one valid up to 99g pmj 14/9/99
    # get last event number
    $line =~ /Done with Event no\. ([0-9]+)\W+([0-9]+)/ and do {
      $last_event = $1;
      $return_code_last_event = $2;
      next;
    };
    
    # get timing strings
    $line !~ /Done with Event/ and $line =~ /Real Time =/ and do{
      $line =~ s/QAInfo://;
      ! defined($timing_string) and $timing_string = "\n";
      if ( $line =~ /bfc/ ){
	$timing_string .= $divider.$line.$divider;
      }
      else{
	$timing_string .= $line;
      }
      next;
    };
    
    # run completed o.k.?
    $line =~ /Run completed/ and do{
      $run_completed_ok = 1;
      next;
    };
    
    # run completion date/time
    $line =~ /Run is finished at Date\/Time ([0-9\/]+)/ and do{
      $run_completion_time_and_date = $1;
      next;
    };
 
  }

  #--------------------------------------------------------------------------
  # now check if expected files have been created

  $this_dir = dirname($logfile_name);

  $missing_files = "";
  
  undef $global_root_dst_file;
  find ( \&QA_cgi_utilities::get_root_dst_file, $this_dir);
  defined $global_root_dst_file or $missing_files .= " .dst.root"; 

  undef $global_root_hist_file;
  find ( \&QA_cgi_utilities::get_root_hist_file, $this_dir);
  defined $global_root_hist_file or $missing_files .= " .hist.root"; 

  # also flag .hist.root missing if it is too small
  defined $global_root_hist_file and do{
    $size = stat($global_root_hist_file)->size;
    $size < 10000 and $missing_files .= " .hist.root";
  };

  undef $global_root_event_file;
  find ( \&QA_cgi_utilities::get_root_event_file, $this_dir);
  defined $global_root_event_file or $missing_files .= " .event.root"; 

  undef $global_dst_xdf_file;
  find ( \&QA_cgi_utilities::get_xdf_file, $this_dir);
  defined $global_dst_xdf_file or $missing_files .= " .dst.xdf"; 

  if ($missing_files  eq ""){
    undef $missing_files;
  }

  
  #------------------------------------------------------
  # fix up the data directory a bit

  $output_directory =~ s/\/direct//;
  $output_directory =~ s/\+/\//;

  #--------------------------------------------------------------------------

  print REPORT "*" x 80, "\n";
  print REPORT "Report on logfile $logfile_name \n";
  print REPORT "*" x 80, "\n";
  
  # output header info
  
  write_scalar(\*REPORT, "STAR level", $star_level_log);
  write_scalar(\*REPORT, "ROOT level", $root_level_log);
  write_scalar(\*REPORT, "STARLIB version", $starlib_version);
  write_scalar(\*REPORT, "chain", $requested_chain);
  write_scalar(\*REPORT, "run options", $run_options);
  write_scalar(\*REPORT, "input filename", $input_fn);
  write_scalar(\*REPORT, "requested number of events", $n_event);
  write_scalar(\*REPORT, "first event requested", $first_event_requested);
  write_scalar(\*REPORT, "last event requested", $last_event_requested);
  write_scalar(\*REPORT, "output filename", $output_fn);
  write_scalar(\*REPORT, "start time and date", $run_start_time_and_date);
  write_scalar(\*REPORT, "machine", $machine);
  write_scalar(\*REPORT, "output dir", $output_directory);
  write_scalar(\*REPORT, "cvs tags", $tags);
  write_scalar(\*REPORT, "event timing", $event_timing);
  write_scalar(\*REPORT, "segmentation violation?", $segmentation_violation);
  write_scalar(\*REPORT, "last event", $last_event);
  write_scalar(\*REPORT, "ret code last event", $return_code_last_event);
  write_scalar(\*REPORT, "timing string", $timing_string);
  write_scalar(\*REPORT, "run completed ok?", $run_completed_ok);
  write_scalar(\*REPORT, "run completion time and date", $run_completion_time_and_date);
  
  defined $missing_files and write_scalar(\*REPORT, "missing files", $missing_files);

  #------------------------------------------------------------------------------

  close REPORT;
  
}
#=====================================================================================

sub write_scalar{

  my $filehandle = shift (@_);
  my $text = shift (@_);
  my $string = shift (@_);

  $not_found_string = " *** Not found *** ";

  ! defined($string) and $string = $not_found_string;
  print REPORT "$text: $string\n";

  return;

}
#=====================================================================================
sub get_logfile_report{

  my $logfile_report = shift (@_);

  # dump contents of logfile report into hash

  open LOGFILE, $logfile_report or die "Cannot open log file $logfile_report: $!\n";

  %scalars_logfile = ();

  my $record_run_options = 0;
  my $record_tags = 0;
  my $record_event_timing = 0;
  my $record_final_timing = 0;

  while(<LOGFILE>){

    #---
    
    /Report on logfile (\S+)/ and do {
      $scalars_logfile{"input_logfile"} = $1;
      next;
    };

    #---
    
    /STAR level: (\w+)/ and do {
      $scalars_logfile{"star_level"} = $1;
      next;
    };
    
    #---
    
    /ROOT level: (\S+)/ and do {
      $scalars_logfile{"root_level"} = $1;
      next;
    };
    
    #---
    
    /STARLIB version: (\w+)/ and do {
      $scalars_logfile{"starlib_version"} = $1;
      next;
    };
    
    #---
    
    /chain: ([\w ]+)/ and do {
      $scalars_logfile{"chain"} = $1;
      next;
    };
    
    #---
    
    /run options:/ and do {
      $record_run_options = 1;
      $scalars_logfile{"run_options"} = "\n";
      next;
    };

    # done with run options?
    $record_run_options and $_ !~ /======/ and $record_run_options = 0;
    
    $record_run_options and do {
      $scalars_logfile{"run_options"} .= $_;
      next;
    };

    #---
    
    /input filename: (\S+)/ and do {
      $scalars_logfile{"input_filename"} = $1;
      next;
    };
    
    #---
    
    /requested number of events: (\d+)/ and do {
      $scalars_logfile{"nevent_requested"} = $1;
      next;
    };
    
    #---
    
    /first event requested: (\d+)/ and do {
      $scalars_logfile{"first_event_requested"} = $1;
      next;
    };
    
    #---
    
    /last event requested: (\d+)/ and do {
      $scalars_logfile{"last_event_requested"} = $1;
      next;
    };
    
    #---
    
    /output filename: (\S+)/ and do {
      $scalars_logfile{"output_filename"} = $1;
      next;
    };
    
    #---
    
    /start time and date: (\S+)/ and do {
      $scalars_logfile{"start_time_and_date"} = $1;
      next;
    };
    
    #---
    
    /machine: (\S+)/ and do {
      $scalars_logfile{"machine_name"} = $1;
      next;
    };
    
    #---
    
    /output dir: (\S+)/ and do {
      $scalars_logfile{"output_directory"} = $1;
      next;
    };

    #---
    
    /segmentation violation\?: (\d+)/ and do {
      $scalars_logfile{"segmentation_violation"} = $1;
      next;
    };
    
    #---
    
    /^last event: (\d+)/ and do {
      $scalars_logfile{"nevent_last"} = $1;
      next;
    };
    
    #---
    
    /ret code last event: (\d+)/ and do {
      $scalars_logfile{"return_code_last_event"} = $1;
      next;
    };
    
    #---
   
    /run completed ok\?: (\d+)/ and do {
      $scalars_logfile{"run_completed"} = $1;
      next;
    };
    
    #---
    
    /run completion time and date: (\S+)/ and do {
      $scalars_logfile{"finish_time_and_date"} = $1;
      $global_creation_time = $1;
      next;
    };
    
    #---
    
    /cvs tags:/ and do {
      $record_tags = 1;
      $scalars_logfile{"cvs_tags"} = "\n";
      next;
    };

    # done with cvs tags?
    $record_tags and do{
      if($_ !~ /Name/){$record_tags = 0;}
    };
    
    $record_tags and do {
      $scalars_logfile{"cvs_tags"} .= $_;
      next;
    };
    
    #---
    
    /event timing:/ and do {
      $record_event_timing = 1;
      $scalars_logfile{"event_timing"} = "\n";
      next;
    };

    # done with event timing?
    $record_event_timing and $_ !~ /Event no\./ and $record_event_timing = 0;
    
    $record_event_timing and do {
      $scalars_logfile{"event_timing"} .= $_;
      next;
    };
    
    #---
    
    /timing string:/ and do {
      $record_final_timing = 1;
      $scalars_logfile{"final_timing"} = "\n";
      next;
    };

    # done with timing string?
    $record_final_timing and $_ !~ /Real Time/ and $_ !~ /----------/ and do {
      $record_final_timing = 0;
      next;
    };

    $record_final_timing and do {
      $scalars_logfile{"final_timing"} .= $_;
      next;
    };

  }

  close LOGFILE;

  return %scalars_logfile;

}
#=========================================================
sub get_logfile_summary_string {
  
  my $logfile_report = shift @_;
  my $return_string;

  undef $star_level_defined;
  my $nevent_requested = 0;
  my $nevent_last = 0;
  my $first_event_requested = 0;
  my $last_event_requested = 0;
  my $seg_violation = 0;
  my $run_completed = 0;
  undef $missing_files;

  open LOGREPORT, $logfile_report or die "Cannot open logreport file $logfile_report: $!\n";
  
  while($line = <LOGREPORT>){

    $line =~ /STAR level: (\w+)/ and do{
      $star_level_defined = $1;
      next;
    };
    
    $line =~ /requested number of events: (\d+)/ and do{
      $nevent_requested = $1;
      next;
    };

    $line =~ /^last event: (\d+)/ and do{
      $nevent_last = $1;
      next;
    };

    #---
    
    $line =~ /first event requested: (\d+)/ and do {
      $first_event_requested = $1;
      next;
    };
    
    #---
    
    $line =~ /last event requested: (\d+)/ and do {
      $last_event_requested = $1;
      next;
    };
    
    #---

    $line =~ /segmentation violation\?: (\d+)/ and do{
      $seg_violation = $1;
      next;
    };

    $line =~ /run completed ok\?: (\d+)/ and do{
      $run_completed = $1;
      next;
    };

    $line =~ /missing files: (.*)/ and do{
      $missing_files = $1;
      next;
    };

  }

  close LOGREPORT;

  $return_string = "";

  if ( defined $star_level_defined ) {

    if ($run_completed) {
      $return_string .= "run completed;";
    }
    else {
      $return_string .= " run not completed;";
      $seg_violation and $return_string .= " segmentation fault;";
    }

    $return_string .= " $nevent_last";
    $nevent_requested and $return_string .= "/$nevent_requested";
    $return_string .= " events done;";

    if ( $first_event_requested and $last_event_requested){
       $return_string .= "<br>(events requested: $first_event_requested-$last_event_requested)";
     }
    
  }
  else {
    $return_string .= "Log file could not be parsed";
  }

  defined $missing_files and $return_string .="<br>missing files: $missing_files";
  
  return $return_string;
}
#=========================================================
sub display_logfile_report {
  
  my $report_key = shift @_;

  print "<h2> Logfile report for $report_key </h2> \n";

  #--------------------------------------------------------------------
  # put logfile report into hash scalars_logfile

  %scalars_logfile = %{$QA_object_hash{$report_key}->LogfileReportData()};

  #--------------------------------------------------------------------

  $divider = "*" x 100;
  $divider .= "\n";

  print "$divider <br> Report for logfile $scalars_logfile{'input_logfile'} <br> $divider";

  print "<pre>";

  print "STAR Level = $scalars_logfile{'star_level'}" 
    ,"; ROOT Level = $scalars_logfile{'root_level'}"
      ,"; STARLIB version = $scalars_logfile{'starlib_version'}"
	,"\n";
  
  print "Chain = $scalars_logfile{'chain'} \n";

  print "Input filename = $scalars_logfile{'input_filename'} \n";
  print "Output directory = $scalars_logfile{'output_directory'} \n";
  print "Output filename = $scalars_logfile{'output_filename'} \n";

  print "Start date/time = $scalars_logfile{'start_time_and_date'} \n";
  print "Nevents requested = $scalars_logfile{'nevent_requested'} \n";
  print "First event requested = $scalars_logfile{'first_event_requested'} \n";
  print "Last event requested = $scalars_logfile{'last_event_requested'} \n";
  print "Nevents completed = $scalars_logfile{'nevent_last'} \n";
  print "Return code for last event = $scalars_logfile{'return_code_last_event'} \n";
  print "Finish date/time = $scalars_logfile{'finish_time_and_date'} \n";
  print "Machine name = $scalars_logfile{'machine_name'} \n";

  $temp = ( $scalars_logfile{"run_completed"} == 1 ) ? "Run completed O.K." : "Run not completed" ;
  print "$temp \n";

  defined ($scalars_logfile{"segmentation_violation"}) and $scalars_logfile{"segmentation_violation"} and
      print "Segmentation violation found \n";

  print "$divider Run options = $scalars_logfile{'run_options'} \n";
  print "$divider CVS tags = $scalars_logfile{'cvs_tags'} \n";

  print "$divider";
  $scalars_logfile{"run_completed"} == 1 or 
    print "Event timing report is a mess if run didn't complete o.k. \n";
  print "Event timing = $scalars_logfile{'event_timing'} \n";

  $scalars_logfile{"run_completed"} == 1  and  print "$divider Final timing = $scalars_logfile{'final_timing'} \n";

  print "$divider";
  print "</pre> \n";

}
