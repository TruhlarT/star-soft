#! /usr/local/bin/tcsh -f

\rm -rf ${1}
crontab -l >& ${1}

