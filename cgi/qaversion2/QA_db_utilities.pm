
#! /usr/bin/perl
# 
# utilities for database interface 
#
#===================================================================
package QA_db_utilities;
#===================================================================
use CGI qw/:standard :html3/;

use DBI;
use Time::Local;
use File::Basename;
use File::stat;
use QA_globals;

require Exporter;
@ISA       = qw(Exporter);
# symbols to export upon request
# other Db packages need these

my @db_globals = qw($dbh 
		    $dbQA
		    $dbFile
		    $JobStatus
		    $FileCatalog
		    $ProdOptions
		    $JobRelations
		    $QASummaryTable
		    $QAMacrosTable 
		    %QASum
		    %QAMacros);

@EXPORT_OK   = @db_globals;
%EXPORT_TAGS = ( db_globals => [ @db_globals] );


use vars qw($dbh $dbQA $dbFile $JobStatus $ProdOptions $FileCatalog
	    $JobRelations $QASummaryTable $QAMacrosTable %QASum %QAMacros);

use strict;
1;
#===================================================================

#
# $dbFile and $dbQA are the 'filecatalog' and 'qa' 
# databases respectively.

# connect and disconnect are called at the beginning
# and end of QA_main.pm and QA_main::doBatch,
# so none of the subs below explicitly connect and
# disconnect from the db server

# $dbh is the database handle (as usual)

# for specific information about the operation database, good luck
# The structure of QA database is the following:
# 

# table : 'QASummary' ($dbQA - set in DataClass_object...)
#         Contains the basic information about the qa status
#         
#         jobID       varchar(64)         not null index,
#         report_key  varchar(64)         not null,
#         type        varchar(20)         not null index,
#         QAdone      enum('Y','N')       not null default 'N' index,
#         QAok        enum('Y','N','n/a') not null default 'n/a' index,
#         QAdate      datetime            not null,
#         controlFile varchar(128)        not null default 'n/a',
#         qaID        mediumint           not null auto_increment,
#                     primary key (qaID),
#                     

# table : 'QAMacros'
#          
#          qaID       mediumint(9) not null index
#          macroName  varchar(64)  not null
#          fName      varchar(64)  not null
#          path       varchar(128) not null
#          extension  varchar(10)  not null
#          size       int(11)      not null
#          createTime datetime     not null
#          status     varchar(20)  not null index
#          warnings   varchar(5)   not null index
#          errors     varchar(5)   not null index
#          ID         mediumint(9) not null auto_increment 
#                     primary key(ID)


# database variables - just in case you want to change the column names
# sorry - columns for other databases are hard coded...

# QASummary table
%QASum = (
	 Table        => 'QASummary', # name of the table
	 jobID        => 'jobID',
	 report_key   => 'report_key',
	 type         => 'type',      # type of data (real, MC)
	 QAdone       => 'QAdone',
	 QAok         => 'QAok',
	 QAdate       => 'QAdate',
	 controlFile  => 'controlFile',
	 qaID         => 'qaID'
	 );

# QAMacros
%QAMacros = (
	 Table      => 'QAMacros', # name of the table
	 qaID      => 'qaID',
	 macroName  => 'macroName',
	 fName      => 'fName',
	 path       => 'path',
	 extension  => 'extension',
	 size       => 'size',
	 createTime => 'createTime',
	 status     => 'status',
	 warnings   => 'warnings',
	 errors     => 'errors',
	 ID         => 'ID'        # never used
	 );


#====================================================================

my $serverHost = 'duvall.star.bnl.gov';
my $userFile = '/star/u2e/starqa/.my.cnf';
my %attr = (RaiseError =>1, PrintError =>0); # rely on this to catch errors

#===================================================================
# connecting to $dbQA is arbitray.  just need to connect to 
# the mysql server

