<?php

@(include "setup.php") or die("Problems (0).");

$rhst = chop($_SERVER["REMOTE_ADDR"]);
$rhsn = gethostbyaddr($rhst);

logit("--------------------");
logit("HOST IP: ${rhst}");
logit("HOST   : ${rhsn}");
logit("BROWSER: " . $_SERVER["HTTP_USER_AGENT"]);
#logit("COOKIES: " . $_SERVER["HTTP_COOKIE"]);
#foreach ($_SERVER as $k => $v ) { logit("$k => $v"); }
logit("--------------------");

$erase = 0;
getPassedInt("erase",1);

# Might not have a session name cookie at first
$oldWork = getSesName();

# If passed erase, then remove the old session
if ($erase == 1) {
  if (defd($oldWork)) {
    $wDirName = getSesDir($oldWork);
    logit("Erasing: " . $wDirName);
    if (is_dir($wDirName)) { rmrf($wDirName); }
    $oldWork = "";
  }
  eraseSesName();
}


$allSes = " ";
$workDirs = dirlist(getWrkDir());

head("STAR QA Shift Report Sessions");
jstart();
?>
    var allSes = "";
    function checkSesName() {
      form = document.ses;
      sess = form.work.value;
      if (sess.length < 2) {
        lstr = "That session name is too short.\n";
        lstr += "The minimum length is 2 characters.\n";
        lstr += "Please select a different session name.";
        alert(lstr);
        return 2;
      }
      w1 = " " + sess + " ";
      if (allSes.indexOf(w1) > -1 ) {
        pstr = "That session name is already being used.\n";
        pstr += "Any new session must have a unique name.\n";
        pstr += "If you do not wish to continue that session,\n";
        pstr += "please go back and select a different session name.";
        alert(pstr);
        return 1;
      }
      form.mode.value = "Edit";
      return 0;
    }
    function makeCopy() {
      if (checkSesName() > 0) return;
      form = document.ses;
      form.mode.value = "Copy" + form.owork.value;
      form.submit();
    }
    function continueSes() {
      form = document.ses;
      sess = form.owork.value;
      form.work.value = sess;
      w1 = " " + sess + " ";
      idx = allSes.indexOf(w1);
      if (idx > -1 ) {
        play = allSes.substr(idx-1,1);
	form.play[play].checked = true;
      }
      form.submit();
    }
    function readyWork(val) {
      document.ses.owork.value = val;
    }
<?php
jend();
body();
?>

<h3>QA Shift Report Form: Session Selection</h3>

Please choose either a name for a new session,
or select from the available saved sessions.
If you need help, select Instructions from the
menu on the left.
<p>

<?php 
fstart("ses","info.php","QArfr");
fhidden("mode","View");
fhidden("owork",$oldWork);

print "Enter a <b>NEW</b> session name (no spaces, slashes, or
special characters, minumum of 2 characters, e.g. John1, Alan_June_15)";
linebreak();
finput("work",10);
fsubmit("Begin New Session","return (checkSesName() < 2)");
print "&nbsp;&nbsp;&nbsp;&nbsp;<i>Play</i> session:&nbsp;";
$plays[$play] = "0";
fradio("radio","play",$plays,0);
print "no&nbsp;&nbsp;";
fradio("radio","play",$plays,1);
print "yes (generate toy reports)";
linebreak();
if (count($workDirs) == 0) {

  holinel(20);

  print "No available saved sessions<p>\n";

} else {
  fbutton("cpy","Copy Selected Session (below) to New Session (above)","makeCopy()");
  
  holinel(20);

  print "Available saved sessions:<p>\n";

  $wDir = end($workDirs);
  while ($wDir) {
    $wDir = chop($wDir);
    if (defd($wDir)) {
      print "<input type=radio name=otherwork value=\"$wDir\"";
      if ($oldWork == $wDir) { print " checked"; }
      print " onfocus=\"readyWork('$wDir')\"";
      print " onclick=\"readyWork('$wDir')\"";
      print "> <b>$wDir</b>";
      $play = (isPlaySes($wDir) ? 1 : 0);
      if ($play) { print "&nbsp;<font size=-1><i>(play)</i></font>"; }
      print "<br>\n";
      $allSes .= "$play $wDir ";
    }
    $wDir = prev($workDirs);
  }
  reset($workDirs);
}

fbutton("stat","Continue Selected Session","continueSes()");
fend();
jstart();
print "    allSes = \"${allSes}\";";
jend();

if ($erase == 1) { reloadMenu(); }
foot(); ?>
