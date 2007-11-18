#! /usr/bin/perl -w

################################################################
# QASR_sync.pl
#   author :  G. Van Buren - BNL
#   purpose:  synchronize temporary and archive (web) data for
#             STAR QA Shift Reports
#


#############################################
# Global variables and functions
#

use File::Path;
use File::Copy;
use File::Basename;
use File::Find;
no warnings 'File::Find';

if ($ENV{'HTTP_HOST'}) exit;

$webdir = "/afs/rhic.bnl.gov/star/doc_public/www/comp/qa/QAShiftReport/";
$tempdir = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub/QA/";
mkpath($tempdir) if (! -d $tempdir);
$sdir = "";
$ifile = "";
$tfile = ".time_";
$tmp = "/tmp/QAout";

sub qafind { my $w = shift; find({ wanted => \&{$w}, no_chdir => 1 },$sdir); }
sub qawarn {
  my ($mvcp,$file1,$file2) = @_;
  mkpath(dirname($file2));
  ($mvcp =~ m/move/ ? move($file1,$file2) : copy($file1,$file2))
    or warn("Could not $mvcp from $file1 to $file2");
}
sub qatouch { utime(time,time,$ifile) or (open(F,">$ifile") && close F); }


#############################################
# Syncrhonize runFileSeqIndex
#

$sdir = "runFileSeqIndex";
$tempsdir = $tempdir . $sdir;
$lfile = $tempdir . "rFSI.lis";
$update_lfile = 0;

if ((-f $lfile) && (-d $tempsdir)) {
  chdir $tempdir;
  qafind("SyncRFSIT2W");
} else {
  mkpath($tempsdir);
  $update_lfile = 1;
}
if ($update_lfile) {
  # Update the temporary listing of the runFileSeqIndex directories
  unlink($lfile) if (-e $lfile);
  chdir $webdir;
  `/usr/bin/find $sdir -name "*.txt" > $lfile`;
}

sub SyncRFSIT2W {
  # Test file validity
  return if (! m/\/\d{1,2}\/\d{3}\/.+\.txt$/);
  return if ((! -f) || (-z) || ((-M) > (-M $lfile)));
  # Move the file
  $newfile = $webdir . $_;
  if (-e $newfile) { warn("Two copies of file: " . $_); return; }
  qawarn("move",$tempdir . $_, $newfile);
  $update_lfile++;
}


#############################################
# Syncrhonize archives
#

foreach $sdir ("archive","archiveOnline") {
  $cfile = $sdir . "/.Count";
  $tempsdir = $tempdir . $sdir;
  $tempcfile = $tempdir . $cfile;
  $webcfile = $webdir . $cfile;

  if ((-d $tempsdir) && (-e $tempcfile) && (-s $tempcfile)) {
    # First check for any new archived files
    $update_cfile = 0;
    chdir $tempdir;
    qafind("SyncArchT2W");
    if ($update_cfile) {
      # Update the archive counts from tempdir to webdir
      unlink($webcfile) if (-e $webcfile);
      qawarn("copy",$tempcfile,$webcfile);
    }
  } else {
    # Update the archive counts from webdir to tempdir
    mkpath($tempsdir);
    unlink($tempcfile) if (-e $tempcfile);
    qawarn("copy",$webcfile,$tempcfile);
  }
} # arch loop

sub SyncArchT2W {
  # Test file validity (year_mo = 20yy_mm)
  return if (! m/\/20\d\d_[01]\d\/Report_20\d\d_[01]\d_\d{4}\./);
  return if ((! -f) || (-z));
  $newfile = $webdir . $_;
  if (-e $newfile) { warn("Two copies of file: " . $_); return; }
  # Move the file
  qawarn("move",$tempdir . $_, $newfile);
  $update_cfile++;
}


#############################################
# Syncrhonize issues
#

