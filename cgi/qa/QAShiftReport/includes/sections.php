<?php

function beginSectionHelp($section,$idx,$color,$disp) {
    print "<div id =\"${section}\"\n";
    print "       style=\"display:${disp} ;z-index:${idx}; background-color:${color}\">\n";
}

function beginSection($section,$title,$index,$color) {
    $idx = abs($index);

    beginSectionHelp("no${section}",$idx,$color,($index > 0 ? "block" : "none"));
    print "<span onclick=\"toggleSection('${section}')\"><i><u>${title}</u></i> ";
    print "&#9658;";
    print "</span></div>\n";

    beginSectionHelp("full${section}",$idx,$color,($index < 0 ? "block" : "none"));
    print "<span onclick=\"toggleSection('${section}')\"><i><u>${title}</u></i> ";
    print "&#9660;";
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
    function toggleSections(section) {
      idx = 0;
      temp1 = '';
      temp2 = '';
      while (1) {
        noSection = document.getElementById('no' + section + idx);
        if (noSection) {
           fullSection = document.getElementById('full' + section + idx);
           if (idx == 0) {
             temp1 = noSection.style.display;
             temp2 = fullSection.style.display;
           }
           noSection.style.display = temp2;
           fullSection.style.display = temp1;
           idx++;
        } else { break; }
      }
      return false;
    }
    function hiddenSection(section) {
      fullSection = document.getElementById('full' + section);
      return (fullSection.style.display == "none");
    }
<?php
}

?>
