#! /usr/bin/perl
# 
# utilities for the KeyList_object.
# extracts the relevant information from the database
# to allow users to select on jobs.
#
#===================================================================
package Db_KeyList_utilities;
#===================================================================
use CGI qw/:standard :html3/;

use DBI;
use Time::Local;
use QA_globals;
use POSIX qw(strftime);
use QA_db_utilities qw(:db_globals); # import db handle and tables

use strict qw(vars subs);
use vars qw($selectLimit);

$selectLimit = 500; # limit in retrieving report keys

1;
#===================================================================
# get values for dataset selection menu for offline db
# argument is real or MC

sub GetOfflineSelections{
  my $argument = shift;      # real or MC

  my $now = time;
  my $hashref;               # stores all the selections
  my ($fileType, %query);

  if ($argument eq 'real'){
    $fileType = 'real';
  }
  elsif ( $argument eq 'MC' ){
    $fileType = 'MC';
  }
  else { die "Wrong argument" }
  
  # library selections

  my $queryLibrary = qq{select distinct job.prodSeries, job.chainName
			 from $dbFile.$JobStatus as job,
			      $dbQA.$QASum{Table} as s
			 where job.jobID       = s.$QASum{jobID} and
			       s.$QASum{type} = '$fileType'
			 order by job.prodSeries asc};
     

  # run id
  $query{runID} = QueryOffline('runID',$fileType,'desc');
  
  # dataset 
  $query{dataset} = QueryOffline('dataset',$fileType);

  # QA macros
#  $query{macroName} = qq{select distinct m.$QAMacros{macroName}
#		       from $dbQA.$QAMacros{Table} as m,
#		            $dbQA.$QASum{Table} as s
#		       where 
#		            m.$QAMacros{qaID} = s.$QASum{qaID} and
#		            m.$QAMacros{extension}!='ps' and
#		            m.$QAMacros{extension}!='ps.gz' and
#		            s.$QASum{type}     = '$fileType'           
#		       order by m.$QAMacros{macroName} asc};

  my $sth;

  # get prodOptions - this is different from the others.
  $sth = $dbh->prepare($queryLibrary);
  $sth->execute;

  while (my ($prodSeries, $chainName) = $sth->fetchrow_array) {
    push( @{$hashref->{prodOptions}->{$prodSeries}}, $chainName );
  }

  # more stuff
  foreach my $field (keys %query){    
    $hashref->{$field} = $dbh->selectcol_arrayref($query{$field});
  }
  
  return $hashref;
			 
} 
#========================================================================
sub QueryOffline{
  my $field     = shift;
  my $fileType  = shift;
  my $order     = shift || 'desc';

  return qq{select distinct file.$field
	    from $dbFile.$FileCatalog as file,
	          $dbQA.$QASum{Table} as s
	    where file.jobID = s.$QASum{jobID} and
	          s.$QASum{type} = '$fileType'
	    order by file.$field $order};
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
  my $dataType = shift; # real or MC

  my $now = time;
  my (%query, $fileType, $where_string);

  # different queries for different class of data
  # for real data we have 'daq' and maybe later 'cosmics'
  if ($dataType eq 'MC')
  {
    $where_string  = qq{eventGen!='n/a' and
			eventGen!='daq' and
			eventGen!='cosmics' and};
      
    $fileType = 'MC';
    
  }
  elsif ($dataType eq 'real')  
  {
    $where_string = qq{eventGen!='n/a' and
		      (eventGen='daq' or
		       eventGen='cosmics') and };
      
    $fileType = 'real';

  }
  else {die "Wrong data type $dataType"};

  # other queries...
  $query{eventGen}  = QueryNightly('eventGen', $where_string);
  $query{eventType} = QueryNightly('eventType', $where_string);
  $query{platform}  = QueryNightly('platform', $where_string);
  $query{LibLevel}  = QueryNightly('LibLevel', $where_string);
  $query{geometry}  = QueryNightly('geometry', $where_string); 

#  $query{macroName} = qq{select distinct m.$QAMacros{macroName}
#			  from $dbQA.$QAMacros{Table} as m,
#			       $dbQA.$QASum{Table} as s
#			  where 
#			        m.$QAMacros{qaID} = s.$QASum{qaID} and 
#			        s.$QASum{type}    = '$fileType' and 
#			        m.$QAMacros{extension}!='ps' and
#                                m.$QAMacros{extension}!='ps.gz' 
#			  order by m.$QAMacros{macroName} asc};


  my ($hashref, $value, $sth);

  # get the possible values
  foreach my $field (keys %query){
    $hashref->{$field} = $dbh->selectcol_arrayref($query{$field});
  }

  return $hashref;
}
#========================================================================
sub QueryNightly{
  my $field = shift;
  my $where_string = shift if defined @_;

  return qq{select distinct $field
	    from $dbFile.$FileCatalog 
	    where $where_string 
	          $field !='n/a'
	    order by $field};
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
  my $dataType     = shift; # real or MC
  my $prodOptions   = shift; # e.g. "$prodSeries;$chainName"
  my $runID         = shift; # e.g. 124
  my $QAstatus_arg  = shift; # e.g. "ok"
  my $jobStatus     = shift; # e.g. 'not done'
  my $createTime    = shift; # e.g. three_days
  my $dataset       = shift;
  my $QAdoneTime    = shift;


  #---------------------------------------------------------------------
  # pmj 28/6/00 display keys with header, table formatting

  my @db_key_strings =
    (
     "dataType = $dataType<br>",
     "prodOptions = $prodOptions<br>",
     "runID = $runID<br>",
     "jobStatus = $jobStatus<br>",
     "QAstatus_arg = $QAstatus_arg<br>",
     "createTime = $createTime<br>",
     "dataset = $dataset<br>"
  );

  PrintTableOfKeys(@db_key_strings);
  #----------------------------------------------------------------

  # which class of data are we looking at?
  my $dataType_string;
  if ($dataType eq 'real')
  {
    $dataType_string = "sum.$QASum{type} = 'real' and";
  }
  elsif ($dataType eq 'MC')
  {
    $dataType_string = "sum.$QASum{type} = 'MC' and";
  }
  else {die "Wrong dataType $dataType"; }
  

  # fine tune prodOptions
  my ($prodSeries, $chainName) = split( /;/, $prodOptions );
  
  # fine tune status
  my ($QAstatus, $macroName)  = split( /;/, $QAstatus_arg );

  #----
  # selection strings...
  # determine which tables to join
  my ($file_from_string, $job_from_string);
  my ($file_where_string, $job_where_string);

  # always include the file catalog
  $file_from_string = ",$dbFile.$FileCatalog as file";
  $file_where_string = "sum.jobID = file.jobID and";

  # --- from FileCatalog ---

  # runID string
  my $runID_string = "file.runID = '$runID' and" 
    if $runID ne 'any';

  # dataset string
  my $dataset_string = "file.dataset = '$dataset' and"
    if $dataset ne 'any';
   
  # create time string
  my $createTime_string;
  if ($createTime ne 'any') {
    $createTime_string = ProcessJobCreateTimeQuery($createTime); 
  }

  # --- from JobStatus ---
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
    if ($jobStatus ne 'any'){
      $jobStatus_string = ProcessJobStatusQuery($jobStatus);

    }
  }
  #--- QA status ---
  # $QAstatus_string must be the last line in the 'where' clause

  my ($QAstatus_string, $macro_string, $macro_where_string, $macro_from_string) 
    = ProcessQAStatusQuery($QAstatus,$QAdoneTime,$macroName);
  
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
		      $dataType_string
		      $macro_string
		      $QAstatus_string
		limit $selectLimit };

  print "$query\n" if $gBrowser_object->ExpertPageFlag;

  return GetReportKeys($query, $selectLimit);


}
#=======================================================================
# get offline selected keys for real jobs only

