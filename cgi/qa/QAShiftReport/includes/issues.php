<?php

incl("entrytypes.php");
incl("preserve_wordwrap.php");

###############################
# Class and functions for Issue handling
#

# Issues are kept in a directory under the
# name ####.data, where #### is their ID number.
# An index file of issue names and date-last-used
# is kept in for all issues, and for each type.
# The directories for issues have a number which
# generally corresponds to the run ID numbers, and
# is 1 greater than the RHIC Run Year (e.g. RHIC
# Run VIII starts with runs 8xxxxxx, but generally
# has runs 9xxxxxx, and its issues appear in a
# directory called issues9).


global $issueList,$issuePrev,$closedList,$issueYear;
$issueList = array();
$issuePrev = array();
# default year is this fiscal year:
$issueYear = intval(date("y"))+1;
if (intval(date("m"))>9) $issueYear += 1;


class qaissue {
  var $ID;
  var $Name;
  var $Desc;
  var $firsttime;
  var $times;

  function qaissue($Nm,$De) {
    $this->firsttime = time();
    $this->Name = $Nm;
    $this->Desc = $De;
    $this->ID = 0;
    $this->SetLastTime();
  }

  function HasType($typ) { return (isset($this->times[$typ]) ? true : false); }  
  function LastTime($typ=".") { return $this->times[$typ]; }
  function SetLastTime() { $this->times["."] = time(); }

  function AsStr($tm) {
    if ($tm <= 1) { return "never"; }
    return date("H:i m/d/y T",$tm);
  }
  function First() { return $this->AsStr($this->firsttime); }
  function Last($typ=".") { return $this->AsStr(abs($this->times[$typ])); }

  # Can only add entry types this issue has been seen in.
  function InsureType($typ) {
    if ($this->HasType($typ)) { return; }
    (existsType($typ)) or died("Setting invalid type for issue.");
    $this->times[$typ] = 1;
  }

  function UsedForType($typ) {
    if ((!($this->HasType($typ))) || (abs($this->times[$typ]) <= 1)) { return false; }
    return true;
  }

  function ShortText() {
    return $this->Name;
  }

  function FullText() {
    $str  = "Issue ID: " . $this->ID . "\n";
    $str .= "Name: " . $this->Name . "\n";
    $str .= "First observed: " . $this->First() . "\n";
    $str .= "Last observed: " . $this->Last() . "\n";
    $str .= "Description:\n" . $this->Desc . "\n";
    return $str;
  }
  
  function Update($typ=".") {
    $this->SetLastTime();
    $this->times[$typ] = $this->LastTime();
    $this->Save();
  }
  
  function Save() {
    if ($this->ID == 0) {
      global $issueYear;
      $cnt = issIdFromYear($issueYear);
      $icntfile = getIssDir() . ".count";
      if ($obj = readInt($icntfile)) { $cnt = $obj; }
      $cnt++;
      saveObject($cnt,$icntfile);
      $this->ID = $cnt;
    }
    $file = getIssFile($this->ID);
    saveObject($this,$file);
    logit("Saved Issue: " . $this->ID);

    global $issueList;
    foreach ($this->times as $ty => $ti) {
      readIssList($ty,1);
      $issueList[strval($this->ID)] = array($this->Name, $ti);
      writeIssList($ty);
    }
  }
  
  function AddNote($note,$saveit=1) {
    $this->SetLastTime();
    $this->Desc .= "\n\n" . $this->Last() . " :\n" . $note;
    if ($saveit==1) { $this->Save(); }
  }

  # Closed issues will be indicated with all times set to be negative
  function IsClosed() {
    return ( $this->LastTime() < 0);
  }
  function Close($res) {
    if ($this->IsClosed()) { return; }
    $this->AddNote("ISSUE CLOSED! Resolution:\n" . $res,0);
    foreach ($this->times as $ty => $ti) {
      if ($ti == 0) { $ti = 1; }
      $this->times[$ty] = -1 * abs($ti);
    }
    logit("Closed Issue: " . $this->ID);
    $this->Save();
  }
  function ReOpen() {
    if (! $this->IsClosed()) { return; }
    foreach ($this->times as $ty => $ti) {
      $this->times[$ty] = abs($ti);
    }
    $this->AddNote("ISSUE RE-OPENED!");
    logit("Opened Issue: " . $this->ID);
    $this->Save();
  }

}

