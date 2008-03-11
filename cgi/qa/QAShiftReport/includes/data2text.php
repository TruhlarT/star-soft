<?php

incl("entry.php");
incl("infohandling.php");

function d2tdelim() { return "###"; }
function str2page($title,$str) {
  global $incdir;
  $output  = readText("${incdir}head.html");
  $output .= $title;
  $output .= readText("${incdir}head2.html");
  $output .= readText("${incdir}body.html");
  $output .= $str;
  $output .= readText("${incdir}foot.html");
  return $output;
}

function data2text($spec) {
  $specs = split(d2tdelim(),$spec);
  $str = "";
  
  if (count($specs) > 1) {
    foreach ($specs as $k => $subspec) { $str .= data2text($subspec); }
  } else {
    if ($spec == "Info") {
      readInfo();
      $str .= infoText();
    } elseif ($spec == "Wrapup") {
      readWrapup();
      $str .= wrapupText();
    } elseif ($spec == "InfoWrapup") {
      readInfo();
      readWrapup();
      $str .= infoWrapupText();
    } elseif ($entr = readObjectEntry(getSesDir() . $spec)) {
      $str .= $entr->Text();
    }
  }
  return $str;
}

function data2html($spec) {
  $specs = split(d2tdelim(),$spec);
  $str = "";
  
  if (count($specs) > 1) {
    foreach ($specs as $k => $subspec) { $str .= data2html($subspec); }
  } else {
    if ($spec == "Info") {
      readInfo();
      $str .= infoHtml();
    } elseif ($spec == "Wrapup") {
      readWrapup();
      $str .= wrapupHtml();
    } elseif ($spec == "InfoWrapup") {
      readInfo();
      readWrapup();
      $str .= infoWrapupHtml();
    } elseif ($entr = readObjectEntry(getSesDir() . $spec)) {
      $str .= $entr->Html();
    }
  }
  return $str;
}

?>
