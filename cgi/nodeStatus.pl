#! /usr/local/bin/perl -w
#
#  $Id:
#
#  $Log:   nodeStatus.pl - monitoring of CRS jobs
#           
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
my %nodeDnCount = ();
my %nodeFNFCount = ();
my $outname;
my $outfile;

my @ndCrCount;
my @ndAbCount;
my @ndStCount; 
my @ndDnCount;
my @ndFNFCount;
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
                "rcrs6033.rcf.bnl.gov",
                "rcrs6034.rcf.bnl.gov",
                "rcrs6035.rcf.bnl.gov",
                "rcrs6036.rcf.bnl.gov",
                "rcrs6037.rcf.bnl.gov",
                "rcrs6038.rcf.bnl.gov",
                "rcrs6039.rcf.bnl.gov",
                "rcrs6040.rcf.bnl.gov",
                "rcrs6041.rcf.bnl.gov",
                "rcrs6042.rcf.bnl.gov",
                "rcrs6043.rcf.bnl.gov",
                "rcrs6044.rcf.bnl.gov",            
                "rcrs6045.rcf.bnl.gov",
                "rcrs6046.rcf.bnl.gov",
                "rcrs6047.rcf.bnl.gov",
                "rcrs6048.rcf.bnl.gov",
                "rcrs6049.rcf.bnl.gov",
                "rcrs6050.rcf.bnl.gov",
                "rcrs6051.rcf.bnl.gov",
                "rcrs6052.rcf.bnl.gov",
                "rcrs6053.rcf.bnl.gov",
                "rcrs6054.rcf.bnl.gov",
                "rcrs6055.rcf.bnl.gov",
                "rcrs6056.rcf.bnl.gov",
                "rcrs6057.rcf.bnl.gov",
                "rcrs6058.rcf.bnl.gov",
                "rcrs6059.rcf.bnl.gov",
                "rcrs6060.rcf.bnl.gov",
                "rcrs6061.rcf.bnl.gov",
                "rcrs6062.rcf.bnl.gov",
                "rcrs6063.rcf.bnl.gov",
                "rcrs6064.rcf.bnl.gov",
                "rcrs6065.rcf.bnl.gov",
                "rcrs6066.rcf.bnl.gov",
                "rcrs6067.rcf.bnl.gov",
                "rcrs6068.rcf.bnl.gov",
                "rcrs6069.rcf.bnl.gov",
                "rcrs6070.rcf.bnl.gov",
                "rcrs6071.rcf.bnl.gov",
                "rcrs6072.rcf.bnl.gov",
                "rcrs6073.rcf.bnl.gov",
                "rcrs6074.rcf.bnl.gov",
                "rcrs6075.rcf.bnl.gov",
                "rcrs6076.rcf.bnl.gov",
                "rcrs6077.rcf.bnl.gov",
                "rcrs6078.rcf.bnl.gov",
                "rcrs6079.rcf.bnl.gov",
                "rcrs6080.rcf.bnl.gov",
                "rcrs6081.rcf.bnl.gov",            
                "rcrs6082.rcf.bnl.gov",
                "rcrs6083.rcf.bnl.gov",
                "rcrs6084.rcf.bnl.gov",
                "rcrs6085.rcf.bnl.gov",
                "rcrs6086.rcf.bnl.gov",
                "rcrs6087.rcf.bnl.gov",
                "rcrs6088.rcf.bnl.gov",
                "rcrs6089.rcf.bnl.gov",
                "rcrs6090.rcf.bnl.gov",
                "rcrs6091.rcf.bnl.gov",
                "rcrs6092.rcf.bnl.gov",
                "rcrs6093.rcf.bnl.gov",
                "rcrs6094.rcf.bnl.gov",
                "rcrs6094.rcf.bnl.gov",
                "rcrs6095.rcf.bnl.gov",
                "rcrs6096.rcf.bnl.gov",
                "rcrs6097.rcf.bnl.gov",
                "rcrs6098.rcf.bnl.gov",
                "rcrs6099.rcf.bnl.gov",
                "rcrs6100.rcf.bnl.gov",
                "rcrs6101.rcf.bnl.gov",
                "rcrs6102.rcf.bnl.gov",
                "rcrs6103.rcf.bnl.gov",
                "rcrs6104.rcf.bnl.gov",
                "rcrs6105.rcf.bnl.gov",
                "rcrs6106.rcf.bnl.gov",
                "rcrs6107.rcf.bnl.gov",
                "rcrs6108.rcf.bnl.gov",
                "rcrs6109.rcf.bnl.gov",
                "rcrs6110.rcf.bnl.gov",
                "rcrs6111.rcf.bnl.gov",
                "rcrs6112.rcf.bnl.gov",
                "rcrs6113.rcf.bnl.gov",
                "rcrs6114.rcf.bnl.gov",
                "rcrs6115.rcf.bnl.gov",
                "rcrs6116.rcf.bnl.gov",
                "rcrs6117.rcf.bnl.gov",
                "rcrs6118.rcf.bnl.gov",
                "rcrs6119.rcf.bnl.gov",
                "rcrs6120.rcf.bnl.gov",
                "rcrs6121.rcf.bnl.gov",
                "rcrs6122.rcf.bnl.gov",
                "rcrs6123.rcf.bnl.gov",
                "rcrs6124.rcf.bnl.gov",
                "n/a"
);


