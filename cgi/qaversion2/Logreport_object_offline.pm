#! /usr/bin/perl
#
# derived Logreport_object for offline 
# this is a kludge.
# contains both information for offline real and offline MC
# the difference is controlled by the global DataClass object
# which determines which _initplus to call
# oh well.  
# 
#==========================================================
package Logreport_object_offline;
#==========================================================
use QA_globals;
use FileHandle;
use QA_db_utilities;
use Data::Dumper;

use strict;
use base qw(Logreport_object); # base class
#==========================================================
# more members

my %members = (
	        _RunID            => undef,     
	        _ProdSeries       => undef,
	        _ChainName        => undef, # abbrev of the chain
	        _EventGenDetails  => undef, # more info on the generator
	        _CollisionType    => undef  # e.g. auau200
	      );

#==========================================================
# 
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  

  defined $self or return; # get out if something went wrong

  if (defined %members){
    # using SUPER::AUTOLOAD
    foreach my $element (keys %members) {
      $self->{_permitted}->{$element} = $members{$element};
    }
    # more members
    @{$self}{keys %members} = values %members;
  }

  # ---
  # runID ?
  my $runID = QA_db_utilities::GetRunID($self->JobID);
  $self->RunID($runID);

  # get prod series, chain name, lib version, and chain options
  
  my ($prodSeries, $chainName, $lib, $chain) 
    = QA_db_utilities::GetProdOptions($self->JobID);
  
  $self->ProdSeries($prodSeries);
  $self->ChainName($chainName);
  $self->StarlibVersion($lib);
  $self->RequestedChain($chain);

  # depend on the DataClass_object to detemine which init to call
  # DataClass should be 'offline_real' or 'offline_MC'

  my $init = $gDataClass_object->DataClass;

  $self->$init(); # more initialization

  return $self;
}
#===========================================================
# additional init for offline real

sub offline_real{
  
  my $self = shift;
  
  # first and last event done
  my ($lo, $hi) = QA_db_utilities::GetLoAndHiEvent($self->JobID);

  $self->FirstEventDone($lo);
  $self->LastEventDone($hi); 

  # kill the NEventRequested field
  # this doesnt make sense for offline real data
  
  $self->NEventRequested(undef);

  # parse the dataset column
  

}

#===========================================================
# additional init for offline MC

sub offline_MC{
  my $self = shift;

  # parse the dataset column

  my ($collision, $gen, $gen_details, $event_type, $geometry) = 
    QA_db_utilities::ParseDatasetMC($self->JobID);

  $self->CollisionType($collision);
  $self->EventGen($gen);
  $self->EventGenDetails($gen_details);
  $self->EventType($event_type);
  $self->Geometry($geometry);

}
  
#===========================================================
# get the log file - called in SUPER::_init

sub GetLogFile{
  my $self  = shift;

  return QA_db_utilities::GetOfflineLogFile( $self->JobID );
}
#===========================================================
# get all the production files

sub GetProductionFiles{
  my $self = shift;

  my $file_ref = 
    QA_db_utilities::GetAllProductionFilesOffline($self->JobID);

  $self->ProductionFileListRef($file_ref);
}
#===========================================================
# parse the summary of the log file

sub ParseLogfile{
  my $self = shift;

  my $logfile = $self->LogfileName; # found in SUPER::_init

  # open
  my $fh = FileHandle->new( $logfile, "r" )
    or die "Cannot open $logfile: $!";

  # read the log file (actually summary of the log file)
  
  while (defined (my $line = $fh->getline )) {

    # start time  
    if ($line =~ /Starting job execution at (.*?)on/){
      $self->{_JobStartTimeAndDate} = $1;
      next;
    }

    # star level - e.g. new
    if ($line =~ /STAR_LEVEL : (\w+)/ ) {
      $self->{_StarLevel} = $1; next;
    }

    # root level - e.g. 2.23.12
    if ($line =~ /ROOT_LEVEL : ([\d\.]+)/ ) {
      $self->{_RootLevel} =  $1; next;
    }
							  
    # run options - e.g. StDbT is ON - more than one line
    if ( $line =~ /^QAInfo: =====/ ){
      $line =~ s/QAInfo://;  # get rid of leading QAInfo
      my $run_option = $self->RunOptions;
      if ( not $run_option ){ $self->RunOptions("\n")}
      else { $self->RunOptions($run_option.$line) }
      next;
    }

    # first and last event requested 
    # only good for offline MC
    # offline real overwrites these with undef

    if ($line =~ /^QAInfo:\s*Process/){
      $line =~ /First=\s+(\d+)\/Last=\s+(\d+)\/Total=\s+(\d+)/;
      $self->{_FirstEventRequested} = $1;
      $self->{_LastEventRequested}  = $2;
      $self->{_NEventRequested} = $3;
      next;
    }

    # error string 
    if ($line =~ /Extra error message\W+(.*)/){
      $self->ErrorString($1); next;
    }

    # timing string - more than one line
    if ( $line =~/Real Time/ ){
      my $timing = $self->TimingString;
      $self->TimingString($timing.$line);
      next;
    }
  }
  
}
#=============================================================
# gets some info about the job from the db

sub GetJobInfo{
  my $self = shift;

  # node (machine)
  my $node = QA_db_utilities::GetNodeID($self->JobID);
  $self->Machine($node);

  # input fn
  my $input = QA_db_utilities::GetInputFnOffline($self->JobID);
  $self->InputFn($input);

  # number of events done (processed)
  my $events_done = QA_db_utilities::GetNEventDoneOffline($self->JobID);
  $self->NEventDone($events_done);

  # job status - done, not completed, etc
  my $jobstatus = QA_db_utilities::GetJobStatus($self->JobID);
  $self->JobStatus($jobstatus);

  # number of events skipped
  my $skip = QA_db_utilities::GetNoEventSkipped($self->JobID);
  $self->NoEventSkipped($skip);

  # output file name and directory
  my ($path, $name) = 
    QA_db_utilities::GetOutputFileOffline( $self->JobID );

  $self->OutputDirectory($path);
  $self->OutputFn($name);

  # job completion time
  my $donetime = QA_db_utilities::GetJobCompletionTime($self->JobID);
  $self->JobCompletionTimeAndDate($donetime);

}
1;
