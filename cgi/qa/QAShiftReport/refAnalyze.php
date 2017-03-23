<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  inclR("refData.php");
  inclR("refCuts.php");
  inclR("requestHandling.php");
  inclR("refAutoComb.php");
  inclR("refDisplayPlots.php");
  getPassedVarStrict("inputfile");
  getPassedVarStrict("format");
  getPassedVarStrict("user");
  getPassedInt("refID");
  getPassedInt("combID");
  getPassedInt("viewmode");
  
  function copyCombLogs($dir,$mode) {
    # $mode=0 => to tmp, 1 => from tmp
    global $combID;
    $tmp = getWrkDir() . "comb_${combID}";
    ckdir($tmp);
    $files = array("out.txt","filelist.txt");
    foreach ($files as $k => $file) {
      $file_in = ($mode ? $tmp : $dir) . "/" . $file;
      if (file_exists($file_in)) {
        $file_out = ($mode ? $dir : $tmp) . "/" . $file;
        if (file_exists($file_out)) { rmfile($file_out); }
        copy($file_in,$file_out);
        # don't remove; in case analysis is re-run
        #if ($mode) { rmfile($file_in); }
      }
    }
  }
  
  global $fstream;
  $user_dir = "";
  $status = 1;
  $infile = $inputfile;
  $fstream = "";

#$status = -64; $refID = -1; $combID = -1; # TEST
  
  if ($refID >= 0) {
    if (strlen(getFileById($refID))==0) { $status = -99; }
  }

  if ($combID >= 0) {
    getPassedVarStrict("stream");
    $fstream = FStreamSearch($stream);
    global $DAEMON_OUTPUT_DIR;
    $user_dir = $DAEMON_OUTPUT_DIR . $user . "_" . $combID;
    # Wait for the combine to finish...
    $res = waitForProc(1,$combID,-95,-94);
    $status = $res[0];
    copyCombLogs($user_dir,0);
  } else if (isAutoTag($infile)) {
    $acInfo = getAutoCombInfo($infile);
    $infile = $acInfo[0];
    # e.g. st_ph => st_physics => ph
    $fstream = FStreamSearch($acInfo[2]);
    if ($infile < 0) { $status = -93; }
  } else if (strlen($infile)>4) {
    # e.g. st_physics_9123456_raw_0000000 => st_physics => ph
    $fstream = FStreamSearch(substr($infile,0,strpos($infile,"_",4)));
  }

  if ($status > 0) {
    # Prepare and submit processing request
    logit("Submitting analysis request");
    $cutsID = -1;
    $refCacheExists = false;
    $cacheDir = ""; $cacheTempDir = "";
    if ($refID >=0) {
      $info = getInfoById($refID);
      $cutsID = getLatestCutsID($info['runYear'],$info['trig']);
      # Check on reference cache existence
      $cacheDir = userRefDir($QARefCache,$refID);
      if (is_dir($cacheDir) && file_exists($cacheDir . "/fullCopy")) {
        $refCacheExists = true;
      } else {
        # Maybe a produced cache is waiting for copy
        $cacheTempDir = $DAEMON_OUTPUT_DIR . $QARefCache . "_" . $refID;
        $refCacheExists = is_dir($cacheTempDir);
      }
    }
    $procID = refProcRequest($refID,$cutsID);
    if ($procID < 0) {
      $status = -91; # unable to process
    } else {
      if (($refID >= 0) && (! $refCacheExists)) { refProcRequest($refID,$cutsID,true); }
      # Wait for the results...
      $res = waitForProc(0,$procID,-98,-96,-97);
      if (strlen($cacheTempDir) && is_dir($cacheTempDir)) {
        # Copy a waiting produced reference cache
        cpdir($cacheTempDir,$cacheDir);
        system("/bin/csh -f -c \"/usr/bin/bunzip2 ${cacheDir}/*.bz2 >& /dev/null &\"");
        touch($cacheDir . "/fullCopy");
      }
      $status = $res[0];
      $results = $res[1];
    }

    $user_dir = $user . "_" . $results['anticache'];
    fstart2("successForm","refOutput.php","output");
    fhidden("inputfile",$infile);
    fhidden("fstream",$fstream);
    fhidden("format",$format);
    fhidden("refID",$refID);
    fhidden("cutsID",$cutsID);
    fhidden("newRefHists",$results['refFile']);
    fhidden("refResults",$results['refCuts']);
    fhidden("user_dir",$user_dir);
    if (getPassedVarStrict("useRunsStr",1)) { fhidden("useRunsStr",$useRunsStr); }
    fhidden("viewmode",$viewmode);
    if ($combID >= 0) { 
      copyCombLogs(userRefDir($user_dir,$combID),1);
      fhidden("combID",$combID);
    }
    
    fend();
    
  }
  
  fstart2("failedForm","refStatus.php","main");
  fhidden("status",$status);
  fend();
  
  jstart();
  #print "    setTimeout(\"post_form('" . ($status<0 ? "failed" : "success") . "Form')\",500);\n";
  print "    post_form('" . ($status<0 ? "failed" : "success") . "Form');\n";
  jend();
  if ($status >= 0) { preparePlots(); }
  
  if (connectedDB()) { closeDB(); } ?>
