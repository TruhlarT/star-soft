#! /usr/bin/perl

# pmj 30/7/99
#=========================================================

#use CGI qw/:standard :html3 -no_debug/;
use CGI qw/:standard :html3/;

use CGI::Carp qw(fatalsToBrowser);
use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

use Time::Local;
use Data::Dumper;

# for ensuring that hash elements delivered in insertion order (See Perl Cookbook 5.6)
use Tie::IxHash;

#-------------------------------------------------------
use QA_utilities;
use QA_server_utilities;
use QA_object;
use QA_globals;

use QA_display_reports;
use QA_make_reports;

use Button_object;

use QA_report_object;
use QA_report_io;

#=========================================================

$query = new CGI;
print $query->header;

#---------------------------------------------------------
# this turns off "automatic escaping", which is the default and which
# disables HTML character sequences in labels
#$query->autoEscape(undef);
#-------------------------------------------------------------------------

# reset timing
&QA_utilities::print_timing(0.,0.);

#-------------------------------------------------------------------------
$path_info = $query->path_info;

$TITLE = 'Offline Software QA';
$script_name = $query->script_name;

$cron_job = $query->param('cron_job');

#---------------------------------------------------------
#print "path_info = $path_info, script_name = $script_name\n";

#foreach $string( @INC){print "$string \n";}
#---------------------------------------------------------

if(!$cron_job){

  # If no path information is provided, then create frame set
  
  if (!$path_info) {
    print_frameset($TITLE);
    exit 0;
  }

  print_html_header($TITLE);
}
else
  {
#    $path_info = 'lower_display';
    $path_info = 'batch';
#    $query->param("$cron_job", 1);
  }
#--------------------------------------------------------
&QA_utilities::cleanup_topdir;
#-----------------------------------------------------------------------------
# get all available qa objects (both data on and not on disk)
# puts all objects into QA_object_hash

@QA_key_list = &QA_utilities::get_QA_objects;

#--------------------------------------------------------------------
&upper_display if $path_info =~ /upper_display/;
&lower_display if $path_info =~ /lower_display/;
&batch if $path_info =~ /batch/;
#-----------------------------------------------------------------------------

print  $query->end_html;

### END OF MAIN ###
#=================================================================
### END OF MAIN ###
#=================================================================

