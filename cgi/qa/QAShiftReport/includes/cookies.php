<?php

global $cookiepath,$domain,$undef;

    $cookiepath = "/devcgi/qa/QAShiftReport/";
    $domain = "star.bnl.gov";
    $undef = "unknown";

    function defd($str) {
      global $undef;
      return (($str != $undef) && ($str != ""));
    }
    function eraseCookie($cookieName) {
      global $cookiepath, $domain;
      setcookie($cookieName,"",0,$cookiepath,$domain);
    }
    function QAsetCookie($cookieName,$val) {
      global $cookiepath, $domain, $undef;
      eraseCookie($cookieName);
      if ($val == "") { $val = $undef; }
      $exptime = time() + (3600*24);
      $res = setcookie($cookieName,$val,$exptime,$cookiepath,$domain);
      if (!$res) logit("Error setting cookie: $cookieName => $val");
    }
    function getCookie($cookieName) {
      if (isset($_COOKIE[$cookieName])) {
        return $_COOKIE[$cookieName];
      }
      global $undef;
      return $undef;
    }

?>
