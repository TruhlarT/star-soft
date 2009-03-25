<?php

#############################
# Frame for Table of Contents
#

@(include "setup.php") or die("Problems (0).");
incl("entrytypes.php");

$work = getSesName();
head("STAR QA Shift Report Menu");
?>

    <style type="text/css">
    <!--
      a.items:link {color: navy; text-decoration: none; }
      a.items:visited {color: navy; text-decoration: none; }
      a.items:active {color: tomato; text-decoration: none; }
      a.items:hover {color: maroon; text-decoration: none; }
    -->
    </style>

<?php
jstart();
?>
    function eraseSession() {
      cString = "Do you really want to erase this session?\n\n";
      cString += "Session name: <?php print $work; ?>";
      if ( confirm(cString) ) { return true; }
      return false;
    }
    function showSubMenu() {
      document.getElementById('Tsubmenu').style.display = 'block';
      return false;
    }
    function hideSubMenu() {
      document.getElementById('Tsubmenu').style.display = 'none';
      return false;
    }
<?php
jend();
body();

function mymkhref($ref,$val,$trg="QArfr",$onc="") {
  print "    ";
  mkhref($ref . "\" class=\"items",$val,$trg,$onc);
}
function mymkhref2($ref,$val,$trg="QArfr",$onc="") {
  print "    ";
  mkhref2($ref . "\" class=\"items",$val,$trg,$onc);
}
function BeginRow($col="#ffdc9f") { print "  <tr><td bgcolor=\"${col}\">\n"; }
function EndRow() { print "  </td></tr>\n"; }
function NewRow($col="#ffdc9f") { EndRow(); BeginRow($col); }

print "<b>Menu</b>\n\n";
print "<table border=0 cellpadding=1 cellspacing=1 width=\"100%\">";
NewRow("#dfec9f");
mymkhref2("http://drupal.star.bnl.gov/STAR/comp/qa/offline/QAShiftReportInstructions",
  "<b>QA Shift Report Instructions</b>","QASRinstruct");
BeginRow("#efdc9f");

print "\n  <table cellpadding=0 cellspacing=0 border=0 width=\"100%\"><tr><td>\n";
mymkhref("sessions.php?erase=0","Session");
print "  </td><td align=right><b>$work</b></td></tr></table>\n\n";

# Include the following only if session is defined
if (defd($work)) {

NewRow();
print "Manage Contents:\n";
NewRow();
mymkhref("contents.php?mode=View","&#149; View Current Contents");
NewRow();
mymkhref("info.php?work=${work}&mode=Edit","&#149; (Re)Enter Shift Info");
EndRow();
?>
  <tr onmouseover="showSubMenu()" onmouseout="hideSubMenu()">
  <td bgcolor="#ffdc9f">
    &#149; <font color=navy>Add A Data Entry For...</font>

    <table id ="Tsubmenu" border=0 cellpadding=1 cellspacing=1
           style="display:none ;z-index:2">
<?php
foreach ($ents as $k => $v) {
  print "    <tr><td bgcolor=cornsilk>\n      ";
  mkhref("formData.php?editit=no&type=$k\" class=\"items",$v);
  print "    </td></tr>\n";
}
?>
    </table>


<?php

Newrow();
mymkhref("wrapup.php","&#149; Finish &amp; Submit Report");

}
# end of "if defined session"

Newrow("#ffcc9f");
mymkhref("issueEditor.php","Open Issue Browser/Editor","QAifr");
Newrow("#ffcc9f");
mymkhref2("showRun.php","Open Report Archive","QAafr");

if (defd($work)) {
Newrow("#ffbc9f");
mymkhref("sessions.php?erase=1","Erase Session &amp; Start Over",
       "QArfr","return eraseSession()");
}

Endrow();
print "</table>\n\n";

foot(); ?>
