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
                   'year' => $known_yr);
    if (strlen($inputfile)) {
      if (isRunNum($inputfile)) {
        $finfo['runNumber'] = $inputfile;
      } else {
        global $FOdb,$dbDAQInfo;
        $year = ($known_yr === false ? getCurrentRunYear() : 2);
        $yr = ($known_yr === false ? "" : $known_yr);
        $ifile = assureDaq($inputfile);
        selectDB($FOdb);
        # loop over run years
        while ($year > 1 && $finfo['runNumber'] == 0) {
          $qry = "SELECT `runNumber`,`ExecDate`,`EntryDate`,`DiskLoc`,`EntryDate`+0 as eDate"
          . " FROM ${dbDAQInfo}${yr} WHERE `file`='${ifile}' ORDER BY `EntryDate` DESC LIMIT 1";
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
    $qry = "SELECT `Label`,(SELECT `runNumber` FROM ${dbDAQInfo}${yr} WHERE "
    . "${dbDAQInfo}${yr}.TrgSetup=${dbFOTrig}${yr}.id ORDER BY `runNumber` DESC LIMIT 1)"
    . " AS maxrun FROM ${dbFOTrig}${yr} WHERE `Label` LIKE \"%prod%\" "
    . "AND `Label` NOT LIKE \"%test%\" ORDER BY maxrun DESC";
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
    getPassedVarStrict("rStatus");
    $updated = ($rStatus === "bad" ? "B" : "N");
    buildFileInfo($files);
    foreach ($files as $k => $file) {
      $ifile = stripDaq($file);
      $diskLoc = $fileInfo[$ifile]['DiskLoc'];
      $eDate = $fileInfo[$ifile]['eDate'];
      $qry = "INSERT DELAYED INTO $dbFOHistory (`examiner`,`entryDate`,`file`,`DiskLoc`,`updated`)"
      . " VALUES ('${user}','${eDate}','${ifile}','${diskLoc}','${updated}')";
      queryDb($qry);
    }
  }
  
  
?>