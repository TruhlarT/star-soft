<?php
function fillformHelp(&$val,$key,$pref) { $val = $pref . $val; }

function fillformFromArray($arr) {
  foreach ($arr as $key => $val) {
    if (is_array($val)) {
      $flip = array_flip($val);
      if (array_walk($flip,'fillformHelp',$key)) { fillformFromArray(array_flip($flip)); }
    } else {
      $val = str_replace(chr(10),"\\n",$val);
      $val = str_replace(chr(13),"",$val);
      if ($key == "affiliation") $val = str_replace(" ","_",$val);
      if ($key == "name" && strlen($val)>0) {
        print "      setTimeout('form." . $key . ".value = \"" . addslashes($val) . "\";',400);\n";
      } else {
        print "      form." . $key . ".value = \"" . addslashes($val) . "\";\n";
      }
    }
  }
}

function fillform($arr,$id1 = "", $id2 = "") {
  jstart();
  # Chained 0.9.9 - MIT license - Copyright 2010-2013 Mika Tuupola
  # http://www.appelsiini.net/projects/chained
  if (strlen($id1)>0) { ?>
!function(a,b){"use strict";a.fn.chained=function(c){return this.each(function(){function d(){var d=!0,g=a("option:selected",e).val();a(e).html(f.html());var h="";a(c).each(function(){var c=a("option:selected",this).val();c&&(h.length>0&&(h+=b.Zepto?"\\\\":"\\"),h+=c)});var i;i=a.isArray(c)?a(c[0]).first():a(c).first();var j=a("option:selected",i).val();a("option",e).each(function(){a(this).hasClass(h)&&a(this).val()===g?(a(this).prop("selected",!0),d=!1):a(this).hasClass(h)||a(this).hasClass(j)||""===a(this).val()||a(this).remove()}),1===a("option",e).size()&&""===a(e).val()?a(e).attr("disabled","disabled"):a(e).removeAttr("disabled"),d&&a(e).trigger("change")}var e=this,f=a(e).clone();a(c).each(function(){a(this).bind("change",function(){d()}),a("option:selected",this).length||a("option",this).first().attr("selected","selected"),d()})})},a.fn.chainedTo=a.fn.chained,a.fn.chained.defaults={}}(window.jQuery||window.Zepto,window,document);
    <?php print "setTimeout('$(\"#${id1}\").chained(\"#${id2}\");',500);\n";
  }
  print "    function fillThisForm() {\n";
  print "      form = document.forms[0];\n";
  fillformFromArray($arr);
  print "    }\n";
  print "    setTimeout(\"fillThisForm();\",250);\n";
  jend();
}
?>
