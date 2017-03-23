<?php

@(include "setup.php") or die("Problems (0).");

incl("post.php");

global $slArray;

$slArray = array("date"      => "",
                 "trun"      => "Overnight (Owl)",
                 "author"    => "",
                 "subsystem" => "QA",
                 "comment"   => ""
                );

function PrepShiftLog($date,$author,$comment,$suppressMail=false) {
  global $slArray;
  logit("PrepShiftLog with $date : $author : " . strlen($comment));
  $slArray["date"] = $date;
  $slArray["author"] = $author;
  $slArray["comment"] = $comment;
  if ($suppressMail) { $slArray["suppressMail"] = "false"; }
  # value of suppressMail element is moot as long as it is set
}

function PostToShiftLog() {
  global $slArray;
  logit("Post to shift log for author: " . $slArray["author"]);
  if (strlen($slArray["author"]) < 2) { return; }
  logit($slArray["comment"]);
  $slStr = "";
  foreach ($slArray as $k => $v) {
    if (strlen($slStr)) $slStr .= "&";
    $slStr .= "${k}=" . urlencode($v);
  }
  $res = shiftLogPost($slStr);
  if (preg_match("/There was an error/",$res)) {
    logit($res);
    return false;
  }
  return true;
}


?>
