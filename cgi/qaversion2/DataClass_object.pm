#! /usr/bin/perl

# class to encapsulate all directory assignments for a specific data class

# these should not be used directly for I/O, but should be referenced by IO_object

# pmj 2/6/00

#========================================================
package DataClass_object;
#========================================================

use strict;

use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);

use File::Basename;
use File::Find;
use File::stat;
use Cwd;

use Storable;
use Data::Dumper;
use QA_globals;
#--------------------------------------------------------

use vars qw( $AUTOLOAD 

	     %ok_field 

	     @data_class_array_offline
	     @data_class_array_online
	     @data_class_array

	     %data_class_labels_offline
	     %data_class_labels_online
	     %data_class_labels

	     %ok_data_class_offline 
	     %ok_data_class_online
	     %ok_data_class
	   );
#-------------------------------------------------------
# define registered data classes for offline and online

my @data_class_array_offline = qw ( offline_real
				    offline_MC
				    nightly_real
				    nightly_MC
				    debug
				  );

my %data_class_labels_offline = (offline_real  => 'real data production',
				 offline_MC    => 'MC production',
				 nightly_real  => 'real data nightly tests',
				 nightly_MC    => 'MC nightly tests',
				 debug         => 'debug');

#----

my @data_class_array_online = qw ( online_raw
				   online_dst
				   online_debug
				  );

my %data_class_labels_online = (online_raw  => 'online raw data',
				online_dst  => 'online dst data',
				online_debug => 'debug');

#----
			   
my $data_class;

for $data_class ( @data_class_array_offline ) { 
  $ok_data_class_offline{$data_class}++; 
}

for $data_class ( @data_class_array_online ) { 
  $ok_data_class_online{$data_class}++; 
}

#------------------------------------------------------------
# register allowed accessor fields for AUTOLOADER
# (see PERL Cookbook 13.11, pg 468)

