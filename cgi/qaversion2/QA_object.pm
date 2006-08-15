#! /opt/star/bin/perl 

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
use QA_db_utilities qw(:db_globals);
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
    _qaID                => undef, # identifies the qa job
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
    _QADate              => undef,  # date the QA was done  
    _QAAnalyzed          => undef  # analyzed by shift?
  );
#========================================================
# 
sub new{
  my $proto = shift;
  my $classname = ref($proto) || $proto;

  # this object should never be created
  $classname eq __PACKAGE__ and
    die __PACKAGE__, " should not be instantiated\n";
 
  my $self = {};

  bless ($self, $classname);

  # initialize
  $self->_init(@_) or return;

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
      print h3("<font color=red>Error - Erasing Job...</font>"),br,"\n";
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

  $self->{_JobID} = $self->LogReport->JobID;
  $self->{_qaID}  = $self->LogReport->qaID;
  $self->{_ProductionDirectory} = $self->LogReport->OutputDirectory;

  # convert creation time to epoch seconds
  my $time_temp = $self->LogReport->JobCompletionTimeAndDate;
  $self->{_CreationEpochSec} = 
    QA_utilities::datetime_to_epochsec($time_temp);

  # has QA been done or not?
  $self->{_QADone} = QA_db_utilities::GetFromQASum($QASum{QAdone}, 
						   $self->ReportKey);
  $self->{_QADate} = QA_db_utilities::GetFromQASum($QASum{QAdate}, 
						   $self->ReportKey);
  $self->{_QAAnalyzed} = QA_db_utilities::GetFromQASum($QASum{QAanalyzed},
						      $self->ReportKey);

  # is data on disk? - see derived classes
  
  $self->InitOnDisk();

  # control file initialized 
  #$self->InitControlFile();

  1;
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

  $self->InitControlFile();
	   
  # clear QAMacros table and output files on disk 
  # unless we're just reevaluating
  unless ($run_option =~ /evaluate_only/){
    QA_db_utilities::ClearQAMacrosTable($self->qaID);
    QA_db_utilities::FlagQAInProgress($self->qaID);
    $self->DeleteQAFiles();
  }

  # read the control file
  # each line corresponds to a macro test file which then
  # determines which macro and tests to run
  
  my $control_file = $self->IOControlFile->Name;
  my $fh           = $self->IOControlFile->Open() or do {
    QA_db_utilities::ResetInProgressFlag($self->qaID);
    return;
  };

  my $string = CompareReport_utilities::RunIdentificationString($report_key);
  print h2("<hr>QA for $string\n");
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
    
    # add qa macro summary to the database.
    # WriteQAMacroSummary returns 0 if something's bad
    
    my $macroStatus = 
      QA_db_utilities::WriteQAMacroSummary($self->qaID,$report_obj, 
					   $run_option);
    $qa_status = 0 if !$macroStatus;
       
  }
  close $fh;

  # store the overall qa summary for this job
  QA_db_utilities::WriteQASummary($qa_status, $self->qaID, $control_file);

  # offline_fast requires us to communicate back with the DAQInfo db.
  $self->WrapUpQA();

  # for evaluate only...
  # show the qa evaluation if run from browser
  $self->ShowQA unless $run_option =~ /no_tables/;
}
#==========================================================
sub WrapUpQA{
  my $self=shift;
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

  my $creation_time = $self->LogReport->JobCompletionTimeAndDate.br;
  
  #my $on_disk = 
  #  ($self->OnDisk ? "<font color = green> (on disk) </font>"  
  #                 : "<font color = red> (not on disk)</font>");
  my $on_disk;
  if($self->OnDisk()>0){
    $on_disk="<font color = green> (on disk) </font>";
  }
  elsif($self->OnDisk()==0){
    $on_disk="<font color = red> (not on disk)</font>";
  }
  else{
    $on_disk="<font color = blue> (on disk unknown) </font>";
  }

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

  my $show_log_link = 0;
     
  if ($self->QADone eq 'N') 
  { 
    $summary_string = "QA not done";
  } 
  elsif ( $self->QADone eq 'Y')  # qa indeed has been done
  {
    $summary_string = "QA done ".br.$self->QADate.br;

    # analyzed or not?
    if($self->QAAnalyzed eq 'Y'){
      $summary_string .= "<font color=green>analyzed by shift</font>".br.br;
    }
    else{
      $summary_string .= "<font color=blue>Not analyzed by shift</font>".br.br;
    } 
      

    # get specific macro info
    # ref is a ref to a 2-d array
    my $ref = QA_db_utilities::GetQAMacrosSummary($self->qaID);

    foreach my $macro_ref (@{$ref}) {
     my ($macro, $status, $warnings, $errors) = @{$macro_ref};
      
     $status eq "crashed" and $show_log_link = 1;

     # sometimes, the macro summary is inserted twice
     # for some reason.  let's always suppress duplications...

     next if $seen{$macro}++;

     # crashed or not run?
     if (($status eq "crashed" or $status eq "not run"))
     {
       $summary_string .= "$macro <font color=red> $status;</font>".br;
       #$seen{$macro}++;
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
  } # qa in progress
  else { $summary_string .= "QA in progress\n"}


  if ( $show_log_link ) {
    
    # find the HTML file and make the link
    my $outputFullHTML = IO_object->new("BatchLogHTML", $self->ReportKey)->Name();
    my $outputHTML     = basename($outputFullHTML);
    
    # first need the WWW report directory
    my $report_dir = $self->IOReportDirectory->Name();
    
    if (-s "$report_dir/$outputHTML") {
      
      my $linkdirWWW = $self->ReportDirectoryWWW;
      my $linkWWW    = "$linkdirWWW/$outputHTML";
      
      $summary_string .= $gCGIquery->a({-href=>$linkWWW,
				        -target=>'display'}, $outputHTML);
      $summary_string .= br;
      
    }
  }


  #-------------------------------------------------------
  # check status of batch jobs: look for batch flags in report directory

  my $report_dir = $self->IOReportDirectory->Name;
  my $dh         = $self->IOReportDirectory->Open;

  # ben(10jul00):  logic needs to change here, in case there are more than
  # one .do_qa file hanging about from bad jobs.

  # first find all flag files, keeping track of the latest
  my @flag_files = ();
  my $latest_flag = -1;   # which index in flag_files is latest
  while ( defined( my $file = readdir($dh) ) ){
    $file =~ /^\.+$/ and next;
    $file !~ /batch_(\d+)\.(\w+)/ and next;

    push @flag_files, $file;
    
    if ($#flag_files < 1 ||                         # first flag found
	-M $file > -M $flag_files[$latest_flag]){   # newest flag found
	$latest_flag = $#flag_files;
    }
  }
  
  # delete any old flag files
  for(my $i = 0; $i <= $#flag_files; $i++){
      $i == $latest_flag && next;
      unlink("$report_dir/".$flag_files[$i]);
  }

  # now process the latest one found
  if ($latest_flag >= 0){

    my $file = $flag_files[$latest_flag];
    $file =~ /batch_(\d+)\.(\w+)/;

    my $id = $1;
    my $action = $2;

    my $io_file = new IO_object("BatchScript", $id);
    my $script_name = $io_file->Name();

    if( -e $script_name and $self->QADone eq 'in progress'){

      local *flagFH;
      open(flagFH, "$report_dir/$file") or print "Cannot open $file\n";
      my $text = <flagFH>;

      my ($batch_mode, $jobID) = $text =~ /(\D+)(\d+)/;

      if ($batch_mode =~ /LSF/){
	
	my $lsfTool = "LSF_tool?jobID=$jobID&markedJobs=$jobID";
	#BEN: pass on expert privileges, if any, to LSF_tool
	$lsfTool .= "&expertPW=".$gCGIquery->param("expert_pw");
	my $lsfToolURL = $gCGIquery->script_name;
	$lsfToolURL =~ s/QA_main\.pm/$lsfTool/e;
	$summary_string .= $gCGIquery->a({-href=>$lsfToolURL,
					  -target=>"_blank"}, "LSF status");
      }

      close flagFH;
      
      $summary_string .= "<br><font color=blue>".
	                 "$batch_mode batch job $action in progress</font>";
      
    }
    else{
      # orphaned batch process, clean it up
      my $full_file = "$report_dir/$file";
      unlink($full_file) or print "Cannot delete file $full_file <br> \n";
    }
    
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
  $button_string .= $button_ref->SubmitString;
  
  # detailed evaluation of QA if qa if done
  if ( $self->QADone eq 'Y' ){ 
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
  if ( $self->QADone eq 'Y'){
    $button_ref = Button_object->new('DoCompareToReference', 
				     'Compare to reference', $report_key);
    $button_string .= $button_ref->SubmitString . br;
    $button_ref = Button_object->new('SetUserReference', 
				     'Add to references', $report_key);
    $button_string .= $button_ref->SubmitString . br;
    
  }
  # comments
  if ( $gCGIquery->param('enable_add_edit_comments') ) {
    $button_ref = Button_object->new('AddComment', 'Add comment', $report_key);
    $button_string .= $button_ref->SubmitString;
    $button_string .= "<br>";
  }
  
  
  

  # for experts : do qa, redo qa, do evaluation
  if ($expert_page){

    if ( $self->QADone eq 'Y' ){ 
      $button_ref = Button_object->new('RedoEvaluation', 'Redo Evaluation', 
				       $report_key);
      $button_string .= $button_ref->SubmitString."<br>";

      $self->OnDisk and do {	
	$button_ref = Button_object->new('RedoQaBatch', 'Redo QA (batch)', 
					 $report_key);
	$button_string .= $button_ref->SubmitString."<br>";

      };
    }
    elsif ($self->QADone eq 'N'){
      $self->OnDisk and do {	
	$button_ref = Button_object->new('DoQaBatch', 'Do QA (batch)', 
					 $report_key);
	$button_string .= $button_ref->SubmitString."<br>";

      };
    }
    elsif ($self->QADone eq 'in progress'){
      $button_ref = Button_object->new('ResetInProgress', 'Reset in progress', 
				       $report_key);
      $button_string .= $button_ref->SubmitString."<br>";

    }
  }

  # set analyzed (by shift member)
  if($self->QADone eq 'Y'){
    my ($title,$value);
    if($self->QAAnalyzed eq 'Y'){
      $title = "Unset QA Analyzed"; $value = 'N';
    }
    elsif($self->QAAnalyzed eq 'N'){
#     $button_ref = Button_object->new('StartQAReport','Start QA report',
#                                      $report_key,$self->qaID(),$value);
#     $button_string .= $button_ref->SubmitString."<br>";
      $title = "Set QA Analyzed"; $value = 'Y';
    }
    $button_ref = Button_object->new('RequestQAAnalyzed',$title,
				     $report_key,$self->qaID(),$value);
    $button_string .= $button_ref->SubmitString."<br>";

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
  my $string = CompareReport_utilities::RunIdentificationString($report_key);
  print h2("QA for $string\n"); 

  #--------------------------------------------------------

  $self->ShowPsFiles();

  #--------------------------------------------------------
  # pmj 26/8/00: New logic for presenting scalars and tests:
  # generate one button per table here so user gets overview and
  # only selected table gets displayed in secondary window

  # bum 07/25/2001
  # before we try showing the scalars, make sure the 
  # evaluation files actually exists.

  my @ary = $self->EvaluationFileList();
  if(scalar @ary<1){
    print h2("No qa scalar evaulation done");
    return;
  }

  my $button_string_runscalars = $self->MultClassButtonString('ViewScalarsAndTests', 'run_scalars');

  #---
  # expert page - show event-wise scalars and all tests

  my $expert_page = $gBrowser_object->ExpertPageFlag; 
  my $button_string_evtscalars_tests;

  $expert_page and
    $button_string_evtscalars_tests = $self->MultClassButtonString('ViewScalarsAndTests', 'evtscalars_tests');
  #---

  my $hidden_string = $gBrowser_object->Hidden->Parameters;
  
  print $gCGIquery->startform(-TARGET=>"ScalarsAndTests"); 
  
  print "<hr>",Browser_utilities::ScalarDocumentationString(),"<br>\n";

  print h3("Run-averaged Scalars: \n"); 

  print "$button_string_runscalars";

  if ($expert_page){
    print h3("<hr>Event-wise Scalars and All Tests: \n"); 
    print "$button_string_evtscalars_tests";
  }

  print $hidden_string;
  print $gCGIquery->endform;
}
#========================================================
# QA Details: postscript files

sub ShowPsFiles{
  my $self = shift;

  my $report_key = $self->ReportKey();

  #print "ShowPsFiles: ReportKey=$report_key<br>\n";
  #-------------------------------------------------------------
  my @filelist_ordered = $self->GetPSFiles();
  #-------------------------------------------------------------

  print "<hr>",Browser_utilities::HistogramDocumentationString(),"<br>\n";

  print h4("<font color=red>QA histograms for shift crew:</font> \n"); 
  #-------------------------------------------------------------
  print "<font color=green>This run: ",
  CompareReport_utilities::RunIdentificationString($report_key),
  "</font><br>\n";

  foreach my $file (@filelist_ordered){
   $file =~ /shift/ or next;
   $self->PrintFilestring("Postscript file", $file);
  }
  #-------------------------------------------------------------
  my @refKeys;
  
  if($gDataClass_object->DataClass() !~ /offline_fast/){
    @refKeys= CompareReport_utilities::GetReferenceList($report_key);
  }
  foreach my $ref_key (@refKeys){

    my @ref_filelist = $self->GetPSFiles($ref_key);

    scalar @ref_filelist and do{
      print "<br>Reference run: ",
      CompareReport_utilities::RunIdentificationString($ref_key),"<br>\n";

      foreach my $file (@ref_filelist){
	$file =~ /Shift/ or next;
	$self->PrintFilestring("Postscript file", $file, $ref_key);
      }

    };
  }

  #-------------------------------------------------------------
  print h4("<hr>Other QA histograms for this run: \n"); 

  foreach my $file (@filelist_ordered){
   $file !~ /Shift/ or next;
   $self->PrintFilestring("Postscript file", $file);
  }

  #-------------------------------------------------------------

}
#========================================================
# returns ordered list of ps files for specified report key
# if no argument given, returns ps files for this QA_object;

sub GetPSFiles{

  my $self = shift;
  my $foreign_report_key = shift;

  #-----------------------------------------------------------
  
  my $report_key;
  if ($foreign_report_key){
    $report_key = $foreign_report_key;

    # make the QA_objects in case it doesn't exist
    QA_utilities::make_QA_objects($foreign_report_key);
  }
  else{
    $report_key = $self->ReportKey;
  }

  #---------------------------------------------------------
  # get ps files from directory

  my $dh = $QA_object_hash{$report_key}->IOReportDirectory->Open;
  
  # pmj 28/7/00
  # force ordering of ps files

  my @filelist_unordered;
  while (my $file = readdir $dh){
    $file =~ /^\./ and next;

    # print postscript files
    if ($file =~ /\.ps$|\.gz$/) {
      push @filelist_unordered, $file;
      next;
    }
  }
  close $dh;
  #---------------------------------------------------------
  # order them

  my @filelist_ordered = sort { order_ps_files() } @filelist_unordered;
  #---------------------------------------------------------
  return @filelist_ordered;
}

#========================================================
sub order_ps_files{

  $a =~ /Shift/ and return -1;
  $b =~ /Shift/ and return 1;

  $a =~ /QA/ and return -1;
  $b =~ /QA/ and return 1;

  $a =~ /StEvent/ and return -1;
  $b =~ /StEvent/ and return 1;

  return 0;
}

#========================================================
# QA Details: Scalars and Tests

sub ShowScalarsAndTests{
  my $self = shift;

  my $file = shift;
  my $macro_name  = shift;
  my $mult_class = shift;

  my $flag = shift;
  #---------------------------------------------------------

  my $ref = retrieve($file) or die "Cannot retrieve $file: $!";
  my $eval = $$ref;

  my ($mult_low, $mult_high) = $eval->MultClassLimits($mult_class);

  #---------------------------------------------------------
  my $report_key = $self->ReportKey;
  my $report_dir = $self->IOReportDirectory->Name;
  #---------------------------------------------------------
  # title

  my $title;

  if (  $gDataClass_object->DataClass =~ /offline_real/ ){
    $title = "QA Scalars for Run ID ".
      $self->LogReport->RunID.", File Seq ".$self->LogReport->FileSeq;
  }
  else{
    $title = "QA Scalars for $report_key"; 
  }

  print h2($title);
  
  #---------------------------------------------------------
  # display run-based scalars, errors and warnings

 SWITCH: {

    $flag =~ /run_scalars/ and do{
      print h3("<hr>Run-based scalars, errors and warnings:\n"); 
      print h4("Macro: $macro_name\n"); 
      print h4("Multiplicity class: $mult_class; track node limits = ($mult_low, $mult_high)"); 
      QA_report_io::show_scalars_and_test_failures($eval, $mult_class, 'run');
      last SWITCH;
    };

    $flag =~ /evtscalars_tests/ and do{

      print h3("<hr>Event-based errors and warnings:\n"); 
      print "<h4> Macro: $macro_name </h4> \n"; 
      print h4("Mulitplicity class: $mult_class; track node limits = ($mult_low, $mult_high)"); 
      QA_report_io::show_scalars_and_test_failures($eval, $mult_class, 'event');
      
      print h3("<hr>Run-based tests (all entries):\n"); 
      print "<h4> Macro: $macro_name </h4> \n"; 
      print h4("Mulitplicity class: $mult_class; track node limits = ($mult_low, $mult_high)"); 
      QA_report_io::show_all_tests($eval, $mult_class, 'run');

      last SWITCH;
    };
  }
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
  # Cant access anymore bum 07/25/2001
  if ($self->OnDisk) {

    my $logfile = $self->LogReport->LogfileName;

    # just show them where it is.
    print "Logfile : $logfile<br>\n";

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
  
  my ($logfile, @ps_file, @report, @evaluation, @root_crash, $batchlog);

  while (defined (my $file = readdir $dh ) ){

    next if $file =~ /^\./; # skip dot files
    $logfile = $file,         next if $file =~ /logfile_report/; 
#    push(@ps_file, $file),    next if $file =~ /ps$|ps\.gz$/;  
    push(@report, $file),     next if $file =~ /qa_report$/;   
    push(@evaluation, $file), next if $file =~ /evaluation$/; 
    push(@root_crash, $file), next if $file =~ /rootcrashlog$/;
    $batchlog = $file,        next if $file =~ /html$/;
  }
  closedir $dh;

  
  #----------------------------------------------------------------
  # print links to the ps files
 
  $self->ShowPsFiles();

#  foreach my $file (@ps_file){
#    $self->PrintFilestring("Postscript file", $file);
#  }

  print h4("Output of macros:\n");

  foreach my $file (@report){  
    $self->PrintFilestring("Report", $file);
  }
  #----------------------------------------------------------------
  # these are for experts only

  # browser created in QA_main
  $gBrowser_object->ExpertPageFlag and do{

    # links to the control file, and the macro test files.
    $self->ShowControlFiles();

    print h4("Other files:\n"); 
    
    $logfile and $self->PrintFilestring("Logfile report", $logfile);
    
    foreach my $file (@evaluation){  
      $self->PrintFilestring("Evaluation", $file);
    }
    
    foreach my $file (@root_crash){  
      $self->PrintFilestring("Root crash", $file);
    }
    
    $self->PrintFilestring("Batch log", $batchlog);
    
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
  
  my $control_file = QA_db_utilities::GetFromQASum('controlFile',
						   $self->ReportKey());
						   

  # get names of directories
  if( -e $control_file){
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

    local *FH;
    if(open(FH,$control_file)){
   
      while (my $test_file = <FH>){
	
	$test_file =~ /^\#/ and next; # skip comments
	$test_file !~ /\S+/ and next; # skip blank lines
	
	(my $base_test = $test_file) =~ s/$control_dir_local//;
	my $test_file_WWW = "$control_dir_WWW_local/$base_test";
	
	# link to macro definition file
	QA_cgi_utilities::make_anchor("Macro Definition file", $test_file, 
				      $test_file_WWW);
      }
      close FH;
    }
    else {print h4("Cannot open $control_file");}
  }
  else
  {
    print "Control file $control_file does not exist <br> \n"
      unless $control_file eq 'n/a';
  }
}

#===============================================================================

sub PrintFilestring{
  my $self   = shift;
  my $string = shift;
  my $file   = shift;

  # optional arg for report key; default is this object
  my $report_key = shift;
  $report_key or $report_key = $self->ReportKey();
    
  #--------------------------------------------------------------------

  my $report_dir = $QA_object_hash{$report_key}->IOReportDirectory->Name;

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
    my $report_dir_WWW = $QA_object_hash{$report_key}->ReportDirectoryWWW;
    my $filename_WWW   = "$report_dir_WWW/$file";
    QA_cgi_utilities::make_anchor($string, $filename, $filename_WWW);
  }

  return;
}
#==========================================================
# print the .root files in the production output directory

sub PrintProductionFiles{

  my $self = shift;
 
  my @table_heading = ('File name');
  my @table_rows    = th(\@table_heading);

  # get the production files (full path)
  foreach my $file (@{$self->LogReport->ProductionFileListRef}){

    # bum 7/25/2001 - cant read from disk anymore
    #if (not -e $file ){
    #  print h4(font({-color=>'red'},"$file is not on disk?"));
    #  return;
    #}

    # get size from database
    #my $size = QA_db_utilities::GetFromFileCatalog('size',$self->JobID);
    push @table_rows, td([$file]);
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
  
  print font({-color=>'red'} ,
     "Found new job($report_key) for ",
	     $gDataClass_object->DataClass,".\n"),br;;

  # make new report dir
  print h4("Making directory: $report_dir\n");
  mkdir $report_dir, 0775;

  # just check for existence since it may already have been created before
  if(!-d $report_dir){
    print "Cannot create the report directory $report_dir: $!";
    return;
  }
  else{
    print "...done\n";
  }

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

    print h3("<font color=orange>",$self->ReportKey,
	     " is currently being updated?</font>\n");

#    print h3("<font color=red>Cannot find $filename<br>\n",
#	     "It's possible that the db has been updated, ",
#	     "but the logfile has not been parsed</font>\n"); 
    return; 
  }
  
}
#=========================================================
sub EvaluationFileList{

  my $self = shift;

  my $report_dir = $self->IOReportDirectory->Name;

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
  return @evalfile_list;
}
#=========================================================
sub MultClassLabels{

  my $self = shift;

  exists $self->{_MultClassLabels} or do{

    my @evalfile_list = $self->EvaluationFileList();
    
    # look at one evaluation file to extract multiplcity classes
    my $file = $evalfile_list[0];
    my $ref = retrieve($file) or die "Cannot retrieve $file: $!";
    my $eval = $$ref;
    @{$self->{_MultClassLabels}} = $eval->MultClassLabels();

  };

  return @{$self->{_MultClassLabels}};
}
#=========================================================
sub MultClassLimits{

  my $self = shift;
  my $mult_class = shift;
  
  exists $self->{_MultClassLimits}->{$mult_class} or do{

    my @evalfile_list = $self->EvaluationFileList();
    
    # look at one evaluation file to extract multiplcity classes
    my $file = $evalfile_list[0];
    my $ref = retrieve($file) or die "Cannot retrieve $file: $!";
    my $eval = $$ref;

    my ($low, $high) = $eval->MultClassLimits($mult_class);

    @{$self->{_MultClassLimits}->{$mult_class}} = ($low, $high);
  };

  return @{$self->{_MultClassLimits}->{$mult_class}};
}
#=========================================================
sub MultClassButtonString{

  # returns string for printing buttons for all available macros and multiplicity classes

  my $self = shift;
  my $ButtonSub = shift;
  @_ and my @args = @_;

  #-----------------------------------------------------------
  my $button_string;
  my $report_key = $self->ReportKey;
  #-----------------------------------------------------------

  my @evalfile_list = $self->EvaluationFileList();

  my @mult_class_list = $self->MultClassLabels();

  foreach my $mult_class (@mult_class_list){
    my ($low, $high) =  $self->MultClassLimits($mult_class);
    $button_string .= "Multiplicity class: $mult_class; track node limits ($low, $high)<br>\n";
  }


  #-----------------------------------------------------------------------------------
  # first the scalars for shift crews

  $button_string .= "<br><font color=red>Scalars for QA shift crew:</font>\n";

  foreach my $file (@evalfile_list) {
    (my $macro_name = basename($file) ) =~ s/\.evaluation//;

    $macro_name =~ /eventBranch/ or next;

    $button_string .= "<br>";
    foreach my $mult_class (@mult_class_list){
      my $button_label = "$macro_name";
      $mult_class ne 'none' and $mult_class ne 'mc' and $button_label .= " $mult_class";

      my $button_ref = Button_object->new( $ButtonSub, $button_label, 
					   $report_key, $file, $macro_name, $mult_class, @args);
      $button_string .= $button_ref->SubmitString;
    }
  }
  #-----------------------------------------------------------------------------------
  # now all the rest

  $button_string .= "<br><br>Other scalars:\n";

  foreach my $file (@evalfile_list) {
    (my $macro_name = basename($file) ) =~ s/\.evaluation//;

    $macro_name !~ /eventBranch/ or next;

    $button_string .= "<br>";
    foreach my $mult_class (@mult_class_list){
      my $button_label = "$macro_name";
      $mult_class ne 'none' and $mult_class ne 'mc' and $button_label .= " $mult_class";

      my $button_ref = Button_object->new( $ButtonSub, $button_label, 
					   $report_key, $file, $macro_name, $mult_class, @args);
      $button_string .= $button_ref->SubmitString;
    }
  }
  #-----------------------------------------------------------------------------------
  return $button_string;

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

sub QAAnalyzed{
  my $self = shift;
  $self->{_QAAnalyzed} = shift if @_;
  return $self->{_QAAnalyzed};
}


# pmj 4/6/00
sub CompareReport_obj{
  my $self = shift;
  $self->{_CompareReport_obj} = shift if @_;
  return $self->{_CompareReport_obj};
}

#---------------------------------------------------------
1;
