
#
# Written J.Lauret , July 2001
#
# Perl macro for fastOffline communication
# Changing this will change EVERY scripts
# accessing this schema. Please, be carefull.
#
# Open/Close
#      rdaq_open_rdatabase          open raw-ddb
#      rdaq_close_rdatabase         close raw-ddb
#      rdaq_open_odatabase          open o-ddb
#      rdaq_close_odatabase         close the o-ddb
#
# Function requiering open/close call
#      rdaq_raw_files               return a list of raw file from r-ddb
#      rdaq_add_entry               add one entry in the o-ddb
#      rdaq_add_entries             add entries in the o-ddb
#      rdaq_delete_entries          delete entries from the o-ddb
#      rdaq_check_entries           check entries and return an array of entries
#                                   which are suspect (i.e. does not pass the
#                                   expected conditions).
#      rdaq_list_field              Returns all possible values for field
#
#      rdaq_last_run                return the last run number from the o-ddb
#      rdaq_get_files               get a list of files with $status from o-ddb
#      rdaq_get_ffiles              get a list of characteristic ...
#      rdaq_get_orecords            basic function allowing ANY field selection
#
#      rdaq_set_files               set a list of files from o-ddb to $status
#                                   Accept both format returned by get_files
#                                   and get_ffiles.
#
# Utility (no need for any ddb to be opened)
#      rdaq_file2hpss               return an HPSS path+file (several methods)
#      rdaq_mask2string             convert a detector mask to a string
#      rdaq_status_string           returns a status string from a status val
#
# DEV ONLY *** MAY BE CHANGED AT ANY POINT IN TIME ***
#      rdaq_set_files_where         Not in its final shape.
#

use Carp;
use DBI;
use Date::Manip ();

package RunDAQ;
require 5.000;
require Exporter;
@ISA = qw(Exporter);

@EXPORT= qw( 
	     rdaq_open_rdatabase rdaq_close_rdatabase        
	     rdaq_open_odatabase rdaq_close_odatabase        
	     rdaq_raw_files rdaq_add_entry rdaq_add_entries rdaq_delete_entries 

	     rdaq_check_entries rdaq_list_field
	     rdaq_last_run 

	     rdaq_get_files rdaq_get_ffiles rdaq_get_orecords 
	     rdaq_set_files rdaq_set_files_where

	     rdaq_file2hpss rdaq_mask2string rdaq_status_string
	     );


#
# Database information
# 
$DDBSERVER = "onlsun1.star.bnl.gov";
$DDBUSER   = "starreco";
$DDBPASSWD = "";
$DDBPORT   = 3501;
$DDBNAME   = "RunLog";

$dbhost    = "duvall.star.bnl.gov";
$dbuser    = "starreco";
$dbpass    = "";
$dbtable   = "DAQInfo";
$dbname    = "operation";

$HPSSBASE  = "/home/starsink/raw/daq";        # base path for HPSS file loc.

# Required tables on $DDBSERVER 
@REQUIRED  = ("daqFileTag","daqSummary","triggerSet","beamInfo","magField");


#
# There should be NO OTHER configuration below this line but
# only composit variables or assumed fixed values.
#


# The following was dumped from detectorTypes table in the RunLog
# database.
$DETECTOR[0]="tpc";
$DETECTOR[1]="svt";
$DETECTOR[2]="tof";
$DETECTOR[3]="emc";
$DETECTOR[4]="fpd";
$DETECTOR[5]="ftpc";
$DETECTOR[6]="pmd";
$DETECTOR[7]="rich";
$DETECTOR[8]="trg";
$DETECTOR[9]="l3";
$DETECTOR[10]="sc";


# Build ddb ref here.
$DDBREF    = "DBI:mysql:$DDBNAME:$DDBSERVER:$DDBPORT";

#
# Those fields will be rounded in a get_orecords() and
# list_field() querry. It will NOT be rounded in a future
# to be implemented of set_files() or delete entries.
#
$ROUND{"scaleFactor"} = 1;
$ROUND{"BeamE"}       = 2; # does not work with 1



