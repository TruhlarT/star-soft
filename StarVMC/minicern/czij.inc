*
* $Id: czij.inc,v 1.1 2005/06/09 00:05:12 fisyak Exp $
*
* $Log: czij.inc,v $
* Revision 1.1  2005/06/09 00:05:12  fisyak
* Add stuff for reconstruction
*
* Revision 1.1  2005/05/26 22:28:01  fisyak
* Add stuff necessary for reconstruction packages
*
* Revision 1.1.1.1  1996/02/15 17:48:55  mclareni
* Kernlib
*
*
*
* czij.inc
*
#if defined(CERNLIB_NUMAP)||defined(CERNLIB_NUMCD)||defined(CERNLIB_NUMCV)||defined(CERNLIB_NUMIB2)||defined(CERNLIB_NUMND)
          IZ  =  (LOCF(Z21) - LOCF(Z)) / 2
          JZ  =  (LOCF(Z12) - LOCF(Z)) / 2
#endif
#if defined(CERNLIB_NUMCR)||defined(CERNLIB_NUMUC)
          IZ  =  (LOC(Z21) - LOC(Z)) / 2
          JZ  =  (LOC(Z12) - LOC(Z)) / 2
#endif
#if defined(CERNLIB_NUMDE)
          IZ  =  (%LOC(Z21) - %LOC(Z)) / 8
          JZ  =  (%LOC(Z12) - %LOC(Z)) / 8
#endif
#if defined(CERNLIB_NUMIB1)
          IZ  =  (IADDR(Z21) - IADDR(Z)) / 8
          JZ  =  (IADDR(Z12) - IADDR(Z)) / 8
#endif
