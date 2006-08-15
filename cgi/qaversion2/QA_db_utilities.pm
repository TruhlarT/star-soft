#! /opt/star/bin/perl
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
		    $joinField
		    %QASum
		    %QAMacros
		    %DAQInfo
		   );

@EXPORT_OK   = @db_globals;
%EXPORT_TAGS = ( db_globals => [ @db_globals] );


use vars qw($dbh $dbQA $dbFile $JobStatus $ProdOptions $FileCatalog
	    $JobRelations $QASummaryTable $QAMacrosTable %QASum %QAMacros
	    $serverHost %DAQInfo $joinField);

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
#         QAanalyzed  enum('Y','N')       not null default 'N',
#         QAdone      enum('Y','N','in progress') not null default 'N',
#         QAok        enum('Y','N','n/a') not null default 'n/a',
#         QAdate      datetime            not null,
#         reference   enum('Y','N')       not null default 'N',
#         controlFile varchar(128)        not null default 'n/a',
#         insertTime  timestamp(10)       not null,
#         qaID        mediumint           not null auto_increment,
#                     primary key (qaID),
#                     unique (jobID),
#                     index (type),
#                     index (QAok),
#                     index (QAdone),
#                     index (report_key)
#                     

# QASummary for PRODUCTION (offline) now has two more fields
#         redone      smallint            not null default 0
#         skip        enum('Y','N')       not null default 'Y'

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
	 skip         => 'skip',      # offline only
	 QAanalyzed   => 'QAanalyzed',
	 QAdone       => 'QAdone',
	 QAok         => 'QAok',
	 QAdate       => 'QAdate',
	 reference    => 'reference',
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

# DAQInfo
%DAQInfo = (
	    Table       => 'DAQInfo',
	    file        => 'file',
	    runNumber   => 'runNumber',
	    numEvt      => 'NumEvt',
	    beginEvt    => 'BeginEvt',
	    endEvt      => 'EndEvt',
	    current     => 'Current',
	    scaleFactor => 'scaleFactor',
	    beamE       => 'beamE',
	    collision   => 'collision',
	    detSetMask  => 'DetSetMask',
	    status      => 'status'
);
	    
	    

#----------------------------------------------------------------------------

my $userFile2  = '/star/u2e/starqa/.my.cnf';
my $userFile = '/afs/rhic.bnl.gov/star/starqa/qa01/.my.cnf';
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

  eval {
    $dbh = DBI->connect($datasource, $user_name, $password, \%attr);   
  };
  if ($@) {
    $datasource ="DBI:mysql:$dbQA:$serverHost;mysql_read_default_file=$userFile2";
    $dbh =  DBI->connect($datasource, $user_name, $password, \%attr);
    defined $dbh or die "Oh well: $DBI::errstr\n";
  }

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
  $joinField      = $gDataClass_object->joinField();
}
#----------
# get the log file 
#
sub GetNightlyLogFile{
  my $jobID = shift;
  
  return GetFromJobStatus("concat(path,'/',logFile)", $jobID);
}    
#----------
# get the log file for offline

sub GetOfflineLogFile{
  my $jobID = shift;

  my $logfile = GetFromJobStatus("concat(sumFileDir,'/',sumFileName)", $jobID);
   
  # change to the actual logfile
  # e.g. /star/rcf/disk00001/star/P00hd/sum/daq/st_physics_1166036_raw_0002.sum
  #

  $logfile =~ s|/sum/|/log/|g;   # change the path info
  $logfile =~ s/\.sum$/\.log/; # change the data type 

  return $logfile;
}    
#----------
# check if the root files are too small

sub GetSmallFiles{
  my $jobID = shift;
  my $type  = shift;
  my $size  = 1000;
  my $smallstring;
  my $query = qq{ select distinct component
                  from $dbFile.$FileCatalog 
		  where jobID = '$jobID' and
		  size < $size and
		};

  if ($type eq 'nightly'){
    $query .= qq{avail = 'Y'};
  }
  elsif($type eq 'offline'){
    $query .= qq{hpss = 'N'};
  }
  
  my $sth = $dbh->prepare($query);
  $sth->execute();

  while (my ($component) = $sth->fetchrow_array()){
    $smallstring .= "$component.root<br>";
  }
  
  return $smallstring;
}
#---------
sub GetSmallFilesOffline{
  my $jobID = shift;
  return GetSmallFiles($jobID,'offline');
}
sub GetSmallFilesNightly{
  my $jobID = shift;
  return GetSmallFiles($jobID,'nightly');
}
#---------
# check if the various output files exist
# input is the jobID
# .dst.root, .hist.root, (flag if too small), .tags.root, .runco.root
# .geant.root,

