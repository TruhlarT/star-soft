#!/usr/bin/env perl
#
# $Log:
#
# L.Didenko
#
# ProdDDstreams_pico.pl
#
# Production summary from FileCatalog by stream data for Distributed disk.
# 
################################################################################################

use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use FileCatalog;

use DBI;

($sec,$min,$hour,$mday,$mon,$year) = localtime();

my $mon =  $mon + 1;

if( $mon < 10) { $mon = '0'.$mon };
if( $mday < 10) { $mday = '0'.$mday };
if( $hour < 10) { $hour = '0'.$hour };
if( $min < 10) { $min = '0'.$min };
if( $sec < 10) { $sec = '0'.$sec };


my $todate = ($year+1900)."-".$mon."-".$mday." ".$hour.":".$min.":".$sec;

my $nowdate = ($year+1900).$mon.$mday;
my $nowyear = $year+1900; 

my $crtime;
my $daydif;
my $mondif;
my $pyear;

my %collHash = (
                 AuAu_200_production_2016 => 'auau200',
                 AuAu200_production2_2016 => 'auau200',
                 dAu200_production_2016 => 'dau200',
                 dAu20_production_2016 => 'dau20',
                 dAu62_production_2016 => 'dau62',
                 dAu39_production_2016 => 'dau39',
                 production_pp200trans_2015 => 'pp200',
                 production_pp200long_2015 => 'pp200',
                 production_pp200long2_2015 => 'pp200',
                 production_pp200long3_2015 => 'pp200',
                 production_fms_pp200trans_2015 => 'pp200',
                 production_fms_pp200long2_2015 => 'pp200',
                 production_pAu200_2015 => 'pAu200',
                 production_pAu200_fms_2015 => 'pAu200',
                 production_pAl200_2015 => 'pAl200',
                 production_pAl200_fms_2015 => 'pAl200',
                 production_pAl200_2015_lowlumi => 'pAl200',
                 fixedTarget2015 => 'pAu19',
                 AuAu_200_production_2014 => 'auau200',
                 AuAu_200_production_high_2014 => 'auau200',
                 AuAu_200_production_mid_2014 => 'auau200',
                 AuAu_200_production_low_2014 => 'auau200',
                 AuAu_200_LowLuminosity_2014 => 'auau200',
                 AuAu200_production_high_2014_RDO14-4-off => 'auau200',
                 production_15GeV_2014 => 'auau15',
                 AuHe3_production_2014 => 'He3Au200',
                 pp500_production_2013 => 'pp500',
                 pp500_production_2013a => 'pp500',
                 pp500_production_2013_noendcap => 'pp500',
                 pp500_production_fms_2013 => 'pp500',
                 pp500_production_fmsonly_2013 => 'pp500',
                 pp500_upc_2013 => 'pp500',
                 pp500_lowlumi_2013 => 'pp500',
                 pp500_strawman_2013 => 'pp500',
                 UU_production_2012 => 'UU193',
                 cuAu_production_2012 => 'cuAu200',
                 cuAu_production_2012_noemc => 'cuAu200',
                 pp200_production_2012 => 'pp200',
                 pp200_production_2012_setup => 'pp200',
                 pp200_production_noemc_2012 => 'pp200',
                 pp200_production_fms_2012 => 'pp200',
                 low_luminosity2009 => 'pp200', 
                 pp500_production_2012 => 'pp500',
                 pp500_production_2012_noeemc => 'pp500',
                 pp500_production_fms_2012 => 'pp500',
                 pp500_lowluminosity_2012 => 'pp500',
                 AuAu5Gev_test     => 'auau5',
                 AuAu200_production_2011 => 'auau200',
                 AuAu200_vernier_2011 => 'auau200',
                 AuAu27_production_2011 => 'auau27',
                 pp500_production_2011  => 'pp500',
                 pp500_production_2011_noeemc => 'pp500',
                 pp500_production_2011_fms => 'pp500',
                 pp500_production_2011_long_fms => 'pp500',
                 pp500_production_2011_long => 'pp500',
                 pp500_production_2011_long_noeemc => 'pp500',
                 Vernier_scan_pp500 => 'pp500',
                 AuAu200_production => 'auau200',
                 LowLuminosity_2010 => 'auau200',
                 AuAu62_production => 'auau62',
                 AuAu39_production => 'auau39',                           
                 AuAu19_production => 'auau19.6',
                 AuAu18_production => 'auau19.6',
                 AuAu19_test1 => 'auau19.6',
                 AuAu19_test2 => 'auau19.6',
                 AuAu11_production => 'auau11.5',
                 AuAu7_production => 'auau7.7',
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
                 production62GeV => 'auau62',
                 emcPed => 'auau62',
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
                 lowLuminosity2009 => 'pp500', 
                 production2009_200Gev_Single => 'pp200', 
                 vernier_scan => 'pp200', 
                 tof_production2009_single => 'pp200', 
                 production2009_200Gev_nocal => 'pp200', 
                 production2009_200Gev_noendcap => 'pp200', 
                 tof_prepost_himult => 'pp200', 
                 pp2ppStrawMan => 'pp200',
                 vpd_minbias => 'pp500',
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
                 ppTune => 'pp200',
                 testppUPC => 'pp200',
                 ppLongRamp => 'pp200',
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
                 cu22ProductionMinBias => 'cucu22', 
	      );
             
