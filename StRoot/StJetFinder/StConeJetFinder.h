// -*- mode: c++;-*-
// $Id: StConeJetFinder.h,v 1.41 2008/05/08 02:22:25 tai Exp $
#ifndef StConeJetFinder_HH
#define StConeJetFinder_HH

#include "StConeJetFinderBase.h"

class StConeJetFinder : public StConeJetFinderBase {

public:
	
  StConeJetFinder(const StConePars& pars);
  virtual ~StConeJetFinder();

  void findJets(JetList& protoJetList, const FourVecList& particleList);
	
private:

  CellList generateEtOrderedList(JetList& protoJetList);

  void findJetAroundThis(StEtaPhiCell* cell);

  bool shouldNotSearchForJetAroundThis(const StEtaPhiCell* cell) const;

  void findJetWithStableCone();
	
  CellList generateMidpointList();

  void findProtoJetsAroundMidpoints(CellList& midpointList);

  bool isInTheVolume(double eta, double phi);

  bool areTheyInTheSameCell(double eta1, double phi1, double eta2, double phi2);

  StJetSpliterMerger* mMerger;


};

#endif

