#! /opt/star/bin/perl

# pmj 18/5/00

#========================================================
package Browser_object;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Storable;
use Data::Dumper;
use POSIX qw(ceil);

use QA_globals;
use QA_object;
use Server_object;
use Button_object;
use HiddenObject_object;
use IO_object;
use IO_utilities;
use Browser_utilities;
use KeyList_object_offline;
use KeyList_object_nightly;
use KeyList_object_online;
use KeyList_object_offline_fast;
use Db_KeyList_utilities;
use CompareReport_utilities;

use DataClass_object;

use strict;
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

  my $self  = shift;
  my $title = shift;
  my $server_type = shift;

  $self->Title($title);
  $self->ServerType($server_type);

  # uses 2 classes
  no strict 'refs';
  $self->{_KeyList} = 
    $gDataClass_object->KeyList_obj->new(); # depends on type of data
  $self->{_Hidden}  = new HiddenObject_object;

  

  # pmj 7/9/00 generate user reference filename
  my $io = new IO_object("UserReferenceFile");
  undef $io;

}


#===========================================================
sub StartHtml{

  my $self = shift;
  my $title = $self->Title();

  print $gCGIquery->start_html($title);
}
#===========================================================
sub EndHtml{
  my $self = shift;
  print $gCGIquery->end_html;
}
#===========================================================
# upper half of frame

sub UpperDisplay{
  my $self = shift;

  $self->PrintPageHeader();

  $self->ExpertPageFlag();

  $self->StartingDisplay();

  $self->ButtonActions();

  $self->DisplayDataset();

}
#==========================================================
# lower half of frame

sub LowerDisplay{
  my $self = shift;

  $self->ExpertPageFlag();

  $self->CheckForCshScript();

  $self->ButtonActions();
}
#==========================================================
sub PrintPageHeader{
  my $self = shift;

  my $server_type = $self->ServerType();

  my $colour = $gDataClass_object->BrowserBannerColor();
  my $text_colour = $gDataClass_object->BrowserBannerTextColor();
  my $class_label = $gDataClass_object->BrowserBannerLabel();

  my $contact_string = $self->ContactString();

  # where's the documentation?  
  #my $doc_link = $gCGIquery->script_name;
  #$doc_link =~ s/QA_main\.pm/doc\/index.html/;
  my $doc_link="http://www.star.bnl.gov/STARAFS/comp/qa/CurrentQADocs.html";
  my $doc_string = "<a href=$doc_link target='documentation'>Documentation </a>";

  #---
  # generate header string with pull-down menu
  # pmj 21/6/00

  my $script_name = $gCGIquery->script_name;
  my $header_string = $gCGIquery->startform(-action=>"$script_name/upper_display",
					    -TARGET=>"list");
  $header_string .= $self->Title();

  my $class_switch_string = Browser_utilities::SwitchDataTypeMenuLite();
  $header_string .= ": server=$server_type; data class = $class_switch_string";
					     
  my $hidden_string = $gBrowser_object->Hidden->Parameters;
  $header_string .= $hidden_string.$gCGIquery->endform;

  #---

  # this is the header

  print qq{
    <table border=0 width=100% cellpadding=0 bgcolor=$colour>
      <tr valign=center>
      <td align=left><br>	  
      <ul> <font color=$text_colour>
	<h2>$header_string</h2>
	      </font></ul> 
      <td><table border=0> 
      <tr> $doc_string <br>
      <tr> $contact_string
      </table>
      </table>
      <hr noshade>
    };
}

