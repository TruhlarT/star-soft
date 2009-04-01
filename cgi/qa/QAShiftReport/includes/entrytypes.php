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

$noent = "No data entry type specified";
?>
