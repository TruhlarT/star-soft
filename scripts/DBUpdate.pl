#!/opt/star/bin/perl -w

#
# This script scans a disk given as the first argument
# checks all files and update the database with a file
# location new netry if it finds the same entry as
# storage = HPPS.
#
# It uses the clone_location() method to update the 
# database with that entry and is a very good example
# of how to do this ...
#
# ***
#  This is REALLY a spider ... It is used to post-scan 
#  disk and catch entries which may be missing. 
#  
#  Only clones (if there is no similar entries in the db,
#  it won't add it).
# ***
#
# BEWARE : 
#  (1) $SITE and $HPSSD are global variables
#  (2) There is an hidden logic based on $path !~ /\/star\/data/
#      to recognized if the storage is local or NFS.
#

use lib "/afs/rhic/star/packages/scripts";
#use lib "/star/u/jeromel/work/ddb";
use FileCatalog;
use Date::Manip;


if ($#ARGV == -1){
    print qq~
 Syntax is
  % DBUpdate.pl BasePath [fileExtension] [RelPathOverwrite] [Substitute]
    [user] [password]

 Arguments are
   ARGV0   the base path of a disk to scan (default /star/data06)
   ARGV1   the filetype (default .MuDst.root ). If null, it will
           search for all files.
   ARGV2   this scripts limits it to a sub-directory "reco" starting
           from ARGV0. Use this argument to overwrite.
   ARGV3   A base path substitution for find the entry in HPSS
           Default is /home/starreco .

   ARGV4   a user name (default FC_admin)
   ARGV5   a password (default is guessed)


 Examples
  % DBUpdate.pl /star/data27
  % DBUpdate.pl /star/data27 ""
  % DBUpdate.pl /star/data03 .daq daq /home/starsink/raw

 ~;
    exit;
}


$SITE  = "BNL";
$HPSSD = "/home/starreco";

$SCAND = "/star/data06";
$USER  = "";
$PASSWD= "";
$SUB   = "reco";

# Argument pick-up
$SCAND = shift(@ARGV) if (@ARGV);
$FTYPE = shift(@ARGV) if (@ARGV);
$SUB   = shift(@ARGV) if (@ARGV);
$HPSSD = shift(@ARGV) if (@ARGV);
$USER  = shift(@ARGV) if (@ARGV);
$PASSWD= shift(@ARGV) if (@ARGV);


#@ALL =( "$SCAND/$SUB/FPDXmas/FullField/P02ge/2002/013/st_physics_3013016_raw_0018.MuDst.root",
#	"$SCAND/$SUB/FPDXmas/FullField/P02ge/2002/013/st_physics_3013012_raw_0008.MuDst.root");


