#! /usr/bin/perl
# 
# utilities for the database and the selection menu
# all utilities are used only in the KeyList_object
# and all its derived classes
#
#===================================================================
package Db_KeyList_utilities;
#===================================================================
use CGI qw/:standard :html3/;

use DBI;
use Time::Local;
use QA_globals;
use QA_db_utilities qw(:db_globals); # import db handle and tables

use strict qw(vars subs);

#========================================================================
# get values for dataset selection menu for offline db
# argument is real or MC

sub GetOfflineSelections{
  my $argument = shift;      # real or MC

  my $hashref;               # stores all the selections
  my $now      = time;       # what time is it?
  my $time_sec = 14*24*3600; # 2 weeks

  my $file_type;

 SWITCH:{
    $argument eq 'real' and do{$file_type = 'real';   last; };
    $argument eq 'MC'   and do{$file_type = 'MC'; last; };
    # default
    die "Wrong argument";
  }
  
  # library selections

  my $query_library = qq{select distinct job.prodSeries, job.chainName
			 from $dbFile.$JobStatus as job,
			      $dbQA.$QASum{Table} as s
			 where job.jobID       = s.$QASum{jobID} and
			       s.$QASum{type} = '$file_type'
			 order by job.prodSeries asc};
  

  # run id
  my $query_runID = qq{select distinct file.runID
		       from $dbFile.$FileCatalog as file,
			    $dbQA.$QASum{Table} as s
		       where file.jobID = s.$QASum{jobID} and
			     ($now-unix_timestamp(createtime))>0 and
			     s.$QASum{type} = '$file_type'
		       order by file.runID asc};

  # QA macros
  my $query_QAmacros = qq{select distinct m.$QAMacros{macroName}
			  from $dbQA.$QAMacros{Table} as m,
			       $dbQA.$QASum{Table} as s
			  where 
			        m.$QAMacros{qaID} = s.$QASum{qaID} and
			        m.$QAMacros{extension}!='ps' and
			        m.$QAMacros{extension}!='ps.gz' and
				s.$QASum{type}     = '$file_type'           
			  order by m.$QAMacros{macroName} asc};

  # dataset 
  my $query_dataset = qq{select distinct file.dataset
			 from $dbFile.$FileCatalog as file,
			   $dbQA.$QASum{Table} as s
			 where file.jobID      = s.$QASum{jobID} and
			       s.$QASum{type} = '$file_type'
			 order by file.dataset asc };
  
  my $sth;

  # get prodOptions
  $sth = $dbh->prepare($query_library);
  $sth->execute;

  while (my ($prodSeries, $chainName) = $sth->fetchrow_array) {
    push( @{$hashref->{prodOptions}->{$prodSeries}}, $chainName );
  }

  # get run id
  $sth = $dbh->prepare($query_runID);
  $sth->execute;

  while ( my $runID = $sth->fetchrow_array ) {
    push( @{$hashref->{runID}}, $runID );
  }
  
  # dataset
  $sth = $dbh->prepare($query_dataset);
  $sth->execute;
  while ( my $dataset = $sth->fetchrow_array ) {
    push (@{$hashref->{dataset}}, $dataset);
  }

  # get macro names
  $sth = $dbh->prepare($query_QAmacros);
  $sth->execute;
  while (my $macro_name = $sth->fetchrow_array ){
    push( @{$hashref->{macroName}}, $macro_name );
  }
  
  return $hashref;
			 
} 
#========================================================================
# get values for dataset selection menu for offline real

sub GetOfflineSelectionsReal{
  return GetOfflineSelections('real');
}

#========================================================================
# get values for dataset selection menu for offline MC

sub GetOfflineSelectionsMC{
  return GetOfflineSelections('MC');
}

#========================================================================
# get values for dataset selection menu for nightly tests
# see KeyList_object

