#!/usr/bin/env perl

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
#  % ScriptName [LibVersion] [NumEvt] [{|^|+|C|Z}targetDataDisk]
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
# Note that the presence of a file named FastOff.quit will
# make this script to quit without any processing. This
# script itself handles clashes between multiple execution
# via  afile named FastOff.lock . This latest file, if created
# by hand, it may be automatically deleted if older than
# some arbitrary time. TO stop FastOffline, you should then
# use the FastOff.quit file mechanism instead.
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
# Jan 2005     Added HPSS output mode
# May 2005     Added disk range syntax support (delegation to bfcca)
# April 2006   $ltarget/FreeSpace mechanism for PANASAS, changed
#              the meaning of express.
#

use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use RunDAQ;
use CRSQueues;

$ThisYear = 2008;                 # Block to consider. Completely artificial
                                  # and used to preserve older options in if
                                  # block along with current option.
$HPSS     = 1;                    # turn to 0 for UNIX staging only
                                  # HPSS staging was requested for Run5

# Self-sorted vars
$SELF  =  $0;
$SELF  =~ s/.*\///;
$SELF  =~ s/\..*//;
$SSELF = $SELF;
$SELF .= " :: ".time();

# default values global (unless overwritten)
@EXPRESS = undef;  $EXPRESS_W  =  70;
$ZEROBIAS= 0;      $ZEROBIAS_W =  30;

# this does not have a weight
$PHYSTP2 = 0;

# If defined, command line argument will be ignored and this
# will be the ultimate maximum number of events processed.
# DO NOT SET IT HERE but in the diverse blocks.
$MAXEVT  = 0;


# Second layer throttling would do one file per run within the
# regular mode.
$THROTTLE = 2;

# Do not change this value. Set by year, this is the default.
$TREEMODE = 0;

#### SET THIS TO 1 TO DEBUG NEW SCRIPTS / FEATURES - Can be done by year
$DEBUG    = 0;


