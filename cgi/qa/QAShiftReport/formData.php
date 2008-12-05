<?php

@(include "setup.php") or die("Problems (0).");
incl("entry.php");

# Routes:
# Add form data from menu: editit=no num=0 (temp)
# Edit form from contents: editit=yes, num=id
# Copy form from contents: editit=copy, num=id, send num=0
# Add/Remove/Refresh issues: editit=yes, num=same, send addissue != 0
#  (will use entry numbers <= 0 to indicate restore from temp entry file)


getPassedVarStrict("type");
getPassedVarStrict("editit");
getPassedInt("issueYear",1);

if ($type == "Info") {
  getPassedVarStrict("work");
  header("location: ${webdir}info.php?mode=Edit&work=${work}");
  exit;
}

# Better be an existing type
(existsType($type)) || died("Non-existent type: " . $type);

$num = 0;
getPassedInt("num",1);
$entr = false;
if ($editit != "no") {
  if ($num <= 0) {
    ($entr = readEntry("temp")) or died("Could not read temp entry.");
    $num = -1 * $num;
  } else {
    logit ("WENT FOR ENTRY $type $num");
    ($entr = readEntry($type,$num)) or died("Could not read entry " . $type . $num);
    if ($editit == "copy") { $num = 0; }
  }
}

head("STAR QA Shift Report");
jstart();
?>
    function AddIssueN(id) {
      form = document.dataForm;
      form.addissue.value = id;
      form.submit();
    }
    function RemoveIssueN(id) {
      form = document.dataForm;
      form.addissue.value = '-' + id;
      form.submit();
    }
    function EditIssue(id) {
      form = document.issEd;
      form.iid.value = id;
      form.mode.value = 'view';
      form.submit();
    }
    function Lookup() {
      form = document.lookupForm;
      form1 = document.dataForm;
      if (form1.runid.value == "") {
        alert("You must enter a Run ID first!");
        return;
      }
      form.run.value = form1.runid.value;
      form.submit();
    }
    function CheckDigits() {
      form = document.dataForm;
      runidN = Math.floor(form.runid.value);
      fseqN = Math.floor(form.fseq.value);
      runid7 = (runidN < 1000000);
      fseq7 = (fseqN < 1000000);
      if (runid7 || fseq7) {
        cString = "Do you really intend to have <7 digits?\n\n";
        if (runid7) cString += "Run ID: " + form.runid.value + "\n\n";
        if (fseq7) cString += "File Sequence: " + form.fseq.value + "\n\n";
        if (! confirm(cString) ) { return; }
      }
      runidD = ( (runidN % 1000000) - (runidN % 1000) ) / 1000;
      if ((runidD < 1) || (runidD > 366)) {
        cString = "Standard parsing of the Run ID indicates\n\n";
        cString += "day number: " + runidD;
        cString += "\n\nIs this what you want?\n\n";
        if (! confirm(cString) ) { return; }
      }
      form.submit();
    }
<?php
jend();
body();

fstart("dataForm","saveEntry.php");
fhidden("addissue",0);
?>

<h3>QA Shift Report Form:
<?php print $ents[$type]; ?>
</h3>

<b>Add one entry for each QA job examined!</b><p>

<?php if (($type=="MNT") || ($type=="MDP")) {
  fhidden("runid","");
} else { ?>
Run ID:
<input tabindex=1 name=runid size=9 maxlength=8>
<font size=-1>(usually a 7 or 8 digit number)
<?php
  fbutton("lookup","Lookup","Lookup()");
  print " other QA Reports for this Run</font>";
  linebreak();
  if (($type=="RDP") || ($type=="RNT")) {
    print "<font size=-1>";
    fbutton("refYear","Refresh Issues","RefreshIssues()");
    print " for this Run Year (e.g. examining run 6 data during later years)</font>";
    linebreak();
  }
} ?>
File Sequence number:
<input tabindex=2 name=fseq size=8 maxlength=7>
<font size=-1>(leave as NA if none available)</font><br>
Production Job ID:
<input tabindex=3 name=prodid size=20 value="NA"><br>
Production job status:
<input type=radio name=prodstat value=ok>OK
<input type=radio name=prodstat value=crashed>Crashed<br>
Number of events in this file:
<input tabindex=4 name=nevents size=8><br>
Number of events with reconstructed primary vertex:
<input tabindex=5 name=nprivs size=8><br>
QA job status:
<input type=radio name=jobstat value=ok>OK
<input type=radio name=jobstat value=crashed>Crashed<p>

