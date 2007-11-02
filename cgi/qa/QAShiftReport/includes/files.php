<?php

###############################
# Return a list of files in a directory, with match requirements
# order sorted by modification date (oldest first)
#
function dirlist($path,$match1="",$match2="",$sortalpha=0) {
  cleanFileName($path);
  cleanFileName($match1);
  cleanFileName($match2);
  $found = array();
  $times = array();
  if (!is_dir($path)) return $found;
  $path_id = opendir($path);
  while ($fname = chop(readdir($path_id))) {
    if ($fname != "." and $fname != "..") {
      $keep = 1;
      if ($match1 != "" ) {
        if (!(ereg($match1,$fname))) { $keep=0; }
        else if ($match2 != "" ) {
          if (!(ereg($match2,$fname))) { $keep=0; }
        }
      }
      if ($keep) {
        $found[] = $fname;
        $times[] = filemtime("$path/$fname");
      }
    }
  }
  closedir($path_id);
  if ($sortalpha) rsort($found);
  else array_multisort($found,SORT_NUMERIC,SORT_DESC,$times);
  return $found;
}

###############################
# File addition/removal
#
function rmfile($file) {
  cleanFileName($file);
  if (file_exists($file)) { unlink($file); }
}
function rmrf($path) {
  cleanFileName($path);
  if (is_dir($path)) {
    foreach (dirlist($path) as $k => $subfile) { rmrf($path . "/" . $subfile); }
    rmdir($path);
  } else {
    rmfile($path);
  }
}
function ckdir($pathname) {
  cleanFileName($pathname);

  // Check if directory already exists
  if (is_dir($pathname) || empty($pathname)) {
    return true;
  }
 
  // Ensure a file does not already exist with the same name
  if (is_file($pathname)) {
    logit("ckdir(): File exists in $pathname");
    return false;
  }
 
  // Crawl up the directory tree
  $next_pathname = substr($pathname, 0, strrpos($pathname, "/"));
  if (ckdir($next_pathname)) {
    if (!file_exists($pathname)) {
      return mkdir($pathname,0777);
    }
  }
 
  return false;
}
function cpdir($path1,$path2) {
  cleanFileName($path1);
  cleanFileName($path2);
  if (ckdir($path2)) {
    foreach (dirlist($path1) as $k => $subfile) {
      copy($path1 . "/" . $subfile, $path2 . "/" . $subfile);
    }
  }
}



###############################
# String prep for saving/reading
#
$chrsToCode = array(10,34,39,60,62);
function xmlN($n) { return "&#" . nDigits(3,$n) . ";"; }
# Not doing ampersand (must be done last if done)
function encodeText($str, $n=0) {
#  return htmlentities($str,ENT_QUOTES);
  if ($n != 0) { return str_replace(chr($n),xmlN($n),$str); }
  global $chrsToCode;
  $encoded = $str;
  $n = end($chrsToCode);
  while ($n) {
    $encoded = str_replace(chr($n),xmlN($n),$encoded);
    $n = prev($chrsToCode);
  }
  reset($chrsToCode);
  return $encoded;
}
function decodeText($str, $n=0) {
  # html_entity_decode supported in PHP 4.3.0 and above.
  # 12/30/04 running PHP 4.1
  # return html_entity_decode($str,ENT_QUOTES);
  if ($n != 0) { return str_replace(xmlN($n),chr($n),$str); }
  global $chrsToCode;
  $decoded = $str;
  foreach ($chrsToCode as $k => $n) {
    $decoded = str_replace(xmlN($n),chr($n),$decoded);
  }
  return $decoded;
}


###############################
# String save/read
#
function saveText($str,$file,$encodeit=0) {
  cleanFileName($file);
  if ($encodeit != 0) { saveText(encodeText($str,10),$file,0); return; }
  rmfile($file);
  ckdir(dirname($file));
  @($fp = fopen($file,'w')) or died("Couldn't open output file");
  flock($fp,LOCK_EX);
  @(fwrite($fp,$str)) or died("Couldn't write to output file");
  flock($fp,LOCK_UN);
  @(fclose($fp)) or died("Couldn't close output file");
}
function readText($file) {
  cleanFileName($file);
  $str = "";
  if (!is_file($file)) { return $str; }
  @($fp = fopen($file,'r')) or died("Couldn't open input file");
  flock($fp,LOCK_SH);
  while (!feof($fp)) {
#logit("INPUTFILE: $file \n");
    @($strtemp = fread($fp,8192)) or died("Couldn't read from input file");
    $str .= $strtemp;
  }
  flock($fp,LOCK_UN);
  @(fclose($fp)) or died("Couldn't close input file");
  return decodeText($str,10);
}

###############################
# Object save/read
#
function saveObject($object,$file) {
  $serialed = serialize($object);
  saveText($serialed,$file,1);
}
function readObject($file) {
  $stored = readText($file);
  return unserialize($stored);
}
function readInt($file) {
  if (($obj = readObject($file)) && (gettype($obj) == "integer")) { return $obj; }
  return false;
}
function readArray($file) {
  if (($obj = readObject($file)) && (is_array($obj))) { return $obj; }
  return false;
}
function readObjectClass($file,$class) {
  if (($obj = readObject($file)) && (get_class($obj) == $class)) { return $obj; }
  return false;
}


?>