sub GetNightlySelections{
  my $data_type = shift; # real or MC


  my ($query_eventGen, $query_eventType, $file_type);

  # different queries for different class of data
  if ($data_type eq 'MC')
  {
    $query_eventGen  = qq{select distinct eventGen
		          from $dbFile.$FileCatalog
			  where eventGen !='n/a/'
			  order by eventGen};

    $query_eventType = qq{select distinct eventType
		          from $dbFile.$FileCatalog
                          where eventType!='n/a' 
                          order by eventType};
    $file_type = 'MC';
    
  }
  elsif ($data_type eq 'real')  
  {
    $query_eventGen  = qq{select ID
			  from $dbFile.$FileCatalog
                          where 1<0}; # dummy query
    
    # only want event types where the event gen is not applicable
    $query_eventType = qq{select distinct eventType
		         from $dbFile.$FileCatalog
                         where eventType!='n/a' and
			       eventGen = 'n/a'
			 order by eventType};
    $file_type = 'real';

  }
  else {die "Wrong data type $data_type"};

  # other queries...

  my $query_library   = qq{select distinct LibTag
		         from $dbFile.$FileCatalog 
			 where LibTag!='n/a'
                         order by LibTag};
  my $query_platform  = qq{select distinct platform
		          from $dbFile.$FileCatalog 
			  where platform!='n/a'
                          order by platform};
  
  my $query_geometry  = qq{select distinct geometry
		         from $dbFile.$FileCatalog 
			 order by geometry};

  my $query_QAmacros = qq{select distinct m.$QAMacros{macroName}
			  from $dbQA.$QAMacros{Table} as m,
			       $dbQA.$QASum{Table} as s
			  where 
			        m.$QAMacros{qaID} = s.$QASum{qaID} and 
			        s.$QASum{type}    = '$file_type' and 
			        m.$QAMacros{extension}!='ps' and
                                m.$QAMacros{extension}!='ps.gz'
			  order by m.$QAMacros{macroName} asc};

  my ($hashref, $row, $sth);

  # get the eventGen (maybe)
  $sth = $dbh->prepare($query_eventGen);
  $sth->execute;
    
  push( @{$hashref->{eventGen}}, $row ) 
    while ( $row = $sth->fetchrow_array );

  # get library version
  $sth = $dbh->prepare($query_library);
  $sth->execute;
  
  push( @{$hashref->{LibTag}}, $row ) while ( $row = $sth->fetchrow_array );

  # get machine info
  $sth = $dbh->prepare($query_platform);
  $sth->execute;

  push( @{$hashref->{platform}}, $row ) while ( $row = $sth->fetchrow_array );

  # get eventType info
  $sth = $dbh->prepare($query_eventType);
  $sth->execute;

  push( @{$hashref->{eventType}}, $row ) while ( $row = $sth->fetchrow_array );

  # get geometry info
  $sth = $dbh->prepare($query_geometry);
  $sth->execute;

  push( @{$hashref->{geometry}}, $row ) while ( $row = $sth->fetchrow_array );

  # get macro names
  $sth = $dbh->prepare($query_QAmacros);
  $sth->execute;

  push (@{$hashref->{macroName}},$row ) while ( $row = $sth->fetchrow_array );

  return $hashref;
}
#========================================================================
# get possible values for dataset selection menu for real nightly tests
# 

sub GetNightlySelectionsReal{
  return GetNightlySelections('real');
}

#========================================================================
# get possible values for dataset selection menu for MC nightly tests
# 

sub GetNightlySelectionsMC{
  return GetNightlySelections('MC');
}



#=======================================================================
# get the QA report keys according to selection query
# see KeyList_object

