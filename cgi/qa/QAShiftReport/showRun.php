<?php
include("setup.php");


# Request mode
# 0 nothing
# 1 know run year
# 2 know run day
# 3 know run number
# 4 know run report
# 11 know report offline / fast offline
# 12 know report year_month
# 13 know report number

$mode = 0;
getPassedInt("mode",1);

$run = 0;
getPassedInt("run",1);
getPassedInt("runyear",1);
getPassedInt("runday",1);


# Passed only a runnumber:
if (!$mode && $run) {
  $mode = 3;
  $runstr = strval($run);
  $yeardigits = strlen($runstr)-6;
  $runyear = intval(substr($runstr,0,$yeardigits));
  $runday = intval(substr($runstr,$yeardigits,3));
}

$byrun = 0;
$byrep = 0;
$showrep = 0;

# Strict checking of passed parameters:
if ($mode > 0 && $mode < 10) { # By run
  getPassedInt("runIndex",1);
  if ((!$runyear || $runyear > 99) ||
      ($mode > 1 && (!$runday || $runday > 366)) ||
      ($mode > 2 && ($run < 1000000 || $run > 99999999)) ||
      ($mode > 3 && $runIndex>999) ||
      ($mode > 4)) $mode = 0;
  else $byrun = 1;
} else if ($mode > 10) { # By report
  getPassedInt("reptype");
  getPassedInt("repyrmo",1);
  getPassedVarStrict("repnum",1);
  if ((!$reptype || $reptype > 2) ||
      ($mode > 11 && (!$repyrmo || $repyrmo > 209999)) ||
      ($mode > 12 && (!$repnum || intval($repnum) > 9999)) ||
      ($mode > 13)) $mode = 0;
  else $byrep = 1;
} else if ($mode < 0) $mode = 0;
if ($mode == 4 || $mode == 13) $showrep=1;


$repfile = "";
$replistFast = array();
$replist = array();


#######################
# Begin Page

head("STAR QA Shift Report Archives");
if ($showrep) {
  jstart();
  ?>
     function showMenus() {
       document.getElementById('menus').style.display = 'block';
       return false;
     }
     function hideMenus() {
       document.getElementById('menus').style.display = 'none';
       return false;
     }
  <?php
  jend();
}
body();
?>

<div style="position:absolute; top:0; width:98%; z-index:1; "
<?php if ($showrep) { ?>  onmouseover="showMenus()" onmouseout="hideMenus()"<?php } ?>>

<h1>STAR QA Shift Report Archives</h1>

<span style="background-color:#ffbc9f; "><b>Please select a report:</b></span>

  <div id=menus style="position:relative; z-index:2;
     background-color:#ffdc9f;
     display:<?php print ($showrep ? "none" : "block"); ?> " >


<?php
#print "Mode = $mode\n\n"; # for debugging purposes

fstart("rform","showRun.php","");
fhidden("mode",$mode);

print "<table cellspacing=5 width=\"98%\"><tr><td width=\"53%\">\n";
if ($byrun) print "<font color=maroon>\n";
print "By Run year / day / number / sequence :<br>\n";
if ($byrun) print "</font>\n";

print "<select name=runyear onchange=\"rform.mode.value=1;submit()\">\n";
$byrundir = $hdir . "runFileSeqIndex/";
print "<option value=0 disabled" . (!$byrun ? " selected" : "") . ">year</option>\n";
foreach (dirlist($byrundir,"","",1) as $k => $runyears) {
  print "<option value=$runyears";
  if ($byrun && $runyears == $runyear) print " selected";
  print ">$runyears</option>\n";
}
if ($byrun) {
  print "</select> / <select name=runday onchange=\"rform.mode.value=2;submit()\">\n";
  print "<option value=0 disabled" . ($mode==1 ? " selected" : "") . ">day</option>\n";
  $byrunyeardir = $byrundir . $runyear . "/";
  foreach (dirlist($byrunyeardir,"","",1) as $k => $rundays) {
    print "<option value=$rundays";
    if ($mode > 1 && $rundays == $runday) print " selected";
    print ">$rundays</option>\n";
  }
  if ($mode > 1) {
    print "</select> / <select name=run onchange=\"rform.mode.value=3;submit()\">\n";
    print "<option value=0 disabled" . ($mode==2 ? " selected" : "") . ">number</option>\n";
    $byrundaydir = $byrunyeardir . nDigits(3,$runday) . "/";
    $runslist = array();
    foreach (dirlist($byrundaydir,"","",1) as $k => $fname) {
      $fnames = split("[_.]",$fname);
      $runslist[$fnames[0]] = 1;
      if ($mode > 2 && $fnames[0] == $run) {
        $link = readText($byrundaydir . $fname);
        if (substr($link,0,5) != "/STAR") $link = "/STAR" . $link;
        if ($fnames[3] == "fast") $replistFast[] = array($fnames[1],$fnames[2],$link);
        else $replist[] = array($fnames[1],$fnames[2],$link);
      }
    }
    foreach ($runslist as $runs => $val) {
      print "<option value=$runs";
      if ($mode > 2 && $runs == $run) print " selected";
      print ">$runs</option>\n";
    }
    if ($mode > 2) {
      if (count($replistFast) + count($replist) == 0) {
        $mode=9;
      } else {
        print "</select> / <select name=runIndex onchange=\"rform.mode.value=4;submit()\">\n";
        print "<option value=0 disabled" . ($mode==3 ? " selected" : "") . ">sequence</option>\n";
        if (count($replist)) {
          print "<optgroup label=\"Offline\">\n";
          foreach ($replist as $k => $runInfo) {
            $runIndices = intval($k) + 1;
            print "<option value=$runIndices";
            if ($mode > 3 && $runIndices == $runIndex) {
              print " selected";
              $repfile = $webHost . $runInfo[2];
            }
            print ">" . $runInfo[0] . " (" . $runInfo[1] . ")</option>\n";
          }
          print "</optgroup>\n";
        }
        if (count($replistFast)) {
          print "<optgroup label=\"Fast Offline\">\n";
          foreach ($replistFast as $k => $runInfo) {
            $runIndices = intval($k) + 1 + count($replist);
            print "<option value=$runIndices";
            if ($mode > 3 && $runIndices == $runIndex) {
              print " selected";
              $repfile = $webHost . $runInfo[2];
            }
            print ">" . $runInfo[0] . " (" . $runInfo[1] . ")</option>\n";
          }
          print "</optgroup>\n";
        }
      }
    }
  }
}

