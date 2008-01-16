<?php

@(include "setup.php") or die("Problems (0).");
incl("entry.php");

# Reset all issue indices
#if (isset($_POST["res"])) { resetIssueIndices(); }
if (isset($_POST["res"])) { fillDBIssuesFromFiles(); }
$issue;

# modes:
# view: browse an issue



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

function ViewDesc($iname,$idesc) {
    print "\n<b><font color=\"#800000\">";
    print stripslashes($iname) . "</font></b><br>\n";
    print "Full Description And Notes:\n";
    print "<b><font color=\"#C00000\" size=+1><pre>\n";
    print preserve_wordwrap(htmlentities(stripslashes($idesc)),75,chr(10));
    print "\n</pre></font></b>\n";
}

function EditDesc($iname,$idesc) {
    print "<input tabindex=1 name=iname size=50 value=\"";
    print stripslashes($iname) . "\"><br>\n";
    print "Full Description:<br>\n";
    print "<textarea tabindex=2 name=idesc rows=14 cols=74>";
    print stripslashes($idesc) . "</textarea>\n\n<br>\n\n";
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
        print "><font color=\"#";
        if ($marked == 1) { print "800000"; }
        else { print "000080"; }
        print "\">${entT}</font></option>\n";
      }
      print "</select>\n";
    } else {
      fhidden("ftype",$type);
    }
}

function listis($arr,$typ) {
  foreach ($arr as $id => $desc) {
    fbutton("brw${id}",$id,"editIssueN(-${id},'${typ}','view')");
    print " : <font color=\"#800000\">" . stripslashes($desc) . "</font>";
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
    function CloseEditor() {
      window.close();
    }
    function NoteData() {
      note = document.issForm.note.value;
      if (note == "") {
        alert("Cannot enter an empty note or resolution!\n");
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
jend();
body();

fstart("issIDForm","issueEditor.php","_top");
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
    print "link: ${webdir}${refphp}?iid=${iid}</font>\n";
  }
}
fhidden("mode","view");
fend();

fstart("issForm","issueEditor.php","_top");
fhidden("issueYear","$issueYear");
########################################################
### Edit Issues:


if ($mode != "none") {

  # Setup variables
  getPassedVarStrict("type",1);
  $iname = "";
  $idesc = "";
  $isclosed = false;
  if ($mode == "save") {
    getPassedVar("iname");
    getPassedVar("idesc");
    if ($iid == 0) {
      $issue = new qaissue($iname,$idesc);
    } else {
      ($issue = readIssue($iid)) or died("Could not read issue " . $iid);
      $issue->Name = $iname;
      $issue->Desc = $idesc;
    }
    if ($type != "none") { $issue->InsureType($type); }
    $issue->Save();
    $iid = intval($issue->ID);
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
      $iname = $issue->Name;
      $idesc = $issue->Desc;
    } else {
      print "<i>Could not read issue $iid</i><br><br>\n";
      #     $iid = 0;
      $mode = "not";      
    }
  }

  if ($mode != "not") {

  # Date viewing
    if ($iid != 0) {
      if ($isclosed) {
        print "<i><b>THIS ISSUE IS CLOSED/RESOLVED!</b></i><p>\n";
      }
      PrintDates($issue);
    } else {
      print "<i>New issue</i><br>\n";
    }

    # Description viewing/editing
    linebreak();
    print "Name <font size=-1>(short description)</font>:";
    if (($mode == "edit") || ($mode == "new")) {
      EditDesc($iname,$idesc,$type);
      EditType($iid,$type);
      fsubmit("Save Issue","SetType()");
    } else {
      ViewDesc($iname,$idesc);
      if ($isclosed) {
        fbutton("reopenThis","Re-Open This Issue",
                "editIssueN(${iid},'${type}','reopen')");
      } else {
        fbutton("editThis","Edit Descriptions and Notes",
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
      }
    }

    holines(8);
  }
}

########################################################
### List Issues:

fbutton("createiss","Open/Create New Issue","CreateIssue()");
print "\n<br>\n<font size=-1>Issues can only be added.\n";
print " If you feel an issue needs to be removed, please contact ";
print "<a href=\"mailto:gene@bnl.gov\">Gene Van Buren</a>.</font>\n";
fhidden("mode","save");
fhidden("iid","$iid");
fhidden("type",$type);
holines(8);

$issueYear1 = $issueYear - 1;
print "<p align=right><font size=-1>Issues for RHIC Run ${issueYear1} only<br>\n";
print "(generally STAR run ID numbers ${issueYear}xxxxxx)<font></p>\n\n";

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
  fstart("resetIss","issueEditor.php","_top");
  print "<p align=right><font size=-3>";
  print "For debugging only. Please ignore.\n";
  fhidden("type",$type);
  fhidden("res","restart");
  fsubmit(" ");
  print "</font></p>\n";
  fend();
}

foot(); ?>
