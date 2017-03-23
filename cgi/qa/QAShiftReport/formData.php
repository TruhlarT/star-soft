<?php

@(include "setup.php") or die("Problems (0).");
incl("entry.php");
incl("issueSearch.php");

# Routes:
# Add form data from menu  : editit=no  , num=0 (temp)
# Edit form from contents  : editit=yes , num=id
# Copy form from contents  : editit=copy, num=id  , send num=0
# Fill form from _POST     : editit=fill
# Add/Remove/Refresh issues: editit=yes , num=same, send addissue != 0
#  (will use entry numbers <= 0 to indicate restore from temp entry file)


getPassedVarStrict("type");
getPassedVarStrict("editit");
getPassedInt("issueYear",1);

if ($type == "Info") {
  getPassedVarStrict("work");
  header("location: ${webdir}info.php?mode=Edit&work=${work}");
  exit;
}

head("STAR QA Shift Report");

# Better be an existing type
(existsType($type)) || died("Non-existent type: " . $type);


$sesDefd = defd(getSesName());
$num = 0;
$entr = false;
if ($sesDefd) {
  getPassedInt("num",1);
  if ($editit != "no") {
    if ($editit == "fill") {
      $entr = new qaentry($type);
      $entr->Fill($_POST);
    } else if ($num <= 0) {
      ($entr = readEntry("temp")) or died("Could not read temp entry.");
      $num = -1 * $num;
    } else {
      logit ("WENT FOR ENTRY $type $num");
      ($entr = readEntry($type,$num)) or died("Could not read entry " . $type . $num);
      if ($editit == "copy") { $num = 0; }
    }
  }
}

jstart();
?>
    if (top.location.href == window.location.href) {
      str  = "You did not have an existing QA Shift Report open\n";
      str += "Please close this window/tab and open a report in a new one.";
      alert(str);
      window.close();
    }
<?php
if ($sesDefd) {
  jhideshow();
?>
    var runshowing = 0;
    function AddRun() {
      if (showElemBlock("elrunid" + runshowing)) { runshowing++; }
    }
    function RemoveRun() {
      if (runshowing > 1) {
        runshowing--;
        if (hideElem("elrunid" + runshowing)) {
          document.dataForm.elements["runid" + runshowing].value = "";
        } else { runshowing++; }
      }
    }
    function AddIssueN(id) {
      form = document.dataForm;
      form.addissue.value = id;
      form.submit();
    }
    function RemoveIssueN(id) {
      AddIssueN('-' + id);
    }
    function EditIssue(id) {
      form = document.issEd;
      form.iid.value = id;
      form.mode.value = 'view';
      form.submit();
    }
    function NewIssue() {
      form = document.issEd;
      form.iid.value = 0;
      form.mode.value = 'new';
      form.submit();
    }
    function Lookup(runi) {
      runnum = document.dataForm.elements["runid" + runi].value;
      if (runnum == "") {
        alert("You must enter a Run ID first!");
        return;
      }
      form = document.lookupForm;
      form.run.value = runnum;
      form.submit();
    }
    function ShowRuns() {
      form = document.dataForm;
      runi = 1;
      while ((elrun = form.elements["runid" + runi]) && (elrun.value > 0)) {
        AddRun();
        runi++;
      }
    }
    function CheckDigits() {
      form = document.dataForm;
      runi = 0;
      while ((elrun = form.elements["runid" + runi]) && (elrun.value > 0)) {
        runidN = Math.floor(elrun.value);
        runid8 = (runidN < 10000000 || runidN > 30000000);
        if (runid8) {
          cString = "Do you have the right number of digits?\n\n";
          if (runid8) cString += "Run ID: " + elrun.value + "\n\n";
          if (! confirm(cString) ) { return; }
        }
        runidD = ( (runidN % 1000000) - (runidN % 1000) ) / 1000;
        if ((runidD < 1) || (runidD > 366)) {
          cString = "Standard parsing of the Run ID indicates\n\n";
          cString += "Run ID: " + elrun.value + ", day number: " + runidD;
          cString += "\n\nIs this what you want?\n\n";
          if (! confirm(cString) ) { return; }
        }
        runi++;
      }
      form.submit();
    }
    function my_is_int(value){
      if((parseFloat(value) == parseInt(value)) && !isNaN(parseInt(value))) {
        return true;
      } else { return false; } 
    }
    function trig2fseq() {
      form = document.dataForm;
      form.fseq.value = form.trigset.value;
    }
    function fseq2trig() {
      form = document.dataForm;
      if (my_is_int(form.fseq.value)) { form.trigset.value = "NA"; }
      else { form.trigset.value = form.fseq.value; }
    }
<?php
} else {
  print "    parent.QArfr.location.href = \"${webdir}sessions.php\";\n";
}
jend();
body();

