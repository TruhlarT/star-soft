#! /usr/bin/perl -w
#
# general object to retrieve basic information about the job.
# the information is gathered from 
# 1. logfile
# 2. mysql database
# beware: the derived objects should override several methods.
# this class should never be instantiated
#
# pmj 13/11/99 
#
#=========================================================
package Logreport_object;
#=========================================================
use CGI qw/:standard :html3/;
use QA_globals;
use QA_db_utilities qw(:db_globals); 
use Data::Dumper;

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
		_NoEventSkipped      => undef, # not written to dst
		_OutputFn            => undef, 
		_JobStartTimeAndDate => undef,
		_JobCompletionTimeAndDate => undef,
		_Machine             => undef,
		_OutputDirectory     => undef,
		_ErrorString         => undef,
		_TimingString        => undef,
		_MissingFiles        => undef,
		_SmallFiles          => undef,
		_JobStatus           => undef,
		_WarningFile         => undef,
		_ErrorFile           => undef,
		_ProductionFileListRef => undef, # ref to an array
		_MemoryFile          => undef,
		_MemoryListRef       => undef, # ref to an array
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
  $self->_init(@_) or do{
    print h3("Error in Logreport_object constructor:\n ",
	     $self->ReportKey,"\n");
    return;
  };

  return $self;
}
#----------
#
sub _init{

  my $self       = shift;
  my $report_key = shift;
 
  # check for report key
  defined $report_key or die __PACKAGE__, " needs a report key";

  print h4("Making logfile report for $report_key...\n");
  
  # get and set some members
  $self->ReportKey($report_key);
 
  # initialize the IDs from the db
  $self->InitIDs() or do{
    print "Cannot initialize ids in db\n";
    return;
  };
  # get the log file
  my $logfile = $self->GetLogFile();  
  $self->LogfileName($logfile);

  # parse the log file
  # returns an error if this doesnt exist
  
  print "Parsing logfile...\n", br;
  $self->ParseLogfile() or return;
  print "...done\n" , br;

  # get additional job info from the db
  #
  print "Getting info from db...\n" , br;
  $self->GetJobInfo() or return;;
  print "...done\n" , br;
  
  return 1;
}
#----------
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
#----------
# the only reason i put this in a separate method is
# because online reco (dst) doesnt need the jobID.

sub InitIDs{
  my $self = shift;

  $self->JobID( QA_db_utilities::GetFromQASum($QASum{jobID},$self->ReportKey) );
  $self->qaID(  QA_db_utilities::GetFromQASum($QASum{qaID},$self->ReportKey ) );
}
#----------
# get log file

sub GetLogFile{
  my $self = shift;;
}  
#----------
# this method gets overriden

sub ParseLogfile {
  my $self = shift;
}
#----------
# get additional info about the job from the db.
# overridden,

sub GetJobInfo{
  my $self = shift;
}
#----------
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
      $return_string .= "error code:" . br . $self->ErrorString.br.br; 
  }

  # how many events done (processed)?

  $return_string .= $self->NEventDone . " evts ".br."processed".br.br;
  
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

  # files too small?
  # must be this way for backwords compatibility
  $self->{_SmallFiles} and $return_string .= br.
   "small files: ". br.
     font({-color=>'red'}, $self->{_SmallFiles});
  
  return $return_string . "\n";

}
#----------
# 'Run details' button
sub DisplayLogReport {
  
  my $self = shift;

  my $divider = "*" x 100 . "\n";
  my $var;

#  print Dumper $self;
  print qq{
    $divider 
    <br> Report for logfile $self->{_LogfileName} <br> 
    $divider
    <br>
    STAR Level = $self->{_StarLevel}<br>
    ROOT Level = $self->{_RootLevel}<br>
    STARLIB version = $self->{_StarlibVersion}<br>
    Chain requested = $self->{_RequestedChain}<br>
    Input filename = $self->{_InputFn} <br>
    Output directory = $self->{_OutputDirectory}<br> 
    Start date/time = $self->{_JobStartTimeAndDate}<br>
  };
  if($self->NEventRequested){
    print qq{Nevents requested = $self->{_NEventRequested}<br>
	     First event requested = $self->{_FirstEventRequested}<br>
	     Last event requested = $self->{_LastEventRequested}<br>
	     Nevents processed = $self->{_NEventDone}<br>
	   };
  }
  else{
    print qq{First event done = $self->{_FirstEventDone}<br>
	     Last event done = $self->{_LastEventDone}<br>
	     NEvents done = $self->{_NEventDone}<br>
	   };
  }
  print "Production Files :<br>\n";

  print join "<br>\n", @{$self->{_ProductionFileListRef}};
  print "<br>\n";
  # error?
  defined ($self->{_ErrorString}) and
    print "Error found: $self->{_ErrorString}<br>\n";

  # run options
  print "<pre>\n";
  print "$divider Run options = $self->{_RunOptions}\n";

  # final timing
  $self->{_JobStatus} =~ /^[dD]one/ and  
    print "$divider Final timing $self->{_TimingString}\n";
  print "</pre>";
  print "$divider <br>\n";

}
#----------

sub GetMissingFiles{
  my $self=shift;
  
}

1;
