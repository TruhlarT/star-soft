<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  incl("entrytypes.php");
  incl("sections.php");

  global $DAEMON_OUTPUT_DIR,$URL_FOR_DAEMON_OUTPUT;

  getPassedVarStrict("inputfile");
  getPassedVarStrict("fstream");
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
    return false;
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

  $sectColor = $myCols[($exists_plots || $format=="none" ? "good" : "bad")];

  print "<div id=\"outputLabel\" class=\"refNavig refPop refPopNavig\">\n";
  print "<b>Output...</b>\n\n";
  print "</div>\n\n";
  print "<div id=\"outputOutline\" class=\"refContent refPopOutline\">\n";
  print "<div id=\"outputContent\" class=\"refPop refPopContent\">\n";

  helpButton(3);

  if ($format!="none") {
    beginSection("plots","Output plots",800,$sectColor);
    if ($exists_plots) {
      foreach ($trigs as $type => $v) {
        if (isset($stdFiles[$type])) {
          mkhref2($urlstr . $stdFiles[$type],$v,"new");
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
  beginSection("logs","Logs",802,$sectColor);
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
    fstart2("statusForm","refShowAnalysis.php","main");
    fhidden("refID",$refID);
    fhidden("cutsID",$cutsID);
    fhidden("inputfile",$inputfile);
    fhidden("fstream",$fstream);
    fhidden("page",0);
    fhidden("doPageCell",($format=="none" ? 0 : 1));
    fhidden("user_dir",$user_dir);
    if (getPassedVarStrict("useRunsStr",1)) { fhidden("useRunsStr",$useRunsStr); }
    if (getPassedInt("viewmode",1)) { fhidden("viewmode",$viewmode); }
    fhidden("newRefHists",$newRefHists);
    fhidden("refResults",$refResults);
    if ($combJob) { fhidden("combID",$combID); }
    if ($QAdebug) {
      linebreak();
      fbutton("reDispButton","Re-display results","post_form('statusForm')");
    }
  } else {
    fstart2("statusForm","refStatus.php","main");
    fhidden("status",-89);    
  }
  fend();
  
  jstart();
  if ($format!="none") { print "    toggleSection('plots');\n"; }
  print "    toggleSection('logs');\n";
  print "    post_form('statusForm');\n";
  print "    assignClicks();\n";
  jend();

  print "</div></div>\n\n";

  if (connectedDB()) { closeDB(); } ?>
