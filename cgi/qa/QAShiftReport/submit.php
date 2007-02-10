<?php

include "setup.php";
incl("data2text.php");


getPassedVarStrict("mode");
if ($mode == "none") { died("mode not set"); }

$ses = needSesName();
$sesDir = GetSesDir($ses);

# Save the wrapup:
saveWrapup($_POST,$ses);

# Go back to contents if only saving:
if ($mode == "SaveIt") {
  header("location: ${webdir}contents.php?mode=View");
  exit;
}

###################################################################

include "shiftLog.php";

#################################
# Prepare for archiving
#

$start = "STAR QA Shift Report";
$startSum = $start . " Summary";
$startTxt = array($startSum, $startSum . " (FAST OFFLINE)");


$allents = "InfoWrapup";
$info = data2text($allents);

readInfo($ses);
$dateyf = nDigits(4,strval(2000 + intval($shift["datey"])));
$datemf = nDigits(2,$shift["datem"]);
$datedf = nDigits(2,$shift["dated"]);
$datestr = $dateyf . "_" . $datemf;
$datestr2 = "${datemf}/${datedf}/${dateyf}";

$archFile = "";
$webFile = "";
$runFileSeqDir = $bdir . "runFileSeqIndex/";
$runFileSeqIndex = "";
$fast = 1;
$toFolks = array(
  "Test" => array("squonk@alum.mit.edu","gene@cs.wustl.edu"),
#  "Real" => array("production-hn@www.star.bnl.gov","shiftreport-hn@www.star.bnl.gov")
  "Real" => array("starqa-hn@www.star.bnl.gov","starqa-hn@www.star.bnl.gov")
);

# Convert .txt filename to .html
function HfromT($file) {
  return preg_replace("/\.txt$/",".html",$file);
}

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

foreach ($ents as $typ => $entN) {
  $entFiles = dirlist($sesDir,$typ,".data");
  sort($entFiles);
  $typecounts[$typ] = count($entFiles);
  if ($typecounts[$typ] == 0) { continue; }
  $typecounts["all"] += $typecounts[$typ];
  $issueLIndex = getIssIndexL($typ);
  $oldtypeissues = readIssListFile($issueLIndex);

  $typeissues = array();
  $runFileSeqs = array();
  foreach ($entFiles as $k => $entFile) {
    $datFile = $sesDir . $entFile;
    $allents .= d2tdelim() . $datFile;
    if ($entr = readObjectEntry($datFile)) {
      $typeissues += $entr->issues;
      $runFileSeqs[] = array($entr->info["runid"],$entr->info["fseq"],$entr->Anchor());
    }
  }
  $allissues[$typ] = $typeissues;
  writeIssListFile($typeissues,$issueLIndex);
  $allRunFileSeqs[$typ] = $runFileSeqs;

  # Check for new issues
  $newissues = array();
  foreach ($typeissues as $id => $isstxt) {
    if (!isset($oldtypeissues[$id])) { $newissues[$id] = $isstxt; }
  }
  $allnewissues[$typ] = $newissues;

  # Check for gone issues
  $goneissues = array();
  foreach ($oldtypeissues as $id => $isstxt) {
    if (!isset($typeissues[$id])) { $goneissues[$id] = $isstxt; }
  }
  $allgoneissues[$typ] = $goneissues;

}


###################################################################


#################################
# Functions for creating archives
#

# Put a copy of the full report in the appropriate archive directory
function Archive() {
  global $reportFile,$archFile,$webFile,$datestr,$fast,$bdir;
  $archDir = "archive";
  if ($fast != 0) { $archDir .= "Online"; }
  $archDir .= "/";
  $acount = 0;
  $acntfile = $bdir . $archDir . ".Count";
  if ($obj = readInt($acntfile)) { $acount = $obj; }
  $acount++;
  saveObject($acount,$acntfile);
  $acountF = nDigits(4,$acount);
  $webFile = "${archDir}${datestr}/Report_${datestr}_${acountF}.txt";
  $archFile = $bdir . $webFile;
  ckdir(dirname($archFile));
  copy($reportFile,$archFile);
  copy(HfromT($reportFile),HfromT($archFile));
}

# Trial filenames for archive links
function linkFileFind($file1) {
  global $fast,$runFileSeqIndex;
  $insert = "";
  if ($fast != 0) { $insert = ".fast"; }
  $file2 = "";
  $n = 0;
  while (ereg(basename($file2 = $file1 . ++$n . $insert . ".txt"),
              $runFileSeqIndex,$temp) ||
         file_exists($file2)) {}
  return $file2;
}

# Put a link to the full report in the appropriate runFileSeq directory
function LinkArchive($typ) {
  global $runFileSeqDir,$allRunFileSeqs,$webFile,$datestr;
  foreach ($allRunFileSeqs[$typ] as $k => $rfs) {
    $runid = strval($rfs[0]);
    $yeardigits = strlen($runid)-6;
    $runyear = substr(strval($runid),0,$yeardigits);
    $runday  = substr(strval($runid),$yeardigits,3);
    $fseqf = nDigits(7,strval($rfs[1]));
    $file = "${runFileSeqDir}${runyear}/${runday}/${runid}_${fseqf}.";
    $link = HfromT($webFile) . "#" . $rfs[2];
    saveText($link,linkFileFind($file));
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
      $rundigits = (intval($rfs[0])>9999999 ? 8 : 7);
      $ostr .= "\n  " . nDigits($rundigits,$rfs[0]) . " / " . nDigits(7,$rfs[1]);
    }
    $ostr .= "\n";
  }
  return $ostr;
}

