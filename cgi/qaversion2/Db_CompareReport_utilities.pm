#! /usr/bin/perl
# 
# utilities for the database and comparing similar datasets
#
#==================================================================
package Db_CompareReport_utilities;
#==================================================================
use CGI qw/:standard :html3/;

use DBI;
use Time::Local;
use QA_globals;
use QA_db_utilities qw(:db_globals); # import db handle and tables

use strict qw(vars subs);
1;
#------------------------------------------------------------------
# finds similar jobs for MC data for nightly tests
# returns a list of report keys
# criteria: event generator
#           event type
#           geometry

sub nightly_MC{
  my $report_key = shift;
  my $limit      = 10; # limit on how many similar keys are returned

  # first get the eventGen, event type, and geometry
  # according to the report key

  my $query_info = qq{select file.eventGen, file.eventType, file.geometry
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = file.jobID
			    limit 1 };

  # then find similar jobs- return the report keys
  
  my $query_sim = qq{select distinct qa.$QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = file.jobID and
			file.eventGen    = ? and
			file.eventType   = ? and
			file.geometry    = ? and
			qa.$QASum{report_key} != '$report_key'
		        limit $limit};

  my ($sth, @similar_keys);

  my ($eventGen, $eventType, $geometry) = $dbh->selectrow_array($query_info);

  # return similar keys
  return @{$dbh->selectcol_arrayref($query_sim, undef, 
				    $eventGen, $eventType, $geometry)};
  
}
#--------------------------------------------------------------
# finds similar jobs for real data for nightly tests
# returns a list of report keys
# criteria: 
#           event type
#           geometry

sub nightly_real{
  my $report_key = shift;
  my $limit      = 10; # limit on returned keys

  # first get the event type, and geometry
  # according to the report key

  my $query_info = qq{select file.eventType, file.geometry
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = file.jobID
			    limit 1 };

  # then find similar jobs- return the report keys
  
  my $query_sim = qq{select distinct qa.$QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = file.jobID and
			file.eventType   = ? and
			file.geometry    = ? and
			qa.$QASum{report_key} != '$report_key'
			order by file.createTime desc
		        limit $limit};

  my ($sth, @similar_keys);

  my ($eventType, $geometry) = $dbh->selectrow_array($query_info);

  # return similar keys
  return @{$dbh->selectcol_arrayref($query_sim, undef, 
				    $eventType, $geometry)};
}
#------------------------------------------------------------------
# find similar jobs for offline production
# criteria : prodOptions (prodSeries, chainName)
#            dataset

sub offline_real{
  my $report_key = shift;
  my $limit      = 10;

  # first get the prodSeries, chainName, dataset
  # according to the report key

  my $query_info = qq{select job.prodSeries, job.chainName, file.dataset
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file,
			   $dbFile.$JobStatus as job
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = job.jobID     and
			    qa.$QASum{jobID}      = file.jobID 
			    limit 1 };

  # then find similar jobs- return the report keys
  
  my $query_sim = qq{select distinct qa.report_key
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$JobStatus as job,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = job.jobID and
			qa.$QASum{jobID} = file.jobID and
			job.prodSeries   = ? and
			job.chainName    = ? and
			file.dataset     = ? and 
			qa.$QASum{report_key} != '$report_key'
                        order by file.createTime desc
		        limit $limit};

  my ($sth, @similar_keys);

  my ($prodSeries, $chainName, $dataset) = $dbh->selectrow_array($query_info);

  $sth = $dbh->prepare($query_sim );
  
  $sth->execute($prodSeries, $chainName, $dataset);

  while (my $report_key = $sth->fetchrow_array){
    push @similar_keys, $report_key;
  }

  return @similar_keys;
}

#----------------------------------------------------------------
# offline MC is identical to offline real for now

sub offline_MC{
  my $report_key = shift;
  return offline_real($report_key);
}

  
			  
