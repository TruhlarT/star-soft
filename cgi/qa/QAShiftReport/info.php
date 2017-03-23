<?php

###########################
# Form for entering shift info
#

@(include "setup.php") or die("Problems (0).");
incl("loadSession.php");
incl("dbmembers.php");

getPassedVarStrict("work");

if (!defd($work)) {
  header("location: ${webdir}sessions.php");
  exit;
}

getPassedVarStrict("mode");
$play = 0;
getPassedInt("play",1);
logit("PLAY $play");

#Set the session
loadSes($work,$play);

#Check where to route the user:
# possibilities include
# a) new session (mode = Edit)            => info
# b) new copied session (mode=CopyX)      => contents
# c) old session (mode=View)              => contents
# d) from menu to edit (mode = Edit)      => info
# e) from info with error (mode = ErrorX) => info

if (substr($mode,0,1) != "E") {
  header("location: ${webdir}contents.php?mode=${mode}&play=${play}");
  exit;
}



#Continue with Shift Info form
head("STAR QA Shift Report Basic Info");

jqry();

body();

fstart("basicInfo","saveEntry.php");
?>

<h3>QA Shift Report Form: Shift Info</h3>

<?php
$errant = (substr($mode,0,5) == "Error" ? substr($mode,8) : substr(errInfo($work),3));
if (strlen($errant)>0) {
  $errs = split($errTok,$errant);
  foreach ($errs as $k => $err) {
    print "<font color=\"red\">ERROR: You have "
    . str_replace("_"," ",$err) . "! Please correct!</font><br>\n";
  }
}
$membsInsts = getMembersInstitutions();
$instList = "<option value=\"\">--- Institutions ---</option>\n";
$membList = "<option value=\"\">--- People ---</option>\n";
foreach ($membsInsts as $inst => $people) {
  $inst2 = str_replace(" ","_",$inst);
  $instList .= "<option value=\"${inst2}\">${inst}</option>\n";
  foreach ($people as $l => $person) {
    $lastName = $person[0];
    $firstName = $person[1];
    $membList .= "<option value=\"${firstName} ${lastName}\" class=\"${inst2}\">${lastName}, ${firstName}</option>\n";
  }
}
?>


Affiliation:
<select name="affiliation" id="affiliation_id">
<?php print $instList; ?>
</select>
<br>

Name:
<select name="name" id="name_id">
<?php print $membList; ?>
</select>
<br>

Shift Date: 
<select name=datem>
<option value="01">01 (Jan)</option>
<option value="02">02 (Feb)</option>
<option value="03">03 (Mar)</option>
<option value="04">04 (Apr)</option>
<option value="05">05 (May)</option>
<option value="06">06 (Jun)</option>
<option value="07">07 (Jul)</option>
<option value="08">08 (Aug)</option>
<option value="09">09 (Sep)</option>
<option value="10">10 (Oct)</option>
<option value="11">11 (Nov)</option>
<option value="12">12 (Dec)</option>
</select>/<select name=dated>
<?php for ($mo = 1; $mo<=31; $mo++) {
  $month = nDigits(2,$mo);
  print "<option value=\"$month\">$month</option>\n";
} ?>
</select>/<select name=datey>
<?php for ($yr = 4; $yr<=date("y")+date("m")/12; $yr++) {
  $year = nDigits(2,$yr);
  print "<option value=\"$year\">20$year</option>\n";
} ?>
</select>
(mm/dd/yyyy, e.g. 04/30/2007, <b>NOT</b> 30/04/2007)<br>

Shift Time:
Start: <input name=start size=6 maxlength=5> 
End: <input name=end size=6 maxlength=5> 
(hh:mm, e.g. 16:30)<br>
<font size=-1>
PLEASE ENTER THE START AND END TIMES OF THE SHIFT ACCORDING
TO THE TIME AT BNL (U.S. EASTERN TIME)!
(current time and date at BNL is: <b>
<?php print date("H:i m/d/Y T"); ?>
</b>)
</font><br>

Shift Location:
<select name=location>
<?php print str_replace("_"," ",$instList); ?>
</select>
<br>



<?php

holine(20);
print "<center><div style=\"background-color:#ffdc9f; \">\n";
fsubmit("Save &amp; View Contents");
freset("Reset This Page");
fhidden("type","Info");
fhidden("work",$work);
print "</div></center>\n";
fend();

incl("fillform.php");
fillform($shift,"name_id","affiliation_id");
reloadMenu();

foot(); ?>
