#!/opt/star/bin/perl
#
# Perl version of the script that sets the STAR_SYS architecture variable
#
# T. Wenaus
#
$STAR_SYS='';
if (-e '/usr/afsws/bin/sys') {$STAR_SYS=`/usr/afsws/bin/sys`}
$STAR_HOST_SYS=$STAR_SYS;

# be lazy ... leave the tedious AFS-isn't-there part for some other time!!!
# Anyway, nowadays even on Linux we have real AFS.
