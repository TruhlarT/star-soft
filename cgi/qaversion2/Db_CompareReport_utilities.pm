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
use Tie::IxHash;
use QA_globals;
use QA_db_utilities qw(:db_globals); # import db handle and tables

use strict qw(vars subs);
1;
#----------
# finds similar jobs for MC data for nightly tests
# returns a list of report keys
# criteria: event generator
#           event type
#           geometry

sub nightly_MC{
  my $report_key  = shift;
  my $doReference = shift || 0; # only want reference keys?

  my $reference = "and $QASum{reference} = 'Y' " if ($doReference);

  my $limit      = 10; # limit on how many similar keys are returned

  # first get the eventGen, event type, and geometry
  # according to the report key

  my $queryInfo = qq{select file.eventGen, file.eventType, file.geometry
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = file.jobID
			    limit 1 };

  # then find similar jobs- return the report keys

  my $querySim = qq{select distinct qa.$QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = file.jobID and
			file.eventGen    = ? and
			file.eventType   = ? and
			file.geometry    = ? and
			qa.$QASum{report_key} != '$report_key' and
			qa.$QASum{QAdone} = 'Y'  
			$reference
		        limit $limit};

  my ($eventGen, $eventType, $geometry) = $dbh->selectrow_array($queryInfo);

  # return similar keys
  return @{$dbh->selectcol_arrayref($querySim, undef, 
				    $eventGen, $eventType, $geometry)};
  
}
#----------
# finds similar jobs for real data for nightly tests
# returns a list of report keys
# criteria: 
#           event type
#           geometry

sub nightly_real{
  my $report_key = shift;
  my $doReference = shift || 0; # only want reference keys?

  my $reference = "and $QASum{reference} = 'Y' " if ($doReference);

  my $limit      = 10; # limit on returned keys

  # first get the event type, and geometry
  # according to the report key

  my $queryInfo = qq{select file.eventType, file.geometry
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = file.jobID
			    limit 1 };

  # then find similar jobs- return the report keys
  
  my $querySim = qq{select distinct qa.$QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = file.jobID and
			file.eventType   = ? and
			file.geometry    = ? and
			qa.$QASum{report_key} != '$report_key' and
			qa.$QASum{QAdone} = 'Y' 
			$reference
		        limit $limit};

  my ($eventType, $geometry) = $dbh->selectrow_array($queryInfo);

  # return similar keys
  return @{$dbh->selectcol_arrayref($querySim, undef, 
				    $eventType, $geometry)};
}
#----------
# find similar jobs for offline production
# criteria : prodSeries
#            dataset

sub offline_real{
  my $report_key = shift;
  my $doReference = shift || 0; # only want reference keys?

  my $reference = "and $QASum{reference} = 'Y' " if ($doReference);
  
  my $limit      = 10;

  # first get the prodSeries, chainName, dataset
  # according to the report key

  my $queryInfo = qq{select job.prodSeries, file.dataset
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file,
			   $dbFile.$JobStatus as job
		      where qa.$QASum{report_key} = '$report_key' and
			    qa.$QASum{jobID}      = job.jobID     and
			    qa.$QASum{jobID}      = file.jobID    
			    limit 1 };

  # then find similar jobs- return the report keys
  
  my $querySim = qq{select distinct qa.report_key
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$JobStatus as job,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = job.jobID and
			qa.$QASum{jobID} = file.jobID and
			job.prodSeries   = ? and
			file.dataset     = ? and 
			qa.$QASum{report_key} != '$report_key' and
			qa.$QASum{QAdone} = 'Y' 
			$reference
		        limit $limit};

  my ($sth, @similarKeys);

  my ($prodSeries, $dataset) = $dbh->selectrow_array($queryInfo);

  $sth = $dbh->prepare($querySim );
  
  $sth->execute($prodSeries, $dataset);

  while (my $report_key = $sth->fetchrow_array){
    push @similarKeys, $report_key;
  }

  return @similarKeys;
}

#----------
# offline MC is identical to offline real for now

sub offline_MC{
  my $report_key  = shift;
  my $doReference = shift;
  return offline_real($report_key, $doReference);
}
#-----------

sub debug{
  return nightly_MC(@_);
}
#-----------
# check if this report key is in fact a reference report key

