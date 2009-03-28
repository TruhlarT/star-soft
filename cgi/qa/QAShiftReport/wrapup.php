<?php

@(include "setup.php") or die("Problems (0).");
incl("infohandling.php");

$ses = needSesName();
head("STAR QA Shift Report Submission");
readWrapup($ses);

jstart();
?>
  function subReport() {
    form = document.wrapupForm;
    if ((form.originator.value == "") && (form.origphone.value == "")) { 
      pstr = "An email address or phone number is required!\n";
      alert(pstr);
      return;
    }
    form.mode.value = arguments[0];
    if ((form.iexists.value == "0") && (form.mode.value != "SaveIt")) {
      pstr = "You need to enter your Shift Info before submitting!\n";
      alert(pstr);
      return;
    }
    if ((form.originator.value == "") && (form.mode.value != "SaveIt")) { 
      pstr = "WARNING: No email address was entered.\n";
      pstr += "A copy of the report cannot be mailed to you.\n";
      pstr += "If you want to see the report, you will need to\n";
      pstr += "go to the report archive from the QA web page.";
      alert(pstr);
    }
    if (arguments.length > 1) { form.target=arguments[1]; }
    form.submit()
  }
<?php
jend();
body();

fstart("wrapupForm","submit.php");

?>

<h3>QA Shift Report Form: End of Report and Submission</h3>

Current session: <b>
<?php print $ses; ?>
</b><br>
<font size=-1>
(Please select <u>Session</u> from the <b>Menu</b>
if this is not the correct session name.)
</font><p>

   If problems or anomalies were found which you suspect are due
   to hardware, calibrations or reconstruction, please notify
   the appropriate person(s).<p>

   Person(s) notified:
<textarea tabindex=70 name=rnotified rows=3 cols=40>
<?php print $wrapup["rnotified"]; ?></textarea>
<p>

Please enter information on where you can be reached within the
next few days:<br>
Email: <input name=originator size=40 value="<?php print $wrapup["originator"]; ?>"><br>
Phone: <input name=origphone size=20 value="<?php print $wrapup["origphone"]; ?>"><br>
<font size=-1>(A copy of this report will be emailed to the entered address
as well as being archived.)</font><br><br>

Please enter any additional comments you may have:<br>
<textarea name=anycomments rows=7 cols=70>
<?php print stripslashes($wrapup["anycomments"]); ?></textarea>
<p>

<?php

print "<center>\n";
holine(30);
print "<b>PLEASE NOTE:</b> If you are submitting data entries for Fast Offline, you\n";
print "will <u>need to know the STAR protected area password</u> for the summary\n";
print "of this Shift Report to appear in the Electronic Shift Log!<br>\n";

print "<div style=\"background-color:#ffdc9f; \">\n";
fbutton("saveIt","Save &amp; View Contents","subReport('SaveIt')");
freset("Reset This Page");
linebreak();
print "</div><div style=\"background-color:#ffcc9f; \">\n";
fbutton("sendIt","Save &amp; Submit Report, Erase Session","subReport('SendIt')");
fbutton("keepIt","Save &amp; Submit Report, Keep Session","subReport('KeepIt')");
print "</div></center>\n";

fhidden("mode","none");


linebreak();
linebreak();
if ($QAdebug) {
  print "<p align=right><font size=-3>";
  print "For debugging only. Please ignore.\n";
  fbutton("testIt","","subReport('TestIt')");
  print "</font></p>\n";
}


$ffile = getInfoFile($ses);
$iexists = 0;
if (file_exists($ffile)) { $iexists = 1; }
fhidden("iexists",$iexists);
fend();

# Make sure the QAnfr frame is blank (and not submit.php)
jstart();
print "  parent.QAnfr.location.href=\"${webdir}blank.html\";\n";
jend();

foot(); ?>
