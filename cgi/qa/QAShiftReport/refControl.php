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
  $histGroups = array("reg" => "Regular QA",
                      "TPCsectors" => "TPC sectors",
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
    $inputfile = $useRun;
    $soFarStr = getAutoCombStr($useRun);
  } else if ($oooer === "viewRef") {
    $useRuns[] = getLastExaminedRun();
  } else {
    header("location: ${webdir}blank.html");
    exit;
  }


  headR("STAR QA Reference Histograms Control");
  ?>

<style type="text/css">
<!--
a.items:link {color: navy; text-decoration: none; }
a.items:visited {color: navy; text-decoration: none; }
a.items:active {color: tomato; text-decoration: none; }
a.items:hover {color: maroon; text-decoration: none; }
-->
</style>

<?php
  
  
  jstart();
  initRefSelectors(2,$useRuns[0]);  
  ?>
    function prepReady(val) {
      document.showInfoForm.refID.value = val;
      document.analyzeForm.refID.value = val;
    }
    function prepAnalysis() {
      aForm = document.analyzeForm;
      cForm = document.choiceForm;
      aForm.format.value = cForm.format.value;
      aForm.whichHist.value = cForm.whichHist.value;
      document.waitForm.submit();
      aForm.submit();
      window.parent.setFirst();
    }
    function noAnalysis() {
      refID = document.analyzeForm.refID.value;
      prepReady(-999);
      prepAnalysis();
      setTimeout('prepReady(' + refID + ');',300);
    }
    function backToQA(val) {
      bForm = document.backForm;
      bForm.formNumber.value = val;
      bForm.submit();
    }
<?php
  jsToggleSection();
  jend();

  body();
  # /cgi-bin/protected/starqa/qa?textUserName=${textUserName}&commas=no&formNumber=2&radioMainMenu=fastOffline
  helpButton(1);
  
  print "<h3>Controls...</h3>\n\n";

  beginSection("backers","Go back",1017,"cornsilk");
  fstart("backForm","/cgi-bin/protected/starqa/qa","_top","GET",0);
  foreach ( $_GET as $k => $v ) {
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
    fstart("choiceForm","refControl.php");

    beginSection("referencers","Select a reference set",1015,"cornsilk");
    $lcnt = selectYTV();
    endSection();

    print "<div style=\"background-color:" . $myCols["emph"] . "; display: table; border: 2px solid rgb(0, 64, 128); \">\n";
    if (!($oooer === "viewRef")) { fbutton("noRef","Plots Only","noAnalysis()"); print " | "; }
    print "<span id=\"refSelected\" style=\"display:none\">\n";
    fbutton("analyze","Analyze","prepAnalysis()");
    fbutton("showInfo","Show Set Info","loadWindow('showInfoForm','QARinfo')");
    print "</span>\n";
    print "<span id=\"refNotSelected\" style=\"display:inline\"><i>reference not selected</i>&nbsp;</span>\n";
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
    $useRunsStr = implode("_",$useRuns);
    $detList = getDetList($useRunsStr);
    foreach ($detList as $k => $v) {
      print "<option value=\"det${v}\">Subsystem: ${v}</option>\n";
    }
    print "</select>)\n";
    print "</font>\n\n";
    endSection();

    fend();

    # For showing info about the selected reference histogram set:
    fstart("showInfoForm","refShowInfo.php","QARinfo");
    fhidden("refID","-1");
    fend();
    
    # For starting the analysis:
    fstart("analyzeForm","refAnalyze.php","QARnfr");
    fhidden("inputfile",$inputfile);
    fhidden("format",$fileFormat);
    fhidden("user",$textUserName);
    fhidden("whichHist",$whichHist);
    fhidden("refID","-1");
    fhidden("combID",$combID);
    if (!($oooer === "viewRef")) fhidden("useRuns",$useRunsStr);
    fend();
    fstart("waitForm","refStatus.php","QARmfr");
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
    print "    toggleSection('flisters');\n";
    if ($combID>=0) {
      print "    window.parent.fsHideSize = 55;\n";
      print "    window.parent.fsShowSize = 350;\n";
    }
    jend();
  }

  foot(0,0); ?>
