#! /usr/bin/perl 

# first try at a QA object
# pmj 29/7/99
#========================================================
package QA_object;
#========================================================
use CGI qw/:standard :html3/;
use File::Basename;
use File::stat;
use Storable;

use QA_globals;
use Logreport_object_nightly;
use Logreport_object_offline;
use QA_cgi_utilities;
use Browser_object;
use HiddenObject_object;
use QA_report_io;   #check why this gives errors
use QA_db_utilities;
use IO_object; 
use QA_report_object;
use strict;
#--------------------------------------------------------
1;

# just for the reader's benefit
# %members is never explicitly used
# all IO_objects have an IO in front

my %members = 
  ( _JobID               => undef, # interface with db
    _qaID               => undef, # identifies the qa job
    _ReportKey           => undef, # identifies QA_object
    _IOReportDirectory   => undef, # where all the qa files are
    _ReportDirectoryWWW  => undef, # used for links
    _OnDisk              => undef, # on disk still or not?
    _LogReportStorable   => undef, # logreport storable on disk
    _ProductionDirectory => undef, # output directory of root files
    _CreationEpochSec    => undef, # convert YYYY-MM-DD hh:mm:ss
    _LogReport           => undef, # pointer to Logreport_object
    _IOControlFile       => undef, # the brains behind running the macros
    _QADone              => undef, # QA done or not?   
    _QADate              => undef  # date the QA was done  
    
  );
#========================================================
# 
sub new{
  my $classname = shift;

  # this object should never be created
  $classname eq __PACKAGE__ and
    die __PACKAGE__, " should not be instantiated\n";
 
  my $self = {};

  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  # tag new object for hidden
  $gBrowser_object and $gBrowser_object->Hidden->NewQAObject(1);

  return $self;
}
#========================================================
sub _init{
  
  my $self = shift;

  my $report_key = shift;
  @_ and my $action = shift; # e.g update - make Logreport

  my $io; # points to the io_object

  # check for $report_key
  defined $report_key or die __PACKAGE__ ," needs a report key";

  # 
  $self->{_ReportKey} = $report_key;  
  $self->{_IOReportDirectory} = IO_object->new("ReportDir",$report_key);

  $io = IO_object->new("ReportDirWWW",$report_key);
  $self->{_ReportDirectoryWWW} = $io->Name;

  # set Logreport obj file
  $io = IO_object->new("LogReportStorable",$report_key);
  $self->{_LogReportStorable} = $io->Name;
  
  #----------
  # updating entails creating the Logreport object
  # and making the report directory

  my $report_dir = $self->IOReportDirectory->Name;

  if ($action =~ /update/ )
  { 
    # create logreport obj
    $self->UpdateLogReport() or do{  
      # something's wrong.  erase everything and get out
      print h3("<font color=red>Error - Erasing Job..."),br;
      QA_db_utilities::EraseJob($self->ReportKey,
				$self->IOReportDirectory->Name);
      return;
    };
  } 
  else
  {   # just get it from disk
      $self->GetLogReport or return;
  }     
  # ----------
  # initialize some members using logreport_object

  #$self->{_JobID} = $self->LogReport->JobID;
  $self->{_qaID}  = $self->LogReport->qaID;
  $self->{_ProductionDirectory} = $self->LogReport->OutputDirectory;

  # convert creation time to epoch seconds
  my $time_temp = $self->LogReport->JobCompletionTimeAndDate;
  $self->{_CreationEpochSec} = 
    QA_utilities::datetime_to_epochsec($time_temp);

  # has QA been done or not?

  ($self->{_QADone}, $self->{_QADate}) =
    QA_db_utilities::GetQASummary($self->qaID);

  # is data on disk? - see derived classes
  
  $self->InitOnDisk();

  # control file initialized 
  $self->InitControlFile();
}
#===========================================================
# check if this job is still on disk
# overridden

