<?php

incl("issues.php");
incl("entrytypes.php");

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
      "runid"     => array(),
      "prodid"    => "0",
      "prodstat"  => "ok",
      "fseq"      => "NA",
      "nevents"   => "0",
      "nprivs"    => "0",
      "jobstat"   => "ok",
      "rcomments" => "",
      "fstream"   => ""
    );
  }

  function Fill($passed) {
    # Only allow info element and issues (xID)
    # Use runidN for multiple run numbers
    $this->CheckRunId();
    $initRunIds = true;
    foreach ($passed as $key => $val) {
      if (substr($key,0,1) == "x") {
        $id = substr($key,1);
        if (cleanInt($id)) { $this->AddIssue($id); }
      } elseif (substr($key,0,5) == "runid") {
        $rk = (strlen($key) > 5 ? substr($key,5) : 0);
        if (cleanInt($val) && ($val > 0)) {
          if ($initRunIds) {
            $this->info["runid"] = array();
            $initRunIds = false;
          }
          $this->info["runid"][$rk] = $val;
        }
      } elseif (array_key_exists($key,$this->info)) {
        # Be strict about types
        switch($key) {
          case "nevents"   :
          case "nprivs"    : cleanInt($val); break;
          case "prodid"    :
          case "fseq"      :
          case "fstream"   :
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

  function CheckRunId() {
    # To handle backward compatibility of old persistant instances
    $runid = $this->info["runid"];
    if (! is_array($runid)) {
      $this->info["runid"] = (intval($runid) > 0 ? array($runid) : array());
    }
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
      $this->CheckRunId();
      if (count($this->info["runid"])) {
        $str .= "\n   Run Number(s):                          " . implode(",",$this->info["runid"]);
      }
    }
    if (existsTrigType($this->info["fseq"])) {
      $str .= "\n   Trigger Type:                           " . $this->info["fseq"];
    } else {
      $str .= "\n   File Sequence number:                   " . $this->info["fseq"];
    }
    $str .= "\n   File stream:                            " . formatFStream($this->info["fstream"]);
    if ($this->info["prodid"] > 0) {
      $str .= "\n   Production Job ID:                      " . $this->info["prodid"];
      $str .= "\n   Production job status (OK or crashed?): " . $this->info["prodstat"];
      $str .= "\n   QA job status (OK or crashed?):         " . $this->info["jobstat"];
    }
    $str .= "\n   Number of events in this file:          " . $this->info["nevents"];
    $str .= "\n   Number of events with reconstructed";
    $str .= "\n      primary vertex:                      " . $this->info["nprivs"];
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
        $str .= "  [ID:${issid}]  " . getCategoryForIssue($issid) . " : ${isstxt}\n";
      }
    } else {
      $str .= "\n  No issues.\n";
    }
    return $str;
  }
  
  function Anchor() {
    $this->CheckRunId();
    return AnchorTRFS($this->type,$this->info["runid"][0],
                      $this->info["fseq"],$this->info["fstream"]);
  }

  function Headline($delim) {
    $this->CheckRunId();
    #return HeadlineRFS($this->info["runid"][0],$this->info["fseq"],$this->info["fstream"]);
    $runHeadlines = array();
    foreach ($this->info["runid"] as $runid) {
      $runHeadlines[] = HeadlineRFS($runid,$this->info["fseq"],$this->info["fstream"]);
    }
    return implode($delim,$runHeadlines);
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
        $str .= "[ID:${issid}]  <font size=-1><i>" . getCategoryForIssue($issid);
        $str .= "</i></font> : " . stripslashes($isstxt) . "</a>\n";
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
    # a negative parameter means save a temporary copy
    # non-negative params indicate the entry number in a report
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
      if (! isPlaySes()) { $this->UpdateIssues(); }
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
  # a negative parameter means read the temporary copy
  # non-negative params indicate the entry number in a report
  $file = "";
  if ($num == -1) { $file = tempEntry(); }
  else { $file = fileEntry($typ,$num); }
  #return readObjectEntry($file);
  $entr = readObjectEntry($file);
  $entr->CheckRunId();
  return $entr;
}

function formatFseq($var) {
  return (existsTrigType($var) ? $var : nDigits(7,$var));
}
function formatRun($var) {
  $rundigits = (intval($var)>9999999 ? 8 : 7);
  return nDigits($rundigits,$var);
}
function formatFStreamLink($var) {
  global $fstreams;
  $isAKey = false;
  return (existsFStreamType($var,$isAKey) ? "_" . ($isAKey ? $var : array_search($var)) : "" );
}
function formatFStream($var) {
  global $fstreams;
  $isAKey = false;
  return (existsFStreamType($var,$isAKey) ? ($isAKey ? $fstreams[$var] : $var) : "" );
}
function AnchorTRFS($type,$run,$fseq,$fstream) {
  return $type . "_" . formatRun($run)
               . "_" . formatFseq($fseq)
                     . formatFStreamLink($fstream);
}
function HeadlineRFS($run,$fseq,$fstream) {
  return formatRun($run) . " / " . formatFseq($fseq) . " / " . formatFStream($fstream);
}


?>
