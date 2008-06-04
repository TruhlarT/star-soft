#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L.Didenko
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI;
use Mysql;
use Class::Struct;
use File::Basename;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Scheduler_bnl";



 struct JobAttr => {
    subtime     => '$',
    tsite       => '$',
    infile      => '$', 
    prtag       => '$',
    glerr       => '$',
    errstat      => '$', 
    lgstat      => '$',
    exstat      => '$',
    intrs       => '$',
    outtrs      => '$',
    mxout       => '$',
    stat        => '$',
    rsubm       => '$',
    ovrstat     => '$',    
  };


($sec,$min,$hour,$mday,$mon,$year) = localtime;


if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $nowdate = ($year+1900)."-".($mon+1)."-".$mday;

my $thisyear = $year+1900;
my $dyear = $thisyear - 2000;

# Tables

$MasterJobEfficiencyT = "MasterJobEfficiency";
$IOStatusT = "MasterIO";


my @ardays = ();
my @arsites = ( );
my $mydate;
my $nd = 0;
my $nsite = 0;
my $maxday = "0000-00-00";

my $nstat = 0;
my $inFile = "none";
my $prodtag;
my $glError;
my $lgStatus;
my $errStatus;
my $logStatus = "unknown";
my $intrans;
my $outtrans;
my $recoSt;
my $sbtime = "0000-00-00 00:00:00";
my $gsite = "pdsf";
my $nresub = 0;
my $overstat = "unknown";
my $inStatus = "unknown";
my $outStatus = "unknown";
my $recoStatus = "unknown";

###############
my $globStatus;
my $logStatus;
my @recoStat = ();
$recoStat[0] = "unknown";
$recoStat[1] = "completed";
$recoStat[2] = "failed";
my @inStat = ();
$inStat[0] = "unknown";
$inStat[1] = "complete";
$inStat[2] = "failed";
my @outStat = ();
$outStat[0] = "unknown";
$outStat[1] = "complete";
$outStat[2] = "incomplete";
$outStat[3] = "failed";
my $jbstat;
my @logStat = ();
$logStat[0] = "unknown";
$logStat[1] = "incomplete";
$logStat[2] = "complete";
$logStat[3] = "failed";

##############

my $njobs = 0;
my @sites = ();
my $msite;
my $inName;
  
  &GRdbConnect();

  $sql="SELECT DISTINCT date_format(submitTime, '%Y-%m-%d') AS PDATE  FROM $MasterJobEfficiencyT order by PDATE ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

     while($mydate = $cursor->fetchrow) {
         
        $ardays[$nd] = $mydate;
        $nd++;    
    }
      $cursor->finish;         

 
  $maxday = $ardays[$nd-1];

  $sql="SELECT DISTINCT site FROM $MasterJobEfficiencyT where site is not NULL ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while($mysite = $cursor->fetchrow) {
        $arsites[$nsite] = $mysite;
        $nsite++;
      }

   $cursor->finish; 

  push @sites, @arsites;
  push @arsites, "ALL";
   
    &GRdbDisconnect();

 my $query = new CGI;

my $scriptname = $query->url(-relative=>1);

 my $qdate  =  $query->param('proddate');
 my $qsite  =  $query->param('prodsite');

 if( $qdate eq "" and $qsite eq "" ) {


print $query->header;
print $query->start_html('Grid Production Jobs status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Grid Production Status</u></h1>\n";
print "<br>";
print "<br>";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
END

print "<p>";
print "<td>";  
print "<h3 align=center> Date of Production</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'proddate',
                             -values=>\@ardays,
                             -default=>$maxday,
                             -size =>1); 


print "<p>";
print "</td><td>"; 
print "<h3 align=center> Production Site</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'prodsite',
                             -values=>\@arsites,
                             -default=>ALL,
                             -size =>1); 

