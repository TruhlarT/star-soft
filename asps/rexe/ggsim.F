*CMZ :  1.30/00 05/03/96  15.55.16  by  Unknown
*CMZ :  1.00/01 02/02/96  10.45.45  by  G. Poulard
*CMZ :  3.21/02 29/03/94  15.41.30  by  S.Giani
*-- Author :
      SUBROUTINE GSNGTR(X,P,IACT,SNEXT,SNXT,SAFE,INSIDE)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *                                                                *
C.    *    Routine to determine the shortest distance from the point   *
C.    *    X(1-3) to the boundary of the shape of type GTRA defined    *
C.    *    by the parameters P along the vector X(4-6). If INSIDE is   *
C.    *    1 then the point is inside the shape and the distance is    *
C.    *    returned as SNEXT. If INSIDE is 0 then the point is         *
C.    *    outside the shape and if the line hits the shape then       *
C.    *    if the new distance is less than the                        *
C.    *    old value of SNEXT the new distance is returned as SNEXT.   *
C.    *                                                                *
C.    *          Called by : GNEXT, GTNEXT                             *
C.    *          A.C.McPherson   22nd April 1985.                      *
C.    *                                                                *
C.    *   Shekhtman: SL,SL1,SM,SM1 declared as DOUBLE PRECISION        *
C.    *                                                                *
C.    ******************************************************************
C.
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
C
      DOUBLE PRECISION X0,Y0,DXDZ,DYDZ,A,B,C,DISC,X1,X2,X3,SN,CP,SMALL
      DOUBLE PRECISION SL,SL1,SM,SM1
      LOGICAL FIRST  / .TRUE. /
      LOGICAL LPRINT / .TRUE. /
!
      PARAMETER (SMALL=1E-10)
C
      DIMENSION X(6),P(30),SN(2,5),IOUT(5),X0(4),Y0(4),DXDZ(4),DYDZ(4)
C.
C.                ---------------------------------------------
C.
C
C               Compute Safety distance
C
      IF(IACT.LT.3) CALL GSAGTR(X,P,SAFE,INSIDE)
      SNXT=BIG
      IF (IACT .EQ. 0) GO TO 999
      IF (IACT .EQ. 1) THEN
        IF (SNEXT .LT. SAFE) GO TO 999
      ENDIF
C
C               First compute the distance along the line to the
C               boundaries.
C
C               The distance to the planes defined by z=+/-P(1).
C
      IF(X(6).EQ.0.0) THEN
          SN(1,1)=BIG
          SN(2,1)=BIG
          GOTO 10
      ENDIF
      SN(1,1)=(-P(1)-X(3))/X(6)
      SN(2,1)=(P(1)-X(3))/X(6)
      IF(X(6).GT.0.0) GO TO 10
      ST=SN(2,1)
      SN(2,1)=SN(1,1)
      SN(1,1)=ST
   10 CONTINUE
C
C               The distance to the remaining four surfaces.
C
      DO 20 I=1,4
      X0(I)=P(I*4+11)
      Y0(I)=P(I*4+12)
      DXDZ(I)=P(I*4+13)
      DYDZ(I)=P(I*4+14)
   20 CONTINUE
C
      DO 65 I=1,4
      J=I+1
      IF(J.EQ.5) J=1
C
      A=(X(4)-DXDZ(I)*X(6))*(DYDZ(J)-DYDZ(I))*X(6) -
     +(X(5)-DYDZ(I)*X(6))*(DXDZ(J)-DXDZ(I))*X(6)
C
      B=(X(4)-DXDZ(I)*X(6))*(Y0(J)-Y0(I)+(DYDZ(J)-DYDZ(I))*X(3)) +
     +(X(1)-X0(I)-DXDZ(I)*X(3))*(DYDZ(J)-DYDZ(I))*X(6) -
     +(X(5)-DYDZ(I)*X(6))*(X0(J)-X0(I)+(DXDZ(J)-DXDZ(I))*X(3)) -
     +(X(2)-Y0(I)-DYDZ(I)*X(3))*(DXDZ(J)-DXDZ(I))*X(6)
C
      C=(X(1)-X0(I)-DXDZ(I)*X(3))*(Y0(J)-Y0(I)+(DYDZ(J)-DYDZ(I))*X(3))
     + - (X(2)-Y0(I)-DYDZ(I)*X(3))*(X0(J)-X0(I)+(DXDZ(J)-DXDZ(I))*X(3))
C
      IOUT(I+1)=0
      IF(C.GT.0.0) IOUT(I+1)=1
C
C             The solutions are in the normal form:
C             s = (-B+/-SQRT(B*B-4.0*A*C))*0.5/A
C
      SN(1,I+1)=BIG
      SN(2,I+1)=BIG
      IF(ABS(A).GT.1.0E-10) GO TO 30
C
C             A = 0 only one solution.
C
      IF(ABS(B).LT.1.0E-10) GO TO 60
C
      SN(1,I+1)=-C/B
      GO TO 60
C
   30 CONTINUE
      IF(ABS(C).GT.1.0E-10) GO TO 40
      SN(1,I+1)=0.0
      SN(2,I+1)=0.0
      IF(ABS(B).LT.1.0E-10) GO TO 60
      SN(1,I+1)=-C/B
      IF(C.EQ.0.0) SN(1,I+1)=SIGN(SMALL,B)
      SN(2,I+1)=-B/A
      GO TO 50
C
   40 CONTINUE
      DISC=B*B-A*C*4.0
      IF(DISC.LT.0.0) GO TO 60
      IF(DISC.GT.0.0) DISC=SQRT(DISC)
      SN(1,I+1)=(-B-DISC)*0.5/A
      SN(2,I+1)=(-B+DISC)*0.5/A
C
   50 CONTINUE
      IF(SN(2,I+1).GT.SN(1,I+1)) GO TO 60
      ST=SN(2,I+1)
      SN(2,I+1)=SN(1,I+1)
      SN(1,I+1)=ST
C
   60 CONTINUE
C
      DO 65 K=1,2
      IF(ABS(SN(K,I+1)).GT.1.0E+05.OR.ABS(SN(K,I+1)).LT.1.0E-05)
     +GO TO 65
C
      X1=X(1)+SN(K,I+1)*X(4)
      X2=X(2)+SN(K,I+1)*X(5)
      X3=X(3)+SN(K,I+1)*X(6)
      CP=(X1-X0(I)-DXDZ(I)*X3)*(Y0(J)-Y0(I)+(DYDZ(J)-DYDZ(I))*X3)
     + - (X2-Y0(I)-DYDZ(I)*X3)*(X0(J)-X0(I)+(DXDZ(J)-DXDZ(I))*X3)
      CP=CP/SQRT((X0(J)-X0(I)+(DXDZ(J)-DXDZ(I))*X3)**2+
     +   (Y0(J)-Y0(I)+(DYDZ(J)-DYDZ(I))*X3)**2)
C
      IF(ABS(CP).LT.0.0001) GO TO 65
      IF(ABS(CP/SN(K,I+1)).LT.1.0E-06) GO TO 65
      IF ( FIRST.AND.LPRINT ) THEN
           IF (First) Print *,' * GSNGTR: corrected version *'
           FIRST = .FALSE.
           WRITE(CHMAIL,1020) I,K,SN(K,I+1)
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1021) X
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1022) X1,X2,X3,CP
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1023) A,B,C,DISC
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1024) INSIDE
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1025) X0
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1026) Y0
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1027) DXDZ
           CALL GMAIL(0,0)
           WRITE(CHMAIL,1028) DYDZ
           CALL GMAIL(0,0)
      ENDIF
 1020 FORMAT('0 GSNGTR ERROR - I,K =',2I2,' SN =',E13.5)
 1021 FORMAT(' X =',6F15.6)
 1022 FORMAT(' X1,X2,X3 =',3F15.6,' CP =',E15.6)
 1023 FORMAT(' A =',E15.6,' B =',E15.6,' C =',E15.6,' DISC =',E15.6)
 1024 FORMAT(' INSIDE =',I3)
 1025 FORMAT('   X0 =',4E15.6)
 1026 FORMAT('   Y0 =',4E15.6)
 1027 FORMAT(' DXDZ =',4E15.6)
 1028 FORMAT(' DYDZ =',4E15.6)
C
   65 CONTINUE
C
C
C             Have computed the two distances for the z planes and
C             the four surfaces. Combine them accordingly as to
C             whether the point is inside or outside the shape.
C
      IF(INSIDE.EQ.0) GO TO 80
C
C             Point is inside shape.
C
      DO 70 I=1,5
      DO 70 J=1,2
      IF(SN(J,I).GT.0.0.AND.SN(J,I).LT.SNXT) SNXT=SN(J,I)
   70 CONTINUE
      GO TO 999
C
   80 CONTINUE
C
C             Point is outside shape.
C
      IOUT(1)=0
      IF(ABS(X(3)).GT.P(1)) IOUT(1)=1
C
C             For each of five sets of SN and IOUT, IOUT(I) equal to 1
C             indicates that the point is outside the shape by the Ith
C             test, SN(1,I) is the distance to the first change in the
C             test and SN(2,I) is the distance to the second change.
C             The remaining logic just attempts to find a distance when
C             the line is inside by all five tests, bearing in mind that
C             for some tests the line can start inside, leave and return
C             inside.
C
      SL=-1.0
      SM=BIG
      SM1=BIG
      DO 100 I=1,5
      IF(IOUT(I).EQ.0) GO TO 90
      IF(SN(2,I).LT.0.0) GO TO 999
      IF(SN(1,I).LT.0.0.AND.SN(2,I).GT.SL) SL=SN(2,I)
      IF(SN(1,I).GT.SL) SL=SN(1,I)
      IF(SN(1,I).GE.0.0.AND.SN(2,I).LT.SM) SM=SN(2,I)
      GO TO 100
   90 CONTINUE
      IF(SN(1,I).LT.0.0.AND.SN(2,I).GE.0.0.AND.SN(2,I).LT.SM) SM=SN(2,I)
      IF(SN(1,I).LT.0.0.OR.SN(1,I).GT.SM1) GO TO 100
      IF(SN(1,I).GE.SN(2,I)) GO TO 100
      SM1=SN(1,I)
      SL1=SN(2,I)
  100 CONTINUE
C
C             SL is the largest of the five distances to the first
C             time the line is inside. SM is the smallest to the
C             last time the point is inside. SM1 is the smallest
C             distance to when the line is temporarily outside
C             one of the tests.
C
      IF(SM.LE.SL) GO TO 999
      IF(SM1.GT.SL) GO TO 130
C
  110 CONTINUE
C
C             In this loop SL is updated by the return after SM1
C             if SM1 is less than SL.
C
      SL=SL1
      IF(SM.LE.SL) GO TO 999
      SM1=SM
C
      DO 120 I=1,5
      IF(IOUT(I).EQ.1) GO TO 120
      IF(SN(2,I).LE.SL.OR.SN(1,I).GT.SM1) GO TO 120
      IF(SN(1,I).GE.SN(2,I)) GO TO 120
      SM1=SN(1,I)
      SL1=SN(2,I)
  120 CONTINUE
C
      IF(SM1.GT.SL) GO TO 130
C
      GO TO 110
  130 CONTINUE
C
      IF(SL.LT.SNXT) SNXT=SL
C
  999 CONTINUE
      END
*CMZ :  1.00/00 25/05/95  03.58.23  by  A. James Cook
*-- Author :
      SUBROUTINE GFLRAD(IAXIS,ISH,IROT,DX,PARS,CL,CH,IERR)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    ROUTINE TO COMPUTE THE LIMITS IN R FOR THE SHAPE ISH        *
C.    *    DISPLACED BY THE VECTOR DX AND ROTATED BY THE MATRIX IROT.  *
C.    *    IF IAXIS = 4 THE R IS THE XY PLANE R, IF IAXIS = 5 IT IS    *
C.    *    THE 3 DINEMSIONAL SPACE R. THE SHAPE HAS NPAR PARAMETERS    *
C.    *    IN THE ARRAY PARS. THE LOWER LIMIT IS RETURNED IN CL AND    *
C.    *    THE HIGHER IN CH. IF THE CALCULATION CANNOT BE PERFORMED    *
C.    *    IERR IS SET TO 1 OTHERWISE IT IS SET TO 0.                  *
C.    *                                                                *
C.    *    ==>Called by : GFCLIM                                       *
C.    *         Author  A.McPherson  *********                         *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCSHNO.
      PARAMETER ( NSBOX=1,  NSTRD1=2, NSTRD2=3, NSTRAP=4, NSTUBE=5,
     +  NSTUBS=6, NSCONE=7, NSCONS=8, NSSPHE=9, NSPARA=10,NSPGON=11,
     +  NSPCON=12,NSELTU=13,NSHYPE=14,NSGTRA=28, NSCTUB=29 )
*KEND.
      DIMENSION DX(3),PARS(11),X(3),XT(3)
C.
C.           --------------------------------------------------
C.
      IERR=1
C
C            FIRST CALCULATE THE LENGTH OF THE DISPLACEMENT OF THE
C            ORIGIN.
C
      DXS=DX(1)*DX(1)+DX(2)*DX(2)
      IF(IAXIS.EQ.5) DXS=DXS+DX(3)*DX(3)
      IF(DXS.GT.0.0) DXS=SQRT(DXS)
C
      IF(ISH.GT.4.AND.ISH.NE.10.AND.ISH.NE.28) GO TO 40
C
C          CUBOIDS, TRAPEZOIDS, PARALLELEPIPEDS.
C
      CH=0.0
      CL=DXS
C
      DO 30 IP=1,8
C
C           THIS IS A LOOP OVER THE 8 CORNERS.
C           FIRST FIND THE LOCAL COORDINATES.
C
      IF(ISH.EQ.28) THEN
C
C            General twisted trapezoid.
C
         IL=(IP+1)/2
         I0=IL*4+11
         IS=(IP-IL*2)*2+1
         X(3)=PARS(1)*IS
         X(1)=PARS(I0)+PARS(I0+2)*X(3)
         X(2)=PARS(I0+1)+PARS(I0+3)*X(3)
         GO TO 20
C
      ENDIF
C
      IP3=ISH+2
      IF(ISH.EQ.10) IP3=3
      IF(ISH.EQ.4) IP3=1
      X(3)=PARS(IP3)
      IF(IP.LE.4) X(3)=-X(3)
      IP2=3
      IF(ISH.GT.2.AND.X(3).GT.0.0) IP2=4
      IF(ISH.EQ.1.OR.ISH.EQ.10) IP2=2
      IF(ISH.EQ.4) IP2=4
      IF(ISH.EQ.4.AND.X(3).GT.0.0) IP2=8
      X(2)=PARS(IP2)
      IF(MOD(IP+3,4).LT.2) X(2)=-X(2)
      IP1=1
      IF(ISH.NE.1.AND.ISH.NE.10.AND.X(3).GT.0.0) IP1=2
      IF(ISH.EQ.4) IP1=5
      IF(ISH.EQ.4.AND.X(3).GT.0.0) IP1=IP1+4
      IF(ISH.EQ.4.AND.X(2).GT.0.0) IP1=IP1+1
      X(1)=PARS(IP1)
      IF(MOD(IP,2).EQ.1) X(1)=-X(1)
C
      IF(ISH.NE.10) GO TO 10
      X(1)=X(1)+X(2)*PARS(4)+X(3)*PARS(5)
      X(2)=X(2)+X(3)*PARS(6)
   10 CONTINUE
C
      IF(ISH.NE.4) GO TO 20
      IP4=7
      IF(X(3).GT.0.0) IP4=11
      X(1)=X(1)+X(2)*PARS(IP4)+X(3)*PARS(2)
      X(2)=X(2)+X(3)*PARS(3)
   20 CONTINUE
C
C          ROTATE.
C
      JROT=LQ(JROTM-IROT)
      XT(1)=X(1)
      XT(2)=X(2)
      XT(3)=X(3)
      IF(IROT.NE.0) CALL GINROT(X,Q(JROT+1),XT)
C
C          NOW COMPUTE RMIN = PROJECTED R ON DX AND RMAX = R
C          AND UPDATE LIMITS IF NECESSARY.
C
      R2=(XT(1)+DX(1))**2+(XT(2)+DX(2))**2
      IF(IAXIS.EQ.5) R2=R2+(XT(3)+DX(3))**2
      R=SQRT(R2)
      IF(R.GT.CH) CH=R
C
      IF(CL.LE.0.0) GO TO 30
C
      XPT=DX(1)*XT(1)+DX(2)*XT(2)
      IF(IAXIS.EQ.5) XPT=XPT+DX(3)*XT(3)
      IF(DXS.LE.1.0E-05) GO TO 30
      RMN=DXS+XPT/DXS
      IF(RMN.LT.CL) CL=RMN
C
   30 CONTINUE
C
      IF(CL.LE.0.0) CL=0.0
C
      IERR=0
      GO TO 999
C
   40 CONTINUE
      IF(ISH.GT.8.AND.ISH.NE.NSCTUB.AND.ISH.NE.13.AND.ISH.NE.14)GO TO 80
C
C             TUBES AND CONES.
C
      IP3=3
      IF(ISH.GT.6.AND.ISH.NE.NSCTUB.AND.ISH.NE.13.AND.ISH.NE.14) IP3=1
      DZ=PARS(IP3)
      R=PARS(2)
      IF(ISH.EQ.NSCTUB) THEN
        S1 = (1.0-PARS(8))*(1.0+PARS(8))
        IF( S1 .GT. 0.0) S1 = SQRT(S1)
        S2 = (1.0-PARS(11))*(1.0+PARS(11))
        IF( S2 .GT. 0.0) S2 = SQRT(S2)
        IF( S2 .GT. S1 ) S1 = S2
        DZ = DZ+R*S1
      ENDIF
**
      IF(ISH.EQ.13) THEN
**
**       APPROXIME TO A CYLINDER WHIT RADIUS
**       EQUAL TO THE ELLIPSE MAJOR AXIS
**
         RMN=0.0
         IF(PARS(1).GT.R) R=PARS(1)
         GOTO 50
      ENDIF
      RMN=PARS(1)
*
      IF(ISH.EQ.14) THEN
        R = SQRT(PARS(2)**2+(PARS(3)*TAN(PARS(4)*DEGRAD))**2)
        GO TO 50
      ENDIF
C
      IF(ISH.LE.6.OR.ISH.EQ.NSCTUB) GO TO 50
C
      R=PARS(3)
      IF(PARS(5).GT.R) R=PARS(5)
      RMN=PARS(2)
      IF(PARS(4).LT.RMN) RMN=PARS(4)
C
   50 CONTINUE
C
C          ROTATE THE LOCAL Z AXIS.
C
      X(1)=0.0
      X(2)=0.0
      X(3)=1.0
      JROT=LQ(JROTM-IROT)
      XT(1)=X(1)
      XT(2)=X(2)
      XT(3)=X(3)
      IF(IROT.NE.0) CALL GINROT(X,Q(JROT+1),XT)
C
C          COMPUTE RMIN AND RMAX ASSUMING COMPLETE TUBE HALF
C          LENGTH DZ AND RADIUS R.
C
      CH=DXS+R
      CL=DXS-R
      DO 60 IS=-1,1,2
         R2=(DX(1)+IS*DZ*XT(1))**2+(DX(2)+IS*DZ*XT(2))**2
         IF(IAXIS.EQ.5) R2=R2+(DX(3)+IS*DZ*XT(3))**2
         R1=SQRT(R2)
         CH=MAX(CH,R1+R)
         CL=MIN(CL,R1-R)
   60 CONTINUE
      IF(CL.LT.0.0) CL=0.0
      IF(IROT.EQ.0.AND.DXS.LT.1.0E-05) CL=RMN
      IERR=0
C
      GO TO 999
C
   80 CONTINUE
      IF(ISH.GT.9) GO TO 999
C
C           SPHERE.
C
      CL=DXS-PARS(2)
      IF(CL.LT.0.0) CL=0.0
      CH=DXS+PARS(2)
      IF(IAXIS.EQ.5.AND.DXS.LT.1.0E-05) CL=PARS(1)
      IERR=0
C
  999 CONTINUE
      END
*CMZU:  1.00/01 25/01/96  14.17.49  by  A. DellAcqua
*CMZ :  3.21/02 29/03/94  15.41.28  by  S.Giani
*-- Author :
      SUBROUTINE GGORDQ (IVO)
C.
C.    *****************************************************************
C.    *                                                               *
C.    *    Find and order the boundaries of the contents of the       *
C.    *    IVOth volume, with respect to coordinate IAX :             *
C.    *           IAX = 1    X Axis                                   *
C.    *           IAX = 2    Y Axis                                   *
C.    *           IAX = 3    Z Axis                                   *
C.    *           IAX = 4    Rxy                                      *
C.    *           IAX = 5    Rxyz                                     *
C.    *           IAX = 6    PHI   (PHI=0 => X axis)                  *
C.    *           IAX = 7    THETA (THETA=0 => Z axis)                *
C.    *    All values of IAX will be tried and then that value is     *
C.    *    chosen, that results in the smallest number of volumes per *
C.    *    division.                                                  *
C.    *    Called by : GGCLOS                                         *
C.    *    Author: Stephan Egli (large parts are copies of GGORD)     *
C.    *                                                               *
C.    *****************************************************************
C.
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
 
      DIMENSION CLOW(500),CHIGH(500),CORD(1000),ITYPE(1000),
     +ICONT(500),ICON(1000),ICONS(500)
      EQUIVALENCE (CLOW(1),WS(1)),(CHIGH(1),WS(501))
      EQUIVALENCE (CORD(1),WS(1001)),(ITYPE(1),WS(2001))
      EQUIVALENCE (ICONT(1),WS(3001)),(ICON(1),WS(3501))
      EQUIVALENCE (ICONS(1),WS(4501))
C
      CHARACTER*4 NAME
 
C.    ------------------------------------------------------------------
*
      JVO = LQ(JVOLUM-IVO)
      CALL UHTOC(IQ(JVOLUM+IVO),4,NAME,4)
      NIN = Q(JVO+3)
      IAXNOW = 0
      IF(IQ(JVO-2).EQ.NIN+2) THEN
*
* *** This is to allow re-entry in the routine from the interactive
* *** version.
         JNEAR = LQ(JVO-NIN-1)
         IF(JNEAR.GT.0) THEN
            JSB = LQ(JNEAR)
            IF(JSB.GT.0) THEN
               IAXNOW = Q(JSB+1)
            ENDIF
         ENDIF
      ENDIF
      IF(IAXNOW.EQ.0) THEN
         IAXNOW=-Q(JVO+1)
      ENDIF
*   assume that ordering can not be done unless proven otherwise
      Q(JVO+1)=0.
      RBEST=1.E9
 
* try all possible axes
 
      DO 1 IAX=1,7
 
*   count number of additional words needed and total number of volumes
*   in all divisions
 
      NCOALL=0
*
* *** Find the upper and lower coordinates of each content
*
      DO 50 IN = 1,NIN
         CALL GFCLIM (JVO, IN, IAX, CLOW(IN), CHIGH(IN), IERR)
         IF (IERR.NE.0) GOTO 1
   50 CONTINUE
*
* *** Order the coordinate limits, keeping track of the associated
*           content number
*
      CALL GFCORD (NIN, CLOW, CHIGH, CORD, ITYPE, ICON)
      NC = NIN*2
*
*  **   Count and load up the distinct boundaries
*
      IBO = 0
      DO 60 IC = 1,NC
         IBO = IBO +1
         IF (IBO.EQ.1) GO TO 60
         IF (CORD(IC)-CORD(IC-1).LT.1.E-4) IBO = IBO -1
   60 CONTINUE
      NDIV  = IBO -1
      IF (IAX.EQ.6) NDIV = IBO
 
*   *   Load up number of contents in each section
*
      IDIV    = 0
      NCONT   = 1
      ICONT(1)= ICON(1)
      IF (IAX.NE.6) GO TO 70
      NCONT   = 0
      NSTOR   = 0
      ICONT(1)= 0
      DO 65 IN = 1,NIN
         IF (CHIGH(IN).GT.CLOW(IN)) GO TO 65
*           (this content straddles PHI=0.)
         NSTOR = NSTOR +1
         ICONS(NSTOR) = IN
         IF (ICON(1).EQ.IN) GO TO 65
*           (IN is in 1st division as well)
         NCONT = NCONT +1
         ICONT(NCONT) = IN
   65 CONTINUE
*
      IF (ITYPE(1).EQ.2) GO TO 70
*            (first boundary is a low, add the new content)
      NCONT = NCONT +1
      ICONT(NCONT) = ICON(1)
*
   70 CONTINUE
*
      DO 130 IC = 2,NC
         IDIV = IDIV +1
         IF (CORD(IC)-CORD(IC-1).LT.1.E-4) GO TO 90
*
*          New division, load up last division
*
         IF (NCONT.LE.0) GO TO 100
         NCOALL=NCOALL+NCONT
         GO TO 100
   90    CONTINUE
         IDIV = IDIV -1
*
  100    CONTINUE
*
*         Update contents of current division
*
         IF (ITYPE(IC).EQ.1) GO TO 120
*
*         This boundary was a high, so one less content
*
         ICP = 0
         DO 110 ICNT = 1,NCONT
            IF (ICONT(ICNT).EQ.ICON(IC)) ICP=1
         IF (ICP.EQ.1) ICONT(ICNT) = ICONT(ICNT+1)
  110    CONTINUE
         NCONT = NCONT -1
         GO TO 130
*
  120    CONTINUE
*
*          This boundary was a low, so one extra content
*
         NCONT = NCONT +1
         ICONT(NCONT) = ICON(IC)
*
  130 CONTINUE
*
      IF(IAX.EQ.6) NCOALL = NCOALL+NSTOR
      RNOW=FLOAT(NCOALL)/NDIV
      IF(RNOW.LT.RBEST)THEN
        IAXOPT=IAX
        RBEST=RNOW
        NDIVB=NDIV
      ENDIF
 
* end of loop over IAX
 
1     CONTINUE
 
 
* now the best axis is selected - compare with axis requested by CALL
* to GSORD (if any)
 
      IF(IAXNOW.GT.0)THEN
 
*        WRITE (CHMAIL,1002) NAME,NIN,IAXOPT,NDIVB,RBEST,IAXNOW
*        CALL  GMAIL (0, 0)
 1002   FORMAT(' GGORDQ : Volume ',A4,2X,'NIN=',I4,' IAX=',I2,2X,
     +    'NDIV=',I3,2X,'NVOL/DIV=',F5.1,2X,'IAX wanted by user:',I2)
 
      ELSE
 
*        WRITE (CHMAIL,1003) NAME,NIN,IAXOPT,NDIVB,RBEST
*        CALL  GMAIL (0, 0)
 1003   FORMAT(' GGORDQ : Volume ',A4,2X,'NIN=',I4,' IAX=',I2,2X,
     +    'NDIV=',I3,2X,'NVOL/DIV=',F5.1)
 
      ENDIF
 
* overwrite old axis and store sorting information for new axis
 
      Q(JVO+1)=-IAXOPT
      CALL GGORD(IVO)
 
      END
*CMZ :  1.30/00 02/06/96  16.40.08  by  Pavel Nevski
*CMZ :  1.00/00 16/08/95  01.09.49  by  Pavel Nevski
*-- Author :
      SUBROUTINE GSCHIT(ISET,IDET,ITRA,NUMBV,HITS,NHSUM,IHIT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Store HITS values into detector IUDET of set IUSET       *
C.    *                                                                *
C.    *       NUMBV  volume numbers                                    *
C.    *       HITS  array of values for the elements of current hit    *
C.    *       ITRA  track number associated to this hit                *
C.    *       IHIT  output parameter containing the hit number         *
C.    *             If IHIT=0  hit has not been stored                 *
C.    *                                                                *
C.    *       Same action as GSAHIT but in case the physical volume    *
C.    *       specified by NUMBV contains already some hit for the     *
C.    *       same track, then the routine will sum up the last NHSUM  *
C.    *       elements of the hit.                                     *
C.    *        In order to use that routine , no packing must be       *
C.    *        specified for these NHSUM last hits.                    *
C.    *        If NHSUM.LE.0 then GSCHIT is the same as GSAHIT.        *
C.    *                                                                *
C.    *    ==>Called by : <USER>, GUSTEP                               *
C.    *       Authors    R.Brun, M.Maire  *********                    *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      COMMON/GCLOCA/NLOCAL(2),JS,JD,JDH,JH,JHD,LOCAL(15)
      DIMENSION NUMBV(*),HITS(*)
      PARAMETER (MAXINT=2147483647)
      SAVE NMESS
      DATA NMESS/0/
C.
C.    ------------------------------------------------------------------
C.
      CALL GSAHIT(ISET,IDET,ITRA,NUMBV,HITS,IHIT)
      IF (IHIT.LE.1)  GO TO 999
      IF (NHSUM.LE.0) GO TO 999
C
      NV=IQ(JD+1)
      NH=IQ(JD+3)
      NW=NV+NH+1
      JNEWH = JHD+(IHIT-1)*NW
      JCURR = JNEWH
C
      DO 30 I=1,IHIT-1
         JCURR = JCURR-NW
C
C             Check if track number is ITRA
C
         IF (ITRA.NE.IQ(JCURR+1)) GO TO 999
C
C             Check if volume numbers are the same
C
         DO 10 J=2,NV+1
            IF (IQ(JCURR+J).NE.IQ(JNEWH+J)) GO TO 30
   10    CONTINUE
C
C             Volumes are the same. Now sum the last NHSUM hits
C
         DO 20 K=NW,NW-NHSUM+1,-1
            IF (IQ(JCURR+K).GT.MAXINT-IQ(JNEWH+K)) THEN
               NMESS=NMESS+1
               IF (NMESS.LT.3) THEN
                  WRITE (CHMAIL,10000) IQ(JSET+ISET),IQ(JS+IDET)
10000             FORMAT(' ***** GSCHIT OVERFLOW WARNING FOR SET= ',
     +                                               A4,' DET= ',A4)
                  CALL GMAIL(0,0)
               ENDIF
               GO TO 999
            ELSE
               IQ(JCURR+K)=IQ(JCURR+K)+IQ(JNEWH+K)
            ENDIF
   20    CONTINUE
C
C             Remove temporarily stored hit
C
*****    IHIT=IHIT-1
         IHIT=IHIT-I
         IQ(JH+IDET)=IQ(JH+IDET)-NW
         GO TO 999
   30 CONTINUE
C
  999 CONTINUE
      END
 
 
 
 
*CMZ :  1.30/00 12/05/97  15.31.50  by  Pavel Nevski
*CMZU:  1.00/00 17/03/94  10.22.21  by  Andrea DellAcqua
*-- Author :    *MRT : by Pavel Nevski
*----------------------------------------------------------------------*
      SUBROUTINE GUSCNTR(PRECOR)
*                                                                      *
* Description :  routine to control a looping near a boundary          *
* Arguments   :  PRECOR  (modified) GEANT tracking precision           *
*                                                                      *
* Author      :  Pavel Nevski                       Date : 25/05/93    *
* Modification:  Never done                                            *
*----------------------------------------------------------------------*
*KEEP,TYPING.
      IMPLICIT NONE
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
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
      INTEGER ICNT,IPRI,MSTEP,LU
      REAL SAFEOLD,ONLY,PRECOR
      DATA ICNT,MSTEP /0,0/
      IPRI=0
      SAFEOLD = SAFETY+STEP
      ONLY=GONLY(NLEVEL)
C   Check IGNEXT==1 & SAFETY<0 & STEP<10*PREC & ONLY>0
      IF (IGNEXT.EQ.1 .AND. SAFETY.LT.0 .AND. STEP.LT.10*PREC
     *    .AND.  ONLY.GT.0 .AND. INWVOL.EQ.0) THEN
         ICNT=ICNT+1
      ELSE
         ICNT=0
      END IF
C   Check ICNT==10
      IF (ICNT.EQ.10) THEN
         IFIELD =0
      END IF
C   Check 11<=ICNT<=18
      IF (11.LE.ICNT.AND.ICNT.LE.18) THEN
         PRECOR=PRECOR*2
      END IF
C   Check 20<=ICNT<=20
      IF (20.LE.ICNT.AND.ICNT.LE.20) THEN
         IPRI =1
      END IF
C   Check NSTEP>=MSTEP+1000
      IF (NSTEP.GE.MSTEP+1000) THEN
         MSTEP = NSTEP
         IPRI=0
      END IF
C   Check NSTEP==MAXNST
      IF (NSTEP.EQ.MAXNST) THEN
         IPRI=3
      END IF
C   If Amax1(Abs(Vect(1)),Abs(Vect(2)))>Rmx \ Abs(Vect(3))>Zmx [Istop=1;]
C   Check IPRI>0
      IF (IPRI.LE.0)GO TO 1
      CALL GPCXYZ
      LU=LOUT
      WRITE(LU,10) NSTEP,ICNT,IGNEXT,PREC,SAFETY,SNEXT,PRECOR
10    FORMAT(5x,'Nstep,icnt,IGnext,Prec,Safety,Snext,Precor=',
     >       2I5,I3,4F10.4)
1     CONTINUE
      END         ! GUSCNTR
*CMZ :  1.40/05 13/06/98  16.35.00  by  Pavel Nevski
*CMZ :  1.30/00 17/04/97  14.00.58  by  Pavel Nevski
*CMZU:  1.00/00 11/07/94  15.46.40  by  Pavel Nevski
*-- Author :
      SUBROUTINE GTRACK
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Controls tracking of current particle,                   *
C.    *        up to end of track for sequential tracking mode, or     *
C.    *        through current volume for parallel tracking mode.      *
C.    *                                                                *
C.    *    ==>Called by : GUTRAK                                       *
C.    *       Authors   : R.Brun, F.Bruyant                            *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
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
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
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
*KEEP,GCPARM.
      COMMON/GCPARM/IPARAM,PCUTGA,PCUTEL,PCUTNE,PCUTHA,PCUTMU
     +             ,NSPARA,MPSTAK,NPGENE
      REAL PACUTS(5)
      EQUIVALENCE (PACUTS(1),PCUTGA)
      INTEGER IPARAM,MPSTAK,NSPARA,NPGENE
      REAL    PCUTGA,PCUTEL,PCUTNE,PCUTHA,PCUTMU
C
*KEEP,GCSETS.
      COMMON/GCSETS/IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV(20)
C
      INTEGER       IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV
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
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
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
*KEND.
      COMMON/GCCHAN/LSAMVL
      LOGICAL LSAMVL
*
      DIMENSION CUTS(10),MECA(5,13)
      EQUIVALENCE (CUTS(1),CUTGAM),(MECA(1,1),IPAIR)
      SAVE PRECOR
      PARAMETER (EPSMAC=1.E-6)
C.
C.    ------------------------------------------------------------------
      ISTOP = 0
      EPSCUR = EPSMAC
      NSTOUT = 0
      INWOLD = 0
      LSAMVL = .FALSE.
*
* *** Check validity of tracking medium and material parameters
*
   10 IF (NUMED.NE.NUMOLD) THEN
         NUMOLD = NUMED
         IUPD   = 0
         JTM    = LQ(JTMED- NUMED)
         DO 20 I = 1,5
            NATMED(I) = IQ(JTM+I)
   20    CONTINUE
         NMAT     = Q(JTM + 6)
         ISVOL    = Q(JTM + 7)
         IFIELD   = Q(JTM + 8)
         FIELDM   = Q(JTM + 9)
         TMAXFD   = Q(JTM + 10)
         STEMAX   = Q(JTM + 11)
         DEEMAX   = Q(JTM + 12)
         EPSIL    = Q(JTM + 13)
         STMIN    = Q(JTM + 14)
         PRECOR   = MIN(0.1*EPSIL, 0.0010)
         IF (LQ(JTM).EQ.0) THEN
            IF (ISTPAR.NE.0) THEN
               DO 30 I = 1,10
                  CUTS(I) = Q(JTMED+I)
   30          CONTINUE
               DO 40 I = 1,13
                  MECA(1,I) = Q(JTMED+10+I)
   40          CONTINUE
               ILABS = Q(JTMED+10+21)
               ISYNC = Q(JTMED+10+22)
               ISTRA = Q(JTMED+10+23)
               ISTPAR = 0
            ENDIF
         ELSE
            JTMN = LQ(JTM)
            DO 50 I = 1,10
               CUTS(I) = Q(JTMN+I)
   50       CONTINUE
            DO 60 I = 1,13
               MECA(1,I) = Q(JTMN+10+I)
   60       CONTINUE
            ILABS = Q(JTMN+10+21)
            ISYNC = Q(JTMN+10+22)
            ISTRA = Q(JTMN+10+23)
            ISTPAR = 1
         ENDIF
*
         JMA   = LQ(JMATE-NMAT)
         JPROB = LQ(JMA-4)
         JMIXT = LQ(JMA-5)
         DO 70 I = 1,5
            NAMATE(I) = IQ(JMA+I)
   70    CONTINUE
         A    = Q(JMA +6)
         Z    = Q(JMA +7)
         DENS = Q(JMA +8)
         RADL = Q(JMA +9)
         ABSL = Q(JMA +10)
         IF(IQ(JTM-2).GE.3.AND.LQ(JTM-3).NE.0.AND.ITCKOV.NE.0.AND.
     +      LQ(LQ(JTM-3)-3).NE.0.AND.Z.GE.1.) THEN
*
* ***  In this tracking medium Cerenkov photons are generated and
* ***  tracked. Set to 1 the corresponding flag.
*
            IMCKOV = 1
         ELSE
            IMCKOV = 0
         ENDIF
*
*
*  **   Update precomputed quantities
*
         IMULL = IMULS
         IF (ILOSS.LE.0) THEN
            DEEMAX = 0.
            ILOSL = 0
         ELSEIF (DEEMAX.GT.0.) THEN
            ILOSL = ILOSS
         ELSE
            ILOSL = 0
         ENDIF
      ENDIF
*
      IF(LSAMVL) THEN
*
*       If now the particle is entering in the same volume where
*       it was exiting from last step, and if it has done this for
*       more than 5 times, we decrease the precision of tracking
         NSTOUT=NSTOUT+1
         IF(MOD(NSTOUT,5).EQ.0) THEN
            EPSCUR=NSTOUT*EPSMAC
*            WRITE(CHMAIL,10000)ITRA,ISTAK,NTMULT,NAPART
*10000          FORMAT(' *** GTRAcCK *** Boundary loop: track ',
*     +         I6,' stack ',I6,' NTMULT ',I8,1X,5A4)
*            CALL GMAIL(1,0)
*            WRITE (CHMAIL,10250) IEVENT,IDEVT,(NRNDM(I),I = 1,2)
*            CALL GMAIL(0,0)
*            WRITE(CHMAIL,10100) EPSCUR
*10100          FORMAT('                Precision now set to ',G10.3)
*            CALL GMAIL(0,1)
         ENDIF
      ELSE
         NSTOUT = 0
         EPSCUR = EPSMAC
      ENDIF
*
      INWVOL = 1
*
* *** Compute SET and DET number if volume is sensitive
*
*      IF (JSET.GT.0) THEN
*         IF(ISVOL.GT.0) THEN
*            CALL GFINDS
*         ELSE
*            IHSET = 0
*            IHDET = 0
*            ISET = 0
*            IDET = 0
*            IDTYPE = 0
*            NVNAME = 0
*         ENDIF
*      ENDIF
*
*    Clear step dependent variables
*
   80 NMEC   = 0
      STEP   = 0.
      DESTEL = 0.
      DESTEP = 0.
      NGKINE = 0
      NGPHOT = 0.
      IGNEXT = 0
      INWOLD = INWVOL
      PREC   = MAX(PRECOR,MAX(ABS(VECT(1)),ABS(VECT(2)),
     +                        ABS(VECT(3)),SLENG)*EPSCUR)
*
*     Give control to user at entrance of volume (INWVOL=1)
*
      IF (INWVOL.EQ.1) THEN
         CALL GUSTEP
         IF (ISTOP.NE.0) GO TO 999
         INWVOL = 0
      ENDIF
*
* *** Propagate particle up to next volume boundary or end of track
*
      INGOTO = 0
      NLEVIN = NLEVEL
      IF (IPARAM.NE.0) THEN
         IF (GEKIN.LE.PACUTS(ITRTYP)) THEN
            NMEC = NMEC+1
            LMEC(NMEC) = 26
            ISTOP = 2
            CALL GUPARA
            GO TO 90
         ENDIF
      ENDIF
      IF      (ITRTYP.EQ.1) THEN
         CALL GTGAMA
      ELSE IF (ITRTYP.EQ.2) THEN
         CALL GTELEC
      ELSE IF (ITRTYP.EQ.3) THEN
         CALL GTNEUT
      ELSE IF (ITRTYP.EQ.4) THEN
         CALL GTHADR
      ELSE IF (ITRTYP.EQ.5) THEN
         CALL GTMUON
      ELSE IF (ITRTYP.EQ.6) THEN
         CALL GTNINO
      ELSE IF (ITRTYP.EQ.7) THEN
         CALL GTCKOV
      ELSE IF (ITRTYP.EQ.8) THEN
         CALL GTHION
      ENDIF
      IF(JGSTAT.NE.0) CALL GFSTAT(10+ITRTYP)
      STLOSS=STEP
*
*     Check for possible endless loop
*
   90 NSTEP = NSTEP +1
      IF (NSTEP.GT.MAXNST) THEN
         IF (ISTOP.EQ.0) THEN
            ISTOP = 99
            IF (IDEBUG.GT.0) THEN
            NMEC  = NMEC +1
            LMEC(NMEC) = 30
            WRITE(CHMAIL,10200) MAXNST
            CALL GMAIL(1,0)
            WRITE(CHMAIL,10250) IEVENT,IDEVT,(NRNDM(I),I = 1,2)
            CALL GMAIL(0,0)
            WRITE(CHMAIL,10300)ITRA,ISTAK,NTMULT,(NAPART(I),I=1,5),
     +      TOFG*1.E9
            CALL GMAIL(0,1)
10200       FORMAT(' *** GTRACK *** More than ',I6,
     +             ' steps, tracking abandoned!')
10250       FORMAT('                IEVENT=',I7,' IDEVT=',I7,
     +             ' Random Seeds = ',I10,2X,I10)
10300       FORMAT('                Track',I6,' stack',I6,' NTMULT',
     +             I8,1X,5A4,'Time of flight ',F10.3,' ns')
            ENDIF
         ENDIF
      ENDIF
*
* *** Give control to user at end of each tracking step
*
      SAFETY = SAFETY -STEP
      CALL GUSTEP
C - pln - 11/7/94  - add user control over loopers
      CALL GUSCNTR(PRECOR)
*
      IF (ISTOP.NE.0) GO TO 999
*
*      Renormalize direction cosines
*
      PMOM = SQRT(VECT(4)**2+VECT(5)**2+VECT(6)**2)
      IF(PMOM.GT.0.) THEN
         CMOD = 1./PMOM
         VECT(4) = VECT(4)*CMOD
         VECT(5) = VECT(5)*CMOD
         VECT(6) = VECT(6)*CMOD
      ENDIF
*
      IF (INWVOL.EQ.0) then
         if (GONLY(NLEVEL).eq.0.and.Safety.le.0.and.Iswit(10).ge.0)
     +                                       CALL GTMEDI(VECT,NMED)
         GO TO 80
      endif
*
      IF (NJTMAX.GT.0) THEN
         CALL GSTRAC
         IF (NLEVIN.EQ.0) GO TO 100
         GO TO 999
      ELSE
         IF (NLEVIN.GE.NLEVEL) THEN
            INFROM = 0
         ELSE
            IF (NLEVIN.EQ.0) GO TO 100
            INFROM = LINDEX(NLEVIN+1)
         ENDIF
         IF (NLEVIN.NE.NLEVEL) INGOTO = 0
         NLEVEL = NLEVIN
*
         CALL GTMEDI (VECT, NUMED)
         IF (NUMED.NE.0) THEN
            SAFETY = 0.
            GO TO 10
         ENDIF
      ENDIF
*
*     Track outside setup, give control to user (INWVOL=3)
*
  100 INWVOL = 3
      ISTOP  = 1
      ISET   = 0
      IDET   = 0
      NMEC   = 0
      STEP   = 0.
      DESTEL = 0.
      DESTEP = 0.
      NGKINE = 0
      NLCUR  = NLEVEL
      NLEVEL = 1
      CALL GUSTEP
      NLEVEL = NLCUR
*                                                             END GTRACK
  999 END
*CMZ :  1.30/00 25/05/96  05.56.55  by  Pavel Nevski
*CMZ :  1.00/00 20/11/95  03.51.01  by  Pavel Nevski
*-- Author :
      SUBROUTINE GXDZ
C.
C.    ******************************************************************
C.    *                                                                *
C.    *      DZEBRA control commands                                   *
C.    *                                                                *
C.    *       Authors:   R.Brun      **********                        *
C.    *                  P.Zanarini  **********                        *
C.    *                                                                *
C.    * Modifications:                                                 *
C.    *  PN, 20.11.95: change unit 10 to 61 due to SGI problems        *
C.    *  PN, 25.05.96: reaccess link in DISP command after RZ access   *
C.    *  PN, 25.05.96: default documentation file detm.rz introduced   *
C.    ******************************************************************
C.
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
*KEEP,GCXLUN.
      COMMON/GCXLUN/LUNIT(128)
*
*KEND.
      COMMON/GCLTMP/LTEMPA(3)
      COMMON/QUEST/IQUEST(100)
      CHARACTER*20  CHOPT
      CHARACTER*4   BNAME
      CHARACTER*32  CHPATL
      CHARACTER*255 DOCFIL
      CHARACTER*10  CHTOP
      CHARACTER*12  CHTDIR
      CHARACTER*12  CDEF/'detm.rz'/
      LOGICAL       EXST
C.
C.    ------------------------------------------------------------------
C.
      CALL KUPATL(CHPATL,NPAR)
      INQUIRE  (FILE='detm.rz',EXIST=EXST)
*
      IF(CHPATL.EQ.'SHOW')THEN
         CALL KUGETC(BNAME,NCH)
         CALL KUGETI(NUMBER)
         CALL KUGETC(CHOPT,NCH)
         LOC=LZLOC(IXSTOR,BNAME,NUMBER)
         IF(LOC.NE.0)THEN
            CALL DZSHOW('DZSHOW',IXSTOR,LOC,CHOPT,0,0,0,0)
         ENDIF
*
      ELSEIF(CHPATL.EQ.'SURV')THEN
         CALL KUGETC(BNAME,NCH)
         CALL KUGETI(NUMBER)
         LOC=LZLOC(IXSTOR,BNAME,NUMBER)
         IF(LOC.NE.0)THEN
            CALL DZSURV('DZSURV',IXSTOR,LOC)
         ENDIF
*
      ELSEIF(CHPATL.EQ.'SNAP')THEN
         CALL KUGETI(IDIV)
         CALL KUGETC(CHOPT,NCH)
         CALL DZSNAP('DZSNAP',IDIV,CHOPT)
*
      ELSEIF(CHPATL.EQ.'VERIFY')THEN
         CALL KUGETI(IDIV)
         CALL KUGETC(CHOPT,NCH)
         CALL DZVERI('DZVERI',IDIV,CHOPT)
*
      ELSEIF(CHPATL.EQ.'STORE')THEN
         CALL KUGETI(IXSTOR)
         CALL DZSTOR('DZSTOR',IXSTOR)
*
      ELSEIF (CHPATL.EQ.'DDIV') THEN
         CALL KUGETI(IDIV)
         DOCFIL=' '
         CALL KUGETC(DOCFIL,NCH)
         NCH=MAX(NCH,1)
         CALL CUTOL(DOCFIL(1:NCH))
         If (NCH.le.1 .and. EXST) Then
            DOCFIL=CDEF
            NCH=LENOCC(CDEF)
         EndIf
         CHOPT='IN'
         IWDISP=1
         IWMETA=0
         ILOCNR=1
         CHTOP =' '
         CHTDIR=' '
         IF(DOCFIL.NE.' ') THEN
            CALL GXLUNF(61, 3, IFREE)
            IF(IFREE.NE.0) THEN
               LRECL = 256
               CALL RZOPEN(IFREE,CHTOP,DOCFIL(1:NCH),'W',LRECL,ISTAT)
               IF(ISTAT.NE.0) GOTO 999
               CALL RZFILE(IFREE,CHTOP,' ')
               LUNIT(IFREE) = 3
               CHTDIR='//'//CHTOP
            ENDIF
         ENDIF
*
*        Workstation ID is 1 for GEANT
*
         IWTYPE=IGIWTY(1)
         CALL DZDDIV(IDIV,LMAIN,CHTDIR,CHOPT,IWDISP,
     +               IWMETA,ILOCNR,IWTYPE)
         IF(DOCFIL.NE.' ') THEN
            CALL RZEND(CHTOP)
            CLOSE(IFREE)
            LUNIT(IFREE)=0
         ENDIF
      ELSEIF (CHPATL.EQ.'DISP') THEN
         CALL KUGETC(BNAME,NCH)
         DOCFIL=' '
         CALL KUGETC(DOCFIL,NCH)
         NCH=MAX(NCH,1)
         CALL CUTOL(DOCFIL(1:NCH))
         If (NCH.le.1 .and. EXST) Then
            DOCFIL=CDEF
            NCH=LENOCC(CDEF)
         EndIf
         CALL KUGETI(NUMBER)
         CHOPT='N'
         IWDISP=1
         IWMETA=0
         ILOCNR=1
         CHTOP =' '
         CHTDIR=' '
         IF (LZLOC(IXSTOR,BNAME,NUMBER).GT.0) THEN
            IF(DOCFIL.NE.' ') THEN
               CALL GXLUNF(61, 3, IFREE)
               IF(IFREE.NE.0) THEN
                  LRECL = 256
                  CALL RZOPEN(IFREE,CHTOP,DOCFIL(1:NCH),
     +                        'W',LRECL,ISTAT)
                  IF(ISTAT.NE.0) GOTO 999
                  CALL RZFILE(IFREE,CHTOP,' ')
                  LUNIT(IFREE) = 3
                  CHTDIR='//'//CHTOP
               ENDIF
            ENDIF
*
*        Workstation ID is 1 for GEANT
*
            IWTYPE=IGIWTY(1)
            LOC=LZLOC(IXSTOR,BNAME,NUMBER)
            CALL DZDISP(IXSTOR,LOC,CHTDIR,CHOPT,IWDISP,
     +                  IWMETA,ILOCNR,IWTYPE)
            IF(DOCFIL.NE.' ') THEN
               CALL RZEND(CHTOP)
               CLOSE(IFREE)
               LUNIT(IFREE)=0
            ENDIF
         ENDIF
      ELSEIF (CHPATL.EQ.'DIRZ') THEN
         DOCFIL=CDEF
         CALL KUGETC(DOCFIL,NCH)
         NCH=MAX(NCH,1)
         CALL CUTOL(DOCFIL(1:NCH))
         If (NCH.le.1 .and. EXST) Then
            DOCFIL=CDEF
            NCH=LENOCC(CDEF)
         EndIf
         CHOPT='N'
         IWDISP=1
         IWMETA=0
         ILOCNR=1
         IDZSTR=0
         CALL MZLINT(IDZSTR,'/GCLTMP/',LTEMPA,LTEMPA(3),LTEMPA)
         CALL DZDIRZ(IDZSTR,LTEMPA(3),1,DOCFIL(1:NCH),CHOPT,
     +               IWDISP,IWMETA,ILOCNR)
         LTEMPA(1)=0
      ENDIF
*
  999 END
*CMZ :  1.40/05 13/02/98  18.13.57  by  Pavel Nevski
*CMZ :  1.30/00 30/04/97  22.41.05  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.24.17  by  S.Giani
*-- Author :
      SUBROUTINE GMEDIA (X, NUMED)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *   Finds in which volume/medium the point X is, and updates the *
C.    *    common /GCVOLU/ and the structure JGPAR accordingly.        *
C.    *                                                                *
C.    *   NUMED returns the tracking medium number, or 0 if point is   *
C.    *         outside the experimental setup.                        *
C.    *                                                                *
C.    *   Called by :  GTREVE, GLTRAC, 'User'                          *
C.    *   Authors   : R.Brun, F.Bruyant, A.McPherson                   *
C.    *               S.Giani.                                         *
C.    *                                                                *
C.    *   Modified by S.Giani (1993) to perform the search according   *
C.    *    to the new 'virtual divisions' algorithm and to build the   *
C.    *    stack of the 'possible overlapping volumes' in the case of  *
C.    *    MANY volumes. Any kind of boolean operation is now possible.*
C.    *    Divisions along arbitrary axis are now possible.            *
C.    *   PN: in MANY volums the search should start from top          *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCVDMA.
      COMMON/GCVDMA/NVMANY,MANYLE(20),MANYNA(20,15),
     +MANYNU(20,15),NFMANY,MYCOUN,IMYSE,RAYTRA,VECCOS(3)
C
      INTEGER NVMANY,MANYLE,MANYNA,MANYNU,
     +        NFMANY,MYCOUN,IMYSE
      REAL RAYTRA,VECCOS
C
*KEEP,GCHVIR.
      COMMON/GCHVIR/JVIRT,JVDIV,JCONT2,JCONT
C
      INTEGER JVIRT,JVDIV,JCONT2,JCONT
C
*KEND.
C.
      DIMENSION  X(*)
      REAL       XC(6)
      LOGICAL    BTEST
      CHARACTER  NAME*4
C.
C.    ------------------------------------------------------------------
*
      nvmany=0
      nfmany=0
      new2fl=0
*
      IF (NLEVEL.EQ.0) CALL GMEDIN
*
* SECTION I: The /GCVOLU/ table contains the initial guess for a path
*            in the geometry tree on which X may be found.  Look along this
*            path until X is found inside.  This is the starting position.
*            If this is an ONLY volume with no daughters, we are done;
*            otherwise reset search record variables, proceed to section II.
*
*            The information contained in INFROM has to be invalidated
*            because it has no meaning for the subsequent tracking. INFR
*            is a local variable used to optimise the search in the
*            geometry tree.
*
      INFROM = 0
*
* *** Check if point is in current volume
*
      INFR   = 0
      JVIN   = 0
C
C        PN: in MANY volums the search should start from top
  100 If (NLEVEL.GT.1) then
         If (GONLY(NLEVEL).EQ.0) then
            NLEVEL=NLEVEL-1
            GOTO 100
         endif
      endif
C
C*****  Code Expanded From Routine:  GTRNSF
         IF (GRMAT(10,NLEVEL) .EQ. 0.) THEN
         XC(1) = X(1) - GTRAN(1,NLEVEL)
         XC(2) = X(2) - GTRAN(2,NLEVEL)
         XC(3) = X(3) - GTRAN(3,NLEVEL)
*
      ELSE
         XL1 = X(1) - GTRAN(1,NLEVEL)
         XL2 = X(2) - GTRAN(2,NLEVEL)
         XL3 = X(3) - GTRAN(3,NLEVEL)
         XC(1) = XL1*GRMAT(1,NLEVEL) + XL2*GRMAT(2,NLEVEL) + XL3*GRMAT(3
     +      ,NLEVEL)
         XC(2) = XL1*GRMAT(4,NLEVEL) + XL2*GRMAT(5,NLEVEL) + XL3*GRMAT(6
     +      ,NLEVEL)
         XC(3) = XL1*GRMAT(7,NLEVEL) + XL2*GRMAT(8,NLEVEL) + XL3*GRMAT(9
     +      ,NLEVEL)
 
      ENDIF
      xc(4)=0.
      xc(5)=0.
      xc(6)=0.
C*****  End of Code Expanded From Routine:  GTRNSF
*
      JVO  = LQ(JVOLUM-LVOLUM(NLEVEL))
      JPAR = LQ(JGPAR-NLEVEL)
      CALL GINME (XC, Q(JVO+2), Q(JPAR+1), IYES)
      IF (IYES.EQ.0) THEN
*
*  **   Point not in current volume, go up the tree
*
         IF (NLEVEL.GT.1) THEN
            NLEVEL = NLEVEL -1
            JVO  = LQ(JVOLUM-LVOLUM(NLEVEL))
            NIN = Q(JVO+3)
            IF(NIN.GT.0) THEN
*
*       Do not set INFR whne going up the tree. GMEDIA can be called
*       by the user and it  should not assume  that the previous
*       position has something to do with the current search. INFR
*       is otherwise useful when searching in a 'MANY' volume
*       configuration. This statement is commented for the above reason.
*
*              INFR  =LINDEX(NLEVEL+1)
            ELSE
               INFR  =0
            ENDIF
            GO TO 100
         ELSE
*
*   *      Point is outside setup
*
            NUMED = 0
            GO TO 999
         ENDIF
      ENDIF
*
*  **   Point is in current volume
*
      IF(INFR  .GT.0) THEN
         JIN=LQ(JVO-INFR  )
         IQ(JIN) = IBSET(IQ(JIN),4)
         JVIN = JIN
      ENDIF
      NLMIN = NLEVEL
      NLMANY = 0
*
* SECTION II: X is found inside current node at NLEVEL in /GCVOLU/.
*             Search all contents recursively for any containing X.
*             Take the first one found, if any, and continue at that
*             level, incrementing NLEVEL and extending /GCVOLU/ tables.
*             This is continued until a level is reached where X is not
*             found in any of the contents, or there are no contents.
* Note: Since Section II is re-entered from Section III, a blocking word
* is used to mark those contents already checked.  Upon exit from Section
* II, these blocking words are cleared at NLEVEL, but may remain set in
* levels between NLEVEL-1 and NLMIN, if any.  They must be cleared at exit.
*
*  **  Check contents, if any
*
  200 JVO = LQ(JVOLUM-LVOLUM(NLEVEL))
      NIN = Q(JVO+3)
      if(raytra.eq.1..and.imyse.eq.1)then
            CALL UHTOC(NAMES(NLEVEL),4,NAME,4)
            CALL GFIND(NAME,'SEEN',ISSEEN)
            if(isseen.eq.-2.or.isseen.eq.-1)goto 300
      endif
*
*   *   Case with no contents
*
      IF (NIN.EQ.0) THEN
         GO TO 300
*
*   *   Case with contents defined by division
*
      ELSEIF (NIN.LT.0) THEN
         CALL GMEDIV (JVO, IN, XC, 1)
         IF (IN.GT.0) THEN
            INFR   = 0
            GO TO 200
         ENDIF
*
*   *  Case with contents positioned
*
      ELSE
       if(nin.gt.1)then
        clmoth=q(jvirt+4*(LVOLUM(NLEVEL)-1)+3)
        chmoth=q(jvirt+4*(LVOLUM(NLEVEL)-1)+4)
        ndivto=q(jvirt+4*(LVOLUM(NLEVEL)-1)+2)
        iaxis =q(jvirt+4*(LVOLUM(NLEVEL)-1)+1)
        if(iaxis.le.3)then
          ivdiv=((xc(iaxis)-clmoth)*ndivto/(chmoth-clmoth))+1
            if(ivdiv.lt.1)then
              ivdiv=1
            elseif(ivdiv.gt.ndivto)then
              ivdiv=ndivto
            endif
        else
          call gfcoor(xc,iaxis,cx)
          if(iaxis.eq.6)then
            if((cx-clmoth).lt.-1.)then
              cx=cx+360.
            elseif((cx-chmoth).gt.1.)then
              cx=cx-360.
            endif
            if(cx.gt.chmoth)then
              cx=chmoth
            elseif(cx.lt.clmoth)then
              cx=clmoth
            endif
          endif
          ivdiv=((cx-clmoth)*ndivto/(chmoth-clmoth))+1
            if(ivdiv.lt.1)then
              ivdiv=1
            elseif(ivdiv.gt.ndivto)then
              ivdiv=ndivto
            endif
        endif
        jvdiv=lq(jvirt-LVOLUM(NLEVEL))
        iofset=iq(jvdiv+ivdiv)
        ncont=iq(jvdiv+iofset+1)
        jcont=jvdiv+iofset+1
        if(ncont.eq.0)goto 260
       else
         JCONT  = LQ(JVO-NIN-1)+1
         NCONT  = 1
       endif
*
*     For each selected content in turn, check if point is inside
*
         DO 259 ICONT=1,NCONT
           if(nin.eq.1)then
            in=1
           else
            IN = IQ(JCONT+ICONT)
           endif
            IF(IN.EQ.0) THEN
*
*     If the value IQ(JCONT+ICONT)=0 then we are back in the mother.
*     So jump to 260, the search is finished. Clean-up should be done
*     only up to ICONT-1, so we set:
*
               NCONT=ICONT-1
               GOTO 260
            ELSE
            JIN = LQ(JVO-IN)
            IF (.NOT.BTEST(IQ(JIN),4)) THEN
               CALL GMEPOS (JVO, IN, XC, 1)
               IF (IN.GT.0) THEN
                  new2fl=0
                  IF (GONLY(NLEVEL).NE.0.) THEN
                    NLMANY = 0
                    nvmany = 0
                    nfmany = 0
                  ENDIF
                  INFR   = 0
                  GO TO 200
               ELSE
                  IQ(JIN) = IBSET(IQ(JIN),4)
               ENDIF
            ENDIF
            ENDIF
  259    CONTINUE
*
  260    IF(NCONT.EQ.NIN) THEN
         DO 268 IN=1,NIN
            JIN = LQ(JVO-IN)
            IQ(JIN) = IBCLR(IQ(JIN),4)
  268    CONTINUE
         ELSE
         DO 269 ICONT=1,NCONT
           if(nin.eq.1)then
            in=1
           else
            IN  = IQ(JCONT+ICONT)
           endif
            JIN = LQ(JVO-IN)
            IQ(JIN) = IBCLR(IQ(JIN),4)
  269    CONTINUE
         IF(INFR  .GT.0) THEN
            JIN = LQ(JVO-INFR  )
            IQ(JIN) = IBCLR(IQ(JIN),4)
         ENDIF
         ENDIF
*
      ENDIF
*
* SECTION III: X is found at current node (NLEVEL in /GCVOLU) but not in
*              any of its contents, if any.  If this is a MANY volume,
*              save it as a candidate best-choice, and continue the search
*              by backing up the tree one node and proceed to Section II.
*              If this is an ONLY volume, proceed to Section IV.
*
* *** Point is in current volume/medium, and not in any content
*
  300 IF (GONLY(NLEVEL).EQ.0.) THEN
*
*  **   Lowest level is 'NOT ONLY'
*
         IF (NLEVEL.GT.NLMANY) THEN
            CALL GSCVOL
            NLMANY = NLEVEL
            nfmany=nvmany+1
         ENDIF
         if(new2fl.eq.0)then
            nvmany=nvmany+1
            manyle(nvmany)=nlevel
            do 401 i = 1,nlevel
              manyna(nvmany,i)=names(i)
              manynu(nvmany,i)=number(i)
 401        continue
         endif
*
*   *   Go up the tree up to a volume with positioned contents
*
         new2fl=-1
  310    INFR   = LINDEX(NLEVEL)
         NLEVEL = NLEVEL -1
         JVO    = LQ(JVOLUM-LVOLUM(NLEVEL))
         NIN    = Q(JVO+3)
         IF (NIN.LT.0) GO TO 310
*
C*****  Code Expanded From Routine:  GTRNSF
C
         IF (GRMAT(10,NLEVEL) .EQ. 0.) THEN
            XC(1) = X(1) - GTRAN(1,NLEVEL)
            XC(2) = X(2) - GTRAN(2,NLEVEL)
            XC(3) = X(3) - GTRAN(3,NLEVEL)
*
         ELSE
            XL1 = X(1) - GTRAN(1,NLEVEL)
            XL2 = X(2) - GTRAN(2,NLEVEL)
            XL3 = X(3) - GTRAN(3,NLEVEL)
            XC(1) = XL1*GRMAT(1,NLEVEL) + XL2*GRMAT(2,NLEVEL) + XL3*
     +      GRMAT(3,NLEVEL)
            XC(2) = XL1*GRMAT(4,NLEVEL) + XL2*GRMAT(5,NLEVEL) + XL3*
     +      GRMAT(6,NLEVEL)
            XC(3) = XL1*GRMAT(7,NLEVEL) + XL2*GRMAT(8,NLEVEL) + XL3*
     +      GRMAT(9,NLEVEL)
 
         ENDIF
C*****  End of Code Expanded From Routine:  GTRNSF
*
         JIN = LQ(JVO-INFR  )
         IQ(JIN) = IBSET(IQ(JIN),4)
         NLMIN = MIN(NLEVEL,NLMIN)
         GO TO 200
      ENDIF
*
* SECTION IV: This is the end of the search.  The current node (NLEVEL
*             in /GCVOLU/) is the lowest ONLY volume in which X is found.
*             If X was also found in any of its contents, they are MANY
*             volumes: the best-choice is the one among them at the greatest
*             level in the tree, and it is stored.  Otherwise the current
*             volume is the solution.  Before exit, all of the blocking
*             words leftover in the tree must be reset to zero.
* Note: A valid structure is assumed, in which no ONLY volumes overlap.
* If this rule is violated, or if a daughter is not entirely contained
* within the mother volume, the results are unpredictable.
*
      DO 419 NL=NLMIN,NLEVEL-1
         JVO = LQ(JVOLUM-LVOLUM(NL))
         NIN = Q(JVO+3)
         DO 418 IN=1,NIN
            JIN = LQ(JVO-IN)
            IQ(JIN) = IBCLR(IQ(JIN),4)
  418    CONTINUE
  419 CONTINUE
*
      if(nlmany.eq.0)then
        nvmany=0
        nfmany=0
      endif
      IF (NLMANY.GT.0) CALL GFCVOL
      JVO = LQ(JVOLUM-LVOLUM(NLEVEL))
      IF(JVIN.NE.0) IQ(JVIN) = IBCLR(IQ(JVIN),4)
      NUMED = Q(JVO+4)
*                                                             END GMEDIA
  999 IF(JGSTAT.NE.0) CALL GFSTAT(2)
      END
*CMZ :          07/09/98  17.24.08  by  Pavel Nevski
*CMZ :  1.30/00 24/05/96  21.28.46  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.20  by  S.Giani
*-- Author :
      SUBROUTINE GSDETV (IUSET, IUDET, IDTYPE, NWHI, NWDI, ISET, IDET)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Defines detector IUDET as a member of set IUSET          *
C.    *     and prepares the DETector structure                        *
C.    *                                                                *
C.    *             Input parameters                                   *
C.    * IUSET     set identifier (4 characters), user defined          *
C.    * IUDET     detector identifier  (4 characters),   name of  an   *
C.    *           existing volume                                      *
C.    * IDTYPE    detector type, user defined                          *
C.    * NWHI      number of words for primary allocation of HITS banks *
C.    * NWDI      number of words for primary allocation of DIGI banks *
C.    *                                                                *
C.    *             Output parameters                                  *
C.    * ISET      position of set in bank JSET                         *
C.    * IDET      position of detector in bank JS=IB(JSET-ISET)        *
C.    *              If ISET=0 or IDET=0  error                        *
C.    * Remarks:                                                       *
C.    * - The path through the volume tree will be automatically set   *
C.    *   in GGDETV,called by GGCLOS, after all volumes have been      *
C.    *   positionned.                                                 *
C.    * - The detector type  IDTYPE is not used  internally by GEANT   *
C.    *   and  can be  defined by  the user  to distinguish  quickly   *
C.    *   between various kinds of detectors,  in the routine GUSTEP   *
C.    *   for example.                                                 *
C.    *                                                                *
C.    *       IQ(JSET+ISET) = IUSET                                    *
C.    *       JS = LQ(JSET-ISET) = pointer to set IUSET                *
C.    *       IQ(JS+IDET)=IUDET                                        *
C.    *       JD= LQ(JS-1)  = pointer to detector IUDET                *
C.    *       IQ(JD+1)=Number of words to store packed volume numbers  *
C.    *       IQ(JD+2)=Number of volume descriptors                    *
C.    *       IQ(JD+3)=Number of words per hit                         *
C.    *       IQ(JD+4)=Number of elements per hit                      *
C.    *       IQ(JD+5)=Number of words per digitisation                *
C.    *       IQ(JD+6)=Number of elements per digitisation             *
C.    *       IQ(JD+7)=NWHI, primary size of hit bank                  *
C.    *       IQ(JD+8)=NWDI, primary size of digitisation bank         *
C.    *       IQ(JD+9)=Number of paths through the JVOLUM tree         *
C.    *       IQ(JD+10)=For aliases only, IDET of mother detector      *
C.    *       IQ(JD+11)=Name of first volume descriptor                *
C.    *       IQ(JD+12)=Number of bits for packing its number          *
C.    *       ...                                                      *
C.    *       IQ(JD+9+2*NV)=Name of last volume descriptor             *
C.    *       IQ(JD+10+2*NV)=Number of bits for packing its number     *
C.    *       then for each possible path                              *
C.    *       list of names and numbers for all levels                 *
C.    *       (The number of levels is entered as number attached to   *
C.    *       the first name which is the top of the JVOLUM tree)      *
C.    *                                                                *
C.    *            The Detector Set data structure JSET                *
C.    *            ------------------------------------                *
C.    *                                                                *
C.    *                                        | JSET                  *
C.    *    NSET            ISET                v         NSET          *
C.    *     ................................................           *
C.    *     |              | |               |  | Set names|           *
C.    *     ................................................           *
C.    *                     | JS                                       *
C.    *                     |                                          *
C.    *    NDET       IDET  v                    NDET                  *
C.    *     ........................................                   *
C.    *     |        |  |  | | Detector names      |                   *
C.    *     ........................................                   *
C.    *                  | JD                                          *
C.    *       -3  -2  -1 v                                             *
C.    *     ................................................           *
C.    *     |   |   |   |  | Volume parameters, in GGDETV  |           *
C.    *     ................................................           *
C.    *              JDH                                               *
C.    *          JDD                                                   *
C.    *      JDU                                                       *
C.    *                                                                *
C.    * The JSET structure is filled by GSDETV + GGDETV, and by        *
C.    *      GSDETH, GSDETD and GSDETU, eventually by GSDETA.          *
C.    *                                                                *
C.    *    ==>Called by : <USER>, UGEOM                                *
C.    *       Authors   R.Brun, F.Bruyant    **********                *
C.    *                                                                *
C.    * Modifications:                                                 *
C.    *  PN, 20.04.96:  warning on non-sensetive volume in DEBUG only  *
C.    *  PN, 07.09.98:  make it re-entrant and overwrite old banks     *
C.    ******************************************************************
C.
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
*KEEP,GCMZFO.
      COMMON/GCMZFO/IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO(13)
C
      INTEGER       IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO
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
      CHARACTER*4 IUSET,IUDET
C.
C.    ------------------------------------------------------------------
C.
      ISET = 0
      IDET = 0
C
C     Check if volume IUDET has been defined
C
      IF (JVOLUM.LE.0) GO TO 920
      NVOLUM = IQ(JVOLUM-1)
      CALL GLOOK (IUDET, IQ(JVOLUM+1), NVOLUM, IVOL)
      IF (IVOL.EQ.0) GO TO 920
C
C     Check that volume IVOL is a sensitive medium
C
      JVO = LQ(JVOLUM-IVOL)
      ITM = Q(JVO+4)
      JTM = LQ(JTMED-ITM)
      IF (Q(JTM+7).EQ.0. .AND. IDEBUG.GT.0) THEN
         WRITE (CHMAIL,1000) IUDET
         CALL GMAIL(0,0)
      ENDIF
C
      IF (JSET.EQ.0)THEN
C
C     Create mother JSET bank
C
         CALL MZBOOK (IXCONS, JSET, JSET, 1, 'SETS', 0,0,0, 5, 0)
         IQ(JSET-5)=0
      ENDIF
C
      ISET = 0
      NSET = IQ(JSET-1)
      CALL GLOOK (IUSET, IQ(JSET+1), NSET, ISET)
C
C     Create JSET bank
C
      IF (ISET.EQ.0) THEN
         CALL MZPUSH (IXCONS, JSET, 1, 1, 'I')
         NSET = NSET +1
         ISET = NSET
      ENDIF
C
      CALL UCTOH  (IUSET, IQ(JSET+ISET), 4, 4)
      IF (LQ(JSET-ISET).LE.0)
     >  CALL MZBOOK (IXCONS, JS, JSET, -ISET, 'SETS', 0,0,0, 5, 0)
      IQ(JS-5) = ISET
C
C     Check if detector has already been defined
C
  30  JS = LQ(JSET-ISET)
      IDET = 0
      NDET = IQ(JS-1)
      IF (NDET.NE.0) CALL GLOOK (IUDET, IQ(JS+1), NDET, IDET)
C
C     If not, create detector bank
C
      IF (IDET.EQ.0) THEN
         CALL MZPUSH (IXCONS, JS, 1, 1, 'I')
         NDET = NDET +1
         IDET = NDET
      ENDIF
 
      CALL UCTOH (IUDET, IQ(JS+IDET), 4, 4)
      IF (LQ(JS-IDET).LE.0)
     >  CALL MZBOOK (IXCONS, JD, JS, -IDET, 'SEJD', 4,4,100, IOSEJD, 0)
      IQ(JD-5) = IDET
C
      IQ(JD+7) = NWHI
      IQ(JD+8) = NWDI
      IQ(JD+9) = -1
C
C     Now enter Set/Det into JVOLUM data structure
C
      CALL GSATT (IUDET, 'SET ', ISET)
      CALL GSATT (IUDET, 'DET ', IDET)
      CALL GSATT (IUDET, 'DTYP', IDTYPE)
      GO TO 999
C
C     Errors
C
  920 WRITE (CHMAIL,2000) IUDET
      CALL GMAIL(0,0)
      GO TO 999
C
  930 WRITE (CHMAIL,3000)  IUSET, IUDET
      CALL GMAIL(0,0)
C
 1000 FORMAT (' ***** GSDETV - ISVOL=0 FOR DETECTOR ',A4,' - WARNING!')
 2000 FORMAT (' ***** GSDETV ERROR, VOLUME ',A4,' NOT DEFINED')
 3000 FORMAT (' ***** GSDETV ERROR ,SET ',A4, ' DETECTOR ',A4,
     +        ' ALREADY DEFINED')
C
  999 RETURN
      END
*CMZ :  1.30/00 31/05/96  19.39.03  by  Unknown
*CMZ :  3.21/02 29/03/94  15.41.33  by  S.Giani
*-- Author :
      SUBROUTINE GXPICK
C.
C.    ******************************************************************
C.    *                                                                *
C.    *      Geometry commands                                         *
C.    *                                                                *
C.    * Point to volume just drawn to pick up medium name, volume name *
C.    * etc. The first point points to the volume, the second point    *
C.    * gives the position of the character string which contains this *
C.    * information.                                                   *
C.    *                                                                *
C.    *       Authors:   S.Egli      **********                        *
C.    *                                                                *
C.    ******************************************************************
C.
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEEP,GCDRAW.
      COMMON/GCDRAW/NUMNOD,MAXNOD,NUMND1,LEVVER,LEVHOR,MAXV,IPICK,
     + MLEVV,MLEVH,NWCUT,JNAM,JMOT,JXON,JBRO,JDUP,JSCA,JDVM,JPSM,
     + JNAM1,JMOT1,JXON1,JBRO1,JDUP1,JSCA1,JULEV,JVLEV,
     + LOOKTB(16),
     + GRMAT0(10),GTRAN0(3),IDRNUM,GSIN(41),GCOS(41),SINPSI,COSPSI,
     + GTHETA,GPHI,GPSI,GU0,GV0,GSCU,GSCV,NGVIEW,
     + ICUTFL,ICUT,CTHETA,CPHI,DCUT,NSURF,ISURF,
     + GZUA,GZVA,GZUB,GZVB,GZUC,GZVC,PLTRNX,PLTRNY,
     + LINATT,LINATP,ITXATT,ITHRZ,IPRJ,DPERS,ITR3D,IPKHIT,IOBJ,LINBUF,
     + MAXGU,MORGU,MAXGS,MORGS,MAXTU,MORTU,MAXTS,MORTS,
     + IGU,IGS,ITU,ITS,NKVIEW,IDVIEW,
     + NOPEN,IGMR,IPIONS,ITRKOP,IHIDEN,
     + ZZFU,ZZFV,MYISEL,
     + DDUMMY(15)
C
      INTEGER NUMNOD,MAXNOD,NUMND1,LEVVER,LEVHOR,MAXV,IPICK,
     + MLEVV,MLEVH,NWCUT,JNAM,JMOT,JXON,JBRO,JDUP,JSCA,JDVM,JPSM,
     + JNAM1,JMOT1,JXON1,JBRO1,JDUP1,JSCA1,JULEV,JVLEV,
     + LOOKTB,IDRNUM,NGVIEW,ICUTFL,ICUT,NSURF,ISURF,LINATT,LINATP,
     + ITXATT,ITHRZ,IPRJ,ITR3D,IPKHIT,IOBJ,LINBUF,
     + MAXGU,MORGU,MAXGS,MORGS,MAXTU,MORTU,MAXTS,MORTS,
     + IGU,IGS,ITU,ITS,NKVIEW,IDVIEW,
     + NOPEN,IGMR,IPIONS,ITRKOP,IHIDEN
      REAL GRMAT0,GTRAN0,GSIN,GCOS,SINPSI,COSPSI,GTHETA,GPHI,GPSI,
     + GU0,GV0,GSCU,GSCV,CTHETA,CPHI,DCUT,GZUA,GZVA,GZUB,GZVB,GZUC,
     + GZVC,PLTRNX,PLTRNY,DPERS,DDUMMY
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
*KEEP,GCSETS.
      COMMON/GCSETS/IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV(20)
C
      INTEGER       IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV
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
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*
* this COMMON filled in routine GDRAW !
*
      COMMON/GCVHLP/NVLAST
*
      DIMENSION XC(3),XYZ(3),XINVMA(3,3),VL(3),VM(3),VN(3)
      DIMENSION XX(10),YY(10),RHELP(3)
*
      CHARACTER*4 NAMV,CHIDTY
      CHARACTER*20 NAMM
      LOGICAL BTEST
*
* determine inverse matrix xinvma for current view parameters
*
      PH = ABS(MOD(GPHI,360.))
      THET = ABS(MOD(GTHETA,360.))
      IF(THET.LE.180.)GO TO 10
      PH = PH + 180.
      THET = 360. - THET
*
   10 ST = SIN(THET * DEGRAD)
      CT = COS(THET * DEGRAD)
      SP = SIN(PH * DEGRAD)
      CP = COS(PH * DEGRAD)
*
*             VN is new nu axis
*
      VN(1) = ST * CP
      VN(2) = ST * SP
      VN(3) = CT
*
      IF(ABS(VN(2)).GT.0.99999) THEN
*
*             Special case when observer line of sight is along mu:
*             in this case one chooses arbitrarily the vertical axis of
*             plane of projection as the lambda axis and the horizontal
*             as the nu axis
*
         VL(1) = 0.
         VL(2) = 0.
         VL(3) = 1.
         VM(1) = 1.
         VM(2) = 0.
         VM(3) = 0.
      ELSE
*
         VM(1) = 0.
         VM(2) = 1.
         VM(3) = 0.
*
*             Define new lambda axis
*
         CALL CROSS(VM,VN,VL)
         CALL VUNIT(VL,VL,3)
*
*             Define new mu axis
*
         CALL CROSS(VN,VL,VM)
      ENDIF
*
*   now invert matrix defined by VL,VM,VN -> XINVMA
*
      DO 20 I=1,3
         XINVMA(1,I)=VL(I)
         XINVMA(2,I)=VM(I)
         XINVMA(3,I)=VN(I)
   20 CONTINUE
*
      CALL RINV(3,XINVMA,3,RHELP,IFAIL)
      IF(IFAIL.NE.0)THEN
         WRITE(CHMAIL,10100) IFAIL
         CALL GMAIL(0,0)
         GOTO 999
      ENDIF
*
*   perspective projection ?
*
      CALL UCTOH('PERS',IPERS,4,4)
      IF(IPRJ.EQ.IPERS)THEN
         WRITE(CHMAIL,10200)
         CALL GMAIL(0,0)
         GOTO 999
      ENDIF
*
* pick up two points in user coordinates:
*
   30 CALL IRQLC(1,1,ISTAT,NT,U0,V0)
      IF(ISTAT.EQ.0)GOTO 999
      CALL IRQLC(1,1,ISTAT,NT,U1,V1)
      IF(ISTAT.EQ.0)GOTO 999
*
* transform (u0,v0) to coordinates in MARS system:
*  (inverse operation of what is done in routine GDFR3D)
*
*   take zoom parameters into account:
*
      U01=(U0-GZUB-GZUC)/GZUA
      V01=(V0-GZVB-GZVC)/GZVA
*
*   rotate and shift back
*
      UU=+COSPSI*(U01-GU0)+SINPSI*(V01-GV0)
      VV=-SINPSI*(U01-GU0)+COSPSI*(V01-GV0)
      XYZ(1)=UU/GSCU
      XYZ(2)=VV/GSCV
      XYZ(3)=DCUT
*
*   apply xinvma
*
      XC(1)=XINVMA(1,1)*XYZ(1)+XINVMA(1,2)*XYZ(2)+XINVMA(1,3)*XYZ(3)
      XC(2)=XINVMA(2,1)*XYZ(1)+XINVMA(2,2)*XYZ(2)+XINVMA(2,3)*XYZ(3)
      XC(3)=XINVMA(3,1)*XYZ(1)+XINVMA(3,2)*XYZ(2)+XINVMA(3,3)*XYZ(3)
*
*   build up GCVOLU structure with last drawn volume as
*   top of tree
*
      NLEV=1
      LNUM=0
      CALL GLVOLU(NLEV,NVLAST,LNUM,IER)
*
*  determine medium
*
      NUMED=0
      CALL GMEDIA(XC,NUMED)
*
      IF(NUMED.EQ.0)THEN
         WRITE(CHMAIL,10300)
         CALL GMAIL(0,0)
         GOTO 30
      ENDIF
      JTM = LQ(JTMED- NUMED)
      DO 40 I=1,5
   40 NATMED(I)=IQ(JTM+I)
      NMAT   = Q(JTM + 6)
      ISVOL  = Q(JTM + 7)
      IFIELD = Q(JTM + 8)
      FIELDM = Q(JTM + 9)
      TMAXFD = Q(JTM + 10)
      STEMAX = Q(JTM + 11)
      DEEMAX = Q(JTM + 12)
      EPSIL  = Q(JTM + 13)
      STMIN  = Q(JTM + 14)
      CALL UHTOC(NAMES(NLEVEL),4,NAMV,4)
      CALL UHTOC(NATMED,4,NAMM,20)
      DO 50 I=1,20
         IF(NAMM(I:I).EQ.'$')NAMM(I:I)=' '
   50 CONTINUE
      DO 60 I=20,1,-1
         IF(NAMM(I:I).NE.' ')GOTO 70
   60 CONTINUE
   70 NJLAST=I
*
*  determine detector idtype
*
      IF(JSET.GT.0)CALL GFINDS
*
* draw pointer and write volume name,medium
*
      XX(1)=U0
      YY(1)=V0
      XX(2)=U1
      YY(2)=V1
      CALL IPL(2,XX,YY)
*
*  determine text alignment
*
*     protect against double click:
      If (abs(V1-V0)+abs(U1-U0).GT.0) PHI=ATAN2(V1-V0,U1-U0)*RADDEG
      IF(ABS(PHI).LT.90.)THEN
         IHOR=1
      ELSE
         IHOR=3
      ENDIF
      IF(PHI.GT.0.)THEN
         IVER=5
      ELSE
         IVER=1
      ENDIF
      CALL ISTXAL(IHOR,IVER)
*
      IF(.NOT.BTEST(IQ(LQ(JVOLUM-LVOLUM(1))),4))THEN
         CALL ITX(U1,V1,NAMV//'"j# '//NAMM(1:NJLAST))
      ELSE
         WRITE(CHIDTY,10000)IDTYPE
         CALL ITX(U1,V1,NAMV//'"j# '//NAMM(1:NJLAST)//','//CHIDTY)
      ENDIF
      GOTO 30
10000 FORMAT(I4)
10100 FORMAT(' GXPICK: Matrix inversion failed with ',I3,
     +       '; abandoning')
10200 FORMAT(' GXPICK: perspective projection can not be handled')
10300 FORMAT(' GXPICK: point is outside volume')
  999 END
 
*CMZ :  1.40/05 14/07/98  12.44.58  by  Pavel Nevski
*CMZ :  1.30/00 16/04/97  20.12.19  by  Pavel Nevski
*CMZ :  3.21/02 07/07/94  19.47.38  by  S.Giani
*-- Author :
      SUBROUTINE GXCONT
**
**    ******************************************************************
**    *                                                                *
**    *      General control commands                                  *
**    *                                                                *
**    *       Authors:   R.Brun      **********                        *
**    *                  P.Zanarini  **********                        *
**    *                  S.Giani     **********                        *
**    *                                                                *
**    * Modifications:                                 PN, 06 July 96  *
**    *  - strong typing introduced to find undefined variables        *
**    *  - GCTIME common was missing                                   *
**    *  - SPART command corrected ( a la NA49 and Star): Ubuf,        *
**    *    branching ratios and decay modes are KUIP vectors!          *
**    *  - RNDM command with single parameter ISEQ (1-215) recals      *
**    *    standard precomputed sequences.                             *
**    *    If ISEQ=0, sequence is elected according to IGTIME.         *
**    *  - Time control introduced - upon the limit IQUEST(1) is set   *
**    ******************************************************************
**
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEEP,PAWC.
      INTEGER NWPAW,IXPAWC,IHBOOK,IXHIGZ,IXKUIP,IFENCE,LLMAIN,IQQ,LQQ
      REAL WWS,QQ
      COMMON /PAWC/ NWPAW,IXPAWC,IHBOOK,IXHIGZ,IXKUIP,IFENCE(5),
     +              LLMAIN, WWS(9989)
      DIMENSION IQQ(2),QQ(2),LQQ(8000)
      EQUIVALENCE (QQ(1),IQQ(1),LQQ(9)),(LQQ(1),LLMAIN)
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
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
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
*KEEP,GCMULO.
      COMMON/GCMULO/SINMUL(101),COSMUL(101),SQRMUL(101),OMCMOL,CHCMOL
     +  ,EKMIN,EKMAX,NEKBIN,NEK1,EKINV,GEKA,GEKB,EKBIN(200),ELOW(200)
C
      REAL SINMUL,COSMUL,SQRMUL,OMCMOL,CHCMOL,EKMIN,EKMAX,ELOW,EKINV
      REAL GEKA,GEKB,EKBIN
      INTEGER NEKBIN,NEK1
C
*KEEP,GCLIST.
      COMMON/GCLIST/NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     +       ,NSTAT,LHSTA(20),LGET (20),LSAVE(20),LSETS(20),LPRIN(20)
     +             ,LGEOM(20),LVIEW(20),LPLOT(20),LSTAT(20)
C
      INTEGER       NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     + ,NSTAT,LHSTA,LGET ,LSAVE,LSETS,LPRIN,LGEOM,LVIEW,LPLOT,LSTAT
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
*KEEP,GCDRAW.
      COMMON/GCDRAW/NUMNOD,MAXNOD,NUMND1,LEVVER,LEVHOR,MAXV,IPICK,
     + MLEVV,MLEVH,NWCUT,JNAM,JMOT,JXON,JBRO,JDUP,JSCA,JDVM,JPSM,
     + JNAM1,JMOT1,JXON1,JBRO1,JDUP1,JSCA1,JULEV,JVLEV,
     + LOOKTB(16),
     + GRMAT0(10),GTRAN0(3),IDRNUM,GSIN(41),GCOS(41),SINPSI,COSPSI,
     + GTHETA,GPHI,GPSI,GU0,GV0,GSCU,GSCV,NGVIEW,
     + ICUTFL,ICUT,CTHETA,CPHI,DCUT,NSURF,ISURF,
     + GZUA,GZVA,GZUB,GZVB,GZUC,GZVC,PLTRNX,PLTRNY,
     + LINATT,LINATP,ITXATT,ITHRZ,IPRJ,DPERS,ITR3D,IPKHIT,IOBJ,LINBUF,
     + MAXGU,MORGU,MAXGS,MORGS,MAXTU,MORTU,MAXTS,MORTS,
     + IGU,IGS,ITU,ITS,NKVIEW,IDVIEW,
     + NOPEN,IGMR,IPIONS,ITRKOP,IHIDEN,
     + ZZFU,ZZFV,MYISEL,
     + DDUMMY(15)
C
      INTEGER NUMNOD,MAXNOD,NUMND1,LEVVER,LEVHOR,MAXV,IPICK,
     + MLEVV,MLEVH,NWCUT,JNAM,JMOT,JXON,JBRO,JDUP,JSCA,JDVM,JPSM,
     + JNAM1,JMOT1,JXON1,JBRO1,JDUP1,JSCA1,JULEV,JVLEV,
     + LOOKTB,IDRNUM,NGVIEW,ICUTFL,ICUT,NSURF,ISURF,LINATT,LINATP,
     + ITXATT,ITHRZ,IPRJ,ITR3D,IPKHIT,IOBJ,LINBUF,
     + MAXGU,MORGU,MAXGS,MORGS,MAXTU,MORTU,MAXTS,MORTS,
     + IGU,IGS,ITU,ITS,NKVIEW,IDVIEW,
     + NOPEN,IGMR,IPIONS,ITRKOP,IHIDEN
      REAL GRMAT0,GTRAN0,GSIN,GCOS,SINPSI,COSPSI,GTHETA,GPHI,GPSI,
     + GU0,GV0,GSCU,GSCV,CTHETA,CPHI,DCUT,GZUA,GZVA,GZUB,GZVB,GZUC,
     + GZVC,PLTRNX,PLTRNY,DPERS,DDUMMY
*KEEP,GCTIME.
      COMMON/GCTIME/TIMINT,TIMEND,ITIME,IGDATE,IGTIME
      INTEGER ITIME,IGDATE,IGTIME
      REAL TIMINT,TIMEND
C
*KEND.
*
      Integer      IGIWTY,IwkSty,i,N,Npar,Npk,Nch,Level,Numb,Imat,
     +             NumHit,Llow,Lhigh,Llo1,Lhig1,Llo2,Lhig2,NW,
     +             Idm,Nlmat,Nmec,Kmec,ItMed,Is1,Is2
      Real         A,Z,Dens,RadL,AbsL,ParVal,T,TL
      CHARACTER*20 CHNAME
      CHARACTER*4  CHMECA,CHDEB,CHSET,CHDET,CHMECS(20)
      CHARACTER*32 CHPATL,CHPAR,Cmate,Cpart,Cvec
      External     IGIWTY
* the following is a part of the GCDRAW keeps, forgotten in the official code
      Integer      MyISel
      real         zzfu,zzfv
      Logical      First_QNEXT/.true./
**
**    ------------------------------------------------------------------
**
      IWKSTY = IGIWTY(1)
      CALL KUPATL(CHPATL,NPAR)
*
      IF (CHPATL.EQ.'KINE') THEN
         CALL KUGETI(IKINE)
         NPK=NPAR-1
         DO 10 I=1,NPK
            CALL KUGETR(PKINE(I))
   10    CONTINUE
*
      ELSEIF (CHPATL.EQ.'SORD') THEN
         CALL KUGETI(ISTORD)
*
*     ELSEIF (CHPATL.EQ.'PATR') THEN
*        CALL KUGETI(NJTMAX)
*        CALL KUGETI(NJTMIN)
*        WRITE(CHMAIL,'('' *** GXCONT: Parallel tracking disabled, '',
*    +                  ''see documentation'')')
*        CALL GMAIL(1,1)
*
      ELSEIF (CHPATL.EQ.'RUNG') THEN
         CALL KUGETI(IDRUN)
         CALL KUGETI(IDEVT)
*
      ELSEIF (CHPATL.EQ.'GTIME') THEN
         CALL KUGETR(T)
         CALL KUGETR(TIMEND)
         CALL KUGETI(ITIME)
         if (IDEBUG.GT.0) then
            call TIMEL(TL)
            WRITE(CHMAIL,'('' *** GXCONT: Time left is '',F12.1)') TL
            CALL  GMAIL(0,0)
         endif
*
      ELSEIF (CHPATL.EQ.'TRACK') THEN
         IF(JXYZ.NE.0)CALL MZDROP(IXDIV,JXYZ,' ')
         IF(JHITS.NE.0)CALL MZDROP(IXDIV,JHITS,' ')
         CALL MZGARB(IXDIV,0)
         CALL GTREVE
*
      ELSEIF (CHPATL.EQ.'TRIGGER') THEN
         CALL KUGETI(N)
         NEVENT=IEVENT+N
         If (First_QNEXT) then
             First_QNEXT=.false.
             CALL QNEXTE
         else
             CALL QNEXT
         endif
*
      ELSEIF (CHPATL.EQ.'SWITCH') THEN
         CALL KUGETI(I)
         IF(I.GE.1.AND.I.LE.10) THEN
            IF(NPAR.LT.2)THEN
               WRITE(CHMAIL,'('' ISWIT('',I2,'')= '',I3)')I,ISWIT(I)
               CALL GMAIL(0,0)
            ENDIF
            CALL KUGETI(ISWIT(I))
         ENDIF
*
      ELSEIF (CHPATL.EQ.'PRINT') THEN
         CALL KUGETC(CHNAME,NCH)
         N=0
         CALL KUGETI(N)
         CALL GPRINT(CHNAME,N)
*
      ELSEIF (CHPATL.EQ.'DEBUG') THEN
         CALL KUGETC(CHDEB,NCH)
         IF(CHDEB.EQ.'ON')THEN
            IDEBUG=max(IDEBUG,1)
            IDEMIN=1
            IDEMAX=1000000
            ITEST =1
            ITIME =1
         ELSE
            IDEBUG=0
            IDEMIN=0
            IDEMAX=0
         ENDIF
*
      ELSEIF (CHPATL.EQ.'OUTPUT_LP') THEN
         CALL KUGETI(LOUT)
*
      ELSEIF (CHPATL.EQ.'PHITS') THEN
         CALL KUGETC(CHSET,NCH)
         CALL KUGETC(CHDET,NCH)
         CALL KUGETI(NUMHIT)
         IPKHIT=NUMHIT
         CALL GPHITS(CHSET,CHDET)
         IPKHIT=0
*
      ELSEIF (CHPATL.EQ.'PDIGI') THEN
         CALL KUGETC(CHSET,NCH)
         CALL KUGETC(CHDET,NCH)
         CALL GPDIGI(CHSET,CHDET)
*
      ELSEIF (CHPATL.EQ.'MZLOGL') THEN
         IXSTOR=0
         LEVEL=0
         CALL KUGETI(LEVEL)
         CALL MZLOGL(IXSTOR,LEVEL)
*
      ELSEIF (CHPATL.EQ.'PMATE') THEN
         CALL KUGETI(NUMB)
         IF(IWKSTY.GE.1.AND.IWKSTY.LE.10) THEN
            CALL GPMATX(NUMB)
         ELSE
            CALL GPMATE(NUMB)
         ENDIF
*
      ELSEIF (CHPATL.EQ.'SMATE') THEN
         CALL KUGETI(IMAT)
         CALL KUGETC(Cmate,NCH)
         CALL KUGETR(A)
         CALL KUGETR(Z)
         CALL KUGETR(DENS)
         CALL KUGETR(RADL)
         CALL KUGETR(ABSL)
         CALL KUGETV(Cvec,LLOW,LHIGH)
         CALL KUGETI(NW)
         CALL GSMATE(IMAT,Cmate,A,Z,DENS,RADL,ABSL,QQ(LLOW),NW)
*
      ELSEIF (CHPATL.EQ.'SMIXT') THEN
         CALL KUGETI(IMAT)
         CALL KUGETC(Cmate,NCH)
         CALL KUGETV(Cvec,LLOW,LHIGH)
         CALL KUGETV(Cvec,LLO1,LHIG1)
         CALL KUGETR(DENS)
         CALL KUGETI(NLMAT)
         CALL KUGETV(Cvec,LLO2,LHIG2)
         CALL GSMIXT(IMAT,Cmate,QQ(LLOW),QQ(LLO1),DENS,NLMAT,QQ(LLO2))
*
      ELSEIF (CHPATL.EQ.'PRMAT') THEN
         CALL KUGETI(Imat)
         CALL KUGETI(IPART)
         CALL KUGETC(CHMECA,NCH)
         CALL GPRMAT(Imat,IPART,CHMECA,NEKBIN,ELOW)
*
      ELSEIF (CHPATL.EQ.'DRMAT') THEN
         CALL KUGETI(Imat)
         CALL KUGETI(IPART)
         IF(NPAR.GT.2) THEN
            NMEC = NPAR-2
            DO 11 KMEC=1,NMEC
               CALL KUGETC(CHMECS(KMEC),NCH)
  11        CONTINUE
         ELSE
            NMEC = 1
            CHMECS(1)='ALL'
         ENDIF
         CALL GDRMAT(Imat,IPART,CHMECS,NMEC)
*
      ELSEIF (CHPATL.EQ.'PLMAT') THEN
         CALL KUGETI(Imat)
         CALL KUGETI(IPART)
         CALL KUGETC(CHMECA,NCH)
         IDM=0
         CALL KUGETI(IDM)
         CALL GPLMAT(Imat,IPART,CHMECA,NEKBIN,ELOW,IDM)
*
      ELSEIF (CHPATL.EQ.'SPART') THEN
         CALL KUGETI(IPART)
         CALL KUGETC(Cpart,NCH)
         CALL KUGETI(ITRTYP)
         CALL KUGETR(AMASS)
         CALL KUGETR(CHARGE)
         CALL KUGETR(TLIFE)
         CALL KUGETV(Cvec,LLOW,LHIGH)
         CALL KUGETI(NW)
         CALL GSPART(IPART,Cpart,ITRTYP,AMASS,CHARGE,TLIFE,QQ(LLOW),NW)
         CALL KUGETV(CVEC,LLO1,LHIG1)
         CALL KUGETV(CVEC,LLO2,LHIG2)
         CALL GSDK  (IPART,QQ(LLO1),IQQ(LLO2))
*
      ELSEIF (CHPATL.EQ.'PPART') THEN
         CALL KUGETI(NUMB)
         IF(IWKSTY.GE.1.AND.IWKSTY.LE.10) THEN
            CALL GPPARX(NUMB)
         ELSE
            CALL GPPART(NUMB)
         ENDIF
*
      ELSEIF (CHPATL.EQ.'PRKINE') THEN
         CALL KUGETI(NUMB)
         IF(IWKSTY.GE.1.AND.IWKSTY.LE.10) THEN
            CALL GPKINX(NUMB)
         ELSE
            CALL GPKINE(NUMB)
         ENDIF
*
      ELSEIF (CHPATL.EQ.'STPAR') THEN
         CALL KUGETI(ITMED)
         CALL KUGETC(CHPAR,NCH)
         CALL KUGETR(PARVAL)
         CALL GSTPAR(ITMED,CHPAR,PARVAL)
*
      ELSEIF (CHPATL.EQ.'RNDM') THEN
         IF (NPAR.EQ.0) THEN
            CALL GRNDMQ(IS1,IS2,0,'G')
            WRITE(CHMAIL, 10000) IS1, IS2
10000       FORMAT('  RANDOM NUMBER = ',2I12)
            CALL GMAIL(0,0)
         ELSEIF (NPAR.EQ.1) THEN
            CALL KUGETI(IS1)
            If (IS1.LE.0) IS1=IGTIME
            IS2 = mod(IS1, 215 ) + 1
            CALL GRNDMQ(0, 0, IS2, ' ')
         ELSEIF (NPAR.EQ.2) THEN
            CALL KUGETI(NRNDM(1))
            CALL KUGETI(NRNDM(2))
            If (NRNDM(2).GT.0) THEN
               CALL GRNDMQ(NRNDM(1),NRNDM(2),0,'S')
            else
               IS1 = mod (NRNDM(1),215) + 1
               CALL GRNDMQ( 0, 0, IS1, ' ')
            endif
         ELSE
            WRITE(CHMAIL, 10100)
            CALL GMAIL(0,0)
10100       FORMAT(' Please give up to 2 seeds to initialize',
     +             ' the random number generator')
         ENDIF
         CALL GRNDMQ(NRNDM(1),NRNDM(2),0,'G')
      ENDIF
*
   30 END
 
*CMZ :  1.30/00 06/07/96  18.25.27  by  Pavel Nevski
*CMZ :  3.21/04 09/11/94  15.31.28  by  S.Ravndal
*-- Author :    R.Brun
      SUBROUTINE GXPHYS
**
**    ******************************************************************
**    *                                                                *
**    *      Physics parameters control commands                       *
**    *                                                                *
**    *       Author:    R.Brun      **********                        *
**    *                                                                *
**    * Modifications:                                PN 06 July 96    *
**    * - strong typing introduced to find undefined variables         *
**    * - GCTRAK.IGAUTO was missing                                    *
**    * - ICKOV was never used. GTMED.ITCKOV is read instead           *
**    * - ITCKOV and ILABS correlated as in GFFGO                      *
**    ******************************************************************
**
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
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
*KEEP,GCMULO.
      COMMON/GCMULO/SINMUL(101),COSMUL(101),SQRMUL(101),OMCMOL,CHCMOL
     +  ,EKMIN,EKMAX,NEKBIN,NEK1,EKINV,GEKA,GEKB,EKBIN(200),ELOW(200)
C
      REAL SINMUL,COSMUL,SQRMUL,OMCMOL,CHCMOL,EKMIN,EKMAX,ELOW,EKINV
      REAL GEKA,GEKB,EKBIN
      INTEGER NEKBIN,NEK1
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
*KEND.
*
      Integer       Npar,i,j,Ipart,Imate,Npoint,JTM,JTMi,JM,JMA
      Real          Stepa
      Real          UCUTS(10),ULCUTS(10)
      EQUIVALENCE  (UCUTS(1),CUTGAM)
      Integer       MECA(5,13)
      EQUIVALENCE  (MECA(1,1),IPAIR)
      CHARACTER*6   CUTNAM(10)
      CHARACTER*4   CEN(10)
      CHARACTER*32  CHPATL
      CHARACTER*10  CHNUMB
      PARAMETER    (CHNUMB='1234567890')
      DATA  CUTNAM/'CUTGAM','CUTELE','CUTNEU','CUTHAD','CUTMUO',
     +             'BCUTE' ,'BCUTM' ,'DCUTE' ,'DCUTM' ,'PPCUTM'/
**
**    ------------------------------------------------------------------
**
      CALL KUPATL(CHPATL,NPAR)
*
      IF(CHPATL.EQ.'ANNI')THEN
         CALL KUGETI(IANNI)
*
      ELSEIF(CHPATL.EQ.'AUTO')THEN
         CALL KUGETI(IGAUTO)
*
      ELSEIF(CHPATL.EQ.'BREM')THEN
         CALL KUGETI(IBREM)
*
      ELSEIF(CHPATL.EQ.'CKOV')THEN
         CALL KUGETI(ITCKOV)
*
      ELSEIF(CHPATL.EQ.'COMP')THEN
         CALL KUGETI(ICOMP)
*
      ELSEIF(CHPATL.EQ.'DCAY')THEN
         CALL KUGETI(IDCAY)
*
      ELSEIF(CHPATL.EQ.'DRAY')THEN
         CALL KUGETI(IDRAY)
*
      ELSEIF(CHPATL.EQ.'ERAN')THEN
         CALL KUGETR(EKMIN)
         CALL KUGETR(EKMAX)
         CALL KUGETI(NEKBIN)
         NEKBIN=MIN(NEKBIN,199)
*
      ELSEIF(CHPATL.EQ.'HADR')THEN
         CALL KUGETI(IHADR)
*
      ELSEIF(CHPATL.EQ.'LABS')THEN
         CALL KUGETI(ILABS)
*
      ELSEIF(CHPATL.EQ.'LOSS')THEN
         CALL KUGETI(ILOSS)
         IF(ILOSS.EQ.2)THEN
            IDRAY=0
         ELSE
            IDRAY=1
         ENDIF
*
      ELSEIF(CHPATL.EQ.'MULS')THEN
         CALL KUGETI(IMULS)
*
      ELSEIF(CHPATL.EQ.'MUNU')THEN
         CALL KUGETI(IMUNU)
*
      ELSEIF(CHPATL.EQ.'PAIR')THEN
         CALL KUGETI(IPAIR)
*
      ELSEIF(CHPATL.EQ.'PFIS')THEN
         CALL KUGETI(IPFIS)
*
      ELSEIF(CHPATL.EQ.'PHOT')THEN
         CALL KUGETI(IPHOT)
*
      ELSEIF(CHPATL.EQ.'RAYL')THEN
         CALL KUGETI(IRAYL)
*
      ELSEIF(CHPATL.EQ.'STRA')THEN
         CALL KUGETI(ISTRA)
*
      ELSEIF(CHPATL.EQ.'SYNC')THEN
         CALL KUGETI(ISYNC)
*
      ELSEIF(CHPATL.EQ.'CUTS')THEN
         IF(NPAR.LE.0)THEN
            WRITE(LOUT,10000)
10000       FORMAT(/,' Current PHYSICS parameters:',/)
            DO 10 I=1,10
               CALL GEVKEV(UCUTS(I),ULCUTS(I),CEN(I))
               WRITE(LOUT,10100)CUTNAM(I),ULCUTS(I),CEN(I)
10100          FORMAT(5X,A,' = ',F7.2,1X,A)
   10       CONTINUE
            GO TO 999
         ENDIF
         CALL KUGETR(CUTGAM)
         CALL KUGETR(CUTELE)
         CALL KUGETR(CUTHAD)
         CALL KUGETR(CUTNEU)
         CALL KUGETR(CUTMUO)
         CALL KUGETR(BCUTE)
         CALL KUGETR(BCUTM)
         CALL KUGETR(DCUTE)
         CALL KUGETR(DCUTM)
         CALL KUGETR(PPCUTM)
         CALL KUGETR(TOFMAX)
         CALL KUGETR(GCUTS(1))
         IF(BCUTE.LE.0.)BCUTE=CUTGAM
         IF(BCUTM.LE.0.)BCUTM=CUTGAM
         IF(DCUTE.LE.0.)DCUTE=CUTELE
         IF(DCUTM.LE.0.)DCUTM=CUTELE
         IF(PPCUTM.LT.4.*EMASS)PPCUTM=4.*EMASS
*
      ELSEIF(CHPATL.EQ.'DRPRT')THEN
         CALL KUGETI(IPART)
         CALL KUGETI(IMATE)
         CALL KUGETR(STEPA)
         CALL KUGETI(NPOINT)
         CALL GDRPRT(IPART,IMATE,STEPA,NPOINT)
*
      ELSEIF(CHPATL.EQ.'PHYSI')THEN
         IF(JTMED.GT.0)THEN
            DO 30 I=1,IQ(JTMED-2)
               JTM=LQ(JTMED-I)
               IF(JTM.LE.0)GO TO 30
               IF(IQ(JTM-2).EQ.0)THEN
                  CALL MZPUSH(IXCONS,JTM,10,0,'I')
                  GO TO 30
               ENDIF
               DO 20 J=1,10
                  JTMI=LQ(JTM-J)
                  IF(JTMI.GT.0)THEN
                     CALL MZDROP(IXCONS,JTMI,' ')
                  ENDIF
   20          CONTINUE
   30       CONTINUE
            CALL UCOPY(CUTGAM,Q(JTMED+1),10)
            DO 40 I=1,13
               Q(JTMED+10+I)=MECA(1,I)
   40       CONTINUE
         ENDIF
         IF(JMATE.LE.0)GO TO 999
         DO 60 I=1,IQ(JMATE-2)
            JMA=LQ(JMATE-I)
            IF(JMA.LE.0)GO TO 60
            DO 50 J=1,IQ(JMA-2)
               IF(J.EQ.4.OR.J.EQ.5)GO TO 60
               JM=LQ(JMA-J)
               IF(JM.LE.0)GO TO 50
               CALL MZDROP(IXCONS,JM,'L')
   50       CONTINUE
   60    CONTINUE
         CALL MZGARB (IXCONS, 0)
         CALL GPHYSI
      ENDIF
*
      IF(ILABS.NE.0 .and. ITCKOV.NE.0) ILABS=1
*
  999 END
*CMZ :  1.30/00 30/10/96  18.46.07  by  Pavel Nevski
*-- Author :    L.Urban
      FUNCTION GBRSGE(ZZ,T,BCUT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *  Calculates cross-section in current material                  *
C.    *  for discrete(hard) electron BREMSSTRAHLUNG.                   *
C.    *         (SIG in barn/atom)                                     *
C.    *                                                                *
C.    *    ==>Called by : GBRSGA                                       *
C.    *       Author  L.Urban  *********                               *
C.    *                                                                *
C.    *  correction for T> 100 GeV !  (by L.Urban on 23/09/96)         *
C.    ******************************************************************
C.
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEND.
      DIMENSION C(100),C1(60),C2(40)
      EQUIVALENCE (C(1),C1(1)),(C(61),C2(1))
      SAVE C
      PARAMETER (AKSI=1.80,ALFA=0.98,VS=0.0001)
      DATA C1/ 0.430748E-02, 0.576058E-02,-0.122564E-02, 0.114843E-03
     +      ,-0.489452E-05, 0.795991E-07, 0.326746E-02,-0.132872E-02
     +      , 0.217197E-03,-0.179769E-04, 0.766114E-06,-0.125603E-07
     +      , 0.326452E-02,-0.175331E-02, 0.415488E-03,-0.507652E-04
     +      , 0.297569E-05,-0.651741E-07, 0.847189E-03,-0.433923E-03
     +      , 0.116672E-03,-0.166799E-04, 0.110237E-05,-0.263383E-07
     +      , 0.846052E-04,-0.415764E-04, 0.129610E-04,-0.212844E-05
     +      , 0.152871E-06,-0.384393E-08, 0.300838E-05,-0.136833E-05
     +      , 0.507296E-06,-0.943623E-07, 0.720305E-08,-0.187210E-09
     +      , 0.448230E-01,-0.210048E-01, 0.379434E-02,-0.328431E-03
     +      , 0.136710E-04,-0.220593E-06,-0.539248E-02, 0.330244E-02
     +      ,-0.733726E-03, 0.732312E-04,-0.336810E-05, 0.583913E-07
     +      ,-0.106983E-02, 0.378021E-03,-0.384854E-04, 0.978156E-06
     +      , 0.410622E-07,-0.174250E-08,-0.117501E-04,-0.983887E-05
     +      , 0.239644E-05,-0.190104E-06, 0.619226E-08,-0.680932E-10/
      DATA C2/ 0.168074E-03,-0.934609E-04, 0.141293E-04,-0.854216E-06
     +      , 0.183287E-07, 0.932144E-04,-0.234926E-04, 0.136656E-05
     +      , 0.351109E-07,-0.330189E-08, 0.174523E-04, 0.253854E-05
     +      ,-0.171643E-05, 0.183074E-06,-0.566331E-08, 0.111970E-05
     +      , 0.112776E-05,-0.386924E-06, 0.367597E-07,-0.108504E-08
     +      , 0.171604E-07, 0.738801E-07,-0.218761E-07, 0.199032E-08
     +      ,-0.576173E-10,-0.105531E-03, 0.362995E-04,-0.433334E-05
     +      , 0.207664E-06,-0.330250E-08,-0.168293E-05,-0.773204E-06
     +      , 0.227974E-06,-0.159385E-07, 0.321958E-09, 0.167046E-05
     +      ,-0.440761E-06, 0.396377E-07,-0.151053E-08, 0.215624E-10/
C.
      DATA THIGH,CHIGH/100.,50./
C.    ------------------------------------------------------------------
C.
      GBRSGE=0.
*
      IF(BCUT.LE.0.) GOTO 99
      IF(BCUT.GE.T) GOTO 99
*
      IF(T.GT.THIGH) THEN
          TT=THIGH
        IF(BCUT.GE.THIGH) THEN
            EC=CHIGH
        ELSE
            EC=BCUT
        ENDIF
      ELSE
          TT=T
          EC=BCUT
      ENDIF
*
      E=TT+EMASS
*
C
      X=LOG(E/EMASS)
      Y=LOG(E*VS/EC)
C
      S=0.
      YY=1.
      DO 30 I=1,2
         XX=1.
         DO 20 J=1,6
            K=6*I+J-6
            S=S+C(K)*XX*YY
            XX=XX*X
  20     CONTINUE
         YY=YY*Y
  30  CONTINUE
      DO 50 I=3,6
         XX=1.
         DO 40 J=1,6
            K=6*I+J-6
            IF(Y.LE.0.) THEN
               S=S+C(K)*XX*YY
            ELSE
               S=S+C(K+24)*XX*YY
            ENDIF
            XX=XX*X
  40     CONTINUE
         YY=YY*Y
  50  CONTINUE
      SS=0.
      YY=1.
      DO 70 I=1,2
         XX=1.
         DO 60 J=1,5
            K=5*I+J+55
            SS=SS+C(K)*XX*YY
            XX=XX*X
  60     CONTINUE
         YY=YY*Y
  70  CONTINUE
      DO 90 I=3,5
         XX=1.
         DO 80 J=1,5
            K=5*I+J+55
            IF(Y.LE.0.) THEN
               SS=SS+C(K)*XX*YY
            ELSE
               SS=SS+C(K+15)*XX*YY
            ENDIF
            XX=XX*X
  80     CONTINUE
         YY=YY*Y
  90  CONTINUE
C
      S=S+Z*SS
      IF(S.LE.0.) GOTO 99
C
      FAC=ZZ*(ZZ+AKSI)*E*E*(LOG(TT/EC))**ALFA/(TT*(E+EMASS))
      IF(FAC.LE.0.) GOTO 99
C
      GBRSGE=FAC*S
*
      IF(T.GT.THIGH) THEN
 
       IF(BCUT.LT.THIGH) THEN
        RAT=BCUT/T
        S=(-LOG(RAT)-2./3.+RAT-RAT*RAT/3.)
        RAT=BCUT/TT
        S=S/(-LOG(RAT)-2./3.+RAT-RAT*RAT/3.)
       ELSE
        RAT=BCUT/T
        S=(-LOG(RAT)-2./3.+RAT-RAT*RAT/3.)
        RAT=EC/TT
        S=S/(-LOG(RAT)-2./3.+RAT-RAT*RAT/3.)
       ENDIF
 
        GBRSGE=GBRSGE*S
      ENDIF
*
99    RETURN
*
      END
*CMZ :  1.30/00 30/10/96  18.44.39  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.21  by  S.Giani
*-- Author :      L.Urban
      FUNCTION GBRELE(ZZ,T,BCUT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *  Calculates energy loss by soft Bremsstrahlung                 *
C.    *         (in GeV barn/atom)                                     *
C.    *                                                                *
C.    *    ==>Called by : GBRELA                                       *
C.    *       Author  L.Urban  *********                               *
C.    *  corrected by L.Urban on 23/09/96                              *
C.    *    ( correction for T>100. GeV)                                *
C.    *                                                                *
C.    ******************************************************************
C.
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEND.
      DIMENSION C(100),C1(60),C2(40)
      EQUIVALENCE (C(1),C1(1)),(C(61),C2(1))
      DATA C1/-0.960613E-01, 0.631029E-01,-0.142819E-01, 0.150437E-02
     +      ,-0.733286E-04, 0.131404E-05, 0.859343E-01,-0.529023E-01
     +      , 0.131899E-01,-0.159201E-02, 0.926958E-04,-0.208439E-05
     +      ,-0.684096E+01, 0.370364E+01,-0.786752E+00, 0.822670E-01
     +      ,-0.424710E-02, 0.867980E-04,-0.200856E+01, 0.129573E+01
     +      ,-0.306533E+00, 0.343682E-01,-0.185931E-02, 0.392432E-04
     +      , 0.127538E+01,-0.515705E+00, 0.820644E-01,-0.641997E-02
     +      , 0.245913E-03,-0.365789E-05, 0.115792E+00,-0.463143E-01
     +      , 0.725442E-02,-0.556266E-03, 0.208049E-04,-0.300895E-06
     +      ,-0.271082E-01, 0.173949E-01,-0.452531E-02, 0.569405E-03
     +      ,-0.344856E-04, 0.803964E-06, 0.419855E-02,-0.277188E-02
     +      , 0.737658E-03,-0.939463E-04, 0.569748E-05,-0.131737E-06
     +      ,-0.318752E-03, 0.215144E-03,-0.579787E-04, 0.737972E-05
     +      ,-0.441485E-06, 0.994726E-08, 0.938233E-05,-0.651642E-05
     +      , 0.177303E-05,-0.224680E-06, 0.132080E-07,-0.288593E-09/
      DATA C2/-0.245667E-03, 0.833406E-04,-0.129217E-04, 0.915099E-06
     +      ,-0.247179E-07, 0.147696E-03,-0.498793E-04, 0.402375E-05
     +      , 0.989281E-07,-0.133378E-07,-0.737702E-02, 0.333057E-02
     +      ,-0.553141E-03, 0.402464E-04,-0.107977E-05,-0.641533E-02
     +      , 0.290113E-02,-0.477641E-03, 0.342008E-04,-0.900582E-06
     +      , 0.574303E-05, 0.908521E-04,-0.256900E-04, 0.239921E-05
     +      ,-0.741271E-07,-0.341260E-04, 0.971711E-05,-0.172031E-06
     +      ,-0.119455E-06, 0.704166E-08, 0.341740E-05,-0.775867E-06
     +      ,-0.653231E-07, 0.225605E-07,-0.114860E-08,-0.119391E-06
     +      , 0.194885E-07, 0.588959E-08,-0.127589E-08, 0.608247E-10/
      DATA AKSI,BETA,VE/2.51,0.99,0.00004/
      DATA CORFAC/0.805485E-10/
C.
      DATA THIGH,CHIGH/100.,50./
C.    ------------------------------------------------------------------
C.
      GBRELE=0.
 
      IF(BCUT.LE.0.) GOTO 99
************************************
      CUTSAV=BCUT
      IF(BCUT.GT.T) BCUT=T
*************************************
      IF(T.GT.THIGH) THEN
          TT=THIGH
        IF(BCUT.GE.THIGH) THEN
            EC=CHIGH
        ELSE
            EC=BCUT
        ENDIF
      ELSE
          TT=T
          EC=BCUT
      ENDIF
 
      E=TT+EMASS
      IF(BCUT.GT.TT) EC=TT
C
      X=LOG(TT/EMASS)
      Y=LOG(EC/(E*VE))
C
      S=0.
      YY=1.
      DO 30 I=1,2
         XX=1.
         DO 20 J=1,6
            K=6*I+J-6
            S=S+C(K)*XX*YY
            XX=XX*X
  20     CONTINUE
         YY=YY*Y
  30  CONTINUE
      DO 50 I=3,6
         XX=1.
         DO 40 J=1,6
            K=6*I+J-6
            IF(Y.LE.0.) THEN
               S=S+C(K)*XX*YY
            ELSE
               S=S+C(K+24)*XX*YY
            ENDIF
            XX=XX*X
  40     CONTINUE
         YY=YY*Y
  50  CONTINUE
      SS=0.
      YY=1.
      DO 70 I=1,2
         XX=1.
         DO 60 J=1,5
            K=5*I+J+55
            SS=SS+C(K)*XX*YY
            XX=XX*X
  60     CONTINUE
         YY=YY*Y
  70  CONTINUE
      DO 90 I=3,5
         XX=1.
         DO 80 J=1,5
            K=5*I+J+55
            IF(Y.LE.0.) THEN
               SS=SS+C(K)*XX*YY
            ELSE
               SS=SS+C(K+15)*XX*YY
             ENDIF
             XX=XX*X
  80     CONTINUE
         YY=YY*Y
  90  CONTINUE
C
      S=S+Z*SS
      IF(S.LE.0.) GOTO 99
C
      CORR=1./(1.+CORFAC*DENS*Z*E*E/(A*EC*EC))
      FAC=ZZ*(ZZ+AKSI)*E*E*(EC*CORR/TT)**BETA/(E+EMASS)
      IF(FAC.LE.0.) GOTO 99
C
      GBRELE=FAC*S
 
      IF(T.GT.THIGH) THEN
 
       IF(BCUT.LT.THIGH) THEN
        RAT=BCUT/T
        S=(1.-0.5*RAT+2.*RAT*RAT/9.)
        RAT=BCUT/TT
        S=S/(1.-0.5*RAT+2.*RAT*RAT/9.)
       ELSE
        RAT=BCUT/T
        S=BCUT*(1.-0.5*RAT+2.*RAT*RAT/9.)
        RAT=EC/TT
        S=S/(EC*(1.-0.5*RAT+2.*RAT*RAT/9.))
       ENDIF
 
        GBRELE=GBRELE*S
      ENDIF
******************************************
      BCUT=CUTSAV
******************************************
C
  99  RETURN
      END
 
 
*CMZ :  1.30/00 19/09/96  18.01.50  by  Pavel Nevski
*CMZ :  3.21/04 21/02/95  11.53.59  by  S.Giani
*-- Author :
      SUBROUTINE GPAIRG
C.
C.    ******************************************************************
C.    *                                                                *
C.    *  Simulates e+e- pair production by photons.                    *
C.    *                                                                *
C.    *  The secondary electron energies are sampled using the         *
C.    *  Coulomb corrected BETHE-HEITLER cross-sections.For this the   *
C.    *   modified version of the random number techniques of          *
C.    *   BUTCHER and MESSEL (NUCL.PHYS,20(1960),15) are employed.     *
C.    *                                                                *
C.    *  NOTE :                                                        *
C.    *  (1) Effects due to the breakdown of the BORN approximation at *
C.    *      low energies are ignored.                                 *
C.    *  (2) The differential cross-section implicitly takes account   *
C.    *      of pair production in both nuclear and atomic electron    *
C.    *      fields. However, triplet production is not generated.     *
C.    *                                                                *
C.    *    ==>Called by : GTGAMA                                       *
C.    *       Authors    G.Patrick, L.Urban  *********                 *
C.    *                                                                *
C.    *  Correction: S.Randval:  PEL1 = SQRT((EEL1+EMASS)*TEL1)        *
C.    ******************************************************************
C.
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
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
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
*KEND.
      DIMENSION NTYPEL(2)
      DIMENSION RNDM(2)
      LOGICAL ROTATE
      PARAMETER (ONE=1,ONETHR=ONE/3,EMAS2=2*EMASS)
C.
C.    ------------------------------------------------------------------
C.
C             If not enough energy : no pair production
C
      EGAM   = VECT(7)
      IF (EGAM.LT.EMAS2) GO TO 999
C
      KCASE  = NAMEC(6)
      IF(IPAIR.NE.1) THEN
         ISTOP  = 2
         NGKINE = 0
         DESTEP = DESTEP + EGAM
         VECT(7)= 0.
         GEKIN  = 0.
         GETOT  = 0.
         GO TO 999
      ENDIF
C
C             For low energy photons approximate the electron energy by
C             sampling from a uniform distribution in the interval
C             EMASS -> EGAM/2.
C
      IF (EGAM.LE.2.1E - 03)THEN
         CALL GRNDM(RNDM,1)
         EEL1   = EMASS + (RNDM(1)*(0.5*EGAM - EMASS))
         X=EEL1/EGAM
         GO TO 20
      ENDIF
C
      Z3=Q(JPROB+2)
      F=8.*Q(JPROB+3)
      IF(EGAM.GT.0.05) F=F+8.*Q(JPROB+4)
      X0=EMASS/EGAM
      DX=0.5-X0
      DMIN=544.*X0/Z3
      DMIN2=DMIN*DMIN
      IF(DMIN.LE.1.)THEN
         F10=42.392-7.796*DMIN+1.961*DMIN2-F
         F20=41.405-5.828*DMIN+0.8945*DMIN2-F
      ELSE
         F10=42.24-8.368*LOG(DMIN+0.952)-F
         F20=F10
      ENDIF
C
C             Calculate limit for screening variable,DELTA, to ensure
C             that screening rejection functions always remain
C             positive.
C
      DMAX=EXP((42.24-F)/8.368)-0.952
C
C             Differential cross-section factors which form
C             the coefficients of the screening functions.
C
      DSIG1=DX*DX*F10/3.
      DSIG2=0.5*F20
      BPAR   = DSIG1 / (DSIG1 + DSIG2)
C
C             Decide which screening rejection function to use and
C             sample the electron/photon fractional energy BR.
C
   10 CALL GRNDM(RNDM,2)
      IF(RNDM(1).LT.BPAR)THEN
         X=0.5-DX*RNDM(2)**ONETHR
         IREJ=1
      ELSE
         X=X0+DX*RNDM(2)
         IREJ   = 2
      ENDIF
C
C             Calculate DELTA ensuring positivity.
C
      D=0.25*DMIN/(X*(1.-X))
      IF(D.GE.DMAX) GOTO 10
      D2=D*D
C
C             Calculate F1 and F2 functions using approximations.
C             F10 and F20 are the F1 and F2 functions calculated for the
C             DELTA=DELTA minimum.
C
      IF(D.LE.1.)THEN
         F1=42.392-7.796*D+1.961*D2-F
         F2=41.405-5.828*D+0.8945*D2-F
      ELSE
         F1=42.24-8.368*LOG(D+0.952)-F
         F2=F1
      ENDIF
      IF(IREJ.NE.2)THEN
         SCREJ=F1/F10
      ELSE
         SCREJ=F2/F20
      ENDIF
C
C             Accept or reject on basis of random variate.
C
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).GT.SCREJ) GOTO 10
      EEL1=X*EGAM
C
C             Successful sampling of first electron energy.
C
C             Select charges randomly.
C
   20 NTYPEL(1) = 2
      CALL GRNDM(RNDM,2)
      IF (RNDM(1).GT.0.5) NTYPEL(1) = 3
      NTYPEL(2) = 5 - NTYPEL(1)
C
C             Generate electron decay angles with respect to a Z-axis
C             defined along the parent photon.
C             PHI is generated isotropically and THETA is assigned
C             a universal angular distribution
C
      EMASS1 = EMASS
      THETA  = GBTETH(EEL1, EMASS1, X)*EMASS/EEL1
      SINTH  = SIN(THETA)
      COSTH  = COS(THETA)
      PHI    = TWOPI*RNDM(2)
      COSPHI = COS(PHI)
      SINPHI = SIN(PHI)
C
C             Rotate tracks into GEANT system
C
      CALL GFANG(VECT(4),COSAL,SINAL,COSBT,SINBT,ROTATE)
C
C            Polar co-ordinates to momentum components.
C
      NGKINE = 0
      TEL1 = EEL1 - EMASS
      PEL1 = SQRT((EEL1+EMASS)*TEL1)
      IF(TEL1.GT.CUTELE) THEN
         PEL1 = SQRT((EEL1+EMASS)*TEL1)
         NGKINE = NGKINE + 1
         GKIN(1,NGKINE) = PEL1 * SINTH * COSPHI
         GKIN(2,NGKINE) = PEL1 * SINTH * SINPHI
         GKIN(3,NGKINE) = PEL1 * COSTH
         GKIN(4,NGKINE) = EEL1
         GKIN(5,NGKINE) = NTYPEL(1)
         TOFD(NGKINE)=0.
         GPOS(1,NGKINE) = VECT(1)
         GPOS(2,NGKINE) = VECT(2)
         GPOS(3,NGKINE) = VECT(3)
         IF(ROTATE)
     +   CALL GDROT(GKIN(1,NGKINE),COSAL,SINAL,COSBT,SINBT)
      ELSE
         DESTEP = DESTEP + TEL1
         IF(NTYPEL(1).EQ.2) CALL GANNI2
      ENDIF
C
C             Momentum vector of second electron. Recoil momentum of
C             target nucleus/electron ignored.
C
      EEL2=EGAM-EEL1
      TEL2=EEL2-EMASS
      IF(TEL2.GT.CUTELE) THEN
         PEL2 = SQRT((EEL2+EMASS)*TEL2)
         NGKINE = NGKINE + 1
         SINTH=SINTH*PEL1/PEL2
         COSTH=SQRT(MAX(0.,1.-SINTH**2))
         GKIN(1,NGKINE)=-PEL2*SINTH*COSPHI
         GKIN(2,NGKINE)=-PEL2*SINTH*SINPHI
         GKIN(3,NGKINE)=PEL2*COSTH
         GKIN(4,NGKINE)=EEL2
         GKIN(5,NGKINE) = NTYPEL(2)
         TOFD(NGKINE)=0.
         GPOS(1,NGKINE) = VECT(1)
         GPOS(2,NGKINE) = VECT(2)
         GPOS(3,NGKINE) = VECT(3)
         IF(ROTATE)
     +   CALL GDROT(GKIN(1,NGKINE),COSAL,SINAL,COSBT,SINBT)
      ELSE
         DESTEP = DESTEP + TEL2
         IF(NTYPEL(2).EQ.2) CALL GANNI2
      ENDIF
      ISTOP = 1
      IF(NGKINE.EQ.0) ISTOP = 2
 999  END
 
 
*CMZ :  1.40/05 25/03/98  00.20.33  by  Pavel Nevski
*CMZ :  1.30/00 04/05/97  23.58.54  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.23  by  S.Giani
*-- Author :
      SUBROUTINE GSSTAK (IFLAG)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    SUBR. GSSTAK (IFLAG)                                        *
C.    *                                                                *
C.    *   Stores in auxiliary stack JSTAK the particle currently       *
C.    *    described in common /GCKINE/.                               *
C.    *                                                                *
C.    *   On request, creates also an entry in structure JKINE :       *
C.    *    IFLAG =                                                     *
C.    *     0 : No entry in JKINE structure required (user)            *
C.    *     1 : New entry in JVERTX / JKINE structures required (user) *
C.    *    <0 : New entry in JKINE structure at vertex -IFLAG (user)   *
C.    *     2 : Entry in JKINE structure exists already (from GTREVE)  *
C.    *                                                                *
C.    *   Called by : GSKING, GTREVE                                   *
C.    *   Author    : S.Banerjee, F.Bruyant                            *
C.    *   Modifications: PN - put protection against lack of memory.   *
C.    *   - reject Cerenkov photons if mechanism is not activated.     *
C.    *   - save interaction description (MECAT) in stack and NTTARG   *
C.    *   - accept all unknown IPART as geantino                       *
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
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
      INTEGER       IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT,IFINIT,NEVENT,NRNDM
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCMZFO.
      COMMON/GCMZFO/IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO(13)
C
      INTEGER       IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO
C
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
      INTEGER      NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT ,NALIVE,NTMSTO
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
*KEND.
*
      INTEGER         NVTX,ITR
      COMMON /VTXKIN/ NVTX,ITR
      REAL    UBUF(1)
      DATA    UBUF/0./
      INTEGER         IFLAG,IER,ISKIP,LP,ITRT,JST,I,MECAT
C.
C.    ------------------------------------------------------------------
*
      IF (IEOTRI.NE.0) RETURN
*
*     IF (IPART.LE.0.OR.IPART.GT.NPART) ...
      IF (IPART.LE.0)  THEN
         PRINT *, ' GSSTAK - Unknown particle code, skip track ', IPART
         GO TO 999
      ENDIF
*
* ***                          protect against lack of memory faults
      IF (IFLAG.NE.0) THEN
         CALL AGNEED(IER)
         IF (IER.NE.0) RETURN
      ENDIF
*
* ***                   create target description for GEANT produced vertices
      Mecat = 0
      If (NGKINE.GT.0 .and. NMEC.GT.0) then
          Mecat = min(LMEC(NMEC),49) + LVOLUM(NLEVEL)*100
          If (ISTOP.EQ.0) Mecat = Mecat+50 ! flag non-stopped particles
          If (ISTAK.GT.0) Mecat = -Mecat   ! flag disconnected vertex
      ENDIF
*
* ***                          Give control to user for track selection
      CALL GUSKIP(ISKIP)
      IF (ISKIP.NE.0) GO TO 999
*
* *** Check if an entry in JKINE structure is required
*
      IF (IFLAG.EQ.1) THEN
         CALL GSVERT (VERT,  ITRA, 0, UBUF, 0, NVTX)
         If (NVTX.LE.0) THEN
            Print *,' GSSTAK cannot set Vertex for ',ITRA,Mecat
            Print *,' ****** event simulation abandoned ******'
            IEOTRI=1
            RETURN
         ENDIF
         Q(6+LQ(JVERTX-NVTX))=MECAT
         CALL GSKINE (PVERT, IPART, NVTX, UBUF, 0, ITR)
      ELSE IF (IFLAG.LT.0) THEN
         NVTX = -IFLAG
         CALL GSKINE (PVERT, IPART, NVTX, UBUF, 0, ITR)
      ELSE
         IF (IFLAG.EQ.0) THEN
*          Store -ITRA in stack for a track without entry in JKINE
            ITR = -ITRA
         ELSE
            ITR = ITRA
         ENDIF
      ENDIF
*
* *** Store information in stack
*
      IF (JSTAK.EQ.0) THEN
         NDBOOK = NTSTKP*NWSTAK +3
         NDPUSH = NTSTKS*NWSTAK
         CALL MZBOOK (IXCONS,JSTAK,JSTAK,1,'STAK', 0,0,NDBOOK, IOSTAK,3)
         IQ(JSTAK+2) = NTSTKP
      ELSE IF (IQ(JSTAK+1).EQ.IQ(JSTAK+2)) THEN
         CALL AGNEED (IER)
         IF (IER.NE.0) RETURN
         CALL MZPUSH (IXCONS, JSTAK, 0, NDPUSH, 'I')
         IQ(JSTAK+2) = IQ(JSTAK+2) +NTSTKS
      ENDIF
*
      LP   = 0
      IF (IPART.LE.IQ(JPART-2)) LP = LQ(JPART-Ipart)
      IF (LP.LE.0)              LP = LQ(JPART-48)
 
*PN:  do not save Cerenkov photons if the mechanism is not activated
      ITRT =  Q(6+LP)
      IF (ITRT.EQ.7 .and. ITCKOV.EQ.0) GO TO 999
*
      JST = JSTAK +IQ(JSTAK+1)*NWSTAK +3
      IQ(JSTAK+1) = IQ(JSTAK+1) +1
      IF (IQ(JSTAK+3).EQ.0)  IQ(JSTAK+3) = IQ(JSTAK+1)
      IF (IQ(JSTAK+1).GT.NSTMAX)  NSTMAX = IQ(JSTAK+1)
*
      IQ(JST+1)   = ITR       ! track number(or parent), STACK_ONLY flag
      IQ(JST+2)   = IPART     ! particle type
      IQ(JST+3)   = Mecat     ! its production history
      DO 90 I = 1,3
         Q(JST+3+I) = VERT(I)
         Q(JST+6+I) = PVERT(I)
   90 CONTINUE
      Q(JST+10) = TOFG
      Q(JST+11) = SAFETY
      Q(JST+12) = UPWGHT
*
      NALIVE = NALIVE +1
*                                                             END GSSTAK
  999 END
*CMZ :  1.30/00 03/05/97  16.32.36  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.21  by  S.Giani
*-- Author :
      SUBROUTINE GSVERT(V,NTBEAM,NTTARG,UBUF,NWBUF,NVTX)
C.
C.    ******************************************************************
C.    *                                                                *
C     *       Creates a new vertex bank                                *
C     *       Vertex is generated from tracks NTBEAM NTTARG            *
C     *       NVTX is the new vertex number                            *
C.    *                                                                *
C.    *    ==>Called by : <USER>, GUKINE,GUSTEP                        *
C.    *       Authors    R.Brun, F.Carena, M.Hansroul  *********       *
C.    *                                                                *
C.    * Modifications:                                                 *
C.    * PN, 07/Feb/97: allow negative NTbeam and NTtarg                *
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
*KEEP,GCPUSH.
      COMMON/GCPUSH/NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
      INTEGER       NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
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
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
      INTEGER       IKINE,ITRA,ISTAK,IVERT,IPART,ITRTYP,NAPART,IPAOLD
      REAL          PKINE,AMASS,CHARGE,TLIFE,VERT,PVERT
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
      REAL     V(3),UBUF(1)
      INTEGER  LGKINE,NTBEAM,NTTARG,NWBUF,NVTX,NT(2),IER,
     >         JV,JUV,I,J,JK,NVG,NFREE
C.
C.    ------------------------------------------------------------------
C.
      CALL AGNEED (IER)
      IF (IER.NE.0) GO TO 90
 
      NVTX   = NVERTX + 1
      IF (JVERTX.EQ.0)THEN
C        simulated vertex list
         CALL MZBOOK(IXDIV,JVERTX,JVERTX,1,'VERT',NCVERT,NCVERT,2,2,0)
         IQ(JVERTX-5)=0
      ENDIF
      IF (NVTX.GT.IQ(JVERTX-2)) CALL MZPUSH(IXDIV,JVERTX,NPVERT,0,'I')
      IF (NVTX.GT.IQ(JVERTX-2)) THEN
         PRINT *,' GSVERT ERROR: WRONG NVertex ',NVTX
         GOTO 90
      ENDIF
C     one vertex parameters
      CALL MZBOOK(IXDIV,JV,JVERTX,-NVTX,'VERT',1,1,9,3,0)
C     and users buffer
      IF (NWBUF.GT.0) THEN
         CALL MZBOOK(IXDIV,JUV,JV,-1,'VERU',0,0,NWBUF,2,0)
         IQ(JUV-5)=NVTX
         DO 3 I=1,NWBUF
   3     Q(JUV+I)=UBUF(I)
      ENDIF
      DO 4 I=1,3
   4  Q(JV + I) = V(I)
      Q(JV + 4) = TOFG
      Q(JV + 5) = NTBEAM
      Q(JV + 6) = NTTARG
C
      NT(1) = NTBEAM
      NT(2) = NTTARG
      Do i=1,2
         IF (NT(i).GT.0) THEN
            JK   = LGKINE(J,NT(i))
            IF(JK.LE.0) GO TO 90
            NVG  = Q(JK + 7)
            NFREE=IQ(JK-1)-7-NVG
            IF(NFREE.LE.0) CALL MZPUSH(IXDIV,JK,0,max(2,NVG/5),'I')
            Q(JK + NVG + 8) = NVTX
            Q(JK + 7) = NVG + 1
         ENDIF
      EndDO
C
      NVERTX      = NVTX
      IQ(JVERTX+1)= NVERTX
      RETURN
C
C             Error
C
  90  NVTX   = 0
      END
 
*CMZ :  1.40/05 19/07/97  13.08.07  by  Pavel Nevski
*CMZ :  1.30/00 18/04/97  18.05.51  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.20  by  S.Giani
*-- Author :
      SUBROUTINE GSAHIT(ISET,IDET,ITRA,NUMBV,HITS,IHIT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    Routines to Communicate with the JHITS data structure       *
C.    *   ---------------------------------------------------------    *
C.    *                                                                *
C.    *   Stores  element  values  for current  hit  into  the  data   *
C.    * structure JHITS.                                               *
C.    * ISET      set number  (can be obtained from  /GCSETS/ filled   *
C.    *           by GFINDS)                                           *
C.    * IDET      detector    number   "           "               "   *
C.    *           "                                                    *
C.    * ITRA      track number producing this hit                      *
C.    * NUMBV     array  of  volume numbers  corresponding  to  list   *
C.    *           NAMESV of GSDET                                      *
C.    * HITS      array of values for current hit elements             *
C.    * IHIT      on return, current hit number.  If =0, hit has not   *
C.    *           been stored.                                         *
C.    *                                                                *
C.    *       JH=LQ(JHITS-ISET)                                        *
C.    *       JHD=LQ(JH-IDET)                                          *
C.    *       IQ(JH+IDET)= pointer to LAST USED word in JHD            *
C.    *         Each hit is packed into JHD in the following format    *
C.    *        --Track number ITRA not packed                          *
C.    *        --Volume numbers packed                                 *
C.    *        --Hits transformed and packed                           *
C.    *                                                                *
C.    *                The Hit data structure JHITS                    *
C.    *                ----------------------------                    *
C.    *                                                                *
C.    *                                            | JHITS             *
C.    *    NSET                  ISET              v                   *
C.    *     ..........................................                 *
C.    *     |                   |  |              |  |                 *
C.    *     ..........................................                 *
C.    *                           |                                    *
C.    *                           | JH                                 *
C.    *      NDET    IDET         v               NDET                 *
C.    *        .....................................                   *
C.    *        |      |  |      |  |               |                   *
C.    *        .....................................                   *
C.    *                |                                               *
C.    *                | JHD                                           *
C.    *                v                                               *
C.    *               .........................................        *
C.    *               |  | 1st hit        | 2nd hit, etc.     |        *
C.    *               .........................................        *
C.    *                         Bank layout                            *
C.    * JH            =  LQ(JHITS-ISET,)  pointer  to  hits for  set   *
C.    *           number ISET                                          *
C.    * JHD           = LQ(JH-IDET),   pointer to  hits of  detector   *
C.    *           IDET                                                 *
C.    *                  of set ISET                                   *
C.    * IQ(JH+IDET)    number of words  used so far for  storing the   *
C.    *           hits                                                 *
C.    *                  of detector IDET                              *
C.    * IQ(JHD+1)       1st word of 1st hit                            *
C.    * IQ(JHD+NWH+1)  1st word of 2nd hit                             *
C.    *                      JS=LQ(JSET-ISET)                          *
C.    *                      JD=LQ(JS-IDET)                            *
C.    *                      NWH=IQ(JD+3)                              *
C.    *   The JHITS structure is filled with the routines GSAHIT and   *
C.    * GSCHIT.   The routine GFHITS can be used to get the hits for   *
C.    * a detector IDET and set ISET.                                  *
C.    *                                                                *
C.    *    ==>Called by : <USER>, GUSTEP                               *
C.    *       Author    R.Brun  *********                              *
C.    *                                                                *
C.    ******************************************************************
C.
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
      COMMON/GCLOCA/NLOCAL(2),JS,JD,JDH,JH,JHD,LOCAL(15)
      DIMENSION NUMBV(1),HITS(1)
      SAVE NMESS
      DATA NMESS/0/
C.
C.    ------------------------------------------------------------------
C.
      IHIT=0
      IF(JSET.LE.0)GO TO 99
      NSET=IQ(JSET-1)
      IF(NSET.LE.0)GO TO 99
      IF(ISET.LE.0)GO TO 99
      IF(ISET.GT.NSET)GO TO 99
      JS=LQ(JSET-ISET)
      NDET=IQ(JS-1)
      IF(NDET.LE.0)GO TO 99
      IF(IDET.LE.0)GO TO 99
      IF(IDET.GT.NDET)GO TO 99
      JD=LQ(JS-IDET)
      JDH=LQ(JD-1)
      IF(JDH.LE.0)GO TO 99
      NW=IQ(JD+1)+IQ(JD+3)+1
      NH=IQ(JD+4)
      NV=IQ(JD+2)
C
C              Create HITS master bank
C
      IF(JHITS.EQ.0)THEN
         CALL MZBOOK(IXDIV,JHITS,JHITS,1,'HITS',NSET,NSET,0,2,0)
         IQ(JHITS-5)=0
      ENDIF
      JH=LQ(JHITS-ISET)
      IF(JH.EQ.0)THEN
         CALL MZBOOK(IXDIV,JH,JHITS,-ISET,'HITS',NDET,NDET,NDET,2,0)
      ENDIF
C
      JHD=LQ(JH-IDET)
      IF(JHD.EQ.0)THEN
C
C            Create Hits bank
C
         NWHI=IQ(JD+7)
         CALL MZBOOK(IXDIV,JHD,JH,-IDET,'SJHD',0,0,NWHI,1,0)
         IQ(JHD-5)=1000*ISET+IDET
         ILAST=0
      ELSE
C
C           Check if enough space. If not increase bank size
C
         NHD=IQ(JHD-1)
         ILAST=IQ(JH+IDET)
         NFREE=NHD-ILAST
         IF(NFREE.LE.NW)THEN
            NWHI2=MAX(100,NW,IQ(JD+7)/2)
*           CALL MZPUSH(IXDIV,JHD,0,NWHI2,'I')
            CALL AgPUSH(Idebug,JHD,0,NHD+NWHI2,Ier)
            IF (Ier.ne.0) Return
            JS  = LQ(JSET-ISET)
            JD  = LQ(JS-IDET)
            JDH = LQ(JD-1)
            JH  = LQ(JHITS-ISET)
         ENDIF
      ENDIF
C
      IQ(JH+IDET)=ILAST+NW
      IHIT=IQ(JH+IDET)/NW
C
C ========>    Store track number,volumes numbers and hits
C
      IQ(JHD+ILAST+1)=ITRA
C
C
C           Store packed volume numbers
C
      NK=ILAST+2
      IF(NV.GT.0)THEN
         K=1
C
         DO 50 I=1,NV
            NB=IQ(JD+2*I+10)
            IF(NB.LE.0)THEN
               IF(K.GT.1)THEN
                   NK=NK+1
               ENDIF
               IQ(JHD+NK)=NUMBV(I)
               K=1
               IF(I.NE.NV)NK=NK+1
            ELSE
               IF(K+NB.GT.33)THEN
                  K=1
                  NK=NK+1
               ENDIF
               CALL MVBITS(NUMBV(I),0,NB,IQ(JHD+NK),K-1)
               K=K+NB
            ENDIF
  50     CONTINUE
         NK=NK+1
      ENDIF
C
C          Store packed hits
C          Before packing, hits are changed to integers
C          Origin is shifted to have only positive integers
C          Result is multiplied by a constant to get resolution
C
      IF(NH.GT.0)THEN
         K=1
         DO 90 I=1,NH
            NB=IQ(JDH+4*I-2)
            XHIT=(HITS(I)+Q(JDH+4*I-1))*Q(JDH+4*I)
            IF(NB.EQ.0)THEN
               VALMX=2.147483E+9
            ELSE
               VALMX=2.**NB-1.
            ENDIF
            IFLAG=0
            IF(XHIT.LT.0.)THEN
               XHIT=0.
               IFLAG=1
            ELSE IF(XHIT.GT.VALMX)THEN
               XHIT=VALMX
               IFLAG=1
            ENDIF
            IF(IFLAG.NE.0)THEN
               NMESS=NMESS+1
               IF(NMESS.LT.10)THEN
                  WRITE(CHMAIL,1000)IQ(JSET+ISET),IQ(JS+IDET),I,HITS(I)
     +             ,Q(JDH+4*I-1),Q(JDH+4*I)
                  CALL GMAIL(0,0)
               ENDIF
            ENDIF
C
            KHIT=XHIT+0.5
            IF(NB.LE.0)THEN
               IF(K.GT.1)THEN
                   NK=NK+1
               ENDIF
               IQ(JHD+NK)=KHIT
               NK=NK+1
               K=1
            ELSE
               IF(K+NB.GT.33)THEN
                  K=1
                  NK=NK+1
               ENDIF
               CALL MVBITS(KHIT,0,NB,IQ(JHD+NK),K-1)
               K=K+NB
            ENDIF
  90     CONTINUE
      ENDIF
C
 1000 FORMAT(' ***** GSAHIT OVERFLOW WHEN IUSET= ',A4,' IUDET= ',
     +A4,' HITS(',I2,')=',E14.7,' ORIG= ',E14.7,' FACT= ',E14.7)
  99  RETURN
      END
*CMZ :  1.40/05 25/03/98  00.14.32  by  Pavel Nevski
*CMZ :  1.30/00 23/03/97  22.06.36  by  Pavel Nevski
*CMZ :  3.21/02 28/03/94  01.30.59  by  S.Giani
*-- Author :
      SUBROUTINE GSKINE(PLAB,IPART,NV,BUF,NWBUF,NT)
C.
C.    ******************************************************************
C.    *                                                                *
C     *       Store kinematics of track NT into data structure         *
C     *       Track is coming from vertex NV                           *
C.    *                                                                *
C.    *    ==>Called by : <USER>, GUKINE,GUSTEP                        *
C.    *       Authors    R.Brun, F.Carena, M.Hansroul  *********       *
C.    *                                                                *
C.    *    Modifications:                                              *
C.    *    PN: put all unknown particles as Geantino                   *
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
*KEEP,GCPUSH.
      COMMON/GCPUSH/NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
      INTEGER       NCVERT,NCKINE,NCJXYZ,NPVERT,NPKINE,NPJXYZ
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
 
      REAL      PLAB(3),BUF(1),P2,AMASS,E
      INTEGER   LGKINE,IPART,NV,NWBUF,NT,NTI,IER,JV,JPA,JK,JUK,NTG,
     >          I,J,NFREE,JKIN
C.
C.    ------------------------------------------------------------------
C.
      CALL AGNEED (IER)
      IF (IER.NE.0)     GO TO 90
 
      IF (NV.LE.0)      GO TO 10
      IF (JVERTX.LE.0)  GO TO 90
      IF (NV.GT.NVERTX) GO TO 90
      JV = LQ(JVERTX- NV)
      IF (JV.LE.0)      GO TO 90
C
   10 NT     = NTRACK + 1
      IF (JKINE.EQ.0) THEN
         CALL MZBOOK(IXDIV,JKINE,JKINE,1,'KINE',NCKINE,NCKINE,2,2,0)
         IQ(JKINE-5)=0
      ENDIF
      J = LgKINE(JKIN,NT)
      NTI=NT-IQ(JKIN+2)
      IF(NTI.GT.IQ(JKIN-2)) CALL MZPUSH(IXDIV,JKIN,NPKINE,0,'I')
      IF(NTI.GT.IQ(JKIN-2)) THEN
         PRINT *,' GSKINE ERROR: WRONG NTRACK ',NTRACK
         GOTO 90
      ENDIF
C
      IF (JPART.LE.0) GO TO 90
      JPA = 0
      IF (IPART.LE.IQ(JPART-2)) JPA = LQ(JPART- IPART)
      IF (JPA.LE.0)             JPA = LQ(JPART- 48)
 
      P2     = PLAB(1)**2 + PLAB(2)**2 + PLAB(3)**2
      AMASS  = Q(JPA + 7)
      E      = SQRT(P2 + AMASS*AMASS)
C
C            Store kinematics in JKINE
C
      NTRACK = NT
      IQ(JKIN+1)=NTRACK
      CALL MZBOOK(IXDIV,JK,JKIN,-NTI,'KINE',1,1,8,3,0)
      Q(JK + 1) = PLAB(1)
      Q(JK + 2) = PLAB(2)
      Q(JK + 3) = PLAB(3)
      Q(JK + 4) = E
      Q(JK + 5) = IPART
      Q(JK + 6) = NV
C
C            Copy user words
C
      IF(NWBUF.GT.0)THEN
         CALL MZBOOK(IXDIV,JUK,JK,-1,'KINU',0,0,NWBUF,3,0)
         IQ(JUK-5)=NT
C
         DO 15 I=1,NWBUF
            Q(JUK+I)=BUF(I)
   15    CONTINUE
      ENDIF
C
C
C            Connect track NT to vertex NV
C
      IF(NV.GT.0)THEN
         JV = LQ(JVERTX- NV)
         NTG = Q(JV + 7)
         NFREE=IQ(JV-1)-7-NTG
         IF(NFREE.LE.0)CALL MZPUSH(IXDIV,JV,0,max(2,NTG/5),'I')
         Q(JV + NTG + 8) = NT
         Q(JV + 7) = NTG + 1
      ENDIF
C
      GO TO 99
C
C            Error
C
  90  NT = 0
  99  RETURN
      END
 
 
*CMZ :  1.40/05 25/03/98  00.13.37  by  Pavel Nevski
*CMZ :  1.30/00 03/05/97  16.07.14  by  Pavel Nevski
*CMZ :  3.21/04 13/12/94  15.36.22  by  S.Giani
*-- Author :
      SUBROUTINE GLTRAC
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    SUBR. GLTRAC                                                *
C.    *                                                                *
C.    *   Extracts next track from stack JSTAK and prepares commons    *
C.    *    /GCTRAK/, /GCKINE/ and /GCVOLU/                             *
C.    *                                                                *
C.    *   Called by : GTREVE                                           *
C.    *   Authors   : R.Brun, F.Bruyant                                *
C.    *   Modifications:                                               *
C.    *   1. extend KINE bank with LgKINE                              *
C.    *   2. all unknown particle are treated as geantino              *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
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
*KEEP,GCSTAK.
      INTEGER  NJTMAX,NJTMIN,NTSTKP,NTSTKS,NDBOOK,NDPUSH,NJFREE,NJGARB,
     +         NJINVO,LINSAV,LMXSAV,NWSTAK,NWINT,NWREAL,NWTRAC
      INTEGER ISTORD
      PARAMETER (NWSTAK=12,NWINT=11,NWREAL=12,NWTRAC=NWINT+NWREAL+5)
      COMMON /GCSTAK/ NJTMAX, NJTMIN, NTSTKP, NTSTKS, NDBOOK, NDPUSH,
     +                NJFREE, NJGARB, NJINVO, LINSAV(15), LMXSAV(15)
      EQUIVALENCE (ISTORD,NJTMIN)
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
*KEEP,GCVOLU.
      COMMON/GCVOLU/NLEVEL,NAMES(15),NUMBER(15),
     +LVOLUM(15),LINDEX(15),INFROM,NLEVMX,NLDEV(15),LINMX(15),
     +GTRAN(3,15),GRMAT(10,15),GONLY(15),GLX(3)
C
      INTEGER NLEVEL,NAMES,NUMBER,LVOLUM,LINDEX,INFROM,NLEVMX,
     +        NLDEV,LINMX
      REAL GTRAN,GRMAT,GONLY,GLX
*KEND.
      DIMENSION RNDM(5)
      DOUBLE PRECISION P2,GETOTD,GEKIND
      DOUBLE PRECISION PXD,PYD,PZD,ONE,HNORM,DAMASS,PP
      PARAMETER (ONE=1)
      COMMON /GCKINE_CONT/ ITRO,TOFO,MECATO
C.
C.    ------------------------------------------------------------------
*
* *** Extract next track from stack JSTAK
*
      IF(ISTORD.EQ.1) THEN
*
* *** User ordering of tracks if requested
         CALL GSTORD
      ENDIF
      ISTAK = IQ(JSTAK+1)
      IQ(JSTAK+1) = ISTAK -1
      JST = JSTAK +NWSTAK*IQ(JSTAK+1) +3
      ITRA   = IQ(JST+1)
      IF (ITRA.LT.0) THEN
         ITRA = -ITRA
      ELSE
*
*        This is a new track. We set to zero the stack number and
*        update the vertex number
         ISTAK = 0
*<       JK=LQ(JKINE-ITRA)
         IVERT=Q(LgKINE(JK,ITRA)+6)
      ENDIF
*PN: extract and save ALL from stack, it may be overwritten by interactions
      ITRO   = IQ(JST+1)
      IPART  = IQ(JST+2)
      MECATO = IQ(JST+3)
      DO 60 I = 1,3
         VERT(I) = Q(JST+3+I)
        PVERT(I) = Q(JST+6+I)
   60 CONTINUE
      TOFO   = Q(JST+10)
      TOFG   = Q(JST+10)
      SAFETY = Q(JST+11)
      UPWGHT = Q(JST+12)
*
* *** Prepare tracking parameters
*
      VECT(1) = VERT(1)
      VECT(2) = VERT(2)
      VECT(3) = VERT(3)
      PXD = PVERT(1)
      PYD = PVERT(2)
      PZD = PVERT(3)
      P2 = PXD**2+PYD**2+PZD**2
      IF(P2.GT.0.) THEN
         PP    = SQRT(P2)
         HNORM = ONE/PP
         VECT(4) = PVERT(1)*HNORM
         VECT(5) = PVERT(2)*HNORM
         VECT(6) = PVERT(3)*HNORM
         VECT(7) = PP
      ELSE
         VECT(4) = 0.
         VECT(5) = 0.
         VECT(6) = 1.
         VECT(7) = 0.
      ENDIF
*
*  ** Reload Particle characteristics, if needed
*
      IF (IPART.NE.IPAOLD) THEN
         JPA = 0
         IF (IPART.LE.IQ(JPART-2)) JPA = LQ(JPART-IPART)
         IF (JPA .EQ. 0)           JPA = LQ(JPART-48)
 
         DO 90 I = 1,5
            NAPART(I) = IQ(JPA+I)
   90    CONTINUE
         ITRTYP = Q(JPA+6)
         AMASS  = Q(JPA+7)
         CHARGE = Q(JPA+8)
         TLIFE  = Q(JPA+9)
         IUPD   = 0
         IPAOLD = IPART
      ENDIF
*
      DAMASS = AMASS
      GETOTD = SQRT(P2+DAMASS**2)
      GEKIND = GETOTD - DAMASS
      GETOT  = GETOTD
      GEKIN  = GEKIND
*
      IF (ITRTYP.EQ.7) THEN
*
* *** Cerenkov photon. Retrieve polarisation
         JPO = LQ(JSTAK-1)+(ISTAK-1)*3
         POLAR(1) = Q(JPO+1)
         POLAR(2) = Q(JPO+2)
         POLAR(3) = Q(JPO+3)
      ELSE
         CALL GEKBIN
      ENDIF
*
      SLENG  = 0.
      NSTEP  = 0
      NTMSTO = NTMSTO +1
      NTMULT = NTMSTO
      ISTORY = 0
*
*  ** Initialize interaction probabilities
*
      IF (ITRTYP.EQ.1) THEN
*      Gammas
         CALL GRNDM(RNDM,5)
         ZINTPA = -LOG(RNDM(1))
         ZINTCO = -LOG(RNDM(2))
         ZINTPH = -LOG(RNDM(3))
         ZINTPF = -LOG(RNDM(4))
         ZINTRA = -LOG(RNDM(5))
      ELSE IF (ITRTYP.EQ.2) THEN
*       Electrons
         CALL GRNDM(RNDM,3)
         ZINTBR = -LOG(RNDM(1))
         ZINTDR = -LOG(RNDM(2))
         ZINTAN = -LOG(RNDM(3))
      ELSE IF (ITRTYP.EQ.3) THEN
*       Neutral hadrons
         CALL GRNDM(RNDM,2)
         SUMLIF = -CLIGHT*TLIFE*LOG(RNDM(1))
         ZINTHA = -LOG(RNDM(2))
      ELSE IF (ITRTYP.EQ.4) THEN
*       Charged hadrons
         CALL GRNDM(RNDM,3)
         SUMLIF = -CLIGHT*TLIFE*LOG(RNDM(1))
         ZINTHA = -LOG(RNDM(2))
         ZINTDR = -LOG(RNDM(3))
      ELSE IF (ITRTYP.EQ.5) THEN
*       Muons
         CALL GRNDM(RNDM,5)
         SUMLIF = -CLIGHT*TLIFE*LOG(RNDM(1))
         ZINTBR = -LOG(RNDM(2))
         ZINTPA = -LOG(RNDM(3))
         ZINTDR = -LOG(RNDM(4))
         ZINTMU = -LOG(RNDM(5))
      ELSE IF (ITRTYP.EQ.7) THEN
*       Cerenkov photons
         CALL GRNDM(RNDM,1)
         ZINTLA = -LOG(RNDM(1))
      ELSE IF (ITRTYP.EQ.8) THEN
*       Ions
         CALL GRNDM(RNDM,2)
         ZINTHA = -LOG(RNDM(1))
         ZINTDR = -LOG(RNDM(2))
      ENDIF
*
*   * Prepare common /GCVOLU/ and structure JGPAR, if needed
*
      IF (NJTMAX.LE.0) THEN
        IF (GONLY(NLEVEL).EQ.0.) NLEVEL=0
        CALL GMEDIA (VECT, NUMED)
      ENDIF
      INFROM = 0
*                                                             END GLTRAC
      END
 
 
*CMZ :  1.30/00 19/04/97  17.50.02  by  Pavel Nevski
*-- Author :    Pavel Nevski
*
      SUBROUTINE GPDCAY  (IPART)
*-
*-    ******************************************************************
*-    *                                                                *
*-    *  Print branching ratios and decay modes for GEANT particles.   *
*-    *                                                                *
*-    *    ==>Called by : <USER>                                       *
*-    *       Author    P.Nevski                                       *
*-    *                                                                *
*-    ******************************************************************
*-
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
*KEND.
      REAL      BRATIO
      INTEGER   LENOCC,IPART,IP1,IP2,IP,JPA,
     >          MODE,JDK1,JDK2,L1,L,LL,I,JP,M1
      CHARACTER CNAME*20,CMODE*200
*-
*-    ------------------------------------------------------------------
*-
      IF (IPART.EQ.0) THEN
         IP1=1
         IP2=NPART
      ELSE
         IP1=IPART
         IP2=IPART
      ENDIF
*
      DO IP=IP1,IP2
         IF (IP.LE.0)      GOTO 90
         IF (IP.GT.NPART)  GOTO 90
         JPA = LQ(JPART-IP)
         IF (JPA.LE.0)     GOTO 90
         JDK1=LQ(JPA-1) !  PABR bank
         IF (JDK1.LE.0)    GOTO 90
         JDK2=LQ(JPA-2) !  PAMO bank
         IF (JDK2.LE.0)    GOTO 90
*
         CALL UHTOC(IQ(JPA+1),4,CMODE,20)
         L1=LENOCC(CMODE(1:20))
         WRITE(LOUT,1000) IP,CMODE(1:L1)
 1000    FORMAT(I5,1x,A,'  Decay(s):')
*
*    COPY branching ratios & decay modes.
*
         DO I  = 1,6
            CMODE = CMODE(1:L1)//' => '
            LL     = L1+4
            BRATIO = Q(JDK1+I)
            IF (BRATIO.LE.0) GO TO 60
            MODE   = IQ(JDK2+I)
            DO WHILE (MODE.GT.0)
               M1  = MOD(MODE,100)
               IF (M1.LE.0) GOTO 50
               JP  = LQ(JPART-M1)
               IF (JP.LE.0) GO TO 50
               CALL UHTOC(IQ(JP+1),4,CNAME,20)
               L   = LENOCC(CNAME)
               CMODE=CMODE(1:LL)//CNAME(1:L)//' & '
               LL  = LL+L+3
  50           MODE=MODE/100
            ENDDO
            WRITE(LOUT,1001) BRATIO,CMODE(1:LL-3)
 1001       FORMAT(6x,'Branching(%)=',F8.3,' Channel: ',A)
  60     ENDDO
C
  90     CONTINUE
      ENDDO
      END
 
 
 
 
 
 
*CMZ :  1.40/05 01/07/97  10.45.18  by  Pavel Nevski
*CMZ :  1.30/00 19/04/97  17.50.46  by  Pavel Nevski
*CMZ :  3.21/03 02/08/94  18.13.20  by  S.Ravndal
*-- Author :
      SUBROUTINE GFDCAY (IPART,BRATIO,MODE)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *  Return branching ratios and decay modes for GEANT particles.  *
C.    *                                                                *
C.    *    ==>Called by : <USER>                                       *
C.    *       Author    P.Nevski                                       *
C.    *                                                                *
C.    ******************************************************************
C.
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
      REAL      BRATIO(6)
      INTEGER   MODE(6)
C.
C.    ------------------------------------------------------------------
C.
      CALL VZERO(BRATIO,6)
      CALL VZERO(MODE,6)
      IF (IPART.LE.0)      RETURN
      IF (IPART.GT.NPART)  RETURN
C
C     Particle pointer.
C
      JPA = LQ(JPART-IPART)
      IF (JPA.LE.0)        RETURN
C
C PABR bank
      JDK1=LQ(JPA-1)
      IF (JDK1.LE.0)       RETURN
C PAMO bank
      JDK2=LQ(JPA-2)
      IF (JDK2.LE.0)       RETURN
C
C     COPY branching ratios & decay modes.
C
      DO I=1,6
         BRATIO(I) = Q(JDK1+I)
         MODE(I)   = IQ(JDK2+I)
      ENDDO
C
  99  RETURN
      END
 
*CMZ :  1.40/05 29/05/98  21.36.19  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.21  by  S.Giani
*-- Author :
      SUBROUTINE GFLUCT(DEMEAN,DE)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *   Subroutine to decide which method is used to simulate        *
C.    *   the straggling around the mean energy loss.                  *
C.    *                                                                *
C.    *                                                                *
C.    *   DNMIN:  <---------->1<-------->30<--------->50<--------->    *
C.    *                                                                *
C.    *  STRA=0   :                                                    *
C.    *   LOSS=2  <----------GLANDZ-------------------><--GLANDO-->    *
C.    *   LOSS=1,3<---------------------GLANDZ-------------------->    *
C.    *   LOSS=4              no call to GFLUCT is done                *
C.    *   STRA=1  <-----------PAI---------------------><--GLANDZ-->    *
C.    *   STRA=2  <---PAI----><---ASHO---><----PAI----><--GLANDZ-->    *
C.    *                                                                *
C.    *   DNMIN :  an estimation of the number of collisions           *
C.    *            with energy close to the ionization energy          *
C.    *            (see PHYS333)                                       *
C.    *                                                                *
C.    *   Input  : DEMEAN (mean energy loss)                           *
C.    *   Output : DE   (energy loss in the current step)              *
C.    *                                                                *
C.    *    ==>Called by : GTELEC,GTMUON,GTHADR                         *
C.    *                                                                *
C.    *   Modifications:                                               *
C.    *PN,27/07/97: For Gamma<1.1 PAI fluctuations are scaled as 1/v**2*
C.    *PN,29/05/98: - no  Brems losses are added to ionization         *
C.    *             ILOSS 1 and 3 are equivalent. Thanks to F.Luerhing *
C.    ******************************************************************
C.
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
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCONST.
      REAL          PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      REAL          EMMU,PMASS,AVO
C
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCMULO.
      COMMON/GCMULO/SINMUL(101),COSMUL(101),SQRMUL(101),OMCMOL,CHCMOL
     +  ,EKMIN,EKMAX,NEKBIN,NEK1,EKINV,GEKA,GEKB,EKBIN(200),ELOW(200)
C
      REAL SINMUL,COSMUL,SQRMUL,OMCMOL,CHCMOL,EKMIN,EKMAX,ELOW,EKINV
      REAL GEKA,GEKB,EKBIN
      INTEGER NEKBIN,NEK1
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
      PARAMETER (DGEV=0.153536 E-3, DNLIM=50)
      PARAMETER (ASHMIN=1,ASHMAX=30)
**
      DE=DEMEAN
      IF (STEP. LE.0) return
      IF (ILOSS.LE.0) return
 
      POTI  = Q(JPROB+9)
      GAMMA = GETOT/AMASS
      BETA  = VECT(7)/GETOT
      XI    = DGEV*CHARGE**2*STEP*DENS*Z/(A*BETA*BETA)
      DNMIN = MIN(XI,DEMEAN)/POTI
*
*PN,27/06/97:  PAI properly tabulated for GAMMA higher than 1.1
      IF (ILOSS.EQ.2 .and. DNMIN.GE.DNLIM) THEN
 
         CALL GLANDO(ILOSS,STEP,Z,A,DENS,VECT(7),GETOT,AMASS,DELAND,I)
         DE = DEMEAN + DELAND
 
      else IF (ISTRA.GT.0 .and. DNMIN.LT.DNLIM) THEN
         DE = GSTREN(max(GAMMA,1.1),DCUTE,STEP)
         If (Gamma.LE.1.1) DE=DE*.173554/(BETA*BETA)
      ELSE
 
         DEDX  = DEMEAN/STEP
         CALL GLANDZ(Z,STEP,VECT(7),GETOT,DEDX,DE,POTI,Q(JPROB+ 10))
 
      ENDIF
*
*        Add brem losses to ionisation
*        - wrong these are LOSSES, not a measured IONIZATION !!!
*
*      NB = 0
*      IF (ITRTYP.EQ.2) NB=2*NEK1
*      IF (ITRTYP.EQ.5) NB=  NEK1
*      IF (NB.GT.0) THEN
*         JBASE = LQ(JMA-1)+NB+IEKBIN
*         DE = DE +(1.-GEKRAT)*Q(JBASE)+GEKRAT*Q(JBASE+1)
*      ENDIF
*
      END
*CMZ :  1.40/05 02/09/97  18.34.00  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.19  by  S.Giani
*-- Author :
      SUBROUTINE GSMIXT(IMAT,NAMATE,A,Z,DENS,NLMAT,WMAT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Defines mixture OR COMPOUND IMAT as composed by          *
C.    *       THE BASIC NLMAT materials defined by arrays A,Z and WMAT *
C.    *                                                                *
C.    *       If NLMAT.GT.0 then WMAT contains the PROPORTION BY       *
C.    *       WEIGTHS OF EACH BASIC MATERIAL IN THE MIXTURE.           *
C.    *                                                                *
C.    *       If NLMAT.LT.0 then WMAT contains the number of atoms     *
C.    *       of a given kind into the molecule of the COMPOUND        *
C.    *       In this case, WMAT in output is changed to relative      *
C.    *       weigths.                                                 *
C.    *                                                                *
C.    *       nb : the radiation length is computed according          *
C.    *            the EGS manual slac-210 uc-32 June-78               *
C.    *                           formula  2-6-8 (37)                  *
C.    *                                                                *
C.    *    ==>Called by : <USER>, UGEOM                                *
C.    *       Authors    R.Brun, M.Maire  *********                    *
C.    *                                                                *
C.    *    Modifications:                                              *
C.    *    PN, 2.09.97  - Calculate Abs.Length for protons, not pions  *
C.    ******************************************************************
C.
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
*KEEP,GCMZFO.
      COMMON/GCMZFO/IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO(13)
C
      INTEGER       IOMATE,IOPART,IOTMED,IOSEJD,IOSJDD,IOSJDH,IOSTAK
     +             ,IOMZFO
C
*KEND.
      DIMENSION WMAT(1),A(1),Z(1)
      CHARACTER*(*) NAMATE
      CHARACTER*20 NAME
      DATA ALR2AV , AL183 / 1.39621E-03  ,  5.20948 /
C.
C.    ------------------------------------------------------------------
C.
      IF (IMAT.LE.0)GO TO 99
      IF(JMATE.LE.0)THEN
         CALL MZBOOK(IXCONS,JMATE,JMATE,1,'MATE',NMATE,NMATE,0,3,0)
         IQ(JMATE-5)=0
      ENDIF
      IF(IMAT.GT.NMATE)THEN
         CALL MZPUSH(IXCONS,JMATE,IMAT-NMATE,0,'I')
         NMATE=IMAT
         JMA1=0
      ELSE
         JMA1=LQ(JMATE-IMAT)
         IF(JMA1.GT.0) THEN
            WRITE(CHMAIL,10000)
            CALL GMAIL(1,0)
            CALL GPMATE(IMAT)
            CALL MZDROP(IXCONS,LQ(JMATE-IMAT),' ')
         ENDIF
      ENDIF
      CALL MZBOOK(IXCONS,JMA,JMATE,-IMAT,'MATE',20,20,11,IOMATE,0)
C
      NAME=NAMATE
      NCH=LNBLNK(NAME)
      IF(NCH.GT.0)THEN
         IF(NAME(NCH:NCH).EQ.'$')NAME(NCH:NCH)=' '
      ENDIF
      CALL UCTOH(NAME,IQ(JMA+1),4,20)
C
C             Store mixture parameters
C             and parameter for Pair/Brems and
C             Photoelectric routines
C
      NLM    = IABS(NLMAT)
      IF (NLM.LE.0)GO TO 90
      CALL MZBOOK(IXCONS,JMIXT,JMA,-5,'MAMI',2,2,4*NLM,3,0)
      CALL MZBOOK(IXCONS,JMI1,JMIXT,-1,'MAM1',0,0,10,3,0)
      JMA = LQ(JMATE- IMAT)
      IQ(JMIXT-5)=IMAT
      IQ(JMI1-5)=IMAT
C
C             Compute proportion by weigths in the compound
C
      IF(NLMAT.LT.0) THEN
         AMOL   = 0.
         ZMOL   = 0.
         DO 10 I= 1,NLM
         AMOL   = AMOL + WMAT(I)*A(I)
         ZMOL   = ZMOL + WMAT(I)*Z(I)
   10    CONTINUE
         DO 20 I= 1,NLM
         WMAT(I)= WMAT(I)*A(I) / AMOL
   20    CONTINUE
      ENDIF
C
C             Compute effective mixture parameters
C
      AEFF   = 0.
      ZEFF   = 0.
      RADINV = 0.
      DO 40 I = 1,NLM
         AEFF   = AEFF + WMAT(I)*A(I)
         ZEFF   = ZEFF + WMAT(I)*Z(I)
         ZC     = Z(I)
         ALZ    = LOG(ZC)/3.
         XINV   = ZC*(ZC+GXSI(ZC))*(AL183-ALZ-GFCOUL(ZC))/A(I)
         RADINV = RADINV + WMAT(I)*XINV
         Q(JMIXT+3*NLM+I)=XINV
         Q(JMIXT + 2* NLM + I) = WMAT(I)
         Q(JMIXT + NLM + I) = Z(I)
         Q(JMIXT + I) = A(I)
   40 CONTINUE
      RADINV = ALR2AV * DENS * RADINV
      RADEFF = 1. / RADINV
      CALL GHMIX(A,WMAT,NLM,AHEFF)
      ABSEFF=10000.*AHEFF/(6.022*DENS*GHSIGM(5.,14,AHEFF))
C
      Q(JMA + 6) = AEFF
      Q(JMA + 7) = ZEFF
      Q(JMA + 8) = DENS
      Q(JMA + 9) = RADEFF
      Q(JMA + 10) = ABSEFF
      Q(JMA + 11) = NLM
      Q(JMI1 + 1) = AHEFF
      IF(NLMAT.GT.0)THEN
         Q(JMI1 + 2) = AEFF
         Q(JMI1 + 3) = ZEFF
      ELSE
         Q(JMI1 + 2) = AMOL
         Q(JMI1 + 3) = ZMOL
      ENDIF
C
      IF(JMA1.GT.0) THEN
         CALL GPMATE(-IMAT)
      ENDIF
C
      GO TO 99
C
  90  CHMAIL=' ***** GSMIXT ERROR. MIXTURE WITH NO COMPONENTS'
      CALL GMAIL(0,0)
C
  99  RETURN
10000 FORMAT(' *** GSMIXT ***: Warning, material redefinition:')
      END
*CMZ :  1.40/05 14/11/97  16.33.57  by  Pavel Nevski
*CMZ :  1.00/00 26/08/95  00.36.09  by  Pavel Nevski
*-- Author :
      SUBROUTINE TRPRFN(X1,P1,H1,X2,P2,H2,CH,XL,R,MVAR,IFLAG,ITRAN,IERR)
************************************************************************
*
*
*     SUBR. TRPRFN(X1,P1,H1,X2,P2,H2,CH,XL,*R*,MVAR,IFLAG,ITRAN,IERR*)
*
*     Origin W.Wittek    EMCSW/81/18
*
*     Finite step length case coded by V.Innocente ( Feb. 88 )
*
*     code improved:                   V.Innocente ( April. 90 )
*                   inline code replaces external function
*     code improved:                   V.Innocente ( January 91 )
*                   effect of energy loss added
*
*_______________________________________________________________________
*
* *** ERROR PROPAGATION ALONG A PARTICLE TRAJECTORY IN A MAGNETIC FIELD
*     ROUTINE ASSUMES THAT IN THE INTERVAL (X1,X2) THE QUANTITIES 1/P
*     AND (HX,HY,HZ) ARE CONSTANT.
*
* *** IFLAG  =  -1   INITIALIZATION, TRANSFORMATION OF ERROR MATRIX FROM
*                    EXTERNAL TO SC VARIABLES
*            =   0   ERROR PROPAGATION FROM X1 TO X2
*            =   1   TRANSFORMATION OF ERROR MATRIX FROM SC TO
*                    EXTERNAL VARIABLES
*
*     ITRAN          USED FOR IFLAG = 0 OR 1 ONLY
*            =   0   TRANSFORMATION MATRIX IS UPDATED ,BUT ERROR MATRIX IS NOT
*                    TRANSFORMED
*           =    1   TRANSF. MATRIX IS UPDATED  AND ERROR MATRIX IS TRANSFORMED
*
*     MVAR           SPECIFIES TYPE OF EXTERNAL VARIABLES
*            =   0   ( 1/P,LAMBDA,PHI,YT, ZT ;   SC   )
*            =   1   ( 1/P,  Y',  Z',  Y,  Z ; SPLINE )
*
* *** X1, P1, H1     X,Y,Z COMPONENTS OF POSITION, MOMENTUM AND MAGNETIC   INPUT
*                    FIELD VECTOR/GRADIENT AT STARTING POINT OF INTERVAL
*     X2, P2, H2     ......  AT END POINT OF INTERVAL                      INPUT
*     CH             CHARGE OF PARTICLE                                    INPUT
*     XL             PATHLENGTH FROM X1 TO X2   ( NEGATIVE IF OPPOSITE
*                    TO ACTUAL MOVEMENT OF PARTICLE )                      INPUT
*     R              ERROR MATRIX  (TRIANGLE)                       INPUT/OUTPUT
*     B              5 * 5 TRANSFORMATION MATRIX FOR ERRORS IN
*                    SC VARIABLES                                         OUTPUT
*
* *** IERR   =  1    ILLEGAL VALUE OF MVAR                                OUTPUT
*               2    MOMENTUM IS ZERO
*               3    H*ALFA/P AT X1 AND X2 DIFFER TOO MUCH
*               4    PARTICLE MOVES IN Z - DIRECTION
*
************************************************************************
*
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL  X1,P1,H1,X2,P2,H2,R,CH,PS,PC,XL,SPX
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      DIMENSION X1(3),P1(3),H1(9),X2(3),P2(3),H2(9)
      DIMENSION R(15),PS(3),PC(3)
*
      DIMENSION T1(3),T2(3),U1(3),U2(3),V1(3),V2(3),HN(9)
      DIMENSION AN2(3),DX(3)
      DIMENSION HV1(3),HU1(3)
*
      SAVE INIT,DELHP6,CFACT8
*
      DATA INIT/0/
      DATA DELHP6/300.D0/
*
      DATA CFACT8 / 2.997925 D-4 /
*
*____________________________________________________________________
*
      IERR=0
      IF(IFLAG) 10, 20, 80
*
* *** TRANSFORM ERROR MATRIX FROM EXTERNAL TO INTERNAL VARIABLES;
*
   10 NEW=1
      IF(MVAR.NE.1) GO TO 11
      PA1=SQRT(P1(1)**2+P1(2)**2+P1(3)**2)
      IF(PA1.EQ.0.) GO TO 902
      PS(1)=1./PA1
      IF(P1(1).EQ.0.) GO TO 904
      PS(2)=P1(2)/P1(1)
      PS(3)=P1(3)/P1(1)
      SPX=1.
      IF(P1(1).LT.0.) SPX=-1.
      CALL TRSPSC(PS,R,PC,R,H1,CH,IERR,SPX)
      GO TO 19
*
   11 IF(MVAR.NE.0) GO TO 901
   19 GO TO 900
*
* *** ERROR PROPAGATION ON A HELIX ASSUMING SC VARIABLES
 
*
   20 PA1=SQRT(P1(1)**2+P1(2)**2+P1(3)**2)
      PA2=SQRT(P2(1)**2+P2(2)**2+P2(3)**2)
      IF(PA1*PA2.EQ.0.) GO TO 902
C      DPA = PA2 - PA1
      PM1=1./PA1
      PM2=1./PA2
      DPM = PM2 - PM1
*
      DO 201 I=1,3
        T1(I) = P1(I)*PM1
        T2(I) = P2(I)*PM2
201   CONTINUE
*
      SINL=T2(3)
      SINL0=T1(3)
*
      COSL=SQRT(ABS(1.-SINL**2))
      IF(COSL.EQ.0.) GO TO 904
      COSL1=1./COSL
      COSL0=SQRT(ABS(1.-SINL0**2))
*
* *** DEFINE TRANSFORMATION MATRIX BETWEEN X1 AND X2 FOR
* *** NEUTRAL PARTICLE OR FIELDFREE REGION
*
      DO 26 I=1,5
         DO 15 K=1,5
            A(I,K)=0.
   15    CONTINUE
         A(I,I)=1.
   26 CONTINUE
      A(4,3)=XL*COSL
      A(5,2)=XL
*
      IF(CH.EQ.0.) GO TO 45
      HA1=SQRT(H1(1)**2+H1(2)**2+H1(3)**2)
      HA2=SQRT(H2(1)**2+H2(2)**2+H2(3)**2)
      HAM1=HA1*PM1
      HAM2=HA2*PM2
      HAMX=MAX(HAM1,HAM2)
      IF(HAMX.EQ.0.) GO TO 45
*
*
*
* *** CHECK WHETHER H*ALFA/P IS TOO DIFFERENT AT X1 AND X2
*
*
      IF(HA2.NE.0.) THEN
         GAM=(H2(1)*T2(1)+H2(2)*T2(2)+H2(3)*T2(3))/HA2
      ELSE
         GAM=(H1(1)*T1(1)+H1(2)*T1(2)+H1(3)*T1(3))/HA1
      ENDIF
*
      ALFA2=1.-GAM**2
*
      DH2=(H1(1)*PM1-H2(1)*PM2)**2+
     1    (H1(2)*PM1-H2(2)*PM2)**2+
     1    (H1(3)*PM1-H2(3)*PM2)**2
      IF(DH2*ALFA2.GT.DELHP6**2) GO TO 903
*
* *** DEFINE AVERAGE MAGNETIC FIELD AND GRADIENT
*
      PM12=(PM1+PM2)*0.5
      P12=1./(2.*PM12)
      HN(1)=(H1(1)*PM1+H2(1)*PM2)*P12*CH*CFACT8
      HN(2)=(H1(2)*PM1+H2(2)*PM2)*P12*CH*CFACT8
      HN(3)=(H1(3)*PM1+H2(3)*PM2)*P12*CH*CFACT8
CC    HN(4)=(H1(4)*PM1+H2(4)*PM2)*P12*CH*CFACT8
CC    HN(5)=(H1(5)*PM1+H2(5)*PM2)*P12*CH*CFACT8
CC    HN(6)=(H1(6)*PM1+H2(6)*PM2)*P12*CH*CFACT8
CC    HN(7)=(H1(7)*PM1+H2(7)*PM2)*P12*CH*CFACT8
CC    HN(8)=(H1(8)*PM1+H2(8)*PM2)*P12*CH*CFACT8
CC    HN(9)=(H1(9)*PM1+H2(9)*PM2)*P12*CH*CFACT8
*
      HM = SQRT(HN(1)**2+HN(2)**2+HN(3)**2)
      OVER = 1./HM
      HN(1) = OVER*HN(1)
      HN(2) = OVER*HN(2)
      HN(3) = OVER*HN(3)
      PAV = .5*(PA1+PA2)
      Q = - HM/PAV
      THETA = Q*XL
      SINT = SIN(THETA)
      COST = COS(THETA)
      GAMMA=HN(1)*T2(1)+HN(2)*T2(2)+HN(3)*T2(3)
      AN2(1) = HN(2)*T2(3)-HN(3)*T2(2)
      AN2(2) = HN(3)*T2(1)-HN(1)*T2(3)
      AN2(3) = HN(1)*T2(2)-HN(2)*T2(1)
*
      AU = 1./SQRT(T1(1)**2+T1(2)**2)
      U1(1) = -AU*T1(2)
      U1(2) =  AU*T1(1)
      U1(3) =  0.D0
      V1(1) = -T1(3)*U1(2)
      V1(2) =  T1(3)*U1(1)
      V1(3) =  T1(1)*U1(2)-T1(2)*U1(1)
*
      AU = 1./SQRT(T2(1)**2+T2(2)**2)
      U2(1) = -AU*T2(2)
      U2(2) =  AU*T2(1)
      U2(3) =  0.D0
      V2(1) = -T2(3)*U2(2)
      V2(2) =  T2(3)*U2(1)
      V2(3) =  T2(1)*U2(2)-T2(2)*U2(1)
*
      DX(1) = X1(1) - X2(1)
      DX(2) = X1(2) - X2(2)
      DX(3) = X1(3) - X2(3)
*
*
* *** COMPLETE TRANSFORMATION MATRIX BETWEEN ERRORS AT X1 AND X2
* *** FIELD GRADIENT PERPENDICULAR TO TRACK IS PRESENTLY NOT
* *** TAKEN INTO ACCOUNT
*
   30 CONTINUE
      QP  = Q*PAV
      ANV = -(HN(1)*U2(1)+HN(2)*U2(2)            )
      ANU =  (HN(1)*V2(1)+HN(2)*V2(2)+HN(3)*V2(3))
      OMCOST = 1.-COST
      TMSINT = THETA-SINT
*
      HU1(1) =            -HN(3)*U1(2)
      HU1(2) = HN(3)*U1(1)
      HU1(3) = HN(1)*U1(2)-HN(2)*U1(1)
*
      HV1(1) = HN(2)*V1(3)-HN(3)*V1(2)
      HV1(2) = HN(3)*V1(1)-HN(1)*V1(3)
      HV1(3) = HN(1)*V1(2)-HN(2)*V1(1)
*
***   1/P
*
      A(1,1) = 1.-DPM*PAV*(1.+(T2(1)*DX(1)+T2(2)*DX(2)+T2(3)*DX(3))/XL)
     +           +2.*DPM*PAV
*
      A(1,2) =  -DPM/THETA*
     1           ( TMSINT*GAMMA*(HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3)) +
     2             SINT*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3)) +
     3             OMCOST*(HV1(1)*T2(1)+HV1(2)*T2(2)+HV1(3)*T2(3)) )
*
      A(1,3) =  -COSL0*DPM/THETA*
     1           ( TMSINT*GAMMA*(HN(1)*U1(1)+HN(2)*U1(2)            ) +
     2             SINT*(U1(1)*T2(1)+U1(2)*T2(2)            ) +
     3             OMCOST*(HU1(1)*T2(1)+HU1(2)*T2(2)+HU1(3)*T2(3)) )
*
      A(1,4) =  -DPM/XL*(U1(1)*T2(1)+U1(2)*T2(2)            )
*
      A(1,5) =  -DPM/XL*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3))
*
***   Lambda
*
      A(2,1) = -QP*ANV*(T2(1)*DX(1)+T2(2)*DX(2)+T2(3)*DX(3))
     +         *(1.+DPM*PAV)
*
      A(2,2) = COST*(V1(1)*V2(1)+V1(2)*V2(2)+V1(3)*V2(3)) +
     +         SINT*(HV1(1)*V2(1)+HV1(2)*V2(2)+HV1(3)*V2(3)) +
     1         OMCOST*(HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3))*
     A                (HN(1)*V2(1)+HN(2)*V2(2)+HN(3)*V2(3)) +
     2         ANV*( -SINT*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3)) +
     3         OMCOST*(V1(1)*AN2(1)+V1(2)*AN2(2)+V1(3)*AN2(3)) -
     4         TMSINT*GAMMA*(HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3)) )
*
      A(2,3) = COST*(U1(1)*V2(1)+U1(2)*V2(2)            ) +
     +         SINT*(HU1(1)*V2(1)+HU1(2)*V2(2)+HU1(3)*V2(3)) +
     1         OMCOST*(HN(1)*U1(1)+HN(2)*U1(2)            )*
     A                (HN(1)*V2(1)+HN(2)*V2(2)+HN(3)*V2(3)) +
     2         ANV*( -SINT*(U1(1)*T2(1)+U1(2)*T2(2)            ) +
     3         OMCOST*(U1(1)*AN2(1)+U1(2)*AN2(2)             ) -
     4         TMSINT*GAMMA*(HN(1)*U1(1)+HN(2)*U1(2)            ) )
      A(2,3) = COSL0*A(2,3)
*
      A(2,4) = -Q*ANV*(U1(1)*T2(1)+U1(2)*T2(2)            )
*
      A(2,5) = -Q*ANV*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3))
*
***   Phi
*
      A(3,1) = -QP*ANU*(T2(1)*DX(1)+T2(2)*DX(2)+T2(3)*DX(3))*COSL1
     +         *(1.+DPM*PAV)
*
      A(3,2) = COST*(V1(1)*U2(1)+V1(2)*U2(2)            ) +
     +         SINT*(HV1(1)*U2(1)+HV1(2)*U2(2)             ) +
     1         OMCOST*(HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3))*
     A                (HN(1)*U2(1)+HN(2)*U2(2)            ) +
     2         ANU*( -SINT*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3)) +
     3         OMCOST*(V1(1)*AN2(1)+V1(2)*AN2(2)+V1(3)*AN2(3)) -
     4         TMSINT*GAMMA*(HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3)) )
      A(3,2) = COSL1*A(3,2)
*
      A(3,3) = COST*(U1(1)*U2(1)+U1(2)*U2(2)            ) +
     +         SINT*(HU1(1)*U2(1)+HU1(2)*U2(2)             ) +
     1         OMCOST*(HN(1)*U1(1)+HN(2)*U1(2)            )*
     A                (HN(1)*U2(1)+HN(2)*U2(2)            ) +
     2         ANU*( -SINT*(U1(1)*T2(1)+U1(2)*T2(2)            ) +
     3         OMCOST*(U1(1)*AN2(1)+U1(2)*AN2(2)             ) -
     4         TMSINT*GAMMA*(HN(1)*U1(1)+HN(2)*U1(2)            ) )
      A(3,3) = COSL1*COSL0*A(3,3)
*
      A(3,4) = -Q*ANU*(U1(1)*T2(1)+U1(2)*T2(2)            )*COSL1
*
      A(3,5) = -Q*ANU*(V1(1)*T2(1)+V1(2)*T2(2)+V1(3)*T2(3))*COSL1
*
***   Yt
*
      A(4,1) = PAV*(U2(1)*DX(1)+U2(2)*DX(2)            )
     +         *(1.+DPM*PAV)
*
      A(4,2) = (   SINT*(V1(1)*U2(1)+V1(2)*U2(2)            ) +
     1           OMCOST*(HV1(1)*U2(1)+HV1(2)*U2(2)             ) +
     2           TMSINT*(HN(1)*U2(1)+HN(2)*U2(2)            )*
     3                  (HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3)) )/Q
*
      A(4,3) = (   SINT*(U1(1)*U2(1)+U1(2)*U2(2)            ) +
     1           OMCOST*(HU1(1)*U2(1)+HU1(2)*U2(2)             ) +
     2           TMSINT*(HN(1)*U2(1)+HN(2)*U2(2)            )*
     3                  (HN(1)*U1(1)+HN(2)*U1(2)            ) )*COSL0/Q
*
      A(4,4) = (U1(1)*U2(1)+U1(2)*U2(2)            )
*
      A(4,5) = (V1(1)*U2(1)+V1(2)*U2(2)            )
*
***   Zt
*
      A(5,1) = PAV*(V2(1)*DX(1)+V2(2)*DX(2)+V2(3)*DX(3))
     +         *(1.+DPM*PAV)
*
      A(5,2) = (   SINT*(V1(1)*V2(1)+V1(2)*V2(2)+V1(3)*V2(3)) +
     1           OMCOST*(HV1(1)*V2(1)+HV1(2)*V2(2)+HV1(3)*V2(3)) +
     2           TMSINT*(HN(1)*V2(1)+HN(2)*V2(2)+HN(3)*V2(3))*
     3                  (HN(1)*V1(1)+HN(2)*V1(2)+HN(3)*V1(3)) )/Q
*
      A(5,3) = (   SINT*(U1(1)*V2(1)+U1(2)*V2(2)            ) +
     1           OMCOST*(HU1(1)*V2(1)+HU1(2)*V2(2)+HU1(3)*V2(3)) +
     2           TMSINT*(HN(1)*V2(1)+HN(2)*V2(2)+HN(3)*V2(3))*
     3                  (HN(1)*U1(1)+HN(2)*U1(2)            ) )*COSL0/Q
*
      A(5,4) = (U1(1)*V2(1)+U1(2)*V2(2)            )
*
      A(5,5) = (V1(1)*V2(1)+V1(2)*V2(2)+V1(3)*V2(3))
   45 CONTINUE
*
* *** NEW = 0  TRANSFORMATION MATRIX IS UPDATED
*           1  TRANSFORMATION MATRIX IS INITIALIZED
*
      IF(NEW.EQ.0) GO TO 23
      NEW=0
      DO 25 I=1,5
         DO 24 K=1,5
            B(I,K)=A(I,K)
   24    CONTINUE
   25 CONTINUE
      GO TO 27
   23 CONTINUE
*
      CALL XMM55(A,B,B)
*
   27 CONTINUE
   80 IF(ITRAN.EQ.0) GO TO 90
*
*
      J=0
      DO 22 I=1,5
         DO 21 K=I,5
            J=J+1
            S(J)=R(J)
   21    CONTINUE
   22 CONTINUE
*
*
* *** TRANSFORM ERROR MATRIX
*
      CALL SSMT5T(B,S,S)
*
      NEW=1
 
      J=0
      DO 41 I=1,5
         DO 40 K=I,5
            J=J+1
            R(J)=S(J)
   40    CONTINUE
   41 CONTINUE
*
   90 IF(IFLAG.LE.0) GO TO 900
*
*
* *** TRANSFORM ERROR MATRIX FROM INTERNAL TO EXTERNAL VARIABLES;
*
*
      NEW=1
      IF(MVAR.NE.1) GO TO 91
      PC(1)=PM2
      PC(2)=ASIN(P2(3)*PC(1))
      IF (ABS (P2(1)) .LT. 1.E-30) P2(1) = 1.E-30
      PC(3)=ATAN2(P2(2),P2(1))
      CALL TRSCSP(PC,R,PS,R,H2,CH,IERR,SPX)
      GO TO 900
*
   91 IF(MVAR.NE.0) GO TO 901
      GO TO 900
*
* *** ERROR EXITS
*
  901 IERR=1
      GO TO 999
  902 IERR=2
      GO TO 999
  903 IERR=3
C     IF(INIT.NE.0) GO TO 30
*     WRITE (LOUT, 998) DH2,ALFA2,XL
  998 FORMAT('0',' *** S/R TRPROP   DELTA(H*ALFA/P)',5X
     1,'EXCEEDS TOLERANCE    '/'0',3E12.5//' **********    ',///)
      INIT=1
      GO TO 30
  904 IERR=4
  999 WRITE (LOUT, 1000) IERR
 1000 FORMAT(1H ,' *** S/R ERPROP   IERR =',I5)
*
  900 CONTINUE
      END
 
*CMZ :  1.40/05 14/11/97  16.33.57  by  Pavel Nevski
*CMZ :  1.00/00 26/08/95  00.38.03  by  Pavel Nevski
*-- Author :
C
      SUBROUTINE TRPROP(X1,P1,H1,X2,P2,H2,CH,XL,R,MVAR,IFLAG,ITRAN,IERR)
C
C *** ERROR PROPAGATION ALONG A PARTICLE TRAJECTORY IN A MAGNETIC FIELD
C     ROUTINE ASSUMES THAT IN THE INTERVAL (X1,X2) THE QUANTITIES 1/P
C     AND (HX,HY,HZ) ARE RATHER CONSTANT. DELTA(PHI) MUST NOT BE TOO LARGE
C
C     Authors: A. Haas and W. Wittek
C
C *** IFLAG  =  -1   INITIALIZATION, TRANSFORMATION OF ERROR MATRIX FROM
C                    EXTERNAL TO SC VARIABLES
C            =   0   ERROR PROPAGATION FROM X1 TO X2
C            =   1   TRANSFORMATION OF ERROR MATRIX FROM SC TO
C                    EXTERNAL VARIABLES
C
C     ITRAN          USED FOR IFLAG = 0 OR 1 ONLY
C            =   0   TRANSFORMATION MATRIX IS UPDATED ,BUT ERROR MATRIX IS NOT
C                    TRANSFORMED
C           =    1   TRANSF. MATRIX IS UPDATED  AND ERROR MATRIX IS TRANSFORMED
C
C     MVAR           SPECIFIES TYPE OF EXTERNAL VARIABLES
C            =   0   ( 1/P,LAMBDA,PHI,YT, ZT ;   SC   )
C            =   1   ( 1/P,  Y',  Z',  Y,  Z ; SPLINE )
C
C *** X1, P1, H1     X,Y,Z COMPONENTS OF POSITION, MOMENTUM AND MAGNETIC   INPUT
C                    FIELD VECTOR/GRADIENT AT STARTING POINT OF INTERVAL
C     X2, P2, H2     ......  AT END POINT OF INTERVAL                      INPUT
C     CH             CHARGE OF PARTICLE                                    INPUT
C     XL             PATHLENGTH FROM X1 TO X2   ( NEGATIVE IF OPPOSITE
C                    TO ACTUAL MOVEMENT OF PARTICLE )                      INPUT
C     R              ERROR MATRIX  (TRIANGLE)                       INPUT/OUTPUT
C     B              5 * 5 TRANSFORMATION MATRIX FOR ERRORS IN
C                    SC VARIABLES                                         OUTPUT
C
C *** IERR   =  1    ILLEGAL VALUE OF MVAR                                OUTPUT
C               2    MOMENTUM IS ZERO
C               3    H*ALFA/P AT X1 AND X2 DIFFER TOO MUCH
C                    OR DELTA PHI IS TOO LARGE
C               4    PARTICLE MOVES IN Z - DIRECTION
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL  X1,P1,H1,X2,P2,H2,R,CH,PS,PC,XL,SPX
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      DIMENSION X1(3),P1(3),H1(9),X2(3),P2(3),H2(9)
      DIMENSION R(15),PS(3),PC(3),HN(9)
C
      SAVE INIT,DELHP6,CFACT8
*
      DATA INIT/0/
      DATA DELHP6/300.D0/,DELFI6/0.1D0/
      DATA CFACT8 / 2.997925 D-4 /
C
      IERR=0
      IF(IFLAG) 10, 20, 80
C
C *** TRANSFORM ERROR MATRIX FROM EXTERNAL TO INTERNAL VARIABLES;
C
   10 NEW=1
      IF(MVAR.NE.1) GO TO 11
      PA1=SQRT(P1(1)**2+P1(2)**2+P1(3)**2)
      IF(PA1.EQ.0.) GO TO 902
      PS(1)=1./PA1
      IF(P1(1).EQ.0.) GO TO 904
      PS(2)=P1(2)/P1(1)
      PS(3)=P1(3)/P1(1)
      SPX=1.
      IF(P1(1).LT.0.) SPX=-1.
      CALL TRSPSC(PS,R,PC,R,H1,CH,IERR,SPX)
      GO TO 19
C
   11 IF(MVAR.NE.0) GO TO 901
   19 GO TO 900
C
C *** ERROR PROPAGATION ON A HELIX ASSUMING SC VARIABLES
 
C
   20 PA1=SQRT(P1(1)**2+P1(2)**2+P1(3)**2)
      PA2=SQRT(P2(1)**2+P2(2)**2+P2(3)**2)
      IF(PA1*PA2.EQ.0.) GO TO 902
      PM1=1./PA1
      PM2=1./PA2
C
      TN(1)=P1(1)+P2(1)
      TN(2)=P1(2)+P2(2)
      TN(3)=P1(3)+P2(3)
      PM12=1./SQRT(TN(1)**2+TN(2)**2+TN(3)**2)
      TN(1)=TN(1)*PM12
      TN(2)=TN(2)*PM12
      TN(3)=TN(3)*PM12
C
      SINL=TN(3)
      COSL=SQRT(ABS(1.-SINL**2))
      IF(COSL.EQ.0.) GO TO 904
      COSL1=1./COSL
      SINP=TN(2)*COSL1
      COSP=TN(1)*COSL1
C
C *** DEFINE TRANSFORMATION MATRIX BETWEEN X1 AND X2 FOR
C *** NEUTRAL PARTICLE OR FIELDFREE REGION
C
      DO 26 I=1,5
         DO 15 K=1,5
            A(I,K)=0.
   15    CONTINUE
         A(I,I)=1.
   26 CONTINUE
      A(4,3)=XL*COSL
      A(5,2)=XL
C
      IF(CH.EQ.0.) GO TO 45
      HA1=SQRT(H1(1)**2+H1(2)**2+H1(3)**2)
      HA2=SQRT(H2(1)**2+H2(2)**2+H2(3)**2)
      HAM1=HA1*PM1
      HAM2=HA2*PM2
      HAMX = MAX(HAM1,HAM2)
      IF(HAMX.EQ.0.) GO TO 45
C
C *** DEFINE AVERAGE MAGNETIC FIELD AND GRADIENT
C
      PM12=(PM1+PM2)*0.5
      P12=1./(2.*PM12)
      HN(1)=(H1(1)*PM1+H2(1)*PM2)*P12*CH*CFACT8
      HN(2)=(H1(2)*PM1+H2(2)*PM2)*P12*CH*CFACT8
      HN(3)=(H1(3)*PM1+H2(3)*PM2)*P12*CH*CFACT8
      HN(4)=(H1(4)*PM1+H2(4)*PM2)*P12*CH*CFACT8
      HN(5)=(H1(5)*PM1+H2(5)*PM2)*P12*CH*CFACT8
      HN(6)=(H1(6)*PM1+H2(6)*PM2)*P12*CH*CFACT8
      HN(7)=(H1(7)*PM1+H2(7)*PM2)*P12*CH*CFACT8
      HN(8)=(H1(8)*PM1+H2(8)*PM2)*P12*CH*CFACT8
      HN(9)=(H1(9)*PM1+H2(9)*PM2)*P12*CH*CFACT8
C
      B0=HN(1)*COSP+HN(2)*SINP
      B2=-HN(1)*SINP+HN(2)*COSP
      B3=-B0*SINL+HN(3)*COSL
      TGL=SINL*COSL1
C
C
C *** CHECK WHETHER H*ALFA/P IS TOO DIFFERENT AT X1 AND X2
C     AND WHETHER CHANGE OF TRACK DIRECTION DUE TO MAG.FIELD IS TOO LARGE
C
C
      IF(HA2.EQ.0.) GO TO 29
 
      GAM=(H2(1)*TN(1)+H2(2)*TN(2)+H2(3)*TN(3))/HA2
      GO TO 28
   29 GAM=(H1(1)*TN(1)+H1(2)*TN(2)+H1(3)*TN(3))/HA1
   28 CONTINUE
      ALFA=SQRT(ABS(1.-GAM**2))
C
      DH2=(H1(1)*PM1-H2(1)*PM2)**2+
     1    (H1(2)*PM1-H2(2)*PM2)**2+
     1    (H1(3)*PM1-H2(3)*PM2)**2
      IF(DH2*ALFA**2.GT.DELHP6**2) GO TO 903
      ALFAQ=-ALFA*CFACT8*(HAM1+HAM2)*0.5
      DFI=ABS(XL*ALFAQ)
      IF(DFI.GT.DELFI6) GO TO 903
C
C *** COMPLETE TRANSFORMATION MATRIX BETWEEN ERRORS AT X1 AND X2
C *** TAKING INTO ACCOUNT  FIELD GRADIENT PERPENDICULAR TO TRACK
C
   30 COSP2=COSP*COSP
      SINP2=SINP*SINP
      COSIP=COSP*SINP
C
      G22=SINP2*HN(9)+COSP2*HN(8)-2.0*COSIP*HN(7)
      G33=SINL*SINL*(COSP2*HN(9)+SINP2*HN(8)+2.0*COSIP*HN(7))
     ++COSL*(COSL*HN(6)-2.0*SINL*(COSP*HN(4)+SINP*HN(5)))
      G23=SINL*(COSIP*(HN(9)-HN(8))+(SINP2-COSP2)*HN(7))
     ++COSL*(COSP*HN(5)-SINP*HN(4))
C
      A(2,1)=XL*B2
      A(2,3)=-B0*XL*PM12
      A(2,4)=(B2*B3*PM12+G22)*XL*PM12
      A(2,5)=(-B2*B2*PM12+G23)*XL*PM12
C
      A(3,1)=-XL*B3*COSL1
      A(3,2)=B0*XL*PM12*COSL1**2
      A(3,3)=1.+TGL*B2*XL*PM12
      A(3,4)=(-B3*B3*PM12-G23)*XL*PM12*COSL1
      A(3,5)=(B3*B2*PM12-G33)*XL*PM12*COSL1
C
      A(4,5)=-B3*TGL*XL*PM12
      A(5,4)=B3*TGL*XL*PM12
C
   45 CONTINUE
C
C *** NEW = 0  TRANSFORMATION MATRIX IS UPDATED
C           1  TRANSFORMATION MATRIX IS INITIALIZED
C
      IF(NEW.EQ.0) GO TO 23
      NEW=0
      DO 25 I=1,5
         DO 24 K=1,5
            B(I,K)=A(I,K)
   24    CONTINUE
   25 CONTINUE
      GO TO 27
   23 CONTINUE
C
      CALL XMM55(A,B,B)
C
   27 CONTINUE
   80 IF(ITRAN.EQ.0) GO TO 90
C
C
      J=0
      DO 22 I=1,5
         DO 21 K=I,5
            J=J+1
            S(J)=R(J)
   21    CONTINUE
   22 CONTINUE
C
C
C *** TRANSFORM ERROR MATRIX
C
      CALL SSMT5T(B,S,S)
C
      NEW=1
 
      J=0
      DO 41 I=1,5
         DO 40 K=I,5
            J=J+1
            R(J)=S(J)
   40    CONTINUE
   41 CONTINUE
C
   90 IF(IFLAG.LE.0) GO TO 900
C
C
C *** TRANSFORM ERROR MATRIX FROM INTERNAL TO EXTERNAL VARIABLES;
C
C
      NEW=1
      IF(MVAR.NE.1) GO TO 91
      PC(1)=PM2
      PC(2)=ASIN(P2(3)*PC(1))
      IF (ABS (P2(1)) .LT. 1.E-30) P2(1) = 1.E-30
      PC(3) = ATAN2 (P2(2),P2(1))
      CALL TRSCSP(PC,R,PS,R,H2,CH,IERR,SPX)
      GO TO 900
C
   91 IF(MVAR.NE.0) GO TO 901
      GO TO 900
C
C *** ERROR EXITS
C
  901 IERR=1
      GO TO 999
  902 IERR=2
      GO TO 999
  903 IERR=3
      IF(INIT.NE.0) GO TO 30
C     WRITE (LOUT, 998) DH2,DFI,ALFA,XL
C 998 FORMAT(1H0,48H *** S/R TRPROP   DELTA(H*ALFA/P)  OR DELTA(PHI),5X
C    1,22HEXCEEDS TOLERANCE     /1H0,4E12.5//16H **********    ,
C    251HATTENTION !   NO FURTHER WARNINGS WILL BE GIVEN    ///)
      INIT=1
      GO TO 30
  904 IERR=4
  999 WRITE (LOUT, 1000) IERR
 1000 FORMAT(1H ,' *** S/R ERPROP   IERR =',I5)
C
  900 RETURN
      END
 
*CMZ :  1.40/05 14/11/97  16.33.57  by  Pavel Nevski
*CMZ :  1.00/00 19/03/92  12.19.31  by  Federico Carminati
*-- Author :
C
      SUBROUTINE TRSCSP(PC,RC,PS,RS,H,CH,IERR,SPX)
C
C *** TRANSFORMS ERROR MATRIX
C     FROM   SC   VARIABLES (1/P,LAMBDA,PHI,YT,ZT)
C      TO  SPLINE VARIABLES (1/P,Y',Z',Y,Z)
C
C     Authors: A. Haas and W. Wittek
C
C
C *** PC(3)     1/P,LAMBDA,PHI                          INPUT
C     PS(3)     1/P,Y',Z'                              OUTPUT
C     H(3)      MAGNETIC FIELD                          INPUT
C     RC(15)    ERROR MATRIX IN   SC   VARIABLES        INPUT     (TRIANGLE)
C     RS(15)    ERROR MATRIX IN SPLINE VARIABLES       OUTPUT     (TRIANGLE)
C     CH        CHARGE OF PARTICLE                      INPUT
C               CHARGE AND MAGNETIC FIELD ARE NEEDED
C               FOR CORRELATION TERMS (Y',YT),(Y',ZT),(Z',YT),(Z',ZT)
C               THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
C               TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
C               AND RS FOR FIXED X
C
C     IERR  =   1       PARTICLE MOVES PERPENDICULAR TO X-AXIS
C                      ( Y',Z' ARE NOT DEFINED )
C     SPX       SIGN OF X-COMPONENT OF PARTICLE MOMENTUM   OUTPUT
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL   PC,PS,H,RC,RS,CH,SPX
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
      DIMENSION PC(3),PS(3),H(3),RC(15),RS(15)
      DIMENSION UN(3),VN(3)
C
      DATA CFACT8 / 2.997925 D-4 /
C
      IERR=0
      PM=PC(1)
      COSL=COS(PC(2))
      SINP=SIN(PC(3))
      COSP=COS(PC(3))
C
      TN(1)=COSL*COSP
      SPX=1.
      IF(TN(1).LT.0.) SPX=-1.
      IF(TN(1).EQ.0.) GO TO 901
      TN(2)=COSL*SINP
      TN(3)=SIN(PC(2))
C
      T1R=1./TN(1)
      PS(1)=PC(1)
      PS(2)=SINP/COSP
      PS(3)=TN(3)*T1R
C
      UN(1)=-SINP
      UN(2)=COSP
C
      VN(1)=-TN(3)*UN(2)
      VN(2)=TN(3)*UN(1)
      VN(3)=COSL
C
      J=0
      DO 10 I=1,5
         DO 5 K=I,5
            J=J+1
            A(I,K)=0.
            A(K,I)=0.
            S(J)=RC(J)
    5    CONTINUE
   10 CONTINUE
C
      IF(CH.EQ.0.) GO TO 6
      HA=SQRT(H(1)**2+H(2)**2+H(3)**2)
      HAM=HA*PM
      IF(HAM.EQ.0.) GO TO 6
      HM=CH/HA
      Q=-HAM*CFACT8
C
C
      SINZ=-(H(1)*UN(1)+H(2)*UN(2)           )*HM
      COSZ= (H(1)*VN(1)+H(2)*VN(2)+H(3)*VN(3))*HM
 
      T3R=Q*T1R**3
      A(2,4)=-UN(1)*(VN(3)*COSZ           )*T3R
      A(2,5)=-VN(1)*(VN(3)*COSZ           )*T3R
      A(3,4)=UN(1)*(VN(2)*COSZ-UN(2)*SINZ)*T3R
      A(3,5)=VN(1)*(VN(2)*COSZ-UN(2)*SINZ)*T3R
C
    6 T2R=T1R**2
C
      A(1,1)=1.
      A(2,3)=VN(3)*COSL*T2R
      A(3,2)=UN(2)*T2R
      A(3,3)=-VN(2)*COSL*T2R
      A(4,4)=VN(3)*T1R
      A(5,4)=-VN(2)*T1R
      A(5,5)=UN(2)*T1R
C
      CALL SSMT5T(A,S,S)
C
      J=0
      DO 25 I=1,5
         DO 20 K=I,5
            J=J+1
            RS(J)=S(J)
   20    CONTINUE
   25 CONTINUE
C
      RETURN
C
C *** ERROR EXITS
C
  901 IERR=1
  910 CONTINUE
C
      RETURN
      END
 
*CMZ :  1.40/05 14/11/97  16.33.57  by  Pavel Nevski
*CMZ :  1.00/00 19/03/92  12.19.31  by  Federico Carminati
*-- Author :
C
      SUBROUTINE TRSPSC(PS,RS,PC,RC,H,CH,IERR,SPX)
C
C *** TRANSFORMS ERROR MATRIX
C     FROM SPLINE VARIABLES (1/P,Y',Z',Y,Z)
C      TO    SC   VARIABLES (1/P,LAMBDA,PHI,YT,ZT)
C
C     Authors: A. Haas and W. Wittek
C
C
C *** PS(3)     1/P,Y',Z'                               INPUT
C     PC(3)     1/P,LAMBDA,PHI                         OUTPUT
C     H(3)      MAGNETIC FIELD                          INPUT
C     RS(15)    ERROR MATRIX IN SPLINE VARIABLES        INPUT      (TRIANGLE)
C     RC(15)    ERROR MATRIX IN   SC   VARIABLES       OUTPUT      (TRIANGLE)
C     CH        CHARGE OF PARTICLE                      INPUT
C               CHARGE AND MAGNETIC FIELD ARE NEEDED
C               FOR CORRELATION TERMS (LAMBDA,Y),(LAMBDA,Z),(PHI,Y),(PHI,Z)
C               THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
C               TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
C               AND RS FOR FIXED X
C
C     IERR              NOT USED
C     SPX       SIGN OF X-COMPONENT OF PARTICLE MOMENTUM    INPUT
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL   PS,PC,H,RC,RS,CH,SPX
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
      DIMENSION PS(3),PC(3),H(3),RC(15),RS(15)
      DIMENSION UN(3),VN(3)
C
      DATA CFACT8 / 2.997925 D-4 /
C
      IERR=0
      PM=PS(1)
      TN(1)=1./SQRT(1.+PS(2)**2+PS(3)**2)
      IF(SPX.LT.0.) TN(1)=-TN(1)
      TN(2)=PS(2)*TN(1)
      TN(3)=PS(3)*TN(1)
C
      PC(1)=PS(1)
      PC(2)=ASIN(TN(3))
      IF (ABS (TN(1)) .LT. 1.E-30) TN(1) = 1.E-30
      PC(3) = ATAN2 (TN(2),TN(1))
C
      COSL=SQRT(ABS(1.-TN(3)**2))
      IF (COSL .LT. 1.E-30) COSL = 1.E-30
      COSL1=1./COSL
      UN(1)=-TN(2)*COSL1
      UN(2)=TN(1)*COSL1
C
      VN(1)=-TN(3)*UN(2)
      VN(2)=TN(3)*UN(1)
      VN(3)=COSL
C
      J=0
      DO 10 I=1,5
         DO 4 K=I,5
            J=J+1
            A(I,K)=0.
            A(K,I)=0.
            S(J)=RS(J)
    4    CONTINUE
   10 CONTINUE
C
      IF(CH.EQ.0.) GO TO 6
 
      HA=SQRT(H(1)**2+H(2)**2+H(3)**2)
      HAM=HA*PM
      IF(HAM.EQ.0.) GO TO 6
      HM=CH/HA
C
      Q=-HAM*CFACT8
C
      SINZ=-(H(1)*UN(1)+H(2)*UN(2)           )*HM
      COSZ= (H(1)*VN(1)+H(2)*VN(2)+H(3)*VN(3))*HM
      A(2,4)=-Q*TN(2)*SINZ
      A(2,5)=-Q*TN(3)*SINZ
      A(3,4)=-Q*TN(2)*COSZ*COSL1
      A(3,5)=-Q*TN(3)*COSZ*COSL1
C
    6 A(1,1)=1.
      A(2,2)=TN(1)*VN(2)
      A(2,3)=TN(1)*VN(3)
      A(3,2)=TN(1)*UN(2)*COSL1
      A(4,4)=UN(2)
      A(5,4)=VN(2)
      A(5,5)=VN(3)
C
      CALL SSMT5T(A,S,S)
C
      J=0
      DO 25 I=1,5
         DO 20 K=I,5
            J=J+1
            RC(J)=S(J)
   20    CONTINUE
   25 CONTINUE
*
* *** ERROR EXITS
*
      END
 
*CMZ :  1.00/00 26/08/95  01.41.40  by  Pavel Nevski
*-- Author :
C
      SUBROUTINE TRSCSD(PC,RC,PD,RD,H,CH,IERR,SPU,DJ,DK)
C
C *** TRANSFORMS ERROR MATRIX
C     FROM   SC   VARIABLES (1/P,LAMBDA,PHI,YT,ZT)
C      TO         VARIABLES (1/P,V',W',V,W)
C
C     Authors: A. Haas and W. Wittek
C
C
C *** PC(3)     1/P,LAMBDA,PHI                          INPUT
C     PD(3)     1/P,V',W'                              OUTPUT
C     H(3)      MAGNETIC FIELD                          INPUT
C     RC(15)    ERROR MATRIX IN   SC   VARIABLES        INPUT     (TRIANGLE)
C     RD(15)    ERROR MATRIX IN 1/P,V',W',V,W          OUTPUT     (TRIANGLE)
C     CH        CHARGE OF PARTICLE                      INPUT
C               CHARGE AND MAGNETIC FIELD ARE NEEDED
C               FOR CORRELATION TERMS (V',YT),(V',ZT),(W',YT),(W',ZT)
C               THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
C               TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
C               AND RD FOR FIXED U
C     DJ(3)     UNIT VECTOR IN V-DIRECTION
C     DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM
C
C     IERR  =   1       PARTICLE MOVES PERPENDICULAR TO U-AXIS
C                      ( V',W' ARE NOT DEFINED )
C     SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM   OUTPUT
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL  PC,PD,H,RC,RD,CH,DJ,DK,SPU
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
      DIMENSION PC(3),PD(3),H(3),RC(15),RD(15),DJ(3),DK(3)
      DIMENSION UN(3),VN(3),DI(3),TVW(3)
C
      DATA CFACT8 / 2.997925 D-4 /
C
      IERR=0
      PM=PC(1)
      COSL=COS(PC(2))
      SINP=SIN(PC(3))
      COSP=COS(PC(3))
C
      TN(1)=COSL*COSP
      TN(2)=COSL*SINP
      TN(3)=SIN(PC(2))
C
      DI(1)=DJ(2)*DK(3)-DJ(3)*DK(2)
      DI(2)=DJ(3)*DK(1)-DJ(1)*DK(3)
      DI(3)=DJ(1)*DK(2)-DJ(2)*DK(1)
C
      TVW(1)=TN(1)*DI(1)+TN(2)*DI(2)+TN(3)*DI(3)
      SPU=1.
      IF(TVW(1).LT.0.) SPU=-1.
      TVW(2)=TN(1)*DJ(1)+TN(2)*DJ(2)+TN(3)*DJ(3)
      TVW(3)=TN(1)*DK(1)+TN(2)*DK(2)+TN(3)*DK(3)
      IF(TVW(1).EQ.0.) GO TO 901
C
      T1R=1./TVW(1)
      PD(1)=PC(1)
      PD(2)=TVW(2)*T1R
      PD(3)=TVW(3)*T1R
C
      UN(1)=-SINP
      UN(2)=COSP
      UN(3)=0.
C
      VN(1)=-TN(3)*UN(2)
      VN(2)=TN(3)*UN(1)
      VN(3)=COSL
C
      UJ=UN(1)*DJ(1)+UN(2)*DJ(2)+UN(3)*DJ(3)
      UK=UN(1)*DK(1)+UN(2)*DK(2)+UN(3)*DK(3)
      VJ=VN(1)*DJ(1)+VN(2)*DJ(2)+VN(3)*DJ(3)
      VK=VN(1)*DK(1)+VN(2)*DK(2)+VN(3)*DK(3)
C
C
      J=0
 
      DO 10 I=1,5
         DO 5 K=I,5
            J=J+1
            A(I,K)=0.
            A(K,I)=0.
            S(J)=RC(J)
    5    CONTINUE
   10 CONTINUE
C
      IF(CH.EQ.0.) GO TO 6
      HA=SQRT(H(1)**2+H(2)**2+H(3)**2)
      HAM=HA*PM
      IF(HAM.EQ.0.) GO TO 6
      HM=CH/HA
      Q=-HAM*CFACT8
C
C
      SINZ=-(H(1)*UN(1)+H(2)*UN(2)+H(3)*UN(3))*HM
      COSZ= (H(1)*VN(1)+H(2)*VN(2)+H(3)*VN(3))*HM
      T3R=Q*T1R**3
      UI=UN(1)*DI(1)+UN(2)*DI(2)+UN(3)*DI(3)
      VI=VN(1)*DI(1)+VN(2)*DI(2)+VN(3)*DI(3)
      A(2,4)=-UI*(VK*COSZ-UK*SINZ)*T3R
      A(2,5)=-VI*(VK*COSZ-UK*SINZ)*T3R
      A(3,4)= UI*(VJ*COSZ-UJ*SINZ)*T3R
      A(3,5)= VI*(VJ*COSZ-UJ*SINZ)*T3R
C
    6 T2R=T1R**2
C
      A(1,1)=1.
      A(2,2)=-UK*T2R
      A(2,3)=VK*COSL*T2R
      A(3,2)=UJ*T2R
      A(3,3)=-VJ*COSL*T2R
      A(4,4)=VK*T1R
      A(4,5)=-UK*T1R
      A(5,4)=-VJ*T1R
      A(5,5)=UJ*T1R
C
      CALL SSMT5T(A,S,S)
C
      J=0
      DO 25 I=1,5
         DO 20 K=I,5
            J=J+1
            RD(J)=S(J)
   20    CONTINUE
   25 CONTINUE
C
      RETURN
C
C *** ERROR EXITS
C
  901 IERR=1
  910 CONTINUE
C
      RETURN
      END
*
*CMZ :  1.00/00 07/10/95  13.25.14  by  Pavel Nevski
*-- Author :   A. Haas and W. Wittek
C
      SUBROUTINE TRSDSC(PD,RD,PC,RC,H,CH,IERR,SPU,DJ,DK)
C
C *** TRANSFORMS ERROR MATRIX
C     FROM        VARIABLES (1/P,V',W',V,W)
C      TO    SC   VARIABLES (1/P,LAMBDA,PHI,YT,ZT)
C
C     Authors: A. Haas and W. Wittek
C
C
C *** PD(3)     1/P,V',W'                               INPUT
C     PC(3)     1/P,LAMBDA,PHI                         OUTPUT
C     H(3)      MAGNETIC FIELD                          INPUT
C     RD(15)    ERROR MATRIX IN 1/P,V',W',V,W           INPUT      (TRIANGLE)
C     RC(15)    ERROR MATRIX IN   SC   VARIABLES       OUTPUT      (TRIANGLE)
C     CH        CHARGE OF PARTICLE                      INPUT
C               CHARGE AND MAGNETIC FIELD ARE NEEDED
C               FOR CORRELATION TERMS (LAMBDA,V),(LAMBDA,W),(PHI,V),(PHI,W)
C               THESE CORRELATION TERMS APPEAR BECAUSE RC IS ASSUMED
C               TO BE THE ERROR MATRIX FOR FIXED S (PATH LENGTH)
C               AND RD FOR FIXED U
C     DJ(3)     UNIT VECTOR IN V-DIRECTION
C     DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM
C
C     IERR              NOT USED
C     SPU       SIGN OF U-COMPONENT OF PARTICLE MOMENTUM    INPUT
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      REAL   PD,PC,H,RC,RD,CH,DJ,DK,SPU
*KEEP,TRCOM3.
      DOUBLE PRECISION A, B, S, TN, T, COSL, SINL, COSP, SINP, COSL1
      INTEGER          NEW
      COMMON /TRCOM3/ A(5,5), B(5,5), S(15),
     +                TN(3), T(5), COSL, SINL, COSP, SINP, COSL1, NEW
*     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*KEND.
      DIMENSION PD(3),PC(3),H(3),RC(15),RD(15),DJ(3),DK(3)
      DIMENSION UN(3),VN(3),DI(3),TVW(3)
C
      DATA CFACT8 / 2.997925 D-4 /
C
      IERR=0
      PM=PD(1)
      TVW(1)=1./SQRT(1.+PD(2)**2+PD(3)**2)
      IF(SPU.LT.0.) TVW(1)=-TVW(1)
      TVW(2)=PD(2)*TVW(1)
      TVW(3)=PD(3)*TVW(1)
C
      DI(1)=DJ(2)*DK(3)-DJ(3)*DK(2)
      DI(2)=DJ(3)*DK(1)-DJ(1)*DK(3)
      DI(3)=DJ(1)*DK(2)-DJ(2)*DK(1)
C
      DO 5 I=1,3
         TN(I)=TVW(1)*DI(I)+TVW(2)*DJ(I)+TVW(3)*DK(I)
    5 CONTINUE
C
      PC(1)=PD(1)
      PC(2)=ASIN(TN(3))
      IF (ABS (TN(1)) .LT. 1.E-30) TN(1) = 1.E-30
      PC(3) = ATAN2 (TN(2),TN(1))
C
      COSL=SQRT(ABS(1.-TN(3)**2))
      IF (COSL .LT. 1.E-30) COSL = 1.E-30
      COSL1=1./COSL
      UN(1)=-TN(2)*COSL1
      UN(2)=TN(1)*COSL1
      UN(3)=0.
C
      VN(1)=-TN(3)*UN(2)
      VN(2)=TN(3)*UN(1)
      VN(3)=COSL
 
C
      UJ=UN(1)*DJ(1)+UN(2)*DJ(2)+UN(3)*DJ(3)
      UK=UN(1)*DK(1)+UN(2)*DK(2)+UN(3)*DK(3)
      VJ=VN(1)*DJ(1)+VN(2)*DJ(2)+VN(3)*DJ(3)
      VK=VN(1)*DK(1)+VN(2)*DK(2)+VN(3)*DK(3)
C
      J=0
      DO 10 I=1,5
         DO 4 K=I,5
            J=J+1
            A(I,K)=0.
            A(K,I)=0.
            S(J)=RD(J)
    4    CONTINUE
   10 CONTINUE
C
      IF(CH.EQ.0.) GO TO 6
      HA=SQRT(H(1)**2+H(2)**2+H(3)**2)
      HAM=HA*PM
      IF(HAM.EQ.0.) GO TO 6
      HM=CH/HA
C
      Q=-HAM*CFACT8
C
      SINZ=-(H(1)*UN(1)+H(2)*UN(2)+H(3)*UN(3))*HM
      COSZ= (H(1)*VN(1)+H(2)*VN(2)+H(3)*VN(3))*HM
      A(2,4)=-Q*TVW(2)*SINZ
      A(2,5)=-Q*TVW(3)*SINZ
      A(3,4)=-Q*TVW(2)*COSZ*COSL1
      A(3,5)=-Q*TVW(3)*COSZ*COSL1
C
    6 A(1,1)=1.
      A(2,2)=TVW(1)*VJ
      A(2,3)=TVW(1)*VK
      A(3,2)=TVW(1)*UJ*COSL1
      A(3,3)=TVW(1)*UK*COSL1
      A(4,4)=UJ
      A(4,5)=UK
      A(5,4)=VJ
      A(5,5)=VK
C
      CALL SSMT5T(A,S,S)
C
      J=0
      DO 25 I=1,5
         DO 20 K=I,5
            J=J+1
            RC(J)=S(J)
   20    CONTINUE
   25 CONTINUE
C
      RETURN
C
C *** ERROR EXITS
C
      END
 
*CMZ :  1.00/00 19/03/92  12.19.31  by  Federico Carminati
*-- Author :
      SUBROUTINE SSMT5T(A,S,R)
C *** ------------------------------------------------------            05/07/81
C *** TRANSFORMATION OF SYMMETRIC 5X5 MATRIX S: A*S*AT -> R.
C *** A IS A GENERAL 5X5 MATRIX WHEREAS S,R ARE SYMMETRIC
C *** MATRICES STORED IN TRIANGULAR FORM. FOR:I,J=1,5
C *** R(I,J) = SUM:K=1,5(SUM:L=1,5(A(I,L)*S(L,K)*A(J,K))).
C *** NB: S AND R MAY WELL BE THE SAME MATRIX.
C
C        Author: A. Haas (Freiburg University)
C
C *** ------------------------------------------------------
      DOUBLE PRECISION A,S,R,Q,T1,T2,T3,T4,T5
      DIMENSION A(25),S(15),R(15),Q(15)
      DO 5 I=1,15
         Q(I)=S(I)
    5 CONTINUE
      K=1
      DO 15 J=1,5
         T1=A(J   )
         T2=A(J+ 5)
         T3=A(J+10)
         T4=A(J+15)
         T5=A(J+20)
         DO 10 I=J,5
            R(K)=A(I   )*(Q(1)*T1+Q(2)*T2+Q( 3)*T3+Q( 4)*T4+Q( 5)*T5)
     +          +A(I+ 5)*(Q(2)*T1+Q(6)*T2+Q( 7)*T3+Q( 8)*T4+Q( 9)*T5)
     +          +A(I+10)*(Q(3)*T1+Q(7)*T2+Q(10)*T3+Q(11)*T4+Q(12)*T5)
     +          +A(I+15)*(Q(4)*T1+Q(8)*T2+Q(11)*T3+Q(13)*T4+Q(14)*T5)
     +          +A(I+20)*(Q(5)*T1+Q(9)*T2+Q(12)*T3+Q(14)*T4+Q(15)*T5)
            K=K+1
   10    CONTINUE
   15 CONTINUE
*
      END
 
*CMZ :  1.00/00 19/03/92  12.19.31  by  Federico Carminati
*-- Author :
      SUBROUTINE XMM55(A,B,C)
C *** ---------------------------------------------                     05/07/81
C *** MULTIPLICATION OF 5X5 MATRICES: A*B -> C.
C *** FOR:I,J=1,5   C(I,J)=SUM:K=1,5(A(I,K)B(K,J))
C *** NB: B AND C MAY WELL BE THE SAME MATRIX
C
C        Author: A. Haas (Freiburg University)
C
C *** ---------------------------------------------
      DOUBLE PRECISION A,B,C,B1J,B2J,B3J,B4J,B5J
      DIMENSION A(25),B(25),C(25)
      DO 10 J5=5,25,5
         B5J=B(J5)
         J4=J5-1
         B4J=B(J4)
         J3=J4-1
         B3J=B(J3)
         J2=J3-1
         B2J=B(J2)
         J1=J2-1
         B1J=B(J1)
         C(J1)=A( 1)*B1J+A( 6)*B2J+A(11)*B3J+A(16)*B4J+A(21)*B5J
         C(J2)=A( 2)*B1J+A( 7)*B2J+A(12)*B3J+A(17)*B4J+A(22)*B5J
         C(J3)=A( 3)*B1J+A( 8)*B2J+A(13)*B3J+A(18)*B4J+A(23)*B5J
         C(J4)=A( 4)*B1J+A( 9)*B2J+A(14)*B3J+A(19)*B4J+A(24)*B5J
         C(J5)=A( 5)*B1J+A(10)*B2J+A(15)*B3J+A(20)*B4J+A(25)*B5J
   10 CONTINUE
*
      END
*CMZ :  1.40/05 07/12/97  17.29.02  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.19  by  S.Giani
*-- Author :
      SUBROUTINE GZEBRA(NZEB)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Routine to initialise ZEBRA store (//)                   *
C.    *                                                                *
C.    *    ==>Called by : <USER>                                       *
C.    *       Author    R.Brun  *********                              *
C.    *                                                                *
C.    *       Modifications:                                           *
C.    *   PN: Ellastic zebra inspired by V.Perevozchikov               *
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
*KEND.
       INTEGER I1,I2,Itry,LL,KWW,memget,LOCF,NZEB
C.
C.    ------------------------------------------------------------------
C.
       NZEBRA = abs(NZEB)
       NZEBRA = max(NZEBRA,1000000)
       I1     = LOCF   (IQ)
       Do iTry=0,5
          I2  = memget (NZEBRA*4+1000)/4
          If (I2.GT.I1) GO TO 11
          NZEBRA = NZEBRA/2
          PRINT *,'* GZEBRA: requested memory size reduced to ',
     >               Nzebra,' *'
       enddo
       PRINT *,' iTRY,NZEBRA,I1,I2 =', iTRY,NZEBRA,I1,I2
       STOP    ' GZEBRA: FATAL - CAN NOT ALLOCATE MEMORY '
C
  11   LL     = max    (I2-I1,0)
       NZEBRA = LL + NZEBRA
       KWW    = LL + 100
C
       CALL MZSTOR (IXSTOR,'/GCBANK/',' ',FENDQ,LQ,LR1,WS,
     >                                    LQ(KWW+100),LQ(NZEBRA-100))
       IF (IDEBUG.GE.3) CALL MZLOGL(IXSTOR,0)
       I1     = KWBANK
       CALL MZWORK (IXSTOR,LQ(I1),LQ(KWW),5)
       CALL GWORK  (KWBANK-100)
C
      END
 
 
 
 
 
*CMZ :  1.40/05 06/12/97  17.19.33  by  Pavel Nevski
*CMZ :  3.21/02 06/07/94  18.26.03  by  S.Giani
*-- Author :
      SUBROUTINE GFINDS
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Returns the set/volume parameters corresponding to       *
C.    *       the current space point in /GCTRAK/                      *
C.    *       and fill common /GCSETS/                                 *
C.    *                                                                *
C.    *       IHSET  user set identifier                               *
C.    *       IHDET  user detector identifier                          *
C.    *       ISET set number in JSET                                  *
C.    *       IDET   detector number in JS=LQ(JSET-ISET)               *
C.    *       IDTYPE detector type (1,2)                               *
C.    *       NUMBV  detector volume numbers (array of length NVNAME)  *
C.    *       NVNAME number of volume levels                           *
C.    *                                                                *
C.    *    ==>Called by : GTRACK                                       *
C.    *       Author    R.Brun  *********                              *
C.    *       Modified  V.Perev                                        *
C.    *       Jattf corrected by Bagdan Pavlik (Cracow)                *
C.    ******************************************************************
C.
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
*KEEP,GCSETS.
      COMMON/GCSETS/IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV(20)
C
      INTEGER       IHSET,IHDET,ISET,IDET,IDTYPE,NVNAME,NUMBV
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
*KEND.
      JATTF(JV) = JV + Nint(Q(JV+5)) + 6
C.
C.    ------------------------------------------------------------------
C.
*
*
      IHSET = 0
      IHDET = 0
      ISET  = 0
      IDET  = 0
      IDTYPE = 0
      NVNAME = 0
*
      DO 10 NLEV = NLEVEL,1,-1
         JVO = LQ(JVOLUM-LVOLUM(NLEV))
         JAT = JATTF(JVO)
         IDET = Q(JAT+8)
         IF(IDET.NE.0) THEN
            NL = NLEV
            GO TO 15
         ENDIF
  10  CONTINUE
      GOTO 99
  15  ISET   = Q(JAT+7)
      IDTYPE = Q(JAT+9)
      IHSET  = IQ(JSET+ISET)
      JS     = LQ(JSET-ISET)
      IHDET  = IQ(JS+IDET)
      JD     = LQ(JS-IDET)
      NVNAME = IQ(JD+2)
      DO 40 I=1,NVNAME
            NAME=IQ(JD+2*I+9)
            NUMBV(I)=0
            DO 30 J=1,NLEVEL
               IF(NAMES(J).EQ.NAME)THEN
                  NUMBV(I)=NUMBER(J)
                  GO TO 40
               ENDIF
  30        CONTINUE
  40  CONTINUE
C
   99 END
*CMZ :  1.40/05 29/01/98  13.12.38  by  Pavel Nevski
*CMZ :  3.21/02 19/05/94  13.35.12  by  S.Ravndal
*-- Author :
      SUBROUTINE FLUFIN
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
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
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
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
*KEEP,GSECTI.
      COMMON/GSECTI/ AIEL(20),AIIN(20),AIFI(20),AICA(20),ALAM,K0FLAG
      INTEGER K0FLAG
      REAL AIEL,AIIN,AIFI,AICA,ALAM
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
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEEP,GFKDIS.
      COMMON/ GFKDIS/ ZINE, ZELA, ZTOT, INT
     +               ,SINE, SELA, FSIG, IFMAT, IGF
C
C
*KEND.
*CDE,DIMPAR,FINUCT,PART2T,COMCONT,FHEAVYT,PAPROPT
*CDE,       FINUC, PART2, COMCON, FHEAVY, PAPROP
*KEEP,DIMPAR.
*                                                                     *
*=== dimpar ==========================================================*
*                                                                     *
*---------------------------------------------------------------------*
*                                                                     *
*      DIMPAR: included in any routine                                *
*                                                                     *
*          Mxxrgn = maximum number of regions                         *
*          Mxxmdf = maximum number of media in Fluka                  *
*          Mxxmde = maximum number of media in Emf                    *
*          Mfstck = stack dimension in Fluka                          *
*          Mestck = stack dimension in Emf                            *
*          Nallwp = number of allowed particles                       *
*          Mpdpdx = number of particle types for which EM dE/dx pro-  *
*                   cesses (ion,pair,bremss) have to be computed      *
*          Icomax = maximum number of materials for compounds (equal  *
*                   to the sum of the number of materials for every   *
*                   compound )                                        *
*          Nstbis = number of stable isotopes recorded in common iso- *
*                   top                                               *
*                                                                     *
*---------------------------------------------------------------------*
*                                                                     *
      PARAMETER ( MXXRGN = 500  )
      PARAMETER ( MXXMDF = 50   )
      PARAMETER ( MXXMDE = 18   )
      PARAMETER ( MFSTCK = 1000 )
      PARAMETER ( MESTCK = 100  )
      PARAMETER ( NALLWP = 39   )
      PARAMETER ( MPDPDX = 8    )
      PARAMETER ( ICOMAX = 120  )
      PARAMETER ( NSTBIS = 304  )
 
*KEEP,FINUCT.
      DOUBLE PRECISION CXR, CYR, CZR, TKI, PLR, WEI, TV, TVCMS,
     &                 TVRECL, TVHEAV, TVBIND
 
*KEEP,FINUC.
*
*=== finuc ============================================================*
*
*----------------------------------------------------------------------*
*     Last change on 5 april 1990     by Alfredo Ferrari, INFN Milan   *
*     include file: finuc copy                   created 26/11/86 by pa*
*     note: if changed change finuc2 copy also                         *
*     changes: none                                                    *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /finuc/ is the storage for secondaries created in event          *
*        np        = number of secondaries                             *
*        kpart(ip) = type of the secondary ip                          *
*        cxr(ip)   = direction cosine of the secondary ip              *
*                    with respect to x-axis                            *
*        cyr(ip)   = direction cosine of the secondary ip              *
*                    with respect to y-axis                            *
*        czr(ip)   = direction cosine of the secondary ip              *
*                    with respect to z-axis                            *
*        tki(ip)   = kinetic energy of secondary ip                    *
*        plr(ip)   = momentum of the secondary ip                      *
*        wei(ip)   = weight of the secondary ip                        *
*        tv        = excitation energy                                 *
*        tvcms     = actual excitation energy of the residual nucleus  *
*        tvrecl    = recoil kinetic energy of the residual nucleus     *
*        tvheav    = recoil kinetic energies of heavy (2-H, 3-H, 3-He, *
*                    4-He) fragments after evaporation                 *
*        tvbind    = approximate energy wasted in nuclear binding      *
*                    effects
*----------------------------------------------------------------------*
*
      PARAMETER (MXP=999)
      COMMON / FKFINU / CXR (MXP), CYR (MXP), CZR (MXP), TKI (MXP),
     &                 PLR (MXP), WEI (MXP), TV, TVCMS, TVRECL, TVHEAV,
     &                 TVBIND, NP0, NP, KPART (MXP)
 
      REAL RNDM(1)
      DOUBLE PRECISION AOCMBM, AMSS , ZTAR, RHO , ZLIN, ZLEL, ZLRAD,
     +ZUL
      COMMON / FKMAPA / AOCMBM (MXXMDF), AMSS (MXXMDF), ZTAR   (MXXMDF),
     +                  RHO    (MXXMDF), ZLIN (MXXMDF), ZLEL   (MXXMDF),
     +                  ZLRAD  (MXXMDF), ZUL  (MXXMDF), MEDIUM (MXXRGN),
     +                  MULFLG (MXXMDF),IFCOMP(MXXMDF), MSSNUM (MXXMDF),
     +                  NREGS, NMATF, MTBSNM
*KEEP,PART2T.
      DOUBLE PRECISION AAM, GA, TAU, AAMDSC
 
*KEEP,PART2.
*
*=== part2 ============================================================*
*
*----------------------------------------------------------------------*
*     Include file: part2 copy        Revised on 20-7-90 by A. Ferrari *
*     Note: see also part copy and part3 copy                          *
*     Changes: none                                                    *
*     Included in the following subroutines or functions: not updated  *
*                                                                      *
*     Description of the common block(s) and variable(s)               *
*                                                                      *
*         Kptoip = conversion from part to paprop numbering            *
*         Iptokp = conversion from paprop to part numbering            *
*                                                                      *
*----------------------------------------------------------------------*
*
      PARAMETER (IDMAX8=183)
      CHARACTER*8  ANAME
      COMMON / FKPART / AAM  (IDMAX8), GA     (IDMAX8), TAU    (IDMAX8),
     &                AAMDSC (IDMAX8), IICH   (IDMAX8), IIBAR  (IDMAX8),
     &                K1     (IDMAX8), K2     (IDMAX8), KPTOIP (IDMAX8),
     &                IPTOKP (39)
      COMMON / FKCHPA / ANAME (IDMAX8)
 
*KEEP,COMCONT.
      DOUBLE PRECISION AOCMBC, CONTNT, SUMACN, CABINX, CABELX,
     &                 ANXNOR, ELXNOR, CONA13, SUMZMF
 
*KEEP,COMCON.
*
*=== comcon ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     include file: comcon copy                 created 26/11/86 by pa *
*                                                                      *
*     Last change  on  30-oct-92   by   Alfredo Ferrari, INFN - Milan  *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*                                                                      *
*     /comcon/ contains information about compounds                    *
*         icompl(imat) = number of materials in a compound             *
*         matnum(i)    = material numbers (compounds consist of the    *
*                        materials)                                    *
*         aocmbc(i)    = atomic densities in barn**-1 cm**-1           *
*                        (Atoms Over Cm times Barn for Compounds)      *
*         cona13(i)    = A^1/3 of the constituents                     *
*         sumzmf(i)    = cumulative z^2 for multiple scattering        *
*         contnt(i)    = partial densities                             *
*         sumacn(i)    = cumulative atom contents of the compounds     *
*         cabinx(i)    = cumulative at.cont.*inelastic cross section   *
*         cabelx(i)    = cumulative at.cont.*  elastic cross section   *
*         anxnor       = total inelastic cross section                 *
*         elxnor       = total   elastic cross section                 *
*----------------------------------------------------------------------*
*
      COMMON /FKCOMC/ AOCMBC (ICOMAX), CONA13 (ICOMAX), SUMZMF (ICOMAX),
     &                CONTNT (ICOMAX), SUMACN (ICOMAX), CABINX (ICOMAX),
     &                CABELX (ICOMAX), ANXNOR, ELXNOR,  ICOMPL (MXXMDF),
     &                MATNUM (ICOMAX)
 
*KEEP,FHEAVYT.
      DOUBLE PRECISION CXHEAV, CYHEAV, CZHEAV, TKHEAV, PHEAVY,
     &                 WHEAVY, AMHEAV
 
*KEEP,FHEAVY.
*
*=== fheavy ===========================================================*
*
*----------------------------------------------------------------------*
*     Last change on 9 March 1993     by Alfredo Ferrari, INFN Milan   *
*     include file: fheavy copy       created 5/4/90 by A. Ferrari     *
*     changes: none                                                    *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /fheavy/ is the storage for heavy secondaries created in the     *
*              nuclear evaporation                                     *
*        npheav     = number of secondaries                            *
*        kheavy(ip) = type of the secondary ip                         *
*                   ( 3 = deuteron, 4 = 3-H, 5 = 3-He, 6 = 4-He,       *
*                     7-12 = "Heavy" fragment specified by Ibheav and  *
*                     Icheav )                                         *
*        cxheav(ip) = direction cosine of the secondary ip             *
*                     with respect to x-axis                           *
*        cyheav(ip) = direction cosine of the secondary ip             *
*                     with respect to y-axis                           *
*        czheav(ip) = direction cosine of the secondary ip             *
*                     with respect to z-axis                           *
*        tkheav(ip) = kinetic energy of secondary ip                   *
*        pheavy(ip) = momentum of the secondary ip                     *
*        wheavy(ip) = weight of the secondary ip                       *
*        amheav(ip) = atomic masses of the six types of evaporated     *
*                     particles                                        *
*        anheav(kp) = name of the kp-type heavy particle               *
*        icheav(kp) = charge of the kp-type heavy particle             *
*        ibheav(kp) = mass number of the kp-type heavy particle        *
*   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   *
*   !!! There is now the possibility to produce up to 6 "heavy" !!!!   *
*   !!! fragments besides the residual nucleus recorded in      !!!!   *
*   !!! Resnuc: they are identified by indeces 7-12, of course  !!!!   *
*   !!! the corresponding physical properties (Z,A,m..) must be !!!!   *
*   !!! updated every time they are produced                    !!!!   *
*   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   *
*----------------------------------------------------------------------*
*
      PARAMETER ( MXHEAV = 100 )
      CHARACTER*8 ANHEAV
      COMMON / FKHEAV / CXHEAV (MXHEAV), CYHEAV (MXHEAV),
     &                  CZHEAV (MXHEAV), TKHEAV (MXHEAV),
     &                  PHEAVY (MXHEAV), WHEAVY (MXHEAV),
     &                  AMHEAV  ( 12 ) ,
     &                  KHEAVY (MXHEAV), ICHEAV  ( 12 ) ,
     &                  IBHEAV  ( 12 ) , NPHEAV
      COMMON / FKHEAC / ANHEAV  ( 12 )
 
*KEEP,PAPROP.
*
*=== paprop ===========================================================*
*
*----------------------------------------------------------------------*
*     include file: paprop copy                   created 26/11/86 by p*
*     changes: on  16 december 1992 by Alfredo Ferrari                 *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /paprop/ contains particle properties                            *
*        btype  = literal name of the particle                         *
*        am     = particle mass in gev                                 *
*        ichrge = electric charge of the particle                      *
*        iscore = explanations for the scored distribution             *
*        genpar = names of the generalized particles                   *
*        ijdisc = list of the particle types to be discarded           *
*        thalf  = half life of the particle in sec                     *
*        biasdc = decay biasing factors                                *
*        biasin = inelastic interaction biasing factors                *
*        lhadro = flag for hadrons                                     *
*        jspinp = particle spin (in units of 1/2)                      *
*        lbsdcy = logical flag for biased decay: if .true. the biasing *
*                 factor is used as an upper limit to the decay length *
*        lprbsd = logical flag for biased decay: if .true. the biasing *
*                 factor is applied only to primaries                  *
*        lprbsi = logical flag for inelastic interaction biasing: if   *
*                 .true. the biasing factor is applied only to prima-  *
*                 ries                                                 *
*                                                                      *
*----------------------------------------------------------------------*
*
      LOGICAL LHADRO, LBSDCY, LPRBSD, LPRBSI
      CHARACTER*8 BTYPE,GENPAR
      COMMON / FKPAPR / AM  (NALLWP), AMDISC (NALLWP), THALF  (NALLWP),
     &               BIASDC (NALLWP), BIASIN (NALLWP), ICHRGE (NALLWP),
     &               ISCORE     (10), IJDISC (NALLWP), LHADRO (NALLWP),
     &               JSPINP (NALLWP), LBSDCY (NALLWP), LPRBSD, LPRBSI
      COMMON / FKCHPR / BTYPE  (NALLWP), GENPAR (30)
 
*KEEP,PAPROPT.
      DOUBLE PRECISION AM, AMDISC, THALF,BIASDC, BIASIN
*KEND.
 
      DOUBLE PRECISION POO,EKE,TXI,TYI,TZI,AMM,WE,ONE,PGEANT,DMOD
      PARAMETER (ONE=1)
      DIMENSION IGTOFL(49),IFLTOG(39),IHVTOG(6),ZSAMP(50)
      DATA IGTOFL / 0, 0, 0, 0, 0, 0,23,13,14,12, 15,16, 8, 1, 2,19, 0,
     +17,21,22, 20, 34, 36, 38, 9,18, 31, 32, 33, 35, 37, 39, 17*0/
 
      DATA IFLTOG /14,15, 3, 2, 4, 4, 1,13,25, 5, 6,10, 8, 9,11,12,18,
     +26,16,21, 19,20, 7, 7*0, 27, 28, 29, 22, 30, 23, 31, 24, 32/
      DATA IHVTOG /13,14,45,46,49,47/
*
*KEEP,agchadr.
* sequence to let hadronic package produce more then MXGKIN secondaries
*     geant  message - NDONE positive
*     guhadr message - NREST positive
*
      INTEGER          NDONE,NREST
      COMMON /AGCHADR/ NDONE,NREST
 
*KEND.
*
C     geant  message - NDONE positive
C     guhadr message - NREST positive
*
      IF (NDONE.GT.0 .AND. NREST.GT.0)  GO TO 81
      NDONE  = 0
      NREST  = 0
      NP     = 0
      NPHEAV = 0
*
*    Stopped particles:
*    o Neutral particles are sent to GHSTOP
*    o pi+ and K+/K- are forced to decay
*    o pi-, antiprotons and antineutrons are sent to FLUKA
*      for annihilation (not here but later in this routine)
      IF ((IGF.EQ.1).OR.
     +      (GEKIN.EQ.0..AND.ITRTYP.EQ.3.AND.IPART.NE.25)) THEN
         CALL GHEISH
         IGF = 0
         GOTO 999
      ELSE IF (GEKIN.EQ.0..AND.
     +        (IPART.EQ.8.OR.IPART.EQ.12.OR.IPART.EQ.11)) THEN
         CALL GDECAY
         NMEC=NMEC+1
         LMEC(NMEC)=5
         ISTOP=1
         GOTO 999
      ENDIF
*
      IF (IFINIT(5) .EQ. 0) CALL FLINIT
      INT=0
      IJ=IGTOFL(IPART)
      IF(IJ.EQ.0) GOTO 110
      NMEC = NMEC + 1
      EKE = GEKIN
      TXI = VECT(4)
      TYI = VECT(5)
      TZI = VECT(6)
      DMOD = ONE/SQRT(TXI**2+TYI**2+TZI**2)
      TXI = TXI*DMOD
      TYI = TYI*DMOD
      TZI = TZI*DMOD
      WE  = 1.
      JMA = LQ(JMATE-NMAT)
      NCOMP = ABS (Q(JMA+11))
      AMM = Q(JMA+6)
      JMIXT = LQ(JMA-5)
 
*    Antiprotons, antineutrons and pi- are sent to
*    eventv for annihilation
      IF (GEKIN.EQ.0..AND.
     +         (IPART.EQ.15.OR.IPART.EQ.9.OR.IPART.EQ.25)) THEN
         IF(NCOMP.LE.1) THEN
            AMSS(1) = Q(JMA+6)
            ZTAR(1) = Q(JMA+7)
            MSSNUM(1) = 0
            RHO(1) = Q(JMA+8)
         ELSE
            ZSAMP(1) = 0.
            DO 10 I=1,NCOMP
               ZSAMP(I+1) = ZSAMP(I) + Q(JMIXT+NCOMP+I)
   10       CONTINUE
            CALL GRNDM(RNDM,1)
            ZCONT=ZSAMP(NCOMP+1)*RNDM(1)
            DO 20 I=1,NCOMP
               IF(ZCONT.LE.ZSAMP(I+1)) GO TO 30
   20       CONTINUE
            I = NCOMP
   30       CONTINUE
            AMSS(1)   = Q(JMIXT+I)
            MSSNUM(1) = 0
            ZTAR(1)   = Q(JMIXT+NCOMP+I)
            RHO(1)    = Q(JMIXT+2*NCOMP+I)*DENS
         END IF
         EKE = 1E-9
         POO=SQRT(EKE*(EKE+2*AM(IJ)))
         CALL EVENTV(IJ,POO,EKE,TXI,TYI,TZI,WE,1)
         GOTO 80
      ELSE IF (GEKIN.LE.CUTHAD .AND. ITRTYP.EQ.4) THEN
         DESTEP = DESTEP + GEKIN
         GEKIN  = 0.
         GETOT  = AMASS
         VECT(7) = 0.
         ISTOP = 1
         LMEC(NMEC)=30
         GO TO 110
      ENDIF
*
      CALL GRNDM(RNDM,1)
      RNDEVT=RNDM(1)
      IF ( RNDEVT .GE. SINE/FSIG) THEN
 
         IF (GEKIN .GT. 0.02) THEN
            POO=SQRT(EKE*(EKE+2*AM(IJ)))
         ELSE
            GO TO 110
         END IF
         INT=1
         LMEC(NMEC)=13
         IF(NCOMP.LE.1) THEN
            CALL NUCREL(IJ,POO,EKE,TXI,TYI,TZI,AMM,WE)
         ELSE
            CALL GRNDM(RNDM,1)
            RCONT=ELXNOR*RNDM(1)
            DO 40  I=1,NCOMP
               IF(RCONT.LE.CABELX(I)) GO TO 50
   40       CONTINUE
            I=NCOMP
   50       CONTINUE
            CALL NUCREL(IJ,POO,EKE,TXI,TYI,TZI,ONE*Q(JMIXT+I),WE)
         END IF
      ELSE
         LMEC(NMEC)=20
         IF (IHADR.EQ.2) THEN
            ISTOP = 2
            DESTEP = DESTEP + GETOT
            GO TO 110
         ENDIF
         IF (GEKIN .GT. 0.02) THEN
            POO=SQRT(EKE*(EKE+2*AM(IJ)))
         ELSE
            IF ((IJ.EQ.2 .OR. IJ.EQ.9 .OR. IJ.EQ.14 .OR. IJ.EQ.16)
     +            .AND. GEKIN .GT. 0.0) THEN
               POO=SQRT(EKE*(EKE+2*AM(IJ)))
            ELSE
               NMEC=NMEC-1
               GO TO 110
            END IF
         END IF
         INT=2
         IF(NCOMP.LE.1) THEN
            AMSS(1) = Q(JMA+6)
            ZTAR(1) = Q(JMA+7)
            MSSNUM(1) = 0
            RHO(1) = Q(JMA+8)
         ELSE
            CALL GRNDM(RNDM,1)
            RCONT=ANXNOR*RNDM(1)
            DO 60  I=1,NCOMP
               IF(RCONT.LE.CABINX(I)) GO TO 70
   60       CONTINUE
            I=NCOMP
   70       CONTINUE
            AMSS(1)   = Q(JMIXT+I)
            MSSNUM(1) = 0
            ZTAR(1)   = Q(JMIXT+NCOMP+I)
            RHO(1)    = Q(JMIXT+2*NCOMP+I)*DENS
         END IF
         CALL EVENTV(IJ,POO,EKE,TXI,TYI,TZI,WE,1)
      END IF
*
   80 IF(NP.EQ.1.AND.NPHEAV.EQ.0.AND.KPART(1).EQ.IJ) THEN
         VECT(4)=CXR(1)
         VECT(5)=CYR(1)
         VECT(6)=CZR(1)
         VECT(7)=SQRT(TKI(1)*(TKI(1)+2*AMASS))
         GETOT=TKI(1)+AMASS
         GEKIN=TKI(1)
         GO TO 105
      ENDIF
*
      NREST = NP+NPHEAV
      NDONE = 0
*
   81    ISTOP=1
         NSTAK1 = MIN(MAX(0,NP-NDONE),MXGKIN-NGKINE)
         DO 90  K=NDONE+1,NDONE+NSTAK1
            NREST  = NREST  - 1
            NGKINE = NGKINE + 1
            IF (KPART(K) .EQ. 24 .OR. KPART(K) .EQ. 25) THEN
               KPART(K) = 19
               CALL GRNDM(RNDM,1)
               IF (RNDM(1) .GT. 0.5) KPART(K) = 12
            END IF
            IGEPAR = IFLTOG(KPART(K))
            JPA = LQ(JPART-IGEPAR)
            AGEMAS = Q(JPA+7)
            PGEANT = SQRT(TKI(K)*(TKI(K)+2*AGEMAS))
            GKIN(1,NGKINE)=CXR(K)*PGEANT
            GKIN(2,NGKINE)=CYR(K)*PGEANT
            GKIN(3,NGKINE)=CZR(K)*PGEANT
            GKIN(4,NGKINE)=TKI(K)+AGEMAS
            GKIN(5,NGKINE)=IGEPAR
            TOFD(NGKINE)=0.0
            GPOS(1,NGKINE) = VECT(1)
            GPOS(2,NGKINE) = VECT(2)
            GPOS(3,NGKINE) = VECT(3)
   90    CONTINUE
*
         NDONE2 = MAX(NDONE+NSTAK1-NP,0)
         NSTAK2 = MIN(MAX(0,NPHEAV-NDONE2),MXGKIN-NGKINE)
*
         DO 100 K=NDONE2+1,NDONE2+NSTAK2
            NREST  = NREST  - 1
            NGKINE = NGKINE + 1
            IGEPAR = IHVTOG(KHEAVY(K))
            JPA = LQ(JPART-IGEPAR)
            AGEMAS = Q(JPA+7)
            PGEANT = SQRT(TKHEAV(K)*(TKHEAV(K)+2*AGEMAS))
            GKIN(1,NGKINE)=CXHEAV(K)*PGEANT
            GKIN(2,NGKINE)=CYHEAV(K)*PGEANT
            GKIN(3,NGKINE)=CZHEAV(K)*PGEANT
            GKIN(4,NGKINE)=TKHEAV(K)+AGEMAS
            GKIN(5,NGKINE)=IGEPAR
            TOFD(NGKINE)=0.0
            GPOS(1,NGKINE) = VECT(1)
            GPOS(2,NGKINE) = VECT(2)
            GPOS(3,NGKINE) = VECT(3)
  100    CONTINUE
*
  105  KCASE=NAMEC(12)
 
  110 CONTINUE
      ZINTHA = GARNDM(DUMMY)
      SLHADR = SLENG
      STEPHA = 1.0E10
 
  999 END
 
*CMZ :  1.40/05 16/12/97  13.31.05  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.38  by  S.Giani
*-- Author :
      SUBROUTINE GHEISH
C
C *** MAIN STEERING FOR HADRON SHOWER DEVELOPMENT ***
C *** NVE 15-JUN-1988 CERN GENEVA ***
C
C CALLED BY : GUHADR (USER ROUTINE)
C ORIGIN : F.CARMINATI, H.FESEFELDT
C                       ROUTINES : CALIM  16-SEP-1987
C                                  SETRES 19-AUG-1985
C                                  INTACT 06-OCT-1987
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
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
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
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
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
*KEEP,GSECTI.
      COMMON/GSECTI/ AIEL(20),AIIN(20),AIFI(20),AICA(20),ALAM,K0FLAG
      INTEGER K0FLAG
      REAL AIEL,AIIN,AIFI,AICA,ALAM
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
C --- GHEISHA COMMONS ---
*KEEP,MXGKGH.
      PARAMETER (MXGKGH=100)
*KEEP,/BLANKP.
      PARAMETER (MXGKPV=MXGKGH)
      COMMON /VECUTY/ PV(10,MXGKPV)
C
*KEEP,/CONSTS.
      COMMON/CONSTS/ PI,TWPI,PIBTW,MP,MPI,MMU,MEL,MKCH,MK0,SMP,SMPI,
     $               SMU,CT,CTKCH,CTK0,
     $               ML0,MSP,MS0,MSM,MX0,MXM,CTL0,CTSP,CTSM,CTX0,CTXM,
     $               RMASS(35),RCHARG(35)
C
                     REAL MP,MPI,MMU,MEL,MKCH,MK0,
     *                    ML0,MSP,MS0,MSM,MX0,MXM
C
*KEEP,/EVENT.
      PARAMETER (MXEVEN=12*MXGKGH)
      COMMON/EVENT / NSIZE,NCUR,NEXT,NTOT,EVE(MXEVEN)
C
*KEEP,/PRNTFL.
      COMMON/PRNTFL/INBCD,NEWBCD,INBIN,NEWBIN,NPEVT,NEVTP,LPRT,NPRT(10)
                    LOGICAL LPRT,NPRT
C
*KEND.
C
C --- "NEVENT" CHANGED TO "KEVENT" IN COMMON /CURPAR/ DUE TO CLASH ---
C --- WITH VARIABLE "NEVENT" IN GEANT COMMON ---
C
      PARAMETER (MXGKCU=MXGKGH)
      COMMON /CURPAR /WEIGHT(10),DDELTN,IFILE,IRUN,NEVT,KEVENT,SHFLAG,
     $                ITHST,ITTOT,ITLST,IFRND,TOFCUT,CMOM(5),CENG(5),
     $                RS,S,ENP(10),NP,NM,NN,NR,NO,NZ,IPA(MXGKCU),
     $                ATNO2,ZNO2
C
C --- "IPART" CHANGED TO "KPART" IN COMMON /RESULT/ DUE TO CLASH ---
C --- WITH VARIABLE "IPART" IN GEANT COMMON ---
C
      COMMON /RESULT/ XEND,YEND,ZEND,RCA,RCE,AMAS,NCH,TOF,PX,PY,PZ,
     $                USERW,INTCT,P,EN,EK,AMASQ,DELTN,ITK,NTK,KPART,IND,
     $                LCALO,ICEL,SINL,COSL,SINP,COSP,
     $                XOLD,YOLD,ZOLD,POLD,PXOLD,PYOLD,PZOLD,
     $                XSCAT,YSCAT,ZSCAT,PSCAT,PXSCAT,PYSCAT,PZSCAT
                      REAL NCH,INTCT
C
C --- "ABSL(21)" CHANGED TO "ABSLTH(21)" IN COMMON /MAT/ DUE TO CLASH ---
C --- WITH VARIABLE "ABSL" IN GEANT COMMON ---
C
      COMMON /MAT/ LMAT,
     $             DEN(21),RADLTH(21),ATNO(21),ZNO(21),ABSLTH(21),
     $             CDEN(21),MDEN(21),X0DEN(21),X1DEN(21),RION(21),
     $             MATID(21),MATID1(21,24),PARMAT(21,10),
     $             IFRAT,IFRAC(21),FRAC1(21,10),DEN1(21,10),
     $             ATNO1(21,10),ZNO1(21,10)
C
      DIMENSION IPELOS(35)
      SAVE IDEOL
C
C --- TRANSFER GEANT CUT-OFFS INTO GHEISHA VALUES ---
      DIMENSION CUTS(5)
      EQUIVALENCE (CUTS(1),CUTGAM)
      DIMENSION RNDM(1)
C
*KEEP,PCODIM.
C --- DIMENSION STMTS. FOR GEANT/GHEISHA PARTICLE CODE CONVERSIONS ---
C --- KIPART(I)=GHEISHA CODE CORRESPONDING TO GEANT   CODE I ---
C --- IKPART(I)=GEANT   CODE CORRESPONDING TO GHEISHA CODE I ---
C
      DIMENSION KIPART(48),IKPART(35)
C
*KEEP,PCODAT.
C --- DATA STMTS. FOR GEANT/GHEISHA PARTICLE CODE CONVERSIONS ---
C --- KIPART(I)=GHEISHA CODE CORRESPONDING TO GEANT   CODE I ---
C --- IKPART(I)=GEANT   CODE CORRESPONDING TO GHEISHA CODE I ---
C
      DATA KIPART/
     $               1,   3,   4,   2,   5,   6,   8,   7,
     $               9,  12,  10,  13,  16,  14,  15,  11,
     $              35,  18,  20,  21,  22,  26,  27,  33,
     $              17,  19,  23,  24,  25,  28,  29,  34,
     $              35,  35,  35,  35,  35,  35,  35,  35,
     $              35,  35,  35,  35,  30,  31,  32,  35/
C
      DATA IKPART/
     $               1,   4,   2,   3,   5,   6,   8,   7,
     $               9,  11,  16,  10,  12,  14,  15,  13,
     $              25,  18,  26,  19,  20,  21,  27,  28,
     $              29,  22,  23,  30,  31,  45,  46,  47,
     $              24,  32,  48/
C
*KEND.
C
C --- DENOTE STABLE PARTICLES ACCORDING TO GHEISHA CODE ---
C --- STABLE : GAMMA, NEUTRINO, ELECTRON, PROTON AND HEAVY FRAGMENTS ---
C --- WHEN STOPPING THESE PARTICLES ONLY LOOSE THEIR KINETIC ENERGY ---
      DATA IPELOS/
     $             1,   1,   0,   1,   0,   0,   0,   0,
     $             0,   0,   0,   0,   0,   1,   0,   0,
     $             0,   0,   0,   0,   0,   0,   0,   0,
     $             0,   0,   0,   0,   0,   1,   1,   1,
     $             0,   0,   1/
C
C --- LOWERBOUND OF KINETIC ENERGY BIN IN N CROSS-SECTION TABLES ---
      DATA TEKLOW /0.0001/
C
C --- KINETIC ENERGY TO SWITCH FROM "CASN" TO "GNSLWD" FOR N CASCADE ---
      DATA SWTEKN /0.05/
C
      DATA IDEOL/0/
C
C --- INITIALIZE RELEVANT GHEISHA VARIABLES IN CASE NOT DONE ALREADY ---
      IF (IFINIT(4) .EQ. 0) CALL GHEINI
C
C --- SET THE INTERACTION MECHANISM TO "HADR" ---
      KCASE=NAMEC(12)
C
C --- SET GHEISHA PRINTING FLAGS ACCORDING TO "DEBUG" STEERING CARD --
      IF (IDEOL .EQ. IDEBUG) GO TO 9000
C
      IF (IDEBUG .NE. 1) GO TO 9001
C
C --- SET SELECTED DEBUGGING FLAGS ---
      DO 9002 LL=1,10
      IF ((ISWIT(LL) .LE. 100) .OR. (ISWIT(LL) .GT. 110)) GO TO 9002
      JJ=ISWIT(LL)-100
      NPRT(JJ)=.TRUE.
 9002 CONTINUE
      GO TO 9000
C
C --- NO DEBUGGING SELECTED ---
 9001 CONTINUE
      DO 9003 LL=1,10
      NPRT(LL)=.FALSE.
 9003 CONTINUE
      IDEOL=IDEBUG
C
 9000 CONTINUE
C
C --- SET THE GHEISHA PARTICLE TYPE TO THE ONE OF GEANT ---
      IF(IPART.GT.48) THEN
         IF(ISTOP.EQ.0) GOTO 9999
         JPA = LQ(JPART-IPART)
         AMAS=Q(JPA+7)
         NCH =Q(JPA+8)
         KPART=-IPART
         GOTO 107
      ENDIF
      NETEST=IKPART(KPART)
      IF ((NETEST .EQ. IPART) .OR. (ISTOP .NE. 0)) GO TO 9004
C
      PRINT 8881,IPART,KPART,ISTOP
 8881 FORMAT(' *GHEISH* IPART,KPART = ',2(I3,1X),' ISTOP = ',I3/
     $ ' *GHEISH* ======> PARTICLE TYPES DO NOT MATCH <=======')
      STOP
C
 9004 CONTINUE
      KPART=KIPART(IPART)
      KKPART=KPART
      AMAS=RMASS(KPART)
      NCH=RCHARG(KPART)
C
C --- TRANSPORT THE TRACK NUMBER TO GHEISHA AND INITIALISE SOME NUMBERS
 107  NTK=ITRA
      INTCT=0.0
      NEXT=1
      NTOT=0
      TOF=0.0
C
C --- FILL RESULT COMMON FOR THIS TRACK WITH GEANT VALUES ---
C --- CALIM CODE ---
      XEND=VECT(1)
      YEND=VECT(2)
      ZEND=VECT(3)
      PX=VECT(4)
      PY=VECT(5)
      PZ=VECT(6)
      USERW=UPWGHT
C --- SETRES CODE ---
      P=VECT(7)
      AMASQ=AMAS*AMAS
      EN=SQRT(AMASQ+P*P)
      EK=ABS(EN-ABS(AMAS))
      ENOLD=EN
C
      SINL=0.0
      COSL=1.0
      SINP=0.0
      COSP=1.0
C
      IF (ABS(P) .LE. 1.0E-10) GO TO 1
      SINL=PZ
      COSL=SQRT(ABS(1.0-SINL**2))
C
 1    CONTINUE
      CALL GRNDM(RNDM,1)
      PHI=RNDM(1)*TWPI
      IF ((PX .EQ. 0.0) .AND. (PY .EQ. 0.0)) GOTO 3
      IF (ABS(PX) .LT. 1.E-10) GOTO 2
      PHI=ATAN2(PY,PX)
      GOTO 3
C
 2    CONTINUE
      IF (PY .GT. 0.0) PHI=PI/2.0
      IF (PY .LE. 0.0) PHI=3.0*PI/2.0
C
 3    CONTINUE
      SINP=SIN(PHI)
      COSP=COS(PHI)
C
C --- SET GHEISHA INDEX FOR THE CURRENT MEDIUM ALWAYS TO 1 ---
      IND=1
C
C --- TRANSFER GLOBAL MATERIAL CONSTANTS FOR CURRENT MEDIUM ---
C --- DETAILED DATA FOR COMPOUNDS IS OBTAINED VIA ROUTINE COMPO ---
      ATNO(IND+1)=A
      ZNO(IND+1)=Z
      DEN(IND+1)=DENS
      RADLTH(IND+1)=RADL
      ABSLTH(IND+1)=ABSL
C
C --- SETUP PARMAT FOR PHYSICS STEERING ---
      PARMAT(IND+1,5)=0.0
      PARMAT(IND+1,8)=IPFIS
      PARMAT(IND+1,9)=0.0
      PARMAT(IND+1,10)=0.0
      JTMN=LQ(JTM)
      IF (JTMN .LE. 0) GO TO 4
      PARMAT(IND+1,5)=Q(JTMN+26)
 4    CONTINUE
C
C --- CHECK WHETHER PARTICLE IS STOPPING OR NOT ---
      IF (ISTOP .EQ. 0) GO TO 5
C
      IF (NPRT(9)) PRINT 1000,KPART
 1000 FORMAT(' *GHEISH* STOPPING GHEISHA PARTICLE ',I3)
      CALL GHSTOP
C --- IN CASE OF DECAY OF PARTICLE OR USER PARTICLE ==> RETURN ---
      IF (LMEC(NMEC) .EQ. 5 .OR. KPART .LT. 0) GO TO 9999
C --- IN CASE OF HAD. INT. WITH GENERATION OF SEC. ==> GO TO 40 ---
      IF (IHADR .NE. 2) GO TO 40
C --- ALSO DEPOSIT REST MASS ENERGY FOR IN-STABLE PARTICLES ---
      IF (IPELOS(KPART) .EQ. 0) DESTEP=DESTEP+ABS(RMASS(KPART))
      GO TO 9999
  5   CONTINUE
C
C --- INDICATE LIGHT (<= PI) AND HEAVY PARTICLES (HISTORICALLY) ---
C --- CALIM CODE ---
      J=2
      TEST=RMASS(7)-0.001
      IF (ABS(AMAS) .LT. TEST) J=1
C
C *** DIVISION INTO VARIOUS INTERACTION CHANNELS DENOTED BY "INT" ***
C THE CONVENTION FOR "INT" IS THE FOLLOWING
C
C INT  = -1 REACTION CROSS SECTIONS NOT YET TABULATED/PROGRAMMED
C      =  0 NO INTERACTION
C      =  1 ELEASTIC SCATTERING
C      =  2 INELASTIC SCATTERING
C      =  3 NUCLEAR FISSION WITH INELEASTIC SCATTERING
C      =  4 NEUTRON CAPTURE
C
C --- INTACT CODE ---
      KK=ABS(Q(JMA+11))
      ALAM1=0.0
      CALL GRNDM(RNDM,1)
      RAT=RNDM(1)*ALAM
      NMEC=NMEC+1
      ATNO2=A
      ZNO2 =Z
C
      DO 6 K=1,KK
      IF (KK .LE. 0) GO TO 6
C
      IF (KK .EQ. 1) GO TO 7
      ATNO2=Q(JMIXT+K)
      ZNO2 =Q(JMIXT+K+KK)
C
 7    CONTINUE
C
C --- TRY FOR ELASTIC SCATTERING ---
      INT=1
      LMEC(NMEC)=13
      ALAM1=ALAM1+AIEL(K)
      IF (RAT .LT. ALAM1) GO TO 8
C
C --- TRY FOR INELASTIC SCATTERING ---
      INT=2
      LMEC(NMEC)=20
      ALAM1=ALAM1+AIIN(K)
      IF (RAT .LT. ALAM1) GO TO 8
C
C --- TRY FOR NUCLEAR FISSION WITH INELASTIC SCATTERING ---
      INT=3
      LMEC(NMEC)=15
      ALAM1=ALAM1+AIFI(K)
      IF (RAT .LT. ALAM1) GO TO 8
C
C --- TRY FOR NEUTRON CAPTURE ---
      INT=4
      LMEC(NMEC)=18
      ALAM1=ALAM1+AICA(K)
      IF (RAT .LT. ALAM1) GO TO 8
C
 6    CONTINUE
C --- NO REACTION SELECTED ==> ELASTIC SCATTERING ---
      INT=1
      LMEC(NMEC)=13
C
C *** TAKE ACTION ACCORDING TO SELECTED REACTION CHANNEL ***
C --- FOLLOWING CODE IS A TRANSLATION OF "CALIM" INTO GEANT JARGON ---
C
 8    CONTINUE
      IF (NPRT(9)) PRINT 1001,INT
 1001 FORMAT(' *GHEISH* INTERACTION TYPE CHOSEN INT = ',I3)
C
C --- IN CASE OF NO INTERACTION OR UNKNOWN CROSS SECTIONS ==> DONE ---
      IF (INT .LE. 0) GO TO 40
C
C --- IN CASE OF NON-ELASTIC SCATTERING AND NO GENERATION OF SEC. ---
C --- PARTICLES DEPOSIT TOTAL PARTICLE ENERGY AND RETURN ---
      IF ((INT .EQ. 1) .OR. (IHADR .NE. 2)) GO TO 9
      ISTOP=2
      DESTEP=DESTEP+EN
      NGKINE=0
      GO TO 9999
C
 9    CONTINUE
      IF (INT .NE. 4) GO TO 10
C
C --- NEUTRON CAPTURE ---
      IF (NPRT(9)) PRINT 2000
 2000 FORMAT(' *GHEISH* ROUTINE CAPTUR WILL BE CALLED')
      ISTOP=1
      CALL CAPTUR(NOPT)
      GO TO 40
C
 10   CONTINUE
      IF (INT .NE. 3) GO TO 11
C --- NUCLEAR FISSION ---
      IF (NPRT(9)) PRINT 2001
 2001 FORMAT(' *GHEISH* ROUTINE FISSIO WILL BE CALLED')
      ISTOP=1
      TKIN=FISSIO(EK)
      GO TO 40
C
 11   CONTINUE
C
C --- ELASTIC AND INELASTIC SCATTERING ---
      PV( 1,MXGKPV)=P*PX
      PV( 2,MXGKPV)=P*PY
      PV( 3,MXGKPV)=P*PZ
      PV( 4,MXGKPV)=EN
      PV( 5,MXGKPV)=AMAS
      PV( 6,MXGKPV)=NCH
      PV( 7,MXGKPV)=TOF
      PV( 8,MXGKPV)=KPART
      PV( 9,MXGKPV)=0.
      PV(10,MXGKPV)=USERW
C
C --- ADDITIONAL PARAMETERS TO SIMULATE FERMI MOTION AND EVAPORATION ---
      DO 111 JENP=1,10
         ENP(JENP)=0.
 111  CONTINUE
      ENP(5)=EK
      ENP(6)=EN
      ENP(7)=P
C
      IF (INT .NE. 1) GO TO 12
C
C *** ELASTIC SCATTERING PROCESSES ***
C
C --- ONLY NUCLEAR INTERACTIONS FOR HEAVY FRAGMENTS ---
      IF ((KPART .GE. 30) .AND. (KPART .LE. 32)) GO TO 35
C
C --- NORMAL ELASTIC SCATTERING FOR LIGHT MEDIA ---
      IF (ATNO2 .LT. 1.5) GO TO 35
C
C --- COHERENT ELASTIC SCATTERING FOR HEAVY MEDIA ---
      IF (NPRT(9)) PRINT 2002
 2002 FORMAT(' *GHEISH* ROUTINE COSCAT WILL BE CALLED')
      CALL COSCAT
      GO TO 40
C
C *** NON-ELASTIC SCATTERING PROCESSES ***
 12   CONTINUE
C
C --- ONLY NUCLEAR INTERACTIONS FOR HEAVY FRAGMENTS ---
      IF ((KPART .GE. 30) .AND. (KPART .LE. 32)) GO TO 35
C
C *** USE SOMETIMES NUCLEAR REACTION ROUTINE "NUCREC" FOR LOW ENERGY ***
C *** PROTON AND NEUTRON SCATTERING ***
      CALL GRNDM(RNDM,1)
      TEST1=RNDM(1)
      TEST2=4.5*(EK-0.01)
      IF ((KPART .EQ. 14) .AND. (TEST1 .GT. TEST2)) GO TO 85
      IF ((KPART .EQ. 16) .AND. (TEST1 .GT. TEST2)) GO TO 86
C
C *** FERMI MOTION AND EVAPORATION ***
      TKIN=CINEMA(EK)
      PV( 9,MXGKPV)=TKIN
      ENP(5)=EK+TKIN
C --- CHECK FOR LOWERBOUND OF EKIN IN CROSS-SECTION TABLES ---
      IF (ENP(5) .LE. TEKLOW) ENP(5)=TEKLOW
      ENP(6)=ENP(5)+ABS(AMAS)
      ENP(7)=(ENP(6)-AMAS)*(ENP(6)+AMAS)
      ENP(7)=SQRT(ABS(ENP(7)))
      TKIN=FERMI(ENP(5))
      ENP(5)=ENP(5)+TKIN
C --- CHECK FOR LOWERBOUND OF EKIN IN CROSS-SECTION TABLES ---
      IF (ENP(5) .LE. TEKLOW) ENP(5)=TEKLOW
      ENP(6)=ENP(5)+ABS(AMAS)
      ENP(7)=(ENP(6)-AMAS)*(ENP(6)+AMAS)
      ENP(7)=SQRT(ABS(ENP(7)))
      TKIN=EXNU(ENP(5))
      ENP(5)=ENP(5)-TKIN
C --- CHECK FOR LOWERBOUND OF EKIN IN CROSS-SECTION TABLES ---
      IF (ENP(5) .LE. TEKLOW) ENP(5)=TEKLOW
      ENP(6)=ENP(5)+ABS(AMAS)
      ENP(7)=(ENP(6)-AMAS)*(ENP(6)+AMAS)
      ENP(7)=SQRT(ABS(ENP(7)))
C
C *** IN CASE OF ENERGY ABOVE CUT-OFF LET THE PARTICLE CASCADE ***
      TEST=ABS(CHARGE)
      IF ((TEST .GT. 1.0E-10) .AND. (ENP(5) .GT. CUTHAD)) GO TO 35
      IF ((TEST .LE. 1.0E-10) .AND. (ENP(5) .GT. CUTNEU)) GO TO 35
C
C --- SECOND CHANCE FOR ANTI-BARYONS DUE TO POSSIBLE ANNIHILATION ---
      IF ((AMAS .GE. 0.0) .OR. (KPART .LE. 14)) GO TO 13
      ANNI=1.3*P
      IF (ANNI .GT. 0.4) ANNI=0.4
      CALL GRNDM(RNDM,1)
      TEST=RNDM(1)
      IF (TEST .GT. ANNI) GO TO 35
C
C *** PARTICLE WITH ENERGY BELOW CUT-OFF ***
C --- ==> ONLY NUCLEAR EVAPORATION AND QUASI-ELASTIC SCATTERING ---
 13   CONTINUE
C
      ISTOP=3
C
      IF (NPRT(9)) PRINT 1002,KPART,EK,EN,P,ENP(5),ENP(6),ENP(7)
 1002 FORMAT(' *GHEISH* ENERGY BELOW CUT-OFF FOR GHEISHA PARTICLE ',I3/
     $ ' EK,EN,P,ENP(5),ENP(6),ENP(7) = ',6(G12.5,1X))
C
      IF ((KPART .NE. 14) .AND. (KPART .NE. 16)) GO TO 14
      IF (KPART .EQ. 16) GO TO 86
C
C --- SLOW PROTON ---
 85   CONTINUE
      IF (NPRT(9)) PRINT 2003,EK,KPART
 2003 FORMAT(' *GHEISH* ROUTINE NUCREC WILL BE CALLED',
     $ ' EK = ',G12.5,' GEV  KPART = ',I3)
      CALL NUCREC(NOPT,2)
C
      IF (NOPT .NE. 0) GO TO 50
C
      IF (NPRT(9)) PRINT 2004,EK,KPART
 2004 FORMAT(' *GHEISH* ROUTINE COSCAT WILL BE CALLED',
     $ ' EK = ',G12.5,' GEV  KPART = ',I3)
      CALL COSCAT
      GO TO 40
C
C --- SLOW NEUTRON ---
 86   CONTINUE
      IF (NPRT(9)) PRINT 2015
      NUCFLG=0
      CALL GNSLWD(NUCFLG,INT,NFL,TEKLOW)
      IF (NUCFLG .NE. 0) GO TO 50
      GO TO 40
C
C --- OTHER SLOW PARTICLES ---
 14   CONTINUE
      IPA(1)=KPART
C --- DECIDE FOR PROTON OR NEUTRON TARGET ---
      IPA(2)=16
      CALL GRNDM(RNDM,1)
      TEST1=RNDM(1)
      TEST2=ZNO2/ATNO2
      IF (TEST1 .LT. TEST2) IPA(2)=14
      AVERN=0.0
      NFL=1
      IF (IPA(2) .EQ. 16) NFL=2
      IPPP=KPART
      IF (NPRT(9)) PRINT 2005
 2005 FORMAT(' *GHEISH* ROUTINE TWOB WILL BE CALLED')
      CALL TWOB(IPPP,NFL,AVERN)
      GOTO 40
C
C --- INITIALISATION OF CASCADE QUANTITIES ---
 35   CONTINUE
C
C *** CASCADE GENERATION ***
C --- CALCULATE FINAL STATE MULTIPLICITY AND LONGITUDINAL AND ---
C --- TRANSVERSE MOMENTUM DISTRIBUTIONS ---
C
C --- FIXED PARTICLE TYPE TO STEER THE CASCADE ---
      KKPART=KPART
C
C --- NO CASCADE FOR LEPTONS ---
      IF (KKPART .LE. 6) GO TO 9999
C
C *** WHAT TO DO WITH "NEW PARTICLES" FOR GHEISHA ?????? ***
C --- RETURN FOR THE TIME BEING ---
      IF (KKPART .GE. 35) GO TO 9999
C
C --- CASCADE OF HEAVY FRAGMENTS
      IF ((KKPART .GE. 30) .AND. (KKPART .LE. 32)) GO TO 390
C
C --- INITIALIZE THE IPA ARRAY ---
      CALL VZERO(IPA(1),MXGKCU)
C
C --- CASCADE OF OMEGA - AND OMEGA - BAR ---
      IF (KKPART .EQ. 33) GO TO 330
      IF (KKPART .EQ. 34) GO TO 331
C
      NVEPAR=KKPART-17
      IF (NVEPAR .LE. 0) GO TO 15
      GO TO (318,319,320,321,322,323,324,325,326,327,328,329),NVEPAR
C
 15   CONTINUE
      NVEPAR=KKPART-6
      GO TO (307,308,309,310,311,312,313,314,315,316,317,318),NVEPAR
C
C --- PI+ CASCADE ---
 307  CONTINUE
      IF (NPRT(9)) PRINT 2006
 2006 FORMAT(' *GHEISH* ROUTINE CASPIP WILL BE CALLED')
      CALL CASPIP(J,INT,NFL)
      GO TO 40
C
C --- PI0 ==> NO CASCADE ---
 308  CONTINUE
      GO TO 40
C
C --- PI- CASCADE ---
 309  CONTINUE
      IF (NPRT(9)) PRINT 2007
 2007 FORMAT(' *GHEISH* ROUTINE CASPIM WILL BE CALLED')
      CALL CASPIM(J,INT,NFL)
      GO TO 40
C
C --- K+ CASCADE ---
 310  CONTINUE
      IF (NPRT(9)) PRINT 2008
 2008 FORMAT(' *GHEISH* ROUTINE CASKP WILL BE CALLED')
      CALL CASKP(J,INT,NFL)
      GO TO 40
C
C --- K0 CASCADE ---
 311  CONTINUE
      IF (NPRT(9)) PRINT 2009
 2009 FORMAT(' *GHEISH* ROUTINE CASK0 WILL BE CALLED')
      CALL CASK0(J,INT,NFL)
      GO TO 40
C
C --- K0 BAR CASCADE ---
 312  CONTINUE
      IF (NPRT(9)) PRINT 2010
 2010 FORMAT(' *GHEISH* ROUTINE CASK0B WILL BE CALLED')
      CALL CASK0B(J,INT,NFL)
      GO TO 40
C
C --- K- CASCADE ---
 313  CONTINUE
      IF (NPRT(9)) PRINT 2011
 2011 FORMAT(' *GHEISH* ROUTINE CASKM WILL BE CALLED')
      CALL CASKM(J,INT,NFL)
      GO TO 40
C
C --- PROTON CASCADE ---
 314  CONTINUE
      IF (NPRT(9)) PRINT 2012
 2012 FORMAT(' *GHEISH* ROUTINE CASP WILL BE CALLED')
      CALL CASP(J,INT,NFL)
      GO TO 40
C
C --- PROTON BAR CASCADE ---
 315  CONTINUE
      IF (NPRT(9)) PRINT 2013
 2013 FORMAT(' *GHEISH* ROUTINE CASPB WILL BE CALLED')
      CALL CASPB(J,INT,NFL)
      GO TO 40
C
C --- NEUTRON CASCADE ---
 316  CONTINUE
      NUCFLG=0
      IF (EK .GT. SWTEKN) THEN
         CALL CASN(J,INT,NFL)
         IF (NPRT(9)) PRINT 2014
 2014 FORMAT(' *GHEISH* ROUTINE CASN WILL BE CALLED')
      ELSE
         CALL GNSLWD(NUCFLG,INT,NFL,TEKLOW)
         IF (NPRT(9)) PRINT 2015
 2015 FORMAT(' *GHEISH* ROUTINE GNSLWD WILL BE CALLED')
      ENDIF
      IF (NUCFLG .NE. 0) GO TO 50
      GO TO 40
C
C --- NEUTRON BAR CASCADE ---
 317  CONTINUE
      IF (NPRT(9)) PRINT 2016
 2016 FORMAT(' *GHEISH* ROUTINE CASNB WILL BE CALLED')
      CALL CASNB(J,INT,NFL)
      GO TO 40
C
C --- LAMBDA CASCADE ---
 318  CONTINUE
      IF (NPRT(9)) PRINT 2017
 2017 FORMAT(' *GHEISH* ROUTINE CASL0 WILL BE CALLED')
      CALL CASL0(J,INT,NFL)
      GO TO 40
C
C --- LAMBDA BAR CASCADE ---
 319  CONTINUE
      IF (NPRT(9)) PRINT 2018
 2018 FORMAT(' *GHEISH* ROUTINE CASAL0 WILL BE CALLED')
      CALL CASAL0(J,INT,NFL)
      GO TO 40
C
C --- SIGMA + CASCADE ---
 320  CONTINUE
      IF (NPRT(9)) PRINT 2019
 2019 FORMAT(' *GHEISH* ROUTINE CASSP WILL BE CALLED')
      CALL CASSP(J,INT,NFL)
      GO TO 40
C
C --- SIGMA 0 ==> NO CASCADE ---
 321  CONTINUE
      GO TO 40
C
C --- SIGMA - CASCADE ---
 322  CONTINUE
      IF (NPRT(9)) PRINT 2020
 2020 FORMAT(' *GHEISH* ROUTINE CASSM WILL BE CALLED')
      CALL CASSM(J,INT,NFL)
      GO TO 40
C
C --- SIGMA + BAR CASCADE ---
 323  CONTINUE
      IF (NPRT(9)) PRINT 2021
 2021 FORMAT(' *GHEISH* ROUTINE CASASP WILL BE CALLED')
      CALL CASASP(J,INT,NFL)
      GO TO 40
C
C --- SIGMA 0 BAR ==> NO CASCADE ---
 324  CONTINUE
      GO TO 40
C
C --- SIGMA - BAR CASCADE ---
 325  CONTINUE
      IF (NPRT(9)) PRINT 2022
 2022 FORMAT(' *GHEISH* ROUTINE CASASM WILL BE CALLED')
      CALL CASASM(J,INT,NFL)
      GO TO 40
C
C --- XI 0 CASCADE ---
 326  CONTINUE
      IF (NPRT(9)) PRINT 2023
 2023 FORMAT(' *GHEISH* ROUTINE CASX0 WILL BE CALLED')
      CALL CASX0(J,INT,NFL)
      GO TO 40
C
C --- XI - CASCADE ---
 327  CONTINUE
      IF (NPRT(9)) PRINT 2024
 2024 FORMAT(' *GHEISH* ROUTINE CASXM WILL BE CALLED')
      CALL CASXM(J,INT,NFL)
      GO TO 40
C
C --- XI 0 BAR CASCADE ---
 328  CONTINUE
      IF (NPRT(9)) PRINT 2025
 2025 FORMAT(' *GHEISH* ROUTINE CASAX0 WILL BE CALLED')
      CALL CASAX0(J,INT,NFL)
      GO TO 40
C
C --- XI - BAR CASCADE ---
 329  CONTINUE
      IF (NPRT(9)) PRINT 2026
 2026 FORMAT(' *GHEISH* ROUTINE CASAXM WILL BE CALLED')
      CALL CASAXM(J,INT,NFL)
      GO TO 40
C
C --- OMEGA - CASCADE ---
 330  CONTINUE
      IF (NPRT(9)) PRINT 2027
 2027 FORMAT(' *GHEISH* ROUTINE CASOM WILL BE CALLED')
      CALL CASOM(J,INT,NFL)
      GO TO 40
C
C --- OMEGA - BAR CASCADE ---
 331  CONTINUE
      IF (NPRT(9)) PRINT 2028
 2028 FORMAT(' *GHEISH* ROUTINE CASAOM WILL BE CALLED')
      CALL CASAOM(J,INT,NFL)
      GO TO 40
C
C --- HEAVY FRAGMENT CASCADE ---
 390  CONTINUE
      IF (NPRT(9)) PRINT 2090
 2090 FORMAT(' *GHEISH* ROUTINE CASFRG WILL BE CALLED')
      NUCFLG=0
      CALL CASFRG(NUCFLG,INT,NFL)
      IF (NUCFLG .NE. 0) GO TO 50
C
C *** CHECK WHETHER THERE ARE NEW PARTICLES GENERATED ***
 40   CONTINUE
      IF ((NTOT .NE. 0) .OR. (KKPART .NE. KPART)) GO TO 50
C
C --- NO SECONDARIES GENERATED AND PARTICLE IS STILL THE SAME ---
C --- ==> COPY EVERYTHING BACK IN THE CURRENT GEANT STACK ---
      NGKINE=0
      TOFG=TOFG+TOF*0.5E-10
C --- In case of crazy momentum value ==> no change to GEANT stack ---
      IF (P .LT. 0.) GO TO 41
      VECT(4)=PX
      VECT(5)=PY
      VECT(6)=PZ
      VECT(7)=P
      GETOT=EN
      GEKIN=EK
C --- CHECK KINETIC ENERGY ---
      CALL GEKBIN
      EDEP=ABS(ENOLD-EN)
      RMASSI=EN-EK
      IF (NPRT(9) .AND. (EN .GT. ENOLD))
     $ PRINT 8888,EDEP,ENOLD,EN,EK,RMASSI
 8888 FORMAT(' *GHEISH* EDEP,ENOLD,EN,EK,M = ',5(G12.5,1X)/
     $ ' *GHEISH* =======> EDEP WOULD BE NEGATIVE <========')
      IF (ISTOP .EQ. 0) DESTEP=DESTEP+EDEP
C
C --- RE-INITIALIZE THE PROBABILITY FOR HADRONIC INTERACTION ---
 41   CONTINUE
      CALL GRNDM(RNDM,1)
      IF ((RNDM(1) .LE. 0.) .OR. (RNDM(1) .GE. 1.)) GO TO 41
      ZINTHA=-LOG(RNDM(1))
      SLHADR=SLENG
      STEPHA=1.0E10
C
      NVEDUM=KIPART(IPART)
      IF (NPRT(9)) PRINT 1003,NTOT,IPART,KPART,KKPART,NVEDUM
 1003 FORMAT(' *GHEISH* NO SEC. GEN. NTOT,IPART,KPART,KKPART,KIPART = ',
     $ 5(I3,1X)/
     $ ' CURRENT PARTICLE ON THE STACK AGAIN')
      GO TO 9999
C
C *** CURRENT PARTICLE IS NOT THE SAME AS IN THE BEGINNING OR/AND ***
C *** ONE OR MORE SECONDARIES HAVE BEEN GENERATED ***
 50   CONTINUE
C
      NVEDUM=KIPART(IPART)
      IF (NPRT(9)) PRINT 1004,NTOT,IPART,KPART,KKPART,NVEDUM
 1004 FORMAT(' *GHEISH* SEC. GEN. NTOT,IPART,KPART,KKPART,KIPART = ',
     $ 5(I3,1X))
C
C --- INITIAL PARTICLE TYPE HAS BEEN CHANGED ==> PUT NEW TYPE ON ---
C --- THE GEANT TEMPORARY STACK ---
C
C --- MAKE CHOICE BETWEEN K0 LONG / K0 SHORT ---
      IF ((KPART .NE. 11) .AND. (KPART .NE. 12)) GO TO 52
      CALL GRNDM(RNDM,1)
      KPART=11.5+RNDM(1)
C
 52   CONTINUE
      ITY=IKPART(KPART)
      LNVE=LQ(JPART-ITY)
      IF (LNVE .LE. 0) PRINT 1234,NTOT,ITY,LNVE
 1234 FORMAT('0*GHEISH* 1234 NTOT,ITY,LNVE = ',3(I10,1X))
      IF (LNVE .LE. 0) STOP
      IF (ISTOP .EQ. 0) ISTOP=1
C
C --- IN CASE THE NEW PARTICLE IS A NEUTRINO ==> FORGET IT ---
      IF (KPART .EQ. 2) GO TO 60
C
C --- PUT PARTICLE ON THE STACK ---
      GKIN(1,1)=PX*P
      GKIN(2,1)=PY*P
      GKIN(3,1)=PZ*P
      GKIN(4,1)=SQRT(P*P+RMASS(KPART)**2)
      GKIN(5,1)=ITY
      TOFD(1)=TOF*0.5E-10
      NGKINE = 1
      GPOS(1,1) = VECT(1)
      GPOS(2,1) = VECT(2)
      GPOS(3,1) = VECT(3)
C
      IF (NPRT(9)) PRINT 1005,ITY,NGKINE
 1005 FORMAT(' *GHEISH* GEANT PART. ',I3,' PUT ONTO STACK AT POS. ',I3)
C
C *** CHECK WHETHER SECONDARIES HAVE BEEN GENERATED AND COPY THEM ***
C *** ALSO ON THE GEANT STACK ***
 60   CONTINUE
C
C --- ALL QUANTITIES ARE TAKEN FROM THE GHEISHA STACK WHERE THE ---
C --- CONVENTION IS THE FOLLOWING ---
C
C EVE(INDEX+ 1)= X
C EVE(INDEX+ 2)= Y
C EVE(INDEX+ 3)= Z
C EVE(INDEX+ 4)= NCAL
C EVE(INDEX+ 5)= NCELL
C EVE(INDEX+ 6)= MASS
C EVE(INDEX+ 7)= CHARGE
C EVE(INDEX+ 8)= TOF
C EVE(INDEX+ 9)= PX
C EVE(INDEX+10)= PY
C EVE(INDEX+11)= PZ
C EVE(INDEX+12)= TYPE
C
      IF (NTOT .LE. 0) GO TO 9999
C
C --- ONE OR MORE SECONDARIES HAVE BEEN GENERATED ---
      DO 61 L=1,NTOT
      INDEX=(L-1)*12
      JND=EVE(INDEX+12)
C
C --- MAKE CHOICE BETWEEN K0 LONG / K0 SHORT ---
      IF ((JND .NE. 11) .AND. (JND .NE. 12)) GO TO 63
      CALL GRNDM(RNDM,1)
      JND=11.5+RNDM(1)
C
C --- FORGET ABOUT NEUTRINOS ---
 63   CONTINUE
      IF (JND .EQ. 2) GO TO 61
C
C --- SWITH TO GEANT QUANTITIES ---
      ITY=IKPART(JND)
      JTY=LQ(JPART-ITY)
      IF (JTY .LE. 0) PRINT 1235,NTOT,ITY,JTY
 1235 FORMAT('0*GHEISH* 1235 NTOT,ITY,JTY = ',3(I10,1X))
      IF (JTY .LE. 0) STOP
*     ITRT=Q(JTY+6)
      PLX=EVE(INDEX+9)
      PLY=EVE(INDEX+10)
      PLZ=EVE(INDEX+11)
      ELT=SQRT(PLX*PLX+PLY*PLY+PLZ*PLZ+Q(JTY+7)**2)
C
C --- ADD PARTICLE TO THE STACK IF STACK NOT YET FULL ---
      IF (NGKINE .GE. MXGKIN) THEN
          WRITE(CHMAIL,1236) NTOT, L
 1236     FORMAT(' *** GHEISH: ',I9,' particle produced but only ',
     +           I9,' put on the GEANT stack!')
          CALL GMAIL(1,1)
          GO TO 9999
      ENDIF
      NGKINE=NGKINE+1
      GKIN(1,NGKINE)=PLX
      GKIN(2,NGKINE)=PLY
      GKIN(3,NGKINE)=PLZ
      GKIN(4,NGKINE)=ELT
      GKIN(5,NGKINE)=ITY
      TOFD(NGKINE)=EVE(INDEX+8)*0.5E-10
      GPOS(1,NGKINE) = VECT(1)
      GPOS(2,NGKINE) = VECT(2)
      GPOS(3,NGKINE) = VECT(3)
C
      IF (NPRT(9)) PRINT 1006,ITY,NGKINE,L,(EVE(INDEX+J),J=1,12)
 1006 FORMAT(' *GHEISH* GEANT PART. ',I3,' ALSO PUT ONTO STACK AT',
     $ ' POS. ',I3/
     $ ' EVE(',I2,') = '/12(1H ,12X,G12.5/))
C
 61   CONTINUE
C
 9999 CONTINUE
C --- LIMIT THE VALUE OF NGKINE IN CASE OF OVERFLOW ---
      NGKINE=MIN(NGKINE,MXGKIN)
      END
 
*CMZ :  1.40/05 16/12/97  13.31.05  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.47  by  S.Giani
*-- Author :
      SUBROUTINE GFMFIN
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
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
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
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
*KEEP,GSECTI.
      COMMON/GSECTI/ AIEL(20),AIIN(20),AIFI(20),AICA(20),ALAM,K0FLAG
      INTEGER K0FLAG
      REAL AIEL,AIIN,AIFI,AICA,ALAM
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
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
*KEEP,DIMPAR.
*                                                                     *
*=== dimpar ==========================================================*
*                                                                     *
*---------------------------------------------------------------------*
*                                                                     *
*      DIMPAR: included in any routine                                *
*                                                                     *
*          Mxxrgn = maximum number of regions                         *
*          Mxxmdf = maximum number of media in Fluka                  *
*          Mxxmde = maximum number of media in Emf                    *
*          Mfstck = stack dimension in Fluka                          *
*          Mestck = stack dimension in Emf                            *
*          Nallwp = number of allowed particles                       *
*          Mpdpdx = number of particle types for which EM dE/dx pro-  *
*                   cesses (ion,pair,bremss) have to be computed      *
*          Icomax = maximum number of materials for compounds (equal  *
*                   to the sum of the number of materials for every   *
*                   compound )                                        *
*          Nstbis = number of stable isotopes recorded in common iso- *
*                   top                                               *
*                                                                     *
*---------------------------------------------------------------------*
*                                                                     *
      PARAMETER ( MXXRGN = 500  )
      PARAMETER ( MXXMDF = 50   )
      PARAMETER ( MXXMDE = 18   )
      PARAMETER ( MFSTCK = 1000 )
      PARAMETER ( MESTCK = 100  )
      PARAMETER ( NALLWP = 39   )
      PARAMETER ( MPDPDX = 8    )
      PARAMETER ( ICOMAX = 120  )
      PARAMETER ( NSTBIS = 304  )
 
*KEEP,FINUCT.
      DOUBLE PRECISION CXR, CYR, CZR, TKI, PLR, WEI, TV, TVCMS,
     &                 TVRECL, TVHEAV, TVBIND
 
*KEEP,FINUC.
*
*=== finuc ============================================================*
*
*----------------------------------------------------------------------*
*     Last change on 5 april 1990     by Alfredo Ferrari, INFN Milan   *
*     include file: finuc copy                   created 26/11/86 by pa*
*     note: if changed change finuc2 copy also                         *
*     changes: none                                                    *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /finuc/ is the storage for secondaries created in event          *
*        np        = number of secondaries                             *
*        kpart(ip) = type of the secondary ip                          *
*        cxr(ip)   = direction cosine of the secondary ip              *
*                    with respect to x-axis                            *
*        cyr(ip)   = direction cosine of the secondary ip              *
*                    with respect to y-axis                            *
*        czr(ip)   = direction cosine of the secondary ip              *
*                    with respect to z-axis                            *
*        tki(ip)   = kinetic energy of secondary ip                    *
*        plr(ip)   = momentum of the secondary ip                      *
*        wei(ip)   = weight of the secondary ip                        *
*        tv        = excitation energy                                 *
*        tvcms     = actual excitation energy of the residual nucleus  *
*        tvrecl    = recoil kinetic energy of the residual nucleus     *
*        tvheav    = recoil kinetic energies of heavy (2-H, 3-H, 3-He, *
*                    4-He) fragments after evaporation                 *
*        tvbind    = approximate energy wasted in nuclear binding      *
*                    effects
*----------------------------------------------------------------------*
*
      PARAMETER (MXP=999)
      COMMON / FKFINU / CXR (MXP), CYR (MXP), CZR (MXP), TKI (MXP),
     &                 PLR (MXP), WEI (MXP), TV, TVCMS, TVRECL, TVHEAV,
     &                 TVBIND, NP0, NP, KPART (MXP)
 
*KEND.
      REAL RNDM(1)
      DOUBLE PRECISION AOCMBM, AMSS , ZTAR, RHO , ZLIN, ZLEL, ZLRAD,
     +ZUL
      COMMON / FKMAPA / AOCMBM (MXXMDF), AMSS (MXXMDF), ZTAR   (MXXMDF),
     +                  RHO    (MXXMDF), ZLIN (MXXMDF), ZLEL   (MXXMDF),
     +                  ZLRAD  (MXXMDF), ZUL  (MXXMDF), MEDIUM (MXXRGN),
     +                  MULFLG (MXXMDF),IFCOMP(MXXMDF), MSSNUM (MXXMDF),
     +                  NREGS, NMATF, MTBSNM
*KEEP,PART2T.
      DOUBLE PRECISION AAM, GA, TAU, AAMDSC
 
*KEEP,PART2.
*
*=== part2 ============================================================*
*
*----------------------------------------------------------------------*
*     Include file: part2 copy        Revised on 20-7-90 by A. Ferrari *
*     Note: see also part copy and part3 copy                          *
*     Changes: none                                                    *
*     Included in the following subroutines or functions: not updated  *
*                                                                      *
*     Description of the common block(s) and variable(s)               *
*                                                                      *
*         Kptoip = conversion from part to paprop numbering            *
*         Iptokp = conversion from paprop to part numbering            *
*                                                                      *
*----------------------------------------------------------------------*
*
      PARAMETER (IDMAX8=183)
      CHARACTER*8  ANAME
      COMMON / FKPART / AAM  (IDMAX8), GA     (IDMAX8), TAU    (IDMAX8),
     &                AAMDSC (IDMAX8), IICH   (IDMAX8), IIBAR  (IDMAX8),
     &                K1     (IDMAX8), K2     (IDMAX8), KPTOIP (IDMAX8),
     &                IPTOKP (39)
      COMMON / FKCHPA / ANAME (IDMAX8)
 
*KEEP,COMCONT.
      DOUBLE PRECISION AOCMBC, CONTNT, SUMACN, CABINX, CABELX,
     &                 ANXNOR, ELXNOR, CONA13, SUMZMF
 
*KEEP,COMCON.
*
*=== comcon ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     include file: comcon copy                 created 26/11/86 by pa *
*                                                                      *
*     Last change  on  30-oct-92   by   Alfredo Ferrari, INFN - Milan  *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*                                                                      *
*     /comcon/ contains information about compounds                    *
*         icompl(imat) = number of materials in a compound             *
*         matnum(i)    = material numbers (compounds consist of the    *
*                        materials)                                    *
*         aocmbc(i)    = atomic densities in barn**-1 cm**-1           *
*                        (Atoms Over Cm times Barn for Compounds)      *
*         cona13(i)    = A^1/3 of the constituents                     *
*         sumzmf(i)    = cumulative z^2 for multiple scattering        *
*         contnt(i)    = partial densities                             *
*         sumacn(i)    = cumulative atom contents of the compounds     *
*         cabinx(i)    = cumulative at.cont.*inelastic cross section   *
*         cabelx(i)    = cumulative at.cont.*  elastic cross section   *
*         anxnor       = total inelastic cross section                 *
*         elxnor       = total   elastic cross section                 *
*----------------------------------------------------------------------*
*
      COMMON /FKCOMC/ AOCMBC (ICOMAX), CONA13 (ICOMAX), SUMZMF (ICOMAX),
     &                CONTNT (ICOMAX), SUMACN (ICOMAX), CABINX (ICOMAX),
     &                CABELX (ICOMAX), ANXNOR, ELXNOR,  ICOMPL (MXXMDF),
     &                MATNUM (ICOMAX)
 
*KEEP,FHEAVYT.
      DOUBLE PRECISION CXHEAV, CYHEAV, CZHEAV, TKHEAV, PHEAVY,
     &                 WHEAVY, AMHEAV
 
*KEEP,FHEAVY.
*
*=== fheavy ===========================================================*
*
*----------------------------------------------------------------------*
*     Last change on 9 March 1993     by Alfredo Ferrari, INFN Milan   *
*     include file: fheavy copy       created 5/4/90 by A. Ferrari     *
*     changes: none                                                    *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /fheavy/ is the storage for heavy secondaries created in the     *
*              nuclear evaporation                                     *
*        npheav     = number of secondaries                            *
*        kheavy(ip) = type of the secondary ip                         *
*                   ( 3 = deuteron, 4 = 3-H, 5 = 3-He, 6 = 4-He,       *
*                     7-12 = "Heavy" fragment specified by Ibheav and  *
*                     Icheav )                                         *
*        cxheav(ip) = direction cosine of the secondary ip             *
*                     with respect to x-axis                           *
*        cyheav(ip) = direction cosine of the secondary ip             *
*                     with respect to y-axis                           *
*        czheav(ip) = direction cosine of the secondary ip             *
*                     with respect to z-axis                           *
*        tkheav(ip) = kinetic energy of secondary ip                   *
*        pheavy(ip) = momentum of the secondary ip                     *
*        wheavy(ip) = weight of the secondary ip                       *
*        amheav(ip) = atomic masses of the six types of evaporated     *
*                     particles                                        *
*        anheav(kp) = name of the kp-type heavy particle               *
*        icheav(kp) = charge of the kp-type heavy particle             *
*        ibheav(kp) = mass number of the kp-type heavy particle        *
*   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   *
*   !!! There is now the possibility to produce up to 6 "heavy" !!!!   *
*   !!! fragments besides the residual nucleus recorded in      !!!!   *
*   !!! Resnuc: they are identified by indeces 7-12, of course  !!!!   *
*   !!! the corresponding physical properties (Z,A,m..) must be !!!!   *
*   !!! updated every time they are produced                    !!!!   *
*   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   *
*----------------------------------------------------------------------*
*
      PARAMETER ( MXHEAV = 100 )
      CHARACTER*8 ANHEAV
      COMMON / FKHEAV / CXHEAV (MXHEAV), CYHEAV (MXHEAV),
     &                  CZHEAV (MXHEAV), TKHEAV (MXHEAV),
     &                  PHEAVY (MXHEAV), WHEAVY (MXHEAV),
     &                  AMHEAV  ( 12 ) ,
     &                  KHEAVY (MXHEAV), ICHEAV  ( 12 ) ,
     &                  IBHEAV  ( 12 ) , NPHEAV
      COMMON / FKHEAC / ANHEAV  ( 12 )
 
*KEEP,PAPROP.
*
*=== paprop ===========================================================*
*
*----------------------------------------------------------------------*
*     include file: paprop copy                   created 26/11/86 by p*
*     changes: on  16 december 1992 by Alfredo Ferrari                 *
*     included in the following subroutines or functions: not updated  *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*     /paprop/ contains particle properties                            *
*        btype  = literal name of the particle                         *
*        am     = particle mass in gev                                 *
*        ichrge = electric charge of the particle                      *
*        iscore = explanations for the scored distribution             *
*        genpar = names of the generalized particles                   *
*        ijdisc = list of the particle types to be discarded           *
*        thalf  = half life of the particle in sec                     *
*        biasdc = decay biasing factors                                *
*        biasin = inelastic interaction biasing factors                *
*        lhadro = flag for hadrons                                     *
*        jspinp = particle spin (in units of 1/2)                      *
*        lbsdcy = logical flag for biased decay: if .true. the biasing *
*                 factor is used as an upper limit to the decay length *
*        lprbsd = logical flag for biased decay: if .true. the biasing *
*                 factor is applied only to primaries                  *
*        lprbsi = logical flag for inelastic interaction biasing: if   *
*                 .true. the biasing factor is applied only to prima-  *
*                 ries                                                 *
*                                                                      *
*----------------------------------------------------------------------*
*
      LOGICAL LHADRO, LBSDCY, LPRBSD, LPRBSI
      CHARACTER*8 BTYPE,GENPAR
      COMMON / FKPAPR / AM  (NALLWP), AMDISC (NALLWP), THALF  (NALLWP),
     &               BIASDC (NALLWP), BIASIN (NALLWP), ICHRGE (NALLWP),
     &               ISCORE     (10), IJDISC (NALLWP), LHADRO (NALLWP),
     &               JSPINP (NALLWP), LBSDCY (NALLWP), LPRBSD, LPRBSI
      COMMON / FKCHPR / BTYPE  (NALLWP), GENPAR (30)
 
*KEEP,PAPROPT.
      DOUBLE PRECISION AM, AMDISC, THALF,BIASDC, BIASIN
 
*KEEP,GFKDIS.
*KEND.
      DOUBLE PRECISION POO,EKE,TXI,TYI,TZI,AMM,WE,ONE,PGEANT,DMOD
      PARAMETER (ONE=1)
      DIMENSION IGTOFL(49),IFLTOG(39),IHVTOG(6),ZSAMP(50)
      DATA IGTOFL / 0, 0, 0, 0, 0, 0,23,13,14,12, 15,16, 8, 1, 2,19, 0,
     +17,21,22, 20, 34, 36, 38, 9,18, 31, 32, 33, 35, 37, 39, 17*0/
 
      DATA IFLTOG /14,15, 3, 2, 4, 4, 1,13,25, 5, 6,10, 8, 9,11,12,18,
     +26,16,21, 19,20, 7, 7*0, 27, 28, 29, 22, 30, 23, 31, 24, 32/
      DATA IHVTOG /13,14,45,46,49,47/
*
      NP = 0
      NPHEAV = 0
*
*    Stopped particles:
*    o Neutral particles are sent to GHSTOP
*    o pi+ and K+/K- are forced to decay
*    o pi-, antiprotons and antineutrons are sent to FLUKA
*      for annihilation (not here but later in this routine)
      IF (IGF.EQ.2.OR.(GEKIN.EQ.0.0.AND.IPART.EQ.13)) THEN
         IF (GEKIN.LT.CUTNEU) THEN
            GEKIN = MAX(GEKIN,1E-14)
* should kinetic energy be deposited?
            ISTOP = 2
            IGF = 0
            GOTO 110
         ENDIF
         CALL GMICAP
         IGF = 0
         GOTO 110
      ELSE IF (GEKIN.EQ.0..AND.
     +        (IPART.EQ.8.OR.IPART.EQ.12.OR.IPART.EQ.11)) THEN
         CALL GDECAY
         NMEC=NMEC+1
         LMEC(NMEC)=5
         ISTOP=1
         GOTO 999
      ENDIF
*
      IF (IFINIT(5) .EQ. 0) CALL FLINIT
      INT=0
      IJ=IGTOFL(IPART)
      IF(IJ.EQ.0) GOTO 110
      NMEC = NMEC + 1
      EKE = GEKIN
      TXI = VECT(4)
      TYI = VECT(5)
      TZI = VECT(6)
      DMOD = ONE/SQRT(TXI**2+TYI**2+TZI**2)
      TXI = TXI*DMOD
      TYI = TYI*DMOD
      TZI = TZI*DMOD
      WE  = 1.
      JMA = LQ(JMATE-NMAT)
      NCOMP = ABS (Q(JMA+11))
      AMM = Q(JMA+6)
      JMIXT = LQ(JMA-5)
 
*    Antiprotons, antineutrons and pi- are sent to
*    eventv for annihilation
      IF (GEKIN.EQ.0..AND.
     +         (IPART.EQ.15.OR.IPART.EQ.9.OR.IPART.EQ.25)) THEN
         IF(NCOMP.LE.1) THEN
            AMSS(1) = Q(JMA+6)
            ZTAR(1) = Q(JMA+7)
            MSSNUM(1) = 0
            RHO(1) = Q(JMA+8)
         ELSE
            ZSAMP(1) = 0.
            DO 10 I=1,NCOMP
               ZSAMP(I+1) = ZSAMP(I) + Q(JMIXT+NCOMP+I)
   10       CONTINUE
            CALL GRNDM(RNDM,1)
            ZCONT=ZSAMP(NCOMP+1)*RNDM(1)
            DO 20 I=1,NCOMP
               IF(ZCONT.LE.ZSAMP(I+1)) GO TO 30
   20       CONTINUE
            I = NCOMP
   30       CONTINUE
            AMSS(1)   = Q(JMIXT+I)
            MSSNUM(1) = 0
            ZTAR(1)   = Q(JMIXT+NCOMP+I)
            RHO(1)    = Q(JMIXT+2*NCOMP+I)*DENS
         END IF
         EKE = 1E-9
         POO=SQRT(EKE*(EKE+2*AM(IJ)))
         CALL EVENTV(IJ,POO,EKE,TXI,TYI,TZI,WE,1)
         GOTO 80
      ELSE IF (GEKIN.LE.CUTHAD .AND. ITRTYP.EQ.4) THEN
         DESTEP = DESTEP + GEKIN
         GEKIN  = 0.
         GETOT  = AMASS
         VECT(7) = 0.
         ISTOP = 1
         GO TO 110
      ENDIF
*
      CALL GRNDM(RNDM,1)
      RNDEVT=RNDM(1)
      IF ( RNDEVT .GE. SINE/FSIG) THEN
 
         IF (GEKIN .GT. 0.02) THEN
            POO=SQRT(EKE*(EKE+2*AM(IJ)))
         ELSE
            GO TO 110
         END IF
         INT=1
         LMEC(NMEC)=13
         IF(NCOMP.LE.1) THEN
            CALL NUCREL(IJ,POO,EKE,TXI,TYI,TZI,AMM,WE)
         ELSE
            CALL GRNDM(RNDM,1)
            RCONT=ELXNOR*RNDM(1)
            DO 40  I=1,NCOMP
               IF(RCONT.LE.CABELX(I)) GO TO 50
   40       CONTINUE
            I=NCOMP
   50       CONTINUE
            CALL NUCREL(IJ,POO,EKE,TXI,TYI,TZI,ONE*Q(JMIXT+I),WE)
         END IF
      ELSE
         LMEC(NMEC)=20
         IF (IHADR.EQ.2) THEN
            ISTOP = 2
            DESTEP = DESTEP + GETOT
            GO TO 110
         ENDIF
         IF (GEKIN .GT. 0.02) THEN
            POO=SQRT(EKE*(EKE+2*AM(IJ)))
         ELSE
            IF ((IJ.EQ.2 .OR. IJ.EQ.9 .OR. IJ.EQ.14 .OR. IJ.EQ.16)
     +            .AND. GEKIN .GT. 0.0) THEN
               POO=SQRT(EKE*(EKE+2*AM(IJ)))
            ELSE
               NMEC=NMEC-1
               GO TO 110
            END IF
         END IF
         INT=2
         IF(NCOMP.LE.1) THEN
            AMSS(1) = Q(JMA+6)
            ZTAR(1) = Q(JMA+7)
            MSSNUM(1) = 0
            RHO(1) = Q(JMA+8)
         ELSE
            CALL GRNDM(RNDM,1)
            RCONT=ANXNOR*RNDM(1)
            DO 60  I=1,NCOMP
               IF(RCONT.LE.CABINX(I)) GO TO 70
   60       CONTINUE
            I=NCOMP
   70       CONTINUE
            AMSS(1)   = Q(JMIXT+I)
            MSSNUM(1) = 0
            ZTAR(1)   = Q(JMIXT+NCOMP+I)
            RHO(1)    = Q(JMIXT+2*NCOMP+I)*DENS
         END IF
         CALL EVENTV(IJ,POO,EKE,TXI,TYI,TZI,WE,1)
      END IF
*
   80 IF(NP.EQ.1.AND.NPHEAV.EQ.0.AND.KPART(1).EQ.IJ) THEN
         VECT(4)=CXR(1)
         VECT(5)=CYR(1)
         VECT(6)=CZR(1)
         VECT(7)=SQRT(TKI(1)*(TKI(1)+2*AMASS))
         GETOT=TKI(1)+AMASS
         GEKIN=TKI(1)
      ELSE
         ISTOP=1
         NSTAK1 = MIN(NP,MXGKIN-NGKINE)
         IF(NP.GT.NSTAK1) THEN
            WRITE(CHMAIL,10000) NP-NSTAK1
            CALL GMAIL(0,0)
         ENDIF
         DO 90  K=1,NSTAK1
            NGKINE = NGKINE + 1
            IF (KPART(K) .EQ. 24 .OR. KPART(K) .EQ. 25) THEN
               KPART(K) = 19
               CALL GRNDM(RNDM,1)
               IF (RNDM(1) .GT. 0.5) KPART(K) = 12
            END IF
            IGEPAR = IFLTOG(KPART(K))
            JPA = LQ(JPART-IGEPAR)
            AGEMAS = Q(JPA+7)
            PGEANT = SQRT(TKI(K)*(TKI(K)+2*AGEMAS))
            GKIN(1,NGKINE)=CXR(K)*PGEANT
            GKIN(2,NGKINE)=CYR(K)*PGEANT
            GKIN(3,NGKINE)=CZR(K)*PGEANT
            GKIN(4,NGKINE)=TKI(K)+AGEMAS
            GKIN(5,NGKINE)=IGEPAR
            TOFD(NGKINE)=0.0
            GPOS(1,NGKINE) = VECT(1)
            GPOS(2,NGKINE) = VECT(2)
            GPOS(3,NGKINE) = VECT(3)
   90    CONTINUE
*
         NSTAK2 = MIN(NPHEAV,MXGKIN-NGKINE)
         IF(NPHEAV.GT.NSTAK2) THEN
            WRITE(CHMAIL,10100) NPHEAV-NSTAK2
            CALL GMAIL(0,0)
         ENDIF
         DO 100 K=1,NSTAK2
            NGKINE = NGKINE + 1
            IGEPAR = IHVTOG(KHEAVY(K))
            JPA = LQ(JPART-IGEPAR)
            AGEMAS = Q(JPA+7)
            PGEANT = SQRT(TKHEAV(K)*(TKHEAV(K)+2*AGEMAS))
            GKIN(1,NGKINE)=CXHEAV(K)*PGEANT
            GKIN(2,NGKINE)=CYHEAV(K)*PGEANT
            GKIN(3,NGKINE)=CZHEAV(K)*PGEANT
            GKIN(4,NGKINE)=TKHEAV(K)+AGEMAS
            GKIN(5,NGKINE)=IGEPAR
            TOFD(NGKINE)=0.0
            GPOS(1,NGKINE) = VECT(1)
            GPOS(2,NGKINE) = VECT(2)
            GPOS(3,NGKINE) = VECT(3)
  100    CONTINUE
*
         KCASE=NAMEC(12)
      END IF
  110 CONTINUE
      ZINTHA = GARNDM(DUMMY)
      SLHADR = SLENG
      STEPHA = 1.0E10
10000 FORMAT(' **** FLUFIN: Stack overflow, ',I6,' particles lost')
10100 FORMAT(' **** FLUFIN: Stack overflow, ',I6,
     +' heavy particles lost')
  999 END
*CMZ :  1.40/05 09/02/98  16.15.20  by  Pavel Nevski
*CMZ :  3.21/04 13/12/94  15.17.13  by  S.Giani
*-- Author :
      SUBROUTINE GTCKOV
C.
C.    ******************************************************************
C.    *                                                                *
C.    *   This routine is called to follow the Cherenkov photons       *
C.    *   created during the tracking of charged particles and         *
C.    *   simulate the relevant processes along the way, until either  *
C.    *   the photon is absorbed or exits the detector. Processes      *
C.    *   currently simulated are absorption in-flight, and reflection *
C.    *   /transmission/absorption at a medium boundary. There are two *
C.    *   boundary types: dielectric-metal and dielectric-dielectric.  *
C.    *   For each of these there is a continuum of reflectivity       *
C.    *   and of surface quality from mirror finish to matte. The      *
C.    *   surface model is contained in routine GHSURF.                *
C.    *                                                                *
C.    *   ==>Called by : GTRACK                                        *
C.    *      Authors    F.Carminati, R.Jones ************              *
C.    *                                                                *
C.    *   Modifications:                                               *
C.    *   Nicola.Colonna@ba.infn.it                                    *
C.    *          - more generalized formula for refraction             *
C.    *   PN, 9-feb-98: Let c-photons inter non-transparent media      *
C.    ******************************************************************
C.
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
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
*KEEP,GCSTAK.
      INTEGER  NJTMAX,NJTMIN,NTSTKP,NTSTKS,NDBOOK,NDPUSH,NJFREE,NJGARB,
     +         NJINVO,LINSAV,LMXSAV,NWSTAK,NWINT,NWREAL,NWTRAC
      INTEGER ISTORD
      PARAMETER (NWSTAK=12,NWINT=11,NWREAL=12,NWTRAC=NWINT+NWREAL+5)
      COMMON /GCSTAK/ NJTMAX, NJTMIN, NTSTKP, NTSTKS, NDBOOK, NDPUSH,
     +                NJFREE, NJGARB, NJINVO, LINSAV(15), LMXSAV(15)
      EQUIVALENCE (ISTORD,NJTMIN)
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
*KEEP,GCVOL1.
      COMMON/GCVOL1/NLEVL1,NAMES1(15),NUMBR1(15),LVOLU1(15)
C
      INTEGER NAMES1,NUMBR1,LVOLU1
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
 
*KEEP,GCVDMA.
      COMMON/GCVDMA/NVMANY,MANYLE(20),MANYNA(20,15),
     +MANYNU(20,15),NFMANY,MYCOUN,IMYSE,RAYTRA,VECCOS(3)
C
      INTEGER NVMANY,MANYLE,MANYNA,MANYNU,
     +        NFMANY,MYCOUN,IMYSE
      REAL RAYTRA,VECCOS
C
*KEND.
*
* ** The following common is in GTMEDI. LSAMVL is set to true if
* ** we did not change volume yet
*
      COMMON/GCCHAN/LSAMVL
      LOGICAL LSAMVL
*
      REAL  R(3),U(3),QQ(3),vin(3),u_v(3)
*     REAL  D(3)
 
      LOGICAL LOLDTR
      PARAMETER (EPSMAC=1.E-6)
      PARAMETER (MXPUSH=10)
      SAVE RIN1,EFFIC
C.
C.    ------------------------------------------------------------------
*
* *** Update local pointers if medium has changed
*
      LOLDTR=.FALSE.
      IF(IUPD.EQ.0)THEN
         IUPD  = 1
         JTCKOV = LQ(JTM-3)
         IF(JTCKOV.EQ.0) THEN
*
* *** This Cerenkov photon has crossed into a black medium.
* *** Just absorb it.
            IPROC = 101
            SLABS = 0.
            ISTOP = 2
            STEP  = 0.0001
            DESTEP = VECT(7)
            GOTO 110
         ENDIF
         NPCKOV = Q(JTCKOV+1)
         JABSCO = LQ(JTCKOV-1)
         JEFFIC = LQ(JTCKOV-2)
         JINDEX = LQ(JTCKOV-3)
         JPOLAR = LQ(JSTAK-1)
      ENDIF
      IF(SLENG.LE.0.) THEN
*
* *** Calculate GEKRAT for the particle
         IF(VECT(7).GE.Q(JTCKOV+NPCKOV+1)) THEN
            GEKRAT=1.
            IEKBIN=NPCKOV-1
         ELSEIF(VECT(7).LT.Q(JTCKOV+2)) THEN
*
* *** Particle below energy threshold ?  Short circuit
* *** This should never happen because the photons are generated
* *** only above threshold
*
*            GEKIN = 0.
*            GETOT = 0.
*            VECT(7)= 0.
*            ISTOP = 2
*            NMEC = 1
*            LMEC(1)= 30
*            GO TO 110
 
            GEKRAT=0.
            IEKBIN=1
         ELSE
            JMIN = 1
            JMAX = NPCKOV
   10       JMED = (JMIN+JMAX)/2
            IF(Q(JTCKOV+JMED+1).LT.VECT(7)) THEN
               JMIN = JMED
            ELSE
               JMAX = JMED
            ENDIF
            IF(JMAX-JMIN.GT.1) GO TO 10
            IEKBIN = JMIN
            GEKRAT = (VECT(7) - Q(JTCKOV+IEKBIN+1))/
     +      (Q(JTCKOV+IEKBIN+2)-Q(JTCKOV+IEKBIN+1))
         ENDIF
         GEKRT1=1.-GEKRAT
         RIN1=Q(JINDEX+IEKBIN)*GEKRT1+Q(JINDEX+IEKBIN+1)*GEKRAT
         EFFIC=Q(JEFFIC+IEKBIN)*GEKRT1+Q(JEFFIC+IEKBIN+1)*GEKRAT
         STEPLA=Q(JABSCO+IEKBIN)*GEKRT1+Q(JABSCO+IEKBIN+1)*GEKRAT
      ENDIF
*
* *** Compute current step size
*
      IPROC  = 103
      STEP   = STEMAX
*
*  **   Step limitation due to in flight absorbtion ?
*
      IF (ILABS.GT.0) THEN
         SLABS  = STEPLA*ZINTLA
         IF (SLABS.LT.STEP) THEN
            STEP  = SLABS
            IPROC = 101
         ENDIF
      ENDIF
*
      IF (STEP.LT.0.) STEP = 0.
*
*  **   Step limitation due to geometry ?
*
      STEPT=0.
      IF (STEP.GE.SAFETY) THEN
         CALL GTNEXT
         IF (IGNEXT.NE.0) THEN
*
* **    We are going to cross a boundary, so we need to simulate
* **    boundary effects and to know what is on the other side.
* **    For the moment save the current vector in the geometry tree.
*
         if(mycoun.gt.1.and.nfmany.gt.0)then
           nlevel=manyle(nfmany)
           do 99 i=1,nlevel
             names(i)=manyna(nfmany,i)
             number(i)=manynu(nfmany,i)
 99        continue
           call glvolu(nlevel,names,number,ier)
           if(ier.ne.0)print *,'Fatal error in GLVOLU'
           ingoto=0
         endif
            NLEVL1 = NLEVEL
            DO 20   I=1,NLEVEL
               NAMES1(I) = NAMES(I)
               NUMBR1(I) = NUMBER(I)
               LVOLU1(I) = LVOLUM(I)
   20       CONTINUE
*
* *** This is different from the other tracking routines.
* *** We get to the boundary and then we just jump over it
* *** So, linear transport till we are very near the boundary
*
            STEP = MAX(SNEXT-PREC,0.)
            IF(STEP.GT.0.) THEN
               DO 30 I=1,3
                  VECT(I)=VECT(I)+STEP*VECT(I+3)
   30          CONTINUE
            ENDIF
            STEPT=STEP
            STEP  = SNEXT - STEP + PREC
            IPROC = 0
            INWVOL= 2
            NMEC =  1
            LMEC(1)=1
         ENDIF
*
*        Update SAFETY in stack companions, if any
*        This may well not work.
         IF (IQ(JSTAK+3).NE.0) THEN
            DO 40 IST = IQ(JSTAK+3),IQ(JSTAK+1)
               JST = JSTAK +3 +(IST-1)*NWSTAK
               Q(JST+11) = SAFETY
   40       CONTINUE
            IQ(JSTAK+3) = 0
         ENDIF
*
      ELSE
         IQ(JSTAK+3) = 0
      ENDIF
*
* *** Linear transport
*
      VIN(1) = VECT(1)
      VIN(2) = VECT(2)
      VIN(3) = VECT(3)
      IF (INWVOL.EQ.2) THEN
         NBPUSH = 0
   50    DO 60 I = 1,3
            VECTMP  = VECT(I) +STEP*VECT(I+3)
            IF(VECTMP.EQ.VECT(I)) THEN
*
* *** Correct for machine precision
*
               IF(VECT(I+3).NE.0.) THEN
                  VECTMP = VECT(I)+ABS(VECT(I))*SIGN(1.,VECT(I+3))*
     +            EPSMAC
                  IF(NMEC.GT.0) THEN
                     IF(LMEC(NMEC).EQ.104) NMEC=NMEC-1
                  ENDIF
                  NMEC=NMEC+1
                  LMEC(NMEC)=104
               ENDIF
            ENDIF
            VOUT(I) = VECTMP
   60    CONTINUE
         NUMED1=NUMED
         CALL GTMEDI(VOUT,NUMED2)
         LOLDTR=.TRUE.
         IF(NUMED2.LE.0) THEN
            VECT(1) = VOUT(1)
            VECT(2) = VOUT(2)
            VECT(3) = VOUT(3)
            GO TO 110
         ENDIF
         JVO=LQ(JVOLUM-LVOLUM(NLEVEL))
         IF(LSAMVL.AND.Q(JVO+2).NE.12.) THEN
*
* *** In spite of our efforts we have not crossed the boundary
* *** we increase the step size and try again
*
            NBPUSH = NBPUSH + 1
            IF (NBPUSH.LE.MXPUSH) THEN
              STEP = STEP + NBPUSH*PREC
              GOTO 50
            ELSE
              INWVOL = 0
            ENDIF
 
         ENDIF
         IF(NUMED1.EQ.NUMED2) THEN
*
* *** If we are in the same medium, nothing needs to be done!
*
            VECT(1)=VOUT(1)
            VECT(2)=VOUT(2)
            VECT(3)=VOUT(3)
            IPROC=0
         ELSE
            JTM2 = LQ(JTMED-NUMED2)
            IF(IQ(JTM2-2).GE.3) THEN
               JTCKV2 = LQ(JTM2-3)
            ELSE
               JTCKV2 = 0
            ENDIF
            IF(JTCKV2.GT.0) THEN
               NPCKV2 = Q(JTCKV2+1)
               JABSC2 = LQ(JTCKV2-1)
               JEFFI2 = LQ(JTCKV2-2)
               JINDX2 = LQ(JTCKV2-3)
               IF(VECT(7).GE.Q(JTCKV2+NPCKV2+1)) THEN
                  GEKRT2=1.
                  IEKBI2=NPCKV2-1
               ELSEIF(VECT(7).LT.Q(JTCKV2+2)) THEN
                  GEKRT2=0.
                  IEKBI2=1
               ELSE
                  JMIN = 1
                  JMAX = NPCKV2
   64             JMED = (JMIN+JMAX)/2
                  IF(Q(JTCKV2+JMED+1).LT.VECT(7)) THEN
                     JMIN = JMED
                  ELSE
                     JMAX = JMED
                  ENDIF
                  IF(JMAX-JMIN.GT.1) GO TO 64
                  IEKBI2 = JMIN
                  GEKRT2 = (VECT(7) - Q(JTCKV2+IEKBI2+1))/
     +            (Q(JTCKV2+IEKBI2+2)-Q(JTCKV2+IEKBI2+1))
               ENDIF
               GEKRT1=1.-GEKRT2
               ABSCO2=Q(JABSC2+IEKBI2)*GEKRT1+Q(JABSC2+IEKBI2+1)*GEKRT2
               EFFIC2=Q(JEFFI2+IEKBI2)*GEKRT1+Q(JEFFI2+IEKBI2+1)*GEKRT2
               IF(JINDX2.GT.0) THEN
                 RIN2=Q(JINDX2+IEKBI2)*GEKRT1+Q(JINDX2+IEKBI2+1)*GEKRT2
               ELSE
                 RIN2=0.
               ENDIF
               IPROC = 102
            ELSE
* do nothing - let it be absobed there
*              ISTOP  = 2
*              DESTEP = VECT(7)
*              NMEC   = NMEC+1
*              LMEC(NMEC)=30
               VECT(1)=VOUT(1)
               VECT(2)=VOUT(2)
               VECT(3)=VOUT(3)
               GOTO 110
            ENDIF
         ENDIF
      ELSE
         DO 70 I = 1,3
            VECT(I)  = VECT(I) +STEP*VECT(I+3)
   70    CONTINUE
      ENDIF
*
      STEP = STEPT + STEP
      SLENG = SLENG +STEP
*
* *** Update time of flight
*
      TOFG = TOFG +STEP*RIN1/CLIGHT
*
* *** Update interaction probabilities
*
      IF (ILABS.GT.0)    ZINTLA = ZINTLA -STEP/STEPLA
*
      IF (IPROC.EQ.0) GO TO 110
      NMEC = NMEC+1
      LMEC(NMEC) = IPROC
*
*  ** Absorbtion in flight ?
*
      IF (IPROC.EQ.101) THEN
         ISTOP=2
         CALL GRNDM(RNDM,1)
         IF(RNDM.LT.EFFIC) THEN
*
* ***  Destep =/= 0 means that the photon has been detected
*
            DESTEP=VECT(7)
         ELSE
            DESTEP=0.
         ENDIF
*
*  ** Boundary action?
*
      ELSE IF (IPROC.EQ.102) THEN
         IF(JINDX2.EQ.0) THEN
*
* *** Case dielectric -> metal
*
            CALL GRNDM(RNDM,1)
            IF(RNDM.LT.ABSCO2) THEN
*
* *** Photon is absorbed in the next medium
*
               NMEC=NMEC+1
               LMEC(NMEC)=101
               ISTOP = 2
               CALL GRNDM(RNDM,1)
               IF(RNDM.LT.EFFIC2) THEN
*
* ***  Destep =/= 0 means that the photon has been detected
*
                  DESTEP=VECT(7)
               ELSE
                  DESTEP = 0.
               END IF
               VECT(1) = VOUT(1)
               VECT(2) = VOUT(2)
               VECT(3) = VOUT(3)
               GOTO 110
            ELSE
*
* *** Photon is reflected (no polarization effects)
*
               CALL GLISUR(VECT,VOUT,NUMED1,NUMED2,U,PDOTU,IERR)
               IF (IERR.NE.0) THEN
                  WRITE(CHMAIL,10200) IERR
                  CALL GMAIL(0,0)
                  GO TO 110
               END IF
*
* ** Restore old volume tree, the photon does not cross the boundary
*
*              CALL GLVOLU(NLEVL1,NAMES1,NUMBR1,IERR)
               CALL GTMEDI(VIN,N)
               LOLDTR=.FALSE.
*
*
* *** Reflect, but make sure we are in the old volume before
*
               NBPUSH = 0
   80          NBPUSH = NBPUSH+1
               IF(NBPUSH.GT.MXPUSH) THEN
                  WRITE(CHMAIL,10300) NTMULT,NSTEP
                  CALL GMAIL(0,0)
                  ISTOP=1
                  GOTO 110
               ELSE
                  CALL GINVOL(VECT,ISAME)
                  IF(ISAME.EQ.0) THEN
                     PRECN = NBPUSH*PREC
                     VECT(1) = VECT(1) - PRECN*VECT(4)
                     VECT(2) = VECT(2) - PRECN*VECT(5)
                     VECT(3) = VECT(3) - PRECN*VECT(6)
                     GO TO 80
                  ENDIF
               ENDIF
*
               NMEC=NMEC+1
               LMEC(NMEC)=106
               EDOTU = POLAR(1)*U(1) + POLAR(2)*U(2) + POLAR(3)*U(3)
               VECT(4) = +VECT(4) - 2*PDOTU*U(1)
               VECT(5) = +VECT(5) - 2*PDOTU*U(2)
               VECT(6) = +VECT(6) - 2*PDOTU*U(3)
               POLAR(1) = -POLAR(1) + 2*EDOTU*U(1)
               POLAR(2) = -POLAR(2) + 2*EDOTU*U(2)
               POLAR(3) = -POLAR(3) + 2*EDOTU*U(3)
               INWVOL  = 0
            ENDIF
         ELSE
*
*  case dielectric-dielectric:
*
            CALL GLISUR(VECT,VOUT,NUMED1,NUMED2,U,PDOTU,IERR)
            IF (IERR.NE.0) THEN
               WRITE(CHMAIL,10200) IERR
               CALL GMAIL(0,0)
               GO TO 110
            END IF
            EDOTU = POLAR(1)*U(1) + POLAR(2)*U(2) + POLAR(3)*U(3)
            COST1 = -PDOTU
            IF (ABS(COST1).LT.1.) THEN
               SINT1 = SQRT((1-COST1)*(1+COST1))
               SINT2 = SINT1*RIN1/RIN2
            ELSE
               SINT1 = 0.0
               SINT2 = 0.0
            END IF
            IF (SINT2.GE.1) THEN
*
* ***  Simulate total internal reflection
*
               NMEC=NMEC+1
               LMEC(NMEC)=106
*
* ** Restore old volume tree, the photon does not cross the boundary
*
*              CALL GLVOLU(NLEVL1,NAMES1,NUMBR1,IERR)
               CALL GTMEDI(VIN,N)
               LOLDTR=.FALSE.
*
* *** Reflect, but make sure we are in the old volume before
*
               NBPUSH = 0
   90          NBPUSH = NBPUSH+1
               IF(NBPUSH.GT.MXPUSH) THEN
                  WRITE(CHMAIL,10300) NTMULT,NSTEP
                  CALL GMAIL(0,0)
                  ISTOP=1
                  GOTO 110
               ELSE
                  CALL GINVOL(VECT,ISAME)
                  IF(ISAME.EQ.0) THEN
                     PRECN = NBPUSH*PREC
                     VECT(1) = VECT(1) - PRECN*VECT(4)
                     VECT(2) = VECT(2) - PRECN*VECT(5)
                     VECT(3) = VECT(3) - PRECN*VECT(6)
                     GO TO 90
                  ENDIF
               ENDIF
*
               VECT(4) = +VECT(4) - 2*PDOTU*U(1)
               VECT(5) = +VECT(5) - 2*PDOTU*U(2)
               VECT(6) = +VECT(6) - 2*PDOTU*U(3)
               POLAR(1) = -POLAR(1) + 2*EDOTU*U(1)
               POLAR(2) = -POLAR(2) + 2*EDOTU*U(2)
               POLAR(3) = -POLAR(3) + 2*EDOTU*U(3)
               INWVOL = 0
            ELSE
*
* ***  Calculate amplitude for transmission (Q = P x U)
*
               COST2 = SIGN(1.0,COST1)*SQRT((1-SINT2)*(1+SINT2))
               IF (SINT1.GT.1.E-4) THEN
                  QQ(1) = VECT(5)*U(3) - VECT(6)*U(2)
                  QQ(2) = VECT(6)*U(1) - VECT(4)*U(3)
                  QQ(3) = VECT(4)*U(2) - VECT(5)*U(1)
                  EPERP1 = (POLAR(1)*QQ(1) + POLAR(2)*QQ(2) + POLAR(3)*
     +            QQ(3))
                  ENORM  = SQRT(EPERP1**2+EDOTU**2)
                  EPERP1 = EPERP1/ENORM
                  EPARL1 = EDOTU/ENORM
               ELSE
                  QQ(1) = POLAR(1)
                  QQ(2) = POLAR(2)
                  QQ(3) = POLAR(3)
*
*     Here we follow Jackson's conventions and we set the parallel
*     component = 1 in case of a ray perpendicular to the surface
                  EPERP1 = 0.
                  EPARL1 = 1.
               END IF
               IF(COST1.NE.0.) THEN
                  S1 = RIN1*COST1
                  EPERP2 = 2*S1*EPERP1/(RIN1*COST1+RIN2*COST2)
                  EPARL2 = 2*S1*EPARL1/(RIN2*COST1+RIN1*COST2)
                  E2 = EPERP2**2 + EPARL2**2
                  S2 = RIN2*COST2*E2
                  TCOEF = S2/S1
               ELSE
                  TCOEF = 0.
               ENDIF
               CALL GRNDM(RNDM,1)
               IF (RNDM.GT.TCOEF) THEN
*
* *** Simulate reflection
*
                  NMEC=NMEC+1
                  LMEC(NMEC)=106
*
* *** Restore old volume tree, the photon does not cross the boundary
*
*                 CALL GLVOLU(NLEVL1,NAMES1,NUMBR1,IERR)
                  CALL GTMEDI(VIN,N)
                  LOLDTR=.FALSE.
*
* *** Reflect, but make sure we are in the old volume before
*
                  NBPUSH = 0
  100             NBPUSH = NBPUSH+1
                  IF(NBPUSH.GT.MXPUSH) THEN
                     WRITE(CHMAIL,10300) NTMULT,NSTEP
                     CALL GMAIL(0,0)
                     ISTOP=1
                     GOTO 110
                  ELSE
                     CALL GINVOL(VECT,ISAME)
                     IF(ISAME.EQ.0) THEN
                        PRECN = NBPUSH*PREC
                        VECT(1) = VECT(1) - PRECN*VECT(4)
                        VECT(2) = VECT(2) - PRECN*VECT(5)
                        VECT(3) = VECT(3) - PRECN*VECT(6)
                        GO TO 100
                     ENDIF
                  ENDIF
*
                  VECT(4) = VECT(4) - 2*PDOTU*U(1)
                  VECT(5) = VECT(5) - 2*PDOTU*U(2)
                  VECT(6) = VECT(6) - 2*PDOTU*U(3)
                  IF(SINT1.GT.1E-4) THEN
                     EPARL2 = RIN2*EPARL2/RIN1-EPARL1
                     EPERP2 = EPERP2-EPERP1
                     E2 = EPERP2**2 + EPARL2**2
                     R(1) = U(1) + PDOTU*VECT(4)
                     R(2) = U(2) + PDOTU*VECT(5)
                     R(3) = U(3) + PDOTU*VECT(6)
                     EABS = SQRT(E2)*SINT1
                     CPARL = EPARL2/EABS
                     CPERP = EPERP2/EABS
                     POLAR(1) = CPARL*R(1) - CPERP*QQ(1)
                     POLAR(2) = CPARL*R(2) - CPERP*QQ(2)
                     POLAR(3) = CPARL*R(3) - CPERP*QQ(3)
                  ELSEIF(RIN2.GT.RIN1) THEN
*
* *** Case of ray perpendicular to the surface. No change or
* *** an inversion of phase.
                     POLAR(1) = -POLAR(1)
                     POLAR(2) = -POLAR(2)
                     POLAR(3) = -POLAR(3)
                  ENDIF
                  INWVOL = 0
               ELSE
*
* *** Simulate transmission/refraction
*
                  NMEC=NMEC+1
                  LMEC(NMEC)=107
                  VECT(1) = VOUT(1)
                  VECT(2) = VOUT(2)
                  VECT(3) = VOUT(3)
                  GEKRAT = GEKRT2
                  IEKBIN = IEKBI2
                  STEPLA = ABSCO2
                  EFFIC = EFFIC2
                  RIN1 = RIN2
                  IF(SINT1.GT.1E-4) THEN
c                     ALPHA = COST1-COST2*(RIN2/RIN1)
c                     D(1) = VECT(4) + ALPHA*U(1)
c                     D(2) = VECT(5) + ALPHA*U(2)
c                     D(3) = VECT(6) + ALPHA*U(3)
c                     DABS = SQRT(D(1)**2+D(2)**2+D(3)**2)
c                     VECT(4) = D(1)/DABS
c                     VECT(5) = D(2)/DABS
c                     VECT(6) = D(3)/DABS
 
c ... more generalized formula for refraction ...		nc
 
		     costp = - cost2
	             cost_rel=cosd(acosd(cost1)-acosd(cost2))
		     if(u(1).gt.-1.e-5.and.u(1).lt.1.e-5.and.
     +                  u(2).gt.-1.e-5.and.u(2).lt.1.e-5)then
		      vectn3 = cost2
	 	      cy = (cost_rel-vect(6)*cost2)/(1.-vect(6)**2)
		      vectn2 = vect(5)*cy
		      vectn1 = vect(4) * vectn2 / vect(5)
		     else if(u(2).gt.-1.e-5.and.u(2).lt.1.e-5.and.
     +                       u(3).gt.-1.e-5.and.u(3).lt.1.e-5)then
		      vectn1 = costp
		      cz = (cost_rel-vect(4)*costp)/(1.-vect(4)**2)
		      vectn3 = vect(6) * cz
		      vectn2 = vect(5) * vectn3 /vect(6)
		     else
		      u_v(1) = u(2)*vect(6) - u(3)*vect(5)
		      u_v(2) = u(3)*vect(4) - u(1)*vect(6)
		      u_v(3) = u(1)*vect(5) - u(2)*vect(4)
	 	      c1 = u_v(1)*u(2) - u_v(2)*u(1)
	 	      c2 = u_v(3)*u(1) - u(3)*u_v(1)
	 	      c3 = costp * u_v(1)
	 	      c4 = c2/c1
	 	      c5 = c3/c1
	 	      c1p = u_v(1)*vect(5) - u_v(2)*vect(4)
	 	      c2p = u_v(3)*vect(4) - vect(6)*u_v(1)
	 	      c3p = cost_rel * u_v(1)
	 	      c4p = c2p/c1p
	 	      c5p = c3p/c1p
 
		      vectn3 = (c5p - c5) / (c4 - c4p)
	 	      vectn2 = vectn3 * c4 + c5
		      if(vect(4).eq.0.)return
		vectn1 = (cost_rel-vect(5)*vectn2-vect(6)*vectn3)/vect(4)
		     endif
		      vect(4) = vectn1
		      vect(5) = vectn2
		      vect(6) = vectn3
 
c ... end correction					nc
	 	
		     PDOTU = -COST2
                     R(1) = U(1) - PDOTU*VECT(4)
                     R(2) = U(2) - PDOTU*VECT(5)
                     R(3) = U(3) - PDOTU*VECT(6)
                     EABS = SQRT(E2)
                     CPARL = EPARL2/(EABS*SINT2)
                     CPERP = EPERP2/(EABS*SINT1)
                     POLAR(1) = CPARL*R(1) + CPERP*QQ(1)
                     POLAR(2) = CPARL*R(2) + CPERP*QQ(2)
                     POLAR(3) = CPARL*R(3) + CPERP*QQ(3)
                  ENDIF
               END IF
            END IF
         END IF
      ENDIF
*                                                             END GTCKOV
  110 IF(LOLDTR) CALL GLVOLU(NLEVL1,NAMES1,NUMBR1,IERR)
10200  FORMAT(' **** GTCKOV: error from GLISUR = ',I10)
10300  FORMAT(' **** GTCKOV: unable to reflect at NTMULT = ',
     +        I8,' step No. ',I8,' photon abandoned!')
      END
*CMZ :  1.40/05 09/02/98  16.09.29  by  Pavel Nevski
*CMZ :  3.21/02 21/03/94  17.01.28  by  Rene Brun
*-- Author :
      SUBROUTINE GSCKOV(ITMED, NPCKOV, PPCKOV, ABSCO, EFFIC, RINDEX)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    Stores the tables for UV photon tracking in medium ITMED    *
C.    *    Please note that it is the user's responsability to         *
C.    *    provide all the coefficients:                               *
C.    *                                                                *
C.    *                                                                *
C.    *       ITMED       Tracking medium number                       *
C.    *       NPCKOV      Number of bins of each table                 *
C.    *       PPCKOV      Value of photon momentum (in GeV)            *
C.    *       ABSCO       Absorbtion coefficents                       *
C.    *                   dielectric: absorbtion length in cm          *
C.    *                   metals    : absorbtion fraction (0<=x<=1)    *
C.    *       EFFIC       Detection efficiency for UV photons          *
C.    *       RINDEX      Refraction index (if=0 metal)                *
C.    *                                                                *
C.    *       Called by : <USER>                                       *
C.    *                                                                *
C.    *       Authors: F.Carminati, R.Jones  ************              *
C.    *                                                                *
C.    *       Modifications:                                           *
C.    *       PN, 9-feb-98:   multiple calls subsitute same banks      *
C.    *                                                                *
C.    ******************************************************************
C.
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
C
      DIMENSION PPCKOV(*), ABSCO(*), EFFIC(*), RINDEX(*)
C.
C.    ------------------------------------------------------------------
C.
      JTM = 0
      IF(ITMED.GT.0) THEN
         IF(JTMED.GT.0) THEN
            IF(IQ(JTMED-2).GE.ITMED) THEN
               JTM = LQ(JTMED-ITMED)
            ENDIF
         ENDIF
      ENDIF
      IF(JTM.LE.0) THEN
         WRITE(CHMAIL,10000)
10000   FORMAT(' **** GSCKOV Tracking medium ',I10,' not defined')
         CALL GMAIL(0,0)
         GO TO 999
      ENDIF
      IF(IQ(JTM-2).LT.3) THEN
         CALL MZPUSH(IXSTOR,JTM,3-IQ(JTM-2),0,' ')
      ENDIF
      JTCKOV=LQ(JTM-3)
      IF (JTCKOV.le.0)
     +   CALL MZBOOK(IXCONS,JTCKOV,JTM, -3,'CKOV',4,4,NPCKOV+1,3,-1)
      JABSCO=LQ(JTCKOV-1)
      IF (JABSCO.le.0)
     +   CALL MZBOOK(IXCONS,JABSCO,JTCKOV,-1,'ABSC',0,0,NPCKOV,3,-1)
      JEFFIC=LQ(JTCKOV-2)
      IF (JEFFIC.le.0)
     +   CALL MZBOOK(IXCONS,JEFFIC,JTCKOV,-2,'EFFI',0,0,NPCKOV,3,-1)
      IF(RINDEX(1).GE.1.) THEN
         JINDEX=LQ(JTCKOV-3)
         IF (JINDEX.le.0)
     +    CALL MZBOOK(IXCONS,JINDEX,JTCKOV,-3,'RIND',0,0,NPCKOV,3,-1)
         JCURIN=LQ(JTCKOV-4)
         IF (JCURIN.le.0)
     +    CALL MZBOOK(IXCONS,JCURIN,JTCKOV,-4,'ABCU',0,0,NPCKOV,3,-1)
      ENDIF
      Q(JTCKOV+1)=NPCKOV
      DO 10 J=1, NPCKOV
         Q(JTCKOV+1+J) = PPCKOV(J)
         Q(JABSCO+  J) = MAX(1E-10,ABSCO(J))
         Q(JEFFIC+  J) = EFFIC(J)
         IF(RINDEX(1).GE.1.) THEN
            Q(JINDEX+ J) = RINDEX(J)
            IF(J.GT.1) THEN
               Q(JCURIN+J)=0.5*((1/RINDEX(J-1)**2)+(1./RINDEX(J)**2))
               Q(JCURIN+J)=Q(JCURIN+J-1)+(PPCKOV(J)-PPCKOV(J-1))*
     +                     Q(JCURIN+J)
            ELSE
               Q(JCURIN+J)=0.
            ENDIF
         ENDIF
   10 CONTINUE
*
  999 END
*CMZ :  3.21/02 29/03/94  15.41.22  by  S.Giani
*-- Author :
      SUBROUTINE GPHOT
C.
C.    ******************************************************************
C.    *                                                                *
C.    *  GENERATES PHOTO ELECTRIC MECHANISM                            *
C.    *  Corrected version of L. Urban's routine.                      *
C.    *  Improvements:                                                 *
C.    *    1. Angular distributions of photoelectrons from K-L3 shells *
C.    *    2. Generation of shell decay mode                           *
C.    *    3. Probability of interactioon with a shell = function      *
C.    *       of photon energy                                         *
C.    *                                                                *
C.    *    ==>CALLED BY : GTGAMA                                       *
C.    *       AUTHOR    : J. Chwastowski                               *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
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
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
      REAL          CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCUNIT.
      COMMON/GCUNIT/LIN,LOUT,NUNITS,LUNITS(5)
      INTEGER LIN,LOUT,NUNITS,LUNITS
      COMMON/GCMAIL/CHMAIL
      CHARACTER*132 CHMAIL
C
*KEND.
      DIMENSION POT(4),PROB(4),RNA(9)
      EQUIVALENCE (RNA(1),RN01),(RNA(2),RN02),(RNA(3),RN03)
      EQUIVALENCE (RNA(4),RN04),(RNA(5),RN05),(RNA(6),RN06)
      EQUIVALENCE (RNA(7),RN07),(RNA(8),RN08),(RNA(9),RN09)
      EQUIVALENCE (POT(1),POTK),(POT(2),POTL1)
      EQUIVALENCE (POT(3),POTL2),(POT(4),POTL3)
      EQUIVALENCE (PROB(1),PROBK),(PROB(2),PROBL1)
      EQUIVALENCE (PROB(3),PROBL2),(PROB(4),PROBL3)
      SAVE ZINOLD,POT,NSHELL
      DATA ZINOLD / 0.0 /
C.
C.    ------------------------------------------------------------------
C.
      KCASE = NAMEC(8)
C
C             STOP ELECTRON ?
C
C Check if the photoelectric effect was activated. If not deposit
C gamma & return
      IF(IPHOT.NE.1) THEN
         ISTOP = 2
         NGKINE= 0
         DESTEP = DESTEP + VECT(7)
         VECT(7) = 0.
         GEKIN = 0.
         GETOT = 0.
      ELSE
         E=VECT(7)
         CALL GRNDM(RNA,9)
         JPHXS = LQ(JPHOT-1)
         NZ = Q(JPHXS+1)
         IF(NZ.GT.1) THEN
            QS = 0.0
            QS2 = GPHSG1(E)*RN01
            DO 10 I = 1,NZ-1
               QS1 = GPHSGP(I,E)
               QS = QS+QS1
               IF(QS2.LE.QS) THEN
                  K = I
                  GO TO 20
               ENDIF
   10       CONTINUE
            K = NZ
   20       CONTINUE
            JPHFN = LQ(JPHXS-K)
            NUSED = Q(JPHFN+1)*5+1
            JFN = JPHFN+NUSED
            ZINT = Q(JPHXS+1+K)
         ELSE
            JPHFN = LQ(JPHXS-1)
            NUSED = Q(JPHFN+1)*5+1
            JFN = JPHFN+NUSED
            ZINT = Q(JPHXS+1+1)
         ENDIF
C COPY SHELLS POTENTIALS FROM THE ZEBRA STUCTURE
C Check if this atom was used in last entry
         IF(ZINT.NE.ZINOLD) THEN
            NSHELL = Q(JFN+1)
            DO 30 I = 1,NSHELL
               POT(I) = Q(JFN+1+I)
   30       CONTINUE
            ZINOLD = ZINT
         ENDIF
C Check if E-gamma is bigger than the L3 ionization potential.
C This will make GPHOT a little faster.
         ISHELL = 0
         PROB(1) = 0.
         PROB(2) = 0.
         PROB(3) = 0.
         PROB(4) = 0.
         IF(E.GE.POTL3) THEN
C If ZINT < 5 we can have K shell only, so
            IF(ZINT.LT.5) THEN
               IF(E.GT.POTK) THEN
                  PROBK = 1.
                  TK = E-POTK
                  ISHELL = 1
               ENDIF
            ELSE
C The probabilities given below come from crude approximation
C It uses the jump ratios and assumes that they are valid for the whole energy
C range.
               IF(E.LT.POTL2) THEN
                  PROBL3 = 1.0
                  TK = E-POTL3
                  ISHELL = 4
               ELSE
                  E3 = E-POTL3
                  GAMAL3 = E3/EMASS+1.
                  BETAL3 = SQRT(E3*(E3+2.0*EMASS))/(E+EMASS)
                  E2 = E-POTL2
                  GAMAL2 = E2/EMASS+1.
                  BETAL2 = SQRT(E2*(E2+2.0*EMASS))/(E+EMASS)
                  EFRAC = EMASS/E
                  PROBL3 = GAVRL3(GAMAL3,BETAL3,EFRAC)
                  PROBL2 = GAVRL2(GAMAL2,BETAL2,EFRAC)
                  ANOR = 1./(PROBL3+PROBL2)
                  PROBL3 = PROBL3*ANOR
                  PROBL2 = PROBL2*ANOR
                  IF(E.LT.POTL1) THEN
                     IF(RN02.LT.PROBL3) THEN
                        ISHELL = 4
                        TK = E-POTL3
                     ELSE
                        ISHELL = 3
                        TK = E-POTL2
                     ENDIF
                  ELSE
C Parametrization of L1 jump ratio gives constant 1.2
                     PROBL1 = 1.-1./1.2
                     IF(E.LT.POTK) THEN
                        PROBL2 = (1.-PROBL1)*PROBL2
                        PROBL3 = (1.-PROBL1)*PROBL3
                     ELSE
                        PROBK = 125./ZINT+3.5
                        PROBK = 1.-1/PROBK
                        PROBL1 = (1.-PROBK)*PROBL1
                        PROBL2 = (1.-PROBK-PROBL1)*PROBL2
                        PROBL3 = (1.-PROBK-PROBL1)*PROBL3
                     ENDIF
                     IF(POTL3.LE.0.0) PROBL3 = 0.0
                     IF(POTL2.LE.0.0) PROBL2 = 0.0
                     IF(POTL1.LE.0.0) PROBL1 = 0.0
                     ANOR = PROBK+PROBL1+PROBL2+PROBL3
                     IF(ANOR.GT.0.0) THEN
                        ANOR = 1./ANOR
                        PROBK = PROBK*ANOR
                        PROBL1 = PROBL1*ANOR+PROBK
                        PROBL2 = PROBL2*ANOR+PROBL1
                        PROBL3 = PROBL3*ANOR+PROBL2
                        ISHELL = 4
                        TK = E-POTL3
                        IF(RN02.LE.PROBK) THEN
                           ISHELL = 1
                           TK = E-POTK
                        ELSEIF(RN02.LE.PROBL1) THEN
                           ISHELL = 2
                           TK = E-POTL1
                        ELSEIF(RN02.LE.PROBL2) THEN
                           ISHELL = 3
                           TK = E-POTL2
                        ENDIF
                     ENDIF
                  ENDIF
               ENDIF
            ENDIF
            IF(TK.LE.CUTELE) ISHELL = -ISHELL
         ENDIF
         IF(ISHELL.LT.1) THEN
C None of the shells was chosen because of the CUTELE
            ISTOP = 2
            IF(ISHELL.LT.0) THEN
               DESTEP = DESTEP+TK
            ELSEIF(ISHELL.EQ.0) THEN
               DESTEP = DESTEP+VECT(7)
            ENDIF
            NGKINE= 0
            VECT(7) = 0.
            GEKIN = 0.
            GETOT = 0.
         ELSE
C
C             ENERGY AND MOMENTUM OF PHOTOELECTRON
C
            EEL=TK + EMASS
            PEL=SQRT((TK+2.*EMASS)*TK)
            BETA = PEL/EEL
            ISTOP = 1
            NGKINE = 1
            IF(ISHELL.EQ.1) THEN
               COST = GPHAK(BETA)
            ELSEIF(ISHELL.EQ.2) THEN
               COST = GPHAL1(BETA)
            ELSEIF(ISHELL.EQ.3) THEN
               COST = GPHAL2(BETA)
            ELSEIF(ISHELL.EQ.4) THEN
               COST = GPHAL3(BETA)
            ENDIF
            PHI = TWOPI*RN03
            COSPHI = COS(PHI)
            SINPHI = SIN(PHI)
            SINT = SQRT((1.-COST)*(1.+COST))
            GKIN(1,NGKINE) = PEL*SINT*COSPHI
            GKIN(2,NGKINE) = PEL*SINT*SINPHI
            GKIN(3,NGKINE) = PEL*COST
            GKIN(4,NGKINE) = EEL
            GKIN(5,NGKINE) = 3.
            TOFD(NGKINE) = 0
            GPOS(1,NGKINE) = VECT(1)
            GPOS(2,NGKINE) = VECT(2)
            GPOS(3,NGKINE) = VECT(3)
C
C             ROTATE ELECTRON AND SCATTERED PHOTON INTO GEANT SYSTEM
C
            CALL GVROT(VECT(4),GKIN)
         ENDIF
         IF(ISHELL.NE.0) THEN
            ISHELL = ABS(ISHELL)
            IF(ZINT.GE.5.AND.POT(ISHELL).GT.MIN(CUTGAM,CUTELE)) THEN
C Generate shell decay mode
               IF(RN04.LE.Q(JFN+1+NSHELL+ISHELL)) THEN
                  IF(POT(ISHELL).LE.CUTGAM) THEN
                     DESTEP = DESTEP+POT(ISHELL)
                  ELSE
C Radiative shell decay
                     JS = JFN+1+2*NSHELL+ISHELL
                     JS = JPHFN+Q(JS)
                     NPOINT = Q(JS)
                     DO 40 I = 1,NPOINT
                        IF(RN05.LT.Q(JS+I)) THEN
                           TSEC = Q(JS+NPOINT+I)
                           IF(TSEC.GT.CUTGAM) THEN
                              NGKINE = NGKINE+1
                              PHI = TWOPI*RN06
                              COST = 2.*RN07-1.
                              COSPHI = COS(PHI)
                              SINPHI = SIN(PHI)
                              SINT = SQRT((1.-COST)*(1.+COST))
                              GKIN(1,NGKINE) = TSEC*SINT*COSPHI
                              GKIN(2,NGKINE) = TSEC*SINT*SINPHI
                              GKIN(3,NGKINE) = TSEC*COST
                              GKIN(4,NGKINE) = TSEC
                              GKIN(5,NGKINE) = 1.
                              TOFD(NGKINE) = 0.
                              GPOS(1,NGKINE) = VECT(1)
                              GPOS(2,NGKINE) = VECT(2)
                              GPOS(3,NGKINE) = VECT(3)
                           ELSE
                              DESTEP = DESTEP+ABS(TSEC)
                           ENDIF
C The following particle forces the energy conservation
                           TSEC = POT(ISHELL)-ABS(TSEC)
                           IF(TSEC.GT.CUTGAM) THEN
                              NGKINE = NGKINE+1
                              PHI = TWOPI*RN08
                              COST = 2.*RN09-1.
                              COSPHI = COS(PHI)
                              SINPHI = SIN(PHI)
                              SINT = SQRT((1.-COST)*(1.+COST))
                              GKIN(1,NGKINE) = TSEC*SINT*COSPHI
                              GKIN(2,NGKINE) = TSEC*SINT*SINPHI
                              GKIN(3,NGKINE) = TSEC*COST
                              GKIN(4,NGKINE) = TSEC
                              GKIN(5,NGKINE) = 1.
                              TOFD(NGKINE) = 0.
                              GPOS(1,NGKINE) = VECT(1)
                              GPOS(2,NGKINE) = VECT(2)
                              GPOS(3,NGKINE) = VECT(3)
                           ELSE
                              DESTEP = DESTEP+TSEC
                           ENDIF
                           GO TO 50
                        ENDIF
   40                CONTINUE
   50                CONTINUE
                  ENDIF
               ELSE
                  IF(POT(ISHELL).LE.CUTELE) THEN
                     DESTEP = DESTEP+POT(ISHELL)
                  ELSE
c Nonradiative decay
                     JS = JFN+1+3*NSHELL+ISHELL
                     JS = JPHFN+Q(JS)
                     NPOINT = Q(JS)
                     DO 60 I = 1,NPOINT
                        IF(RN05.LT.Q(JS+I)) THEN
                           TSEC = Q(JS+NPOINT+I)
                           IF(TSEC.GT.CUTELE) THEN
                              EEL=TSEC + EMASS
                              PEL=SQRT((TSEC+2.*EMASS)*TSEC)
                              NGKINE = NGKINE+1
                              PHI = TWOPI*RN06
                              COST = 2.*RN07-1.
                              COSPHI = COS(PHI)
                              SINPHI = SIN(PHI)
                              SINT = SQRT((1.-COST)*(1.+COST))
                              GKIN(1,NGKINE) = PEL*SINT*COSPHI
                              GKIN(2,NGKINE) = PEL*SINT*SINPHI
                              GKIN(3,NGKINE) = PEL*COST
                              GKIN(4,NGKINE) = EEL
                              GKIN(5,NGKINE) = 3.
                              TOFD(NGKINE) = 0.
                              GPOS(1,NGKINE) = VECT(1)
                              GPOS(2,NGKINE) = VECT(2)
                              GPOS(3,NGKINE) = VECT(3)
                           ELSE
                              DESTEP = DESTEP+ABS(TSEC)
                           ENDIF
C The following particle forces the energy conservation
                           TSEC = POT(ISHELL)-ABS(TSEC)
                           IF(TSEC.GT.CUTGAM) THEN
                              NGKINE = NGKINE+1
                              PHI = TWOPI*RN08
                              COST = 2.*RN09-1.
                              COSPHI = COS(PHI)
                              SINPHI = SIN(PHI)
                              SINT = SQRT((1.-COST)*(1.+COST))
                              GKIN(1,NGKINE) = TSEC*SINT*COSPHI
                              GKIN(2,NGKINE) = TSEC*SINT*SINPHI
                              GKIN(3,NGKINE) = TSEC*COST
                              GKIN(4,NGKINE) = TSEC
                              GKIN(5,NGKINE) = 1.
                              TOFD(NGKINE) = 0.
                              GPOS(1,NGKINE) = VECT(1)
                              GPOS(2,NGKINE) = VECT(2)
                              GPOS(3,NGKINE) = VECT(3)
                           ELSE
                              DESTEP = DESTEP+TSEC
                           ENDIF
                           GO TO 70
                        ENDIF
   60                CONTINUE
   70                CONTINUE
                  ENDIF
               ENDIF
            ELSE
               DESTEP = DESTEP+POT(ISHELL)
            ENDIF
         ENDIF
      ENDIF
      END
*CMZ :  1.40/05 25/03/98  12.07.16  by  Pavel Nevski
*CMZ :  3.21/03 14/09/94  14.33.42  by  S.Ravndal
*-- Author :
      SUBROUTINE GPART
C.
C.    *******************************************************************
C.    *                                                                 *
C.    *  Define standard GEANT particles plus selected decay modes      *
C.    *  and branching ratios.                                          *
C.    *                                                                 *
C.    *  All data taken from : M. AGUILAR-BENITEZ et al,                *
C.    *                        Review of Particle Properties,           *
C.    *                        Rev. Mod. Phys. 56(1984).                *
C.    *                                                                 *
C.    *  Updated to:           Phys.Rev. D50,1173(1994)                 *
C.    *                        S. Ravndal                               *
C.    *  PN: activate paricles from Geant 3.16 with crude decay guess   *
C.    *                                                                 *
C.    *  In the case of W and Z, the lifetimes are calculated from      *
C.    *  quoted upper limits on widths.                                 *
C.    *                                                                 *
C.    *  NPAR           Number of parent particles defined for decay.   *
C.    *  IPAR           List of parent partilces allowed to decay.      *
C.    *                 Currently set up for pi0,pi+,pi-,K0long,K+,K-,  *
C.    *                 K0short,eta,lambda,sigma+,sigma0,sigma-,xi0,    *
C.    *                 xi-,omega-,antilambda,antisigma -,antisigma 0,  *
C.    *                 antisigma +,antixi 0,antixi +,antiomega +       *
C.    *                 decays.                                         *
C.    *  MODE(I,J)      I'th decay mode of J'th particle defined in     *
C.    *                 IPAR.                                           *
C.    *  BRATIO(I,J)    Branching ratio for I'th decay mode of J'th     *
C.    *                 particle in IPAR.                               *
C.    *                                                                 *
C.    *    ==>Called by : <USER>, UGINIT                                *
C.    *       Author    G.Patrick  *********                            *
C.    *                                                                 *
C.    *******************************************************************
C.
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
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEND.
C                       do not activate additional decays
      DATA     NPAR/24/
      INTEGER  IPAR(36),UBUF(1)
      REAL     BRATIO(6,36),BRTIO1(6,20),BRTIO2(6,16)
      INTEGER  MODE(6,36),  MODE1(6,20), MODE2(6,16)
      DATA     UBUF/0./
C
      EQUIVALENCE(BRTIO1(1,1),BRATIO(1,1)),(BRTIO2(1,1),BRATIO(1,21))
      EQUIVALENCE(MODE1(1,1), MODE(1,1)),  (MODE2(1,1), MODE(1,21))
C
      DATA IPAR/ 7, 8, 9,10,11,12,16,17,18,19,20,
     *          21,22,23,24,26,27,28,29,30,31,32,5,6,
     *          33,34,35,36,37,38,39,40,41,42,43,44/
      DATA BRTIO1/ 98.802, 1.198, 0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *             21.60, 19.35, 19.35, 13.50, 13.50, 12.38,
     *             63.51, 21.17,  5.59,  4.82,  3.18,  1.73,
     *             63.51, 21.17,  5.59,  4.82,  3.18,  1.73,
     *             68.61, 31.39,  0.,    0.,    0.,    0.,
     *             38.80, 31.90, 23.6,   4.88,  0.5,   0.071,
     *             63.90, 35.80,  0.,    0.,    0.,    0.,
     *             51.57, 48.30,  0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *             67.80, 23.60,  8.60,  0.,    0.,    0.,
     *             63.90, 35.80,  0.,    0.,    0.,    0.,
     *             51.57, 48.30,  0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0./
      DATA BRTIO2/100.00,  0.,    0.,    0.,    0.,    0.,
     *             67.80, 23.60,  8.60,  0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            100.00,  0.,    0.,    0.,    0.,    0.,
     *            25.2,  17.65, 18.01,  11.7,  13.0,  13.0,
     *            25.2,  17.65, 18.01,  11.7,  13.0,  13.0,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            100.0,   0.,    0.,    0.,    0.,    0.,
     *            63.90, 35.80,   0.,    0.,    0.,    0.,
     *            10.8,  10.6,  10.8,  67.8,    0.,    0.,
     *            10.8,  10.6,  10.8,  67.8,    0.,    0.,
     *            3.37,  3.37,  3.36,  69.9,  20.01,   0./
 
      DATA MODE1/  101,30201,    0,    0,    0,    0,
     *             405,    0,    0,    0,    0,    0,
     *             406,    0,    0,    0,    0,    0,
     *             70707,40308,40209,40608,40509,70908,
     *             405,  708,90808,70402,70405,70708,
     *             406,  709,80909,70403,70406,70709,
     *             908,  707,    0,    0,    0,    0,
     *             101,70707,70908,10908,10302,10107,
     *             914,  713,    0,    0,    0,    0,
     *             714,  813,    0,    0,    0,    0,
     *             118,    0,    0,    0,    0,    0,
     *             913,    0,    0,    0,    0,    0,
     *             718,    0,    0,    0,    0,    0,
     *             918,    0,    0,    0,    0,    0,
     *            1218,  922,  723,    0,    0,    0,
     *             815,  725,    0,    0,    0,    0,
     *             715,  925,    0,    0,    0,    0,
     *             126,    0,    0,    0,    0,    0,
     *             825,    0,    0,    0,    0,    0,
     *             726,    0,    0,    0,    0,    0/
      DATA MODE2/  826,    0,    0,    0,    0,    0,
     *            1126,  830,  731,    0,    0,    0,
     *           40402,    0,    0,    0,    0,    0,
     *           40403,    0,    0,    0,    0,    0,
     *          080704, 050404, 020404, 0804, 090808, 080707,     !Tau+
     *          090704, 060404, 030404, 0904, 090908, 090707,     !Tau-
     *            1608,    0,    0,    0,    0,    0,             !D+->K0s+pi
     *            1609,    0,    0,    0,    0,    0,             !D_->K0s+pi
     *            1208,    0,    0,    0,    0,    0,             !D0->K_+pi+
     *            1109,    0,    0,    0,    0,    0,             !D0->K++pi_
     *            1608,    0,    0,    0,    0,    0,             !Ds+->K0s+pi
     *            1609,    0,    0,    0,    0,    0,             !Ds_->K0s+pi
     *            141208,180807, 0,    0,    0,    0,             !Lc+
     *            0204,  0604, 3304, 90908,  0,    0,             !W+
     *            0304,  0504, 3404, 90908,  0,    0,             !W-
     *            0203,  0506, 3334, 90807, 0404,  0/             !Z
C.
C.    -------------------------------------------------------------------
C.
      REMASS=EMASS
      REMMU =EMMU
      RPMASS=PMASS
      CALL GSPART( 1,'GAMMA$      ',1,0.       , 0., 1.E+15,    UBUF,0)
      CALL GSPART( 2,'POSITRON$   ',2,REMASS   , 1., 1.E+15,    UBUF,0)
      CALL GSPART( 3,'ELECTRON$   ',2,REMASS   ,-1., 1.E+15,    UBUF,0)
      CALL GSPART( 4,'NEUTRINO$   ',3,0.       , 0., 1.E+15,    UBUF,0)
      CALL GSPART( 5,'MUON +$     ',5,REMMU    , 1., 2.19703e-6,UBUF,0)
      CALL GSPART( 6,'MUON -$     ',5,REMMU    ,-1., 2.19703e-6,UBUF,0)
      CALL GSPART( 7,'PION 0$     ',3,0.1349764, 0., 0.84E-16,  UBUF,0)
      CALL GSPART( 8,'PION +$     ',4,0.1395700, 1., 2.603E-08, UBUF,0)
      CALL GSPART( 9,'PION -$     ',4,0.1395700,-1., 2.603E-08, UBUF,0)
      CALL GSPART(10,'KAON 0 LONG$',3,0.497672 , 0., 5.17E-08,  UBUF,0)
      CALL GSPART(11,'KAON +$     ',4,0.493677 , 1., 1.237E-08, UBUF,0)
      CALL GSPART(12,'KAON -$     ',4,0.493677 ,-1., 1.237E-08, UBUF,0)
      CALL GSPART(13,'NEUTRON$    ',3,.93956563, 0., 8.870E+02, UBUF,0)
      CALL GSPART(14,'PROTON$     ',4,RPMASS   , 1., 1.000e+15, UBUF,0)
      CALL GSPART(15,'ANTIPROTON$ ',4,RPMASS   ,-1., 1.000e+15, UBUF,0)
      CALL GSPART(16,'KAON 0 SHORT$',3,0.497672, 0., 8.926E-11, UBUF,0)
      CALL GSPART(17,'ETA$        ',3,0.54745  , 0., 5.485E-19, UBUF,0)
      CALL GSPART(18,'LAMBDA$     ',3,1.115684 , 0., 2.632E-10, UBUF,0)
      CALL GSPART(19,'SIGMA +$    ',4,1.18937  , 1., 0.799E-10, UBUF,0)
      CALL GSPART(20,'SIGMA 0$    ',3,1.19255  , 0., 7.4E-20,   UBUF,0)
      CALL GSPART(21,'SIGMA -$    ',4,1.197436 ,-1., 1.479E-10, UBUF,0)
      CALL GSPART(22,'XI 0$       ',3,1.3149   , 0., 2.9E-10,   UBUF,0)
      CALL GSPART(23,'XI -$       ',4,1.32132  ,-1., 1.639E-10, UBUF,0)
      CALL GSPART(24,'OMEGA -$    ',4,1.67245  ,-1., 0.822E-10, UBUF,0)
      CALL GSPART(25,'ANTINEUTRON$',3,.93956563, 0., 8.870E+02, UBUF,0)
      CALL GSPART(26,'ANTILAMBDA$ ',3,1.115684 , 0., 2.632E-10, UBUF,0)
      CALL GSPART(27,'ANTISIGMA -$',4,1.18937  ,-1., 0.799E-10, UBUF,0)
      CALL GSPART(28,'ANTISIGMA 0$',3,1.19255  , 0., 7.4E-20,   UBUF,0)
      CALL GSPART(29,'ANTISIGMA +$',4,1.197436 , 1., 1.479E-10, UBUF,0)
      CALL GSPART(30,'ANTIXI 0$   ',3,1.3149   , 0., 2.9E-10,   UBUF,0)
      CALL GSPART(31,'ANTIXI +$   ',4,1.32132  , 1., 1.639E-10, UBUF,0)
      CALL GSPART(32,'ANTIOMEGA +$',4,1.67245  , 1., 0.822E-10, UBUF,0)
      CALL GSPART(33,'TAU +$      ',4,1.7771   , 1., 2.956e-13, UBUF,0)
      CALL GSPART(34,'TAU -$      ',4,1.7771   ,-1., 2.956e-13, UBUF,0)
      CALL GSPART(35,'D +$        ',4,1.8694   , 1., 1.062e-12, UBUF,0)
      CALL GSPART(36,'D -$        ',4,1.8694   ,-1., 1.062e-12, UBUF,0)
      CALL GSPART(37,'D 0$        ',3,1.8646   , 0., 4.280e-13, UBUF,0)
      CALL GSPART(38,'ANTI D 0$   ',3,1.8646   , 0., 4.280e-13, UBUF,0)
      CALL GSPART(39,'DS+$        ',4,1.9685   , 1., 4.360e-13, UBUF,0)
      CALL GSPART(40,'DS-$        ',4,1.9685   ,-1., 4.360e-13, UBUF,0)
      CALL GSPART(41,'LAMBDA C +$ ',4,2.2851   , 1., 1.790e-13, UBUF,0)
      CALL GSPART(42,'W +$        ',4,80.220   , 1., 3.160e-25, UBUF,0)
      CALL GSPART(43,'W -$        ',4,80.220   ,-1., 2.640e-25, UBUF,0)
      CALL GSPART(44,'Z 0$        ',3,91.187   , 0., 7.740e-26, UBUF,0)
      CALL GSPART(45,'DEUTERON$   ',8,1.875613 ,+1., 1.000e+15, UBUF,0)
      CALL GSPART(46,'TRITON$     ',8,2.80925  ,+1., 1.000e+15, UBUF,0)
      CALL GSPART(47,'ALPHA$      ',8,3.727417 ,+2., 1.000e+15, UBUF,0)
      CALL GSPART(48,'GEANTINO$   ',6,0.       , 0., 1.000e+15, UBUF,0)
      CALL GSPART(49,'HE3$        ',8,2.80923  ,+2., 1.000e+15, UBUF,0)
      CALL GSPART(50,'Cerenkov$   ',7,0.       , 0., 1.000e+15, UBUF,0)
c     CALL GSPART(51,'phi$        ',3,1.019    , 0., 1.000e-15, UBUF,0)
c     CALL GSPART(52,'J/psi$      ',3,3.09688  , 0., 1.000e-15, UBUF,0)
c     CALL GSPART(53,'Ypsilon$    ',3,9.46037  , 0., 1.000e-15, UBUF,0)
 
C
C     Define decay modes.
C
      DO 10 I=1,NPAR
      CALL GSDK(IPAR(I),BRATIO(1,I),MODE(1,I))
   10 CONTINUE
C
  99  RETURN
      END
 
 
 
*CMZ :  1.40/05 06/04/98  12.37.16  by  Pavel Nevski
*CMZ :  3.21/04 13/12/94  15.29.27  by  S.Giani
*-- Author :
      SUBROUTINE GGCLOS
C.
C.    ******************************************************************
C.    *                                                                *
C.    *    Closes off the geometry setting.                            *
C.    *    Initializes the search list for the contents of each        *
C.    *    volume following the order they have been positioned, and   *
C.    *    inserting the content '0' when a call to GSNEXT (-1) has    *
C.    *    been required by the user.                                  *
C.    *    Performs the development of the JVOLUM structure for all    *
C.    *    volumes with variable parameters, by calling GGDVLP.        *
C.    *    Interprets the user calls to GSORD, through GGORD.          *
C.    *    Computes and stores in a bank (next to JVOLUM mother bank)  *
C.    *    the number of levels in the geometrical tree and the        *
C.    *    maximum number of contents per level, by calling GGNLEV.    *
C.    *    Sets status bit for CONCAVE volumes, through GGCAVE.        *
C.    *    Completes the JSET structure with the list of volume names  *
C.    *    which identify uniquely a given physical detector, the      *
C.    *    list of bit numbers to pack the corresponding volume copy   *
C.    *    numbers, and the generic path(s) in the JVOLUM tree,        *
C.    *    through the routine GHCLOS.                                 *
C.    *                                                                *
C.    *    Called by : <USER>                                          *
C.    *    Authors   : R.Brun, F.Bruyant, S.Giani  *********           *
C.    *                                                                *
C.    *    Modified by S.Giani for automatic initialization of the new *
C.    *    tracking based on virtual divisions (1993).                 *
C.    *    PN: reset tmpmax (for CRAY)                                 *
C.    ******************************************************************
C.
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
*KEEP,GCLIST.
      COMMON/GCLIST/NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     +       ,NSTAT,LHSTA(20),LGET (20),LSAVE(20),LSETS(20),LPRIN(20)
     +             ,LGEOM(20),LVIEW(20),LPLOT(20),LSTAT(20)
C
      INTEGER       NHSTA,NGET ,NSAVE,NSETS,NPRIN,NGEOM,NVIEW,NPLOT
     + ,NSTAT,LHSTA,LGET ,LSAVE,LSETS,LPRIN,LGEOM,LVIEW,LPLOT,LSTAT
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
*KEEP,GCOPTI.
      COMMON/GCOPTI/ IOPTIM
C
      INTEGER IOPTIM
*KEEP,GCHVIR.
      COMMON/GCHVIR/JVIRT,JVDIV,JCONT2,JCONT
C
      INTEGER JVIRT,JVDIV,JCONT2,JCONT
C
*KEND.
      CHARACTER*4 NAME
      LOGICAL BTEST
C.
C.    ------------------------------------------------------------------
      dimension dx(3),tmpmax(7),ndivto(7),qualit(7),ivoaxi(7)
      data jfirst/0/
      save jfirst
      COMMON /QUEST/ IQUEST(100)
      COMMON/GCDINA/jphi2,jclow,jchig,jbuff
*
* *** Stop the run in case of serious anomaly during initialization
*
      IF (IEORUN.NE.0) THEN
         WRITE (CHMAIL, 1001)
         CALL GMAIL (0, 0)
         STOP
      ENDIF
*
      IF (NVOLUM.LE.0) THEN
         WRITE (CHMAIL, 1002) NVOLUM
         CALL GMAIL (0, 0)
         GO TO 999
      ENDIF
*
      NPUSH = NVOLUM -IQ(JVOLUM-2)
      CALL MZPUSH (IXCONS, JVOLUM, NPUSH, NPUSH,'I')
*
* *** Loop over volumes, create default JNear banks as relevant,
*      and release unused bank space
*
      IDO = 0
      DO 80 IVO = 1,NVOLUM
         JVO = LQ(JVOLUM-IVO)
*
* *** Check if Tracking medium has been defined
*
         NMED=Q(JVO+4)
         IF(NMED.LE.0.OR.NMED.GT.IQ(JTMED-2))THEN
            WRITE(CHMAIL,1003)IQ(JVOLUM+IVO)
            CALL GMAIL (0, 0)
         ELSE
            IF(LQ(JTMED-NMED).EQ.0)THEN
               WRITE(CHMAIL,1003)IQ(JVOLUM+IVO)
               CALL GMAIL (0, 0)
            ENDIF
         ENDIF
         IF (BTEST(IQ(JVO),0)) GO TO 80
         IDO = 1
         IQ(JVO) = IBSET(IQ(JVO),0)
         NINL  = IQ(JVO-2)
         NIN   = Q(JVO+3)
         NUSED = IABS(NIN)
         IF (NIN.GT.0) THEN
*           reserve enough additional space for sorted volumes
            IF(NIN.LE.1.OR.NIN.GT.500.OR.IOPTIM.LT.0)THEN
              NUSED=NUSED+1
            ELSE
              NUSED=NUSED+2
            ENDIF
         ENDIF
*
         NPUSH = NUSED -NINL
         DO 90 IN=NINL,NUSED+1,-1
            JIN = LQ(JVO-IN)
            IF(JIN.GT.0) THEN
               CALL MZDROP(IXCONS,JIN,'L')
            ENDIF
  90     CONTINUE
         CALL MZPUSH (IXCONS, JVO, NPUSH, 0, 'I')
         IF (NIN.LE.0) GO TO 80
*
         IF(BTEST(IQ(JVO),3)) THEN
            IZERO=1
         ELSE
            IZERO=0
         ENDIF
         NEL = NIN +IZERO
         JN = LQ(JVO-NIN-1)
         IF(JN.EQ.0) THEN
            CALL MZBOOK (IXCONS,JN,JVO,-NIN-1,'VONE',0,0,NEL+1,2,0)
         ENDIF
         IQ(JN-5) = IVO
         IQ(JN+1) = NEL
         JN = JN +1
         DO 29 I = 1,NIN
            IQ(JN+IZERO+I) = I
   29    CONTINUE
         IF (IZERO.NE.0) IQ(JN+1) = 0
*
   80 CONTINUE
*
      IF (IDO.NE.0) THEN
*
* ***    Perform development of JVOLUM structure where necessary
*
         CALL GGDVLP
*
* ***    Fill GSORD ordering banks if required
*
* Modified by S.Egli to allow GGORDQ to find the optimum sorting for
* all volumes
*
         IF(IOPTIM.GE.1)THEN
            WRITE(6,'(A)')' GGCLOS: Start automatic volume ordering:'
         ENDIF
         DO 91 IVO = 1,NVOLUM
            JVO = LQ(JVOLUM-IVO)
            NIN = Q(JVO+3)
            ISEARC=Q(JVO+1)
            IF(ISEARC.GT.0) GO TO 91
*           check if sorting not possible or not wanted
            IF(NIN.LE.1.OR.NIN.GT.500.OR.IOPTIM.LT.0)THEN
               Q(JVO+1)=0.
               IF(NIN.GT.500.AND.IOPTIM.GE.1)THEN
                 CALL UHTOC(IQ(JVOLUM+IVO),4,NAME,4)
                 WRITE (CHMAIL,1004) NAME,NIN
                 CALL  GMAIL (0, 0)
               ENDIF
            ELSEIF(IOPTIM.EQ.0)THEN
               IF(ISEARC.LT.0)CALL GGORD (IVO)
            ELSEIF(IOPTIM.EQ.1)THEN
               IF(ISEARC.EQ.0) THEN
                  CALL GGORDQ(IVO)
               ELSE
                  CALL GGORD (IVO)
               END IF
            ELSE
               CALL GGORDQ(IVO)
            ENDIF
   91    CONTINUE
*
* ***    Set status bit for concave volumes
*
         CALL GGCAVE
*
* ***    Compute maximum number of levels and of contents per level
*
         CALL GGNLEV
*
      ENDIF
*
********************************************************************************
*
      if(jfirst.eq.0)then
        jfirst=1
        call mzlink(ixcons,'/GCHVIR/',jvirt,jvdiv,jcont)
        call mzlink(ixstor,'/GCDINA/',jphi2,jbuff,jphi2)
      endif
      jflag=0
      nwjvdi=0
      jphi2=0
      jclow=0
      jchig=0
      jbuff=0
      if(jvirt.ne.0)call mzdrop(ixcons,jvirt,' ')
      nwjvir=5*nvolum+20
      call mzneed(ixcons,nwjvir,'G')
      if(iquest(11).lt.0)then
          print *,'No space for jvirt bank'
      else
          call mzbook(ixcons,jvirt,jvirt,1,'VIRT',nvolum,nvolum,
     +              4*nvolum+20,0,0)
      endif
      dx(1)=0.
      dx(2)=0.
      dx(3)=0.
      ndivst=0
      ndioff=0
      ninmax=0
      do 101 ivo=1,nvolum
        jvo=lq(jvolum-ivo)
        call uhtoc(iq(jvolum+ivo),4,NAME,4)
*         print *,'VOLUME ',NAME
*         print *,' '
        nin=q(jvo+3)
        isearc=q(jvo+1)
*        if(nin.eq.0)then
*          print *,'No daughters.'
*        elseif(nin.lt.0)then
*          print *,'Divided volume.'
*        elseif(nin.le.1)then
*          print *,'Only 1 daughter.'
*        endif
 1      continue
        if(nin.gt.1)then
         if(jflag.eq.0)then
          if(iswit(9).eq.12345)then
            print *,'VOLUME ',NAME
            print *,' '
          endif
         endif
         if(jflag.eq.1)then
           q(jvirt+4*(ivo-1)+1)=itmpq
           iaxlo=itmpq
           iaxhi=itmpq
         else
           iaxlo=1
           iaxhi=7
         endif
          if(nin.gt.ninmax)then
           if(jphi2.ne.0)call mzdrop(ixstor,jphi2,' ')
           if(jclow.ne.0)call mzdrop(ixstor,jclow,' ')
           if(jchig.ne.0)call mzdrop(ixstor,jchig,' ')
           call mzbook(ixstor,jphi2,jphi2,2,'PHI2',0,0,
     +                 nin+20,2,-1)
           call mzbook(ixstor,jclow,jclow,2,'CLOW',0,0,
     +                 nin+20,3,-1)
           call mzbook(ixstor,jchig,jchig,2,'CHIG',0,0,
     +                 nin+20,3,-1)
           if(jflag.eq.1)then
             if(jbuff.ne.0)call mzdrop(ixstor,jbuff,' ')
             call mzbook(ixstor,jbuff,jbuff,2,'BUFF',0,0,
     +                   nin+20,2,-1)
           endif
          endif
         do 110 iaxis=iaxlo,iaxhi
          tmpmax(iaxis)=0
          myphif=0
*          print *,'Quality search for axis ',iaxis
          ish=q(jvo+2)
          if(iaxis.le.3)then
            call gvdcar(iaxis,ish,0,q(jvo+7),clmoth,chmoth,ierr)
            if(ierr.eq.1.or.(chmoth.le.clmoth))then
*              print *,'Not convenient: abandoned!',iaxis
*              print *,' '
              qualit(iaxis)=10000
              goto 110
            endif
          elseif(iaxis.le.5)then
            call gvdrad(iaxis,ish,0,dx,q(jvo+7),clmoth,chmoth,ierr)
             if(iaxis.eq.5)ierr=1
            if(ierr.eq.1.or.(chmoth.le.clmoth))then
*              print *,'Not convenient: abandoned!',iaxis
*              print *,' '
              qualit(iaxis)=10000
              goto 110
            endif
          elseif(iaxis.eq.6)then
            call gvdphi(ish,0,dx,q(jvo+7),clmoth,chmoth,ierr)
            if(ierr.eq.1.or.(chmoth.le.clmoth))then
*              print *,'Not convenient: abandoned!',iaxis
*              print *,' '
              qualit(iaxis)=10000
              goto 110
            elseif((chmoth-clmoth).gt.360..or.chmoth.gt.360)then
              print *,'(chmoth-clmoth).gt.360.or.chmoth.gt.360'
            elseif((chmoth-clmoth).eq.360.)then
              myphif=1
            endif
          elseif(iaxis.eq.7)then
            call gvdthe(ish,0,dx,q(jvo+7),clmoth,chmoth,ierr)
            ierr=1
            if(ierr.eq.1.or.(chmoth.le.clmoth))then
*              print *,'Not convenient: abandoned!',iaxis
*              print *,' '
              qualit(iaxis)=10000
              goto 110
            endif
          endif
          if(jflag.eq.1)then
            q(jvirt+4*(ivo-1)+3)=clmoth
            q(jvirt+4*(ivo-1)+4)=chmoth
          endif
          thimot=abs(chmoth-clmoth)
          thimin=100000.
          do 102 in=1,nin
            iq(jphi2+in)=0
            jin=lq(jvo-in)
            call gvdlim(jvo,in,iaxis,clow,chigh,ierr)
            if(ierr.eq.1.or.(chigh.le.clow))then
*              if(ierr.eq.0)print *,'Error in gvdlim: corrected',iaxis
              clow=clmoth
              chigh=chmoth
            elseif(myphif.eq.1)then
              clowm=clow
              chighm=chigh
              sg=sign(1.0,clow)
              clow=mod(abs(clow),360.0)
              if(chigh.ne.360.0)then
               if(sg.le.0.0)clow=360.-clow
               sg=sign(1.0,chigh)
               chigh=mod(abs(chigh),360.0)
               if(sg.le.0.0)chigh=360.-chigh
              endif
              if(chigh.lt.clow)then
                iq(jphi2+in)=1
              endif
            elseif(iaxis.eq.6.and.myphif.eq.0)then
             if((chigh-chmoth).gt..01.or.(clmoth-clow).gt..01)then
               if(clmoth.lt.0..and.clow.gt.0.)then
                clow=clow-360.
                chigh=chigh-360.
                if((chigh-chmoth).gt..01)then
                  chigh=chmoth
                  if(chigh.le.clow)clow=clmoth
                elseif((clmoth-clow).gt..01)then
                  clow=clmoth
                  if(clow.ge.chigh)chigh=chmoth
                endif
               elseif(chigh.lt.0..and.chmoth.gt.0.)then
                clow=clow+360.
                chigh=chigh+360.
                if((chigh-chmoth).gt..01)then
                  chigh=chmoth
                  if(chigh.le.clow)clow=clmoth
                elseif((clmoth-clow).gt..01)then
                  clow=clmoth
                  if(clow.ge.chigh)chigh=chmoth
                endif
               endif
             endif
            endif
            if((chigh-chmoth).gt..01)then
*** ONLY FOR DEBUG
*              print *,'iaxis =',iaxis,'protuding daughter',in
**              print *,'myphif =',myphif,'myphi2 =',iq(jphi2+in)
*              print *,'Dhigh=',chigh-chmoth
*              print *,'Dlow=',clmoth-clow
***
              chigh=chmoth
              if(chigh.le.clow)clow=clmoth
            elseif((clmoth-clow).gt..01)then
*** ONLY FOR DEBUG
*              print *,'iaxis =',iaxis,'protuding daughter',in
**              print *,'myphif =',myphif,'myphi2 =',iq(jphi2+in)
*              print *,'Dhigh=',chigh-chmoth
*              print *,'Dlow=',clmoth-clow
***
              clow=clmoth
              if(clow.ge.chigh)chigh=chmoth
            endif
            q(jclow+in)=clow
            q(jchig+in)=chigh
            if(iq(jphi2+in).eq.0)then
             tmpthi=abs(chigh-clow)
            else
             tmpthi=abs(chighm-clowm)
            endif
            if(thimin.gt.tmpthi)thimin=tmpthi
 102      continue
          if((thimin-thimot).gt.1)then
*            print *,'thimin.gt.thimot',thimin-thimot,'iax=',iaxis
            qualit(iaxis)=10000
            goto 110
          endif
          if(thimin.lt.0.04)thimin=0.04
          tmpndi=2.*thimot/thimin
          nditmp=tmpndi+1
*****          print *,nditmp,' divisions asked for ',nin,' daughters.'
*****           if(nditmp.lt.nin)then
*****             nditmp=nin
*****             print *,'Number of divisions corrected to be = ',nin
*****           endif
*****          if(nditmp.gt.1000.)print *,'1000 divisions are enough.'
          ndivto(iaxis)=min(nditmp,1000)
          if(jflag.eq.1)then
            q(jvirt+4*(ivo-1)+2)=ndivto(iaxis)
           jvdiv=lq(jvirt-ivo)
           if(jvdiv.ne.0)call mzdrop(ixcons,jvdiv,' ')
           nwvili=ndivto(iaxis)+ivoaxi(itmpq)+11
           nwjvdi=nwjvdi+nwvili
           call mzneed(ixcons,nwvili,'G')
           if(iquest(11).lt.0)then
            print *,'No space for jvdiv bank',ivo
           else
            call mzbook(ixcons,jvdiv,jvirt,-ivo,'VLIST',0,0,
     +                  nwvili,2,0)
           endif
          endif
          thisli=thimot/ndivto(iaxis)
          clslic=clmoth
          chslic=clmoth+thisli
          avelis=0.
          aveave=0.
          avesta=0.
          ii=0
          tmpmax(iaxis)=0.
          import=0
          if(jflag.eq.1)ioff=ndivto(iaxis)
          do 103 i=1,ndivto(iaxis)
            j=1
            do 104 in=1,nin
             if(iq(jphi2+in).eq.0)then
              if(q(jchig+in).ge.clslic.and.
     +           q(jclow+in).le.chslic)then
                j=j+1
                if(jflag.eq.1)then
                  iq(jbuff+j)=in
                endif
              endif
             else
              if(q(jchig+in).ge.clslic.or.
     +           q(jclow+in).le.chslic)then
                j=j+1
                if(jflag.eq.1)then
                  iq(jbuff+j)=in
                endif
              endif
             endif
 104        continue
            inbuf1=j-1
            if(jflag.eq.1)then
             if(i.gt.1.and.iq(jbuff+1).eq.(j-1))then
               if(j-1.eq.0)then
                 import=1
               elseif(j-1.eq.1)then
                 if(iq(jbuff+2).eq.iq(jvdiv+ioff-nposti+2))then
                   import=1
                 else
                   import=0
                 endif
               else
                import=1
                do 234 ijk=2,nposti-2
                 do 432 kji=2,nposti-2
                  if(iq(jbuff+ijk).eq.iq(jvdiv+ioff-nposti+kji))then
                    goto 234
                  endif
 432             continue
                 import=0
                 goto 235
 234            continue
 235            continue
               endif
               if(import.eq.1)then
                 iq(jvdiv+ioff-nposti+nposti)=i
                 iq(jvdiv+i)=ioff-nposti
                 goto 145
               endif
             else
               import=0
             endif
             iq(jbuff+1)=j-1
             nposti=j+2
             iq(jbuff+j+1)=i
             iq(jbuff+j+2)=i
             iq(jvdiv+i)=ioff
             do 144 m=1,nposti
               iq(jvdiv+ioff+m)=iq(jbuff+m)
 144         continue
             ioff=ioff+nposti
            else
             aveinc=j+2
             avesta=avesta+aveinc
            endif
 145        continue
            if(inbuf1.gt.tmpmax(iaxis))then
             tmpmax(iaxis)=inbuf1
            endif
            if(inbuf1.ne.0.)ii=ii+1
            avelis=avelis+inbuf1
            clslic=chslic
            chslic=clslic+thisli
 103      continue
          if(jflag.eq.1)then
             ndioff=ndioff+ioff
             if(iswit(9).eq.12345)then
              print *,'words booked =',nwvili,'; words used =',ioff
              print *,' '
          endif
*** ONLY FOR DEBUG
**             mymyof=0
**             do 2 mm=1,ndivto(iaxis)
**               myoff=iq(jvdiv+mm)
**              if(myoff.ne.mymyof)then
**               if(iq(jvdiv+myoff+1).eq.0)then
**                 print *,'Lower div =',iq(jvdiv+myoff+2)
**                 print *,'Upper div =',iq(jvdiv+myoff+3)
**               elseif(iq(jvdiv+myoff+1).eq.1)then
**                 print *,'Lower div =',iq(jvdiv+myoff+3)
**                 print *,'Upper div =',iq(jvdiv+myoff+4)
**               endif
**             endif
**               mymyof=iq(jvdiv+mm)
** 2           continue
***
          endif
          if(ii.eq.0)then
            print *,iaxis,'=iax: not filled divisions: error!'
            print *,' '
            aveave=10000
            avelis=10000
            goto 105
          endif
          if(jflag.eq.0)then
            ivoaxi(iaxis)=avesta
          endif
          aveave=avelis/ndivto(iaxis)
          avelis=avelis/ii
 105      continue
          qualit(iaxis)=avelis
*** ONLY FOR DEBUG
**      print *,'Max n. of objects per div = ',tmpmax(iaxis)
**      print *,'Aver. n. of obj. per not-empty div = ',avelis
**      print *,'Average n. of objects per div = ',aveave
**            print *,' '
***
 110     continue
        if(jflag.eq.0)then
         tmpq=10000
         tmpm=10000
         itmpq=0
         itmpm=0
         do 111 iaxis=1,7
          if(qualit(iaxis).lt.tmpq)then
           tmpq=qualit(iaxis)
           itmpq=iaxis
          endif
          if(tmpmax(iaxis).lt.tmpm)then
           tmpqm=tmpmax(iaxis)
           itmpm=iaxis
          endif
 111     continue
         if(iswit(9).eq.12345)then
          print *,'nin=',nin,' iax=',itmpq,' ndiv=',ndivto(itmpq)
          print *,'Max n. of objects per div = ',tmpmax(itmpq)
          print *,'Average n. of objects per div = ',tmpq
         endif
*** ONLY FOR DEBUG
**         if(isearc.lt.0)then
**           jsb=lq(lq(jvo-nin-1))
**           iaxor=q(jsb+1)
**           ndivor=q(jsb+2)-1
**           jsco=lq(jvo-nin-2)
**           tmpqor=0.
**           tmpmor=0.
**           do 133 idivor=1,ndivor
**             if(iq(jsco+idivor).gt.tmpmor)tmpmor=iq(jsco+idivor)
**             tmpqor=tmpqor+iq(jsco+idivor)
** 133       continue
**           tmpqor=tmpqor/ndivor
**           print *,'Gsord: iax=',iaxor,' ndiv=',ndivor
**           print *,'Gsord: Max n. of obj. per div = ',tmpmor
**           print *,'Gsord: Aver. n. of obj. per div = ',tmpqor
**         endif
***
         ndivst=ndivst+(ndivto(itmpq)+ndivto(itmpq)*(3.+tmpq)+10.)
         jflag=1
         goto 1
        else
          jflag=0
*** ONLY FOR DEBUG
**          print *,'nin=',nin,' iax=',q(jvirt+4*(ivo-1)+1),' ndiv=',
**     +q(jvirt+4*(ivo-1)+2)
**          ittmp=0
**          iind=q(jvirt+4*(ivo-1)+2)
**          do 155 n=1,iind
**           jvdiv=lq(jvirt-ivo)
**           iofset=iq(jvdiv+n)
**           nnobj=iq(jvdiv+iofset+1)
**           if(nnobj.gt.ittmp)ittmp=nnobj
** 155      continue
**          print *,'Max n. of objects per div = ',ittmp
**          print *,' '
**          print *,' '
***
        endif
        endif
        if(nin.gt.ninmax)ninmax=nin
 101  continue
       nwtota=ndivst+nvolum*5+10.
       if(iswit(9).eq.12345)then
        print *,'Computed number of words foreseen = ',nwtota
       endif
       nwreal=nwjvir+nwjvdi
       if(iswit(9).eq.12345)then
        print *,'Computed number of words booked = ',nwreal
       endif
       nwneed=nwjvir+ndioff
       if(iswit(9).eq.12345)then
        print *,'Computed number of words needed = ',nwneed
       endif
       if(jphi2.ne.0)call mzdrop(ixstor,jphi2,' ')
       if(jclow.ne.0)call mzdrop(ixstor,jclow,' ')
       if(jchig.ne.0)call mzdrop(ixstor,jchig,' ')
       if(jbuff.ne.0)call mzdrop(ixstor,jbuff,' ')
*
********************************************************************************
*
* *** Scan the volume structure to retrieve the path through
*      the physical tree for all sensitive detectors
*
       CALL GHCLOS
*
* *** Books STAT banks if data card STAT is submitted
*
      IF (NSTAT.GT.0)  CALL GBSTAT
*
      CALL MZGARB (IXCONS, 0)
*
 1001 FORMAT (' Severe diagnostic in initialization phase. STOP')
 1002 FORMAT (' GGCLOS : NVOLUM =',I5,' *****')
 1003 FORMAT (' Illegal tracking medium number in volume : ',A4)
 1004 FORMAT (' GGORDQ : Volume ',A4,' has more than 500 (',
     +        I3,') daughters ; volume sorting not possible !')
*                                                             END GGCLOS
  999 END
 
*CMZ :  3.21/02 29/03/94  15.41.29  by  S.Giani
*-- Author :
      SUBROUTINE GNOBOX (X, PAR, IACT, SNEXT, SNXT, SAFE)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       COMPUTE DISTANCE UP TO INTERSECTION WITH 'BOX' VOLUME,   *
C.    *        FROM OUTSIDE POINT X(1-3) ALONG DIRECTION X(4-6)        *
C.    *                                                                *
C.    *       PAR   (input)  : volume parameters                       *
C.    *       IACT  (input)  : action flag                             *
C.    *         = 0  Compute SAFE only                                 *
C.    *         = 1  Compute SAFE, and SNXT only if SNEXT .GT.new SAFE *
C.    *         = 2  Compute both SAFE and SNXT                        *
C.    *         = 3  Compute SNXT only                                 *
C.    *       SNEXT (input)  : see IACT = 1                            *
C.    *       SNXT  (output) : distance to volume boundary             *
C.    *       SAFE  (output) : shortest distance to any boundary       *
C.    *                                                                *
C.    *       ==>Called by : GNEXT, GTNEXT                             *
C.    *       Author  A.McPherson, P.Weidhaas  ******                  *
C.    * Modifications:                                                 *
C.    * 13.06.98, Tikhomirov - fix precision problem                   *
C.    ******************************************************************
C.
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEND.
      DIMENSION X(6),PAR(3),SAF(3)
      EQUIVALENCE (SAF(1),SAF1),(SAF(2),SAF2),(SAF(3),SAF3)
C.
C.    ----------------------------------------------------------------
C.
 
      SNXT = BIG
      DO 5 I=1,3
        SAF(I)=ABS(X(I))-PAR(I)
   5  CONTINUE
 
      IF (IACT .LT. 3) THEN
 
C       -------------------------------------------------
C       |  Compute safety-distance 'SAFE' (P.Weidhaas)  |
C       -------------------------------------------------
 
        SAFE  = MAX (SAF1, SAF2, SAF3, 0.0)
 
        IF (IACT .EQ. 0) GO TO 999
        IF (IACT .EQ. 1) THEN
          IF (SNEXT .LT. SAFE) GO TO 999
        ENDIF
      ENDIF
 
C     ------------------------------------------------
C     |  Compute vector-distance 'SNXT' (McPherson)  |
C     ------------------------------------------------
 
 
      IF(X(1)*X(4).GE.0.0.AND.SAF1.GT.0.) GO TO 999
      IF(X(2)*X(5).GE.0.0.AND.SAF2.GT.0.) GO TO 999
      IF(X(3)*X(6).GE.0.0.AND.SAF3.GT.0.) GO TO 999
C
      SMAX1=BIG
      SMAX2=BIG
      SMAX3=BIG
      SMIN1=0.0
C
      IF(SAF1.LT.0.) GO TO 10
      IF(X(4).EQ.0.0) GO TO 999
      S4 = ABS(X(4))
      SMIN1=SAF1 / S4
      SMAX1=(PAR(1)+ABS(X(1))) / S4
      GO TO 20
C
   10 CONTINUE
      IF(X(4).NE.0.)THEN
         SMAX1=PAR(1)/ABS(X(4))-X(1)/X(4)
      ENDIF
   20 CONTINUE
C
      SMIN2=0.0
      IF(SAF2.LT.0.) GO TO 30
      IF(X(5).EQ.0.0) GO TO 999
      S5=ABS(X(5))
      SMIN2=SAF2/S5
      SMAX2=(PAR(2)+ABS(X(2)))/S5
      GO TO 40
C
   30 CONTINUE
      IF(X(5).NE.0.)THEN
         SMAX2=PAR(2)/ABS(X(5))-X(2)/X(5)
      ENDIF
   40 CONTINUE
C
      SMIN3=0.0
      IF(SAF3.LT.0.) GO TO 50
      IF(X(6).EQ.0.0) GO TO 999
      S6=ABS(X(6))
      SMIN3=SAF3/S6
      SMAX3=(PAR(3)+ABS(X(3)))/S6
      GO TO 60
C
   50 CONTINUE
      IF(X(6).NE.0.)THEN
         SMAX3=PAR(3)/ABS(X(6))-X(3)/X(6)
      ENDIF
   60 CONTINUE
C
      SMIN=MAX(SMIN1,SMIN2,SMIN3)
      SMAX=MIN(SMAX1,SMAX2,SMAX3)
      IF(SMAX.LT.SMIN) GO TO 999
C
C 13.06.98, Tikhomirov:
      IF(SMIN.LT.0.)GO TO 999
C     IF(SMIN.LE.0.)GO TO 999
 
      SNXT = SMIN
 
  999 CONTINUE
      END
*CMZ :  1.40/05 04/07/98  16.10.45  by  Pavel Nevski
*CMZ :  3.21/04 31/10/94  10.11.27  by  S.Ravndal
*-- Author :
      SUBROUTINE GRNDMQ(IS1,IS2,ISEQ,CHOPT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       To set/retrieve the seed of the random number generator  *
C.    *        Copy of the CERN Library routine RECUSQ                 *
C.    *        Each sequence has a period of 10**9 numbers             *
C.    *                                                                *
C.    *    ==>Called by : <USER>, many GEANT routines                  *
C.    *       Author    R.Brun, F.Carminati  *********                 *
C.    *                                                                *
C.    ******************************************************************
C.
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
      CHARACTER*(*) CHOPT
      CHARACTER*12  CCHOPT
      PARAMETER  (MAXSEQ=215)
      COMMON / GCRNDM / JSEQ(2), ISEED(2,MAXSEQ)
      DIMENSION  LSEQS(2,MAXSEQ)
      DATA LSEQS(1,  1),LSEQS(2,  1 )/      9876,     54321/
      DATA LSEQS(1,  2),LSEQS(2,  2 )/1299961164, 253987020/
      DATA LSEQS(1,  3),LSEQS(2,  3 )/ 669708517,2079157264/
      DATA LSEQS(1,  4),LSEQS(2,  4 )/ 190904760, 417696270/
      DATA LSEQS(1,  5),LSEQS(2,  5 )/1289741558,1376336092/
      DATA LSEQS(1,  6),LSEQS(2,  6 )/1803730167, 324952955/
      DATA LSEQS(1,  7),LSEQS(2,  7 )/ 489854550, 582847132/
      DATA LSEQS(1,  8),LSEQS(2,  8 )/1348037628,1661577989/
      DATA LSEQS(1,  9),LSEQS(2,  9 )/ 350557787,1155446919/
      DATA LSEQS(1, 10),LSEQS(2, 10 )/ 591502945, 634133404/
      DATA LSEQS(1, 11),LSEQS(2, 11 )/1901084678, 862916278/
      DATA LSEQS(1, 12),LSEQS(2, 12 )/1988640932,1785523494/
      DATA LSEQS(1, 13),LSEQS(2, 13 )/1873836227, 508007031/
      DATA LSEQS(1, 14),LSEQS(2, 14 )/1146416592, 967585720/
      DATA LSEQS(1, 15),LSEQS(2, 15 )/1837193353,1522927634/
      DATA LSEQS(1, 16),LSEQS(2, 16 )/  38219936, 921609208/
      DATA LSEQS(1, 17),LSEQS(2, 17 )/ 349152748, 112892610/
      DATA LSEQS(1, 18),LSEQS(2, 18 )/ 744459040,1735807920/
      DATA LSEQS(1, 19),LSEQS(2, 19 )/1983990104, 728277902/
      DATA LSEQS(1, 20),LSEQS(2, 20 )/ 309164507,2126677523/
      DATA LSEQS(1, 21),LSEQS(2, 21 )/ 362993787,1897782044/
      DATA LSEQS(1, 22),LSEQS(2, 22 )/ 556776976, 462072869/
      DATA LSEQS(1, 23),LSEQS(2, 23 )/1584900822,2019394912/
      DATA LSEQS(1, 24),LSEQS(2, 24 )/1249892722, 791083656/
      DATA LSEQS(1, 25),LSEQS(2, 25 )/1686600998,1983731097/
      DATA LSEQS(1, 26),LSEQS(2, 26 )/1127381380, 198976625/
      DATA LSEQS(1, 27),LSEQS(2, 27 )/1999420861,1810452455/
      DATA LSEQS(1, 28),LSEQS(2, 28 )/1972906041, 664182577/
      DATA LSEQS(1, 29),LSEQS(2, 29 )/  84636481,1291886301/
      DATA LSEQS(1, 30),LSEQS(2, 30 )/1186362995, 954388413/
      DATA LSEQS(1, 31),LSEQS(2, 31 )/2141621785,  61738584/
      DATA LSEQS(1, 32),LSEQS(2, 32 )/1969581251,1557880415/
      DATA LSEQS(1, 33),LSEQS(2, 33 )/1150606439, 136325185/
      DATA LSEQS(1, 34),LSEQS(2, 34 )/  95187861,1592224108/
      DATA LSEQS(1, 35),LSEQS(2, 35 )/ 940517655,1629971798/
      DATA LSEQS(1, 36),LSEQS(2, 36 )/ 215350428, 922659102/
      DATA LSEQS(1, 37),LSEQS(2, 37 )/ 786161212,1121345074/
      DATA LSEQS(1, 38),LSEQS(2, 38 )/1450830056,1922787776/
      DATA LSEQS(1, 39),LSEQS(2, 39 )/1696578057,2025150487/
      DATA LSEQS(1, 40),LSEQS(2, 40 )/1803414346,1851324780/
      DATA LSEQS(1, 41),LSEQS(2, 41 )/1017898585,1452594263/
      DATA LSEQS(1, 42),LSEQS(2, 42 )/1184497978,  82122239/
      DATA LSEQS(1, 43),LSEQS(2, 43 )/ 633338765,1829684974/
      DATA LSEQS(1, 44),LSEQS(2, 44 )/ 430889421, 230039326/
      DATA LSEQS(1, 45),LSEQS(2, 45 )/ 492544653,  76320266/
      DATA LSEQS(1, 46),LSEQS(2, 46 )/ 389386975,1314148944/
      DATA LSEQS(1, 47),LSEQS(2, 47 )/1720322786, 709120323/
      DATA LSEQS(1, 48),LSEQS(2, 48 )/1868768216,1992898523/
      DATA LSEQS(1, 49),LSEQS(2, 49 )/ 443210610, 811117710/
      DATA LSEQS(1, 50),LSEQS(2, 50 )/1191938868,1548484733/
      DATA LSEQS(1, 51),LSEQS(2, 51 )/ 616890172, 159787986/
      DATA LSEQS(1, 52),LSEQS(2, 52 )/ 935835339,1231440405/
      DATA LSEQS(1, 53),LSEQS(2, 53 )/1058009367,1527613300/
      DATA LSEQS(1, 54),LSEQS(2, 54 )/1463148129,1970575097/
      DATA LSEQS(1, 55),LSEQS(2, 55 )/1795336935, 434768675/
      DATA LSEQS(1, 56),LSEQS(2, 56 )/ 274019517, 605098487/
      DATA LSEQS(1, 57),LSEQS(2, 57 )/ 483689317, 217146977/
      DATA LSEQS(1, 58),LSEQS(2, 58 )/2070804364, 340596558/
      DATA LSEQS(1, 59),LSEQS(2, 59 )/ 930226308,1602100969/
      DATA LSEQS(1, 60),LSEQS(2, 60 )/ 989324440, 801809442/
      DATA LSEQS(1, 61),LSEQS(2, 61 )/ 410606853,1893139948/
      DATA LSEQS(1, 62),LSEQS(2, 62 )/1583588576,1219225407/
      DATA LSEQS(1, 63),LSEQS(2, 63 )/2102034391,1394921405/
      DATA LSEQS(1, 64),LSEQS(2, 64 )/2005037790,2031006861/
      DATA LSEQS(1, 65),LSEQS(2, 65 )/1244218766, 923231061/
      DATA LSEQS(1, 66),LSEQS(2, 66 )/  49312790, 775496649/
      DATA LSEQS(1, 67),LSEQS(2, 67 )/ 721012176, 321339902/
      DATA LSEQS(1, 68),LSEQS(2, 68 )/1719909107,1865748178/
      DATA LSEQS(1, 69),LSEQS(2, 69 )/1156177430,1257110891/
      DATA LSEQS(1, 70),LSEQS(2, 70 )/ 307561322,1918244397/
      DATA LSEQS(1, 71),LSEQS(2, 71 )/ 906041433, 360476981/
      DATA LSEQS(1, 72),LSEQS(2, 72 )/1591375755, 268492659/
      DATA LSEQS(1, 73),LSEQS(2, 73 )/ 461522398, 227343256/
      DATA LSEQS(1, 74),LSEQS(2, 74 )/2145930725,2020665454/
      DATA LSEQS(1, 75),LSEQS(2, 75 )/1938419274,1331283701/
      DATA LSEQS(1, 76),LSEQS(2, 76 )/ 174405412, 524140103/
      DATA LSEQS(1, 77),LSEQS(2, 77 )/ 494343653,  18063908/
      DATA LSEQS(1, 78),LSEQS(2, 78 )/1025534808, 181709577/
      DATA LSEQS(1, 79),LSEQS(2, 79 )/2048959776,1913665637/
      DATA LSEQS(1, 80),LSEQS(2, 80 )/ 950636517, 794796256/
      DATA LSEQS(1, 81),LSEQS(2, 81 )/1828843197,1335757744/
      DATA LSEQS(1, 82),LSEQS(2, 82 )/ 211109723, 983900607/
      DATA LSEQS(1, 83),LSEQS(2, 83 )/ 825474095,1046009991/
      DATA LSEQS(1, 84),LSEQS(2, 84 )/ 374915657, 381856628/
      DATA LSEQS(1, 85),LSEQS(2, 85 )/1241296328, 698149463/
      DATA LSEQS(1, 86),LSEQS(2, 86 )/1260624655,1024538273/
      DATA LSEQS(1, 87),LSEQS(2, 87 )/ 900676210,1628865823/
      DATA LSEQS(1, 88),LSEQS(2, 88 )/ 697951025, 500570753/
      DATA LSEQS(1, 89),LSEQS(2, 89 )/1007920268,1708398558/
      DATA LSEQS(1, 90),LSEQS(2, 90 )/ 264596520, 624727803/
      DATA LSEQS(1, 91),LSEQS(2, 91 )/1977924811, 674673241/
      DATA LSEQS(1, 92),LSEQS(2, 92 )/1440257718, 271184151/
      DATA LSEQS(1, 93),LSEQS(2, 93 )/1928778847, 993535203/
      DATA LSEQS(1, 94),LSEQS(2, 94 )/1307807366,1801502463/
      DATA LSEQS(1, 95),LSEQS(2, 95 )/1498732610, 300876954/
      DATA LSEQS(1, 96),LSEQS(2, 96 )/1617712402,1574250679/
      DATA LSEQS(1, 97),LSEQS(2, 97 )/1261800762,1556667280/
      DATA LSEQS(1, 98),LSEQS(2, 98 )/ 949929273, 560721070/
      DATA LSEQS(1, 99),LSEQS(2, 99 )/1766170474,1953522912/
      DATA LSEQS(1,100),LSEQS(2,100 )/1849939248,  19435166/
      DATA LSEQS(1,101),LSEQS(2,101 )/ 887262858,1219627824/
      DATA LSEQS(1,102),LSEQS(2,102 )/ 483086133, 603728993/
      DATA LSEQS(1,103),LSEQS(2,103 )/1330541052,1582596025/
      DATA LSEQS(1,104),LSEQS(2,104 )/1850591475, 723593133/
      DATA LSEQS(1,105),LSEQS(2,105 )/1431775678,1558439000/
      DATA LSEQS(1,106),LSEQS(2,106 )/ 922493739,1356554404/
      DATA LSEQS(1,107),LSEQS(2,107 )/1058517206, 948567762/
      DATA LSEQS(1,108),LSEQS(2,108 )/ 709067283,1350890215/
      DATA LSEQS(1,109),LSEQS(2,109 )/1044787723,2144304941/
      DATA LSEQS(1,110),LSEQS(2,110 )/ 999707003, 513837520/
      DATA LSEQS(1,111),LSEQS(2,111 )/2140038663,1850568788/
      DATA LSEQS(1,112),LSEQS(2,112 )/1803100150, 127574047/
      DATA LSEQS(1,113),LSEQS(2,113 )/ 867445693,1149173981/
      DATA LSEQS(1,114),LSEQS(2,114 )/ 408583729, 914837991/
      DATA LSEQS(1,115),LSEQS(2,115 )/1166715497, 602315845/
      DATA LSEQS(1,116),LSEQS(2,116 )/ 430738528,1743308384/
      DATA LSEQS(1,117),LSEQS(2,117 )/1388022681,1760110496/
      DATA LSEQS(1,118),LSEQS(2,118 )/1664028066, 654300326/
      DATA LSEQS(1,119),LSEQS(2,119 )/1767741172,1338181197/
      DATA LSEQS(1,120),LSEQS(2,120 )/1625723550,1742482745/
      DATA LSEQS(1,121),LSEQS(2,121 )/ 464486085,1507852127/
      DATA LSEQS(1,122),LSEQS(2,122 )/ 754082421,1187454014/
      DATA LSEQS(1,123),LSEQS(2,123 )/1315342834, 425995190/
      DATA LSEQS(1,124),LSEQS(2,124 )/ 960416608,2004255418/
      DATA LSEQS(1,125),LSEQS(2,125 )/1262630671, 671761697/
      DATA LSEQS(1,126),LSEQS(2,126 )/  59809238, 103525918/
      DATA LSEQS(1,127),LSEQS(2,127 )/1205644919,2107823293/
      DATA LSEQS(1,128),LSEQS(2,128 )/1615183160,1152411412/
      DATA LSEQS(1,129),LSEQS(2,129 )/1024474681,2118672937/
      DATA LSEQS(1,130),LSEQS(2,130 )/1703877649,1235091369/
      DATA LSEQS(1,131),LSEQS(2,131 )/1821417852,1098463802/
      DATA LSEQS(1,132),LSEQS(2,132 )/1738806466,1529062843/
      DATA LSEQS(1,133),LSEQS(2,133 )/ 620780646,1654833544/
      DATA LSEQS(1,134),LSEQS(2,134 )/1070174101, 795158254/
      DATA LSEQS(1,135),LSEQS(2,135 )/ 658537995,1693620426/
      DATA LSEQS(1,136),LSEQS(2,136 )/2055317555, 508053916/
      DATA LSEQS(1,137),LSEQS(2,137 )/1647371686,1282395762/
      DATA LSEQS(1,138),LSEQS(2,138 )/  29067379, 409683067/
      DATA LSEQS(1,139),LSEQS(2,139 )/1763495989,1917939635/
      DATA LSEQS(1,140),LSEQS(2,140 )/1602690753, 810926582/
      DATA LSEQS(1,141),LSEQS(2,141 )/ 885787576, 513818500/
      DATA LSEQS(1,142),LSEQS(2,142 )/1853512561,1195205756/
      DATA LSEQS(1,143),LSEQS(2,143 )/1798585498,1970460256/
      DATA LSEQS(1,144),LSEQS(2,144 )/1819261032,1306536501/
      DATA LSEQS(1,145),LSEQS(2,145 )/1133245275,     37901/
      DATA LSEQS(1,146),LSEQS(2,146 )/ 689459799,1334389069/
      DATA LSEQS(1,147),LSEQS(2,147 )/1730609912,1854586207/
      DATA LSEQS(1,148),LSEQS(2,148 )/1556832175,1228729041/
      DATA LSEQS(1,149),LSEQS(2,149 )/ 251375753, 683687209/
      DATA LSEQS(1,150),LSEQS(2,150 )/2083946182,1763106152/
      DATA LSEQS(1,151),LSEQS(2,151 )/2142981854,1365385561/
      DATA LSEQS(1,152),LSEQS(2,152 )/ 763711891,1735754548/
      DATA LSEQS(1,153),LSEQS(2,153 )/1581256466, 173689858/
      DATA LSEQS(1,154),LSEQS(2,154 )/2121337132,1247108250/
      DATA LSEQS(1,155),LSEQS(2,155 )/1004003636, 891894307/
      DATA LSEQS(1,156),LSEQS(2,156 )/ 569816524, 358675254/
      DATA LSEQS(1,157),LSEQS(2,157 )/ 626626425, 116062841/
      DATA LSEQS(1,158),LSEQS(2,158 )/ 632086003, 861268491/
      DATA LSEQS(1,159),LSEQS(2,159 )/1008211580, 779404957/
      DATA LSEQS(1,160),LSEQS(2,160 )/1134217766,1766838261/
      DATA LSEQS(1,161),LSEQS(2,161 )/1423829292,1706666192/
      DATA LSEQS(1,162),LSEQS(2,162 )/ 942037869,1549358884/
      DATA LSEQS(1,163),LSEQS(2,163 )/1959429535, 480779114/
      DATA LSEQS(1,164),LSEQS(2,164 )/ 778311037,1940360875/
      DATA LSEQS(1,165),LSEQS(2,165 )/1531372185,2009078158/
      DATA LSEQS(1,166),LSEQS(2,166 )/ 241935492,1050047003/
      DATA LSEQS(1,167),LSEQS(2,167 )/ 272453504,1870883868/
      DATA LSEQS(1,168),LSEQS(2,168 )/ 390441332,1057903098/
      DATA LSEQS(1,169),LSEQS(2,169 )/1230238834,1548117688/
      DATA LSEQS(1,170),LSEQS(2,170 )/1242956379,1217296445/
      DATA LSEQS(1,171),LSEQS(2,171 )/ 515648357,1675011378/
      DATA LSEQS(1,172),LSEQS(2,172 )/ 364477932, 355212934/
      DATA LSEQS(1,173),LSEQS(2,173 )/2096008713,1570161804/
      DATA LSEQS(1,174),LSEQS(2,174 )/1409752526, 214033983/
      DATA LSEQS(1,175),LSEQS(2,175 )/1288158292,1760636178/
      DATA LSEQS(1,176),LSEQS(2,176 )/ 407562666,1265144848/
      DATA LSEQS(1,177),LSEQS(2,177 )/1071056491,1582316946/
      DATA LSEQS(1,178),LSEQS(2,178 )/1014143949, 911406955/
      DATA LSEQS(1,179),LSEQS(2,179 )/ 203080461, 809380052/
      DATA LSEQS(1,180),LSEQS(2,180 )/ 125647866,1705464126/
      DATA LSEQS(1,181),LSEQS(2,181 )/2015685843, 599230667/
      DATA LSEQS(1,182),LSEQS(2,182 )/1425476020, 668203729/
      DATA LSEQS(1,183),LSEQS(2,183 )/1673735652, 567931803/
      DATA LSEQS(1,184),LSEQS(2,184 )/1714199325, 181737617/
      DATA LSEQS(1,185),LSEQS(2,185 )/1389137652, 678147926/
      DATA LSEQS(1,186),LSEQS(2,186 )/ 288547803, 435433694/
      DATA LSEQS(1,187),LSEQS(2,187 )/ 200159281, 654399753/
      DATA LSEQS(1,188),LSEQS(2,188 )/1580828223,1298308945/
      DATA LSEQS(1,189),LSEQS(2,189 )/1832286107, 169991953/
      DATA LSEQS(1,190),LSEQS(2,190 )/ 182557704,1046541065/
      DATA LSEQS(1,191),LSEQS(2,191 )/1688025575,1248944426/
      DATA LSEQS(1,192),LSEQS(2,192 )/1508287706,1220577001/
      DATA LSEQS(1,193),LSEQS(2,193 )/  36721212,1377275347/
      DATA LSEQS(1,194),LSEQS(2,194 )/1968679856,1675229747/
      DATA LSEQS(1,195),LSEQS(2,195 )/ 279109231,1835333261/
      DATA LSEQS(1,196),LSEQS(2,196 )/1358617667,1416978076/
      DATA LSEQS(1,197),LSEQS(2,197 )/ 740626186,2103913602/
      DATA LSEQS(1,198),LSEQS(2,198 )/1882655908, 251341858/
      DATA LSEQS(1,199),LSEQS(2,199 )/ 648016670,1459615287/
      DATA LSEQS(1,200),LSEQS(2,200 )/ 780255321, 154906988/
      DATA LSEQS(1,201),LSEQS(2,201 )/ 857296483, 203375965/
      DATA LSEQS(1,202),LSEQS(2,202 )/1631676846, 681204578/
      DATA LSEQS(1,203),LSEQS(2,203 )/1906971307,1623728832/
      DATA LSEQS(1,204),LSEQS(2,204 )/1541899600,1168449797/
      DATA LSEQS(1,205),LSEQS(2,205 )/1267051693,1020078717/
      DATA LSEQS(1,206),LSEQS(2,206 )/1998673940,1298394942/
      DATA LSEQS(1,207),LSEQS(2,207 )/1914117058,1381290704/
      DATA LSEQS(1,208),LSEQS(2,208 )/ 426068513,1381618498/
      DATA LSEQS(1,209),LSEQS(2,209 )/ 139365577,1598767734/
      DATA LSEQS(1,210),LSEQS(2,210 )/2129910384, 952266588/
      DATA LSEQS(1,211),LSEQS(2,211 )/ 661788054,  19661356/
      DATA LSEQS(1,212),LSEQS(2,212 )/1104640222, 240506063/
      DATA LSEQS(1,213),LSEQS(2,213 )/ 356133630,1676634527/
      DATA LSEQS(1,214),LSEQS(2,214 )/ 242242374,1863206182/
      DATA LSEQS(1,215),LSEQS(2,215 )/ 957935844,1490681416/
C
      CCHOPT = CHOPT
      IF(CCHOPT.EQ.' ') THEN
        IF(ISEQ.GT.215.OR.ISEQ.LT.1) THEN
            ISEED(1,1) = LSEQS(1,1)
            ISEED(2,1) = LSEQS(2,1)
            JSEQ(1)    = 1
        ELSE
            ISEED(1,ISEQ) = LSEQS(1,ISEQ)
            ISEED(2,ISEQ) = LSEQS(2,ISEQ)
            JSEQ(1)    = ISEQ
        END IF
        GO TO 999
      END IF
      IF(INDEX(CHOPT,'S').NE.0) THEN
        IF(ISEQ.GT.0) JSEQ(1) = ISEQ
        IF(IS1.GT.0.AND.IS2.GT.0) THEN
          ISEED(1,JSEQ(1)) = IS1
          ISEED(2,JSEQ(1)) = IS2
        END IF
        IF(INDEX(CHOPT,'H').NE.0) THEN
          IQ(JHEAD+3) = IS1
          IQ(JHEAD+4) = IS2
        END IF
      END IF
      IF(INDEX(CHOPT,'G').NE.0) THEN
        IF(ISEQ.LE.0)THEN
           KSEQ = JSEQ(1)
        ELSE
           KSEQ = ISEQ
        ENDIF
        IS1 = ISEED(1,KSEQ)
        IS2 = ISEED(2,KSEQ)
      END IF
      IF(INDEX(CHOPT,'Q').NE.0) THEN
        IF(ISEQ.GE.1.AND.ISEQ.LE.MAXSEQ) THEN
          IS1 = LSEQS(1,ISEQ)
          IS2 = LSEQS(2,ISEQ)
        ELSE
          IS1 = 0
          IS2 = 0
        END IF
      END IF
C
 999  END
*CMZ :  1.40/05 04/07/98  16.10.45  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.23  by  S.Giani
*-- Author :
      SUBROUTINE GRNDM(RVEC,LEN)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       To generate a vector RVECV of LEN random numbers         *
C.    *         Copy of the CERN Library routine RANECU                *
C.    *                                                                *
C.    *    ==>Called by : <USER>, many GEANT routines                  *
C.    *       Author    F.Carminati *********                          *
C.    *                                                                *
C.    ******************************************************************
C.
      DIMENSION RVEC(*)
      PARAMETER  (MAXSEQ=215)
      COMMON / GCRNDM / JSEQ(2), ISEED(2,MAXSEQ)
C
      ISEQ   = JSEQ(1)
      ISEED1 = ISEED(1,ISEQ)
      ISEED2 = ISEED(2,ISEQ)
      DO 100 I= 1, LEN
        K = ISEED1/53668
        ISEED1 = 40014*(ISEED1 - K*53668) - K*12211
        IF (ISEED1 .LT. 0) ISEED1=ISEED1+2147483563
C
        K = ISEED2/52774
        ISEED2 = 40692*(ISEED2 - K*52774) - K* 3791
        IF (ISEED2 .LT. 0) ISEED2=ISEED2+2147483399
C
        IZ = ISEED1 - ISEED2
        IF (IZ .LE. 0)  IZ = IZ + 2147483562
C
        RVEC(I) = IZ * 4.6566128E-10
  100 CONTINUE
      ISEED(1,ISEQ) = ISEED1
      ISEED(2,ISEQ) = ISEED2
      END
*CMZ :  1.40/05 04/07/98  16.17.30  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.40  by  S.Giani
*-- Author :
      SUBROUTINE HIGCLU(IPPP,NFL,AVERN)
C
C *** GENERATION OF X- AND PT- VALUES FOR ALL PRODUCED PARTICLES ***
C *** NVE 01-AUG-1988 CERN GENEVA ***
C
C ORIGIN : H.FESEFELDT (11-OCT-1987)
C
C A SIMPLE TWO CLUSTER MODEL IS USED
C THIS SHOULD BE SUFFICIENT FOR LOW ENERGY INTERACTIONS
C
C
*KEEP,/DEFCOM.
      PARAMETER (MXGKGH=100)
      COMMON/CONSTS/ PI,TWPI,PIBTW,MP,MPI,MMU,MEL,MKCH,MK0,SMP,SMPI,
     $               SMU,CT,CTKCH,CTK0,
     $               ML0,MSP,MS0,MSM,MX0,MXM,CTL0,CTSP,CTSM,CTX0,CTXM,
     $               RMASS(35),RCHARG(35)
C
                     REAL MP,MPI,MMU,MEL,MKCH,MK0,
     *                    ML0,MSP,MS0,MSM,MX0,MXM
C
      PARAMETER (MXGKCU=MXGKGH)
      COMMON/CURPAR/WEIGHT(10),DDELTN,IFILE,IRUN,NEVT,NEVENT,SHFLAG,
     *              ITHST,ITTOT,ITLST,IFRND,TOFCUT,CMOM(5),CENG(5),
     *              RS,S,ENP(10),NP,NM,NN,NR,NO,NZ,IPA(MXGKCU),
     *              ATNO2,ZNO2
C
      COMMON/RESULT/XEND,YEND,ZEND,RCA,RCE,AMAS,NCH,TOF,PX,PY,PZ,
     *              USERW,INTCT,P,EN,EK,AMASQ,DELTN,ITK,NTK,IPART,IND,
     *              LCALO,ICEL,SINL,COSL,SINP,COSP,
     *              XOLD,YOLD,ZOLD,POLD,PXOLD,PYOLD,PZOLD,
     *              XSCAT,YSCAT,ZSCAT,PSCAT,PXSCAT,PYSCAT,PZSCAT
                    REAL NCH,INTCT
C
      COMMON/MAT   / LMAT,
     *               DEN(21),RADLTH(21),ATNO(21),ZNO(21),ABSL(21),
     *               CDEN(21),MDEN(21),X0DEN(21),X1DEN(21),RION(21),
     *               MATID(21),MATID1(21,24),PARMAT(21,10),
     *               IFRAT,IFRAC(21),FRAC1(21,10),DEN1(21,10),
     *               ATNO1(21,10),ZNO1(21,10)
C
      PARAMETER (MXEVEN=12*MXGKGH)
      COMMON/EVENT / NSIZE,NCUR,NEXT,NTOT,EVE(MXEVEN)
C
      COMMON/PRNTFL/INBCD,NEWBCD,INBIN,NEWBIN,NPEVT,NEVTP,LPRT,NPRT(10)
                    LOGICAL LPRT,NPRT
C
      COMMON/ERRCOM/ IER(100)
C
      PARAMETER (MXGKPV=MXGKGH)
      COMMON /VECUTY/ PV(10,MXGKPV)
C
C
*KEEP,/GENIO.
      COMMON/GENIN /TECM,AMASS(18),NPG,KGENEV
      COMMON/GENOUT/PCM(5,18),WGT
C
*KEND.
C
      REAL NUCSUP
      DIMENSION SIDE(MXGKCU),C1PAR(5),G1PAR(5),NUCSUP(6)
* PN, 04/06/98 - poor man solution
      DATA      SIDE/MXGKCU*0./
      DIMENSION RNDM(3)
      DATA C1PAR/0.6,0.6,0.35,0.15,0.10/
      DATA G1PAR/2.6,2.6,1.8,1.30,1.20/
      DATA NUCSUP/1.0,0.7,0.5,0.4,0.35,0.3/
      DIMENSION PSUP(6)
      DATA PSUP/3.,6.,20.,50.,100.,1000./
C     DATA CB/3.0/
      DATA CB/0.01/
      BPP(X)=4.000+1.600*LOG(X)
C
      MX =MXGKPV-20
      MX1=MX+1
      MX2=MX+2
      MX3=MX+3
      MX4=MX+4
      MX5=MX+5
      MX6=MX+6
      MX7=MX+7
      MX8=MX+8
      EK=ENP(5)
      EN=ENP(6)
      P=ENP(7)
      S=ENP(8)
      RS=ENP(9)
      CFA=0.025*((ATNO2-1.)/120.)*EXP(-(ATNO2-1.)/120.)
      IF(P.LT.0.001) GOTO 60
      NT=0
C**
C** CHECK MASS-INDICES FOR ALL PARTICLES
C**
      DO 1 I=1,100
      IF(IPA(I).EQ.0) GOTO 1
      NT=NT+1
      IPA(NT)=IPA(I)
    1 CONTINUE
      CALL VZERO(IPA(NT+1),MXGKCU-NT)
C**
C** SET THE EFFECTICE 4-MOMENTUM-VECTOR FOR INTERACTION
C**
      PV( 1,MXGKPV-1)=P*PX
      PV( 2,MXGKPV-1)=P*PY
      PV( 3,MXGKPV-1)=P*PZ
      PV( 4,MXGKPV-1)=EN
      PV( 5,MXGKPV-1)=AMAS
      PV( 6,MXGKPV-1)=NCH
      PV( 7,MXGKPV-1)=TOF
      PV( 8,MXGKPV-1)=IPART
      PV( 9,MXGKPV-1)=0.
      PV(10,MXGKPV-1)=USERW
      IER(48)=IER(48)+1
C**
C** DISTRIBUTE PARTICLES IN FORWARD AND BACKWARD HEMISPHERE OF CMS
C** OF THE HADRON NUCLEON INTERACTION
C**
      SIDE(1)= 1.
      SIDE(2)=-1.
      TARG=0.
      SPALL=TARG
      IFOR=1
      IBACK=1
      DO 3 I=1,NT
* PN: poor man solution
      SIDE(I)=1.
      IF (I .LE. 2) GO TO 78
      CALL GRNDM(RNDM,1)
      IF (RNDM(1) .LT. 0.5) SIDE(I)=-1.
      IF (SIDE(I) .LT. 0.) GO TO 76
C
C --- PARTICLE IN FORWARD HEMISPHERE ---
 77   CONTINUE
      IFOR=IFOR+1
      IF (IFOR .LE. 18) GO TO 78
C
C --- CHANGE IT TO BACKWARD ---
      SIDE(I)=-1.
      IFOR=IFOR-1
      IBACK=IBACK+1
      GO TO 78
C
C --- PARTICLE IN BACKWARD HEMISPHERE ---
 76   CONTINUE
      IBACK=IBACK+1
      IF (IBACK .LE. 18) GO TO 78
C
C --- CHANGE IT TO FORWARD ---
      SIDE(I)=1.
      IBACK=IBACK-1
      IFOR=IFOR+1
C**
C** SUPPRESSION OF CHARGED PIONS FOR VARIOUS REASONS
C**
   78 IF(IPART.EQ.15.OR.IPART.GE.17) GOTO 3
      IF(ABS(IPA(I)).GE.10) GOTO 3
      IF(ABS(IPA(I)).EQ. 8) GOTO 3
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).GT.(10.-P)/6.) GOTO 3
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).GT.ATNO2/300.) GOTO 3
      IPA(I)=14
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).GT.ZNO2/ATNO2) IPA(I)=16
      TARG=TARG+1.
    3 CONTINUE
      TB=2.*IBACK
      CALL GRNDM(RNDM,1)
      IF(RS.LT.(2.0+RNDM(1))) TB=(2.*IBACK+NT)/2.
C**
C** NUCLEONS + SOME PIONS FROM INTRANUCLEAR CASCADE
C**
      AFC=0.312+0.200*LOG(LOG(S))+S**1.5/6000.
      IF(AFC.GT.0.50) AFC= 0.50
      XTARG=AFC*(ATNO2**0.33-1.0)*TB
      IF(XTARG.LE.0.) XTARG=0.01
      DO 881 IPX=1,6
         IF(P.LE.PSUP(IPX)) GOTO 882
  881 CONTINUE
      IPX=6
  882 XPNHMF = XTARG*NUCSUP(IPX)
      XSHHMF = XTARG - XPNHMF
      IF(XSHHMF.LT.0.01) XSHHMF=0.01
      IF(XPNHMF.LT.0.01) XPNHMF=0.01
      SSHHMF=0.5*XSHHMF
      SPNHMF=0.9*XPNHMF
      RSHHMF=SSHHMF**2/XSHHMF
      RPNHMF=SPNHMF**2/XPNHMF
      IF(RSHHMF.LT.1.1) THEN
        CALL POISSO(XSHHMF,NSHHMF)
        GOTO 541
      ELSE
        RSHHMF=XSHHMF/(RSHHMF-1.)
        IF(RSHHMF.LE.20.) THEN
          CALL SVGAM7(RSHHMF,XHMF)
        ELSE
          KRSHMF=IFIX(RSHHMF+0.5)
          CALL SVERL2(KRSHMF,XHMF)
        ENDIF
        XSHHMF=XHMF*XSHHMF/RSHHMF
        CALL POISSO(XSHHMF,NSHHMF)
      ENDIF
  541 IF(RPNHMF.LE.1.1) THEN
        CALL POISSO(XPNHMF,NPNHMF)
        GOTO 542
      ELSE
        RPNHMF=XPNHMF/(RPNHMF-1.)
        IF(RPNHMF.LE.20.) THEN
           CALL SVGAM7(RPNHMF,XHMF)
        ELSE
           KRPHMF=IFIX(RPNHMF+0.5)
           CALL SVERL2(KRPHMF,XHMF)
        ENDIF
        XPNHMF=XHMF*XPNHMF/RPNHMF
        CALL POISSO(XPNHMF,NPNHMF)
      ENDIF
  542 NTARG=NSHHMF+NPNHMF
      NT2=NT+NTARG
      IF(NT2.LE.MXGKPV-30) GOTO 2
      NT2=MXGKPV-30
      NTARG=NT2-NT
    2 CONTINUE
      IF(NPRT(4))
     *WRITE(NEWBCD,3001) NTARG,NT
 
      DO 777 I=NT+1,NT+NTARG
* PN, 06/04/98: SIDE(I) should be always defined.
 777  SIDE(I)=0
 
      NT1=NT+1
      IF(NTARG.EQ.0) GOTO 51
      DO 4 I=NT1,NT2
* PN, 06/04/98: SIDE(I) should be always defined.
      SIDE(I)=-2.
      IF(NPNHMF.GT.0) GOTO 52
      CALL GRNDM(RNDM,1)
      IPA(I)=-(7+IFIX(RNDM(1)*3.0))
      GOTO 4
   52 IPA(I)=-16
      PNRAT=1.-ZNO2/ATNO2
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).GT.PNRAT) IPA(I)=-14
      TARG=TARG+1.
      NPNHMF=NPNHMF-1
    4 CONTINUE
      NT=NT2
C**
C** CHOOSE MASSES AND CHARGES FOR ALL PARTICLES
C**
   51 DO 5 I=1,NT
      IPA1=ABS(IPA(I))
      PV(5,I)=RMASS(IPA1)
      PV(6,I)=RCHARG(IPA1)
      PV(7,I)=1.
      IF(PV(5,I).LT.0.) PV(7,I)=-1.
      PV(5,I)=ABS(PV(5,I))
    5 CONTINUE
C**
C** MARK LEADING STRANGE PARTICLES
C**
      LEAD=0
      IF(IPART.LT.10.OR.IPART.EQ.14.OR.IPART.EQ.16) GOTO 6
      IPA1=ABS(IPA(1))
      IF(IPA1.LT.10.OR.IPA1.EQ.14.OR.IPA1.EQ.16) GOTO 531
      LEAD=IPA1
      GOTO 6
  531 IPA1=ABS(IPA(2))
      IF(IPA1.LT.10.OR.IPA1.EQ.14.OR.IPA1.EQ.16) GOTO 6
      LEAD=IPA1
C**
C** CHECK AVAILABLE KINETIC ENERGY , CHANGE HEMISPHERE FOR PARTICLES
C** UNTIL IT FITS
C**
    6 IF(NT.LE.1) GOTO 60
      TAVAI=0.
      DO 7 I=1,NT
      IF(SIDE(I).LT.-1.5) GOTO 7
      TAVAI=TAVAI+ABS(PV(5,I))
    7 CONTINUE
      IF(TAVAI.LT.RS) GOTO 12
      IF(NPRT(4))
     *WRITE(NEWBCD,3002) (IPA(I),I=1,20),(SIDE(I),I=1,20),TAVAI,RS
 3002 FORMAT(' *HIGCLU* CHECK AVAILABLE ENERGIES'/
     *       1H ,20I5/1H ,20F5.0/1H ,'TAVAI,RS ',2F10.3)
      DO 10 I=1,NT
      II=NT-I+1
      IF(SIDE(II).LT.-1.5) GOTO 10
      IF(II.EQ.NT) GOTO 11
      NT1=II+1
      NT2=NT
      DO 8 J=NT1,NT2
      IPA(J-1)=IPA(J)
      SIDE(J-1)=SIDE(J)
      DO 8 K=1,10
    8 PV(K,J-1)=PV(K,J)
      GOTO 11
   10 CONTINUE
   11 SIDE(NT)=0.
      IPA(NT)=0
      NT=NT-1
      GOTO 6
   12 IF(NT.LE.1) GOTO 60
      B=BPP(P)
      IF(B.LT.CB) B=CB
C**
C** CHOOSE MASSES FOR THE 3 CLUSTER: 1. FORWARD CLUSTER
C**   2. BACKWARD MESON CLUSTER  3. BACKWARD NUCLEON CLUSTER
C**
      RMC0=0.
      RMD0=0.
      RME0=0.
      NTC=0
      NTD=0
      NTE=0
      DO 31 I=1,NT
      IF(SIDE(I).GT.0.) RMC0=RMC0+ABS(PV(5,I))
      IF(SIDE(I).GT.0.) NTC =NTC +1
      IF(SIDE(I).LT.0..AND.SIDE(I).GT.-1.5) RMD0=RMD0+ABS(PV(5,I))
      IF(                  SIDE(I).LT.-1.5) RME0=RME0+ABS(PV(5,I))
      IF(SIDE(I).LT.0..AND.SIDE(I).GT.-1.5) NTD =NTD +1
      IF(                  SIDE(I).LT.-1.5) NTE =NTE +1
   31 CONTINUE
   32 CALL GRNDM(RNDM,1)
      RAN=RNDM(1)
      RMC=RMC0
      IF(NTC.LE.1) GOTO 33
      NTC1=NTC
      IF(NTC1.GT.5) NTC1=5
      RMC=-LOG(1.-RAN)
      GPAR=G1PAR(NTC1)
      CPAR=C1PAR(NTC1)
      DUMNVE=GPAR
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      RMC=RMC0+RMC**CPAR/DUMNVE
   33 RMD=RMD0
      IF(NTD.LE.1) GOTO 34
      NTD1=NTD
      IF(NTD1.GT.5) NTD1=5
      CALL GRNDM(RNDM,1)
      RAN=RNDM(1)
      RMD=-LOG(1.-RAN)
      GPAR=G1PAR(NTD1)
      CPAR=C1PAR(NTD1)
      DUMNVE=GPAR
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      RMD=RMD0+RMD**CPAR/DUMNVE
   34 IF(RMC+RMD.LE.RS) GOTO 35
      IF (RMC.LE.RMC0.AND.RMD.LE.RMD0) THEN
         HNRMDC = 0.999*RS/(RMC+RMD)
         RMD = RMD*HNRMDC
         RMC = RMC*HNRMDC
      ELSE
         RMC=0.1*RMC0+0.9*RMC
         RMD=0.1*RMD0+0.9*RMD
      END IF
      GOTO 34
   35 IF(NTE.LE.0) GOTO 38
      RME=RME0
      IF(NTE.EQ.1) GOTO 38
      NTE1=NTE
      IF(NTE1.GT.5) NTE1=5
      CALL GRNDM(RNDM,1)
      RAN=RNDM(1)
      RME=-LOG(1.-RAN)
      GPAR=G1PAR(NTE1)
      CPAR=C1PAR(NTE1)
      DUMNVE=GPAR
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      RME=RME0+RME**CPAR/DUMNVE
C**
C** SET BEAM , TARGET OF FIRST INTERACTION IN CMS
C**
   38 PV( 1,MX1) =0.
      PV( 2,MX1) =0.
      PV( 3,MX1) =P
      PV( 5,MX1) =ABS(AMAS)
      PV( 4,MX1) =SQRT(P*P+AMAS*AMAS)
      PV( 1,MX2) =0.
      PV( 2,MX2) =0.
      PV( 3,MX2) =0.
      PV( 4,MX2) =MP
      PV( 5,MX2) =MP
 
C** TRANSFORM INTO CMS.
 
      CALL ADD(MX1,MX2,MX)
      CALL LOR(MX1,MX,MX1)
      CALL LOR(MX2,MX,MX2)
      PF=(S+RMD*RMD-RMC*RMC)**2 - 4*S*RMD*RMD
      IF(PF.LT.0.0001) PF=0.0001
      DUMNVE=2.0*RS
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      PF=SQRT(PF)/DUMNVE
      IF(NPRT(4)) WRITE(6,2002) PF,RMC,RMD,RS
C**
C** SET FINAL STATE MASSES AND ENERGIES IN CMS
C**
      PV(5,MX3) =RMC
      PV(5,MX4) =RMD
      PV(4,MX3) =SQRT(PF*PF+RMC*RMC)
      PV(4,MX4) =SQRT(PF*PF+RMD*RMD)
C**
C** SET |T| AND |TMIN|
C**
      T=-1.0E10
      CALL GRNDM(RNDM,1)
      IF (B .NE. 0.0) T=LOG(1.-RNDM(1))/B
      CALL LENGTX(MX1,PIN)
      TACMIN=(PV(4,MX1) -PV(4,MX3))**2 -(PIN-PF)**2
C**
C** CACULATE (SIN(TETA/2.)**2 AND COS(TETA), SET AZIMUTH ANGLE PHI
C**
      DUMNVE=4.0*PIN*PF
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      CTET=-(T-TACMIN)/DUMNVE
      CTET=1.0-2.0*CTET
      IF (CTET .GT. 1.0) CTET=1.0
      IF (CTET .LT. -1.0) CTET=-1.0
      DUMNVE=1.0-CTET*CTET
      IF (DUMNVE .LT. 0.0) DUMNVE=0.0
      STET=SQRT(DUMNVE)
      CALL GRNDM(RNDM,1)
      PHI=RNDM(1)*TWPI
C**
C** CALCULATE FINAL STATE MOMENTA IN CMS
C**
      PV(1,MX3) =PF*STET*SIN(PHI)
      PV(2,MX3) =PF*STET*COS(PHI)
      PV(3,MX3) =PF*CTET
      PV(1,MX4) =-PV(1,MX3)
      PV(2,MX4) =-PV(2,MX3)
      PV(3,MX4) =-PV(3,MX3)
C**
C** SIMULATE BACKWARD NUCLEON CLUSTER IN LAB. SYSTEM AND TRANSFORM IN
C** CMS.
C**
      IF(NTE.EQ.0) GOTO 28
      GA=1.2
      EKIT1=0.04
      EKIT2=0.6
      IF(EK.GT.5.) GOTO 666
      EKIT1=EKIT1*EK**2/25.
      EKIT2=EKIT2*EK**2/25.
  666 A=(1.-GA)/(EKIT2**(1.-GA)-EKIT1**(1.-GA))
      DO 29 I=1,NT
      IF(SIDE(I).GT.-1.5) GOTO 29
      CALL GRNDM(RNDM,3)
      RAN=RNDM(1)
      EKIT=(RAN*(1.-GA)/A+EKIT1**(1.-GA))**(1./(1.-GA))
      PV(4,I)=EKIT+PV(5,I)
      DUMNVE=ABS(PV(4,I)**2-PV(5,I)**2)
      PP=SQRT(DUMNVE)
      RAN=RNDM(2)
      COST=LOG(2.23*RAN+0.383)/0.96
      IF (COST .LT. -1.0) COST=-1.0
      IF (COST .GT. 1.0) COST=1.0
      DUMNVE=1.0-COST*COST
      IF (DUMNVE .LT. 0.0) DUMNVE=0.0
      SINT=SQRT(DUMNVE)
      PHI=TWPI*RNDM(3)
      PV(1,I)=PP*SINT*SIN(PHI)
      PV(2,I)=PP*SINT*COS(PHI)
      PV(3,I)=PP*COST
      CALL LOR(I,MX,I)
   29 CONTINUE
C**
C** FRAGMENTATION OF FORWARD CLUSTER AND BACKWARD MESON CLUSTER
C**
   28 PV(1,1)=PV(1,MX3)
      PV(2,1)=PV(2,MX3)
      PV(3,1)=PV(3,MX3)
      PV(4,1)=PV(4,MX3)
      PV(1,2)=PV(1,MX4)
      PV(2,2)=PV(2,MX4)
      PV(3,2)=PV(3,MX4)
      PV(4,2)=PV(4,MX4)
      DO 17 I=MX5,MX6
      DO 16 J=1,3
   16 PV(J,I)=-PV(J,I-2)
      DO 17 J=4,5
   17 PV(J,I)= PV(J,I-2)
      KGENEV=1
      IF(NTC.LE.1) GOTO 26
      TECM=PV(5,MX3)
      NPG=0
      DO 18 I=1,NT
      IF(SIDE(I).LT.0.) GOTO 18
      IF(NPG.EQ.18) THEN
         SIDE(I)=-SIDE(I)
         GOTO 18
      ENDIF
      NPG=NPG+1
      AMASS(NPG)=ABS(PV(5,I))
   18 CONTINUE
      IF(NPRT(4)) WRITE(NEWBCD,2004) TECM,NPG,(AMASS(I),I=1,NPG)
      CALL PHASP
      NPG=0
      DO 19 I=1,NT
      IF(SIDE(I).LT.0.OR.NPG.GE.18) GOTO 19
      NPG=NPG+1
      PV(1,I)=PCM(1,NPG)
      PV(2,I)=PCM(2,NPG)
      PV(3,I)=PCM(3,NPG)
      PV(4,I)=PCM(4,NPG)
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,5)
      CALL LOR(I,MX5,I)
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,10),IPA(I),SIDE(I)
   19 CONTINUE
   26 IF(NTD.LE.1) GOTO 27
      TECM=PV(5,MX4)
      NPG=0
      DO 20 I=1,NT
      IF(SIDE(I).GT.0..OR.SIDE(I).LT.-1.5) GOTO 20
      IF(NPG.EQ.18) THEN
         SIDE(I)=-2.
         PV(4,I)=ABS(PV(5,I))
         DO 48 J=1,3
            PV(J,I)=0.
   48    CONTINUE
         GOTO 20
      ENDIF
      NPG=NPG+1
      AMASS(NPG)=ABS(PV(5,I))
   20 CONTINUE
      IF(NPRT(4)) WRITE(NEWBCD,2004) TECM,NPG,(AMASS(I),I=1,NPG)
      CALL PHASP
      NPG=0
      DO 21 I=1,NT
      IF(SIDE(I).GT.0..OR.SIDE(I).LT.-1.5) GOTO 21
      NPG=NPG+1
      PV(1,I)=PCM(1,NPG)
      PV(2,I)=PCM(2,NPG)
      PV(3,I)=PCM(3,NPG)
      PV(4,I)=PCM(4,NPG)
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,5)
      CALL LOR(I,MX6,I)
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,10),IPA(I),SIDE(I)
   21 CONTINUE
C**
C** LORENTZ TRANSFORMATION IN LAB SYSTEM
C**
   27 TARG=0.
      DO 36 I=1,NT
      IF(PV(5,I).GT.0.5) TARG=TARG+1.
      CALL LOR(I,MX2,I)
   36 CONTINUE
      IF(TARG.LT.0.5) TARG=1.
C**
C** SOMETIMES THE LEADING STRANGE PARTICLES ARE LOST , SET THEM BACK
C**
      IF(LEAD.EQ.0) GOTO 6085
      DO 6081 I=1,NT
      IF(ABS(IPA(I)).EQ.LEAD) GOTO 6085
 6081 CONTINUE
      I=1
      IF(LEAD.GE.14.AND.ABS(IPA(2)).GE.14) I=2
      IF(LEAD.LT.14.AND.ABS(IPA(2)).LT.14) I=2
      IPA(I)=LEAD
      EKIN=PV(4,I)-ABS(PV(5,I))
      PV(5,I)=RMASS(LEAD)
      PV(7,I)=1.
      IF(PV(5,I).LT.0.) PV(7,I)=-1.
      PV(5,I)=ABS(PV(5,I))
      PV(6,I)=RCHARG(LEAD)
      PV(4,I)=PV(5,I)+EKIN
      CALL LENGTX(I,PP)
      DUMNVE=ABS(PV(4,I)**2-PV(5,I)**2)
      PP1=SQRT(DUMNVE)
C
      IF (PP .GE. 1.0E-6) GO TO 8000
      CALL GRNDM(RNDM,2)
      RTHNVE=PI*RNDM(1)
      PHINVE=TWPI*RNDM(2)
      PV(1,I)=PP1*SIN(RTHNVE)*COS(PHINVE)
      PV(2,I)=PP1*SIN(RTHNVE)*SIN(PHINVE)
      PV(3,I)=PP1*COS(RTHNVE)
      GO TO 8001
 8000 CONTINUE
      PV(1,I)=PV(1,I)*PP1/PP
      PV(2,I)=PV(2,I)*PP1/PP
      PV(3,I)=PV(3,I)*PP1/PP
 8001 CONTINUE
C
C** FOR VARIOUS REASONS, THE ENERGY BALANCE IS NOT SUFFICIENT,
C** CHECK THAT,  ENERGY BALANCE, ANGLE OF FINAL SYSTEM E.T.C.
 6085 KGENEV=1
      PV(1,MX4) =0.
      PV(2,MX4) =0.
      PV(3,MX4) =P
      PV(4,MX4) =SQRT(P*P+AMAS*AMAS)
      PV(5,MX4) =ABS(AMAS)
      EKIN0=PV(4,MX4) -PV(5,MX4)
      PV(1,MX5) =0.
      PV(2,MX5) =0.
      PV(3,MX5) =0.
      PV(4,MX5) =MP*TARG
      PV(5,MX5) =PV(4,MX5)
      EKIN=PV(4,MX4) +PV(4,MX5)
      I=MX4
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,5)
      I=MX5
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,5)
      CALL ADD(MX4,MX5,MX6)
      CALL LOR(MX4,MX6,MX4)
      CALL LOR(MX5,MX6,MX5)
      TECM=PV(4,MX4) +PV(4,MX5)
      NPG=NT
      PV(1,MX8) =0.
      PV(2,MX8) =0.
      PV(3,MX8) =0.
      PV(4,MX8) =0.
      PV(5,MX8) =0.
      EKIN1=0.
      DO 598 I=1,NPG
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,10),IPA(I),SIDE(I)
      CALL ADD(MX8,I,MX8)
      EKIN1=EKIN1+PV(4,I)-PV(5,I)
      EKIN=EKIN-PV(5,I)
      IF(I.GT.18) GOTO 598
      AMASS(I)=PV(5,I)
  598 CONTINUE
      IF(NPG.GT.18) GOTO 597
      CALL PHASP
      EKIN=0.
      DO 599 I=1,NPG
      PV(1,MX7)=PCM(1,I)
      PV(2,MX7)=PCM(2,I)
      PV(3,MX7)=PCM(3,I)
      PV(4,MX7)=PCM(4,I)
      PV(5,MX7)=AMASS(I)
      CALL LOR(MX7,MX5,MX7)
  599 EKIN=EKIN+PV(4,MX7)-PV(5,MX7)
      CALL ANG(MX8,MX4,COST,TETA)
      IF(NPRT(4)) WRITE(NEWBCD,2003) TETA,EKIN0,EKIN1,EKIN
C**
C** MAKE SHURE, THAT  KINETIC ENERGIES ARE CORRECT
C** THE 3. CLUSTER IS NOT PRODUCED WITHIN PROPER KINEMATICS!!!
C** EKIN= KINETIC ENERGY THEORETICALLY
C** EKIN1= KINETIC ENERGY SIMULATED
C**
  597 IF(EKIN1.EQ.0.) GOTO 600
      PV(1,MX7) =0.
      PV(2,MX7) =0.
      PV(3,MX7) =0.
      PV(4,MX7) =0.
      PV(5,MX7) =0.
      WGT=EKIN/EKIN1
      EKIN1=0.
      DO 602 I=1,NT
      EKIN=PV(4,I)-PV(5,I)
      EKIN=EKIN*WGT
      PV(4,I)=EKIN+PV(5,I)
      DUMNVE=ABS(PV(4,I)**2-PV(5,I)**2)
      PP=SQRT(DUMNVE)
      CALL LENGTX(I,PP1)
C
      IF (PP1 .GE. 1.0E-6) GO TO 8002
      CALL GRNDM(RNDM,2)
      RTHNVE=PI*RNDM(1)
      PHINVE=TWPI*RNDM(2)
      PV(1,I)=PP*SIN(RTHNVE)*COS(PHINVE)
      PV(2,I)=PP*SIN(RTHNVE)*SIN(PHINVE)
      PV(3,I)=PP*COS(RTHNVE)
      GO TO 8003
 8002 CONTINUE
      PV(1,I)=PV(1,I)*PP/PP1
      PV(2,I)=PV(2,I)*PP/PP1
      PV(3,I)=PV(3,I)*PP/PP1
 8003 CONTINUE
C
      EKIN1=EKIN1+EKIN
      CALL ADD(MX7,I,MX7)
  602 CONTINUE
      CALL ANG(MX7,MX4,COST,TETA)
      IF(NPRT(4)) WRITE(NEWBCD,2003) TETA,EKIN0,EKIN1
C**
C** ROTATE IN DIRECTION OF Z-AXIS, SEE COMMENTS IN 'GENXPT'
C**
  600 PV(1,MX7)=0.
      PV(2,MX7)=0.
      PV(3,MX7)=0.
      PV(4,MX7)=0.
      PV(5,MX7)=0.
      DO 596 I=1,NT
  596 CALL ADD(MX7,I,MX7)
*          call rannor(ran1,ran2)
      CALL GRNDM(RNDM,2)
      RY=RNDM(1)
      RZ=RNDM(2)
      RX=6.283185*RZ
      A1=SQRT(-2.*LOG(RY))
      RAN1=A1*SIN(RX)
      RAN2=A1*COS(RX)
      PV(1,MX7)=PV(1,MX7)+RAN1*0.020*TARG
      PV(2,MX7)=PV(2,MX7)+RAN2*0.020*TARG
      CALL DEFS(MX4,MX7,MX8)
      PV(1,MX7)=0.
      PV(2,MX7)=0.
      PV(3,MX7)=0.
      PV(4,MX7)=0.
      PV(5,MX7)=0.
      DO 595 I=1,NT
      CALL TRAC(I,MX8,I)
  595 CALL ADD(MX7,I,MX7)
      CALL ANG(MX7,MX4,COST,TETA)
      IF(NPRT(4)) WRITE(NEWBCD,2003) TETA
C**
C** ROTATE IN DIRECTION OF PRIMARY PARTICLE
C**
      DEKIN=0.
      NPIONS=0
      EK1=0.
      DO 25 I=1,NT
      CALL DEFS1(I,MXGKPV-1,I)
      IF(NPRT(4)) WRITE(NEWBCD,2001) I,(PV(J,I),J=1,10),IPA(I),SIDE(I)
      IF(ATNO2.LT.1.5) GOTO 25
      CALL LENGTX(I,PP)
      EKIN=PV(4,I)-ABS(PV(5,I))
      CALL NORMAL(RAN)
      EKIN=EKIN-CFA*(1.+0.5*RAN)
      IF (EKIN .LT. 1.0E-6) EKIN=1.0E-6
      CALL STEEQ(XXH,I)
      DEKIN=DEKIN+EKIN*(1.-XXH)
      EKIN=EKIN*XXH
      IF(ABS(IPA(I)).GE.7.AND.ABS(IPA(I)).LE.9) NPIONS=NPIONS+1
      IF(ABS(IPA(I)).GE.7.AND.ABS(IPA(I)).LE.9) EK1=EK1+EKIN
      PP1=SQRT(EKIN*(EKIN+2.*ABS(PV(5,I))))
      PV(4,I)=EKIN+ABS(PV(5,I))
C
      IF (PP .GE. 1.0E-6) GO TO 8004
      CALL GRNDM(RNDM,2)
      RTHNVE=PI*RNDM(1)
      PHINVE=TWPI*RNDM(2)
      PV(1,I)=PP1*SIN(RTHNVE)*COS(PHINVE)
      PV(2,I)=PP1*SIN(RTHNVE)*SIN(PHINVE)
      PV(3,I)=PP1*COS(RTHNVE)
      GO TO 8005
 8004 CONTINUE
      PV(1,I)=PV(1,I)*PP1/PP
      PV(2,I)=PV(2,I)*PP1/PP
      PV(3,I)=PV(3,I)*PP1/PP
 8005 CONTINUE
C
   25 CONTINUE
      IF(EK1.EQ.0.) GOTO 23
      IF(NPIONS.LE.0) GOTO 23
      DEKIN=1.+DEKIN/EK1
      DO 22 I=1,NT
      IF(ABS(IPA(I)).LT.7.OR.ABS(IPA(I)).GT.9) GOTO 22
      CALL LENGTX(I,PP)
      EKIN=PV(4,I)-ABS(PV(5,I))
      EKIN=EKIN*DEKIN
      IF (EKIN .LT. 1.0E-6) EKIN=1.0E-6
      PP1=SQRT(EKIN*(EKIN+2.*ABS(PV(5,I))))
      PV(4,I)=EKIN+ABS(PV(5,I))
C
      IF (PP .GE. 1.0E-6) GO TO 8006
      CALL GRNDM(RNDM,2)
      RTHNVE=PI*RNDM(1)
      PHINVE=TWPI*RNDM(2)
      PV(1,I)=PP1*SIN(RTHNVE)*COS(PHINVE)
      PV(2,I)=PP1*SIN(RTHNVE)*SIN(PHINVE)
      PV(3,I)=PP1*COS(RTHNVE)
      GO TO 8007
 8006 CONTINUE
      PV(1,I)=PV(1,I)*PP1/PP
      PV(2,I)=PV(2,I)*PP1/PP
      PV(3,I)=PV(3,I)*PP1/PP
 8007 CONTINUE
C
   22 CONTINUE
   23 IF(ATNO2.LT.1.5) GOTO 40
C**
C** ADD BLACK TRACK PARTICLES
C**
      SPALL=TARG
      CALL HIGHAB(SPROB)
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).LT.SPROB) GOTO 40
      TEX=ENP(1)
      SPALL=TARG
      IF(TEX.LT.0.001) GOTO 445
      BLACK=(1.5+1.25*TARG)*ENP(1)/(ENP(1)+ENP(3))
      CALL POISSO(BLACK,NBL)
      IF(NPRT(4))
     *WRITE(NEWBCD,3003) NBL,TEX
      IF(IFIX(TARG)+NBL.GT.ATNO2) NBL=ATNO2-TARG
      IF(NT+NBL.GT.MXGKPV-2) NBL=MXGKPV-2-NT
      IF(NBL.LE.0) GOTO 445
      EKIN=TEX/NBL
      EKIN2=0.
      CALL STEEP(XX)
      DO 441 I=1,NBL
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).LT.SPROB) GOTO 441
      IF(NT.EQ.MXGKPV-2) GOTO 441
      IF(EKIN2.GT.TEX) GOTO 443
      CALL GRNDM(RNDM,1)
      RAN1=RNDM(1)
      CALL NORMAL(RAN2)
      EKIN1=-EKIN*LOG(RAN1)-CFA*(1.+0.5*RAN2)
      IF(EKIN1.LT.0.0) EKIN1=-0.010*LOG(RAN1)
      EKIN1=EKIN1*XX
      EKIN2=EKIN2+EKIN1
      IF(EKIN2.GT.TEX) EKIN1=TEX-(EKIN2-EKIN1)
      IF (EKIN1 .LT. 0.0) EKIN1=1.0E-6
      IPA1=16
      PNRAT=1.-ZNO2/ATNO2
      CALL GRNDM(RNDM,3)
      IF(RNDM(1).GT.PNRAT) IPA1=14
      NT=NT+1
      SPALL=SPALL+1.
      COST=-1.0+RNDM(2)*2.0
      DUMNVE=1.0-COST*COST
      IF (DUMNVE .LT. 0.0) DUMNVE=0.0
      SINT=SQRT(DUMNVE)
      PHI=TWPI*RNDM(3)
      IPA(NT)=-IPA1
      SIDE(NT)=-4.
      PV(5,NT)=ABS(RMASS(IPA1))
      PV(6,NT)=RCHARG(IPA1)
      PV(7,NT)=1.
      PV(4,NT)=EKIN1+PV(5,NT)
      DUMNVE=ABS(PV(4,NT)**2-PV(5,NT)**2)
      PP=SQRT(DUMNVE)
      PV(1,NT)=PP*SINT*SIN(PHI)
      PV(2,NT)=PP*SINT*COS(PHI)
      PV(3,NT)=PP*COST
  441 CONTINUE
  443 IF(ATNO2.LT.10.) GOTO 445
      IF(EK.GT.2.0) GOTO 445
      II=NT+1
      KK=0
      EKA=EK
      IF(EKA.GT.1.) EKA=EKA*EKA
      IF(EKA.LT.0.1) EKA=0.1
      IKA=3.6*EXP((ZNO2**2/ATNO2-35.56)/6.45)/EKA
      IF(IKA.LE.0) GO TO 445
      DO 444 I=1,NT
      II=II-1
      IF(IPA(II).NE.-14) GOTO 444
      IPA(II)=-16
      IPA1  = 16
      PV(5,II)=ABS(RMASS(IPA1))
      PV(6,II)=RCHARG(IPA1)
      KK=KK+1
      IF(KK.GT.IKA) GOTO 445
  444 CONTINUE
  445 TEX=ENP(3)
      IF(TEX.LT.0.001) GOTO 40
      BLACK=(1.5+1.25*TARG)*ENP(3)/(ENP(1)+ENP(3))
      CALL POISSO(BLACK,NBL)
      IF(NT+NBL.GT.MXGKPV-2) NBL=MXGKPV-2-NT
      IF(NBL.LE.0) GOTO 40
      EKIN=TEX/NBL
      EKIN2=0.
      CALL STEEP(XX)
      IF(NPRT(4))
     *WRITE(NEWBCD,3004) NBL,TEX
      DO 442 I=1,NBL
      CALL GRNDM(RNDM,1)
      IF(RNDM(1).LT.SPROB) GOTO 442
      IF(NT.EQ.MXGKPV-2) GOTO 442
      IF(EKIN2.GT.TEX) GOTO 40
      CALL GRNDM(RNDM,1)
      RAN1=RNDM(1)
      CALL NORMAL(RAN2)
      EKIN1=-EKIN*LOG(RAN1)-CFA*(1.+0.5*RAN2)
      IF(EKIN1.LT.0.0) EKIN1=-0.005*LOG(RAN1)
      EKIN1=EKIN1*XX
      EKIN2=EKIN2+EKIN1
      IF(EKIN2.GT.TEX) EKIN1=TEX-(EKIN2-EKIN1)
      IF (EKIN1 .LT. 0.0) EKIN1=1.0E-6
      CALL GRNDM(RNDM,3)
      COST=-1.0+RNDM(1)*2.0
      DUMNVE=1.0-COST*COST
      IF (DUMNVE .LT. 0.0) DUMNVE=0.0
      SINT=SQRT(DUMNVE)
      PHI=TWPI*RNDM(2)
      RAN=RNDM(3)
      IPA(NT+1)=-30
      IF(RAN.GT.0.60) IPA(NT+1)=-31
      IF(RAN.GT.0.90) IPA(NT+1)=-32
      SIDE(NT+1)=-4.
      PV(5,NT+1)=(ABS(IPA(NT+1))-28)*MP
      SPALL=SPALL+PV(5,NT+1)*1.066
      IF(SPALL.GT.ATNO2) GOTO 40
      NT=NT+1
      PV(6,NT)=1.
      IF(IPA(NT).EQ.-32) PV(6,NT)=2.
      PV(7,NT)=1.
      PV(4,NT)=PV(5,NT)+EKIN1
      DUMNVE=ABS(PV(4,NT)**2-PV(5,NT)**2)
      PP=SQRT(DUMNVE)
      PV(1,NT)=PP*SINT*SIN(PHI)
      PV(2,NT)=PP*SINT*COS(PHI)
      PV(3,NT)=PP*COST
  442 CONTINUE
C**
C** STORE ON EVENT COMMON
C**
   40 CALL GRNDM(RNDM,1)
      IF(RS.GT.(4.+RNDM(1)*1.)) GOTO 42
      DO 41 I=1,NT
      CALL LENGTX(I,ETB)
      IF(ETB.LT.P) GOTO 41
      ETF=P
      PV(4,I)=SQRT(PV(5,I)**2+ETF**2)
      DUMNVE=ETB
      IF (DUMNVE .EQ. 0.0) DUMNVE=1.0E-10
      ETF=ETF/DUMNVE
      PV(1,I)=PV(1,I)*ETF
      PV(2,I)=PV(2,I)*ETF
      PV(3,I)=PV(3,I)*ETF
   41 CONTINUE
   42 EKIN=PV(4,MXGKPV)-ABS(PV(5,MXGKPV))
      EKIN1=PV(4,MXGKPV-1)-ABS(PV(5,MXGKPV-1))
      EKIN2=0.
      CALL TDELAY(TOF1)
      CALL GRNDM(RNDM,1)
      RAN=RNDM(1)
      TOF=TOF-TOF1*LOG(RAN)
      DO 44 I=1,NT
      IF(PV(7,I).LT.0.) PV(5,I)=-PV(5,I)
      PV(7,I)=TOF
      PV(8,I)=ABS(IPA(I))
      PV(9,I)=0.
   44 PV(10,I)=0.
      CALL GHETUN(NT)
      DO 45 I=1,NT
         EKIN2=EKIN2+PV(4,I)-ABS(PV(5,I))
   45 CONTINUE
      EKIN2=(EKIN2-EKIN)/EKIN
      IF(NPRT(4))
     $            WRITE(NEWBCD,2006) NT,EKIN,ENP(1),ENP(3),EKIN1,EKIN2
      IF(EKIN2.GT.0.2) GOTO 60
      INTCT=INTCT+1.
      NMODE=3
      IF(SPALL.LT.0.5.AND.ATNO2.GT.1.5) NMODE=14
      CALL SETCUR(NT)
      NTK=NTK+1
      IF(NT.EQ.1) GOTO 300
      DO 50 II=2,NT
      I=II-1
      IF(NTOT.LT.NSIZE/12) GOTO 43
      GO TO 9999
   43 CALL SETTRK(I)
   50 CONTINUE
 300  CONTINUE
      GO TO 9999
C**
C** IT IS NOT POSSIBLE TO PRODUCE A PROPER TWO CLUSTER FINAL STATE.
C** CONTINUE WITH QUASI ELASTIC SCATTERING
C**
   60 IF(NPRT(4)) WRITE(NEWBCD,2005)
      DO 61 I=3,MXGKCU
   61 IPA(I)=0
      IPA(1)=IPART
      IPA(2)=14
      IF(NFL.EQ.2) IPA(2)=16
      CALL TWOB(IPPP,NFL,AVERN)
      GO TO 9999
C
 2000 FORMAT(' *HIGCLU* CMS PARAMETERS OF FINAL STATE PARTICLES',
     $ ' AFTER ',I3,' TRIALS')
 2001 FORMAT(' *HIGCLU* TRACK',2X,I3,2X,10F8.2,2X,I3,2X,F3.0)
 2002 FORMAT(' *HIGCLU* MOMENTUM ',F8.3,' MASSES ',2F8.4,' RS ',F8.4)
 2003 FORMAT(' *HIGCLU* TETA,EKIN0,EKIN1,EKIN ',4F10.4)
 2004 FORMAT(' *HIGCLU* TECM,NPB,MASSES: ',F10.4,1X,I3,1X,8F10.4/
     $ 1H ,26X,15X,8F10.4)
 2005 FORMAT(' *HIGCLU* NUMBER OF FINAL STATE PARTICLES',
     $ ' LESS THAN 2 ==> CONTINUE WITH 2-BODY SCATTERING')
 2006 FORMAT(' *HIGCLU*  COMP.',1X,I5,1X,5F7.2)
 3001 FORMAT(' *HIGCLU* NUCLEAR EXCITATION ',I5,' PARTICLES PRODUCED',
     $ ' IN ADDITION TO',I5,' NORMAL PARTICLES')
 3003 FORMAT(' *HIGCLU* ',I3,' BLACK TRACK PARTICLES PRODUCED',
     $ ' WITH TOTAL KINETIC ENERGY OF ',F8.3,' GEV')
 3004 FORMAT(' *HIGCLU* ',I5,' HEAVY FRAGMENTS WITH TOTAL ENERGY OF ',
     $ F8.4,' GEV')
C
 9999 CONTINUE
      END
*CMZ :  1.40/05 28/08/98  10.37.39  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.21  by  S.Giani
*-- Author :
      SUBROUTINE GFKINE(ITRA,VERT,PVERT,IPART,NVERT,UBUF,NWBUF)
*
************************************************************************
*                                                                      *
*           Retrieves Vertex and Track parameters                      *
*           -------------------------------------                      *
*                                                                      *
*  Retrieves parameters for a track with a long lifetime.              *
*                                                                      *
*  Input:                                                              *
*    ITRA      track number for which parameters are requested         *
*                                                                      *
*  Output:                                                             *
*    VERT      vector origin of the track                              *
*    PVERT     4 momentum components at the track origin               *
*    IPART     particle type (=0 if track ITRA does not exist)         *
*    NVERT     vertex number origin of the track                       *
*    UBUF      user words stored in GSKINE.                            *
*                                                                      *
*    ==>Called by : <USER>, GTREVE                                     *
*       Author    R.Brun  *********                                    *
*  modifications:                                                      *
*  PN, 28.08.98:  interface to kine bank via LgKINE                    *
*                                                                      *
************************************************************************
*
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
      DIMENSION VERT(3),PVERT(4),UBUF(*)
C.
C.    ------------------------------------------------------------------
C.
      IPART  = 0
      IF (JKINE.LE.0)GO TO 99
      IF (ITRA.LE.0)GO TO 99
      IF (ITRA.GT.NTRACK)GO TO 99
C
      JK = LgKINE(JKINE,ITRA)
      IF (JK.LE.0)GO TO 99
      NV = Q(JK + 6)
      IF (JVERTX.LE.0)GO TO 99
      JV = LQ(JVERTX- NV)
      IF (JV.LE.0)GO TO 99
      DO 10 I=1,3
  10  VERT(I) = Q(JV + I)
*     TOFG=Q(JV+4)
C
      DO 20 I=1,4
  20  PVERT(I) = Q(JK + I)
      IPART = Q(JK + 5)
      NVERT = Q(JK + 6)
      NLINK = IQ(JK-2)
      NWBUF  = 0
      IF (NLINK.LE.0)GO TO 99
      JKU = LQ(JK- 1)
      IF (JKU.LE.0)GO TO 99
      NWBUF = IQ(JKU-1)
      DO 30 I=1,NWBUF
  30  UBUF(I)=Q(JKU+I)
C
  99  RETURN
      END
*CMZ :  1.40/05 28/08/98  10.42.37  by  Pavel Nevski
*CMZ :  3.21/02 29/03/94  15.41.21  by  S.Giani
*-- Author :
      SUBROUTINE GPKINE(IT)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Prints kinematics bank JKINE for track number IT         *
C.    *       If IT=0 Prints all kinematics banks                      *
C.    *                                                                *
C.    *    ==>Called by : <USER>, GPRINT                               *
C.    *       Author    R.Brun  *********                              *
C.    *  modifications:                                                *
C.    *  PN, 28.08.98:  interface to kine bank via LgKINE              *
C.    *                                                                *
C.    ******************************************************************
C.
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
*KEND.
C.
C.    ------------------------------------------------------------------
C.
      WRITE(CHMAIL,1000)
      CALL GMAIL(1,0)
C
      I1=1
      I2=NTRACK
      IF(IT.NE.0)I1=IT
      IF(IT.NE.0)I2=IT
      IF(I2.GT.NTRACK)GO TO 99
      IF(I1.LT.1)GO TO 99
      IF(JKINE.LE.0)GO TO 99
C
      DO 20 ITRACK=I1,I2
         JK=LgKINE(JKINE,ITRACK)
         IF(JK.NE.0)THEN
            IPART=Q(JK+5)
            JPA=LQ(JPART-IPART)
            NL=IQ(JK-2)
            NG=Q(JK+7)+7
            NW=MIN(NG,16)
            WRITE(CHMAIL,2000)ITRACK,IQ(JPA+1),IQ(JPA+2),IQ(JPA+3),IPART
     +       ,(Q(JK+I),I=1,4),Q(JK+6),(INT(Q(JK+L)),L=8,NW)
   10       CALL GMAIL(0,0)
            IF(NG-NW.GT.0) THEN
               NS=NW+1
               NW=MIN(NG,NW+9)
               WRITE(CHMAIL,3000) (INT(Q(JK+L)),L=NS,NW)
               GO TO 10
            END IF
            IF(NL.GT.0) THEN
               JUK = LQ(JK-1)
               IF (JUK.GT.0) THEN
                  WRITE(CHMAIL,4000)
                  CALL GMAIL(0,0)
                  ND  = IQ(JUK-1)
                  NW=MIN(ND,9)
                  WRITE(CHMAIL,5000) (Q(JUK+L),L=1,NW)
   15             CALL GMAIL(0,0)
                  IF(ND-NW.GT.0) THEN
                     NS=NW+1
                     NW=MIN(ND,NW+9)
                     WRITE(CHMAIL,5000) (Q(JUK+L),L=NS,NW)
                     GO TO 15
                  END IF
               END IF
            END IF
         ENDIF
   20 CONTINUE
C
 1000 FORMAT(3X,'Kine',5X,'Name',10X,'Type',5X,'Px',9X,'Py',
     +       9X,'Pz',7X,'Energy',5X,'Vorigin',2X,'Vgener')
 2000 FORMAT(1X,I5,6X,3A4,I5,5(1X,F10.4),9(1X,I4))
 3000 FORMAT(84X,9(1X,I4))
 4000 FORMAT(62X,'User words')
 5000 FORMAT(1X,9(2X,E12.5))
C
  99  RETURN
      END
*CMZ :  1.30/00 11/02/96  22.08.12  by  Pavel Nevski
*CMZ :  1.00/01 09/12/95  16.20.44  by  Pavel Nevski
*-- Author :    O.Schaile
************************************************************************
*                                                                      *
      SUBROUTINE DZE2HT(LUNIN,LUNUSE, FLAG, UPUP1)
*                                                                      *
*     convert DZEDIT SGML to HTML, plug in links                       *
*                                                                      *
*     flag:       Steering flag:                                       *
*                 0 make all hyperlinks internal only                  *
*                 1 add file name in first up bank                     *
*                 2 add file names in all links                        *
*                 3 as 2 and make 1 file/bank                          *
*     upup1:      Id of Upbank of Upbank of top bank                   *
*                                                                      *
*     output file name(s): BankId//UpId.html                           *
*                                                                      *
*     Author: O.Schaile                                                *
*                                                                      *
************************************************************************
      IMPLICIT NONE
 
      INTEGER       LUNIN,LUNUSE
      CHARACTER*80  CFOUT
      CHARACTER*4   UPUP1
      INTEGER       FLAG
      INTEGER       ML, MS
      PARAMETER     (ML=2000, MS=5000)
      CHARACTER*132 CB(ML), CL
      CHARACTER*8   CSTACK(MS), CLIST(MS)
      CHARACTER*4   BANKID, UPID, UPUPID, DOWNID
      CHARACTER*13  CF
      CHARACTER*4   DZE2US
      INTEGER IPBKID,IPUP,IPLSTA,IPLLAS, ISTAT, IP, IPSTAC,I,J,K,NC
     +        ,INDEXA,INDEXN,INDEXC,LNBLNK, IS, NUP,NCUPID,NCCF,IPLIST
     +        ,LUNOUT, NBANKS, NFILES
      LOGICAL EOF, IGNORE
*---
      IF(UPUP1.EQ.' ')THEN
         UPUP1='NONE'
      ELSE
         UPUP1=DZE2US(UPUP1)
      ENDIF
      EOF=.FALSE.
      IGNORE=.FALSE.
      NUP = 0
      NBANKS=0
      NFILES=0
      LUNOUT=0
 
*     Run through files and find all banks
      IPBKID=0
      IPUP=0
      IPLIST=0
*  10    READ(LUNIN,'(A)',END=50)CL
10    CALL DZDCRD(LUNIN,CL,ISTAT)
      IF(ISTAT.NE.0)GOTO 50
      IF(CL(2:9).EQ.'Bank IDH')THEN
         IPBKID=1
         CB(1)=CL
         BANKID=CL(12:15)
      ELSE IF(CL(2:5).EQ.'Up  ')THEN
         IF(IPBKID.EQ.0)THEN
            WRITE(*,*)'Prescan: Upbank appears before bank'
            GOTO 999
         ENDIF
         UPID=CL(12:15)
         BANKID=DZE2US(BANKID)
         UPID  =DZE2US(UPID)
         IPLIST=IPLIST+1
         IF(IPLIST.GT.MS)THEN
            WRITE(*,*)'Too many banks',IPLIST
            GOTO 999
         ENDIF
         CLIST(IPLIST)=BANKID//UPID
         IPBKID=0
      ENDIF
      GOTO 10
 
 50   CONTINUE
 
      REWIND(LUNIN)
*     LOOP ON BANKS
 
      IPSTAC=0
 100  CONTINUE
      IP=0
      IPBKID=0
      IPUP=0
      IPLSTA=0
      IPLLAS=0
*   110  READ(LUNIN,'(A)',END=150)CL
 110    CALL DZDCRD(LUNIN,CL,ISTAT)
      IF(ISTAT.NE.0)GOTO 150
*     IGNORE ALL CONTROL LINES
      IF(CL(1:4).EQ.'<FIG')IGNORE=.TRUE.
      IF(CL(1:5).EQ.'</FIG')IGNORE=.FALSE.
      IF(IGNORE)GOTO 110
      IF(CL(1:1).EQ.'<')GOTO 110
      IF(CL(1:2).EQ.' |')GOTO 110
      IF(CL(1:11).EQ.' ----------')GOTO 110
*     GET HERE FOR START OF A NEW BANK
 115  CONTINUE
      IF(CL(2:9).EQ.'Bank IDH')THEN
*        ONE FILE/BANK
         IF(FLAG.GE.3)THEN
            IF(LUNOUT.NE.0)THEN
               CLOSE(LUNOUT)
               LUNOUT=0
            ENDIF
         ENDIF
         IF(IPBKID.NE.0)THEN
            NBANKS=NBANKS+1
            IF(IPLSTA.NE.0 .AND. IPLLAS.EQ.0)IPLLAS=IP
            IPSTAC=IPSTAC+1
            IF(IPSTAC.GT.MS)THEN
               WRITE(*,*)'Too many banks'
               GOTO 999
            ENDIF
*
            NCUPID=LNBLNK(UPID)
            BANKID=DZE2US(BANKID)
            UPID  =DZE2US(UPID)
            IF(LUNOUT.LE.0)THEN
               LUNOUT=LUNUSE
               CALL CUTOL(CFOUT)
               CFOUT=BANKID//UPID//'.html'
               CALL KUOPEN(LUNOUT,CFOUT(1:LNBLNK(CFOUT)),
     +                    'UNKNOWN',ISTAT)
               NFILES=NFILES+1
               WRITE(LUNOUT,'(A)')'<html>'
               WRITE(LUNOUT,'(A)')'<head>'
               WRITE(LUNOUT,'(A)')'<body>'
               WRITE(LUNOUT,'(A)')'<isindex>'
               WRITE(LUNOUT,'(A)')'</head>'
               WRITE(LUNOUT,'(A)')'<body>'
               WRITE(LUNOUT,'(A)')'<pre>'
            ENDIF
            CSTACK(IPSTAC)=BANKID//UPID
            DO I=1,IP
               NC = LNBLNK(CB(I))
               IF(I.EQ.IPBKID)THEN
                  WRITE(LUNOUT,'(A)')'<hr>'
                  WRITE(LUNOUT,'(A)')'<a name="'
     +            //BANKID//UPID//'"><b>'//
     +            CB(I)(1:NC)//'</b></a>'
               ELSE IF(I.EQ.IPUP .AND. UPID.NE.'NONE')THEN
*                 FIRST FIND UP BANK OF IT
                  IF(IPSTAC.EQ.1 .AND. UPUP1.NE.' ')THEN
                     UPUPID=UPUP1
                  ELSE
                     UPUPID='NONE'
                     IF(IPSTAC.GT.1)THEN
                        DO K=IPSTAC-1,1,-1
                           IF(CSTACK(K)(1:4).EQ.UPID)THEN
                              UPUPID=CSTACK(K)(5:8)
                              GOTO 120
                           ENDIF
                        ENDDO
 120                    CONTINUE
                     ENDIF
                  ENDIF
                  IF((FLAG.GE.1 .AND. NUP .EQ.0) .OR.
     +                FLAG.GE.2) THEN
                     CF=UPID//UPUPID//'.html'
                     CALL CUTOL(CF)
                     NCCF=LNBLNK(CF)
                  ELSE
                     NCCF=0
                  ENDIF
                  NUP=NUP+1
                  NC=MAX(NC,16)
                  IF(NCCF.GT.0)THEN
                     WRITE(LUNOUT,'(A)')' Up        <a href="'//
     +                           CF//'#'//UPID//UPUPID//
     +                      '"><b>'//CB(I)(12:15)//'</b></a>'//
     +                        CB(I)(16:NC)
                  ELSE
                     WRITE(LUNOUT,'(A)')' Up        <a href="'//
     +                                       '#'//upid//upupid//
     +                      '"><b>'//CB(I)(12:15)//'</b></a>'//
     +                        CB(I)(16:NC)
                  ENDIF
               ELSEIF(IPLSTA.NE.0.AND.I.GE.IPLSTA.AND.I.LE.IPLLAS)THEN
                  IS=INDEXC(CB(I),' ')
                  IF(IS.LE.0)GOTO 145
*                 is it an integer, i.e. only numbers or space?
                  DO 126 J=IS,IS+4
                     IF(CB(I)(J:J).NE.' ')THEN
                        IF(INDEXN(CB(I)(J:J)).NE.1)GOTO 130
                     ENDIF
126               CONTINUE
*                  READ(CB(I)(IS:IS+4),'(I5)',ERR=130)K
*                 yes, where does name start?
                  IS = INDEXA(CB(I))
                  IF(IS.LE.0)THEN
                     WRITE (*,*)' Down link has no name ', BANKID, UPID
                     WRITE(*,*) CB(I)
                     IS=10
                  ENDIF
                  DOWNID=CB(I)(IS:IS+3)
                  DOWNID=DZE2US(DOWNID)
                  IF(FLAG.GE.2)THEN
                     CF=DOWNID//BANKID//'.html'
                     CALL CUTOL(CF)
                     NCCF=13
                  ELSE
                     NCCF=0
                  ENDIF
                  IF(NCCF.GT.0)THEN
                     NC=MAX(NC,IS+4)
                     WRITE(LUNOUT,'(A)')CB(I)(1:IS-1)//
     +                           '<a href="'//CF//'#'//
     +                           DOWNID//BANKID//'"><b>'//
     +                           CB(I)(IS:IS+3)//'</b></a>'//
     +                           CB(I)(IS+4:NC)
                  ELSE
*                    is there doc?
                     DO K=1,IPLIST
                        IF(CLIST(K).EQ.DOWNID//BANKID)THEN
                           WRITE(LUNOUT,'(A)')CB(I)(1:IS-1)//
     +                           '<a href="#'//
     +                           DOWNID//BANKID//'"><b>'//
     +                           CB(I)(IS:IS+3)//'</b></a>'//
     +                           CB(I)(IS+4:NC)
                            GOTO 125
                         ENDIF
                     ENDDO
*                    fallen through do loop, no doc there
                     WRITE(LUNOUT,'(A)')CB(I)(1:IS-1)//
     +                           '<a href="nodoc.html"><b>'//
     +                           CB(I)(IS:IS+3)//'</b></a>'//
     +                           CB(I)(IS+4:NC)
                     WRITE(*,'(A)')' No doc for: '
     +               //DOWNID//' '//BANKID//
     +               ' will make a reference to: "nodoc.html"'
 125                 CONTINUE
                  ENDIF
                  GOTO 140
 130              CONTINUE
                  NC=MAX(NC,1)
                  WRITE(LUNOUT,'(A)')CB(I)(1:NC)
 140              CONTINUE
               ELSE
                  NC=MAX(NC,1)
                  WRITE(LUNOUT,'(A)')CB(I)(1:NC)
               ENDIF
 145           CONTINUE
            ENDDO
            IF(EOF) GOTO 900
            IPBKID=0
            IP=0
            IPBKID=0
            IPUP=0
            IPLSTA=0
            IPLLAS=0
         ENDIF
         IP=IP+1
         CB(IP)=CL
         IPBKID=IP
         BANKID=CL(12:15)
         CALL CLTOU(BANKID)
      ELSE IF(CL(2:5).EQ.'Up  ')THEN
         IF(IPUP.NE.0)THEN
            WRITE(*,*)'More then 1 Up bank'
            GOTO 999
         ENDIF
         IP=IP+1
         CB(IP)=CL
         IPUP=IP
         UPID=CL(12:15)
         CALL CLTOU(UPID)
      ELSE IF(INDEX(CL,'Description of the links') .NE. 0)THEN
         IF(IPLSTA.NE.0)THEN
            WRITE(*,*)'More then 1 Link block start'
            GOTO 999
         ENDIF
         IP=IP+1
         CB(IP)=CL
         IPLSTA=IP+1
      ELSE IF(INDEX(CL,'Description of the data') .NE. 0)THEN
         IF(IPLLAS.NE.0)THEN
            WRITE(*,*)'More then 1 Link block end'
            GOTO 999
         ENDIF
         IP=IP+1
         CB(IP)=CL
         IPLLAS=IP-1
      ELSE
         IP=IP+1
         CB(IP)=CL
      ENDIF
      GOTO 110
 150  EOF=.TRUE.
*     DO THE LAST BANK
      CL(2:9)='Bank IDH'
      GOTO 115
 
900   CONTINUE
      WRITE(LUNOUT,'(A)')'</pre>'
      WRITE(LUNOUT,'(A)')'</body>'
      WRITE(LUNOUT,'(A)')'</html>'
      CLOSE(LUNIN)
      CLOSE(LUNOUT)
999   END
 
      CHARACTER*(*) FUNCTION DZE2US(CH)
      CHARACTER*(*) CH
      DO I=1,LEN(CH)
         IF(CH(I:I).EQ.' ')THEN
            DZE2US(I:I)='_'
         ELSE
            DZE2US(I:I)=CH(I:I)
         ENDIF
      ENDDO
      RETURN
      END
*CMZ :  1.30/00 11/02/96  22.08.12  by  Pavel Nevski
*CMZU:  1.00/01 21/01/96  20.40.48  by  Sasha Vanyashin
*CMZ :          09/12/95  16.20.44  by  Pavel Nevski
*-- Author :    M. Goossens DD/US
      SUBROUTINE DZDENT
************************************************************************
*.                                                                     *
*...DZDENT outputs the link,data and status bit information for a bank *
*.                                                                     *
*.  DZDENT is a daugther routine of DZDOCO                             *
*.  It prints the information about the link, status bit and data      *
*.  part of a given bank identifier                                    *
*.                                                                     *
*. BANKS  R : QBKD                                                     *
*. CALLS    : DZDLIN,INDXBC                                            *
*. CALLED   : DZDOCO                                                   *
*. COMMON   : DZDOCC,DZDTAP,MZCN                                       *
*.                                                                     *
*. AUTHOR   : M. Goossens DD/US                                        *
*. VERSION  : 2.03(47)  / 11 Oct 1987                                  *
*.                                                                     *
*. UPDATE   : 21 Mar 1988                                              *
*. BY       : O.Schaile                                                *
*.            Allow return of all described links if B-option is       *
*.            given (rather then only announced one)                   *
*.            Use link in link area (LBQBKD, LQBKD) for all references *
*.            Suppress printing at various places if B-option given    *
*.            3 Dec 88                                                 *
*.            simplify SGML, remove all SGML from this routine         *
*.            21-Nov-95 PN:  Z option supress data description dump    *
*.**********************************************************************
C     SAVE
 
*KEEP,BKWRP.
      PARAMETER (LNCARD=80 , LNCAR4=LNCARD/4)
      CHARACTER CARD*(LNCARD)
      COMMON /DZDINC/ CARD
 
      PARAMETER (IRLVMQ = 10)
 
C--     DESCRIPTION OF COMMON DZDTYP
C-      ============================
 
C--   Common DZDTYP contains the decoded information corresponding to
C--   one "CARD" image in variable CARD. Is contains also the back-up
C--   i.e. the old valus of the status flags to treat continuation info
 
C--     VARIABLE                        DESCRIPTION
C-      ========                        ===========
C       ISTATE        Code of state for last valid card ID
C       IDTAG         Code of character identification of card
C       ICONT         Card is continuation of previous one
C       ISLASH        Flag set when last character of CARD is '/'
C                     This character is used to generate a line feed
C                     for multi-line entries
C       IISLSH        Value of ISLASH for previous CARD
C       IREPLV        Repetition level
C       IREPLO        Old repetition level
C       ISCHLO        Old CHOICE section flag
C       IDEMTX        Hollerith code for text as previous entry (DZDINI)
C       IILFLF        Hollerith code for line feed (DZDINI)
C       INUM1         First number if number interpretation possible
C       IHNUM1        Vector containing the Hollerith representation
C                     of the first  number field (if non-numeric)
C                     INUM1 then contains -16* number of words used
C       INUM2         Second number if number interpretation possible
C       IHNUM2        Vector containing the Hollerith representation
C                     of the second number field (if non-numeric)
C                     INUM2 then contains -16* number of words used
C       NBNKS         Number of bank descriptors present
C       NHTAG         Number of characters in the tag field of the card
C                     This field can also correspond to a declared
C                     numeric field with a non-numeric entry
C       NWTAG         Number of 4-byte machine words needed for the tag
C       IHTAG         Vector containing the Hollerith representation
C                     of the tag field of the card
C       NHTXT         Number of characters in the text field of the card
C       NWTAG         Number of 4-byte machine words needed for the text
C       IHTAG         Vector containing the Hollerith representation
C                     of the text field of the card
 
      COMMON/DZDTYP/ISTATE,IDTAG,ICONT,ISLASH,IISLSH,IREPLV,IREPLO,
     X       IDEMTX,IILFLF,INUM1,IHNUM1(LNCAR4),INUM2,IHNUM2(LNCAR4),
     X       NBNKS,NHTAG,NWTAG,IHTAG(LNCAR4),NHTXT,NWTXT,IHTXT(LNCAR4)
 
      INTEGER        LDQBKD,LBQBKD,LDOC,LLTOP,LQBKD,LQBKD1,
     &               LUP,LORIG,LSAME,LNEW,LT,LD1,LD2,
     &               LUPD,LTD,LDD1,LDUMMY
 
      COMMON /DZDOCC/LDQBKD,LBQBKD,LDOC,LLTOP,LQBKD,LQBKD1,
     &               LUP,LORIG,LSAME,LNEW,LT,LD1,LD2,
     &               LUPD,LTD,LDD1,LDUMMY
 
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
              DIMENSION  LQLUP(99), LQLORG(98),IQWIDN(97),IQWIDH(96)
     +,                  IQWNL(95), IQWNS(94), IQWND(93)
            EQUIVALENCE (LQLUP(8),  LQLORG(7), IQWIDN(6), IQWIDH(5)
     +,                  IQWNL(4),  IQWNS(3),  IQWND(2), IQ(1))
      COMMON /MZCN/  IQLN,IQLS,IQNIO,IQID,IQNL,IQNS,IQND, IQNX,IQFOUL
*KEEP,TAPES.
      COMMON /DZDTAP/ LUNIN,LUNOUT,LUNUSR
*KEEP,ZBCDK.
      PARAMETER (MPOSAQ= 1 ,MPOSBQ= 2 ,MPOSCQ= 3 ,MPOSDQ= 4 ,MPOSEQ= 5
     X          ,MPOSFQ= 6 ,MPOSGQ= 7 ,MPOSHQ= 8 ,MPOSIQ= 9 ,MPOSJQ=10
     X          ,MPOSKQ=11, MPOSLQ=12 ,MPOSMQ=13 ,MPOSNQ=14 ,MPOSOQ=15
     X          ,MPOSPQ=16, MPOSQQ=17 ,MPOSRQ=18 ,MPOSSQ=19 ,MPOSTQ=20
     X          ,MPOSUQ=21, MPOSVQ=22 ,MPOSWQ=23 ,MPOSXQ=24 ,MPOSYQ=25
     X          ,MPOSZQ=26                                            )
*KEEP,LINOUT.
C--     Parameters and commons defining the output line
 
C--     Output vector
      PARAMETER (NOUTQ=80)
      CHARACTER COUT*(NOUTQ)
C--     Definition of fields on output line
      PARAMETER (IOTAGQ=12,IOENTQ=21,NOENTQ=NOUTQ-IOENTQ+1)
      PARAMETER (INDENQ=2,NENTIQ=10)
 
      COMMON/CDLINE/COUT
      COMMON/IDLINE/IEWORK,IFLOPT(26),INLINE,INSERT,NOUTF,NWHOLL
C--     Description of the variables in common CDLINE and IDLINE
C     Identifier                     Description
C     ==========                     ===========
C     COUT         Character variable representing the output line
C     IEWORK       Pointer to the last position occupied in the work
C                  variable CWORK (Subr. DZDLIN)
C     IFLOPT (26)  Integer array with value non-zero for each option
C                  set (used by DZDOCO and DZDOCS for transmitting the
C                  options to its daughter routines)
C     INLINE       Offset of the start of the information in COUT
C     INSERT       Pointer to the current text field being treated in
C                  the ZEBRA bank
C     NOUTF        Number of columns available on the output line
C                  to contain the text information
C     NWHOLL       Number of words in the ZEBRA bank containing the
C                  text information and remaining to be treated
*KEND.
      LOGICAL BTEST, LTHERE, RTHERE,BTHERE,DTHERE
*--     General information
      CHARACTER CFORM*4
*KEEP,DOCPARQ.
C
C----           PARAMETER definitions for DZDOC
C
C--     Offset of DOWN bank for text buffers in master DOC babk
      PARAMETER (MDOCDQ = -1)
C--     Offset of number of words used
      PARAMETER (MDCENQ = 1 )
 
C----   Description of the documentation bank
C       =====================================
 
C--     Bank header part
C       ----------------
C--     Number of words in the header
      PARAMETER (NBHEAQ = 20)
C--     Offset of encoded bank IDH
      PARAMETER (MBIDHQ = 1)
C--     Offset of number of words in use
      PARAMETER (MBUSEQ = MBIDHQ+1)
C--     Offset of number of words in the header
      PARAMETER (MBHEAQ = MBUSEQ+1)
C--     Offset of total number of links
      PARAMETER (MBNNDQ = MBHEAQ+1)
C--     Offset of number of structural links
      PARAMETER (MBNNLQ = MBNNDQ+1)
C--     Offset of number of data words
      PARAMETER (MBNNSQ = MBNNLQ+1)
 
C--     Offset of number of words with general information
      PARAMETER (MBGENQ = 11)
C--     Offset of number of words describing the links
      PARAMETER (MBLINQ = MBGENQ+1)
C--     Offset of number of words describing the ref links
      PARAMETER (MBRLIQ = MBLINQ+1)
C--     Offset of number of words describing the status bits
      PARAMETER (MBBITQ = MBRLIQ+1)
C--     Offset of number of words describing the data words
      PARAMETER (MBDATQ = MBBITQ+1)
 
C---             Bank Description pointers and flags
C---             ===================================
 
C--              Normal entry
C                ------------
C--     Number of words in bank description pointers and flag section
      PARAMETER (NBDSCQ = 4)
C--     Offset of pattern word inside section
      PARAMETER (MBPATQ = 1)
C--     Offset of the two index words inside the section
      PARAMETER (MBIX1Q = MBPATQ+1  , MBIX2Q = MBIX1Q+1)
 
C--              End of sequence
C                ---------------
C--     Number of words in bank description for end of sequence entry
      PARAMETER (NBEOSQ = 2)
 
C--     Descriptor for normal entry
C       ---------------------------
C--     Start bit and number of bits for tag information
      PARAMETER (ICHTGQ = 0 , NCHTGQ = 2)
C--     Multiple choice bit
      PARAMETER (ICHBTQ = 2)
C--     Start bit and number of bits for identifier information
      PARAMETER (ICHIDQ = 10 , NCHIDQ = 5)
C--     Start bit and number of bits for REP. level information
      PARAMETER (IRPLVQ = ICHIDQ+NCHIDQ , NRPLVQ = 4)
C--     Bit for end-of-sequence flag
      PARAMETER (IBEOSQ = IRPLVQ+NRPLVQ)
 
C--     Descriptor for CHOICE tag
C       -------------------------
 
C--     Number of words for CHOICE flag descriptor
      PARAMETER (NCDSCQ = 4)
C--     Offset of pattern word inside section
      PARAMETER (MCPATQ = 1)
 
C--     Offset of the word offset in the bank and its contents
      PARAMETER (MCWOFQ = MCPATQ+1  , MCWCOQ = MCWOFQ+1)
 
C--     Bit flags choice by number (dynamic sector)
      PARAMETER (ICNUMQ = 0 )
C--     Bit flags choice by format (self describing sector)
      PARAMETER (ICFORQ = ICNUMQ + 1)
C--     Bit flags choice by contents
      PARAMETER (ICCONQ = ICFORQ + 1)
C--     Offset of self description information and width
      PARAMETER (ICSELQ = 10, NCSELQ=4)
C--     Offset of selection byte fields in word and width
      PARAMETER (ICBY1Q = ICSELQ+NCSELQ, NCBYTQ=8)
      PARAMETER (ICBY2Q = ICBY1Q+NCBYTQ)
 
*KEEP,DZDOCOBK.
C--     Offset for NL, NS and ND for bank being described
      PARAMETER (MONLQ = 1 , MONSQ = MONLQ+1 , MONDQ = MONSQ+1)
C--     Offset for Hollerith identifier of bank
      PARAMETER (MOIDHQ = 7)
C--     Offset of ORigin, UP and NeXt links
      PARAMETER (MOORQ = 8 , MOUPQ = MOORQ+1 , MONXQ = MOUPQ+1)
C--     Offset for 0th address of links of bank
      PARAMETER (MOLK0Q = MONXQ)
C--     Offset in IQUEST of return address for link description bank
      PARAMETER (MOQUEQ = 11)
*KEEP,BKNUPARQ.
 
C--               Indefinite (* given in number field)
      PARAMETER ( INUINQ = -1)
C--               Tag (non-numeric description given in number field)
      PARAMETER ( INUTGQ = -2)
 
*KEEP,BKFOPARQ.
 
C--     Definition of the bank IO characteristic types (MZBOOK/MZLIFT)
 
C--               Undefined --> bank cannot be transported
      PARAMETER ( IFOUNQ = 0)
C--               Bit pattern
      PARAMETER ( IFOBIQ = 1)
C--               Integer
      PARAMETER ( IFOINQ = 2)
C--               Floating point
      PARAMETER ( IFOFLQ = 3)
C--               Double precision
      PARAMETER ( IFODOQ = 4)
C--               Hollerith
      PARAMETER ( IFOHOQ = 5)
C--               Self describing sector
      PARAMETER ( IFOSEQ = 7)
C--               Retrieve by name
      PARAMETER ( IFONAQ = 9)
C--               Copy from linear chain
      PARAMETER ( IFOLIQ = 11)
C--               Multiplication factor for self-describing sector
      PARAMETER ( JFOSEQ = 16)
 
*KEEP,BKSTPARQ.
 
C--               General information
      PARAMETER ( ISGENQ = 1)
C--              Link description
      PARAMETER ( ISLINQ = ISGENQ+1)
C--              ref Link description
      PARAMETER ( ISRLIQ = ISLINQ+1)
C--               Status bit description
      PARAMETER ( ISBITQ = ISRLIQ+1)
C--               Data description
      PARAMETER ( ISDATQ = ISBITQ+1)
C--               Choice section
      PARAMETER ( ISCHOQ = 16)
C--               Repetition section
      PARAMETER ( ISREPQ = 32)
 
*KEEP,BKTGPARQ.
 
 
C--     Description of the action flags
 
C-      Code for NO  entry
      PARAMETER (IBKANQ = -1)
C-      Code for YES entry
      PARAMETER (IBKAYQ = -2)
C-      Flag for numeric tag field
      PARAMETER (IBKAMQ = -3)
C-      Flag for special decoding(CHOICE tag)
      PARAMETER (IBKASQ = -9)
 
C--     Description of the action fields
 
C-      Offset of state information
      PARAMETER (MBKASQ = 1)
C-      Offset of tag flag (1,2 words , numeric)
      PARAMETER (MBKAGQ = MBKASQ+1)
C-      Offset of repetition flag
      PARAMETER (MBKARQ = MBKAGQ+1)
C-      Offset of choice flag
      PARAMETER (MBKAHQ = MBKARQ+1)
C-      Number of action fields
      PARAMETER (NBKACQ = MBKAHQ)
 
C----   Identifiers of various card tags
 
C--               AUthor
      PARAMETER (ITGAUQ = 1)
C--               BIt (status)
      PARAMETER (ITGBIQ = ITGAUQ+1)
C--               CHoice section
      PARAMETER (ITGCHQ = ITGBIQ+1)
C--               DAta section
      PARAMETER (ITGDAQ = ITGCHQ+1)
C--               Division
      PARAMETER (ITGDVQ = ITGDAQ+1)
C--               LInk section
      PARAMETER (ITGLIQ = ITGDVQ+1)
C--               RLink section
      PARAMETER (ITGRLQ = ITGLIQ+1)
C--               Number of data words (ND)
      PARAMETER (ITGNDQ = ITGRLQ+1)
C--               Total Number of Links (NL)
      PARAMETER (ITGNLQ = ITGNDQ+1)
C--               Number of Structural links (NS)
      PARAMETER (ITGNSQ = ITGNLQ+1)
C--               NeXt link
      PARAMETER (ITGNXQ = ITGNSQ+1)
C--               ORigin link
      PARAMETER (ITGORQ = ITGNXQ+1)
C--               REpetition section
      PARAMETER (ITGREQ = ITGORQ+1)
C--               STore
      PARAMETER (ITGSTQ = ITGREQ+1)
C--               UP link
      PARAMETER (ITGUPQ = ITGSTQ+1)
C--               VErsion
      PARAMETER (ITGVEQ = ITGUPQ+1)
C--               Entry
      PARAMETER (ITGENQ = ITGVEQ+1)
C--               NZERO words to preset to zero
      PARAMETER (ITGNZQ = ITGENQ+1)
C--               IO characteristics
      PARAMETER (ITGIOQ = ITGNZQ+1)
C--               Numerical identifier
      PARAMETER (ITGNIQ = ITGIOQ+1)
C--               IDem qualifier
      PARAMETER (ITGIDQ = ITGNIQ+1)
C--               Tag length for entry
      PARAMETER (NWTENQ = 2)
 
*KEEP,BKTGDATQ.
      CHARACTER CBKTAC(ITGIDQ)*2
      DIMENSION IBKTAC(NBKACQ,ITGIDQ)
 
C--               AUthor
      DATA CBKTAC(ITGAUQ)        / 'AU'   /
      DATA IBKTAC(MBKASQ,ITGAUQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGAUQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGAUQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGAUQ) / IBKANQ /
C--               BIt (status)
      DATA CBKTAC(ITGBIQ)        / 'BI'   /
      DATA IBKTAC(MBKASQ,ITGBIQ) / ISBITQ /
      DATA IBKTAC(MBKAGQ,ITGBIQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGBIQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGBIQ) / IBKAYQ /
C--               CHoice section
      DATA CBKTAC(ITGCHQ)        / 'CH'   /
      DATA IBKTAC(MBKASQ,ITGCHQ) / ISCHOQ /
      DATA IBKTAC(MBKAGQ,ITGCHQ) / IBKASQ /
      DATA IBKTAC(MBKARQ,ITGCHQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGCHQ) / IBKANQ /
C--               DAta section
      DATA CBKTAC(ITGDAQ)        / 'DA'   /
      DATA IBKTAC(MBKASQ,ITGDAQ) / ISDATQ /
      DATA IBKTAC(MBKAGQ,ITGDAQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGDAQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGDAQ) / IBKAYQ /
C--               Division
      DATA CBKTAC(ITGDVQ)        / 'DV'   /
      DATA IBKTAC(MBKASQ,ITGDVQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGDVQ) /      2 /
      DATA IBKTAC(MBKARQ,ITGDVQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGDVQ) / IBKAYQ /
C--               LInk section
      DATA CBKTAC(ITGLIQ)        / 'LI'   /
      DATA IBKTAC(MBKASQ,ITGLIQ) / ISLINQ /
      DATA IBKTAC(MBKAGQ,ITGLIQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGLIQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGLIQ) / IBKAYQ /
C--               RLink section
      DATA CBKTAC(ITGRLQ)        / 'RL'   /
      DATA IBKTAC(MBKASQ,ITGRLQ) / ISRLIQ /
      DATA IBKTAC(MBKAGQ,ITGRLQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGRLQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGRLQ) / IBKAYQ /
C--               Numerical Identifier
      DATA CBKTAC(ITGNIQ)        / 'NI'   /
      DATA IBKTAC(MBKASQ,ITGNIQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNIQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNIQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNIQ) / IBKANQ /
C--               Number of Data words
      DATA CBKTAC(ITGNDQ)        / 'ND'   /
      DATA IBKTAC(MBKASQ,ITGNDQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNDQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNDQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNDQ) / IBKANQ /
C--               Total Number of Links
      DATA CBKTAC(ITGNLQ)        / 'NL'   /
      DATA IBKTAC(MBKASQ,ITGNLQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNLQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNLQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNLQ) / IBKANQ /
C--               Number of Structural links
      DATA CBKTAC(ITGNSQ)        / 'NS'   /
      DATA IBKTAC(MBKASQ,ITGNSQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNSQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNSQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNSQ) / IBKANQ /
C--               NeXt link
      DATA CBKTAC(ITGNXQ)        / 'NX'   /
      DATA IBKTAC(MBKASQ,ITGNXQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNXQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGNXQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNXQ) / IBKAYQ /
C--               ORigin link
      DATA CBKTAC(ITGORQ)        / 'OR'   /
      DATA IBKTAC(MBKASQ,ITGORQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGORQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGORQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGORQ) / IBKAYQ /
C--               REpetition section
      DATA CBKTAC(ITGREQ)        / 'RE'   /
      DATA IBKTAC(MBKASQ,ITGREQ) / ISREPQ /
      DATA IBKTAC(MBKAGQ,ITGREQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGREQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGREQ) / IBKAYQ /
C--               STore
      DATA CBKTAC(ITGSTQ)        / 'ST'   /
      DATA IBKTAC(MBKASQ,ITGSTQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGSTQ) /      2 /
      DATA IBKTAC(MBKARQ,ITGSTQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGSTQ) / IBKAYQ /
C--               UP link
      DATA CBKTAC(ITGUPQ)        / 'UP'   /
      DATA IBKTAC(MBKASQ,ITGUPQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGUPQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGUPQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGUPQ) / IBKAYQ /
C--               VErsion
      DATA CBKTAC(ITGVEQ)        / 'VE'   /
      DATA IBKTAC(MBKASQ,ITGVEQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGVEQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGVEQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGVEQ) / IBKANQ /
C--               NZERO number of data words preset to 0
      DATA CBKTAC(ITGNZQ)        / 'NZ'   /
      DATA IBKTAC(MBKASQ,ITGNZQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNZQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNZQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNZQ) / IBKANQ /
C--              IO characteristics
      DATA CBKTAC(ITGIOQ)        / 'IO'   /
      DATA IBKTAC(MBKASQ,ITGIOQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGIOQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGIOQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGIOQ) / IBKANQ /
C--               IDEM
      DATA CBKTAC(ITGIDQ)        / 'ID'   /
      DATA IBKTAC(MBKASQ,ITGIDQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGIDQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGIDQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGIDQ) / IBKAYQ /
 
*KEND.
 
      LTHERE=.FALSE.
      RTHERE=.FALSE.
      BTHERE=.FALSE.
      DTHERE=.FALSE.
   10 CONTINUE
 
*--     Loop over the link, status bit and data information
 
      II     = NBHEAQ
      IF (IFLOPT(MPOSBQ).NE.0) THEN
*--         Link description bank option
*--           Number of links announced
          NLLINK = IQ(KQSP+LBQBKD+MONLQ)
          NSLINK = IQ(KQSP+LBQBKD+MONSQ)
          NLLL = MAX(NLLINK,NSLINK)
*--           Get the number ow words required in the bank
          NLPUSH = NLLL + MOLK0Q - IQWND(KQSP+LBQBKD)
*--           If number of link > 0 -- Push bank, otherwise noopt
 
*--- OTTO    allow return of non announced links
 
*--          CALL DZVERI('Before MZPUSH',0,'CFLSU')
         IF (NLLL.GE.0) CALL MZPUSH(0,LBQBKD,0,NLPUSH,'I')
*--      PRINT '('' NLLINK NLPUSH '',2I5)',NLLINK,NLPUSH
*--      CALL DZSHOW('After PUSH',0,L,' ',0,0,0,0)
*--           Local working variables
*--            0th address and max. nb. entries in link description bank
*          MBLK0  = KQSP + LBQBKD + MOLK0Q
          NBLMAX = IQWND(KQSP+LBQBKD) - MOLK0Q
 
          IHLPUT = 0
 
      ENDIF
      ITAG   = IOTAGQ
      IF (IFLOPT(MPOSIQ).NE.0) THEN
         IREP   = 0
      ELSE
         IREP   = 5
      ENDIF
 
      DO 120 I=MBLINQ,MBDATQ
          IF (IFLOPT(MPOSBQ).NE.0.AND.I.NE.MBLINQ)         GO TO 120
          II     = II + IQ(KQSP+LQBKD+I-1)
          INSERT = II + 1
          IREPLO = 0
          INDENT = 0
          IF (I.EQ.MBLINQ .AND. IFLOPT(MPOSBQ).EQ.0) THEN
              IF (IQ(KQSP+LQBKD+I).GT.0) THEN
                 IF (IFLOPT(MPOSIQ).NE.0) THEN
                     WRITE(LUNUSR,'(''*B.LINK'')')
                     LTHERE=.TRUE.
                 ELSE
                     WRITE(LUNUSR,10102) 'links'
10102                format(T15,' ---------- Description of the ',a,
     +                          ' ----------')
                 ENDIF
             ELSE
C--              No link description
                                                           GO TO 120
             ENDIF
 
          ELSEIF (I.EQ.MBRLIQ) THEN
              IF (IQ(KQSP+LQBKD+I).GT.0) THEN
                 IF (IFLOPT(MPOSIQ).NE.0) THEN
                     RTHERE=.TRUE.
                     IF(LTHERE)THEN
                        WRITE(LUNUSR,'(''*B/LINK'')')
                        LTHERE=.FALSE.
                     ENDIF
                     WRITE(LUNUSR,'(''*B.RLINK'')')
                 ELSE
                     WRITE(LUNUSR,10102) 'Reference links'
                 ENDIF
             ELSE
C--              No ref link description
                                                           GO TO 120
             ENDIF
 
          ELSEIF (I.EQ.MBBITQ) THEN
            IF (IQ(KQSP+LQBKD+I).GT.0) THEN
                 IF (IFLOPT(MPOSIQ).NE.0) THEN
                     WRITE(LUNUSR,'(''*B.BI'')')
                     BTHERE=.TRUE.
                     IF(LTHERE)THEN
                        WRITE(LUNUSR,'(''*B/LINK'')')
                        LTHERE=.FALSE.
                     ENDIF
                     IF(RTHERE)THEN
                        WRITE(LUNUSR,'(''*B/RLINK'')')
                        RTHERE=.FALSE.
                     ENDIF
                 ELSE
                     WRITE(LUNUSR,10102) 'status bits'
                 ENDIF
            ELSE
C--               No status bit description
                                                           GO TO 120
            ENDIF
          ELSEIF (I.EQ.MBDATQ) THEN
            IF (IQ(KQSP+LQBKD+I).GT.0 .AND. IFLOPT(MPOSZQ).EQ.0) THEN
                 IF (IFLOPT(MPOSIQ).NE.0) THEN
                     WRITE(LUNUSR,'(''*B.DATA'')')
                     DTHERE=.TRUE.
                     IF(LTHERE)THEN
                        WRITE(LUNUSR,'(''*B/LINK'')')
                        LTHERE=.FALSE.
                     ENDIF
                     IF(RTHERE)THEN
                        WRITE(LUNUSR,'(''*B/RLINK'')')
                        RTHERE=.FALSE.
                     ENDIF
                     IF(BTHERE)THEN
                        WRITE(LUNUSR,'(''*B/BI'')')
                        BTHERE=.FALSE.
                     ENDIF
                 ELSE
                     WRITE(LUNUSR,10102) 'data words'
                 ENDIF
            ELSE
C--            No data description
                                                           GO TO 120
            ENDIF
          ENDIF
   20     IF (INSERT.GT.II+IQ(KQSP+LQBKD+I))               GO TO 100
          JTAG   = IQ(KQSP+LQBKD+INSERT+MBPATQ)
          NWTAG  = IBITS(JTAG,ICHTGQ,NCHTGQ)
          ICHOIC = IBITS(JTAG,ICHBTQ,1)
          IDTAG  = IBITS(JTAG,ICHIDQ,NCHIDQ)
          IREPLV = IBITS(JTAG,IRPLVQ,NRPLVQ)
          IF (IREPLO.LT.IREPLV) THEN
*----           Repetition field descriptor
*--                  Start of higher level
               IF (IFLOPT(MPOSIQ).NE.0) THEN
                  COUT   = '*B.REP '
                  INDENT = 8
               ELSE
                  INDENT = IREPLO*INDENQ
                  COUT   = ' '
                  COUT(INDENT+2:)='--REP level='//
     +                         CHAR(ICHAR('0')+IREPLV)
               ENDIF
 
*1810               IF    (IREPLO.EQ.0)THEN
*1810                  COUT(INDENT+2:)='-- Do I = 1,'
*1810               ELSE IF(IREPLO.EQ.1)THEN
*1810                  COUT(INDENT+2:)='-- Do K = 1,'
*1810               ELSE
*1810                  COUT(INDENT+2:)='-- Do J = 1,'
*1810               ENDIF
              IREPLO = IREPLV
              INUM1  = IQ(KQSP+LQBKD+INSERT+MBIX1Q)
              IF (INUM1.GT.0) THEN
*--               Given as real number
                  WRITE(COUT(ITAG+IREP+INDENT:),'(I8)') INUM1
              ELSEIF (INUM1.EQ.INUINQ) THEN
*--                 Indefinite (variable) number
                  COUT(ITAG+IREP+INDENT:) = 'infinite'
              ELSE
*--                 Information is in form of Hollerith text
                  NWTAG = -INUM1/JFOSEQ
              ENDIF
*--             Skip I self-describing sector
              INSERT = INSERT + NBDSCQ
*--             If not Hollerith self-describing sector -- SKIP
              IF (MOD(IQ(KQSP+LQBKD+INSERT),JFOSEQ).NE.IFOHOQ) THEN
                  IF (NWTAG.GT.0) THEN
*--                     Inconsistency: Tag announced and non present
                      WRITE(LUNUSR,10103)
10103                 format('0?? DZDENT: Inconsistency: ',
     +                'Tag information announced and non present')
                                                           GO TO 130
                  ENDIF
                  IF(IFLOPT(MPOSBQ).EQ.0)THEN
*                     IF (INUM1.NE.0)
                      WRITE(LUNUSR,'(A)') COUT
                  ENDIF
                                                           GO TO 20
              ENDIF
*--             Total number of Hollerith words
              NWHOLL = IQ(KQSP+LQBKD+INSERT)/JFOSEQ
              INSERT = INSERT + 1
*--             When there is tag info
              IF (NWTAG.GT.0) THEN
*--                Numbers given as Hollerith text
                 INLINE=ITAG+IREP+INDENT
                 CALL UHTOC(IQ(KQSP+LQBKD+INSERT),4,
     +                      COUT(INLINE:),NWTAG*4)
                 INSERT = INSERT + NWTAG
                 NWHOLL = NWHOLL - NWTAG
              ENDIF
*--             Is there some text left
              IF (NWHOLL.GT.0) THEN
*--                 More text in the buffer
                  INLINE = INLINE+NWTAG*4
*                  INLINE = IOENTQ + IREP + INDENT
                  IEWORK = 0
                  NOUTF  = NOUTQ - INLINE + 1
                  CALL DZDLIN
              ELSE
                  IF(IFLOPT(MPOSBQ).EQ.0)WRITE(LUNUSR,'(A)') COUT
              ENDIF
 
*------------------ End of loop over Hollerith text
              INDENT = IREPLV*INDENQ
          ELSEIF (IREPLO.GT.IREPLV) THEN
*----           End of repetition field
              IF (IFLOPT(MPOSBQ) .EQ. 0)THEN
*--              Level goes down --> close present level
                  INDENT = IREPLV*INDENQ
                  IF (IFLOPT(MPOSIQ).NE.0) THEN
                     COUT   = '*B/REP '
                  ELSE
                     COUT   = ' '
                     COUT(INDENT+2:)='--REP level='//
     +                       CHAR(ICHAR('0')+IREPLO)//' -- End --'
*1810               COUT(INDENT+2:)='-- End Do -----------------------'
                 ENDIF
                 WRITE (LUNUSR,'(A)') COUT
              ENDIF
              IREPLO = IREPLV
*--             Cross check on EOFS flag
              IF (.NOT.BTEST(JTAG,IBEOSQ)) THEN
                   WRITE (LUNUSR,10101)
*                  WRITE (LUNOUT,10101)
10101              format('0??? DZDENT- Illegal repetition level',
     +                    ' counting (only 1 item allowed')
                                                          GO TO 130
              ELSE
*--                 Skip I self-describing sector
                  INSERT = INSERT + NBEOSQ
              ENDIF
          ELSE
*----           Entry documentation
              INUM1  = IQ(KQSP+LQBKD+INSERT+MBIX1Q)
              INUM2  = IQ(KQSP+LQBKD+INSERT+MBIX2Q)
              IF (INUM1.GT.0) THEN
*--               Get number of characters in INUM1
                  ICH    = INUM1
                  DO 30  IW1=1,8
                      ICH = ICH/10
                      IF (ICH.EQ.0)                        GO TO 40
   30             CONTINUE
                  IW1 = 8
   40         ENDIF
              IF (INUM2.GT.0) THEN
*--               Get number of characters in INUM2
                  ICH    = INUM2
                  DO 50  IW2=1,8
                      ICH = ICH/10
                      IF (ICH.EQ.0)                        GO TO 60
   50             CONTINUE
                  IW2 = 8
   60         ENDIF
*--             Indent for each new repetition level
              COUT   = ' '
              IF (IFLOPT(MPOSIQ).NE.0) THEN
                 COUT='*B.'
                 INLINE=3
                 IW1=IW1-1
              ELSE
                 COUT   = ' '
                 INLINE = INDENT*INDENQ
              ENDIF
              IF (INUM2.EQ.0) THEN
*--                 Case of only one number given
                  IF (INUM1.GE.0) THEN
*--                   Given as real number
                      CFORM  = '(I'//CHAR(ICHAR('1')+IW1)//')'
                      WRITE(COUT(INLINE+1:),CFORM) INUM1
                      INLINE = INLINE + IW1 + 1
                  ELSEIF (INUM1.EQ.INUINQ) THEN
*--                     Indefinite (variable) number
                      INLINE = INLINE + 1
                      COUT(INLINE:) = '*'
                  ENDIF
              ELSE
*--                 Case of two numbers
                  IF (INUM1.GE.0) THEN
*--                   Given as real number
                      CFORM  = '(I'//CHAR(ICHAR('1')+IW1)//')'
                      WRITE(COUT(INLINE+1:),CFORM) INUM1
                      INLINE = INLINE + IW1 + 1
                  ELSEIF (INUM1.EQ.INUINQ) THEN
*--                     Indefinite (variable) number
                      INLINE = INLINE + 1
                      COUT(INLINE:) = '*'
                  ENDIF
                  IF (INUM2.GE.0) THEN
*--                   Given as real number
                      INLINE = INLINE + 1
                      COUT(INLINE:INLINE) = '-'
                      CFORM  = '(I'//CHAR(ICHAR('0')+IW2)//')'
                      WRITE(COUT(INLINE+1:),CFORM) INUM2
                      INLINE = INLINE + IW2
                  ELSEIF (INUM2.EQ.INUINQ) THEN
*--                     Indefinite (variable) number
                      COUT(INLINE+1:INLINE+2) = '-*'
                      INLINE = INLINE + 2
                  ENDIF
              ENDIF
*--             Skip I self-describing sector
              INSERT = INSERT + NBDSCQ
*--             If not Hollerith self-describing sector -- SKIP
              IF (MOD(IQ(KQSP+LQBKD+INSERT),JFOSEQ).NE.IFOHOQ) THEN
*                  WRITE(LUNOUT,'(''0?? DZDENT -- Incomplete data'')')
                  WRITE(LUNUSR,'(''0?? DZDENT -- Incomplete data'')')
                  WRITE(LUNUSR,'(A,A4)')' Previous error occured in',
     +                      IQ(KQSP+LBQBKD+MOIDHQ)
                                                           GO TO 20
              ENDIF
*--             Total number of Hollerith words
              NWHOLL = IQ(KQSP+LQBKD+INSERT)/JFOSEQ
              IITAG  = INSERT + 1
              INSERT = IITAG
              IF (INUM2.EQ.0) THEN
*--                 Case of only one number given
                  IF (INUM1.LE.-JFOSEQ) THEN
*--                     Information is in form of Hollerith text
                      NWN1   = -INUM1/JFOSEQ
                      CALL UHTOC(IQ(KQSP+LQBKD+INSERT+NWTAG),4,
     +                           COUT(INLINE+1:),NWN1*4)
                      INLINE = INDXBC(COUT(:INLINE+NWN1*4),' ')
                      INSERT = INSERT + NWN1
                      NWHOLL = NWHOLL - NWN1
                  ENDIF
              ELSE
*--                 Case of two numbers
                  IF (INUM1.LE.-JFOSEQ) THEN
*--                     Information is in form of Hollerith text
                      NWN1   = -INUM1/JFOSEQ
                      CALL UHTOC(IQ(KQSP+LQBKD+INSERT+NWTAG),4,
     +                           COUT(INLINE+1:),NWN1*4)
                      INLINE = INDXBC(COUT(:INLINE+NWN1*4),' ')
                      INSERT = INSERT + NWN1
                      NWHOLL = NWHOLL - NWN1
                  ENDIF
                  IF (INUM2.LE.-JFOSEQ) THEN
*--                     Information is in form of Hollerith text
                      INLINE = INLINE + 1
                      COUT(INLINE:INLINE) = '-'
                      NWN2   = -INUM2/JFOSEQ
                      CALL UHTOC(IQ(KQSP+LQBKD+INSERT+NWTAG),4,
     +                           COUT(INLINE+1:),NWN2*4)
                      INLINE = INDXBC(COUT(:INLINE+NWN2*4),' ')
                      INSERT = INSERT + NWN2
                      NWHOLL = NWHOLL - NWN2
                  ENDIF
              ENDIF
              INLINE = INDENT + ITAG
 
*--             Special case for the link descriptor bank
 
              IF (IFLOPT(MPOSBQ).EQ.0)                     GO TO 90
*--                Update pointer in input bank and test tag information
                  INSERT = INSERT + NWHOLL
                  LENBKD = IQWND(LBQBKD+KQSP)
                  IF (NWTAG.LE.0)                          GO TO 20
*--                Now cases for link numbers
                  IF (INUM1.LE.0)                          GO TO 20
                  IF (INUM2.LT.INUINQ) THEN
                                                           GO TO 20
                  ELSEIF (INUM2.EQ.INUINQ) THEN
*--                     Undefined --> Fill bank up to end and exit
                      DO 70  IINUM=INUM1,NBLMAX
   70                 IQ(KQSP + LBQBKD + MOLK0Q+IINUM) =
     +                                      IQ(KQSP+LQBKD+IITAG)
                                                           GO TO 120
                  ELSEIF (INUM2.EQ.0) THEN
*--                     Only one number given - Inside allowed offsets?
                      IF(INUM1+MOLK0Q .GT. LENBKD)THEN
                          NLPUSH=INUM1+MOLK0Q - LENBKD
                          CALL MZPUSH(0,LBQBKD,0,NLPUSH,'I')
                      ENDIF
                      IQ(KQSP + LBQBKD + MOLK0Q+INUM1)=
     +                                      IQ(KQSP+LQBKD+IITAG)
                      IF(INUM1 .GT. IHLPUT)IHLPUT = INUM1
                  ELSE
*--                     Range of numbers given - Inside allowed offsets?
                      DO 80  IINUM=MIN(INUM1,NBLMAX),MIN(INUM2,NBLMAX)
   80                 IQ(KQSP + LBQBKD + MOLK0Q+IINUM) =
     +                                     IQ(KQSP+LQBKD+IITAG)
                  ENDIF
                                                           GO TO 20
   90         CONTINUE
*--             When there is tag info  <===========
              IF (NWTAG.GT.0) THEN
*--                 Numbers given as Hollerith text
                  CALL UHTOC(IQ(KQSP+LQBKD+IITAG),4,
     +                       COUT(INLINE:),MIN(NENTIQ-2,NWTAG*4))
*1810
                  IF(INDEX(COUT,'L:').NE.0)THEN
                     IF (IFLOPT(MPOSIQ).NE.0) THEN
                        COUT(1:4)  = '*B.*'
                     ELSE
                        WRITE(LUNUSR,'(A)')' '
                        COUT(1:INDEX(COUT,'L:')-1)='--Label:'
                     ENDIF
                  ENDIF
                  INSERT = INSERT + NWTAG
*--                 Is there some text left
                  NWHOLL = NWHOLL - NWTAG
              ENDIF
*--             Remaining text
              IF (NWHOLL.GT.0) THEN
*--                 Copy text according to output type desired
                  INLINE = IOENTQ + INDENT
                  IF (NWHOLL.EQ.1.AND.IQ(KQSP+LQBKD+INSERT).EQ.IDEMTX)
     +                                                           THEN
*--                     Repetition of the previous line
                      COUT(INLINE:) = '  idem'
                      INSERT = INSERT + 1
                      NWHOLL = 0
                      IF(IFLOPT(MPOSBQ).EQ.0)WRITE(LUNUSR,'(A)') COUT
                  ELSE
                      IEWORK = 0
                      NOUTF  = NOUTQ  - INLINE + 1
*--                     General case with text
                      CALL DZDLIN
                  ENDIF
              ELSE
*--             For tags only
                  IF(IFLOPT(MPOSBQ).EQ.0)WRITE(LUNUSR,'(A)') COUT
*------------------ End of field with text information
              ENDIF
*--------------- Multiple choice present ?
              IF (ICHOIC.NE.0) THEN
*--                 Still more text to read?
                  IF (MOD(IQ(KQSP+LQBKD+INSERT),JFOSEQ).EQ.IFOHOQ) THEN
*--                   Indent for each new repetition level
                      COUT   = ' '
                      INLINE = INDENT + ITAG
*--                     Total number of Hollerith words
                      NWHOLL = IQ(KQSP+LQBKD+INSERT)/JFOSEQ
                      IITAG  = INSERT + 1
                      INSERT = IITAG
*--  ==============     Alternative choice for entry      ==============
                                                           GO TO 90
*--          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                  ENDIF
              ENDIF
*-------------- End of entry (repetition or information tag) [below 110]
          ENDIF
                                                           GO TO 20
*--         Close the description level if needed
  100     CONTINUE
          IF(IFLOPT(MPOSBQ) .EQ. 0)THEN
              DO 110 IR=IREPLV,1,-1
                  IF (IFLOPT(MPOSIQ).NE.0) THEN
                     COUT   = '*B/REP '
                     INDENT = 10
                  ELSE
                     INDENT = (IR-1)*INDENQ
                     COUT   = ' '
                     COUT(INDENT+2:)='--REP level='//
     +                            CHAR(ICHAR('0')+IR)//' -- End --'
*1810                COUT(INDENT+2:)='-- End Do -----------------------'
                  ENDIF
                  WRITE (LUNUSR,'(A)') COUT
  110         CONTINUE
          ENDIF
          IF(LTHERE)THEN
             WRITE(LUNUSR,'(''*B/LINK'')')
             LTHERE=.FALSE.
          ENDIF
          IF(RTHERE)THEN
             WRITE(LUNUSR,'(''*B/RLINK'')')
             RTHERE=.FALSE.
          ENDIF
          IF(BTHERE)THEN
             WRITE(LUNUSR,'(''*B/BI'')')
             BTHERE=.FALSE.
          ENDIF
          IF(DTHERE)THEN
             WRITE(LUNUSR,'(''*B/DATA'')')
             DTHERE=.FALSE.
          ENDIF
*---------- End of loop over link/status bits/data info (400)
  120 CONTINUE
 
      GOTO 140
 
  130 CONTINUE
 
      WRITE(LUNOUT,'(A,A4)')' Previous error occured in: ',
     +                      IQ(KQSP+LQBKD+1)
 
  140 CONTINUE
 
*--- OTTO tell highest link number
 
      IQ(LBQBKD+KQSP+5) = IHLPUT
      IQUEST(MOQUEQ) = LBQBKD
 
      END
*CMZ :  1.30/00 14/06/96  12.56.57  by  Pavel Nevski
*CMZU:  1.00/01 21/01/96  23.17.55  by  Sasha Vanyashin
*-- Author :
      SUBROUTINE DZDDOC(IXSTOR,L,CHBANK,CHOPT,IF1,IL1,LUN,CHPF,NKEEPS)
*.
*. INPUT     :  IXSTOR  store index
*.              L       link to bank to be dumped
*.              CHOPT   character option
*.                      'U' suppress list of UNDEFIND
*.                      'K' Keep sequences
*.                      'D' INTEGER statements for data offsets
*.                      'O' Parameter statements for data offsets
*.                      'Z' force hexadecimal (DZSHOW)
*.                      'T' list also pure Character banks 1 word/line
*.                      'C'  list value only (useful for output read by
*.                           another program
*.                      '='  list as IQ(LCHBANK(1)+IOFF)=value
*.                      'R'  try to recover from incomplete doc
*.                      'V'  return data word values into VVAR
*.                      'P'  return path to data word into VVAR
*.                      'I'  return IO char into CHPF
*.                      'E'  examine, check range
*.              IFIRST   first word to dump
*.              ILAST    last word
*.              LUN      output unit
*.              CHPF     prefix when making FORTRAN code (data words)
*.              NKEEPS   # of data words for which offsets
*.                       have been gen
*. OUTPUT    :
*.
*. CALLS     : DZSHOW UOPTC ,MZDROP,RZIN,UCTOH, DZSHOW
*. CALLED    : DZDISP, USER
*.
*. AUTHOR    : O.Schaile
*. VERSION   : 1.00
*. CREATED   : 7-Aug-88
*. LAST MOD  : 18-OCT-92
*.           : 14-jun-96, PN : INDEXN has 1 argument only
*.**********************************************************************
      CHARACTER*(*) CHOPT, CHPF
      CHARACTER*40 CHPFI
      CHARACTER*8  CHBANK
      INTEGER KEYVEC(2), IWHOLL, NLSKIP,IDELAY
      CHARACTER*11 CVAL, CVALSA
      CHARACTER*21 CLOOP
      CHARACTER*1 COPTDZ
      CHARACTER*80 CLINE, CLINSA, CLINDE
      CHARACTER*8 CVAR, CVAR1
      CHARACTER*12 CTEMP
      SAVE LUNINT, IOCH
      PARAMETER (LUNINV=41)
      LOGICAL NEWVAL,KEEPSQ,INHOLL,REPEND, NEWPNT, LRECOV, ENDED
*     pointer stuff
      INTEGER MAXP, IPOINT
      PARAMETER (MAXP=200)
      CHARACTER*8 CVARP, CHREPC
      CHARACTER*8 CPOINT(MAXP)
      INTEGER POINT(MAXP),NPOINT(MAXP), IWDOC,IWDOCO,IWORD, IF11,IL11,
     +        NSTYP, IPCHPF
      CHARACTER*1 CHARIO,CHARIS
      CHARACTER*7 CHARIA
      CHARACTER*32 CVARNM
 
*     for returning values
      INTEGER IENTRY,ITYYY
      INTEGER VVAR(100), NVAL,ITY, MAXVAL
      INTEGER VALINT
      REAL    VALREA
      EQUIVALENCE (VALINT,VALREA)
      CHARACTER*8 CVREQ
      LOGICAL REPATH, NOTFIL
      CHARACTER*13 SPACES
      EXTERNAL SPACES
*KEEP,NONEWL2.
      CHARACTER*(*) NONEWL
      PARAMETER (NONEWL=',$')
*KEND.
*
*KEEP,BKWRP.
      PARAMETER (LNCARD=80 , LNCAR4=LNCARD/4)
      CHARACTER CARD*(LNCARD)
      COMMON /DZDINC/ CARD
 
      PARAMETER (IRLVMQ = 10)
 
C--     DESCRIPTION OF COMMON DZDTYP
C-      ============================
 
C--   Common DZDTYP contains the decoded information corresponding to
C--   one "CARD" image in variable CARD. Is contains also the back-up
C--   i.e. the old valus of the status flags to treat continuation info
 
C--     VARIABLE                        DESCRIPTION
C-      ========                        ===========
C       ISTATE        Code of state for last valid card ID
C       IDTAG         Code of character identification of card
C       ICONT         Card is continuation of previous one
C       ISLASH        Flag set when last character of CARD is '/'
C                     This character is used to generate a line feed
C                     for multi-line entries
C       IISLSH        Value of ISLASH for previous CARD
C       IREPLV        Repetition level
C       IREPLO        Old repetition level
C       ISCHLO        Old CHOICE section flag
C       IDEMTX        Hollerith code for text as previous entry (DZDINI)
C       IILFLF        Hollerith code for line feed (DZDINI)
C       INUM1         First number if number interpretation possible
C       IHNUM1        Vector containing the Hollerith representation
C                     of the first  number field (if non-numeric)
C                     INUM1 then contains -16* number of words used
C       INUM2         Second number if number interpretation possible
C       IHNUM2        Vector containing the Hollerith representation
C                     of the second number field (if non-numeric)
C                     INUM2 then contains -16* number of words used
C       NBNKS         Number of bank descriptors present
C       NHTAG         Number of characters in the tag field of the card
C                     This field can also correspond to a declared
C                     numeric field with a non-numeric entry
C       NWTAG         Number of 4-byte machine words needed for the tag
C       IHTAG         Vector containing the Hollerith representation
C                     of the tag field of the card
C       NHTXT         Number of characters in the text field of the card
C       NWTAG         Number of 4-byte machine words needed for the text
C       IHTAG         Vector containing the Hollerith representation
C                     of the text field of the card
 
      COMMON/DZDTYP/ISTATE,IDTAG,ICONT,ISLASH,IISLSH,IREPLV,IREPLO,
     X       IDEMTX,IILFLF,INUM1,IHNUM1(LNCAR4),INUM2,IHNUM2(LNCAR4),
     X       NBNKS,NHTAG,NWTAG,IHTAG(LNCAR4),NHTXT,NWTXT,IHTXT(LNCAR4)
 
      INTEGER        LDQBKD,LBQBKD,LDOC,LLTOP,LQBKD,LQBKD1,
     &               LUP,LORIG,LSAME,LNEW,LT,LD1,LD2,
     &               LUPD,LTD,LDD1,LDUMMY
 
      COMMON /DZDOCC/LDQBKD,LBQBKD,LDOC,LLTOP,LQBKD,LQBKD1,
     &               LUP,LORIG,LSAME,LNEW,LT,LD1,LD2,
     &               LUPD,LTD,LDD1,LDUMMY
 
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
              DIMENSION  LQLUP(99), LQLORG(98),IQWIDN(97),IQWIDH(96)
     +,                  IQWNL(95), IQWNS(94), IQWND(93)
            EQUIVALENCE (LQLUP(8),  LQLORG(7), IQWIDN(6), IQWIDH(5)
     +,                  IQWNL(4),  IQWNS(3),  IQWND(2), IQ(1))
      COMMON /MZCN/  IQLN,IQLS,IQNIO,IQID,IQNL,IQNS,IQND, IQNX,IQFOUL
*KEEP,TAPES.
      COMMON /DZDTAP/ LUNIN,LUNOUT,LUNUSR
*KEEP,ZBCDK.
      PARAMETER (MPOSAQ= 1 ,MPOSBQ= 2 ,MPOSCQ= 3 ,MPOSDQ= 4 ,MPOSEQ= 5
     X          ,MPOSFQ= 6 ,MPOSGQ= 7 ,MPOSHQ= 8 ,MPOSIQ= 9 ,MPOSJQ=10
     X          ,MPOSKQ=11, MPOSLQ=12 ,MPOSMQ=13 ,MPOSNQ=14 ,MPOSOQ=15
     X          ,MPOSPQ=16, MPOSQQ=17 ,MPOSRQ=18 ,MPOSSQ=19 ,MPOSTQ=20
     X          ,MPOSUQ=21, MPOSVQ=22 ,MPOSWQ=23 ,MPOSXQ=24 ,MPOSYQ=25
     X          ,MPOSZQ=26                                            )
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,DZDPRM.
      INTEGER ALDBIT
      PARAMETER (ALDBIT=1)
      INTEGER IFLRZF,IFRCAR
     &      ,IFQUIT, IFLDIR, IFWORD,ILWORD, IDVERS
     &      ,IFOMED,LUNGRA,KWTYP,KWID,IPCSIZ,LUDORZ
     &      ,LULIRZ, IFLPKY, LFCOL, IBCCOL,IBDCOL,IDREFL
     &      ,IDZTFO,IDZTPR
      REAL XRANGE,YRANGE,GRIDX,GRIDY,DXTB,DXUB,DXLK, DYB, DXB
     &      ,X0HEAD, Y0HEAD, X0TB, Y0TB,  X0UB, Y0UB
     &      ,RADBUB, CSIZE, CSFACT, ARRLEN,PAGECM,PAMM10,GRIDSC
 
       COMMON/DZDPRM/XRANGE,YRANGE,GRIDX,GRIDY,DXTB,DXUB,DXLK, DYB, DXB
     &      ,X0HEAD, Y0HEAD, X0TB, Y0TB,  X0UB, Y0UB
     &      ,RADBUB, CSIZE, CSFACT, ARRLEN,IFLRZF,IFRCAR
     &      ,IFQUIT, IFLDIR, IFWORD,ILWORD, IDVERS
     &      ,IFOMED,LUNGRA,KWTYP,KWID,PAGECM,PAMM10,GRIDSC,IPCSIZ,LUDORZ
     &      ,LULIRZ, IFLPKY, LFCOL, IBCCOL,IBDCOL,IDREFL
     &      ,IDZTFO,IDZTPR
*KEEP,LINOUT.
C--     Parameters and commons defining the output line
 
C--     Output vector
      PARAMETER (NOUTQ=80)
      CHARACTER COUT*(NOUTQ)
C--     Definition of fields on output line
      PARAMETER (IOTAGQ=12,IOENTQ=21,NOENTQ=NOUTQ-IOENTQ+1)
      PARAMETER (INDENQ=2,NENTIQ=10)
 
      COMMON/CDLINE/COUT
      COMMON/IDLINE/IEWORK,IFLOPT(26),INLINE,INSERT,NOUTF,NWHOLL
C--     Description of the variables in common CDLINE and IDLINE
C     Identifier                     Description
C     ==========                     ===========
C     COUT         Character variable representing the output line
C     IEWORK       Pointer to the last position occupied in the work
C                  variable CWORK (Subr. DZDLIN)
C     IFLOPT (26)  Integer array with value non-zero for each option
C                  set (used by DZDOCO and DZDOCS for transmitting the
C                  options to its daughter routines)
C     INLINE       Offset of the start of the information in COUT
C     INSERT       Pointer to the current text field being treated in
C                  the ZEBRA bank
C     NOUTF        Number of columns available on the output line
C                  to contain the text information
C     NWHOLL       Number of words in the ZEBRA bank containing the
C                  text information and remaining to be treated
*KEEP,DOCPARQ.
C
C----           PARAMETER definitions for DZDOC
C
C--     Offset of DOWN bank for text buffers in master DOC babk
      PARAMETER (MDOCDQ = -1)
C--     Offset of number of words used
      PARAMETER (MDCENQ = 1 )
 
C----   Description of the documentation bank
C       =====================================
 
C--     Bank header part
C       ----------------
C--     Number of words in the header
      PARAMETER (NBHEAQ = 20)
C--     Offset of encoded bank IDH
      PARAMETER (MBIDHQ = 1)
C--     Offset of number of words in use
      PARAMETER (MBUSEQ = MBIDHQ+1)
C--     Offset of number of words in the header
      PARAMETER (MBHEAQ = MBUSEQ+1)
C--     Offset of total number of links
      PARAMETER (MBNNDQ = MBHEAQ+1)
C--     Offset of number of structural links
      PARAMETER (MBNNLQ = MBNNDQ+1)
C--     Offset of number of data words
      PARAMETER (MBNNSQ = MBNNLQ+1)
 
C--     Offset of number of words with general information
      PARAMETER (MBGENQ = 11)
C--     Offset of number of words describing the links
      PARAMETER (MBLINQ = MBGENQ+1)
C--     Offset of number of words describing the ref links
      PARAMETER (MBRLIQ = MBLINQ+1)
C--     Offset of number of words describing the status bits
      PARAMETER (MBBITQ = MBRLIQ+1)
C--     Offset of number of words describing the data words
      PARAMETER (MBDATQ = MBBITQ+1)
 
C---             Bank Description pointers and flags
C---             ===================================
 
C--              Normal entry
C                ------------
C--     Number of words in bank description pointers and flag section
      PARAMETER (NBDSCQ = 4)
C--     Offset of pattern word inside section
      PARAMETER (MBPATQ = 1)
C--     Offset of the two index words inside the section
      PARAMETER (MBIX1Q = MBPATQ+1  , MBIX2Q = MBIX1Q+1)
 
C--              End of sequence
C                ---------------
C--     Number of words in bank description for end of sequence entry
      PARAMETER (NBEOSQ = 2)
 
C--     Descriptor for normal entry
C       ---------------------------
C--     Start bit and number of bits for tag information
      PARAMETER (ICHTGQ = 0 , NCHTGQ = 2)
C--     Multiple choice bit
      PARAMETER (ICHBTQ = 2)
C--     Start bit and number of bits for identifier information
      PARAMETER (ICHIDQ = 10 , NCHIDQ = 5)
C--     Start bit and number of bits for REP. level information
      PARAMETER (IRPLVQ = ICHIDQ+NCHIDQ , NRPLVQ = 4)
C--     Bit for end-of-sequence flag
      PARAMETER (IBEOSQ = IRPLVQ+NRPLVQ)
 
C--     Descriptor for CHOICE tag
C       -------------------------
 
C--     Number of words for CHOICE flag descriptor
      PARAMETER (NCDSCQ = 4)
C--     Offset of pattern word inside section
      PARAMETER (MCPATQ = 1)
 
C--     Offset of the word offset in the bank and its contents
      PARAMETER (MCWOFQ = MCPATQ+1  , MCWCOQ = MCWOFQ+1)
 
C--     Bit flags choice by number (dynamic sector)
      PARAMETER (ICNUMQ = 0 )
C--     Bit flags choice by format (self describing sector)
      PARAMETER (ICFORQ = ICNUMQ + 1)
C--     Bit flags choice by contents
      PARAMETER (ICCONQ = ICFORQ + 1)
C--     Offset of self description information and width
      PARAMETER (ICSELQ = 10, NCSELQ=4)
C--     Offset of selection byte fields in word and width
      PARAMETER (ICBY1Q = ICSELQ+NCSELQ, NCBYTQ=8)
      PARAMETER (ICBY2Q = ICBY1Q+NCBYTQ)
 
*KEND.
      CHARACTER CQSTAK*13,CQINFO*40
      PARAMETER (NLICHQ=130,NSTCHQ=8,NDVCHQ=8,NBKCHQ=4 )
      CHARACTER CQLINE*(NLICHQ),CQMAP(10)*(NLICHQ)
      CHARACTER CQSTOR*(NSTCHQ),CQDIV*(NDVCHQ),CQID*(NBKCHQ)
      COMMON /DZC1CH/ CQSTOR,CQDIV,CQID,CQMAP,CQSTAK,CQINFO
      EQUIVALENCE (CQLINE,CQMAP)
*KEEP,BKNUPARQ.
 
C--               Indefinite (* given in number field)
      PARAMETER ( INUINQ = -1)
C--               Tag (non-numeric description given in number field)
      PARAMETER ( INUTGQ = -2)
 
*KEEP,BKFOPARQ.
 
C--     Definition of the bank IO characteristic types (MZBOOK/MZLIFT)
 
C--               Undefined --> bank cannot be transported
      PARAMETER ( IFOUNQ = 0)
C--               Bit pattern
      PARAMETER ( IFOBIQ = 1)
C--               Integer
      PARAMETER ( IFOINQ = 2)
C--               Floating point
      PARAMETER ( IFOFLQ = 3)
C--               Double precision
      PARAMETER ( IFODOQ = 4)
C--               Hollerith
      PARAMETER ( IFOHOQ = 5)
C--               Self describing sector
      PARAMETER ( IFOSEQ = 7)
C--               Retrieve by name
      PARAMETER ( IFONAQ = 9)
C--               Copy from linear chain
      PARAMETER ( IFOLIQ = 11)
C--               Multiplication factor for self-describing sector
      PARAMETER ( JFOSEQ = 16)
 
*KEEP,BKSTPARQ.
 
C--               General information
      PARAMETER ( ISGENQ = 1)
C--              Link description
      PARAMETER ( ISLINQ = ISGENQ+1)
C--              ref Link description
      PARAMETER ( ISRLIQ = ISLINQ+1)
C--               Status bit description
      PARAMETER ( ISBITQ = ISRLIQ+1)
C--               Data description
      PARAMETER ( ISDATQ = ISBITQ+1)
C--               Choice section
      PARAMETER ( ISCHOQ = 16)
C--               Repetition section
      PARAMETER ( ISREPQ = 32)
 
*KEEP,BKTGPARQ.
 
 
C--     Description of the action flags
 
C-      Code for NO  entry
      PARAMETER (IBKANQ = -1)
C-      Code for YES entry
      PARAMETER (IBKAYQ = -2)
C-      Flag for numeric tag field
      PARAMETER (IBKAMQ = -3)
C-      Flag for special decoding(CHOICE tag)
      PARAMETER (IBKASQ = -9)
 
C--     Description of the action fields
 
C-      Offset of state information
      PARAMETER (MBKASQ = 1)
C-      Offset of tag flag (1,2 words , numeric)
      PARAMETER (MBKAGQ = MBKASQ+1)
C-      Offset of repetition flag
      PARAMETER (MBKARQ = MBKAGQ+1)
C-      Offset of choice flag
      PARAMETER (MBKAHQ = MBKARQ+1)
C-      Number of action fields
      PARAMETER (NBKACQ = MBKAHQ)
 
C----   Identifiers of various card tags
 
C--               AUthor
      PARAMETER (ITGAUQ = 1)
C--               BIt (status)
      PARAMETER (ITGBIQ = ITGAUQ+1)
C--               CHoice section
      PARAMETER (ITGCHQ = ITGBIQ+1)
C--               DAta section
      PARAMETER (ITGDAQ = ITGCHQ+1)
C--               Division
      PARAMETER (ITGDVQ = ITGDAQ+1)
C--               LInk section
      PARAMETER (ITGLIQ = ITGDVQ+1)
C--               RLink section
      PARAMETER (ITGRLQ = ITGLIQ+1)
C--               Number of data words (ND)
      PARAMETER (ITGNDQ = ITGRLQ+1)
C--               Total Number of Links (NL)
      PARAMETER (ITGNLQ = ITGNDQ+1)
C--               Number of Structural links (NS)
      PARAMETER (ITGNSQ = ITGNLQ+1)
C--               NeXt link
      PARAMETER (ITGNXQ = ITGNSQ+1)
C--               ORigin link
      PARAMETER (ITGORQ = ITGNXQ+1)
C--               REpetition section
      PARAMETER (ITGREQ = ITGORQ+1)
C--               STore
      PARAMETER (ITGSTQ = ITGREQ+1)
C--               UP link
      PARAMETER (ITGUPQ = ITGSTQ+1)
C--               VErsion
      PARAMETER (ITGVEQ = ITGUPQ+1)
C--               Entry
      PARAMETER (ITGENQ = ITGVEQ+1)
C--               NZERO words to preset to zero
      PARAMETER (ITGNZQ = ITGENQ+1)
C--               IO characteristics
      PARAMETER (ITGIOQ = ITGNZQ+1)
C--               Numerical identifier
      PARAMETER (ITGNIQ = ITGIOQ+1)
C--               IDem qualifier
      PARAMETER (ITGIDQ = ITGNIQ+1)
C--               Tag length for entry
      PARAMETER (NWTENQ = 2)
 
*KEEP,BKTGDATQ.
      CHARACTER CBKTAC(ITGIDQ)*2
      DIMENSION IBKTAC(NBKACQ,ITGIDQ)
 
C--               AUthor
      DATA CBKTAC(ITGAUQ)        / 'AU'   /
      DATA IBKTAC(MBKASQ,ITGAUQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGAUQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGAUQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGAUQ) / IBKANQ /
C--               BIt (status)
      DATA CBKTAC(ITGBIQ)        / 'BI'   /
      DATA IBKTAC(MBKASQ,ITGBIQ) / ISBITQ /
      DATA IBKTAC(MBKAGQ,ITGBIQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGBIQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGBIQ) / IBKAYQ /
C--               CHoice section
      DATA CBKTAC(ITGCHQ)        / 'CH'   /
      DATA IBKTAC(MBKASQ,ITGCHQ) / ISCHOQ /
      DATA IBKTAC(MBKAGQ,ITGCHQ) / IBKASQ /
      DATA IBKTAC(MBKARQ,ITGCHQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGCHQ) / IBKANQ /
C--               DAta section
      DATA CBKTAC(ITGDAQ)        / 'DA'   /
      DATA IBKTAC(MBKASQ,ITGDAQ) / ISDATQ /
      DATA IBKTAC(MBKAGQ,ITGDAQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGDAQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGDAQ) / IBKAYQ /
C--               Division
      DATA CBKTAC(ITGDVQ)        / 'DV'   /
      DATA IBKTAC(MBKASQ,ITGDVQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGDVQ) /      2 /
      DATA IBKTAC(MBKARQ,ITGDVQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGDVQ) / IBKAYQ /
C--               LInk section
      DATA CBKTAC(ITGLIQ)        / 'LI'   /
      DATA IBKTAC(MBKASQ,ITGLIQ) / ISLINQ /
      DATA IBKTAC(MBKAGQ,ITGLIQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGLIQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGLIQ) / IBKAYQ /
C--               RLink section
      DATA CBKTAC(ITGRLQ)        / 'RL'   /
      DATA IBKTAC(MBKASQ,ITGRLQ) / ISRLIQ /
      DATA IBKTAC(MBKAGQ,ITGRLQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGRLQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGRLQ) / IBKAYQ /
C--               Numerical Identifier
      DATA CBKTAC(ITGNIQ)        / 'NI'   /
      DATA IBKTAC(MBKASQ,ITGNIQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNIQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNIQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNIQ) / IBKANQ /
C--               Number of Data words
      DATA CBKTAC(ITGNDQ)        / 'ND'   /
      DATA IBKTAC(MBKASQ,ITGNDQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNDQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNDQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNDQ) / IBKANQ /
C--               Total Number of Links
      DATA CBKTAC(ITGNLQ)        / 'NL'   /
      DATA IBKTAC(MBKASQ,ITGNLQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNLQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNLQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNLQ) / IBKANQ /
C--               Number of Structural links
      DATA CBKTAC(ITGNSQ)        / 'NS'   /
      DATA IBKTAC(MBKASQ,ITGNSQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNSQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNSQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNSQ) / IBKANQ /
C--               NeXt link
      DATA CBKTAC(ITGNXQ)        / 'NX'   /
      DATA IBKTAC(MBKASQ,ITGNXQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNXQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGNXQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNXQ) / IBKAYQ /
C--               ORigin link
      DATA CBKTAC(ITGORQ)        / 'OR'   /
      DATA IBKTAC(MBKASQ,ITGORQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGORQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGORQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGORQ) / IBKAYQ /
C--               REpetition section
      DATA CBKTAC(ITGREQ)        / 'RE'   /
      DATA IBKTAC(MBKASQ,ITGREQ) / ISREPQ /
      DATA IBKTAC(MBKAGQ,ITGREQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGREQ) / IBKAYQ /
      DATA IBKTAC(MBKAHQ,ITGREQ) / IBKAYQ /
C--               STore
      DATA CBKTAC(ITGSTQ)        / 'ST'   /
      DATA IBKTAC(MBKASQ,ITGSTQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGSTQ) /      2 /
      DATA IBKTAC(MBKARQ,ITGSTQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGSTQ) / IBKAYQ /
C--               UP link
      DATA CBKTAC(ITGUPQ)        / 'UP'   /
      DATA IBKTAC(MBKASQ,ITGUPQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGUPQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGUPQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGUPQ) / IBKAYQ /
C--               VErsion
      DATA CBKTAC(ITGVEQ)        / 'VE'   /
      DATA IBKTAC(MBKASQ,ITGVEQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGVEQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGVEQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGVEQ) / IBKANQ /
C--               NZERO number of data words preset to 0
      DATA CBKTAC(ITGNZQ)        / 'NZ'   /
      DATA IBKTAC(MBKASQ,ITGNZQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGNZQ) / IBKAMQ /
      DATA IBKTAC(MBKARQ,ITGNZQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGNZQ) / IBKANQ /
C--              IO characteristics
      DATA CBKTAC(ITGIOQ)        / 'IO'   /
      DATA IBKTAC(MBKASQ,ITGIOQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGIOQ) / IBKANQ /
      DATA IBKTAC(MBKARQ,ITGIOQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGIOQ) / IBKANQ /
C--               IDEM
      DATA CBKTAC(ITGIDQ)        / 'ID'   /
      DATA IBKTAC(MBKASQ,ITGIDQ) / ISGENQ /
      DATA IBKTAC(MBKAGQ,ITGIDQ) /      1 /
      DATA IBKTAC(MBKARQ,ITGIDQ) / IBKANQ /
      DATA IBKTAC(MBKAHQ,ITGIDQ) / IBKAYQ /
 
*KEND.
*
      DATA CHARIA/'BIFDHUR'/
      DATA LUNINT/0/
*------
      IENTRY = 1
      ITY    = 0
      IF11=IF1
      IL11=IL1
      IF(INDEX(CHOPT,'K').NE.0 .OR. INDEX(CHOPT,'I').NE.0)THEN
         KEEPSQ=.TRUE.
      ELSE
*KEEP,QSTORE.
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)
***********************************************************************
*KEND.
         IF(IL11.GT.IQ(KQS+L-1))IL11=IQ(KQS+L-1)
         KEEPSQ=.FALSE.
      ENDIF
      NSTYP=0
      CHARIS=' '
      CHARIO=' '
      IF(INDEX(CHOPT,'D').NE.0)THEN
         IF(INDEX(CHOPT,'R').NE.0)THEN
            CHARIO='R'
         ELSE
            CHARIO='I'
         ENDIF
      ENDIF
      IF(INDEX(CHOPT,'I').NE.0)THEN
         IPCHPF=1
         CHPF=' '
      ELSE
         CALL UCTOH(CHBANK,KEYVEC,4,8)
      ENDIF
      LUC = LUN
      REPATH=.FALSE.
      MAXVAL=0
      GOTO 2
 
      ENTRY DZDGVA(IXSTOR, L, CHOPT,CVREQ,NVAL,VVAR,ITYYY)
      IENTRY = 2
      ITY    = 0
      IF(L.EQ.0)GOTO 990
*KEEP,QSTORE.
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)
***********************************************************************
*KEND.
      LUC = 6
      IF11=1
      IL11=IQ(KQS+L-1)
      MAXVAL=NVAL
      NVAL=0
      ITY=-1
      IPREP0=0
      IPREP1=0
      IPDRE0=0
      IPDRE1=0
      NOTFIL=.TRUE.
      IF(INDEX(CHOPT,'P').NE.0)THEN
         REPATH=.TRUE.
      ELSE
         REPATH=.FALSE.
      ENDIF
      KEYVEC(1)=IQ(KQS+L-4)
      LUP=LQ(KQS+L+1)
      IF(LUP.NE.0)THEN
         KEYVEC(2)=IQ(KQS+LUP-4)
      ELSE
         CALL UCTOH('NONE',KEYVEC(2),4,4)
      ENDIF
 
2     LUNINT = LUNINV
      LUNSAV = IQPRNT
      IDENTF=0
      IWDOCO=0
      NEXTRA=0
      IMBED2=0
      IOCH = -1
      IPOINT=0
      DO 5 I=1,MAXP
         POINT(I)  = -1
         CPOINT(I) = ' '
5        NPOINT(I) = -1
 
*      IREPC=-2
      IPRKEE=0
      NLSKIP=0
      IDELAY=0
      CLINSA=' '
      LCLINE  = LEN(CLINE)
      IPLINE = 1
      INHOLL = .FALSE.
      IF(INDEX(CHOPT,'R').NE.0)THEN
         LRECOV=.TRUE.
      ELSE
         LRECOV=.FALSE.
      ENDIF
      ENDED =.FALSE.
      REPEND=.FALSE.
      NEWPNT=.FALSE.
      IF(KEEPSQ)THEN
          NBLENG = IL1
      ELSE
         NBLENG = IQ(KQS+L-1)
         KEEPSQ=.FALSE.
*         CALL CLTOU(CHOPT)
         IF(INDEX(CHOPT,'Z').NE.0)THEN
            COPTDZ='Z'
         ELSE
            COPTDZ=' '
         ENDIF
         CALL UCTOH ('$LF/',IILFLF,4,4)
      ENDIF
      IF(INDEX(CHOPT,'C').NE.0 .AND. .NOT.KEEPSQ)THEN
         IQPRNT=LUC
         IW1=IF11
         GOTO 90
      ENDIF
      IF(INDEX(CHOPT,'I').EQ.0)
     +CALL  DZDGDO(0,LQBKD1,KEYVEC,CLINE,IFC,ILC,ICYCLE)
      IF(LQBKD1.EQ.0)THEN
         IF(KEEPSQ  .OR. INDEX(CHOPT,'V').NE.0)THEN
            WRITE(LUC,'(A)')'*   No documentation for '//CHBANK(1:4)
            GOTO 990
         ENDIF
         NDATA = 0
      ELSE
 
         IF(ICYCLE.LT.0)WRITE(LUC,'(A)')
     &  ' **** Requested version not found ****'
         IPDATA = IQ(KQS+LQBKD1+MBHEAQ) + IQ(KQS+LQBKD1+MBGENQ)
     +           +IQ(KQS+LQBKD1+MBLINQ) + IQ(KQS+LQBKD1+MBRLIQ)
     &           +IQ(KQS+LQBKD1+MBBITQ) + 1
         IP1 = 0
         IP2 = 0
         IC1 = 0
         IC2 = 0
         IWORD = 0
         IWORDR=0
         IREPL=0
         IFREPL = 0
         CHREPC=' '
         ILOWRC=0
         IUPERC=0
         LOOPC1=-1
         LOOPC2=-1
         IPFORM=0
         ICFORM=0
         IMFORM=0
         LALILE=0
         IP = KQS+LQBKD1+IPDATA
         IPSAVE=IP
         NDATA = IQ(KQS+LQBKD1+MBDATQ)
      ENDIF
 
      IF(INDEX(CHOPT,'Q').EQ.0 .AND.
     &   INDEX(CHOPT,'V').EQ.0 .AND.
     &  .NOT.KEEPSQ)THEN
         IF(INDEX(CHOPT,'E').EQ.0)THEN
            WRITE(LUC,'(10A)')
     &' -------- Data of Bank/UpBank: ',CHBANK(1:4),'/',CHBANK(5:8),
     &     ' Doc Version: ',CLINE(IFC:ILC), ' ----------'
         ELSE
            WRITE(LUC,'(10A)')
     &   '  Checking data of Bank/UpBank: ',CHBANK(1:4),'/',CHBANK(5:8)
         ENDIF
      ENDIF
 
      IF(NDATA.GT.0)THEN
          IC9 = 10
      ELSE
          IQPRNT = LUC
          IW1 = IF11
          WRITE(LUC,'(A)')
     +    '* Data words not documented for '//CHBANK(1:4)
          IF(KEEPSQ .OR. INDEX(CHOPT,'V').NE.0)THEN
             GOTO 990
          ELSE
             GOTO 90
          ENDIF
      ENDIF
      LDATUM = IP + NDATA
      IWDOC = 0
 
*      IF(.NOT.KEEPSQ) WRITE(LUC,*)' '
*
*     IF11,IL11 first, last word to be doc'td
*     IWORD   current word in data
*     IWORDR   current word in rep section
*     IWDOC   word announced in documentation
*     IWDOCO  remember announced word (for cont lines)
*     IP      pointer in documentation
*     IP1     remember IP for start of rep lev 1
*     IP2     remember IP for start of rep lev 2
*     IC1,IC2 repetition counter 1, 2
*     IT      type of info in doc
*             2 integer
*             5 holl
*     NW      # of words in doc
*     IDENT   ITGREQ describe rep
*             ITGENQ describe seq # of data
*     NEWVAL  if false: cont card
*     INHOLL  holl text in data words started
*     IPFORM  pointer to a key descriptor format (see RZ)
*     LOOPC1  or LOOPC2)loop counters in rep section
*
 
 
   10 CONTINUE
      IF(IP .GE. LDATUM)THEN
          IF(.NOT.KEEPSQ)THEN
              IQPRNT = LUC
               ENDED=.TRUE.
               NEWVAL=.TRUE.
               IP=IPSAVE
          ENDIF
          IF(KEEPSQ)GOTO 990
      ENDIF
      IT = MOD(IQ(IP),16)
      NW = IQ(IP)/16
*      WRITE(*,*)' IT,NW,IP ',IT,NW,IP
      IF(NW .LE. 0)THEN
         WRITE(LUC,'(A,2I9)')' Illegal NW at IPDATA ',NW,IPDATA
         GOTO 990
      ENDIF
 
*     start hollerith sector
 
      IF(IT .EQ. 5)THEN
*         WRITE(*,*)' IDENTF= ',IDENTF
*        try to get rep count name and range
         IF(KEEPSQ .AND. ABS(IDENTF).EQ. ITGREQ)THEN
            NCH=MIN(NW*4,LEN(CLINE))
            CLINE=' '
            CALL UHTOC(IQ(IP+1),4,CLINE,NCH)
            NCH=LNBLNK(CLINE)
            ICOLON=INDEX(CLINE(1:8),':')+1
            CHREPC=CLINE(ICOLON:8)
            IFC=INDEX(CLINE,'[')
            ILC=INDEX(CLINE,']')
            IFC=IFC+1
            ILC=ILC-1
            NC=INDEX(CLINE(IFC:ILC),',')
            IF(NC.EQ.0)NC=INDEX(CLINE(IFC:ILC),':')
            IF(IFC.GT.1 .AND. ILC.GT.IFC+2 .AND. NC.NE.0)THEN
               ILC1=IFC+NC-2
               IFC2=ILC1+2
               CALL DZDCTI(CLINE(IFC:ILC1),ILOWRC)
               CALL DZDCTI(CLINE(IFC2:ILC),IUPERC)
            ENDIF
         ENDIF
         IF(IDENTF .NE. ITGENQ) GOTO 80
 
*        rep count = 0 calc from data word
*         IF(IREPC .EQ. 0)GOTO 80
 
         IF(      IWORD+1 .NE. IWDOC
     +      .AND. IP1+IP2 .EQ. 0
     +      .AND. IWDOC   .NE. IWDOCO )THEN
              IWDOCO = -1
         ENDIF
 
*        rep section ended already?
 
         IF(REPEND)GOTO 80
 
*        look if more words documented then announced
 
         IF(NEXTRA.LT.0 .AND. LRECOV)THEN
            IF(IWDOC.GT.ABS(NEXTRA))THEN
               GOTO 80
            ENDIF
         ENDIF
 
*        is it not continuation card for same item
*        or not a start of rep section
 
         NEWVAL = .FALSE.
*         WRITE(*,*)'IWDOCO ,IWDOC, IWORD', IWDOCO ,IWDOC, IWORD
         IF(IWDOCO .NE. IWDOC .OR. IWDOCO .LE. 0 .OR. NEWPNT)THEN
            IWORD = IWORD+1
            IWORDR = IWORDR+1
            NEWVAL = .TRUE.
         ENDIF
*        remember possible repetition count
         IVALLW = IQ(KQS+L+IWORD)
 
         IF(IWORD .GT. IL11)GOTO 990
         IF(IWORD .LT. IF11)GOTO 80
 
*         look if all words are hollerith
 
         IF(IOCH .LT. 0)THEN
            NIO = JBYT(IQ(KQS+L),19,4)
            NL =  IQ(KQS+L-3)
            IOFFBS = - (NIO + NL + 8 + 1)
            IOCH = JBYT(IQ(KQS+L+IOFFBS),17,16)
            IF(IOCH .EQ. 5 .AND. INDEX(CHOPT,'Z').EQ. 0
     +      .AND. INDEX(CHOPT,'T').EQ. 0)THEN
               IF(.NOT.KEEPSQ)THEN
                   WRITE(LUC,'(1X,2A4,1X,100(15A4/7X))')
     +             (IQ(IP+K),K=1,NW)
                   WRITE(LUC,'(A)')'---- '
               ENDIF
               NEWVAL = .TRUE.
            ENDIF
         ENDIF
 
*        loop here if all words are hollerith
 
   20    CONTINUE
*        empty text buffer at end
          IF(IWORD .GT. IL11)THEN
            IF(IPLINE .GT. 1)THEN
               IF(.NOT.KEEPSQ)
     +          WRITE(LUC,'(14X,A)')CLINE(1:IPLINE-1)
                IPLINE = 1
            ENDIF
            GOTO 990
         ENDIF
 
*        get the printed value from CQLINE of DZSHOW  (Quiet option)
         IF(NEWVAL     .AND.
     &     .NOT.KEEPSQ .OR.
     &     (NEWVAL .AND. INDEX(CHOPT,'V').NE.0 .AND. ITY.EQ.-1)
     &     )THEN
             IF(IC9 .GE. 9 .OR. NEWPNT)THEN
                CALL DZSHOW(' ',IXSTOR, L,COPTDZ//'Q',1,0,IWORD,IWORD+8)
                IC9 = 1
             ELSE
                IC9 = IC9+1
             ENDIF
             IBV1 = IC9*12
             IBV2 = IBV1+10
             CVAL = CQLINE(IBV1:IBV2)
             CVALSA=CVAL
         ELSE
             CVAL = '          '
         ENDIF
*        collect text on CLINE
         IF(IOCH .EQ. 5            .AND.
     +      INDEX(CHOPT,'Z').EQ.0  .AND.
     +      INDEX(CHOPT,'T').EQ. 0 )THEN
            IF(IPLINE .GE. LCLINE)THEN
               IF(.NOT.KEEPSQ)
     +         WRITE(LUC,'(14X,A)')CLINE(1:IPLINE-1)
               IPLINE = 1
            ENDIF
            CLINE(IPLINE:IPLINE+3)=CVAL(8:11)
            IPLINE = IPLINE+4
            IF(INHOLL)THEN
               IWORD = IWORD+1
               GOTO 20
            ELSE
               INHOLL = .TRUE.
               CVAL = ' '
            ENDIF
         ELSE
 
*        output other then pure text, empty text buffer
 
             IF(IPLINE .GT. 1)THEN
                IF(.NOT.KEEPSQ .AND.INDEX(CHOPT,'V').EQ.0)
     &          WRITE(LUC,'(14X,A)')CLINE(1:IPLINE-1)
                IPLINE= 1
             ENDIF
             INHOLL = .FALSE.
         ENDIF
 
         CALL UHTOC(IQ(IP+1),4,CVAR,8)
 
*        return value?
 
         IF(INDEX(CHOPT,'V').NE.0)THEN
            IF(CVAR.EQ.CVREQ)THEN
*              find data type
               IF(ITY.LT.0)THEN
                  IF     (INDEX(CVAL,'"').NE.0)THEN
                     ITY=5
                  ELSE IF(INDEX(CVAL,'.').NE.0)THEN
                     ITY=3
                  ELSE
                     ITY=2
                  ENDIF
               ENDIF
*              return path only?
               IF(REPATH)THEN
                  IF(NOTFIL)THEN
                     NOTFIL=.FALSE.
                     NVAL=NVAL+1
                     IF(IREPL.LE.1)THEN
                        VVAR(NVAL)=IWORD-IPREP0
                     ELSE
                        VVAR(NVAL)=IWORD-IPREP1
                     ENDIF
                  ENDIF
               ELSE
                  IF(ITY.EQ.5)THEN
                     WRITE(*,*)'Holleriths not yet supported'
                     ITY=5
                     GOTO 80
                  ENDIF
                  NVAL=NVAL+1
                  VVAR(NVAL)=IQ(KQS+L+IWORD)
               ENDIF
            ENDIF
            IF(NVAL.EQ.MAXVAL)THEN
               IF(MAXVAL.GT.1)WRITE(*,*)
     &         'Max number of values reached', MAXVAL
                GOTO 990
            ELSE
               GOTO 80
            ENDIF
         ENDIF
 
         CVAR1 = CVAR
         CALL CLTOU(CVAR1)
 
*        conVert it by ZITOH?
 
         IF     (CVAR1(1:2).EQ.'Z:')THEN
            CALL ZITOH(IQ(KQS+L+IWORD),IWHOLL,1)
            CVAL=' '
            CALL UHTOC(IWHOLL,4,CVAL,4)
*        format of a Key descriptor
         ELSE IF(CVAR1(1:2).EQ.'F:')THEN
            IF(IPFORM.EQ.0)IPFORM=KQS+L+IWORD
            DO 15 I=1,10
               IFM=JBYT(IQ(KQS+L+IWORD),(I-1)*3+1,3)
               IF     (IFM.EQ.1)THEN
                  CVAL(I:I)='I'
                  IMFORM=IMFORM+1
               ELSE IF(IFM.EQ.3)THEN
                  CVAL(I:I)='H'
                  IMFORM=IMFORM+1
                ELSE
                  CVAL(I:I)=' '
               ENDIF
               CVAL(11:11)=' '
15          CONTINUE
         ELSE IF(CVAR1(1:2).EQ.'K:')THEN
            ICFORM=ICFORM+1
            IF(ICFORM.GT.IMFORM)ICFORM=1
            IFC2=ICFORM/10
            IFC1=MOD(ICFORM,10)
            IF(IFC1.EQ.0)THEN
               IFC1=10
               IFC2=IFC2-1
            ENDIF
            IFM=JBYT(IQ(IPFORM+IFC2),(IFC1-1)*3+1,3)
            IF(IFM.EQ.3)THEN
               CALL ZITOH(IQ(KQS+L+IWORD),IWHOLL,1)
               CVAL=' '
               CALL UHTOC(IWHOLL,4,CVAL,4)
            ENDIF
         ELSE IF(CVAR1(1:2).EQ.'B:')THEN
             WRITE(CVAL,'(Z9)')IQ(KQS+L+IWORD)
             CVALSA=CVAL
         ELSE IF(CVAR1(1:2).EQ.'D:')THEN
             CALL RZDATE(IQ(KQS+L+IWORD),IDATX,ITIMX,1)
             WRITE(CVAL(1:6),'(I6)')MOD(IDATX,1000000)
             WRITE(CVAL(8:11),'(I4)')MOD(ITIMX,10000)
             CVAL(7:7)='/'
         ENDIF
*     pointer stuff
 
*     look if a label is reached
 
      IF(NEWPNT .OR. .NOT. NEWVAL)THEN
        NEWPNT=.FALSE.
      ELSE
       IF(IPOINT.GT.0)THEN
         DO I=1,IPOINT
            IF(IWORD.EQ.POINT(I) .AND. NPOINT(I).NE.0)THEN
*           skip in doc until label is found
               IF(ENDED)ENDED=.FALSE.
               IPP=IPSAVE
               NWP=-1
21             IPP=IPP+NWP+1
               IF(IPP.GE.LDATUM)THEN
                  WRITE(*,*)'No label found for : ',CPOINT(I)
                  GOTO 26
               ENDIF
               ITP = MOD(IQ(IPP),16)
               NWP = IQ(IPP)/16
               IF(ITP.NE.5)GOTO 21
               CALL UHTOC(IQ(IPP+1),4,CVARP,8)
               CALL CLTOU(CVARP)
               IF(CVARP(1:2).NE.'L:')GOTO 21
 
               IF(CVARP(3:).EQ.CPOINT(I)(3:))THEN
*                 remember for later in case identical lines are skipped
                  WRITE(CLINDE,'(2A4,13X,14A4)')
     +            (IQ(IPP+K),K=1,NWP)
                  IDELAY=1
                  IP=IPP+NWP+1
                  NEWPNT=.TRUE.
*                 end a possible infinite repetition
                  IF(IFREPL.EQ.0)THEN
                     IWORD=IWORD-1
                  ELSE
                     IWORD=IWORD-1
                     IFREPL=0
                  ENDIF
*                  WRITE(*,*)'Label found',IWORD,' ',CPOINT(I)
                  IWDOCO=-1
                  GOTO 10
               ELSE
                  GOTO 21
               ENDIF
            ENDIF
         ENDDO
         IF(ENDED)THEN
            IW1=IWORD
            GOTO 90
         ENDIF
       ENDIF
      ENDIF
 
*     is the pointer bit coded in cont card?
      IF(INDEX(CVALSA,'.').NE.0)THEN
         IF(Q(KQS+L+IWORD).GT.0. .AND. Q(KQS+L+IWORD).LT.1000000.)THEN
            IBVAL=Q(KQS+L+IWORD)
         ELSE
            IBVAL=0
         ENDIF
      ELSE
         IBVAL=IQ(KQS+L+IWORD)
      ENDIF
      IF(.NOT.NEWVAL)THEN
         IF(CVAR1(2:4).EQ.':BI')THEN
            READ(CVAR1(5:6),'(I2)',ERR=40  )I1BIT
            IF(I1BIT.GT.31)GOTO 24
            READ(CVAR1(7:8),'(I2)',ERR=24  )I2BIT
            IF(I2BIT.GT.31)GOTO 24
            IF(I2BIT.LT.I1BIT)GOTO 24
            IBVAL = JBYT(IQ(KQS+L+IWORD),I1BIT+1,I2BIT-I1BIT+1)
            IF(INDEX(CHOPT,'Z').NE.0)THEN
               WRITE(CVAL,'(Z11)')IBVAL
            ELSE
               WRITE(CVAL,'(I11)')IBVAL
            ENDIF
*           get the name
            IF(NW.LT.3)THEN
               CTEMP='XXXXXX'
            ELSE
               NCH=MIN(NW-2,2)*4
               IF(NCH.GT.6)NCH=6
               CALL UHTOC(IQ(IP+3),4,CTEMP,NCH)
*              embedded space
               IPSP=INDEX(CTEMP,' ')
               IF(IPSP.NE.0)CTEMP(IPSP:)=' '
            ENDIF
            CVAR1(3:8)=CTEMP
         ENDIF
      ENDIF
 
24    CONTINUE
 
*     if it is a pointer or rep count of it, remember its value
 
      IF(CVAR1(1:2).EQ.'P:' .OR. CVAR1(1:2).EQ.'N:')THEN
*        already there?
         IF(IPOINT.GT.0)THEN
            DO I=1,IPOINT
               IF(CPOINT(I).EQ.CVAR1)THEN
*                  IF(CVAR1(1:2).EQ.'P:')THEN
*                     IF(POINT(I).GE.0)THEN
*                        IF(POINT(I) .LT. IQ(KQS+L+IWORD))
*     &                  POINT(I)=IQ(KQS+L+IWORD)
*                        WRITE(*,*)'Ambigous pointer: ', CPOINT(I)
*                     ELSE
*                        POINT(I)=IBVAL
*                        GOTO  25
*                     ENDIF
*                  ELSE
                  IF(CVAR1(1:2).EQ.'N:')THEN
                     IF(NPOINT(I).GE.0)THEN
                        WRITE(*,*)'Ambigous rep count: ', CPOINT(I)
                     ELSE
*                       may be a simple expression of the value
                        CALL DZDGRC(IQ(IP),2,IBVAL,IREPC,NEXTRA,
     &                  IDUMMY,0,NDUMMY)
                        IF(IREPC.GT.0)IBVAL=IREPC
                        NPOINT(I)=IBVAL
                        GOTO  25
                     ENDIF
                  ENDIF
               ENDIF
            ENDDO
         ENDIF
         IPOINT=IPOINT+1
         IF(IPOINT.GT.MAXP)THEN
            WRITE(*,*)'Too many pointers:',IPOINT
         ELSE
            CPOINT(IPOINT)=CVAR1
            IF(CVAR1(1:2).EQ.'P:')THEN
               POINT (IPOINT)=IBVAL
*              does it point to same as previous
               IF(IPOINT.GT.1)THEN
                  DO I=1,IPOINT-1
                     IF(POINT(I).EQ.POINT(IPOINT)
     &               .AND. POINT(I).NE.0)THEN
                        POINT(I)=-1
                       WRITE(*,*)'Pointer: ',CPOINT(I),
     &                  ' overwritten by: ',CPOINT(IPOINT)
                     ENDIF
                  ENDDO
               ENDIF
            ELSE
*              may be a simple expression of the value
               CALL DZDGRC(IQ(IP),2,IBVAL,IREPC,NEXTRA,
     &         IDUMMY,0,NDUMMY)
               IF(IREPC.GT.0)IBVAL=IREPC
               NPOINT (IPOINT)=IBVAL
            ENDIF
         ENDIF
25       CONTINUE
      ENDIF
 
26    CONTINUE
 
*     pointer stuff end
 
*       if cont line then look if its mask, bitvalue or choice
         LENMSK=0
         IF(.NOT.NEWVAL)THEN
*            wildchar mask
             IF(CVAR(1:8) .EQ. 'WILDCHAR' .OR.
     &          CVAR(1:4) .EQ. 'MASK')THEN
                IF(KEEPSQ)GOTO 80
*               get the mask
                IF(NW.LT.3)THEN
*                  no mask provided
                   GOTO 80
                ELSE
                   CVAR1 = ' '
                   CTEMP=' '
                   NCH=MIN(NW-2,2)*4
                   IF(NCH.GT.11)NCH=11
                   CALL UHTOC(IQ(IP+3),4,CTEMP,NCH)
*                  embedded space
                   NCH=INDEX(CTEMP,' ')-1
                   IF(NCH.LE.0)NCH=11
                   LENMSK=NCH
                   CTEMP(NCH+1:)=' '
*                  look if it matches
                   DO 28 I=11,1,-1
*                     mask ended?
                      IF(NCH.LE.0)THEN
                         IF(CVALSA(I:I).EQ. ' ')THEN
                            GOTO 29
                         ELSE
                            GOTO 80
                         ENDIF
                      ENDIF
*                     value ended, is rest of mask *?
                      IF(CVALSA(I:I).EQ. ' ')THEN
                         DO 27 J=NCH,1,-1
                           IF(CTEMP(J:J).NE.'*')GOTO 80
27                       CONTINUE
                         GOTO 29
                      ENDIF
                      IF(CTEMP(NCH:NCH).EQ.'*')GOTO 28
                      IF(CTEMP(NCH:NCH).NE.CVALSA(I:I))GOTO 80
28                 NCH=NCH-1
29                 CONTINUE
*                  all matched, does it still fit on line?
                   NCH=(NW-2)*4
                   IF(NCH+LALILE-LENMSK.GT.80)GOTO 50
 
                   CLINE=' '
                   CALL UHTOC(IQ(IP+3),4,CLINE,NCH)
                   NCH=LENOCC(CLINE)
                   LALILE=LALILE+NCH-LENMSK
                   WRITE(LUC,'(A'//NONEWL//')')CLINE(LENMSK+1:NCH)
                   LENMSK=0
                   GOTO 80
                ENDIF
            ENDIF
 
*            choice
             IF(CVAR(1:6) .EQ. 'BITVAL')THEN
                 IF(KEEPSQ)GOTO 80
                 READ(CVAR(7:8),'(I2)')IBIT
                 IF(IAND(IQ(KQS+L+IWORD),ISHFT(1,IBIT)).EQ.0)THEN
                     GOTO 80
                 ELSE
                     CVAR1 = ' '
                     GOTO 50
                 ENDIF
             ENDIF
*            choice starts with C, and
*            contains only numbers or  _  + -
*
             IF(CVAR(1:1).EQ.'C')THEN
                 ILC = INDXBC(CVAR,' ')
                 IF(ILC.LE.1)GOTO 40
                 IFNUM = 2
                 DO 30   K=2,ILC
                     IF(INDXNC(CVAR(K:K)) .NE. 0
     +               .AND.      CVAR(K:K) .NE. '_'
     +               .AND.      CVAR(K:K) .NE. '-'
     +               .AND.      CVAR(K:K) .NE. '+')GOTO 40
                     IF(CVAR(K:K) .EQ. '_')IFNUM=K+1
   30            CONTINUE
                 IF(IFNUM.GT.ILC)GOTO 40
                 IF(KEEPSQ)GOTO 80
                 READ(CVAR(IFNUM:ILC),'(I8)')IVAL
                 IF(INDEX(CVALSA,'.').NE.0)THEN
                    IBVAL=Q(KQS+L+IWORD)
                 ELSE
                    IBVAL=IQ(KQS+L+IWORD)
                 ENDIF
                 IF(IBVAL .NE. IVAL)THEN
                     GOTO 80
                 ELSE
                     CVAR1 = ' '
                     GOTO 50
                 ENDIF
             ENDIF
             IF(CVAR(1:4).EQ.'BITS')THEN
                 READ(CVAR(5:6),'(I2)',ERR=40  )I1BIT
                 IF(I1BIT.GT.31)GOTO 40
                 READ(CVAR(7:8),'(I2)',ERR=40  )I2BIT
                 IF(I2BIT.GT.31)GOTO 40
                 IF(I2BIT.LT.I1BIT)GOTO 40
                 IBVAL = JBYT(IQ(KQS+L+IWORD),I1BIT+1,I2BIT-I1BIT+1)
                 IF(INDEX(CHOPT,'Z').NE.0)THEN
                     WRITE(CVAL,'(Z11)')IBVAL
                 ELSE
                     WRITE(CVAL,'(I11)')IBVAL
                 ENDIF
             ENDIF
         ENDIF
   40    CONTINUE
*
   50    CONTINUE
         IF(IWORD .LT. IF11)GOTO 80
         IF(CVAR .EQ. 'UNDEFIND' .AND. INDEX(CHOPT,'U').NE. 0)GOTO 80
         IF(KEEPSQ)THEN
*           generate FORTRAN code
            IF(NEWVAL .AND. CVAR.NE.'UNDEFIND')THEN
               ILC = INDXBC(CVAR,' ')
*              suppress D:, P: etc
               IFNCOL=MAX(1,INDEX(CVAR(1:ILC),':')+1)
*              get IO-char
               NCH=MIN((NW-2)*4,60)
               CLINE=' '
               CALL UHTOC(IQ(IP+3),4,CLINE,NCH)
               ICOLON=INDEX(CLINE,'IO:')
               IF(ICOLON.NE.0)THEN
*                 skip space
                  ICOLON=ICOLON+2+INDEXC(CLINE(ICOLON:),' ')
                  CHARIO=CLINE(ICOLON:ICOLON)
                  IF(CHARIO.EQ.'U')CHARIO='B'
                  IF(CHARIO.EQ.'R')CHARIO='F'
                  IOLCHA=ICOLON+INDEX(CLINE(ICOLON:),' ')-1
               ENDIF
               IF(INDEX(CHOPT,'I').NE.0)THEN
                  IF(ICOLON.NE.0)THEN
                     IF(INDEX(CHARIA,CHARIO).EQ.0)THEN
                        WRITE(*,*)'Illegal IO-char: ',CHARIO
                        CHPF=' '
                        GOTO 995
                     ENDIF
                     IF(CHARIO.EQ.CHARIS)THEN
                        NSTYP=NSTYP+1
                     ELSE
                        IF(NSTYP.NE.0)THEN
                           CALL DZDFIO(CHPF,IPCHPF,NSTYP,CHARIS)
                           IF(IPCHPF.LE.0)GOTO 995
                        ENDIF
                        NSTYP=1
                     ENDIF
                  ELSE
                     IF(NSTYP.GT.0)THEN
                        NSTYP=NSTYP+1
                     ELSE
                        WRITE(*,*)'No IO-char given yet'
                     ENDIF
                  ENDIF
*                 end of get IO-char
               ELSE
*                 if parameter statements required force Integers
                  IF(INDEX(CHOPT,'p').NE.0) CHARIO='I'
*                 data word offsets, assignments
                  ISKC=INDEXN(CHOPT)
*                 skip first ISKCC characters in data word name
                  IF(ISKC.NE.0)THEN
                     CALL DZDCTI(CHOPT(ISKC:ISKC),ISKCC)
                     IFNCOL=MIN(IFNCOL+ISKCC,ILC)
                  ENDIF
*                 prepare pre or postfix
                  ILPF = MIN(LNBLNK(CHPF),LEN(CHPFI))
                  IF(ILPF.GT.0)THEN
                     CHPFI(1:ILPF)=CHPF(1:ILPF)
                  ELSE
                     IF(INDEX(CHOPT,'=').NE.0)THEN
                        IF(IREPL.GT.0)THEN
                           CHPFI='(I)= Q(NOFF+'
                           IF(CHARIO.EQ.'I')CHPFI(5:5)='I'
                           ILPF=12
                        ELSE
                           CHPFI='= Q(NOFF+'
                           IF(CHARIO.EQ.'I')CHPFI(2:2)='I'
                           ILPF=9
                        ENDIF
                     ELSE IF((INDEX(CHOPT,'C').NE.0 .OR.
     +               INDEX(CHOPT,'H').NE.0)
     +               .AND.IREPL.GT.0)THEN
                        IF(CHREPC.EQ.' ')THEN
                           CHPFI='(MW)'
                        ELSE
                           CHPFI='('//CHREPC(1:2)//')'
                        ENDIF
                        ILPF=4
                     ENDIF
                  ENDIF
                  IF(ILPF.GT.0)THEN
                     IF(INDEX(CHOPT,'Z').EQ.0 .AND.
     +                  INDEX(CHOPT,'=').EQ.0 .AND.
     +                  INDEX(CHPFI,'(').EQ.0)THEN
                        CVARNM(1:ILPF)=CHPFI(1:ILPF)
                        CVARNM(ILPF+1:)=CVAR(IFNCOL:ILC)
                     ELSE
                        CVARNM(1:ILC-IFNCOL+1)=CVAR(IFNCOL:ILC)
                        CVARNM(ILC-IFNCOL+2:)=CHPFI(1:ILPF)
                     ENDIF
                     ILC=ILC-IFNCOL+1+ILPF
                  ELSE
                     CVARNM=CVAR(IFNCOL:ILC)
                     ILC=ILC-IFNCOL+1
                  ENDIF
                  WRITE(CVAR1,'(I8)')IWORDR
*  PN: compilation problem on sp2
*                 IFC = INDEXN(CVAR1,' ')
                  IFC = INDEXN(CVAR1)
                  IF(INDEX(CHOPT,'=').NE.0)THEN
*                    data assignments
                     IF(NKEEPS.EQ.0)THEN
                        ILC1 = INDXBC(CHBANK(1:4),' ')
                        IF(IPRKEE.LE.0)THEN
                           IPRKEE=IPRKEE+1
                           WRITE(LUC,'(A)')
     +                    'C +KEEP,'//'DAASS'//CHBANK(1:ILC1)
                        ENDIF
                     ENDIF
                     CALL DZDPLN(LUC,
     +               CVARNM(1:ILC)//CVAR1(IFC:8)//')',2)
                  ELSE IF(INDEX(CHOPT,'D').NE.0)THEN
*                    declarations, commons
                     IF(NKEEPS.EQ.0)THEN
                        ILC1 = INDXBC(CHBANK(1:4),' ')
                        IF(IPRKEE.LE.0)THEN
                           IPRKEE=IPRKEE+1
                           WRITE(LUC,'(A)')
     +                     'C +KEEP,'//'DAOFF'//CHBANK(1:ILC1)
                        ENDIF
                        IF(INDEX(CHOPT,'C').NE.0)THEN
*                          commons
                           IF(CHPFI(1:1).EQ.'(' .AND.
     +                     CHPFI(ILPF:ILPF).EQ.')')THEN
*                             parameter statement for dimension
                              CALL DZDPLN(LUC,'INTEGER ',2)
                              CHPFI(1:1)=' '
                              CALL DZDPLN(LUC,CHPFI(1:ILPF-1),1)
                              CHPFI(1:1)='('
                              CALL DZDPLN(LUC,'PARAMETER (',2)
                              CALL DZDPLN(LUC,CHPFI(2:ILPF-1)//'=',1)
                              IF(IUPERC.GT.0)THEN
                                 WRITE(CTEMP,'(I12)')IUPERC
                                 IFC=INDEXC(CTEMP,' ')
                                 CALL DZDPLN(LUC,CTEMP(IFC:)//')',1)
                              ELSE
                                 CALL DZDPLN(LUC,'??)',1)
                              ENDIF
                           ENDIF
                           CALL DZDPLN(LUC,
     +                     'COMMON/CO'//CHBANK(1:ILC1)//'/',2)
                           CALL DZDPLN(LUC,
     +                     ' '//CVARNM(1:ILC),1)
                           ILC=0
                        ENDIF
                        IF(INDEX(CHOPT,'H').NE.0)THEN
*                          hbname
                           CALL DZDPLN(LUC,
     +                     'CALL HBNAME (ID'//CHBANK(1:ILC1)//
     +                     ','''//CHBANK(1:ILC1)//''',',2)
*                          if its an array fill dimension first
                           IF(CHPFI(1:1).EQ.'(' .AND.
     +                     CHPFI(ILPF:ILPF).EQ.')')THEN
                              CALL DZDPLN(LUC,
     +                        CHPFI(2:ILPF-1)//','''//CHPFI(2:ILPF-1),1)
                              IF(IUPERC.GT.0)THEN
                                 WRITE(CTEMP,'(I12)')ILOWRC
                                 IFC=INDEXC(CTEMP,' ')
                                 CALL DZDPLN(LUC,'['//CTEMP(IFC:),1)
                                 WRITE(CTEMP,'(I12)')IUPERC
                                 IFC=INDEXC(CTEMP,' ')
                                 CALL DZDPLN(LUC,
     +                           ','//CTEMP(IFC:)//']',1)
                              ELSE
                                 CALL DZDPLN(LUC,'[0,??]',1)
                              ENDIF
                           ELSE
                              CALL DZDPLN(LUC,
     +                        CVARNM(1:ILC)//',''',1)
                              CALL DZDPLN(LUC,CVARNM(1:ILC),1)
                              ILC=0
                           ENDIF
                        ENDIF
                     ENDIF
                     IF(INDEX(CHOPT,'C').EQ.0 .AND.
     +                  INDEX(CHOPT,'H').EQ.0)THEN
                        IF(CHARIO.NE.CHARIS)THEN
                           IF(CHARIO.EQ.'F')THEN
                              CALL DZDPLN(LUC,'REAL ',2)
                           ELSE
                              CALL DZDPLN(LUC,'INTEGER ',2)
                           ENDIF
                           CALL DZDPLN(LUC,
     +                     ' '//CVARNM(1:ILC),1)
                           ILC=0
                        ENDIF
                     ENDIF
                     IF(ILC.GT.0)THEN
                        CALL DZDPLN(LUC,
     +                  ','//CVARNM(1:ILC),1)
                     ENDIF
                     IF(INDEX(CHOPT,'H').NE.0)THEN
                        IF(ICOLON.GT.1)THEN
                           CALL DZDPLN(LUC,':'//CLINE(ICOLON:IOLCHA),1)
                        ENDIF
                     ENDIF
                  ELSE
*                    PARAMETER statements
                     IF(NKEEPS.EQ.0)THEN
                        CALL DZDPLN(LUC,'PARAMETER(',2)
                     ELSE
                        CALL DZDPLN(LUC,',',1)
                     ENDIF
                     CALL DZDPLN(LUC,
     +               CVARNM(1:ILC)//'='//CVAR1(IFC:8)
     +               ,1)
                  ENDIF
                  NKEEPS = NKEEPS+1
                  CHARIS=CHARIO
               ENDIF
            ENDIF
         ELSE
            MC1 = MIN(NW,17)
            MC=MC1
            DO 60   K=3,MC1
               IF(IQ(IP+K).EQ.IILFLF)THEN
                 MC=K-1
                 GOTO 70
               ENDIF
   60       CONTINUE
   70       CONTINUE
*           examine/check value against range
            IF(INDEX(CHOPT,'E').NE.0)THEN
*              get [ , ]
               NCH=MIN((NW-2)*4,LEN(CLINE))
               CLINE=' '
               CALL UHTOC(IQ(IP+3),4,CLINE,NCH)
               IFC=INDEX(CLINE,'[')
               ILC=INDEX(CLINE,']')
               IFC=IFC+1
               ILC=ILC-1
               NC=INDEX(CLINE(IFC:ILC),',')
               IF(NC.EQ.0)NC=INDEX(CLINE(IFC:ILC),':')
               IF(IFC.EQ.1 .OR. ILC.LE.0 .OR. NC.EQ.0)THEN
                  WRITE(LUC,'(A,I6)')
     +            'No range defined for word:',IWORD
                   GOTO 80
               ENDIF
               ILC1=IFC+NC-2
               IFC2=ILC1+2
               IOUT=0
               IF(INDEX( CVAL,'.').EQ.0)THEN
*                 INTEGER
                  IF(CLINE(IFC:IFC).NE.'*')THEN
                     CALL DZDCTI(CLINE(IFC:ILC1),IVAL1)
                     IF(IQ(KQS+L+IWORD).LT.IVAL1)THEN
                        IOUT=1
                     ELSE IF(CLINE(IFC2:IFC2).NE.'*')THEN
                        CALL DZDCTI(CLINE(IFC2:ILC),IVAL2)
                        IF(IQ(KQS+L+IWORD).GT.IVAL2)IOUT=1
                     ENDIF
                  ENDIF
                  IF(IOUT.GT.0)THEN
                     WRITE(LUC,'(A,I10,A,I6,A,2(I10,A))')
     +               CVAR1,IQ(KQS+L+IWORD),' at:',IWORD,
     +               ' out of range [', IVAL1,',' ,IVAL2,']'
                  ENDIF
               ELSE
                  IF(CLINE(IFC:IFC).NE.'*')THEN
                     CALL IZCTOR(CLINE(IFC:ILC1),VAL1)
                     IF(Q(KQS+L+IWORD).LT.VAL1)THEN
                        IOUT=1
                     ELSE IF(CLINE(IFC2:IFC2).NE.'*')THEN
                        CALL IZCTOR(CLINE(IFC2:ILC),VAL2)
                        IF(Q(KQS+L+IWORD).GT.VAL2)IOUT=1
                     ENDIF
                  ENDIF
                  IF(IOUT.GT.0)THEN
                     WRITE(LUC,'(A,E10.4,A,I6,A,2(E10.4,A))')
     +               CVAR1,Q(KQS+L+IWORD),' at:',IWORD,
     +               ' out of range [', VAL1,',' ,VAL2,']'
                  ENDIF
               ENDIF
*           print the value
            ELSE IF(INDEX(CHOPT,'=').EQ.0)THEN
*               fill in a possible index
                CLOOP=CVAR1
                IF(LOOPC1.GT.0)THEN
                   CLOOP(9:9)='('
                   CLOOP(21:21)=')'
                   WRITE(CLOOP(10:14),'(I5)')LOOPC1
                   IF(LOOPC2.GT.0)THEN
                      CLOOP(15:15)=','
                      WRITE(CLOOP(16:20),'(I5)')LOOPC2
                   ENDIF
                   CLOOP=SPACES(CLOOP,0)
                ENDIF
*               indent
                NCLOOP=LENOCC(CLOOP)
                IF(NCLOOP.LE.12)THEN
                     NCLOOP=12
                ELSE IF(NCLOOP.LE.16)THEN
                     NCLOOP=16
                ENDIF
                CLINE=' '
                WRITE(CLINE,'(1X,I5)')IWORD
 
                CLINE(9:9+NCLOOP-1)=CLOOP(1:NCLOOP)
                CLINE(9+NCLOOP:9+NCLOOP+10)=CVAL
                MC=(MC-2)*4
                MC=MIN(MC,LEN(CLINE)-21-NCLOOP)
                CALL UHTOC(IQ(IP+3),4,CLINE(22+NCLOOP-LENMSK:),MC)
*               remove leading part if its MASK
                IF(LENMSK.GT.0)CLINE(1:22+NCLOOP-1)=' '
                IF(CLINE (9+NCLOOP-1:MC+35).NE.
     &             CLINSA(9+NCLOOP-1:MC+35))THEN
                   IF(NLSKIP.GT.0)THEN
                      WRITE(LUC,'(/26X,A,I5,A)')'---',NLSKIP,
     &                ' lines with same value skipped ---'
*                      IF(IDELAY.LE.0)WRITE(LUC,'(A)')' '
                      NLSKIP=0
                   ENDIF
                   IF(IDELAY.GT.0)THEN
                      WRITE(LUC,'(/11X,A)')CLINDE
                      IDELAY=IDELAY-1
                   ENDIF
                   LALILE=LENOCC(CLINE)
                   WRITE(LUC,'(/A'//NONEWL//')')CLINE(1:LALILE)
*             only if bank has more then 100 words
                   IF(NBLENG.GT.100)CLINSA(1:MC+35)=CLINE(1:MC+35)
                ELSE
                   NLSKIP=NLSKIP+1
                ENDIF
             ELSE
                IF(INDEX( CVAL,'.').EQ.0)THEN
                   WRITE(LUC,'(6X,A,A4,A,A8,A,A11)')
     +             'IQ(L',CHBANK(1:4), '+', CVAR1, ') = ', CVAL
                ELSE
                   WRITE(LUC,'(6X,A,A4,A,A8,A,A11)')
     +             'Q(L',CHBANK(1:4), '+', CVAR1, ') = ', CVAL
                ENDIF
             ENDIF
         ENDIF
         GOTO 80
      ENDIF
 
*     end of hollerith sector
 
      IF(IT .NE. 2)THEN
         WRITE(LUC,'(/A,2I9)')' Unexpected IT,NW ',IT,NW
         WRITE(LUC,'(1X,100Z8)')(IQ(IP+K),K=1,NW)
         GOTO 80
      ENDIF
 
*     start of integer sector
*     i.e. word # documented or rep level change
 
*     WRITE(*,'(1X,Z8,100I8)')(IQ(IP+K),K=1,NW)
      ICHOIC = IQ(IP+1)
*      IBIT13 = JBYT(ICHOIC,1,3)
      IDENTF = JBYT(ICHOIC,11,5)
      IF(KEEPSQ )THEN
         IF(IREPL.NE.JBYT(ICHOIC,16,3))THEN
            IF(INDEX(CHOPT,'C').NE.0)NKEEPS=0
            IF(INDEX(CHOPT,'H').NE.0)THEN
               IF(NKEEPS.GT.0)CALL DZDPLN(LUC,''')',1)
               NKEEPS=0
            ENDIF
         ENDIF
      ENDIF
 
      IREPL=JBYT(ICHOIC,16,3)
*      IESEQ  = JBYT(ICHOIC,19,1)
*      WRITE(*,*)' IBIT13, IDENTF, IREPL, IESEQ',
*     &               IBIT13, IDENTF, IREPL, IESEQ
*     remember sequence number of data word documented
      IWDOCO = IWDOC
      IF(IDENTF .EQ. ITGENQ)THEN
*        remember start of rep section in doc
         IF(IC1.GT.0 .AND. IP1 .EQ. 0)IP1 =IP
         IF(IC2.GT.0 .AND. IP2 .EQ. 0)IP2 =IP
         IWDOC = IQ(IP+2)
         GOTO 80
      ENDIF
 
*     repetition level
 
      IF(IDENTF .EQ. ITGREQ)THEN
          IF(REPEND)THEN
             REPEND=.FALSE.
          ELSE
             IF(KEEPSQ)IWORDR=0
          ENDIF
*         end of infinite rep loop (IFREPL=1), check if doc is uptodate
 
          IF(IFREPL.NE.0 .AND. NEXTRA.EQ.0 .AND. LRECOV
     &     .AND. IMBED2.EQ.0 .AND. NW.EQ.1 .AND. IREPL.EQ.0)THEN
             NTRIAL=0
             NDREST=IQ(L+KQS-1)-IWORIF
             NNREP=FLOAT(NDREST)/FLOAT(IWDOC)+0.5
74           NDEXT=NDREST-IWDOC*NNREP
             IF(NDEXT.NE.0 .AND. NNREP.GT.0)THEN
                NEXTRA=NDEXT/NNREP
                IF(NNREP*NEXTRA.EQ.NDEXT)THEN
                   IF(INDEX(CHOPT,'Q').EQ.0)
     &             CALL DZDPRW(LUC,NEXTRA+IWDOC)
                ELSE
                   IF(NTRIAL.EQ.0)THEN
                      NNREP=NNREP+1
                      NTRIAL=1
                      GOTO 74
                   ELSEIF(NTRIAL.EQ.1)THEN
                      NNREP=NNREP-2
                      NTRIAL=-1
                      GOTO 74
                   ELSE
                      NEXTRA=0
                   ENDIF
                ENDIF
             ELSE
                NEXTRA=0
             ENDIF
             IF(NEXTRA.LT.0)THEN
                 WRITE(LUC,'(/A,I5,A)')
     &           ' Ignore last',-NEXTRA,' words'
                 IWORD=IWORD+NEXTRA
                 IWORDR=IWORDR+NEXTRA
*                force new retrieval of formatted values
                 IC9=10
                 NEXTRA=-(NEXTRA+IWDOC)
             ENDIF
             IF(NEXTRA.EQ.0 .AND. NDEXT.NE.0)THEN
                   CALL DZDPRW(LUC,-1000000)
             ENDIF
          ENDIF
*     look if enough data words are documented for this section
          IF(NEXTRA.GT.0 .AND. LRECOV)THEN
             DO 75 II=IWORD+1,IWORD+NEXTRA
                CALL DZSHOW(' ',IXSTOR, L,COPTDZ//'Q',1,0,II,II)
                CVAL = CQLINE(12:22)
                IF(INDEX(CHOPT,'C').EQ.0)THEN
                   IF(INDEX(CHOPT,'Q').EQ.0)
     &             WRITE(LUC,'(/1X,I5,16X,A11,A)') II, CVAL,
     &            '  not documented'
                ELSE
                   WRITE(LUC,'(A11)')CVAL
                ENDIF
   75        CONTINUE
             IWORD=IWORD+NEXTRA
             IWORDR=IWORDR+NEXTRA
*            force new retrieval of formatted values
             IC9=10
          ENDIF
 
*
76        IWDOC = -1
 
*     end of rep level
 
          IF(NW .EQ. 1)THEN
 
             IF(IREPL .EQ. 1)THEN
*               end rep lev 2
                IF(REPATH)THEN
                   IF(IP.NE.IPDRE1)THEN
                      IF(IPRL1.LE.0)THEN
                         NVAL=-1
                         GOTO 990
                      ENDIF
                      VVAR(IPRL2)=IWORD-IPREP1
                      IPRL2=0
                      IPDRE1=IP
                      IF(NOTFIL)THEN
                         NVAL=NVAL+1
                         VVAR(NVAL)=0
                      ENDIF
                   ENDIF
                   IPREP1=IWORD
                ENDIF
                IC2 = IC2 -1
                LOOPC2=LOOPC2+1
*                IREPC=-2
                IF(IC2 .GT. 0)THEN
                    IP = IP2
                    IDENTF = ITGENQ
                    GOTO 10
                ENDIF
                LOOPC2=-1
                NEXTRA=0
                GOTO 80
             ELSE
                IF(IREPL .EQ. 0)THEN
                   IF(REPATH)THEN
*                     all done
                      IF(IP.NE.IPDRE0)THEN
                         IF(IPRL1.LE.0)THEN
                            NVAL=-1
                            GOTO 990
                         ENDIF
                         VVAR(IPRL1)=IWORD-IPREP0
                         IPDRE0=IP
                         IPRL1=0
                         IF(NOTFIL)THEN
                            NVAL=NVAL+1
                            VVAR(NVAL)=0
                         ENDIF
                      ENDIF
                      IF(.NOT.NOTFIL)GOTO 990
                      IPREP0=IWORD
                   ENDIF
                   IC1=IC1-1
                   LOOPC1=LOOPC1+1
*                   IREPC=-2
                   IF(IC1 .GT. 0)THEN
                      IF(KEEPSQ)GOTO 990
                      IP = IP1
                      IDENTF = ITGENQ
                      GOTO 10
                   ENDIF
                   LOOPC1=-1
                   NEXTRA=0
                   IMBED2=0
                   GOTO 80
                ELSE
                   WRITE(LUC,'(/A,I9)')' Illegal end of rep at',IP
                   GOTO 990
                ENDIF
             ENDIF
          ENDIF
 
* start of rep
 
          IREPC = IQ(IP+2)
 
*         return path?
 
          IF(REPATH)THEN
             NVAL=NVAL+1
*            offset from previous to start of rep
             VVAR(NVAL)= - (IWORD-IPREP0)
*            remember start of section
             IF(IREPL.EQ.2)THEN
                IPREP1=IWORD
             ELSE
                IPREP0=IWORD
             ENDIF
             NVAL=NVAL+1
             VVAR(NVAL)=4
             NVAL=NVAL+1
             VVAR(NVAL)=IREPC
             MGEVAL=MAXVAL-NVAL
          ELSE
             MGEVAL=0
          ENDIF
 
          IF(IREPC.LT.0 .AND. .NOT. KEEPSQ)THEN
*            was it given in previous data word?
             ITP = MOD(IQ(IP+NW+1),16)
             NWP = IQ(IP+NW+1)/16
             NCOP=MIN(15,NWP)*4
             IF(ITP.EQ.5)THEN
                CLINE=' '
                CALL UHTOC(IQ(IP+NW+2),4,CLINE,NCOP)
                IF(CLINE(1:2).EQ.'N:'.AND.IPOINT.GT.0)THEN
                   DO I=1,IPOINT
                      NCH=LENOCC(CPOINT(I))
                      IF(CPOINT(I)(1:NCH).EQ.CLINE(1:NCH))THEN
                         IREPC=NPOINT(I)
                         IF(LENOCC(CLINE).GT.NCH)THEN
                            IVALRC=IREPC
                            IF(REPATH)THEN
                               CALL DZDGR1
     &                         (CLINE(NCH+1:),IVALRC,IREPC,NEX,
     &                          VVAR(NVAL+1),MGEVAL,NGEVAL)
                            ELSE
                               CALL DZDGR1
     &                         (CLINE(NCH+1:),IVALRC,IREPC,NEX,
     &                          IDUMMY,0,NDUMMY)
                            ENDIF
                         ENDIF
                         GOTO 77
                      ENDIF
                   ENDDO
                ENDIF
             ENDIF
 
*            try to get rep count from variable
 
             IF(REPATH)THEN
                CALL DZDGRC(IQ(IP+NW+1),0,IVALLW,IREPC,NEXTRA,
     &          VVAR(NVAL+1),MGEVAL,NGEVAL)
                IF(NGEVAL.LE.0)THEN
                   VVAR(NVAL)=1000000
                ELSE
                   VVAR(NVAL-1)=VVAR(NVAL-1)+NGEVAL
                   NVAL=NVAL+NGEVAL
                ENDIF
             ELSE
                CALL DZDGRC(IQ(IP+NW+1),0,IVALLW,IREPC,NEXTRA,
     &          IDUMMY,0,NDUMMY)
             ENDIF
 
             IF(NEXTRA.LT.0 .AND.INDEX(CHOPT,'Q').EQ.0 .AND. LRECOV)
     &       CALL DZDPRW(LUC,NEXTRA)
             IF(NEXTRA.GT.0 .AND. LRECOV)THEN
                IF(INDEX(CHOPT,'Q').EQ.0)WRITE(*,*)
     &          ' WARNING: Assume EXTRA',NEXTRA,' words not documented'
             ENDIF
 
             IF(IREPC.EQ.0)THEN
                REPEND=.TRUE.
             ENDIF
          ENDIF
77        CONTINUE
 
          IF(REPATH)THEN
             NVAL=NVAL+1
             IF(IREPL.EQ.1)THEN
                IPRL1=NVAL
             ELSE
                IPRL2=NVAL
             ENDIF
          ENDIF
 
          IF(IREPL.EQ.1)THEN
             IP1 = 0
             LOOPC1=1
             IC1 = IREPC
*             IC1 = IQ(IP+2)
             IF(IC1 .LT. 0)THEN
                IF(IFREPL .EQ. 0)THEN
                   IF(KEEPSQ)THEN
                      IC1 = 1
                   ELSE
*                    variable (infinite)rep
                      IFREPL =1
                      IC1 = 10000000
                   ENDIF
                   IDENTF = -ITGREQ
                   IF(NEWPNT)THEN
                      IWORIF=IWORD+1
                   ELSE
                      IWORIF=IWORD
                   ENDIF
                ELSE
                   WRITE(LUC,'(/A,I9)')
     &             ' Illegal var Rep count at ',IP
                   GOTO 990
                ENDIF
             ENDIF
             GOTO 80
          ELSE
             IF(IREPL.EQ.2)THEN
                IP2 = 0
                LOOPC2=1
                IC2 = IREPC
*               flag imbedded rep level 2
                IMBED2=1
*                IC2 = IQ(IP+2)
                IF(IC2 .LT. 0)THEN
                   WRITE(LUC,'(/A,I9)')
     &             ' Illegal var Rep count at ',IP
                   GOTO 990
                ENDIF
             ELSE
                WRITE(LUC,'(/A,I9)')' Repl>2 at ',IP
                GOTO 990
             ENDIF
          ENDIF
      ENDIF
 
   80 CONTINUE
      IP = IP+NW+1
      IF(IWORD.LT.IL11 .OR. IP.LT.LDATUM)THEN
          GOTO 10
      ELSE
          GOTO 990
      ENDIF
 
   90 CONTINUE
      IF(NLSKIP.GT.0)THEN
         WRITE(LUC,'(/A,I5,A)')'       ---',NLSKIP,
     &   ' identical lines skipped ---'
         NLSKIP=0
      ELSE
         WRITE(LUC,'(/A)')' '
      ENDIF
      DO 100 IWORD=IW1,IL11
      CALL DZSHOW(' ',IXSTOR, L,COPTDZ//'Q',1,0,IWORD,IWORD)
      CVAL = CQLINE(12:22)
      IF(INDEX(CHOPT,'C').EQ.0)THEN
          WRITE(LUC,'(1X,I5,16X,A11)') IWORD, CVAL
      ELSE
          WRITE(LUC,'(A11)')CVAL
      ENDIF
  100 CONTINUE
 
  990 CONTINUE
      IF( .NOT. KEEPSQ)THEN
         IF(NLSKIP.GT.0)THEN
            WRITE(LUC,'(/A,I5,A)')'       ---',NLSKIP,
     &      ' identical lines skipped ---'
            NLSKIP=0
         ELSE
            WRITE(LUC,'(/A)')
     &     '-----------------------------------------------------------'
         ENDIF
      ENDIF
  995 CONTINUE
      IF(INDEX(CHOPT,'I').NE.0 .AND. NSTYP.GT.0)THEN
          CALL DZDFIO(CHPF,IPCHPF,NSTYP,CHARIS)
      ENDIF
      IF(KEEPSQ .AND. INDEX(CHOPT,'H').NE.0 .AND. NKEEPS.GT.0)THEN
         CALL DZDPLN(LUC,''')',1)
      ENDIF
      IF(LQBKD1.NE.0 .AND.INDEX(CHOPT,'I').EQ.0)THEN
         CALL MZDROP(0,LQBKD1,'L')
         LQBKD1=0
      ENDIF
      IQPRNT =LUNSAV
      IF (IENTRY.EQ.2) ITYYY=ITY
      END
 
*CMZ :  1.30/00 11/02/96  22.08.12  by  Pavel Nevski
*CMZU:  1.00/01 22/01/96  00.49.05  by  Sasha Vanyashin
*-- Author :
      SUBROUTINE DZIOPH (IFIRST,ILAST)
      SAVE KFOTYP
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,QEQU.
              DIMENSION  LQLUP(99), LQLORG(98),IQWIDN(97),IQWIDH(96)
     +,                  IQWNL(95), IQWNS(94), IQWND(93)
            EQUIVALENCE (LQLUP(8),  LQLORG(7), IQWIDN(6), IQWIDH(5)
     +,                  IQWNL(4),  IQWNS(3),  IQWND(2), IQ(1))
*KEEP,MZIOC.
      COMMON /MZIOC/ NWFOAV,NWFOTT,NWFODN,NWFORE,IFOCON(3)
     +,              MFOSAV(2),  JFOEND,JFOREP,JFOCUR,MFO(200)
*KEEP,ZBCDK.
      PARAMETER (MPOSAQ= 1 ,MPOSBQ= 2 ,MPOSCQ= 3 ,MPOSDQ= 4 ,MPOSEQ= 5
     X          ,MPOSFQ= 6 ,MPOSGQ= 7 ,MPOSHQ= 8 ,MPOSIQ= 9 ,MPOSJQ=10
     X          ,MPOSKQ=11, MPOSLQ=12 ,MPOSMQ=13 ,MPOSNQ=14 ,MPOSOQ=15
     X          ,MPOSPQ=16, MPOSQQ=17 ,MPOSRQ=18 ,MPOSSQ=19 ,MPOSTQ=20
     X          ,MPOSUQ=21, MPOSVQ=22 ,MPOSWQ=23 ,MPOSXQ=24 ,MPOSYQ=25
     X          ,MPOSZQ=26                                            )
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,DZC1.
      PARAMETER(NOFMTQ=0)
      PARAMETER(MSYSFQ=5,MSYSDQ=7,MSYSKQ=8,MSYSPQ=9)
 
      COMMON /DZC1/  IFLOPT(26),
     +               JDROP,LN,LS,LX,IO,NL,NS,ND,
     +               IBASE,LBASE,NDW,JDFD,JD,JTYP
 
      PARAMETER (NSTMXQ=16,NDVMXQ=20,LNULL=0,NOFLIQ=8,NCHEKQ=-7)
 
      PARAMETER (MCQSIQ=8,MCQLSQ=2,MCQLGQ=15,MCQLTQ=19,MCQLIQ=87)
      CHARACTER CQSTAK*13,CQINFO*40
      PARAMETER (NLICHQ=130,NSTCHQ=8,NDVCHQ=8,NBKCHQ=4 )
      CHARACTER CQLINE*(NLICHQ),CQMAP(10)*(NLICHQ)
      CHARACTER CQSTOR*(NSTCHQ),CQDIV*(NDVCHQ),CQID*(NBKCHQ)
      COMMON /DZC1CH/ CQSTOR,CQDIV,CQID,CQMAP,CQSTAK,CQINFO
      EQUIVALENCE (CQLINE,CQMAP)
 
      CHARACTER   CDUMMQ*(*)
      PARAMETER ( CDUMMQ = ' ' )
*KEEP,BKFOPARQ.
 
C--     Definition of the bank IO characteristic types (MZBOOK/MZLIFT)
 
C--               Undefined --> bank cannot be transported
      PARAMETER ( IFOUNQ = 0)
C--               Bit pattern
      PARAMETER ( IFOBIQ = 1)
C--               Integer
      PARAMETER ( IFOINQ = 2)
C--               Floating point
      PARAMETER ( IFOFLQ = 3)
C--               Double precision
      PARAMETER ( IFODOQ = 4)
C--               Hollerith
      PARAMETER ( IFOHOQ = 5)
C--               Self describing sector
      PARAMETER ( IFOSEQ = 7)
C--               Retrieve by name
      PARAMETER ( IFONAQ = 9)
C--               Copy from linear chain
      PARAMETER ( IFOLIQ = 11)
C--               Multiplication factor for self-describing sector
      PARAMETER ( JFOSEQ = 16)
 
*KEND.
 
      CHARACTER CHROUT*(*),CHSTAK*6,KFOTYP(0:11)*1
      CHARACTER CDWORD*20
      DOUBLE PRECISION DWORD
      INTEGER                IWORD
      REAL                         RWORD
      EQUIVALENCE     (DWORD,IWORD,RWORD)
      PARAMETER (CHROUT = 'DZIOPH')
      DATA KFOTYP /'U','B','I','F','D','H','*','S','*','N','*','L'/
 
*SEQ, Q$JBIT.
 
      CHSTAK          = CQSTAK(MCQSIQ:)
      CQSTAK(MCQSIQ:) = CHROUT
 
      CALL ZPAGE(IQPRNT,MIN((ILAST-IFIRST)/10+2,5))
      CQLINE = ' --------  DATA part of bank  --------'
      IF (IFLOPT(MPOSQQ).EQ.0) CALL DZTEXT(0,CDUMMQ,1)
 
      WRITE (CQLINE,'(1X,I7,'' /'',120X)') IFIRST
      INLINE =11
 
      JDATA  = 0
      JFOCUR = 0
      NWPRNT = 0
 
 
   10 ITYPE  = MFO(JFOCUR+1)
      IF (ITYPE.EQ.7)                                      GO TO 40
      NWSEC = MFO(JFOCUR+2)
      IF   (NWSEC)           20, 30, 60
 
   20 NWSEC = ILAST - JDATA
                                                           GO TO 60
 
   30 JDATA = JDATA + 1
      IWORD = IQ(KQS+LS+JDATA)
      NWSEC = IWORD
      IF (JDATA.GE.IFIRST) THEN
          WRITE(CQLINE(INLINE:INLINE+11),'('' *'',A1,''('', I7,'')'')')
     +     KFOTYP(MIN(ITYPE,6)),NWSEC
          NWPRNT = NWPRNT + 1
      ENDIF
                                                           GO TO 50
 
   40 JDATA = JDATA + 1
      IWORD = IQ(KQS+LS+JDATA)
      ITYPE = MOD (IWORD,16)
      NWSEC = IWORD/16
      IF (JDATA.GE.IFIRST) THEN
         WRITE(CQLINE(INLINE:INLINE+11),'('' *S('',A1,'','', I5,'')'')')
     +     KFOTYP(MIN(ITYPE,6)),NWSEC
          NWPRNT = NWPRNT + 1
      ENDIF
 
   50 IF (JDATA.GE.IFIRST) THEN
          IF (MOD(NWPRNT,10).EQ.0)  THEN
              IF (IFLOPT(MPOSQQ).NE.0)                    GO TO 999
              CALL DZTEXT(0,CDUMMQ,1)
              WRITE (CQLINE,'(1X,I7,'' /'',120X)') NWPRNT+IFIRST
              INLINE =11
          ELSE
              INLINE = INLINE + 12
          ENDIF
      ENDIF
 
      IF (ITYPE.GE.8) THEN
          ITYPE      = 0
          NWSEC      = ILAST - JDATA
          IQUEST(11) = -ITYPE
      ELSEIF (NWSEC.EQ.0) THEN
          ITYPE      = 0
                                                           GO TO 900
      ELSEIF (NWSEC.LT.0) THEN
          ITYPE      = 0
          NWSEC      = ILAST - JDATA
          IQUEST(11) = -ITYPE-32
      ENDIF
 
 
   60 IDBLE  = 0
      DO 100 I=MAX(JDATA+1,IFIRST),MIN(JDATA+NWSEC,ILAST)
          IWORD = IQ(KQS+LS+I)
          IF (IDBLE.EQ.1)           THEN
              WRITE(CQLINE(INLINE:INLINE+11),'(A,'')'')') CDWORD(10:)
              IDBLE  = 0
          ELSEIF (ITYPE.EQ.IFOHOQ)  THEN
              WRITE(CQLINE(INLINE:INLINE+11),'(7X,''"'',A4)')  IWORD
          ELSEIF (ITYPE.EQ.IFOINQ)  THEN
              WRITE(CQLINE(INLINE:INLINE+11),'(I12)')          IWORD
          ELSEIF (ITYPE.EQ.IFOFLQ)  THEN
              if (Rword.EQ.0.0) then
                 CQLINE(INLINE:INLINE+11)='  0.0  '
              else if (abs(Rword).LT.1.e-3.or.abs(Rword).GT.1.e8) then
                 WRITE(CQLINE(INLINE:INLINE+11),'(G12.4)')     RWORD
              else if (abs(Rword).LT.1) then
                 WRITE(CQLINE(INLINE:INLINE+11),'(F12.8)')     RWORD
              else
                 WRITE(CQLINE(INLINE:INLINE+15),'(G16.9)')     RWORD
                 CQLINE(INLINE+12:INLINE+15)=' '
              endif
          ELSEIF (ITYPE.EQ.IFODOQ)  THEN
              CALL UCOPY(Q(KQS+LS+I),DWORD,2)
              WRITE(CDWORD,'(D20.13)') DWORD
              WRITE(CQLINE(INLINE:INLINE+11),'('' D('',A)') CDWORD(:9)
              IDBLE  = 1
          ELSE
              WRITE(CQLINE(INLINE:INLINE+11),'(''  Z '',Z8)')  IWORD
          ENDIF
          NWPRNT = NWPRNT + 1
 
          IF (MOD(NWPRNT,10).EQ.0)  THEN
              IF (IFLOPT(MPOSQQ).NE.0)                    GO TO 999
              CALL DZTEXT(0,CDUMMQ,1)
              WRITE (CQLINE,'(1X,I7,'' /'',120X)') NWPRNT+IFIRST
              INLINE =11
          ELSE
              INLINE = INLINE + 12
          ENDIF
 
  100 CONTINUE
 
 
      JDATA = JDATA + NWSEC
 
      IF (JDATA.GE.ILAST)                                  GO TO 900
 
      IF (JDATA.LT.ILAST)   THEN
          JFOCUR = JFOCUR + 2
          IF (JFOCUR.LT.JFOEND)                            GO TO 10
          JFOCUR = JFOREP
                                                           GO TO 10
      ENDIF
 
 
  900 IF (INLINE.NE.11.AND.IFLOPT(MPOSQQ).EQ.0) CALL DZTEXT(0,CDUMMQ,1)
 
  999 CQSTAK(MCQSIQ:) = CHSTAK
      END
 
*CMZ :  1.30/00 14/02/96  21.04.12  by  Pavel Nevski
*-- Author :    Otto Schaile  14/02/96
******************************************************************************
*                                                                            *
      SUBROUTINE DZDPSC(ISTORE,LEV,CF)
*                                                                            *
* draw bank tree below LEV in store ISTORE in PostScript format into file CF *
******************************************************************************
      INTEGER LEV
      INTEGER LUNTRE, IRET
      PARAMETER (LUNTRE=65)
      CHARACTER*(*) CF
      CALL KUOPEN(LUNTRE,CF,'UNKNOWN',IRET)
      CALL IOPWK(2,LUNTRE,-111)
      CALL IDAWK(1)
      CALL IACWK(2)
      CALL RZCDIR('//RZDOC',' ')
      CALL DZDDTR(ISTORE,LEV,0,0,0,2,-111,'MPR')
      CALL IUWK(0,1)
      CALL IDAWK(2)
      CALL IACWK(1)
      CALL ICLWK(2)
      END
 
*CMZ :  1.30/00 28/05/96  23.54.26  by  Unknown
*-- Author :    Otto Schaile   14/02/96
*******************************************************************
*                                                                 *
      SUBROUTINE DZDHTM(ISTORE,L,CFLAG)
*                                                                 *
*     walk through a d/s at L and write doc in html               *
*     CFLAG  'S' one bank only                                    *
*            'T' bank tree (default)                              *
*            'N' no data words                                    *
*            'P' plain text (no hyperlinks)                       *
*                                                                 *
*******************************************************************
C+SEQ,ZUNIT.
*KEEP,ZEBQ.
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
*KEEP,MZCA, IF=QTRHOLL.
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
*KEEP,MZCB.
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
*KEND.
C++CDE,ZBCDK.         From DZEBRA
C++SEQ,DZDPRM
C++SEQ,DZDOCC.
      CHARACTER*(*) CFLAG
      CHARACTER*16 CLTOP
      INTEGER L,LN,LGO,LRET,LDOWN, IFC,ILC, IHNONE, LUN
      PARAMETER (LUN=65)
      CHARACTER*8 ANCHOR
      CHARACTER*80 CGET
      CHARACTER*4 CLINK
      CHARACTER*5 CSUFFI
      CHARACTER*16 CLDOWN
      CHARACTER*16 DZE2US
      INTEGER KEYVEC(2)
*---
      CALL MZSDIV(ISTORE,-7)
      CALL UCTOH('NONE',IHNONE,4,4)
      IF(INDEX(CFLAG,'P').EQ. 0)THEN
         CSUFFI='.html'
      ELSE
         CSUFFI='.txt'
      ENDIF
      WRITE(CLTOP,'(A4,I7.7,A)')IQ(KQS+L-4),L,CSUFFI
      CLTOP=DZE2US(CLTOP)
      OPEN(LUN,FILE=CLTOP,STATUS='UNKNOWN')
*      CALL KUOPEN(LUN,CLTOP,'UNKNOWN',IRET)
      IF(LQ(KQS+L+1).EQ.0)THEN
         CLTOP=' '
      ELSE
         WRITE(CLTOP,'(A4,I7.7,A)')
     +   IQ(KQS+LQ(KQS+L+1)-4),LQ(KQS+L+1),CSUFFI
         CLTOP=DZE2US(CLTOP)
      ENDIF
      IF(INDEX(CFLAG,'P').EQ. 0)THEN
         WRITE(LUN,'(A)')'<html>'
         WRITE(LUN,'(A)')'<head>'
         WRITE(LUN,'(A)')'<body>'
         WRITE(LUN,'(A)')'<isindex>'
         WRITE(LUN,'(A)')'</head>'
         WRITE(LUN,'(A)')'<body>'
         WRITE(LUN,'(A)')'<pre>'
         ENDIF
      LRET=-L
 20   CONTINUE
      LGO=LRET
      CALL DZDWTR(ISTORE,LGO,LRET)
      IF(LRET.NE.0)THEN
*         WRITE(*,'(A,A4,I10)')'Found ',IQ(KQS+LRET-4),LRET
         KEYVEC(1)=IQ(KQS+LRET-4)
         IF(LQ(KQS+LRET+1).GT.1)THEN
            KEYVEC(2)=IQ(KQS+LQ(KQS+LRET+1)-4)
         ELSE
            KEYVEC(2)=IHNONE
         ENDIF
         I1000=100000
         LQBKD=0
         CALL RZIN(0,LQBKD,2,KEYVEC,I1000,'D')
         IF (LQBKD .EQ. 0)THEN
            NLT = 0
            NLU = 0
            WRITE(*,'(A,A4)')'No doc for bank ',KEYVEC(1)
         ELSE
            IP0=KQSP+LQBKD+1
 
            CALL DZDGGI(IQ(IP0),'CL',' ',CGET,IFC,ILC)
            WRITE(ANCHOR,'(I8.8)')LRET
            IF(INDEX(CFLAG,'P').EQ. 0)
     +      WRITE(LUN,'(A)')'<a name="L'//ANCHOR//'"><b>'
            IF(ILC.GT.0)WRITE(LUN,'(A)')
     +      'Bank IDH '//CGET(1:4)//' '//CGET(5:ILC)
            IF(INDEX(CFLAG,'P').EQ. 0)
     +      WRITE(LUN,'(A)')'</b></a>'
            CALL DZDGGI(IQ(IP0),'AU',' ',CGET,IFC,ILC)
            IF(ILC.GT.0)WRITE(LUN,'(A,A,A)')'Author(s) ',CGET(IFC:ILC)
            CALL DZDGGI(IQ(IP0),'VE',' ',CGET,IFC,ILC)
            IF(ILC.GT.0)WRITE(LUN,'(A,A,A)')'Version  ',CGET(IFC:ILC)
            NID=IQ(KQS+LRET-5)
            WRITE(LUN,'(A,I6)')'NumId     ',NID
            NL=IQ(KQS+LRET-3)
            NS=IQ(KQS+LRET-2)
            WRITE(LUN,'(A,I6)')'Str Links ',NS
            NR=NL-NS
            WRITE(LUN,'(A,I6)')'Ref Links ',NR
            ND=IQ(KQS+LRET-1)
            WRITE(LUN,'(A,I6)')'NData     ',ND
            NIO = JBYT(IQ(KQS+LRET),19,4)
            IOFFBS = - (NIO + NL + 8 + 1)
            CALL DZDIOC(IQ(KQS+LRET+IOFFBS),CGET,ILC)
            IF(ILC.GT.0)WRITE(LUN,'(A,A,A)')'IO-Char   ',CGET(1:ILC)
 
            WRITE(LUN,'(A)')'----------  System links ----------'
            CALL UHTOC(KEYVEC(2),4,CLINK,4)
            IF(CLINK.NE.'NONE')THEN
               IF(INDEX(CFLAG,'P').EQ. 0)THEN
                  WRITE(ANCHOR,'(I8.8)')LQ(KQS+LRET+1)
*                 is it very first bank
                  IF(LRET.EQ.L)THEN
                     NCH=LNBLNK(CLTOP)
                     WRITE(LUN,'(A,A)')'Up-Link   '//
     +               '<a href="'//CLTOP(1:NCH)//'#L'//ANCHOR//'"><b>'//
     +               CLINK//'</b></a>'
                  ELSE
                     WRITE(LUN,'(A,A)')'Up-Link   '//
     +               '<a href="#L'//ANCHOR//'"><b>'//
     +               CLINK//'</b></a>'
 
                  ENDIF
               ELSE
                  WRITE(LUN,'(A,A)')'Up-Link   '//CLINK
               ENDIF
*              handle Origin link eventually
            ELSE
               WRITE(LUN,'(A,A)')'Up-Link   '//CLINK
            ENDIF
            LN=LQ(KQS+LRET)
            IF(LN.NE.0)THEN
               CALL UHTOC(IQ(KQS+LN-4),4,CLINK,4)
               IF(INDEX(CFLAG,'P').EQ. 0)THEN
                  WRITE(ANCHOR,'(I8.8)')LN
                  WRITE(LUN,'(A,A)')'Next-Link '//
     +            '<a href="#L'//ANCHOR//'"><b>'//
     +            CLINK//'</b></a>'
               ELSE
                   WRITE(LUN,'(A,A)')'Next-Link '//CLINK
               ENDIF
            ENDIF
            IF(NS.GT.0)THEN
               WRITE(LUN,'(A)')'--------- Struct links ----------'
               DO I=1,NS
                  LDOWN=LQ(KQS+LRET-I)
                  IF(LDOWN.NE.0)THEN
                     CALL UHTOC(IQ(KQS+LDOWN-4),4,CLINK,4)
                     CALL DZDGGI(IQ(IP0),'LI',CLINK,CGET,IFC,ILC)
                     IF(INDEX(CFLAG,'P').EQ. 0)THEN
                        WRITE(ANCHOR,'(I8.8)')LDOWN
                        IF(INDEX(CFLAG,'S').NE.0)THEN
                           WRITE(CLDOWN,'(A4,I7.7,A5)')
     +                     CLINK,LDOWN,'.html'
                           CLDOWN=DZE2US(CLDOWN)
                           WRITE(LUN,'(I6,A)')I,
     +                     ' <a href="'//CLDOWN//'#L'//
     +                     ANCHOR//'"><b>'//
     +                     CLINK//'</b></a> '//CGET(1:ILC)
                        ELSE
                           WRITE(LUN,'(I6,A)')I,
     +                     ' <a href="#L'//
     +                     ANCHOR//'"><b>'//
     +                     CLINK//'</b></a> '//CGET(1:ILC)
                        ENDIF
                     ELSE
                        WRITE(LUN,'(I6,A)')I,CLINK//' '//CGET(1:ILC)
                     ENDIF
                  ENDIF
               ENDDO
            ENDIF
            IF(ND.GT.0 .AND. INDEX(CFLAG,'N').EQ. 0)THEN
               CALL DZDDWD(ISTORE,LRET,' ',1,ND,LUN)
            ENDIF
            CALL MZDROP(0,LQBKD,' ')
            LQBKD=0
         ENDIF
         IF(INDEX(CFLAG,'S').EQ.0)GOTO 20
      ENDIF
      IF(INDEX(CFLAG,'P').EQ. 0)THEN
         WRITE(LUN,'(A)')'</pre>'
         WRITE(LUN,'(A)')'</body>'
         WRITE(LUN,'(A)')'</html>'
      ENDIF
  999 CONTINUE
      RETURN
      END
 
 
*CMZ :  1.30/00 14/02/96  21.11.15  by  Pavel Nevski
*-- Author :    Otto Schaile   14/02/96
**************************************************************************
*                                                                        *
       SUBROUTINE DZDWTR(ISTORE,L,LRET)
*                                                                        *
*     walk through a d/s at L, return link to the next bank in LRET      *
**************************************************************************
*KEEP,ZEBQ.
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
*KEEP,MZCA, IF=QTRHOLL.
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
*KEEP,MZCB.
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
*KEND.
      INTEGER L,LIN,LRET,JB
      INTEGER LORIG, LUP, LFROM
      SAVE    LORIG, LUP, LFROM
*---
      CALL MZSDIV(ISTORE,-7)
*     init links and return
      IF(L.LT.0)THEN
         LRET=-L
         LORIG = LRET
         LUP = LRET
         LFROM = LQ(KQS+LRET+1)
         GOTO 90
      ENDIF
*
      LIN=L
      JB = LUP - LORIG + 1
   10 CONTINUE
      NS = IQ(KQS+LUP -2)
      IF(JB .LE. NS)THEN
*        go down
         LD1 = LQ(KQS+ LIN - JB)
*        look if this link is used
         IF(LD1 .EQ. 0)THEN
            JB = JB + 1
            GOTO 10
         ENDIF
         LUP = LD1
         LORIG = LD1
         LRET = LD1
         GOTO 90
      ENDIF
 
*     look if its part of linear structure
 
      LN = LQ(KQS+LIN)
      IF(LN .NE. 0)THEN
         LUP = LN
         LORIG = LN
         LRET = LN
         GOTO 90
      ENDIF
 
*     look if it is end of a linear structure
*     i.e. origin and up link are in different banks
 
   50 CONTINUE
      LUP = LQ(KQS+LIN+1)
      LORIG = LQ(KQS+LIN+2)
*     look if back at top bank or if it would move above top bank
      IF(LUP .LE. 1 .OR. LUP .EQ. LFROM) THEN
         LRET=0
         GOTO 99
      ENDIF
      NSU = IQ(KQS+LUP-2)
      IF(LORIG .GE. LUP .OR. LORIG .LT. LUP-NSU)THEN
*        its different, step back
         LIN = LORIG
         GOTO 50
      ENDIF
*     go up
      LRET = LUP
   90 CONTINUE
      JB = LUP - LORIG + 1
      IF(JB.NE.1) THEN
         LIN=LRET
         GOTO 10
      ENDIF
   99 CONTINUE
      END
*CMZ :  1.40/05 21/08/98  17.28.58  by  Pavel Nevski
*CMZ :  1.30/00 01/04/97  18.15.21  by  Pavel Nevski
*-- Author :    Pavel Nevski   16/03/97
      SUBROUTINE ZFATAL
 
C-    FATAL PROGRAM TERMINATION
 
*KEEP,ZMACH.
      PARAMETER      (IQBITW=32, IQBITC=8, IQCHAW=4)
      COMMON /ZMACH/ NQBITW,NQBITC,NQCHAW
     +,              NQLNOR,NQLMAX,NQLPTH,NQRMAX,IQLPCT,IQNIL
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,FZCI.
      COMMON /FZCI/  LUNI,LUNNI,IXDIVI,LTEMPI,IEVFLI
     +,              MSTATI,MEDIUI,IFIFOI,IDAFOI,IACMOI,IUPAKI
     +,              IADOPI,IACTVI,INCBPI,LOGLVI,MAXREI,  ISTENI
     +,              LBPARI, L4STOI,L4STAI,L4CURI,L4ENDI
     +,              IFLAGI,NFASTI,N4SKII,N4RESI,N4DONI,N4ENDI
     +,              IOPTIE,IOPTIR,IOPTIS,IOPTIA,IOPTIT,IOPTID
     +,                     IOPTIF,IOPTIG,IOPTIH,IOPTI2(4)
     +,              IDI(2),IPILI(4),NWTXI,NWSEGI,NWTABI,NWBKI,LENTRI
     +,              NWUHCI,IOCHI(16),NWUMXI,NWUHI,NWIOI
     +,              NWRDAI,NRECAI,LUHEAI,JRETCD,JERROR,NWERR
      PARAMETER      (JAUIOC=50, JAUSEG=68, JAUEAR=130)
*KEND.
C--------------    END CDE                             --------------
*KEEP,ZFATALCH.
      DATA  INIT   / 1234321 /
*KEEP,ZFATALRE,   P=QEND.
      IF (NQINIT.EQ.INIT)    RETURN
*KEND.
 
      IF (NQERR.GT.0)              GO TO 71
      NQERR = NQERR+1
      LUN   = IQTYPE
      IF (LUN.NE.0)                GO TO 22
 
   21 LUN  = IQLOG
   22 IF (NQTRAC.EQ.0)             GO TO 31
 
C----              PRINT ZEBRA TRACE-BACK
 
      JT = NQTRAC - 2
      WRITE (LUN,9024) MQTRAC(JT+1),MQTRAC(JT+2)
 9024 FORMAT (1X/' !!!!! ZFATAL called from ',2A4)
      GO TO 28
 
   25 WRITE (LUN,9025) MQTRAC(JT+1),MQTRAC(JT+2)
 9025 FORMAT (14X,'called from ',2A4)
   28 JT = JT - 2
      IF (JT.GE.0)                 GO TO 25
      IF (NQFATA.EQ.0)             GO TO 49
      GO TO 41
 
C--                EXTERNAL CALL TO ZFATAL
 
   31 IF (NQFATA.NE.0)             GO TO 41
      WRITE (LUN,9031)
 9031 FORMAT (1X/' !!!!! ZFATAL reached.')
      GO TO 49
 
C--                ZEBRA INTERNAL CALL TO ZFATAL
 
   41 CONTINUE
      WRITE (LUN,9041) IQUEST(9),IQUEST(10),NQCASE
 9041 FORMAT (1X/' !!!!! ZFATAL reached from ',2A4,'  for Case=',I3/1X)
 
      JPOS = IQBITW - 7
 
      DO 47  JW=11,10+NQFATA
      IT = IQUEST(JW)
      J  = JBYT (IT,JPOS,8)
      IF (J.EQ.0)                  GO TO 44
      IF (J.EQ.255)                GO TO 44
 
      WRITE (LUN,9043,ERR=47)  JW,IT,IT,IT
      GO TO 47
 
   44 WRITE (LUN,9044,ERR=47)  JW,IT,IT
 9043 FORMAT (10X,'IQUEST(',I2,') = ',I9,1X,Z16,1X,A6)
 9044 FORMAT (10X,'IQUEST(',I2,') = ',I9,1X,Z16)
   47 CONTINUE
 
   49 WRITE (LUN,9049) JQSTOR,JQDIVI
 9049 FORMAT (1X/10X,'Current Store number =',I3,'  (JQDIVI=',I2,')')
 
      IF (IQVID(2).EQ.0)           GO TO 59
 
      WRITE (LUN,9051) IQVID
      WRITE (LUN,9052) (J,IQVREM(1,J),IQVREM(2,J),J=1,6)
 
 9051 FORMAT (1X/10X,'Automatic Verification Identifiers :'
     F/10X,'Current :',2X,2I11)
 9052 FORMAT (10X,'Stacked, J =',I2,' :',I6,I11,5(/22X,I2,' :',I6,I11))
 
   59 IF (LUN.NE.IQLOG)            GO TO 21
 
*PN: trying to do something, at least provide an extended diagnostoc
      CALL ZABEND (NQCASE,LQSYSR(KQT+1))
*     print *,' ==> NQCASE,NQERR after ZABEND =',NQCASE,NQERR
      JRETCD = -3
      IF (NQCASE.EQ.0) RETURN
*
      NQCASE = 0
      NQFATA = 0
 
 
C----              RECOVERY LOOP
 
   71 NQERR = NQERR + 1
      IF (NQERR.GE.4)              GO TO 79
      WRITE (IQLOG,9071)
      IF (IQTYPE.EQ.0)             GO TO 79
      IF (IQTYPE.EQ.IQLOG)         GO TO 79
      WRITE (IQTYPE,9071)
 9071 FORMAT (1X/' !!!!! break for re-entry to ZFATAL !!!!!')
   79 CONTINUE
*
* PN: regain control as in arithmetic trap
      CALL TRACEQ
*KEEP,QTOABEND.
*KEND.
      CALL ABEND
* PN: never reached, for reference only
      CALL ZPHASE(0)
      END
 
*CMZ :  1.30/00 15/04/97  17.42.11  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZINK(KEYU,ICYCLE,CHOPT)
*
************************************************************************
*
*         To find and decode KEYU,ICYCLE
* Input:
*   KEYU    Keyword vector of the information to be read
*   ICYCLE  Cycle number of the key to be read
*           ICYCLE > highest cycle number means read the highest cycle
*           ICYCLE = 0 means read the lowest cycle
*   CHOPT   Character variable specifying the options selected.
*           data structure
*             default
*                   Same as 'D' below
*             'A'   Read continuation of the previously read data structure
*                   with identifier KEYU,ICYCLE
*                   Given that option implies that the record was written with
*                   the same option by a call to RZOUT.
*             'C'   Provide   information   about   the   cycle   numbers
*                   associated with KEY.
*                   The  total number  of  cycles  and the  cycle  number
*                   identifiers of the 19 highest  cycles are returned in
*                   IQUEST(50) and IQUEST(51..89) respectively
*             'D'   Read the  Data structure  with the  (key,cycle)  pair
*                   specified.
*             'N'   Read the neighbouring. keys (i.e. those preceding and
*                   following KEY).
*                   The  key-vectors of  the previous  and  next key  are
*                   available   respectively   as   IQUEST(31..35)    and
*                   IQUEST(41..45), see below.
*             'R'   Read data into existing bank at LSUP,JBIAS
*             'S'   KEYU(1) contains the key serial number
*                   IQUEST(20)= serial number of the key in directory
*                   IQUEST(21..20+NWKEY)=KEY(1....NWKEY)
*
* Called by RZIN,RZVIN
*
*  Author  : R.Brun DD/US/PD
*  Written : 09.05.86
*  Last mod: 11.09.89
*          : 04.03.94 S.Banerjee (Change in cycle structure)
*          : 15.04.97 P.Nevski   accept both selection KEY versions
************************************************************************
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZCOUT.
      COMMON /RZCOUT/IP1,IR1,IR2,IROUT,IRLOUT,IOPTRR
C
*KEEP,RZK.
      PARAMETER (KUP=5,KPW1=7,KNCH=9,KDATEC=10,KDATEM=11,KQUOTA=12,
     +           KRUSED=13,KWUSED=14,KMEGA=15,KRZVER=16,KIRIN=17,
     +           KIROUT=18,KRLOUT=19,KIP1=20,KNFREE=22,KNSD=23,KLD=24,
     +           KLB=25,KLS=26,KLK=27,KLF=28,KLC=29,KLE=30,KNKEYS=31,
     +           KNWKEY=32,KKDES=33,KNSIZE=253,KEX=6,KNMAX=100)
C
*KEEP,RZCKEY.
      COMMON/RZCKEY/IHEAD(3),KEY(100),KEY2(100),KEYDUM(50)
C
*KEEP,RZCYCLE.
*
*     Pointers to cycle content
*
*     KLCYCL : length of cycle block (4,7)
*     KPPCYC : pointer to previous cycle
*     KFRCYC : first record number
*     KSRCYC : secord record number
*     KFLCYC : creation date/time and other stuff
*     KORCYC : offset in first record to data
*     KCNCYC : cycle number
*     KNWCYC : number of words in d/s
*     KKYCYC : key number to which this cycle belongs (only for version 1)
*     KVSCYC : version of RZ cycles structure (0, 1)
*
      INTEGER        KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
      COMMON/RZCYCLE/KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
*KEND.
      CHARACTER*(*) CHOPT
      DIMENSION KEYU(*)
      EQUIVALENCE (IOPTA,IQUEST(91)), (IOPTC,IQUEST(92))
     +,    (IOPTD,IQUEST(93)), (IOPTN,IQUEST(94)), (IOPTR,IQUEST(95))
     +,    (IOPTS,IQUEST(96))
*
*-----------------------------------------------------------------------
*
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEND.
*
      IQUEST(1)=0
      CALL UOPTC(CHOPT,'ACDNRS',IQUEST(91))
*
*           Search KEY and CYCLE
*
      LK=IQ(KQSP+LCDIR+KLK)
      NKEYS=IQ(KQSP+LCDIR+KNKEYS)
      NWKEY=IQ(KQSP+LCDIR+KNWKEY)
      IQUEST(7)=NKEYS
      IQUEST(8)=NWKEY
      IF(NKEYS.EQ.0)GO TO 90
*
      IF(IOPTS.NE.0)THEN
         IK1=KEYU(1)
         IK2=IK1
         IF(IK1.GT.NKEYS.OR.IK1.LE.0)THEN
            IQUEST(1)=1
            IQUEST(2)=IK1
            RETURN
         ENDIF
      ELSE
         IK1=1
         IK2=NKEYS
         DO 5 I=1,NWKEY
            IKDES=(I-1)/10
            IKBIT1=3*I-30*IKDES-2
            IF(JBYT(IQ(KQSP+LCDIR+KKDES+IKDES),IKBIT1,3).LT.3)THEN
               KEY(I)=KEYU(I)
            ELSE
               CALL ZHTOI(KEYU(I),KEY(I),1)
            ENDIF
   5     CONTINUE
      ENDIF
      DO 30 I=IK1,IK2
         LKC=LK+(NWKEY+1)*(I-1)
         IF(IOPTS.EQ.0)THEN
            DO 10 K=1,NWKEY
               IF(IQ(KQSP+LCDIR+LKC+K).NE.KEY(K))GO TO 30
  10        CONTINUE
         ELSE
            DO 15 K=1,NWKEY
               IF(K.LT.10)THEN
                  IKDES=(K-1)/10
                  IKBIT1=3*K-30*IKDES-2
                  IF(JBYT(IQ(KQSP+LCDIR+KKDES+IKDES),IKBIT1,3).LT.3)THEN
                     IQUEST(20+K)=IQ(KQSP+LCDIR+LKC+K)
                  ELSE
                     CALL ZITOH(IQ(KQSP+LCDIR+LKC+K),IQUEST(20+K),1)
                  ENDIF
               ENDIF
  15        CONTINUE
         ENDIF
         IQUEST(20)=I
         LCYC=IQ(KQSP+LCDIR+LKC)
         IF (KVSCYC.NE.0) THEN
            II=I
            IF (IQUEST(99).GE.96) II=IQ(KQSP+LCDIR+LKC+1)
            IF (IQ(KQSP+LCDIR+LCYC+KKYCYC).NE.II) THEN
               IQUEST(1) = 11
               GO TO 99
            ENDIF
         ENDIF
         NC=0
  20     NC=NC+1
         ICY = JBYT(IQ(KQSP+LCDIR+LCYC+KCNCYC),21,12)
         IF(ICY.EQ.ICYCLE)GO TO 50
         IF(NC.EQ.1.AND.ICYCLE.GT.ICY)GO TO 50
         IF (KVSCYC.EQ.0) THEN
            LCOLD = JBYT(IQ(KQSP+LCDIR+LCYC+KPPCYC),1,16)
         ELSE
            LCOLD = IQ(KQSP+LCDIR+LCYC+KPPCYC)
         ENDIF
         IF(LCOLD.EQ.0.AND.LCOLD.NE.LCYC.AND.ICYCLE.EQ.0)GO TO 50
         LCYC=LCOLD
         IF(LCYC.NE.0)GO TO 20
         GO TO 90
  30  CONTINUE
      GO TO 90
*
*           Cycle has been found
*           Read record descriptor
*
  50  IF (KVSCYC.EQ.0) THEN
         IR1   = JBYT(IQ(KQSP+LCDIR+LCYC+KFRCYC),17,16)
         IR2   = JBYT(IQ(KQSP+LCDIR+LCYC+KSRCYC),17,16)
         IP1   = JBYT(IQ(KQSP+LCDIR+LCYC+KORCYC), 1,16)
         NW    = JBYT(IQ(KQSP+LCDIR+LCYC+KNWCYC), 1,20)
      ELSE
         IR1   = IQ(KQSP+LCDIR+LCYC+KFRCYC)
         IR2   = IQ(KQSP+LCDIR+LCYC+KSRCYC)
         IP1   = JBYT(IQ(KQSP+LCDIR+LCYC+KORCYC), 1,20)
         NW    = IQ(KQSP+LCDIR+LCYC+KNWCYC)
      ENDIF
      N1    = NW
      IQUEST(2)=1
      IF(IR2.NE.0)IQUEST(2)=(NW-N1-1)/LREC+2
      IQUEST(3)=IR1
      IQUEST(4)=IP1
      IQUEST(5)=IR2
      IQUEST(6)=ICY
      IQUEST(12)=NW
      IQUEST(14)=IQ(KQSP+LCDIR+LCYC+1)
      IQUEST(15)=LCYC
C
C           C option given
C
      IF(IOPTC.NE.0)THEN
         IQUEST(50)=0
         LC1=LCYC
  51     IQUEST(50)=IQUEST(50)+1
         IF (KVSCYC.EQ.0) THEN
            LCOLD = JBYT(IQ(KQSP+LCDIR+LC1+KPPCYC),1,16)
         ELSE
            LCOLD = IQ(KQSP+LCDIR+LC1+KPPCYC)
         ENDIF
         IF(IQUEST(50).LE.19)THEN
            NC=IQUEST(50)
            IQUEST(50+NC)=JBYT(IQ(KQSP+LCDIR+LC1+KCNCYC),21,12)
            IQUEST(70+NC)=IQ(KQSP+LCDIR+LC1+KFLCYC)
         ENDIF
         IF(LCOLD.NE.0.AND.LCOLD.NE.LC1)THEN
            LC1=LCOLD
            GO TO 51
         ENDIF
      ENDIF
C
C           N option given. return neighbours
C
      IF(IOPTN.NE.0)THEN
         IF(I.EQ.1)THEN
            IQUEST(30)=0
         ELSE
            IQUEST(30)=NWKEY
            DO 52 J=1,NWKEY
               IF(J.LT.10)THEN
                  LKCJ=LK+(NWKEY+1)*(I-2)
                  IQUEST(30+J)=IQ(KQSP+LCDIR+LKCJ+J)
                  IKDES=(J-1)/10
                  IKBIT1=3*J-30*IKDES-2
                  IF(JBYT(IQ(KQSP+LCDIR+KKDES+IKDES),IKBIT1,3).GE.3)THEN
                     CALL ZITOH(IQUEST(30+J),IQUEST(30+J),1)
                  ENDIF
               ENDIF
  52        CONTINUE
         ENDIF
         IF(I.EQ.NKEYS)THEN
            IQUEST(40)=0
         ELSE
            IQUEST(40)=NWKEY
            DO 53 J=1,NWKEY
               IF(J.LT.10)THEN
                  LKCJ=LK+(NWKEY+1)*I
                  IQUEST(40+J)=IQ(KQSP+LCDIR+LKCJ+J)
                  IKDES=(J-1)/10
                  IKBIT1=3*J-30*IKDES-2
                  IF(JBYT(IQ(KQSP+LCDIR+KKDES+IKDES),IKBIT1,3).GE.3)THEN
                     CALL ZITOH(IQUEST(40+J),IQUEST(40+J),1)
                  ENDIF
               ENDIF
  53        CONTINUE
         ENDIF
      ENDIF
      GO TO 99
*
*           Error
*
  90  IQUEST(1)=1
      IF(IOPTN.NE.0)THEN
         IF(NKEYS.GT.0)THEN
            IQUEST(30)=NWKEY
            IQUEST(40)=NWKEY
            DO 91 J=1,NWKEY
               IF(J.GE.10)GO TO 91
               LKCJ=LK+(NWKEY+1)*(NKEYS-1)
               IQUEST(30+J)=IQ(KQSP+LCDIR+LK+J)
               IQUEST(40+J)=IQ(KQSP+LCDIR+LKCJ+J)
               IKDES=(J-1)/10
               IKBIT1=3*J-30*IKDES-2
               IF(JBYT(IQ(KQSP+LCDIR+KKDES+IKDES),IKBIT1,3).GE.3)THEN
                  CALL ZITOH(IQUEST(30+J),IQUEST(30+J),1)
                  CALL ZITOH(IQUEST(40+J),IQUEST(40+J),1)
               ENDIF
  91        CONTINUE
         ENDIF
      ENDIF
*
  99  RETURN
      END
*CMZ :  1.30/00 18/03/97  19.04.33  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZPUSH (IXDIV,LORGP,INCNLP,INCNDP,CHOPT)
 
C-    Change the size of a bank, user called
 
*KEEP,ZBCD.
      COMMON /ZBCD/  IQNUM2(11),IQLETT(26),IQNUM(10),   IQPLUS,IQMINS
     +,              IQSTAR,IQSLAS,IQOPEN,IQCLOS,IQDOLL,IQEQU, IQBLAN
     +,              IQCOMA,IQDOT, IQNUMB,IQAPO, IQEXCL,IQCOLO,IQQUOT
     +,              IQUNDE,IQCLSQ,IQAND, IQAT,  IQQUES,IQOPSQ,IQGREA
     +,              IQLESS,IQREVE,IQCIRC,IQSEMI,IQPERC,  IQLOWL(26)
     +,              IQCROP,IQVERT,IQCRCL,IQNOT, IQGRAV,  IQILEG
     +,              NQHOL0,NQHOLL(95)
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,MZCL.
      COMMON /MZCL/  NQLN,NQLS,NQNIO,NQID,NQNL,NQNS,NQND,NQIOCH(16)
     +,              LQSUP,NQBIA, NQIOSV(3)
*KEEP,MZCN.
      COMMON /MZCN/  IQLN,IQLS,IQNIO,IQID,IQNL,IQNS,IQND, IQNX,IQFOUL
*KEEP,MZCT.
      COMMON /MZCT/  MQDVGA,MQDVWI,JQSTMV,JQDVM1,JQDVM2,NQDVMV,IQFLIO
     +,              MQDVAC,NQNOOP,IQPART,NQFREE, IQTBIT,IQTVAL
     +,              IQTNMV,JQGAPM,JQGAPR,NQGAPN,NQGAP,IQGAP(5,4)
     +,              LQTA,LQTE, LQRTA,LQTC1,LQTC2,LQRTE
     +,                         LQMTA,LQMTB,LQMTE,LQMTLU,LQMTBR
     +,              LQMTC1,LQMTC2, NQFRTC,NQLIVE
*KEND.
C--------------    End CDE                             --------------
      DIMENSION    IXDIV(9),LORGP(9),INCNLP(9),INCNDP(9)
      CHARACTER    *(*) CHOPT
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZPU, 4HSH   /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEEP,Q$SBIT.
      MSBIT0 (IZW,IZP)   = AND (IZW, NOT(LSHIFT(1,IZP-1)) )
      MSBIT1 (IZW,IZP)   = OR  (IZW,     LSHIFT(1,IZP-1)  )
      MSBIT (MZ,IZW,IZP) = OR (AND (IZW, NOT(LSHIFT(1,IZP-1)) )
     +                             , LSHIFT(AND(MZ,1),IZP-1) )
*KEEP,Q$SBYT,     T=NOLIST.
*KEND.
 
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEND.
 
      IF (IXDIV(1).EQ.-7)          GO TO 12
      CALL MZSDIV (IXDIV,0)
 
   12 CALL MZCHNB (LORGP)
      LORG  = LORGP(1)
      INCNL = INCNLP(1)
      INCND = INCNDP(1)
 
      CALL UOPTC (CHOPT,'RI',IQUEST)
      IFLAG = MIN (2, IQUEST(1)+2*IQUEST(2))
 
C-         IFLAG = 0  general
C-                 1  R-educe
C-                 2  I-solated
 
      IF (IQVSTA.NE.0)       CALL ZVAUTX
      IF ((INCNL.EQ.0) .AND. (INCND.EQ.0))  GO TO 999
      LQSYSR(KQT+1) = LORG
 
C--                Find division
 
      JQDIVI = MZFDIV (-7, LORG)
      IF (JQDIVI.EQ.0)             GO TO 91
 
C--                Set bank parameters
 
      CALL MZCHLS (-7,LORG)
      IF (IQFOUL.NE.0)             GO TO 91
      NL    = IQNL
      NS    = IQNS
      ND    = IQND
      NQNIO = IQNIO
      NQID  = IQID
      NQNL = NL + INCNL
      NQNS = MIN (NS,NQNL)
      NQND = ND + INCND
      IF (NS.EQ.NL)  NQNS = NQNL
      IF (NQLOGL.GE.2)
     + WRITE (IQLOG,9032) JQSTOR,JQDIVI,LORG,NQID,INCNL,INCND,CHOPT
 9032 FORMAT (' MZPUSH-  Store/Div',2I3,' L/ID/INCNL/INCND/OPT=',
     FI9,1X,A4,2I7,1X,A)
      IF (JBIT(IQ(KQS+LORG),IQDROP).NE.0)   GO TO 92
 
C--                Check for bad parameters
 
      IF (NQND+NQNL.GE.LQSTA(KQT+21)) GO TO 93
      IF (NQND.LT.0)               GO TO 93
      IF (NQNL.GT.64000)           GO TO 93
      IF (NQNS.LT.0)               GO TO 93
 
      NLC = MIN (NL,NQNL)
      NSC = MIN (NS,NQNS)
      NDC = MIN (ND,NQND)
 
C--                Check giving up non-zero structural links
 
      IF (NQNS.GE.NS)              GO TO 36
      L  = LORG - NS - 1
      LD = LORG - NQNS
   34 L  = L + 1
      IF (L.GE.LD)                 GO TO 36
      LNZ = LQ(KQS+L)
   35 IF (LNZ.EQ.0)                GO TO 34
      IF (LQ(KQS+LNZ+2).NE.L)         GO TO 34
      IF (JBIT(IQ(KQS+LNZ),IQDROP).EQ.0)   GO TO 94
      LNZ = LQ(KQS+LNZ)
      GO TO 35
 
C--                Ready I/O characteristic
 
   36 LN = LORG - NL - NQNIO - 1
      CALL UCOPY (LQ(KQS+LN),NQIOCH,NQNIO+1)
      IF (NQNIO.NE.0)  NQIOSV(1)=0
      NQIOCH(1) = MSBYT (NQNL+NQNIO+12,NQIOCH(1),1,16)
 
C--                Re-enter after garbage collection, if any
 
   41 LE = LORG + ND + 9
 
C------            Check for short-cuts
 
      INCTT = INCNL + INCND
      INCMX = MAX (INCNL,INCND)
      INCMI = MIN (INCNL,INCND)
      CALL MZRESV
      IF (JQMODE.NE.0)             GO TO 45
 
C--                Last bank in forward division
 
      IF (LE.NE.LQEND(KQT+JQDIVI))    GO TO 51
      IF (INCNL.GE.0)              GO TO 42
      IF (IFLAG.NE.1)              GO TO 42
      IF ((NQRESV.GE.INCTT).AND.(NQRESV.LT.INCND))  GO TO 42
 
      LNN = LN - INCNL
      CALL UCOPY (NQIOCH,LQ(KQS+LNN),NQNIO+1)
      IQ(KQS+LORG-3) = NQNL
      IQ(KQS+LORG-2) = NQNS
 
      NWD = -INCNL
      CALL MZPUDX (LN,NWD)
      INCNL = 0
      INCTT = INCND
      LN    = LNN
      NL    = NQNL
 
   42 NQRESV = NQRESV - INCTT
      IF (NQRESV.LT.0)             GO TO 49
      NDELTA = INCNL
      LNEW   = LORG + NDELTA
      LQEND(KQT+JQDIVI) = LQEND(KQT+JQDIVI) + INCTT
      IF (NDELTA.EQ.0)  THEN
          IQ(KQS+LNEW-1) = NQND
          IF (IFLAG.NE.0)          GO TO 81
          IF (INCMI.GE.0)          GO TO 81
          GO TO 71
        ELSE
          CALL UCOPY2 (LQ(KQS+LORG-NLC),LQ(KQS+LNEW-NLC),NLC+NDC+9)
          IF (INCNL.GT.0)  CALL VZERO (LQ(KQS+LNEW-NQNL),INCNL)
          LQ(KQS+LN)     = NQIOCH(1)
          IQ(KQS+LNEW-3) = NQNL
          IQ(KQS+LNEW-2) = NQNS
          IQ(KQS+LNEW-1) = NQND
          GO TO 61
        ENDIF
 
C--                First bank in reverse division
 
   45 IF (LN.NE.LQSTA(KQT+JQDIVI))    GO TO 51
      IF (INCND.GE.0)              GO TO 47
      IF (IFLAG.NE.1)              GO TO 47
      IF ((NQRESV.GE.INCTT).AND.(NQRESV.LT.INCNL))  GO TO 47
      IQ(KQS+LORG-1) = NQND
 
      L   = LE + INCND
      NWD = -INCND
      CALL MZPUDX (L,NWD)
      INCND = 0
      INCTT = INCNL
      ND    = NQND
 
   47 NQRESV = NQRESV - INCTT
      IF (NQRESV.LT.0)             GO TO 49
      LNN    = LN - INCTT
      NDELTA = -INCND
      LQSTA(KQT+JQDIVI) = LNN
 
      LNEW  = LORG + NDELTA
 
      IF (NDELTA.NE.0)  CALL UCOPY2 (LQ(KQS+LORG-NLC)
     +,                              LQ(KQS+LNEW-NLC), NLC+NDC+9)
 
      IF (INCNL.GT.0)  CALL VZERO (LQ(KQS+LNEW-NQNL),INCNL)
      CALL UCOPY (NQIOCH,LQ(KQS+LNN),NQNIO+1)
 
      IQ(KQS+LNEW-3) = NQNL
      IQ(KQS+LNEW-2) = NQNS
      IQ(KQS+LNEW-1) = NQND
 
      IF (NDELTA.NE.0)             GO TO 61
      IF (IFLAG.NE.0)              GO TO 81
      IF (INCMI.GE.0)              GO TO 81
      GO TO 71
 
C--                Garbage collection
*     IQUEST(1)=0
   49 CALL MZGAR1
      IF (IQUEST(1).EQ.0 .and. IQUEST(11).LT.0) then
         print *,' ***** error in mzpush after mzgar1, iquest(1,11)=',
     >            iquest(1),iquest(11)
         IQUEST(1)=-1
         return
      ENDIF
*
      LORG = LQSYSR(KQT+1)
      LN   = LORG - NL - NQNIO - 1
      GO TO 41
 
C----              Reduction only
 
   51 IF (INCMX.GT.0)              GO TO 56
      IF (INCNL.EQ.0)              GO TO 52
 
C--                Link part
 
      LNN = LN - INCNL
      CALL UCOPY (NQIOCH,LQ(KQS+LNN),NQNIO+1)
      IQ(KQS+LORG-3)= NQNL
      IQ(KQS+LORG-2)= NQNS
 
      CALL MZPUDX (LN,-INCNL)
 
      IF (INCND.EQ.0)              GO TO 54
 
C--                Data part
 
   52 IQ(KQS+LORG-1) = NQND
      LD  = LE + INCND
      NWD = -INCND
      CALL MZPUDX (LD,NWD)
 
   54 LNEW   = LORG
      NDELTA = 0
      IF (IFLAG.NE.0)              GO TO 999
      GO TO 71
 
C------            Lift replacement bank
 
   56 J = 64*(32*NQNIO + NQNIO + 1) + 1
      NQIOCH(1) = MSBYT (J,NQIOCH(1),1,16)
 
      NQBIA = 2
      CALL MZLIFT (-7,LNEW,0,63,NQID,-1)
      LORG   = LQSYSR(KQT+1)
      NDELTA = LNEW - LORG
 
      CALL UCOPY (LQ(KQS+LORG-NLC),LQ(KQS+LNEW-NLC),NLC+4)
      CALL UCOPY (IQ(KQS+LORG),    IQ(KQS+LNEW),    NDC+1)
      IQ(KQS+LORG) = MSBIT1 (IQ(KQS+LORG),IQDROP)
 
C------            Up-date immediate links only
 
   61 IF (IFLAG.LT.2)              GO TO 71
 
C----              Update according to k-link in pushed bank
 
      K = LQ(KQS+LNEW+2)
      IF (K.EQ.0)                  GO TO 62
      IF (LQ(KQS+K).NE.LORG)          GO TO 95
      LQ(KQS+K) = LNEW
 
C----              Update according to link 0
 
   62 K = LNEW
      L = LQ(KQS+K)
      IF (L.EQ.0)                  GO TO 65
      IF (L.EQ.LORG)               GO TO 64
      LQ(KQS+L+2) = K
   63 K = L
      L = LQ(KQS+K)
      IF (L.EQ.0)                  GO TO 65
      IF (L.NE.LORG)               GO TO 63
   64 LQ(KQS+K) = LNEW
 
C----              Update k- and up-link in vertically dependent banks
 
   65 K = LNEW - NSC - 1
 
C--                          each link
   66 K = K + 1
      IF (K.GE.LNEW)               GO TO 81
      L = LQ(KQS+K)
      IF (L.EQ.0)                  GO TO 66
      IF (LQ(KQS+L+2).NE.K-NDELTA)    GO TO 66
      LQ(KQS+L+2) = K
 
C--                          and its linear structure
 
      LF = L
   68 LQ(KQS+L+1) = LNEW
      L = LQ(KQS+L)
      IF (L.EQ.LF)                 GO TO 66
      IF (L.NE.0)                  GO TO 68
      GO TO 66
 
C------            Global update of links
 
   71 MQDVGA = 0
      MQDVWI = 0
      JQSTMV = -1
      IF (NQLOGL.GE.1)
     + WRITE (IQLOG,9071) JQSTOR,JQDIVI,LORG,NQID
 9071 FORMAT (' MZPUSH-  Store/Div',2I3,' Relocation pass for L/ID ='
     F,I9,1X,A4)
 
      CALL MZTABM
 
      LMT  = LQMTA - 8
   74 LMT  = LMT + 8
      IF (LQ(LMT).NE.JQDIVI)       GO TO 74
      LQ(LMT+1) = 2
 
      CALL MZTABX
      LQMTE = LQMTLU
 
      LQ(LQTA-1) = LORG - NL - NQNIO - 1
      LQ(LQTA)   = LORG - NLC
      LQ(LQTA+1) = LORG + NDC + 9
      LQ(LQTA+2) = NDELTA
      LQ(LQTA+3) = 0
      LQ(LQTA+4) = LORG + ND + 9
 
      LQTE  = LQTA + 4
 
      CALL MZRELX
 
      NQDPSH(KQT+JQDIVI) = NQDPSH(KQT+JQDIVI) + 1
 
C------            Finished, reset LORG, clear new data words
 
   81 LORGP(1) = LNEW
      IF (INCND.GT.0)  CALL VZERO (IQ(KQS+LNEW+ND+1),INCND)
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
 
C----              Error conditions
 
   95 NQCASE = 3
      NQFATA = 1
      IQUEST(19) = K
      GO TO 92
 
   94 NQCASE = 1
      NQFATA = 2
      IQUEST(19) = L - LORG
      IQUEST(20) = LQ(KQS+L)
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 7
      IQUEST(12) = NQID
      IQUEST(13) = NS
      IQUEST(14) = NL
      IQUEST(15) = ND
      IQUEST(16) = NQNIO
      IQUEST(17) = INCNL
      IQUEST(18) = INCND
   91 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 1
      IQUEST(11) = LORG
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 17/10/97  12.42.42  by  Pavel Nevski
*CMZ :  1.30/00 19/03/97  22.28.33  by  Pavel Nevski
*-- Author :
      SUBROUTINE ZTELL (IDP,JFLP)
*KEEP,QUEST.
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
*KEND.
C-    Signal trouble situation,
C-    called from the garbage collector if not enough space
C-    may be user called with IDP > 100
      write (*,101) IDP,JFLP
 101  format(1x,20('*'),' ZEBRA problem, ZTELL called with ',2i6,
     >       1x,20('*'))
      If (IDP.eq.19 .and. JFLP.eq.0) write(*,102)
 102  format(22x,'probably there is no more space on output file')
      END
 
 
 
 
 
*CMZ :  1.30/00 19/03/97  21.37.20  by  Pavel Nevski
*-- Author :    Pavel Nevski   16/03/97
      subroutine ZFATAM  (message)
      character  message*(*)
*KEEP,MZCA, IF=QTRHOLL.
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
*KEEP,ZFATALCH.
      DATA  INIT   / 1234321 /
*KEEP,ZFATALRE,   P=QEND.
      IF (NQINIT.EQ.INIT)    RETURN
*KEND.
      print *,' ********** ZFATAM message: ',message,' **********'
      end
*CMZ :  1.40/05 08/08/97  16.00.05  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZREAD(V,N,IPC,IFORM)
*
************************************************************************
*
*           Read N words from input buffer into V
*
* Called by RZIN,RZINS,RZVIN
*
*  Author  : R.Brun, B.Holl
*  Written : 07.05.86
*  Last mod: 17.05.93 Change test on IFOCON(1) to .LT.0
*        PN: 08.08.97 When exchange format does not conside with native,
*            (-FQXISN selected), if last copied record comes from LROUT,
*            current IRIN value was not saved.
*
************************************************************************
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZCOUT.
      COMMON /RZCOUT/IP1,IR1,IR2,IROUT,IRLOUT,IOPTRR
C
*KEEP,RZK.
      PARAMETER (KUP=5,KPW1=7,KNCH=9,KDATEC=10,KDATEM=11,KQUOTA=12,
     +           KRUSED=13,KWUSED=14,KMEGA=15,KRZVER=16,KIRIN=17,
     +           KIROUT=18,KRLOUT=19,KIP1=20,KNFREE=22,KNSD=23,KLD=24,
     +           KLB=25,KLS=26,KLK=27,KLF=28,KLC=29,KLE=30,KNKEYS=31,
     +           KNWKEY=32,KKDES=33,KNSIZE=253,KEX=6,KNMAX=100)
C
*KEEP,MZIOC.
      COMMON /MZIOC/ NWFOAV,NWFOTT,NWFODN,NWFORE,IFOCON(3)
     +,              MFOSAV(2),  JFOEND,JFOREP,JFOCUR,MFO(200)
*KEND.
      DIMENSION V(*)
*
*-----------------------------------------------------------------------
*
*           Find first record
*
      NL1=LREC-IP1+1
      IF(IPC.LE.NL1)THEN
         IRS=IR1
         IS1=IP1+IPC-1
      ELSE
         NBEF=(IPC-NL1-1)/LREC
         IRS=IR2+NBEF
         IS1 =IPC-NL1-NBEF*LREC
      ENDIF
*
      LRIN=LQ(KQSP+LTOP-7)
      IF(LRIN.EQ.0)THEN
         CALL MZBOOK(JQPDVS,LRIN,LTOP,-7,'RZIN',0,0,LREC+1,2,-1)
         IQ(KQSP+LRIN-5)=IQ(KQSP+LTOP-5)
         IQ(KQSP+LTOP+KIRIN)=0
         IRIN=0
      ELSE
         IRIN=IQ(KQSP+LTOP+KIRIN)
      ENDIF
      LROUT=LQ(KQSP+LTOP-6)
      IF(LROUT.EQ.0)THEN
         IROUT=0
      ELSE
         IROUT=IQ(KQSP+LTOP+KIROUT)
      ENDIF
      IF(IRS.NE.IRIN)THEN
         IF(IRS.NE.IROUT)THEN
            CALL RZIODO(LUN,LREC,IRS,IQ(KQSP+LRIN+1),1)
            IF(IQUEST(1).NE.0)GO TO 90
            IRIN=IRS
            IQ(KQSP+LTOP+KIRIN)=IRIN
         ENDIF
      ENDIF
*
*           Read record into array V
*
      NLEFT=LREC-IS1+1
      IF(N.LE.NLEFT)THEN
         NP1=N
      ELSE
         NP1=NLEFT
      ENDIF
      IF(IRS.NE.IROUT)THEN
            CALL UCOPY(IQ(KQSP+LRIN+IS1),V,NP1)
      ELSE
            CALL UCOPY(IQ(KQSP+LROUT+IS1),V,NP1)
      ENDIF
      IF(NP1.LT.N)THEN
         NR=(N-NP1-1)/LREC+1
         IF(IRS.EQ.IR1)THEN
            IRS=IR2
         ELSE
            IRS=IRS+1
         ENDIF
         DO 60 I=1,NR
            IRin=IRS+I-1
            IF(I.NE.NR)THEN
                  CALL RZIODO(LUN,LREC,IRin,V(NP1+1),1)
                  IF(IQUEST(1).NE.0)GO TO 90
               NP1=NP1+LREC
            ELSE
               NL=N-NP1
               IF(IRIN.NE.IROUT)THEN
                  CALL RZIODO(LUN,LREC,IRIN,IQ(KQSP+LRIN+1),1)
                  IF(IQUEST(1).NE.0)GO TO 90
                  IQ(KQSP+LTOP+KIRIN)=IRIN
                     CALL UCOPY(IQ(KQSP+LRIN+1),V(NP1+1),NL)
               ELSE
                     CALL UCOPY(IQ(KQSP+LROUT+1),V(NP1+1),NL)
               ENDIF
            ENDIF
  60     CONTINUE
      ENDIF
  90  CONTINUE
  99  RETURN
      END
*CMZ :  1.40/05 20/11/97  23.58.03  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZLINK (IXSTOR,CHNAME,LAREA,LREF,LREFL)
 
C-    Set permanent link area, user called
 
*KEEP,ZBCD.
      COMMON /ZBCD/  IQNUM2(11),IQLETT(26),IQNUM(10),   IQPLUS,IQMINS
     +,              IQSTAR,IQSLAS,IQOPEN,IQCLOS,IQDOLL,IQEQU, IQBLAN
     +,              IQCOMA,IQDOT, IQNUMB,IQAPO, IQEXCL,IQCOLO,IQQUOT
     +,              IQUNDE,IQCLSQ,IQAND, IQAT,  IQQUES,IQOPSQ,IQGREA
     +,              IQLESS,IQREVE,IQCIRC,IQSEMI,IQPERC,  IQLOWL(26)
     +,              IQCROP,IQVERT,IQCRCL,IQNOT, IQGRAV,  IQILEG
     +,              NQHOL0,NQHOLL(95)
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEND.
C--------------    End CDE                             --------------
      DIMENSION    LAREA(9),LREF(9),LREFL(9),NAME(2)
      CHARACTER    *(*) CHNAME
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZLI, 4HNK   /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEEP,Q$LOCF,     T=NOLIST.
*KEND.
 
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEND.
 
*KEEP,QSTORE.
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)
***********************************************************************
*KEND.
      IF (IQVSTA.NE.0)       CALL ZVAUTX
 
C--                Check enough space in system link-area table
 
      LSYS  = LQSYSS(KQT+1)
      NWTAB = IQ(KQS+LSYS+1)
      IF (NWTAB+5.GT.IQ(KQS+LSYS-1))  THEN
          JQDIVI = JQDVSY
          CALL MZPUSH (-7,LSYS,0,100,'I')
          LQSYSS(KQT+1) = LSYS
        ENDIF
 
C--                Construct table entry
 
      LSTO = LSYS + NWTAB
*KEEP,MZLINK24.
*KEND.
      LOCAR = LOCF (LAREA(1)) - LQSTOR
      LOCR  = LOCF (LREF(1))  - LQSTOR
      LOCRL = LOCF (LREFL(1)) - LQSTOR
      NS = LOCR    - LOCAR
      NL = LOCRL+1 - LOCAR
      IF (NL.EQ.1)  THEN
          NS = NS + 1
          NL = NS
        ENDIF
 
      LOCARE = LOCAR + NL
      MODAR  = NS
 
      NAME(1) = IQBLAN
      NAME(2) = IQBLAN
      N = MIN (8, LEN(CHNAME))
      IF (N.NE.0)  CALL UCTOH (CHNAME,NAME,4,N)
 
      IQ(KQS+LSTO+1) = LOCAR
      IQ(KQS+LSTO+2) = LOCARE
      IQ(KQS+LSTO+3) = MODAR
      IQ(KQS+LSTO+4) = NAME(1)
      IQ(KQS+LSTO+5) = NAME(2)
 
C--                Range of possible values for an origin-link
 
      IQTABV(KQT+13) = MIN (IQTABV(KQT+13), LOCAR)
      IQTABV(KQT+14) = MAX (IQTABV(KQT+14), LOCARE)
 
      IF (NQLOGL.GE.0)
     +WRITE (IQLOG,9039) NAME,JQSTOR,NL,NS
 9039 FORMAT (1X/' MZLINK.  Initialize Link Area  ',2A4,'  for Store'
     F,I3,' NL/NS=',2I6)
 
 
C----              Check valid parameters
 
      IF (LOCR .LT.LOCAR)          GO TO 91
      IF (LOCRL.LT.LOCAR)          GO TO 91
      IF (NL.LT.NS)                GO TO 91
 
C------            Check overlap with existing stores
 
      KLA = KQS + LOCAR
      KLE = KQS + LOCARE
 
 
      DO 47  JSTO=1,NQSTOR+1
      IF (NQALLO(JSTO).NE.0)       GO TO 47
      JT  = NQOFFT(JSTO)
      JS  = NQOFFS(JSTO)
      JSA = JS  - IQTABV(JT+2) + 1
      JSE = JS  + LQSTA(JT+21) + 1
      JTA = JT  + LQBTIS       + 1
      JTE = JTA + NQTSYS
 
 
      IF (KLE.GT.JTA .AND. KLA.LT.JTE)    GO TO 92
      IF (KLE.GT.JSA .AND. KLA.LT.JSE)    THEN
         IF (NQLOGL.GE.0) WRITE (IQLOG,9139) CHNAME,JSTO
 9139    FORMAT (' Link area ',a,' overlaps with store #',i3)
      ENDIF
 
C--                Check overlap with existing link areas
 
      L = JS+ LQSYSS(JT+1)
      N = IQ(L+1)
      IF (N.LT.12)                 GO TO 47
 
      DO 44  J=12,N,5
      JLA = JS + IQ(L+J)
      JLE = JS + IQ(L+J+1)
 
 
      IF (KLE.GT.JLA .AND. KLA.LT.JLE)    GO TO 94
   44 CONTINUE
   47 CONTINUE
 
   61 IQ(KQS+LSYS+1) = NWTAB + 5
      CALL VZERO (LAREA,NL)
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
 
C------            Error conditions
 
   94 NQCASE = 1
      NQFATA = 3
      IQUEST(21) = IQ(L+J+3)
      IQUEST(22) = IQ(L+J+4)
      IQUEST(23) = JLA + LQSTOR
 
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 3
      IQUEST(18) = JSTO - 1
      IQUEST(19) = NQPNAM(JT+1)
      IQUEST(20) = NQPNAM(JT+2)
 
   91 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 7
      IQUEST(11) = NAME(1)
      IQUEST(12) = NAME(2)
      IQUEST(13) = LOCAR + LQSTOR
      IQUEST(14) = LOCR  + LQSTOR
      IQUEST(15) = LOCRL + LQSTOR
      IQUEST(16) = NS
      IQUEST(17) = NL
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 21/11/97  17.09.55  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZLINT (IXSTOR,CHNAME,LAREA,LREF,LREFL)
 
C-    Set permanent link area, user called
 
*KEEP,ZBCD.
      COMMON /ZBCD/  IQNUM2(11),IQLETT(26),IQNUM(10),   IQPLUS,IQMINS
     +,              IQSTAR,IQSLAS,IQOPEN,IQCLOS,IQDOLL,IQEQU, IQBLAN
     +,              IQCOMA,IQDOT, IQNUMB,IQAPO, IQEXCL,IQCOLO,IQQUOT
     +,              IQUNDE,IQCLSQ,IQAND, IQAT,  IQQUES,IQOPSQ,IQGREA
     +,              IQLESS,IQREVE,IQCIRC,IQSEMI,IQPERC,  IQLOWL(26)
     +,              IQCROP,IQVERT,IQCRCL,IQNOT, IQGRAV,  IQILEG
     +,              NQHOL0,NQHOLL(95)
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEND.
C--------------    End CDE                             --------------
      DIMENSION    LAREA(9),LREF(9),LREFL(9),NAME(2)
      CHARACTER    *(*) CHNAME
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZLI, 4HNT   /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEEP,Q$SBIT.
      MSBIT0 (IZW,IZP)   = AND (IZW, NOT(LSHIFT(1,IZP-1)) )
      MSBIT1 (IZW,IZP)   = OR  (IZW,     LSHIFT(1,IZP-1)  )
      MSBIT (MZ,IZW,IZP) = OR (AND (IZW, NOT(LSHIFT(1,IZP-1)) )
     +                             , LSHIFT(AND(MZ,1),IZP-1) )
*KEEP,Q$LOCF,     T=NOLIST.
*KEND.
 
 
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEND.
 
*KEEP,QSTORE.
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)
***********************************************************************
*KEND.
      IF (IQVSTA.NE.0)       CALL ZVAUTX
 
      LSYS  = LQSYSS(KQT+1)
      NWTAB = IQ(KQS+LSYS+1)
*KEEP,MZLINT14.
*KEND.
      LOCAR = LOCF (LAREA(1)) - LQSTOR
      JDES = LAREA(2)
      IF (JDES.LT.11)              GO TO 21
      IF (JDES.GE.NWTAB)           GO TO 21
      LSTO = LSYS + JDES
      IF (IQ(KQS+LSTO+1).NE.LOCAR)    GO TO 21
      NL = IQ(KQS+LSTO+2) - LOCAR
      IF (NQLOGL.LT.2)             GO TO 19
      WRITE (IQLOG,9018) IQ(KQS+LSTO+4),IQ(KQS+LSTO+5),JQSTOR
 9018 FORMAT (1X/' MZLINT-  Re-Init of Link Area ',2A4,'  for Store',I3)
 
C--                Set link area active
 
   19 LAREA(1) = 7
      CALL VZERO (LAREA(3),NL-2)
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
 
C------            Initialize for the first time
 
   21 IF (NWTAB+5.GT.IQ(KQS+LSYS-1))  THEN
          JQDIVI = JQDVSY
          CALL MZPUSH (-7,LSYS,0,100,'I')
          LQSYSS(KQT+1) = LSYS
        ENDIF
 
      LSTO = LSYS + NWTAB
*KEEP,MZLINT24.
*KEND.
      LOCR  = LOCF (LREF(1))  - LQSTOR
      LOCRL = LOCF (LREFL(1)) - LQSTOR
      NS = LOCR    - LOCAR
      NL = LOCRL+1 - LOCAR
      IF (NL.EQ.1)  THEN
          NS = NS + 1
          NL = NS
        ENDIF
 
      LOCARE = LOCAR + NL
      MODAR  = MSBIT1 (NS,31)
 
      NAME(1) = IQBLAN
      NAME(2) = IQBLAN
      N = MIN (8, LEN(CHNAME))
      IF (N.NE.0)  CALL UCTOH (CHNAME,NAME,4,N)
 
      IQ(KQS+LSTO+1) = LOCAR
      IQ(KQS+LSTO+2) = LOCARE
      IQ(KQS+LSTO+3) = MODAR
      IQ(KQS+LSTO+4) = NAME(1)
      IQ(KQS+LSTO+5) = NAME(2)
 
C--                Range of possible values for an origin-link
 
      IQTABV(KQT+13) = MIN (IQTABV(KQT+13), LOCAR+2)
      IQTABV(KQT+14) = MAX (IQTABV(KQT+14), LOCARE)
 
      NSM2 = NS - 2
      NLM2 = NL - 2
      IF (NQLOGL.GE.1)
     +WRITE (IQLOG,9039) NAME,JQSTOR,NLM2,NSM2
 9039 FORMAT (1X/' MZLINT.  Initialize Link Area  ',2A4,'  for Store'
     F,I3,' NL/NS=',2I6)
 
 
C----              Check valid parameters
 
      IF (LOCR .LT.LOCAR)          GO TO 91
      IF (LOCRL.LT.LOCAR)          GO TO 91
      IF (NL.LT.NS)                GO TO 91
 
C------            Check overlap with existing stores
 
      KLA = KQS + LOCAR
      KLE = KQS + LOCARE
 
 
      DO 47  JSTO=1,NQSTOR+1
      IF (NQALLO(JSTO).NE.0)       GO TO 47
      JT  = NQOFFT(JSTO)
      JS  = NQOFFS(JSTO)
      JSA = JS  - IQTABV(JT+2) + 1
      JSE = JS  + LQSTA(JT+21) + 1
      JTA = JT  + LQBTIS       + 1
      JTE = JTA + NQTSYS
 
 
      IF (KLE.GT.JTA .AND. KLA.LT.JTE)    GO TO 92
      IF (KLE.GT.JSA .AND. KLA.LT.JSE)    THEN
         IF (NQLOGL.GE.0) WRITE (IQLOG,9139) CHNAME,JSTO
 9139    FORMAT (' Link area ',a,' overlaps with store #',i3)
      ENDIF
 
C--                Check overlap with existing link areas
 
      L = JS+ LQSYSS(JT+1)
      N = IQ(L+1)
      IF (N.LT.12)                 GO TO 47
 
      DO 44  J=12,N,5
      JLA = JS + IQ(L+J)
      JLE = JS + IQ(L+J+1)
 
 
      IF (KLE.GT.JLA .AND. KLA.LT.JLE)    GO TO 94
   44 CONTINUE
   47 CONTINUE
 
C--                Success, register new link area
 
      LAREA(2) = NWTAB
      IQ(KQS+LSYS+1) = NWTAB + 5
      GO TO 19
 
C------            Error conditions
 
   94 NQCASE = 1
      NQFATA = 4
      IQUEST(21) = IQ(L+J+3)
      IQUEST(22) = IQ(L+J+4)
      IQUEST(23) = JLA + LQSTOR
      IQUEST(24) = LAREA(2)
 
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 3
      IQUEST(18) = JSTO - 1
      IQUEST(19) = NQPNAM(JT+1)
      IQUEST(20) = NQPNAM(JT+2)
 
   91 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 7
      IQUEST(11) = NAME(1)
      IQUEST(12) = NAME(2)
      IQUEST(13) = LOCAR + LQSTOR
      IQUEST(14) = LOCR  + LQSTOR
      IQUEST(15) = LOCRL + LQSTOR
      IQUEST(16) = NSM2
      IQUEST(17) = NLM2
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
*     prevent warning only
      L = MSBIT0 (NS,31)
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 25/03/98  17.51.27  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZSTOR (IXSTOR,CHNAME,CHOPT
     +,                  IFENCE,LV,LLR,LLD,LIMIT,LAST)
 
C-    Initialize new Zebra store region, user called
 
*KEEP,ZBCD.
      COMMON /ZBCD/  IQNUM2(11),IQLETT(26),IQNUM(10),   IQPLUS,IQMINS
     +,              IQSTAR,IQSLAS,IQOPEN,IQCLOS,IQDOLL,IQEQU, IQBLAN
     +,              IQCOMA,IQDOT, IQNUMB,IQAPO, IQEXCL,IQCOLO,IQQUOT
     +,              IQUNDE,IQCLSQ,IQAND, IQAT,  IQQUES,IQOPSQ,IQGREA
     +,              IQLESS,IQREVE,IQCIRC,IQSEMI,IQPERC,  IQLOWL(26)
     +,              IQCROP,IQVERT,IQCRCL,IQNOT, IQGRAV,  IQILEG
     +,              NQHOL0,NQHOLL(95)
*KEEP,ZMACH.
      PARAMETER      (IQBITW=32, IQBITC=8, IQCHAW=4)
      COMMON /ZMACH/ NQBITW,NQBITC,NQCHAW
     +,              NQLNOR,NQLMAX,NQLPTH,NQRMAX,IQLPCT,IQNIL
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,MZCWK.
      PARAMETER            (NQWKTT=2560)
      COMMON /MZCWK/ IQWKTB(NQWKTT), IQWKFZ(NQWKTT)
*KEND.
C--------------    End CDE                             --------------
      DIMENSION    IXSTOR(9),IFENCE(9)
      DIMENSION    LV(9),LLR(9),LLD(9),LIMIT(9),LAST(9)
      DIMENSION    MMSYSL(5), NAMELA(2), NAMESY(2)
      CHARACTER    *(*) CHNAME,CHOPT
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZST, 4HOR   /
      DATA  MMSYSL / 4HSYSL,0,0,101,2/
      DATA  NAMELA / 4Hsyst, 4Hem   /
      DATA  NAMESY / 4Hsyst, 4Hem   /
      DATA  NAMWSP / 4Hqwsp /
      DATA  NAMEDV / 4HQDIV /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEEP,Q$SBIT.
      MSBIT0 (IZW,IZP)   = AND (IZW, NOT(LSHIFT(1,IZP-1)) )
      MSBIT1 (IZW,IZP)   = OR  (IZW,     LSHIFT(1,IZP-1)  )
      MSBIT (MZ,IZW,IZP) = OR (AND (IZW, NOT(LSHIFT(1,IZP-1)) )
     +                             , LSHIFT(AND(MZ,1),IZP-1) )
*KEEP,Q$SHIFT.
      ISHFTL (IZW,NZB) = LSHIFT (IZW, NZB)
      ISHFTR (IZW,NZB) = lrshft (IZW, NZB)
*KEEP,Q$LOCF,     T=NOLIST.
*KEND.
 
 
C--                Clear Zebra tables on first entry
 
      IF (NQSTOR.NE.-1)            GO TO 13
      CALL VZERO (NQOFFT,32)
      LQATAB = LOCF (IQTABV(1)) - 1
      LQASTO = LOCF (LQ(1)) - 1
      LQBTIS = LQATAB - LQASTO
      LQWKTB = LOCF(IQWKTB(1)) - LQASTO
      LQWKFZ = LOCF(IQWKFZ(1)) - LQASTO
      NQTSYS = LOCF(IQDN2(20)) - LQATAB
      NQWKTB = NQWKTT
 
C-      KQFT=342 relies on LQFSTA(1) to be LQSTA(1+342) in /MZCC/
      KQFT = 342
      IF (NQLOGD.GE.-1)
     +WRITE (IQLOG,9011) LQATAB,LQATAB
 9011 FORMAT (1X/' MZSTOR.  ZEBRA table base TAB(0) in /MZCC/ at adr'
     F,I12,1X,Z11,' HEX')
   13 CONTINUE
 
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEND.
 
      CALL UOPTC (CHOPT,'Q:',IQUEST)
      LOGQ   = IQUEST(1)
      IFLSPL = IQUEST(2)
 
      JQSTOR = NQSTOR + 1
      CALL VZERO (KQT,27)
 
C--                Calculate store off-set
 
      LQSTOR = LOCF(LV(1)) - 1
      KQS    = LQSTOR - LQASTO
 
      NFEND  = (LQSTOR+1) - LOCF(IFENCE(1))
      NQFEND = NFEND
 
C--                Printing name of store
 
      NQSNAM(1) = IQBLAN
      NQSNAM(2) = IQBLAN
      N = MIN (8, LEN(CHNAME))
      IF (N.NE.0)  CALL UCTOH (CHNAME,NQSNAM,4,N)
 
C--                Set log level
 
      NQLOGL = NQLOGD
      IF (LOGQ.NE.0)  NQLOGL=-2
 
C--                Permanent links et al.
 
      NQSTRU = LOCF(LLR(1)) - (LQSTOR+1)
      NQREF  = LOCF(LLD(1)) - (LQSTOR+1)
      NQLINK = NQREF
      LQ2END = LOCF(LIMIT(1)) - LQSTOR
      NDATAT = LOCF(LAST(1))  - LQSTOR
 
C--                Calculate table off-set
 
      NDATA = NDATAT
      LOCT  = LQATAB
      IF (JQSTOR.NE.0)  THEN
          NDATA = NDATA  - NQTSYS
          NQSNAM(6) = NDATA
          LOCT  = LQSTOR + NDATA
          KQT   = LOCT   - LQATAB
          NDATA = NDATA - 4
          CALL VFILL (LQ(KQS+NDATA),10,IQNIL)
        ENDIF
 
      IF (NQLOGL.GE.-1)
     +WRITE (IQLOG,9021) JQSTOR,NQSNAM(1),NQSNAM(2)
     +,                  LQSTOR,LOCT,LQSTOR,LOCT,KQS,KQT,KQS,KQT
     +,                  NQSTRU,NQREF,LQ2END,NDATAT,NFEND
 9021 FORMAT (1X/' MZSTOR.  Initialize Store',I3,'  in ',2A4,
     F/10X,'with Store/Table at absolute adrs',2I12
     F/40X,'HEX',2(1X,Z11)/40X,'HEX',2(1X,Z11)
     F/30X,'relative adrs',2I12
     F/10X,'with',I6,' Str. in',I6,' Links in',I7,' Low words in'
     F,I8,' words.'
     F/10X,'This store has a fence of',I5,' words.')
 
C--                Set minimum sizes
 
      NSYS   =  400
      NQMINR =   40
      NWF    = 2000
      IF (JQSTOR.EQ.0)  NQMINR=164
 
C--                Check parameters valid
 
      IF (NQSTRU.LT.0)               GO TO 91
      IF (NQREF .LT.NQSTRU)          GO TO 91
      IF (NDATAT.LT.NQLINK+NWF)      GO TO 91
      IF (LQ2END.LT.NQLINK+NQMINR)   GO TO 91
      IF (NFEND .LT.1)               GO TO 92
      IF (NFEND .GE.1001)            GO TO 92
      IF (IFLSPL.EQ.1)  THEN
          IF (JQSTOR.EQ.0)           GO TO 96
          GO TO 39
        ENDIF
 
C--                Check overlapping stores
 
      IF (JQSTOR.EQ.0)             GO TO 41
      KSA = KQS - NQFEND
      KSE = KQS + NDATAT
 
      DO 36  JSTO=1,JQSTOR
      JT  = NQOFFT(JSTO)
      JS  = NQOFFS(JSTO)
      JSA = JS  - IQTABV(JT+2)
      JSE = JS  + LQSTA(JT+21)
      JTA = JT  + LQBTIS
      JTE = JTA + NQTSYS
 
      IF (KSE.GT.JTA .AND. KSA.LT.JTE     .or.
     >    KSE.GT.JSA .AND. KSA.LT.JSE)    THEN
         IF (NQLOGL.GE.0) WRITE (IQLOG,9139)
     >                    CHNAME,NQPNAM(JT+1), NQPNAM(JT+2)
 9139    FORMAT (' store ',a,' overlaps with store ',2a4)
      ENDIF
 
   36 CONTINUE
   39 IF (JQSTOR.GE.16)            GO TO 93
 
C----              Initialize divisions 1 + 2 + system
 
   41 NQOFFT(JQSTOR+1) = KQT
      NQOFFS(JQSTOR+1) = KQS
      NQALLO(JQSTOR+1) = IFLSPL
      CALL VZERO (IQTABV(KQT+1),NQTSYS)
      CALL VBLANK (IQDN1(KQT+1), 40)
      NQSTOR = NQSTOR + 1
 
      LQ(KQS+NDATA-1) = IQNIL
      LQ(KQS+NDATA)   = IQNIL
 
      NDATA = NDATA - 2
      LQSTA(KQT+21) = NDATA
 
      JQDVLL = 2
      JQDVSY = 20
      LQSTA(KQT+20)  = NDATA
      LQEND(KQT+20)  = NDATA
      NQDMAX(KQT+20) = NDATA
      IQMODE(KQT+20) = 1
      IQKIND(KQT+20) = ISHFTL (1, 23)
      IQRNO(KQT+20)  = 9437183
      IQDN1(KQT+20)  = NAMESY(1)
      IQDN2(KQT+20)  = NAMESY(2)
 
      LQSTA(KQT+2)  = NDATA - NSYS
      LQEND(KQT+2)  = LQSTA(KQT+2)
      NQDMAX(KQT+2) = NDATA
      IQMODE(KQT+2) = 1
      IQKIND(KQT+2) = MSBIT1 (2, 21)
      IQRCU(KQT+2)  = 3
      IQRTO(KQT+2)  = ISHFTL (3,20)
      IQRNO(KQT+2)  = 9437183
      IQDN1(KQT+2)  = NAMEDV
      IQDN2(KQT+2)  = IQNUM(3)
 
      LQSTA(KQT+1)  = NQLINK + 1
      LQEND(KQT+1)  = LQSTA(KQT+1)
      NQDMAX(KQT+1) = NDATA
      IQKIND(KQT+1) = MSBIT1 (1, 21)
      IQRCU(KQT+1)  = 3
      IQRTO(KQT+1)  = ISHFTL (3,20)
      IQRNO(KQT+1)  = 9437183
      IQDN1(KQT+1)  = NAMEDV
      IQDN2(KQT+1)  = IQNUM(2)
 
      CALL UCOPY (IQCUR,IQTABV(KQT+1),16)
      CALL VFILL (IFENCE,NFEND,IQNIL)
      IF (NQLINK.NE.0)  CALL VZERO (LV,NQLINK)
 
C--                Return IXSTOR
 
      IF (JQSTOR.EQ.0)  THEN
          IF (IXSTOR(1).EQ.0)      GO TO 71
        ENDIF
      IDN = ISHFTL (JQSTOR,26)
      IXSTOR(1) = IDN
 
C----              Create system link table bank
 
   71 JQDIVI = JQDVSY
      CALL MZLIFT (-7,LSYS,0,2,MMSYSL,0)
      LQSYSS(KQT+1) = LSYS
 
      NALL   = LOCF(IQTDUM(1)) - LOCF(LQSYSS(1))
      NSTR   = LOCF(LQSYSR(1)) - LOCF(LQSYSS(1))
 
      LOCAR  = LOCF (LQSYSS(KQT+1)) - LQSTOR
      LOCARE = LOCAR + NALL
 
C--                Working space
 
      IQ(KQS+LSYS+1) = 11
      IQ(KQS+LSYS+2) = 1
      IQ(KQS+LSYS+3) = 1 + NQLINK
      IQ(KQS+LSYS+4) = NQSTRU
      IQ(KQS+LSYS+5) = NAMWSP
      IQ(KQS+LSYS+6) = IQBLAN
 
C--                System link area
 
      IQ(KQS+LSYS+7) = LOCAR
      IQ(KQS+LSYS+8) = LOCARE
      IQ(KQS+LSYS+9) = NSTR
      IQ(KQS+LSYS+10)= NAMELA(1)
      IQ(KQS+LSYS+11)= NAMELA(2)
 
C--                Range of possible values for an origin-link
 
      IQTABV(KQT+13) = MIN (1, LOCAR)
      IQTABV(KQT+14) = MAX (LQSTA(KQT+21), LOCARE)
 
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
C------            Error conditions
 
   96 NQCASE = NQCASE + 3
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
   91 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 9
      IQUEST(11) = NQSNAM(1)
      IQUEST(12) = NQSNAM(2)
      IQUEST(13) = NFEND
      IQUEST(14) = NQSTRU
      IQUEST(15) = NQLINK
      IQUEST(16) = LQ2END
      IQUEST(17) = NDATAT
      IQUEST(18) = NQMINR
      IQUEST(19) = NWF
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 25/03/98  17.50.48  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZRELB
 
C-    Relocator for links in banks
 
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,MZCN.
      COMMON /MZCN/  IQLN,IQLS,IQNIO,IQID,IQNL,IQNS,IQND, IQNX,IQFOUL
*KEEP,MZCT.
      COMMON /MZCT/  MQDVGA,MQDVWI,JQSTMV,JQDVM1,JQDVM2,NQDVMV,IQFLIO
     +,              MQDVAC,NQNOOP,IQPART,NQFREE, IQTBIT,IQTVAL
     +,              IQTNMV,JQGAPM,JQGAPR,NQGAPN,NQGAP,IQGAP(5,4)
     +,              LQTA,LQTE, LQRTA,LQTC1,LQTC2,LQRTE
     +,                         LQMTA,LQMTB,LQMTE,LQMTLU,LQMTBR
     +,              LQMTC1,LQMTC2, NQFRTC,NQLIVE
*KEND.
C--------------    End CDE                             --------------
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZRE, 4HLB   /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEND.
 
 
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEND.
 
      LFIXLO = LQ(LQTA-1)
      LFIXRE = LQ(LQTA)
      LFIXHI = LQ(LQTE)
      JHIGO  = (LQTE-LQTA) / 4
      NENTR  = JHIGO - 1
 
      IF (NENTR.EQ.0)  THEN
          LADTB1 = LQ(LQTA+1)
          NRLTB2 = LQ(LQTA+2)
          IFLTB3 = LQ(LQTA+3)
        ENDIF
 
      LMRNX  = LQMTA
   12 LMR    = LMRNX
      IF (LMR.GE.LQMTE)            GO TO  999
      LMRNX  = LMRNX + 8
 
 
      IACT   = LQ(LMR+1)
      IF (IACT.LE.0)               GO TO 12
      IF (IACT.EQ.4)               GO TO 12
      LSTOP  = LQ(LMR+4)
      IF (IACT.EQ.3)               GO TO 14
      LN     = LQ(LMR+3)
      LDEAD  = LSTOP
      GO TO 19
 
   14 LSEC   = LQRTA + LQ(LMR+5) - 4
 
C------            Next bank,  check if dead group
 
   16 LSEC   = LSEC + 4
      LNX    = LQ(LSEC)
      LDEAD  = LQ(LSEC+1)
 
   17 LN = LNX
      IF (LN.GE.LSTOP)             GO TO 12
      IF (LN.EQ.LDEAD)             GO TO 16
 
C--                Next bank,  alive
 
   19 CONTINUE
 
      CALL MZCHLN (-7,LN)
      IF (IQFOUL.NE.0)             GO TO 91
      LNX = IQNX
      IF (IQND.LT.0)               GO TO 17
      LS  = IQLS
      LO  = LS + 2
      LX  = LS + 3
      L2  = LS - IQNS
      L1  = LS - IQNL
      IF   (NENTR)           66, 46, 26
 
C--------------    2 OR MORE RELOCATION INTERVALS       -------------
 
C----              Next link
 
   23 IF (L1.EQ.LO) GO TO 25
   24 LQ(KQS+L1)= 0
 
   25 L1 = L1 + 1
      IF (L1.EQ.LX)                GO TO 17
   26 LFIRST= LQ(KQS+L1)
   27 LINK  = LQ(KQS+L1)
      IF (LINK.EQ.0)               GO TO 25
 
      IF (IQFLIO.EQ.0)  THEN
          IF (LINK.LT.LFIXLO)      GO TO 25
          IF (LINK.GE.LFIXHI)      GO TO 25
          IF (LINK.LT.LFIXRE)      GO TO 23
        ELSE
          IF (LINK.LT.LFIXRE)      GO TO 24
          IF (LINK.GE.LFIXHI)      GO TO 24
        ENDIF
 
C--                Binary search in relocator table
 
      JLOW = 0
      JHI  = JHIGO
 
   29 JEX = (JHI+JLOW) / 2
      IF (JEX.EQ.JLOW)             GO TO 31
      IF (LINK.GE.LQ(LQTA+4*JEX))  GO TO 30
      JHI  = JEX
      GO TO 29
 
   30 JLOW = JEX
      GO TO 29
 
C--                Relocate
 
   31 JTB = LQTA + 4*JLOW
 
      IF (LINK.GE.LQ(JTB+1))             GO TO 33
      LQ(KQS+L1) = LINK + LQ(JTB+2)
      GO TO 25
 
C----              Link into dead area
 
   33 IF   (LQ(JTB+3))       25, 24, 34
 
C--                Bridge structural link
 
   34 IF (L1.LT.L2)                GO TO 24
      IF (LS+1-L1)           36, 24, 35
   35 CONTINUE
 
      CALL MZCHLS (-7,LINK)
      IF (IQFOUL.NE.0)             GO TO 92
      LINK = LQ(KQS+LINK)
      LQ(KQS+L1) = LINK
      IF (LINK.NE.LFIRST)          GO TO 27
      GO TO 24
 
C--                Reverse bridging of s-link
 
   36 LINK = LQ(KQS+LINK+2)
      LQ(KQS+L1) = LINK
      GO TO 27
 
C--------------    1 RELOCATION INTERVAL ONLY           -------------
 
C----              Next link
 
   43 IF (L1.EQ.LO) GO TO 45
   44 LQ(KQS+L1)= 0
 
   45 L1 = L1 + 1
      IF (L1.EQ.LX)                GO TO 17
   46 LFIRST= LQ(KQS+L1)
   47 LINK  = LQ(KQS+L1)
      IF (LINK.EQ.0)               GO TO 45
 
      IF (IQFLIO.EQ.0)  THEN
          IF (LINK.LT.LFIXLO)      GO TO 45
          IF (LINK.GE.LFIXHI)      GO TO 45
          IF (LINK.LT.LFIXRE)      GO TO 43
          IF (LINK.GE.LADTB1)      GO TO 53
        ELSE
          IF (LINK.LT.LFIXRE)      GO TO 44
          IF (LINK.GE.LADTB1)      GO TO 44
        ENDIF
 
C--                Relocate
 
      LQ(KQS+L1) = LINK + NRLTB2
      GO TO 45
 
C----              Link into dead area
 
   53 IF   (IFLTB3)           45, 44, 54
 
C--                Bridge structural link
 
   54 IF (L1.LT.L2)                GO TO 44
      IF (LS+1-L1)           56, 44, 55
   55 CONTINUE
 
      CALL MZCHLS (-7,LINK)
      IF (IQFOUL.NE.0)             GO TO 92
      LINK = LQ(KQS+LINK)
      LQ(KQS+L1) = LINK
      IF (LINK.NE.LFIRST)          GO TO 47
      GO TO 44
 
C--                Reverse bridging of s-link
 
   56 LINK = LQ(KQS+LINK+2)
      LQ(KQS+L1) = LINK
      GO TO 47
 
C--------------    NO RELOCATION INTERVAL               -------------
 
C----              Next link
 
   64 LQ(KQS+L1)= 0
 
   65 L1 = L1 + 1
      IF (L1.EQ.LX)                GO TO 17
   66 LINK  = LQ(KQS+L1)
      IF (LINK.EQ.0)               GO TO 65
 
      IF (LINK.LT.LFIXLO)          GO TO 65
      IF (LINK.GE.LFIXHI)          GO TO 65
      GO TO 64
 
C------            Error conditions
   92 NQCASE = 1
      NQFATA = 2
      LN     = LS
      IQUEST(12) = L1
      IQUEST(13) = LINK
   91 NQCASE = NQCASE + 1
      NQFATA = NQFATA + 1
      IQUEST(11) = LN
      IF (IQFLIO.NE.0)             GO TO 98
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
 
   98 IQUEST(9) = NQCASE
      IQUEST(10)= NQFATA
      NQCASE = 0
      NQFATA = 0
      IQFLIO = -7
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 06/12/97  11.36.55  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZPAW (NWORDS,CHOPT)
 
C-    Initialize the store /PAWC/ of at least 10000 words;
 
      COMMON /PAWC/  NWPAW,IXPAWC,IHBOOK,IXHIGZ,IXKU,IFENCE(5)
     +,              LMAIN, IPAW(9989)
C--------------------------------------------------------------------
      CHARACTER*(*) CHOPT
 
      NW   = abs (NWORDS)
      NW   = max (NW,100000)
      I1   = LOCF(IPAW)
      I2   = memget (NW*4+1000)/4
      LL   = max    (I2-I1,0)
      NW   = NW + LL
      KWW  = LL + 100
C
      CALL MZSTOR (IXPAWC,'/PAWC/',' ',IFENCE,LMAIN,IPAW,IPAW,
     +                                 IPAW(KWW+100),IPAW(NW-100))
      CALL MZWORK (IXPAWC,IPAW(9989),IPAW(KWW),5)
      CALL MZWORK (IXPAWC,IPAW(50),IPAW(5000),0)
c
      NWPAW  = NW
      IHBOOK = 0
      IXHIGZ = 0
      IXKU   = 0
      RETURN
      END
*CMZ :  1.40/05 05/12/97  19.43.57  by  Pavel Nevski
*-- Author :    Pavel Nevski   05/12/97
 
      SUBROUTINE MZCHNB (LIX)
      END
*CMZ :  1.40/05 06/12/97  11.43.18  by  Pavel Nevski
*-- Author :
      SUBROUTINE MZWORK (IXSTOR,DFIRST,DLAST,IFLAGP)
 
C-    Allocate working space, user called
 
C-    IFLAG = -1  reset wsp empty
C-             0  new wsp
C-             1  vary both limits, keep common links
C-             2  vary  only DLAST  limit, keep links and common data
C-             3  reset only DFIRST limit, zero all links
C-             4  vary  only DFIRST limit, keep common links
C-            >5  allocate reserve between WS and DIV1
*KEEP,ZMACH.
      PARAMETER      (IQBITW=32, IQBITC=8, IQCHAW=4)
      COMMON /ZMACH/ NQBITW,NQBITC,NQCHAW
     +,              NQLNOR,NQLMAX,NQLPTH,NQRMAX,IQLPCT,IQNIL
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,MQSYS.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEND.
      COMMON /MZCDN/ LQRSTA(20),LQREND(20)
C--------------    End CDE                             --------------
      INTEGER      DFIRST(9), DLAST(9), IFLAGP(9)
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZWO, 4HRK   /
 
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEEP,Q$LOCF,     T=NOLIST.
*KEEP,QTRACE.
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
      IF (NQTRAC.GE.41)      CALL ZFATAL
*KEEP,QSTORE.
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)
***********************************************************************
*KEND.
 
      IFLAG = IFLAGP(1)
      JSTO  = JBYT (IXSTOR,27,4)
      IF (JSTO.GT.NQSTOR) GO TO 91
 
C----              Reset empty working space
 
      NEWL  = NQREF
      NEWD  = NQREF
      IF (IFLAG.LT.0)              GO TO 71
      NEWL  = LOCF (DFIRST(1)) - (LQSTOR+1)
      NEWD  = LOCF (DLAST(1))  -  LQSTOR
 
      IF (IFLAG.GE.5)              then
         LQRSTA(JSTO+1)=NEWL
         LQREND(JSTO+1)=NEWD
         GO TO 999
      endif
 
      IF (IFLAG.GE.3)  NEWD = LQSTA(1) - 1
      IF (IFLAG.EQ.2)  NEWL = NQLINK
 
C----              Check valid parameters
 
      IF (NEWL.LT.NQREF)           GO TO 92
      IF (NEWD.LT.NEWL)            GO TO 93
      IF (IFLAG.GE.3)              GO TO 31
      IF (LQRSTA(JSTO+1).EQ.0) then
         IF (NEWD.GE.LQEND(KQT+2)) GO TO 94
      ELSE
         IF (NEWD.GE.LQRSTA(JSTO+1)) GO TO 94
      ENDIF
 
C--                Check garbage collection
 
      NQRESV = LQSTA(KQT+2) - NQMINR - NEWD
      IF (NQRESV.GT.0)             GO TO 31
      print *,' negative NQRESV force garbage collection = ',NQRESV
      LQEND(KQT+1) = LQSTA(KQT+1)
      JQDIVI = 2
      CALL MZRESV
      CALL MZGAR1
      NQRESV = LQSTA(KQT+2) - NQMINR - NEWD
      IF (NQRESV.LE.0)             GO TO 94
 
C--                Clear new links
 
   31 LA = NQREF
      IF (IFLAG.EQ.1)  LA = NQLINK
      IF (IFLAG.EQ.2)  LA = NQLINK
      IF (IFLAG.EQ.4)  LA = NQLINK
      N  = NEWL - LA
      IF (N.GT.0)  CALL VZERO (LQ(KQS+LA+1),N)
 
C----              Set new limits
 
   71 NQLINK  = NEWL
      IQTABV(KQT+5) = NQLINK
      IF (IFLAG.LT.3)  THEN
          IF (NEWD.GE.LQSTA(KQT+1)) Then
             LQSTA(KQT+1) = LQREND(JSTO+1)
             IF (LQSTA(KQT+1).EQ.0)  LQSTA(KQT+1) = NEWD + 1
             LQEND(KQT+1) = LQSTA(KQT+1)
          endif
        ENDIF
 
      IF (NQLOGL.GE.2) WRITE (IQLOG,9071) JQSTOR,IFLAG,NQLINK,NEWD
 9071 FORMAT (' MZWORK-  Store',I3,' Flag=',I2,' Last Link/Data',2I7)
 
*KEEP,QTRACE99.
  999 NQTRAC = NQTRAC - 2
*KEND.
      RETURN
 
C------            Error conditions
 
   94 NQCASE = 1
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
   91 NQCASE = NQCASE + 1
      NQFATA = 4
      IQUEST(11) = NQREF
      IQUEST(12) = NEWL
      IQUEST(13) = NEWD
      IQUEST(14) = IFLAG
*KEEP,QTOFATAL, IF=QTRHOLL.
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
      CALL ZFATAL
*KEND.
      END
*KEEP,QCARDL,     T=NOLIST.
*CMZ :  1.40/05 25/03/98  19.29.54  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZMAKE(LUNIN,CHDIR,NWKEY,CHFORM,CHTAG,NRECP,CHOPT)
*
************************************************************************
*
*           Routine to create a new RZ file
*           To use an already existing file CALL RZFILE
* Input:
*   LUNP    Logical unit number associated with  the RZ file.   A FORTRAN
*           OPEN statement must precede the call to RZFILE.
*           Starting address of the memory area which will contain the RZ
*           information ('M' option)
*   CHDIR   Character variable specifying  the name of the  top directory
*           to be associated with unit LUN.
*   NWKEY   Number of words associated to a key (maximum 5)
*   CHFORM  Character variable describing each element  of the key vector
*           'B' Bit string but not zero
*           'H' Hollerith (4 characters)
*           'I' Integer (nonzero)
*           Ex: CHFORM='IIH' for NWKEY=3 and the 2 first keys are integer
*               and the third one is Hollerith
*   CHTAG   Character array defined as CHARACTER*8 CHTAG(NWKEY).
*           Each  element of  the  array allows  the  description of  the
*           corresponding element in the key vector with a tag of up to 8
*           characters.
*   NRECP   Number of physical records for primary allocation
*   CHOPT   Character variable specifying the selected options.
*           medium
*             default
*                   Disk
*             'M'   Memory
*                   In this  case the user  must have allocated  at least
*                   NRECP*LUNP words of memory starting at address LUN.
*           mode
*             default
*                   Native mode
*             'X'   Exchange mode
*           other
*             'F'   Format NRECP records (unless 'M')
*             'C'   C I/O (unless 'M')
*                   LRECL (words) taken from IQUEST(10)
*             'O'   OLD format for Cycle information (default is NEW)
*
* Called by <USER>
*
*  Author  : R.Brun DD/US/PD
*  Written : 01.04.86
*  Last mod: 14.09.93 No longer force exchange mode for LINUX
*          : 09.03.94 S.Banerjee (Change in cycle structure)
*          : 30.01.95 J.Shiers. Permit nrecp>65000 for new format
*          : 10.12.97 P.Nevski  Default is NEW
************************************************************************
*
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZDIR.
      PARAMETER (NLPATM=100)
      COMMON /RZDIRN/NLCDIR,NLNDIR,NLPAT
      COMMON /RZDIRC/CHCDIR(NLPATM),CHNDIR(NLPATM),CHPAT(NLPATM)
      CHARACTER*16   CHNDIR,    CHCDIR,    CHPAT
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZK.
      PARAMETER (KUP=5,KPW1=7,KNCH=9,KDATEC=10,KDATEM=11,KQUOTA=12,
     +           KRUSED=13,KWUSED=14,KMEGA=15,KRZVER=16,KIRIN=17,
     +           KIROUT=18,KRLOUT=19,KIP1=20,KNFREE=22,KNSD=23,KLD=24,
     +           KLB=25,KLS=26,KLK=27,KLF=28,KLC=29,KLE=30,KNKEYS=31,
     +           KNWKEY=32,KKDES=33,KNSIZE=253,KEX=6,KNMAX=100)
C
*KEEP,RZCYCLE.
*
*     Pointers to cycle content
*
*     KLCYCL : length of cycle block (4,7)
*     KPPCYC : pointer to previous cycle
*     KFRCYC : first record number
*     KSRCYC : secord record number
*     KFLCYC : creation date/time and other stuff
*     KORCYC : offset in first record to data
*     KCNCYC : cycle number
*     KNWCYC : number of words in d/s
*     KKYCYC : key number to which this cycle belongs (only for version 1)
*     KVSCYC : version of RZ cycles structure (0, 1)
*
      INTEGER        KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
      COMMON/RZCYCLE/KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
*KEND.
      CHARACTER    CHOPT*(*),CHDIR*(*),CHFORM*(*)
      CHARACTER*16 CHTOP
      CHARACTER*(*)  CHTAG(*)
      DIMENSION    IOPTV(6),IHDIR(2)
      EQUIVALENCE (IOPTM,IOPTV(1)), (IOPTX,IOPTV(2))
     +,           (IOPTF,IOPTV(3)), (IOPTC,IOPTV(4))
     +,           (IOPTN,IOPTV(5)), (IOPTO,IOPTV(6))
*
*-----------------------------------------------------------------------
*
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEND.
      IQUEST(1)=0
      LOGLV = MIN(NQLOGD,4)
      LOGLV = MAX(LOGLV,-3)
      LUNP  = LUNIN
*
      CALL UOPTC(CHOPT,'MXFCNO',IOPTV)
      IOPTN =1-IOPTO
      IMODEX=IOPTX
      IMODEC=IOPTC
      IF(IOPTC.NE.0) LUNP = IQUEST(11)
      IMODEX=1
      IRELAT=0
*
*                Check NWKEY and NRECP
*
      IF(NWKEY.LE.0.OR.NWKEY.GT.KNMAX)THEN
         IF(LOGLV.GE.-2) WRITE(IQLOG,9010)
 9010    FORMAT(' RZMAKE. NWKEY input value is invalid')
         IQUEST(1) =1
         IQUEST(11)=NWKEY
         GO TO 99
      ENDIF
      IF(NRECP.LT.2.OR.(NRECP.GT.65000.AND.IOPTN.EQ.0))THEN
         IF(LOGLV.GE.-2) WRITE(IQLOG,9011)
 9011    FORMAT(' RZMAKE. NRECP input value is invalid')
         IQUEST(1) =1
         IQUEST(11)=NRECP
         GO TO 99
      ENDIF
*
*          Save existing material (if any)
*
      CALL RZSAVE
*
*            Find record length (as specified in the OPEN statement)
*
*          A, Memory option. LUN contains the buffer address
*                            and the value of LUNP is the block length
*
      IF(IOPTM.NE.0)THEN
         LRECP=LUNP
         IF(LRECP.LT.100.OR.LRECP.GT.10000)LRECP=1024
      ELSE
*
*          B, Standard option DISK. Use information as specified
*             in the Fortran OPEN statement
*
          IF(IOPTC.EQ.0) THEN
            INQUIRE(UNIT=LUNP,RECL=LRECB)
*
            LRECP=LRECB/4
         ELSE
*
*     Take LRECL from IQUEST(10) in case of C I/O option
*
            LRECP = IQUEST(10)
         ENDIF
      ENDIF
*
      LUN = LUNP
      IZRECL = LRECP
      IF(LUN.LE.0.AND.IOPTM.EQ.0)THEN
         IF(LOGLV.GE.-2) WRITE(IQLOG,9012)
 9012    FORMAT(' RZMAKE. LUN input value is invalid')
         IQUEST(1) =1
         IQUEST(11)=LUN
         GO TO 99
      ENDIF
      IF(LRECP.LT.50)THEN
         IF(LOGLV.GE.-2) WRITE(IQLOG,9013)
 9013    FORMAT(' RZMAKE. LRECP input value less than 50')
         IQUEST(1) =1
         IQUEST(11)=LRECP
         GO TO 99
      ENDIF
      IF(LOGLV.GE.0) WRITE(IQLOG,9014) LUNP,LRECP,CHOPT
 9014 FORMAT(' RZMAKE. Unit ',I6,' Initializing with LREC=',I6,
     +', OPT= ',A)
      CALL MZSDIV (0,-7)
*
*           Check if LUN not already defined
*
      LRZ=LQRS
  10  IF(LRZ.NE.0)THEN
         IF(IQ(KQSP+LRZ-5).EQ.LUN)THEN
            IF(LOGLV.GE.-2) WRITE(IQLOG,9015)
 9015       FORMAT(' RZMAKE. Logical unit number already in use')
            IQUEST(1) =1
            IQUEST(11)=LUN
            GO TO 99
         ELSE
            LRZ=LQ(KQSP+LRZ)
            GO TO 10
         ENDIF
      ENDIF
*
*            First call to RZMAKE, create link area
*
      IF(LQRS.EQ.0)THEN
         CALL MZLINK(JQPDVS,'RZCL',LTOP,LTOP,LFROM)
         CALL MZBOOK(JQPDVS,LRZ0,LQRS,1,'RZ0 ',2,2,36,2,0)
         IQ(KQSP+LRZ0-5)=0
         ISAVE = 1
         NHPWD = 0
         CALL VBLANK(IHPWD,2)
      ENDIF
      NCHD  = LEN(CHDIR)
      IF(NCHD.GT.16)NCHD=16
      CHTOP = CHDIR(1:NCHD)
*
*            Create control bank
*
      IDTIME=0
      CALL RZDATE(IDTIME,IDATE,ITIME,2)
      KTAGS = KKDES+(NWKEY-1)/10+1
      NREC  = NRECP
      LREC  = LRECP
      NWREC = (NREC-1)/32 +1
      NW    = 50+NWREC
      NRD   = (NW-1)/LREC +1
      NWL   = NRD*LREC
      LD    = KTAGS+2*NWKEY
      LB    = LD+NRD+1
      LS    = LB+3+NWREC
      LK    = LS
      LF    = LS
*
      CALL MZBOOK (JQPDVS,LTOP,LQRS,1,'RZ  ',10,9,NWL,2,0)
*
*            Disk or memory
*
      IF(IOPTM.EQ.0)THEN
         IQ(KQSP+LTOP-5) = LUN
*
*            C I/O?
         IF(IOPTC.NE.0) CALL SBIT1(IQ(KQSP+LTOP),5)
      ELSE
         NMEM=IQ(KQSP+LRZ0)+1
         IQ(KQSP+LRZ0)=NMEM
         IQ(KQSP+LTOP-5)=-NMEM
         IF(2*NMEM.GT.IQ(KQSP+LRZ0-1))THEN
            CALL MZPUSH(JQPDVS,LRZ0,0,10,'I')
         ENDIF
         IQ(KQSP+LRZ0+2*NMEM-1)=LOCF(LUNP)-LOCF(IQ(1))+1
         IQ(KQSP+LRZ0+2*NMEM  )=LRECP
         LUN=-NMEM
      ENDIF
*
*            Pre-format file
*
      IF((IOPTF.NE.0).AND.(IOPTM.EQ.0))THEN
         DO 100 I=2,NRECP
  100    CALL RZIODO(LUN,LREC,I,IQ(KQSP+LTOP+1),2)
         IF(IQUEST(1).NE.0)THEN
            IF(LOGLV.GE.-1) WRITE(IQLOG,1000) I-1
 1000       FORMAT(' RZMAKE. Could only pre-format',I6,' records')
            IQUEST(1)=0
         ENDIF
      ENDIF
*
*            Write empty record for locks
*
      CALL RZIODO(LUN,LREC,1,IQ(KQSP+LTOP+1),2)
      IF(IQUEST(1).NE.0) GO TO 99
*
*            Build top-directory parameters
*
      CALL SBIT1(IQ(KQSP+LTOP),2)
      CALL VBLANK(IQ(KQSP+LTOP+1),4)
      CALL UCTOH(CHDIR,IQ(KQSP+LTOP+1),4,NCHD)
      CALL ZHTOI(IQ(KQSP+LTOP+1),IQ(KQSP+LTOP+1),4)
*
      NHPWD = 0
      CALL VBLANK(IHPWD,2)
      CALL UCOPY(IHPWD,IQ(KQSP+LTOP+KPW1),2)
      IQ(KQSP+LTOP+KPW1+2) = NCHD
      IF(IMODEX.GT.0)THEN
         CALL SBIT1(IQ(KQSP+LTOP+KPW1+2),12)
      ENDIF
      IQ(KQSP+LTOP+KDATEC) = IDTIME
      IQ(KQSP+LTOP+KDATEM) = IDTIME
      IQ(KQSP+LTOP+KQUOTA) = NREC
      IQ(KQSP+LTOP+KRUSED) = NRD
      IQ(KQSP+LTOP+KWUSED) = NWL
      IF (IOPTN.NE.0) THEN
        WRITE(IQLOG,7001) CHDIR
 7001   FORMAT(10x,'RZMAKE. new RZ format selected for ',a)
*     +        10x,'This file will not be readable with versions',
*     +            ' of RZ prior to release 94B')
        IQ(KQSP+LTOP+KRZVER) = 1
      ELSE
        WRITE(IQLOG,7007)
 7007 FORMAT(10x,'RZMAKE. OLD RZ format selected for ',a/,
     +       10x,'This file will have the limit on the number of',
     +           ' blocks < 64 K')
        IQ(KQSP+LTOP+KRZVER) = 0
      ENDIF
      IQ(KQSP+LTOP+KIP1)   = 2
      IQ(KQSP+LTOP+KNFREE) = NWL-LF
      IQ(KQSP+LTOP+KLD)    = LD
      IQ(KQSP+LTOP+KLB)    = LB
      IQ(KQSP+LTOP+KLS)    = LS
      IQ(KQSP+LTOP+KLK)    = LK
      IQ(KQSP+LTOP+KLF)    = LF
      IQ(KQSP+LTOP+KLC)    = NWL+1
      IQ(KQSP+LTOP+KLE)    = NWL
      IQ(KQSP+LTOP+KNWKEY) = NWKEY
      IQ(KQSP+LTOP+LD)     = NRD
      IQ(KQSP+LTOP+LB)     = NWREC
      IQ(KQSP+LTOP+LB+1)   = LREC
      IQ(KQSP+LTOP+LB+2)   = IDTIME
*
      NCHF=LEN(CHFORM)
      NCH =LEN(CHTAG(1))
      IF(NCH.GT.8)NCH=8
      DO 20 I=1,NWKEY
         IF(NCH.LT.8)CALL VBLANK(IHDIR,2)
         CALL UCTOH(CHTAG(I),IHDIR,4,NCH)
         CALL UCOPY(IHDIR,IQ(KQSP+LTOP+KTAGS+2*(I-1)),2)
         IFORM=2
         IF(I.LE.NCHF)THEN
            IF(CHFORM(I:I).EQ.'B')IFORM=1
            IF(CHFORM(I:I).EQ.'H')IFORM=3
            IF(CHFORM(I:I).EQ.'A')IFORM=4
         ENDIF
         IKDES=(I-1)/10
         IKBIT1=3*I-30*IKDES-2
         CALL SBYT(IFORM,IQ(KQSP+LTOP+KKDES+IKDES),IKBIT1,3)
  20  CONTINUE
      CALL ZHTOI(IQ(KQSP+LTOP+KTAGS),IQ(KQSP+LTOP+KTAGS),2*NWKEY)
      DO 30 I=1,NRD
         IQ(KQSP+LTOP+LD+I)=I+1
         CALL SBIT1(IQ(KQSP+LTOP+LB+3),I+1)
  30  CONTINUE
*
*            Store default LOG level
*
      LOGL = LOGLV + 3
      CALL SBYT(LOGL,IQ(KQSP+LTOP),15,3)
      CALL RZVCYC(LTOP)
*
*            Allocate free records
*
      CALL MZBOOK(JQPDVS,LFREE,LTOP,-2,'RZFR',0,0,3,2,0)
      IQ(KQSP+LFREE-5)=LUN
      IQ(KQSP+LFREE+1)=1
      IQ(KQSP+LFREE+2)=NRD+2
      IQ(KQSP+LFREE+3)=NREC
*
*            Allocate space for used records
*
      CALL MZBOOK(JQPDVS,LUSED,LTOP,-3,'RZUS',0,0,21,2,0)
*
      IQ(KQSP+LUSED-5)=LUN
      LRIN  = 0
      LPURG = 0
      LROUT = 0
      LCDIR = LTOP
      NLCDIR= 1
      NLNDIR= 1
      NLPAT = 1
      CHCDIR(1)=CHTOP
      CHNDIR(1)=CHTOP
      IQUEST(1)=0
*
  99  RETURN
      END
*CMZ :  1.40/05 18/03/98  17.12.00  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZFILE(LUNIN,CHDIR,CHOPT)
*
************************************************************************
*
*           Routine to access an already existing RZ file
*           To create a new RZ file routine RZMAKE should be used
* Input:
*   LUNP    Logical unit number associated with  the RZ file.   A FORTRAN
*           OPEN statement must precede the call to RZFILE.
*           Starting address of the memory area which will contain the RZ
*           information ('M' option)
*   CHDIR   Character variable specifying  the name of the  top directory
*           to be associated with unit LUN.
*   CHOPT   Character variable specifying the selected options.
*           medium
*          default
*                   Disk
*             'M'   Memory mode
*                   In this case space has already been allocated starting
*                   at address LUNP.
*           other
*             'U'   UPDATE mode  default is READ mode only
*             'S'   SHARED mode  default is exclusive access
*             '1'   UPDATE mode  with only one user (no LOCKs required)
*             'L'   Show all locked directories and lock-ids
*             'D'   Reset LOCKing word in first record
*             'C'   C I/O
*             'H'   Hook user routine to RZIODO
*             'X'   Exchange mode file
*
*             'B'   Rebuild bit map of file occupancy from file itself
*
* Called by <USER>
*
*  Author  : R.Brun DD/US/PD
*  Written : 07.04.86
*  Last mod: 22.09.94 JDS - include Z=RZCYCLE and call to RZVCYC
*            18.03.98 PN  - IZRECL assignment moved later to avoid warnings
*
************************************************************************
*
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZDIR.
      PARAMETER (NLPATM=100)
      COMMON /RZDIRN/NLCDIR,NLNDIR,NLPAT
      COMMON /RZDIRC/CHCDIR(NLPATM),CHNDIR(NLPATM),CHPAT(NLPATM)
      CHARACTER*16   CHNDIR,    CHCDIR,    CHPAT
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZK.
      PARAMETER (KUP=5,KPW1=7,KNCH=9,KDATEC=10,KDATEM=11,KQUOTA=12,
     +           KRUSED=13,KWUSED=14,KMEGA=15,KRZVER=16,KIRIN=17,
     +           KIROUT=18,KRLOUT=19,KIP1=20,KNFREE=22,KNSD=23,KLD=24,
     +           KLB=25,KLS=26,KLK=27,KLF=28,KLC=29,KLE=30,KNKEYS=31,
     +           KNWKEY=32,KKDES=33,KNSIZE=253,KEX=6,KNMAX=100)
C
*KEEP,RZCKEY.
      COMMON/RZCKEY/IHEAD(3),KEY(100),KEY2(100),KEYDUM(50)
C
*KEEP,RZCYCLE.
*
*     Pointers to cycle content
*
*     KLCYCL : length of cycle block (4,7)
*     KPPCYC : pointer to previous cycle
*     KFRCYC : first record number
*     KSRCYC : secord record number
*     KFLCYC : creation date/time and other stuff
*     KORCYC : offset in first record to data
*     KCNCYC : cycle number
*     KNWCYC : number of words in d/s
*     KKYCYC : key number to which this cycle belongs (only for version 1)
*     KVSCYC : version of RZ cycles structure (0, 1)
*
      INTEGER        KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
      COMMON/RZCYCLE/KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
*KEEP,RZBUFF.
      COMMON /RZBUFF/ ITEST(8704)
C
*KEND.
      CHARACTER    CHOPT*(*),CHDIR*(*)
      CHARACTER*16 CHTOP
      DIMENSION    IOPTV(10)
      EQUIVALENCE (IOPTM,IOPTV(1)), (IOPTU,IOPTV(2))
      EQUIVALENCE (IOPTS,IOPTV(3)), (IOPTL,IOPTV(4))
      EQUIVALENCE (IOPT1,IOPTV(5)), (IOPTD,IOPTV(6))
      EQUIVALENCE (IOPTC,IOPTV(7)), (IOPTX,IOPTV(8))
      EQUIVALENCE (IOPTB,IOPTV(9)), (IOPTH,IOPTV(10))
*
*-----------------------------------------------------------------------
*
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEND.
      IQUEST(1)=0
      LOGLV = MIN(NQLOGD,4)
      LOGLV = MAX(LOGLV,-3)
      LUNSA = LUN
      LUNP  = LUNIN
*
*          Save existing material (if any)
*
      CALL RZSAVE
*
      CALL UOPTC (CHOPT,'MUSL1DCXBH',IOPTV)
      IRELAT=0
      IMODEC=IOPTC
      IMODEH=IOPTH
      IMODEX=IOPTX
*
*     Take LRECL and LUNP from IQUEST(10-11) in case of C I/O
*
      IF(IOPTC.NE.0) THEN
         LRECP = IQUEST(10)
         LUNP  = IQUEST(11)
      ENDIF
*
*     Take LRECL and address of user routine from IQUEST(10-11)
*     in case of user I/O routine
*
      IF(IOPTH.NE.0) THEN
         LRECP  = IQUEST(10)
         LUN    = IQUEST(11)
         LUSER  = LUNIN
      ENDIF
*
*            Find record length (as specified in the OPEN statement)
*
*          A, Memory option. LUN contains the buffer address
*                            and the value of LUNP is the block length
*
      IF(IOPTM.NE.0)THEN
         LRECP=1024
         LUN=-99
      ELSEIF(IOPTH.EQ.0) THEN
*
*          B, Standard option DISK. Use information as specified
*             in the Fortran OPEN statement
*
*
         IZRECL=LRECP
         CALL RZIODO(LUNP,50,2,ITEST,1)
*
*      If option X not specified, determine mode (eXchange, native)
*      from file
*
         IF(IOPTX.EQ.0) THEN
            IF(JBIT(ITEST(9),12).NE.0)THEN
               IMODEX=1
            ENDIF
         ENDIF
 
         IF(IQUEST(1).NE.0)GO TO 30
         LB=ITEST(KLB)
         IF(LB.GT.48)CALL RZIODO(LUNP,LB+6,2,ITEST,1)
         IF(LB.GT.100)THEN
            IF(LOGLV.GE.-1) WRITE(IQLOG,10000)
10000       FORMAT(' RZFILE. WARNING!! Top directory is big')
         ENDIF
         LRECP=ITEST(LB+1)
         LUN=LUNP
         IQUEST(1)=0
      ENDIF
*
      IZRECL=LRECP
      IF(LOGLV.GE.0) WRITE(IQLOG,10200) LUN,LRECP,CHOPT
10200 FORMAT(' RZFILE. UNIT ',I6,' Initializing with LREC=',I6,
     +', OPT= ',A)
      CALL MZSDIV (0,-7)
*
*           Check if LUN not already defined
*
      LRZ=LQRS
   10 IF(LRZ.NE.0)THEN
         IF(IQ(KQSP+LRZ-5).EQ.LUN)THEN
            IQUEST(1)=1
            IF(LOGLV.GE.-2) WRITE(IQLOG,10300)
10300       FORMAT(' RZFILE. Unit is already in use')
            LUN=LUNSA
            GO TO 30
         ELSE
            LRZ=LQ(KQSP+LRZ)
            GO TO 10
         ENDIF
      ENDIF
*
*            First call to RZFILE, create link area
*
      IF(LQRS.EQ.0)THEN
         CALL MZLINK(JQPDVS,'RZCL',LTOP,LTOP,LFROM)
         CALL MZBOOK (JQPDVS,LRZ0,LQRS,1,'RZ0 ',2,2,36,2,0)
         IQ(KQSP+LRZ0-5)=0
         ISAVE = 1
         NHPWD = 0
         CALL VBLANK(IHPWD,2)
      ENDIF
      NCHD  = LEN(CHDIR)
      IF(NCHD.GT.16)NCHD=16
      CHTOP = CHDIR(1:NCHD)
*
*            Create control bank
*
      CALL MZBOOK(JQPDVS,LTOP,LQRS,1,'RZ  ',10,9,LRECP,2,0)
*
*            Disk or memory
*
      IF(IOPTM.EQ.0)THEN
         IQ(KQSP+LTOP-5) = LUN
*
*            C I/O?
*
         IF(IOPTC.NE.0) CALL SBIT1(IQ(KQSP+LTOP),5)
*
*            user I/O?
*
         IF(IOPTH.NE.0) THEN
            CALL SBIT1(IQ(KQSP+LTOP),6)
            CALL SBYT(LUSER,IQ(KQSP+LTOP),7,7)
         ENDIF
      ELSE
         NMEM=IQ(KQSP+LRZ0)+1
         IQ(KQSP+LRZ0)=NMEM
         IQ(KQSP+LTOP-5)=-NMEM
         IF(2*NMEM.GT.IQ(KQSP+LRZ0-1))THEN
            CALL MZPUSH(JQPDVS,LRZ0,0,10,' ')
         ENDIF
         IQ(KQSP+LRZ0+2*NMEM-1)=LOCF(LUNP)-LOCF(IQ(1))+1
         IQ(KQSP+LRZ0+2*NMEM  )=LRECP
         LUN=-NMEM
      ENDIF
*
*            Read 1st record of directory
*
      CALL RZIODO(LUN,LRECP,2,IQ(KQSP+LTOP+1),1)
      IF(IQUEST(1).NE.0)GO TO 30
      LD   = IQ(KQSP+LTOP+KLD)
      LB   = IQ(KQSP+LTOP+KLB)
      LREC = IQ(KQSP+LTOP+LB+1)
      NRD  = IQ(KQSP+LTOP+LD)
*
*     Set exchange mode bit
*
      CALL SBIT1(IQ(KQSP+LTOP+KPW1+2),12)
      IMODEX=JBIT(IQ(KQSP+LTOP+KPW1+2),12)
*
*            Increase size of control bank if required
*            and read all records for top directory
*
      NPUSH=NRD*LREC-LRECP
      IF(NPUSH.NE.0)CALL MZPUSH(JQPDVS,LTOP,0,NPUSH,'I')
      DO 20 I=2,NRD
         CALL RZIODO(LUN,LREC,IQ(KQSP+LTOP+LD+I),
     +               IQ(KQSP+LTOP+(I-1)*LREC+1),1)
         IF(IQUEST(1).NE.0)GO TO 30
   20 CONTINUE
      CALL VBLANK(IQ(KQSP+LTOP+1),4)
      CALL UCTOH(CHDIR,IQ(KQSP+LTOP+1),4,NCHD)
      CALL ZHTOI(IQ(KQSP+LTOP+1),IQ(KQSP+LTOP+1),4)
      CALL SBYT(NCHD,IQ(KQSP+LTOP+KPW1+2),1,5)
      CALL UCOPY(IQ(KQSP+LTOP+KPW1),IHPWD,2)
      NHPWD=JBYT(IQ(KQSP+LTOP+KPW1+2),6,5)
      IQ(KQSP+LTOP+KIRIN)=0
      IQ(KQSP+LTOP+KIROUT)=0
 
      LFREE = 0
      LUSED = 0
      LRIN  = 0
      LPURG = 0
      LROUT = 0
      LCDIR = LTOP
      NLCDIR= 1
      NLNDIR= 1
      NLPAT = 1
      CHCDIR(1)=CHTOP
      CHNDIR(1)=CHTOP
*
*             Reset LOCKing word in record 1
*
      IF(IOPTD.NE.0)THEN
         CALL RZDLOK
      ENDIF
*
*             Show locks
*
      IF(IOPTL.NE.0)THEN
         CALL RZLLOK
      ENDIF
*
*            Store default LOG level
*
      LOGL = LOGLV + 3
      CALL SBYT(LOGL,IQ(KQSP+LTOP),15,3)
      CALL RZVCYC(LTOP)
*
*     Rebuild bit map?
*
      IF(IOPTB.NE.0) CALL RZVERI('//'//CHTOP(1:NCHD),'B')
*
*             UPDATE mode only
*
      CALL SBIT1(IQ(KQSP+LTOP),1)
      IF(IOPTU.NE.0.OR.IOPT1.NE.0)THEN
*
*            Allocate free records
*
         CALL SBIT0(IQ(KQSP+LTOP),1)
         CALL MZBOOK(JQPDVS,LFREE,LTOP,-2,'RZFR',0,0,21,2,0)
         IQ(KQSP+LFREE-5)=LUN
*
*        IF(IOPTU.EQ.0.AND.IOPT1.EQ.0)THEN
         IF(IOPTS.EQ.0)THEN
            CALL SBIT1(IQ(KQSP+LTOP),3)
            CALL RZLOCK('RZFILE')
            IF(IQUEST(1).NE.0)THEN
               CALL SBIT1(IQ(KQSP+LTOP),1)
               IQ1=IQUEST(1)
               CALL MZDROP(JQPDVS,LFREE,' ')
               LFREE=0
               IQUEST(1)=2+IQ1
               GO TO 30
            ENDIF
         ELSE
            CALL SBIT0(IQ(KQSP+LTOP),3)
         ENDIF
*
*            Allocate space for used records
*
         CALL MZBOOK(JQPDVS,LUSED,LTOP,-3,'RZUS',0,0,21,2,0)
         IQ(KQSP+LUSED-5)=LUN
      ENDIF
      IQUEST(7)=IQ(KQSP+LCDIR+KNKEYS)
      IQUEST(8)=IQ(KQSP+LCDIR+KNWKEY)
*
   30 RETURN
      END
*CMZ :  1.40/05 18/03/98  17.23.05  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZLOGL(LUN,LOGLEV)
*
************************************************************************
*
*        To set the LOG level
* Input:
*   LUN     Logical unit number for which the logging level has to be set
*   LOGLEV  Logging level
*           -3  Suppress all messages
*           -2  Error messages only
*           -1  Terse logging
*            0  Normal logging: RZFILE, RZEND
*            1  Log to watch rare events
*            2  Log to monitor calls
*            3  Short diagnostics
*               Short dumps to debug user-written output routines
*            4  Full diagnostics
*               Full dumps to debug user-written output routines
*
* Called by <USER>
*
*  Author  : R.Brun DD/US/PD
*  Written : 01.04.86
*  Last mod: 17.11.92 JDS - restrict loglevel to documented range
*                     so that only 3 bits are required to store it (15-17)
*            18.03.98 PN  - NQLOGD is really used in RZ package...
*
************************************************************************
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,ZSTATE.
      COMMON /ZSTATE/QVERSN,NQPHAS,IQDBUG,NQDCUT,NQWCUT,NQERR
     +,              NQLOGD,NQLOGM,NQLOCK,NQDEVZ,NQOPTS(6)
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEND.
*-----------------------------------------------------------------------
*
      NQLOGD = LOGLEV
*
      IQUEST(1)=0
      IF(LQRS.EQ.0)GO TO 99
      LRZ=LQRS
  10  IF(LRZ.EQ.0)GO TO 99
      IF(IQ(KQSP+LRZ-5).NE.LUN)THEN
         LRZ=LQ(KQSP+LRZ)
         GO TO 10
      ENDIF
*
      LOGL = MIN(LOGLEV,4)
      LOGL = MAX(LOGL, -3) + 3
      CALL SBYT(LOGL,IQ(KQSP+LRZ),15,3)
      IF(LOGLEV.GE.0)WRITE(IQLOG,9022)LUN,LOGLEV
 9022 FORMAT(' RZLOGL.  File at LUN=',I6,', Diagnostic log level=',I2)
*
  99  RETURN
      END
*CMZ :  1.40/05 18/06/98  22.07.51  by  Pavel Nevski
*-- Author :    Pavel Nevski   18/06/98
          subroutine zdummy
*KEEP,MZCA, IF=QTRHOLL.
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
*KEEP,MZCB.
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
*KEEP,MZCC.
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
*KEEP,ZBCDCH.
                      CHARACTER  CQALLC*96
      COMMON /ZBCDCH/ CQALLC
                      CHARACTER*1  CQLETT(96), CQNUM(10)
                      EQUIVALENCE (CQLETT(1),CQALLC(1:1))
                      EQUIVALENCE (CQNUM(1), CQALLC(27:27))
*KEND.
          end
*CMZ :  1.40/05 20/03/95  09.52.17  by  Unknown
*-- Author :
      SUBROUTINE RZIODO(LUNRZ,JREC,IREC1,IBUF,IRW)
*
**********************************************************************
*
*        To read/write a block from disk or memory
*
*       LUNRZ Logical unit number for disk (LUN>0)
*       JREC  Record length
*       IREC  RECORD NUMBER
*       IBUF  ADDRESS OF BUFFER TO BE READ/WRITTEN ON IREC
*       IRW   =1 TO READ
*       IRW   =2 TO WRITE
*
* Called by RZCOP1,RZDELT,RZDFIR,RZFILE,RZFREE,RZLLOK,RZLOCK
*           RZMAKE,RZMDIR,RZOUT,RZREAD,RZSAVE,RZOPEN
*
*  Author  : R.Brun DD/US/PD
*  Written : 01.04.86
*  Last mod: 10.06.94 Implement File striping for PIAF (R.Brun)
*                     New routine RZSTRIR called
*  Last mod: 26.10.93 IQUEST(1) = 101 in case of READ error,
*                                 102 in case of WRITE error
*
************************************************************************
*
*KEEP,ZUNIT.
      COMMON /ZUNIT/ IQREAD,IQPRNT,IQPR2,IQLOG,IQPNCH,IQTTIN,IQTYPE
      COMMON /ZUNITZ/IQDLUN,IQFLUN,IQHLUN,  NQUSED
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZBUFF.
      COMMON /RZBUFF/ ITEST(8704)
C
*KEEP,RZCOUNT.
      COMMON/RZCOUNT/RZXIO(2)
C
*KEEP,RZCSTR.
      PARAMETER     (MAXFILES=128, MAXSTRIP=21)
      CHARACTER*128  RZNAMES(MAXFILES),RZSFILE(MAXSTRIP)
      COMMON/RZCSTRC/RZNAMES,RZSFILE
      COMMON/RZCSTRI/ISLAST,ISTRIP(MAXFILES),NSTRIP(MAXFILES),
     +                      NRSTRIP(MAXFILES)
C
*KEND.
      DIMENSION IBUF(JREC)
      PARAMETER (MEDIUM=0)
*
*-----------------------------------------------------------------------
*
*
*     I/O statistics
*
      RZXIO(IRW) = RZXIO(IRW) + JREC
 
      IREC=IREC1
      IF(LUNRZ.GT.0)THEN
         NERR=0
         IF(IMODEH.NE.0) THEN
*
            IQUEST(1) = JBYT(IQ(KQSP+LTOP),7,7)
            IQUEST(2) = JREC
            IQUEST(4) = IREC
            IOWAY     = IRW - 1
*
            CALL JUMPST(LUNRZ)
            CALL JUMPX2(IBUF,IOWAY)
 
            IF(IQUEST(1).NE.0) IQUEST(1) = 100 + IRW
         ELSE
*
*     Read a record
*
   10       IF (IRW.EQ.1)THEN
*
*     Fortran I/O
*
               IF(IMODEC.EQ.0) THEN
*-* Case of File striping
*
      if(nstrip(lunrz).gt.0)then
         call rzstrir(lunrz,irec)
      endif
*
                  READ (UNIT=LUNRZ,REC=IREC,ERR=20,IOSTAT=ISTAT)IBUF
*
*     C I/O
*
               ELSE
*-* Case of File striping
*
      if(nstrip(lunrz-1000).gt.0)then
         call rzstrir(lunrz-1000,irec)
      endif
*
                     CALL CFSEEK(LUNRZ-1000,MEDIUM,IZRECL,IREC-1,ISTAT)
                     NWTAK = JREC
                     CALL CFGET(LUNRZ-1000,MEDIUM,JREC,NWTAK,IBUF,
     +               ISTAT)
                     IF(ISTAT.NE.0) GOTO 20
               ENDIF
*
*     Write
*
            ELSE
               IF(IMODEC.EQ.0) THEN
                  WRITE(UNIT=LUNRZ,REC=IREC,ERR=20,IOSTAT=ISTAT)IBUF
               ELSE
                  CALL CFSEEK(LUNRZ-1000,MEDIUM,IZRECL,IREC-1,ISTAT)
                  IF(ISTAT.NE.0) GOTO 20
                  CALL CFPUT(LUNRZ-1000,MEDIUM,JREC,IBUF,ISTAT)
                  IF(ISTAT.NE.0) GOTO 20
               ENDIF
            ENDIF
            RETURN
   20       NERR=NERR+1
            IF(NERR.LT.100)GO TO 10
            IQUEST(1)=100+IRW
            WRITE(IQLOG,1000)IREC,LUNRZ,ISTAT
 1000       FORMAT(' RZIODO. Error at record =',I5,' LUN =',I6,
     +             ' IOSTAT =',I6)
         ENDIF
      ELSE
         KOF=IQ(KQSP+LRZ0-2*LUNRZ-1)+IQ(KQSP+LRZ0-2*LUNRZ)*(IREC-1)
         IF (IRW.EQ.1)THEN
            CALL UCOPY(IQ(KOF),IBUF,JREC)
         ELSE
            CALL UCOPY(IBUF,IQ(KOF),JREC)
         ENDIF
      ENDIF
*
      END
*CMZ :  1.40/05 19/08/98  20.10.01  by  Pavel Nevski
*-- Author :
      SUBROUTINE RZPURG(NKEEP)
*
************************************************************************
*
*        Purge cycles in the CWD
* Input:
*   NKEEP   Number of cycles which must be kept for the given key
*           If NKEEP < 1 then NKEEP is taken to be 1 and only the highest
*           cycle is kept
*
* Called by <USER>
*
*  Author  : R.Brun DD/US/PD
*  Written : 06.04.86
*  Last mod: 11.12.88
*          : 04.03.94 S.Banerjee (Change in cycle structure)
*
************************************************************************
*KEEP,RZCL.
      PARAMETER      (IQDROP=25, IQMARK=26, IQCRIT=27, IQSYSX=28)
      INTEGER      IQUEST
      COMMON/QUEST/IQUEST(100)
      COMMON /ZVFAUT/IQVID(2),IQVSTA,IQVLOG,IQVTHR(2),IQVREM(2,6)
      COMMON /ZEBQ/  IQFENC(4), LQ(100)
                              DIMENSION    IQ(92),        Q(92)
                              EQUIVALENCE (IQ(1),LQ(9)), (Q(1),IQ(1))
      COMMON /MZCA/  NQSTOR,NQOFFT(16),NQOFFS(16),NQALLO(16), NQIAM
     +,              LQATAB,LQASTO,LQBTIS, LQWKTB,NQWKTB,LQWKFZ
     +,              MQKEYS(3),NQINIT,NQTSYS,NQM99,NQPERM,NQFATA,NQCASE
     +,              NQTRAC,MQTRAC(48)
                                       EQUIVALENCE (KQSP,NQOFFS(1))
      COMMON /MZCB/  JQSTOR,KQT,KQS,  JQDIVI,JQDIVR
     +,              JQKIND,JQMODE,JQDIVN,JQSHAR,JQSHR1,JQSHR2,NQRESV
     +,              LQSTOR,NQFEND,NQSTRU,NQREF,NQLINK,NQMINR,LQ2END
     +,              JQDVLL,JQDVSY,NQLOGL,NQSNAM(6)
                                       DIMENSION    IQCUR(16)
                                       EQUIVALENCE (IQCUR(1),LQSTOR)
      COMMON /MZCC/  LQPSTO,NQPFEN,NQPSTR,NQPREF,NQPLK,NQPMIN,LQP2E
     +,              JQPDVL,JQPDVS,NQPLOG,NQPNAM(6)
     +,              LQSYSS(10), LQSYSR(10), IQTDUM(22)
     +,              LQSTA(21), LQEND(20), NQDMAX(20),IQMODE(20)
     +,              IQKIND(20),IQRCU(20), IQRTO(20), IQRNO(20)
     +,              NQDINI(20),NQDWIP(20),NQDGAU(20),NQDGAF(20)
     +,              NQDPSH(20),NQDRED(20),NQDSIZ(20)
     +,              IQDN1(20), IQDN2(20),      KQFT, LQFSTA(21)
                                       DIMENSION    IQTABV(16)
                                       EQUIVALENCE (IQTABV(1),LQPSTO)
C
      COMMON /RZCL/  LTOP,LRZ0,LCDIR,LRIN,LROUT,LFREE,LUSED,LPURG
     +,              LTEMP,LCORD,LFROM
                   EQUIVALENCE (LQRS,LQSYSS(7))
C
*KEEP,RZCLUN.
      COMMON /RZCLUN/LUN,LREC,ISAVE,IMODEX,IRELAT,NHPWD,IHPWD(2)
     +,              IZRECL,IMODEC,IMODEH
C
*KEEP,RZK.
      PARAMETER (KUP=5,KPW1=7,KNCH=9,KDATEC=10,KDATEM=11,KQUOTA=12,
     +           KRUSED=13,KWUSED=14,KMEGA=15,KRZVER=16,KIRIN=17,
     +           KIROUT=18,KRLOUT=19,KIP1=20,KNFREE=22,KNSD=23,KLD=24,
     +           KLB=25,KLS=26,KLK=27,KLF=28,KLC=29,KLE=30,KNKEYS=31,
     +           KNWKEY=32,KKDES=33,KNSIZE=253,KEX=6,KNMAX=100)
C
*KEEP,RZCYCLE.
*
*     Pointers to cycle content
*
*     KLCYCL : length of cycle block (4,7)
*     KPPCYC : pointer to previous cycle
*     KFRCYC : first record number
*     KSRCYC : secord record number
*     KFLCYC : creation date/time and other stuff
*     KORCYC : offset in first record to data
*     KCNCYC : cycle number
*     KNWCYC : number of words in d/s
*     KKYCYC : key number to which this cycle belongs (only for version 1)
*     KVSCYC : version of RZ cycles structure (0, 1)
*
      INTEGER        KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
      COMMON/RZCYCLE/KLCYCL, KPPCYC, KFRCYC, KSRCYC, KFLCYC, KORCYC,
     +               KCNCYC, KNWCYC, KKYCYC, KVSCYC
*KEND.
*
*-----------------------------------------------------------------------
*
*KEEP,Q$JBIT.
      JBIT (IZW,IZP)    = AND (lrshft(IZW,IZP-1), 1)
      JBYT (IZW,IZP,NZB)= lrshft (LSHIFT(IZW,33-IZP-NZB),32-NZB)
*KEND.
      IQUEST(1)=0
      NK=NKEEP
      IF(NK.LT.1)NK=1
*
*           Check if write permission
*
      IF(LQRS.EQ.0)GO TO 999
      IFLAG=1
      CALL RZMODS('RZPURG',IFLAG)
      IF(IFLAG.NE.0)GO TO 999
*
      LK=IQ(KQSP+LCDIR+KLK)
      LC=IQ(KQSP+LCDIR+KLC)
      LE=IQ(KQSP+LCDIR+KLE)
      NKEYS =IQ(KQSP+LCDIR+KNKEYS)
      NWKEY =IQ(KQSP+LCDIR+KNWKEY)
      IF(NKEYS.EQ.0)GO TO 999
*
      NPUOLD=0
      IF(LPURG.NE.0)THEN
         NPURG=IQ(KQSP+LPURG+1)
         DO 5 I=1,NPURG
            NPUOLD=NPUOLD+IQ(KQSP+LPURG+2*I+1)-IQ(KQSP+LPURG+2*I)+1
   5     CONTINUE
      ENDIF
*
      DO 20 IK=1,NKEYS
         LKC=LK+(NWKEY+1)*(IK-1)
         LCYC=IQ(KQSP+LCDIR+LKC)
         NC=0
  10     NC=NC+1
         IF (LCYC.LE.0. or. LCYC.GE.10000) then
           print *,' RZPURG: cant purge keys starting from ',ik
           print *,' nkeys,ik,nc,LK,LKC,LCYC =',nkeys,ik,nc,LK,LKC,LCYC
           IQUEST(1)=9
           return
         endif
 
         IF (KVSCYC.EQ.0) THEN
            LCOLD = JBYT(IQ(KQSP+LCDIR+LCYC+KPPCYC), 1,16)
         ELSE
            LCOLD = IQ(KQSP+LCDIR+LCYC+KPPCYC)
         ENDIF
*
*              Check for first cycle to be kept
*
         LKEEP=LCOLD
         IF(LKEEP.NE.0)THEN
  12        IF(JBIT(IQ(KQSP+LCDIR+LKEEP+KFLCYC),5).EQ.0)THEN
               IF (KVSCYC.EQ.0) THEN
                  LKEEP = JBYT(IQ(KQSP+LCDIR+LKEEP+KPPCYC),1,16)
               ELSE
                  LKEEP = IQ(KQSP+LCDIR+LKEEP+KPPCYC)
               ENDIF
               IF(LKEEP.NE.0)GO TO 12
            ENDIF
         ENDIF
         IF(NC.EQ.NK)THEN
            IF (KVSCYC.EQ.0) THEN
               CALL SBYT(LKEEP,IQ(KQSP+LCDIR+LCYC+KPPCYC),1,16)
            ELSE
               IQ(KQSP+LCDIR+LCYC+KPPCYC) = LKEEP
            ENDIF
         ENDIF
         IF(NC.GT.NK)THEN
            IF(JBIT(IQ(KQSP+LCDIR+LCYC+KFLCYC),5).NE.0)THEN
               IF (KVSCYC.EQ.0) THEN
                  CALL SBYT(LKEEP,IQ(KQSP+LCDIR+LCYC+KPPCYC),1,16)
               ELSE
                  IQ(KQSP+LCDIR+LCYC+KPPCYC) = LKEEP
               ENDIF
               GO TO 15
            ENDIF
            IF (KVSCYC.EQ.0) THEN
               IR1  = JBYT(IQ(KQSP+LCDIR+LCYC+KFRCYC),17,16)
               IP1  = JBYT(IQ(KQSP+LCDIR+LCYC+KORCYC), 1,16)
               NW   = JBYT(IQ(KQSP+LCDIR+LCYC+KNWCYC), 1,20)
               IR2  = JBYT(IQ(KQSP+LCDIR+LCYC+KSRCYC),17,16)
            ELSE
               IR1  = IQ(KQSP+LCDIR+LCYC+KFRCYC)
               IP1  = JBYT(IQ(KQSP+LCDIR+LCYC+KORCYC), 1,20)
               NW   = IQ(KQSP+LCDIR+LCYC+KNWCYC)
               IR2  = IQ(KQSP+LCDIR+LCYC+KSRCYC)
            ENDIF
            IRL  =0
            NWL  =0
*
*              Mark all records that can be purged in first pass
*
            NLEFT=LREC-IP1+1
            NW1=NW
            IF(NW1.GE.NLEFT)NW1=NLEFT
            IF(IR2.NE.0)THEN
               NR=(NW-NW1-1)/LREC+1
               IF(NR.GT.1)THEN
                  CALL RZPURF(NR-1,IR2)
               ENDIF
               IRL=IR2+NR-1
               NWL=NW-NW1-(NR-1)*LREC
            ENDIF
            IF(NW1.EQ.LREC)THEN
               CALL RZPURF(1,IR1)
               IR1=0
            ENDIF
            IF(NWL.EQ.LREC)THEN
               CALL RZPURF(1,IRL)
               IRL=0
            ENDIF
            IRLOUT=IQ(KQSP+LCDIR+KRLOUT)
            IF(IRL.EQ.IRLOUT.AND.NWL+1.EQ.IQ(KQSP+LCDIR+KIP1))THEN
               CALL RZPURF(1,IRL)
            ENDIF
            IQ(KQSP+LCDIR+LCYC  )=-1
            IQ(KQSP+LCDIR+LCYC+1)=IR1
            IQ(KQSP+LCDIR+LCYC+2)=IRL
         ENDIF
*
  15     IF(LCOLD.NE.0.AND.LCOLD.NE.LCYC)THEN
            LCYC=LCOLD
            GO TO 10
         ENDIF
  20  CONTINUE
*
*           Now loop on all purged cycles to find complete records
*           purged
*
      DO 70 LKC=LC,LE-KLCYCL+1,KLCYCL
         IF(IQ(KQSP+LCDIR+LKC).NE.-1)GO TO 70
         IR1=IQ(KQSP+LCDIR+LKC+1)
         IRL=IQ(KQSP+LCDIR+LKC+2)
         IF(IR1.NE.0)THEN
            DO 30 LKC1=LC,LE-KLCYCL+1,KLCYCL
               IF(IQ(KQSP+LCDIR+LKC1).EQ.-1)GO TO 30
               IF (KVSCYC.EQ.0) THEN
                  KR1  = JBYT(IQ(KQSP+LCDIR+LKC1+KFRCYC),17,16)
                  KP1  = JBYT(IQ(KQSP+LCDIR+LKC1+KORCYC), 1,16)
                  NW   = JBYT(IQ(KQSP+LCDIR+LKC1+KNWCYC), 1,20)
                  KR2  = JBYT(IQ(KQSP+LCDIR+LKC1+KSRCYC),17,16)
               ELSE
                  KR1  = IQ(KQSP+LCDIR+LKC1+KFRCYC)
                  KP1  = JBYT(IQ(KQSP+LCDIR+LKC1+KORCYC), 1,20)
                  NW   = IQ(KQSP+LCDIR+LKC1+KNWCYC)
                  KR2  = IQ(KQSP+LCDIR+LKC1+KSRCYC)
               ENDIF
               KRL  =0
               NLEFT=LREC-KP1+1
               NW1=NW
               IF(NW1.GE.NLEFT)NW1=NLEFT
               IF(KR2.NE.0)THEN
                  NR=(NW-NW1-1)/LREC+1
                  KRL=KR2+NR-1
               ENDIF
               IF(KR1.EQ.IR1.OR.KRL.EQ.IR1)GO TO 40
  30        CONTINUE
            CALL RZPURF(1,IR1)
         ENDIF
*
  40     IF(IRL.NE.0)THEN
            DO 50 LKC1=LC,LE-KLCYCL+1,KLCYCL
               IF(IQ(KQSP+LCDIR+LKC1).EQ.-1)GO TO 50
               IF (KVSCYC.EQ.0) THEN
                  KR1  = JBYT(IQ(KQSP+LCDIR+LKC1+KFRCYC),17,16)
                  KP1  = JBYT(IQ(KQSP+LCDIR+LKC1+KORCYC), 1,16)
                  NW   = JBYT(IQ(KQSP+LCDIR+LKC1+KNWCYC), 1,20)
                  KR2  = JBYT(IQ(KQSP+LCDIR+LKC1+KSRCYC),17,16)
               ELSE
                  KR1  = IQ(KQSP+LCDIR+LKC1+KFRCYC)
                  KP1  = JBYT(IQ(KQSP+LCDIR+LKC1+KORCYC), 1,20)
                  NW   = IQ(KQSP+LCDIR+LKC1+KNWCYC)
                  KR2  = IQ(KQSP+LCDIR+LKC1+KSRCYC)
               ENDIF
               KRL  =0
               NLEFT=LREC-KP1+1
               NW1=NW
               IF(NW1.GE.NLEFT)NW1=NLEFT
               IF(KR2.NE.0)THEN
                  NR=(NW-NW1-1)/LREC+1
                  KRL=KR2+NR-1
               ENDIF
               IF(KR1.EQ.IRL.OR.KRL.EQ.IRL)GO TO 70
  50        CONTINUE
            CALL RZPURF(1,IRL)
         ENDIF
  70  CONTINUE
*
*           Garbage collection on cycles area + relocation
*
      LKC3=LE-KLCYCL+1
  80  IF(LKC3.LT.LC)GO TO 200
      IF(IQ(KQSP+LCDIR+LKC3).EQ.-1)THEN
         LKC3=LKC3+KLCYCL
         LKC2=LKC3-2*KLCYCL
  90     IF(IQ(KQSP+LCDIR+LKC2).NE.-1)THEN
            LKC2=LKC2+KLCYCL
            LKC1=LKC2-2*KLCYCL
            IF(LKC1.LT.LC)LKC1=LC
 100        IF(IQ(KQSP+LCDIR+LKC1).EQ.-1)THEN
               IF(LKC1.GT.LC)LKC1=LKC1+KLCYCL
            ELSE
               IF(LKC1.GT.LC)THEN
                  LKC1=LKC1-KLCYCL
                  GO TO 100
               ENDIF
            ENDIF
*
            NPUSH=LKC3-LKC2
            DO 110 LKC=LC,LKC2-KLCYCL,KLCYCL
               IF(IQ(KQSP+LCDIR+LKC).NE.-1)THEN
                  IF (KVSCYC.EQ.0) THEN
                     LCOLD = JBYT(IQ(KQSP+LCDIR+LKC+KPPCYC),1,16)
                  ELSE
                     LCOLD = IQ(KQSP+LCDIR+LKC+KPPCYC)
                  ENDIF
                  IF(LCOLD.GE.LKC1.AND.LCOLD.LT.LKC2)THEN
                     LCOLD=LCOLD+NPUSH
                     IF (KVSCYC.EQ.0) THEN
                        CALL SBYT(LCOLD,IQ(KQSP+LCDIR+LKC+KPPCYC),1,16)
                     ELSE
                        IQ(KQSP+LCDIR+LKC+KPPCYC) = LCOLD
                     ENDIF
                  ENDIF
               ENDIF
 110        CONTINUE
*
            DO 120 IK=1,NKEYS
               LCYC=IQ(KQSP+LCDIR+LK+(NWKEY+1)*(IK-1))
               IF(LCYC.GE.LKC1.AND.LCYC.LT.LKC2)THEN
                  IQ(KQSP+LCDIR+LK+(NWKEY+1)*(IK-1))=
     +            IQ(KQSP+LCDIR+LK+(NWKEY+1)*(IK-1))+NPUSH
               ENDIF
 120        CONTINUE
*
            CALL UCOPY2(IQ(KQSP+LCDIR+LKC1),IQ(KQSP+LCDIR+LKC1+NPUSH),
     +                  LKC2-LKC1)
            LKC3=LKC1+NPUSH
            LKC2=LKC1-KLCYCL
            IF(LKC1.NE.LC)GO TO 90
            LC=LC+NPUSH
            GO TO 200
*
         ELSE
            LKC2=LKC2-KLCYCL
            IF(LKC2.GE.LC)GO TO 90
         ENDIF
      ELSE
         LKC3=LKC3-KLCYCL
         GO TO 80
      ENDIF
*
*           Reset internal pointers
*
 200  CONTINUE
*
      NPUNEW=0
      IF(LPURG.NE.0)THEN
         NPURG=IQ(KQSP+LPURG+1)
         DO 210 I=1,NPURG
            NPUNEW=NPUNEW+IQ(KQSP+LPURG+2*I+1)-IQ(KQSP+LPURG+2*I)+1
 210     CONTINUE
      ENDIF
      NPU=NPUNEW-NPUOLD
      IQUEST( 9)=IQ(KQSP+LCDIR+KQUOTA)-IQ(KQSP+LCDIR+KRUSED)+NPU
      IQUEST(11)=(LC-IQ(KQSP+LCDIR+KLC))/KLCYCL
      IQUEST(12)=NPU*LREC
      IQUEST(13)=NPU
*
      IQ(KQSP+LCDIR+KRUSED)=IQ(KQSP+LCDIR+KRUSED)-NPU
      NWP=NPU*LREC
      NMEGA=NWP/1000000
      IQ(KQSP+LCDIR+KMEGA)=IQ(KQSP+LCDIR+KMEGA)-NMEGA
      NWP=NWP-1000000*NMEGA
      IQ(KQSP+LCDIR+KWUSED)=IQ(KQSP+LCDIR+KWUSED)-NWP
      IQ(KQSP+LCDIR+KNFREE)=IQ(KQSP+LCDIR+KNFREE)+LC-IQ(KQSP+LCDIR+KLC)
      IQ(KQSP+LCDIR+KLC)=LC
*
 999  RETURN
      END
