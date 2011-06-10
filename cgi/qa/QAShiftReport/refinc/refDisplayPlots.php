<?php
  
  inclR("refCuts.php");
  
  global $sysStr,$disp;
  $sysStr = "";
  $disp = "gif";
  
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
    global $DAEMON_OUTPUT_DIR,$disp,$user_dir;

    $user_dir1 = $DAEMON_OUTPUT_DIR . $user_dir;
    $files = dirlist($user_dir1,".eps");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      foreach ($files as $k => $file) {
        $newfile = "${user_dir2}/" . substr($file,0,strlen($file)-6) . $disp; // strip .eps.gz
        cnvrtr("${user_dir1}/$file",$newfile,false);
      }
      execSys();
    }
  }

  function displayPlots($name) {
    global $URL_FOR_DAEMON_OUTPUT,$DAEMON_OUTPUT_DIR,$disp;
    global $QARefCache,$user_dir,$inputfile,$id,$singleFile;

    $user_dir1 = $DAEMON_OUTPUT_DIR . $user_dir;
    $files = dirlist($user_dir1,"${name}.eps");
    if (count($files)) {
      $user_dir2 = userRefDir($user_dir);
      if (!ckdir($user_dir2)) {
        # not sure;
        logit("FAILED ON ckdir for $user_dir2");
      }
      $filesDisp = dirlist($user_dir2,"${name}.${disp}");
      if (!count($filesDisp)) {
        foreach ($files as $k => $file) {
          $newfile = "${user_dir2}/" . substr($file,0,strlen($file)-6) . $disp; // strip .eps.gz
          cnvrtr("${user_dir1}/$file",$newfile);
        }
      }
      $epsData = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/${name}.eps.gz";
      $dispData = urlUserRefDir($user_dir) . "${name}.${disp}";
      print "<table border=1 cellspacing=0>\n<tr>";
      if (strlen($inputfile)) { print "<th>Data:</th>"; }
      if ($id >= 0) { print "<th>Reference:"; }
      print "</th></tr>\n<tr>\n";
      print "<td><a href=\"${epsData}\"><img src=\"${dispData}\"></a></td>\n";
      if (!$singleFile) {
        $epsRef = ""; $dispRef = "";

        # look for a cached version first
        $cacheDir = userRefDir($QARefCache,$id);
        $name2 = $name;
        $fname2 = $cacheDir . "/Ref_${name2}.eps.gz";
        $useRefCache = file_exists($fname2);
        if (! $useRefCache) {
          # check for general version instead
          $name2 = stripHistPrefixes($name,-1);
          $fname2 = $cacheDir . "/Ref_${name2}.eps.gz";
          $useRefCache = file_exists($fname2);
        }
        if ($useRefCache) {
          $epsRef  = urlUserRefDir($QARefCache,$id) . "Ref_${name2}.eps.gz";
          $dispRef  = urlUserRefDir($QARefCache,$id) . "Ref_${name2}.${disp}";
          $newfile = $cacheDir . "/Ref_${name2}.{$disp}";
          if (!file_exists($newfile)) {
            cnvrtr($fname2,$newfile);
          }
        } elseif (file_exists("${user_dir1}/Ref_${name}.eps.gz")) {
          # no cached versions yet
          $epsRef  = "${URL_FOR_DAEMON_OUTPUT}${user_dir}/Ref_${name}.eps.gz";
          $dispRef  = urlUserRefDir($user_dir) . "Ref_${name}.${disp}";
          if (ckdir($cacheDir)) {
            copy("${user_dir1}/Ref_${name}.eps.gz",$cacheDir . "/Ref_${name}.eps.gz");
            copy("${user_dir2}/Ref_${name}.${disp}",$cacheDir . "/Ref_${name}.${disp}");
          }
        }
        if (strlen($epsRef)) {
          print "<td><a href=\"${epsRef}\"><img src=\"${dispRef}\"></a></td>\n";
        } else {
          print "<td><i>Not present<br>in reference</i></td>\n";
        }
      }
      print "</tr>\n</table>\n";
    } else {
      print "<b>PLOTS UNAVAILABLE</b>\n";
    }
  }

?>