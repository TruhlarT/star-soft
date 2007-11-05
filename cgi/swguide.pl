#!/usr/bin/env perl
#
# $Id: swguide.pl,v 1.10 2007/11/05 19:42:00 jeromel Exp $
#
######################################################################
#
# swguide.pl
#
# T. Wenaus 6/99
#
# Software guide; tool for browsing software info and doc
#
# Usage: CGI script
#

BEGIN {
    use CGI::Carp qw(fatalsToBrowser);
}

use CGI;
use lib "/afs/rhic.bnl.gov/star/packages/cgi";
use File::Basename;
require SWGdbheader;
require SWGdbsetup;


# Area where the files will be written
$fpath   = "/afs/rhic.bnl.gov/star/doc/www/html/tmp";
$CVSroot = "/afs/rhic.bnl.gov/star/packages/repository/CVSROOT";
$DOXPATH = $fpath."/dox/html";
$DOXURL  = "/webdatanfs/dox/html";
$CVSURL  = "/webdatanfs/cvs/user";
$curTime = time();

&cgiSetup();
#print "Bla\n";
$q->param('ver','dev')  if ( $q->param('ver')    eq '');
$q->param('detail','1') if ( $q->param('detail') eq '');


# Option dynamic was suppressed to avoid users clasing with each other
# The above commented lines were in the form above.
#<input type="checkbox" name="dynamic" value="yes">
#    Force regeneration of page. Slow; only for debugging or if displayed
#page is too old.

$dynamic = $q->param('dynamic');
if ( $dynamic ne "yes" && $q->param('pkg') eq '' && $q->param('find') eq '') {
    $fname = $fpath."/swguide-".$q->param('ver')."-".$q->param('detail').".html";
    if ( -e $fname ) {
	@all = stat($fname);
        if( open(FILE,"< $fname") && $all[7] != 0){
	    # just display the pre-prepared page
	    print "<!-- $fname opened -->\n";
	    while (<FILE>) {
		print;
	    }
	    exit;
	}
    } else {
        print "$fname not found<br>\n";
    }
}


%okExtensions = (
                 ".hh" => "C++",
                 ".hpp" => "C++", # yes, someone's actually using this
                 ".h" => "C++",
                 ".cc" => "C++",
                 ".cxx" => "C++",
                 ".C" => "C++",
                 ".C++" => "C++",
                 ".c" => "C",
                 ".inc" => "FORTRAN",
                 ".F" => "FORTRAN",
                 ".f" => "FORTRAN",
                 ".idl" => "IDL",
                 ".ddl" => "DDL",
                 ".sh" => "script",
                 ".pl" => "script",
                 ".pm" => "script",
                 ".csh" => "script",
                 ".batch" => "script",
                 ".bat" => "script",
                 ".scr" => "script",
                 ".kumac" => "KUMAC",
                 ".g" => "MORTRAN",
                 ".mk" => "Makefile"
                 );

foreach $typ (sort keys %okExtensions) {
    $typeCounts{$okExtensions{$typ}} = 0;
    $typeCountsRecent{$okExtensions{$typ}} = 0;
}

&printMainHeader("STAR Offline Software Guide",1);

print <<END;
The purpose of this page is to gather together information and
documentation on all offline software components: source code,
macros, and scripts. Pointers and comments...
<ul>
    <li> The basic package list provides links to the more detailed
    package listing, to README file and documentation area (if
    existing, and they are supposed to exist), and to CVS and
    cross-referenced source code browsers for the package.
    <li> The package list with details adds summary info about
    the package: responsible person,
                 file count, line count, date of latest mod,
    days since latest mod, associated PAM.
    <li> The full listing lists all details of all packages.
    <li> The file listings report the file version in that release
    (linked to the CVS source), username and date of the most
    recent CVS commit, and the most recent tag for that file version.
    Filename is linked to associated class doc if it exists.
    <li>Only Library version <b>dev</b> provides link to the
    doxygen formatted source code.
    <li> Ball color indicates time since most recent mod:
    <img src="/images/redball.gif">=2days, <img src="/images/greenball.gif">=2weeks, <img src="/images/blueball.gif">=2months, <img src="/images/whiteball.gif">=older
