#! /usr/bin/perl

# general utilities used by various scripts

# pmj 1/7/99
#=========================================================
package Browser_utilities;
#=========================================================
use CGI qw(:standard escapeHTML);

use Time::Local;
use Storable;

use Browser_object;
use QA_globals;
use Button_object;

use strict;
#=========================================================
1.;


#=========================================================
# see Browser::StartingDisplay

sub start_comment_button{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $button_ref 
    = Button_object->new('EnableAddEditComments', "Add or edit comments");

# pmj 28/6/00
#    h3('Add or edit comments:').
  my $string = $gCGIquery->startform(-action=>"$script_name/lower_display", 
		      -TARGET=>"display").
    $button_ref->SubmitString.
    $hidden_string.
    $gCGIquery->endform;  

  return $string;

}
#==========================================================
# see Browser_object::StartingDisplay

sub start_expert_buttons{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my ($row1, $row2);

  # -- first row --
  $row1 = $gCGIquery->startform(-action=>"$script_name/lower_display", 
		       -TARGET=>"display");

  my $button_ref = Button_object->new('UpdateCatalogue', 'Update Catalogue');
  $row1         .= $button_ref->SubmitString;

  $button_ref = Button_object->new('BatchUpdateQA', 'Update Catalogue and QA');
  $row1      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('ServerLog', 'Server Log');
  $row1      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('ServerBatchQueue', 'Server Batch Queue');
  $row1      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('BatchLog', 'Batch Logfiles');
  $row1      .= $button_ref->SubmitString;

  $row1      .= $hidden_string . $gCGIquery->endform();

  # -- second row --
  $row2 = $gCGIquery->startform(-action=>"$script_name/lower_display", 
		       -TARGET=>"display");
  
  $button_ref = Button_object->new('CshScript', 'Run csh script');
  $row2      .= $button_ref->SubmitString;


  $button_ref = Button_object->new('MoveOldReports', 'Move old reports');
  $row2      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('CrontabAdd', 'Add crontab.txt');
  $row2      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('CrontabMinusL', 'Do crontab -l');
  $row2      .= $button_ref->SubmitString;

#  $button_ref = Button_object->new('CrontabMinusR', 'Do crontab -r');
#  $row2      .= $button_ref->SubmitString;

  $button_ref = Button_object->new('CleanUpHangedJobs', 'Hung jobs');
  $row2      .= $button_ref->SubmitString;
  
  $button_ref = Button_object->new('EnableDSV','Enable DSV'); 
  $row2      .= $button_ref->SubmitString;
  
  $row2      .= $hidden_string . $gCGIquery->endform();

  # see global messages only
  my $message =
    $gCGIquery->startform(-action=>"$script_name/upper_display", 
			  -TARGET=>"list") .
    $gCGIquery->submit('Display messages') .
    $hidden_string .
    $gCGIquery->endform();

  return table({-align=>'center', -border=>0, -cellpadding=>0 -cellspacing=>0 } , 
	       Tr( [ td ([$row1, $message]), td( [$row2 ]) ] ));

  # table({-align=>'center'}, Tr( [ $row1, $row2.$message]));
  # global messages
  
  
  #return $action_string . $message;
}
#===================================================================
# not experts page for Browser_object::StartingDisplay

sub start_expert_default{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my $button_ref = Button_object->new('ExpertPageRequest', "Expert's page");


# pmj 28/6/00
#  my $string = h3("Access expert's page").
  my $string = 
    $gCGIquery->startform(-action=>"$script_name/lower_display", 
			  -TARGET=>"display").
			    $button_ref->SubmitString.
			      $hidden_string.
				$gCGIquery->endform;
  return $string;
    
}
#============================================================
# see Browser_object::DisplayDataset

sub display_expert_page_buttons{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my ($button_string, $button_ref);

  print $gCGIquery->startform(-action=>"$script_name/lower_display", 
			  -TARGET=>"display");     
  $button_string = "";
  
  $button_ref = Button_object->new('DoQaDataset', 'Do QA on whole dataset');
  $button_string .= $button_ref->SubmitString;
  
  $button_ref = Button_object->new('RedoQaDataset', 'Redo QA on whole dataset');
  $button_string .= $button_ref->SubmitString;
  
  $button_string .= $hidden_string.$gCGIquery->endform;
  
  print $button_string;

}
#============================================================
# see Browser_object::DisplayDataset

