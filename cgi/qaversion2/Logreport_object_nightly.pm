#! /usr/bin/perl
#
# derived Logreport_object for nightly tests
#
#==========================================================
package Logreport_object_nightly;
#==========================================================
use CGI qw/:standard :html3/;

use QA_globals;
use QA_db_utilities;
use FileHandle;

use strict;
use base qw(Logreport_object); 
#==========================================================
# more members

my %members = ();

#==========================================================
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_) or return;  

  if (defined %members){
    # using SUPER::AUTOLOAD
    foreach my $element (keys %members) {    
      $self->{_permitted}->{$element} = $members{$element};
    }
    # add more members
    @{$self}{keys %members} = values %members;
  }

  
  $self->_initplus(); # additional intialization

  return $self;
}
#==========================================================
sub _initplus{ 

  my $self = shift;

  # trigger info for the control file

  my ($eventGen, $eventType, $geometry) = 
    QA_db_utilities::GetControlFileInfo( $self->JobID );
  
  $self->EventGen($eventGen);
  $self->EventType($eventType);
  $self->Geometry($geometry);

}
#==========================================================
# get the log file in SUPER::_init

sub GetLogFile{
  my $self  = shift;

  return QA_db_utilities::GetNightlyLogFile( $self->JobID );
}
#==========================================================
# get the production files

sub GetProductionFiles{
  my $self = shift;
  
  my $file_ref = 
    QA_db_utilities::GetAllProductionFilesNightly($self->JobID);
  $self->ProductionFileListRef($file_ref);
}

#=========================================================
# parse the logfile

sub ParseLogfile {
  my $self = shift;

  my $logfile = $self->LogfileName(); # found in SUPER::_init

  # open files
  my $fh       = FileHandle->new( $logfile, "r" ) or return;
  my $FH_WARN  = $self->IOStWarningFile->Open(">", "0664");
  my $FH_ERR   = $self->IOStErrorFile->Open(">", "0664");

  my ($record_run_options);
  # read the log file
  while (defined (my $line = $fh->getline )) {

    next unless $line =~ /^QAInfo:|^StWarning:|^StError/;
     
    # start recording of run options
    $line =~ /Requested chain/ and do{
      $record_run_options = 1;
      $self->RunOptions("\n");
      next;
    };
    
    # turn off recording of run options?
    $record_run_options and $line !~ /=======/ and $record_run_options = 0;
    
    # retrieve run options
    $record_run_options and do {
      $line =~ s/QAInfo://;
      $self->{_RunOptions} .= $line;
      next;
    };
    
    # get input file name
    $line =~ /Input file name = (\S+)/ and do {
      $self->{_InputFn} = $1; # dont know why..
      next;
    };
        
    # run start time
    $line =~ /Run is started at Date\/Time ([0-9\/]+)/ and do {
      my $datetime = QA_utilities::convert_logdatetime($1);
      $self->JobStartTimeAndDate($datetime);
      next;
    };
        
    # get timing strings
    $line !~ /Done with Event/ and $line =~ /Real Time =/ and do{
      $line =~ s/QAInfo://;
      my $divider = "*" x 100 . "\n";
      my $timing_string = $self->TimingString();
      ! defined($timing_string) and $timing_string = "\n";
      if ( $line =~ /bfc/ ){
	$timing_string .= $divider.$line.$divider;
      }
      else{
	$timing_string .= $line;
      }
      $self->TimingString($timing_string);

      next;
    };

    # StError ?
    print $FH_ERR $line  if $line =~ /^StError:/;

    # StWarning ?    
    print $FH_WARN $line if $line =~ /^StWarning:/;
  }

  close $FH_ERR;  close $FH_WARN;
  
  return 1;
}

#=========================================================
# get more info from the db

sub GetJobInfo{
  my $self = shift;

  my $jobID = $self->JobID;

  # get the starlib level - e.g. new
  # root level - e.g. 2.24
  # starlib version - e.g. DEV00
  # chain options
  
  my ($liblevel, $rootlevel, $starlib, $chain) =
    QA_db_utilities::GetStarRootInfo($jobID);

  $self->StarLevel($liblevel);
  $self->RootLevel($rootlevel);
  $self->StarlibVersion($starlib);
  $self->RequestedChain($chain);

  # node (machine)
  my $node = QA_db_utilities::GetFromJobStatus('nodeID',$jobID);
  $self->Machine($node);

  # number of event requested
  my $events = QA_db_utilities::GetFromFileCatalog('NoEventReq',$jobID);
  $self->NEventRequested($events);

  # the first event is always 1
  $self->FirstEventRequested(1);

  # num of events requested is the same as the last event requested
  $self->LastEventRequested($events);

  # number of events skipped
  my $skip = QA_db_utilities::GetFromJobStatus('NoEventSkip',$jobID);
  $self->NoEventSkipped($skip);

  # output file name and directory
  my ($path, $name) = 
    QA_db_utilities::GetOutputFileNightly( $jobID );

  $self->OutputDirectory($path);
  $self->OutputFn($name);
  
  # job completion time
  my $donetime = QA_db_utilities::GetFromFileCatalog('createTime',$jobID);
  $self->JobCompletionTimeAndDate($donetime);

  # number of events done
  my $events_done = QA_db_utilities::GetFromJobStatus('NoEventDone',$jobID);
  $self->NEventDone($events_done);

  # job status - done, not completed, etc
  my $jobstatus = QA_db_utilities::GetFromJobStatus('jobStatus',$jobID);
  $self->JobStatus($jobstatus);
  

}  
1;