for my $attr ( qw (
		   TopDir
		   TopDirWWW
		   TopDirReport
		   BatchDir
		   ControlDir
		   UpdateDir
		   BackupDir
		   CronDir
		   Scratch
		   CompareDir
		   TopDirReportOld
		   MessageDir
		   TopDirReportWWW
		   ControlDirWWW
		   BatchDirWWW
		   LogScratchDirWWW
		   LogScratchDir
		   KeyList_obj
		   QA_obj
		   GetSelectedKeys
		   GetSelectionOptions
		   GetOldReports
		   dbFile
		   FileCatalog
		   JobStatus
		   ProdOptions
		   JobRelations
		   dbQA
		   GetMissingFiles
		   UpdateRoutine
		   BrowserBannerColor
		   BrowserBannerLabel
		   DataClassArray
		   DataClassLabels
		  )
	    ) { $ok_field {$attr}++; }
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

  my $data_class = shift;
  @_ and my @args = @_;
  #--------------------------------------------------------
  my $server_type = $gServer_object->ServerType();
  
  if ($server_type eq 'online' ){
    @data_class_array = @data_class_array_online;
    %data_class_labels = %data_class_labels_online;
    %ok_data_class = %ok_data_class_online;
  }
  elsif ($server_type eq 'offline' ){
    @data_class_array = @data_class_array_offline;
    %data_class_labels = %data_class_labels_offline;
    %ok_data_class = %ok_data_class_offline;
  }
  else{
    die "DataClass_object::_init: unknown server type $server_type<br>\n";
  }

  #--------------------------------------------------------
  $ok_data_class{$data_class} or die "DataClass_object::init_: unregistered data class $data_class \n";
  #--------------------------------------------------------
  # this is master top directory, should depend upon server object
  # BEN(8jun2000):  changed for rcas
  $self->Home("/star/rcf/qa");
  #--------------------------------------------------------
  $self->DataClass($data_class);

  $self->DataClassArray(\@data_class_array);
  $self->DataClassLabels(\%data_class_labels);

  #--------------------------------------------------------
  # call data class-specific routine with rest of arguments
  $self->$data_class(@args);

}
#========================================================
sub Home{

  my $self = shift;
  @_ and $self->{_Home} = shift;
  return $self->{_Home};
}
#========================================================
sub DataClass{

  my $self = shift;
  @_ and $self->{_DataClass} = shift;
  return $self->{_DataClass};
}
#========================================================
sub AUTOLOAD{
  
  # see PERL Cookbook recipe 13.11

  my $self = shift;
  my $attr = $AUTOLOAD;

  #--------------------------------------------------------
  # strip package qualifiers
  $attr =~ s/.*:://;

  # test if valid call

  $attr =~ /[^A-Z]/ or croak "DataClass_object::AUTOLOAD: invalide accessor $attr \n";
  $ok_field{$attr} or croak "DataClass_object::AUTOLOAD: unregistered accessor $attr \n";

  #--------------------------------------------------------
  # do accessor
  no strict;

  *{$attr} = sub {
    my $self = shift;;
    $self->{uc $attr} = shift if @_;
    return $self->{uc $attr};
  };
  

  @_ and $self->{uc $attr} = shift;
  return $self->{uc $attr}
}
#********************************************************
# Data class-specific routines follow
#********************************************************
#========================================================
sub StandardDirectories{

  my $self = shift;

# called after TopDir defined below

  my $topdir = $self->TopDir();
  $self->TopDirReport("$topdir/reports");
  $self->ControlDir("$topdir/control_and_test");
  $self->UpdateDir("$topdir/update");
  $self->BackupDir("$topdir/backups");
  $self->Scratch("$topdir/scratch");
  $self->CompareDir("$topdir/compare_runs");
  $self->TopDirReportOld("$topdir/reports_old");
  $self->MessageDir("$topdir/messages");

  my $topdir_WWW = $self->TopDirWWW();
  my $data_class = $self->DataClass();

  $self->TopDirReportWWW("$topdir_WWW/report_dir_$data_class");
  $self->ControlDirWWW("$topdir_WWW/control_dir_$data_class");
  $self->BatchDirWWW("$topdir_WWW/batch_dir_$data_class");

  # need to make a temporary link to the logfiles
  #
  $self->LogScratchDirWWW("$topdir_WWW/scratch");
  $self->LogScratchDir("/star/u2e/starqa/WWW/qa_db/scratch");

  my $batch_dir = "$topdir/batch";
  $self->BatchDir("$batch_dir");
  $self->CronDir("$batch_dir/cronjob_logs");

}
#========================================================
sub offline_real{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------

  my $home = $self->Home();

  $self->TopDir("$home/offline_real");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  # objects to create
  $self->KeyList_obj("KeyList_object_offline");
  $self->QA_obj("QA_object_offline");

  # database stuff
  $self->dbFile("operation");
  $self->FileCatalog("FileCatalog");
  $self->JobStatus("JobStatus");
  $self->ProdOptions("ProdOptions");
  $self->JobRelations("cpjobRelations");
  $self->dbQA("prod_QA");

  # utilities for KeyList_object
  $self->GetSelectionOptions("Db_KeyList_utilities::GetOfflineSelectionsReal");
  $self->GetSelectedKeys("Db_KeyList_utilities::GetOfflineKeysReal");  

  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQAOfflineReal");

  # find missing files
  $self->GetMissingFiles("QA_db_utilities::GetMissingFilesReal");

  # get old reports
  $self->GetOldReports("QA_db_utilities::GetOldReportsReal");

  # browser banner for interactive display
  $self->BrowserBannerColor("red");
  $self->BrowserBannerLabel("Real Data Production");

}
#========================================================
sub offline_MC{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------

  my $home = $self->Home();

  $self->TopDir("$home/offline_MC");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  # objects to create
  $self->KeyList_obj("KeyList_object_offline");
  $self->QA_obj("QA_object_offline");
  
  # database stuff
  $self->dbFile("operation");
  $self->FileCatalog("FileCatalog");
  $self->JobStatus("JobStatus");
  $self->ProdOptions("ProdOptions");
  $self->JobRelations("cpjobRelations");
  $self->dbQA("prod_QA");

  # utilities for KeyList_object
  $self->GetSelectionOptions("Db_KeyList_utilities::GetOfflineSelectionsMC");
  $self->GetSelectedKeys("Db_KeyList_utilities::GetOfflineKeysMC");
  
  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQAOfflineMC");

  # find missing files
  $self->GetMissingFiles("QA_db_utilities::GetMissingFilesMC");

  # get old reports
  $self->GetOldReports("QA_db_utilities::GetOldReportsMC");

  # browser banner for interactive display
  $self->BrowserBannerColor("red");
  $self->BrowserBannerLabel("MC Data Production");

}


