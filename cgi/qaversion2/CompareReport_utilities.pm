#! /usr/bin/perl

# pmj 4/6/00

#========================================================
package CompareReport_utilities;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Storable;
use Data::Dumper;
use File::Find;

use QA_globals;
use QA_object;
use Server_object;
use Button_object;
use HiddenObject_object;
use IO_object;
use IO_utilities;

use DataClass_object;

use strict;
#--------------------------------------------------------
1;
#========================================================
#
# These routines define the comomon data for CompareReport_object for each defined data class
# they return a time-ordered set of keys
#
#========================================================
sub offline_real{

  my $report_key = shift;
  #---------------------------------------------------------

  print "CompareReport_utilities::offline_real not implemented<br>\n";

}
#========================================================
sub offline_MC{

  my $report_key = shift;
  #---------------------------------------------------------

  print "CompareReport_utilities::offline_MC not implemented<br>\n";
}
#========================================================
sub nightly_real{

  my $report_key = shift;
  #---------------------------------------------------------

  print "CompareReport_utilities::nightly_real not implemented<br>\n";
}
#========================================================
sub nightly_MC{

  my $report_key = shift;
  #---------------------------------------------------------
  print "In CompareReport_utilities::nightly_MC, report_key = $report_key<br>\n";
  #---------------------------------------------------------
  # extract essence of report key

  my $match_pattern = reduced_key($report_key);

  my @matched_keys_unordered = ();

  foreach my $test_key (keys %QA_object_hash){
    $test_key eq $report_key and next;
    my $test_pattern = reduced_key($test_key);
    $test_pattern and $test_pattern eq $match_pattern and push @matched_keys_unordered, $test_key;
  }

  # time-order the matched objects
  my @matched_keys_ordered = sort { $QA_object_hash{$b}->CreationEpochSec <=> 
				 $QA_object_hash{$a}->CreationEpochSec } @matched_keys_unordered;

  return  @matched_keys_ordered;

}
#========================================================
sub debug{

  my $report_key = shift;
  #---------------------------------------------------------

  print "CompareReport_utilities::debug not implemented<br>\n";

}
#========================================================
#========================================================
# utility routines used by above subs and others in class
#========================================================
#========================================================
sub reduced_key{

  my $value = shift;

  $value =~ s/_Solaris|_Linux//;

# take care of Solaris_CC5   pmj 23/2/00
  $value =~ s/_CC5//;

# take care of redhat
  $value =~ s/_redhat61//;

  $value =~ s/(Sun|Mon|Tue|Wed|Thu|Fri|Sat)\.//;
  $value =~ s/\.[0-9]+$//;


 TYPE:{
    
    $value =~ /hc/ and do{
      last TYPE;
    };
    
    $value =~ /cosmics/ and do{
      $value = "cosmics";
      last TYPE;
    };
    
    $value .= "\.venus";
    
  }

  return $value;

}
#========================================================
sub GetComparisonKeys{

  # extracts the comparison keys from the CGI params, returns a time-ordered list
  
  my @matched_keys_unordered = ();

  my @params = $gCGIquery->param;

  foreach my $param ( @params){

    $param =~ /compare_report/ or next;

    (my $compare_key = $param) =~ s/\.compare_report//;

    push @matched_keys_unordered, $compare_key;
  }

  # time-order the matched objects
  my @matched_keys_ordered = sort { $QA_object_hash{$b}->CreationEpochSec <=> 
				 $QA_object_hash{$a}->CreationEpochSec } @matched_keys_unordered;
  return @matched_keys_ordered;
}
#========================================================
sub BuildFileTable{

  my $report_key = shift;
  my @matched_keys_ordered = @_;

  #-------------------------------------------------------

  # display matching runs

  my @table_heading = ('Label', 'Dataset', 'Created/On disk?' );
  my @table_rows =  th(\@table_heading);
  my $label;
  
  #--- current run

  $label = "this run";
  my $dataset_string = $QA_object_hash{$report_key}->DataDisplayString();
  my $creation_string = $QA_object_hash{$report_key}->CreationString();
  
  push @table_rows, td( [$label, $dataset_string, $creation_string ]); 

  my $ascii_string = "$label: $dataset_string, $creation_string\n";

  #--- comparison runs
    
  $label = "A";

  my %match_key_label = ();

  foreach my $match_key (@matched_keys_ordered){

    $match_key_label{$match_key} = $label;

    my $dataset_string = $QA_object_hash{$match_key}->DataDisplayString();
    my $creation_string = $QA_object_hash{$match_key}->CreationString();

    push @table_rows, td( [$label, $dataset_string, $creation_string ]); 

    $ascii_string .= "$label: $dataset_string, $creation_string\n";

    $label++;

  }
  #----------------------------------------------------------------
  # get rid of html junk from ascii string

  $ascii_string =~ s/<.*?>//g;
  #----------------------------------------------------------------
  return (\@table_rows, \%match_key_label, $ascii_string) ;
}
