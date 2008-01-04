<?php

incl("files.php");
global $lockfile,$refphp;

# requested php
$refphp = basename($_SERVER["PHP_SELF"],".php");

# Do not write to log file while gzipping.
$lockfile = "/tmp/QAfilelock";
function waitForLock() {
  global $lockfile;
  if (file_exists($lockfile)) {
    # Don't trust a lock that's more than 30 seconds old
    #if (time()-filemtime($lockfile) > 30) {
    if (time()-filemtime($lockfile) > 3) {
      clearLock();
    } else {
      while (file_exists($lockfile)) { usleep(50000); }
    }
  }
  touch($lockfile);
}
function clearLock() {
  global $lockfile;
  rmfile($lockfile);
}

# add an entry to the log file
function logit($str) {
  global $elog;
  waitForLock();
  ckdir(dirname($elog));
  error_log("${str}\n",3,$elog);
  clearLock();
}

function rotateLog() {
  global $elog;
  # If log file is > 250k, gzip it
  if (filesize($elog) < 250000) { return; }

  # Prevent writing to log file while gzipping
  waitForLock();
  
  $dname = dirname($elog);
  $bname = basename($elog,"txt");
  $elogs = dirlist($dname,$bname);
  $numf = nDigits(3,count($elogs));
  $ofile = "${dname}/${bname}${numf}.txt.gz";
  `/usr/bin/gzip -c $elog > $ofile`;
  # If compression worked, remove old log file
  if (file_exists($ofile)) { rmfile($elog); }

  clearLock();
}

function logpage() {
  global $refphp;
  if (strpos($refphp,"toc.php"))  { return; }
  $logstr  = date("H:i:s m/d/y") . " : ";
  $logstr .= getSesName() . " : ";
  $logstr .= $refphp;
  if (!strpos($refphp,"saveEntry.php")) {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
      foreach ( $_POST as $k => $v ) {
        if (($k == "allDirs") || ($k == "idesc") ||
	    ($k == "iResolve")) { continue; }
        $logstr .= "\n  POST: $k => $v";
      }
    } elseif ($_SERVER["REQUEST_METHOD"] == "GET") {
      foreach ( $_GET as $k => $v ) { $logstr .= "\n  GET : $k => $v"; }
    }
  }
  logit($logstr);
# For more detailed debugging:
#  foreach ($_SERVER as $k => $v ) { logit("_SERVER $k => $v"); }
}

logpage();

?>
