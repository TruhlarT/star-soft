#! /usr/bin/perl
#
# derived Logreport_object for nightly tests
#
#==========================================================
package Logreport_object_nightly;
#==========================================================
use CGI qw/:standard :html3/;

use IO_object;
use QA_globals;
use QA_db_utilities;
use FileHandle;

use strict;
use base qw(Logreport_object); 
#=======================================================o===
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
#
#----------
#
sub _initplus{ 

  my $self = shift;

  # trigger info, etc
  my @fields = ('eventGen', 'eventType', 'geometry');

  my ($evtgen, $evttype, $geom) =
    QA_db_utilities::GetFromFileCatalog(\@fields, $self->JobID);

  $self->EventGen($evtgen);
  $self->EventType($evttype);
  $self->Geometry($geom);

}
#
#----------
# get the log file in SUPER::_init
#
sub GetLogFile{
  my $self  = shift;

  return QA_db_utilities::GetNightlyLogFile( $self->JobID );
}
#
#----------
# parse the logfile
#
sub ParseLogfile {
  my $self = shift;

  # open files
  my $fh = FileHandle->new( $self->LogfileName(), "r" ) or return;
  
  print "Found logfile ", $self->LogfileName(), "\n", br;

  # init StWarning and StError files
  my $io_warn = new IO_object("StWarningFile",$self->ReportKey);
  my $io_err  = new IO_object("StErrorFile",$self->ReportKey);

  my $FH_WARN  = $io_warn->Open(">", "0664");
  my $FH_ERR   = $io_err->Open(">", "0664");

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
#
#----------
# get more info from the db
#
sub GetJobInfo{
  my $self = shift;

  my $jobID = $self->JobID;

  # info from the job status table
  
  my @jobFields = ('LibLevel', 'rootLevel',   'LibTag',      'chainOpt',
		   'nodeID',   'NoEventSkip', 'NoEventDone', 'jobStatus');

  my ($liblevel, $rootlevel, $starlib, $chain,
      $node, $Nskip, $eventsDone, $jobStatus ) =
    QA_db_utilities::GetFromJobStatus(\@jobFields, $jobID);

  $self->StarLevel($liblevel);
  $self->RootLevel($rootlevel);
  $self->StarlibVersion($starlib);
  $self->RequestedChain($chain);   
  $self->Machine($node);         
  $self->NoEventSkipped($Nskip);
  $self->NEventDone($eventsDone);
  $self->JobStatus($jobStatus);

  # info from the File Catalog
  my @fileFields = ('NoEventReq', 'createTime');

  my ($events, $createTime)  = 
      QA_db_utilities::GetFromFileCatalog(\@fileFields,$jobID);

  $self->NEventRequested($events);
  $self->FirstEventRequested(1);
  $self->LastEventRequested($events);
  $self->JobCompletionTimeAndDate($createTime);   
  
  # output file name and directory
  my ($path, $name) = 
    QA_db_utilities::GetOutputFileNightly( $jobID );

  $self->OutputDirectory($path);
  $self->OutputFn($name);
  
  
  # all the output files
  my $file_ref = 
    QA_db_utilities::GetAllProductionFilesNightly($self->JobID);
  $self->ProductionFileListRef($file_ref);

  # check for missing files.
  # depends on the data class - use global DataClass_object.
  # returns a string.
  
  no strict 'refs';
  my $sub_missing = $gDataClass_object->GetMissingFiles; # name of the sub
  $self->MissingFiles( &$sub_missing($self->JobID) );

  1;
}  
1;
