<?php

global $issSearchVars,$issSearchVarsPassed;
$issSearchVarsPassed = false;
$issSearchVars = array(
  "scateg" => 0,
  "skeyws" => 0,
  "sstrtag" => 1,
  "sstrname" => 1,
  "sstrdesc" => 0,
  "sstr" => "");


# function maybe not needed
function jsForIssueSearch($form) {
  global $issSearchVars;
  print "    function issSearchTransfer() {\n";
  print "      from_form = document.searchIss;\n";
  print "      to_form = document.${form};\n";
  foreach ($issSearchVars as $k => $v) {
    print "      to_form.${k}.value = from_form.${k}.value;\n";
  }
  print "    }\n";
}

function isIssueSearch() {
  global $issSearchVarsPassed;
  return $issSearchVarsPassed;
}

function varsForIssueSearch($pass_along=0) {
  # pass_along =
  # 0: do not pass along
  # 1: pass along if passed
  # 2: pass along regardless
  global $issSearchVars,$issSearchVarsPassed;
  $str_of_passed = "";
  foreach ($issSearchVars as $k => $v) {
    global $$k;
    $was_passed = (is_string($v) ? getPassedVarStrict($k,1) : getPassedInt($k,1));
    if (! $was_passed) {
      $kk = $v;
    } else {
      $issSearchVarsPassed = true;
      $str_of_passed .= "&${k}=" . $$k;
    }
    if ($pass_along == 2 ||
        ($pass_along == 1 && $was_passed)) fhidden($k,$$k);
  }
  return $str_of_passed;
}

function buildIssueSearch($action = "") {
  global $issSearchVars,$issSearchVarsPassed;
  foreach ($issSearchVars as $k => $v)
    global $$k; // issue of scope? may need to be outside loop
  foreach ($issSearchVars as $k => $v)

  $stand_alone = (strlen($action) == 0);

  if ($issSearchVarsPassed) {
    global $issueRestrict;
    if (strlen($sstr) > 0) {
      $ar1 = array();
      $ar2 = array();
      $ar3 = array();
      if ($sstrtag) $ar1 = getListOfIssuesForTagString($sstr);
      if ($sstrname) $ar2 = getListOfIssuesForNameString($sstr);
      if ($sstrdesc) $ar3 = getListOfIssuesForDescString($sstr);
      $issueRestrict = array_merge($ar1,$ar2,$ar3); // AND
    }
    $restricted=array();
    if ($scateg!=0) $restricted[] = array("Categories",$scateg);
    if ($skeyws!=0) $restricted[] = array("Keywords",$skeyws);
    if (count($restricted)) {
      if (count($issueRestrict)) {
        $ar1 = $issueRestrict;
        $ar2 = getListOfIssuesForTags($restricted);
        $issueRestrict = array_intersect($ar1,$ar2); // OR
      } else {
	getListOfIssuesForTags($restricted);
      }
    }
  }
  
  if ($stand_alone) fstart("searchIss","","_top");
  print "<table border=1 cellpadding=0 cellspacing=0 bgcolor=\"#ffbc9f\"><tr><td>\n";
  print "<table border=0 cellpadding=0 cellspacing=0 bgcolor=\"#ffbc9f\">\n";
  print "<tr><td rowspan=2 valign=middle>";
  print "<b>Filter</b> issues<br>using...</td>\n";
  print "<td rowspan=3>&nbsp;</td>\n";
  print "<td rowspan=3 bgcolor=\"#C08080\">&nbsp;</td>\n";
  print "<td rowspan=3>&nbsp;</td>\n";
  print "<td>tags:";
  print printCategorySelector("scateg",0,$scateg);
  #print "</td>\n<td>";
  print printKeywordSelector("skeyws",$skeyws);
  #print "</td>\n<td>";
  print "</td></tr>\n<tr><td>text:";
  finput("sstr",30,$sstr,$action);
  print "<font size=-1>(alphanumerics only)</font></td></tr>\n";
  print "<tr><td>\n";
  fbutton("startsearch","Search",($stand_alone ? "submit()" : $action));
  print "</td><td>&nbsp;&nbsp;in&nbsp;\n";
  print "<nobr><input type=checkbox name=sstrtag value=1" . ($sstrtag ? " checked" : "");
  print ">issue tags</nobr>&nbsp;\n";
  print "<nobr><input type=checkbox name=sstrname value=1" . ($sstrname || !$issSearchVarsPassed ? " checked" : "");
  print ">issue names</nobr>&nbsp;\n";
  print "<nobr><input type=checkbox name=sstrdesc value=1" . ($sstrdesc ? " checked" : "");
  print ">issue descriptions</nobr>\n";
  print "</td></tr>\n<tr><td colspan=5><font size=-1>";
  print "(Issues listed below will be subject to these search criteria; 'text' field must not be blank.)</font>";
  print "</td></tr></table>\n";
  print "</td></tr></table>\n";
  if ($stand_alone) fend();
  
}

?>
