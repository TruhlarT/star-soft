#! /usr/bin/perl -w
#
# general object to contain logfile summary
#
# pmj 13/11/99
#
#=========================================================
package Logreport_object;
#=========================================================
use Cwd;

use File::stat;

use File::Copy;
use File::Find;
use File::Basename;

use Data::Dumper;

use Storable;

use QA_cgi_utilities;
use QA_globals;

use QA_make_reports; # bum

#=========================================================
1.;
#========================================================
sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  return $self;
}
#========================================================
sub _init{

  my $self = shift;
  
  my $arg = shift;
  my $data_type = shift;   # data, txt_report

  #-------------------------------------------------

  if ($data_type eq 'data'){

    # this is data: parse log file

    $production_dir = $arg;

    # check directory
    
    -d $production_dir or do{
      print "<h4> Error in Logreport_object constructor: ",
      "production dir $production_dir does not exist </h4> \n";
      return;
    };

    $self->ProductionDir($production_dir);

    # logfile exists?

    $global_logfile = "";
    find( \&QA_cgi_utilities::get_logfile, $production_dir );
    
    if ( -e $global_logfile ){
      print "<h3> Making logfile report for $global_logfile... </h3> \n";
      $self->LogfileName($global_logfile);
    }
    else{
      print "<h4> Error in Logreport_object constructor: ",
      "logfile not found in directory $production_dir </h4> \n";
      return;
    };

    # bum -initialize warning and error files
    my $report_key = QA_make_reports::get_report_key($production_dir);
    my $warning_file = "$topdir_report/$report_key/warning.txt";
    my $error_file = "$topdir_report/$report_key/error.txt";
    
    $self->WarningFile($warning_file);
    $self->ErrorFile($error_file);


    # get the info from the log file, build logfile report object
    
    $self->ParseLogfile();

  }
  elsif ($data_type eq 'txt_report'){
    # read existing report from "old style" ascii txt file
    $report_file = $arg;
    $self->FillObjectFromTxt($report_file);
  }

}