</ul>
END

$debugOn = 0;



%ignoreStuff = (
                "." => 1,
                ".." => 1,
                "CVS" => 1,
                ".cvsignore" => 1,
                "D" => 1,
                "README" => 1,
                ".rootrc" => 1,
                "html" => 1
                );

if ( $debugOn ) {
    $getString = $ENV{'QUERY_STRING'};
    $getString =~ s/%(..)/sprintf("%c", hex($1))/ge;	# unquote %-quoted
    print "\nGET: \"".$getString."\"<br>\n" if $debugOn;
}
if ($qstring = $ENV{'QUERY_STRING'}) {
    foreach (split(/&/, $qstring)) {
        s/%(..)/sprintf("%c", hex($1))/ge;	# unquote %-quoted
        if (/([^=><!]+)=(.*)/) {
            if ($2 ne "") {
                $kyv = $2;
                if (exists($input{$1})) {
                    $input{$1} .= ",$kyv";
                } else {
                    $input{$1} = $kyv;
                }
                print "'$1' = '$input{$1}'<br>\n" if $debugOn;
            }
        } else {
            $input{$_}++;
        }
    }
}

$ver = $q->param('ver');
$ver = '.dev' if ( $ver eq ".dev" );

$showFlag = $q->param('detail');

$find = $q->param('find');

$pkg = $q->param('pkg');

#read in avail file of package owners
if ( -e "$CVSroot/avail"){
    open(AVAIL,"< $CVSroot/avail")
	or print "Can't open avail file: $!\n";
    @availFile=<AVAIL>;
    close AVAIL;
}

#read in loginfo file of package mod notification email
if ( -e "$CVSroot/loginfo"){
    open(LOGINFO,"< $CVSroot/loginfo")
	or print "Can't open loginfo file: $!\n";
    @loginfoFile=<LOGINFO>;
    close LOGINFO;
}

$STAR = "/afs/rhic.bnl.gov/star/packages/$ver";
$root = $STAR;
$rel = readlink("/afs/rhic.bnl.gov/star/packages/$ver");
($f, $d, $e) = fileparse($rel);
$rel = $f;
undef($d);

$ddevVer= (fileparse(readlink("/afs/rhic.bnl.gov/star/packages/.dev")))[0];
$devVer = (fileparse(readlink("/afs/rhic.bnl.gov/star/packages/dev")))[0];
$newVer = (fileparse(readlink("/afs/rhic.bnl.gov/star/packages/new")))[0];
$proVer = (fileparse(readlink("/afs/rhic.bnl.gov/star/packages/pro")))[0];
$oldVer = (fileparse(readlink("/afs/rhic.bnl.gov/star/packages/old")))[0];

$verChecked{$ver} = "checked";
$detailChecked{$showFlag} = "checked";
print <<END;
<form method="GET" action="/cgi-bin/prod/swguide.pl">
<b>Version:</b>
    <input type="radio" $verChecked{".dev"} name="ver" value=".dev"> .dev
    ($ddevVer)
    <input type="radio" $verChecked{"dev"} name="ver" value="dev"> dev
    ($devVer)
    <input type="radio" $verChecked{"new"} name="ver" value="new"> new
    ($newVer)
    <input type="radio" $verChecked{"pro"} name="ver" value="pro"> pro
    ($proVer)
    <input type="radio" $verChecked{"old"} name="ver" value="old"> old
    ($oldVer)
<br>
<b>Detail:</b>
    <input type="radio" $detailChecked{"0"} name="detail" value="0"> Package list
    <input type="radio" $detailChecked{"1"} name="detail" value="1"> Detailed package list
    <input type="radio" $detailChecked{"2"} name="detail" value="2"> Full listing <br>
<b>Find package:</b> <input type="text" name="pkg" value="$pkg">
<b>or Find file:</b> <input type="text" name="find" value="$find"><br>
<br>
<input type="submit"> &nbsp; <input type="reset"><br>
</form>

