
#
# Perl macro for fastOffline communication
# Changing this will change EVERY scripts
# accessing this schema. Please, be carefull.
#
#      rdaq_open_rdatabase          open raw-ddb
#      rdaq_close_rdatabase         close raw-ddb
#      rdaq_raw_files               return a list of raw fileinformation
#      rdaq_open_odatabase          open o-ddb
#      rdaq_close_odatabase         close the o-ddb
#      rdaq_add_entry               add one entry in the o-ddb
#      rdaq_add_entries             add entries in the o-ddb
#      rdaq_last_run                return the last run number from the o-ddb
#
use Carp;
use DBI;


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



require 5.000;
require Exporter;
@ISA = qw(Exporter);
@EXPORT= qw( 
	     rdaq_open_rdatabase         
	     rdaq_close_rdatabase        
	     rdaq_raw_files              
	     rdaq_open_odatabase         
	     rdaq_close_odatabase        
	     rdaq_add_entry              
	     rdaq_add_entries            
	     rdaq_last_run               
	     );


# Build ddb ref here.
$DDBREF    = "DBI:mysql:$DDBNAME:$DDBSERVER:$DDBPORT";

# Required tables
@REQUIRED  = ("daqFileTag","daqSummary","triggerSet","beamInfo","magField");


#
# Insert an element in the o-database.
# We accept only one entry. INEFFICIENT.
#
sub rdaq_add_entry
{
    my($obj,@values)=@_;
    my($sth);

    $sth = $obj->prepare("INSERT IGNORE INTO $dbtable VALUES(?,?,?,?,?,?,?,?,?,?,0)");
    $sth->execute(@values);
    $sth->finish();
}

# enter records as returned by rdaq_raw_files
sub rdaq_add_entries
{
    my($obj,@records)=@_;
    my($sth,$line,@values);
   
    if($#records != -1){
	$sth = $obj->prepare("INSERT INTO $dbtable VALUES(?,?,?,?,?,?,?,?,?,?,0)");
	if($sth){
	    foreach $line (@records){
		@values = split(" ",$line);
		$sth->execute(@values);
	    }
	    $sth->finish();    
	}
    }
}

#
# Select the top element of the o-database
#
sub rdaq_last_run
{
    my($obj)=@_;
    my($sth);

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


    # Default values
    if( ! defined($from) ){ $from = "";}
    if( ! defined($limit)){ $limit= -1;}

    # Trigger selection
    $stht = $obj->prepare("SELECT detectorSet.detectorID FROM detectorSet ".
			  "WHERE detectorSet.runNumber=?");

    # We will select on RunStatus == 0
    $cmd  = "SELECT daqFileTag.file, daqSummary.runNumber, daqFileTag.numberOfEvents, daqFileTag.beginEvent, daqFileTag.endEvent, magField.current, magField.scaleFactor, beamInfo.yellowEnergy+ beamInfo.blueEnergy FROM daqFileTag, daqSummary, magField, beamInfo  WHERE daqSummary.runNumber=daqFileTag.run AND daqSummary.runStatus=0 AND daqSummary.destinationID In(1,4) AND daqFileTag.file LIKE '%physics%' AND magField.runNumber=daqSummary.runNumber AND magField.entryTag=0 AND beamInfo.runNumber=daqSummary.runNumber AND beamInfo.entryTag=0";

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
    push(@res,"AuAu");
    

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
    $obj->disconnect();
}

sub rdaq_close_odatabase
{
    my($obj)=@_;
    $obj->disconnect();
}

sub rdaq_open_odatabase
{
   my($obj);
   
   $obj = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass);
   return $obj;
}




# --------------------
# Utility routines.
# --------------------

# Provide a decoding method for the above
# built mask, We can hardcode values (they
# won't change);
sub rdaq_mask2string
{
    0;
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
 
 
 
