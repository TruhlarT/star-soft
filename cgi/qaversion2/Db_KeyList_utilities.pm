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
use QA_db_utilities qw(:db_globals); # import db handle and tables

use strict qw(vars subs);
1;
#========================================================================
# get values for dataset selection menu for offline db
# argument is real or MC

sub GetOfflineSelections{
  my $argument = shift;      # real or MC

  my $now = time;
  my $hashref;               # stores all the selections
  my ($file_type, %query);


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
  $query{runID} = qq{select distinct file.runID
		     from $dbFile.$FileCatalog as file,
		          $dbQA.$QASum{Table} as s
		     where file.jobID = s.$QASum{jobID} and
			   ($now-unix_timestamp(createtime))>0 and
		           s.$QASum{type} = '$file_type'
		     order by file.runID asc};


  # QA macros
  $query{macroName} = qq{select distinct m.$QAMacros{macroName}
		       from $dbQA.$QAMacros{Table} as m,
		            $dbQA.$QASum{Table} as s
		       where 
		            m.$QAMacros{qaID} = s.$QASum{qaID} and
		            m.$QAMacros{extension}!='ps' and
		            m.$QAMacros{extension}!='ps.gz' and
		            s.$QASum{type}     = '$file_type'           
		       order by m.$QAMacros{macroName} asc};

  # dataset 
  $query{dataset} = qq{select distinct file.dataset
		       from $dbFile.$FileCatalog as file,
			    $dbQA.$QASum{Table} as s
		       where file.jobID      = s.$QASum{jobID} and
			    s.$QASum{type} = '$file_type'
		       order by file.dataset asc };
  
  my $sth;

  # get prodOptions - this is different from the others.
  $sth = $dbh->prepare($query_library);
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

  my $now = time;
  my (%query, $file_type);

  # different queries for different class of data
  if ($data_type eq 'MC')
  {
    $query{eventGen}  = qq{select distinct eventGen
		          from $dbFile.$FileCatalog
			  where eventGen !='n/a/'
			  order by eventGen};

    $query{eventType} = qq{select distinct eventType
		          from $dbFile.$FileCatalog
                          where eventType!='n/a' 
                          order by eventType};
    $file_type = 'MC';
    
  }
  elsif ($data_type eq 'real')  
  {
    $query{eventGen}  = qq{select ID
			  from $dbFile.$FileCatalog
                          where 1<0}; # dummy query
    
    # only want event types where the event gen is not applicable
    $query{eventType} = qq{select distinct eventType
		         from $dbFile.$FileCatalog
                         where eventType!='n/a' and
			       eventGen = 'n/a'
			 order by eventType};
    $file_type = 'real';

  }
  else {die "Wrong data type $data_type"};

  # other queries...

  $query{LibLevel}   = qq{select distinct LibLevel
		         from $dbFile.$FileCatalog 
			 where LibTag!='n/a'
                         order by LibLevel};
  $query{platform}  = qq{select distinct platform
		          from $dbFile.$FileCatalog 
			  where platform!='n/a'
                          order by platform};
  
  $query{geometry}  = qq{select distinct geometry
		         from $dbFile.$FileCatalog 
			 order by geometry};

  $query{macroName} = qq{select distinct m.$QAMacros{macroName}
			  from $dbQA.$QAMacros{Table} as m,
			       $dbQA.$QASum{Table} as s
			  where 
			        m.$QAMacros{qaID} = s.$QASum{qaID} and 
			        s.$QASum{type}    = '$file_type' and 
			        m.$QAMacros{extension}!='ps' and
                                m.$QAMacros{extension}!='ps.gz'
			  order by m.$QAMacros{macroName} asc};


  my ($hashref, $value, $sth);

  # get the possible values
  foreach my $field (keys %query){
    $hashref->{$field} = $dbh->selectcol_arrayref($query{$field});
  }

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
  my $jobStatus     = shift; # e.g. 'not done'
  my $createTime    = shift; # e.g. three_days
  my $dataset       = shift;

  my $limit = 50; # dont want to get a million of them

  #---------------------------------------------------------------------
  # pmj 28/6/00 display keys with header, table formatting

  my @db_key_strings;
  push @db_key_strings, "data_type = $data_type<br>";
  push @db_key_strings, "prodOptions = $prodOptions<br>";
  push @db_key_strings, "runID = $runID<br>";
  push @db_key_strings, "jobStatus = $jobStatus<br>";
  push @db_key_strings, "QAstatus_arg = $QAstatus_arg<br>";
  push @db_key_strings, "createTime = $createTime<br>";
  push @db_key_strings, "dataset = $dataset<br>";

  PrintTableOfKeys(@db_key_strings);
  #----------------------------------------------------------------

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
      my $days;
      # cant get the stupid soft refs to work...
      
      $days = 3  if $createTime eq 'three_days';
      $days = 7  if $createTime eq 'seven_days';
      $days = 14 if $createTime eq 'fourteen_days';
      
      $createTime_string  = 
	" (to_days(from_unixtime($now))-to_days(file.createTime))<= $days and";
    }
  }
  
  # --- from cpJobStatus ---2
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
      if ($jobStatus eq 'done' ){ 
	$jobStatus_string = "job.jobStatus ='done' and";
      }
      elsif ($jobStatus eq 'not done'){
	$jobStatus_string = "job.jobStatus !='done' and";
      }
      else {die "Wrong argument for job status"}
    }
  }
  #--- QA status ---
  # $QAstatus_string must be the last line in the 'where' clause
  my ($QAstatus_string, $macro_string);
  my ($macro_where_string, $macro_from_string);

  if ($QAstatus ne 'any')
  {
    if ($QAstatus ne 'warnings' and $QAstatus ne 'errors')
    { # dont need to join with macros table
      
      $QAstatus_string = "sum.$QASum{QAok}='Y'"   if $QAstatus eq 'ok';
      $QAstatus_string = "sum.$QASum{QAok}='N'"   if $QAstatus eq 'not ok';
      $QAstatus_string = "sum.$QASum{QAdone}='Y'" if $QAstatus eq 'done';
      $QAstatus_string = "sum.$QASum{QAdone}='N'" if $QAstatus eq 'not done';
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

  print $query if $gBrowser_object->ExpertPageFlag;

  my $sth = $dbh->prepare($query);
  $sth->execute();
  my $rows = $sth->rows;
  if ($rows == $limit){
    print h3(font({-color=>'red'}, "You've selected $rows rows<br>",
		  "Please narrow your selection for better performance<br>"));
  }
  return map { $_->[0] } @{$sth->fetchall_arrayref()};

#  my $keys_ref = $dbh->selectcol_arrayref( $query );
  
#  return @{$keys_ref};

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
  my $LibLevel      = shift;
  my $platform      = shift;
  my $eventType     = shift;
  my $geometry      = shift;
  my $QAstatus_arg  = shift;
  my $ondisk        = shift;
  my $jobStatus     = shift;
  my $createTime    = shift; 

  my $limit = 50; # limit the query

  #---------------------------------------------------------------------
  # pmj 28/6/00 display keys with header, table formatting

  my @db_key_strings;
  push @db_key_strings, "eventGen     = $eventGen<br>";
  push @db_key_strings, "LibLevel     = $LibLevel<br>";
  push @db_key_strings, "platform     = $platform<br>";
  push @db_key_strings, "eventType    = $eventType<br>";
  push @db_key_strings, "geometry     = $geometry<br>";
  push @db_key_strings, "QAstatus_arg = $QAstatus_arg<br>";
  push @db_key_strings, "ondisk       = $ondisk<br>";
  push @db_key_strings, "jobStatus    = $jobStatus<br>";
  push @db_key_strings, "createTime   = $createTime<br>";

  PrintTableOfKeys(@db_key_strings);
  #----------------------------------------------------------------


  # fine tune status
  my ($QAstatus, $macro_name) = split( /;/, $QAstatus_arg);

  # --- determine which tables to join ---
  my ($file_from_string, $file_where_string);
  my ($job_from_string, $job_where_string);

  # --- file catalog ---
  my ($LibLevel_string, $platform_string, $eventType_string,
      $geometry_string, $ondisk_string, $createTime_string);

  if ($eventGen   ne 'any' or
      $LibLevel   ne 'any' or 
      $platform   ne 'any' or
      $eventType  ne 'any' or
      $geometry   ne 'any' or
      $createTime ne 'any' or
      $ondisk     ne 'any'     )
  {
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
    if ($createTime ne 'any'){
      # create time string
      my $now = time;
      my $days;
      # cant get the stupid soft refs to work...
      
      $days = 3  if $createTime eq 'three_days';
      $days = 7  if $createTime eq 'seven_days';
      $days = 14 if $createTime eq 'fourteen_days';
      
      $createTime_string  = 
	" (to_days(from_unixtime($now))-to_days(file.createTime))<= $days and";
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
    elsif ($jobStatus eq 'not done'){
      $jobStatus_string = "job.jobStatus !='done' and";
    }
    else { die "Wrong argument for jobStatus";}
  }
    
  # for eventGen, if real we dont need to query on it.
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
      $QAstatus_string = "sum.$QASum{QAok}='N'"   if $QAstatus eq 'not ok';
      $QAstatus_string = "sum.$QASum{QAdone}='Y'" if $QAstatus eq 'done';
      $QAstatus_string = "sum.$QASum{QAdone}='N'" if $QAstatus eq 'not done';
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
		       $LibLevel_string 
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
  
  # for debugging
  print $query if $gBrowser_object->ExpertPageFlag;

  my $sth = $dbh->prepare($query);
  $sth->execute();
  my $rows = $sth->rows;
  if ($rows == $limit){
    print h3(font({-color=>'red'}, "You've selected $rows rows<br>",
		  "Please narrow your selection for better performance<br>"));
  }
  return map { $_->[0] } @{$sth->fetchall_arrayref()};


#  my $keys_ref = $dbh->selectcol_arrayref( $query );
#  return @{$keys_ref};

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
  my $count = $number =~ tr /0-9//;
  return $count == 1 ? "0$number" : $number;
}
#=======================================================================
# eliminate devaint white space

sub remove_white_space{
  $_[0] =~ s/\s+//g;
  return $_[0];
}
#=======================================================================
# for printing DB query keys to browser

sub PrintTableOfKeys{

  my @db_key_strings = @_;

  #---------------------------------------------------------------

  print h2("Database query:");

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



