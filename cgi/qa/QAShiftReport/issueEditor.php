<?php

@(include "setup.php") or die("Problems (0).");
incl("entry.php");
incl("sections.php");
incl("issueAttachments.php");
incl("report.php");

# Reset all issue indices
#if (isset($_POST["res"])) { resetIssueIndices(); }
if (isset($_POST["res"])) { fillDBIssuesFromFiles(); }
$issue = 0;
$nattach = 0;

# modes:
# view: browse an issue
# new: create a new issue
# edit: edit an issue
# add: add a note to an issue
# save: save edits to an issue
# close: close an issue
# isssearch: search for issues



############## PHP FUNCTIONS TO USE ################

function PrintDates($issue) {
  global $ents;
  print "Opened/Created: <b>" . $issue->First() . "</b><br>\n";
  foreach ($issue->times as $typ => $lt) {
    if ($typ == QAnull) {
      print "Last used/modified: <b>";
      print $issue->Last() . "</b><br>\n";
      print "<font size=-1>";
      if (count($issue->times) > 1) { print "Currently allowed types:"; }
      else { print "No currently allowed types."; }
      print "</font><br>\n";
    } else {
      print "Last used in a " . $ents[$typ] . " entry: <b>";
      print $issue->Last($typ) . "</b><br>\n";
    }
  }
}

function PrintRuns($iid) {
  global $issueYear;
  $runlist = getListOfRunsForIssue($iid);
  if (count($runlist)<1) return;
  print "<table border=0 cellpadding=0 cellspacing=0>\n";
  print "<tr valign=top><td>Runs with this issue active:</td><td align=right>";
  print "<div id =\"noRunList\"\n";
  print "       style=\"display:block ;z-index:2\">\n";
  fbutton("showRunsButton","Show full list of runs","toggleSection('RunList')");
  print "First-last runs: <b>" . min($runlist) . "-" . max($runlist) . "</b><br>";
  print "</div>\n";
  print "<div id =\"fullRunList\"\n";
  print "       style=\"display:none ;z-index:2\">\n";
  print "<table border=0 cellpadding=0 cellspacing=0><tr valign=top><td>\n";
  fbutton("hideRunsButton","Show only first-last runs","toggleSection('RunList')");
  print "</td><td>";
  print "<div id =\"noMissList\"\n";
  print "       style=\"display:block ;z-index:3\">\n";
  fbutton("showMissButton","...and inactive","toggleSection('MissList')");
  print "<font size=-1>\n";
  foreach ($runlist as $run) print "<br><b>$run</b>\n";
  print "</font>\n</div>\n";
  print "<div id =\"fullMissList\"\n";
  print "       style=\"display:none ;z-index:3\">\n";
  fbutton("hideMissButton","...only active","toggleSection('MissList')");
  $fullRunList = getRunsInIssYear($issueYear);
  $bigspace = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  print "<font size=-1>\n";
  foreach ($fullRunList as $run) {
    print "<br><font color=\"";
    if (in_array($run,$runlist)) {
      print "red\"><b>${bigspace}${run}</b>";
    } else {
      print "blue\" size=-2>${run}";
    }
    print "</font>\n";
  }
  print "</font>\n</div>\n";
  print "</td></tr></table>\n";
  print "</div>\n";
  print "</td></tr></table>\n";
}


function ViewDesc($issue) {
  print "<u>Tags:</u>\n<table border=0 cellpadding=0 cellspacing=0>\n";
  print "<tr valign=top><td>Category/Subsytem:</td>\n";
  print "<td><b><font color=\"#800000\">";
  print $issue->GetTagCategory() . "</font></b></td></tr>\n";
  #print "<tr valign=top><td>Relevant Plots:</td>\n";
  #print "<td><b><font color=\"#800000\">";
  #print $issue->GetTagPlots() . "</font></b></td></tr>\n";
  print "<tr valign=top><td>Keywords:</td>\n";
  print "<td><b><font color=\"#800000\">";
  print $issue->GetTagKeywords() . "</font></b></td></tr></table><br>\n";
  print "Name <font size=-1>(short description)</font>:";
  print "\n<b><font color=\"#800000\">";
  print htmlentities(stripslashes($issue->Name)) . "</font></b><br>\n";
  print "Full Description And Notes:\n";
  print "<b><font color=\"#C00000\" size=+1><pre>\n";
  print preserve_wordwrap(htmlentities(stripslashes($issue->Desc)),75,chr(10));
  print "\n</pre></font></b>\n";
}

