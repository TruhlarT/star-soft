#
# This module is used to get information about the CRS queue
# system. Only a few routine implemented so far.
#
#

use Carp;

package CRSQueues;
require 5.000;
require Exporter;
@ISA = qw(Exporter);

@EXPORT= qw(CRSQ_submit
	    CRSQ_getcnt
	    CRSQ_check
	    );


$STATUS="/usr/local/bin/crs_status.pl -m";
$JOBINF="/usr/local/bin/crs_status.pl -c";
$SUBMIT="/usr/local/bin/crs_submit.pl";
#$SUBMIT="/usr/crs/bin/CRS_submit_awc.pl";


#
# This routine checks the job files matching $pat
# if they are anywhere in the queue. If not, the jobfiles
# found are moved to a directory named $mdir.
#
sub CRSQ_check
{
    my($pat,$mdir)=@_;
    my($line,$jfile);
    my(@result,@JOBS);
    my($tmp);


    @result = `$JOBINF`;

    # If the following test is true, something is wrong or we are at
    # the end of the year period or we are no longer running ...
    # Most probably, something is wrong with the CRS nodes (or at 
    # least, we need to prevent it from happening again).
    if($#result == -1){ return;}


    # Get a list of jobs still in the queue
    foreach $line (@result){
	chomp($line);
	$job = (split("%",$line))[1];
	$JOBS{$job} = 1;
    }

    # Scan the current directory for all job files
    @all = glob($pat);
    
    foreach $jfile (@all){
	if( ! defined($JOBS{$jfile}) ){
	    # It is no longer in the queue. We actually cannot much more
	    # here than moving the file into the archive directory.
	    if ($jfile =~ m/(.*\/)(.*)/){
		# path was specified in pattern
		$tmp =  $2;
	    } else {
		# no path specified
		$tmp = $jfile;
	    }
	    print "CRSQ :: Job $tmp no longer in the queue on ".
		localtime()."\n";
	    rename($jfile,"$mdir/$tmp");
	}
    }
}


# Check the number of slots in queue $qnum. 
# If $drop is specified, check all queues lt than $qnum.
# If $pat is specified, check files with that wildcard pattern. If plenty
# exists, return an error. See comments for this obscure mode ...
# This can be disabled by using $nchk parameter (in case the job files
# are pre-generated, we do not want to do this check).
#
# Returns the total number of available slots.
#
sub CRSQ_getcnt
{
    my($qnum,$drop,$pat,$nchk)=@_;

    my($line);
    my(@result,@items);
    my($ATOT,$TOT,$TOTS,$NOTA,$SAVT);
    my(%NODES);
    
    # Dummy initialization
    $NOTA = $TOTS = $TOT = 0;

    # get queue status first
    @result = `$STATUS`;
    foreach $line (@result){
	chomp($line);
	@items = split("%",$line);

	if( $items[1] ne "unavailable"){
	    if ($drop){
		# In drop mode, all queues number < $qnum are available to us
		# However, we will put only 2 jobs in the 'other'
		# queues and 3 in the $qnum.
		if ($items[4] == $qnum){
		    $TOT  += $items[2];          # requested queue total
		    $NODES{$items[0]} = 1;
		} elsif ($items[4] >= ($qnum-$drop) ) {
		    $TOTS += $items[2]-1;        # other queue total
		}
	    } else {
		if ($items[4] == $qnum){
		    # choice of -1 (just the exact number) or
		    # not (add one more in the queue).
		    $TOT += $items[2]-1;         # requested queue total
		    $NODES{$items[0]} = 1;
		}
	    }
	} else {
	    $NOTA++;
	}
    }
    #print "$TOT $TOTS $NOTA\n";
    $SAVT = $TOT;
    $ATOT = $TOT+$TOTS;


    # This small test implies that the job files will be moved
    # after beeing off the queue.
    # There are cases (July 30th for example) when the CRS 
    # queues goes beserk and the crs_status does not return 
    # any information. This leads to a bad count of jobs and
    # available slots (0 actually) and subsequently, too many 
    # submission ... The pattern find will prevent this. 
    if( defined($pat) && ! defined($nchk) ){
	@all = glob($pat);
	if($#all > 10*$ATOT){ 
	    print 
		"CRSQ :: Warning on ".localtime().", there are ",
		"$#all job files found as $pat\n";
	    return -1;
	}
    }


    # Get the number of jobs actually on their way
    # to those queues. 'staging' or 'staged' jobs would not 
    # necessarily show up in the -m list. 
    # -c shows all jobs. Initial logic was a major bug because 
    # it did not account for this CRS queue peculiarity.
    # This part is relevant in no $drop mode only.
    @result = `$JOBINF`;

    foreach $line (@result){
	chomp($line);
	@items = split("%",$line);

	if ($drop){
	    if($items[4] == $qnum ){
		if( defined($NODES{$items[3]}) ||
		    $items[2] =~ /stag/){          # staged or staging
		    $TOT  = $TOT  - 1;
		}
		# Otherwise, those are dying/finishing spill-over
		# jobs. Staging and Staged jobs needs to be counted
		# because we do not not know where they belong.
	    } elsif ( $items[4] >= ($qnum-$drop) ) {
		$TOTS = $TOTS - 1;
	    }
	} else {
	    if($items[4] == $qnum){
		$TOT = $TOT - 1;
	    }
	}
    }
    #print "$TOT\n";

    # Check TOT only in non-spill mode. In spill mode, the new
    # count TOT+TOTS will give the accurate number of slots.
    if($TOT < 0 && ! $drop){ 
	$TOT = -$TOT;
	print 
	    "CRSQ :: Error: We have $TOT more jobs than expected ",
	    "(Max jobs should be $ATOT, $SAVT found, unavailable $NOTA) on ",
	    localtime()."\n";
	return -1;
    }
    undef($ATOT);
    undef(@items);
    undef(@result);


    # We don't care of what is happening to the spill-over
    # queue pool. If the count is incorrect there, just set
    # to 0.
    if($TOT < 0 && $TOTS < 0){  return 0;}
    if($TOTS < 0){              return $TOT;}
    return $TOT+$TOTS;
}



#
# Submit $jfile with priority $prio. Eventually use a queue
# shift of $drop.
#
sub CRSQ_submit
{
    my($jfile,$prio,$qnum,$drop)=@_;
    my($res);

    if ( ! -e $jfile){
	print 
	    "CRSQ :: File $jfile does not exists. ",
	    "Cannot submit to queue $qnum\n";
	0;
    }

    $res = `$SUBMIT $jfile $prio $qnum $drop`;
    $res =~ s/\n//g;
    if( $res =~ m/queue $qnum with priority $prio/){ 
	1;
    } else {
	if ( $res =~ m/(queue\s+)(\d+)/ ){
	    print "CRSQ :: Failed to submit $jfile $qnum -> $2 => [$res]\n";
	} else {
	    print "CRSQ :: Failed to submit $jfile $qnum => [$res]\n";
	}
	0;
    }
}


1;