sub db_connect{

  SetDBVariables();

  my $datasource =
    "DBI:mysql:$dbQA:$serverHost;mysql_read_default_file=$userFile";

  my ($user_name, $password);

  # $dbh is a global...
  $dbh = DBI->connect($datasource, $user_name, $password, \%attr)
    or die "Couldnt connect to $dbQA: $dbh->errstr";

  
}
#=====================================================================

sub db_disconnect{
  $dbh->disconnect or die "Couldnt disconnect from $dbQA";
}

#===================================================================
# pmj 3/6/00 declare variables with file scope
# the names of the operations database, the qa database
# and the table names are set in the DataClass_object

sub SetDBVariables{
  
  $dbFile         = $gDataClass_object->dbFile(); 
  $FileCatalog    = $gDataClass_object->FileCatalog(); 
  $JobStatus      = $gDataClass_object->JobStatus(); 
  $ProdOptions    = $gDataClass_object->ProdOptions();
  $JobRelations   = $gDataClass_object->JobRelations();
  $dbQA           = $gDataClass_object->dbQA();
  #$QASummaryTable = $gDataClass_object->QASummaryTable(); 
  #$QAMacrosTable  = $gDataClass_object->QAMacrosTable();

}
#=====================================================================
# get the log file 

sub GetNightlyLogFile{
  my $jobID = shift;
  
  my $query = qq{select 
		 concat(path,'/',logFile)		 
		 from $dbFile.$JobStatus  
		 where jobID='$jobID' };
  
  return $dbh->selectrow_array($query);


}    
#===========================================================================
# get the log file for offline

sub GetOfflineLogFile{
  my $jobID = shift;

  # this query gets the summary of the log file
  my $query = qq{select 
		 concat(sumFileDir,'/',sumFileName)		 
		 from $dbFile.$JobStatus  
		 where jobID='$jobID' };
  
  my $logfile = $dbh->selectrow_array($query);
   
  # change to the actual logfile
  # e.g. /star/rcf/disk00001/star/P00hd/sum/daq/st_physics_1166036_raw_0002.sum
  #

  $logfile =~ s/\/sum/\/log/g; # change the path info
  $logfile =~ s/\.sum$/\.log/; # change the data type 

  return $logfile;
}    

#=========================================================================
# check if the various output files exist
# input is the jobID
# .dst.root, .hist.root, (flag if too small), .tags.root, .runco.root
# .geant.root,

sub GetMissingFiles{
  my $jobID = shift;
  my ($missing_files); # return the missing files as a string
  my $hist_size =  1000;

  # these are the file components we're looking for
  my %comp_hash = (
		   dst  => undef, 
		   hist => undef, 
		   tags => undef, 
		   runco=> undef, 
		   geant=> undef
		  );
  
  # general checking
  my $query =  qq{select component 
		  from $dbFile.$FileCatalog 
	          where jobID='$jobID' };

  # special check for hist files
  my $query2 = qq{select component
		  from $dbFile.$FileCatalog 
                  where jobID = '$jobID' and
		        component='hist' and
		        size > $hist_size };


  my $sth= $dbh->prepare($query);
  $sth->execute;

  # for each component, mark if it exists in the db
  while(my $component = $sth->fetchrow_array){
    exists $comp_hash{$component} and $comp_hash{$component} = 1;
  }
  
  $sth = $dbh->prepare($query2);
  $sth->execute;

  # additional stuff for .hist
  my $hist_file = $sth->fetchrow_array;
  defined $hist_file or $comp_hash{'hist'}=undef; 

  # mark the missing files
  while ( my ($component, $status) = each %comp_hash){
      $status eq 1 or $missing_files .= " $component.root";
    }
  
  return $missing_files;
}
#=========================================================================
# get the report_key from QASummary
# never used

sub GetReportKey{
  my $jobID = shift;
  
  my $query = qq{select $QASum{report_key}
		 from  $dbQA.$QASum{Table}
		 where $QASum{jobID} = '$jobID'};
    
  return $dbh->selectrow_array($query);

}

#==========================================================================
# get the jobID according to the report key

