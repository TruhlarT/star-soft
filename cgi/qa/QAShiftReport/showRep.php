<?php
include("setup.php");
incl("data2text.php");
getPassedVar("content");
print str2page("QA Shift Report [in progress]",data2html($content));
?>