function EditDesc($mode,$issue) {
  $iname = "";
  $idesc = "";
  if ($mode != "new") {
    $iname = stripslashes($issue->Name);
    $idesc = stripslashes($issue->Desc);
  }
  print "<i>Please use tags and an issue name which will make it\n";
  print "easy for others to identify and re-use this issue.</i><p>\n";
  print "<table border=0 cellpadding=0 cellspacing=0>\n";
  print "<tr><td colspan=3><u>Tags:</u></td></tr>\n";
  print "<tr valign=top><td>Category/Subsytem:</td>\n<td>";
  print printCategorySelector("icateg",$issue);
  print "</td><td><font size=-1>(required)</font></td></tr>\n";
  #print "Relevant Plots:" . printPlotsSelector("iplots",$issue);
  #print "<nobr><font size=-1>(optional, multi-select)</font></nobr><br>\n";
  print "<tr valign=top><td>Keywords:</td>\n<td>";
  beginSection("Keywords","List of keywords",3,"");
  print printKeywordsMultiSelector("ikeyws",$issue);
  endSection();
  print "</td><td><nobr><font size=-1>(optional, multi-select)</font></nobr></td></tr></table><br>\n";
  print "Name <font size=-1>(short description)</font>:";
  print "<input tabindex=1 name=iname size=50 value=\"${iname}\"><br>\n";
  print "Full Description:<br>\n";
  print "<textarea tabindex=2 name=idesc rows=14 cols=74>";
  print $idesc . "</textarea>\n\n<br>\n\n";
}

function EditNote() {
  print "Author: ";
  finput("auth",20);
  print " Note to add (or <b>resolution</b> if closing):<br>\n";
  print "<textarea tabindex=1 name=note rows=6 cols=74>";
  print "</textarea>\n\n<br>\n\n";
}

function EditType($iid,$type) {
  global $ents,$issue;
  $addtype = array("none" => "----------");
  $addtype += $ents;
  $atcount = count($ents);
  if ($iid != 0) { $atcount = count($issue->times); }
  if ($atcount > 0) {
    $addtype["none"] = "----------";
    print "Allow issue to be used for data entries of: ";
    print "<select name=\"ftype\">\n";
    foreach ($addtype as $typ => $entT) {
      $marked = 0;
      if (($iid != 0) && ($issue->HasType($typ))) { $marked = 1; }

      print "<option value=\"${typ}\"";
      if ($marked == 1) { print " disabled"; }
      if ($typ == $type) { print " selected"; }
      print ">${entT}</option>\n";
    }
    print "</select>\n";
  } else {
    fhidden("ftype",$type);
  }
}

function Details2AttachmentSection() {
  endSection();
  linebreak();
  beginSection("Attachments","Image Attachments",4,"#bfdc9f");
}

function listis($arr,$typ) {
  foreach ($arr as $id => $issData) {
    fbutton("brw${id}",$id,"editIssueN(-${id},'${typ}','view')");
    print " : <font color=\"#500000\" size=-1><i>" . $issData[1] . "</i></font>";
    print " : <font color=\"#800000\">" . htmlentities(stripslashes($issData[0])) . "</font>";
    linebreak();
  }
}

####################### END OF FUNCTIONS ##################


head("QA Issue Browser/Editor");
jstart();
?>
    function editIssueN(id,typ,mode) {
      form = document.issForm;
      if (typ == '.') typ = 'none';
      form.type.value = typ;
      if (id < 0) { form.iid.value = -id; }
      else { form.iid.value = id; }
      form.mode.value = mode;
      form.submit();
    }
    function CreateIssue() {
      form = document.issForm;
      form.mode.value = 'new';
      form.iid.value = 0;
      form.submit();
    }
    function SetType() {
      form = document.issForm;
      form.type.value = form.ftype.value;
    }
    function JustView() {
      form = document.issForm;
      form.mode.value = 'view';
      form.submit();
    }
    function CloseEditor() {
      window.close();
    }
    function NoteData() {
      note = document.issForm.note.value;
      if (note == "") {
        alert("Cannot enter an empty note or resolution!\n");
        return false;
      }
      icateg = document.issForm.icateg;
      if (icateg && icateg.value == 0) {
        alert("A category/subsystem must be selected!\n");
        return false;
      }
      auth = document.issForm.auth.value;
      if (auth == "") {
        var noauth = confirm("Do you really want to submit this anonymously?\n");
        if (noath==0) { return false; }
      } else {
        document.issForm.note.value = auth + " : " + note;
      }
      return true;
    }

