#! /usr/bin/perl

#========================================================
package QA_report_io;
#========================================================
use CGI qw(:standard escapeHTML);
use CGI::Carp qw(fatalsToBrowser);

use Cwd;

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

# for ensuring that hash elements delivered in insertion order (See Perl Cookbook 5.6)
use Tie::IxHash;

# expands tabs when printing to ascii
use Text::Tabs;

use Data::Dumper;
use Storable qw(nstore retrieve);

use QA_cgi_utilities;
use QA_globals;

use QA_report_object;

#--------------------------------------------------------
1;
#========================================================
sub display_reports {
  
  my $report_key = shift;
 
  my $report_dirname = $QA_object_hash{$report_key}->ReportDirectory;
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  #---------------------------------------------------------
    print "<h2> QA for $production_dirname </h2> \n"; 
  #---------------------------------------------------------
  # get links to test files

  print "<hr><h3> Control and Macro Definition files: </h3> \n";
  
  $control_file = $QA_object_hash{$report_key}->ControlFile;
  $control_file_WWW = "$control_dir_WWW/".basename($control_file);
  QA_cgi_utilities::make_anchor("Control file", $control_file, $control_file_WWW);
  
  open CONTROL, $control_file or die "Cannot open control file $control_file: $! \n";
  while ($test_file = <CONTROL>){
    
    $test_file =~ /^\#/ and next;
    $test_file !~ /\S+/ and next;

    $test_file_WWW = "$control_dir_WWW/".basename($test_file);
    
    QA_cgi_utilities::make_anchor("Macro Definition file", $test_file, $test_file_WWW);
  }
  close CONTROL;

  #---------------------------------------------------------
  # display ps files

  print "<hr><H3> QA histograms: </H3>\n"; 

  my $report_dir = $QA_object_hash{$report_key}->ReportDirectory;
  
  opendir (DIR, $report_dir) or die "Cannot opendir $report_dir: $! \n";
  
  @ps_file = ();

  while (defined ($file = readdir(DIR) ) ){

    # skip . and ..
    $file =~ /^\./ and next;

    $file =~ /ps$/ and do{
      push @ps_file, $file;
      next;
    };

    $file =~ /ps\.gz$/ and do{
      push @ps_file, $file;
      next;
    };

  }

  closedir (DIR);

  foreach $file (@ps_file){
    $QA_object_hash{$report_key}->PrintFilestring("Postscript file", $file);
  }

  #---------------------------------------------------------

  # get all evaluation files in that directory

  @evalfile_list = ();

  my %eval_hash = ();

  find(\&get_evalfile, $report_dirname);

  foreach $file (@evalfile_list) {

    ($macro_name = basename($file) ) =~ s/\.evaluation//;

    my $ref = retrieve($file);
    $eval_hash{$macro_name} = $$ref;
  }

  #---------------------------------------------------------
  # display run-based scalars, errors and warnings

  print "<hr><h3> Run-based scalars, errors and warnings: </h3>\n"; 

  foreach $macro_name (keys %eval_hash){

    $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 
    
    show_scalars_and_test_failures($eval, 'run');
  }

  #---------------------------------------------------------
  # display event-based scalars, errors and warnings

  print "<hr><h3> Event-based errors and warnings: </h3>\n"; 

  foreach $macro_name (keys %eval_hash){

    $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 
    
    show_scalars_and_test_failures($eval, 'event');
  }

  #---------------------------------------------------------
  # display run-based tests

  print "<hr><h3> Run-based tests (all entries): </h3>\n"; 

  foreach $macro_name (keys %eval_hash){

    $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 

    show_all_tests($eval, 'run');

  }

  #---------------------------------------------------------
  # display event-based tests

  print "<hr><h3> Event-based tests (all entries): </h3>\n"; 

  foreach $macro_name (keys %eval_hash){

    $eval = $eval_hash{$macro_name};
    print "<h4> Macro: $macro_name </h4> \n"; 

    show_all_tests($eval, 'event');

  }
}
 
