#!/usr/local/bin/perl
#
# $Log:
#
# L.Didenko
#
# ProdTrgList.pl
#
# List of trigset set productions from FileCatalog.
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

my %collHash = (
              AuAu200_production_2011 => 'auau200',
              AuAu200_production => 'auau200',
              AuAu62_production => 'auau62',
              AuAu39_production => 'auau39',                           
              AuAu19_production => 'auau19.6',
#              AuAu11_production => 'auau11.5',
#              AuAu7_production => 'auau7.7',
              2007LowLuminosity => 'auau200',
              2007Production2 => 'auau200',
              2007ProductionMinBias => 'auau200',
              ProductionMinBias => 'auau200',
              productionCentral => 'auau200',
              productionCentral600 => 'auau200',
              productionCentral1200 => 'auau200',
              vandermeer => 'auau200',
              productionHigh => 'auau200',
              productionMid => 'auau200',
              productionLow => 'auau200',
              productionHalfLow => 'auau200',
              productionHalfHigh => 'auau200',
              MinBiasVertex => 'auau200',
              minBias22GeVZDC => 'auau20',
              minbias => 'auau130', 
              central => 'auau130', 
              LowEnergy_newtier1 => 'auau9', 
              lowEnergy2008 => 'auau9', 
              bbcvpd => 'auau9', 
              ppMinBias => 'pp200', 
              pp => 'pp200', 
              eemcCalibration => 'pp200', 
              zdcSMDTest => 'pp200', 
              productionPP => 'pp200', 
              emcCalPP => 'pp200', 
              productionPPnoBarrel => 'pp200', 
              productionPPnoEndcap => 'pp200', 
              ppProductionMinBias => 'pp200', 
              eemc_led => 'pp200', 
              ppProduction => 'pp200', 
              ppEmcCheck => 'pp200', 
              ppAdjJetPatch => 'pp200', 
              ppVHM => 'pp200', 
              Jpsi => 'pp200', 
              ppTransProduction => 'pp200', 
              ppTransProductionMinBias => 'pp200', 
              ppEmcBackgroundCheck => 'pp200', 
              pp2006MinBias => 'pp200', 
              barrelBackground => 'pp200', 
              muonminbias => 'pp200', 
              upsilonTest => 'pp200', 
              ppProductionTrans => 'pp200', 
              ppProductionTransFPDonly => 'pp200', 
              ppProductionTransNoEMC => 'pp200', 
              ppLongTest => 'pp200', 
              ppProductionLong => 'pp200', 
              ppProductionLongNoEmc => 'pp200', 
              ppProductionJPsi => 'pp200', 
              ppProduction2008 => 'pp200', 
              ppProduction2008-2 => 'pp200', 
              pp2pp => 'pp200', 
              low_luminosity2009 => 'pp200', 
              pp2pp_VPDMB => 'pp200', 
              pp2pp_Production2009 => 'pp200', 
              zdc_polarimetry => 'pp200', 
              commission2009_200Gev_Lo => 'pp200', 
              commission2009_200Gev_Hi => 'pp200', 
              production2009_200Gev_Hi => 'pp200', 
              production2009_200Gev_Lo => 'pp200', 
              low_luminosity2009 => 'pp200', 
              production2009_200Gev_Single => 'pp200', 
              vernier_scan => 'pp200', 
              tof_production2009_single => 'pp200', 
              production2009_200Gev_nocal => 'pp200', 
              production2009_200Gev_noendcap => 'pp200', 
              tof_prepost_himult => 'pp200', 
              pp2ppStrawMan => 'pp200',
              vpd_minbias => 'pp500',
              vpd_minbias-jan1 => 'pp500',
              physics2009_early_b => 'pp500',
              production2009_500GeV => 'pp500',
              production2009_500GeV_carl => 'pp500',
              test2009_carl => 'pp500',
              test2009_carl_hi_thr => 'pp500',
              teest2009_carl_b => 'pp500',
              productionZDCpolarimetry => 'pp500',
              zdc_polarimetry_test => 'pp500',
              production2009_500Gev_b => 'pp500',
              testtier0325 => 'pp500',
              production2009_500Gev_c => 'pp500',
              production2009_500Gev_25 => 'pp500',
              ppProduction62 => 'pp62',
              ppProductionMB62 => 'pp62',
              barrelBackground62 => 'pp62',
              pp400MinBias => 'pp400',
              pp400Production => 'pp400',
              FPDtbEMCproduction => 'pp200',
              FPDEMCproduction => 'pp200',
              fpdTrigger => 'pp200',
              FPDXmas => 'pp200',
              bbcTrigger => 'pp200',
              fpdTopBottom => 'pp200',
              topology => 'pp200',
              ppFPDTOFu => 'pp200',
              ppLong-1 => 'pp200',
              ppTrans-1 => 'pp200',
              ppTune => 'pp200',
              testppUPC => 'pp200',
              ppLongRamp => 'pp200',
              testJPsi-3 => 'dau200',
              EmcCheck => 'dau200',
              dAuTOF => 'dau200',
              dAuCombined => 'dau200',
              dAuMinBias => 'dau200',
              UPCCombined => 'dau200',
              dAuFPD => 'dau200',
              zeroBias => 'dau200',
              HTonly => 'dau200',
              production_dAu2008 => 'dau200',
              production_mb2008 => 'dau200',
              production_PMD2008 => 'dau200',
              setup-2008 => 'dau200',
              cuProductionMinBias => 'cucu200',
              cuProductionHighTower => 'cucu200',
              cu62productionMinBias  => 'cucu62',
              cu22ProductionMinBias => 'cucu22' 
	      );
             


