#! /opt/star/bin/perl -w
#
# $Id:
#
# L.Didenko
#
# updateFC.pico.events.pl - script to update number of events for picoDst files in FileCatalog when# produced from MuDst
# 
##############################################################################################################


use DBI;

use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;

my $SITE         = "BNL";
my $status       = (0==1);

my $fileC = new FileCatalog();

my ($user,$passwd) = $fileC->get_connection($SITE."::Admin");

if ( ! defined($user) ){  $user  = "";}
if ( ! defined($passwd) ){$passwd= "";}

if ( $user eq ""){
    print "Password : ";

    chomp($passwd = <STDIN>);
    $fileC->connect_as($SITE."::Admin","FC_admin",$passwd) || die "Connection failed for FC_admin\n";
} else {
    if ( $passwd eq "" ){
        print "Password for $user : ";
        chomp($passwd = <STDIN>);
    }
    $fileC->connect_as($SITE."::Admin",$user,$passwd)      || die "Connection failed for $user\n";
}

my $prodSr = $ARGV[0];
my $libtag = $ARGV[1];
my $trig   = $ARGV[2];


my $logPath = "/star/rcf/prodlog/".$prodSr.".".$libtag."/log/daq/";

my @fileList = ();
my @prt = ();

my $updatefile;
my $logFile;
my $fullname;
my $jfile;  
my $Nevent = 0;
my $Nevline ;

  $fileC->set_context(
    "production=$prodSr",
    "library=$libtag",
    "trgsetupname=$trig",
    "filetype=daq_reco_picoDst",
#    "filename~st_physics",
    "events=0",
    "storage=hpss");

$fileC->set_context("limit=0");

@fileList = $fileC->run_query("filename");
$fileC->clear_context();

for ( $ii = 0; $ii<scalar(@fileList); $ii++){
    $updatefile = $fileList[$ii];

#   print $updatefile, "\n";
    $jfile = $updatefile ;
    $jfile =~ s/picoDst.root//g;
    $logFile = $jfile ."log.gz";
    $fullname = $logPath.$logFile;

     if (-f $fullname)  {

   $Nevline = `zgrep 'NumberOfEvents' $fullname` ;

    @prt = ();
    @prt = split("=", $Nevline);

    $Nevent = $prt[1];

# print $fullname,  "  Nevents  = ",$Nevent,"\n"; 
 
  if($Nevent >= 1) {

########################
   $fileC->set_context("filename=$updatefile","production=$prodSr","library=$libtag","events=0"); # set conditions

   print "Update file  :", $updatefile,"  ", $Nevent, "\n";

   $fileC->update_record("events","$Nevent", 1);
   $fileC->clear_context();

      }   
     }

  }


$fileC->destroy();

exit ;



