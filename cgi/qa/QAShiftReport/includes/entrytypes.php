<?php
global $ents,$noent,$trigs,$fstreams;
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

$fstreams = array(
  "ph" => "st_physics",
  "mt" => "st_mtd",
  "ht" => "st_ht",
  "cp" => "st_centralpro",
  "rp" => "st_rp"
);


function existsType($type) {
  global $ents;
  return array_key_exists($type,$ents);
}

function existsTrigType($type) {
  global $trigs;
  return array_key_exists($type,$trigs);
}

function existsFStreamType($type,&$isAKey) {
  global $fstreams;
  $isAKey = array_key_exists($type,$fstreams);
  return ($isAKey || in_array($type,$fstreams));
}

function FStreamSearch($type) {
  global $fstreams;
  # in place of array_search, allows st_ce to match st_centralpro
  foreach ($fstreams as $k => $v) {
    if (substr($v,0,strlen($type)) == $type) { return $k; }
  }
  return "";
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
