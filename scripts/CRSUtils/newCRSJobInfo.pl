#!/usr/local/bin/perl -w
#
#  $Id: newCRSJobInfo.pl
#
#  L. Didenko
#
#  $Log: script to fillin table CRSJobsInfo with jobfiles properties and status 
#
###############################################################################

use DBI;
use File::Basename;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

# Tables
$crsJobStatusT = "CRSJobsInfo";

 my @jbstate  = ();
 my @prodtags = ();
 my @jbtrigs = ();
 my @jbfiles = ();
 my @jbstreams = ();
 my @prt = ();
 my @jbId = ();
 my @runId = ();
 my $njob = 0;
 my @outfile = ();
 my @wrd = ();
 my @spl = ();
 my @joblist  = ();

 
 my $year;
 my $mon = 0;
 my $mday = 0;
 my $hour = 0;
 my $min = 0;
 my $sec = 0;
 my $thisday ;

 ($sec,$min,$hour,$mday,$mon,$yr) = localtime;


    $mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

 $year = $yr + 1900;

 $thisday = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;


 print "-------------------------------------","\n";
 print $thisday, "\n";

   &StcrsdbConnect();

########### jobs in QUEUED

 @joblist = ();

 @joblist = `crs_job -stat | grep QUEUED` ;

    foreach my $jline (@joblist) {
     chop $jline ;
     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "QUEUED";  

     $njob++;
 }

########### jobs in STAGING

 @joblist = ();

 @joblist = `crs_job -stat | grep STAGING` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "STAGING";  

     $njob++;
 } 

########### jobs in SUBMITTED

 @joblist = ();

 @joblist = `crs_job -stat | grep SUBMITTED` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "SUBMITTED";  

     $njob++;
 } 

########### jobs in IMPORTING

 @joblist = ();

 @joblist = `crs_job -stat | grep IMPORTING` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "IMPORTING";  

     $njob++;
 } 

########### jobs in RUNNING

 @joblist = ();

 @joblist = `crs_job -stat | grep RUNNING` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "RUNNING";  

     $njob++;
 } 

########### jobs in ERROR

 @joblist = ();

 @joblist = `crs_job -stat | grep ERROR` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "ERROR";  

     $njob++;
 } 

########### jobs in HELD

 @joblist = ();

 @joblist = `crs_job -stat | grep HELD` ;

    foreach my $jline (@joblist) {
     chop $jline ;
#     print $jline, "\n";
     @wrd = ();
     @wrd = split (" ", $jline);
#     print $wrd[0],"   ",$wrd[1], "\n";

     $jbId[$njob] = $wrd[0];
     $jbId[$njob] = substr($wrd[0],0,-1) + 0;
     $jbstate[$njob] = "HELD";  

     $njob++;
 } 


for($ii = 0; $ii<$njob; $ii++) {

    @outfile = ();
    @outfile = `crs_job -long $jbId[$ii] | grep MuDst`;

     foreach my $fline (@outfile) {
     if ( $fline =~ /starreco/ ) {
       @prt = ();
       @prt = split("starreco", $fline) ;
       @wrd = ();
       @wrd = split("/", $prt[1]) ;
       $jbtrigs[$ii] = $wrd[2];
       $prodtags[$ii] = $wrd[4];
       $runId[$ii] = $wrd[7];
       chop $wrd[8]; 
       $jbfiles[$ii] = $wrd[8];
       $jbfiles[$ii] =~ s/MuDst.root'/daq/g; 
       @spl = (); 
       @spl = split("_", $wrd[8]) ; 
       $jbstreams[$ii] = $spl[1]; 

       
       print "Inserting into table values:  ", $jbstate[$ii]," % ",$jbId[$ii]," % ",$jbtrigs[$ii]," % ",$prodtags[$ii]," % ",$runId[$ii]," % ",$jbstreams[$ii]," % ",$jbfiles[$ii], "\n";


     &fillTable();

      }
     }
###########  insert table
}

for($ii = 0; $ii<$njob; $ii++) {

    @outfile = ();
    @outfile = `crs_job -long $jbId[$ii] | grep laser.root`;

     foreach my $fline (@outfile) {
     if ( $fline =~ /starreco/ ) {
       @prt = ();
       @prt = split("starreco", $fline) ;
       @wrd = ();
       @wrd = split("/", $prt[1]) ;
       $jbtrigs[$ii] = $wrd[2];
       $prodtags[$ii] = $wrd[4];
       $runId[$ii] = $wrd[7];
       chop $wrd[8]; 
       $jbfiles[$ii] = $wrd[8];
       $jbfiles[$ii] =~ s/laser.root'/daq/g; 
       @spl = (); 
       @spl = split("_", $wrd[8]) ; 
       $jbstreams[$ii] = $spl[1]; 

       
       print "Inserting into table values:  ", $jbstate[$ii]," % ",$jbId[$ii]," % ",$jbtrigs[$ii]," % ",$prodtags[$ii]," % ",$runId[$ii]," % ",$jbstreams[$ii]," % ",$jbfiles[$ii], "\n";


     &fillTable();

      }
     }
###########  insert table
}


 &StcrsdbDisconnect();

exit;


#################################################################################################

  sub fillTable {

 $sql="insert into $crsJobStatusT set ";
 $sql.="jobId='$jbId[$ii]',";
 $sql.="status='$jbstate[$ii]',";
 $sql.="prodtag='$prodtags[$ii]',";
 $sql.="trigset='$jbtrigs[$ii]',";
 $sql.="runnumber='$runId[$ii]',";
 $sql.="filename='$jbfiles[$ii]',";
 $sql.="stream='$jbstreams[$ii]',";
 $sql.="runDate='$thisday' "; 
   print "$sql\n" if $debugOn;
#   $rv = $dbh->do($sql) || die $dbh->errstr;
    $dbh->do($sql) || die $dbh->errstr;
  }

##################################################################################################
sub StcrsdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StcrsdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}
