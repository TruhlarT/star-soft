#!/opt/star/bin/perl -w

#
# This script will fetch records fron the o-database
# and create a job file and submit it.
# This script is meant to run under starreco and on
# a rcrs nodes from which we can actually submit a job
# and finally, only after a cd to the working directory
# where the scripts will be submitted.
#
# The number of jobs we can submit is automatically
# determined byt the number of available queues.
#
# A cronjob should call this script regularly using
# arguments
#  % ScriptName [LibVersion] [NumEvt] [{|^|+|C}targetDataDisk]
#     [CommaSeparatedChainOptions]  [Queue] [SpillMode]
# or
#  % ScriptName [LibVersion] [NumEvt] [Option]
#
# If targetDataDisk starts with a ^, the jobs are only
# taken from the top of the DDB pile (latest entries),
# otherwise, the jobs will be taken from top to bottom
# which will have the net effect to go through all jobs
# if time allows.
#
# If + is specified, the run listed in a file named after
# $CONFF are first marked as new and submitted one after
# another. This mode slides in some extraneous runs in
# high priority mode (spill mode) and provide a convenient
# to push some runs through the FastOffline chain.
#
# The second syntax as a few options
#   Option=1      Move the log into the archive directory
#                 if the job is done.
#
# Default are currently
#    dev, 20, /star/data19/reco
#
#
# History
#  Fri Jul 27. dammit !! Did not take into account that
#              'staged' and 'staging' jobs are not showed
#              in -m mode. Got a situation with zillions
#              of submit. Now corrected.
#
# Sunday Sept 10. Added +/path syntax.
#
# Mon Dec 17 2001, chained to DCHAIN functioning on based on 
#              a mandatory collision
#              type for submiting with the default chain. If
#              a chain is used as argument, this does not 
#              apply.
# Jan 22 2002  Added mode 3 which performs calibration sweep
#              on ftype. We MUST use the proper ftype number
#              in the routine call i.e. a-priori known
#              what the laser files will be in our case ...
# Feb  9 2002  Modified for support of several LIB dependent
#              job files simply using JobSubmit$LIB.lis .
#              Allows for many cron-tab entries and several
#              jobs in //.
#

use lib "/afs/rhic/star/packages/scripts";
use RunDAQ;
use CRSQueues;

$ThisYear = 2004;

# Default values Year2 data
if ($ThisYear == 2002){
    $LIB     = "dev";
    $NUMEVT  = 20;
    $TARGET  = "/star/data13/reco";

    $PHYSTP  = 1;
    $LASERTP = 3;            # This can known only by looking into the FOFileType
                             # or calling some extra routine from the pm. Prefer to 
                             # hard-code (that is -> faster) Sorry ...
    @USEQ    = (4,4,2);      # queue to be used for regular mode, bypass and calib 
    @SPILL   = (0,3,1);      # queue spill level for the 3 modes

    # Default production chains by species
    $DCHAIN{"AuAu"}           = "P2001a";
    $DCHAIN{"ProtonProton"}   = "PP2001,fpd";


    # Default pre-pass calibration chains by species used in regular mode if defined
    $DCALIB{"AuAu"}           = "";   # Trash out default calib pass. 
                                      # All done now ; was PreTpcT0
    $DCALIB{"ProtonProton"}   = "";   # PreLaser" no more interlayed laser, 
                                      # all laser files processed


    # Stand-alone Calibration pass. Used in C/mode
    $SCALIB{"AuAu"}           = "";
    $SCALIB{"ProtonProton"}   = "OptLaser";

} elsif ($ThisYear == 2003 ){
    $LIB     = "dev";
    $NUMEVT  = 100;
    $TARGET  = "/star/data27/reco";

    $LASERTP = 2;
    $PHYSTP  = 5;

    @USEQ    = (4,4,3);
    @SPILL   = (0,3,1);      
    
    # Default chain
    $DCHAIN{"dAu"}            = "dAu2003,alltrigger,est,CMuDst";
    $DCHAIN{"ProtonProton"}   = "pp2003,alltrigger,trgd,est,CMuDst";

    # Default pre-calib
    #$DCALIB{"dAu"}            = "PreTpcT0";

    # Default stand-alone auto-calib (works only on $LASERTP files)
    $SCALIB{"dAu"}            = "OptLaser";
    $SCALIB{"ProtonProton"}   = "OptLaser";

} elsif ($ThisYear == 2004 ){
    $LIB     = "dev";
    $NUMEVT  = 100;
    $TARGET  = "/star/data27/reco";

    $LASERTP = 3;
    $PHYSTP  = 1;

    @USEQ    = (4,4,3);
    @SPILL   = (0,3,2);      
    
    # Default chain
    $DCHAIN{"AuAu"}           = "P2004,EST,CMuDst,OShortR";


    # Default pre-calib
    #$DCALIB{"dAu"}            = "PreTpcT0";

    # Default stand-alone auto-calib (works only on $LASERTP files)
    $SCALIB{"AuAu"}           = "OptLaser";

} else {
    print "Unknown Year $ThisYear\n";
    exit;
}





