#! /opt/star/bin/perl -w
#
#  $Id:
#
#  $Log:   nodeStatus.pl - script for Web presentaion of node and Jobstatus
#          moving jobfiles for crashed jobs from archive to jobfiles directory 
#  L.Didenko
###############################################################################


use CGI;

&cgiSetup();

&beginHtml();

my @maifile;
my $mail_line;
my $status_line;
my $job_file = "none";
my $jbStat = "n/a";
my @parts;
my $nodeID = "n/a";
my $mynode; 
my @wrd;
my @jobFList;
my $numJbfile = 0;
my %nodeCrCount = ();
my %nodeStCount = ();
my %nodeAbCount = ();
my $outname;
my $outfile;


my @nodeList = (
                "rcrs6001.rcf.bnl.gov",
                "rcrs6002.rcf.bnl.gov",
                "rcrs6003.rcf.bnl.gov",
                "rcrs6004.rcf.bnl.gov",
                "rcrs6005.rcf.bnl.gov",
                "rcrs6006.rcf.bnl.gov",
                "rcrs6007.rcf.bnl.gov",            
                "rcrs6008.rcf.bnl.gov",
                "rcrs6009.rcf.bnl.gov",
                "rcrs6010.rcf.bnl.gov",
                "rcrs6011.rcf.bnl.gov",
                "rcrs6012.rcf.bnl.gov",
                "rcrs6013.rcf.bnl.gov",
                "rcrs6014.rcf.bnl.gov",
                "rcrs6015.rcf.bnl.gov",
                "rcrs6016.rcf.bnl.gov",
                "rcrs6017.rcf.bnl.gov",
                "rcrs6018.rcf.bnl.gov",
                "rcrs6019.rcf.bnl.gov",
                "rcrs6020.rcf.bnl.gov",
                "rcrs6021.rcf.bnl.gov",
                "rcrs6022.rcf.bnl.gov",
                "rcrs6023.rcf.bnl.gov",
                "rcrs6024.rcf.bnl.gov",
                "rcrs6025.rcf.bnl.gov",
                "rcrs6026.rcf.bnl.gov",
                "rcrs6027.rcf.bnl.gov",
                "rcrs6028.rcf.bnl.gov",
                "rcrs6029.rcf.bnl.gov",
                "rcrs6030.rcf.bnl.gov",
                "rcrs6031.rcf.bnl.gov",
                "rcrs6032.rcf.bnl.gov",
                "rcrs6033.rcf.bnl.gov"
);


my $eachNode;

 for ( $ll = 0; $ll<scalar(@nodeList); $ll++) {   
        
       $eachNode = $nodeList[$ll];
       $nodeCrCount{$eachNode} = 0;
       $nodeStCount{$eachNode} = 0;
       $nodeAbCount{$eachNode} = 0;
     }


$now = localtime;
($sec,$min,$hour,$mday,$mon) = localtime;

foreach my $int ( $mon,$mday ){
  $int < 10 and $int = '0'.$int;
   $thisday .= $int;
}

$outname = "mail" . "_" .$thisday . "_" . "out";
$outfile = "/star/u2e/starreco/" . $outname;
#print $outfile, "\n";

open (MAILFILE, $outfile ) or die "cannot open $outfile: $!\n";


 @mailfile = <MAILFILE>;

  foreach $mail_line (@mailfile) {
     chop $mail_line ;
     if ($mail_line =~ /JobInfo/ ) {
      @wrd = split ("%", $mail_line);
      $nodeID = $wrd[2];
      $jbStat = $wrd[1];
      $job_file = $wrd[3]; 

      if ($jbStat =~ /crashed/) {
       $nodeCrCount{$nodeID}++;
     }
      elsif ($jbStat =~ /aborted/) {
      $nodeAbCount{$nodeID}++; 
     }
     elsif ($jbStat =~ /staging failed/) {
      $nodeStCount{$nodeID}++; 
     }
     $jobFList[$numJbfile] = $job_file;
     $numJbfile++;
  } 
 }


for ($ll = 0; $ll < scalar(@nodeList); $ll++) {
      $mynode = $nodeList[$ll];
       
   &printRow();     

}

  &endHtml();

######################

sub beginHtml {

print <<END;
 <html>
  <head>
          <title>Crashed Jobs Summary  </title>
</head>
   <body BGCOLOR=\"#ccffff\"> 
        <h1 align=center>Crashed Jobs Summary</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH= 220 HEIGHT=80><B>Node ID </B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs crashed</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs aborted</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs with staging failed</B></TD>
</TR> 
   </head>
    <body>
END
}


################
sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
</tr>
END

}


#####################
sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Fri Juny 7  05:29:25 MET 2000 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}