#===================================================================
sub show_scalars_and_test_failures{

  my $eval = shift;
  my $test_type = shift;

  #----------------------------------------------
  # get scalars

  tie %scalars, "Tie::IxHash"; 
  
 TYPE: {
    
    $test_type eq 'run' and do{
      %scalars = %{$eval->RunScalarsHash};
      last TYPE;
    };
    
    $test_type eq 'event' and do{
      %scalars = %{$eval->EventScalarsHash};
      last TYPE;
    };
    
    return;
  }

  #----------------------------------------------------------------------
  # print run scalars only

  if ($test_type eq 'run'){

    @table_heading = ('Scalar Name', 'Value');
    @table_rows_scalar = th(\@table_heading);
    
    $n_scalars = 0;
    foreach $key ( keys %scalars ){
      $n_scalars++;
      
      $key_string = "<small>".$key."</small>";
      $scalar_string = "<small>".$scalars{$key}."</small>";
      push @table_rows_scalar, td( [$key_string, $scalar_string] );
    }
  }
  else{
    @table_heading = ();
    $n_scalars = 0;
  }
  
  #----------------------------------------------
  my @test_name_list = $eval->TestNameList($test_type);
  #----------------------------------------------
  # Display errors and warnings

  @table_heading = ('Test name', 'String');
  @table_rows_error = th(\@table_heading);
  @table_rows_warn = th(\@table_heading);
  
  $n_error = 0;
  $n_warn = 0;
  
  foreach $test_name (@test_name_list){    

    $test_name_string = "<small>".$test_name."</small>";
    
    my @test_line_list = $eval->TestLineDisplayList($test_type, $test_name);
    
    foreach $test_line (@test_line_list){
      
      $string = "<small>".$test_line."</small>";
      $severity = $eval->TestLineDisplaySeverity($test_type, $test_name,$test_line);
      $result = $eval->TestLineDisplayResult($test_type, $test_name,$test_line);

      $result eq "FALSE" and do {
	
	$severity eq "error" and do{
	  push @table_rows_error, td( [$test_name_string, $string] );  
	  $n_error++;
	};
	
	$severity eq "warn" and do{
	  push @table_rows_warn, td( [$test_name_string, $string] );  
	  $n_warn++;
	};
	
      };
    }
  }
  
  $n_scalars or @table_rows_scalar = ();
  $n_error or @table_rows_error = ();
  $n_warn or @table_rows_warn = ();
  #----------------------------------------------
  # something to show?

  if($n_scalars+$n_error+$n_warn){

    if ($n_scalars){$scalar_header = 'Scalars';}
    else{$scalar_header = '';}
  
    @table_heading = ("$scalar_header", 'Error if string false', 'Warning if string false');
    @table_rows_display =  th(\@table_heading);

    push @table_rows_display, td( [ 
				   table( {-border=>undef, -align=>'center'},
					  Tr(\@table_rows_scalar))
				   , table( {-border=>undef, -align=>'center'},
					    Tr(\@table_rows_error))
				   , table( {-border=>undef, -align=>'center'},
					    Tr(\@table_rows_warn))
				  ] );
    
    print table( {-width=>'100%'}, Tr(\@table_rows_display));      
  } 
  else{
    print "No errors or warnings generated. <br> \n";
  }

  #--------------------------------------------------------------------

}
#======================================================================================
sub show_all_tests{

  my $eval = shift;
  my $test_type = shift;

  #----------------------------------------------
  # all test results

  my @test_name_list = $eval->TestNameList($test_type);  
  #----------------------------------------------
  @test_name_list or do{
    print "No tests defined. <br> \n";
    return;
  };
  #----------------------------------------------
  foreach $test_name (@test_name_list){    
    
    @table_heading = ('String', 'Severity', 'Result');
    
    my @table_rows = th(\@table_heading);
    
    my @test_line_list = $eval->TestLineDisplayList($test_type, $test_name);
    
    @data = ();
    foreach $test_line (@test_line_list){
      
      $string = $test_line;
      $severity = $eval->TestLineDisplaySeverity($test_type, $test_name,$test_line);
      $result = $eval->TestLineDisplayResult($test_type, $test_name,$test_line);

      $string = "<font size=1>".$string."</font>";
      $severity = "<font size=1>".$severity."</font>";
      $result = "<font size=1>".$result."</font>";
      
      push @data, "$string, $severity, $result";
    }

    if(@data){
      print "<h5> Test name: \"$test_name\" </h5> \n"; 

      my $test_comment = $eval->TestComment($test_type, $test_name);
      $test_comment and print "<h5> Test comment: \"$test_comment\" </h5> \n"; 

      $n_display_columns_data = 6;
      print_horizontal_table( \@table_heading, \@data, $n_display_columns_data);    
    }
    else{
      print "No tests defined. <br> \n";
    }

  }
  #----------------------------------------------
  
}

