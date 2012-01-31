<?php
  
  inclR("refCuts.php");
  
  global $sysStr,$disp1,$disp2,$HiRes1,$HiRes2;
  $sysStr = "";
  $disp1 = "gif";
  $HiRes1 = "eps";
  $HiRes2 = "svg";
  $disp2 = "png";
  
  function addSys($str) {
    global $sysStr;
    $sysStr .= $str . "\n";
  }
  function execSys() {
    global $sysStr,$bdir;
    if (!strlen($sysStr)) { return; }
    $fcmd = $bdir . "/QAtmpcmd";
    saveText($sysStr,$fcmd);
    system("/bin/csh -f $fcmd");
    $sysStr = "";
  }
  function cnvrtr($file1,$file2,$exec=true) {
    $str = "if ( ! -e $file2 ) /usr/bin/convert $file1 $file2";
    if ($exec) { system("/bin/csh -f -c '$str '"); }
    else { addSys($str); }
  }
  
  function preparePlots() {
    global $DAEMON_OUTPUT_DIR,$disp1,$HiRes1,$HiRes2,$user_dir;

    $user_dir1 = $DAEMON_OUTPUT_DIR . $user_dir;
    $files = dirlist($user_dir1,".${HiRes1}");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      foreach ($files as $k => $file) {
        $newfile = "${user_dir2}/" . substr($file,0,strlen($file)-6) . $disp1; // assumes .gz
        cnvrtr("${user_dir1}/$file",$newfile,false);
      }
      execSys();
    }
    $files = dirlist($user_dir1,".${HiRes2}");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      addSys("/bin/cp ${user_dir1}/*.${HiRes2} ${user_dir2}/");
      addSys("/usr/bin/bunzip2 ${user_dir2}/*.bz2 >& /dev/null");
      addSys("/bin/rm ${user_dir2}/*.bz2 >& /dev/null");
      execSys();
    }
  }

  function displayPlots($name) {
    global $URL_FOR_DAEMON_OUTPUT,$DAEMON_OUTPUT_DIR;
    global $disp1,$disp2,$HiRes1,$HiRes2;
    global $QARefCache,$user_dir,$inputfile,$refID,$singleFile;

    $user_dir1 = $DAEMON_OUTPUT_DIR . $user_dir;
    $files = dirlist($user_dir1,"${name}.${HiRes1}");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      $filesDisp = dirlist($user_dir2,"${name}.${disp1}");
      if (!count($filesDisp)) {
        foreach ($files as $k => $file) {
          $newfile = "${user_dir2}/" . substr($file,0,strlen($file)-6) . $disp1; // assumes .gz
          cnvrtr("${user_dir1}/$file",$newfile);
        }
      }
      $HiResData = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/${name}.${HiRes1}.gz";
      $dispData = urlUserRefDir($user_dir) . "${name}.${disp1}";
      print "<table border=1 cellspacing=0>\n<tr>";
      if (strlen($inputfile)) { print "<th>Data:</th>"; }
      if ($refID >= 0) { print "<th>Reference:"; }
      print "</th></tr>\n<tr>\n";
      print "<td><a href=\"${HiResData}\"><img src=\"${dispData}\"></a></td>\n";
      if (! $singleFile) {
        $HiResRef = false;
        $dispRef = "";

        # look for a cached version first
        $cacheDir = userRefDir($QARefCache,$refID);
        $specific = true;
        $name2 = $name;
        while ($HiResRef === false) {
          $fname2 = $cacheDir . "/Ref_${name2}.${HiRes1}.gz";
          if (file_exists($fname2)) {
            $HiResRef  = urlUserRefDir($QARefCache,$refID) . "Ref_${name2}.${HiRes1}.gz";
            $dispRef  = urlUserRefDir($QARefCache,$refID) . "Ref_${name2}.${disp1}";
            $newfile = $cacheDir . "/Ref_${name2}.{$disp1}";
            if (!file_exists($newfile)) {
              cnvrtr($fname2,$newfile);
            }
          } elseif (file_exists("${user_dir1}/Ref_${name}.${HiRes1}.gz")) {
            # no cached versions yet
            $HiResRef  = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/Ref_${name}.${HiRes1}.gz";
            $dispRef  = urlUserRefDir($user_dir) . "Ref_${name}.${disp1}";
            if (ckdir($cacheDir)) {
              copy("${user_dir1}/Ref_${name}.${HiRes1}.gz",$cacheDir . "/Ref_${name}.${HiRes1}.gz");
              copy("${user_dir2}/Ref_${name}.${disp1}",$cacheDir . "/Ref_${name}.${disp1}");
            }
          } elseif ($specific) {
            # check for general version instead
            $specific = false;
            $name2 = stripHistPrefixes($name,-1);
          } else { break; }
        }
        if ($HiResRef === false) {
          print "<td><i>Not present<br>in reference</i></td>\n";
        } else {
          print "<td><a href=\"${HiResRef}\"><img src=\"${dispRef}\"></a></td>\n";
        }
      }
      print "</tr>\n</table>\n";
    }
    $files = dirlist($user_dir1,"${name}.${disp2}");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      $filesHiRes = dirlist($user_dir2,"${name}.${HiRes2}");
      if (!count($filesHiRes)) {
        foreach ($files as $k => $file) {
          $newfile = "${user_dir1}/" . substr($file,0,strlen($file)-3) . ".${HiRes2}*"; // assumes not compressed
          addSys("/bin/cp ${user_dir1}/$newfile ${user_dir2}/");
          addSys("/usr/bin/bunzip2 ${user_dir2}/${newfile}.bz2");
          addSys("/bin/rm ${user_dir2}/${newfile}.bz2");
        }
        execSys();
      }
      $dispData = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/${name}.${disp2}";
      $HiResData = urlUserRefDir($user_dir) . "${name}.${HiRes2}";
      print "<table border=1 cellspacing=0>\n<tr>";
      if (strlen($inputfile)) { print "<th>Data:</th>"; }
      if ($refID >= 0) { print "<th>Reference:"; }
      print "</th></tr>\n<tr>\n";
      #print "<td><a href=\"${HiResData}\" target=\"QARzfr\"><img src=\"${dispData}\"></a></td>\n";
      print "<td><img src=\"${dispData}\" onclick=\"LoadZoom('${HiResData}')\"></td>\n";
      if (! $singleFile) {
        $HiResRef = false;
        $dispRef = "";

        # look for a cached version first
        $cacheDir = userRefDir($QARefCache,$refID);
        $specific = true;
        $name2 = $name;
        while ($HiResRef === false) {
          $fname2 = $cacheDir . "/Ref_${name2}.${HiRes2}";
          if (file_exists($fname2)) {
            $HiResRef  = urlUserRefDir($QARefCache,$refID) . "Ref_${name2}.${HiRes2}";
            $dispRef  = urlUserRefDir($QARefCache,$refID) . "Ref_${name2}.${disp2}";
          } elseif (file_exists("${user_dir2}/Ref_${name}.${HiRes2}")) {
            # no cached versions yet
            $dispRef  = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/Ref_${name}.${disp2}";
            $HiResRef  = urlUserRefDir($user_dir) . "Ref_${name}.${HiRes2}";
            if (ckdir($cacheDir)) {
              copy("${user_dir2}/Ref_${name}.${HiRes2}",$cacheDir . "/Ref_${name}.${HiRes2}");
              copy("${user_dir1}/Ref_${name}.${disp2}",$cacheDir . "/Ref_${name}.${disp2}");
            }
          } elseif ($specific) {
            # check for general version instead
            $specific = false;
            $name2 = stripHistPrefixes($name,-1);
          } else { break; }
        }
        if ($HiResRef === false) {
          print "<td><i>Not present<br>in reference</i></td>\n";
        } else {
          print "<td><img src=\"${dispRef}\" onclick=\"LoadZoom('${HiResRef}')\"></td>\n";
        }
      }
      print "</tr>\n</table>\n";
    } else {
      print "<b>PLOTS UNAVAILABLE</b>\n";
    }
  }

?>
