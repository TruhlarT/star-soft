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
#


sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # possible selection fields (i.e. popup menus)
  $self->{select_fields} = [ 
			    'prodOptions',
			    'runID',
			    'QAstatus',
			    'jobStatus',
			    'createTime',
			    'dataset',
			    'QAdoneTime'
			   ];

  # selection labels for the user
  $self->{select_labels} = {
			    prodOptions => 'prod options',
			    runID       => 'runID',
			    QAstatus    => 'QA status',
			    jobStatus   => 'prod job status',
			    createTime  => 'prod job create time',
			    dataset     => 'dataset',
			    QAdoneTime  => 'QA done time'
			   };

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

  # -- production options -- (prod series and chainname)

  foreach my $prodSeries (keys %{$select_ref->{prodOptions}}){
    push @{$self->{values}{prodOptions}}, $prodSeries;
    $self->{labels}{prodOptions}{$prodSeries} = $prodSeries;
    
    foreach my $chainName ( @{$select_ref->{prodOptions}{$prodSeries}} ){
      my $value = "$prodSeries;$chainName";
      push @{$self->{values}{prodOptions}}, $value;
      $self->{labels}{prodOptions}{$value} = "$prodSeries - $chainName";
    }
  }
  # -- runID -- 
  push @{$self->{values}{runID}}, @{$select_ref->{runID}};

  # -- QA status -- (errors, warnings, ok)
  my @macro_names = @{$select_ref->{macroName}};
 
  $self->FillQAStatusMenu(@macro_names);
  
  # -- dataset --
  push @{$self->{values}{dataset}}, @{$select_ref->{dataset}};
    
  # -- job status -- 
  $self->FillJobStatusMenu();

  # -- job create time --
  $self->FillJobCreateTimeMenu();

  # -- qa done time --
  $self->FillQADoneTimeMenu();

  # set defaults.  unless otherwise stated, default is 'any'
  $self->{defaults}{QAstatus}  = 'done';
  $self->{defaults}{QAdoneTime} = 'seven_days';

  my $submit_string = br.$gCGIquery->submit('Display datasets');

  #--- 
  # pmj 21/6/00: more compact display, no header. Pulldown menu for changing classes
  # has been moved to banner so there is more horizontal space

  my $null_string = "";

  my @rows =
    (
     td([$self->GetRowOfMenus('prodOptions',
			      'jobStatus',
			      'QAstatus',
			      'dataset')
	]),
     
     td([$self->GetRowOfMenus(
			      'runID',
			      'createTime',
			      'QAdoneTime'
			      ) 
	                       
	                       ,$submit_string
	])
    );
  
  #---
  #my $table_string = 
  #    table({-align=>'center'}, Tr({-valign=>'top'}, \@table_rows));
  
  my $script_name   = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $select_data_string =
      $gCGIquery->startform(-action=>"$script_name/upper_display",
			-TARGET=>"list").
	table({-align=>'left'}, Tr({-valign=>'top'}, \@rows  )).
	   $hidden_string.
	    $gCGIquery->endform;
	      
  return $select_data_string;

}
#========================================================
# get the selected parameters chose by the user
# returns an array of cgi values according to the popup menu
# the order of the select_fields is important for database query.

sub SelectedParameters{
  my $self = shift;

  return map { $gCGIquery->param($_) } @{$self->{select_fields}};

}


1;
