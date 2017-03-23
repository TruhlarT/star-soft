<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  incl("files.php");

  getPassedInt("topic");
  
  $status = 0;
  
  # topic values:
  # 1 : cuts
  # 2 : descriptions
  # 3 : references
  # 4 : references preparation file
  # 5 : attachment for an issue
  $tasks = array( 1 => "updating analysis options and pass/fail cut",
                  2 => "updating plot description",
                  3 => "updating reference histograms",
                  4 => "marking for reference histogram update",
                  5 => "attaching plot to issue"
                );

  $task = (array_key_exists($topic) ? $tasks[$topic] : "unknown");
  
  $isRef = ($topic == 3 || $topic == 4); # longer waiting for updating references
  $UPDATElockfile = "/tmp/QAUPDATElockfile" . ($isRef ? "3" : "${topic}");
  $tooOld = ($isRef ? 1800 : 180);
  $giveUp = ($isRef ? 900 : 90);
  if (! (waitForLock($UPDATElockfile,$tooOld,2.0,$giveUp))) {
    jstart();
    print "    err_handle.html('Could not complete ${task}\nOther update not yet completed.');\n";
    print "    err_handle.show();\n";
    jend();
    died("Problems (7.${topic})");
    # This seems to cause unexpected EOF for web browser
  }

  switch ($topic) {
      
    case  1 :
      # 1 : cuts

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
      
      inclR("refDesc.php");

      getPassedVarStrict("name");
      getPassedVar("title");
      getPassedVar("desc");
      uploadDesc($name,$title,$desc);

      break;
      
    case 3 :
      # 3 : references
      
      inclR("refData.php");
      
      getPassedVarStrict("user_dir");
      getPassedVarStrict("runYear");
      getPassedVarStrict("trig");
      getPassedVar("comments");
      getPassedVarStrict("allOrSome");
      
      $aOS = ($allOrSome === "all" ? 0 : 1);
      $status = writeDbFromFile($user_dir,$runYear,$trig,$comments,$aOS);
      break;

    case 4 :
      # 4 : reference preparation file
      
      inclR("refMarks.php");

      getPassedVarStrict("name");
      getPassedVarStrict("user_dir");
      getPassedVarStrict("mode");
      $pref = false;
      getPassedVarStrict("pref",1);

      addOrRemoveMark($name,$pref,$user_dir,$mode);
      break;

    case 5 :
      # 5 : attachment for an issue

      getPassedVarStrict("user_dir");
      getPassedVarStrict("attach");
      getPassedVarStrict("suffix");
      $inattach = "${DAEMON_OUTPUT_DIR}${user_dir}/${attach}.${suffix}";
      if (is_file($inattach)) {
        @(ckdir($bdir_tmp)) or $status = -2;
        if ($status == 0) {
          $outattach = "${bdir_tmp}${attach}.${suffix}";
          if (is_file($outattach)) { unlink($outattach); }
          @(copy($inattach,$outattach)) or $status = -3;
          if ($status == 0) {
            fstart("issAttach","issueEditor.php","QAifr");
            fhidden("iid",0);
            fhidden("mode","view");
            fhidden("attach",$attach);
            fhidden("suffix",$suffix);
            fend();
            jstart();
?>
    var trying = true;
    var astr = '';
    while (trying) {
      iid = prompt(astr + 'Please enter the ID of an existing issue (e.g. 8009)','0');
      if (iid == '' || iid == null || (iid > 999 && iid < 30000)) { trying = false; }
      else { astr = 'Invalid issue ID: ' + iid + '\n'; }
    }
    if (iid > 999) {
      submit_form('issAttach','iid',iid);
    }
<?php       jend();
          }
        }
      } else {
        $status = -1;
      }
      if ($status < 0) {
        jstart();
        print "    alert('Problems with attachments (${status})');\n";
        jend();
      }
      break;

    default :
      #died("Unknown update topic: $topic");
      logit("Unknown update topic: $topic");
      
      
  }
  
  clearLock($UPDATElockfile);

  print ($status < 0 ? "Failed" : "Succeeeded") . " in ${task} : ${status}.\n";
  
  ?>
