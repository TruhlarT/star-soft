#! /usr/bin/perl 
#
# general object to contain pushbuttons
#
# pmj 14/11/99
#
#=========================================================
package Button_object;
#=========================================================
use CGI qw/:standard :html3/;
use Cwd;

use File::stat;

use File::Copy;
use File::Find;
use File::Basename;

use Data::Dumper;

use Server_utilities;
use Browser_object;
use QA_globals;
use QA_utilities;

use CompareReport_object;

#=========================================================
1.;
#=========================================================

sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  $gBrowser_object->Hidden->NewButtonObject(1);

  return $self;
}
#========================================================
sub _init{

  my $self = shift;

  $method_name = shift;  
  $button_value = shift;
  @_ and $report_key = shift;

  # pmj 26/8/00 save rest of arguments
  @_ and @args = @_;

  #-------------------------------------------------

  $self->MethodName($method_name);
  $self->ButtonValue($button_value);
  $report_key and $self->ReportKey($report_key);
  @args and $self->Args(@args);

  # generate a unique name for the button, put reference to this
  #object into a hash that persists over multiple calls to script
  
  $name = $self->ButtonName();
  $Button_object_hash{$name} = \$self;

#  &QA_utilities::print_button_object_hash;
}
#========================================================
sub MethodName{
  my $self = shift;
  @_ and $self->{MethodName} = shift;
  return $self->{MethodName};
}
#========================================================
sub ButtonValue{
  my $self = shift;
  @_ and $self->{ButtonValue} = shift;
  return $self->{ButtonValue};
}
#========================================================
sub ButtonName{
  my $self = shift;

  # generate unique name for button (use address of instance of object)
#  $self->{ButtonName} or $self->{ButtonName} = \$self;

  $self->{ButtonName} or do{

    $name = $self->MethodName;

    $report_key = $self->ReportKey;
    $report_key and $name .= "\.$report_key";

    # add arguments to name, if any
    my @args = $self->Args();
    @args and do{
      my $string = join '_', @args;
      $name .= $string;
    };
    $self->{ButtonName} = $name;

  };

  return $self->{ButtonName};
}
#========================================================
sub ReportKey{
  my $self = shift;
  @_ and $self->{ReportKey} = shift;
  return $self->{ReportKey};
}
#========================================================
sub Args{
  my $self = shift;
  @_ and @{$self->{Args}} = @_;
  return @{$self->{Args}};
}
#========================================================
sub SubmitString{
  my $self = shift;

  my $button_name = $self->ButtonName;
  my $button_value = $self->ButtonValue;

  my $string = $gCGIquery->submit("$button_name","$button_value");

  return $string;
}
#========================================================
sub ButtonAction{
  my $self = shift;

  $method = $self->MethodName;
  $status = eval "\$self->$method";

  $@ and die "Button_object::ButtonAction: Error calling method $method <br> \n";
}
#========================================================
sub TestSub{

  my $self = shift;
  #-------------------------------------------------------

  print "In Button_object::TestSub, here is dump of object: <br> \n";

  print "<pre> ", Dumper(\$self), "</pre> <br> \n";

}
#========================================================
sub ExpertPageRequest{

  my $self = shift;

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<h3>Enter password for expert's page:</h3> \n",
  print $gCGIquery->startform(-action=>"$script_name/upper_display", -TARGET=>"list"); 
  print $gCGIquery->password_field('expert_pw', '', 20, 20);
  print $hidden_string;
  print $gCGIquery->endform;
  
}
#========================================================
sub EnableDSV{

  my $self = shift;
  #-------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<h3>Enable DSV</h3> \n";
  print "This button enables the use in this web page of DSV, Duncan Prindle's DataSetViewer, to",
  " allow you to look in detail at the events in the .dst.xdf file for a given run. Use of it",
  " here is under development, and though it appears to work, it is slow at remote sites and",
  " should be used with caution. In addition, the interface to this web page is somewhat ",
  " messy and is under development. Please send me any comments or questions. pmj 1/12/99"; 
    
  print "<h4>To enable DSV, enter your DISPLAY environment variable below. Otherwise, don't",
  " enter anything and do a different operation in the upper frame.",
  " If an incorrect DISPLAY value has been entered previously, simply press the 'Enable DSV' button",
  " and enter the correct one.</h4> \n";

  print $gCGIquery->startform(-action=>"$script_name/upper_display", -TARGET=>"list"); 
  print $gCGIquery->textfield('display_env_var', '', 50, 80);
  print $hidden_string;
  print $gCGIquery->endform;
  
}
#========================================================
sub UpdateCatalogue{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3> Updating catalogue... </h3> \n";
  &QA_utilities::print_refresh;

#  my $KeyList_obj = $gDataClass_object->KeyList_obj();  
#  my $key_list = update $KeyList_obj;
 
  &QA_utilities::doUpdate;
 
  #-------------------------------------------------------
  return;
}
#========================================================
sub BatchUpdateQA{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3> Submitting batch job for catalogue update and global QA... </h3> \n";
  &QA_utilities::submit_batchjob('update_and_qa');
}
#========================================================
sub BatchUpdate{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3> Submitting batch job for catalogue update... </h3> \n";
  &QA_utilities::submit_batchjob('update');
}
#========================================================
sub ServerLog{

  my $self = shift;
  #-------------------------------------------------------
  &Server_utilities::display_server_log;
}
#========================================================
sub ServerBatchQueue{

  my $self = shift;
  #-------------------------------------------------------
  &Server_utilities::display_server_batch_queue;
}
#========================================================
sub BatchLog{

  my $self = shift;
  #-------------------------------------------------------
  &Server_utilities::display_batch_logfiles;
}
#========================================================
sub MoveOldReports{

  my $self = shift;
  #-------------------------------------------------------
  &IO_utilities::move_old_reports;
}
#========================================================
sub CshScript{

  my $self = shift;
  #-------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<h3>Enter csh scriptname to execute:</h3> \n",
  print $gCGIquery->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
  print $gCGIquery->textfield('csh_scriptname', '', 80, 120);
  print $hidden_string;
  print $gCGIquery->endform;
  
}
#========================================================
sub CrontabAdd{

  my $self = shift;

  my $io = new IO_object("CrontabFile");
  my $filename = $io->Name();
  
  print "<h4> Adding file $filename to crontab for starlib. Here are contents: <br> </h4>";
  
  my $fh = $io->Open();
  while (<$fh>){ print "$_ <br> \n";}
  undef $fh;

  $status = system("crontab $filename");

  print "...done. Status = $status <br> \n";

}
#========================================================
sub CrontabMinusL{

  my $self = shift;
  #-------------------------------------------------------
  print "<h4> Doing crontab -l for starlib: <br> </h4>";

  my $io = new IO_object("CrondirMinusLFile");
  my $filename = $io->Name();

  $status = system("$now/crontab_minus_l.csh $filename");
  print "...done. Status = $status <br> \n";
  
  print "<hr> Here is output: <br> <br>\n";

  my $fh = $io->Open();
  while (<$fh>){ print "$_ <br> \n";}
  undef $fh;

}
#========================================================
sub CrontabMinusR{

  my $self = shift;
  #-------------------------------------------------------
  
  print "<h4> Doing crontab -r for starlib. <br> </h4>";

  $status = system("crontab -r");

  print "...done. Status = $status <br> \n";
}
#========================================================
sub DoQaDataset{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3> Submitting batch job for QA on dataset... </h3> \n";

  # BEN(4jun2000):  one batchjob per key 
  my @key_list = $gCGIquery->param('selected_key_list');
  
  my $key;
  foreach $key (@key_list){
      &QA_utilities::submit_batchjob('do_qa', $key); 
  }
}
#========================================================
sub RedoQaDataset{

  my $self = shift;
  #-------------------------------------------------------
    print "<h3> Submitting batch job to redo QA on dataset... </h3> \n";

  # BEN(4jun2000):  one batchjob per key 
  my @key_list = $gCGIquery->param('selected_key_list');
  
  my $key;
  foreach $key (@key_list){
      &QA_utilities::submit_batchjob('redo_qa', $key); 
  }
}
#========================================================
sub RunDetails{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  $QA_object_hash{$report_key}->DisplayLogReport;
}
#========================================================
sub QaDetails {

  my $self = shift;
  my $report_key = $self->ReportKey;
  #-------------------------------------------------------

  $QA_object_hash{$report_key}->ShowQA;
}
#========================================================
sub ViewScalarsAndTests{

  my $self = shift;
  my $report_key = $self->ReportKey;
  #-------------------------------------------------------

  my ($file, $macro_name, $mult_class, $flag) = $self->Args();

  $QA_object_hash{$report_key}->ShowScalarsAndTests($file, $macro_name, $mult_class, $flag);
}
#========================================================
sub FilesAndReports{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  $QA_object_hash{$report_key}->DisplayFilesAndReports;
}
#========================================================
sub RunDSV{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  &QA_utilities::run_DSV($report_key);
}
#========================================================
#sub CompareSimilarRuns{
#
#  my $self = shift;
#  my $report_key = $self->ReportKey;
#
#  #-------------------------------------------------------
#  QA_report_io::setup_report_comparison($report_key);
#
#
#}
#========================================================
sub SetupCompareReport{

  # pmj 4/6/00 sets up report comparisons using CompareReports_object
  # replaces CompareSimilarRuns

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------

  my $ref = new CompareReport_object($report_key);

  # save reference as part of object
  $QA_object_hash{$report_key}->CompareReport_obj($ref);
  
  # initial display 
  $ref->InitialDisplay();

  
}
#========================================================
# obsolete pmj 11/9/00
#sub SelectMultipleReports{
#
#  my $self = shift;
#  my $report_key = $self->ReportKey;
#
#  #-------------------------------------------------------
#  my $ref = $QA_object_hash{$report_key}->CompareReport_obj();
#  $ref->SelectMultipleReports();
#}
#========================================================
sub DoCompareMultipleReports{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  my ($file, $macro_name, $mult_class) = $self->Args();

  my $ref = $QA_object_hash{$report_key}->CompareReport_obj();
  $ref->CompareMultipleReports($file, $macro_name, $mult_class);
}
#========================================================
sub DoCompareToReference{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  my $ref = new CompareReport_object($report_key);
  
  # save reference as part of object
  $QA_object_hash{$report_key}->CompareReport_obj($ref);

  #my $ref = $QA_object_hash{$report_key}->CompareReport_obj();
  $ref->CompareToReference();
}
#========================================================
sub RedoEvaluation{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  &QA_utilities::print_refresh;
  $QA_object_hash{$report_key}->DoQA('evaluate_only');

}
#========================================================
sub RedoQaBatch{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  print "<h3> Submitting batch job to redo QA on run $report_key... </h3> \n";
  &QA_utilities::submit_batchjob('redo_qa', $report_key);

}
#========================================================
sub DoQaBatch{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  print "<h3> Submitting batch job to do QA on run $report_key... </h3> \n";
  &QA_utilities::submit_batchjob('do_qa', $report_key);
}
#========================================================
sub ResetInProgress{
  my $self = shift;
  my $report_key = $self->ReportKey;

  my $qaID = $QA_object_hash{$report_key}->qaID;
  
  my $rows = QA_db_utilities::ResetInProgressFlag($qaID);

  if ($rows+=0){
    print h3("Reset $report_key as QA not done");
  }
  else{
    print h3("<font color=red>Error in resetting in progress flag</font>");
  }
}

