#! /usr/bin/perl
#
# derived KeyList class for fast offline jobs
#
#========================================================
package KeyList_object_offline_fast;
#========================================================
use CGI qw/:standard :html3/;

use QA_globals;

use QA_utilities;
use Db_KeyList_utilities;
use Browser_object;
use QA_db_utilities qw(:db_globals); # import db handle and tables

use base qw(KeyList_object);

use vars qw(%members);

use strict;
1;
#========================================================


#========================================================
sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  %members = (
	    # possible cgi selection fields (i.e. popup menus)
	    select_fields => [ 
			      $DAQInfo{runNumber},
			      $DAQInfo{scaleFactor},
			      $DAQInfo{beamE},
			      $DAQInfo{collision},
			      'QAdate',
			      'QAstatus'
			     ],
	    
	    # selection labels for the user
	    select_labels => {
			      $DAQInfo{runNumber}   => 'run',
			      $DAQInfo{scaleFactor} => 'B scale factor',
			      $DAQInfo{beamE}       => 'beam energy',
			      $DAQInfo{collision}   => 'collision',
			      QAdate  => 'QA done time',
			      QAstatus    => 'QA status'
			     },
	   db_fields => { $DAQInfo{runNumber}   => $DAQInfo{Table},
			  $DAQInfo{scaleFactor} => $DAQInfo{Table},
			  $DAQInfo{collision}   => $DAQInfo{Table},
			  $DAQInfo{beamE}       => $DAQInfo{Table}
			}
			    
	   );

  # addmore members
  @{$self}{keys %members} = values %members;

  bless($self,$classname);

  return $self;
}


#----------
# popup menu for selecting jobs
#

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # possible values for each selection field
  # ref of hash of refs to arrays
  # init with 'any's
  %{$self->{values}} = map {$_, ['any']} @{$self->{select_fields}};

  # possible labels for each selection field
  # ref of hash of refs to hashes
  # not all values need labels...
  $self->{labels} = undef; 

  # get some selection values from the database
  my $select_ref = $self->GetSelectionOptions(1);

  # -- runNumber,scaleFactor, beamE, collision
  foreach my $field ('runNumber','scaleFactor','beamE','collision'){
    push @{$self->{values}{$field}}, @{$select_ref->{$field}};
  }

  # -- QA status -- (errors, warnings, ok)
  $self->FillQAStatusMenu();
  
  # -- job create time --
  $self->FillJobCreateTimeMenu();

  # -- qa done time --
  $self->FillQADoneTimeMenu();

  # set defaults.  unless otherwise stated, default is 'any'
  $self->{defaults}{QAstatus}  = 'done';
  $self->{defaults}{QAdate} = 'seven_days';

  my $submit_string = br.$gCGIquery->submit('Display datasets');

  #--- 
  # pmj 21/6/00: more compact display, no header. Pulldown menu for changing classes
  # has been moved to banner so there is more horizontal space

  my $null_string = "";

  my @rows =
    (
     td([$self->GetRowOfMenus('runNumber',
			      'scaleFactor',
			      'QAstatus')
	]),
     
     td([$self->GetRowOfMenus(
			      'beamE',
			      'collision',
			      'QAdate'
			      ) 
	                       
	                       ,$submit_string
	])
    );
  
  #---
  #my $table_string = 
  #    table({-align=>'center'}, Tr({-valign=>'top'}, \@table_rows));
  
  
  return $self->TableString(@rows);

}

#----------

sub GetSelectionOptionsFromDb{
  my $self = shift;
  
    return Db_KeyList_utilities::GetOfflineSelectionsFast($self->{db_fields});

}

#----------

sub GetSelectedKeysFromDb{
  my $self = shift;

  return 
    Db_KeyList_utilities::GetOfflineKeysFast($self->SelectedParameters());

} 



1;
