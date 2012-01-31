<?php
  
  incl("db.php");
  inclR("refRunFileInfo.php");
  
  global $dbResultsTable,$maxCell;
  $dbResultsTable = "QARefHistResults";
  $maxCell = 1;

  function optimizeResultsTable() { 
    global $dbResultsTable;
    optimizeTable($dbResultsTable);
  }

  function getResults($file,$mode) {
    global $maxCell;
    # mode = 0 : by name
    # mode = 1 : by location
    $data = array();
    $resfile = (strstr($file,"/") === false ? getWrkDir() : "") . $file;
    $inputfull = readText($resfile);
    $inputs = array();
    $tokens = "\n";
    $tok = strtok($inputfull,$tokens);
    $cnt = 0;
    while ($tok !== false) {
      $inputs[] = $tok;
      $tok = strtok($tokens);
      ($cnt++ < 4096) or died("Reading results file not sane");
    }

    $tokens = " \t";
    foreach ($inputs as $k => $input) {
      $page = strtok($input,$tokens);
      $cell = strtok($tokens);
      $name = strtok($tokens);
      $ttyp = getTrigPrefix($name);
      $tok = strtok($tokens);
      $resu = $tok;
      # Handle names with spaces
      while (!cleanFloat($resu)) {
        $name .= " $tok";
        $tok = strtok($tokens);
        $resu = $tok;
      }
      if ($mode == 0) {
        $data[$name] = array("type" => $ttyp, "page" => $page, "cell" => $cell, "result" => $resu);
      } else {
        if (!isset($data[$ttyp])) { $data[$ttyp] = array(); }
        if (!isset($data[$ttyp][$page])) { $data[$ttyp][$page] = array(); }
        $data[$ttyp][$page][$cell] = array("name" => $name, "result" => $resu);
      }
      if ($cell > $maxCell) { $maxCell = $cell; }
    }
    if ($mode != 0) { sortTrigType($data); }
    return $data;
  }

  function getResultsByName($file) { return getResults($file,0); }
  function getResultsByLoc($file) { return getResults($file,1); }
  
  function recordResults($user,$name,$analRes,$refId,$cut,$file) {
    global $dbResultsTable,$fileInfo;
    $ifile = stripDaq($file);
    $runNumber = $fileInfo[$ifile]['runNumber'];
    $procTime = $fileInfo[$ifile]['ExecDate'];
    $seenTime = $fileInfo[$ifile]['EntryDate'];
    $qry = "INSERT DELAYED INTO $dbResultsTable (`name`,`result`,`refId`,`cut`,"
    . "`runNumber`,`procTime`,`seenTime`,`file`,`user`)"
    . " VALUES ('${name}','${analRes}','${refId}','${cut}',"
    . "'${runNumber}','${procTime}','${seenTime}','${ifile}','${user}')";
    queryDB($qry);
  }
  
  function recordResultsForFiles($user,$name,$analRes,$refId,$cut,$files) {
    buildFileInfo($files);
    foreach ($files as $k => $file) {
      recordResults($user,$name,$analRes,$refId,$cut,$file);
    }
    if (rand(1,1000)==2) { optimizeResultsTable(); } # Slow on big table
  }
  
  function getRecordedResults($name,$idx,$min=false,$max=false) {
    global $dbResultsTable;
    # Only obtain results since the last October 1st
    $qry = "SELECT `result`,`refId`,`cut`,`runNumber`"
    . ",UNIX_TIMESTAMP(`entryTime`) AS eTime,DATE_FORMAT(`entryTime`,\"%Y-%m-%d\") AS enTime"
    . ",UNIX_TIMESTAMP(`procTime`) AS pTime,DATE_FORMAT(`procTime`,\"%Y-%m-%d\") AS prTime"
    . ",UNIX_TIMESTAMP(`seenTime`) AS sTime,DATE_FORMAT(`seenTime`,\"%Y-%m-%d\") AS seTime"
    #. " FROM $dbResultsTable WHERE `name`='${name}' AND FLOOR(YEAR(NOW())+QUARTER(NOW())/4)="
    #. "FLOOR(YEAR(entryTime)+QUARTER(entryTime)/4) ORDER BY `${idx}` ASC";
    . " FROM $dbResultsTable WHERE `name`='${name}' AND "
    #    . "entryTime>\"2011-03-15\" ORDER BY `${idx}` ASC";
    . "entryTime>\"2011-04-03\""
    . " GROUP BY `runNumber`,`cut`,`refId`,`result`";
    if ($min || $max) {
      $qry .= " HAVING";
      if ($min !== false) { $qry .= " ${idx}>=${min}"; }
      if ($max !== false) { 
        if ($min !== false) {$qry .= " AND"; }
        $qry .= " ${idx}<=${max}";
      }
    }
    $qry .= " ORDER BY `${idx}` ASC";
    return queryDB($qry);
  }


?>