# Decide on whether sync temp->web is necessary...
chdir $tempdir;
opendir($tdir,".");
foreach $sdir (readdir($tdir)) {
  next if (($sdir !~ m/^issues/) || (! -d $sdir)); # issues subdirs
  $tempsdir = $tempdir . $sdir;
  $tempcfile = $tempsdir . "/.count";
  $ifile = $tempdir . $tfile . $sdir;

  if (-f $tempcfile) {
    $resync = 0.0;
    if (! -d $webdir . $sdir) {
      if (-f $ifile) { warn("Cannot sync to " . $webdir . $sdir); }
      else { $resync = -1.0; }
    } elsif ((-f $ifile) && ((-M $ifile) > (-M $tempsdir))) {
      $resync = (-M $ifile);
    }
    if ($resync != 0) {
      qafind("SyncIssT2W");
      qatouch;
    }
    # else do nothing
  } else {
    warn("Cannot sync $sdir, possibly corrupt");
  }
} # temp issues loop
closedir($tdir);

# Decide on whether sync web->temp is necessary...
chdir $webdir;
opendir($wdir,".");
foreach $sdir (readdir($wdir)) {
  next if (($sdir !~ m/^issues/) || (! -d $sdir)); # issues subdirs
  $tempsdir = $tempdir . $sdir;
  $tempcfile = $tempsdir . "/.count";
  $ifile = $tempdir . $tfile . $sdir;
  if (!((-e $ifile) && (-d $tempsdir) && (-e $tempcfile) && (-s $tempcfile))) {
    unlink($ifile) if (-e $ifile);
    rmtree($tempsdir);
    qafind("SyncIssW2T");
    qatouch;
  }
} # web issues loop
closedir($wdir);

sub SyncIssT2W {
  # Test file validity (.count, type indices, issue data files)
  return if (! m/\/(\.count)|(\.typ.{1,3}index.?)|(\d{4,5}\.data)$/);
  return if ((! -f) || (-z));
  $newfile = $webdir . $_;
  return if (($resynce >= 0) && (-e $newfile) && ((-M) > $resync));
  # Copy the file
  unlink($newfile) if (-e $newfile);
  qawarn("copy",$tempdir . $_, $newfile);
}

sub SyncIssW2T {
  # Test file validity (.count, type indices, issue data files)
  return if (! m/\/(\.count)|(\.typ.{1,3}index.?)|(\d{4,5}\.data)$/);
  # Copy the file
  qawarn("copy",$webdir . $_, $tempdir . $_);
}


#############################################
# Syncrhonize logs
#

$sdir = "log";
$ifile = $tempdir . $tfile . $sdir;
$lfile = $ifile . "/QAlog.txt";

# only ten times per day
exit if ((-f $ifile) && ((-M $ifile) < 0.1));

chdir $tempdir;
  # Decide on whether sync temp->web is necessary...
if ((-f $ifile) && (-d $sdir)) {
  if ((-M $lfile) < (-M $ifile)) { qafind("SyncLogsT2W"); }
} else {
  unlink($ifile) if (-e $ifile);
  rmtree($sdir);
  chdir $webdir;
  qafind("SyncLogsW2T");
}
qatouch;

sub SyncLogsT2W {
  # Test file validity
  return if (! m/\/(QAlog\.txt)|(QAlog\.\d{3}\.txt\.gz)|(ESLsubmission\d+\.html)$/);
  return if ((-M) >= (-M $ifile));
  # Copy the file
  ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime) = stat;
  $newfile = $webdir . $_;
  unlink($newfile) if (-e $newfile);
  qawarn("copy",$tempdir . $_,$newfile);
  utime($atime,$mtime,$newfile);
}

sub SyncLogsW2T {
  # Test file validity
  return if (! m/\/(QAlog\.txt)|(QAlog\.\d{3}\.txt\.gz)|(ESLsubmission\d+\.html)$/);
  # Copy the file
  ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime) = stat;
  $newfile = $tempdir . $_;
  qawarn("copy",$webdir . $_,$newfile);
  utime($atime,$mtime,$newfile);
}


exit;