# Main routine for archiving/linking/mailing reports & summaries
function ArchAndMail($typs, $sendmail=1) {
  global $startTxt,$info,$sesDir,$webFile,$archFile,$webdir,$bdir;
  global $fast,$toFolks,$mode,$typecounts,$shift,$datestr2,$runFileSeqIndex;
  $runFileSeqIndex = readText($bdir . "rFSI.lis");
  Archive();

  $sumTemp = "";
  foreach ($typs as $typ => $entN) {
    if ($typecounts[$typ] > 0) {
      LinkArchive($typ);
      $sumTemp .= OutputChangedIssues($typ);
    }
  }
  reset($typs);
  foreach ($typs as $typ => $entN) {
    if ($typecounts[$typ] > 0) { $sumTemp .= OutputExaminedRunFseq($typ); }
  }

  $fullLink = $webdir . HfromT($webFile);

  # output is the email summary, output2 is for the electronic shift log entry

  $output  = $startTxt[$fast] . "\n\n" . dashdelim() . "\n";
  $output .= $sumTemp . "\n" . $info . "\nFull report archived in:\n";
  #$output .= $archFile . "\n" . $fullLink . "\n\n";
  $output .= $fullLink . "\n\n";

  $output2  = $startTxt[$fast] . "\n";
  $output2 .= $sumTemp . "\n" . str_replace("----","",$info);
  $output2 .= "\nFull report archived in:\n" . $fullLink;
  
  if ($fast > 0) {
    if (strlen($datestr2)<10) { return 11; }
    if (strlen($shift["name"])<2) { return 12; }
    if (strlen($output2)<4) { return 13; }
    PrepShiftLog($datestr2,$shift["name"],$output2);
  }

  $summaryFile = "${sesDir}Summary.${fast}.txt";
  saveText($output,$summaryFile);
  
  if ($sendmail == 0) { return 0; }

  $testReal = "Test";
  if ($mode != "TestIt") { $testReal = "Real"; }
  $to = $toFolks[$testReal][$fast];
  $toalso = $_POST["originator"];
  if (strlen($toalso) > 0) { $to .= "," . $toalso; }
  logit("submit: (fast=${fast}) sending mail to $to");
  $mailResult = mail($to,$startTxt[$fast],$output);
  if (!$mailResult) {
    logit("submit: mail failed for fast=$fast"); 
    return 5;
  }
  return 0;
}


# Output if the submission to the electronic shift log and mail failed
function FailSubmission($code) {
  # Mail the maintainer first
  $mstr = "gene@bnl.gov";
  $sstr = "QA Shift Report Failure";
  $fstr = "QA Shift Report submission failed with code: ${code}\n";
  $mailResult = mail($mstr,$sstr,$fstr);

  head("STAR QA Shift Report Submission");
  body();
  print "<h3>QA Shift Report Form: ";
  print "<font color=red>Submission Failed</font></h3>\n\n";
  print "<h2>Please do not re-attempt submission.</h2>\n\n";
  print "Please notify <a href=${mstr}>Gene Van Buren</a>\n";
  print "(631-344-7953) that the submission failed with code:\n";
  print "<b>${code}.${mailResult}</b>\n\n";
  foot();
  exit;
}

# Output if the submission to the electronic shift log and mail succeeded
function SuccessSubmission() {
  head("STAR QA Shift Report Submission");
  body();
  print "<h3>QA Shift Report Form: ";
  print "<font color=blue>Submission Completed Successfully</font></h3>\n\n";
  print "<h2>NEVER SELECT YOUR BROWSER'S RELOAD BUTTON AFTER FORM SUBMISSION!</h2>\n\n";
  PostToShiftLog();
  foot();
  exit;
}

###################################################################


#################################
# Report & Summary archives/mails
#

# Full report
$reportFile = $sesDir . "Report.txt";
$output = $start . "\n\n" . data2text($allents);
saveText($output,$reportFile);
$output = str2page($start,data2html($allents));
saveText($output,HfromT($reportFile));



# Summaries
# If there are any fast offline entries, archive report and prepare summary,
# but only mail summary if there are some issue changes...
if ($typecounts["FRP"] > 0) {
  $fast = 1;
  $atyps = array("FRP" => $ents["FRP"]);
  $nofastchanges = count($allnewissues["FRP"]) + count($allgoneissues["FRP"]);
  #ArchAndMail($atyps,$nofastchanges);
  $aamResult = ArchAndMail($atyps);
  if ($aamResult > 0) { FailedSubmission($aamResult); }
}
# If there are any non - fast offline entries, archive report and mail summary
if ($typecounts["all"] - $typecounts["FRP"] > 0) {
  $fast = 0;
  $atyps = $ents;
  unset($atyps["FRP"]);
  $aamResult = ArchAndMail($atyps);
  if ($aamResult > 0) { FailedSubmission($aamResult); }
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
SuccessSubmission();

?>
