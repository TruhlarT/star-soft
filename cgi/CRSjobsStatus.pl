#! /opt/star/bin/perl -w
#
#  $Id:
#
#  $Log:   CRSjobsStatus.pl - monitoring of CRS jobs
#           
#  L.Didenko
###############################################################################


use CGI;
use Mysql;
use Class::Struct;

require "/afs/rhic/star/packages/scripts/dbCpProdSetup.pl";

&cgiSetup();

&beginHtml();

my $mynode; 
my $nodeCrCount;
my $nodeStCount;
my $nodeAbCount;
my $nodeDnCount;
my $nodeFNFCount;
my @jobsCount = ();
my $njobsCount = 0;

 struct NodeAttr => {
         node    => '$',
         crash   => '$',
         abort   => '$',
         staging => '$',
         donejob => '$',
         nofile  => '$'
};

my $TotAbCount = 0;
my $TotDnCount = 0;
my $TotCrCount = 0;
my $TotStCount = 0;
my $TotFNFCount = 0;


    &StDbProdConnect();
 $sql="SELECT  nodeName, crashedJobs, abortedJobs, stagingFailed, doneJobs, fileNotFound from $nodeStatusT" ;

      $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
      $cursor->execute;
 
       while(@fields = $cursor->fetchrow) {
       my $cols=$cursor->{NUM_OF_FIELDS};
           $fObjAdr = \(NodeAttr->new());
 
      for($i=0;$i<$cols;$i++) {
        my $fvalue=$fields[$i];
        my $fname=$cursor->{NAME}->[$i];
#          print "$fname = $fvalue\n" ;

        ($$fObjAdr)->node($fvalue)     if( $fname eq 'nodeName');
        ($$fObjAdr)->crash($fvalue)    if( $fname eq 'crashedJobs');
        ($$fObjAdr)->abort($fvalue)    if( $fname eq 'abortedJobs');
        ($$fObjAdr)->staging($fvalue)  if( $fname eq 'stagingFailed');
        ($$fObjAdr)->donejob($fvalue)  if( $fname eq 'doneJobs'); 
        ($$fObjAdr)->nofile($fvalue)   if( $fname eq 'fileNotFound');
      }
        
        $jobsCount[$njobsCount] = $fObjAdr;
        $njobsCount++;
}

  foreach my $eachNode(@jobsCount) {
      $mynode = ($$eachNode)->node;
      $nodeCrCount = ($$eachNode)->crash;
      $nodeAbCount = ($$eachNode)->abort;
      $nodeStCount = ($$eachNode)->staging; 
      $nodeDnCount = ($$eachNode)->donejob;       
      $nodeFNFCount = ($$eachNode)->nofile;
      
      $TotAbCount += $nodeCrCount;
      $TotDnCount += $nodeAbCount;
      $TotCrCount += $nodeStCount;
      $TotStCount += $nodeDnCount;
      $TotFNFCount += $nodeFNFCount;

     if(($nodeDnCount  != 0) && ($nodeCrCount  == 0) && ($nodeAbCount == 0) && ($nodeStCount == 0) ) {
   &printDnRow();
  }      
     elsif($nodeDnCount  != 0 && $nodeCrCount  != 0 && $nodeAbCount  == 0 && $nodeStCount  == 0 ) {
   &printCrDnRow();
  }       
     elsif ($nodeDnCount  != 0 && $nodeAbCount  != 0 && $nodeCrCount  == 0 && $nodeStCount  == 0 ) {
   &printAbDnRow();
  }
     elsif ($nodeDnCount  != 0 && $nodeStCount  != 0 && $nodeAbCount  == 0 && $nodeCrCount  == 0 ) {
   &printStDnRow();
 }
#
     elsif($nodeDnCount  == 0 && $nodeCrCount  != 0 && $nodeAbCount == 0 && $nodeStCount  == 0 ) {
   &printCrRow();
  }       
     elsif ($nodeDnCount  == 0 && $nodeAbCount  != 0 && $nodeCrCount  == 0 && $nodeStCount  == 0) {
   &printAbRow();
  }
     elsif ($nodeDnCount  == 0 && $nodeStCount  != 0 && $nodeAbCount  == 0 && $nodeCrCount  == 0) {
   &printStRow();
}
#
     elsif($nodeDnCount  == 0 && $nodeCrCount  != 0 && $nodeAbCount  != 0 && $nodeStCount  == 0 ) {
   &printAbCrRow();
  }       
     elsif ($nodeDnCount  == 0 && $nodeAbCount  != 0 && $nodeCrCount  == 0 && $nodeStCount  != 0) {
   &printAbStRow();
  }
     elsif ($nodeDnCount  == 0 && $nodeStCount  != 0 && $nodeAbCount  == 0 && $nodeCrCount  != 0) {
   &printCrStRow();
}
#
     elsif($nodeDnCount  != 0 && $nodeCrCount  != 0 && $nodeAbCount  != 0 && $nodeStCount  == 0 ) {
   &printAbCrDnRow();
  }       
     elsif ($nodeDnCount  != 0 && $nodeAbCount  != 0 && $nodeCrCount  == 0 && $nodeStCount  != 0) {
   &printAbStDnRow();
  }
     elsif ($nodeDnCount  != 0 && $nodeStCount  != 0 && $nodeAbCount  == 0 && $nodeCrCount  != 0) {
   &printCrStDnRow();
}
# 
     elsif($nodeDnCount  != 0 && $nodeCrCount  != 0 && $nodeAbCount  != 0 && $nodeStCount  != 0 ) {
   &printAbCrStDnRow();
  }       
     elsif ($nodeDnCount  == 0 && $nodeAbCount  != 0 && $nodeCrCount  != 0 && $nodeStCount  != 0) {
   &printAbCrStRow();
  }
 elsif ($nodeDnCount  == 0 && $nodeAbCount  == 0 && $nodeCrCount  == 0 && $nodeStCount  == 0 && $nodeFNFCount  != 0) {
   &printFNFRow(); 
 }else {       
 &printRow();
}
}

 &printTotal();

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
<td>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printCrRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
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
<td>$TotFNFCount</td>
</TR>
END

}

#######################

 sub printDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}
#######################

 sub printAbDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printCrDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printAbCrRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printAbStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printCrStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printAbCrDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printAbStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

#######################

 sub printCrStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}
#######################

 sub printAbCrStDnRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td bgcolor=lightgreen>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}
#######################

 sub printAbCrStRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td bgcolor=red>$nodeCrCount </td>
<td bgcolor=red>$nodeAbCount </td>
<td bgcolor=red>$nodeStCount </td>
<td>$nodeDnCount </td>
<td>$nodeFNFCount </td>
</TR>
END

}

########################
 sub printFNFRow {

print <<END;
<TR ALIGN=CENTER>
<td>$mynode</td>
<td>$nodeCrCount </td>
<td>$nodeAbCount </td>
<td>$nodeStCount </td>
<td>$nodeDnCount </td>
<td bgcolor=red>$nodeFNFCount</td>
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


