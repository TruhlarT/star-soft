#! /usr/bin/perl
# 
# utilities for database interface for updating new QA 'objects'
#
#===================================================================
package Db_update_utilities;
#===================================================================
use DBI;
use POSIX qw(strftime);
use CGI qw/:standard :html3/;
use Time::Local;
use QA_globals;
use QA_db_utilities qw(:db_globals); # import

use strict;
1;
#-------------------
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
# takes an argument of either real or MC
#
sub UpdateQAOffline{
  my $data_type   = shift; # either 'real' or 'MC'
  my $limit       = 20;     # limit number of new jobs
  my $oldest_date; # dont retrieve anything older than this
  my $file_type;
  my $time_sec = 100*3600*24; # number of seconds in a week
  my $today    = strftime("%Y-%m-%d %H:%M:%S",localtime());

  # real or simulation?
  if($data_type eq 'real')
  {
    $file_type = 'daq_reco';
    $oldest_date='2000-06-20';
  }
  elsif($data_type eq 'MC')
  {
    $file_type = 'MC_reco';  
    $oldest_date='2000-04-01';
  }
  else {die "Wrong argument $data_type" }
  
  # report key
  my $query_key = qq{select concat(jobID, '.', runID, '.',   
			      date_format(file.createTime, '%y%m%d'))
		     from $dbFile.$FileCatalog as file
		     where file.jobID=? limit 1};

  # recent production jobID's have slashes ...
  # replace with underscores
  
  sub make_report_key_offline{
    my $report_key = shift;

    $report_key =~ s/\//_/g;
    return $report_key;
  }

  # update
  my $query_update = qq{select distinct file.jobID
			from $dbFile.$FileCatalog as file 
			LEFT JOIN $dbQA.$QASum{Table} as qa
			on file.jobID = qa.$QASum{jobID}
			where
			  file.type = '$file_type' and
			  file.createTime < '$today' and
			  file.hpss = 'N' and 
			  file.createTime > '$oldest_date' and 
			  qa.$QASum{jobID} is NULL
			limit $limit};


  # insert new jobs into  the QASummaryTable 
  my $query_insert = qq{insert into $dbQA.$QASum{Table} 
			set
			  $QASum{jobID}       = ?,
			  $QASum{report_key}  = ?,
			  $QASum{type}        = '$data_type',
			  $QASum{QAdone}      = 'N',
			  $QASum{qaID}        = NULL
			};

  my (@key_list);
  my $sth_update = $dbh->prepare($query_update); # find jobs to update
  my $sth_key    = $dbh->prepare($query_key);    # get the report key info
  my $sth_insert = $dbh->prepare($query_insert); # insert into QASummary

print $query_update,"\n";
  $sth_update->execute;
  my $rows = $sth_update->rows or return; # get out if there are no jobs

  print h3("Found $rows new jobs\n");

  # loop over jobs
  while ( my $jobID = $sth_update->fetchrow_array ) {
    $sth_key->execute($jobID);
    
    # get report key
    my $report_key = make_report_key_offline($sth_key->fetchrow_array);
    
    # save report_key
    push @key_list, $report_key;
    
    # insert into QASummary
    $sth_insert->execute($jobID, $report_key);
  }	       
  return @key_list;
}
#-------------------
# update for offline MC
# wraps around UpdateQAOffline
#
sub UpdateQAOfflineMC{

  return UpdateQAOffline('MC');
}

#-------------------
# update for offline real
# wraps around UpdateQAOffline
#
sub UpdateQAOfflineReal{

  return UpdateQAOffline('real');
}

