
#! /opt/star/bin/perl -w

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

use strict;

#=========================================================
1.;
#=========================================================
sub bfcread_dstBranch{ 

  my $report_key = shift;
  my $report_filename = shift;
  #--------------------------------------------------------------

  my ($object, $end_of_first_event, %bfc_hash);
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

  $run_scalar_hash{BfcStatus} = 0;

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
    if (/BfcStatus table -- row \d+, Maker: (\w+) has istat = (\d+)/){
      #$run_scalar_hash{BfcStatus} = 1;
      next if defined $bfc_hash{"BfcStatus_$1"};
      $bfc_hash{"BfcStatus_$1"} = $2;
      $run_scalar_hash{BfcStatus}++; # just count the number of times 
                                     # a BfcStatus error is called per event
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

    # events with dataset
    if (/events with \w+ dataset = (\d+)/){
      $run_scalar_hash{'events_with_dataset'} = $1;
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
      $run_scalar_hash{'avg_Bfc_tables_per_event'} = $1;
      next;
    }

    # avg Bfc objects per event
    if (/Bfc objects per event\s+= ([\d\.]+)/){ 
      $run_scalar_hash{'avg_Bfc_objects_per_event'} = $1;
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
  #-------------------------------------
  while ( <REPORT> ) {
    /QAInfo:/ or next; 

    # for all leaves, avg over all tags, all evts
    
    if (/avg leaf \#\d+,\s+(\w+)\s+=\s+([\d\.]+)/){
      $run_scalar_hash{$1} = $2;
      next;
    }

    # list the branch name, num of leaves, num of tags
    
    if (/branch\(table\)\s+(\w+)\s+has\s+(\d+)\s+leaves,\s+(\d+)\s+tags/){
      $run_scalar_hash{"$1_leaves"} = $2;
      $run_scalar_hash{"$1_tags"}   = $3;
      next;
    }

    #--- we're at the end ---

    # total num of events/branches/leaves/tags
    
    if (/tot num (\w+) = (\d+)/){
      $run_scalar_hash{"tot_num_$1"} = $2;
      next;
    }
  }
   
  #=------------------------------------

  close REPORT;

  return \%run_scalar_hash, \%event_scalar_hash;
} 
#================================================================
sub bfcread_eventBranch{

  my $report_key = shift;
  my $report_filename = shift;


# pmj 26/8/00 added multiplicity class label as third argument
# currently can be "mc" for Monte Carlo, "lm", "mm", "hm" for real data

  my $mult_class_label = shift;
  my $mult_limit_low = shift;
  my $mult_limit_high = shift;

  return QA_bfcread_dst_analysis($report_key, $report_filename,
				 $mult_class_label,$mult_limit_low, $mult_limit_high);
} 
  
#================================================================

# pmj 2/2/00: QA_bfcread_dst_analysis is a new macro written by Kathy
# that is now run in autoQA instead of doEvents, so the doEvents
# routine which comes next should eventually go away. Leave it around for
# now. As of today (Feb 2, 00), these two routines are line-for-line
# idenitical.

# bum:read_eventBranch wraps around this subrouting
# for some unknown reason (even though i did this)
# eliminate all reference to the log

sub QA_bfcread_dst_analysis{ 

  my $report_key = shift;
  my $report_filename = shift;

# pmj 26/8/00 added multiplicity class label as third argument
# currently can be "mc" for Monte Carlo, "lm", "mm", "hm" for real data

  my $mult_class_label = shift;
  my $mult_limit_low = shift;
  my $mult_limit_high = shift;

  #--------------------------------------------------------------
  tie my %run_scalar_hash, "Tie::IxHash"; 
  tie my %event_scalar_hash, "Tie::IxHash"; 
  
  %run_scalar_hash = ();
  %event_scalar_hash = ();

  tie my %run_statistics_hash, "Tie::IxHash"; 
  %run_statistics_hash = ();

  #--------------------------------------------------------------
  open REPORT, $report_filename or do{
    print "Cannot open report $report_filename:$! \n";
    return;
  };
  #--------------------------------------------------------------
  # parse report

  # pmj 15/9/00: put into temporary event-wise hash, calculate statistics afterward

  tie my %event_hash,  "Tie::IxHash";
  tie my %scalar_name_hash,  "Tie::IxHash";
  
  my $report_previous_line = -9999999;
  
  my $icount_event = 0;
  
  while ( my $report_line = <REPORT> ){
      
      #---	
      # protect against successive duplicate lines in report file
      
      while ($report_line eq $report_previous_line){
	$report_line = <REPORT>;
	defined ($report_line) or last;
      }
      $report_previous_line = $report_line;
      #---
      
      # look for new event in report file
      $report_line =~ /==\s+Event\s+(\d+)\s+(\S+)/ and do{
	$2 =~ /finish/ and last;
	$icount_event++;
	next;
      };
      
      # does line contain scalars?
      
      $report_line =~ /\# (.*):\s+(\d+)/ or next;
      
      #-- accumulate run-wise quantities
      
      my $name = $1;
      my $value = $2;
      
      # change multiple blanks to single underscore
      $name =~ s/ +/_/g;
      
      # pmj 26/8/00
      # add multiplicity class to scalar name for real data, skip this for MC
      if ( $mult_class_label ne "mc"){
	$name .= "_".$mult_class_label;
      }
      
      $event_hash{$icount_event}->{$name} = $value;
      
      $name =~ /track_nodes/ and $event_hash{$icount_event}->{track_nodes_save} = $value;
      $name =~ /primary_tracks/ and $event_hash{$icount_event}->{prim_tracks_save} = $value;
      
      
      $scalar_name_hash{$name} = 1;
      
    }
  
  #--------------------------------------------------------------
  # initialize statistics counters

  my $n_event_all = 0;
  my $n_event_prim_vertex = 0;
  
  foreach my $name (keys %scalar_name_hash){
    $run_statistics_hash{$name}->{n_event} = 0;
    $run_statistics_hash{$name}->{min} = 999999.;
    $run_statistics_hash{$name}->{max} = -999999.;
    $run_statistics_hash{$name}->{sum} = 0.;
    $run_statistics_hash{$name}->{sum_sqr} = 0;
    $run_statistics_hash{$name}->{mean} = -999999.;
    $run_statistics_hash{$name}->{rms} = -999999.;
  }
  
  #--------------------------------------------------------------
  # loop through events
  
  foreach $icount_event ( keys %event_hash ){
    
    # count all events passing cuts for mult class
    my $track_nodes = $event_hash{$icount_event}->{track_nodes_save};
    next unless ($track_nodes >= $mult_limit_low and $track_nodes < $mult_limit_high);
    
    $n_event_all++;
    
    # in following, only consider events with primary vertex
    my $prim_tracks = $event_hash{$icount_event}->{prim_tracks_save};
    $prim_tracks or next;
    
    $n_event_prim_vertex++;
    
    # now get run-wise accumulated quanitities
    
    foreach my $name ( keys %scalar_name_hash ){
      
      $run_statistics_hash{$name}->{n_event}++;
      
      my $value = $event_hash{$icount_event}->{$name};
      
      $run_statistics_hash{$name}->{sum} += $value;
      $run_statistics_hash{$name}->{sum_sqr} += $value*$value;
      
      my $min = $run_statistics_hash{$name}->{min};
      $run_statistics_hash{$name}->{min} = ($value < $min) ? $value : $min;
      
      my $max = $run_statistics_hash{$name}->{max};
      $run_statistics_hash{$name}->{max} = ($value > $max) ? $value : $max;
    }
  }
  
  #--------------------------------------------------------------
  # calculate run-wise quantities
  
  no strict 'refs';

  foreach my $name ( keys %run_statistics_hash){

    exists $run_statistics_hash{$name}->{n_event} or next;
    
    my $n_event = $run_statistics_hash{$name}->{n_event};
    $n_event and do{
      my $mean = $run_statistics_hash{$name}->{sum} / $n_event;
      my $mean_sq = $run_statistics_hash{$name}->{sum_sqr} / $n_event;
      
      $run_statistics_hash{$name}->{mean} = $mean;
      
      my $arg = $mean_sq - ($mean*$mean);
      $arg >= 0 and $run_statistics_hash{$name}->{rms} = sqrt( $arg );
    };
  }
  #--------------------------------------------------------------
  # now copy to run_scalar_hash, which is flat structure (without sub-hashes)

  $run_scalar_hash{n_event_all} = $n_event_all;
  $run_scalar_hash{n_event_prim_vertex} = $n_event_prim_vertex;

  foreach my $name ( keys %run_statistics_hash){
    
    foreach my $field ( 'mean', 'rms', 'min', 'max' ){
      my $value = (int ( 100 * $run_statistics_hash{$name}->{$field})) / 100;
      my $string = $name."_".$field;
      defined($value) and $run_scalar_hash{$string} = $value;
    }
  }
  
  #--------------------------------------------------------------
  close REPORT;
  #--------------------------------------------------------------
  return \%run_scalar_hash, \%event_scalar_hash;
} 
#=========================================================
sub doEvents{ 

  my $report_key = shift;
  my $report_filename = shift;

  #--------------------------------------------------------------
  tie my %run_scalar_hash, "Tie::IxHash"; 
  tie my %event_scalar_hash, "Tie::IxHash"; 

  %run_scalar_hash = ();
  %event_scalar_hash = ();

  tie my %run_statistics_hash, "Tie::IxHash"; 
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
  my $event = 0;
  my $icount_event = 0;

  my $report_previous_line = -9999999;
  my $logfile_previous_line;

 REPORT: {

    while ( my $report_line = <REPORT> ){

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
	  while ( my $logfile_line = <LOGFILE> ){
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

	my $logfile_line;

	while ($logfile_line = <LOGFILE>){
	  last if $logfile_line ne $logfile_previous_line;
	}
	$logfile_previous_line = $logfile_line;
	#---

	$logfile_line =~ s/.*Info: //;
	
	# are these the same? 
	my $string = $report_line;

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

  foreach my $name ( keys %run_statistics_hash){

    my $n_event = $run_statistics_hash{$name}->{n_event};
    $n_event and do{
      my $mean = $run_statistics_hash{$name}->{sum} / $n_event;
      my $mean_sq = $run_statistics_hash{$name}->{sum_sqr} / $n_event;
      
      $run_statistics_hash{$name}->{mean} = $mean;

      my $arg = $mean_sq - ($mean*$mean);
      $arg >= 0 and $run_statistics_hash{$name}->{rms} = sqrt( $arg );
    };
  }

  # now copy to run_scalar_hash, which is flat structure (without sub-hashes)
  $run_scalar_hash{n_event} = $run_statistics_hash{track_nodes}->{n_event};

  foreach my $name ( keys %run_statistics_hash){
    foreach my $field ( 'mean', 'rms', 'min', 'max' ){
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