sub IsReference{
  my $report_key = shift;

  my $query = qq{select $QASum{qaID}
		 from $QASum{Table}
		 where 
		   $QASum{report_key} = '$report_key' and
		   $QASum{reference}  = 'Y'
		 };

  return defined $dbh->selectrow_array($query);
}

#----------
# returns the references for offline.
# matched by prodSeries and dataset

sub GetReferences_offline{
  my $datatype = shift; # real or MC
  
  my $datastring = "qa.$QASum{type} = '$datatype'";
    
  # first get all possible prodSeries, dataset pairs that 
  # have an entry in the QASummary table
  
  my $query = qq{ select distinct job.prodSeries, file.dataset
	          from $dbQA.$QASum{Table} as qa,
		       $dbFile.$JobStatus as job,
		       $dbFile.$FileCatalog as file
		  where qa.$QASum{jobID} = job.jobID and
	                qa.$QASum{jobID} = file.jobID and
                        $datastring and
			job.prodSeries != 'P00hd_1' and
			job.prodSeries != 'P00he' and
			job.prodSeries != 'P00hf'
			order by job.prodSeries, file.dataset
		       };
			
  my $sth = $dbh->prepare($query);
  $sth->execute();

  my %refHash; # hash of arrays 
  tie %refHash, "Tie::IxHash";

  while ( my ($prodSeries, $dataset) = $sth->fetchrow_array){
    $refHash{"$prodSeries $dataset"} = undef;
  }

  # find the matching reference report_keys

  my $queryRef = qq {select distinct $QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$JobStatus as job,
		          $dbFile.$FileCatalog as file
		     where 
		          qa.$QASum{jobID}  = job.jobID and
			  qa.$QASum{jobID}  = file.jobID and 
			  qa.$QASum{QAdone} = 'Y' and
			  qa.$QASum{reference} = 'Y' and
			  job.prodSeries    = ? and
			  file.dataset      = ? and
                          $datastring
			};

  my $sthRef = $dbh->prepare($queryRef);

  # now loop over the refHash hash
  foreach my $key ( keys %refHash ) {

    my ($prodSeries, $dataset) = split(/\s+/, $key);
    $sthRef->execute($prodSeries, $dataset);
    
    # can have more than one reference dataset
    # per prodSeries,dataset pair
    
    while (my $report_key = $sthRef->fetchrow_array){
      push @{$refHash{$key}}, $report_key;
    }
  }


  return %refHash;
}
#----------
sub GetReferences_offline_real{
  return GetReferences_offline('real');
}

#----------
sub GetReferences_offline_MC{
  return GetReferences_offline('MC');
}

#----------
# returns the references for nightly_MC
# MC matched by :
#           event generator
#           event type
#           geometry
# real matched by : event type, geometry

sub GetReferences_nightly{
  my $type = shift; # real or MC

  my ($select, $match, $order);
  # beware: the ordering of $select and $match must be the same
  if ($type eq 'MC'){
    $select = "file.eventGen, file.eventType, file.geometry ";
    $match  = qq{file.eventGen = ? and file.eventType = ? 
		 and file.geometry = ? 
	       };
    $order  = "file.eventGen, file.geometry, file.eventType ";
  }
  elsif( $type eq 'real'){
    $select = "file.eventType, file.geometry ";
    $match  = "file.eventType = ? and file.geometry = ?"; 
    $order  = "file.geometry, file.eventType ";
  }


  # first get the possible eventGen, event type, and geometry

  my $queryInfo = qq{select distinct $select
		      from $dbQA.$QASum{Table} as qa,
			   $dbFile.$FileCatalog as file
		      where 
			    qa.$QASum{jobID} = file.jobID and
			    qa.$QASum{type}  = '$type'     
			    order by $order
			  };
  
  my %refHash;
  tie %refHash, "Tie::IxHash";

  my $sthInfo = $dbh->prepare($queryInfo);
  $sthInfo->execute();

  while( my @values = $sthInfo->fetchrow_array){
    $refHash{"@values"} = undef;
  }

  # get the references
  my $queryRef = qq{select distinct qa.$QASum{report_key}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$FileCatalog as file
		     where 
			qa.$QASum{jobID} = file.jobID and
		        qa.$QASum{QAdone}  = 'Y' and
			qa.$QASum{reference} = 'Y' and
			$match
		      };

  my $sthRef = $dbh->prepare($queryRef);
 
  foreach my $key ( keys %refHash ){
    my @values = split(/\s+/,$key);

    $sthRef->execute(@values);

    while (my $report_key = $sthRef->fetchrow_array()){
      push @{$refHash{$key}}, $report_key;
    }
  }
  
  return %refHash;
}
#---------
sub GetReferences_nightly_MC{
  return GetReferences_nightly('MC');
}
#---------
sub GetReferences_nightly_real{
  return GetReferences_nightly('real');
}
#------------
sub GetReferences_debug{
  return GetReferences_nightly_MC();
}
#------------
# check that the report key actually corresponds to the 
# match criteria

