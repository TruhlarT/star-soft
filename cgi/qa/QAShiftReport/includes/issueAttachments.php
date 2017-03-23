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

    @($fp = fopen($file,"wb")) or died("Problems opening attachments cache for writing.",$file);
    flock($fp,LOCK_EX);
    @(fwrite($fp,$row['data'])) or died("Problems writing attachments to cache.",$file);
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems closing attachments cache for writing.",$file);

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
    @($fp = fopen($file,"rb")) or died("Problems opening attachments cache for reading.",$file);
    flock($fp,LOCK_EX);
    @($data = escapeDB(@fread($fp,@filesize($file)))) or died("Problems reading attachments from cache.",$file);
    flock($fp,LOCK_UN);
    @(fclose($fp)) or died("Problems closing attachments cache for reading.",$file);
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
    $qry .= " ORDER BY SIGN(`serial`) DESC, `entryTime` ASC;";
    $res = queryDB($qry);
    $data = array();
    while ($row = nextDBrow($res)) { $data[] = $row; }
    return $data;
  }

  function IAtableOfAttachments($id,$listInactive) {
    $list = IAlistOfAttachments($id);
    $nlist = count($list);
    $ninactive = 0;
    if ($nlist > 0) {
      print "<table cellspacing=3 callpadding=0 style=\"border: solid 1px black; \">\n";
      print "<tr><th>Attached image(s) for this issue</th>\n";
      print "<th align=right>Serial # & entry timestamp</th></tr>";
      foreach ($list as $k => $v) {
        $active = ($v['serial'] > 0);
        if (!$active) { $ninactive++; }
        if ($active || $listInactive) {
          $idx = abs($v['serial']);
          print "<tr><td>";
          if ($active) {
            print "<img src=\"/~starweb/tmp/QAShiftReport/issueData/" . basename(IAgetFile($idx)) . "\">\n";
          } else {
            print "(inactive) ";
            fbutton("IAtog${idx}","Re-activate","JustView(${idx})");
          }
          print "</td>\n<td valign=top>#" . nDigits(6,$idx) . "<br>";
          print $v['entryTime'];
          if ($active) {
            linebreak();
            fbutton("IAtog${idx}","De-activate","JustView(${idx})");
          }
          print "</td></tr>\n";
        } # list it
      } # foreach
      print "<tr><td colspan=2>\n";
      if ($ninactive > 0) {
        if ($listInactive) {
          fbutton("IAinact","Hide inactive attachments","JustView(0)");
        } else {
          fbutton("IAinact","List inactive attachments","JustView(-1)");
        }
      } else {
        print "<font size=-1>No inactive attachments</font>\n";
      }
      print "</td></tr>\n</table>\n";
    } else {
      print "<b>No currently attached images.</b>\n";
    }
    return $nlist - $ninactive;
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

  function IAhandleAttachmentHelp($id,$input,$mode) {
    # mode = 0 => uploaded
    #      = 1 => direct copy
    $file = IAgetFilename("temp");
    @(ckdir(dirname($file))) or died("Problems creating attachement cache",$file);
    if (is_file($file)) { unlink($file); }
    $func = ($mode > 0 ? "copy" : "move_uploaded_file");
    @($func($input, $file)) or
      died("Problems copying attachment file",$file);
    $idx = IAwriteFileToDb($id);
    rename($file,IAgetFilename($idx));
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
        IAhandleAttachmentHelp($id,$_FILES["upfile"]["tmp_name"],0);
      }
    } else {
      linebreak();
      print "<b>New image upload failed!</b> Invalid file (please check type or size).<br>\n";
      logit("Invalid upload file: " . $_FILES["upfile"]["name"] . " ("
            . $_FILES["upfile"]["type"] . " , "
            . $_FILES["upfile"]["size"] . ")");
    }
  }

  function IAcheckDirectAttachment($id) {
    global $attach;
    $attach = "";
    getPassedVarStrict("attach",1);
    if (strlen($attach)) {
      global $bdir_tmp, $suffix;
      getPassedVarStrict("suffix");
      $directFile = "${bdir_tmp}${attach}.${suffix}";
      @(is_file($directFile)) or died("Problems finding attachment file",$directFile);
      IAhandleAttachmentHelp($id,$directFile,1);
      unlink($directFile);
    }
  }

?>
