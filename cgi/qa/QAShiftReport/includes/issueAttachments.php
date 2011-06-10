<?php

global $issueAttachDB,$maxAttach;;
$issueAttachDB = "QAissueAttachments";
$maxAttach = 512;

  function IAgetFilename($idx) {
    global $bdir;
    return "${bdir}issueData/Item_${idx}.bin";
  }

  function IAgetFile($idx) {
    $file = IAgetFilename($idx);
    if (! file_exists($file)) {
      ckdir(dirname($file));
      if (!(IAreadDbToFile($idx,$file))) { return false; }
    }
    return $file;
  }

  function IAreadDbToFile($idx,$file) {
    global $issueAttachDB;
    $qry = "SELECT `data` FROM $issueAttachDB WHERE ABS(`serial`)='$idx';";
    $row = queryDBfirst($qry);

    @($fp = fopen($file,"wb")) or died("Problems opening attachments cache for writing.");
    flock($fp,LOCK_EX);
    @(fwrite($fp,$row['data'])) or died("Problems writing attachments to cache.");
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems closing attachments cache for writing.");

    return filesize($file);
  }

  function IAwriteFileToDb($id) {
    global $issueAttachDB;
    $data = IAreadAttachment("temp");
    if (!$data) { return false; }
    $qry = "INSERT INTO $issueAttachDB (`issueID`,`data`) VALUES ('$id','$data');";
    queryDB($qry);
    return getDBid();
  }

  function IAreadAttachment($idx) {
    $file = IAgetFile($idx);
    if ($file === false) { return false; }
    @($fp = fopen($file,"rb")) or died("Problems opening attachments cache for reading.");
    flock($fp,LOCK_EX);
    @($data = escapeDB(@fread($fp,@filesize($file)))) or died("Problems reading attachments from cache.");
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems closing attachments cache for reading.");
    return $data;
  }

  function IAtoggleActive($idx) {
    global $issueAttachDB;
    $str = "UPDATE $issueAttachDB SET `entryTime`=`entryTime`,`serial`=-1*`serial`";
    $str .= " WHERE ABS(`serial`)='$idx';";
    queryDB($str);
  }
    
  function IAlistOfAttachments($id) {
    global $issueAttachDB;
    $qry = "SELECT `serial`,`entryTime` FROM $issueAttachDB WHERE `issueID`='$id'";
    $qry .= " ORDER BY `entryTime` ASC;";
    $res = queryDB($qry);
    $data = array();
    while ($row = nextDBrow($res)) { $data[] = $row; }
    return $data;
  }

  function IAtableOfAttachments($id) {
    $list = IAlistOfAttachments($id);
    $nlist = count($list);
    if ($nlist > 0) {
      print "<table border=1 cellspacing=0 callpadding=0><tr><td>\n";
      print "<table border=0 cellspacing=3 callpadding=0>\n";
      print "<tr><th>Attached image(s) for this issue</th>\n";
      print "<th align=right>Serial # & entry timestamp</th></tr>";
      foreach ($list as $k => $v) {
        $active = ($v['serial'] > 0);
        $idx = abs($v['serial']);
        print "<tr><td>";
        if ($active) {
          #print "<img src=\"" . IAgetFile($idx) . "\">\n";
          print "<img src=\"/~starweb/tmp/QAShiftReport/issueData/" . basename(IAgetFile($idx)) . "\">\n";
        } else {
          print "(inactive)";
        }
        print "</td>\n<td valign=top>#" . nDigits(6,$idx) . "<br>";
        print $v['entryTime'] . "</td></tr>\n";
      }
      print "</table>\n</table>\n";
    } else {
      print "<b>No currently attached images.</b>\n";
    }
    return $nlist;
  }

  function IAformForAttachment($id) {
    global $maxAttach;
    #fstart("formIA","","_top enctype=\"multipart/form-data\"");
    print "<br>You may attach image files (e.g. a screen grab)";
    if ($id > 0) {
      print " <font size=-1>[GIF/JPEG/PNG/TIFF, ${maxAttach}kB max,";
      print " one file upload at a time,";
      print " please use wisely]</font>:<br>\n";
      print "<label for=\"upfile\">Image file to upload:</label>\n";
      print "<input type=\"file\" name=\"upfile\" id=\"upfile\">\n"; 
    } else {
      print " to an issue <b>after</b> it has been created &amp; saved.\n";
    }
    #fhidden("$id",$id);
    #fsubmit("Upload");
    #fend();
  }

  function IAattached() {
    global $_FILES;
    return (isset($_FILES) && isset($_FILES["upfile"]) &&
        (strlen($_FILES["upfile"]["name"]) > 0));
  }

  function IAhandleAttachment($id) {
    global $maxAttach,$_FILES;
    if ((($_FILES["upfile"]["type"] == "image/gif")
      || ($_FILES["upfile"]["type"] == "image/tiff")
      || ($_FILES["upfile"]["type"] == "image/jpeg")
      || ($_FILES["upfile"]["type"] == "image/pjpeg")
      || ($_FILES["upfile"]["type"] == "image/png"))
      && ($_FILES["upfile"]["size"] < $maxAttach * 1024)) {
      if ($_FILES["upfile"]["error"] > 0) {
        died("UPLOADING Error: " . $_FILES["file"]["error"]);
      } else {
        $str = "UPLOADING:\n  File: " . $_FILES["upfile"]["name"];
        $str .= "\n  Type: " . $_FILES["upfile"]["type"];
        $str .= "\n  Size: " . ($_FILES["upfile"]["size"] / 1024);
        $str .= "\n  Stored in: " . $_FILES["upfile"]["tmp_name"];
        logit($str);
        $file = IAgetFilename("temp");
        @(ckdir(dirname($file))) or died("Problems creating attachement cache");
        if (is_file($file)) { unlink($file); }
        @(move_uploaded_file($_FILES["upfile"]["tmp_name"], $file)) or
          died("Problems moving attachment file");
        $idx = IAwriteFileToDb($id);
        rename($file,IAgetFilename($idx));
      }
    } else {
      linebreak();
      print "<b>New image upload failed!</b> Invalid file (please check type or size).<br>\n";
      logit("Invalid upload file: " . $_FILES["upfile"]["name"] . " ("
            . $_FILES["upfile"]["type"] . " , "
            . $_FILES["upfile"]["size"] . ")");
    }
  }

?>
