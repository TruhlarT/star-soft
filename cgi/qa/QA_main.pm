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

use QA_report_object;
use QA_report_io;

#=========================================================

$query = new CGI;
print $query->header;

#---------------------------------------------------------
# this turns off "automatic escaping", which is the default and which
# disables HTML character sequences in labels
#$query->autoEscape(undef);
#--------------------------------------------------------------------

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
    $path_info = 'display_data';
    $query->param("$cron_job", 1);
  }
#--------------------------------------------------------
# check if certain fields have changed - if so, clear bottom of page
#&clear_page_on_field_change;
#--------------------------------------------------------
&QA_utilities::cleanup_topdir;
#-----------------------------------------------------------------------------
# get all available qa objects (both data on and not on disk)
# puts all objects into QA_object_hash

@QA_key_list = &QA_utilities::get_QA_objects;
#-----------------------------------------------------------------------------
&list_datasets if $path_info =~ /list_datasets/;
&display_data if $path_info =~ /display_data/;
#-----------------------------------------------------------------------------

print  $query->end_html;

### END OF MAIN ###
#=================================================================
### END OF MAIN ###
#=================================================================

#=============================================================
sub list_datasets{

  #--------------------------------------------------------

  QA_cgi_utilities::print_page_header("Offline Software QA");		    

  #-----------------------------------------------------------------------------
  &check_for_expert_page;
  #--------------------------------------------------------
  &starting_display;
  #-----------------------------------------------------------------------------
  $select_dataset = $query->param('select_dataset');
  
  get_selected_key_list($select_dataset);
  
  display_datasets($select_dataset);
}
#==========================================================================
sub display_data{

  #-------------------------------------------------------------------------
    my $string = &QA_utilities::hidden_field_string;
    print "$string";
  #-------------------------------------------------------------------------
  #print "In display_data, here are query values: <br> \n";
  #print $query->dump;
  #-----------------------------------------------------------------------------
  &check_for_expert_page;
  #-----------------------------------------------------------------------------
  &check_for_csh_script;
  #-------------------------------------------------------------------------
  $select_dataset = $query->param('select_dataset');
  get_selected_key_list($select_dataset);
  #-----------------------------------------------------------------------------
  my $do_this_file = 0;
  my $update_catalogue = 0;
  my $batch_update_qa = 0;
  my $do_qa_dataset = 0;
  my $redo_qa_dataset = 0;
  my $expert_page_request = 0;
  my $csh_script = 0;
  #-----------------------------------------------------------------------------
  # which button was pushed?

 GETBUTTON: {

    $query->param('update_catalogue') and do{
      $update_catalogue = 1;
      last GETBUTTON;
    };

    $query->param('batch_update_qa') and do{
      $batch_update_qa = 1;
      last GETBUTTON;
    };

    $query->param('server_log') and do{
      &QA_server_utilities::display_server_log;
      last GETBUTTON;
    };

    $query->param('server_batch_queue') and do{
      &QA_server_utilities::display_server_batch_queue;
      last GETBUTTON;
    };

    $query->param('batch_log') and do{
      &QA_server_utilities::display_batch_logfiles;
      last GETBUTTON;
    };
    
    $query->param('do_qa_dataset') and do{
      $do_qa_dataset = 1;
      last GETBUTTON;
    };
    
    $query->param('redo_qa_dataset') and do{
      $redo_qa_dataset = 1;
      last GETBUTTON;
    };
    
    $query->param('expert_page_request') and do{
      $expert_page_request = 1;
      last GETBUTTON;
    };
    
    $query->param('csh_script') and do{
      $csh_script = 1;
      last GETBUTTON;
    };
    
    $query->param('crontab_add') and do{
      &QA_utilities::crontab_add;
      last GETBUTTON;
    };
    
    $query->param('crontab_l') and do{
      &QA_utilities::crontab_l;
      last GETBUTTON;
    };
    
    $query->param('crontab_r') and do{
      &QA_utilities::crontab_r;
      last GETBUTTON;
    };
    
    foreach $report_key ( @selected_key_list ){
      foreach $suffix ( "show_log_report", "show_qa", "show_files", 
			"setup_report_comparison", "do_report_comparison",
			"do_qa_batch", "redo_evaluation", "redo_qa_batch"){
	
	$temp = $report_key.".".$suffix;
	
	$query->param($temp) and do{
	  
	  $query->param('report_key_selected', $report_key);
	  $query->param('button_action', $suffix);
	  $do_this_file = 1;
	  last GETBUTTON;
	};
      }
    }
  }
  
  #-----------------------------------------------------------------------------
  $report_key = $query->param('report_key_selected');
  $button_action = $query->param('button_action');
  #-----------------------------------------------------------------------------

  $batch_update_qa and do{
    print "<h3> Submitting batch job for catalogue update and global QA... </h3> \n";
    &QA_utilities::submit_batchjob('update_and_qa');
  };

  #---

  $update_catalogue and do{
    print "<h3> Updating calatogue... </h3> \n";
    &print_refresh;
    QA_utilities::get_QA_objects('update');
  };

  #---

  $do_qa_dataset and do{
    print "<h3> Submitting batch job for QA on dataset... </h3> \n";
    &QA_utilities::submit_batchjob('do_qa', @selected_key_list);
  };

  #---

  $redo_qa_dataset and do{
    print "<h3> Submitting batch job to redo QA on dataset... </h3> \n";
    &QA_utilities::submit_batchjob('redo_qa', @selected_key_list);
  };


  #---

  $expert_page_request and do{
    print "<h3>Enter password for expert's page:</h3> \n",
    print $query->startform(-action=>"$script_name/list_datasets", -TARGET=>"list"); 
    print $query->password_field('expert_pw', '', 20, 20);
    my $string = &QA_utilities::hidden_field_string;
    print "$string";
    print $query->endform;
  };

  #---

  $csh_script and do{
    print "<h3>Enter csh scriptname to execute:</h3> \n",
    print $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"); 
    print $query->textfield('csh_scriptname', '', 80, 120);
    my $string = &QA_utilities::hidden_field_string;
    print "$string";
    print $query->endform;
  };

  #-----------------------------------------------------------------------------
  if ($do_this_file and $report_key){  
    
    #---

  BUTTONACTION: {
      
      $button_action eq "show_log_report" and do {
	$QA_object_hash{$report_key}->DisplayLogfileReport;
	last BUTTONACTION;
      };
      
      $button_action eq "show_files" and do {
	$QA_object_hash{$report_key}->DisplayFilesAndReports;
	last BUTTONACTION;
      };
      
      $button_action eq "show_qa" and do {
	$QA_object_hash{$report_key}->ShowQA;
	last BUTTONACTION;
      };

      $button_action eq "setup_report_comparison" and do {
	QA_report_io::setup_report_comparison($report_key);
	last BUTTONACTION;
      };

      $button_action eq "do_report_comparison" and do {
	QA_report_io::do_report_comparison($report_key);
	last BUTTONACTION;
      };
      
      $button_action eq "do_qa" and do {
	$QA_object_hash{$report_key}->DoQA;
	last BUTTONACTION;
      };
      
      $button_action eq "redo_evaluation" and do {
	&print_refresh;
	$QA_object_hash{$report_key}->DoQA('evaluate_only');
	last BUTTONACTION;
      };

      $button_action eq "redo_qa_batch" and do {
	print "<h3> Submitting batch job to redo QA on run $report_key... </h3> \n";
	&QA_utilities::submit_batchjob('redo_qa', $report_key);
	last BUTTONACTION;
      };

      $button_action eq "do_qa_batch" and do {
	print "<h3> Submitting batch job to do QA on run $report_key... </h3> \n";
	&QA_utilities::submit_batchjob('do_qa', $report_key);
	last BUTTONACTION;
      };
      
    }
    
  }
  
}
#===================================================================
sub clear_page_on_field_change{

  # clears page if a selection changes between invocations

#  print "clear_page called... <br> \n";

#  print $query->dump;

  @dataset_array = $query->param('select_dataset');

#  print "dataset array = @dataset_array <br> \n";
#-----------------------------------------------------------------
  undef $clear_page;

  if ($#dataset_array > 0){
    $dataset_array_previous = $query->param('dataset_array_previous');
    $#dataset_array > $dataset_array_previous and  $clear_page = 1;
  }
  $query->param('dataset_array_previous', $#time_array);

#-----------------------------------------------------------------

  defined ($clear_page) and do{
    my $save = $query->param('select_dataset');
    $query->delete('select_dataset');
    &display_data;
    $query->param('select_dataset', $save);
  };
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
    $query->startform(-action=>"$script_name/list_datasets", -TARGET=>"list").
      $query->popup_menu('select_dataset', \@selection_list, $selection_list[0], \%selection_hash).
	"<P>".$query->submit('Display selected dataset').
	  $hidden_string.$query->endform;

  if($global_expert_page){  

    $action_string = "<H3>Global actions:</H3>".
      $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"). 
	$query->submit('update_catalogue', 'Update Catalogue')."<br>".
	  $query->submit('batch_update_qa', 'Update Catalogue and QA (batch job)')."<br>".
	    $query->submit('server_log', 'Server Log').
	      $query->submit('server_batch_queue', 'Server Batch Queue').
		$query->submit('batch_log', 'Batch Logfiles')."<br>".
		  $query->submit('csh_script', 'Run csh script')."<br>".

    $action_string .= $query->submit('crontab_add', 'Add crontab.txt').
      $query->submit('crontab_l', 'Do crontab -l').
	$query->submit('crontab_r', 'Do crontab -r').
	  $hidden_string.$query->endform;

    $expert_page_string = "<H3>This is the expert's page</H3>";

  }
  else{ 

    undef $action_string; 

    $expert_page_string = "<H3>Access expert's page<br>(do updates and QA):</H3>".
      $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"). 
	$query->submit('expert_page_request', "Expert's page").
	  $hidden_string.$query->endform;
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

    print $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"); 
    
    print $query->submit('do_qa_dataset', 'Do QA on whole dataset');
    print $query->submit('redo_qa_dataset', 'Redo QA on whole dataset');
    my $string = &QA_utilities::hidden_field_string;
    print "$string";
    
    print $query->endform;

  }

  #---------------------------------------------------    
  
  if ($#selected_key_list >= 0) {
    
    @table_heading = ('Data Set', 'Created/On disk?', 'Run Status', 'QA Status', '');
    @table_rows = th(\@table_heading);
    
    foreach $report_key ( @selected_key_list ){
      
      # make sure logfile report exists
      $logfile_report = $QA_object_hash{$report_key}->LogfileReportName;
      -s $logfile_report or next;

      $data_string = $QA_object_hash{$report_key}->DataDisplayString;
      $creation_string = $QA_object_hash{$report_key}->CreationString;
      $run_summary_string = $QA_object_hash{$report_key}->RunSummaryString;
      $qa_summary_string = $QA_object_hash{$report_key}->QASummaryString;
      $button_string = $QA_object_hash{$report_key}->ButtonString;
      
      push(@table_rows, td( [$data_string, $creation_string, $run_summary_string, 
			     $qa_summary_string, $button_string] ) );
    }
    
    print $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"); 
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
  "<frame src=$script_name/list_datasets name=list>",
  "<frame src=$script_name/display_data name=display>",
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
	    frame( {-name=>'list', -scr=>"$script_name/list_datasets"} ),
	    frame( {-name=>'display', -scr=>"$script_name/display_data"} )
	 );

  #exit 0;
}
#===========================================================
sub print_html_header {
  $title = shift;
  print $query->start_html($title);

}
#===========================================================
sub print_refresh{
  print "<h3> <font color = blue> To refresh upper panel when done, reselect dataset </font> </h3> \n";
  return;
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
