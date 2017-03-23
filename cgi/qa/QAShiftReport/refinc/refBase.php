<?php

###############################
# Basic setup specific to RefHists
#
  
  $incdir = "../QAShiftReport/includes/";
  @(include_once $incdir . "base.php") or die("Problems (1).");
  incl("sections.php");

  # Base directory for working on reports:
  $bdir = $bdir_base . "QARefHists/";
  $url_bdir = "/~starweb/tmp/QARefHists/";
  
  # Reference cache "user"
  $QARefCache = "QARefCache";

  # Daemon output locations:
  $DAEMON_OUTPUT_DIR = "/afs/rhic.bnl.gov/star/users/starqa/WWW/QA/";
  $URL_FOR_DAEMON_OUTPUT = "https://www.star.bnl.gov/~starqa/QA/";

  # Log file
  $elog = $bdir . "log/QARefLog.txt";

  function inclR($file) {
    global $incdirR;
    @(include_once $incdirR . $file) or die("Problems (22).");
  }
  
  # Additional DBs
  $FOdb = "operation";
  $dbDAQInfo = "DAQInfo";
  $dbFOFileType = "FOFileType";
  $dbFOTrig = "FOTriggerSetup";
  $dbFOLoc = "FOLocations";
  $dbFODets = "FODetectorTypes";
  
  function isRunNum($input) {
    return preg_match('/^\d{7,8}$/',$input);
  }
  
  function userRefDir($user,$id=-1) {
    global $bdir;
    $urdir = "${bdir}users/${user}";
    if ($id >= 0) { $urdir .= "/${id}"; }
    ckdir($urdir);
    return $urdir;
  }
  function urlUserRefDir($user,$id=-1) {
    global $url_bdir;
    $urdir = "${url_bdir}users/${user}/";
    if ($id >= 0) { $urdir .= "${id}/"; }
    return $urdir;
  }
  function readUserName($dir) {
    global $DAEMON_OUTPUT_DIR;
    // remove line feeds
    $user = preg_replace("\r*\n*","",readText("${DAEMON_OUTPUT_DIR}${dir}/user.txt"));
    return (cleanStrict($user) ? $user : "unknown");
  }
  function readVerts($dir) {
    global $DAEMON_OUTPUT_DIR;
    $matches = array();
    $trgVerts = array();
    $nm = preg_match_all("/([A-Z][A-Z]) QA Events \(found vtx\/total\) (\d+) \/ (\d+)/",
            readText("${DAEMON_OUTPUT_DIR}${dir}/stdout.html"),$matches);
    for ($k =0; $k < $nm; $k++) {
      $type = $matches[1][$k];
      if (existsTrigType($type)) { $trgVerts[$type] = array($matches[2][$k],$matches[3][$k]); }
    }
    return $trgVerts;
  }


###############################
# Parameter parsing functions
#
  
  function getPassedFloat($vname,$noDie=0) {
    if (!getPassedVar($vname,$noDie)) { return false; }
    global $$vname;
    return cleanFloat($$vname);
  }
  

###############################
# Scrubber functions
#
  
  function cleanFloat(&$var) {
    # Allow only floats, e.g. 732 , -.45 , +0.67e-23 , 9e22 , 6.e+2
    if (!preg_match("/^(\-|\+)?(\d+|\d+\.\d*|\d*\.\d+)(e(\-|\+)?\d+)?$/",$var,$temparr)) {
      $var = floatval(0);
      return false;
    }
    return true;
  }


###############################
# General HTML
#
  
  function headR($title) {
    head($title);
    jstart();
    ?>
    var QARwins = new Object;
    function loadWindow(form,QARnam) {
      opennew = false;
      var cfr = window.parent.frames['QARcfr'];
      if (typeof(cfr.QARwins[QARnam]) != "object") { opennew = true; }
      else { if (cfr.QARwins[QARnam].closed || !(cfr.QARwins[QARnam].document)) { opennew = true; } }
      if (opennew) {
        ops = 'fullscreen=yes,toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes'; 
        cfr.QARwins[QARnam]=cfr.open('blank.php',QARnam,ops); 
        cfr.QARwins[QARnam].resizeTo(550,350);
      }
      setTimeout('document.forms.' + form + '.submit()',50);
      cfr.QARwins[QARnam].focus();
    }
<?php
    jend();
  }
  function headR2($title) {
    head($title);
    jstart();
    ?>
    var QARwins = new Object;
    function loadWindow(form,QARnam) {
      opennew = false;
      if (typeof(QARwins[QARnam]) != "object") { opennew = true; }
      else { if (QARwins[QARnam].closed || !(QARwins[QARnam].document)) { opennew = true; } }
      if (opennew) {
        ops = 'fullscreen=yes,toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes'; 
        QARwins[QARnam]=window.open('blank.php',QARnam,ops); 
        QARwins[QARnam].resizeTo(550,350);
      }
      setTimeout('document.forms.' + form + '.submit()',50);
      QARwins[QARnam].focus();
    }
<?php
    jend();
  }
  function helpButton($topic) {
    if (!cleanInt($topic)) { return; }
    $rtmrgn = ($topic>10 ? 20 : 5);
    print "<div id=\"helpButton${topic}\" class=\"refHelpButton\" style=\"position:absolute; top:3px; right:${rtmrgn}px; z-index:1020; \">\n";
    fstart("helpForm${topic}","refHelp.php","QARhelp");
    fhidden("topic",$topic);
    fbutton("Help${topic}","Help","loadWindow('helpForm${topic}','QARhelp')");
    fend();
    print "</div>\n\n";
  }
      
      
###############################
# Browser Info and Uses
#

  $whichBrowser = "unknown";
  function getWhichBrowser() {
    global $whichBrowser;
    if (!($whichBrowser == "unknown")) { return; }
    $user_agent = $_SERVER["HTTP_USER_AGENT"];
    if (preg_match('/MSIE/i',$user_agent) && !preg_match('/Opera/i',$user_agent)) {
      $whichBrowser = "MSIE"; 
    } elseif (preg_match('/Firefox/i',$user_agent)) { 
      $whichBrowser = "Firefox"; 
    } elseif (preg_match('/Chrome/i',$user_agent)) { 
      $whichBrowser = "Chrome"; 
    } elseif (preg_match('/Safari/i',$user_agent)) { 
      $whichBrowser = "Safari"; 
    } elseif (preg_match('/Opera/i',$user_agent)) { 
      $whichBrowser = "Opera"; 
    } elseif (preg_match('/Netscape/i',$user_agent)) { 
      $whichBrowser = "Netscape"; 
    } else {
      $whichBrowser = "unknown";
    }
  }
  function onSelect($name,$action) {
    global $whichBrowser;
    if ($whichBrowser == "unknown") { getWhichBrowser(); }
    $tiout = 100;
    $str = "<select name=$name";
    if (!($whichBrowser === "Safari")) {
      # Chrome + Firefox + others
      $str.= " onchange=\"setTimeout('${action}',${tiout})\"";
      #$str.= " onblur=\"setTimeout('${action}',${tiout})\"";
    }
    if (!(($whichBrowser === "Chrome") || ($whichBrowser === "Firefox"))) {
      # Safari + others
      $str.= " onclick=\"setTimeout('${action}',${tiout})\"";
    }
    return $str . ">\n";
  }

?>
