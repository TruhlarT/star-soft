#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveJobStat.pl
#
# Retrive production jobs status
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
use Mysql;
use Class::Struct;


($sec,$min,$hour,$mday,$mon,$year) = localtime();

 $mon++;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation"; 

struct JobAttr => {
      jbname    => '$',
      jbst      => '$',
      jbtrk     => '$',
      stname    => '$',
      stcpu     => '$',
      jbcrtime  => '$',
      sttrk     => '$',
      jbevt     => '$',
      jbnode    => '$'
 };


my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');
my $qyear = $query->param('pyear');
my $qflag = $query->param('pflag');

my $JobStatusT = "JobStatus".$qyear; 


my @archain = ();

my $nst = 0;
my @jbstat = ();
my @jbStatus = ();
my @jbfName = ();
my @jbEvent = ();
my @jbctime = ();
my @jbtrack = ();
my @jbnoden = ();
my $nn = 0;

my @strName = ();
my @avgcpu = ();
my @avgtrck = ();

my $nsm = 0;
my $nk = 0;


my $jobname = $qtrg."%".$qprod."%";


  &StDbProdConnect();

   if( $qflag eq "jstat") {
 
  &beginJbHtml(); 

    $sql="SELECT jobfileName, jobStatus, NoEvents, avg_no_tracks, createTime, nodeID  FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and trigsetName = ? and jobStatus <> 'Done' and jobStatus <> 'n/a' and jobStatus <> 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'jobfileName');
                ($$fObjAdr)->jbst($fvalue)     if( $fname eq 'jobStatus');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'NoEvents');
                ($$fObjAdr)->jbtrk($fvalue)    if( $fname eq 'avg_no_tracks'); 
                ($$fObjAdr)->jbcrtime($fvalue) if( $fname eq 'createTime'); 
                ($$fObjAdr)->jbnode($fvalue)   if( $fname eq 'nodeID');                 
            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
   }
  
 }elsif($qflag eq "hpss") {

   &beginHpHtml();

     $sql="SELECT jobfileName, inputHpssStatus, NoEvents  FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and trigsetName = ? and inputHpssStatus like 'hpss_error%' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'jobfileName');
                ($$fObjAdr)->jbst($fvalue)     if( $fname eq 'inputHpssStatus');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'NoEvents');

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }

 }elsif($qflag eq "hung") {

   &beginHgHtml();

     $sql="SELECT jobfileName, jobStatus, NoEvents FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and trigsetName = ? and jobStatus = 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'jobfileName');
                ($$fObjAdr)->jbst($fvalue)     if( $fname eq 'jobStatus');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'NoEvents');                

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }
 }elsif($qflag eq "mudst") {

   &beginMuHtml();

     $sql="SELECT jobfileName, jobStatus, NoEvents, avg_no_tracks, date_format(createTime, '%Y-%m-%d') as PDATE FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and trigsetName = ? and jobStatus <> 'n/a' and jobStatus <> 'hung' and inputHpssStatus = 'OK' and outputHpssStatus = 'n/a'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'jobfileName');
                ($$fObjAdr)->jbst($fvalue)     if( $fname eq 'jobStatus');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'NoEvents');
                ($$fObjAdr)->jbtrk($fvalue)    if( $fname eq 'avg_no_tracks'); 
                ($$fObjAdr)->jbcrtime($fvalue)    if( $fname eq 'PDATE');               

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }

 }elsif($qflag eq "strcpu") {

   &beginStrHtml();

     $sql="SELECT distinct streamName, avg(CPU_per_evt_sec) FROM $JobStatusT  where prodSeries = ? and trigsetName = ? and jobStatus <> 'n/a' and  CPU_per_evt_sec >= 0.0001 group by streamName ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->stname($fvalue)   if( $fname eq 'streamName');
                ($$fObjAdr)->stcpu($fvalue)    if( $fname eq 'avg(CPU_per_evt_sec)');

           }
            $jbstat[$nsm] = $fObjAdr;
            $nsm++;
      }

 }elsif($qflag eq "sttrack") {

   &beginSttrkHtml();

     $sql="SELECT distinct streamName, avg(avg_no_tracks) FROM $JobStatusT  where prodSeries = ? and trigsetName = ? and jobStatus <> 'n/a' and  avg_no_tracks >= 1 group by streamName ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qprod,$qtrg);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->stname($fvalue)   if( $fname eq 'streamName');
                ($$fObjAdr)->sttrk($fvalue)    if( $fname eq 'avg(avg_no_tracks)');

           }
            $jbstat[$nsm] = $fObjAdr;
            $nsm++;
      }

   }else{

   &beginHtml();
 }