sub InitOnDisk{
  my $self = shift;
}

#===========================================================
# initialize control file
# overridden

sub InitControlFile{
  my $self = shift;
 
}

#===========================================================
# called for batch jobs
# creates QA_report_object
# argument can be 'evaluate_only'  
# or 'no_tables' (run macros and evaluate)

sub DoQA{
  my $self = shift;
  @_ and my $run_option = shift; # e.g. evaluate_only
 
  my $report_key  = $self->ReportKey;
  my $qa_status   = 1;  # either 0 for bad, 1 for good (default)
  # -----
  # run macros
	   
  # clear QAMacros table and output files on disk 
  # unless we're just reevaluating
  unless ($run_option =~ /evaluate_only/){
    QA_db_utilities::ClearQAMacrosTable($self->qaID);
    $self->DeleteQAFiles();
  }

  # read the control file
  # each line corresponds to a macro test file which then
  # determines which macro and tests to run
  
  my $control_file = $self->IOControlFile->Name;
  my $fh           = $self->IOControlFile->Open() or return;

  print h2("<hr>QA for report key $report_key\n");
  print "The time is " . localtime(). "\n". br;
  print h3("Using control file $control_file\n");

  while (my $line = <$fh>){
    
    $line =~ /^\#/ and next; # skip comments

    $line !~ /\S+/ and next; # skip blank lines

    # found the macro test file
    # also known as the test_definition file
    my $macro_test_file = $line;
    print h4("\nMacro test file $macro_test_file\n");

    # create QA_report_object to run macros or do tests
    my $report_obj = QA_report_object->new($report_key,$macro_test_file,
					   $self->LogReport);

    # get the tests and name of macro
    $report_obj->GetTests(); 
    
    # run the macro ? if evaluate_only, no
    $report_obj->RunMacro() unless ($run_option =~ /evaluate_only/);
      
    # evaluate
    $report_obj->EvaluateMacro();
    
    # add qa macro summary to the database
    # returns 0 if something's bad
    QA_db_utilities::WriteQAMacroSummary($self->qaID,$report_obj, $run_option) 
      or $qa_status=0;
    
  }
  close $fh;

  # store the overall qa summary for this job
  QA_db_utilities::WriteQASummary($qa_status, $self->qaID, $control_file);

  # for evaluate only...
  # show the qa evaluation if run from browser
  $self->ShowQA unless $run_option =~ /no_tables/;
}
#==========================================================
# delete the QAFiles before we run macros

sub DeleteQAFiles{

  my $self = shift;

  my $dh         = $self->IOReportDirectory->Open();
  my $report_dir = $self->IOReportDirectory->Name;

  while (defined (my $file = readdir $dh) ){

    my $delete = 0;

    $file =~ /qa_report$/ and $delete = 1;
    $file =~ /evaluation$/ and $delete = 1;
    $file =~ /rootcrashlog$/ and $delete = 1;
    $file =~ /\.ps$/ and $delete = 1;
    $file =~ /\.ps\.gz$/ and $delete = 1;

    $delete or next;

    my $filename = "$report_dir/$file";
    unlink($filename) or print "Cannot delete file $filename <br> \n";
  }

  closedir $dh;
	 
}
#==========================================================
# (first column)
# identifies the job/dataset in the browser  
# overridden

sub DataDisplayString{

  my $self = shift;

  
}
#========================================================
# (second column)
# shows creation time and whether it's on disk

sub CreationString{
  my $self = shift;

  my $creation_time = localtime($self->CreationEpochSec).br;
  
  my $on_disk = 
    ($self->OnDisk ? "<font color = green> (on disk) </font>"  
                   : "<font color = red> (not on disk)</font>");

  return $creation_time.$on_disk;
}
#========================================================
# (third column)
# summary of job information
# wraps around Logreport_object::LogfileSummarystring

