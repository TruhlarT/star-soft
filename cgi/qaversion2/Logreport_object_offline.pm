#! /opt/star/bin/perl
#
# derived Logreport_object for offline 
# this is a kluge.
# contains both information for offline real and offline MC
# the difference is controlled by the global DataClass object
# which determines which _initplus to call
# oh well.  
# 
#==========================================================
package Logreport_object_offline;
#==========================================================
use CGI qw/:standard :html3/;
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
	        _FileSeq          => undef,
	        _ProdSeries       => undef,
	        _ChainName        => undef, # abbrev of the chain
	        _EventGenDetails  => undef, # more info on the generator
	        _CollisionType    => undef, # e.g. auau200
	        _Dataset          => undef,
	        _Redone           => undef,
	        _FirstEventDone   => undef, # used for offline real...
		_LastEventDone    => undef # used for offline real...
	      );

#=========================================================
# 
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_) or return;  

  defined $self or return; # get out if something went wrong

  $classname eq __PACKAGE__ and 
    die __PACKAGE__, " is virtual";

  if (defined %members){
    # using SUPER::AUTOLOAD
    foreach my $element (keys %members) {
      $self->{_permitted}->{$element} = $members{$element};
    }
    # more members
    @{$self}{keys %members} = values %members;
  }

  $self->_init_offline();
 
  return $self;
}

#----------
sub _init_offline{
  my $self = shift;

  # runID, file seq, dataset
  $self->RunID(QA_db_utilities::GetFromFileCatalog('runID',$self->JobID) );
  $self->FileSeq(QA_db_utilities::GetFromFileCatalog('fileSeq',$self->JobID));
  $self->Dataset(QA_db_utilities::GetFromFileCatalog('dataset',$self->JobID));
  $self->Redone(QA_db_utilities::GetFromFileCatalog('redone',$self->JobID));

  # get prod series, chain name, lib version, and chain options
  
#  my ($prodSeries, $chainName, $lib, $chain) 
#    = QA_db_utilities::GetProdOptions($self->JobID);
  
  $self->ProdSeries(QA_db_utilities::GetFromJobStatus('prodSeries',$self->JobID));
  $self->ChainName("?");
  $self->StarlibVersion($self->StarLevel());
  #$self->RequestedChain($chain);

}
  
#----------
# get the log file - called in SUPER::_init

sub GetLogFile{
  my $self  = shift;

  return QA_db_utilities::GetOfflineLogFile( $self->JobID );
}

#----------
# parse the summary of the log file
# also parses the separate error file which contains
# the StError and StWarning info among other things

sub ParseLogfile{
  my $self = shift;

  my $logfile = $self->LogfileName; # found in SUPER::_init

  # change the logfile to the summary of the log file

  my $fh = FileHandle->new($logfile,"r");
  if(!defined $fh){
    print "Cannot find the log file $logfile<br>\n";
    $logfile =~ s|/log/|/log_old/|;
    print "Will try parsing the logfile: $logfile<br>\n";
    $fh = FileHandle->new($logfile,"r") or do{
      print "I give up. Cannot find $logfile :$!<br>\n";
      return;
      };
  }
  print "Found logfile $logfile<br>\n";

  # read the log file 
  my $startoptions=0;
  while (defined (my $line = $fh->getline )) {

    # start time  
    if ($line =~ /Starting job execution at (.*?)on/){
      my $value=$1;
      $self->JobStartTimeAndDate($value);
      next;
    }

    # star level and root level
    if ($line =~ /STAR_LEVEL\s+:\s+(\w+),.*?:\s+([\d\.]+)/) {
      my $star=$1; my $root=$2;
      $self->StarLevel($star); $self->RootLevel($root);
      next;
    }
			
    # requested chain
    if(!$startoptions and $line =~ /Requested chain bfc is\s+:\s+([^\.]+)/){
      my $value = $1; $self->RequestedChain($value);
      next;
    }

    # run options ++ 
    if($line =~ /StMessageManager message summary/ ){ 
      $startoptions=1;
      next;
    }
    if($startoptions and $line=~ /^QAInfo:\s+==/){
      $line =~ s/QAInfo://;
      my $opt = $self->RunOptions;
      if(!$opt){ $self->RunOptions("\n");}
      else { $self->RunOptions($opt.$line); }
      next;
    }
    if($startoptions and $line !~ /^QAInfo:/){
      $startoptions=0;
      next;
    }
      
    # first and last event requested 
    # only good for offline MC
    # offline real overwrites these with undef

    if ($line =~ /^QAInfo:\s*Process/){
      $line =~ /First=\s+(\d+)\/Last=\s+(\d+)\/Total=\s+(\d+)/;
      my $first=$1; my $last=$2; my $n=$3;
      $self->FirstEventRequested($first);
      $self->LastEventRequested($last);
      $self->NEventRequested($n);
      next;
    }

    # error string 
    if ($line =~ /Extra error message\W+(.*)/){
      $self->ErrorString($1); next;
    }

    # timing string - more than one line
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
  }
  
  # deduce the error file
  (my $errorfile = $logfile) =~ s/log$/err/;

  my $fh_error  = FileHandle->new($errorfile, "r");

  if (defined $fh_error)
  {
    # init StWarning and StError files
    my $io_warn = new IO_object("StWarningFile",$self->ReportKey);
    my $io_err  = new IO_object("StErrorFile",$self->ReportKey);
    
    my $FH_WARN  = $io_warn->Open(">", "0664");
    my $FH_ERR   = $io_err->Open(">", "0664");
 
    # print to StError and StWarning file
    if($FH_WARN and $FH_ERR){
      while( my $line = <$fh_error> ){
	print $FH_ERR  $line if $line =~ /StError:/;
	print $FH_WARN $line if $line =~ /StWarning:/;
	
      }
      close $FH_ERR; close $FH_WARN;
    } 
  }
  return 1;
}
#----------
# gets some info about the job from the db

