#! /usr/bin/perl -w

# displays analysis report

# pmj 1/7/99
#=========================================================
package QA_display_reports;
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
#=========================================================
sub get_logfile_summary_string {
  
  my $logfile_report = shift @_;
  my $return_string;

  undef $star_level_defined;
  my $nevent_requested = 0;
  my $nevent_last = 0;
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
      $return_string .= "run not completed;";
      $seg_violation and $return_string .= "segmentation fault;";
    }

    $return_string .= "$nevent_last/$nevent_requested events done;";
    
  }
  else {
    $return_string .= "Log file could not be parsed";
  }

  defined $missing_files and $return_string .="<br>missing files: $missing_files";
  
  return $return_string;
}
#=========================================================

sub display_logfile_report {
  
  my $logfile_report = shift @_;
  #--------------------------------------------------------------------
  # dumps logfile report into hash scalars_logfile
  get_logfile_report($logfile_report);

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
