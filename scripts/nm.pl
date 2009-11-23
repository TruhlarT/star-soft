#!/usr/bin/perl

#
# Usage: nm.pl SymbolToLocate [LibraryPattern]
#
# (c) J.Lauret 2003-2009
#

$STAR       = $ENV{STAR};
$ROOTSYS    = $ENV{ROOTSYS};
$OS         = $ENV{STAR_HOST_SYS};
$CERN       = $ENV{CERN};
$CERN_LEVEL = $ENV{CERN_LEVEL};
$OSG        = $ENV{OSG};

if ( !defined($ARGV[0]) ){
    die "Syntax: $0 SymbolToLocate [LibraryPattern]\n";
}

# try to locate nm
$NM = "";
foreach ( ("/usr/bin/nm","/bin/nm")){
    if ( -x $_ ){
	$NM = $_;
	last
    }
}
$NM ="nm" if ($NM eq "");


# else ...
$symb = $ARGV[0];

#
# ARG0 is the symbol but ARG1 may be a pattern
# for the library name to search.
#
if( ! defined($ARGV[1]) ) {
    $pat = "*";
} else {
    $pat = $ARGV[1];
}
if($pat !~ /\./){ $pat .= ".so";}

#
# Defines the directory to look-up.
# There is a STAR dependency here ...
#
$LIBL = "lib"; # default
if( ! defined($ARGV[2]) ){
    if ( defined($ENV{INSURE}) ) {
	$LIBL= "ILIB";
    } elsif ( defined($ENV{NODEBUG}) ){
	$LIBL = "LIB";
    } else {
	$LIBL = "lib";
    }
    $dir = "$STAR/.$OS/$LIBL";
} else {
    $dir = $ARGV[2];
}


#
# Resolve symbol 
#
if ($OS =~ m/icc/){
    chomp($CXXFILT = `echo $symb | iccfilt`);
} else {
    chomp($CXXFILT = `c++filt $symb`);
}


print "Searching for   $symb = $CXXFILT\n";

print "\tLooking into $dir/$pat\n";
push(@all,glob("$dir/$pat"));

# Match LIBL pattern if found, revert to "lib" otherwise
if ( -e  "$ROOTSYS/$LIBL"){
    $rs = "$ROOTSYS/$LIBL/$pat";
} else {
    $rs = "$ROOTSYS/lib/$pat";
}
print "\tAdding files from $rs\n";
push(@all,glob("$rs"));

# Also add user's directory
if ( -e  ".$OS/$LIBL"){
    print "\tAdding files from .$OS/$LIBL/$pat\n";
    push(@all,glob(".$OS/$LIBL/$pat"));
}



print "\tAdding files from $CERN/$CERN_LEVEL/lib/*.a\n";
push(@all,glob("$CERN/$CERN_LEVEL/lib/*.a"));


if ( defined($OSG) ){
    print "\tAdding Globus librraies from $OSG/globus/lib/*.so\n";
    push(@all,glob("$OSG/globus/lib/*.so"));
}

# a common file intermediate
$FF = "/tmp/nm$$.$<.tmp";

foreach $file (@all){
    unlink($FF) if ( -e $FF);
    `$NM $file >&$FF`;
    if ( -e $FF ){
	open(FI,"<$FF"); @SYM = <FI>; close(FI);
	chomp(@res = grep(/$symb/,@SYM));
    }
    
    # chomp(@res = `$NM $file >&$FF`); 
    # | /bin/grep $symb`);

    if($#res != -1){
	print "$file >>\n";
	foreach $el (@res){
	    $l   = length($el);
	    $c   = 80-$l;
	    $pad = "";
	    for ( ; $c >= 0 ; $c--){  $pad .= " ";}

	    if ($el =~ /(\s+A )(.*)/){
		print "$el$pad [Absolute symbol]\n";		
	    } elsif ($el =~ /(\s+B )(.*)/){		
		print "$el$pad [bss (unitialized data space)]\n";
	    } elsif ($el =~ /(\s+C )(.*)/){		
		print "$el$pad [COMMON symbol]\n";
	    } elsif ($el =~ /(\s+D )(.*)/){		
		print "$el$pad [Data object symbol]\n";
	    } elsif ($el =~ /(\s+F )(.*)/){		
		print "$el$pad [File symbol]\n";
	    } elsif ($el =~ /(\s+G )(.*)/){		
		print "$el$pad [Small data object symbol (optimized access)]\n";
	    } elsif ($el =~ /(\s+I )(.*)/){		
		print "$el$pad [Indirect reference (GNU extension)]\n";		
	    } elsif ($el =~ /(\s+N )(.*)/){		
		print "$el$pad [Symbol has no type or is a debugging information]\n";
	    } elsif ($el =~ /(\s+L )(.*)/){		
		print "$el$pad [Thread-Local storage symbol]\n";
	    } elsif ($el =~ /(\s+R )(.*)/){		
		print "$el$pad [Read only data section]\n";
	    } elsif ($el =~ /(\s+S )(.*)/){		
		print "$el$pad [Section symbol for small objects]\n";
	    } elsif ($el =~ /(\s+T )(.*)/){		
		print "$el$pad [Text symbol or code section (defined)]\n";
	    } elsif ($el =~ /(\s+U )(.*)/){
		print "$el$pad [Undefined symbol (MUST be resolved))]\n";		
	    } elsif ($el =~ /(\s+V )(.*)/){
		print "$el$pad [Weak object symbol]\n";	
	    } elsif ($el =~ /(\s+W )(.*)/){
		print "$el$pad [Implicit weak object symbol (untagged)]\n";
	    } else {
		print "$el\n";
	    }
	}
    }
}
unlink($FF) if ( -e $FF);