sub ReferenceOk_offline_real{
  my $report_key = shift;
  my $dataType   = shift;

  # clean up the report key
  $report_key = MakeNice($report_key);

  # parse the dataset
  my ($prodSeries, $dataset) = split(/\s+/, $dataType);

  my $queryCheck = qq{select qa.$QASum{qaID}
		     from $dbQA.$QASum{Table} as qa,
		          $dbFile.$JobStatus as job,
		          $dbFile.$FileCatalog as file
		     where 
		          qa.$QASum{jobID}  = job.jobID and
			  qa.$QASum{jobID}  = file.jobID and 
			  qa.$QASum{QAdone} = 'Y' and
			  qa.$QASum{report_key} = '$report_key' and
			  job.prodSeries    = '$prodSeries' and
			  file.dataset      = '$dataset'
			};
  return defined $dbh->selectrow_array($queryCheck);
  
}
#------------
sub ReferenceOk_offline_MC{
  my $report_key = shift;
  my $dataType   = shift;

  return ReferenceOk_offline_real($report_key, $dataType);
}
#------------
sub ReferenceOk_nightly{
  my $report_key = shift;
  my $dataset    = shift;
  my $type       = shift; # real or MC

  # clean up the report key
  $report_key = MakeNice($report_key);

  my ($eventType, $geometry, $eventGen);
  
  if ($type eq 'real'){
    ($eventType, $geometry) = split(/\s+/, $dataset);
  }
  elsif ($type eq 'MC'){
    ($eventGen, $eventType, $geometry) = split(/\s+/, $dataset);
  }

  my $queryCheck = qq{select qa.$QASum{report_key}
		      from $dbQA.$QASum{Table} as qa,
		           $dbFile.$FileCatalog as file
		      where 
			qa.$QASum{jobID} = file.jobID and
			qa.$QASum{report_key} = '$report_key' and
			qa.$QASum{QAdone}     = 'Y' and
			qa.$QASum{type}       = '$type' and
			file.eventType   = '$eventType' and
			file.geometry    = '$geometry' 
		      };

  if ($type eq 'MC'){
    $queryCheck .= " and file.eventGen = '$eventGen'";
  }

  return defined $dbh->selectrow_array($queryCheck);
  
}
#------------
sub ReferenceOk_nightly_real{
  my $report_key = shift;
  my $dataType   = shift;
  
  return ReferenceOk_nightly($report_key, $dataType, 'real');
}
#------------
sub ReferenceOk_nightly_MC{
  my $report_key = shift;
  my $dataType   = shift;
  
  return ReferenceOk_nightly($report_key, $dataType, 'MC');
}
#------------
sub ReferenceOk_debug{
  return ReferenceOk_nightly_MC(@_);
}
#------------
sub UpdateReference{
  my $report_key = shift;
  my $value      = shift; # Y or N

  my $query = qq{update $dbQA.$QASum{Table}
		 set $QASum{reference} = '$value'
		 where $QASum{report_key} = '$report_key'
	       };

  my $rows = $dbh->do($query);
  return $rows;
}
#------------

sub AddReference{
  my $report_key = shift;
  
  return UpdateReference($report_key,'Y');
}

#------------

sub DeleteReference{
  my $report_key = shift;
  
  return UpdateReference($report_key,'N');
}
#------------

sub MakeNice{
  $_[0] =~ s/\s//g;
  $_[0] =~ s/'//g;
  return $_[0];
}
