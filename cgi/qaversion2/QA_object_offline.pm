#! /usr/bin/perl b                
#
# derived QA_object for offline
#
#=============================================================================
package QA_object_offline;
#=============================================================================
use CGI qw(:standard :html3);
use IO_object;
use QA_db_utilities;
use QA_globals;
use Logreport_object_offline;

use base qw(QA_object);

use strict;
1;
#----------------------------------------------------------------------------

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  

  return $self;
}

#----------
# is it on disk?
#
sub InitOnDisk{
  my $self = shift;

  my $ondisk = QA_db_utilities::OnDiskOffline($self->LogReport->JobID);
  $self->OnDisk($ondisk);
}

#----------
#
sub InitControlFile{
  my $self = shift;

  $self->{_IOControlFile} = 
    IO_object->new("ControlFileOffline", $self);
 
}
#----------
# (first column)
# identifies the job/dataset in the browser  
#
sub DataDisplayString{
  my $self = shift;

  my $prodSeries = $self->LogReport->ProdSeries;
  my $chainName  = $self->LogReport->ChainName;
  
  my $report_key_string = $self->ReportKey . br . br
    if $gBrowser_object->ExpertPageFlag;

  return $report_key_string .
         "JobID : " . $self->LogReport->JobID . br.
	 "RunID : " . $self->LogReport->RunID . br.
	 "Dataset : " . $self->LogReport->Dataset . br .	   
         "(prodSeries: $prodSeries; chain name: $chainName)";
}


#----------
# create the log report object
#
sub NewLogReportObject{
  my $self = shift;

  return Logreport_object_offline->new($self->ReportKey);
}
1;
