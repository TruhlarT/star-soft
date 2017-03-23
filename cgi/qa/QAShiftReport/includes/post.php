<?php

incl("files.php");

function shiftLogPost($data) {
  return webPost("http://online.star.bnl.gov/apps/shiftLog/private/addWebSummry.jsp",$data);
}

function webPost($url,$params) {
  $curl = curl_init(); 
  curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST ) ; 
  curl_setopt($curl, CURLOPT_USERPWD, o1u2("o1r0o0s1d1a2t0c2d0:0 301,0D1n0e2_2g0b3!0")); 
  curl_setopt($curl, CURLOPT_SSLVERSION,3); 
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE); 
  curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 2); 
  curl_setopt($curl, CURLOPT_HEADER, true); 
  curl_setopt($curl, CURLOPT_POST, true); 
  curl_setopt($curl, CURLOPT_POSTFIELDS, $params ); 
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, true); 
  curl_setopt($curl, CURLOPT_USERAGENT, $_SERVER["HTTP_USER_AGENT"]); 
  curl_setopt($curl, CURLOPT_URL, $url); 

  $data = curl_exec($curl);
  $idx1 = strpos($data,"Content-Type");
  $idx2 = strpos($data,"Content-Type",$idx1+10);
  $idx3 = strpos($data,"\r\n",$idx2+10);
  $res = substr($data,$idx3+4);
  return $res;
}

?>