# Default values Year2 data
if ($ThisYear == 2002){
    $LIB     = "dev";
    $NUMEVT  = 20;           # this may be overwritten by command line arguments
    $TARGET  = "/star/data13/reco";

    $PHYSTP  = 1;
    $LASERTP = 3;            # This can known only by looking into the FOFileType
                             # or calling some extra routine from the pm. Prefer to
                             # hard-code (that is -> faster) Sorry ...
    @USEQ    = (4,4,2);      # queue to be used for regular mode, bypass and calib
    @SPILL   = (0,3,1);      # queue spill level for the 3 modes

    #
    # Default production chains by species
    #                           ^^^^^^^^^^
    # Note that in 2002, the specie for p+p was ProtonProton and this changed
    # later in PPPP. One has to be aware of the Specices and define the appropriate
    # chains before FastOffline can submit AND accept any jobs. If a chain is missing,
    # the jobs (files) will be ignored.
    #
    $DCHAIN{"AuAu"}           = "P2001a";
    $DCHAIN{"ProtonProton"}   = "PP2001,fpd";


    #
    # Default pre-pass calibration chains by species used in regular mode if defined
    # pre-pass is any pass done with the SAME production job but done just before
    # the data-cranking.
    #
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

} elsif ( $ThisYear == 2004 ){
    $LIB     = "dev";
    $NUMEVT  = 100;
    $TARGET  = "/star/data27/reco";

    $LASERTP =  3;
    $PHYSTP  =  1;
    $PHYSTP2 =  5;    # just comment them if you want them disabled
    @EXPRESS = (8);
    $ZEROBIAS= 11;

    @USEQ    = (4,4,3);
    @SPILL   = (0,3,2);

    # Default chain
    $DCHAIN{"AuAu"}           = "P2004,svt_daq,svtD,EST,eemcD,OShortR,-OSpaceZ,OSpaceZ2,Xi2,V02,Kink2,CMuDst";
    $DCHAIN{"PPPP"}           = "P2004,ppOpt,svt_daq,svtD,EST,eemcD,OShortR,-OSpaceZ,OSpaceZ2,Xi2,V02,Kink2,CMuDst";

    # Default pre-calib
    #$DCALIB{"dAu"}            = "PreTpcT0";

    # Default stand-alone auto-calib (works only on $LASERTP files)
    $SCALIB{"AuAu"}           = "OptLaser";
    $SCALIB{"PPPP"}           = "OptLaser";

} elsif ( $ThisYear == 2005 ){
    $TREEMODE= 1;
    $LIB     = "dev";

    $NUMEVT  = 100;
    #$MAXEVT  = 250;

    $TARGET  = "/star/data+08-09/reco";   # This is ONLY a default value.
                                          # Overwritten by ARGV (see crontab)

    # Those were made automatically guessed in 2005.
    # Previous years hardcoded values could remain as-is (will not change
    # as tables are already filled)
#    $LASERTP =  rdaq_string2ftype("laser");
    $PHYSTP  =  rdaq_string2ftype("physics");
    $PHYSTP2 =  rdaq_string2ftype("physics_adc"); # just comment them if you want them disabled
#    @EXPRESS = (rdaq_string2ftype("express"));
#    $ZEROBIAS=  rdaq_string2ftype("zerobias");

    @USEQ    = (5,5,4);
    @SPILL   = (1,5,2);

    # Default chain -- P2005 does not include Corr4 but Corr3
    $DCHAIN{"AuAu"}           = "P2005,svt_daq,svtD,EST,pmdRaw,Xi2,V02,Kink2,CMuDst,OShortR";
    $DCHAIN{"PPPP"}           = "P2005,ppOpt,svt_daq,svtD,EST,pmdRaw,Xi2,V02,Kink2,CMuDst,OShortR";
    $DCHAIN{"CuCu"}           = "P2005,SCEbyE,OGridLeak,svt_daq,svtD,EST,pmdRaw,Xi2,V02,Kink2,CMuDst,OShortR,OSpaceZ2";

    $DCALIB{"CuCu"}           = "OneSpaceCharge";

    # Default stand-alone auto-calib (works ONLY on $LASERTP files)
    $SCALIB{"AuAu"}           = "OptLaser";
    $SCALIB{"PPPP"}           = "OptLaser";
    $SCALIB{"CuCu"}           = "OptLaser";

    # ezTree production requires some conditions. We set them here.
    # ezTree uses the Xtended Status index 1. See table in RunDAQ.pm
    $ID                   = 1;
    $EZTREE{"Status"}     = 0;
    $EZTREE{"XStatus$ID"} = 0;

    if ( ($tmp = rdaq_string2trgs("ppProductionMinBias")) != 0){
    	# Self adapting
    	$EZTREE{"TrgSetup"} = $tmp;
    }

} elsif ( $ThisYear == 2006 ) {
    # ... blabla like year5 ...
    $TREEMODE= 1;
    $LIB     = "dev";

    $NUMEVT  = 100;
    $MINEVT  = 200;

    $TARGET  = "/star/data09/reco";       # This is ONLY a default value.
                                          # Overwritten by ARGV (see crontab)

    # Those were made automatically guessed in 2005.
    # Previous years hardcoded values could remain as-is (will not change
    # as tables are already filled)
    $LASERTP =  rdaq_string2ftype("laser");

    $PHYSTP  =  rdaq_string2ftype("physics");
    $PHYSTP2 =  rdaq_string2ftype("physics_adc"); # just comment them if you want them disabled
    @EXPRESS = (
		rdaq_string2ftype("express"),
		rdaq_string2ftype("jpsi"),
		rdaq_string2ftype("upsilon"),
		rdaq_string2ftype("btag"),
		rdaq_string2ftype("muon")
		);
    $ZEROBIAS=  rdaq_string2ftype("zerobias");

    @USEQ    = (5,5,5);
    @SPILL   = (0,2,4);

    # Default chain -- P2005 does not include Corr4 but Corr3
    #$DCHAIN{"PPPP"}           = "pp2006a,ittf,ezTree";
    $DCHAIN{"PPPP"}           = "pp2006b,ittf,ezTree";

    # Default stand-alone auto-calib (works ONLY on $LASERTP files)
    $SCALIB{"PPPP"}           = "OptLaser";

    # ezTree production requires some conditions. We set them here.
    # ezTree uses the Xtended Status index 1. See table in RunDAQ.pm
    $ID                   = 1;
    $EZTREE{"Status"}     = 0;
    $EZTREE{"XStatus$ID"} = 0;

    # ...
    #if ( ($tmp = rdaq_string2trgs("minbiasSetup")) != 0){
    if ( ($tmp = rdaq_string2trgs("pp2006MinBias")) != 0){
    	# Self adapting
    	$EZTREE{"TrgSetup"} = $tmp;
    }

} elsif ( $ThisYear == 2007 ) {
    # ... blabla like year6 ...
    $TREEMODE= 1;
    $LIB     = "dev";

    $NUMEVT  = 100;
    $MINEVT  = 200;

    $TARGET  = "/star/data09/reco";       # This is ONLY a default value.
                                          # Overwritten by ARGV (see crontab)

    # Those were made automatically guessed in 2005.
    # Previous years hardcoded values could remain as-is (will not change
    # as tables are already filled)
    $LASERTP =  rdaq_string2ftype("laser");

    $PHYSTP  =  rdaq_string2ftype("physics");
    $PHYSTP2 =
	rdaq_string2ftype("physics_adc")."|".
	rdaq_string2ftype("upsilon")."|".
	rdaq_string2ftype("btag");

    @EXPRESS = (
		rdaq_string2ftype("express"),
		rdaq_string2ftype("jpsi"),
		rdaq_string2ftype("gamma"),
		rdaq_string2ftype("mtd"),
		rdaq_string2ftype("muon"),
		rdaq_string2ftype("upcjpsi")
		);
    $ZEROBIAS=  rdaq_string2ftype("zerobias");

    # Order is: regular, bypass, calib
    @USEQ    = (5,5,5);
    @SPILL   = (0,4,4);

    # Default chain
    # $DCHAIN{"AuAu"}           = "p2007a,alltrigger,ittf,ezTree";
    # Changed Thu Apr 26 13:51:28 EDT 2007
#    $DCHAIN{"AuAu"}           = "p2007b,alltrigger,ittf,ezTree";
    $DCHAIN{"AuAu"}           = "p2007b,ittf,pmdRaw,ezTree";

    # Default stand-alone auto-calib (works ONLY on $LASERTP files)
    $SCALIB{"AuAu"}           = "OptLaser";

    # ezTree production requires some conditions. We set them here.
    # ezTree uses the Xtended Status index 1. See table in RunDAQ.pm
    $ID                   = 1;
    $EZTREE{"Status"}     = 0;
    $EZTREE{"XStatus$ID"} = 0;

    # ...
    # EzTree were processed for this trigger before
    #
    # if ( ($tmp = rdaq_string2trgs("pp2006MinBias")) != 0){
    #	# Self adapting
    #	$EZTREE{"TrgSetup"} = $tmp;
    # }

} elsif ( $ThisYear == 2008 ) {
    $TREEMODE= 1;
    $LIB     = "dev";

    $NUMEVT  = 100;
    $MINEVT  = 200;

    $TARGET  = "/star/data09/reco";       # This is ONLY a default value.
                                          # Overwritten by ARGV (see crontab)

    # Those are taken from previous yera - agreed upon as per rate, etc...
    # and documented on our Web pages.
    $LASERTP =  rdaq_string2ftype("laser");

    $PHYSTP  =  rdaq_string2ftype("physics");
    $PHYSTP2 =
	rdaq_string2ftype("physics_adc")."|".
	rdaq_string2ftype("upsilon")."|".
	rdaq_string2ftype("btag");

    @EXPRESS = (
		rdaq_string2ftype("express"),
		rdaq_string2ftype("jpsi"),
		rdaq_string2ftype("gamma"),
		rdaq_string2ftype("mtd"),
		rdaq_string2ftype("muon"),
		rdaq_string2ftype("upcjpsi")
		);
    $ZEROBIAS=  rdaq_string2ftype("zerobias");

    # Order is: regular, bypass, calib
    @USEQ    = (5,5,5);
    @SPILL   = (0,4,4);


    # Chain for 2008 starts here
    $DCHAIN{"dAu"}  = "P2008,ITTF,QAalltrigs";
    $SCALIB{"dAu"}  = "OptLaser";

} else {
    # Well, at first you may get that message ... should tell you that
    # you have to add some default values.
    print "$SELF : Unknown Year $ThisYear\n";
    exit;
}




