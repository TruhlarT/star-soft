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
#      rdaq_list_field              Returns all possible values for give record
#      rdaq_set_location            Set the disk location field for a give record
#      rdaq_get_location            gets the output directory location if any.
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
#      rdaq_status_string           returns a status string from a status val
#      rdaq_bits2string             Returns a string from a bitfield.
#      rdaq_mask2string             Returns detector set from detector BitMask.
#      rdaq_trgs2string             Return trigger Setup name
#      rdaq_ftype2string            Return file type/flavor name
#      rdaq_toggle_debug            Turn ON/OFF SELECT of raw data.
#
#
# DEV ONLY *** MAY BE CHANGED AT ANY POINT IN TIME ***
#      rdaq_set_files_where         Not in its final shape.
#      rdaq_update_entries          For maintainance ONLY
#
#
# Internal
#      GetBitValue                  Returns the bit position for a given variable
#                                   saved in a given table. If the second argument
#                                   is 1, the value is added to the list of possible
#                                   ones.
#      Record_n_Fetch               Base routine to save a string record in an
#                                   associated array and return the index.
#
#
# HowTo add a field
#  Adding a field with a plain type is easy. Just ALTER the table, modify
#  VALUES() and add a ?, modify the hack routine to make this field
#  appear at the proper place, eventually modify the MAINTAINER only
#  routine update_entries to initialize the column, and save ... Status
#  column is always expected to be the last field. For readability,
#  add fields before EntryDate (see the NOW()+0,0,0).
#
#  For a BITWISE field, do the same AND, in addition, add a
#  hash value for that column. The value MUST be a valid existing
#  table you can create using
#  > create table $TBLName (id INT NOT NULL AUTO_INCREMENT, Label CHAR(50) NOT NULL,
#  PRIMARY KEY(id), UNIQUE(Label));
#  The fields of that extra table are expected to be EXACTLY as above i.e. there
#  are all standardized to avoid proliferation of routines. THERE is nothing else
#  to do at this level.
#
#  If you have build a script based on get_ffiles() or get_orecords(), you will
#  need to take into account the fact that the number of fields is larger. The
#  last field of DAQInfo is expected to be 'Status'. Please, preserve this ...
#
# The full DAQInfo table description is as follow (last dumped, Dec 2001). Other
# tables are of trivial format (i.e. and int id and a char label).
#
# +-------------+---------------------+------+-----+---------+-------+
# | Field       | Type                | Null | Key | Default | Extra |
# +-------------+---------------------+------+-----+---------+-------+
# | file        | char(255)           |      | PRI |         |       |
# | runNumber   | int(10)             |      |     | 0       |       |
# | NumEvt      | int(10)             | YES  |     | NULL    |       |
# | BeginEvt    | int(10)             | YES  |     | NULL    |       |
# | EndEvt      | int(10)             | YES  |     | NULL    |       |
# | Current     | float(16,8)         | YES  |     | NULL    |       |
# | scaleFactor | float(16,8)         | YES  |     | NULL    |       |
# | BeamE       | float(16,8)         | YES  |     | NULL    |       |
# | Collision   | char(10)            | YES  |     | NULL    |       |
# | DetSetMask  | bigint(20) unsigned | YES  |     | 0       |       |
# | TrgSetup    | bigint(20) unsigned | YES  |     | 0       |       |
# | TrgMask     | bigint(20) unsigned | YES  |     | 0       |       |
# | ftype       | int(11)             | YES  |     | 0       |       |
# | EntryDate   | timestamp(14)       | YES  |     | NULL    |       |
# | DiskLoc     | int(11)             | YES  |     | 0       |       |
# | Status      | int(11)             | YES  |     | 0       |       |
# +-------------+---------------------+------+-----+---------+-------+
#
#
#
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
	    rdaq_set_location rdaq_get_location
	    rdaq_delete_entries

	    rdaq_check_entries rdaq_list_field
	    rdaq_last_run

	    rdaq_get_files rdaq_get_ffiles rdaq_get_orecords
	    rdaq_set_files

	    rdaq_file2hpss rdaq_mask2string rdaq_status_string
	    rdaq_bits2string rdaq_trgs2string rdaq_ftype2string
	    rdaq_toggle_debug 

	    rdaq_set_files_where rdaq_update_entries

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
# List for Year2
#@REQUIRED  = ("daqFileTag","daqSummary",
#	      "triggerSet","detectorSet",
#	      "beamInfo","magField");
# List for Year3
@REQUIRED  = ("daqFileTag","daqSummary",
	      "l0TriggerSet","detectorSet",
	      "beamInfo","magField");



