#! /usr/bin/perl 
#
# derived QA_object for offline
#
#=============================================================================
package QA_object_nightly;
#=============================================================================
use CGI qw(:standard :html3);
use IO_object;
use QA_db_utilities;
use Logreport_object_nightly;

use base qw(QA_object);

use strict;
1;
#-----------------------------------------------------------------------------

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  

  return $self;
}

#-----------
# is it on disk?
#
sub InitOnDisk{
  my $self = shift;

  my $ondisk = QA_db_utilities::OnDiskNightly($self->LogReport->JobID);
  $self->OnDisk($ondisk);
 
}
#-----------
#
sub InitControlFile{
  my $self = shift;

  $self->{_IOControlFile} = 
    IO_object->new("ControlFileNightly", $self);
  
}
#-----------
# (first column)
# identifies the job/dataset in the browser  
#
sub DataDisplayString{
  my $self = shift;

  my $starlib_version = $self->LogReport->StarlibVersion;
  my $star_level      = $self->LogReport->StarLevel;
  
  return
    $self->ReportKey . br . br .
    "JobID : " . $self->JobID . br .
    "(STARLIB version: $starlib_version; STAR level: $star_level)";
      
    
  #my $input_filename = $self->LogReport->InputFn;

  # pmj 10/12/99
  # pmj 11/1/00 - simu file catalogue changed
  
  #$input_filename =~ s%/star/rcf/disk0/star/test/|/star/rcf/simu/%%;
  #$string .= "<br><font size=1>(input: $input_filename)</font>";

}

#----------
# create the log report object
#
sub NewLogReportObject{
  my $self = shift;

  return Logreport_object_nightly->new($self->ReportKey);
}
1;
