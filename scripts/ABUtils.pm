
#
# This simple module was added to regroup a bunch of utility
# routines for the Insure++ build.
# Put there WebStyles, routines or anything which would be
# common to several scripts (so we don't have to re-write
# it and we would have everything centralized)
#

package ABUtils;
require 5.000;
use Exporter;

@ISA = (Exporter);
@EXPORT=qw(IUbody IUcmt IUhead IUtrail IUGetRef IUl2pre IUresource
	   IUExcluded IUSourceDirs IUError IUconsOK
	   IULoad JPLoad
	   IURTFormat JPRFFormat
	   JPRExec
	   IUTests IUTestDir IUListRoutine IUErrorURL IUCVSRef
	   IUQueue IUSubmit
	   IUCheckFile IUMoveFile
	   IUReleaseFile IUManagers IUCompDir
	   IUHtmlDir IUHtmlRef IUHtmlPub
	   );

# ------------------------------------------
# ---- Compilation section (insure and cons)
# ------------------------------------------
# Directory where we compile
$INSU::COMPDIR="/afs/.rhic/star/replicas/DEV";
$INSU::STARAFS="/afs/rhic/star/packages";

# list of dirs affected by a cvs co
@INSU::DIRS=("StRoot","StarDb","StDb","pams","asps","mgr");

# List of excluded modules in StRoot compilation. This is a default
# and does not preclude the SKIP_DIRS usage.
@INSU::SKIP=("StEbyePool");
$INSU::SKIPNM="SKIP_DIRS";


# This array declares a list of errors or messages
# to ignore.
# Pattern only ; case insensitive.
@INSU::MSGISERR=("Do not generate Streamer",
		 ".consign",
		 ".flc",
		 "cvs update: Updating",
		 "Run Conscript-standard in");

# OK return status from cons is
$INSU::CONSOK=0;

# ------------------------------------------
# Afs volume release file. Relative path
# Mailing list in case of failure.
# ------------------------------------------
$INSU::RELFLNM=".log/afs.release";
@INSU::MANAGERS=("jlauret\@bnl.gov",
		 "didenko\@bnl.gov"
		 );


# ------------------------------------------
# --- Tests and running section
# ------------------------------------------
$INSU::QUEUE="star_cas_prod";

# Command to issue to load the Insure environment
$INSU::INSLOAD="setenv INSURE yes ; unsetenv NODEBUG ; staradev";
$INSU::JPRLOAD="staradev";

# directory which will contain the test result files
$INSU::TDIR="/star/rcf/test/dev/Insure";

# LSF submit command
$INSU::BSUB = "/usr/local/lsf/bin/bsub";

# All tests may be declared here in this array. The first element is the chain
# the second a list of files to work on. Note that the array will be later
# sorted so no need to try to put the chain in a different order, hoping
# it will do something different.
%INSU::TESTS=(
	      "p00h",
	      "/star/data03/daq/2000/09/st_physics_1248022_raw_0001.daq",

	      "trs srs fss rrs C2001 GeantOut big evout fzin",
	      "/star/rcf/simu/cocktail/hadronic/default/highdensity/year2001/hadronic_on/Gstardata/hc_highdensity.16_evts.fz",

	      "trs sss fss rrs C2001 GeantOut big evout fzin",
	      "/star/rcf/simu/cocktail/hadronic/default/highdensity/year2001/hadronic_on/Gstardata/hc_highdensity.16_evts.fz",

	      "p2000",
	      "/star/data03/daq/2000/08/st_physics_1229021_raw_0003.daq",

	      #"p2001 -Kalman fiedloff",
	      #"/star/data03/daq/2001/192/st_physics_2192029_raw_0003.daq",

	      "p2001a",
	      "/star/data03/daq/2001/251/st_physics_2251004_raw_0001.daq",

	      "p2001",
	      "/star/data03/daq/2001/251/st_physics_2251004_raw_0001.daq",

	      "pp2001",
	      "/star/data03/daq/2002/017/st_physics_3017028_raw_0006.daq",

	      "dau2003 est beamLine CMuDst",
	      "/star/rcf/test/daq/2003/041/st_physics_4041002_raw_0020001.daq",

	      "pp2003 eemcD alltrigger trgd",
	      "/star/data03/daq/2003/111/st_physics_4111036_raw_0030004.daq"

	      );

