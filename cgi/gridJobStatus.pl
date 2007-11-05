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
    lgpath      => '$',
    glstat      => '$',
    glerr       => '$', 
    lgstat      => '$',
    exstat      => '$',
    intrs       => '$',
    outtrs      => '$',
    rftime      => '$',
    crtime      => '$',
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
#$JobStatusT = "JobStatus"."_".$dyear;

$JobStatusT = "JobStatus_06";

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
my $sdate = "0000-00-00 00:00:00:";
my $cretime = "0000-00-00 00:00:00:";
my $sbtime = "0000-00-00 00:00:00:";
my $gsite;
my $njobs = 0;
my %siteH = { };
my $globeff = 0;
my $logeff = 0;
my $inputef = 0;
my $outputeff = 0;
my $recoComeff = 0;
my $overeff = 0;
my %globEfH = { };
my %logEfH = { };
my %inEfH  = { };
my %outEfH  = { };
my %recoEfH = { };
my %overEfH = { };
my %siteEff = { };
my $nreco = 0;
my @sites = ();
my $msite;

my @viewopt = ("jobs_browser","efficiency");

my @logar = ();
my @globar = ();

$logar[0] = "failed";
$logar[1] = "incomplete";
$logar[2] = "complete";

$globar[0] = "failed";
$globar[1] = "OK";

my @infile = ();
my @outfile = ();

$infile[0] = "failed";
$infile[1] = "complete";

$outfile[0] = "failed";
$outfile[1] = "incomplete";
$outfile[2] = "incomplete";
$outfile[3] = "incomplete";
$outfile[4] = "incomplete";
$outfile[5] = "complete";
$outfile[6] = "complete";
$outfile[7] = "complete";
$outfile[8] = "complete";

my $globSt;
my $logSt;
my $inSt;
my $outSt;

 
  &GRdbConnect();

  $sql="SELECT DISTINCT testday  FROM $JobStatusT order by testday ";

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

 my $qdate  =  $query->param('testdate');
 my $qsite  =  $query->param('testsite');
 my $qview  =  $query->param('voption');

 if( $qdate eq "" and $qsite eq "" and $qview eq "" ) {


print $query->header;
print $query->start_html('Grid Jobs status');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Grid Jobs Site Status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";  
print "<h3 align=center> Date of Test</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'testdate',
                             -values=>\@ardays,
                             -default=>$maxday,
                             -size =>1); 


print "<p>";
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "<h3 align=right> Test Site</h3>";
print "<h4 align=right>";
print  $query->scrolling_list(-name=>'testsite',
                             -values=>\@arsites,
                             -default=>ALL,
                             -size =>1); 

print "<p>";
print "</td><td>"; 
print "</td><td>";
print "</td><td>";
print "<h3 align=center> How do you like to view</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'voption',
                             -values=>\@viewopt,
                             -default=>jobs_browser,
                             -size =>1); 

print "<p>";
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

 my $qdate  =  $qqr->param('testdate');
 my $qsite  =  $qqr->param('testsite');
 my $qview  =  $qqr->param('voption');

 print $qqr->header;
 print $query->start_html('Grid Jobs status on Site');
 print "<body bgcolor=\"cornsilk\">\n";
# print "<h1 align=center><u>Grid jobs status on $qsite site for day $qdate </u></h1>\n";
# print "<br>";

   &GRdbConnect();

  if( $qsite eq "ALL" ) {

      $sql="SELECT submissionTime, site, inputFile, logpath, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, recoFinishTime, createTime FROM $JobStatusT WHERE testday = ? order by id "; 

       $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
     $cursor->execute($qdate);

  }else{

     $sql="SELECT submissionTime, site, inputFile, logpath, globusStatus, globusError, logStatus, execStatus, transfer_in, transfer_out, recoFinishTime, createTime FROM $JobStatusT WHERE testday = ? and site = ?  order by id  ";

 

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
      ($$fObjAdr)->lgpath($fvalue)    if( $fname eq 'logpath');
      ($$fObjAdr)->glstat($fvalue)    if( $fname eq 'globusStatus');
      ($$fObjAdr)->glerr($fvalue)     if( $fname eq 'globusError');
      ($$fObjAdr)->lgstat($fvalue)    if( $fname eq 'logStatus');
      ($$fObjAdr)->exstat($fvalue)    if( $fname eq 'execStatus');          
      ($$fObjAdr)->intrs($fvalue)     if( $fname eq 'transfer_in');  
      ($$fObjAdr)->outtrs($fvalue)    if( $fname eq 'transfer_out'); 
      ($$fObjAdr)->rftime($fvalue)    if( $fname eq 'recoFinishTime');
      ($$fObjAdr)->crtime($fvalue)    if( $fname eq 'createTime');

        }
       $jbstat[$nstat] = $fObjAdr;
        $nstat++;
      }

my $maxout = 5;


