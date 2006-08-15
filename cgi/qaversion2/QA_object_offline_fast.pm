#! /opt/star/bin/perl 
#
# derived QA_object for offline
#
#=============================================================================
package QA_object_offline_fast;
#=============================================================================
use CGI qw(:standard :html3);
use IO_object;
use QA_globals;
use QA_db_utilities;
use Logreport_object_offline_fast;
use lib "/afs/rhic.bnl.gov/star/packages/scripts"; # RunDaq.pm lives here
use RunDAQ;

use base qw(QA_object);

use strict;
1;
#-----------------------------------------------------------------------------

sub new{
  my $proto = shift;
  my $classname = ref($proto) || $proto;

  my $self = $classname->SUPER::new(@_);  
  #bless($self,$classname);

  return $self;
}

#-----------
# is it on disk?
#
sub InitOnDisk{
  my $self = shift;

  my $files = $self->LogReport->ProductionFileListRef();

  my $ondisk='N';
  foreach my $file (@$files) {
    if(-e $file) { $ondisk='Y'; last; }
  }
  $self->OnDisk($ondisk);
}
#-----------
#
sub InitControlFile{
  my $self = shift;

  $self->{_IOControlFile} = 
    IO_object->new("ControlFileOfflineFast", $self);
  
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
    $self->JobID . br .
    "collision: " . $self->LogReport->CollisionType() .br .
    "dataset: " . $self->LogReport->Dataset() . br .
    "current: " . $self->LogReport->Current() . br .
    "B scale: " . $self->LogReport->ScaleFactor(). br.
    "beam: " . $self->LogReport->BeamE() . br . "\n";
    #$self->LogReport->OutputDirectory .br.
    #"(STARLIB version: $starlib_version; STAR level: $star_level)\n";
      
    
}
#----------
# set the DAQInfo table that qa has been done
#
sub WrapUpQA{
  my $self=shift;

  print "Setting QA done for DAQInfo table<br>\n";
  my $hh = rdaq_open_odatabase();
  my $stat = rdaq_set_files($hh,3,$self->JobID());
  rdaq_close_odatabase($hh);
  if($stat) { print "...done. file=",$self->JobID(),"<br>\n"; }
  else { print "\tSomething went wrong with file ",$self->JobID(),"<br>\n";}

}


#----------
# create the log report object
#
sub NewLogReportObject{
  my $self = shift;

  return Logreport_object_offline_fast->new($self->ReportKey);
}
1;
