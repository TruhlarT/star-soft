#! /usr/bin/perl -w

# Contains utility methods for using the LSF and at
# batch systems
# BEN:  31 may 2000

#========================================================
package Batch_utilities;
#========================================================
use strict;
use IO_object;

# this should be "LSF" for lsf and "AT" for at
# my $batchType = "AT";
my $batchType = "AT";
# queue to use on LSF
my $lsfQueue = "star_cas_short";

#========================================================
# return true on loading
#========================================================
1.;

#========================================================
# submit a batch job using the default mechanism (at or bsub)
# 
# Batch_utilities->SubmitJob($commandName)
#
# $commandName should the name of a script to run as a 
# batch job
#
# returns the job id prefixed by LSF or AT
#========================================================
sub SubmitJob
{
    my $cmd = shift;
#print "Batch_utilities::SubmitJob($cmd)";

    if ($batchType eq "AT")
    {
	return SubmitAtJob($cmd);
    }
    elsif ($batchType eq "LSF")
    {
	return SubmitLSFJob($cmd);
    }
}

#========================================================
# return the status of all QA batch jobs
#
# Batch_utilities->Queue()
#
# the return will be a multiple-line string containing
# all the output from the batch status command used
# (atq, bjobs)
#========================================================
sub Queue
{
#print "Batch_utilities::Queue()";
    if ($batchType eq "AT")
    {
	return AtQueue();
    }
    elsif ($batchType eq "LSF")
    {
	return LSFQueue();
    }
}

#========================================================
# submit an LSF batch job using 'bsub'
# 
# Batch_utilities->SubmitLSFJob($commandName)
#
# $commandName should the name of a script to run as a 
# batch job
#
# returns the lsf job id prefixed by LSF
#========================================================
sub SubmitLSFJob
{
    my $cmd = shift;

    # user to notify on job begin and end
    my $notifyEmail = "starqa\@rcf.rhic.bnl.gov";  

    # unique (someday, perhaps...) name of job in batch system
    my $jobName = "QATEST";

    # -N == notify on job completion
    # -B == notify on job dispatch
    my $cmdStr = 
	"bsub -N -B -u $notifyEmail -J $jobName -q $lsfQueue \"$cmd\"";
    my $retStr = `$cmdStr`;

    # extract job ID from output
    $retStr =~ /^[^<]*<([^>]*)>.*$/m;
    return "LSF" . $1;
}

#========================================================
# submit a batch job using 'at'
# 
# Batch_utilities->SubmitAtJob($commandName)
#
# $commandName should the name of a script to run as a 
# batch job
#
# returns the at job id prefixed by AT
#========================================================
sub SubmitAtJob
{
    my $cmd = shift;

    my $cmdStr = "at -f \"$cmd\" now";
    my $retStr = `$cmdStr`;
    
    # extract job ID from output
    $retStr =~ /^job ([^ ]*) .*$/m;
    return "AT" . $1;

}

#========================================================
# return the status of all running at jobs
#
# Batch_utilities->AtQueue()
#
# the return will be a multiple-line string containing
# all the output from atq
#========================================================
sub AtQueue
{
    return `atq`;
}

#========================================================
# return the status of all running lsf jobs
#
# Batch_utilities->LSFQueue()
#
# the return will be a multiple-line string containing
# all the output from bjobs
#========================================================
sub LSFQueue
{
    return `bjobs`;
}

#========================================================
# 
#========================================================
