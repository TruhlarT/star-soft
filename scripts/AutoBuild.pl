#!/usr/bin/env perl

# $Id: AutoBuild.pl,v 1.12 2003/08/28 21:36:48 jeromel Exp $
# This script was written to perform an automatic compilation
# with cvs co and write some html page related to it afterward.
# Written J.Lauret Apr 6 2001
# Need to extend it ? (some internal rules)
# - Menu reference is automatically build if a %%REF%% is found
#   the menu will appear on top of the report.
# 
#
use lib "/afs/rhic/star/packages/scripts";
use ABUtils;

# DEfault library version to work with
$LIBRARY="adev";
$COMPDIR="";

# Directory where the reports will be at the end
$TRGTDIR=IUHtmlDir();

# Cvs command and directory
$CVSCMDT="cvs -n -q checkout -A";  # check differences and updates
$CVSCMDR="cvs -q checkout -A";     # first timer directory or real checkout
$CVSUPDC="cvs update -A";          # update command
# checkout by
$BY=50;
# directories (default)
@DIRS=IUSourceDirs();

# tasks to peform after compilation
$DFILE = "RELEASE.date";
@POSTSKS=("rm -f $DFILE",
	  "date >$DFILE",
	  );

# Compilation will be made with the following commands. If
# the associative array has for value 1, the command MUST
# succeed in order to continue. Otherwise, the return result
# is irrelevant ...
# There are some assumptions made :
# 0 - csh is used to execute the commands.
# 1 - the SKIP_DIRS rule will be respected
# 2 - $CHVER command will be issued before compilation
#
# BTW : the echo command is a tupid thing. The keys
# are returned in reverse order (??) somehow and I 
# want them to be in this SAME exact order.
#
%COMPILC=(
	  "echo 1 ; unsetenv NODEBUG   ; cons", 1,
	  "echo 2 ; setenv NODEBUG yes ; cons", 1);
@SKIP=IUExcluded();
$OPTCONS="";


# --- Miscellaneous
# name of the HTML output report. ONLY the main name
# is expected here. Extension .html will be added.
$FLNM="AutoBuild";

# HTML colors for warnings. Experimental
# Used to display error messages.
@COLORS=("#D3D3D3","#EEEEEE");

# keeps compilation ans post-tasks status.
@STATUS=();

# Global error string
$ERRSTR="";

# Post-fix
$POST="";



# Arguments taking. Also controled via command line options ;
# Check the help for a better view of what you can do since
# some of those variables are dependant on others.
$FIRSTPASS=1==0;      # First pass compilation only
$SILENT=1==0;         # Ask for confirmation or not
$NIGNOR=1==1;         # Compile without update
$CVSUPD=1==0;         # Use cvs update
$CVSCOU=1==1;         # Use cvs check-out
$DEBUG= 1==0;         # Debug mode (i.e. no post-tasks)
$TRASH =1==0;         # trash code cvs finds conflicting
$FILO  =STDOUT;       # Default Output file





# Quick argument parsing (dirty)
for ($i=0 ; $i <= $#ARGV ; $i++){
    $arg = $ARGV[$i];
    if( substr($arg,0,1) eq "-"){
	# yeap. We consider this as an argument.
	# I know we can use this package but why ?
	if($arg eq "-x"){
	    # Exclude this
	    push(@SKIP,$ARGV[++$i]);
	} elsif($arg eq "-f"){
	    undef(@SKIP);
	} elsif($arg eq "-o"){
	    $FILO= $ARGV[++$i];
	    if(-e $FILO){ unlink($FILO);}
	    if(open(FILO,">$FILO")){
		$FILO = FILO;
	    } else {
		$FILO = STDOUT;
	    }
	} elsif($arg eq "-t"){
	    # tag output file with OS name
	    $FLNM .= "-$^O" if($FLNM !~ $^O);  
	    $POST = "-$^O";
	} elsif($arg eq "-1"){
	    # first compilation pass only
	    $FIRSTPASS=1==1;
	} elsif($arg eq "-i"){
	    # interractive that is no cvs 
	    # operations
	    $NIGNOR=1==0;
	    $SILENT=1==1;
	} elsif($arg eq "-u"){
	    $CVSUPD=1==1;
	    $CVSCOU=1==0;
	    $SILENT=1==1;
	} elsif($arg eq "-c"){
	    $CVSUPD=1==0;
	    $CVSCOU=1==1;
	    $SILENT=1==1;
	} elsif($arg eq "-d"){
	    $DEBUG = 1==1;
	} elsif($arg eq "-k"){
	    $OPTCONS .= "-k ";
	} elsif($arg eq "-v"){
	    $LIBRARY= $ARGV[++$i];
	} elsif($arg eq "-p"){
	    $COMPDIR= $ARGV[++$i];
	    $DEBUG = 1==1;
	} elsif ($arg eq "-h" || $arg eq "--help"){
	    &lhelp();
	    exit;
	} else {
	    print $FILO "Unkown argument $arg\n";
	}
    } else {
	&lhelp();
	die "Check syntax.\n";
    }
}


