#! /usr/local/bin/tcsh -f
#
# $Id: manage-rcf.csh,v 1.1 1999/11/20 12:31:08 wenaus Exp $
#
# $Log: manage-rcf.csh,v $
# Revision 1.1  1999/11/20 12:31:08  wenaus
# Nightly cron management script
#
#
######################################################################
#
# manage-rcf.csh
#
# T. Wenaus
#
# Management tasks for rcf.rhic.bnl.gov, run in nightly cron
#
#

#### Build the software statistics
/afs/rhic/star/packages/dev/scripts/cron/swstat.pl
#### Build the home directory usage reports
/afs/rhic/star/packages/dev/scripts/cron/diskUsers.sh
