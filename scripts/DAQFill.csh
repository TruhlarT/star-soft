#!/bin/csh

#
# Quick wrapper to the perl script which
# function as an infinit loop process. Safer
# this way because the cron stuff have the tendancies
# to die ...
# Will be running on some node ...
#

set PATH="/afs/rhic/star/packages/scripts"
set SCRIPT="DAQFill.pl"
set LOG="$HOME/DAQFill.log"
set ME=`whoami`

set TEST=`ps -ef | grep $ME | grep $SCRIPT | grep -v grep`


if ("$TEST" == "") then
    cd $PATH
    ./$SCRIPT >>$LOG &
endif