sub JobSummaryString{
  my $self = shift;

  return $self->LogReport->LogfileSummaryString;
  
}
#=======================================================
# (fourth column)
# summary of QA info 
# get it from the db

sub QASummaryString{
  my $self = shift;

  my (%seen, $summary_string);
  

  if (! $self->QADone) 
  { 
    $summary_string = "QA not done";
  } 
  else  # qa indeed has been done
  {
    $summary_string = "QA done ".br.$self->QADate.br.br;
    
    # get specific macro info
    # ref is a ref to a 2-d array
    my $ref = QA_db_utilities::GetQAMacrosSummary($self->qaID);
     
    foreach my $macro_ref (@{$ref}) {
     my ($macro, $status, $warnings, $errors) = @{$macro_ref};
      
     # crashed or not run?
     if (($status eq "crashed" or $status eq "not run") and !$seen{$macro})
     {
       $summary_string .= "$macro <font color=red> $status;</font>".br;
       $seen{$macro}++;
     }
     # no tests?
     elsif ($warnings eq 'n/a') {} # do nothing
     
     # errors or warnings
     elsif ($warnings ne '0' or $errors ne '0') 
     {
       $summary_string .= "$macro: $errors <font color=red>errors</font>, ".
	 "$warnings <font color=red>warnings</font>".br;
     }
     # ok
     elsif ($warnings eq '0' and $errors eq '0') 
     {
       $summary_string .= "$macro: <font color=green>O.K.</font>".br;
     }
     else  # something's wrong
     {
       $summary_string .=" $macro: unknown"; 
     }
     
   }
  }

  #-------------------------------------------------------
  # check status of batch jobs: look for batch flags in report directory

  my $report_dir = $self->IOReportDirectory->Name;
  my $dh         = $self->IOReportDirectory->Open;

  while ( defined( my $file = readdir($dh) ) ){

    $file =~ /^\.+$/ and next;
    $file !~ /batch_(\d+)\.(\w+)/ and next;

    my $id = $1;
    my $action = $2;

    my $io_file = new IO_object("BatchScript", $id);
    my $script_name = $io_file->Name();

    if( -e $script_name ){

      $summary_string .= "<br><font color=blue>".
	                 "Batch job $action in progress</font>";
    }
    else{
      # orphaned batch process, clean it up
      my $full_file = "$report_dir/$file";
      unlink($full_file) or print "Cannot delete file $full_file <br> \n";
    }
    
    last;

  }
  closedir($dh);

  #----------------------
  return $summary_string;
}
#========================================================
# (fifth column)
# possible actions on the QA object

sub ButtonString{
  my $self        = shift;

  my $expert_page = $gBrowser_object->ExpertPageFlag; 
  my $report_key = $self->ReportKey;

  my ( $button_string, $button_ref );

  # summary of log file
  $button_ref = Button_object->new('RunDetails', 'Run Details', 
				   $report_key);
  $button_string .= $button_ref   ->SubmitString;
  
  # detailed evaluation of QA if qa if done
  if ( $self->QADone ){ 
    $button_ref = Button_object->new('QaDetails', 'QA Details', 
				     $report_key);
    $button_string .= $button_ref->SubmitString;
  }
  $button_string .= "<br>";

  # files and reports
  $button_ref = Button_object->new('FilesAndReports', 'Files and Reports', 
				   $report_key);
  $button_string .= $button_ref->SubmitString;

  # ??
  $gCGIquery->param('display_env_var') and $self->OnDisk and do{
    $button_ref = Button_object->new('RunDSV', 'Run DSV', $report_key);
    $button_string .= $button_ref->SubmitString;
  };

  $button_string .= "<br>";

  # compare similar reports
  $button_ref = Button_object->new('SetupCompareReport', 'Compare reports', 
				   $report_key);
  $button_string .= $button_ref->SubmitString;
  $button_string .= "<br>";

  # comments
  if ( $gCGIquery->param('enable_add_edit_comments') ) {
    $button_ref = Button_object->new('AddComment', 'Add comment', $report_key);
    $button_string .= $button_ref->SubmitString;
    $button_string .= "<br>";
  }
  
  # for experts : do qa, redo qa, do evaluation
  if ($expert_page){

    if ( $self->QADone ){ 
      $button_ref = Button_object->new('RedoEvaluation', 'Redo Evaluation', 
				       $report_key);
      $button_string .= $button_ref->SubmitString."<br>";

      $self->OnDisk and do {	
	$button_ref = Button_object->new('RedoQaBatch', 'Redo QA (batch)', 
					 $report_key);
	$button_string .= $button_ref->SubmitString;

      };
    }
    else{
      $self->OnDisk and do {	
	$button_ref = Button_object->new('DoQaBatch', 'Do QA (batch)', 
					 $report_key);
	$button_string .= $button_ref->SubmitString;

      };
    }
  }

  # return 
  return $button_string;

}
#========================================================
# summary of parsing of log file
# Run details button

