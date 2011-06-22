<?php
  
  incl("db.php");
  inclR("refAutoComb.php");
  
  global $dbProcTable,$dbCombTable,$dbCombFileTable,
         $stdFilePath,$useRuns,$SLEEP,$MAXCOUNT;
  $dbProcTable = "hist2ps";
  $dbCombTable = "combineFiles";
  $dbCombFileTable = "combineFileList";
  $stdFilePath = "/star/u/starqa/QA/files";
  $useRuns = array();
  $SLEEP = 3;
  $MAXCOUNT = 100;
  
  function runLogLink() {
    global $useRuns,$myCols;
    $nruns = count($useRuns);
    $str = "You have selected " . ($nruns < 1 ? "no " : "")
    . "run" . ($nruns != 1 ? "s" : "") . " ";
    $hrStart = "<a href=\"http://online.star.bnl.gov/";
    $spStart = "<span style=\"background-color:";
    $srStart = $spStart . $myCols["good"] . "\">${hrStart}RunLog/index.php?r=";
    $seStart = $spStart . $myCols["emph"] . "\">${hrStart}apps/shiftLog/logForFullTextSearch.jsp?text=";
    $hrEnd = "\" target=\"new\">";
    $hsEnd = "</a></span>";
    if (count($useRuns) > 1) {
      foreach ($useRuns as $k => $run) {
        if ($k > 0) { $str .= ", "; }
        $str .= "${run}<font size=-2><i>[${srStart}${run}${hrEnd}RL${hsEnd},"
        . "${seStart}${run}${hrEnd}ESL${hsEnd}]</i></font>";
      }
    } else {
      $run = $useRuns[0];
      $str .= "${run} <i>[${srStart}${run}${hrEnd}RunLog${hsEnd}, "
      . "${seStart}${run}${hrEnd}ElectronicShiftLog${hsEnd}]</i>";
    }
    return $str;
  }


  function diskLocByFile($file) {
    global $dbFOLoc,$dbDAQInfo;
    $qry = "SELECT `Label` from $dbFOLoc where `id` = "
    . "(SELECT `DiskLoc` FROM $dbDAQInfo WHERE `file`=\"${file}.daq\" LIMIT 1)";
    $row = queryDBfirst($qry);
    if ($row == 0) { return false; }
    return $row['Label'];
  }

  function diskLocById($id) {
    global $dbFOLoc;
    $qry = "SELECT `Label` from $dbFOLoc where `id` = '${id}'";
    $row = queryDBfirst($qry);
    if ($row == 0) { return false; }
    return $row['Label'];
  }
  
  function refProcRequest($reffileID,$refcutsID,$forCache=false) {
    global $FOdb,$dbProcTable,$whichHist,$user,$format,$QARefCache,
           $inputfile,$combID,$stdFilePath,$autoFilePath;
    $path = $stdFilePath;
    $detectors = "NULL";
    $frmt = 2; // none
    $infile = "";
    $whichHist = "all";
    $user1 = $QARefCache;
    if (! $forCache) {
      $user1 = $user;
      if ($format == "pdf") { $frmt = 1; }
      elseif ($format == "none") { $frmt = 2; }
      else { $frmt = 0; }
      getPassedVarStrict("whichHist");
      $infile = $inputfile;
      if (strlen($infile)) {         # ! reference only
        if ($combID < 0) {           # ! combining
          if (isAutoTag($infile)) {  # AutoCombined
            $infile .= "_comb";
            $path = $autoFilePath;
          } else {                   # single file
            selectDB($FOdb);
            $path = diskLocByFile($infile);
            selectDB();
            if ($path === false) { return -1; }
          }
        }
        $infile .= ".hist.root";
        if (substr($whichHist,0,3) == "det") {
          $detectors = substr($whichHist,3);
          $whichHist = "reg";
        } else {
          $detectors = implode(",",getDetList());
        }
        $detectors = "'${detectors}'";
      }
    }
    $qry = "INSERT INTO $dbProcTable (`done`,`user`,`path`,`fName`,"
    . "`whichHist`,`format`,`refFile`,`refCuts`,`detectors`) "
    . " VALUES ('N','${user1}','${path}','${infile}',"
    . "'${whichHist}','${frmt}','${reffileID}','${refcutsID}',${detectors})";
    queryDB($qry);
    return getDBid(); # grabs auto-incremented id
  }

  global $months;
  $months = array(
	     'Jan' => 1,
	     'Feb' => 2,
	     'Mar' => 3,
	     'Apr' => 4,
	     'May' => 5,
	     'Jun' => 6,
	     'Jul' => 7,
	     'Aug' => 8,
	     'Sep' => 9,
	     'Oct' => 10,
	     'Nov' => 11,
	     'Dec' => 12,
	     );
  function dateChecker($var,$min,$max,&$status) {
    global $months,$$var;
    if (substr($var,0,5) == "month") {
      getPassedVarStrict($var);
      if (array_key_exists($$var,$months)) {
        $$var = $months[$$var];
      } else {	$status = -77; }
    } else {
      getPassedInt($var);
    }
    if ($$var < $min || $$var > $max) { $status = -78; }
    if ($status < 0) { return "FATAL ERROR: $var == " . $$var . "<br>\n"; }
    return "";
  }
    
  function combProcRequest(&$combID,&$status) {
    global $textUserName,$FOdb,$dbCombTable,$dbCombFileTable,$dbDAQInfo;
    global $month1,$day1,$year1,$month2,$day2,$year2,$useRuns;
    $combID = rand(1,65535); # seed is now done automatically in PHP
    $str = "";
    
    #streams = array("jpsi","mtd","upsilon","minbias","gamma","physics");
    $stream = ""; # default stream is any
    
    # determine passed run numbers
    $MAX_RUNS = 32;
    foreach ($_GET as $k => $v) {
      if ((substr($k,0,6) === "useRun") && cleanInt(substr($k,6))) {
        $vals = explode(' ',$v); # delimeter is space
        if (count($vals) == 2 && isRunNum($vals[0]) && cleanStrict($vals[1])) {
          if (strlen($stream)) {
            if ($vals[1] != $stream) {
              $str .= "<b>WARNING: combine request for multiple streams; ignoring run "
              . $vals[0] . ", st_" . $vals[1] . "* stream</b><br>\n";
              continue;
            }
          } else {
            $stream = $vals[1]; # for now, only first stream is selected
          }
          $useRuns[] = $vals[0];
          if (count($useRuns) >= $MAX_RUNS) {
            $str .= "<br>Warning, maximum number of runs (${MAX_RUNS}) reached,"
                .  " ignoring the rest...<br>\n";
            break;
          }
        }
      }
    }
    if (count($useRuns) == 0) {
      $str .= "<br>No runs chosen.<br>\n";
      $status = -79;
    } else {
      $runList = implode(",",$useRuns);
      $str .= runLogLink() . "<br>\n";
      $str .= dateChecker("month1",1,12,$status);
      $str .= dateChecker("day1",1,31,$status);
      $str .= dateChecker("year1",1998,2040,$status);
      $str .= dateChecker("month2",($year2 == $year1 ? $month1 : 1),12,$status);
      $str .= dateChecker("day2",($year2 == $year1 && $month2 == $month1 ? $month1 : 1),31,$status);
      $str .= dateChecker("year2",$year1,2040,$status);
      if ($status < 0) { return $str; }
      $qry = "SELECT `file`,`DiskLoc` FROM $dbDAQInfo WHERE `runNumber` IN"
      . " (${runList}) AND `Status` > 1 and `Status` < 4 and `DiskLoc` > 0"
      . " AND `file` LIKE 'st_${stream}%'"
      . " AND `UpdateDate` >= " . sprintf("\"%d-%02d-%02d 00:00:00\"",$year1,$month1,$day1)
      . " AND `UpdateDate` <= " . sprintf("\"%d-%02d-%02d 23:59:59\"",$year2,$month2,$day2)
      . " LIMIT 100";
      
      # Should I limit the query length? 380 char limit in qa.c
      
      # Obtain and verify file locations
      selectDB($FOdb);
      $result = queryDB($qry);
      $listOfFiles = array();
      while ($row = nextDBrow($result)) {
        $path = diskLocById($row['DiskLoc']);
        if ($path !== false) {
          $file = str_replace(".daq",".hist.root",$row['file']);
          $listOfFiles[] = $path . "/" . $file;
        }
      }

      # Push the request into the DB
      selectDB();
      $nfiles = count($listOfFiles);
      if ($nfiles==0) {
        $status = -76;
      } else {
        $str .= "<br>Combinining $nfiles files:\n<pre>";
        foreach ($listOfFiles as $k => $file) {
          $qry = "INSERT INTO $dbCombFileTable (`id`,`file`)"
          . " VALUES ($combID,'${file}')";
          queryDB($qry);
          $str .= " ${file}\n";
        }
        $str .= "</pre>\n";
        $qry = "INSERT INTO $dbCombTable (`done`,`id`,`user`,`whichHist`,`format`)"
        . " VALUES ('N',$combID,'${textUserName}','none','0')";
        queryDB($qry);
      }
    }
    return $str;
  }
  
  function mergeProcRequest($user,$whichDir,$marks) {
    # merge two reference histogram sets
    global $dbCombTable,$dbCombFileTable;
    $id = rand(0,65535);
    # make entry in DB for daemon.c to process
    $tokens = "\n";
    $tok = strtok($marks,$tokens);
    while ($tok !== false) {
      if (cleanStrict($tok)) {
        $qry = "INSERT INTO $dbCombFileTable (`id`,`file`) VALUES (${id},'${tok}');";
        queryDB($qry);
      }
      $tok = strtok($tokens);
    }
    $qry = "INSERT INTO $dbCombTable (`id`,`user`,`whichHist`,`done`,`format`)"
    . " VALUES (${id},'${user}','${whichDir}','N',4)";
    queryDB($qry);
    return $id;
  }
                            
  function refProcPoll($id) {
    global $dbProcTable;
    $qry = "SELECT `done`,`anticache`,`refFile`,`refCuts` FROM $dbProcTable WHERE `id`=${id}";
    return queryDBfirst($qry);
  }
  
  function combProcPoll($id) {
    global $dbCombTable;
    $qry = "SELECT `done` FROM $dbCombTable WHERE `id`=${id} ORDER BY `timeOfRequest` DESC LIMIT 1";
    return queryDBfirst($qry);
  }
  
  function waitForProc($comb,$id,$stat1,$stat2,$stat3=-1) {
    global $MAXCOUNT,$SLEEP;
    logit("Waiting on process request $id (${comb})");
    $status = $stat1; # timed out (too many iterations)
    $notdone = 1;
    for ($cnt=0; $cnt < $MAXCOUNT && $notdone; $cnt++) {
      sleep($SLEEP);
      $results = ($comb > 0 ? combProcPoll($id) : refProcPoll($id));
      switch ($results['done']) {
        case "P" : $status = $stat3; $notdone = 0; break;
	    case "E" : $status = $stat2; $notdone = 0; break;
	    case "Y" : $status = 1; $notdone = 0; break; # all went well
          # default case is "N"...keep looping
      }
    }
    logit("Process request completed with status = ${status} after waiting "
          . $SLEEP*$cnt . " sec");
    return array($status,$results);
  }
  
  function getAutoCombStr($autoID) {
    # Assemble a string to print info about an AutoCombine jobs
    global $useRuns;
    $info = getAutoCombInfo($autoID);
    $useRuns[] = $info[0];
    return runLogLink() . ", using "
    . intval($info[1]) . " <i>" . $info[2] . "*</i> files.\n";
  }

  function getDetList($useRunsStr="") {
    # Get the list of detectors which were in the run
    global $FOdb,$dbFODets,$dbDAQInfo,$useRuns;
    if (strlen($useRunsStr)) { $useRuns = $useRunsStr; }
    else { getPassedVarStrict("useRuns"); }
    $runList = preg_replace("/_/",",",$useRuns);
    selectDB($FOdb);
    $qry = "SELECT Label FROM $dbFODets AS FOD WHERE"
    . " ((SELECT BIT_OR(DetSetMask) FROM $dbDAQInfo"
    . " WHERE runNumber IN (${runList}) GROUP BY 1=1)>>FOD.id)&1=1";
    $detLabels = queryDBarray($qry,"Label");
    selectDB();
    return $detLabels;
  }
  
  
?>