<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  inclR("refDisplayPlots.php");
  getPassedVarStrict("user_dir");

  head("QA Reference Histogram Prepare Plots");
  body();
  preparePlots();
  foot();
  
?>
