<?php
@(include "setup.php") or die("Problems (0).");

incl("data2text.php");
print str2page("QAlog","<pre>" . readText($elog) . "</pre>");
?>
