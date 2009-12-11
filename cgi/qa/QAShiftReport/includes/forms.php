<?php
# Forms HTML    
				
    function fstart($name,$action,$target="QArfr",$meth="POST",$auto=1) {
      global $webdir;
      #print "<form name=\"${name}\" action=\"${action}\" ";
      print "<form name=\"${name}\" action=\"";
      if ($auto==1) { print $webdir; }
      print $action . "\" method=\"${meth}\" target=${target}>\n";
    }

    function fend() { print "</form>\n"; }

    function fbutton($name,$val,$oncl) {
      print "<input type=button name=${name} value=\"${val}\"";
      print " onclick=\"${oncl}\">\n";
    }

    function fhidden($name,$val) {
      print "<input type=hidden name=${name} value=\"${val}\">\n";
    }

    function fsubmit($val,$oncl="",$onsub="") {
      print "<input type=submit name=subit value=\"${val}\"";
      if ($oncl != "") { print " onclick=\"${oncl}\""; }
      if ($onsub != "") { print " onsubmit=\"${onsub}\""; }
      print ">\n";
    }

    function freset($val) {
      print "<input type=reset name=reset value=\"${val}\">\n";
    }
    
    function finput($name,$size,$defval="") {
      print "<input name=${name} size=${size} value=\"${defval}\">\n";
    }
    
//print a textarea
    function ftext($element_name,$values,$rows=-1,$cols=-1) {
      print "<textarea name=\"${element_name}\"";
      if ($rows >= 0) { print " rows=${rows}"; }
      if ($cols >= 0) { print " cols=${cols}"; }
      print ">" . stripslashes($values[$element_name]) . "</textarea>";
    }

//print a radio button or checkbox
    function fradio($type, $element_name,
                           $values, $element_value) {
      print "<input type=\"${type}\" name=\"${element_name}\"" .
            " value=\"${element_value}\" ";
      if ($element_value == $values[$element_name]) {
          print " checked=\"checked\"";
      }
      print "/>";
    }

?>
