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

if ( "$1" == "") then
  set TEST=`ps -ef | grep $ME | grep $SCRIPT | grep -v grep`
  if ("$TEST" == "") then
    cd $PATH
    ./$SCRIPT >>$LOG &
  endif

else if ( "$1" == "Clean") then
  # since AFS fluke may induce strange effects
  set TEST=`ps -ef | grep $ME | grep $SCRIPT | grep -v grep | awk '{print $2}' | xargs`
  if ("$TEST" != "") then
    kill -9 $TEST
  endif

else if ( "$1" == "Update") then
  # Run the script in update mode i.e. fetch intermediate records
  # we may have missed  
  cd $PATH 
  ./$SCRIPT 1 >&/dev/null 

endif





