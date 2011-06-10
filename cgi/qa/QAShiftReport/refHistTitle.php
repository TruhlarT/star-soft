<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  @inclR("refCuts.php");
  @inclR("refDesc.php");
  
  getPassedVarStrict("name");
  $dname = stripHistPrefixes($name);
  $desc = getLatestDesc($dname);
  if (!$desc) { $desc = array('title' => "(No Title)", 'desc' => "(No Description)"); }
  
  #print "<i><u>" . $desc['title'] . "</u></i><br><font size=-1>" . $desc['desc'] . "</font>";
  $descName = "histDesc_${name}";
  $moreName = "moreDesc_${name}";
  linebreak();
  print "<i><u>" . $desc['title'] . "</u></i>";
  print "<span id=\"${moreName}\" onclick=\"hideElem('${moreName}');showElem('${descName}')\">";
  print "&nbsp;&nbsp;<font size=-2>(more)</font></span><br>";
  print "<span id=\"${descName}\" style=\"display:none; \"><font size=-1>" . $desc['desc'] . "</font></s[an>";
  
?>
