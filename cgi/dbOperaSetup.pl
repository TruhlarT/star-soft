#!/opt/star/bin/perl -w
#
# $Id:
#
# $Log:
#
#
######################################################################
#
# dbOperaSetup.pl
#
# Wensheng Deng 9/99
#
# 
# Usage: dbOperaSetup.pl
#
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


##try to connect to 'operation' table of 'operation' database

#&StDbOperaConnect();
#&StDbOperaDisconnect();

# Tables
$OperationT = "operation";

######################
sub StDbOperaConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbOperaDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

