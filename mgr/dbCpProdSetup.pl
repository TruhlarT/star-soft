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
#$SystemData="system_data";


# Tables
$cpFileCatalogT = "cpFileCatalog";
$FilesCatalogTestT = "FilesCatalogTest";
$ProdOptionsT = "ProdOptions";
$cpJobStatusT = "cpJobStatus";
$cpjobRelationsT = "cpjobRelations";

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

