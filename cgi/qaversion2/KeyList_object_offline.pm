#! /usr/bin/perl
#
# derived KeyList class for offline jobs
#
#========================================================
package KeyList_object_offline;
#========================================================
use CGI qw/:standard :html3/;

use QA_globals;

use QA_utilities;
use Db_KeyList_utilities;
use Browser_object;

use base qw(KeyList_object);

use strict;
#--------------------------------------------------------
1;
#========================================================
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);

  #$classname eq __PACKAGE__ and 
  #  die __PACKAGE__, " is virtual";

  return $self;
}


#========================================================
# popup menu for selecting jobs
# currently select on 
#
# prodOptions
# runID
# QAstatus
# jobstatus
# createTime
# dataset
# job created

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # fill selection values, selection_labels

  my $select_ref = $self->GetSelectionOptions;

  #prodOptions - see QA_db_utilities::db_GetOfflineSelections()
  my (@prodOptions_values, %prodOptions_labels);

  foreach my $prodSeries (keys %{$select_ref->{prodOptions}}){
    push @prodOptions_values, $prodSeries;
    $prodOptions_labels{$prodSeries} = $prodSeries;
    
    foreach my $chainName ( @{$select_ref->{prodOptions}->{$prodSeries}} ){
      my $value = "$prodSeries;$chainName";
      push @prodOptions_values, $value;
      $prodOptions_labels{$value} = "$prodSeries - $chainName";
    }
  }
  # runID
  my (@runID_values, %runID_labels);
  @runID_values = @{$select_ref->{runID}};

  
  # QA status (errors, warnings, ok)
  my @macro_names = @{$select_ref->{macroName}};

  # QA status now fill in errors and warnings info
  my @status_values = ('any','ok','not_ok','done', 'not_done');
  my %status_labels = (
		       any      => 'any',
		       ok       => 'ok',
		       not_ok   => 'not ok',
		       done     => 'done',
		       not_done => 'not done'
		       );

  push @status_values, 'warnings';$status_labels{warnings} = 'warnings';

  foreach my $macro_name (@macro_names){
    my $value = "warnings;$macro_name";
    push(@status_values, $value);
    $status_labels{$value} = "warn - $macro_name";
  }
  push @status_values, 'errors'; $status_labels{errors} =  'errors';

  foreach my $macro_name (@macro_names){
    my $value = "errors;$macro_name";
    push(@status_values, $value);
    $status_labels{$value} = "err - $macro_name";
  }

  # dataset
  my (@dataset_values,%dataset_labels);
  @dataset_values = @{$select_ref->{dataset}};
    
  # make it cleaner
  foreach my $element (@dataset_values){
#    (my $clean_element = $element) =~ s/\// /g;
    $dataset_labels{$element} = $element;
  }
  
  # job status 
  my (@jobStatus_values, %jobStatus_labels);
  
  @jobStatus_values = ('any', 'done','not_done');
  %jobStatus_labels = ( any      => 'any',
			done     => 'done',
			not_done => 'not done' );

  # createTime
  my (@createTime_values, %createTime_labels);
  push @createTime_values, 'three_days'   ; 
  $createTime_labels{'three_days'} = '3 days';
  push @createTime_values, 'seven_days'   ; 
  $createTime_labels{seven_days} = '7 days';
  push @createTime_values, 'fourteen_days'; 
  $createTime_labels{fourteen_days} = '14 days';
  
  # make general adjustments

  unshift @prodOptions_values, 'any'; $prodOptions_labels{any} = 'any';
  unshift @runID_values, 'any';       $runID_labels{any} = 'any';
  unshift @createTime_values, 'any';  $createTime_labels{any} = 'any';
  unshift @dataset_values, 'any';     $dataset_labels{any} = 'any';

  # make the cgi strings

  my $prodOptions_string = 
    b('prodOptions').br.
      $gCGIquery->popup_menu(-name    => 'select_prodOptions',
			 -values  => \@prodOptions_values,
			 -default => $prodOptions_values[0],
			 -labels  => \%prodOptions_labels);

  my $runID_string =
    b('runID').br.
      $gCGIquery->popup_menu(-name    => 'select_runID',
			 -values  => \@runID_values,
			 -default => $runID_values[0] );

  my $QAstatus_string = 
    b('QA status').br.
      $gCGIquery->popup_menu(-name    => 'select_QAstatus',
			 -values  => \@status_values,
			 -default => $status_values[0],
			 -labels  => \%status_labels);

  my $createTime_string =
    b('job created').br.
      $gCGIquery->popup_menu(-name    => 'select_createTime',
			 -values  => \@createTime_values,
			 -default => $createTime_values[0],
			 -labels  => \%createTime_labels);

  my $jobStatus_string =
    b('job status').br.
      $gCGIquery->popup_menu(-name    => 'select_jobStatus',
			 -values  => \@jobStatus_values,
			 -default => $jobStatus_values[0],
			 -labels  => \%jobStatus_labels);

  my $dataset_string =
    b('dataset').br.
      $gCGIquery->popup_menu(-name    => 'select_dataset',
			 -values  => \@dataset_values,
			 -default => $dataset_values[0],
			 -labels  => \%dataset_labels );


  my $submit_string = br.$gCGIquery->submit('Display datasets');

  my (@table_rows);

  $table_rows[0] = td( [h3('Select dataset:')]);
  push @table_rows, td( [$prodOptions_string, $runID_string, $dataset_string ]);
  push @table_rows, td( [$QAstatus_string, $jobStatus_string, $createTime_string ]);
  push @table_rows, td( [$submit_string] );

  my $table_string = 
    table({-align=>'center'}, Tr({-valign=>'top'}, \@table_rows));

  my $script_name   = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $select_data_string =
      $gCGIquery->startform(-action=>"$script_name/upper_display",
			-TARGET=>"list").
	table({-align=>'center'}, Tr({-valign=>'top'}, \@table_rows)).
	  $hidden_string.
	    $gCGIquery->endform;

  return $select_data_string;

}
#========================================================
# get the selected parameters chose by the user
# returns an array of cgi values according to the popup menu

sub SelectedParameters{
  my $self = shift;

  my $select_prodOptions = $gCGIquery->param('select_prodOptions');
  my $select_runID       = $gCGIquery->param('select_runID');
  my $select_status      = $gCGIquery->param('select_QAstatus');
  my $select_jobStatus   = $gCGIquery->param('select_jobStatus');
  my $select_createTime  = $gCGIquery->param('select_createTime');
  my $select_dataset     = $gCGIquery->param('select_dataset');

  return ($select_prodOptions, $select_runID, $select_status,
	  $select_jobStatus, $select_createTime, $select_dataset);

}


1;
