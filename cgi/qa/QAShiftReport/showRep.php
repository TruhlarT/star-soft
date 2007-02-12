<?php
@(include "setup.php") or die("Problems (0).");
incl("data2text.php");
getPassedVar("content");
print str2page("QA Shift Report [in progress]",data2html($content));
?>
