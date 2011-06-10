<?php
global $ents,$noent,$trigs;
$ents = array(
  "FRP" => "Fast Offline Data",
  "RDP" => "Real Data Production",
  "RNT" => "Real Data Nightly Test",
  "MDP" => "Monte Carlo Data Production",
  "MNT" => "Monte Carlo Data Nightly Test"
);

$trigs = array(
  "NA" => "not applicable",
  "GE" => "General",
  "MB" => "MinBias",
  "CL" => "Central",
  "HT" => "High Tower",
  "JP" => "Jet Patch",
  "HP" => "High Pt",
  "XX" => "Other Physics"
);


function existsType($type) {
  global $ents;
  return isset($ents[$type]);
}

function existsTrigType($type) {
  global $trigs;
  return isset($trigs[$type]);
}

function cmpTrigTypes($tt1,$tt2) {
  global $trigs;
  foreach ($trigs as $type => $v) {
    if ($tt1 == $type) {
      if ($tt2 == $type) { return 0; }
      else { return -1; }
    } else if ($tt2 == $type) { return 1; }
  }
  return 0;
}
function sortTrigType(&$ar) {
  return uksort($ar,"cmpTrigTypes");
}

$noent = "No data entry type specified";
?>
