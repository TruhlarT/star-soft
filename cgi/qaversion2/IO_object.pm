#! /usr/bin/perl

# class to encapsulate all disk I/O

# pmj 24/5/00

#========================================================
package IO_object;
#========================================================

use strict;

use CGI qw/:standard :html3/;

#use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;
use FileHandle;
use DirHandle;
use Cwd;

use Storable;
use Data::Dumper;
use QA_globals;

use DataClass_object;

use QA_report_object;
use QA_object;

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

  my $filetype = shift;
  @_ and my @args = @_;

  #--------------------------------------------------------
  # this class depends upon an instance of  DataClass_object: check that it exists

  $gDataClass_object or die "IO_object::_init: gDataClass_object not defined <br>\n";

  #--------------------------------------------------------

  $self->FileType($filetype);

  #--------------------------------------------------------
  # call filetype-specific routine with rest of arguments
  # at the minimum, this generates the filename

  # default is file; for directory, need to set this explicitly
  $self->IsDir(0);

  # this flags whether to print to browser if error occurs on open - not desirable
  # for all files, default is silent
  $self->ReportErrorOnOpen(0);

  my $name = $self->$filetype(@args);
  $self->Name($name);

}
#========================================================
sub FileType{

  my $self = shift;
  @_ and $self->{_FileType} = shift;
  return $self->{_FileType};
}
#========================================================
sub FileHandle{

  my $self = shift;
  @_ and $self->{_FileHandle} = shift;
  return $self->{_FileHandle};
}
#========================================================
sub DirHandle{

  my $self = shift;
  @_ and $self->{_DirHandle} = shift;
  return $self->{_DirHandle};
}
#========================================================
sub Name{

  my $self = shift;
  @_ and $self->{_Name} = shift;
  return $self->{_Name};
}
#========================================================
sub IsDir{

  my $self = shift;
  @_ and $self->{_IsDir} = shift;
  return $self->{_IsDir};
}
#========================================================
sub ReportErrorOnOpen{

  my $self = shift;
  @_ and $self->{_ReportErrorOnOpen} = shift;
  return $self->{_ReportErrorOnOpen};
}
#========================================================
sub Open{

  # generic routine to open file or directory 
  # returns filehandle or dirhandle if sucecssful, 0 otherwise 

  # default for files is open for reading 
  # optional first argument: string of mode for opening, such as ">", "<" 
  # optional second argument: disk access mode to set (e.g. 0644)

  my $self = shift;
  @_ and my $open_mode = shift;
  @_ and my $disk_access_mode = shift;

  #------------------------------------------------------------
  # check if directory, otherwise assume it is a file
  # bum - need a unique filehandle FH
  
  local *FH;

  if ( $self->IsDir() ){

    my $dirname = $self->Name();
    
    opendir FH, "$dirname" or do{
      my $dirtype = $self->FileType();

      $self->ReportErrorOnOpen() and
	print "In IO_object::Open: could not open dirtype $dirtype,",
	"name $dirname <br>\n";

      return 0;
    };
    
    $self->DirHandle(*FH);
  }
  else{

    my $filename = $self->Name();
    defined ($open_mode) or $open_mode = "";

    open FH, "$open_mode $filename" or do{

      my $filetype = $self->FileType();

      $self->ReportErrorOnOpen() and
	print "In IO_object::Open: could not open filetype $filetype,",
	"open mode $open_mode, name $filename <br>\n";

      return 0;
    };
    
    $self->FileHandle(*FH);

    #---
    if (defined $disk_access_mode){
	my $cmd = "chmod $disk_access_mode $filename";
	system($cmd);
    }
    #---
  }

  #------------------------------------------------------

  return *FH;
}
#========================================================
sub DESTROY{

  # do proper cleanup when object goes out of scope
  
  my $self = shift;

  #------------------------------------------------------
  my $filehandle = $self->FileHandle();
  $filehandle and close $filehandle;
  #------------------------------------------------------
}

