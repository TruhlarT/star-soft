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
my $jbStat = "n/a";
my @parts;
my $nodeID = "n/a";
my $mynode; 
my @wrd;
my %nodeCrCount = ();
my %nodeStCount = ();
my %nodeAbCount = ();
my $outname;
my $outfile;

my @ndCrCount;
my @ndAbCount;
my @ndStCount; 

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
        
       $ndCrCount[$ll]  = 0;
       $ndAbCount[$ll]  = 0;
       $ndStCount[$ll]  = 0;
     };

my %nodeHash = (
                "rcrs6001.rcf.bnl.gov" => 0,
                "rcrs6002.rcf.bnl.gov" => 1, 
                "rcrs6003.rcf.bnl.gov" => 2,
                "rcrs6004.rcf.bnl.gov" => 3,
                "rcrs6005.rcf.bnl.gov" => 4,
                "rcrs6006.rcf.bnl.gov" => 5,
                "rcrs6007.rcf.bnl.gov" => 6,            
                "rcrs6008.rcf.bnl.gov" => 7,
                "rcrs6009.rcf.bnl.gov" => 8,
                "rcrs6010.rcf.bnl.gov" => 9,
                "rcrs6011.rcf.bnl.gov" => 10,
                "rcrs6012.rcf.bnl.gov" => 11,
                "rcrs6013.rcf.bnl.gov" => 12,
                "rcrs6014.rcf.bnl.gov" => 13,
                "rcrs6015.rcf.bnl.gov" => 14,
                "rcrs6016.rcf.bnl.gov" => 15,
                "rcrs6017.rcf.bnl.gov" => 16,
                "rcrs6018.rcf.bnl.gov" => 17,
                "rcrs6019.rcf.bnl.gov" => 18,
                "rcrs6020.rcf.bnl.gov" => 19,
                "rcrs6021.rcf.bnl.gov" => 20,
                "rcrs6022.rcf.bnl.gov" => 21,
                "rcrs6023.rcf.bnl.gov" => 22,
                "rcrs6024.rcf.bnl.gov" => 23,
                "rcrs6025.rcf.bnl.gov" => 24,
                "rcrs6026.rcf.bnl.gov" => 25,
                "rcrs6027.rcf.bnl.gov" => 26,
                "rcrs6028.rcf.bnl.gov" => 27,
                "rcrs6029.rcf.bnl.gov" => 28,
                "rcrs6030.rcf.bnl.gov" => 29,
                "rcrs6031.rcf.bnl.gov" => 30,
                "rcrs6032.rcf.bnl.gov" => 31,
                "rcrs6033.rcf.bnl.gov" => 32
 );               


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
      chop $nodeID;
      chop $nodeID;
      $nodeID =~ s/^\ *//g;
      $ii = $nodeHash{$nodeID};

      if ($jbStat =~ /crashed/) {
        $ndCrCount[$ii]++;
     }
      elsif ($jbStat =~ /aborted/) {
        $ndAbCount[$ii]++;  
     }
     elsif ($jbStat =~ /staging failed/) {
         $ndStCount[$ii]++;
     }
  } 
 }


for ($ll = 0; $ll < scalar(@nodeList); $ll++) {
      $mynode = $nodeList[$ll];
      $nodeCrCount{$mynode} = $ndCrCount[$ll];
      $nodeAbCount{$mynode} = $ndAbCount[$ll];
      $nodeStCount{$mynode} = $ndStCount[$ll]; 
      if( $nodeCrCount{$mynode} != 0) {
   &printCrRow();
  }       
     elsif ($nodeAbCount{$mynode} != 0) {
   &printAbRow();
  }
     elsif ($nodeStCount{$mynode} != 0) {
   &printStRow();
  }else {       
 &printRow();
}
}
 close (MAILFILE);

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

#######################

 sub printAbRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
</TR>
END

}

#######################

 sub printCrRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
</TR>
END

}

#######################

 sub printStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
</TR>
END

}

#######################

 sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
</TR>
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


