#!/bin/csh

#
# test token. Works for both Solaris and Linux.
# Is silent if there is a token.
# Complains otherwise.
#
set TEST=`tokens | grep afs@rhic | sed "s/\[.*//"`
set USER=`id | sed "s/).*//" | sed "s/.*(//"`
if( "$TEST" == "") then
    echo "There is no token for $USER on `hostname` at `date`"
endif