#=============================================================
sub upper_display{

  #--------------------------------------------------------
  QA_cgi_utilities::print_page_header("Offline Software QA");		    
  #-----------------------------------------------------------------------------
  &check_for_expert_page;
  #--------------------------------------------------------
  &starting_display;
  #-----------------------------------------------------------------------------
  &button_actions;
  #-----------------------------------------------------------------------------
  display_datasets($select_dataset);
  #-----------------------------------------------------------------------------

}
#==========================================================================
sub lower_display{

  #-------------------------------------------------------------------------
  my $string = &QA_utilities::hidden_field_string;
  print "$string";
  #-------------------------------------------------------------------------
  #print "In lower_display, here are query values: <br> \n";
  #print $query->dump;
  #-----------------------------------------------------------------------------
  &check_for_expert_page;
  #-----------------------------------------------------------------------------
  &check_for_csh_script;
  #-----------------------------------------------------------------------------
  &button_actions;
}
#==========================================================================
sub batch{

  #-------------------------------------------------------

  print "In QA_main::batch, cron_job = $cron_job <br> \n";

 BATCH:{

    $cron_job eq batch_update_qa and do{
      print "<h3> Submitting batch job for catalogue update and global QA... </h3> \n";
      &QA_utilities::submit_batchjob('update_and_qa');      
      last BATCH;
    };

    # default

      print "<h3> No action taken for cron_job = $cron_job </h3> \n";
    
  }
}
#=================================================================
sub starting_display {

  #-------------------------------------------------------
  # get pull-down menu

  tie %selection_hash, "Tie::IxHash"; 
  
  # now look at all keys to extract possible subselections
  
  foreach $key ( @QA_key_list ){
    # get rid of date
    ($selection = $key) =~ s/\.\d{6}//;;
    
    # get rid of days of the week
    $selection =~ s/(Mon|Tue|Wed|Thu|Fri|Sat|Sun)\.//;

    # replace dots with spaces for readbility
    ($string = $selection) =~ s/\./ /g;
    
    $selection_hash{$selection} = $string;
  }
  
  @selection_list = ();

  #-----------------------------------------------------------
  
  foreach $key ( keys %selection_hash ){
    push @selection_list, $key;
  }

  @temp = sort selection_sort @selection_list;
  #-----------------------------------------------------------

  # now the generic stuff
  $selection_hash{on_disk} = "All datasets on disk";
  $selection_hash{all} = "All archived datasets";

  @selection_list = ("on_disk", "all");

  push @selection_list, @temp;

  #-----------------------------------------------------------

  $hidden_string = &QA_utilities::hidden_field_string;

  $select_data_string= "<H3>Select datasets:</H3>".
    $query->startform(-action=>"$script_name/upper_display", -TARGET=>"list").
      $query->popup_menu('select_dataset', \@selection_list, $selection_list[0], \%selection_hash).
	"<P>".$query->submit('Display selected dataset').
	  $hidden_string.$query->endform;

  if($global_expert_page){  

    $action_string = "<H3>Global actions:</H3>".
      $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display");

    $button_ref = Button_object->new('UpdateCatalogue', 'Update Catalogue');
    $action_string .= $button_ref->SubmitString."<br>";

    $button_ref = Button_object->new('BatchUpdateQA', 'Update Catalogue and QA (batch job)');
    $action_string .= $button_ref->SubmitString."<br>";

    $button_ref = Button_object->new('ServerLog', 'Server Log');
    $action_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('ServerBatchQueue', 'Server Batch Queue');
    $action_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('BatchLog', 'Batch Logfiles');
    $action_string .= $button_ref->SubmitString."<br>";

    $button_ref = Button_object->new('CshScript', 'Run csh script');
    $action_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('MoveOldReports', 'Move old reports');
    $action_string .= $button_ref->SubmitString."<br>";

    $button_ref = Button_object->new('CrontabAdd', 'Add crontab.txt');
    $action_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('CrontabMinusL', 'Do crontab -l');
    $action_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('CrontabMinusR', 'Do crontab -r');
    $action_string .= $button_ref->SubmitString;

    $hidden_string = &QA_utilities::hidden_field_string;
    $action_string .= $hidden_string.$query->endform;

    $expert_page_string = "<H3>This is the expert's page</H3>";

  }
  else{ 

    undef $action_string; 

    $expert_page_string = "<H3>Access expert's page<br>(do updates and QA):</H3>".
      $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display");

    $button_ref = Button_object->new('ExpertPageRequest', "Expert's page");
    $expert_page_string .= $button_ref->SubmitString;

    $expert_page_string .= $hidden_string.$query->endform;
  }

  #-----------------------------------------------------------

  @table_rows = (); 
  push( @table_rows, td( [$select_data_string, $expert_page_string, 
			  $action_string ] ) );

  print table( {-width=>'100%', -valign=>'top', -align=>'center'}, Tr(\@table_rows));

  my $string = &QA_utilities::hidden_field_string;
  print "$string";
  
  #-----------------------------------------------------------------------------
  # display update status

  my $update_filename = "$update_dir/last_update";
  -s $update_filename and do{ 
    open UPDATE, "$update_filename" or print "Cannot open update file $update_filename: $! \n";
    $line = <UPDATE>;
    close UPDATE;
    chomp $line;
    print "Last catalogue update at $line (East Coast time)<br>\n";
  };

  #-----------------------------------------------------------------------------
  # check for running batch jobs and report if update in progress

  opendir(DIR,$update_dir) or die "Cannot open update dir $update_dir:$! \n"; 
  while ( defined( $file = readdir(DIR) ) ){

    $file !~ /(\d+)\.csh/ and next;

    $batch_job_file = "$batch_dir/$file";

    $start_time = stat("$update_dir/$file")->mtime; 
    $time_string = " (started ".localtime($start_time).")";
    
    if ( -e $batch_job_file ){
      print "<font color=blue>Update and QA batch job in progress $time_string</font><br>\n";
    }
    else{
      $full_file = "$update_dir/$file";
      unlink($full_file);
    }
  }
  close DIR;

  #-----------------------------------------------------------------------------
  print "<HR>\n";
  #-----------------------------------------------------------------------------
  return;

}
#=================================================================
sub get_selected_key_list {

  my $select_dataset = shift;
  
  #-----------------------------------------------------------------------------

  @selected_key_list = ();
  $select_dataset or return @selected_key_list;
  #-----------------------------------------------------------------------------

 SWITCH: {
    
    # look for generic stuff first
    
    $select_dataset =~ /all/ and do {
      @selected_key_list = @QA_key_list;
      last SWITCH;
    };
    
    $select_dataset =~ /on_disk/ and do {
      foreach $report_key ( @QA_key_list ) {
	$QA_object_hash{$report_key}->OnDisk() and push @selected_key_list, $report_key;
      }
      last SWITCH;
    };

    # now pattern match selection to report keys
    
    foreach $report_key ( @QA_key_list ) {
      # get rid of days of week
      ($temp = $report_key) =~ s/(Mon|Tue|Wed|Thu|Fri|Sat|Sun)\.//;
      $temp =~ /$select_dataset/ and push @selected_key_list, $report_key;
    }
    last SWITCH;

  }

  #-----------------------------------------------------------------------------

  return @selected_key_list;
  
}
#=================================================================
sub display_datasets{

  my $select_dataset = shift;
  #---------------------------------------------------    

  $select_dataset or return;

  print "<H2> Dataset selection: $selection_hash{$select_dataset} </H2>\n";
  
  #---------------------------------------------------    
  
  if ($global_expert_page){

    print $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
    
    $button_string = "";

    $button_ref = Button_object->new('DoQaDataset', 'Do QA on whole dataset');
    $button_string .= $button_ref->SubmitString;

    $button_ref = Button_object->new('RedoQaDataset', 'Reoo QA on whole dataset');
    $button_string .= $button_ref->SubmitString;

    $hidden_string = &QA_utilities::hidden_field_string;
    $button_string .= $hidden_string.$query->endform;

    print $button_string;

  }

  #---------------------------------------------------    
  
  if ($#selected_key_list >= 0) {
    
    @table_heading = ('Data Set', 'Created/On disk?', 'Run Status', 'QA Status', '');
    @table_rows = th(\@table_heading);

    foreach $report_key ( @selected_key_list ){

      # make sure logfile report exists
      $logfile_report = $QA_object_hash{$report_key}->LogReportName;
      -s $logfile_report or next;

      $data_string = $QA_object_hash{$report_key}->DataDisplayString;
      $creation_string = $QA_object_hash{$report_key}->CreationString;
      $run_summary_string = $QA_object_hash{$report_key}->RunSummaryString;
      $qa_summary_string = $QA_object_hash{$report_key}->QASummaryString;
      $button_string = $QA_object_hash{$report_key}->ButtonString;
      
      push(@table_rows, td( [$data_string, $creation_string, $run_summary_string, 
			     $qa_summary_string, $button_string] ) );
    }
    
    print $query->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
    print table( {-border=>undef}, Tr(\@table_rows));
    my $string = &QA_utilities::hidden_field_string;
    print "$string";

    print $query->endform;
    
    print "<HR>\n";
  }
  else{
    print "<h2> No datasets found on disk. </h2> \n"; 
  }
}
#===========================================================
# Create the frameset
sub print_frameset{

  $title = shift;
 
  print "<html><head><title>$title</title></head>",
  "<frameset rows=60%,40%>",
  "<frame src=$script_name/upper_display name=list>",
  "<frame src=$script_name/lower_display name=display>",
  "</frameset> \n";

    exit 0;
}
#===========================================================
# Create the frameset
sub print_frameset_test{

  #print "<br> In print_frameset... <br> \n"; 

  $title = shift;
 
  print title("$title"),
  frameset( {-rows=>'60%,40%'},
	    frame( {-name=>'list', -scr=>"$script_name/upper_display"} ),
	    frame( {-name=>'display', -scr=>"$script_name/lower_display"} )
	 );

  #exit 0;
}
#===========================================================
sub print_html_header {
  $title = shift;
  print $query->start_html($title);

}
#===========================================================
sub check_for_expert_page{
  $expert_pw = $query->param('expert_pw');
  $global_expert_page = ($expert_pw eq "qaexpert")? 1:0;
}
#===========================================================
sub check_for_csh_script{
  
  $scriptname = $query->param('csh_scriptname');

  # undef script name so it isn't run again
  $query->delete('csh_scriptname');

  # get rid of leading and following whitespace
  $scriptname =~ s/\s+//g;
  
  # something there?
  $scriptname or return;
  
  # for safety, cannot be in afs area
  $scriptname =~ /afs/ and do{
    print "File $scriptname contains string 'afs', not allowed.",
    " Move it to a local disk area and try again. <br> \n";
    return;
  };

  
  # is it an existing csh script?
  if ($scriptname =~ /\.csh$/ and -x $scriptname){
    print "Running script $scriptname...<br> \n";
    $status = system("$scriptname");
    print "...done; status = $status <br> \n";
    
  }
  else{
    print "File $scriptname does not have type .csh or",
    " is not executable by server; not run <br> \n";
  }
  
}
#============================================================
sub selection_sort{

  ($a_version, $a_sim, $a_year) = split ' ',$a;
  ($b_version, $b_sim, $b_year) = split ' ',$b;

  $a_version cmp $b_version
    or  
      $a_sim cmp $b_sim
	or  
	  $a_year cmp $b_year
	    or
	      $a cmp $b;
}
#============================================================
sub button_actions{

  $select_dataset = $query->param('select_dataset');
  get_selected_key_list($select_dataset);
  #-----------------------------------------------------------------------------
  
  @get_params = $query->param;
  
  # get button action
  foreach $param ( @get_params ){
    exists $Button_object_hash{$param} and do{
      $button_ref = $Button_object_hash{$param}; 
      $$button_ref->ButtonAction;
      last;
    };
  }
}
