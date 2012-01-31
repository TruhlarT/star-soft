<?php
  
  inclR("refRunFileInfo.php");
  
  global $jfuncstr,$l0str,$l1str,$l2strs,$refMenuMode,$idcnt,$defSelTag;
  $l0str = "";
  $l1str = "";
  $l2str = "";
  $refMenuMode = 2;
  $idcnt = 0;
  
  function selectedTag($i,$j) { return 10000*$i + $j; }
  $defSelTag = selectedTag(0,0);

  function jselectors() {
    global $jfuncstr;
    jhideshow();
    ?>
    function refSelector(lvl,cnt,prnt,slctidx) {
      this.level = lvl;
      this.count = cnt;
      this.parent = prnt;
      this.selectidx = slctidx;
    }
    var selectors = new Object;
    function selName(sel) { return 'sel' + sel; }
    function hideSel(level) {
      for (var sels in selectors) {
        if (selectors[sels].level >= level) hideElem(selName(sels));
      }
      hideElem('refSelected'); showElem('refNotSelected');
    }
    function showSel(sel,force) {
      level = selectors[sel].level;
      if (level < 2) hideSel(level + 1);
      if (level == 2 || (level == 1 && force == 1)) {
        readElem = eval("document.choiceForm." + selName(sel));
        prepReady(readElem.options[readElem.selectedIndex].value);
        showElem('refSelected'); hideElem('refNotSelected');
        if (level == 2) return;
      }
      parSel = eval("document.choiceForm.sel" + sel);
      idx = parSel.selectedIndex;
      for (var sels in selectors) {
        if ((selectors[sels].parent == sel) &&
            (selectors[sels].selectidx == idx)) {
          showElem(selName(sels));
          if (selectors[sels].count == 1) {
            showSel(sels,0);
          }
        }
      }
    }
<?php
    print $jfuncstr;
  }
  
  
  function makemenu($enums,$level,$parent,$parent_idx,$defaultEnum=-1) {
    global $refMenuMode,$idcnt,$jfuncstr,$defSelTag;
    $action = ""; $fullySelected = false;
    $cnt = count($enums);
    $idcnt++;
    $showing = (selectedTag($parent,$parent_idx) == $defSelTag);
    $ename = "sel" . $idcnt;
    $str = "<span id=\"$ename\" style=\"display:"
      . ($showing ? "inline" : "none")
      . " ;z-index:${idcnt}\">\n";

    if ($level == 2 && $refMenuMode == 1) {
      $enum_keys = array_keys($enums);
      $last_vers = $enum_keys[0];
      if ($cnt==0) {
	    $str.="none\n";
      } else {
	    $str.= "${last_vers} (" . strtok($enums["$last_vers"]['entryTime']," ") . ")\n";
      }
      $cnt = 1;
    } else {
      # $force==1 makes the submit button appear (forces past level 2)
      $force = ($level==1 && $refMenuMode==1 ? 1 : 0);
      $action = "showSel(${idcnt},${force})";
      $str.= onSelect($ename,$action);
      
      $enumI = 0;
      foreach ($enums as $k => $v) {
        $selected = "";
        # show child element if this is default, or only enum
        #if ($showing && (($cnt==1) || ($v==$defaultEnum))) {
        if ($showing && (($cnt==1) || ($v==$defaultEnum) ||
                         ($defaultEnum==-1 && $enumI==0))) {
          $defSelTag = selectedTag($idcnt,$k);
          $selected = "selected ";
          if ($level==2) { $fullySelected = true; }
        }
        $str.= "<option ${selected}value=\"";
        if ($level==2) {
          $str.= $v['id'] . "\">${k} (" . strtok($v['entryTime']," ") . ")";
        } else {
          $str.= "${v}\">${v}";
        }
        $str.= "</option>\n";
        $enumI++;
      }
      $str.= "</select>\n";
      $str.= "<input type=button name=\"advance${idcnt}\" value=\"&"
      . ($level==2 ? "c" : "") . "rarr;\" onclick=\"${action}\">\n";
    }
    $str.= "</span>\n";
    $jfuncstr .= "    selectors[${idcnt}] ="
    . " new refSelector(${level},${cnt},${parent},${parent_idx});\n";
    if ($fullySelected) { $jfuncstr .= "    setTimeout('${action}',150);\n"; }
    return $str;
  }
  
  
  function initRefSelectors($mode=2,$runNumber=0) {
    # Get list of runYears/trig/vers+entryTime
    # Should be called from within a jstart()
    # $mode:
    #   1 : new version menu
    #   2 : existing versions menu
    global $l0str,$l1str,$l2str,$refMenuMode,$idcnt;
    $refMenuMode = $mode;
    $runYearTrig = getYTfromRun($runNumber);
    $runYears = array();
    if ($refMenuMode == 1) { $runYears[] = $runYearTrig['runYear']; }
    else { $runYears = getRunYearList(); }
    $l0str .= makemenu($runYears,0,0,0,$runYearTrig['runYear']);
    foreach ($runYears as $kc => $runYear) {
      $trigs = ($refMenuMode == 1 ? getTrigListAll($runYear) : getTrigList($runYear));
      $l1str .= makemenu($trigs,1,1,$kc,$runYearTrig['trig']);
      $parent = $idcnt;
      $trigvers = array();
      foreach ($trigs as $kt => $trig) {
	    $trigvers["$trig"] = getVersList($runYear,$trig);
	    $l2str .= makemenu($trigvers["$trig"],2,$parent,$kt);
      }
    }
    jselectors();
  }
  

  function selectYTV() {
    global $l0str,$l1str,$l2str,$idcnt,$refMenuMode;
    print "<font size=-1>\n";
    print "<table border=0 cellpadding=6 cellspacing=0><tr valign=top><td>\n";
    print "Run Year:<br>${l0str}\n\n";
    print "</td><td>\n";
    print "Trigger Setup:<br>${l1str}\n\n";
    print "</td><td>\n";
    if ($refMenuMode == 1) { print "Latest "; }
    print "Version:<br>${l2str}\n\n";
    print "</td></tr></table>\n";
    print "</font>\n";
    $idcnt++;
    return $idcnt;
  }
  
?>