sub DisplayLogReport{
  my $self = shift;

  return $self->LogReport->DisplayLogReport;

}
#========================================================
# QA Details button

sub ShowQA{
  my $self = shift;

  my $report_key = $self->ReportKey;
  my $report_dir = $self->IOReportDirectory->Name;

  # title
  print h2("QA for $report_key\n"); 

  #--------------------------------------------------------

  $self->ShowPsFiles();
#  $self->ShowScalarsAndTests();

  #--------------------------------------------------------
  # pmj 24/6/00
  # new buttons to display scalars and reports in a new browser window

  my $button_ref = Button_object->new('ViewScalarsAndTests', 'Scalars And Tests', 
				   $report_key);
  my $button_string .= $button_ref->SubmitString;

  
  my $script_name   = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print $gCGIquery->startform(-TARGET=>"ScalarsAndTests"); 

  print h3("<hr>Scalars and Tests: \n"); 
  print "View in separate browser window: $button_string.$hidden_string";
  print $gCGIquery->endform;
}
#========================================================
# QA Details: postscript files

sub ShowPsFiles{
  my $self = shift;

  my $report_key = $self->ReportKey;
  my $report_dir = $self->IOReportDirectory->Name;

  #---------------------------------------------------------
  # open the report directory

  print h3("<hr>QA histograms: \n"); 
  
  my $dh = $self->IOReportDirectory->Open;
  
  my @ps_files;

  while (my $file = readdir $dh){
    $file =~ /^\./ and next;

    # print postscript files
    if ($file =~ /\.ps$|\.gz$/) {
      $self->PrintFilestring("Postscript file", $file);
      next;
    }
  }
  close $dh;
}
#========================================================
# QA Details: Scalars and Tests

