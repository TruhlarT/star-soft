<?php

global $QAdbhost,$QAdbname;
#$QAdbhost = "duvall.star.bnl.gov";
$QAdbhost = "db09.star.bnl.gov";
$QAdbname = "OfflineQA";

###############################
# DB Generic functions
#

function connectDB() {
  global $QAdbhost;
  if (connectedDB()) return;
  @($conn = mysql_connect($QAdbhost)) or died("Could not connect to the DB");
  setConnectedDB($conn);
  selectDB();
}
function selectDB($dbname="") {
  global $QAdbname;
  if (!strlen($dbname)) { $dbname = $QAdbname; }
  connectDB();
  mysql_select_db($dbname);
}
function closeDB() {
  global $QAdbconn;
  if (! connectedDB()) return;
  @(mysql_close($QAdbconn)) or died("Could not close DB connection");
  setUnconnectedDB();
}
function queryDB($str) {
  global $QAdebug,$QAdbconn;
  connectDB();
  if ($QAdebug) logit("QUERY###\n$str\n###QUERY");
  @($result = mysql_query($str,$QAdbconn)) or
    died("Could not query the DB: " . ($QAdebug ? mysql_error() : "please report"));
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
function optimizeTable($str) {
  $query = "ANALYZE TABLE $str;";
  queryDB($query);
  $query = "OPTIMIZE TABLE $str;";
  queryDB($query);
}


?>
