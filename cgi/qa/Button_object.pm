#! /usr/bin/perl -w
#
# general object to contain pushbuttons
#
# pmj 14/11/99
#
#=========================================================
package Button_object;
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

  $method_name = shift;  
  $button_value = shift;
  @_ and $report_key = shift;

  #-------------------------------------------------

  $self->MethodName($method_name);
  $self->ButtonValue($button_value);
  $report_key and $self->ReportKey($report_key);

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
sub SubmitString{
  my $self = shift;

  my $button_name = $self->ButtonName;
  my $button_value = $self->ButtonValue;

  my $string = $query->submit("$button_name","$button_value");

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
  #-------------------------------------------------------
  print "<h3>Enter password for expert's page:</h3> \n",
  print $query->startform(-action=>"$script_name/upper_display", -TARGET=>"list"); 
  print $query->password_field('expert_pw', '', 20, 20);
  my $string = &QA_utilities::hidden_field_string;
  print "$string";
  print $query->endform;
  
}
#========================================================
sub UpdateCatalogue{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3> Updating calatogue... </h3> \n";
  &QA_utilities::print_refresh;
  QA_utilities::get_QA_objects('update');
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
sub ServerLog{

  my $self = shift;
  #-------------------------------------------------------
  &QA_server_utilities::display_server_log;
}
#========================================================
sub ServerBatchQueue{

  my $self = shift;
  #-------------------------------------------------------
  &QA_server_utilities::display_server_batch_queue;
}
#========================================================
sub BatchLog{

  my $self = shift;
  #-------------------------------------------------------
  &QA_server_utilities::display_batch_logfiles;
}
#========================================================
sub MoveOldReports{

  my $self = shift;
  #-------------------------------------------------------
  &QA_utilities::move_old_reports;
}
#========================================================
sub CshScript{

  my $self = shift;
  #-------------------------------------------------------
  print "<h3>Enter csh scriptname to execute:</h3> \n",
  print $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
  print $query->textfield('csh_scriptname', '', 80, 120);
  my $string = &QA_utilities::hidden_field_string;
  print "$string";
  print $query->endform;
  
}
#========================================================
sub CrontabAdd{

  my $self = shift;
  #-------------------------------------------------------

  $now = cwd();
  $filename = "$now/crontab.txt";

  print "<h4> Adding file $filename to crontab for starlib. Here are contents: <br> </h4>";
  
  open CRONTAB, $filename;
  while (<CRONTAB>){ print "$_ <br> \n";}
  close CRONTAB;

  $status = system("crontab $filename");

  print "...done. Status = $status <br> \n";

}
#========================================================
sub CrontabMinusL{

  my $self = shift;
  #-------------------------------------------------------
  print "<h4> Doing crontab -l for starlib: <br> </h4>";

  $filename = "$cron_dir/minus_l.txt";

  $now = cwd();
  $status = system("$now/crontab_minus_l.csh $filename");
  print "...done. Status = $status <br> \n";
  
  print "<hr> Here is output: <br> <br>\n";

  open CRONFILE, $filename;
  while (<CRONFILE>){ print "$_ <br> \n";}
  close CRONFILE;
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
  &QA_utilities::submit_batchjob('do_qa', @selected_key_list);
}
#========================================================
sub RedoQaDataset{

  my $self = shift;
  #-------------------------------------------------------
    print "<h3> Submitting batch job to redo QA on dataset... </h3> \n";
    &QA_utilities::submit_batchjob('redo_qa', @selected_key_list);
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
sub FilesAndReports{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  $QA_object_hash{$report_key}->DisplayFilesAndReports;
}
#========================================================
sub CompareSimilarRuns{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  QA_report_io::setup_report_comparison($report_key);
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
sub DoRunComparison{

  my $self = shift;
  my $report_key = $self->ReportKey;

  #-------------------------------------------------------
  QA_report_io::do_report_comparison($report_key);
}
