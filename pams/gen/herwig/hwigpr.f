      PROGRAM HWIGPR
C---COMMON BLOCKS ARE INCLUDED AS FILE HERWIG65.INC
C      INCLUDE 'HERWIG65.INC'
C           ****COMMON BLOCK FILE FOR HERWIG VERSION 6.5****
C
C ALTERATIONS: Layout completely overhauled for 5.9
C
C
C New common blocks added for version 6.1:
C              HWCLUS,HWSUSY,HWRPAR,HWMINB
C
C New variables added for version 6.1:
C              OMHMIX,ET2MIX,PH3MIX,IOP4JT,NPRFMT,
C              PRNDEF,PRNTEX,PRNWEB,EFFMIN,GCUTME,
C              IOP4JT,NPRFMT                       see HWPRAM
C              Y4JT,DURHAM                         see HWHARD
C              QORQQB,QBORQQ                       see HWPROP
C              NRECO                               see HWUCLU
C              TXNAME                              see HWUNAM
C              PPCL,NCL,IDCL                       see HWCLUS
C              TANB,ALPHAH,COSBPA,SINBPA,COSBMA,
C              SINBMA,COSA,SINA,COSB,SINB,COTB,
C              ZMIXSS,ZMXNSS,ZSGNSS,LFCH,RFCH,
C              SLFCH,SRFCH,WMXUSS,WMXVSS,WSGNSS,
C              QMIXSS,LMIXSS,THETAT,THETAB,THETAL,
C              ATSS,ABSS,ALSS,MUSS,FACTSS,GHWWSS,
C              GHZZSS,GHDDSS,GHUUSS,GHWHSS,GHSQSS,
C              XLMNSS,RMMNSS,DMSSM,SENHNC,
C              SSPARITY,SUSYIN                     see HWSUSY
C              LAMDA1,LAMDA2,LAMDA3,HRDCOL,RPARTY,
C              COLUPD                              see HWRPAR
C              PMBN1,PMBN2,PMBN3,PMBK1,PMBK2,
C              PMBM1,PMBM2,PMBP1,PMBP2,PMBP3       see HWMINB
C
C New parameters added for version 6.1:
C              NMXCL
C
C Parameter NMXRES raised to 500
C
C Scalar variables changed to arrays of size 2:
C              CLSMR,PSPLT,CLDIR                   see HWPRAM
C
C   NEW for HERWIG6.200
C
C New common blocks added for version 6.2:
C              HWGRAV                              see HWHGRV
C
C   NEW for HERWIG6.202
C
C New common block added for version 6.202:
C              HW6202
C which contains all other new variables, parameters and
C control flags introduced since version 6.1, so that
C other common blocks become identical to version 6.1
C
C New parameters added for version 6.2:
C              VIPWID,DXRCYL,DXZMAX,DXRSPH,LRSUSY  see HWIGIN
C              GRVLAM,EMGRV,GAMGRV                 see HWHGRV
C
C New control flags added for version 6.2:
C              WZRFR                               see HWBJCO
C              FIX4JT                              see HWIGIN
C              IMSSM,IHIGGS                        see HWUINC
C
C New variable added for version 6.2:
C              PARITY                              see HWUINC
C
C  Version 6.203:
C
C  NMXHEP raised to 4000 for LHC studies
C
C
      IMPLICIT NONE
      DOUBLE PRECISION ZERO,ONE,TWO,THREE,FOUR,HALF
      PARAMETER (ZERO =0.D0, ONE =1.D0, TWO =2.D0,
     &           THREE=3.D0, FOUR=4.D0, HALF=0.5D0)
C
      DOUBLE PRECISION
     & ACCUR,AFCH,ALPFAC,ALPHEM,ANOMSC,ASFIXD,AVWGT,B1LIM,BETAF,BRFRAC,
     & BRHIG,BTCLM,CAFAC,CFFAC,CLDKWT,CLMAX,CLPOW,CLQ,CLSMR,CMMOM,COSS,
     & COSTH,CSPEED,CTHRPW,CTMAX,DECPAR,DECWT,DISF,DKLTM,EBEAM1,EBEAM2,
     & EMLST,EMMAX,EMMIN,EMPOW,EMSCA,ENHANC,ENSOF,EPOLN,ETAMIX,EVWGT,
     & EXAG,F0MIX,F1MIX,F2MIX,GAMH,GAMMAX,GAMW,GAMWT,GAMZ,GAMZP,GCOEF,
     & GEV2NB,GEV2MM,GPOLN,H1MIX,HBAR,HARDST,OMEGA0,PBEAM1,PBEAM2,PDIQK,
     & PGSMX,PGSPL,PHEP,PHIMIX,PHIPAR,PHOMAS,PIFAC,PLTCUT,PPAR,PPOLN,
     & PRECO,PRSOF,PSPLT,PTINT,PTMAX,PTMIN,PTPOW,PTRMS,PXRMS,PWT,Q2MAX,
     & Q2MIN,Q2POW,Q2WWMN,Q2WWMX,QCDL3,QCDL5,QCDLAM,QDIQK,QEV,QFCH,QG,
     & QLIM,QSPAC,QV,QWT,REPWT,RESN,RHOHEP,RHOPAR,RLTIM,RMASS,RMIN,
     & RSPIN,SCABI,SINS,SNGWT,SWEIN,SWTEF,SUD,THMAX,TLOUT,TMTOP,TMNISR,
     & TQWT,VCKM,VFCH,VGCUT,VHEP,VMIN2,VPAR,VPCUT,VQCUT,VTXPIP,VTXQDK,
     & WBIGST,WGTMAX,WGTSUM,WHMIN,WSQSUM,XFACT,XLMIN,XMIX,XMRCT,XX,
     & XXMIN,YBMAX,YBMIN,YJMAX,YJMIN,YMIX,YMRCT,YWWMAX,YWWMIN,ZBINM,
     & ZJMAX,ZMXISR,Y4JT,EFFMIN,PPCL,
     & TANB,ALPHAH,COSBPA,SINBPA,COSBMA,SINBMA,COSA,SINA,COSB,SINB,COTB,
     & ZMIXSS,ZMXNSS,ZSGNSS,LFCH,RFCH,SLFCH,SRFCH, WMXUSS,WMXVSS,WSGNSS,
     & QMIXSS,LMIXSS,THETAT,THETAB,THETAL,ATSS,ABSS,ALSS,MUSS,FACTSS,
     & GHWWSS,GHZZSS,GHDDSS,GHUUSS,GHWHSS,GHSQSS
C--fix by PR 12/7/02 to avoid problems with nag compiler
       DOUBLE PRECISION
     & XLMNSS,RMMNSS,DMSSM,SENHNC,SSPARITY,LAMDA1,LAMDA2,LAMDA3,
     & PMBN1,PMBN2,PMBN3,PMBK1,PMBK2,PMBM1,PMBM2,PMBP1,PMBP2,PMBP3,
     & OMHMIX,ET2MIX,PH3MIX,GCUTME
