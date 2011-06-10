<?php
  
  incl("db.php");
  incl("files.php");
  
  global $autoIndex,$autoFilePath;
  $autoFilePath = "/star/data10/qa/files";
  $autoIndex = "/afs/rhic.bnl.gov/star/users/starqa/WWW/QA/listofFiles.txt";


###############################
# AutoCombine functions
#
    
  function isAutoTag($inputfile) {
    return preg_match('/^zz\d+$/',$inputfile);
  }
    
  function getAutoCombFiles($autoID,$status) {
    global $autoFilePath;
    $listfile = "${autoFilePath}/${autoID}_filelist.txt";
    if (!(file_exists($listfile))) { $status = -59; return ""; }
    $inputfull = readText($listfile);
    return "";
  }
  
  function getAutoCombInfo($autoID) {
    global $autoIndex;
    (file_exists($autoIndex)) or died("No autoComb list found");
    $inputfull = readText($autoIndex);
    $tokens = "\n";
    $tok = strtok($inputfull,$tokens);
    $found = false;
    $cnt = 0;
    while ((! $found) && ($tok !== false)) {
      // Either the start or end of the line...
      if ((preg_match("/ ${autoID}$/",$tok)) || (preg_match("/^${autoID} /",$tok))) {
        $found = true;
      } else {
        $tok = strtok($tokens);
        ($cnt++ < 4096) or died("Reading autoComb list not sane");
      }
    }
    if (! $found) {
      logit("Run not found in autoComb list");
      $tok = "-1 0 0 0";
    }
    return split(" ",$tok);
  }
  
  function getAutoCombRun($autoID) {
    if (isRunNum($autoID)) { return $autoID; }
    $info = getAutoCombInfo($autoID);
    return $info[0];
  }

  function getAutoCombTag($autoID) {
    if (isAutoTag($autoID)) { return $autoID; }
    $info = getAutoCombInfo($autoID);
    return $info[3];
  }
  
  ?>