#! /usr/local/bin/perl -w
#
# L. Didenko
#
#
# SubmitToCarousel.pl - scripts automatically generate and  submit to DataCarousel list of N daq files 
# using query from FileCatalog and list of runnumbers to be processed in production.
# List of daq files is created if number of files in the designed directory less than MAXNUM. 
#
##############################################################################################################

use lib "/afs/rhic/star/packages/scripts";
use FileCatalog;
use DBI;
use Time::Local;

my $prodSer = $ARGV[0]; 
my $fileName = $ARGV[1];  

my $lockfile = "/star/u/starreco/runkisti/submission.lock";

$fC1 = FileCatalog->new();
$fC1->connect_as("Admin");


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="Embedding_job_stats";

my $JobStatusT = "jobs_prod_2013";

my $nfspath = "/star/data10/daq/2012/";
my $daqpat = $nfspath."*.daq";

my @daqlist = `ls $daqpat` ;

my $MAXNUM = 200;

print "There are  ", scalar(@daqlist),"  daq files in the ", $nfspath,"  directory", "\n";
 
if(scalar(@daqlist) <= $MAXNUM ) {

 if( -f $lockfile) {
     `/bin/rm  $lockfile` ;

#######

my $listName = "/star/u/starreco/".$fileName;
my @runSet = ();

  open (RUNLIST, $listName ) or die "cannot open $listName: $!\n";

  @runSet = <RUNLIST>;

  close(RUNLIST);

my $timestamp ;
my $lastid = 0;
my $prodrun = 0;
my $nfiles = 0;
my $nruns = 0;
my @fileset = ();
my @filelist = ();
my @trigname = ();
my @daqfile = ();
my $nlist = 0;
my @prt = ();
my $myrun;
my $todate;

 $lastid = scalar(@runSet) -1;

 print "There are ",$lastid," run numbers in the list", "\n";

 my $nextName = "/star/u/starreco/runkisti/".$lastid."_".$fileName;

#######

my ($sec,$min,$hour,$mday,$mon,$yr) = localtime();

 $mon++;
 if( $mon  < 10) { $mon  = '0'.$mon  };
 if( $mday < 10) { $mday = '0'.$mday };
 if( $hour < 10) { $hour = '0'.$hour };
 if( $min  < 10) { $min  = '0'.$min  };
 if( $sec  < 10) { $sec  = '0'.$sec  };
	 
 $year = $yr + 1900;
 $timestamp = $year."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;
 $todate = $year.$mon.$mday."-".$hour."-".$min;

 print "Today is  ",$timestamp, "\n";

my $fname = "dcfile"."_".$todate.".list";
my $DCfname = "/star/u/starreco/".$fname;

my $dclog = "dcarousel"."_".$todate.".log";
my $dcsubm = "/star/u/starreco/runkisti/".$dclog;

 print "Input/log file name for DataCarousel  ", $DCfname,"   ", $dcsubm,"\n";

#####
     
 if ($lastid > 0 ) {

 `/bin/mv $listName $nextName`;

 if (!open (NEWLIST, ">$listName" ))  {printf ("Unable to create file %s\n",$listName);}
	 
 if (!open (CFILE, ">$DCfname")) {printf ("Unable to create file %s\n",$DCfname);};

 &StDbConnect();

########

 foreach $prodrun (@runSet) {
  chop $prodrun ;

  if($prodrun != 10000000 ) {

 print  $prodrun, "\n";

  @fileset = ();

 $fC1->set_context("runnumber=$prodrun","filetype=online_daq");

 @fileset = $fC1->run_query("trgsetupname","path","filename");

 $fC1->clear_context();

########

 foreach my $line (@fileset) {

 @prt = ();
 @prt = split("::", $line);

 $trigname[$nlist] = $prt[0];
 $filelist[$nlist] = $prt[1]."/".$prt[2];
 $daqfile[$nlist] = $prt[2];

 print CFILE $filelist[$nlist], "\n";

 $sql= "insert into $JobStatusT set datasetName = '$trigname[$nlist]', prodTag = '$prodSer', inputFileName = '$daqfile[$nlist]', carouselSubTime = '$timestamp' ";

 $rv = $dbh->do($sql) || die $rv." ".$dbh->errstr;   

 $nlist++;

  }

  $nruns++;

#####

  if($nlist >= $MAXNUM ) {

  close (CFILE);
  goto GO_SUBMIT; 
      }

    }else{
	 if (!open (NEWLIST, ">$listName" )){
	     printf ("Unable to create file %s\n",$listName);
	 }else{
		 print  "No more run numbers in the list", "\n";
		 print NEWLIST "10000000\n";
	close (NEWLIST);
	 }
     }
   }
 }


GO_SUBMIT:

 &StDbDisconnect();

#    `hpss_user.pl -r $nfspath -f $DCfname >& $dcsubm`;

	 if (!open (NEWLIST, ">$listName" )){
	     printf ("Unable to create file %s\n",$listName);
	 } else {


	     if ($nruns <= $lastid ) {

		 for ( my $kk = $nruns; $kk <= $lastid; $kk++) {
		     $myrun = $runSet[$kk];
		     chop $myrun; 
#                 print "Before writing  ",$nruns,"   ",$kk,"   ",$lastid,"   ",$myrun, "\n"; 

		     print NEWLIST  "$myrun\n";  
		 }
                    close (NEWLIST);
	     } else {

		 print  "No more run numbers in the list", "\n";
		 print NEWLIST "10000000\n";
	     close (NEWLIST);
	     } 
	 }

#########

     if (!open (SUBFILE, ">$lockfile" ))  {printf ("Unable to create file %s\n",$lockfile);}
 
     print SUBFILE "Submission done", "\n";

     close (SUBFILE);

  } else {
     exit;
 }

 $fC1->destroy();

}

exit;


######################
sub StDbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}


######################
sub StDbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}