fstart("dataForm","saveEntry.php");
fhidden("addissue",0);
print "\n\n<h3>QA Shift Report Form: ";
print $ents[$type];
print "</h3>\n\n<b>Add one entry for each QA job examined!</b><p>\n\n";
if (($type=="MNT") || ($type=="MDP")) {
  fhidden("runid","");
} else {
  print "<div>Run number(s): <font size=-1>(usually 8 digits)</font>\n";
  fbutton("addRunButton","more runs","AddRun()");
  fbutton("removeRunBUtton","less runs","RemoveRun()");
  print "</div>";
  for ($runi = 0; $runi < 32; $runi++) {
    $runi1 = $runi + 1;
    $elid = "elrunid${runi}";
    print "<div id=\"${elid}\" style=\"position:relative; display: none; \">\n";
    print "<input tabindex=${runi1} name=\"runid${runi}\" size=9 maxlength=8 value=\"\">\n";
    fbutton("lookup${runi}","Lookup","Lookup(${runi})");
    if ($runi == 0) { print "<font size=-1>other QA Reports for this run</font>"; }
    linebreak();
    print "</div>\n";
  }
  if (($type=="RDP") || ($type=="RNT")) {
    print "<font size=-1>";
    fbutton("refYear","Refresh Issues","RefreshIssues()");
    print " for this Run Year (e.g. examining run 6 data during later years)</font>";
    linebreak();
  }
}
print "Trigger type\n";
print "<select tabindex=40 name=trigset id=\"Ttrig\" onchange=\"trig2fseq()\">\n";
foreach ($trigs as $k => $v) {
  print "<option value=\"${k}\"". ($k == "NA" ? " selected" : "") . ">${k} - ${v}</option>\n";
} ?>
</select>
<font size=-1>(or file sequence number)</font>:
<input tabindex=50 name=fseq id="Tfseq" size=8 maxlength=7 onchange="fseq2trig()"><br>

File stream:
<select tabindex=51 name=fstream>
<option value="">not applicable</option>
<?php
foreach ($fstreams as $k => $v) {
  print "<option value=\"${k}\"". ($k == "ph" ? " selected" : "") . ">${v}</option>\n";
}
print "</select><br>\n";


fhidden("prodid","NA");
fhidden("prodstat","ok");
?>
Number of events in this dataset:
<input tabindex=52 name=nevents size=8><br>
Number of events with a reconstructed primary vertex:
<input tabindex=53 name=nprivs size=8><br>
<?php fhidden("jobstat","ok"); ?>

If you would like to enter some additional comments beyond what
is described by the <b><i><font color="#400000">Active Issues</font></i></b>
below, please do so here.<br>
<textarea tabindex=60 name=rcomments rows=5 cols=60>
<?php if ($entr) { print stripslashes($entr->info["rcomments"]); } ?>
</textarea>
<p>

<?php



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
  foreach ($arr as $id => $issData) {
    print "<tr><td>";
    $removal = ($AR == "Remove");
    $isscat = ($removal ? getCategoryForIssue($id) : $issData[1]);
    $isstxt = ($removal ? $issData : $issData[0]);
    fbutton("${AR}${id}","${AR}:${id}","${AR}IssueN('${id}')");
    print "</td>\n<td><font color=\"#500000\" size=-1><i>" . $isscat;
    print "</i></font> : <font color=\"#800000\">";
    print htmlentities(stripslashes($isstxt)) . "</font></td>\n<td>";
    fbutton("Edit${id}","Edit/Examine","EditIssue('${id}')");
    if ($removal) { fhidden("x${id}","1"); }
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

print "<tr><td>&nbsp;</td></tr><tr><td align=center colspan=3 bgcolor=\"#ffdc9f\">\n";
fbutton("ContinueTwo","Save &amp; View Contents","CheckDigits()");
fbutton("Reset","Reset This Page","reset()");
fhidden("num",$num);
fhidden("type",$type);
fhidden("editit",$editit);
print "</td></tr><tr><td>&nbsp;</td></tr>\n";

print "<tr><td align=right colspan=3 bgcolor=\"#ffcc9f\">\n";
fbutton("issEd2","Open/Create New Issue","NewIssue()");
fbutton("refresh","Refresh Issues","AddIssueN(-${issueYear})");
print "</td></tr>\n\n";

print "<tr><td colspan=3>\n";
varsForIssueSearch();
buildIssueSearch("AddIssueN(-${issueYear})");
print "</td></tr>\n\n";


# List issues from the last filed entry.
$previssues = getIssList(0,$type,$actissues);
sectionhead("<br><u><font size=+1>Available Inactive Issues</font></u>");
if (count($previssues) > 0) {
  sectionhead("Issues in the latest " . $ents[$type] . " entry");
  listar($previssues,"Add");
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

print "<tr><td align=right colspan=3 bgcolor=\"#ffcc9f\">\n";
fstart("issEd","issueEditor.php","QAifr");
fhidden("type",$type);
fhidden("mode","new");
fhidden("issueYear","$issueYear");
fhidden("iid",0);
fbutton("issEd1","Open/Create New Issue","NewIssue()");
fbutton("refresh","Refresh Issues","AddIssueN(-${issueYear})");
print "</td></tr>\n\n";

print "<tr><td>&nbsp;</td></tr><tr><td align=center colspan=3 bgcolor=\"#ffdc9f\">\n";
fbutton("Continue","Save &amp; View Contents","CheckDigits()");
fbutton("Reset","Reset This Page","document.dataForm.reset()");
print "</td></tr>\n";
print "\n</table>\n\n";
fend();

fstart("lookupForm","showRun.php","QAshowRun","POST",0);
fhidden("run",0);
fend();

if ($entr) {
  incl("fillform.php");
  fillform($entr->info);
} else {
  reloadMenu();
}
jstart();
print "  AddRun();\n";
print "  setTimeout(\"ShowRuns();fseq2trig();\",350);\n";
jend();

foot(); ?>
