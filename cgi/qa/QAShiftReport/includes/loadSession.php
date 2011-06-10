<?php

incl("infohandling.php");

function loadSes($work,$play=0) {
  setSesName($work);
  $dir = getSesDir($work);
  ckdir($dir);
  readInfo($work);
  if ($play > 0) { setPlaySes($work); }
}

?>