sub ShowScalarsAndTests{
  my $self = shift;

  my $report_key = $self->ReportKey;
  my $report_dir = $self->IOReportDirectory->Name;
  #---------------------------------------------------------
  # title
  print h2("QA Scalars and Tests for $report_key\n"); 

  #---------------------------------------------------------
  # open the report directory, get evaluation files
  
  my $dh = $self->IOReportDirectory->Open;
  
  my @evalfile_list;

  while (my $file = readdir $dh){
    $file =~ /^\./ and next;

    # save evaluation files
    if ($file =~ /evaluation$/) {
      push @evalfile_list, "$report_dir/$file"; 
      next;
    }
  }
  undef $dh;
  
  #---------------------------------------------------------
  my %eval_hash;

  # retrieve evaluation from storage
  foreach my $file (@evalfile_list) {

    (my $macro_name = basename($file) ) =~ s/\.evaluation//;

    my $ref = retrieve($file) or die "Cannot retrieve $file: $!";
    $eval_hash{$macro_name} = $$ref;
  
  }
  
  #---------------------------------------------------------
  # display run-based scalars, errors and warnings

  print h3("<hr>Run-based scalars, errors and warnings:\n"); 

  foreach my $macro_name (keys %eval_hash){

    my $eval = $eval_hash{$macro_name};
    print h4("Macro: $macro_name\n"); 
    
    QA_report_io::show_scalars_and_test_failures($eval, 'run');
  }

  #---------------------------------------------------------
  # display event-based scalars, errors and warnings

  print h3("<hr>Event-based errors and warnings:\n"); 
  foreach my $macro_name (keys %eval_hash){

    my $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 
    
    QA_report_io::show_scalars_and_test_failures($eval, 'event');
  }

  #---------------------------------------------------------
  # display run-based tests

  print h3("<hr>Run-based tests (all entries):\n"); 

  foreach my $macro_name (keys %eval_hash){

    my $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 

    QA_report_io::show_all_tests($eval, 'run');

  }
  #---------------------------------------------------------
  # display event-based tests

  # disabled because display too long for many events and in any case not very useful
  # pmj 11/11/99

  #print "<hr><h3> Event-based tests (all entries): </h3>\n"; 
  #
  # foreach $macro_name (keys %eval_hash){
  #
  #   $eval = $eval_hash{$macro_name};
  #  print "<h4> Macro: $macro_name </h4> \n"; 
  #
  #   show_all_tests($eval, 'event');
  #}
}

#============================================================================
# 'Files and reports' button

sub DisplayFilesAndReports{
  my $self = shift;
  
  # if on disk, then show the files in the output directory
  if ( $self->OnDisk ) {
    $self->PrintProductionFiles;
  } else { 
    print h2(font({-color=>'orange'}, "Not on Disk\n"));
  }

  print h3("Reports for ",$self->ReportKey,"\n");

  # make a temporary link to the log file
  if ($self->OnDisk) {

    my $logfile = $self->LogReport->LogfileName;

    if (-s $logfile){
      
      my $io = IO_object->new("LogScratchWWW",$logfile);
      my $link = $io->Name;

      my $string = "Logfile (created:" . localtime(stat($logfile)->mtime) . ")";
      QA_cgi_utilities::make_anchor($string, $logfile, $link); 
    }
  }

  # add error and warning files ( if they exist )
  my $warning_string = "StWarning file: ";
  my $error_string   = "StError file: ";
  my $io_warn        = new IO_object("StWarningFile",$self->ReportKey);
  my $io_err         = new IO_object("StErrorFile",$self->ReportKey);

  my $warning_file   = $io_warn->Name;
  my $error_file     = $io_err->Name;

  # links to StWarning and StError files
  $self->PrintFilestring( $warning_string, basename $warning_file )
    if -s $warning_file;
  $self->PrintFilestring( $error_string, basename $error_file )
    if -s $error_file;


  # look in report directory for more files

  my $dh = $self->IOReportDirectory->Open;
  
  my ($logfile, @ps_file, @report, @evaluation, @root_crash);

  while (defined (my $file = readdir $dh ) ){

    next if $file =~ /^\./; # skip dot files

    $logfile = $file, next         if $file =~ /logfile_report/; 
    
    push(@ps_file, $file), next    if $file =~ /ps$|ps\.gz$/;  

    push(@report, $file),  next    if $file =~ /qa_report$/;   

    push(@evaluation, $file), next if $file =~ /evaluation$/; 

    push(@root_crash, $file), next if $file =~ /rootcrashlog$/;

  }

  closedir $dh;

  # links to the control file, and the macro test files.
  $self->ShowControlFiles();

  #----------------------------------------------------------------
  # print links to the ps files

#  $self->ShowPsFiles();

  print h4("Postscript files:\n"); 
  
  foreach my $file (@ps_file){
    $self->PrintFilestring("Postscript file", $file);
  }

  # links to output of the macros
  foreach my $file (@report){  
    $self->PrintFilestring("Report", $file);
  }
  #----------------------------------------------------------------
  # these are for experts only

  # browser created in QA_main
  $gBrowser_object->ExpertPageFlag and do{

    print h4("Other files:\n"); 
    
    $logfile and $self->PrintFilestring("Logfile report", $logfile);
    
    foreach my $file (@evaluation){  
      $self->PrintFilestring("Evaluation", $file);
    }
    
    foreach my $file (@root_crash){  
      $self->PrintFilestring("Root crash", $file);
    }
    
  };

  print hr;
}
#===============================================================================
# make links to the control file and the macro - test files
#
sub ShowControlFiles{
  my $self = shift;

  # Control and Test Files
  # pmj moved here 21/6/00

  # get links to test files  
  print h3("<hr>Control and Macro Definition files:\n");
  
  my $control_file = $self->IOControlFile->Name;

  # get names of directories
  my $io  = new IO_object("ControlDir");
  my $control_dir_local = $io->Name();
  undef $io;
  
  $io = new IO_object("ControlDirWWW");   
  my $control_dir_WWW_local = $io->Name();
  undef $io;      

  # chop off the path 
  (my $base_control = $control_file) =~ s/$control_dir_local//;
  
  # link to control file
  my $control_file_WWW = "$control_dir_WWW_local/$base_control";
  QA_cgi_utilities::make_anchor("Control file", $control_file, $control_file_WWW);
 
  # check if it still exists on disk
  if ( -e $control_file )
  {
    my $fh = $self->IOControlFile->Open;
   
    while (my $test_file = <$fh>){
      
      $test_file =~ /^\#/ and next; # skip comments
      $test_file !~ /\S+/ and next; # skip blank lines
      
      (my $base_test = $test_file) =~ s/$control_dir_local//;
      my $test_file_WWW = "$control_dir_WWW_local/$base_test";

      # link to macro definition file
      QA_cgi_utilities::make_anchor("Macro Definition file", $test_file, 
				    $test_file_WWW);
    }
    close $fh;
  }
  else
  {
    print "Control file $control_file does not exist <br> \n";
  }
}