my $SITE         = "BNL";
my $status       = (0==1);


my $fileC = new FileCatalog();

    $fileC->connect_as($SITE."::User","FC_user") || die "Connection failed for FC_user\n";

my @coll = ();
my @trig = ();
my @prod = ();
my @sumevt = ();
my @prodset = ();
my @runevents = ();
my @sumsize = ();
my @datasize = ();
my @prt = ();
my $nline = 0;
my $nlist = 0;

my $trg0 = "n/a";

 $fileC->set_context("filetype=daq_reco_MuDst","storage=hpss","limit=0");

 my @prodset = $fileC->run_query("trgsetupname","ordd(production)");

 $fileC->clear_context( );

&beginHtml();

    foreach my $line (@prodset){

	next if($line =~ /$trg0/);
        next if($line =~ /DEV/);

    @prt = (); 
    @prt = split("::",$line); 

    $trig[$nlist] = $prt[0];
    $prod[$nlist] = $prt[1];  
    $coll[$nlist] = $collHash{$trig[$nlist]};

     @runevents = ();
     $runevents[0] = 0;  
     @datasize = ();
     $datasize[0] = 0; 

    $fileC->set_context("trgsetupname=$trig[$nlist]","production=$prod[$nlist]","filetype=daq_reco_MuDst","storage=hpss");
 
   @runevents = $fileC->run_query("sum(events)");
   @datasize = $fileC->run_query("sum(size)");

   $fileC->clear_context( );

   $sumevt[$nlist] = $runevents[0];
   $sumsize[$nlist] = int($datasize[0]/1000000000);

 print <<END;

<TR ALIGN=CENTER HEIGHT=60 bgcolor=\"#ffdc9f\">
<td HEIGHT=10><h3>$coll[$nlist]</h3></td>
<td HEIGHT=10><h3>$trig[$nlist]</h3></td>
<td HEIGHT=10><h3>$prod[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumevt[$nlist]</h3></td>
<td HEIGHT=10><h3>$sumsize[$nlist]</h3></td>
</TR>
END

      $nlist++;

    }
 
   $fileC->destroy();

 &endHtml();


######################

sub beginHtml {

print <<END;

  <html>
   <body BGCOLOR=\"cornsilk\"> 
 <h2 ALIGN=CENTER> <B> Real Data Production Summary </B></h2>
<br>
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Collision</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"40%\" HEIGHT=60><B><h3>Trigger sets</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Production Tag</h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Number of Events<h3></B></TD>
<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Size (GB) of MuDst <h3></B></TD>
</TR> 
   </head>
    </body>
END
}

#####################
sub endHtml {
my $Date = `date`;

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












