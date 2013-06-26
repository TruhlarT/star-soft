#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveEmbJob.pl
#
# Retrive embedding production jobs status
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use DBI;
use CGI qw(:standard);
#use Mysql;
use Class::Struct;


($sec,$min,$hour,$mday,$mon,$year) = localtime();

 $mon++;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

$dbhost="duvall.star.bnl.gov:3306";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";


struct JobAttr => {
      jbid     => '$',
      jbind    => '$',
      jbfst    => '$',
      jbname   => '$',
      jbst     => '$',
      jbevt    => '$',
      jbtime   => '$'
 };


my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qtrg  = $query->param('rtrig');
my $qpart = $query->param('rpart');
my $qreq  = $query->param('rreq');
my $qflag = $query->param('pflag');


my $JobStatusT = "jobs_embed_2012";
my $RequestSumT = "request_embed_2012";

my $nst = 0;
my @jbstat = ();
my @jbStatus = ();
my @jbfName = ();
my @jbEvent = ();
my @jbjobid = ();
my @jbprocid = ();
my @jbfset = ();
my @jbctime = ();

my @disklst = ();
my @diskname = ();
my @disksize = ();
my @chnopts  = ();
my $chn;
my $nch = 0;

my $nn = 0;
my $nnd = 0;
my $dnm = 0;


  &StDbEmbConnect();


   if($qflag eq "jstat") {
 
  &beginJbHtml(); 

     $sql="SELECT jobID, jobIndex, fSet, inputFile, totalEvents, recoStatus, date_format(endTime, '%Y-%m-%d') as CDATE  FROM $JobStatusT  where  triggerSetName = ? and requestID = ? and particle = ?  and jobStatus = 'Done' and recoStatus <> 'Done' and status = 1 ";


      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qtrg,$qreq,$qpart);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;


                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'inputFile');
                ($$fObjAdr)->jbid($fvalue)     if( $fname eq 'jobID');
                ($$fObjAdr)->jbind($fvalue)    if( $fname eq 'jobIndex');
                ($$fObjAdr)->jbfst($fvalue)    if( $fname eq 'fSet');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'totalEvents');
                ($$fObjAdr)->jbst($fvalue)     if( $fname eq 'recoStatus');               
                ($$fObjAdr)->jbtime($fvalue)   if( $fname eq 'CDATE');         

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
      }


 }elsif($qflag eq "mudst") {

   &beginMuHtml();

     $sql="SELECT jobID, jobIndex, fSet, inputFile, MuDstEvents, date_format(endTime, '%Y-%m-%d') as PDATE  FROM $JobStatusT  where  triggerSetName = ? and requestID = ? and particle = ?  and jobStatus = 'Done' and outputNFS <> 'Done' and status = 1 ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qtrg,$qreq,$qpart);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};
            $fObjAdr = \(JobAttr->new());

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];
                # print "$fname = $fvalue\n" ;

                ($$fObjAdr)->jbname($fvalue)   if( $fname eq 'inputFile');
                ($$fObjAdr)->jbid($fvalue)     if( $fname eq 'jobID');
                ($$fObjAdr)->jbind($fvalue)    if( $fname eq 'jobIndex');
                ($$fObjAdr)->jbfst($fvalue)    if( $fname eq 'fSet');
                ($$fObjAdr)->jbevt($fvalue)    if( $fname eq 'MuDstEvents');               
                ($$fObjAdr)->jbtime($fvalue)   if( $fname eq 'PDATE');  

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
       }

  }elsif($qflag eq "chnopt") {

   &beginChHtml();

     $sql="SELECT distinct chainOptions FROM $RequestSumT  where requestID = ?  and type = 'embed'";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qreq);

       while( $chn = $cursor->fetchrow() ) {
          $chnopts[$nch] = $chn;

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$chnopts[$nch]</h3></td>
</TR>
END
          $nch++;
       }
    $cursor->finish();

 }elsif($qflag eq "sdisk") {

 &beginDsHtml();

     $sql="SELECT distinct diskName, sum(outputSize) FROM $JobStatusT  where triggerSetName = ? and requestID = ? and particle = ?  and outputNFS
= 'Done' group by diskName ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qtrg,$qreq,$qpart);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];

             $disklst[$nnd] = $fvalue     if( $fname eq 'diskName');
             $diskname[$nnd] = $disklst[$nnd];
             $disksize[$nnd] = $fvalue    if( $fname eq 'sum(outputSize)');
                $disksize[$nnd] = int($disksize[$nnd]/1000 + 0.5);

            }

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$diskname[$nnd]</h3></td>
<td HEIGHT=10><h3>$disksize[$nnd]</h3></td>
</TR>
END
            $nnd++;
        }

   }else{

  &beginHtml();

   }



 &StDbEmbDisconnect(); 

       foreach  $pjob (@jbstat) {

       $jbfName[$nn]  = ($$pjob)->jbname; 
       $jbjobid[$nn]  = ($$pjob)->jbid;
       $jbprocid[$nn] = ($$pjob)->jbind;
       $jbfset[$nn]   = ($$pjob)->jbfst; 
       $jbStatus[$nn] = ($$pjob)->jbst;
       $jbEvent[$nn]  = ($$pjob)->jbevt;
       $jbctime[$nn]  = ($$pjob)->jbtime;

  if($qflag eq "jstat" ) {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbjobid[$nn]</h3></td>
<td HEIGHT=10><h3>$jbprocid[$nn]</h3></td>
<td HEIGHT=10><h3>$jbfset[$nn]</h3></td>
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbctime[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "mudst") {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbjobid[$nn]</h3></td>
<td HEIGHT=10><h3>$jbprocid[$nn]</h3></td>
<td HEIGHT=10><h3>$jbfset[$nn]</h3></td>
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbctime[$nn]</h3></td>
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
<h2 ALIGN=CENTER> <B>No data for <font color="blue">$qtrg </font>embedding production of <font color="blue"> $qpart </font> particle<br> with  requestID = <font color="blue">$qreq </font> </B></h2>
    </body>
END
}

#####################################

sub beginJbHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs crashed in <font color="blue">$qtrg </font>embedding production <br>
 for <font color="blue"> $qpart </font> particle  with requestID = <font color="blue">$qreq </font> </B></h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>JobID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>Job Index</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"5%\" HEIGHT=60><B><h3>fSet</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>File name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Reco status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events processed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
</TR>
    </body>
END
}

#####################################

sub beginMuHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
<h2 ALIGN=CENTER> <B>List of jobs failed to create output files on NFS in <font color="blue">$qtrg </font>embedding production <br> for <font color="blue"> $qpart </font> particle with requestID = <font color="blue">$qreq </font> </B></h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>JobID</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Job Index</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>fSet</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>File name</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events processed</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Finish time</h3></B></TD>
</TR>
    </body>
END
}

#####################################


sub beginChHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Chain options for embedding production with requestID = <font color="blue"> $qreq </font> </B></h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"80%\" HEIGHT=60><B><h3>Chain options</h3></B></TD>
</TR>
    </body>
END
}


#####################################

sub beginDsHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of NFS disk names for <font color="blue">$qtrg</font> embedding production <br> for <font color="blue">$qpart </font> particle with  requestID = <font color="blue">$qreq </font> </B></h2>
 <h3 ALIGN=CENTER> Created on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Disk names</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Size of output files in GB</h3></B></TD>
</TR>
   </head>
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
<!-- Created: Wed November 28 2012 -->
<!-- hhmts start -->
<!-- hhmts end -->
  </body>
</html>
END

}



######################
sub StDbEmbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbEmbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

#####################################

sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}