#
# Insert an element in the o-database.
# We accept only one entry. INEFFICIENT.
#
sub rdaq_add_entry
{
    my($obj,@values)=@_;
    my($sth);

    if(!$obj){ return 0;}
    $sth = $obj->prepare("INSERT IGNORE INTO $dbtable VALUES(?,?,?,?,?,?,?,?,?,?,0)");
    $sth->execute(@values);
    $sth->finish();
    1;
}

# enter records as returned by rdaq_raw_files
# Returns the number of added entries.
sub rdaq_add_entries
{
    my($obj,@records)=@_;
    my($sth,$line,@values);
    my($count);
   
    $count=0;
    if(!$obj){ return 0;}

    if($#records != -1){
	$sth = $obj->prepare("INSERT INTO $dbtable VALUES(?,?,?,?,?,?,?,?,?,?,0)");
	if($sth){
	    foreach $line (@records){
		@values = split(" ",$line);
		if($sth->execute(@values)){
		    $count++;
		}
	    }
	    $sth->finish();    
	}
    }
    $count;
}


#
# This method may be needed .
#
sub rdaq_delete_entries
{
    my($obj,@files)=@_;
    my($sth,$line,@values);
    my($count);

    $count=0;
    if(!$obj){ return 0;}

    $sth = $obj->prepare("DELETE FROM $dbtable WHERE file=?");
    if(!$sth){ return 0;}

    foreach $line (@files){
	#print "$line\n";
	@values = split(" ",$line);
	#print "[$values[0]]\n";
	if( $sth->execute($values[0]) ){
	    print "Successful deletion of $values[0]\n";
	    $count++;
	}
    }
    $sth->finish();
    1;
}

#
# On August 3rd, we noticed that some entries were in but should not
# have been. After some discussion, it appeared that this is caused by
# a hand-shaking problem between offline/online and especially, a
# problem when a run information is copied in the database but then
# only after marked as bad.
# FastOffline wants those entries but the final table should not have
# them. Therefore, we implemented a method to boostrap the information
# in our  $dbtable and compare it to the initial expectations.
#
# $since is a number of minutes
#
sub rdaq_check_entries
{
    my($obj,$since)=@_;
    my($tref);

    $tref = Date::Manip::DateCalc("today","-$since minutes");
    $tref = Date::Manip::UnixDate($tref,"%Y%m%H%M%S00");
    

    undef;
}


#
# Select the top element of the o-database
#
sub rdaq_last_run
{
    my($obj)=@_;
    my($sth,$val);

    if(!$obj){ return 0;}
    $sth = $obj->prepare("SELECT file FROM $dbtable ORDER BY file DESC LIMIT 1");
    $sth->execute();
    if($sth){
	$val = $sth->fetchrow();
	$sth->finish();
	$val =~ /(.*_)(\d+_)(.*)(\d+)/;
	$val = $2.$4;
	$val =~ s/_/./;
	$val;
    } else {
	0;
    }    
}