if( $qview eq "jobs_browser")  {

 print "<h1 align=center><u>Grid jobs status on $qsite site for day $qdate </u></h1>\n";
 print "<br>"; 

   &beginHtml();

    foreach $jstat (@jbstat) {

    $sbtime    = ($$jstat)->subtime;
    $gsite     = ($$jstat)->tsite; 
    $glStatus  = ($$jstat)->glstat; 
    $inFile    = ($$jstat)->infile;
    $lpath     = ($$jstat)->lgpath;
    $glError   = ($$jstat)->glerr;
    $lgStatus  = ($$jstat)->lgstat;
    $intrans   = ($$jstat)->intrs;
    $outtrans  = ($$jstat)->outtrs; 
    $recoSt    = ($$jstat)->exstat;
    $sdate     = ($$jstat)->rftime;
    $cretime    = ($$jstat)->crtime;

  
   if( $outtrans >= $maxout ) {
        $maxout = $outtrans ;
    }

    if($recoSt eq "submitted") {

    $globSt = "n/a";
    $logSt = "n/a";
    $glError = 0;
    $inSt = "n/a";
    $outSt = "n/a";
     &printClRow();


  }elsif( $recoSt eq "executing" ) {

   $globSt = "n/a";
    $logSt = "n/a";
    $glError = 0;
    $inSt = "n/a";
    $outSt = "n/a";
     &printExcRow();

  }elsif( $recoSt eq "not_completed" ) {

    $globSt = $globar[$glStatus];
    $logSt = $logar[$lgStatus];
    $inSt = $infile[$intrans]; 
    $outSt =$outfile[$outtrans];
     &printFldRow();

    }else{

    $globSt = $globar[$glStatus];
    $logSt = $logar[$lgStatus];
    $inSt = $infile[$intrans]; 
    $outSt =$outfile[$outtrans];

    &printRow();
   }
  }
 
   }else{

   print "<h1 align=center><u>Efficiency of jobs execution for $qsite site on day $qdate </u></h1>\n";
 print "<br>"; 

   &beginEffHtml();

 %siteH = { };
 %globEfH = { };
 %logEfH = { };
 %inEfH  = { };
 %outEfH  = { };
 %recoEfH = { };
 %overEfH = { };
 %siteEff = { };

   $nreco = 0;

      foreach $jstat (@jbstat) {

    $sbtime    = ($$jstat)->subtime;
    $gsite     = ($$jstat)->tsite; 
    $glStatus  = ($$jstat)->glstat; 
    $inFile    = ($$jstat)->infile;
    $glError   = ($$jstat)->glerr;
    $lgStatus  = ($$jstat)->lgstat;
    $intrans   = ($$jstat)->intrs;
    $outtrans  = ($$jstat)->outtrs; 
    $recoSt    = ($$jstat)->exstat;
    $sdate     = ($$jstat)->rftime;
    $cretime    = ($$jstat)->crtime;


   if( $outtrans >= $maxout ) {
        $maxout = $outtrans ;
    }


    if( $glError == 129 ) {
	$glStatus = 1;
   }

    $siteH{$gsite}++; 

    if( $recoSt eq "Done" ) { 
    $nreco = 1;
   } else{ 
    $nreco = 0;
  }


    $globEfH{$gsite} = $globEfH{$gsite} + $glStatus;
    $logEfH{$gsite} =  $logEfH{$gsite} +  $lgStatus;
    $inEfH{$gsite} = $inEfH{$gsite} + $intrans;   
    $outEfH{$gsite} = $outEfH{$gsite} + $outtrans;
    $recoEfH{$gsite} = $recoEfH{$gsite} + $nreco;

   if( $glStatus == 1 && $lgStatus >= 1 && $intrans == 1 && $outtrans >= 5 && $nreco == 1 ) {

       $siteEff{$gsite}++;

  }

}
   for($ii = 0; $ii <scalar(@sites); $ii++) {

   $msite = $sites[$ii]; 
       if( $siteH{$msite} >= 1 ) {
   $njobs = $siteH{$msite};
   $globeff = $globEfH{$msite}*100/$njobs;
   $logeff = $logEfH{$msite}*100/(2*$njobs);
   $inputef = $inEfH{$msite}*100/$njobs;
   $outputeff = $outEfH{$msite}*100/($maxout*$njobs);
   $recoComeff = $recoEfH{$msite}*100/$njobs; 
   $overeff = $siteEff{$msite}*100/$njobs;
     
   &printEffRow();

     }
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
          <title>Grid Jobs Status on Sites</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center></h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Site</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Input File</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log Path</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Globus Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Globus Error</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Input Transfer</B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=50><B>Output Transfer</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Reco Status</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Submission Time<br>EST</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Reco Finish Time<br>site local</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Files Created at Time<br>EST</B></TD>
</TR> 
   </head>
    <body>
END
}

#####################################

sub beginEffHtml {

print <<END;
  <html>
   <head>
          <title>Grid Jobs Status on Sites</title>
   </head>
   <body BGCOLOR=\"#ccffff\">
     <h1 align=center></h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Site</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Number of jobs submitted</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Globus efficiency in %</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Log transfer <br> efficiency in %</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Input Transfer <br>efficiency in % </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Output Transfer <br> efficiency in % </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Reco completion <br> efficiency in % </B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=50><B>Overall efficiency in %</B></TD>
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
<td>$lpath</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$sbtime</td>
<td>$sdate</td>
<td>$cretime</td>
</TR>
END

}


############### 
sub printClRow {

print <<END;
<TR BGCOLOR=\"#D8BFD8\" ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$lpath</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$sbtime</td>
<td>$sdate</td>
<td>$cretime</td>
</TR>
END

}

############### 
sub printExcRow {

print <<END;
<TR BGCOLOR=lightgreen ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$lpath</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$sbtime</td>
<td>$sdate</td>
<td>$cretime</td>
</TR>
END

}

############### 
sub printFldRow {

print <<END;
<TR BGCOLOR=\"#ffdc9f\" ALIGN=CENTER>
<td>$gsite</td>
<td>$inFile</td>
<td>$lpath</td>
<td>$globSt</td>
<td>$glError</td>
<td>$logSt</td>
<td>$inSt</td>
<td>$outSt</td>
<td>$recoSt</td>
<td>$sbtime</td>
<td>$sdate</td>
<td>$cretime</td>
</TR>
END

}

############### 
sub printEffRow {

print <<END;
<TR ALIGN=CENTER>
<td>$msite</td>
<td>$njobs</td>
<td>$globeff</td>
<td>$logeff</td>
<td>$inputef</td>
<td>$outputeff</td>
<td>$recoComeff</td>
<td>$overeff</td>
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
