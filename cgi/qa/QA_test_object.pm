#! /usr/bin/perl -w

#=========================================================
package QA_test_object;
#=========================================================

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

# for ensuring that hash elements delivered in insertion order (See Perl Cookbook 5.6)
use Tie::IxHash;

#=========================================================
1.;
#=========================================================
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
  #-------------------------------------------------
}
#========================================================
sub Comment{
  my $self = shift;
  
  if (@_) {
    $line = shift;
    $self->{comment} or $line = "\n".$line;
    $self->{comment} .= $line;
  }
  
  return $self->{comment};
}
#========================================================
sub TestStringList{
  
  my $self = shift;
  
  if (@_) {
    push @{$self->{test_string}}, shift;
  }

  return @{$self->{test_string}};
}

