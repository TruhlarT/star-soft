<?php
  
  @inclR("refDesc.php");
  incl("sections.php");
  inclR("refDisplayPlots.php");
  
  global $user_dir,$myCols,$edit,$cutModes,$defaultCutMode,$singleFile;
  global $res,$cuts,$page,$cell,$ttyp,$trigs;
  getPassedInt("cell");
  getPassedVarStrict("ttyp");
  
  $result = $res[$ttyp][$page][$cell];
  $name = $result['name'];
  print "<h3>Reference Analysis for Histogram: $name</h3>\n";

  $strRunEdit0 = "runEdit('${ttyp}',${page},${cell},0)";
  $strRunEdit1 = "runEdit('${ttyp}',${page},${cell},1)";

  #######################
  # Section for displaying the histogram(s)
  displayPlots($name);
  #execSys();
  print "<p>\n";

  
  #######################
  # Section for the description of the histogram
  beginSection("descriptor","Description",1080,$myCols["emph"]);
  fstart("descForm","refUpdater.php","QARnfr");
  $dname = stripHistPrefixes($name);
  fhidden("name",$dname);
  fhidden("topic",2);
  $desc = getLatestDesc($dname);
  if ($edit) {
    if (!$desc) { $desc = array('title' => "(No Title)", 'desc' => "(No Description)"); }
    ftext("title",$desc,1,55);
    linebreak();
    ftext("desc",$desc,5,55);
    linebreak();
    fbutton("updateDesc","Update Description",
            "UpdateSubmit('descForm')");
  } else {
    if (!$desc) {
      print "<i>No description available.</i>\n";
    } else {
      print "<i>Title:</i> <tt>" . stripslashes($desc['title']);
      print "</tt><br>\n";
      print "<i>Description:</i><blockquote><pre>" . stripslashes($desc['desc']);
      print "</pre></blockquote>\n";
    }
  }
  fend();
  endSection();
  print "<p>\n";

  #######################
  # Section for the marking the histogram for reference update
  if ($edit) {
    fstart("markForm","refUpdater.php","QARnfr");
    fhidden("name",$name);
    fhidden("mode",0);
    fhidden("user_dir",$user_dir);
    fhidden("topic",4);
    ReadMarks();
    if (markExists($name)) {
      fbutton("unmarkForRef","Unmark for updating reference",
              "markForm.mode.value=1;UpdateSubmit('markForm')");
    } else {
      $histprefix = getTrigPrefix($name);
      print "<i>Reference applies to histograms for trigger types:</i> ";
      print "<select name=pref>\n";
      foreach ($trigs as $k => $v) {
        $desc = "$k - $v";
        $pval = stripHistPrefixes($name,-1,$k);
        if ($k == "GE") { $desc .= " (any)"; }
        elseif ($k == "NA") { continue; }
        print "<option value=\"${pval}\"";
        if ($k == $histprefix) {
          print " selected";
        }
        print ">${desc}</option>\n";
      }
      print "</select>\n";
      linebreak();
      fbutton("markForRef","Mark for updating reference data",
              "markForm.mode.value=0;UpdateSubmit('markForm')");
    }
    
    fend();
    linebreak();
  }
  
 
  #######################
  # Section for the cuts of the analysis
  beginSection("analer","Analysis",1080,$myCols["good"]);
  $namedCut = getCutForName($name,$cuts);
  
  if ($namedCut) {
    $cutprefix = $namedCut['prefix'];
    $cutname = $namedCut['name'];
    $cutn = $cuts[$cutname];
    $cut = floatval($cutn['cut']);
    $mode = intval($cutn['mode']);
    $opts = $cutn['opts'];
  } else {
    print "<i><font color=maroon>No specific cut was used for this histogram."
    . " Defaults were used.</font></i>\n";
    $mode = -1;
    $cutprefix = "";
    $opts = "";
  }
  
  fstart("cutForm","refUpdater.php","QARnfr");
  fhidden("topic",1);
  fhidden("name",$name);
  print "<table>\n";

  print "<tr><td><i>Cut for histograms of name similar to:</i></td><td>";
  print stripHistPrefixes($name) . "</td></tr>\n";
  
  print "<tr><td><i>Cut applies to histograms for trigger types:</i></td><td>";
  if ($edit) {
    print "<select name=pref>\n";
    foreach ($trigs as $k => $v) {
      $desc = "$k - $v";
      $pval = "\"${k}\"";
      if ($k == "GE") { $desc .= " (any)"; }
      elseif ($namedCut && $k == "NA") { continue; }
      elseif ($k == "NA") { $pval .= " disabled"; }
      print "<option value=${pval}";
      if ($k == $cutprefix) {
        print " selected";
        $desc .= " [currently selected]";
      }
      print ">${desc}</option>\n";
    }
    print "</select>\n";
  } elseif ($namedCut) {
    $desc = "${cutprefix} - " . $trigs[$cutprefix];
    if ($cutprefix == "GE") { $desc .= " (any)"; }
    print $desc;
  }
  print "</td></tr>\n";
  
  print "<tr><td><i>Analysis mode:</i></td><td>";
  if ($edit) {
    print "<select name=mode>\n";
    foreach ($cutModes as $k => $v) {
      $desc = "$k - $v";
      print "<option value=\"$k\"";
      if ($k == $mode) {
        print " selected";
        $desc .= " <font size=-1>[currently selected]</font>";
      }
      print ">${desc}</option>\n";
    }
    print "</select>\n";
  } elseif ($namedCut) {
    $desc = "${mode} - " . $cutModes[$mode];
    print $desc;
  }
  print "</td></tr>\n";

  print "<tr><td><i>Analysis options:</i></td><td>";
  if ($edit) {
    finput("opts",10,$opts);
  } elseif ($namedCut) {
    print $opts;
  }
  print "</td></tr>\n";

  if (!$singleFile) {
    print "<tr><td><i>Analysis result:</i></td><td>" . $result['result'];
    if (!($namedCut)) {
      print " <font size=-1>[from default mode: ${defaultCutMode} - "
      . $cutModes[$defaultCutMode] . "]</font>";
    }
    print "</td></tr>\n";
  }

  print "<tr><td><i>Cut value <font size=-1>(minimum passing result)</font>:</i></td><td>";
  if ($edit) {
    finput("cut",10,$cut);
    print "</td></tr>\n";
    print "<tr><td colspan=2 align=center><br>\n";
    #fsubmit("Update Cut");
    fbutton("updateCut","Update Cut","UpdateSubmit('cutForm')");
    print "<br><font size=-1>Updating a cut does not automatically re-run the reference analysis\n";
    print "nor immediately update the cut value shown for this analysis.<br>\n";
    print "Please click on \"Help\" if you're not sure what you are doing.</font></td></tr>\n";
    print "<tr><td colspan=2 align=right>\n";
    fbutton("deleteCut","Delete Cut","SetDeleteCut();UpdateSubmit('cutForm')");
    print "</td></tr>\n";
  } elseif ($namedCut) {
    print "${cut}</td></tr>\n";
  }
  print "</table>\n\n";
  
  fend();
  
  fbutton("viewTrends","View Trends","ViewTrends('')");
  endSection();  
  linebreak();
  

  if ($edit) {
    fbutton("editExam","Examine only (no edits)",$strRunEdit0);
  } else {
    fbutton("editExam","Edit (experts only!)",$strRunEdit1);
  }
  linebreak();

  print "</div>\n<div id=\"trendGraph\" ";
  print "style=\"position:absolute; bottom:10px; left:10px; z-index:200; display:none; ";
  print "background-color:" . $myCols["emph"] . "; border: 2px solid rgb(0, 64, 128); \">";
  print "</div>\n<div id=\"jhelpers\">\n";
  
  jstart();
  jsToggleSection();
  if ($edit) {
    ?>
    function UpdateSubmit(formToSub) {
      setTimeout("document." + formToSub + ".submit()",0);
      str = "<?php print $strRunEdit1; ?>";
      setTimeout(str,250);
    }
    function SetDeleteCut() {
      document.cutForm.cut.value = -999;
    }
<?php } ?>
    function ViewTrends(args) {
      $.ajax({
              url : "refGraph.php?name=<?php print $name; ?>" + args,
              success : function (data) {
                $("#trendGraph").html(data);
                document.getElementById("trendGraph").style.display = 'block';
              }
             });
    }
    function HideTrends() {
      $("#trendGraph").html("");
      document.getElementById("trendGraph").style.display = 'none';
    }
    toggleSection('descriptor');
    toggleSection('analer');
  <?php
  jend();

?>
