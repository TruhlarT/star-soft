
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
sub bfcread_dstBranch{ 

  my $report_key = shift;
  my $report_filename = shift;
  #--------------------------------------------------------------

  my ($object, $end_of_first_event);
  my ( %run_scalar_hash, %event_scalar_hash );

  tie %run_scalar_hash, "Tie::IxHash"; 
  tie %event_scalar_hash, "Tie::IxHash"; 

  #--------------------------------------------------------------
  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename \n";
    return;
  };
  #--------------------------------------------------------------
  # default for BfcStatus
  # 0 means no error...

  $run_scalar_hash{BfcStatusError} = 0;

  while (<REPORT>){
    /QAInfo:/ or next; # skip lines that dont start with QAInfo
    
    if (/found object: (\w+)/){ # found an object?
      # only store first event 
      # BfcStatus has special status
      next if ($end_of_first_event or $1 eq 'BfcStatus') ;
      $object = $1;
      # num of rows found in next line
      $run_scalar_hash{$object} = undef;
      next;
    }
    
    if (/table with \#rows = (\d+)/){ # fill in the # of rows
      # only store first event
      next if ($end_of_first_event or $1 eq 'BfcStatus');
      # get # rows
      $run_scalar_hash{$object} = $1;
      next;
    }

    # BfcStatus has special status
    # error!
    if (/BfcStatus table --/){
      $run_scalar_hash{BfcStatusError} = 1;
      next;
    }

    # end of the first event
    if (/ev \# 1,.*?= (\d+).*?= (\d+)/){ # objects, tables in evt1
      $run_scalar_hash{'event_1_num_tables'} = $2;
      $run_scalar_hash{'event_1_num_objects'} = $1;
      $end_of_first_event = 1;
      next;
    }

    # --- now we're at the end ---

    if (/events read\s+= (\d+)/){ # num events read
      $run_scalar_hash{'num_events_read'} = $1;
      next;
    }

    if (/with tables\s+= (\d+)/){ # num events with tables
      $run_scalar_hash{'events_with_tables'} = $1;
      next;
    }

    if (/with objects\s+= (\d+)/){ # events with objects
      $run_scalar_hash{'events_with_objects'} = $1;
      next;
    }
    
    # avg tables per event
    if (/(?<!Bfc )tables per event\s+= ([\d\.]+)/){ 
      $run_scalar_hash{'avg_tables_per_event'} = $1;
      next;
    }

    # avg objects per event
    if (/(?<!Bfc )objects per event\s+= ([\d\.]+)/){ 
      $run_scalar_hash{'avg_objects_per_event'} = $1;
      next;
    }

    # avg Bfc tables per event
    if (/Bfc tables per event\s+= ([\d\.]+)/){ 
      $run_scalar_hash{'avg_bfc_tables_per_event'} = $1;
      next;
    }

    # avg Bfc objects per event
    if (/Bfc objects per event\s+= ([\d\.]+)/){ 
      $run_scalar_hash{'avg_bfc_objects_per_event'} = $1;
      next;
    }
    


  } # end of while


  close REPORT;

  #--------------------------------------------------------------
  return \%run_scalar_hash, \%event_scalar_hash;
  
} 
#================================================================
# bum macro 
# runs only one event

sub bfcread_runcoBranch{ 

  my $report_key = shift;
  my $report_filename = shift;
  #--------------------------------------------------------------

  my ($end_of_first_event);
  my ( %run_scalar_hash, %event_scalar_hash );

  tie %run_scalar_hash, "Tie::IxHash"; 
  tie %event_scalar_hash, "Tie::IxHash"; 

  #--------------------------------------------------------------
  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename \n";
    return;
  };
  #--------------------------------------------------------------
  while (<REPORT>){
    /QAInfo:/ or next; # skip lines that dont start with QAInfo
    
    
    if (/table with \#rows = (\w+),\s+(\d+)/){ # fill in the # of rows
      # only store first event
      next if $end_of_first_event;
      # get # rows
      $run_scalar_hash{$1} = $2;
      next;
    }

    if (/event \# 1,.*?= (\d+).*?tables.*?= (\d+)/){ # dirs, tables in evt1
      $run_scalar_hash{'directories'} = $1;
      $run_scalar_hash{'tables'} = $2;
      $end_of_first_event = 1;
      next;
    }

    # now we're at the end


    if (/events read\s+= (\d+)/){ # events read
      $run_scalar_hash{'num_events_read'} = $1;
      next;
    }


  } # end of while

  close REPORT;

  #--------------------------------------------------------------
  return \%run_scalar_hash, \%event_scalar_hash;
} 
#================================================================
sub QA_bfcread_dst_tables{

  my $report_key = shift;
  my $report_filename = shift;

  return bfcread_dstBranch($report_key, $report_filename);
}
#================================================================
sub bfcread_geantBranch{
  
  my $report_key = shift;
  my $report_filename = shift;
  #--------------------------------------------------------------

  return bfcread_dstBranch($report_key, $report_filename);
} 
#================================================================
sub bfcread_tagsBranch{
  
  my $report_key = shift;
  my $report_filename = shift;
  
  my (%run_scalar_hash, %event_scalar_hash );
  my ($key, $value, %temp_hash );

  tie %run_scalar_hash, "Tie::IxHash";
  tie %event_scalar_hash, "Tie::IxHash";

  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename \n";
    return;
  };
  #------------------------------------------------
  while ( <REPORT> ) {
    /QAInfo:/ or next; 

    # get the number of tags for each leaf
    if (/dimensions\(tags\) = (\d+)\s+(\d+)/){
      $run_scalar_hash{"leaf_$1"} = $2;
      next;
    }

    # total # events
    if (/total \# events = (\d+)/){
      $run_scalar_hash{'tot_num_events'} = $1;
      next;
    }

    # tot num of leaves
    if (/tot num leaves = (\d+)/){
      $run_scalar_hash{'tot_num_leaves'} = $1;
      next;
    }

    # tot num of tags
    if (/tot num tags = (\d+)/){
      $run_scalar_hash{'tot_num_tags'} = $1;
      next;
    }
  }

  #=------------------------------------------------

  close REPORT;

  return \%run_scalar_hash, \%event_scalar_hash;
} 
#================================================================
sub bfcread_eventBranch{

  my $report_key = shift;
  my $report_filename = shift;

  return doEvents($report_key, $report_filename);
} 
  
#================================================================

# pmj 2/2/00: QA_bfcread_dst_analysis is a new macro written by Kathy
# that is now run in autoQA instead of doEvents, so the doEvents
# routine which comes next should eventually go away. Leave it around for
# now. As of today (Feb 2, 00), these two routines are line-for-line
# idenitical.

sub QA_bfcread_dst_analysis{ 

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

  my $logfile = $QA_object_hash{$report_key}->LogReport->LogfileName;

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
  $run_scalar_hash{n_event} = $run_statistics_hash{track_nodes}->{n_event};

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

  my $logfile = $QA_object_hash{$report_key}->LogReport->LogfileName;

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
  $run_scalar_hash{n_event} = $run_statistics_hash{track_nodes}->{n_event};

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