<hr>
<p>
<h3>Version $ver = $rel</h3>
</h3>
<pre>
END

# Build list of pams
@pamList = `cd $root; /usr/bin/find pams -maxdepth 2 -mindepth 2 -type d`;
foreach $pm (@pamList) {
    $pm =~ m/pams\/([a-zA-Z0-9]+)\/([a-zA-Z0-9]+)/;
    if ( $1 ne "CVS" && $1 ne "inc" && $1 ne "kumac" ) {
        $pams{$2} = "$1/$2";
        $pams{$1} = "$1";
    }
}
if ( $debugOn ) {
    foreach $p ( keys %pams ) {
        print $p." ".$pams{$p}."\n";
    }
}

$totlines = 0;
$totfiles = 0;
#### Loop through packages

@allDirs = (
            "StRoot",
            "StDb",
            "mgr",
            "scripts",
            "cgi",
            "pams/ctf",
            "pams/db",
            "pams/ebye",
            "pams/emc",
            "pams/ftpc",
            "pams/gen",
            "pams/geometry",
            "pams/global",
            "pams/l3",
            "pams/magnet",
            "pams/mwc",
            "pams/sim",
            "pams/strange",
            "pams/svt",
            "pams/tpc",
            "pams/trg",
            "pams/vpd",
            "Dsv"
            );

%oneLevel = (
             "mgr" => 1,
             "scripts" => 1,
             "cgi" => 1,
             "Dsv" => 1
             );

for ($idr=0; $idr<@allDirs; $idr++) {
    $dir = $allDirs[$idr];
    if (exists($oneLevel{$dir})) {
        if ( $pkg ne "" ) {
            if ( $dir eq $pkg ) {
                &showPackage($root,".",$dir);
                last;
            } else {
                next;
            }
        } else {
            &showPackage($root,".",$dir);
        }
        $totlines += $linecount;
        $totfiles += $filecount;
        if ( $find ne "" && $showFlag > 0 ) {
            # We're done
            last;
        }
        next;
    }
    print "Open $root/$dir<br>\n" if $debugOn;
    opendir(DIR, "$root/$dir");
    @files = 0;
    $if=0;
    while (defined ($file = readdir DIR)) {
        $files[$if] = $file;
        $if++;
    }
    @files = sort @files;
    foreach $file ( @files ) {
        next if (exists($ignoreStuff{$file}));
        if ( $pkg ne "" ) {
            if ( $file eq $pkg ||
                 $dir."/".$file eq $pkg ||
                 $dir."/".$file eq "pams/".$pkg ) {
                &showPackage($root,$dir,$file);
                last;
            } else {
                if ( $dir eq "pams/".$pkg ) { &showPackage($root,$dir,$file); }
                next;
            }
        } else {
            &showPackage($root,$dir,$file);
        }
        $totlines += $linecount;
        $totfiles += $filecount;
        if ( $find ne "" && $showFlag > 0 ) {
            # We're done
            last;
        }
    }
}

if ( $find eq "" && $pkg eq "" && $showFlag > 0 ) {
    print "\n<b>Total files $totfiles</b>";
    print "\n<b>Total lines $totlines</b>";
    print "\n  By type:          All    Last 2 months\n";
    foreach $typ (sort keys %typeCounts) {
        if ( $typeCounts{$typ} > 0 ) {
            printf("    %-10s   %7d   %7d\n",$typ,$typeCounts{$typ},
                   $typeCountsRecent{$typ});
        }
    }
    if ( $ver eq 'dev' ) {
        open(FSTAT,">$fpath/swguide-stats.txt-tmp");
        print FSTAT "\n<b>Total files $totfiles</b>";
        print FSTAT "\n<b>Total lines $totlines</b>";
        print FSTAT "\n  By type:          All    Last 2 months\n";
        foreach $typ (sort keys %typeCounts) {
            if ( $typeCounts{$typ} > 0 ) {
                printf(FSTAT "    %-10s   %7d   %7d\n",$typ,$typeCounts{$typ},
                       $typeCountsRecent{$typ});
            }
        }
        close(FSTAT);
	rename("$fpath/swguide-stats.txt-tmp","$fpath/swguide-stats.txt");
    }
}

