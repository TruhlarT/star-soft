#! /opt/star/bin/perl
#
# derived Logreport_object for nightly tests
#
#==========================================================
package Logreport_object_nightly;
#==========================================================
use CGI qw/:standard :html3/;

#use IO_object;
use QA_globals;
use QA_db_utilities;
use FileHandle;

use strict;
use base qw(Logreport_object); 
#=======================================================o===
# more members

my %members = (
	       _EventGen            => undef, #  
	       _EventType           => undef, # 
	       _Geometry            => undef  # 
	      );

#==========================================================
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_) or return;  

  $classname eq __PACKAGE__ and 
    die __PACKAGE__, " is virtual";

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
# 
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
  my $fh = FileHandle->new( $self->LogfileName(), "r" ) or 
    do{
      print "Trouble opening file = ", $self->LogfileName(), " $!\n";
      return;
    };
  print "Found logfile ", $self->LogfileName(), "\n", br;

  # init StWarning and StError files
  my $io_warn = new IO_object("StWarningFile",$self->ReportKey);
  my $io_err  = new IO_object("StErrorFile",$self->ReportKey);

  my $FH_WARN  = $io_warn->Open(">", "0664");
  my $FH_ERR   = $io_err->Open(">", "0664");

  my ($record_run_options);
  # read the log file
  while (defined (my $line = $fh->getline )) {

    if($line =~ /StMessageManager message summary/ ){ 
      $record_run_options=1;
      next;
    }

    if($record_run_options and $line !~ /^QAInfo:/){
      $record_run_options=0;
      next;
    }

    next unless $line =~ /^QAInfo:|^StWarning:|^StError/;
     
    # get input file name
    $line =~ /Input file name = (\S+)/ and do {
      my $value=$1;
      $self->InputFn($value); # dont know why..
      next;
    };
        
    # run start time
    $line =~ /Run is started at Date\/Time ([0-9\/]+)/ and do {
      my $datetime = QA_utilities::convert_logdatetime($1);
      $self->JobStartTimeAndDate($datetime);
      next;
    };

    # runopts
    if($record_run_options and $line=~ /^QAInfo:\s+==/){
      $line =~ s/QAInfo://;
      my $opt = $self->RunOptions;
      if(!$opt){ $self->RunOptions("\n");}
      else { $self->RunOptions($opt.$line); }
      next;
    }
    
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
    print $FH_ERR $line  if ($line =~ /^StError:/ and $FH_ERR);

    # StWarning ?    
    print $FH_WARN $line if ($line =~ /^StWarning:/ and $FH_WARN);
  }

  undef $io_err; undef $io_warn;
  
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
  
  # output directory
  my $path = 
    QA_db_utilities::GetFromFileOnDiskNightly('path',$self->JobID);
  $self->OutputDirectory($path);
  
  # all the output files
  my @files = 
    QA_db_utilities::GetFromFileOnDiskNightly('fname', $self->JobID);

  @files = map{ $self->OutputDirectory . "/$_" } @files;
  $self->ProductionFileListRef(\@files);

  $self->MissingFiles( $self->GetMissingFiles($self->JobID) );

  $self->{_SmallFiles} = QA_db_utilities::GetSmallFilesNightly($self->JobID);
  1;
}  
1;
#===========================================================
#
# nightly_MC
#
package Logreport_object_nightly_MC;
use base qw(Logreport_object_nightly);

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  
  #bless($self,$classname);
  defined $self or return;
  return $self;
}

#----------

sub GetMissingFiles{
  my $self  =  shift;
  my $jobID =  shift;

  return QA_db_utilities::GetMissingFiles($jobID,1,0);

}


1;
#=============================================================
#
# nightly_real
#

package Logreport_object_nightly_real;
use base qw(Logreport_object_nightly);

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  
  #bless($self,$classname);
  defined $self or return;

  return $self;
}

#----------

sub GetMissingFiles{
  my $self  =  shift;
  my $jobID =  shift;

  return QA_db_utilities::GetMissingFiles($jobID,0,0);

}

1;