C
      INTEGER
     & CLDIR,IAPHIG,IBRN,IBSH,ICHRG,ICO,IDCMF,IDHEP,IDHW,IDK,IDKPRD,IDN,
     & IDPAR,IDPDG,IERROR,IFLAV,IFLMAX,IFLMIN,IHPRO,IMQDK,INHAD,INTER,
     & IOPDKL,IOPHIG,IOPREM,IPART1,IPART2,IPRINT,IPRO,IPROC,ISLENT,
     & ISPAC,ISTAT,ISTHEP,ISTPAR,JCOPAR,JDAHEP,JDAPAR,JMOHEP,JMOPAR,
     & JNHAD,LNEXT,LOCN,LOCQ,LRSUD,LSTRT,LWEVT,LWSUD,MAPQ,MAXER,MAXEV,
     & MAXFL,MAXPR,MODBOS,MODMAX,MODPDF,NBTRY,NCLDK,NCOLO,NCTRY,NDKYS,
     & NDTRY,NETRY,NEVHEP,NEVPAR,NFLAV,NGSPL,NHEP,NME,NMODES,NMXCDK,
     & NMXDKS,NMXHEP,NMXJET,NMXMOD,NMXPAR,NMXQDK,NMXRES,NMXSUD,NPAR,
     & NPRODS,NQDK,NQEV,NRES,NRN,NSPAC,NSTRU,NSTRY,NSUD,NUMER,NUMERU,
     & NWGTS,NZBIN,SUDORD,IOP4JT,HRDCOL,NMXCL,NCL,IDCL,NPRFMT,NRECO
C
      LOGICAL
     & AZSOFT,AZSPIN,BGSHAT,BREIT,CLRECO,COLISR,DKPSET,FROST,FSTEVT,
     & FSTWGT,GENEV,GENSOF,HARDME,HVFCEN,MAXDKL,MIXING,NOSPAC,NOWGT,
     & PRNDEC,PIPSMR,PRVTX,RSTAB,SOFTME,TMPAR,TPOL,USECMF,VTOCDK,VTORDK,
     & ZPRIME,RPARTY,COLUPD,PRNDEF,PRNTEX,PRNWEB,DURHAM,SUSYIN,
     & QORQQB,QBORQQ
C
      CHARACTER*4
     & BDECAY
      CHARACTER*8
     & PART1,PART2,RNAME
      CHARACTER*20
     & AUTPDF
      CHARACTER*37
     & TXNAME
C
C New standard event common
      PARAMETER (NMXHEP=4000)
      COMMON/HEPEVT/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
     & JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
C
C Beams, process and number of events
      COMMON/HWBEAM/IPART1,IPART2
      COMMON/HWBMCH/PART1,PART2
      COMMON/HWPROC/EBEAM1,EBEAM2,PBEAM1,PBEAM2,IPROC,MAXEV
C
C Basic parameters (and quantities derived from them)
      COMMON/HWPRAM/AFCH(16,2),ALPHEM,B1LIM,BETAF,BTCLM,CAFAC,CFFAC,
     & CLMAX,CLPOW,CLSMR(2),CSPEED,ENSOF,ETAMIX,F0MIX,F1MIX,F2MIX,GAMH,
     & GAMW,GAMZ,GAMZP,GEV2NB,H1MIX,PDIQK,PGSMX,PGSPL(4),PHIMIX,PIFAC,
     & PRSOF,PSPLT(2),PTRMS,PXRMS,QCDL3,QCDL5,QCDLAM,QDIQK,QFCH(16),QG,
     & QSPAC,QV,SCABI,SWEIN,TMTOP,VFCH(16,2),VCKM(3,3),VGCUT,VQCUT,
     & VPCUT,ZBINM,EFFMIN,OMHMIX,ET2MIX,PH3MIX,GCUTME,
     & IOPREM,IPRINT,ISPAC,LRSUD,LWSUD,MODPDF(2),NBTRY,NCOLO,NCTRY,
     & NDTRY,NETRY,NFLAV,NGSPL,NSTRU,NSTRY,NZBIN,IOP4JT(2),NPRFMT,
     & AZSOFT,AZSPIN,CLDIR(2),HARDME,NOSPAC,PRNDEC,PRVTX,SOFTME,ZPRIME,
     & PRNDEF,PRNTEX,PRNWEB
C
      COMMON/HWPRCH/AUTPDF(2),BDECAY
C
C Parton shower common (same format as /HEPEVT/)
      PARAMETER (NMXPAR=500)
      COMMON/HWPART/NEVPAR,NPAR,ISTPAR(NMXPAR),IDPAR(NMXPAR),
     & JMOPAR(2,NMXPAR),JDAPAR(2,NMXPAR),PPAR(5,NMXPAR),VPAR(4,NMXPAR)
C
C Parton polarization common
      COMMON/HWPARP/DECPAR(2,NMXPAR),PHIPAR(2,NMXPAR),RHOPAR(2,NMXPAR),
     & TMPAR(NMXPAR)
C
C Electroweak boson common
      PARAMETER (MODMAX=50)
      COMMON/HWBOSC/ALPFAC,BRHIG(12),ENHANC(12),GAMMAX,RHOHEP(3,NMXHEP),
     & IOPHIG,MODBOS(MODMAX)
C
C Parton colour common
      COMMON/HWPARC/JCOPAR(4,NMXPAR)
C
C other HERWIG branching, event and hard subprocess common blocks
      COMMON/HWBRCH/ANOMSC(2,2),HARDST,PTINT(3,2),XFACT,INHAD,JNHAD,
     & NSPAC(7),ISLENT,BREIT,FROST,USECMF
C
      COMMON/HWEVNT/AVWGT,EVWGT,GAMWT,TLOUT,WBIGST,WGTMAX,WGTSUM,WSQSUM,
     & IDHW(NMXHEP),IERROR,ISTAT,LWEVT,MAXER,MAXPR,NOWGT,NRN(2),NUMER,
     & NUMERU,NWGTS,GENSOF
C
      COMMON/HWHARD/ASFIXD,CLQ(7,6),COSS,COSTH,CTMAX,DISF(13,2),EMLST,
     & EMMAX,EMMIN,EMPOW,EMSCA,EPOLN(3),GCOEF(7),GPOLN,OMEGA0,PHOMAS,
     & PPOLN(3),PTMAX,PTMIN,PTPOW,Q2MAX,Q2MIN,Q2POW,Q2WWMN,Q2WWMX,QLIM,
     & SINS,THMAX,Y4JT,TMNISR,TQWT,XX(2),XLMIN,XXMIN,YBMAX,YBMIN,YJMAX,
     & YJMIN,YWWMAX,YWWMIN,WHMIN,ZJMAX,ZMXISR,IAPHIG,IBRN(2),IBSH,
     & ICO(10),IDCMF,IDN(10),IFLMAX,IFLMIN,IHPRO,IPRO,MAPQ(6),MAXFL,
     & BGSHAT,COLISR,FSTEVT,FSTWGT,GENEV,HVFCEN,TPOL,DURHAM
