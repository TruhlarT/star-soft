#! /usr/bin/perl -w

#=========================================================
package QA_report_object;
#=========================================================

use File::stat;
use File::Copy;
use File::Find;
use File::Basename;

# for ensuring that hash elements delivered in insertion order (See Perl Cookbook 5.6)
use Tie::IxHash;
use Data::Dumper;

# persistent I/O (PERL Cookbook recipe 11.13)
use Storable qw(nstore retrieve);

use QA_globals;
use QA_cgi_utilities;
use QA_object;
use QA_run_root;
#use QA_test_object;

use QA_macro_scalars;

#=========================================================
1.;
#=========================================================
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

  my $self = shift;
  #-------------------------------------------------
  
  # if no macro name supplied as argument, return
  return unless @_;

  my $report_key = shift;
  my $test_definition_file = shift;
  #-------------------------------------------------

  $self->ReportKey($report_key);
  $self->TestDefinitionFile($test_definition_file);

}
#=======================================================
sub EvaluateMacro{
  my $self = shift;

  #----------------------------------------------------------
  # any tests defined?
  $self->NTests or return;
  #----------------------------------------------------------
  $self->Evaluate;
  $self->Write;

}
#=========================================================
sub GetTests{

  my $self = shift;

  #-----------------------------------------------------------1
  my $report_key = $self->ReportKey;
  #-----------------------------------------------------------
  $test_definition_file = $self->TestDefinitionFile;
  #-----------------------------------------------------------
  open TESTFILE, $test_definition_file or die "Cannot open test definition file $test_definition_file: $! \n";
  my @test_definition_array = <TESTFILE>;
  close TESTFILE;

  #--------------------------------------------------------------------------
  %{$self->{test}} = ();
  #--------------------------------------------------------------------------
  # parse file contents

  my $test_active = 0;
  my $line;

  my $n_tests = 0;

  foreach $line (@test_definition_array){

    # comment lines
    $line =~ /^\#/ and next;

    $line =~ /macro name:(.*)/ and do{
      $file = $1;
      $macro_name = basename($file);
      $macro_name =~ s/\.C//;

      print "Found macro_name $macro_name, file = $file <br> \n";

      $self->MacroName($macro_name);
      $self->MacroFile($file);
      next;
    };

    $line =~ /macro arguments:(.*)/ and do{
      $self->MacroArguments($1);
      next;
    };

    $line =~ /input data filetype:(.*)/ and do{
      (my $temp = $1) =~ s/\s+//g;
      $self->InputDataType($temp);
      next;
    };

    $line =~ /output data extension:(.*)/ and do{
      (my $temp = $1) =~ s/\s+//g;
      $self->OutputDataExtension($temp);
      next;
    };

    $line =~ /output data filename:(.*)/ and do{
      (my $temp = $1) =~ s/\s+//g;
      $self->OutputDataFilename($temp);
      next;
    };

    $line =~ /output data filetype:(.*)/ and do{
      (my $temp = $1) =~ s/\s+//g;
      $self->OutputDataType($temp);
      next;
    };

    $line =~ /first starlib version:(.*)/ and do{
      $self->FirstStarlibVersion($1);
      next;
    };

    $line =~ /last starlib version:(.*)/ and do{
      $self->LastStarlibVersion($1);
      next;
    };

    $line =~ /macro comment:(.*)/ and do{
      $self->MacroComment($1);
      next;
    };

    $line =~ /end of header:/ and do{
      $self->MacroReportFilename($report_key,$macro_name);
      next;
    };

    $line =~ /run scalars:(.*)/ and do{
      $self->RunScalars_string($1);
      next;
    };

    $line =~ /event scalars:(.*)/ and do{
      $self->EventScalars_string($1);
      next;
    };

    $line =~ /BEGIN TEST:/ and do{
      $test_active = 1;
      $n_tests++;
      next;
    };

    $line =~ /END TEST:/ and do{
      $test_active = 0;
      next;
    };

    $test_active and $line =~ /(\w+) test name:(.*)/ and do{
      # first arg is test type (= 'run','event'), second arg is test name
      $test_type = $1;
      $test_name = $2;
      $self->TestNameList($test_type, $test_name);
      next;
    };

    $test_active and $line =~ /test comment:(.*)/ and do{
      $self->TestComment($test_type, $test_name, $1);
      next;
    };

    $test_active and $line =~ /((?:error|warn):.*)/ and do{
      $self->TestLineList($test_type, $test_name, $1);
      next;
    };

  }

  $self->NTests($n_tests);

  #------------------------------------------------------
  # if macro is bfcread_hist_to_ps, check that .hist.root file exists

  $self->MacroName eq "bfcread_hist_to_ps" and do{

    $global_input_data_type = ".hist.root";
    
    my $replace_macro = 0;

    # is there a .hist.root file?
    $production_dir = $QA_object_hash{$report_key}->LogReport->OutputDirectory; 
    find( \&QA_cgi_utilities::get_file, $production_dir );

#    print "global_filename = $global_filename <br> \n";

    if ( ! -e $global_filename ){
      $replace_macro = 1;
    }
    else{
      $size = stat($global_filename)->size;

#      print "size = $size <br> \n";

      $size < 10000 and $replace_macro = 1;
    }

#    print "replace_macro = $replace_macro <br> \n";

    $replace_macro and do{

      print "<h4> .hist.root file not found or too small to contain histograms: ",
      "Replacing bfcread_hist_to_ps with bfcread_dst_QAhist </h4> \n";

      $macro_name = "bfcread_dst_QAhist";
      $file = '$STAR/StRoot/macros/analysis/bfcread_dst_QAhist.C';
      $self->MacroName($macro_name);
      $self->MacroFile($file);

      $macro_args = "nevent=all infile outfile";
      $self->MacroArguments($macro_args);

      $input_data_type =  ".dst.root";
      $self->InputDataType($input_data_type);

      $self->MacroReportFilename($report_key,$macro_name);
    };

  };

  #------------------------------------------------------

}
#=======================================================
sub RunMacro{
  my $self = shift;

  #-----------------------------------------------------------
  my $report_key = $self->ReportKey;
  my $macro_file = $self->MacroFile;
  my $macro_name = $self->MacroName;

  my $macro_report_filename= $self->MacroReportFilename;
  #--------------------------------------------------------------------------------------------
  # if macro report exists, quit...
  
  -s $macro_report_filename and do{
    print "Macro not run: file $macro_report_filename exists <br> \n";
    return;
  };

  #--------------------------------------------------------------------------------------------
  my $starlib_version = $QA_object_hash{$report_key}->LogReport->StarlibVersion;

  if ($starlib_version =~ /SL/){
    $starlib_version =~ s/SL//;
  }
  else{
    $starlib_version = "dev";
  }

  # Sl99h is screwed up - use 99i instead  pmj 13/11/99
#  $starlib_version eq "99h" and $starlib_version = "99i";

  my $production_dir = $QA_object_hash{$report_key}->LogReport->OutputDirectory; 

  my $nevent_requested = $QA_object_hash{$report_key}->LogReport->NEvent;
  $nevent_requested or $nevent_requested = 40;
  #--------------------------------------------------------------------------------------------

  $global_input_data_type = $self->InputDataType;

  find( \&QA_cgi_utilities::get_file, $production_dir );

  ! -e $global_filename and do{  
    print "<h4> File with type $global_input_data_type not found in directory $production_dir </h4> \n";
    return;
  };
  
  #--------------------------------------------------------------------------------------------
  # get output file name

  $output_file = $macro_report_filename;
  #--------------------------------------------------------------------------------------------
  # set up root commands

  $argument_string = $self->MacroArguments;

  ! $argument_string and do{  
    print "<h4> Argument string not found for macro $macro_file; defaults not allowed </h4> \n";
    return;
  };

  @args = split ' ',$argument_string;

  @root_commands = ();

  $exec_string = ".x $macro_file(";
  
  foreach $arg (@args){
    
    $arg =~ /infile/ and do{
      push @root_commands, "char *infile = \"$global_filename\"";
      $exec_string .= " infile,";
      next;
    };
    
    $arg =~ /outfile/ and do{
      push @root_commands, "char *outfile = \"$output_file\"";
      $exec_string .= " outfile,";
      next;
    };
    
    $arg =~ /nevent=(\S+)/ and do{  
      $nevent = $1;
      $nevent =~ /\d+/ or $nevent = $nevent_requested;
      $exec_string .= " $nevent,";
      next;
    };
    
    $arg =~ /string=(\S+)/ and do{  
      $exec_string .= " \"$1\",";
      next;
    };
  }
  
  # clean up exec string and terminate
  $exec_string =~ s/,$/\)/;
  
  push @root_commands, $exec_string;
  push @root_commands, ".q";
  
  #--------------------------------------------------------------------------------------------
  # all set, now run macro
    
  print "<H3> Making report for macro $macro_file... </H3>\n";
  
  print "<H4> Root macro: $macro_file </H4> \n";
  print "<H4> Input file: $global_filename </H4> \n";
  print "<H4> Output file: $output_file </H4> \n";
  
  -s $output_file and do {
    print "<H4> $macro_report_filename exists, macro not run.</h4> \n";
    return;
  };
  
  print "<H4> Running macro... </H4> \n";

  @root_output = QA_run_root::run_root( $starlib_version, $scratch, @root_commands);
  #--------------------------------------------------------------------------------------------
  # special treatment for various kinds of output file

 OUTPUT: {
    
    # if output is to STDOUT, filter root session for event labels and QAinfo string
    # and write to $output_file
    $self->OutputDataType =~ /STDOUT/ and do{

      open OUTPUTFILE, ">$output_file" or die "Cannot open output file $output_file:$! \n";
      foreach $line (@root_output){
	( $line =~ /QAInfo/ or $line =~ /==\s+Event\s+\d+/ ) and print OUTPUTFILE $line;
      }
      close OUTPUTFILE;
      last OUTPUT;
    };
    
    # if output file is postscript, gzip it
    $output_file =~ /\.ps$/ and do{
      print "<H4> gzipping file $output_file... </H4> \n";

      # kill gzipped file if it exists
      $temp = "$output_file\.gz";
      -e $temp and unlink ($temp);

      chmod 0666, $output_file;
      $status = system("/usr/local/bin/gzip $output_file");
      $output_file .= ".gz";
      last OUTPUT;
    };
    
  }
  #--------------------------------------------------------------------------------------------
  # check that output file made o.k.
  QA_make_reports::check_file_made($report_key, $macro_name, $output_file, @root_output);
  
}
#=======================================================
sub Evaluate{
  my $self = shift;

  #-----------------------------------------------------------

  my $report_key = $self->ReportKey;
  my $macro_name = $self->MacroName;
  my $report_name = $self->MacroReportFilename;
  #-----------------------------------------------------------
  $self->EvaluationFilename($report_key,$macro_name);
  #-----------------------------------------------------------

  $macro_with_package = "QA_macro_scalars::$macro_name";
  ($run_scalar_hashref, $event_scalar_hashref) = &$macro_with_package($report_key,$report_name);

  tie %event_scalars, "Tie::IxHash"; 
  tie %run_scalars, "Tie::IxHash"; 

  %event_scalars = %$event_scalar_hashref;
  %run_scalars = %$run_scalar_hashref;

  #-----------------------------------------------------------

  $self->EventScalarsHash(\%event_scalars);
  $self->RunScalarsHash(\%run_scalars);
  
  #-----------------------------------------------------------
  # run-wise tests
  $self->DoTests(\%run_scalars, 'run');

  # event-wise tests
  $self->DoTests(\%event_scalars, 'event');
  #-----------------------------------------------------------

}
#========================================================================
sub DoTests{

  my $self = shift;
  my $scalar_ref = shift;

  # test types are 'run' and 'event' (run-wise and event-wise tests)
  my $test_type = shift;

  #-----------------------------------------------------------

 TYPE: {
  
    $test_type eq 'run' and do{
      $scalars_string = $self->RunScalars_string;
      last TYPE;
    };
  
    $test_type eq 'event' and do{
      $scalars_string = $self->EventScalars_string;
      last TYPE;
    };

    return;
  }

  #-----------------------------------------------------------
  tie %scalars, "Tie::IxHash"; 
  %scalars = %$scalar_ref;
  #-----------------------------------------------------------

  my $report_key = $self->ReportKey;
  my $macro_name = $self->MacroName;
  my $report_name = $self->MacroReportFilename;

  #-----------------------------------------------------------

  # now cycle through tests, compare to scalars
  
  my @test_name_list = $self->TestNameList($test_type);
  
  foreach $test_name (@test_name_list){

    my $n_error = 0;
    my $n_warn = 0;
    
    my @test_line_list = $self->TestLineList($test_type, $test_name);
    
  TESTLINE: {
      
      foreach $test_line ( @test_line_list ) {

	($severity, $test_string) = split ':', $test_line;
	($this_scalar, $operator_string, $value_string) = split '\.', $test_string;

	# clean up strings (get rid of white space)
	$severity =~ s/\s+//g;
	$this_scalar =~ s/\s+//g;
	$operator_string =~ s/\s+//g;
	$value_string =~ s/\s+//g;
	
      OPERATOR:{
	  
	  # error if unexpected table found
	  $this_scalar =~ /nonscalar/ and $operator_string =~ /notfound/ and do{

	    # modified pmj 29/11/99
	    # clean up scalars_string, make array
	    $scalars_string =~ s/^\W+//;
	    $scalars_string =~ s/\W+$//;
	    @scalars_array = split / /, $scalars_string;

	    foreach $scalar_found ( keys %scalars ){
	      $display_string = "$scalar_found expected";
	      $perl_string = "*** Is $scalar_found in $scalars_string? ***";

	      $result = 'FALSE';
	      foreach $scalar ( @scalars_array ) {
		$scalar_found eq $scalar and do{
		  $result = 'TRUE';
		  last;
		};
	      }

	      $result eq 'FALSE' and $severity eq 'error' and $n_error++;
	      $result eq 'FALSE' and $severity eq 'warn' and $n_warn++;

	      $self->TestLineDisplayList($test_type, $test_name, $display_string);

	      $self->TestLineDisplayPerlString($test_type, $test_name, $display_string, $perl_string); 
	      $self->TestLineDisplaySeverity($test_type, $test_name, $display_string, $severity); 
	      $self->TestLineDisplayResult($test_type, $test_name, $display_string, $result); 
	    }
	    last TESTLINE;
	  };

	  # for doEvents: compare to logfile
	  # work has already been done: %scalars contains strings which were not matched 
	  # to log file, or contains one entry announcing success

	  $this_scalar =~ /string_QAInfo/ and $operator_string =~ /notfound/ and do{

	    foreach $scalar ( keys %scalars ){

	      $display_string = $scalar;
	      $perl_string = '$scalars{'.$scalar."} =~ /o.k./";

	      $result = eval( $perl_string ) ? "TRUE" : "FALSE" ;
	      $result eq 'FALSE' and $severity eq 'error' and $n_error++;
	      $result eq 'FALSE' and $severity eq 'warn' and $n_warn++;

	      $self->TestLineDisplayList($test_type, $test_name, $display_string);
	      $self->TestLineDisplayPerlString($test_type, $test_name, $display_string, $perl_string); 
	      $self->TestLineDisplaySeverity($test_type, $test_name, $display_string, $severity); 
	      $self->TestLineDisplayResult($test_type, $test_name, $display_string, $result); 
	    }
	    last TESTLINE;
	  };


	  # error if expected table not found
	  $operator_string =~ /found/ and do{
	    $perl_string = ' defined $scalars{'.$this_scalar."}";
	    last OPERATOR;
	  };
	  
	  # default: numerical tests
	  # is $value_string actually a scalar?
	  if ( defined $scalars{$value_string} ){
	    $value = $scalars{$value_string};
	  }
	  else{
	    $value = $value_string;
	  }
	  
	  # now figure out what the operator is
	  
	  $operator_string eq 'eq' and $operator = '==';
	  $operator_string eq 'ne' and $operator = '!=';
	  $operator_string eq 'lt' and $operator = '<';
	  $operator_string eq 'gt' and $operator = '>';
	  $operator_string eq 'le' and $operator = '<=';
	  $operator_string eq 'ge' and $operator = '>=';
	  
	  $perl_string = '$scalars{'.$this_scalar.'}'.$operator.$value;

	}

	$result = eval( $perl_string ) ? "TRUE" : "FALSE" ;
	$result eq 'FALSE' and $severity eq 'error' and $n_error++;
	$result eq 'FALSE' and $severity eq 'warn' and $n_warn++;

	$self->TestLineDisplayList($test_type, $test_name, $test_string);
	$self->TestLineDisplayPerlString($test_type, $test_name, $test_string, $perl_string); 
	$self->TestLineDisplaySeverity($test_type, $test_name, $test_string, $severity); 
	$self->TestLineDisplayResult($test_type, $test_name, $test_string, $result); 
	
      }
    } # end of TESTLINE

    $self->Nerror($test_type, $test_name, $n_error);
    $self->Nwarn($test_type, $test_name, $n_warn);
  }

}    
#=======================================================
sub Write{
  my $self = shift;

  my $filename = $self->EvaluationFilename;

  print "<h4> Writing report object to $filename... </h4> \n";

  nstore( \$self, $filename) or die "<h4> Cannot write $filename: $! </h4> \n";

  if ( -e $filename ){
    print "<h4> ... done </h4> \n";
  }
  else {
    print "<h4> file $filename not created, something went wrong. </h4> \n";
  }
}
#=========================================================================
sub TestDefinitionFile{
  my $self = shift;

  if (@_){
    my $filename = shift;
    $self->{test_definition_file} = $filename
  }

  return  $self->{test_definition_file};
}
#========================================================
sub NTests{
  my $self = shift;
  if (@_) {$self->{n_tests} = shift }
  return $self->{n_tests};
}
#========================================================
sub MacroArguments{
  my $self = shift;
  if (@_) {$self->{macro_args} = shift }
  return $self->{macro_args};
}
#========================================================
sub FirstStarlibVersion{
  my $self = shift;
  if (@_) {$self->{first_starlib_ver} = shift }
  return $self->{first_starlib_ver};
}
#========================================================
sub LastStarlibVersion{
  my $self = shift;
  if (@_) {$self->{last_starlib_ver} = shift }
  return $self->{last_starlib_ver};
}
#========================================================
sub InputDataType{
  my $self = shift;
  if (@_) {$self->{input_data_type} = shift }
  return $self->{input_data_type};
}
#========================================================
sub OutputDataExtension{
  my $self = shift;
  if (@_) {$self->{output_data_extension} = shift }
  return $self->{output_data_extension};
}
#========================================================
sub OutputDataFilename{
  my $self = shift;
  if (@_) {$self->{output_data_filename} = shift }
  return $self->{output_data_filename};
}
#========================================================
sub OutputDataType{
  my $self = shift;
  if (@_) {$self->{output_data_type} = shift }
  return $self->{output_data_type};
}
#========================================================
sub MacroComment{
  my $self = shift;
  if (@_) {
    my $temp = shift;
    # make newline if this is not first comment
    $self->{macro_comment} and $temp = "\n".$temp;
    $self->{macro_comment} .= $temp;
  }
  return $self->{macro_comment};
}
#========================================================
sub RunScalars_string{
  my $self = shift;
  if (@_) {$self->{run_scalars_string} .= shift }
  return $self->{run_scalars_string};
}
#========================================================
sub EventScalars_string{
  my $self = shift;
  if (@_) {$self->{event_scalars_string} .= shift }
  return $self->{event_scalars_string};
}
#========================================================
sub RunScalarsHash{
  my $self = shift;
  if (@_) { $hash_ref = shift;
	    tie %{$self->{run_scalars_hash}}, "Tie::IxHash"; 
	    %{$self->{run_scalars_hash}} = %$hash_ref;
	  }

  return \%{$self->{run_scalars_hash}};
}
#========================================================
sub EventScalarsHash{
  my $self = shift;
  if (@_) { $hash_ref = shift;
	    tie %{$self->{event_scalars_hash}}, "Tie::IxHash"; 
	    %{$self->{event_scalars_hash}} = %$hash_ref;
	  }

  return \%{$self->{event_scalars_hash}};
}
#========================================================
sub TestNameList{
  my $self = shift;
  my $type = shift;

  if (@_) {
    my $name = shift;
    push @{$self->{testname_array}->{$type}}, $name;
  }
  return @{$self->{testname_array}->{$type}};
}
#========================================================
sub TestComment{
  my $self = shift;
  my $test_type = shift;
  my $test_name = shift;
  
  $test_name or return;
  
  if (@_) {
    $line = shift;
    $self->{test}->{$test_type}->{$test_name}->{comment} or $line = "\n".$line;
    $self->{test}->{$test_type}->{$test_name}->{comment} .= $line;
  }
  
  return $self->{test}->{$test_type}->{$test_name}->{comment};
}
#========================================================
sub TestLineList{
  my $self = shift;

  (my $test_type = shift) or return;;
  (my $test_name = shift) or return;;
  
  if (@_) {
    my $line = shift;
    push @{$self->{test}->{$test_type}->{$test_name}->{test_line}}, $line;
  }

  return @{$self->{test}->{$test_type}->{$test_name}->{test_line}};
}
#========================================================
sub TestLineDisplayList{
  my $self = shift;

  (my $test_type = shift) or return;;
  (my $test_name = shift) or return;;
  
  if (@_) {
    my $line = shift;
    push @{$self->{test}->{$test_type}->{$test_name}->{test_line_display}}, $line;
  }
  else {
    exists $self->{test}->{$test_type}->{$test_name} or do{
      print "TestLineDisplayList: unknown test $test_name <br> \n";
      return "unknown test";
    };
  }

  return @{$self->{test}->{$test_type}->{$test_name}->{test_line_display}};
}
#========================================================
sub TestLineDisplayPerlString{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;
  (my $test_line = shift) or return;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{$test_line}->{perl} = shift;
  }
  
  return $self->{test}->{$test_type}->{$test_name}->{$test_line}->{perl};
}
#========================================================
sub TestLineDisplaySeverity{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;
  (my $test_line = shift) or return;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{$test_line}->{severity} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{$test_line}->{severity};
}
#========================================================
sub TestLineDisplayResult{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;
  (my $test_line = shift) or return;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{$test_line}->{result} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{$test_line}->{result};
}
#========================================================
sub Nerror{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{n_errors} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{n_errors};
}
#========================================================
sub Nwarn{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{n_warn} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{n_warn};
}
#=======================================================
sub MacroName{
  my $self = shift;
  if (@_){ $self->{macro_name} = shift; }

  return $self->{macro_name};
}
#=======================================================
sub MacroFile{
  my $self = shift;
  if (@_){$self->{macro_file} = shift; }

  return $self->{macro_file};
}
#=======================================================
sub ReportKey{
  my $self = shift;
  if (@_) {$self->{report_key} = shift }
  return $self->{report_key};
}
#=======================================================
sub MacroReportFilename{
  my $self = shift;

  if ( @_){
    my $report_key = shift;
    my $macro_name = shift;

    my $filetype = ( $self->OutputDataType =~ /ps/ ) ? ".ps" : ".qa_report";

    my $temp = $self->OutputDataFilename;

    if ($temp) {
      $filename = $temp.$filetype;
    }
    else{
      $extension = $self->OutputDataExtension;
      $filetype = $extension.$filetype;
      $filename = $macro_name.$filetype;
    }

    my $report_dirname = $topdir_report."/".$report_key;
    $self->{macro_report_filename} = $report_dirname."/".$filename;

    my $report_dirname_WWW = $topdir_report_WWW."/".$report_key;
    $self->{macro_report_filename_WWW} = $report_dirname_WWW."/".$filename;
  }

  return $self->{macro_report_filename};
}
#=======================================================
sub MacroReportFilenameWWW{
  my $self = shift;
  return $self->{macro_report_filename_WWW};
}
#=======================================================
sub EvaluationFilename{
  my $self = shift;

  if ( @_){
    my $report_key = shift;
    my $macro_name = shift;

    my $filename = $macro_name.".evaluation";

    my $report_dirname = $topdir_report."/".$report_key;
    $self->{evaluation_filename} = $report_dirname."/".$filename;

    my $report_dirname_WWW = $topdir_report_WWW."/".$report_key;
    $self->{evaluation_filename_WWW} = $report_dirname_WWW."/".$filename;
  }

  return $self->{evaluation_filename};
}
#=======================================================
sub EvaluationFilenameWWW{
  my $self = shift;
  return $self->{evaluation_filename_WWW};
}
#=======================================================
sub SummaryString{
  my $self = shift;

  #---------------------------------------------------------
  my $macro_name = $self->MacroName;

  my $summary_string = " $macro_name:";

  #-----------------------------------------------------------
  my $n_error = 0;
  my $n_warn = 0;
  my $n_test = 0;

  foreach $type ('run','event'){

    my @test_name_list = $self->TestNameList($type);
  
    foreach $test_name (@test_name_list){
      $n_test++;
      $n_error += $self->Nerror($type,$test_name);
      $n_warn += $self->Nwarn($type,$test_name);
    }

  }
  #-----------------------------------------------------------
  
  $n_test == 0 and do {

    # modified pmj 12/11/99
    #    $summary_string .= " done, no tests;";
    #    return $summary_string;
    return "";

  };

  #-----------------------------------------------------------

  if($n_error == 0 and $n_warn == 0){
    $summary_string .= "<font color=green> o.k.;</font>" ;
  }
  else{
    my $error_string = ($n_error == 1 )? "error" : "errors";
    my $warn_string = ($n_warn == 1 )? "warning" : "warnings";

    $n_error > 10 and $n_error = ">10";
    $n_warn > 10 and $n_warn = ">10";

    $summary_string .= "<font color=red> $n_error $error_string, $n_warn $warn_string;</font>";
  }

  #-----------------------------------------------------------
  return $summary_string;
}
