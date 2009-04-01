<?php
function fillform($arr) {
  jstart();
  print "    function fillThisForm() {\n";
  print "      form = document.forms[0];\n";
  while (list($key,$val) = each($arr)) {
      $val = str_replace(chr(10),"\\n",$val);
      $val = str_replace(chr(13),"",$val);
      print "      form." . $key . ".value = \"" . addslashes($val) . "\";\n";
  }
  print "    }\n";
  print "    setTimeout(\"fillThisForm();\",100);\n";
  jend();
}
?>
