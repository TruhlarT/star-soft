<?php

function beginSectionHelp($name,$idx,$color,$disp) {
    print "<div id =\"${name}\"\n";
    print "       style=\"display:${disp} ;z-index:${idx}; background-color:${color}\">\n";
}

function beginSection($name,$title,$index,$color) {
    $idx = abs($index);
    beginSectionHelp("no${name}",$idx,$color,($index > 0 ? "block" : "none"));
    print "<span onclick=\"toggleSection('${name}')\"><i><u>${title}</u></i> ";
    print "<img src=\"http://www.milonic.com/imagepack/Arrows/Arrow%203/Arrow3_black3d_10x13.gif\">\n";
    print "</span></div>\n";
    beginSectionHelp("full${name}",$idx,$color,($index < 0 ? "block" : "none"));
    print "<span onclick=\"toggleSection('${name}')\"><i><u>${title}</u></i> ";
    print "<img src=\"http://www.milonic.com/imagepack/Arrows/Downarrows/Down%20Arrow%203/Downarrow3_black_16x10.gif\">\n";
    print "</span><br>\n";
}

function endSection() {
  print "</div>\n";
}

function jsToggleSection() { ?>
    function toggleSection(section) {
      noSection = document.getElementById('no' + section);
      fullSection = document.getElementById('full' + section);
      temp = noSection.style.display;
      noSection.style.display = fullSection.style.display;
      fullSection.style.display = temp;
      return false;
    }
<?php
}

?>