my $eachNode;

 for ( $ll = 0; $ll<scalar(@nodeList); $ll++) {   
        
       $ndCrCount[$ll]  = 0;
       $ndAbCount[$ll]  = 0;
       $ndStCount[$ll]  = 0;
       $ndDnCount[$ll]  = 0;
       $ndFNFCount[$ll] = 0;
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
                "rcrs6033.rcf.bnl.gov" => 32,
                "rcrs6034.rcf.bnl.gov" => 33,
                "rcrs6035.rcf.bnl.gov" => 34,
                "rcrs6036.rcf.bnl.gov" => 35,
                "rcrs6037.rcf.bnl.gov" => 36, 
                "rcrs6038.rcf.bnl.gov" => 37,
                "rcrs6039.rcf.bnl.gov" => 38,
                "rcrs6040.rcf.bnl.gov" => 39,
                "rcrs6041.rcf.bnl.gov" => 40,
                "rcrs6042.rcf.bnl.gov" => 41,
                "rcrs6043.rcf.bnl.gov" => 42,
                "rcrs6044.rcf.bnl.gov" => 43,            
                "rcrs6045.rcf.bnl.gov" => 44,
                "rcrs6046.rcf.bnl.gov" => 45,
                "rcrs6047.rcf.bnl.gov" => 46,
                "rcrs6048.rcf.bnl.gov" => 47,
                "rcrs6049.rcf.bnl.gov" => 48,
                "rcrs6050.rcf.bnl.gov" => 49,
                "rcrs6051.rcf.bnl.gov" => 50,
                "rcrs6052.rcf.bnl.gov" => 51,
                "rcrs6053.rcf.bnl.gov" => 52,
                "rcrs6054.rcf.bnl.gov" => 53,
                "rcrs6055.rcf.bnl.gov" => 54,
                "rcrs6056.rcf.bnl.gov" => 55,
                "rcrs6057.rcf.bnl.gov" => 56,
                "rcrs6058.rcf.bnl.gov" => 57,
                "rcrs6059.rcf.bnl.gov" => 58,
                "rcrs6060.rcf.bnl.gov" => 59,
                "rcrs6061.rcf.bnl.gov" => 60,
                "rcrs6062.rcf.bnl.gov" => 61,
                "rcrs6063.rcf.bnl.gov" => 62,
                "rcrs6064.rcf.bnl.gov" => 63,
                "rcrs6065.rcf.bnl.gov" => 64,
                "rcrs6066.rcf.bnl.gov" => 65,
                "rcrs6067.rcf.bnl.gov" => 66,
                "rcrs6068.rcf.bnl.gov" => 67,
                "rcrs6069.rcf.bnl.gov" => 68,
                "rcrs6070.rcf.bnl.gov" => 69,
                "rcrs6071.rcf.bnl.gov" => 70,
                "rcrs6072.rcf.bnl.gov" => 71,
                "rcrs6073.rcf.bnl.gov" => 72,
                "rcrs6074.rcf.bnl.gov" => 73,
                "rcrs6075.rcf.bnl.gov" => 74,
                "rcrs6076.rcf.bnl.gov" => 75,
                "rcrs6077.rcf.bnl.gov" => 76,
                "rcrs6078.rcf.bnl.gov" => 77,
                "rcrs6079.rcf.bnl.gov" => 78,
                "rcrs6080.rcf.bnl.gov" => 79,
                "rcrs6081.rcf.bnl.gov" => 80,            
                "rcrs6082.rcf.bnl.gov" => 81,
                "rcrs6083.rcf.bnl.gov" => 82,
                "rcrs6084.rcf.bnl.gov" => 83,
                "rcrs6085.rcf.bnl.gov" => 84,
                "rcrs6086.rcf.bnl.gov" => 85,
                "rcrs6087.rcf.bnl.gov" => 86,
                "rcrs6088.rcf.bnl.gov" => 87,
                "rcrs6089.rcf.bnl.gov" => 88,
                "rcrs6090.rcf.bnl.gov" => 89,
                "rcrs6091.rcf.bnl.gov" => 90,
                "rcrs6092.rcf.bnl.gov" => 91,
                "rcrs6093.rcf.bnl.gov" => 92,
                "rcrs6094.rcf.bnl.gov" => 93,
                "rcrs6095.rcf.bnl.gov" => 94,
                "rcrs6096.rcf.bnl.gov" => 95,
                "rcrs6097.rcf.bnl.gov" => 96,
                "rcrs6098.rcf.bnl.gov" => 97,
                "rcrs6099.rcf.bnl.gov" => 98,
                "rcrs6100.rcf.bnl.gov" => 99,
                "rcrs6101.rcf.bnl.gov" => 100,
                "rcrs6102.rcf.bnl.gov" => 101,
                "rcrs6103.rcf.bnl.gov" => 102,
                "rcrs6104.rcf.bnl.gov" => 103,
                "rcrs6105.rcf.bnl.gov" => 104,
                "rcrs6106.rcf.bnl.gov" => 105,
                "rcrs6107.rcf.bnl.gov" => 106,
                "rcrs6108.rcf.bnl.gov" => 107,
                "rcrs6109.rcf.bnl.gov" => 108,
                "rcrs6110.rcf.bnl.gov" => 109,
                "rcrs6111.rcf.bnl.gov" => 110,
                "rcrs6112.rcf.bnl.gov" => 111,
                "rcrs6113.rcf.bnl.gov" => 112,
                "rcrs6114.rcf.bnl.gov" => 113,
                "rcrs6115.rcf.bnl.gov" => 114,
                "rcrs6116.rcf.bnl.gov" => 115, 
                "rcrs6117.rcf.bnl.gov" => 116,
                "rcrs6118.rcf.bnl.gov" => 117,
                "rcrs6119.rcf.bnl.gov" => 118,
                "rcrs6120.rcf.bnl.gov" => 119,
                "rcrs6121.rcf.bnl.gov" => 120,
                "rcrs6122.rcf.bnl.gov" => 121,
                "rcrs6123.rcf.bnl.gov" => 122,
                "rcrs6124.rcf.bnl.gov" => 123,
                "n/a"                  => 124 
);               


