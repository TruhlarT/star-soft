#! /usr/bin/perl

# first try at a QA object
# pmj 29/7/99
#========================================================
package QA_object;
#========================================================
#use CGI qw/:standard :html3 -no_debug/;
use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;

use Storable;
use Data::Dumper;
use QA_globals;

#use QA_logfile_report;
use Logreport_object;

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
  
  # this argument can be production dir or report dir - check later
  my $arg_dir = shift;

  # second argument is optional action: update log file, do qa, etc.
  @_ and $action = shift;

  #-------------------------------------------------
  # is this a data or report directory?

  undef $report_key;
  my $this_is_prod_dir = 0;

 DIRTYPE: {

    foreach $topdir (@topdir_data){

      $arg_dir =~ /$topdir/ and do{
	$report_key = QA_make_reports::get_report_key($arg_dir); 
	$this_is_prod_dir = 1;
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
  $self->ReportDirectory();
  $self->LogReportName();
  #------------------------------------------------------
  # get pointer to logreport object

  if($action =~ /update/ and $this_is_prod_dir){
      QA_make_reports::make_report_directory($report_key);
      $self->LogReport($arg_dir);
    }
  else{
    $self->LogReport();
  }

  #------------------------------------------------------
  # special processing for cosmics directories pmj 13/12/99

  $report_key =~ /cosmics\.(\w+)/ and do{

    $new_output_dir = "/star/rcf/test/dst/$1";
    $self->LogReport->OutputDirectory("$new_output_dir");

  };
  #------------------------------------------------------
  $self->QASummaryString();
  #------------------------------------------------------
  # is data on disk?

  $self->OnDisk();

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

  $self->{report_directory} or do{
    my $report_key = $self->ReportKey;
    $self->{report_directory} = QA_make_reports::report_directory($report_key);
  };

  return $self->{report_directory};
}
#========================================================
sub ReportDirectoryWWW{

  my $self = shift;

  $self->{report_directory_www} or do{
    my $report_key = $self->ReportKey;
    $self->{report_directory_www} = QA_make_reports::report_directory_www($report_key);
  };

  return $self->{report_directory_www};
}
#========================================================
sub ControlFile{
  my $self = shift;

  $self->{control_file} or do{

    my $starlib_version = $self->LogReport->StarlibVersion;
    my $input_filename = $self->LogReport->InputFn;
    
  CONTROLFILE: {
      
      $control_file = "unknown";
      
      my $dir = "$control_dir/$starlib_version";
      -d $dir or $dir = "$control_dir/default";
      -d $dir or last CONTROLFILE;

      my $filestring = "$dir/test_control";

      if ( $input_filename =~ /venus412\/b0_3/ ){
	$filestring .= "\.venus";
      }
      elsif ( $input_filename =~ /daq/ ){
	$filestring .= "\.cosmics";
      }
      elsif( $input_filename =~ /hadronic_cocktail/ ){

	if ( $input_filename =~ /lowdensity/ ){
	  	$filestring .= "\.hc_low";
	      }
	elsif ( $input_filename =~ /standard/ ){
	  	$filestring .= "\.hc_std";
	      }
	elsif ( $input_filename =~ /highdensity/ ){
	  	$filestring .= "\.hc_high";
	      }
	else{
	  	last CONTROLFILE;
	      }

      }
      else{
	last CONTROLFILE;
      }

      if ( $input_filename =~ /year_1b/ ){
	$filestring .= "\.year_1b";
      }
      elsif ( $input_filename =~ /year_2a/ ){
	$filestring .= "\.year_2a";
      }

      $control_file = "$filestring\.txt";
      
    } # end of CONTROLFILE

    $self->{control_file} = $control_file;    
  };
  
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

  $report_key = $self->ReportKey(); 
  
  $test_data_dir = $self->LogReport->OutputDirectory;
  $on_disk = 0;
  
  if (defined $test_data_dir and -d $test_data_dir){ 
    # even if same directory exists, may contain later run -> test against dir time
    $test_report_key = QA_make_reports::get_report_key($test_data_dir); 
    $test_report_key eq $report_key and $on_disk = 1;
  }

  return  $on_disk;
}
#========================================================
sub DataDisplayString{

  my $self = shift;

  #--------------------------------------------------------

  my $logfile_report = $self->LogReportName;
  
  if (-e $logfile_report ){

    $string = $self->LogReport->OutputDirectory;
    
    $starlib_version = $self->LogReport->StarlibVersion;
    $star_level = $self->LogReport->StarLevel;
    $starlib_version =~ /SL/ and $string .= "<br>(STARLIB version: $starlib_version; STAR level: $star_level)";
    
    $input_filename = $self->LogReport->InputFn;

    # pmj 10/12/99
    ($input_fn_string = $input_filename) =~ s%/star/rcf/disk0/star/test/%%;
    $input_filename and $string .= "<br><font size=1>(input: $input_fn_string)</font>";

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

  $self->{CreationEpochSec} or do{

    # get finish time of job, convert to format used by localtime
    $time_temp = $self->LogReport->RunStartTimeAndDate;
    
    $self->{CreationEpochSec} = QA_cgi_utilities::convert_logtime_to_epoch_sec($time_temp);
  };

  return $self->{CreationEpochSec}
}
#========================================================
sub RunSummaryString{
  my $self = shift;

  exists $self->{run_summary_string} or do{
    $self->{run_summary_string} = $self->LogReport->LogfileSummaryString;
  };
  
  return $self->{run_summary_string};
}
#========================================================
sub ButtonString{
  my $self = shift;

  my $report_key = $self->ReportKey;
  #-----------------------------------------------------------------------

  $button_string = "";

  $button_ref = Button_object->new('RunDetails', 'Run Details', 
				   $report_key);
  $button_string .= $button_ref->SubmitString;
  
  
  if ( $self->QADone ){ 
    $button_ref = Button_object->new('QaDetails', 'QA Details', 
				     $report_key);
    $button_string .= $button_ref->SubmitString;
  }
  $button_string .= "<br>";

  $button_ref = Button_object->new('FilesAndReports', 'Files and Reports', 
				   $report_key);
  $button_string .= $button_ref->SubmitString;

  $query->param('display_env_var') and $self->OnDisk and do{
    $button_ref = Button_object->new('RunDSV', 'Run DSV', $report_key);
    $button_string .= $button_ref->SubmitString;
  };

  $button_string .= "<br>";

  $button_ref = Button_object->new('CompareSimilarRuns', 'Compare similar runs', 
				   $report_key);
  $button_string .= $button_ref->SubmitString;
  $button_string .= "<br>";

  #---
  if ( $query->param('enable_add_edit_comments') ) {
    $button_ref = Button_object->new('AddComment', 'Add comment', $report_key);
    $button_string .= $button_ref->SubmitString."<br>";
  }
  #----
  
  if ($global_expert_page){

    if ( $self->QADone ){ 
      $button_ref = Button_object->new('RedoEvaluation', 'Redo Evaluation', 
				       $report_key);
      $button_string .= $button_ref->SubmitString;

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
  #-----------------------------------------------------------------------------

  return $button_string;

}
#========================================================
sub DisplayLogReport{
  my $self = shift;

  $self->LogReport->DisplayLogReport;

  return;
}
#========================================================
sub DoQA{
  my $self = shift;

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
#========================================================
sub ProductionDirectory{
  my $self = shift;
  return $self->LogReport->OutputDirectory;
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

    if (-s $rootcrashlog){
      $summary_string .= "<font color=red> $macro_name crashed; </font>" ;
    }
    else{		  
      $summary_string .= $macro_object->SummaryString;
    }

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

  $logfile = $self->LogReport->LogfileName;
  $logfile_WWW = $self->LogReport->LogfileNameWWW;

  if (-s $logfile){

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

  if ( $file =~ /\.(evaluation|obj)$/){
    print "$string $filename <br> \n";
  }
  else{
    my $report_dir_WWW = $self->ReportDirectoryWWW;
    $filename_WWW = "$report_dir_WWW/$file";
    QA_cgi_utilities::make_anchor($string, $filename, $filename_WWW);
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

  opendir (DIR, $production_dir) or do{
    print "Cannot open directory $production_dir: $! \n";
    return;
  };
  #-----------------------------------------------------------

  @table_heading = ('File name', 'Size (bytes)', 'Created');
  @table_rows = th(\@table_heading);
  
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
#========================================================
sub LogReport{

  my $self = shift;

  $self->{logreport} or do{

    $report_key = $self->ReportKey();

    $report_key or do{
      ($package, $filename, $line) = caller;
      print "=" x 80, "\n<br> No report_key, LogReport called from $package::$filename, line $line <br> \n";
    };

    $filename = QA_make_reports::log_report_name($report_key);

    if (@_){

      # log report doesn't exist, create new object and write it to disk
      $production_dir = shift;
      $logreport_ref = Logreport_object->new($production_dir, 'data');

      print "<h4> Writing Logreport object to $filename... </h4> \n";
      store( $logreport_ref, $filename) or die "<h4> Cannot write $filename: $! </h4> \n";
      if ( -e $filename ){
	print "<h4> ... done </h4> \n";
      }
      else {
	print "<h4> file $filename not created, something went wrong. </h4> \n";
      }
      
      $self->{logreport} = $logreport_ref;

    }
    elsif($filename =~ /\.txt/){
      # old style ascii report; creat new object and fill it from disk
      $logreport_ref = Logreport_object->new($filename, 'txt_report');

      $self->{logreport} = $logreport_ref;
     
      # now write as new-style object

      ($filename_obj = $filename ) =~ s/\.txt$/\.obj/;

      print "<h4> Writing Logreport object to $filename_obj... </h4> \n";
      store( $logreport_ref, $filename_obj) or die "<h4> Cannot write $filename_obj: $! </h4> \n";
      if ( -e $filename_obj ){
	print "<h4> ... done </h4> \n";
      }
      else {
	print "<h4> file $filename_obj not created, something went wrong. </h4> \n";
      }
 
    }
    else{
      # "Storable" object on disk    
      
      if ( -e $filename ){
	$self->{logreport} = retrieve($filename);
      }
      else{
	print "Error in QA_object::LogReport: report_key=$report_key, cannot find $filename <br> \n";
      }
      
    }
    
  };
  
  return $self->{logreport};
}
#========================================================
sub LogReportName{

  my $self = shift;

  $self->{logreport_name} or do{

    my $report_key = $self->ReportKey;
    my $report_dirname = $self->ReportDirectory;
    my $report_dirname_WWW = $self->ReportDirectoryWWW;

    # if existing ascii file present, use that. Otherwise, generate "Storable" object pmj 13/11/99
    my $name = "/logfile_report";

    if (-e $report_dirname."$name\.txt"){
      $name .= "\.txt";
    }
    else{
      $name .= "\.obj";
    }

    $self->{logreport_name} = $report_dirname.$name;
    $self->{logreport_name_WWW} = $report_dirname_WWW.$name;
  };

  return $self->{logreport_name};
}
#========================================================
sub LogReportNameWWW{
  my $self = shift;

  $self->{logreport_name_WWW} or $self->LogReportName();

  return $self->{logreport_name_WWW};
}