# Functions for issue directories and file names
function getIssWebLink($id) {
  global $webdir;
  return $webdir . "issueEditor.php?iid=${id}";
}
function getIssDir() {
  global $bdir,$issueYear;
  return $bdir . "issues${issueYear}/";
}
function getIssFile($id) { return getIssDir() . "${id}.data"; }
function getIssIndex($typ) {
  (($typ == ".") || (existsType($typ))) or died("Invalid issue type.");
  return getIssDir() . ".typ${typ}index";
}
function getIssIndexP($typ) { return getIssIndex($typ) . "P"; }
function getIssIndexL($typ) { return getIssIndex($typ) . "L"; }
function issIdFromYear($yr) { return 1000*intval($yr-5); }
function issYearFromId($id) {
  global $issueYear;
  return ($id < 1000 ? $issueYear : 5+intval($id/1000));
}

# Read in a specific issue from file
function readObjectIssue($file) { return readObjectClass($file,"qaissue"); }
function readIssue($id) { return readObjectIssue(getIssFile($id)); }

# Helper functions for the functions below
function readIssListFile($file) {
  if ($obj = readArray($file)) { return $obj; }
  return array();
}
function writeIssListFile($ilist,$file) {
  if (count($ilist) > 0) { saveObject($ilist,$file); }
  else { rmfile($file); }
}

# Read the issue list from the index files
# Will skip reading file if issueList already has contents,
# unless force != 0
function readIssList($typ=".",$force=0) {
  global $issueList, $issuePrev;
  if ((count($issueList) > 0) && ($force == 0)) { return; }
  $issueList = readIssListFile(getIssIndex($typ));
  if ($typ != ".") { $issuePrev = readIssListFile(getIssIndexP($typ)); }
}

# Write the issue list to index files
function writeIssList($typ) {
  global $issueList;
  writeIssListFile($issueList,getIssIndex($typ));
}

# Write the latest used issue list to an index file
function writeIssPrev($list,$typ) {
  if ($typ == ".") { return; }
  global $issuePrev;
  $issuePrev = $list;
  writeIssListFile($issuePrev,getIssIndexP($typ));
}


# Get list of issues matching:
# Type = $typ
# Age is less than $old (in days), or more than -$old
# Not in the issue list $exc
# $force mandates reading in of issue index from file (refresh)

$closedList = -1;

function getIssList($old,$typ,$exc,$force=0) {
  global $issueList, $issuePrev, $closedList;
  readIssList($typ,$force);
  $issueA = array();
  $issues = array();
  foreach ($issueList as $id => $idata) {
    # Check if looking for closed issues:
    $ltime = $idata[1];
    if ($ltime == 0) { $ltime = 1; }
    if ($closedList * $ltime > 0) { continue; }

    $ids = strval($id);

    if (isset($exc[$ids])) { continue; }
    if (($closedList < 0) && ($old == 0) &&
        (!isset($issuePrev[$ids]))) { continue; }

    $now = time();
    # floatval supported in PHP 4.2.0
    # 12/30/2004 - using PHP 4.1
    $daysold = $now - abs($ltime);
    settype($daysold, "double");   
    $daysold = $daysold / (60.0 * 60.0 * 24.0);
    if ($old <= 0) { $daysold *= -1.0; }
    if ($old >= $daysold) {
      $issueA[$ids] = abs($daysold);
      $issues[$ids] = $idata[0];
    }
  }
  # Sort by most recently used
  $issueF = array();
  arsort($issueA);
  foreach($issueA as $k => $v) { $issueF[$k] = $issues[$k]; }
  return $issueF;
}
function getClosedIssList($typ,$force=0) {
  global $closedList;
  $closedList = 1;
  $z = array();
  $z = getIssList(0,$typ,$z,$force);
  $closedList = -1;
  return $z;
}

# Re-write the issue index files from the actual issue files
function resetIssueIndices() {
  global $issueList, $ents;
  $issFiles = dirlist(getIssDir(),".data");
  sort($issFiles);
  $ents2 = $ents;
  $ents2["."] = "";
  foreach ($ents2 as $typ => $entT) {
    $issueList = array();
    foreach ($issFiles as $k => $issFile) {
      if (($issue = readObjectIssue(getIssDir() . $issFile)) &&
          ($issue->HasType($typ))) {
        $issueList[strval($issue->ID)] = array($issue->Name,$issue->LastTime($typ));
      }
    }
    writeIssList($typ);
  }
}

?>
