#! /usr/bin/perl
# 
# utilities for database interface for updating
#
#===================================================================
package Db_update_utilities;
#===================================================================
use DBI;
use Time::Local;
use QA_globals;
use QA_db_utilities qw(:db_globals); # import

use strict;

#=========================================================================
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
# takes an argument of either real or MC

sub UpdateQAOffline{
  my $data_type   = shift; # either 'real' or 'MC'
                         # only used in $query_update
  my $limit       = 2; # limit number of new jobs
  my $oldest_date = '2000-01-01'; # dont retrieve anything older than this
  my ($file_type);

  # real or simulation?
 switch:{
    $data_type eq 'real' and do {$file_type = 'daq_reco'; last ;};
    $data_type eq 'MC'   and do {$file_type = 'MC_reco';  last ;};
    # default
    die "Wrong argument $data_type";
  }
  
  my @key_list;
  my $time_sec = 100*3600*24; # number of seconds in a week
  my $now      = time;        # current time in epoch sec

  # report key
  my $query_key = qq{select concat(jobID, '.', runID, '.',   
			      date_format(file.createTime, '%y%m%d'))
		     from $dbFile.$FileCatalog as file
		     where file.jobID=? limit 1};

  # recent production jobID's have slashes ...
  
  sub make_report_key{
    my $report_key = shift;

    return $report_key =~ s/\//_/g;
  }

  # update
  my $query_update = qq{select distinct file.jobID
			from $dbFile.$FileCatalog as file 
			LEFT JOIN $dbQA.$QASum{Table} as qa
			on file.jobID = qa.$QASum{jobID}
			where
			  file.type = '$file_type' and
			  unix_timestamp(file.createTime) < $now and
			  qa.$QASum{jobID} is NULL and
			  file.hpss = 'N' and
			  file.createTime > '$oldest_date'
			  
			limit $limit};


  # insert new jobs into  the QASummaryTable 
  my $query_insert = qq{insert into $dbQA.$QASum{Table} 
			set
			  $QASum{jobID}       = ?,
			  $QASum{report_key}  = ?,
			  $QASum{type}        = '$data_type',
			  $QASum{QAdone}      = 'N' };

			
  my $sth_update = $dbh->prepare($query_update); # find jobs to update
  my $sth_key    = $dbh->prepare($query_key); # get the report key info
  my $sth_insert = $dbh->prepare($query_insert); # insert into QASummary

  my $rc = $sth_update->execute;
  $rc += 0 or return; # get out if there are no jobs to update

  # loop over jobs
  while ( my $jobID= $sth_update->fetchrow_array) {
    $sth_key->execute($jobID);
    
    # get report key
    my $report_key = make_report_key($sth_key->fetchrow_array);
    
    # save report_key
    push @key_list, $report_key;
    
    # insert into QASummary
    $sth_insert->execute($jobID, $report_key);
  }	       
  return @key_list;
}
#========================================================================
# update for offline MC
# wraps around UpdateQAOffline

sub UpdateQAOfflineMC{

  return UpdateQAOffline('MC');
}

#========================================================================
# update for offline real
# wraps around UpdateQAOffline

sub UpdateQAOfflineReal{

  return UpdateQAOffline('real');
}

#=========================================================================
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's

sub UpdateQANightly {  
  my $data_class = shift; # 'real' or 'MC'
  my $limit = 2;

  my ($type, $eventGen_string);

  # real or simulation
  if ($data_class eq 'real')
  {
    $eventGen_string = "file.eventGen = 'n/a' and";
  }
  elsif ($data_class eq 'MC')
  {
    $eventGen_string = "file.eventGen != 'n/a' and";
  }
  else { die "Incorrect argument $data_class"; }

  my @key_list;
  my $time_sec = 100*3600*24;    #number of seconds in a week
  my $now      = time; #current time in epoch sec

  # get info for report key
  my $query_key = qq{select concat(LibLevel,'.',
			        platform,'.', eventGen,'.', 
			        eventType,'.', geometry,'.',
			        date_format(createTime,'%d%m%y'))
		     from $dbFile.$FileCatalog
		     where jobID=? limit 1};

  # make the report key
  sub make_report_key{
    my $report_key = shift;
    
    # make some abbreviations
    $report_key =~ s/lowdensity/low/;
    $report_key =~ s/highdensity/high/;
    $report_key =~ s/standard/std/;
    $report_key =~ s/hadronic_cocktail/hc/;

    # get rid of any n/a (e.g. for real jobs)
    $report_key =~ s/\.n\/a//;

    return $report_key;
  }
  
  # update
  my $query_update = qq{select distinct file.jobID
			from $dbFile.$FileCatalog as file
			LEFT JOIN $dbQA.$QASum{Table} as qa
			  on file.jobID = qa.$QASum{jobID}
			where  
			  file.avail='Y' and
			  $eventGen_string
			  unix_timestamp(file.createTime) < $now and
			  file.jobID != 'n/a' and 
			qa.$QASum{jobID} is NULL
			limit $limit};
  
  # check if the report_key is unique
  my $query_check = qq{select $QASum{qaID}
		       from $dbQA.$QASum{Table}
		       where report_key = ? };

  # insert new jobs into  the QASummaryTable 
  my $query_insert = qq{insert into $dbQA.$QASum{Table} 
			set
			  $QASum{jobID}      = ?,
			  $QASum{report_key} = ?,
			  $QASum{QAdone}     = 'N',
			  $QASum{type}       = '$data_class' };

  my $sth_update = $dbh->prepare($query_update); # find jobs to update
  my $sth_key    = $dbh->prepare($query_key); # get report key info
  my $sth_check  = $dbh->prepare($query_check); # check for uniqueness
  my $sth_insert = $dbh->prepare($query_insert); # insert into QASummary 

  my $rc = $sth_update->execute;
  $rc += 0 or return; # get out if there are no jobs to update
 
  # loop over jobs
  while ( my $jobID= $sth_update->fetchrow_array) {
    $sth_key->execute($jobID);
    
    # get the report key
    my $report_key = make_report_key( $sth_key->fetchrow_array);

    # check if the report key is unique
    $sth_check->execute($report_key);
    my $found = $sth_check->fetchrow_array;
    # not unique, add a 'b'.  if this is not unique, we're in trouble
    $found and $report_key .= 'b'; 

    # save keys
    push @key_list, $report_key;

    # insert into QASummary
    $sth_insert->execute($jobID, $report_key);
  }
  
  return @key_list;
}

#=========================================================================
# update nightly test MC

sub UpdateQANightlyMC { 

  return UpdateQANightly('MC');
}

#=========================================================================
# update nightly test real data

sub UpdateQANightlyReal { 

  return UpdateQANightly('real');
}
#=========================================================================
# called in QA_main
# gets the report keys from the QATable that need to be QA-ed

sub db_GetToDoReportKeys{
  my (@todo_keys, $job);

  # distinct just in case
  my $query = qq{select distinct $QASum{report_key} 
		 from $dbQA.$QASum{Table}  
		 where $QASum{QAdone} = 'N'};
  
  my $sth = $dbh->prepare($query);
  $sth->execute;
  
  push @todo_keys, $job while( $job = $sth->fetchrow_array );

  return @todo_keys;
}


sub Test{ print "dbFile      = $dbFile\n",
	        "FileCatalog = $FileCatalog\n",
	        "JobStatus   = $JobStatus\n" }

1;