#========================================================
sub LogfileName{
  my $self = shift;
  if (@_) {$self->{LogfileName} = shift }
  return $self->{LogfileName};
}
#========================================================
sub LogfileNameWWW{
  my $self = shift;
  $self->{LogfileNameWWW} or do{

    my $logfile = $self->LogfileName;
    my $icount = -1;
    foreach $topdir (@topdir_data){
      $icount++;
      $logfile =~ /$topdir/ and do{
	($logfile_WWW = $logfile) =~ s/$topdir\///;
	$self->{LogfileNameWWW} = $topdir_data_WWW[$icount].$logfile_WWW;
	last;
      };
    }
  };

  return $self->{LogfileNameWWW};
}
#========================================================
sub ProductionDir{
  my $self = shift;
  if (@_) {$self->{ProductionDir} = shift }
  return $self->{ProductionDir};
}
#========================================================
sub StarLevel{
  my $self = shift;
  if (@_) {$self->{StarLevel} = shift }
  return $self->{StarLevel};
}
#========================================================
sub RootLevel{
  my $self = shift;
  if (@_) {$self->{RootLevel} = shift }
  return $self->{RootLevel};
}
#========================================================
sub StarlibVersion{
  my $self = shift;
  if (@_) {$self->{StarlibVersion} = shift }
  return $self->{StarlibVersion};
}
#========================================================
sub RunOptions{
  my $self = shift;
  if (@_) {$self->{RunOptions} = shift }
  return $self->{RunOptions};
}
#========================================================
sub RequestedChain{
  my $self = shift;
  if (@_) {$self->{RequestedChain} = shift }
  return $self->{RequestedChain};
}
#========================================================
sub InputFn{
  my $self = shift;
  if (@_) {$self->{InputFn} = shift }
  return $self->{InputFn};
}
#========================================================
sub FirstEventRequested{
  my $self = shift;
  if (@_) {$self->{FirstEventRequested} = shift }
  return $self->{FirstEventRequested};
}
#========================================================
sub LastEventRequested{
  my $self = shift;
  if (@_) {$self->{LastEventRequested} = shift }
  return $self->{LastEventRequested};
}
#========================================================
sub NEvent{
  my $self = shift;
  if (@_) {$self->{NEvent} = shift }
  return $self->{NEvent};
}
#========================================================
sub OutputFn{
  my $self = shift;
  if (@_) {$self->{OutputFn} = shift }
  return $self->{OutputFn};
}
#========================================================
sub RunStartTimeAndDate{
  my $self = shift;
  if (@_) {$self->{RunStartTimeAndDate} = shift }
  return $self->{RunStartTimeAndDate};
}
#========================================================
sub Machine{
  my $self = shift;
  if (@_) {$self->{Machine} = shift }
  return $self->{Machine};
}
#========================================================
sub OutputDirectory{
  my $self = shift;
  if (@_) {
    $temp = shift;

    # disk00000 is kaput pmj 17/11/99
    $temp =~ s/disk00000\/star\///;
    $temp =~ s/data01/rcf/;

    $self->{OutputDirectory} = $temp; 
  }

  return $self->{OutputDirectory};
}
#========================================================
sub Tags{
  my $self = shift;

# pmj 21/1/00: not currently of interest, make log report big
#  if (@_) {$self->{Tags} = shift }

  return $self->{Tags};
}
#========================================================
sub EventTiming{
  my $self = shift;

# pmj 21/1/00: not currently of interest, make log report big
#  if (@_) {$self->{EventTiming} = shift }
  return $self->{EventTiming};
}
#========================================================
sub RunCompletedOk{
  my $self = shift;
  if (@_) {$self->{RunCompletedOk} = shift }
  return $self->{RunCompletedOk};
}
#========================================================
sub ErrorString{
  my $self = shift;
  if (@_) {$self->{ErrorString} = shift }
  return $self->{ErrorString};
}
#========================================================
sub LastEvent{
  my $self = shift;
  if (@_) {$self->{LastEvent} = shift }
  return $self->{LastEvent};
}
#========================================================
sub ReturnCodeLastEvent{
  my $self = shift;
  if (@_) {$self->{ReturnCodeLastEvent} = shift }
  return $self->{ReturnCodeLastEvent};
}
#========================================================
sub TimingString{
  my $self = shift;
  if (@_) {$self->{TimingString} = shift }
  return $self->{TimingString};
}
#========================================================
sub RunCompletionTimeAndDate{
  my $self = shift;
  if (@_) {$self->{RunCompletionTimeAndDate} = shift }
  return $self->{RunCompletionTimeAndDate};
}
#========================================================
sub NEventsProcessed{
  my $self = shift;
  if (@_) {$self->{NEventsProcessed} = shift }
  return $self->{NEventsProcessed};
}
#========================================================
sub NEventsNotCompleted{
  my $self = shift;
  if (@_) {$self->{NEventsNotCompleted} = shift }
  return $self->{NEventsNotCompleted};
}
#========================================================
sub MissingFiles{
  my $self = shift;
  if (@_) {$self->{MissingFiles} = shift }
  return $self->{MissingFiles};
}
#========================================================
# bum - file for StWarning in the log file

sub WarningFile{
  my $self = shift;
  if (@_) {$self->{WarningFile} = shift }
  return $self->{WarningFile};
}
#========================================================
# bum - file for StError in the log file