# Massage parameters
if($LIBRARY =~ m/dev/i || $LIBRARY =~ m/new/i ||
   $LIBRARY =~ m/pro/i || $LIBRARY =~ m/old/i ||
   $LIBRARY =~ m/\.dev/i ){
    $CHVER = "star".lc($LIBRARY);
} else {
    $CHVER = "starver $LIBRARY";
}


# Directory this script will work in
$COMPDIR=IUCompDir($LIBRARY) if ( $COMPDIR eq "");

# A temp script will be created with this name (number will be
# appended at the end).
$TMPNM="$COMPDIR/.AutoBuild".$POST;
# stdout/errors will be re-directed to a file with this main 
# name. No extension please.
$FLNMSG="$COMPDIR/Execute".$POST;
# name of an eventual resource file
$FLNMRC="$COMPDIR/.ABrc_$^O";


#
# --- We start here
#
if( ! chdir($COMPDIR) ){
    die "Could not change directory to $COMPDIR\n";
}

# else
print $FILO " - We are now in $COMPDIR\n";
$fail = 0;

# if a config file exists, read it
if( -e $FLNMRC){
    if (open(FI,$FLNMRC)){
	print $FILO " - Reading configuration\n";	
	while( defined($line = <FI>) ){
	    @items=split("#",$line); # comment lines
	    $line = $items[0];
	    if($line ne ""){
		@items = split("=",$line);
		chomp(@items);
		if( uc($items[0]) eq "SKIP_DIRS"){
		    push(@SKIP,$items[1]);
		}
	    }
	}
	close(FI);
    } 
}

if($NIGNOR){
    foreach $dir (@DIRS){
	print $FILO " + Inspecting $dir\n";
	if( -d $dir){
	    @res = `$CVSCMDT $dir`;
	} else {
	    @res = `$CVSCMDR $dir`;
	}

	if($? != 0){ $fail++;}
	foreach $line (@res){
	    if($line =~ m/^U /){
		push(@UPDATES,(split(" ",$line))[1]);
	    } elsif ($line =~ m/^M /){
		push(@MERGED,(split(" ",$line))[1]);
	    }
	}
    }
    if($fail != 0){
	print $FILO "$CVSCMDT problems prevents continuation ...\n";
	push(@REPORT,"$CVSCMDT problems prevents continuation ...");
	&Exit($fail);
    }
}

# Output this out. Note that we will update ONLY what was
# caught in the above search. This will avoid interim commit
# to get on the way ...
$tmp = "";

# U
if($#UPDATES != -1){
    print $FILO
	"\n",
	" - List of updates will follow ...\n";
    push(@REPORT,"%%REF%%<H2>List of new codes</H2>&nbsp;<I>".localtime()."</I>");
    push(@REPORT,"<UL>");
    foreach $line (@UPDATES){
	$dir = (split("/",$line))[0];
	if($dir ne $tmp){
	    push(@REPORT," </OL>") if($tmp ne "");
	    push(@REPORT,"<LI>$dir");
	    push(@REPORT," <OL>");
	    print $FILO "   For $dir ...\n"; 
	    $tmp = $dir;
	}
	push(@REPORT," <LI><TT>$line</TT>");
	print $FILO "     $line\n";
    }
    push(@REPORT," </OL>") if($tmp ne "");
    push(@REPORT,"</UL>");
}