my %yrHash = (
                 AuAu_200_production_2016 => 'year2016',
                 AuAu200_production2_2016 => 'year2016',
                 dAu200_production_2016 => 'year2016',
                 dAu20_production_2016 => 'year2016',
                 dAu62_production_2016 => 'year2016',
                 dAu39_production_2016 => 'year2016',
                 production_pp200trans_2015 => 'year2015',
                 production_pp200long_2015 => 'year2015',
                 production_pp200long2_2015 => 'year2015',
                 production_pp200long3_2015 => 'year2015',
                 production_fms_pp200trans_2015 => 'year2015',
                 production_fms_pp200long2_2015 => 'year2015',
                 production_pAu200_2015 => 'year2015',
                 production_pAu200_fms_2015 => 'year2015',
                 production_pAl200_2015 => 'year2015',
                 production_pAl200_fms_2015 => 'year2015',
                 production_pAl200_2015_lowlumi => 'year2015',
                 fixedTarget2015 => 'year2015',
                 AuAu_200_production_2014 => 'year2014',
                 AuAu_200_production_high_2014 => 'year2014',
                 AuAu_200_production_mid_2014 => 'year2014',
                 AuAu_200_production_low_2014 => 'year2014',
                 AuAu_200_LowLuminosity_2014 => 'year2014',
                 AuAu200_production_high_2014_RDO14-4-off => 'year2014',
                 production_15GeV_2014 => 'year2014',
                 AuHe3_production_2014 => 'year2014',
                 pp500_production_2013 => 'year2013',
                 pp500_production_2013a => 'year2013',
                 pp500_production_2013_noendcap => 'year2013',
                 pp500_production_fms_2013 => 'year2013',
                 pp500_production_fmsonly_2013 => 'year2013',
                 pp500_upc_2013 => 'year2013',
                 pp500_lowlumi_2013 => 'year2013',
                 pp500_strawman_2013 =>'year2013',
                 UU_production_2012 => 'year2012',
                 cuAu_production_2012 => 'year2012',
                 cuAu_production_2012_noemc => 'year2012',
                 pp200_production_2012 => 'year2012',
                 pp200_production_2012_setup => 'year2012',
                 pp200_production_fms_2012 => 'year2012',
                 pp200_production_noemc_2012 => 'year2012',
                 low_luminosity_2012 => 'year2012',
                 pp500_production_2012 => 'year2012',
                 pp500_production_2012_noeemc => 'year2012',
                 pp500_production_fms_2012 => 'year2012',
                 pp500_lowluminosity_2012 => 'year2012',
                 AuAu5Gev_test   => 'year2012',
                 AuAu200_production_2011 => 'year2011',
                 AuAu200_vernier_2011 => 'year2011',
                 AuAu27_production_2011 => 'year2011',
                 pp500_production_2011  => 'year2011',
                 pp500_production_2011_noeemc => 'year2011',
                 pp500_production_2011_fms => 'year2011',
                 pp500_production_2011_long_fms => 'year2011',
                 pp500_production_2011_long => 'year2011',
                 pp500_production_2011_long_noeemc => 'year2011',
                 Vernier_scan_pp500 => 'year2011',
                 AuAu200_production => 'year2010',
                 LowLuminosity_2010 => 'year2010',
                 AuAu62_production => 'year2010',
                 AuAu39_production => 'year2010',                           
                 AuAu19_production => 'year2011',
                 AuAu18_production => 'year2011',
                 AuAu19_test1 => 'year2011',
                 AuAu19_test2 => 'year2011',
                 AuAu11_production => 'year2010',
                 AuAu7_production => 'year2010',
                 productionCentral => 'year2001',
                 productionCentral600 => 'year2001',
                 productionCentral1200 => 'year2001',
                 vandermeer => 'year2001',
                 productionHigh => 'year2004',
                 productionMid => 'year2004',
                 productionLow => 'year2004',
                 productionHalfLow => 'year2004',
                 productionHalfHigh => 'year2004',
                 productionMinBias => 'year2004',
                 MinBiasVertex => 'year2001',
                 minBias22GeVZDC => 'year2001',
                 production62GeV => 'year2004',
                 emcPed => 'year2004',
                 minbias => 'year2000', 
                 central => 'year2000', 
                 LowEnergy_newtier1 => 'year2007', 
                 lowEnergy2008 => 'year2008', 
                 bbcvpd => 'year2008',                  
                 ppMinBias => 'year2004', 
                 pp => 'year2004', 
                 eemcCalibration => 'year2004', 
                 zdcSMDTest => 'year2004', 
                 productionPP => 'year2004', 
                 emcCalPP => 'year2004', 
                 productionPPnoBarrel => 'year2004', 
                 productionPPnoEndcap => 'year2004', 
                 ppProductionMinBias => 'year2005', 
                 eemc_led => 'year2005', 
                 ppProduction => 'year2006', 
                 ppEmcCheck => 'year2006', 
                 ppAdjJetPatch => 'year2005', 
                 ppVHM => 'year2005', 
                 Jpsi => 'year2005', 
                 ppTransProduction => 'year2005', 
                 ppTransProductionMinBias => 'year2005', 
                 ppEmcBackgroundCheck => 'year2006', 
                 pp2006MinBias => 'year2006', 
                 barrelBackground => 'year2006', 
                 muonminbias => 'year2006', 
                 upsilonTest => 'year2006', 
                 ppProductionTrans => 'year2006', 
                 ppProductionTransFPDonly => 'year2006', 
                 ppProductionTransNoEMC => 'year2006', 
                 ppLongTest => 'year2006', 
                 ppProductionLong => 'year2006', 
                 ppProductionLongNoEmc => 'year2006', 
                 ppProductionJPsi => 'year2006', 
                 ppProduction2008 => 'year2008', 
                 ppProduction2008-2 => 'year2008', 
                 pp2pp => 'year2008', 
                 low_luminosity2009 => 'year2009', 
                 lowLuminosity2009 => 'year2009', 
                 pp2pp_VPDMB => 'year2009', 
                 pp2pp_Production2009 => 'year2009', 
                 zdc_polarimetry => 'year2009', 
                 commission2009_200Gev_Lo => 'year2009', 
                 commission2009_200Gev_Hi => 'year2009', 
                 production2009_200Gev_Hi => 'year2009', 
                 production2009_200Gev_Lo => 'year2009', 
                 low_luminosity2009 => 'year2009', 
                 production2009_200Gev_Single => 'year2009', 
                 vernier_scan => 'year2009', 
                 tof_production2009_single => 'year2009', 
                 production2009_200Gev_nocal => 'year2009', 
                 production2009_200Gev_noendcap => 'year2009', 
                 tof_prepost_himult => 'year2009', 
                 pp2ppStrawMan => 'year2009',
                 vpd_minbias => 'year2009',
                 physics2009_early_b => 'year2009',
                 production2009_500GeV => 'year2009',
                 production2009_500GeV_carl => 'year2009',
                 test2009_carl => 'year2009',
                 test2009_carl_hi_thr => 'year2009',
                 teest2009_carl_b => 'year2009',
                 productionZDCpolarimetry => 'year2009',
                 zdc_polarimetry_test => 'year2009',
                 production2009_500Gev_b => 'year2009',
                 testtier0325 => 'year2009',
                 production2009_500Gev_c => 'year2009',
                 production2009_500Gev_25 => 'year2009',
                 ppProduction62 => 'year2006',
                 ppProductionMB62 => 'year2006',
                 barrelBackground62 => 'year2006',
                 pp400MinBias => 'year2005',
                 pp400Production => 'year2005',
                 FPDtbEMCproduction => 'year2002',
                 FPDEMCproduction => 'year2002',
                 fpdTrigger => 'year2002',
                 FPDXmas => 'year2002',
                 bbcTrigger => 'year2002',
                 fpdTopBottom => 'year2002',
                 topology => 'year2002',
                 ppFPDTOFu => 'year2003',
                 ppTune => 'year2003',
                 testppUPC => 'year2003',
                 ppLongRamp => 'year2003',
                 EmcCheck => 'year2008',
                 dAuTOF => 'year2003',
                 dAuCombined => 'year2003',
                 dAuMinBias => 'year2003',
                 UPCCombined => 'year2003',
                 dAuFPD => 'year2003',
                 zeroBias => 'year2003',
                 HTonly => 'year2003',
                 production_dAu2008 => 'year2008',
                 production_mb2008 => 'year2008',
                 production_PMD2008 => 'year2008',
                 cuProductionMinBias => 'year2005',
                 cuProductionHighTower => 'year2005',
                 cu62productionMinBias  => 'year2005',
                 cu22ProductionMinBias => 'year2005',
	      );