#===========================================================
sub ExpertPageFlag{
  my $self = shift;
  my $expert_pw = $gCGIquery->param('expert_pw');
  $self->{_ExpertPageFlag} = ($expert_pw eq "qaexpert")? 1:0;
}
#=================================================================
sub StartingDisplay{
  my $self = shift;

  # test 
  
  # job selection menu
  my $selection_string = $self->KeyList->JobPopupMenu(); 

  # switch class of data menu if not in Online
  # pmj 21/6/00 data class string moved to banner, this is no longer needed
  #my $switch_string    = Browser_utilities::SwitchDataTypeMenu();


  # comment form?
  my $comment_string 
    = Browser_utilities::start_comment_button();
  
  my ($expert_action_string, $expert_string);
  
  if( $self->ExpertPageFlag() )
  {  
  
    $expert_action_string = Browser_utilities::start_expert_buttons();
    $expert_string = h3("This is the expert's page");
  
  } 
  else 
  {
    $expert_string = Browser_utilities::start_expert_default();
  }


  #----------------------------------------------------------

  my $table_string = "<tr> $expert_string <tr> $comment_string";

  $gServer_object->ServerType eq "offline" and do{

    my $rcas_lsf_string = $self->RcasLsfMonitor();
    my $online_run_browser_string = $self->OnlineRunBrowser();

    $table_string .= "<tr> $rcas_lsf_string";
    $table_string .= "<br><tr> $online_run_browser_string";
  };
  #----------------------------------------------------------
  print qq{
	<table border=0, width=100%, valign=top, align=center>
        <tr>
	    <td> $selection_string
	    <td> <table border=0, valign=top, align=center>
                 <tr> $table_string
                 </table>
        </table>};

  #-----------------------------------------------------------------------------
  if( $self->ExpertPageFlag() ){
    print "$expert_action_string";
  }
  print hr;
  #-----------------------------------------------------------------------------
  # display update status
  my ($io, $fh, $line);

  $io = new IO_object("UpdateFile");
  $fh = $io->Open();

  $fh and do{ 
    $line = <$fh>;
    chomp $line;
    print "Last catalogue update at $line (East Coast time)<br>\n";
  };

  #-----------------------------------------------------------------------------
  # -- display backup status
  # temporarily remove this
  
#  $io = new IO_object("BackupStatusFile");
#  $fh = $io->Open();

#  $fh and do{
#    $line = <$fh>;
#    chomp $line;
#    print "Last backup at $line <br>\n";
#  };

#  $fh or do{
#      print "No backup available. <br>\n";
#  };

  #---------------------------------------------------------------
  # check for running batch jobs and report if update in progress

  my $string = &IO_utilities::CheckBatchStatus;
  print $string,"\n";
 
  print "<HR>\n";
  
  return;

}
#============================================================
sub ButtonActions{

  my $self = shift;
  
  my @get_params = $gCGIquery->param;

  # get button action
  foreach my $param ( @get_params ){
    exists $Button_object_hash{$param} and do{
      my $button_ref = $Button_object_hash{$param}; 
      $$button_ref->ButtonAction;
      last;
    };
  }

}
#=================================================================
sub DisplayDataset{
  my $self = shift;

  my $limit = $Db_KeyList_utilities::selectLimit;
  my $subset_len = 50; 

  my @selected_keys;	  
  # get out unless we're looking at messages or datasets
  return unless($gCGIquery->param('Display datasets') or
		$gCGIquery->param('Display messages') or
	        $gCGIquery->param('Next subset')      or
	        $gCGIquery->param('Previous subset')  or
	        defined $gCGIquery->param('Select subset'));
 
  $gCGIquery->param('enable_add_edit_comments') 
    and  &Browser_utilities::display_comment_buttons;

  my (@selected_keys);
  # are we looking for datasets?
  if ($gCGIquery->param('Display datasets')){
    # delete this parameter
    $gCGIquery->delete('selected_key_list');

    # get selected keys - also make QA_objects

    # pmj 5/9/00 **Also prints out DB query (this should be made a separate function)
    my @all_selected_keys = $self->KeyList->GetSelectedKeyList;


    #----
    # pmj 5/9/00 move these here...
    # show the references
    unless($gCGIquery->param('Display messages')){
      CompareReport_utilities::ShowReferences() 
	if $gDataClass_object->DataClass()=~/nightly_MC/;
      print "<hr>\n";
    }

    #----

    
    my $rows = scalar @all_selected_keys;
    # no keys match query, get out
    unless ( $rows ) {
      print h2('No QA datasets match your query.  Try again.');
      return;
    }
    # too many matches
    if ( $rows == $limit ){
      print h2(font({-color=>'red'},
		    "Over $limit rows from the database match your query.<br>",
		    "Please choose a more restrictive query.<br>"));
      return;
    }
    # if the selected keys is greater than the subset_size,
    # break it up into smaller blocks
    
    if ( $rows > $subset_len){
      
      $gCGIquery->param('previous_subset',1); 
      $gCGIquery->param('selected_key_list',@all_selected_keys);
      
      @selected_keys = splice(@all_selected_keys,0,$subset_len);
      
      my $n_subset = ceil($rows/$subset_len);
      my $popup    = 
	Browser_utilities::SelectSubsetMenu($subset_len,$n_subset,$rows, 1);
      my $more_button = Browser_utilities::SubmitButton('Next subset');
      my $row_ref  = td([ $popup, $more_button]);
      
      print "<center>",h3("Rows 1 - $subset_len (of $rows)"),
      table(Tr($row_ref)). "</center>";
      
    }
    else{
      print "<center>",h3("Rows 1 - $rows"),"</center>";
      @selected_keys = @all_selected_keys;
    }
  }
  elsif($gCGIquery->param('Next subset') ||
        $gCGIquery->param('Previous subset') ||
        defined $gCGIquery->param('Select subset')){    
    my $previous_subset   = $gCGIquery->param('previous_subset');
    
    my $current_subset;
    if ($gCGIquery->param('Next subset')){
      $current_subset    = $previous_subset + 1;
    }
    elsif($gCGIquery->param('Previous subset')){
      $current_subset    = $previous_subset - 1;
    }
    elsif(defined $gCGIquery->param('Select subset')){
      $current_subset    = $gCGIquery->param('Select subset');
    }
    $gCGIquery->param('previous_subset',$current_subset);

    my @all_selected_keys = $gCGIquery->param('selected_key_list');
    my $rows              = scalar @all_selected_keys;
    my $n_subset          = ceil($rows/$subset_len);
    my $is_last_subset    = ($current_subset == $n_subset);
    my $is_first_subset   = ($current_subset == 1);

    # if the current subset is the last subset, dont show the more button.
    # if the current subset is the first subset, dont show the previous button.
    # note that the current subset is numbered from 1
    my $more_button = Browser_utilities::SubmitButton('Next subset') 
      unless $is_last_subset;
			     
    my $previous_button = Browser_utilities::SubmitButton('Previous subset')
      unless $is_first_subset;
	  
    my $popup    
      = Browser_utilities::SelectSubsetMenu($subset_len,$n_subset,$rows, 
					    $current_subset);

    my $first_row = ($current_subset-1)*$subset_len + 1;
    my $last_row;
    if ($is_last_subset){
      $last_row = $rows;
    }
    else {
      $last_row = $current_subset*$subset_len;
    }
    
    @selected_keys = splice(@all_selected_keys,
			    ($current_subset-1)*$subset_len, $subset_len);

    my $row_ref = td([ $previous_button, $popup, $more_button]);
    print "<center>",
          h3("Rows $first_row - $last_row (of $rows)"), 
          table( Tr($row_ref) ), 
          "</center>";
  }

  # add the messages - resorts as well
  my @key_list = $self->KeyList->AddMessagesToKeyList(@selected_keys);

	
  # BUM - these buttons are causing problems...
  #$self->ExpertPageFlag() 
  #  and &Browser_utilities::display_expert_page_buttons;

  if (!scalar @key_list and $gCGIquery->param('Display messages')){
    print h2("No global messages\n");
    return;
  }
  #---------------------------------------------------------------------------

  # now display datasets
  my ($data_string, $creation_string, $run_summary_string,
	  $qa_summary_string, $button_string);

  my @table_heading = 
    ('Data Set', 'Created/On disk?', 'Job Status', 'QA Status', '');

  my @table_rows = th(\@table_heading);

  foreach my $key ( @key_list ){
    
    # check if this is message or report
    
    if ( $key =~ /\.msg/ ) {
      
      my $author = $QA_message_hash{$key}->Author;      
      my $temp   = $QA_message_hash{$key}->CreationEpochSec;
      my $time   = localtime($temp);
      my $text   = $QA_message_hash{$key}->MessageString;

      # pmj 15/9/00 get rid of references to sol in old messages
      $text =~ s/sol\.star\.bnl\.gov/www\.star\.bnl\.gov/g;
      #---

      $data_string = "<strong>";

      if ( $key =~ /global/ ){

	$data_string .= "Global comment<br> ". 
	               " Author $author; Date $time; ";
      }
      else{
	($temp = $key) =~ s/\.msg//;

	$data_string .= "Comment for job $temp <br> " .
	               "Author $author; ";
	# more info for offline real
	if ($gDataClass_object->DataClass() =~ /offline_real/){
	  # temp is the reportkey
	  $data_string .= 
	    "Run ID: " .  $QA_object_hash{$temp}->LogReport->RunID . "; " .
	    "File Seq: " . $QA_object_hash{$temp}->LogReport->FileSeq .
	    br . "\n";
	}

      }
  
      $data_string .= "</strong><br>$text";
      
      # check whether add and edit of comments is enabled
      $gCGIquery->param('enable_add_edit_comments') 
	and my $button_string = 
	  Browser_utilities::display_comment_string($key);
	
      # fill in the row
      my $row_string = td({-colspan=>4}, $data_string).td($button_string);
      push(@table_rows, $row_string);
      
    }
    
    else{ # print dataset
     
      # make sure logfile report exists

      defined  $QA_object_hash{$key} or next;
      my $logfile_report = $QA_object_hash{$key}->LogReportStorable;
      -s $logfile_report or next;
      
      $data_string        = $QA_object_hash{$key}->DataDisplayString;
      $creation_string    = $QA_object_hash{$key}->CreationString;
      $run_summary_string = $QA_object_hash{$key}->JobSummaryString;
      $qa_summary_string  = $QA_object_hash{$key}->QASummaryString;
      $button_string      = $QA_object_hash{$key}->ButtonString;
      
      push(@table_rows, td( [$data_string, $creation_string, 
			     $run_summary_string, 
			     $qa_summary_string, $button_string] ), "\n" );
    }
    
  }
  
  my $script_name   = $gCGIquery->script_name;
  my $hidden_string = $self->Hidden->Parameters;

  print $gCGIquery->startform(-action=>"$script_name/lower_display", 
			  -TARGET=>"display"); 
  print table( {-border=>undef}, Tr(\@table_rows));
  print $hidden_string;
  print $gCGIquery->endform;
  print "<HR>\n";
}