print "</select>\n\n";
print "</td><td width=\"45%\">\n";
if ($byrep) print "<font color=maroon>\n";
print "By Report type / year / month / number :<br>\n";
if ($byrep) print "</font>\n";

print "<select name=reptype onchange=\"rform.mode.value=11;submit()\">\n";
print "<option value=0 disabled" . (!$byrep ? " selected" : "") . ">type</option>\n";
foreach (array("FAST OFFLINE","OFFLINE") as $k => $type) {
  $types = intval($k) + 1;
  print "<option value=$types";
  if ($reptype==$types) print " selected";
  print ">$type</option>\n";
}
if ($byrep) {
  print "</select> / <select name=repyrmo onchange=\"rform.mode.value=12;submit()\">\n";
  print "<option value=0 disabled" . ($mode==11 ? " selected" : "") . ">year/month</option>\n";
  $byrepdir = $hdir . "archive";
  if ($reptype == 1) $byrepdir .= "Online";
  $oldyear = 0;
  $yrmo_subdir = "";
  foreach (dirlist($byrepdir,"","",1) as $k => $fname) {
    $fnames = split("_",$fname);
    $fyear = $fnames[0];
    if (intval($fyear) < 1999) continue; # avoid other files
    if ($fyear != $oldyear) {
      if ($oldyear) print "</optgroup>\n";
      print "<optgroup label=$fyear>\n";
    }
    $fmonth = $fnames[1];
    $fyrmo = $fyear . $fmonth;
    print "<option value=$fyrmo";
    if ($mode > 11 && intval($fyrmo) == $repyrmo) {
      print " selected";
      $yrmo_subdir = $fname;
    }
    print ">$fyear / $fmonth</option>\n";
    $oldyear = $fyear;
  }
  print "</optgroup>\n";
  if ($mode > 11) {
    print "</select> / <select name=repnum onchange=\"rform.mode.value=13;submit()\">\n";
    print "<option value=0 disabled" . ($mode==12 ? " selected" : "") . ">number</option>\n";
    $repslist = array();
    $byrepdatedir = $byrepdir . "/" . $yrmo_subdir;
    foreach (dirlist($byrepdatedir,"","",1) as $k => $fname) {
      $fnames = split("[_.]",$fname);
      if (($fnames[0] == "Report") &&
          (!isset($repslist[$fnames[3]]) || $fnames[4] == "html"))
          $repslist[$fnames[3]] = $fname;
    }
    foreach ($repslist as $repnums => $rfile) {
      print "<option value=$repnums";
      if ($mode > 12 && $repnums == $repnum) {
        print " selected";
        $repfile = substr($byrepdatedir,strlen($hdir)) . "/" . $rfile;
      }
      print ">$repnums</option>\n";
    }
  }
}


print "</select>\n";
print "</td></tr></table>\n\n<hr size=3 noshade>\n";

fend();
print "</div>\n";
if ($mode==9) {
  print "<h3>No availble reports for run $run. Please select a different run from the above menus.</h3>\n\n";
} else if ($mode==3) {
  print "<h3>Please select from the above menu of file sequences for availble reports on run $run</h3>\n\n";
}
print "</div>\n";
if ($showrep) {
  print "<object style=\"position:absolute; width:98%; bottom:0; height:80%;\n";
  print "   z-index:0; border-style:groove none none; \"";
  print "   data=\"$repfile\" >\n";
  print "<a href=\"$repfile\">Report</a>\n</object>\n";
}


foot();
?>
