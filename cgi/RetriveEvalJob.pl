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

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation"; 

struct JobAttr => {
      jbname    => '$',
      jbst      => '$',
      jbtrk     => '$',
      jbevt     => '$'
 };


my $query = new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $query->header };

my $qtrg = $query->param('trigs');
my $qprod = $query->param('prod');
#my $qyear = $query->param('pyear');
my $qflag = $query->param('pflag');
my $qtrack = $query->param('caltag');

my $JobStatusT = "EvalJobStatus"; 


my @archain = ();

my $nst = 0;
my @jbstat = ();
my @jbStatus = ();
my @jbfName = ();
my @jbEvent = ();
my @disklst = ();
my $diskname = ();
my $disksize = ();
my $nn = 0;
my $nnd = 0;
my $dnm = 0;
my @chainop  = ();

my $jobname = $qtrg."%".$qprod."_".$qtrack."%";


  &StDbProdConnect();

   if( $qflag eq "jstat") {
 
  &beginJbHtml(); 

    $sql="SELECT jobfileName, jobStatus, NoEvents, avg_no_tracks  FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and evaltag = ? and jobStatus <> 'Done' and jobStatus <> 'n/a' and jobStatus <> 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrack);

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

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }

  
 }elsif($qflag eq "hpss") {

   &beginHpHtml();

     $sql="SELECT jobfileName, inputHpssStatus, NoEvents  FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and evaltag = ? and inputHpssStatus like 'hpss_error%' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrack);

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

     $sql="SELECT jobfileName, jobStatus, NoEvents FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and evaltag = ? and jobStatus = 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrack);

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

     $sql="SELECT jobfileName, jobStatus, NoEvents, avg_no_tracks FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and evaltag = ? and jobStatus <> 'n/a' and jobStatus <> 'hung' and inputHpssStatus = 'OK' and outputStatus <> 'yes'  ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrack);

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

            }
            $jbstat[$nst] = $fObjAdr;
            $nst++;
         }

   }elsif($qflag eq "qchain") {


     $sql="SELECT distinct chainOpt FROM $JobStatusT  where trigsetName = ? and prodSeries = ? and evaltag = ? ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($qtrg,$qprod,$qtrack);

       while( $mpr = $cursor->fetchrow() ) {
          $chainop[$nst] = $mpr;
         $nst++; 
       }
     $cursor->finish();

   &beginChHtml();


 }elsif($qflag eq "ndisk") {

   &beginDsHtml();

     $sql="SELECT distinct diskName, sum(mudstsize) FROM $JobStatusT  where jobfileName like ? and prodSeries = ? and evaltag = ?  and outputStatus = 'yes' group by diskName ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute($jobname,$qprod,$qtrack);

        while(@fields = $cursor->fetchrow) {
            my $cols=$cursor->{NUM_OF_FIELDS};

            for($i=0;$i<$cols;$i++) {
                my $fvalue=$fields[$i];
                my $fname=$cursor->{NAME}->[$i];

             $disklst[$nnd] = $fvalue     if( $fname eq 'diskName');
             $diskname[$nnd] = "/star/".$disklst[$nnd];
             $disksize[$nnd] = $fvalue    if( $fname eq 'sum(mudstsize)');
             $disksize[$nnd] = int($disksize[$nnd]/1000000000 + 0.5)
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

&StDbProdDisconnect(); 


       foreach  $pjob (@jbstat) {

       $jbfName[$nn]  = ($$pjob)->jbname;      
       $jbStatus[$nn] = ($$pjob)->jbst;
       $jbEvent[$nn]  = ($$pjob)->jbevt;
       $jbtrack[$nn]  = ($$pjob)->jbtrk;

    if( $qflag eq "jstat" ) {

 print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbtrack[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "mudst") {

print <<END;

<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
<td HEIGHT=10><h3>$jbtrack[$nn]</h3></td>
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
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
 <TD ALIGN=CENTER> <B><h3> List of failed jobs found for <font color="blue">$qprod </font>production and <font color="blue"> $qtrg </font>dataset and <font color="blue">$qtrack</font> tracker</B></h3></TD>
</TR>
</TABLE>
    </body>
</html>
END
}

#####################################

sub beginJbHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs crashed for<font color="blue"> $qprod </font> production and <font color="blue">$qtrg </font> dataset  and <font color="blue">$qtrack</font> tracker</B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events produced</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Avg.No.tracks</h3></B></TD>
</TR>
   </head>
    </body>
END
}

#####################################

sub beginMuHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to create MuDst files on disk for<font color="blue"> $qprod </font> production and <font color="blue">$qtrg </font> dataset and <font color="blue">$qtrack</font> tracker </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>No.events produced</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Avg.No.tracks</h3></B></TD>
</TR>
   </head>
    </body>
END
}

#####################################


sub beginHgHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs 'hung' for<font color="blue"> $qprod </font> production and <font color="blue">$qtrg </font> dataset  and <font color="blue">$qtrack</font> tracker</B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
</TR>
   </head>
    </body>
END
}


#####################################

sub beginHpHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of jobs failed to stage files from HPSS for <font color="blue">$qprod</font> production and <font color="blue">$qtrg </font> dataset and <font color="blue">$qtrack</font> tracker </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>HPSS error</h3></B></TD>
</TR>
   </head>
    </body>
END
}

#####################################

sub beginChHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>Chain options used for <font color="blue">$qprod</font> production of <font color="blue">$qtrg </font> dataset and <font color="blue">$qtrack</font> tracker  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"90%\" HEIGHT=60><B><h3>$chainop[0]</h3></B></TD>
</TR>
   </head>
    </body>
END
}

#####################################

sub beginDsHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\">
 <h2 ALIGN=CENTER> <B>List of NFS disk names for <font color="blue">$qprod</font> production of <font color="blue">$qtrg </font> dataset and <font color="blue">$qtrack</font> tracker </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
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












