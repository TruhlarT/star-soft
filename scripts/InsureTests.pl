#!/usr/local/bin/perl -w

#
# this script was developped to provide a quick and easy Insure
# test running platform. Sub-directories will be auto-created
# according to test chain. For Insure, there is no real need
# to run multiple times the same chain since the intent is NOT 
# to test the physics results but the code sanity ...
#
# Written J.Lauret Apr  3 2001. Copy in /star/rcf/test/dev/Insure/
# History
#  Apr 13 2001 ; JL added real events chain.
#
use lib "/afs/rhic/star/packages/scripts";
use ABUtils;



# All tests may be declared here in this array. The first element is the chain
# the seconde a list of files to work on. Note that the array will be later
# sorted so no need to try to put the chain in a different order, hoping
# this script will do something different.
%TESTS=IUTests();
$SRCDIR=IUTestDir();



# ------ No Changes below this line -------------------------------------

# Parse arguments if any
for($i=0 ; $i <= $#ARGV ; $i++){
    $arg = $ARGV[$i];
    if( substr($ARGV[$i],0,1) eq "-"){
	# consider it an option
	if ($arg eq "-d"){
	    # Delete all directories option. Maintainance
	    print "Are you sure you do delete all directories in $SRCDIR ? ";
	    chomp($ans = <STDIN>); if($ans eq ""){ $ans = "no";}
	    if($ans =~ m/y/i){
		chomp(@dirs = `cd $SRCDIR ; find . -type d`);
		foreach $el (@dirs){
		    if($el ne "."){
			print "Deleting $el\n";
			system("cd $SRCDIR ; rm -rf $el");
		    }
		}
	    }
	    exit;
	}
    } else {
	push(@ARG,$arg);
    }
}
undef(@ARGV);


# Sort array now, transfer i into another associative array.
foreach $el (keys %TESTS){
    @items = split(" ",$el);
    @items = sort(@items);
    $chain = join(" ",@items);
    push(@CHAINS,$chain);
    $STESTS{$chain} = $TESTS{$el};
}
undef(%TESTS);



if($#ARG == -1){
    print 
	"You may enter several tests separated by space or one\n",
	"per line. Press return to end input.\n";
    do {
	for($i=0 ; $i <= $#CHAINS ; $i++){
	    printf "%4d --> %s\n",$i,$CHAINS[$i];
	}
	print "Test number : ";
	chomp($choice = <STDIN>);
	if($choice ne ""){ push(@ARG,split(" ",$choice));}
    } while($choice ne "");
}


# test all choices
print "You chose test(s) [".join(" ",@ARG)."]\n";
foreach $choice (@ARG){
    # Now we know
    $chain = $CHAINS[$choice];

    # trying to trick me ??
    if( ! defined($chain) ){    
	print "Illegal choice $choice ...\n";
	next;
    }

    # else, multiple files may be used. Several tests will follow
    print "\n*** $chain ***\n";

    $dir   = $chain;
    $dir   =~ s/ /_/g;
    @files = split(" ",$STESTS{$chain});
    for($i=0 ; $i <= $#files ; $i++){
	$file = $files[$i];
	if(! -e $file){  die "$file cannot be seen from ".`hostname`."\n";}
	print "Doing [$chain] on $file\n";
	# Ready to produce a running script
	# Create directory
	if( ! chdir($SRCDIR) ){ die "Cannot change directory to $SRCDIR\n";}
	
	if(! -d "$dir"){ 
	    print " - Directory $dir created\n";
	    mkdir($dir,0755); 
	}
	print " - Changing directory to $dir\n";
	if( ! chdir($dir) ){ die "Could not change directory to $dir\n";}

	$script = "script$i.csh";
	if( -e $script){ unlink($script);}

	# ********* MODIFY THIS IF NECESSARY ************
	IUresource("$SRCDIR/$dir/insure$i.log"," - creating .psrc file");
	print " - Creating a script file\n";
	open(FO,">script$i.csh") || die "Could not open file for write\n";
	print FO 
	    "#\!/bin/csh\n",
	    "# Script created on ".localtime()."\n",
	    "# by $0. Written J.Lauret\n",
	    "source ~/.cshrc\n",
	    IULoad()."\n",
	    "cd $SRCDIR/$dir\n",
	    "\n",
	    "# Display result\n",
	    "echo \"Path   = \$PATH\"\n",
	    "echo \"LDPath = \$LD_LIBRARY_PATH\"\n",
	    "echo \"STAR   = \$STAR\"\n",
	    "echo \"root4* = \" `which root4star`\n",
	    "echo \"CDir   = \" `pwd`\n",
	    "\n",
	    "setenv StarEndMakerShell\n",
	    "rm -f *.root\n",
	    "\n",
	    "root4star -b -q 'bfc.C(2,\"$chain\",\"$file\")'\n";

	close(FO);
	chmod(0770,"$SRCDIR/$dir/$script");

	print " - Running it now\n";
	system("$SRCDIR/$dir/$script"); # we can also trapped the returned error
	if( -e "$SRCDIR/$dir$i.html"){ unlink("$SRCDIR/$dir$i.html");}
	system(IURTFormat()." $SRCDIR/$dir/insure$i.log >$SRCDIR/$dir$i.html");

    }
}