sub GetOfflineKeys{
  my $data_type     = shift; # real or MC
  my $prodOptions   = shift; # e.g. "$prodSeries;$chainName"
  my $runID         = shift; # e.g. 124
  my $QAstatus_arg  = shift; # e.g. "warnings;$macro_name" or "ok"
  my $jobStatus     = shift;
  my $createTime    = shift; 
  my $dataset       = shift;

  my $limit = 50; # dont want to get a million of them

  print "data_type = $data_type<br>",
        "prodOptions = $prodOptions<br>",
        "runID       = $runID<br>",
        "jobStatus   = $jobStatus<br>";



  # which class of data are we looking at?
  my $data_type_string;
  if ($data_type eq 'real')
  {
    $data_type_string = "sum.$QASum{type} = 'real' and";
  }
  elsif ($data_type eq 'MC')
  {
    $data_type_string = "sum.$QASum{type} = 'MC' and";
  }
  else {die "Wrong data_type $data_type"; }
  

  # fine tune prodOptions
  my ($prodSeries, $chainName) = split( /;/, $prodOptions );
  
  # fine tune status
  my ($QAstatus, $macro_name)  = split( /;/, $QAstatus_arg );

  #----
  # selection strings...
  # determine which tables to join
  my ($file_from_string, $job_from_string);
  my ($file_where_string, $job_where_string);

  # --- from cpFileCatalog ---
  my ($runID_string, $dataset_string, $createTime_string);

  if ($runID ne 'any' or $createTime ne 'any' or $dataset ne 'any') 
  {  
    # include this in the from clause
    $file_from_string = ",$dbFile.$FileCatalog as file";
    
    # where clause
    $file_where_string = "sum.jobID = file.jobID and";

    # runID string
    $runID_string = "file.runID = '$runID' and" 
      if $runID ne 'any';

    # dataset string
    $dataset_string = "file.dataset = '$dataset' and"
      if $dataset ne 'any';
    
    # create time string
    if ($createTime ne 'any') {
      my $now = time;
      my $three_days    = 3600*24*3;
      my $seven_days    = 3600*24*7;
      my $fourteen_days = 3600*24*14;
      my $time_sec;
      # cant get the stupid soft refs to work...
      
      $time_sec = $three_days if $createTime eq 'three_days';
      $time_sec = $seven_days if $createTime eq 'seven_days';
      $time_sec = $fourteen_days if $createTime eq 'fourteen_days';
      
      $createTime_string  = 
	" ($now-unix_timestamp(file.createTime))< $time_sec and";
    }
  }
  
  # --- from cpJobStatus ---
  my ($prod_string, $chain_string, $jobStatus_string);
 
  if ($jobStatus ne 'any' or $prodSeries ne 'any' ) 
  {  
    # include this in the from clause
    $job_from_string  = ",$dbFile.$JobStatus as job";
   
    # where clause
    $job_where_string = "sum.jobID = job.jobID and";

    # prod string
    $prod_string = "job.prodSeries = '$prodSeries' and"
      if $prodSeries ne 'any';

    # chain string
    $chain_string = "job.chainName = '$chainName' and"
      if defined $chainName;

    # jobStatus string
    if ($jobStatus eq 'done' ){ 
      $jobStatus_string = "job.jobStatus ='done' and";
    }
    if ($jobStatus eq 'not_done'){
      $jobStatus_string = "job.jobStatus !='done' and";
    }
  }
  #--- QA status ---
  # $QAstatus_string must be the last line in the 'where' clause
  # used when no warnings or errors are specified
  my ($QAstatus_string, $macro_string);
  my ($macro_where_string, $macro_from_string);

  if ($QAstatus ne 'any')
  {
    if ($QAstatus ne 'warnings' and $QAstatus ne 'errors')
    { # dont need to join with macros table
      
      $QAstatus_string = "sum.$QASum{QAok}='Y'"   if $QAstatus eq 'ok';
      $QAstatus_string = "sum.$QASum{QAok}='N'"   if $QAstatus eq 'not_ok';
      $QAstatus_string = "sum.$QASum{QAdone}='Y'" if $QAstatus eq 'done';
      $QAstatus_string = "sum.$QASum{QAdone}='N'" if $QAstatus eq 'not_done';
    }
    elsif ($QAstatus eq 'warnings' or $QAstatus eq 'errors')
    { # need to join macros table

      $macro_from_string  = ",$dbQA.$QAMacros{Table} as macro ";
      $macro_where_string = "sum.$QASum{qaID} = macro.$QAMacros{qaID} and";

      $QAstatus_string = "macro.$QAstatus!='0' and macro.$QAstatus!='n/a'";
      $macro_string = "macro.$QAMacros{macroName} = '$macro_name' and"
	if defined $macro_name;
    }
    else {die "Wrong argument $QAstatus"}
  }
  else { $QAstatus_string = "1>0";}
  
  my $query = qq{select distinct sum.$QASum{report_key}
		 from $dbQA.$QASum{Table} as sum
		      $macro_from_string
		      $job_from_string
		      $file_from_string
		where 
		      $macro_where_string
		      $job_where_string
		      $file_where_string
		      $prod_string
		      $chain_string
		      $runID_string
		      $jobStatus_string
		      $createTime_string
		      $dataset_string
		      $data_type_string
		      $macro_string
		      $QAstatus_string
		limit $limit };

  print $query; # debugging

  my $sth = $dbh->prepare( $query );
  $sth->execute;
  
  my @report_keys;

  while ( my $key = $sth->fetchrow_array){
    push @report_keys, $key;
  }

  return @report_keys;
}
#=======================================================================
# get offline selected keys for real jobs only