#===========================================================
sub CheckForCshScript{
  
  my $self = shift;

  my $scriptname = $gCGIquery->param('csh_scriptname');

  # undef script name so it isn't run again
  $gCGIquery->delete('csh_scriptname');

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
    my $status = system("$scriptname");
    print "...done; status = $status <br> \n";
    
  }
  else{
    print "File $scriptname does not have type .csh or",
    " is not executable by server; not run <br> \n";
  }
  
}
#===========================================================
# pmj 28/6/00 returns link to html page containing contact info 

sub ContactString{

  my $self = shift;
  
  #---------------------------------------------------------
  # doesn't work - why not???
  #my $server_name = $gCGIquery->server_name;
  #(my $base_name = $gCGIquery->script_name) =~  s/\/\w+?$//;
  #my $url = "http://$server_name$base_name/contacts.html";

  # temporary solution:
#  my $url = "http://www.star.bnl.gov/~jacobs/contacts.html";
  # BEN(9jul00):
  #my $url = $gCGIquery->script_name;
  #$url =~ s/QA_main\.pm/doc\/contacts.html/;
  
  # hardcoded 
  my $url ="http://www.star.bnl.gov/STARAFS/comp/qa/shifts/Contacts_QA_experts.html";

  my $string = "<a href=$url target = 'documentation'>Contacts </a>";
  return $string;
}
#===========================================================
# pmj 7/6/00 returns link to rcas/lsf monitor