# Default formatting script for run-time
$INSU::RTFORMAT="/afs/rhic/star/packages/scripts/insrtm.pl";
$INSU::JPFORMAT="/afs/rhic/star/packages/scripts/jprtm.pl";
$INSU::JPEXEC  ="/afs/rhic/star/packages/dev/.\@sys/BIN/jprof";

# routine exclusion in listing-by-routine
@INSU::SKIPFUNC=("_Cint",
		 "_TableCint",
		 "_Table.");


# ------------------------------------------
# ---- HTML section
# ------------------------------------------
# directory where the HTML file will be stored (final target)
$INSU::HTMLREPD="/afs/rhic/star/doc/www/comp/prod/Sanity";       # final direcory
$INSU::HTMLREF="http://www.star.bnl.gov/STAR/comp/prod/Sanity";  # URL
$INSU::HTMLPUBD="/afs/rhic/star/doc/www/html/tmp/pub/Sanity";    # public dir (temp)
$INSU::CVSWEB="http://www.star.bnl.gov/cgi-bin/cvsweb.cgi";      # CVS web utility


# variables subject to export. So far, we will be using
# functions to return their value
# HTML body attributes
$INSU::BODYATTR="bgcolor=cornsilk text=black link=navy vlink=maroon alink=tomato";
# HTML font declaration
$INSU::FONT="<basefont face=\"verdana,arial,helvetica,sans-serif\">";
$INSURL="http://www.star.bnl.gov/STAR/comp/sofi/Insure/manuals/";
%INSERRORS=(
	    # the above list was generated dumping and parsing the main
	    # insure++ index.htm page. Script used is named format_insure.pl
        "ALLOC_CONFLICT","err_allo.htm#69",
        "BAD_CAST","err_badc.htm#4301",
        "BAD_DECL","err_badd.htm#175",
        "BAD_FORMAT","err_badf.htm#1558",
        "BAD_INTERFACE","err_badi.htm#117",
        "BAD_PARM","err_badp.htm#234",
        "COPY_BAD_RANGE","err_copy.htm#48",
        "COPY_DANGLING","err_copa.htm#51",
        "COPY_UNINIT_PTR","err_copb.htm#1240",
        "COPY_WILD","err_copc.htm#33",
        "DEAD_CODE","err_dead.htm#69",
        "DELETE_MISMATCH","err_delm.htm#25",
        "EXPR_BAD_RANGE","err_expr.htm#104",
        "EXPR_DANGLING","err_expa.htm#113",
        "EXPR_NULL","err_expb.htm#122",
        "EXPR_UNINIT_PTR","err_expc.htm#89",
        "EXPR_UNRELATED_ PTRCMP","err_expd.htm#134",
        "EXPR_UNRELATED_ PTRDIFF","err_expe.htm#847",
        "EXPR_WILD","err_expf.htm#65",
        "FREE_BODY","err_free.htm#132",
        "FREE_DANGLING","err_frea.htm#140",
        "FREE_GLOBAL","err_freb.htm#152",
        "FREE_LOCAL","err_frec.htm#165",
        "FREE_UNINIT_PTR","err_fred.htm#192",
        "FREE_WILD","err_fref.htm#61",
        "FUNC_BAD","err_func.htm#62",
        "FUNC_NULL","err_funa.htm#70",
        "FUNC_UNINIT_PTR","err_funb.htm#80",
        "INSURE_ERROR","err_insu.htm#41",
        "INSURE_WARNING","err_insa.htm#67",
        "LEAK_ASSIGN","err_leak.htm#80",
        "LEAK_FREE","err_leaa.htm#92",
        "LEAK_RETURN","err_leab.htm#108",
        "LEAK_SCOPE","err_leac.htm#119",
        "PARM_BAD_RANGE","err_parm.htm#73",
        "PARM_DANGLING","err_para.htm#95",
        "PARM_NULL","err_parb.htm#109",
        "PARM_UNINIT_PTR","err_parc.htm#137",
        "PARM_WILD","err_pard.htm#47",
        "READ_BAD_INDEX","err_read.htm#198",
        "READ_DANGLING","err_reaa.htm#207",
        "READ_NULL","err_reab.htm#212",
        "READ_OVERFLOW","err_reac.htm#224",
        "READ_UNINIT_MEM","err_reae.htm#98",
        "READ_UNINIT_PTR","err_reaf.htm#233",
        "READ_WILD","err_reag.htm#71",
        "RETURN_DANGLING","err_retu.htm#94",
        "RETURN_FAILURE","err_reta.htm#140",
        "RETURN_INCONSISTENT","err_retb.htm#104",
        "UNUSED_VAR","err_unus.htm#58",
        "USER_ERROR","err_user.htm#151",
        "VIRTUAL_BAD","err_virt.htm#60",
        "WRITE_BAD_INDEX","err_writ.htm#112",
        "WRITE_DANGLING","err_wria.htm#123",
        "WRITE_NULL","err_wrib.htm#131",
        "WRITE_OVERFLOW","err_wric.htm#140",
        "WRITE_UNINIT_PTR","err_wrid.htm#150",
        "WRITE_WILD","err_wrie.htm#66"
	    );



# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ---- Internal variables only
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
$PRGM="ABUtils ::";
$AUTHOR="Jerome LAURET";
$EMAIL="jlauret\@bnl.gov";
$VERSION="V01-005";


#
# Returns a list of directories to exclude from compilation.
# This list DOES not preclude the SKIP_DIRS usage.
#
sub IUExcluded
{
    if( defined($ENV{$INSU::SKIPNM}) ){
	@INSU::SKIP = split(" ",$ENV{$INSU::SKIPNM});
    }
    return @INSU::SKIP;
}

# Although I am forseing only the use if INSUhead, flexibility
# of 2 extra routines added.
sub IUbody {
    "<BODY $INSU::BODYATTR>\n$INSU::FONT\n";
}
sub IUcmt {
    my($tmp);
    $tmp  = "<!-- Listing auto-generated on ".localtime()." -->\n";
    $tmp .= "<!-- $PRGM version $VERSION -->\n";
    $tmp .= "<!-- Script written by $AUTHOR $EMAIL  -->\n";
}
# Both head and trail may later include templates
# or style sheets etc ...
sub IUhead
{
    my($title)=@_;
    my($tmp);
    $tmp  = "<HTML>\n<HEAD><TITLE>$title</TITLE></HEAD>\n";
    $tmp .= &IUbody().&IUcmt();
    $tmp .= "<H1 ALIGN=\"center\">$title</H1>\n";
    $tmp .= "<H4 ALIGN=\"center\">Formatted on ".localtime()."</H4>\n";
    $tmp;
}
sub IUtrail
{
    "</BODY>\n</HTML>\n";
}


# Format line to something suitable to a pre tag.
# Some character needs HTML escaping.
sub IUl2pre
{
    my($line,$flag)=@_;
    if( defined($line) ){
	$line =~ s/&/&amp;/g;
	$line =~ s/</&lt;/g;
	$line =~ s/>/&gt;/g;
	if($line =~ m/\serror\s/i){
	    if( defined($flag) ){
		"$flag<b>$line</b>";
	    } else {
		"<b>$line</b>";
	    }
	} else {
	    $line;
	}
    } else {
	"";
    }
}

# This routine converts a line into a string suitable
# for NAME and HREF relative document reference
sub IUGetRef
{
    my($line)=@_;

    if( ! defined($line) ){ die "$PRGM IUGetRef requires an argument\n";}
    if( $line ne ""){
	$line =~ s/[\.\[\]:\(\)]/_/g;
	$line =~ s/\s//g;
    }
    $line;
}


