#!/usr/local/bin/perl -w

# Written as interface to JProf formatting
# However, arguments are expected to be the same
# i.e. arg1 program
#      arg2 jprof-log
#
use lib "/afs/rhic/star/packages/scripts/";
use ABUtils;
    
$xprgm = shift(@ARGV) if (@ARGV);
$fprof = shift(@ARGV) if (@ARGV);

if( ! -x $xprgm){
    print "First argument must be a program name\n";
    exit;
} elsif ( ! -f $fprof){
    print "Second argument must be a profiling file\n";
    exit;
} 

if( $fprof =~ m/(.*\/)(.*)/ ){
    $path = $1; $file = $2;
} else {
    $path = "."; $file = $fprof;
}

open(STDERR,">/dev/null");
$jprof = `which jprof`;
if( ! -x $jprof){
    print "Could not locate the jprof program\n";
    exit;
}


@all = `stardev ; cd $path && jprof $xprgm $file`;
foreach $line (@all){
    if( $line =~ m/<body>/i){ $line =~ s/(.*)(<body>)(.*)/$1.IUbody().$3/}
    print $line;
}

# And that's it ...
