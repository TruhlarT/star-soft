#! /usr/bin/perl -w
#
# general object to contain logfile summary
#
# pmj 13/11/99
#
#=========================================================
package Logreport_object;
#=========================================================
use CGI qw/:standard :html3/;
use QA_globals;
use QA_db_utilities; 
use DataClass_object;

use strict;
use vars qw($AUTOLOAD);
#=========================================================
1.;
#=========================================================
# class members

my %members = ( _ReportKey           => undef, # identifies job for disk
		_JobID               => undef, # interface with db
		_qaID                => undef,
		_LogfileName         => undef, # full path of the log file
		_LogfileNameWWW      => undef, # do we need this?
		_StarLevel           => undef, 
		_RootLevel           => undef,
		_StarlibVersion      => undef,
		_RunOptions          => undef,
		_RequestedChain      => undef,
		_InputFn             => undef,
		_FirstEventRequested => undef,
		_LastEventRequested  => undef,
		_NEventRequested     => undef,
		_NEventDone          => undef, # really processed
		_FirstEventDone      => undef, # used for offline real...
		_LastEventDone       => undef, # used for offline real...
		_NoEventSkipped      => undef, # not written to dst
		_OutputFn            => undef, 
		_JobStartTimeAndDate => undef,
		_JobCompletionTimeAndDate => undef,
		_Machine             => undef,
		_OutputDirectory     => undef,
		_ErrorString         => undef,
		_TimingString        => undef,
		_MissingString       => undef,
		_MissingFiles        => undef,
		_JobStatus           => undef,
		_WarningFile         => undef,
		_ErrorFile           => undef,
		_EventGen            => undef, #
	        _EventType           => undef, #
	        _Geometry            => undef, #
		_ProductionFileListRef => undef, # ref to an array
		_MemoryFile          => undef,
		_MemoryListRef       => undef, # ref to an array
		_IOStErrorFile       => undef,
		_IOStWarningFile     => undef  
	      );
#========================================================
sub new{
  my $classname = shift;

  # make sure Logreport_object is never created
  if ($classname eq __PACKAGE__ ){
    die __PACKAGE__," is a virtual class!";
  }

  my $self = { _permitted => \%members,
	        %members
	     };
  bless ($self, $classname);

  # initialize
  $self->_init(@_) or return;

  return $self;
}
#========================================================
sub _init{

  my $self = shift;
  my $report_key = shift;
 
  # diagnostic
  print h4("Making logfile report for $report_key...\n");

  # check for report key
  #
  defined $report_key or die __PACKAGE__, " needs a report key";

  # set the report key.
  #
  $self->ReportKey($report_key);
 
  # get and set the jobID
  #
  my $jobID = QA_db_utilities::GetJobID($report_key);
  defined $jobID or do{print h3("No jobID $jobID in db"); return};
  $self->JobID($jobID);

  # get and set the qaID
  #
  my $qaID = QA_db_utilities::GetQAID($report_key);
  $self->qaID($qaID);

  # get the log file
  my $logfile = $self->GetLogFile( );  
  $self->LogfileName($logfile);

  # init StWarning and StError files

  $self->IOStWarningFile(IO_object->new("StWarningFile",$report_key));
  $self->IOStErrorFile(IO_object->new("StErrorFile", $report_key));

  # parse the log file
  # returns an error if this doesnt exist
  #
  $self->ParseLogfile() or do{
    print h3("Error in Logreport_object constructor:\n ",
	     "logfile $logfile not found for $jobID ($report_key)\n");
    return;
  };

  # get additional job info from the db
  #
  $self->GetJobInfo();
  
  # check for missing files - depends on the dataclass (real or MC)
  #
  no strict 'refs';

  my $sub_missing_files = $gDataClass_object->GetMissingFiles;
  $self->MissingFiles( &$sub_missing_files($jobID) );

  # get the production output files
  #
  $self->GetProductionFiles;
}
#=================================================================
# copied from perl toot
# automatically makes accessors 
# for 'permitted' members if they dont already exist