#
# Get a list of files recently added
# to the database
#
sub rdaq_raw_files
{
    my($obj,$from,$limit)=@_;
    my($sth,$cmd);
    my($stht);
    my(@all,@res);
    my($tref);

    if(!$obj){ return 0;}

    # Default values
    if( ! defined($from) ){ $from = "";}
    if( ! defined($limit)){ $limit= -1;}
    if( $from eq 0){ $from = "";}

    # An additional time-stamp selection will be made to minimize
    # a problem with database hand-shaking. This will affect only
    # the test runs with max file sequence = 1.
    $tref = Date::Manip::DateCalc("today","-1 minute");
    $tref = Date::Manip::UnixDate($tref,"%Y%m%H%M%S00");

    # Trigger selection
    $stht = $obj->prepare("SELECT detectorSet.detectorID FROM detectorSet ".
			  "WHERE detectorSet.runNumber=?");

    # We will select on RunStatus == 0
    $cmd  = "SELECT daqFileTag.file, daqSummary.runNumber, daqFileTag.numberOfEvents, daqFileTag.beginEvent, daqFileTag.endEvent, magField.current, magField.scaleFactor, beamInfo.yellowEnergy+beamInfo.blueEnergy, CONCAT(beamInfo.blueSpecies,beamInfo.yellowSpecies) FROM daqFileTag, daqSummary, magField, beamInfo  WHERE daqSummary.runNumber=daqFileTag.run AND daqSummary.runStatus=0 AND daqSummary.destinationID In(1,4) AND daqFileTag.file LIKE '%physics%' AND magField.runNumber=daqSummary.runNumber AND magField.entryTag=0 AND beamInfo.runNumber=daqSummary.runNumber AND beamInfo.entryTag=0";

    # Optional arguments
    if( $from ne ""){
	# start from some run number
	if( index($from,"_") != -1){
	    # recent format returns file sequence
	    @res = split("\.",$from);
	    $cmd .= " AND (daqSummary.runNumber > $res[0] OR ".
		" (daqSummary.runNumber=$res[0] AND daqFileTag.fileSequence > $res[1]))";
	} else {
	    # old expected a run number only
	    $cmd .= " AND daqSummary.runNumber > $from";
	}
	$cmd .= " AND daqFileTag.entryTime <= $tref";
    }
    if($limit > 0){
	$cmd .= " LIMIT $limit";
    }

    #print "$cmd\n";
    $sth  = $obj->prepare($cmd);
    $sth->execute();
    while( @res = $sth->fetchrow_array() ){
	# Massage the results to return a non-ambiguous information
	# We are still lacking 
	#print join("|",@res)."\n";
	push(@all,&rdaq_hack($stht,@res));
    }
    @all;
}

# hack for currently missing elements and information in
# database. This routine is internal only and may be 
# rehsaped at any time. However the final returned values
# should remain the same.
sub rdaq_hack
{
    my($stht,@res)=@_;
    my($run,$mask);

    # Add a default BeamBeam at the last element.
    # Will later be in beamInfo table. Use global
    # variable for spead.
    # THIS IS NOW IN THE DATABASE. Moi : Jul 20th 2001
    #push(@res,"AuAu");
    

    # Sort out trigger information. This will have to remain
    # as is.
    $run = $res[1];
    if( ! defined($DETSETS{$run}) ){
	&info_message("hack","Checking run $run\n");
	$stht->execute($run);
	if( ! $stht ){
	    &info_message("hack","$run cannot be evaluated. No SET info.\n");
	} else {
	    while( defined($line = $stht->fetchrow() ) ){
		$mask |= 1 << $line;
	    }
	}
	$DETSETS{$run} = $mask;
    } else {
	$mask = $DETSETS{$run};
    }
    push(@res,$mask);

    join(" ",@res);
}



# This is going to be entirely mysql-based
# so no need for a handler.
sub rdaq_open_rdatabase
{
    my($obj);
    my($i,$cmd,$sth);

    $obj = DBI->connect($DDBREF,$DDBUSER,$DDBPASSWD,
			{PrintError  => 0, AutoCommit => 1,
			 ChopBlanks  => 1, LongReadLen => 200});
    if(!$obj){
	return 0;
    }

    # Else fine, it is opened
    # check presence of tables
    for($i=0 ; $i <= $#REQUIRED ; $i++){
	$sth = $obj->prepare("SELECT * FROM $REQUIRED[$i] LIMIT 1");
	if(! $sth->execute() ){
	    &info_message("open_database","Required Database $REQUIRED[$i] does not exists\n");
	    $obj->disconnect();
	    return 0;
	}
	$sth->finish();
    }

    # return object
    return $obj;
}
sub rdaq_close_rdatabase
{
    my($obj)=@_;
    if(!$obj){ 
	return 0;
    } else {
	$obj->disconnect();
	1;
    }
}

sub rdaq_close_odatabase
{
    my($obj)=@_;

    if(!$obj){ 
	return 0;
    } else {
	$obj->disconnect();
	1;
    }
}

sub rdaq_open_odatabase
{
   my($obj);
   
   $obj = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass,
			{PrintError  => 0, AutoCommit => 1,
			 ChopBlanks  => 1, LongReadLen => 200});
   return $obj;
}