sub GetOfflineKeysReal{
  my @selection_param = @_;

  return GetOfflineKeys('real',@selection_param);
}

#=======================================================================
# get offline selected keys for MC jobs only

sub GetOfflineKeysMC{
  my @selection_param = @_;

  return GetOfflineKeys('MC',@selection_param);
}

			  
#=======================================================================
# get the QA report keys for nightly test 
# see KeyList_object

sub GetNightlyKeys{
  my $data_type     = shift; # real or MC
  my $eventGen      = shift;
  my $LibTag        = shift;
  my $platform      = shift;
  my $eventType     = shift;
  my $geometry      = shift;
  my $QAstatus_arg  = shift;
  my $ondisk        = shift;
  my $jobStatus     = shift;
  my $createTime    = shift; 

  my $limit = 50; # limit the query
  
  # fine tune status
  my ($QAstatus, $macro_name) = split( /;/, $QAstatus_arg);

  # --- determine which tables to join ---
  my ($file_from_string, $file_where_string);
  my ($job_from_string, $job_where_string);

  # --- file catalog ---
  my ($LibTag_string, $platform_string, $eventType_string,
      $geometry_string, $ondisk_string, $createTime_string);

  if ($eventGen  ne 'any' or
      $LibTag    ne 'any' or 
      $platform  ne 'any' or
      $eventType ne 'any' or
      $geometry  ne 'any' or
      $ondisk    ne 'any'     )
  {
    $file_from_string  = ",$dbFile.$FileCatalog as file";
    $file_where_string = "sum.jobID = file.jobID and";

    # any or not any?
    $LibTag_string    = "file.LibTag = '$LibTag' and"
      if $LibTag ne 'any';
    $platform_string  = "file.platform = '$platform' and"
      if $platform ne 'any';
    $eventType_string = "file.eventType = '$eventType' and"
      if $eventType ne 'any';
    $geometry_string  = "file.geometry = '$geometry' and"
      if $geometry ne 'any';
  
    # ondisk?
    if ($ondisk ne 'any') {
      if ($ondisk eq 'on_disk')
      {
	$ondisk_string = "file.avail = 'Y' and";
      }
      elsif ($ondisk eq 'not_on_disk') 
      {
	$ondisk_string = "file.avail = 'N' and";
      }
      else{ die "Wrong argument for on_disk";}
    }

    # when was the job created?
    if ($createTime ne 'any'){
      # create time string
      my $now = time;
      my $three_days    = 3600*24*3;
      my $seven_days    = 3600*24*7;
      my $fourteen_days = 3600*24*14;

      my $time_sec;
      $time_sec = $three_days if $createTime eq 'three_days';
      $time_sec = $seven_days if $createTime eq 'seven_days';
      $time_sec = $fourteen_days if $createTime eq 'fourteen_days';
      
      $createTime_string  = 
	" ($now-unix_timestamp(file.createTime))< $time_sec and ";
    }
  }

  # --- job status info ---
  # only join with jobStatus if client queries jobStatus
  my ($jobStatus_string);

  if ($jobStatus ne 'any')
  {
    $job_from_string  = ",$dbFile.$JobStatus as job";
    $job_where_string = "sum.jobID = job.jobID and ";

    # jobStatus string
    if ($jobStatus eq 'done' ){ 
      $jobStatus_string = "job.jobStatus ='done' and";
    }
    if ($jobStatus eq 'not_done'){
      $jobStatus_string = "job.jobStatus !='done' and";
    }
  }
    
  # for eventGen, if real we dont need to query on it
  # data_type_string takes care of selecting on real vs MC
  
  # which class of data are we looking at?
  my ($data_type_string, $eventGen_string);

  if ($data_type eq 'real')
  {
    $data_type_string = "sum.$QASum{type} = 'real' and";
  }
  elsif ($data_type eq 'MC')
  {
    $data_type_string = "sum.$QASum{type} = 'MC' and";

    # want specific event gen info if ne 'any'
    $eventGen_string  = "file.eventGen = '$eventGen' and"
      if $eventGen ne 'any';
  }
  else {die "Wrong data_type $data_type"; }
 
  
  # $QAstatus_string must be the last line in the 'where' clause
  # used when no warnings or errors are specified
  my ($QAstatus_string, $macro_string);
  my ($macro_where_string, $macro_from_string);

  if ($QAstatus ne 'any')
  {
    if ($QAstatus ne 'warnings' and $QAstatus ne 'errors')
    { # dont need to join with macros table
      
      $QAstatus_string = "sum.$QASum{QAok}='Y'"   if $QAstatus eq 'ok';
      $QAstatus_string = "sum.$QASum{QAok}='N'"   if $QAstatus eq 'not_ok';
      $QAstatus_string = "sum.$QASum{QAdone}='Y'" if $QAstatus eq 'done';
      $QAstatus_string = "sum.$QASum{QAdone}='N'" if $QAstatus eq 'not_done';
    }
    elsif ($QAstatus eq 'warnings' or $QAstatus eq 'errors')
    { # need to join macros table

      $macro_from_string  = ",$dbQA.$QAMacros{Table} as macro ";
      $macro_where_string = "sum.$QASum{qaID} = macro.$QAMacros{qaID} and";

      $QAstatus_string = "macro.$QAstatus!='0' and macro.$QAstatus!='n/a'";
      $macro_string = "macro.$QAMacros{macroName} = '$macro_name' and"
	if defined $macro_name;
    }
    else {die "Wrong argument $QAstatus"}
  }
  else {$QAstatus_string = "1>0";}

  #query ...
  my $query = qq{ select distinct sum.$QASum{report_key}
	 	  from $dbQA.$QASum{Table} as sum
		       $macro_from_string
		       $file_from_string
		       $job_from_string
		 where 
		       $macro_where_string
		       $file_where_string
		       $job_where_string
		       $eventGen_string 
		       $LibTag_string 
		       $platform_string
		       $eventType_string
		       $geometry_string
		       $ondisk_string
		       $data_type_string
		       $createTime_string
		       $jobStatus_string
		       $macro_string
		       $QAstatus_string
		 limit $limit };
  
  print $query;

  my $sth = $dbh->prepare( $query );
  $sth->execute;
  
  my @report_keys;

  while ( my $key = $sth->fetchrow_array){
    push @report_keys, $key;
  }

  return @report_keys;
} 
#=======================================================================
# get nightly selected keys for real jobs only

sub GetNightlyKeysReal{
  my @selection_param = @_;

  return GetNightlyKeys('real',@selection_param);
}

#=======================================================================
# get nightly selected keys for MC jobs only

sub GetNightlyKeysMC{
  my @selection_param = @_;

  return GetNightlyKeys('MC',@selection_param);
}

1;