C
C Arrays for particle properties (NMXRES = max no of particles defined)
      PARAMETER(NMXRES=500)
      COMMON/HWPROP/RLTIM(0:NMXRES),RMASS(0:NMXRES),RSPIN(0:NMXRES),
     & ICHRG(0:NMXRES),IDPDG(0:NMXRES),IFLAV(0:NMXRES),NRES,
     & VTOCDK(0:NMXRES),VTORDK(0:NMXRES),
     & QORQQB(0:NMXRES),QBORQQ(0:NMXRES)
C
      COMMON/HWUNAM/RNAME(0:NMXRES),TXNAME(2,0:NMXRES)
C
C Arrays for particle decays (NMXDKS = max total no of decays,
C                             NMXMOD = max no of modes for a particle)
      PARAMETER(NMXDKS=4000,NMXMOD=200)
      COMMON/HWUPDT/BRFRAC(NMXDKS),CMMOM(NMXDKS),DKLTM(NMXRES),
     & IDK(NMXDKS),IDKPRD(5,NMXDKS),LNEXT(NMXDKS),LSTRT(NMXRES),NDKYS,
     & NME(NMXDKS),NMODES(NMXRES),NPRODS(NMXDKS),DKPSET,RSTAB(0:NMXRES)
C
C Weights used in cluster decays
      COMMON/HWUWTS/REPWT(0:3,0:4,0:4),SNGWT,DECWT,QWT(3),PWT(12),
     & SWTEF(NMXRES)
C
C Parameters for cluster decays (NMXCDK = max total no of cluster
C                                         decay channels)
      PARAMETER(NMXCDK=4000)
      COMMON/HWUCLU/CLDKWT(NMXCDK),CTHRPW(12,12),PRECO,RESN(12,12),
     & RMIN(12,12),LOCN(12,12),NCLDK(NMXCDK),NRECO,CLRECO
C
C Variables controling mixing and vertex information
C--VTXPIP should have been a 5-vector, problems with NAG compiler
      COMMON/HWDIST/EXAG,GEV2MM,HBAR,PLTCUT,VMIN2,VTXPIP(5),XMIX(2),
     & XMRCT(2),YMIX(2),YMRCT(2),IOPDKL,MAXDKL,MIXING,PIPSMR
C
C Arrays for temporarily storing heavy-b,c-hadrons decaying partonicaly
C (NMXQDK = max no such decays in an event)
      PARAMETER (NMXQDK=20)
      COMMON/HWQDKS/VTXQDK(4,NMXQDK),IMQDK(NMXQDK),LOCQ(NMXQDK),NQDK
C
C Parameters for Sudakov form factors
C (NMXSUD= max no of entries in lookup table)
      PARAMETER (NMXSUD=1024)
      COMMON/HWUSUD/ACCUR,QEV(NMXSUD,6),SUD(NMXSUD,6),INTER,NQEV,NSUD,
     & SUDORD
C
      PARAMETER (NMXJET=200)
C
C SUSY parameters
      COMMON/HWSUSY/
     & TANB,ALPHAH,COSBPA,SINBPA,COSBMA,SINBMA,COSA,SINA,COSB,SINB,COTB,
     & ZMIXSS(4,4),ZMXNSS(4,4),ZSGNSS(4), LFCH(16),RFCH(16),
     & SLFCH(16,4),SRFCH(16,4), WMXUSS(2,2),WMXVSS(2,2), WSGNSS(2),
     & QMIXSS(6,2,2),LMIXSS(6,2,2),
     & THETAT,THETAB,THETAL,ATSS,ABSS,ALSS,MUSS,FACTSS,
     & GHWWSS(3),GHZZSS(3),GHDDSS(4),GHUUSS(4),GHWHSS(3),
     & GHSQSS(4,6,2,2),XLMNSS,RMMNSS,DMSSM,SENHNC(24),SSPARITY,SUSYIN
C
C R-Parity violating parameters and colours
      COMMON /HWRPAR/ LAMDA1(3,3,3),LAMDA2(3,3,3),
     &                LAMDA3(3,3,3),HRDCOL(2,5),RPARTY,COLUPD
C
C Parameters for minimum bias/soft underlying event
      COMMON/HWMINB/
     & PMBN1,PMBN2,PMBN3,PMBK1,PMBK2,PMBM1,PMBM2,PMBP1,PMBP2,PMBP3
C
C Cluster common used by soft event routines
      PARAMETER (NMXCL=500)
      COMMON/HWCLUS/PPCL(5,NMXCL),IDCL(NMXCL),NCL
C
C  Parameters for resonant graviton production
      DOUBLE PRECISION GRVLAM,EMGRV,GAMGRV
      COMMON/HWGRAV/GRVLAM,EMGRV,GAMGRV
C
C  Other new parameters for version 6.2
      DOUBLE PRECISION VIPWID,DXRCYL,DXZMAX,DXRSPH
      LOGICAL WZRFR,FIX4JT
      INTEGER IMSSM,IHIGGS,PARITY,LRSUSY
      COMMON/HW6202/VIPWID(3),DXRCYL,DXZMAX,DXRSPH,WZRFR,FIX4JT,
     & IMSSM,IHIGGS,PARITY,LRSUSY
C
C  New parameters for version 6.203
      DOUBLE PRECISION ABWGT,ABWSUM,AVABW
      INTEGER NNEGWT,NNEGEV
      LOGICAL NEGWTS
      COMMON/HW6203/ABWGT,ABWSUM,AVABW,NNEGWT,NNEGEV,NEGWTS
C
C  New parameters for version 6.3
      INTEGER IMAXCH,IMAXOP
      PARAMETER (IMAXCH=20,IMAXOP=40)
      DOUBLE PRECISION MJJMIN,CHNPRB(IMAXCH)
      INTEGER IOPSTP,IOPSH
      LOGICAL OPTM,CHON(IMAXCH)
      COMMON/HW6300/MJJMIN,CHNPRB,IOPSTP,IOPSH,OPTM,CHON
C  New PDF's for version 6.3
      INTEGER NXMRS,NQMRS,NPMRS
      PARAMETER(NXMRS=49,NQMRS=37,NPMRS=8)
      DOUBLE PRECISION FMRS(3,NPMRS,NXMRS,NQMRS+1)
      COMMON /HWPMRS/FMRS
C  Circe interface for version 6.3
      INTEGER CIRCOP,CIRCAC,CIRCVR,CIRCRV,CIRCCH
      COMMON /HWCIRC/CIRCOP,CIRCAC,CIRCVR,CIRCRV,CIRCCH
C  New parameters and commons for spin correlations
C--constants for the arrays
      INTEGER NMXSPN,NCFMAX
      PARAMETER(NMXSPN=50,NCFMAX=3)
      INTEGER NMODE2,NMODE3,NDIAGR,NMODEB,NMODE4
      PARAMETER(NMODE2=500,NMODE3=500,NDIAGR=8,NMODEB=50,NMODE4=4)