# Default production chains by species
#$DCHAIN{"AuAu"}           = "P2001a";
#$DCHAIN{"ProtonProton"}   = "PP2001,fpd";
#$DCHAIN{"dAu"}            = "dAu2003,alltrigger";

# Default pre-pass calibration chains by species used in regular mode if defined
#$DCALIB{"AuAu"}           = "";         # Trash out default calib pass. All done now, was PreTpcT0
#$DCALIB{"ProtonProton"}   = "";         # PreLaser" no more interlayed laser, all laser files processed
#$DCALIB{"dAu"}            = "PreTpcT0";

# Stand-alone Calibration pass. Used in C/mode
#$SCALIB{"AuAu"}           = "";
#$SCALIB{"ProtonProton"}   = "OptLaser";
#$SCALIB{"dAu"}            = "OptLaser";




$CHAIN   = "";

$LIB     = shift(@ARGV) if ( @ARGV );
$NUMEVT  = shift(@ARGV) if ( @ARGV );
$TARGET  = shift(@ARGV) if ( @ARGV );
$CHAIN   = shift(@ARGV) if ( @ARGV );

$tmpUQ   = shift(@ARGV) if ( @ARGV );
$tmpSP   = shift(@ARGV) if ( @ARGV );

$SPATH ="/afs/rhic/star/packages/scripts";

# if we wait 1 minute between submit, and our cron
# tab executes this once every 20 minutes, max the
# return number of slots to $MAXCNT.
$SCRATCH = ".";
$LOCKF   = "FastOff.lock";
$CONFF   = "JobSubmit$LIB.lis";
$PRIORITY= 100;              # default queue priority
$SLEEPT  = 10;               # sleep time between submit
$MAXCNT  = 20;               # max job to send in a pass
$RATIO   = 2;                # time drop down for mode + (2=twice faster)
                   



# Intermediate variable
$LIBV = $LIB;
if($LIB eq "cal"){ $LIB = "dev";}

$PAT = "$LIB"."_*_st_*";