<?php
jsToggleSection();
jend();
body();

fstart("issIDForm","","_top");
#print "<a href=\"javascript:_top.window.close()\">Close Window</a>\n";
fbutton("closeit","Close Window","CloseEditor()");
print "<h2>QA Issue Browser/Editor</h2>\n\n";

$type = "none";
$mode = "none";
$iid = 0;
getPassedInt("issueYear",1);
getPassedInt("iid",1);
if ($iid > 0) {
  $mode = "view";
  $issueYear = issYearFromId($iid);
  setIssMinMax();
}
getPassedVarStrict("mode",1);
if ($mode != "new") {
  print "Issue ID: ";
  if (($mode == "edit") || ($mode == "add") || ($mode == "close")) {
    print "<b>${iid}</b>\n";
  } else { finput("iid",5,$iid); fsubmit("Lookup"); }
  if ($iid>0) {
    print "<br>\n";
    print "<font size=-2>";
    print "direct link: <a href=\"${webdir}${refphp}.php?iid=${iid}\">";
    print "${webdir}${refphp}.php?iid=${iid}</a></font>\n";
  }
}
fhidden("mode","view");
fend();

fstart("issForm","","_top enctype=\"multipart/form-data\"");
fhidden("issueYear","$issueYear");
########################################################
### Edit Issues:

if ($mode != "none") {

  # Setup variables
  getPassedVarStrict("type",1);
  $isclosed = false;
  if ($mode == "save") {
    getPassedVar("iname");
    getPassedVar("idesc");
    getPassedInt("icateg");
    #getPassedVar("iplots",1);
    getPassedVar("ikeyws",1);
    if ($iid == 0) {
      $issue = new qaissue($iname,$idesc);
    } else {
      ($issue = readIssue($iid)) or died("Could not read issue " . $iid);
      $issue->Name = $iname;
      $issue->Desc = $idesc;
      clearTagsForIssue($iid);
    }
    if ($type != "none") { $issue->InsureType($type); }
    $issue->Save();
    $iid = intval($issue->ID);
    saveTagsForIssue($iid,"Categories",$icateg);
    #saveTagsForIssue($iid,"Plots",$iplots);
    saveTagsForIssue($iid,"Keywords",$ikeyws);
    $mode = "view";
  } elseif ($mode != "new") {
    if ($issue = readIssue($iid)) {
      if ($mode == "close") {
        getPassedVar("note");
        $issue->Close($note);
      } else if ($mode == "add") {
        getPassedVar("note");
        $issue->AddNote($note);
        $mode = "view";
      } else if ($mode == "reopen") {
        $issue->Reopen();
        $mode = "view";
      }
      $isclosed = $issue->IsClosed();
      if ($isclosed) { $mode = "view"; }
    } else {
      print "<i>Could not read issue $iid</i><br><br>\n";
      #     $iid = 0;
      $mode = "not";      
    }
  }

  if ($mode != "not") {

    beginSection("Details","Issue details",-7,"#efdc9f");
    # Date viewing
    if ($iid != 0) {
      if ($isclosed) {
        print "<i><b>THIS ISSUE IS CLOSED/RESOLVED!</b></i><p>\n";
      }
      PrintDates($issue);
      PrintRuns($iid);
    } else {
      print "<i>New issue</i><br>\n";
    }

    # Description viewing/editing
    linebreak();

    if (($mode == "edit") || ($mode == "new")) {
      EditDesc($mode,$issue);
      EditType($iid,$type);
      fsubmit("Save Issue","SetType()");
      Details2AttachmentSection();
      IAformForAttachment($iid);
    } else {
      ViewDesc($issue);
      if ($isclosed) {
        fbutton("reopenThis","Re-Open This Issue",
                "editIssueN(${iid},'${type}','reopen')");
        Details2AttachmentSection();
      } else {
        fbutton("editThis","Edit Tags, Descriptions, Notes",
                "editIssueN(${iid},'${type}','edit')");
        print "(Please use only for correcting errors!)<p>\n";
        EditNote();
        fbutton("addThis","Add Note",
                "if (NoteData()) editIssueN(${iid},'${type}','add')");
        fbutton("addThis","Close/Resolve",
                "if (NoteData()) editIssueN(${iid},'${type}','close')");
        linebreak();
        EditType($iid,$type);
        fsubmit("Allow Type","SetType()");
        Details2AttachmentSection();
        IAformForAttachment($iid);
        fbutton("attachThis","Upload File","JustView()");
      }
      if (IAattached()) IAhandleAttachment($iid);
    }
    linebreak();
    $nattach = IAtableOfAttachments($iid);
    endSection(); // Attachments
    print "<font size=-1>(Currently $nattach attachment" .
      ($nattach != 1 ? "s" : "") . ".)</font><br>\n";

    holines(8);
  }
}

