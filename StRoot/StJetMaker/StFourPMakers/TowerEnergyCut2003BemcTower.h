// -*- mode: c++;-*-
// $Id: TowerEnergyCut2003BemcTower.h,v 1.1 2008/07/13 09:38:00 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef TOWERENERGYCUT2003BEMCTOWER_H
#define TOWERENERGYCUT2003BEMCTOWER_H

#include "TowerEnergyCut.h"

#include <set>

namespace StJetTowerEnergyCut {

class TowerEnergyCut2003BemcTower : public TowerEnergyCut {

public:
  TowerEnergyCut2003BemcTower() { }
  virtual ~TowerEnergyCut2003BemcTower() { }

  bool operator()(const StSpinJet::TowerEnergy& tower)
  {
    const static int badWestTowerId[ ] = { 511, 555, 615, 656, 772, 953, 1042, 1043, 1044, 1045, 1046, 1048, 1385, 1386, 1387, 1408, 1418, 1419, 1555, 1614, 1615, 1616, 1636, 1705, 1706, 1707, 1708, 1725, 1726, 1727, 1728, 1745, 1746, 1747, 1748, 1750, 1765, 1766, 1767, 1768, 1773, 1785, 1786, 1787, 1788, 1866, 1867, 1868, 1869, 1870, 1871, 1872, 1873, 1874, 1875, 1876, 1877, 1878, 1879, 1880, 1881, 1882, 1883, 1884, 1885, 1886, 1887, 1888, 1889, 1890, 1891, 1892, 1893, 1894, 1899, 2073, 2093, 2096, 2127 };
    const static std::set<int> badWestTowerIdSet(badWestTowerId, badWestTowerId + sizeof(badWestTowerId)/sizeof(int));

    if(tower.detectorId != 9) return true;

    if(tower.towerId > 2400) return true;

    if(badWestTowerIdSet.count(tower.towerId)) return true;

    return false;
  }

private:
  
};

}

#endif // TOWERENERGYCUT2003BEMCTOWER_H
