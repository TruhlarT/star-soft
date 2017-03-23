<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  inclR("refData.php");
  inclR("refSelector.php");
  inclR("requestHandling.php");
  incl("sections.php");
  
  # Defaults
  $oooer = "viewRef";
  $fileFormat = "none";
  $whichHist = "reg";

  getPassedVarStrict("textUserName");
  getPassedVarStrict("fileFormat",1);
  getPassedVarStrict("whichHist",1);
  getPassedVarStrict("oooer",1);
  $formats = array("ps" => "PostScript",
                   "pdf" => "PDF",
                   "none" => "none");
  $histGroups = array("reg" => "QA Shift",
                      "TPCsectors" => "TPC Sectors",
                      "all" => "All");
  
  $combID = -1;
  $status = 1;
  $soFarStr = "";
  $inputfile = ""; # default
  if ($oooer === "combRef") {
    $inputfile = "${textUserName}_comb";
    $soFarStr = combProcRequest($combID,$status);
    logit("combProcRequest gave status = ${status}");
  } else if ($oooer === "singleRef") {
    getPassedVarStrict("whichFastOffline");
    (substr($whichFastOffline,14,1) == "_") or died("Invalid input");
    $inputfile = substr($whichFastOffline,15);
    $finfo = getInfoFromFilename($inputfile);
    $useRuns[] = $finfo['runNumber'];
    $soFarStr = runLogLink() . ", using file ${inputfile}<br>\n";
  } else if ($oooer === "autoRef") {
    getPassedVarStrict("useRun");
    if (substr($useRun,0,2) === "go") {
      $useRun = substr($useRun,2);
      $status = 2;
    }
    $soFarStr = getAutoCombStr($useRun,$inputfile);
  } else if ($oooer === "viewRef") {
    $useRuns[] = getLastExaminedRun();
  } else {
    header("location: ${webdir}blank.php");
    exit;
  }


  jstart();
  initRefSelectors(2,$useRuns[0]);  
  ?>
    function prepReady2(val) {
      document.showInfoForm.refID.value = val;
      document.analyzeForm.refID.value = val;
    }
    function prepAnalysis() {
      hidePops();
      clear_div("output");
      setQATitle("processing...");
      post_form("waitForm");
      cForm = document.choice2Form;
      cWhichHist = cForm.whichHist.value;
      if (cWhichHist.substring(0,3) == 'det') {
        document.analyzeForm.viewmode.value = 11;
      }
      post_form("analyzeForm",'format',cForm.format.value,'whichHist',cWhichHist);
      page_entry = false;
    }
    function noAnalysis() {
      refID = document.analyzeForm.refID.value;
      prepReady2(-999);
      prepAnalysis();
      setTimeout('prepReady2(' + refID + ');',300);
    }
    function backToQA(formNumber) {
      submit_form('backForm','formNumber',formNumber);
    }
<?php
  jend();

  
  print "<div id=\"controlLabel\" class=\"refNavig refPop refPopNavig\">\n";
  print "<b>Controls...</b>\n\n";
  print "</div>\n\n";
  print "<div id=\"controlOutline\" class=\"refContent refPopOutline\">\n";
  print "<div id=\"controlContent\" class=\"refPop refPopContent\">\n";

  helpButton(1);

  beginSection("backers","Go back",1017,"cornsilk");
  fstart("backForm","/cgi-bin/protected/starqa/qa","_top","GET",0);
  foreach ( $_POST as $k => $v ) {
    $first6 = substr($k,0,6);
    if (! (($first6 === "useRun") ||
           ($first6 === "formNu") ||
           ($first6 === "whichF"))) {
      fhidden($k,$v);
    }
  }
  fhidden("formNumber","0");
  if ($status > 0 && $oooer !== "viewRef") { fbutton("subit","Back to data selections","backToQA(22)"); }
  fbutton("rubit","Back to QA options","backToQA(2)");
  fend();
  endSection();

  if ($status > 0) {
    fstart2("choice2Form");

    beginSection("referencers","Select a reference set",1015,"cornsilk");
    $lcnt = selectYTV();
    endSection();

    print "<div id=\"plotAnalyze\" style=\"background-color:" . $myCols["emph"] . "; display: table; border: 2px solid rgb(0, 64, 128); \">\n";
    if (!($oooer === "viewRef")) { fbutton("noRef","Plots Only","noAnalysis()"); print " | "; }
    print "<span id=\"refSelected2\" style=\"display:none\">\n";
    fbutton("analyze","Analyze","prepAnalysis()");
    fbutton("showInfo","Show Set Info","loadWindow('showInfoForm','QARinfo')");
    print "</span>\n";
    print "<span id=\"refNotSelected2\" style=\"display:inline\"><i>reference not selected</i>&nbsp;</span>\n";
    print "</div>\n";
    
    beginSection("optioners","Plotting options",1016,"cornsilk");
    print "<font size=-1>Full output format: <select name=\"format\">\n";
    foreach ($formats as $k => $v) {
      print "<option value=\"${k}\"";
      if ($k == $fileFormat) print " selected";
      print ">${v}</option>\n";
    }
    print "</select>\n";
    print "&nbsp;&nbsp;&nbsp;Histogram group: <select name=\"whichHist\">\n";
    foreach ($histGroups as $k => $v) {
      print "<option value=\"${k}\"";
      if ($k == $whichHist) print " selected";
      print ">${v}</option>\n";
    }
    $detList = getDetList();
    if (count(array_intersect(array("pxl","ist","sst"),$detList)))
      $detList[] = "hft";
    foreach ($detList as $k => $v) {
      print "<option value=\"det${v}\">Subsystem: ${v}</option>\n";
    }
    print "</select>\n";
    print "</font>\n\n";
    endSection();

    fend();

    # For showing info about the selected reference histogram set:
    fstart("showInfoForm","refShowInfo.php","QARinfo");
    fhidden("refID","-1");
    fend();
    
    # For starting the analysis:
    fstart2("analyzeForm","refAnalyze.php","no");
    fhidden("inputfile",$inputfile);
    fhidden("format",$fileFormat);
    fhidden("user",$textUserName);
    fhidden("whichHist",$whichHist);
    fhidden("refID","-1");
    fhidden("combID",$combID);
    if (!($oooer === "viewRef")) { fhidden("useRunsStr",$useRunsStr); }
    if (strlen($stream)) { fhidden("stream",$stream); }
    fhidden("viewmode",($status == 2 ? "11" : "1"));
    fend();
    fstart2("waitForm","refStatus.php","main");
    fhidden("status","1");
    fend();
  }
  
  if (!($oooer === "viewRef")) {
    beginSection("flisters","Selected runs and files",
	         ($status < 0 ? -1018 : 1018),
	         ($status < 0 ? "#ffbc9f" : "cornsilk"));
    print "<font size=-1>\n${soFarStr}</font>\n";
    endSection();
  }
  
  if ($status>0) {
    jstart();
    print "    toggleSection('referencers');\n";
    print "    toggleSection('optioners');\n";
    if (!($oooer === "viewRef")) { print "    toggleSection('flisters');\n"; }
    if ($status == 2) { print "    noAnalysis(); setTimeout('hidePops();',500);\n"; }
    jend();
  }

  print "</div></div>\n\n";

  if (connectedDB()) { closeDB(); } ?>
