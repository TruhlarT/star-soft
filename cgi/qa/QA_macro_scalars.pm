#! /usr/bin/perl -w

# contains a subroutine for each QA macro
# input is report filename, output is hash whose keys are scalar names
# and whose values are the scalar values extracted from the report

#=========================================================
package QA_macro_scalars;
#=========================================================

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

# for ensuring that hash elements delivered in insertion order (See Perl Cookbook 5.6)
use Tie::IxHash;
use Data::Dumper;

use QA_globals;
use QA_cgi_utilities;

#=========================================================
1.;
#=========================================================
sub QA_bfcread_dst_tables{ 

  my $report_key = shift;
  my $report_filename = shift;
  #--------------------------------------------------------------

  %run_scalar_hash = ();
  %event_scalar_hash = ();
  tie %run_scalar_hash, "Tie::IxHash"; 
  tie %event_scalar_hash, "Tie::IxHash"; 

  #--------------------------------------------------------------
  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename \n";
    return;
  };
  #--------------------------------------------------------------
  while (<REPORT>){
    /QAInfo: ([\w_]+)\s+(\d+)/ and $run_scalar_hash{$1} = $2;
  }

  close REPORT;

  #--------------------------------------------------------------
  return \%run_scalar_hash, \%event_scalar_hash;
} 
#=========================================================
sub doEvents{ 

  my $report_key = shift;
  my $report_filename = shift;

  #--------------------------------------------------------------
  tie %run_scalar_hash, "Tie::IxHash"; 
  tie %event_scalar_hash, "Tie::IxHash"; 

  %run_scalar_hash = ();
  %event_scalar_hash = ();

  tie %run_statistics_hash, "Tie::IxHash"; 
  %run_statistics_hash = ();

  #--------------------------------------------------------------
  # get logfile

  my $logfile = $QA_object_hash{$report_key}->LogfileName;

  #--------------------------------------------------------------
  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename:$! \n";
    return;
  };
  #--------------------------------------------------------------
  open LOGFILE, $logfile or do{
    print "Cannot open logfile $logfile:$! \n";
    return;
  };
  #--------------------------------------------------------------
  $event = 0;
  $icount_event = 0;

  $report_previous_line = -9999999;

 REPORT: {

    while ( $report_line = <REPORT> ){

      #---	
      # protect against successive duplicate lines in report file
      
      while ($report_line eq $report_previous_line){
	$report_line = <REPORT>;
	defined ($report_line) or last REPORT;
      }
      $report_previous_line = $report_line;
      #---

      
    REPORTLINE: {
	
	# look for new event in report file
	$report_line =~ /==\s+Event\s+(\d+)\s+(\S+)/ and do{
	  $2 =~ /finish/ and last REPORT;
	  $event = $1;
	  $icount_event++;
	  next;
	};
	
	# if this is start of event, skip to next event in logfile
	$report_line =~ /Reading Event/ and do{
	  while ( $logfile_line = <LOGFILE> ){
	    #$logfile_line =~ /QAInfo/ or next;
	    $logfile_previous_line = $logfile_line;
	    $logfile_line =~ /Reading Event:\s+\d+\s+Type:/ and last REPORTLINE;
	  }
	};
	
	# does line contain scalars?

	$report_line =~ /\# (.*):\s+(\d+)/ or next REPORTLINE;

	#-- accumulate run-wise quantities
	
	my $name = $1;
	my $value = $2;
	
	# change multiple blanks to single underscore
	$name =~ s/ +/_/g;
	
	$icount_event == 1 and do{
	  $run_statistics_hash{$name}->{n_event} = 0;
	  $run_statistics_hash{$name}->{min} = 999999.;
	  $run_statistics_hash{$name}->{max} = -999999.;
	  $run_statistics_hash{$name}->{sum} = 0.;
	  $run_statistics_hash{$name}->{sum_sqr} = 0;
	  $run_statistics_hash{$name}->{mean} = -999999.;
	  $run_statistics_hash{$name}->{rms} = -999999.;
	};
	
	$run_statistics_hash{$name}->{n_event}++;
	$run_statistics_hash{$name}->{sum} += $value;
	$run_statistics_hash{$name}->{sum_sqr} += $value*$value;
	
	my $min = $run_statistics_hash{$name}->{min};
	$run_statistics_hash{$name}->{min} = ($value < $min) ? $value : $min;
	
	my $max = $run_statistics_hash{$name}->{max};
	$run_statistics_hash{$name}->{max} = ($value > $max) ? $value : $max;
	
	#---
	# Eventwise comparison of strings
	
	# strip off leading junk
	$report_line =~ s/.*QAInfo: //;

	#---	
	# protect against successive duplicate lines in logfile

	while ($logfile_line = <LOGFILE>){
	  last if $logfile_line ne $logfile_previous_line;
	}
	$logfile_previous_line = $logfile_line;
	#---

	$logfile_line =~ s/.*Info: //;
	
	# are these the same? 
	$string = $report_line;

	# special processing for primary vertex
	$string =~ /primary vertex/ and $string =~ s/:\s+\(.*\)//;	

	# change pound sign to N
	$string =~ s/\#/_N/g;
	# change colon to eq
	$string =~ s/:/_eq/;
	# change multiple blanks to single underscore
	$string =~ s/ +/_/g;
	# get rid of all other non-word characters
	$string =~ s/\W//g;

	$string ="Event$event".$string;

	# just to be safe, strip leading and trailing whitespace
	$report_line =~ s/^\s+//;
	$report_line =~ s/\s+$//;
	$logfile_line =~ s/^\s+//;
	$logfile_line =~ s/\s+$//;

	$event_scalar_hash{$string} = ($report_line eq $logfile_line) ? "o.k." : "not_matched";
	
      } # end of REPORTLINE
    }
  } # end of report
  
  #--------------------------------------------------------------
  # calculate run-wise quantities

  foreach $name ( keys %run_statistics_hash){

    my $n_event = $run_statistics_hash{$name}->{n_event};
    $n_event and do{
      $mean = $run_statistics_hash{$name}->{sum} / $n_event;
      $mean_sq = $run_statistics_hash{$name}->{sum_sqr} / $n_event;
      
      $run_statistics_hash{$name}->{mean} = $mean;

      $arg = $mean_sq - ($mean*$mean);
      $arg >= 0 and $run_statistics_hash{$name}->{rms} = sqrt( $arg );
    };
  }

  # now copy to run_scalar_hash, which is flat structure (without sub-hashes)
  $run_scalar_hash{n_event} = $run_statistics_hash{tracks}->{n_event};

  foreach $name ( keys %run_statistics_hash){
    foreach $field ( 'mean', 'rms', 'min', 'max' ){
      my $value = (int ( 100 * $run_statistics_hash{$name}->{$field})) / 100;
      my $string = $name."_".$field;
      defined($value) and $run_scalar_hash{$string} = $value;
    }
  }

  #--------------------------------------------------------------
  close REPORT;
  close LOGFILE;
  #--------------------------------------------------------------
  return \%run_scalar_hash, \%event_scalar_hash;
} 