#-------------------
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
#
sub UpdateQANightly {  
  my $data_class = shift; # 'real' or 'MC'
  
  my $limit       = 10;
  my $oldest_date = '2000-06-25'; # dont retrieve anything older 
  my ($type, $eventGen_string);
  my $today    = strftime("%Y-%m-%d %H:%M:%S",localtime());

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

  

  # get info for report key
  my $query_key = qq{select concat(LibLevel,'.',
			        platform,'.', eventGen,'.', 
			        eventType,'.', geometry,'.',
			        date_format(createTime,'%y%m%d'))
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
			  file.createTime < '$today' and
			  file.jobID != 'n/a' and
			  file.createTime > '$oldest_date' and
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
			  $QASum{type}       = '$data_class',
		          $QASum{qaID}       = NULL          
			};
  my (@key_list);
print $query_update,"\n";
  my $sth_update = $dbh->prepare($query_update); # find jobs to update
  my $sth_key    = $dbh->prepare($query_key);    # get report key info
  my $sth_check  = $dbh->prepare($query_check);  # check for uniqueness
  my $sth_insert = $dbh->prepare($query_insert); # insert into QASummary 

  $sth_update->execute;
  my $rows = $sth_update->rows or return; # get out if there are no jobs to update

  print h3("Found $rows new jobs\n");

  # loop over jobs
  while ( my $jobID = $sth_update->fetchrow_array) {
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

#-------------------
# update nightly test MC
#
sub UpdateQANightlyMC { 

  return UpdateQANightly('MC');
}

#-------------------
# update nightly test real data
#
sub UpdateQANightlyReal { 

  return UpdateQANightly('real');
}
#-------------------
# update online raw
# scan evtpool (or is the datapool?).
#
sub UpdateOnline{
  my ($io, $dh, %seen, %duplicate, @histkeys, @toUpdate);
  
  my $count =0; # for debugging

  # get the report keys from the summary hist dir
  $io = new IO_object("SummaryHistDir") or return;
  $dh = $io->Open;

  # stripping off the file type should give us the corresponding 'report key'
  while (defined (my $file = readdir $dh)){
    if ( $file =~ /\.root$/){
      (my $key = $file) =~ s/\.\w+\.root$//;
      push @histkeys, $key unless $duplicate{$key}++;
    }
  }
  undef $io;
  
  # now go into the QA reports directory, 
  $io = new IO_object("TopdirReport");
  $dh = $io->Open;
  
  my @QAreports  = readdir $dh;
  undef $io;
  
  # put QAreports in the seen hash
  @seen{ @QAreports } = ();

  # find the keys from the histfiles not in the QAreports
  foreach (@histkeys){
    push @toUpdate, $_ unless exists $seen{$_};
  }
  # test
  #print join "\n", @toUpdate;
  
  # now update the database

  InsertOnlineQASum(@toUpdate);

  return @toUpdate;
}
#-------------------
# takes a bunch of report keys and inserts the new 'jobs' into
# the QASummary table

sub InsertOnlineQASum{
  my @toUpdate = @_;

  my $query = qq{ insert into $dbQA.$QASum{Table} set
		    $QASum{report_key} = ?,
		    $QASum{QAdone}     = 'N',
		    $QASum{qaID}       = NULL         
		  };

  my $sth = $dbh->prepare($query);
  
  foreach my $key (@toUpdate) {
    $sth->execute($key);
  }

}
  
#-------------------
# called in QA_main
# gets the report keys from the QATable that need to be QA-ed
#
sub GetToDoReportKeys{
  my $type = shift; # real or MC
  my (@todo_keys, $job, $type_string);
  

  if ($type eq 'real'){
    $type_string = "$QASum{type} = 'real'";
  }
  elsif ($type eq 'MC'){
    $type_string = "$QASum{type} = 'MC'";
  }

  # distinct just in case
  my $query = qq{select distinct $QASum{report_key} 
		 from $dbQA.QASum{Table}  
		 where $QASum{QAdone} = 'N' and
	         $type_string};
  
  my $todo_keys_ref = $dbh->selectcol_arrayref($query);

  return @{$todo_keys_ref};
}
#---------------------------
sub GetToDoReportKeysMC{
  return GetToDoReportKeys('MC');
}
#---------------------------
sub GetToDoReportKeysReal{
  return GetToDoReportKeys('real');
}

sub Test{ print "dbFile      = $dbFile\n",
	        "FileCatalog = $FileCatalog\n",
	        "JobStatus   = $JobStatus\n" }


