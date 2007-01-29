<?php
# Taken from http://us3.php.net/manual/en/function.wordwrap.php#53403
  function preserve_wordwrap($tstr, $len = 75 , $br ='\n' ) {
     $strs = explode($br,$tstr);
     $retstr = "";
     foreach ($strs as $str) {
         $retstr .= wordwrap($str,$len,$br) . $br;
     }
     return $retstr;
}?>
