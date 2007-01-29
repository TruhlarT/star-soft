<?php

incl("entry.php");
incl("infohandling.php");

function d2tdelim() { return "###"; }
function str2page($title,$str) {
  global $htmlfull;
  $output .= readText("${htmlfull}head.html");
  $output .= $title;
  $output .= readText("${htmlfull}head2.html");
  $output .= readText("${htmlfull}body.html");
  $output .= $str;
  $output .= readText("${htmlfull}foot.html");
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
