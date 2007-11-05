#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# ProdSummary.pl
#
# Production Summary for real data from FileCatalog.
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
 my @trigg = $fileC->run_query(trgsetupname);
 my @colls = $fileC->run_query(collision);

 $fileC->clear_context( );

 my @detc = ("all","tpc","svt","rich","tof","ftpc","ssd","emc","eemc","bsmd","esmd","fpd","pmd"); 
 my @fieldm = ("all","FullField","ReversedFullField","HalfField","ReversedHalfField","FieldOff");
 my @location = ("HPSS","NFS","local");

  push @prod, "all";
  push @prod, @prodSr;
  push @trig, "all";
  push @trig, @trigg;
  push @col, "all";
  push @col, @colls; 

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
print "<h1 align=center>Production Summary</h1>\n";
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
                   -default=>all,                   
                   -size=>6                              
                   );  

print "</h3>";
print "</td><td>";
print "<h3 align=center>Production tag:</h3>";
print "<h3 align=center>";
print $query->scrolling_list(-name=>'SetP',  
                   -values=>\@prod,
                   -default=>all,                   
                   -size=>6                              
                   );                                  
 
 print "</h3>";
 print "</td><td>";
 print "<h3 align=center>Trigger set:</h3>";
 print "<h3 align=center>";
 print $query->scrolling_list(-name=>'SetT',
                    -values=>\@trig,
                    -default=>all, 
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
 print $query->start_html('Production Summary');
 print "<body bgcolor=\"cornsilk\">\n";


#####  Find sets in DataSet table

 my @daqHpEvts = ();
 my @daqHpSize = ();
 my @evtHpSize = ();
 my @evDstEvts = ();
 my @muDstEvts = ();
 my @muDstSize = ();
 my $TdaqHpSize = 0;
 my $TevtHpSize = 0;
 my $TmuDstSize = 0;
 my $mfield;
 
if ($coll eq "all" and $trigD eq "all" and $prodSer eq "all" and $fieldM eq "all" and $detSet eq "all" ) {

  $fileC->set_context("filetype=daq_reco_MuDst","storage=$Loc");

  @muDstEvts = $fileC->run_query("sum(events)");
  @muDstSize = $fileC->run_query("sum(size)");

  $fileC->clear_context( );

 $fileC->set_context("filetype=daq_reco_event","storage=$Loc");

 @evDstEvts = $fileC->run_query("sum(events)");
 @evtHpSize = $fileC->run_query("sum(size)");

   $fileC->clear_context( );

 $fileC->set_context("filetype=online_daq","sanity=1","storage=hpss");

 @daqHpEvts = $fileC->run_query("sum(events)");
 @daqHpSize = $fileC->run_query("sum(size)");

   $fileC->clear_context( );

 }else {

######################### MuDst.root files data

     if($coll ne "all") {
   $fileC->set_context("filetype=daq_reco_MuDst","collision=$coll","storage=$Loc");  
  };

     if($trigD ne "all") {
  $fileC->set_context("filetype=daq_reco_MuDst","trgsetupname=$trigD","storage=$Loc"); 
  };

     if($fieldM ne "all") {
  $fileC->set_context("filetype=daq_reco_MuDst","magscale=$fieldM","storage=$Loc");
  };

     if($prodSer ne "all")  {
  $fileC->set_context("filetype=daq_reco_MuDst","production=$prodSer","storage=$Loc"); 
 };
  
     if($detSet ne "all")  {
   $fileC->set_context("filetype=daq_reco_MuDst","$detSet=1","storage=$Loc"); 
 }; 

  @muDstEvts = $fileC->run_query("sum(events)");
  @muDstSize = $fileC->run_query("sum(size)");

  $fileC->clear_context( );

######################### event.root files data

     if($coll ne "all") {
   $fileC->set_context("filetype=daq_reco_event","collision=$coll","storage=$Loc");  
  };

     if($trigD ne "all") {
  $fileC->set_context("filetype=daq_reco_event","trgsetupname=$trigD","storage=$Loc"); 
  };

     if($fieldM ne "all") {
  $fileC->set_context("filetype=daq_reco_event","magscale=$fieldM","storage=$Loc");
  };

     if($prodSer ne "all")  {
  $fileC->set_context("filetype=daq_reco_event","production=$prodSer","storage=$Loc"); 
 };
  
     if($detSet ne "all")  {
   $fileC->set_context("filetype=daq_reco_event","$detSet=1","storage=$Loc"); 
 }; 

  @evDstEvts = $fileC->run_query("sum(events)");
  @evtHpSize = $fileC->run_query("sum(size)");

  $fileC->clear_context( );

########################## daq data

     if($coll ne "all") {
   $fileC->set_context("filetype=online_daq","collision=$coll","sanity=1","storage=$Loc");  
  };

     if($trigD ne "all") {
  $fileC->set_context("filetype=online_daq","trgsetupname=$trigD","sanity=1","storage=$Loc"); 
  };

     if($fieldM ne "all") {
  $fileC->set_context("filetype=online_daq","magscale=$fieldM","sanity=1","storage=$Loc");
  };
  
     if($detSet ne "all")  {
   $fileC->set_context("filetype=online_daq","$detSet=1","sanity=1","storage=$Loc"); 
 }; 

    @daqHpEvts = $fileC->run_query("sum(events)");
    @daqHpSize = $fileC->run_query("sum(size)");

  $fileC->clear_context( ); 

 };



 if( $evDstEvts[0] <= 0.1 ) {$evDstEvts[0] = 0};
 if( $muDstEvts[0] <= 0.1 ) {$muDstEvts[0] = 0};
 if( $daqHpEvts[0] <= 0.1 ) {$daqHpEvts[0] = 0}; 
 if( $evtHpSize[0] <= 0.1 ) {$evtHpSize[0] = 0};
 if( $daqHpSize[0] <= 0.1 ) {$daqHpSize[0] = 0};
 if( $muDstSize[0] <= 0.1 ) {$muDstSize[0] = 0};


 $fileC->destroy();

    $TdaqHpSize = int($daqHpSize[0]/1024/1024/1024);
    $TevtHpSize = int($evtHpSize[0]/1024/1024/1024);
    $TmuDstSize = int($muDstSize[0]/1024/1024/1024);


&beginHtml();


print <<END;
<TR ALIGN=CENTER HEIGHT=80 bgcolor=\"#ffdc9f\">
<td HEIGHT=80><h3>$TdaqHpSize</h3></td>
<td HEIGHT=80><h3>$daqHpEvts[0]</h3></td>
<td HEIGHT=80><h3>$TevtHpSize</h3></td>
<td HEIGHT=80><h3>$evDstEvts[0]</h3></td>
<td HEIGHT=80><h3>$TmuDstSize</h3></td>
<td HEIGHT=80><h3>$muDstEvts[0]</h3></td>
</TR>
END

 
 print $qqr->end_html;
 &endHtml();

 }


######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"#ccffff\"> 
 <h2 ALIGN=CENTER><B> Summary for $coll events in $prodSer production of $trigD trigger set</B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Size(GB) of DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events<br>in DAQ files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events <br>in event.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Size(GB) of MuDst.root files</B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>Number of Events <br>in MuDst.root files</B></TD>
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












