#! /usr/bin/perl
# pmj 22/12/99
#========================================================
package QA_message;
#========================================================
#use CGI qw/:standard :html3 -no_debug/;
use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;

use Storable;
use Data::Dumper;
use QA_globals;

use Logreport_object;

use QA_make_reports;
use QA_cgi_utilities;
use QA_report_io;

#--------------------------------------------------------
1;
#========================================================
sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  $new_Message_object = 1;

  return $self;
}
#========================================================
sub _init{

  my $self = shift;

  # if no directory supplied as argument, return
  return unless @_;
  
  # this argument can be production dir or report dir - check later
  my $message_key = shift;
  #------------------------------------------------------

  my $author = shift;
  $author or $author = "No author entered";

  # this is in epoch-seconds
  my $date = shift;
  $date or $date = time;

  my $text = shift;
  $text or $text = "No text entered";

  #------------------------------------------------------
  $self->MessageKey($message_key);

  $self->Author($author);
  $self->CreationEpochSec($date);
  $self->MessageString($text);
}
#========================================================
sub MessageKey{
  my $self = shift;

  @_ and do{
    $self->{message_key} = shift;
  };

  return $self->{message_key};
}
#========================================================
sub Author{
  my $self = shift;

  @_ and do{
    $self->{author} = shift;
  };

  return $self->{author};
}
#========================================================
sub CreationEpochSec{

  my $self = shift;

  @_ and do{
    $time = shift;
    $self->{CreationEpochSec} = $time;
  };

  return $self->{CreationEpochSec}
}
#========================================================
sub MessageString{
  my $self = shift;

  #--------------------------------------------------------
  @_ and do{
    $self->{message_string} = shift;
  };
  #--------------------------------------------------------
  return $self->{message_string};
}