$CHAIN   = "";

$LIB     = shift(@ARGV) if ( @ARGV );
$NUMEVT  = shift(@ARGV) if ( @ARGV );
$TARGET  = shift(@ARGV) if ( @ARGV );
$CHAIN   = shift(@ARGV) if ( @ARGV );

$tmpUQ   = shift(@ARGV) if ( @ARGV );
$tmpSP   = shift(@ARGV) if ( @ARGV );


# DO NOT MODIFY THIS unless all STAR scripts have moved elsewhere
$SPATH ="/afs/rhic.bnl.gov/star/packages/scripts";

# if we wait 1 minute between submit, and our cron
# tab executes this once every 20 minutes, max the
# return number of slots to $MAXCNT.
$SCRATCH = ".";
$LOCKF   = "FastOff.lock";
$QUITF   = "FastOff.quit";
$CONFF   = "JobSubmit$LIB.lis";
$PRIORITY= 50;                        # default queue priority    (old=100 [max], new 50 (lower the better))
$SLEEPT  =  1;                        # sleep time between submit (old=10)
$MAXCNT  = 20;                        # max job to send in a pass
$RATIO   =  2;                        # time drop down for mode + (2=twice faster)
$MAXFILL = 95;                        # max disk occupancy 
$FUZZ4C  =  3;                        # for C mode, margin is higher MAXFILL+FUZZ4C <= 100 best ;-)
$MINEVT  =  0 if (!defined($MINEVT)); # minimum number of events to consider



# Check if the quit file is present
if ( -e $QUITF){
    print "$SELF : $QUITF detected I have been asked to skip processing\n";
    rdaq_set_message($SSELF,"$QUITF detected","I have been asked to skip processing");
    exit;
}

# be sure to turn it ON
# if (rdaq_toggle_debug()){ rdaq_toggle_debug();}
# if ($DEBUG){
#    rdaq_toggle_debug(1);
# }

# Global condition wille exclude from accidental processing of junk
# puslers or lasers types. Note that EXPRESS are NOT added as they
# will be grabbed FIRST (then, if there is room, some other files).
$COND = "$PHYSTP";
if ($PHYSTP2 != 0){ $COND .= "|$PHYSTP2";}



#
# Check space on the target disk
#
if ($TARGET !~ m/^\d+$/){
    $target = $TARGET;
    $target =~ s/^\+//;
    $target =~ s/^C//;   # BEWARE !! hack here to check disk presence
    $target =~ s/^Z//;
    $target =~ s/^\^//;

    #
    # Support disk range and spanning. Syntax follows the same syntax
    # than bfcca i.e. /star/data+XX-YY where XX and YY are numbers and
    # the range will be defined as [XX,YY]
    #
    if ( $target =~ m/(.*)(\+)(\d+)(-)(\d+)(.*)/){
	$disk= $1;
	$low = $3;
	$high= $5;
	$last= $6;
    } else {
	$disk= $target;
	$low = $high = 0;
	$last= "";
    }

    $OK = 0==1;
    for( $i=$low ; $i <= $high ; $i++){
	if ( $i != 0){  $ltarget = sprintf("%s%2.2d%s",$disk,$i,$last);}
	else         {  $ltarget = $target;}

	#
	# FreeSpace file is generated from outside and especially from
	# FastOffCheck.pl which runs on the CAS farm nor on the rcrs node.
	# The main goal of this approach is that we had (pre-2007) PanFS
	# and the size could be reliably determined only from the farm
	# and not the rcrs node, hence an information passing mechanism
	# was designed.
	#
	$space = "";
	if ( -e "$ltarget/FreeSpace"){
	    $delta = time()-(stat("$ltarget/FreeSpace"))[10];
	    if ( $delta < 3600){
		print "Reading free space from $ltarget/FreeSpace\n";
		open(FI,"$ltarget/FreeSpace");
		chomp($space=<FI>);
		close(FI);
	    }
	}
	if ( $space eq ""){
	    #print "Checking $ltarget\n";
	    chomp($space = `/bin/df -k $ltarget`);
	    $space =~ m/(.* )(\d+)(%.*)/;
	    $space =  $2;
	}



	if ( $TARGET =~ m/^C/ && $space >= $MAXFILL+$FUZZ4C){
	    print "$SELF : C mode - disk $ltarget is $space % full\n";
	    rdaq_set_message($SSELF,"Target disk space notice","C mode - $ltarget is $space % full");

	} elsif ($space >= $MAXFILL ){
	    print "$SELF : Target disk $ltarget is $space % full\n";
	    rdaq_set_message($SSELF,"Target disk space notice","$ltarget is $space % full");

	} else {
	    # only one disk OK warrant a full OK
	    print "$SELF : Target disk $ltarget is $space < $MAXFILL (we shall proceed)\n";
	    $OK = 1==1;
	    last;
	}
    }

    if ( ! $OK){
	print "$SELF : Target disk(s) $target is/are full (baling out on ".localtime().")\n";
	rdaq_set_message($SSELF,"Disk Space problem","Target disk(s) $target is/are full (baling out)");
	exit;
    }
}



