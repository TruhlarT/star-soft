
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
# Function requirring open/close call
#      rdaq_raw_files               return a list of raw file from r-ddb
#      rdaq_add_entry               add one entry in the o-ddb
#      rdaq_add_entries             add entries in the o-ddb
#      rdaq_last_run                return the last run number from the o-ddb
#      rdaq_get_files               get a list of files with $status from o-ddb
#      rdaq_get_ffiles              get a list of characteristic ...
#      rdaq_set_files               set a list of files from o-ddb to $status
#                                   Accept both format returned by get_files
#                                   and get_ffiles.
#
# Utility (no need for any ddb to be opened)
#      rdaq_file2hpss               return an HPSS path+file (several methods)
#      rdaq_mask2string             convert a detector mask to a string
#
# DEV ONLY
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
	     rdaq_raw_files rdaq_add_entry rdaq_add_entries            
	     rdaq_last_run rdaq_get_files rdaq_get_ffiles rdaq_set_files
	     rdaq_set_files_where

	     rdaq_file2hpss rdaq_mask2string
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
# Select the top element of the o-database
#
sub rdaq_last_run
{
    my($obj)=@_;
    my($sth);

    if(!$obj){ return 0;}
    $sth = $obj->prepare("SELECT * FROM $dbtable ORDER BY file DESC LIMIT 1");
    $sth->execute();
    if($sth){
	@res = $sth->fetchrow_array();
	$sth->finish();
	$res[1];
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

    if(!$obj){ return 0;}

    # Default values
    if( ! defined($from) ){ $from = "";}
    if( ! defined($limit)){ $limit= -1;}

    # Trigger selection
    $stht = $obj->prepare("SELECT detectorSet.detectorID FROM detectorSet ".
			  "WHERE detectorSet.runNumber=?");

    # We will select on RunStatus == 0
    $cmd  = "SELECT daqFileTag.file, daqSummary.runNumber, daqFileTag.numberOfEvents, daqFileTag.beginEvent, daqFileTag.endEvent, magField.current, magField.scaleFactor, beamInfo.yellowEnergy+beamInfo.blueEnergy, CONCAT(beamInfo.blueSpecies,beamInfo.yellowSpecies) FROM daqFileTag, daqSummary, magField, beamInfo  WHERE daqSummary.runNumber=daqFileTag.run AND daqSummary.runStatus=0 AND daqSummary.destinationID In(1,4) AND daqFileTag.file LIKE '%physics%' AND magField.runNumber=daqSummary.runNumber AND magField.entryTag=0 AND beamInfo.runNumber=daqSummary.runNumber AND beamInfo.entryTag=0";

    # Optional arguments
    if( $from ne ""){
	# start from some run number
	$cmd .= " AND daqSummary.runNumber > $from";
    }
    if($limit > 0){
	$cmd .= " LIMIT $limit";
    }

    $sth  = $obj->prepare($cmd);
    $sth->execute();
    while( @res = $sth->fetchrow_array() ){
	# Massage the results to return a non-ambiguous information
	# We are still lacking 
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
# files which have status $status. A limit
# number of files may be required. 
# -1 for all. The list will be given in 
# a descending order array (first file
# is last saved to HPSS).
#
# Return full list (i.e. all columns from o-ddb)
sub rdaq_get_ffiles
{
    my($obj,$status,$limit)=@_;
    return &rdaq_get_files($obj,$status,$limit,1);
}
# return only a list of files (i.e. column file from o-ddb)
sub rdaq_get_files
{
    my($obj,$status,$limit,$mode)=@_;
    my($cmd,$sth);
    my($file,@files,@items);

    if(!$obj){ return undef;}

    # default values
    if( ! defined($status) ){ $status = 0;}
    if( ! defined($limit) ) { $limit  = 0;}
    if( ! defined($mode)  ) { $mode   = 0;}

    if($status == -1){
	$cmd = "SELECT * FROM $dbtable ORDER BY file DESC";
    } else {
	$cmd = "SELECT * FROM $dbtable WHERE Status=$status ORDER BY file DESC";
    }
    if($limit > 0){
	$cmd .= " LIMIT $limit";
    }

    #print "DEBUG : [$cmd]\n";
    $sth = $obj->prepare($cmd);
    $sth->execute();
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




# --------------------
# Utility routines.
# --------------------

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
    $file =~ m/(st_)(physics_)(\d+)(_.*)/;
    $code = $3;

    ($y,$dm,$n) = $code =~ m/(\d)(\d{3,})(\d{3,})/;
    $y += 1999;
    if($y <= 2000){
	&info_message("file_to_hpss","Y1 not yet supported\n");
	"";
    } else {
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
 
 
 
