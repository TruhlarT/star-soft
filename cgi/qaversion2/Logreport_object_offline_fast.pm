#! /opt/star/bin/perl
#
# derived Logreport_object for fast offline
#
#==========================================================
package Logreport_object_offline_fast;
#==========================================================
use CGI qw/:standard :html3/;

#use IO_object;
use QA_globals;
use QA_db_utilities qw(:db_globals);
use FileHandle;
use File::Basename;

use lib "/afs/rhic.bnl.gov/star/packages/scripts"; # RunDaq.pm lives here
use RunDAQ;

use strict;
use base qw(Logreport_object); 
#=======================================================o===
# more members

my %members = (
	       _RunID            => undef,     
	       _FileSeq          => undef,
 	       _CollisionType    => undef,
	       _ChainName        => undef,
	       _FirstEventDone   => undef,
	       _LastEventDone    => undef,
	       _Dataset          => undef,
	       _Current          => undef,
	       _BeamE            => undef,
	       _ScaleFactor      => undef
	      );

my $basePath = "/star/data13/reco/dev";
my $logPath = "/star/rcf/prodlog/dev/log/daq";

#==========================================================
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_) or return;  
  defined $self or return;

#  bless($self,$classname);

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

  $self->ChainName($self->RequestedChain());

  my $jobID = $self->JobID();

  # first, last, and n events done, collision type, current, beam,
  # detsetmaske
  my @fields=(
	      $DAQInfo{beginEvt},$DAQInfo{endEvt},$DAQInfo{numEvt},
	      $DAQInfo{collision},$DAQInfo{current},
	      $DAQInfo{beamE},$DAQInfo{detSetMask},$DAQInfo{scaleFactor}
	     );
  my $table = "$dbFile." . $DAQInfo{Table};
  my $where = "$table." . $DAQInfo{file} . "='$jobID'";
  my ($first,$last,$n,$collision,$current,$beamE,$detSetMask,$scaleFactor)
    = QA_db_utilities::GetOneRowFromTable(\@fields,$table,$where);


  $self->NEventDone($n); 
  $self->FirstEventDone($first); 
  $self->LastEventDone($last);
  $self->CollisionType($collision);
  $self->Current($current);
  $self->BeamE($beamE);
  $self->ScaleFactor($scaleFactor);

  # run id and file seq
  $self->JobID() =~ /st_physics_(\d+)_raw_(\d+)/;
  my $run=$1; my $seq=$2;
  $self->RunID($run); $self->FileSeq($seq);
  
  #  unpack detSetMaske
  my $dataset = rdaq_mask2string($detSetMask);
  
  $self->Dataset($dataset);
  

}
#
#----------
# 
#
sub GetLogFile{
  my $self  = shift;

  # path of logfiles is hardcoded
  (my $id = $self->JobID())=~ s/\.daq$//;
  return "$logPath/$id.log";

}
#
#----------
# parse the logfile
#
sub ParseLogfile {
  my $self = shift;

  # open files
  # log file may be .log or .fz;
  #
  my $logFile = $self->LogfileName();
  my $openOption=undef;
  if(-e $logFile) { # .log 
    $openOption=$logFile;
  }
  else {            # .log.gz
    $logFile =~ s/\.log$/\.log\.gz/;
    $openOption="zcat $logFile|";
  }

  my $fh = FileHandle->new($openOption) or 
    do{
      print "Trouble opening file = ", $logFile, " $!\n";
      return;
    };
  print "Found logfile ", $logFile, "\n", br;

  
  my $outFileRequestedString;
  my $segFault=0;
  my ($record_run_options,$record_job_status);
  # read the log file
  while (defined (my $line = $fh->getline )) {

    # look for seg fault
    if($line =~ /segmentation violation/){
      $segFault=1;
      next;
    }

    # star library version
    if($line =~ /chain will run from library\s+(\S+)/){
      my $value = $1;
      $self->StarlibVersion($value);
      next;
    }

    # chain options summary
    if($line =~ /chain will run with options\s+(\S+)/){
      my $value = $1;
      $self->RequestedChain($value);
      next;
    }

    # output directory
    #if($line =~ /output destination will be\s+(\S+)/){
    #  my $value = $1;
    #  $self->OutputDirectory($value);
    #  next;
    #}

    # input file
    if($line =~ /chain will run over file\s+(\S+)/){
      my $value = $1;
      $self->InputFn($value);
      next;
    }
    
    # this is the expected output files
    if($line =~ /Outputs final will be(.*)/){
      $outFileRequestedString = $1;
    }
    
    # run options ++ 
    if($line =~ /StMessageManager message summary/ ){ 
      $record_run_options=1;
      print "****************YESY\n";
      next;
    }
    if($record_run_options and $line=~ /^QAInfo:/){
      $line =~ s/QAInfo://;
      my $opt = $self->RunOptions;
      if(!$opt){ $self->RunOptions("\n");}
      else { $self->RunOptions($opt.$line); }
      next;
    }
    if($record_run_options and $line !~ /^QAInfo:/){
      $record_run_options=0;
      next;
    }

    next unless $line =~ /^QAInfo:/;

    # star and root level
    if( $line =~ /STAR_LEVEL\s+:\s+(\w+),.*?:\s+([\d\.]+).*?:\s+(\S+)/){
      my $star = $1; my $root = $2; my $node =3;
      $self->StarLevel($star);
      $self->RootLevel($root);
      $self->Machine($node);
      next;
    }
    
    
    
    # get input file name
    $line =~ /Input file name = (\S+)/ and do {
      my $value = $1;
      $self->InputFn($value); 
      next;
    };
        
    # run start time
    $line =~ /Run is started at Date\/Time ([\d\/]+)/ and do {
      my $datetime = QA_utilities::convert_logdatetime($1);
      $self->JobStartTimeAndDate($datetime);
      next;
    };
     
    # find the job status
    #if($line =~ /StIOMaker::Make() == 3/){
    #  while(my $next = $fh->getline()){
    #	if($line=~/^QAInfo:(.*)/){
    #}
    #  }
    #}
	       
   
    # finish time and skipped?
    if($line =~ /Run is finished at Date\/Time\s+([\d\/]+);.*?not completed:\s+(\d+)/){
      my $datetime = QA_utilities::convert_logdatetime($1);
      $self->JobCompletionTimeAndDate($datetime);
      my $val=$2;
      $self->NoEventSkipped($val);
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

  }
  # check that the input file name is valid
  defined $self->InputFn() or do {
    print "Cannot find the input file.  Trouble parsing log file?\n";
    return 0;
    };

  # just set the job status as done
  my $jobStatus = ($segFault) ? "segmentation violation" : "done";
  $self->JobStatus($jobStatus);

  # a first stab at the output files. see GetJobInfo for find tuning
  $self->ProductionFileListRef([split(/\s+/,$outFileRequestedString)]);
  	 
  # just copy the warning file
  my $warnName = new IO_object("StWarningFile",$self->ReportKey)->Name();
  my $log = $self->LogfileName();
  (my $warnFile = $log) =~ s/\.log$/\.err/;
  
  my $ok = link $warnFile, $warnName; 
  if(!$ok){
    print h2("Cannot copy warning file $warnFile to $warnName\n");
  }
  else{
    $self->WarningFile($warnName);
  }
  

  return 1;
}
#
#----------
# get more info from the db
#
sub GetJobInfo{
  my $self = shift;

  my $jobID = $self->JobID();

  # get the output directory from db
  my $hh = rdaq_open_odatabase();
  my $outputDir = rdaq_get_location($hh,$self->JobID());
  $self->OutputDirectory($outputDir);
  rdaq_close_odatabase($hh);
  
  # emergency output directory
  my $hpss = rdaq_file2hpss($self->JobID(),2);
  my ($year,$month) = (split(/\s+/,$hpss))[2,3];
  $month = "0$month" if length $month<2;
  my $defaultOutputDir = "$basePath/$year/$month";

  if(!-d $self->OutputDirectory()){
    print "<font color=red>Cannot find",$self->OutputDirectory(),
    "<br>\n";
    print "Trying $defaultOutputDir...<br>\n";
    if(!-d $defaultOutputDir){
      print  "Bailing out...</font><br>\n";
      return 0;
    }
    else{
      print "Found it</font><br>\n";
      $self->OutputDirectory($defaultOutputDir);
    }
  }

  # Real output files
  my @outFiles; 
  my $size =1000;
  my ($smallString,$missingString);

  # check if they're all there or if they're too small
  if(scalar @{$self->ProductionFileListRef()} < 2){
    print "No output files? Bailing out\n";
    return 0;
  }

  foreach my $file (@{$self->ProductionFileListRef()}){
    next if !$file;
    $file =~ /\.(\w+\.root)$/; 
    my $comp = $1;
    $file = "$outputDir/" . basename $file;    
    if(!-e $file){
      $missingString .= "$comp<br>";
    }
    else{ # ok it exists
      push @outFiles, $file;
      if((stat($file))[7]<$size){
	$smallString .= "$comp<br>";
      }
    }
  }
  $self->MissingFiles($missingString) if $missingString;
  $self->SmallFiles($smallString) if $smallString;

  print "outfiles: \n", join("\n",@outFiles),"\n";
  $self->ProductionFileListRef(\@outFiles);

  1;
}  
1;