$now = localtime;
($sec,$min,$hour,$mday,$mon) = localtime;

foreach my $int ( $mon,$mday ){
  $int < 10 and $int = '0'.$int;
   $thisday .= $int;
}

$outname = "mail" . "_" .$thisday . "_" . "out";
$outfile = "/star/u/starreco/" . $outname;
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
#      chop $nodeID;
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
     elsif ($jbStat =~ /file not found/) {
         $ndStCount[$ii]++;
     }
     elsif ($jbStat =~ /done/) {
         $ndDnCount[$ii]++;
       }
   } 
 }

my $TotAbCount = 0;
my $TotDnCount = 0;
my $TotCrCount = 0;
my $TotStCount = 0;
my $TotFNFCount = 0;

for ($ll = 0; $ll < scalar(@nodeList); $ll++) {
      $mynode = $nodeList[$ll];
      $nodeCrCount{$mynode} = $ndCrCount[$ll];
      $nodeAbCount{$mynode} = $ndAbCount[$ll];
      $nodeStCount{$mynode} = $ndStCount[$ll]; 
      $nodeDnCount{$mynode} = $ndDnCount[$ll];       
      $nodeFNFCount{$mynode} = $ndFNFCount[$ll];
      
      $TotAbCount += $ndAbCount[$ll];
      $TotDnCount += $ndDnCount[$ll];
      $TotCrCount += $ndCrCount[$ll];
      $TotStCount += $ndStCount[$ll];
      $TotFNFCount += $ndFNFCount[$ll];

     if(($nodeDnCount{$mynode} != 0) && ($nodeCrCount{$mynode} == 0) && ($nodeAbCount{$mynode}== 0) && ($nodeStCount{$mynode}== 0) ) {
   &printDnRow();
  }      
     elsif($nodeDnCount{$mynode} != 0 && $nodeCrCount{$mynode} != 0 && $nodeAbCount{$mynode} == 0 && $nodeStCount{$mynode} == 0 ) {
   &printCrDnRow();
  }       
     elsif ($nodeDnCount{$mynode} != 0 && $nodeAbCount{$mynode} != 0 && $nodeCrCount{$mynode} == 0 && $nodeStCount{$mynode} == 0 ) {
   &printAbDnRow();
  }
     elsif ($nodeDnCount{$mynode} != 0 && $nodeStCount{$mynode} != 0 && $nodeAbCount{$mynode} == 0 && $nodeCrCount{$mynode} == 0 ) {
   &printStDnRow();
 }
#
     elsif($nodeDnCount{$mynode} == 0 && $nodeCrCount{$mynode} != 0 && $nodeAbCount{$mynode}== 0 && $nodeStCount{$mynode} == 0 ) {
   &printCrRow();
  }       
     elsif ($nodeDnCount{$mynode} == 0 && $nodeAbCount{$mynode} != 0 && $nodeCrCount{$mynode} == 0 && $nodeStCount{$mynode} == 0) {
   &printAbRow();
  }
     elsif ($nodeDnCount{$mynode} == 0 && $nodeStCount{$mynode} != 0 && $nodeAbCount{$mynode} == 0 && $nodeCrCount{$mynode} == 0) {
   &printStRow();
}
#
     elsif($nodeDnCount{$mynode} == 0 && $nodeCrCount{$mynode} != 0 && $nodeAbCount{$mynode} != 0 && $nodeStCount{$mynode} == 0 ) {
   &printAbCrRow();
  }       
     elsif ($nodeDnCount{$mynode} == 0 && $nodeAbCount{$mynode} != 0 && $nodeCrCount{$mynode} == 0 && $nodeStCount{$mynode} != 0) {
   &printAbStRow();
  }
     elsif ($nodeDnCount{$mynode} == 0 && $nodeStCount{$mynode} != 0 && $nodeAbCount{$mynode} == 0 && $nodeCrCount{$mynode} != 0) {
   &printCrStRow();
}
#
     elsif($nodeDnCount{$mynode} != 0 && $nodeCrCount{$mynode} != 0 && $nodeAbCount{$mynode} != 0 && $nodeStCount{$mynode} == 0 ) {
   &printAbCrDnRow();
  }       
     elsif ($nodeDnCount{$mynode} != 0 && $nodeAbCount{$mynode} != 0 && $nodeCrCount{$mynode} == 0 && $nodeStCount{$mynode} != 0) {
   &printAbStDnRow();
  }
     elsif ($nodeDnCount{$mynode} != 0 && $nodeStCount{$mynode} != 0 && $nodeAbCount{$mynode} == 0 && $nodeCrCount{$mynode} != 0) {
   &printCrStDnRow();
}
# 
     elsif($nodeDnCount{$mynode} != 0 && $nodeCrCount{$mynode} != 0 && $nodeAbCount{$mynode} != 0 && $nodeStCount{$mynode} != 0 ) {
   &printAbCrStDnRow();
  }       
     elsif ($nodeDnCount{$mynode} == 0 && $nodeAbCount{$mynode} != 0 && $nodeCrCount{$mynode} != 0 && $nodeStCount{$mynode} != 0) {
   &printAbCrStRow();

 }else {       
 &printRow();
}
}

 &printTotal();

 close (MAILFILE);

  &endHtml();

