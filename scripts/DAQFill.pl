#!/opt/star/bin/perl -w


#
# This script will function as a loop and will fill
# the operation DAQInfo table.
# BEWARE !!! This is an infite loop process filling
# information in the DAQInfo table.
#

use lib "/afs/rhic/star/packages/scripts/";
use RunDAQ;

# Mode 1 will quit
$mode  = 1;
$sltime= 60;

$mode   = shift(@ARGV) if ( defined(@ARGV) );
$sltime = shift(@ARGV) if ( defined(@ARGV) );


# We add an infinit loop around so the table will be filled
# as we go.
do {
    $ctime = localtime();
    $dbObj = rdaq_open_odatabase();
    if( $dbObj){
	#print "O-Database opened\n";
	if ( ($obj = rdaq_open_rdatabase()) == 0){
	    print "Failed to open R-Database on ".localtime()."\n";
	} else {
	    #print "R-Database opened\n";
	    
	    # get the top run
	    $run = $mode*rdaq_last_run($dbObj);
	    
	    # fetch new records since that run number
	    @records = rdaq_raw_files($obj,$run);
	    
	    # display info
	    if ($#records != -1){
		print "Fetched ".($#records+1)." records on $ctime\n";

		# record entries
		rdaq_add_entries($dbObj,@records);

		# cleanup
		undef(@records);
	    }

	    # close
	    rdaq_close_rdatabase($obj);

	}
	rdaq_close_odatabase($dbObj);
    } else {
	print "Failed to open O-Database on ".localtime()."\n";
    }

    sleep($sltime*$mode);
} while(1*$mode);

