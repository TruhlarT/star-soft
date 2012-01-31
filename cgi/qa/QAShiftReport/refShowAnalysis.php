<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  inclR("refCuts.php");
  inclR("refMarks.php");
  inclR("refRecords.php");
  incl("sections.php");

  global $DAEMON_OUTPUT_DIR,$marks_exist,$go_back,$singleFile,$myCols;
  
  getPassedInt("refID");
  getPassedInt("cutsID");
  getPassedVarStrict("inputfile");
  getPassedInt("page"); # page > 0 means we are editing/examining
  getPassedVarStrict("user_dir");
  getPassedInt("doPageCell");
  getPassedVar("newRefHists");
  getPassedVar("refResults");
  $edit = 0;
  getPassedInt("edit",1);

  $combJob = getPassedVarStrict("combID",1);
  $singleFile = (strlen($inputfile) < 1 || $refID < 0);
  
  headR("QA Reference Histogram Analysis");
  
  ?>
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.4/jquery.min.js"
            type="text/javascript"></script>
  <?php
  jstart();
  jhideshow();
  ?>
    curelem = 0;
    prevStr = '';
    nextStr = '';

    function showOnlyElem(ename) {
      elem = showElem(ename);
      if (elem) {
        if (curelem) {
          curelem.style.display = 'none';
        }
        curelem = elem;
      }
    }
    function runEdit(ttyp,page,cell,edit) {
      document.dispForm.ttyp.value = ttyp;
      document.dispForm.page.value = page;
      document.dispForm.cell.value = cell;
      document.dispForm.edit.value = edit;
      document.dispForm.submit();
    }
    function check4sure(status) {
      var retval = confirm("Are you sure you want to record these results as " + status + "?");
      if (retval == true) {
        document.dispForm.viewmode.value = 3;
        document.dispForm.rStatus.value = status;
        document.dispForm.submit();
      } else {
        return false;
      }
    }
