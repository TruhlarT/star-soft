<?php

@(include "setup.php") or die("Problems (0).");
incl("entrytypes.php");
incl("infohandling.php");
incl("data2text.php");
getPassedVarStrict("mode");

$ses = needSesName();
$sesDir = getSesDir($ses);

# Deleting some of the data entries:
if ($mode == "Delete") {
  foreach ($_POST as $pname => $pval) {
    if (substr($pname,0,3) == "del") {
      if (cleanAlphaFileName($pval)) {
        $rfile = $sesDir . $pval;
        unlink($rfile);
      }
    }
  }

# Copying a session
} elseif (substr($mode,0,4) == "Copy") {
  $olddir = substr($mode,4);
  if (cleanAlphaFileName($olddir)) {
    cpdir(getSesDir($olddir),$sesDir);
  }
  getPassedInt("play");
  setPlaySes($ses,$play);
}

# Now list the contents

head("STAR QA Shift Report File List");
jstart();
?>
  function nogo() {
    if (navigator.appName == 'Netscape') {
      astr = "Sorry.\nEdit and Copy are not currently ";
      astr += "available to Netscape users.";
      alert(astr);
      return;
    }
  }
  function Edit(typ,todo,num) {
    form = document.editForm;
    form.type.value = typ;
    form.num.value = num;
    form.editit.value = todo;
    form.submit();
  }
  var numA = 0;
  var allChecked = false;
  function checkAll() {
    allChecked = !allChecked;
    form = document.delFiles;
    for (i = 0; i < numA; i++) {
      field = eval("form.del" + i);
      field.checked = allChecked;
    }
  }
<?php
jend();
body();

print "<h3>QA Shift Report Form: Contents [${ses}]</h3>\n\n";

fstart("showReport","showRep.php","new");
fsubmit("View Full Report");
fhidden("content","");
fend();
fstart("delFiles","contents.php");

print "<p>\n<table border=0 callpadding=0 cellspacing=0>\n";

$infoFile = getInfoFile();
if (file_exists($infoFile)) {
  print "<tr><td></td><td>\n";
  mkhref("showRep.php?content=Info","Shift Info","new");
  print "</td><td>\n";
  fbutton("Einfo","Edit","Edit('Info','yes',0)");
} else {
  print "<tr><td colspan=3 bgcolor=#ffbc9f>\n";
  print "<b>YOU NEED TO RE-ENTER YOUR SHIFT INFO!</b>\n";
}
print "</td></tr>\n\n";
$allents = "InfoWrapup";

$numA = 0;
foreach ($ents as $typ => $entN) {
  $entFiles = dirlist($sesDir,$typ,".data");
  sort($entFiles);
  if (count($entFiles) > 0) {
    print "<tr><td><br></td></tr>\n<tr><td colspan=3>\n";
    print "$entN data entries:\n<br>\n";
    print "</td></tr>\n";
    $duplicates = 0;
    $listOfRFS = array();
    foreach ($entFiles as $k => $entFile) {
      $entFileEnd = substr($entFile,3);
      $numb = intval(substr($entFileEnd,0,strpos($entFileEnd,".data")));
      if ($entr = readEntry($typ,$numb));
        $dname = "del" . $numA;
        print "<tr><td>\n";
        print "<input type=checkbox name=${dname}";
        print "  value=\"${entFile}\">\n";
        print "</td><td>\n";
        $allents .= d2tdelim() . $entFile;

        # insert run/fseq:
        $runfseq = $entr->info["runid"] . " / " . $entr->info["fseq"];
        if (isset($listOfRFS[$runfseq])) $duplicates = 1;
        else $listOfRFS[$runfseq] = 1;

        mkhref("showRep.php?content=${entFile}","${numb} : ${runfseq}","new");
        print "</td><td>\n";
        fbutton("E${dname}","Edit","Edit('${typ}','yes',${numb})");
        fbutton("C${dname}","Make Copy","Edit('${typ}','copy',${numb})");
#        fbutton("D${dname}","Copy To Different Session","Edit('${typ}','dupl',${numb})");
        print "</td></tr>\n\n";
        $numA++;
    }
    if ($duplicates) {
      print "<tr><td colspan=3 bgcolor=#ffbc9f>\n";
      print "WARNING: duplicate run / file sequence entries!\n</td></tr>\n\n";
    }
  }
}

print "</table><p>\n\n";

if ($numA > 0) {
  fbutton("unselector","(Un)Select All Entries","checkAll()");
  fhidden("mode","Delete");
  fsubmit("Delete Selected Data Entries");
}
fend();

fstart("editForm","formData.php");
fhidden("work",$ses);
fhidden("type","");
fhidden("editit","yes");
fhidden("num","0");
fend();

jstart();
print "    document.showReport.content.value = \"${allents}\";\n";
print "    numA = ${numA};\n";
jend();
reloadMenu();
foot();
?>