$yrHash{"2007ProductionMinBias"} = "year2007";
$yrHash{"2007Production2"} = "year2007";
$yrHash{"2007TestProduction"} = "year2007";
$yrHash{"2007LowLuminosity"} = "year2007";
$yrHash{"vpd_minbias-jan1"} = "year2009";
$yrHash{"setup-2008"} = "year2008";
$yrHash{"ppProduction2008-2"} = "year2008";
$yrHash{"ppTrans-1"} = "year2003";
$yrHash{"ppLong-1"} = "year2003";
$yrHash{"testJPsi-3"} = "year2003";
$yrHash{"ProductionMinBias"} = "year2001";
$yrHash{"productionMinBias"} = "year2004";

$collHash{"2007ProductionMinBias"} = "auau200";
$collHash{"2007Production2"} = "auau200";
$collHash{"2007TestProduction"} = "auau200";
$collHash{"2007LowLuminosity"} = "auau200";
$collHash{"vpd_minbias-jan1"} = "pp500";
$collHash{"setup-2008"} = "dau200";
$collHash{"ppProduction2008-2"} = "pp200";
$collHash{"ppTrans-1"} = "pp200";
$collHash{"ppLong-1"} = "pp200";
$collHash{"testJPsi-3"} = "dau200";


my $prod_html = "/star/u/starlib/localdata/ProdDDstreams_pico.html";

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
my @filelst = ();
my @yrdat = ();
my @prt = ();
my $nline = 0;
my $nlist = 0;
my $ssize = 0;
my $dsize  = 0;
my @numfiles = ();
my @nfileHpss = ();
my @filehpss = ();
my @eventhpss = ();
my @sumevthpss = ();
my $pdrate = 0;
my @prodrate = ();
my @nstreams = ();
my $nstr = 0;

