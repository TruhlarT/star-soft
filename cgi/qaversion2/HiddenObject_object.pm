#! /usr/bin/perl

# class to hide objects between invocations of cgi script
# used to be handled by QA_utilities::hidden_field_string

# pmj 23/5/00

#========================================================
package HiddenObject_object;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Storable;
use Data::Dumper;
use QA_globals;

use QA_cgi_utilities;

use IO_utilities;
use IO_object;

use strict;
#--------------------------------------------------------
1;
#========================================================
sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  return $self;
}
#========================================================
sub _init{

  my $self = shift;

  #---------------------------------------------------------
  # initialize some flags

  $self->NewQAObject(0);
  $self->NewButtonObject(0);
  $self->NewMessage(0);

  #---------------------------------------------------------
  # delete the scratch file if switching directories
  # or selecting on datasets

  $gCGIquery->delete('save_object_hash_scratch_file') if
    (defined $gCGIquery->param('Change Class') or
     defined $gCGIquery->param('Display datasets'));
  
  IO_utilities::CleanUpScratch();
  $self->Retrieve();

}
#==============================================================
sub Retrieve{

  # retrieve objects from scratch file if it exists, otherwise initiate new one

  my $self = shift;

  #----------------------------------------------------------------

  my $scratch_file = $gCGIquery->param('save_object_hash_scratch_file');
  
  if (-e $scratch_file) {

#    print h2("Retrieve $scratch_file");

    my %Save_object_hash = %{retrieve($scratch_file)};
    
    %QA_object_hash = %{$Save_object_hash{QA_object_hash}};
    %Button_object_hash = %{$Save_object_hash{Button_object_hash}};
    %QA_message_hash = %{$Save_object_hash{QA_message_hash}};
    
    }
  else {
    
    %QA_object_hash = (); %Button_object_hash = (); %QA_message_hash = ();
    
    #---- 

    # generate unique file ID
    srand;
    my $id_string = int(rand(1000000)); 
    my $io = new IO_object("HiddenObjectFile", $id_string);
    my $scratch_file = $io->Name();
    undef $io;

    $gCGIquery->param('save_object_hash_scratch_file', $scratch_file);
    
  }
  
}

#===================================================================
# these are the hidden parameters to persist over invocation of script

sub Parameters{

  my $self = shift;
  
  my $string = $gCGIquery->hidden('selected_key_string').
    $gCGIquery->hidden('dataset_array_previous').
      $gCGIquery->hidden('selected_key_list').
	$gCGIquery->hidden('expert_pw').
	  $gCGIquery->hidden('display_env_var').
	    $gCGIquery->hidden('enable_add_edit_comments').
	      $gCGIquery->hidden('save_object_hash_scratch_file').
		$gCGIquery->hidden('data_class');

  return $string;
}
#===================================================================
# store persistent hashes

sub Store{
  my $self = shift;

  #------------------------------------------------------------  
  # store persistent hashes if this hasn't been done since script was
  # invoked or a new object has been created
  
  my $scratch_file = $gCGIquery->param('save_object_hash_scratch_file');
  
  # for testing
  #  $self->print_traceback_hidden($scratch_file);
  #------------------------------------------------------------  
 SAVEOBJECTS: {
    
    ( (-s $scratch_file) and 
      ($self->NewQAObject() == 0) and 
      ($self->NewButtonObject() == 0) and 
      ($self->NewMessage() == 0) ) and last SAVEOBJECTS;
    
    #    print "Printing temp file $scratch_file <br> \n";
    #    print h2("STORE $scratch_file<br>");
    
    #foreach my $key (%QA_object_hash){
    #  print "QA objects: $key<br>\n";
    #}

    #foreach my $key (%Button_object_hash){
    #  print "Button objects: $key<br>\n";
    #}
    
    #foreach my $key (%QA_message_hash){
    #  print "Message objects: $key<br>\n";
    #}
    

    my %Save_object_hash;
    $Save_object_hash{QA_object_hash} = \%QA_object_hash;
    $Save_object_hash{Button_object_hash} = \%Button_object_hash;
    $Save_object_hash{QA_message_hash} = \%QA_message_hash;
    
    store(\%Save_object_hash, $scratch_file ) or 
      print "<h4> HiddenObject_object::Store: Cannot write $scratch_file: $! </h4> \n";
  };

}
#======================================================================='
sub NewQAObject{
  my $self = shift;
  @_ and $self->{_NewQAObject} = shift;
  return  $self->{_NewQAObject};
}
#======================================================================='
sub NewButtonObject{
  my $self = shift;
  @_ and $self->{_NewButtonObject} = shift;
  return  $self->{_NewButtonObject};
}
#======================================================================='
sub NewMessage{
  my $self = shift;
  @_ and $self->{_NewMessage} = shift;
  return  $self->{_NewMessage};
}
#=======================================================================
sub print_traceback_hidden{

  # for debugging

  my $self = shift;
  my $save_filename = shift;

  print "=" x 80, "\n<br> print_traceback_hidden called <br> \n";

  my $i = 0;
  while (my ($package, $filename, $line, $sub, $hasargs, $wantarray) = caller($i++) ){
    print "from $package::$filename, line $line, subroutine $sub <br> \n";
  }

  if ( -e $save_filename ){
    print "$save_filename exists <br> \n";
  }
  else{
    print "$save_filename doesnt exist <br> \n";
  }
  
  print "new QaObj: ",$self->NewQAObject(),
  " new ButtonObj: ",$self->NewButtonObject(),
  " new Message: ",$self->NewMessage()," <br> \n";

  print "=" x 80, "<br> \n";

}

1;
