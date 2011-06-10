<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  
  getPassedInt("topic");
  
  head("QA Reference Updater");
  body();
  
  $task = "unknown";
  $status = 0;
  
  # topic values:
  # 1 : cuts
  # 2 : descriptions
  # 3 : references
  # 4 : references preparation file
  
  switch ($topic) {
      
    case  1 :
      # 1 : cuts
      $task = "updating analysis options and pass/fail cut";

      inclR("refCuts.php");
      
      getPassedVarStrict("name");
      getPassedInt("mode");
      getPassedVarStrict("pref");
      
      $name = stripHistPrefixes($name,($pref == "GE" ? 0 : 1),$pref);
      
      if (!getPassedFloat("cut",1)) {
        uploadCut($name,$mode);
      } else if (!getPassedVarStrict("opts",1)) {
        uploadCut($name,$mode,$cut);
      } else {
        uploadCut($name,$mode,$cut,$opts);
      }
      
      break;
      
    case 2 :
      # 2 : descriptions
      $task = "updating plot description";
      
      inclR("refDesc.php");

      getPassedVarStrict("name");
      getPassedVar("title");
      getPassedVar("desc");
      uploadDesc($name,$title,$desc);

      break;
      
    case 3 :
      # 3 : references
      $task = "updating reference histograms";
      
      inclR("refData.php");
      
      getPassedVarStrict("user_dir");
      getPassedVarStrict("runYear");
      getPassedVarStrict("trig");
      getPassedVar("comments");
      getPassedVarStrict("allOrSome");
      
      $aOS = ($allOrSome === "all" ? 0 : 1);
      $status = writeDbFromFile($user_dir,$runYear,$trig,$comments,$aOS);
      ($status >= 0) or died("Failed in $task: $status");
      break;

    case 4 :
      # 4 : reference prepation file
      $task = "marking for reference histogram update";
      
      inclR("refMarks.php");

      getPassedVarStrict("name");
      getPassedVarStrict("user_dir");
      getPassedVarStrict("mode");
      $pref = false;
      getPassedVarStrict("pref",1);

      addOrRemoveMark($name,$pref,$user_dir,$mode);
      break;

    default :
      died("Unknown update topic: $topic");
      
  }
  
  print ($status < 0 ? "Failed" : "Succeeeded") . " in ${task}.\n";
  foot();
  
  ?>
