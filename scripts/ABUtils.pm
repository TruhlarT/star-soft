
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
	   IUTests IUTestDir IUListRoutine IUErrorURL
	   IUReleaseFile IUManagers IUCompDir IUHtmlDir IUHtmlRef
	   );

# ------------------------------------------
# ---- Compilation section (insure and cons)
# ------------------------------------------
# Directory where we compile
$INSU::COMPDIR="/afs/.rhic/star/replicas/DEV";
$INSU::STARAFS="/afs/rhic/star/packages";

# list of dirs affected by a cvs co
@INSU::DIRS=("StRoot","StarDb","StDb","pams","asps");

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
	      "/star/data03/daq/2002/017/st_physics_3017028_raw_0006.daq"

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
$INSU::HTMLREPD="/afs/rhic/star/doc/www/comp/prod/Sanity";
$INSU::HTMLREF="http://www.star.bnl.gov/STAR/comp/prod/Sanity";

# variables subject to export. So far, we will be using
# functions to return their value
# HTML body attributes
$INSU::BODYATTR="bgcolor=cornsilk text=black link=navy vlink=maroon alink=tomato";
# HTML font declaration
$INSU::FONT="<basefont face=\"verdana,arial,helvetica,sans-serif\">";
$INSURL="http://www.parasoft.com/products/insure/manuals/v5_2/unix/ref/";
%INSERRORS=(
	    # the above list was generated dumping and parsing the main
	    # insure++ index.htm page. Script used is named format_insure.pl
        "ALLOC_CONFLICT","err_aloc.htm",
        "BAD_CAST","err_badc.htm",
        "BAD_DECL","err_badd.htm",
        "BAD_FORMAT","err_badf.htm",
        "BAD_INTERFACE","err_badi.htm",
        "BAD_PARM","err_badp.htm",
        "COPY_BAD_RANGE","err_cp_b.htm",
        "COPY_DANGLING","err_cp_d.htm",
        "COPY_UNINIT_PTR","err_cp_u.htm",
        "COPY_WILD","err_cp_w.htm",
        "DEAD_CODE","err_dcod.htm",
        "DELETE_MISMATCH","err_delm.htm",
        "EXPR_BAD_RANGE","err_expr.htm",
        "EXPR_DANGLING","err_expd.htm",
        "EXPR_NULL","err_expn.htm",
        "EXPR_UNINIT_PTR","err_expu.htm",
        "EXPR_UNRELATED_PTRCMP","err_expp.htm",
        "EXPR_UNRELATED_PTRDIFF","err_expf.htm",
        "EXPR_WILD","err_expw.htm",
        "FREE_BODY","err_freb.htm",
        "FREE_DANGLING","err_fred.htm",
        "FREE_GLOBAL","err_freg.htm",
        "FREE_LOCAL","err_frel.htm",
        "FREE_NULL","err_fren.htm",
        "FREE_UNINIT_PTR","err_freu.htm",
        "FREE_WILD","err_frew.htm",
        "FUNC_BAD","err_fncb.htm",
        "FUNC_NULL","err_fncn.htm",
        "FUNC_UNINIT_PTR","err_fncu.htm",
        "INSIGHT_ERROR","err_inse.htm",
        "INSIGHT_WARNING","err_insw.htm",
        "LEAK_ASSIGN","err_leka.htm",
        "LEAK_FREE","err_lekf.htm",
        "LEAK_RETURN","err_lekr.htm",
        "LEAK_SCOPE","err_leks.htm",
        "PARM_BAD_RANGE","err_prmb.htm",
        "PARM_DANGLING","err_prmd.htm",
        "PARM_NULL","err_prmn.htm",
        "PARM_UNINIT_PTR","err_prmu.htm",
        "PARM_WILD","err_prmw.htm",
        "READ_BAD_INDEX","err_redb.htm",
        "READ_DANGLING","err_redd.htm",
        "READ_NULL","err_redn.htm",
        "READ_OVERFLOW","err_redo.htm",
        "READ_UNINIT_MEM","err_redm.htm",
        "READ_UNINIT_PTR","err_redp.htm",
        "READ_WILD","err_redw.htm",
        "RETURN_DANGLING","err_retd.htm",
        "RETURN_FAILURE","err_retf.htm",
        "RETURN_INCONSISTENT","err_reti.htm",
        "UNUSED_VAR","err_unus.htm",
        "USER_ERROR","err_user.htm",
        "VIRTUAL_BAD","err_vbad.htm",
        "WRITE_BAD_INDEX","err_wrtb.htm",
        "WRITE_DANGLING","err_wrtd.htm",
        "WRITE_NULL","err_wrtn.htm",
        "WRITE_OVERFLOW","err_wrto.htm",
        "WRITE_UNINIT_PTR","err_wrtu.htm",
        "WRITE_WILD","err_wrtw.htm"
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
    my($err)=@_;

    if( defined($INSERRORS{$err}) ){
	"$err <FONT SIZE=\"-1\"><A HREF=\"$INSURL/$INSERRORS{$err}\">(learn more)</A></FONT>";
    } else {
	$err;
    }
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

# Returns the HTML (or other) report directory
sub IUHtmlDir  { return $INSU::HTMLREPD;}

# Returns the HTML URL reference
sub IUHtmlRef  { return $INSU::HTMLREF;}
