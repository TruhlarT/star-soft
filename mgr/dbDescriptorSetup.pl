#!/opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
# L.Didenko
######################################################################
#
# dbDescriptorSetup.pl
#

use DBI;

$dbhostc="onlsun1.star.bnl.gov:3306";
$dbuserc="dbmole";
$dbpassc="quegp23";
$dbnamec="RunLog";
#$dbport="3316";


# Tables
$runDescriptorT = "runDescriptor";
$daqDescriptorT = "daqDescriptor";

######################
sub StDbDescriptorConnect {
    $dbh = DBI->connect("dbi:mysql:$dbnamec:$dbhostc", $dbuserc, $dbpassc)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbDescriptorDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