sub GetJobID{
  my $reportkey = shift;

  my $query = qq{select $QASum{jobID} 
		 from  $dbQA.$QASum{Table} 
	         where $QASum{report_key}='$reportkey'};

  my $jobID = $dbh->selectrow_array($query);
  
  return $jobID;  
}

#==========================================================================
# get the qaID according to the report key

sub GetQAID{
  my $report_key = shift;
  
  my $query = qq{select $QASum{qaID}
		 from $dbQA.$QASum{Table}
		 where $QASum{report_key} = '$report_key'};

  return $dbh->selectrow_array($query);
}

#==========================================================================
# get the input file for the macros
# arguments are jobID and filetype
# file type must be in the form 'component'+'format'
# not used

sub GetMacroInputFile{
  my $jobID = shift;  
  my $filetype = shift; #e.g. .hist.root

  # remove leading spaces, dot if any
  $filetype =~ s/^\s*\.?//;

  my ($component, $format) = split /\./, $filetype;
				      
  my $query = qq{select concat(file.path, '/', file.fName)
	         from $dbFile.$FileCatalog as file 
	         where file.jobID='$jobID' and
		       file.component='$component' and
                       file.format='$format'
	      };

  return $dbh->selectrow_array($query);

} 
#========================================================================
# check if files are on disk

sub OnDiskNightly{
  my $jobID =  shift;

  my $query = qq{select ID 
		   from $dbFile.$FileCatalog
		   where jobID = '$jobID' and
                         avail = 'Y' limit 1};

  my $status = $dbh->selectrow_array($query);

  return defined $status ;
}
#========================================================================
# check if files are on disk

sub OnDiskOffline{
  my $jobID =  shift;
 

  my $query = qq{select ID 
		   from $dbFile.$FileCatalog
		   where jobID = '$jobID' and
                         hpss = 'N' limit 1};

  my $status = $dbh->selectrow_array($query);

  return defined $status;
}



#===================================================================
# get the control file info for nightly test
# event generator, event type, geometry...

sub GetControlFileInfo{
  my $jobID = shift;

  my $query = qq{select distinct 
		   eventGen, eventType, geometry
		 from $dbFile.$FileCatalog 
		 where jobID='$jobID' };
  
  return $dbh->selectrow_array( $query );

}
#===================================================================
# get output file of the job (dst.root) for offline and nightly

sub GetOutputFileOffline{
  my $jobID = shift;

  my $on_disk_clause;

  my $query = qq{select path, fName
		 from $dbFile.$FileCatalog 
		 where jobID ='$jobID' and
		       component = 'dst' and
		       format = 'root' and
		       hpss = 'N'
		       limit 1};

  #returns the path and name
  return $dbh->selectrow_array( $query );
}
#===================================================================
# get output file of the job (dst.root) for offline and nightly
# path and name for nightly

sub GetOutputFileNightly{
  my $jobID = shift;

  my $on_disk_clause;

  my $query = qq{select path, fName
		 from $dbFile.$FileCatalog 
		 where jobID ='$jobID' and
		       component = 'dst' and
		       format = 'root' and
		       avail = 'Y'
		       limit 1};

  #returns the path and name
  return $dbh->selectrow_array( $query );
}

#===================================================================
# get job completion time for offline and nightly

