*
* $Id: rmsub.F,v 1.1 2005/06/09 00:05:18 fisyak Exp $
*
* $Log: rmsub.F,v $
* Revision 1.1  2005/06/09 00:05:18  fisyak
* Add stuff for reconstruction
*
* Revision 1.1  2005/05/26 22:28:17  fisyak
* Add stuff necessary for reconstruction packages
*
* Revision 1.1.1.1  1996/02/15 17:48:58  mclareni
* Kernlib
*
*
#include "kernnum/pilot.h"
          SUBROUTINE          RMSUB(M,N,X,X12,X21,Y,Y12,Y21,Z,Z12,Z21)
          REAL                X(*), X12(*), X21(*), Y(*), Y12(*), Y21(*)
          REAL                Z(*), Z12(*), Z21(*), ADD,  A,      B
          ADD(A,B)  =  A-B
#include "rxij.inc"
#include "ryij.inc"
#include "rzij.inc"
#include "madd.inc"
