#!/opt/star/bin/perl -w
#
# $Id: dbbackup.pl,v 1.1 1999/07/09 12:41:59 wenaus Exp $
#
######################################################################
#
# dbbackup.pl
#
# T. Wenaus 7/99
#
# Manages MySQL DB backup. For use in a cron job.
#
# Usage:    dbbackup.pl 
#
# $Log: dbbackup.pl,v $
# Revision 1.1  1999/07/09 12:41:59  wenaus
# cron script to back up databases
#
#

$debugOn = 0;

## Databases to be backed up, and the number of backup files to keep
%dbToBackup = (
               'system_data' => 2,
               'mysql' => 2
               );

$backupDir = '/star/sol4/duvall/archive/mysql';

foreach $db ( keys %dbToBackup ) {
    ## Back up the desired databases
    ($dy,$mo,$yr) = (localtime())[3,4,5];
    $mo++;
    $yr=$yr+1900;
    $cdate = sprintf("%4.4d%2.2d%2.2d",$yr,$mo,$dy);
    $fname = "$db-$cdate.sql.gz";
    $out = `mysqldump --opt $db | gzip > $backupDir/$fname`;
    if ( $out ne '' ) {print $out}

    ## Keep only the most recent nToKeep for each DB
    @files = split(/\n/,`cd $backupDir; ls -1 $db*`);
    # sort the list and delete from the top
    $nf = 0;
    foreach $fl ( reverse sort @files ) {
        $nf++;
        if ( $nf > $dbToBackup{$db} ) {
            $out = `rm -f $backupDir/$fl`;
            if ( $out ne '' ) {print $out}
        }
        print "Sorted ".$fl."\n" if $debugOn;
    }
}