C--common block for X --> X gauge boson
      DOUBLE PRECISION ABMODE(2,NMODEB),BBMODE(2,12,NMODEB),
     & PBMODE(12,NMODEB),WTBMAX(12,NMODEB)
      INTEGER IDBPRT(NMODEB),IBMODE(NMODEB),IBDRTP(NMODEB),NBMODE
      COMMON /HWDSPB/ABMODE,BBMODE,PBMODE,WTBMAX,IDBPRT,IBDRTP,IBMODE,
     & NBMODE
C--common block for two body decays
      DOUBLE PRECISION A2MODE(2,NMODE2),P2MODE(NMODE2),WT2MAX(NMODE2)
      INTEGER ID2PRT(NMODE2),I2DRTP(NMODE2),N2MODE
      COMMON /HWDSP2/A2MODE,P2MODE,WT2MAX,ID2PRT,I2DRTP,N2MODE
C--common block for three body decays
      DOUBLE PRECISION A3MODE(2,NDIAGR,NMODE3),B3MODE(2,NDIAGR,NMODE3),
     & P3MODE(NMODE3),WT3MAX(NMODE3),SPN3CF(NCFMAX,NCFMAX,NMODE3)
      INTEGER ID3PRT(NMODE3),I3MODE(NDIAGR,NMODE3),
     & I3DRTP(NDIAGR,NMODE3),N3MODE,NDI3BY(NMODE3),N3NCFL(NMODE3),
     &  I3DRCF(NDIAGR,NMODE3)
      COMMON /HWDSP3/A3MODE,B3MODE,P3MODE,WT3MAX,SPN3CF,ID3PRT,I3MODE,
     &  I3DRTP,N3MODE,NDI3BY,N3NCFL,I3DRCF
C--common block for four body decays
      DOUBLE PRECISION A4MODE(2,12,NMODE4),B4MODE(2,12,NMODE4),
     & P4MODE(12,12,NMODE4),WT4MAX(12,12,NMODE4)
      INTEGER ID4PRT(NMODE4),I4MODE(2,NMODE4),N4MODE
      COMMON /HWDSP4/A4MODE,B4MODE,P4MODE,WT4MAX,ID4PRT,I4MODE,N4MODE
C--common block for spin correlations in event
      INTEGER NDECSY,NSEARCH,LRDEC,LWDEC
      LOGICAL SYSPIN,THREEB,FOURB
      CHARACTER *6 TAUDEC
      COMMON /HWDSPN/NDECSY,NSEARCH,LRDEC,LWDEC,SYSPIN,THREEB,
     &  FOURB,TAUDEC
                                                                                                      
      INTEGER IDSPN(NMXSPN),JMOSPN(NMXSPN),JDASPN(2,NMXSPN),NSPN,
     &  ISNHEP(NMXHEP),NSNTRY,NCFL(NMXSPN),SPCOPT
      DOUBLE COMPLEX MESPN(2,2,2,2,NCFMAX,NMXSPN),RHOSPN(2,2,NMXSPN)
      DOUBLE PRECISION SPNCFC(NCFMAX,NCFMAX,NMXSPN)
      LOGICAL DECSPN(NMXSPN)
      COMMON /HWSPIN/MESPN,RHOSPN,SPNCFC,IDSPN,JMOSPN,JDASPN,
     &  NSPN,ISNHEP,NSNTRY,DECSPN,NCFL,SPCOPT
      INTEGER JAK1,JAK2,ITDKRC,IFPHOT
      COMMON /HWSTAU/ JAK1,JAK2,ITDKRC,IFPHOT
C
C--common block for Les Houches interface to store information we need
C
      INTEGER MAXHRP
      PARAMETER (MAXHRP=100)
      DOUBLE PRECISION LHWGT(MAXHRP),LHWGTS(MAXHRP),LHMXSM,
     &     LHXSCT(MAXHRP),LHXERR(MAXHRP),LHXMAX(MAXHRP)
      INTEGER LHIWGT(MAXHRP),ITYPLH,LHNEVT(MAXHRP)
      LOGICAL LHSOFT,LHGLSF
      COMMON /HWGUPR/LHWGT,LHWGTS,LHXSCT,LHXERR,LHXMAX,LHMXSM,LHIWGT,
     &     LHNEVT,ITYPLH,LHSOFT,LHGLSF
C
C--common block for HERWIG6.5
C
      LOGICAL PRESPL
      COMMON /HW6500/ PRESPL
      INTEGER ITOPRD
      COMMON /HW6504/ITOPRD
C--the only change for 6505 was to increase MODMAX from 5 to 50
      DOUBLE PRECISION PDFX0,PDFPOW
      COMMON /HW6506/PDFX0,PDFPOW
CCCCCC#include "headpss.inc"
      real*4 PSSHEP,VSSHEP
      INTEGER INTRUN
      COMMON/HEADPSS/PSSHEP(5),VSSHEP(4),INTRUN
      SAVE /HEADPSS/
      INTEGER N
      EXTERNAL HWUDAT
      OPEN(UNIT=13,FORM='FORMATTED',STATUS='OLD',ERR=999,
     &     FILE='herwig.in')
C---MAX NUMBER OF EVENTS THIS RUN
      READ(13,33) INTRUN
      CALL HepRun(INTRUN)
      READ(13,33) MAXEV
33    FORMAT(I10)
C---BEAM PARTICLES
      READ(13,34) PART1
      READ(13,34) PART2
34    FORMAT(a)
C---BEAM MOMENTA
      READ(13,*) PBEAM1
      PBEAM2=PBEAM1
C---PROCESS
      READ(13,33) IPROC
C---INITIALISE OTHER COMMON BLOCKS
      CALL HWIGIN
C---USER CAN RESET PARAMETERS AT
C   THIS POINT, OTHERWISE DEFAULT
C   VALUES IN HWIGIN WILL BE USED.
      READ(13,*) PTMAX
      READ(13,*) PTMIN
      PRVTX=.FALSE.
      MAXER=MAXEV/100
      MAXPR=0
      PTMIN=5.
C   N.B. TO READ SUDAKOV FORM FACTOR FILE ON UNIT 77
C   INSERT THE FOLLOWING TWO LINES IN SUBSEQUENT RUNS
C      LRSUD=77
C      LWSUD=0
C---READ IN SUSY INPUT FILE, IN THIS CASE LHC SUGRA POINT 2
CCCCC      OPEN(UNIT=LRSUSY,FORM='FORMATTED',STATUS='OLD',ERR=999,
CCCCC     &     FILE='sugra_pt2.1200.in')
CCCCC      CALL HWISSP
CCCCC      CLOSE(UNIT=LRSUSY)
C---COMPUTE PARAMETER-DEPENDENT CONSTANTS
      CALL HWUINC
