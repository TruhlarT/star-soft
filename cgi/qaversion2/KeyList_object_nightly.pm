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
1;

#========================================================
# more members

my %members = ( # cgi parameter names 
	       select_fields => [ 'eventGen',
				  'LibLevel',
				  'platform',
				  'eventType',
				  'geometry',
				  'QAstatus',
				  'onDisk',
				  'jobStatus',
				  'createTime',
				  'QAdoneTime'
				],
	       # labels for user
	       select_labels => { eventGen  => 'event gen',
				  LibLevel  => 'library',
				  platform  => 'platform',
				  eventType => 'event type',
				  geometry  => 'geometry',
				  onDisk    => 'on disk',
				  QAstatus  => 'QA status',
				  jobStatus => 'prod job status',
				  createTime=> 'prod job create time',
				  QAdoneTime=> 'QA done time'
				}
	      );

#========================================================

sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  # addmore members
  @{$self}{keys %members} = values %members;

  $classname eq __PACKAGE__ and 
    die __PACKAGE__, " is virtual";

  bless($self,$classname);

  return $self;
}

#----------
# popup menu for selecting jobs

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';
  
  # possible values for each selection field
  # ref of hash of refs to arrays
  
  %{$self->{values}} = map {$_, ['any']} @{$self->{select_fields}};

  # possible labels for each selection field
  # ref of hash of refs to hashes
  # not all values need labels...
  $self->{labels} = undef; 


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
  $self->FillJobStatusMenu();

  # QA status
  my @macro_names = @{$select_ref->{macroName}};

  $self->FillQAStatusMenu(@macro_names);
    
  # job createTime
  $self->FillJobCreateTimeMenu();
  
  # -- qa done time --
  $self->FillQADoneTimeMenu();

  # set defaults
  # unless specified otherwise, default will be 'any'
  $self->{defaults}{eventGen}   = 'hadronic_cocktail';
  $self->{defaults}{LibLevel}   = 'dev';
  $self->{defaults}{onDisk}     = 'on disk';
  $self->{defaults}{QAstatus}   = 'done';
  #$self->{defaults}{createTime} = 'seven_days';
  $self->{defaults}{QAdoneTime} = 'seven_days';

  my $submit_string = br.$gCGIquery->submit('Display datasets');

  my @table_rows;
  #--- 
  # pmj 21/6/00: more compact display, no header. Pulldown menu for changing classes
  # has been moved to banner so there is more horizontal space

  my @rows = 
    (
     td([$self->GetRowOfMenus(
			      'eventGen'
			      ,'LibLevel'
			      ,'platform'
			      ,'jobStatus'
			      ,'QAstatus'
			     )
	]),
     td([$self->GetRowOfMenus(
			      'eventType'
			      ,'geometry'
			      ,'onDisk'
			      ,'createTime'
			      ,'QAdoneTime'
			     )
	                      ,$submit_string
	])
    );
  #---

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $table_string =
    table({-align=>'left'}, Tr({-valign=>'top'}, [@rows]));

  my $select_data_string = 
      $gCGIquery->startform(-action=>"$script_name/upper_display",
			    -TARGET=>"list").
	$table_string.
	  $hidden_string.
	    $gCGIquery->endform;

  return $select_data_string;

}

1;
#================================================================
#
# nightly_MC
#
package KeyList_object_nightly_MC;
use base qw(KeyList_object_nightly);

sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  bless($self,$classname);

  return $self;
}

#----------

sub GetSelectionOptions{
  my $self = shift;
  
  my $menuRef = $self->GetSelectionOptionsStorable();

  if(!defined $menuRef){
    return Db_KeyList_utilities::GetNightlySelectionsMC();
  }
}

#----------

sub GetSelectedKeysFromDb{
  my $self = shift;

  return 
    Db_KeyList_utilities::GetNightlyKeysMC($self->SelectedParameters());

}

1;
#==================================================================
#
# nightly_real
#

package KeyList_object_nightly_real;
use base  qw(KeyList_object_nightly);

sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  bless($self,$classname);

  return $self;
}

#----------

sub GetSelectionOptions{
  my $self = shift;
  
  my $menuRef = $self->GetSelectionOptionsStorable();

  if(!defined $menuRef){
    return Db_KeyList_utilities::GetNightlySelectionsReal();
  }
}
#----------
sub GetSelectedKeysFromDb{
  my $self = shift;

  return 
    Db_KeyList_utilities::GetNightlyKeysReal($self->SelectedParameters());

}

1;

