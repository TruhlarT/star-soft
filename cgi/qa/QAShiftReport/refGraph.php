<?php
  
  @(include "refSetup.php") or die("Problems (0).");
  @inclR("refRecords.php");
  
  global $refphp;
  
  getPassedVarStrict("name");
  getPassedVarStrict("opt");

  if (!getPassedVarStrict("plot",1)) {
  
    helpButton(13);

    print "<table border=0 width=\"100%\"><tr>";
    print "<td align=center><u>Trends plot for <b>${name}</b></u></td><td align=right>";
    print "</td></tr>\n<tr><td>Results vs. ...<br>\n";

    print "<input type=\"radio\" name=\"opt\" onclick=\"ViewTrends(1)\" value=\"1\" ";
    if ($opt == 1) { print " checked=\"checked\""; }
    print ">date data was taken<br>\n";
    print "<input type=\"radio\" name=\"opt\" onclick=\"ViewTrends(2)\" value=\"2\" ";
    if ($opt == 2) { print " checked=\"checked\""; }
    print ">date data was processed<br>\n";
    print "<input type=\"radio\" name=\"opt\" onclick=\"ViewTrends(3)\" value=\"3\" ";
    if ($opt == 3) { print " checked=\"checked\""; }
    print ">run number<br>\n";
    print "<input type=\"radio\" name=\"opt\" onclick=\"ViewTrends(4)\" value=\"4\" ";
    if ($opt == 4) { print " checked=\"checked\""; }
    print ">date results were recorded<br>\n";
    
    print "</td><td align=right valign=middle>";
    fbutton("hideTrends","Close trends plot","HideTrends()");
    print "</td></table>\n";
    print "<img border=1 src=\"${refphp}.php?plot&name=${name}&opt=${opt}\">";

  } else {
   
    # Generate the graph
    
    switch ($opt) {
      case 1 : $yidx = "sTime"; $xidx = "seTime"; break;
      case 2 : $yidx = "pTime"; $xidx = "prTime"; break;
      case 3 : $yidx = "runNumber"; $xidx = $yidx; break;
      case 4 : $yidx = "eTime"; $xidx = "enTime"; break;
    }
    
    $res = getRecordedResults($name,$yidx);
    $values = array();
    $cvalues = array();
    $redIds = array();
    $xlabels = array();
    $idx = 0;
    while ($row = nextDBrow($res)) {
      $idx = $row[$yidx];
      if ($row[$xidx] > 0) {
        $xlabels[$idx] = $row[$xidx];
        $values[$idx] = $row['result'];
        $cvalues[$idx] = $row['cut'];
        $refIds[$idx] = $row['refId'];
      }
    }
    
    $img_width=640;
    $img_height=300; 
    $margins=20;
    
    
    # ---- Find the size of graph by substracting the size of borders
    $graph_width=$img_width - $margins * 3;
    $graph_height=$img_height - $margins * 2; 
    $img=imagecreate($img_width,$img_height);
    
    
    # -------  Define Colors ----------------
    $std_color = imagecolorallocate($img,0,64,128);
    $cut_color = imagecolorallocate($img,202,0,0);
    $id_color = imagecolorallocate($img,0,160,0);
    $background_color = imagecolorallocate($img,255,255,255);
    $border_color = imagecolorallocate($img,220,220,220);
    $line_color = imagecolorallocate($img,220,220,220);
    
    # ------ Create the border around the graph ------
    
    imagefilledrectangle($img,1,1,$img_width-2,$img_height-2,$border_color);
    imagefilledrectangle($img,$margins*2,$margins,$img_width-1-$margins,$img_height-1-$margins,$background_color);
    
    
    # ------- Max value is required to adjust the vertical scale	-------
    $max_value = 1.1*max(max($values),max($cvalues));
    if ($max_value > 0.5) { $max_value = 1.1; }
    $ratioY = $graph_height/$max_value;
    
    # ------- Min & max values are required to adjust the horizontal scale	-------
    $indices = array_keys($values);
    $firstIdx = min($indices);
    $lastIdx = max($indices);
    $ratioX = 0.9 * $graph_width/($lastIdx - $firstIdx);
    $offsetX = 0.05 * $graph_width;
    
    
    # -------- Create scale and draw horizontal lines  --------
    $horizontal_lines=11;
    $line_spacing=$graph_height/$horizontal_lines;
    
    for($i=1;$i<$horizontal_lines;$i++){
      $y=$img_height - $margins - $line_spacing * $i ;
      imageline($img,$margins*2,$y,$img_width-$margins,$y,$line_color);
      $v=floor(1000*($line_spacing * $i /$ratioY))/1000.;
      imagestring($img,0,5,$y-5,$v,$std_color);
    }
    
    imagestring($img,0,$margins*2-10,$img_height-15,$xlabels[$firstIdx],$std_color);
    imagestring($img,0,$graph_width-5,$img_height-15,$xlabels[$lastIdx],$std_color);
    imagestring($img,4,$img_width*0.4,$margins*0.25,$name,$std_color);
    
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
    
    
    # ----------- Draw the lines here ------
    $x1 = -1; $y1 = 0; $c1 = 0; $prevId = -1;
    foreach($values as $idx => $value) {
      $x2 = $margins*2 + intval(($idx - $firstIdx) * $ratioX) + $offsetX ;
      $y2 = $margins + $graph_height - intval($value * $ratioY) ;
      $c2 = $margins + $graph_height - intval($cvalues[$idx] * $ratioY) ;
      if ($refIds[$idx] != $prevId) {
        imageline($img,$x2,$margins + $graph_height - intval($max_value * $ratioY),
                  $x2,$margins + $graph_height - intval($max_value * 0.96 * $ratioY),$id_color);
        imageline($img,$x2,$margins + $graph_height - intval($max_value * 0.04 * $ratioY),
                  $x2,$margins + $graph_height,$id_color);
        $prevId = $refIds[$idx];
      }
      if ($x1 > 0) {
        imageline($img,$x1,$c1,$x2,$c2,$cut_color);
        imageline($img,$x1,$y1,$x2,$y2,$std_color);
      }
      $marker = array($x2,$y2-2,$x2-1,$y2+1,$x2+1,$y2+1);
      imagepolygon($img,$marker,3,$std_color);
      $x1 = $x2; $y1 = $y2; $c1 = $c2;
    }
    header("Content-type:image/png");
    imagepng($img);
    
  }
  
?>