#========================================================
sub nightly_real{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();
  $self->TopDir("$home/nightly_real");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/db");

  $self->StandardDirectories();
  
  # objects to create
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database stuff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");


  # utilities for KeyList_object
  $self->GetSelectionOptions("Db_KeyList_utilities::GetNightlySelectionsReal");
  $self->GetSelectedKeys("Db_KeyList_utilities::GetNightlyKeysReal");
  
  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyReal");

  # find missing files
  $self->GetMissingFiles("QA_db_utilities::GetMissingFilesReal");

  # get old reports
  $self->GetOldReports("QA_db_utilities::GetOldReportsReal");

  # browser banner for interactive display
  $self->BrowserBannerColor("red");
  $self->BrowserBannerLabel("Real Data Nightly Tests");

}
#========================================================
sub nightly_MC{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();
  $self->TopDir("$home/nightly_MC");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  # objects to create
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database stuff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");


  # utilities for KeyList_object
  $self->GetSelectionOptions("Db_KeyList_utilities::GetNightlySelectionsMC");
  $self->GetSelectedKeys("Db_KeyList_utilities::GetNightlyKeysMC");

  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyMC");

  # find missing files
  $self->GetMissingFiles("QA_db_utilities::GetMissingFilesMC");

  # get old reports
  $self->GetOldReports("QA_db_utilities::GetOldReportsMC");

  # browser banner for interactive display
  $self->BrowserBannerColor("red");
  $self->BrowserBannerLabel("MC Data Nightly Tests");

}
#========================================================
sub debug{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();

  $self->TopDir("$home/debug");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database stuff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");

  # utilities for KeyList_object
  $self->GetSelectionOptions("Db_KeyList_utilities::GetNightlySelectionsMC");
  $self->GetSelectedKeys("Db_KeyList_utilities::GetNightlyKeysMC");

  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyMC");

  # find missing files
  $self->GetMissingFiles("QA_db_utilities::GetMissingFilesMC");

  # get old reports
  $self->GetOldReports("QA_db_utilities::GetOldReportsMC");

  # browser banner for interactive display
  $self->BrowserBannerColor("yellow");
  $self->BrowserBannerLabel("Debug");

}
#========================================================
sub online_raw{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();
  $self->TopDir("$home/debug");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database stuff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");

  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyReal");

  # browser banner for interactive display
  $self->BrowserBannerColor("green");
  $self->BrowserBannerLabel("Raw Data");

}
#========================================================
sub online_dst{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();
  $self->TopDir("$home/debug");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database suff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");


  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyReal");

  # browser banner for interactive display
  $self->BrowserBannerColor("green");
  $self->BrowserBannerLabel("DST Data");

}
#========================================================
sub online_debug{

  my $self = shift;
  @_ and my @args = @_;
  #------------------------------------------------------
  my $home = $self->Home();
  $self->TopDir("$home/debug");
  $self->TopDirWWW("http://duvall.star.bnl.gov/~starqa/qa_db");

  $self->StandardDirectories();
  
  $self->KeyList_obj("KeyList_object_nightly");
  $self->QA_obj("QA_object_nightly");
  
  # database suff
  $self->dbFile("TestJobs");
  $self->FileCatalog("FilesCatalog");
  $self->JobStatus("JobStatus");
  $self->dbQA("nightly_QA");


  # for updating from DB
  $self->UpdateRoutine("Db_update_utilities::UpdateQANightlyReal");

  # browser banner for interactive display
  $self->BrowserBannerColor("green");
  $self->BrowserBannerLabel("Online Debug");

}