print "</td><td>";
print "</td><td>";
print "</td><td>";
print "</td><td>";
print "</td> </tr> </table><hr><center>";
print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

  }else{

my $qqr = new CGI;

 my $qdate  =  $qqr->param('proddate');
 my $qsite  =  $qqr->param('prodsite');

my $qdates = "$qdate%";
my $qsites = "$qsite%";

 print $qqr->header;
 print $query->start_html('Grid Production Jobs status');
 print "<body bgcolor=\"cornsilk\">\n";
# print "<h1 align=center><u>Production jobs status on $qsite site for day $qdate </u></h1>\n";
# print "<br>";

$gsite = "none";
$prodtag = "none";
$inFile = "none";
$nresub = 0;
$sbtime = "0000-00-00 00:00:00";
$globStatus = "unknown";
$logStatus = "unknown";
$inStatus = "unknown";
$outStatus = "unknown";
$recoStatus = "unknown";
$jbstat = "unknown";
$overstat = "unknown";


   &GRdbConnect();

  if( $qsite eq "ALL" ) {

      $sql="SELECT $MasterJobEfficiencyT.jobID_MD5 as jobid, $MasterJobEfficiencyT.processID as prodid, submitTime, site, prodTag, submitAttempt, globusError, dotOutHasSize, dotErrorHasSize, exec, transIn, transOut, lastKnownState, overAllState, $IOStatusT.jobID_MD5, $IOStatusT.processID, name_workerNode FROM $MasterJobEfficiencyT, $IOStatusT WHERE submitTime like ? and $MasterJobEfficiencyT.jobID_MD5 = $IOStatusT.jobID_MD5 and $MasterJobEfficiencyT.processID = $IOStatusT.processID and isInputFile = 1 order by $MasterJobEfficiencyT.processID"; 

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qdates);

  }else{


     $sql="SELECT $MasterJobEfficiencyT.jobID_MD5 as jobid, $MasterJobEfficiencyT.processID as prodid, submitTime, site, prodTag, submitAttempt, globusError, dotOutHasSize, dotErrorHasSize, exec, transIn, transOut, lastKnownState, overAllState, $IOStatusT.jobID_MD5, $IOStatusT.processID, name_workerNode FROM $MasterJobEfficiencyT, $IOStatusT WHERE submitTime like ? and site = ? and $MasterJobEfficiencyT.jobID_MD5 = $IOStatusT.jobID_MD5 and $MasterJobEfficiencyT.processID = $IOStatusT.processID and isInputFile = 1 order by $MasterJobEfficiencyT.processID ";


     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qdates, $qsites);
} 

      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(JobAttr->new());

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

      ($$fObjAdr)->subtime($fvalue)   if( $fname eq 'submitTime');
      ($$fObjAdr)->tsite($fvalue)     if( $fname eq 'site');
      ($$fObjAdr)->infile($fvalue)    if( $fname eq 'name_workerNode');
      ($$fObjAdr)->prtag($fvalue)     if( $fname eq 'prodTag');
      ($$fObjAdr)->glerr($fvalue)     if( $fname eq 'globusError');
      ($$fObjAdr)->errstat($fvalue)   if( $fname eq 'dotErrorHasSize');
      ($$fObjAdr)->lgstat($fvalue)    if( $fname eq 'dotOutHasSize');
      ($$fObjAdr)->exstat($fvalue)    if( $fname eq 'exec');           
      ($$fObjAdr)->intrs($fvalue)     if( $fname eq 'transIn');  
      ($$fObjAdr)->outtrs($fvalue)    if( $fname eq 'transOut');
      ($$fObjAdr)->stat($fvalue)      if( $fname eq 'lastKnownState'); 
      ($$fObjAdr)->rsubm($fvalue)     if( $fname eq 'submitAttempt');
      ($$fObjAdr)->ovrstat($fvalue)   if( $fname eq 'overAllState');

         }
       $jbstat[$nstat] = $fObjAdr;
        $nstat++;
      }


 print "<h1 align=center><u>Grid production jobs status on $qsite site for day $qdate </u></h1>\n";
 print "<br>"; 

   &beginHtml();

    foreach $jstat (@jbstat) {

    $sbtime    = ($$jstat)->subtime;
    $gsite     = ($$jstat)->tsite; 
    $prodtag   = ($$jstat)->prtag; 
    $inName    = ($$jstat)->infile;
    $glError   = ($$jstat)->glerr;
    $lgStatus  = ($$jstat)->lgstat;
    $errStatus = ($$jstat)->errstat;
    $intrans   = ($$jstat)->intrs;
    $outtrans  = ($$jstat)->outtrs;
    $recoSt    = ($$jstat)->exstat;
    $jbstat    = ($$jstat)->stat;
    $nresub    = ($$jstat)->rsubm ;
    $overstat  = ($$jstat)->ovrstat;

   if($glError <= 0) {
    $globStatus = "OK";
  }else{
   $globStatus = "error ".$glError;
  }  
    $inFile = basename($inName);

    if($jbstat eq "done" or $jbstat eq "killed" ) {

    $inStatus = $inStat[$intrans];
    $outStatus = $outStat[$outtrans];
    $recoStatus = $recoStat[$recoSt];
    $logStatus = $logStat[$lgStatus+$errStatus];

  }else{

    $inStatus = $inStat[0];
    $outStatus = $outStat[0];
    $recoStatus = $recoStat[0];
    $logStatus = $logStat[0];

}

    if ($overstat eq "complete") {

	$overstat = "success";
    }
  
    if($jbstat eq "submit" or $jbstat eq "pend" ) {

     &printSbRow();


  }elsif( $jbstat eq "run" ) {

    &printExcRow();

  }elsif( $jbstat eq "held") {

     &printFldRow();

  }elsif( $jbstat eq "killed") {

         &printKlRow();

  }elsif( $jbstat eq "unknown") {
     
     &printUnkRow();

  }elsif( $jbstat eq "done" and $overstat eq "success") {

    &printRow();

   }elsif( $jbstat eq "done" and $overstat eq "failed") {

     &printFldRow();

   }
  }
 

    &GRdbDisconnect();

 print $qqr->end_html;

 &endHtml();

}

######################
sub GRdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub GRdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub beginHtml {

print <<END;
  <html>
   <head>
          <title>Grid Production Jobs Status</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center></h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Site</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Production tag</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Input file name</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>N Resubmit</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Submission Time</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Globus status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Log file<br> transfer status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Input file<br> transfer status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Output files transfer<br>status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Reco completion<br> status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Current job status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Overall performance<br> status</B></TD>


</TR> 
   </head>
    <body>
END
}


############### 
sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
</TR>
END

}


############### 
sub printSbRow {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
END

}

############### 
sub printExcRow {

print <<END;
<TR BGCOLOR=lightgreen ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
</TR>
END

}

############### 
sub printFldRow {

print <<END;
<TR BGCOLOR=\"#ffdc9f\" ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
</TR>
END

}


############### 
sub printKlRow {

print <<END;
<TR BGCOLOR=red ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
</TR>
END

}

############### 
sub printUnkRow {

print <<END;
<TR BGCOLOR=blue ALIGN=CENTER>
<td>$gsite</td>
<td>$prodtag</td>
<td>$inFile</td>
<td>$nresub</td>
<td>$sbtime</td>
<td>$globStatus</td>
<td>$logStatus</td>
<td>$inStatus</td>
<td>$outStatus</td>
<td>$recoStatus</td>
<td>$jbstat</td>
<td>$overstat</td>
</TR>
END

}

###############
sub endHtml {
my $Date = `/bin/date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created:  2008 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}
