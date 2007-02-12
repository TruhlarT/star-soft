<?php
@(include "setup.php") or die("Problems (0).");
head("QAlog2");
body();
print "<pre>";
@(include $elog) or die("Problems (4).");
print "</pre>";
foot();
?>