sub GetOfflineKeysReal{
  my @selectionParam = @_;

  return GetOfflineKeys('real',@selectionParam);
}

#=======================================================================
# get offline selected keys for MC jobs only

sub GetOfflineKeysMC{
  my @selectionParam = @_;

  return GetOfflineKeys('MC',@selectionParam);
}
			  
#=======================================================================
# get the QA report keys for nightly test 
# see KeyList_object

sub GetNightlyKeys{
  my $dataType     = shift; # real or MC
  my $eventGen      = shift;
  my $LibLevel      = shift;
  my $platform      = shift;
  my $eventType     = shift;
  my $geometry      = shift;
  my $QAstatus_arg  = shift;
  my $ondisk        = shift;
  my $jobStatus     = shift;
  my $createTime    = shift; 
  my $QAdoneTime    = shift;

  #---------------------------------------------------------------------
  # pmj 28/6/00 display keys with header, table formatting

  my @db_key_strings = 
    (
     "eventGen     = $eventGen<br>",
     "LibLevel     = $LibLevel<br>",
     "platform     = $platform<br>",
     "eventType    = $eventType<br>",
     "geometry     = $geometry<br>",
     "QAstatus_arg = $QAstatus_arg<br>",
     "ondisk       = $ondisk<br>",
     "jobStatus    = $jobStatus<br>",
     "createTime   = $createTime<br>",
     "QAdoneTime   = $QAdoneTime<br>"
    );

  PrintTableOfKeys(@db_key_strings);
  #----------------------------------------------------------------


  # fine tune status
  my ($QAstatus, $macroName) = split( /;/, $QAstatus_arg);

  # --- determine which tables to join ---
  my ($file_from_string, $file_where_string);
  my ($job_from_string, $job_where_string);

  # --- file catalog ---
  my ($LibLevel_string, $platform_string, $eventType_string,
      $geometry_string, $ondisk_string, $createTime_string);

  # always join with the file catalog

  $file_from_string  = ",$dbFile.$FileCatalog as file";
  $file_where_string = "sum.jobID = file.jobID and";

  # any or not any?
  $LibLevel_string  = "file.LibLevel = '$LibLevel' and"
    if $LibLevel ne 'any';
  $platform_string  = "file.platform = '$platform' and"
    if $platform ne 'any';
  $eventType_string = "file.eventType = '$eventType' and"
    if $eventType ne 'any';
  $geometry_string  = "file.geometry = '$geometry' and"
    if $geometry ne 'any';
  
  # ondisk?
  if ($ondisk ne 'any') {
    if ($ondisk eq 'on disk')
      {
	$ondisk_string = "file.avail = 'Y' and";
      }
    elsif ($ondisk eq 'not on disk') 
      {
	$ondisk_string = "file.avail = 'N' and";
      }
    else{ die "Wrong argument for on_disk";}
  }
  
  # when was the job created?
  $createTime_string = ProcessJobCreateTimeQuery($createTime);    

  # --- job status info ---
  # only join with jobStatus if client queries jobStatus
  my ($jobStatus_string);

  if ($jobStatus ne 'any') # then join the table
  {
    $job_from_string  = ",$dbFile.$JobStatus as job";
    $job_where_string = "sum.jobID = job.jobID and ";

    $jobStatus_string = ProcessJobStatusQuery($jobStatus);
  }
    
  # for eventGen, if real we dont need to query on it.
  # dataType_string takes care of selecting on real vs MC
  
  # which class of data are we looking at?
  my ($dataType_string, $eventGen_string);

  if ($dataType eq 'real')
  {
    $dataType_string = "sum.$QASum{type} = 'real' and";
  }
  elsif ($dataType eq 'MC')
  {
    $dataType_string = "sum.$QASum{type} = 'MC' and";

    # want specific event gen info if ne 'any'
    $eventGen_string  = "file.eventGen = '$eventGen' and"
      if $eventGen ne 'any';
  }
  else {die "Wrong data type $dataType"; }
 
  
  # $QAstatus_string must be the last line in the 'where' clause
  # used when no warnings or errors are specified

  my ($QAstatus_string, $macro_string, $macro_where_string, $macro_from_string) 
    = ProcessQAStatusQuery($QAstatus,$QAdoneTime,$macroName);
  
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
		       $LibLevel_string 
		       $platform_string
		       $eventType_string
		       $geometry_string
		       $ondisk_string
		       $dataType_string
		       $createTime_string
		       $jobStatus_string
		       $macro_string
		       $QAstatus_string
		 limit $selectLimit };
  
  # for debugging
  #print "$query\n" if $gBrowser_object->ExpertPageFlag;

  return GetReportKeys($query, $selectLimit);

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
#=======================================================================
# process job creation time query