sub GetJobCompletionTime{
  my $jobID = shift;

  my $query = qq{select createTime 
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' limit 1};


  return $dbh->selectrow_array($query);

}

#===================================================================
# returns the production series, chain name,
# library version and chain options of job for offline

sub GetProdOptions{
  my $jobID =  shift;

  my $query = qq{select prod.prodSeries, prod.chainName,
		        prod.libVersion, prod.chainOpt
		 from $dbFile.$ProdOptions as prod,
		      $dbFile.$JobStatus as job
		 where job.jobID = '$jobID' and
		       job.prodSeries = prod.prodSeries and
                       job.chainName = prod.chainName };

  return $dbh->selectrow_array ($query);
}
#===================================================================
# returns the node (machine) that the job was run for offline and nightly

sub GetNodeID{
  my $jobID = shift;

  my $query = qq{select nodeID 
		 from $dbFile.$JobStatus 
		 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}
#===================================================================
# returns the input file name for offline

sub GetInputFnOffline{
  my $jobID = shift;

  my $query = qq{select inputFile 
		 from $dbFile.$JobRelations
                 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}

#====================================================================
# return number of events done for offline

sub GetNEventDoneOffline{
  my $jobID = shift;

  my $query = qq{select NoEvents 
		 from $dbFile.$JobStatus
		 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}
#====================================================================
# return number of events done for nightly

sub GetNEventDoneNightly{
  my $jobID = shift;

  my $query = qq{select NoEventDone 
		 from $dbFile.$JobStatus
		 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}

#=====================================================================
# get the low and high event done (processed) for offline real

sub GetLoAndHiEvent{
  my $jobID = shift;
  
  my $query = qq{select NevLo, NevHi
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' 
	         limit 1};

  return $dbh->selectrow_array($query);
}

#=====================================================================
# returns job status for nightly and offline

sub GetJobStatus{
  my $jobID = shift;

  my $query = qq{select jobStatus 
                 from $dbFile.$JobStatus
                 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}
#=====================================================================
# get the root level, star level, starlib version, and chain 
# for nightly tests

sub GetStarRootInfo{
  my $jobID = shift;

  my $query = qq{select LibLevel, rootLevel, LibTag, chainOpt
		 from $dbFile.$JobStatus
		 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}

#======================================================================
# get num of events requested from nightly

sub GetNEventRequested{
  my $jobID = shift;

  my $query = qq{select NoEventReq
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' 
	         limit 1};
  
  return $dbh->selectrow_array($query);
}
#=====================================================================
# get runID for offline

sub GetRunID{
  my $jobID = shift;

  my $query = qq{select runID
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID'
		 limit 1};

  return $dbh->selectrow_array($query);
}
#=====================================================================
# returns all production files for offline 

sub GetAllProductionFilesOffline{
  my $jobID     = shift;
  my (@file_list, $file);
  
  my $query = qq{select concat(path,'/',fName)
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' and
	               hpss = 'N'};
 
  my $sth = $dbh->prepare($query);
  $sth->execute;

  
  push @file_list, $file while ($file = $sth->fetchrow_array);

  return \@file_list;
}
#=====================================================================
# returns  all production files for nightly 

sub GetAllProductionFilesNightly{
  my $jobID     = shift;
  my (@file_list, $file);
  
  my $query = qq{select concat(path,'/',fName)
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' and
	               avail = 'Y'};
 
  my $sth = $dbh->prepare($query);
  $sth->execute;

  
  push @file_list, $file while ($file = $sth->fetchrow_array);

  return \@file_list;
}
#=============================================================
# returns the number of events that werent written out to dst

sub GetNoEventSkipped{
  my $jobID = shift;

  my $query = qq{select NoEventSkip
		 from $dbFile.$JobStatus
		 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}

#=============================================================
# delete jobID from QASummary and remove the 
# corresponding report directory

sub EraseJob{
  my $report_key = shift;
  my $report_dir = shift;

  my $query = qq{delete from $dbQA.$QASum{Table}
		 where $QASum{report_key} = '$report_key'};

  # delete from db
  $dbh->do($query) 
    or warn "Could not delete $report_key from $QASum{Table}";

  # rm report directory
  rmdir $report_dir or warn "Could not remove $report_dir";
}
#===========================================================
# clear the QAMacros table in db

sub ClearQAMacrosTable{
  my $qaID = shift;
 
  my $query = qq{delete from $dbQA.$QAMacros{Table}
		 where $QAMacros{qaID} ='$qaID'};

  print h4("Clearing macros from the database for qaID = $qaID...\n"); 
 
  $dbh->do($query);

  print h4("...done\n");
}

#==============================================================
# Write QASummary

sub WriteQASummary{
  my $qa_status    = shift; # 0,1
  my $qaID         = shift;
  my $control_file = shift;

  # the control file may be a symlink
  $control_file = readlink $control_file || $control_file;
  
  # qa ok?
  my $QAok = $qa_status ? 'Y' : 'N';
  
  # get current date
  my ($sec, $min, $hour, $day, $month, $year) = localtime;
  $year += 1900;  $month++;
  my $datetime = "$year-$month-$day $hour:$sec:$min";

  my $query = qq{update $dbQA.$QASum{Table} 
	      set 
		$QASum{QAdone}      ='Y', 
		$QASum{QAok}        ='$QAok', 
		$QASum{QAdate}      = '$datetime',
		$QASum{controlFile} = '$control_file'
	      where $QASum{qaID} ='$qaID'};

  print h4("Writing overall QA summary into db...\n");

  $dbh->do($query) or die "$query";

  print h4("...done\n");
}

#==========================================================
# write the QA macro summary into the db
# takes in a report_object as an arg
# writes in the following information
#
# jobID   
# macro_name
# fName
# path
# extension
# size
# createTime
# status
# warnings
# errors

sub WriteQAMacroSummary{
  my $qaID      = shift; # needs the jobID from QA_object
  my $report_obj = shift; # QA_report_object
  my $option     = shift; # evaluate_only

  my ($status, $errors, $warnings, $n_error, $n_warn);
  my $qa_status = 1; # default is that everything's a-ok

  # macro output info
  my $output_file = $report_obj->IOMacroReportFilename->Name;
  my $macro_name  = $report_obj->MacroName;
  my $fName       = basename($output_file);
  my $path        = dirname($output_file);
  my ($junk, $extension) = split /\./, $fName, 2;

  my ($size, $createTime_epoch, $createTime);

  # check that the output file exists
  
  if ( -e $output_file) 
  {
    $size             = stat($output_file)->size;
    $createTime_epoch = stat($output_file)->mtime;
  } 
  else 
  { # doesnt exist - keep the extention though...
    $fName      = "n/a";
    $size       = "n/a";
    $path       = "n/a";
  }
  # check for root crash

  # -- fill in QA status for the macro--
  my $rootcrashlog = $report_obj->IORootCrashLog->Name;
  
  if (-s $rootcrashlog)
  {
    $status    = "crashed";
    $errors    = "n/a";
    $warnings  = "n/a";
    $qa_status = 0;
  }
  # check if the macro was actually run
  # look for output file - maybe the input file didnt exist
  elsif (not -e $output_file)
  {
    $status     = "not run";
    $errors     = "n/a";
    $warnings   = "n/a";
    $qa_status  = 0;
  }
  # if no tests were defined and it succesfully ran
  elsif ($report_obj->NTests == 0 )
  {
    $status    = "finished";
    $errors    = "n/a";
    $warnings  = "n/a";
  }
  else 
  {
  # still here?
  # loop over each type of test
    foreach my $type ('run','event'){

      my @test_name_list = $report_obj->TestNameList($type);
    
      # loop over each test 
      foreach my $test_name (@test_name_list){
	$n_error += $report_obj->Nerror($type,$test_name);
	$n_warn  += $report_obj->Nwarn($type,$test_name);
      }
      
    }
    # adjust if more than 10 warnings
    $status   = "finished";
    $errors   = ($n_error > 10) ? ">10" : $n_error;
    $warnings = ($n_warn > 10) ? ">10" : $n_warn;
    
    ($errors or $warnings) and $qa_status = 0;
  }

  my $query;

  # convert createTime_epoch 
  if (defined $createTime_epoch){
    my ($sec, $min, $hour, $day, $month, $year) = localtime($createTime_epoch);
    $year += 1900; $month++;
    $createTime = "$year-$month-$day $hour:$min:$sec";
  }
 
  # only re-evaluating, update table
  if ($option eq 'evaluate_only' )
  {
    $query = 
      qq{update $dbQA.$QAMacros{Table}
	 set
	   $QAMacros{status}     = '$status',
           $QAMacros{warnings}   = '$warnings',
           $QAMacros{errors}     = '$errors'
	 where $QAMacros{macroName} = '$macro_name' and
	       $QAMacros{fName}     = '$fName' and
	       $QAMacros{qaID}     = '$qaID'};
  }
  else
  { # new macros... insert into table
    $query = 
      qq{insert into $dbQA.$QAMacros{Table}
	 set
	   $QAMacros{qaID}      = '$qaID',
	   $QAMacros{macroName}  = '$macro_name',
	   $QAMacros{fName}      = '$fName',
           $QAMacros{path}       = '$path',
           $QAMacros{extension}  = '$extension',
           $QAMacros{size}       = '$size',
           $QAMacros{createTime} = '$createTime',
           $QAMacros{status}     = '$status',
           $QAMacros{warnings}   = '$warnings',
           $QAMacros{errors}     = '$errors'};
  }
  print h4("Inserting qa macro summary into db for $macro_name...\n");

  # insert
  my $rc = $dbh->do($query);

  if ($rc) { print h4("...done\n")}
  else     { print h4("<font color = red> Error. Cannot insert qa info for ",
		      "$output_file</font>"); return;}
    
  return $qa_status;
}
#==============================================================
# get overall qa summary

sub GetQASummary{
  my $qaID = shift;

  # get QAdone, QAdate,  
  my $query = qq{select $QASum{QAdone}, $QASum{QAdate}
                 from $dbQA.$QASum{Table}
                 where $QASum{qaID} = '$qaID' limit 1};

  my ($QADone, $QADate) = $dbh->selectrow_array($query);
  
  $QADone = ($QADone eq 'Y') ? 1 : 0;

  return ($QADone, $QADate);

}
#==============================================================
# get specific macro results if there are any problems with 
# the evaluation.  returns ref to a 2-d array

sub GetQAMacrosSummary{
  my $qaID = shift;

  # get the QA status, errors, warnings of each marco
  my $query = qq{select $QAMacros{macroName}, 
		        $QAMacros{status}, 
		        $QAMacros{warnings}, 
		        $QAMacros{errors}
                 from $dbQA.$QAMacros{Table}
		 where $QAMacros{qaID} = '$qaID' };
  
  my $sth = $dbh->prepare($query);
  $sth->execute;
  return $sth->fetchall_arrayref();
}

#===============================================================
# parse the dataset field for offline MC
# format: [collision]/[eventGen]/[details]/[eventType]/[geometry]/[junk]
#         e.g. auau200/venus412/default/b0_3/year_1b/hadronic_on

sub ParseDatasetMC{
  my $jobID = shift;

  my $query = qq{ select dataset 
		  from $dbFile.$FileCatalog
		  where jobID = '$jobID'
		  limit 1 };

  # retrieve the dataset
  my $dataset = $dbh->selectrow_array($query);
  
  my ($collisionType, $eventGen, $details, $eventType, $geometry, $junk)=
    split /\//, $dataset, 6;

  return ($collisionType, $eventGen, $details, $eventType, $geometry);
  
}

#==============================================================
# parse the dataset field for offline real
# format: [collisionType]/[geometry]/[eventType]

sub ParseDatasetReal{
  my $jobID = shift;

  my $query = qq{ select dataset 
		  from $dbFile.$FileCatalog
		  where jobID = '$jobID'
		  limit 1 };

  # retrieve the dataset
  my $dataset = $dbh->selectrow_array($query);

  # collisionType, geometry, eventType
  return split /\//, $dataset, 3;

}
#==============================================================

sub db_GetControlFile{
  my $jobID = shift;

  my $query = qq{select $QASum{controlFile} 
		 from $dbQA.$QASum{Table}
		 where $QASum{jobID} = '$jobID' };

  return $dbh->selectrow_array($query);
}
1;  
  
