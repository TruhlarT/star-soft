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
use vars qw(@matchCriteria @order $subEditMatchValues $subSqlMatch $type);
my $debug = 0;
1;
#------------------------------------------------------------------
# @matchCriteria : array of the criteria for determining a 'similar' job.
#                : for now, these must come from the file catalog
# @order         : the order of the criteria by which the 
#                  matches are returned
# $subEditMatchValues: anonymous subroutine which parses the matching values 
# $subSqlMatch   : anon sub which processes the matching values
#                  and criteria into an sql string
# $type          : real or MC
#------------
# sets the above values according to the 'data class'.
# probably should move all this into DataClass_object.

sub Controller{
  
  my $dataClass = $gDataClass_object->DataClass();

  if ( $dataClass =~ /offline_real/ ){
    @matchCriteria = qw( dataset );
    @order         = qw( dataset );  
    # for offline real, we dont care about the stuff after 
    # the first period in the 'dataset' field
    $subEditMatchValues = sub { 
                               my ($data, @junk) = split(/\./,$_[0],2); 
			       return ($data);
			     };
    $subSqlMatch        = \&SqlMatchLike;
    $type               = 'real';
    
  }
  elsif ( $dataClass =~ /offline_MC/ ){
    @matchCriteria  = qw( dataset );
    @order          = qw( dataset );  
    $subEditMatchValues = sub {return @_}; # does nothing
    $subSqlMatch        = \&SqlMatchExact;
    $type               = 'MC';
  }
  elsif ( $dataClass =~ /nightly_real/ ){
    # event type, geometry
    @matchCriteria  = qw( eventType geometry);
    @order          = qw( geometry eventType);
    $subEditMatchValues = sub {return @_};
    $subSqlMatch        = \&SqlMatchExact;
    $type               = 'real';
  }
  elsif ( $dataClass =~ /nightly_MC/ ){
    # event gen, event type, geometry
    @matchCriteria = qw( eventGen eventType geometry);
    @order         = qw( eventGen geometry eventType);
    $subEditMatchValues = sub {return @_};
    $subSqlMatch        = \&SqlMatchExact;
    $type               = 'MC';
  }
  elsif ( $dataClass =~ /debug/ ) {
    @matchCriteria = qw( eventGen eventType geometry);
    @order         = qw( eventGen geometry eventType);
    $subEditMatchValues = sub {return @_};
    $subSqlMatch        = \&SqlMatchExact;
    $type               = 'MC';
  }
  elsif ($dataClass =~ /offline_fast/){
    @matchCriteria = qw( collision beamE);
    @order         = qw( collision beamE);
    $subEditMatchValues = sub {return @_};
    $subSqlMatch        = \&SqlMatchExact;
    $type               = 'n/a';
  }
}


sub SqlMatch{
  my $mode = shift; #exact, like
  my @matchValues = @_;

  my $sql;

  foreach my $i ( 0..$#matchCriteria ) {
    next if ($matchValues[$i] eq 'any'   or 
             $matchValues[$i] eq 'n/a'  or 
             not defined $matchValues[$i]  );
    if($mode eq 'exact'){
      $sql .= "$dbFile.$FileCatalog.$matchCriteria[$i] = '$matchValues[$i]' and ";}
    elsif($mode eq 'like'){
      $sql .= "$dbFile.$FileCatalog.$matchCriteria[$i] like '$matchValues[$i]%' and ";
    }
    else { die; }
  }
  # strip off the last 'and'
  $sql =~ s/and\s*$//;

  # if the string is empty, add a dummy query
  $sql .= "1>0" if (!defined $sql);

  return $sql;
}

#----------
# returns an sql query string for finding similar jobs.
# where the values match the criteria exactly 

sub SqlMatchExact{
  return SqlMatch('exact',@_);
}
#----------
# returns an sql query string for finding similar jobs.
# where the values are like the criteria

sub SqlMatchLike{
  return SqlMatch('like',@_);
}

#----------
# returns the default references
# corresponding to the report_key.

sub GetMatchingDefaultReferences{
  my $report_key = shift;
  my $limit = 10;

  # set the file scope globals
  Controller();

  # get the job ID
  my $jobID = QA_db_utilities::GetFromQASum($QASum{jobID}, $report_key);

  # first get the matching values
  my @matchValues = 
    QA_db_utilities::GetFromFileCatalog(\@matchCriteria, $jobID);
 
  # edit some matching values
  @matchValues = $subEditMatchValues->(@matchValues);
   
  # process the matching values into an sql string.
  my $matchClause = $subSqlMatch->(@matchValues);

  # find reference report keys
  my $queryRef = 
    qq{ select distinct $dbQA.$QASum{Table}.$QASum{report_key}
	from $dbQA.$QASum{Table},
	     $dbFile.$FileCatalog
	where 
	     $dbQA.$QASum{Table}.$QASum{jobID} = 
	       $dbFile.$FileCatalog.$joinField and
	     $dbQA.$QASum{Table}.$QASum{report_key} != '$report_key' and
	     $dbQA.$QASum{Table}.$QASum{QAdone} = 'Y' and
	     $dbQA.$QASum{Table}.$QASum{reference} = 'Y' and
	     $matchClause and
	     $dbQA.$QASum{Table}.$QASum{type} = '$type' 
	     limit $limit
	   };
  
  print $queryRef if $debug;
  return @{$dbh->selectcol_arrayref($queryRef)};
}
#-----------
# returns a hash whose keys are the matching criteria and
# whose values are the report keys.

