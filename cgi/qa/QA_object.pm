#! /usr/bin/perl

# first try at a QA object
# pmj 29/7/99
#========================================================
package QA_object;
#========================================================
use CGI qw/:standard :html3 -no_debug/;
use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;

use Data::Dumper;

use QA_globals;
use QA_logfile_report;
use QA_make_reports;
use QA_cgi_utilities;
use QA_report_io;

#--------------------------------------------------------
1;
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
  
  # if no directory supplied as argument, return
  return unless @_;

  #-------------------------------------------------
  # get report names
  
  # is this a data or report directory?
  
  my $arg_dir = shift;
  
  undef $report_key;
  my $this_is_data = 0;

 DIRTYPE: {

    foreach $topdir (@topdir_data){

      $arg_dir =~ /$topdir/ and do{
	$report_key = QA_make_reports::get_report_key($arg_dir); 
	$this_is_data = 1;
	last DIRTYPE
      };
    }    
    
    $arg_dir =~ /$topdir_report/ and do{
      my $temp = $arg_dir;
      my $temp1 = dirname($arg_dir)."/";
      $temp =~ s/$temp1//;
      $report_key = $temp; 
      last DIRTYPE
    };

    $temp_dir = $topdir_report."/".$arg_dir;
    -d $temp_dir and do{
      $report_key = $arg_dir;
      last DIRTYPE
    };

    print "<h4> Error in QA_object constructor: unknown argument $arg_dir </h4> \n";
    return;
  }
  #------------------------------------------------------
  $self->ReportKey($report_key);
  $self->ReportDirectory($report_key);
  #------------------------------------------------------
  $logfile_report = $self->LogfileReportName($report_key);
  #------------------------------------------------------

  # second argument upon initialization: update log file, do qa, etc.

  if (@_){

    $action = shift;

    $action =~ /update/ and $this_is_data and do{
      QA_make_reports::make_report_directory($report_key);
      QA_logfile_report::make_logfile_report($arg_dir, $logfile_report);
    };

  }
  #------------------------------------------------------

  -e $logfile_report  and do{
    $self->LogfileReportData($logfile_report);
  };
  #------------------------------------------------------
  # set QA control file

  $control_file = "unknown";

 CONTROLFILE: {

    $report_key =~ /year_1b/ and do{
#      $control_file = "/star/u2/jacobs/QA/cgi/development/control_and_test/test_control.year_1b.txt";
      $control_file = "$control_dir/test_control.year_1b.txt";
      last CONTROLFILE;
    };

    $report_key =~ /year_2a/ and do{
#      $control_file = "/star/u2/jacobs/QA/cgi/development/control_and_test/test_control.year_2a.txt";
      $control_file = "$control_dir/test_control.year_2a.txt";
      last CONTROLFILE;
    };
    
  }

  $self->ControlFile($control_file);

  #------------------------------------------------------

  $self->QASummaryString($report_key);

  #------------------------------------------------------
  # is data on disk?

  $self->OnDisk($report_key);

}
#========================================================
sub ReportKey{
  my $self = shift;
  if (@_) {$self->{report_key} = shift }
  return $self->{report_key};
}
#========================================================
sub ReportDirectory{

  my $self = shift;

  if (@_){
    my $report_key = shift;
    $self->{report_directory} = $topdir_report."/".$report_key;
    $self->{report_directory_WWW} = $topdir_report_WWW."/".$report_key;
  }

  return $self->{report_directory};
}
#========================================================
sub ReportDirectoryWWW{

  my $self = shift;

  if (@_){
    my $report_key = shift;
    $self->ReportDirectory($report_key);
  }

  return $self->{report_directory_WWW};
}
#========================================================
sub LogfileReportData{
  my $self = shift;
  if (@_) {
    $self->{logfile_report_data} = { QA_logfile_report::get_logfile_report(shift) } ;
  }
  
  return $self->{logfile_report_data};
}
#========================================================
sub ControlFile{
  my $self = shift;
  if (@_) {
    $self->{control_file} = shift;
  }
  
  return $self->{control_file};
}
#===========================================================
sub QASummaryFileName{

  my $self = shift;
  my $report_dir = $self->ReportDirectory;
  return $report_dir."/qa_summary.txt";
}
#===========================================================
sub WriteQASummary{

  my $self = shift;
  $summary_string = shift;

  #---------------------------------------------------------

  my $qa_summary_file = $self->QASummaryFileName;
  my $control_file = $self->ControlFile;

  open QASUMMARY, ">$qa_summary_file" or die "Cannot open qa summary file $qa_summary_file: $!\n"; 

  print QASUMMARY "Control file: $control_file \n";
  print QASUMMARY "Summary string: $summary_string";

  close QASUMMARY;

  return;
}
#========================================================
sub QASummaryString{

  my $self = shift;

  my $qa_summary_file = $self->QASummaryFileName;

  #-----------------------------------------------------
  if ( -s $qa_summary_file ) {
    
    open QAFILE, $qa_summary_file or die "Cannot open qa summary file $qa_summary_file: $! \n";
    
    undef my $string;
    
    while ($line = <QAFILE>){

      $line =~ /Summary string:/ or next;
      $line =~ s/Summary string://g;

      $string .= $line;
    }
    
    close QAFILE;
    
    $self->{qa_done} = 1;
    $self->{qa_summary_string} = $string;
    
  }
  else{
    $self->{qa_done} = 0;
    $self->{qa_summary_string} = "QA not done";
  }

  #-------------------------------------------------------
  # check status of batch jobs: look for batch flags in report directory

  my $report_dir = $self->ReportDirectory;

  opendir(DIR,$report_dir) or die "Cannot open report dir $report_dir:$! \n"; 
  while ( defined( $file = readdir(DIR) ) ){

    $file =~ /^\.+$/ and next;
    $file !~ /batch_(\d+)\.(\w+)/ and next;

    $id = $1;
    $action = $2;

    $batch_job = "$batch_dir/temp_$id\.csh";

    if( -e $batch_job ){
      $self->{qa_summary_string} .= "<br><font color=blue> Batch job $action in progress</font>";
    }
    else{
      # orphaned batch process, clean it up
      $full_file = "$report_dir/$file";
      unlink($full_file) or print "Cannot delete file $full_file <br> \n";
    }
  }
  closedir(DIR);
  #-------------------------------------------------------
  return $self->{qa_summary_string};
}
#========================================================
sub QADone{

  my $self = shift;
  return $self->{qa_done};
}
#========================================================
sub OnDisk{
  my $self = shift;

  if (@_) {
    $report_key = shift; 
    $test_data_dir = $self->{logfile_report_data}->{output_directory};
    $on_disk = 0;

    if (defined $test_data_dir and -d $test_data_dir){ 
      # even if same directory exists, may contain later run -> test against dir time
      $test_report_key = QA_make_reports::get_report_key($test_data_dir); 
      $test_report_key eq $report_key and $on_disk = 1;
    }

    $self->{on_disk} = $on_disk;
  }
  
  return $self->{on_disk};
}
#========================================================
sub LogfileReportName{

  my $self = shift;

  if (@_){
    my $report_key = shift;
    my $report_dirname = $self->ReportDirectory;
    my $report_dirname_WWW = $self->ReportDirectoryWWW;
    my $logfile_reportname = "logfile_report\.txt";
    $self->{logfile_report} = $report_dirname."/".$logfile_reportname;
    $self->{logfile_report_WWW} = $report_dirname_WWW."/".$logfile_reportname;
  }
  return $self->{logfile_report};
}
#========================================================
sub LogfileReportNameWWW{
  my $self = shift;
  return $self->{logfile_report_WWW};
}
#========================================================
sub LogfileName{
  my $self = shift;
  return $self->LogfileReportData->{input_logfile};
}
#========================================================
sub ProductionDirectory{
  my $self = shift;
  return $self->LogfileReportData->{output_directory};
}
#========================================================
sub DataDisplayString{

  my $self = shift;

  #--------------------------------------------------------

  my $string = $self->LogfileReportData->{"output_directory"}; 

  my $logfile_report = $self->LogfileReportName;
      
  if (-e $logfile_report ){
    
    $starlib_version = $self->LogfileReportData->{"starlib_version"};
    $star_level = $self->LogfileReportData->{"star_level"};
    $starlib_version =~ /SL/ and $string .= "<br>(STARLIB version: $starlib_version; STAR level: $star_level)";
    
    $input_filename = $self->LogfileReportData->{"input_filename"};
    $input_filename and $string .= "<br>(input: $input_filename)";
  }

  return $string;
}
#========================================================
sub CreationString{

  my $self = shift;

  #--------------------------------------------------------

  $time_temp = $self->CreationEpochSec;
  $creation_time = localtime($time_temp);
  
  $on_disk = $self->OnDisk;
  $creation_time .="<br>".($on_disk ? "<font color = green> (on disk) </font>" : 
			   "<font color = red> (not on disk)</font>");
  #--------------------------------------------------------

  return $creation_time;
}
#========================================================
sub CreationEpochSec{

  my $self = shift;

  #--------------------------------------------------------
  # get finish time of job, convert to format used by localtime
  $time_temp = $self->LogfileReportData->{start_time_and_date};
 
  return QA_cgi_utilities::convert_logtime_to_epoch_sec($time_temp);
}


