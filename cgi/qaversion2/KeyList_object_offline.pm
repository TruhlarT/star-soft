#! /opt/star/bin/perl
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
use QA_db_utilities qw(:db_globals); # import db handle and tables

use base qw(KeyList_object);

use vars qw(%members);

use strict;
1;

#========================================================
sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  %members = (
	      # possible selection fields (i.e. popup menus)
	      select_fields => [ 
				'prodSeries',
				'runID',
				'QAstatus',
				'jobStatus',
				'createTime',
				'dataset',
				'QAdate'
			       ],
	      
	      # selection labels for the user
	      select_labels => {
				prodSeries  => 'prod',
				runID       => 'runID',
				QAstatus    => 'QA status',
				jobStatus   => 'prod job status',
				createTime  => 'prod job create time',
				dataset     => 'dataset',
				QAdate  => 'QA done time'
			       },
	      # these are the fields and tables requested from the db
	      db_fields => { 
			    prodSeries  => $JobStatus,
			    runID       => $FileCatalog,
			    dataset     => $FileCatalog
			   }
	      
	      
	     );


  # addmore members
  @{$self}{keys %members} = values %members;


  #$classname eq __PACKAGE__ and 
  #  die __PACKAGE__, " is virtual";
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
  my $select_ref = $self->GetSelectionOptions();

  # -- production options -- (prod series)
  foreach my $field( keys %{$self->{db_fields}}){
    push @{$self->{values}{$field}}, @{$select_ref->{$field}};
  }

  # -- QA status -- (errors, warnings, ok)
  #$my @macro_names = @{$select_ref->{macroName}};
 
  $self->FillQAStatusMenu();
  
  # -- job status -- 
  $self->FillJobStatusMenu();

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
     td([$self->GetRowOfMenus('prodSeries',
			      'jobStatus',
			      'QAstatus',
			      'dataset')
	]),
     
     td([$self->GetRowOfMenus(
			      'runID',
			      'createTime',
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

1;
#================================================================
#
# offline_MC
#
package KeyList_object_offline_MC;
use base qw(KeyList_object_offline);

sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  bless($self,$classname);

  return $self;
}

#----------

sub GetSelectionOptionsFromDb{
  my $self = shift;

  return Db_KeyList_utilities::GetOfflineSelectionsMC($self->{db_fields});
  
}

#----------

sub GetSelectedKeysFromDb{
  my $self = shift;

  return 
    Db_KeyList_utilities::GetOfflineKeysMC($self->SelectedParameters());

}
1;
#==================================================================
#
# offline_real
#

package KeyList_object_offline_real;
use base  qw(KeyList_object_offline);

sub new{
  my $proto     = shift;
  my $classname = ref($proto) || $proto;
  my $self      = $classname->SUPER::new(@_);

  bless($self,$classname);

  return $self;
}

#----------

sub GetSelectionOptionsFromDb{
  my $self = shift;
    return Db_KeyList_utilities::GetOfflineSelectionsReal($self->{db_fields});

}

#----------

sub GetSelectedKeysFromDb{
  my $self = shift;

  return 
    Db_KeyList_utilities::GetOfflineKeysReal($self->SelectedParameters());

}
1;