# Creates an Insure++ .psrc file in the current directory
# Argument is the file to redirect the output to.
# Arg2 : message to display.
sub IUresource
{
    my($ofile,$mess)=@_;

    if(! -e ".psrc"){
	open(FO,">.psrc") ||
	    die "$PRGM Could not open any file in W mode in the current tree\n";
	print FO qq~
insure++.summarize bugs
insure++.checking_uninit on
insure++.demangle full_types
insure++.symbol_table off
insure++.stack_internal on
insure++.leak_combine none
insure++.leak_search on
insure++.leak_sort size
insure++.leak_sweep on
insure++.leak_trace off
insure++.summarize leaks outstanding
insure++.uninit_flow 300
insure++.report_file $ofile
insure++.GusCacheDir /tmp
    ~;
#insure++.unsuppress all
	close(FO);
	print "$mess\n";
    }
}

# Return TRUE or FALSE if a routine has to be displayed
# in the Insure report or not. Based on pattern exclusion
# of course ...
sub IUListRoutine
{
    my($func) = @_;

    return &IUIfAnyMatchExclude($func,@INSU::SKIPFUNC);
}


# Return true if this error can be taken, false otherwise.
# False is based on patterns in @INSU::MSGISERR.
sub IUError
{
    my($line) = @_;
    return &IUIfAnyMatchExclude($line,@INSU::MSGISERR);
}

# Global internal routine managing both
# INSListRoutine and IUError. Based on pattern
# exclusion (if found, not OK) mechanism.
sub IUIfAnyMatchExclude
{
    my($line,@PATS)=@_;
    my($pat,$sts);

    $sts = 1==1; # i.e. take it by default
    foreach $pat (@PATS){
	if($line =~ m/$pat/i){
	    $sts = 0==1; # found a pattern, not OK then
	    last;
	}
    }
    $sts;
}

# Returns a URL reference for the error message
sub IUErrorURL
{
    my($err,$mode)=@_;
    my($perr);

    if ( ! defined($mode) ){  $mode = 0;}

    if ( $err =~ m/(\w+)(\(.*\))/){
	# some errors will come here like BAD_FORMAT(other)
	# and we need the reference to BAD_FORMAT only
	$perr = $1;
    } else {
	$perr = $err;
    }

    if( defined($INSERRORS{$perr}) ){
	($mode == 1?" ":$err).
	    "<FONT SIZE=\"-1\">(<A HREF=\"$INSURL/$INSERRORS{$perr}\">learn more</A>)</FONT>";
    } else {
	($mode == 1?" ":$err);
    }
}

# Returns a formatted reference / string relating to CVS web
sub IUCVSRef
{
    my($file)=@_;
    "<A HREF=\"$INSU::CVSWEB/$file\">$file</A>";
}



# Returns the compilation directory
sub IUCompDir
{
    my($lib)=@_;
    my($retv);

    $retv = $INSU::COMPDIR;

    if( defined($lib) ){
	if ($lib !~ /adev/){
	    if( -d "$INSU::STARAFS/$lib"){
		$retv = "$INSU::STARAFS/$lib";
	    }
	}
    }
    $retv;
}

# Submits a job to "a" queue system
# Currently used, LSF ..
#
# Arg1 : job to submit
# Arg2 : flag
#
sub IUSubmit
{
    my($job,$flag)=@_;
    my($log,$cmd,$tmpfile);

    $log = $job.".log";

    if ( ! defined($flag) ){ $flag = 0;}

    if ( -e $log ){ 
	print "Deleting preceding log\n";
	unlink($log);
    }

    $cmd = "$INSU::BSUB -q $INSU::QUEUE -o $log $job";
    if ( ! $flag ){
	print "$cmd\n";
    } else {
	$tmpfile = "/tmp/$$-$<.ABUtils";
	if (open(FO,">$tmpfile") ){
	    print FO 
		"#!/bin/csh\n",
		"$cmd\n";
	    close(FO);
	    chmod(0700,$tmpfile);
	    print "Executing : $cmd\n";
	    system($tmpfile);
	    unlink($tmpfile);
	} else {
	    print "Could not open $tmpfile\n";
	}
    }
}






