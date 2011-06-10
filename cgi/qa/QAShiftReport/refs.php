<!doctype html public "-//W3C//DTD HTML 4.01 Frameset//EN"
  "http://www.w3.org/TR/REC-html4/frameset.dtd">
<html>
<HEAD><TITLE>STAR QA Browser with Reference Histograms</TITLE>
<script type="text/javascript">
<!--
var firstProc = false;
var blockSet = false;
var fsShowSize = 250;
var fsHideSize = 40;
function setFS1(fsiz) {
  if (firstProc && !blockSet) {
    document.getElementById("QARfs1").rows = "1," + fsiz + ",*";
    blockSet = true;
    setTimeout('blockSet=false;',150);
  }
}
function setFS1Show() { setFS1(fsShowSize); }
function setFS1Hide() { setFS1(fsHideSize); }
function setFirst() {
  firstProc = true;
  setFS1Hide();
  document.getElementById("QARfs2").cols = "*,200";
}
// -->
</script>
</head>
<noframes>
<font size="+1" color="green">This page uses frames.</font><p>
</noframes>
<frameset id="QARfs1" rows="1,*,1" border=1 frameborder=1 framespacing=0>
<frame src="blank.html" name="QARnfr" scrolling=no
  style="background:cornsilk" allowtransparency="true">
<frameset id="QARfs2" cols="*,1" border=0 frameborder=0 framespacing=0>
<frame src="refControl.php<?php
if (count($_GET)) {
  $cnt = false;
  foreach ( $_GET as $k => $v ) {
    if ($cnt) { print "&"; }
    else { print "?"; $cnt = true; }
    print "${k}=${v}";
  }
}
?>" name="QARcfr" scrolling=auto onmouseover="setFS1Show()"
  style="background:cornsilk" allowtransparency="true">
<frame src="blank.html" name="QARofr" scrolling=auto onmouseover="setFS1Show()"
  style="background:cornsilk" allowtransparency="true">
</frameset>
<frame src="blank.html" name="QARmfr" scrolling=auto onmouseover="setFS1Hide()"
   style="background:cornsilk" allowtransparency="true">
</frameset>
</html>
