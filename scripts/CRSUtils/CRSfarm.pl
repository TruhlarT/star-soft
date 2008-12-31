#!/usr/local/bin/perl -w
#
# L. Didenko
###############################################################################

 use Mysql;
 use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";


# Tables
$crsJobStatusT = "crsJobStatusY9";

 my @statlist = ();

 @statlist = `farmstat`;
 
 my $year;
 my $mon = 0;
 my $mday = 0;
 my $hour = 0;
 my $min = 0;
 my $sec = 0;
 my $thisday ;

my $Nsubm = 0;
my $Nsubmfail = 0;
my $Nstart = 0;
my $Nimportw = 0;
my $Nimporth = 0;
my $Nsleep = 0;
my $Nexe = 0;
my $Nexportw = 0;
my $Nexporth = 0;
my $Nexportu = 0;
my $Ndone = 0;
my $Nerror = 0;
my $Nfatal = 0;
my @prt = ();


 ($sec,$min,$hour,$mday,$mon,$yr) = localtime;


    $mon++;
if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };

  $year = $yr + 1900;

  $thisday = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

 print $thisday, "\n";

   &StcrsdbConnect();

  foreach $line (@statlist) {
     chop $line ;
#   print  $line, "\n";
    @prt = ();
    @prt = split (" ", $line);
     if ($prt[0] eq "SUBMITTED") {
	 $Nsubm =  $prt[1];
	} elsif ($prt[0] eq "STARTED") {
        $Nstart =  $prt[1]; 
	} elsif ($prt[0] eq "MAIN-IMPORT-WAITING") {         
        $Nimportw =  $prt[1]; 
	} elsif ($prt[0] eq "MAIN-IMPORT-HPSS") {       
        $Nimporth =  $prt[1];
	} elsif ($prt[0] eq "MAIN-SLEEP") {       
        $Nsleep =  $prt[1];
	} elsif ($prt[0] eq "MAIN-EXEC") { 
         $Nexec =  $prt[1];
	} elsif ($prt[0] eq "MAIN-EXPORT-UNIX") { 
         $Nexportu =  $prt[1];
	} elsif ($prt[0] eq "MAIN-EXPORT-WAITING") { 
         $Nexportw =  $prt[1];
	} elsif ($prt[0] eq "MAIN-EXPORT-HPSS") { 
         $Nexporth  =  $prt[1];
	} elsif ($prt[0] eq "DONE") { 
         $Ndone =  $prt[1];
	} elsif ($prt[0] eq "SUBMIT_FAILED") { 
         $Nsubmfail =  $prt[1];
	} elsif ($prt[0] eq "ERROR") {        
         $Nerror =  $prt[1];
 	} elsif ($prt[0] eq "FATAL") {        
         $Nfatal =  $prt[1];
     }

 }

      &fillTable();

#     print $Nsubm,"   ",$Nstart,"   ",$Nimportw,"   ",$Nimporth,"   ",$Nexec,"   ",$Nexportw,"   ",$Nexporth,"   ",$Ndone,"   ",$Nerror,"   ",$Nfatal, "\n";
   &StcrsdbDisconnect();

exit;


#################################################################################################

  sub fillTable {

 $sql="insert into $crsJobStatusT set ";
 $sql.="submitted='$Nsubm',";
 $sql.="submitFailed='$Nsubmfail',";
 $sql.="started='$Nstart',";
 $sql.="importWaiting='$Nimportw',"; 
 $sql.="importHPSS='$Nimporth',";
 $sql.="sleep='$Nsleep',";
 $sql.="executing='$Nexec',";
 $sql.="exportWaiting='$Nexportw',";
 $sql.="exportHPSS='$Nexporth',";
 $sql.="exportUNIX='$Nexportu',";
 $sql.="done='$Ndone',";
 $sql.="error='$Nerror',";
 $sql.="fatal='$Nfatal',";
 $sql.="sdate='$thisday' "; 
#   print "$sql\n" if $debugOn;
    # $rv = $dbh->do($sql) || die $dbh->errstr;
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