sub ProcessJobCreateTimeQuery{
  my $createTime = shift;

  return if $createTime eq 'any';

  my $createTime_string;

  # create time string
  my $now = strftime("%Y-%m-%d %H:%M:%S", localtime());
  my $days;
  # cant get the stupid soft refs to work...
  
  $days = 1  if $createTime eq 'one_day';
  $days = 3  if $createTime eq 'three_days';
  $days = 7  if $createTime eq 'seven_days';
  $days = 14 if $createTime eq 'fourteen_days';
  
  $createTime_string  = 
    " (to_days('$now')-to_days(file.createTime))<= $days and";
 
  return $createTime_string;
}
#========================================================================
# process the job status query

sub ProcessJobStatusQuery{
  my $jobStatus = shift;

  my ($jobStatus_string);

  # jobStatus string
  if ($jobStatus eq 'done' ){ 
    $jobStatus_string = "job.jobStatus ='done' and";
  }
  elsif ($jobStatus eq 'not done'){
    $jobStatus_string = "job.jobStatus !='done' and";
  }
  else { die "Wrong argument for jobStatus";}
  
  return $jobStatus_string;
}
  
#========================================================================
# returns :
# QAstatus clause, the Macro where clause (optional - to join the table),
# Macro from clause (optional - to join the table if needed),
# Macro clause

