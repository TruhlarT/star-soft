#!/opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
# L.Didenko
######################################################################
#
# dbProdSetup.pl
#

use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="dbUser@*";
$dbname="operation";


# Tables
$FileCatalogT = "FileCatalog2004";
$ProdOptionsT = "ProdOptions";
$JobStatusT = "JobStatus2004";
$TriggerEventsT = "TriggerEvents";
$DAQInfoT = "DAQInfo";
$crsStatusT = "crsStatus";
$TriggerSetT = "TriggerSet";

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

