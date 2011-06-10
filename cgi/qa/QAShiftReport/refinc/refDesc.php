<?php
  
  incl("db.php");
  
  global $dbDescTable;
  $dbDescTable = "QAHistDesc";

  function getEntryTimes($name) {
    global $dbDescTable;
    $qry = "SELECT `entryTime` FROM $dbDescTable WHERE `name`='${name}' ORDER BY 1 DESC";
    return queryDBarray($qry);
  }

  function getLatestDesc($name) {
    global $dbDescTable;

    # optimize the table every 100 queries
    srand(time());
    if (rand()%100 == 0) { optimizeDescTable(); }

    $qry = "SELECT `title`,`desc` FROM $dbDescTable WHERE"
    . " `name`='${name}' ORDER BY `entryTime` DESC LIMIT 1";
    return queryDBfirst($qry);
  }
  
  function uploadDesc($name,$title,$desc) {
    global $dbDescTable;
    $name = escapeDB($name);
    $title = escapeDB($title);
    $desc = escapeDB($desc);
    $qry = "INSERT DELAYED INTO $dbDescTable (`name`,`title`,`desc`) "
    . "VALUES ('${name}','${title}','${desc}')";
    queryDB($qry);
  }
  
  function optimizeDescTable() { 
    global $dbDescTable;
    optimizeTable($dbDescTable);
  }
  
  ?>