# Intermediate variable
$LIBV = $LIB;
if($LIB eq "cal"){ $LIB = "dev";}

$PAT = "$LIB"."_*_st_*";

# lock file mechanism prevents multiple execution of this
# script. However, prevent from crash and left over lock
# file. Notethat TARGET=1 also remove the LOCK file.
if ( -e $LOCKF){
    $date = time()-(stat($LOCKF))[9];
    if ($date > 3600){
	print "$SELF : removing $LOCKF (older than 3600 seconds)\n";
	rdaq_set_message($SSELF,"Recovery","Removing $LOCKF (older than 3600 seconds)");
	unlink($LOCKF);
    } else {
	print "$SELF : $LOCKF present. Skipping pass using target=$TARGET\n";
	rdaq_set_message($SSELF,"$LOCKF present. Skipping pass","using target=$TARGET");
    }
    exit;
}


# This will be a global selection
$SEL{"NumEvt"} = "> $MINEVT";



# Now go ...
if( $TARGET =~ m/^\// || $TARGET =~ m/^\^\// ){
    #
    # FAST OFFLINE regular mode
    #
    print "$SELF : FO regular mode\n";

    undef(@Xfiles);
    undef(@Files);

    # Overwrite queue if necessary
    $USEQ[0] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[0]= $tmpSP if ( defined($tmpSP) );

    # Default mode is submit. Target is a path
    # get the number of possible jobs per queue.
    $TOT = CRSQ_getcnt($USEQ[0],$SPILL[0],$PAT);
    $TOT = 1 if ($DEBUG);

    print "$SELF : Mode=direct Queue count Tot=$TOT\n";


    $time = localtime();
    if ($TOT > 0 && ! -e $LOCKF){
	open(FL,">$LOCKF");
	close(FL);
	#print "$SELF : We need to submit $TOT jobs\n";

	# Check $TARGET for sub-mode
	# If $TARGET starts with a ^, take only the top, otherwise
	# go into the 'crawling down the list' mode. We will start
	# with the second mode (gives an idea of how often we have
	# a dead time process earlier runs).

	if( ($obj = rdaq_open_odatabase()) ){
	    if( substr($TARGET,0,1) eq "^" ){
		# Simple with a perl module isn't it.
		print "$SELF : Top of the list only ...\n";
		$TARGET=~ s/\^//;
		if ($#EXPRESS != 0){
		    $num = int($TOT*$EXPRESS_W/100)+1;
		    push(@Xfiles,rdaq_get_files($obj,-1,$num, 1,\%SEL,@EXPRESS));
		}
		if ($ZEROBIAS != 0){
		    $num = int($TOT*$ZEROBIAS_W/100)+1;
		    push(@Xfiles,rdaq_get_files($obj,-1,$num, 1,\%SEL,$ZEROBIAS));
		}
                # we may push into @Files up to 10 times more files than
		# nevessary. But please, check the logic further down i.e.
		# if we want to submit one file per run, we have to select
		# more files first and then sub-select from that pool. To do
		# that, we separate clearly Xfiles and files and loop over the
		# first array then the second ...
		# Be aware that if $THROTTLE is 0, there will be
		# no files of the regular type.
		$W = ($TOT-$#Xfiles+1);
		push(@Files,rdaq_get_files($obj,-1,$W*($THROTTLE?10:0), 1,\%SEL,$COND));

	    } else {
		# ask only for status=0 files (will therefore
		# crawl-down the list).
		print "$SELF : Crawling down the list ...\n";
		if ($#EXPRESS != -1){
		    $num = int($TOT*$EXPRESS_W/100)+1;
		    push(@Xfiles,rdaq_get_files($obj,0,$num, 1,\%SEL,@EXPRESS));
		}
		if ($ZEROBIAS != 0){
		    $num = int($TOT*$ZEROBIAS_W/100)+1;
		    push(@Xfiles,rdaq_get_files($obj,0,$num, 1,\%SEL,$ZEROBIAS));
		}
		$W = ($TOT-$#Xfiles+1);
		push(@Files,rdaq_get_files($obj,0,$W*($THROTTLE?10:0), 1,\%SEL,$COND));
	    }

	    print "$SELF : Xfiles=$#Xfiles Files=$#Files $TARGET\n";

	    #undef($files);
	    for($ii=0; $ii<=1 ; $ii++){
		# we loop twice and separate special cases and other cases
		@files = @Xfiles if ($ii==0);
		@files = @Files  if ($ii==1);

		if($#files != -1){
		    # scramble
		    #@files = &Scramble(@files);

		    print "$SELF : Checking ".($#files+1)." jobs\n";
		    undef(@OKFILES);             # will be filled by Submit
		    undef(@SKIPPED);

		    $kk    = $TOT;
		    $prun  = 0;
		    foreach $file (@files){
			# pattern match run-number / security pattern check
			# (should not really validate and a redundant test)
			if ( $file !~ m/(\D+)(\d+)(_raw)/){
			    print "$SELF : File $file did not match pattern\n";
			    push(@SKIPPED,$file);
			} else {
			    $run  = $2;
			    #print "DEBUG:: Deduced run=$run\n";

			    # Check run-number
			    if ($prun != $run){
				$count = 0;
				$prun  = $run;
			    } else {
				#print "DEBUG:: Same run but $count cmp $THROTTLE\n";
				$count++;
				if ( $count >= $THROTTLE && $THROTTLE != 0){ next;}
			    }

			    sleep($SLEEPT) if &Submit(0,$USEQ[0],$SPILL[0],
						      $file,$CHAIN,"Normal");
			    $MAXCNT--;
			    $kk--;
			}
			last if ($MAXCNT == 0);
			last if ($kk     == 0);
		    }
		    rdaq_set_files($obj,1,@OKFILES);
		    rdaq_set_chain($obj,$SCHAIN,@OKFILES);
		    rdaq_set_files($obj,4,@SKIPPED);
		} else {
		    # there is nothing to submit
		    print "$SELF : There is nothing to submit on $time\n";
		    rdaq_set_message($SSELF,"Submitted","There is nothing to submit at this time");
		}
	    }

	    rdaq_close_odatabase($obj);
	}
	if(-e $LOCKF){  unlink($LOCKF);}
    } else {
	rdaq_set_message($SSELF,"No slots available","$USEQ[0] / $SPILL[0]","mode=direct");
    }



} elsif ($TARGET =~ m/(^\+)(.*)/ ) {
    #
    # FAST OFFLINE BYPASS
    #
    # Copied from mode 0. Can be merged ...
    #
    print "$SELF : FO bypass $TARGET\n";

    $TARGET   = $2;
    print "$SELF : Target is now $TARGET\n";

    # Overwrite queue if necessary
    $USEQ[1] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[1]= $tmpSP if ( defined($tmpSP) );


    # In this mode, read a configuration file, select those runs
    # and submit them out.
    if( ! -e $CONFF){ 
	# no conf exit
	print "$SELF : mode=bypass ; could not find $CONFF at this moment\n";
	exit;
    }

    if( ! ($obj = rdaq_open_odatabase()) ){ exit;} # no ddb abort
    if( -e $LOCKF){ exit;}                         # leave if lockf

    # read conf
    open(FI,$CONFF) || die "Could not open $CONFF for read\n";
    chomp(@all = <FI>);
    close(FI);

    if ( $#all == -1){
	exit;
    } else {
	my($tmp)=($#all+1);
	rdaq_set_message($SSELF,"Found bypass requests","$tmp line".($tmp!=1?"s":"")." to consider ".join("::",@all));
    }

    # get number of slots. Work is spill mode.
    $TOT = CRSQ_getcnt($USEQ[1],$SPILL[1],$PAT);
    $TOT = 1 if ($DEBUG);

    # Ok or not ?
    if( $TOT > 0){
	# Lock file creation
	open(FL,">$LOCKF");
	close(FL);

	print "$SELF : We can slide in $TOT jobs\n" if ($#all != -1);
	foreach $line (@all){
	    # There are 2 possibilities. The run is new
	    # or has been marked for re-run. We will recognize
	    # a new run by a run number only on a line.
	    @items = split(" ",$line);

	    if (defined($items[3]) ){
		$patt = $items[3];
	    } else {
		$patt = "";
	    }

	    if($#items == 0 || $#items == 1){
		print "$SELF : Run $line is new\n";

		if($#items == 1){
		    $cho = $items[1];
		    print "$SELF : Chain bypass $cho\n";
		} else {
		    if($CHAIN eq ""){ $CHAIN = "default";}
		    $cho = $CHAIN;
		}
		$SEL{"runNumber"} = $items[0];

		#foreach (keys %SEL){   print "XXXXDEBUG:: $_ $SEL{$_}\n";}


		@files = rdaq_get_orecords($obj,\%SEL,-1);

		if ($#files != -1){
		    print "$SELF : Resetting records to status=0 for $items[0]\n";
		    rdaq_set_files($obj,0,@files);      # Bypass: reset status to 0
		} else {
		    print "$SELF : There were no records of any kind for $items[0]\n";
		}

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
	    print "$SELF : Working with $run -> $cnt and $TOT slots\n";
	    rdaq_set_message($SSELF,"Working with run","$run -> $cnt and $TOT slots");

	    # Submit no more than $TOT jobs
	    if($#files != -1){
		undef(@OKFILES);
		undef(@SKIPPED);
		$k = -1;
		foreach $file (@files){
		    last if ($MAXCNT <= 0);    # max jobs per pass

		    last if ($TOT <= 0);       # max available queues
		    last if (($cnt-$k) <= 0);  # max file seq for this run

		    #print "$SELF : Submitting $file\n";
		    $TOT = $TOT-1;
		    $k   = $k+1;

		    if ($patt ne ""){
			if ( $file !~ /$patt/ ){
			    print "$SELF : Skipping $file not matching $patt\n";
			    push(@SKIPPED,$file);
			    next;
			}
		    }


		    sleep($SLEEPT/$RATIO) if &Submit(1,$USEQ[1],$SPILL[1],
						     $file,$cho,"Bypass");

		    $MAXCNT--;
		}
		# Mark files as submitted
		rdaq_set_files($obj,1,@OKFILES);
		rdaq_set_chain($obj,$SCHAIN,@OKFILES);
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
			$cnt = $cnt - $k if ($k != -1);
			push(@RECORDS,"$run $cnt $cho $patt");
		    }
		} else {
		    print "$SELF : Discrepency $k counted $tot success ".
			"($#OKFILES/$#SKIPPED)\n";
		    push(@RECORDS,"$run $cnt $cho $patt");
		}
	    } else {
		print "$SELF : Run $run will be ignored. No files returned by ddb\n";
		rdaq_set_message($SSELF,"Run $run will be ignored. No files returned by ddb");
	    }
	}


	# We are done scanning the runs, re-build the CONFF
	# file. Delete lock file afterward.
	open(FO,">$CONFF");
	foreach $line (@RECORDS){ print FO "$line\n";}
	close(FO);
	unlink($LOCKF);

    } else {
	rdaq_set_message($SSELF,"No slots available within range $USEQ[1] / $SPILL[1]","mode=bypass");
    }


} elsif ($TARGET =~ m/(^C\/)(.*)/ ) {
    #
    # AUTO-CALIBRATION MODE
    #
    # Overwrite queue if necessary
    $USEQ[2] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[2]= $tmpSP if ( defined($tmpSP) );

    # Default mode is submit. Target is a path
    # get the number of possible jobs per queue.
    #print "$SELF : Using $USEQ[2] $SPILL[2]\n";
    $TOT = CRSQ_getcnt($USEQ[2],$SPILL[2],$PAT,1);
    $TOT = 1 if ($DEBUG);

    $time = localtime();
    if ($TOT > 0 && ! -e $LOCKF){
	open(FL,">$LOCKF");
	close(FL);
	#print "$SELF : We need to submit $TOT jobs\n";

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
		print "$SELF : Failed. Wrong syntax\n";
	    }



	    if($#files != -1){
		print "$SELF : Checking ".($#files+1)." jobs\n";
		undef(@OKFILES);             # will be filled by Submit
		undef(@SKIPPED);
		foreach $file (@files){
		    #print "$SELF : HW : $file\n";
		    sleep($SLEEPT) if &Submit(2,$USEQ[2],$SPILL[2],
					      $file,$CHAIN,"Calibration");
		    $MAXCNT--;
		    last if ($MAXCNT == 0);
		}
		rdaq_set_files($obj,5,@OKFILES);  # special flag
		rdaq_set_chain($obj,$SCHAIN,@OKFILES);
		rdaq_set_files($obj,4,@SKIPPED);  # mark skipped
	    } else {
		# there is nothing to submit
		print "$SELF : There is nothing to submit on $time\n";
	    }
	    rdaq_close_odatabase($obj);
	}
	if(-e $LOCKF){  unlink($LOCKF);}
    } else {
	print "$SELF : Target=C - There are no slots available within range $USEQ[2] / $SPILL[2]\n";
	rdaq_set_message($SSELF,"No slots available within range $USEQ[2] / $SPILL[2]","mode=calib");
    }

} elsif ($TARGET =~ m/(^Z\/)(.*)/ ) {
    #
    # eZTree processing
    #
    # Overwrite queue if necessary

    my(%Cond);

    foreach $key (keys %EZTREE){
	$Cond{$key} = $EZTREE{$key};
    }

    # ezTree chain
    if (  $ThisYear == 2004){
	# there was one chain only
	$CHAIN   = "pp2004,ITTF,hitfilt,ezTree,-trg,-Sti,-Ftpc,-SvtD,-fcf,-Corr4";
    } else {
	if ( $DCHAIN{"PPPP"} !~ /ezTree/i){
	    $CHAIN   = $DCHAIN{"PPPP"}.",ezTree,-Sti,-genvtx,-Ftpc,-SvtD,-fcf,-fcl";
	}
    }

    $USEQ[0] = $tmpUQ if ( defined($tmpUQ) );
    $SPILL[0]= $tmpSP if ( defined($tmpSP) );

    # Default mode is submit. Target is a path
    # get the number of possible jobs per queue.
    #print "$SELF : Using $USEQ[1] $SPILL[1]\n";
    $TOT = CRSQ_getcnt($USEQ[0],$SPILL[0],$PAT,1);
    $TOT = 1 if ($DEBUG);

    print "$SELF : ezTree processing, checking $TOT\n";

    $time = localtime();
    if ($TOT > 0 && ! -e $LOCKF){
	open(FL,">$LOCKF");
	close(FL);
	print "$SELF : We need to submit $TOT jobs\n";

	# Check $TARGET for sub-mode
	# If $TARGET starts with a ^, take only the top, otherwise
	# go into the 'crawling down the list' mode. We will start
	# with the second mode (gives an idea of how often we have
	# a dead time process earlier runs).

	if( ($obj = rdaq_open_odatabase()) ){
	    if( substr($TARGET,0,1) eq "Z" ){
		# Simple with a perl module isn't it.
		$TARGET=~ s/Z\//\//;
		@files = rdaq_get_orecords($obj,\%Cond,$TOT,$COND);
	    } else {
		# Cannot do this
		print "$SELF : Failed. Wrong syntax\n";
	    }



	    if($#files != -1){
		print "$SELF : Checking ".($#files+1)." jobs\n";
		undef(@OKFILES);             # will be filled by Submit
		undef(@SKIPPED);
		foreach $file (@files){
		    #print "$SELF : HW : $file\n";
		    sleep($SLEEPT) if &Submit(1,$USEQ[0],$SPILL[0],
					      $file,$CHAIN,"eZTree");
		    $MAXCNT--;
		    last if ($MAXCNT == 0);
		}
		rdaq_set_xstatus($obj,$ID,1,@OKFILES);  # mark submitted
		rdaq_set_chain($obj,$SCHAIN,@OKFILES);
		rdaq_set_xstatus($obj,$ID,4,@SKIPPED);  # mark skipped
	    } else {
		# there is nothing to submit
		print "$SELF : There is nothing to submit on $time\n";
	    }
	    rdaq_close_odatabase($obj);
	}
	if(-e $LOCKF){  unlink($LOCKF);}
    } else {
	print "$SELF : Target=Z - There are no slots available within range $USEQ[0] / $SPILL[0]\n";
	rdaq_set_message($SSELF,"Target=XForm - No slots available within range $USEQ[0] / $SPILL[0]");
    }



} elsif ($TARGET == 1) {
    # First argument specified, check job list and results ...
    CRSQ_check($PAT,"../archive/");

    # clean lock file from default mode. Adds sturdiness
    # the process since the possibility to have a job killed while
    # a lock file was opened is non null.
    if(-e $LOCKF){ unlink($LOCKF);}


} else {
    print "$SELF : Unknown mode P3=$TARGET used\n";
}






#
# Create a job file and submit.
# Note that the full file info is received here ...
#
sub Submit
{
    my($mode,$queue,$spill,$file,$chain,$ident)=@_;
    my($Hfile,$jfile,$mfile,@items);
    my($field,$tags);
    my($trgsn,$trgrs);
    my($stagedon);
    my($destination);

    # We are assuming that the return value of $file is
    # the mode 2 of get_ffiles() and counting on the
    # elements position.
    #print "$SELF : $file\n";
    @items = split(" ",$file);
    $file  = $items[0];
    $coll  = $items[8];

    $coll  = "dAu" if ($coll eq "DeuteronAu");

    # get field as string
    $field = &rdaq_scaleToString($items[6]);

    #print "$SELF : DEBUG scale=$items[6] --> $field\n"  if ($DEBUG);
    #print "$SELF : DEBUG 10=$items[10] 11=$items[11]\n" if ($DEBUG);

    # Trigger setup string
    $trgsn = rdaq_trgs2string($items[10]);
    # Triggers  mask information
    $trgrs = rdaq_bits2string("TrgMask",$items[11]);
    # Detector setup information
    $dets  = rdaq_bits2string("DetSetMask",$items[9]);

    #print "$SELF : DEBUG 10=$trgsn 11=$trgrs\n"          if ($DEBUG);

    if($chain eq "" || $chain eq "none" || $chain eq "default"){
	$chain = $DCHAIN{$coll};
	if( ! defined($chain) ){
	    print
		"$SELF : Warning : ".localtime().
		" No chain options declared. No default for [$coll] either.\n";
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
	print "$SELF : Info : mode 2 requested and calib is empty\n";
	return 0;
    } elsif ($calib eq ""){
	# Change it to a dummy value so the
	# soft-link is created.
	#$calib = "DUMMY";
    }

    #
    # ATTENTION - Exclusions
    #
    # Those are explained in the FastOffline documentation.
    #
    # This was added according to an Email I have sent to
    # the period coordinator list. Only Jeff Landgraff
    # has answered saying we can skip the 'test' ones.
    #
    if ( $file =~ /pedestal/){
	print "$SELF : Info : Skipping $file (name matching exclusion)\n";
	push(@SKIPPED,$file);
	return 0;

    } elsif ( $trgrs eq "unknown" || $trgsn eq "unknown"){
	print "$SELF : Info : Skipping $file has unknown setup or triggers sn=$trgsn ts=$trgrs\n";
	return 0;

    } elsif ( $trgrs eq "pedestal" || $trgrs eq "pulser" ||
	 $trgsn eq "pedestal" || $trgsn eq "pulser" ){
	print "$SELF : Info : Skipping $file has setup=$trgsn 'triggers'=$items[11]=$trgrs\n";
	push(@SKIPPED,$file);
	return 0;

    } elsif ( $trgrs =~ m/test/ && $mode == 0){
	if ( $ThisYear == 2002){
	    # start with a warning
	    print "$SELF : Info : Skipping $file has 'triggers'=$items[11]=$trgrs\n";
	    push(@SKIPPED,$file);
	    return 0;
	} else {
	    print
		"Info :: $file has 'triggers'=$items[11]=$trgrs ",
		"but Year=$ThisYear not skipping it\n";
	}
    }

    # Note that skipping dets when tpc is not present is ONLY related to
    # mode 1. While mode is weakly related to regular/calib/bypass, mode Z (ezTree)
    # uses mode=1 and will therefore ACCEPT files with no tpc information in.
    if ( $dets ne "tpc" && $dets !~ m/\.tpc/){
	if ($mode != 1){
	    print "$SELF : Info : detectors are [$dets] (not including tpc) skipping it\n";
	    push(@SKIPPED,$file);
	    return 0;
	} else {
	    print "$SELF : Info : detectors are [$dets] (not including tpc) - Submitting anyway\n";
	}
    }


    # ------------ selectionn/ exclusion logic is done --------------


    # Last element will always be the Status
    # Even in ezTree mode or else, this should remain
    if($items[$#items] != 0 ){
	print "$SELF : Found status = $items[$#items] (??)\n";
	return;
    }

    # Otherwise, we do have a valid entry
    $Hfile = rdaq_file2hpss($file,3);
    @items = split(" ",$Hfile);

    # No trigger information nowadays
    $m     = sprintf("%2.2d",$items[3]);
    $dm    = $items[4];
    $jfile = join("_",$LIB,$items[2],$m,$file);
    $jfile =~ s/\..*//;
    $mfile = $file;
    $mfile =~ s/\..*//;

    # Just in case ...
    if( -e "$jfile"){
	print "$SELF : Info : $jfile exists. Ignoring for now\n";
	return 0;
    }

    # THIS IS HACK FOR 2004 data until Jeff fixes the names
    $prefix = "";
    #$prefix = "COPY_";

    # PATH are different depending on HPSS storage or local
    # Mode for UNIX is a Fast-local buffering.
    if ( $TREEMODE == 0){
	$XXX = "$LIB/$items[2]/$m";
    } else {
	if ($ThisYear < 2006){
	    $XXX = "$trgsn/$field/$LIB/$items[2]/$dm";
	} else {
	    if ( $mfile =~ m/(\d+)(_raw_)/ ){
		$run = $1;
	    } else {
		$run = 0;
	    }
	    $XXX   = "$trgsn/$field/$LIB/$items[2]/$dm/$run";
	}
    }

    if ($HPSS){
	$SCRATCH     = "/home/starreco/reco/$XXX";
	$destination = "$TARGET";  $destination =~ s/\/reco//;
	$stagedon    = "HPSS";
    } else {
	$SCRATCH     = ".";
	$destination = "$TARGET/$XXX";
	$stagedon    = "UNIX";
    }

    # Now generate the file and submit
    if( open(FO,">$jfile") ){
	if($calib ne ""){

	    # ------------------------------------------------------------------
	    # THIS IS A CALIBRATION PRE-PASS -- IT REQUIRES AN EXTRANEOUS INPUT
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
	    # THIS IS A REGULAR RECONSTRUCTION PROCESSING
	    print FO <<__EOH__;
mergefactor=1
#input
    inputnumstreams=1
    inputstreamtype[0]=HPSS
    inputdir[0]=$items[0]
    inputfile[0]=$prefix$items[1]

__EOH__
	}
	    # ------------------------------------------------------------------

	# SEVERAL OUTPUT "MAY" BE CREATED, NOTE THAT IN CALIBF MODE, $tags WILL
	# BE CHANGED TO TAKE INTO ACCOUNT THE laser.root FILE.
	print FO <<__EOF__;

#output
    outputnumstreams=5

#output stream
    outputstreamtype[0]=$stagedon
    outputdir[0]=$SCRATCH
    outputfile[0]=$prefix$mfile.event.root

    outputstreamtype[1]=$stagedon
    outputdir[1]=$SCRATCH
    outputfile[1]=$prefix$mfile.MuDst.root

    outputstreamtype[2]=$stagedon
    outputdir[2]=$SCRATCH
    outputfile[2]=$prefix$mfile.hist.root

    outputstreamtype[3]=$stagedon
    outputdir[3]=$SCRATCH
    outputfile[3]=$prefix$mfile.$tags.root

    outputstreamtype[4]=$stagedon
    outputdir[4]=$SCRATCH
    outputfile[4]=$prefix$mfile.runco.root

#    outputstreamtype[4]=$stagedon
#    outputdir[4]=$SCRATCH
#    outputfile[4]=$mfile.dst.root

#standard out
    stdoutdir=/star/rcf/prodlog/$LIB/log/daq
    stdout=$mfile.log

#standard error
    stderrdir=/star/rcf/prodlog/$LIB/log/daq
    stderr=$mfile.err
    notify=starreco\@rcrsuser3.rcf.bnl.gov

#program to run
    executable=$SPATH/bfccb
__EOF__



        # Chain default
	print FO
	    "    executableargs=25,",
	    "$LIBV,$destination,",
	    ($MAXEVT!=0?$MAXEVT:$NUMEVT),",$chain",
	    "\n";
	close(FO);

	# A returned value
	$SCHAIN = $chain;

	if( (stat($jfile))[7] == 0){
	    print "$SELF : Info : 0 size $jfile . Please, check quota/disk space\n";
	    unlink($jfile);
	    return 0;
	} else {
	    if ( ! $DEBUG ){
		if ( CRSQ_submit($jfile,$PRIORITY,$queue,$spill) ){
		    # Mark it so we can set status 1 later
		    print "$SELF : Successful submission of $file ($queue,$spill) on ".
			localtime()."\n";

		    rdaq_set_execdate($obj,undef,$file);  # set execdate, more or less meaning submit
		    rdaq_set_message($SSELF,"Submitted",$file);
		    push(@OKFILES,$file);
		    return 1;
		}
	    } else {
		rdaq_set_message($SSELF,"DEBUG is ON - There will be no submission");
		print "$SELF : DEBUG is on, $jfile not submitted\n";
		return 0;
	    }
	}
    } else {
	print "$SELF : Fatal : Could not open $jfile\n";
	return 0;
    }

}

#
# This routine was written to randomize a file list.
# Did not turn out to be usefull actually so ... but
# left anyhow in case.
#
sub Scramble
{
    my(@files)=@_;
    my(@TMP,$i,$s);

    #print "Scrambling ...\n";
    while ($#files != -1){
	$i = rand($#files+1);
	$s = splice(@files,$i,1); #print "Removing $s\n";
	push(@TMP,$s);
    }
    return @TMP;
}

