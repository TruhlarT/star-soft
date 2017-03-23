<?php

global $QAdbhost,$QAdbname;
$QAdbhost = "duvall.star.bnl.gov";
#$QAdbhost = "db09.star.bnl.gov";
$QAdbname = "OfflineQA";

###############################
# DB Generic functions
#

function connectDB($user1="starweb",$user2="") {
  global $QAdbhost;
  if (connectedDB()) return;
  @($conn = mysql_connect($QAdbhost,$user1,$user2)) or died("Could not connect to the DB, please report",dbErrMess());
  setConnectedDB($conn);
  selectDB();
}
function selectDB($dbname="") {
  global $QAdbname;
  if (!strlen($dbname)) { $dbname = $QAdbname; }
  connectDB();
  @(mysql_select_db($dbname)) or died("Could not select DB, please report",dbErrMess());
}
function closeDB() {
  global $QAdbconn;
  if (! connectedDB()) return;
  @(mysql_close($QAdbconn)) or died("Could not close DB connection",dbErrMess());
  setUnconnectedDB();
}
function queryDB($str) {
  global $QAdebug,$QAdbconn;
  connectDB();
  if ($QAdebug) {
    if (strlen($str)<2050) logit("QUERY###\n$str\n###QUERY");
    else logit("QUERY### long one ###QUERY");
  }
  $tt = time();
  @($result = mysql_query($str,$QAdbconn)) or
    died("Could not query the DB, please report",dbErrMess());
  if ($QAdebug && strlen($str)<2050)
    logit("2QUERY###\n" . preg_replace("/\),\(/","),\n(",$str) .
      "\n###QUERY TOOK : " . (time() - $tt) . " seconds");
  return $result;
}
function nextDBrow($result) {
  return mysql_fetch_assoc($result);
}
function numDBrows($result) {
  return mysql_num_rows($result);
}
function queryDBfirst($str) {
  # returns the first such row from the DB
  $result = queryDB($str);
  if (mysql_num_rows($result)<1) return 0;
  return nextDBrow($result);
}
function queryDBarray($str,$col) {
  # returns an array of column $col from the DB
  $result = queryDB($str);
  $list = array();
  while ($row = nextDBrow($result)) { $list[] = $row["$col"]; }
  return $list;
}
function escapeDB($str) {
  if (get_magic_quotes_gpc()) { $str = stripslashes($str); }
  connectDB();
  return mysql_real_escape_string($str);
}
function getDBid() {
  return mysql_insert_id();
}
function existsDBtable($table) {
  return (queryDBfirst("SHOW TABLES LIKE '${table}'") !== 0);
}
function optimizeTable($str) {
  $query = "ANALYZE TABLE $str;";
  queryDB($query);
  $query = "OPTIMIZE TABLE $str;";
  queryDB($query);
}


#-------------------
# For temp connections to other DBs

$TMPdbhost = QAnull;
$TMPdbname = QAnull;
$TMPdbconn = QAnull;

function startDbTemp($tempHost,$tempName,$tempUser1="",$tempUser2="") {
  global $QAdbhost,$QAdbconn,$QAdbname;
  global $TMPdbhost,$TMPdbconn,$TMPdbname;

  $TMPdbhost = $QAdbhost;
  $TMPdbname = $QAdbname;
  $TMPdbconn = $QAdbconn;
  $QAdbhost = $tempHost;
  $QAdbname = $tempName;
  $QAdbconn = QAnull;
  connectDB($tempUser1,$tempUser2);
}

function stopDbTemp() {
  global $QAdbhost,$QAdbconn,$QAdbname;
  global $TMPdbhost,$TMPdbconn,$TMPdbname;

  closeDB();
  $QAdbhost = $TMPdbhost;
  $QAdbname = $TMPdbname;
  $QAdbconn = $TMPdbconn;
}

function dbErrMess() {
  if (connectedDB()) {
    global $QAdbconn;
    $dbErrNumb = mysql_errno($QAdbconn);
    $dbErrMess = mysql_error($QAdbconn);
  } else {
    $dbErrNumb = mysql_errno();
    $dbErrMess = mysql_error();
  }
  return "DB error # = ${dbErrNumb}, message = ${dbErrMess}";
}


?>
