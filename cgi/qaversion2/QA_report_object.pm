#! /usr/bin/perl
#
# runs and tests the macros
#
#=========================================================
package QA_report_object;
#=========================================================
use CGI qw(:standard :html3);
use File::stat;
use File::Copy;
use File::Basename;
use Tie::IxHash;
use Data::Dumper;
use Storable qw(nstore retrieve); 

use QA_globals;
use QA_cgi_utilities;
use QA_object;
use QA_run_root;
use QA_macro_scalars;
use QA_db_utilities; 
use IO_object;

#use strict 'vars';
#=========================================================
1.;
#=========================================================
# class members

# most of these are set in GetTests
# just for the reader's benefit. %members is not explicitly used
# pointers to IO_objects start with IO

my %members = 
  (
    _ReportKey              => undef, # identifies job
    _TestDefinitionFile     => undef, # file that runs and test macros 
    _MacroName              => undef, # e.g. bfcread_dstBranch (no .C)
    _MacroFile              => undef, # full macro name (/path/name.C)
    _MacroArguments         => undef, # uhh.  arguments for the macro
    _InputDataType          => undef, # e.g. .hist.root 
    _OutputDataExtension    => undef, # e.g. .qa_report
    _OutputDataFilename     => undef, # e.g. tpc_hits 
    _OutputDataType         => undef, # e.g. .ps 
    _FirstStarlibVersion    => undef, # 
    _LastStarlibVersion     => undef, # 
    _NTests                 => undef, # number of tests requested
    _IORootCrashLog         => undef, # 
    _RunScalars_string      => undef, #
    _EventScalars_string    => undef, #
    _MacroComment           => undef, #
    _IOMacroReportFilename  => undef, #
    _IOEvaluationFilename   => undef, #
    _RunScalarsHash         => {},    #
    _EventScalarsHash       => {},    #
    _TestNameList           => {},    #
                       test => {}     # stores qa test results
  );
    
    
# there are additional members regarding the test scalars
# they look like $self->{test}->etc...
#=========================================================
sub new{
  my $classname = shift;
  my $self      = {};

  bless ($self, $classname);

  # initialize
   $self->_init(@_); #

  return $self;
}
#========================================================
# initialization of the control file and OnDisk is done 
# in the derived classes

sub _init{
  my $self = shift;
  my $report_key = shift;
  my $test_file  = shift;
  my $missing    = shift;

  $self->ReportKey($report_key);
  $self->TestDefinitionFile($test_file);
  $self->MissingFiles($missing);

}

#=========================================================
# get tests and macro to run from the TestDefinitionFile

