#!/opt/star/bin/perl -w

#
# This script checks if jobs are done or not.
# Done jobs are simply based on the appearance of
# the root files associated to the job.
# this script is meant to run in a cronjob ...
#
# There is NOTHING to change from this script.
# Use arguments like
#
# .../FastOffCheck.pl dev /star/data27/reco 12
#
# where
#  arg1 is the directory to scan
#  arg2 the path where the files are supposed to appear
#  arg3 a retention time for the output in days
#

use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use RunDAQ;

$LIB     = "dev";
$TARGET  = "/star/data19/reco";
$UPDATE  = 0;
$RETENT  = 14;

$LIB     = shift(@ARGV) if ( @ARGV );
$TARGET  = shift(@ARGV) if ( @ARGV );
$RETENT  = shift(@ARGV) if ( @ARGV );
$UPDATE  = shift(@ARGV) if ( @ARGV );   # 0, scan and delete if old,
                                        # 1, scan and enter in db
                                        # 2, get db entries and compare

# Assume standard tree structure
$JOBDIR    = "/star/u/starreco/$LIB/requests/daq/archive/";
$SCRATCH   = defined($ENV{SCRATCH})?$ENV{SCRATCH}:"/tmp/$<";
$SPACEPRGM = $ENV{STAR_SCRIPTS}."/dfpanfs";


if ( ! -d $SCRATCH){  mkdir($SCRATCH);}

# Fault tolerant. No info if fails.
if( ! opendir(DIR,"$JOBDIR") ){
    print "$JOBDIR does not exists\n";
    exit;
}

if ($UPDATE == 0){
    print "Scanning $JOBDIR vs $TARGET on ".localtime()."\n";

    if ( -e $SPACEPRGM ){
	chomp($space = `$SPACEPRGM  $TARGET`);
	$space =~ m/(.* )(\d+)(%.*)/;
	$space =  $2;
	open(FO,">$TARGET/FreeSpace");
	print FO "$space\n";
	close(FO);
    }

    while( defined($jfile = readdir(DIR)) ){
	#print "$jfile\n";
	if( $jfile =~ /(.*_)(st_.*)/){
	    $tree = $1;
	    $file = $2;

	    #print "$jfile Tree=$tree file=$file\n";

	    $tree =~ s/_/\//g;
	    chop($tree);        # remove trailing '/'
	    if( -e "$JOBDIR/old/$jfile.checked"){
		@stat1 = stat("$JOBDIR/old/$jfile.checked");
		@stat2 = stat("$JOBDIR/$jfile");
		if ( $stat1[10] >= $stat2[10]){
		    next;
		} else {
		    print "$jfile is more recent than last check. Rescan\n";
		    unlink("$JOBDIR/old/$jfile.checked");
		}
	    }

	    # double check the conformity of the job file name
	    if( $tree !~ m/$LIB/){
		print "WARNING :: Ill-formed $jfile found in $JOBDIR\n";
		push(@MOVE,$jfile);
	    } else {
		if ( ! -e "$SCRATCH/$file.done"){
		    open(FF,">$SCRATCH/$file.done"); close(FF);
		    #print "Searching for $file\n";
		    chomp($lfile = `cd $TARGET ; /usr/bin/find -type f -name $file.MuDst.root`);
		    if( $lfile ne ""){
			# found it so it is done.

			@info = stat($lfile);
			if ( $info[7] == 0){   next;}

			($tree,$el) = $lfile =~ m/(.*\/)(.*)/;
			chop($tree);
			$tree =~ s/\.\///;
			
			#print " $el --> $TARGET/$tree\n";

			$LOCATIONS{"$file.daq"} = "$TARGET/$tree";
			push(@DONE,"$file.daq");
			push(@MOVE,$jfile);
		    } else {
			#print "Could not find $TARGET/$tree/$file.MuDst.root\n";
		    }
		}
	    }
	}
    }
    closedir(DIR);


    if( ! -d "$JOBDIR/old"){  mkdir("$JOBDIR/old",0755);}

    # Also scan the main tree for obsolete files
    if( -d $TARGET){
	#print "Searching for f in $LIB from $TARGET\n";
	if ( -e "$TARGET/$LIB"){
	    chomp(@all = `cd $TARGET ; /usr/bin/find $LIB -type f -mtime +$RETENT`);
	} else {
	    push(@all,`cd $TARGET ; /usr/bin/find -type f -mtime +$RETENT`);
	    push(@all,`cd $TARGET ; /usr/bin/find -type f  -empty`) if ( $^O =~ /linux/);
	    chomp(@all);

	    @all = grep(!/StarDb/,@all);
	}
	foreach $el (@all){
	    print "Deleting $TARGET/$el\n";
	    unlink("$TARGET/$el");
	    $el =~ s/.*\///g;
	    $el =~ s/\..*//;
	    $el .= ".daq";

	    if( ! defined($LOCATIONS{$el}) ){
		$LOCATIONS{$el} = 0;
	    }
	}
    }


    $obj = rdaq_open_odatabase();
    if($obj){
	foreach $el (keys %LOCATIONS){
	    if( ! rdaq_set_location($obj,$LOCATIONS{$el},$el) ){
		print "Failed to set location for $el\n";
	    }
	}

	print "Setting files with status=2 if status=1 [".join(" ",@DONE)."]\n";
	rdaq_toggle_debug(1);
	rdaq_set_files_where($obj,2,1,@DONE);
	rdaq_close_odatabase($obj);

	foreach $jfile (@MOVE){
	    open(FO,">$JOBDIR/old/$jfile.checked");
	    print FO "$0 ".localtime()."\n";
	    close(FO);
	}
    }
} elsif ($UPDATE == 1) {
    # Scan the directory for all files present and mark their
    # path in the database. This is rarely used. And done
    # only to update the database with a new location
    # directory if files are moved ...
    $obj = rdaq_open_odatabase();
    if($obj){
	chomp(@all = `cd $TARGET ; /usr/bin/find $LIB -type f -name '*.MuDst.root'`);
	foreach $el (@all){
	    $el =~ m/(.*\/)(.*)/;
	    ($tree,$el) = ($1,$2);
	    $el =~ s/\..*//;
	    $el .= ".daq";

	    chop($tree);
	    if( ! defined($LOCATIONS{$el}) ){
		$LOCATIONS{$el} = "$TARGET/$tree";
	    }
	}

	foreach $el (keys %LOCATIONS){
	    rdaq_set_location($obj,$LOCATIONS{$el},$el);
	}
	rdaq_close_odatabase($obj);
    }

} else {
    $obj = rdaq_open_odatabase();
    @all = rdaq_get_files($obj,2,0);
    foreach $file (@all){
	if ( $path  = rdaq_get_location($obj,$file) ){
	    $qfile = $ffile = $file;
	    $ffile =~ s/\.daq/\.event\.root/;
	    $qfile =~ s/\.daq/\.hist\.root/;

	    if ( ! -e "$path/$ffile"){
		rdaq_set_location($obj,0,$file);
		print "$path $ffile not found\n";
	    } else {
		foreach $tfile (("$path/$ffile","$path/$qfile")){
		    # we will require for this to have both event and hist
		    # present or disable it
		    if ( -e $tfile){
			@info = stat($tfile);
			if ( $info[7] == 0){
			    # disable those records
			    print "Bogus zero size file found $tfile\n";
			    rdaq_set_location($obj,0,$file);
			} else {
			    #if ( $file =~ /794028/){
			    #print "Found $file\n";
			    #}
			}
		    }
		}
	    }
	}
    } 
    
}

