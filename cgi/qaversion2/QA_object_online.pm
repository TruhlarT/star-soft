#! /usr/bin/perl
#
# derived QA_object for online_raw?
# bum 000623 
#
#==============================================================================
package QA_object_online;
#==============================================================================
use CGI qw(:standard :html3);
use QA_globals;
use IO_object;
use QA_db_utilities;
use Logreport_object_online;

use base qw(QA_object);

use strict;        
1;                  
#------------------------------------------------------------------------------
# use base class's constructor
#
sub new{
  my $class = shift;
  my $self  = $class->SUPER::new(@_);
  return $self;
}
#----------
# override the _init sub in SUPER?
#
#sub _init{
#  my $self       = shift;
#  my $report_key = shift;
#  my $action     = shift if @_; # update?
#}
  
#----------
# is it on disk?  should be...
#
sub InitOnDisk{
  my $self = shift;

  $self->OnDisk(1);
 
}
#----------
# what does the control file look like
#
sub InitControlFile{
  my $self = shift;

  $self->{_IOControlFile} =
    new IO_object("ControlFileOnline", $self);

}
#----------
# (first column)
#
sub DataDisplayString{
  my $self = shift;

  my $report_key = $self->ReportKey . br .br if $gBrowser_object->ExpertPageFlag;

  return $report_key .
         "Run ID : " . $self->LogReport->RunID ;
}
#----------
# create the log report obj
#
sub NewLogReportObject{
  my $self = shift;

  return Logreport_object_online->new($self->ReportKey);

}

