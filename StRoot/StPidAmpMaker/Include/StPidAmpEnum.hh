/***************************************************************************
 *
 * $Id: StPidAmpEnum.hh,v 1.2 2000/04/09 16:38:31 aihong Exp $
 *
 * Author: Aihong Tang & Richard Witt (FORTRAN Version),Kent State U.
 *         Send questions to aihong@cnr.physics.kent.edu
 ***************************************************************************
 *
 * Description:part of StPidAmpMaker package
 *             
 ***************************************************************************
 *
 * $Log: StPidAmpEnum.hh,v $
 * Revision 1.2  2000/04/09 16:38:31  aihong
 * nhitsDcaDependent added
 *
 * Revision 1.1.1.1  2000/03/09 17:48:34  aihong
 * Installation of package
 *
 **************************************************************************/

#ifndef StPidAmpEnum_hh
#define StPidAmpEnum_hh

enum StPidAmpNetType {noDependent, ptDependent, nhitsDependent,nhitsDcaDependent, ptNhitsDependent};


#endif