$DOIT  = ($#ALL == -1);


if ( ! defined($FTYPE) ){  $FTYPE = ".MuDst.root";}


if( $DOIT ){
    if ($FTYPE ne ""){
	print "Searching for all files like '*$FTYPE' ...\n";
	@ALL   = `find $SCAND/$SUB -type f -name '*$FTYPE'`;
	print "Found ".($#ALL+1)." files to add (x2)\n";
    } else {
	print "Searching for all files ...\n";
	@ALL   = `find $SCAND/$SUB -type f`;
	print "Found ".($#ALL+1)." files to add (x2)\n";
    }
}

if ($#ALL == -1){ exit;}


$fC = FileCatalog->new();


# Get connection fills the blanks while reading from XML
# However, USER/PASSWORD presence are re-checked
#$fC->debug_on();
($USER,$PASSWD,$PORT,$HOST,$DB) = $fC->get_connection("Admin");
$port = $PORT if ( defined($PORT) );
$host = $HOST if ( defined($HOST) );
$db   = $DB   if ( defined($DB) );


if ( defined($USER) ){   $user = $USER;}
else {                   $user = "FC_admin";}

if ( defined($PASSWD) ){ $passwd = $PASSWD;}
else {                   print "Password for $user : ";
                         chomp($passwd = <STDIN>);}





#
# Now connect
#
$fC->connect($user,$passwd,$port,$host,$db);

#$fC->debug_off();

$failed = $unkn = $old = $new = 0;

#$fC->set_delimeter(",");             # Make it easier to parse
$fC->set_silent(1);                  # Turn OFF messaging

# Make a main context
# Temporary so we get it once only
chomp($NODE    = `hostname`);





foreach  $file (@ALL){
    chomp($file);

    # We need to parse the information we can 
    # save in the ddb
    $file =~ m/(.*\/)(.*)/;
    $path = $1; $file = $2;
    chop($path);
    $hpath= $path;
    $hpath=~ s/$SCAND/$HPSSD/;

    
    # Is a disk copy ??
    $fC->clear_context();
    if ( $path =~ m/\/star\/data/){
	$node    = "";
	$storage = "NFS";
	$fC->set_context("path = $path","filename = $file","storage = NFS","site = $SITE");

    } else {
	$storage = "local";
	$node    = $NODE;
	$fC->set_context("path = $path","filename = $file","storage = local","site = $SITE",
			 "node = $NODE");
    }
    @all1 = $fC->run_query("size");



    # HPSS copy (must be the last context to use clone_location() afterward )
    $fC->clear_context();
    $fC->set_context("path = $hpath","filename = $file","storage = HPSS","site = $SITE");
    @all = $fC->run_query("size");



    if ($#all == -1){
	$unkn++;
	print STDERR "Did not find $path $file in HPSS\n";

    } else {
	$mess = "Found ".($#all+1)." records for $file " if ($#all > 0);

	@stat   = stat("$path/$file");

	if ($#stat == -1){  
	    print "/!\ stat($path/$file) failed\n";
	    next;
	}

	#if( $stat[7] != 0){  
	#    $sanity = 1;
	#} else {
	#    $sanity = 0;
	#}


	if ($#all1 != -1){
	    $old++;
	    #print "$mess Already in ddb\n";

	} else {
	    #print "Cloning $hpath $file\n";
	    if ( ! $fC->clone_location() ){
		print "Cloning of $file did not occur\n";

	    } else {
		print "$mess File cloned ".sprintf("%.2f %%",($new/$#ALL)*100)."\n" 
		    if ($new % 10 == 0);
		$fC->set_context("persistent= 0");
		
		#chomp($node = `hostname`);
		
		$fsize = $stat[7];
		@own   = getpwuid($stat[4]);
		$prot  = &ShowPerms($stat[2]);
		#$dt    = &UnixDate(scalar(localtime($stat[10])),"%Y%m%d%H%M%S");
		$fC->set_context("path       = $path",
				 "storage    = $storage",
				 "persistent = 0",
				 "size       = $fsize",
				 "owner      = $own[0]",
				 "protection = $prot",
				 "available  = 1",
				 "site       = $SITE");
		if ( $node ne ""){
		    $fC->set_context("node       = $node");
		}
		
		if ( ! $fC->insert_file_location() ){
		    print "\tAttempt to insert new location $path failed\n";
		    $failed++;
		} else {
		    $new++;
		}
	    }
	}


    }
}

$fC->destroy();

print 
    "Unkown = $unkn\n",
    "Old    = $old\n",
    "New    = $new\n",
    "Failed = $failed\n";





# This sub has been taken from fcheck software
# as-is (was too lazzy to get it done by myself)
sub ShowPerms
{
    local ($mode) = @_;

    local (@perms) = ("---", "--x",  "-w-",  "-wx",  "r--",  "r-x",  "rw-",  "rwx");
    local (@ftype) = ("?", "p", "c", "?", "d", "?", "b", "?", "-", "?", "l", "?", "s", "?", "?", "?");
    local ($setids) = ($mode & 07000)>>9;
    local (@permstrs) = @perms[($mode & 0700) >> 6, ($mode & 0070) >> 3, ($mode & 0007) >> 0];
    local ($ftype) = $ftype[($mode & 0170000)>>12];
    if ($setids){
	# Sticky Bit?
	if ($setids & 01) { $permstrs[2] =~ s/([-x])$/$1 eq 'x' ? 't' : 'T'/e; }
	# Setuid Bit?
	if ($setids & 04) { $permstrs[0] =~ s/([-x])$/$1 eq 'x' ? 's' : 'S'/e; }
	# Setgid Bit?
	if ($setids & 02) { $permstrs[1] =~ s/([-x])$/$1 eq 'x' ? 's' : 'S'/e; }
    }
    return (join('', $ftype, @permstrs));
}







