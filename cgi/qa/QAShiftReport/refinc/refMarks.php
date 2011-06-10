<?php

  incl("files.php");
  
  global $marks_exist,$marks_file,$marks_txt,$marksCheckedDir,$prefixSig;
  $marks_exist = false;
  $marks_file = "";
  $marks_txt = "";
  $marksCheckedDir = "";
  $prefixSig = "(__\w+__x__)?";

  function getUpdateFile($subdir) {
    return userRefDir($subdir) . "/refsToUpdate.txt";
  }
    
  function checkMarksExist($subdir) {
    # This function should be called before any reads/saves
    global $marks_file,$marks_exist,$marksCheckedDir;
    if ($marksCheckedDir !== $subdir) {
      $marks_file = getUpdateFile($subdir);
      $marks_exist = file_exists($marks_file);
      $marksCheckedDir = $subdir;
    }
    return $marks_exist;
  }
  
  function readMarks() {
    global $marks_exist,$marks_file,$marks_txt;
    if ($marks_exist && (strlen($marks_txt) < 2)) { $marks_txt = readText($marks_file); }
  }
  
  function saveMarks() {
    global $marks_file,$marks_txt;
    rmfile($marks_file);
    if (strlen($marks_txt) > 1) { saveText($marks_txt,$marks_file); }
  }
  
  function markExists($mark) {
    global $marks_txt,$marks_exist,$prefixSig;
    if (!$marks_exist) { return false; }
    return (preg_match("/(^|\n)${prefixSig}${mark}\n/",$marks_txt) > 0);
  }
  
  function removeMark($mark) {
    global $marks_txt,$prefixSig;
    $needsUpdate = markExists($mark);
    if ($needsUpdate) {
      $marks_txt = preg_replace("/^${prefixSig}${mark}\n/","",$marks_txt);
      $marks_txt = preg_replace("/\n${prefixSig}${mark}\n/","\n",$marks_txt);
    }
    return $needsUpdate;
  }
  
  function addMark($mark,$pref) {
    global $marks_txt;
    $needsUpdate = !(markExists($mark));
    if ($needsUpdate) {
      if ($pref !== false) { $marks_txt .= "__${pref}__x__"; }
      $marks_txt .= "${mark}\n";
    }
    return $needsUpdate;
  }
  
  function addOrRemoveMark($mark,$pref,$subdir,$remove=0) {
    # Use remove=0 to add, remove=1 to remove
    if (checkMarksExist($subdir)) { readMarks(); }
    $needsUpdate = ($remove == 0 ? addMark($mark,$pref) : removeMark($mark));
    if ($needsUpdate) { saveMarks(); }
  }

    
?>