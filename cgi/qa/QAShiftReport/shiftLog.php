<?php

@(include "setup.php") or die("Problems (0).");

global $slArray, $slFile;

$slFile = "/tmp/QAsubmission.dat";

$slArray = array("date"      => "",
                 "trun"      => "Overnight (Owl)",
                 "author"    => "",
                 "subsystem" => "QA",
                 "comment"   => ""
                );

function PrepShiftLog($date,$author,$comment) {
  global $slArray;
  logit("PrepShiftLog with $date : $author : " . strlen($comment));
  $slArray["date"] = $date;
  $slArray["author"] = $author;
  $slArray["comment"] = $comment;
}

function PostToShiftLog() {
  global $slArray, $slFile, $webdir;
  logit("Post to shift log for author: " . $slArray["author"]);
  if (strlen($slArray["author"]) < 2) { return; }
  saveObject($slArray,$slFile);
  $loc = "${webdir}shiftLog.php";

# temporary change from QAnfr to QAhfr to test for Mike
  jstart();
  print "  parent.QAnfr.location.href=\"${loc}\";\n";
  jend();
  logit("REDIRECT:\n  parent.QAnfr.location.href=\"${loc}\";\n");
  if (file_exists($slFile)) { logit("Successfully wrote to $slFile \n"); }
  else { logit("Failed write to $slFile \n"); }
}


############ Submit data if it has been passed to us:

if (file_exists($slFile)) {
  logit("Submitting to Electronic ShiftLog");
  ($slArray = readArray($slFile)) or died("Problem reading submission array.");
  rmfile($slFile);
  ob_start();
  head("QA Shift Report Shift Log");
  body();
  $summaryUrl = "http://online.star.bnl.gov/apps/shiftLog/private/addWebSummry.jsp";
  fstart("sform",$summaryUrl,"QAnfr","POST",0);
  logit("SHIFTLOG DATA START");
  foreach ($slArray as $name => $val) {
    if ($name == "comment") {
      print "<textarea name=comment>" . stripslashes($val) . "</textarea>\n";
    } else { fhidden($name,$val); }
    logit(stripslashes($val));
  }
  logit("SHIFTLOG DATA STOP");
  print "<input type=submit value=Submit name=B12>\n";
  fend();
  jstart();
  print "  setTimeout('document.sform.submit()',100);\n";
  jend();
  foot();
  $page = ob_get_contents();
  ob_end_flush();

  # Save the submission to a log file. Replace oldest file if we reach maxCnt
  $maxCnt = 20;
  $subfile = $bdir . "log/";
  $prefix = "ESLsubmission";
  $subFiles = dirlist($subfile,$prefix);
  $subCnt = count($subFiles);
  $subfile .= ($subCnt >= $maxCnt) ? $subFiles[0] : $prefix . $subCnt . ".html";
  logit("SHIFTLOG ENTRY SAVED TO $subfile");
  saveText($page,$subfile);
  exit;
}


?>