#
# This routines only checks for existence of an output file
# and prepares for a new one to appear. Arguments are
#   mode     0 returns a csh instruction
#            1 do it in perl on the fly
#   file     the filename
#
# This routine does not create an empty file.
#
sub IUCheckFile
{
    my($mode,$file)=@_;
    my($dir,$sts);

    $sts = 0;
    $file =~ m/(.*\/)(.*)/;
    ($dir,$file) = ($1,$2);
    chop($dir);

    if ($mode == 0){
	# csh mode
	$sts = "";
	$sts = "if ( -e $dir/$file-old) rm -f $dir/$file-old\n";
	$sts.= "if ( -e $dir/$file)     mv -f $dir/$file $dir/$file-old\n";

    } elsif ($mode == 1){
	# perl mode
	if ( -e "$dir/$file-old"){ unlink("$dir/$file-old");}
	if ( -e "$dir/$file")    { rename("$dir/$file","$dir/$file-old");}


    } elsif ($mode == 3){
	# csh mode
	$sts = "";
	$sts = "if ( ! -e $dir/$file) echo \"This test has never run\" >$dir/$file\n";
	
    } else {
	# unknown mode
	print "ABUtil:: IUCheckFile : Unknown mode $mode\n";
    }
    $sts;
}


#
# This routine move a file infile to outfile using target
# outfile versioning with filename-version.ext
# The argument $mode functions as above.
#
sub IUMoveFile
{
    my($mode,$infile,$outfile,$limit)=@_;
    my($sts,$file,$odir,$oflnm,$oext);
    my($cnt,$line);

    $cnt = $sts   = 0;

    $outfile      =~ m/(.*\/)(.*)/;
    ($odir,$oflnm)= ($1,$2);
    chop($odir);
    $oflnm        =~ m/(.*)(\..*)/;
    ($oflnm,$oext)= ($1,$2);

    while ( -e "$odir/$oflnm-$cnt.$oext" && $cnt < $limit){ $cnt++;}
    if ($cnt == $limit) {
	$cnt = 0;
	unlink(glob("$odir/$oflnm-*.$oext"));
    }


    if ($mode == 0){
	# csh mode ; we are cheating for the version
	$sts = "";
	$sts.= "if ( -e $odir/$oflnm$oext ) mv -f $odir/$oflnm$oext $odir/$oflnm-$cnt$oext\n";
	$sts.= "if ( -e $infile) cp -f $infile $odir/$oflnm$oext\n";

    } elsif ($mode == 1){
	# perl mode
	if ( -e "$odir/$oflnm$oext"){ rename("$odir/$oflnm$oext","$odir/$oflnm-$cnt$oext");}
	if ( -e "$infile"){
	    $sts = open(FO,">$odir/$oflnm$oext") && open(FI,"$infile");
	    if ($sts){
		while ( defined($line = <FI>) ){
		    chomp($line);
		    print FO "$line\n";
		}
	    }
	    close(FI);
	    close(FO);
	}
    } else {
	# unknown mode
	print "ABUtil:: IUMoveFile : Unknown mode $mode\n";
    }
    $sts;
}







# Returns the directories to update using cvs
sub IUSourceDirs { return @INSU::DIRS;}

# OK status from cons
sub IUconsOK { return $INSU::CONSOK;}

# Return command to load Insure environment
sub IULoad { return $INSU::INSLOAD;}

# Return command to load JProf environment.
# Currently, only 'adev' is loaded
sub JPLoad { return $INSU::JPRLOAD;}

# Return the test list
sub IUTests { return %INSU::TESTS;}

# Returns the default run-time formatting script
sub IURTFormat { return $INSU::RTFORMAT;}

# Returns the jprof formatting program
sub JPRFFormat { return $INSU::JPFORMAT;}

# Returns the jprof program location
sub JPRExec {    return $INSU::JPEXEC;}

# Returns the Test working directory
sub IUTestDir { return $INSU::TDIR;}

# Returns the release file name
sub IUReleaseFile { return $INSU::RELFLNM;}

# Return the mailing-list /admin accounts
sub IUManagers { return @INSU::MANAGERS;}

# Returns the HTML (or other) report directory (token required)
sub IUHtmlDir  { return $INSU::HTMLREPD;}

# Returns the HTML URL reference
sub IUHtmlRef  { return $INSU::HTMLREF;}

# Returns "a" HTML output public directory (volatile ; no token)
sub IUHtmlPub  { return $INSU::HTMLPUBD;}

# Returns the queue name
sub IUQueue    { return $INSU::QUEUE;}