sub AUTOLOAD {
  my $self = shift;
  my $type = ref($self)
    or die "$self is not an object";

  my $name = $AUTOLOAD;
  $name =~ s/.*://;   # strip fully-qualified portion

  return if $name eq 'DESTROY'; 
  exists $self->{_permitted}->{"_$name"}  or
    die "Can't access `$name' field in class $type\n";

  # create accessor
  no strict;

  *{$name} = sub {
    my $self = shift;;
    $self->{"_$name"} = shift if @_;
    return $self->{"_$name"};
  };
  $self->{"_$name"} = shift if @_;
    return $self->{"_$name"};
}
#========================================================
# get the log file.  overridden in the derived classes

sub GetLogFile{
  my $self  = shift;

  return;
}  
#========================================================
# this method gets overriden

sub ParseLogfile {

  my $self = shift;
  
  return;
}
#=========================================================
# get production files
# overriddne

sub GetProductionFiles{
  my $self = shift;
}
#=========================================================
sub LogfileSummaryString {
  my $self = shift;

  # error if we couldnt arbitrarily 
  # get the Starlevel or the star lib version
  unless ($self->StarLevel or $self->StarlibVersion) {
    return "Log file could not be parsed";
  }

  my $return_string;

  # how's the job status?
  if ($self->JobStatus =~ /^[Dd]one/)
  {
    $return_string .= "Run completed;".br.br;
  } 
  else 
  {
    $return_string .= font({-color=>'red'},$self->JobStatus).br.br;
    $self->{_ErrorString} and 
      $return_string .= $self->ErrorString.br; 
  }

  # how many events done (processed)?

  $return_string .= "$self->{_NEventDone} evts ".br."processed".br.br;
  
  # any events skipped?

  $self->NoEventSkipped and
    $return_string .= font({-color=>'red'},$self->NoEventSkipped," evts").br.
                      font({-color=>'red'},"not completed").br.br;

  # 2 possibilities
  # for real production, there's no events requested.
  # this is will show up as _NEventRequested being undef.
  # for everything else _NEventRequested makes sense

  if ($self->NEventRequested){
    $return_string .= 
      "(evts requested:".br.
      "$self->{_FirstEventRequested}-$self->{_LastEventRequested})".br;
  }
  else{
    $return_string .=
      "(evts processed:".br.
      "$self->{_FirstEventDone}-$self->{_LastEventDone})".br;
  }

  # missing files?
  $self->MissingFiles and $return_string .= br.
    "missing files: ".br.
    font({-color=>'red'}, $self->MissingFiles);
  
  return $return_string;

}
#=========================================================
# 'Run details' button
sub DisplayLogReport {
  
  my $self = shift;

  my $divider = "*" x 100 . "\n";
  my $var;

 
  print qq{
    $divider 
    <br> Report for logfile $self->{_LogfileName} <br> 
    $divider
    <br>
    <pre>
    STAR Level = $self->{_StarLevel}
    ROOT Level = $self->{_RootLevel}
    STARLIB version = $self->{_StarlibVersion}<br>
    Chain = $self->{_RequestedChain}
    Input filename = $self->{_InputFn} 
    Output directory = $self->{_OutputDirectory} 
    Output filename = $self->{_OutputFn}
    Start date/time = $self->{_JobStartTimeAndDate} 
    Nevents requested = $self->{_NEventRequested}
    First event requested = $self->{_FirstEventRequested}
    Last event requested = $self->{_LastEventRequested}
    Nevents processed = $self->{_NEventDone}
    Finish date/time = $self->{_JobCompletionTimeAndDate}
    Machine name = $self->{_Machine}
    Job status = $self->{_JobStatus}
  };
  # error?
  defined ($self->{_ErrorString}) and
    print "Error found: $self->{_ErrorString}\n";

  # run options
  print "$divider Run options = $self->{_RunOptions}\n";

  # final timing
  $self->{_JobStatus} =~ /^[dD]one/ and  
    print "$divider Final timing $self->{_TimingString}\n";

  print "$divider </pre>\n";

}
1;
