#! /usr/bin/perl

# pmj 31/8/99
#=========================================================

use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Time::Local;
use Data::Dumper;
use Tie::IxHash;

#-------------------------------------------------------
use QA_utilities;
use QA_object;
use QA_globals;

use QA_make_reports;

use QA_report_object;
use QA_report_io;

#=========================================================
# get filename containing report keys to operate on
#$report_key_filename = "/star/data1/jacobs/qa/batch/test1.txt";

$report_key_filename = shift;

#get rid of potential white space
$report_key_filename =~ s/\s+//;
#-----------------------------------------------------------------------------
&QA_utilities::cleanup_topdir;
#-----------------------------------------------------------------------------
# get action from file type
($action = $report_key_filename) =~ s/.*\.//;
#-----------------------------------------------------------------------------

ACTION: {

  # update and do QA on everything

  $action eq 'update_and_qa' and do{
    QA_utilities::get_QA_objects('update');
    foreach $report_key (keys %QA_object_hash){
      $QA_object_hash{$report_key}->DoQA('no_tables');
    }
    last ACTION;
  };

  # for all other actions, get selected report keys from file to operate on

  # first check that file of report keys exists...
  -e $report_key_filename or do{
    print "Argument not defined: $report_key_filename \n";
    exit;
  };
  #---

  @QA_key_list = &QA_utilities::get_QA_objects;
  @report_key_list = get_selected_key_list_batch($report_key_filename);

  $action eq 'do_qa' and do{
    foreach $report_key (@report_key_list){
      $QA_object_hash{$report_key}->DoQA('no_tables');
    }
    last ACTION;
  };

  $action eq 'redo_qa' and do{
    foreach $report_key (@report_key_list){
      $QA_object_hash{$report_key}->DeleteQAFiles;
      $QA_object_hash{$report_key}->DoQA('no_tables');
    }
    last ACTION;
  };

  $action eq 'test' and do{
    foreach $report_key (@report_key_list){
      print "Testing: report key = $report_key \n";
    }
    last ACTION;
  };


}
#=================================================================
### END OF MAIN ###
#=================================================================
sub get_selected_key_list_batch {

  my $report_key_file = shift;

  #-----------------------------------------------------------------------------
#  foreach $key (keys %QA_object_hash){
#    print "QA_object_hash key $key \n";
#  }

  #-----------------------------------------------------------------------------
  # file contains list of report keys

  open REPORTKEYS, $report_key_file or die "Cannot open report key file $report_key_file \n";

  @selected_key_list = ();

  while( $report_key = <REPORTKEYS> ) {

    #get rid of potential white space
    $report_key =~ s/\s+//;
    
    $QA_object_hash{$report_key}->OnDisk() and push @selected_key_list, $report_key;
  }

  #-----------------------------------------------------------------------------
  
  return @selected_key_list;
  
}

