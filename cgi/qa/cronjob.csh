#! /usr/local/bin/tcsh 
setenv GROUP_DIR /afs/rhic/rhstar/group 
setenv CERN_ROOT /cern/pro 
setenv HOME /star/u2/jacobs 
setenv SILENT 1 
source /afs/rhic/rhstar/group/.stardev 

stardev

setenv DIR /afs/rhic/star/packages/dev/cgi/qa
setenv CRON_LOG /star/data1/jacobs/qa/batch/cronjob_logs/cronjob.log

cd $DIR
\rm -rf $CRON_LOG
QA_main.pm cron_job=server_log >& $CRON_LOG

exit
