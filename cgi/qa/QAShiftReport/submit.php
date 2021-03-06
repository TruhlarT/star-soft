<?php

@(include "setup.php") or die("Problems (0).");
incl("data2text.php");
incl("report.php");


getPassedVarStrict("mode");
if ($mode == "none") { died("mode not set"); }

$ses = needSesName();
$sesDir = GetSesDir($ses);
$play = isPlaySes($ses);

# Save the wrapup:
saveWrapup($_POST,$ses);

# Go back to contents if only saving:
if ($mode == "SaveIt") {
  header("location: ${webdir}contents.php?mode=View");
  exit;
}

###################################################################

@(include "shiftLog.php") or die("Problems (3).");

#################################
# Prepare for archiving
#

$start = "STAR QA Shift Report";
$startSum = $start . " Summary";
$startTxt = array($kOFFL => $startSum, $kFAST => $startSum . " (FAST OFFLINE)");

$submErrs = array( 5 => "mail failure (possibly an invalid email address)",
                  11 => "invalid date",
                  12 => "invalid shift person name",
                  13 => "invalid string");


$allents = "InfoWrapup";
$info = data2text($allents);

readInfo($ses);
$dateyf = nDigits(4,strval(2000 + intval($shift["datey"])));
$datemf = nDigits(2,$shift["datem"]);
$datedf = nDigits(2,$shift["dated"]);
$datestr = $dateyf . "_" . $datemf;
$datestr2 = "${datemf}/${datedf}/${dateyf}";

$fast = $kFAST;
$repnum = 0;
$toFolks = array(
  "Test" => array($kOFFL => "squonk@alum.mit.edu",
                  $kFAST => "gene@cs.wustl.edu"),
#  "Real" => array($kOFFL => "production-hn@www.star.bnl.gov",
#                  $kFAST => "shiftreport-hn@www.star.bnl.gov")
  "Real" => array($kOFFL => "starqa-hn@www.star.bnl.gov",
                  $kFAST => "starqa-hn@www.star.bnl.gov")
);

###################################################################


#################################
# Sort through the Issues
#

$typecounts = array();
$typecounts["all"] = 0;

$allissues = array();
$allnewissues = array();
$allgoneissues = array();
$allRunFileSeqs = array();
$allRunIssues = array();

foreach ($ents as $typ => $entN) {
  $entFiles = dirlist($sesDir,$typ,".data");
  sort($entFiles);
  $typecounts[$typ] = count($entFiles);
  if ($typecounts[$typ] == 0) { continue; }
  $typecounts["all"] += $typecounts[$typ];
  $oldtypeissues = readIssLast($typ);

  $typeissues = array();
  $runFileSeqs = array();
  foreach ($entFiles as $k => $entFile) {
    $allents .= d2tdelim() . $entFile;
    if ($entr = readObjectEntry($sesDir . $entFile)) {
      $typeissues += $entr->issues;
      $entrRun = $entr->info["runid"];
      if (! is_array($entrRun)) { $entrRun = array($entrRun); }
      foreach ($entrRun as $runid) {
        $runFileSeqs[] = array($runid,$entr->info["fseq"],$entr->info["fstream"],$entr->Anchor());

        # Compile list of runs for each issue
        if (count($entr->issues) > 0) {
          foreach ($entr->issues as $id => $isstxt) {
            $allRunIssues[$id][] = $runid;
          }
        } else {
          # no issues
          $allRunIssues["0"][] = $runid;
        }
      }
    }
  }
  $allissues[$typ] = $typeissues;
  if (! $play) { writeIssLast($typeissues,$typ); }
  $allRunFileSeqs[$typ] = $runFileSeqs;

  # Check for new issues
  $newissues = array();
  foreach ($typeissues as $id => $isstxt) {
    if (!isset($oldtypeissues[$id])) {
      $newissues[$id] = getCategoryForIssue($id) . " : " . $isstxt;
    }
  }
  $allnewissues[$typ] = $newissues;

  # Check for gone issues
  $goneissues = array();
  foreach ($oldtypeissues as $id => $isstxt) {
    if (!isset($typeissues[$id])) {
      $goneissues[$id] = getCategoryForIssue($id) . " : " . $isstxt;
    }
  }
  $allgoneissues[$typ] = $goneissues;

}