sub GetMissingFiles{
  my $jobID = shift;
  my $mc    = shift; # 0,1
  my $offline = shift; # 0,1

  my ($missingFiles); # return the missing files as a string
  my $hist_size =  1000;

  # these are the file components we're looking for
  my @componentAry = qw(event hist tags runco);

  # check for one more component 
  push @componentAry, 'geant' if $mc;

  # quick fix
  my @outputComp;
  if ($offline){
    @outputComp = GetFromFileOnDiskOffline('component',$jobID);
  }
  else{
    @outputComp = GetFromFileOnDiskNightly('component',$jobID);
    push @componentAry, 'dst';
  }

  # construct 'seen' hash - see perl cookbook
  my %seen;
  @seen{ @outputComp } = ();

  # find missing files
  foreach ( @componentAry) {
    $missingFiles .= "$_.root<br>" unless exists $seen{$_};
  } 
    
  return $missingFiles;
}

#----------
# check if files are on disk

sub OnDiskNightly{
  my $jobID =  shift;

  return defined GetFromFileOnDiskNightly('ID', $jobID);

}
#----------
# check if files are on disk

sub OnDiskOffline{
  my $jobID =  shift;

  return defined GetFromFileOnDiskOffline('ID', $jobID);
}
#----------
sub GetOneRowFromTable{
  my $field = shift;
  my $table = shift;
  my $where = shift;

  my @fields;
  
  # add commas to a list
  if ( ref($field) ){
    @fields = join ',', @$field;
  }
  else{
    @fields = $field; # just one field
  }

  my $query = qq{select @fields 
		 from $table
		 where $where
	       };

  return $dbh->selectrow_array($query);
  
}

#----------
# returns the value from the '@field(s)' requested from FileCatalog
# that matches the '$jobID'

sub GetFromFileCatalog{
  my $field   = shift; # ref to an array or normal scalar
  my $jobID   = shift;

  my $where_clause = "$joinField = '$jobID' limit 1";

  return GetOneRowFromTable($field,"$dbFile.$FileCatalog",$where_clause);
}

#----------
# returns the value from the '@field(s)' requested from JobStatus
# that matches the '$jobID'

