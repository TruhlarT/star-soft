#! /usr/bin/perl

# pmj 18/5/00

#========================================================
package Browser_object;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Storable;
use Data::Dumper;

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
  my $KeyList_obj = $gDataClass_object->KeyList_obj();

  $self->{_KeyList} = new $KeyList_obj; # depends on type of data
  $self->{_Hidden}  = new HiddenObject_object;

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
  my $doc_link = 
      "http://duvall.star.bnl.gov/STARAFS/comp/pkg/dev/cgi/qa/doc/index.html";
#  my $doc_string = "<a href=$doc_link target='display'>Documentation </a>";
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

  # job selection menu
  my $selection_string = $self->KeyList->JobPopupMenu(); 

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

  my $rightmost_buttons_string =  "<tr> $expert_string <tr> $comment_string";
  
  $gServer_object->ServerType() eq "offline" and do{
    my $button_string = Browser_utilities::start_rcas_lsf_monitor();
    $rightmost_buttons_string .= "<tr> $button_string";
  };


  print qq{
	<table border=0, width=100%, valign=top, align=center>
        <tr valign=top>
	    <td> $selection_string
	    <td> <table border=0, valign=top, align=center>
	      $rightmost_buttons_string
                 </table>
        </table>};
  #-----------------------------------------------------------------------------
  if( $self->ExpertPageFlag() ){
    print "<hr>$expert_action_string<hr>";
  }
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
  
  $io = new IO_object("BackupStatusFile");
  $fh = $io->Open();

  $fh and do{
    $line = <$fh>;
    chomp $line;
    print "Last backup at $line <br>\n";
  };

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
  
  # check that Display datasets has been clicked
  $gCGIquery->param('Display datasets') or return;

  # get selected keys - also make QA_objects
  my @selected_keys = $self->KeyList->GetSelectedKeyList;

  # no keys match query, get out
  unless (scalar @selected_keys) {
    print h2('No QA datasets match your query.  Try again.');
    return;
  }

  # add the messages
  my @key_list = $self->KeyList->AddMessagesToKeyList(@selected_keys);

  # print header...
  #print h2("Dataset selection: $selection_string");  

  $self->ExpertPageFlag() 
    and &Browser_utilities::display_expert_page_buttons;
 
  $gCGIquery->param('enable_add_edit_comments') 
    and  &Browser_utilities::display_comment_buttons;
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
      
      if ( $key =~ /global/ ){
	$data_string = "<strong>Global comment</strong> ". 
                       "(<font size=1>Message key: $key</font>):" .
	               " Author $author; Date $time; ";
      }
      else{
	($temp = $key) =~ s/\.msg//;
	$data_string = "<strong>Comment for run $temp </strong " .
	               "(<font size=1>Message key: $key</font>):" .
	               "Author $author;";
      }
  
      $data_string .= "<br>$text";
      
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
      my $logfile_report = $QA_object_hash{$key}->LogReportStorable;
      -s $logfile_report or next;
      
      $data_string        = $QA_object_hash{$key}->DataDisplayString;
      $creation_string    = $QA_object_hash{$key}->CreationString;
      $run_summary_string = $QA_object_hash{$key}->JobSummaryString;
      $qa_summary_string  = $QA_object_hash{$key}->QASummaryString;
      $button_string      = $QA_object_hash{$key}->ButtonString;
      
      push(@table_rows, td( [$data_string, $creation_string, 
			     $run_summary_string, 
			     $qa_summary_string, $button_string] ) );
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
  my $url = "http://www.star.bnl.gov/~jacobs/contacts.html";

  my $string = "<a href=$url target = 'documentation'>Contacts </a>";
  return $string;
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