#
# Scans o-database and returns a list of
# files which have status $status. 
# The parameters are
#    status    may be -1 for all status
#    limit     -1 for no limit
#    mode      0 for the file name only, 
#              all fields are otherwise
#              returned.
#    conds     A reference to an hash array
#              for extraneous condition selection.
#
# The list will be given in a descending ordered 
# array (first file is last saved to HPSS).
#
# Return full list (i.e. all columns from o-ddb)
#
sub rdaq_get_ffiles
{
    my($obj,$status,$limit)=@_;
    return &rdaq_get_files($obj,$status,$limit,1);
}

sub rdaq_get_files
{
    my($obj,$status,$limit,$mode)=@_;
    my(%Conds);
    
    # Default values will be sorted out here.
    if( ! defined($limit) ){  $limit = 0;}
    if( ! defined($mode)  ){  $mode  = 0;}
    if( ! defined($status) ){ $status= 0;}

    # We MUST pass a reference to a hash. 
    $Conds{"Status"} = $status;
    return &rdaq_get_orecords($obj,\%Conds,$limit,$mode);
}

#
# Because of a later version of this (evoluated from get_files()),
# and for backward compatibility, we need to support the options 
# described above .
# This basic fundamental function DOES NOT support default values
# so it needs to be sorted out prior to this call.
#
sub rdaq_get_orecords
{
    my($obj,$Conds,$limit,$mode)=@_;
    my($cmd,$el,$val,$sth);
    my(@Values);
    my($file,@files,@items);

    if(!$obj){ return undef;}

    # basic selection
    $cmd = "SELECT * FROM $dbtable";


    # backward compatibility is status selection where -1 = all
    # may be achieved by skipping hash element.
    foreach $el (keys %$Conds){
	$val = $$Conds{$el};
	if( $el eq "Status" && $val == -1){ next;}

	if( defined($ROUND{$el}) ){
	    $val = "ROUND($el,$ROUND{$el})";
	} else {
	    $val = $el;
	}
	if($cmd !~ /WHERE/){
	    $cmd .= " WHERE $val=?";
	} else  {
	    $cmd .= " AND $val=?";
	}
	push(@Values,$$Conds{$el});
    }
    $cmd .= " ORDER BY file DESC";
    if( $limit > 0){	            
	$cmd .= " LIMIT $limit";
    }


    #print "DEBUG : [$cmd] [@Values]\n";
    $sth = $obj->prepare($cmd);
    $sth->execute(@Values);
    if ($sth){
	while ( @items = $sth->fetchrow_array() ){
	    if($mode == 0){
		$file = $items[0];
	    } else {
		$file = join(" ",@items);
		chomp($file);
	    }
	    push(@files,$file);
	}
    }
    @files;
}


# This method is a backward support for the preceeding method
# which allowed setting status without condition. Now, we
# also support WHERE Status= cases.
sub rdaq_set_files
{
    my($obj,$status,@files)=@_;
    return rdaq_set_files_where($obj,$status,-1,@files);
}


# Set the status for a list of files
sub rdaq_set_files_where
{
    my($obj,$status,$stscond,@files)=@_;
    my($sth,$success,$cmd);
    my(@items);
    
    if(!$obj){ return 0;}

    $success = 0;
    $cmd = "UPDATE $dbtable SET Status=$status WHERE file=? ";
    if ($stscond != -1){
	$cmd .= " AND Status=$stscond";
    }

    $sth = $obj->prepare($cmd);
    if($sth){
	foreach $file (@files){
	    # support for list of files or full list.
	    $file = (split(" ",$file))[0];  
	    if($sth->execute($file)){
		$success++;
	    }
	}
	$sth->finish();
    }
    $success;
}