sub GetFromJobStatus{
  my $field   = shift; # ref to an array or normal scalar
  my $jobID   = shift;
  
  my $where_clause = "jobID = '$jobID'";

  return GetOneRowFromTable($field,"$dbFile.$JobStatus",$where_clause);

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
# can get multiple rows or one row from table but just one column
#
sub GetRowsFromTable{
  my $field = shift;
  my $table = shift;
  my $where = shift;

  my $query = qq{select $field 
		 from $table
		 where $where
	       };
  return wantarray ? @{$dbh->selectcol_arrayref($query)}
                   : $dbh->selectrow_array($query);
}

#----------
# only one select field, but can return an array of rows matched
#
sub GetFromFileOnDiskNightly{
  my $field = shift;
  my $jobID = shift;
  my $where = "jobID = '$jobID' and avail='Y'";

  return GetRowsFromTable($field,"$dbFile.$FileCatalog",$where);
}
#----------
# ony one select field, but can return an array of rows matched
#
sub GetFromFileOnDiskOffline{
  my $field = shift;
  my $jobID = shift;
  my $where = "jobID = '$jobID' and hpss='N'";

  return GetRowsFromTable($field,"$dbFile.$FileCatalog",$where);
}

#----------
# arguments : field      - this is what you want
#             report_key - where the 'report_key' matches this

sub GetFromQASum{
  my $field      = shift;
  my $report_key = shift;
  my $where = "$QASum{report_key}='$report_key'";

  return GetOneRowFromTable($field,"$dbQA.$QASum{Table}",$where);
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
  
  return $dbh->do($query);
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
  if(-e $report_dir){
     rmdir $report_dir or warn "Could not remove $report_dir :$!";
  }
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
sub FlagQAInProgress{
  my $qaID = shift;
  return UpdateQASummary($QASum{QAdone},'in progress', $qaID);
}
#----------
#
sub FlagQADone{
  my $qaID = shift;
  return UpdateQASummary($QASum{QAdone},'Y',$qaID);
}
#----------
#
sub ResetInProgressFlag{
  my $qaID = shift;
  return UpdateQASummary($QASum{QAdone}, 'N', $qaID);
}
#----------
# 
sub FlagQAAnalyzed{
  my $qaID = shift;
  my $value = shift;
  return UpdateQASummary($QASum{QAanalyzed},$value,$qaID);
}
#----------
#
sub ResetQANotDone{

  my $query = qq{ select $QASum{qaID}, $QASum{report_key}
		  from   $QASum{Table}
		  where  $QASum{QAdone} = 'in progress'
		};

  my $sth = $dbh->prepare($query);
  $sth->execute();

  while (my ($qaID, $report_key) = $sth->fetchrow_array){
    print "Resetting flag for report key = $report_key<br>\n";
    UpdateQASummary($QASum{QAdone},'N', $qaID);
  }
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
  my $QAok = ($qaStatus>0) ? 'Y' : 'N';
  
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

  print h4("<font color=blue>",
	   "Writing overall QA summary into db...\n",
	   "<br>QAok is $QAok</font>\n");

  $dbh->do($query) or die "$query";

  print h4("<font color=blue>...done</font>\n");
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
    return 1;
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
  elsif (not -s $outputFile)
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
    
    #($errors or $warnings) and $qaStatus = 0;
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

  my $statusTitle = $qaStatus ? "good" : "bad";
  print h4("<font color=blue>",
	   "Inserting qa macro summary into db for $fName ($macroName)...",
	   "<br>qa status is $statusTitle",
	   "</font>\n");

  
  # insert
  my $rows = $dbh->do($query);

  # 0 rows affected is ok.  $rows = undef is bad.
  if (defined $rows) { print h4("<font color=blue>...done</font>\n")}
  else     { print h4("<font color = red> Error. Cannot insert qa info for ",
		      "$outputFile</font>"); return;}
    
  return $qaStatus;
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
# 1. deletes the 'old' reports from the databasee
# 2. returns the report keys so that we can delete it from disk

sub GetOldReports{
  my $data_type = shift; # MC or real
  
  my $old_time  = shift || 5;   # number of days
  my $now       = time;  # current date in epoch seconds
  my @old_report_keys;

  print "GetOldReports($data_type, $old_time)\n";

  # determine which reports are old from the FileCatalog.createTime
#  my $query_old = qq{ select distinct qa.$QASum{report_key}, qa.$QASum{qaID}
#		      from $dbQA.$QASum{Table} as qa,
#		      $dbFile.$FileCatalog as file  
#			  where  
#			      qa.$QASum{jobID} = file.jobID and
#			(to_days(from_unixtime($now)) -
#			 to_days(file.createTime)) > $old_time and
#			qa.$QASum{type} = '$data_type'
#		      };

  # determine which reports are old from the QA insert time
  my $query_old = qq{ select distinct qa.$QASum{report_key}, qa.$QASum{qaID}
		      from $dbQA.$QASum{Table} as qa
			  where 
			      (to_days(from_unixtime($now)) -
			       to_days(qa.insertTime)) > $old_time and
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

  my $rc;
  while(my ($report_key, $qaID) = $sth_old->fetchrow_array){
    push @old_report_keys, $report_key; # save it

    print "Deleting $report_key from $QASum{Table} ...<br>\n";
    $rc = $sth_delete_sum->execute($report_key);  # delete it
    print "Uh oh. could not delete\n" unless ($rc+=0);

    print "Deleting $report_key from $QAMacros{Table} ...<br>\n";
    $sth_delete_macro->execute($qaID);

    print "... done<br>\n";
  }
  
  return @old_report_keys;
}
#----------
sub GetOldReportsReal{
  return GetOldReports('real', shift);
}
#----------
sub GetOldReportsMC{
  return GetOldReports('MC', shift);
}

    

1;  
  