#========================================================
sub EnableAddEditComments{

  my $self = shift;

  #---------------------------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  print "<h4>Enter your name (will be attached to comments you create): </h4> \n";

  print $gCGIquery->startform(-action=>"$script_name/upper_display", -TARGET=>"list"); 
  print $gCGIquery->textfield('enable_add_edit_comments', '', 50, 80);
  print $hidden_string;
  print "$string";
  print $gCGIquery->endform;

}
#========================================================
sub AddComment{

  my $self = shift;

  #--------------------------------------------------------

  $report_key = $self->ReportKey;

  if ($report_key) {
    $arg = $report_key;
  }
  else{
    $arg = 'global';
  }

  #--------------------------------------------------------

  &QA_utilities::comment_form($arg);

}
#========================================================
sub NewComment{

  my $self = shift;

  #--------------------------------------------------------

  $report_key = $self->ReportKey;

  if ($report_key) {
    $arg = $report_key;
  }
  else{
    $arg = 'global';
  }

  #--------------------------------------------------------

  &QA_utilities::create_comment_object($arg);

}
#========================================================
sub EditComment{

  my $self = shift;

  $message_key = $self->ReportKey;

  defined $message_key or do{
    print "Button_object::EditComment: report key not defined <br> \n";
    return;
  };

  &QA_utilities::edit_comment($message_key);

}
#========================================================
sub ModifyComment{

  my $self = shift;

  $message_key = $self->ReportKey;

  defined $message_key or do{
    print "Button_object::ModifyComment: report key not defined <br> \n";
    return;
  };

  &QA_utilities::modify_comment($message_key);

}
#========================================================
sub DeleteComment{

  my $self = shift;

  $message_key = $self->ReportKey;

  defined $message_key or do{
    print "Button_object::DeleteComment: report key not defined <br> \n";
    return;
  };

  &QA_utilities::delete_comment($message_key);

}
#========================================================
sub CleanUpHungJobs{
  my $self = shift;

  my $io;
  # get rid of all batch files
  $io       = new IO_object("BatchDir");
  my $batchDir = $io->Name();
  my $batchDH  = $io->Open() or die "Can't open $batchDir\n";
  
  unlink map { "$batchDir/$_" } grep { /^temp/ } readdir $batchDH;
  undef $io;

  # get rid of all update statements

  $io = new IO_object("UpdateDir");
  my $updateDir = $io->Name();
  my $updateDH  = $io->Open() or die "Can't open $updateDir\n";

  unlink map { "$updateDir/$_" } grep { /^temp/ } readdir $updateDH;

  # change the flag in the db

  QA_db_utilities::ResetQANotDone();
}

