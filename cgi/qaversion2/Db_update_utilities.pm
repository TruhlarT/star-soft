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

#--------------------------------------------------------------------
# OLDEST date
# this is the oldest 'create time' date picked up by autoqa.
# 
my %oldestDate = ( nightlyReal => '2001-04-20',
		   nightlyMC   => '2001-04-20',
		   offlineReal => '2001-04-20',
		   offlineMC   => '2001-04-30'
);

#-------------------
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
# takes an argument of either real or MC
#
sub UpdateQAOffline{
  my $dataType   = shift; # either 'real' or 'MC'

  my $limit      = 10;     # limit number of new jobs
  my $oldestDate;         # dont retrieve anything older than this
  my $fileType;           # daq_reco or MC_reco
  my $today      = strftime("%Y-%m-%d %H:%M:%S",localtime());

  # real or simulation?
  if($dataType eq 'real')
  {
    $fileType = 'daq_reco';
    $oldestDate= $oldestDate{'offlineReal'};
  }
  elsif($dataType eq 'MC')
  {
    $fileType = 'MC_reco';  
    $oldestDate=$oldestDate{'offlineMC'};
  }
  else {die "Wrong argument $dataType" }
  
  # report key
  my $queryKey = qq{select concat(jobID, '.', redone, '.', runID, '.',   
				  fileSeq)
		     from $dbFile.$FileCatalog as file
		     where file.jobID=? limit 1};

  # recent production jobID's have slashes ...
  # replace with underscores
  
  sub make_report_key_offline{
    my $reportKey = shift;

    $reportKey =~ s/\//_/g;
    return $reportKey;
  }

  # update
  my $queryUpdate = qq{select distinct file.jobID, file.redone, file.runID
			from $dbFile.$FileCatalog as file 
			LEFT JOIN $dbQA.$QASum{Table} as qa
			  using (jobID, redone)
			where
			  file.type = '$fileType' and
			  file.createTime < '$today' and
			  file.hpss = 'N' and 
			  file.createTime > '$oldestDate' and 
			  qa.$QASum{jobID} is NULL
			limit $limit};


  # insert new jobs into  the QASummaryTable 
  my $queryInsert = qq{insert into $dbQA.$QASum{Table} 
			set
			  $QASum{jobID}       = ?,
			  $QASum{redone}      = ?,
			  $QASum{report_key}  = ?,
			  $QASum{type}        = '$dataType',
			  $QASum{QAdone}      = 'N',
			  $QASum{skip}        = ?,
			  $QASum{qaID}        = NULL
			};

  my (@keyList);
  my $sthUpdate = $dbh->prepare($queryUpdate); # find jobs to update
  my $sthKey    = $dbh->prepare($queryKey);    # get the report key info
  my $sthInsert = $dbh->prepare($queryInsert); # insert into QASummary

  $sthUpdate->execute;
  my $rows = $sthUpdate->rows or return; # get out if there are no jobs

  print h3("Found $rows new jobs\n");

  my %runhash; # hash of hashes of hashes
  my %noskip;  # keys are runIDs

  # organize the new jobs by runID 
  while (my ($jobID, $redone, $runID) = $sthUpdate->fetchrow_array){
    $runhash{$runID}{$jobID}{redone}  = $redone;
    
    # set 1/10 as noskip
    if (rand() < 0.1 ){
      $runhash{$runID}{$jobID}{noskip}++;
      $noskip{$runID}++;
    }
  }

  # now double check that there's at least one noskip key per runID
  foreach my $runID ( keys %runhash ){
    next if exists $noskip{$runID};
    
    # else randomly set one of the jobs as noskip
  JOB:foreach my $jobID ( keys %{$runhash{$runID}} ){
      $runhash{$runID}{$jobID}{noskip}++;
      last JOB;
    }
  }
  # loop over runID, jobID
  foreach my $runID ( keys %runhash ){
    foreach my $jobID ( keys %{$runhash{$runID}} ){

      $sthKey->execute($jobID);
    
      # get report key
      my $reportKey = make_report_key_offline($sthKey->fetchrow_array);
      
      # save report key
      push @keyList, $reportKey;
    
      # insert into QASummary
      my $redone = $runhash{$runID}{$jobID}{redone};
      my $skip   = exists $runhash{$runID}{$jobID}{noskip} ? 'N' : 'Y';
      
      #print "\n$runID, $skip";

      $sthInsert->execute($jobID, $redone, $reportKey, $skip);
    }
  }	       
  return @keyList;
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
  my $dataType = shift; # 'real' or 'MC'
  
  my $limit       = 20;            # limit number of new jobs
  my $oldestDate; # dont retrieve anything older 
  my $today       = strftime("%Y-%m-%d %H:%M:%S",localtime());

  my ($type, $eventGen_string);
  # real or simulation
  if ($dataType eq 'real')
  {
    $eventGen_string = qq{file.eventGen != 'n/a' and
			  (file.eventGen = 'daq' or
                           file.eventGen = 'cosmics') and
			 };
    $oldestDate = $oldestDate{'nightlyReal'};
  }
  elsif ($dataType eq 'MC')
  {
    $eventGen_string = qq{file.eventGen != 'n/a' and
			  file.eventGen != 'daq' and
			  file.eventGen != 'cosmics' and
			};
    $oldestDate = $oldestDate{'nightlyMC'};
  }
  else { die "Incorrect argument $dataType"; }

  

  # get info for report key
  my $queryKey =  qq{select concat(LibLevel,'.',
			        platform,'.', eventGen,'.', 
			        eventType,'.', geometry,'.',
			        date_format(createTime,'%y%m%d'))
		     from $dbFile.$FileCatalog
		     where jobID=? limit 1};

  # make the report key
  sub make_report_key{
    my $reportKey = shift;
    
    # make some abbreviations
    $reportKey =~ s/lowdensity/low/;
    $reportKey =~ s/highdensity/high/;
    $reportKey =~ s/standard/std/;
    $reportKey =~ s/hadronic_cocktail/hc/;

    # get rid of any n/a (e.g. for real jobs)
    $reportKey =~ s/\.n\/a//;

    return $reportKey;
  }
  
  # update
  my $queryUpdate =  qq{select distinct file.jobID
			from $dbFile.$FileCatalog as file
			LEFT JOIN $dbQA.$QASum{Table} as qa
			  on file.jobID = qa.$QASum{jobID}
			where  
			  file.avail='Y' and
			  $eventGen_string
			  file.createTime < '$today' and
			  file.jobID != 'n/a' and
			  file.createTime > '$oldestDate' and
			qa.$QASum{jobID} is NULL
			limit $limit};
  
  # check if the report_key is unique
  my $queryCheck =  qq{select $QASum{qaID}
		       from $dbQA.$QASum{Table}
		       where $QASum{report_key} = ? };

  # insert new jobs into  the QASummaryTable 
  my $queryInsert =  qq{insert into $dbQA.$QASum{Table} 
			set
			  $QASum{jobID}      = ?,
   			  $QASum{report_key} = ?,
			  $QASum{QAdone}     = 'N',
			  $QASum{type}       = '$dataType',
		          $QASum{qaID}       = NULL          
			};
  my (@keyList);
  my $sthUpdate = $dbh->prepare($queryUpdate); # find jobs to update
  my $sthKey    = $dbh->prepare($queryKey);    # get report key info
  my $sthCheck  = $dbh->prepare($queryCheck);  # check for uniqueness
  my $sthInsert = $dbh->prepare($queryInsert); # insert into QASummary 

  $sthUpdate->execute;
  my $rows = $sthUpdate->rows or return; # get out if there are no jobs to update

  print h3("Found $rows new jobs\n");

  # somtimes jobIDs are duplicated in the database.
  # they can either be intentional (two jobs run on the same day)
  # or database errors.
  # @addLabel is the postfixes to these duplications.

  my @addLabel = ('a','b','c','d','e','f','g');

  # loop over jobs
  while ( my $jobID = $sthUpdate->fetchrow_array) {
    $sthKey->execute($jobID);
    
    # get the report key
    my $reportKey = make_report_key( $sthKey->fetchrow_array);

    # check if the report key is unique
    $sthCheck->execute($reportKey);
    my $found = $sthCheck->fetchrow_array;
 
    # apparently not unique
    if($found){
	my $label;
	foreach $label (@addLabel){
	    my $trialKey = $reportKey . $label;
	    $sthCheck->execute($trialKey);
	    my $foundAgain = $sthCheck->fetchrow_array;
    
	    if(!$foundAgain){ # new reportkey
		last;
	    }
	}
	# set the report key w/ additional label
	$reportKey .= $label;
    }
        

    # save keys
    push @keyList, $reportKey;

    # insert into QASummary
    $sthInsert->execute($jobID, $reportKey);
  }
  
  return @keyList;
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
# gets the report keys from the QATable that need to be QA-ed
#
sub GetToDoReportKeys{
  my $type = shift; # real or MC
  my $limit = 15;

  # distinct just in case
  my $query = qq{select distinct $QASum{report_key} 
		 from $dbQA.$QASum{Table}  
		 where $QASum{QAdone} = 'N'
	       };

  if ($type eq 'real'){
    $query .= qq{and $QASum{type} = 'real'
		};
  }
  elsif ($type eq 'MC'){
    $query .= qq{and $QASum{type} = 'MC'
	       };
  }
  # quick fix - make sure that the skip field is no for production.
  if ($gDataClass_object->DataClass() =~ /offline/){
    $query .= qq{and $QASum{skip} = 'N'
	       };
  }
  # limit
  $query .= qq{limit $limit };
      
  return @{$dbh->selectcol_arrayref($query)};

}
#---------------------------
sub GetToDoReportKeysMC{
  return GetToDoReportKeys('MC');
}
#---------------------------
sub GetToDoReportKeysReal{
  return GetToDoReportKeys('real');
}


