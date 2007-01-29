<?php

###############################
# Basic setup
#

    $bdir = "/tmp/QA/";
    $bdir = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub/QA/";
    $elog = $bdir . "log/QAlog.txt";
    $webDir = dirname($_SERVER["SCRIPT_NAME"]) . "/";
    $webHost .= "http://" . $_SERVER["HTTP_HOST"];
    $webFullDir = $webHost . $webDir;
    #historically, webDir did not include "/STAR"...
    if (substr($webDir,0,5) == "/STAR") { $webDir = substr($webDir,5); }
    $hdir = dirname($_SERVER["PATH_TRANSLATED"]) . "/";
    $htmldir = "html/";
    $htmlfull = $hdir . $htmldir;
    $refphp = $refphp = basename($_SERVER["PHP_SELF"],".php");
    function incl($file) { global $incdir; include_once($incdir . $file); }
    

    incl("shift.php");
    incl("logit.php");
    

###############################
# Page functions
#
    function head($title) {
      global $htmldir;
      include("${htmldir}head.html");
      print $title;
      include("${htmldir}head2.html");
    }
    function body()       { global $htmldir; include("${htmldir}body.html"); }
    function foot()       { global $htmldir; include("${htmldir}foot.html"); }
    
    
###############################
# Status functions
#
    function died($str) {
      $code = $_SERVER["REQUEST_URI"];
      $str = "*** DIED ***: ${code}: ${str}";
      logit($str);
      die("${str}\n");
    }
    function reloadMenu() {
      jstart();
      print "  parent.QAmfr.location.reload();\n";
      jend();
    }
    function needSesName() {
      global $webFullDir;
      $ses = GetSesName();
      if (!defd($ses)) {
        header("location: ${webFullDir}sessions.php");
	exit;
      }
      return $ses;
    }
    
    
###############################
# Parameter parsing functions
#
    function getPassedVar($vname,$noDie=0) {
      $given = 0;
      if (isset($_POST["$vname"])) { $given=1; }
      elseif (isset($_GET["$vname"])) { $given=2; }
      elseif ($noDie==0) { died("${vname} not passed!"); }
      else { return false; }
      global $$vname;
      if ($given==1) { $$vname = $_POST["$vname"]; }
      elseif ($given==2) { $$vname = $_GET["$vname"]; }
      return true;
    }
    function getPassedVarStrict($vname,$noDie=0) {
      if (!getPassedVar($vname,$noDie)) { return false; }
      global $$vname;
      return cleanStrict($$vname);
    }
    function getPassedInt($vname,$noDie=0) {
      if (!getPassedVar($vname,$noDie)) { return false; }
      global $$vname;
      return cleanInt($$vname);
    }
    

###############################
# Scrubber functions
#
    function cleanStrict(&$var) {
      # Allow only alphanumeric or underscore characters
      if (preg_match("/\W/",$var,$temparr)) {
        $var = "";
        return false;
      }
      return true;
    }
    function cleanInt(&$var) {
      # Allow only integers (with a possible minus sign)
      if (!preg_match("/^-?\d+$/",$var,$temparr)) {
        $var = intval(0);
        return false;
      }
      return true;
    }
    function cleanFileName(&$var) {
      # Useful for filenames, strip just about all special characters
      # but leave periods and forward slashes
      $var = preg_replace(
        "/[\s\|\>\<\;\*\?\!\@\$\%\^\&\(\)\'\"\:\{\}\[\]\`\~].*/","",$var);
    }
    function cleanAlphaFileName(&$var) {
      # Require filename to start with an alphanumeric or underscore
      # to prevent absolute filenames, or ones that go up dirs (e.g. ../*)
      if (preg_match("/^\W/",$var,$temparr)) {
        # just to give something back
        $var = preg_replace("/\W/","",$var);
        return false;
      }
      cleanFileName($var);
      return true;
    }


###############################
# Forms HTML
#
incl("forms.php");


###############################
# Java HTML
#
    function jstart() {
      print "\n<script type=\"text/javascript\">\n<!--\n";
    }
    function jend() {
      print "\n// -->\n</script>\n\n";
    }


###############################
# General HTML
#
    function linebreak() { print "<br>\n"; }
    function holine($width) { print "\n\n<p>\n<hr width=\"${width}%\">\n<p>\n\n\n"; }
    function holinel($width) { print "\n\n<hr width=\"${width}%\" align=left>\n\n\n"; }
    function holines($size) { print "\n\n<p>\n<hr size=\"${size}\" noshade>\n<p>\n\n\n"; }
    function nDigits($n,$val) {
      $str = strval($val);
      while (strlen($str) < $n) { $str = "0" . $str; }
      return $str;
    }
    function mkhref($ref,$val,$trg="QArfr",$onc="") {
      global $webFullFir;
      mkhref2($webFullDir . $ref,$val,$trg,$onc);
    }
    function mkhref2($ref,$val,$trg="QArfr",$onc="") {
      print "<a href=\"${ref}\" target=\"${trg}\"";
      if ($onc != "") { print " onclick=\"${onc}\""; }
      print ">${val}</a>\n";
    }

?>