#========================================================
#********************************************************
# Filetype-specific routines follow
#********************************************************
#========================================================
sub QASummaryFile{

  my $self = shift;
  my $report_key = shift; 

  #--------------------------------------------------------
  # construct filename (replaces QA_object::QASummaryFileName)

  my $io = new IO_object("ReportDir", $report_key);
  my $report_dir = $io->Name();
  undef $io;

  my $filename = $report_dir."/qa_summary.txt";
  
  return $filename;
}
#========================================================
sub UpdateFile{

  my $self = shift;
  #--------------------------------------------------------
  #  my $filename = "$update_dir/last_update";
  my $filename = $gDataClass_object->UpdateDir()."/last_update";

  return $filename;
}
#========================================================
sub BackupStatusFile{

  my $self = shift;

  #--------------------------------------------------------
  #  my $filename = "$backup_dir/last_backup";
  my $filename = $gDataClass_object->BackupDir()."/last_backup";
  #--------------------------------------------------------
  return $filename;
}
#========================================================
sub BatchKeyList{

  my $self = shift;

  my $id_string = shift;
  my $action = shift;
  #--------------------------------------------------------
  #  my $filename = "$batch_dir/temp\_$id_string\.$action";
  my $filename = $gDataClass_object->BatchDir()."/temp\_$id_string\.$action";
  #--------------------------------------------------------

  $self->ReportErrorOnOpen(1);  

  return $filename;
}
#========================================================
sub BatchStatusReport{

  my $self = shift;

  my $id_string = shift;
  my $action = shift;
  my $report_key = shift;
  #--------------------------------------------------------
  #  my $filename = "$topdir_report/$report_key/batch_$id_string\.$action";
  my $filename = $gDataClass_object->TopDirReport()."/$report_key/batch_$id_string\.$action";
  #--------------------------------------------------------
  return $filename;
}
#========================================================
sub BatchScript{

  my $self = shift;

  my $id_string = shift;
  #--------------------------------------------------------
  my $filename = $gDataClass_object->BatchDir()."/temp\_$id_string\.csh";
  #--------------------------------------------------------

  $self->ReportErrorOnOpen(1);  

  return $filename;
}
#========================================================
sub BatchJob{

  my $self = shift;

  my $id_string = shift;
  #--------------------------------------------------------
  my $filename = $gDataClass_object->BatchDir()."/temp\_$id_string\.batch";
  #--------------------------------------------------------

  $self->ReportErrorOnOpen(1);  

  return $filename;
}
#===================================================================
sub CrontabFile{
  my $self = shift;

  my $now = cwd();
  return "$now/crontab.txt";
}
#===================================================================
sub CrondirMinusLFile{
  my $self = shift;
  return $gDataClass_object->CronDir()."/minus_l.txt";
}
#===================================================================
sub AtQueueFile{
  my $self = shift;
  return  $gDataClass_object->BatchDir()."/at_queue";
}
#===================================================================
sub UpdateDir{
  my $self = shift;
  $self->IsDir(1);

  $self->ReportErrorOnOpen(1);  

  return $gDataClass_object->UpdateDir();
}
#===================================================================
sub BatchDir{
  my $self = shift;

  # flag as directory
  $self->IsDir(1);

  $self->ReportErrorOnOpen(1);  

  return  $gDataClass_object->BatchDir();
}
#===================================================================
sub BatchDirWWW{
  my $self = shift;
  return  $gDataClass_object->BatchDirWWW();
}
#===================================================================
sub BatchDirDone{
  my $self = shift;

  # flag as directory
  $self->IsDir(1);

  $self->ReportErrorOnOpen(1);  

  return  $gDataClass_object->BatchDir()."/done";
}
#===================================================================
sub BatchDirDoneWWW{
  my $self = shift;

  # flag as directory
  $self->IsDir(1);

  return  $gDataClass_object->BatchDirWWW()."/done";
}
#===================================================================
sub ServerLogFile{
  my $self = shift;

  $self->ReportErrorOnOpen(1);  

  return  "/usr/local/apache/var/log/error_log";
}
#===================================================================
sub BatchLogHTML{
  my $self = shift;
  my $id_string = shift;

  $self->ReportErrorOnOpen(1);  

  return  $gDataClass_object->BatchDir()."/temp\_$id_string\.html";
}
#===================================================================
sub TopDir{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->TopDir();
}
#===================================================================
sub ControlDir{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->ControlDir();
}
#===================================================================
sub ControlDirWWW{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->ControlDirWWW();
}
#===================================================================
sub MessageDir{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->MessageDir();
}
#===================================================================
sub MessageFile{
  my $self = shift;
  my $message_key = shift;

  return $gDataClass_object->MessageDir()."/$message_key";
}
#===================================================================
sub DeletedMessageFile{
  my $self = shift;
  my $message_key = shift;

  return $gDataClass_object->Scratch()."/$message_key";
}
#===================================================================
sub ScratchDir{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->Scratch();
}
#===================================================================
sub TopdirReport{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->TopDirReport();
}
#===================================================================
sub TopdirReportOld{
  my $self = shift;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $gDataClass_object->TopDirReportOld();
}
#===================================================================
sub ReportDir{
  my $self = shift;
  my $report_key = shift;

  my $dir = $gDataClass_object->TopDirReport()."/".$report_key;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $dir;
}
#===================================================================

