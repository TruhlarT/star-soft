<?php
include "setup.php";
incl("data2text.php");
print str2page("QAlog","<pre>" . readText($elog) . "</pre>");
?>
