<?php

@(include "refSetup.php") or die("Problems (0).");
inclR("refData.php");

getPassedInt("refID");

head("QA Refence Histograms: Info for Selected Set");
body();

print "<h3>Info for Selected Reference Histogram Set:</h3>\n";

if ($refID < 0) {
  print "</i>No reference set selected for analysis.";
  if ($refID == -999) { print "Plots made without comparison to reference set."; }
  print "</i>";
} else {
  $info = getInfoById($refID);
  if ($info == 0) {
    print "<i>Invalid set requested.</i>\n";
  } else {
    print "<table border=0 cellpadding=2 cellspacing=2>\n";
    print "<tr><td align=right><b><nobr>Run Year:</nobr></b></td>\n";
    print "<td align=left>" . $info['runYear'] . "</td></tr>\n";
    print "<tr><td align=right><b><nobr>Trigger Setup:</nobr></b></td>";
    print "<td align=left>" . $info['trig'] . "</td></tr>\n";
    print "<tr><td align=right><b>Version <font size=-1><nobr>(date entered)</nobr></font>:</b></td>";
    print "<td align=left>" . $info['vers'] . " <font size=-1>(" . $info['entryTime'] . " GMT)</font></td></tr>\n";
    print "<tr><td align=right><b><nobr>Set id #:</nobr></b></td>";
    print "<td align=left>${refID}</td></tr>\n";
    print "<tr><td align=right><b><nobr>Entered by:</nobr></b></td>";
    print "<td align=left>" . $info['user'] . "</td></tr>\n";
    print "<tr><td align=right valign=top><b>Comments:</b></td>";
    print "<td align=left>" . $info['comments'] . "</td></tr>\n";
    print "</table>\n";
  }
}

foot(); ?>
