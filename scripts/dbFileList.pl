#! /opt/star/bin/perl -w
#
#  $Id:
#
# dbFileList.pl - script to get file list from DB for given dataset
#
# L.Didenko
############################################################################

use Mysql;
use Class::Struct;
use File::Basename;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn=0;

my $prodSr = $ARGV[0];
my $SetD = $ARGV[1];

print $prodSr, " % ",$SetD, "\n";

struct JFileAttr => {
          fileN  => '$',
          EvtN   => '$', 
          pathN  => '$',  
		    };
 
 my @dstFiles;
 my $ndstFiles = 0;

 &StDbProdConnect();

# for ($ii=0; $ii< scalar(@SetD); $ii++)  { 

  $sql="SELECT path, fName, Nevents FROM $FileCatalogT WHERE fName LIKE '%root' AND jobID like '%$prodSr%' AND dataset = '$SetD' AND hpss = 'Y' AND dataStatus = 'OK' ";


     $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
           $cursor->execute;
 
   while(@fields = $cursor->fetchrow) {
     my $cols=$cursor->{NUM_OF_FIELDS};
        $fObjAdr = \(JFileAttr->new());
    for($i=0;$i<$cols;$i++) {
     my $fvalue=$fields[$i];
       my $fname=$cursor->{NAME}->[$i];
      print "$fname = $fvalue\n" if $debugOn;

         ($$fObjAdr)->pathN($fvalue)    if( $fname eq 'path');
         ($$fObjAdr)->fileN($fvalue)   if( $fname eq 'fName'); 
         ($$fObjAdr)->EvtN($fvalue)    if( $fname eq 'Nevents'); 
  }

   $dstFiles[$ndstFiles] = $fObjAdr;
   $ndstFiles++;
  }

    &StDbProdDisconnect();
my $fullname;
my $nEvts = 0;

######## declare variables needed to fill the database table

 my $mfName;
 my $mpath;
 my $mEvts;

my $Listfile = "GetFiles.txt";

open (STDOUT, ">$Listfile");

    foreach my $eachFile (@dstFiles) {
         $mfName = ($$eachFile)->fileN;
         $mpath  = ($$eachFile)->pathN;
         $mEvts  = ($$eachFile)->EvtN;
         $fullname = $mpath ."/".$mfName;
        if($mfName =~ /dst.root/) {
           $nEvts =  $nEvts + $mEvts;
}
#         if($nEvts <= 1000)  {
         
      print $fullname, "\n";
# }
}
   close (STDOUT);
  exit;


