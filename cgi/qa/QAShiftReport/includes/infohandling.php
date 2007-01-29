<?php

#################################
# Shift and Wrapup information for QA Shift Reports
#

incl("preserve_wordwrap.php");

global $shift,$wrapup,$mergeiw;

$shift_now_str = nDigits(2,date("H")) . ":" . nDigits(2,date("i"));

$shift = array(
  "name"        => "",
  "affiliation" => "",
  "datem"       => date("m"),
  "dated"       => date("d"),
  "datey"       => date("y"),
  "start"       => $shift_now_str,
  "end"         => $shift_now_str,
  "location"    => ""
);
$wrapup = array(
  "rnotified"  => "",
  "originator"  => "",
  "origphone"   => "",
  "anycomments" => ""
);

function getInfoFile($ses="") {
  return getSesDir($ses) . "info.data";
}
function getWrapupFile($ses="") {
  return getSesDir($ses) . "wrapup.data";
}

function saveInfo($arr,$ses="") {
  global $shift;
  foreach ($arr as $key => $val) {
    if (isset($shift[$key])) { $shift[$key] = $val; }
  }
  saveObject($shift,getInfoFile($ses));
}
function saveWrapup($arr,$ses="") {
  global $wrapup;
  foreach ($arr as $key => $val) {
    if (isset($wrapup[$key])) { $wrapup[$key] = $val; }
  }
  saveObject($wrapup,getWrapupFile($ses));
}

function readInfo($ses="") {
  global $shift;
  if ($obj = readArray(getInfoFile($ses))) { $shift = $obj; }
}
function readWrapup($ses="") {
  global $wrapup;
  if ($obj = readArray(getWrapupFile($ses))) { $wrapup = $obj; }
}

# The following code formats output of this data into text.

function dashdelim() {
  return "-----------------------------------------------------------------------";
}
function infoText() {
  global $shift,$mergeiw;
  $str  = dashdelim();
  $str .= "\nNAME:                                      " . $shift["name"];
  $str .= "\nORGANIZATION OR AFFILIATION:               " . $shift["affiliation"];
  $str .= "\nSHIFT DATE (mm/dd/yy):                     " . 
          nDigits(2,$shift["datem"]) . "/" .
	  nDigits(2,$shift["dated"]) . "/" .
	  nDigits(2,$shift["datey"]);
  $str .= "\nSHIFT TIME (at BNL):     START:            " . $shift["start"];
  $str .= "\n                           END:            " . $shift["end"];
  $str .= "\nSHIFT LOCATION:                            " . $shift["location"];
  if ($mergeiw != 0) { $str .= wrapupText(); }
  return $str;
}
function wrapupText() {
  global $wrapup;
  $str = "";
  if (strlen($wrapup["rnotified"]) > 0) {
    $str .= "\nPERSONS NOTIFIED OF PROBLEMS:              " . $wrapup["rnotified"];
  }
  $str .= "\nSUBMITTER CONTACT INFO:";
  if (strlen($wrapup["originator"]) > 0) {
    $str .= "  EMAIL:            " . $wrapup["originator"];
  }
  if (strlen($wrapup["origphone"]) > 0) {
    if (strlen($wrapup["originator"]) > 0) { $str .= "\n                       "; }
    $str .= "  PHONE:            " . $wrapup["origphone"];
  }
  $str .= "\nCOMMENTS:\n";
  if (strlen($wrapup["anycomments"]) > 0) {
    $str .= stripslashes($wrapup["anycomments"]);
  } else {
    $str .= "None.";
  }
  $str .= "\n" . dashdelim() . "\n";
  return $str;
}
function infoWrapupText() {
  global $mergeiw;
  $mergeiw = 1;
  return infoText();
}

function infoHtml() {
  global $shift,$mergeiw;
  $str  = "\n\n<hr>\n\n";
  $str .= "<table border=0 cellpadding=0 cellspacing=0 width=\"98%\">\n";
  $str .= "<tr>\n  <td colspan=2 width=\"50%\">NAME:</td>\n";
  $str .= "  <td><b><font color=\"#800000\">" . $shift["name"] .
            "</font></b></td>\n</tr>\n";
  $str .= "<tr>\n  <td colspan=2>ORGANIZATION OR AFFILIATION:</td>\n";
  $str .= "  <td><b>" . $shift["affiliation"] . "</b></td>\n</tr>\n";
  $str .= "<tr>\n  <td colspan=2>SHIFT DATE (mm/dd/yy):</td>\n";
  $str .= "  <td><b>" . nDigits(2,$shift["datem"]) . "/" .
                        nDigits(2,$shift["dated"]) . "/" .
                        nDigits(2,$shift["datey"]) . "</b></td>\n</tr>\n";
  $str .= "<tr>\n  <td>SHIFT TIME (at BNL):</td>\n";
  $str .= "  <td align=right>START:<br>END:</td>\n";
  $str .= "  <td><b>" . $shift["start"] . "<br>";
  $str .=               $shift["end"] . "</b></td>\n</tr>\n";
  $str .= "<tr>\n  <td colspan=2>SHIFT LOCATION:</td>\n";
  $str .= "  <td><b>" . $shift["location"] . "</b></td>\n</tr>\n";
  if ($mergeiw == 0) { $str .= "</table>\n\n"; }
  else { $str .= wrapupHtml(); }
  return $str;
}
function wrapupHtml() {
  global $wrapup;
  $str = "";
  if (strlen($wrapup["rnotified"]) > 0) {
    $str .= "<tr>\n  <td colspan=2>PERSONS NOTIFIED OF PROBLEMS:</td>\n";
    $str .= "  <td><b>" . $wrapup["rnotified"] . "</b></td>\n</tr>\n";
  }

  $str .= "<tr>\n  <td>SUBMITTER CONTACT INFO:</td>\n";
  $str .= "  <td align=right>";
  if (strlen($wrapup["originator"]) > 0) {
    $str .= "EMAIL:";
  }
  if (strlen($wrapup["origphone"]) > 0) {
    if (strlen($wrapup["originator"]) > 0) { $str .= "<br>"; }
    $str .= "PHONE:";
  }
  $str .= "</td>\n    <td><b>";
  if (strlen($wrapup["originator"]) > 0) {
    $str .= "<i><a href=\"mailto:" . $wrapup["originator"] . "\">" .
                                     $wrapup["originator"] . "</a></i>";
  }
  if (strlen($wrapup["origphone"]) > 0) {
    if (strlen($wrapup["originator"]) > 0) { $str .= "<br>"; }
    $str .= $wrapup["origphone"];
  }
  $str .= "</b></td>\n</tr>\n";
  $str .= "</table>\n\n";

  $str .= "COMMENTS:<br>\n";
  $str .= "<font color=\"#C00000\"><b>";
  if (strlen($wrapup["anycomments"]) > 0) {
    $str .= "<pre>";
    $str .= preserve_wordwrap(htmlentities(stripslashes($wrapup["anycomments"])),75,chr(10));
    $str .= "</pre>";
  } else {
    $str .= "None.";
  }
  $str .= "</b></font>\n\n";
  $str .= "<hr>\n<p>\n\n";
  return $str;
}
function infoWrapupHtml() {
  global $mergeiw;
  $mergeiw = 1;
  return infoHtml();
}

$mergeiw = 0;
?>