sub ReportDirWWW{
  my $self = shift;
  my $report_key = shift;

  my $dir = $gDataClass_object->TopDirReportWWW()."/".$report_key;
  $self->IsDir(1);
  $self->ReportErrorOnOpen(1);  
  return $dir;
}
#===================================================================

sub ProductionDir{
  my $self      = shift;
  my $qa_object = shift;

  my $dir = $qa_object->LogReport->OutputDirectory;
  $self->IsDir(1);
  
  return $dir;
}
#===================================================================
# this is a perl Storable.  dont call any open methods

sub LogReportStorable{
  my $self = shift;
  my $report_key = shift;
  
  my $io = IO_object->new("ReportDir",$report_key);
  my $report_dir = $io->Name;

  return "$report_dir/logfile_report.obj";
}
  
#===================================================================
sub DSVRunScript{
  my $self = shift;
  my $proc_id = shift;

  my $file = $gDataClass_object->Scratch()."/run_dsv\.$proc_id\.csh";
  $self->ReportErrorOnOpen(1);  
  return $file;
}
#===================================================================
sub DSVSubmitScript{
  my $self = shift;
  my $proc_id = shift;

  my $file = $gDataClass_object->Scratch()."/submit_run_dsv\.$proc_id\.csh";
  $self->ReportErrorOnOpen(1);  
  return $file;
}
#===================================================================
sub RootCrashLog{
  my $self = shift;
  my $report_key = shift;
  my $macro_name = shift;

  my $io = new IO_object("ReportDir", $report_key);
  my $report_dir = $io->Name();
  undef $io;

  my $file = "$report_dir/$macro_name.rootcrashlog";
  $self->ReportErrorOnOpen(1);  
  return $file;
}
#===================================================================
sub HiddenObjectFile{
  my $self = shift;
  my $id_string = shift;

  my $file = $gDataClass_object->Scratch()."/temp_$id_string.persistent_hash";

  return $file;
}

#===================================================================
# brains behind running the list of macros
# format:
# [controlDir]/[starlib]/test_control.[eventGen].[eventType].[geometry].txt

