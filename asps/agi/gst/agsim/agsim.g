*CMZ :          13/07/98  10.50.50  by  Pavel Nevski
*-- Author :    Pavel Nevski
*****************************************************************************
*                                                                           *
      subroutine        A G M A I N
*                                                                           *
*****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCTIME.
      COMMON/GCTIME/TIMINT,TIMEND,ITIME,IGDATE,IGTIME
      INTEGER ITIME,IGDATE,IGTIME
      REAL TIMINT,TIMEND
C
*KEND.
*
      INTEGER           NWGEAN, NWGEA, NWPAW, NWPA
      PARAMETER        (NWGEAN= 8 000 000,    NWPAW=2 000 000)
      CHARACTER*240     BATCHF,PAWLOGF,PROG,COMD,ARG,VERSION,FATCAT
      INTEGER           AgIPAW,IwTYP
      COMMON /AgCIPAW/  AgIPAW,IwTYP
      INTEGER           LENOCC,ICDECI,Iprin,I,J,K,L,N,Nr/0/,Iv/0/,Na/0/,Irc
      CHARACTER*320     CHARGS
      COMMON /PCARGS/   CHARGS
      EXTERNAL          PAEXIT,UGLAST,AgPAWE
      INTEGER           ICSDEBUG
      COMMON /CSDEBUG/  ICSDEBUG
      LOGICAL           S,G
 
*     ON REAL UNDERFLOW IGNORE
*
      CALL TIMEST  (3.E7)  ! set time limit for interactive mode
      NWGEA = NWGEAN
      NWPA  = NWPAW
      CALL GETARG(0,PROG)
      I = 1
      N = LENOCC (PROG)
      DO J=1,N   { IF (PROG(J:J).EQ.'/') I=J+1; }
      VERSION = '       '
*     VERSION = PROG(I:N)
      FATCAT = ' '
      if (PROG(I:N)=='atlsim') CALL REBANKM(-1)
*
      do J=1,999
      {  CALL GETARG(J,comd);  Call CUTOL(comd)
         L=LENOCC(comd);       if (L<=0) Break
         if comd(1:2)=='-h'
         { print *, ' usage: '//prog(i:n)     _
                 // ' [ -V version]'          _
                 // ' [ -w HIGZ_UNIT ]'       _
                 // ' [ -l login_kumac]'      _
                 // ' [ -b batch_kumac]'      _
                 // ' [ -D debug_level]'      _
                 // ' [ -S STAF_size(Mw)]'    _
                 // ' [ -P PAWC_size(Mw)]'    _
                 // ' [ -G GCBANK_size(Mw)]'  _
                 // ' [ -f fatmen_catalog  ]' _
                 // ' [ -n(o login_kumac)]'   _
           ; return
         }
         if comd(1:1)='-'
         { Na+=1;  Nr=1;  Arg=' ';  CALL GETARG(J+1,Arg);
           K=Lenocc(arg);   If (K>0) Nr=ICDECI(arg,1,K);
           If (comd(1:2)='-v') { if (LenOCC(arg)>0) VERSION = arg; Iv=1 }
           If (comd(1:2)='-d') { IDEBUG = Nr;  ICSDEBUG=Index(Arg,'c')  }
           If (comd(1:2)='-g') NWGEA   = max(0,Nr)*1000000
           If (comd(1:2)='-p') NWPA    = max(0,Nr)*1000000
           If (comd(1:2)='-f') FATCAT  = Arg
      }  }
      CALL CUTOL(VERSION)
      S = Version.ne.'gstar'
      G = Version.ne.'staf'
*
      write (*,1001) PROG(I:N),NWGEA,NWPA
1001  format(1x,54('*')/' * Starting ',a8,
     >       ' NwGEANT=',i9,' NwPAW=',i8,' *'/ 1x,54('*'))
*
      IPRIN = -3
      IF (IDEBUG>2) IPRIN=-1
*                                        initialise packages
      CALL MZEBRA  (IPRIN)
      CALL GZEBRA  (NWGEA)                      ! store 0 - geant
      CALL MZPAW   (NWPA,' ')                   ! store 1 - pawc
 
      CALL PAWINT1 (PROG(I:N),BATCHF,PAWLOGF)
      CALL PAWINT2 (0,'+?',AgPAWE,IWTYP)  ! type of PAW, HBOOK, command
      CALL FMLOGL  (-3)
      IF (LENOCC(FATCAT)>0) CALL FMSTRT(62,63,%L(FATCAT),Irc)
 
      if (G) CALL GINTRI            ! Geant MENUs and COMMANDs
*
      IF (IWTYP.EQ.999) THEN        ! motif zebra browser
         CALL PMINIT                ! Paw-Motif
         CALL GBROWS                ! Geant Browser
         CALL KUINIM (PROG)         ! Kuip-Motif
      ELSE
*        CALL ZBRDEF                ! zebra menu  (p.248)
      ENDIF
*
      CALL PAWINT3                  ! HIGZ,HPLOT,COMIS,SIGMA, commons
      if (G) CALL GXCS              ! declare GEANT routines to COMIS
      if (G) CALL UGINIT (PROG)     ! user MENUs
      if (G) CALL GDINIT            ! Initialise Drawing pkg
      CALL TIMEL  (TIMINT)
 
      if (PROG(I:N)!='staf' | Version!=' ')  Call AgVERSION
      if (G) Call KUEXEC('ROOT /GEANT')
      if (S) Call staf_start
****>
      CALL KUEXEC  ('SET/PROMPT '''//PROG(I:N)//' >''')
*
      NOLOG = LENOCC(PAWLOGF).le.0
      CALL PAWINT4 (PAWLOGF)
      BATCH = LENOCC(BATCHF).gt.0
      IF (BATCH) CALL PAWINT4(BATCHF)
*
      Call AgPAWQ
****>
      if (S) call staf_stop
      WRITE(*,'(/1x,a)') 'Exiting from '//PROG(I:N)
      if (G) Call UGLAST
      CALL PAEXIT
      :return:
      END
 
      subroutine  AgPAWQ
      COMMON /AgCIPAW/  AgIPAW,IwTyp
      AgIPAW = AgIPAW + 1
 
      if (IwTYP.EQ.999) then
        Call KuWham ('PAW++')
      else
        call KuWhag
      endif
      entry       AgPAWE
      end
*
 
 
*CMZ :          13/07/98  10.44.40  by  Pavel Nevski
*CMZ :  1.30/00 13/05/97  14.57.05  by  Pavel Nevski
*-- Author :    Pavel Nevski   10/07/96
      SUBROUTINE AGVERSION
character*36 cmon/'JanFebMarAprMayJunJulAugSepOctNovDec'/
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcvers.
      COMMON /AGCVERS/IDATQQ,ITIMQQ,IVERSQ,VERSQQ,QFTITLCH
      INTEGER         IDATQQ,ITIMQQ,IVERSQ
      CHARACTER       VERSQQ*8,QFTITLCH*60
*     - - - - - - - - - - - - - - - - - - - -
*KEEP,VIDQQ.
      CHARACTER*68 VIDQQ
      DATA VIDQQ/
     +'@(#)Advanced Geant Inteface               C: 08/08/98  23.37.20
     +'/
*KEEP,DATEQQ.
      IDATQQ =   980808
*KEEP,TIMEQQ.
      ITIMQQ =   2337
*KEEP,VERSQQ.
      VERSQQ = ' '
      IVERSQ = -1
*KEND.
     QFTITLCH=VIDQQ(5:60)
     id=mod(IDATQQ,100);  im=3*mod(IDATQQ/100,100);  iy=IDATQQ/10000;
 <w>;(' ********************************************************************')
 <w>;(' *                                                                  *')
 <w>;(' *        A D V A N C E D   G E A N T   I N T E R F A C E           *')
 <w>;(' *                                                                  *')
*<w>;(' *                      04-Sep-97 hot news:                         *')
 <w> id,cmon(im-2:im),iy; (' *',22x,i2.2,'-',a3,'-',i2.2,' hot news:',25x,'*')
 <w>;(' *                                                                  *')
*<w>;(' * 20-Jul-97, MAJOR update! Remove all sl files prior to this date  *')
*<w>;(' *                                                                  *')
 <w>;(' * Kuip command "ON ERROR GOTO label" will now react on:            *')
 <w>;(' *      - End_of_DATA on P stream, Write_Error on O stream          *')
 <w>;(' *      - time_left less than defined by GTIME command argument     *')
*<w>;(' * On GHIST command some standard histogram handling is introduced  *')
*<w>;(' *        with automatic histogram dump when EXITing AGI.           *')
*<w>;(' * Binning refined: - for BIT option all 2**Nbit values are used,   *')
*<w>;(' *                    unknown elements are supposed to be integer   *')
*<w>;(' *                  - for BIN option the interval is centered       *')
*<w>;(' * To get robust tracking in MANY volumes use ISWIT(10) value > 0   *')
*<w>;(' * Electron physics (Bremsstraghlung, Pair production) updated      *')
*<w>;(' * Print control is now fully consistent with SLUG-DICE-ATRECON     *')
 <w>;(' * Explicit NCOPY parameter is now allowed in the POSITION operator *')
*<w>;(' * Protection against errenious hit limits (bug in GFIPAR on SUN)   *')
*<w>;(' * RbGET counting request now returns again the correct number      *')
*<w>;(' *       of banks in a chain, as it is described in SOFT-NO-002     *')
 <w>;(' * USE operator has an OPERation NEXT, allowing bank chain scanning *')
 <w>;(' * "-b filename" option now available for batch mode.               *')
*<w>;(' * CERNLIB 97a release is now the default library version.          *')
*<w>;(' * Be aware that it requires the FILL attribute to be 0, otherwise  *')
*<w>;(' * edges drawn in black/white obscure most of the GEANT drawings !  *')
 <w>;(' *                                                                  *')
 <w>;(' * Absorption length calculation for mixtures corrected in GEANT.   *')
 <w>;(' * CMZ KEEP sequences (car-format) are recognised as REPLACE macros *')
 <w>;(' *                                                                  *')
 <w>;(' * GEANT memory may be increased at the program invocation time -   *')
 <w>;(' * start with -h option to get more information how to use switches *')
 <w>;(' *                                                                  *')
 <w>;(' * Tracking in MANY volumes is corrected - no missing hits anymore  *')
 <w>;(' *                                                                  *')
 <w>;(' * GENZ package added - LGNFIND,GNZGET* calls are available         *')
 <w>;(' *                                                                  *')
 <w>;(' *           FOR MORE DETAILS PLEASE USE HELP FACILITY              *')
 <w>;(' *                                                                  *')
 <w>;(' * To get complete description of AGI commands in printable format  *')
 <w>;(' *              do:  MANUAL AGUSER MAN.TEX LATEX                    *')
 <w>;(' ********************************************************************')
      end
 
 
*CMZ :          30/12/97  11.59.38  by  Pavel Nevski
*CMZ :  1.30/00 17/04/97  20.55.24  by  Pavel Nevski
*-- Author :    Pavel Nevski   27/11/94
*****************************************************************************
*                                                                           *
             Subroutine   U G I N I T (C)
*                                                                           *
*            GEANT Initialization Sequence                                  *
*****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
      INTEGER IPAIR,ICOMP,IPHOT,IPFIS,IDRAY,IANNI,IBREM,IHADR,IMUNU
     +       ,IDCAY,ILOSS,IMULS,IRAYL,ILABS,ISYNC,ISTRA
      REAL    SPAIR,SLPAIR,ZINTPA,STEPPA,SCOMP,SLCOMP,ZINTCO,STEPCO
     +       ,SPHOT,SLPHOT,ZINTPH,STEPPH,SPFIS,SLPFIS,ZINTPF,STEPPF
     +       ,SDRAY,SLDRAY,ZINTDR,STEPDR,SANNI,SLANNI,ZINTAN,STEPAN
     +       ,SBREM,SLBREM,ZINTBR,STEPBR,SHADR,SLHADR,ZINTHA,STEPHA
     +       ,SMUNU,SLMUNU,ZINTMU,STEPMU,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +       ,SLOSS,SOLOSS,STLOSS,DPHYS2,SMULS,SOMULS,STMULS,DPHYS3
     +       ,SRAYL,SLRAYL,ZINTRA,STEPRA,SLABS,SLLABS,ZINTLA,STEPLA
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     CHARACTER C*1
     Integer  p/0/
     EXTERNAL CSRMSL,AGDROP
*
     CALL GINIT                   "  GEANT common blocks                "
     CALL GZINIT                  "  GEANT core divisions, link areas,  "
     CALL AGZINI                  "  specific ZEBRA initialization      "
*    CALL GFFGO                   !  READ data cards within GEANt
     CALL GPART                   "  Define standard particles          "
     CALL GMATE                   "  Initialize standard materials      "
     Call CSEXT ('CSRMSL,AGDROP,p',CSRMSL,AGDROP,p,p,p,p,p,p,p,p)
     Call CSFILE('0.csl')         "  Make all AGI routines callable     "
     DPHYS1      = 0              "  oshibku oshibkoi vybivaiut         "
     %Standalone = 1              "  standalone version, not batch      "
     %IGRAP      = -1             "  no default graphic, on request only"
     IGAUTO      = 0              "  defaults GEANT tracking  off       "
     CrunType    = ' '            "  no default actions defined         "
     NkineMax    =  64 000        "  ZEBRA limit on KINE bank           "
     NhitsMax    = 100 000 000    "  a reasonable limit on hit bank     "
*    Call GUINTI                     gsuser menu - called by geant      "
     Call AGXINIT                 "  aguser menu - called here          "
     %Module=' ';  call Agstand
     Call AgDummy
*
END
 
 
*CMZ :          21/11/97  17.47.13  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  22.56.51  by  Pavel Nevski
*-- Author :    Pavel Nevski   27/11/94
*********************************************************************
                Subroutine   U G L A S T
*********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
    Integer      ICYCLE
    Character*10 CTOP
 
    IF IUHIST>0
    { CTOP='//'//CDHIST;  <w> CTOP,CFHIST;
      (' Saving Histograms from ',a,' to ',a)
      CALL  RZCDIR(CTOP,' ');
      CALL  HCDIR('//PAWC','  ');    CALL HCDIR(CTOP,' ');
      CALL  HROUT(0,ICYCLE,'NT');    Call HREND(CTOP)
      If (Idebug>0) Call HLDIR('//PAWC','TSIA')
      CLOSE (IUHIST);    IUHIST=0
    }
    * Call RZCLOS(' ','A')
    If (Ioutp!=0) Call FZENDO(23,'TX')
    Call GLAST
    " STOP "
    END
 
 
*CMZ :          05/08/98  23.31.34  by  Pavel Nevski
*CMZ :  1.30/00 23/04/97  18.45.29  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/04/96
*********+*********+*********+*********+*********+*********+*********+*********+
*                                                                              *
      SUBROUTINE AGXUSER
* Description:  define AgI KUIP command repertoire                             *
*********+*********+*********+*********+*********+*********+*********+*********+
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
      INTEGER IPAIR,ICOMP,IPHOT,IPFIS,IDRAY,IANNI,IBREM,IHADR,IMUNU
     +       ,IDCAY,ILOSS,IMULS,IRAYL,ILABS,ISYNC,ISTRA
      REAL    SPAIR,SLPAIR,ZINTPA,STEPPA,SCOMP,SLCOMP,ZINTCO,STEPCO
     +       ,SPHOT,SLPHOT,ZINTPH,STEPPH,SPFIS,SLPFIS,ZINTPF,STEPPF
     +       ,SDRAY,SLDRAY,ZINTDR,STEPDR,SANNI,SLANNI,ZINTAN,STEPAN
     +       ,SBREM,SLBREM,ZINTBR,STEPBR,SHADR,SLHADR,ZINTHA,STEPHA
     +       ,SMUNU,SLMUNU,ZINTMU,STEPMU,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +       ,SLOSS,SOLOSS,STLOSS,DPHYS2,SMULS,SOMULS,STMULS,DPHYS3
     +       ,SRAYL,SLRAYL,ZINTRA,STEPRA,SLABS,SLLABS,ZINTLA,STEPLA
C
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCLIST.
      COMMON/GCLIST/NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     +       ,NSTAT,LHSTA(20),LGET (20),LSAVE(20),LSETS(20),LPRIN(20)
     +             ,LGEOM(20),LVIEW(20),LPLOT(20),LSTAT(20)
C
      INTEGER       NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     + ,NSTAT,LHSTA,LGET ,LSAVE,LSETS,LPRIN,LGEOM,LVIEW,LPLOT,LSTAT
C
*KEEP,asflags.
      INTEGER      NFLAGS
      PARAMETER    (NFLAGS=15)
      CHARACTER*4  CFLAG(NFLAGS)
      DATA CFLAG   /'PNOW','PRIN','DEBU','GEOM','HIST','GRAP',
     >              'SIMU','DIGI','RECO','MFLD','ANAL','BACK',
     >              'RESA','RESB','RESC'/
*    ---------------------------------------------------------
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
     character     command*32,Cword*4,C*1
     character*256 string1,string2,string3
     integer       LENOCC,CSADDR,SYSTEMF,
                   Npar,Len1,Len2,Len3,Ip,Kp,Jp,L1,L,i,j,K,i0,j0,id,
                   id1,id2,address,JAD,IAD,Ival,Ier,Iprin/1/,Li/20/
     Character*160 source,      destin,      mname,     library
     data          source/' '/, destin/' '/, mname/' '/,library/' '/
     Real          PAR(1000),Rval,dummy1,dummy2
*    force string1,2 at word boundary - comis pass whole words only
     EQUIVALENCE  (string1,dummy1),(string2,dummy2)
*    reset comis error (PAWFCA ... symbol not found ...)
     Integer         ii
     common /hcbits/ ii(37)
*
  call KUPATL( command, npar )
  Iprin=Idebug;  Ncommand+=1;
 
  if command=='GDUMP' | command=='DUMP'
  {  " dump a sub-tree of banks "
     call kugetc (string1,Len1)
     call kugetc (string2,Len2)
     Call AgDUMP (string1(1:Len1),0,string2(1:Len2))
  }
  else If Command=='GFILE'
  {  " open an I/O: file stream request"  Ccommand=' '
     Call KUGETC(string1,len1);
     Call KUGETS(string2,len2);
     Call KUGETC(string3,len3);         C='P'
     IF (Index(String1(1:len1),'B')>0)  C='B'
     IF (Index(String1(1:len1),'O')>0)  C='O'
     If (string2(1:len2)=='ZEBRA')  { String2='ZEBRA.'//C; Len2=7; }
     Do i=4,Npar { Call KUGETI(PAR(i-3)) }
 
     If  Index(String1(1:len1),'U')>0
     {  { Ikine,IkineOld }=-5;  CoptKine=string3;
        call AgFOPEN(li,string2(1:len2),ier)
        Address=CsADDR('AgUSOPEN')
        L1 = 4*((len2+3)/4)
        If (address>0) CALL CsJCAL1S(address,string2(1:L1))
     }
     else If Index(String1(1:len1),'N')>0
     {  Call AgNTOpen(String2(1:len2),4) }
     else
     {  Call AgZOPEN(string1(1:len1),string2(1:len2),string3(1:len3),
                                                          Npar-3,PAR)
        IF (Index(String1(1:len1),'P')>0)  Call AGZREAD ('P',ier)
        IF (Index(String1(1:len1),'B')>0)  Call AGZREAD ('B',ier)
        IF (Index(String1(1:len1),'O')>0)  Call AGZWRITE('O',ier)
     }
     If (Index(String3(1:Len3),'S')>0 | String3(1:1)='*') _
                                      Call AGKEEPS(' ','def')
  }
  else If Command=='GHIST' | Command=='HFILE'
  {  " open a histigram file
     Call KUGETS(string1,len1); CFHIST=string1(1:len1)
     Call KUGETC(string2,len2); CDHIST=string2(1:len2)
     Call KUGETI(IUHIST)
     Call HROPEN(IUHIST,CDHIST,CFHIST,'N',1024,IVAL)
     prin1 %L(CDHIST),%L(CFHIST),IUHIST
     (' Creating RZ-directory ',a,' for histogram file ',a,' on unit ',i3)
  }
  Else If Command=='GRFILE'
  {   Call KugetS (String1,len1)
      Call KUGETC (String2,len2)
      Call KUGETI (ID)
      call agrfile(ID,String1(1:len1),String2(1:len2))
  }
  else If Command=='ACTIONS'
  {  Call KUGETC(string1,len1);  CRunType=string1(1:len1)
     prin1 CrunType; (' Allowed actions: ',a)
  }
  else If Command=='VERSIONS'
  {  Call KUGETC(string1,len1);
     IF (String1(1:4)=='RZ95')  { prin1; (' RZ format 95 '); IQUEST(99)=0  }
     IF (String1(1:4)=='RZ96')  { prin1; (' RZ format 96 '); IQUEST(99)=96 }
     IF (String1(1:5)=='ATLAS') { prin1; (' rebank old');  call REBANKM(-1); }
     IF (String1(1:4)=='STAF')  { prin1; (' rebank new');  call REBANKM( 0); }
     IF (String1(1:5)=='DENSE') { prin1; (' rebank dens'); call REBANKM(+1); }
  }
  else If Command=='GKINE' | Command=='PHASESPACE' _
        | Command='GMOMENTUM' | Command=='MOMENTUMBIN'
  {  " Flat phase space generation - old KINE card function "
     " Ntracks=" call KUGETI(Ikine);  "Ipart=" call KUGETI(ip);
     " get all other parameters - Pt,eta,phi,z limits "
     Do i=2,min(Npar-2,8),2
     { " historical order - may disappear sometime "
       j=i; If (i==8) j=9;
       call KUGETR(pkine(j));  call KUGETR(pkine(j+1))
       pkine(j+1) = max(pkine(j),pkine(j+1))
     }
*    Ival=2 means not only fix pT, but also Geant particle code rather then PDG
     Ival=2; If Npar>=9       " get GEANT/PDG PID switch "
     {  Call KUGETC(string2,len2); C=String2(1:1)
        If C=='E' {Ival=0} else If C=='P' {Ival=1}
     }
     If Ikine>=0
     {  " check to see if particle exists: "
        Kp=Ip; If (Ival<2) Call aPDG2GEA(IP,Kp)
        Jp=0;  If (1<=Kp&Kp<=Npart) Jp=LQ(Jpart-Kp)
        if Jp<=0 { <w> ip; (' AGXUSER: unknown particle id =',i6); Return; }
        Call UHTOC(IQ(JP+1),4,string1,20);  Len1=LENOCC(string1(1:20))
        Prin1 Ikine,string1(1:len1);
        (' Generating ',i5,2x,a,' events in interval:')
     } else
     {  prin1 Ip;
        (' reading events with following cuts (skipping ',i5,' events)')
     } Pkine(1)=IP
*
     If Command=='GKINE' | Command=='PHASESPACE' _
     {  If Ival==0 { Prin1 (pkine(i),i=2,3); ( 10x,f8.2, ' <  E  < ', f8.2) }
        else       { Prin1 (pkine(i),i=2,3); ( 10x,f8.2, ' < pT  < ', f8.2) }
        Prin1 (pkine(i),i=4,7),(pkine(i),i=9,10)
          ( 10x,f8.2, ' < eta < ', f8.2,
           /10x,f8.3, ' < phi < ', f8.3,
           /10x,f8.1, ' <  Z  < ', f8.1)
        Pkine(8)=Ival
     }  else
     {  Prin1 (pkine(i),i=2,7),(pkine(i),i=9,10)
          ( 10x,f8.2, ' < px  < ', f8.2,
           /10x,f8.2, ' < py  < ', f8.2,
           /10x,f8.2, ' < pz  < ', f8.2,
           /10x,f8.1, ' <  Z  < ', f8.1)
        Pkine(8)=Ival+10
     }
  }
  else if Command=='GBACK'
  {  Iback=-1;             Call KUGETI(IbBefor); Call KUGETI(IbAfter);
     Call KUGETR(BgMUlt);  Call KUGETR(BgTIME);  Call KUGETR(BgSKIP);
     prin1 IbBefor,IbAfter,BgMult,BgTime,BgSkip;
     (' Reading Background from ',i3,' to ',i3,' pile-up bunchs '/,
      ' with ',F5.1,' events in average, ',F5.1,' ns between them.'/,
      ' Average Randomizing skip ',F5.1,' events')
  }
  else If Command=='GVERTEX'
  {" set up the vertex position "
     AvFLAG=1;     Do I=1,Npar { CAll KUGETR(AVcoor(i)); }
     Prin1 Avcoor; (' AGXUSER: generating vertex at ',3f12.4)
  }
  else If Command=='GSPREAD'
  {" set up the vertex position "
     AvFLAG=1;     Do I=1,Npar { CAll KUGETR(AVsigm(i)) }
     Prin1 AVsigm; (' AGXUSER: generating vertex spread ',3f9.4)
  }
  else If Command=='GDROP' | Command=='DROP'
  {" drop selected bank tree "
     Call KUGETC(String1,Len1); Call AGDROP(String1(1:len1));
  }
  else If Command=='GMODE' | Command=='MODE'
  {" detector mode datacard  "
     Call KUGETC(String1,Len1); Cword=String1(1:len1);
     If Cword=='ALL'  { ID1=1; ID2=0; IF (LKDETM>0) ID2=IQ(LKDETM-2); }
     else             { Call AsBDETE(Cword,ID1);    ID2=ID1;          }
     Do i=2,Npar-1,2
     {  Call KUGETC(String2,Len2); Cword=String2(1:len2); Call KUGETI(IVAL)
        Do j=1,NFLAGS
        { Check Cword==CFLAG(j); Do ID=ID1,ID2
          { If (LQ(LKDETM-ID)>0) IQ(LQ(LKDETM-ID)+j)=IVAL; }
     }  }
     Do ID=ID1,ID2
     { Check LQ(LKDETM-ID)>0;
       Prin1 IQ(LKDETM+ID),(Cflag(j),IQ(LQ(LKDETM-ID)+j),j=1,Nflags)
                  (1x,A4,' mode:',15(1x,a4,i2))
  }  }
  Else If Command=='DETP' | Command=='GPAR'
  {" detector parameters in DETM bank "
      Call KUGETC(string1,len1); Cword=string1(1:4)
      Call AsBDETE('DOCU',ID);   Call AsBDETE(Cword,ID);
      j=2;  string2=' ';   Len2=0;  Len3=0;
      Do i=2,Npar
      { * awful coding, may be sometime will do it better. PN.
         :more:       string1=string2; Len1=Len2;
         if Len3==0 { Call KUGETS(string2,len2);  }
         else       { string2=string3; Len2=Len3; }
         Call KUDPAR(string2,Ival,Rval,string3,len3,C);
         Len3=0
         if C=='C'
         {  i0=INDEX(string2,'=')
            if 0<i0 & i0<len2
            { string3=string2(i0+1:len2);  Len3=Len2-i0
              string2=string2(1:i0);       Len2=i0
            }
            If i0==1 & len2==1   " = "
            { string2=string1(1:len1)//'=';     j=j0; len2=len1+1;   }
            Call UCTOH(string2,PAR(j),4,len2);  j0=j; j+=(len2-1)/4+1;
            If J>=1000 { print *,' Tooooo many input parameters !!!'; Break; }
         }
         If C=='R'  { PAR(j)=Rval;  J+=1; }
         If C=='I'  { PAR(j)=Ival;  J+=1; }
         prin2 C,string2(1:len2),len2; (' DETP input: ',a,' = ',a,i6)
         If (Len3>0) goto :more:
      }  Call AsLSETBA(CWORD,'DETP',j-1,PAR)
      if (id>0) Call MZFLAG(IxCons,LQ(LkDetm-id),1,'Z')
  }
  Else If Command=='GFLAG' | Command=='GSFLAG'
  {" all possible subsystem control flags "
     Do i=1,Npar-1,2
     {  Call KUGETC(string1,len1);  Call KUGETI(Ival);
        Call AgSFLAG(string1(1:len1),Ival)
        Prin1 string1(1:len1),Ival; (' Flag ',a,' set to ',i3)
  }  }
  Else If Command=='GDEBUG'
  {" make hard debugging level available "
     Call KUGETI (Idebug);          Call KUGETI (Itest)
  }
  Else If Command=='GCLOSE'
  {" close geometry and possible recalculate cross-sections"
     Call GGCLOS;
*    hide gphysi table in this case in a file - done inside agphysi
*    Ival=Lout;  If (Idebug==0) Lout=99;
     If (Npar>0) Call AGPHYSI
*    Lout=Ival
  }
  Else If Command=='GAUTO'
  {" set geant IGAUTO flag (does not work in GEANT yet)"
     Call KUGETC(string1,len1);
     If string1(1:2)=='ON' | string1(1:1)='1' {IGAUTO=1} else {IGAUTO=0}
     prin1 IGAUTO; (' IGAUTO flag set to ',i2)
  }
  Else If Command=='GSTOP'
  {" stopping electron control "
     Call KuGETI(Ival);  DPHYS1=Ival;
     prin1 Ival;   ('  stopping electron mode=',i2)
  }
  Else If Command=='GPRINT'
  {" different object print out - to be improved later "
     Call KUGETC(string1,len1); cword=string1(1:len1)
     If cword='PART' | cword='MATE' | cword='TMED' | cword='ROTM' _
      | cword='SETS' | cword='VERT' | cword='KINE' | cword='JXYZ' _
     {  IP=0;  if (Npar>1) CALL KUGETI(IP);  call GPRINT(Cword,IP)  }
     else If cword='DECA'|cword='DCAY'
     {  IP=0;  if (Npar>1) CALL KUGETI(IP);  call GPDCAY(IP)        }
     else If cword='HITS'|cword='DIGI'
     {  Call KuGETC(string1,len1); Call KuGETC(string2,len2)
        if (string1!='*') string1=string1(1:3)//Cword(1:1)
        call AgPDIGI(string1,string2)
     }
     else If cword='VOLU' & JVOLUM>0
     {  Call KuGETC(string1,Len1); Do I=1,NVOLUM
        {  Call UHTOC(IQ(LQ(JVOLUM-I)-4),4,String2,4)
           If (String1=='*' | String1(1:4)==string2(1:4)) Call GPVOLU(I)
     }  }
  }
  Else If Command=='GPHITS' | Command=='GPDIGI'
  {  Call KuGETC(string1,len1); Call KuGETC(string2,len2)
     if (string1!='*') string1=string1(1:3)//Command(3:3)
     call AgPDIGI(string1,string2)
  }
  Else If Command=='GEXEC'
  {  * PN, 04.03.98:  make it case sensitive
     Call KuGetS(string1,len1); " Call CUTOL(string1(1:Len1)) "
     If (Npar>1) Call KuGetS(Library,len2)
     L=Len1; K=1; DO i=Len1,1,-1
     { if (string1(i:i)=='.')   L=i-1
       if (string1(i:i)=='/') { K=i+1; Break; }
     }
*    call to csrmsl is needed to free the sl file before compilation
     If LENOCC(Source)+LENOCC(Destin)==0
     {  Call CSRMSL(String1(1:L));         CALL PAWCS;
        II(4)=0;
        IQUEST(1) = SystemF('make '//string1(1:L)//'.sl')
        CALL  PAWFCA(string1(1:L)//'.csl',L+4,JAD,Idebug)
        Prin1  'make '//string1(1:L)//'.sl';  ('gexec: ',a)
     }
     else
     {  Call CSRMSL('sl/'//String1(K:L));  CALL PAWCS;
        II(4)=0;
        Prin1       'gmake '//%L(mname)//                      _
                    ' INP_DIR='//%L(Source)//'/'//%L(string1)//_
                    ' '//%L(library)
                    ('gexec: ',a)
        IQUEST(1)=SystemF('gmake '//%L(mname)//                _
                    ' INP_DIR='//%L(Source)//'/'//%L(string1)//_
                    ' '//%L(library))
        CALL PAWFCA('sl/'//string1(K:L)//'.csl',L-K+8,JAD,Idebug)
     }
 
     if (JAD!=0) Call Ami_Module_Register (string1(K:L))
     IAD=CsADDR(string1(K:L)//'_init')
     IF  IAD!=0       " staf module - init and possibly start it "
     {  CALL CSJCAL(IAD,0, 0,0,0,0,0, 0,0,0,0,0)
        JAD=CsADDR(string1(K:L)//'_start')
     }
     if (JAD!=0)   CALL CSJCAL(JAD,0, 0,0,0,0,0, 0,0,0,0,0)
  }
  Else If Command=='GMAKE'
  {  Call KuGetS(source,len1)
     if (Npar>1) { Call KuGetS(string2,len2); mname = ' -m '//string2 }
     if (Npar>2) { Call KuGetS(library,len3);                         }
  }
  Else If Command=='GSTAT'
  {  DO i=1,Npar
     {  CALL KUGETC(string1,Len1)
        IF String1(1:Len1)=='ALL' | String1(1:len1).EQ.'*'
        {  NHSTA=5;  CALL UCTOH('TIMESIZEMULTNTRASTAK',LHSTA,4,20); }
        else
        {  NHSTA=i;  CALL UCTOH(String1,LHSTA(i),4,4); }
     }
     CALL GBHSTA; prin1 NHSTA,(LHSTA(i),i=1,NHSTA)
     (I5,' standard GEANT histogram activated:',10(1x,a4))
  }
  Else If Command=='STRUCTURES'
  {   Call KuGetS (string1,len1); Call KuGetS (string2,len2);
      Call AGKEEPS(string1(1:len1), string2(1:len2));
  }
  Else If Command=='TABLES'
  {   Call KuGetS (string1,len1); Call KuGetS (string2,len2);
      Call AGSTRUT(string1(1:len1), string2(1:len2));
  }
  Else If Command=='TABCLEAR'
  {   Call KuGetS (string1,len1);
      Call TDM_CLEAR_ALL(string1(1:len1)//char(0))
  }
  Else If Command=='ONFAULT'
  {   Call KugetC  (String1,len1); Call KugetI (L1);
      Call KugetC  (String2,len2);
      Call Onfault (String1(1:Len1),L1,String2(1:len2))
  }
  Else If Command=='ABEND'
  {   call ABEND; }
  else
  { print *,' AGXuser: Unknown Command - ',command(1:lenocc(command)),
            ', Npar = ',Npar
  }
*
  end
 
 
*CMZ :          05/08/98  16.29.34  by  Pavel Nevski
*CMZ :  1.30/00 15/04/97  19.40.26  by  Pavel Nevski
*-- Author :    Pavel Nevski   18/03/97
************************************************************************
      SUBROUTINE QNEXT
*                                                                      *
* Description:    Process events, protected against ZEBRA faults       *
* Modifications:  Clear ZEBRA storage after memory fault   PN 01/04/97 *
************************************************************************
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCTIME.
      COMMON/GCTIME/TIMINT,TIMEND,ITIME,IGDATE,IGTIME
      INTEGER ITIME,IGDATE,IGTIME
      REAL TIMINT,TIMEND
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,MZCA, IF=QTRHOLL.
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
      REAL    TIMNOW/0/
      INTEGER IDEBAG/0/,TRIG/0/,AgPHASE
      COMMON /AgCPHASE/ AgPHASE
*
         TRIG      = TRIG + 1
         IQUEST(1) = 1
         CALL ZPHASE(1)
*
         DO WHILE (IEVENT<NEVENT)
            IQUEST(1)= 0
            IEORUN   = 0
            NQTRAC   = 0
            NQERR    = 0
            AgPHASE  = 1
 
*          due to the chaining of RAW data, drop the first one (if it is there)
            If (LKARAW>0) then
               IQ(LKARAW-5) = 0
               CALL MZDROP(IxSTOR,LKARAW,'.')
               If (LKARAW.GT.0) IQ(LKARAW-5) = 1
            Endif
*           clean up memory - fully or partially
            If (LKARAW.EQ.0) CALL GTRIGC
            If (LKARP1.GT.0) CALL MZDROP(IxSTOR,LKARP1,'L')
            If (JHEAD.GT.0)  CALL MZDROP(IxSTOR,JHEAD,'L')
*
            CALL TIMEL(TIMNOW)
*          Check time left for non-splitted events
            IF (NtrSubEV.le.0 .or. IsubEVNT.ge.NsubEvnt) then
            IF (ITIME.GT.0 .and. TIMNOW.LE.TIMEND) Then
               WRITE(CHMAIL,10001) TIMEND
10001          FORMAT(' ***** THE JOB STOPS NOW because the TIME',
     >                ' left is less than ',F12.3,' seconds *****')
               CALL GMAIL(0,1)
               IQUEST(1) = 1
               GO TO 19
            ENDIF
            ENDIF
*
*              initialise event counters
            IEVENT=IEVENT+1
            IDEBAG=IDEBUG
            CALL GTRIGI
            IDEBUG=max(IDEBUG,IDEBAG)
            CALL GRNDMQ(IQ(JRUNG+19),IQ(JRUNG+20),0,'G')
            IQ(JRUNG+29)=IEVENT
*              Normal GEANT simulations (GTREVE) or RAW DATA here
            If (LKARAW.EQ.0) then
               CALL GTRIG
            else             !  very special case - test beam data
               CALL AgBEAMdat
               Call GUOUT
            endif
            CALL GFHSTA
            Call GRLEAS(JHITS)
            If (JKINE>0) Call ZSORTI(IxSTOR,JKINE,-5)
            If (JHITS>0) Call ZSORTI(IxSTOR,JHITS,-5)
*
            IF(IEORUN.NE.0) Then
               WRITE(CHMAIL,10002) TIMNOW
10002          FORMAT(' ***** THE JOB STOPS NOW because the IEORUN',
     >                ' flag set by user, Time left is ',F12.3,' *****')
               CALL GMAIL(0,1)
               IQUEST(1) = 1
               GO TO 19
            ENDIF
*
            IF(IQUEST(1).NE.0) Then
               WRITE(CHMAIL,10003) TIMNOW
10003          FORMAT(' ***** THE JOB STOPS NOW because the IQUEST',
     >             ' flag set by program, Time left is ',F12.3,' *****')
               CALL GMAIL(0,1)
               IEORUN = 1
               GO TO 19
            ENDIF
         ENDDO
 
  19     Nevent  = Ievent
         TRIG    = 0
         AgPHASE = 0
 
      END
 
 
*CMZ :  1.30/00 27/11/96  15.51.58  by  Pavel Nevski
*-- Author :    Rene Brun
      SUBROUTINE GDEBUG
************************************************************************
*             Standard GEANT debug                                     *
*          ==>Called by : <USER>,GUSTEP                                *
************************************************************************
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEND.
*
*             Debug/plot event
            IF (IDEBUG=0) Return
*
C.      Store space point VECT in banks JXYZ
        IF (ISWIT(2)=1 | ISWIT(2)=4 | ISWIT(3)=1)  Call GSXYZ
 
C.      Print track and volume parameters at current point
        IF (ISWIT(2)=2)                            Call GPCXYZ
 
C.      Print kinematics of secondary tracks at the current interaction point
        IF (ISWIT(1)=2)                            Call GPGKIN
 
C.      Online display of the track trajectory
        IF (ISWIT(2)=3) then
           IF(ISWIT(4)=3 & CHARGE=0) RETURN
                                                   Call GDCXYZ
                                                   Call IGSA(0)
        ELSE IF(ISWIT(2)=4) THEN
C.      Store space point VECT in banks JXYZ
           IF(ISTOP.NE.0)                          Call GDTRAK(' ')
        ENDIF
*
      END
 
 
*CMZ :  1.30/00 17/07/96  15.57.39  by  Pavel Nevski
*-- Author :    A. Rozanov  11/03/95
***************************************************************************
*                                                                         *
                Subroutine  G U K I N E
*                                                                         *
* Description: Read or Generate Kinematics for primary tracks             *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEND.
        Call AgZKINE
* do it for savety, JGPAR may be dropped
        NLEVEL=0
END
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 29/07/96  12.00.03  by  Pavel Nevski
*-- Author :    R.Brun
***********************************************************************
*                                                                     *
                SUBROUTINE G U T R E V
*                                                                     *
*     User routine to control tracking of one event                   *
*     ==>Called by : GTRIG                                            *
***********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
      Integer LENOCC,CsADDR,Nd,Id,IP,address/0/
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
*
      Nd=0;  If (LKDETM>0) Nd=IQ(LKDETM-2)
* following the best RDW traditions
      Do id=1,ND
         Check LQ(LKDETM-id)>0
         IP=LWPRIN(id)
         If (IDEBUG>0) IP=max(IP,LWDEBU(id))
         IQ(LQ(LKDETM-id)+1)=IP
      enddo
*
      address=CsADDR ('AGUTREV')
      if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
*
* By default (No ACTION command issued) GEANT simulations are done if:
* a: IKINE<0 and reading of HITS, DIGI and RECB is prohibited,  b: IKINE>=0.
* If ACTION is issued, Geant simulations should be asked explicitely
*
      If (Lenocc(CrunType)>0) then
         Check  Index(CrunType,'S')>0  | Index(CrunType,'*')>0
      else If (IKine<=0) then
         Check  Index(CoptKine,'H')==0 & Index(CoptKine,'D')==0
         Check  Index(CoptKine,'R')==0 & Index(CoptKine,'*')==0
      endif
 
* In addition, the presence of KINE tracks and VOLUMES and
* absence of HITS and DIGIts are required
 
      If (JHITS==0 & JDIGI==0 & JVOLUM>0 & JKINE>0) then
        CALL GTREVE
      endif
      END
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 17/04/97  20.57.01  by  Pavel Nevski
*-- Author : R. Brun
******************************************************************
             SUBROUTINE   G U T R A K
* Description: User routine to control tracking of one track     *
******************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     integer CsADDR,idevt0/-1/,address/0/
*
     CALL AGCHAIN(NhitsMax,NkineMax)
     If (Idevt0 != Idevt) then
         Idevt0  = Idevt
         address = CsADDR ('AGUTRAK')
     endif
*
     Istop = 0
     if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
     If (Istop==0)  CALL GTRACK
*
      END
 
 
*CMZ :          05/08/98  23.33.58  by  Pavel Nevski
*CMZ :  1.30/00 01/04/97  15.49.43  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.25  by  S.Giani
*-- Author :
      SUBROUTINE GUSKIP (ISKIP)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *   User routine to skip unwanted tracks                         *
C.    *                                                                *
C.    *   Called by : GSSTAK                                           *
C.    *   Author    : F.Bruyant                                        *
C.    *                                                                *
C.    ******************************************************************
C.
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
      Integer CsADDR,address/0/,Idevt0/-1/,ISKIP,L,ITRT,NVER
*
      ISKIP = 0
 
      If (Idevt0 != IDEVT) then
          Idevt0  = IDEVT
          address = CsADDR ('AGUTREV')
      End IF
 
      If (NGKINE==0 & JKINE>0) then
*     skip particles with a vertex produced - not final state
         L = LQ(JKINE-ITRA)
         If (L>0) then
            ITRT = Q(5+L)
            Nver = Q(7+L)
            If (NVER>0 | ITRT<=0) then
               ISKIP = -1
               If (IDEBUG>=3) write (LOUT,1001) ITRA
 1001          FORMAT(' *** GUSKIP: skip track number ',i8)
            endif
         endif
      endif
 
      if (address>0) CALL CsJCAL (address,1, ISKIP,0,0,0,0, 0,0,0,0,0)
 
      END
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 22/04/97  20.18.53  by  Pavel Nevski
*-- Author :    Alexandre Rozanov 02.04.95
****************************************************************************
                SUBROUTINE   G U S T E P
*                                                                          *
*  Description: process one geant  step throu a volume                     *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,agchadr.
* sequence to let hadronic package produce more then MXGKIN secondaries
*     geant  message - NDONE positive
*     guhadr message - NREST positive
*
      INTEGER          NDONE,NREST
      COMMON /AGCHADR/ NDONE,NREST
 
*KEND.
     INTEGER   CsAddr,Itry,Iret/0/,Idet/-1/,Isimu/0/,Idevt0/-1/,address/0/
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
*
   If Idevt0 != Idevt               " On a new event set USER and TRAC: "
   {  Idevt0  = Idevt;                address=CsADDR ('AgUstep')
      Call ASLDETN('TRAC',Idet);      If (Idet>0) ISIMU=LVSIMU(Idet)
   }
*
   CALL AgGSTEP(IRET)                           ! standard hit processing
   If (Idebug>0 & ISWIT(2)==3) Call GDEBUG      ! for graphics only
   if (ipart == 48)            Call AgSMATER    ! geantino run
*
   DO itry=1,10        " let hadronic package produce what it needs "
   {  IF (NGKINE>0) then                           ! decide on secondaries
         CALL VZERO(IFLGK,NGKINE)
         If (ISIMU>=1)            Call AgUsecond   ! - mechanism based
         If (Flag_secondaries>=2) Call AgsSECOND   ! - dense media
      endif
*                                                  ! let user do something
      if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
*
      If (NGKINE<=0)   Break
         NDONE += NGKINE
         CALL GSKING(0)   " really save secondaries "
         NGKINE = 0
         if (NREST<=0) Break
         CALL GUHADR
    }
 
        if(ngphot.gt.0.)then
           CALL GSKPHO(0)
        endif
 
    If (NREST>0) <W> itry,NDONE,NREST
       (' GUSTEP ERROR: after ',i2,' iterations and ',i5,'particles done'/,
          15x,        ' still ',i5,' particles left in hadronic package')
    NDONE=0
 
*
 END
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 10/04/96  18.46.17  by  Pavel Nevski
*CMZU:  1.00/01 16/11/95  02.01.56  by  Pavel Nevski
*-- Author :    P. Nevski
************************************************************************
*                                                                      *
                SUBROUTINE   G U F L D (VECT,FIELD)
*                                                                      *
* Description: Geant user routine for FIELD definition step by step    *
* Arguments  : VECT   (in)   -              tracking position          *
*              Field  (out)  -              filed map at vect          *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
*
      REAL      VECT(3),FIELD(3)
      Integer   CSADDR,Iprin/2/,address/0/,IevOLD/-1/
      Logical   FIRST/.TRUE./
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*    make it possible to replace field routine between events
      IF (IEVENT != IEVOLD) THEN
         address=CsADDR ('AGUFLD')
         IEVOLD=IEVENT
      endif
*
      if (address>0) then
         CALL CsJCAL (address,2, VECT,Field,0,0,0, 0,0,0,0,0)
      Else
         Field={0.,0.,0.}
      Endif
*
      END
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 07/07/96  13.08.33  by  Pavel Nevski
*-- Author :    Pavel Nevski   07/07/96
     subroutine    G U D I G I
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
     Integer      CsADDR,Nset,Ndet,Iset,Idet,Ldete,Lsete,address
     Character*4  Cset,Cdet
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
 
     Check LkDetm>0 & Jset>0 & Jhits>0
     Ndet  = IQ(LkDetm-2);       Check Ndet>0
     Nset  = IQ(Jset - 2);       Check Nset>0
     Do Idet=1,Ndet
        Ldete=LQ(LkDetm-Idet);   Check Ldete>0
        Check LvDIGI(Idet)>0
        Call UHTOC(IQ(LkDetm+Idet),4,Cdet,4)
        Do Iset=1,Nset
           Lsete=LQ(Jset-Iset);  Check Lsete>0
           Call UHTOC(IQ(Jset+Iset),4,Cset,4)
           Check Cdet(1:3)//'H'==Cset
           address=CsADDR (cdet//'DIG')
*           print *,'digi routine for ',cdet,': address=',address
           if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
        enddo
     enddo
*
     address=CsADDR ('AGUDIGI')
     if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
 
     end
 
 
*CMZ :  1.30/00 06/07/96  00.19.32  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/06/96
******************************************************************************
*                                                                            *
                   Subroutine  G U O U T
*                                                                            *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Integer  Ier
*
      If (IOutp!=IOutpOld) then
         If (IOutp==-1) Call AgZOPEN('O','ZEBRA.O','*',0,0)
         If (IOutp > 0) IOutpOld = Ioutp
      endif
*
      Ier   = 0
      If (IOutpOld==-1)   call AgZwrite('O',ier)
      If (ier != 0)       { IOutpOld = 0;  IQUEST(1)=Ier; IEORUN=1; }
*
END
 
 
*CMZ :  1.30/00 19/04/97  21.12.12  by  Pavel Nevski
*-- Author :    Rashid Mekhdiev
****************************************************************************
                SUBROUTINE   G U H A D R
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
      INTEGER IPAIR,ICOMP,IPHOT,IPFIS,IDRAY,IANNI,IBREM,IHADR,IMUNU
     +       ,IDCAY,ILOSS,IMULS,IRAYL,ILABS,ISYNC,ISTRA
      REAL    SPAIR,SLPAIR,ZINTPA,STEPPA,SCOMP,SLCOMP,ZINTCO,STEPCO
     +       ,SPHOT,SLPHOT,ZINTPH,STEPPH,SPFIS,SLPFIS,ZINTPF,STEPPF
     +       ,SDRAY,SLDRAY,ZINTDR,STEPDR,SANNI,SLANNI,ZINTAN,STEPAN
     +       ,SBREM,SLBREM,ZINTBR,STEPBR,SHADR,SLHADR,ZINTHA,STEPHA
     +       ,SMUNU,SLMUNU,ZINTMU,STEPMU,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +       ,SLOSS,SOLOSS,STLOSS,DPHYS2,SMULS,SOMULS,STMULS,DPHYS3
     +       ,SRAYL,SLRAYL,ZINTRA,STEPRA,SLABS,SLLABS,ZINTLA,STEPLA
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEND.
*
      IF      IHADR==0  { ISTOP=2; KCASE=NAMEC(12); DESTEP+=GEKIN; }
      ELSE IF IHADR<=3  { CALL GHEISH }
      ELSE IF IHADR==4  { CALL FLUFIN }
      ELSE IF IHADR==5  { CALL GFMFIN }
      ELSE IF IHADR==6  { CALL GCALOR }
*
      END
 
 
*CMZ :  1.30/00 17/04/97  19.08.11  by  Pavel Nevski
*-- Author :    Rashid mekhdiev
****************************************************************************
      SUBROUTINE GUPHAD
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
      INTEGER IPAIR,ICOMP,IPHOT,IPFIS,IDRAY,IANNI,IBREM,IHADR,IMUNU
     +       ,IDCAY,ILOSS,IMULS,IRAYL,ILABS,ISYNC,ISTRA
      REAL    SPAIR,SLPAIR,ZINTPA,STEPPA,SCOMP,SLCOMP,ZINTCO,STEPCO
     +       ,SPHOT,SLPHOT,ZINTPH,STEPPH,SPFIS,SLPFIS,ZINTPF,STEPPF
     +       ,SDRAY,SLDRAY,ZINTDR,STEPDR,SANNI,SLANNI,ZINTAN,STEPAN
     +       ,SBREM,SLBREM,ZINTBR,STEPBR,SHADR,SLHADR,ZINTHA,STEPHA
     +       ,SMUNU,SLMUNU,ZINTMU,STEPMU,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +       ,SLOSS,SOLOSS,STLOSS,DPHYS2,SMULS,SOMULS,STMULS,DPHYS3
     +       ,SRAYL,SLRAYL,ZINTRA,STEPRA,SLABS,SLLABS,ZINTLA,STEPLA
C
*KEND.
      IF       IHADR<=3 {"geisha"       CALL GPGHEI  }
      ELSE IF  IHADR==4 {"fluka"        CALL FLDIST  }
      ELSE IF  IHADR==5 {"fluka+Mikap"  CALL GFMDIS  }
      ELSE IF  IHADR==6 {"gcalor"       CALL CALSIG  }
      END
 
 
*CMZ :          30/01/98  13.07.52  by  Pavel Nevski
*CMZ :  1.30/00 20/04/97  23.19.45  by  Pavel Nevski
*-- Author :    Pavel Nevski
******************************************************************
*                                                                *
                Function    R N D M (x)
*                                                                *
******************************************************************
      logical first/.true./
*
        if (first) print *,' *******  RNDM substituted by GRNDM  *******'
        first=.false.;   call GRNDM(r,1);   rndm=r;  Return;
      entry IRNDM
        if (first) print *,' *******  RNDM substituted by GRNDM  *******'
        first=.false.;   call GRNDM(i,1);  irndm=i;  Return;
      END
*
      subroutine NORRAN (a)
      real    a,b/99999/
      logical first/.true./
       if (first) print *,' *******  NORRAN substituted by RANNOR  *******'
       if b==99999 { call rannor(a,b); first=.false. } else { a=b; b=99999 }
      end
*
      function  RANF (a)
      real      RANF,a,b
      logical   first/.true./
       if (first) print *,' *******  RANF substituted by GRNDM  *******'
       first=.false.
       Call GRNDM(b,1)
       RANF=b
      end
*
      function  RN32(a)
      real      RN32,a,b
      logical   first/.true./
       if (first) print *,' *******  RN32 substituted by GRNDM  *******'
       first=.false.
       Call GRNDM(b,1)
       RN32=b
      end
*
      function  RG32(d)
      real      RG32,d,a,b/99999/
      logical   first/.true./
       if (first) print *,' *******  RG32 substituted by RANNOR  *******'
       if b==99999 { call rannor(a,b); first=.false. } else { a=b; b=99999 }
       RG32=a
      end
*
      Subroutine RDMIN
      entry      RDMOUT
        print *,' RNDM substituted by GRNDM, set seed using G/CONT/RNDM'
      end
*
      Subroutine RN32IN
      entry      RN32OT
        print *,' RN32 substituted by GRNDM, set seed using G/CONT/RNDM'
      end
*
      Subroutine RG32IN
      entry      RG32OT
        print *,' RG32 substituted by RANNOR, set seed using G/CONT/RNDM'
      end
*
 
 
 
*CMZ :          18/12/97  17.27.24  by  Pavel Nevski
*CMZ :  1.30/00 29/03/97  18.01.53  by  Pavel Nevski
*-- Author :    Pavel Nevski   15/08/96
 
      SUBROUTINE GCALOR
      print *,' No GCALOR available in this version'
      end
      SUBROUTINE CALSIG
      print *,' No GCALOR available in this version'
      end
 
 
*CMZ :          01/04/98  11.36.29  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  18.16.37  by  Pavel Nevski
*-- Author :    Pavel Nevski
************************************************************************
      subroutine TRACEQ
*                         (LUNP,LEV)
*                                                                      *
* Description: dispatch an abnormal situation (arithmetics or ZEBRA)   *
************************************************************************
      Implicit NONE
      Integer  AgPHASE,IgPAW,IwTYP
      Common /AgCPHASE/ AgPHASE
      Common /AgCIPAW/  IgPAW,IwTYP
*
      call traceqc
      If AgPHASE>0                                 " in event loop  "
      {  call qnexte; print *,' in traceq: qnexte exit' }
      ELSE IF IgPAW>0                              " single command "
      {  call kusibr; print *,' in traceq: kusibr exit' }
*
      print *,' Abnormal break recovery - only limited functionality'
      CALL   AGPAWQ
      STOP ' TRACEQ '
 
      END
 
 
*CMZ :  1.30/00 15/07/96  15.54.59  by  Pavel Nevski
*-- Author :    P.Nevski    20/01/94
***************************************************************************
                FUNCTION   I S L F L A G (CHDET,CHFLAG)
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,asflags.
      INTEGER      NFLAGS
      PARAMETER    (NFLAGS=15)
      CHARACTER*4  CFLAG(NFLAGS)
      DATA CFLAG   /'PNOW','PRIN','DEBU','GEOM','HIST','GRAP',
     >              'SIMU','DIGI','RECO','MFLD','ANAL','BACK',
     >              'RESA','RESB','RESC'/
*    ---------------------------------------------------------
*KEND.
      INTEGER      ISLFLAG,IDET,IFLAG
      CHARACTER*4  CHDET,CHFLAG
*
      ISLFLAG = -1;    check LkDETM>0
      CALL GLOOK(CHDET,IQ(LkDETM+1),IQ(LkDETM-1),Idet)
      check Idet>0;    Check LQ(LkDETM-Idet)>0
*
      ISLFLAG = -2
      DO IFLAG = 1,NFLAGS
         check CHFLAG==CFLAG(IFLAG)
         ISLFLAG = IQ(LQ(LKDETM-IDET)+IFLAG)
         Return
      END DO
      END
 
*CMZ :          07/07/98  10.26.34  by  Pavel Nevski
*CMZ :  1.30/00 27/03/97  19.14.44  by  Pavel Nevski
*-- Author :    Pavel Nevski   10/04/96
**************************************************************************
                subroutine   z a b e n d (NQCASE,LINK)
**************************************************************************
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
 
  Integer      i,NQCASE,LINK
  Character    Cname*8
  Equivalence (Cname,IQUEST(9))
*
* print *,'*************************************************************'
* print *,'***       Our old Zebra is heavilly ill, almost dead      ***'
* print *,'***       next time try to treat her more carefully       ***'
* print *,'***                 Or ask Pavel to save her              ***'
* print *,'*************************************************************'
*
* Call UHTOC(IQUEST(9),4,CNAME,8)
  <w> Nzebra,Cname,NQCASE,NQPHAS,NQFATA
  (' zebra age = ',i8,' hinted by ',a8,' for case ',i4,
   ' in phase ',i3,' fatality ',i3)
 
  If Cname='MZGAR1'
  {  L= "LQSYSR(KQT+1)" LINK;
     IF (NQCASE==1) <w> IQUEST(11),(IQ(L+i),i=-5,1)
     (' LACK OF SPACE to push a bank,',i8,' words missing '/,
      ' bank ID=',i6,a6,'  NL,ND=',3i8,'  system, data=',2i12)
  }
  else If Cname='MZTABC'
  { IF (NQCASE==1) print *,' the BANK CHAINING is CLOBBERED (corrupted)',
                           ' the start of clobbered region is ',IQuest(11)  }
  else If Cname='MZPUSH'
  { if (NQCASE==1) print *,' this means the link ',IQUEST(11),' is invalid '}
  else If Cname='ZSHUNT'
  { if (NQCASE==2) print *,' the supporting link ',IQUEST(12),' is invalid '}
  else If Cname='FZLOC'
  { print *,' FZLOC reports an illegal FZ control information access (p.269)'
    print *,' Lun=',iquest(11),' I/O mode (1-i, 2-o) ',iquest(12)
    If (NQCASE==1) print *,' WRITE after READ without switching by FZENDI  '
    If (NQCASE==2) print *,' READ after WRITE without switching by FZENDO  '
    If (NQCASE==3) print *,' access permision fault, e.g. write protected  '
    If (NQCASE==4) print *,' access to the file was not declared by FZFILE '
  }
  else If Cname='MZLIFT'
  { print *,' MZLIFT Cannot mount a new bank possibly because of '
    If (NQCASE==1) print *,'        faulty bank parameters '
    If (NQCASE==2) print *,'        invalid supporting link'
    If (NQCASE==3) print *,'        bank at LSUP has too few structural links'
    If (NQCASE==4) print *,'        invalid next link '
    If (NQCASE==5) print *,'        non-existing I/O characteristic'
    If (NQCASE==6) print *,'        invalid I/O parameter'
    If (NQCASE==7) print *,'        attempt to lift bank in a wrong division'
    If (NQCASE==8) print *,'   attempt to connect the new bank inside a bank'
  }
  else If Cname='MZDROP'
  {  print *,' MZDROP can not drop bank because '
     If (NQCASE==1) print *,'  the Link ',Iquest(11),' is illegal '
     If (NQCASE==2) print *,'  the Next Link ',Iquest(12),' is illegal '
  }
  else
  { Print *,' JVOLUM,NVOLUM =',JVOLUM,Nvolum
    If 0<Jvolum&Jvolum<Nzebra
    { If (IQ(Jvolum-1)!=Nvolum) print *,' real VOLU bank length=',IQ(Jvolum-1)}
    else
    { print *,' JVOLUM points outside reasonable area '}
 
    Print *,' JGPAR,NLEVEL  =',JGPAR,NLEVEL
    If (0<JGpar & JGpar<Nzebra)
    { print *,' real GPAR bank data/link length=',(IQ(JGPAR-i),i=1,3)
      "If (IQ(JGPAR-1)<=0)" JGpar=0
    }
    print *,' that is all for the moment, Have you done GGCLOS ? '
  }
  <w> (IQUEST(i),i= 1,10); (' Iquest=',10i9)
  <w> (IQUEST(i),i=11,20); (' Iquest=',10i9)
  NQCASE=0
  end
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*-- Author :    Pavel Nevski   20/03/98
************************************************************************
      subroutine on fault (c,nn,name)
*
* Description: HP arithmetic error handler control
*   In a normal mode (no +) unspecified errors are disabled.
*   With a + their handler is unchanged, is may stay as default.
*
************************************************************************
      character  Name*(*),c*(*)
      end
 
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*-- Author : Pavel Nevski
******************************************************************
                SUBROUTINE GUDCAY
*                                                                *
*       User routine to decay particles                          *
*                                                                *
*    ==>Called by : GDECAY                                       *
*                                                                *
******************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     integer CsADDR,idevt0/-1/,address/0/
*
     If (Idevt0 != Idevt) then
         Idevt0  = Idevt
         address = CsADDR ('AGUDCAY')
     endif
*
     if (address>0) CALL CsJCAL (address,0, 0,0,0,0,0, 0,0,0,0,0)
*
     END
 
 
 
*CMZ :  1.30/00 16/07/96  23.30.40  by  Pavel Nevski
*CMZ :  1.00/00 12/04/95  19.53.08  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x C o m p o n e n t
*                                                                    *
*  Description:  introduce a componenet of a new mixture             *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
 Integer LENOCC
 " check %W>0; "
 If (%z>0) %Za=%z;
 IF %NLmat>=10 { error('NO more place to store a component of the mixture') }
 %NLmat+=1; %AA(%NLmat)=%A; %ZZ(%NLmat)=%Za; %WW(%NLmat)=%W;
   END
 
*CMZ :  1.30/00 21/07/96  15.36.42  by  Pavel Nevski
*CMZ :  1.00/00 05/05/95  20.15.51  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x M i x t u r e
*                                                                    *
*  Description:  introduce a new mixture, reset medium number   	     *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
  Integer      AgSMATE,LENOCC,Imixt,N,i,jma;
  Real         SW,a(20),z(20),w(20),Par(10);
  Character*4  Cmate,Cmodu;
 
  Call Vzero(Par,10);
  %Material=%Title;  Imixt=AgSMATE(%Material,JMATE,Par);
  Cmate=%Material;   Cmodu=%Module;
 
  N=0;  do i=1,%Nlmat  { if (%WW(i)>0) N+=1; };   Par={0,0,%Dens,0,0,N};
  if Imixt<0 & Cmate#Cmodu & Cmodu#' '
  {  %Material=Cmodu//'_'//%Title; Imixt=AgSMATE(%Material,JMATE,Par); }
 
  %Medium=%Material;   %Imed=-1;   %Imat=abs(Imixt);
  If Imixt<0
  {  SW=0; N=0;  do i=1,%Nlmat
     {check %WW(i)>0; N+=1; SW+=%WW(i); a(N)=%aa(i); z(N)=%ZZ(i); W(N)=%WW(i)}
     If SW<=0 {error('Mixture undefined')};   if (SW>1.5)  N=-N;
     prin1  %L(%Material),%Imat,%Dens,N,(%aa(i),%zz(i),%ww(i),i=1,%NLmat);
     (' GSMIXT   for mixture ',A,' used Imat=',I3,
      ' Density=',F5.2,' NLmat=',i2/(10x,'A,Z,W =',3F10.3));
     Call GSMIXT (%Imat, %Material, A, Z, %Dens, N, W);
  }
  Jma=LQ(JMATE-%Imat);  %A   = Q(Jma+6);     %Z  = Q(Jma+7);
                       %RadL = Q(Jma+9);    %AbsL = Q(Jma+10);
                       %NLMAT= 0;
   END
 
*CMZ :  1.00/00 23/02/95  01.10.25  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x M a t e r i a l
*                                                                    *
*  Description:  introduce a new material, reset medium number       *
*  New material in a module is always prefixed by the module name    *
*  A request without parameters does not introduce new material      *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
    Integer     AgSMATE,LENOCC,Im;
    Character   Cmate*4,Cmodu*4,Material*20;
    Real        PAR(10);
 
 If(%z>0) %Za=%z;     Call Vzero(Par,10);
 %Material=%Title;    Cmate=%Material;   Cmodu=%Module;
 If %ParList#'NONE'  { PAR={%A,%Za,%Dens,%Radl,%ABSL}; }
 
 Im=AgSMATE (%Material,JMATE,Par);           " first check for a global "
 if Im<0 & Cmate#Cmodu & Cmodu#' '           " then for a local material"
 {  %Material=Cmodu//'_'//%Title;  Im=AgSMATE(%Material,JMATE,Par); }
 
 %Medium=%Material;   %Imed=-1;   %Imat=abs(Im);
 if Im<0
 { If %Parlist='NONE'  {error('Undefined material requested',%Title)}
   prin1  %L(%Material),%Imat,%A,%Za,%Dens,%RADL,%ABSL;
   (' GSMATE   called with for material ',A,' produces Imat =',I3/,
      10x, 'A,Z,D,x0,l0 =',5E11.4);
    Call GSMATE(%Imat,%Material,%A,%Za,%Dens,%RADL,%ABSL,%UBUF,%NWBUF);
 }
 Else If %Parlist='NONE'
 {  Call GFMATE(%Imat, Material,%A,%Za,%Dens,%RADL,%ABSL,%UBUF,%NWBUF); }
  END
 
*CMZ :  1.30/00 02/04/97  15.00.54  by  Pavel Nevski
*CMZ :  1.00/00 27/02/95  15.31.04  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x M e d i u m
*                                                                    *
*  Description:  introduce parameters of a new GEANT tracking medium *
*  Direct call always sets the medium name and fetchs its parameters *
*  In the STANDARD module it can introduce a new media in the table  *
*  The real medium is introduced at the SHAPE operator only,         *
*  otherwise initial medium inherits a wrong material (tested!)      *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
    Integer      AgSMATE,LENOCC,Im,Imed,Imat,Ifield
    Character    Medium*20,Cmedi*4,Cmodu*4
    Real         Par(10)
*
 %Medium=%Title;     Cmedi=%Medium;   Cmodu=%Module;  Ifield=%Ifield*%Imfld
 PAR={0,%IsVol, Ifield,%Fieldm,%TmaxFD, %SteMax,%DeeMax,%Epsil,%Stmin, 0};
 
 Im=AgSMATE (%Medium,JTMED,Par);              " first check for a global "
 If Im<=0 & Cmedi#Cmodu & Cmodu#' '           " then for a local medium  "
 {  %Medium=Cmodu//'_'//%Title;  Im=AgSMATE(%Medium,JTMED,Par);  }
 
 Imed=abs(Im); %Imed=-1;
 If Im<0
 {  %Imed = Imed
    " If %Parlist='NONE' {error('Undefined medium requested',%Title)} "
    prin1       %L(%MEDIUM), %Imed, %Imat, %ISVOL,   IFIELD, %FIELDM, %TMAXFD,
                                           %STEMAX, %DEEMAX, %EPSIL,  %STMIN
                (' AGSTMED  for medium ',A,' med,mat,sen,fld =',2i4,2i2/,
                               10x ,'Field = ',2F5.1,'  steps = ',4F8.5)
    Call GSTMED (%Imed, %MEDIUM, %IMAT,   %ISVOL,  IFIELD, %FIELDM, %TMAXFD,
                        %STEMAX, %DEEMAX, %EPSIL, %STMIN,  %UBUF,   %NWBUF)
 }
 else if %Parlist='NONE'
 {  Call GFTMED ( Imed,  Medium,  Imat,   %Isvol, %IFIELD, %FIELDM, %TMAXFD,
                        %STEMAX, %DEEMAX, %EPSIL, %STMIN,  %UBUF,   %NWBUF)
 }
  END
 
*CMZ :  1.00/00 06/01/95  22.24.20  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x S H A P E
*                                                                    *
*  Description:  a dispatch routine to do GSDIV, GSVOLU              *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEND.
 
    %Shape=%Title;  %Ishape=0;
    if %Imed<=0        {   Call AgSMedi;   check %Imed    >0; }
    If %Shape = 'DIVI' {   Call AgSDIVI;   Check %Ivolume >0; }
    else               {   Call AgSHAPE;   Check %Ishape  >0;
                           Call AgSVOLU;   Check %Ivolume >0; }
    %Istatus=1;            Call AxATTRIBUTE;
   END
 
*CMZ :  1.30/00 28/04/96  20.12.52  by  Pavel Nevski
*CMZ :  1.00/00 21/03/95  22.40.41  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x A T T R I B U T E
*                                                                    *
*  Description:  set volume attributes for GEANT                     *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
 character*4 ATTname(6) /'WORK','SEEN','LSTY','LWID','COLO','FILL'/; Integer i;
 Integer     is,ig;
 Check  %Istatus>0;
 Do i=1,6
 {  if (%attribute(i)#%MAGIC) Call GSATT (%Cnick,ATTname(i),%attribute(i)); }
 If %IGRAP>1
 {  is=1;  Ig=%IGRAP-%LEVEL;
    if(Ig<0) is=-1; if(Ig>2) is=0; Call GSATT(%Cnick,'SEEN',is);
 }
 END
 
*CMZ :  1.30/00 21/11/96  19.48.44  by  Pavel Nevski
*CMZ :  1.00/00 06/08/95  14.04.27  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A x P O S I T I O N
*                                                                    *
*  Description:  make GSPOS or GSPOSP                                *
*  Modifications:                                     28.07.95 - PLN *
*  - Start with the mother volume checking to allow fake positioning *
*    divisions.   No checks are done yet for an errenious            *
*    normal volume positioning at the same level as divisions ...    *
*  - 14.11.96 PN+SB: Ncopy can be passed throu AGECOM in both ways   *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
  Character*4 Daughter,Daught;            Real Vdist,D,V
  Integer  LENOCC,Idaught,Ivd,Jvd,Ivo,Jvo,Ign,Ir,Jvm,Ivm,
           Npo,Npa,Jmo,in,nin,Ncopy,Id,Jd,Jg,IDH,IDM
 
* search for the mother, if it is explicitely defined, and check it.
  If %Ivolume<=0 | %Mother!=%Volume
  {  %Cnick=%Mother;  Call GLOOK(%Mother,IQ(JVOLUM+1),Nvolum,%Ivolume);
     If %Ivolume<=0
     {  If %Level>0  {error('mother volume does not exist')};
        <w> %Mother; (' Warning: Volume ',a4,' does not exist'); Return;
     }
     Jvm=LQ(JVOLUM-%Ivolume); Ivm=IQ(Jvm-5); IDM=IQ(Jvm-4);
     IF IDM==IQ(JVOLUM+%Ivolume) & 1<=Ivm&Ivm<=Nvolum
     { %Ivolume=Ivm; call UHTOC(IQ(JVOLUM+Ivm),4,%Cnick,4); }
  }  Jmo=LQ(JVOLUM-%Ivolume); nin=Q(Jmo+3);
  Check "that it has no divisions " nin>=0
 
* get Active volume number from the generic bank IDN word;
  Daughter=%Title;  Call GLOOK (Daughter,IQ(JVOLUM+1),Nvolum,Ivd);
  If Ivd<=0   {error('daughter ',Daughter,' does not exist ')};
  " generic daughter "  IDH=IQ(JVOLUM+Ivd); Jvd=LQ(JVOLUM-Ivd);
  Ivo=IQ(Jvd-5);  If Ivo<=0 {error('Actual daughter does not exist ')};
  " its nickname "  Idaught=IQ(JVOLUM+Ivo); Jvo=LQ(JVOLUM-Ivo);
  " and number   "  Ign=0;    If (Ivd#Ivo)  Ign=IQ(Jvo-5);
 
* get actual rotation and may be shape parameters
  %Ishape=Q(Jvo+2);  Npo=Q(Jvo+5);  Npa=0;
  Call AgSROTM " - it may cause bank relocation, links should be reaccessed !"
  If Npo=0
  {  Call AgSHAPE;      Npa=%Npar;
     If %Npar=0  {error('Can not position undefined Volume ',Daughter)}
  }
 
* set copy number(generic) and avoid content (actual name!) dublication
  Ncopy=1;  Jmo=LQ(JVOLUM-%Ivolume);
  do in=1,abs(nin)
  {  Jd=LQ(Jmo-in); "its content"Id=Q(Jd+2); "and address"Jg=LQ(JVOLUM-Id);
     "count copies of generic name"    Check IDH=IQ(Jg-4); Ncopy+=1;
     " dont position same volumes "    Check Idaught=IQ(JVOLUM+Id);
     " at the same place and angle"    Ir=Q(jd+4); d=Vdist(%x,Q(Jd+5),3); v=0;
                                       if (Npo=0) V=Vdist(%Par,Q(jd+10),Npa);
                                       if (d=0 & V=0 & Ir=%Irot)  Return;
  }
  If (%Ncopy>0) Ncopy=%Ncopy;  %Ncopy=Ncopy;
  Call UHTOC(Idaught,4,Daught,4);   Call CLTOU (%KONLY);
  If Npo>0 { Call GSPOS (Daught,Ncopy,%CNick,%X,%Y,%Z,%Irot,%KONLY); }
  else     { Call GSPOSP(Daught,Ncopy,%CNick,%X,%Y,%Z,%Irot,%KONLY,
                                                         %PAR, %NPAR);  }
  prin1 Daught,Daughter,%CNick,%Volume,%x,%y,%z,
        %Level,Ncopy,Npa,%IROT,Ivd,Ivo,nin;
  (' POSITION',2(1x,A4),'  into',2(1x,A4),' at x,y,z=',3f9.3/_
  10x,'level',i3,'  Ncopy',i4,' with Npar,Irot=',2i4,' Ivdau,Ivact=',3I5);
   END
 
 
*CMZ :  1.30/00 02/04/97  15.21.45  by  Pavel Nevski
*CMZU:  1.00/01 30/11/95  19.31.02  by  Pavel Nevski
*CMZ :  1.00/00 04/09/95  14.29.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Subroutine   A g S V O L U
*                                                                    *
*  Description: On SHAPE returns Ivolume, actual Npar and Npo of the *
*  existing GEANT volume or creates and returns the new volume number*
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEND.
Integer     Name,LENOCC,Ivo,Jvo,IDH,Npo,Npa,i,JATTF,Jj,Jat
real        eps/1.e-6/,P(50),Tth,Phi,Ph
JATTF(Jj) = Jj+int(Q(Jj+5))+6
*
* Toggle the actual Npa = 0 | NPar
  Npa=0;  Do I=1,%Npar { if (%Par(i)#0) Npa=%Npar; }
  Call UCTOH(%Volume,Name,4,4);  %Ignum=-1;
  If %IMED<=0 {error(' Medium  in  ',%Volume,' not defined')};
 
* if the top level volume has a hole, its inner radius(radii) is reset to 0:
   if Nvolum==0
   {  If %Ishape==5 | %Ishape==6 | %Ishape==9 { %Par(1)=0 " - TUBE,TUBS,SPHE"}
      If %Ishape==7 | %Ishape==8   { %Par(2)=0; %Par(4)=0 " - CONE,CONS     "}
      If %Ishape==11  {  do i=1,nint(%PAR(4)) { %Par(3*i+3)=0 }  " - PGON   "}
      If %Ishape==12  {  do i=1,nint(%PAR(3)) { %Par(3*i+2)=0 }  " - PCON   "}
   }
* If the volume has been defined with the same dimensions, return %Ivolume;
  :volume: Do %Ivolume=1,NVOLUM
  { "take next volum's IDs "       Jvo=LQ(JVOLUM-%Ivolume);   IDH=IQ(Jvo-4);
    "Select same generic names"  check IDH==Name;   "and count them" %Ignum+=1;
    "Now check that parameters are the same, otherwise search for another copy"
    "Undefined volumes with Npa=0  will fit any other volume "
     Npo=Q(Jvo+5);     Jat=JATTF(Jvo);
     If %Ishape=4 | %Ishape=10      "      special cases in Geant 3.21     "
     {  Call Ucopy(%Par,P,min(%Npar,30));
        IF %ISHAPE=4                "        Trapezoid    "
        {  TTH =TAN(P(2)*DEGRAD);   PHI  =P(3)*DEGRAD;
           P(2)=TTH*COS(PHI);       P(3) =TTH*SIN(PHI)
           P(7)=TAN(P(7)*DEGRAD);   P(11)=TAN(P(11)*DEGRAD)
        }
        ELSE IF %ISHAPE=10   " Parallelepiped - change angles to tangents. "
        {  P(4)=TAN(P(4)*DEGRAD);   TTH=TAN(P(5)*DEGRAD);  PH=P(6)*DEGRAD;
           P(5)=TTH*COS(PH);        P(6)=TTH*SIN(PH)
        }
        Do I=1,min(Npo,Npa)
        {  If (abs(P(i)-Q(Jvo+6+i))>eps*abs(P(i)+Q(Jvo+6+i))) Next :volume:; }
     }  Else
     {  Do I=1,min(Npo,Npa)        { If (%Par(i)#Q(Jvo+6+i))  Next :volume:; }
     }
    "Do I=1,6             { If(%Attribute(i)#nint(Q(Jat+i)))  Next :volume:; }"
    "This is an existing volume, use it! If Npo==0, we will need to GSPOSP it"
     if (%Serial=nint(Q(Jat+10)) & %Imed=nint(Q(Jvo+4)))      goto :done:
  }
 
* make a new volume always at the end of the volume list
   %Ignum+=1;  Call AgSNAME(%Volume,%Ignum,%Cnick)
   Call GSVOLU(%Cnick, %Shape, %Imed, %Par, Npa, %Ivolume)
   prin1 %Volume,%Cnick,%Shape,%Imed,%Ivolume,Npa,(%Par(i),i=1,Npa)
  (' AGSVOLU: Name/shape ',3(A4,2x),' Imed,Iv,Np=',3I5/(10x,'Par=',10F8.2))
   If %Ivolume<NVOLUM {error(' error defining GEANT volume ',%Volume)}
*
  "set also volume generic name and number in IDH & IDN , Idtype "
   Jvo=LQ(JVOLUM-%Ivolume); IQ(Jvo-4)=Name; IQ(Jvo-5)=%Ignum;
   Jat=JATTF(Jvo);  Q(Jat+9)=%IdType;  Q(Jat+10)=%Serial;
:done:
* save Active volume number in the generic bank status word;
  Call GLOOK (%Volume,IQ(JVOLUM+1),Nvolum,Ivo);  Jvo=LQ(JVOLUM-Ivo);
  IQ(Jvo-5)=%Ivolume;  Call UHTOC(IQ(JVOLUM+%Ivolume),4,%CNICK,4);
   END
 
*CMZU:  1.00/01 30/11/95  23.54.58  by  Pavel Nevski
*CMZ :  1.00/00 04/09/95  14.29.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Subroutine   A g S D I V I
*                                                                    *
*  Description: make volume division according to actual parameters  *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
 Character   Fun*6,Mother*4
 Integer     LENOCC,Name,Nick,Nin,Jmo,Jvd,Ndm,JATTF,Jj,Jat
 JATTF(Jj) = Jj+int(Q(Jj+5))+6
*
 Call UCTOH(%Volume,Name,4,4)
 Call UHTOC(IQ(JVOLUM+%Imother),4,Mother,4)
 Jmo=LQ(JVOLUM-%Imother);  nin=Q(Jmo+3);
 If nin>0  { error('Volume has daughters, division impossible')}
 If nin<0  { %Ivolume=Q(LQ(Jmo-1)+2);       Jvd=LQ(JVOLUM-%Ivolume);
             If IQ(Jvd-4)#NAME  { error('bad name of an existing division')}
             Call UHTOC(IQ(JVOLUM+%Ivolume),4,%CNICK,4)
             %Ignum=IQ(Jvd-5);              Return;
           }
 %Ignum=0;
 Do %Ivolume=1,NVOLUM { If(IQ(LQ(JVOLUM-%Ivolume)-4)=Name) %Ignum+=1; }
 Call AgSNAME (%Volume,%Ignum,%CNick)
*
  Ndm=%NdvMax;
  If      %C0=0 & %Ndiv#0
  { Fun='GSDVN';  Call GSDVN (%Cnick,Mother,%Ndiv,%Iaxis )}
  else If %C0=0 & %Step#0
  { Fun='GSDVT';  Call GSDVT (%Cnick,Mother,%Step,%Iaxis,%Imed,Ndm)}
  else If %C0#0 & %Ndiv#0 & %Step#0
  { Fun='GSDVX';  Call GSDVX (%Cnick,Mother,%Ndiv,%Iaxis,%Step,%C0,%Imed,Ndm)}
  else If %C0#0 & %Ndiv#0
  { Fun='GSDVN2'; Call GSDVN2(%Cnick,Mother,%Ndiv,%Iaxis,%C0,%Imed)}
  else If %C0#0 & %Step#0
  { Fun='GSDVT2'; Call GSDVT2(%Cnick,Mother,%Step,%Iaxis,%C0,%Imed,Ndm)}
  else { error('missing parameters to make a division ')}
*
  Call UCTOH(%Cnick,Nick,4,4)
  If IQ(JVOLUM+Nvolum)#Nick {error('can not find newly created division ')}
  "set also volume generic name and number in IDH & IDN, and IdType "
  %Ivolume=NVOLUM; Jvd=LQ(JVOLUM-%Ivolume)
  IQ(Jvd-4)=NAME;  IQ(Jvd-5)=%Ignum;
  Jat=JATTF(Jvd);  Q(jat+9)=%IdType;  Q(jat+10)=%Serial;
  prin1 Mother,%Cnick,%L(%Volume),%Ignum,Fun
  (' AGSDIVI: mother ',A4,' divided into ',A4,2x,A4,'(',i3,') using ',A6)
  END
 
 
*CMZ :          02/12/97  18.46.06  by  Pavel Nevski
*CMZ :  1.00/00 12/12/94  22.30.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Subroutine   A g S H A P E
*                                                                    *
*  Description: given SHAPE or ISHAPE  returns its code/name and     *
*               parameters                                           *
*  Modifications:                                                    *
*  A.Dellacqua 27.02.97: CTUB parameters introduced                  *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
Replace[;#?#;]    with  [[SETR a=0];    IF %Shape=='#1' {;#2=>Par;};          ]
Replace[;#,#=>#;] with  [{IF} [EXIST 1] {[INCR a]; %#3([COPY a])=%#1; #2,=>#3;}
                         {ELSE} {; %Npar=[COPY a]; }            ]
 
 Integer  LENOCC,Is,I,K; Character*4  ShapS(30);
 Data ShapS /'BOX ','TRD1','TRD2','TRAP','TUBE','TUBS','CONE','CONS','SPHE',
      'PARA','PGON','PCON','ELTU','HYPE',  13 * '    ','GTRA','CTUB','    '/;
 
 If %Ishape<=0  { Do Is=1,30 { IF %SHAPE==ShapS(Is)  { %Ishape=Is; Break;} } }
 If %Ishape<=0  { error(' Undefined shape ',%SHAPE)}   %Shape=ShapS(%Ishape);
 
 Box  ?  dx,dy,dz;
 Trd1 ?  dx1,dx2, dy,dz;
 Trd2 ?  dx1,dx2, dy1,dy2, dz;
 Trap ?  dz,thet,phi, h1,bl1,tl1,alp1, h2,bl2,tl2,alp2;
 Tube ?  Rmin,Rmax,Dz;
 Tubs ?  Rmin,Rmax,Dz, Phi1,Phi2;
 Cone ?  Dz, Rmn1,Rmx1, Rmn2,Rmx2;
 Cons ?  Dz, Rmn1,Rmx1, Rmn2,Rmx2, phi1,phi2;
 Sphe ?  Rmin,Rmax, The1,The2, Phi1,Phi2;
 Para ?  Dx,Dy,Dz,  Alph,Thet,Phi;
 Pgon ?  Phi1,Dphi,Npdiv,Nz;
 Pcon ?  Phi1,Dphi,      Nz;
 Eltu ?  P1, P2, Dz;
 Hype ?  Rmin,Rmax,Dz,Thet;
 Gtra ?  Dz,Thet,Phi,Twis, h1,bl1,tl1,alp1, h2,bl2,tl2,alp2;
 Ctub ?  Rmin,Rmax,Dz, Phi1,Phi2, Lx,Ly,Lz,Hx,Hy,Hz;
 
 If %Shape=='PGON' | %Shape=='PCON'
 { k=%Npar; %Npar+=3*%Nz;  do i=1,%Nz
   { %Par(3*i+k-2)=%zi(i); %Par(3*i+k-1)=%rmn(i); %Par(3*i+k)=%rmx(i);}
 }
   END
 
*CMZ :          05/06/97  12.19.59  by  Pavel Nevski
*CMZ :  1.30/00 13/03/96  21.37.15  by  Pavel Nevski
*CMZ :  1.00/00 12/12/94  22.30.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
************************************************************************
*                                                                      *
                    Subroutine   A g S R O T M
*                                                                      *
* Description:  Given the rotation parameters returns matrix number    *
  Replace [;#,#=>#;] with [;rot(#3)=%#1; IF(abs(rot(#3)-#2)>eps) k+=1; ]
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
  Real Rrot,Rot(6),Rota(6),eps/1.e-5/
  Integer k,Im,i,Nlink,JTM,ii
  rrot(ii)=rot(mod(2*%OrtI+ii-1,6)+1)
*
  k=0;  %Irot=0;
  Thetax+%Alfay,90 => 1;   Thetay+%Alfax,90 => 3;   Thetaz+%Alfax+%Alfay,0 => 5;
  Phix + %Alfaz, 0 => 2;   Phiy + %Alfaz,90 => 4;   Phiz                ,0 => 6;
        " correct for phi uncertainty "  If  %Alfax#0  { %Phiz=90; rot(6)=90; }
  check  k>0 | %Orti>0
  %Irot=1;   Do i=1,6 { Rota(i)=RRot(i) }
  IF JROTM>0    " find an old matrix or the first free slot (or the end) "
  {  Nlink=IQ(JROTM-2);  :matrix: DO  Im=1,Nlink+1
     {  %Irot=Im;  JTM=LQ(JROTM-Im);   IF (JTM<=0 | Im>Nlink)  Break
        Do i=1,6 { If (Rota(i)#Q(JTM+10+i)) Next :Matrix:; };  Return
  }  }
        " Free slot for a new rotation matrix"
  Call GSROTM(%IRot,Rota(1),Rota(2),Rota(3),Rota(4),Rota(5),Rota(6))
  prin1 (Rota(i),i=1,6); (' NEW ROTM theta,phi=',3(F8.1,F6.1))
  END
 
 
 
*CMZ :  1.00/00 03/02/95  14.29.31  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
              Function     A g S M A T E (CNAME,LINK,Par)
*                                                                    *
*  Description: find the media or the first free slot (or the  end)  *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
     Integer       AgSMATE,NAME(5),LINK,Nlink,Im,JTM,i,Np;
     Character*20  CNAME;
     Real          Par(10);
 
 IF LINK<=0  { AgSMATE =-1;  Return "book first medium at slot 1"; }
;
 Call UCTOH(CNAME,NAME,4,20);  Nlink=IQ(LINK-2);
 NP=6; If (LINK=JTMED) NP=5;
 :Media: DO  Im=1,Nlink+1
 {  JTM=LQ(LINK-Im);    IF (JTM<=0 | Im>Nlink)  Break;
    Do i=1,5  { If ( NAME(i) # IQ(JTM+i) )      Next :Media:; };
    Do i=1,Np { If (0#PAR(i)&Par(i)#Q(JTM+5+i)) Next :Media:; };
    AgSMATE=+Im; " <W> IM; (10x,'ITMED of existing medium ', I3);" return;
 }  AgSMATE=-Im; " <W> IM; (10x,'Free slot for a new medium',I3);" return;
   END
 
*CMZ :  1.30/00 17/11/96  21.30.12  by  Pavel Nevski
*CMZU:  1.00/01 30/11/95  19.17.48  by  Pavel Nevski
*CMZ :  1.00/00 24/12/94  15.06.25  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
          Subroutine   A g S N A M E   (Volume,Ign,CNick)
*                                                                    *
*  Description:  generate a NickName for (Volume,Ign) instance       *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
  Character*1 Symb
  Character*4 Volume,Cnick
  Integer     Ign,ii,i,j,k
 
 Cnick=Volume;  Unless 0<=Ign & Ign <=1368
{<W> Ign,Volume;(' AgSNAME: Bad volume number ',I5,' for Volume ',A); Return;}
  ii=Ign; do k=4,3,-1
  {  i=mod(ii,37);   ii=ii/37;   check i>0
     j=i+48;   If(i==10) j=48;   If(i>10) j=96+(i-10)
*     Cnick(k:k)=char(j)
     Call ITOCH(j,Symb,*:err:);   Cnick(k:k)=Symb
  }  :err:
   END
 
*CMZ :  1.00/00 07/03/95  21.07.41  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A g S M e d i
*                                                                    *
*  Description:  introduce parameters of a new GEANT tracking medium *
*  Called from   AxSHAPE on a new material or medium parameters      *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
    Integer      AgSMATE,LENOCC,Imede,Ifield;
    Character    Cmedi*4,Cmodu*4;
    Real         Par(10);
 
 Cmedi=%Medium;   Cmodu=%Module;  Ifield=%Ifield * %IMFLD;
 if (Cmedi#Cmodu & Cmodu#' ')  %Medium=Cmodu//'_'//%Medium;
 PAR={%Imat,%IsVol,Ifield,%Fieldm,%TmaxFD,%SteMax,%DeeMax,%Epsil,%Stmin,0};
 
 Imede=AgSMATE(%Medium,JTMED,Par);  %IMED=abs(Imede);
 If Imede<0
 {  prin1       %L(%MEDIUM), %IMED, %Imat, %ISVOL,   IFIELD, %FIELDM, %TMAXFD,
                                           %STEMAX, %DEEMAX, %EPSIL,  %STMIN;
                (' AGSTMED  for medium ',A,' med,mat,sen,fld =',2i4,2i2/,
                               10x ,'Field = ',2F5.1,'  steps = ',4F8.5);
    Call GSTMED (%IMED, %MEDIUM, %IMAT,   %ISVOL,  IFIELD, %FIELDM, %TMAXFD,
                        %STEMAX, %DEEMAX, %EPSIL, %STMIN,  %UBUF,   %NWBUF);
 }
  END
 
*CMZ :          28/03/98  23.09.07  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  15.03.50  by  Pavel Nevski
*CMZ :  1.00/00 04/09/95  14.29.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                Subroutine   A g S D E T V (title)
*                                                                    *
*  Description: for a given (SET,DET) create GEANT sensetive         *
*  detector with corresponding DETU user structure filled later.     *
* In a Geometry module global %iset,%idet are set only for the call  *
* when this set is created to allow next routine (Agsdetu) to store  *
* hit or digi definitions in DETU bank, otherwise they are set to 0. *
* Local Iset,Idet are save in attributes of each calling Nick volume.*
*    In a Digitisation module global %iset,%idet are set always,     *
*    to allow not only set creation, but a modification as well.     *
***GsDETv definition for DIGI erases Iset,Idet,Idtype in the volume. *
*  this is corrected by saving them in sdt and then restoring attrib.*
***If %Type is changed, a new copy of DETU bank is created and       *
* %iset/%idet are set to allow DETU filling in AgsDETH/AgSDETU       *
*                                                                    *
*  Called from users code at the beginning of the hit definition     *
* 16/05/96 PN: bug corrected in %JDU selection for USER bank change  *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
   Character title*(*),Cdet*4,Cset*4,Cbank*4,T*1,Cpar*4
   Integer   LENOCC,JATTF,JV,J,Iset,Idet,Jdet,Iv,Js,Jd,JDN,JDU,
             NWHI/1000/,NWDI/1000/,Lcumu/15/
   Real      Sdt(3),Upar(%LDETU)" up to 15 levels of volumes and hits "
   JATTF(JV) = JV+int(Q(JV+5))+6
                            * * *
 " Set is always the same as 3 letters of the module name plus H or D "
 T=%EXNAME;  Cset=%Module(1:3)//T;  Cdet=Title;
 { %iset,%idet,Iset,Idet,Jdet,Iv }=0;
 If (Jset > 0)  Call GLOOK(Cset,IQ(JSET+1),IQ(JSET-1),Iset)
 If (Iset > 0)  JDET =LQ(JSET-ISET)
 If (Jdet > 0)  Call GLOOK(Cdet,IQ(JDET+1),IQ(JDET-1),Idet)
                            * * *
 If Iset<=0 | Idet<=0
 {  "              for digi, save previous volume set/det reference       "
    If (T='D') Call GLOOK (Cdet,IQ(JVOLUM+1), Nvolum, Iv)
    If (iv>0)  Call UCopy (Q(JATTF(LQ(JVOLUM-Iv))+7),sdt,3)
    Call GsDETv (Cset,Cdet,%Idtype,NWHI,NWDI,Iset,Idet)
    If Idet<=0|Iset<=0 {error(' can not define sensitive detector ',Title)}
    "              set empty hit or digi bank with maximum size           "
    Call Vzero (Upar,%LDETU)
    If (T='H') Call GsDETH (Cset,Cdet,Lcumu,Cpar,Upar,Upar,Upar)
    If (T='D') Call GsDETD (Cset,Cdet,Lcumu,Cpar,Upar)
    "              now set users bank - also with max.size                "
    Upar(1)=10;  Upar(8)=%Type;   Upar(9)=%Idtype;  Upar(10)=-1;
    Call GsDETU (Cset,Cdet,%LDETU,Upar); %Iset=Iset; %Idet=Idet;
*pn: 16/03/96 - to get nice bank NID reset it for the first bank
    JDU=LQ(LQ(LQ(Jset-Iset)-Idet)-3); Cbank=' ';
    If (JDU>0) Call UHTOC(IQ(JDU-4),4,Cbank,4)
    If Cbank!='SJDU' {error('can not create User Hit/Digi bank for',Cset,Cdet)}
    IQ(JDU-5)=1
 }
                            * * *
 If      %Module(5:5)='G' & T='H' " mark each volume with its HIT set/detector"
 {  j=JATTF(LQ(JVOLUM-%Ivolume)); Q(j+7)=Iset; Q(j+8)=Idet; Q(j+9)=%IdType; }
 else If %Module(5:5)='D' & T='D' " only digitisation re-definition accepted "
 { if(Iv>0) Call UCopy(sdt,Q(JATTF(LQ(JVOLUM-Iv))+7),3);%iset=Iset;%idet=Idet;}
 else       {error('HITS or DIGI can not be redefined for ',Cset,Cdet)}
 
                            * * *
 " find DETU bank with corresponding serial number and keep its link in %JDU "
 JS=LQ(JSET-Iset);  JD=LQ(JS-Idet);  JDU=LQ(JD-3);  %JDU=JDU;
 While Q(JDU+8)!=%Type & LQ(JDU)>0 { JDU=LQ(JDU);   %JDU=JDU; }
 If %Type!=Q(JDU+8)       " make a new user bank "
 {  Call MZBOOK(IxCons,JDN,JDU,0,'SJDU',0,0,%LDETU,3,0)
    If JDN<=0  {error(' cant create new copy of DETU bank ',%Type)}
    Call Ucopy (Q(JDU+1),Q(JDN+1),%LDETU);    Q(JDN+8)=%Type;
    %iset=Iset;  %idet=Idet;  %JDU=JDN;
 }
   END
 
 
*CMZ :          15/02/98  12.51.45  by  Pavel Nevski
*CMZ :  1.30/00 16/04/96  19.12.28  by  Pavel Nevski
*CMZ :  1.00/00 02/06/95  02.20.02  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
***************************************************************************
*                                                                         *
                  Subroutine   A g S D E T H (IEXT)
*                                                                         *
*  Description:  fill the description of a new hit element in DETU.       *
*  In a digitization module a modification mode is also possible.         *
*  Final analyse is done by AggDETV and AggDETU called from AggCLOS.      *
*  This is done on the exit from a geometry module, when all volume       *
*  positionning is finished, or at the end of the DIGI operator           *
*  in a digitization module where positionning is already done.           *
*                Called from users code on each hit element               *
*  Possible hit options are:  C,H,X,R,S - see comments in the code        *
*  If hit code is undefined, an attempt is made to find 'codehit' routine *
*  It is supposed to have same arguments as any user step routine-(j,hit) *
*  Modifications:                                                         *
*  15feb97, PN: Allow less then 4 letters for a 'chit'HIT  routine        *
*                                                                         *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEND.
 Integer     CSADDR,LENOCC,IEXT,Ltab,Ioption,Jdu,Ia,N,Ja,i1,i2,Ifun,k,i,new
 Real        ARFROMC
 Parameter   (Ltab=27)
 Character   T*1, Hit*4, Ctab(Ltab)*4 _
            /'X','Y','Z','R','RR','PHI','THE','ETA','TDR','CT',
             'CX','CY','CZ','ETOT','ELOS','BIRK','STEP','LGAM',
             'TOF','USER','XX','YY','ZZ','PX','PY','PZ','SLEN'/
 
  Check %Idet>0 & %Iset>0 & %Jdu>0;
  " save next hit in DETU bank for a new structure marked by negative U(10) "
  JDU=%Jdu;  Ia=Q(Jdu+1);    N=Q(jdu+2);      Ja=Jdu+Ia+%NwuHit*N;
             Hit=%Parlist;   new=Q(Jdu+10);   T=%EXNAME;
                               * * *
  If new<0                                            " a new hit element "
  {  Ia=Q(Jdu+1);   N=Q(jdu+2);    Ja=Jdu+Ia+%NwuHit*N;
     If (N>=14)    {error('Can not store more hit elements ',N)};
     N+=1;          Q(jdu+2)=N;    Q(jdu+3)=Ia+%NwuHit*N;
     Call  Vzero(Q(Ja+1),10);
     Q(Ja+1)=ARFROMC(%ParList);    Q(Ja+2)=ARFROMC(%Option);
     Q(Ja+3)=%Nbits;   Q(Ja+4)=%FhMin;   Q(Ja+5)=%FhMax;
     If (%bin>0)       Q(Ja+7)=1/%bin;
     If (HIT='USER')   IQ(Ja+9)=IEXT;                " not exportable...   "
     Ifun=0;      k=Lenocc(Hit)                      " hit function code   "
     do i=1,Ltab  { Check Hit(1:k)==Ctab(i)(1:k);    Ifun=i;   break;      }
     If Ifun==0   { IQ(Ja+9)=CSADDR(HIT(1:k)//'HIT') }
*
     Q(Ja+10)=Ifun;  Ioption=Q(Jdu+7);               " global option setup "
     "option H used in AggDETU to mark the start of 'hit' field a la GEANT "
     "option R                 to require bin rounding up to 2 digits      "
     if (Index(%Option,'S')>0) Call SBIT1(Ioption,1) " single step option  "
     if (1 <=Ifun & Ifun<= 10) Call SBIT1(Ioption,2) " local coordinate rq "
     if (Index(%Option,'X')>0) Call SBIT1(Ioption,2) " same explicitly     "
     if (11<=Ifun & Ifun<= 13) Call SBIT1(Ioption,3) " local direction rq  "
     if (Index(%Option,'X')>0) Call SBIT1(Ioption,3) " same explicitly     "
     if (Index(%Option,'C')>0) Call SBIT1(Ioption,4) " Calorimeter option  "
     Q(Jdu+7)=Ioption
  }
  else                               " update an existing hit/digi element "
  {  i1=Q(Jdu+1); i2=Q(Jdu+3);
     do ia=i1,i2-1,%NwuHit
     {  Ja=Jdu+ia;   check Q(Ja+1)=ARFROMC(%ParList)
        If (%Option # '*') Q(Ja+2)=ARFROMC(%Option)
        If (%Nbits#%Magic) Q(ja+3)=%Nbits;  Q(Ja+4)=%FhMin;  Q(Ja+5)=%FhMax;
        If (%bin>0)      { Q(Ja+7)=1/%bin;  Q(Ja+3)=%Magic; }
  }  }
  END
 
 
 
*CMZ :  1.00/00 01/06/95  18.40.03  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                  Subroutine   A g S D E T U (Title)
*                                                                    *
*  Description: in a digitisation module make changes in SET param-s *
*  called from users code at the end of a digi structure description *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
  Character Title*(*),Cdet*4;   Integer Js,Jd,Jdu,new;
 
  Check  %Idet>0 & %Iset>0 & %Jdu>0;      Cdet=Title;
  Jdu=%Jdu;  new=Q(Jdu+10);  Q(Jdu+10)=max(0,%Iprin);
  If (%Module(5:5)='D')
  {  Js=LQ(JSET-%Iset);  Jd=LQ(Js-%Idet);
     if (IQ(JD+9)<0)     IQ(Jd+9)=0;
     if (new<0)   call AgGDETV(Cdet,Jdu);
     call AgGDETU(%Iset,%Idet,JDU,%Iprin);
  }
  { %Iset,%Idet }=0;
  END
 
 
*CMZ :          25/03/98  16.44.21  by  Pavel Nevski
*CMZ :  1.30/00 14/11/96  17.24.24  by  Pavel Nevski
*CMZ :  1.00/00 06/08/95  14.00.59  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Subroutine   A g S R E S E T
*                                                                    *
*  Description: Before each processor call reset WORK2 area to allow *
*               recognition of actual parameters
*               and set some (KONLY,ROTM) defaults                   *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEND.
  Integer LOCF
  Call VZERO(%Reset1,LOCF(%Reset2)-LOCF(%Reset1)+1)
  Call VZERO(%code,  LOCF(%eCode) -LOCF(%Code)  +1)
  %Mother=%Volume; %Konly='ONLY'
  {%Thetax,%Thetay,%Phiy}=90
  END
 
*CMZ :          30/05/97  15.31.01  by  Pavel Nevski
*CMZ :  1.30/00 07/08/96  15.08.41  by  Pavel Nevski
*CMZU:  1.00/01 01/12/95  02.07.10  by  Pavel Nevski
*CMZ :  1.00/00 01/06/95  13.09.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                     Subroutine   A g S P U S H
*                                                                    *
*  Description:  Push the stack at the start-of-block                *
*                redefine parents and set default attributes etc     *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
 Integer       LOCF,LENOCC,L,Iv,IL,NUM/0/
 Real          Volume
 Equivalence   (%Volume,Volume)
 
 If %Mark!='V00'
 { print *,'     ***********************************************************'
   print *,'     ***           FATAL ERROR in ',%Module,'       ***'
   print *,'     *** geant3.def file was changed, delete your *.sl files ***'
           STOP '***********************************************************'
 }
 If (%Level=0) NUM=0
 If %Level>=15 {error('Number of nesting levels is more than 15')}; %Level+=1;
 L=LOCF(%EndSave)-LOCF(%BegCom)
 if (L>%LSTACK) stop 'AgsPUSH Fatal error: lack of stack dimension'
 Call UCOPY (%BegCom, %Stack(1,%Level), L)
 CALL VZERO (%BegScr, LOCF(%EndScr)-LOCF(%BegScr))
 
 %Mother=%Volume;  %Imother=%Ivolume;  %Volume=%Title;
 {%Ivolume,%Istatus,%NLmat,%Isvol}=0;
 Iv=LOCF(Volume)-LOCF(%Begcom)+1;
 Do IL=1,%Level-1
 { IF %Stack(iv,il)=VOLUME {error('Recursive block call not accepted')} }
 Iprin=max(%Iprin-%Level-1,0);   Num+=1;  Prin1 NUM,%level,%L(%Title)
       (/' **',i5,' ** we are at level ',i3,' in block ',A/)
   END
 
*CMZ :  1.30/00 05/08/96  13.22.16  by  Pavel Nevski
*CMZ :  1.00/00 26/12/94  01.37.43  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                     Subroutine   A g S P O P B
*                                                                    *
*  Description:  pop stack at the end-of-block                       *
*                at upper level close hit structure                  *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
 Integer LOCF,LENOCC;
 
 If %Istatus==0 {error('block is empty')};
 If %Level<=0   {error('Stack underflow: nesting level is wrong')};
 Call UCOPY (%Stack(1,%Level), %BegCom, LOCF(%EndSave)-LOCF(%BegCom));
 %Level-=1;  Iprin=max(%Iprin-%Level-1,0);  if (%level>0) return;
   END
 
*CMZ :          20/06/98  13.32.24  by  Pavel Nevski
*CMZ :  1.30/00 13/05/97  14.31.40  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
************************************************************************
*                                                                      *
            Subroutine   A g S B E G M (Module,IPR)
*                                                                      *
*  Description: open a module execution part and control execution     *
*  Print flag is set to the production of both module and stage print  *
*  In a standalone mode all geomtry structures are dropped             *
*  Modifications:                                                      *
*  13/05/97 PN: default FILL (att6) is 0 to cope with 97a black edges  *
*  10.01.98 PN: detm.rz has to be made 'old format' for built in dzdoc *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
   Integer           AgPFLAG,LENOCC,n,m;   parameter   (n=100)
   Character         Module*(*),Stage*4,Cmother*4,Cs*1,Chdir0*6/' '/
   Integer           IPR,i,Idet,Lrecl,Istat,Itry,Lun/61/
   Character*8       CHTAG(2)/'Bank-ID','Bank-ID'/,CHDIR(n)
   Real              Xtime,XXtime
   Common /AgCMTIME/ Xtime,XXtime
   Logical           EXST,Opnd,First/.true./
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
                            * * *
   Check %Module != Module;
   %Module=Module; Cs=Module(5:5);
   If Cs='G'      {Stage='GEOM'} else if Cs='D' {Stage='DIGI'}
   else if Cs='R' {Stage='RECO'} else           {Stage='UNKN'}
   Cmother=' ';    If (JVOLUM>0) CALL UHTOC(IQ(JVOLUM+1),4,CMother,4);
   If Cs='G' { do i=1,5 { %attribute(i)=1; };  %attribute(6)=0 }
                               * * *
   Call AsbDETE (Module,Idet)
   %IdType=Idet;         %Iprin=AgPFLAG(Module,Stage);
   %IMFLd=LVMFLD(Idet);  %Ihist=LVHIST(Idet);  %IGrap=LVGRAP(idet);
   %Igeom=LVGEOM(Idet);  IF (Stage=='RECO')    %Igeom=LVRECO(Idet);
   IPR=%Iprin; Iprin=%Iprin;
*
   "Make a standalone clean up"
   If Cs='G' & Cmother=%Module(1:4) & %Standalone>0
   {  Call AGDROP('*'); If (Idebug>0) Iprin+=1; }
*
   "Make sure minimal GEANT structures are present for G stage "
   If (Cs=='G' ) Call Agstand
*
   prin1 %Module,%Igeom,%Iprin;
   (' Module ',a8,'  running for geometry',i5,'  print level=',i3);
  " try to reduce the amount of prints:" if (Iprin>0) Iprin=Iprin-1;
   if (%Iprin>1)  Call TIMEX(Xtime);
   If %IHIST>0
   {  CALL HCDIR('//PAWC',' ');   CALL HRDIR(n,CHDIR,m)
      Do I=1,m  { Check CHDIR(i)==Module(1:LENOCC(CHDIR(i)))
                  CALL HCDIR(CHDIR(i),' ');  Break;
   }            }
                              * * *
   INQUIRE(FILE='detm.rz',OPENED=opnd)
   If .not.opnd & LVGEOM(1)>=0
   {  Lrecl=256;   INQUIRE(FILE='detm.rz',EXIST=EXST);  %ChDir='RZDOC'
      If !EXST { Call RZOPEN (Lun,%CHdir,'detm.rz','NWX', Lrecl,Istat)
                 Call RZMAKE (Lun,%CHdir,2,'HH',CHTAG,5000,'XO')
                 call RZCLOS (%Chdir,' ')
               }
      Call RZOPEN (Lun,%ChDir, 'detm.rz','UWXD',Lrecl,Istat);
*
* from pawrop:
*--- bug in RZOPEN with C I/O, TOPDIR is not returned correctly ---
*     IF (IOPTC!=0 & LUN <10) WRITE(TOPDIR,'(3HLUN,i1)') LUN
*     IF (IOPTC!=0 & LUN>=10) WRITE(TOPDIR,'(3HLUN,i2)') LUN
*
      Call RZLOGL (Lun,-3);    "  Call RZCDIR (ChDir0,'P') "
      Do Itry=1,2
      {  Call RZFILE(Lun,%ChDir,'UDX'); if (Iquest(1)==0) Break
         Call Rzfree('RZFILE');         Call RZEND(%Chdir)
      }
      If Istat!=0     { <w>; (' detm.rz absent - no documentation available');}
      If Iquest(1)!=0 { <w>Iquest(1);(' problem opening detm.rz, IQUEST=',i6);}
*     Chdir0=%Chdir
   }
   END
 
 
*CMZ :          04/03/98  23.44.07  by  Pavel Nevski
*CMZ :  1.30/00 17/04/97  17.59.21  by  Pavel Nevski
*CMZ :  1.00/00 29/11/95  08.55.19  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                   Subroutine   A g S E N D M
*                                                                    *
*  Description: close the module. In the interactive debug mode      *
*               show documentation banks and draw the detector       *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
   Integer      LZFID,L1,Iv,I,Npar,Key(2)
   Character*4  Cmother
   Real         c,d, Xtime,XXtime,XXi
   Common /AgCMTIME/ Xtime,XXtime
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
 
   Check %Module#' '; Call TIMEX(XXi)
   If %Module(5:5)=='G'                                " geometry module "
   {  Call AgGCLOS;
      Cmother=%Module; If (JVOLUM>0) Call UHTOC(IQ(JVOLUM+1),4,Cmother,4);
      If Cmother=%Module(1:4) & %STANDALONE>0 "Cmother!='ATLS'&Cmother!='CAVE'"
      {  Call GGCLOS;
         If Idebug>1                             " show documentation banks "
         {  Call UCTOH  ('DETMNONE',Key,4,8);
            L1=LZFID (IxCONS,Key(1),Key(2),0); If (L1>0) _
            call DZSURV ('Detector Master Banks',IxCONS,L1)
         }
         If JVOLUM>0 & LKDETM>0 & %IGRAP>=1 & Idebug>0  " draw the detector "
         {  Iv=1;    Npar=Q(LQ(JVOLUM-Iv)+5);
            d=1;     do I=1,min(Npar,3) { d=max(d,Q(LQ(JVOLUM-Iv)+6+i)); }
            c=10/d;  Call GDRAW (Cmother,120.,120.,0.,10.,10.,c,c);
      }  }
   }
*  if %Chdir!=' ' { call RZCLOS (%Chdir,' ');  %Chdir=' ' }
   if (%Chdir!=' ') call RZSAVE
   If %Iprin>1
   { Call TIMEX(XXtime); <W> %module,XXtime-Xtime,XXi-Xtime
     (' Module ',a,' done',11x,'Time=',F8.3,' (proper time=',F8.3,')')
   } %Module=' '
   END
 
 
*CMZ :          09/01/98  03.41.25  by  Pavel Nevski
*CMZ :  1.30/00 02/04/96  20.16.48  by  Pavel Nevski
*CMZ :  1.00/00 29/05/95  16.26.52  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Subroutine   A g G C L O S
*                                                                    *
*  Description:  Fill hit structures for all sensitive detectors     *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
  Character*4 Cset,Cdet
  Integer     IPRIN,Iset,Idet,JS,JD,Jdu
 
  Check Jset>0
  :set: DO Iset=1,IQ(Jset-1)                                 " Over Nset "
  {  JS=LQ(Jset-Iset);   Check JS>0;  Call UHTOC (IQ(Jset+Iset),4,Cset,4)
     :det: DO Idet=1,IQ(LQ(Jset-Iset)-1)                     " Over Ndet "
     {  JD=LQ(JS-Idet);  Check JD>0;  Call UHTOC (IQ(JS + Idet),4,Cdet,4)
        "Find unprocessed banks "     Check IQ(JD+9)=-1;       IQ(JD+9)=0
*      02/04/96: it is possible also to create GEANT multipath by keeping -1.
*      commented out 09.01.98
*      CALL GGDETV(Iset,Idet);
       JS=LQ(Jset-Iset);    JD=LQ(JS-Idet)
*
        JDU=LQ(JD-3);    While JDU>0
        {  Iprin=Q(JDU+10);
           " get  path  "   Call AgGDETV (Cdet,JDU);
           " fill banks "   Call AgGDETU (Iset,Idet,JDU,IPRIN);
           " take next  "   JDU=LQ(JDU);
        }
  }  }
  END
 
*CMZ :  1.30/00 17/11/96  21.30.48  by  Pavel Nevski
*CMZ :  1.00/00 01/01/95  16.58.06  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A g G D E T V (Cdet,JDU)
*                                                                    *
*  Description: given a sensitive detector make a description of     *
*               path (NAMESV,NBITSV) for the hit definition          *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
  Character*4 Cdet
  Integer   Nchild,Ifamily(1000),Level,Idet,Ivol1,Iv,Jv,nin,in,Jd,Id,ip,N1,N2,
            Iprin/9/,Nhisch,Ncopy,Nr,Jp,L,m,Jdu,Ia,N,Ja,Name(20),GName(20),
            NumV(20),Numb(20),Mask(20),NumP(20),NumH(20),Ivol(20)
 
call UCTOH(Cdet,Idet,4,4); call UCTOH('VOL1',Ivol1,4,4);
Level=1;                 {Name(1),Gname(1)}=Idet;
{N1,N2,Mask(1),NumV(1),NumP(1),NumH(1),Nchild}=0;
if (JVOLUM<0) Return;
Do Iv=1,Nvolum
{  Jv=LQ(JVOLUM-Iv);  Check JV>0;  Check IQ(JV-4)=Idet;
   Nchild+=1; Ifamily(Nchild)=Iv;  If (IQ(JVOLUM+Iv)=Idet) Ivol(1)=Iv;
}
If Nchild=0 { <w> Cdet; (' AgGDETV: detector ',a,' not found'); return; }
"<w> cdet,Nvolum,Nchild; (' *** in aggdetv: cdet,nvol,nchild = ',a4,2i6);"
 
Until "Ifamily(Nchild)==0 \" N1>N2  \ Level==20
{  " previous level children are in (N1,N2) range on family "
   N1=N2+1;  N2=Nchild;  Level+=1;  L=Level;
   {Name(L),Gname(L),NumV(L),Numb(L),NumH(L),Mask(L),NumP(L),Ivol(L)}=0;
 
  " select family parents: Iv is parent of Id, Nr is copy number or Ndiv  "
  " Nhisch is the number if his direct counted children (previous level !)"
  " Ncopy is the higher copy number, used for NVL if more than one copy ! "
  " NumP contains total number of found new parents at that level         "
 
   Do Iv=1,NVOLUM                                      " Iv is a parent "
   {  Jv=LQ(JVOLUM-Iv);  nin=Q(Jv+3); Check nin#0;     " He has a child "
      Nhisch=0; Ncopy=0;
      do in=1,max(nin,1)
      {  Jd=LQ(Jv-in); Id=Q(Jd+2); Nr=Q(Jd+3);         " - is his child "
         do ip=N1,N2                                   " in the family? "
         {  Check Id==Ifamily(ip);                     "   Yes !        "
            Nhisch+=1; Ncopy=max(Ncopy,Nr);
            "mark this parent as a next level child (If not marked yet) "
            Do jp=n2+1,Nchild { If (Ifamily(jp)==Iv) go to :known:; }
            if Nchild<1000    { Nchild+=1;  Ifamily(Nchild)=Iv; }
            else {<W> Cdet;(' AgGDETV error: too many parents of ',a);Return;}
            :known:        " -  find its generic name ";
            If IQ(Jv-4)#Ivol1 { Gname(Level)=IQ(Jv-4); }
            else              { Gname(Level)=IQ(JVOLUM+iv); };
            " make XOR name and mask - and select NameSV name "
            Name(Level)=IOR(Name(Level),IQ(JVOLUM+Iv));
            Mask(Level)=IOR(Mask(Level),IEOR(Name(Level),IQ(JVOLUM+Iv)));
            If (Name(level)==Gname(Level)) Ivol(Level)=Iv;
            If  (Iv=1)  NumV(Level)=1;
      }  }  L=Level-1;
 
      " skip counting if one child only is positioned "
      Unless (Nin>0 & Nhisch<=1) NumH(L)=max(NumH(L),Ncopy)
      NumV(L)=max(NumV(L),Ncopy) " but remember anyway its copy number "
      NumP(Level)=Nchild-N2      " and count how many branches we have "
   }
   If Ivol(Level)==0 " active daughters are positioned NOT in the first copy "
   { Do Iv=1,Nvolum  { If (Gname(Level)==IQ(JVOLUM+iv)) Ivol(Level)=Iv;  } };
   Numb(L)=0; If (NumH(L)>0) { m=NumV(L)-1; while m>0 { m/=2; Numb(L)+=1; }};
   If (Jdu>0) Iprin=Q(Jdu+10);
   Prin5  L,NumP(L),Name(L),Gname(L),NumH(L),NumV(L),Numb(L),Mask(L),Ivol(L);
         (2i6,2(2x,A4),3i6,1x,Z8,i8);
}  Level=Level-2;
   If Jdu>0
   {  Do L=Level,1,-1
      {  Ia=Q(Jdu+3);      N=Q(jdu+4);       Ja=Jdu+Ia+N*3;   "<<start<<"
         Q(Ja+1)=Ivol(L);  Q(Ja+2)=NumV(L);  Q(Ja+3)=Numb(L); " 3 words "
         N+=1;             Q(jdu+4)=N;       Q(jdu+5)=Ia+N*3; "<< stop<<"
   }  }
   END
 
*CMZ :  1.30/00 09/09/96  16.45.51  by  Pavel Nevski
*CMZ :  1.00/00 06/06/95  00.08.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
              Subroutine   A g G D E T U (Iset,Idet,Jdu,IPRIN)
*                                                                    *
*  Description: calculate Nbit,Origin and Factors for hit/digi sets  *
*               and fill DET,DETH/DETD banks starting from DETU bank *
*  ->           Parameters NwuHit,NwuVol,Magic are hardwired here    *
*  ->31.8.96:   Nbit option use full 2**Nbit range,                  *
*               Bin option has its range symmetrise around the center*
**********************************************************************
Replace[ERR(#)] with _
       [<W> Cset,Cdet; (' AgGDETU error for set,det=',2(1x,a));
         Write (Lout,*) ' ******> ',#1; RETURN;              ];
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEND.
 
 Character*4 ACFROMR,Cset,Cdet,Chit,Copt
 Integer     INDEX,IPRIN,Iset,Idet,Js,Jd,Jdu,Jx,i,i1,i2,J,K,L,M,N,X,Mode,Node,
             Nbit,Nbin,Nb,Nam,iv,Kv,Nv,Nn,Nh,Nw,Nwo,Lf,Ifun,Ld,Lx,Ldu,Jds,Lex,
             JL,NameV(20),NbitV(20),LL(2)/10,3/,Magic/-696969/
 Real        Lfact,Fmin,Fmax,Orig,Fact,Range,ofs,
             Log2/.30103/,safety/0.02/
 
  Check  Jset>0 & Idet>0 & Iset>0;
  JS=LQ(Jset-Iset);  Check JS>0;  Call UHTOC (IQ(Jset+Iset),4,Cset,4);
  JD=LQ(JS - Idet);  Check JD>0;  Call UHTOC (IQ(JS + Idet),4,Cdet,4);
  If Cset(4:4)='H'  {X=1}  else  If Cset(4:4)='D'  {X=2}
  else              {err('can not decode set type ')};       Ld =IQ(JD-1);
  JX =LQ(JD-X); If JX <=0 {err('hit/digi bank not found ')}; Lx =IQ(JX-1);
 "Jdu=LQ(JD-3)" If Jdu<=0 {err('No  user bank  defined  ')}; Ldu=IQ(Jdu-1);
  Prin2  Cset,Cdet; (/' *** ',2(1x,A4),' *** ');
 
  "reset volumes and hit counters " {Nn,Nv,Nw,K,Kv,Nh,Nwo,Mode,Node} =0;
  Do M=2,0,-2
  {  i1=Q(Jdu+M+1); i2=Q(Jdu+M+3); N=Q(Jdu+M+2); Check N>0; L=(i2-i1)/N;
     If L#LL(1+M/2) | 1>N|N>15 | i2>Ldu | i1<10
        {err('Bad format of DETU bank, M,i1/2,N=',M,I1,I2,N)}
     do i=i1,i2-1,L
     {  j=Jdu+i; If M==2   " - - - - - - - volumes - - - - - - - - "
        {  iv=Q(j+1); Nam=IQ(JVOLUM+iv); {Nbit,Nb}=Q(j+3); Check Nb>0; Kv+=1; }
        else               " - - - - - - - - hits  - - - - - - - - "
        {  Chit=ACFROMR(Q(j+1)); Copt=ACFROMR(Q(j+2)); Call UCTOH(Chit,nam,4,4)
          " Limits will be re-calculated If Q(4)>=Q(5), ifun is not redefined "
           Ifun=Q(j+10); Call AgGFLIM(Chit,Cdet,Q(j+4),Q(j+5),Ifun);
                                  * * *
          " mode=1 means commulative part, node=1 - users request for hit part"
           Nbit=Q(j+3);  Fmin=Q(j+4);   Fmax=Q(J+5);   Fact=Q(J+7);
           If Index(Copt,'H')>0             { K=0;    Node=1;  }
           If -32<=Nbit&Nbit<=0 & Mode=0    { K=0;    Mode=1;  }
           If Fmin==Magic & Fmax==Magic & Nbit>0
           {  ofs=0;  if (i==i1 & Q(LQ(JD-3)+8)>Magic) ofs=Q(LQ(JD-3)+8)
              Fmin=ofs-0.5; if (Index(Copt,'F')>0) Fmin=ofs; Fmax=Fmin+2**Nbit;
           }
           "   Define Range (for a cumulative mode Origin is always 0)    "
           Orig=0;  If (mode=0) Orig =-Fmin;  Range=Orig+Fmax;
           If (Range<=0) <w> Cset,Cdet,Chit,Fmin,Fmax; (' Error in',2(1x,a4),
             ': HITS/DIGI element ',a4,' has invalid range',2E12.3/,
             ' *** Probably this shape is still absent in GFLCAR/RAD/etc ***'/,
             ' *** You should set limits for this element explicitely !! ***')
                                  * * *
           If Nbit>=-32                                        " Nbit option "
           {  "             Nb is always from 1 to 32                   "
              Nb=min(32,abs(Nbit));  If (Nb=0) Nb=32;
              " 31.08.96:  use all bit combination without last spare   "
              Fact=1;  If (Range>0)  Fact=2.**min(31,Nb)/Range;
              "     if rounding option, factors mantissa is 2 digits    "
              If Index(Copt,'R')>0 & Range>0
              {  Lfact=Log2*min(Nb,31)-log10(Range)-safety;
                 Lf=nint(Lfact-1.5); Fact=nint(10.**(Lfact-Lf))*10.**Lf;
           }  }
           else                                              " fix bin option "
           {  Nbin=Range*Fact+0.99; Range=Nbin/Fact;         " ? to continue? "
              Nb=0;  while Nbin>0 { Nbin/=2; Nb+=1; };
              Nb=min(max(1,Nb),32);
           }
           if (Mode=0) Orig=-(Fmax+Fmin-Range)/2         "  - symmetrise  "
           Q(J+5)=Fmax;  Q(J+6)=Orig;  Q(J+7)=Fact;  Q(J+8)=Nb;
           Prin3 Chit,Ifun,Nb,Fmin,Fmax,Orig,Fact;
           (' hit = ',A4,' cod,nb=',2i3,' min/max,orig,fact=',3F10.3,G12.3);
        }
        " count packed words and the remaining bits "
        If  Nb>K   { Nw+=1; K=32; };    K-=Nb;
        Nn=min(Nn+1,20); NameV(Nn)=Nam; NbitV(Nn)=Nb*(1-2*mode);
                                  * * *
        If Mode=0 & Node=0            " overwrite SEJD detector bank in SETS "
        {  if 2*(nv+1)+10>Ld | Nv>=20
              {err('unsufficient length of the detector bank in SETS',ld,nv)};
           Nv+=1;  IQ(Jd+2*nv+9)=Nam;   nwo=nw;
                   IQ(Jd+2*nv+10)=max(IQ(Jd+2*nv+10),Nb);
        }  else                       " overwrite SJDH or SJDD hit/digi bank "
        {  if (Nh+1)*(4/X)>Lx | Nh>=20
              {err('unsufficient length of DETH or DETD bank in SETS',lx,nh)};
           Nh+=1;  Jx=Jx+1; IQ(Jx)=Nam; Jx=Jx+1; IQ(Jx)=max(IQ(Jx),Nb);
           if X=1 {Jx=Jx+1; Q(Jx)=Orig; Jx=Jx+1;  Q(Jx)=Fact; }
        }
  }  }
  Prin2 (NameV(i),i=1,Nn); (/' NameV : ',20(2x,A4));
  Prin2 (NbitV(i),i=1,Nn); ( ' NbitV : ',20(i4,2x));
  Prin3   Cset,Cdet;       (' *** ',2(1x,A4),' *** '/);
 *                                          this is maximum number of:
 J=JD+2*X;   if  Jdu=LQ(JD-3)   {{IQ(JD+1),IQ(JD+2),IQ(J+1),IQ(J+2)}=0;}
 IQ(JD+1) = max(IQ(JD+1),Nwo)   " words to store packed volume numbers";
 IQ(JD+2) = max(IQ(JD+2),Nv)    " volume descriptors in detector bank ";
 IQ(J+1)  = max(IQ(J+1),Nw-Nwo) " words to store packed hits or digi  ";
 IQ(J+2)  = max(IQ(J+2),Nh)     " hit/digi descriptors in DETH/D bank ";
 Q(Jdu+6) = Kv      " number of geometry branchings - really volumes  ";
 *
 *                                          trim hit/digi/user banks
      Lex=IQ(Jdu-1)-nint(max(Q(Jdu+3),Q(Jdu+5)));
          If (Lex>0) Call MZPUSH(IxCons,Jdu,0,-Lex,'I')
      Lex=IQ(JD-1)-10-2*IQ(JD+2);
 *     original SEJD bank was 100, but GGDETV may change it - then leave it
          If (Lex>0 & IQ(JD-1)==100) Call MZPUSH(IxCons,JD, 0,-Lex,'I')
      JL=JX; JX =LQ(JD-X);  Lex=IQ(JX-1)-(JL-JX);
          If (Lex>0) Call MZPUSH(IxCons,JX, 0,-Lex,'I')
 
 Nv=IQ(JD+2); Do i=kv+1,nv
 { jds=LQ(JD-3); while Jds>0 { Q(Jds+10*(i-kv)+8)=IQ(JD+10+2*i); jds=LQ(jds)} }
 *
  END
 
*CMZ :  1.30/00 17/11/96  21.31.31  by  Pavel Nevski
*CMZ :  1.00/00 22/09/95  18.08.16  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
      Subroutine   A g G F L I M (CHit,Cdet,CLo,CHi,Ifun)
*                                                                    *
*  Description: set limits for a hit using GEANT volume dimensions   *
*  Modifications:                                                    *
*  12/11/96 - only if both limits are not defined explicitly.        *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEND.
 
  Integer      Ifun,iax,Magic/-696969/
  Real         Clo,Chi,CL,CH,dens,Step2,Step3
  Character*4  Cdet,Chit
 
  Check (Clo==%Magic | Chi==%Magic)
If 1<=Ifun & Ifun<=9    "x,y,z,r,rr,phi,the,eta,tdr"
{  iax=Ifun; If (Ifun=8) iax=7; If (Ifun=9) iax=4;
   Call AgGFDIM (iax,Cdet,CL,CH,dens);
   If Ifun=8 { " instead of Rap(CL,CH)" CL=-5; CH=+5; }
}
If 15<=Ifun & Ifun<=17  "step and energy losses"
{  Step2=0; Step3=1; do iax=1,3
   { Call AgGFDIM (iax,Cdet,CL,CH,dens);
     Step2=Step2+(CH-CL)**2;  Step3=Step3*abs(CH-CL);
   } Step2=Sqrt(Step2);   If (Step3>0) Step3=Step3**0.333333;
}
*                               set measurement default limits
 If Ifun=10               "Cp"     { CL=-1;     CH=+1;      }
 If 11<=Ifun&Ifun<=13  "cx,cy,cz"  { CL=-1;     CH=+1;      }
 If Ifun=14              "ETOT"    { CL=0;      CH=1000;    }
 If Ifun=15 | Ifun=16    "ELOS"    { CL=0;      CH=.01*dens*step3; }
 If Ifun=17              "STEP"    { CL=0;      CH=Step2;   }
 If Ifun=18              "Lgam"    { CL=0;      CH=10;      }
 If Ifun=19              "TOF "    { CL=0;      CH=TOFMAX;  }
 If Ifun=20              "USER"    { CL=%Magic; CH=%Magic   }
 If 21<=Ifun&Ifun<=23  "XX,YY,ZZ"  { CL=-1000;  CH=1000;    }
 If 24<=Ifun&Ifun<=26  "PX,PY,PZ"  { CL=-1000;  CH=1000;    }
 If Ifun=27              "SLEN"    { CL=0;      CH=10000;   }
 If Ifun=28              "SHTN"    { CL=%Magic; CH=%Magic   }
 If Ifun>0  { If (Clo=%Magic) Clo=CL; If (Chi=%Magic) Chi=CH; }
   END
 
 
 
 
*CMZ :  1.30/00 17/11/96  21.32.11  by  Pavel Nevski
*CMZU:  1.00/01 27/01/96  22.06.24  by  Pavel Nevski
*CMZ :  1.00/00 04/09/95  14.29.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
          Subroutine   A g G F D I M (Iax,Cdet,Cl0,Ch0,dens)
*                                                                    *
*  Description: given a sensetive volume and axis, find its dimension*
*             Just a continuation of AgGFLIM splitted for convenience*
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEND.
 
 Integer     Idet,Iax,Nvol,Iv,Jv,Ish,Imo,Jmo,Nin,In,Ida,NR,
             IDH,Jda,Npar,Natt,Ier,Numed,Nmat
 Real        CL0,CH0,CL,CH,dens,xyz(3),Par(100),Att(20)
 Character*4 Cdet
 Data        xyz/3*0/
 
 CL0=+1.e10; CH0=-1.e10;            Check 1<=Iax & Iax<=8;
 Check JVOLUM>0; NVOL=IQ(JVOLUM-1); Call UCTOH(Cdet,Idet,4,4);
Do Iv=1,Nvol
{  Jv=LQ(JVOLUM-Iv);               Check JV>0;
   Ish=Q(Jv+2);  IDH=IQ(Jv-4);     Check Idet==IDH;
   numed=Q(Jv+4);  if (numed>0 & JTMED>0) Nmat=Q(LQ(JTMED-numed)+6);
                   If (Nmat>0  & JMATE>0) dens=Q(LQ(JMATE-Nmat)+8);
   Do Imo=1,Nvol
   {  Jmo=LQ(JVOLUM-Imo); Check Jmo>0;  Nin=Q(Jmo+3);
      do In=1,Abs(Nin)
      {  Jda=LQ(Jmo-In);  Check Jda>0;  Ida=Q(Jda+2);
         NR=Q(Jda+3);     Check Ida=Iv; Npar=Q(Jv+5);
         Call GFIPAR(Jv,Jmo,In, Npar,Natt,Par,Att)
         IF Npar<=0 | Npar>50
         { <W> Cdet; (' AgGFDIM: still error in GFIPAR for volume ',a4/,
                      ' ***** PLEASE USE EXPLICIT HIT LIMITS *****')
           next
         }
         if      Iax<=3  {  call GFLCAR (Iax,Ish,0,    Par,CL,CH,ier);  }
         else if Iax<=5  {  call GFLRAD (Iax,Ish,0,xyz,Par,CL,CH,Ier);  }
         else if iax==6  {  call GFLPHI (    Ish,0,xyz,Par,CL,CH,Ier);
                            if (CL>CH) CL-=360; CL*=DegRad; CH*=DegRad; }
         else if iax==7  {  call GFLTHE (    Ish,0,xyz,Par,CL,CH,Ier);
                                                CL*=DegRad; CH*=DegRad; }
 
         CL0=min(CL0,CL);   CH0=max(CH0,CH);
}  }  }
   END
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 16/03/97  14.27.55  by  Pavel Nevski
*CMZU:  1.00/01 29/01/96  13.26.30  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                  Subroutine   A g G S T E P (Iret)
*                                                                    *
*    Description: general gustep for any detector with auto-hits     *
*    Scan and fill the hit structure for all sensitive detectors     *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCTMED.
      COMMON/GCTMED/NUMED,NATMED(5),ISVOL,IFIELD,FIELDM,TMAXFD,STEMAX
     +      ,DEEMAX,EPSIL,STMIN,CFIELD,PREC,IUPD,ISTPAR,NUMOLD
      COMMON/GCTLIT/THRIND,PMIN,DP,DNDL,JMIN,ITCKOV,IMCKOV,NPCKOV
C
      INTEGER       NUMED,NATMED,ISVOL,IFIELD,IUPD,ISTPAR,NUMOLD
      REAL          FIELDM,TMAXFD,STEMAX,DEEMAX,EPSIL,STMIN,CFIELD,PREC
      INTEGER       JMIN,NPCKOV,IMCKOV,ITCKOV
      REAL          THRIND,PMIN,DP,DNDL
C
*KEEP,GCSETS.
      COMMON/GCSETS/IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV(20)
C
      INTEGER       IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,agcstep.
* Connection between AgGSTEP, AgGHIT and a user step routine.
      Real              vect0,vloc0,vloc,xloc,Astep,Adestep,Hits
      COMMON /AGCSTEP/  vect0(7),vloc0(7),vloc(7),xloc(7),
     +                  Astep,Adestep
      COMMON /AGCSTEPH/ Hits(15)
      Integer           IhaveMore
      COMMON /AGCSTEPI/ IhaveMore
*
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
 Real      Org,Fct,Fmx,Hit,AgGHIT,Serial,xx,h1,Gold
 Integer   JBIT,JATTF,LWSTEP,LDETE,Jj,JS,JD,i,j,k,i1,i2,Nb,Ih,Jh,Jv,Idevt0,
           iv,iw,Nlev,Jat,Ihit,Ic,Iad,Id,Iopt,Iret,Itr,JDH,Jds,mode,mec,itry,
           Iprin,Isimu,bin,Nbr,Jdu/0/,Id0/-1/,NwuVol/3/,NwuHit/10/,Inpu/-1/
 Save      Jdu,iv,iw,Iprin,Isimu,Iopt,Id0,Serial,Gold,Idevt0
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
 LWSTEP(IIIII) = IQ(LQ(LKDETM-IIIII)+13)
 LDETE (IIIII) = IQ(LQ(LKDETM-IIIII)-1)
 JATTF(Jj)     = Jj+int(Q(Jj+5))+6
 bin(xx)       = Ifix((xx+org)*fct)
*
* - - - - - - - - - - - - - print control - - - - - - - - - - - -
 If (Idevt!=Idevt0&LkDETM>0) Call GLOOK('TRAC',IQ(LKdetm+1),IQ(LKdetm-1),Id0);
 Idevt0=Idevt;  Jat=JATTF(LQ(JVOLUM-LVOLUM(Nlevel)));  Id=Q(Jat+9);  Iprin=0;
 If Idebug>0 & LkDETM>0
 {  If (Id>0)  Iprin = LVPRIN(Id)
    If (Id0>0) Iprin*= LVPRIN(Id0)
    Iprin = max(Iprin,Idebug)
    If (iw!=IQ(JVOLUM+LVOLUM(Nlevel))&Iprin>0 | Nlevel+Iprin>15) Call Gdebug
        iw= IQ(JVOLUM+LVOLUM(Nlevel))
 }
* - - - - - - - - - - - - - energy correction - - - - - - - - - -
 If LKDETM>0 & Id0>0
 {  if (sleng==0)  Gold=GeKin
    If Istop>0 & 2<=Ipart & Ipart<=3 & NGKINE<2 & LVSIMU(id0)>0
    {  Mec=0;  Do i=1,Nmec { If (Lmec(i)==30 | Lmec(i)==11) Mec=Lmec(i) }
       If (Ipart==3 & NGKINE==0 & Mec==30) dEstep=Gold
       If (Ipart==2 & NGKINE<=1 & Mec==11)
       {   dEstep=Gold+2*emass;  If (NGKINE==1) dEstep-=GKIN(4,1);    }
    }  Gold=Gekin
 }
* - - - - - - - - - - - - - - - - user - - - - - - - - - - - - - -
 AdEstep+=DeStep;     Astep+=Step;      Iret=Id;
 If LKDETM>0 & Id>0          " permanent user tracing routine needed "
 { Iad=0; If (LdetE(id)>12) Iad=LWSTEP(Id); If (Iad!=0) Call JUMPT0(Iad); }
 If (isvol<=0)  Go To :done:;           Iret=0;
* - - - - - - - - - - - - - - - - sensitive - - - - - - - - - - -
 If  InwVOL==1
 { " If sensitive detector, find it's description banks a la GFINDS "
   Do Nlev=Nlevel,1,-1
   { Jat=JATTF(LQ(JVOLUM-LVOLUM(Nlev))); If (Q(Jat+8)>0) goto :sens:; };
   { IHset,IHdet,Iset,Idet,IDtype,NVname,Jdu }=0;        goto :done:;
   :sens:                               " now fill GCSETS "
   Iset=Q(Jat+7);    Js=LQ(Jset-Iset);  IHset=IQ(Jset+Iset);
   Idet=Q(Jat+8);    Jd=LQ(Js - Idet);  IHdet=IQ(Js  +Idet);
   IdType=Q(Jat+9);  Serial=Q(Jat+10);  NVname=IQ(Jd+2);
   Jdu=LQ(Jd-3);     Iret=Jdu;
   If jdu>0
   { i1=Q(Jdu+3);  i2=Q(Jdu+5);  {jv,iv}=0;
     do i=i1,i2-1,NwuVol         " - - - - - - - volumes - - - - - - - - "
     {  jv+=1; Nb=Q(jdu+i+3); Check Nb>0; iv+=1; NUMBV(iv)=NUMBER(jv)-1;
        If (NUMBV(iv)<0) <w> IHset,IHdet,iv,NUMBER(jv)
        (' AgGSTEP error in ',2(1x,a4),' at level',i5,' NUMBER=',i6)
     }
     Isimu=1;  If (IdType>0 & LKDETM>0) Isimu=LVSIMU(IdType)
     Iopt=Q(Jdu+7);               {Astep,AdEstep}=0;
     Call UCOPY(vect,vect0,7);     Vloc0(7)=Vect(7)
     If (Jbit(Iopt,2)>0) Call GMTOD(vect,vloc0,1)
     If (Jbit(Iopt,3)>0) Call GMTOD(vect(4),vloc0(4),2)
 } }
* - - - - - - - - - - - - - -
 If STEP>0 & Jdu>0 & Isimu>0
 {  If (Charge=0 & AdEstep=0)                go to :done:;
    "  Single hit option - only entry and exit are registered by user  "
    If (Istop=0 & InwVol<2 & Jbit(Iopt,1)>0 & aStep<SteMax) go to :done:
    If (Isimu>1 & Istak>0)                   Call AgSKING
*
    If Jbit(Iopt,2)>0                     " calculate the middle position "
    { Call GMTOD(vect,vloc,1);       do i=1,3 { xloc(i)=(vloc(i)+vloc0(i))/2.}}
    If Jbit(Iopt,3)>0                     " calculate the middle cosines  "
    { Call GMTOD(vect(4),vloc(4),2); do i=4,6 { xloc(i)=(vloc(i)+vloc0(i))/2.}}
    Vloc(7)=Vect(7);                            xloc(7)=(vloc(7)+vloc0(7))/2.
*
    Itr=ITRA;  If (Jbit(Iopt,4)>0) Itr=1;  IhaveMore=0;
    Loop
    {"  reaccess Jdu, it might move since we entered the volume "
     Js=LQ(Jset-Iset);  Jd=LQ(Js-Idet);  JDU=LQ(Jd-3);  Iret=Jdu;
     i1=Q(Jdu+1);  i2=Q(Jdu+3);  jv=iv;  ih=0;  jh=0;  JDH=Jd+10+2*iv;
     K=0;
     do i=i1,i2-1,NwuHit        " - - - - - - - - hits  - - - - - - - - "
     {  j=jdu+i;  Fmx=Q(j+5); Org=Q(j+6); Fct=Q(j+7); Iad=IQ(j+9); ic=Q(j+10);
        hit=serial;
        If   Iad==0   { hit=AgGHIT(ic)           }
        else If ic>0  { Call JumpT2(Iad,j,hit)   }
        else          { Call CSJCAL(Iad,2, j,hit,0,0,0, 0,0,0,0,0) }
 
        " special case for phi(0,2pi) and rapidity(0,max) -> Org=-Fmin "
        If "phi"  ic==6  { If (Org<=0 & Fmx>6.28 & hit<0) hit+=TwoPi;  }
        If "eta"  ic==8  { If (Org<=0 &            hit<0) hit=-hit;    }
        K+=1; Hits(k)=hit;
     }
     K=0;  Jds=Jdu;  h1=hits(1);  Mode=0
     do i=i1,i2-1,NwuHit        " - - - - - now make binning  - - - - - "
     {  j=jds+i;  Fmx=Q(j+5); Org=Q(j+6); Fct=Q(j+7); Nb=Q(j+8); Nbr=Q(j+3)
        " NB: Nb is always positive, only Nbr keeps track of REQUESTED Nb "
 
        K+=1;      hit=max(-Org,HITS(k))
        If jv<NVname        "  pseudo-volumes - may change SJDH content   "
        { jv+=1; NumBV(jv)=bin(min(hit,Fmx-.1/fct));
                 JDH+=2;IQ(JDH)=mod(Nb,32);              }
        else                " hit part - may be only partially comulative "
        { ih+=1; Hits(ih)=min(Hit,Fmx-1.1/fct);
                 if (-32<=Nbr&Nbr<=0) Mode=1; jh+=Mode;  }
 
        " select the appropriate hit descriptor using the first hit element "
        If K==1
        { while LQ(Jds)>0 & bin(Q(LQ(Jds)+8))<=NumBv(jv) {Jds=LQ(Jds)} }
     }
    " all non-comulative AGI hits before opt=H are stored in the volume part "
     If IEOTRI==0
     { do itry=1,2
       { Call GSCHIT(Iset,Idet,Itr,NumBV,Hits,jh,Ihit);    if (ihit>0) break
         If itry==1 { call mzgarb(2,0); call mzgarb(20,0); call mzdred(20);}
         else       { IEOTRI=1; IQUEST(1)=0;  Call GPCXYZ;
                      <w> IHset,IHdet;(' AGGSTEP cant store hits in',
                          2(1x,a4)/' **** event simulation abandoned ****');
     } }            }
    } while IhaveMore>0
    Call UCOPY(vect,vect0,7); call Ucopy(vloc,vloc0,7); {Astep,AdEstep}=0;
 }
 :done:; " If  NGKINE>0 { Call GSKinG (0); NGKINE=0; } - now in gustep "
   END
 
 
*CMZ :          08/08/97  11.42.02  by  Pavel Nevski
*CMZ :  1.30/00 02/04/96  14.53.21  by  Pavel Nevski
*CMZ :  1.00/00 31/05/95  23.17.43  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                    Function     A g G H I T (ic)
*                                                                    *
*  Description:  general hit coding for any standard detector        *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCTMED.
      COMMON/GCTMED/NUMED,NATMED(5),ISVOL,IFIELD,FIELDM,TMAXFD,STEMAX
     +      ,DEEMAX,EPSIL,STMIN,CFIELD,PREC,IUPD,ISTPAR,NUMOLD
      COMMON/GCTLIT/THRIND,PMIN,DP,DNDL,JMIN,ITCKOV,IMCKOV,NPCKOV
C
      INTEGER       NUMED,NATMED,ISVOL,IFIELD,IUPD,ISTPAR,NUMOLD
      REAL          FIELDM,TMAXFD,STEMAX,DEEMAX,EPSIL,STMIN,CFIELD,PREC
      INTEGER       JMIN,NPCKOV,IMCKOV,ITCKOV
      REAL          THRIND,PMIN,DP,DNDL
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,agcstep.
* Connection between AgGSTEP, AgGHIT and a user step routine.
      Real              vect0,vloc0,vloc,xloc,Astep,Adestep,Hits
      COMMON /AGCSTEP/  vect0(7),vloc0(7),vloc(7),xloc(7),
     +                  Astep,Adestep
      COMMON /AGCSTEPH/ Hits(15)
      Integer           IhaveMore
      COMMON /AGCSTEPI/ IhaveMore
*
*KEND.
 REAL             AgGHIT,VDOTN,VDOT,Hit,V(3),R,THE,VMOD,
                  a(2),c(2),dk,da,Vec(2)
 Integer          IC,JMP,i,IcMax/27/
 
 AgGHIT=-9999;    If (0>Ic | Ic>IcMax) Return;      hit=0;
 
 Case  IC of ( X  Y  Z   R    RR   PHI  THET ETA  TDR CP    _
               U  V  W   ETOT ELOS BIRK STEP LGAM TOF USER  _
               XX YY ZZ  PX   PY   PZ   SLEN                )
 {
  :X:;:Y:;:Z: hit=Xloc(ic);                                              Break;
  :R:         hit=VMOD(Xloc,2);                                          Break;
  :RR:        hit=VMOD(Xloc,3);                                          Break;
  :PHI:       If (xloc(1)#0|xloc(2)#0) hit=ATAN2(xloc(2),xloc(1));       Break;
  :THET:      R=VMOD(xloc,3); if (R>0) hit=ACOS(xloc(3)/R);              Break;
  :ETA:       Do i=1,3 { V(i)=(Vect(i)+Vect0(i))/2 }
              R=VMOD(V,3); if (R>0) THE=ACOS(V(3)/R)
              hit=-ALOG(TAN(min(max(1.e-6,THE),pi)/2));                  Break;
  :TDR:       " vector a=vloc-vloc0"   Call vsub(vloc,vloc0,a,2);
              da=vdot(a,a,2);  dk=-1;  if (da>0) dk=-vdot(a,vloc0,2)/da;
              If 0<= dk&dk <=1 "point is insided, vec=vloc+a*dk "
                   { Call Vlinco(vloc0,1.,a,dk,Vec,2); hit=VMOD(Vec,2);}
              Else { hit=min(VMOD(vloc0,2),VMOD(vloc,2)) };              Break;
  :CP:        " vector a=vloc-vloc0"   Call vsub(vloc,vloc0,a,2);
              Call Vlinco(vloc0,-1.,a,-0.5,c,2); hit=vdotn(a,c,2);       Break;
  :u:;:v:;:w: i=ic-10+3;   hit=Xloc(i);                                  Break;
  :ETOT:      hit=GETOT;                                                 Break;
  :ELOS:      hit=aDeStep;                                               Break;
  :BIRK:      hit=aDeStep; Call GBIRK(hit);                              Break;
  :STEP:      hit=aStep;                                                 Break;
  :LGAM: hit=-999; IF(AMass>0&GEKin>0&Charge#0) Hit=ALOG10(GEKin/AMass); Break;
  :TOF:       hit=TOFG;                                                  Break;
  :USER:      hit=aDeStep;                                               Break;
  :XX:;:YY:;:ZZ:  i=ic-20; Hit=(Vect(i)+Vect0(i))/2;                     Break;
  :PX:;:PY:;:PZ:  i=ic-20; Hit=(Vect(i)*Vect(7)+Vect0(i)*Vect0(7))/2;    Break;
  :SLEN:      hit= Sleng;                                                Break;
 }
2 AgGHIT=hit;
   END
 
*CMZ :  1.30/00 03/07/96  18.18.58  by  Pavel Nevski
*CMZ :  1.00/00 05/06/95  16.16.44  by  Pavel Nevski
*-- Author : Pavel Nevski
**********************************************************************
*                                                                    *
             Function     A g F H I T 0 (Cset,Cdet)
*                                                                    *
*  Description: only general digitization control here               *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEND.
Character*(*)  Cdet,Cset
Integer        AgFHIT0,AgFDIG0,AgsDIG0,AgPFLAG,I,J,L,ok/0/
*
   AgFHIT0=-1;   Cs=Cset(1:3)//'H';   Cd=Cdet
   IPRIN = AgPFLAG (Cset,'DIGI');     Check Iprin>=0
   If (IPRIN>=5) CALL AGPDIGI (Cs,Cdet)
*
   AgfHIT0  = AgFDIG0 (Cs,Cdet)
   if AgFHIT0==ok { I = AgSDIG0 (Cset(1:3)//'D',Cdet) }
   else           { prin4 AgfHIT0,cs;(' AgFHIT0=',i3,': no hits found in ',a)}
   If Iprin>=15
   {  <w>;  (' *** AGFHIT buffer  ***');  j=1;  while Ibuf(j)>0
      {  L=IBUF(j); if (L<=0) Break; <w> j,L,(Ibuf(j+i),i=1,L);
         (' adr=',i6,' L=',i4,2x,20i5/(20x,20i5));      j+=L+1;
   }  }
   END
 
 
*CMZ :  1.30/00 25/06/96  13.21.46  by  Pavel Nevski
*CMZ :  1.00/00 05/06/95  12.50.41  by  Pavel Nevski
*-- Author : Pavel Nevski
**********************************************************************
*                                                                    *
     Function     A g F H I T 1 (NHit,LTRA,ISC,HITS)
*                                                                    *
* Description:  only general digitization print control here         *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEND.
Integer      AgFHIT1,AgFDIG1,Nhit,LTRA,ISC(*),ok/0/
Real         HITS(*)
*
   AgFHIT1=AGFDIG1(NHit,LTRA,ISC,HITS); If (AgFHIT1==ok) Return;
*
   Prin2 Cs,Cd,nc1,nc2,iws(1)
   (' AGFHIT1: set/det=',2(1x,a),' hits analysed=',2i8,' digits done=',i8)
   if (Iprin>=4)  Call AGPDIGI(cs(1:3)//'D','*')
   END
 
 
*CMZ :  1.30/00 12/07/96  09.34.13  by  Pavel Nevski
*CMZ :  1.00/00 01/05/95  14.09.00  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/12/94
************************************************************************
*                                                                      *
                 Function  A G S D I G 0 (CSET,CDET)
*                                                                      *
*  Description:   store GEANT digits in the new dense format           *
*  Compared to the original GEANT routine a new SET/DET can be added   *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcdig.
*   AGCDIGA is for internal AGSDIG0/1 communication only
      INTEGER        NLOCAL,   JS,JD,JDX,JX,JXD,JDU,LOCAL
      COMMON/GCLOCA/ NLOCAL(2),JS,JD,JDX,JX,JXD,JDU,LOCAL(14)
      Integer        Iset,Idet,NW,NV,ND,NVU,NDU
      COMMON/AGCDIGA/Iset,Idet,NW,NV,ND,NVU,NDU
*     - - - - - - - - - - - - - - -
*
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
   Character*4    Cset,Cdet,cs
   Integer        AgSDIG0,NSET,NDET,NEED,ier
 
   AgSDIG0=-1;  Cs=Cset(1:3)//'D';
   "            Find if selected set, detector exists       "
   JDU=0;                                                   Check JSET> 0;
   NSET = IQ(Jset-1);                                       Check Nset> 0;
   Call GLOOK(Cs,IQ(Jset+1),Nset,Iset);                     Check Iset> 0;
   JS   = LQ(Jset-Iset);                                    Check Js  > 0;
   NDET = IQ(Js-1);                                         Check Ndet> 0;
   Call GLOOK(Cdet,IQ(JS+1),Ndet,Idet);                     Check Idet> 0;
   JD   = LQ(JS-Idet);                                      Check JD  > 0;
   JDX  = LQ(JD-2);                                         Check JDX > 0;
   NW   = IQ(JD+1)+IQ(JD+5)+1;                              Check Nw  > 0;
   JDU  = LQ(JD-3);                                         Check JDU > 0;
   NV   = IQ(JD+2);   ND   = IQ(JD+6);
   NVU  = Q(JDU+6);   NDU  = Q(JDU+2);
   IF (NV+ND # NVU+NDU)  { Print *,' AgSDIG0 error'; Return; }
 
   Ier=iquest(1); Iquest(1)=0;
   IF JDIGI==0                       "    Create DIGItisation master bank    "
   {  Call MZBOOK(IXDIV,JDIGI,JDIGI,1,'DIGI',NSET,NSET,0,2,0); IQ(JDIGI-5)=1;}
   else IF IQ(JDIGI-2)<NSET
   {  NEED=NSET-IQ(JDIGI-2);  Call MZPUSH(IXDIV,JDIGI,NEED,0,'I');   }
*
   JX=LQ(JDIGI-ISET);                "    Create DIGItiastion set bank       "
   IF  JX==0
   {   Call MZBOOK(IXDIV,JX,JDIGI,-ISET,'DIGI',NDET,NDET,NDET,2,0);  }
   else IF min(IQ(JX-1),IQ(JX-2))<Ndet
   {   NEED=NDET-min(IQ(JX-1),IQ(JX-2)); Call MZPUSH(IXDIV,JX,NEED,NEED,'I');}
*
   JXD=LQ(JX-IDET);                  "    Create DIGItisation bank           "
   IF (JXD==0) Call MZBOOK(IXDIV,JXD,JX,-IDET,'SJDX',0,0,IQ(JD+8),1,0);
*
   If IQUEST(1)!=0 {<W> Ier,IQuest(1);(' AgSDIG0 Memory problem ',2i6); Return}
   AgSDIG0 = 0;  IQ(JX+IDET)=0;
 
  END
*CMZ :  1.30/00 01/12/96  23.50.41  by  Pavel Nevski
*CMZ :  1.00/00 03/10/95  23.10.08  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/12/94
**********************************************************************
*                                                                    *
                 FUNCTION A G S D I G 1 (LTRA,NUMBV,DIGI)
*                                                                    *
*  Description:   store GEANT digits in the new dense format         *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcdig.
*   AGCDIGA is for internal AGSDIG0/1 communication only
      INTEGER        NLOCAL,   JS,JD,JDX,JX,JXD,JDU,LOCAL
      COMMON/GCLOCA/ NLOCAL(2),JS,JD,JDX,JX,JXD,JDU,LOCAL(14)
      Integer        Iset,Idet,NW,NV,ND,NVU,NDU
      COMMON/AGCDIGA/Iset,Idet,NW,NV,ND,NVU,NDU
*     - - - - - - - - - - - - - - -
*
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
  Integer   AgSDIG1,Last,Kdigi,Nk,Nb,I,J,K,N,i1,i2,i3,Ltra,j1,num,bin,jds,
            NUMBV(*),NwuHit/10/
  REAL      DIGI(*),Org,fct,fmx,xx
  bin(xx) = (xx+org)*fct
 
  AgSDIG1=-1;  Check Jdu>0;  Jds=Jdu;
  LAST=IQ(JX+IDET)     "  Check if enough space. If not increase bank size  "
  If IQ(JXD-1)<=LAST+Nw             "    one attempt should be enouph       "
  {  N=MAX(100,NW,IQ(JD+8)/2);   CALL MZPUSH(IXDIV,JXD,0,N,'I');
     If IQUEST(1)#0 { <W>; (' Lack of Memory in AgSDIG1');  Return; } }
 
  " ========>    Store tracks numbers, volumes numbers and digits  <========"
  " Nbit is taken from the SEJD/SJDD banks not to dublicate option analysis "
  " Org&Fct are taken from SJDU - the only place containing all variables   "
  j=JXD+LAST+1; IQ(j)=max(0,LTRA);  NK=1; K=1; i3=0;
 
  DO I=1,NVU           "           Store packed volume numbers              "
  {  Nb=IQ(JD+2*I+10);     num=max(0,NUMBV(i)-1);
     IF Nb>0  { K+Nb>33 ?; CALL MVBITS(NUM,0,Nb,IQ(j+NK),K-1);   K+=Nb; }
     else     { K>1     ?; IQ(j+Nk)=NUM;                         Nk+=1; }
  }
  Do I=1,NDU           "               Store packed digits                  "
  {  i1=JDS+i*10;   org=Q(i1+6);  fmx=Q(i1+5);  fct=Q(i1+7);
     KDIGI=(org+min(DIGI(i),fmx))*fct;   KDIGI=max(0,KDIGI);
     i2=I+Nvu;  i3=i2-Nv;  i3==1 & K>1 ?;
     If i3<=0 { Nb=IQ(Jd+2*i2+10) } else { Nb=IQ(Jdx+2*i3) };
     IF Nb>0  { K+Nb>33 ?; CALL MVBITS(KDIGI,0,Nb,IQ(j+Nk),K-1); K+=Nb; }
     else     { K>1     ?; IQ(j+Nk)=KDIGI;                       Nk+=1; }
     "   select the appropriate hit descriptor using first hit element  "
     If I==1  { while LQ(Jds)>0 & bin(Q(LQ(Jds)+8))<=KDIGI {Jds=LQ(Jds)}}
  }
  K=1+IQ(JD+1); N=Nw;
  If   i3>0            "               cumulative digits                    "
  {:D: Do j1=JXD+Last,JXD+1,-Nw
       {                  if (IQ(j1)  !=IQ(j)  ) Break :D:;
          do i=1,K-1    { if (IQ(j1+i)!=IQ(j+i)) Next  :D:; }
          do i=K,Nw-1   {     IQ(j1+i)+=IQ(j+i); }
          N=0; Break :D:;
  }    }
  " if (N=0) <W> (DIGI(i),i=1,NDU); ( ' AGSDIG1 digi added: ',10F10.3);     "
  Last+=N;   IQ(JX+IDET)=Last;  IWS(1)=Last/Nw;
  AgSDIG1=0;
   END
 
 
 
*CMZ :          06/07/98  18.41.28  by  Pavel Nevski
*CMZ :  1.30/00 17/11/96  22.43.56  by  Pavel Nevski
*CMZU:  1.00/01 21/12/95  22.19.56  by  Pavel Nevski
*CMZ :  1.00/00 14/11/95  02.46.06  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A g D O C U M  _
     (Module,MTitle,Author,Created,Btit,Bank,Bpath,num,Lb,
                   Map,Names,Comment,Par,LL,LL1,Link,Flag)
*                                                                    *
*  Description: store a bank in DETM or RECB structure with          *
*               corresponding documentation bank for DZDOC           *
* - AgDOCU is the FILL processor. It may be called in MODULEs only.  *
* - There may be 3 forms of Bpath: short relative (one word),        *
*   long relative (words separated by /), absolute (starts with /).  *
* - If the first call in a MODULE has a short Bpath, the latest is   *
*   kept as a CTOP bank, attached to //DETM/MODULE.                  *
* - If the first call in a MODULE has a long Bpath, the latest is    *
*   attached to //RECB.                                              *
*   CTOP bank or any absolutely addressed bank remain a DEFAULT bank *
* - All documetation banks are created lineary in DOCU/MODULE bank   *
* - Flag controls the I/O format, Link - access methode              *
* Modifications:                                                     *
* 16/04/96 PN: flag list changed as in AsFLAGS                       *
**********************************************************************
REPLACE [ERR#{#}] with _
        [; IF (#1) {<W>%L(Module),Bank; (' AgDOCUM error for module ',A,
                    ' for bank ',A/ 10x,'*** #2 ***');    Istat=-100;
                     "no doc mode" {L1Doc,L2Doc,Ldoc}=0;  Return   }; ]
REPLACE [SWAP(#,#)] with [;iw=#1;#1=#2;#2=iw;]
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
Integer       LENOCC,OK,Lb,LL,LL1,LvL,ns1,ns2,Ndm,i,j,k,l,M/1000000/,
              Idat,Itim,Link,Ia,Lk,L1,L2,Flag,IDYN,INEW,JOX,iw,idd/0/,X/0/,
              map(2,LL1),num(Lb),key(3),ID/0/,Iform/0/,Jform/0/,Istat/0/,IC
Character*(*) Module,MTitle,Author,Created,Bank,Bpath,Btit,
              Names(LL1),Comment(LL1)
Character*12  Ddoc,nam
Character*4   Ctop,Cbank,C1,C2
Character*8   Flags(15),Dmodule,Dmodu,Dbank,Dbanu,Dup,Ddef,dash/'-'/
Character*24  Descr(15),Tshort
Character     Cform*80,Cforn*80,C*1
Parameter     (OK=0)
Save          Id,Dmodule,Dbank,Dup,Ddef,Ctop
Logical       First/.true./,start
Real          Par(LL)
Integer iprin/1/
* - - - - - - - - - - - - - - - dete bank - - - - - - - - - - - - - - - - - - -
Data Flags  /'PNOW', 'PRIN', 'DEBU', 'GEOM', 'HIST', 'GRAP', 'SIMU', 'DIGI',
             'RECO', 'MFLD', 'ANAL', 'BACK', 'resa', 'resb', 'resc'/
Data Descr  _
      /'current print level  ','system print level   ','GEANT debug level    ',
       'geometry version     ','system histogram flag','system graphics level',
       'store GEANT hits flag','digitisation flag    ','reconstruction flag  ',
       'magnetic field flag  ','user analysis level  ','pile-up bunch select.',
       'reserve              ','reserve              ','reserve              '/
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
If First
{  First=.false.;   Istat=0;   L1Doc=0;
   Call MZFORM('DETP','-F',Iform);  Call MZFORM('DDOC','1H 19I -S',Jform);
   If (LdArea(1)=0) call MZLINT(IxCONS,'AGCDOCL',LDarea,L1Doc,Lpar)
}
If L1Doc<=0
{  * locate documentation system at the first link of DOCU bank:
   *(only bank IDH is checked, IDN may be swapped - check later)
   Call AsbDETE('DOCU',I);  L=0;  If (I>0)  L=LQ(LQ(LKDETM-I)-1)
   If L>0  { " both DETM?" if (IQ(L-4)==IQ(LKDETM-4)) L1doc=L; }
}
 
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
* - - - - - -          create the information bank itself           - - - - - *
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
" trace module changes - a module may have only ONE default Ctop bank "
IOX=Flag; If IOX==0
{ call AgDForm(Names,map,LL1,LL,Cform,Cforn);  Call MZFORM(Cbank,CForm,IOX) }
*
Cbank=Bank;  Dmodu=Module;  start=.false.
If Dmodu != Dmodule { Dmodule=Dmodu; Ctop=Cbank; Ddef=' '; start=.true.}
*
If Lb==1                              "  default directories in the DETM bank "
{  If Cbank==Ctop
   { Call AsBDETE(Dmodu,ID); Err Id<=0 {detector not found in DETM bank}
     IrBDIV=IxCONS;  LkArP2=LQ(LkDETM-Id);  LvL=3;  Dup=Dmodu(1:4)//'DETM'}
   else                                   { LvL=4;  Dup=Ddef }
   Call ReBANK (Cbank,Num,LL,LK,Ia)
}
else                                 "     explicit directory setting if /    "
{  J=1;  While Bpath(j:j)=='/' {J=J+1};
   If  J>1                            { Lvl=3;  C2='NONE'}
   else
   {  If Cbank==Ctop
      {  If (LKAR P1==0) Call MZBOOK(IxDIV,LKAR P2,LKAR P1,1,'RECB',2,2,10,2,0)
         IrBDIV=IxDIV;  LkArP2=LkArP1;  Lvl=3;  C2='RECB'}
      else                            { Lvl=4;  C2= Ddef }
   }
   J=J+5*(lb-2)-1; C1=Bpath(J+1:J+4); If (lb>2) C2=Bpath(J-4:J-1); Dup=C1//C2;
   Call ReBANK (Bpath,num,LL,LK,Ia)
}
   JOX=IOX;
   Call UCOPY (PAR,Q(LK+1+Ia),LL);    Call SBIT0(IQ(Lk),1)
   LkArP3=Lk  "temporary save bank address"
   If Lvl==3  { "RbCDir"  LkArP2=Lk;  Ddef=Cbank//Dup }
*
IDYN=0; INEW=LL;             " dependant dynamic banks now - if any required "
DO i=1,LL1
{  if (map(1,i)>0 & map(2,i)>0)       { INEW-=map(1,i)*map(2,i); Next; }
   INEW-=1; IDYN+=1;                      " dynamic array found here "
   If (Link==0) Link=-1                   " force link to be secured "
   L1=map(1,i); If L1<0
   { L1=-L1;    if L1<M { Call Ucopy(Par(L1),L1,1)} else { L1=nint(Par(L1-M))}}
   L2=map(2,i); If L2<0
   { L2=-L2;    if L2<M { Call Ucopy(Par(L2),L2,1)} else { L2=nint(Par(L2-M))}}
   L=Lenocc(Names(i));  Nam=Names(i)(3:L)//'xxxx';  Nam(5:)='*';
   C=Names(i)(1:1); If C=='I' {IOX=2} else If C=='H' {IOX=5} else {IOX=3}
   swap(LkArP2,LkArP3)
   CALL ReBANK (Nam,1,2+L1*L2+3,Lk,Ia)
   swap(LkArP2,LkArP3)
   Err LQ(LkArP3-IDYN)!=Lk {This FILL does not work in this version}
}
* LkArP3 keeps the current bank adress now
Dmodule=Module;  Call AGDLINK(Module,Bank,Link,LkArP3)
Check Flag==0;   Flag=JOX;
 
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
* - - - - -   new bank: make sure that detector documentation exists  - - - - *
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
If Start
{ "-------------------      level 1  - main DETM bank    -------------------"
  Call AsBDETE(Dmodu,ID);     Err Id<=0  {detector does not exist in DETM bank}
  Call AsBDETE('DOCU',Idd);   Err Idd<=0 {cannot book DOCU system in DETM bank}
  Dbanu='DETMNONE';  IQUEST(1)=0;  X=0;
  If Istat=0 & L1Doc<=0
  {
    Call UCTOH(Dbanu,Key,4,8)
    Call RZIN (IxCONS,LQ(LKDETM-idd),-1,Key,0,' ')
    If IQuest(1)==0 { L1Doc=LQ(LQ(LkDETM-idd)-1) }
    else
    {  IQuest(1)=0
       Call MZBOOK (IxCONS,L1Doc,LQ(LkDETM-idd),-1,'DETM',2,2,300,Jform,0)
       Call AgDOCBA(L1Doc,Dbanu,'Detector main bank', Author,Created,'-H',
                          0, 1, 'detector','subsystem or faculty name ',X)
    }
    Err L1Doc<=0 | Iquest(1)#0 | X!=0 { Cant access main documentation bank }
  }
  "-------------------       level 2  -  DETE bank      -------------------"
  If Istat==0 & L1Doc>0
  { "        first add link description in DETM bank                       "
    Call AgDTIT  (MTitle,Tshort)
    Call AgDOCBA (L1Doc,Dbanu,'*','*','*','*',1,0,Module(1:4),Tshort,X)
 
    " insure that links in doc DETM coincides with the main DETM "
    Ns1=IQ(LkDETM-2);  Ns2=IQ(L1Doc-2)
    If (Ns1>Ns2) Call MZPUSH (IxCONS,L1Doc,Ns1-Ns2,0,' ')
    if (L1Doc>0) L2Doc=LQ(L1Doc-Id)
 
    If L1Doc>0 & L2Doc<=0    "Documentation does not exist for THIS detector"
    { Dbank=DModu(1:4)//'DETM';   Call UCTOH(Dbank,Key,4,8);
      Call RZIN (IxCONS,L1Doc,-ID,Key,0,' ');  L2Doc=LQ(L1Doc-Id);
      If Iquest(1)#0|L2Doc<=0
      { IQuest(1)=0; Call MZBOOK(IxCONS,L2Doc,L1Doc,-ID,Dbank,2,2,300,Jform,0)
        Call AgDOCBA(L2Doc,Dbank,Tshort,Author,Created,'-I',0,15,Flags,Descr,X)
      }
      Err L2Doc<=0|Iquest(1)#0|X!=0 { Can not access DETE documentation bank  }
  } }
  Err IQuest(1)#0|L2Doc<=0|L1Doc<0 {cannot find top level documentation banks}
}
 
"---   level 3/4  -  the bank itself: all documentation is linear in DETE  ---"
 
Ldoc=0; Lkdoc=0; X=0;
If L2Doc>0
{  * first, update links in the upper level bank
   Ddoc=Cbank//Dup;   Ndm=60+LL*16;    Ns1=IQ(L2doc-2)
   Call UHTOC (IQ(L2doc-4),4,C1,4)           " - for level 3 doc "
   Call AHTOC (IQ(L2doc-5),4,C2,4)
   if C1==Dup(1:4) & C2==Dup(5:8)
   {  Call AgDOCBA (L2doc,Dup,'*','*','*','*',1,0,Cbank,Btit,X) }
   do i=1,Ns1
   {  Ldoc=LQ(L2Doc-i);   If (Ldoc<=0) go to :f:
      Call UHTOC (IQ(Ldoc-4),4,C1,4)
      Call AHTOC (IQ(Ldoc-5),4,C2,4)
      if C1==Cbank & C2==Dup(1:4)   { Call MZDROP(IxCons,Ldoc,' '); goto :f:; }
      if C1==Dup(1:4) & C2==Dup(5:8)            " - insert links for level 4 "
      { Lkdoc=Ldoc; Call AgDOCBA (Ldoc,Dup,'*','*','*','*',1,0,Cbank,Btit,X) }
   }  i=Ns1+1;  Call MZPUSH(IxCONS,L2DOC,5,0,' ')
 
   :f: Ldoc=LQ(L2Doc-i)
   If (Ldoc==0)  Call MZBOOK (IxCONS,Ldoc,L2doc,-i,Cbank,2,2,Ndm,Jform,0)
   Call AGDTIT (Btit,Tshort)
   Call AgDOCBA(Ldoc,Ddoc,Tshort,Author,Created,cform,0,0,' ',' ',X)
   If INEW>1
   {  Call AgDOCBA(Ldoc,Ddoc, '*', '*', '*', '*',0,-1,dash,'usage counter',X)
      Call AgDOCBA(Ldoc,Ddoc, '*', '*', '*', '*',0,-1,dash,'system version',X)
   }
   Err LDoc<=0 | Iquest(1)#0 { Can not create documentation bank }
   DO i=1,LL1
   {  k=1; if (map(1,i)>0 & map(2,i)>0) k=map(1,i)*map(2,i)
      L=Lenocc(Names(i));   Nam=Names(i)(3:L);  if IDEBUG>0&L>10
      { <W>%L(Module),Bank,Names(i)(3:L);
       (' AgDOCUM/DZDOC warning in module ',a,', bank ',a,', variable ',a,':'/,
        ' -name too long, will be trucated in documentation and include files')
      }
      Call AgDOCBA(Ldoc,Ddoc,Tshort,Author,Created,cform,0,-k,Nam,Comment(i),X)
   }
   If X==0 & Ldoc>0
   { CALL RZCDIR('//LUN61',' ')
     CALL aRZOUT (IXCONS,L1doc,Dbanu,IC,'SN')
     CALL aRZOUT (IXCONS,L2doc,Dbank,IC,'SN')
     CALL aRZOUT (IXCONS,Lkdoc,Dup , IC,'SN')
     CALL aRZOUT (IXCONS,Ldoc, Ddoc, IC,'SN')
     call RZPURG (1)
   }
   else { <W> Ddoc; (' AGDOCUM: problems writing out doc for ',a) }
}
if INEW>1
{  Call DATIME (Idat,Itim);  Par(1)=Idat+Itim/2401.;  Q(LkArP3+1+Ia)=Par(1)
                             Par(2)=IC;               Q(LkArP3+2+Ia)=Par(2)
}
END
 
 
  subroutine AHTOC(iw,n,c,m)
  character  C*(*)
  integer    iw(*),n,m,i,ii
  ii=iw(1)
  do i=4,1,-1
     c(i:i)=CHAR(mod(ii,256))
     ii=ii/256
  enddo
  end
 
*CMZ :          27/06/98  20.48.53  by  Pavel Nevski
*CMZ :  1.30/00 26/04/96  19.30.43  by  Pavel Nevski
*CMZU:  1.00/01 16/01/96  00.31.26  by  Pavel Nevski
*CMZ :  1.00/00 25/08/95  23.30.46  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/01/95
**********************************************************************
*                                                                    *
                 subroutine       A g D O C B A _
            (Link,Bank,Tit,au,ve,io,NL,ND,Cvar,Comment,i)
*                                                                    *
*  Description:  fill a documentation bank                           *
*  Output i - (success flag) should be Ok(0). At least one of the    *
*  operations - create, insert link or data should be done           *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
Character*(*) Bank,Tit,au,ve,io,Cvar(*),Comment(*),NN*4,Cv*8,Cbuf*80;
Integer       AgDocRd,AgDocWr,Lenocc,Link,NL,ND,Lb,key(2),
              i,j,k,L,Lk,N,N0,ioff,M,ok;
Parameter      (ok=0);
 
check I>=0;  I=-1;  Check Link>0;  Lb=IQ(Link-1)
If Bank(1:1)#'*'
{  CALL UCTOH(Bank(1:4),key(1),4,4)
   CALL ACTOH(Bank(5:8),key(2),4,4)
   If IQ(Link-4)!=key(1)
   { <w> Bank,IQ(LINK-4),key;
    (' AgDOCBA wrong bank: request ',a8,' found ',3(1x,a4)/,
    ' *********************************************************************'/,
    ' * Probably this means that the documentation RZ file is corrupted.  *'/,
    ' * This is often fatal and program may crash imediately afterword !  *'/,
    ' * To solve the problem simply remove detm.rz, it will be re-created *'/,
    ' *********************************************************************')
    return
   }
   If IQ(Link+1)=0               " create new bank "
   {  Call Vzero(IQ(Link+1),Lb);  IQ(Link-5)=key(2);
      Call UCTOH(Bank,IQ(Link+1),4,4);
      IQ(Link+2)=20;  IQ(Link+3)=20;
      Cbuf = Bank(1:4)//Tit(1:LENOCC(Tit))
      i    = AgDocWr(Link,'..',0,0,Cbuf)
      i    = AgDocWr(Link,'up',0,0,Bank(5:8))
 
      if (au(1:1)#'*') i=AgDocWr(Link,'au', 0,0,au );
      if (ve(1:1)#'*') i=AgDocWr(Link,'ve', 0,0,ve );
                       i=AgDocWr(Link,'nl', 0,0,' ');
                       i=AgDocWr(Link,'ns', 0,0,' ');
                       i=AgDocWr(Link,'nd', 0,0,' ');
      if (io(1:1)#'*') i=AgDocWr(Link,'io', 0,0,io );
}  }
do k=1,NL                               " links can not be doubled "
{  Lk=Lenocc(Comment(k));
   i =AgDocRd(Link,'Link',Cvar(k)(1:4), N,ioff,L)
   if i > Ok
   {  if (AgDocRd(Link,'nl',' ', M,Ioff,L)=Ok) IQ(Link+Ioff+3)=N+1;
      if (AgDocRd(Link,'ns',' ', M,Ioff,L)=Ok) IQ(Link+Ioff+3)=N+1;
      Cbuf = Cvar(k)(1:4)//'    - '//Comment(k)(1:Lk)
      i    = AgDocWr(Link,'Link',N+1,0,Cbuf)
}  }
N0=1;
do k=NL+1,NL+abs(ND)                    "    data can be doubled   "
{  j=k; if (ND<0) j=NL+1;  Lk=max(Lenocc(Comment(j)),1);  if (k>j) Lk=0;
   if    AgDocRd(Link,'Data','. . . next free place . . . ',N,ioff,L)>Ok
   { If  Lk=0  { N0+=1; write(NN,'(i3)') N0; }  else  { N0=1; NN=' '; }
     if (AgDocRd(Link,'nd',' ', M,Ioff,L)=Ok)    IQ(Link+Ioff+3)=N+1;
     Cv = Cvar(j);  Cbuf = Cv//' - '//Comment(j)(1:Lk)//NN
     i  = AgDocWr(Link,'Data',N+1,0,Cbuf)
}  }
END
 
 
  subroutine ACTOH(c,iw,n,m)
  character  C*(*)
  integer    iw(*),n,m,i,ii
  ii=0
  do i=1,4
     ii=ii*256+ichar(c(i:i))
  enddo
  iw(1)=ii
  end
 
*CMZ :  1.00/00 06/01/95  01.38.29  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/01/95
**********************************************************************
*                                                                    *
          Function   A g D O C R D (Link,Cf,Ckey, N,ioff,L)
*                                                                    *
* Description: get a record with the Ckey content in the Ctype field *
*              Ckey may be a record type or a content of a DD record *
* Output: N - record number if found, else number of scanned records *
*        id - offset of the record in bank, IQ(link+id+1) first word *
*             of  [3*16+2,'cf',i1,i2,L*16+5,'text data (1-L)']       *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
   character      Cf*(*),Ckey*(*), C*5/'GLSUD'/;
   Integer        AgDOCRD,LENOCC,Link,ioff,N,L,id,if,
                  key(10),Lk,Lt,id1,id2,NW,I,J,IW;
   Integer        mask(9)/1,1024,16384,8192,9216,10240,15361,19456,17410/;
   Character*2    ask (9)/'..','au','ve','nd','nl','ns','up','io','dd'/;
 
   {N,ioff,L,Lk}=-1;                       " check bank format "  AgDocRd =-1;
   Lt=20; do i=1,5 { Lt+=IQ(Link+10+i); };
   Unless (IQ(Link+3)==20 & IQ(Link+2)==Lt & IQ(Link-1)>=Lt)      go to :E:;
 
   Id1=20; if=1;                           " decode request Cf "  AgDocRd =-2;
   do id=1,8 { If (Cf(1:2)=ask(id)) goto :F:; };
   Lk=LENOCC(Ckey); Call UCTOH(Ckey,key,4,min(Lk,40)); Lk=(Lk+3)/4;
   do if=1,5 { if (Cf(1:1)=C(if:if)) goto :F:; Id1+=IQ(Link+10+if); }
                                                                  goto :E:;
   :F: Ioff=id1; id2=0; N=0; Nw=IQ(Link+10+if);
   :N: while id2<NW
   {  Ioff=Id1+Id2; J=Link+Ioff; N+=1;   " check record format"   AgDocRd =-3;
      If (IQ(J+1)#50) Break;            L=0;     Id2+=4;
      Iw=IQ(J+5); IF (Mod(Iw,16)=5)   { L=Iw/16; Id2+=1+L; }
      IF (IQ(J+2)#Mask(Id) | Lk>L)      Next :N:;
      Do i=1,Lk { If (IQ(J+i+5)#Key(i)) Next :N:; }               AgDocRd = 0;
                                                                  goto :E:;
:L:}                                                              AgDocRd = 1;
:E:"<w>AgDOCRD,Cf,Ckey,N,ioff,L;(' AgDocRd=',i2,' at ',a,1x,a,' N,of,L=',3i6)";
END;
 
*CMZ :  1.00/00 06/01/95  01.39.27  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/01/95
**********************************************************************
*                                                                    *
            Function   A g D O C W R (Link,Cf, I1,I2, TEXT)
*                                                                    *
* Description:  Insert a new record at the end(!) of the Cf field    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
   character    Cf*(*),TEXT*(*), C*5/'GLSUD'/;
   Integer      AgDOCWR,LENOCC,Link,I1,I2,If,Id,Lk,Need,Lt,Li,L,iof,I,N;
   Integer      mask(9)/1,1024,16384,8192,9216,10240,15361,19456,17410/;
   Character*2  ask (9)/'..','au','ve','nd','nl','ns','up','io','dd'/;
 
                                           " check bank format "  AgDocWr =-1;
   Lt=20; do i=1,5 { Lt+=IQ(Link+10+i); };
   Unless (IQ(Link+3)==20 & IQ(Link+2)==Lt & IQ(Link-1)>=Lt)      goto :E:;
 
   Iof=20+IQ(Link+11);  If=1;             " decode request "      AgDocWr =-2;
   do id=1,8 { If (Cf(1:2)=ask(id)) goto :N:; };  Id=9;
   do if=2,5 { Iof+=IQ(Link+10+if); if (Cf(1:1)=C(if:if)) goto:N:; }
                                                                  goto :E:;
   :N: Lk=LENOCC(Text);  Li=4; N=0;   If (Lk>1) { N=(Lk+3)/4; Li=5+N;}
   Need=Lt+Li-IQ(Link-1);  If (need>0) Call MZPUSH(IxCons,Link,0,Need+10,' ');
   L=Link+Iof;     Call UCOPY2(IQ(L+1),IQ(L+Li+1),Lt-Iof);
   IQ(L+1)=16*3+2; IQ(L+2)=Mask(Id); IQ(L+3)=i1; IQ(L+4)=i2;
   If  Li>4  { IQ(L+5)=16*N+5; Call UCTOH (Text,IQ(L+6),4,Lk); }
   " increase length "  IQ(Link+2)+=Li;  IQ(Link+10+If)+=Li;      AgDocWr = 0;
:E:"<w> AgDOCWR,Cf,I1,I2,TEXT;(' AgDocWr=',i2,' at ',a,' i1,i2,T=',2i5,2x,a)";
END;
 
*CMZ :          06/07/98  18.52.36  by  Pavel Nevski
*CMZ :  1.30/00 09/02/97  21.15.43  by  Pavel Nevski
*CMZU:  1.00/01 22/12/95  21.50.31  by  Pavel Nevski
*CMZ :  1.00/00 15/11/95  01.03.24  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                     Subroutine   A g D G E T P  _
          (Module,Oper,istat,Bank,Name,Value,Bpath,Num,Lb,
                             Map,Names,Par,LL,LL1,Link,Flag)
*               - - -    USE processor    - - -                      *
* Description: Given the module and the bank name returns the        *
*    instance of the bank containing a selected parameter value      *
*    If the Name is blank, select the first (default) bank           *
*    Flag is 0 only at the first call, allowing more checks on it    *
* Modifications:                                                     *
*  PN, 03/06/96:                                                     *
*  default module/bank is saved in stack as suggested by Ulrik Egede *
*  selected DETM branch becomes Unique only in GEO or by Oper=UNIQ   *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,agclink.
*   links for dynamic banks access
       INTEGER    NALINKMAX,AG_NLINK,AG_LINK
       PARAMETER  (NALINKMAX=100)
       COMMON /AGCLINK/ AG_NLINK,AG_LINK(0:NALINKMAX)
*      - - - - - - - - - - - - - - - - - - - - - -
 
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
     INTEGER          Nbp,IP1STACK,    IP2STACK,    IEND,IDSTACK
     COMMON /RBSTACK/ Nbp,IP1STACK(20),IP2STACK(20),IEND,IDSTACK(20)
REPLACE [ERR#{#}] with [;    IF (#1) {  IQUEST(1)=0;
    IF (istat!=-999) { Istat=Jstat; Return; }
    <W> %L(Module),Ctop,%L(Bank),LL,%L(Name),Value,%L(Bpath),(num(i),i=1,lb)
    (' error in USE operator called from ',A,' for bank ',A,'/',A,' L =',i3/ _
         10x,'Looking for variable ',A8,' =',F10.3/10x, '***** #2 *****'  / _
         10x,'The path is ',A,' with IDN =',10i5 );  Return; }
  ]
   Integer       LENOCC,LOCF,JBIT,Iname,Ns,LL,IL,Ia,Ib,Id,LP,JP,La,Lb,Lc,i,J,L,
                 Lvl,LL1,Link,Lk,Flag,Num(Lb),Map(2,LL1),Nch,IDYN,istat,jstat
   Character*(*) Module,Bank,Bpath,Name,Names(LL1),Oper
   Character*4   Ctop,Cbank,C1,C2
   Character*8   Dmodu,Dmodule,Dup,Ddef
   Character*80  Cform,Cforn,Bform
   Real          Value,Val,Par(LL)
   Save          Ctop,Dmodule,Ddef,Dup,ID
 
" trace module changes - a module may have only ONE default Ctop bank "
Cbank=Bank;  Jstat=-1;
if Oper(1:1)=='N' & (Istat==0 | Istat=-999) " this is a NEXT request "
{ Err LINK<0 { Bank was not selected };       Lk=%LINK(LINK);
  Err Lk<=0  { Previous bank desappeared };   Lk=LQ(Lk);
}
else
{ If Nbp==0  { Dmodu=Module; If Dmodu!=Dmodule
               { Dmodule=Dmodu; Ctop=Cbank; Ddef=' '; ID=0;
             } }
*
 If Lb==1                             "  default directories in the DETM bank "
 { :M: If Cbank==Ctop
   { Call ASLDETN(Dmodu,ID);    Err Id<=0 {detector not found in DETM bank}
     IrBDIV=IxCONS;  LkArP2=LQ(LkDETM-Id);  LvL=3;  Dup=Dmodu(1:4)//'DETM'}
   else                                   { LvL=4;  Dup=Ddef }
   If Name!=' '                    " - we need IL. Num(1) is not used at all "
   {  Lk=0;  Err LKARP2<=0 {default bank undefined}
      Call UCTOH (Cbank,Iname,4,4);    NS=IQ(LKARP2-2)
      Do IL=1,NS { Lk=LQ(LKARP2-IL); If(Lk>0&IQ(Lk-4)==Iname) Break; Lk=0}
   }
   else  { Call ReBANK (Cbank,Num,-LL,Lk,Ia) }
   " this may not be a good solution, try it however "
   If  Lk<=0 & LvL==4  { Ctop=Cbank; Go to :M:; }
 }
 else                               "     explicit directory setting if /    "
 { J=1;  While Bpath(j:j)=='/' {J=J+1};
   If J==1   " - relative address "
   {  If Cbank==Ctop
      {  IrBDIV=IxDIV;  LkArP2=LkArP1;  Lvl=3;  C2='RECB'; ID=0}
      else                            { Lvl=4;  C2= Ctop       }
   }
   else      " - absolute address "   { Lvl=3;  C2='NONE'; ID=0}
   IF (LvL==3 & Bpath(J:J+3)=='DETM') Call AsBDETE(Bpath(J+5:J+8),ID)
   J=J+5*(lb-2)-1; C1=Bpath(J+1:J+4); If (lb>2) C2=Bpath(J-4:J-1); Dup=C1//C2;
   Call ReBANK (Bpath,num,-LL,Lk,Ia)
}}
*
 Err Lk<=0 {No bank exists for this path}
*                                            explicit parameter request
 If Name!=' '
 { Ib=LOCF(Value)-LOCf(Par)+1;    Err 1>Ib|Ib>LL {variable is not in the bank}
   Ia=0;  Until Q(Lk+Ib+Ia)==Value
   { * scan a chain or block of banks
     if  IQ(Lk-5)=>0  { Lk=LQ(Lk) } else { Ia=Ia+LL }
     Err Lk<=0 | Ia>=IQ(Lk-1)  {No bank exists with this value}
   }
   " for top level make this bank default and shunt it at 1st position "
   If Cbank==Ctop & ID>0 & IrBDIV==IxCONS & (Module(5:7)='GEO'|OPER(1:1)='U')
   {  Call ZSHUNT(IxCONS,Lk,LkArP2,-IL,0)
      If (LQ(Lk)>0) Call MZDROP(IxSTOR,LQ(Lk),'L')
 } }
" CHECK LL>0   finish processing for dummy calls "
*
*                                        bank Validation
*                       If user requires the status, dont check length here
 IF istat=-999
 { Err mod(IQ(Lk-1),LL)>0 {Bank length does not correspond to the structure} }
 If Flag==0
 { LkArP3=Lk  "temporary save bank address"
   call AgDForm(Names,map,LL1,LL,Cform,Cforn);  Call MZFORM(Cbank,CForm,Flag)
    " If (LkArP3!=Lk)  print *,' popalsia gad ',LkArP3,Lk; "
   Lk=LkArP3;  Call MZIOTC (IxStor,Lk,Nch,Bform);
   If Cform!=Bform & Cform!=Bform(2:) & Cforn!=Bform
   {  IF istat==-999
      { print *,' wrong bank ',Cbank,' : '
        print *,' required format is = ',cform(1:Lenocc(cform)),'***'
        print *,' found bank format  = ',bform(1:Nch),          '***'
      } Err Nch>=0 {Bank formats are not the same}
   }
   "    force link to be secured for banks with dymanic arrays  "
   IDYN=0; Do I=1,LL1 { If (map(1,i)<0 | MAP(2,I)<0) IDYN=1; }
   IF (IDYN>0 & LINK==0) LINK=-1
 }
*  Update once DETM family banks with datacards stored in DETP
*  Bit one of the banks status is SET after update is done
If IrBDIV==IxCONS & ID>0 & JBIT(IQ(Lk),1)==0
{
   LP=LQ(LKDETM-ID); Ns=IQ(LP-2); Call UCTOH('DETP',Iname,4,4);
   Do IL=1,Ns
   {  JP=LQ(LP-IL);  Check JP>0;  Check IQ(JP-4)=Iname;  L=IQ(JP-1);
      "   <w> bank; (' detp bank found for bank ',a4)         "
      "  if bank was selected with ISEQ, transmit it as value "
      La=IQ(Lk-1); Lc=IQ(lk-5);  Val=Value;
      if (Lc<0)    La=IQ(lk-1)/abs(Lc)
      If (Name==' ' & Lc>=0)  Val=Lc
      If (Name==' ' & Lc <0)  Val=Ia/La+1
 
      Call AgDatCar (Bank,Name,Val,Names,map,LL1,Q(Lk+1+ia),La,Q(JP+1),L)
      if (Ia+La>=IQ(Lk-1))  Call SBIT1(IQ(Lk),1)
}  }
*
 Call Ucopy (Q(Lk+1+ia),Par,min(LL,IQ(Lk-1)))
 if (Oper(1:1)=='Z') call VZERO(IQ(Lk+1),IQ(Lk-1))
 if (Oper(1:1)=='D') call MZDROP(IxSTOR,Lk,' ')
 Call AGDLINK (Module,Bank,Link,Lk)
 If  LVL == 3    { " print *,' default bank set ' "; LkArP2=Lk; }
*                                      check length once more
 If  istat!=-999 { Istat=0;  Jstat=min(LL,IQ(Lk-1)); }
 Err mod(IQ(Lk-1),LL)>0 {Bank length does not correspond to the structure}
 IQUEST(1)=0
END
 
 
*CMZ :          30/07/98  14.12.43  by  Pavel Nevski
*CMZ :  1.30/00 15/04/97  17.02.23  by  Pavel Nevski
*CMZ :  1.00/00 07/10/95  19.31.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   12/01/95
****************************************************************************
*                                                                          *
                 Subroutine   A g D A T C A R _
          (Bank,Name,Value,names,map,LL1,vars,LL,Buf,Lbuf)
*                                                                          *
*  Description: datacard input, stored in BUF by FFREAD, is assumed to be  *
*        a sequence of text addresses 'bank(sel).variable(ind)=' and some  *
*        amount of real numbers. All parts of the address are optional.    *
*        Type of the selector Value corresponds to the first letter of Name*
*        CKRACK is an entry in CHPACK (M432)                               *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
Integer       ND,NE,NF,NG,NUM,   Dummy;     Real Anum(2);
Common/slate/ ND,NE,NF,NG,NUM(2),Dummy(34);
Equivalence              (num,                   anum);
Integer       LL,LL1,LBUF,LENOCC,ICLOCU,ICFIND,Isel,i,j,K,M,N,ia,ib,map(2,LL1),
              ie,iv,ii,i0,i1,i2,Lt,Lb,Lv,jv,kv,ind,jb,kb,ia1,Irind,Ivalue,ift
Character     Name*(*),Names(LL1)*(*),Bank*4,Cn*1,
              Line*80,Cline*80,C*1,EQ*1/'='/,CRind*4,Cvalue*4
Real          Value,Rind,Rvalue,vars(LL),Buf(Lbuf),Blank/-989898.e-17/
Equivalence   (Rind,Irind,Crind),(Rvalue,Ivalue,Cvalue)
Replace[ERR(#)]  with [;<W>;(' AgDatCar error : ','#1'); Isel=0; Ia=0; NEXT;]
Replace[DEBUG#;] with [;IF (IDEBUG>=7) print *,#1;]
 
{i1,i2,Ia,Isel}=0;
 
do N=1,LL1                 " find reference variable and bank format"
{  if (name==Names(N)(3:)) M=N
   Ia+=1; If (Map(1,N)>0&Map(2,N)>0) Ia+=Map(1,N)*Map(2,N)-1
}  Ift=LL-Ia+1;  Ia=0;
* take care of IDN selector - it is passed as a real number
  Cn='R'; if (M>0) Cn=Names(M);
 
Call UCOPY(Value,Rvalue,1);
debug ' checking item ',bank,'.',name,': ft=',ift,' M=',M,' c=',Cn
 
While i2<Lbuf
{  " get new field " i0=i2;  Call AgDatAdr(Buf,i1,i2,Lbuf);
   if Isel>0 & Ia>0      " fill the previous address field with data "
   {  do i=i0+1,i1
      {  j=ia+i-i0-1;  if 1<=j&j<=LL
         {  if  Names(N)(1:1)=='I'
            {  Call Ucopy(Nint(Buf(i)),Vars(j),1)
               <w> Names(N),j-ia1+1,Nint(Buf(i)),Bank,Value
               (' ===> Datacard assign ',a,'(',i2,') =',i10,' in ',a,
               ' bank selected with ',F10.3)
            }
            else if Names(N)(1:1)=='H'
            {  Call Ucopy(Buf(i),Vars(j),1)
               <w> Names(N),j-ia1+1,Buf(i),Bank,Value
               (' ===> Datacard assign ',a,'(',i2,') =',a4,' in ',a,
               ' bank selected with ',F10.3)
            }
            else
            {  Call Ucopy(Buf(i),Vars(j),1)
               <w> Names(N),j-ia1+1,Buf(i),Bank,Value
               (' ===> Datacard assign ',a,'(',i2,') =',F10.4,' in ',a,
               ' bank selected with ',F10.3)
   }  }  }  }
*                          transform the next address field into characters
   Lt=4*(i2-i1);     If Lt>80   {err(address field is too long)}
   Lt=min(lt,80);    Line=' ';   Call UHTOC(Buf(i1+1),4,line,Lt)
   Cline=Line;       Call CLTOU (Cline)
   Lb=Lenocc(Bank);  Lt=Lenocc(Line(1:Lt));   Iv=0 "- already used characters "
*
   Jb=ICLOCU(Bank,Lb,CLine,1,LT);              " look for this bank reference "
   debug ' looking for item ',bank,'.',name,' in ',line(1:lt),' LT,JB=',lt,jb
   if jb>0
   {  ib=jb+lb; C=Line(ib:ib);  Rind=blank;   Iv=ib;  Isel=1; Ia=0;
      if C='('                                 " check for index in brackets  "
      {  kb=ICFIND(')',Line,ib,Lt); if kb<=0 {err(no closing bracket)};
         ia=0; ie=index(line(ib+1:kb-1),'=')
         if ie>0
         {  while Line(ib+1:ib+1)==' ' {ib+=1; ie-=1;}
            Ia=ift;  do N=1,LL1                 " find reference variable "
            {  K=N;  if (CLine(ib+1:ib+ie-1)==Names(N)(3:)) Break;  K=0;
               Ia+=1; If (Map(1,N)>0&Map(2,N)>0) Ia+=Map(1,N)*Map(2,N)-1
            }  ib=ib+ie
            debug ' ...name=',%L(name),' line,ib,ie,ia=',line(ib:kb),ib,ie,ia
         }
         Iv=kb+1; call CKRACK(Line,ib+1,kb-1,-1);
         if Nf=2 {Rind=NUM(1)}  else if Nf>2 {Rind=Anum(1)}
         else    {while Line(ib+1:ib+1)==' ' {ib+=1;}; CRind=Line(ib+1:kb-1)}
      }
      if C=EQ                                  " or direct select assignement "
      {  if ib#Lt {err(equal sign is not the last one)}
         Rind=Buf(i2+1);  Iv=Lt+1;
      }                                        " there was a selection done   "
      If Rind!=blank
      { Cn='R'; Rvalue=blank;
        if ia==0    { If (M>0) Cn=Names(M); Call Ucopy(Value,Rvalue,1)    }
        else if K>0 {          Cn=Names(K); Call Ucopy(Vars(ia),Rvalue,1) }
        else        { Isel=0 }
        If (Cn=='I' & Rind!=Ivalue)  Isel=0
        If (Cn=='R' & Rind!=Rvalue)  Isel=0
        If (Cn=='H' & CRind!=Cvalue) Isel=0
      } ia=0
   }  If (Isel=0 | Iv>Lt) Next
*
   Ia=Ift; jv=0; do N=1,LL1                      " now check variable reference "
   {  Lv=Lenocc(Names(N));       Jv=ICLOCU(Names(N)(3:Lv),Lv-2,CLine,Iv+1,LT)
                                 C=line(jv+Lv-2:jv+Lv-2)
      debug ' ...now for ',names(n)(3:lv),' in ',line(Iv+1:LT),' iv,lt,jv,C=',
      iv,lt,jv,C
      Ia1=Ia;   If (jv==iv+1 & (C=='('|C==EQ)) break;     " 2.06.98: was jv>0 "
      Ia=Ia1+1; If (Map(1,N)>0&Map(2,N)>0) Ia=Ia1+Map(1,N)*Map(2,N)
   }
* variable name should imediatly follow - otherwise it may be another bank name
   If jv!=Iv+1 { Isel=0; Next; }
*
   ii=jv+(lv-2);  C=Line(ii:ii);  Ind=1;  Ie=ii;
   If C='('
   {  kv=ICFIND(')',Line,ii,Lt);      if kv<=0 {err(closing bracket lost)}
      call CKRACK(Line,ii+1,kv-1,-1); Ie=kv+1;
      If Nf=2 {Ind=Num(1)} else {err(Index must be integer)}
   }
   debug ' ........ isel,ia,ind=',isel,ia,ind
   Ia+=Ind-1;  If Line(Ie:Ie)#EQ {err(bad assignement termination)}
}
   END
 
*CMZ :  1.30/00 26/04/96  17.32.50  by  Pavel Nevski
*CMZ :  1.00/00 07/10/95  18.49.25  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/01/95
**********************************************************************
*                                                                    *
          Subroutine  A g D A T A D R (Itemp,I1,I2,L)
*                                                                    *
*  Description: compensate the lack of info provided by FFREAD(!)    *
*  Find an address field starting with a letter and ending with a =  *
*  Accept everything in (). All other combinations are data fields.  *
*  ICtype is 0-unseen, 1-anything, 2-numeric, 3-low/4-up characters. *
*  PN,26/04/96 change L0 to 2(!) - will see if it is ambigious       *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
    Integer       L,Itemp(L),I1,I2,i,j,M,N,jx,nb,mb,ICTYPE,Lid,L0/2/
    character     Ctemp*4,c*1,eq*1/'='/
;
  { Lid,Nb,Mb,M }=0;
  do I=I2+1,L
  {  Call UHTOC(Itemp(i),4,Ctemp,4)
     Do j=1,4
     { C=Ctemp(j:j); jx=ICTYPE(C);
       If jx=0                        { Nb=1;         Lid =0;  Break;}
       If Lid=0 & j=1 & jx<=2         { Nb=1;         Lid =0;  Break;}
       If Lid<L0 & jx>=3              { Nb=2;         Lid+=1;  Next; }
       If Lid>=L0	
       {  If jx>=2|C='/'|C='.'|C=' '  { Nb=2;         Lid+=1;  Next; }
          If Mb=0  & C='('            { Nb=2; Mb+=1;  Lid+=1;  Next; }
          If Mb>0  & C=')'            { Nb=2; Mb-=1;  Lid+=1;  Next; }
          If Mb>0  & jx>0             { Nb=2;         Lid+=1;  Next; }
          If C=EQ                     { Nb=3;                  Break;}
       }                                Nb=9;         Lid =0;  Break;
     }   "  print *,' I,Ctemp,nb,lid=',I,Ctemp,nb,lid  "
          If Nb=3                   { N=Lid/4+1; I1=I-N; I2=I; Return; }
  }       I1=L; I2=L;
  End
 
 
*CMZ :          08/12/97  13.55.36  by  Pavel Nevski
*CMZ :  1.30/00 23/05/96  14.03.56  by  Pavel Nevski
*CMZ :  1.00/00 22/08/95  04.05.46  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Subroutine   A S B D E T E (Cdet,ID)
*                                                                    *
*  Description:  Book a new subdetector into DETM system description *
*                (SBDETE analog)                                     *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,asflags.
      INTEGER      NFLAGS
      PARAMETER    (NFLAGS=15)
      CHARACTER*4  CFLAG(NFLAGS)
      DATA CFLAG   /'PNOW','PRIN','DEBU','GEOM','HIST','GRAP',
     >              'SIMU','DIGI','RECO','MFLD','ANAL','BACK',
     >              'RESA','RESB','RESC'/
*    ---------------------------------------------------------
*KEND.
CHARACTER   Cdet*(*)
INTEGER     I,ID,LDETE,NEED,IUCOMP,Iprin,ND/10/,NL/10/,
            FLAGS(NFLAGS)/3*0, 8*1, 4*0/
 
Iprin=Idebug
If Cdet(1:4)=='flag' " really OO action - only ASBDETE has access to defaults "
{ Do i=1,NFLAGS
  {  check Cdet(5:8)==CFLAG(i); FLAGS(i)=ID;
     Prin2 i,CFLAG(i),ID; (' ASBDETE: change default flag',i3,1x,a,' to',i4)
  }; Return;
}
 
" Check if top level bank exists at all. If not book it:  "
" Occupy first link for the documentation tree            "
 IF LKDETM<=0
 { Call MZBOOK (IxCONS,LKDETM,LKDETM, 1,'DETM',ND,ND,ND, 5,0)
   Call MZBOOK (IxCONS,LDETE, LKDETM,-1,'DOCU',NL,NL,NFLAGS,2,0)
   Call UCTOH  ('DOCU',IQ(LKDETM+1),4,4)
 }
" now check if the detector already exists, If not - find free place "
 ND=IQ(LKDETM-1);   Call GLOOK (Cdet,IQ(LKDETM+1),ND,ID);  If (Id>0) Return;
 ID=IUCOMP (0,IQ(LKDETM+1),ND)
 If ID==0 { ID=ND+1; NEED=10; Call MZPUSH (IxCONS,LKDETM,NEED,NEED,' ') }
 
" Hang the DETector Data bank "
 Call MZBOOK (IxCONS,LDETE,LKDETM,-ID,Cdet,NL,NL,NFLAGS,2,0)
 Call UCTOH  (Cdet,IQ(LKDETM+ID),4,4);      IQ(LDETE-5)=1
 Call Ucopy  (Flags,IQ(LDETE+1), Nflags)
   END
 
 
*CMZ :  1.30/00 20/11/96  13.38.13  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/01/95
******************************************************************************
*                                                                            *
                          SUBROUTINE   A G S T A N D
*                                                                            *
*  Description: tables of the obvious standard materials and media           *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
  Character*20 Modulo
*
* make sure that minimal GEANT structures exist
  If (Jpart==0) Call GPART
  IF (Jmate==0) Call GMATE
  Check JTMED==0
  call UCTOH('no  ',IQ(LQ(JPART-48)+3),4,4)
  call UCTOH('otti',IQ(LQ(JPART-48)+2),4,4)
  call UCTOH('gian',IQ(LQ(JPART-48)+1),4,4)
  Modulo = %Module;  %Module = ' '
*
*    More simple materials from PDG (july 1994)
  Material  Silicon       z=14  A=28.09  Dens=2.33 RadL=9.36 AbsL=106.0/2.33
  Material  Liquid_argon  z=18  A=39.95  Dens=1.40 RadL=14.0 AbsL=117.2/1.40
  Material  Argon_gas     z=18  A=39.95  Dens=1.78e-3,
                                         RadL=14.*1.4/%Dens  AbsL=117.2/%Dens
  Material  Nitrogen_gas  z=7   A=14.01  Dens=1.25e-3,
                                         RadL=37.99/%Dens    AbsL=87.8/%Dens
  Material  Oxigen_gas    z=8   A=16     Dens=1.43e-3,
                                         RadL=23944          AbsL=90./%Dens "?"
*
*    Some organic composites from PDG (july 1994)
  Component C             Z=6   A=12  w=1
  Component H             Z=1   A=1   w=1
  Component O             Z=8   A=16  w=1
  Mixture   Polystyren    NlMat=2  ww={1,1}   Dens=1.032    "scintillator"
  Mixture   Polyethylene  NlMat=2  ww={1,2}   Dens=0.93
  Mixture   Mylar         NlMat=3  ww={5,4,2} Dens=1.39
*
*    now standard tracking medium (filled here with air)
  Material Air
  Medium   Standard  Ifield=1 FieldM=20 TmaxFd=20 Epsil=0.01,
                     SteMax=10.0   DeeMax=-0.02   StMin=-0.01
  Medium   Atlas     Ifield=1 FieldM=20 TmaxFd=20 Epsil=0.01,
                     SteMax=10.0   DeeMax=-0.02   StMin=-0.01
  %Module = Modulo
  End
 
 
 
 
*CMZ :          22/06/98  21.58.44  by  Pavel Nevski
*CMZ :  1.30/00 26/11/96  23.11.18  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
             Function     A G P F L A G (Cdet,Stage)
*                                                                    *
*  Description:  get a standard SLUG-like control Print Flag         *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEND.
  Integer        AGPFLAG,Idet/0/,Ista/0/
  Character      Cdet*(*),Stage*(*),Cdeto*4/'.'/,Stageo*4/'.'/
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
*                                     requested detector does not exist
      AgPFLAG=-1;
      If (Cdet!=Cdeto) CALL GLOOK(Cdet, IQ(LKDETM+1),IQ(LKDETM-1),Idet)
      Cdeto=Cdet;  Check Idet>0
*                                     attempt to reconsile with DICE
      If      Stage=='RECO'  { Check LVRECO(Idet)>0; }
      Else If Stage=='ANAL'  { Check LVANAL(Idet)>0; }
      Else If Stage!='UNKN'  { Check LVGEOM(Idet)>0; }
*
      AgPFLAG = max(LVPRIN(Idet),LWPRIN(Idet),IDEBUG)
      If (stage!=stageo) CALL GLOOK(Stage,IQ(LKDETM+1),IQ(LKDETM-1),Ista)
      If (Ista>0) AgPFLAG*=max(LVPRIN(Ista),LWPRIN(Ista),IDEBUG)
*     print *,' AFPFLAG: module,stage,flag=',cdet,stage,agpflag
      stageo=stage
   END
 
 
*CMZ :  1.30/00 17/04/97  16.06.21  by  Pavel Nevski
*CMZ :  1.00/00 09/08/95  15.18.33  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
****************************************************************************
*                                                                          *
                 subroutine   A g D R O P (Title)
*                                                                          *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEND.
 character*(*) Title;  Character*1 Com;
 com=title;  If (Title=='ALL') Com='*';
 if (com='G'|com='G') & JRUNG >0  { Call MZDROP(IxStor,JRUNG ,'L');           }
 if (com='A'|com='-') & JMATE >0  { Call MZDROP(IxStor,JMATE ,'L');  NMATE=0; }
 if (com='M'|com='-') & JTMED >0  { Call MZDROP(IxStor,JTMED ,'L');  NTMED=0; }
 if (com='P'|com='-') & JPART >0  { Call MZDROP(IxStor,JPART ,'L');  NPART=0; }
 if (com='V'|com='*') & JROTM >0  { Call MZDROP(IxStor,JROTM ,'L');  NROTM=0; }
 if (com='V'|com='*') & JVOLUM>0  { Call MZDROP(IxStor,JVOLUM,'L');  NVOLUM=0;}
*if (com='V'|com='*') & JGPAR >0  { Call MZDROP(IxStor,JGPAR, 'L');  JGPAR=0; }
*if (com='V'|com='*') & JGPAR2>0  { Call MZDROP(IxStor,JGPAR2,'L');  JGPAR2=0;}
 if (com='S'|com='*') & JSET  >0  { Call MZDROP(IxStor,JSET  ,'L');           }
 if (com='S'|com='*') & JHITS >0  { Call MZDROP(IxStor,JHITS ,'L');           }
 if (com='S'|com='*') & JDIGI >0  { Call MZDROP(IxStor,JDIGI ,'L');           }
 if (com='D'|com='*') & LKDETM>0  { Call MZDROP(IxStor,LKDETM,'L');           }
 if (com='D'|com='*') & L1Doc >0  { Call MZDROP(IxStor,L1Doc, 'L');           }
 if (com='R'|com='*') & LKRUNT>0  { Call MZDROP(IxStor,LKRUNT,'L');           }
 if (com='R'|com='*') & LKEVNT>0  { Call MZDROP(IxDiv, LKEVNT,'L');           }
 if (com='R'|com='*') & LKARAW>0  { Call MZDROP(IxDiv, LKARAW,'L');           }
 if (com='R'|com='*') & LKARP1>0  { Call MZDROP(IxDiv, LKARP1,'L');           }
 if (com='E'|com='*')             { Call MZWIPE(IxDiv); NTRACK=0; NVERTX=0;   }
 if  com='*'        { call MZGARB(20,0); <w>;(' *** all banks DROPPED *** '); }
 NLEVEL = 0
    END
 
*CMZ :  1.30/00 03/08/96  17.13.04  by  Pavel Nevski
*CMZ :  1.00/00 04/12/94  14.38.39  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Function     A R F R O M C (Cvar)
*                                                                    *
*  Description:  4-character  to a real number conversion            *
**********************************************************************
Real ARFROMC;  Character Cvar*(*),C*4,S*64;  Integer I,K;
Data S/' 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz '/;
     C=Cvar;  k=0;
     Do i=1,4 { k=ISHFT(k,6); k+=Index(s(2:64),c(i:i)); }
     ARFROMC=k;
   END
 
*CMZ :  1.30/00 03/08/96  16.52.41  by  Pavel Nevski
*CMZ :  1.00/00 04/12/94  14.38.39  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 Function     A C F R O M R (R)
*                                                                    *
*  Description: real to 4-character conversion                       *
**********************************************************************
Real R;   Character ACFROMR*4,C*4,S*64;  Integer I,J,K;
Data S/' 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ '/;
     C=' ';   k=R;
     Do i=4,1,-1  { j=IAND(k,63)+1; k=ISHFT(k,-6); C(i:i)=S(j:j); }
     ACFROMR=C;
   END
 
 
*CMZ :  1.00/00 03/02/95  01.15.24  by  Pavel Nevski
*-- Author :    Pavel Nevski   22/01/95
**********************************************************************
*                                                                    *
              SUBROUTINE A G P H I T S (CSET,CDET)
*                                                                    *
*  Description:   print GEANT hits summary in the ATLAS dense format *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      INTEGER       IBITS,JS,JD,JDX,JX,JXD,JDU,Nw,Nd,Nv,Nk,Nb,ii,I,J,K,
                    Nset,Ndet,Last,Kdigi,Iset,Idet,Ltra,i1,Nvu,Ndu,IHIT,
                    ITRA,Nhits,Ind,Mind,NUMBV(15),NHIT(100);
      REAL          Sumt,DIGI(20),SUM(100);
      CHARACTER*4   CSET,CDET,CS,CD;
 
   Check JhitS>0;  NSET=IQ(JSET-1);   " first make selection using SETS "
   DO ISET=1,Nset     "             Loop on all selected sets        "
   {  CALL UHTOC(IQ(JSET+ISET),4,CS,4);  Check CSET(1:1)='*' | CSET=CS;
      JS = LQ(JSET-ISET);   Check Js>0;  Ndet=IQ(JS-1);
      Do IDET=1,NDET  "         Loop on selected detectors for this set "
      {  CALL UHTOC(IQ(JS+IDET),4,CD,4); Check CDET(1:1)='*' | CDET=CD;
 
                                      " now check the HITS structure "
         JX   = LQ(JhitS-ISET);        Check JX>0;
         JXD  = LQ(JX-IDET);           Check JXD>0;
         LAST = IQ(JX+IDET);           Check LAST>0;
         JD   = LQ(JS-IDET);           Check Jd>0;
         JDX  = LQ(JD-1);              Check JDX>0;
         NW   = IQ(JD+1)+IQ(JD+3)+1;   Check Nw>0;
         NV   = IQ(JD+2);              ND  = IQ(JD+4);
         JDU  = LQ(JD-3); If JDU>0   { NVU = Q(JDU+6);  NDU = Q(JDU+2); }
 
         { Mind,Sumt,Nhits,ITRA,NUMBV(1),DIGI(1) } = 0;
         Call Vzero(Sum,100);  Call Vzero(Nhit,100);
         " loop on all hits to get track numbers, volume numbers and info "
         Do ii=1,LAST,NW
         {  j=JXD+ii;  LTRA=IQ(j);   NK=1; K=1;
            DO I=1,min(1,NV)  "      get unpacked volume numbers              "
            {  Nb=IQ(JD+2*I+10);
               IF Nb>0  { K+Nb>33 ?; NUMBV(i)=IBITS(IQ(j+Nk),K-1,Nb); K+=Nb; }
               else     { K>1     ?; NUMBV(i)=IQ(j+Nk);               Nk+=1; }
            }
                                     Nk=1+IQ(JD+1); K=1;
            Do I=1,min(1,ND)  "      get unpacked cumulative hits             "
            {  i1=Jdx+4*(I-1); Nb=IQ(i1+2);  Ihit=IQ(i1+1);
               IF Nb>0  { K+Nb>33 ?; KDIGI=IBITS(IQ(j+Nk),K-1,Nb); K+=Nb; }
               else     { K>1     ?; KDIGI=IQ(j+Nk);               Nk+=1; }
               DIGI(i)=KDIGI/Q(i1+4)-Q(i1+3);
            }
            Ind=min(max(1,NUMBV(1)+1),100);  Nhit(Ind)+=1;  Sum(Ind)+=Digi(1);
            Nhits+=1; Sumt+=Digi(1);  Mind=Max(Mind,Ind); ITRA=max(ITRA,LTRA);
         }
         <W> Cd,Cs,ITRA;
         (/' HITS summary in detector ',A4,' of SET ',A4,' on',i6,' tracks');
         <w> Nhits,    (Nhit(i),i=1,Mind); ('  Hits: ',11I10  /(18x,10i10));
         <w> Ihit,Sumt,(Sum(i) ,i=1,Mind); (2x,a4,': ',11G10.3/(18x,10G10.3));
   }  }
   END
 
 
*CMZ :  1.30/00 28/04/96  19.59.55  by  Pavel Nevski
*CMZ :  1.00/00 21/03/95  15.01.57  by  Pavel Nevski
*-- Author :    Pavel Nevski   21/03/95
****************************************************************************
*                                                                          *
                SUBROUTINE   A G S F L A G (CflagI,Iflag)
*                                                                          *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEND.
     character*4 CflagI,Cflag
     Integer     Iflag
     Cflag=CflagI;       Call CLTOU(Cflag)
     If (Cflag='PRIN')   %Iprin=Iflag
     If (Cflag='GRAP')   %Igrap=Iflag
     If (Cflag='HIST')   %Ihist=Iflag
     If (Cflag='GEOM')   %Igeom=Iflag
     If (Cflag='MFLD')   %Imfld=Iflag
     If (Cflag='DEBU')   %Idebu=Iflag
     If (Cflag='SIMU')   %Isimu=Iflag
     CALL AsbDETE('flag'//CFLAG,Iflag)
END
 
 
*CMZ :          27/08/97  14.26.21  by  Pavel Nevski
*CMZ :  1.00/00 06/06/95  15.09.02  by  Pavel Nevski
*-- Author :    Pavel Nevski   07/02/95
**********************************************************************
*                                                                    *
         subroutine     A g F P A T H (ISC)
*                                                                    *
* Description:  build geant path to a sensitive element ISC          *
*              Set/det should be already selected - only JDU is used *
* Modifications:                                                     *
* 27.08.97,  PN: zero in an ISC means the last possible copy number  *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
  Integer  ISC(*),nam,nom,nick,Ier,I,J,K,L,N,Nb,i1,i2,Jm,Imo,Ivo,nin,
           in,jn,Nr,NwuVol/3/
  Integer  Lnam(20),Lnom(20),Lnum(20),Ivol(20)
  Save     Lnam,Lnom,Lnum,Ivol
*
  Check Jdu>0;
  i1=Q(Jdu+3);  i2=Q(Jdu+5);  N=Q(Jdu+4);  {L,K,Imo}=0;
  :L: Do i=i1,i2-1,NwuVol
  {  j=Jdu+i;         Nb=Q(j+3);    IF (Nb>0) K+=1;    L+=1;
     Ivo=Q(j+1);      nam=IQ(Jvolum+Ivo);    {Lnam(L),Lnom(L)}=nam;
     Lnum(L)=Q(j+2);  IF (Nb>0) Lnum(L)=ISC(K);
     If  L=1          { Ivol(1)=Ivo;  Next :L:; }
     Imo=Ivol(L-1);   Jm=LQ(JVOLUM-Imo);
     nin=Q(jm+3);     If L<N & nin=0
     { <w> nam,L,N; (' AGFPATH: empty ',a4,' at level',2i5);    Break; }
*
     " find copy with the same generic name as NameSH element "
     do in=1,max(nin,1)   " over number of contents "
     {  jn=LQ(Jm-in); Ivo=Q(jn+2); Nr=Q(jn+3);
        Nom=IQ(LQ(JVOLUM-Ivo)-4);  Nick=IQ(JVOLUM+Ivo);
        Check nam=nom | nam=Nick;
        " special request - last copy "
        If k>0 & ISC(k)==0 & Nr>Lnum(L)
        { Lnum(L)=Nr; Lnam(L)=IQ(JVOLUM+Ivo); IVOL(L)=Ivo; Next; }
        " normal request - selected copy "
        Check nin>0 & Lnum(L)=Nr | nin<0 & 0<Lnum(L)&Lnum(L)<=Nr
        Lnam(L)=IQ(JVOLUM+Ivo);    IVOL(L)=Ivo;        Next :L:;
     }
     if k>0 & ISC(k)==0  { ISC(k)=Lnum(L); Next :L:; }
 
     if (Idebug>0) <w> nam,L
     (' AGFPATH: can not find ',a4,' at level',i5); L-=1; Break;
  }  CALL GLVOLU (L,Lnam,Lnum,IER);
*
  END
 
 
*CMZ :  1.30/00 18/04/96  17.09.45  by  Pavel Nevski
*CMZ :  1.00/00 07/05/95  00.09.13  by  Pavel Nevski
*-- Author :    Pavel Nevski
*************************************************************************
      subroutine     A G S S T E P (ext)
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
   external ext;   Integer JUMPAD,Ldete,L,Id;
   call AsbDETE(%Module,Id);
   If (Id != %IdType) print *,'Id inconsistent - ',Id,%Idtype
   Ldete=LQ(LKDETM-Id);   L=IQ(Ldete-1);
   If L>12 {  IQ(Ldete+13)=JUMPAD(ext) }   else    {  <W>;
   (' AgSSTEP warning: you need a modified DETM format to run this option')}
      end
 
*CMZ :  1.30/00 02/04/97  18.53.55  by  Pavel Nevski
*CMZ :  1.00/00 04/06/95  23.36.31  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/12/94
**********************************************************************
*                                                                    *
                SUBROUTINE A g G E T D I G  (JD,JJ,NBV,DIGI)
*                                                                    *
*  Description: Common hit/digi unpacking for any AGI routine        *
*          JD is the link to SEJD bank, JJ is link to a hit/digi     *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
   integer            idigi
   Common   /AgCdigi/ idigi(15)
*
   INTEGER     JD,JJ,JDS,Nv,Nk,No,Nb,I,J,K,L,j1,j2,Idig,Ihitf,bin,mode,
               JBYT,NBV(15),NwuVol/3/,NwuHit/10/
   REAL        Org,Fct,Fmx,xx,D,DIGI(15)
   bin(xx)  =  IFIX((xx+org)*fct)
*
*                            get SJDU link and set common counters
     NK=jj+1;  K=1;  D=0.5;  Jds=LQ(JD-3);  Nv=IQ(JD+2);
*                            get unpacked branching volume numbers
     j1=Q(Jds+3);  j2=Q(Jds+5)-1;  i=0;
     Do j=j1,j2,NwuVol
     {  L=Jds+j;  Nb=Q(L+3);  Check Nb>0;
        I+=1;  K+Nb>33?;  NBV(i)=JBYT(IQ(Nk),K,Nb)+1; K+=Nb;
     }
     Ihitf=Nv-I;  mode=0;  I=0;    " Ihitf - start of geant HIT field        "
     j1=Q(Jds+1);  j2=Q(Jds+3)-1;
     Do j=j1,j2,NwuHit             "         unpacked digits                 "
     {" No - requested Nbit (if not MAGIC), Nb - allocated (always positive) "
        L=Jds+j;  No=Q(L+3); Org=Q(L+6); Fct=Q(L+7); Fmx=Q(L+5); Nb=Q(L+8);
        If I==Ihitf               {" geant HIT field "  K>1 ?;  D=0;    }
        If -32<=No&No<=0 & mode=0 {" comulative part "  K>1 ?;  Mode=1; }
        IF 0<Nb&Nb<32  { K+Nb>33 ?;  IDIG=JBYT(IQ(Nk),K,Nb);  K+=Nb; }
        else           { K>1     ?;  IDIG=IQ(Nk);             Nk+=1; }
        I+=1;      DIGI(i)=min((IDIG+D)/fct-Org,fmx);  idigi(i)=IDIG
        If I==1
        { while LQ(Jds)>0 & bin(Q(LQ(Jds)+8))<=IDIG { Jds=LQ(Jds) }}
     }
   END
 
 
*CMZU:  1.00/01 15/11/95  02.08.58  by  Pavel Nevski
*CMZ :  1.00/00 05/10/95  02.29.43  by  Pavel Nevski
*-- Author :    Pavel Nevski   17/01/95
**********************************************************************
*                                                                    *
   subroutine   A G F D I G I (Cset,Cdet,NVS,LTRA,NBV,DIGI,Iw,Iad)
*                                                                    *
* Returns the next digitisation for the physical volume, specified   *
* by NVS list with generic volume/set name Cdet/Cset,packed form     *
* INPUT:                                                             *
* Cset,Cdet - user set/detector identifiers (CHAR*4)                 *
* NVS - list of volumes identifying the path, ignored if nvs(1)<0    *
* OUTPUT:                                                            *
* LTRA the number of the track which has produced this digitisation  *
* NBV  the list of volume numbers which identify the physical volume *
* KDIGI       array that get the digitalisation elements             *
* ====>  User should take care of NVB and KDIGI real dimesions !     *
* Iw - Hit sequential number. It is negative, if SET/DET does not    *
*      exist at all, and 0 when hits are absent or all hits are done *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
  CHARACTER*4 Cset,Cdet,Cset0/'****'/,Cdet0/'****'/
  Integer     Nvs(*),NBV(*),LTRA,NTRA,Iw,Iad,JH,Iset,Idet,I,J,ii,X
  Real        DIGI(*)
* - - - - - - - - - - - - - - - - - - - - - - - - -
IF Iw<=0 | Cset!=Cset0 | Cdet!=Cdet0
{  Check Jset>0;   {Jdu,Last}=0;   Iw=-1;
   Call  MZLINT(IxSTOR,'AGCRDIG',IWA,JS,Jdu);
   "  Find if digi in selected set & detector exist  "
   Call GLOOK(Cset,IQ(Jset+1),IQ(Jset-1),Iset);             Check Iset> 0;
   JS  = LQ(Jset-Iset);                                     Check Js  > 0;
   Call GLOOK(Cdet,IQ(JS + 1),IQ(JS - 1),Idet);             Check Idet> 0;
   JD  = LQ(JS-Idet);                                       Check JD  > 0;
   JDU = LQ(JD-3);    Cset0=Cset;    Cdet0=Cdet;     Iw=0;
   if Cset(4:4)=='H' {X=1; JH=JHITS} else {X=2; JH=JDIGI};  Check JH  > 0;
   Jx  = LQ(JH-Iset);                                       Check Jx  > 0;
   JXD = LQ(JX-Idet);                                       Check JXD > 0;
   Last= IQ(JX+Idet);                                       Check Last> 0;
   NW  = IQ(JD+1)+IQ(JD+2*X+1)+1
   Nvb = Q(JDU+6)
   if (IW<0) IW  = 0
}
If jdu<=0  { call GFDIG1(Cset,Cdet,1,NVS,LTRA,NTRA,NBV,DIGI,Iw,Ia); Return; }
*
:D: DO ii=Iw*Nw+1,Last,Nw
 {  j=JXD+ii;   LTRA=IQ(j);   Call AgGETDIG(Jd,J,NBV,DIGI)
    do i=1,Nvb  { If (NVS(i)>0 & NVS(i)!=NBV(i)) Next :D:; }
    iw=ii/Nw+1; Iad=J;                           Return;
 }
   {iw,iad,IWA(1)}=0;
   END
 
 
*CMZ :          24/04/98  16.58.32  by  Pavel Nevski
*CMZ :  1.30/00 13/05/97  14.48.21  by  Pavel Nevski
*CMZ :  1.00/00 01/09/95  22.54.27  by  Pavel Nevski
*-- Author : Pavel Nevski
**********************************************************************
*                                                                    *
             Function     A g F D I G 0 (Cset,Cdet)
*                                                                    *
*  Prepare hits for digitization making chains in each element       *
*  modifications: 1.09.95 - protect agains 0 path     - PN           *
*  25.01.96 - invert hits order as suggested by Fred                 *
*  01.05.97 - check consistency between sets and hits/digi structure *
*  13.05.97 - on error keep Iv=-1 to stop AgFDIG1                    *
*  02.04.98 - accept wildcard (*) for Cdet (Idet=1)                  *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
Character*(*)    Cdet,Cset;   Integer Lp,Lt;  Parameter (Lp=20,Lt=100);
Integer          AgFDIG0,JBYT,MSBYT,LENOCC,ICDECI,NVL(Lp),ISC(Lp),Itr,
                 Iset,Idet,X,Nv,Nr,Nb,Ja,i,j,k,L,Na,Ma,Jv,Nk,Ih,JH,Mbm,Ier
integer          nac,nas,iac,itc,jtr
common/agctrbuf/ nac,nas,iac(50000),itc(50000)
*
   Cs=Cset;  Cd=Cdet;  {AgFDIG0,Iv,Ia}=-1;  {Iset,Idet,Jdu}=0;
   CALL MZLINT (IXSTOR,'AGCRDIG',IWA,JS,JDU);
*
   "  Find if hits in selected set & detector exist  "
   Call GLOOK(Cs,IQ(Jset+1),IQ(Jset-1),Iset);               Check Iset> 0;
   JS  = LQ(Jset-Iset);                                     Check Js  > 0;
   Call GLOOK(Cd,IQ(JS + 1),IQ(JS - 1),Idet);
   if (Cd=='*' & IQ(JS-1)>0 & IQ(Js+1)!=0) Idet=1;          Check Idet> 0;
   JD  = LQ(JS-Idet);                                       Check JD  > 0;
   JDU = LQ(JD-3);                                          Check Jdu > 0;
   if Cset(4:4)=='H' {X=1; JH=JHITS} else {X=2; JH=JDIGI};  Check JH  > 0;
   Ier = 1;          If (Iset>IQ(JH-2))                     goto :e:
   Jx  = LQ(JH-Iset);                                       Check Jx  > 0;
   Ier = 2;          If (Idet>IQ(Jx-2)|Idet>IQ(Jx-1))       goto :e:
   JXD = LQ(JX-Idet);                                       Check JXD > 0;
   Last= IQ(JX+Idet);                                       Check Last> 0;
*
   Nw=IQ(JD+1)+IQ(JD+2*X+1)+1;  Nvb=Q(Jdu+6);  Nv=IQ(JD+2); Nc1=Last/Nw;
   Ier = 3;          If (mod(last,nw)!=0)                   go to :e:
   Nr=0;  if (LENOCC(Cdet)>=6)  Nr=ICDECI(Cdet,5,6);   Nvb=min(Nvb+Nr,Nv);
   Call VZERO(NVL,Lp);          Mb=0; i=Nc1; while i>0 {i/=2; Mb+=1;};
   If Mb>1  { Mbm=2**(32-Mb) } else { Mbm=2 000 000 000 "big positive" }
*
   Ier=0; last=Nc1+1; jtr=-1; Nac=0
   do ih=1,Nc1
   {  j=JXD+(Ih-1)*Nw+1; itr=IQ(J);
      If itr>Ntrack & ier<=Idebug
      { ier+=1; <w> Cset,Cdet,itr;(' AgFDIG0 error in',2a5,': bad ITRA=',i12)}
      if jtr!=itr { Nac+=1; jtr=itr; }
   }
   nas=Nac/Mbm+1; jtr=-1; Nac=0
   do ih=1,Nc1
   {  j=JXD+(Ih-1)*Nw+1; itr=IQ(J);
      if jtr!=itr { nac+=1; iac(nac)=ih; itc(nac)=itr; jtr =itr; }
      IQ(J)=(nac-1)/nas
   }  iac(nac+1)=Nc1+1
*
   "       ----------      associate hits in chains     ---------    "
   call VZERO(Ibuf,Lbuf); Na=1; Ma=0; ISC(1)=1; ier=0;
   Do Jv=1,max(1,Nvb)                      " for all higher levels   "
   {  Do Ih=Nc1,1,-1                       " rescan all hits to find "
      {  Nk=1; K=1; J=JXD+(Ih-1)*NW+1;     " the actual maximum of   "
         do Iv=1,min(Jv+1,Nvb)             " the volume number used  "
         { Nb=IQ(JD+2*Iv+10); K+Nb>33?; ISC(iv)=JBYT(IQ(j+Nk),K,Nb)+1; K+=Nb;}
         *                                   now get buffer address
         Ia=1; do i=1,Jv { Ja=Ia+ISC(i); Ia=IBuf(Ja);}  Ma=max(Ma,Ja);
         If Jv<Nvb { IBuf(Ja)=max(Ia,ISC(Jv+1)); }
         else
         {   itr=IQ(J);  IQ(J)=MSBYT(Ia,Itr,33-Mb,Mb);  IBuf(Ja)=Ih; }
      }  If (Jv=1) Ibuf(1)=Ma-1;
      *
      Ja=Ma+1;  "expand array"  While Ibuf(Na)>0 & Na<Ma & Jv<Nvb
      {  Do Ia=1,Ibuf(Na)
         {  L=Ibuf(Na+Ia); Check L>0; Ibuf(Na+Ia)=Ja; Ibuf(Ja)=L; Ja+=1+L;
            Check Ja>Lbuf; Ibuf(Na+Ia)=0;  <W> Cset,Cdet;
            (' AgFDIG0: NOT ENOUPH MEMORY FOR',2(1x,A),', HITS WILL BE LOST');
         }  Na+=1+Ibuf(Na);
   }  }
   {AgFDIG0,Iv,Ia,nc2}=0
   If (Last<Nc1)  <W> Cset,Cdet,Mbm,int(Q(LQ(Jkine-Mbm)+6))
   (' AgFDIG0 WARNING FOR',2(1x,a),': TRACKS ABOVE',2i12,' WILL BE chitted')
   return
   :e: <w> ier,Cset,Cdet
   (' AgFDIG0 FATAL ERROR:',i3,' Probably inconsistent geometry ',2(1x,a4))
   {AgFDIG0,Iv,Ia,nc2}=-1
   END
 
 
*CMZ :          24/04/98  16.58.32  by  Pavel Nevski
*CMZ :  1.30/00 13/05/97  14.48.21  by  Pavel Nevski
*CMZ :  1.00/00 01/09/95  22.55.18  by  Pavel Nevski
*-- Author : Pavel Nevski
**********************************************************************
*                                                                    *
     Function     A g F D I G 1 (NHit,LTRA,ISC,HITS)
*                                                                    *
* Description:  make a loop over detector elements and give to user  *
*               all hits in the selected element sequentially        *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
integer           nac,nas,iac,itc,jtr
common /agctrbuf/ nac,nas,iac(50000),itc(50000)
                 Integer Lp; Parameter (Lp=20);
Integer          AgFDIG1,ISC(*),NVL(Lp),JBYT,Nhit,LTRA,ja,Itr,Lev,i
Real             HITS(*);
Save             NVL;
*
   Lev=0     " will be set to the lowest Iv of the volume index been changed "
If Iv>=0     " Iv - the last changed level is saved in the AGCHIT common     "
{  If Ia==0
   {  Lev=LP; Nhit=0;
      :a:;If (Iv>0) NVL(Iv)+=1;  call UZERO(NVL,Iv+1,Lp);
          Lev=min(max(1,Iv),Lev);
          Ia=1; Iv=0; While Iv<max(1,Nvb)       " bootstrap index "
          {  IF NVL(Iv+1)>=Ibuf(Ia) { If (Iv==0) goto :e:; goto :a:; }
             Iv+=1;  Ia=IBuf(Ia+NVL(Iv)+1);   If (Ia=0) goto :a:;
   }      }
                               * * *
   "   getting a hit in the selected element and the address of the next "
   Ja=JXD+Nw*(Ia-1)+1;   call  AgGETDIG (JD,Ja,ISC,HITS);
   "   get track number, check for the track overlap, clear track number "
 
   jtr=JBYT(IQ(ja),1,32-Mb)*nas;
   do i=1,nas { itr=itc(jtr+i); if (iac(jtr+i+1)>Ia) break; }
*
   If (Nhit=0) LTRA=ITR;      If (LTRA#ITR) LTRA=-ITR
   Ia=JBYT(IQ(ja),33-Mb,Mb);  IQ(Ja)=Itr
                              * * *
   " Count hits in the same element, the last one get Nhit negative "
   Nhit+=1; If (Ia=0) Nhit=-Nhit; Nc2+=1;  AgFDIG1=0; "intermediate" Return;
}
   :e:   IWA(1)=0;                         AgFDIG1=-1; "  final  "   Return;
   END
 
 
*CMZ :  1.30/00 06/05/97  15.20.30  by  Pavel Nevski
*CMZU:  1.00/01 13/12/95  16.02.30  by  Pavel Nevski
*CMZ :  1.00/00 07/10/95  23.14.29  by  Pavel Nevski
*-- Author :    Pavel Nevski   03/06/95
************************************************************************
*                                                                      *
         SUBROUTINE A G F D P A R (hits,Chit,FHmin,FHmax,FHbin)
*                                                                      *
*  Description: provides user description of the hit/digi format       *
*               Set/det should be already defined - only JDU is used   *
*               First free element of CHIT is set to blank.            *
*               If No description is available at all, CHIT(1)=blank   *
*               For vectorised hits ONLY: CHIT(1) is also blank        *
*               if HITS(1) is outside any of the defined regions       *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
     Real         HITS(*),FHmin(*),FHmax(*),FHbin(*),Org,fct,fmx,xx
     Integer      j1,j2,I,J,K,K2,L,Ju,Jn,bin,NwuHit/10/,%Magic/-696969/
     character*4  Chit(*),ACFROMR
     bin(xx)=IFIX((xx+org)*fct)
*
     Chit(1)=' ';  Check Jdu>0;  Ju=Jdu;  j1=Q(Ju+1);  j2=Q(Ju+3)-1;  i=0;
     Do j=j1,j2,NwuHit       "         unpacked digits                   "
     {  L=Ju+j;  Fmx=Q(L+5);  Org=Q(L+6);  fct=Q(L+7);
        If i==0 &  Q(Ju+8)>%Magic
        {  * only for vectorised hit definition
           if (Org>hits(1) | hits(1)>Fmx)   "outside all(a,b)"  Return
           K=bin(hits(1));  K2=bin(Q(ju+8));  If (K<K2) "below" Return
           While K>K2                       "find a valid region"
           { Jn=LQ(Ju); If (Jn<=0) Return; K2=bin(Q(Jn+8)); If (K>=K2) Ju=Jn }
        }
        I+=1; Chit(i)=ACFROMR(Q(L+1)); Fhmin(i)=-Org;  Fhmax(i)=Fmx;
        if (fct!=0) FHbin(i)=1.0/fct
     }  Chit(i+1)=' '
    END
 
 
*CMZ :          23/10/97  22.22.23  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  18.53.55  by  Pavel Nevski
*CMZ :  1.00/00 03/06/95  12.02.49  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/12/94
**********************************************************************
*                                                                    *
                SUBROUTINE A G P D I G I (CSET,CDET)
*                                                                    *
*  Description: print GEANT hits or digits                           *
*  If USER bank is there this is the AGI dense format                *
*  FOR OTHER APPLICATION PLEASE TAKE CARE OF THE NAMING CONVENTION:  *
*  Nv,Nx(=h/d) for original geant counters, Nha,Nvb for AGI counters *
**********************************************************************
 Replace [;#?;]   With   [; IF #1 {" Take next word " K=1; Nk+=1; } ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
     INTEGER       JS,JD,JH,JX,JXD,JDU,Ip0,Ip1,Nw,NVb,Nha,Mv,Md,
                   Nset,Ndet,Last,Iset,Idet,Ltra,Idig,ii,jj,X,i,
                   JBYT,NBV(15)
     REAL          DIGI(20)
     CHARACTER     CBUF*400,T*6
     CHARACTER*4   ACFROMR,CSET,CDET,CS,CD,CDID
*
 NSET=IQ(JSET-1)    "           first make selection using SETS    "
 DO ISET=1,Nset     "             Loop on all selected sets        "
 { CALL UHTOC(IQ(JSET+ISET),4,CS,4);  Check CSET(1:1)='*' | CSET=CS;
   JS = LQ(JSET-ISET);   Check Js>0;  Ndet=IQ(JS-1);
   Do IDET=1,NDET  "         Loop on selected detectors for this set "
   { CALL UHTOC(IQ(JS+IDET),4,CD,4);  Check CDET(1:1)='*' | CDET=CD;
*
                                     " now check the DIGI structure "
     JD  = LQ(JS-IDET);           Check Jd>0;
     If LQ(JD-2)>0                { T='DIGITS'; JH=JDIGI; X=2;  }
     If LQ(JD-1)>0                { T=' HITS '; JH=JHITS; X=1;  }
                                  CHECK JH>0;
     JX   = LQ(JH-ISET);          Check JX>0;
     JXD  = LQ(JX-IDET);          Check JXD>0;
     LAST = IQ(JX+IDET);          Check LAST>0;
     JDU  = LQ(JD-3);
     IF JDU<=0
     {  CALL UHTOC(IQ(JXD-4),4,CDID,4);
        IF CDID=='DIGI' { CALL GPDIGI(CS,CD) } else { Call GPHITS(CS,CD) }
        Next;
     }
     " otherwise this are hits(SJHD) or new digits(SJDX) "
     NW = IQ(JD+1)+IQ(JD+2*X+1)+1;   Check Nw>0;
     " volumes "  Nvb = Q(JDU+6);  Mv = Min(Nvb,15);  Ip0 = 12+5*Mv;
     " all hits " Nha = Q(JDU+2);  Md = Min(Nha,20);  Ip1 = Ip0+10*Md+2;
*
     <W> T,Cd,Cs;
     (/' ====>',A6,' IN DETECTOR ** ',A4,' ** OF SET ** ',A4,' ** <===='/);
     Cbuf=' '                                   "  print header line ";
     WRITE(CBUF,'(1x,A5,6H TRACK,15(1x,A4))')  T,(IQ(JD+2*I+9),i=1,Mv);
     WRITE(CBUF(Ip0+1:),'(20(6x,A4))') (ACFROMR(Q(JDU+10*I+1)),i=1,Md);
     <W>  (CBUF(i:i),i=1,Ip1);     (122A1/(12x,110A1));
     IDIG=0;
     Do ii=1,LAST,NW
     {  jj=JXD+ii; IDIG+=1; LTRA=JBYT(IQ(jj),1,16);
        Call  AGGETDIG (Jd,jj,NBV,DIGI);
        WRITE(CBUF,        '(2i6,15i5)')     IDIG,LTRA,(NBV(i),i=1,Mv)
        WRITE(CBUF(IP0+1:),'(2x,1P,20G10.3)')         (DIGI(i),i=1,Md)
        <W>  (CBUF(i:i),i=1,Ip1);  (122A1/(12x,110A1));
     }
 } }
   END
 
 
*CMZ :  1.30/00 18/11/96  12.59.52  by  Pavel Nevski
*CMZU:  1.00/01 22/12/95  21.09.57  by  Pavel Nevski
*CMZ :  1.00/00 08/11/95  00.05.48  by  Pavel Nevski
*-- Author :    Pavel Nevski   12/08/95
**********************************************************************
            subroutine  A G D L I N K (Module,Bank,Link,LK)
*            Register a new link for dynamic bank access             *
*  keep them names now in a common, but can be an internal array too *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agclink.
*   links for dynamic banks access
       INTEGER    NALINKMAX,AG_NLINK,AG_LINK
       PARAMETER  (NALINKMAX=100)
       COMMON /AGCLINK/ AG_NLINK,AG_LINK(0:NALINKMAX)
*      - - - - - - - - - - - - - - - - - - - - - -
 
*KEND.
Character         Module*(*),Bank*(*),Cbank*8
Integer           NumLin,LinkName,Link,Lk,Key(2),LENOCC
Common /AGCDLINK/ NumLin,LinkName(2,NaLinkMax)
 
If Link<0  " allocate a new secured link "
{  Cbank=Bank(1:lenocc(Bank))//module;  Call UCTOH(CBank,Key,4,8)
   If (%Nlink==0) call MZLINK(IxCONS,'AGCLINK',%Link,%Link,%Link(NaLinkMax))
   Do Link=1,NumLin
   {  If (Key(1)==LinkName(1,link) & Key(2)==LinkName(2,link)) goto :fnd:; }
 
   If NumLin>=NaLinkMax
   {  Print *,'AGDLINK fatal error: NO more free links left for bank ',Bank;
      Link=NaLinkMax; Return
   }
   NumLin+=1; %NLink=NumLin; Link=NumLin; Call Ucopy(Key,LinkName(1,link),2)
   If (IDEBUG>0) Print *,'AGDLINK: new link for bank ',bank,' is ',link
}
:fnd: If (Link>=0)  %LINK(link)=Lk
End
 
 
*CMZ :          13/03/98  22.56.27  by  Pavel Nevski
*CMZ :  1.30/00 01/07/96  15.35.02  by  Pavel Nevski
*CMZ :  1.00/00 07/09/95  13.27.40  by  Pavel Nevski
*-- Author :    Pavel Nevski   12/08/95
*************************************************************************
        Subroutine   A g D F O R M (Names,map,LL1,LL,Cformo,Cforma)
*                    encode bank format for zebra                       *
*   Both new (with 2 system words) and old (only users words) formats   *
*   PN,29-06-96: Make Cform different from Cformo due to AIX problem    *
*************************************************************************
Implicit      NONE
Integer       LL1,LL,map(2,LL1),i,j,k,L,N,NN,Ls
Character     Names(LL1)*(*),Cformo*80,Cforma*80,Cform*80,cf*8,T*1,S*1
Logical       NoTail/.true./
*
*                   count the total mapped bank length
Cformo='-F'; n=0; do i=1,LL1
{  k=1;  if (map(1,i)>0 & map(2,i)>0) k=map(1,i)*map(2,i);  n+=k; }
 
*          for 'old' format n should be the same as LL, the rest is a header
if  n==LL { T=' '; nn=0; }   else if  n+2=LL   { T='F'; nn=2; }
else      { print *,' AgDFORM error detected: N,L=',n,LL,LL1;
            do i=1,LL1 { print *,' i,map =',i,map(1,i),map(2,i),' ',names(i) }
            Return
          }
*
Cform='/';  L=1;
do i=1,LL1+1
{  If i<=LL1
   {  k=1;  if (map(1,i)>0 & map(2,i)>0) k=map(1,i)*map(2,i);
      S=Names(i); If (S!='I' & S!='H') S='F';  If S==T { nn+=k; Next; }
   }
   if T!=' '                   " write previous format element "
   {  L+=1;  write(cf,'(i8)') nn;  Ls=L+1;
      If L>70 { print *,' AgDFORM error: format too long for ',names; break;}
      do j=1,8 { if Cf(j:j)!=' ' { L+=1; Cform(L:L)=Cf(j:j) } }
                                   L+=1; Cform(L:L)=T;
   }  nn=k; T=S;
}
*
   if NoTail & Ls>3 { cformo=cform; cform(Ls:)='-'//T; cforma=cform(3:Ls+1) }
   else             { cforma=cform; cform(Ls:)='-'//T; cformo=cform(3:Ls+1) }
   " print *,' cformo,Ls = ',cformo(1:20),Ls "
*
end
 
 
*CMZ :  1.00/00 14/08/95  03.36.26  by  Pavel Nevski
*-- Author :    Pavel Nevski   14/08/95
************************************************************************
                Subroutine    A g D T I T (MTitle,Tshort)
*      make reasonable title cut by rejecting some trivial words       *
************************************************************************
  Implicit      none
  Character*(*) MTitle,Tshort
  Integer       Lenocc,Ntriv,i,j,k,is
  Parameter     (Ntriv=11)
  Character*12  word,trivial(Ntriv)
  Data          Trivial/' ','THIS','IS','THE','DESCRIPTION','OF','A',
                        'GEOMETRY','DIGITISATION','DIGITIZATION','ROUTINE'/
*
    k=1; :syntax: Do i=1,Lenocc(MTitle)                  " skip trivial words "
    {  is=k;  If MTitle(i:i)==' '
       {  word=Mtitle(k:i);  k=i+1
          do j=1,Ntriv { If (word=trivial(j)) next :syntax:; };  Break
    }  }
    Tshort=MTitle(is:)
end
 
 
*CMZ :  1.00/00 27/08/95  20.18.55  by  Pavel Nevski
*-- Author :    Pavel Nevski   27/08/95
***************************************************************************
                SUBROUTINE    A G A U T O  (IAUTO)
* Description - Interactive GEANT fails to do it now, temporary fix       *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEND.
     Integer  Iauto
     print *,' igauto was=',igauto,',  set to ',Iauto
     Igauto=Iauto
end
 
*CMZ :          15/06/98  12.24.27  by  Pavel Nevski
*CMZ :  1.30/00 24/03/96  21.59.47  by  Pavel Nevski
*CMZU:  1.00/01 21/01/96  20.18.19  by  Sasha Vanyashin
*CMZ :  1.00/00 24/11/95  00.28.56  by  Pavel Nevski
*-- Author :    Pavel Nevski   20/11/95
***************************************************************************
*                                                                         *
            Subroutine   A G D U M P (CpathI,NUM,Chopt)
*                                                                         *
* Description: Given a path, dump the whole structure below it with DZDOC *
*      NUM   :  If NUM(1) is zero, array of 1s is assumed                 *
*      Chopt : F - write output in a file with the name of the bank(.sgml)*
*            : C - dump values only (to be read by another program)       *
*            : U - dump also undocumented banks, otherwise they are skept *
*            : 1 - skip banks longer then 1000 words                      *
*            : S - SGML format                                            *
*            : H - HGML format                                            *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
  INTEGER    LENOCC,INDEX,IL(15),LK(15),Num(15),Nun(15)/15*1/,
             L,I,J,K/0/,Luu/6/,MOQUEQ/11/,Ierr/0/
  Character  CpathI*(*),Cpath*80,Chopt*(*),Chtop*8,Cbank*4,
             Ctop*4,Bank*8,Cold*8,Chop*4,Cfile*4
  Logical    Opnd
*
  INQUIRE (FILE='detm.rz',opened=opnd)
  If .not.opnd
  {  CALL RZOPEN(61,CHTOP,'detm.rz','UWX',256,Ierr)
     CALL RZFILE(61,CHTOP,' ')
  }
*                  convert to capitals
L=Lenocc(CpathI);  Cpath=CpathI(1:L);  Call CLTOU(CPATH(1:L))
*
If Num(1)>0 { Call ReBANK(Cpath,Num,0,L,J) }
else        { Call ReBANK(Cpath,Nun,0,L,J) }
Check L>0;  J=1;  Cold=' ';  Luu=Lout;
If Index(Chopt,'F')!=0
{  Luu=62;  Call UHTOC(IQ(L-4),4,Cfile,4)
   Open(Luu,File=Cfile//'.sgml',STATUS= 'UNKNOWN')
}
*
Loop
{   If L>0
    {  If LQ(L+1)<=0  { Ctop='NONE' }
       else           { Call UHTOC(IQ(LQ(L+1)-4),4,CTOP,4) }
       Call UHTOC(IQ(L-4),4,CBank,4);   Bank=Cbank//Ctop;
*                                          print bank header
       Chop='PRZ'
       If (Index(Chopt,'H')!=0) Chop='PRZH'
       If (Index(Chopt,'S')!=0) Chop='PRZS'
       If Cold != bank                   " dump new bank header "
       {  IQUEST(MOQUEQ)=1; Call DzDOCO(Luu,Bank,Chop); IERR=IQUEST(MOQUEQ) }
*                                          print the bank itself
       If (Index(Chopt,'C')==0) { Chop=' ' } else { Chop='C' }
       If ((Ierr==0|Index(Chopt,'U')>0) & (Index(Chopt,'1')==0|IQ(L-1)<1000))_
          Call DzDDOC(IrbDiv,L,Bank,Chop,1,IQ(L-1),Luu,'    ',K)
       Lk(j)=L;  IL(j)=0;  Cold=Bank;
*                                          skip content of docu tree
       if (Bank='DOCUDETM' & J>1) IL(j)=999999;
    }
*    now navigate in the structure - first through links, then to next bank
    If IL(j)<IQ(LK(j)-2)  { IL(j)+=1; L=LQ(LK(j)-IL(j));  If (L >0) j+=1; }
    else   " brothers "   { If (j==1) Break; L=LQ(LK(j)); If (L<=0) j-=1; }
}
If Index(Chopt,'F')!=0
{ Close (Luu);  If (Index(Chopt,'H')!=0)
  {  L=Lenocc(CPath);  J=0;  Ctop='NONE'
     do i=1,L-14  { If (CPath(i:i)='/') J=i }
     If (J>0) Ctop=CPath(J+1:J+4)
     Open (Luu,  File=Cfile//'.sgml', STATUS= 'UNKNOWN')
     Call DZE2HT(Luu,Luu+1,3,Ctop)
     close (Luu)
} }
END
 
 
*CMZ :  1.30/00 12/02/96  15.17.30  by  Pavel Nevski
*-- Author :    Sasha Rozanov  06/02/96
**********************************************************************
*                                                                    *
                    Function   A g E X I S T (Ctest)
*                                                                    *
* Description: check if a GEANT volume exist                         *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
  Integer      AgEXIST
  Character*4  Ctest
*
  Call GLOOK  (Ctest,IQ(JVOLUM+1),IQ(JVOLUM-1),AgEXIST)
*
  END
 
 
*CMZ :          13/07/97  23.26.30  by  Pavel Nevski
*CMZ :  1.30/00 05/08/96  11.35.22  by  Pavel Nevski
*-- Author :     Pavel Nevski
******************************************************************************
                 subroutine   A g P M A T E R (a,b)
******************************************************************************
   Implicit  none
   Real      ARGUM,HI,HIJ,a,b,x,y,s0,s1,s2,ax,bx,ay,by,aa,bb
   integer   id,jd,kind,ix,iy,nx,ny,nwt,loc/0/
   character tit*100
*
aa=ARGUM(a);  bb=ARGUM(b)
do Id=3000,4000,1000
{  Do Jd=1,7,2
   {  Call  HKIND (ID+jd,KIND,' ')
      If (Kind==1)  Call HOPERA(ID+jd,'/',ID,ID+2,1.,1.)
      If  Kind==2
      {  Call  Hgive (ID+jd,  tit,nx,ax,bx,ny,ay,by,nwt,loc)
         Call  Hbook1(ID+jd+1,tit,nx,ax,bx,0)
         do ix=1,nx
         {  x=ax+(ix-0.5)*(bx-ax)/nx;    {s0,s1,s2}=0;   s0+=HI(ID,ix)
            do iy=0,ny+1
            { y=ay+(iy-0.5)*(by-ay)/ny;
              check aa<=y&y<=bb; s1+=HIJ(ID+jd,ix,iy);
            }
            if (s0>0) call Hfill (ID+jd+1,x,y,s1/s0)
      }  }
      if (1<=Kind&Kind<=2) call HPLOT(ID+jd+1,' ',0,0)
}  }
*
   end
*CMZ :          29/07/97  16.38.30  by  Pavel Nevski
*CMZ :  1.30/00 10/02/97  15.01.26  by  Unknown
*-- Author :    Alexandre Rozanov 02.04.95
******************************************************************************
*                                                                            *
                      SUBROUTINE   A g S M A T E R
*                                                                            *
*  Description:  store material distribution while processing geant step     *
*                again a temporary solution before something more general    *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
    REAL               ALRADL,ALABSL
    COMMON /AMATERIAL/ ALRADL,ALABSL
*
      REAL      ptot,eta,x0,R,Za,phi,Vmod,AL
      Real      ax,bx,ay,by
      integer   nx,ny,nwt,loc/0/
      character tit*100
      logical   First/.true./
      save      tit,nx,ax,bx,ny,ay,by,nwt,loc,eta,phi
*
*    should be called for geantino run
      if (First) Call Hgive(3000,tit,nx,ax,bx,ny,ay,by,nwt,loc)
      First=.false.
      If (loc>0) Then
         If Nstep==0
         {  ptot = vmod(pvert,3);    phi  = atan2(pvert(2),pvert(1));
            eta  = -10;  If (ptot>0) eta  = -log(tan(acos(pvert(3)/ptot)/2))
            if (ax>=0) eta=abs(eta); ALRADL=0; ALABSL=0;
            call hfill(3000,eta,1,1.); call hfill(4000,phi,1,1.)
            call hfill(5000,eta,phi,1.)
         }
         R  = vmod(Vect,2);     Za = abs(vect(3))
         x0 = step/radl;        AL = step/AbsL
*
         if Ntmult==1 & NMAT!=15
         {  ALRADL+= x0; ALABSL+= AL;
            call hfill(3001,eta,R,x0);   call hfill(3003,eta,R,AL);
            call hfill(4001,phi,R,x0);   call hfill(4003,phi,R,AL)
* slices in z possible - never used until now.
            call hfill(3005,eta,Za,x0);  call hfill(4005,phi,Za,x0)
            call hfill(3007,eta,Za,AL);  call hfill(4007,phi,Za,AL)
* I dont remember what this was useful for - keep it as spare for a while
            call hfill(5001,eta,phi,x0); call hfill(5003,eta,phi,AL);
         }
      endif
 END
 
 
*CMZ :  1.30/00 17/04/97  17.28.45  by  Pavel Nevski
*-- Author :    Pavel Nevski   16/04/96
***************************************************************************
*                                                                         *
      SUBROUTINE   A G C H E C K
*
* description: closing of the geometry sometime is not done properly      *
*              due to users faults - try to fix it if posssible           *
***************************************************************************
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
      Integer      Iflag/0/,JNAME/0/
*
      Iflag=0;   If (JNAME==0) CALL UCTOH('GPAR',JNAME,4,4)
      If   JGPAR<=0 | JGPAR>=NZEBRA    {  Iflag=1  }
      else IF IQ(JGPAR-1)<=0           {  Iflag=2  }
      else If IQ(JGPAR-3)!=IQ(JGPAR-1) {  Iflag=3  }
      else If IQ(JGPAR-4)!=JNAME       {  Iflag=4  }
*
      If Iflag>=1
      {   <W> Iflag,Jgpar;  (' AGCHECK: GPAR error',i3,i9,', doing GGCLOS')
         CALL GGCLOS
      }
     END
 
 
*CMZ :  1.30/00 17/04/97  16.14.18  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
***************************************************************************
*                                                                         *
                Subroutine   A g Z I N I
*                                                                         *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
   Integer NLM/20/
*
   Call MZLINK (IxSTOR,'/SCLINK/',LKSLUG,LKSLUG(NSLINK),LKSLUG)
   CALL MZBOOK (IxCONS, JGPAR, JGPAR, 1,'GPAR', NLM,0,NLM, 2,0)
   CALL MZBOOK (IxCONS, JGPAR2,JGPAR2,1,'GPA2', NLM,0,NLM, 2,0)
*
   END
 
*CMZ :  1.00/00 21/02/95  01.18.39  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/01/95
**********************************************************************
*                                                                    *
                     subroutine   G F D I G 1                        _
         (IUSET,IUDET,NTDIM,NVS, LTRA,NTRA,NBV,KDIGI,Iw,Iacce)
*                                                                    *
*      Returns the next digitisation for the physical volume, spe-   *
*      cified by NVS list with generic volume/set name IUDET/IUSET   *
* INPUT:                                                             *
* IUSET,IUDET - user set/detector identifiers (CHAR*4)               *
* NTDIM       Max. number of associated tracks to return             *
* NVS         array that contains the path to the detector volume    *
* OUTPUT:                                                            *
* LTRA        array that get the list of tracks                      *
*             which have produced this digitalisation                *
* NTRA        total number of contributed tracks                     *
* NBV         the list of volume numbers which identify              *
*             the physical volume                                    *
* KDIGI       array that get the digitalisation elements             *
* ====>  User should take care of NVS,NVB,KDIGI real dimesions !     *
**********************************************************************
Replace[;#?;] With [; IF #1 {" Take next word " K=1; Nk+=1; } ]   ;
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
  CHARACTER*4 IUSET,IUDET;
  Integer   NVS(1),NBV(1),KDIGI(1),LTRA(NTDIM),NTDIM,JBYT,
            Iset,Idet,Js,Jd,Jdi,Jddi,Jdid,ILAST,Nv,Nd,Kd,
            I,Iw,Io,Iv,Id,NWDI,NTRA,K,Nk,Nb,Jv,It,Iacce;
  COMMON    /GFDIGLI/  JS,JD,JDI,JDDI,JDID;
  Save      ISET,IDET,ILAST,NV,ND,IO;
  LOGICAL   First/.TRUE./;
                           * * *
IF First { First=.FALSE.; Call MZLINK(IXSTOR,'GFDIGLI',JS,JS,JDID); }
IF Iw<=0
{  "      Find if selected set and detector exist    "      Check JDIGI>0;
   Call GLOOK(IUSET,IQ(JSET+1),IQ(JSET-1),ISET);            Check Iset>0;
   JS   = LQ(JSET-ISET);                                    Check Js>0;
   JDI  = LQ(JDIGI-ISET);                                   Check JDI>0;
   Call GLOOK(IUDET,IQ(JS + 1),IQ(JS - 1),IDET);            Check Idet>0;
   JDID = LQ(JDI-IDET);                                     Check JDID>0;
   ILAST= IQ(JDI+IDET);                                     Check ILAST>0;
   JD=LQ(JS-IDET);  JDDI=LQ(JD-2);  NV=IQ(JD+2);  ND=IQ(JD+6);
   Iw=1; Io=0;
}
"                 Loop Over remaining digits                         "
NWDI=0;
for I=Iw  to  ILAST  by  NWDI
{  NWDI=IQ(JDID+I);  If (NWDI<=0 | I>=ILAST) Break;
   If (I=Io & Iacce=Jdid+Io) Next;
   NTRA=JBYT(IQ(JDID+I+1),1,16)+1;  Nk=2+NTRA/2; K=1; Nb=0;
   "   Select volume (tracks are not selected)   "
   Do Iv=1,NV
   {  Nb=IQ(JD+2*Iv+10);
      IF Nb>0  { K+Nb>33 ?; Jv=JBYT(IQ(JDID+I+Nk),K,Nb); K+=Nb;}
      ELSE     { K>1     ?; Jv=IQ(JDID+I+Nk);            Nk+=1;}
      IF (0<NVS(Iv)&NVS(Iv)#JV) GOTO :E:;           NBV(iv)=JV;
   }  Nb>0 ?;
   "      Now fetch unpacked digits and track numbers   "
   Do Id=1,ND
   {  Nb=IQ(JDDI+2*Id);
      IF Nb>0  { K+Nb>33 ?; Kd=JBYT(IQ(JDID+I+Nk),K,Nb); K+=Nb;}
      ELSE     { K>1     ?; Kd=IQ(JDID+I+Nk);            Nk+=1;}
                                                  Kdigi(Id)=Kd;
   }
   "             Get track numbers                    "
   Nk=1;  K=17;  Nb=16;
   do It=1,min (NTRA,NTdim)
   {   K+Nb>33 ?;  LTRA(It)=JBYT(IQ(JDID+I+Nk),K,Nb); K+=Nb;}
   {Iw,Io}=I;      Iacce=JDID+I;  Return;      :E:
}   Iw=0;
END;
 
 
*CMZ :  1.30/00 03/05/97  16.11.50  by  Pavel Nevski
*-- Author :    Pavel Nevski  01/02/97
****************************************************************************
*                                                                          *
                subroutine   A g S K I N G
*                                                                          *
* Description: Save a stack track in KINE bank, before it produces a hit   *
* Too late to get anything from stack, all should be extracted in GLTRAC   *
*                                                                          *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCSTAK.
      INTEGER  NJTMAX,NJTMIN,NTSTKP,NTSTKS,NDBOOK,NDPUSH,NJFREE,NJGARB,
     +         NJINVO,LINSAV,LMXSAV,NWSTAK,NWINT,NWREAL,NWTRAC
      INTEGER ISTORD
      PARAMETER (NWSTAK=12,NWINT=11,NWREAL=12,NWTRAC=NWINT+NWREAL+5)
      COMMON /GCSTAK/ NJTMAX, NJTMIN, NTSTKP, NTSTKS, NDBOOK, NDPUSH,
     +                NJFREE, NJGARB, NJINVO, LINSAV(15), LMXSAV(15)
      EQUIVALENCE (ISTORD,NJTMIN)
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCTMED.
      COMMON/GCTMED/NUMED,NATMED(5),ISVOL,IFIELD,FIELDM,TMAXFD,STEMAX
     +      ,DEEMAX,EPSIL,STMIN,CFIELD,PREC,IUPD,ISTPAR,NUMOLD
      COMMON/GCTLIT/THRIND,PMIN,DP,DNDL,JMIN,ITCKOV,IMCKOV,NPCKOV
C
      INTEGER       NUMED,NATMED,ISVOL,IFIELD,IUPD,ISTPAR,NUMOLD
      REAL          FIELDM,TMAXFD,STEMAX,DEEMAX,EPSIL,STMIN,CFIELD,PREC
      INTEGER       JMIN,NPCKOV,IMCKOV,ITCKOV
      REAL          THRIND,PMIN,DP,DNDL
C
*KEND.
Integer  i,L,Ivn,Itn,IPRIN,MECATO,ITRO
Real     TOFO,Ubuf
COMMON   /GCKINE_CONT/ ITRO,TOFO,MECATO
*
Check Istak>0 & Isvol=1; Iprin=Idebug
 
* first hit by this particle, save it
   Do IVN=NVERTX,1,-1
   { L=LQ(JVERTX-IVN);     IF "generator vertices" (Q(5+L)<=0) Break;
     check Q(4+L)==TOFO    & Q(5+L)==ITRA    & Q(6+L)==Mecato
     check Q(1+L)==Vert(1) & Q(2+L)==Vert(2) & Q(3+L)==Vert(3)
     go to :track:
   }
   Call GsVERT (Vert,ITRA,0,Ubuf,0,IVN)
   If IVN<=0
   { <w> ITRA,MECATO; (' AgGSKING cannot set Vertex for ',2i8/,
         ' ****** event simulation abandoned ******');  IEOTRI=1; RETURN
   }
   * Correct TOF (GsVERT takes it from TOFG of /GCTRAK/), save History
   L=LQ(JVERTX-IVN);  Q(4+L)=TOFO;  Q(6+L)=Mecato
*
   :track: Call GsKINE (Pvert, Ipart, IVN, Ubuf, 0, ITN)
   prin4 ITRA,Ivert,(vert(i),i=1,3),Itn,Ivn,Mecato
   (' AgSKING:  T/V=',2i4,'  v=',3f9.3,'  t/v=',2i4,' Mecato=',i8)
   * Ivert is set in GLTRAC only for KINE entries, not for any Jstak
   * Ivert should still remains primary numbering and cant be used
   Istak=0;  ITRA=Itn;  " Bad: Ivert=Ivn "
 
end
 
 
*CMZ :  1.30/00 05/05/97  01.05.56  by  Pavel Nevski
*-- Author :    Pavel Nevski   02/04/97
****************************************************************************
       Subroutine    A g S S E C O N D
*                                                                          *
* Description:  default solution is to put secondaries onto JSTAK only     *
*   NA49:  descendents of tracks from stack go into stack                  *
*          in DENSE MEDIA:  write all vertices of showers in NEW media,    *
*          ie check medium at point origin of parent track and             *
*          if the same as current medium, do not write out vertex          *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCTMED.
      COMMON/GCTMED/NUMED,NATMED(5),ISVOL,IFIELD,FIELDM,TMAXFD,STEMAX
     +      ,DEEMAX,EPSIL,STMIN,CFIELD,PREC,IUPD,ISTPAR,NUMOLD
      COMMON/GCTLIT/THRIND,PMIN,DP,DNDL,JMIN,ITCKOV,IMCKOV,NPCKOV
C
      INTEGER       NUMED,NATMED,ISVOL,IFIELD,IUPD,ISTPAR,NUMOLD
      REAL          FIELDM,TMAXFD,STEMAX,DEEMAX,EPSIL,STMIN,CFIELD,PREC
      INTEGER       JMIN,NPCKOV,IMCKOV,ITCKOV
      REAL          THRIND,PMIN,DP,DNDL
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
       CHARACTER    Cmedium*20
       EQUIVALENCE (Cmedium,NATMED)
       Integer      LgKINE, i, j, IV, IB, IT
*                   Med_Vertex, Med_Current
*
       If ( flag_secondaries  .lt.  2 )    Return
       If ( Ngkine.le.0.or.Istak.gt.0 )    Return
       IV = Q(6+LgKINE(J,ITRA))            ! production vertex
       IB = Q(5+LQ(JVERTX-IV))             ! beam   - geant parent
       IT = Q(6+LQ(JVERTX-IV))             ! target - medium & process
*      If (IB!=0)                          Return
       If ( Cmedium(6:10) .ne. 'DENSE')    Return
*      call GTMEDI( vert, Med_Vertex  )
*      call GTMEDI( vect, Med_Current )
*      If ( Med_Vertex.eq.Med_Current )    Return
       If (abs(IT)/100==LVOLUM(NLEVEL))    Return
*
***      put secondaries into both JSTAK and JVERTX/JKINE structures
*
       do I=1,NGKINE
          IFLGK(I) = 1
       enddo
 
       END
 
*CMZ :          16/07/97  22.01.24  by  Pavel Nevski
*CMZ :  1.30/00 03/05/97  16.15.42  by  Pavel Nevski
*-- Author :    Pavel Nevski
************************************************************************
*                                                                      *
                SUBROUTINE   A g U S E C O N D
*                                                                      *
* Description :                                                        *
*     Set users conditions for products saving into the KINE bank      *
*     It gets arguments from DETP  TRAC  datacard:                     *
*          Mechanism, Rmax, Zmax, Eparent, Esecondary                  *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
*
      INTEGER      AGPFLAG,N,I,J,IPRIN/0/,NPAR/0/,ISEL/0/,IdEvt0/-1/,IPAR(21)
      LOGICAL      FIRST/.true./
      Real         VMOD,PAR(21)
      Save         PAR
      Character*4  Cproc
      Equivalence  (PAR,IPAR)
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      IF (IdEvt0 != IdEvt)  THEN
          Idevt0  = Idevt
          IPRIN=AGPFLAG('TRAC','SIMU')
          CALL ASLGETBA('TRAC','DETP',21,NPAR,PAR)
          If (Iprin>=Idevt & Idebug>0)  <w> (PAR(i),i=2,NPAR)
             (' SECONDARY SAVING : process   Rmax   Zmax    Eparent    Eprod',
                                   /(20x,a4,f10.1,f7.1,2f10.3))
          NPAR=((NPAR-1)/5)*5;  Isel=0
          Do N=1,NPAR,5
             Call UHTOC(PAR(N+1),4,CPROC,4)
             If (Cproc=='*' | Cproc=='ALL') Isel=1
          enddo
      ENDIF
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       CHECK ISTAK==0
* Check Mechanism, R,Z,E0 and Ei
:Mech: DO N=1,NPAR,5
          Check GETOT>=PAR(N+4)
          Check ABS(VECT(3))<PAR(N+3)
          Check VMOD(VECT,2)<PAR(N+2)
          DO I=1,NGKINE
             IF (GKIN(4,I)<PAR(N+5)) Next :mech:
          enddo
 
          DO I=max(1,NMEC-1),NMEC
             Check (NAMEC(LMEC(I))==IPAR(N+1) | Isel>0)
             Prin5   NGKINE,(VECT(J),J=1,3),GETOT,(NAMEC(LMEC(J)),J=1,NMEC)
             (' AgUSECOND: SAVED',I3,' products at',4F10.3,' of',20(1X,A4))
             DO J = 1,NGKINE
                IFLGK(J) = 1
             ENDDO
             break :Mech:
          enddo
       enddo
*
      END
 
 
*CMZ :  1.30/00 17/11/96  21.32.49  by  Pavel Nevski
*-- Author : Pavel Nevski
*************************************************************************
*                                                                       *
             Function     A g F H I T a (Cset,Cdet)
*                                                                       *
*  Description: this routine does not set DIGI - this allows add digits *
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEND.
 Character*(*)  Cdet,Cset
 Integer        AgFHITa,AgFDIG0,AgPFLAG,I,J,L,ok/0/
*
   AgFHITa =-1;  Cs=Cset(1:3)//'H';  Cd=Cdet
   IPRIN = AgPFLAG (Cset,'DIGI');    Check Iprin>=0
   If (IPRIN>=5) CALL AGPDIGI (Cs,Cdet)
   AgfHITa = AgFDIG0 (Cs,Cdet)
*
****** if (AgFHIT0==ok)   I = AgSDIG0 (Cset(1:3)//'D',Cdet) **********
   If Iprin>=15
   {  <w>; (' *** AGFHITa buffer  ***');  j=1; while Ibuf(j)>0
      {  L=IBUF(j); if (L<=0) Break; <w> j,L,(Ibuf(j+i),i=1,L);
         (' adr=',i6,' L=',i4,2x,20i5/(20x,20i5));      j+=L+1;
   }  }
   END
 
 
*CMZ :          02/07/98  00.04.30  by  Pavel Nevski
*-- Author :    Pavel Nevski   25/11/97
***************************************************************************
*                                                                         *
                subroutine  A G K E E P S (Request,Cdest)
*                                                                         *
* Description:                                                            *
* produce include files and update the documentation database             *
*     Request is a REBANK path, default root is DETM                      *
*     Cdest   is def, idl or memory (dui etc)                             *
*     IWr is generated according to request:                              *
*     0- global include file, 1 - subsystem files, 2 - separate structs   *
*     Kw=0  - no prefix in keep name, not used                            *
* Attention: Current links are equivalenced to Ldoc/Ldete for protection  *
***************************************************************************
+include,TYPING,GCBANK,SCLINK,GCUNIT,GCFLAG,AGCDOCL.
     integer     Iprin,i,i1,i2,il,id,ic,jl,L,Iwr,Kw/1/,Lu,Idl,Iswap/0/,Key(2)
     Integer     AgPFLAG,LENOCC,INDEX,TDM_MAP_TABLE
     Character*8 Sname, Bname, Ckey
     Character*4 Csys, Cban
     Character   Request*(*),Cdest*(*), Table*10
     Logical     opnd
     character      ccc*12000
     common /agcstaftab/ ccc
 
     INQUIRE(FILE='detm.rz',OPENED=opnd)
     if (.not.opnd) Call Agsbegm('DOCUM',Iprin)
     Iprin=AgPFLAG('DOCU','RECO')
 
     Idl = 2
     if (Index(Cdest,'idl')>0) Idl=1
     if (Index(Cdest,'def')>0) Idl=0
 
*  request a la UNIX: sys/bank.
*  single name (without /) is equivalent to name/
     Iwr = 0
     i2=lenocc(request);    i1=index(request,'/');  if (i1<=0) i1=i2+1
     Csys='*'; if (i1>2)    Csys=request(1:i1-1);   if (i2>0)  Iwr=1
     Cban='*'; if (i1<i2) { Cban=request(i1+1:i2);             Iwr=2 }
     prin3 csys,cban,i1,i2,iwr,idl;(' in agkeep csys=',a,' cban=',a,' iwr=',4i2)
 
     i1=Lenocc(Csys);       Call CUTOL(Csys);
     i2=Lenocc(Cban);       Call CUTOL(Cban);
*
     If (LdArea(1)=0) call MZLINT(IxCONS,'AGCDOCL',LDarea,L1Doc,Lpar)
     Call AsbDETE('DOCU',Id); Check LKDETM>0 & Id>0;
     L=LQ(LQ(LKDETM-Id)-1);   Check L>0;
*
*    top level documantation bank should be 'NONEDETM', but NONE
*    may be swapped on some machines because of big/little endian
*
     CALL UHTOC(IQ(L-5),4,Sname,8); Iswap=-1;
     if (Sname(5:8)=='DETM')
     { L1doc=L
       if     Sname(1:4)='NONE' {Iswap=0}
       elseif Sname(1:4)='ENON' {Iswap=1}
       else   { prin0 Sname; (' AgKEEPS warning : IDN coding wrong ',a)}
     }
     if (Iswap==1) call agswap(Sname)
     prin4 sname,L1Doc;  (' ==> got DocName=',a,' L1Doc=',i10);  Check L1Doc>0;
 
     Lu = 0;  Kw = Iswap
     call agdprina(Iprin,Lu,L1doc,0,Iwr,Kw,Idl)
 
     do il=1,IQ(L1doc-2)
        Ldoc=LQ(L1doc-il); check Ldoc>0
        CALL UHTOC(IQ(Ldoc-5),4,Sname,8)
        if (Iswap==1) call agswap(Sname)
        Call CUTOL(Sname)
        Check csys='*' | Sname(5:4+i1)==csys(1:i1)
 
        call agdprina(Iprin,Lu,Ldoc,1,Iwr,Kw,Idl)
 
        Ckey=Sname(5:8)//Sname(1:4); Call UCTOH(Ckey,Key,4,8)
        CALL aRZOUT(IXCONS,Ldoc,CKey,IC,'SN')
 
        do jl=1,IQ(Ldoc-2)
           Ldete=LQ(Ldoc-jl); check Ldete>0; ccc=' '
           CALL UHTOC(IQ(Ldete-5),4,Bname,8)
           if (Iswap==1) call agswap(Bname)
           Call CUTOL(Bname)
           Check cban='*' | Bname(5:4+i2)==cban(1:i2)
           call agdprina(Iprin,Lu,Ldete,2,Iwr,Kw,Idl)
 
           Table=Sname(5:8)//'_'//Bname(5:8); Call CUTOL(Table)
           if (idl==2) i=TDM_MAP_TABLE(%L(Cdest),%L(Table),%L(ccc),0,0)
 
           Ckey=Bname(5:8)//Bname(1:4); Call UCTOH(Ckey,Key,4,8)
           CALL aRZOUT(IXCONS,Ldete,CKey,IC,'SN')
 
        enddo
     enddo
     If (Lu>6) close (Lu)
     if (.not.opnd) Call Agsendm
     end
 
 
*************************************************************************
*                                                                       *
              subroutine agdprina(Iprin,Lu,L,Lev,Iwr,Kw,Idl)
*                                                                       *
* Description: Produce a copiler readable include files for structures  *
* Decoding part is tough, for format details see 2.16 MZFORM, page 44:  *
* a Bank consists of 3 types of blocks (P=1-3 -> tit)                   *
* each of blocks contains sectors (crec<=ask(1-9))                      *
* A useful dd sector contains type.variable + comments                  *
* Routine produce or a def file, or an idl file, or struct in memory    *
*************************************************************************
+include,TYPING,GCBANK,SCLINK,GCUNIT,AGCDOCL,QUEST.
   Integer      INDEX,LENOCC,NwDESC,Nwhead,NwGEN,Nwlink,Nwdata,Idl,lu,nc,MM
   Integer      Lev,Iwr,Kw,Iprin,i,j,k,l,m,n,is,nd,Nw,iw,iv,i1,j1,P,nn(3),x
   Integer      mask(9)/1,1024,16384,8192,9216,10240,15361,19456,17410/
   Character*2  ask (9)/'ba','au','ve','nd','nl','ns','up','io','dd'/
   character*1  Let,T,Sec(0:8)/'*','B','I','F','D','H','*','S','*'/
   character*6  tit (3)/'header','links','data'/
   character*80 Text,texto,Format,Header,Author,Create
   character*8  var,varo,dname,cn,type,typo
   character    crec*2,kname*16,blan*12/' '/
   character*4  Upper,Bname,Csys/' '/
   Equivalence  (text,var),(texto,varo)
 
   character           ccc*24
   common /agcstaftab/ ccc(500)
 
   nc=0; check L>0;
   prin3 (IQ(L-i),i=1,5);(' ***** doc bank =',3i10,2x,2a5,' *****')
   call UHTOC(IQ(L-5),4,dname,8)
   if (kw==1) call agswap(dname); prin5 dname;  (' dname  = ',a)
   call UHTOC(IQ(L+1),4,bname,4); prin5 bname;  (' bname  = ',a)
   NwDesc = IQ(L+2);              prin5 NwDesc; (' Nwdesc = ',i4)
   NwHead = IQ(L+3);              prin5 Nwhead; (' Nwhead = ',i4)
   NwGen  = IQ(L+11);             prin5 NwGen;  (' Nwgen  = ',i4)
   NwLink = IQ(L+12);             prin5 NwLink; (' Nwlink = ',i4)
   NwData = IQ(L+15);             prin5 NwData; (' Nwdata = ',i4)
   i=Nwhead+1;  Call Vzero(NN,3); P=1; Format='-F'; MM=0;
 
   while i<=Nwdesc+1
   {  if i>=Nwhead+Nwgen+Nwlink+1 {P=3} else if i>=Nwhead+Nwgen+1 {P=2}
      Let='H'; Text=' '; if i<NwDesc
      {  i1=i; Is=IQ(L+i1); Nw=is/16; i=i+Nw;
         Let=Sec(min(mod(Is,16),8));
      }  i=i+1;
 
      If let=='I' & Nw==3
      {  iw=IQ(L+i1+1);  Iv=IQ(L+i1+2);
         crec='un';   do k=1,9 { If (iw==mask(k)) crec=ask(k); }
         if (crec(1:1)=='n') { prin5 crec,iv; (' sector ',a4,i5);}
      }
      else If let='H' & i<=NwDesc+1
      {  j1=1; if (crec=='ba') j1=2;
         Call UHTOC(IQ(L+i1+j1),4,text,4*(Nw-j1+1));
         If  NN(P)==0  { Nd=0; Texto=' '; Prin4 tit(p); (' ---  ',a,'  ---') }
         if (P==3 & nn(p)>=mm)  call agreforma(format,mm,type,idl)
         NN(P)+=1;  Prin6 crec,p,NN(p),Nd,type,text(1:Lenocc(text));
         (' sector ',A4,':  NN(',i1,')=',i4,'  ND=',i3,' t=',a,' : ',a)
      }
      else  { prin6 i,let,Nw; (' unknown sector at ',i6,2x,a1,i8); crec='dd';}
 
      If (crec=='ba' & Let='H')  Header = text
      If (crec=='au' & Let='H')  Author = text
      If (crec=='ve' & Let='H')  Create = text
      If (crec=='up' & Let='H')  Upper  = text
      If (crec=='io' & Let='H')  Format = text
      check P==3 & Let='H' & crec='dd'
*
* ----------------  unpacking done, now output stuff --------------
*
      If NN(P)==1
      {  prin4 lev,bname; ('===>  starting lev,bname=',i3,2x,a,' <===');
*         if (Lev<=1) Csys='sys'
         kname=%L(csys)//'_'//%L(bname)
         if (Lev<=1) kname=%L(bname)//'sys'
         if (Idl==0) kname=%L(kname)//'.def'
         if (Idl>0 ) kname=%L(kname)//'.idl'
         call CUTOL (kname); J=index(kname,'.')
         if (Lev==1) Csys=bname
 
         if Lev==Iwr
         {
            If (Lu>6) CLose(lu);  Lu=1 " pseudo-output - in memory only"
            if (idl<=1)
            { lu=62;  prin2 kname; (' AgDocPrin: open file ',a)
              Open (Lu, file=%L(kname), STATUS= 'UNKNOWN')
         }  }
 
         if (Lu>0 & Idl==0)
         { if (Lev=0) output kname(:j),%L(create)
              ('+PATCH,',a/'*Created: ',a/,
               '*This file is automatically generated by AGI'/,
               '*--------- DO NOT EDIT THIS FILE -----------'/'*')
           if (Lev=1) output kname(:j),%L(header),%L(author),%L(create)
              ('+DECK,',a,' describes the ',a/'*Author : ',a/'*Created: ',a/'*')
           if (Lev=2) output kname(:j),%L(header),%L(author),%L(create),
                                                                  bname,header
              ('+KEEP,',a,' - ',a/'*Author : ',a/'*Created: ',a/'*'/,
               '  structure  ',A4,'    { " ',a42, ' " _ ')
         }
         if (Lu>0 & Idl==1)
         {  if (Lev==Iwr) output %L(kname),%L(header),%L(author),%L(create)
            ('/* File ',a,/'** '/'** Description: ',a/,
             '** Author     : ',a/'** Created    : ',a/,
             '** This file is automatically generated by AGI'/,
             '** --------- DO NOT EDIT THIS FILE -----------'/'*/')
            if (Lev==2) output kname(:j-1);  ('  struct  ',a,'   { ')
         }
         if (Lu>0 & Idl==2 & Lev==2)
         {  nc+=1; CCC(nc)=' struct '//kname(:j-1)//' { '; }
      }
*
      nd+=1; check Lev==2 & var!=varo & lu>0
*
      If varo!='  '
      {  if (varo=='- ') varo='system'
*        fit rigid stic format - no extra spaces allowed
         call CUTOL(varo);     N=Lenocc(varo)
         if (idl>0 & typo=='char') ND=4*ND
         write(CN,'(i6)') ND;  M=Lenocc(CN)
         do K=1,M { if (CN(K:K)!=' ') Break; }
 
         if Idl==0
         {  T=','; if (text==' ') T='}'
            " hash in comments creates problems for AGI parser "
             do x=9,80  { if (texto(x:x)=='#') texto(x:x)='N' }
            if (ND==1) output typo,%L(varo),blan(N:),texto(9:),T
                    (4x,a4,1x,2a,' " ',a42,' " ',a)
            if (ND >1) output typo,%L(varo),CN(K:M),blan(M-K+N+3:),texto(9:),T
                    (4x,a4,1x,a,'(',a,')',a,' " ',a42,' " ',a)
            if (text==' ') output; ('*');
         }
         If Idl==1
         {  if (ND==1) output typo,%L(varo),blan(N:),texto(9:)
                    (4x,a5,1x,a,       ';',a,'/* ',a42,' */')
            if (ND >1) output typo,%L(varo),CN(K:M),blan(M-K+N+3:),texto(9:)
                    (4x,a5,1x,a,'[',a,'];',a,'/* ',a42,' */')
            if (text==' ') output; ('};');
         }
         If Idl==2
         {  NC+=1;
            if (ND==1) CCC(NC)='  '//typo//%L(varo)//'; '
            if (ND >1) CCC(NC)='  '//typo//%L(varo)//'['//CN(K:M)//']; '
            if (text==' ')  { NC+=1; CCC(NC)='}' }
         }
      }
      nd=0; Texto=Text; typo=type
   }
  end
 
 
****************************************************************************
  subroutine  agreforma (format,num,type,idl)
*                                                                          *
* Description: decode ZEBRA 'format' descriptor into a sequence of 'type's *
*              for format details see: 2.16 MZFORM, page 44                *
*              - num is the number of items already taken, should be saved *
*              - idl is an agi/c switch                                    *
****************************************************************************
 
  character   format*(*),type*8,List*14/'0123456789-IFH'/
  integer     Lenocc,idl,L,i/0/,k,n,num,big/9999999/
 
     L=Lenocc(format);  if (num==0) i=0;  N=0;
     Do i=i+1,L
     { k=index(list,format(i:i))-1;  check k>=0
       if  k<=9  "digit"  { N=N*10+k; Next; }
       if  k=10  "tail"   { N=big;    Next; }
       num=num+max(1,N);  Break;
     }
     if (idl==0) { type ='real';  if (format(i:i)=='I') type='int';  }
     else        { type ='float'; if (format(i:i)=='I') type='long'; }
     if (format(i:i)=='H') type='char'
     end
 
 
****************************************************************************
   subroutine  agswap(cname)
   character   c*1,cname*(*)
   c=cname(1:1); cname(1:1)=cname(4:4); cname(4:4)=c
   c=cname(2:2); cname(2:2)=cname(3:3); cname(3:3)=c
   end
****************************************************************************
 
 
*CMZ :          31/03/98  19.05.30  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/03/98
************************************************************************
*                                                                      *
                subroutine    A g P H Y S I
*                                                                      *
*  Description: make Cross-section calculations re-executable          *
*  Modified algorithm from GXPHYS. CKOV banks are not dropped          *
*                                                                      *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
      INTEGER IPAIR,ICOMP,IPHOT,IPFIS,IDRAY,IANNI,IBREM,IHADR,IMUNU
     +       ,IDCAY,ILOSS,IMULS,IRAYL,ILABS,ISYNC,ISTRA
      REAL    SPAIR,SLPAIR,ZINTPA,STEPPA,SCOMP,SLCOMP,ZINTCO,STEPCO
     +       ,SPHOT,SLPHOT,ZINTPH,STEPPH,SPFIS,SLPFIS,ZINTPF,STEPPF
     +       ,SDRAY,SLDRAY,ZINTDR,STEPDR,SANNI,SLANNI,ZINTAN,STEPAN
     +       ,SBREM,SLBREM,ZINTBR,STEPBR,SHADR,SLHADR,ZINTHA,STEPHA
     +       ,SMUNU,SLMUNU,ZINTMU,STEPMU,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +       ,SLOSS,SOLOSS,STLOSS,DPHYS2,SMULS,SOMULS,STMULS,DPHYS3
     +       ,SRAYL,SLRAYL,ZINTRA,STEPRA,SLABS,SLLABS,ZINTLA,STEPLA
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
*    provide index access to geant mechanism
     Integer       MECA(5,13)
     EQUIVALENCE  (MECA,IPAIR)
 
     Integer i,j,jtm,jma,Ival
 
     IF JTMED>0               " Extracted From GXPHYS "
     {  DO I=1,IQ(JTMED-2)
        {  JTM=LQ(JTMED-I);  Check JTM>0
           IF IQ(JTM-2)==0 { CALL MZPUSH(IXCONS,JTM,10,0,'I');     Next;}
           * drop only MUEL and MUMU banks
           DO J=1,2 { IF(LQ(JTM-J)>0) CALL MZDROP(IXCONS,LQ(JTM-J),' ');}
        }
        " copy tracking cuts from standard to special media "
        CALL UCOPY(CUTGAM,Q(JTMED+1),10)
        " copy mecanism flags (pair..rayl) to special media "
        DO I=1,13 { Q(JTMED+10+I)=MECA(1,I) }
     }
     IF JMATE>0               " Extracted From GXPHYS "
     {  DO I=1,IQ(JMATE-2)
        {  JMA=LQ(JMATE-I); Check JMA>0
           DO J=1,IQ(JMA-2)
           {  IF (J==4 | J==5) Break " strange !"
              IF (LQ(JMA-J)>0) CALL MZDROP(IXCONS,LQ(JMA-J),'L')
     }  }  }
     Ival=Lout;  If (Idebug==0) Lout=99;
     Call GPHYSI
     Lout=Ival
     end
 
 
*CMZ :          01/07/98  14.53.37  by  Pavel Nevski
*-- Author :    Pavel Nevski   25/11/97
***************************************************************************
*                                                                         *
            Subroutine   A G S T R U T (Source,Destin)
*                                                                         *
* Description: Given a path, dump the whole structure below into STAF     *
*     request a la UNIX: sys/bank - very combersome for the moment :      *
*     'standard' path form is [/DETM/]sys..., * at the end means 'all'    *
*     RECB etc alternative form is /RECB/....bank@sys                     *
*          meaning 'take documentation from sys'                          *
*     Only existing banks are dumped, alternative is commented out now    *
* Attention: Current link is equivalenced to Lpar for protection          *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
  INTEGER       LENOCC,TDM_MAP_TABLE,Iprin,Nun(15),LK(15),IL(15),Ist(15),
                I,J,L,K,M,N,Ia,Lc,Lp,Mj
  Character     Cpath*80,Cdest*80,Csys*4,Table*10,Cbank*4
  Character*(*) Source,Destin
  EQUIVALENCE   (L,Lpar)
*
* reduce to the standard path and dest:
  Iprin=Idebug;         Cpath=Source;
  if (Cpath(1:1)!='/')
  { If Lenocc(Source)==4 { Cpath='/DETM/'//Source(1:4)//'/*'; }
    else                 { Cpath='/DETM/'//Source;            }
  }
  Call CLTOU(Cpath);
 
  Cdest='/dui/Run'; if (Cpath(2:5)!='DETM') Cdest='/dui/Event';
  if (Lenocc(Destin)>0) Cdest=Destin;
 
* Csys - prefix for AgKeeps
  Lc=Lenocc(Cpath); n=Index(Cpath,'@');  Csys=' ';
  if (Cpath(1:6)=='/DETM/' & Lc>=10) Csys=Cpath(7:Lc)
  if (0<n&n<Lc)  { Csys=Cpath(n+1:Lc); Lc=n-1 }
  Mj=2; if (Lenocc(Csys)>0) { Mj=0; "Call Agkeeps(Csys,Cdest);" }
*
* Rebank path does not accept / or /_* at the end, truncate:
  m=Index(Cpath(1:Lc),'*'); Lp=Lc;
  if (m>0) Lp=min(Lp,m-1);  if (Cpath(Lp:Lp)='/') { Lp-=1; m=-1 }
  do i=1,Lp/5 { Nun(i)=1 }; Nun(Lp/5)=0;
 
:A: Call ReBANK(Cpath(:Lp),Nun,0,L,Ia)
    Call UHTOC(IQ(L-4),4,CBank,4)
 
  prin2  %L(Csys),Cpath(:lp),Cbank,lc,n,m,mj,lp
  (' AGSTRUT decoded Csys,Cpath,Cbank=',3(1x,a),' lc,n,m,mj,lp=',6i8)
  if L<=0 { <w> %L(Cpath); (' AGSTRU: Data source ',a,' not found '); Return; }
*
J=1; Loop                                  " over existing banks only "
{  If L>0
   {  Call UHTOC(IQ(L-4),4,CBank,4);
      if     J==MJ      { Csys=Cbank; "Call Agkeeps(Csys,Cdest);" }
      elseif J> MJ & Csys!='DOCU'
      { Table=Csys(1:4)//'_'//Cbank;  Call CUTOL(Table);
        Call AGKEEPs(%L(Csys)//'/'//Cbank,%L(Cdest))
        K=1; if (IQ(L-5)<0) K=-IQ(L-5)
        i=TDM_MAP_TABLE(%L(Cdest),%L(Table),Char(0),K,IQ(L+1))
        prin2 %L(Cdest),%L(Table),i,k,(Q(L+i),i=1,3)
              (' TDM_MAPing_TABLE:',2(1x,a),2i5,2x,3F8.1)
        " specific bank requested " if (m==0 & Mj==0) Break;
      } Lk(j)=L;  Ist(j)=IQ(L);  IL(j)=0;
   }
*    now navigate in the structure - first through links, then to next bank
   if IQ(LK(j))!=Ist(j)  { prin2;(' AGSTRUT problem, links are lost'); Goto:A:}
   If IL(j)<IQ(LK(j)-2)  { IL(j)+=1; L=LQ(LK(j)-IL(j));  If (L >0) j+=1; }
   else   " brothers "   { If (j==1) Break; L=LQ(LK(j)); If (L<=0) j-=1; }
}
END
 
*CMZ :          29/06/98  12.56.45  by  Pavel Nevski
*-- Author :    Pavel Nevski   25/03/98
**********************************************************************
                subroutine   a x p a r t i c l e
**********************************************************************
*KEEP,AGECOM.
      CHARACTER*20 AG_MODULE,  AG_TITLE,  AG_EXNAME,   AG_PARLIST,
     +             AG_MATERIAL,AG_MIXTURE,AG_COMPONENT,AG_MEDIUM,
     +             AG_CHDIR
      CHARACTER*4  AG_VOLUME,AG_MOTHER,AG_SHAPE,AG_CNICK,AG_KONLY,
     +             AG_OPTION,AG_ORT,AG_MARK
      INTEGER      AG_BEGCOM,AG_IVOLUME,AG_IMOTHER,AG_IGNUM,AG_ISHAPE,
     +             AG_IMED,AG_IMAT,AG_IFIELD,AG_IDTYPE,AG_NLMAT,AG_ORTI,
     +             AG_IERROR,AG_NWBUF,AG_NPAR,AG_ISTATUS,AG_IROT,AG_JDU,
     +             AG_NBITS,AG_ISET,AG_IDET,AG_ISVOL, AG_ATTRIBUTE(6),
     +             AG_WORK, AG_SEEN,AG_LSTY,AG_LWID,AG_COLO,AG_FILL,
     +             AG_LEVEL,AG_NDIV,AG_IAXIS,AG_NDVMAX,AG_NPDV,AG_NCOPY,
     +             AG_IPRIN,AG_RESET1,AG_RESET2,AG_BEGSCR,AG_ENDSCR,
     +             AG_IRESER,AG_LSTACK,AG_NWUHIT,AG_NWUVOL,AG_MAGIC,
     +             AG_LDETU,AG_NPDIV,AG_NZ,AG_IGEOM,AG_IDEBU,AG_IGRAP,
     +             AG_IHIST,AG_IMFLD,AG_SERIAL,AG_STANDALONE,AG_ISIMU,
     +             AG_CODE,AG_TRKTYP,AG_ECODE,AG_MODE,AG_PDG,
     +             AG_ENDSAVE,IPRIN
      REAL         AG_FIELDM,AG_TMAXFD,AG_STEMAX,AG_DEEMAX,AG_EPSIL,
     +             AG_STMIN,AG_DENS,AG_RADL,AG_ABSL,AG_THETAX,AG_THETAY,
     +             AG_THETAZ,AG_ALFAX,AG_ALFAY,AG_ALFAZ,AG_PHIX,AG_PHIY,
     +             AG_ALPHAX,AG_ALPHAY,AG_ALPHAZ, AG_PHIZ, AG_TWIST,
     +             AG_DX, AG_DX1, AG_DX2, AG_DY, AG_DY1,AG_DY2,
     +             AG_THET, AG_THE1, AG_THE2, AG_PHI, AG_PHI1, AG_PHI2,
     +             AG_ALPH, AG_ALP1, AG_ALP2, AG_RMIN, AG_RMAX, AG_RMN,
     +             AG_RMX, AG_ZI, AG_RMN1, AG_RMN2, AG_RMX1, AG_RMX2,
     +             AG_H1, AG_H2, AG_BL1, AG_BL2, AG_TL1, AG_TL2,AG_DPHI,
     +             AG_DZ, AG_TWIS, AG_X, AG_Y, AG_Z, AG_A, AG_ZA, AG_W,
     +             AG_STEP, AG_C0, AG_PAR, AG_AA,AG_ZZ,AG_WW,AG_TYPE,
     +             AG_STACK,AG_UBUF,AG_XHMAX,AG_YHMAX,AG_ZHMAX,
     +             AG_RHMAX,AG_FHMAX,AG_FHMIN,AG_BIN,AG_DMAXMS,
     +             AG_LX, AG_LY, AG_LZ, AG_HX, AG_HY, AG_HZ, AG_P1,
     +             AG_P2, AG_CHARGE, AG_MASS, AG_TLIFE, AG_BRATIO
      PARAMETER   (AG_LSTACK=130, AG_NWUHIT=10, AG_NWUVOL=3,
     +             AG_MAGIC=-696969, AG_LDETU=250)
      COMMON/AGCGLOB/AG_MODULE, AG_CHDIR,   AG_LEVEL,   AG_IDTYPE,
     +              AG_IERROR,  AG_STANDALONE,          IPRIN,
     +              AG_IPRIN,   AG_IGEOM,   AG_IDEBU,   AG_IGRAP,
     +              AG_IHIST,   AG_IMFLD,   AG_ISIMU
C Inherited variables saved during internal calls
      COMMON/AGCPARA/AG_BEGCOM, AG_IVOLUME, AG_IMOTHER, AG_IGNUM,
     +              AG_ISHAPE,  AG_IMED,    AG_IMAT,    AG_IFIELD,
     +              AG_FIELDM,  AG_TMAXFD,  AG_STEMAX,  AG_DEEMAX,
     +              AG_EPSIL,   AG_STMIN,   AG_DENS,    AG_RADL,
     +              AG_ABSL,    AG_DX,      AG_DX1,     AG_DX2,
     +              AG_DY,      AG_DY1,     AG_DY2,
     +              AG_RMN1,    AG_RMN2,    AG_RMX1,    AG_RMX2,
     +              AG_THET,    AG_THE1,    AG_THE2,
     +              AG_PHI,     AG_PHI1,    AG_PHI2,
     +              AG_ALPH,    AG_ALP1,    AG_ALP2,
     +              AG_H1,      AG_BL1,     AG_TL1,
     +              AG_H2,      AG_BL2,     AG_TL2,
     +              AG_RMIN,    AG_RMAX,    AG_DPHI,    AG_NPDIV,
     +              AG_NZ,      AG_DZ,      AG_TWIS,
     +              AG_LX,      AG_LY,      AG_LZ,
     +              AG_HX,      AG_HY,      AG_HZ,
     +              AG_A,       AG_ZA,      AG_W,       AG_NLMAT,
     +              AG_WORK,    AG_SEEN,    AG_LSTY,
     +              AG_LWID,    AG_COLO,    AG_FILL,
     +              AG_SERIAL,  AG_ISVOL,   AG_ISTATUS,
     +              AG_ZI(16),  AG_RMN(16), AG_RMX(16),
     +              AG_VOLUME,  AG_MOTHER,  AG_SHAPE,   AG_CNICK,
     +                                                  AG_ENDSAVE,
     +              AG_RESET1,  AG_THETAX,  AG_THETAY,  AG_THETAZ,
     +              AG_ALFAX,   AG_ALFAY,   AG_ALFAZ,
     +              AG_PHIX,    AG_PHIY,    AG_PHIZ,
     +              AG_X,       AG_Y,       AG_Z,
     +              AG_STEP,    AG_C0,      AG_NDIV,
     +              AG_IAXIS,   AG_NDVMAX,  AG_ORTI,    AG_NCOPY,
     +              AG_RESET2,
     +              AG_KONLY,   AG_ORT,     AG_MARK
      COMMON/AGCPART/AG_code,AG_trktyp,AG_mass,AG_charge,AG_tlife,
     +                       AG_bratio(6),AG_mode(6),AG_pdg,AG_ecode
C local variables valid inside same block
      COMMON/AGCLOCA/AG_BEGSCR, AG_UBUF(100), AG_PAR(100),
     +              AG_AA(20),  AG_ZZ(20),    AG_WW(20),   AG_NWBUF,
     +              AG_XHMAX,   AG_YHMAX,     AG_ZHMAX,    AG_RHMAX,
     +              AG_FHMAX, AG_FHMIN, AG_NBITS, AG_BIN,  AG_TYPE,
     +              AG_IROT,  AG_NPAR,  AG_ISET,  AG_IDET, AG_JDU,
     +              AG_IRESER,                             AG_ENDSCR,
     +              AG_TITLE,   AG_EXNAME,    AG_PARLIST,  AG_MATERIAL,
     +              AG_MIXTURE, AG_COMPONENT, AG_MEDIUM,   AG_OPTION
      COMMON/AGCSTAC/AG_STACK(AG_LSTACK,15)
      EQUIVALENCE  (AG_ATTRIBUTE,AG_WORK),(AG_STEMAX,AG_DMAXMS),
     +             (AG_ALFAX,AG_ALPHAX),  (AG_ALFAY,AG_ALPHAY),
     +             (AG_ALFAZ,AG_ALPHAZ),  (AG_TWIST,AG_TWIS),
     +             (AG_P1,AG_HX),         (AG_P2,AG_HY),
     +             (AG_NPDIV,AG_NPDV),
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 
 
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
    real    Sum,bratio(6)
    Integer i
 
    call gspart(%Code,%Title,%TrkTyp,%Mass,%Charge,%Tlife,0,0)
    Sum=0;   Do i=1,6 { if (%Mode(i)>0) Sum+=%Bratio(i); }
    If Sum>0
    {  Do i=1,6 { bratio(i)=%Bratio(i)*100.0001/Sum; }
       call GSDK(%Code, Bratio, %Mode)
    }
    If (%pdg  != 0) Call SET_PDGEA(%pdg,%code)
    if (Idebug > 1) Call GPPART(%Code)
    if (Idebug > 2) Call GPDCAY(%Code)
 end
*CMZ :          08/08/98  23.17.10  by  Pavel Nevski
*-- Author :    Pavel Nevski   03/05/98
*************************************************************************
      SUBROUTINE  aGFVOLU (Ivol,Cvol,Cshap,numed,par,npar)
*
* description: extract parameters of a give geant volume
*
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      integer   Ivol,numed,npar,nv
*     integher  Ishap
      character Cvol*4,Cshap*4
      real      par(*)
 
*         make GFVOLU call... ? => CVOL,CSHAP
          Nv=-1;  npar=0;  numed=0;
          If (JVOLUM>0) Nv=IQ(JVOLUM-1)
          if (Ivol<1 | Ivol>Nv)  Return
          Call GFVOLU (Ivol,CVOL,CSHAP)
*         Call UHTOC   (IQ(JVOLUM+IVOL),4,Cvol,4)
*         Ishap     = Q(LQ(JVOLUM-IVOL)+2)
*         Cshap     = Cshapes(Ishap)
          Numed     = Q(LQ(JVOLUM-IVOL)+4)
          Npar      = Q(LQ(JVOLUM-IVOL)+5)
*         Numat     = Q(LQ(JTMED-Numed)+6)
          Call Ucopy (Q(LQ(JVOLUM-IVOL)+7),par,min(50,Npar) )
       end
 
*CMZ :          29/06/98  13.00.34  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
****************************************************************************
          subroutine  ARZOUT(Idiv,Lo,CCKey,IC,opt)
*                                                                          *
* Description: same functionality as RZOUT is supposed with few additions: *
*            - consistence between Bank at Lo and Ckey is checked          *
*            - previous bank with simular Ckey is read and compaired,      *
*              new bank is writtent only if it differs from the old one.   *
*            - very crude version , to be developed later (?). Therefore   *
*              intermediate input bank is kept on a free Link=1 of L1Doc   *
* Attention:   both RZIN and RZOUT may trigger garbage collection          *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
 Integer        Ie,Iprin,Idiv,Lo,Li,Key(3),Nc,IC,i,k,New,Old,Mn,Mo,Istat,diff;
 Character*(*)  CCkey,Opt,status*10,Copt*4,Ckey*12
*
 New(k)=IQ(Lo+k)
 Old(k)=IQ(Li+k)
*
*
  check Lo>0;  Nc=0;  Iprin=Idebug; Ie=0; Li=0;
  if new(2)>20
  { diff=IQ(Lo-1)-new(2)-1; if (diff>1) Call MZPUSH(IxCONS,Lo,0,-Diff,'I') }
  else
  { prin4 CCkey; (' ARZOUT: empty documentation bank detected for ',a); }
 
* take into account that IQ(L-5) are integer and may be swaped,
* but key is ascii and should never be swapped
*
  Ckey=CCkey(1:8)//CCkey(8:8)//CCkey(7:7)//CCkey(6:6)//CCkey(5:5)
  Call CLTOU(Ckey);   Call UCTOH(Ckey,key,4,12);
  if (key(1)!=IQ(Lo-4) | (key(2)!=IQ(Lo-5) & key(3)!=IQ(Lo-5)))
  {  prin4 key,IQ(Lo-4),IQ(Lo-5); (' ARZOUT error: key=',3a4,' bank=',2a4)
     IC=0; Return;
  }
 
  istat=IQ(Lo); status=' '; IC=0;
 
* look for the previous definition, see that it is readable
* and test thet the output bank was not lost due to garbage collection
* CD - read the highest cycle, return data + cycle info
 
  CALL RZIN (IxDIV,Li,2,Key,999999,'CD')
  if (IQUEST(1)!=0)
  { prin4 ckey; (' ARZOUT message: bank ',a,' not found')
    status='new';  Li=0;  go to :w:;
  }
  if (IQ(Lo)!=Istat)
  { prin0 ckey; (' ARZOUT error: bank ',a,' link is not protected !')
    status='bad';  Lo=0;  go to :w:;
  }
 
* previous definition found - extract its cycle number
  IC=0; Nc=IQUEST(50); if (IQUEST(1)==0 & 0<Nc&Nc<20) Ic=IQUEST(50+Nc)
 
  ie=1; status='updated';  if (Li<=0)
  { prin4 key; (' ARZOUT error: key=',3a4,' not found '); go to :w: }
 
  ie=2; "data"   if (New(15)!=Old(15)) goto :w:
  mn=new(3)+new(11)+new(12);  mo=old(3)+old(11)+old(12);
  do i=1,New(15) { If (New(mn+i)!=Old(mo+i)) go to :w: }
 
  ie=3; "links"  if (New(12)> Old(12)) goto :w:
 
  ie=4; "header" if (New(11)> Old(11)) goto :w:;
  mn=new(3);  mo=old(3);
 
* do i=1,New(11) { If (New(mn+i)!=Old(mo+i)) go to :w: }
 
  ie=0; status='found'
 
  :w: Copt='SN';                           " If (ie>2)   Copt='SNR'  "
  if (Li>0) Call MZDROP(IxSTOR,Li,' ')     " drop first, it may move "
  if (Lo>0 & status!='found') CALL RZOUT(Idiv,Lo,Key,IC,Copt)
  prin4  status,key,ie,nc,ic; (' aRZOUT status - ',a,' - ',3a4,' cycles ',3i6)
 
 end
 
 
 
 
*CMZ :          20/04/98  15.46.43  by  Pavel Nevski
*CMZ :  1.30/00 29/04/97  23.23.51  by  Pavel Nevski
*CMZU:  1.00/01 15/01/96  20.20.30  by  Pavel Nevski
*-- Author :    L.Vacavant, A.Rozanov    14/12/94
******************************************************************************
*                                                                            *
     subroutine    A G Z O P E N (stream,name,Copt,Npar,Ipar)
*                                                                            *
* Description: (re)open a file with events in GENZ format-via Fatmen or GENZ *
*   After a succesful open, K keeps track of what should be closed next call *
* Modifications:                                                             *
* PN 20.04.98  - automatic record length correction                          *
*              - stream is saved in mem stack                                *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
Character  Stream*(*),Name*(*),Copt*(*),FName*255/' '/,IOFILE*8,
           CREQ*256,COPTN*20,CSTREAM*8,FZOP*4
Integer    LOCF,Npar,Ipar(*),KEYS(10),LENOCC,Nfound,Jcont,Unit,
           Ier,Irc,Jrc,K,Lc,iend,mem,iu,IREQ,ko,LREC,L,NUH,HEAD(400)
Common     /AgZbuffer/  K,JRC,JCONT,CSTREAM,COPTN,CREQ,IREQ,iend,mem(100,5)
*
*  extract requested unit record
   If      INDEX(Stream,'B')>0 { iu=2; IBack = -1; IBackOld = 0; }
   else If INDEX(Stream,'O')>0 { iu=3; Ioutp = -1; IOutpOld = 0; }
   else                        { iu=1; IKine = -1; IKineOld = 0; }
   if (LocF(iend)-LocF(K)>=100) Stop ' AGZOPEN: insufficient  buffrer length '
   Call UCOPY(mem(1,iu),K,LocF(iend)-LocF(K));
   Unit=20+iu;  write (IOFILE,'(6hIOFILE,i2)') Unit;
 
*  close previously opened unit
   If  K==1   { Call FMCLOS(FName,IOFILE,0,'DE',Irc);  IF (Jrc==0) Jcont=0;  }
   elseIf K>0 { if iu<=2 {Call FZENDI(Unit,'TX')}else{Call FZENDO(Unit,'TX')}}
*
   If Name!=' '  { CREQ=Name; COPTN=COPT; CSTREAM=Stream; IREQ=1; }
   else          { if (iu!=2) IREQ-=1;                            }
   LC=LENOCC(CREQ);  FName=' ';  Nfound=0;  Ier=-1;  Ko=K;  K=0;
   LREC=8100;        If (Index(Stream,'Z')>0) LREC=0
   If Index(Stream,'F')>0
   {  Print *,'* AGZOPEN trying to get tape from FATMEN catalog *'
      CALL FMLOGL(-2); Call FMLFIL(CREQ(1:LC),FName,KEYS,NFound,1,JCont,JRC)
      If NFound>0 & Jrc<=0                    "   fatmen request manager    "
      {  K=1;  IQUEST(10)=3;                  "inhibit tape label processing"
         Call FMFILE(Unit,FName,'FN',Irc);      ier=0;  If (Irc>1) ier=irc
   }  }
   else If iu<=2 & IREQ>0                     "   direct  file  request     "
   { " first try the variable record length format, then the fix length one "
      :R: Print *,' ANZOPEN opening file ',CREQ(1:LC);
      If Index(Stream,'L')>0
      {  Fzop='XI';  K=2;  OPEN (Unit,FILE=CREQ,Iostat=Ier,
                           STATUS='OLD',FORM='UNFORMATTED',RECL=8100) }
      else
      {  Fzop='XIL'; K=3;  CALL CFOPEN(IQUEST,0,0,'r ',0,CREQ,ier)    }
      IF Ier==0
      { Call FZFILE(Unit,LREC,Fzop); CALL FZLOGL(Unit,-2)
        * automatic record length detection
        NUH=400;  Call FZIN  (Unit,IxDiv,L,2,'S',NUH,HEAD)
        If Iquest(1)==-4 & Iquest(12)==202
        {  LREC=IQUEST(15); print *,' AGZOPEN: LREC corrected to',LREC
           Call FZENDI(Unit,'TXQ');  GoTo :R:
        }  Call FZENDI(Unit,'IQ')
   }  }
   else If iu==3 & IREQ>0
   {  CALL CFOPEN(IQUEST,0,LREC,'w ',0,CREQ,ier);          K=3;
      IF Ier==0 { Call FZFILE(Unit,LREC,'XOL');  Ier=Iquest(1); }
   }
   IF Ier!=0 { If (IREQ>0) print *,' AGZOPEN error K,ier=',K,Ier,
                                   ' file =',CREQ(1:LC);   K=0;
             }
   else      { If iu==1 { IKine = -1; IKineOld = -1; CoptKine = Coptn; }
               If iu==2 { IBack = -1; IBackOld = -1; CoptBack = Coptn; }
               If iu==3 { Ioutp = -1; IOutpOld = -1; CoptOutp = Coptn; }
               CALL FZLOGL(Unit,-2)
             }
   Kevent(iu)=0;  Call UCOPY(K,mem(1,iu),LocF(iend)-LocF(K))
*
End
 
 
*CMZ :          05/08/98  23.16.12  by  Pavel Nevski
*CMZ :  1.30/00 19/03/97  21.57.11  by  Pavel Nevski
*CMZU:  1.00/01 15/01/96  20.20.30  by  Pavel Nevski
*-- Author :    L.Vacavant, A.Rozanov    14/12/94
******************************************************************************
*                                                                            *
                subroutine    A G Z R E A D (Stream,ier)
* Modifications and comments:                                                *
* last event may be lost                                                     *
* PN, 24.11.97 - both IDEVT and IDRUN are taken only from the primary stream *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
   Integer      ISLFLAG,i,ier,iprin,jvol,Ldata,Lk,N,NP,NT,NS,IdZ/0/,IdG/0/
   Integer      NHSETS,NDSETS,NSECT,NDETM,NSET,JOCRUN,JOCEVT,IGEN,NTRA,M
   Integer      LOCF,INDEX,CSADDR,Iadr,iu,jb,none,Idev,Ierold(3)/3*0/
   Integer      Lun/21/,Lhead/0/,ifl/0/,nw/0/,Lsup,Iev/0/,Ihead(400)/400*0/
   Character    Stream*(*),HEAD*4,CHEAD(2)*4/2*' '/,Chopt*8/'*'/,IDH*4,Cin*4
   Logical      Trig,Done/.true./
*  tentative guess for standard GFOUT data
   Character*4  Gsets(23)/'PART','MATE','TMED','VOLU','ROTM','SETS','DRAW',
                          'RUNG',  'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' ,
                          'HEAD','VERT','KINE','JXYZ','HITS','DIGI','SCAN'/
   Character*4  Esets(3) /'CODE','RUN ','EVEN'/
   Character    CREQ*256,COPTN*20,CSTREAM*8
   Integer      K,Jrc,Jcont,IREQ,iend,mem
   Common       /AgZbuffer/ K,JRC,JCONT,CSTREAM,COPTN,CREQ,IREQ,iend,mem(100,5)
*
  Replace [INP(#,#,#,#,#)] with [
    CHECK (Index(Chopt,'#1')>0 | Index(Chopt,'*')>0);   Nt=Nt+1;
    {IF} '#1'='G' { Np=Np+1; CHECK Jvol==0; IF (#3>0) Call MZDROP(#2,#3,'L'); }
    IF #3==0 { Call FZIN(LUN,#2,#3,1,'A',Nhead,Ihead); jb=#3;    }
    ELSE     { jb=#3; WHILE LQ(jb)>0 { jb=LQ(jb) };
               Call FZIN(LUN,#2,jb,0,'A',Nhead,Ihead); jb=LQ(jb) }
    Ier=Iquest(1);  Nw=Iquest(14);  CHECK jb>0;  Call UHTOC(IQ(jb-4),4,IDH,4);
    IF (IDH!=HEAD&IDEBUG>0) print *,' AGZREAD got ',IDH,' instead of ',HEAD;
    Ns=Ns+1; IQ(jb-5)=iu;  #4=IQ(jb+(#5));
    IF (#5==-2&Ier==0) { DO I=1,IQ(jb-2) { IF (LQ(jb-I)>0) #4=I; }}
    PRIN2 '#3','#4',#4,Nw; (' AGZREAD: read',2(2x,a6),' = ',i6,'  Leng = ',i8)
  ]
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
    Check ( index(stream,'P')>0 & IkineOld<=-1 _
          | index(stream,'B')>0 & IBackOld<=-1 )
10  Iprin=max(Idebug+1,ISLFLAG('INPU','PRIN'))
                             iu=1;  Chopt=CoptKine;
    If index(stream,'B')>0 { iu=2;  Chopt=CoptBack; }
    If index(stream,'S')>0 {        Chopt=' ';      }
    Call Ucopy(mem(1,iu),K,LocF(Iend)-LocF(k))
    M=5;  If (INDEX(CSTREAM,'1')>0) M=2
    Lun=20+iu;  HEAD=CHEAD(iu);  jvol=JVOLUM; Np=0; Nt=0; Ns=0;
    Done=.false.;  If (Kevent(iu)==0) { Done=.true.; Ierold(iu)=0 }
*
  Loop
  {  If done | HEAD=='NONE'
     {  Cin='S';        if (Chopt==' ')  Cin='SE'
        If (Stream='P' & 1<kevent(1) & kevent(1)<=Ptype)  Cin='SE'
        Lhead=400;      Call FZIN(LUN,IXDIV,LSUP,2,Cin,LHEAD,IHEAD)
        Ier=Iquest(1);  ifl=Iquest(11);  Nw=Iquest(14);  HEAD='NONE'
        If Ier<0  { prin0 ifl; (' error',i6,', see ZEBRA manual page 299');
               If (IQUEST(11)==-4 & IQUEST(12)==202) <w> IQUEST(14),IQUEST(15)
                  (10x,'Expected block size',i6,', found on input',i6); Next;}
        If Ier==1 { prin1 ifl; (' zebra sor, run ',i6); Iev=0; IDz=Ifl; Next;}
        If Ier> 1 { prin1 ier,ifl; (' zebra err, run ',2i6); If (Ier<M) Next;
                    IerOld(iu)=Ier;  Ier=0;   ifl=1;  Kevent(iu)+=1;  break; }
        If      Lhead=1 & Ifl=0 { i=IHEAD(1);  If(1<=i&i<=22) HEAD=Gsets(i); }
        else If Lhead=2 & Ifl>0 { HEAD='RUNG'; If(Kevent(iu)>0) HEAD='HEAD'; }
        else If Lhead=1 & Ifl>0 { i=IHEAD(1);  IF(1<=i&i<=3)  HEAD=Esets(i); }
        else If LHead==3 & Ihead(1)+IHEAD(2)+Ihead(3)==0      { HEAD='RAWD'; }
        else If Lhead>2 {"atlas genz format" Call UHTOC(Ihead(3),4,HEAD,4);  }
        Trig=Ifl.gt.0
        If ( " new eor " HEAD=='HEAD' & Ns==0 & Nt>0 & Kevent(iu)>0 _
           | HEAD=='RUNG' & Nt==0 | HEAD=='CODE' | HEAD=='RUN') Trig=.false.
        If Trig
        { prin2 kevent(iu),Lun,IHEAD(1),IHEAD(2),HEAD
          (' AGZREAD: event',i8,' on unit',i4,' ended by',2i6,A6)
          Break;
        }
     }  Done=.true.
*
     If (iu==1 & Head=='HEAD' & JHEAD>0) Call MZDROP(IxDIV,JHEAD,' ')
     If      Head=='RUNG' { inp(G,IXCONS,JRUNG,  IdG,    +1)
             If (iu==1)          IDRUN=max(IdG,IdZ,IHEAD(1)) }
     else If Head=='PART' { inp(G,IXCONS,JPART,  NPART,  -2) }
     else If Head=='MATE' { inp(G,IXCONS,JMATE,  NMATE,  -2) }
     else If Head=='TMED' { inp(G,IXCONS,JTMED,  NTMED,  -2) }
     else If Head=='ROTM' { inp(G,IXCONS,JROTM,  NROTM,  -2) }
     else If Head=='VOLU' { inp(G,IXCONS,JVOLUM, NVOLUM, -2) }
     else If Head=='SETS' { inp(G,IXCONS,JSET,   NSET,   -1) }
     else If Head=='DETM' { inp(G,IXCONS,LKDETM, NDETM,  -1) }
     else If Head=='SCAN' { inp(G,IXCONS,LKDETM, NDETM,  -1) }
     else If Head=='CODE' { inp(E,IxCONS,LKRUNT, IGEN,   +1) }
     else If Head=='RUN ' { inp(E,IxCONS,LKRUNT, none,   +1) }
     else if iu==1 & kevent(1)<Ptype+1         { Next;     }
     else If Head=='RUNT' { inp(E,IxDIV, LKRUNT, JOCRUN, +5) }
     else If Head=='EVNT' { inp(E,IxDIV, LKEVNT, JOCEVT, +6) }
     else If Head=='EVEN' { inp(E,IxDIV, LKEVNT, NTRA,   +1) }
     else If Head=='HEAD' { inp(K,IxDIV, JHEAD,  IDEV ,  +2)
          If iu==1 & Jb>0 & IQ(Jb+1)>1  {IDRUN=IQ(Jb+1); IDEVT=IDEV}}
     else If Head=='VERT' { inp(K,IXDIV, JVERTX, NVERTX, +1) }
     else If Head=='KINE' { inp(K,IXDIV, JKINE,  NTRACK, +1) }
     else If Head=='HITS' { inp(H,IXDIV, JHITS,  NHSETS, -2) }
     else If Head=='DIGI' { inp(D,IXDIV, JDIGI,  NDSETS, -2) }
     else If Head=='RECB' { inp(R,IXDIV, LKARP1, NSECT,  -2) }
     else If Head=='RAWD' { inp(R,IXDIV, LKARAW, Ldata,  -1)
              Lk=LkaRaw; N=0; while Lk>0
              {  prin2 (IQ(LK-i),i=1,5);(' ND,NS,NL=',3i6,' IDH,IDN =',a4,i8)
                 N+=1; Call UCTOH('RAWD',IQ(Lk-4),4,4); IQ(Lk-5)=N; Lk=LQ(Lk)
              }
          }
     else {   prin1 HEAD,LHEAD,(IHEAD(i),i=1,min(LHEAD,10))
              (' READRZ: unknown structure ',A,' skipped '/,
                 8x,'Lhead=',i6,' header=',10z9/(20x,10z9))
          }
     IF Ier#0 { <W> Ier,head; (' READRZ error ',i5,' entering ',A); }
  }
*
  If (JKINE>0  & IQ(JKINE-1)==1 ) Call MZPUSH(IxDIV,JKINE, 0,1,'I')
  If (JVERTX>0 & IQ(JVERTX-1)==1) Call MZPUSH(IxDIV,JVERTX,0,1,'I')
*
  CHEAD(iu)=HEAD; Kevent(iu)+=1;  Ier=IerOld(iu)
  If Stream=='P'
  {  if ( jvol==0 & Jvolum>0 )   Call AgReINIT
     if ( 1<kevent(1) & kevent(1)<=Ptype+1 & Ier==0 )   Goto 10
     If (LKEVNT>0&INDEX(Chopt,'E')>0&INDEX(Chopt,'K')==0)
     {  Iadr=CSADDR('AGUSKINE');  call UHTOC(IQ(LKEVNT-4),4,IDH,4)
        If      IDH=='EVNT' { Call AgGZKINE(iprin)      }
        else If IDH=='EVEN' { Call AgEZKINE(iprin)      }
        else If IADR!=0     { Call CSJCAL(Iadr,1, Iprin,0,0,0,0, 0,0,0,0,0) }
        else { <w> IDH; (' READRZ error: unknown event bank :',a) }
     }
     If (LKARAW>0 & LKARP1==0)   Call AgBEAMdat
  }
  if (ns>0 & Ier<6) { Ier=0; IQUEST(1)=0; }
  End
 
 
*CMZ :  1.30/00 23/05/96  22.35.51  by  Pavel Nevski
*CMZU:  1.00/01 14/01/96  18.11.41  by  Pavel Nevski
*-- Author :    Pavel Nevski   14/01/96
***************************************************************************
                   Subroutine  A G N T O P E N (File,IDH)
* Description:  Open a CW n-tuple (done AgGENZ) with generated events     *
*               Status is saved in 'opened'                               *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Character*(*) File
     Integer       LENOCC,Li/20/,Iprin,Ier,IDH
     Logical       opened/.false./
*
     Iprin=Idebug
     If (Opened) then
        Call  HREND('HCWN')
        Close (Li)
     endif
*
     call HRopen (Li,'HCWN',file,' ',1024,Ier)
     If (ier!=0)
     {  <w> Ier,file(1:Lenocc(file)); (' AgNTOPEN: error ',i6,' openning ',a)
        opened = .false.
     }
     else
     {  Opened = .true.;   IdInp   = IDH;   Kevent(1) = 0
        IKine  = -2;       IkineOld = -2
     }
     end
 
 
*CMZ :          31/10/97  13.01.26  by  Pavel Nevski
*CMZ :  1.30/00 04/07/96  14.07.00  by  Pavel Nevski
*CMZU:  1.00/01 14/01/96  22.35.50  by  Pavel Nevski
*-- Author :    A. Rozanov  11/03/95
***************************************************************************
                Subroutine  A G N T R E A D (ier)
* Description:  Read Kinematics of primary tracks from Ntuples            *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
      Integer    ier,Ntrk,Nvrt,IPARTI,ITR,Nv
      Real       vertex(4),P(4),E,Ener,VMOD
*
      Integer           Mxtr,irun,Nparti,Itype
      Real              vxyz,pp4
      Parameter         (MxTr=2000)
      common /AgBlock1/ irun,vxyz(4)
      common /AgBlock2/ Nparti,itype(MxTr,5),PP4(MxTr,8)
*     - - - - - - - - - - - - - - - - - - - - - - - - -
*
       kevent(1) = max(nint(ptype),kevent(1)+1)
*      call hldir  ('//','T')
       call hcdir  ('//HCWN',' ')
       call hrin   (IdInp,9999,0)
       call hbname (IdInp,'      ',0,     '$CLEAR')
       call hbname (IdInp,'Block1',irun,  '$SET')
       call hbname (IdInp,'Block2',Nparti,'$SET')
       call HGNT   (IdInp,kevent,ier)
       if ier!=0
       { <w> kevent(1),ier; (' AGNTREAD error: Kevnt,ier=',2i8); return }
*
       CALL aGSVERT(vxyz,0,0,0.,0,Nvrt)
       Ener   = 0
       ntrk   = 0
       do itr=1,Nparti
          check itype(itr,1) == 1 & itype(itr,5) == 0
          p      = { pp4(itr,1), pp4(itr,2), pp4(itr,3), pp4(itr,4) }
          vertex = { pp4(itr,6), pp4(itr,7), pp4(itr,8), pp4(itr,5) }
          E      =  VMOD(P,4)
*
          Call aGSVERT (Vertex,0,0,0.,0,Nv)
          Call aPDG2GEA(itype(itr,2),IPARTI)
          Call aGSKINE (P,IPARTI,Nv,float(itr),0,NTrk)
          check Ntrk>0
          Nvrt  = Max(Nv,Nvrt)
          Ener += E
       enddo
       Print *,' AGNTREAD: # of particles fed to GEANT=',Ntrk,
                         ' # VERTEX=',Nvrt,' Etot=',Ener
    END
 
 
*CMZ :          18/08/97  11.17.47  by  Pavel Nevski
*CMZ :  1.30/00 16/04/97  20.01.44  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/06/96
******************************************************************************
*                                                                            *
                subroutine    A G Z W R I T E (Stream,ier)
*                                                                            *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
   Integer      iu,Lun,Iev,Ier,iprin, Idevt0/-1/,IsubE0/0/,Lk/0/
   Logical      Done/.true./
   Character    stream*(*)
*  tentative guess for standard GFOUT data
*  'PART','MATE','TMED','VOLU','ROTM','SETS','DRAW','RUNG','DETM','a',
*  'RUNT','EVNT','DETM','a','a','a','HEAD','VERT','KINE','JXYZ','HITS','DIGI'
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
    Ier=999;  Check Stream=='O';  Ier=0;  Iu=3;
    Iprin=Idebug;   Lun=20+iu;  Iev=Kevent(iu);
    prin3 Idevt,Idevt0,Iev,CoptOutp
    (' AGZwrite Idevt,Idevt0,Iev = ',3I10,' opt=',a)
*
    If Kevent(iu)==0
    {  Call AgZout(LUN,'RUNG','G',Iev,CoptOutp,JRUNG, 'IDRUN',  +1, 8, ier)
       Call AgZout(LUN,'PART','G',Iev,CoptOutp,JPART, 'NPART',  -2, 1, ier)
       Call AgZout(LUN,'MATE','G',Iev,CoptOutp,JMATE, 'NMATE',  -2, 2, ier)
       Call AgZout(LUN,'TMED','G',Iev,CoptOutp,JTMED, 'NTMED',  -2, 3, ier)
       Call AgZout(LUN,'ROTM','G',Iev,CoptOutp,JROTM, 'NROTM',  -2, 5, ier)
       Call AgZout(LUN,'VOLU','G',Iev,CoptOutp,JVOLUM,'NVOLUM', -2, 4, ier)
       Call AgZout(LUN,'SETS','G',Iev,CoptOutp,JSET,  'NSET',   -1, 6, ier)
       Call AgZout(LUN,'DETM','G',Iev,CoptOutp,LKDETM,'NDETM',  -1, 9, ier)
       Kevent(iu)=1;  Lk=-1;  Idevt0=-1;  If (Ier!=0) IOutpOld=0;  Return
    }
    If Idevt != Idevt0 | IsubEVnt !=IsubE0
    {  if (JHITS>0) Call GRLEAS (JHITS)
       if (JDIGI>0) Call GRLEAS (JDIGI)
       Call AgZout(LUN,'HEAD','*',Iev,CoptOutp,JHEAD, 'IDEVT',  +2, 17,ier)
       Call AgZout(LUN,'RUNT','E',Iev,CoptOutp,LKRUNT,'JOCRUN', +5, 11,ier)
       Call AgZout(LUN,'EVNT','E',Iev,CoptOutp,LKEVNT,'JOCEVT', +6, 12,ier)
       Call AgZout(LUN,'VERT','K',Iev,CoptOutp,JVERTX,'NVERTX', +1, 18,ier)
       Call AgZout(LUN,'KINE','K',Iev,CoptOutp,JKINE, 'NTRACK', +1, 19,ier)
       Call AgZout(LUN,'HITS','H',Iev,CoptOutp,JHITS, 'NHSETS', -2, 21,ier)
       Call AgZout(LUN,'DIGI','D',Iev,CoptOutp,JDIGI, 'NDSETS', -2, 22,ier)
       Call AgZout(LUN,'RECB','R',Iev,CoptOutp,LKARP1,'NSECT',  -2, 13,ier)
       Kevent(iu)+=1;
    }
    else If LK==0           " second call after users reconstruction "
    {  Call AgZout(LUN,'RECB','R',-1, CoptOutp,LKARP1,'NSECT',  -2, 13,ier) }
*
    If (Ier!=0) IOutpOld=0
    Lk      =   LKARP1
    Idevt0  =   Idevt
    IsubE0  =   IsubEvnt
end
 
 
*CMZ :          30/07/97  11.24.59  by  Pavel Nevski
*-- Author :    Pavel Nevski 06/06/97
***************************************************************************
                Subroutine  A G S V E R T (Vertex,NtBeam,NtTarg,UBUF,NU,Nv)
* Description:                                                            *
*               add a common vertex displacement in an event              *
*               and save vertices in GEANT VERT bank                      *
* Note:         An additional word in Vertex(4) is Time-of-flight - this  *
*               is different from GSVERT, which pass it in /GCTRAK/ TOFG  *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
*
     Real     Vertex(4),UBUF(*)
     Integer  NtBeam,NtTarg,NU
     Integer  Iv,Nv,IDEVT0/-999/,Iprin/0/
     REAL     RNDM,VDIST,VMOD,a,b,d,z,d1,Vxyz(4),Vcut/0/
*
     Iprin=Idebug
*    if 3 sigma interval overlaps with request and Sigma is not too big:
     If Idevt0!=Idevt
     {  Idevt0=Idevt; D=abs(AvSigm(3));  Z=-1.e+10
        if Zmin<AvCoor(3)+3*D & AvCoor(3)-3*D<Zmax & Zmax-Zmin > D/5
             { until ZMin<=z&z<=ZMax { call rannor(a,b); z=Avcoor(3)+D*b } }
        else { z=Zmin+Rndm(-1.)*(Zmax-Zmin) }
        call rannor(a,b)
        VertexNow = {Avcoor(1)+Avsigm(1)*a,Avcoor(2)+Avsigm(2)*b,z}
        If (VMOD(VertexNow,3)>0 & Iprin>=2) <w> VertexNow;
           (' AgSVERT: vertex shifted at ',3F10.4)
     }
*
      D1=VMOD(Vertex,4)
      CALL VADD (Vertex,VertexNow,Vxyz,3)
      TOFG=Vertex(4);  Vxyz(4)=TOFG
      DO IV=1,Nvertx
         Check NtBeam == Q(LQ(Jvertx-IV)+5)
         Check NtTarg == Q(LQ(Jvertx-IV)+6)
         If NtBeam!=0 { If (D1>0) Call UCOPY(Vxyz,Q(LQ(Jvertx-IV)+1),4) }
         else         { If (VDIST(Q(LQ(Jvertx-IV)+1),Vxyz,4)>0)  Next;  }
         Nv=Iv; Return
      Enddo
*
      Call GsVERT(Vxyz,NtBeam,NtTarg,UBUF,NU,Nv)
      If (Nv>0) Return
      <w> ntbeam; (' AgSVERT can not set vertex ',i8)
END
 
 
 
*CMZ :          08/08/98  23.14.38  by  Pavel Nevski
*CMZ :  1.30/00 21/03/97  15.15.10  by  Pavel Nevski
*-- Author :    Pavel Nevski   27/05/96
************************************************************************
                SUBROUTINE A G Z B A C K
*                                                                      *
* Description: AG pileup facility - draft, to be polished later        *
* Modifications:                                                       *
* PN, 27.11.97 : Neagitive Bg multiplicity means no fluctuations       *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Character Copt*4
     Integer   AgPFLAG,Iprin,Nback,Ibevnt,Nskip,Ier,I
     Real      Tbunch,RNDM
*
     Iprin = AgPFLAG('BACK','RECO')
     :bunch: Do IbCurrent=-IbBefor,IbAfter
    {  Call POISSN(BgMult,NBack,Ier)
       If (BgMULT<0) NBack=nint(abs(BgMULT))
       Tbunch=IbCurrent*BgTime*1.e-9
       Prin1 IbCurrent,Nback
       (' AGZBACK: pile-up in bunch',i5,' consists of ',i5,' event(s)')
       Do IBevnt=1,Nback
       {  Nskip=2*Rndm(-1.)*BgSkip+.5
          Prin3 IbEvnt,Nskip
          (' AGZBACK:    merging event',i5,' after skipping',i5)
          Do I=1,Nskip+1
          { Copt='BS';   If (I>Nskip) Copt='B'
            Call AgZREAD (Copt,ier); Check Ier>0  " event still was read "
            Call AGZOPEN ('B', ' ', ' ', 0, 0)
            Call AgZREAD (Copt,ier); Check Ier>0  " geometry skept Only  "
            Prin0; (' AGZBACK error: CANNOT OPEN FILE WITH EVENTS, QUIT !')
            IbackOld=0;  Return
          }
          call AgMERGE (Iprin,IbCurrent,IbEvnt,Tbunch,Ier)
          If (Ier!=0) Break :bunch:
    }  }
    Call AgTRIM
*
    END
 
 
***************************************************************************
   subroutine AgMERGE (Iprin,IbCurrent,IbEvnt,Tbunch,Ier)
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
*
   Integer            Laref,   Jd,jhs,jhd,jv2,jk2
   Common  /agcmerge/ Laref(2),Jd,jhs,jhd,jv2,jk2
   Integer            AgPointr,Iprin,IbCurrent,IbEvnt,Ier,Ib,
                      Dum(20)/20*0/,Jdu,Idu,Nv1,Nv2,Nt1,Nt2,Nh1,Nh2,
                      Iv,Jv,It,Jt,i,j,Isel,Nw,Nw1,Nw2,L,L1,L2
   REAL               Tbunch
*  GEANT general definitions for SET-type banks:
   Integer            JSF,JDF,IDF,ISF,LINK,Iset,Idet
*KEEP,STAFUNC.
C Declare types for the things used in the statement function STAFUNC
      INTEGER IIIII, LVPRIN,LVGEOM,LVHIST,LVGRAP,LVDEBU,LWPRIN,
     +        LWDEBU,LVSIMU,LVDIGI,LVRECO,LVMFLD,LVANAL,LVBACK
C
C Statement Functions for ZEBRA
C datacard value are in LW PRIN/DEBU, current print is in LV PRIN
C
      LVPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+1)
      LVDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWPRIN(IIIII)=IQ(LQ(LKDETM-IIIII)+2)
      LWDEBU(IIIII)=IQ(LQ(LKDETM-IIIII)+3)
      LVGEOM(IIIII)=IQ(LQ(LKDETM-IIIII)+4)
      LVHIST(IIIII)=IQ(LQ(LKDETM-IIIII)+5)
      LVGRAP(IIIII)=IQ(LQ(LKDETM-IIIII)+6)
      LVSIMU(IIIII)=IQ(LQ(LKDETM-IIIII)+7)
      LVDIGI(IIIII)=IQ(LQ(LKDETM-IIIII)+8)
      LVRECO(IIIII)=IQ(LQ(LKDETM-IIIII)+9)
      LVMFLD(IIIII)=IQ(LQ(LKDETM-IIIII)+10)
      LVANAL(IIIII)=IQ(LQ(LKDETM-IIIII)+11)
      LVBACK(IIIII)=IQ(LQ(LKDETM-IIIII)+12)
 
*KEND.
   "link" JSF(LINK) = LQ(LINK-Iset);  JDF(LINK) = LQ(LQ(LINK-Iset)-Idet)
   "data" ISF(LINK) = IQ(LINK+Iset);  IDF(LINK) = IQ(LQ(LINK-Iset)+Idet)
*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
   Prin2; ('*****  AgMERGE *****')
   Call MZLINT(IXSTOR,'AgCMERGE',Laref,Jd,Jk2)
   Call AgMER(Iprin,JVERTX,+1,Nv1,Nv2);  Nvertx=Nv1+Nv2;
   Call AgMER(Iprin,JKINE, +1,Nt1,Nt2);  Ntrack=Nt1+Nt2;
*
*                        adjust track-vertex cross references
   do iv=Nv1+1,Nvertx
   {  jv=LQ(JVERTX-iv); check jv>0;   "ToF"  Q(jv+4)+=Tbunch;
 
      if (Q(jv+5)>0) Q(jv+5)+=Nt1     " only for geant produced tracks   "
      do i=8,7+nint(Q(jv+7))          " update track numbers in vertices "
      {               j=jv+i; if (Q(j)>0) Q(j)+=Nt1; If (Q(j)>Ntrack) Q(j)=0; }
   }
   do it=Nt1+1,Ntrack
   {  jt=LQ(JKINE-it);  check jt>0;
      do i=6,7+nint(Q(jt+7))          " update vertex numbers  in tracks "
      {  check i!=7;  j=jt+i; if (Q(j)>0) Q(j)+=Nv1; if (Q(j)>Nvertx) Q(j)=0; }
   }
*
*  First, count number of hit sets in both streams as the number of links
   Check Jhits>0;   Call AgMER(Iprin,Jhits,-2,Nh1,Nh2)
   prin3 Nh1,Nh2; (' AgMerge: start hit sets merging',2i8)
   If Nh2>0
   {  **>                            correct only track references now
      Iset=0;  J=JHITS; If (LQ(J)>0) J=LQ(J)
      While AgPOINTR (J,Iset,Idet)==0
      {  JDU=LQ(JDF(JSET)-3); Check JDU>0; Idu=Q(JDU+9); Ib=LVBACK(Idu)
         L = abs(ib);  L1=-L;  L2=+L                    " rule 1: t+/-(i-1)
         IF (L>=10)  { L1= - (L/100);  L2= mod(L,10) }  " rule 2: -i1,1,+i2
         If Ib>=0 & L1<=IBcurrent&IBcurrent<=L2
         {  Nw2=IDF(J);  JHS=JDF(J);  Nw=1+IQ(JDF(JSET)+1)+IQ(JDF(JSET)+3)
            Isel=Nw2/Nw; do i=JHS+1,JHS+Nw2,Nw
            { If (IQ(i)>0) IQ(i)+=Nt1; IF (IQ(i)>Ntrack) IQ(i)=0; }
         }
         else { Isel=0;  Call MZDROP (IxSTOR,JDF(J),'L') }
         prin3 ISF(JSET),IDF(JSET),Isel,Ibcurrent
         (' AgMERGE:',2(1x,a4),i8,' Hits selected in bunch',i3)
   }  }
   If Nh1>0 & Nh2>0
   {  Iset=0;
      While AgPOINTR (LQ(JHITS),Iset,Idet)==0
      {  IF JSF(JHITS)<=0 | JDF(JHITS)<=0
         { " hit set/det did not exist previously "
            Call GSAHIT (Iset,Idet,Dum,Dum,Dum,Ier)
            IF Ier<=0
            { <w> ISF(JSET),IDF(JSET)
              (' AgMERGE: Unable to create bank for secondary HITS for ',2a6)
              Ier=1;  Break
            } IQ(LQ(JHITS-Iset)+Idet)=0;  Ier=0
         }
         **>                                     Check geometry consistance
         IF Iset>IQ(JHITS-2) | Idet>(IQ(JSF(JHITS)-2))
         {  <w> IQ(JHITS-2),IQ(JSF(JHITS)-2),ISF(JSET),IDF(JSET)
            (' AgMERGE: HITS bank has too few links ',2I3,' to accept ',2a6)
            Ier=2;  Break
         }
         **>                                     Copy hits to existing bank
         Nw1=IDF(JHITS);   Nw2=IDF(LQ(JHITS))
         prin4 nw2,nw1,ISF(JSET),IDF(JSET)
         ('  ===> Copying',i10,' words to',i10,' in set/det',2(2x,a4))
         JHS=JDF(LQ(JHITS));   JHD=JDF(JHITS)
         Call AgPUSH (Iprin,JHD,0,Nw1+Nw2,Ier);
         IF Ier>0
         {  <w> IbCurrent; (/1x,30(1H*),' AgMERGE ERROR ',30(1H*)/,
            5x,'not enouph memory to merge bunch',i3,', merging abandoned'/)
            Break
         }
         **>
         Call UCOPY (IQ(JHS+1),IQ(JHD+Nw1+1),Nw2)
         IQ(LQ(JHITS-Iset)+Idet)=Nw1+Nw2
         Call MZDROP (IxSTOR,JHS,'L')
      }  Call MZDROP(IxSTOR,LQ(JHITS),'L')
   }
   If (IDebug>0) Call DZVERI(' VERT/KINE/HITS merged',IXDIV,'CLU')
   If (Ier==0)   Ier=Iquest(1)
   Laref(1)=0
END
 
 
*****************************************************************************
     subroutine AgMER (Iprin,Jj,k,N1,N2)
* Description : for positive k, IQ(J+k) should contain object counter
*               for negative, it is number of words or liks.
*****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEND.
   Integer Iprin,N1,N2,jj,jv,jv2,i,k,ier
 
   check Jj>0; Jv=Jj;
   do i=1,2  { N1=N2; N2=0; check Jv>0; N2=IQ(Jv+k); Jv=LQ(Jv); }
   If (JV>0) print *,'****  AGMER WARNING: SOMETHING LEFT !!! ***'
   Check k>0;  If N1>0 & N2>0
   {  Call agpush(Iprin,Jj,N1+N2,1,Ier);  check Ier==0;
      DO I=1,N2
      { JV2=LQ(LQ(Jj)-I); Check JV2>0; Call ZSHUNT(IXSTOR,JV2,Jj,-(N1+I),1) }
      Call MZDROP(IXSTOR,LQ(Jj),'L');
   }  IQ(Jj+k)=N1+N2
END
 
 
*****************************************************************************
      Subroutine AgTRIM
*****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
   Integer AgPOINTR,Link,JDF,IDF,Iset,Idet,JHS,Nextra,Nw
*  GEANT general definitions for SET-type banks:
   "link" JDF(LINK) = LQ(LQ(LINK-Iset)-Idet)
   "data" IDF(LINK) = IQ(LQ(LINK-Iset)+Idet)
*
   Check Jhits>0;  Iset=0
   While AgPOINTR (JHITS,Iset,Idet)==0
   {   Nw=IDF(JHITS); JHS=JDF(JHITS);  Nextra=IQ(JHS-1)-Nw
       If (Nextra>0) Call MzPUSH(IxDIV,JHS,0,-Nextra,'I')
   }
END
 
 
*****************************************************************************
      SUBROUTINE AgPUSH (iprin,LINK,NLINK,NDATA,Ier)
*****************************************************************************
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
      Integer Iprin,LINK,NLINK,NDATA,Ier,MBANK,
              NLOLD,NDOLD,NNEW,NLEFT,NLNEED,NDNEED
*
      Ier   = 0
      MBANK = IQ(LINK-4)
      NLOLD = IQ(LINK-3)
      NDOLD = IQ(LINK-1)
      check (NDATA>NDOLD | NLINK>NLOLD)
      NNEW  = 20+max(NDOLD,NDATA)+max(NLOLD,NLINK)
      Call MZNEED(IXDIV,NNEW,'G');  NLEFT=IQUEST(11) " after request "
      prin5  MBANK,NLOLD,NDOLD,NLINK,NDATA,NLEFT
      (' AgPUSH: pushing bank ',A4,' from ',2i8,' to ',2i8,' Nleft=',i8)
*
      IF NLEFT<=100
      {  prin0  MBANK,ABS(NLEFT),NNEW
         (' AgPUSH: Not enough memory for pushing bank ',A4/ _
          ' ***',I8,' words short in relocating',I8,' words ***')
         Ier=NNEW;  return
      }
      NLNEED=max(NLINK-NLOLD,0); If (NLNeed>0 & NLeft>1000)  NLNeed+=100;
      NDNEED=max(NDATA-NDOLD,0); If (NDNeed>0 & NLeft>10000) NDNeed+=5000;
      Call MZPUSH(IXDIV,LINK,NLNEED,NDNEED,'I')
      IF IQUEST(1) != 0
      {  prin0  MBANK,ABS(NLEFT),NNEW
         (' AgPUSH: wrong strategy for pushing bank ',A4/ _
          ' ***',I8,' words short in relocating',I8,' words ***')
         Ier=NNEW;  return
      }
      END
 
 
************************************************************************
                  FUNCTION AGPOINTR(LINK,IS,ID)
*                                                                      *
* Description :                                                        *
*        give the address of a next HIT/DIGI bank in GEANT             *
* Arguments   :                                                        *
*        LINK  (in)  - link to the top level bank (i.e HITS,HIT2 etc)  *
*        IS,ID (out) - Geant Iset/Idet of the next non-empty bank      *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
      INTEGER  AGPOINTR,LINK,IS,ID,JH,JS,JP,JD,NW
*
      AGPOINTR = 1;    IF (IS>0) GOTO :cont:
      :set: Loop
      { IS=IS+1;  ID=0;  :cont:   IF (IS>IQ(LINK-2) | IS>IQ(JSET-1)) RETURN
        JH=LQ(LINK-IS);  JS=LQ(JSET-IS);  IF (JS<=0 | JH<=0) next :set:
        :det: Loop
        {  ID=ID+1;                       IF (ID > IQ(JH-2)) next :set:
           JP=LQ(JH-ID); JD=LQ(JS-ID);    IF (JD<=0 | JP<=0) next :det:
           NW=IQ(JH+ID);                  IF (NW<=0)         next :det:
           AGPOINTR = 0;  Return;          :done:
      } }
END
 
 
 
 
 
 
 
 
 
*CMZ :          29/01/98  00.21.52  by  Pavel Nevski
*CMZ :  1.30/00 27/03/97  19.08.58  by  Pavel Nevski
*CMZ :  1.00/00 12/01/95  23.13.14  by  Pavel Nevski
*-- Author :    Pavel Nevski   09/01/95
****************************************************************************
*                                                                          *
                 SUBROUTINE   A G R F I L E (Lun,File,Option)
*                                                                          *
*  Description: save DETM structure together with GEANT standard structures*
*               do it now in a simple way instead of the scan structure    *
*       Routine to open a GEANT/RZ data base.                              *
*       LUN logical unit number associated to the file                     *
*       FILE RZ file name                                                  *
*       CHOPT is a character string which may be I or O                    *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCSCAL.
      INTEGER MXSLNK, ISLINK, LSLAST, LSCAN, LSTEMP, LSPARA, LSERAY
*
      PARAMETER(MXSLNK=100)
      COMMON/GCSCAL/ ISLINK(MXSLNK)
      EQUIVALENCE (LSLAST,ISLINK(MXSLNK))
      EQUIVALENCE (LSCAN ,ISLINK(1)),(LSTEMP,ISLINK(2))
      EQUIVALENCE (LSPARA,ISLINK(3)),(LSERAY,ISLINK(4))
*
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
 
      Integer       INDEX,LENOCC,Lun,Lsv,L,Istat
      EQUIVALENCE   (LKSLUG(NSLINK),Lsv)
      Character     File*(*),Option*(*),Ctree*4,Cdoc*4
*     Integer       Keys(2),ICycle,Istat,Idvers/1/
*     Character*20  ChDir
      SAVE          CHTOP,     CHTAGS
      CHARACTER*8   CHTOP,     CHTAGS(2)
      DATA          CHTOP/' '/,CHTAGS/'Object','Version'/
*
      If (LdArea(1)=0) call MZLINT(IxCONS,'AGCDOCL',LDarea,Lpar,LDarea)
 
*   Save GEANT standard structures in a new file
      Lsv=Lscan;                           Lscan=Lkdetm;
 
      if (Idebug>1) print *,' AgRFILE: file=',%L(file)
      if index(Option,'i')+index(Option,'I')>0
      { if (Idebug>1) print *,' AgRFILE: calling RZOPEN '
        CALL RZOPEN(LUN,CHTOP,File,'XW',1024,ISTAT)
        If istat!=0
        { print *,' AgRFILE error ',ISTAT,' opening file ',%L(file)
          return
        }
        CALL RZFILE(LUN,CHTOP,'X')
        if IQUEST(1)!=0
        { print *,' AgRFILE error ',IQUEST(1),' on rzfile ',%L(file)
          return
        }
        if (Idebug>1) print *,' AgRFILE: calling GRIN '
        CALL GRIN  ('INIT', 0,' ')
        Ctree=' ';  If (Lscan>0) call UHTOC(IQ(Lscan-4),4,Ctree,4)
        if Ctree=='DETM'
        {  LkDetm=Lscan; L=LQ(LKDETM-1);
           Cdoc=' ';  If (L>0) call UHTOC(IQ(L-4),4,Cdoc,4)
           if (Cdoc=='DOCU') L1DOC=L
      } }
      else
      { CALL RZOPEN(LUN,CHTOP,File,'NWX',1024,ISTAT)
        CALL RZMAKE(LUN,CHTOP,2,'HI',CHTAGS,5000,'XO')
        CALL GROUT ('INIT', 1,' ')
      }
      CALL RZEND(CHTOP)
      CLOSE(LUN)
 
      Lscan=Lsv; if (ISTAT==0) return;
"   Update existing file in exchange mode, return directory    "
"     Call RzOpen(Lun,ChDir,Cfile,'UXW',1024,Istat)            "
"   Update, show and reset LOCK, exchange mode                 "
"     Call RzFile(Lun,ChDir,'ULDX')                            "
"   Append the DETM structure after GEANT standard objects     "
"     Call UCTOH('DETM',Keys,4,4);   Keys(2)=Idvers;           "
"     If (LkDETM>0) Call RzOut(IxCons,LkDETM,keys,ICycle,' '); "
"     Call RzEnd(Chdir);  Close(Lun);                          "
*
      Prin0 ISTAT; (' AGRFILE error =',i6)
*
      End
 
 
 
 
*CMZ :  1.30/00 26/04/96  17.40.50  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/04/96
****************************************************************************
                subroutine   A g F O U T (Lun,Chopt,Ier)
* Description:  write out DETM parameter bank and optionally DOCUmentation *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,AGCDOCL.
C     common for the documentation supporting links
      Integer           LDarea(2),L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
      COMMON /AGCDOCL/  LDarea,   L1Doc,L2Doc,LKDoc,Ldoc,Ldete,Lpar
C     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Integer        Lun,Ier,IOPD,INDEX,Iprin
     Character*(*)  Chopt
*
     Iprin=Idebug
     IOPD=Index(Chopt,'d')+Index(Chopt,'D')
     If LKDETM>0
     {  CALL FZOUT(LUN,IxCONS,LKDETM,0,'L',2,1,24)
        Prin1;(' *** AGFOUT ** Data structure DETM (N=24) written out')
     }
     If LKDoc>0&IOPD>0
     {  CALL FZOUT(LUN,IxCONS,LKDoc, 0,'L',2,1,25)
        Prin1;(' *** AGFOUT ** Data structure DOCU (N=25) written out')
     }
*
  END
 
 
*CMZ :          31/07/97  17.26.28  by  Pavel Nevski
*CMZ :  1.30/00 16/04/97  20.30.01  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/06/96
***************************************************************************
    subroutine  A g Z o u t (LUN,Name,Key,Iev,Chopt,J,Var,K1,K2,Ier)
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
    Character  chopt*(*),key*1,name*4,Var*(*)
    Integer    LUN,IEV,J,K1,K2, Is,Ier,n1,nw,mw,INDEX,Nob,
               Iprin/3/,IOH(3)/0,0,0/,LH/3/,IHEAD(10)
*
    Iprin=Idebug
    If (IOH(1)==0) Call MZIOCH(IOH,3,'2I 1H -I')
    Check J>0 & Ier==0 & Index(Chopt,key)+Index(Chopt,'*')+Index(Key,'*')>0
    Call UCTOH(name,IHEAD(3),4,4);  IHEAD(1)=K2;  IHEAD(2)=0
    If IQ(J-4)!=IHEAD(3)
    {  prin2 IQ(J-4),IHEAD(3)
       (' AgZOUT warning: bank ',a4,' found instead of ',a4)
    }
    Is=0; N1=IQ(J+K1);  If IEV>=0
    { * count objects for SLUG .... shit, may be more than really exist.
      Nob=0;  if (Var=='IDRUN') { Nob=7; }
      else  { If (Index(Chopt,'E')+Index(Chopt,'*')>0 & LKRUNT>0)  Nob+=1
              If (Index(Chopt,'E')+Index(Chopt,'*')>0 & LKEVNT>0)  Nob+=1
              If (Index(Chopt,'K')+Index(Chopt,'*')>0 & JVERTX>0)  Nob+=1
              If (Index(Chopt,'K')+Index(Chopt,'*')>0 & JKINE >0)  Nob+=1
              If (Index(Chopt,'H')+Index(Chopt,'*')>0 & JHITS >0)  Nob+=1
              If (Index(Chopt,'D')+Index(Chopt,'*')>0 & JDIGI >0)  Nob+=1
              If (Index(Chopt,'R')+Index(Chopt,'*')>0)             Nob+=1
            }
      Is=1; IHEAD(1)=IEV; IHEAD(2)=Nob; IEV=-1;
    }
*   ----------Zebra(1994), p.107-----------
    Call FZOUT(LUN,0,J,Is,'L',IOH,LH,Ihead)
*   ---------------------------------------
    Ier=Iquest(1);  nw=Iquest(11); Mw=Iquest(14)
    PRIN2 Is,Name,var,N1,nw; (' AGZwrite:',i3,2(2x,a6),'=',i6,'  Leng=',i8)
    Check Ier!=0; print *,' AgZOUT error ier=',ier,' after ',Mw,'Mw written'
    If (Ier==+1)  print *,' software EOT set by FZLIMIT reached '
    If (Ier==-1)  print *,' attempt to write after End-Of-Data  '
    If (Ier==-2)  print *,' write error occured on output stream'
*
End
 
 
*CMZ :          30/07/97  13.50.48  by  Pavel Nevski
*CMZ :  1.30/00 12/03/97  13.19.34  by  Pavel Nevski
*-- Author :    Pavel Nevski
**************************************************************************
                SUBROUTINE   A g G Z K I N E   (Iprin)
* Description: routine for feeding GENZ information into GEANT.          *
* Note the use of TOFG in common GCTRAK, set before Calls to GSVERT,     *
* to store the correct time of the vertices                              *
* Original version:                              Robert DeWolf  23/07/92 *
* Mod:  Minimum cut on secondary vertices (10 microns)       PN 12/01/96 *
*       No user words with EVNT references are save in KINE  PN 04/07/96 *
**************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCTRAK.
      INTEGER NMEC,LMEC,NAMEC,NSTEP ,MAXNST,IGNEXT,INWVOL,ISTOP,MAXMEC
     + ,IGAUTO,IEKBIN,ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN,NLVSAV,ISTORY
     + ,MAXME1,NAMEC1
      REAL  VECT,GETOT,GEKIN,VOUT,DESTEP,DESTEL,SAFETY,SLENG ,STEP
     + ,SNEXT,SFIELD,TOFG  ,GEKRAT,UPWGHT
      REAL POLAR
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEND.
      CHARACTER*4 CGENE
      INTEGER     IE,IP,NEVTS,NPART1,NKEEP,ICODE,ISTAT,IV,IV1,IEVT,IRUN,
                  IWTFL,IPA,ITRA,Iprin,MOTH(2),IDAU,K,NU/2/
      REAL        AMAS,Vrt(4),UB(2),VV(4),VDIST,VCUT,VERT(4),WEIGH,P4(4)
      DATA        VCUT /0.0010/
 
      Call AgNZGETG(1,NEVTS)
      Prin2 NEVTS; (' AgGZKINE: Gate found with ',I8,' events.')
 
      NKEEP = 0
      DO IE = 1,NEVTS
         Call AgNZGETE(1,IE,NPART1,IRUN,IEVT,CGENE,VERT,IWTFL,WEIGH)
         prin2 CGENE,IRUN,IEVT,IE,NPART1,WEIGH
               (' AgGZKINE: Generator ',A4,'  Run',I8,' Gate',I8/10x,
                ' Event',I6,' has',I7,' particles.  Weight =',E10.5)
*
         UB(1) = IE                         "  store event number here
         IV1   = Nvertx
         DO IP = 1,NPART1
            Call AgNZGETP(1,IE,IP,ISTAT,ICODE,P4,AMAS,MOTH,TOFG,IDAU,VV)
            Check ISTAT==1                  "  Skip non stable particles    "
            Check IDAU<=0                   "  and particles with daughters "
            Prin5 IP,ICODE,ISTAT,IDAU; (3x,'partc: IP,ICODE,ISTAT,IDAU=',4I8)
 
            K=ABS(ICODE)
*           stable particle but not e,nu,mu,Mmu    Ntau  or   phot ?
            IF (.not.(11<=K&K<=14 | K==16 | K==22 | K>=100)) then
               prin1 ICODE; (' AgGZKINE: Stable particle with funny code',I10)
            endif
            Call VSCALE (VV,100.,Vrt,3)       " get vertex in cm "
            Vrt(4) = TOFG                     "  for print only  "
            DO 11 IV=IV1+1,Nvertx
 11         IF ( VDIST(Q(LQ(Jvertx-IV)+1),Vrt,3) <= Vcut) GO TO 19
            UB(2) = MOTH(1);  Call aGSVERT (Vrt,0,0,UB,NU,IV)
            Prin3 IV,Vrt; (3x,'vertx',I5,' booked at ',3F10.5,' Time=',E10.3)
 
 19         Call aPDG2GEA (ICODE,IPA)
            IF (IPA<=0) THEN
               prin1 ICODE,IP; (' AgGZKINE: PDG code ',I7,' for particle',I6,
                                ' is not recognized by GEANT. SKIP.')
               next
            ENDIF
 
            UB(2) = IP;     Call aGSKINE (P4, IPA, IV, UB, NU, ITRA)
            Check ITRA>0;   NKEEP = NKEEP + 1
*
*          Set the flag in the GENZ record as negative of the Geant KINE ?
*           Call AgNZXREF(1,IE,IP,ITRA,NORPH)
        enddo
     enddo
     prin1 NKEEP,Nvertx;
           (' AgGZKINE: # of particles fed to GEANT=',I6,' # of VERTEX',I6)
     END
 
 
*CMZ :  1.30/00 07/07/96  13.29.54  by  Pavel Nevski
*-- Author :    Pavel Nevski   14/01/96
**************************************************************************
                SUBROUTINE   A g N Z G E T G (ILINK,NEVEN)
* Description: Get number of  Gates in event (Neven)                     *
* Input : ILINK - Link number : 1 = primary, 2 = secondary               *
* Original version:                              Robert DeWolf  23/07/92 *
**************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
      INTEGER ILINK,NEVEN,NZBANK
      entry gnzgetg (ILINK,NEVEN)
      NEVEN = -1
      If (LKEVNT>0) NEVEN = NZBANK(IXDIV,LKEVNT)
      END
 
 
*CMZ :  1.30/00 07/07/96  13.29.54  by  Pavel Nevski
*-- Author :    Pavel Nevski   14/01/96
***************************************************************************
    SUBROUTINE AgNZGETE(ILK,IDE,NPART,IRUN,IEVT,CGNAM,VERT,IWTFL,WEIGH)
* Description: Get parameters of a single event in gates                  *
* Input : ILK   - Link number  : 1 = primary, 2 = secondary (obsolete)    *
*         IDE   - ID of event in gate ( ZEBRA IDN)                        *
* Output: NPART - Number of particles in event record                     *
*         IRUN  - run number as recorded by generator                     *
*         IEVT  - event number as recorded by generator                   *
*         CGNAM - generator name                                          *
*         VERT(4)- x,y,z,t of event (metres,seconds)                      *
*         IWTFL - weight flag                                             *
*         WEIGH - event weight                                            *
* Original version:                              Robert DeWolf  23/07/92  *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
      CHARACTER*(*)  CGNAM
      REAL           VERT(4),WEIGH
      INTEGER        ILK,IDE,NPART,IRUN,IEVT,IWTFL,LGENE,LGENP,LZFIND
 
      entry gNZGETE(ILK,IDE,NPART,IRUN,IEVT,CGNAM,VERT,IWTFL,WEIGH)
      NPART = -1;                                   check   LKEVNT>0
      check  "#of links"   IQ(LKEVNT-2)>=2 & "2nd link"  LQ(LKEVNT-2)>0
      LGENE = LZFIND(IXDIV,LQ(LKevnt-2),IDE,-5);    check   LGENE>0
      check  "bank length" IQ(LGENE-1)>=12 & "#of links" IQ(LGENE-2)>=1
*
      IRUN  =    IQ(LGENE+4)
      IEVT  =    IQ(LGENE+5)
      CALL UHTOC(IQ(LGENE+6),4,CGNAM,4)
      CALL UCOPY( Q(LGENE+7),VERT,4)
      IWTFL =    IQ(LGENE+11)
      WEIGH =     Q(LGENE+12)
*
* Find the number of particles
      LGENP = LQ(LGENE-1);                    Check LGENP>0
      NPART = MOD(IQ(LGENP+2),100000)
*
      END
 
 
*CMZ :          13/07/98  10.03.02  by  Pavel Nevski
*CMZ :  1.30/00 07/07/96  13.29.54  by  Pavel Nevski
*-- Author :    Pavel Nevski   14/01/96
****************************************************************************
    SUBROUTINE AgNZGETP(IL,IDE,IP,ISTAT,IDPDG,P,AMASS,MOTH,TIME,IDAU1,V)
* Description: Get parameters of a single particle from EVNT bank          *
* Input : IL    - Link number : 1 = primary, 2 = secondary (obsolete)      *
*         IDE   - ID of event in gate                                      *
*         IP    - Number of particle in event record                       *
* Output: ISTAT - HEPEVT status flag. Returns 0 if record not found.       *
*         IDPDG - PDG code for particle                                    *
*         P     - 4-momentum (px,py,pz,E)                                  *
*         AMASS - particle (quark) mass                                    *
*         MOTH  - mothers. If MOTH(2)<0 the range is MOTH(1)-ABS(MOTH(2))  *
*         TIME  - Start time of particle relative to interaction (sec)     *
*         IDAU1 - a daughter pointer                                       *
*         V     - vertex coordinates (in meter)                            *
* Original version:                              Robert DeWolf  23/07/92   *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
      REAL     P(4),AMASS,PTOT,VMOD,TIME,V(3)
      INTEGER  IL,IDE,IP,IDPDG,ISTAT,MOTH(2),IDAU1,
               LGENE,LGENP,LZFIND,MODUL,ND,IOFF
*
      entry gNZGETP(IL,IDE,IP,ISTAT,IDPDG,P,AMASS,MOTH,TIME,IDAU1,V)
      IDPDG = 0
      ISTAT = 0
      Check Lkevnt>0
*
* Find the event with the desired IDN:
      check  "#of links"   IQ(LKEVNT-2)>=2 & "2nd link"  LQ(LKEVNT-2)>0
      LGENE = LZFIND(IXDIV,LQ(LKevnt-2),IDE,-5);    check   LGENE>0
      check  "bank length" IQ(LGENE-1)>=12 & "#of links" IQ(LGENE-2)>=1
      LGENP = LQ(LGENE-1);                          Check   LGENP>0
*
      MODUL   = MOD(IQ(LGENP+3),100 000)
      ND      = IQ(LGENP-1)
      IOFF    = MODUL * (IP-1) + 3
      Check     IOFF+MODUL<=ND
*
      LGENP   = LGENP + IOFF
      ISTAT   = IQ(LGENP + 1)
      IDPDG   = IQ(LGENP + 2)
      MOTH(1) = IQ(LGENP + 3)
      MOTH(2) = IQ(LGENP + 4)
      IDAU1   = IQ(LGENP + 5)
      call UCOPY(Q(LGENP + 6),P,3)
      AMASS   =  Q(LGENP + 9)
      TIME    =  Q(LGENP + 10)
      call UCOPY(Q(LGENP + 11),V,3)
      PTOT    = VMOD( Q(LGENP+6),3)
      IF AMASS>=0. { P(4) = SQRT(PTOT**2  +  AMASS**2)     }
      ELSE         { P(4) = SQRT(MAX(PTOT**2-AMASS**2,0.)) }
*
      END
 
 
 
*CMZ :          03/06/98  12.10.44  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  17.34.39  by  Pavel Nevski
*CMZU:  1.00/01 14/01/96  21.33.44  by  Pavel Nevski
*-- Author :    A. Rozanov  11/03/95
***************************************************************************
    Subroutine  A G G Z U F L T (COPTS,Ieven,Ipart,Idpdg,vert,Pmom,Irc)
* Description : select particles according to the SLUG KINE card standard *
*    PtFlag:  <---collider mode--->   <-----fix target----->              *
*             <pdg>   <---geant--->   <-pdg->  <---geant--->              *
*             0   1   2 . . . . . 9   10   11  12 . . . . 20              *
*             E  PT........................................>              *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Character*(*)  COPTS
     Integer        Ieven,Ipart,Idpdg,Irc
     Real           vert(4),Pmom(4),VMOD,Psel,theta,eta,phi,ptot,pt
*
  Irc   = 0             ! track would be rejected
  If (PtFlag<10) then
     pt    = vmod(pmom,2)
     ptot  = vmod(pmom,3)
     If ptflag==0  { Psel=ptot }  else  { Psel=pt }
     Irc+=1; Check  Ptmin <= Psel & Psel <= Ptmax
*
*    eta should fit into +/-10
     theta = max(asin(pt/ptot),1.e-4);  if (pmom(3)<0) theta=pi-theta
     eta   = -alog(tan(theta/2.))
     Irc+=1; Check  EtaMin <=Eta & Eta<= EtaMax
*
*    atan2 require (y,x) or (sin,cos):
     phi   = 0;  if (pt  > 0) phi=atan2(pmom(2),pmom(1))
                 if (phi < 0) phi=phi+TwoPi
     Irc+=1; Check  PhiMin <=Phi & Phi<= PhiMax
     Irc+=1; Check  Zmin<=vert(3)&vert(3)<=Zmax
  else
     Irc+=1; Check  Pxmin<=Pmom(1)&Pmom(1)<=Pxmax
     Irc+=1; Check  Pymin<=Pmom(2)&Pmom(2)<=Pymax
     Irc+=1; Check  Pzmin<=Pmom(3)&Pmom(3)<=Pzmax
  endif
*
  Irc = 0               ! track selected
END
 
 
 
*CMZ :          13/05/98  21.57.17  by  Pavel Nevski
*CMZ :  1.30/00 10/07/96  10.34.36  by  Pavel Nevski
*CMZU:  1.00/01 29/01/96  16.49.07  by  Pavel Nevski
*-- Author :    Pavel Nevski
*----------------------------------------------------------------------------
                SUBROUTINE   A P D G 2 G E A  (IDIN,IDOUT)
* For a given PDG particle code in IDIN, returns GEANT particle ID in IDOUT
*----------------------------------------------------------------------------
      INTEGER    NPARTC,      NPARTM,    NPART,  I
      PARAMETER (NPARTC = 52, NPARTM = 100)
      INTEGER    IDGEA(0:NPARTM),IDPDG(0:NPARTM),IDMAX,IGMAX
      DATA       NPART/NPARTC/
*
* In rough order of multiplicity: gamma,pi+,pi-,pi0,etc
*                -   gamma  pi+   pi-   pi0   K0L   K+   K-    K0S   Eta
*               prot  neut  ~p    ~n    e+    e-   nu_e ~nu_e  mu+   mu-
*              lamda sigm+ sigm0 sigm-  xi0   xi- omeg-
*           ~: lamda sigm- sigm0 sigm+  xi0   xi+ omeg+
*              tau+  tau-    D+    D-    D0  ~D0   DS+   DS-  LamC+
*                W+    W-    Z0   nu_m ~nu_m nu_t ~nu_t
*
  DATA (IDGEA(I),I=0,NPARTC) _
             /   0,    1,    8,    9,    7,   10,   11,  12,   16,   17,
                14,   13,   15,   25,    2,    3,   4,    4,    5,    6,
                18,   19,   20,   21,   22,   23,  24,
                26,   27,   28,   29,   30,   31,  32,
                33,   34,   35,   36,   37,   38,  39,   40,   41,
                42,   43,   44,    4,    4,    4,   4,   48,   48,   48/
*
  DATA (IDPDG(I),I=0,NPARTC) _
            /    0,   22,  211, -211,  111,  130,  321, -321, 310,  221,
              2212, 2112,-2212,-2112,  -11,   11,  -12,  12,  -13,   13,
              3122, 3222, 3212, 3112, 3322, 3312, 3334,
             -3122,-3222,-3212,-3112,-3322,-3312,-3334,
               -15,   15,  411, -411,  421, -421,  431, -431, 4122,
                24,  -24,   23,  -14,   14,  -16,   16,   71,   72,  75/
  DATA IDMAX/4122/,IGMAX/50/
*
*     attention:  (1) is meaningful for arrays starting from (0)
*
      Entry  PDG2GE   (IDIN,IDOUT)
      IDOUT = 0
      IF (abs(IDIN)<=IDMAX) IDOUT = IDGEA(IUCOMP(IDIN,IDPDG(1),NPART))
      return
*
      Entry  AGEA2PDG (IDIN,IDOUT)
      IDOUT = 0
      IF (abs(IDIN)<=IDMAX) IDOUT = IDPDG(IUCOMP(IDIN,IDGEA(1),NPART))
      return
*
      Entry  SET_PDGEA (IDIN,IDOUT)
      I=0;  IF (0<abs(IDIN)&abs(IDIN)<=IDMAX) I=IUCOMP(IDIN,IDPDG(1),NPART)
      IF ( I>0) Then
         If ( IDGEA(I)!=IDOUT ) print *,
            ' SET_PDGEA warning:  particle PDG code ',IDIN,
            ' known to geant as ',IDGEA(I),' is redefined as ',IDOUT
         IDGEA(I)  = IDOUT
         return
      ENDIF
      NPART=min(NPART+1,NPARTM)
      IDPDG(NPART) = IDIN;    IDMAX=max(IDMAX,abs(IDIN))
      IDGEA(NPART) = IDOUT;   IGMAX=max(IGMAX,abs(IDOUT))
      return
*
  END
 
 
*CMZ :  1.30/00 08/07/96  16.11.19  by  Pavel Nevski
*-- Author :    Pavel Nevski   08/07/96
 
      SUBROUTINE GEPCODE (In,Io, Ic)
      if ic==0 { Call APDG2GEA(In,Io) } else { call AGEA2PDG(In,Io) }
      end
 
 
*CMZ :  1.30/00 10/07/96  11.22.34  by  Pavel Nevski
*-- Author :    Pavel Nevski   10/07/96
**************************************************************************
         SUBROUTINE   G N Z P D A T (IDPDG,CPNAM,PMASS,PCHAR,IER)
*                                                                        *
*  Given the particle code IDPDG, this routine returns the information   *
*  about the particle. The data from the EURODE* database has been used  *
*                                                                        *
* Input : IDPDG ( int*4)        - Particle Data Group particle code      *
* Output: CPNAM ( character*8 ) - Name for particle                      *
*         PMASS ( real*4 )      - Particle mass in GeV                   *
*         PCHAR ( real*4 )      - Charge in multiples of proton charge   *
*         IER   ( int*4 )       - error flag                             *
* Original Version.                                 R. DeWolf   12/03/91 *
**************************************************************************
*CDE,TYPING.
     integer     idpdg,ier,k,i,IA,IQ1,IQ2,IQ3
     real        pmass,pchar,m,l
     character   cpnam*8,c
*
     K=IDpdg;    Ia=abs(K);
     i=0;  Q=0;  Ier=0;
     IQ1 = MOD(IA,10000)/1000
     IQ2 = MOD(IA,1000)/100
     IQ3 = MOD(IA,100)/10
*
IF  Ia>0
{   IF IA<=10
 {"quarks"   Q = .6666667-MOD(IA,2)
        if K==     1 { i=  1; c='DOWN    '; m=.15       ; l= .0        }
   else If K==     2 { i=  2; c='UP      '; m=.15       ; l= .0        }
   else If K==     3 { i=  3; c='STRANGE '; m=.35       ; l= .0        }
   else If K==     4 { i=  4; c='CHARM   '; m=1.75      ; l= .0        }
   else If K==     5 { i=  5; c='BOTTOM  '; m=5.1       ; l= .0        }
   else If K==     6 { i=  6; c='TOP     '; m=60.       ; l= .0        }
   else If K==     7 { i=  7; c='LOW     '; m=100.      ; l= .0        }
   else If K==     8 { i=  8; c='HIGH    '; m=160.      ; l= .0        }
   else If K==     9 { i=  9; c='GLUON   '; m=.0        ; l= .0        }
 }
 else IF IA<=20
 {"leptons"  Q =  -MOD(IA,2)
        If K==    11 { i= 11; c='E      -'; m=.510e-03  ; l= .10000e+13}
   else If K==    12 { i= 12; c='ENEU    '; m=.0        ; l= .10000e+13}
   else If K==    13 { i= 13; c='MU     -'; m=.10566    ; l= .21970e-05}
   else If K==    14 { i= 14; c='MUNEU   '; m=.0        ; l= .10000e+13}
   else If K==    15 { i= 15; c='TAU    -'; m=1.7842    ; l= .30400e-12}
   else If K==    16 { i= 16; c='TAUNEU  '; m=.0        ; l= .10000e+13}
   else If K==    17 { i= 17; c='SIGMA  -'; m=40.       ; l= .10000e-19}
   else If K==    18 { i= 18; c='SIGNEU  '; m=.0        ; l= .10000e+13}
 }
 else If Ia<=100
 {  If  (Ia==24 | Ia==37)  Q=1
        If K==    22 { i= 22; c='GAMMA   '; m=.0        ; l= .10000e+13}
   else If K==    23 { i= 23; c='Z0      '; m=93.       ; l= .25360e-24}
   else If K==    24 { i= 24; c='W      +'; m=82.       ; l= .27860e-24}
   else If K==    25 { i= 25; c='HIGGS0  '; m=9.6       ; l= .99730e-20}
   else If K==    37 { i= 37; c='HIGGS  +'; m=23.       ; l= .34310e-20}
 }
 else If Ia<=1000
 {"Mesons"    Q = MOD((IQ2-IQ3),2)
        If K==   111 { i=117; c='PI0     '; m=.13496    ; l= .87000e-16}
   else If K==  -211 { i=118; c='PI     -'; m=.13957    ; l= .26030e-07}
   else If K==   221 { i=119; c='ETA     '; m=.54880    ; l= .62687e-18}
   else If K==  -321 { i=120; c='K      -'; m=.49367    ; l= .12371e-07}
   else If K==  -311 { i=121; c='K0     B'; m=.49772    ; l= .89230e-10}
   else If K==   331 { i=122; c='ETAP    '; m=.95760    ; l= .27400e-20}
   else If K==   113 { i=123; c='RHO0    '; m=.77030    ; l= .43021e-23}
   else If K==  -213 { i=124; c='RHO    -'; m=.76680    ; l= .43021e-23}
   else If K==   223 { i=125; c='OMEGA   '; m=.78260    ; l= .67200e-22}
   else If K==  -323 { i=126; c='K*     -'; m=.89210    ; l= .12900e-22}
   else If K==  -313 { i=127; c='K*0    B'; m=.89210    ; l= .12900e-22}
   else If K==   310 { i=128; c='KSHORT  '; m=.49772    ; l= .89230e-10}
   else If K==   130 { i=129; c='KLONG   '; m=.49772    ; l= .51830e-07}
   else If K==   333 { i=130; c='PHI     '; m=1.0195    ; l= .15600e-21}
   else If K==   115 { i=131; c='A20     '; m=1.32      ; l= .59800e-23}
   else If K==  -215 { i=132; c='A2     -'; m=1.32      ; l= .59800e-23}
   else If K==   421 { i=153; c='D0      '; m=1.8647    ; l= .42700e-12}
   else If K==   411 { i=154; c='D      +'; m=1.8694    ; l= .10450e-11}
   else If K==   431 { i=155; c='DS     +'; m=1.9719    ; l= .43300e-12}
   else If K==   423 { i=156; c='D*0     '; m=2.0072    ; l= .0        }
   else If K==   413 { i=157; c='D*     +'; m=2.0101    ; l= .0        }
   else If K==   433 { i=158; c='DS*    +'; m=2.1150    ; l= .0        }
   else If K==   441 { i=159; c='ETAC1S  '; m=2.9796    ; l= .63900e-22}
   else If K==   443 { i=160; c='J-PSI   '; m=3.0969    ; l= .96797e-20}
   else If K==   445 { i=165; c='CHIC21P '; m=3.5563    ; l= .25320e-21}
   else If K==  -521 { i=188; c='B      -'; m=5.2782    ; l= .14200e-11}
   else If K==  -511 { i=189; c='B0     B'; m=5.2795    ; l= .14200e-11}
   else If K==  -531 { i=190; c='BS0    B'; m=5.4       ; l= .14200e-11}
   else If K==  -541 { i=191; c='BC     -'; m=6.55      ; l= .14200e-11}
   else If K==  -523 { i=192; c='B*     -'; m=5.4250    ; l= .0        }
   else If K==  -513 { i=193; c='B*0    B'; m=5.4180    ; l= .0        }
   else If K==  -533 { i=194; c='BS*0   B'; m=5.54      ; l= .0        }
   else If K==  -543 { i=195; c='BC*    -'; m=6.6       ; l= .0        }
   else If K==   551 { i=196; c='ETAB1S  '; m=9.4       ; l= .10000e-23}
   else If K==   553 { i=197; c='YPSI1S  '; m=9.4603    ; l= .12760e-19}
   else If K==   555 { i=204; c='CHIB21P '; m=9.9132    ; l= .0        }
   else If K==   621 { i=231; c='T0      '; m=60.2      ; l= .0        }
   else If K==   611 { i=232; c='T      +'; m=60.2      ; l= .0        }
   else If K==   631 { i=233; c='TS     +'; m=60.4      ; l= .0        }
   else If K==   641 { i=234; c='TC0     '; m=61.2      ; l= .0        }
   else If K==   623 { i=235; c='T*0     '; m=60.350    ; l= .0        }
   else If K==   613 { i=236; c='T*     +'; m=60.355    ; l= .0        }
   else If K==   633 { i=237; c='TS*    +'; m=60.5      ; l= .0        }
   else If K==   643 { i=238; c='TC*0    '; m=61.350    ; l= .0        }
   else If K==   661 { i=239; c='ETAT1S  '; m=118.08    ; l= .14820e-20}
   else If K==   663 { i=240; c='THET1S  '; m=118.13    ; l= .10760e-20}
   else If K==   665 { i=247; c='CHIT21P '; m=119.13    ; l= .12500e-20}
   else If K==  -721 { i=274; c='L      -'; m=100.27    ; l= .0        }
   else If K==  -711 { i=275; c='L0     B'; m=100.27    ; l= .0        }
   else If K==  -731 { i=276; c='LS0    B'; m=100.40    ; l= .0        }
   else If K==  -741 { i=277; c='LC     -'; m=101.37    ; l= .0        }
   else If K==  -723 { i=278; c='L*     -'; m=100.43    ; l= .0        }
   else If K==  -713 { i=279; c='L*0    B'; m=100.42    ; l= .0        }
   else If K==  -733 { i=280; c='LS*0   B'; m=100.54    ; l= .0        }
   else If K==  -743 { i=281; c='LC*    -'; m=101.63    ; l= .0        }
   else If K==   821 { i=308; c='H0      '; m=160.20    ; l= .0        }
   else If K==   811 { i=309; c='H      +'; m=160.20    ; l= .0        }
   else If K==   831 { i=310; c='HS     +'; m=160.40    ; l= .0        }
   else If K==   841 { i=311; c='HC0     '; m=161.30    ; l= .0        }
   else If K==   823 { i=312; c='H*0     '; m=160.35    ; l= .0        }
   else If K==   813 { i=313; c='H*     +'; m=160.35    ; l= .0        }
   else If K==   833 { i=314; c='HS*    +'; m=160.50    ; l= .0        }
   else If K==   843 { i=315; c='HC*0    '; m=161.50    ; l= .0        }
 }
 else
 { IF IQ3==0 {"Di-quarks" Q=1.333333    -MOD(IQ1,2)-MOD(IQ2,2) }
   else      {" Baryons " Q=2-MOD(IQ1,2)-MOD(IQ2,2)-MOD(IQ3,2) }
        If K==  2212 { i=135; c='P      +'; m=.93828    ; l= .10000e+13}
   else If K==  2112 { i=136; c='N       '; m=.93957    ; l=  898.     }
   else If K==  1001 { i=342; c='QL1     '; m=10.       ; l= .0        }
   else If K==  1002 { i=343; c='QL2     '; m=20.       ; l= .0        }
   else If K==  1003 { i=344; c='QL3     '; m=80.       ; l= .0        }
   else If K==  1004 { i=345; c='QL4     '; m=200.      ; l= .0        }
   else If K==  3222 { i=137; c='SIGMAU +'; m=1.1894    ; l= .80000e-10}
   else If K==  3212 { i=138; c='SIGMA0  '; m=1.1925    ; l= .58000e-19}
   else If K==  3122 { i=139; c='LAMBDA  '; m=1.1156    ; l= .26320e-09}
   else If K==  3112 { i=140; c='SIGMAD -'; m=1.1973    ; l= .14820e-09}
   else If K==  3322 { i=141; c='CASCA0  '; m=1.3149    ; l= .29000e-09}
   else If K==  3312 { i=142; c='CASCA  -'; m=1.3213    ; l= .16420e-09}
   else If K==  2224 { i=143; c='DELTA 2+'; m=1.23      ; l= .59800e-23}
   else If K==  2214 { i=144; c='DELTAU +'; m=1.2310    ; l= .59800e-23}
   else If K==  2114 { i=145; c='DELTA0  '; m=1.2320    ; l= .59800e-23}
   else If K==  1114 { i=146; c='DELTAD -'; m=1.2330    ; l= .59800e-23}
   else If K==  3224 { i=147; c='SIGM*U +'; m=1.3823    ; l= .18300e-22}
   else If K==  3214 { i=148; c='SIGM*0  '; m=1.3820    ; l= .18300e-22}
   else If K==  3114 { i=149; c='SIGM*D -'; m=1.3874    ; l= .16900e-22}
   else If K==  3324 { i=150; c='CASC*0  '; m=1.5318    ; l= .72300e-22}
   else If K==  3314 { i=151; c='CASC*  -'; m=1.5350    ; l= .65200e-22}
   else If K==  3334 { i=152; c='OMEGA* -'; m=1.6722    ; l= .82200e-10}
   else If K==  2203 { i=101; c='UU1     '; m=.30       ; l= .0        }
   else If K==  2101 { i=102; c='DU0     '; m=.30       ; l= .0        }
   else If K==  2103 { i=103; c='DU1     '; m=.30       ; l= .0        }
   else If K==  1103 { i=104; c='DD1     '; m=.30       ; l= .0        }
   else If K==  3201 { i=105; c='SU0     '; m=.50       ; l= .0        }
   else If K==  3203 { i=106; c='SU1     '; m=.50       ; l= .0        }
   else If K==  3101 { i=107; c='SD0     '; m=.50       ; l= .0        }
   else If K==  3103 { i=108; c='SD1     '; m=.50       ; l= .0        }
   else If K==  3303 { i=109; c='SS1     '; m=.70       ; l= .0        }
   else If K==  4201 { i=110; c='CU0     '; m=1.9       ; l= .0        }
   else If K==  4203 { i=111; c='CU1     '; m=1.9       ; l= .0        }
   else If K==  4101 { i=112; c='CD0     '; m=1.9       ; l= .0        }
   else If K==  4103 { i=113; c='CD1     '; m=1.9       ; l= .0        }
   else If K==  4301 { i=114; c='CS0     '; m=2.1       ; l= .0        }
   else If K==  4303 { i=115; c='CS1     '; m=2.1       ; l= .0        }
   else If K==  4403 { i=116; c='CC1     '; m=3.5       ; l= .0        }
   else If K==  4222 { i=166; c='SIGMC 2+'; m=2.44      ; l= .0        }
   else If K==  4212 { i=167; c='SIGMC  +'; m=2.44      ; l= .0        }
   else If K==  4122 { i=168; c='LAMBC  +'; m=2.2812    ; l= .16400e-12}
   else If K==  4112 { i=169; c='SIGMC0  '; m=2.44      ; l= .0        }
   else If K==  4322 { i=170; c='CASCC  +'; m=2.5       ; l= .11000e-12}
   else If K==  4232 { i=171; c='CASCCP +'; m=2.55      ; l= .0        }
   else If K==  4312 { i=172; c='CASCC0  '; m=2.5       ; l= .11000e-12}
   else If K==  4132 { i=173; c='CASCCP0 '; m=2.55      ; l= .0        }
   else If K==  4332 { i=174; c='OMEGC0  '; m=2.6       ; l= .0        }
   else If K==  4422 { i=175; c='CCU   2+'; m=3.63      ; l= .0        }
   else If K==  4412 { i=176; c='CCD    +'; m=3.63      ; l= .0        }
   else If K==  4432 { i=177; c='CCS    +'; m=3.8       ; l= .0        }
   else If K==  4224 { i=178; c='SIGMC*2+'; m=2.53      ; l= .0        }
   else If K==  4214 { i=179; c='SIGMC* +'; m=2.53      ; l= .0        }
   else If K==  4114 { i=180; c='SIGMC*0 '; m=2.53      ; l= .0        }
   else If K==  4324 { i=181; c='CASCC* +'; m=2.65      ; l= .0        }
   else If K==  4314 { i=182; c='CASCC*0 '; m=2.65      ; l= .0        }
   else If K==  4334 { i=183; c='OMEGC*0 '; m=2.75      ; l= .0        }
   else If K==  4424 { i=184; c='CCU*  2+'; m=3.69      ; l= .0        }
   else If K==  4414 { i=185; c='CCD*   +'; m=3.69      ; l= .0        }
   else If K==  4434 { i=186; c='CCS*   +'; m=3.85      ; l= .0        }
   else If K==  4444 { i=187; c='CCC*  2+'; m=4.9       ; l= .0        }
   else If K==  5222 { i=205; c='SIGMBU +'; m=5.67      ; l= .40000e-12}
   else If K==  5212 { i=206; c='SIGMB0  '; m=5.67      ; l= .40000e-12}
   else If K==  5122 { i=207; c='LAMBB0  '; m=5.32      ; l= .40000e-12}
   else If K==  5112 { i=208; c='SIGMBD -'; m=5.67      ; l= .40000e-12}
   else If K==  5322 { i=209; c='CASCB0  '; m=5.77      ; l= .40000e-12}
   else If K==  5232 { i=210; c='CASCBP0 '; m=5.87      ; l= .40000e-12}
   else If K==  5312 { i=211; c='CASCB  -'; m=5.77      ; l= .40000e-12}
   else If K==  5132 { i=212; c='CASCBP -'; m=5.87      ; l= .40000e-12}
   else If K==  5332 { i=213; c='OMEGB  -'; m=5.97      ; l= .40000e-12}
   else If K==  5422 { i=214; c='BCU    +'; m=7.07      ; l= .40000e-12}
   else If K==  5242 { i=215; c='BCUP   +'; m=7.17      ; l= .0        }
   else If K==  5412 { i=216; c='BCD0    '; m=7.07      ; l= .40000e-12}
   else If K==  5242 { i=217; c='BCDP0   '; m=7.17      ; l= .0        }
   else If K==  5432 { i=218; c='BCS0    '; m=7.27      ; l= .40000e-12}
   else If K==  5342 { i=219; c='BCSP0   '; m=7.37      ; l= .0        }
   else If K==  5442 { i=220; c='BCC    +'; m=8.27      ; l= .40000e-12}
   else If K==  5224 { i=221; c='SIGMB*U+'; m=5.97      ; l= .0        }
   else If K==  5214 { i=222; c='SIGMB*0 '; m=5.97      ; l= .0        }
   else If K==  5114 { i=223; c='SIGMB*D-'; m=5.97      ; l= .0        }
   else If K==  5324 { i=224; c='CASCB*0 '; m=6.17      ; l= .0        }
   else If K==  5314 { i=225; c='CASCB* -'; m=6.17      ; l= .0        }
   else If K==  5334 { i=226; c='OMEGB* -'; m=6.37      ; l= .0        }
   else If K==  5424 { i=227; c='BCU*   +'; m=7.37      ; l= .0        }
   else If K==  5414 { i=228; c='BCD*0   '; m=7.37      ; l= .0        }
   else If K==  5434 { i=229; c='BCS*0   '; m=7.57      ; l= .0        }
   else If K==  5444 { i=230; c='BCC*   +'; m=8.57      ; l= .0        }
   else If K==  6222 { i=248; c='SIGMT 2+'; m=60.570    ; l= .0        }
   else If K==  6212 { i=249; c='SIGMT  +'; m=60.570    ; l= .0        }
   else If K==  6122 { i=250; c='LAMBT  +'; m=60.570    ; l= .0        }
   else If K==  6112 { i=251; c='SIGMT0  '; m=60.570    ; l= .0        }
   else If K==  6322 { i=252; c='CASCT  +'; m=60.770    ; l= .0        }
   else If K==  6232 { i=253; c='CASCTP +'; m=60.770    ; l= .0        }
   else If K==  6312 { i=254; c='CASCT0  '; m=60.770    ; l= .0        }
   else If K==  6132 { i=255; c='CASCTP0 '; m=60.770    ; l= .0        }
   else If K==  6332 { i=256; c='OMEGT0  '; m=60.970    ; l= .0        }
   else If K==  6422 { i=257; c='TCU   2+'; m=61.5      ; l= .0        }
   else If K==  6242 { i=258; c='TCUP  2+'; m=61.7      ; l= .0        }
   else If K==  6412 { i=259; c='TCD    +'; m=61.5      ; l= .0        }
   else If K==  6142 { i=260; c='TCDP   +'; m=61.7      ; l= .0        }
   else If K==  6432 { i=261; c='TCS    +'; m=61.8      ; l= .0        }
   else If K==  6342 { i=262; c='TCSP   +'; m=62.       ; l= .0        }
   else If K==  6442 { i=263; c='TCC   2+'; m=62.5      ; l= .0        }
   else If K==  6224 { i=264; c='SIGMT*2+'; m=60.770    ; l= .0        }
   else If K==  6214 { i=265; c='SIGMT* +'; m=60.770    ; l= .0        }
   else If K==  6114 { i=266; c='SIGMT*0 '; m=60.770    ; l= .0        }
   else If K==  6324 { i=267; c='CASCT* +'; m=60.970    ; l= .0        }
   else If K==  6314 { i=268; c='CASCT*0 '; m=60.970    ; l= .0        }
   else If K==  6334 { i=269; c='OMEGT*0 '; m=61.170    ; l= .0        }
   else If K==  6424 { i=270; c='TCU*  2+'; m=61.970    ; l= .0        }
   else If K==  6414 { i=271; c='TCD*   +'; m=61.970    ; l= .0        }
   else If K==  6434 { i=272; c='TCS*   +'; m=62.170    ; l= .0        }
   else If K==  6444 { i=273; c='TCC*  2+'; m=63.170    ; l= .0        }
   else If K==  7222 { i=282; c='SIGMLU +'; m=100.47    ; l= .0        }
   else If K==  7212 { i=283; c='SIGML0  '; m=100.47    ; l= .0        }
   else If K==  7122 { i=284; c='LAMBL0  '; m=100.47    ; l= .0        }
   else If K==  7112 { i=285; c='SIGMLD -'; m=100.47    ; l= .0        }
   else If K==  7322 { i=286; c='CASCL0  '; m=100.67    ; l= .0        }
   else If K==  7232 { i=287; c='CASCLP0 '; m=100.67    ; l= .0        }
   else If K==  7312 { i=288; c='CASCL  -'; m=100.67    ; l= .0        }
   else If K==  7132 { i=289; c='CASCLP -'; m=100.67    ; l= .0        }
   else If K==  7332 { i=290; c='OMEGL  -'; m=100.87    ; l= .0        }
   else If K==  7422 { i=291; c='LCU    +'; m=100.50    ; l= .0        }
   else If K==  7242 { i=292; c='LCUP   +'; m=100.70    ; l= .0        }
   else If K==  7412 { i=293; c='LCD0    '; m=101.50    ; l= .0        }
   else If K==  7142 { i=294; c='LCDP0   '; m=101.70    ; l= .0        }
   else If K==  7432 { i=295; c='LCS0    '; m=101.80    ; l= .0        }
   else If K==  7342 { i=296; c='LCSP0   '; m=102.      ; l= .0        }
   else If K==  7442 { i=297; c='LCC    +'; m=102.50    ; l= .0        }
   else If K==  7224 { i=298; c='SIGML*U+'; m=100.77    ; l= .0        }
   else If K==  7214 { i=299; c='SIGML*0 '; m=100.77    ; l= .0        }
   else If K==  7114 { i=300; c='SIGML*D-'; m=100.77    ; l= .0        }
   else If K==  7324 { i=301; c='CASCL*0 '; m=100.97    ; l= .0        }
   else If K==  7314 { i=302; c='CASCL* -'; m=100.97    ; l= .0        }
   else If K==  7334 { i=303; c='OMEGL* -'; m=101.17    ; l= .0        }
   else If K==  7424 { i=304; c='LCU*   +'; m=101.97    ; l= .0        }
   else If K==  7414 { i=305; c='LCD*0   '; m=101.97    ; l= .0        }
   else If K==  7434 { i=306; c='LCS*0   '; m=102.17    ; l= .0        }
   else If K==  7444 { i=307; c='LCC*   +'; m=103.17    ; l= .0        }
   else If K==  8222 { i=316; c='SIGMH 2+'; m=160.57    ; l= .0        }
   else If K==  8212 { i=317; c='SIGMH  +'; m=160.57    ; l= .0        }
   else If K==  8122 { i=318; c='LAMBH  +'; m=160.37    ; l= .0        }
   else If K==  8112 { i=319; c='SIGMH0  '; m=160.57    ; l= .0        }
   else If K==  8322 { i=320; c='CASCH  +'; m=160.77    ; l= .0        }
   else If K==  8232 { i=321; c='CASCHP +'; m=160.97    ; l= .0        }
   else If K==  8312 { i=322; c='CASCH0  '; m=160.77    ; l= .0        }
   else If K==  8132 { i=323; c='CASCHP0 '; m=160.97    ; l= .0        }
   else If K==  8332 { i=324; c='OMEGH0  '; m=161.17    ; l= .0        }
   else If K==  8422 { i=325; c='HCU   2+'; m=161.50    ; l= .0        }
   else If K==  8242 { i=326; c='HCUP  2+'; m=161.70    ; l= .0        }
   else If K==  8412 { i=327; c='HCD    +'; m=161.50    ; l= .0        }
   else If K==  8142 { i=328; c='HCDP   +'; m=161.70    ; l= .0        }
   else If K==  8432 { i=329; c='HCS    +'; m=161.80    ; l= .0        }
   else If K==  8342 { i=330; c='HCSP   +'; m=162.      ; l= .0        }
   else If K==  8442 { i=331; c='HCC   2+'; m=162.50    ; l= .0        }
   else If K==  8224 { i=332; c='SIGMH*2+'; m=160.77    ; l= .0        }
   else If K==  8214 { i=333; c='SIGMH* +'; m=160.77    ; l= .0        }
   else If K==  8114 { i=334; c='SIGMH*0 '; m=160.77    ; l= .0        }
   else If K==  8324 { i=335; c='CASCH* +'; m=160.97    ; l= .0        }
   else If K==  8314 { i=336; c='CASCH*0 '; m=160.97    ; l= .0        }
   else If K==  8334 { i=337; c='OMEGH*0 '; m=161.17    ; l= .0        }
   else If K==  8424 { i=338; c='HCU*  2+'; m=161.97    ; l= .0        }
   else If K==  8414 { i=339; c='HCD*   +'; m=161.97    ; l= .0        }
   else If K==  8434 { i=340; c='HCS*   +'; m=162.17    ; l= .0        }
   else If K==  8444 { i=341; c='HCC*  2+'; m=163.17    ; l= .0        }
   else If K== 10441 { i=163; c='CHIC01P '; m=3.4151    ; l= .48760e-22}
   else If K== 10443 { i=164; c='CHIC11P '; m=3.5106    ; l= .50630e-21}
   else If K== 10551 { i=202; c='CHIB01P '; m=9.8598    ; l= .0        }
   else If K== 10553 { i=203; c='CHIB11P '; m=9.8919    ; l= .0        }
   else If K== 10661 { i=245; c='CHIT01P '; m=119.13    ; l= .12500e-20}
   else If K== 10663 { i=246; c='CHIT11P '; m=119.13    ; l= .12500e-20}
   else If K== 20443 { i=161; c='PSI2S   '; m=3.6860    ; l= .27090e-20}
   else If K== 30443 { i=162; c='PSI3S   '; m=3.7699    ; l= .26020e-22}
   else If K== 20113 { i=133; c='A10     '; m=1.2620    ; l= .16920e-23}
   else If K==-20213 { i=134; c='A1     -'; m=1.2620    ; l= .16920e-23}
   else If K== 20663 { i=241; c='THET2S  '; m=119.23    ; l= .13540e-20}
   else If K== 30663 { i=242; c='THET3S  '; m=119.62    ; l= .0        }
   else If K== 40663 { i=243; c='THET4S  '; m=119.85    ; l= .0        }
   else If K== 50663 { i=244; c='THET5S  '; m=120.02    ; l= .0        }
   else If K== 20553 { i=198; c='YPSI2S  '; m=10.023    ; l= .14960e-19}
   else If K== 30553 { i=199; c='YPSI3S  '; m=10.355    ; l= .25320e-19}
   else If K== 40553 { i=200; c='YPSI4S  '; m=10.580    ; l= .27660e-22}
   else If K== 50553 { i=201; c='YPSI5S  '; m=10.865    ; l= .59840e-23}
}}
*  Apply charge conjugation:
   CPNAM=c; PMASS=m; PCHAR=Q*sign(1,IDpdg); if (i==0) ier=1
*
 END
 
 
 
 
 
 
 
 
 
 
 
 
 
*CMZ :  1.30/00 15/04/97  21.39.26  by  Pavel Nevski
*-- Author :    Pavel Nevski   21/07/96
************************************************************************
       Subroutine    A g B E A M D A T
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
Integer Iarray(10000), Lbuff/10000/, Lsize, num(5)
Integer itit(100,5),ICntr,ICnts,Ndet,id,ITR,Idet,ld,Jdet,JCntr,JCnts,Ldet
Integer Nsub,is,JTR,Jsub,Lsub,Lab,ls,KCntr,KCnts,Nsss,KTR,Ksss,j,iz,
        larea,lf,LLast,N,Lt,Iprin/0/,ISLFLAG,L
common /beamLINK/ Larea(2),Lf,Ld,Ls,LLast
Character*4  cform/'-I'/
 
Call  MZLINT(IxSTOR,'beamLINK',Larea,Lf,LLast)
Lf=LkARAW; N=1; Iprin=max(Idebug+1,Islflag('INPU','RECO'));
Check LkARAW>0
Lsize=0
" get general event header, pointers to control and data (detector list)"
 ICntr=IQ(lf+9);   ICnts=IQ(lf+10);
 Lt=11; If (Icntr>0) Lt=min(11+IQ(lf+ICntr+1),100)
 Call UCOPY(IQ(lf+1),Itit(1,1),Lt);
 num(1)=1; num(2)=N; call RBSTORE('/RECB/RAWH',num,Cform,Lt,Itit(1,1))
"      top data block: number of detectors and their id+pointers        "
Check Icnts>0
Ndet = IQ(lf+ICnts+1)
 
Do id=1,2*NDet,2
{ ITR =IQ(lf+ICnts+1+id);  " pointer to the detector block "
  Idet=IQ(lf+ICnts+2+id);  " it's identificator  "
  Prin5 IDet,ITR;  (' AgBEAMdat: Found detector Idet=',i5,' at pointer ',i5)
 
  "  get into the detector header "  ld=lf+ITR; Jdet=max(1,Idet/1000)
  JCntr=IQ(ld+9);  JCnts=IQ(ld+10);  Ldet=IQ(ld+2)
  Lt=11; If (Jcntr>0) Lt=min(11+IQ(ld+JCntr+1),100)
  Call UCOPY(IQ(ld+1),Itit(1,2),Lt)
  num(3)=Jdet; call RBSTORE('/RECB/RAWH/DETE',num,Cform,Lt,Itit(1,2))
 
  check Jcnts>0;
  Nsub=IQ(ld+Jcnts+1);  Do is=1,2*Nsub,2
  { JTR =IQ(ld+JCnts+1+is);  " pointer to the subdetector block "
    Jsub=IQ(ld+JCnts+2+is);  " it's identificator  "
    Lsub=IQ(ld+JTR+1);        " subdet info length  "
    Lab =IQ(ld+JTR+2);        " suddet label   "
    If Jsub<1000
    { Prin1 Jsub,JTR,Lsub,Lab
      (' AgBEAMdat: bad detector Isub=',i6,' at pointer',i6,
       ' Len=',i6,' label',i6);  next;
    }
    if Lsub<Ldet
    { Prin5 Jsub,JTR,Lsub,Lab
      (' AgBEAMdat: Found subdetec Isub=',i6,' at pointer',i6,
       ' Len=',i6,' label',i6)
        Lsize=Lsub-2;  If Lsize>Lbuff
        { prin0 lab,Lsize,Lbuff
         (' Insufficient length of user array for subdet block',i8,/,
          ' Length=',i8,' available size=',i8,' the rest will be lost')
        }
        L=min(Lsize,Lbuff);  Call Ucopy(IQ(ld+JTR+3),Iarray,L);  num(4)=Jsub;
        Prin8 Lsub, Lab, (IQ(ld+JTR+2+j),j=1,L)
              (' AgBEAMdat: Raw data: size, ID=',2i6/(10z9))
        call RBSTORE('/RECB/RAWH/DETE/SUBD',num,Cform,L,Iarray)
    }
    else   " detector with  subsubdivisions - not tested "
    { Prin5 Jsub,JTR
      (' AgBEAMdat: Found subsystem Jsub=',i5,' at pointer',i5)
      " get into the subdet header "  ls=ld+JTR
      Call UCOPY(IQ(ls+1),Itit(1,3),8); KCntr=IQ(ls+9); KCnts=IQ(ls+10)
      num(4)=Jsub;
      call RBSTORE('/RECB/RAWH/DETE/SUBA',num,Cform,8,Itit(1,3))
 
      Nsss=IQ(ls+KCnts+1)
      Do iz=1,2*Nsss,2
      { KTR =IQ(ls+KCnts+1+iz);  " pointer to the subsubdet block "
        Ksss=IQ(ls+KCnts+2+iz);  " it's identificator  "
        Lsub=IQ(ls+KTR+1);       " subdet info length  "
        Lab =IQ(ls+KTR+2);       " suddet label        "
        If Ksss<1000 | Ksss!=Lab
        { Prin1 Ksss,KTR,Lsub,Lab
          (' AgBEAMdat: bad subdetec Isub=',i5,' at pointer',i5,
           ' Len=',i5,' label',i5);  next;
        }
        Lsize=Lsub-2; Prin5 Ksss,KTR,Lsize,Lab
        (18x,'subsubdet Isub=',i5,' at pointer',i5,'  Len=',i5,' label',i5)
        If Lsize>Lbuff
        { <w> Ksss,Lbuff,Lsize
          (' Insufficient length of user array for subsubdetector block',i6/,
          ' User array length',i6,' block length',i6,' the rest will be lost')
        }
        L=min(Lsize,Lbuff); Call Ucopy(IQ(ls+KTR+3),Iarray,L); num(5)=Lab;
        Prin8 Lsub, Lab, (IQ(ls+KTR+2+j),j=1,L)
        (' AgBEAMdat: Raw data: size, ID=',2i6/(10z9))
        call RBSTORE('/RECB/RAWH/DETE/SUBA/SUBD',num,Cform,L,Iarray)
} } } }
larea(1)=0; Iquest(1)=0
End
 
*CMZ :  1.30/00 27/07/96  15.41.07  by  Pavel Nevski
*-- Author :    Pavel Nevski   27/07/96
************************************************************************
                SUBROUTINE   A G R E I N I T
*                                                                      *
* description: after a new JVOLUME and DETM structures are read        *
* get rid of traces of old job: drop DETP banks, clear read-done flag  *
* reset jump pointers because thay are not valid anymore               *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
  Integer IdetP,Idet,Ldet,Ib,Lb
 
  Call UCTOH('DETP',IdetP,4,4)
*
  If LkDETM>0
  {  Call MZFLAG(IxSTOR,LkDETM,1,'Z')
     Do Idet=1,IQ(LkDETM-2)
     {  * clean up SIMU and RESA - no jumps are defined
        Ldet=LQ(LkDETM-Idet);  Check Ldet>0;  Check IQ(Ldet-1)>=13
        "IRESA" IQ(Ldet+13)=0;        "ISIMU" IQ(Ldet+7) =0
 
        * drop DETP banks
        Do Ib=1,IQ(Ldet-2)
        {  Lb=LQ(Ldet-Ib);     Check Lb>0;    Check IQ(Lb-4)==IdetP
           CALL MZDROP(IxStor,Lb,' ');  Break;
  }  }  }
  call GGCLOS
  End
*CMZ :          05/08/98  23.16.13  by  Pavel Nevski
*CMZ :  1.30/00 02/05/97  17.21.14  by  Pavel Nevski
*-- Author :    A. Rozanov  11/03/95
******************************************************************************
*                                                                            *
                   Subroutine  A G Z K I N E
*                                                                            *
* Description: Read or Generate Kinematics for primary tracks (new version)  *
* This routine understands the KINE card in the following format (a la SLUG) *
* KINE IKINE part pmin pmax etamin etamax phimin phimax gmode zmin zmax      *
*   - if IKINE=0 and gmode=0                                                 *
*                px,py,pz and z are generated randomly according to          *
*                pmin-pmax, etamin-etamax, phimin-phimax, zmin-zmax ranges   *
*   -  . . . .   gmode=1 - same, but pt-range is assumed instead of E-range  *
*   - if IKINE=-1                                                            *
*                FZ file opened on unit 21 is used as input (GNZ format)     *
*                If not opened previously with AgZOpen, ZEBRA.P is opened    *
*   - if IKINE=-2                                                            *
*                a hbook file with a CWN (on unit 20) is used as an input    *
*                If not opened previously with AgNTopen, hcwn.hbook is used  *
******************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     Integer  Ier,Iev,CsADDR,J,L
     Real     Undf/9.e9/
*
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     IF (NtrSubEV>0 & IsubEVNT<NsubEvnt) Go to :splitted:
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
* prepare AgCKINE/VERT parameters here, because they may be common for all KINE
*
     If Pkine(1)<Undf  { PType =    Pkine(1)         }  else  { Ptype = 0    }
     If Pkine(2)<Undf  { PtMin =max(Pkine(2),0.)     }  else  { PtMin = 0    }
     If Pkine(3)<Undf  { PtMax =max(Pkine(3),Ptmin)  }  else  { PtMax = 99999}
     If Pkine(4)<Undf  { EtaMin=max(Pkine(4),-10.)   }  else  { EtaMin=-10   }
     If Pkine(5)<Undf  { EtaMax=min(Pkine(5),+10.)   }  else  { EtaMax=+10   }
     If Pkine(6)<Undf  { PhiMin=max(Pkine(6),-TwoPi) }  else  { PhiMin= 0    }
     If Pkine(7)<Undf  { PhiMax=min(Pkine(7), TwoPi) }  else  { PhiMax= TwoPi}
     If Pkine(8)<Undf  { Ptflag=    Pkine(8)         }  else  { Ptflag= 0    }
     If Pkine(9)<Undf  { ZMin  =max(Pkine(9),-10000.)}  else  { ZMin  =-10000}
     If Pkine(10)<Undf { ZMax  =min(Pkine(10),10000.)}  else  { ZMax  = 10000}
*   Fixed target version
     If Pkine(2)<Undf  { Pxmin =max(Pkine(2),-10000.)}  else  { Pxmin  = -1 }
     If Pkine(3)<Undf  { Pxmax =max(Pkine(3),Pxmin)  }  else  { Pxmax  =  1 }
     If Pkine(4)<Undf  { Pymin =max(Pkine(4),-10000.)}  else  { Pymin  = -1 }
     If Pkine(5)<Undf  { Pymax =max(Pkine(5),Pymin)  }  else  { Pymax  =  1 }
     If Pkine(6)<Undf  { Pzmin =max(Pkine(6),-10000.)}  else  { Pzmin  = -1 }
     If Pkine(7)<Undf  { Pzmax =max(Pkine(7),Pzmin)  }  else  { Pzmax  =  1 }
*
*get event:
* initialise data file - when called directly be user, these routines should
* reset IKineOld to prevent file name redifinition to defaults
*
      If (IKINE!=IKineOld) then
         If (IKine > 0) IKineOld = Ikine
         If (IKine==-1) Call AgZOPEN (' ', ' ', '*', 0,0)
         If (IKine==-2) Call AgNTOPEN('hcwn.hbook' ,  4 )
         If (IKine==-3) Call AgFOPEN ( 0,  ' ',      ier)
         If (IKine<=-4) { J=CsADDR('AGUSOPEN'); IkineOld=Ikine;
                          If (J>0) Call CSjCAL1S(J,' ') }
      endif
*
      Ier   = 0
*     If (Idebug>0)     Itest=max(Itest,1)
      If  IKINE >0      { Do iev=1,IKINE { Call AgSPkine } }
      If (IKineOld==-1) call AgPread (ier)
      If (IKINEold==-2) call AgNTread(ier)
      If (IKINEold<=-3) call AgFread (ier)
      If (IKINEold<=-4)
      { J=CsADDR('AGUSREAD'); If (J>0) Call CSjCAL(J,1,Ier,0,0,0,0,0,0,0,0,0) }
        J=CsADDR('AGUKINE');  If (J>0) Call CSjCAL(J,1,Ier,0,0,0,0,0,0,0,0,0)
*
      If  ier!=0  { Ikineold=0; Ieotri=1; Iquest(1)=Ier; Return; }
*
      If NtoSKIP>0
      { if (IDEBUG>0) <w> Ievent,Idevt; (' AGZKINE event ',2i7,' is skipped ')
        NtoSKip-=1; Ieotri=1; Return;
      }
*
      If (IBackOld==-1)           Call AgZback
      L=max(Alog10(1.+NVERTX),Alog10(1.+NTRACK))
      If (Idebug>L & JVertx>0)    Call GPVERT(0)
      If (Idebug>L & Jkine >0)    Call GPKINE(0)
      NsubEvnt=-1
*
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
:splitted:        Check NtrSubEV>0
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*     count subevents from one, first is always event generator info only
      If NsubEvnt==-1  { NsubEvnt=(NTRACK-1)/NtrSubEv+2; IsubEvnt=0;
*                        Call GSVERT(VertexNow,0,0,0,0,Nv)
                       }
      IsubEvnt+=1;  Call AgSPLIT(NtrSubEv,ier)
      If (Ier!=0) <w> IsubEvnt,NsubEvnt;
      (' AgSPLIT track counting wrong in sub-event',i4,' out of',i4)
      IF (IsubEvnt > 1)         "not first - for Identity"  Idevt  -= 1
      IF (IsubEvnt!=NsubEvnt)   "not last  - for counting"  Ievent -= 1
*
*     set header bank
      If Jhead>0       { IQ(JHEAD+5)=NsubEvnt; IQ(JHEAD+6)=IsubEvnt; }
      return
END
 
 
*CMZ :          30/07/97  16.14.22  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  22.56.50  by  Pavel Nevski
*-- Author :    Pavel Nevski
**************************************************************************
                SUBROUTINE   A g E Z K I N E   (Iprin)
* Description: routine for feeding EGZ information into GEANT.           *
* Note the use of TOFG in common GCTRAK, set before Calls to GSVERT,     *
* to store the correct time of the vertices.                             *
* Iprin is defined as Idebug+1 in AGZREAD                                *
**************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
    Character Cname*4,Gname*8,Gnamo*8/' '/
    Real      evtver,zproj,aproj,ztarg,atarg,sqrts,bmin,bmax,bimevt,
              plab(4),UBUF(100),VERT(4)/4*0/
    Integer   Iprin,L,i,nptls,nptarg,nntarg,npproj,nnproj,ntry,
              IdPtl,IoPtl,IC,Ipart,NVTX,Nt,part_size/6/,Nu/0/
*
*     generator run header
      check   LKRUNT>0;    call UHTOC(IQ(LKRUNT-4),4,CNAME,4)
      check  "bank length" IQ(LKRUNT-1)>=10 & "name" CNAME=='CODE'
*
      call UHTOC(IQ(LKRUNT+1),4,Gname,8)
      evtver  = Q(LKRUNT+3)
      zproj   = Q(LKRUNT+4)
      aproj   = Q(LKRUNT+5)
      ztarg   = Q(LKRUNT+6)
      atarg   = Q(LKRUNT+7)
      sqrts   = Q(LKRUNT+8)
      bmin    = Q(LKRUNT+9)
      bmax    = Q(LKRUNT+10)
      If Gname!=Gnamo
      { Prin1 Gname,evtver,zproj,aproj,ztarg,atarg,sqrts,bmin,bmax
        (' AgEZKINE: generator ',a8,' version ',f8.3/10x,
        ' beam z/a',2f5.0,' target a/z',2f5.0,' sqrt(s)=',f6.1,' b=',2f8.3)
      }
          Gnamo=Gname;                       IC=0
      If (Gname='VENUS'  | Gname='HIJET')    IC=1
      If (Gname='HIJING')                    IC=2
      If (Gname='FRITIOF'| Gname='FRTIOF17') IC=3
      If (IC==0) <w> Gname; (' AgEZKINE error: unknown event generator ',a)
 
*     Normal event following
      Check   LKEVNT>0;    Call UHTOC(IQ(LKEVNT-4),4,CNAME,4)
      check  "bank length" IQ(LKEVNT-1)>=7 & "name" CNAME=='EVEN'
 
*     Do leading part of bank
      nptls   = IQ(LKEVNT+1)
      nptarg  = IQ(LKEVNT+2)
      nntarg  = IQ(LKEVNT+3)
      npproj  = IQ(LKEVNT+4)
      nnproj  = IQ(LKEVNT+5)
      ntry    = IQ(LKEVNT+6)
      bimevt  =  q(LKEVNT+7)
      Call aGSVERT(VERT,0,0,Ubuf,Nu,Nvtx)
      prin3 nptls,npproj,nnproj,nptarg,nntarg,ntry,bimevt
      (' AgEZKINE: setting GEANT vertex with Npart=',i6,' (before filter)'/,
        10x,' beam p/n=',2i5,'  targ p/n=',2i5,'  ntry=',i6,'  b=',f8.3)
 
*     Do trailing part of bank:  ID, 4-momentum, daughter/parent information
      do i=1,nptls
         L=LKEVNT+7+(i-1)*part_size
         Ipart    =  0
         Idptl    = IQ(L+1)
         plab(1)  =  Q(L+2)
         plab(2)  =  Q(L+3)
         plab(3)  =  Q(L+4)
         plab(4)  =  Q(L+5)
         ioptl    = IQ(L+6)
         If (Ic==1) Call ISA_to_GEANT    (IdPtl,Ipart)
*        If (Ic==2) Call HIJING_to_GEANT (IdPtl,Ipart)
         If (Ic==2) Call a PDG 2 GEA     (IdPtl,Ipart)
         If (Ic==3) Call LUND_to_GEANT   (IdPtl,Ipart)
         If Ipart<=0
         {  Prin2 IdPtl,Gname;
            (' AgEZKine: particle code ',i6,' from ',A,' is unknown ')
            Next
         }
         CALL aGSKINE (Plab,Ipart,NVTX,Ubuf,Nu,Nt)
      enddo
*
    prin2 Ntrack,Nvertx;
         (' AgEZKINE: # of particles in GEANT=',I6,' # of VERTEX',I6)
*
    END
 
 
*CMZ :  1.30/00 12/03/97  13.19.34  by  Pavel Nevski
*-- Author :
******************************************************************
      SUBROUTINE HIJING_TO_GEANT(LUID,GEID)
*                                                                *
*  Subroutine to convert HIJING (PDG) id's to GEANT ID's         *
*                                                                *
*  Author:    Richard Morse  LBL (510)-486-6349                  *
*  Modified:  9 May 1995 Matt Bloomer                            *
*      - extended GLTBLE to include Delta resonances.            *
*      - Fixed bug: GEID -> LUID in neutrino IF statement.       *
******************************************************************
      implicit  none
      INTEGER   IUCOMP, LUID, GEID, NUMID
      PARAMETER (NUMID=75)
      INTEGER   GLTBLE(1:NUMID)
*
      DATA GLTBLE/   22,  -11,   11,   12,  -13,
     +               13,  111,  211, -211,  130,
     +              321, -321, 2112, 2212,-2212,
     +              310,  221, 3122, 3222, 3212,
     +             3112, 3322, 3312, 3334,-2112,
     +            -3122,-3112,-3212,-3222,-3322,
     +            -3312,-3334,  -15,   15,  411,
     +             -411,  421, -421,  431, -431,
     +             4122,   24,  -24,   23,    0,
     +                0,    0,    0,  223,  333,
     +              113,  213, -213,  411,  421,
     +             1114, 2114, 2214, 2224,    0,
     +                1,   -1,    2,   -2,    3,
     +               -3,    4,   -4,    5,   -5,
     +                6,   -6,    21, -21,    0/
*
      GEID=IUCOMP(LUID,GLTBLE,NUMID)
*
*     We must map all neutrinos onto a single ID...
      IF (ABS(LUID)==12 | ABS(LUID)==14 | ABS(LUID)==16) GEID=4
*
      End
 
*CMZ :  1.30/00 12/03/97  13.19.34  by  Pavel Nevski
*-- Author :
*********************************************************************
      subroutine isa_to_geant(isa,id)
*                                                                   *
*  translates isa (isajet particle code) to id (geant code)         *
*  Author: Tom Throwe, bnl                                          *
*  Correction: PN, 2/26/97 isa was overwritten                      *
*********************************************************************
      implicit  none
      integer   IUCOMP,isa,id,isacod(44)
      data isacod/10,  -12,   12,   11,  -14,   14,
     +           110,  120, -120,  -20,  130, -130,
     +          1220, 1120,-1120,   20,  220, 2130,
     +          1130, 1230, 2230, 1330, 2330, 3331,
     +         -1220,-2130,-1130,-1230,-2230,-1330,
     +         -2330,-3331,  -16,   16, -240,  240,
     +          -140,  140, -340,  340, 2140,   80, -80, 90/
*
      ID=IUCOMP(ISA,isacod,44)
*
* special cases: different types of neutrino are all neutrino, anti-pi0 is pi0
      If (abs(isa)==11 | abs(isa)==13 | abs(isa)==15)  Id = 4
      If (isa==-110)                                   Id = 7
*
      end
 
 
 
*CMZ :  1.30/00 19/03/97  15.33.37  by  Pavel Nevski
*-- Author :
*     =========================================
      subroutine lund_to_geant(lund_id,geant_id)
*     ==========================================
      implicit none
      integer lund_id, geant_id, numid, i
      parameter (numid=41)
      integer lundid_table(numid),gltble(-100:100), jantid(numid)
      logical first/.true./
*
      data lundid_table /
     +     1, -7,  7,  8, -8, -9,  9, 10,-10, 12,-12, 17,-17,
     +     18,-18, 37, 38, 41,-41, 42,-42, 43,-43, 45,-45, 46,-46,
     +     47,-47, 57,-57, 70,-70, 11,-11, 44,-44, 24,-24, 23,-23/
      data jantid/
     +     1,  2,  3,  4,  4,  5,  6,  4,  4,  4,  4,  8,  9,
     +     11, 12, 16, 10, 14, 15, 13, 25, 19, 29, 21, 27, 22, 30,
     +     23, 31, 18, 26, 24, 32, 34, 33, 20, 28, 17, 17,  7,  7/
 
 
      if (first) then
*     make lund to geant code lookup table
          do i=-100,100
              gltble(i)=0
          end do
          do i=1,numid
              gltble(lundid_table(i))=jantid(i)
          end do
          first = .false.
      end if
 
*     convert the type
      if(ABS(lund_id) .le. 100) then
          geant_id = gltble(lund_id)
      else
          geant_id = 0
      endif
*
      end
 
*CMZ :  1.30/00 21/03/97  12.42.58  by  Pavel Nevski
*-- Author :    Pavel Nevski   16/03/97
      SUBROUTINE   AGNEED (IER)
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
      Integer      Ier,LSTACK,NNEW,IPRIN
 
      Ier  = IEOTRI
      If (IER.NE.0) RETURN
      Iprin=IDEBUG
 
      LSTACK=0;  IF (JSTAK>0) LSTACK=IQ(JSTAK-1)
      NNEW = 500+max(NTRACK,NVERTX,LSTACK)
      Call MZNEED(IXDIV,NNEW,'G');  CHECK IQUEST(11)<0
*     Iswit(9)-=1; if (Iswit(9)<0) return
*
      Call MZGARB(2,0);  CALL MZGARB(20,0);  Call MZDRED(20);
      prin2;  (' ***** AGNEED compression done *****')
      Call MZNEED(IXDIV,NNEW,'G');  CHECK IQUEST(11)<0
 
      prin0  ABS(IQUEST(11)),NNEW
      (' ***** AgNEED: Not enough memory for KINE/VERT/STACK *****'/,
       ' ***',  I9, ' words short in relocating',  I9, ' words ***'/,
       ' ************** event simulation abandoned ***************')
      IQUEST(1) = 0
      IEOTRI    = 1
      IER       = 1
      end
 
*CMZ :  1.30/00 24/04/97  20.12.49  by  Pavel Nevski
*-- Author :    Pavel Nevski   22/03/97
***************************************************************************
     FUNCTION LgKINE (JO,I)
* Description: return Link to the t-th track in LgKINE and Link           *
*              to its mother bank (in JKINE linear chain) in J0           *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
     Integer  LgKINE,I,J,JO,NF
*
     LgKine=0; j=JKINE; JO=j; NF=IQ(j+2)
     while  0<j&j<NZEBRA
     { JO=J; If NF==0
       { If      I >IQ(j+1) "move right" {  J=LQ(J)  }
         else If I<=IQ(j+2) "move left"  { J=LQ(J+2) }
         else    {  LgKINe=LQ(j-I+IQ(j+2));  Return  }
       }
       else
       { If      I<=IQ(j+2) "move right" {  J=LQ(J)  }
         else    {  LgKINe=LQ(j-I+IQ(j+2));  Return  }
     } }
*      Print *,' LgKINE error - track ',I,' not found'
     END
 
*CMZ :  1.30/00 31/03/97  21.39.29  by  Pavel Nevski
*-- Author :    Pavel Nevski
****************************************************************************
         SUBROUTINE   A G C H A I N (MaxHITS,MaxKINE)
*                                                                          *
* Description: If length of the HITS or KINE structures is more than       *
*        the maximum a new bank is chained at the corresponding link.      *
*        For hits this is transparent for hit storing routines             *
*        For KINE a special versions of GSVERT/GSKINE should be used       *
*        otherwise no action is taken                                      *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCPUSH.
      COMMON/GCPUSH/NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
      INTEGER       NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
C
*KEND.
      Integer  MaxHits,MZVOLM,Nw,Nset,Iprin,MAXKINE
*
      IPRIN=IDEBUG
      IF JKINE>0
      {  IF IQ(JKINE-1)>1 & NTRACK-IQ(JKINE+2)>=MAXKINE
         {  CALL MZBOOK(IXDIV,JKINE,JKINE,1,'KINE',NCKINE,NCKINE,2,2,0)
            IQ(JKINE+2)=NTRACK;
            Prin2 NTRACK,IQ(JKINE-5)
            (' AGCHAIN: after',i8,' tracks new KINE bank chained at ID=',i3)
      }  }
*
      IF JHITS>0 & JSET>0
      {  NW=MZVOLM(IxDIV,JHITS,' ')
         IF NW>MaxHITS
         {  CALL GRLEAS(JHITS); NSET=IQ(JSET-2)
            CALL MZBOOK(IXDIV,JHITS,JHITS,1,'HITS',NSET,NSET,0,2,0)
            Prin2 NW,IQ(JHITS-5)
            (' AGCHAIN: HITS bank size=',i9,'  new bank chained at ID=',i3)
      }  }
      END
 
 
*CMZ :          11/12/97  00.29.35  by  Pavel Nevski
*CMZ :  1.30/00 03/04/97  13.58.50  by  Pavel Nevski
*-- Author :    Pavel Nevski   31/03/97
***************************************************************************
                subroutine A G S P L I T (N0,Ier)
*                                                                         *
* Description: If KINE bank contains too many tracks, event is splitted   *
*              into a number of smaller events with exactly N0 tracks     *
*              First guess for the algorithm, may be done better          *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
   integer itr1,itr2,itr,jtr,it,iv,jv,Lk,Lv,Nt
   Integer IDN,N0,Ier,IsubEV/-1/,Iprin,NTRA,NVER
 
 Ier=-1; Check  N0>0;
 Iprin=Idebug; NTRACK=0; NVERTX=0;
 IF JVERTX>0 & JKINE>0
 { IDN=IQ(JVERTX-5); If IDN==0
   {  If (LKAGEV>0) Call MZDROP (IxSTOR,LKAGEV,   'L')
      CALL MZGARB (IxDiV,0)
      Call MZCOPY (IxDIV,JVERTX, IxCONS,LKAGEV, 1,' ')
      call MZCOPY (IxDIV,JKINE,  IxCONS,LKAGEV, 0,'L')
      IQ(LKAGEV-5)=-1;  IQ(LQ(LKAGEV)-5)=-1
      call MZDROP(IxSTOR,JVERTX,'L')
      call MZDROP(IxSTOR,JKINE ,'L')
      IsubEv=0; Ier=0;  GOTO :e:
 } }
 
 If LKAGEV>0
 { IsubEv += 1;
   If (JVERTX>0) call MZDROP(IxSTOR,JVERTX,'L')
   If (JKINE >0) call MZDROP(IxSTOR,JKINE ,'L')
   Call MZCOPY (IxCONS,LKAGEV,     IxDIV,JVERTX, 1,' ')
   call MZCOPY (IxCONS,LQ(LKAGEV), IxDIV,JKINE,  1,'L')
   IQ(JVERTX-5)=1;      IQ(JKINE -5)=1
   NVER=IQ(JVERTX+1);   NTRA=IQ(JKINE+1)
*
     itr1=N0*(IsubEV-1)+1;  itr2=min(N0*IsubEV,NTRA)
     if Itr1>Itr2 { Call MZDROP(IxSTOR,LKAGEV,  'L'); ier=1; GOTO :e: }
*
     do iv=1,NVER
     {  Lv=LQ(JVERTX-Iv);  Check Lv>0;  Call VZERO (Q(7+Lv),IQ(Lv-1)-6) }
*
     jtr=0; do itr=1,NTRA
     {  "===>"    if itr1<=itr&itr<=itr2   "<==="
        {  Lk=LQ(JKINE-itr);  check Lk>0;  Jtr+=1
           call ZSHUNT(IxSTOR,Lk,JKINE,-jtr,0)
           Iv=Q(6+Lk);   Lv=LQ(JVERTX-Iv)
           Nt=Q(7+Lv)+1; Q(7+Lv)=Nt;  Q(7+Lv+Nt)=jtr
        }
        else    { Call MZDROP(IxSTOR,LQ(JKINE-itr),' ') }
     }
*
     jv=0; do iv=1,NVER
     {  Lv=LQ(JVERTX-Iv);  Check Lv>0;  Nt=Q(7+Lv)
        If Nt>0  { jv+=1; Do itr=1,Nt { it=Q(7+Lv+itr); Q(6+LQ(JKINE-it))=jv }
                   Call ZSHUNT(Ixstor,Lv,JVERTX,-jv,0)
                 }
        else     { call MZDROP(IxSTOR,LQ(JVERTX-iv),' ') }
     }
     Ntrack=jtr; IQ(JKINE+1)=Jtr; NVERTX=Jv; IQ(JVERTX+1)=Jv; Ier=0
   }
:e:; PRIN1 IsubEv,Idevt,Nvertx,Ntrack
     (3x,'** GSPLIT: subevt=',i7,' idevt=',i7,' Vertex/Track =',i11,i12)
   end
 
 
 
*CMZ :          31/10/97  13.01.26  by  Pavel Nevski
*CMZ :  1.30/00 02/04/97  17.34.39  by  Pavel Nevski
*-- Author :    A. Rozanov  11/03/95
**********************************************************************
                Subroutine  A G S P K I N E
* Description:  Generates Kinematics for primary track               *
*    PtFlag:  <---collider mode--->   <-----fix target----->         *
*             <pdg>   <---geant--->   <-pdg->  <---geant--->         *
*             0   1   2 . . . . . 9   10   11  12 . . . . 20         *
*             E  PT........................................>         *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
     REAL     Theta,Eta,Phi,Etot,Ptot,PT,P(3),vertex(4),RNDM
     integer  NVRT,NTRK,IParti
*
*  collider or fixed target datacard...         Ilia Iliych:
     if (ptflag<10) then                  "    collider mode     "
        Eta    = EtaMin+RNDM(-1.)*(EtaMax-EtaMin)
        Phi    = PhiMin+RNDM(-1.)*(PhiMax-PhiMin)
        etot   = PtMin +Rndm(-1.)*(PtMax - PtMin)
        Theta  = 2*ATAN(EXP(-Eta))
        If (ptflag==0)  { Ptot = Etot;    PT   = Ptot*SIN(Theta) }
        else            { PT   = Etot;    Ptot = PT / SIN(Theta) }
        P      = { PT*Cos(Phi), PT*Sin(Phi), PTOT*COS(Theta) }
     else                                 "  Fixed target mode   "
        P      = { Pxmin+RNDM(-1.)*(Pxmax-Pxmin),
                   Pymin+RNDM(-1.)*(Pymax-Pymin),
                   Pzmin+RNDM(-1.)*(Pzmax-Pzmin) }
     endif
*
     IParti = nint(ptype)                                            " *star "
     If (mod(nint(ptflag),10)<=1) Call aPDG2GEA (nint(ptype),IParti) " atlas "
*
     If (Iparti==0) "replace by muon"  Iparti=6
     Call VZERO   (vertex,4)
     Call aGSVERT (vertex, 0, 0, 0.,0,NVRT)
     Call aGSKINE (P,IParti,NVRT,0.,0,NTRK)
END
 
 
*CMZ :          24/03/98  12.52.35  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/06/97
***************************************************************************
                Subroutine  A G S K I N E (Plab,Iparti,Nv,UB,NB,Nt)
* Description:                                                            *
*              Save tracks in GEANT KINE bank                             *
***************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
   Real     ARGUM,Vertex(4),Plab(3),UB(*)
   Integer  Iparti,Nv,NB,Nt,Id/0/,Iprin,Irc,JV,IV
 
      Iprin=Idebug;      Check JVERTX>0;
      Jv=0; IF (1<=NV & NV<=IQ(JVERTX-2)) Jv=LQ(JVERTX-Nv)
      if Jv<=0 { prin1 NV; (' aGSKINE: Vertex',I8,' does not exist'); return }
      Call UCOPY(Q(JV+1), Vertex, 4);     Irc=0;
 
      If (IKINE<=0) Call AgGZUFLT('AGSKINE',Ievent,Iparti,Id,vertex,Plab,Irc)
      If irc != 0
      {  prin4 Iparti,Plab,Irc
         (' AgSKINE: particle',i5,' Plab=',3f10.3,' rejected by filter',i3)
         return
      }
      Call GSKINE (Plab,IPARTI,Nv,UB,NB,Nt); IV=ARGUM(UB)
      if nt>0 & NB==0 { IQ(LQ(JKINE-Nt)-5)=IV }
      if nt <= 0 { Prin1 Iparti,IV; (' AgSKINE: unknown geant iv,id: ',2i6) }
   END
 
 
*CMZ :          28/07/97  20.58.07  by  Pavel Nevski
*-- Author :    Pavel Nevski   18/07/97
*************************************************************************
   subroutine   A g F O P E N (li,file,ier)
*
* Description: open a standard fortran formattted data file.            *
*************************************************************************
   Implicit   None
   Integer    LENOCC,Li,L,ier
   Character  file*(*)
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
    ier=0;  close (Li,err=:o:)
:o: L=LENOCC(file);  Check L>0
*
    open (Li,file=file,form='FORMATTED',status='OLD',err=:e:)
    If (Idebug>=2) <w> file(1:L),Li;
       (' AgFOPEN: file ',a,' opened succesfully on unit',i3)
    IKineOld=IKine
    return
:e: <w> file(1:L); (' AgFOPEN error openning file ',a); ier=1
   end
 
 
 
*CMZ :          19/07/97  12.41.07  by  Pavel Nevski
*-- Author :    Pavel Nevski   18/07/97
*************************************************************************
   Subroutine   A g F R E A D (ier)
*                                                                       *
* Description: loop over all files opened by USER/INPUT                 *
*              and call the corresponding readout routine               *
*************************************************************************
   Implicit   None
   Integer    LENOCC,Igate,Ier,I
   Character  C*1
*
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
   Ier = 0
   Do i=1,LENOCC(Ccommand)
     C=CCOMMAND(i:i); Igate=i
     if  C=='e'  { Call AGZREAD('P',ier) }
     if  C=='t'  { call AgReadTXT(Igate) }
     If Igate<=0 { Ier=1;        return  }
     If (Idebug>0 & (C=='e'|C=='t'))  <w>  C,Ntrack,Nvertx
        (' AgFREAD mode ',a,': # of particles in GEANT=',i6,' vertices=',i6)
   enddo
   End
 
 
*CMZ :          02/08/98  15.13.50  by  Pavel Nevski
*-- Author :    Pavel Nevski   18/07/97
*************************************************************************
   Subroutine   A g R E A D T X T (Igate)
*                                                                       *
* Description: read both NEW and OLD gstar event generator text formats *
Replace [READ[DIGIT](#)#;] with [READ(#2,ERR=:E:)#3;IF(Idebug>=#1)<W>#3;]
*************************************************************************
   implicit      none
   character*120 line
   integer       LENOCC,li,Ieven,Ntrac,Nvert,itr,ivt,nv,nt,Igate,i,
                 LabelTr,LabelVx,ge_pid,StartVx,StopVx,
                 eg_proc,parent
   Real          version,east_z,east_a,west_z,west_a,sqrts,b_max,
                 PP(3),vert(4),UBUF(10)
*
   integer       istat,eg_pid,moth,daut,num(5)
   data          num/1,1,0,0,0/
   character     Cform*8 /'/6I 9F'/
   Real          phep,vhep
   common/GHEPEVT/ istat,eg_pid,moth(2),daut(2),phep(5),vhep(4)
*
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEND.
*
   Li=21-Igate
 { Ntrac,Nvert } = 999;
 { itr, ivt    } =  0;
*
 WHILE itr<Ntrac | ivt<Nvert
 { line='end-of-file';  read5 (li,'(a)') Line; (1x,a)
 
   If Line(1:5)=='GENER'
   {
     read1 (line(11:),*) version,east_z,east_a,west_z,west_a,sqrts,b_max
                       (' AgReadNew: GENER :',F8.3,4F8.0,F8.1,F8.3)
   }
   else If Line(1:5)=='EVENT'
   {
     read2 (line(7:),*) Ieven,Ntrac,Nvert;(' AgReadNew: EVENT :',3i8,2f8.3)
     if (Ieven<=-999) goto :e: " end of data "
   }
   else If Line(1:5)='TRACK'
   {
     read5 (line(7:),*) ge_pid,PP,LabelTr,StartVx,StopVx,eg_pid
                        (16x,'TRACK :',i6,3F9.3,4i6)
     Call VZERO(Vert,4);   Call AgSVERT(vert,-StartVx,-Igate,Ubuf,0,nv)
     Itr += 1;  call AgSKINE(PP,ge_pid,nv,Ubuf,0,nt)
   }
   else If Line(1:6)=='VERTEX'
   {
     read5 (line(8:),*) Vert,LabelVx,eg_proc,parent; (16x,'VERTEX:',4F10.6,3i6)
     ivt += 1;  call AgSVERT(vert,-LabelVx,-Igate,Ubuf,0,nv)
   }
   else If Line(1:6)=='HEPEVT' & itr+ivt==0
   { *             HEPEVT text format
     read1 (line(8:),*) Ntrac,Ieven; (' gstar_Read HEPEVT:',i8,' event#',i6)
 
     do itr=1,Ntrac
     {  read5(li,*) istat,eg_pid,moth,daut,phep,vhep; (6i5,5F8.2,4F9.3)
        num(3)=0;   If (itr==1) num(3)=1
        Call RbSTORE ('/EVNT/GENE/GENT*',num,Cform,15,istat)
        check Istat==1;       Call apdg2gea (eg_pid, ge_pid)
	if ge_pid<=0
        {  if (Idebug>1) <W> eg_pid;(' gstar_read HEPEVT unknown particle',i6);
           ge_pid = 1000000+eg_pid
        }
        Call AgSVERT ( vhep,   0,  -Igate,   0.,       0, nv);
        Call AgSKINE ( phep,  ge_pid,  nv, float(itr), 0, nt);
     }  Break
   }
   else If Index(Line,'event')>0 & itr+ivt==0
   { *              OLD text format
     i=Index(Line,'event');  line(i:i+6)='  ';
     read1 (line,*) Ntrac,Ieven; (' gstar_ReadOld: ',i8,' event# ',i6)
     call VZERO(vert,4); call AgSVERT(vert,-1,-Igate,Ubuf,0,nv)
     do itr=1,Ntrac
     {  read5 (li,*) ge_pid,PP; (16x,i6,3F8.3)
        call AgSKINE(PP,ge_pid,nv,Ubuf,0,nt)
     }  break
   }
   else If LENOCC(Line)>0
   { <w> line(1:LENOCC(Line)); (' unknown line : ',a); }
 } return
*
:e:<w> line; (' AgReadTXT error in line '/1x,a);  Igate=-1
   end
 
 
*CMZ :          28/07/98  17.27.19  by  Pavel Nevski
*-- Author :    Pavel Nevski   23/04/98
******************************************************************
      subroutine    A G P R E A D (ier)
* description: read and possible re-assembly splitted subevents  *
******************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
   Integer ISLFLAG,IsubEv,Iprin,IbEvnt,ier,jer,i,IHEAD(10)
*
   IbEvnt = 0; IsubEv = 0
   jer=1;  call AgZread ('P',ier)
   if (Ier!=0 | JHEAD<=0) go to :er:
   Iprin = ISLFLAG('INPU','PRIN')
   call UCOPY(IQ(JHEAD+1),IHEAD,10)
 
* appending
    While IQ(JHEAD+5)>IQ(JHEAD+6)
    { jer=2;  call AgZread ('P',ier);
      if (ier!=0 | JHEAD<=0) go to :er:
 
      IsubEv+=1; prin2 Isubev,(IQ(JHEAD+i),i=1,10)
      (' AGPREAD: appending subevent',i3,' HEADER ='/10x,2i6,2i12,6i6)
 
      IbEvnt = IQ(JHEAD+6)
      call AgMERGE (Iprin,0,IbEvnt,0.,Ier)
      jer=3;  if (Ier!=0) go to :er:
      Call Ucopy(IHEAD,IQ(JHEAD+1),4)
    }
    ier=0; IQUEST(1)=0; Return
 
:er:; prin1 jer,ier,Isubev,IbEvnt;
      (' AGPREAD: error',2i3,' in subevent =',2i6)
      IQUEST(1)=jer; IQUEST(2)=ier; ier=jer
      end
*CMZ :          13/07/98  10.03.02  by  Pavel Nevski
*-- Author :    Pavel Nevski   13/07/98
****************************************************************************
 
      function    lgnfind (i,name)
* Description: find the origin of the event/run bank                       *
* Input : I     - Link number : 1 = primary, 2 = secondary (obsolete)      *
*         name  - RUNT or EVNT                                             *
* Output:       - link to the bank or -1 if the bank was not found.        *
* Original version:                              Robert DeWolf  23/07/92   *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
      character*4 name
      integer     lgnfind,i,l,n
 
      l = -1
      if (name=='EVNT') l = lkevnt
      if (name=='RUNT') l = lkrunt
      do n=2,i { if (l>0) l=lq(l) }
      lgnfind = l
      end
*CMZ :  1.00/00 30/06/95  13.09.22  by  Pavel Nevski
*-- Author :     Pavel Nevski
    subroutine   M Y F I L L (tt,Ix,Iy);
*KEEP,HISCOM.
      Implicit Character*30 (T)
      Parameter (LC=30,L=50,Idm=2000)
      Common    /histab/List(Idm),Tab(L,3),WW(L,3),
     +                  ie(3),Nen(3),nn(l),aa(l),bb(l)
*     - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
   Equivalence (Jtit,Itit);
   character*(*) tt; Character Jtit*4,L1*1,L2*1;
   Dimension ii(5); Common /LastId/ id;   Data Iw/0/;
*
   If (Iw==0) call VZERO(List,Idm);  Iw=1;  tit=tt;
   if tit(1:1)==' ' { ie(1)=Mynum(tit,1); Return; }
   Jtit=tit(5:8);  Ie(2)=Abs(Itit);  If (Ie(2)>L) ie(2)=Mynum(tit,2);
   id=ie(1)*L+ie(2);
if List(id)==0
{ " histogram Id defined by all LC characters, find parameters with keywords ";
  tt=tab(ie(2),2); Itit=ie(2); tit(5:8)=Jtit;          L2=' '; N=0;
  do k=1,25                                                "IF:"
  { L1=L2; L2=tt(k:k); Check L1==' ' & L2#' ';      " new word started "
    tn=tt(k:k+3);  i=Mynum(tn,4);   Check i>0;      " is a keyword ->  "
    N=N+1; ii(N)=i;                                 " get  parameters  "
  }
  IF      N==0 {Call Hbook1(id,tt,     100 ,       0.,       0.,0); List(id)=1}
  else IF N==1 {Call Hbook1(id,tt,nn(ii(1)),aa(ii(1)),bb(ii(1)),0); List(id)=1}
  else         {Call Hbprof(id,tt,nn(ii(2)),aa(ii(2)),bb(ii(2)),
                                          aa(ii(1)),bb(ii(1)),'S'); List(id)=2}
}
If (List(id)>1) y=argum(Iy);  Call Hfill (id, Argum(Ix), y, 1.);
End;
 
*CMZ :  1.00/00 01/05/95  15.03.56  by  Pavel Nevski
*-- Author :     Pavel Nevski
    subroutine   M Y B O O K (tit,N,Ia,Ib);
*KEEP,HISCOM.
      Implicit Character*30 (T)
      Parameter (LC=30,L=50,Idm=2000)
      Common    /histab/List(Idm),Tab(L,3),WW(L,3),
     +                  ie(3),Nen(3),nn(l),aa(l),bb(l)
*     - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
tn=tit(1:4); ih=Mynum(tn,3); NN(ih)=N; AA(ih)=Argum(Ia); BB(ih)=Argum(Ib);
End;
*CMZ :  1.00/00 01/05/95  14.38.22  by  Pavel Nevski
*-- Author :     Pavel Nevski
    Function     M Y N U M   (tit,jj);
*KEEP,HISCOM.
      Implicit Character*30 (T)
      Parameter (LC=30,L=50,Idm=2000)
      Common    /histab/List(Idm),Tab(L,3),WW(L,3),
     +                  ie(3),Nen(3),nn(l),aa(l),bb(l)
*     - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
    j=min(jj,3);
    :I: for i=1 to nen(j)
    { ie(j)  = mod(ie(j),nen(j))+1; if (tit==TAB(ie(j),j)) go to :FND:;}
       MYNUM=0; if (jj>3) Return;
      nen(j) = min0(nen(j)+1,L);    ie(j) = nen(j);  tab(ie(j),j) = tit;
:FND: MYNUM=ie(j);
End;
*CMZ :  1.00/00 01/05/95  16.32.51  by  Pavel Nevski
*-- Author :     Pavel Nevski
    Function     A R G U M    (Iarg)
    Real         ARGUM,Var
    Integer      Iarg,Ivar
    Equivalence  (Var,Ivar)
 
    Ivar=Iarg;              Argum=Ivar;
    if (abs(Iarg) > 100000) Argum=Var
    END
 
*CMZ :  1.00/00 07/05/95  00.37.37  by  Pavel Nevski
*-- Author :    Pavel Nevski
**********************************************************************
      function     X F I N T E R (X,A,F,N)
*  Description:  simple linear interpolation                         *
**********************************************************************
  Implicit  None
  Integer N,K,K1/1/,K2/1/
  Real XFINTER,X,A(n),F(n),X1,X2;
 
 XFINTER=F(1);  Check N>1;
 If (K1>=N | X<A(K1))  K1=1
 If (K2> N | X>A(K2))  K2=N
 While K2-K1>1  { K=(K1+K2)/2; IF A(K)<X {K1=K} else {K2=K} }
 X1=A(K1); X2=A(K1+1);
 XFINTER=(F(K1)*(X-X2)+F(K1+1)*(X1-X))/(X1-X2)
END
 
*CMZ :          12/05/98  14.44.06  by  Pavel Nevski
*CMZ :  1.00/00 07/05/95  13.12.49  by  Pavel Nevski
*-- Author :    Pavel Nevski
**********************************************************************
      function    X G I N T   (EXT,A,B,EPS)
*   Description:  famous integration procedure                       *
**********************************************************************
  Implicit None
  External EXT
  Integer  M,N,I,K
  Real     XGINT,A,B,Eps,OTB,Y,W(4),U(4),D,Ext
  DATA     M/4/,
  U/-.8611363,-.3399810, .3399810 ,.8611363/,
  W/ .3478548, .6521452, .6521452, .3478548/
 
 N=10;  OTB=0;  Loop
 {  Y=OTB; OTB=0; D=(B-A)*.5/N;
    DO I=1,N  { DO K=1,M  { OTB+=W(K)*EXT(A+D*(2*I-1+U(K)))*D; } }
    XGINT=OTB;  N=2*N;  IF N>100000 { Print *,'XGINT Divergence !!!'; Return;}
 } While EPS>0 & ABS(OTB-Y)>ABS(EPS*OTB)
END
 
**********************************************************************
      function    X G I N T 1   (EXT,A,B,EPS)
*   Description:  famous integration procedure                       *
**********************************************************************
  Implicit None
  External EXT
  Integer  M,N,I,K
  Real     XGINT1,A,B,Eps,OTB,Y,W(4),U(4),D,Ext
  DATA     M/4/,
  U/-.8611363,-.3399810, .3399810 ,.8611363/,
  W/ .3478548, .6521452, .6521452, .3478548/
 
 N=10;  OTB=0;  Loop
 {  Y=OTB; OTB=0; D=(B-A)*.5/N;
    DO I=1,N  { DO K=1,M  { OTB+=W(K)*EXT(A+D*(2*I-1+U(K)))*D; } }
    XGINT1=OTB;  N=2*N;  IF N>100000 { Print *,'XGINT1 Divergence !!!'; Return}
 } While EPS>0 & ABS(OTB-Y)>ABS(EPS*OTB)
END
 
**********************************************************************
      function    X G I N T 2   (EXT,A,B,EPS)
*   Description:  famous integration procedure                       *
**********************************************************************
  Implicit None
  External EXT
  Integer  M,N,I,K
  Real     XGINT2,A,B,Eps,OTB,Y,W(4),U(4),D,Ext
  DATA     M/4/,
  U/-.8611363,-.3399810, .3399810 ,.8611363/,
  W/ .3478548, .6521452, .6521452, .3478548/
 
 N=10;  OTB=0;  Loop
 {  Y=OTB; OTB=0; D=(B-A)*.5/N;
    DO I=1,N  { DO K=1,M  { OTB+=W(K)*EXT(A+D*(2*I-1+U(K)))*D; } }
    XGINT2=OTB;  N=2*N;  IF N>100000 { Print *,'XGINT2 Divergence !!!'; Return}
 } While EPS>0 & ABS(OTB-Y)>ABS(EPS*OTB)
END
 
*CMZ :          31/10/97  12.55.37  by  Pavel Nevski
*CMZ :  1.00/00 06/08/95  17.16.05  by  Pavel Nevski
*-- Author :    Pavel Nevski
*************************************************************************
      function     N X P O I S S (w)
*  Description :         simulate Poisson distribution                  *
*************************************************************************
Real Rndm,exp,w,r,P,S;  Integer n,NXpoiss
r=rndm(1.);   n =0;  P =exp(-w);  S =P;
While s<r   { n+=1;  P*=w/n;      S+=P; }
NXpoiss=n
End
 
 
*CMZ :          25/11/97  23.22.25  by  Pavel Nevski
*CMZ :  1.30/00 06/09/96  18.10.33  by  Pavel Nevski
*CMZ :  1.00/00 25/08/95  00.07.49  by  Pavel Nevski
*-- Author :    A.Rozanov   30/06/95
********************************************************************
*                                                                  *
                 function      F U N C T (X)
*               track description in ATLAS tracker                 *
* OPTION choice: 0          - vertex                               *
*                1          - cylinder parallel to z               *
*                1+/- tilt  - plane parallel to z, abs(tilt)<0.5   *
*                2          - plane perpendicular to z axis        *
*                11&12      - Calorimeter points for brem fit      *
* modifications:                                                   *
* PN, 14/11/97 - bremfit corrected by David Rousseau               *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,HELVAR.
*--   helix parameters
      LOGICAL                                           TRAPPED
      REAL            BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL
      COMMON /HELVAR/ BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL,TRAPPED
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,FUMVAR.
*   fumili fitted parameters
      REAL            A
      COMMON /FUMILA/ A(10)
*   fumili parameters - in addition to FUMSIZE
      REAL         A0FIT,FI0FIT,PTINV,Z0FIT,DZDR0,RBREM,XBREM,RSHOW
      EQUIVALENCE (A0FIT,A(1)),(FI0FIT,A(2)),(PTINV,A(3)),(Z0FIT,A(4)),
     +            (DZDR0,A(5)),(RBREM,A(6)),(XBREM,A(7)),(RSHOW,A(8))
*     -----------------------------------------------------------
*     --------------------------------
*KEND.
*
      REAL      FUNCT,X(5),PBREM(10),TOWHERE(2),OPTION,BFLD,RMX,SAS,ZR0,TILT
      INTEGER   IOPTION,JOPTION,IBREM
      SAVE      IBREM,PBREM
      DATA      BFLD/2./,RMX/140./
*     ----------------------------
      OPTION     = X(1)
      TOWHERE(1) = X(2)
      SAS        = X(3)
      ZR0        = X(4)
      TOWHERE(2) = X(5)
      JOPTION    = nint (OPTION)
      IF (0<OPTION & OPTION<1.99) JOPTION = 1
      IOPTION    = mod (JOPTION,10)
      tilt       = Option-Joption
*
*    set starting point from vertex (0,0)+A
*
      IF IOPTION==0  " vertex "
      {  BCONST  = -2.999792E-3*BFLD
         TRAPPED = .FALSE.
         CF      = COS(FI0FIT)
         SF      = SIN(FI0FIT)
         RS      = A0FIT
         ZS      = Z0FIT
         XS      = -RS*SF
         YS      = +RS*CF
         TL      = DZDR0
         TT      = PTINV
         EL      = 0
         FUNCT   = RS
         IBREM   = 0
*        put protection against infinite momentum - 7/6/94
         IF (ABS(TT)<1.E-4) TT=SIGN(1.E-4,PTINV)
      }
      ELSE IF TOWHERE(1)!=0   " we move to the next point "
      {* special point - calorimeter: as if no brem occures
         IF (IBREM==1 & OPTION>10) CALL UCOPY(PBREM,XS,10)
         CALL HELIXA(OPTION,TOWHERE)    !  swim to r,z or plane
*        Have we crossed the brem point ?
         IF (IBREM==0 & RS>RBREM & RBREM<RMX) THEN
            IBREM = 1                   !  moment is changed
            CALL HELIXA (1., RBREM)
            CALL UCOPY  (XS,PBREM,10)
            TT = PTINV+SIGN(XBREM,PTINV)/(RBREM-RSHOW)/BCONST/RSHOW*2
            CALL HELIXA (OPTION,TOWHERE)
         ENDIF
 
*        Have we crossed the brem point back ?
         IF (IBREM==1 & RS<RBREM) THEN
            IBREM = 0                   !  moment is restored
            CALL UCOPY  (PBREM,XS,10)
            CALL HELIXA (OPTION,TOWHERE)
         ENDIF
 
         FUNCT = ATAN2(YS,XS)           ! always phi-measurement
*        introduce a shift for the strip center for u/v strips in z/r
         IF (SAS!=0 & IOPTION==1) FUNCT=FUNCT+SAS*(ZR0-ZS)/RS
                                  "  * (1-SAS*(ZR0-ZS)/RS*TILT) "
         IF (SAS!=0 & IOPTION==2) FUNCT=FUNCT+SAS*(ZR0-RS)/RS
         FUNCT=AMOD(FUNCT+6.2831853,6.2831853)
      }
      ELSE
      {*  Give Z/R component instead of Phi according to option
          IF IOPTION=1 { FUNCT = ZS } else { FUNCT = RS }
      }
      END
 
 
*CMZ :          20/11/97  22.25.45  by  Pavel Nevski
*CMZ :  1.30/00 11/05/96  21.53.45  by  Pavel Nevski
*CMZ :  1.00/00 25/08/95  00.07.49  by  Pavel Nevski
*-- Author :  Pavel Nevski
********************************************************************
*                                                                  *
          subroutine     H E L I X A (OPTION,TOWHERE)
*                                                                  *
*  track vector in /HELVAR/ is updated by Helix to endpoint:       *
*      OPTION = 1 : endpoint at radius TOWHERE                     *
*      OPTION = 2 : endpoint at z-coor TOWHERE                     *
*  Trapped particles (loopers) are stopped at their maximum radius *
*  Modifications:                                                  *
*  PN, 20.11.97:  tilt up to 1 accepted with OPTION (0-1.999)      *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,HELVAR.
*--   helix parameters
      LOGICAL                                           TRAPPED
      REAL            BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL
      COMMON /HELVAR/ BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL,TRAPPED
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
*
      INTEGER NSMAX,NS,IOPTION
      REAL    OPTION,TOWHERE(2),TILT,SMAX,TOL,
              R0,RE,ZE,DL,DF,RP,SDF,CDF,CD1,D,C0,SB,CB,RO
      DATA    TOL/2.E-6/, SMAX/.50/, NSMAX/10/, RO/0./
*     ---------------------------------------------------
 
      IOPTION = nint(OPTION);          IF (OPTION<1.999) IOPTION = 1
      TILT    = OPTION - IOPTION
      IOPTION = MOD(IOPTION,10);       {RE,ZE} = TOWHERE(1)
 
   IF .not.TRAPPED
   {  R0=1./(BCONST*TT);  {CB,SB}=0
*   new  OPTION==3 : have to swim to a plane parallel to Z-axis
      IF TILT!=0
      {  RE      = RE*COS(TILT)
         CB      = COS(TOWHERE(2)+TILT)
         SB      = SIN(TOWHERE(2)+TILT)
      }
*   Loop here until the required precision is reached
      DO NS=1,NSMAX
      {  RO = RS
         IF IOPTION==1        " barrel-like swim "
         {  IF CB==0 | NS==1  " swim to fix RE "
            {  RP=XS*CF+YS*SF; SDF=(SQRT(MAX(RE*RE-RS*RS+RP*RP,0.))-RP)/R0 }
            ELSE " CB> & NS>1 - swim to the propre plane "
            {  RP=XS*CB+YS*SB; SDF=(RE-RP)*RS/(R0*RP)  }
         }
         ELSE IF IOPTION==2  " - swim to fix ZE "
         {  DF=(ZE-ZS)/TL;    SDF=SIN(DF/R0)  }
         *      Check if the step is too large
         IF (ABS(SDF)>SMAX) SDF = SIGN(SMAX,SDF)
         C0 = CF
         CDF = SQRT(1-SDF**2);               CD1 = SDF*SDF/(1+CDF)
         XS = XS+(SDF*CF-CD1*SF)*R0;         YS = YS+(SDF*SF+CD1*CF)*R0
         CF = CF*CDF-SF*SDF;                 SF = SF*CDF+C0*SDF
         RS = SQRT(XS**2+YS**2);             DL = R0*ASIN(SDF)
         EL = EL+DL;                         ZS = ZS+DL*TL
*       build the estimator
         IF IOPTION==1  { IF CB==0 { D=RE-RS } else { D=RE-XS*CB-YS*SB } }
         ELSE           { D=ZE-ZS }
*       Check precision and put some protection
         IF (ABS(D/TOWHERE(1)) < TOL)   return   " accuracy is achived   "
         IF (RS > 199 | ABS(ZS) > 399)  return   " outside the apperture "
       " IF ((RE-RO)*(RO-RS) > 0)        Break     particle is trapped   "
   }  }
* RE - final point, may by R (for IOPT=1) or Z (for IOPT=2)
   TRAPPED = .TRUE.
   If IOPTION==1
   {  XS=XS*RE/RS
      YS=YS*RE/RS
      ZS=ZS*RE/RS
      RS=RE
   }
   else
   {  XS=XS*ZE/ZS
      YS=YS*ZE/ZS
      RS=SQRT(XS**2+YS**2)
      ZS=ZE
   }
   END
 
 
*CMZ :  1.00/00 25/08/95  00.07.49  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
                 subroutine    F U M S I Z E
*                                                                  *
* Original Version:                                 Pavel Nevski   *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEND.
      Integer i
      DO I=1,L  { AMX(I)=1.E30;   AMN(I)=-1.E30 }
      End
 
*CMZ :          12/06/98  11.36.35  by  Pavel Nevski
*CMZU:  1.00/01 14/01/96  17.57.22  by  Pavel Nevski
*CMZ :  1.00/00 07/03/95  21.21.52  by  Pavel Nevski
*-- Author :    Pavel Nevski   07/02/95
********************************************************************
*                                                                  *
                 subroutine    A g F K I N E (ITR)
* Description: restore GCKINE common block plus auxilary AGMYKINE  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
C
*KEEP,FUMVAR.
*   fumili fitted parameters
      REAL            A
      COMMON /FUMILA/ A(10)
*   fumili parameters - in addition to FUMSIZE
      REAL         A0FIT,FI0FIT,PTINV,Z0FIT,DZDR0,RBREM,XBREM,RSHOW
      EQUIVALENCE (A0FIT,A(1)),(FI0FIT,A(2)),(PTINV,A(3)),(Z0FIT,A(4)),
     +            (DZDR0,A(5)),(RBREM,A(6)),(XBREM,A(7)),(RSHOW,A(8))
*     -----------------------------------------------------------
*     --------------------------------
*KEND.
      INTEGER           ITR,Nw,Ip
      REAL              VMOD,UBUF(20),Rcal/168./
      REAL              PTP,TET,PHI,ETP,ENN,PLP,RAP
      COMMON /AGMYKINE/ PTP,TET,PHI,ETP,ENN,PLP,RAP
      Character         Cpart*20
;
      {ITRA,ISTAK,IPAOLD}=0;            Check 1<=ITR&ITR<=NTRACK
      CALL GFKINE (ITR,VERT,PVERT,Ip,IVERT,UBUF,Nw);  Check Ip>0
      CALL GFPART (Ip,CPART,ITRTYP,AMASS,CHARGE,TLIFE,UBUF,Nw)
      ITRA = ITR;
      PTP  = SQRT (PVERT(1)**2+PVERT(2)**2);
      TET  = ATAN2(PTP,PVERT(3));           ETP  = -ALOG(TAN(TET/2));
      PHI  = ATAN2(PVERT(2),PVERT(1));      IF (PHI<0) PHI+=6.283185;
*   Compute calo impact rapidity (D.Froideval personally)
      PLP  = PVERT(3) + VERT(3)/RCAL*PTP;
      ENN  = SQRT (PLP**2+PTP**2);          RAP = .5*ALOG((ENN+PLP)/(ENN-PLP));
*   Fill Funct/Fumili common to swim the track
      Fi0Fit = PHI              " Fi at origin     "
      A0Fit  = VMOD(VERT,2)     " Impact parameter "
      PTinv  = CHARGE/PTP       " 1/pT             "
      Z0Fit  = VERT(3)
      dZdR0  = 1/TAN(TET)
      Xbrem  = 0
      Rbrem  = 200
      Rshow  = Rcal
*     Print *,'  get track fi0,a0,Pti,z0,dz=',Fi0Fit,A0Fit,PTinv,z0fit,dZdR0
    END
 
*CMZ :          04/12/97  13.25.20  by  Pavel Nevski
*CMZU:  1.00/01 25/01/96  02.13.04  by  Pavel Nevski
*CMZ :  1.00/00 28/08/95  00.45.41  by  Pavel Nevski
*-- Author :    Pavel Nevski   11/10/93
********************************************************************
*                                                                  *
                subroutine  X N T U P (TIT,IVAR)
*                                                                  *
*   simple mind NTUPLE, if you don't like it, do it yourself  !!!  *
* XNTUP (' a b c ',I) defines 'page' of tages with 'vector' prefix *
*                    and preselects i-th component from a,b,c      *
*         you can also use a default page without prefixes at all  *
* XNTUP ('tag',v)    defines a value of a tag in the current page  *
*                    in selected component of vector (a,b,c)       *
* XNTUP ('*',ID)     close current event                           *
*                                                                  *
* Original Version:                                   Pavel Nevski *
* Modifications:   page structure for Fabiola         08/10/94     *
*       introduce a default page without prefixes     27/08/95     *
* 04.12.97 - customise for atlsim: get IUHIST & CDHIST
********************************************************************
      IMPLICIT NONE
*KEEP,agckine.
*    AGI general data card information
      Integer          IKineOld,IdInp,Kevent,
     >                 Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 IbCurrent,IvCurrent,Ioutp,IoutpOld
      Real             AVflag,AVcoor,AVsigm,Ptype,PTmin,PTmax,
     >                 Etamin,Etamax,PhiMin,PhiMax,Ptflag,
     >                 Zmin,Zmax,BgMult,BgTime,BgSkip,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINE/ IKineOld,IdInp,Kevent(3),
     >                 AVflag,AVcoor(3),AVsigm(3),
     >                 Ptype,PTmin,PTmax,Etamin,Etamax,
     >                 PhiMin,PhiMax,Ptflag,Zmin,Zmax,
     >                 Pxmin,Pxmax,Pymin,Pymax,Pzmin,Pzmax
      COMMON /AgCKINB/ Iback,IbackOld,IbMode,IbBefor,IbAfter,
     >                 BgMult,BgTime,BgSkip,IbCurrent,IvCurrent
      COMMON /AgCKINO/ Ioutp,IoutpOld
      Character*20     CoptKine,CoptBack,CoptOutp
      COMMON /AgCKINC/ CoptKine,CoptBack,CoptOutp
      Character*20     CrunType
      COMMON /AgCKINR/ CrunType
      Integer          Ncommand
      Character*20     Ccommand
      COMMON /AgCCOMD/ Ncommand,Ccommand
      Integer          IUHIST
      Character*80            CFHIST,CDHIST
      COMMON /AgCHIST/ IUHIST,CFHIST,CDHIST
*
      Integer          NtrSubEV,NkineMax,NhitsMax,NtoSkip,NsubToSkip,
     >                 Nsubran,ItrigStat,NsubEvnt,IsubEvnt,
     >                 Make_Shadow,Flag_Secondaries
      Real             Cutele_Gas,VertexNow
      COMMON /AgCSUBE/ NtrSubEV,NkineMax,NhitsMax,
     >                 NtoSkip,NsubToSkip,Nsubran(2)
      COMMON /AgCSTAR/ Make_Shadow,Cutele_Gas,Flag_Secondaries
      COMMON /AgCstat/ ItrigSTAT,NsubEvnt,IsubEvnt,VertexNow(3)
*
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*KEND.
      CHARACTER*(*) TIT
      CHARACTER*8   TAG,TAGS,Pfx,PfxS
      CHARACTER*16  PAGTAG,PAGE,PAG
      REAL          V,VAL
      INTEGER       IVAR,IV,ID,JD,IT,IP,II,KV,NTAG,NPAG,NPfx,NVAL,
                    K,L,N,LENOCC,NT,NV,NP,ND,Itag,Ipfx,KADR
      PARAMETER     (NTAG=200,NPAG=200,NPfx=200,NVAL=1000)
      COMMON /AGXTUPLE/ NT,NP,NV,ND,Itag(NPAG+1),Ipfx(NPAG+1),KADR(NPAG+1),
             PfxS(NPfx+1),PAGE(NPAG+1),TAGS(NTAG+1),PAGTAG(NVAL),VAL(NVAL)
      EQUIVALENCE   (V,IV)
      LOGICAL       FIRST /.TRUE./
      INTEGER       Lout/6/,Iprin/0/
      DATA          IP,KV,JD/1,1,1/
 
*   -------------------------------------------------------------------
      IF Iabs(IVAR)<1 000 000 {"integer" V=IVAR} else {"real" IV=IVAR}
*   -------------------------------------------------------------------
      ID=V
      IF TIT(1:1)==' '            " page declaration "
      {  PAG=TIT
         DO  IP=1,NP  { IF (PAG==PAGE(IP)) GOTO :P: }
         If (!First)  GoTo :e:
*           new page entered
            NP=MIN(NP+1,NPAG); IP=NP
*           page markers:     PfxS       variables   Block*Variables
            PAGE(IP)=PAG; Ipfx(IP)=ND;  Itag(IP)=NT;  KADR(IP)=NV
*           get list of prefixes
            L=LENOCC(TIT);  N=0;  Pfx=' ';  PfxS(ND+1)=' '
            DO K=1,L+1
            {  IF K<=L & TIT(K:K)!=' '
               {  N=MIN(N+1,8);  Pfx(N:N)=TIT(K:K);  Next; }
               Check N>0;  ND=MIN(ND+1,NPfx);  PfxS(ND)=Pfx;  N=0;  Pfx=' '
            }
            ND=Max(1,ND);  Ipfx(IP+1)=ND;  Itag(IP+1)=NT;  KADR(IP+1)=NV
            Prin1 PAG,ND-Ipfx(IP),NT,NV
            (' XNTUP: New Page ',A,' with ',i3,' blocks, NT,NV=',2i5)
*           No rep. for this page  - set ID selector within it
        :P: KV=Ipfx(IP+1)-Ipfx(IP);    JD=MAX(1,MIN(ID,KV))
      }
      ELSE IF TIT(1:1)!='*'       "  variable (tag)  "
      {  TAG=TIT
         DO IT=Itag(IP)+1,Itag(IP+1) { IF (TAG==TAGS(IT)) GoTo :T: }
         IF (!FIRST) GoTo :E:
            NT=MIN(NT+1,NTAG);  It=Nt;   TAGS(NT)=TAG
            Itag(IP+1)=NT;    NV=NV+KV;  KADR(IP+1)=NV
            Prin1 TAG,NT,IP,NV
            (' XNTUP: new tag ',A,i4,' on page',i3,' NVtot=',i5)
        :T: II=MIN(KADR(IP)+(IT-Itag(IP)-1)*KV+JD,NVAL);  VAL(II)=V
      }
      ELSE                        "   close event    "
      {  If (IUHIST>0) CALL RZCDIR('//'//CDHIST,' ')
         If (IUHIST>0) CALL  HCDIR('//'//CDHIST,' ')
         IF FIRST
         {  DO IP=1,max(1,Np)
            {  DO IT=Itag(IP)+1,Itag(IP+1)
               {  KV=max(1,Ipfx(IP+1)-Ipfx(IP))
                  prin1 IP,IT,KV,NV
                  (' XNTUP: defining page IP with tags IT,KV=',5i5)
                  DO JD=1,KV
                  {  II=MIN(KADR(IP)+(IT-Itag(IP)-1)*KV+JD,NVAL)
                     Pfx=' ';  If (NP>0) Pfx=PfxS(Ipfx(IP)+JD)
                     PAGTAG(II)=Pfx(1:LENOCC(Pfx))//TAGS(IT)
                     prin1 JD,II,PAGTAG(ii),LENOCC(Pfx)
                     (10x,'JD,II,PAGTAG=',2i5,2x,A,i5)
            }  }  }
            CALL HBOOKN(ID,'ATLAS',NV,CDHIST,1000,PAGTAG)
            FIRST=.FALSE.;
         }
         CALL HFN(ID,VAL)
         CALL VZERO(VAL,NVAL)
         {IP,JD,KV}=1
      }
      Return
:E:;  Prin0 TAG; (' XNTUP: too late to introduce new TAG/PAGE ',A)
      END
 
*CMZ :          08/11/97  18.05.57  by  Pavel Nevski
*CMZU:  1.30/01 17/05/97  16.47.03  by  Pavel Nevski
*CMZ :  1.30/00 15/04/97  14.58.38  by  Pavel Nevski
*-- Author :    Pavel Nevski   03/03/96
*************************************************************************
*                                                                       *
                subroutine   A G G P L A N E (Cset,Ipp)
*                                                                       *
* Modifications:                                                        *
* A.Rozanov 07/11/97: IpOld introduced to start new plane without mods  *
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,TRBANK.
*   - Track point bank
      INTEGER         LTB,NTB,LPNT,ISPOINT
      PARAMETER       (LTB=10000,LPNT=12)
      REAL            TRPOINT, DTRPOINT
      COMMON /TRBANK/ NTB,TRPOINT(LPNT,LTB)
* ISPOINT contains IPP={IP,IZ,IF} of counter, negative if point rejected
      COMMON /TRBANI/     ISPOINT(LTB)
* DTRPOINT contains the cluster position error (ask A.Rozanov for details)
      COMMON /TRBANJ/     DTRPOINT(LTB)
      REAL            OPNT,XPNT,DPNT,SPNT,APNT,EPNT,PPNT
      COMMON /TRKPNT/ OPNT,XPNT(3),DPNT,SPNT(2),APNT(3),EPNT,PPNT
*  1  : Opnt    - 1+tilt for barrel, 2 for end-caps
* 2-4 : Xpnt(i) - r,phi,z of the element center
*  5  : Dpnt    - stereo angle for strips, drift distance for TRT
* 6-7 : Spnt(i) - error in phi and Z/R
*  8  : Apnt(1) - detector code as follows
*  9  :     (2) - plane number in AgCRTAB
* 10  :     (3) - first digi reference number
* 11  : Epnt    - energy or discriminator value
* 12  : Ppnt    - MC reference track number
      REAL            PIXB,PIXE,GAAS,SCTT,ZSCT,SITV,SIT,MSGC,XTRT
      DATA            PIXB,PIXE,GAAS,SCTT,ZSCT,SITV,SIT,MSGC,XTRT
     +                / 1,   2,   3,   4,   5,   6,  7,   8,   9  /
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agclink.
*   links for dynamic banks access
       INTEGER    NALINKMAX,AG_NLINK,AG_LINK
       PARAMETER  (NALINKMAX=100)
       COMMON /AGCLINK/ AG_NLINK,AG_LINK(0:NALINKMAX)
*      - - - - - - - - - - - - - - - - - - - - - -
 
*KEEP,agcclus.
*                                            clustering bank
      Integer          Ndig,Ktyp,Lh,Nclu,Kdig,Ltra,Ktypdig,Nodig
      Real                          Fdig,Zdig,Edig
      Parameter        (Lh=1024)
      Common /ARCdigt/ Ndig,Ktyp,Fdig(Lh),Zdig(Lh),Edig(Lh),
     +                           Nclu(Lh),Kdig(lh),Ltra(Lh)
      COMMON /AGCCLUS/ Ktypdig(Lh),NoDig(Lh)
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcrfun.
*     Road definition function and its parameters
      Integer          IFunAdr,IfunFlag
      Real             XXf(6),YYf(6),   Xopnt,Xrz,Xsas, Xzrc,Xphic,Xres,
     >                                  Yphi, Yzr,Ydphi,Ydzr,Ysign,Yres
      Common /AgCRFun/ IFunAdr,Ifunflag,Xopnt,Xrz,Xsas, Xzrc,Xphic,Xres,
     >                                  Yphi, Yzr,Ydphi,Ydzr,Ysign,Yres
      Equivalence      (XXf,Xopnt), (YYf,Yphi)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcrtab.
*
*     Commons for the inner detector digi reconstruction
      Integer           Lstack,     Lr,   Lhead,   Lpack
      Parameter        (Lstack=2000,Lr=15,Lhead=52,Lpack=512)
*
*                                            subsystem descriptor
      Integer          Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,NumPmx,
     +                 Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires, nam,nmx
      Real             Rstack,drzm,RRmin,RRmax,ZZmin,ZZmax
*
      Common /AgCRtab/ Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,drzm,
     +                 RRmin,RRmax,ZZmin,ZZmax,
     +                 NumPmx,Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires,
     +                 Nam(15),Nmx(15),  Rstack(Lr,Lstack)
      Integer                            Istack(Lr,Lstack)
      Equivalence      (Rstack,Istack)
*                                            plane descriptor
      Real             rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent
      Integer          Nfi,Nzr,Nump,Iadr,Jres,Lpacku
      Common /AgCRta1/ rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent,
     +                 Nfi,Nzr,Nump,Iadr,Jres,Lpacku
*                                            detector size
      Integer          Ishape,Npar
      Real                         AgTran,   AgRmat,    Par
      Common /ARCplan/ Ishape,Npar,AgTran(3),AgRmat(10),Par(50)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
*KEND.
*
Structure AgCR { char Cset, char Cdet, int Isys, int Itype, int Npl,
                 int kkk, int kfi, int krz, int mrz, drzm,
		 RRmin, RRmax, ZZmin, ZZmax, int Istart, int Nadr, int NupMax,
		 char Nam(kkk), int Nmx(kkk), int Ibuf(Nadr),int Ipla(NupMax),
                 rzp(Npl),RZmin(Npl),RZmax(Npl),Fmin(Npl),Fmax(Npl),
                 Dfi(Npl),Dzr(Npl),Tilt(Npl),Sas(Npl),Fcent(Npl),
                 int Nfi(Npl), int Nzr(Npl), int Nump(Npl), int Iadr(Npl),
                 int Jres(Npl) }
*
  INTEGER      NV,Nd;          PARAMETER   (NV=10,Nd=10)
  Integer      NVL(NV),ISC(NV),K,Ia,Iad,ip,Iz,Jz,kz,If,i,id,Lm,kk,Jd,Jf,
               AgPFLAG,Iprin,Ids,Ip2,Mz,Mf,modz,Modf,itry,ipp,Ltr,N,if0,
               IpOld,ist/0/,ok/0/,Lpacki/0/
  Real         DIGI(Nd),Fc,Df,Yphi0
  Character*4  Cset,Cdet,Cs
  Save         NVL,Cdet,Cs,Iprin,Ids,Ip2,Lm,Modz,Modf,Jd,Jf
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
  IF  Ipp>=10000  {" automatic agplane continuation "  Ip=Ipp/10000;   }
  else            {" new user plane request "  Ip=Ipp; Modz=0; Modf=0; }
 
  {Ndig,Ktyp}=0;
*                                       for the first plane, get tables
  If Ip<=0 | Ip >999 | Cset(1:3)!=Cs(1:3)
  {  " start track at the vertex "
     If IfunAdr>0  { Call Vzero(xxf,6); Call JUMPT2(IfunAdr,xxf,yyf) }
*
     call RbPUSHd
     Lm=1;     USE  /DETM/AXXX/AgXX/AgCR  Cset=Cset   Stat=Ist
     If Ip>0 & Cset=='XTRT' & Ist==ok
     { Lm=-1;  USE  /DETM/AXXX/AgXX/AgCR  Oper=Next   Stat=Ist;  }
     call RbPOPd
     Check Ist==ok;  Nplane=agcr_Npl;  Itp=agcr_Itype;
     * let user a way to increase Lpack in AXXXREC
     Lpacki=Lpack;   If (Lpacku>0) Lpacki=Lpacku
 
     Call VZERO(Nvl,Nv);    Call Vzero(Isc,Nv);   Call Vzero(Digi,Nd)
     Cs=Agcr_Cset(1:3)//'D';  Cdet=Agcr_Cdet;  {K,Ia}=0
     Call AgFDIGI (Cs,Cdet,NVL,Ltra,ISC,Digi,K,Ia)
 
     If Ip<=0 { Ip=0;                Ip2=Nplane; Ids= 1; }
     else     { Ip=min(Ip,Nplane)+1; Ip2=1;      Ids=-1; }
     " start neighbour counting "    Modz=0;  Modf=0;   Jd=1;
  }
  Iprin=AgPFLAG(Cset,'RECO');     If (Iprin<0) { Ipp=-1; return }
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
  If (modz==0 & Modf==0) Ip+=Ids;  IpOld=Ip;
  For Ip=Ip to Ip2 by Ids
  {                            " extrapolate the track to the next plane  "
     itp   = Agcr_Itype;         rzp   = Agcr.rzp(ip)
     RZmin = Agcr.RZmin(ip);     RZmax = Agcr.RZmax(ip)
     Fmin  = Agcr.Fmin(ip);      Fmax  = Agcr.Fmax(ip)
     Dfi   = Agcr.dfi(ip);       dzr   = Agcr.dzr(ip)
     Tilt  = Agcr.tilt(ip);      Sas   = Agcr.Sas(ip)
     Nfi   = Agcr.Nfi(ip);       Nzr   = Agcr.Nzr(ip)
     Nump  = Agcr.Nump(ip);      Jres  = Agcr.Jres(ip)
     Fcent = Agcr.Fcent(ip);     Iadr  = Agcr.Iadr(ip)
*    print * ,ip,modz,modf
     If (Ip != IpOld) {modz=0;modf=0;IpOld=Ip} ! start new plane without mods
*
     xxf " Xopnt,Xrz,Xsas, Xzrc,Xphic,Xres " = {Itp, rzp,  0,0,  0,0};
     yyf " Yphi, Yzr,Ydphi,Ydzr,Ysign,Yres " = {0,0, TwoPi, big, 0,0};
     If (IfunAdr>0 " & modf==0 & modz==0 ")  Call JUMPT2(IfunAdr,xxf,yyf)
*
                                     "    select one phi sector (if>=0)     "
     if=0;  If Nfi>1 & dfi!=0
     { if0=nint((Yphi-(Fmin+Fmax)/2)/Dfi);  if=If0+modf;
       jf=sign(1.,Yphi-(Fmin+Fmax)/2-if0*Dfi)
     }
     Fc=Fcent+if0*Dfi;  Df=if*Dfi;  Yphi0=Yphi
     if Itp==1 & Tilt!=0 "& modf==0 & modz==0   extrapolation for tilt plane "
     { xxf(1)=1+tilt; xxf(5)=Fc; If (IfunAdr>0) Call JUMPT2(IfunAdr,xxf,yyf)  }
     Yphi+=nint((Yphi0-Yphi)/TwoPi)*TwoPi  "    keep Yphi in the same place  "
 
*
     If nfi>1  & dfi!=0                 "    rotate to the right sector     "
     {  check Fmin+Df-Ydphi <=Yphi&Yphi<= Fmax+Df+Ydphi;  Fcent+=Df; }
*
                                        "    select z/r-section (iz>=0)   "
     {i,iz}=0;   Mz=max(Itp,Nzr);   Mf=max(1,Nfi)
*
     If Itp==1                          "    this is a barrel detector    "
     {  If (dzr!=0) iz=min(max(0,nint((Yzr-(RZmin+RZmax)/2)/dzr)),Nzr-1)
*
*       Roads may produce iz detector variations at both sides around center
        kz=iz+modz;   If RZmin+kz*dzr-Ydzr <= Yzr&Yzr <= RZmax+kz*dzr+Ydzr
        {  " closest neighbour direction is " jd=sign(1.,2*Yzr-RZmin-RZmax)
           " check next detector in advance and save it for the next entry "
           do itry=1,2
           {  modz=-modz;  if (jd*modz>=0) modz+=jd;  jz=iz+modz
              If (0<=jz&jz<=Nzr-1) break;             jz=-1
           }
           If (jz<0 | RZmin+jz*dzr-Ydzr>Yzr | Yzr>RZmax+jz*dzr+Ydzr) modz=0
           iz=kz
        }
        else                             " no detector left in this layer "
        {  modz=0;
           If Cset=='XTRT' & Lm>=0
          {" we are in the TRT barrel here - this should be followed by endcap"
             If (Ids*Lm<0) Break;     Lm=-Lm;
 
          " backward tracing will be more complicate here - will do later(pn)"
            Call RBPUSHD
            If Lm>0  { USE /DETM/AXXX/AgXX/AgCR   Cset=Cset   Stat=Ist; }
            else     { USE /DETM/AXXX/AgXX/AgCR   Oper=Next   Stat=Ist; }
            Call RBPOPD
 
            If Ist!=ok { <w> ip; (' AggPlaNa error in XTRT plane=',i3); Break;}
            Nplane=agcr_Npl;  Itp=agcr_Itype
            If Ids>0   { Ip=0; Ip2=Nplane} else { Ip=Nplane+1; Ip2=1;}
            Next
        } }
     }
     else                                "    this is an end-cap detector  "
     {" Delta Z and reflections rules may be conflicting - have to check it"
        If  dzr!=0  { iz=nint((Yzr-Rzp)/dzr); iz=min(max(0,iz),Mz-1); }
        else        { iz=0;  if (Ysign<0) iz=1; }
        Check   Rzmin-Ydzr <= Yzr & Yzr <= RZmax+Ydzr
     }
*
     If nfi>1  & dfi!=0 & modz==0        "    rotate to the next sector    "
     {  modf=-modf;  if (jf*modF>=0) modf+=jf;  Df=(if0+modf)*Dfi
        Unless (Fmin+Df-Ydphi <=Yphi & Yphi<= Fmax+Df+Ydphi) modf=0
        if (abs(modf)>=Nfi/2) modf=0     " protect against infinite search "
     }
*
     iad=agcr.Iadr(ip)+mod(if+2*Mf,Mf)+iz*Mf+1  " if,iz have 0 offset here "
     Ipp=Ip*10000+mod(if+2*Mf,Mf)+iz*max(100,Mf)
 
                                        "  pick up hits in one board  "
     Ndig=0;  Id=0;  KK=agcr.Ibuf(iad);  Call Vzero(Digi,Nd)
     IF KK>0
     {  Ndig=mod(KK,Lpacki);  K=KK/Lpacki-1 " may start from zero ";
        Do N=1,Ndig
        {  Call  AgFDIGI (Cs,Cdet,NVL,Ltr,ISC,Digi,K,Ia)
           If k<=0
           { <w> Cs,Cdet,KK,Id,K,Ia,NVL; (' AggPlaNa logic error in',
              2(1x,a4),' KK,Id,K,Ia=',4i6/20x,' NVL=',10i4);   break;
           }
           Check Ltr>=0;   Id+=1;  Kdig(id)=k;  Ltra(id)=Ltr;
*
           Ktyp=Digi(1); Fdig(id)=Digi(2); Zdig(id)=Digi(3); Edig(id)=Digi(4);
           If Cset=='XTRT'        " dfi does not change sign for reflection?"
           {  Ktyp=Itp;   Fdig(id)=Fcent+dfi*(ISC(3)-1);
              Zdig(id)=Digi(2);  Edig(id)=Digi(1);
           }
           prin5 id,Ktyp,Fdig(id),Zdig(id),Edig(id);
           ('   digit id,ktyp,f,z,E = ',2i5,3f12.4);
           KtypDig(id)=Ktyp;  Nodig(id)=Digi(5)+.001;
        }
        Ndig=Id;  Call  AgFPATH (ISC);
        Ishape=Q(LQ(JGPAR-Nlevel)-4);   Npar=Q(LQ(JGPAR-Nlevel)-1);
        Call Ucopy(Q(LQ(JGPAR-Nlevel)+1),Par,min(Npar,50));	
        Call Ucopy(GTRAN(1,NLEVEL),AgTRAN,3);
        Call Ucopy(GRMAT(1,NLEVEL),AgRMAT,10);
     }
*    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     prin4 Cset,Ipp,Ndig; (' AgGPLANE: ',a4,' Ipp,Ndig =',2i12)
     prin8 ip,Ktyp,Ishape,Npar,(par(i),i=1,Npar)
     (' plane',2i4,'  Shape,Npar=',2i5,(' par=',10f8.3))
     prin6 tilt,sas,fcent; (' plane angles t,s,f(AggPlANa)',3F12.4)
     prin5 rzp,Yphi; ('   track at point   (FUNCT)  ',5F12.4);
     Return;                                                 :dummy:
  }
  Ipp=0
*
  END
 
*CMZ :  1.30/00 03/03/96  12.29.00  by  Pavel Nevski
*-- Author :    Pavel Nevski   03/03/96
*************************************************************************
*                                                                       *
                subroutine   A G S F U N C T (ext,ia)
*                                                                       *
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,agcrfun.
*     Road definition function and its parameters
      Integer          IFunAdr,IfunFlag
      Real             XXf(6),YYf(6),   Xopnt,Xrz,Xsas, Xzrc,Xphic,Xres,
     >                                  Yphi, Yzr,Ydphi,Ydzr,Ysign,Yres
      Common /AgCRFun/ IFunAdr,Ifunflag,Xopnt,Xrz,Xsas, Xzrc,Xphic,Xres,
     >                                  Yphi, Yzr,Ydphi,Ydzr,Ysign,Yres
      Equivalence      (XXf,Xopnt), (YYf,Yphi)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
   external   ext
   Integer    JUMPAD,IA
*
   IFunAdr  = JUMPAD(ext)
   IfunFlag = Ia
   end
 
 
*CMZ :          20/11/97  22.28.54  by  Pavel Nevski
*CMZ :  1.30/00 01/09/96  16.24.19  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
********************************************************************
*                                                                  *
               subroutine   F U M F I T (TAG,NPAR)
**DIRECTIVE RANGE ON
**DIRECTIVE CHECK_OVERFLOW INTEGER ON 	
*             LSQ track parameters fit to IHIT bank                *
*                                                                  *
* Original Version:                                   Pavel Nevski *
* Modifications:                                      Sasha Rozanov*
* PN, 20.11.97:  to accept big tilts in barrel OPNT (0-1.999)=> 1  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,IREPAR.
C  -   Fumfit control parameters
      INTEGER         IFSHOW,IFTIME,ICLEAN,IFBREM,
     >                IRC,NUV,NZM,JPR,NDF,NTR,IKINE,ISHOW
      REAL            BCONST,DBREM,CHI2,PTPR,SSHE0,UKINE,
     >                DA0,DZ0,DELCHI,CHIBAD,SIG0,DT0,XTR
      COMMON /IREDAT/ JPR,IFBREM,UKINE,IKINE,ISHOW,PTPR,SSHE0,
     >                DA0,DZ0,SIG0,DT0,DELCHI,CHIBAD
      COMMON /IREPAR/ BCONST,DBREM,IRC,CHI2,NDF,NUV,NZM,NTR,XTR,
     >                IFSHOW,IFTIME,ICLEAN
C---------------------------------------------------------------------
*KEEP,FUMUSE.
*   fumili users commons
      INTEGER         NA, NS, NP, NN, MM
      PARAMETER       (NA=10, NS=8, NP=400)
      REAL            EX,YY
      COMMON /FUMNED/ NN,MM
      COMMON /FEXDA/  EX(NS,NP)
      COMMON /FUMYY/  YY(0:NA,NP)
*     - - - - - - - - - - - - - - - - - - - -
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEEP,fumsva.
*   fumili parameters - in addition to FUMSIZE
      REAL         A0FIT,FI0FIT,PTINV,Z0FIT,DZDR0,RBREM,XBREM,RSHOW
      EQUIVALENCE (A0FIT,A(1)),(FI0FIT,A(2)),(PTINV,A(3)),(Z0FIT,A(4)),
     +            (DZDR0,A(5)),(RBREM,A(6)),(XBREM,A(7)),(RSHOW,A(8))
*     -----------------------------------------------------------
*KEEP,TRROAD.
*   - Track road parameters
      REAL            ESHE,FSHE,ZSHE,RSHE,SSHE,ZVRT,DZSIT,
     +                RRSTV,RRSIT,RRMSG,RRGAA,RRTRD,
     +                RFISTV,RFISIT,RFIMSG,RFIGAA,RFITRD
      INTEGER         IWRK
      COMMON /TRROAD/ IWRK,ESHE,FSHE,ZSHE,RSHE,SSHE,ZVRT,DZSIT,
     +                RRSTV(3),RRSIT(3),RRMSG(3),RRGAA(3),RRTRD(3),
     +                RFISTV(3),RFISIT(3),RFIMSG(3),RFIGAA(3),RFITRD(3)
      INTEGER         NTZ
      REAL            RTZ,ZTZ
      COMMON /TZROAD/ NTZ, RTZ(100),ZTZ(100)
*     --------------------------------
 
*KEEP,TRBANK.
*   - Track point bank
      INTEGER         LTB,NTB,LPNT,ISPOINT
      PARAMETER       (LTB=10000,LPNT=12)
      REAL            TRPOINT, DTRPOINT
      COMMON /TRBANK/ NTB,TRPOINT(LPNT,LTB)
* ISPOINT contains IPP={IP,IZ,IF} of counter, negative if point rejected
      COMMON /TRBANI/     ISPOINT(LTB)
* DTRPOINT contains the cluster position error (ask A.Rozanov for details)
      COMMON /TRBANJ/     DTRPOINT(LTB)
      REAL            OPNT,XPNT,DPNT,SPNT,APNT,EPNT,PPNT
      COMMON /TRKPNT/ OPNT,XPNT(3),DPNT,SPNT(2),APNT(3),EPNT,PPNT
*  1  : Opnt    - 1+tilt for barrel, 2 for end-caps
* 2-4 : Xpnt(i) - r,phi,z of the element center
*  5  : Dpnt    - stereo angle for strips, drift distance for TRT
* 6-7 : Spnt(i) - error in phi and Z/R
*  8  : Apnt(1) - detector code as follows
*  9  :     (2) - plane number in AgCRTAB
* 10  :     (3) - first digi reference number
* 11  : Epnt    - energy or discriminator value
* 12  : Ppnt    - MC reference track number
      REAL            PIXB,PIXE,GAAS,SCTT,ZSCT,SITV,SIT,MSGC,XTRT
      DATA            PIXB,PIXE,GAAS,SCTT,ZSCT,SITV,SIT,MSGC,XTRT
     +                / 1,   2,   3,   4,   5,   6,  7,   8,   9  /
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,TRCALO.
*   main calo parameters for tracking
      REAL            RCAL,     ZCAL,     YCAL
      DATA            RCAL/140/,ZCAL/360/,YCAL/1.4/
*     --------------------------------
 
*KEND.
* ----------------------------
 
      INTEGER     I,J,K,M,N,IW,II,I1,I2,IT,IPR,IFL,M1,IM,NPAR,Iprin
      REAL        FI,F1,F2,S,R,Z,D,AK,AL,XX(6),SS(-1:1),FUNCT,ORDER
      CHARACTER*6 TAG
      INTEGER     AgPFLAG,IOPNT,Nok,NDF0PR/0/
*
*     - - - - - - - - - - - - - - - - - - -
*     Order    <->     Option       R or Z
      ORDER(II) = 1000*Nint(EX(3,II))+ABS(EX(4,II))
*     - - - - - - - - - - - - - - - - - - -
 
      Iprin=AgPFLAG('FUMF','RECO')
      CALL VZERO (EX,NS*NP)
*     protect against bad call
      IF (NTB<=0) return
 
      MM   = NPAR
      NUV  = 0
      NZM  = 0
      NTR  = 0
      XTR = 0
*    vertex constrain
      M       = 1
      EX(1,M) = 0
      EX(2,M) = DA0
      EX(3,M) = 0
      EX(4,M) = 0
      FI      = FUNCT(EX(3,1))
      M       = 2
      EX(1,M) = 0
      EX(2,M) = DZ0
      EX(3,M) = 1
      EX(4,M) = 0
 
*   Loop here over IHIT bank and fill  FUMILIs EXDA
*   ------------------------------------------------
      Nok=0
      Prin9 ; ('FumFit called with these pts:')
      DO I = 1,NTB
 
         Check ISPOINT(i)==0
	 Nok+=1
	 Prin9 i; ('     entry ',I4)
 
         CALL UCOPY(TRPOINT(1,I),OPNT,LPNT)
         IOPNT=nint(OPNT);  If (0<OPNT&OPNT<1.999) IOPNT=1
	 Prin9 i,opnt,iopnt;  (' next point=',i5,f8.1,i5)
 
         IF (APNT(1)==0) THEN
*           this is the pointer (track/cluster), skip it
            RSHE = XPNT(1)
            FSHE = XPNT(2)
            ZSHE = XPNT(3)
            SSHE = SPNT(2)
            ESHE = EPNT
            NEXT
         ENDIF
         XX(1) = OPNT
         XX(3) = 0
         XX(4) = 0
         XX(5) = XPNT(2)
 
*      Check OPNT => fix r or z
         IF (IOPNT==1) THEN
*                               fix radius data
*                               ===============
            XX(2) = XPNT(1)
            FI    = FUNCT(XX)
            XX(2) = 0
            Z     = FUNCT(XX)
            R     = XPNT(1)
 
         ELSEIF(IOPNT==2)THEN
*                                 fix z- data
*                                 ===========
            XX(2) = XPNT(3)
            FI    = FUNCT(XX)
            XX(2) = 0
            R     = FUNCT(XX)
            Z     = XPNT(3)
 
         ELSE
            prin0 (TRPOINT(J,I),J=1,LPNT)
            (' FUMFIT: bad point in TRBANK',12F10.4)
            NEXT
         END IF
 
 
*       protection against EXDA overflow
        if(M.GE.NP)then
           prin0 I,NTB,M,NP
           (' fumfit: dimension of exda is too small, i,ntb,m,np=',6i6)
           Next
        endif
 
*       push point into fumilis common
 
         M       = M+1
         N       = 1
         EX(1,M) = XPNT(2)
         EX(2,M) = SPNT(1)/R
         EX(3,M) = OPNT
         EX(5,M) = 0
         EX(6,M) = 0
         EX(7,M) = 0
 
*      Check OPNT==1  r/z
         IF (IOPNT==1) THEN
            EX(4,M) = XPNT(1)
         ELSE
            EX(4,M) = XPNT(3)
         END IF
 
*      Check APNT(1) = MSGC   - u/v angle in R
         IF (APNT(1)==MSGC) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(1)
         END IF
 
*      Check APNT(1) = SCTT    - u/v angle in Z
         IF (APNT(1)==SCTT) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(3)
*           fi of center for tilt
            EX(7,M) = XPNT(2)
         END IF
 
*      Check APNT(1) = SITV    - cross-strips
         IF (APNT(1)==SITV) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(3)
*           fi of center for tilt
            EX(7,M) = XPNT(2)
         END IF
 
*      Check APNT(1) = PIXB    - pixels
         IF (APNT(1)==PIXB) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(3)
*           fi of center for tilt
            EX(7,M) = XPNT(2)
         END IF
 
*      Check APNT(1) = GAAS    - u/v angle in Fi
         IF (APNT(1)==GAAS) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(1)
         END IF
 
*      Check APNT(1) = ZSCT    - u/v angle in Fi
         IF (APNT(1)==ZSCT) THEN
            EX(5,M) = DPNT
            EX(6,M) = XPNT(1)
         END IF
 
*        u/v measurements
*        ----------------
         IF (APNT(1).NE.XTRT  &  DPNT.NE.0)NUV = NUV+1
 
*        precize z measurements
*        ----------------------
         IF (SPNT(2) <= SPNT(1))NZM = NZM+1
 
*      Check APNT(1)==XTRT - resolve the left/right ambiguity in some way
 
         IF (APNT(1)==XTRT) THEN
            NTR = NTR + 1
            IF (EPNT<0) XTR = XTR + 1
            IT  = 0
*         Check 1<I&I<NTB & IFTIME==1                   - locally
            IF (1<I & I<NTB  &  IFTIME==1) THEN
               SS(-1) = 0
               SS(+1) = 0
*            Loop here
               DO 21 I1 = -1,1,2
*               Loop here
                  DO 31 I2 = -1,1,2
                     F1 = XPNT(2)+I1*DPNT/R
*                  Loop here
                     DO 41 J = I-1,I+1,2
                        F2 = TRPOINT(3,J)+I2*TRPOINT(5,J)/R
                        IF (ABS (F1-F2)*R<DT0)SS(I1) = SS(I1)+1
41                   CONTINUE
31                CONTINUE
21             CONTINUE
 
*            Check (SS(-1) = 2 & SS(+1) = 0)    - left
               IF (SS(-1)==2  &  SS(+1)==0) THEN
                  IT = -1
               END IF
 
*            Check (SS(+1) = 2 & SS(-1) = 0)    - right
               IF (SS(+1)==2  &  SS(-1)==0) THEN
                  IT = +1
               END IF
            END IF
 
*         Check IFTIME==2                          - or globally
            IF (IFTIME==2) THEN
*            Check XPNT(2)<FI
               IF (XPNT(2)<FI) THEN
                  IT = +1
               ELSE
                  IT = -1
               END IF
            END IF
*         Check IT#0
            IF (IT.NE.0) EX(2,M) = .02/R
            EX(1,M) = EX(1,M)+IT*DPNT/R
            TRPOINT(12,I) = IT
         END IF
	 prin9 M,(EX(K,M),K=1,7); (' point m:', i6,10F10.3)
 
*       Add 2nd coordinate measurment if it is good enouph
*       --------------------------------------------------
 
         IF (SPNT(2)<SIG0) THEN
            M       = M+1
            N       = 2
            EX(2,M) = SPNT(2)
            EX(3,M) = OPNT
            EX(4,M) = 0
*         Check OPNT==1/2         ->    r/z
            IF (IOPNT==1) THEN
               EX(1,M) = XPNT(3)
            ELSE
               EX(1,M) = XPNT(1)
            END IF
            prin9 M,(EX(K,M),K=1,7); (' point m:', i6,10F10.3)
         END IF
 
 
*      Now reshuffle in increasing order - any Z is always bigger than any R
*      ----------------------------------------------------------------------
 
*      Loop here over new points
         DO K = 1,M-N
*           Skip second component and right order
            Prin9 k,Order(k); ('FumFit: K=',I4,' Order=',3F12.4)
            IF (EX(4,K)==0 | ORDER(K)<=ORDER(M-N+1)) NEXT
*           Loop here over old points
            DO 61 IW = 1,N
*              swap points
               DO 71 J = M,K,-1
71             CALL UCOPY(EX(1,J),EX(1,J+1),ns)
               CALL UCOPY(EX(1,M+1),EX(1,K),ns)
61          CONTINUE
            CALL VZERO(EX(1,M+1),ns)
            BREAK
 
         ENDDO
 
      enddo
 
      If Nok==0 { Print *,'FUMFIT ERROR: no points selected'; Goto 999; }
 
      prin9 (j,(EX(I,J),I=1,7),j=1,M)
            (' FUMFIT After ordering:'/(' fumfit j,ex=',i4,7F12.4))
*   ...
* ---------------------------------------------------------
*   ... ADD POINT FROM THE CALORIMETER (or other road pointer)
* ---------------------------------------------------------
*   ...
*   Check IFSHOW # 0 - if needed !
      IF (IFSHOW .NE. 0) THEN
*      Check RSHE==RCAL     r or z ?
         IF (RSHE==RCAL) THEN
            M       = M+1
            EX(1,M) = FSHE
            EX(2,M) = SSHE/RSHE
            EX(3,M) = 11
            EX(4,M) = RSHE
            M       = M+1
            EX(1,M) = ZSHE
            EX(2,M) = 200
            EX(3,M) = 1
            EX(4,M) = 0
         ELSE
            M       = M+1
            EX(1,M) = FSHE
            EX(2,M) = SSHE/RSHE
            EX(3,M) = 12
            EX(4,M) = ZSHE
            M       = M+1
            EX(1,M) = RSHE
            EX(2,M) = 200
            EX(3,M) = 2
            EX(4,M) = 0
         END IF
      END IF
*   ...
* ---------------------------------------------------------
*   FIT WITH FUMILI AND PRINT RESULTS
* ---------------------------------------------------------
*   ...
      CALL FUMSIZE           ! set steps for:
      PL0(1) = .01           !  A0
      PL0(2) = .01           !  F0
      PL0(3) = .01           !  1/pT
      PL0(4) = 1             !  z0
      PL0(5) = .1            !  dz/dR
      PL0(6) = 10            !  R brem
      AMN(6) =  1            !
      AMX(6) = 100           !
      PL0(7) = .01           ! and Xbrem
 
*   Check (MM>5 & XBREM==0)  - set first approximation for brem
 
      IF (MM>5  &  XBREM==0) THEN
         XBREM = DBREM
         RBREM = 12          ! better then nothing !
 
*        the most secret formula, no comments
         D = XBREM/RSHOW/(RBREM-RSHOW)/BCONST*2
         PTINV = PTINV-D
      END IF
 
*   Check XBREM>0 - fix its sign forever
      IF (XBREM>0) THEN
         AMN(7) = 0.
         AMX(7) =  100
      ELSE
         AMN(7) = -100
         AMX(7) =  0.
      END IF
 
      NN = M
      M1 = MIN(MM,5)
* try:
       IPR = -1
*      IF (MM==7)IPR = JPR
*     IPR=JPR
 
*   ===============================================
*   everything ready,      F I R E  !!!!!!
*   ===============================================
 
90    CONTINUE
 
 
	Prin9 Irc,IPR; ('IRC,IPR=',2I4);
 
      DO 91 IM = 1,3
*        Check MM>6 - go slowly, help FUMILI  manually
         IF (MM>6) CALL FUMILI (S, 6,2,2,30,0.1,AK,AL, -1,IRC)
                   CALL FUMILI (S,MM,2,2,30,0.1,AK,AL,IPR,IRC)
         Chi2=2*S
*        Check TAG=='best'&IPRIN>=2 \ IPRIN>=3  - trace fitting results
         IF (TAG=='best' & IPRIN>=2  |  IPRIN>=3) _
         <w> TAG,IRC,NTB,M,NZM,NUV,CHI2,1/PTinv,Fi0FIT,Z0FIT,XBREM,RBREM
         (1X,A6,' Irc,n,m=',5I4,' Chi2,Pt,fi0,Z0,X-Rbrem fitted=',F15.3,5F8.3)
*        calculate real NDF - number od degree of freedom
         NDF = -MM
         DO I = 1,NN  { IF (EX(2,I)<10) NDF+=1; }
*
*        Loop here over all points and select good
*        Check CHI2 <NDF*1.5  - good enouph, no clean up
         IF (CHI2<NDF*1.5) ICLEAN = 0
*        clean up if necessery
         IF (ICLEAN==0) GO TO 92
         CALL FUMCLEAN(IFL)
*        and if cleaned up, repeat fit
         IF (IFL==0) GO TO 92
*
91    CONTINUE
92    CONTINUE
 
      If NDF!=0 { A(10) = CHI2/NDF ; }
      Else      { A(10)=99999.; NDF0PR+=1;
                  If (NDF0PR<100) Print *,'FumFit: NdF=0 Chi2=',Chi2 ; }
 
      Prin5 chi2,ndf,a(10);
      (' FumFit: Chi2=',F8.1,' NdF=',I6,' Chi2/NdF=',F6.1)
*
*     TR signature
      IF (NTR>0) XTR = XTR/NTR
 
*     may be used in case of problems
*      IF (IGRAP>=2) CALL TRPLOT
 
999   Continue;
 
      END
 
 
*CMZ :  1.30/00 13/03/95  23.59.17  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
      SUBROUTINE FUMCLEAN (IFL)
********************************************************************
*                                                                  *
*                    F U M C L E A N (IFL)
*                                                                  *
* Original Version:                                   Pavel Nevski *
* Modifications:                                      Never done   *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMUSE.
*   fumili users commons
      INTEGER         NA, NS, NP, NN, MM
      PARAMETER       (NA=10, NS=8, NP=400)
      REAL            EX,YY
      COMMON /FUMNED/ NN,MM
      COMMON /FEXDA/  EX(NS,NP)
      COMMON /FUMYY/  YY(0:NA,NP)
*     - - - - - - - - - - - - - - - - - - - -
*KEND.
 
*
      INTEGER   I,IM,IFL
      REAL      Y,CH2,CHMAX,FUNCT
      EXTERNAL  FUNCT
*
      CHMAX=0
      IFL=0
*
*   Loop here over points (do not through the last) and find the worst one
*
      DO I=1,NN-2
      {   Y=FUNCT(EX(3,I))
         Check I>2
         CH2=ABS((EX(1,I)-Y)/EX(2,I))
         Check CH2>CHMAX
         IM=I
         CHMAX=CH2
      }
      Check CHMAX>5.0
      EX(2,IM)=100*EX(2,IM)
*     Print *,' measurement rejected:', im,(EX(i,im),i=1,4),Chmax;
      IFL=IFL+1
      END
 
*CMZU:  1.00/01 25/01/96  22.22.59  by  Pavel Nevski
*CMZ :  1.00/00 04/10/95  19.58.59  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
*************************************************************************
*                                                                       *
                subroutine   A G P L A N E (Cset,Ip)
*                                                                       *
*************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,agcrtab.
*
*     Commons for the inner detector digi reconstruction
      Integer           Lstack,     Lr,   Lhead,   Lpack
      Parameter        (Lstack=2000,Lr=15,Lhead=52,Lpack=512)
*
*                                            subsystem descriptor
      Integer          Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,NumPmx,
     +                 Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires, nam,nmx
      Real             Rstack,drzm,RRmin,RRmax,ZZmin,ZZmax
*
      Common /AgCRtab/ Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,drzm,
     +                 RRmin,RRmax,ZZmin,ZZmax,
     +                 NumPmx,Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires,
     +                 Nam(15),Nmx(15),  Rstack(Lr,Lstack)
      Integer                            Istack(Lr,Lstack)
      Equivalence      (Rstack,Istack)
*                                            plane descriptor
      Real             rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent
      Integer          Nfi,Nzr,Nump,Iadr,Jres,Lpacku
      Common /AgCRta1/ rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent,
     +                 Nfi,Nzr,Nump,Iadr,Jres,Lpacku
*                                            detector size
      Integer          Ishape,Npar
      Real                         AgTran,   AgRmat,    Par
      Common /ARCplan/ Ishape,Npar,AgTran(3),AgRmat(10),Par(50)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
*KEEP,agcclus.
*                                            clustering bank
      Integer          Ndig,Ktyp,Lh,Nclu,Kdig,Ltra,Ktypdig,Nodig
      Real                          Fdig,Zdig,Edig
      Parameter        (Lh=1024)
      Common /ARCdigt/ Ndig,Ktyp,Fdig(Lh),Zdig(Lh),Edig(Lh),
     +                           Nclu(Lh),Kdig(lh),Ltra(Lh)
      COMMON /AGCCLUS/ Ktypdig(Lh),NoDig(Lh)
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEEP,HELVAR.
*--   helix parameters
      LOGICAL                                           TRAPPED
      REAL            BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL
      COMMON /HELVAR/ BCONST,XS,YS,ZS,RS,CF,SF,TL,TT,EL,TRAPPED
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
  INTEGER      NV,Nd;          PARAMETER   (NV=10,Nd=10);
  Integer      NVL(NV),ISC(NV),K,L,Ia,Iad,ip,Iz,Jz,kz,If,i,id,Lm,kk,Jd,
               AgPFLAG,Iprin,Ids,Ip2,Mz,Mf,modz,itry
  Real         DIGI(Nd),Fi,ZR,x(6),FUNCT,Fc,Df,Dz
  Character*4  Cset,Cdet,Cs
  Save         x,NVL,Cdet,Cs,Iprin,Ids,Ip2,Lm,Modz,Jd
*
*                                       for the first plane, get tables
;
  {Ndig,Ktyp}=0
;
  If Ip<=0 | Ip >999 | Cset(1:3)!=Cs(1:3)
  {  " start track at the vertex "
     Call Vzero(x,6);       Fi=Funct(x);
     Lm=Lhead+Lr*Lstack;    Call ASLGETBA (Cset,'RMAP',Lm,L,Isys);
     If Ip>0   { Lm=-Lm;    Call ASLGETBA (Cset,'RMAP',Lm,L,Isys);}
     Check  L>Lhead;
     Call VZERO(Nvl,Nv);    Call Vzero(Isc,Nv);   Call Vzero(Digi,Nd)
     Cs=Cset(1:3)//'D';     Call UHTOC(Inamd,4,Cdet,4);     {K,Ia}=0
     Call AgFDIGI (Cs,Cdet,NVL,Ltra,ISC,Digi,K,Ia)
     If Ip<=0 { Ip=0;                Ip2=Nplane; Ids=1;  }
     else     { Ip=min(Ip,Nplane)+1; Ip2=1;      Ids=-1; }
     " start neighbour counting "    Modz=0;  Jd=1;
     Iprin=AgPFLAG(Cset,'RECO')
  }
  If (Iprin<0) Return
*
  If (modz==0)  Ip+=Ids
  For Ip=Ip to Ip2 by Ids
  {                            " extrapolate the track to the next plane  "
     Call Ucopy(Rstack(1,Ip),rzp,Lr)
     Call Vzero(x,6);       x(1)=Itp;
     x(2)=rzp;  If (Itp==2) x(2)=sign(rzp,TL);
     Fi=Funct(x)
     Df=1.0/rs;  Dz=20;
                                     "    select one phi sector (if>=0)   "
     if=0;    If (dfi#0) if=nint((Fi-(Fmin+Fmax)/2)/Dfi);   Fc=Fcent+if*Dfi;
     if Itp=1 & Tilt#0   { x(1)=1+tilt; x(5)=Fc; Fi=Funct(x); }
     If nfi>1  { check Fmin+if*Dfi-Df <= Fi&Fi <= Fmax+if*Dfi+df; Fcent=Fc; }
*
                                        "    select z/r-section (iz>=0)   "
     {i,iz}=0;   x(2)=0;  ZR=Funct(x)
     Mz=max(Itp,Nzr);   Mf=max(1,Nfi)
     If Itp==1                          "    this is a barrel detector    "
     {  If (dzr!=0) iz=min(max(0,nint((ZR-(RZmin+RZmax)/2)/dzr)),Nzr-1)
        * Print *,' AgPLANE: ip,rzp,if,iz=',ip,rzp,if,iz,Rzmin,Rzmax,dzr
*
*       Roads may produce iz detector variations at both sides around center
        kz=iz+modz;  If RZmin+kz*dzr-dz <= ZR&ZR <= RZmax+kz*dzr+dz
        {  " closest neighbour direction is "  jd=sign(1.,2*ZR-RZmin-RZmax)
           " check next detector in advance and save it for the next entry "
           do itry=1,2
           {  modz=-modz;  if (jd*modz>=0) modz+=jd;  jz=iz+modz;
              If (0<=jz&jz<=Nzr-1) break;             jz=-1
           }
           If (jz<0 | RZmin+jz*dzr-dz>ZR | ZR>RZmax+jz*dzr+dz) modz=0;
           iz=kz;  * print *,'          itry,modz,iz,jz=', itry,modz,iz,jz
        }
        else                             " no detector left in this layer "
        { modz=0;  If (Cset!='XTRT' | Lm<0) Next
          " we are in the TRT barrel here - this should be followed by endcap"
          " backward tracing will be more complicate here - will do later(pn)"
          If (Ids*Lm<0) Break;       Lm=-Lm
          Call ASLGETBA (Cset,'RMAP',Lm,L,Isys)
          If L<0    { <w> ip; (' AgPLANE error in XTRT plane=',i3); Break; }
          If Ids>0  { Ip=0; Ip2=Nplane; }    else    { Ip=Nplane+1; Ip2=1; }
          Next
        }
     }
     else
     {" Delta Z and reflections rules may be conflicting - have to check it"
        If  dzr!=0  { iz=nint((ZS-Rzp)/dzr); iz=min(max(0,iz),Mz-1); }
        else        { iz=0;  if (ZS<0) iz=1; }
     }
     iad=Istart+Iadr+mod(if+Mf,Mf)+iz*max(1,Mf)
*
                                        "  pick up hits in one board  "
     Ndig=0;  KK=Ibuf(iad+1);
     IF KK>0
     {  Ndig=mod(KK,Lpack);  K=KK/Lpack-1 " may start from zero ";
        Do Id=1,Ndig
        {  Kdig(id)=k; Call  AgFDIGI (Cs,Cdet,NVL,Ltra(id),ISC,Digi,K,Ia);
           If k<=0
           { <w> Cs,Cdet,KK,Id,K,Ia,NVL; (' AgPLANE logic error in',
              2(1x,a4),' KK,Id,K,Ia=',4i6/20x,' NVL=',10i4);  break;
           }
           Ktyp=Digi(1); Fdig(id)=Digi(2); Zdig(id)=Digi(3); Edig(id)=Digi(4);
           If Cset=='XTRT'
           {  Ktyp=Itp;  Fdig(id)=Fcent+dfi*(ISC(3)-1);
              Zdig(id)=Digi(2);  Edig(id)=Digi(1);
           }
           prin5 id,Ktyp,Fdig(id),Zdig(id),Edig(id);
           ('   digit id,ktyp,f,z,E = ',2i5,3f12.4);
        }
        Call  AgFPATH (ISC);
        Ishape=Q(LQ(JGPAR-Nlevel)-4);   Npar=Q(LQ(JGPAR-Nlevel)-1);
        Call Ucopy(Q(LQ(JGPAR-Nlevel)+1),Par,min(Npar,50));	
        Call Ucopy(GTRAN(1,NLEVEL),AgTRAN,3);
        Call Ucopy(GRMAT(1,NLEVEL),AgRMAT,10);
     }
     prin8 Cset,ip,Ktyp,Ndig,Ishape,Npar,(par(i),i=1,Npar);
     (1x,a4,' plane',2i4,' Ndig=',i4,'  Shape,Npar=',2i5,(' par=',10f8.3));
     prin6 tilt,sas,fcent; (' plane angles t,s,f(AgPLANE) ',3F12.4);
     prin5 xs,ys,zs,rs,fi; ('   track at point   (FUNCT)  ',5F12.4);
     Return;                                                 :dummy:
  }
  Ip=0;
*
  END
 
 
*CMZ :  1.00/00 17/09/95  22.47.16  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
************************************************************************
*                                                                      *
                subroutine    A R C L U S (Par,Key)
*                                                                      *
* description:  SMEAR CLOSE HITS. key>0 - 2 dimensional pixels         *
*                                 key<0 strips                         *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,agcclus.
*                                            clustering bank
      Integer          Ndig,Ktyp,Lh,Nclu,Kdig,Ltra,Ktypdig,Nodig
      Real                          Fdig,Zdig,Edig
      Parameter        (Lh=1024)
      Common /ARCdigt/ Ndig,Ktyp,Fdig(Lh),Zdig(Lh),Edig(Lh),
     +                           Nclu(Lh),Kdig(lh),Ltra(Lh)
      COMMON /AGCCLUS/ Ktypdig(Lh),NoDig(Lh)
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
*
  INTEGER    Itype,Key,MM,MY,MZ,ID,JD,IT,IND,JND,NN
  Real       Par(3),Dfp,Dzp,SE,SY,SZ
*
    Itype = nint(Par(1))
    Dfp   = Par(2)
    Dzp   = Par(3)
    If Itype=1 { "pixel" If Dfp<Dzp { Key=1 } else {Key=2 }; MM=100000}
    else       { "s.s.s" If Dfp<Dzp { Key=-1} else {Key=-2}; MM=0 }
 
*   select direction of clustering
    IF Dfp<Dzp {"Phi measurement, strips or pads in z (or R)" MY=1; MZ=MM;}
    else       {"z (or R) measurement, strips or pads in Phi" MY=MM; MZ=1;}
*
    DO ID=1,Ndig
    {   Check Edig(Id)>0
        IND=nint(Fdig(ID)/dfp+0.5)*MY+nint(Zdig(ID)/dzp+0.5)*MZ;
        { NN,SE,Sy,Sz }=0;    IT=Ltra(ID);
        DO JD=ID,Ndig
        {  Check Edig(JD)>0
           JND=nint(Fdig(JD)/dfp+0.5)*MY+nint(Zdig(JD)/dzp+0.5)*MZ;
                                     "   check if hits are adjacent   "
           IF JND=IND
           {  NN+=1;            IND+=1;
              SE+=Edig(JD);     SY+=Fdig(JD);    SZ+=Zdig(JD);
              IF (IT!=Ltra(Jd)) IT=0;            Edig(JD)=0;
        }  }
        Edig(Id)=SE; Fdig(Id)=SY/NN; Zdig(Id)=SZ/NN; Nclu(Id)=NN; Ltra(Id)=IT;
    }
  END
 
*CMZ :  1.30/00 08/09/96  13.33.40  by  Pavel Nevski
*CMZU:  1.00/01 21/12/95  13.52.03  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
*************************************************************************
*                                                                       *
                subroutine   A g D e c o d e (Cdet,itype)
*                                                                       *
* Description:                                                          *
*   Geometry of a given sensetive detector is generalised in a table.   *
*   Each table line repersent a hyper-plane (repetetive elements) with  *
*   known periodicities in phi and z.                                   *
*   If itype is more than 10, only elements with this serial number     *
*   are scanned.                                                        *
*   Z periodicity may be approximative (dz-rule) or be a reflection     *
*   In the first case detectors should be always position from left to  *
*   right sequentially, in the second - always starting from innermost  *
*   pair (or center), otherwise problems may arise.                     *
* known problems:                                                       *
*   It is not yet as versatile as one may think, this will come         *
*************************************************************************
Replace[ERR(#)]   with _
       [{<W> Cdet; (' error in AgDECODE for detector ',a4,2x,'#1'); RETURN;}]
*
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcrtab.
*
*     Commons for the inner detector digi reconstruction
      Integer           Lstack,     Lr,   Lhead,   Lpack
      Parameter        (Lstack=2000,Lr=15,Lhead=52,Lpack=512)
*
*                                            subsystem descriptor
      Integer          Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,NumPmx,
     +                 Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires, nam,nmx
      Real             Rstack,drzm,RRmin,RRmax,ZZmin,ZZmax
*
      Common /AgCRtab/ Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,drzm,
     +                 RRmin,RRmax,ZZmin,ZZmax,
     +                 NumPmx,Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires,
     +                 Nam(15),Nmx(15),  Rstack(Lr,Lstack)
      Integer                            Istack(Lr,Lstack)
      Equivalence      (Rstack,Istack)
*                                            plane descriptor
      Real             rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent
      Integer          Nfi,Nzr,Nump,Iadr,Jres,Lpacku
      Common /AgCRta1/ rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent,
     +                 Nfi,Nzr,Nump,Iadr,Jres,Lpacku
*                                            detector size
      Integer          Ishape,Npar
      Real                         AgTran,   AgRmat,    Par
      Common /ARCplan/ Ishape,Npar,AgTran(3),AgRmat(10),Par(50)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
*KEND.
Integer       LOCF,LENOCC,ICDECI,Itype,Js,Jd,Jdu,i,j,k,i1,i2,L,LL,p,N,
              Lv,Iv,Jv,Jvo,ip,it,iz,ir,mm,nz,Iax,Ish,Imo,Ivo,Jm,In,Jn,Nin,
              Nr,Name,Nick,ier,Natt,Nvr,Nvb,Nb,kk0,jj,JATTF,serial,
              Ndv(2),Nvl(15),Lnam(15),Ivol(15),NwuVol/3/,Irot/0/
Real          VMOD,ATAN2,c0(2),st(2),Att(20),pp(3),p0(3),xyz(3),e1,e2,e3,d2m,
              r,f,z,v,Rmin,Rmax,Zmin,Zmax,d1,d2,d3,pt,pr,pz,ptm,prm,pzm,ds,es,
              zero(3)/3*0./,eps/1.e-4/
Character     Cdet*(*),Cs*4,cd*4
JATTF(Jj)  =  Jj+int(Q(Jj+5))+6
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*   Routine is not fully reentrant when geometry is changed (Irot...)   *
  L=0;  If  (JROTM>0 & Irot>0)               L=LQ(JROTM-Irot)
        If  (L>0 & Q(L+1)+Q(L+5)+Q(L+9)!=3)  L=0
*
  If L==0                                     " no rotation matrix "
  {  N=0;  If (JROTM>0) N=IQ(JROTM-2)
     Do Irot=1,N+1 { If (LQ(JROTM-Irot)<=0 | Irot>N) Break; }
     call GSROTM (Irot,90.,0.,90.,90.,0.,0.)
  }
*                                       first, make a set up
  call Vzero(ISYS,Lhead);   Check Jset>0;   Itp=mod(Itype-1,2)+1;
  " get level offset from the detector name "
  Nvr=0; if (Lenocc(Cdet)>=6) Nvr=ICDECI(Cdet,5,6);
  RRmin=10000;  ZZmin=10000;
 
*                                       find the set/det and its user bank
  :set: DO Iset=1,IQ(Jset-1)                                 " Over Nset "
  {  JS=LQ(Jset-Iset);   Check JS>0;  Call UHTOC (IQ(Jset+Iset),4,Cs,4);
     :det: DO Idet=1,IQ(LQ(Jset-Iset)-1)                     " Over Ndet "
     {  JD=LQ(JS-Idet);  Check JD>0;  Call UHTOC (IQ(JS + Idet),4,Cd,4);
        Check Cdet(1:4)=cd;   JDU=LQ(JD-3);    Check JDU>0;    goto :F:;
  }  }  Return;                                                     :F:
*
*              now unpack the tree info and find the known periodicities
*              using generic volumes only ( to avoid to much scanning )
  i1=Q(Jdu+3); i2=Q(Jdu+5); {k,kkk,kfi,krz,kk0}=0;  Nvb=Q(Jdu+6)+Nvr; d2m=0;
  do i=i1,i2-1,NwuVol
  {  kkk+=1;  j=jdu+i;  iv=Q(j+1);  Nmx(kkk)=Q(j+2);  Nam(kkk)=IQ(Jvolum+iv);
     Nb=Q(j+3);   If (Nb>0) K+=1;   if (K<=Nvb) kk0=kkk;
     jv=LQ(Jvolum-iv); nin=Q(jv+3); Ish=Q(jv+2);
     if nin<0
     {  jd=LQ(jv-1); Iax=Q(jd+1);
        If Iax=2 & (5<=Ish&Ish<=8 | 11<=Ish&Ish<=12)        " phi-divisions"
        {  If kfi#0  { <w> Cdet,kkk,nam(kkk); (' error in agdecode for ',a4,
                      ' at level',i5,2x,a4,' many phi divisions');   next;
        }  kfi=kkk+1;}
        else                                                " z-divisions "
        {  If krz#0  { <w> Cdet,kkk,nam(kkk); (' error in agdecode for ',a4,
                      ' at level',i5,2x,a4,' many  z  divisions');   next;
        }  krz=kkk+1; }
  }  }
*                                                   dont scan known things
  if (kfi#0) Nmx(kfi)=-Nmx(kfi);  if (krz#0) Nmx(krz)=-Nmx(krz);
*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
  { c0(1),c0(2),st(1),st(2),Ndv(1),Ndv(2) }=0;
  LL=1;  Nvl(1)=0;  Ivol(1)=Q(Jdu+i1+1);  Lnam(1)=IQ(Jvolum+Ivol(1));
  :LL: while LL>0
  { NVL(LL)+=1 ;    if NVL(LL)>max(1,Nmx(LL)) { LL-=1; Next; }
    Lv=LL; LL=kkk;  do i=Lv+1,kkk             { NVL(i)=1; }
    Call Vzero(rzp,Lr);
    :L: Do L=Lv,kkk                    " encode the nickname path    "
    {  If (L=1) Next;  Imo=Ivol(L-1);  Jm=LQ(JVOLUM-Imo); nin=Q(Jm+3);
       p=0;  if  nin<0 & L=kfi {p=1}  else  if  nin<0 & L=krz  {p=2};
       if p>0                         " save steps for periodicities "
       { jd=LQ(Jm-1);  Ndv(p)=Q(jd+3); C0(p)=Q(jd+4); St(p)=Q(jd+5); }
       do in=1,max(nin,1)             " find next nickname content   "
       {  jn=LQ(Jm-in);  Ivo=Q(jn+2);  Jvo=LQ(JVOLUM-Ivo);  Nr=Q(jn+3);
          Name=IQ(jvo-4); Nick=IQ(JVOLUM+Ivo); Ish=Q(jvo+2);
          Serial=Q(JATTF(jvo)+10)
          Check   nam(L)=Name     | nam(L)=Nick;
          Check   nin>0&Nvl(L)=Nr | nin<0&Nvl(L)<=Nr;
          Lnam(L)=IQ(JVOLUM+Ivo);    Ivol(L)=Ivo;     Next :L:;
       }  LL=L-1; Next :LL:;
    }
  * make device typing stronger - skip elements which do not fit definition
    If (Itype>2 & Serial!=Itype) Next
    call GLVOLU(kkk,Lnam,NVL,ier);  call GDTOM(zero,xyz,1);
  *
  * copy the current rotation into a working matrix
    call Ucopy  (GRMAT(1,kkk),Q(LQ(Jrotm-Irot)+1),10)
    call GFIPAR (jvo,jn,in,Npar,Natt,Par,att)
    call GFLRAD (4,ish,Irot,GTRAN(1,kkk),Par,Rmin,Rmax,ier)
    call GFLPHI (  ish,Irot,GTRAN(1,kkk),Par,Fmin,Fmax,ier)
    call GFLCAR (3,ish,Irot,             Par,Zmin,Zmax,ier)
    If (Fmin>Fmax) Fmin-=360
    Fmin*=DegRad;                         Fmax*=DegRad;
    Zmin+=GTRAN(3,kkk);                   Zmax+=GTRAN(3,kkk);
    RRmin=min(RRmin,Rmin);                RRmax=max(RRmax,Rmax);
    ZZmin=min(ZZmin,abs(Zmin),abs(Zmax)); ZZmax=max(ZZmax,abs(Zmin),abs(Zmax))
  *
    r=vmod(xyz,2);     z=xyz(3);     f=0;    Jres=Serial;
    if r>0 { f=atan2(xyz(2),xyz(1)); if (f<0) f+=2*pi; };  Fcent=f;
    " tilt is a dfi/dr - angle between plane normal and radius to it center"
    " sas  is a dfi/dz - tangent component of a local axial vector "
    { ir,it,iz,prm,ptm,pzm,tilt,sas }=0
    do i=1,3
    { Call Vzero(p0,3);   p0(i)=1;   call GDTOM(p0,pp,2);   v=Vmod(pp,2);
      pr=xyz(1)*pp(1)+xyz(2)*pp(2);  pt=xyz(1)*pp(2)-xyz(2)*pp(1);  pz=pp(3);
      If abs(pr)>prm  { ir=i; prm=abs(pr); Tilt=pt/(r*v); }
      If abs(pt)>ptm  { it=i; ptm=abs(pt); }
      If abs(pz)>pzm  { iz=i; pzm=abs(pz); }
    } sas=GRMAT("iz" 3+3*(it-1),kkk);  Iaxr=ir; Iaxt=It; Iaxz=Iz;
    *
    *                    make a new entry
    if Itp=1
    {  drzm=max(drzm,Rmax-Rmin);  rzp=r; Rzmin=Zmin; RZmax=Zmax; }
    else
    {  drzm=max(drzm,Zmax-Zmin);  rzp=z; RZmin=Rmin; RZmax=Rmax; }
 
    If kfi!=0   { Nfi=Ndv(1);  Dfi=sign(st(1),GRMAT(9,kfi))*DegRad; }
    If krz!=0   { Nzr=Ndv(2);  Dzr=st(2); }
    Nump=0;  do i=1,kkk { check Nmx(i)>1;  Nump*=Nmx(i)+NVL(i)-1; }
    *
    *                    put it in the table
    DFN [I_[NAME]]  as  [ Istack(LOCF(#1)-LOCF(rzp)+1,ip) ]
    DFN [R_[NAME]]  as  [ Rstack(LOCF(#1)-LOCF(rzp)+1,ip) ]
    do ip=1,Nplane
    {  d1=abs(rzp)-abs(R_rzp); e1=abs(d1)-eps*abs(rzp)
       if e1>0  { check d1<0; go to :ins: }
       d2=RZmin-R_RZmin;       e2=abs(d2)-eps*abs(RZmin)
       ds=abs(RZmin+R_RZmax)+abs(RZmax+R_RZmin)
       es=abs(ds)-eps*abs(RZmin+Rzmax)
       d3=Fmin-R_Fmin;        e3=abs(d3)-eps*abs(Fmin)
 
       If Itp=1 & krz==0 & e3<0                  " some artificial rules"
       { If mrz==0
         {  If ("dz-rule"  dfi==R_dfi & abs(R_RZmin+R_Rzmax)>abs(RZmin+RZmax)_
              | "reflection"  dfi==-R_dfi & Es<0 )  mrz=Nump-I_Nump
         }
         If mrz>0
         {  Nz=(Nump-I_Nump)/mrz;  I_Nzr=max(I_Nzr,Nz+1)
            if (R_dzr==0 & Nz>0)   R_dzr=(RZmin-R_RZmin)/nz
            d2=d2-R_dzr*Nz;        d2m=max(d2m,abs(d2))
            if (abs(d2)>1.) <w> Ip,Nz,d2; (' bad dz rule: Ip,nz,d2=',2i5,f9.3)
            goto :eq:
       } }
       if abs(d2)>eps*abs(RZmin)   { check d2<0; go to :ins: }
       if abs(d3)>eps*abs(Fmin)    { check d3<0; go to :ins: }
       goto :eq:
    }  ip=Nplane+1;
    :ins: call Ucopy2(Rstack(1,ip),Rstack(1,ip+1),Lr*(Nplane-ip+1));
          call Ucopy (rzp,Rstack(1,ip),Lr);           Nplane+=1;
          if Nplane>=Lstack {err(too many planes found, quit)};
    :eq:  if abs(rzp+R_rzp)<eps*abs(rzp) & Itp=2 & Dfi==-R_Dfi "reflection"
          {  mm=Nump-I_Nump;       If (mrz=0 & mm!=0) mrz=mm;
             If mm!=mrz {err(z-reflections are too complicate, quit)}
          }
  }
  * last pass over the table - addresses and extremis
  Nadr=0; NumPmx=0; drzm=max(drzm,d2m);
  * scan volume offset (kk0) is taken into account only for divisions:
  do ip=1,Nplane                       " temporary - may find a better way  "
  {  if (kfi>=kk0) I_nfi=-I_nfi;   if (krz>=kk0) I_nzr=-I_nzr;
     " NumP may have increasing modifications due to dz or reflection rules "
       NumPmx=max(NumPmx,I_NumP+(max(I_Nzr,Itp)-1)*mrz+1)    " 1 word fence "
     " take into accont that in end-caps we always have only reflections    "
     I_Iadr=Nadr;  Nadr+=Max(1,I_Nfi)*Max(Itp,I_Nzr);
  }
  END
 
 
 
 
*CMZ :  1.30/00 28/06/96  18.19.55  by  Pavel Nevski
*-- Author :    Pavel Nevski   28/06/96
****************************************************************************
       subroutine AGETPLANE (Clev,IP,IF,IZ)
*                                                                          *
* decscription:                                                            *
*   given a layer generic name, reconstructs all its GEANT parameters      *
*   (shape, position, rotation) for a selected entry in AGCRTAB            *
****************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,agcrdig.
*  AGCRDIG is communication between AgFHIT0/1, AgFDIGI, AgFPATH, AGFDPAR.
      Integer          IWA,   JS,JD,JX,JXD,JDS,JDU
      COMMON /AGCRDIG/ IWA(2),JS,JD,JX,JXD,JDS,JDU
      Integer          Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia
      Character*4                                         cs,cd
      COMMON /AGCHITV/ Iprin,Nvb,Nw,Last,Mb,Nc1,Nc2,Iv,Ia,cs,cd
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,agcrtab.
*
*     Commons for the inner detector digi reconstruction
      Integer           Lstack,     Lr,   Lhead,   Lpack
      Parameter        (Lstack=2000,Lr=15,Lhead=52,Lpack=512)
*
*                                            subsystem descriptor
      Integer          Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,NumPmx,
     +                 Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires, nam,nmx
      Real             Rstack,drzm,RRmin,RRmax,ZZmin,ZZmax
*
      Common /AgCRtab/ Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,drzm,
     +                 RRmin,RRmax,ZZmin,ZZmax,
     +                 NumPmx,Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires,
     +                 Nam(15),Nmx(15),  Rstack(Lr,Lstack)
      Integer                            Istack(Lr,Lstack)
      Equivalence      (Rstack,Istack)
*                                            plane descriptor
      Real             rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent
      Integer          Nfi,Nzr,Nump,Iadr,Jres,Lpacku
      Common /AgCRta1/ rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent,
     +                 Nfi,Nzr,Nump,Iadr,Jres,Lpacku
*                                            detector size
      Integer          Ishape,Npar
      Real                         AgTran,   AgRmat,    Par
      Common /ARCplan/ Ishape,Npar,AgTran(3),AgRmat(10),Par(50)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
*KEND.
*  -----------------------------------------------------------------
*
       Integer      IP,IF,IZ,I,K,KK,NUM,ILEV,LEV,NUMBV(20)
       Character    Clev*(*)
*
*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*      If (Cd!=Cdet(1:4)) Call AGDECODE(Cdet,IT)
       JS=LQ(Jset-Iset);  Check JS>0;  Call UHTOC (IQ(Jset+Iset),4,Cs,4);
       JD=LQ(JS-Idet);    Check JD>0;  Call UHTOC (IQ(JS + Idet),4,Cd,4);
       JDU=LQ(JD-3);      Check JDU>0;
*
       Call UCOPY(Rstack(1,ip),rzp,Lr)
       Call UCTOH(Clev,ILev,4,4)
       K=0; NUM=NUMP; Lev=kkk
       Do i=1,kkk
          If (ILev==NAM(i))  Lev=i
          If (abs(NMX(i))>1) k=k+1
       enddo
       kk=k
       Do i=kkk,1,-1
          Check abs(NMX(i))>1
          If (nmx(i)>1)  then
             NUMBV(k)=mod(NUM,NMX(i))+1
             NUM = NUM/NMX(i)
          else
             NUMBV(k)=1
             If (K==kfi) NUMBV(k)=IF
             If (K==krz) NUMBV(k)=IZ
          endif
          k=k-1
       enddo
*      <w> ip,(numbv(i),i=1,kk); (' ip=',i3,' numbv=',15i5)
       Call AGFPATH(NUMBV)
 
       Ishape=Q(LQ(JGPAR-Lev)-4);   Npar=Q(LQ(JGPAR-lev)-1);
       Call Ucopy(Q(LQ(JGPAR-lev)+1),Par,min(Npar,50));	
       Call Ucopy(GTRAN(1,LEV),AgTRAN,3);
       Call Ucopy(GRMAT(1,LEV),AgRMAT,10);
*
       END
 
 
 
*CMZ :  1.30/00 19/06/96  03.24.23  by  Pavel Nevski
*CMZ :  1.00/00 04/10/95  19.54.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/02/95
************************************************************************
*                                                                      *
                   subroutine    A x x x P R E P
*Attention: XTRT is special now - it is TWO detectors with types 11 &12*
************************************************************************
Replace[CHK#;] with _
  [; IF (~(#1)) { <W> Cset; (' Error in XXXPREP for detector ',a4,
                             ' condition #1 is not satisfied'); NEXT; };
  ]
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,agcbuff.
*     buffer for hit/digi maps
      Integer          Ibuf,Lbuf
      Parameter        (Lbuf=500 000)
      Common /AGCBUFF/ Ibuf(Lbuf)
*     - - - - - - - - - - - - - -
*KEEP,agcrtab.
*
*     Commons for the inner detector digi reconstruction
      Integer           Lstack,     Lr,   Lhead,   Lpack
      Parameter        (Lstack=2000,Lr=15,Lhead=52,Lpack=512)
*
*                                            subsystem descriptor
      Integer          Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,NumPmx,
     +                 Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires, nam,nmx
      Real             Rstack,drzm,RRmin,RRmax,ZZmin,ZZmax
*
      Common /AgCRtab/ Isys,Nplane,Itp,Iset,Idet,kkk,kfi,krz,mrz,drzm,
     +                 RRmin,RRmax,ZZmin,ZZmax,
     +                 NumPmx,Nadr,Istart,Inamd,Iaxr,Iaxt,Iaxz,Ires,
     +                 Nam(15),Nmx(15),  Rstack(Lr,Lstack)
      Integer                            Istack(Lr,Lstack)
      Equivalence      (Rstack,Istack)
*                                            plane descriptor
      Real             rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent
      Integer          Nfi,Nzr,Nump,Iadr,Jres,Lpacku
      Common /AgCRta1/ rzp,RZmin,RZmax,Fmin,Fmax,Dfi,Dzr,tilt,sas,Fcent,
     +                 Nfi,Nzr,Nump,Iadr,Jres,Lpacku
*                                            detector size
      Integer          Ishape,Npar
      Real                         AgTran,   AgRmat,    Par
      Common /ARCplan/ Ishape,Npar,AgTran(3),AgRmat(10),Par(50)
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
*KEND.
  INTEGER       NN,  NV,   Nd,   Lt
  PARAMETER    (NN=7,NV=10,Nd=10,Lt=3000)
  * trt: XGAS, mdt: FMUC/FTUI, MUCH/MTUI
  Character*6  Csets(NN)/'PIXB','PIXE','SITV','SCTT','ZSCT','XTRT',  'XTRT'/;
  Character*6  Cdets(NN)/'PBCR','PECR','STCR','SCTB','ZSEN','XGAS-1','XGAS-1'/
  Integer      Itypes(NN)/   1 ,    2 ,    1 ,    1 ,    2 ,   11  ,    12 /;
  Integer      NVL(NV),ISC(NV),Iaddr(0:Lt),Nfdim(0:Lt),Nzdim(0:Lt);
* - - - - - - - - - -
*CDE,SLDBNK. - Slug auxilary common for SLDETBA routine
      CHARACTER*4  CHFOR
      INTEGER      IOWDS
      COMMON /SLDBNK/ CHFOR,IOWDS(16)
* - - - - - - - - - -
  INTEGER      AgPFLAG,Id,Ip,Iprin,Ifree,Itype,Lmap,N,I,J,K,L,
               Ia,i1,i2,Ndi,Nds,Ndd,Ltra;
  Character*6  Cset,Cdet;
  Real         Digi(Nd);
  Logical      First/.true./;
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 Ifree=1;   Call Vzero(Ibuf,Lbuf);
 Do Id=1,NN
 {  Itype=Itypes(Id);  Cset=Csets(Id);  Cdet=Cdets(id);
    IPrin=AgPFLAG(Cset,'RECO');         Check IPrin>=0;
    If First
    {  Call AgDECODE(Cdet,Itype);   Check Nplane>0;
       Call UCTOH(Cdet,Inamd,4,4);  Isys=Id;  Istart=Ifree;
       L=Lhead+Lr*Nplane;
       If (Cset=='XTRT' & Itype==12) L=-L;
*      - - - - - - - - - - - - - - - - - -
       CALL MZIOCH (IOWDS,16,'9I 5F 3I 1H 4I 15H 15I / 10F 5I'); CHFOR='RMAP';
       Call ASLSETBA(Cset,'RMAP',L,Isys);                         CHFOR=' ';
 
       Prin2 (nam(i),i=1,15); (' Names=',15(2x,a4))
       Prin2 (Nmx(i),i=1,15); (' LVmax=',15i6)
       Prin2 Itp,Nplane,kfi,krz,mrz,drzm,iaxr,iaxt,iaxz
             (' type',i2,' Nplane=',i3,' k=',2i3,i6,f8.3,' axes r,t,z=',3i2)
       Prin3 ((Rstack(i,ip),i=1,10),(Istack(i,ip),i=11,Lr),Ip=1,Nplane)
             (' R,z,F=',3F8.2,3F7.3,F8.2,3F7.4,' N=',3i4,i6,i4)
       Prin1 Cset,Ifree,Ifree+Nadr
             (' AXXXPREP: Detector ',A4,', required space',2i8);
    }
    else
    {  L=Lhead+Lr*Lstack;
       If (Cset=='XTRT' & Itype==12) L=-L;
*      - - - - - - - - - - - - - - - - - -
       Call ASLGETBA(Cset,'RMAP',L,Lmap,Isys);
    "  <w> L,Lmap,Isys,Istart,Nadr;(' ASLGETBA: L,Lmap,Isys,Istart,Nadr=',5I6)"
       Check Lmap>0;   CHK Lmap>=Lhead+Lr*Nplane;
    "  <w> Cset,Lmap; (' AXXXPREP error: ',a,' reconstruction bank len=',i4) "
    }
   *                    make intermediate map
    Ifree+=Nadr+1;                                CHK Ifree<Lbuf;
    Call Vzero(Ibuf(Istart+1),Nadr+1);            Call Vzero(Iaddr,Lt+1);
    Do Ip=1,Nplane
    {  Call Ucopy(Rstack(1,ip),rzp,Lr);           CHK Nump<=Lt;
       Ia=Istart+Iadr;                            CHK Ia<Ifree;
       Iaddr(NumP)=Ia;                            Nfdim(NumP)=Max(1,Nfi);
       " in endcaps we always do a reflection "   Nzdim(NumP)=Max(Itp,Nzr);
    }
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Call VZERO(NVL,NV);   {K,ia,Ndi,Nds}=0;
    Loop
    {  Call AgFDIGI (Cset(1:3)//'D',Cdet,NVL,Ltra,ISC,DIGI,K,IA);
       If (k<=0) Break;
       If Cset=='XTRT' { Check Itype==11 & ISC(1)<=2 | Itype==12 & ISC(1)>=3; }
       Ndi+=1;  {N,j}=0; { i1,i2 }=1;
      * - - -    step one - map ISC to the packed address NumP
       do i=1,kkk
       { Check abs(Nmx(i))>1;  j+=1;  If (Nmx(i)>1) N*=Nmx(i)+ISC(j)-1;
         If (i==kfi)  i1=ISC(j);      If (i==Krz)  i2=ISC(j);
       }
       prin9 Ndi,(ISC(i),i=1,j),N;  (' AXXPREP Ndig,ISC,Nump=',10i6)
 
       * step two - modify Nump to account for z shifts (dz rule or reflection)
       CHK N<=Lt;  Ia=Iaddr(N);
       if krz=0 & mrz>0  { while Ia=0&N>=mrz { i2+=1; N-=mrz; Ia=Iaddr(N); } }
 
       " skip hits which are not mapped "  chk Ia>0;
       CHK N>=0;    i1=min(i1,NFdim(N));   i2=min(i2,NZdim(N));
       prin9 N,Ia,i1,i2,Ltra;   (' selected Npack,Ia,i1,i2,Ltra=',6i6);
       ia+=i1+(i2-1)*Nfdim(N);    CHK Istart <=Ia&Ia< Ifree;
       Ndd=Ibuf(Ia);   IF (Ndd=0) Ndd=k*Lpack;   Ndd+=1;
       if mod(Ndd,Lpack)=0  { <W> Cset,(ISC(i),i=1,J);
          (' AXXXPREP overflow in det=',a4,' nbv=',15i5); Break; }
       Ibuf(Ia)=Ndd;   Nds+=1;
    }
    Prin2 Cset,Ndi,Nds; (' AXXXPREP: total digits in detector ',a4,' =',2I8);
    " prin9 (Ibuf(i),i=1,Ifree); (20i5); "
 }
 First=.false.
 end
 
 
*CMZ :  1.00/00 25/08/95  00.09.19  by  Pavel Nevski
*-- Author :  Silin & Sokolov
********************************************************************
*                                                                  *
               subroutine     F U M I L I _
            (S,M,N1,N2,N3,EPS,AKP,ALM,IT,MC)
*                                                                  *
*           almost copy of D520 from CERNLIB                       *
* Original Version:                                Silin & Sokolov *
* Modifications:                                    Pavel Nevski   *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEND.
      C O M M O N /ENDFLG/NA,IEND,IND
      LOGICAL FUMPLA
      INTEGER M,N1,N2,N3,IT,MC,NA,IEND,IND,NN1,NN2,NN3,NINF,NFIX,
              I,N0,NN0,I1,I2,J,J1,J2,IMX,IFX,M1,L1,IFI
      REAL    S,EPS,AKP,ALM,T,GT,T1,RP,SP,DS,OLDS,Ai,AJ,Ak,Al,Afix,d,
              SIGI,AMAX
      DATA RP/1.E-5/ ! 10*MAX. RELATIVE PRECISION
* ..
      NN2  = 0
      NN3  = 0
      NINF = 0
      NFIX = 0
      IEND = 0
      CALL VZERO (RR,M)
      CALL UCOPY (PL0,PLU,M)
      IF (EPS>0) CALL VZERO (SIGM,M)
* ...                             *****  new iteration *****
10 T1  = 1
   NN1 = 1
   Loop
   {  S   = 0
      CALL VZERO (GG,M)                      ! REPEAT WITH SMALLER STEP
      DO I = 1,M
      {  Check FUMPLA(PL0,I,N0)
         IF (PLU(I)>0) PL0(I) = PLU(I)       ! save PL, may be fixed later
      }
      NN0 = N0*(N0+1)/2
      CALL VZERO (ZZ,NN0)
      NA = M
      CALL FUMSGZ (M,S)
      SP = RP*ABS(S)
      DS = OLDS-S
      CALL UCOPY(ZZ,Z0,NN0)
      IF (NN3<=0 | NN1>N1 | DS>GT/6 | ABS(DS) <=SP & GT<=SP) Break
* ...                                  **** relaxation ****
      T = AMAX1(0.5*GT/(GT-DS),0.25)
      GT = GT*T
      T1 = T1*T
      NN2 = 0
      NN1 = NN1+1
      DO I = 1,M
      {  Check PLU(I)>0
         A(I)   = A(I)-DA(I)*(1-T)
         PLU(I) = PLU(I)*T
         DA(I)  = DA(I)*T
      }
   }
* ..                                   fix some parameters and compress Z
50 Loop
   {  I2 = 0
      DO I = 1,M
      {  Check FUMPLA(PL0,I,I1)
         IF (PLU(I)==0)      PLU(I) = PL0(I)
         IF (PLU(I)>0 & (A(I)>=AMX(I)&GG(I)<=0 | A(I)<=AMN(I)&GG(I)>=0)) _
                                                                PLU(I)=0
         check FUMPLA(PLU,I,I2)
         J2 = 0
         DO J = 1,I
         {  Check FUMPLA(PL0,J,J1)
            Check FUMPLA(PLU,J,J2)
            ZZ(I2*(I2-1)/2+J2) = Z0(I1*(I1-1)/2+J1)
         }
         RR(I) = ZZ(I2*(I2+1)/2)    ! save ZZ(I,I) in correlation factors
      }
* ...                            ***  get covariance matrix ***
      CALL FUMCONV(I2)
      If (IND==0) Break
      NINF = NINF+IND
      NFIX = NFIX+1
      IFI  = 0
   }
 
* ..             CALCULATE STEPS, CHECK BOUND, LIMITING OF STEPS
      ALM  = 1
      AKP  = 0
      AFIX = 0
      IMX  = 0
      IFX  = 0
      DO I = 1,M
      {  DA(I) = 0
         Check FUMPLA(PLU,I,I1)
         D=0
         DO J = 1,M
         {  Check FUMPLA(PLU,J,J1)
            M1 = MAX0(I1,J1)
            D = D-GG(J)*ZZ(M1*(M1-3)/2+I1+J1)
         }
         AI = A(I)
         L1 = I1*(I1+1)/2
* ...                                    calculate A,KAP,LAM
         AJ = min(max(AMN(I),AI-PLU(I),AI+D),AI+PLU(I),AMX(I))
         SIGI  = SQRT(ABS(ZZ(L1)))
         RR(I) = RR(I)*ZZ(L1)
         IF (EPS>0) SIGM(I) = SIGI
         AK  = ABS(D/SIGI)              ! parameter step vs its accuracy
         AL  = ABS((AI-AJ)/D)           ! actual(plu limited) step vs desired
         AKP = max(AKP,ABS(D/SIGM(I)))
* ...                                    check for fixation and limitation
         IF AK>AFIX & (AI>=AMX(I)&D>0 | AI<=AMN(I)&D<0) { AFIX=AK;  IFX=I; }
         If AL<=ALM                           {  ALM=AL;  AMAX=AJ;  IMX=I; }
         DA(I) = D
      }
      IF (IFX<=0) GO TO 120
      PLU(IFX) = -1
  110 NFIX = NFIX+1
      IFI = 0
      GO TO 50
* ..                                     trying to increase step
  120 GT = 0
      DO 140 I = 1,M
         IF (PLU(I)<=0) GO TO 140
         IF (NN2<=N2  |  ABS(PLU(I)/DA(I))>4*ALM) GO TO 130
         PLU(I) = 4*PLU(I)
         T1     = 4
  130    DA(I)  = DA(I)*ALM
         GT     = GT-DA(I)*GG(I)
  140 CONTINUE
* ...
      IF (AKP<=ABS(EPS)) GO TO 160       ! accuracy check
      IEND = 0
      IFI  = IFI+1
      IF (NFIX==0 | IFI-1<=NFIX) GO TO 170
  150 CALL UCOPY(PL0,PLU,M)              ! un-fix parameters
      NFIX = 0
      NINF = 0
      GO TO 50
* ...
  160 IEND = IEND+1
      IF (NFIX==0) GO TO 170
      IF (IEND==1) GO TO 150
* * *       IF (NFIX>NINF) IEND = 0        ! estx ON BOUND
* ...
  170 IF (IEND==0 & NN3>=N3) IEND = -3 ! ITER.LIMIT
      IF (IEND>0 & NINF>0)   IEND = -2 ! INF.ER.ESTIM
      IF (GT<=SP & T1<1 & ALM<1) IEND = -1
      IF (IT>=0) CALL FUMONITO(S,M,NN3,N3,IT,EPS,GT,AKP,ALM,T1)
* ...
      MC = IEND
      IF (IEND!=0) RETURN              ! TEST FOR END
      OLDS = S
      NN2 = NN2+1
      NN3 = NN3+1
      DO 180 I = 1,M
  180 A(I) = A(I)+DA(I)
      IF (IMX>0) A(IMX) = AMAX
      GO TO 10
      END
 
********************************************************************
*                                                                  *
               subroutine   F U M O N I T O _
            (S,M,NN3,N3,IT,EPS,GT,AKP,ALM,T1)
*                                                                  *
* Original Version:                                Silin & Sokolov *
* Modifications:      03/10/94                      Pavel Nevski   *
********************************************************************
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEND.
      C O M M O N /ENDFLG/NA,IEND,IND
      Integer M,NN3,N3,IT,NA,IEND,IND,IP,LU/6/
      Real    S,EPS,GT,AKP,ALM,T1,P
*
      IP=1
      IF (IT>0) IP=MOD(NN3,IT)
*     print each IT iteration or the last one, if IT positive:
      IF (IP==0  |  IEND.NE.0)  &  IT>=0
      {  Output NN3,S*2,GT*2,AKP,ALM,T1
         (/8(' *'),I3,5H ITER,2X,3H2S= ,E11.4,2X,3HGT=,E10.2/,
            15X,4HKAP=,E8.2, 2X,5HLAMB=,E8.2, 2X,3HT1=,E8.2//,
            15X,10HPARAMETERS, 5X,6HERRORS, 10X,7HFACTORS)
         DO I=1,M
         {  P=-100
            IF (PL0(I)>0)   P=PLU(I)
            IF (P>0)        output I,A(I),SIGM(I),RR(I)
                   (10X,I3,E13.5,3H+/-,E10.4,6X,E10.3)
            IF (-1<=P&P<=0) output I,A(I),SIGM(I),RR(I)
                   (10X,I3,E13.5,3H+/-,E10.4,6X,E10.3,'  ON BOUND')
            IF (P==-2)      output I,A(I)
                    (10X,I3,E13.5,12H+/- INFINITE)
      }  }
      IF(IEND==-1) output; (' S does not decrease, bad derivatives')
      IF(IEND==-2) output; (' infinite parameter errors    ')
      IF(IEND==-3) output; (' iteration limit is exceeded  ')
      END
 
 
********************************************************************
*                                                                  *
        FUNCTION     F U M P L A (PL,I,I1)
*                                                                  *
*       find next free parameter                                   *
* Original Version:                                 Pavel Nevski   *
********************************************************************
        IMPLICIT NONE
        LOGICAL  FUMPLA,L
        INTEGER  I,I1
        REAL     PL(*)
        IF (I==1) I1=0
        L=PL(I).GT.0
        IF(L) I1=I1+1
        FUMPLA=L
        END
 
********************************************************************
*                                                                  *
               SUBROUTINE   F U M C O N V (N)
*                                                                  *
*         fast matrix conversion - FUMILI original                 *
* Original Version:                                Silin & Sokolov *
* Modifications:                             never done since 1961 *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEND.
        Integer         NA,IEND,IND,N,IR,I,Ni,II,L1,K,NL,KI,NK
        Real            Aps,Rp,Am,Ap,D,C,ZI
        COMMON /ENDFLG/ NA,IEND,IND
        DATA   RP/1.E-5/     ! MAX.REL.PRECISION - 10/10/94 * 10
        DATA   AM/1.E+35/    ! MAXIMAL NUMBER ON THE COMPUTER
*
   IND = 0
   Check N>0
   APS = SQRT(AM/N)
   AP  = 1/APS**2
   IR  = 0
   DO I=1,N
   {  IR+=1;  while PLU(IR)<=0 { IR+=1; }
      NI=I*(I-1)/2
      II=NI+I
      ZI=ZZ(II)
      IF (ZI<=RP*ABS(RR(IR)) | ZI<=AP) GO TO 170
      ZI=1./SQRT(ZI)
      ZZ(II)=ZI
      Do NL=II-1,NI+1,-1
      { ZZ(NL)=ZZ(NL)*ZI;  IF (ABS(ZZ(NL))>=APS) GO TO 140;   }
      Check I<N
 
* . . .  inversion here  . . .
      Do K=N,I+1,-1
      {  NK = K*(K-1)/2
         NL = NK
         D  = ZZ(NK+I)*ZI
         C  = D*ZI
         Do L1=K,1,-1
         { IF   L1>I    { ZZ(NK+L1)-=ZZ(NL+I)*C;  NL=NL-L1+1; }
           Else IF L1<I { ZZ(NK+L1)-=ZZ(NI+L1)*D;             }
           Else         { ZZ(NK+L1)=-C;                       }
   }  }  }
 
* . . .  normal exit here  . . .
      DO I=1,N
      {  DO K=I,N
         {  NL=K*(K-1)/2
            D=0.
            DO L1=K,N  { D+=ZZ(NL+I)*ZZ(NL+K); NL+=L1; }
            KI=K*(K-1)/2+I
            ZZ(KI)=D
      }  }
      RETURN
 
* . . .  error exit here  . . .
  140 K=I+NL-II
      IR=0
      DO I=1,K  { IR+=1; While PLU(IR)<=0 { IR+=1; } }
*
  170 PLU(IR)=-2
      RR(IR)=0
      IND=1
      END
 
********************************************************************
*                                                                  *
                 subroutine    F U M S G Z (M,S)
*                                                                  *
*     calculation of chi-square deviations and derivatives         *
* Original Version:                                Silin & Sokolov *
* Modifications:                                    Pavel Nevski   *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEEP,FUMUSE.
*   fumili users commons
      INTEGER         NA, NS, NP, NN, MM
      PARAMETER       (NA=10, NS=8, NP=400)
      REAL            EX,YY
      COMMON /FUMNED/ NN,MM
      COMMON /FEXDA/  EX(NS,NP)
      COMMON /FUMYY/  YY(0:NA,NP)
*     - - - - - - - - - - - - - - - - - - - -
*KEND.
     Integer I,J,K,M,N
     Real Funct,S,Ai,Hi,E,D,Y,DY,S1,S2,Rpd/1.e-4/
     Real PI/3.14159265/
;                                            " starting parameters "
Do n=1,NN {  YY(0,n)=FUNCT(Ex(3,n)); }
DO I=1,M                                    " calculate derivatives "
{  Check PL0(i)>0;
   AI=A(I); HI=AMAX1(PL0(I)*0.1,RPD*ABS(AI));
        IF  AI+HI<=AMX(I)       { A(I)=AI+HI }
   else IF  AI-HI>=AMN(I)       { A(I)=AI-HI }
   else IF  AI-AMN(I)>AMX(I)-AI { A(I)=AMN(I)} else { A(I)=AMX(i)};
   Do n=1,NN { Dy=FUNCT(Ex(3,n))-YY(0,n);
                              "check that deltaFi is from -Pi to +Pi"
   if(Ex(3,n)!=0. & Ex(4,n)!=0. & abs(DY)>PI) {
     if(DY>PI){DY=DY-2*PI}elseif(DY<-PI){DY=DY+2*PI};};
               YY(I,n)=DY/(A(i)-Ai); }
   A(I)=AI;
}
DO n=1,NN                      " calculate gradients and derivatives matrix "
{  K=0;  E=EX(1,n);  D=EX(2,n);  Y=YY(0,n);
   DY=Y-E;
                              "check that deltaFi is from -Pi to +Pi"
   if(Ex(3,n)!=0. & Ex(4,n)!=0. & abs(DY)>PI) {
     if(DY>PI){DY=DY-2*PI}elseif(DY<-PI){DY=DY+2*PI};};
   Check D>0 | Y>1.e-9;
   IF D>0  { S2=1/D**2;  S1=DY*S2;  S+=DY*S1/2; }
   else    { S2=E/Y**2;  S1=DY/Y;   S+=Y;  IF(E>0) S-=E*ALOG((E+DY)/E)-E; }
   DO I=1,M
   { Check PL0(I)>0;      GG(I)+=YY(I,n)*S1;
     DO J=1,I  {  Check PL0(J)>0; K+=1;  ZZ(K)+=YY(I,n)*YY(J,n)*S2; }
}  }
End
 
********************************************************************
*                                                                  *
               subroutine    F U M S G Z O L D (M,S)
*                                                                  *
*     calculation of chi-square deviations and derivatives         *
* Original Version:                                Silin & Sokolov *
* Modifications:                                    Pavel Nevski   *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,FUMSIZ.
*   fumili internal commons
      INTEGER        L, LL
      REAL           ZZ,Z0,A,DA,RR,GG,SIGM,AMN,AMX,PLU,PL0
      PARAMETER      (L=10,LL=L*(L+1)/2)
      COMMON /FUMIZ/  ZZ(LL)
      COMMON /FUMZ0/  Z0(LL)
      COMMON /FUMILA/ A(L)
      COMMON /FUMIR/  RR(L)
      COMMON /FUMIG/  GG(L)
      COMMON /FUMDA/  DA(L)
      COMMON /FSIGMA/ SIGM(L)
      COMMON /FUMAU/  AMX(L)
      COMMON /FUMAL/  AMN(L)
      COMMON /FUMPL/  PL0(L)
      COMMON /FUMPLU/ PLU(L)
*     - - - - - - - - - - - - - - - - -
*KEEP,FUMUSE.
*   fumili users commons
      INTEGER         NA, NS, NP, NN, MM
      PARAMETER       (NA=10, NS=8, NP=400)
      REAL            EX,YY
      COMMON /FUMNED/ NN,MM
      COMMON /FEXDA/  EX(NS,NP)
      COMMON /FUMYY/  YY(0:NA,NP)
*     - - - - - - - - - - - - - - - - - - - -
*KEND.
     Integer I,J,K,M,N
     Real Funct,S,Ai,Hi,E,D,Y,DY,S1,S2,Rpd/1.e-4/
;                                            " starting parameters "
Do n=1,NN {  YY(0,n)=FUNCT(Ex(3,n)); }
DO I=1,M                                    " calculate derivatives "
{  Check PL0(i)>0;
   AI=A(I); HI=AMAX1(PL0(I)*0.1,RPD*ABS(AI));
        IF  AI+HI<=AMX(I)       { A(I)=AI+HI }
   else IF  AI-HI>=AMN(I)       { A(I)=AI-HI }
   else IF  AI-AMN(I)>AMX(I)-AI { A(I)=AMN(I)} else { A(I)=AMX(i)};
   Do n=1,NN { Dy=FUNCT(Ex(3,n))-YY(0,n); YY(I,n)=DY/(A(i)-Ai); }
   A(I)=AI;
}
DO n=1,NN                      " calculate gradients and derivatives matrix "
{  K=0;  E=EX(1,n);  D=EX(2,n);  Y=YY(0,n);
   Check D>0 | Y>1.e-9;
   IF D>0  { S2=1/D**2;  S1=(Y-E)*S2;  S+=(Y-E)*S1/2; }
   else    { S2=E/Y**2;  S1=(Y-E)/Y;   S+=Y;  IF(E>0) S-=E*ALOG(Y/E)-E; }
   DO I=1,M
   { Check PL0(I)>0;      GG(I)+=YY(I,n)*S1;
     DO J=1,I  {  Check PL0(J)>0; K+=1;  ZZ(K)+=YY(I,n)*YY(J,n)*S2; }
}  }
End
 
*CMZ :          05/11/97  15.31.12  by  Pavel Nevski
*-- Author :    Pavel Nevski   04/11/97
function sind(x);     +cde,gconst;  sind=sin(degrad*x);       end;
function cosd(x);     +cde,gconst;  cosd=cos(degrad*x);       end;
function tand(x);     +cde,gconst;  tand=tan(degrad*x);       end;
function asind(x);    +cde,gconst;  asind=raddeg*asin(x);     end;
function acosd(x);    +cde,gconst;  acosd=raddeg*acos(x);     end;
function atand(x);    +cde,gconst;  atand=raddeg*atan(x);     end;
function atan2d(x,y); +cde,gconst;  atan2d=raddeg*atan2(x,y); end;
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*CMZ :          10/11/97  15.32.54  by  Pavel Nevski
*CMZ :  1.30/00 18/06/96  12.32.41  by  Pavel Nevski
*CMZU:  1.03/00 28/10/93  12.54.58  by  M. Nessi CERN
*-- Author :  Pavel Nevski
************************************************************************
      FUNCTION TTAN (Y)
*
* Description :     translate rapidity to tangent of polar theta       *
************************************************************************
*
      REAL Y,TTAN
      TTAN = TAN(2*ATAN(EXP(-Y)))
*
      END
*CMZ :          31/01/98  14.01.41  by  Pavel Nevski
*-- Author :    Bill LOVE
C----------------------------------------------------------------------
      FUNCTION  BITCH(INT,FORMAT)
C
C   Functional Description :
C BITCH Converts a 32 bit integer, INT, into either 8 hexadecimal
C or 11 octal characters (according to the value of FORMAT) and
C returns as the value of BITCH as many characters as will fit
C from the right end of the string (Caller declares length of BITCH).
C If FORMAT is something other than 'H' or 'O' BITCH returns blank.
C
C   Input arguments
C      INTEGER   INT        ! actually a bit string, assumed 32 bits long
C      CHARACTER FORMAT     ! either 'H' or 'O'.
C   Returned value : ASCII string of digits representing INT.
C
C Converted to STAR style  5 Feb 1992   Bill Love
C----------------------------------------------------------------------
      IMPLICIT   NONE
      CHARACTER  BITCH*(*)
      INTEGER    INT        ! actually a bit string, assumed 32 bits long
      CHARACTER  FORMAT     ! either 'H' or 'O'.
      INTEGER    I,L,M3,M4
      CHARACTER  TAB(16),STRING*11
C-------
      DATA M3/7/,M4/15/
      DATA TAB/'0','1','2','3','4','5','6','7',
     >         '8','9','A','B','C','D','E','F'/
C-------
C
        STRING=' '
        IF(FORMAT.EQ.'H')THEN
            DO I=1,8
              STRING(I+3:I+3)=TAB(IAND(M4,ISHFT(INT,4*(I-8)))+1)
            ENDDO ! I loop to 8
        ELSE IF(FORMAT.EQ.'O')THEN
            DO I=1,11
              STRING(I:I)=TAB(IAND(M3,ISHFT(INT,3*(I-11)))+1)
            ENDDO ! I loop to 11
        ENDIF
        BITCH = STRING
        L     = LEN(BITCH)
        IF(L.LT.11) BITCH=STRING(12-L:11)
        RETURN
        END
 
*CMZ :          31/01/98  14.01.41  by  Pavel Nevski
*-- Author :    Bill Love
C----------------------------------------------------------------------
      FUNCTION IFNB(STRING)
C
C   IFNB returns the position of the first non-blank character in STRING
C
C----------------------------------------------------------------------
      IMPLICIT NONE
      INTEGER  IFNB
      CHARACTER*(*) STRING    ! String input argument
*
      IFNB = 0
      IF (LEN(STRING).EQ.0) RETURN
*
      DO IFNB = 1,LEN(STRING)
        IF (STRING(IFNB:IFNB).NE.' ') RETURN
      ENDDO
*
      END
 
*CMZ :          31/01/98  14.01.41  by  Pavel Nevski
*-- Author :    Bill Love
C----------------------------------------------------------------------
        FUNCTION LSTRG(STRING)
C
C   Input argument :   String whose actual length is returned.
C   Returns the length of textstrings, i. e. the position of the
C      last non-blank character.
C   Converted to STAR style  5-Feb-1992   Bill Love
C----------------------------------------------------------------------
        IMPLICIT NONE
	INTEGER  LSTRG
	CHARACTER*(*) STRING
        INTEGER  I,LS
 
	LSTRG=0
	LS=LEN(STRING)
	DO I=1,LS
           IF(STRING(I:I).NE.' ')LSTRG=I
        ENDDO
	RETURN
	END
 
*CMZ :          31/01/98  14.12.02  by  Pavel Nevski
*-- Author :    Bill Love
C----------------------------------------------------------------------
      SUBROUTINE QIKS (MM,NN,MOVE,COMPARE)
C
C INPUTS         MM,NN          QIKS sorts a list of items numbered
C                               sequentially from MM to NN.  Every item
C    in the list to be sorted must be associated with a unique integer from
C    MM to NN inclusive.  Zero cannot be included in the range, i.e. both
C    MM and NN should be positive integers.  In the vast majority of cases
C    MM is 1 and NN is the number of items in the list.
C              MOVE,COMPARE     MOVE and COMPARE must be defined as
C                               external in the calling program.
C                               SUBROUTINE MOVE(I,J) must perform the
C     operation of moving an item from position I to position J.  If
C     either I or J is zero, the move should be from or to an extra item
C     of storage (this extra storage must be provided by the routine
C     which calls QIKS).  The values of I and J transmitted to
C     MOVE and COMPARE are generated by QIKS - the user has no control
C     over them.  However, he must make provision in MOVE and in COMPARE
C     to recognize when I or J are zero and take appropriate action.
C     The calling routine is presumed to communicate with MOVE and COMPARE
C     through common.  The layout of the item is entirely up to the caller,
C     QIKS will never see it.  The item may have several separate pieces.
C  FUNCTION COMPARE (I,J) must return a value that is negative, O, or
C     positive according to whether item I is to occupy a position in the
C     sequence respectively, lower than, equivalent to, or higher than J.
C     Again, if either I or J is zero, comparison is with the extra item.
C     COMPARE should be declared as INTEGER.
C PROGRAMMER   R. HUNN
C         BNL modification by K. Fuchel and R. Horwitz     Feb. 67.
C         Moved to PDP-10 and updated to FORTRAN-IV by W. A. Love 2-April-79.
C         Added to E810 library [mpslib.e810.sources]gutil.src 2 Oct 87.
C         Converted to F77+VAX extensions (DO WHILE) Feb 1992 WAL
C         Reverted the spreader to F66 version after hang Jun 1992 WAL
C PURPOSE      QIKS is a FORTRAN internal sort subroutine useful for
C         sorting arrays in memory.  It is fast and requires only one
C additional item of working storage.  Definition of the items to be sorted
C is completely flexible, being specified by user-supplied subprograms.
C
C ERROR CONDITIONS     QIKS has been in use for 30 years now without error
C                      to my knowledge.  There is potential with a long enough
C list to overflow the 20 levels of push-down provided (unchecked) but since
C the main virtue of QIKS is its speed, I am reluctant to add error checking
C until we turn up an example.
C
C TYPICAL USE                  PROGRAM XXX
C                              COMMON/SORTITEMS/IA(10000)
C                              COMMON/EXTRAITEM/IB
C                              EXTERNAL MO, CO
C                              INTEGER CO
C                                       .
C                              fill array IA to N items, set M=1
C                                       .
C                              CALL QIKS (M,N,MO,CO)
C                                       .
C                                       .
C COMMON BLOCKS    As required by user to communicate between the calling
C                  routine and the user supplied move and compare routines.
C
C METHOD       QIKS is based on C. A. R. Hoare's quicksort and partition
C              algorithms (Nos. 64 and 63 respectively)
C              See  COM. ACM 4,321 (JULY 1961).
C
C----------------------------------------------------------------------
C
      IMPLICIT NONE
      INTEGER  MM,NN,COMPARE
      EXTERNAL MOVE,COMPARE
      INTEGER  I,J,M,N,KEY,LEVL
      INTEGER  MSAVE(20),NSAVE(20)
      LOGICAL  SWITCH
C
      I=0
      J=0
      LEVL = 0
      M=MM
      N=NN
   35 CONTINUE
C     Test for number of items left unsorted.
      IF((N-M).GT.1)THEN
C        More than 2 items, partition and push down
C        Partition Routine
         I=M
         J=N
C        Simplest key, i. e. middle element, works as well as any.
         KEY=(N+M)/2
         CALL MOVE(KEY, 0)
         IF(N.NE.KEY)CALL MOVE(N,KEY)
         SWITCH=.TRUE.
         DO WHILE (I.NE.J)
         IF(SWITCH)THEN
            IF(COMPARE(0,I).LT.0)THEN
C              Hole at bottom
               CALL MOVE(I,J)
               J=J-1
               SWITCH=.FALSE.
            ELSE
               I=I+1
            ENDIF
         ELSE
            IF(COMPARE(0,J).GT.0)THEN
C              Hole at top
               CALL MOVE(J,I)
               I=I+1
               SWITCH=.TRUE.
            ELSE
               J=J-1
            ENDIF
         ENDIF
         ENDDO      ! while (i.ne.j)
C        end partition
C        Spreader
         CALL MOVE(0,I)
 12      IF(I.EQ.N)GO TO 10
         I = I + 1
         IF(COMPARE(0,I).EQ.0)GO TO 12
 10      IF(J.EQ.M)GO TO 8
         J = J - 1
         IF(COMPARE(0,J).EQ.0)GO TO 10
 8       CONTINUE
C        Have partitioned this level in two
C        Push down
         LEVL = LEVL+1
C        Work on smallest portion, push down the other
         IF ((J-M).LE.(N-I))THEN
            MSAVE(LEVL) =I
            NSAVE(LEVL) = N
            N=J
         ELSE
            MSAVE(LEVL) = M
            NSAVE(LEVL) = J
            M=I
         ENDIF
      ELSE
C        One or two items remain in the partition
         IF((N-M).EQ.1)THEN
C           Come here when two items remain in any partition
            IF(COMPARE(M,N).GT.0)THEN
C              Swap if two items are out of order
               CALL MOVE(M,0)
               CALL MOVE(N,M)
               CALL MOVE(0,N)
            ENDIF
         ENDIF
C        Pop up; QIKS is finished when LEVL returns to 0
         IF(LEVL.EQ.0)RETURN
         M = MSAVE(LEVL)
         N = NSAVE(LEVL)
         LEVL = LEVL - 1
      ENDIF
      GO TO 35
      END
 
*CMZ :  1.00/00 30/06/95  13.07.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                subroutine   R B C D I R  (Cname,NVL);
*                                                                    *
*  Description:                                                      *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
CHARACTER  Cname*(*);   Integer    NVL(5),Link,Ia;
;                                                           /* save link */
 Call Rebank (Cname,NVL,BIG,Link,Ia);
 If Link==0 { <W> Cname; (' RBCDIR: Directory does not exist: ',A); Return; }
 LKAR P2=Link;
   END
 
*CMZ :  1.00/00 27/11/94  15.30.46  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
                 subroutine   R B F I N D
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
Integer i1,i2,ic,jdd; Data Jdd/1/;
;
  IF Inam#DDL(1,Jdd)                                         " fast search "
  {  i1=1; i2=NDD;    While i2-i1>1
     {  ic=(i1+i2)/2; If (Inam-DDL(1,ic)) :Lt:,:Equal:,:Gt:;
        :Lt: i2=ic; Next;        :Gt: i1=ic;
     }                                                       " normal search "
     Do ic=i1,i2 { If (Inam==DDL(1,ic)) goto :Equal:; }
     Iadr=0;  IOD=3;  Leng=MM;  Return;  :Equal: Jdd=ic;
  }  Iadr=DDL(2,Jdd);  Leng=DDL(3,Jdd);  IOD=DDL(4,Jdd);
   END
 
*CMZ :          23/03/98  20.56.20  by  Pavel Nevski
*CMZ :  1.00/00 30/06/95  13.07.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
        subroutine   R B C O P Y  (Cname,NVL,Ndim,Npar,Array)
*                                                                    *
*  Description: Return a copy of bank into users array               *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
CHARACTER  Cname*(*);    Integer    NVL(*),Npar,Array(*),Link,Ia,Ndim;
;                                                         /*  get access  */
 Call REbank (Cname,NVL,-Ndim,Link,Ia);
 " special counting request - return only number of banks, not data "
 If  NVL(kk)==0 { NVL(kk)=II-1; Npar=0; Return; }
;                                                        /* check and copy */
 Npar=-1; Check Link>0; Npar=min(Ndim,IQ(Link-1));
 If (Npar>0) Call UCOPY (IQ(Link+1+Ia),Array,Npar);
   END
 
*CMZ :          24/03/98  14.42.38  by  Pavel Nevski
*CMZ :  1.00/00 30/06/95  13.07.15  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
        subroutine   R B S T O R E (Cname,NVL,Form,Npar,Array)
*                                                                    *
*  Description: Copy a user Array into ZEBRA bank at CNAME(NVL)      *
*  Bank format (Form) is modified to keep the real format address    *
*  If Form was 0, standard format (32 bit UINT) is provided          *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
CHARACTER*(*)  Cname,FORM;     Integer  NVL(*),Npar,Array(*),Link,Ia;
;                                                 /* get format index */
 Cnam=FORM(1:4); Unless 0<=Inam<=Nfr
 { If Nfr>=100   { Output Form;
                 (' RBSTORE error: too many different FORMATS defined ! '/,
                  ' probably you use immediate constant ? last format=',A);}
   Nfr+=1; Call MZFORM('RECB',Form,FrTab(Nfr));  Inam=Nfr;  FORM(1:4)=Cnam;
 }
;                                                   /*  store data  */
   IOX=1;  if(Inam>0) IOX=FrTab(Inam);
   Call REbank (Cname,NVL,Npar,Link,Ia);   Check Link>0;
   Call UCOPY (Array,IQ(Link+1+Ia),Npar);  If (NVL(kk)==0) NVL(kk)=II;
   END
 
*CMZ :          01/07/98  19.10.00  by  Pavel Nevski
*CMZ :  1.30/00 16/04/97  22.11.16  by  Pavel Nevski
*CMZU:  1.00/01 21/12/95  22.17.57  by  Pavel Nevski
*CMZ :  1.00/00 03/10/95  18.17.59  by  Pavel Nevski
*-- Author :    Pavel Nevski   26/11/94
**********************************************************************
*                                                                    *
            Subroutine   R E B A N K  (Cname,NVL,Npar,Link,Ia)
*                                                                    *
* Input:                                                             *
*  Cname - 'Unix-like' path to the data block: /dir1/.../name.exte   *
*  NVL   - Bank numbers in their linear structures                   *
*  Npar >0 Bank is requested for writing, may be created or expanded *
*       <0 BAnk is requested for reading, should not be changed      *
* Output:                                                            *
*  Link  - returned link pointer to the bank, >0 if bank was found   *
*  Ia    - displacement in the bank for a row by row mode            *
*                                                                    *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
  INTEGER      NVL(*),Npar,LinkUp,Link,ia,Need,NV1,
               J,IE,J0,IL,JL,NS,ND,NV,Lm,LENOCC
  CHARACTER    Cname*(*),Del*1
 
Replace[ERR#;]  with [;OUTPUT kk,NVL(kk),IL,#1; (' REBANK ERROR: ',2x,
                      'level/copy/link=',3i4,' needed/found=',3i6); Return; ]
 
if (Lu<=0) Lu=6
 
"  Set starting directory - top level or current "
KK=0; {J0,J}=1;  While Cname(J0:J0)=='/' {J0=J0+1}
If J0>1
{  KK=1;
   " Get RECB/DETM bank address and make sure that it has been booked "
    If     Cname(J0:J0+3)=='DETM'
   { If (LK Detm==0) Call MZBOOK(IxCons,LKAR P2,LK Detm,1,'DETM',50,50,50,5,0)
     IrbDIV=IxCons;   Link=LK Detm;
   }
   else If Cname(J0:J0+3)=='RECB'
   { If (LKAR P1==0) Call MZBOOK(IxDIV,LKAR P2,LKAR P1, 1,'RECB',MM,MM,10,2,0)
     IrbDIV=IxDIV;    LINK=LKAR P1;
   }
   else If Cname(J0:J0+3)=='SECT' | Cname(J0:J0+3)=='TRIG' "old name for recb"
   { If (LKAR P1==0) Call MZBOOK(IxDIV,LKAR P2,LKAR P1, 1,'RECB',MM,MM,10,2,0)
     IrbDIV=IxDIV;    LINK=LKAR P1;   KK=0;
   }
   else If Cname(J0:J0+3)=='EVNT'   { IrbDIV=IxDIV;    Link=LKEVNT;  }
   else If Cname(J0:J0+3)=='SETS'   { IrbDIV=IxCons;   Link=JSET;    }
   else                             { "set externally" Link=LKAR P2; }
 
   LKAR P2=Link;  J=J0+5*KK;  If (Cname(J-1:J-1)='*' | Link<=0) Return;
}
else { LINK=LKAR P2 }
                                    "  search requested level "
Lm=LENOCC(Cname);  Check Lm>=J+3;
 
:Search_level: Loop
{ J=J0+5*KK;  KK+=1;  LinkUp=Link;  NS=IQ(LinkUp-2);
  Cnam=Cname(J:J+3);
  Del=Cname(J+4:J+4); If(J+4>Lm) Del='*';
  NV1=0; NV=NVL(KK);  JL=NS+1;  II=1;
  IF (NV==0 & Npar>0) NV=BIG       " 0 means the free element "
                                   "   Find structural link   "
  :Check_link: Do IL=1,NS
  {  Link=LQ(LinkUp-IL);   If Link==0 { JL=min(IL,JL); Next; }
     Check Inam==IQ(Link-4);   JL=IL
     :Linear_search: do II=2,NV+1
     { NV1=IQ(Link-5);  If (NV1==NV) Break;  If (NV1> NV) GOTO :new_bank:
***
     * on CHAIN entry: last item, no links, no next bank - group them together.
     * IrMode -1 prevents grouping, 0 - allows only on append, 1 - go wild:
       if IrMode>=0 & ii==2 & Del=='*' & LQ(Link-1)==0 & LQ(Link)==0
       { If (Nv==Big | IrMode>0 | Nv1<0 )
         {  Nd=IQ(Link-1);  Del='.';  kk-=1;  Break :Search_level:; }
       }
***
       JL=0;  LinkUP=Link;  Link=LQ(Link);   If (Link==0) GOTO :new_bank:
     } Nd=IQ(Link-1);       GOTO :Next_level:
  }
                                    "   create a new bank   "
  :new_bank: Link=0; IF Npar>0
  { IF (JL>NS) Call MZPUSH (IrbDIV,LinkUp,MM,0,' ')
    IF Del#'/' & Npar<BIG { Leng=Npar; IOD=IOX; } else { Call RBFIND; }
 
    Call MZBOOK (IrbDIV,Link,LinkUp,-JL,Cnam,MM,MM,Leng,IOD,0);
    if NV<BIG {IQ(link-5)=NV} else {IQ(link-5)=NV1+1};   Nd=0;
  }
  :Next_level: If (Del!='/' | Link==0) Break
}
                    "   end of request chain, copy and update LAST pointers "
  Leng=Iabs(Npar);  If (Leng==BIG) Call RBFIND;
  Ia=0;  Ie=Leng;
  If Del=='.'
  {  kk+=1;
     Ia=0; If (Npar>0) Ia=Nd; If (NVL(kk)>0) Ia=Leng*(NVL(kk)-1);
     Ie=Ia+Leng; II=Ie/Leng;  If (Npar<=0 & Ie>IQ(Link-1)) Link=0;
     "print *,' Packing kk,NVL,leng,ia,ie,ii = ',Cnam,kk,NVL(kk),leng,ia,ie,ii"
  }
  If Npar>0 & Link>0
  {  Need=Ie-IQ(Link-1); " If Need>leng { Err Ie,Nd; } "
     If (Need>0)   Call MZPUSH(IrbDIV,Link,0,NEED,' ')
     if (Del=='.') IQ(Link-5)=-max(Ie/Leng,-IQ(Link-5))
  }
  IQUEST(1)=0
END
 
subroutine REBANKM(i)
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
   IrMode=i
end
*CMZ :  1.00/00 07/09/95  19.44.56  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
      subroutine   R B D E F  (CNAME,FIRST,LAST,FORM,COMMENT)
*                                                                  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
*
      CHARACTER*(*) CNAME,FORM
      INTEGER       FIRST,LAST,COMMENT,LOCF,I,J
 
*   - FIND PLACE
      IF (LU==0) LU=6
      CNAM=CNAME(1:4)
*   - names will be ordered in the table
      Do J=1,NDD { IF (DDL(1,J)>INAM) Break; }
 
*   - is there a free place left ?
      IF NDD>NDDMAX
      { OUTPUT CNAME; (' RBDEF Fatal Error - lack of space, Bank=',A4); STOP }
 
*   - shift upper part of the table
      DO I=NDD,J,-1 {  CALL UCOPY(DDL(1,I),DDL(1,I+1),LDD) }
      NDD=NDD+1
 
*   - STORE a DDL line
      DDL(1,J)=INAM
      DDL(2,J)=LOCF(FIRST)-LOCF(IQ)
      DDL(3,J)=LOCF(LAST)-LOCF(FIRST)+1
      CALL MZFORM(CNAME,FORM,DDL(4,J))
      DDL(5,J)=COMMENT
*
      END
 
*CMZ :  1.30/00 10/01/97  07.02.21  by  Pavel Nevski
*CMZ :  1.00/00 07/09/95  19.30.39  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
               function   R B G E T  (CNAME,NVL)
*                                                                  *
* Modifications:                                                   *
* PN, 27/11/96 - counting access redone. Result is always >=0      *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
*
      CHARACTER CNAME*(*)
      INTEGER RBGET,NVL(*),LINK,IA,L
*
      CALL REBANK (CNAME,NVL,-BIG,LINK,IA)
*
*     Special counting request (last NVL = 0)
      IF NVL(KK)==0
      { L=Link
        If L>0&Ia>0 { RBGET=II-1 " row count" }
        ELSE        { RBGET=0; while L>0 { RBGET+=1; L=LQ(L) }}
        Return
      }
*     CHECK window ACCESS  (bank access successful):
      RBGET=-1;      Check LINK>0
      RBGET=0;       Check IADR!=0
*     DATA READY:
      L=MIN(IQ(LINK-1)-IA,LENG);       RBGET=L
      IF (L>0) CALL UCOPY (IQ(LINK+1+IA),IQ(IADR+1),L)
*
      END
 
*CMZ :  1.30/00 17/07/96  18.51.59  by  Pavel Nevski
*CMZ :  1.00/00 07/09/95  22.43.41  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
                 function    R B P U T  (CNAME,NVL)
*                                                                  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
*
      CHARACTER CNAME*(*)
      INTEGER   RBPUT,NVL(*),LINK,IA
 
*     possible error - writing out of chain
      CALL REBANK (CNAME,NVL,BIG,LINK,IA);     RBPUT=-1
      Check LINK>0 & IADR!=0
 
*     DATA READY
      CALL UCOPY (IQ(IADR+1),IQ(LINK+1+IA),LENG)
*     Special counting request ? (Last NVL = 0)
      RBPUT=LENG;     IF (NVL(KK)==0) RBPUT=II
      END
 
 
*CMZ :  1.30/00 17/07/96  18.51.59  by  Pavel Nevski
*CMZ :  1.00/00 19/11/95  23.54.52  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
               subroutine   R B D R O P  (CNAME,NVL)
*                                                                  *
* Modifications:       ReBANK(..Len=0..) ->  No RBDEF call needed  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
*
      CHARACTER CNAME*(*)
      INTEGER   NVL(*),LINK,IA
*
      CALL REBANK (CNAME,NVL,0,LINK,IA)
*
      Check LINK>0 & IADR!=0
      Check NVL(KK)>0 & IA==0
      CALL  MZDROP(IrbDIV,Link,' ')
*
      END
 
*CMZ :  1.30/00 05/06/96  14.16.44  by  Pavel Nevski
*CMZU:  1.00/01 06/01/96  21.35.37  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/01/96
************************************************************************
      SUBROUTINE   R B P U S H D
*                                                                      *
* Description : save a default directory into the RB stack             *
*                                                                      *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
      INTEGER          Nbp,IP1STACK,    IP2STACK,    IEND,IDSTACK
      COMMON /RBSTACK/ Nbp,IP1STACK(20),IP2STACK(20),IEND,IDSTACK(20)
      Logical          First/.true./
*
   If (First) then
       First=.false.
       Call MZLINK(IxStor,'RBSTACK',IP1STACK,IP1STACK,IEND)
   endif
*
   If (Nbp<20) then
      Nbp+=1; IP1STACK(Nbp)=LKARP1; IP2STACK(Nbp)=LKARP2; IDSTACK(Nbp)=IrbDiv;
   else
      <w>;(' RBPUSHD Error: link stack overflow, default bank may be lost')
   endif
*
      END
 
 
*CMZ :  1.30/00 05/06/96  14.31.30  by  Pavel Nevski
*CMZU:  1.00/01 06/01/96  21.35.37  by  Pavel Nevski
*-- Author :    Pavel Nevski   06/01/96
************************************************************************
      SUBROUTINE   R B P O P D
*                                                                      *
* Description : restore default directory from the RB stack            *
*                                                                      *
************************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,RBBANK.
C   - combined DETM + Reconstruction bank access variables - AGI version
      CHARACTER         CNAM*4
      INTEGER           LU,BIG,MM,INAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,
     >                  LDD,NDDMAX,NDD,DDL,NFR,FRTAB,IrMode
      PARAMETER         (LDD=5,NDDMAX=100,MM=2,BIG=99999)
      COMMON /RBXBANK/  LU, CNAM,II,KK,IADR,LENG,IOD,IOX,IrbDIV,IrMode
      COMMON /RBXLIST/  NDD,DDL(LDD,NDDMAX)
      COMMON /RBXFORM/  NFR,FRTAB(NDDMAX)
      EQUIVALENCE       (CNAM,INAM)
*
*KEND.
      INTEGER          Nbp,IP1STACK,    IP2STACK,    IEND,IDSTACK
      COMMON /RBSTACK/ Nbp,IP1STACK(20),IP2STACK(20),IEND,IDSTACK(20)
*
   If (Nbp>0) then
      LKARP1=IP1STACK(Nbp); LKARP2=IP2STACK(Nbp); IrbDiv=IDSTACK(Nbp); Nbp-=1;
   else
      <w>;(' RBPOPD Error: link stack empty, default bank may be lost')
   endif
*
      END
 
 
*CMZ :  1.00/00 03/10/95  18.17.59  by  Pavel Nevski
*-- Author :
********************************************************************
*                                                                  *
            subroutine   ASLSETBA (CHDET,CBank,NPAR,PAR)
*                                                                  *
*     Put CBank parameter bank for detector CHDET into ZEBRA       *
*     Input:  CHDET - detector name                                *
*             CBank - parameter bank name                          *
*             NPAR  - number of parameters to store (counting PAR1)*
*                     If it exceeds the existing bank length,      *
*                     the bank is pushed to the length needed      *
*             PAR   - array of parameters, declared integer not to *
*                     corrupt (possibly) formatted banks           *
*                                                                  *
* Modifications:                            * 21/01/94 - P.Nevski  *
*    If the bank has been previously created by a datacard input   *
*    ( in this case its first word is always DUMMY=-787878)        *
*    only the dummy(undefined) words are rewritten by PAR values.  *
*    VERY useful! datacards may be read before bank definition but *
*    still their input overwrites default definitions called later *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
      CHARACTER*(*) CHDET,CBank
      INTEGER       NPAR,LdetP,I,PAR(Npar)
      REAL          DUMMY/-787878/
*
    Call ASLDETBA (CHDET,CBank,Npar,LdetP);      Check LdetP>0
    IF  Q(LdetP+1)==DUMMY
         {  DO  I=1,ABS(Npar) { IF (Q(LdetP+I)==DUMMY) IQ(LdetP+I)=PAR(I)}}
    ELSE {  Call UCOPY(PAR,Q(LdetP+1),ABS(Npar)) }
    END
 
*CMZ :  1.00/00 03/10/95  18.17.59  by  Pavel Nevski
*-- Author :    Pavel Nevski
********************************************************************
*                                                                  *
          subroutine    ASLGETBA (CHDET,CBank,NPMAX,Npar,PAR)
*                                                                  *
*     Get CBank parameter bank for detector CHdet from ZEBRA       *
*     Input:  CHdet - detector name                                *
*             CBank - parameter bank name                          *
*             NPMAX - maximum number of parameters to return       *
*     Output: Npar  - number of parameters returned(including PAR1)*
*             PAR   - array of parameters,,declared integer not to *
*                     corrupt (possibly) formatted banks           *
*                                                                  *
* Modifications:  Skip empty words ( DUMMY=Nothing!)     10.10.93  *
********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
      INTEGER       NPMAX,Npar,LdetP,I,PAR(NPmax)
      REAL          DUMMY/-787878/
      CHARACTER*(*) CHdet,CBank
      SAVE          LdetP
*
* this is not completely correct because LdetP should be a protected link
* saved somewhere in SCLINKs. Dont know yet what to do.     - PN 11.05.95
   Npar=0
   IF NPMAX>0 { "first bank " Call ASLDETBA (CHdet,CBank,0,LdetP) }
   ELSE       { " next bank " If  (LdetP>0)  LdetP=LQ(LdetP)      }
*
   Check " if the bank is there"  LdetP>0
   Npar=MIN(IQ(LdetP-1),ABS(NPMAX))
   DO I=1,Npar  { IF (Q(LdetP+I)!=DUMMY) PAR(I)=IQ(LdetP+I) }
   END
 
*CMZ :  1.30/00 28/07/96  23.49.57  by  Pavel Nevski
*CMZ :  1.00/00 03/10/95  18.17.59  by  Pavel Nevski
*-- Author :    Pavel Nevski
*********************************************************************
*                                                                   *
         subroutine    ASLDETBA (CHdet,CBank,Npar,LdetP)
*                                                                   *
* This routine gives users access to DET* banks associated with DETE*
* Input: CHdet - 4-character detector name,                         *
*        CBank - 4-character bank name (starting with DET normally) *
*        Npar  - #0 - this is a request to store parameters:        *
*                  >0 create or rewrite single bank (first)         *
*                  <0 new bank is added in a linear structure       *
*              -  0 - request to get a link to an existing bank     *
* Output:LdetP - if >0 - link to the appropriate bank               *
*                                                                   *
* Modifications: More protection put to creat/extend bank - 03.09.93*
*                New words in bank are filled with DUMMY  - 10.10.93*
*                Order of banks in a linear chain changed - 15.02.94*
*                Use SHUNT to free first link for DETP    - 28.07.96*
*********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*CDE,SLDBNK. - Slug auxilary common for SLDETBA routine
      CHARACTER*4  CHFOR
      INTEGER      IOWDS
      COMMON /SLDBNK/ CHFOR,IOWDS(16)
*
      INTEGER      Npar,Mpar,IND,LDETE,LdetP,NEED,NS,IL,JL,NF,INAM,LOLD,I,N
      CHARACTER*4  CHdet,CBank
      REAL         DUMMY/-787878/
*
  LdetP=0
  Mpar=ABS(Npar)
  Call ASLDETN(CHdet,IND)
  IF IND<=0          " the Faculty is not yet booked "
  {"<w> CHdet;(' ASLDETBA: Detector ',a4,' not found in DETM bank !');" return}
*
  LDETE=LQ(LKDETM-IND)
  IF LDETE==0        " same check - technical error  "
  { <w> CHdet,Ind;(' ASLDETBA: bank for ',a4,' not found at index',i5); return}
 
* Try to find existing data set and store input data in it, or get an emty link
  NS=IQ(LDETE-2); NF=0;     Call UCTOH(CBank,INAM,4,4)
  DO IL=1,NS                " Check structural links "
  {  LdetP=LQ(LDETE-IL); IF (LdetP==0 & NF=0) NF=IL;
     IF (LdetP>0 & IQ(LdetP-4)==INAM) GO TO :f:
  }
 
* Bank is not found: if this is a reading request - quit, else book a new link
  LdetP=0;  IF (Mpar==0) return;
  IF NF==0    { IL=NS+1;  Call MZPUSH(IxCONS,LDETE,2,0,' ') }
  else        { IL=NF  }
  IF CBank=='DETP' & IL!=1  "special case - always the first bank"
  {  DO I=IL,2,-1 " {LQ(LDETE-i)=LQ(LDETE-(i-1))}; "
     { Call ZSHUNT(IxCons,LQ(LDETE-(i-1)),LDETE,-IL,1) }
     LQ(LDETE-1)=LdetP;  IL=1
  }
*
:f: IF "bank already exist" LdetP>0 & "it is the first bank" Npar>=0
    {  LOLD = IQ(LdetP-1);        NEED = Mpar-LOLD
       IF (NEED>0) Call MZPUSH(IxCONS,LdetP,0,NEED,' ')
    }
    else " create a new bank (with a required format) "
    {  LOLD=0;         NEED=Mpar;          JL=-IL;        N=1
      " if a linear chain, insert it AT THE END ! (pln, 15.02.94) "
       while Npar<0 & LdetP>0 { JL=0; LDETE=LdetP;  LdetP=LQ(LdetP); N+=1; }
       IF (CHFOR!=CBank | IOWDS(1)==0) IOWDS(1)=3
       Call MZBOOK(IxCONS,LdetP,LDETE,JL,CBank,0,0,Mpar,IOWDS,0)
       If (LdetP>0) IQ(LdetP-5)=N
    }
* Fill new words in the bank with DUMMY value
  IF NEED>0  {  DO I=LOLD+1,Mpar { Q(LdetP+I)=DUMMY } }
   END
 
 
*CMZ :          01/08/98  14.42.35  by  Pavel Nevski
*CMZ :  1.00/00 03/10/95  18.17.59  by  Pavel Nevski
*-- Author :    R. DeWolf   15/07/91
**********************************************************************
*                                                                    *
                SUBROUTINE  ASLDETN(CHDET,IDET)
*                                                                    *
* Given a 4-character detector name, return a user detector number   *
* which is the link number in DETM for the desired DETE bank.        *
**********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
      CHARACTER*(*) CHDET
      INTEGER       IDET
 
      ENTRY   SLDETN (CHDET,IDET)
*
      IDET = -1;      check LkDETM>0
      CALL GLOOK(CHDET,IQ(LkDETM+1),IQ(LkDETM-1),Idet)
      check Idet>0;   If (LQ(LkDETM-Idet)<=0) Idet = 0
*
      END
 
 
*CMZ :          02/08/98  09.36.16  by  Pavel Nevski
*-- Author :    Pavel Nevski   01/08/98
*********************************************************************
*                                                                   *
    subroutine  AgDETP add (Cpar,p,N)
*                                                                   *
* Description: compose a DETP command from the code:                *
*   - new selects a subsystem and drops the old DETP bank           *
*   - add appends the parameter description and its values          *
*********************************************************************
*KEEP,TYPING.
      IMPLICIT NONE
*KEEP,GCBANK.
      INTEGER IQ,LQ,NZEBRA,IXSTOR,IXDIV,IXCONS,LMAIN,LR1,JCG
      INTEGER KWBANK,KWWORK,IWS
      REAL GVERSN,ZVERSN,FENDQ,WS,Q
C
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      INTEGER       JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,SCLINK.
C SLUG link area :    Permanent Links for SLUG:
      INTEGER         LKSLUG,NSLINK
      PARAMETER       (NSLINK=40)
      COMMON /SCLINK/ LKSLUG(NSLINK)
C The following names are equivalenced to LKSLUG.
C The equivalence name is the one used in SLINIB.
      INTEGER LKGLOB,LKDETM,LKTFLM,LKTFLT,LKAMOD,LKAGEV,LKAMCH,LKADIG,
     +        LKMAPP,LKMFLD,LKRUNT,LKEVNT,LKARAW,LKATRI,LKAPRE,LKARP1,
     +        LKARP2,LKARP3,LKDSTD,LKRUN2,LKEVN2,LKVER2,LKKIN2,LKHIT2,
     +        LKGENE
C                                       Link to:
      EQUIVALENCE (LKSLUG(1),LKGLOB)   ! top of temporary HEPEVT Zebra tree
      EQUIVALENCE (LKSLUG(2),LKDETM)   ! top of subdetector structure
      EQUIVALENCE (LKSLUG(3),LKTFLM)   ! permanent track filter structure
      EQUIVALENCE (LKSLUG(4),LKTFLT)   ! temporary track filter structure
      EQUIVALENCE (LKSLUG(5),LKAMOD)   ! MODule parameters (Dont know this)
      EQUIVALENCE (LKSLUG(6),LKAGEV)   ! Link to general event structure
      EQUIVALENCE (LKSLUG(7),LKAMCH)   ! MonteCarlo Hits ( not GEANT I guess)
      EQUIVALENCE (LKSLUG(8),LKADIG)   ! DIGitized hits (again not GEANT...?)
      EQUIVALENCE (LKSLUG(9),LKMAPP)   ! map structure
      EQUIVALENCE (LKSLUG(10),LKMFLD)  ! magnetic field banks
      EQUIVALENCE (LKSLUG(11),LKRUNT)  ! run tree bank (vertical structure)
      EQUIVALENCE (LKSLUG(12),LKEVNT)  ! event tree bank (vertical struct)
      EQUIVALENCE (LKSLUG(13),LKARAW)  ! raw data structure
      EQUIVALENCE (LKSLUG(14),LKATRI)  ! trigger banks
      EQUIVALENCE (LKSLUG(15),LKAPRE)  ! preprocessed hits
      EQUIVALENCE (LKSLUG(16),LKARP1)  ! reconstuction phase 1 banks
      EQUIVALENCE (LKSLUG(17),LKARP2)  ! reconstuction phase 2 banks
      EQUIVALENCE (LKSLUG(18),LKARP3)  ! reconstuction phase 3 banks
      EQUIVALENCE (LKSLUG(19),LKDSTD)  ! DST data banks
      EQUIVALENCE (LKSLUG(20),LKRUN2)  ! run tree bank for secondary run
      EQUIVALENCE (LKSLUG(21),LKEVN2)  ! event tree bank for secondary events
      EQUIVALENCE (LKSLUG(22),LKVER2)  ! secondary GEANT VERT bank
      EQUIVALENCE (LKSLUG(23),LKKIN2)  ! secondary GEANT KINE bank
      EQUIVALENCE (LKSLUG(24),LKHIT2)  ! secondary GEANT HITS bank
      EQUIVALENCE (LKSLUG(26),LKGENE)  ! old slug ZEBRA generator structure
*KEND.
   Character   Cpar*(*),EQ*1/'='/,Cd*4/'none'/
   Integer     LENOCC,Par(1000),p(N),N,L,I,J,LL,Id/0/,Ld
   Real        R
   Equivalence (R,I)
*
    Call ASLGETBA (Cd,'DETP',1000,LL,Par)
    L=Lenocc(Cpar)
    If id<=0
    {  print *,' AgDETP error: system undefined ',Cd,': ',cpar,p }
    else
    {  Call UCTOH (Cpar,Par(LL+1),4,L);  LL+=(L+3)/4;
       do j=1,N
       {  I=p(j); if (abs(I)<10000) R=p(j);  LL+=1; Par(LL)=I; }
       Call ASLSETBA (Cd,'DETP',LL,Par)
    }
    return
*
    entry AgDETP new (Cpar)
    Cd=Cpar;  Call CLTOU(cd);  Call ASBDETE (Cd,id);  Check Id>0
    Call ASLDETBA (Cd,'DETP',1,Ld);  If (Ld>0) Call MZDROP (IxCons,Ld,' ')
    Call MZFLAG(IxCons,LQ(LkDetm-id),1,'Z')
*
   end
 
 
