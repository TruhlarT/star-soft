#!/usr/bin/env perl
#
#  $Id:
#
#  $Log:
# splitJobsStatus.pl - script to check splitted jobs status in splitJobs2016 table
# and run merging macro to merge them if all splitted MuDst files are produced.
# 
#  Author: L.Didenko
############################################################################

use Class::Struct;
use File::Basename;
use Time::Local;
use DBI;

$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="operation";

$JobStatusT = "splitJobs2016";
$JobsInfoT  = "splitDaqInfo2016";

my $debugOn=0;

my $prodTg = $ARGV[0];
my $trig   = $ARGV[1];

my $dyear = "2016";

my $datpath = "/star/data17/reco/".$trig."/ReversedFullField/".$prodTg."/".$dyear."/*/*/seq/";

my @nmfile = ();
my @njcreat = ();
my @njdone = ();
my $nst = 0;
my $jobFname ;
my @numjobs = ();
my @jobSt = ();

my @mgfile = ();
my @mgseq = ();
my $nseq = 0;
my $basefile ;
my $nfile = 0;
my $mudstfile;
my $dirpatt ;
my @prt = ();
my $mpath ;
my $mgdir;
my $dstfile;
my $histfile;
my $tagsfile;

#####  connect to the DB

   &StDbProdConnect();


$sql="SELECT filename, njobcreate, njobdone from $JobsInfoT where prodTag = '$prodTg' and jobStatus <> 'Done' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute();

             while(@fields = $cursor->fetchrow) {

              $nmfile[$nst]    = $fields[0]; 
              $njcreat[$nst]   = $fields[1]; 
              $njdone[$nst]    = $fields[2]; 

             $nst++;
    }

   $cursor->finish();


  for ($ii = 0; $ii < $nst; $ii++)  {

      $jobSt[$ii] = 'n/a' ;

  $jobFname = $trig."_"."ReversedFullField"."_".$prodTg."_".$nmfile[$ii] ; 

 $sql="SELECT count(jobfileName)  FROM $JobStatusT where jobfileName like '$jobFname%' and jobStatus <> 'n/a' and NoEvents >= 1 and outputStatus = 'yes' ";
 
      $cursor =$dbh->prepare($sql)
          || die "Cannot prepare statement: $DBI::errstr\n";
      $cursor->execute();

      while( $mpr = $cursor->fetchrow() ) {
          $numjobs[$ii] = $mpr;
       }

    $cursor->finish();

#########
    if($numjobs[$ii] == $njcreat[$ii] ) {

    $jobSt[$ii] = 'Done' ;

    }elsif($numjobs[$ii] >= 1 and $numjobs[$ii] < $njcreat[$ii] ) {

    $jobSt[$ii] = 'not complete' ; 

    }else{
    $jobSt[$ii] = 'n/a' ;
   
     }

    if($jobSt[$ii] eq 'Done' or $jobSt[$ii] eq 'not complete' )  {

    $sql="update $JobsInfoT set njobdone = '$numjobs[$ii]', jobStatus = '$jobSt[$ii]' where filename = '$nmfile[$ii]' and prodTag = '$prodTg' ";

    $rv = $dbh->do($sql) || die $dbh->errstr;

      }

#########

 }

    $sql="SELECT filename, njobdone from $JobsInfoT where prodTag = '$prodTg' and jobStatus = 'Done' and mergeStatus = 'n/a' ";

            $cursor =$dbh->prepare($sql)
              || die "Cannot prepare statement: $DBI::errstr\n";
            $cursor->execute();

             while(@fields = $cursor->fetchrow) {

              $mgfile[$nfile]   = $fields[0];  
              $mgseq[$nfile]    = $fields[1]; 

      print "Input filename found   ",$mgfile[$nfile], "   %  ", $mgseq[$nfile],"\n"; 

             $nfile++;
    }

   $cursor->finish();
  

    for ($kk = 0; $kk < $nfile; $kk++)  {

    $basefile = $mgfile[$kk]."_1.MuDst.root"; 
    $nseq = $mgseq[$kk] - 1;
    $dirpatt = $datpath.$basefile;
    $mpath = `ls $dirpatt`;

    print "Path name  ", $mpath, "\n";

   if(  $mpath =~/$mgfile[$kk]/ ) {   
    @prt = ();
    @prt = split ("st_", $mpath);

    $mgdir = $prt[0];

#    print "Path splitted   ", $mgdir, "\n";

    chdir($mgdir) ;
    
    ` /star/u/starreco/bin/merger_sequences.pl $mgfile[$kk] $nseq `;

   $dstfile = $mgfile[$kk].".MuDst.root";
   $histfile = $mgfile[$kk].".hist.root";
   $tagsfile = $mgfile[$kk].".tags.root";

    if( -f  $dstfile) {

    `mv $dstfile ..` ;
    `mv $histfile ..` ;
    `mv $tagsfile ..` ;

    print "File found  ",$dstfile, "\n";

   $sql="update $JobsInfoT set mergeStatus = 'Done' where filename = '$mgfile[$kk]' and prodTag = '$prodTg' ";


    $rv = $dbh->do($sql) || die $dbh->errstr;

    }

   }else{
       next;
   }

}


#####  finished with data base

  &StDbProdDisconnect();

    exit;

#==============================================================================

######################
sub StDbProdConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub StDbProdDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

###################################################################################