my @sumevet = ();
my @sumsize = ();
my @sumfile = ();

my @trigset = ();
my @prodtag = ();
my @strname = ();
my @yeardt = ();
my @colls = ();

my $prodname = "n/a";

 $fileC->set_context("filetype=daq_reco_picoDst","storage=local","limit=0");

  @prodset = $fileC->run_query("trgsetupname","ordd(production)");

 $fileC->clear_context( );


 &beginHtml();

    foreach my $line (@prodset){

    @prt = (); 
    @prt = split("::",$line); 

    $trig[$nlist] = $prt[0];
    $prod[$nlist] = $prt[1];  
    $coll[$nlist] = $collHash{$trig[$nlist]};
    $yrdat[$nlist] = $yrHash{$trig[$nlist]};

	if($trig[$nlist] eq "ppMinBias" and ($prod[$nlist] eq "P02ge" or $prod[$nlist] eq "P03if")) {
	    $yrdat[$nlist] = "year2002";
	}elsif($trig[$nlist] eq "ppMinBias" and ($prod[$nlist]  eq "P03ie" or $prod[$nlist] eq "P03ih")) {
             $yrdat[$nlist] = "year2003";
	}elsif($trig[$nlist] eq "ppMinBias" and ($prod[$nlist]  eq "P04ik" or $prod[$nlist] eq "P04ij")) {
             $yrdat[$nlist] = "year2004";
        }        

	if($trig[$nlist] eq "productionCentral" and ($prod[$nlist] =~ /P02/ or $prod[$nlist] =~ /P03/ )) {
	    $yrdat[$nlist] = "year2001";
        }elsif( $trig[$nlist] eq "productionCentral" and $prod[$nlist] eq "P05ic" ) {
           $yrdat[$nlist] = "year2004";
        }

        if( $trig[$nlist] eq "ProductionMinBias" and ($prod[$nlist] =~ /P05/ or $prod[$nlist] =~ /P04/ ) ) {
           $yrdat[$nlist] = "year2004";
           $trig[$nlist] = "productionMinBias";
	}elsif($trig[$nlist] eq "ProductionMinBias" and $prod[$nlist] =~ /P02/ ) {
	    $yrdat[$nlist] = "year2001";
	}
        
       if( $trig[$nlist] eq "ppProduction" and $prod[$nlist] eq "P05if" ) {
           $yrdat[$nlist] = "year2005";
       }elsif( $trig[$nlist] eq "ppEmcBackground" and $prod[$nlist] eq "P05if" ) {
          $yrdat[$nlist] = "year2005";
       }elsif( $trig[$nlist] eq "ppEmcCheck" and $prod[$nlist] eq "P05if" ) {  
          $yrdat[$nlist] = "year2005";
       }

         if( $trig[$nlist] eq "eemcCalibration" and $prod[$nlist] eq "P04id" ) {          
	     $coll[$nlist] = "auau62";
	 }


	next if($trig[$nlist] eq "productionLow" and $prod[$nlist] eq "P04if");
	next if($trig[$nlist] eq "dAuMinBias" and $prod[$nlist] eq "P03if");

        next if($prod[$nlist] eq "P03id");
        next if($prod[$nlist] eq "P03ig");     
        next if($prod[$nlist] eq "P02gh1");
        next if($prod[$nlist] eq "P03gb");
        next if($prod[$nlist] eq "P03gc"); 
        next if($prod[$nlist] eq "P03ie");          

 @runevents = ();
 $runevents[0] = 0;  
 @datasize = ();
 $datasize[0] = 0; 
 @filelst = (); 
 @eventhpss = ();
 $eventhpss[0] = 0;
 @filehpss = (); 
 @nstreams = ();
 $nstr = 0;

    $fileC->set_context("trgsetupname=$trig[$nlist]","production=$prod[$nlist]","filetype=daq_reco_picoDst","storage=local","sanity=1","limit=0");

   @nstreams = $fileC->run_query(sname2); 

    $nstr = scalar(@nstreams);

   $fileC->clear_context( );

     for ($kk=0; $kk< $nstr; $kk++) {

    $fileC->set_context("trgsetupname=$trig[$nlist]","production=$prod[$nlist]","sname2=$nstreams[$kk]","filetype=daq_reco_picoDst","storage=local","sanity=1","limit=0" );


   @runevents = $fileC->run_query("sum(events)");
   @datasize = $fileC->run_query("sum(size)");
   @filelst = $fileC->run_query(filename);

   $trigset[$nline] = $trig[$nlist];
   $prodtag[$nline] = $prod[$nlist];
   $colls[$nline]   = $coll[$nlist];
   $yeardt[$nline]  = $yrdat[$nlist];
   $strname[$nline] = $nstreams[$kk];
   $sumevet[$nline] = $runevents[0];
   $sumsize[$nline] = $datasize[0];
   $sumfile[$nline] = scalar(@filelst);        
   
   $fileC->clear_context( );

   $fileC->set_context("trgsetupname=$trig[$nlist]","production=$prod[$nlist]","filetype=daq_reco_picoDst","sname2=$nstreams[$kk]","storage=HPSS","sanity=1","limit=0");

   @filehpss = $fileC->run_query(filename);
   @eventhpss = $fileC->run_query("sum(events)");

    $sumevthpss[$nline] = $eventhpss[0];
    $nfileHpss[$nline] =scalar(@filehpss);  

   $fileC->clear_context( );

#####

   $dsize = $sumsize[$nline]/1000000000.;

   if($dsize < 10 ) {
   $sumsize[$nline] = sprintf("%.2f", $dsize);
   }elsif($dsize < 100 ) {
   $sumsize[$nline] = sprintf("%.1f", $dsize);
   }else{
   $sumsize[$nline] = int($dsize + 0.5);
    }

    if($nfileHpss[$nline] >=1) {
   $pdrate = ($sumfile[$nline]/$nfileHpss[$nline])*100;
   $prodrate[$nline] = sprintf("%.1f", $pdrate);

  }else{
    $pdrate = 0;
    $prodrate[$nline] = 0;
  }

    print HTML "<TR ALIGN=CENTER HEIGHT=10 bgcolor=\"cornsilk\">\n";
    if($kk == 0) {

    print HTML "<td HEIGHT=10 rowspan=$nstr><h3>$trigset[$nline]</h3></td>\n";
    }

    print HTML "<td HEIGHT=10><h3>$strname[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$colls[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$yeardt[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$prodtag[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$sumevet[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$sumevthpss[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$sumsize[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$sumfile[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$nfileHpss[$nline]</h3></td>\n";
    print HTML "<td HEIGHT=10><h3>$prodrate[$nline]</h3></td>\n";
    print HTML "</TR>\n";


      $nline++;

    }
      $nlist++;
}
 
   $fileC->destroy();

 &endHtml();