######################

sub beginHtml {

print <<END;
 <html>
  <head>
          <title>CRS Jobs Monitor  </title>
</head>
   <body BGCOLOR=\"#ccffff\"> 
        <h1 align=center>CRS Jobs Monitor</h1>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH= 220 HEIGHT=80><B>Node ID </B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs crashed</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs aborted</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs with staging failed</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>Done</B></TD>
<TD ALIGN=CENTER WIDTH= 100  HEIGHT=80><B>Number of Jobs <br>with file notfound</B></TD>
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
<td>$nodeDnCount{$mynode}</td>
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
<td>$nodeDnCount{$mynode}</td>
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
<td>$nodeDnCount{$mynode}</td>
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
<td>$nodeDnCount{$mynode}</td>
</TR>
END

}
#######################

 sub printTotal {

print <<END;
<TR ALIGN=CENTER bgcolor=lightblue>
<td>Total</td>
<td>$TotCrCount</td>
<td>$TotAbCount</td>
<td>$TotStCount</td>
<td>$TotDnCount</td>
</TR>
END

}

#######################

 sub printDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}
#######################

 sub printAbDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printCrDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printAbCrRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
<td>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printAbStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printCrStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printAbCrDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printAbStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}

#######################

 sub printCrStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}
#######################

 sub printAbCrStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td bgcolor=lightgreen>$nodeDnCount{$mynode}</td>
</TR>
END

}
#######################

 sub printAbCrStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount{$mynode}</td>
<td bgcolor=red>$nodeAbCount{$mynode}</td>
<td bgcolor=red>$nodeStCount{$mynode}</td>
<td>$nodeDnCount{$mynode}</td>
</TR>
END

}

#####################
sub endHtml {
my $Date = `/bin/date`;

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


