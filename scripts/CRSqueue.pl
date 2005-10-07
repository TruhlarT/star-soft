#!/usr/local/bin/perl -w
#
# L. Didenko
###############################################################################

 use Mysql;

 require "/afs/rhic.bnl.gov/star/packages/scripts/dbCRSSetup.pl";

 my @statlist = ();

 @statlist = `crs_job -show_queues`;
 
 my $year;
 my $mon = 0;
 my $mday = 0;
 my $hour = 0;
 my $min = 0;
 my $sec = 0;
 my $timestamp ;

my @queueRun = ();
my @queueAvl  = ();
my @Rqueue = ();

my @prt = ();


 ($sec,$min,$hour,$mday,$mon,$yr) = localtime;


    $mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

 $year = $yr + 1900;

  $timestamp = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

 print $timestamp, "\n";

   &StcrsdbConnect();
 
my $nn = 0;

  foreach $line (@statlist) {
     chop $line ;
#   print  $line, "\n";
     next if( $line =~ /queue/);
    @prt = ();
    @prt = split (" ", $line);
    $queueAvl[$nn] = $prt[1]; 
    $queueRun[$nn] = $prt[2]; 
     if($queueAvl[$nn] >=1 ) {
	 $Rqueue[$nn] = ($queueRun[$nn]/$queueAvl[$nn])*100.0 ;
     } else {
     $Rqueue[$nn] = 0; 
  }
#     print $nn,"  All slots:  ", $queueAvl[$nn], "  Busy: ", $queueRun[$nn], "  Ratio ", $Rqueue[$nn], "\n";
    $nn++;

 }
   
      &fillTable();

   &StcrsdbDisconnect();

exit;


#################################################################################################

sub fillTable {

    $sql="insert into $crsQueueT set ";
    $sql.="queue0='$queueRun[0]',";
    $sql.="queue1='$queueRun[1]',";
    $sql.="queue2='$queueRun[2]',"; 
    $sql.="queue3='$queueRun[3]',";
    $sql.="queue4='$queueRun[4]',";
    $sql.="queue5='$queueRun[5]',";
    $sql.="Rqueue0='$Rqueue[0]',";
    $sql.="Rqueue1='$Rqueue[1]',";
    $sql.="Rqueue2='$Rqueue[2]',"; 
    $sql.="Rqueue3='$Rqueue[3]',";
    $sql.="Rqueue4='$Rqueue[4]',";
    $sql.="Rqueue5='$Rqueue[5]',";
    $sql.="sdate='$timestamp' "; 

    #  print "$sql\n" if $debugOn;
    # $rv = $dbh->do($sql) || die $dbh->errstr;
    $dbh->do($sql) || die $dbh->errstr;
}
