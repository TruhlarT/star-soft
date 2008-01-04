<?php

incl("db.php");

global $reportsDB,$rFSIDB,$repFODB,$repFO,$kFAST,$kOFFL;
$reportsDB = "QAShiftReports";
$rFSIDB = "QArunFileSeqIndex";

$kFAST = "FastOffline";
$kOFFL = "Offline";
$repFODB = array($kFAST => 0, $kOFFL => 1); # DB values
$repFO = array($kFAST,$kOFFL); # 0 => FastOffline, etc.

function cleanRepType(&$var) {
  # either Offline or FastOffline
  return (preg_match("/^(Fast)?Offline$/",$var,$temparr));
}


###############################
# Reports
#

function saveReportDB($RepNum,$RepType,$RepYear,$RepMonth,$RepText) {
  global $reportsDB,$repFODB;
  $encoded = escapeDB($RepText);
  if (!(cleanStrict($RepNum) && cleanInt($RepYear) &&
        cleanInt($RepMonth) && cleanRepType($RepType))) return false;
  $RepTypeDB = $repFODB[$RepType];
  $query = "INSERT INTO $reportsDB (RepNum,RepType,RepYear,RepMonth,RepText) VALUES "
         . "('$RepNum','$RepTypeDB','$RepYear','$RepMonth','$encoded');";
  queryDB($query);
}

function readReportDB($RepNum,$RepType,$next=0) {
  global $reportsDB,$repFODB;
  # next!=0 allows for next RepNum in case this one isn't found
  if (!(cleanStrict($RepNum) && cleanRepType($RepType))) return false;
  $RepTypeDB = $repFODB[$RepType];
  $query = "SELECT RepYear,RepMonth,RepText FROM $reportsDB WHERE RepType='$RepTypeDB' and RepNum";
  if ($next) $query .= ">";
  $query .= "='$RepNum' ORDER by RepNum ASC LIMIT 1;";
  return queryDBfirst($query);
}

function getReportYrMos($RepType) {
  global $reportsDB,$repFODB;
  if (!(cleanRepType($RepType))) return false;
  $str = "SELECT RepYear,RepMonth FROM $reportsDB WHERE RepType='" . $repFODB[$RepType]
       . "' GROUP by RepYear,RepMonth ORDER by RepYear DESC, RepMonth DESC;";
  return queryDB($str);
}

function getReportNums($RepType,$RepYear,$RepMonth) {
  global $reportsDB,$repFODB;
  if (!(cleanRepType($RepType) && cleanInt($RepYear) &&
        cleanInt($RepMonth))) return false;
  $str = "SELECT RepNum FROM $reportsDB WHERE RepType='" . $repFODB[$RepType]
       . "' and RepYear='$RepYear' and RepMonth='$RepMonth'"
       . " ORDER by RepNum DESC;";
  return queryDB($str);
}

function getNextRepNum($RepType) {
  global $reportsDB,$repFODB;
  if (!(cleanRepType($RepType))) return false;
  $str = "SELECT max(RepNum) FROM $reportsDB WHERE RepType='" . $repFODB[$RepType]
       . "' and RepNum between '0001' and '9999';";
  $row = queryDBfirst($str);
  return nDigits(4,intval($row['max(RepNum)'])+1);
}

############
# runFileSeqIndex

function saveLinkDB($RepType,$run,$seq,$link,$RepNum) {
  global $rFSIDB,$refFODB;
  if (!(cleanInt($run) && cleanRepType($RepType) &&
        cleanStrict($seq) && cleanStrict($RepNum))) return false;
  $RepTypeDB = $repFODB[$RepType];
  $runCnt = $run % 1000;
  $runDay = (($run - $runCnt) / 1000) % 1000;
  $runYear = ($run - $runCnt - ($runDay * 1000)) / 1000000;
  $query = "SELECT max(idx) FROM $rFSIDB WHERE runYear='$runYear' and $runDay='$runDay' and"
         . " run='$run' and seq='$seq' and RepType='$RepTypeDB';";
  $row = queryDBfirst($query);
  $idx = intval($row['max(idx)']) + 1;
  $encoded = escapeDB($link);
  $query = "INSERT INTO $rFSIDB (runYear,runDay,run,seq,idx,RepType,RepNum,link) VALUES ";
  $query .= "('$runYear','$runDay','$run','$seq','$idx','$RepTypeDB','$RepNum','$encoded');";
  queryDB($query);
}

function getLinksDB($runYear=-1,$runDay=-1,$run=-1) {
  if (!(cleanInt($runYear) && cleanInt($runDay) && cleanInt($run))) return false;
  global $rFSIDB;
  $xstr = "XXX"; $rstr = "runYear";
  $str = "SELECT ";
  if ($run < 0) $str .= $xstr;
  else $str .= "seq,RepType,idx,link,RepNum";
  $str .= " FROM $rFSIDB ";
  if ($runYear >0) {
    $str .= "WHERE runYear='$runYear' ";
    if ($runDay > 0) {
      $str .= "and runDay='$runDay' ";
      $rstr = "run";
    } else $rstr = "runDay";
    if ($run    > 0) $str .= "and run='$run' ";
  }
  if ($run < 0) $str .= "GROUP by $xstr ORDER by $xstr DESC;";
  else $str .= "ORDER by RepType,seq,idx ASC;";
  return queryDB(str_replace($xstr,$rstr,$str));
}

?>
