/***************************************************************************
 *
 * $Id: StHbtPair.hh,v 1.12 2001/01/22 22:56:40 laue Exp $
 *
 * Author: Brian Laziuk, Yale University
 *         slightly modified by Mike Lisa
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    the Pair object is passed to the PairCuts for verification, and
 *    then to the AddRealPair and AddMixedPair methods of the
 *    Correlation Functions
 *
 ***************************************************************************
 *
 * $Log: StHbtPair.hh,v $
 * Revision 1.12  2001/01/22 22:56:40  laue
 * Yano-Koonin-Podgoretskii Parametrisation added
 *
 * Revision 1.11  2000/10/26 16:09:16  lisa
 * Added OpeningAngle PairCut class and method to StHbtPair
 *
 * Revision 1.10  2000/10/05 23:09:05  lisa
 * Added kT-dependent radii to mixed-event simulator AND implemented AverageSeparation Cut and CorrFctn
 *
 * Revision 1.9  2000/07/17 20:03:17  lisa
 * Implemented tools for addressing and assessing trackmerging
 *
 * Revision 1.8  2000/04/04 16:13:09  lisa
 * StHbtPair:quality() now returns normalized value (and so is double) and add a CorrFctn which looks at quality()
 *
 * Revision 1.7  2000/04/03 22:09:12  rcwells
 * Add member function ... quality().
 *
 * Revision 1.6  2000/02/13 21:13:34  lisa
 * changed ambiguous StHbtPair::fourMomentum() to fourMomentumSum() and fourMomentumDiff() and fixed related bug in QvecCorrFctn
 *
 * Revision 1.5  2000/01/25 17:35:17  laue
 * I. In order to run the stand alone version of the StHbtMaker the following
 * changes have been done:
 * a) all ClassDefs and ClassImps have been put into #ifdef __ROOT__ statements
 * b) unnecessary includes of StMaker.h have been removed
 * c) the subdirectory StHbtMaker/doc/Make has been created including everything
 * needed for the stand alone version
 *
 * II. To reduce the amount of compiler warning
 * a) some variables have been type casted
 * b) some destructors have been declared as virtual
 *
 * Revision 1.4  1999/07/29 16:16:34  lisa
 * Selemons upgrade of StHbtPair class
 *
 * Revision 1.3  1999/07/22 18:49:10  lisa
 * Implement idea of Fabrice to not create and delete StHbtPair all the time
 *
 * Revision 1.2  1999/07/06 22:33:22  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:57  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#ifndef ST_HBT_PAIR_HH
#define ST_HBT_PAIR_HH

#include <utility>

#include "StHbtMaker/Infrastructure/StHbtParticle.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class StHbtPair {
public:
  StHbtPair();
  StHbtPair(StHbtParticle*, StHbtParticle*);
  

  ~StHbtPair();
  //StHbtPair(const StHbtPair&);
  //StHbtPair& operator=(const StHbtPair&);

  // track Gets:
  StHbtParticle* track1() const;
  StHbtParticle* track2() const;
  // track Sets:
  void SetTrack1(const StHbtParticle* trkPtr);
  void SetTrack2(const StHbtParticle* trkPtr);

  StHbtLorentzVector fourMomentumDiff() const;
  StHbtLorentzVector fourMomentumSum() const;
  double qInv() const;
  double kT()   const;
  double mInv() const;

  // Bertsch-Pratt momentum components in Pair Frame - written by Bekele/Humanic
  double qSidePf() const;
  double qOutPf() const;
  double qLongPf() const;
   
  // Bertsch-Pratt momentum components in Local CMS (longitudinally comoving) frame
  // - written by Bekele/Humanic
  double qSideCMS() const;
  double qOutCMS() const;
  double qLongCMS() const;

  // Bertsch-Pratt momentum components in a longitudinally boosted frame
  // the argument is the beta of the longitudinal boost (default is 0.0, meaning lab frame)
  // - written by Bekele/Humanic
  double qSideBf(double beta=0.0) const;
  double qOutBf(double beta=0.0) const;
  double qLongBf(double beta=0.0) const;

  // Yano-Koonin-Podgoretskii Parametrisation 
  void qYKPCMS(double& qP, double& qT, double& q0);
  void qYKPLCMS(double& qP, double& qT, double& q0);

  double quality() const;

  // the following two methods calculate the "nominal" separation of the tracks 
  // at the inner field cage (EntranceSeparation) and when they exit the TPC,
  // which may be at the outer field cage, or at the endcaps.
  // "nominal" means that the tracks are assumed to start at (0,0,0).  Making this
  // assumption is important for the Event Mixing-- it is not a mistake. - MALisa
  double NominalTpcExitSeparation() const;
  double NominalTpcEntranceSeparation() const;

  double NominalTpcAverageSeparation() const;

  double OpeningAngle() const;

private:
  StHbtParticle* mTrack1;
  StHbtParticle* mTrack2;

};

inline void StHbtPair::SetTrack1(const StHbtParticle* trkPtr){mTrack1=(StHbtParticle*)trkPtr;}
inline void StHbtPair::SetTrack2(const StHbtParticle* trkPtr){mTrack2=(StHbtParticle*)trkPtr;}

inline StHbtParticle* StHbtPair::track1() const {return mTrack1;}
inline StHbtParticle* StHbtPair::track2() const {return mTrack2;}

#endif