########################################################
### List Issues:

print "<div style=\"background-color:#ffcc9f\">\n";
fbutton("createiss","Open/Create New Issue","CreateIssue()");
print "</div>\n";
print "<font size=-1>Issues can only be added.\n";
print " If you feel an issue needs to be removed, please contact ";
print "<a href=\"mailto:gene@bnl.gov\">Gene Van Buren</a>.</font><p>\n";
fhidden("mode","save");
fhidden("iid","$iid");
fhidden("type",$type);
fend();


varsForIssueSearch();
beginSection("Picker","Issue Search",(isIssueSearch() ? -5 : 5),"#ffdc9f");
buildIssueSearch();

holines(8);

$issueYear1 = $issueYear - 1;
print "<p align=right><font size=-1>Issues for RHIC Run ${issueYear1} only<br>\n";
print "(generally STAR run ID numbers ${issueYear}xxxxxx)</font></p>\n\n";

# Put the list of entry types in the order of whichever
# type we are examining first
$entorder = array();
if ($type == "none") {
  $entorder = $ents;
} else {
  $entorder[$type] = $ents[$type];
  foreach ($ents as $k => $v) {
    if ($k == $type) { continue; }
    $entorder[$k] = $v;
  }
}
$entorder[QAnull] = $noent;

# An empty array for excluding nothing
$z = array();
# An array for excluding all issues with assigned types
$allarray = array();

fstart("pickIssue","","_top");

foreach ($entorder as $entn => $enttitle) {

  print "\n\n<h3><font color=\"#400000\">Issues for: $enttitle</font></h3>\n\n";

  if ($entn == QAnull) { $z = $allarray; }

# List issues from past week, most recent first
  $pastweek = getIssList(7.0,$entn,$z);
  if (count($pastweek) > 0) {
    print "\n\n<b>Issues from past week:</b><br>\n\n";
    listis($pastweek,$entn);
    $allarray += $pastweek;
  }
  
# List all old/unused issues
  $oldissues = getIssList(-7.0,$entn,$z);
  if (count($oldissues) > 0) {
    print "\n\n<b>Old/Unused Issues:</b><br>\n\n";
    listis($oldissues,$entn);
    $allarray += $oldissues;
  }
  
# List all closed issues
  $closedissues = getIssList(0,$entn,$z,1);
  if (count($closedissues) > 0) {
    print "\n\n<b>Closed Issues:</b><br>\n\n";
    listis($closedissues,$entn);
    $allarray += $closedissues;
  }

  if (count($pastweek)+count($oldissues)+count($closedissues) == 0) {
    print "No known issues.<br>\n";
  }

  holinel(50);
}

fend();

if ($QAdebug) {
  fstart("resetIss","","_top");
  print "<p align=right><font size=-3>";
  print "For debugging only. Please ignore.\n";
  fhidden("type",$type);
  fhidden("res","restart");
  fsubmit(" ");
  print "</font></p>\n";
  fend();
}

endSection(); # Picker

if ($nattach>0) {
  jstart();
  print "    toggleSection('Attachments');\n";
  jend();
}

foot(); ?>