&StDbProdDisconnect(); 

 $nk =0;
 my @spl = ();

     if( $qflag eq "strcpu" ) {

      foreach  $pjob (@jbstat) {

       $strName[$nk] = ($$pjob)->stname;
       $avgcpu[$nk]  = ($$pjob)->stcpu;
       $avgcpu[$nk]  = sprintf("%.2f",$avgcpu[$nk]);
 

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$strName[$nk]</h3></td>
<td HEIGHT=10><h3>$avgcpu[$nk]</h3></td>
</TR>
END

    $nk++;
     }

  }

 $nk = 0;

     if( $qflag eq "sttrack" ) {

      foreach  $pjob (@jbstat) {

       $strName[$nk] = ($$pjob)->stname;
       $avgtrck[$nk]  = ($$pjob)->sttrk;

    if($avgtrck[$nk] <= 1.0 ) {
    $avgtrck[$nk] = sprintf("%.2f",$avgtrck[$nk]);
    }elsif($avgtrck[$nk] <= 10.0 ) {
    $avgtrck[$nk] = sprintf("%.1f",$avgtrck[$nk]);
    }else{
    $avgtrck[$nk] = int($avgtrck[$nk] + 0.5);
    }


print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$strName[$nk]</h3></td>
<td HEIGHT=10><h3>$avgtrck[$nk]</h3></td>
</TR>
END

    $nk++;
     }

  }

       foreach  $pjob (@jbstat) {

       $jbfName[$nn]  = ($$pjob)->jbname;      
       $jbStatus[$nn] = ($$pjob)->jbst;
       $jbEvent[$nn]  = ($$pjob)->jbevt;
       $jbtrack[$nn]  = ($$pjob)->jbtrk;
       $jbctime[$nn]   = ($$pjob)->jbcrtime;
       $jbnoden[$nn]   = ($$pjob)->jbnode;

     $jbnoden[$nn]=~ s/.rcf.bnl.gov//g;

    if( $qflag eq "jstat" ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbtrack[$nn]</h3></td>
<td HEIGHT=10><h3>$jbctime[$nn]</h3></td>
<td HEIGHT=10><h3>$jbnoden[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "mudst") {

 $jbctime[$nn]  = ($$pjob)->jbcrtime; 


print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbtrack[$nn]</h3></td>
<td HEIGHT=10><h3>$jbctime[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "hung") {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "hpss") {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
</TR>
END

 }
      $nn++;

}

 &endHtml();

######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B>List of jobs crashed for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>No failed jobs</h3></B></TD>
   </TR>
    </body>
END
}

#####################################

sub beginJbHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs crashed in<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events produced</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Avg.No.<br>tracks</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Node name</h3></B></TD>
</TR>
    </body>
END
}

#####################################

sub beginMuHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to transfer MuDst files on HPSS for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events produced</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Avg.No.<br>tracks</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Date</h3></B></TD>
</TR>
    </body>
END
}

#####################################


sub beginHgHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs 'hung' for<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
</TR>
    </body>
END
}


#####################################

sub beginHpHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to stage files from HPSS for <font color="blue">$qprod</font> production <br>and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>HPSS error</h3></B></TD>
</TR>
    </body>
END
}

##########################

sub beginStrHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Average CPU/evt  for diffrent streams in<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Stream name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Average CPU/evt<br> in sec</h3></B></TD>
</TR>
    </body>
END
}

##########################

sub beginSttrkHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Average no. of tracks  for diffrent streams in<font color="blue"> $qprod </font> production <br> and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Stream name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Average no.tracks</h3></B></TD>
</TR>
    </body>
END
}

######################

sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Fri July 8 2011 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}



######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}












