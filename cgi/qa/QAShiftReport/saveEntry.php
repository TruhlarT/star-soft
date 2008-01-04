<?php

###########################
# Take care of saving a data entry/info/wrapup to file
#

@(include "setup.php") or die("Problems (0).");
incl("entry.php");
incl("infohandling.php");

getPassedVarStrict("type");

if ($type == "Info") {
  # Info entries are special

  saveInfo($_POST);

  # Need to do some error checking (people do silly things)
  $estr = "";
  if (!checkdate($shift["datem"],$shift["dated"],$shift["datey"])) {
    # invalid date syntax (probably day and month reversed)
    $estr = "date_syntax";
  } else {
    $shiftStr = $shift["datem"] . "/" . $shift["dated"]
                . "/20" . nDigits(2,$shift["datey"]);
    $shiftStrTime = strtotime($shiftStr);
    if ($shiftStrTime > strtotime("+1 week")) {
      # no dates more than 1 week ahead
      $estr = "date_future";
    } elseif ($shiftStrTime < strtotime("-2 years")) {
      # no dates more than 2 years old
      $estr = "date_past";
    }
  }
  if ($estr != "") {
    getPassedVarStrict("work");
    header("location: ${webdir}info.php?work=${work}&mode=Error${estr}");
    exit;
  }

} elseif ($type == "Wrapup") {
  # Wrapup entries are special

  saveWrapup($_POST);

} else {
  # All other entries

  $entr = new qaentry($type);
  $entr->Fill($_POST);

  # If there are issues being added/removed,
  # then save a temporary entry and keep editing.
  # addissue > 999 means add that issue
  # addissue < -999 means remove that issue
  # addissue = 1 means add all previus issues for type
  # addissue between -999 and 0 means do nothing (refresh issues)
  # addissue = 0 means save entry and go on
  getPassedInt("num");
  getPassedInt("addissue");
  if ($addissue != 0) {
    $entr->AddIssue($addissue);
    $entr->Save();
    $passStr = "type=${type}&num=-${num}&editit=yes&issueYear=${issueYear}";
    header("location: ${webdir}formData.php?${passStr}");
    exit;
  }
  $entr->Save($num);

}

# View the entries so far
header("location: ${webdir}contents.php?mode=View");
exit;

?>