<?php
  jend();
  body();
  
  ### Initial and global values
  $ttyp = "";
  $cell = 0;
  $resultsfile = $DAEMON_OUTPUT_DIR . $user_dir . "/" . $refResults;
  $res = getResultsByLoc($resultsfile);
  $cuts = getCutsById($cutsID);
  checkMarksExist($user_dir);

  helpButton( ($page > 0 ? 12 : 11) );
  $go_back = false;

  
  ### Content (edit or display)
  print "<div id=\"refViewer\" style=\"position:absolute; top:0px; right:0px;";
  print " width:80%; height:99%; overflow:auto; z-index:1; ";
  print ($edit? "border: 2px dashed rgb(256, 0, 0); " : "") . "\">\n";
  @inclR("ref" . ($page > 0 ? "Edit" : "Display") . "Analysis.php");
  print "</div>\n\n";
  

  ### Menu (allow selections)
  print "<div id=\"refMenu\" style=\"position:absolute; top:0px; left:0px; ";
  print "width:20%; height:100%; overflow:auto; z-index:100; \">\n";
  

  # Mark as examined
  if (strlen($inputfile)) {
    print "<div style=\"background-color:" . $myCols["emph"];
    print "; display: table; border: 2px solid rgb(0, 64, 128); \">\n";
    print "<b>Mark as examined:&nbsp;</b><br>\n";
    fbutton("rGood","Good","check4sure('good')");
    fbutton("rBad","Bad","check4sure('bad')");
    print "</div>\n<p>\n";
  }
  
  #print "<div style=\"background-color:" . $myCols["good"]
  #. "; display: table; border: 2px solid rgb(0, 64, 128); \">\n";
  beginSection("navigators","Navigation",101,$myCols["good"]);

  fstart("dispForm","","QARmfr");

  # Dataset
  print ($singleFile ? "Plots" : "Analysis") . " for: <b>";
  if (strlen($inputfile)) {
    print (isRunNum($inputfile) ? "run " : "")
    . ($combJob ? "combined files (see selections above)" : $inputfile);
  } else {
    print "reference set ${refID}";
  }
  print "</b>\n<p>\n";
  
  # Hist list to show
  print "<b>Show list:</b><br>\n";
  if ($marks_exist) {
    fbutton("mbutton","Marked for update","viewmode.value=2;submit()");
    print "<br>\n";
  }
  if (! $singleFile) { fsubmit("Failed"); }
  fbutton("abutton","All","viewmode.value=1;submit()");
  linebreak();
  fbutton("apbutton","All + Plots","viewmode.value=11;submit()");

  fhidden("refID",$refID);
  fhidden("cutsID",$cutsID);
  fhidden("inputfile",$inputfile);
  fhidden("user_dir",$user_dir);
  fhidden("newRefHists",$newRefHists);
  fhidden("refResults",$refResults);
  fhidden("doPageCell",$doPageCell);
  fhidden("viewmode",0);
  fhidden("ttyp","");
  fhidden("page",0);
  fhidden("cell",0);
  fhidden("edit",$edit);
  if (strlen($inputfile)) { fhidden("rStatus",""); }
  if ($combJob) { fhidden("combID",$combID); }

  
  # Navigation
  print "<p><b>" . ($edit ? "Edit" : "Examine") . " ";
  print ($singleFile ? "plots" : "analysis") . " for:</b><br>\n";
  print "<span id=\"prever\" style=\"display:none ;z-index:102 \">\n";
  fbutton("prevEdit","Prev","eval(prevStr)");
  print "</span>\n<span id=\"noneer\" style=\"display:none ;z-index:103 \">\n";
  fbutton("noneEdit","----","");
  print "</span>\n<span id=\"nexter\" style=\"display:none ;z-index:104 \">\n";
  fbutton("nextEdit","Next","eval(nextStr)");
  print "</span>\n<br>\n\n";
  
  print "<span id=\"trButtonss\" style=\"display:none ;z-index:105 \">\n";
  foreach ($res as $TR => $typdata) {
    if (count($typdata) < 1) continue;
    print "<input type=\"radio\" name=\"trButtons\" value=\"${TR}\""
    . " onchange=\"showOnlyElem('div${TR}')\""
    . " onselect=\"showOnlyElem('div${TR}')\"";
    if ($TR==$ttyp) { print " checked"; }
    print ">" . $trigs[$TR] . "<br>\n";
  }
  print "</span>\n<br>\n\n";

  fend(); #dispForm
  
  $zin = 106;
  $prevStr = false;
  $nextStr = false;
  $lastStr = false;
  $tdStr = "<td style=\"width:2em\"";
  
  foreach ($res as $TR => $typdata) {
    
    $pages = count($typdata);
    if ($pages < 1) continue;
    $zin++;
    print "<div id=\"div${TR}\" style=\"display:none ;z-index:${zin} \">\n";
    #print "<div id=\"div${TR}\" style=\"display:none \">\n";
    $pgForm = "pgForm${TR}";
    fstart($pgForm,"","QARmfr");
    print "<table border=0 cellspacing=2 cellpadding=0>\n";
    
    for ($pg=1; $pg<=$pages; $pg++) {
      print "<tr valign=middle><td align=right><font size=-1>Page ${pg}</font></td><td align=left>\n";
      print "<table border=2 cellpadding=0 cellspacing=0>\n";
      $maxcl = count($typdata[$pg]);
      for ($cl=1;$cl<=$maxCell;$cl++) {
        $cstr = "<font size=-1>${cl}</font>";
        $bstr = "";
        if ($cl <= $maxcl) {
          $bstr = "<input type=\"radio\" name=\"pgButtons\" value=\"${pg}_${cl}\"";
          $editStr = "runEdit('${TR}',${pg},${cl},${edit})";
          if ($pg==$page && $cl==$cell && $TR==$ttyp) { 
            $bstr .= " checked";
            $prevStr = $lastStr;
            $nextStr = false;
          } else if (! $nextStr) { $nextStr = $editStr; }
          if (! $prevStr) { $lastStr = $editStr; }
          $bstr .= " onchange=\"${editStr}\">";
        }
        if (($cl % 2) == 1) { print "<tr>${tdStr}><nobr>${cstr}${bstr}</nobr></td>\n"; }
        else { print "${tdStr} align=right><nobr>${bstr}${cstr}</nobr></td></tr>\n"; }
      }
      print "</table>\n<p>\n";
      print "</tr>\n";
    }
    
    print "</table>\n";
    fend();
    print "</div>\n\n"; #div${TR}
    
  }

  endSection();
  print "</div>\n\n"; #refMenu
  #print "</div>\n</div>\n\n"; #bordered box; refMenu

  print "<div id=\"zoomPlot\" ";
  print "style=\"position:absolute; top:10px; left:10px; z-index:201; display:none; ";
  print "background-color:" . $myCols["emph"] . "; border: 2px solid rgb(0, 64, 128); \">";
  print "</div>\n\n";
  
  # initial values for Menu
  jstart();
  ?>
    function LoadZoom(args) {
      ops = 'fullscreen=yes,toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes';
      window.open(args,'QARzfr',ops);
    }
    function ViewZoom(args) {
      alert("GGGG :: " + args);
      $.ajax({
              url : args,
              success : function (data) {
                $("#zoomPlot").html(data);
                document.getElementById("zoomPlot").style.display = 'block';
              }
             });
    }
    function HideZoom() {
      $("#zoomPlot").html("");
      document.getElementById("zoomPlot").style.display = 'none';
    }
<?php
  if ($prevStr) {
    print "    setTimeout('showElem(\"prever\")',100);\n";
    print "    prevStr=\"${prevStr}\";\n";
  } else {
    print "    setTimeout('showElem(\"noneer\")',100);\n";
  }
  if ($nextStr) {
    print "    setTimeout('showElem(\"nexter\")',100);\n";
    print "    nextStr=\"${nextStr}\";\n";
  } else {
    print "    setTimeout('showElem(\"noneer\")',100);\n";
  }
  if ($doPageCell) {
    if ($page > 0) {
      print "    setTimeout('showOnlyElem(\"div${ttyp}\")',100);\n";
    } else {
      print "    setTimeout('document.dispForm.trButtons[0].checked=true',100);\n";
      print "    setTimeout('showOnlyElem(\"div\" + document.dispForm.trButtons[0].value)',100);\n";
    }
    print "    setTimeout('showElem(\"trButtonss\")',100);\n";
  }
  if ($go_back) {
    ?>
    function go_back() {
      var retval = confirm("Would you like to go back to the QA data selections?");
      if (retval == true) {
        form = window.parent.frames['QARcfr'].document.backForm;
        form.formNumber.value=22;
        form.submit();
      }
    }
    setTimeout('go_back()',250);
<?php
  }
  jsToggleSection();
  print "    toggleSection('navigators');\n";
  jend();
  
  foot(0,1);
?>

