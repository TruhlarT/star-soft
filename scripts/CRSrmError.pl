#! /usr/local/bin/perl -w
#
# L. Didenko
###############################################################################

 my $prodSer = $ARGV[0];  
my $jobdir = "/home/starreco/newcrs/" . $prodSer ."/requests/daq/jobfiles";
my $archdir = "/home/starreco/newcrs/" . $prodSer ."/requests/daq/archive";

 my @statlist = ();
 my @joblist = ();
 my $timestamp ;
 my $fullname;


 @statlist = `farmstat`;

my $Ndone = 0;
my $Nerror = 0;

my $jobname;
my $crsjobname;
my @prt = ();
my @wrd = ();
my $year = ();

  ($sec,$min,$hour,$mday,$mon,$yr) = localtime;

  
    $mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $min = '0'.$sec };

$year = $yr + 1900 ;

  $timestamp = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

 print $timestamp, "\n";

  foreach $line (@statlist) {
     chop $line ;
#   print  $line, "\n";
    @prt = ();
    @prt = split (" ", $line);
     if ($prt[0] eq "ERROR") {
         $Nerror =  $prt[1]; 
  }
 }

    if($Nerror >= 1 ) {

    print $Nerror,"  ", "jobs failed, below is a list:", "\n";

    @joblist = `crs_job -stat_show_problem | grep ERROR` ;

    foreach $erline (@joblist) {
     chop $erline ;
#     print $erline, "\n";       

      @wrd = ();
      @prt = ();
      @wrd = split ("-", $erline);
      $jobname = $wrd[0];
      @prt = split (" ", $erline);
      $crsjobname = $prt[0];

      print $jobname,"   ", $prt[1], "\n";

      next if ($erline =~ /hpss_export_failed/ );

     $fullname = $archdir ."/". $jobname;

    `mv $fullname $jobdir \n`;
    `crs_job -kill $crsjobname`;
        print "Job resubmitted: ", $jobname, "\n";
  }

 }else {

     print "No failed jobs", "\n";
 }

exit;