#
# Returns all possible values for a given field
# BEWARE of some querries which may return a long-long list ...
# 
#
sub rdaq_list_field
{
    my($obj,$field,$limit)=@_;
    my($cmd,$sth,@tmp);
    my($val,$pval);
    my($i,@all);

    if(!$obj){ return 0;}
    if( ! defined($limit) ){ $limit = 0;}

    # The association of DISTINCT and ROUND is apparently
    # unsafe. It works for 'scaleFactor' but not for 'BeamE' (??).
    # We will therefore make the unicity ourselves.
    if( defined($ROUND{$field}) ){
	$cmd = "SELECT DISTINCT ROUND($field,$ROUND{$field}) FROM $dbtable";
    } else {
	$cmd = "SELECT DISTINCT $field FROM $dbtable";
    }
    $cmd .= " ORDER BY $field DESC";
    #print "$cmd\n";

    $sth = $obj->prepare($cmd);
    if($sth){
	if($sth->execute()){
	    #print "Execute = success. Fetching.\n";
	    $i   = 0;
	    $pval= "";
	    while ( @tmp = $sth->fetchrow_array() ){
		#print "Debug :: @tmp\n";
		chomp($val = join("",@tmp));
		if( $val ne $pval){
		    $pval = $val;
		    push(@all,$val);
		    $i++;
		}
		if($i == $limit){ last;}
	    }
	} else {
	    &info_message("list_field","Execute failed for $field");
	}
	$sth->finish();
    } else {
	&info_message("list_field","[$cmd] could no be prepared");
    }
    @all;
}


# --------------------
# Utility routines.
# --------------------

#
# Returns the status string for a given entry.
#
sub rdaq_status_string
{
    my($sts)=@_;
    my($str);

    $str = "Unknown";
    $str = "Recorded"  if($sts == 0);
    $str = "Submitted" if($sts == 1);
    $str = "Processed" if($sts == 2);
    $str = "QADone"    if($sts == 3); # i.e. + QA

    $str;
}

# Provide a decoding method for the above
# built mask, We can hardcode values (they
# won't change);
sub rdaq_mask2string
{
    my($mask)=@_;
    my($st);

    if( ! defined($MASKS[$mask]) ){
	# build string
	for($i=0; $i <= $#DETECTOR ; $i++){
	    if( ($mask & (1 << $i)) >> $i ){
		$st .= ".$DETECTOR[$i]";
	    }
	}
	$st =~ s/\.//;
	$MASKS[$mask] = $st;
    } else {
	# fast = in memory
	$st = $MASKS[$mask];
    }
    $st;
}

#
# Accept a raw name, return a fully specified HPSS path
# file name.
# Mode 0 -> return 'path/file' (default)
# Mode 1 -> return 'path file' (i.e. with space)
# Mode 2 -> return 'path file year month'
#           month is calculated.
# 
# May implement other modes ...
#
sub rdaq_file2hpss
{
    my($file,$mode)=@_;
    my($Hfile,$code);
    my($y,$dm,$n,@items);

    # default
    if( ! defined($mode) ){ $mode = 0;}

    # reduce the a file list (all characteristics) to a file-only
    $file  = (split(" ",$file))[0];

    # parse the damned file name. This is really trivial but
    # good to put it in a module so we can bacward support Y1
    # convention if necessary.
    #            -----v  may be a | list
    $file =~ m/(st_)(\w+_)(\d+)(_.*)/;
    $code = $3;

    ($y,$dm,$n) = $code =~ m/(\d)(\d{3,})(\d{3,})/;
    $y += 1999;
    if($y <= 2000){
	# The default path is to store by month
	# We are NOT taking care of exceptions ...
	@items = Date::Manip::Date_NthDayOfYear($y,$dm);
	my($y1path)=sprintf("%s/%s/%2.2d",$HPSSBASE,$y,$items[1]);

	if($mode == 1){
	    "$y1path $file";
	} elsif ($mode == 2){
	    "$y1path $file $y $items[1]";
	} else {
	    "$y1path/$file"; 
	}
    } else {
	# the default option is to store by day-of-year
	if($mode==1){
	    "$HPSSBASE/$y/$dm $file";
	} elsif ($mode == 2){
	    @items = Date::Manip::Date_NthDayOfYear($y,$dm);
	    "$HPSSBASE/$y/$dm $file $y $items[1]";
	} else {
	    "$HPSSBASE/$y/$dm/$file";
	}
    }
}


#
# Some utility / cut-n-paste
#
sub	info_message
{
    my($routine,@messages) = @_;
    my($mess);
 
    foreach $mess (@messages){
	printf "FastOffl :: %10.10s : %s",$routine,$mess;
    }
}
 
 
1;
 