print <<END;
</pre>
</body>
</html>
END

    exit;

#########################

sub showPackage {
    my ( $theRoot, $theDir, $thePkg ) = @_;
    $lastMod = 0;
    $linecount = 0;
    $filecount = 0;
    # if the package searched for is this one, display it
    if ( $find ne "" ) {
        if ( $thePkg eq $find ) {
            $showFlag = 2;
        } else {
            $showFlag = -1;
        }
    }
    print "flag $showFlag $theRoot $theDir $thePkg<br>\n" if $debugOn;
    $pkgLine = "";
    if ( $thePkg eq 'inc' || $thePkg eq 'kumac' ) {
      $readme = "      ";
      $doc = "   ";
    } else {
      ### README file
      if ( -e "$theRoot/$theDir/$thePkg/README" ) {
        $readme = "<a href=\"/STAR/comp/pkg/$ver/$theDir/$thePkg/README\">README</a>";
      } else {
        $readme = "      ";
      }
      ### doc directory. For pams, the doc area has package name doc
      if ( $thePkg eq 'doc' ) {
        $docDir = "$theRoot/$theDir/$thePkg";
        $docLoc = "";
      } else {
        $docDir = "$theRoot/$theDir/$thePkg/doc";
        $docLoc = "doc/";
      }
      $doc = "  ";
      if ( -d $docDir ) {
        opendir(DOC, $docDir);
        while (defined ($docf = readdir DOC)) {
          if ( $docf ne "." && $docf ne ".." && $docf ne "CVS" ) {
            # something seems to be there
            $doc = "<a href=\"/STAR/comp/pkg/$ver/$theDir/$thePkg/$docLoc\">doc</a>";
            last;
          }
        }
        close DOC;
      }
    }
    ### CVS link
    $cvs = "<a href=\"/cgi-bin/cvsweb.cgi/$theDir/$thePkg\">CVS</a>";


    ### Try to find the owner
    $pkgOwner = "";
    for ($ia=0; $ia<@availFile; $ia++) {
        if ( $theDir =~ m/(\S+)\/(\S+)/ ) {
            $dr = "$1\\\/$2";
        } else {
            $dr = $theDir;
        }
        if ( $availFile[$ia] =~ m/$dr\/$thePkg\/*\s*$/ ) {
            $own = $availFile[$ia];
            $own =~ m/(avail\s+\|)([a-z]+)/;
            $pkgOwner = $2;
        } elsif ( $availFile[$ia] =~ m/$dr\/*\s*$/ ) {
            if ( $pkgOwner eq "" ) {
                $own = $availFile[$ia];
                $own =~ m/^\s*([a-z]+\s*\|)([a-z]+)/;
                $pkgOwner = $2;
            }
        }
    }
    ### Find the people who get CVS commit email
    $eList = "";
    @eListH = 0;
    for ($ia=0; $ia<@loginfoFile; $ia++) {
        if ( $theDir =~ m/(\S+)\/(\S+)/ ) {
            $dr = "$1\\\/$2";
        } else {
            $dr = $theDir;
        }
        if ( $loginfoFile[$ia] =~ m/^ALL.*-m/ ) {
            print $loginfoFile[$ia]."\n" if $debugOn;
            $eList = &getList($loginfoFile[$ia]);
        } else {
            if ( $loginfoFile[$ia] =~ m/$dr\/$thePkg\/*\s+/ ) {
                print $loginfoFile[$ia]."\n" if $debugOn;
                $eList .= &getList($loginfoFile[$ia]);
            } elsif ( $loginfoFile[$ia] =~ m/$dr\/*\s+/ ) {
                print $loginfoFile[$ia]."\n" if $debugOn;
                $eList .= &getList($loginfoFile[$ia]);
            }
        }
    }

    ### subdirectories
#    if ( -d "$theRoot/$theDir/$thePkg/doc" ) {

    $nsub = 0;
    opendir(SUB, "$theRoot/$theDir/$thePkg");
    while (defined ($sub = readdir SUB)) {
        if (-d "$theRoot/$theDir/$thePkg/$sub") {
            if ( $sub ne "." && $sub ne ".." && $sub ne "CVS"
                 && $sub ne "doc" ) {
                $subDirs[$nsub] = $sub;
                $subdetails[$nsub] = &showFiles ($theRoot, $theDir, $thePkg, $sub, 1);
                $nsub++;
            }
        }
    }
    close SUB;
    $level = 0;
    $theSubDir = "";
    $details = &showFiles ($theRoot, $theDir, $thePkg, $theSubDir, $level);

    ### Print results
    if ( $theDir =~ m/pams\/([a-z0-9A-Z]+)/ ) {
        # for pams, include domain in package name
        $pkgName = $1."/".$thePkg;
    } else {
        $pkgName = $thePkg;
    }
    $pkgUrl = "<a href=\"/cgi-bin/prod/swguide.pl?ver=$ver&pkg=$pkgName&detail=2\">";


    if ( $showFlag > 0 ) { # print all pkg info
        ## associated pam?
        $thePamUrl = "";
        if ( $thePkg =~ m/St_([a-z0-9]+)_/ ) {
            if ( exists($pams{$1}) ) {
                $thePam = $pams{$1};
                $thePamUrl = "<a href=\"/cgi-bin/prod/swguide.pl?ver=$ver&pkg=$thePam&detail=2\">$thePam</a>";
            }
        }
        ## time since last mod
        $sinceMod = $curTime - $lastMod;
        $sinceMod = $sinceMod/3600/24; # days
        if ( $sinceMod < 3 ) {
            $ball="red";
        } elsif ( $sinceMod < 14 ) {
            $ball="green";
        } elsif ( $sinceMod < 60 ) {
            $ball="blue";
        } else {
            $ball="white";
        }
        $ballUrl="<img src=\"/images/".$ball."ball.gif\">";
        ($dy, $mo, $yr) = (localtime($lastMod))[3,4,5];
        if ($yr == 69 ) {
            $dy = 0;
            $mo = -1;
            $yr = 0;
            $sinceMod = 999;
        }
	$yr = $yr+1900;
        if ($linecount == 0) {
            $disp1="<font color=\"gray\">$ballUrl";
            $disp2="</font>";
        } else {
            $disp1="<b>$ballUrl";
            $disp2="</b>";
        }
        $pkgLine =
	    sprintf("$disp1%s%-30s%s %-6s %-3s %s%s%9s%s%4d Files".
		    "%7d Lines %02d/%02d/%04d %4d Days %s$disp2\n",
		    $pkgUrl,$theDir."/".$thePkg,"</a>",$readme,$doc,$cvs,
		    "<a href=\"$CVSURL/$pkgOwner/index.html#bottom\">",$pkgOwner,"</a>",
		    $filecount,$linecount,$mo+1,$dy,$yr,$sinceMod,$thePamUrl);
    } else {
        $pkgLine =
	    sprintf("%s%-30s%s %-6s %-3s %s\n",
		    $pkgUrl,$theDir."/".$thePkg,"</a>",$readme,$doc,$cvs);
    }

    if ( $showFlag >= 0 ) { print $pkgLine; }
    if ( $showFlag > 1 ) {
        print "<blockquote>\n";
        print $details;
        if ($nsub>0) {
            for ($ns=0; $ns<$nsub; $ns++) {
                print "<br><b>$subDirs[$ns]/</b>\n";
                print $subdetails[$ns];
            }
        }
        print "\n<b>CVS email recipients:</b>";
        print "    <a href=\"mailto:";
        foreach $e ( sort keys %eListH ) {
            print $e." ";
        }
        print "\">[Click to send email to recipients]</a>\n";
        $i=0;
        foreach $e ( sort keys %eListH ) {
            $i++;
            printf("%-33s",$e);
            if ($i%3 == 0) { print "\n"; }
        }
        print "</blockquote>\n";
    }
}

sub showFiles {
    my ($theRoot, $theDir, $thePkg, $theSubDir, $level) = @_;
    my $output;
    if ( $theSubDir ne "" ) { $thePkg .= "/".$theSubDir; }
    ### Files
    $lines = 0;

    return if ( ! -e "$theRoot/$theDir/$thePkg/CVS/Entries");
    open(ENTRIES, "<$theRoot/$theDir/$thePkg/CVS/Entries");

    while (<ENTRIES>) {
        $line = $_;
        chomp $line;
        print "Line $line\n" if $debugOn;
        @tokens = split(/\//,$line);
        if ( @tokens>2 ) {
            $fname = $tokens[1];
            # if the file searched for is in this package, display it
            if ( $find eq $fname ) { $showFlag = 2; }
            next if ( exists($ignoreStuff{$fname}) );
            next if ( $fname =~ m/^(\.)/ );
            next if ( $fname =~ m/\~$/ );
            $filecount++;
            $cver = $tokens[2];
##            This date is flaky. Does not correspond to most recent
##            commit date. Can be more recent. Have to pick up the
##            date from the repository file itself.
            $cdate = $tokens[3];
            $date = substr($cdate,4,12)." ".substr($cdate,22,2);

	    next if ( ! -e "/afs/rhic.bnl.gov/star/packages/repository/$theDir/$thePkg/$fname,v");
            open(REPFILE,"</afs/rhic.bnl.gov/star/packages/repository/$theDir/$thePkg/$fname,v");

            $owner = "";
            $repTime = 0;
            $repver = "";
            $reptag = "";
            while (<REPFILE>) {
                chomp;
                $repline = $_;
                if ( $reptag eq "" && $repline =~ m/\s*(.*):$cver/ ) {
                    $reptag = $1;
                }
                if ( $repver eq $cver ) {
                    $cdate = $repline;
                    if ( $cdate =~ m/date\s*([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+).*author\s+([a-z0-9]+)/ ) {
                        $date = "$2/$3/$1 $4:$5 ";
                        $repTime = timelocal($6,$5,$4,$3,$2-1,$1);
                        $owner = $7;
                        last;
                    }
                }
                $repver = $_; # the version number is on the preceding line
            }
            close(REPFILE);
            if ( $repTime > 0 ) {
                if ( $repTime > $lastMod ) { $lastMod = $repTime; }
            } else {
                if ( $writeTime > $lastMod ) { $lastMod = $writeTime; }
            }
            # stat
            $fullname = "$theRoot/$theDir/$thePkg/$fname";
            $writeTime = (stat($fullname))[9];

            $count = 0;
            $showLines = 0;
            if ($showFlag > 0) {
                $ee = "";
                ($ff, $dd, $ee) = fileparse("$fullname",'\.[a-zA-z]*');
                print "\"$ff\" \"$dd\" \"$ee\"\n" if $debugOn;
                $isScript = 0;
                if ( $ee eq "" ) {
		    next if ( ! -e $fullname);
                    open(FL,"< $fullname") or next;
                    $line1=<FL>;
                    close FL;

                    if ( $line1 =~ m/^#!/ ) {
                         $isScript = 1;
                     }
                }
                if ( exists($okExtensions{$ee}) || ($ff =~ m/akefile/)
                     || $isScript ) {
                    $showLines = 1;
                    if ( $isScript ) {
                        $ftype = "script";
                    } elsif ( $ff =~ m/akefile/ ) {
                        $ftype = "Makefile";
                    } else {
                        $ftype = $okExtensions{$ee};
                    }

		    next if ( ! -e "$theRoot/$theDir/$thePkg/$fname");
                    open(FILE,"< $theRoot/$theDir/$thePkg/$fname") or next;
                    @lines=<FILE>;
                    close FILE;

                    $inComment=0;
                    for ($ii=0; $ii<@lines; $ii++) {
                        ## Don't count comments. Imperfect but should get
                        ## most.
                        if ($owner eq "" && $ii<10) {
                            # Give a try at finding the owner
                            if ( $lines[$ii] =~ m/(Id:).*(,v).*(\d\d:\d\d:\d\d)\s([a-z]+)/ ) {
                                $owner = $4;
                            }
                        }
                        next if ( $lines[$ii] =~ m/^\s*$/ );
                        if ( $ftype eq "C++" || $ftype eq "C"
                             || $ftype eq "IDL" || $ftype eq "DDL" ) {
                            next if ( $lines[$ii] =~ m/^\s*\/\// );
                            if ( $lines[$ii] =~ m/^\s*\/\*/ ) { $cstart=1; }
                            if ( $lines[$ii] =~ m/\*\// ) { $cend=1; }
                            if ( $cstart==1 ) { $inComment=1; $cstart=0; }
                            # Bug: it includes the last line of a multi-line comment block
                            if ( $cend==1 ) { $inComment=0; $cend=0; }
                            next if ( $inComment );
                        } elsif ($ftype eq "FORTRAN" || $ftype eq "MORTRAN") {
                            next if ( $lines[$ii] =~ m/^[\*CDcd]{1}/ );
                        } elsif ($ftype eq "script"
                                  || $ftype eq "Makefile") {
                            next if ( $lines[$ii] =~ m/^\s*\#/ );
                        }
                        $count++;
                    }
                    if ( $ftype eq "" ) {
                        print "ERROR: no ftype for $theDir/$thePkg/$fname\n";
                    }
                    $typeCounts{$ftype} = $typeCounts{$ftype} +$count;
                }
                if ($showLines) {
                    $theLines = sprintf("%5d Lines",$count);
                } else {
                    $theLines = "           ";
                }

                if ( $repTime > 0 ) {
                    $sinceMod = $curTime - $repTime;
                } else {
                    $sinceMod = $curTime - $writeTime;
                }
                $sinceMod = $sinceMod/3600/24; # days
                if ( $sinceMod < 3 ) {
                    $ball="red";
                } elsif ( $sinceMod < 14 ) {
                    $ball="green";
                } elsif ( $sinceMod < 60 ) {
                    $ball="blue";
                } else {
                    $ball="white";
                }
                $ballUrl="<img src=\"/images/".$ball."ball.gif\">";

                if ( exists($okExtensions{$ee}) || ($ff =~ m/akefile/)
                     || $isScript ) {
                    if ( $ball ne "white" ) {
                        # count lines for recently modified files
                        $typeCountsRecent{$ftype} = $typeCountsRecent{$ftype} +$count;
                    }
                }

                ## Does ROOT class doc exist?
                $fnameFull = $fname;
                $fnameLen = length $fname;
                $fillLen = 35 - $fnameLen;
                if ( $ftype eq 'C++' ) {
                    if ( -e "/afs/rhic.bnl.gov/star/packages/$rel/StRoot/html/$ff.html" ) {
                        $fnameFull = "<a href=\"/STAR/comp/src/$rel/StRoot/html/$ff.html\">$ff</a>$ee";
                    }
                }

		## Prepare file extention for doxygen
		$fnameFull = &DoxyCode($fname,2);
		$CRef = &DoxyCode($fname,1," ","ClassRef");
		# We can generate other cross-reference list such as the
		# one generated while using the \file comment.
		if($CRef eq ""){
		    $CRef = &DoxyCode($fname,2," ","FileRef");
		}

                $blank='                                              ';
                $output .= sprintf("%s%s%s %-8s %s%-7s%s %10.10s %s %s%9.9s%s %10.10s %5.5s\n",
                                   $ballUrl,$fnameFull,substr($blank,0,$fillLen),
				   $CRef,
                                   "<a href=\"/cgi-bin/cvsweb.cgi/$theDir/$thePkg/$fname?rev=$cver&content-type=text/x-cvsweb-markup\">",$cver,"</a>",
                                   $date,
                                   "<a href=\"/cgi-bin/cvsweb.cgi/$theDir/$thePkg/$fname\">CVS</a>",

                                   "<a href=\"$CVSURL/$owner/index.html#bottom\">",$owner,"</a>",
                                   $theLines,
				   $reptag);

                print "$output" if $debugOn;
                $linecount += $count;
            }
        }
    }
    return $output;
}