#========================================================
sub RunSummaryString{
  my $self = shift;

  exists $self->{run_summary_string} or do{
    $logfile_report = $self->LogfileReportName;
    $self->{run_summary_string} = QA_logfile_report::get_logfile_summary_string($logfile_report);
  };
  
  return $self->{run_summary_string};
}
#========================================================
sub ButtonString{
  my $self = shift;
  
  my $report_key = $self->ReportKey;
  
  my $temp = $report_key.".show_log_report";
  my $button_string = "<input type=submit name=$temp value='Run details'>";
  
  if ( $self->QADone ){ 
    $temp = $report_key.".show_qa";
    $button_string .= "<input type=submit name=$temp value='QA details'>";
  }
  $button_string .= "<br>";

  $temp = $report_key.".show_files";
  $button_string .= "<input type=submit name=$temp value='Files and Reports'><br>";

  $temp = $report_key.".compare_runs";
  $button_string .= "<input type=submit name=$temp value='Compare similar runs'><br>";
  
  if ($global_expert_page){

    if ( $self->QADone ){ 
      $temp = $report_key.".redo_evaluation";
      $button_string .= "<input type=submit name=$temp value='Redo Evaluation'>";
      $self->OnDisk and do {	
	$temp = $report_key.".redo_qa_batch";
	$button_string .= "<input type=submit name=$temp value='Redo QA (batch)'>";
      };
    }
    else{
      $self->OnDisk and do {	
	$temp = $report_key.".do_qa_batch";
	$button_string .= "<input type=submit name=$temp value='Do QA (batch)'>";
      };
    }
  }
  #-----------------------------------------------------------------------------

  return $button_string;

}
#========================================================
sub DisplayLogfileReport{
  my $self = shift;

  my $report_key = $self->ReportKey;
  QA_logfile_report::display_logfile_report($report_key);

  return;
}
#========================================================
sub DoQA{
  my $self = shift;

  #------------------------------------------------------------------------
  # make sure this is on disk (protects against doing QA on wrong run in same directory)
  $self->OnDisk or return;
  #------------------------------------------------------------------------

  @_ and my $arg_string = shift;

  $run_option = "";
  $arg_string =~ /evaluate_only/ and $run_option = "evaluate_only";

  $self->RunQAMacros($run_option);
  $arg_string =~ /no_tables/ or $self->ShowQA;

  return;
}
#========================================================
sub ShowQA{
  my $self = shift;

  my $report_key = $self->ReportKey;
  QA_report_io::display_reports($report_key);

  return;
}
#===========================================================
sub RunQAMacros {

  my $self = shift;
  @_ and my $run_option = shift;

  #----------------------------------------------------------

  my $report_key = $self->ReportKey;
  my $production_dir = $self->ProductionDirectory;
  my $report_dir = $self->ReportDirectory;

  #----------------------------------------------------------------
  # check if qa summary file present. If so, QA has been done already. In order
  # to redo QA, must delete all QA files first

  my $qa_summary_file = $self->QASummaryFileName;

  if ($run_option =~ /evaluate_only/){
     -s $qa_summary_file and unlink($qa_summary_file);
   }
  else{
    -s  $qa_summary_file and do{
      print "<h4> <font color = green> QA already done for $production_dir </font> </h4> \n";
      return;
    };
  }

  #----------------------------------------------------------------
  $control_file = $self->ControlFile;

  -s $control_file or do{    
    print "<h4> <font color = red> Cannot find control file for report key $report_key </font> </h4> \n";
    return;
  };

  #----------------------------------------------------------------
  # run macros

  open CONTROL, $control_file or die "Cannot open control file $control_file: $! \n";


  print "<hr><h2> QA for $production_dir (report key $report_key) </h2> \n";

  $time_string = "The time is ".localtime();
  print "$time_string <br> \n";

  print "<h3> Using control file $control_file </h3> \n";

  $summary_string = "QA done ".localtime()."; ";

  while ($line = <CONTROL>){

    # skip comments
    $line =~ /^\#/ and next;

    #skip blank lines
    $line !~ /\S+/ and next;

    my $macro_test_file = $line;
    print "<h4> Macro test file $macro_test_file </h4> \n";

    my $macro_object = QA_report_object->new($report_key, $macro_test_file);

    $macro_object->GetTests;
    $run_option =~ /evaluate_only/ or $macro_object->RunMacro;
    $macro_object->EvaluateMacro;

    # check for root crash
    $macro_name = $macro_object->MacroName;
    $rootcrashlog = "$report_dir/$macro_name.rootcrashlog";

    -s $rootcrashlog and $summary_string .= "<font color=red> $macro_name crashed; </font>" ;

    $summary_string .= $macro_object->SummaryString;

   }

  close CONTROL;

  #----------------------------------------------------------------
  # write QA summary

  $self->WriteQASummary($summary_string);

}
#================================================================================
sub DisplayFilesAndReports{

  my $self = shift;

  #---------------------------------------------------------------------------------
  $self->PrintProductionFiles;
  #---------------------------------------------------------------------------------
  my $production_dir = $self->ProductionDirectory;

  print "<H2> Reports for $production_dir </H2>\n";
  #---------------------------------------------------------------------------------

  $logfile = $self->LogfileName;
  if (-s $logfile){

    # get topdir this is found under, replace with link

    undef $logfile_WWW;
    my $icount = -1;
    foreach $topdir (@topdir_data){
      $icount++;
      $logfile =~ /$topdir/ and do{
	($logfile_WWW = $logfile) =~ s/$topdir\///;
	$logfile_WWW = $topdir_data_WWW[$icount].$logfile_WWW;
	last;
      };
    }

    $logfile_WWW and do{
      $time = stat($logfile)->mtime;
      $time_string = " (created:".localtime($time).")";
      $string = "Logfile $time_string";
      QA_cgi_utilities::make_anchor($string, $logfile, $logfile_WWW);
    };

  }

  #---
  # look in report directory

  my $report_dir = $self->ReportDirectory;
  
  opendir (DIR, $report_dir) or die "Cannot opendir $report_dir: $! \n";
  
  undef $logfile;
  undef $qa_summary;
  @ps_file = ();
  @report = ();
  @evaluation = ();
  @root_crash = ();

  while (defined ($file = readdir(DIR) ) ){

    # skip . and ..
    $file =~ /^\./ and next;
    
    $file =~ /logfile_report/ and do{
      $logfile = $file;
      next;
    };

    $file =~ /ps$/ and do{
      push @ps_file, $file;
      next;
    };

    $file =~ /ps\.gz$/ and do{
      push @ps_file, $file;
      next;
    };

    $file =~ /qa_report$/ and do{
      push @report, $file;
      next;
    };

    $file =~ /evaluation$/ and do{
      push @evaluation, $file;
      next;
    };

    $file =~ /rootcrashlog$/ and do{
      push @root_crash, $file;
      next;
    };

    $file =~ /qa_summary/ and do{
      $qa_summary = $file;
      next;
    };

  }

  closedir (DIR);
  #----------------------------------------------------------------

  print "<H4> Postscript files: </H4>\n"; 

  foreach $file (@ps_file){
    $self->PrintFilestring("Postscript file", $file);
  }

  #----------------------------------------------------------------
  # these are for experts only

  $global_expert_page and do{

    print "<H4> Other files: </H4>\n"; 
    
    $logfile and $self->PrintFilestring("Logfile report", $logfile);
    $qa_summary and $self->PrintFilestring("QA summary", $qa_summary);
    
    foreach $file (@report){  
      $self->PrintFilestring("Report", $file);
    }
    
    foreach $file (@evaluation){  
      $self->PrintFilestring("Evaluation", $file);
    }
    
    foreach $file (@root_crash){  
      $self->PrintFilestring("Root crash", $file);
    }
    
  };

  print "<HR>\n";
}

