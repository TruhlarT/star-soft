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
$file  = "";

$mode   = shift(@ARGV) if ( @ARGV );
$sltime = shift(@ARGV) if ( @ARGV );
$file   = shift(@ARGV) if ( @ARGV );


# We add an infinit loop around so the table will be filled
# as we go.
&Print("$0 starting on ".localtime()."\n");
do {
    $ctime = localtime();
    $dbObj = rdaq_open_odatabase();
    if( $dbObj){
	#&Print("O-Database opened\n");
	if ( ($obj = rdaq_open_rdatabase()) == 0){
	    &Print("Failed to open R-Database on ".localtime()."\n");
	} else {
	    #&Print("R-Database opened\n");

	    # get the top run
	    $run = $mode*rdaq_last_run($dbObj);
	    &Print("Last Run=$run\n");

	    if($run >= 0){
		# fetch new records since that run number
		@records = rdaq_raw_files($obj,$run);

		# display info
		if ($#records != -1){
		    &Print("Fetched ".($#records+1)." records on $ctime, entered ");

		    # record entries
		    &Print( rdaq_add_entries($dbObj,@records)."\n");

		    # cleanup
		    undef(@records);
		}
	    } else {
		&Print("Checking entries on ".localtime()."\n");
		$mode    = 0;  # loop reset
		@records = rdaq_raw_files($obj,$run);
		rdaq_update_entries($dbObj,@records);

		#rdaq_check_entries($dbObj,$sltime);
	    }

	    # close
	    rdaq_close_rdatabase($obj);

	}
	rdaq_close_odatabase($dbObj);
    } else {
	&Print("Failed to open O-Database on ".localtime()."\n");
    }

    sleep($sltime*$mode);
} while(1*$mode);


#
# perform IO on a file or STDOUT.
#
sub Print
{
    my(@all)=@_;

    if($file ne ""){
	while( ! open(FO,">>$file")){;}
	$FO = FO;
    } else {
	$FO = STDOUT;
    }
    foreach $el (@all){
	print $FO $el;
    }
    if($file ne ""){ close(FO);}
}
