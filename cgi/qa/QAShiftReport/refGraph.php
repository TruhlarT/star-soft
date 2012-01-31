<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  @incl("issues.php");

  # default parameters
  $defRange = "auto";
  $defWidth = 720;
  $defHeight = 300;
  $opt = 1;
  $iss = 0;
  $minX = $defRange;
  $maxX = $defRange;
  $minY = $defRange;
  $maxY = $defRange;
  $img_width=$defWidth;
  $img_height=$defHeight;
  $adj = 0;

  # passed parameters
  getPassedVarStrict("name");
  getPassedInt("opt",1);
  getPassedInt("iss",1);
  getPassedVar("minX",1);
  getPassedVar("maxX",1);
  getPassedVar("minY",1);
  getPassedVar("maxY",1);
  getPassedInt("img_width",1);
  getPassedInt("img_height",1);
  getPassedInt("adj",1);
  
  $xIsDate = ($opt < 4);
  #$dformat = "Y-m-d H:i:s";
 

  # create page first, then call again with "plot" to deliver image

  
  if (!getPassedVarStrict("plot",1)) {

    # *************** Generate the HTML ***************

    @incl("sections.php");
    helpButton(13);

    fstart("graphForm","","");

    print "<table border=0 width=\"100%\"><tr>";
    print "<td align=center><u>Trends plot for <b>${name}</b></u></td><td align=right>";

    # Plotting options
    $opts = array(1 => "date data was taken",
                  2 => "date data was processed",
                  3 => "date results were recorded",
                  4 => "run number");
    print "</td></tr>\n<tr><td>Results vs. ...<br>\n";
    foreach ($opts as $optn => $optstr) {
      print "<input type=\"radio\" name=\"optn\" "
      . "onclick=\"ReViewTrends(${optn})\" value=\"${optn}\" ";
      if ($opt == $optn) { print " checked=\"checked\""; }
      print ">${optstr}<br>\n";
    }

    # Issue overlays
    print "Overlay issue:\n";
    global $issueList,$whichBrowser;
    getWhichBrowser();
    $fstr = "ReViewTrends(${opt})";
    readIssList("FRP");
    if (count($issueList)) {
      $issList = array_reverse($issueList,SORT_NUMERIC);
      print onSelect("iss",$fstr);
      print "<option value=0 " . ($iss == 0 ? "selected" : "") . ">none</option>\n";
      foreach ($issList as $id => $issData) {
        print "<option value=${id}";
        if ($iss == $id) { print " selected"; }
        print ">${id}</option>\n";
      }
      print "</select>\n";
      if ($iss > 0) {
        print "<font size=-1>";
        mkhref("issueEditor.php?iid=${iss}",$issueList[$iss][0],"QAifr");
        print "</font>\n";
      }
    }

    print "</td><td align=right valign=middle>";
    fbutton("hideTrends","Close trends plot","HideTrends()");
    print "</td></table>\n";

    # Plot adjustments
    beginSection("adjusters","Adjust plot ranges",($adj ? -2000 : 2000),$myCols["emph"]);
    print "<table border=0><tr><td><nobr>X axis min: </nobr>";
    finput("minX",21,$minX);
    print "</td><td><nobr>X axis max: </nobr>";
    finput("maxX",21,$maxX);
    print "</td><td>";
    fbutton("autoX","Auto","SetAuto('X')");
    if ($xIsDate) { print "<font size=-1><i>(times in GMT)</i></font>"; }
    print "</td></tr>\n<tr><td><nobr>Y axis min: </nobr>";
    finput("minY",6,$minY);
    print "</td><td><nobr>Y axis max: </nobr>";
    finput("maxY",6,$maxY);
    print "</td><td>";
    fbutton("autoY","Auto","SetAuto('Y')");
    print "</td></tr>\n<tr><td><nobr>Image width: </nobr>";
    finput("img_width",6,$img_width);
    print "</td><td><nobr>Image height: </nobr>";
    finput("img_height",6,$img_height);
    print "</td><td>";
    fbutton("autoS","Auto","SetAuto('S')");
    print "</td></tr>\n<tr><td colspan=3>";
    fbutton("rePlot","Re-Plot",$fstr);
    print "</table>\n";
    endSection();
    fhidden("adj",$adj);

    fend();
    global $refphp;
    print "<img height=${img_height} width=${img_width}"
    . "border=1 src=\"${refphp}.php?plot";
    foreach ( $_GET as $k => $v ) { print "&${k}=${v}"; }
    print "\">";

    jstart();
    $cmpr = ($xIsDate ? ">" : "<"); // switching between date and runnumbers
    ?>
    var form = document.graphForm;
    function ReViewTrends(opt) {
      form.adj.value = (hiddenSection('adjusters') ? 0 : 1);
      if (opt <?php print $cmpr; ?> 3.5) SetAuto('X'); 
      args = "&opt=" + opt;
      elem = form.elements;
      for (i = 0; i < elem.length; i++) {
        args += "&" + elem[i].name + "=" + elem[i].value;
      }
      ViewTrends(args);
    }
    function SetAuto(par) {
      if (par == 'S') {
        form.img_width.value = <?php print $defWidth; ?>;
        form.img_height.value = <?php print $defHeight; ?>;
      } else {
        e1 = eval("form.min" + par);
        e2 = eval("form.max" + par);
        e1.value = "<?php print $defRange; ?>";
        e2.value = "<?php print $defRange; ?>";
      }
    }
    <?php
    jend();
  
  } else {
   
    # *************** Generate the graph ***************

    @inclR("refRecords.php");
    
    # ---- Obtain sorted and limited values ----
    switch ($opt) {
      case 1 : $idxSort = "sTime"; $idxLabels = "seTime"; break;
      case 2 : $idxSort = "pTime"; $idxLabels = "prTime"; break;
      case 3 : $idxSort = "eTime"; $idxLabels = "enTime"; break;
      case 4 : $idxSort = "runNumber"; $idxLabels = $idxSort; break;
    }
    
    $idxMin = false;
    if ($minX != $defRange) {
      if ($xIsDate) {
        $idxMin = "UNIX_TIMESTAMP(\"${minX}\")";
      } else {
        $idxMin = $minX;
      }
    }
    $idxMax = false;
    if ($maxX != $defRange) {
      if ($xIsDate) {
        $idxMax = "UNIX_TIMESTAMP(\"${maxX}\")";
      } else {
        $idxMax = $maxX;
      }
    }

    $res = getRecordedResults($name,$idxSort,$idxMin,$idxMax);

    $values = array();
    $xvalues = array();
    $cvalues = array();
    $redIds = array();
    $xlabels = array();
    $runs = array();
    $min_label = false;
    $max_label = false;
    while ($row = nextDBrow($res)) {
      if ($row[$idxLabels] > 0) {
        $xlabels[] = $row[$idxLabels];
        $values[] = $row['result'];
        $xvalues[] = $row[$idxSort];
        $cvalues[] = $row['cut'];
        $refIds[] = $row['refId'];
        $runs[] = $row['runNumber'];
        if (! $min_label) { $min_label = $row[$idxLabels]; }
        $max_label = $row[$idxLabels];
      }
    }
    
    
        
    # ---- Find the size of graph by substracting the size of borders
    $margins=20;
    $graph_width=$img_width - $margins * 3;
    $graph_height=$img_height - $margins * 2; 
    $img=imagecreate($img_width,$img_height);
    
    
    # -------  Define Colors ----------------
    $std_color = imagecolorallocate($img,0,64,128);
    $line_color = imagecolorallocate($img,32,96,160);
    $cut_color = imagecolorallocate($img,202,0,0);
    $id_color = imagecolorallocate($img,0,160,0);
    $iss_color = imagecolorallocate($img,255,255,63);
    $background_color = imagecolorallocate($img,255,255,255);
    $border_color = imagecolorallocate($img,220,220,220);


    # ------- Define horizontal & vertical scales	-------
    # define x scale
    if ($minX == $defRange) {
      $min_x = $xvalues[0];
      $min_label = $xlabels[0];
    } else {
      $min_x = ($xIsDate ? strtotime($minX . " GMT") : $minX);
      $min_label = $minX;
    }
    if ($maxX == $defRange) {
      $lastIdx = count($xvalues)-1;
      $max_x = $xvalues[$lastIdx];
      $max_label = $xlabels[$lastIdx];
    } else {
      $max_x = ($xIsDate ? strtotime($maxX) : $maxX);
      $max_label = $maxX;
    }
    $min_xval = $min_x;
    $max_xval = $max_x;
    $margin_x = ($max_x - $min_x)*0.01;
    $min_x -= $margin_x;
    $max_x += $margin_x;
    $ratioX = $graph_width/($max_x - $min_x);
    $offsetX = $margins*2;
    
    # define y scale
    $min_value = ($minY == $defRange ? 0 : $minY);
    if ($maxY == $defRange) {
      $max_value = max(max($values),max($cvalues));
      if ($max_value > 0.5 && $minY == $defRange) { $max_value = 1.0; }
      $max_value = 1.1*($max_value - $min_value) + $min_value;
    } else {
      $max_value = $maxY;
    }
    $ratioY = $graph_height/($max_value-$min_value);
    $offsetY = $margins + $graph_height;

    # scale helper functions and variables
    function graphx($x) { 
      global $offsetX,$ratioX,$min_x;
      return $offsetX + intval($ratioX * ($x - $min_x));
    }
    function graphy($y) { 
      global $offsetY,$ratioY,$min_value;
      return $offsetY - intval($ratioY * ($y - $min_value));
    }
    $ymin = graphy($min_value);
    $ymax = graphy($max_value);
    $xmin = graphx($min_xval);
    $xmax = graphx($max_xval);
    $xmin2 = $offsetX;
    $xmax2 = $offsetX + $graph_width - 1;
    

    # ------ Create the border around the graph ------
    imagefilledrectangle($img,1,1,$img_width-2,$img_height-2,$border_color);
    imagefilledrectangle($img,$xmin2,$ymax,$xmax2,$ymin,$background_color);
    
    
    # ------ If drawing an issue, create highlight areas ------
    if ($iss > 0) {
      $rlist = getListOfRunsForIssue($iss);
      $state = false;
      $x1 = -1;
      $x2 = -1;
      foreach($values as $i => $value) {
        $issActive = in_array($runs[$i],$rlist);
        if ($state != $issActive) {
          if ($state) {
            imagefilledrectangle($img,graphx($x1),$ymax,graphx($x2),$ymin,$iss_color);
          } else {
            $x1 = $xvalues[$i];
          }
          $state = $issActive;
        }
        $x2 = $xvalues[$i];
      }
      if ($state) {
        imagefilledrectangle($img,graphx($x1),$ymax,graphx($x2),$ymin,$iss_color);
      }
    }
    
    
    # -------- Create scales and draw horizontal lines  --------

    # Y axis lines and labels
    $horizontal_lines=11;
    $line_spacing=($max_value-$min_value)/$horizontal_lines;
    $digfactor = pow(10,intval(2.0-log10($max_value-$min_value)));
    for($i=1;$i<$horizontal_lines;$i++){
      $y = $min_value + $line_spacing * $i ;
      $gy = graphy($y);
      imageline($img,$xmin2,$gy,$xmax2,$gy,$border_color);
      $label = intval($digfactor * $y)/$digfactor;
      imagestring($img,0,5,$gy-5,$label,$std_color);
    }
    
    # X axis labels
    $chrwidth = imagefontwidth(0);
    imageline($img,$xmin,$ymin,$xmin,$ymin+6,$std_color);
    imageline($img,$xmax,$ymin,$xmax,$ymin+6,$std_color);
    $x1 = $xmin - 3 * $chrwidth;
    imagestring($img,0,$x1,$img_height-13,$min_label,$std_color);
    $x1 = $xmax - (strlen($max_label)-3) * $chrwidth;
    imagestring($img,0,$x1,$img_height-13,$max_label,$std_color);

    # plot title
    imagestring($img,4,0.5*($img_width-imagefontwidth(4)*strlen($name)),
                $margins*0.25,$name,$std_color);

    # legend
    $x1 = $img_width-18;
    $x2 = $img_width-10;
    $y1 = $img_height*0.45;
    $y2 = $img_height*0.75;
    $y3 = $img_height*0.2;
    imageline($img,$x2,$y1+10,$x2,$y1+30,$cut_color);
    imagestringup($img,2,$x1,$y1,"cut",$cut_color);
    imageline($img,$x2,$y2+10,$x2,$y2+30,$std_color);
    imagestringup($img,2,$x1,$y2,"result",$std_color);
    $y2 += 20;
    $marker = array($x2-2,$y2,$x2+1,$y2-1,$x2+1,$y2+1);
    imagepolygon($img,$marker,3,$std_color);
    imageline($img,$x2,$y3+10,$x2,$y3+30,$id_color);
    imagestringup($img,2,$x1,$y3,"ref. chg.",$id_color);
    
    
    # ----------- Draw the markers & lines ------
    if (count($values)) {
      $x1 = -1; $y1 = 0; $c1 = 0; $prevId = -1;
      $ticklength = 0.04 * ($ymax - $ymin);
      $y3 = $ymax - $ticklength;
      $y4 = $ymin + $ticklength;
      foreach ($values as $i => $value) {
        $xval = $xvalues[$i];
        #if ($value < $min_value || $value > $max_value ||
        #    $xval < $min_xval || $xval > $max_xval) continue; # TO BE IMPROVED
        $x2 = graphx($xval);
        $y2 = graphy($value);
        $c2 = graphy($cvalues[$i]);
        $sameXY = ($x2 == $x1 && $y2 == $y1); # Reduce moot duplicates
        $sameXC = ($x2 == $x1 && $c2 == $c1); # Reduce moot duplicates
        if ($refIds[$i] != $prevId) {
          imageline($img,$x2,$ymax,$x2,$y3,$id_color);
          imageline($img,$x2,$y4,$x2,$ymin,$id_color);
          $prevId = $refIds[$i];
        }
        if ($x1 > 0) {
          if (! $sameXC) { imageline($img,$x1,$c1,$x2,$c2,$cut_color); }
          if (! $sameXY) { imageline($img,$x1,$y1,$x2,$y2,$line_color); }
        }
        if (! $sameXY) {
          $marker = array($x2,$y2-2,$x2-1,$y2+1,$x2+1,$y2+1);
          imagepolygon($img,$marker,3,$std_color);
          $x1 = $x2; $y1 = $y2;
        }
        $c1 = $c2;
      }
    } else {
      $str = "No data matching criteria";
      imagestring($img,5,0.5*($img_width-imagefontwidth(5)*strlen($str)),
                  0.5*$img_height,$str,$std_color);
    }

    
    # ---------- Output the plot ----------
    header("Content-type:image/png");
    imagepng($img);
    
  }
  
?>