sub display_comment_buttons{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  my ($button_string, $button_ref);

  print $gCGIquery->startform(-action=>"$script_name/lower_display", 
			  -TARGET=>"display"); 
  
  $button_ref = Button_object->new('AddComment', 'Add global comment');
  $button_string = $button_ref->SubmitString;
 
  $button_string .= $hidden_string.$gCGIquery->endform;
  
  print $button_string;
  
}
#=============================================================
# see Browser_object::DisplayDataset

sub display_comment_string{
  my $key = shift;
  my ($button_ref, $button_string);

  $button_ref = Button_object->new('EditComment', 'Edit comment', $key);
  $button_string = $button_ref->SubmitString;
  $button_ref = Button_object->new('DeleteComment', 'Delete comment', $key);
  $button_string .= "<br>".$button_ref->SubmitString;

  return $button_string;
}
#=============================================================

sub SwitchDataTypeMenu{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;
 
  my $ref;

  $ref = $gDataClass_object->DataClassArray();
  my @dir_values = @$ref;

  $ref = $gDataClass_object->DataClassLabels();
  my %dir_labels = %$ref;

  # set the default
  my $cur_data_class = $gDataClass_object->DataClass();

   
  #BEN(13jun2000) added javascript to reload on change of data class
  my $popup_string = $gCGIquery->popup_menu(-name   => 'data_class',
					    -values => \@dir_values,
					    -default=> $cur_data_class,
					    -labels => \%dir_labels,  
					    -onChange => 'this.form.submit()'
					    );

#pmj 6/4/00: change labels from "Select Class" to "Change Class"

#  my $submit_string = $gCGIquery->submit('Select Class');
#  my @table_rows =  td ( [h3('Select Class of Data:')] );

  my $submit_string = $gCGIquery->submit('Change Class');
  my @table_rows =  td ( [h3('Change Class of Data:')] );
#---

  push @table_rows, td ( [$popup_string ] );
  push @table_rows, td ( [$submit_string] );
  
  my $table_string = table({-align=>'center'}, 
			   Tr({-valign=>'top'},\@table_rows));

  my $toggle_string =
    $gCGIquery->startform(-action=>"$script_name/upper_display",
			  -TARGET=>"list").
      $table_string.
	$hidden_string.
	  $gCGIquery->endform;
  
  return $toggle_string;
} 
#=============================================================

sub SwitchDataTypeMenuLite{

  my $script_name = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;
 
  my $ref;

  $ref = $gDataClass_object->DataClassArray();
  my @dir_values = @$ref;

  $ref = $gDataClass_object->DataClassLabels();
  my %dir_labels = %$ref;

  # set the default
  my $cur_data_class = $gDataClass_object->DataClass();

  #BEN(13jun2000) added javascript to reload on change of data class
  my $popup_string = $gCGIquery->popup_menu(-name   => 'data_class',
					    -values => \@dir_values,
					    -default=> $cur_data_class,
					    -labels => \%dir_labels,  
					    -onChange => 'this.form.submit()'
					    );

#pmj 6/4/00: change labels from "Select Class" to "Change Class"

#  my $submit_string = $gCGIquery->submit('Select Class');
#  my @table_rows =  td ( [h3('Select Class of Data:')] );

#  my $submit_string = $gCGIquery->submit('Change Class');
#  my @table_rows =  td ( [h3('Change Class of Data:')] );
#---

#  push @table_rows, td ( [$popup_string ] );
#  push @table_rows, td ( [$submit_string] );
  
#  my $table_string = table({-align=>'center'}, 
#			   Tr({-valign=>'top'},\@table_rows));

  my $toggle_string =
    $gCGIquery->startform(-action=>"$script_name/upper_display",
			  -TARGET=>"list").
      $popup_string.
	$hidden_string.
	  $gCGIquery->endform;
  
  return $toggle_string;
} 
