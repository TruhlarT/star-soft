#! /usr/bin/perl
#
# derived KeyList class for online
#
#========================================================
package KeyList_object_online;
#========================================================
use CGI qw/:standard :html3/;

use QA_globals;
use QA_utilities;
use Db_KeyList_utilities;
use Browser_object;

use base qw(KeyList_object);

use strict;
#--------------------------------------------------------
1;
#========================================================
sub new{
  my $classname = shift;
  my $self      = $classname->SUPER::new(@_);

  #$classname eq __PACKAGE__ and 
  #  die __PACKAGE__, " is virtual";

  return $self;
}


#========================================================
# popup menu for selecting jobs
#

sub JobPopupMenu{
  my $self = shift;

  no strict 'refs';

  # QA status is a scroll menu.
  # run ID is a text field.
  # year, month, day are text fields

  my %select_labels = (
		       QAstatus => 'QA status',
		       runID    => 'run ID',
		       detector => 'Detector',
		       year     => 'year',
		       month    => 'month',
		       day      => 'day'
		      );
  
  # possibles values for QA status
  my %values;
  $values{QAstatus} = [ 'any', 'done', 'not done', 'ok', 'not ok' ];
  $values{detector} = [ 'tpc', 'svt', 'rich' ];
  
  my %default = (QAstatus => 'any',
		  detector => 'tpc');
  
  # scroll menu for QA status and detector

  my ($QAstatus_menu, $detector_menu) =
    map {
      $gCGIquery->scrolling_list(-name    => $_,
				 -values  => $values{$_},
				 -default => $default{$_});
    } ('QAstatus','detector'); 

  # radio button group (either select on runID or the date)
  # exclusive or...
  my $radio_values_ref = [
			  'runID',
			  'date'
			 ];

  my ($radio_runID, $radio_date) =
    $gCGIquery->radio_group( -name    => 'radio',
			     -values  => $radio_values_ref,
			     -default => 'date'
			   );
  
  # text fields for runID; year, month, day
  
  # current date used for defaults
  my ($default_day, $default_month, $default_year) = (localtime)[3,4,5];
  $default_month++; $default_year += 1900;

  %default = ( runID => undef,
	       year  => $default_year,
	       month => $default_month,
	       day   => $default_day
	     );
  my %size = ( runID => 8,
	       year  => 4,
	       month => 2,
	       day   => 2 
	       );

  my %max = ( runID => 20,
	      year  => 4,
	      month => 2,
	      day   => 2
	      );
  

  my ($runID_text, $year_text, $month_text, $day_text)= 
    map {
      $select_labels{$_}.br.
      $gCGIquery->textfield(-name      => $_,
			    -default   => $default{$_},
			    -override  => 1,
			    -size      => $size{$_},
			    -maxlength => $max{$_} )
        } ('runID','year','month','day');

  # make the table
  my $instructions = h4("Select EITHER the run ID button or ",
			"the date button to access text fields");
  my $submit = $gCGIquery->submit('Display datasets');


  my $rows_ref = 
    [ td([ $select_labels{detector},$select_labels{QAstatus} , "", 
	   $radio_runID, "..or..",$radio_date, "",""                  ]),
      td([ $detector_menu, $QAstatus_menu,            "", 
	   $runID_text,  "",$year_text,$month_text, $day_text, $submit])
    ];
		      
  my $table_string = table({-align=>'center'}, 
			   Tr({-valign=>'top'}, $rows_ref));

  
  my $script_name   = $gCGIquery->script_name;
  my $hidden_string = $gBrowser_object->Hidden->Parameters;

  return 
      $gCGIquery->startform(-action=>"$script_name/upper_display",
			-TARGET=>"list").
	$instructions. 
	$table_string.
	  $hidden_string.
	    $gCGIquery->endform;

}
#========================================================
# get the selected parameters chose by the user
# returns an array of cgi values according to the popup menu

sub SelectedParameters{
  my $self = shift;

  return (
	  $gCGIquery->param('QAstatus'),
	  $gCGIquery->param('radio'),
	  $gCGIquery->param('runID'),
	  $gCGIquery->param('year'),
	  $gCGIquery->param('month'),
	  $gCGIquery->param('day'),
	  $gCGIquery->param('detector')
	 );
}


1;
