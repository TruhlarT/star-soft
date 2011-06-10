<?php
  
  incl("db.php");
  inclR("refMarks.php");
  inclR("requestHandling.php");
  
  global $dbRefSetTable,$dbDataTable;
  $dbRefSetTable = "QARefHists";
  $dbDataTable = "QARefHistsData";
  
  function fromWhereYTV($runYear=0,$trig="",$vers=0) {
    global $dbRefSetTable;
    $str = "FROM $dbRefSetTable";
    if ($runYear>0) {
      $str .= " WHERE `runYear`=${runYear}";
      if (strlen($trig)>0) {
        $str .= " AND `trig`='${trig}'";
        if ($vers>0) {
          $str .= " AND `vers`=${vers}";
        }
      }
    }
    return $str;
  }

  function getRunYearList() {
    $qry = "SELECT `runYear` " . fromWhereYTV() . " GROUP BY 1 ORDER BY 1 DESC";
    return queryDBarray($qry,"runYear");
  }
  
  function getTrigList($runYear) {
    $qry = "SELECT `trig` " . fromWhereYTV($runYear) . " GROUP BY 1 ORDER BY 1 ASC";
    return queryDBarray($qry,"trig");
  }
  
  function getVersList($runYear,$trig) {
    $qry = "SELECT `vers`,`id`,`entryTime` " . fromWhereYTV($runYear,$trig) . " ORDER BY 1 DESC";
    $res = queryDB($qry);
    $vers = array();
    while ($row = nextDBrow($res)) {
      $vers[$row['vers']] = array("id" => $row['id'],
                                  "entryTime" => $row['entryTime']);
    }
    return $vers;
  }
  
  function getNextVers($runYear,$trig) {
    $vers = getVersList($runYear,$trig);
    if (count($vers)>0) {
      $keys = array_keys($vers);
      return $keys[0] + 1; # already in descending order
    }
    return 1;
  }

  function getIdForVers($runYear,$trig,$vers) {
    $qry = "SELECT `id` " . fromWhereYTV($runYear,$trig,$vers);
    $row = queryDBfirst($qry);
    return $row['id'];
  }
  
  function getFilename($runYear=0,$trig="",$vers=0) {
    $str = getWrkDir();
    if ($runYear>0) {
      $str .= "Run${runYear}/${trig}/QAref_${runYear}_${trig}_${vers}.hist.root";
    } else {
      $str .= "QAref_temp.hist.root";
    }
    return $str;
  }
  
  function getFile($runYear,$trig,$vers) {
    $file = getFilename($runYear,$trig,$vers);
    if (! file_exists($file)) {
      ckdir(dirname($file));
      if (!(readDbToFile(getIdForVers($runYear,$trig,$vers),$file))) { return 0; }
    }
    return $file;
  }
  
  function getFileById($id) {
    $info = getInfoById($id);
    $file = getFilename($info['runYear'],$info['trig'],$info['vers']);
    if (! file_exists($file)) {
      ckdir(dirname($file));
      if (!(readDbToFile($id,$file))) { return 0; }
    }
    return $file;
  }
    
  # Not useful?
  function getComment($runYear,$trig,$vers) {
    $qry = "SELECT `comments` " . fromWhereYTV($runYear,$trig,$vers);
    $row = queryDBfirst($qry);
    return $row['comments'];
  }
  
  function getInfoById($id) {
    global $dbRefSetTable;
    $qry = "SELECT `runYear`,`trig`,`vers`,`entryTime`,`user`,`comments` FROM $dbRefSetTable WHERE `id`=$id";
    return queryDBfirst($qry);
  }
  
  function readDbToFile($id,$file) {
    global $dbDataTable;
    #cleanSpace();  # maintain disk space
    $qry = "SELECT `data` FROM $dbDataTable WHERE `id`=${id} ORDER BY `segment` ASC";
    $res = queryDB($qry);

    # write file segment-by-segment
    @($fp = fopen($file,"wb")) or died("Problems (24).");
    flock($fp,LOCK_EX);
    while ($row = nextDBrow($res)) {
      @(fwrite($fp,$row['data'])) or died("Problems (25).");
    }
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems (26).");

    return filesize($file);
  }
  
  function writeDbFromFile($user_dir,$runYear,$trig,$comments,$allOrSome=0) {
    global $dbRefSetTable,$dbDataTable,$QAdebug,$marks_txt,$DAEMON_OUTPUT_DIR;
    if (idMatchCheck()) { return -1; } # SYNC PROBLEMS!
    $vers = getNextVers($runYear,$trig);
    
    $user_dir1 = $DAEMON_OUTPUT_DIR . $user_dir;
    $newRefs = $user_dir1;
    if ($allOrSome) {
      # update some reference histograms
      @(checkMarksExist($user_dir)) or died("Problems (30).");
      readMarks($user_dir);
      $_pos = strrpos($user_dir,"_");
      $user = substr($user_dir,0,$_pos);
      $whichDir = substr($user_dir,$_pos+1);
      $mergeID = mergeProcRequest($user,$whichDir,$marks_txt);
      $res = waitForProc(2,$mergeID,-65,-64);
      $status = $res[0];
      if ($status < 0) { return $status; }
      $newRefs .= "/newRefHists.root";
    } else {
      # else update all reference histograms
      $newRefs .= "/resultHists.root";
    }
    
    @($fp = fopen($newRefs,"rb")) or died("Problems (27).");
    flock($fp,LOCK_SH);
    @($data = escapeDB(@fread($fp,@filesize($newRefs)))) or died("Problems (28)."); 
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems (29).");

    $user = readUserName($user_dir);
    $qry = "INSERT INTO $dbRefSetTable (`runYear`,`trig`,`vers`,`user`,`comments`)"
    . " VALUES (${runYear},'${trig}',${vers},'${user}','${comments}')";
    queryDB($qry);
    $id = getDBid(); # grabs auto-incremented id (does not work for delayed)

    $qry = "SHOW VARIABLES LIKE 'max_allowed_packet'";
    $row = queryDBfirst($qry);
    $maxsize = $row['Value'];
    $maxsize = min($maxsize,16777216)-1024; # Stored as medium blob, must stay below it
    
    # insert data into DB segment-by-segment
    $QAdebugTmp = $QAdebug; $QAdebug=0; # Otherwise the logs will fill up
    for ($segment=0; $segment<strlen($data)/$maxsize; $segment++) {
      $dataseg = substr($data,$segment * $maxsize,$maxsize);

      $qry = "INSERT DELAYED INTO $dbDataTable (`id`,`segment`,`data`) "
      . "VALUES (${id},'${segment}','${dataseg}')";
      queryDB($qry);
    }
    $QAdebug = $QAdebugTmp; # Otherwise the logs will fill up
    #copy $newRefs getFilename($runYear,$trig,$vers);

    return $id;
  }
  
  function idMatchCheck() {
    # return difference in ids (data table id minus description table id)
    global $dbRefSetTable,$dbDataTable;
    $row = queryDB("SELECT MAX(`id`) FROM $dbRefSetTable");
    $id1 = $row['MAX(`id`)'];
    $row = queryDB("SELECT MAX(`id`) FROM $dbDataTable");
    $id2 = $row['MAX(`id`)'];
    if ($id1 != $id2) {
      logit("idMatchCheck failed: $dbDataTable id = $id2 , $dbRefSetTable id = $id1");
    }
    return ($id2-$id1);    
  }

  function optimizeRefTables() {
    global $dbRefSetTable,$dbDataTable;
    optimizeTable($dbRefSetTable);
    optimizeTable($dbDataTable);
  }
    
# find out the next auto_inc value
# show table status like 'QARefHistsData';
# set the next auto_inc vlaue
# alter table QARefHistsData AUTO_INCREMENT=3;

?>