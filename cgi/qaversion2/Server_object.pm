#! /usr/bin/perl

# pmj 18/5/00

#========================================================
package Server_object;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;
use Cwd;

use Storable;
use Data::Dumper;
use QA_globals;

use Logreport_object;

use QA_cgi_utilities;
use QA_report_io;

use Server_utilities;
use DataClass_object;

use Data::Dumper;
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
  
  #BEN(6jun2000): get hostname from /bin/hostname because we can't see
  # $gCGIquery in batch mode
  my $hostname = `/bin/hostname`;
  chop $hostname;
  $self->ServerName($hostname);

  # offline
  if ( $self->ServerName eq "sol.star.bnl.gov" ||
       $self->ServerName =~ /rcas/){
    $self->ServerType("offline");
  } # online
  elsif ( $self->ServerName eq "onllinux1.star.bnl.gov" ){
    $self->ServerType("online");
  }
  else{
    $self->ServerType("Unknown");
  }

}
#===========================================================
sub ServerName{
  my $self = shift;
  @_ and $self->{_ServerName} = shift;
  return  $self->{_ServerName};
}
#===========================================================
sub ServerType{
  my $self = shift;
  @_ and $self->{_ServerType} = shift;
  return  $self->{_ServerType};
}
#===========================================================
sub DataClass{
  my $self = shift;
  @_ and $self->{_DataClass} = shift;
  return  $self->{_DataClass};
}
