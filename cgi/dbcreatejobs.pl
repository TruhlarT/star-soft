#! /opt/star/bin/perl -w

use Class::Struct;
use CGI;

require "/afs/rhic/star/packages/SL99h/cgi/dbOperaSetup.pl";
#require "dbOperaRetrv.pl";

my $debugOn=0;


###Set directories to be created for jobfiles
my $DISK1        = "/star/rcf/disk00001";
my $TOPHPSS_SINK =  "/home/starsink/raw";
my $TOPHPSS_RECO =  "/home/starreco/reco";
my $JOB_LOG      =  $DISK1 . "/star/prod4/log";
my $JOB_DIR      =  "/star/u2e/starreco/prod4/requests/"; 
my @chain_opt    = ("tfs","tss","trs");

### connect to the DB
&StDbOperaConnect();


my @jobf_set;
my $jobf_no = 0;



struct JFileAttr => {

          setn   => '$', 
     file_name   => '$',
		    };


 $sql="SELECT SetName, GeantFile FROM $OperationT where Disk_dst_size = 0 AND HPSS_dst_size = 0 AND Jobfile = 'no' ";
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

        ($$fObjAdr)->setn($fvalue)     if( $fname eq 'SetName');
       ($$fObjAdr)->file_name($fvalue)  if( $fname eq 'GeantFile');
   }

  $jobf_set[$jobf_no] = $fObjAdr;
  $jobf_no++;


}

foreach my $jobnm (@jobf_set){
   my $sjob = ($$jobnm)->setn;
   my $flname = ($$jobnm)->file_name;
   my $jfile = $flname;
     $jfile =~ s/.fzd//g;
  
     creat_jobs($jfile, $sjob, $chain_opt[0]);
 }

# finished with data base
&StDbOperaDisconnect();

exit();


### create jobfiles to get default set of output files
 sub creat_jobs($$$) {

 my $gfile = $_[0];
 my $Jset  = $_[1]; 
 my $process = $_[2];
 my $job_set;

 $job_set = $Jset;
 $job_set =~ s/\//_/g;

# print $job_set, "\n";
 
 my $jb_new = $JOB_DIR . $process . "/new_jobs/" .  $job_set . "_" . $gfile;
 
       my $hpss_raw_dir  = $TOPHPSS_SINK . "/" . $Jset . "/gstardata";
       my $hpss_raw_file = $gfile . ".fzd";
       my $hpss_dst_dir  = $TOPHPSS_RECO . "/" . $Jset . "/" . $process . "_4";
       my $hpss_dst_file0 = $gfile . ".event.root";
       my $hpss_dst_file1 = $gfile . ".dst.root";
       my $hpss_dst_file2 = $gfile . ".hist.root";
       my $hpss_dst_file3 = $gfile . ".dst.xdf";
       my $executable     = "/afs/rhic/star/packages/SL99f/mgr/bfc.csh";
       my $executableargs    = $process . ",y1b,eval,fzin,xout";
       my $log_dir       = $JOB_LOG . "/" . $process;
       my $log_name      = $gfile . ".log";
       my $err_log       = $gfile . ".err";
       if (!open (TOM_SCRIPT,">$jb_new")) {printf ("Unable to create job submission script %s\n",$jb_new);}
       print TOM_SCRIPT "mergefactor=1\n";
       print TOM_SCRIPT "#input\n";
       print TOM_SCRIPT "      inputnumstreams=1\n";
       print TOM_SCRIPT "      inputstreamtype[0]=HPSS\n";
       print TOM_SCRIPT "      inputdir[0]=$hpss_raw_dir\n";
       print TOM_SCRIPT "      inputfile[0]=$hpss_raw_file\n";
       print TOM_SCRIPT "#output\n";
       print TOM_SCRIPT "      outputnumstreams=4\n";
       print TOM_SCRIPT "#output stream \n";
       print TOM_SCRIPT "      outputstreamtype[0]=HPSS\n";
       print TOM_SCRIPT "      outputdir[0]=$hpss_dst_dir\n";
       print TOM_SCRIPT "      outputfile[0]=$hpss_dst_file0\n";
       print TOM_SCRIPT "      outputstreamtype[1]= HPSS\n";
       print TOM_SCRIPT "      outputdir[1]=$hpss_dst_dir\n";
       print TOM_SCRIPT "      outputfile[1]=$hpss_dst_file1\n";
       print TOM_SCRIPT "      outputstreamtype[2]=HPSS\n";
       print TOM_SCRIPT "      outputdir[2]=$hpss_dst_dir\n";
       print TOM_SCRIPT "      outputfile[2]=$hpss_dst_file2\n";
       print TOM_SCRIPT "      outputstreamtype[3]=HPSS\n";
       print TOM_SCRIPT "      outputdir[3]=$hpss_dst_dir\n";
       print TOM_SCRIPT "      outputfile[3]=$hpss_dst_file3\n";
       print TOM_SCRIPT "#standard out -- Should be five outputs\n";
       print TOM_SCRIPT "      stdoutdir=$log_dir\n";
       print TOM_SCRIPT "      stdout=$log_name\n";
       print TOM_SCRIPT "#standard error -- Should be five\n";
       print TOM_SCRIPT "      stderrdir=$log_dir\n";
       print TOM_SCRIPT "      stderr=$err_log\n";
       print TOM_SCRIPT "      notify=starreco\@rcf.rhic.bnl.gov\n";
       print TOM_SCRIPT "#program to run\n";
       print TOM_SCRIPT "      executable=$executable\n";
       print TOM_SCRIPT "      executableargs=$executableargs\n";
       close(TOM_SCRIPT);

}


# finished with data base
&StDbDisconnect();