######################
sub getList {
    my ( $line ) = @_;
    my @tks = split(/\s/,$line);
    my $i=0;
    my $list = "";
    foreach $t ( @tks ) {
        if ( $t eq "-m" ) {
            if ( $list ne "" ) { $list .= " "; }
            $list .= $tks[$i+1];
            $eListH{$tks[$i+1]}++;
        }
        $i++;
    }
    return $list;
}

sub DoxyCode
{
    my($src,$mode,$b1,$b2) = @_;
    my($rv);

    if( defined($b1) ){
	$rv = $b1;
    } else {
	$rv  = $src;
    }
    if( ! defined($b2) ){ $b2 = $src;}
    if($mode == 1){
	#
	# Class file definition all formatted by doxygen
	#
	if($src =~ /\.h/){
	    $src =~ s/\..*//;
	    if(-e "$DOXPATH/class$src.html"){
		$rv = "<a href=\"$DOXURL/class$src.html\">$b2</a>";
	    }
	}
    } elsif ($mode == 2){
	#
        # Plain source code mode. Return doxygen URL
	#
	$tmp = $src;
	$tmp =~ s/_/__/g;
	$tmp =~ s/\./_8/g;
	$tmp.= "-source.html";

	if( -e "$DOXPATH/$tmp"){
	    $rv = "<a href=\"$DOXURL/$tmp\">$b2</a>";
	}
    }
    $rv;
}


