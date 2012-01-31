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
  
  head("QA Reference Histogram Analyze");
  body();
  
  $user_dir = "";
  $status=1;
  $infile = $inputfile;
  
  if ($refID >= 0) {
    if (strlen(getFileById($refID))==0) { $status = -99; }
  }

  if ($combID >= 0) {
    # Wait for the combine to finish...
    $res = waitForProc(1,$combID,-95,-94);
    $status = $res[0];
    global $DAEMON_OUTPUT_DIR;
    $user_dir = $DAEMON_OUTPUT_DIR . $user . "_" . $combID;
    copyCombLogs($user_dir,0);
  } else if (isAutoTag($infile)) {
    $infile = getAutoCombRun($infile);
    if ($infile < 0) { $status = -93; }
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
    fstart("successForm","refOutput.php","QARofr");
    fhidden("inputfile",$infile);
    fhidden("format",$format);
    fhidden("refID",$refID);
    fhidden("cutsID",$cutsID);
    fhidden("newRefHists",$results['refFile']);
    fhidden("refResults",$results['refCuts']);
    fhidden("user_dir",$user_dir);
    if ($combID >= 0) { 
      copyCombLogs(userRefDir($user_dir,$combID),1);
      fhidden("combID",$combID);
    }
    
    fend();
    
  }
  
  fstart("failedForm","refStatus.php","QARmfr");
  fhidden("status",$status);
  fend();
  
  fstart("prepForm","refPrepPlots.php","QARnfr");
  fhidden("user_dir",$user_dir);
  fend();
  
  jstart();
  print "    document." . ($status<0 ? "failed" : "success") . "Form.submit();\n";
  if ($status >= 0) { print "    document.prepForm.submit();\n"; }
  jend();
  
  foot();
?>
