<?php
global $ents,$noent;
$ents = array(
  "FRP" => "Fast Offline Data",
  "RDP" => "Real Data Production",
  "RNT" => "Real Data Nightly Test",
  "MDP" => "Monte Carlo Data Production",
  "MNT" => "Monte Carlo Data Nightly Test"
);

function existsType($type) {
  global $ents;
  return isset($ents[$type]);
}

$noent = "No data entry type specified";
?>
