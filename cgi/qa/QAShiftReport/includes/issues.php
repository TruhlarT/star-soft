<?php

incl("db.php");
incl("entrytypes.php");
incl("preserve_wordwrap.php");

###############################
# Class and functions for Issue handling
#

# Issues are kept in a DB orgnaized by Run Year + 1
# (e.g. RHIC Run VIII starts with runs 8xxxxxx,
# but generally has runs 9xxxxxx, and its issues
# appear under run year 9).

global $issueList,$issuePrev,$issueYear,$issMinMax,$kPREV,$kLAST;
$issueList = array();
$issuePrev = array();
# default year is this fiscal year:
$issueYear = intval(date("y"))+1;
if (intval(date("m"))>9) $issueYear += 1;
$kPREV = 0;
$kLAST = 1;

global $IssuesDB,$RunIssuesDB;
$IssuesDB = "QAIssues";
$RunIssuesDB = "QArunIssueIndex";

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
  function LastTime($typ=QAnull) { return $this->times[$typ]; }
  function SetLastTime() { $this->times[QAnull] = time(); }
  
  function AsStr($tm) {
    if ($tm <= 1) { return "never"; }
    return date("H:i m/d/y T",$tm);
  }
  function First() { return $this->AsStr($this->firsttime); }
  function Last($typ=QAnull) { return $this->AsStr(abs($this->times[$typ])); }
  
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
  
  function Update($typ=QAnull) {
    $this->SetLastTime();
    $this->times[$typ] = $this->LastTime();
    $this->Save($typ);
  }
  
  function Save($makePrev=QAnull,$saveFirst=0) {
    global $IssuesDB;
    
    # Give it a new ID if it hasn't got one, and put it in the DB
    if ($this->ID == 0) {
      global $issueYear,$issMinMax;
      $cnt = issIdFromYear($issueYear);
      $row = queryDBfirst("SELECT max(ID) FROM $IssuesDB WHERE $issMinMax;");
      if ($row) $cnt = intval($row['max(ID)']);
      $cnt++;
      $this->ID = $cnt;
      queryDB("INSERT INTO $IssuesDB (ID) VALUES ('$cnt');");
    }
    
    # prepare for DB updating
    $nameForDB = escapeDB($this->Name);
    $descForDB = escapeDB($this->Desc);
    $str = "UPDATE $IssuesDB SET Name='$nameForDB',Description='$descForDB'";
    
    # Only when copying old ones?
    if ($saveFirst) {
      $str .= ",timeFirst=from_unixtime('" . $this->firsttime . "')";
      queryDB("INSERT INTO $IssuesDB (ID) VALUES ('" . $this->ID ."');");
    }
    
    foreach ($this->times as $ty => $ti) {
      $tp = ( $ty == QAnull ? "Last" : $ty );
      $str .= ",time$tp=" . abs($ti);
    }
    # Setting as a "previous" issue
    if ($makePrev != QAnull) {
      global $kPREV;
      $flag = flagFromTyp($makePrev); $comp = compFromBit($kPREV);
      $str .= ",$flag=$flag|$comp";
    }
    $str .= ",closed='" . ( $this->IsClosed() ? "1" : "0" );

    $str .= "' WHERE ID=" . $this->ID . " LIMIT 1;";
    queryDB($str);
    logit("Saved Issue to DB: " . $this->ID);
  }
  
  function Fill($issDB) {
    global $ents;
    $this->ID = $issDB['ID'];
    $this->Name = $issDB['Name'];
    $this->Desc = $issDB['Description'];
    $coef = (int) ( $issDB['closed'] ? -1 : 1 );
    # timeFirst is stored as a string in GMT; PHP needs to know it is in GMT
    $this->firsttime = strtotime($issDB['timeFirst'] . " GMT");
    $this->times[QAnull] = $coef * (int) ($issDB['timeLast']);
    foreach ($ents as $k=>$v) {
      $ti = (int) $issDB["time$k"];
      if ($ti>0) $this->times[$k] = $coef * $ti;
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

function setIssMinMax() {
  global $issueYear,$issMinMax;
  $minIss = issIdFromYear($issueYear);
  $maxIss = $minIss+999;
  $issMinMax = "ID BETWEEN $minIss and $maxIss";
}

# Functions for handling the run-issue index
function updateRunIssueIndex($runIssues) {
  if (count($runIssues)<1) return;
  $str = "INSERT INTO $RunIssuesDB (issueID,run) VALUES ";
  $more_than_one = 0;
  foreach ($runIssues as $id => $rlist) {
    foreach ($rlist as $run) {
      if ($more_than_one++>0) $str .= ",";
      $str .= "('$id','$run')";
    }
  }
  $str .= " ON DUPLICATE KEY UPDATE run=run;";
  queryDB($str);
}

function cleanRunIssueIndex() {
  global $RunIssuesDB;
  $str = "SELECT run FROM $RunIssuesDB GROUP BY run";
  $str .= " HAVING min(issueID)='0' and max(issueID)>'0';";
  $result = queryDB($str);
  $to_delete = 0;
  $str = "DELETE FROM $RunIssues WHERE issueID='0' and run in (";
  while ($row = nextDBrow($result)) {
    if ($to_delete++>0) $str .= ",";
    $str .= "'" . $row['run'] . "'";
  }
  if ($to_delete>0) queryDB($str . ");");
}

function getListOfRunsForIssue($id) {
  global $RunIssuesDB;
  $str = "SELECT run FROM $RunIssuesDB WHERE issueID='$id'";
  $str .= " ORDER BY run ASC;";
  $result = queryDB($str);
  $runs = array();
  while ($row = nextDBrow($result)) $runs[] = $row['run'];
  return $runs;
}

function getListOfRunsToggleIssue($id) {
  global $RunIssuesDB;
  $str = "SELECT run,bit_or(issueID='$id') FROM $RunIssuesDB";
  $str .= " GROUP BY run ORDER BY run ASC;";
  return queryDB($str);
}

# Functions for issue directories and file names
function getIssWebLink($id) {
  global $webdir;
  return $webdir . "issueEditor.php?iid=${id}";
}
function issIdFromYear($yr) { return 1000*intval($yr-5); }
function issYearFromId($id) {
  global $issueYear;
  return ($id < 1000 ? $issueYear : 5+intval($id/1000));
}

function readIssue($id,$full=1) {
  # if full=0, then just check if id is in the database
  global $IssuesDB,$ents;
  if (!(cleanInt($id))) return false;
  $str = "SELECT ID";
  if ($full) {
    $str .= ",closed,Name,Description,timeFirst,timeLast";
    foreach ($ents as $k=>$v) { $str .= ",time$k"; }
  }
  $str .= " FROM $IssuesDB WHERE ID='$id';";
  $result = queryDBfirst($str);
  if ($full && $result) {
    $iss = new qaissue("","");
    $iss->Fill($result);
    return $iss;
  }
  return $result;
}

# Helper functions for the functions below

# Read the issue list (and prev list) from the DB
# Will skip DB query if same type as previous query
function readIssList($typ=QAnull) {
  global $IssuesDB,$issMinMax,$issueList,$issuePrev,$kPREV,$kLAST;
  static $prevTyp = "none";
  if ($typ == $prevTyp) { return; }
  $prevTyp = $typ;
  $issueList = array();
  $issuePrev = array();
  $flag = "flags$typ";
  $typp = $typ;
  if ($typ == QAnull) { $typp = "Last"; $flag = 0; }
  #$typp = ( $typ == QAnull ? "Last" : $typ );
  $tstr = "time$typp";
  $str = "SELECT ID,Name,closed,$tstr,$flag FROM $IssuesDB WHERE $tstr>0 and $issMinMax;";
  $result = queryDB($str);
  while ($row = nextDBrow($result)) {
    $coef = (int) ( $row['closed'] ? -1 : 1 );
    $id = strval($row['ID']);
    $issueList[$id] = array($row['Name'],$coef * (intval($row[$tstr])));
    if ($typ != QAnull && testFlag($row[$flag],$kPREV))
      $issuePrev[] = strval($row['ID']);
  }
}


# Update previous flags to the latest used issue list
function flagFromTyp($typ) { return "flags$typ"; }
function compFromBit($bit) { return 1<<intval($bit); }
function clearIssPrev($typ) {
  global $kPREV;
  if ($typ != QAnull) clearIssFlag($typ,$kPREV);
}
function writeIssPrev($list,$typ) {
  global $kPREV;
  if ($typ != QAnull) writeIssFlag($list,$typ,$kPREV);
}
function writeIssLast($list,$typ) {
  global $kLAST;
  if ($typ != QAnull) writeIssFlag($list,$typ,$kLAST);
}

function clearIssFlag($typ,$bit) {
  global $IssuesDB,$issMinMax;
  $flag = flagFromTyp($typ); $comp = compFromBit($bit);
  $str = "UPDATE $IssuesDB SET $flag=$flag^$comp WHERE $issMinMax and $flag&$comp;";
  queryDB($str);
}

function writeIssFlag($list,$typ,$bit) {
  global $IssuesDB;
  $flag = flagFromTyp($typ); $comp = compFromBit($bit);
  clearIssFlag($typ,$bit);
  if (count($list)) {
    $str = "UPDATE $IssuesDB SET $flag=$flag|$comp WHERE ID in (";
    $k = 0;
    foreach ($list as $issid => $val) {
      if ($k) { $str .= ","; }
      else { $k = 1; }
      $str .= strval($issid);
    }
    $str .= ");";
    queryDB($str);
  }
}
function readIssLast($typ) {
  global $issMinMax,$IssuesDB,$kLAST;
  $flag = flagFromTyp($typ);
  $str = "SELECT ID,Name,$flag FROM $IssuesDB WHERE $issMinMax";
  $str .= " ORDER by ID ASC;";
  $result = queryDB($str);
  $list = array();
  while ($row = nextDBrow($result)) {
    $flagval = $row[$flag];
    if (testFlag($flagval,$kLAST)) {
      $iddigits = (intval($row['ID'])>9999 ? 5 : 4);
      $list[nDigits($iddigits,$row['ID'])] = $row['Name'];
    }
  }
  return $list;
}  
function testFlag($flagval,$bit) {
  $comp = compFromBit($bit);
  return (intval($flagval) & $comp);
}

# Get list of issues matching:
# Type = $typ
# Age is less than $old (in days), or more than -$old
# Not in the issue list $exc
# $old = 0 asks for previous issues
# $closed = 1 asks for closed issues


function getIssList($old,$typ,$exc,$closed=-1) {
  global $issueList,$issuePrev;
  readIssList($typ);
  $issueA = array();
  $issues = array();
  foreach ($issueList as $id => $idata) {
    # Check if looking for closed issues:
    $ltime = $idata[1];
    if ($ltime == 0) { $ltime = 1; }
    if ($closed * $ltime > 0) { continue; }
    
    $ids = strval($id);
    
    if (isset($exc[$ids])) { continue; }
    if (($closed < 0) && ($old == 0) &&
	(!in_array($ids,$issuePrev))) { continue; }
    
    $daysold = floatval(time() - abs($ltime)) / (60.0 * 60.0 * 24.0);
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

function optimizeIssuesDB() {
  global $IssuesDB,$RunIssuesDB;
  optimizeTable($IssuesDB);
  cleanRunIssueIndex();
  optimizeTable($RunIssuesDB);
} 


# depracated, but needed for coping
function getIssDir() {
  global $bdir,$issueYear;
  return $bdir . "issues${issueYear}/";
}
function getIssFile($id) { return getIssDir() . "${id}.data"; }
function getIssIndex($typ) {
  (($typ == QAnull) || (existsType($typ))) or died("Invalid issue type.");
  return getIssDir() . ".typ${typ}index";
}
function getIssIndexP($typ) { return getIssIndex($typ) . "P"; }
function getIssIndexL($typ) { return getIssIndex($typ) . "L"; }
# Read in a specific issue from file
function readObjectIssue($file) { return readObjectClass($file,"qaissue"); }
# Write the issue list to index files
function readIssListFile($file) {
  #depracated
  if ($obj = readArray($file)) { return $obj; }
  return array();
}



function fillDBIssuesFromFiles() {
  global $ents,$issueYear;
  $tempIY = $issueYear;
  while ($issueYear>5) {
    $issFiles = dirlist(getIssDir(),".data");
    if (!count($issFiles)) continue;
    sort($issFiles);
    foreach ($issFiles as $k => $issFile) {
      if ($issue = readObjectIssue(getIssDir() . $issFile)) $issue->Save(QAnull,1);
    }
    foreach ($ents as $typ => $entT) {
      writeIssPrev(readIssListFile(getIssIndexP($typ)),$typ);
      writeIssLast(readIssListFile(getIssIndexL($typ)),$typ);
    }
    $issueYear--;
  }
  $issueYear = $tempIY;
}

setIssMinMax();

?>
