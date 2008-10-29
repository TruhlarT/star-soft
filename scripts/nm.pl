#!/usr/bin/perl

#
# Usage: nm.pl SymbolToLocate [LibraryPattern]
#
# (c) J.Lauret 2003-2008
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
if( ! defined($ARGV[2]) ){
    if ( defined($ENV{INSURE}) ) {
	$dir = "$STAR/.$OS/ILIB";
    } elsif ( defined($ENV{NODEBUG}) ){
	$dir = "$STAR/.$OS/LIB";
    } else {
	$dir = "$STAR/.$OS/lib";
    }
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
    
print "\tAdding files from $ROOTSYS/lib/$pat\n";
push(@all,glob("$ROOTSYS/lib/$pat"));

print "\tAdding files from $CERN/$CERN_LEVEL/lib/*.a\n";
push(@all,glob("$CERN/$CERN_LEVEL/lib/*.a"));

if ( defined($OSG) ){
    print "\tAdding Globus librraies from $OSG/globus/lib/*.so\n";
    push(@all,glob("$OSG/globus/lib/*.so"));
}

foreach $file (@all){
    chomp(@res = `nm $file | /bin/grep $symb`);
    if($#res != -1){
	print "$file >>\n";
	foreach $el (@res){
	    if ($el =~ /(\s+A )(.*)/){
		print "$el   \t[Absolute symbol]\n";		
	    } elsif ($el =~ /(\s+B )(.*)/){		
		print "$el   \t[bss (unitialized data space)]\n";
	    } elsif ($el =~ /(\s+C )(.*)/){		
		print "$el   \t[COMMON symbol]\n";
	    } elsif ($el =~ /(\s+D )(.*)/){		
		print "$el   \t[Data object symbol]\n";
	    } elsif ($el =~ /(\s+F )(.*)/){		
		print "$el   \t[File symbol]\n";
	    } elsif ($el =~ /(\s+G )(.*)/){		
		print "$el   \t[Small data object symbol (optimized access)]\n";
	    } elsif ($el =~ /(\s+I )(.*)/){		
		print "$el   \t[Indirect reference (GNU extension)]\n";		
	    } elsif ($el =~ /(\s+N )(.*)/){		
		print "$el   \t[Symbol has no type or is a debugging information]\n";
	    } elsif ($el =~ /(\s+L )(.*)/){		
		print "$el   \t[Thread-Local storage symbol]\n";
	    } elsif ($el =~ /(\s+S )(.*)/){		
		print "$el   \t[Section symbol for small objects]\n";
	    } elsif ($el =~ /(\s+T )(.*)/){		
		print "$el   \t[Text symbol or code section (defined)]\n";
	    } elsif ($el =~ /(\s+U )(.*)/){
		print "$el   \t[Undefined symbol (MUST be resolved))]\n";		
	    } elsif ($el =~ /(\s+V )(.*)/){
		print "$el   \t[Weak object symbol]\n";	
	    } elsif ($el =~ /(\s+W )(.*)/){
		print "$el   \t[Implicit weak object symbol (untagged)]\n";						
	    } else {
		print "$el\n";
	    }
	}
    }
}