# 07/12/01 - new qa fields
# 'any','done','done and ok','done and not ok',
# 'done and analyzed','done and not analyzed',
# 'not done', 'running'
#

sub ProcessQAStatusQuery{
  my $QAstatus  = shift;
  my $QAdoneTime = shift;
  my $macroName = shift;

  my ($QAstatus_string, $macro_string);
  my ($macro_from_string, $macro_where_string);
  my $QAdoneTime_string;

  # create time string
  if($QAdoneTime ne 'any' && 
     ($QAstatus ne 'not done' && $QAstatus ne 'running')){
    my $now = strftime("%Y-%m-%d %H:%M:%S", localtime());
    my $days;
    $days = 1  if $QAdoneTime eq 'one_day';
    $days = 3  if $QAdoneTime eq 'three_days';
    $days = 7  if $QAdoneTime eq 'seven_days';
    $days = 14 if $QAdoneTime eq 'fourteen_days';
    
    $QAdoneTime_string  = 
      " (to_days('$now')-to_days(sum.$QASum{QAdate}))<= $days and ";
  }
   
  if ($QAstatus ne 'any')
  {
    if ($QAstatus ne 'warnings' and $QAstatus ne 'errors')
    { # dont need to join with macros table
      
      # QAok should be 'n/a' unless QA is done,
      # but just to be safe, requre both to be true.
      if($QAstatus eq 'done'){
	$QAstatus_string = "sum.$QASum{QAdone}='Y'";
      }
      elsif($QAstatus eq 'done and ok'){
	$QAstatus_string = "sum.$QASum{QAdone}='Y' and sum.$QASum{QAok}='Y'";
      }
      elsif($QAstatus eq 'done and not ok'){
	$QAstatus_string = "sum.$QASum{QAdone}='Y' and sum.$QASum{QAok}='N'";
      }
      elsif($QAstatus eq 'done and analyzed'){
	$QAstatus_string = "sum.$QASum{QAdone}='Y' and sum.$QASum{QAanalyzed}='Y'";
      }
      elsif($QAstatus eq 'done and not analyzed'){
	$QAstatus_string = "sum.$QASum{QAdone}='Y' and sum.$QASum{QAanalyzed}='N'";
      }
      elsif($QAstatus eq 'not done'){
	$QAstatus_string = "sum.$QASum{QAdone}='N'";
      }
      elsif($QAstatus eq 'running'){
	$QAstatus_string = "sum.$QASum{QAdone}='in progress'";
      }
    }
    elsif ($QAstatus eq 'warnings' or $QAstatus eq 'errors')
    { 
      # need to join macros table if the macro string is defined
 
      $macro_from_string  = ",$dbQA.$QAMacros{Table} as macro ";
      $macro_where_string = "sum.$QASum{qaID} = macro.$QAMacros{qaID} and";

      $QAstatus_string = "macro.$QAstatus!='0' and macro.$QAstatus!='n/a'";
      $macro_string = "macro.$QAMacros{macroName} = '$macroName' and"
	if defined $macroName;
    }
    else {die "Wrong argument $QAstatus"}
  }
  else {$QAstatus_string = "1>0";}

  $QAstatus_string = "$QAdoneTime_string $QAstatus_string";

  return ($QAstatus_string, $macro_string, $macro_where_string, $macro_from_string);
}

