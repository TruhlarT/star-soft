#! /usr/bin/perl 
#
# Logreport object for online raw.
# Pretty much completely different from the other Logreports...
# i could have used Logreport_object as a base class but i didnt.
# dont ask why.
# bum 000623
#
#=============================================================================
package Logreport_object_online;
#=============================================================================
use CGI qw/:standard :html3/;
use QA_globals;
use QA_db_utilities qw(:db_globals); 
use QA_cgi_utilities;
use IO_object;

use Data::Dumper;
use FileHandle;
use File::Basename;
use File::stat;
use POSIX qw(strftime);
use strict;
use vars qw($AUTOLOAD);
1;
#-----------------------------------------------------------------------------
# class members that use autoload

my %members = ( _ReportKey                => undef, #
		_qaID                     => undef, #
		_LogfileName              => undef, # full path e
		_StarlibVersion           => undef, # needed to run macro
		_JobCompletionTimeAndDate => undef, # hist file creation time
		_NEventRequested          => undef, # dont need these for .hist ?...
		_NEventDone               => undef, # 
		_OutputDirectory          => undef, # .../datapool/QA
		_ProductionFileListRef    => undef, # ref to an array
		_MissingFiles             => undef, # dummy
		# 
		# see parse info file
		_Detector                 => undef,
		_RunID                    => undef, 
		_Trigger                  => undef,
		_NEvent                   => undef,
		_FirstEvent               => undef,
		_LastEvent                => undef,
		_FirstEventReceivedTime   => undef,
		_LastEventReceivedTime    => undef		
	      );
#-----------------------------------------------------------------------------
sub new{
  my $classname = shift;

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
# initialize.
#
sub _init{
  my $self       = shift;
  my $report_key = shift;
  
  defined $report_key or die __PACKAGE__, " needs a report key";

  $self->ReportKey($report_key);

  $self->qaID(QA_db_utilities::GetFromQASum($QASum{qaID},$report_key));
	      
  # parse the info file
  print "Parsing info file...\n", br;
  $self->ParseInfoFile() or return;
  print "...done\n", br;
 
  print "Getting additional info...\n", br;
  $self->GetJobInfo() or return;
  print "...done\n",br;

  print "Inserting into db\n",br;
  $self->InsertIntoDb() or return;
  print "...done";

  return 1;
}
#-----------
# copied from perl toot.
# automatically makes accessors 
# for 'permitted' members if they dont already exist
#
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
# parse the log file ( just the info.daq file)
# CHANGE THIS
sub ParseInfoFile{
  my $self = shift;

  my (@index_ary, @daqtime_ary);

  # deduce the name of the info file
  my $io         = new IO_object("SummaryHistDir");
  my $sumhistdir = $io->Name;

  $self->LogfileName("$sumhistdir/" . $self->ReportKey . ".hist.info");

  # might as well set the ouput directory here
  $self->OutputDirectory($sumhistdir);

  my $fh = new FileHandle($self->LogfileName, "r") or do{
    print "Cannot find " ,$self->LogfileName;
    return;
  };

  while (defined (my $line = $fh->getline)){
    next if $line =~ /^\#/;

    # star library
    if ($line =~ /lib\s+(\w+)/){
      $self->{_StarlibVersion} = $1; next;
    }
    
    # run number
    if ($line =~ /run\s+(\d+)/){
      $self->{_RunID} = $1; next;
    }

    # triggers used
    if ($line =~ /trigger\s+(\w+)/){
      $self->{_Trigger} = $1; next;
    }

    # number of events in the summary file
    if ($line =~ /events\s+(\d+)/){
      $self->{_NEvent} = $1; next;
    }

    # ok. if the line starts with a number, 
    # the first number is the event # (index),
    # the second is the daq received time in epoch seconds
    # i'm only interest in the first and last values so
    # keep in arrays for simplicity
 
    if ($line =~ /(\d+)\s+(\d+)/){
      push @index_ary, $1;
      push @daqtime_ary, $2;
      next;
    }
  }

  # first and last events and their corresponding received times
  $self->FirstEvent(pop @index_ary);
  $self->FirstEventReceivedTime(pop @daqtime_ary);

  # be careful if only one event
  my $lastevent = shift @index_ary   || $self->FirstEvent;
  my $lasttime  = shift @daqtime_ary || $self->FirstEventReceivedTime;

  $self->LastEvent($lastevent);
  $self->LastEventReceivedTime($lasttime);

  return 1;
}
#----------
# more info
# 
sub GetJobInfo{
  my $self = shift;

  # find the .hist.root files.
  # assume a particular form

  (my $file = $self->LogfileName) =~ s/\.info/\.root/;

  # hmm. convert the $file to @file to be compatible
  # with offline

  my @file = ($file);

  -e $file[0] or do{ 
    print font({-color => 'red'}, "No .hist.root file?"); return;
  };

  $self->ProductionFileListRef(\@file);

  # find the job completion time for one of the hist files
  # QA_object needs this.
  # i'm going around in circles here.  QA_object will then 
  # convert this back into epoch sec

  my $aFile     = $self->ProductionFileListRef->[0];
  my $epoch_sec = stat($aFile)->mtime;
  my $dateTime  = strftime("%Y-%m-%d %H:%M:%S",localtime($epoch_sec));

  $self->JobCompletionTimeAndDate($dateTime);

  # deduce the detector info from the report key
  # e.g. sum.0001063039_all.raw_tpc
  my $detector = (split /_/, $self->ReportKey)[-1];
  $self->Detector($detector);

  return 1;
}
#----------
# 
sub InsertIntoDb(){
  my $self = shift;
  
  # daq time of last event
  my $epoch_sec = $self->LastEventReceivedTime;;
  my $dateTime  = strftime("%Y-%m-%d %H:%M:%S",localtime($epoch_sec));
  QA_db_utilities::UpdateQASummary($QASum{createTime}, $dateTime,$self->qaID);

  # run ID
  my $runID     = $self->RunID;
  QA_db_utilities::UpdateQASummary($QASum{runID},$runID,$self->qaID);

  # trigger 
  my $trigger   = $self->Trigger;
  QA_db_utilities::UpdateQASummary($QASum{trigger}, $trigger, $self->qaID);

  # detector;
  my $detector  = $self->Detector;
  QA_db_utilities::UpdateQASummary($QASum{detector}, $detector, $self->qaID);
  return 1;
} 
#----------
# used in QA_object.  third column from the browser
# dont really know what to put here...
#
sub LogfileSummaryString{
  my $self = shift;

  my $daq_epoch = $self->LastEventReceivedTime;
  my $daq_date  = strftime("%Y-%m-%d %H:%M:%S",localtime($daq_epoch));

  my $string = "Last evt received ; " . br . $daq_date . br . br .
               "Events: (" . $self->FirstEvent . "-" . $self->LastEvent . ")".
               "\n";
  
}  
#----------
# 'Run details' button
#
sub DisplayLogReport{
  my $self = shift;;

  # make a link to the 'info.daq'/logfile
  my $io    = new IO_object("LogScratchWWW",$self->LogfileName);
  my $link  = $io->Name;
  my $label = "Info file: ";

  QA_cgi_utilities::make_anchor($label, $self->LogfileName, $link);

  print "Production files : \n", br;
  print join "\n<br>", @{$self->ProductionFileListRef};

}
1;