#===============================================================================

sub PrintFilestring{
  my $self   = shift;
  my $string = shift;
  my $file   = shift;

  my $report_dir = $self->IOReportDirectory->Name;

  my $filename = "$report_dir/$file";
  
  # double check if the files are on disk
  # there's some trouble with disks not being mounted, etc
  
  if (not -e $filename){
    print h4(font({-color=>'red'},"$filename is not on disk?"));
    return;
  }

  my $time     = stat($filename)->mtime;
  $string     .= " (created:".localtime($time).")";

  if ( $file =~ /\.(evaluation|obj)$/){ # no link to these files
    print "$string $filename <br> \n";
  }
  else{
    my $report_dir_WWW = $self->ReportDirectoryWWW;
    my $filename_WWW   = "$report_dir_WWW/$file";
    QA_cgi_utilities::make_anchor($string, $filename, $filename_WWW);
  }

  return;
}
#==========================================================
# print the .root files in the production output directory

sub PrintProductionFiles{

  my $self = shift;
 
  my @table_heading = ('File name', 'Size (bytes)', 'Created');
  my @table_rows    = th(\@table_heading);

  # get the production files (full path)
  foreach my $file (@{$self->LogReport->ProductionFileListRef}){

    # double check that the files are accessible
    if (not -e $file ){
      print h4(font({-color=>'red'},"$file is not on disk?"));
      return;
    }

    my $time = localtime(stat($file)->mtime);
    my $size = stat($file)->size;
    push @table_rows, td([$file, $size, $time]);
  }

  print h3("Files in ",$self->ProductionDirectory);
  print table( {-border=>undef}, Tr(\@table_rows));

}
#==========================================================
# create the log report object
# overridden

sub NewLogReportObject{
  my $self = shift;
}
#==========================================================
# create the logreport_object and set the pointer

