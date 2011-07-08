#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# RetriveChain.pl
#
# Retrive production chain.
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

my $mon =  $mon + 1;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

my $todate = ($year+1900)."-".$mon."-".$mday;

#$dbhost="fc2.star.bnl.gov:3386";
$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation"; 

struct JobAttr => {
      jbname    => '$',
      jbst      => '$',
      jbevt     => '$'
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
my $nn = 0;

  &StDbProdConnect();

   if( $qflag eq "jstat") {
 
  &beginJbHtml(); 

    $sql="SELECT jobfileName, jobStatus, NoEvents  FROM $JobStatusT  where jobfileName like '$qtrg%$qprod%' and prodSeries = '$qprod' and jobStatus <> 'Done' and jobStatus <> 'n/a' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

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

  
 }elsif($qflag eq "hpss") {

   &beginHpHtml();

     $sql="SELECT jobfileName, inputHpssStatus, NoEvents  FROM $JobStatusT  where jobfileName like '$qtrg%$qprod%' and prodSeries = '$qprod' and inputHpssStatus like 'hpss_error%' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

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

     $sql="SELECT jobfileName, jobStatus, NoEvents FROM $JobStatusT  where jobfileName like '$qtrg%$qprod%' and prodSeries = '$qprod' and jobStatus = 'hung' ";

      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
       $cursor->execute();

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


   }else{

   &beginHtml();
 }

&StDbProdDisconnect(); 

  
       foreach  $pjob (@jbstat) {

       $jbfName[$nn]  = ($$pjob)->jbname;      
       $jbStatus[$nn] = ($$pjob)->jbst;
       $jbEvent[$nn]  = ($$pjob)->jbevt;

    if( $qflag eq "jstat") {

 print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
<td HEIGHT=10><h3>$jbEvent[$nn]</h3></td>
</TR>
END


 }elsif($qflag eq "hung") {

print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
<td HEIGHT=10><h3>$jbfName[$nn]</h3></td>
<td HEIGHT=10><h3>$jbStatus[$nn]</h3></td>
</TR>
END

 }elsif($qflag eq "hpss") {

print <<END;

<TR ALIGN=CENTER HEIGHT=20 bgcolor=\"cornsilk\">
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
 <TD ALIGN=CENTER> <B><h3> No failed jobs found for <font color="blue">$qprod </font>production and <font color="blue"> $qtrg </font>dataset </B></h3></TD>
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
 <h2 ALIGN=CENTER> <B>List of jobs crashed due to code problem for<font color="blue"> $qprod </font> production and <font color="blue">$qtrg </font> dataset  </B></h2>
 <h3 ALIGN=CENTER> Generated on $todate</h3>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">
<TR>
<TD ALIGN=CENTER WIDTH=\"50%\" HEIGHT=60><B><h3>Jobfilename</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"30%\" HEIGHT=60><B><h3>Job status</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>No.events produced</h3></B></TD>
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
 <h2 ALIGN=CENTER> <B>List of jobs 'hung' for<font color="blue"> $qprod </font> production and <font color="blue">$qtrg </font> dataset  </B></h2>
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
 <h2 ALIGN=CENTER> <B>List of jobs failed to transfer files from HPSS for <font color="blue">$qprod</font> production and <font color="blue">$qtrg </font> dataset  </B></h2>
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












