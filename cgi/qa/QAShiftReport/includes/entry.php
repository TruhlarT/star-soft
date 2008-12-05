<?php

incl("issues.php");

###############################
# Class and functions for Data Entry handling
#

# Data Entries are stored in the session directory
# They hold infomation about the file examined and
# an array of active issues.

class qaentry {
  var $type;
  var $info;
  var $issues;
  
  function qaentry($typ) {
    (existsType($typ)) or died("Entry cannot be created with type: " . $typ);
    $this->type = $typ;
    $this->issues = array();
    $this->info = array(
      "runid"     => "0000000",
      "prodid"    => "0",
      "prodstat"  => "ok",
      "fseq"      => "NA",
      "nevents"   => "0",
      "nprivs"    => "0",
      "jobstat"   => "ok",
      "rcomments" => ""
    );
  }

  function Fill($passed) {
    # Only allow info element and issues (xID)
    foreach ($passed as $key => $val) {
      if (substr($key,0,1) == "x") {
        $id = substr($key,1);
        if (cleanInt($id)) { $this->AddIssue($id); }
      } elseif (isset($this->info[$key])) {
        # Be strict about types
        switch($key) {
          case "runid"     :
          case "nevents"   :
          case "nprivs"    : cleanInt($val); break;
          case "prodid"    :
          case "fseq"      :
          case "jobstat"   : cleanStrict($val); break;
          default          :
        }
        $this->info[$key] = $val;
      }
    }
  }

  function HasRunId() {
    return (($this->type != "MDP") && ($this->type != "MNT"));
  }
  
  function AddIssue($id) {
    if ($id < 0) {
      $ids = strval(-1 * $id);
      if ($id > -100) {
        global $issueYear;
        $issueYear = $ids;
      }
      # Remove issue if it is active
      unset($this->issues[$ids]);
      return;
    }
    $ids = strval($id);
    global $issueList,$issuePrev;
    readIssList($this->type);
    if ($id > 1) {
      # Add a specific issue unless unknown
      if (isset($issueList[$ids])) { $this->issues[$ids] = $issueList[$ids][0]; }
    } else {
      # Add all previous issues ($id==1)
      foreach ($issuePrev as $k => $issid) {
        $this->issues[$issid] = $issueList[$issid][0];
      }
    }
  }
    
  function InfoText() {
    global $ents;
    $str = "-----------------------------------------------------------------------";
    $str .= "\nData Entry for " . $ents[$this->type] . ":\n";
    if ($this->HasRunId()) {
      $str .= "\n   Run ID:                                 " . $this->info["runid"];
    }
    $str .= "\n   File Sequence number:                   " . $this->info["fseq"];
    $str .= "\n   Production Job ID:                      " . $this->info["prodid"];
    $str .= "\n   Production job status (OK or crashed?): " . $this->info["prodstat"];
    $str .= "\n   Number of events in this file:          " . $this->info["nevents"];
    $str .= "\n   Number of events with reconstructed";
    $str .= "\n      primary vertex:                      " . $this->info["nprivs"];
    $str .= "\n   QA job status (OK or crashed?):         " . $this->info["jobstat"];
    if (strlen($this->info["rcomments"]) > 0) {
      $str .= "\n\n   Comments for this run:\n\n";
      $str .= $this->info["rcomments"] . "\n";
    }
    $str .= "\n";
    return $str;
  }

  function Text() {
    $str = $this->InfoText();
    if (count($this->issues) > 0) {
      $str .= "\n   Issues:\n";
      foreach ($this->issues as $issid => $isstxt) {
        $str .= "  [ID:${issid}]  ${isstxt}\n";
      }
    } else {
      $str .= "\n  No issues.\n";
    }
    return $str;
  }
  
  function Anchor() {
    $rundigits = (intval($this->info["runid"])>9999999 ? 8 : 7);
    return $this->type . "_" . nDigits($rundigits,$this->info["runid"])
                       . "_" . ndigits(7,$this->info["fseq"]);
  }
  function Html() {
    $str = "<a name=\"". $this->Anchor() . "\">\n<pre>";
    $str .= preserve_wordwrap(htmlentities(stripslashes($this->InfoText())),75,chr(10));
    $str .= "</pre>\n";
    if (count($this->issues) > 0) {
      $str .= "\nIssues:\n<ul>\n";
      foreach ($this->issues as $issid => $isstxt) {
        $str .= "<li><a href=\"" . getIssWebLink($issid) . "\"";
        $str .= " target=\"QAifr\">";
        $str .= "[ID:${issid}]  " . stripslashes($isstxt) . "</a>\n";
      }
      $str .= "</ul>\n";
    } else {
      $str .= "\nNo issues.<br>\n";
    }
    $str .= "<p>\n";
    return $str;
  }
  
  function UpdateIssues() {
    clearIssPrev($this->type);
    foreach ($this->issues as $issid => $isstxt) {
      if ($iss = readIssue($issid)) { $iss->Update($this->type); }
    }
  }
  
  function Save($numn=-1) {
    $file = "";
    $num = intval($numn);
    if ($num < 0) {
      $file = tempEntry();
    } else {
      if ($num == 0) {
        $rcntfile = getSesDir() . ".count_" . $this->type;
        if ($obj = readInt($rcntfile)) { $num = $obj; }
        $num++;
        saveObject($num,$rcntfile);
      }
      $file = fileEntry($this->type,$num);
      $this->UpdateIssues();
    }
    saveObject($this,$file);
    logit("Saved Entry: " . $this->type . " $num");
  }

}

function tempEntry() { return getSesDir() . ".temp.data"; }
function fileEntry($typ,$num) {
  if (existsType($typ)) {
    $numf = nDigits(3,$num);
    return getSesDir() . "${typ}${numf}.data";
  }
  return "";
}

function readObjectEntry($file) { return readObjectClass($file,"qaentry"); }
function readEntry($typ,$num=-1) {
  $file = "";
  if ($num == -1) { $file = tempEntry(); }
  else { $file = fileEntry($typ,$num); }
  return readObjectEntry($file);
}


?>
