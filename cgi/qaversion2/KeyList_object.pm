#! /usr/bin/perl
#
# Class that takes care of 
# 1. extracting the relevant keys from the db as chosen by the user
# 2. creating the popup menu
# 3. creating the relevant QA_objects when used from the browser
# 4. adding the messages
#
#========================================================
package KeyList_object;
#========================================================
use CGI qw/:standard :html3/;

use QA_globals;
use Storable;
use DataClass_object;

use strict;
#--------------------------------------------------------
1;
# for the reader's benefit
my %members = ( _SelectionRef       => undef,
		_SelectedKeyListRef => [],
		_KeyListRef         => [],
		_NKeys              => undef
		);
# there are also a bunch of members related to 
# the CGI forms... see the derived classes for details.

#========================================================
# used from browser

sub new{
  my $classname = shift;

  $classname eq __PACKAGE__ and 
    die __PACKAGE__, " should not be instantiated\n";

  my $self      = {};

  bless ($self, $classname);

  # initialize
  #$self->_init(@_);

  return $self;
}
#========================================================
sub _init{
  my $self = shift;
   
}
#========================================================
# get the possible values for various fields from the db
# for selecting a particular job.
# called in JobPopupMenu

sub GetSelectionOptions{
  my $self = shift;

  # uses the global DataClass_object to determine which 
  # sub to call depending on the data class
  no strict 'refs';

  my $sub_getselections = $gDataClass_object->GetSelectionOptions;

  return &$sub_getselections;

}
#========================================================
# popup menu for selecting jobs
# overridden

sub JobPopupMenu{
  my $self = shift;

}
#========================================================
# get the selected parameters chose by the user
# returns an array of cgi values according to the popup menu
# overridden

sub SelectedParameters{
  my $self = shift;
}

#========================================================
# retrieves the selected keys from the database
# according to the SelectedParameters

sub GetSelectedKeysFromDb{
  my $self = shift;

  # uses the global DataClass_object to determine the sub
  # to run depending on the data class
  no strict 'refs';

  my $sub_getselectedkeys = $gDataClass_object->GetSelectedKeys;

  return &$sub_getselectedkeys($self->SelectedParameters);
}

#========================================================
# returns a list of keys (jobs) according to the selection
# options selected by the client
# also makes the QA objects

sub GetSelectedKeyList{
  my $self = shift;

  # get the keys from QASummary table matching the selection query

  my @key_list = $self->GetSelectedKeysFromDb();

  # make the QA_objects
  QA_utilities::make_QA_objects(@key_list);

  # add them to the KeyList and sort them 
  $self->KeyList( $self->SortKeys(@key_list) );

  # pass on the selected key list as hidden values
  # in order to do qa on whole dataset

  $gCGIquery->param('selected_key_list', @key_list);


  return @key_list;
}



#=========================================================
# add the messages to the key list

sub AddMessagesToKeyList{
  my $self = shift;

  # this should be the selected report keys
  my @report_keys = $self->KeyList;

  # if key list is empty, return
  scalar @report_keys or return;

  # hash to contain all messages
  %QA_message_hash = ();

  # open message dir
  my $io_dir            = new IO_object("MessageDir");
  my $message_dir_local = $io_dir->Name;
  my $dh = $io_dir->Open();                     

  # add the keys

  # get global message keys (just the filenames with 'global' in message_dir)
  my @global_message_keys = grep {/global/} readdir $dh;
  close $dh;
  
  # get report message keys (map '.msg' to the report keys)
  my @report_message_keys = map {"$_.msg"} @report_keys;

  # retrieve them

  foreach my $message_key (@global_message_keys, @report_message_keys){
    my $message_file = "$message_dir_local/$message_key";
    if (-e $message_file){
      $QA_message_hash{$message_key} = retrieve($message_file)
	or warn "Cannot retrieve file $message_file:$! <br>";
    }
  }
  
  # add to the key list - should resort as well
  $self->AddKeys(keys %QA_message_hash);

  return $self->KeyList;
 
}
#==================================================================
# make a table row of popup menus
# uses ben's clever mapping technique
# returns an array

sub GetRowOfMenus{
  my $self          = shift;
  my @select_fields = @_;
 
  return map{
              b( $self->{select_labels}{$_} ).br.
	      $gCGIquery->popup_menu(
				     -name    => $_,
				     -values  => $self->{values}{$_},
				     -default => $self->{values}{$_}[$self->{defaults}{$_}],
				     -labels  => $self->{labels}{$_}
                                    )
	    } @select_fields ;
                    
}
  
#==================================================================
sub NKeys{
  
  my $self = shift;
  @_ and $self->{_NKeys} = shift;
  return $self->{_NKeys};
}
#=======================================================
# just the selected report keys
# not used

sub SelectedKeyList{
  my $self = shift;

  no strict 'refs';
  @_ and do{
    my @key_list = @_;
    $self->{_SelectedKeyListRef} = \@key_list;
  };
  return @{$self->{_SelectedKeyListRef}};
}
#=======================================================
# an array containing active keys
# used to include the messages keys as well

sub KeyList{

  my $self = shift;
  
  no strict 'refs';
  @_ and do{
    my @key_list = @_;
    $self->{_KeyListRef} = \@key_list;
  };

  return @{$self->{_KeyListRef}};
}
#=========================================================
# add keys to the key list;  resorts as well

sub AddKeys{
  my $self = shift;
  my @new_keys = @_ or return;


  my @keys = $self->KeyList();
  push @keys, @new_keys;

  my @key_list_sorted = $self->SortKeys(@keys);

  $self->KeyList(@key_list_sorted);
  $self->NKeys($#key_list_sorted);
}

#==========================================================
# resort the keys according  to creation time
# used when including the message objects

sub SortKeys{

  my $self = shift;
  my @keys = @_;

  return sort { QA_utilities::sort_time($b) <=> 
		QA_utilities::sort_time($a)      } @keys ;
}
  
#========================================================
# ref to the selection hash 

sub SelectionRef{
  return $_[0]->{_SelectionRef};
}


1;