# $Log: swguide.pl,v $
# Revision 1.10  2007/11/05 19:42:00  jeromel
# /STAR/images -> /images
#
# Revision 1.9  2006/08/15 17:46:16  jeromel
# Misc fixes
#
# Revision 1.8  2006/08/15 17:36:56  jeromel
# rhic -> rhic.bnl.gov
#
# Revision 1.7  2003/12/22 14:23:10  jeromel
# Trailing spaces removed
#
# Revision 1.6  2003/12/22 14:20:43  jeromel
# Adjustment /STAR/images
#
# Revision 1.5  2002/01/27 00:17:35  jeromel
# Removed unused variables (forgot to do this as the last clean-up). Tested
# and fine as-is.
#
# Revision 1.4  2002/01/26 23:34:44  jeromel
# Modified to use doxygen instead of lxr, fixed a Y2000 bug in date and diverse
# formatting issues.
#
# Revision 1.3  2002/01/07 20:40:18  jeromel
# /STARAFS/ -> /STAR/
#
# Revision 1.2  2002/01/03 04:07:46  starlib
# replace 'src' link for lxr by 'dox' link for doxygen
#
# Revision 1.1  2001/11/22 00:19:55  jeromel
# Finally at thr right place ...
#
# Revision 1.1  2001/11/21 20:21:25  jeromel
# Latest version used for swguide. Was running from Wenaus area in
# crontabs (???).
#
# Revision 1.10  1999/10/30 15:10:03  wenaus
# Improve README, doc handling
#
# Revision 1.9  1999/09/21 12:25:00  wenaus
# Update to run on Solaris
#
# Revision 1.8  1999/09/20 22:55:16  wenaus
# Move output area to RCF NFS web area
#
# Revision 1.7  1999/08/18 13:07:54  wenaus
# Move data files to datapool
#
# Revision 1.6  1999/08/08 18:51:31  wenaus
# Report open failure to page
#
# Revision 1.5  1999/07/25 16:26:52  wenaus
# Report linecounts in files modified in last 2 months
#
# Revision 1.4  1999/07/10 13:17:21  wenaus
# Add ROOT class doc links, when they exist, which isn't too often
#
# Revision 1.3  1999/07/07 13:21:07  wenaus
# faster and more info presented
#
#