sub UpdateLogReport{
  my $self = shift;

  my $filename   = $self->LogReportStorable;
  my $report_key = $self->ReportKey;
  my $report_dir = $self->IOReportDirectory->Name;

  my $io = new IO_object("TopDir");
  my $topdir_local = $io->Name;
  
  # tell them we're updating
  print font({-color=>'red'} ,
     "Found new job($report_key) for ",$gDataClass_object->DataClass,".\n"),br;;
  
  # make new report dir
  print h4("Making directory: $report_dir\n");
  mkdir $report_dir, 0775;

  # create Logreport_object_offline, nightly, or online, etc

  my $logreport_ref = $self->NewLogReportObject() or return;
  
  print h4("Writing Logreport object to $filename...\n");
      
  # set it
  $self->{_LogReport} = $logreport_ref;

  # store it
  store( $logreport_ref, $filename) 
    or die h4("Cannot write $filename: $! \n");
  
  # ok?
  if ( -e $filename )
  {
    print h4(" ... done\n"); chmod 0664, $filename; 
  } 
  else 
  {
    print h4("file $filename not created, something's wrong.\n"); 
    return;
  }
}
#=========================================================
# retrieve the Logreport_object from disk

sub GetLogReport{
  my $self = shift;
  
  # retrieve Logreport object from file
  my $filename =  $self->LogReportStorable;
  
  # check for existence
  # it's possible that the db has been updated
  # but has not finished parsing the job

  if ( -e $filename )
  {
    $self->{_LogReport} = retrieve($filename);
  }
  else
  {
    print h3("<font color=red>Cannot find $filename<br>\n",
	     "It's possible that the db has been updated, ",
	     "but the logfile has not been parsed</font>\n"); 
    return; 
  }
  
}
#=========================================================
# -------------- hard coded accessors  -------------------

sub JobID{
  my $self = shift;
  $self->{_JobID} = shift if @_;
  return $self->{_JobID};
}

sub qaID{
  my $self = shift;
  $self->{_qaID} = shift if @_;
  return $self->{_qaID};
}

sub ReportKey{
  my $self = shift;
  $self->{_ReportKey} = shift if @_;
  return $self->{_ReportKey};
}

sub IOReportDirectory{
  my $self = shift;
  $self->{_IOReportDirectory} = shift if @_;
  return $self->{_IOReportDirectory};
}

sub ReportDirectoryWWW{
  my $self = shift;
  $self->{_ReportDirectoryWWW} = shift if @_;
  return $self->{_ReportDirectoryWWW};
}
	
sub OnDisk{
  my $self = shift;
  $self->{_OnDisk} = shift if @_;
  return $self->{_OnDisk};
}

sub LogReportStorable{
  my $self = shift;
  $self->{_LogReportStorable} = shift if @_;
  return $self->{_LogReportStorable};
}

sub ProductionDirectory{
  my $self = shift;
  $self->{_ProductionDirectory} = shift if @_;
  return $self->{_ProductionDirectory};
}

sub CreationEpochSec{
  my $self = shift;
  $self->{_CreationEpochSec} = shift if @_;
  return $self->{_CreationEpochSec};
}

# pointer to Logreport_object
sub LogReport{
  return $_[0]->{_LogReport};
}

sub IOControlFile{
  my $self = shift;
  $self->{_IOControlFile} = shift if @_;
  return $self->{_IOControlFile};
}

sub QADone{
  my $self = shift;
  $self->{_QADone} = shift if @_;
  return $self->{_QADone};
}

sub QADate{
  my $self = shift;
  $self->{_QADate} = shift if @_;
  return $self->{_QADate};
}

# pmj 4/6/00
sub CompareReport_obj{
  my $self = shift;
  $self->{_CompareReport_obj} = shift if @_;
  return $self->{_CompareReport_obj};
}

#---------------------------------------------------------
1;
