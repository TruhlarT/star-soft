#!/usr/local/bin/perl -w
#
# $Id: scanFastDEV.pl
#
# $Log: L.Didenko
#
# scanFastDEV.pl - script to scan error messages in log files for Fast DEV release test. 
#
##########################################################################################################

my $TOPDIR = "/star/rcf/test/devfast/";
my @OUTDIR = ();
my $devflag = "complete";
my @files = ();
my $fullname;
my $output = ();
my $errMessage = "none";
my $logcount = 0;
my $email = "didenko\@bnl.gov";
my $message = "DEV test failed";
my $subject = "DEV fast test";

my $lockfile = "/afs/rhic.bnl.gov/star/packages/adev/.log/DEVrelease.lock";
my $relsfile = "/afs/rhic.bnl.gov/star/packages/adev/.log/afs.release";

my $dirtree =  $TOPDIR."*/*" ;

 @OUTDIR = `ls -d $dirtree` ;

 for ($i = 0; $i < scalar(@OUTDIR); $i++) {
 print $OUTDIR[$i], "\n"; 
 }

 foreach my $eachdir (@OUTDIR) {

  chop $eachdir;

  opendir(DIR, $eachdir) or die "can't open $eachdir\n";

     @files = readdir(DIR);

     foreach my $fname ( @files) {
      next if !$fname;
      next if $fname =~ /^\.\.?$/;
      next if $fname =~ /.root/;  
   
       if ($fname =~ /.log/)  {

      $logcount++;

#    print "File Name:",$fname, "\n";

     $fullname = $eachdir."/".$fname;

     @output = ();
     @output = `tail -1200 $fullname`;

     foreach my $line (@output) {

    if ($line =~ /Abort/)  {  
         $devflag = "failed";
         $errMessage = "Abort";
    }elsif ($line =~ /segmentation violation/) {
         $devflag = "failed"; 
         $errMessage = "Segmentation violation";  
    } elsif ($line =~ /segmentation fault/) {
         $devflag = "failed"; 
         $errMessage = "Segmentation fault";  
    } elsif ($line =~ /undefined symbol/) {
         $devflag = "failed";  
         $errMessage = "undefined symbol";
    }elsif ($line =~ /Assertion/ & $line =~ /failed/)  {
         $devflag = "failed";  
         $errMessage = "Assertion failed";
    }elsif ($line =~ /FATAL/ and $line =~ /floating point exception/) {
         $devflag = "failed"; 
         $errMessage = "FATAL, floating point exception", 
    }elsif ($line =~ /glibc detected/)  {
         $devflag = "failed"; 
         $errMessage = "glibc detected";

    }
         }
       }
     }

 }

   if($devflag eq "failed") {

   if (!open (LCFILE, ">$lockfile" ))  {printf ("Unable to create file %s\n",$lockfile);}

    print LCFILE "Test failed:  ", $errMessage, "\n";

    close (LCFILE);

    system("echo \"$message\" | mail -s \"$subject\" $email");


   }elsif($devflag eq "complete" and $logcount == 3 ) {

   if (!open (RFILE, ">$relsfile" ))  {printf ("Unable to create file %s\n",$relsfile);}  

    print RFILE "Ready to release on ".localtime()."\n";

    close (RFILE);

  }

exit;