sub RcasLsfMonitor{

  my $self = shift;
  
  #---------------------------------------------------------
  my $lsfTool = "LSF_tool?expertPW=".
      $gCGIquery->param("expert_pw");

  my $url = $gCGIquery->script_name;
  $url =~ s/QA_main\.pm/$lsfTool/e;

  my $string = "<a href=$url target = 'documentation'>Rcas/LSF monitor </a>";
  return $string;
}
#===========================================================
# pmj 6/8/00 returns link to Run Browser

sub OnlineRunBrowser{

  my $self = shift;
  
  #---------------------------------------------------------
  # pmj 23/8/00 point to new browser 
  #  my $url = "http://onlsun1.star.bnl.gov/dbRunBrowser.html";
  my $url = "http://ch2linux.star.bnl.gov/RunLogBrowser/Main.html";

  my $string = "<a href=$url target = 'documentation'>Online Run Log</a>";
  return $string;
}
#===========================================================
sub AddUserReference{

  my $self = shift;
  my $user_reference = shift;
  
  #--------------------------------------------------------------
  my ($io, $FH);
  $io = new IO_object("UserReferenceFile");
  $FH = $io->Open(">>");
  print $FH "$user_reference ";
  undef $io;
}

#===========================================================
# accessors

#sub Server{
#  return $_[0]->{_Server};
#}

sub KeyList{
  return $_[0]->{_KeyList};
}

sub Hidden{
  return $_[0]->{_Hidden};
}

sub Title{
  my $self = shift;
  @_ and $self->{_Title} = shift;
  return  $self->{_Title};
}

sub ServerType{
  my $self = shift;
  @_ and $self->{_ServerType} = shift;
  return  $self->{_ServerType};
}



1;