C---CALL HWUSTA TO MAKE ANY PARTICLE STABLE
      CALL HWUSTA('PI0     ')
      CALL HWUSTA('ETA     ')
      CALL HWUSTA('PI-     ')
      CALL HWUSTA('K-      ')
      CALL HWUSTA('PI+     ')
      CALL HWUSTA('K+      ')
      CALL HWUSTA('K_S0    ')
      CALL HWUSTA('K_L0    ')
      CALL HWUSTA('LAMBDA  ')
      CALL HWUSTA('SIGMA0  ')
      CALL HWUSTA('SIGMA-  ')
      CALL HWUSTA('SIGMA+  ')
      CALL HWUSTA('XI-     ')
      CALL HWUSTA('XI0     ')
      CALL HWUSTA('OMEGA-  ')
      CALL HWUSTA('LAMBDABR')
      CALL HWUSTA('SIGMABR0')
      CALL HWUSTA('SIGMABR+')
      CALL HWUSTA('SIGMABR-')
      CALL HWUSTA('XIBAR0  ')
      CALL HWUSTA('XIBAR+  ')
      CALL HWUSTA('OMEGABR+')
C---USER'S INITIAL CALCULATIONS
      CALL HWABEG
C---INITIALISE ELEMENTARY PROCESS
      CALL HWEINI
C---LOOP OVER EVENTS
      DO 100 N=1,MAXEV
C---INITIALISE EVENT
      CALL HWUINE
C---GENERATE HARD SUBPROCESS
      CALL HWEPRO
C---GENERATE PARTON CASCADES
      CALL HWBGEN
C---DO HEAVY OBJECT DECAYS
      CALL HWDHOB
C---DO CLUSTER FORMATION
      CALL HWCFOR
C---DO CLUSTER DECAYS
      CALL HWCDEC
C---DO UNSTABLE PARTICLE DECAYS
      CALL HWDHAD
C---DO HEAVY FLAVOUR HADRON DECAYS
      CALL HWDHVY
C---ADD SOFT UNDERLYING EVENT IF NEEDED
      CALL HWMEVT
C---FINISH EVENT
      CALL HWUFNE
C---USER'S EVENT ANALYSIS
      CALL HWANAL
  100 CONTINUE
C---TERMINATE ELEMENTARY PROCESS
      CALL HWEFIN
C---USER'S TERMINAL CALCULATIONS
      CALL HWAEND
      STOP
 999  WRITE (6,*)
      WRITE (6,*) 'SUSY input file did not open correctly.'
      WRITE (6,*) 'Please check that it is in the right place.'
      WRITE (6,*) 'Examples can be obtained from the ISAWIG web page.'
      WRITE (6,*)
      END
      SUBROUTINE HWABEG
      RETURN
      END
      SUBROUTINE HWANAL
      IMPLICIT NONE
      DOUBLE PRECISION ZERO,ONE,TWO,THREE,FOUR,HALF
      PARAMETER (ZERO =0.D0, ONE =1.D0, TWO =2.D0,
     &           THREE=3.D0, FOUR=4.D0, HALF=0.5D0)
C
      DOUBLE PRECISION
     & ACCUR,AFCH,ALPFAC,ALPHEM,ANOMSC,ASFIXD,AVWGT,B1LIM,BETAF,BRFRAC,
     & BRHIG,BTCLM,CAFAC,CFFAC,CLDKWT,CLMAX,CLPOW,CLQ,CLSMR,CMMOM,COSS,
     & COSTH,CSPEED,CTHRPW,CTMAX,DECPAR,DECWT,DISF,DKLTM,EBEAM1,EBEAM2,
     & EMLST,EMMAX,EMMIN,EMPOW,EMSCA,ENHANC,ENSOF,EPOLN,ETAMIX,EVWGT,
     & EXAG,F0MIX,F1MIX,F2MIX,GAMH,GAMMAX,GAMW,GAMWT,GAMZ,GAMZP,GCOEF,
     & GEV2NB,GEV2MM,GPOLN,H1MIX,HBAR,HARDST,OMEGA0,PBEAM1,PBEAM2,PDIQK,
     & PGSMX,PGSPL,PHEP,PHIMIX,PHIPAR,PHOMAS,PIFAC,PLTCUT,PPAR,PPOLN,
     & PRECO,PRSOF,PSPLT,PTINT,PTMAX,PTMIN,PTPOW,PTRMS,PXRMS,PWT,Q2MAX,
     & Q2MIN,Q2POW,Q2WWMN,Q2WWMX,QCDL3,QCDL5,QCDLAM,QDIQK,QEV,QFCH,QG,
     & QLIM,QSPAC,QV,QWT,REPWT,RESN,RHOHEP,RHOPAR,RLTIM,RMASS,RMIN,
     & RSPIN,SCABI,SINS,SNGWT,SWEIN,SWTEF,SUD,THMAX,TLOUT,TMTOP,TMNISR,
     & TQWT,VCKM,VFCH,VGCUT,VHEP,VMIN2,VPAR,VPCUT,VQCUT,VTXPIP,VTXQDK,
     & WBIGST,WGTMAX,WGTSUM,WHMIN,WSQSUM,XFACT,XLMIN,XMIX,XMRCT,XX,
     & XXMIN,YBMAX,YBMIN,YJMAX,YJMIN,YMIX,YMRCT,YWWMAX,YWWMIN,ZBINM,
     & ZJMAX,ZMXISR,Y4JT,EFFMIN,PPCL,
     & TANB,ALPHAH,COSBPA,SINBPA,COSBMA,SINBMA,COSA,SINA,COSB,SINB,COTB,
     & ZMIXSS,ZMXNSS,ZSGNSS,LFCH,RFCH,SLFCH,SRFCH, WMXUSS,WMXVSS,WSGNSS,
     & QMIXSS,LMIXSS,THETAT,THETAB,THETAL,ATSS,ABSS,ALSS,MUSS,FACTSS,
     & GHWWSS,GHZZSS,GHDDSS,GHUUSS,GHWHSS,GHSQSS
C--fix by PR 12/7/02 to avoid problems with nag compiler
       DOUBLE PRECISION
     & XLMNSS,RMMNSS,DMSSM,SENHNC,SSPARITY,LAMDA1,LAMDA2,LAMDA3,
     & PMBN1,PMBN2,PMBN3,PMBK1,PMBK2,PMBM1,PMBM2,PMBP1,PMBP2,PMBP3,
     & OMHMIX,ET2MIX,PH3MIX,GCUTME
