#! /usr/bin/perl
# 
# utilities for database interface 
#
#=============================================================================
package QA_db_utilities;
#=============================================================================
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
	    $JobRelations $QASummaryTable $QAMacrosTable %QASum %QAMacros
	    $serverHost );

use strict;
1;
#============================================================================

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
# ($dbQA - set in DataClass_object...)

# table : 'QASummary' 
#         Contains the basic information about the qa status
#         
#         jobID       varchar(64)         not null,
#         report_key  varchar(64)         not null,
#         type        varchar(20)         not null,
#         QAdone      enum('Y','N')       not null default 'N',
#         QAok        enum('Y','N','n/a') not null default 'n/a',
#         QAdate      datetime            not null,
#         controlFile varchar(128)        not null default 'n/a',
#         insertTime  timestamp(10)       not null,
#         qaID        mediumint           not null auto_increment,
#                     primary key (qaID),
#                     index (jobID),
#                     index (type),
#                     index (QAok),
#                     index (QAdone)
#                     

# QASummary for offline now has one more field.
#         redone      smallint            not null default 0

# the QA summary table for online is slightly different...

#         report_key  varchar(64)         not null,
#         runID       int(11)             not null default 0,
#         detector    varchar(10)         not null
#         trigger     varchar(20)         not null,
#         createTime  datetime            not null,
#         QAdone      enum('Y','N')       not null default 'N',
#         QAok        enum('Y','N','n/a') not null default 'n/a',
#         QAdate      datetime            not null,
#         controlFile varchar(128)        not null default 'n/a',
#         insertTime timestamp(10)        not null,
#         qaID        mediumint           not null auto_increment,
#                     primary key (qaID),
#                     index (QAok),
#                     index (QAdone),
#                     index (trigger(10)),
#                     index (createTime),
#                     index (runID),
#                     index (detector(5))
#                     


# table : 'QAMacros'
#          
#          qaID       mediumint(9) not null, 
#          macroName  varchar(64)  not null,
#          fName      varchar(64)  not null,
#          path       varchar(128) not null,
#          extension  varchar(10)  not null,
#          size       int(11)      not null,
#          createTime datetime     not null,
#          status     varchar(20)  not null,
#          warnings   varchar(5)   not null,
#          errors     varchar(5)   not null, 
#          ID         mediumint(9) not null auto_increment, 
#                     primary key(ID),
#                     index (qaID),
#                     index (macroName),
#                     index (status),
#                     index (warnings),
#                     index (errors)


# database variables - just in case you want to change the column names
# sorry - columns for other databases are hard coded...

# QASummary table
%QASum = (
	 Table        => 'QASummary', # name of the table
	 jobID        => 'jobID',
	 redone       => 'redone',    # offline only
	 report_key   => 'report_key',
	 type         => 'type',      # type of data (real, MC)
	 QAdone       => 'QAdone',
	 QAok         => 'QAok',
	 QAdate       => 'QAdate',
	 controlFile  => 'controlFile',
	 qaID         => 'qaID',
         # the rest or only valid for online
	 trigger      => 'trigger',
	 runID        => 'runID',
	 createTime   => 'createTime',
	 detector     => 'detector'

	 );

# QAMacros
%QAMacros = (
	 Table      => 'QAMacros', # name of the table
	 qaID       => 'qaID',
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


#----------------------------------------------------------------------------

my $userFile = '/star/u2e/starqa/.my.cnf';
my %attr = (RaiseError =>1, PrintError =>0, AutoCommit => 1); 
# rely on this to catch errors

# Note: ALL DBI ERRORS ARE FATAL!

#----------
# connecting to $dbQA is arbitray.  just need to connect to 
# the mysql server

sub db_connect{

  SetDBVariables(); # depends on the data class

  my $datasource =
    "DBI:mysql:$dbQA:$serverHost;mysql_read_default_file=$userFile";

  my ($user_name, $password);

  $dbh = DBI->connect($datasource, $user_name, $password, \%attr)
    or die "Couldnt connect to $dbQA: $dbh->errstr";

  
}
#----------
#
sub db_disconnect{
  $dbh->disconnect or die "Couldnt disconnect from $dbQA";
}
#----------
# pmj 3/6/00 declare variables with file scope
# the names of the operations database, the qa database
# and the table names are set in the DataClass_object
#
sub SetDBVariables{
  
  $serverHost     = $gDataClass_object->MySQLHost();
  $dbFile         = $gDataClass_object->dbFile(); 
  $FileCatalog    = $gDataClass_object->FileCatalog(); 
  $JobStatus      = $gDataClass_object->JobStatus(); 
  $ProdOptions    = $gDataClass_object->ProdOptions();
  $JobRelations   = $gDataClass_object->JobRelations();
  $dbQA           = $gDataClass_object->dbQA();

}
#----------
# get the log file 
#
sub GetNightlyLogFile{
  my $jobID = shift;
  
  my $query = qq{select 
		 concat(path,'/',logFile)		 
		 from $dbFile.$JobStatus  
		 where jobID='$jobID' };
  
  return $dbh->selectrow_array($query);
}    
#----------
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

  $logfile =~ s|/sum/|/log/|g;   # change the path info
  $logfile =~ s/\.sum$/\.log/; # change the data type 

  return $logfile;
}    
#----------
# check if the various output files exist
# input is the jobID
# .dst.root, .hist.root, (flag if too small), .tags.root, .runco.root
# .geant.root,

