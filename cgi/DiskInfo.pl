#! /opt/star/bin/perl -w

use CGI;

my $debugOn = 0;

&cgiSetup();

my $dir = $q->param("name");

### disk and dir info
my @diskInfo; 
my @dirInfo;

my $isDisk=0;
my @dirElements = split(/\//, $dir);
$isDisk = 1 if scalar(@dirElements) == 4;
 
@diskInfo = `df -P $dir` if $isDisk;
@dirInfo = `du -sk $dir` if ($dir =~ /^\/.+\/.+\/.+\/.+/);
my $noDirInfo = scalar(@dirInfo);

my $diskAvailable;
if ($isDisk) {
    $diskInfo[1] =~ /^(.+)\s+(\d+)\s+(\d+)\s+(\d+)/;
    $diskAvailable = int($3/1000);
}

my $dirSize;
if ($noDirInfo>0) {
    $dirInfo[0] =~ /(\s)/;
    $dirSize =  int($`/1000);
}

### dir entry info
opendir (DIR, $dir);
my @files = readdir(DIR);
my $noFiles = scalar(@files)-2;
$noFiles = $noFiles>0? $noFiles:0;

### print disk and dir info
&beginHtml();

if ($isDisk) {
print <<END;
<tr><td>disk available space: $diskAvailable Mb</td></tr>
END
}

if ($noDirInfo>0) {
print <<END;
<tr><td>directory size: $dirSize Mb</td></tr>
END
}

print <<END;
</table>
   <hr>
END

### print dir entries
if( $noFiles<100 ) {
print <<END;
Entry count: $noFiles
<pre>
END

  for($i=0; $i<$noFiles+2; $i++) {
      next if ($files[$i] =~ /^\.+/);
print <<END;
$files[$i]
END
    }
} else {
print <<END;
<UL>
<LI>Entry count: $noFiles
END


  @runArray = ();
  for($i=0; $i<$noFiles+2; $i++) {
    next if ($files[$i] =~ /^\.+/);
    if ( $files[$i] =~ /^st_\w+_\d+_/ ) {
      $runNumber = (split(/_/,$files[$i]))[2];
      push (@runArray, $runNumber) if (!arrayCheck($runNumber,\@runArray));
    }
  }

  if (scalar(@runArray)>0) {
print <<END;
<LI>Run numbers
<UL>
END

    @sortedRuns = sort {$a<=>$b} @runArray;

    foreach $runEach (@sortedRuns) {
print <<END;
<LI>$runEach
END
    }

print <<END;
</UL>
</UL>
END
}
}

&endHtml();

#################
sub beginHtml {


print <<END;

<html>
<head><title></title></head>
<body>
   <hr> 
      You selected <B> $dir </B>
<table>
END
}

###############
sub endHtml {

print <<END;
      </pre>
</body>
</html>
END

}

##############
sub arrayCheck() {

    my ($melement, $arrayAddr) = @_;
    $mIsThere = 0;

    @mArray = @$arrayAddr;

    foreach $arrayE (@mArray) {
      if( $arrayE eq $melement ) {
        $mIsThere = 1;
        last;
      } 
    }

    return $mIsThere;
  }

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}