# Now go ...
if( $TARGET =~ m/^\// || $TARGET =~ m/\^\// ){
    #
    # FAST OFFLINE regular mode
    #
    # Overwrite queue if necessary
    $USEQ[0] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[0]= $tmpSP if ( defined($tmpSP) );

    # Default mode is submit. Target is a path
    # get the number of possible jobs per queue.
    $TOT = CRSQ_getcnt($USEQ[0],$SPILL[0],$PAT);

    print "Mode=direct Queue count Tot=$TOT\n";

    $time = localtime();
    if ($TOT > 0 && ! -e $LOCKF){
	open(FL,">$LOCKF");
	close(FL);
	#print "We need to submit $TOT jobs\n";

	# Check $TARGET for sub-mode
	# If $TARGET starts with a ^, take only the top, otherwise
	# go into the 'crawling down the list' mode. We will start
	# with the second mode (gives an idea of how often we have
	# a dead time process earlier runs).

	if( ($obj = rdaq_open_odatabase()) ){
	    if( substr($TARGET,0,1) eq "^" ){
		# Simple with a perl module isn't it.
		print "Top of the list ...\n";
		$TARGET=~ s/\^//;
		@files = rdaq_get_ffiles($obj,-1,$TOT);
	    } else {
		# ask only for status=0 files (will therefore
		# crawl-down the list).
		print "Crawling down the list ...\n";
		@files = rdaq_get_ffiles($obj,0,$TOT);
	    }


	    if($#files != -1){
		print "Checking ".($#files+1)." jobs\n";
		undef(@OKFILES);             # will be filled by Submit
		undef(@SKIPPED);
		foreach $file (@files){
		    sleep($SLEEPT) if &Submit(0,$USEQ[0],$SPILL[0],
					      $file,$CHAIN);
		    $MAXCNT--; 
		    last if ($MAXCNT == 0);
		}
		rdaq_set_files($obj,1,@OKFILES);
		rdaq_set_files($obj,4,@SKIPPED);
	    } else {
		# there is nothing to submit
		print "There is nothing to submit on $time\n";
	    }
	    rdaq_close_odatabase($obj);
	}
	if(-e $LOCKF){  unlink($LOCKF);}
    }



} elsif ($TARGET =~ m/(\+)(.*)/ ) {
    #
    # FAST OFFLINE BYPASS
    #
    # Copied from mode 0. Can be merged ...
    #
    $TARGET = $2;
    #print "Target is now $TARGET\n";

    # Overwrite queue if necessary
    $USEQ[1] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[1]= $tmpSP if ( defined($tmpSP) );


    # In this mode, read a configuration file, select those runs
    # and submit them out.
    if( ! -e $CONFF){ exit;}                       # no conf exit
    if( ! ($obj = rdaq_open_odatabase()) ){ exit;} # no ddb abort
    if( -e $LOCKF){ exit;}                         # leave if lockf

    # read conf
    open(FI,$CONFF) || die "Could not open $CONFF for read\n";
    chomp(@all = <FI>);
    close(FI);


    # get number of slots. Work is spill mode.
    $TOT = CRSQ_getcnt($USEQ[1],$SPILL[1],$PAT);

    # Ok or not ?
    if( $TOT > 0){
	# Lock file creation
	open(FL,">$LOCKF");
	close(FL);

	print "JobSubmit :: We can slide in $TOT jobs\n" if ($#all != -1);
	foreach $line (@all){
	    # There are 2 possibilities. The run is new
	    # or has been marked for re-run. We will recognize
	    # a new run by a run number only on a line.
	    @items = split(" ",$line);

	    if($#items == 0 || $#items == 1){
		print "JobSubmit :: Run $line is new\n";

		if($#items == 1){
		    $cho = $items[1];
		    print "JobSubmit :: Chain bypass $cho\n";
		} else {
		    if($CHAIN eq ""){ $CHAIN = "default";}
		    $cho = $CHAIN;
		}
		$SEL{"runNumber"} = $items[0]; 
		@files = rdaq_get_orecords($obj,\%SEL,-1);
		rdaq_set_files($obj,0,@files);

		# Get the count as being the total
		$run = $items[0];
		$cnt = $#files+1;
		
	    } else {
		# Else old and/or only the one with status
		# 0 can be sent to the queue.
		$run = $items[0];
		$cnt = $items[1];
		$cho = $items[2];

		$SEL{"runNumber"} = $run;
		$SEL{"Status"}    = 0;
		@files = rdaq_get_orecords($obj,\%SEL,$cnt);
	    }

	    # OK. We have $cnt for that one and $TOT slots.
	    print "JobSubmit :: Working with $run -> $cnt and $TOT slots\n";

	    # Submit no more than $TOT jobs
	    if($#files != -1){
		undef(@OKFILES);
		undef(@SKIPPED);
		$k = -1;
		foreach $file (@files){
		    last if ($MAXCNT <= 0);    # max jobs per pass

		    last if ($TOT <= 0);       # max available queues 
		    last if (($cnt-$k) <= 0);  # max file seq for this run

		    #print "Submitting $file\n";
		    $TOT = $TOT-1;
		    $k   = $k+1;

		    sleep($SLEEPT/$RATIO) if &Submit(1,$USEQ[1],$SPILL[1],
						     $file,$cho);

		    $MAXCNT--; 
		}
		# Mark files as submitted
		rdaq_set_files($obj,1,@OKFILES);
		rdaq_set_files($obj,4,@SKIPPED);


		# Check if the $cnt matches $#OKFILES. This is
		# non-necessary check ; however, it allows us to
		# supress redundant runs from the $CONFF files when
		# the count is null. Can be done only when both
		# count matches.
		$tot = $#OKFILES;
		$tot += $#SKIPPED if ($#SKIPPED != -1);
		if ($k == $tot){
		    # Save the remaining record count for that run
		    # When it will reach 0, no longer record that run.
		    if( $cnt > 0){
			$cnt = $cnt - $k;
			push(@RECORDS,"$run $cnt $cho");
		    }
		} else {
		    print "Discrepency $k counted $tot success ".
			"($#OKFILES/$#SKIPPED)\n";
		    push(@RECORDS,"$run $cnt $cho");
		}
	    } else {
		print "Run $run will be ignored. No files returned by ddb\n";
	    }
	}


	# We are done scanning the runs, re-build the CONFF
	# file. Delete lock file afterward.
	open(FO,">$CONFF");
	foreach $line (@RECORDS){ print FO "$line\n";}
	close(FO);
	unlink($LOCKF);

    }


} elsif ($TARGET =~ m/(C\/)(.*)/ ) {
    #
    # AUTO-CALIBRATION MODE
    #
    # Overwrite queue if necessary
    $USEQ[2] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[2]= $tmpSP if ( defined($tmpSP) );

    # Default mode is submit. Target is a path
    # get the number of possible jobs per queue.
    #print "Using $USEQ[2] $SPILL[2]\n";
    $TOT = CRSQ_getcnt($USEQ[2],$SPILL[2],$PAT,1);

    $time = localtime();
    if ($TOT > 0 && ! -e $LOCKF){
	open(FL,">$LOCKF");
	close(FL);
	#print "We need to submit $TOT jobs\n";

	# Check $TARGET for sub-mode
	# If $TARGET starts with a ^, take only the top, otherwise
	# go into the 'crawling down the list' mode. We will start
	# with the second mode (gives an idea of how often we have
	# a dead time process earlier runs).

	if( ($obj = rdaq_open_odatabase()) ){
	    if( substr($TARGET,0,1) eq "C" ){
		# Simple with a perl module isn't it.
		$TARGET=~ s/C\//\//;
		@files = rdaq_get_ffiles($obj,0,$TOT,$LASERTP);
	    } else {
		# Cannot do this
		print "Failed. Wrong syntax\n";
	    }



	    if($#files != -1){
		print "Checking ".($#files+1)." jobs\n";
		undef(@OKFILES);             # will be filled by Submit
		undef(@SKIPPED);
		foreach $file (@files){
		    #print "HW : $file\n";
		    sleep($SLEEPT) if &Submit(2,$USEQ[2],$SPILL[2],
					      $file,$CHAIN);
		    $MAXCNT--; 
		    last if ($MAXCNT == 0);
		}
		rdaq_set_files($obj,5,@OKFILES);  # special flag
		rdaq_set_files($obj,4,@SKIPPED);  # mark skipped
	    } else {
		# there is nothing to submit
		print "There is nothing to submit on $time\n";
	    }
	    rdaq_close_odatabase($obj);
	}
	if(-e $LOCKF){  unlink($LOCKF);}
    #} else {
	#print "There are no slots available\n";
    }



} elsif ($TARGET == 1) {
    # First argument specified, check job list and results ...
    CRSQ_check($PAT,"../archive/");

    # clean lock file from default mode. Adds sturdiness
    # the process since the possibility to have a job killed while
    # a lock file was opened is non null.
    if(-e $LOCKF){ unlink($LOCKF);}



} else {
    print "Unknown mode P3=$TARGET used\n";
}






#
# Create a job file and submit.
# Note that the full file info is received here ...
#
sub Submit
{
    my($mode,$queue,$spill,$file,$chain)=@_;
    my($Hfile,$jfile,$mfile,@items);
    my($field,$tags);
    my($trgsn,$trgrs);

    # We are assuming that the return value of $file is
    # the mode 2 of get_ffiles() and counting on the 
    # elements position.
    #print "$file\n";
    @items = split(" ",$file);
    $file  = $items[0];
    $field = $items[6];
    $coll  = $items[8];

    $coll  = "dAu" if ($coll eq "DeuteronAu");

    # Trigger setup string
    $trgsn = rdaq_bits2string("TrgMask",$items[10]);
    # Triggers  mask information
    $trgrs = rdaq_bits2string("TrgMask",$items[11]);
    # Detector setup information
    $dets  = rdaq_bits2string("DetSetMask",$items[9]);
    

    if($chain eq "" || $chain eq "none" || $chain eq "default"){
	$chain = $DCHAIN{$coll};
	if( ! defined($chain) ){
	    print 
		"No chain options declared. No default for [$coll] either.\n";
	    return 0;
	}
    }
    if($mode == 2){
	# This is the calibration specific mode
	$tags  = "laser";        # **** this is cheap and dirty ****
	$calib = $SCALIB{$coll};
    } else {
	# this is any other mode
	$tags  = "tags";
	$calib = $DCALIB{$coll};
    }
    if( ! defined($calib) ){ $calib = "";}
    if( $mode == 2 && $calib eq ""){
	# Mode to is calibration only so if we are missing
	# the option, do NOT continue.
	push(@SKIPPED,$file);
	print "Info :: mode 2 requested and calib is empty\n";
	return 0;
    } elsif ($calib eq ""){
	# Change it to a dummy value so the
	# soft-link is created.
	#$calib = "DUMMY";
    }

    #
    # Exclusions
    #
    # This was added according to an Email I have sent to
    # the period coordinator list. Only Jeff Landgraff 
    # has answered saying we can skip the 'test' once.
    if ( $file =~ /pedestal/){
	print "Info :: Skipping $file (name matching exclusion)\n";
	push(@SKIPPED,$file);
	return 0;

    } elsif ( $trgrs eq "pedestal" || $trgrs eq "pulser" ||
	 $trgsn eq "pedestal" || $trgsn eq "pulser" ){
	print "Info :: Skipping $file has setup=$trgsn 'triggers'=$items[11]=$trgrs\n";
	push(@SKIPPED,$file);
	return 0;

    } elsif ( $trgrs =~ m/test/ && $mode == 0){
	if ( $ThisYear == 2002){
	    # start with a warning
	    print "Info :: Skipping $file has 'triggers'=$items[11]=$trgrs\n";
	    push(@SKIPPED,$file);
	    return 0;
	} else {
	    print 
		"Info :: $file has 'triggers'=$items[11]=$trgrs ",
		"but Year=$ThisYear not skipping it\n";
	}
    }
    if ( $dets ne "tpc" && $dets !~ m/\.tpc/){
	print "Info :: detectors are [$dets] (not including tpc) skipping it\n";
	push(@SKIPPED,$file);
	return 0;
    }



    # Last element will always be the Status
    if($items[$#items] != 0){ 
	print "Found status = $items[$#items] (??)\n";
	return;
    }

    # Otherwise, we do have a valid entry
    $Hfile = rdaq_file2hpss($file,2);
    @items = split(" ",$Hfile);

    # No trigger information nowadays
    $m     = sprintf("%2.2d",$items[3]);
    $jfile = join("_",$LIB,$items[2],$m,$file);
    $jfile =~ s/\..*//;
    $mfile = $file;
    $mfile =~ s/\..*//;

    # Just in case ...
    if( -e "$jfile"){
	print "Info :: $jfile exists. Ignoring for now\n";
	return 0;
    }

    # THIS IS HACK FOR 2004 data until Jeff fixes the names
    $prefix = "";
    #$prefix = "COPY_";

    # Now generate the file and submit
    if( open(FO,">$jfile") ){
	if($calib ne ""){
	    print FO <<__EOH__;
mergefactor=1
#input
    inputnumstreams=2
    inputstreamtype[0]=HPSS
    inputdir[0]=$items[0]
    inputfile[0]=$prefix$items[1]
    inputstreamtype[1]=UNIX
    inputdir[1]=$TARGET/StarDb
    inputfile[1]=$calib
__EOH__
        } else {
	    print FO <<__EOH__;
mergefactor=1
#input
    inputnumstreams=1
    inputstreamtype[0]=HPSS
    inputdir[0]=$items[0]
    inputfile[0]=$prefix$items[1]
__EOH__
	}
	
	print FO <<__EOF__;
#output
    outputnumstreams=5

#output stream
    outputstreamtype[0]=UNIX
    outputdir[0]=$SCRATCH
    outputfile[0]=$prefix$mfile.event.root

    outputstreamtype[1]=UNIX
    outputdir[1]=$SCRATCH
    outputfile[1]=$prefix$mfile.MuDst.root

    outputstreamtype[2]=UNIX
    outputdir[2]=$SCRATCH
    outputfile[2]=$prefix$mfile.hist.root

    outputstreamtype[3]=UNIX
    outputdir[3]=$SCRATCH
    outputfile[3]=$prefix$mfile.$tags.root

    outputstreamtype[4]=UNIX
    outputdir[4]=$SCRATCH
    outputfile[4]=$prefix$mfile.runco.root

#    outputstreamtype[4]=UNIX
#    outputdir[4]=$SCRATCH
#    outputfile[4]=$mfile.dst.root

#standard out
    stdoutdir=/star/rcf/prodlog/$LIB/log/daq
    stdout=$mfile.log

#standard error
    stderrdir=/star/rcf/prodlog/$LIB/log/daq
    stderr=$mfile.err
    notify=starreco\@rcrsuser1.rcf.bnl.gov

#program to run
    executable=$SPATH/bfccb
__EOF__

        # Chain default
	print FO
	    "    executableargs=25,",
	    "$LIBV,$TARGET/$LIB/$items[2]/$m,",
	    "$NUMEVT,$chain",
	    "\n";
	close(FO);

	if( (stat($jfile))[7] == 0){
	    print "Info :: 0 size $jfile . Please, check quota/disk space\n";
	    unlink($jfile);
	    return 0;
	} else {
	    if ( CRSQ_submit($jfile,$PRIORITY,$queue,$spill) ){
		# Mark it so we can set status 1 later
		print "Successful submission of $file ($queue,$spill) on ".
		    localtime()."\n";
		push(@OKFILES,$file);
		return 1;
	    }
	}
    } else {
	print "Fatal :: Could not open $jfile\n";
	return 0;
    }

}


