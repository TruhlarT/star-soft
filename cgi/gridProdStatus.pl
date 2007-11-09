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


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="GridJobs";



 struct JobAttr => {
    subtime     => '$',
    tsite       => '$',
    infile      => '$', 
    glstat      => '$',
    glerr       => '$', 
    lgstat      => '$',
    exstat      => '$',
    intrs       => '$',
    outtrs      => '$',
    mxout       => '$',
    stat        => '$',
    rsbtime     => '$',
    rsubm       => '$',
    rglstat     => '$',
    rglerr      => '$', 
    rlgstat     => '$',
    rexstat     => '$',
    routtrs     => '$',
    rstat       => '$',
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

$JobStatusT = "ProductionJobs";

my @ardays = ();
my @arsites = ( );
my $mydate;
my $nd = 0;
my $nsite = 0;
my $maxday = "0000-00-00";

my @jbstat = ();
my $nstat = 0;
my $glStatus = 0;
my $inFile = "none";
my $glError = 0;
my $lgStatus = 0;
my $intrans = 0;
my $outtrans = 0;
my $recoSt = "not complete";
my $sbtime = "0000-00-00 00:00:00";
my $gsite;
my $nresub = 0;
my $rglSt = 0;
my $rglEr = 0;
my $rlgSt = 0;
my $rin = 0;
my $rout = 0;
my $rrecoSt = "not complete";
my $resbtime = "0000-00-00 00:00:00";
my $gsite;
my $globSt;
my $logSt;
my $inSt;
my $outSt;
my $glEr;
my $rglobSt;
my $rlogSt;
my $rinSt;
my $routSt;
my $jbstat;
my $jbrstat;
my $ovrestat;
my $njobs = 0;
my @sites = ();
my $msite;


my @logar = ();
my @globar = ();

$logar[0] = "failed";
$logar[1] = "incomplete";
$logar[2] = "complete";

$globar[0] = "failed";
$globar[1] = "OK";

my @infile = ();
my @outfile = ();
my $maxout = 5;

$infile[0] = "failed";
$infile[1] = "complete";

$outfile[0] = "failed";
 
  for ($i = 1; $i< $maxout; $i++) {
   $outfile[$i] = "incomplete";
  }
  
  &GRdbConnect();

  $sql="SELECT DISTINCT productionDate  FROM $JobStatusT order by productionDate ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

     while($mydate = $cursor->fetchrow) {
         
        $ardays[$nd] = $mydate;
        $nd++;    
    }
      $cursor->finish;

 
  $maxday = $ardays[$nd-1];

  $sql="SELECT DISTINCT site   FROM $JobStatusT ";

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

 print $qqr->header;
 print $query->start_html('Grid Production Jobs status');
 print "<body bgcolor=\"cornsilk\">\n";
# print "<h1 align=center><u>Production jobs status on $qsite site for day $qdate </u></h1>\n";
# print "<br>";

   &GRdbConnect();

  if( $qsite eq "ALL" ) {

      $sql="SELECT submissionTime, site, inputFile, maxoutfile, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, ovrStatus, resubmit, resubmitTime, rglobusStatus, rglobusError, rlogStatus, rexecStatus, rtransfer_out, resubmitStatus, ovresubmitStatus FROM $JobStatusT WHERE productionDate = ? order by id "; 

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qdate);

  }else{

     $sql="SELECT submissionTime, site, inputFile, maxoutfile, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, ovrStatus,resubmit, resubmitTime, rglobusStatus, rglobusError, rlogStatus, rexecStatus, rtransfer_out, resubmitStatus, ovresubmitStatus FROM $JobStatusT WHERE productionDate = ? and site = ?  order by id  ";

 

     $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qdate, $qsite);
} 

      while(@fields = $cursor->fetchrow) {
        my $cols=$cursor->{NUM_OF_FIELDS};
          $fObjAdr = \(JobAttr->new());

          for($i=0;$i<$cols;$i++) {
             my $fvalue=$fields[$i];
             my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

      ($$fObjAdr)->subtime($fvalue)   if( $fname eq 'submissionTime');
      ($$fObjAdr)->tsite($fvalue)     if( $fname eq 'site');
      ($$fObjAdr)->infile($fvalue)    if( $fname eq 'inputFile');
      ($$fObjAdr)->glstat($fvalue)    if( $fname eq 'globusStatus');
      ($$fObjAdr)->glerr($fvalue)     if( $fname eq 'globusError');
      ($$fObjAdr)->lgstat($fvalue)    if( $fname eq 'logStatus');
      ($$fObjAdr)->exstat($fvalue)    if( $fname eq 'execStatus');
      ($$fObjAdr)->mxout($fvalue)     if( $fname eq 'maxoutfile');           
      ($$fObjAdr)->intrs($fvalue)     if( $fname eq 'transfer_in');  
      ($$fObjAdr)->outtrs($fvalue)    if( $fname eq 'transfer_out');
      ($$fObjAdr)->stat($fvalue)      if( $fname eq 'ovrStatus'); 
      ($$fObjAdr)->rsbtime($fvalue)   if( $fname eq 'resubmitTime');
      ($$fObjAdr)->rsubm($fvalue)     if( $fname eq 'resubmit');
      ($$fObjAdr)->rglstat($fvalue)   if( $fname eq 'rglobusStatus');
      ($$fObjAdr)->rglerr($fvalue)    if( $fname eq 'rglobusError');
      ($$fObjAdr)->rlgstat($fvalue)   if( $fname eq 'rlogStatus');
      ($$fObjAdr)->rexstat($fvalue)   if( $fname eq 'rexecStatus');          
      ($$fObjAdr)->routtrs($fvalue)   if( $fname eq 'rtransfer_out');
      ($$fObjAdr)->rstat($fvalue)     if( $fname eq 'resubmitStatus');
      ($$fObjAdr)->ovrstat($fvalue)   if( $fname eq 'ovresubmitStatus'); 

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
    $glStatus  = ($$jstat)->glstat; 
    $inFile    = ($$jstat)->infile;
    $glError   = ($$jstat)->glerr;
    $lgStatus  = ($$jstat)->lgstat;
    $intrans   = ($$jstat)->intrs;
    $outtrans  = ($$jstat)->outtrs;
    $maxout    = ($$jstat)->mxout; 
    $recoSt    = ($$jstat)->exstat;
    $jbstat    = ($$jstat)->stat;
    $nresub    = ($$jstat)->rsubm ;
    $rglSt     = ($$jstat)->rglstat;
    $rglEr     = ($$jstat)->rglerr;
    $rlgSt     = ($$jstat)->rlgstat;
    $rout      = ($$jstat)->routtrs;
    $rrecoSt   = ($$jstat)->rexstat;
    $resbtime  = ($$jstat)->rsbtime;
    $jbrstat   = ($$jstat)->rstat;   
    $ovrestat  = ($$jstat)->ovrstat; 

  for ($i = 1; $i< $maxout; $i++) {
   $outfile[$i] = "incomplete";
  }

  $outfile[$maxout-1] = "incomplete";
  $outfile[$maxout] = "complete";

  
    if($jbstat eq "submitted" ) {

    $globSt = "n/a";
    $logSt = "n/a";
    $glError = 0;
    $inSt = "n/a";
    $outSt = "n/a";
    $rglobSt = "n/a";
    $rlogSt = "n/a";
    $rglError = 0;
    $rinSt = "n/a";
    $routSt = "n/a";
    $resbtime = "0000-00-00 00:00:00";
    $rrecoSt = "n/a";
    $jbrstat = "n/a";
    $ovrestat  = "n/a";

     &printSbRow();


  }elsif( $jbstat eq "executing" ) {

    $globSt = $globar[$glStatus];
    $logSt = "n/a";
    $inSt = "n/a";
    $outSt = "n/a";
    $rglobSt = "n/a";
    $rlogSt = "n/a";
    $rglError = 0;
    $routSt = "n/a";
    $resbtime = "0000-00-00 00:00:00";
    $rrecoSt = "n/a";
    $jbrstat = "n/a";
    $ovrestat  = "n/a";

    &printExcRow();

  }elsif( $jbstat eq "not_completed" or $jbstat eq "failed" or $jbstat eq "killed"  ) {

    $globSt = $globar[$glStatus];
    $logSt = $logar[$lgStatus];
    $inSt = $infile[$intrans]; 
    $outSt =$outfile[$outtrans];

  if( $nresub == 0 ) {
    $rglobSt = "n/a";
    $rglError = 0;
    $rlogSt = "n/a";
    $routSt = "n/a";
    $rinSt = "n/a";
    $resbtime = "0000-00-00 00:00:00";
    $rrecoSt = "n/a";
    $jbrstat = "n/a";
    $ovrestat  = "n/a";

  
 }else{ 

     if ($jbrstat eq "submitted") {

    $rglobSt = "n/a";
    $rglError = 0;
    $rlogSt = "n/a";
    $routSt = "n/a";
    $rinSt = "n/a";

 } elsif($jbrstat eq "executing") {

    $rglobSt = $globar[$rglSt];
    
    $rlogSt = "n/a";
    $routSt = "n/a";
    $rinSt = "n/a";     

 } else {

    $rglobSt = $globar[$rglSt];
    $rlogSt = $logar[$rlgSt];
    $routSt =$outfile[$rout];

  }
}

     &printFldRow();

    }else{

    $globSt = $globar[$glStatus];
    $logSt = $logar[$lgStatus];
    $inSt = $infile[$intrans]; 
    $outSt =$outfile[$outtrans];
    $rglobSt = "n/a";
    $rglError = 0;
    $rlogSt = "n/a";
    $routSt = "n/a";
    $rinSt = "n/a";
    $resbtime = "0000-00-00 00:00:00";
    $rrecoSt = "n/a";
    $jbrstat = "n/a";
    $ovrestat = "n/a";

    &printRow();
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
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Input File</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Submission Time</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Globus Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Globus Error</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Log Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Input Transfer</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Output Transfer</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Reco Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Overall Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmit</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Resubmission<br> Time</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Globus Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Globus Error</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Log Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Output Transfer</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Reco Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Resubmission<br> Overall Status</B></TD>

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
<td>$inFile</td>
<td>$sbtime</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$jbstat</td>
<td>$nresub</td>
<td>$resbtime</td>
<td>$rglobSt</td>
<td>$rglError</td>
<td>$rlogSt</td>
<td>$routSt</td>
<td>$rrecoSt</td>
<td>$ovrestat</td>
</TR>
END

}


############### 
sub printSbRow {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$sbtime</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$jbstat</td>
<td>$nresub</td>
<td>$resbtime</td>
<td>$rglobSt</td>
<td>$rglError</td>
<td>$rlogSt</td>
<td>$routSt</td>
<td>$rrecoSt</td>
<td>$ovrestat</td>
</TR>
END

}

############### 
sub printExcRow {

print <<END;
<TR BGCOLOR=lightgreen ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$sbtime</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$jbstat</td>
<td>$nresub</td>
<td>$resbtime</td>
<td>$rglobSt</td>
<td>$rglError</td>
<td>$rlogSt</td>
<td>$routSt</td>
<td>$rrecoSt</td>
<td>$ovrestat</td>
</TR>
END

}

############### 
sub printFldRow {

print <<END;
<TR BGCOLOR=\"#ffdc9f\" ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$sbtime</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$jbstat</td>
<td>$nresub</td>
<td>$resbtime</td>
<td>$rglobSt</td>
<td>$rglError</td>
<td>$rlogSt</td>
<td>$routSt</td>
<td>$rrecoSt</td>
<td>$ovrestat</td>
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
<!-- Created:  2006 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}
