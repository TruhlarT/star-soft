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
use Tie::IxHash;

use QA_globals;
use QA_object;
use Server_object;
use Button_object;
use HiddenObject_object;
use IO_object;
use IO_utilities;
use Db_CompareReport_utilities;
use QA_db_utilities qw(:db_globals);

use DataClass_object;

use strict qw(vars subs);
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
#==================================================================
# CGI form to set/remove default references

sub SetDefaultReferences{

  # get all the current references

  my $dataClass = $gDataClass_object->DataClass();
  my $sub       = "Db_CompareReport_utilities::GetReferences_$dataClass";
  
  my %refHash; tie %refHash, "Tie::IxHash";
  %refHash = &$sub;

  my @tableRows = th(['data type', 'report key']);
  # e.g. $datatype = "P00hg auau130_Halffield
  foreach my $datatype ( keys %refHash ){ 
    
    if (! scalar @{$refHash{$datatype}} ) { # no reference set 
      @tableRows = AddRefRow(undef,$datatype,@tableRows);
      next;
    }
    
    foreach my $reference ( @{$refHash{$datatype}} ) { 
      # there can be more than one default reference per datatype
      @tableRows = AddRefRow($reference, $datatype,@tableRows);
 
    }
  }	      
  
  print table({-align=>'center'}, Tr([@tableRows]) . "\n");

}
#========================================================
sub ShowDefaultReferences{
 
  print h3("Default references:\n");
  # get all the current references

  my $dataClass = $gDataClass_object->DataClass();
  my $sub       = "Db_CompareReport_utilities::GetReferences_$dataClass";
  
  my %refHash; tie %refHash, "Tie::IxHash";
  %refHash = &$sub;

  my (@tableRows,$count, @header, @label);

  if ($dataClass =~ /nightly/){
    @header = "report key";
  }
  elsif ($dataClass =~ /offline/){
    @header = ("runID", "file seq");
  }
  
  @tableRows = th( [ 'data type', @header ] );		      

  # e.g. $datatype = "P00hg auau130_Halffield
  foreach my $datatype ( keys %refHash ){    
    foreach my $reference ( @{$refHash{$datatype}} ) { 
      $count++;
      if ($dataClass =~ /offline/){
	# get the jobID associated with the report key
	my $jobID = QA_db_utilities::GetFromQASum($QASum{jobID},$reference);

	# get the run ID and file seq matching this jobID
	@label =
	  QA_db_utilities::GetFromFileCatalog(['runID','fileSeq'],$jobID);
      }
      elsif ($dataClass =~ /nightly/){
	@label = ($reference);
      }

      @label = map {font({-color=>'blue'},$_) } @label;
      push @tableRows, td( [ $datatype, @label ] );

    }
  }	      
  
  if ($count){
    print table({-align=>'center'}, Tr([@tableRows]) . "\n");
  }
  else{
    print h3("None");
  }
} 
#========================================================
sub AddRefRow{
  my $default   = shift || 'NULL'; # usually the report key
  my $datatype  = shift;
  my @tableRows = @_;

  my $textname   = 'reference_key';
  my $scriptName = $gCGIquery->script_name;
  my $hidden     = $gBrowser_object->Hidden->Parameters;
  my $startform  = $gCGIquery->startform(-action=>"$scriptName/lower_display", 
					 -TARGET=>"display");
  my $endform    = $gCGIquery->endform();
  
  my $field = $gCGIquery->textfield(-name=>$textname,
				    -default=>$default,
				    -override=>1,
				    -size=>20,
				    -maxlength=>100);
  
  # e.g. the button name is "AddReference$dataType"
  my $addButton = Button_object->new("AddReference","Add Ref","",$datatype);
  my $addSubmit = $addButton->SubmitString();
  my $delButton = Button_object->new("DeleteReference",
				     "Delete Ref","",$datatype);
  my $delSubmit = $delButton->SubmitString();
  my $changeButton = Button_object->new("ChangeReference",
					"Change Ref","",$datatype);
  my $changeSubmit = $changeButton->SubmitString();

  # pass on the default report key as a hidden parameter
  if ($default ne 'NULL') {
    $gCGIquery->hidden('old_key',$default);
  }
  
  my $row = $startform .
    td( [ $datatype, $field, $changeSubmit, $addSubmit, $delSubmit ] ) .
    $hidden .  $gCGIquery->hidden('old_key') . $endform ;

  push @tableRows, $row;

  return @tableRows;

}
#===================================================================
# to modify the default references via the web

sub ProcessReference{
  my $command    = shift; # Add, Delete, Change
  my $report_key = shift;
  my $dataType   = shift;
  my $oldKey     = shift;

  # check that this report key is in fact associated with the datatype

  my $dataClass = $gDataClass_object->DataClass();
  my $sub       = "Db_CompareReport_utilities::ReferenceOk_$dataClass";
  my $isOk      = &$sub($report_key, $dataType);

  my $refsub;

  if ($isOk) { 
    if ($command eq 'Change'){
      Db_CompareReport_utilities::DeleteReference($oldKey) 
	if defined $oldKey;
      $refsub = "Db_CompareReport_utilities::AddReference";
    }
    else{
      $refsub = "Db_CompareReport_utilities::${command}Reference";
    }
    # execute the command
    my $rows = &$refsub($report_key);
    if (!$rows){
      print h2("<font color=red>Uh oh, couldn't $command $report_key.</font>");
    }
    else{
      print h2("${command} $report_key done.");
    }
  }
  else{
    print h2("Apparently the report key $report_key ", 
	     "does not correspond to $dataType.<br>",
	     "Maybe qa hasn't been done.  Try again\n");
    return;
  } 
}
#===================================================================
sub ShowUserReferences{
  
  my @reference_list = $gCGIquery->param('user_reference_list');

  print h3("Current user selected references : \n");

  unless( scalar @reference_list ){
    print h2("None");
    return;
  }

  # make the objects in case they dont exist
  QA_utilities::make_QA_objects(@reference_list);

  my $count=0;
  my @rows = 
    map { td([ ++$count, $QA_object_hash{$_}->DataDisplayString()]) } 
       @reference_list;
  
  print table({-border=>'1',-align=>'center'},
	      Tr({-align=>'left'},[ @rows ]));

}
