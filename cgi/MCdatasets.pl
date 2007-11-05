#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# MCdatasets.pl
#
# List of MC datasets in FileCatalog.
# 
################################################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use CGI;
use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;

use DBI;
use Mysql;

my $SITE         = "BNL";
my $status       = (0==1);


my $fileC = new FileCatalog();

    $fileC->connect_as($SITE."::User","FC_user") || die "Connection failed for FC_user\n";

my @coll  = ();
my @evgen = ();
my @geom  = ();

 $fileC->set_context("filetype=MC_fzd","limit=0");

my @evtgen = $fileC->run_query(generator);
my @geomyr = $fileC->run_query('orda(geometry)');
my @cols = $fileC->run_query(collision);

 $fileC->clear_context( );

 my @datatype = ("MC_fzd","MC_reco_MuDst","MC_reco_event","MC_reco_dst");

  push @coll, "all";
  push @coll, @cols;
  push @evgen, "all";
  push @evgen, @evtgen;
  push @geom, "all";
  push @geom, @geomyr;


my ($query) = @_;

 $query = new CGI;

 my $scriptname = $query->url(-relative=>1);

my $colls  =  $query->param('SetC');
my $evtgr  =  $query->param('SetE');
my $geoyr  =  $query->param('SetG');
my $datat  =  $query->param('SetD');

#####################################################################################

  if( $colls eq "" and $evtgr eq "" and $geoyr eq "" ) {

print $query->header;
print $query->start_html('List of MC Datasets');

print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center>List of MC Datasets</h1>\n";
print "<br>";


print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";
print "<h3 align=center>Collisions</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetC',  
                   -values=>\@coll,                   
                   -default=>all,
                   -size=>6                              
                   );  

print "</h3>";
print "</td><td>";
print "<h3 align=center>Event Generator</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetE',  
                   -values=>\@evgen,
                   -default=>all,                   
                   -size=>6                              
                   );                                  
 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Geometry year</h3>";
 print "<h3 align=center>";
 print $query->scrolling_list(-name=>'SetG',
                    -values=>\@geom,
                    -default=>all, 
                    -size=>6
                    );  

 print "</h3>";
 print "</td> </table><hr><center>";


 print "<br><br>";
 print "<h3 align=center>Data Type</h3>";
 print "<h3 align=center>";
 print $query->scrolling_list(-name=>'SetD',
                    -values=>\@datatype,
                    -default=>MC_fzd,
                    -size=>2
                    ); 


 print "</h3>";
 print "<p>";
 print "<p><br><br>"; 
 print $query->submit;
 print "<p><br>";
 print $query->reset;
 print $query->endform;
 print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

  print $query->end_html;

  }else{

my $qqr = new CGI;


my $colls  =  $qqr->param('SetC');
my $evtgr  =  $qqr->param('SetE');
my $geoyr  =  $qqr->param('SetG');
my $datat  =  $qqr->param('SetD');
my $Loc    =  "HPSS";

 print $qqr->header;
 print $query->start_html('List of MC Datasets');
 print "<body bgcolor=\"cornsilk\">\n";


#####  Find sets in DataSet table

 my @mcdata = ();
 my @mcruns = ();
 my @mcpath = ();
 my @mcset  = ();
 my @prod   = ();
 my $topdir;

 if($datat eq "MC_fzd") {

  $topdir = "/home/starsink/raw/"; 

 }else{

   $topdir = "/home/starreco/reco/"; 
 }

  if( $colls eq "all" and $evtgr eq "all" and $geoyr eq "all" ) {
 
  $fileC->set_context("filetype=$datat","storage=$Loc","limit=0");

  @mcdata = $fileC->run_query("orda(runnumber)","path","production");
 
 $fileC->clear_context( );

 }else {

######################### MuDst.root files data

     if($colls ne "all") {
   $fileC->set_context("collision=$colls","filetype=$datat","storage=$Loc","limit=0");  
  };

     if($evtgr ne "all") {
  $fileC->set_context("path~$evtgr","filetype=$datat","storage=$Loc","limit=0"); 
  };

     if($geoyr ne "all") {
  $fileC->set_context("path~$geoyr","filetype=$datat","storage=$Loc","limit=0");
  };

  @mcdata = $fileC->run_query("orda(runnumber)","path","production");

  $fileC->clear_context( );

 };

 $fileC->destroy();
  

my @prt = ();
my $nlist = 0;


if(scalar(@mcdata) < 1) {

 print "<br><br>", "\n";

  print "<h2 align=center>No data for this query. Check MC Production Web page for available datasets</h2>","\n";
     print "<h3 align=center> http://www.star.bnl.gov/STAR/comp/prod/MCProdList.html</h3>","\n";


 print "<br><br><br>", "\n";
 
} else{

 &beginHtml();

 $nlist = 0;

  foreach my $line (@mcdata){
      @prt = ();
      @prt = split("::",$line);

  $mcruns[$nlist] = $prt[0];
  $mcpath[$nlist] = $prt[1];
  $mcpath[$nlist] =~ s|$topdir||g;  
  $prod[$nlist] = $prt[2];
  
print <<END;
<TR ALIGN=CENTER HEIGHT=60 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$mcpath[$nlist]</h3></td>
<td HEIGHT=10><h3>$mcruns[$nlist]</h3></td>
<td HEIGHT=10><h3>$prod[$nlist]</h3></td>
</TR>
END
  $nlist++;

 }

 } 
 print $qqr->end_html;
 &endHtml();

 }


######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"#ccffff\"> 
 <h2 ALIGN=CENTER><B>List of MC datasets for $colls events, $evtgr event generator and $geoyr geometry</B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"60%\" HEIGHT=60><B><h2>List of datasets</h2></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h2>Run numbers</h2></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h2>Production</h2></B></TD>
</TR> 
    </body>
END
}

#####################
sub endHtml {
my $Date = `/bin/date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Wed July 26  05:29:25 MET 2000 -->
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