# M
if($#MERGED != -1){
    print $FILO
	"\n",
	" - List of un-comitted code will follow ...\n";
    push(@REPORT,"%%REF%%<H2>List of code found with conflicting cvs version.</H2>");
    push(@REPORT,"Those re codes modified on disk and NOT commited ");
    push(@REPORT,"in the repository. This may be a mistake or an experimental ");
    push(@REPORT,"version. Please, <U>delete or commit</U> them now !! ");
    push(@REPORT,"<UL>");
    foreach $line (@MERGED){
	push(@REPORT," <LI><TT>$line</TT>");
	print $FILO "   $line\n";
    }
    push(@REPORT,"</UL>");
}

print $FILO " - Compilation will exclude [".join(" ",@SKIP)."]\n";
print $FILO " - Compilation commands will be \n";
foreach $line (sort keys %COMPILC){
    print $FILO "   ".($COMPILC{$line}?"MANDATORY":"OPTIONAL ")." '$line'\n";
}
print $FILO "\n";

if(! $SILENT){ 
    print $FILO " Is this OK ? y/u/i/[n] ";
    chomp($ans = <STDIN>);
    $ans = "no" if ($ans eq "");
} else {
    if($CVSUPD){     $ans = "u";}   # update
    elsif($CVSCOU){  $ans = "y";}   # yes => checkout (default)
    elsif($NIGNOR){  $ans = "i";}   # ignore i.e. compile now without updating the tree
    else {           $ans = "n";}   # absolutly not. Stop ASAP.
}

