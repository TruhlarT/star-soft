<?php

incl("infohandling.php");

function loadSes($work) {
  setSesName($work);
  $dir = getSesDir($work);
  ckdir($dir);
  readInfo($work);
}

?>
