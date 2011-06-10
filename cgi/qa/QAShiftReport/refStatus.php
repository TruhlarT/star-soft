<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  
  getPassedInt("status");
  
  head("QA Reference Histogram Status");
  body();
  
  print "<h3>";
  switch ($status) {
    case 1 :
      #print "Processing (this could take several minutes)....please wait...."; break;
      inclR("ProgressBar.class.php");
      print "Processing (this could take several minutes)....please wait....<hr>\n";
      print "<img src=\"/~genevb/STARevent.gif\"><br><br>\n";
      #$elements = 1;
      #for ($cnt=0;$cnt<66;$cnt++) {
      #  $bar = new ProgressBar("",true,0,400,20,"cornsilk","navy","progBar$cnt");
      #  $bar->initialize($elements);
      #  for($i=0;$i<$elements;$i++){
      #    sleep(5);
      #    $bar->increase();
      #  }
      #}
      #print "This really seems to be taking too long."; break;
      break;

    case -99 :
      print "Invalid reference set!"; break;
    case -98 :
      print "Timeout waiting too long for results"; break;
    case -97 :
      print "The daemon was just now started up and mistakenly flushed your job" .
             " along with 'stale' requests. Plesae try again."; break;
    case -96 :
      print "The daemon had an error processing your job." .
      " You might try a different job or different run."; break;
    case -95 :
      print "Timeout waiting too long for file combining"; break;
    case -94 :
      print "The daemon had an error combining files for your job." .
      " You might try a different run."; break;
    case -93 :
      print "The AutoCombined file is no longer in the index. This may be due to" .
      " a very recent update of the file (new file sequences were added)," .
      " or flushing due to age. Please go back (select" .
      " \"Back to data selections\") and try again.";
      $status = 0; break;
    case -91 :
      print "FOLocations table has no entry for the DiskLoc code for this data file." .
      " It may have been deleted from disk."; break;
    case -89 :
      print "No output plots were generated!"; break;
    case -79 :
      print "There was a problem recording the analysis results."; break;
    case -78 :
      print "There was a problem reading the recorded analysis results."; break;
    case -65 :
      print "Timeout waiting too long for file combining"; break;
    case -64 :
      print "The daemon had an error combining files for your job." .
      " You might try a different run."; break;
    case -1 :
      print "Processing FAILED!"; break;
      
  }
  print "</h3>\n\n";

  if ($status < 0) {
    print "Please contact the administrator and report this error:\n";
    print "<a href=\"mailto:gene@bnl.gov\">G. Van Buren</a>\n";
    logit("Error Status: ${status}");
  }
  
  foot();
?>