# Update the run-issue index
if (! $play) { updateRunIssueIndex($allRunIssues); }


###################################################################


#################################
# Functions for creating archives
#

# Put a copy of the full report in the appropriate archive directory
function Archive() {
  global $reportFile,$datestr,$fast,$kFAST,$bdir,$dateyf,$datemf,$repnum;
  $archDir = "archive";
  if ($fast == $kFAST) $archDir .= "Online";
  $archDir .= "/";
  $repnum = getNextRepNum($fast);
  $webFile = "${archDir}${datestr}/Report_${datestr}_${repnum}.html";
  $archFile = $bdir . $webFile;
  ckdir(dirname($archFile));
  copy($reportFile,$archFile);
  saveReportDB($repnum,$fast,$dateyf,$datemf,readText($reportFile));
}

# Put a link to the full report in the appropriate runFileSeq directory
function LinkArchive($typ) {
  global $allRunFileSeqs,$datestr,$fast,$repnum;
  foreach ($allRunFileSeqs[$typ] as $k => $rfs) {
    $runid = strval($rfs[0]);
    $yeardigits = strlen($runid)-6;
    $runyear = substr(strval($runid),0,$yeardigits);
    $runday  = substr(strval($runid),$yeardigits,3);
    $fseqf = formatFseq($rfs[1]);
    saveLinkDB($fast,$runid,$fseqf,$rfs[2],$rfs[3],$repnum);
  }
}

# Output text for changed issues since last filed reports
function OutputChangedIssues($typ) {
  global $allnewissues,$allgoneissues,$ents;
  $ostr = "\n";
  if (count($allnewissues[$typ]) + count($allgoneissues[$typ]) > 0) {
    $ostr .= "SUMMARY OF CHANGED ISSUES FOR " . $ents[$typ];
    $ostr .= " (+ new / - gone):\n";
    foreach ($allnewissues[$typ] as $issid => $isstxt) {
      $ostr .= "\n+ [ID:${issid}]  ${isstxt}\n";
      $ostr .= getIssWebLink($issid) . "\n";
    }
    foreach ($allgoneissues[$typ] as $issid => $isstxt) {
      $ostr .= "\n- [ID:${issid}]  ${isstxt}\n";
      $ostr .= getIssWebLink($issid) . "\n";
    }
  } else {
    $ostr .= "ALL " . $ents[$typ] . " ISSUES UNCHANGED.\n";
  }
  return $ostr;
}

# Output text for changed issues since last filed reports
function OutputExaminedRunFseq($typ) {
  global $allRunFileSeqs,$ents;
  $ostr = "";
  if (count($allRunFileSeqs[$typ]) > 0) {
    $ostr .= "\n\nSUMMARY OF RUNS / FILE SEQUENCES EXAMINED FOR " . $ents[$typ];
    foreach ($allRunFileSeqs[$typ] as $k => $rfs) {
      $ostr .= "\n  " . HeadlineRFS($rfs[0],$rfs[1],$rfs[2]);
    }
    $ostr .= "\n";
  }
  return $ostr;
}

