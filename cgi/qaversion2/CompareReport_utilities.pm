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

  my %refHash; tie %refHash, "Tie::IxHash";
  %refHash = Db_CompareReport_utilities::GetAllDefaultReferences();

  my @tableRows = th(['match criteria', 'report key']);
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

#----------
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
  my $addButton    = Button_object->new("AddReference",
					"Add Ref","",$datatype);
  my $addSubmit    = $addButton->SubmitString();
  my $delButton    = Button_object->new("DeleteReference",
					"Delete Ref","",$datatype);
  my $delSubmit    = $delButton->SubmitString();
  my $changeButton = Button_object->new("ChangeReference",
					"Change Ref","",$datatype);
  my $changeSubmit = $changeButton->SubmitString();

  # pass on the default report key as a parameter
  if ($default ne 'NULL') {
    $gCGIquery->param('old_key',$default);
  }
  
  my $row = $startform .
    td( [ $datatype, $field, $changeSubmit, $addSubmit, $delSubmit ] ) .
    $hidden .  $gCGIquery->hidden('old_key') . $endform ;

  push @tableRows, $row;

  return @tableRows;

}
#----------
# to modify the default references via the web

sub ProcessReference{
  my $command    = shift; # Add, Delete, Change
  my $report_key = shift;
  my $matchString= shift;
  my $oldKey     = shift;

  # check that this report key is in fact associated with the datatype

  my $isOk = Db_CompareReport_utilities::ReferenceOk($report_key, $matchString);

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
    elsif($command eq 'Change'){
      print h2("${command} from $oldKey to $report_key done");
    }
    else{
      print h2("${command} $report_key done.");
    }
  }
  else{
    print h2("Apparently the report key $report_key <br>", 
	     "does not correspond to <br>",
	     "$matchString.<br>",
	     "Maybe qa hasn't been done.  Try again.\n");
    return;
  } 
}
#----------
sub ShowDefaultReferences{
 
  print h4("Default references matching this query:\n");
  # get all the current references

  my %refHash; tie %refHash, "Tie::IxHash";
  %refHash = Db_CompareReport_utilities::GetDefaultReferencesByQuery();

  my (@tableRows,$count, @header, @label);

  my $dataClass = $gDataClass_object->DataClass();

  if ($dataClass =~ /nightly/){
    @header = "report key";
  }
  elsif ($dataClass =~ /offline/){
    @header = ("runID", "file seq");
  }
  
  @tableRows = th( [ 'matching criteria', @header ] );		      

  # e.g. $matchValues = "P00hg auau130_Halffield
  foreach my $matchValues ( keys %refHash ){    
    foreach my $reference ( @{$refHash{$matchValues}} ) { 
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
      push @tableRows, td( [ $matchValues, @label ] );

    }
  }	      
  
  if ($count){
    print table({-align=>'center',-border=>0}, 
		Tr([@tableRows]) . "\n");
  }
  else{
    print h4("None");
  }
} 
#----------
# user references list upon select datasets.

sub ShowUserReferences{
  
  my @reference_list = $gCGIquery->param('user_reference_list');

  print h4("User selected references : \n");

  unless( scalar @reference_list ){
    print h4("None");
    return;
  }
  # this sets the Db_CompareReport_utilities globals.
  # probably need to move this into DataClass_object
  Db_CompareReport_utilities::Controller();

  my @tableRows;
  my $dataClass = $gDataClass_object->DataClass();

  foreach my $report_key (@reference_list){
    my $jobID = QA_db_utilities::GetFromQASum('jobID',$report_key);
  
    # get the match values
    my @matchValues = Db_CompareReport_utilities::GetMatchValues($jobID);

    my @label;
    if ($dataClass =~ /offline/){
      
      # get the run ID and file seq matching this jobID
      @label =
	QA_db_utilities::GetFromFileCatalog(['runID','fileSeq'],$jobID);
    }
    elsif ($dataClass =~ /nightly/){
      @label = ($report_key);
    }
  
    @label = map {font({-color=>'blue'},$_) } @label;
    push @tableRows, td( [ "@matchValues", @label ] );
  }
  print table({-border=>0,-align=>'center'},
	      Tr([ @tableRows ]));

}
#----------

sub SetUserReference{
  my $report_key = shift;
  my @reference_list = @_;

  # make the objects in case they dont exist
  QA_utilities::make_QA_objects(@reference_list);

  my ($seen, $string);
  foreach my $key ( @reference_list ) {
    if ($key eq $report_key){
      $seen++; last;
    }
  }
  if ($seen){
    $string .= h3("Apparently this dataset has already been chosen ",
		 "as a reference");
  }
  else{
    my $label;
    $gCGIquery->append(-name=>'user_reference_list',
		       -values=>$report_key);

    if ($gDataClass_object->DataClass =~ /offline/){
      my $runID   = $QA_object_hash{$report_key}->LogReport->RunID;
      my $fileSeq = $QA_object_hash{$report_key}->LogReport->FileSeq;

      $label = "runID :$runID - file seq: $fileSeq";
    }
    else{
      $label = $QA_object_hash{$report_key}->ProductionDirectory;
      $label .= " ($report_key) ";
				   
    }
    $string .= h3("Press this button to add <br>",
		  "$label <br>",
		  "to the user selected reference list\n");
    
    my $scriptName = $gCGIquery->script_name;

    $string .= $gCGIquery->startform(-action=>"$scriptName/upper_display", 
				     -TARGET=>"list").
               $gCGIquery->submit('Set as Reference'). 
               $gBrowser_object->Hidden->Parameters .
	       $gCGIquery->endform() ."\n";

  }
  print $string;

  if ( scalar @reference_list ){
    CompareReport_utilities::ShowUserReferences();
  }
}
