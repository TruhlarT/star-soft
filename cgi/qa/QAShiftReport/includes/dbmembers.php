<?php

incl("db.php");


function getMembersInstitutions() {
  # need to add "isQACertified" to the query when it's available
  startDbTemp("onldb2.starp.bnl.gov:3501","starweb","starweb","");
  $membsInsts = array();
  $str = "SELECT ii.`InstitutionName`,mm.`LastName`,mm.`FirstName`,mm.`Id` FROM institutions AS ii"
       . " LEFT JOIN members AS mm ON ii.`Id`=mm.`InstitutionId` WHERE mm.`isShifter`='Y'"
       . " ORDER BY 1,2,3";
  $results = queryDB($str);
  while ($row = nextDBrow($results)) {
    $k = $row['InstitutionName'];
    if (!(isset($membsInsts[$k]))) { $membsInsts[$k] = array(); }
    $membsInsts[$k][] = array($row['LastName'],$row['FirstName'],$row['Id']);
  }
  stopDbTemp();
  return $membsInsts;
}

function getMemberQAStatus($membId) {
  $qry = "SELECT `entryTime`,`lastShift`,`status`,`comments`,(STRCMP(`status`,'Qualified')=0 && DATEDIFF(CURRENT_TIMESTAMP,`lastShift`)>(5*365)) AS `shouldExpire` FROM QAShiftCertification WHERE `Id`=${membId}";
  return queryDBfirst($qry);
}

function getMembersQAStatusus() {
  $qry = "SELECT `Id`,`entryTime`,`lastShift`,`status`,`comments`,(STRCMP(`status`,'Qualified')=0 && DATEDIFF(CURRENT_TIMESTAMP,`lastShift`)>(5*365)) AS `shouldExpire` FROM QAShiftCertification";
  $result = queryDB($qry);
  $list = array();
  while ($row = nextDBrow($result)) {
    $membId = $row['Id'];
    $list["$membId"] = $row;
  }
  return $list;
}

function setMemberQAStatus($membId,$status,$comments,$lastShift="") {
  $commentsForDB = escapeDB($comments);
  $qry = "";
  $noLastShift = (strlen($lastShift) < 7);
  if (getMemberQAStatus($membId) === 0) {
    if ($noLastShift) $lastShift = "1996-01-01";
    $qry = "INSERT INTO QAShiftCertification (`Id`,`lastShift`,`status`,`comments`) VALUES (${membId},\"${lastShift}\",\"${status}\",\"${commentsForDB}\")";
  } else {
    if ($noLastShift) {
      $qry = "UPDATE QAShiftCertification SET `status`=\"${status}\",`comments`=\"${commentsForDB}\" WHERE `Id`=${membId}";
    } else {
      $qry = "UPDATE QAShiftCertification SET `status`=\"${status}\",`lastShift`=\"${lastShift}\",`comments`=\"${commentsForDB}\" WHERE `Id`=${membId}";
    }
  }
  return queryDB($qry);
}

?>