# Main routine for archiving/linking/mailing reports & summaries
function ArchAndMail($typs, $sendmail=1) {
  global $startTxt,$info,$sesDir,$webdir,$bdir,$repnum,$play;
  global $fast,$kFAST,$toFolks,$mode,$typecounts,$shift,$datestr2;
  if (! $play) { Archive(); }

  $sumTemp = "";
  foreach ($typs as $typ => $entN) {
    if ($typecounts[$typ] > 0) {
      if (! $play) { LinkArchive($typ); }
      $sumTemp .= OutputChangedIssues($typ);
    }
  }
  reset($typs);
  foreach ($typs as $typ => $entN) {
    if ($typecounts[$typ] > 0) { $sumTemp .= OutputExaminedRunFseq($typ); }
  }

  $fullLink = ($play ? "Not Archived" : $webdir . "showRun.php?reptype=${fast}&repnum=${repnum}");

  # output is the email summary, output2 is for the electronic shift log entry

  $output  = $startTxt[$fast] . "\n\n" . dashdelim() . "\n";
  $output .= $sumTemp . "\n" . $info . "\nFull report archived in:\n";
  $output .= $fullLink . "\n\n";

  $output2  = $startTxt[$fast] . "\n";
  $output2 .= $sumTemp . "\n" . str_replace("----","",$info);
  $output2 .= "\nFull report archived in:\n" . $fullLink;
  
  if ($fast == $kFAST) {
    if (strlen($datestr2)<10) { return 11; }
    if (strlen($shift["name"])<2) { return 12; }
    if (strlen($output2)<4) { return 13; }
    if (! $play) { PrepShiftLog($datestr2,$shift["name"],$output2); }
  }

  $summaryFile = "${sesDir}Summary.${fast}.txt";
  saveText($output,$summaryFile);
  
  if ($sendmail == 0) { return 0; }

  $testReal = "Test";
  if ($mode != "TestIt") { $testReal = "Real"; }
  $to = $toFolks[$testReal][$fast];
  $toalso = $_POST["originator"];
  if (strlen($toalso) > 0) { $to .= "," . $toalso; }
  if ($play) { $to = $toalso; }
  logit("submit: (reptype=${fast}) sending mail to $to");
  $mailResult = mail($to,$startTxt[$fast],$output);
  if (!$mailResult) {
    logit("submit: mail failed for reptype=$fast"); 
    return 5;
  }
  return 0;
}


# Output if the submission to the electronic shift log and mail failed
function FailSubmission($code) {
  global $submErrs;
  # Mail the maintainer first
  $mstr = "gene@bnl.gov";
  $sstr = "QA Shift Report Failure";
  $fstr = "QA Shift Report submission failed with code: ${code} = "
    . $submErrs[$code] . "\n";
  $mailResult = mail($mstr,$sstr,$fstr);

  print "<font color=red>Submission Failed</font></h3>\n\n";
  print "<h2>Please do not re-attempt submission.</h2>\n\n";
  print "Please notify <a href=${mstr}>Gene Van Buren</a>\n";
  print "(631-344-7953) that the submission failed with code:\n";
  print "<b>${code}.${mailResult}</b><br>\n<i>";
  print $submErrs[$code] . "</i>\n\n";
  foot();
}

# Output if the submission to the electronic shift log and mail succeeded
function SuccessSubmission() {
  global $play;
  print " <font color=blue>";
  if ($play) { print "Play "; }
  print "Submission Completed Successfully</font></h3>\n\n";
  print "<h2>NEVER SELECT YOUR BROWSER'S RELOAD OR BACK (PREVIOUS PAGE) BUTTONS AFTER REPORT SUBMISSION!</h2>\n\n";
}

###################################################################


#################################
# Report & Summary archives/mails
#

# Full report
$reportFile = $sesDir . "Report.html";
$output = str2page($start,data2html($allents));
saveText($output,$reportFile);


# Summaries
# If there are any FastOffline entries, archive report and prepare summary
# For now, also send summary when there are *no* entries of any kind
if ($typecounts["FRP"] > 0 || $typecounts["all"] == 0) {
  $fast = $kFAST;
  $atyps = array("FRP" => $ents["FRP"]);
  # can use $nofastchanges as second arg of ArchAndMail to mail only when
  # issues change
  #$nofastchanges = count($allnewissues["FRP"]) + count($allgoneissues["FRP"]);
  $aamResult = ArchAndMail($atyps);
  if ($aamResult > 0) { FailSubmission($aamResult); }
}
# If there are any non-FastOffline entries, archive report and mail summary
if ($typecounts["all"] - $typecounts["FRP"] > 0) {
  $fast = $kOFFL;
  $atyps = $ents;
  unset($atyps["FRP"]);
  $aamResult = ArchAndMail($atyps);
  if ($aamResult > 0) { FailSubmission($aamResult); }
}

###################################################################

#################################
# Finish by cleaning up
#


# At the end...delete the report session
if ($mode == "SendIt") {
  rmrf(getSesDir($ses));
  eraseSesName();
  reloadMenu();
}

# Mantain that log files do not get too big.
rotateLog();
optimizeReportsDB();
optimizeIssuesDB();

$postPrepResult = ($play || PostToShiftLog());

head("STAR QA Shift Report Submission");
body();
if ($postPrepResult) { SuccessSubmission(); }
else { FailSubmission(21); }
foot();

?>
