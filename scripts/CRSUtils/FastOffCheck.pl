#!/opt/star/bin/perl -w

#
# This script checks if jobs are done or not.
# Done jobs are simply based on the appearance of
# the root files associated to the job. 
# this script is meant to run in a cronjob ...
#
# There is NOTHING to change from this script.
# Use arguments like
#
# .../FastOffCheck.pl dev /star/data27/reco 12 
#
# where 
#  arg1 is the directory to scan
#  arg2 the path where the files are supposed to appear
#  arg3 a retention time for the output in days
#

use lib "/afs/rhic/star/packages/scripts";
use RunDAQ;

$LIB     = "dev";
$TARGET  = "/star/data19/reco";
$UPDATE  = 0;
$RETENT  = 14;

$LIB     = shift(@ARGV) if ( @ARGV );
$TARGET  = shift(@ARGV) if ( @ARGV );
$RETENT  = shift(@ARGV) if ( @ARGV );
$UPDATE  = shift(@ARGV) if ( @ARGV );

# Assume standard tree structure
$JOBDIR  = "/star/u/starreco/$LIB/requests/daq/archive/";

# Fault tolerant. No info if fails.
if( ! opendir(DIR,"$JOBDIR") ){  exit;}

if(! $UPDATE){
    print "Scanning $JOBDIR vs $TARGET on ".localtime()."\n";
    while( defined($jfile = readdir(DIR)) ){
	#print "$jfile\n";
	if( $jfile =~ /(.*_)(st_.*)/){
	    $tree = $1;
	    $file = $2;

	    #print "$jfile Tree=$tree file=$file\n";

	    $tree =~ s/_/\//g;
	    chop($tree);        # remove trailing '/'
	    if( -e "$JOBDIR/old/$jfile.checked"){ 
		@stat1 = stat("$JOBDIR/old/$jfile.checked");
		@stat2 = stat("$JOBDIR/$jfile");
		if ( $stat1[10] >= $stat2[10]){
		    next;
		} else {
		    print "$jfile is more recent than last check. Rescan\n";
		    unlink("$JOBDIR/old/$jfile.checked");
		}
	    }

	    # double check the conformity of the job file name
	    if( $tree !~ m/$LIB/){
		print "WARNING :: Illformed $jfile found in $JOBDIR\n";
		push(@MOVE,$jfile);
	    } else {
		if( -e "$TARGET/$tree/$file.event.root"){
		    # found it so it is done.
		    $LOCATIONS{"$file.daq"} = "$TARGET/$tree";
		    push(@DONE,"$file.daq");
		    push(@MOVE,$jfile);
		} else {
		    #print "Could not find $TARGET/$tree/$file.event.root\n";
		}
	    }
	}
    }
    closedir(DIR);


    if( ! -d "$JOBDIR/old"){  mkdir("$JOBDIR/old",0755);}

    # Also scan the main tree for obsolete files
    if( -d $TARGET){
	chomp(@all = `cd $TARGET ; find $LIB -type f -mtime +$RETENT`);
	foreach $el (@all){
	    print "Deleting $TARGET/$el\n";
	    unlink("$TARGET/$el");
	    $el =~ s/.*\///g;
	    $el =~ s/\..*//;
	    $el .= ".daq";
	    
	    if( ! defined($LOCATIONS{$el}) ){
		$LOCATIONS{$el} = 0;
	    }
	}    
    }


    $obj = rdaq_open_odatabase();
    if($obj){
	foreach $el (keys %LOCATIONS){
	    if( ! rdaq_set_location($obj,$LOCATIONS{$el},$el) ){
		print "Failed to set location for $el\n";
	    }
	}


	rdaq_set_files_where($obj,2,1,@DONE);
	rdaq_close_odatabase($obj);
	
	foreach $jfile (@MOVE){
	    open(FO,">$JOBDIR/old/$jfile.checked");
	    print FO "$0 ".localtime()."\n";
	    close(FO);
	}
    }
} else {
    # Scan the directory for all files present and mark their
    # path in the database. This is rarely used. And done
    # only to update the database with a new location
    # directory if files are moved ...
    $obj = rdaq_open_odatabase();
    if($obj){
	chomp(@all = `cd $TARGET ; find $LIB -name '*.event.root'`);
	foreach $el (@all){
	    $el =~ m/(.*\/)(.*)/;
	    ($tree,$el) = ($1,$2);
	    $el =~ s/\..*//;
	    $el .= ".daq";  

	    chop($tree);
	    if( ! defined($LOCATIONS{$el}) ){
		$LOCATIONS{$el} = "$TARGET/$tree";
	    }    
	}

	foreach $el (keys %LOCATIONS){
	    rdaq_set_location($obj,$LOCATIONS{$el},$el);
	}
	rdaq_close_odatabase($obj);
    }
}