sub GetJobInfo{
  my $self = shift;

  # -- get from JobsStatus
  my @jobFields = ('nodeID', 'NoEvents', 'jobStatus', 'NoEventSkip');

  my ($node, $eventsDone, $jobStatus, $Nskip) =
    QA_db_utilities::GetFromJobStatus(\@jobFields,$self->JobID);
  
  $self->Machine($node);
  $self->NEventDone($eventsDone);
  $self->JobStatus($jobStatus);
  $self->NoEventSkipped($Nskip);  

  # input fn
  my $input = QA_db_utilities::GetInputFnOffline($self->JobID);
  $self->InputFn($input);

  # output directory
  my $path = 
    QA_db_utilities::GetFromFileOnDiskOffline('path',$self->JobID);
  $self->OutputDirectory($path);
  
  # job completion time
  my $donetime = QA_db_utilities::GetFromFileCatalog('createTime',$self->JobID);
  $self->JobCompletionTimeAndDate($donetime);

  # all output files
  my @files = 
    QA_db_utilities::GetFromFileOnDiskOffline('fname', $self->JobID);

  @files = map{ $self->OutputDirectory . "/$_" } @files;
  $self->ProductionFileListRef(\@files);

  $self->MissingFiles( $self->GetMissingFiles($self->JobID) );

  # backwards compatibility
  $self->{_SmallFiles} = QA_db_utilities::GetSmallFilesOffline($self->JobID);
  
  return 1;
}
1;
#===========================================================
#
# offline_MC
#
package Logreport_object_offline_MC;
use base qw(Logreport_object_offline);

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  
  #bless($self,$classname);
  defined $self or return;

  $self->offline_MC();

  return $self;
}
#----------

sub GetMissingFiles{
  my $self  =  shift;
  my $jobID =  shift;

  return QA_db_utilities::GetMissingFiles($jobID,1,1);

}

#----------
# additional init for offline MC

sub offline_MC{
  my $self = shift;

  # parse the dataset column

  my ($collisionType, $eventGen, $details, $eventType, $geometry, $junk)=
    split /\//, $self->Dataset, 6;

  $self->CollisionType($collisionType);
  $self->EventGen($eventGen);
  $self->EventGenDetails($details);
  $self->EventType($eventType);
  $self->Geometry($geometry);

}

1;
#=============================================================
#
# offline_real
#

package Logreport_object_offline_real;
use base qw(Logreport_object_offline);

sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);  
  #bless($self,$classname);
  defined $self or return;

  $self->offline_real();

  return $self;
}

#----------

sub GetMissingFiles{
  my $self  =  shift;
  my $jobID =  shift;

  return QA_db_utilities::GetMissingFiles($jobID,0,1);

}

#----------
# additional init for offline real

sub offline_real{
  
  my $self = shift;
  
  # first and last event done (processed)
  my $lo = QA_db_utilities::GetFromFileCatalog('NevLo',$self->JobID);
  my $hi = QA_db_utilities::GetFromFileCatalog('NevHi', $self->JobID);

  $self->FirstEventDone($lo);
  $self->LastEventDone($hi); 

  # kill the NEventRequested field
  # this doesnt make sense for offline real data
  
  $self->NEventRequested(undef);

  # parse the dataset column
  
}

1;