#
# There should be NO OTHER configuration below this line but
# only composit variables or assumed fixed values.
#
$DEBUG     = 0;

# Build ddb ref here.
$DDBREF    = "DBI:mysql:$DDBNAME:$DDBSERVER:$DDBPORT";

#
# Those fields will be rounded in a get_orecords() and
# list_field() querry. It will NOT be rounded in a future
# to be implemented of set_files() or delete entries.
#
$ROUND{"scaleFactor"} = 1;
$ROUND{"BeamE"}       = 1; # does not work with 1


#
# Those fields are indicative of a bitmask operation.
# A bitwise operation will affect the functions as
# described above. The value of this hash array is
# the table name containing the bit position ...
#
$BITWISE{"TrgMask"}    = "FOTriggerBits";
$BITWISE{"DetSetMask"} = "FODetectorTypes";

#
# For list_field, we may want to select from secondary
# tables instead of from $dbtable. We can do this only
# if the fields are associated with a threaded table.
# Those tables are assumed to be id,Label. The index
# 0 or 1 indicates if we select by id or label in the
# list_field() routine returned values.
$THREAD0{"TrgSetup"} = "FOTriggerSetup";
$THREAD0{"ftype"}    = "FOFileType";
$THREAD1{"runNumber"}= "FOruns";


#
# Insert an element in the o-database.
# We accept only one entry. INEFFICIENT.
#
sub rdaq_add_entry
{
    my($obj,@values)=@_;
    my($sth);

    if(!$obj){ return 0;}
    $sth = $obj->prepare("INSERT IGNORE INTO $dbtable ".
			 "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,NOW()+0,0,0)");
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
	$sth = $obj->prepare("INSERT INTO $dbtable ".
			     "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,NOW()+0,0,0)");
	if($sth){
	    foreach $line (@records){
		@values = split(" ",$line);
		if ($sth->execute(@values)){
		    $count++;
		} else {
		    &info_message("add_entries","Failed to add [$line] ".
				  $sth->errstr."\n");
		}
	    }
	    $sth->finish();
	} else {
	    &info_message("add_entries","Failed to prepare sentence\n");
	}
    }
    $count;
}


