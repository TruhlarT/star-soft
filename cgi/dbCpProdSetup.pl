#!/opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
# L.Didenko
######################################################################
#
# dbcpProdSetup.pl
#

use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


# Tables
$FileCatalogT = "FileCatalog2000-2003";
$ProdOptionsT = "ProdOptions";
$JobStatusT = "JobStatus2000-2003";
$TriggerEventsT = "TriggerEvents";
$jobRelationsT = "jobRelations";
$DAQInfoT = "DAQInfo";
$crsStatusT = "crsStatus";

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

