#! /opt/star/bin/perl
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
use lib "/afs/rhic.bnl.gov/star/packages/scripts"; # RunDaq.pm lives here
use RunDAQ;

use strict;
use vars qw(%oldestDay);
1;

#--------------------------------------------------------------------
# OLDEST date
# this is the oldest 'create time' date picked up by autoqa.
# 08/24/2001 bum. NOT USED anymore
my %oldestDate = ( nightly_real => '2001-08-20',
		   nightly_MC   => '2001-08-20',
		   offline_real => '2001-07-20',
		   offline_MC   => '2001-07-20',
		   offline_fast => undef
);

# days old cut off for updating.
%oldestDay = ( nightly_real => 30,
	       nightly_MC   => 14,
	       offline_real => 14,
	       offline_MC   => 30,
	       offline_fast => 10
);

# max number of updated jobs
my %updateLimit = ( nightly_real => 10,
		    nightly_MC   => 50,
		    offline_real => 200, #200 
		    offline_MC   => 10,
		    offline_fast => 10
);
# for real offline 
my $oldestRun = 1000000;
# for offline fast
#my $oldestFastRun = 2300000;
my $debug = 0;

#-------------------
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
# takes an argument of either real or MC
#
sub UpdateQAOffline{
  my $dataType   = shift; # either 'real' or 'MC'

  my $limit;     # limit number of new jobs
  my $oldestDate;# dont retrieve anything older than this
  my $daysCut;   #
  my $fileType;  # daq_reco or MC_reco
  my $today      = strftime("%Y-%m-%d %H:%M:%S",localtime());
  my $oldestRunString;

  # real or simulation?
  if($dataType eq 'real')
  {
    $fileType  = 'daq_reco';
    #$oldestDate= $oldestDate{'offline_real'};
    $daysCut    = $oldestDay{'offline_real'};
    $limit     = $updateLimit{'offline_real'};
    $oldestRunString="file.runID>=$oldestRun and";
  }
  elsif($dataType eq 'MC')
  {
    $fileType  = 'MC_reco';  
    #$oldestDate= $oldestDate{'offline_MC'};
    $daysCut   = $oldestDay{'offline_MC'};
    $limit     = $updateLimit{'offline_MC'};
  }
  else {die "Wrong argument $dataType" }
 
  $oldestDate = strftime("%Y-%m-%d",localtime(time-$daysCut*3600*24));

  # report key
  my $queryKey = qq{select concat(jobID, '.', redone, '.', runID, '.',   
				  fileSeq)
		     from $dbFile.$FileCatalog as file
		     where file.jobID=? limit 1};

  # recent production jobID's have slashes ...
  # replace with underscores
  
  sub make_report_key_offline{
    my ($jobID,$redone,$runID,$fileSeq) = @_;

    $jobID =~ s/\//_/g;
    return "$jobID.$redone.$runID.$fileSeq";
  }

  # update
  # Note: no sorting done b/c mysql f*cks it up sometimes.
  my $queryUpdate = qq{select distinct file.jobID, file.redone, file.runID,
			 file.fileSeq
			from $dbFile.$FileCatalog as file 
			LEFT JOIN $dbQA.$QASum{Table} as qa
			  using (jobID, redone)
			where
			  file.type = '$fileType' and
			  file.createTime < '$today' and
			  file.hpss = 'N' and 
			  file.createTime > '$oldestDate' and
			  $oldestRunString
			  qa.$QASum{jobID} is NULL
			limit $limit};

  print "update query:\n$queryUpdate\n" if $debug;

  # insert new jobs into  the QASummaryTable 
  my $queryInsert = qq{insert IGNORE into $dbQA.$QASum{Table} 
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

  my %runhash; # hash of hashes of hashes
#  my %noskip;  # keys are runIDs
  my $fraction = .1; # Dec 17,2001 - not used.
  my $countLimit=2;
  my %count; # num of file per run with skip='N'

  # organize the new jobs by runID 
  LOOP:while (my ($jobID, $redone, $runID,$fileSeq) = $sthUpdate->fetchrow_array){
    next LOOP if !$jobID; # huh?
    $runhash{$runID}{$fileSeq}{$jobID}{redone}  = $redone;
    
    #print "$runID, count=",$count{$runID},"\n";

    # Dec 17,2001- check that no more than $countLimit entries per runid
    # has skip='N'
    next LOOP if($count{runID}>=$countLimit);
    
    $count{$runID} += countEntries($runID);
    if($count{$runID}>=$countLimit){ # enough already
      next LOOP;
    }
    #set as noskip (also mod 10, not 1)
    elsif($fileSeq%10==0){
      $runhash{$runID}{$fileSeq}{$jobID}{noskip}++;
      $count{$runID}++;
    }
  }
  my $jobID;
  # now double check that there's at least one noskip key per runID
  #foreach my $runID ( keys %runhash ){
  #next if $count{$runID}>0;
    
    # else set one of the jobs as noskip (file seq 10,20..)
  #SEQ:foreach my $fileSeq ( keys %{$runhash{$runID}} ){
  #    next if($fileSeq%10!=0);
  #    foreach $jobID ( keys %{$runhash{$runID}{$fileSeq}} ){
  #	$runhash{$runID}{$fileSeq}{$jobID}{noskip}++;
  #     last SEQ;
  #    }
  #  }
  #}
  # loop over runID, jobID
  my $countRun=0; my $countJob=0; my $count=0;
  my %foundJob;
  foreach my $runID ( sort keys %runhash ){
    print ++$countRun, " : $runID\n";
    foreach my $fileSeq ( sort { $a <=> $b } keys %{$runhash{$runID}} ){
      foreach my $jobID ( keys %{$runhash{$runID}{$fileSeq}} ){

	# double check for uniqueness
	#next if $foundJob{$jobID}++;

	my $redone = $runhash{$runID}{$fileSeq}{$jobID}{redone};
	my $skip   = exists $runhash{$runID}{$fileSeq}{$jobID}{noskip} ? 'N' : 'Y';
	
	print "\t",++$countJob, " fileSeq=$fileSeq : $jobID skip? $skip",
	  ",redone? $redone\n";
	$count++;
	#$sthKey->execute($jobID);
	
	# get report key
	my $reportKey = make_report_key_offline($jobID,$redone,$runID,$fileSeq);
	
	# insert into QASummary
	#print "\t$reportKey\n";
	unless($debug){
	  my $rc = $sthInsert->execute($jobID, $redone, $reportKey, $skip);
	  $rc +=0;
	  # save report key
	  if(!$rc){
	    print "Couldnt insert into db?\n";
	  }
	  else{
	    push @keyList, $reportKey if $skip eq 'N'; # only no skip jobs
	  }
	}
      }
      #$countJob=0;
    }	 
  }      
  print h3("Found $count new jobs\n");

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
# counts the numbers of entries whose jobID 
# matches the argument string(usually run) and has 'skip='N'

sub countEntries{
  my $run=shift;

  my $query=qq{select count(*) from $dbQA.$QASum{Table}
	       where $QASum{jobID} like '%$run%' and
	       $QASum{skip}='N'};
  return $dbh->selectrow_array($query);
}

#-------------------

sub UpdateQAOfflineFast{
  my $limit = $updateLimit{'offline_fast'};
  my $doneStatus = 2; # according to daqinfo.

  # report key
  my $queryKey = qq{select concat($DAQInfo{file},'.',$DAQInfo{collision})
		    from $dbFile.$DAQInfo{Table}
		    where $DAQInfo{file}=? limit 1
		  };

  # update
  my $queryUpdate = qq{select daq.$DAQInfo{file}, qa.$QASum{QAdone}, 
		       daq.$DAQInfo{runNumber}
		       from $dbFile.$DAQInfo{Table} as daq
		       LEFT JOIN $dbQA.$QASum{Table} as qa
		       on daq.$DAQInfo{file}=qa.$QASum{jobID}
		       where 
			 daq.diskLoc!=0 and 
			 (daq.$DAQInfo{status} = $doneStatus and
			 (qa.$QASum{jobID} is NULL ||
			  qa.$QASum{QAdone}='Y'))
			 
		       limit $limit
		     };
  
  #
  # removed this from the update.
  #
  # || (daq.$DAQInfo{status} = 3 and
  # qa.$QASum{jobID} is NULL)


  # insert
  my $queryInsert = qq{insert into $dbQA.$QASum{Table}
		       set
			 $QASum{jobID}      = ?,
			 $QASum{report_key} = ?,
			 $QASum{type}       = 'real',
			 $QASum{QAdone}     = 'N',
		         $QASum{skip}       = ?,
			 $QASum{qaID}       = NULL
		       };

  my $queryResetQAdone = qq{update $dbQA.$QASum{Table}
			    set $QASum{QAdone}='N'
			    where $QASum{jobID}=?
			  };
  my $querySetSkip = qq{update $dbQA.$QASum{Table}
			set $QASum{skip} = ?
			where $QASum{jobID} = ?
			};

  # here's the logic.
  # first get all 'files' from DAQInfo with status=2.
  # check if this file already exists in the qa table.
  # if NO, then insert a new row.
  # if YES, then 
  #         check if QA has been done
  #         if NO.  ignore it.
  #         if YES. return this key as well (probably a reproduction)
  
  my @keyList;

  my $sthUpdate = $dbh->prepare($queryUpdate);
  my $sthKey    = $dbh->prepare($queryKey);
  my $sthInsert = $dbh->prepare($queryInsert);
  my $sthResetQAdone = $dbh->prepare($queryResetQAdone);
  my $sthSetSkip = $dbh->prepare($querySetSkip);

  $sthUpdate->execute();

  
  # Note: what DAQInfo calls 'file' autoQA calls 'jobID'
 
  my %runhash; # hash of hashes of hashes
  my %noskip;  # keys are runIDs
  my $fraction=0; # Dec 17,2001 - not used
  my $countLimit=2;
   my %count; # num of file per run with skip='N'

  # organize the new jobs by runID 
  LOOP:while (my ($jobID, $qadone, $runID) = $sthUpdate->fetchrow_array){
    next if !$jobID; # huh?
    $runhash{$runID}{$jobID}{qadone}  = $qadone;

    # Dec 17,2001- check that no more than $countLimit entries per runid
    # has skip='N'
    
    next LOOP if($count{runID}>=$countLimit);
    
    $count{$runID}+=countEntries($runID);
    if($count{$runID}>=$countLimit){ # enough already
      next LOOP;
    }
    #set as noskip 
    else{
      $runhash{$runID}{$jobID}{noskip}++;
      $count{$runID}++;
    }
  }

  # now double check that there's at least one noskip key per runID
  foreach my $runID ( keys %runhash ){
    next if $count{$runID}>0;
    
    # else randomly set one of the jobs as noskip
  JOB:foreach my $jobID ( keys %{$runhash{$runID}} ){
      $runhash{$runID}{$jobID}{noskip}++;
      last JOB;
    }
  }

  # connect to the daqinfo table
  my $hh = rdaq_open_odatabase() or do{
    print "Cannot connect to operation db\n";
    return;
  };

  # loop over runID, jobID
  my $countRun=0; my $countJob=0; my $count=0;
  foreach my $runID ( keys %runhash ){
    print h4(++$countRun, " : $runID\n");
    foreach my $jobID ( keys %{$runhash{$runID}} ){
      print h4("\t",++$countJob, " : $jobID\n"); $count++;
      $sthKey->execute($jobID);
      my $report_key = $sthKey->fetchrow_array();
      my $QAdone = $runhash{$runID}{$jobID}{qadone};
      my $skip   = exists $runhash{$runID}{$jobID}{noskip} ? 'N' : 'Y';
      my $stat=undef;
      if(!$QAdone){ # new file. insert
	print "does not exist in QAtable...";
	$sthKey->execute($jobID);
	print "inserting...";
	$stat = $sthInsert->execute($jobID,$report_key,$skip) if !$debug;
	if($stat) { 
	  print "done<br>\n";
	}
	else { 
	  print "Cannot insert<br>\n";
	}
      }
      else{ # already exists, but probably reproduction
	print "Already exists but qa is done.  Will reset qa done to No...";
	$stat = $sthResetQAdone->execute($jobID) if !$debug;
	$stat += 0;
	if(!$stat){
	  print "Cannot reset QAdone to no<br>\n";
	}
	else{
	  print "done<br>\n"; 	   
	}
	if($stat){ $stat = $sthSetSkip->execute($skip,$jobID) if !$debug; }
      }
      if($stat) { 
	# set qadone in the DAQInfo table for skip so we dont
	# pick up this file again.
	if($skip eq 'Y' and !$debug){
	  rdaq_set_files($hh,3,$jobID) or 
	    print "Uh oh.  could not set qa done in daq info table\n";
	}
	push @keyList,$report_key if $skip eq 'N';
      }
      
      print "$runID, $report_key, skip=$skip, stat=$stat\n" if $debug;

    }
  }
  print "Found $count new jobs<br>\n";

  rdaq_close_odatabase($hh);

  return @keyList;
}

#-------------------
# performs 2 tasks -
# 1. returns an array of updated reportkeys 
# 2. update QASummary with these jobID's
#
sub UpdateQANightly {  
  my $dataType = shift; # 'real' or 'MC'
  
  my $limit;       # limit number of new jobs
  my $oldestDate;  # dont retrieve anything older 
  my $daysCut;     #
  my $today  = strftime("%Y-%m-%d %H:%M:%S",localtime());

  my ($type, $eventGen_string);
  # real or simulation
  if ($dataType eq 'real')
  {
    $eventGen_string = qq{file.eventGen != 'n/a' and
			  (file.eventGen = 'daq' or
                           file.eventGen = 'cosmics') and
			 };
    #$oldestDate = $oldestDate{'nightly_real'};
    $daysCut = $oldestDay{'nightly_real'};
    $limit = $updateLimit{'nightly_real'};
  }
  elsif ($dataType eq 'MC')
  {
    $eventGen_string = qq{file.eventGen != 'n/a' and
			  file.eventGen != 'daq' and
			  file.eventGen != 'cosmics' and
			};
    #$oldestDate = $oldestDate{'nightly_MC'};
    $daysCut = $oldestDay{'nightly_MC'};
    $limit = $updateLimit{'nightly_MC'};
  }
  else { die "Incorrect argument $dataType"; }

  $oldestDate = strftime("%Y-%m-%d",localtime(time-$daysCut*3600*24));

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
  
  print "update query:\n$queryUpdate\n" if $debug;

  # check if the report_key is unique
  my $queryCheck =  qq{select count(*)
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

  # somtimes report keys are duplicated in the database.
  # they can either be intentional (two jobs run on the same day)
  # or database errors (QA or production).
  # @addLabel are the postfixes to these duplications.

  my @addLabel = ('a','b','c','d','e','f','g');

  #$sthUpdate->dump_results();

  my $jobID; 
  $sthUpdate->bind_columns(\$jobID);

  # loop over jobs
  my $count=0;
  while ( $sthUpdate->fetch) {
    next if !$jobID;
    print h4(++$count, " : jobId=$jobID\n");
    $sthKey->execute($jobID);
    
    # get the report key
    my $reportKey = make_report_key( $sthKey->fetchrow_array);

    # check if the report key is unique
    $sthCheck->execute($reportKey);
    my ($found) = $sthCheck->fetchrow_array;
 
    # apparently not unique
    if($found){
      print "$reportKey found already\n";
      my $label;
      my $trialKey;
      CHECK:foreach $label (@addLabel){
	$trialKey = $reportKey . $label;
	print "\tTrial key=$trialKey\n";
	$sthCheck->execute($trialKey);
	my ($foundAgain) = $sthCheck->fetchrow_array;
	
	if(!$foundAgain){ # new reportkey
	  print "\tOk. the above is unique\n";
	  last CHECK;
	}
      }
      # set the report key w/ additional label
      $reportKey = $trialKey;
      print "\tSet $reportKey\n";
    }
    # save keys
    push @keyList, $reportKey;

    # insert into QASummary
    print "Inserting report key=$reportKey\n";
    my $stat = $sthInsert->execute($jobID, $reportKey) unless $debug;
  }
  print h3("Found $count new jobs\n");

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
  my $limit = 50;

  # distinct just in case
  my $query = qq{select distinct $QASum{report_key} 
		 from $dbQA.$QASum{Table}  
		 where $QASum{QAdone} = 'N'
	       };

  my $oldestDate;
  if ($type eq 'real'){
    $query .= qq{and $QASum{type} = 'real'
		}; 
   # $oldestDate = $oldestDate{'nightly_real'};
  }
  elsif ($type eq 'MC'){
    $query .= qq{and $QASum{type} = 'MC'
	       };
   # $oldestDate = $oldestDate{'nightly_MC'};
  }

  # adapt date format to sql timestamp, then cut on oldest allowed date
  #$oldestDate =~ /^\d\d(\d\d)-(\d\d)-(\d\d)/;
  #$oldestDate = "${1}${2}${3}2359"; #last minute of oldest day
  #$query .= qq{and insertTime > \'$oldestDate\'
  #	       };
  #print("query=$query<br>\n");

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

1;