#=========================================================
# lets the users modify the default references

sub SetDefaultReferences{
  my $self = shift;

  CompareReport_utilities::SetDefaultReferences();

}
  
#=========================================================
# add a default reference

sub AddReference{
  my $self = shift;

  my $method = $self->MethodName;
  my $name   = $self->ButtonName;

  # extract the datatype from the button name
  (my $dataType = $name) =~ s/$method//;
  
  my $report_key = $gCGIquery->param('reference_key');

  CompareReport_utilities::ProcessReference("Add",$report_key,$dataType);
    
}
#=========================================================
# delete a default reference

sub DeleteReference{
  my $self = shift;

  my $method = $self->MethodName;
  my $name   = $self->ButtonName;

  # extract the datatype from the button name
  (my $dataType = $name) =~ s/$method//;
  
  my $report_key = $gCGIquery->param('reference_key');

  CompareReport_utilities::ProcessReference("Delete",$report_key,$dataType);
}
#=========================================================
sub DeleteUserReferences{

  # pmj 7/9/00

  my $self = shift;

  my $io =  new IO_object("UserReferenceFile");
  my $file = $io->Name();

  unlink $file;

  print "User references deleted<br>\n";

}
#==========================================================
# change the old default with the new reference

sub ChangeReference{
  my $self = shift;

  my $method = $self->MethodName;
  my $name   = $self->ButtonName;

  # extract the datatype from the button name
  (my $dataType = $name) =~ s/$method//;
  
  # what the user typed in the text field
  my $report_key = $gCGIquery->param('reference_key');

  # the default value of the text field
  my $oldKey = $gCGIquery->param('old_key');

  
  CompareReport_utilities::ProcessReference("Change",$report_key,$dataType,$oldKey);

}

#==========================================================

sub SetUserReference{
  my $self = shift;

  my $report_key = $self->ReportKey();

  $gBrowser_object->AddUserReference($report_key);

  my @reference_list = CompareReport_utilities::GetUserReferences();

  #---
  print "<h4>Data set $report_key added to references</h4>\n";

}
