#! /opt/star/bin/perl

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

use strict;

#--------------------------------------------------------
1;

 
#===================================================================
sub show_scalars_and_test_failures{

  my $eval = shift;
  my $mult_label = shift;
  my $test_type = shift;

  #----------------------------------------------
  # get scalars

  my %scalars;
  tie %scalars, "Tie::IxHash"; 
  
 TYPE: {
    
    $test_type eq 'run' and do{
      %scalars = %{$eval->RunScalarsHash($mult_label)};
      last TYPE;
    };
    
    $test_type eq 'event' and do{
      %scalars = %{$eval->EventScalarsHash($mult_label)};
      last TYPE;
    };
    
    return;
  }

  #----------------------------------------------------------------------
  # print run scalars only

  my (@table_heading, @table_rows_scalar, $n_scalars);

  if ($test_type eq 'run'){

    @table_heading = ('Scalar Name', 'Value');
    @table_rows_scalar = th(\@table_heading);
    
    $n_scalars = 0;
    foreach my $key ( keys %scalars ){
      $n_scalars++;
      
      my $key_string = "<small>".$key."</small>";
      my $scalar_string = "<small>".$scalars{$key}."</small>";
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

  my (@table_rows_error, @table_rows_warn);

  @table_heading = ('Test name', 'String');
  @table_rows_error = th(\@table_heading);
  @table_rows_warn = th(\@table_heading);
  
  my $n_error = 0;
  my $n_warn = 0;
  
  foreach my $test_name (@test_name_list){    

    my $test_name_string = "<small>".$test_name."</small>";
    
    my @test_line_list = $eval->TestLineDisplayList($test_type, $test_name);
    
    foreach my $test_line (@test_line_list){
      
      my $string = "<small>".$test_line."</small>";
      my $severity = $eval->TestLineDisplaySeverity($test_type, $test_name,$test_line);
      my $result = $eval->TestLineDisplayResult($test_type, $test_name,$test_line);

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

    my $scalar_header;

    if ($n_scalars){$scalar_header = 'Scalars';}
    else{$scalar_header = '';}
  
    @table_heading = ("$scalar_header", 'Error if string false', 'Warning if string false');
    my @table_rows_display =  th(\@table_heading);

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
  my $mult_label = shift;
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
  foreach my $test_name (@test_name_list){    
    
    my @table_heading = ('String', 'Severity', 'Result');
    
    my @table_rows = th(\@table_heading);
    
    my @test_line_list = $eval->TestLineDisplayList($test_type, $test_name);
    
    my @data = ();
    foreach my $test_line (@test_line_list){
      
      my $string = $test_line;
      my $severity = $eval->TestLineDisplaySeverity($test_type, $test_name,$test_line);
      my $result = $eval->TestLineDisplayResult($test_type, $test_name,$test_line);

      $string = "<font size=1>".$string."</font>";
      $severity = "<font size=1>".$severity."</font>";
      $result = "<font size=1>".$result."</font>";
      
      push @data, "$string, $severity, $result";
    }

    if(@data){
      print "<h5> Test name: \"$test_name\" </h5> \n"; 

      my $test_comment = $eval->TestComment($test_type, $test_name);
      $test_comment and print "<h5> Test comment: \"$test_comment\" </h5> \n"; 

      my $n_display_columns_data = 6;
      print_horizontal_table( \@table_heading, \@data, $n_display_columns_data);    
    }
    else{
      print "No tests defined. <br> \n";
    }

  }
  #----------------------------------------------
  
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

  for ( my $i_print = 0; $i_print <= $n_data; $i_print += $n_display_columns_data ){

    my @table_rows = ();

    for ( my $i_row = 0; $i_row <= $n_rows; $i_row++ ){

      my @this_row = ();

      $this_row[0] = "<strong>".$table_heading[$i_row]."</strong>";

      ROW: for ( my $i_col = 0; $i_col < $n_display_columns_data; $i_col++ ){

	my $i_entry = $i_print + $i_col;

	last ROW if $i_entry > $n_data;

	my $datum = (split /,/,$data[$i_entry])[$i_row];

	$datum =~ /FALSE/ and $datum = "<font color=red>".$datum."</font>"; 

	$this_row[$i_col + 1] = $datum;
      }

      push @table_rows, td(\@this_row);

    }
    
    print table( {-border=>undef, -vspace=>10}, Tr(\@table_rows));

  }
	
}	 
  
