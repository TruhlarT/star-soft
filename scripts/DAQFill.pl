#!/opt/star/bin/perl -w 


#
# This script will function as a loop and will fill
# the operation DAQInfo table.
# BEWARE !!! This is an infite loop process filling
# information in the DAQInfo table.
#

use lib "/afs/rhic/star/packages/scripts/";
use RunDAQ;

# We add an infinit loop around so the table will be filled
# as we go.
do {
    $dbObj = rdaq_open_odatabase();
    if( $dbObj){
	print "O-Database opened\n";
	if ( ($obj = rdaq_open_rdatabase()) == 0){
	    print "Failed to open R-Database\n";
	} else {
	    print "R-Database opened\n";
	    
	    # get the top run
	    $run = rdaq_last_run($dbObj);
	    
	    # fetch new records since that run number
	    @records = rdaq_raw_files($obj,$run);
	    
	    # display info
	    print "Fetched ".($#records+1)."\n";
	    
	    # record entries
	    rdaq_add_entries($dbObj,@records);

	    # close
	    rdaq_close_rdatabase($obj);
	}
	rdaq_close_odatabase($dbObj);
    } else {
	print "Failed to open O-Databse\n";
    }

    sleep(60);
} while(1);

