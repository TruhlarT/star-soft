#! /usr/bin/perl
#
# derived KeyList class for nightly 
#
#========================================================
package KeyList_object_nightly;
#========================================================
use CGI qw/:standard :html3/;

use QA_globals;
use QA_utilities;
use Db_KeyList_utilities;
use Browser_object;

use strict;
use base qw(KeyList_object);
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

# event Gen
# library
# platform
# eventtype
# geometry
# on disk
# QA status
# job status
# job created

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # fill selection values, selection_labels

  my $select_ref = $self->GetSelectionOptions;
  
  # fill the various selection values...

  my @eventGen_values  = @{$select_ref->{eventGen}};
  my @LibTag_values    = @{$select_ref->{LibTag}};
  my @platform_values  = @{$select_ref->{platform}};
  my @eventType_values = @{$select_ref->{eventType}};
  my @geometry_values  = @{$select_ref->{geometry}};
  
  # on disk
  my @ondisk_values = ('any', 'on_disk', 'not_on_disk');
  my %ondisk_labels = (any         => 'any',
		       on_disk     => 'on disk', 
		       not_on_disk => 'not on disk' );
		       
  # job status 
  my (@jobStatus_values, %jobStatus_labels);

  push @jobStatus_values, 'done'    ; $jobStatus_labels{done} = 'done';
  push @jobStatus_values, 'not_done'; $jobStatus_labels{not_done} ='not done';

  # QA status (errors, warnings, ok)
  my (@macro_names, @status_values, %status_labels);

  @macro_names = @{$select_ref->{macroName}};

  # now fill in errors and warnings info
  push @status_values, 'ok';      $status_labels{ok} = 'ok';     
  push @status_values, 'not_ok';  $status_labels{not_ok} = 'not ok'; 
  push @status_values, 'done';    $status_labels{done} = 'done';
  push @status_values, 'not_done';$status_labels{not_done} = 'not done';

  push @status_values, 'warnings';$status_labels{warnings} = 'warnings';

  # macro specific warnings 
  foreach my $macro_name (@macro_names){
    my $value = "warnings;$macro_name";
    push( @status_values, $value );
    $status_labels{$value} = "warn - $macro_name";
  }
  push @status_values, 'errors'; $status_labels{errors} =  'errors';

  # macro specific errors
  foreach my $macro_name (@macro_names){
    my $value = "errors;$macro_name";
    push( @status_values, $value );
    $status_labels{$value} = "err - $macro_name";
  }

  # createTime
  my (@createTime_values, %createTime_labels);
  @createTime_values = ('any','three_days', 'seven_days', 'fourteen_days');

  $createTime_labels{any}          = 'any';         
  $createTime_labels{'three_days'} = '3 days';
  $createTime_labels{seven_days}   = '7 days';
  $createTime_labels{fourteen_days}= '14 days';
  
  # make general adjustments
  
  unshift @LibTag_values, 'any';
  unshift @platform_values, 'any';
  unshift @eventType_values, 'any';
  unshift @geometry_values, 'any';
  unshift @status_values, 'any';   $status_labels{any} = 'any';
  unshift @jobStatus_values, 'any'; $jobStatus_labels{any} = 'any';

  # maybe add selection hash later...

  # make the form

  # special case for the event generators
  # if real data, we dont need it
  # this can be determined if the @eventGen_values is undefined
  my $eventGen_string;
  
  if (defined @eventGen_values)
  { # found some event Gen
    unshift @eventGen_values, 'any'; #general adjustments
    $eventGen_string =
      b('event gen').br.
	$gCGIquery->popup_menu(-name    => 'select_eventGen',
			       -values  => \@eventGen_values,
			       -default => $eventGen_values[1] );
  } # no event Gen
  else {$eventGen_string = b('event gen').br.br.b('n/a'); }

  my $LibTag_string = 
    b('library').br.
      $gCGIquery->popup_menu(-name    => 'select_LibTag',
			 -values  => \@LibTag_values,
			 -default => $LibTag_values[1] );
  
  my $platform_string = 
    b('platform').br.
      $gCGIquery->popup_menu(-name    => 'select_platform',
			 -values  => \@platform_values,
			 -default => $platform_values[0] );

  my $eventType_string =
    b('event type').br.
      $gCGIquery->popup_menu(-name    => 'select_eventType',
			 -values  => \@eventType_values,
			 -default => $eventType_values[0] );

  my $geometry_string =
    b('geometry').br.
      $gCGIquery->popup_menu(-name    => 'select_geometry',
			 -values  => \@geometry_values,
			 -default => $geometry_values[0] );

  my $status_string = 
    b('QA status').br.
      $gCGIquery->popup_menu(-name    => 'select_QAstatus',
			 -values  => \@status_values,
			 -default => $status_values[3],
			 -labels  => \%status_labels );

  my $ondisk_string =
    b('on disk' ).br.
      $gCGIquery->popup_menu(-name    => 'select_ondisk',
			 -values  => \@ondisk_values,
			 -default => $ondisk_values[1],
			 -labels  => \%ondisk_labels );

  my $jobStatus_string =
    b('job status').br.
      $gCGIquery->popup_menu(-name    => 'select_jobStatus',
			 -values  => \@jobStatus_values,
			 -default => $jobStatus_values[0],
			 -labels  => \%jobStatus_labels );

  my $createTime_string =
    b('job createTime').br.
      $gCGIquery->popup_menu(-name    => 'select_createTime',
			 -values  => \@createTime_values,
			 -default => $createTime_values[0],
			 -labels  => \%createTime_labels);

  my $submit_string = br.$gCGIquery->submit('Display datasets');

  my @table_rows;

  $table_rows[0] =  td ( [h3('Select dataset:')]);
  push @table_rows, td( [$eventGen_string, $LibTag_string, $platform_string] );
  push @table_rows, td( [$eventType_string, $geometry_string, $ondisk_string] );
  push @table_rows, td( [$status_string, $jobStatus_string, $createTime_string]);
  push @table_rows, td( [$submit_string ] ) ;

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $table_string =
    table({-align=>'center'}, Tr({-valign=>'top'}, \@table_rows));

  my $select_data_string = 
      $gCGIquery->startform(-action=>"$script_name/upper_display",
			    -TARGET=>"list").
	$table_string.
	  $hidden_string.
	    $gCGIquery->endform;

  return $select_data_string;

}
#========================================================
# get the selected parameter values chose by the user
# returns an array of cgi values according to the popup menu

sub SelectedParameters{
  my $self = shift;

  return (
	  $gCGIquery->param('select_eventGen'),
	  $gCGIquery->param('select_LibTag'),
	  $gCGIquery->param('select_platform'),
	  $gCGIquery->param('select_eventType'),
	  $gCGIquery->param('select_geometry'),
	  $gCGIquery->param('select_QAstatus'),
	  $gCGIquery->param('select_ondisk'),
	  $gCGIquery->param('select_jobStatus'),
	  $gCGIquery->param('select_createTime')
	 );

}
 


1;
