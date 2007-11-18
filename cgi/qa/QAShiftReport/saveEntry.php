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
  foreach ($_POST as $key => $val) {
    if (substr($key,0,1) == "x") {
      $entr->AddIssue(substr($key,1));
    } elseif (isset($entr->info[$key])) {
      $entr->info[$key] = $val;
    }
  }

  # If there are issues being added/removed,
  # then save a temporary entry and keep editing.
  # Negative issue numbers indicate removal from entry.
  # Issue number =  1 indicates add all previous issues for type.
  # Issue number = -n indicates do nothing (refresh issues for year n)
  getPassedInt("num");
  getPassedInt("addissue");
  if ($addissue != 0) {
    $entr->AddIssue($addissue);
    $entr->Save();
    logit("Saved entry: temp");
    $passStr = "type=${type}&num=-${num}&editit=yes&issueYear=${issueYear}";
    header("location: ${webdir}formData.php?${passStr}");
    exit;
  }

  # Otherwise, save it and go on...
  logit("Saved entry: $type $num");
  $entr->Save($num);

}

# View the entries so far
header("location: ${webdir}contents.php?mode=View");
exit;

?>
