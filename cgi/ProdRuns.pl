#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# ProdRuns.pl
#
# Real data production summary by runnumbers from FileCatalog.
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

my @col = ();
my @trig = ();
my @prod = ();


 $fileC->set_context("filetype=daq_reco_event","limit=0");

 my @prodSr = $fileC->run_query('orda(production)');
 my @trig = $fileC->run_query(trgsetupname);
 my @col = $fileC->run_query(collision);

 $fileC->clear_context( );

 my @detc = ("all","tpc","svt","rich","tof","ftpc","ssd","emc","eemc","bsmd","esmd","fpd","pmd"); 
 my @fieldm = ("all","FullField","ReversedFullField","HalfField","ReversedHalfField","FieldOff");
 my @location = ("HPSS","NFS","local");

my ($query) = @_;

 $query = new CGI;

 my $scriptname = $query->url(-relative=>1);

my $prodSer =  $query->param('SetP');
my $trigD   =  $query->param('SetT');
my $fieldM  =  $query->param('SetF');
my $detSet  =  $query->param('SetD');
my $coll  =  $query->param('SetC');
my $Loc   =  $query->param('SetLc');

##################################################################################################################

  if( $coll eq "" and $prodSer eq "" and $trigD eq "" and $fieldM eq "" and $detSet eq "" ) {

print $query->header;
print $query->start_html('Production');

print $query->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center>Production Summary by Run Numbers</h1>\n";
print "<br>";


print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";
print "<h3 align=center>Collisions:</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetC',  
                   -values=>\@col,                   
                   -size=>6                              
                   );  

print "</h3>";
print "</td><td>";
print "<h3 align=center>Production tag:</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetP',  
                   -values=>\@prodSr,                   
                   -size=>6                              
                   );                                  
 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Trigger set:</h3>";
 print "<h3 align=center>";
 print $query->scrolling_list(-name=>'SetT',
                    -values=>\@trig, 
                   -size=>6
                    ); 

 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Magnetic Field:</h3>";
 print "<h3 align=center>";
 print $query->scrolling_list(-name=>'SetF',
                    -values=>\@fieldm,
                    -default=>all, 
                    -size=>6
                    ); 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Detectors:</h3>";
 print "<h3 align=center>";
 print $query->popup_menu(-name=>'SetD',
                    -values=>\@detc,
                    -default=>all, 
                    -size=>6
                    ); 

print "</h3>";
print "</td> </table><hr><center>";

print "<h3 align=center>Location:</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetLc',
                    -values=>\@location,
                    -default=>hpss,
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

my $prodSer =  $qqr->param('SetP');
my $trigD   =  $qqr->param('SetT');
my $fieldM  =  $qqr->param('SetF');
my $detSet  =  $qqr->param('SetD');
my $coll  =  $qqr->param('SetC');
my $Loc   =  $qqr->param('SetLc');


 print $qqr->header;
 print $query->start_html('List of Run Numbers in Production');
 print "<body bgcolor=\"cornsilk\">\n";


#####  Find sets in DataSet table

 my @prodruns = ();
 my @runlist = ();
 my @runconfig  = ();
 my @runfiles = ();
 my @nmudst = ();
 my @runevents = ();

 
if ($coll eq "all" and $trigD eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

  $fileC->set_context("filetype=daq_reco_MuDst","production=$prodSer","storage=$Loc","limit=0");

  @prodruns = $fileC->run_query("orda(runnumber)","configuration");

  $fileC->clear_context( );

 }else {

######################### MuDst.root files data

     if($coll ne "all") {
   $fileC->set_context("filetype=daq_reco_MuDst","collision=$coll","production=$prodSer","storage=$Loc","limit=0");  
  };

     if($trigD ne "all") {
  $fileC->set_context("filetype=daq_reco_MuDst","trgsetupname=$trigD","production=$prodSer","storage=$Loc","limit=0"); 
  };

     if($fieldM ne "all") {
  $fileC->set_context("filetype=daq_reco_MuDst","magscale=$fieldM","production=$prodSer","storage=$Loc","limit=0");
  };

     if($detSet ne "all")  {
   $fileC->set_context("filetype=daq_reco_MuDst","$detSet=1","production=$prodSer","storage=$Loc","limit=0"); 
 }; 

  @prodruns = $fileC->run_query("orda(runnumber)","configuration");

  $fileC->clear_context( );

 };


my @prt = ();
my $nrun = 0;


if(scalar(@prodruns) < 1) {

 print "<br><br>", "\n";

  print "<h2 align=center>No data for this production. Check Real Data Production Web page for available productions</h2>","\n";
     print "<h3 align=center> http://www.star.bnl.gov/STAR/comp/prod/ProdList.html</h3>","\n";


 print "<br><br><br>", "\n";
 
} else{

 &beginHtml();

  foreach my $line (@prodruns){
 
      @runfiles = ();
  @prt = split("::",$line);
  $runlist[$nrun] = $prt[0]; 
  $runconfig[$nrun] = $prt[1];

    $fileC->set_context("filetype=daq_reco_MuDst","runnumber=$runlist[$nrun]","storage=$Loc","limit=0");  
  @runfiles = $fileC->run_query("filename");
  $nmudst[$nrun] = scalar(@runfiles);  
  $fileC->clear_context( ); 

   $fileC->set_context("filetype=daq_reco_MuDst","runnumber=$runlist[$nrun]","storage=$Loc");  
  @runevents = $fileC->run_query("sum(events)");  
  $fileC->clear_context( ); 
  
print <<END;
<TR ALIGN=CENTER HEIGHT=60 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$runlist[$nrun]</h3></td>
<td HEIGHT=10><h3>$runconfig[$nrun]</h3></td>
<td HEIGHT=10><h3>$nmudst[$nrun]</h3></td>
<td HEIGHT=10><h3>$runevents[0]</h3></td>
</TR>
END
  $nrun++;

 }

 $fileC->destroy();

 } 
 print $qqr->end_html;
 &endHtml();

 }


######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"#ccffff\"> 
 <h2 ALIGN=CENTER><B>Production Summary for $coll events in $prodSer production of $trigD trigger set</B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>List of run numbers</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"60%\" HEIGHT=60><B><h3>Detector configuration</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of MuDst files</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of events<h3></B></TD>
</TR> 
   </head>
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