#===================================================================================
sub PrintFilestring{

  my $self = shift;
  $string = shift;
  my $file = shift;

  #-----------------------------------------------------------------

  my $report_dir = $self->ReportDirectory;

  $filename = "$report_dir/$file";
  $time = stat($filename)->mtime;
  $string .= " (created:".localtime($time).")";

  if ($file !~ /\.evaluation$/){
    my $report_dir_WWW = $self->ReportDirectoryWWW;
    $filename_WWW = "$report_dir_WWW/$file";
    QA_cgi_utilities::make_anchor($string, $filename, $filename_WWW);
  }
  else{
    print "$string $filename <br> \n";
  }

  return;
}
#==========================================================
sub PrintProductionFiles{

  my $self = shift;

  #-----------------------------------------------------------
  my $production_dir = $self->ProductionDirectory;
  print "<H2> Files in $production_dir </H2>\n";
  #-----------------------------------------------------------

  @table_heading = ('File name', 'Size (bytes)', 'Created');
  @table_rows = th(\@table_heading);
  
  opendir (DIR, $production_dir) or die "Cannot opendir $report_dir: $! \n";

  while (defined ($file = readdir(DIR) ) ){

    # skip . and ..
    $file =~ /^\./ and next;

    $filename = "$production_dir/$file";

    $size_string = stat($filename)->size;

    $time = stat($filename)->mtime;
    $time_string = localtime($time);

    push @table_rows, td( [$filename, $size_string, $time_string ] ) ; 
  }

  closedir (DIR);

  print table( {-border=>undef}, Tr(\@table_rows));

  #------------------------------------------------------------------

  return;	
	 
}
#==========================================================
sub DeleteQAFiles{

  my $self = shift;

  #-----------------------------------------------------------
  my $report_dir = $self->ReportDirectory;
  #-----------------------------------------------------------
  
  opendir (DIR, $report_dir) or die "Cannot opendir $report_dir: $! \n";

  while (defined ($file = readdir(DIR) ) ){

    my $delete = 0;

    $file =~ /qa_summary/ and $delete = 1;
    $file =~ /qa_report$/ and $delete = 1;
    $file =~ /evaluation$/ and $delete = 1;
    $file =~ /rootcrashlog$/ and $delete = 1;
    $file =~ /\.ps$/ and $delete = 1;
    $file =~ /\.ps\.gz$/ and $delete = 1;

    $delete or next;

    $filename = "$report_dir/$file";

    unlink($filename) or print "Cannot delete file $filename <br> \n";

  }

  closedir (DIR);

  #------------------------------------------------------------------

  return;	
	 
}
