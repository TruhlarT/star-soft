<?php
  @(include "setup.php") or die("Problems (0).");
  incl("report.php");
  
  
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
  getPassedVarStrict("repnum",1);
  
  
  # Passed only a runnumber or report number (FastOffline only):
  if (!$mode) {
    if ($run) {
      $mode = 3;
      $runstr = strval($run);
      $yeardigits = strlen($runstr)-6;
      $runyear = intval(substr($runstr,0,$yeardigits));
      $runday = intval(substr($runstr,$yeardigits,3));
    } else if ($repnum) {
      $mode = 13;
    }
  }
  
  $byrun = 0;
  $byrep = 0;
  $showrep = 0;
  $textFromDB = 0;
  
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
    getPassedVarStrict("reptype");
    getPassedInt("repyrmo",1);
    if ((!cleanRepType($reptype)) ||
	($mode > 11 && (!$repyrmo || $repyrmo > 209999)) ||
	($mode > 12 && (!$repnum || intval($repnum) > 9999)) ||
	($mode > 13)) $mode = 0;
    else $byrep = 1;
  } else if ($mode < 0) {
    if ($QAdebug) {
      if ($mode==-99) {
        # special copy rFSI mode for experts only
        $Rdir = $bdir . "runFileSeqIndex/";
        foreach (dirlist($Rdir,"","",1) as $kry => $runyears) {
          $RYdir = $Rdir . $runyears ."/";
          foreach (dirlist($RYdir,"","",1) as $krd => $rundays) {
            $RYDdir = $RYdir . nDigits(3,$rundays) . "/";
            foreach (dirlist($RYDdir,"","",1) as $k => $fname) {
              $fnames = split("[_.]",$fname);
              $reptypes = ($fnames[3] == "fast" ? $kFAST : $kOFFL);
              $link = readText($RYDdir . $fname);
              $link = substr($link,strpos($link,"Report"));
              $sublink = split("[_.]",$link);
              $repnums = strval($sublink[3]);
              $pos = strrpos($link,"#");
              if ($pos === false) $link = "";
              else $link = substr($link,$pos+1);
              saveLinkDB($reptypes,$fnames[0],$fnames[1],$link,$repnums);
            }
          }
        }
      } else if ($mode==-98) {
        # special copy reports mode for experts only
        foreach ($repFO as $kFO => $reptypes) {
          $Adir = $bdir . "archive";
          if ($reptypes == $kFAST) $Adir .= "Online";
          foreach (dirlist($Adir,"","",1) as $kYM => $fYM) {
            $fYMs = split("_",$fYM);
            $AYMdir = "${Adir}/${fYM}/";
            $flist = dirlist($AYMdir,"","",1);
            foreach ($flist as $kRep => $fRep) {
              $fReps = split("[_.]",$fRep);
              $doRep = 0;
              if ($fReps[0] == "Report") {
                if ($fReps[4] == "txt") { # Only do html if both html/txt exist
                  $fR2 = str_replace("txt","html",$fRep);
                  if (count(array_keys($flist,$fR2))<1) $doRep = 1;
                } else $doRep = 1;
              }
              if ($doRep) {
                $reptext = readText($AYMdir . $fRep);
                if (!($fReps[1] == $fYMs[0] && $fReps[2] == $fYMs[1]))
                  logit("WARNING ON COPY Dir = $fYM , File = $fRep");
                saveReportDB($fReps[3],$reptypes,$fReps[1],$fReps[2],$reptext);
              }
            }
          }
        }
      }
    } 
    $mode = 0;
  }

  if ($mode == 4 || $mode == 13) $showrep=1;
  
  
  $repfile = "";

  
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
  if ($QAdebug) {
    fstart("fillRFSI","showRun.php","_top");
    print "<p align=right><font size=-3>";
    print "For debugging only. Please ignore.Mode = $mode\n\n";
    print "," . getNextRepNum($kOFFL) . " , " . getNextRepNum($kFAST) . "\n";
    fhidden("mode",-98); # -99 for copy rFSI, -98 for copy shiftReports
    fsubmit(" ");
    print "</font></p>\n";
    fend();
  }
    
  
  fstart("rform","showRun.php","");
  fhidden("mode",$mode);
  
  ####### By Run ######
  print "<table cellspacing=5 width=\"98%\"><tr><td width=\"53%\">\n";
  if ($byrun) print "<font color=maroon>\n";
  print "By Run year / day / number / sequence :<br>\n";
  if ($byrun) print "</font>\n";
  
  print "<select name=runyear onchange=\"rform.mode.value=1;submit()\">\n";
  print "<option value=0 disabled" . (!$byrun ? " selected" : "") . ">year</option>\n";
  $result = getLinksDB();
  while ($row = nextDBrow($result)) {
    $runyears = intval($row['runYear']);
    print "<option value=$runyears";
    if ($byrun && $runyears == $runyear) print " selected";
    print ">$runyears</option>\n";
  }
  if ($byrun) {
    print "</select> / <select name=runday onchange=\"rform.mode.value=2;submit()\">\n";
    print "<option value=0 disabled" . ($mode==1 ? " selected" : "") . ">day</option>\n";
    $result = getLinksDB($runyear);
    while ($row = nextDBrow($result)) {
      $rundays = intval($row['runDay']);
      print "<option value=$rundays";
      if ($mode > 1 && $rundays == $runday) print " selected";
      print ">$rundays</option>\n";
    }
    if ($mode > 1) {
      print "</select> / <select name=run onchange=\"rform.mode.value=3;submit()\">\n";
      print "<option value=0 disabled" . ($mode==2 ? " selected" : "") . ">number</option>\n";
      $result = getLinksDB($runyear,$runday);
      while ($row = nextDBrow($result)) {
	$runs = intval($row['run']);
	print "<option value=$runs";
	if ($mode > 2 && $runs == $run) print " selected";
	print ">$runs</option>\n";
      }
      if ($mode > 2) {
        $result = getLinksDB($runyear,$runday,$run);
	$runIndices = 0;
	$prevtype = "first";
	while ($row = nextDBrow($result)) {
	  $runIndices++;
	  $reptypes = $repFO[$row['RepType']];
	  $seq = $row['seq']; # might start with zeros or have "NA"
	  $idx = intval($row['idx']);
	  if ($reptypes != $prevtype) {
	    if ($prevtype == "first"){
	      print "</select> / <select name=runIndex onchange=\"rform.mode.value=4;submit()\">\n";
	      print "<option value=0 disabled" . ($mode==3 ? " selected" : "") . ">sequence</option>\n";
	    } else {
	      print "</optgroup>\n";  
	    }
	    print "<optgroup label=\"$reptypes\">\n";
	    $prevtype = $reptypes;
	  }
	  print "<option value=$runIndices";
	  if ($mode > 3 && $runIndices == $runIndex) {
	    print " selected";
            $repnums = strval($row['RepNum']);
            if (strlen($repnums)) {
              $textFromDB = 1;
              $reptype = $reptypes;
              $repnum = $repnums;
            }
	    $repfile = $row['link'];
	  }
	  print ">$seq ($idx)</option>\n";
	}
	if ($runIndices) {
	  print "</optgroup>\n";
	} else {
	  $mode = 9; # run not found
	}
      }
    }
  }

  ####### By Report ######
  print "</select>\n\n";
  print "</td><td width=\"45%\">\n";
  if ($byrep) print "<font color=maroon>\n";
  print "By Report type / year / month / number :<br>\n";
  if ($byrep) print "</font>\n";
  
  print "<select name=reptype onchange=\"rform.mode.value=11;submit()\">\n";
  print "<option value=0 disabled" . (!$byrep ? " selected" : "") . ">type</option>\n";
  foreach ($repFO as $k => $reptypes) {
    print "<option value=$reptypes";
    if ($byrep && $reptype==$reptypes) print " selected";
    print ">$reptypes</option>\n";
  }
  if ($byrep) {
    print "</select> / <select name=repyrmo onchange=\"rform.mode.value=12;submit()\">\n";
    print "<option value=0 disabled" . ($mode==11 ? " selected" : "") . ">year/month</option>\n";
    $result = getReportYrMos($reptype);
    $oldyear = 0;
    while ($row = nextDBrow($result)) {
      $repyr = intval($row['RepYear']);
      $repmo = intval($row['RepMonth']);
      if ($repyr != $oldyear) {
	if ($oldyear) print "</optgroup>\n";
	print "<optgroup label=$repyr\n";
	$oldyear = $repyr;
      }
      $yrmo = $repyr*100 + $repmo;
      print "<option value=$yrmo";
      if ($mode > 11 && $yrmo == $repyrmo)  print " selected";
      print ">$repyr / $repmo</option>\n";
    }
    print "</optgroup>\n";
    if ($mode > 11) {
      $repyrmostr = strval($repyrmo);
      $repyr = intval(substr($repyrmostr,0,4));
      $repmo = intval(substr($repyrmostr,4,2));
      print "</select> / <select name=repnum onchange=\"rform.mode.value=13;submit()\">\n";
      print "<option value=0 disabled" . ($mode==12 ? " selected" : "") . ">number</option>\n";
      $result = getReportNums($reptype,$repyr,$repmo);
      while ($row = nextDBrow($result)) {
	$repnums = strval($row['RepNum']);
	print "<option value=\"$repnums\"";
	if ($mode > 12 && $repnums == $repnum) print " selected";
	print ">$repnums</option>\n";	
      }
      if ($mode > 12) $textFromDB = 1;
    }
  }
  
  print "</select>\n";
  print "</td></tr></table>\n\n<hr size=3 noshade>\n";
  
  fend();
  print "</div>\n";


  ####### Display Report ######
  if ($mode==9) {
    print "<h3>No availble reports for run $run. Please select a different run from the above menus.</h3>\n\n";
  } else if ($mode==3) {
    print "<h3>Please select from the above menu of file sequences for availble reports on run $run</h3>\n\n";
  }
  print "</div>\n";
  if ($showrep) {
    if ($QAdebug) logit("Getting report from DB? $textFromDB");
    if ($textFromDB) {
      $row = readReportDB($repnum,$reptype,0);
      $reptext = $row['RepText'];
      $doPre = 1;
      if (substr($reptxt,0,6) == "<html>") $doPre = 0;
      print "<div id=vwr style=\"position:absolute; width:98%; bottom:0; height:80%;\n";
      print "   z-index:0; border-style:groove none none; \" >";
      if ($doPre) print "<pre>";
      print "$reptext";      
      if ($doPre) print "</pre>";
      print "\n</div>\n";      

# The txt files might be better handled with objects anyhow...

/*
      #print "$reptext\n<a href=#$repfile>GEE</a>\n</div>\n";      
#try to move to anchor
logit("TTT $repfile");
      if (strlen($repfile)) {
        jstart();
        print "   document.getElementById('vwr').location=\"#$repfile\";\n";
        print "   setTimeout(\"alert('HERE: ' + document.getElementById('vwr').hasAttribute('location'))\",1000);\n";
        jend();
print "<a href=#$repfile>GO</a>\n";
      }
*/
    } else {
      print "<object style=\"position:absolute; width:98%; bottom:0; height:80%;\n";
      print "   z-index:0; border-style:groove none none; \"";
      print "   data=\"$repfile\" >\n";
      print "<a href=\"$repfile\">Report</a>\n</object>\n";      
    }
  }
  
  foot();
?>
