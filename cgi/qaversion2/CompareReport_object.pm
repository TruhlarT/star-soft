#! /usr/bin/perl

# pmj 4/6/00

#========================================================
package CompareReport_object;
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
use CompareReport_utilities;
use CompareScalars_object;
use Db_CompareReport_utilities;

use strict;
#--------------------------------------------------------
my $CompareScalars_object;
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
  my $report_key = shift;

  #--------------------------------------------------------

  $self->ReportKey($report_key);

}
#========================================================
sub InitialDisplay{

  my $self = shift;
  #--------------------------------------------------------
  $self->PrintHeader();
  #---------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  print $gCGIquery->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
  #---------------------------------------------------------
  my $report_key = $self->ReportKey();

  my $button_ref = Button_object->new('SelectMutipleReports', 'Compare to Multiple Reports', $report_key);
  my $button_string = $button_ref->SubmitString;

  $button_ref = Button_object->new('DoCompareToReference', 'Compare to Reference', $report_key);
  $button_string .= $button_ref->SubmitString;

  my $hidden_string = $gBrowser_object->Hidden->Parameters;
  $button_string .= $hidden_string;

  print "$button_string.<br> \n";
  #-------------------------------------------------------------------
  print $gCGIquery->endform;
}
#========================================================
sub SelectMutipleReports{

  my $self = shift;
  #--------------------------------------------------------
  $self->PrintHeader();
  #---------------------------------------------------------
  my $script_name = $gCGIquery->script_name;
  print $gCGIquery->startform(-action=>"$script_name/lower_display", -TARGET=>"display"); 
  #---------------------------------------------------------
  my $report_key = $self->ReportKey();
  my $button_ref = Button_object->new('DoCompareMutipleReports', 'Do Comparison', $report_key);
  my $button_string = $button_ref->SubmitString;

  print "<strong> Select comparison runs from following list, then </strong>",
  "$button_string.<br> \n";

  print "<br>(multiple selections allowed; more than 6-8 do not display or print well) <br> \n";

  #---------------------------------------------------------
  # get time-ordered set of keys, dependent upon data class
  
  my $data_class = $gDataClass_object->DataClass();
  my $function = "Db_CompareReport_utilities::$data_class";

  no strict 'refs';
  my @matched_keys_ordered = &$function($report_key);
  use strict 'refs';

  #---------------------------------------------------------
  # display matching runs

  my @table_heading = ('Dataset (check to compare)', 'Created/On disk?' );
  my @table_rows =  th(\@table_heading);

  #--- current run

  my $pre_string = "<strong> this run: </strong>";
  my $dataset_string = $pre_string.$QA_object_hash{$report_key}->DataDisplayString();
  my $creation_string = $QA_object_hash{$report_key}->CreationString();
  
  push @table_rows, td( [$dataset_string, $creation_string ]); 

  #--- comparison runs

  foreach my $match_key (@matched_keys_ordered){

    my $box_name = $match_key.".compare_report";
    my $button_string = $gCGIquery->checkbox("$box_name", 0, 'on', '');
    my $dataset_string = $button_string.$QA_object_hash{$match_key}->DataDisplayString();
    my $creation_string = $QA_object_hash{$match_key}->CreationString();

    push @table_rows, td( [$dataset_string, $creation_string ]); 

  }

  print "<h3> Comparison runs: </h3>";
  print table( {-border=>undef}, Tr(\@table_rows) );

  #-------------------------------------------------------------------
  my $hidden_string = $gBrowser_object->Hidden->Parameters;
  print "$hidden_string";
  #-------------------------------------------------------------------
  print $gCGIquery->endform;

}
#========================================================
sub CompareMutipleReports{

  my $self = shift;
  #--------------------------------------------------------
  my $report_key = $self->ReportKey();
  #---------------------------------------------------------
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  print "<h2> Comparison of similar runs to $production_dirname ($report_key) </h2> \n"; 
  #---------------------------------------------------------
  my @matched_keys_ordered = &CompareReport_utilities::GetComparisonKeys;
  #---------------------------------------------------------
  my ($ref_file_table_rows, $ref_match_label_hash, $ascii_string_file_table) = 
    CompareReport_utilities::BuildFileTable($report_key, @matched_keys_ordered);
  #---------------------------------------------------------
  # print file table

  my @file_table_rows = @$ref_file_table_rows;
  print "<hr> \n";

  print "<h3> Comparison datasets </h3> \n";
  print table( {-border=>undef}, Tr(\@file_table_rows) );
  #---------------------------------------------------------
  # generate comparison object
  $CompareScalars_object = 
    new CompareScalars_object($report_key, \@matched_keys_ordered, $ref_match_label_hash);
  #---------------------------------------------------------
  $self->PrintTables();
  #---------------------------------------------------------
  $self->MakeAsciiReport($ascii_string_file_table);
}
#========================================================
sub CompareToReference{

  my $self = shift;
  #--------------------------------------------------------
  my $report_key = $self->ReportKey();

  #--------------------------------------------------------

  print "CompareReport_object::CompareToReference: not yet implemented (04/06/00) <br>\n";

}
#========================================================
sub ReportKey{
  my $self = shift;
  @_ and $self->{_Report_Key} = shift;
  return $self->{_Report_Key};
}
#===================================================================
sub PrintHeader{

  my $self = shift;
  #--------------------------------------------------------
  my $report_key = $self->ReportKey();
  #--------------------------------------------------------
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  print "<h2> Comparison of similar runs to $production_dirname ($report_key) </h2> \n"; 
  print "<hr> \n";
}
#===================================================================
sub PrintTables{

  my $self = shift;
  #--------------------------------------------------------

  my @macro_list = $CompareScalars_object->MacroList();

  foreach my $macro (@macro_list){

   my ($ref_table_rows_difference, $ref_table_rows_absolute) = $CompareScalars_object->GetTableRows($macro);

   print "<hr> \n";
   print "<h3> Macro: $macro </h3> \n";
   
   print "<h4> Differences relative to this run </h4> \n";
   print table( {-border=>undef}, Tr($ref_table_rows_difference) );
   
   print "<h4> Absolute values </h4> \n";
   print table( {-border=>undef}, Tr($ref_table_rows_absolute) );
 }
}
#===================================================================
sub MakeAsciiReport{

  my $self = shift;
  my $table_string = shift;
  #---------------------------------------------------------
  my $report_key = $self->ReportKey();
  #---------------------------------------------------------
  my $io = new IO_object("CompareFilename", $report_key);
  my $dh = $io->Open(">", "0644");
  my $filename_ascii = $io->Name();

  print "<h4> (Ascii version of this page written to $filename_ascii) </h4> \n";
  #---------------------------------------------------------
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  print $dh "*" x 80, "\n";
  print $dh "Comparison of similar runs to \n$production_dirname ($report_key) \n";
  print $dh "(up to 10 most recent runs compared) \n"; 
  print $dh "*" x 80, "\n";

  print $dh " Comparison datasets \n \n";

  print $dh "$table_string \n";

  print $dh "*" x 80, "\n";
  #---------------------------------------------------------

  my @macro_list = $CompareScalars_object->MacroList();

  foreach my $macro (@macro_list){

   my ($string_difference, $string_absolute) = $CompareScalars_object->GetAsciiStrings($macro);

    print $dh "Macro: $macro \n";

    print $dh "\nDifferences relative to this run\n$string_difference\n";
    print $dh "\nAbsolute values\n$string_absolute\n";

    print $dh "*" x 80, "\n";

  }

  #---------------------------------------------------------
  undef $io;
}