C
      INTEGER
     & CLDIR,IAPHIG,IBRN,IBSH,ICHRG,ICO,IDCMF,IDHEP,IDHW,IDK,IDKPRD,IDN,
     & IDPAR,IDPDG,IERROR,IFLAV,IFLMAX,IFLMIN,IHPRO,IMQDK,INHAD,INTER,
     & IOPDKL,IOPHIG,IOPREM,IPART1,IPART2,IPRINT,IPRO,IPROC,ISLENT,
     & ISPAC,ISTAT,ISTHEP,ISTPAR,JCOPAR,JDAHEP,JDAPAR,JMOHEP,JMOPAR,
     & JNHAD,LNEXT,LOCN,LOCQ,LRSUD,LSTRT,LWEVT,LWSUD,MAPQ,MAXER,MAXEV,
     & MAXFL,MAXPR,MODBOS,MODMAX,MODPDF,NBTRY,NCLDK,NCOLO,NCTRY,NDKYS,
     & NDTRY,NETRY,NEVHEP,NEVPAR,NFLAV,NGSPL,NHEP,NME,NMODES,NMXCDK,
     & NMXDKS,NMXHEP,NMXJET,NMXMOD,NMXPAR,NMXQDK,NMXRES,NMXSUD,NPAR,
     & NPRODS,NQDK,NQEV,NRES,NRN,NSPAC,NSTRU,NSTRY,NSUD,NUMER,NUMERU,
     & NWGTS,NZBIN,SUDORD,IOP4JT,HRDCOL,NMXCL,NCL,IDCL,NPRFMT,NRECO
C
      LOGICAL
     & AZSOFT,AZSPIN,BGSHAT,BREIT,CLRECO,COLISR,DKPSET,FROST,FSTEVT,
     & FSTWGT,GENEV,GENSOF,HARDME,HVFCEN,MAXDKL,MIXING,NOSPAC,NOWGT,
     & PRNDEC,PIPSMR,PRVTX,RSTAB,SOFTME,TMPAR,TPOL,USECMF,VTOCDK,VTORDK,
     & ZPRIME,RPARTY,COLUPD,PRNDEF,PRNTEX,PRNWEB,DURHAM,SUSYIN,
     & QORQQB,QBORQQ
C
      CHARACTER*4
     & BDECAY
      CHARACTER*8
     & PART1,PART2,RNAME
      CHARACTER*20
     & AUTPDF
      CHARACTER*37
     & TXNAME
C
C New standard event common
      PARAMETER (NMXHEP=4000)
      COMMON/HEPEVT/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
     & JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
C
C Beams, process and number of events
      COMMON/HWBEAM/IPART1,IPART2
      COMMON/HWBMCH/PART1,PART2
      COMMON/HWPROC/EBEAM1,EBEAM2,PBEAM1,PBEAM2,IPROC,MAXEV
C
C Basic parameters (and quantities derived from them)
      COMMON/HWPRAM/AFCH(16,2),ALPHEM,B1LIM,BETAF,BTCLM,CAFAC,CFFAC,
     & CLMAX,CLPOW,CLSMR(2),CSPEED,ENSOF,ETAMIX,F0MIX,F1MIX,F2MIX,GAMH,
     & GAMW,GAMZ,GAMZP,GEV2NB,H1MIX,PDIQK,PGSMX,PGSPL(4),PHIMIX,PIFAC,
     & PRSOF,PSPLT(2),PTRMS,PXRMS,QCDL3,QCDL5,QCDLAM,QDIQK,QFCH(16),QG,
     & QSPAC,QV,SCABI,SWEIN,TMTOP,VFCH(16,2),VCKM(3,3),VGCUT,VQCUT,
     & VPCUT,ZBINM,EFFMIN,OMHMIX,ET2MIX,PH3MIX,GCUTME,
     & IOPREM,IPRINT,ISPAC,LRSUD,LWSUD,MODPDF(2),NBTRY,NCOLO,NCTRY,
     & NDTRY,NETRY,NFLAV,NGSPL,NSTRU,NSTRY,NZBIN,IOP4JT(2),NPRFMT,
     & AZSOFT,AZSPIN,CLDIR(2),HARDME,NOSPAC,PRNDEC,PRVTX,SOFTME,ZPRIME,
     & PRNDEF,PRNTEX,PRNWEB
C
      COMMON/HWPRCH/AUTPDF(2),BDECAY
C
C Parton shower common (same format as /HEPEVT/)
      PARAMETER (NMXPAR=500)
      COMMON/HWPART/NEVPAR,NPAR,ISTPAR(NMXPAR),IDPAR(NMXPAR),
     & JMOPAR(2,NMXPAR),JDAPAR(2,NMXPAR),PPAR(5,NMXPAR),VPAR(4,NMXPAR)
C
C Parton polarization common
      COMMON/HWPARP/DECPAR(2,NMXPAR),PHIPAR(2,NMXPAR),RHOPAR(2,NMXPAR),
     & TMPAR(NMXPAR)
C
C Electroweak boson common
      PARAMETER (MODMAX=50)
      COMMON/HWBOSC/ALPFAC,BRHIG(12),ENHANC(12),GAMMAX,RHOHEP(3,NMXHEP),
     & IOPHIG,MODBOS(MODMAX)
C
C Parton colour common
      COMMON/HWPARC/JCOPAR(4,NMXPAR)
C
C other HERWIG branching, event and hard subprocess common blocks
      COMMON/HWBRCH/ANOMSC(2,2),HARDST,PTINT(3,2),XFACT,INHAD,JNHAD,
     & NSPAC(7),ISLENT,BREIT,FROST,USECMF
C
      COMMON/HWEVNT/AVWGT,EVWGT,GAMWT,TLOUT,WBIGST,WGTMAX,WGTSUM,WSQSUM,
     & IDHW(NMXHEP),IERROR,ISTAT,LWEVT,MAXER,MAXPR,NOWGT,NRN(2),NUMER,
     & NUMERU,NWGTS,GENSOF
C
      COMMON/HWHARD/ASFIXD,CLQ(7,6),COSS,COSTH,CTMAX,DISF(13,2),EMLST,
     & EMMAX,EMMIN,EMPOW,EMSCA,EPOLN(3),GCOEF(7),GPOLN,OMEGA0,PHOMAS,
     & PPOLN(3),PTMAX,PTMIN,PTPOW,Q2MAX,Q2MIN,Q2POW,Q2WWMN,Q2WWMX,QLIM,
     & SINS,THMAX,Y4JT,TMNISR,TQWT,XX(2),XLMIN,XXMIN,YBMAX,YBMIN,YJMAX,
     & YJMIN,YWWMAX,YWWMIN,WHMIN,ZJMAX,ZMXISR,IAPHIG,IBRN(2),IBSH,
     & ICO(10),IDCMF,IDN(10),IFLMAX,IFLMIN,IHPRO,IPRO,MAPQ(6),MAXFL,
     & BGSHAT,COLISR,FSTEVT,FSTWGT,GENEV,HVFCEN,TPOL,DURHAM
C
C Arrays for particle properties (NMXRES = max no of particles defined)
      PARAMETER(NMXRES=500)
      COMMON/HWPROP/RLTIM(0:NMXRES),RMASS(0:NMXRES),RSPIN(0:NMXRES),
     & ICHRG(0:NMXRES),IDPDG(0:NMXRES),IFLAV(0:NMXRES),NRES,
     & VTOCDK(0:NMXRES),VTORDK(0:NMXRES),
     & QORQQB(0:NMXRES),QBORQQ(0:NMXRES)
C
      COMMON/HWUNAM/RNAME(0:NMXRES),TXNAME(2,0:NMXRES)