######################

sub beginHtml {


 open (HTML,">$prod_html") or die "can't write to $prod_html ";
 print HTML "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n";
 print HTML "<html>\n";
 print HTML " <head>\n";
 print HTML "          <title>Production picoDst Summary on DD  </title>\n";
 print HTML "  </head>\n";
 print HTML "  <body BGCOLOR=\"cornsilk\">\n"; 
 print HTML "  <h2 ALIGN=CENTER> <B> Production picoDst Summary on Distributed Disk by stream data </B></h2>\n";
 print HTML "  <h3 ALIGN=CENTER> Generated on $todate</h3>\n";
 print HTML " <TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 bgcolor=\"#ffdc9f\">\n";
 print HTML " <TR>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=60><B><h3>Trigger setup name</h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Stream name</h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Collision</h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Year of data taken</h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Production Tag</h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of Events on DD<h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of Events on HPSS<h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Size of picoDst on DD (GB)<h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of picoDst files on DD<h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>Number of picoDst files on HPSS<h3></B></TD>\n";
 print HTML " <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=60><B><h3>% of production saved on DD<h3></B></TD>\n";
 print HTML " </TR> \n";

}

#####################
sub endHtml {
my $Date = `date`;

 print HTML "</TABLE>\n";
 print HTML "      <h5>\n";
 print HTML "      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";
 print HTML "<!-- Created: Mon July 17  11:58:00 -->\n";
 print HTML "<!-- hhmts start -->\n";
 print HTML "Last modified: $Date\n";
 print HTML "<!-- hhmts end -->\n";
 print HTML "  </body>\n";
 print HTML "</html>\n";
 close (HTML);

}