#==========================================================
sub get_evalfile{
  
  $filename = $File::Find::name;
    
  if ( $filename =~ /\.evaluation/ ) {
    push @evalfile_list, $filename;
  }
}
#==================================================================================
sub print_horizontal_table{

  my $table_heading_ref = shift;
  my $data_ref = shift;
  my $n_display_columns_data = shift;

  #-------------------------------------------------------------------------------

  my @table_heading = @$table_heading_ref;
  my @data = @$data_ref;

  my $n_rows = $#table_heading; 
  my $n_data = $#data; 

  #-------------------------------------------------------------------------------

  for ( $i_print = 0; $i_print <= $n_data; $i_print += $n_display_columns_data ){

    @table_rows = ();

    for ( $i_row = 0; $i_row <= $n_rows; $i_row++ ){

      my @this_row = ();

      $this_row[0] = "<strong>".$table_heading[$i_row]."</strong>";

      ROW: for ( $i_col = 0; $i_col < $n_display_columns_data; $i_col++ ){

	$i_entry = $i_print + $i_col;

	last ROW if $i_entry > $n_data;

	$datum = (split /,/,$data[$i_entry])[$i_row];

	$datum =~ /FALSE/ and $datum = "<font color=red>".$datum."</font>"; 

	$this_row[$i_col + 1] = $datum;
      }

      push @table_rows, td(\@this_row);

    }
    
    print table( {-border=>undef, -vspace=>10}, Tr(\@table_rows));

  }
	
}	 
#========================================================
sub setup_report_comparison {
  
  my $report_key = shift;
  #---------------------------------------------------------
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  print "<h2> Comparison of similar runs to $production_dirname ($report_key) </h2> \n"; 
  print "<hr> \n";
  #---------------------------------------------------------
  print $query->startform(-action=>"$script_name/display_data", -TARGET=>"display"); 
  #---------------------------------------------------------

  $button_value = $report_key.".do_report_comparison";
  print "<strong> Select comparison runs from following list, then </strong>",
  $query->submit("$button_value", 'do run comparison.'),"<br> \n";

  print "<br>(multiple selections allowed; more than 6-8 do not display or print well) <br> \n";

  #---------------------------------------------------------
  # extract essence of report key

  $match_pattern = reduced_key($report_key);

  my @matched_keys_unordered = ();

  foreach $test_key (keys %QA_object_hash){
    $test_key eq $report_key and next;
    my $test_pattern = reduced_key($test_key);
    $test_pattern and $test_pattern eq $match_pattern and push @matched_keys_unordered, $test_key;
  }

  # time-order the matched objects
  @matched_keys_ordered = sort { $QA_object_hash{$b}->CreationEpochSec <=> 
				 $QA_object_hash{$a}->CreationEpochSec } @matched_keys_unordered;

  #---------------------------------------------------------
  # display matching runs

  @table_heading = ('Dataset (check to compare)', 'Created/On disk?' );
  @table_rows =  th(\@table_heading);

  #--- current run

  $pre_string = "<strong> this run: </strong>";
  $dataset_string = $pre_string.$QA_object_hash{$report_key}->DataDisplayString();
  $creation_string = $QA_object_hash{$report_key}->CreationString();
  
  push @table_rows, td( [$dataset_string, $creation_string ]); 

  #--- comparison runs

  foreach $match_key (@matched_keys_ordered){

    $box_name = $match_key.".compare_report";
    $button_string = $query->checkbox("$box_name", 0, 'on', '');
    $dataset_string = $button_string.$QA_object_hash{$match_key}->DataDisplayString();
    $creation_string = $QA_object_hash{$match_key}->CreationString();

    push @table_rows, td( [$dataset_string, $creation_string ]); 

  }

  print "<h3> Comparison runs: </h3>";
  print table( {-border=>undef}, Tr(\@table_rows) );

  #-------------------------------------------------------------------

  my $string = &QA_utilities::hidden_field_string;
  print "$string";
  #-------------------------------------------------------------------
  print $query->endform;

}
#========================================================
sub do_report_comparison {
  
  my $report_key = shift;
  #---------------------------------------------------------
  my $production_dirname = $QA_object_hash{$report_key}->ProductionDirectory;
  print "<h2> Comparison of similar runs to $production_dirname ($report_key) </h2> \n"; 
  #---------------------------------------------------------
  # extract essence of report key, get list of comparison reports

  my @matched_keys_unordered = ();

  @params = $query->param;

  foreach $param ( @params){

    $param =~ /compare_report/ or next;

    ($compare_key = $param) =~ s/\.compare_report//;

    push @matched_keys_unordered, $compare_key;
  }

  # time-order the matched objects
  @matched_keys_ordered = sort { $QA_object_hash{$b}->CreationEpochSec <=> 
				 $QA_object_hash{$a}->CreationEpochSec } @matched_keys_unordered;

  #---------------------------------------------------------
  # display matching runs

  @table_heading = ('Label', 'Dataset', 'Created/On disk?' );
  @table_rows =  th(\@table_heading);

  #--- current run

  $label = "this run";
  $dataset_string = $QA_object_hash{$report_key}->DataDisplayString();
  $creation_string = $QA_object_hash{$report_key}->CreationString();
  
  push @table_rows, td( [$label, $dataset_string, $creation_string ]); 

  #--- comparison runs
    
  $label = "A";

  %match_key_label = ();

  foreach $match_key (@matched_keys_ordered){

    $match_key_label{$match_key} = $label;

    $dataset_string = $QA_object_hash{$match_key}->DataDisplayString();
    $creation_string = $QA_object_hash{$match_key}->CreationString();

    push @table_rows, td( [$label, $dataset_string, $creation_string ]); 

    $label++;

  }

  print "<hr> \n";

  print "<h3> Comparison datasets </h3> \n";
  print table( {-border=>undef}, Tr(\@table_rows) );

  #---------------------------------------------------------
  # make ascii report - cheap version 

  $filename_ascii = "/star/data1/jacobs/qa/compare_runs/$report_key";

  print "<h4> (Ascii version of this page written to $filename_ascii) </h4> \n";

  open ASCIIFILE, ">$filename_ascii" or die "Cannot open file $filename_ascii: $! \n"; 

  print ASCIIFILE "Comparison of similar runs to $production_dirname ($report_key) \n";
  print ASCIIFILE "(up to 10 most recent runs compared) \n"; 
  print ASCIIFILE "*" x 80, "\n";

  print ASCIIFILE " Comparison datasets \n \n";

  $label = "this run";
  $dataset_string = $QA_object_hash{$report_key}->DataDisplayString();
  $creation_string = $QA_object_hash{$report_key}->CreationString();
  print ASCIIFILE "label = $label \n";
  print ASCIIFILE "dataset = $dataset_string \n";
  print ASCIIFILE "creation_string = $creation_string \n";

  foreach $match_key (@matched_keys_ordered){
    $label = $match_key_label{$match_key};
    $dataset_string = $QA_object_hash{$match_key}->DataDisplayString();
    $creation_string = $QA_object_hash{$match_key}->CreationString();
    print ASCIIFILE "\n label = $label \n";
    print ASCIIFILE "dataset = $dataset_string \n";
    print ASCIIFILE "creation_string = $creation_string \n";
  }

  print ASCIIFILE "*" x 80, "\n";
  #---------------------------------------------------------
  # get all evaluation files in that directory

  @evalfile_list = ();

  my %count_defined = ();

  my $report_dirname = $QA_object_hash{$report_key}->ReportDirectory;
  find(\&get_evalfile, $report_dirname);

  foreach $file (@evalfile_list) {

    ($macro_name = basename($file) ) =~ s/\.evaluation//;

    tie %this_hash, "Tie::IxHash"; 

    &get_run_scalar_hash($report_key,$macro_name); 
    %this_hash = %run_scalars;

    foreach $match_key ( @matched_keys_ordered ){

      &get_run_scalar_hash($match_key,$macro_name);
      %match_hash = %run_scalars;

      foreach $scalar ( keys %this_hash ){

	$value = $match_hash{$scalar};

	if( defined ( $value ) ){
	  $match_report->{$match_key}->{$scalar} = $value;
	  $count_defined{$match_key}++;
	}
	else {
	  $match_report->{$match_key}->{$scalar} = "undef";
	}
      }

    }

    #---
    # include in table only those keys that have at least one defined scalar

    @table_keys = ();
    @table_label = ();
    foreach $key (@matched_keys_ordered){
      $count_defined{$key} and do{
	push @table_keys, $key;
	push @table_label, $match_key_label{$key};
      };
    }

    #---
    @table_heading = ('Scalar', 'This run', @table_label );

    @table_rows_absolute =  th(\@table_heading);
    @table_rows_difference =  th(\@table_heading);


    #---
    $table_heading_ascii = join ':',@table_heading;
    $table_heading_ascii =~ s/:/\t/g;
    $tabstop = 20;
    $table_heading_ascii = expand("$table_heading_ascii"); 

    @table_absolute_ascii = ($table_heading_ascii);
    @table_difference_ascii = ($table_heading_ascii);

    #---
    foreach $scalar ( keys %this_hash ){

      @row_data_absolute = $scalar;
      @row_data_difference = $scalar;
      
      $this_scalar_value = $this_hash{$scalar};
      push @row_data_absolute, $this_scalar_value;
      push @row_data_difference, $this_scalar_value;

      foreach $match_key ( @table_keys ){
	$compare_scalar_value = $match_report->{$match_key}->{$scalar};

	if ( $compare_scalar_value =~ /\d+/ ){
	  $difference = $this_scalar_value - $compare_scalar_value;
	  $difference = (int ( 100 * $difference) ) / 100;
	}
	else{
	  $difference = 'undef';
	}
	
	push @row_data_absolute, $compare_scalar_value; 
	push @row_data_difference, $difference;
      }
      
      push @table_rows_absolute, td( \@row_data_absolute );
      push @table_rows_difference, td( \@row_data_difference );

      #---
      # make strings with tab separators
      
      $ascii_abs = join ':',@row_data_absolute;
      $ascii_diff = join ':',@row_data_difference;
      $ascii_abs =~ s/:/\t/g; 
      $ascii_diff =~ s/:/\t/g; 
      
      $tabstop = 20;
      $ascii_abs = expand( "$ascii_abs");
      $ascii_diff = expand( "$ascii_diff");

      push @table_absolute_ascii, $ascii_abs; 
      push @table_difference_ascii, $ascii_diff; 
      #---
      
    }

    print "<hr> \n";
    print "<h3> Macro: $macro_name </h3> \n";

    print "<h4> Differences relative to this run </h4> \n";
    print table( {-border=>undef}, Tr(\@table_rows_difference) );

    print "<h4> Absolute values </h4> \n";
    print table( {-border=>undef}, Tr(\@table_rows_absolute) );

    #---
    
    print ASCIIFILE "Macro: $macro_name \n";

    print ASCIIFILE "\n Differences relative to this run \n";
    foreach $line ( @table_difference_ascii ){print ASCIIFILE "$line \n";}

    print ASCIIFILE "\n Absolute values \n";
    foreach $line ( @table_absolute_ascii ){print ASCIIFILE "$line \n";}

    print ASCIIFILE "*" x 80, "\n";
    #---

  }

  #---------------------------------------------------------
  close ASCIIFILE;
  chmod 0664, $filename_ascii;
  #---------------------------------------------------------

}
#===================================================================
sub reduced_key{

  my $report_key = shift;

  my @essence = split /\./, $report_key;
  $essence[1] =~ s/\_.*//;
#  return $essence[0]."_".$essence[1]."_".$essence[3];

  $value = 0;

  if ( $essence[0] eq "dev" ){
    $value = $essence[1]."_".$essence[3];
  }  
  elsif ( $essence[0] eq "new" ){
    $value = $essence[1]."_".$essence[2];
  }

  return $value;

}
#=====================================================================
sub get_run_scalar_hash{

  my $report_key = shift;
  my $macro_name = shift;
  
  tie %run_scalars, "Tie::IxHash"; 
  %run_scalars = ();

  #-----------------------------------------------------------------------

  my $report_dirname = $QA_object_hash{$report_key}->ReportDirectory;

  $filename = "$report_dirname/$macro_name.evaluation";

  if (-s $filename){

    $ref = retrieve($filename) or print "Cannot retrieve file $filename:$! \n";
    %run_scalars = %{$$ref->RunScalarsHash};

  }
#  return %run_scalars;  
  return;
}

  