#=======================================================================
# get all runID's for offline
# sorted by creation date

sub GetOnlineKeys{
  my $QAstatus = shift;
  my $radio    = shift; # 'runID' or 'creation date'
  my $runID    = shift;
  my $year     = shift;
  my $month    = shift;
  my $day      = shift;
  my $detector = shift;

  $day   = remove_white_space($day);
  $month = remove_white_space($month);
  $runID = remove_white_space($runID);

  my @db_key_strings = ( "QA status = $QAstatus<br>",
			 "radio     = $radio<br>",
			 "runID     = $runID<br>",
			 "year      = $year<br>",
			 "month     = $month<br>",
			 "day       = $day<br>"   
		       );

  PrintTableOfKeys(@db_key_strings);

  my $limit    = 50;   # limit the number of jobs to return

  # -- QA status -
  my $qa_string;
  if ($QAstatus ne 'any'){
    $qa_string = "$QASum{QAdone} = 'Y'" if $QAstatus eq 'done';
    $qa_string = "$QASum{QAdone} = 'N'" if $QAstatus eq 'not done';
    $qa_string = "$QASum{QAok}   = 'Y'" if $QAstatus eq 'ok';
    $qa_string = "$QASum{QAok}   = 'N'" if $QAstatus eq 'not ok';
  }
  else {$qa_string = "1>0"; } # need a dummy where clause
  
  # -- runID --
  my ($runID_string, $date_string);

  if ($radio eq 'runID'){
    $runID_string = "$QASum{runID} = '$runID' and" if $runID;
  }
  # -- createTime--
  elsif ($radio eq 'date'){ 
    if (!$year){
      print h3("You must include the year.  Sorry..."); return;
    }
    else{
      $month = make_date_nice( $month );
      $day   = make_date_nice( $day );
      
      # if the string is empty, use the mysql wild card
      $month ||= "%";
      $day   ||= "%";
      
      $date_string = "$QASum{createTime} like '$year-$month-$day%' and";
    }
  }
  else {die "Wrong argument for the radio button"}
  
  # -- detector--
  # always selected 
  my $detector_string = "$QASum{detector} = '$detector' and";

  # query...
  
  my $query = qq{ select $QASum{report_key}
		  from $QASum{Table}
		  where
		    $runID_string
		    $date_string
		    $detector_string
		    $qa_string
		  order by $QASum{createTime} desc
		  limit $limit};
  print $query;

  my $ref = $dbh->selectcol_arrayref($query);
    
  return @{$ref};
		    
}
#=======================================================================
# prepends a '0' for day or month, if the user only types in a single 
# digit.

sub make_date_nice{
  my $number = shift;
  my $count  = length $number;
  return $count == 1 ? "0$number" : $number;
}
#=======================================================================
# eliminate devaint white space
# also removes unfriendly single quotes

sub remove_white_space{
  $_[0] =~ s/\s//g;
  $_[0] =~ s/'//g;
  return $_[0];
}
#=======================================================================
sub GetReportKeys{
  my $query = shift;

  my $sth = $dbh->prepare($query);
  $sth->execute();
  my $rows = $sth->rows;

  # used to be more stuff here

  return map { $_->[0] } @{$sth->fetchall_arrayref()};

}

#=======================================================================
# for printing DB query keys to browser

sub PrintTableOfKeys{

  my @db_key_strings = @_;

  #---------------------------------------------------------------

  print h4("Database query:");

  my @rows;
  my $n_cols = 3;

  for (my $i = 0; $i<= $#db_key_strings; $i += $n_cols){

    my @temp;

    for (my $j = 0; $j<$n_cols; $j++){
      my $element = $i + $j;
      $element > $#db_key_strings and last;
      $temp[$j] = "<strong>".$db_key_strings[$element]."</strong>";
    }
   push @rows, td([ @temp ]);
  }

  print table(
	      {-border=>'0', -width=>'100%', -align=>'center'},
	      Tr(\@rows)
	     ),"<hr>";
  
}
#=======================================================================
1;



