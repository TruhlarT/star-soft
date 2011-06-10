<?php
  
  incl("db.php");
  incl("entrytypes.php");
  incl("files.php");
  
  global $dbCutsTable,$dbCutsCache,$cutModes,$defaultCutMode,$tts;
  $dbCutsTable = "QARefHistsCuts";
  $dbCutsCache = "QARefHistsCutsCache";
  $tts = false;

  $cutModes = array(0 => "Chi Square Probability",
                    1 => "Kolmogorov Probability",
                    2 => "Kolmogorov Max Distance");
  $defaultCutMode = 2;
  
  # Differentially by runYear and trig not fully implemented

  function getListOfCutsNames() {
    global $dbCutsTable;
    $qry = "SELECT `name` FROM $dbCutsTable GROUP BY 1";
    return queryDBarray($qry,"name");
  }

  function getLatestCutsTime($runYear=0,$trig="") {
    global $dbCutsTable;
    $qry = "SELECT unix_timestamp(entryTime) AS mtime"
    . " FROM $dbCutsTable ORDER BY entryTime DESC LIMIT 1";
    $row = queryDBfirst($qry);
    return ($row == 0 ? 0 : intval($row['mtime']));
  }

  function getLatestCutsID($runYear=0,$trig="") {
    global $dbCutsTable,$dbCutsCache;
    $mtime = getLatestCutsTime($runYear,$trig);
    if ($mtime == 0) return 0;
    
    $qry = "SELECT id,unix_timestamp(entryTime) AS mtime"
    . " FROM $dbCutsCache WHERE `runYear`=$runYear and `trig`='$trig'"
    . " ORDER BY entryTime DESC LIMIT 1";
    $row = queryDBfirst($qry);
    
    if ($row == 0 || $row['mtime'] < $mtime) {
      # Build a new cache entry for the cuts
      # Read from the DB
      logit("Building cuts from DB");
      
      $output = "";
      $names = getListOfCutsNames();
      foreach ($names as $k => $name) {
        $qry = "SELECT `mode`,`cut`,`opts` FROM $dbCutsTable WHERE `name`='$name' "
        . " ORDER BY `entryTime` DESC LIMIT 1";
        $row = queryDBfirst($qry);
        $mode = intval($row['mode']);
        $cut = floatval($row['cut']);
        $opts = $row['opts'];
        if (!($opts && strlen(opts))) { $opts = "!"; }
        $output .= "${name} ${mode} ${cut} ${opts} \r"; # works for file
      }
      $output = escapeDB($output);
      
      $qry = "INSERT INTO $dbCutsCache (`runYear`,`trig`,`cuts`)"
      . " VALUES ($runYear,'$trig','$output')";
      queryDB($qry);
      $id = getDBid();	

      # Not ready for this yet!!!
      # Keep only up to 10 cache files, good time to optimize

      optimizeCutsTable();
    } else {
      $id = $row['id'];
    }
    return $id;
  }

  function getCutsByID($id) {
    global $dbCutsCache;

    if ($id < 0) return array();

    $cutsDir = getWrkDir();
    $prefix = "QARefCuts_";
    
    $file = $cutsDir . $prefix . $id;
    $use_file = file_exists($file);
    if ($use_file) {
      $inputfull = readText($file);
    } else {
      logit("Grabbing cuts from DB cache: $id");
      $qry = "SELECT `cuts` FROM $dbCutsCache WHERE `id`='$id'";
      $row = queryDBfirst($qry);
      ($row != 0) or died("Cuts not found in cache with id=$id");
      $inputfull = $row['cuts'];
    }
    
    $data = array();
    $inputs = array();
    $tokens = "\r\n" . chr(10) . chr(13);
    $tok = strtok($inputfull,$tokens);
    $cnt = 0;
    while ($tok !== false) {
      $inputs[] = $tok;
      $tok = strtok($tokens);
      ($cnt++ < 4096) or died("Reading cuts cache not sane");
    }
    
    $output = "";
    $tokens = " \t";
    foreach ($inputs as $k => $input) {
      $name = strtok($input,$tokens);
      $tok = strtok($tokens);
      $mode = $tok;
      # Handle names with spaces
      while (!cleanInt($mode)) {
        $name .= " $tok";
        $tok = strtok($tokens);
        $mode = $tok;
      }
      $cut = strtok($tokens);
      $opts = strtok($tokens);
      if (!($opts && strlen(opts))) { $opts = "!"; }
      $output .= "${name} ${mode} ${cut} ${opts} \r";
      if ($opts == "!") { $opts = ""; }
      $data[$name] = array("mode" => $mode, "cut" => $cut, "opts" => $opts);
    }
    if (! $use_file) { // then create file
      saveText($output,$file); # cache file
      
      # Keep only up to 10 cache files, good time to optimize
      $flist = dirlist($cutsDir,$prefix); # returns oldest to newest
      $nflist = count($flist);
      if ($nflist > 10) {
        rmfile($cutsDir . $flist[0]);
      }
    }
    
    return $data;
  }
  
  function getCutForName($name,$cuts) {
    $prefix = "GE";
    $cutname = $name;
    if (!isset($cuts[$cutname])) {
      $cutname = stripHistPrefixes($name,1);
      if (!isset($cuts[$cutname])) {
        $cutname = stripHistPrefixes($name,0);
        if (!isset($cuts[$cutname])) { return 0; }
        $prefix = getTrigPrefix($name);
      }
    }
    return array("prefix" => $prefix, "name" => $cutname);
  }

  function uploadCut($name,$mode,$cut=0,$opts="",$runYear=0,$trigger="") {
    global $dbCutsTable;
    $name = escapeDB($name);
    $opts = escapeDB($opts);
    $runYear = escapeDB($runYear);
    $trigger = escapeDB($trigger);
    if ($cut == -999) {
      $qry = "DELETE FROM $dbCutsTable WHERE `name`='${name}'";
      # " AND `runYear`=${runYear} AND `trig`='${trigger}'";
    } else {
      $qry = "INSERT DELAYED INTO $dbCutsTable (`name`,`mode`,`cut`,`opts`,`runYear`,`trig`) " .
        "VALUES ('${name}','${mode}','${cut}','${opts}',${runYear},'${trigger}')";
    }
    queryDB($qry);
  }

  function optimizeCutsTable() { 
    global $dbCutsTable,$dbCutsCache;
    optimizeTable($dbCutsTable);
    optimizeTable($dbCutsCache);
  }


  function stripHistPrefixes($name,$mode=0,$prefix=false) {
    # mode =  1 : strip Tab/StE
    # mode = -1 : strip trig type
    # mode =  0 : both
    # mode =  1 && prefix : strip Tab/StE and use prefix

    # strip maker type prefixes
    $newname = ($mode >= 0 ? preg_replace("/^(Tab|StE)/","",$name) : $name);
    if ($mode <= 0 || $prefix) {
      global $tts;
      if ($tts === false) {
        global $trigs;
        $tts = implode("|",array_keys($trigs));
      }
      if ($prefix === false || !(existsTrigType($prefix)) ||
          $prefix == "NA" || $prefix == "GE") { $prefix = ""; }
      # replace whateever trig type prefix with this one
      $newname = preg_replace("/^(${tts})/",$prefix,$newname);
      $newname = preg_replace("/^Tab(${tts})/","Tab${prefix}",$newname);
      $newname = preg_replace("/^StE(${tts})/","StE${prefix}",$newname);
    }
    return preg_replace("/^ /","",$newname);;
  }

  function getTrigPrefix($name) {
    global $trigs;
    $newname = stripHistPrefixes($name,1);
    foreach ($trigs as $type => $v) {
      if (preg_match("/^${type}.+/",$newname)) { return $type; }
    }
    return "GE";
  }

?>