sub ErrorFile{
  my $self = shift;
  if (@_) {$self->{ErrorFile} = shift }
  return $self->{ErrorFile};
}
#=========================================================
#=== bum, memory usage stuff, 25/1/00 ====================
#=========================================================
#===========beware, returns a reference =================
sub MemoryArray{
  my $self = shift;
  if (@_) {
     push @{$self->{memory}->{array}}, shift;
  }
  return $self->{memory}->{array};
}
#========================================================
#====== initialized in QA_object=========================
sub MemoryFile{
  my $self = shift;
  @_ and do{
      my $report_dir = shift;
      $self->{memory}->{file}= $report_dir . "/memory.log";
  };
  return $self->{memory}->{file};
}
#========================================================
#====this is called in the QA_object LogReport  =========
#====the name of the txt file is $report_dir/memory.log=====
#========================================================
sub WriteMemoryFile{
  my $self = shift;
  my $mem_file = $self->MemoryFile;
  open MEMFILE, ">$mem_file" or die "Cannot open $mem_file: $!\n";
    print MEMFILE join "\n", @{$self->MemoryArray};
  close MEMFILE;
}
#=========================================================
sub ParseLogfile {

  my $self = shift;

  $logfile_name = $self->LogfileName();

  #----------------------------------------------------------
  # dump contents of log file to array for parsing  

  open (LOGFILE, $logfile_name) or die "cannot open $logfile_name: $!";
  @logfile = <LOGFILE>;
  close LOGFILE;

  # initialize WarningFile, ErrorFile and open them
  my $warning_file = $self->WarningFile;
  my $error_file = $self->ErrorFile;

  open (WARN, ">$warning_file") or die "cannot open $warning_file: $!";
  open (ERR, ">$error_file") or die "cannot open $error_file: $!";

  #----------------------------------------------------------
  # bum, memory stuff
  my ($count, @list);

  # parse beginning of file
  
  $record_run_options = 0;
 
  foreach $line (@logfile) {
    
    next unless $line =~ /^QAInfo:|^StWarning:|^StError/;
    
    # get STAR and ROOT levels
    $line =~ /STAR_LEVEL\W+(\w+), ROOT_LEVEL\W+([0-9\.]+)/ and do{
      $self->StarLevel($1);
      $self->RootLevel($2);
      next;
    };
    
    # get STARLIB version
    $line =~ /You are in (\w+)/ and do{
      $self->StarlibVersion($1);
      next;
    };
    
    # start recording of run options
    $line =~ /Requested chain (?:bfc )?is\W+([\w ]+)/ and do{
      $record_run_options = 1;
      $self->RunOptions("\n");
      $self->RequestedChain($1);
      next;
    };
    
    # turn off recording of run options?
    $record_run_options and $line !~ /=======/ and $record_run_options = 0;
    
    $record_run_options and do {
      $line =~ s/QAInfo://;
      $temp = $self->RunOptions();
      $self->RunOptions($temp.$line);
      next;
    };
    
    # get input file name
    $line =~ /Input file name = (\S+)/ and do {
      $self->InputFn($1);
      next;
    };

    #valid from 99h on pmj 14/9/99
    $line =~ /QAInfo:Process\s+\[First=\s+(\d+)\/Last=\s+(\d+)\/Total=\s+(\d+)/ and do{
      $self->FirstEventRequested($1);
      $self->LastEventRequested($2);
      $self->NEvent($3);
      next;
    };

    # valid up to 99g  pmj 14/9/99
    # get number of events to process
    $line =~ /Events to process = (\d+)/ and do {
      $self->NEvent($1);
      next;
    };

    # for old log files (keep this in for now pmj 17/8/99)
    
    # get input file name and number of events to process
    $line =~ /Input file name = (\S+).*Events to process = (\d+)/ and do {
      $self->InputFn($1);
      $self->NEvent($2);
      next;
    };

    
    # get output root filename
    $line =~ /Output root file name (\S+)/ and do {
      $self->OutputFn($1);
      next;
    };
    
    # run start time
    $line =~ /Run is started at Date\/Time ([0-9\/]+)/ and do {
      $self->RunStartTimeAndDate($1);
      next;
    };
    
    # machine and directory
    $line =~ /Run on ([\w\.]+) in (\S+)/ and do {
      $self->Machine($1);
      # fix up the data directory a bit
      ($output_directory = $2) =~ s/\/direct//;
      $output_directory =~ s/\+/\//;
      $self->OutputDirectory($output_directory);
      next;
    };
    #---------- added memory usage stuff, bum 25/1/00 ----- 
    if ($line =~ /tree:\s+endmaker/i) {
	@list = split /\s+/, $line;
	$line =~ /SIZE|SZ/i and do {
	    $count=0;
	    foreach (@list) {last if /SIZE|SZ/i; $count++;}
	    next;
	};
	#solaris is weird, 10/2/00
	$count-- if $self->OutputDirectory =~ /Solaris/i;
	#fill array
	$list[$count] =~ /(\d+)/ and $self->MemoryArray($1);
    }
    
    #---------- bum - StWarning and StError----------------
    
    print WARN $line if ($line =~ /StWarning:/);
    print ERR $line if ($line =~ /StError:/); 

    #-------------------------------------------------------




    # CVS tags
# not currently of interest   pmj 21/1/00
#    $line =~ /with Tag (.*)/ and do{
#      $self->Tags("\n".$1);
#      next;
#    };
#    $line =~ /built.*from Tag (.*)/ and do{
#      $temp = $self->Tags();
#      $self->Tags($temp."\n".$1);
#      next;
#    };
    
    # event timing
# not currently of interest   pmj 21/1/00
#    $line =~ /Done with (Event.*)/ and do{
#      $temp = $self->EventTiming();
#      $self->EventTiming($temp."\n".$1);
#      next;
#    };
    
  }
    
  #--------------------------------------------------------------------------
  # get lines at end of file, starting with last occurence of "EndMakerShell"
  
  undef @end_lines;

  while ( $line  = pop @logfile ){

    push @end_lines, $line;
    $line =~ /Done with Event/  and last;
    
  };
  
  @end_lines = reverse @end_lines;
  
  #--------------------------------------------------------------------------
  # parse end of file

  $self->RunCompletedOk(0);

  $divider = "-" x 80;
  $divider .= "\n";
 
  $done_with_event_flag = 0;

  foreach $line (@end_lines) {

    # look for segmentation violation
    $line =~ /segmentation violation/ and do {
      $self->ErrorString("segmentation violation;");
      next ;
    };

    next unless $line =~ /^QAInfo:/;

    # this one valid from 99h pmj 14/9/99

    # added ".*" between evt and sta to accomodate new Date.Time field pmj 11/1/00

    # get last event number
    $line =~ /QAInfo: Done with Event\s+\[no\.\s+(\d+)\/run\s+(\d+)\/evt\.\s+(\d+).*\/sta\s+(\d+)/ and do{
      $done_with_event_flag = 1;
      $self->LastEvent($1);
      $self->ReturnCodeLastEvent($4);
      next;
    };

    # this one valid up to 99g pmj 14/9/99
    # get last event number
    $line =~ /Done with Event no\. ([0-9]+)\W+([0-9]+)/ and do {
      $self->LastEvent($1);
      $self->ReturnCodeLastEvent($2);
      next;
    };
    
    # get timing strings
    $line !~ /Done with Event/ and $line =~ /Real Time =/ and do{
      $line =~ s/QAInfo://;

      $timing_string = $self->TimingString();
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
    
    # run completed o.k.?
    $line =~ /Run completed/ and do{
      $self->RunCompletedOk(1);
      next;
    };

    # run completion date/time
    # modified pmj 10/5/00

#QAInfo:Run is finished at Date/Time 20000510/33337; Total events processed :400 and not completed: 0
    $line =~ 
      /Run is finished at Date\/Time ([0-9\/]+); Total events processed(\D+)(\d+) and not completed(\D+)(\d+)/ 
	and do{
	  $self->RunCompletionTimeAndDate($1);
	  
	  $self->NEventsProcessed($3);
	  $self->NEventsNotCompleted($5);
	  
	  next;
	};
    
  }

  # bum - close some files
  close WARN; close ERR;

  #--------------------------------------------------------------------------
  # fill these in in case of crash

  $done_with_event_flag or do{
    $self->LastEvent(0);
    $self->ReturnCodeLastEvent(-999);
    $self->RunCompletionTimeAndDate(-999);
  };
  #--------------------------------------------------------------------------
  # now check if expected files have been created

  $this_dir = dirname($logfile_name);

  $missing_files = undef;
  
  undef $global_root_dst_file;
  find ( \&QA_cgi_utilities::get_root_dst_file, $this_dir);
  defined $global_root_dst_file or $missing_files .= " .dst.root"; 

  undef $global_root_hist_file;
  find ( \&QA_cgi_utilities::get_root_hist_file, $this_dir);
  defined $global_root_hist_file or $missing_files .= " .hist.root"; 

  # also flag .hist.root missing if it is too small
  defined $global_root_hist_file and do{
    $size = stat($global_root_hist_file)->size;
    $size < 10000 and $missing_files .= " .hist.root";
  };

  # not relevant after SL99j pmj 11/1/00
#  undef $global_root_event_file;
#  find ( \&QA_cgi_utilities::get_root_event_file, $this_dir);
#  defined $global_root_event_file or $missing_files .= " .event.root"; 


# pmj 7/3/00: took out xdf file checking, are no longer being produced
#  undef $global_dst_xdf_file;
#  find ( \&QA_cgi_utilities::get_xdf_file, $this_dir);
#  defined $global_dst_xdf_file or $missing_files .= " .dst.xdf"; 

#pmj 7/3/00 Added checks for .tags.root, .runco.root
  undef $global_root_tags_file;
  find ( \&QA_cgi_utilities::get_root_tags_file, $this_dir);
  defined $global_root_tags_file or $missing_files .= " .tags.root"; 

  undef $global_root_runco_file;
  find ( \&QA_cgi_utilities::get_root_runco_file, $this_dir);
  defined $global_root_runco_file or $missing_files .= " .runco.root"; 

 # bum 9/3/00 -added check for geant.root
   undef $global_root_geant_file;
   find ( \&QA_cgi_utilities::get_root_geant_file, $this_dir);
   defined $global_root_geant_file or $missing_files .= " .geant.root";



#----

  $self->MissingFiles($missing_files);
  
}
#=========================================================
sub LogfileSummaryString {

  my $self = shift;

  $return_string = "";

  if ( $self->StarLevel() or $self->StarlibVersion()) {

    if ( $self->RunCompletedOk() ) {
      $return_string .= "run completed;";
    }
    else {
      $return_string .= " run not completed;";
      $self->ErrorString() and $return_string .= $self->ErrorString(); 
    }

    # check for event completion info in log file pmj 10/5/00

    if ( $self->NEventsProcessed() > 0 ){

      $return_string .= " Events processed: ".$self->NEventsProcessed().
	", not completed: ".$self->NEventsNotCompleted().";";

    }
    else{

      # old style
      
      $return_string .= " ".$self->LastEvent();
      $self->NEvent() and $return_string .= "/".$self->NEvent();
      $return_string .= " events done;";
    }

    #---

    if ( $self->FirstEventRequested() and $self->LastEventRequested() ){
       $return_string .= "<br>(events requested: ".$self->FirstEventRequested().
	 "-".$self->LastEventRequested().")";
     }
    
  }
  else {
    $return_string .= "Log file could not be parsed";
  }

  $self->MissingFiles() and $return_string .=
    "<br>missing files:<font color=red> ".
      $self->MissingFiles()."</font>";
  
  return $return_string;
}
#=========================================================
sub DisplayLogReport {
  
  my $self = shift;

  print "<h2> Logfile report for ",$self->LogfileName()," </h2> \n";

  #--------------------------------------------------------------------

  $divider = "*" x 100;
  $divider .= "\n";

  print "$divider <br> Report for logfile ",$self->LogfileName()," <br> $divider";

  print "<pre>";

  print "STAR Level = ",$self->StarLevel();
  print " ROOT Level = ",$self->RootLevel();
  print " STARLIB version = ",$self->StarlibVersion(),"\n";
  
  print "Chain = ", $self->RequestedChain() ," \n";

  print "Input filename = ", $self->InputFn ," \n";
  print "Output directory = ", $self->OutputDirectory ," \n";
  print "Output filename = ", $self->OutputFn ," \n";

  print "Start date/time = ", $self->RunStartTimeAndDate ," \n";
  print "Nevents requested = ", $self->NEvent ," \n";
  print "First event requested = ", $self->FirstEventRequested ," \n";
  print "Last event requested = ", $self->LastEventRequested ," \n";
  print "Nevents completed = ", $self->LastEvent ," \n";
  print "Return code for last event = ", $self->ReturnCodeLastEvent ," \n";
  print "Finish date/time = ", $self->RunCompletionTimeAndDate ," \n";
  print "Machine name = ", $self->Machine ," \n";

  $temp = ( $self->RunCompletedOk ) ? "Run completed O.K." : "Run not completed" ;
  print "$temp \n";

  defined ($self->ErrorString) and
      print "Error found:", $self->ErrorString ," \n";

  print "$divider Run options =", $self->RunOptions, "\n";
#  print "$divider CVS tags =", $self->Tags, "\n";

#  print "$divider";
#  $self->RunCompletedOk or 
#    print "Event timing report is a mess if run didn't complete o.k. \n";
#  print "Event timing =", $self->EventTiming, "\n";

  $self->RunCompletedOk and  
    print "$divider Final timing =", $self->TimingString, "\n";

  print "$divider";
  print "</pre> \n";

}
#=====================================================================================
sub FillObjectFromTxt{

  my $self = shift;
  my $logfile_report = shift;

  #-----------------------------------------------------------------------

  # dump contents of logfile report into hash

  open LOGFILE, $logfile_report or die "Cannot open log file $logfile_report: $!\n";

  my $record_run_options = 0;
  my $record_tags = 0;
  my $record_event_timing = 0;
  my $record_final_timing = 0;

  while(<LOGFILE>){

    #---
    
    /Report on logfile (\S+)/ and do {
      $self->LogfileName($1);
      next;
    };

    #---
    
    /STAR level: (\w+)/ and do {
      $self->StarLevel($1);
      next;
    };
    
    #---
    
    /ROOT level: (\S+)/ and do {
      $self->RootLevel($1);
      next;
    };
    
    #---
    
    /STARLIB version: (\w+)/ and do {
      $self->StarlibVersion($1);
      next;
    };
    
    #---
    
    /chain: ([\w ]+)/ and do {
      $self->RequestedChain($1);
      next;
    };
    
    #---
    
    /run options:/ and do {
      $record_run_options = 1;
      $self->RunOptions("\n");
      next;
    };

    # done with run options?
    $record_run_options and $_ !~ /======/ and $record_run_options = 0;
    
    $record_run_options and do {
      $temp = $self->RunOptions().$_;
      $self->RunOptions($temp);
      next;
    };

    #---
    
    /input filename: (\S+)/ and do {
      $self->InputFn($1);
      next;
    };
    
    #---
    
    /requested number of events: (\d+)/ and do {
      $self->NEvent($1);
      next;
    };
    
    #---
    
    /first event requested: (\d+)/ and do {
      $self->FirstEventRequested($1);
      next;
    };
    
    #---
    
    /last event requested: (\d+)/ and do {
      $self->LastEventRequested($1);
      next;
    };
    
    #---
    
    /output filename: (\S+)/ and do {
      $self->OutputFn($1);
      next;
    };
    
    #---
    
    /start time and date: (\S+)/ and do {
      $self->RunStartTimeAndDate($1);
      next;
    };
    
    #---
    
    /machine: (\S+)/ and do {
      $self->Machine($1);
      next;
    };
    
    #---
    
    /output dir: (\S+)/ and do {
      $self->OutputDirectory($1);
      next;
    };

    #---
    
    /segmentation violation\?: (\d+)/ and do {
      $self->ErrorString("segmentation_violation;");
      next;
    };
    
    #---
    
    /^last event: (\d+)/ and do {
      $self->LastEvent($1);
      next;
    };
    
    #---
    
    /ret code last event: (\d+)/ and do {
      $self->ReturnCodeLastEvent($1);
      next;
    };
    
    #---
   
    /run completed ok\?: (\d+)/ and do {
      $self->RunCompletedOk($1);
      next;
    };
    
    #---
    
    /run completion time and date: (\S+)/ and do {
      $self->RunCompletionTimeAndDate($1);
      $global_creation_time = $1;
      next;
    };
    
    #---
    
    /missing files: (.*)/ and do {
      ($temp = $1) =~ s/^s+//;
      $temp =~ s/s+$//;
      $self->MissingFiles($temp);
      next;
    };
    
    #---
    
    /cvs tags:/ and do {
      $record_tags = 1;
      $self->Tags("\n");
      next;
    };

    # done with cvs tags?
    $record_tags and do{
      if($_ !~ /Name/){$record_tags = 0;}
    };
    
    $record_tags and do {
      $temp = $self->Tags.$_;
      $self->Tags($temp);
      next;
    };
    
    #---
#    
#    /event timing:/ and do {
#      $record_event_timing = 1;
#      $self->EventTiming("\n");
#      next;
#    };
#
#
#    # done with event timing?
#    $record_event_timing and $_ !~ /Event no\./ and $record_event_timing = 0;
#    
#    $record_event_timing and do {
#      $temp = $self->EventTiming.$_;
#      $self->EventTiming($temp);
#      next;
#    };
#    
    #---
    
    /timing string:/ and do {
      $record_final_timing = 1;
      $self->TimingString("\n");
      next;
    };

    # done with timing string?
    $record_final_timing and $_ !~ /Real Time/ and $_ !~ /----------/ and do {
      $record_final_timing = 0;
      next;
    };

    $record_final_timing and do {
      $temp = $self->TimingString.$_;
      $self->TimingString($temp);
      next;
    };

  }

  close LOGFILE;

}