sub ControlFileNightly{
  my $self   = shift;
  my $qa_obj = shift;

  $self->ReportErrorOnOpen(1);

  my $starlib_version = $qa_obj->LogReport->StarlibVersion;
  
  # note the . before each scalar
  my $eventGen        = "." .$qa_obj->LogReport->EventGen ;
  my $eventType       = "." .$qa_obj->LogReport->EventType;
  my $geometry        = "." .$qa_obj->LogReport->Geometry;

  # each directory corresponds to a star library version
  my $dir = $self->ControlDir()."/$starlib_version";
  
  # default dir
  -d $dir or do{
    #print "Control dir $dir not found, using default... <br> \n";
    $dir = $self->ControlDir()."/default";
  };
  
  # determine the file name; make some abbreviations
  $eventGen  = ".hc"     if $eventGen  eq 'hadronic_cocktail';
  $eventGen  = ""        if $eventGen  eq 'n/a';  # for real events
  $eventType = ".std"    if $eventType eq 'standard';
  $eventType = ".low"    if $eventType eq 'lowdensity';
  $eventType = ".high"   if $eventType eq 'highdensity';
  
  # name the file...
  # e.g. test_control.[eventGen].[eventType].[geometyr]

  # BEN(4jun00):
  $self->IsDir(0);

  #return "$dir/test_control.txt";
  return "$dir/test_control$eventGen$eventType$geometry.txt";
}
#=====================================================================
# dummy control file for now
# format
# [controlDir]/[prodSeries]/test_control.txt

sub ControlFileOffline{
  my $self = shift;
  my $qa_obj = shift;

  my $prodSeries = $qa_obj->LogReport->ProdSeries;

  my $dir = $self->ControlDir."/$prodSeries";

  # default dir
  -d $dir or do{
    #print "Control dir $dir not found, using default... <br> \n";
    $dir = $self->ControlDir()."/default";
  };

  # TEST
  return "$dir/test_control.txt";
}
#=====================================================================
# output of the macro run

sub MacroReportFilename{
  my $self             = shift;
  my $input_aryref     = shift;
  my $report_key       = shift;
  my $macro_name       = shift;
  my $output_data_type = shift;
  my $output_data_filename = shift;
  my $output_data_ext  = shift;

  $self->ReportErrorOnOpen(1);

  my ($filename) ; # name of the output file

  my $filetype    = ( $output_data_type =~ /ps/ ) ? ".ps" : ".qa_report";

  # if an output file name is requested, use that plus the filetype
  if ($output_data_filename) {
    $filename = $output_data_filename.$filetype;
  }
  # else just use the macro name and the file type (+data extension)
  else{
    $filetype = $output_data_ext.$filetype;
    $filename = $macro_name.$filetype;
  }
  # need to get the report dir
  my $io = IO_object->new("ReportDir",$report_key);
  my $report_dir = $io->Name;

  return "$report_dir/$filename";

}

#=====================================================================
sub EvaluationFilename{
  my $self= shift;
  my $report_key = shift;
  my $macro_name = shift;

  my $filename = "$macro_name.evaluation";

  my $io = IO_object->new("ReportDir",$report_key);
  my $report_dir = $io->Name;

  return "$report_dir/$filename";
}
#=====================================================================
sub CompareFilename{
  my $self= shift;
  my $report_key = shift;

  return  $gDataClass_object->CompareDir()."/$report_key";
}
  
#=====================================================================
# StWarning exceptions in the log file

sub StWarningFile{
  my $self       = shift;
  my $report_key = shift;

  $self->ReportErrorOnOpen(1);

  # report dir
  my $io = IO_object->new("ReportDir", $report_key);
  my $report_dir = $io->Name;

  # warning file

  return "$report_dir/StWarning.txt";
}
 
#=====================================================================
# StError exceptions in the log file

sub StErrorFile{
  my $self       = shift;
  my $report_key = shift;

  $self->ReportErrorOnOpen(1);

  # report dir
  my $io = IO_object->new("ReportDir", $report_key);
  my $report_dir = $io->Name;

  # warning file

  return "$report_dir/StError.txt";
} 
#=====================================================================
# temporary soft link to the log file to view it over the web

sub LogScratchWWW{
  my $self    = shift;
  my $logfile = shift;

  srand; # sets the seed
  my $id_string = int(rand(100000));

  my $scratch_WWW = $gDataClass_object->ScratchDirWWW;
  my $link        = "$scratch_WWW/logfile_link_$id_string";
  
  print h3("$link", "$logfile");

  symlink $logfile, $link or warn "Couldn't symlink";

  return $link;
}
  

  
