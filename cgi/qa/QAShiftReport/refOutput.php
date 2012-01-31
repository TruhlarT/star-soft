<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  incl("entrytypes.php");
  incl("sections.php");

  global $DAEMON_OUTPUT_DIR,$URL_FOR_DAEMON_OUTPUT;

  getPassedVarStrict("inputfile");
  getPassedVarStrict("format");
  getPassedVarStrict("user_dir");
  getPassedVar("newRefHists");
  getPassedVar("refResults");
  getPassedInt("refID");
  getPassedInt("cutsID");
  $combJob = getPassedVarStrict("combID",1);
  
  
  function getOutputTrig($fname){
    global $format,$trigs;
    foreach ($trigs as $type => $v) {
      $typ = ( $type == "GE" ? "" : $type );
      if (preg_match("/hist${typ}\.${format}/",$fname)) { return $type; }
    }
    return 0;
  }
  
  function isRefOutput($fname) {
    return (preg_match("/^Ref_/",$fname));
  }
  
  $user_dir_str = "${DAEMON_OUTPUT_DIR}${user_dir}/";
  $urlstr = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/";

  $files = dirlist($user_dir_str,"QA_hist",$format);
  
  $refFiles = array();
  $stdFiles = array();
  
  foreach ($files as $k => $file) {
    $needsFixStr = ".${format}+";
    $needsFix = strpos($file,$needsFixStr);
    if ($needsFix !== false) {
      $newfile = substr($file,0,$needsFix) . substr($file,$needsFix + strlen($needsFixStr));
      $file = $newfile;
      $format = "ps";
      logit("FIXED FILENAME TO $file");
    }
    
    
    $ttyp = getOutputTrig($file);
    if (!$ttyp) { continue; }
    if (isRefOutput($file)) {
      $refFiles[$ttyp] = $file;
    } else {
      $stdFiles[$ttyp] = $file;
    }
  }

  $exists_plots = (count($stdFiles) > 0);
  $exists_stdout = file_exists($user_dir_str . "stdout.html");
  $exists_stderr = file_exists($user_dir_str . "stderr.html");

  headR("QA Reference Output");
  jstart();
  jsToggleSection();
  jend();
  body();
  
  helpButton(3);
  $sectColor = $myCols[($exists_plots || $format=="none" ? "good" : "bad")];

  if ($format!="none") {
  beginSection("plots","Output plots",800,$sectColor);
  if ($exists_plots) {
    foreach ($trigs as $type => $v) {
      if (isset($stdFiles[$type])) {
        mkhref2($urlstr . $stdFiles[$type],$trigs[$type],"new");
        if (isset($refFiles[$type])) {
          print "(";
          mkhref2($urlstr . $refFiles[$type],"Ref","new");
          print ")\n";
        }
        print "<br>\n";
      }
    }
  } else {
    print "<i>None found!</i>\n";
  }
  endSection();
  linebreak();
  } #Output plots if requested
  
  $sectColor = $myCols[($exists_stdout && $exists_stderr ? "good" : "bad")];
  beginSection("logs","Logs",801,$sectColor);
  print "Plotting:\n";
  if ($exists_stdout) {
    mkhref2("${urlstr}stdout.html","stdout","new");
  } else { print "no stdout\n"; }
  print ", ";
  if ($exists_stderr) {
    mkhref2("${urlstr}stderr.html","stderr","new");
  } else {  print "no stderr\n"; }
  
  if ($combJob) {
    $user_dir_str = userRefDir($user_dir,$combID);
    $urlstr = urlUserRefDir($user_dir,$combID);
    $exists_filelist = file_exists("${user_dir_str}/filelist.txt");
    $exists_out = file_exists("${user_dir_str}/out.txt");
    print "<br>\nCombining:\n";
    if ($exists_filelist) {
      mkhref2("${urlstr}filelist.txt","file list","new");
    } else { print "no file list\n";  }
    print ", ";
    if ($exists_out) {
      mkhref2("${urlstr}/out.txt","output","new");
    } else { print "no output\n"; }
  }
  
  endSection();
  
  if ($exists_plots || $format=="none") {
    fstart("statusForm","refShowAnalysis.php","QARmfr");
    fhidden("refID",$refID);
    fhidden("cutsID",$cutsID);
    fhidden("inputfile",$inputfile);
    fhidden("page",0);
    fhidden("doPageCell",($format=="none" ? 0 : 1));
    fhidden("user_dir",$user_dir);
    fhidden("newRefHists",$newRefHists);
    fhidden("refResults",$refResults);
    if ($combJob) { fhidden("combID",$combID); }
    if ($QAdebug) {
      linebreak();
      fbutton("reDispButton","Re-display results","statsub()");
    }
  } else {
    fstart("statusForm","refStatus.php","QARmfr");
    fhidden("status",-89);    
  }
  fend();
  
  jstart();
  print "    function statsub() { document.statusForm.submit(); }\n";
  print "    statsub();\n";
  jend();

  foot(0,0);
?>
