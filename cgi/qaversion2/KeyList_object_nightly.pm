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

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # using 'map' technique in the cgi forms - originated by ben norman

  # possible criteria to select on 
  # these are the cgi parameter names
  $self->{select_fields} = [ 'eventGen',
			     'LibLevel',
			     'platform',
			     'eventType',
			     'geometry',
			     'onDisk',
			     'QAstatus',
			     'jobStatus',
			     'createTime' 
			   ];
  # selection labels for the user
  $self->{select_labels} = { eventGen  => 'event gen',
			     LibLevel  => 'library',
			     platform  => 'platform',
			     eventType => 'event type',
			     geometry  => 'geometry',
			     onDisk    => 'on disk',
			     QAstatus  => 'QA status',
			     jobStatus => 'job status',
			     createTime=> 'job createTime'
			   };

  # possible values for each selection field
  # ref of hash of refs to arrays
  
  %{$self->{values}} = map {$_, ['any']} @{$self->{select_fields}};

  # possible labels for each selection field
  # ref of hash of refs to hashes
  # not all values need labels...
  $self->{labels}; 

  # get some selection values from the database
  my $select_ref = $self->GetSelectionOptions();
  
  # fill some selection values...
  push @{$self->{values}{eventGen}}, @{$select_ref->{eventGen}};
  push @{$self->{values}{LibLevel}}, @{$select_ref->{LibLevel}};
  push @{$self->{values}{platform}}, @{$select_ref->{platform}};
  push @{$self->{values}{eventType}},@{$select_ref->{eventType}};
  push @{$self->{values}{geometry}}, @{$select_ref->{geometry}};

  # on disk
  push @{$self->{values}{onDisk}}, ('on disk', 'not on disk');
  
  # job status 
  push @{$self->{values}{jobStatus}}, ('done', 'not done');

  # QA status
  my @macro_names = @{$select_ref->{macroName}};

  # now fill in errors and warnings info
  my $abbrev;
  push @{$self->{values}{QAstatus}}, ( 'ok','not ok','done','not done');
  %{$self->{labels}{QAstatus}} = map{$_, $_} @{$self->{values}{QAstatus}};

  foreach my $status ('warnings', 'errors') {

    push @{$self->{values}{QAstatus}}, "$status";
    $self->{labels}{QAstatus}{$status} = "$status";
  
    foreach my $macro_name (@macro_names){
      my $value = "$status;$macro_name";
      push @{$self->{values}{QAstatus}}, $value;
      ($abbrev = $status) =~ s/warnings/warn/;
      ($abbrev = $status) =~ s/errors/err/;
      $self->{labels}{QAstatus}{$value} = "$abbrev - $macro_name";
    }
  }
    
  # createTime
  push @{$self->{values}{createTime}}, ('three_days','seven_days', 'fourteen_days');
  
  $self->{labels}{createTime}{three_days} = '3 days ago';
  $self->{labels}{createTime}{seven_days} = '7 days ago';
  $self->{labels}{createTime}{fourteen_days} = '14 days ago';
  
  # set defaults
  # unless specified otherwise, default will be 'any'
  $self->{defaults}{eventGen}   = 1;
  $self->{defaults}{LibLevel}   = 1;
  $self->{defaults}{onDisk}     = 1;
  $self->{defaults}{QAstatus}   = 3;
  $self->{defaults}{createTime} = 1;

  my $submit_string = br.$gCGIquery->submit('Display datasets');

  my @table_rows;
  #--- 
  # pmj 21/6/00: more compact display, no header. Pulldown menu for changing classes
  # has been moved to banner so there is more horizontal space

  #  $table_rows[0] =  td ( [h3('Select dataset:')]);
  #  push @table_rows, td([$self->GetRowOfMenus('eventGen','LibLevel','platform')]);
  #  push @table_rows, td([$self->GetRowOfMenus('eventType','geometry','onDisk')]);
  #  push @table_rows, td([$self->GetRowOfMenus('QAstatus','jobStatus','createTime')]);
  #  push @table_rows, td( [$submit_string ] ) ;

  push @table_rows, td([$self->GetRowOfMenus(
					     'eventGen'
					     ,'LibLevel'
					     ,'platform'
					     ,'jobStatus'
					     ,'QAstatus'
					    )
		       ]);

  push @table_rows, td([$self->GetRowOfMenus(
					     'eventType'
					     ,'geometry'
					     ,'onDisk'
					     ,'createTime'
					    )
		       ,$submit_string
		       ]);

  #---

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $table_string =
    table({-align=>'left'}, Tr({-valign=>'top'}, \@table_rows));

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
	  $gCGIquery->param('eventGen'),
	  $gCGIquery->param('LibLevel'),
	  $gCGIquery->param('platform'),
	  $gCGIquery->param('eventType'),
	  $gCGIquery->param('geometry'),
	  $gCGIquery->param('QAstatus'),
	  $gCGIquery->param('onDisk'),
	  $gCGIquery->param('jobStatus'),
	  $gCGIquery->param('createTime')
	 );

}
 
1;