sub GetMissingFiles{
  my $jobID = shift;
  my $type  = shift; # MC or real

  my ($missingFiles); # return the missing files as a string
  my $hist_size =  1000;

  # these are the file components we're looking for
  my @componentAry = qw(dst hist tags runco);
  
  my $ondiskString;

  # check for one more component 
  push @componentAry, 'geant' if $type eq 'MC';

  # general checking
  my $query =  qq{select distinct component 
		  from $dbFile.$FileCatalog 
	          where jobID='$jobID' 
		};

#  my $query2 = qq{select component
#		  from $dbFile.$FileCatalog 
#                  where jobID = '$jobID' and
#		        component='hist' and
#		        size > $hist_size };

  # retrieve components from output files from db
  my @outputComp = @{$dbh->selectcol_arrayref($query)};

  # construct 'seen' hash - see perl cookbook
  my %seen;
  @seen{ @outputComp } = ();

  # find missing files
  foreach ( @componentAry) {
    $missingFiles .= "$_.root" unless exists $seen{$_};
  } 
    
  return $missingFiles;
}
#----------
sub GetMissingFilesReal{
  my $jobID = shift;

  return GetMissingFiles($jobID, 'real');
}
#----------
sub GetMissingFilesMC{
  my $jobID = shift;

  return GetMissingFiles($jobID, 'MC');
}
#----------
# arguments : field      - this is what you want
#             report_key - where the 'report_key' matches this

sub GetFromQASum{
  my $field      = shift;
  my $report_key = shift;

  my $query = qq{select $field 
		 from  $dbQA.$QASum{Table} 
	         where $QASum{report_key}='$report_key'};

  return $dbh->selectrow_array($query);
}
#----------
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
#----------
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
#----------
# get output file of the job (dst.root) for offline and nightly

