#! /usr/local/bin/tcsh -f
#
# $Id: manage-rcf.csh,v 1.2 2001/07/18 19:36:01 jeromel Exp $
#
# $Log: manage-rcf.csh,v $
# Revision 1.2  2001/07/18 19:36:01  jeromel
# Changed explicit path from dev/scripts to scripts
#
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
/afs/rhic/star/packages/scripts/cron/swstat.pl
#### Build the home directory usage reports
/afs/rhic/star/packages/scripts/cron/diskUsers.sh
