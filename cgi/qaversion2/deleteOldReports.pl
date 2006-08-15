#!/usr/local/bin/perl -I/usr/lib/perl5/5.00503 -I/usr/lib/perl5/site_perl/5.005 -I/usr/lib/perl5/site_perl/5.005/i386-linux/ -I/afs/rhic.bnl.gov/star/starqa/qa01/libRCAS/lib/site_perl
#
# Removes all report directories older than 2 weeks, also deletes those entries
# from the QA db

#QA db stuff
use CGI qw/:standard :html3/;
use DataClass_object;
use Server_object;
use QA_globals;
use QA_db_utilities qw(:db_globals);
use Db_update_utilities;
use Db_KeyList_utilities;
use KeyList_object_offline;
use IO_object;
use KeyList_object_nightly;
use Time::Local;
use Storable;

use strict;

$gServer_object = new Server_object;

my $dataClasses = ["nightly_MC", "nightly_real", "offline_MC",
		   "offline_fast", "offline_real"];

#my $twoWeeks = time() - 60*60*24*14;  # 2 weeks ago
#my $twoMonths = time() - 60*60*24*61;  # 2 months ago

foreach my $dataClass (@$dataClasses){

    delete_old_reports($dataClass);

} # foreach dataClass

exit(0);

sub delete_old_reports{

    my $dataClass = shift;
    print "delete_old_reports(\"$dataClass\")\n";

    $gDataClass_object = new DataClass_object($dataClass);
    QA_db_utilities::db_connect();
    
    my $io_dir = new IO_object("TopdirReport");
    my $dir_name = $io_dir->Name();

    # determine old report files from the database.

    no strict 'refs';

    # delete the jobs from the db
    # get cut days from Db_update_utilties
    #my $cutDays = 30;  # 1 month
    #($dataClass eq "offline_fast" or $dataClass eq "nightly_MC") and
    #	$cutDays = 7; # 1 week
    
    my $cutDays = $Db_update_utilities::oldestDay{$dataClass};
    print "cut=$cutDays\n";

    # this sub deletes the jobs from the db
    my @old_report_keys = &{$gDataClass_object->GetOldReports()}($cutDays);

    if (not defined @old_report_keys){
	print h4("No report files to delete\n") ;
	return;
    }

    # now delete them from disk

    foreach my $report_key (@old_report_keys){
	my $name      = "$dir_name/$report_key";
	
	print "rm -rf $name<br> \n";
	print `rm -rf $name`;

    } # foreach report_key

    QA_db_utilities::db_disconnect();
}


