#!/opt/star/bin/perl
#
# $Id: group_env.pl,v 1.1 1999/07/29 17:58:00 wenaus Exp $
#
# $Log: group_env.pl,v $
# Revision 1.1  1999/07/29 17:58:00  wenaus
# Set up the STAR environment needed by perl scripts
#
#
######################################################################
#
# group_env.pl
#
# T. Wenaus 7/99
#
# Set up the STAR environment needed by perl scripts
#

use lib "/afs/rhic/star/group";

## STAR environment setup
$STAR_ROOT="/afs/rhic/star";
$GROUP_DIR="$STAR_ROOT/group";
$STAR_PATH="$STAR_ROOT/packages";
if ( ! $STAR_LEVEL ) {$STAR_LEVEL="pro"}
$STAR_VERSION = (fileparse(readlink("$STAR_PATH/$STAR_LEVEL")))[0];
if ( ! $STAR ) {$STAR="$STAR_PATH/$STAR_VERSION"}
require "STAR_SYS.pl";  # define $STAR_HOST_SYS
$STAR_LIB="$STAR/.$STAR_HOST_SYS/lib";
$MINE_LIB=".$STAR_HOST_SYS/lib";
$STAR_BIN="$STAR/.$STAR_HOST_SYS/bin";
$STAR_MGR="$STAR/mgr";
$STAR_PAMS="$STAR/pams";
$STAR_DATA="$STAR_ROOT/data";
$STAR_PARAMS="$STAR/params";
$STAR_CALIB="$STAR_ROOT/calib";
$STAR_PROD="$STAR/prod";
$STAR_CVSROOT="$STAR_PATH/repository";
$ROOT_LEVEL='';
if ( -e "$STAR/mgr/ROOT_LEVEL" ) {$ROOT_LEVEL=`cat $STAR/mgr/ROOT_LEVEL`}
$CERN_LEVEL='';
if ( -e "$STAR/mgr/CERN_LEVEL" ) {$CERN_LEVEL=`cat $STAR/mgr/CERN_LEVEL`}
$STAR_PATH="/usr/afsws/bin:/usr/afsws/etc:/opt/star/bin:/usr/sue/bin:/usr/local/bin:$GROUP_DIR:$STAR_MGR:$STAR_BIN";
$CERN="/cern";
$CERN_ROOT="$CERN/$CERN_LEVEL";

my $systype = substr($STAR_HOST_SYS,0,4);
if ( $systype eq 'sun4' ) {
    $LD_LIBRARY_PATH="/opt/SUNWspro/lib:/usr/openwin/lib:/usr/dt/lib:/usr/local/lib:/afs/rhic/star/packages/ObjectSpace/2.0m/lib:$MINE_LIB:$STAR_LIB:/usr/lib";
} elsif ( $systype eq 'i386' ) {
    $STAR_PATH.=":/usr/local/bin/ddd";
    $LD_LIBRARY_PATH="/usr/lib:/usr/local/lib:$MINE_LIB:$STAR_LIB:/usr/dt/lib:/usr/openwin/lib";
} else {
    $LD_LIBRARY_PATH="/opt/SUNWspro/lib:/usr/openwin/lib:/usr/dt/lib:/usr/local/lib:/afs/rhic/star/packages/ObjectSpace/2.0m/lib:$MINE_LIB:$STAR_LIB:/usr/lib";
}
$LD_LIBRARY_PATH.=":/usr/ccs/lib:/opt/star/lib";
