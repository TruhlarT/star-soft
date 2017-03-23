<?php
  
  incl("db.php");
  
  global $dbFOHistory,$fileInfo,$known_yr;
  $dbFOHistory = "fastOfflineHistory";
  $fileInfo = array();
  $known_yr = false;

  function stripDaq($file) {
    return preg_replace("/\.daq$/","",$file);
  }
  
  function assureDaq($file) {
    return $file . (preg_match("/\.daq$/",$file) ? "" : ".daq");
  }
  
  function getCurrentRunYear() {
    $year = date("y"); $month = date("m");
    $year += ($month >= 10 ? 1 : 0);
    return $year;
  }
  
  function getRunYearFromRun($runNumber) {
    $baseRun = 1274000; #Oct. 1, in non-leap-year (close enough?)
    $year = 0;
    while ($runNumber >= $baseRun) {
      $baseRun += 1000000;
      $year++;
    }
    return $year;    
  }
  
  function getInfoFromFilename($inputfile) {
    global $known_yr;
    $finfo = array('runNumber' => 0,
                   'ExecDate' => 0,
                   'EntryDate' => 0,
                   'DiskLoc' => 0,
                   'eDate' => "",
                   'year' => $known_yr,
                   'fstream' => "");
    if (strlen($inputfile)) {
      if (isRunNum($inputfile)) {
        $finfo['runNumber'] = $inputfile;
      } else {
        global $FOdb,$dbDAQInfo,$dbFOFileType;
        $year = ($known_yr === false ? getCurrentRunYear() : 2);
        $yr = ($known_yr === false ? "" : $known_yr);
        $ifile = assureDaq($inputfile);
        selectDB($FOdb);
        # loop over run years
        while ($year > 1 && $finfo['runNumber'] == 0) {
          $dbFTY = $dbFOFileType . $yr;
          $dbDIY = $dbDAQInfo . $yr;
          $proxyExec = ($year > 5 ? "" : "`EntryDate` AS "); # no ExecDate before Y6
          $qry = "SELECT `runNumber`,${proxyExec}`ExecDate`,"
          . "`EntryDate`,`DiskLoc`,`EntryDate`+0 AS `eDate`,"
          . "(SELECT `Label` FROM $dbFTY WHERE ${dbFTY}.`id` = ${dbDIY}.`ftype`) AS `fstream`"
          . " FROM $dbDIY WHERE `file`='${ifile}' ORDER BY `EntryDate` DESC LIMIT 1";
          $row = queryDBfirst($qry);
          if ($row === 0) {
            if (!($known_yr === false)) {
              # tried a known year and failed; try again without assumption
              $known_yr = false;
              $year = getCurrentRunYear();
              $yr = "";
            } else {
              # keep trying...
              $year--;
              $yr = "_Y${year}";
            }
          } else {
            $finfo = $row;
            $finfo['year'] = $yr;
            $known_yr = $yr; # Guess all files come from same run year
          }
        }
        selectDB();
      }
    }
    return $finfo;
  }
  
  function buildFileInfo($files) {
    global $fileInfo;
    if (count($fileInfo) == 0) {
      # do once to build up records of file info
      foreach ($files as $k => $file) {
        $fileInfo[stripDaq($file)] = getInfoFromFilename($file);
      }
    }
  }
  
  function getYTfromRun($runNumber) {
    global $FOdb,$dbDAQInfo,$dbFOTrig;
    $year = getRunYearFromRun($runNumber);
    $curYear = getCurrentRunYear();
    if ($year < 1) {
      return array('runYear' => $curYear,
                   'trig'    => "");
    }
    $yr = ($year >= $curYear ? "" : "_Y${year}");
    selectDB($FOdb);
    if (!existsDBtable($dbFOTrig . $yr)) {
      # fallback to current year if old year doesn't exist
      (existsDBtable($dbFOTrig)) or
        died("Problems (40).","$dbFOTrig $year $curYear");
      $yr = "";
    }
    $qry = "SELECT `Label` FROM ${dbFOTrig}${yr} WHERE `id`="
    . "(SELECT `TrgSetup` FROM ${dbDAQInfo}${yr} WHERE `runNumber`=${runNumber} LIMIT 1)";
    $row = queryDBfirst($qry);
    selectDB();
    return array('runYear' => $year,
                 'trig'    => $row['Label']);
  }

  function getTrigListAll($runYear) {
    global $FOdb,$dbDAQInfo,$dbFOTrig;
    $yr = ($runYear == getCurrentRunYear() ? "" : "_Y${runYear}");
    selectDB($FOdb);
    if (!existsDBtable($dbFOTrig . $yr)) {
      # fallback to current year if old year doesn't exist
      (existsDBtable($dbFOTrig)) or
        died("Problems (40).","$dbFOTrig $year $curYear");
      $yr = "";
    }
    $qry = "SELECT FO.`Label`,MAX(DI.`runNumber`) AS `maxrun` FROM ${dbDAQInfo}${yr}"
    . " AS DI JOIN ${dbFOTrig}${yr} AS FO ON DI.`TrgSetup`=FO.`id` WHERE"
    . " FO.`Label` LIKE \"%prod%\" AND FO.`Label` NOT LIKE \"%test%\""
    . " GROUP BY 1 ORDER BY 2 DESC";
    $result = queryDBarray($qry,"Label");
    selectDB();
    return $result;
  }
  
  function getLastExaminedRun() {
    global $dbFOHistory;
    $qry = "SELECT `file` FROM $dbFOHistory WHERE `updated`='Y' "
    . "ORDER BY `entryDate` DESC LIMIT 1";
    $row = queryDBfirst($qry);
    $finfo = getInfoFromFilename($row['file']);
    return $finfo['runNumber'];
  }

  function recordStatusForFiles($user,$files) {
    global $dbFOHistory,$rStatus,$fileInfo;
    if (count($files) < 1) {
      logit("Trying to record status for 0 files, user:${user}");
      return;
    }
    getPassedVarStrict("rStatus");
    $updated = ($rStatus === "bad" ? "B" : "N");
    buildFileInfo($files);
    $qryArray = array();
    foreach ($files as $k => $file) {
      $ifile = stripDaq($file);
      $diskLoc = $fileInfo[$ifile]['DiskLoc'];
      $eDate = $fileInfo[$ifile]['eDate'];
      $qryArray[] = "('${user}','${eDate}','${ifile}','${diskLoc}','${updated}')";
    }
    #$qry = "INSERT DELAYED INTO $dbFOHistory (`examiner`,`entryDate`,`file`,"
    $qry = "INSERT INTO $dbFOHistory (`examiner`,`entryDate`,`file`,"
      . "`DiskLoc`,`updated`) VALUES " . implode(",",$qryArray);
    queryDb($qry);
  }
  
  
?>