sub GetAllDefaultReferences{
 
  # set file scope globals
  Controller();

  # add commas
  my $selectClause = 
    join(',', map { "$dbFile.$FileCatalog.$_" } @matchCriteria);

  my $orderClause = 
    "order by " . join(',', map { "$dbFile.$FileCatalog.$_" } @order);

  my $queryInfo = qq{select distinct $selectClause
		     from $dbQA.$QASum{Table},
		          $dbFile.$FileCatalog
		     where 
		          $dbQA.$QASum{Table}.$QASum{jobID} = 
			    $dbFile.$FileCatalog.$joinField and
		          $dbQA.$QASum{Table}.$QASum{type}  = '$type'
			  $orderClause
	  };
    
  print $queryInfo if $debug;
  my $sthInfo = $dbh->prepare($queryInfo);
  $sthInfo->execute();

  my (%refHash);
  tie %refHash, "Tie::IxHash";

  # get all possible matching values and store them in %refHash as the 'keys'
  while( my @match = $sthInfo->fetchrow_array){
    # edit the match values
    @match = $subEditMatchValues->(@match);
    $refHash{"@match"} = undef;
  }

  # get the references.
  # a bit inefficient, b/c i'm re-preparing the query on each 
  # iteration, but it's easier to code this way...

  foreach my $key ( keys %refHash ){
    my @matchValues = split(/\s+/, $key);
    @matchValues = $subEditMatchValues->(@matchValues);
    my $matchClause = $subSqlMatch->(@matchValues);
    my $queryRef = 
      qq{select distinct $dbQA.$QASum{Table}.$QASum{report_key}
	 from   $dbQA.$QASum{Table},
	        $dbFile.$FileCatalog
	 where 
	        $dbQA.$QASum{Table}.$QASum{jobID} = 
		  $dbFile.$FileCatalog.$joinField and
		$dbQA.$QASum{Table}.$QASum{QAdone} = 'Y' and
		$dbQA.$QASum{Table}.$QASum{reference} = 'Y' and
		$matchClause and
		$dbQA.$QASum{Table}.$QASum{type} = '$type'
	      };
    my $sthRef = $dbh->prepare($queryRef);
    $sthRef->execute();

    while (my ($report_key) = $sthRef->fetchrow_array()){
      push @{$refHash{$key}}, $report_key;
    }
  }
  
  return %refHash;
}
#-----------
# returns all default references in a hash according to the user query
# upon Select datasets.  the keys are the match values, the values
# are the report keys

sub GetDefaultReferencesByQuery{

  # set file scope globals
  Controller();

  # add commas
  my $selectClause = 
    join(',', map { "$dbFile.$FileCatalog.$_" } @matchCriteria);
  $selectClause .= " ,$dbQA.$QASum{Table}.$QASum{report_key} ";

  my $orderClause = 
    "order by " . join(',', map { "$dbFile.$FileCatalog.$_" } @order);

  # the match values are taken from the user query

  my @matchValues = 
    $subEditMatchValues->(map { $gCGIquery->param($_) } @matchCriteria );
  my $matchClause = $subSqlMatch->(@matchValues);

  my (%refHash);
  tie %refHash, "Tie::IxHash";

  my $queryRef = 
      qq{select distinct $selectClause
	 from   $dbQA.$QASum{Table},
	        $dbFile.$FileCatalog
	 where 
	        $dbQA.$QASum{Table}.$QASum{jobID} = 
		  $dbFile.$FileCatalog.$joinField and
		$dbQA.$QASum{Table}.$QASum{QAdone} = 'Y' and
		$dbQA.$QASum{Table}.$QASum{reference} = 'Y' and
		$matchClause and
		$dbQA.$QASum{Table}.$QASum{type} = '$type'
		$orderClause
	      };
  print $queryRef if $debug;
  my $sthRef = $dbh->prepare($queryRef);
  $sthRef->execute();

  while ( my @values = $sthRef->fetchrow_array()){
    my $report_key  = pop @values;
    # after pop, the remaining array should be the match values.
    # edit the match values as well.
    my @match       = $subEditMatchValues->(@values);
    push @{$refHash{"@match"}}, $report_key;
  }

  return %refHash;

}
#-----------
sub GetMatchValues{
  my $jobID = shift;

  my @matchValues = QA_db_utilities::GetFromFileCatalog([@matchCriteria],$jobID);
  return $subEditMatchValues->(@matchValues);
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

#------------
# checks if the report_key is consistent with the match values

sub ReferenceOk{
  my $report_key = shift;
  my $matchString    = shift;

  Controller();

  # clean up the report key
  $report_key = MakeNice($report_key);

  my @matchValues = split(/\s+/,$matchString);
  @matchValues = $subEditMatchValues->(@matchValues);
  my $matchClause = $subSqlMatch->(@matchValues);

  my $queryCheck = 
    qq{select $dbQA.$QASum{Table}.$QASum{report_key}
       from $dbQA.$QASum{Table},
            $dbFile.$FileCatalog
       where 
	    $dbQA.$QASum{Table}.$QASum{jobID} = 
	      $dbFile.$FileCatalog.$joinField and
	    $dbQA.$QASum{Table}.$QASum{report_key} = '$report_key' and
	    $dbQA.$QASum{Table}.$QASum{QAdone}     = 'Y' and
	    $matchClause and
	    $dbQA.$QASum{Table}.$QASum{type}       = '$type'
	  };
  print $queryCheck if $debug;

  return defined $dbh->selectrow_array($queryCheck);
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