C
C Arrays for particle decays (NMXDKS = max total no of decays,
C                             NMXMOD = max no of modes for a particle)
      PARAMETER(NMXDKS=4000,NMXMOD=200)
      COMMON/HWUPDT/BRFRAC(NMXDKS),CMMOM(NMXDKS),DKLTM(NMXRES),
     & IDK(NMXDKS),IDKPRD(5,NMXDKS),LNEXT(NMXDKS),LSTRT(NMXRES),NDKYS,
     & NME(NMXDKS),NMODES(NMXRES),NPRODS(NMXDKS),DKPSET,RSTAB(0:NMXRES)
C
C Weights used in cluster decays
      COMMON/HWUWTS/REPWT(0:3,0:4,0:4),SNGWT,DECWT,QWT(3),PWT(12),
     & SWTEF(NMXRES)
C
C Parameters for cluster decays (NMXCDK = max total no of cluster
C                                         decay channels)
      PARAMETER(NMXCDK=4000)
      COMMON/HWUCLU/CLDKWT(NMXCDK),CTHRPW(12,12),PRECO,RESN(12,12),
     & RMIN(12,12),LOCN(12,12),NCLDK(NMXCDK),NRECO,CLRECO
C
C Variables controling mixing and vertex information
C--VTXPIP should have been a 5-vector, problems with NAG compiler
      COMMON/HWDIST/EXAG,GEV2MM,HBAR,PLTCUT,VMIN2,VTXPIP(5),XMIX(2),
     & XMRCT(2),YMIX(2),YMRCT(2),IOPDKL,MAXDKL,MIXING,PIPSMR
C
C Arrays for temporarily storing heavy-b,c-hadrons decaying partonicaly
C (NMXQDK = max no such decays in an event)
      PARAMETER (NMXQDK=20)
      COMMON/HWQDKS/VTXQDK(4,NMXQDK),IMQDK(NMXQDK),LOCQ(NMXQDK),NQDK
C
C Parameters for Sudakov form factors
C (NMXSUD= max no of entries in lookup table)
      PARAMETER (NMXSUD=1024)
      COMMON/HWUSUD/ACCUR,QEV(NMXSUD,6),SUD(NMXSUD,6),INTER,NQEV,NSUD,
     & SUDORD
C
      PARAMETER (NMXJET=200)
C
C SUSY parameters
      COMMON/HWSUSY/
     & TANB,ALPHAH,COSBPA,SINBPA,COSBMA,SINBMA,COSA,SINA,COSB,SINB,COTB,
     & ZMIXSS(4,4),ZMXNSS(4,4),ZSGNSS(4), LFCH(16),RFCH(16),
     & SLFCH(16,4),SRFCH(16,4), WMXUSS(2,2),WMXVSS(2,2), WSGNSS(2),
     & QMIXSS(6,2,2),LMIXSS(6,2,2),
     & THETAT,THETAB,THETAL,ATSS,ABSS,ALSS,MUSS,FACTSS,
     & GHWWSS(3),GHZZSS(3),GHDDSS(4),GHUUSS(4),GHWHSS(3),
     & GHSQSS(4,6,2,2),XLMNSS,RMMNSS,DMSSM,SENHNC(24),SSPARITY,SUSYIN
C
C R-Parity violating parameters and colours
      COMMON /HWRPAR/ LAMDA1(3,3,3),LAMDA2(3,3,3),
     &                LAMDA3(3,3,3),HRDCOL(2,5),RPARTY,COLUPD
C
C Parameters for minimum bias/soft underlying event
      COMMON/HWMINB/
     & PMBN1,PMBN2,PMBN3,PMBK1,PMBK2,PMBM1,PMBM2,PMBP1,PMBP2,PMBP3
C
C Cluster common used by soft event routines
      PARAMETER (NMXCL=500)
      COMMON/HWCLUS/PPCL(5,NMXCL),IDCL(NMXCL),NCL
C
C  Parameters for resonant graviton production
      DOUBLE PRECISION GRVLAM,EMGRV,GAMGRV
      COMMON/HWGRAV/GRVLAM,EMGRV,GAMGRV
C
C  Other new parameters for version 6.2
      DOUBLE PRECISION VIPWID,DXRCYL,DXZMAX,DXRSPH
      LOGICAL WZRFR,FIX4JT
      INTEGER IMSSM,IHIGGS,PARITY,LRSUSY
      COMMON/HW6202/VIPWID(3),DXRCYL,DXZMAX,DXRSPH,WZRFR,FIX4JT,
     & IMSSM,IHIGGS,PARITY,LRSUSY
C
C  New parameters for version 6.203
      DOUBLE PRECISION ABWGT,ABWSUM,AVABW
      INTEGER NNEGWT,NNEGEV
      LOGICAL NEGWTS
      COMMON/HW6203/ABWGT,ABWSUM,AVABW,NNEGWT,NNEGEV,NEGWTS
C
C  New parameters for version 6.3
      INTEGER IMAXCH,IMAXOP
      PARAMETER (IMAXCH=20,IMAXOP=40)
      DOUBLE PRECISION MJJMIN,CHNPRB(IMAXCH)
      INTEGER IOPSTP,IOPSH
      LOGICAL OPTM,CHON(IMAXCH)
      COMMON/HW6300/MJJMIN,CHNPRB,IOPSTP,IOPSH,OPTM,CHON
C  New PDF's for version 6.3
      INTEGER NXMRS,NQMRS,NPMRS
      PARAMETER(NXMRS=49,NQMRS=37,NPMRS=8)
      DOUBLE PRECISION FMRS(3,NPMRS,NXMRS,NQMRS+1)
      COMMON /HWPMRS/FMRS
C  Circe interface for version 6.3
      INTEGER CIRCOP,CIRCAC,CIRCVR,CIRCRV,CIRCCH
      COMMON /HWCIRC/CIRCOP,CIRCAC,CIRCVR,CIRCRV,CIRCCH
C  New parameters and commons for spin correlations
C--constants for the arrays
      INTEGER NMXSPN,NCFMAX
      PARAMETER(NMXSPN=50,NCFMAX=3)
      INTEGER NMODE2,NMODE3,NDIAGR,NMODEB,NMODE4
      PARAMETER(NMODE2=500,NMODE3=500,NDIAGR=8,NMODEB=50,NMODE4=4)
C--common block for X --> X gauge boson
      DOUBLE PRECISION ABMODE(2,NMODEB),BBMODE(2,12,NMODEB),
     & PBMODE(12,NMODEB),WTBMAX(12,NMODEB)
      INTEGER IDBPRT(NMODEB),IBMODE(NMODEB),IBDRTP(NMODEB),NBMODE
      COMMON /HWDSPB/ABMODE,BBMODE,PBMODE,WTBMAX,IDBPRT,IBDRTP,IBMODE,
     & NBMODE
C--common block for two body decays
      DOUBLE PRECISION A2MODE(2,NMODE2),P2MODE(NMODE2),WT2MAX(NMODE2)
      INTEGER ID2PRT(NMODE2),I2DRTP(NMODE2),N2MODE
      COMMON /HWDSP2/A2MODE,P2MODE,WT2MAX,ID2PRT,I2DRTP,N2MODE