$fail = 0;
if ($ans =~ /^\s*y/i){
    # Now, the answer was YES. We need to cvs co for real.
    # We can checkout by bunch of $BY to avoid the usual unix
    # limitation on the number of arguments on the command line.
    print $FILO " - cvs operation status\n";
    push(@REPORT,"%%REF%%<H2>cvs operation status</H2>");
    if($#UPDATES == -1 && $#MERGED == -1){
	if( -e "$COMPDIR/$DFILE" && $DEBUG){
	    open(FI,"$COMPDIR/$DFILE");
	    chomp($tmp = <FI>);
	    close(FI);
	    $tmp = "No action requested. Taking the latest $tmp version";
	} else {
	    $tmp = "No action required";
	}

	push(@REPORT,
	     "<BLOCKQUOTE>\n<I>$tmp</I>\n</BLOCKQUOTE>");

    } else {
	if($#UPDATES != -1){
	    push(@REPORT,"<OL>");
	    do {
		@items = splice(@UPDATES,0,$BY);
		$tmp = "$CVSCMDR ".join(" ",@items);
		push(@REPORT,"<LI><TT>$tmp</TT><BR>");
		$fail += &Execute($tmp);
	    } while ($#UPDATES != -1);
	    push(@REPORT,"</OL>");
	    #undef(@UPDATES);
	}

	# Now the so-called merged. Those needs to be removed
	if($#MERGED != -1){
	    push(@REPORT,"<OL>");
	    foreach $file (@MERGED){
		push(@REPORT,"<LI><TT>$file</TT>");
		if(-e $file){
		    if(! $TRASH){
			push(@REPORT," found and preserved as-is");
		    } else {
			if(unlink($file)){
			    push(@REPORT,"deleted");
			    $fail += &Execute("$CVSCMDR $file");
			} else {
			    push(@REPORT,"<U>*** Could not delete ***</U>");
			    push(@REPORT,
				 "Build will continue but manual intervention is required");
			}
		    }
		} else {
		    push(@REPORT,"<I>File not found</I>");
		    $fail += &Execute("$CVSCMDR $file");
		}
	    }
	    push(@REPORT,"</OL>");
	    #undef(@MERGED);
	}
    }
} elsif ($ans =~ /^\s*u/i){
    # update was requested instead of
    # checkout.
    push(@REPORT,"%%REF%%<H2>cvs operation status</H2>");
    push(@REPORT,"<BLOCKQUOTE>\n<I>Update was required</I>");
    push(@REPORT,"<UL>");
    foreach $dir (@DIRS){
	push(@REPORT,"<LI><TT>$dir</TT>");
	&Execute("$CVSUPDC $dir",1);
    }
    push(@REPORT,"</UL></BLOCKQUOTE>");
} elsif ($ans =~ /^\s*i/i){
    push(@REPORT,"%%REF%%<H2>no cvs operation performed</H2>");
} else {
    print $FILO "OK. Goodbye !...\n";
    exit;
}

# If failure, DO NOT continue.
if($fail != 0){ &Exit($fail); }


#
# Compilation will now take place.
#
push(@REPORT,"%%REF%%<H2>Compilation report</H2>");
push(@REPORT,"<UL>");

# hum ! @ = keys did not put it in the same order. 
$i = 0; 
foreach $line (sort keys %COMPILC){
    if( ! open(FO,">$TMPNM$i") ){ 
	print $FILO " * Could not open file $TMPNM$i for write\n";
	push(@REPORT,"<LI><U>Failure</U> to open temporary file $TMPNM\n");
	goto End;
    }


    print FO 
	"#!/bin/csh\n",
	"$CHVER\n",
	"cd $COMPDIR\n",
	"\n",
	"setenv SKIP_DIRS \"".join(" ",@SKIP)."\"\n",
	"$line $OPTCONS\n";


    close(FO);
    chmod(0770,"$TMPNM$i");

    push(@REPORT,"<P>");
    push(@REPORT,"%%REF%%<LI>$line<BR>");
    $fail = $COMPILC{$line}*(&Execute("$TMPNM$i"));
    push(@STATUS,"$i-$fail");
    if($fail != 0){ 
	last;
    } else {
	unlink("$TMPNM$i");
	$i++;
    }
    if($FIRSTPASS){ last;}
}


# The post tasks are being done only if the preceeding succeeded.
# In principle, some of those tests will also modify the $fail
# variable (if mandatory) so we do not want to merge this with
# the Exit() routine.
if($fail == 0){
    # Other stuff here (test this version, tree copy, send Email, 
    # prepare the coffee etc ...
    push(@REPORT,"</UL>");
    push(@REPORT,"%%REF%%<H2>Post-compilation tasks</H2>");
    push(@REPORT,"<UL>");
    foreach $tmp (@POSTSKS){
	if (&Execute($tmp) == 0){
	    push(@REPORT,"<LI><tt>".IUl2pre($tmp)."</tt> ".&STRsts(0));
	} else {
	    push(@REPORT,"<LI><tt>".IUl2pre($tmp)."</tt> ".&STRsts(1));
	}
    }
}


End:
push(@REPORT,"</UL>");
&Exit($fail);



# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#
# Exit routine dup the report table and
# leave.
#
sub Exit()
{
    my($sts)=@_;
    my($tmp);
    my(@email);

    # Output HTML
    &ReportToHtml($sts);

    # Close global output if needed
    if($FILO ne STDOUT){ close($FILO);}


    if( $DEBUG){
	print "Debug mode. Stopping at this stage. $ERRSTR\n";
	exit(0);
    }


    # LEAVE NOW. Either send Email warning to admin or
    # release the volume.
    if($sts != 0){
	# Send Emails to the list of managers if the compilation
	# failed. We do NOT want to be influcenced by anything else
	@email  = IUManagers();
	foreach $tmp (@email){
	    system("echo \"Last error is $ERRSTR\nFor more information, ".
		   "check ".IUHtmlRef()."/$FLNM.html\" ".
		   "| Mail -s \"AutoBuild: Action failed\" $tmp");
	}
	exit(1);
    } else {
	# Release the volume now
	$tmp = IUReleaseFile();
	if( -e $tmp){ unlink($tmp);}
	open(FO,">$tmp"); print FO "Ready to release on ".localtime()."\n";
	close(FO);

	# And exit with normal status
	exit(0);
    }
}




# Output report to HTML file.
sub ReportToHtml
{
    my($sts)=@_;
    my($flnm);
    my($i,$k,$line,$tmp);
    my($fo);

    # depending on the mode we use, create file on expected
    # target directory or not.
    if($DEBUG){
	$flnm=$ENV{HOME}."/$FLNM";
	print "Output to $flnm.html\n";
    } else {
	$flnm="$TRGTDIR/$FLNM";
    }


    # move old file. 
    $i = 0;
    if( -e "$flnm.html"){
	while( -e "$flnm$i.html"){ $i++;}
	if( $i == 100){
	    unlink(glob("$flnm\[0-9\]*.html"));
	    $i = 0;
	}
	rename("$flnm.html","$flnm$i.html");
    }

    # this is the current generated page
    if( open(FO,">$flnm.html") ){
	$fo = FO;
    } else {
	$fo = STDOUT;
    }

    
    # Title and link to preceeding if any.
    # The beginning of the "prev" thread at 1 is NOT a coding
    # bug but a design i.e. Version 0 will NOT be referenced
    # and this was intended for debug purposes 
    if($LIBRARY ne "adev"){
	print $fo IUhead("AutoBuild report using $LIBRARY");
    } else {
	print $fo IUhead("AutoBuild report");
    }
    if ($i != 0){
	print $fo 
	    "<H5 ALIGN=\"center\">",
	    "<A HREF=\"$FLNM$i.html\">Prev</A></H5>\n";
    }

    # global success
    print $fo
	"<TABLE BORDER=\"0\">\n",
	"<TR><TD><B>Global Status</B></TD><TD>".
	    uc(&STRsts($sts))."</TD></TR>\n",
	"<TR><TD><B>Skipped DIRS </B></TD><TD><TT>".
	    join(" ",@SKIP)."</TT></TD></TR>\n";
    if(IUCompDir($LIBRARY) ne $COMPDIR){
	print $fo 
	"<TR><TD><B>Working directory</B></TD>".
	    "<TD><TT>$COMPDIR</TT></TD></TR>\n";
    }
    print $fo "</TABLE>\n";

    # sort/create references
    $k = 0;
    for($i = 0 ; $i <= $#REPORT ; $i++){
	$line = $tmp = $REPORT[$i];
	if($line =~ m/(.*)(%%REF%%)(.*)/){
	    if( ! defined($1) ){ $1 = "";}
	    $line = $1."<A NAME=\"Ref$k\"></A>".$3;
	    $tmp  = $3; 
	    $tmp =~ s/</<!-- /g;
	    $tmp =~ s/>/ -->/g;
	    push(@REFS,"<A HREF=\"#Ref$k\">$tmp</A>");

	    $REPORT[$i] = $line;
	    $k++;
	} elsif ($line =~ m/errors constructing/ || 
		 $line =~ m/error constructing/ ){
	    push(@REFS,"<A HREF=\"#Ref$k\">$line</A>");
	    $REPORT[$i] = "<A NAME=\"Ref$k\"></A>$line";
	    $ERRSTR = $line;         # over-write stupid default
	    $k++;
	}
    }
    print $fo "<UL>\n";
    foreach $line (@REFS){
	print $fo "<LI>$line\n";
    }
    print $fo "</UL>\n<P>\n";

    # dump all lines with fixed references
    foreach $line (@REPORT){
	print $fo "$line\n";
    }

    # write trailer, close file
    print $fo IUtrail();
    if($fo ne STDOUT){ close(FO);}

    # We can do this part only now because the HTML
    # parsing also determine the GUILTY maker ...
    # This will be used for later processing by some
    # statistics CGI .
    if( open(FO,">>$flnm.dat") ){
	if( $ERRSTR =~ m/(StRoot\/)(.*\/)(.*)/){
	    $GUILTY = $2;
	} else {
	    $GUILTY = $ERRSTR;
	    $GUILTY =~ s/\s+//g;
	}
	print FO time()." ".($i+1)." $sts $GUILTY ".join(" ",@STATUS)."\n";
	close(FO);
    }
}





# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



#
# Execute command, trap stderr only and push the output
# in the REPORT array. Here, the return status of this
# routine is the reverse than expected for a TRUE/FALSE
# answer ; it follows the $rc code ...
#
sub Execute
{
    my($cmd,$mode)=@_;
    my($rc,$line,$k);

    if( ! defined($mode) ){ $mode = 0;}

    open(SAVEERR,">&STDERR");
    open(STDERR,">$FLNMSG.err");
    select(STDERR); $| = 1; 
    if($mode == 1){
	print $FILO " - Executing [$cmd]. Please wait ...\n";
	open(SAVOUT,">&STDOUT");
	open(STDOUT,">$FLNMSG.out");
	select(STDOUT); $| = 1; 
    }


    $rc    = 0xffff & system($cmd);
    $ERRSTR= "Error str = $!";         # temptative

    close(STDERR);
    open(STDERR, ">&SAVEERR");
    close(SAVEERR);
    if($mode == 1){
	close(STDOUT);
	open(STDOUT,">&SAVOUT");
	close(SAVOUT);
    }

    # may be more complex later on. There are some known well
    # known/established returned code.
    if($rc != 0 && $rc != IUconsOK() ){
	print $FILO " * [$cmd] FAILED. Return Code =$rc\n";
	push(@REPORT,&STRsts(1)."Return Code = $rc");
	# RE-assign errstr
	$ERRSTR = "ReturnCode $rc";
    } else {
	push(@REPORT,&STRsts(0));
    }


    # glue the errors with it
    if(-e "$FLNMSG.err"){
	open(FI,"$FLNMSG.err");
	push(@REPORT,"<TABLE BORDER=\"0\">");

	$k=-1;
	$ppat="";
	while (defined($line = <FI>) ){
	    chomp($line);
	    # color scheme based on warning word ?
	    # Experimental
	    if($line ne ""){
		if( ($line =~ m/warning/i      || 
		     $line =~ m/In\sfunction/i ||
		     $line =~ m/In\smethod/i   ) && 
		   $line !~ m/warning\:\s*by/ &&
		   $line !~ m/included\sfrom/    ){
#		    if($k != -1){ push(@REPORT,"</PRE></TR></TD>"); }
#		    push(@REPORT,"<TR BGCOLOR=\"$COLORS[$k]\"><TD><PRE>");
#		    $k++;  if($k > $#COLORS){ $k = 0;}
		    $cpat = (split(":",$line))[0];
		    if($ppat ne $cpat){
			$ppat = $cpat;
			if($k != -1){ push(@REPORT,"</PRE></TR></TD>");}
			push(@REPORT,"<TR BGCOLOR=\"$COLORS[$k]\"><TD><PRE>");
			$k++;  if($k > $#COLORS){ $k = 0;}
		    }
		} elsif ($k == -1){
		    push(@REPORT,"<TR BGCOLOR=\"$COLORS[$k]\"><TD><PRE>");
		    $k++;  if($k > $#COLORS){ $k = 0;}
		}
	    }
	    if(IUError($line)){
		push(@REPORT,IUl2pre($line,"%%REF%%"));
	    }
	}
	if($k != -1){ push(@REPORT,"</PRE></TR></TD>");}
	push(@REPORT,"</TABLE>");
	close(FI);
	unlink("$FLNMSG.err");
    }

    # results from output requested 
    if($mode == 1 && -e "$FLNMSG.out"){
	open(FI,"$FLNMSG.out");
	push(@REPORT,"<BR><U>STDOUT relevant results</U>\n<PRE>");
	while (defined($line = <FI>) ){
	    chomp($line);
	    if(IUError($line)){
		push(@REPORT,IUl2pre($line,"%%REF%%"));
	    }
	}
	push(@REPORT,"</PRE>");
	close(FI);
	unlink("$FLNMSG.out");
    }

    return $rc;
}

sub lhelp
{
    
    my($excl)=join(" ",@SKIP);
    print $FILO qq~
 This utility compiles and test the code automatically. It heavily relies on
 the ABUtils module so any modification to this module would affect this 
 utility. Apart from that, command line arguments may be used to modify the 
 default values. They are :

 -i           Do not checkout/update from cvs. 
 -c           Performs a cvs checkout automatically
 -u           Performs a cvs update automatically
 -t           Tag any resulting output summary file with OS name i.e. 
              $FLNM-$^O .
 -d           Debug. DO NOT perform post compilation tasks and perform
              a HTML output in $ENV{HOME} instead of 
              $TRGTDIR
 -v Lib       Change default library version from $LIBRARY to 'Lib' where
              'Lib' stands for new, old, SL01i etc ...
 -p Path      Change the default $COMPDIR working directory
              to 'Path'. This option automatically disables post-compilation
              operations (-d option is ON).

 -f           Flush the default list of directories to skip
 -x ABC       Exclude ABC from list in addition to default exclusion
              list $excl

 -1           First compilation pass only
 -k           Keep going as far as possible after errors (cons option)
 
 -h or --help Display this help.

 Without -{i|c|u} the procedure will ask you for an answer in interractive 
 mode. Possible answers are y=checkout (-c),u=update (-u) i=ignore (-i) or 
 n=none (abort).
		  ~;
    print $FILO "\n";

}

sub STRsts
{
    my($sts)=@_;

    if($sts==0){
	return "<FONT COLOR=\"#0000FF\"><B>Success </B></FONT>";
    } else {
	return "<FONT COLOR=\"#FF0000\"><B>FAILURE </B></FONT>";
    }
}

