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
my $outname;
my $outfile;

my @ndCrCount;
my @ndAbCount;
my @ndStCount; 
my @ndDnCount;

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
                "rcrs6037.rcf.bnl.gov"
);


my $eachNode;

 for ( $ll = 0; $ll<scalar(@nodeList); $ll++) {   
        
       $ndCrCount[$ll]  = 0;
       $ndAbCount[$ll]  = 0;
       $ndStCount[$ll]  = 0;
       $ndDnCount[$ll]  = 0;
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
                "rcrs6037.rcf.bnl.gov" => 36 
 );               


$now = localtime;
($sec,$min,$hour,$mday,$mon) = localtime;

foreach my $int ( $mon,$mday ){
  $int < 10 and $int = '0'.$int;
   $thisday .= $int;
}

$outname = "mail" . "_" .$thisday . "_" . "out";
$outfile = "/star/u/starreco/" . $outname;

print $outfile, "\n";

open (MAILFILE, $outfile ) or die "cannot open $outfile: $!\n";

 @mailfile = <MAILFILE>;

  foreach $mail_line (@mailfile) {
     chop $mail_line ;
     if ($mail_line =~ /JobInfo/ ) {
      @wrd = split ("%", $mail_line);
      $nodeID = $wrd[2];
       print $nodeID, "\n";
      $jbStat = $wrd[1];
      chop $nodeID;
      chop $nodeID;
      $nodeID =~ s/^\ *//g;
# print $nodeID, "\n";
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
     elsif ($jbStat =~ /done/) {
         $ndDnCount[$ii]++;
# print  $jbStat,"\n";    
       }
   } 
 }

my $TotAbCount = 0;
my $TotDnCount = 0;
my $TotCrCount = 0;
my $TotStCount = 0;

for ($ll = 0; $ll < scalar(@nodeList); $ll++) {
      $mynode = $nodeList[$ll];
      $nodeCrCount{$mynode} = $ndCrCount[$ll];
      $nodeAbCount{$mynode} = $ndAbCount[$ll];
      $nodeStCount{$mynode} = $ndStCount[$ll]; 
      $nodeDnCount{$mynode} = $ndDnCount[$ll];       
      
      $TotAbCount += $ndAbCount[$ll];
      $TotDnCount += $ndDnCount[$ll];
      $TotCrCount += $ndCrCount[$ll];
      $TotStCount += $ndStCount[$ll];

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
</TR> 
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


