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
      $res = setcookie($cookieName,"",0,$cookiepath,$domain);
      logit(($res ? "Success" : "Error") . " erasing cookie: $cookieName [${cookiepath}][${domain}]");
    }
    function QAsetCookie($cookieName,$val,$exptime=24) {
      # exptime is the expiration time in hours from now
      global $cookiepath, $domain, $undef;
      eraseCookie($cookieName);
      if ($val == "") { $val = $undef; }
      $exptime = time() + (3600 * $exptime);
      $res = setcookie($cookieName,$val,$exptime,$cookiepath,$domain);
      logit(($res ? "Success" : "Error") . " setting cookie: $cookieName => $val [${cookiepath}][${domain}]");
    }
    function getCookie($cookieName) {
      if (isset($_COOKIE[$cookieName])) {
        return $_COOKIE[$cookieName];
      }
      global $undef;
      return $undef;
    }
    function cookieEraser() {
      global $cookiepath, $domain;
      print "=0;expires=0;path=${cookiepath};domain=${domain}";
    }

?>