sub GetOutputFileOffline{
  my $jobID = shift;

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
#----------
# get output file of the job (dst.root) for offline and nightly
# path and name for nightly

sub GetOutputFileNightly{
  my $jobID = shift;

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
#----------
# returns the value from the '@field(s)' requested from FileCatalog
# that matches the '$jobID'

sub GetFromFileCatalog{
  my $field   = shift; # ref to an array or normal scalar
  my $jobID   = shift;

  my @fields;

  # add commas to a list
  if ( ref($field) ){
    @fields = join ',', @$field;
  }
  else{
    @fields = ($field); # just one field
  }

  my $query = qq{select @fields
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' limit 1};

  return $dbh->selectrow_array($query);
}
#----------
# returns the value from the '@field(s)' requested from JobStatus
# that matches the '$jobID'

sub GetFromJobStatus{
  my $field   = shift; # ref to an array or normal scalar
  my $jobID   = shift;
  
  my @fields;
  
  # add commas to a list
  if ( ref($field) ){
    @fields = join ',', @$field;
  }
  else{
    @fields = $field; # just one field
  }

  my $query = qq{select @fields 
		 from $dbFile.$JobStatus
		 where jobID = '$jobID'};
  
  return $dbh->selectrow_array($query);
}
#----------
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
#----------
# returns the input file name for offline

sub GetInputFnOffline{
  my $jobID = shift;

  my $query = qq{select inputFile 
		 from $dbFile.$JobRelations
                 where jobID = '$jobID' };

  return $dbh->selectrow_array($query);
}
#----------
# returns all production files for offline 

sub GetAllProductionFilesOffline{
  my $jobID     = shift;
  
  my $query = qq{select concat(path,'/',fName)
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' and
	               hpss = 'N'};

  return $dbh->selectcol_arrayref($query);

}
#----------
# returns  all production files for nightly 

sub GetAllProductionFilesNightly{
  my $jobID     = shift;
  
  my $query = qq{select concat(path,'/',fName)
		 from $dbFile.$FileCatalog
		 where jobID = '$jobID' and
	               avail = 'Y'};
 
  return $dbh->selectcol_arrayref($query);

}
#---------
# update QAsummary
# arguments: name of the field you want
#            value of the field you want to update,
#            qaID which matches the row
#
sub UpdateQASummary{
  my $field = shift;
  my $value = shift;
  my $qaID  = shift;

  my $query = qq{update $dbQA.$QASum{Table}
		 set $field='$value'
		 where $QASum{qaID} = '$qaID' };
  
  $dbh->do($query);
}
#----------
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
#----------
# clear the QAMacros table in db

sub ClearQAMacrosTable{
  my $qaID = shift;
 
  my $query = qq{delete from $dbQA.$QAMacros{Table}
		 where $QAMacros{qaID} ='$qaID'};

  print h4("Clearing macros from the database for qaID = $qaID...\n"); 
 
  $dbh->do($query);

  print h4("...done\n");
}
#----------
# 

sub WriteQASummary{
  my $qaStatus    = shift; # 0,1
  my $qaID        = shift;
  my $controlFile = shift;

  # the control file may be a symlink
  $controlFile = readlink $controlFile || $controlFile;
  
  # qa ok?
  my $QAok = $qaStatus ? 'Y' : 'N';
  
  # get current date
  my ($sec, $min, $hour, $day, $month, $year) = localtime;
  $year += 1900;  $month++;
  my $datetime = "$year-$month-$day $hour:$min:$sec";

  my $query = qq{update $dbQA.$QASum{Table} 
	      set 
		$QASum{QAdone}      ='Y', 
		$QASum{QAok}        ='$QAok', 
		$QASum{QAdate}      = '$datetime',
		$QASum{controlFile} = '$controlFile'
	      where $QASum{qaID} ='$qaID'};

  print h4("Writing overall QA summary into db...\n");

  $dbh->do($query) or die "$query";

  print h4("...done\n");
}

#-----------
# write the QA macro summary into the db.
# whether it crashed, errors, warnings, etc.

sub WriteQAMacroSummary{
  my $qaID      = shift; # needs the jobID from QA_object
  my $report_obj = shift; # QA_report_object
  my $option     = shift; # evaluate_only

  my ($status, $errors, $warnings, $nError, $nWarn);
  my $qaStatus = 1; # default is that everything's a-ok

  # macro output info
  my $outputFile = $report_obj->IOMacroReportFilename->Name;
  $outputFile =~ s/ps$/ps\.gz/; # assume ps changed to ps.gz...

  my $macroName  = $report_obj->MacroName;
  my $fName       = basename($outputFile);
  my $path        = dirname($outputFile);
  my ($junk, $extension) = split /\./, $fName, 2;

  my ($size, $createTime_epoch, $createTime);

  # get out if evaluate only and no test were defined
  if ($option =~ /evaluate_only/ and $report_obj->NTests==0){
    print h4("No tests were defined\n");
    return;
  }

  # check that the output file exists
  
  if ( -e $outputFile) 
  {
    $size             = stat($outputFile)->size;
    $createTime_epoch = stat($outputFile)->mtime;
  } 
  else 
  { # doesnt exist - keep the extention though...
    $fName      = "n/a";
    $size       = "n/a";
    $path       = "n/a";
  }

  # -- fill in QA status for the macro--
  my $rootcrashlog = $report_obj->IORootCrashLog->Name;
  
   # check for root crash
  if (-s $rootcrashlog)
  {
    $status    = "crashed";
    $errors    = "n/a";
    $warnings  = "n/a";
    $qaStatus  = 0;
  }
  # check if the macro was actually run
  # look for output file - maybe the input file didnt exist
  elsif (not -e $outputFile)
  {
    $status     = "not run";
    $errors     = "n/a";
    $warnings   = "n/a";
    $qaStatus  = 0;
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

      my @testNameList = $report_obj->TestNameList($type);
    
      # loop over each test 
      foreach my $testName (@testNameList){
	$nError += $report_obj->Nerror($type,$testName);
	$nWarn  += $report_obj->Nwarn($type,$testName);
      }
      
    }
    # adjust if more than 10 warnings
    $status   = "finished";
    $errors   = ($nError > 10) ? ">10" : $nError;
    $warnings = ($nWarn > 10) ? ">10" : $nWarn;
    
    ($errors or $warnings) and $qaStatus = 0;
  }

  my $query;

  # convert createTime_epoch 
  if (defined $createTime_epoch){
    my ($sec, $min, $hour, $day, $month, $year) = localtime($createTime_epoch);
    $year += 1900; $month++;
    $createTime = "$year-$month-$day $hour:$min:$sec";
  }
 
  # only re-evaluating, update table
  if ($option =~ /evaluate_only/ )
  {
    $query = 
      qq{update $dbQA.$QAMacros{Table}
	 set
	   $QAMacros{status}     = '$status',
           $QAMacros{warnings}   = '$warnings',
           $QAMacros{errors}     = '$errors'
	 where $QAMacros{macroName} = '$macroName' and
	       $QAMacros{fName}     = '$fName' and
	       $QAMacros{qaID}      = '$qaID'};
  }
  else
  { # new macros... insert into table
    $query = 
      qq{insert into $dbQA.$QAMacros{Table}
	 set
	   $QAMacros{qaID}      = '$qaID',
	   $QAMacros{macroName}  = '$macroName',
	   $QAMacros{fName}      = '$fName',
           $QAMacros{path}       = '$path',
           $QAMacros{extension}  = '$extension',
           $QAMacros{size}       = '$size',
           $QAMacros{createTime} = '$createTime',
           $QAMacros{status}     = '$status',
           $QAMacros{warnings}   = '$warnings',
           $QAMacros{errors}     = '$errors',
	   $QAMacros{ID}         = NULL 
	 };
  }
  print h4("Inserting qa macro summary into db for $fName ($macroName)...\n");

  # insert
  my $rows = $dbh->do($query);

  if ($rows += 0) { print h4("...done\n")}
  else     { print h4("<font color = red> Error. Cannot insert qa info for ",
		      "$outputFile</font>"); return;}
    
  return $qaStatus;
}
#----------
# get overall qa summary

sub GetQASummary{
  my $qaID = shift;

  # get QAdone, QAdate,  
  my $query = qq{select $QASum{QAdone}, $QASum{QAdate}
                 from $dbQA.$QASum{Table}
                 where $QASum{qaID} = '$qaID' };

  my ($QADone, $QADate) = $dbh->selectrow_array($query);
  
  $QADone = ($QADone eq 'Y') ? 1 : 0;

  return ($QADone, $QADate);

}
#----------
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
#----------
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
#----------
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
#----------
# 1. deletes the 'old' reports from the databasee
# 2. returns the report keys so that we can delete it from disk

sub GetOldReports{
  my $data_type = shift; # MC or real

  my $old_time  = 5;   # number of days
  my $now       = time;  # current date in epoch seconds
  my @old_report_keys;

  # determine which reports are old from th e FileCatalog.createTime
  my $query_old = qq{ select distinct qa.$QASum{report_key},
			     qa.$QASum{qaID}
		      from $dbQA.$QASum{Table} as qa,
		           $dbFile.$FileCatalog as file  
		      where  
			qa.$QASum{jobID} = file.jobID and
			(to_days(from_unixtime($now)) -
			 to_days(file.createTime)) > $old_time and
			qa.$QASum{type} = '$data_type'
		      };
  # delete from QASummary
  my $query_delete_sum = qq{ delete from $QASum{Table} 
			     where $QASum{report_key} = ? };

  # delete from QAMacros
  my $query_delete_macro = qq{ delete from $QAMacros{Table}
			       where $QAMacros{qaID} = ? };

  my $sth_old          = $dbh->prepare($query_old);
  my $sth_delete_sum   = $dbh->prepare($query_delete_sum);
  my $sth_delete_macro = $dbh->prepare($query_delete_macro);

  $sth_old->execute;

  while(my ($report_key, $qaID) = $sth_old->fetchrow_array){
    push @old_report_keys, $report_key; # save it

    print h4("Deleting $report_key from $QASum{Table} ...\n");
    #$sth_delete_sum->execute($report_key);  # delete it

    print h4("Deleting $report_key from $QAMacros{Table} ...\n");
    #$sth_delete_macro->execute($qaID);

    print h4("... done<br>\n");
  }
  
  return @old_report_keys;
}
#----------
sub GetOldReportsReal{
  return GetOldReports('real');
}
#----------
sub GetOldReportsMC{
  return GetOldReports('MC');
}

    

1;  
  