C--common block for three body decays
      DOUBLE PRECISION A3MODE(2,NDIAGR,NMODE3),B3MODE(2,NDIAGR,NMODE3),
     & P3MODE(NMODE3),WT3MAX(NMODE3),SPN3CF(NCFMAX,NCFMAX,NMODE3)
      INTEGER ID3PRT(NMODE3),I3MODE(NDIAGR,NMODE3),
     & I3DRTP(NDIAGR,NMODE3),N3MODE,NDI3BY(NMODE3),N3NCFL(NMODE3),
     &  I3DRCF(NDIAGR,NMODE3)
      COMMON /HWDSP3/A3MODE,B3MODE,P3MODE,WT3MAX,SPN3CF,ID3PRT,I3MODE,
     &  I3DRTP,N3MODE,NDI3BY,N3NCFL,I3DRCF
C--common block for four body decays
      DOUBLE PRECISION A4MODE(2,12,NMODE4),B4MODE(2,12,NMODE4),
     & P4MODE(12,12,NMODE4),WT4MAX(12,12,NMODE4)
      INTEGER ID4PRT(NMODE4),I4MODE(2,NMODE4),N4MODE
      COMMON /HWDSP4/A4MODE,B4MODE,P4MODE,WT4MAX,ID4PRT,I4MODE,N4MODE
C--common block for spin correlations in event
      INTEGER NDECSY,NSEARCH,LRDEC,LWDEC
      LOGICAL SYSPIN,THREEB,FOURB
      CHARACTER *6 TAUDEC
      COMMON /HWDSPN/NDECSY,NSEARCH,LRDEC,LWDEC,SYSPIN,THREEB,
     &  FOURB,TAUDEC
                                                                                                      
      INTEGER IDSPN(NMXSPN),JMOSPN(NMXSPN),JDASPN(2,NMXSPN),NSPN,
     &  ISNHEP(NMXHEP),NSNTRY,NCFL(NMXSPN),SPCOPT
      DOUBLE COMPLEX MESPN(2,2,2,2,NCFMAX,NMXSPN),RHOSPN(2,2,NMXSPN)
      DOUBLE PRECISION SPNCFC(NCFMAX,NCFMAX,NMXSPN)
      LOGICAL DECSPN(NMXSPN)
      COMMON /HWSPIN/MESPN,RHOSPN,SPNCFC,IDSPN,JMOSPN,JDASPN,
     &  NSPN,ISNHEP,NSNTRY,DECSPN,NCFL,SPCOPT
      INTEGER JAK1,JAK2,ITDKRC,IFPHOT
      COMMON /HWSTAU/ JAK1,JAK2,ITDKRC,IFPHOT
C
C--common block for Les Houches interface to store information we need
C
      INTEGER MAXHRP
      PARAMETER (MAXHRP=100)
      DOUBLE PRECISION LHWGT(MAXHRP),LHWGTS(MAXHRP),LHMXSM,
     &     LHXSCT(MAXHRP),LHXERR(MAXHRP),LHXMAX(MAXHRP)
      INTEGER LHIWGT(MAXHRP),ITYPLH,LHNEVT(MAXHRP)
      LOGICAL LHSOFT,LHGLSF
      COMMON /HWGUPR/LHWGT,LHWGTS,LHXSCT,LHXERR,LHXMAX,LHMXSM,LHIWGT,
     &     LHNEVT,ITYPLH,LHSOFT,LHGLSF
C
C--common block for HERWIG6.5
C
      LOGICAL PRESPL
      COMMON /HW6500/ PRESPL
      INTEGER ITOPRD
      INTEGER I
      COMMON /HW6504/ITOPRD
C--the only change for 6505 was to increase MODMAX from 5 to 50
      DOUBLE PRECISION PDFX0,PDFPOW
      COMMON /HW6506/PDFX0,PDFPOW
CCCCCC#include "hepevt.inc"
      INTEGER jput
      PARAMETER(jput=900000)
      INTEGER itest
      PARAMETER(itest=9000000)
        INTEGER isthp !  status code of the entry 0
        INTEGER idhp !  particle identity, accordingly to the PDG standard 0
        INTEGER jmohp !  pointer(s) to position where the mother(s) stored 0
        INTEGER jdahp !  pointers to position of the first/last daughter 0
         REAL*4 php !  p4 and mass (GeV) 0
         REAL*4 PPP 
         REAL*4 V
         REAL*4 vhp !  production vertex (mm) and time (mm/c) 0
         DIMENSION jmohp(2), jdahp(2)
         DIMENSION php(5),vhp(4),PPP(3),V(3)
CCCCCC#include "headpss.inc"
      real*4 PSSHEP,VSSHEP
      INTEGER INTRUN, JJJ
      COMMON/HEADPSS/PSSHEP(5),VSSHEP(4),INTRUN
      SAVE /HEADPSS/
      CALL HEPEvent('herwig',0,NHEP,0.0,0.,0.,0.,1.,1.,1.,1.)
       JJJ=0
       DO I=1,NHEP
       JJJ = JJJ + 1
        IF(I.EQ.NHEP) JJJ=-1
        isthp=isthep(I)
        idhp=idhep(I)
        IF(IABS(idhp).GT.itest) THEN
          IF(idhp.LT.0) THEN
            idhp=idhp+itest-jput
          ELSE
            idhp=idhp-itest+jput
          ENDIF
        ENDIF
        jmohp(1)=jmohep(1,I)
        jmohp(2)=jmohep(2,I)
        jdahp(1)=jdahep(1,I)
        jdahp(2)=jdahep(2,I)
        php(1)=phep(1,I)
        php(2)=phep(2,I)
        php(3)=phep(3,I)
        php(4)=phep(4,I)
        php(5)=phep(5,I)
        PPP(1)=php(1)
        PPP(2)=php(2)
        PPP(3)=php(3)
        vhp(1)=vhep(1,I)
        vhp(2)=vhep(2,I)
        vhp(3)=vhep(3,I)
        vhp(4)=vhep(4,I)
        V(1)=vhp(1)
        V(2)=vhp(2)
        V(3)=vhp(3)
        CALL HEPPart(JJJ,isthp,idhp,jmohp,jdahp
     1,PPP,php(4),php(5),V,vhp(4))
CCCCC        WRITE(12,*) NEVHEP,I,ISTHEP(I),IDHEP(I),JMOHEP(1,I),JMOHEP(2,I)
CCCCC     &,JDAHEP(1,I),JDAHEP(2,I),PHEP(1,I),PHEP(2,I),PHEP(3,I),PHEP(4,I)
CCCCC     &,PHEP(5,I),VHEP(1,I),VHEP(2,I),VHEP(3,I),VHEP(4,I)
      ENDDO
      RETURN
      END
      SUBROUTINE HWAEND
         CALL HEPEnd('  ')
      STOP
      END
 
