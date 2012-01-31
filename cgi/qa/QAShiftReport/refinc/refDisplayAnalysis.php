<?php
  
  inclR("refData.php");
  inclR("refDisplayPlots.php");
  
  global $refID,$inputfile,$res,$cuts,$trigs,$viewmode,$edit,$doPageCell;
  global $user_dir,$go_back,$combJob,$singleFile,$combID;

  # viewmodes:
  # 0 : failed only (future default)
  # 1 : all = failed & passed (current default, future default for no comparison)
  # 2 : marked for update
  # 3 : marking examined / recording results
  # 11: all with plots (very slow to load)
  
  $viewmode = ($singleFile ? 1 : 0);
  $viewmode = 1;
  getPassedInt("viewmode",1);
  
  if ($viewmode == 2) {
    inclR("refSelector.php");
    inclR("refMarks.php");
    readMarks();
    jstart();
    if ($combJob) {
      $useRuns[] = 0;
    } else {
      inclR("refRunFileInfo.php");
      $finfo = getInfoFromFilename($inputfile); # needs modified for combined?
      $useRuns[] = $finfo['runNumber'];
    }
    initRefSelectors(1,$useRuns[0]);  
    ?>
    function prepReady(val) {
      document.choiceForm.trig.value = val;
      document.choiceForm.runYear.value = document.choiceForm.sel1.value;
    }
<?php
    jend();
  }
  
  global $bcols;
  $bcols = array('pass' => array("#dfec9f","#ebf8ab","passed"),
                 'fail' => array("#ffbc8f","#ffc89b","failed"),
                 'ques' => array("#ffec9f","#fff8ab","questionable"),
                 'none' => array("#dddddd","#ebebeb","no cut"));
  function spanbcol($colkey) {
    global $bcols;
    return "<span style=\"background-color:" . $bcols[$colkey][0] .
      "\">" . $bcols[$colkey][2] . "</span>";
  }
  
  $thl = "<th align=left>";
  $thc = "<th align=center>";
  $thr = "<th align=right>";
  $tdl = "<td align=left>";
  $tdc = "<td align=center>";
  $tdr = "<td align=right>";

  print "\n<h3>";
  if ($singleFile) {
    print "Histogram list <nobr>(all";
  } else {
    print "Results of histogram analysis to reference <nobr>(";
    print spanbcol('fail') . ($viewmode ?
           "/" . spanbcol('ques') . "/" . spanbcol('pass') . "/" . spanbcol('none')
           : " only");
  }
  print ")</nobr></h3>\n";
  print "<table border=0 cellpadding=0 cellspacing=3 width=\"96%\">\n<tr>\n";
  if ($doPageCell) { print "<tr>${thl}Page</th>${thl}Cell</th>"; }
  print "${thl}Histogram Name</th>\n";
  print "${thr}( Result</th>${thc}&le;&ge;</th><th align=left colspan=2>Cut )</th></tr>\n";
  
  $user = "";
  $files = array();
  if ($viewmode == 3) {
    inclR("refRunFileInfo.php");
    if ($combJob || isRunNum($inputfile)) {
      incl("files.php");
      global $DAEMON_OUTPUT_DIR;
      $user_dir2 = ($combJob ? userRefDir($user_dir,$combID) : $DAEMON_OUTPUT_DIR . $user_dir);
      $files = readText2Array("${user_dir2}/filelist.txt");
      foreach ($files as $k => $file) {
        # A bit crude for cleaning the filenames, but it works
        $file = preg_replace("/\n/","",$file);
        $file = preg_replace("/\.hist\.root$/","",stripDaq($file));
        $files[$k] = preg_replace("/.*\//","",$file);
      }
    } else {
      $files[] = $inputfile;
    }
    $user = readUserName($user_dir);
    recordStatusForFiles($user,$files);
    $go_back = true;
  }

  $any_yet = 1;
  $hist_idx = 1;
  $colspan = ($doPageCell ? 7 : 5);
  
  foreach ($res as $TR => $typdata) {
    $none_yet = 1;
    foreach ($typdata as $pg => $pgdata) {
      foreach ($pgdata as $cl => $cldata) {
        $name = $cldata['name'];
        $analRes = floatval($cldata['result']);
        $namedCut = getCutForName($name,$cuts);
        $cut = ($namedCut ? floatval($cuts[$namedCut['name']]['cut']) : 0);
        
        $failed = ($analRes < $cut);
        $questionable = ($analRes >= $cut && $analRes - $cut < 0.1 * (1 - $cut));
        if ($viewmode == 3 && $refID >= 0) { recordResultsForFiles($user,$name,$analRes,$refID,$cut,$files); }
        $list_it = ($viewmode == 2 ? markExists($name) : ($failed || $viewmode));
        if ($list_it) {
          if ($none_yet) {
            print "<tr><td colspan=${colspan} align=center><br><i><u>" . $trigs[$TR]
                . " Histograms</u></i></td></tr>\n";
            $none_yet = 0;
            $any_yet = 0;
          }
          $colkey = ($namedCut ? ($failed ? 'fail' : ($questionable ? 'ques' : 'pass')) : 'none');
          $bcol = $bcols[$colkey][1 - $hist_idx % 2];
          $tdl2 = "<td align=left bgcolor=\"${bcol}\">";
          $tdl3 = "<td align=left bgcolor=\"${bcol}\" ondblclick=\"ViewHistTitle(${hist_idx},'${name}')\">";
          print "<tr>";
          if ($doPageCell) { print "${tdl}${pg}</td>${tdl}${cl}</td>"; }
          print "${tdl3}<b>${name}</b><div id=\"histTitle${hist_idx}\" style=\"width:225px;\">";
          print "</div></td>";

          if ($singleFile) { $analRes = "<font size=-1><i>N/A</i></font>"; }
          print "${tdr}<nobr>( ${analRes}</nobr></td>";
          print "${tdc}&" . ($failed ? "lt" : "ge") . ";</td>${tdl}<nobr>${cut} )</nobr></td>";
          print "${tdl2}";
          fbutton("bb${$TR}_${pg}_${cl}",($edit ? "Edit" : "Examine"),"runEdit('${TR}',${pg},${cl},${edit})");
          print "</td></tr>\n";
          # GGG
          if ($viewmode == 11) {
            print "<tr><td colspan=${colspan} align=left><div style=\"background-color:${bcol}; display: table; \">\n";
            displayPlots($name);
            print "</div><p>";
            print "</td></tr>\n";
          }
          # GGG
          $hist_idx++;
        }
      }
    }
  }
  
  if ($any_yet) {
    $colspan--;
    print "<tr><td colspan=${colspan} align=center><br><i><u>none found</u></i></td></tr>\n";
  }
  print "</table>\n";

  #execSys();
  
  if ($viewmode == 2) {
    # Display form for updating references
    fstart("choiceForm","refUpdater.php","QARnfr");
    fhidden("topic",3);
    fhidden("user_dir",$user_dir);
    print "<hr>\n<h3>Reference Histogram Updating:</h3>\n";
    print "Please select the datasets to assign this reference set.";
    print " You may select from already existing datasets (creating a new version)";
    print " or enter a different dataset run year and/or trigger:\n<font size=-1>";
    print "(please use wisely)\n";
    $lcnt = selectYTV();
    $lcnt++;
    fhidden("runYear",0);
    fhidden("trig","");
    print "Comments about this version:<br>\n";
    ftext("comments","",5,55);

    print "<br><br><font size=-1>\n";
    $grpName = "allOrSome";
    $defValue[$grpName] = "marked";
    fradio("radio",$grpName,$defValue,"marked");
    print "Update only marked histograms<br>\n";
    fradio("radio",$grpName,$defValue,"all");
    print "Update all histograms (please be careful!)\n</font><br>\n";
    print "<span id=\"refSelected\" style=\"display:none ;z-index:${lcnt}\">\n";
    fbutton("updateIt","Submit new reference","document.choiceForm.submit();document.dispForm.submit()");
    print "</span>\n";
    $lcnt++;
    print "<span id=\"refNotSelected\" style=\"display:inline ;z-index:${lcnt}\">";
    print "<i>Please finish selecting tags.</i></span>\n";
    
    fend();
  }
  print "<br><br>\n";
  
  jstart();
  ?>
    var curNum = -1;
    function ViewHistTitle(num,name) {
      if (num == curNum) {
        hideElem("histTitle" + curNum);
        curNum = -1;
        return;
      }
      $.ajax({
             url : "refHistTitle.php?name=" + name,
             success : function (data) {
             $("#histTitle" + num).html(data);
             showElem("histTitle" + num);
             if (curNum>0) hideElem("histTitle" + curNum);
             curNum = num;
             }
             });
    }
<?php
  jend();
  
?>