If you would like to enter some additional comments beyond what
is described by the <b><i><font color="#400000">Active Issues</font></i></b>
below, please do so here.<br>
<textarea tabindex=10 name=rcomments rows=5 cols=60>
<?php
if ($entr) {
  print stripslashes($entr->info["rcomments"]);
} ?>
</textarea>
<p>

<?php
print "<center>\n\n";
fbutton("ContinueTwo","Save/Continue","CheckDigits()");
freset("Reset");
fhidden("num",$num);
fhidden("type",$type);
fhidden("editit",$editit);
print "</center>\n\n";



###################
# Issues Section
#

function sectionhead($tit) {
  print "\n\n<tr><td colspan=3>";
  print "\n<font color=\"#400000\"><b>${tit}:</b></font><br>\n";
  print "</td></tr>\n\n";
}
function listar($arr,$AR) {
  if (!is_array($arr)) { logit("formData.php: listar: " . gettype($arr)); }
  foreach ($arr as $id => $desc) {
    print "<tr><td>";
    fbutton("${AR}${id}","${AR}:${id}","${AR}IssueN('${id}')");
    print "</td>\n<td><font color=\"#800000\">";
    print stripslashes($desc) . "</font></td>\n<td>";
    fbutton("Edit${id}","Edit/Examine","EditIssue('${id}')");
    if ($AR == "Remove") { fhidden("x${id}","1"); }
    print "</td></tr>\n";
#    linebreak();
  }
}

print "<table border=0 cellspacing=3 cellpadding=0>\n";

# List active issues (if new entry, all issues from last entry are made active)
$actissues = array();
if ($entr) { $actissues = $entr->issues; }

sectionhead("<u><font size=+1>Active Issues for this Data Entry</font></u>");
if (count($actissues) > 0) {
  listar($actissues,"Remove");
} else {
  print "<tr><td colspan=3>No active issues.</td></tr>\n";
}

print "<tr><td align=right colspan=3>\n";
fbutton("issEd","Open/Create New Issue","document.issEd.submit()");
fbutton("refresh","Refresh Issues","AddIssueN(-${issueYear})");
print "</td></tr>\n\n";


# List issues from the last filed entry.
$previssues = getIssList(0,$type,$actissues);
sectionhead("<br><u><font size=+1>Inactive Issues</font></u>");
if (count($previssues) > 0) {
  sectionhead("Issues in the latest " . $ents[$type] . " entry");
  listar($previssues,"Add");
  holinel(30);
  if (count($actissues) > 0) { $actissues += $previssues; }
  else { $actissues = $previssues; }
  print "<tr><td colspan=3>\n";
  fbutton("addAllLatest","Add All Latest Issues","AddIssueN(1)");
  print "</td></tr>\n\n";
}

# List issues from past week, most recent first
$pastweek = getIssList(7.0,$type,$actissues);
if (count($pastweek) > 0) {
  sectionhead("Issues from past week");
  listar($pastweek,"Add");
}

# List all old issues
$oldissues = getIssList(-7.0,$type,$actissues);
if (count($oldissues) > 0) {
  sectionhead("Old/Unused Issues");
  listar($oldissues,"Add");
}

if (count($oldissues)+count($pastweek)+count($previssues) == 0) {
  print "<tr><td colspan=3>No inactive issues.</td></tr>\n";
}

fend();

print "<tr><td align=right colspan=3>\n";
fstart("issEd","issueEditor.php","QAifr");
fhidden("type",$type);
fhidden("mode","new");
fhidden("issueYear","$issueYear");
fhidden("iid",0);
fsubmit("Open/Create New Issue");
fbutton("refresh","Refresh Issues","AddIssueN(-${issueYear})");
print "</td></tr>\n\n";

print "\n</table>\n\n";

holinel(60);

print "<center>\n";
fbutton("Continue","Save/Continue","CheckDigits()");
fbutton("Reset","Reset","document.dataForm.reset()");
print "</center>\n";
fend();

fstart("lookupForm","showRun.php",
       "QAshowRun","POST",0);
fhidden("run",0);
fend();

if ($entr) {
  incl("fillform.php");
  fillform($entr->info);
} else {
  reloadMenu();
}

foot(); ?>
