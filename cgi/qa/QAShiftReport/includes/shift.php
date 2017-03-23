<?php

global $shiftCookie,$dirCookie;

    $shiftCookie = "QAShiftSessionName";
    $dirCookie = "QAShiftDirName";
    $localShiftSesName = "";

    incl("cookies.php");

    function setSesName($val) {
      global $shiftCookie;
      if ((defd($val)) && (strlen($val) >= 2)) {
        QAsetCookie($shiftCookie,chop($val));
        return;
      }
    }
    function getSesName() {
      global $shiftCookie,$localShiftSesName,$undef;
      if ($localShiftSesName == $undef) {
        $name = getCookie($shiftCookie);
        #if (!is_dir(getSesDir($name))) { return $undef; }
        if (strlen($name) > 1) { $localShiftSesName = $name; }
      }
      return $localShiftSesName;
    }
    function eraseSesName() {
      global $shiftCookie;
      eraseCookie($shiftCookie);
      eraseLocalShiftSesName();
    }
    function eraseLocalShiftSesName() {
      global $localShiftSesName,$undef;
      $localShiftSesName = $undef;
    }
    function getWrkDir() {
      global $bdir;
      $wdir = $bdir . "work/";
      ckdir($wdir);
      return $wdir;
    }
    function getSesDir($ses="") {
      if ($ses=="") { $ses = getSesName(); }
      return (getWrkDir() . $ses . "/");
    }
    function playSesFile($ses="") {
      return getSesDir($ses) . "PLAY";
    }
    function isPlaySes($ses="") {
      return file_exists(playSesFile($ses));
    }
    function setPlaySes($ses="",$play=1) {
      $file = playSesFile($ses);
      if ($play) { touch($file); }
      else { if (file_exists($file)) { unlink($file); } }
    }

    eraseLocalShiftSesName();
?>
