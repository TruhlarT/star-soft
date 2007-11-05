#! /usr/local/bin/perl -w
#
#  $Id:
#  dbMCProdRetrv.pl - retrive MC files from Database
#  L. Didenko
# 
###############################################################################

use CGI;
use Mysql;

require "/afs/rhic.bnl.gov/star/packages/cgi/dbCpProdSetup.pl";

my $debugOn = 0;
my %pair;
my @pck;

$query = new CGI;

my $set  = $query->param("SetMC");
my $prodr = $query->param("prodSet");

my @spl = ();

@spl = split(" ",$set);
my $setM = $spl[0];

@spl = ();
@spl = split(" ",$prodr);
my $prSet = $spl[0];

@pck = split ("%",$prSet);
 
my $prodSer = $pck[0]; 
my $fform = $pck[1];
my $loc = $pck[2];
my $mcom = "no";
my $mstat;

my $prod = "%$prodSer%";
my $ext = "%$fform";
my $Loc = "$loc%";


&cgiSetup();

&beginHtml();

&StDbProdConnect();

  if(  $prodSer ne "all" and $fform =~ /root/ ) {

$sql="SELECT jobID, fName, path, Nevents, size, createTime, type, dataStatus, comment FROM $FileCatalogT WHERE dataset = ? AND jobID LIKE ? AND fName like ? AND site like ? ";

    $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($setM,$prod,$ext,$Loc);

}elsif($prodSer eq "all" and $fform =~ /root/ ) {

$sql="SELECT jobID, fName, path, Nevents, size, createTime, type, dataStatus, comment FROM $FileCatalogT WHERE dataset = ? AND fName like ? AND site like ? ";

      $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($setM,$ext,$Loc);

}elsif ( $fform = "fzd") {

$sql="SELECT jobID, fName, path, Nevents, size, createTime, type, dataStatus, comment FROM $FileCatalogT WHERE dataset = ? AND fName like ? AND site like ? ";
   $cursor =$dbh->prepare($sql)
     || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute($setM,$ext,$Loc);

}

   my $counter = 0;
   while(@fields = $cursor->fetchrow) {
      my $cols=$cursor->{NUM_OF_FIELDS};

 for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
    my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;
    $pair{$fname} = $fvalue;
   $mstat = $fvalue if( $fname eq 'dataStatus');   
    $mcom = $fvalue if( $fname eq 'comment');   
    } 
      if ($mstat eq "OK") {; 
      $pair{'comment'} = "no";
			  }
   &printRow();

}

&StDbProdDisconnect();

&endHtml();

#################
sub beginHtml {

print <<END;

<html>
  <head>
          <title>List of Files</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
     <h3>set = $setM </h3>
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"10%\" HEIGHT=50><B>jobID</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>fName</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>path</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>size</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>createTime</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>Nevents</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>type</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>dataStatus</B></TD>
<TD WIDTH=\"10%\" HEIGHT=50><B>comment</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$pair{'jobID'}</td>
<td>$pair{'fName'}</td>
<td>$pair{'path'}</td>
<td>$pair{'size'}</td>
<td>$pair{'createTime'}</td>
<td>$pair{'Nevents'}</td>
<td>$pair{'type'}</td>
<td>$pair{'dataStatus'}</td>
<td>$pair{'comment'}</td>
</tr>
END

}

###############
sub endHtml {
my $Date = `/bin/date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Tue Set 10  05:29:25 MET 1999 -->
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