sub GetTests{

  my $self = shift;
  
  # get the test definition file, report key
  my $test_definition_file = $self->TestDefinitionFile;
  my $report_key = $self->ReportKey;

  open TESTFILE, $test_definition_file 
    or die "Cannot open test definition file $test_definition_file: $! \n";
  my @test_definition_array = <TESTFILE>;
  close TESTFILE;
  
  # parse file contents
  my ($test_active, $n_tests) = (0,0);
  my ($macro_name, $test_type, $test_name, $temp);

  foreach my $line (@test_definition_array){

    # comment lines
    $line =~ /^\#/ and next;

    $line =~ /macro name:(.*)/ and do{
      my $file = $1;
      $macro_name = basename($file);
      $macro_name =~ s/\.C//;

      print h4("Found macro_name $macro_name, file = $file <br> \n");

      $self->MacroName($macro_name);
      $self->MacroFile($file);
      next;
    };

    $line =~ /macro arguments:(.*)/ and do{
      $self->MacroArguments($1);
      next;
    };

    $line =~ /input data filetype:(.*)/ and do{
      ($temp = $1) =~ s/\s+//g;
      $self->InputDataType($temp);
      next;
    };

    $line =~ /output data extension:(.*)/ and do{
      ($temp = $1) =~ s/\s+//g;
      $self->OutputDataExtension($temp);
      next;
    };

    $line =~ /output data filename:(.*)/ and do{
      ($temp = $1) =~ s/\s+//g;
      $self->OutputDataFilename($temp);
      next;
    };

    $line =~ /output data filetype:(.*)/ and do{
      ($temp = $1) =~ s/\s+//g;
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
      # set output of filename - use IO_object
      print "macro_name       = ",$self->MacroName,"\n",
            "output_data_type = ",$self->OutputDataType,"\n",
	    "output_data_filename= ",$self->OutputDataFilename,"\n",
	    "output_data_ext  = ",$self->OutputDataExtension,"\n";


      $self->IOMacroReportFilename(IO_object->new("MacroReportFilename",
						  $self->ReportKey, 
						  $self->MacroName,
						  $self->OutputDataType,
						  $self->OutputDataFilename,
						  $self->OutputDataExtension));

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
  # record the number of tests
  $self->NTests($n_tests);

  # set the root crash log just in case - via IO_object
  $self->IORootCrashLog(IO_object->new("RootCrashLog",
				       $self->ReportKey,
				       $self->MacroName));

#------------------------------------------------------
  # if macro is bfcread_hist_to_ps, check that .hist.root file exists

  my $hist_ok = 1;
  if ($self->MacroName eq "bfcread_hist_to_ps"){ 
    $hist_ok = 0 if $self->MissingFiles =~ /\.hist\.root/;
  }

  if (! $hist_ok ){

    print h4(" .hist.root file not found or too small to contain histograms: "),
    h4("Replacing bfcread_hist_to_ps with bfcread_dst_QAhist\n");

    my $macro_name = "bfcread_dst_QAhist";
    my $file = '$STAR/StRoot/macros/analysis/bfcread_dst_QAhist.C';
    $self->MacroName($macro_name);
    $self->MacroFile($file);

    my $macro_args = "nevent=all infile outfile";
    $self->MacroArguments($macro_args);

    my $input_data_type =  ".dst.root";
    $self->InputDataType($input_data_type);

    # reset IOMacroReportFilename
    $self->IOMacroReportFilename(IO_object->new("MacroReportFilename",
					      $macro_name, $self));
  }
  

}
#=======================================================
sub RunMacro{
  my $self = shift;
  my $starlib_version   = shift;
  my $nevent_requested  = shift;
  my $prod_files_ref    = shift; # ref to list of all output files for job
                                 # possible input files for macro

  my $report_key = $self->ReportKey;
  my $macro_file = $self->MacroFile; # fullname
  my $macro_name = $self->MacroName; # basename
  my $output_file= $self->IOMacroReportFilename->Name; # output of macro

  # if macro report exists, quit...   
  -s $output_file and do{
    print "Macro not run: file $output_file exists\n", br;
    return;
  };


  # get the input file that matches the input data type
  # first get all the production files
  
  # find the input for macro file according to input datatype
  my $input_type = $self->InputDataType;
  my @input_file = grep {/$input_type/} @{$prod_files_ref};
  my $input_file = $input_file[0];  # should only be one..   

  # does it exist?        
  -e $input_file or do{  
    my $production_dir = $self->ProductionDirectory;
    print h4("File with type $input_type not found in directory"),
          h4("$production_dir \n");
    return;
  };

  # special case for memory usage
  # add this to IO_object later

#  if ($macro_name eq 'MemoryUsage') {
#    $input_file = $self->LogReport->MemoryFile;
#    -e $input_file or do{
#	print h3("Cannot find memory file\n");
#	return;
#    };
#  }

  # set up root commands
  # get arguments
  my $argument_string = $self->MacroArguments;

  $argument_string or do{  
    print h4("Argument string not found for macro $macro_file;\n",
            "defaults not allowed\n");
    return;
  };

  my @args = split ' ',$argument_string;
  my @root_commands = ();
  my $exec_string = ".x $macro_file(";
  
  foreach my $arg (@args){
    
    $arg =~ /infile/ and do{
      push @root_commands, "char *infile = \"$input_file\"";
      $exec_string .= " infile,";
      next;
    };
    
    $arg =~ /outfile/ and do{
      push @root_commands, "char *outfile = \"$output_file\"";
      $exec_string .= " outfile,";
      next;
    };
    
    $arg =~ /nevent=(\S+)/ and do{  
      my $nevent = $1;
      $nevent =~ /\d+/ or $nevent = $nevent_requested;
      $exec_string .= " $nevent,";
      next;
    };    
    # bum 25/03/00 - added int argument
    $arg =~ /int=(\d+)/ and do{
      $exec_string .= " $1,";
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
  
  #----------------------------------------------------------------------------
  # all set, now run macro
    
  print h3("Making report for macro $macro_file...\n");  
  print h4("Root macro: $macro_file\n");
  print h4("Input file: $input_file \n");
  print h4("Output file: $output_file\n");
  
  -s $output_file and do {
    print h3("$output_file exists, macro not run.\n");
    return;
  };
  
  print h4("Running macro... \n");

  my $io = new IO_object("ScratchDir");
  my $scratch_local = $io->Name();
  undef $io;

  print "Rootcommands = ", "\n", join ("\n",@root_commands),"\n";
  print "Starlib = '$starlib_version'\n";  

  my @root_output = 
    QA_run_root::run_root( $starlib_version, $scratch_local, @root_commands);
  #--------------------------------------------------------------------------
  # special treatment for various kinds of output file

  if ($self->OutputDataType =~ /STDOUT/){
    # if output is to STDOUT, filter root session for event labels 
    # and QAinfo string and write to $output_file

    my $fh = $self->IOMacroReportFilename->Open(">", "0755");
    
    foreach my $line (@root_output){
      ( $line =~ /QAInfo/ or $line =~ /==\s+Event\s+\d+/ ) 
	and print $fh $line;
    }
    close $fh;
   
  }
    
  # if output file is postscript, gzip it
  if ( $output_file =~ /\.ps$/ and $macro_name ne 'MemoryUsage') {
    print "<H4> gzipping file $output_file... </H4> \n";

    # kill gzipped file if it exists
    my $temp = "$output_file\.gz";
    -e $temp and unlink ($temp);

    chmod 0666, $output_file;
    my $status = system("/usr/local/bin/gzip $output_file");
    $output_file .= ".gz";
    
    # need to reset output_file
    $self->IOMacroReportFilename->Name($output_file);
  }

  #--------------------------------------------------------------------------
  # check that output file made o.k.
  $self->CheckFileMade(@root_output);
  
}
#===================================================================
sub CheckFileMade {
  my $self = shift;
  my @root_output = shift;

  my $report_key = $self->ReportKey;
  my $macro_name = $self->MacroName; # basename
  my $output_file= $self->IOMacroReportFilename->Name; # output of macro

  #-------------------------------------------------------------------
  # special check for doEvents

  $macro_name eq 'doEvents' and $self->CheckDoEvents();

  #-------------------------------------------------------------------
  # output exists, everything's ok
  -e  $output_file and do {
    print "<h4> ...done </h4> \n";
    return;
  };

  #-------------------------------------------------------------------
  # Trouble: generate filename to dump root session into

  my $fh = $self->IORootCrashLog->Open(">", "0664");
  #-------------------------------------------------------------------
  print h4("File $output_file not created.\n",
           "Something went wrong. Here is root session:\n");

  print "<pre> \n";
  foreach my $line (@root_output){
    print $line;
    print $fh $line;
  }
  print "</pre> \n";

  close $fh;
}
#=======================================================================
sub CheckDoEvents{
  my $self = shift;
  
  my $output_file = $self->IOMacroReportFilename->Name;

  my $fh          = $self->IOMacroReportFilename->Open;
  my @lines = <$fh>;
  close $fh;

  my $crash = 0;

 CHECKCRASH: {
    while( my $line = pop @lines ){
      last CHECKCRASH if $line =~ /Event\s+\d+\s+finish/;
    }
    $crash = 1;
  }
  
  # if finish string not found, delete file
  $crash and unlink $output_file;
}
#=======================================================
sub EvaluateMacro{
  my $self = shift;

  # any tests defined?
  $self->NTests or return;

  # does the output file exist? (and tests were defined)
  my $macro_name = $self->MacroName;
  unless ( -s $self->IOMacroReportFilename->Name ) {
    print h3("Did not do evaluation for $macro_name because\n",
	     "the macro was never run.\n");
    return;
  }
  # evaluate and write the evaluation file to disk
  print h4("Evaluating $macro_name...\n");

  $self->Evaluate;
  $self->Write;

}
#=======================================================
sub Evaluate{
  my $self = shift;

  #-----------------------------------------------------------

  my $report_key = $self->ReportKey;
  my $macro_name = $self->MacroName;
  my $report_name = $self->IOMacroReportFilename->Name;

  # set the evaluation filename - use IO_object
  my $io = new IO_object("EvaluationFilename",$report_key, $macro_name);
  #-----------------------------------------------------------
  $self->EvaluationFilename($io->Name);
  #-----------------------------------------------------------
  
  my $macro_with_package = "QA_macro_scalars::$macro_name";
  my ($run_scalar_hashref, $event_scalar_hashref) 
    = &$macro_with_package($report_key,$report_name);

 
  $self->EventScalarsHash($event_scalar_hashref);
  $self->RunScalarsHash($run_scalar_hashref);
  
 
  #-----------------------------------------------------------
  # run-wise tests
  $self->DoTests($run_scalar_hashref, 'run');

  # event-wise tests
  $self->DoTests($event_scalar_hashref, 'event');
  #-----------------------------------------------------------

}
#========================================================================
sub DoTests{

  my $self = shift;
  my $scalar_ref = shift;

  # test types are 'run' and 'event' (run-wise and event-wise tests)
  my $test_type = shift;

  #-----------------------------------------------------------
  my ($scalars_string, %scalars, @scalars_array);
  
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

  tie %scalars, "Tie::IxHash"; 
  %scalars = %$scalar_ref;

  my $report_key = $self->ReportKey;
  my $macro_name = $self->MacroName;
  my $report_name = $self->IOMacroReportFilename->Name;

  #-----------------------------------------------------------
  # now cycle through tests, compare to scalars
  no strict;

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
# store the qa evaluation hash as EvaluationFilename

sub Write{
  my $self = shift;

  my $filename = $self->EvaluationFilename;

  print h4("Writing report object to $filename...\n");

  nstore( \$self, $filename) 
    or die h4("Cannot write $filename: $!\n");

  if ( -e $filename ){
    print h4("... done \n");
  }
  else {
    print h4("<font color=red> file $filename not created,\n"),
          h4("something went wrong. </font>\n");
  }

}

#============== accessors, etc ==========================

sub MissingFiles{
    my $self = shift;
    $self->{_MissingFiles} = shift if @_;
    return $self->{_MissingFiles};
}

sub ReportKey{
  my $self = shift;
  $self->{_ReportKey} = shift if @_;
  return $self->{_ReportKey};
}

sub TestDefinitionFile{
  my $self = shift;
  $self->{_TestDefinitionFile} = shift if @_;
  return $self->{_TestDefinitionFile};
}

sub MacroName{
  my $self = shift;
  $self->{_MacroName} = shift if @_;
  return $self->{_MacroName};
}

sub MacroFile{
  my $self = shift;
  $self->{_MacroFile} = shift if @_;
  return $self->{_MacroFile};
}

sub MacroArguments{
  my $self = shift;
  $self->{_MacroArguments} = shift if @_;
  return $self->{_MacroArguments};
}

sub InputDataType{
  my $self = shift;
  $self->{_InputDataType} = shift if @_;
  return $self->{_InputDataType};
}

sub OutputDataExtension{
  my $self = shift;
  $self->{_OutputDataExtension} = shift if @_;
  return $self->{_OutputDataExtension};
}

sub OutputDataFilename{
  my $self = shift;
  $self->{_OutputDataFilename} = shift if @_;
  return $self->{_OutputDataFilename};
}

sub OutputDataType{
  my $self = shift;
  $self->{_OutputDataType} = shift if @_;
  return $self->{_OutputDataType};
}

sub FirstStarlibVersion{
  my $self = shift;
  $self->{_FirstStarlibVersion} = shift if @_;
  return $self->{_FirstStarlibVersion};
}

sub LastStarlibVersion{
  my $self = shift;
  $self->{_LastStarlibVersion} = shift if @_;
  return $self->{_LastStarlibVersion};
}

sub NTests{
  my $self = shift;
  $self->{_NTests} = shift if @_;
  return $self->{_NTests};
}

sub IORootCrashLog{
  my $self = shift;
  $self->{_RootCrashLog} = shift if @_;
  return $self->{_RootCrashLog};
}

sub IOMacroReportFilename{
  my $self = shift;
  $self->{_IOMacroReportFilename} = shift if @_;
  return $self->{_IOMacroReportFilename};
}

sub EvaluationFilename{
  my $self = shift;
  $self->{_EvaluationFilename} = shift if @_;
  return $self->{_EvaluationFilename};
}


#-------------------------------------------------------
sub RunScalars_string{
  my $self = shift;
  if (@_) {$self->{_RunScalars_string} .= shift }
  return $self->{_RunScalars_string};
}
#--------------------------------------------------------
sub EventScalars_string{
  my $self = shift;
  if (@_) {$self->{_EventScalars_string} .= shift }
  return $self->{_EventScalars_string};
}
#--------------------------------------------------------
sub MacroComment{
  my $self = shift;
  if (@_) {
    my $temp = shift;
    # make newline if this is not first comment
    $self->{_MacroComment} and $temp = "\n".$temp;
    $self->{_MacroComment} .= $temp;
  }
  return $self->{_MacroComment};
}
#--------------------------------------------------------

sub RunScalarsHash{
  my $self = shift;
  if (@_) { my $hash_ref = shift;	    
	    tie %{$self->{_RunScalarsHash}}, "Tie::IxHash"; 
	    %{$self->{_RunScalarsHash}} = %$hash_ref;
	  }

  return \%{$self->{_RunScalarsHash}};
}
#--------------------------------------------------------

sub EventScalarsHash{
  my $self = shift;
  if (@_) { my $hash_ref = shift;
	    tie %{$self->{_EventScalarsHash}}, "Tie::IxHash"; 
	    %{$self->{_EventScalarsHash}} = %$hash_ref;
	  }

  return \%{$self->{_EventScalarsHash}};
}
#--------------------------------------------------------

sub TestNameList{
  my $self = shift;
  my $type = shift;

  if (@_) {
    my $name = shift;
    push @{$self->{_TestNameList}->{$type}}, $name;
  }
  return @{$self->{_TestNameList}->{$type}};
}
#--------------------------------------------------------

sub TestComment{
  my $self = shift;
  my $test_type = shift;
  my $test_name = shift;
  
  $test_name or return;
  
  if (@_) {
    my $line = shift;
    $self->{test}->{$test_type}->{$test_name}->{comment} or $line = "\n".$line;
    $self->{test}->{$test_type}->{$test_name}->{comment} .= $line;
  }
  
  return $self->{test}->{$test_type}->{$test_name}->{comment};
}
#--------------------------------------------------------

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
#--------------------------------------------------------

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
#--------------------------------------------------------

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
#--------------------------------------------------------

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
#--------------------------------------------------------

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
#--------------------------------------------------------

sub Nerror{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{n_errors} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{n_errors};
}
#--------------------------------------------------------

sub Nwarn{
  my $self = shift;

  (my $test_type = shift) or return;
  (my $test_name = shift) or return;;

  if (@_) {
    $self->{test}->{$test_type}->{$test_name}->{n_warn} = shift;
  }

  return $self->{test}->{$test_type}->{$test_name}->{n_warn};
}
#--------------------------------------------------------


#========================================================
1;