#
# Update a few field. This routine serves whenever we add a column and
# want to have a specific field updated. This has to be done manually.
#
sub rdaq_update_entries
{
    my($obj,@records)=@_;
    my($sth,$line,@values);
    my($count);

    $count=0;
    if(!$obj){  return 0;}

    if($#records != -1){
	$sth = $obj->prepare("UPDATE $dbtable SET scaleFactor=?, ".
			     "DetSetMask=?, TrgSetup=?, TrgMask=?, ftype=?".
			     "WHERE file=?");
	if($sth){
	    foreach $line (@records){
		@values = split(" ",$line);
		if($sth->execute($values[6],
				 $values[9],$values[10],$values[11],$values[12],
				 $values[0]) ){
		    $count++;
		}
	    }
	    $sth->finish();
	} else {
	    &info_message("update_entries","prepare() failed\n");
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
# Sets the output directory location for this entry
#
sub rdaq_set_location
{
    my($obj,$loc,@values)=@_;
    my($file,$val);
    my($sth,$sth2);

    if(!$obj){  return 0;}

    # sort out if there is something in the hash array for that
    # location. Special case is undef which is reserved for
    # 'not stored on disk'.
    if( defined($loc) ){
	$val = &Record_n_Fetch("FOLocations",$loc);
    } else {
	$val = 0;
    }

    $file= shift(@values);
    $sth = $obj->prepare("UPDATE $dbtable SET DiskLoc=? WHERE file=?");
    return $sth->execute($val,$file);
}

# get the outpur directory location
sub rdaq_get_location
{
    my($obj,@values)=@_;
    my($sth,$val);

    if(!$obj){  return 0;}

    $file= shift(@values);
    $sth = $obj->prepare("SELECT FOLocations.Label FROM FOLocations,$dbtable ".
			 "WHERE FOLocations.id=$dbtable.DiskLoc AND ".
			 "$dbtable.file=?");
    if($sth){
	$sth->execute($file);
	if( ! defined($val = $sth->fetchrow() ) ){
	    $val = 0;
	}
	$sth->finish();
    }
    $val;
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
    my(@all);

    #$tref = Date::Manip::DateCalc("today","-$since minutes");
    #$tref = Date::Manip::UnixDate($tref,"%Y%m%e%H%M%S");

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
    $sth = $obj->prepare("SELECT file FROM $dbtable ORDER BY runNumber DESC, file DESC LIMIT 1");
    $sth->execute();
    if( $sth ){
	$val = $sth->fetchrow();
	if ( defined($val) ){
	    $sth->finish();
	    $val =~ /(.*_)(\d+_)(.*_)(\d+)/;
	    $val = $2.$4;
	    $val =~ s/_/./;
	    $val;
	} else {
	    $val = 0;
	}
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
    my(@all,@res);
    my($tref,$kk);

    if(!$obj){ return 0;}

    # Default values
    if( ! defined($from) ){ $from = "";}
    if( ! defined($limit)){ $limit= -1;}
    if( $from eq 0){ $from = "";}

    # An additional time-stamp selection will be made to minimize
    # a problem with database hand-shaking. This will affect only
    # the test runs with max file sequence = 1.
    #$tref = Date::Manip::DateCalc("today","-1 minute");
    #$tref = Date::Manip::UnixDate($tref,"%Y%m%e%H%M%S");
    $sth = $obj->prepare("select FROM_UNIXTIME( UNIX_TIMESTAMP(NOW())-60 )+0");
    $sth->execute();
    $tref= $sth->fetchrow();
    $sth->finish();
    

    # We will select on RunStatus == 0
    # Year2
    #$cmd  = "SELECT daqFileTag.file, daqSummary.runNumber, daqFileTag.numberOfEvents, daqFileTag.beginEvent, daqFileTag.endEvent, magField.current, magField.scaleFactor, beamInfo.yellowEnergy+beamInfo.blueEnergy, CONCAT(beamInfo.blueSpecies,beamInfo.yellowSpecies) FROM daqFileTag, daqSummary, magField, beamInfo  WHERE daqSummary.runNumber=daqFileTag.run AND daqSummary.runStatus=0 AND daqSummary.destinationID In(1,2,4) AND magField.runNumber=daqSummary.runNumber AND magField.entryTag=0 AND beamInfo.runNumber=daqSummary.runNumber AND beamInfo.entryTag=0";
    # One more table runStatus, daqSummary.runStatus=0 gone, entryTag=5 for hardwired values
    $cmd   = "SELECT daqFileTag.file, daqSummary.runNumber, daqFileTag.numberOfEvents,daqFileTag.beginEvent, daqFileTag.endEvent, magField.current,magField.scaleFactor, beamInfo.yellowEnergy+beamInfo.blueEnergy,CONCAT(beamInfo.blueSpecies,beamInfo.yellowSpecies) FROM daqFileTag,daqSummary, magField, beamInfo,runStatus WHERE daqSummary.runNumber=daqFileTag.run AND daqSummary.destinationID In(1,2,4) AND runStatus.runNumber=daqFileTag.run and runStatus.rtsStatus=0 AND magField.runNumber=daqSummary.runNumber AND magField.entryTag=5 AND beamInfo.runNumber=daqSummary.runNumber AND beamInfo.entryTag=5";
 

    # Optional arguments
    if( $from ne ""){
	# start from some run number
	if( index($from,"\.") != -1){
	    # recent format returns file sequence
	    @res = split(/\./,$from);
	    $cmd .= " AND (daqSummary.runNumber > $res[0] OR ".
		" (daqSummary.runNumber=$res[0] AND daqFileTag.fileSequence > $res[1]))";
	} elsif ( $from =~ /=/){
	    $cmd .=  " AND daqSummary.runNumber $from";
	} else {
	    # old expected a run number only
	    $cmd .= " AND daqSummary.runNumber > $from";
	}
	$cmd .= " AND daqFileTag.entryTime <= $tref";
    }
    if($limit > 0){
	$cmd .= " LIMIT $limit";
    }

    print "$cmd\n" if ($DEBUG);
    $sth  = $obj->prepare($cmd);
    $sth->execute();
    $kk=0;
    while( @res = $sth->fetchrow_array() ){
	# Massage the results to return a non-ambiguous information
	# We are still lacking
	push(@all,&rdaq_hack($obj,@res));
	$kk++;
	if( $kk % 10000 == 0){ 
	    # always output debug lines in HTML comment format
	    # since this may be used in a CGI.
	    print "<!-- Fetched $kk records -->\n" if ($DEBUG);
	}
    }
    $sth->finish();
    @all;
}

# hack for currently missing elements and information in
# database. This routine is internal only and may be
# rehsaped at any time. However the final returned values
# should remain the same.
sub rdaq_hack
{
    my($obj,@res)=@_;
    my($stht,$sthl,$sths);
    my(@items,$line,$run,$mask);


    # Add a default BeamBeam at the last element.
    # Will later be in beamInfo table. Use global
    # variable for spead.
    # THIS IS NOW IN THE DATABASE. Moi : Jul 20th 2001
    #push(@res,"AuAu");


    # Dataset selection, the DetectorTypes was filled by hand.
    $stht = $obj->prepare("SELECT detectorTypes.name FROM detectorTypes, detectorSet ".
			  "WHERE detectorSet.detectorID=detectorTypes.detectorID AND ".
			  "detectorSet.runNumber=?");

    # Trigger label
    # Year2
    #$sthl = $obj->prepare("SELECT triggerLabel,numberOfEvents FROM triggerSet ".
    #			  "WHERE runNumber=? ORDER BY triggerLabel DESC");
    # Year3
    $sthl = $obj->prepare("SELECT name,numberOfEvents FROM l0TriggerSet ".
			  "WHERE runNumber=? ORDER BY name DESC");

    # Trigger Setup
    $sths = $obj->prepare("SELECT glbSetupName FROM runDescriptor ".
			  "WHERE runNumber=? ORDER BY glbSetupName DESC");


    #
    # Sort out Dataset information. This will have to remain
    # as is.
    #
    $run = $res[1];
    &Record_n_Fetch("FOruns","$run");

    if( ! defined($DETSETS{$run}) ){
	#&info_message("hack","Checking DataSet for run $run\n");
	$stht->execute($run);
	if( ! $stht ){
	    &info_message("hack","$run cannot be evaluated. No DataSET info.\n");
	} else {
	    $mask = 0;
	    while( defined($line = $stht->fetchrow() ) ){
		$mask |= (1 << &GetBitValue("DetSetMask",$line));
	    }
	}
	$DETSETS{$run} = $mask;
    } else {
	$mask = $DETSETS{$run};
    }
    push(@res,$mask);


    #
    # This block is for the TriggerSetup
    #
    if( ! defined($TRGSET{$run}) ){
	#&info_message("hack","Checking TrgMask for run $run -> ");
	$mask = 0;
	$sths->execute($run);
	if( ! $sths ){
	    &info_message("hack","$run cannot be evaluated. No TriggerSetup info.\n");
	    $mask = 0;
	} else {
	    $mask = "";
	    while( defined($line = $sths->fetchrow()) ){
		$mask .= $line.".";
	    } 
	    chop($mask);
	    $mask = &Record_n_Fetch("FOTriggerSetup",$mask);
	}
	$TRGSET{$run} = $mask;
    } else {
	$mask = $TRGSET{$run};
    }
    push(@res,$mask);


    #
    # Now, add to this all possible trigger mask
    #
    if( ! defined($TRGMASK{$run}) ){
	#&info_message("hack","Checking TrgMask for run $run -> ");
	$mask = 0;
	$sthl->execute($run);
	if( ! $sthl ){
	    &info_message("hack","$run cannot be evaluated. No TriggerLabel info.\n");
	    $mask = 0;
	} else {
	    while( @items = $sthl->fetchrow_array() ){
		if($items[1] != 0){
		    $mask |= (1 << &GetBitValue("TrgMask",$items[0]));
		}
	    }
	}
	$TRGMASK{$run} = $mask;
    } else {
	$mask = $TRGMASK{$run};
    }
    # if we want to ensure that only good-runs (i.e. marked as such) are
    # taken, we can return 'undef' if mask==0. However, if we need Fastoffline
    # to check this run as we go, we want them ...
    push(@res,$mask);

    # File name is the first field 0
    if( $res[0] =~ m/(st_)(\w+)(_\d+_raw)/ ){
	push(@res,&Record_n_Fetch("FOFileType",$2));
    } else {
	push(@res,0);
    }
    
    return join(" ",@res);
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
#    ftype     Late addition. Has to be something
#              like 'laser' 'physics' 'pulser'.
#              Default is 'physics'. Late addition.
#
# The list will be given in a descending ordered
# array (first file is last saved to HPSS).
#
# Return full list (i.e. all columns from o-ddb)
#
sub rdaq_get_ffiles
{
    my($obj,$status,$limit,$ftype)=@_;
    return &rdaq_get_files($obj,$status,$limit,1,$ftype);
}

sub rdaq_get_files
{
    my($obj,$status,$limit,$mode,$ftype)=@_;
    my(%Conds);

    # Default values will be sorted out here.
    if( ! defined($limit) ){  $limit = 0;}
    if( ! defined($mode)  ){  $mode  = 0;}
    if( ! defined($status)){  $status= 0;}
    if( ! defined($ftype) ){  $ftype = 1;}

    # We MUST pass a reference to a hash.
    #if($status < 0){ $status = 0;}
    $Conds{"Status"} = $status;
    $Conds{"ftype"}  = $ftype;

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
    my($cmd,$el,$val,$tmp,$sth);
    my(@Values);
    my($file,@files,@items);
    my($flag,$comp);

    if(!$obj){ return undef;}
    if( ! defined($mode) ){ $mode = 1;}

    # basic selection
    $cmd = "SELECT * FROM $dbtable";


    # backward compatibility is status selection where -1 = all
    # may be achieved by skipping hash element.
    foreach $el (keys %$Conds){
	$comp= "=";
	$val = $$Conds{$el};

	# do NOT build a querry for a 'all' keyword
	if( ! defined($val) ){ 
	    &info_message("get_orecords","[$el] has an undef value"); 
	    next;
	}
	if( $el eq "Status" && $val == -1){ next;}
	

	# Sort out possible comparison operators
	$test= substr($val,0,1);
	$comp= ">=" if($test eq ">");
	$comp= "<=" if($test eq "<");
	$comp= "!=" if($test eq "!");
	if($comp ne "="){
	    $val = substr($val,1,length($val));
	    $$Conds{$el} = $val;
	}


	# Sort out now the kind of field we are working with
	$flag = 1;

	if( defined($ROUND{$el}) ){                # Round OFF value selection
	    $val = "ROUND($el,$ROUND{$el})";
	} elsif ( defined($BITWISE{$el}) ){	   # BITWISE selection
	    $flag= 0;
	    $tmp = (split(":",$val))[0];
	    if( $tmp == 0){
		$val = "($el = 0)";
	    } else {
		$val = "($el & (1 << $tmp))";
	    }
	} elsif ( index($val,"|") != -1){          # OR syntax in selection
	    #print "<!-- Received $val -->\n";
	    @items = split(/\|/,$val);
	    $val = "(";
	    foreach $tmp (@items) {
		$val .= "$el=$tmp OR ";
	    }
	    $val = substr($val,0,length($val)-3).")";
	    #print "<!-- $val -->\n";
	    undef(@items);
	    $flag = 0;
	} else {                                   # Default selection
	    $val = $el;
	}


	# check WHERE keyword presence or not
	if($cmd !~ /WHERE/){
	    $cmd .= " WHERE $val";
	} else  {
	    $cmd .= " AND $val";
	}
	# check if selection is completely defined
	# or not.
	if( $flag){
	    $cmd .= "$comp?";
	    push(@Values,$$Conds{$el});
	} else {
	    # the syntax is a bit operation or a OR/AND
	    # syntax and therefore is complete
	}

    }

    # order 
    $cmd .= " ORDER BY runNumber DESC, file DESC";
    if( $limit > 0){
	$cmd .= " LIMIT $limit";
    }


    #print "<!-- DEBUG : [$cmd] [@Values] -->\n";
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
	$cmd   = "SELECT DISTINCT ROUND($field,$ROUND{$field})".
	    " AS SELECTED FROM $dbtable";
	$cmd  .= " ORDER BY SELECTED DESC";
    } elsif ( defined($BITWISE{$field}) ) {
	# this works fine
	$cmd   = "SELECT CONCAT(id,':',Label) FROM $BITWISE{$field}";
	$field = "id";
	$cmd  .= " ORDER BY $field DESC";
    } elsif ( defined($THREAD0{$field}) ){
	$cmd   = "SELECT id FROM $THREAD0{$field}";
	$cmd  .= " ORDER BY Label DESC";
    } elsif ( defined($THREAD1{$field}) ){
	$cmd   = "SELECT Label FROM $THREAD1{$field}";
	$cmd  .= " ORDER BY Label DESC";
    } else {
	$cmd   = "SELECT DISTINCT $field AS SELECTED FROM $dbtable";
	$cmd  .= " ORDER BY $field DESC";
    }

    #print "<!-- $cmd -->\n";

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
	    &info_message("list_field","Execute failed for $field\n");
	}
	$sth->finish();
    } else {
	&info_message("list_field","[$cmd] could no be prepared\n");
    }
    @all;
}


# --------------------
# Utility routines.
# --------------------
#
# Returns the bit placement for a BITWISE field.
# A return value of 0 will mean bit 0 set to 1
# and indicate an unknown trigger (missing info
# in the table).
#
sub GetBitValue
{
    my($field,$el)=@_;
    my($tbl,$rv,$sthc,$oobj);

    if( $field eq ""){                       return 0; }
    if( $el    eq ""){                       return 0; }

    # Get the table name from the BITWISE hash configuration
    if( ! defined($tbl = $BITWISE{$field})){ return 0; }

    return &Record_n_Fetch($tbl,$el);
}

#
# Fundamental routine saving/fetching the id of a record
# defined by its descriptor or label. Requires a database
# object handler.
# Returns 0 if any failures.
# Hashes the values to save later processing time.
# $mode if 1, disables insertion of new values.
#
sub Record_n_Fetch
{
    my($tbl,$el)=@_;
    my($obj,$sthc,$val,$rv);

    # cannot insert a null value
    if($el eq ""){  return 0;}
    if($el eq 0){   return 0;}

    #print "Record_n_Fetch :: $tbl $el\n"  if ($tbl eq "FOFileType");

    if( ! defined($rv = $RFETCHED{"$tbl-$el"}) ){
	# Return value
	#if($tbl eq "FOruns"){
	#    print "<!-- Adding $el -->";
	#}
	$rv  = 0;
	$obj = rdaq_open_odatabase();

	if(!$obj){ return $rv;}


	# Quick and dirty insert
	$sthc = $obj->prepare("INSERT IGNORE INTO $tbl VALUES(0,'$el')");
	$sthc->execute();
	$sthc->finish();


	# fetch now.
	$sthc = $obj->prepare("SELECT $tbl.id FROM $tbl ".
			      "WHERE $tbl.Label=?");
	if($sthc){
	    $sthc->execute($el);
	    if( defined($val = $sthc->fetchrow()) ){
		$RFETCHED{"$tbl-$el"} = $val;
		$rv = $val;
	    }
	    $sthc->finish();
	}

	# close database
	rdaq_close_odatabase($obj);
    }
    #print "Record_n_Fetch :: returning $rv\n" if ($tbl eq "FOFileType");
    return $rv;
}

sub GetRecord
{
    my($tbl,$el)=@_;
    my($obj,$sth,$val,$rv);

    if($el eq ""){  return 0;}
    if($el eq 0){   return 0;}

    $rv = 0;
    if( ! defined($rv = $RFETCHED{"$tbl-$el"}) ){
	$obj = rdaq_open_odatabase();
	if(!$obj){ return $rv;}
	$sth = $obj->prepare("SELECT $tbl.Label FROM $tbl ".
			      "WHERE $tbl.id=?");
	if($sth){
	    $sth->execute($el);  
	    if( defined($val = $sth->fetchrow()) ){
		$RFETCHED{"$tbl-$el"} = $val;
		$rv = $val;
	    }
	    $sth->finish();
	}
	rdaq_close_odatabase($obj);
    }
    $rv;
}


# BACKWARD Compatibility only
sub rdaq_mask2string
{
    my($val)=@_;
    return rdaq_bits2string("DetSetMask",$val);
}

#
# Any bits 'val' from field column 'field'
# will be associated to a string. Noet that
# the column needs to have a BITWISE association
# entry for this to work.
#
sub rdaq_bits2string
{
    my($field,$val)=@_;
    my($str,@items);
    my($oobj,$sth);

    if( ! defined($BITWISE{$field}) ){  return "unknown";}

    if( ! defined($BITS2STRING{"$field-$val"}) ){
	$str = "";
	$oobj= rdaq_open_odatabase();
	#print "SELECT * FROM $BITWISE{$field}\n";
	$sth = $oobj->prepare("SELECT * FROM $BITWISE{$field} ORDER BY Label ASC");
	if($sth){
	    $sth->execute();
	    while( @items = $sth->fetchrow_array() ){
		$str .= "$items[1]." if( $val & (1 << $items[0]) );
	    }
	    chop($str);
	}
	rdaq_close_odatabase($oobj);
	if($str eq ""){ $str = "unknown";}
	$BITS2STRING{"$field-$val"} = $str;
    }
    $BITS2STRING{"$field-$val"};
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
# Returns the status string for a given entry.
#
sub rdaq_status_string
{
    my($sts)=@_;
    my($str);

    $str = "Unknown";
    $str = "new"       if($sts == 0);
    $str = "Submitted" if($sts == 1);
    $str = "Processed" if($sts == 2);
    $str = "QADone"    if($sts == 3);   # i.e. + QA
    $str = "Skipped"   if($sts == 4);
    $str = "SCalib"    if($sts == 5);   # submitted for calibration
    $str = "Died"      if($sts == 666);

    $str;
}

sub rdaq_trgs2string
{
    my($val)=@_;

    $rv = &GetRecord("FOTriggerSetup",$val);
    if($rv eq 0){
	return "unknown";
    } else {
	$rv;
    }
}

sub rdaq_ftype2string
{
    my($val)=@_;

    $rv = &GetRecord("FOFileType",$val);
    if($rv eq 0){
	return "unknown";
    } else {
	$rv;
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


sub    rdaq_toggle_debug { $DEBUG = ! $DEBUG;}


1;

#
# Dec 2001
#  Changed the meaning of TriggerSetup from trgSetupName to
#  glbSetupName. Seemed more appropriate and what people are 
#  accustom too. Added rdaq_trgs2string() interface.
#  Also improved speed in runNumber get_list_field by using
#  THREAD arrays. Only 1239 entries to scan for runNumber for
#  example instead of 113940 (2 order of magnitude up).
#

